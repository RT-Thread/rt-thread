//*****************************************************************************
//
//  am_hal_iom.c
//! @file
//!
//! @brief Functions for interfacing with the IO Master module
//!
//! @addtogroup iom2 IO Master (SPI/I2C)
//! @ingroup apollo2hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

#ifdef __IAR_SYSTEMS_ICC__
#define AM_INSTR_CLZ(n)                     __CLZ(n)
#else
#define AM_INSTR_CLZ(n)                     __builtin_clz(n)
#endif

//! ASSERT(1) or Correct(0) invalid IOM R/W Thresholds.
#ifndef AM_ASSERT_INVALID_THRESHOLD
#define AM_ASSERT_INVALID_THRESHOLD    (1)
#endif

//*****************************************************************************
//
// Forcing optimizations
//
// These pragmas must be enabled if we intend to use the IOM4 workaround with a
// delay higher than 18-bits in the first word.
//
//*****************************************************************************
//#ifdef __IAR_SYSTEMS_ICC__
//#pragma optimize=3 s
//#endif
//
//#ifdef __ARMCC_VERSION
//#pragma O3
//#endif
//
//#ifdef __GNUC__
//#pragma GCC optimize ("O3")
//#endif

//*****************************************************************************
//
// Forward declarations.
//
//*****************************************************************************
static void iom_workaround_loop(uint32_t ui32PadRegVal,
                                volatile uint32_t *pui32PadReg,
                                bool bRising);
static uint32_t
internal_am_hal_iom_spi_cmd_construct(uint32_t ui32Operation,
                                      uint32_t ui32ChipSelect,
                                      uint32_t ui32NumBytes,
                                      uint32_t ui32Options);
static am_hal_iom_status_e
internal_iom_wait_i2c_scl_hi(uint32_t ui32Module);

//*****************************************************************************
//
// IOM Buffer states.
//
//*****************************************************************************
#define BUFFER_IDLE                         0x0
#define BUFFER_SENDING                      0x1
#define BUFFER_RECEIVING                    0x2

//*****************************************************************************
//
// Global state variables
//
//*****************************************************************************
//
// Define a structure to map CE for IOM4 only.
//
typedef struct
{
  uint8_t       channel;        // CE channel for SPI
  uint8_t       pad;            // GPIO Pad
  uint8_t       funcsel;        // FNCSEL value
} IOMPad_t;

// Define the mapping between SPI CEn, Pads, and FNCSEL values for all IOMs.
const IOMPad_t g_IOMPads[] =
{
    {0, 29, 6}, {0, 34, 6}, {1, 18, 4}, {1, 37, 5}, {2, 41, 6},
    {3, 17, 4}, {3, 45, 4}, {4, 10, 6}, {4, 46, 6}, {5,  9, 4},
    {5, 47, 6}, {6, 35, 4}, {7, 38, 6}
};

typedef struct
{
  uint8_t       module;         // IOM module
  uint8_t       pad;            // GPIO Pad
  uint8_t       funcsel;        // FNCSEL value
} I2CPad_t;

// Define the mapping between I2C SCL Pads, and FNCSEL values for all IOMs.
const I2CPad_t g_I2CPads[] =
{
    {0, 5, 0},
    {1, 8, 0},
    {2, 0, 7},
    {3, 42, 4},
    {4, 39, 4},
    {5, 48, 4},
    {2, 27, 4},
};

// Defines for IOM 4 Workaround
#define WORKAROUND_IOM          4
#define WORKAROUND_IOM_MOSI_PIN 44
#define WORKAROUND_IOM_MOSI_CFG AM_HAL_PIN_44_M4MOSI

#define MAX_IOM_BITS            9
#define IOM_OVERHEAD_FACTOR     2

//*****************************************************************************
//
// Non-blocking buffer and buffer-management variables.
//
//*****************************************************************************
typedef struct
{
    uint32_t ui32State;
    uint32_t *pui32Data;
    uint32_t ui32BytesLeft;
    uint32_t ui32Options;
    void (*pfnCallback)(void);
}
am_hal_iom_nb_buffer;

//
// Global State to keep track if there is an ongoing transaction
//
volatile bool g_bIomBusy[AM_REG_IOMSTR_NUM_MODULES + 1] = {0};

am_hal_iom_nb_buffer g_psIOMBuffers[AM_REG_IOMSTR_NUM_MODULES];

//
// Save error status from non-blocking calls
//
static am_hal_iom_status_e g_iom_error_status[AM_REG_IOMSTR_NUM_MODULES + 1];

//*****************************************************************************
//
// Computed timeout.
//
// The IOM may not always respond to events (e.g., CMDCMP).  This is a
// timeout value in cycles to be used when waiting on status changes.
//*****************************************************************************
uint32_t ui32StatusTimeout[AM_REG_IOMSTR_NUM_MODULES];

//*****************************************************************************
//
// Queue management variables.
//
//*****************************************************************************
am_hal_queue_t g_psIOMQueue[AM_REG_IOMSTR_NUM_MODULES];

//*****************************************************************************
//
// Default queue flush function
//
//*****************************************************************************
am_hal_iom_queue_flush_t am_hal_iom_queue_flush = am_hal_iom_sleeping_queue_flush;

//*****************************************************************************
//
// Power management structure.
//
//*****************************************************************************
am_hal_iom_pwrsave_t am_hal_iom_pwrsave[AM_REG_IOMSTR_NUM_MODULES];

//*****************************************************************************
//
// I2C BitBang to IOM error mapping
//
//*****************************************************************************
const am_hal_iom_status_e i2c_bb_errmap[AM_HAL_I2C_BIT_BANG_STATUS_MAX] =
    {
        AM_HAL_IOM_SUCCESS, // AM_HAL_I2C_BIT_BANG_SUCCESS,
        AM_HAL_IOM_ERR_I2C_NAK, // AM_HAL_I2C_BIT_BANG_ADDRESS_NAKED,
        AM_HAL_IOM_ERR_I2C_NAK, // AM_HAL_I2C_BIT_BANG_DATA_NAKED,
        AM_HAL_IOM_ERR_TIMEOUT, // AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT,
        AM_HAL_IOM_ERR_TIMEOUT, // AM_HAL_I2C_BIT_BANG_DATA_TIMEOUT,
    };

//*****************************************************************************
//
// Static helper functions
//
//*****************************************************************************

//*****************************************************************************
//
// Get the error interrupt staus
//
//*****************************************************************************
//
//! @brief Returns the error status based on interrupt bits
//!
//! @param ui32Module - IOM module
//!        ui32Status - Currently accumulated error status
//!
//! The function looks at the supplied interrupt error status bits and the
//! the current INTSTAT and maps the same to the enum am_hal_iom_status_e.
//!
//! @return Returns the appropriate error status in the form of am_hal_iom_status_e
//!
//*****************************************************************************
static am_hal_iom_status_e
internal_iom_get_int_err(uint32_t ui32Module, uint32_t ui32IntStatus)
{
    am_hal_iom_status_e ui32Status = AM_HAL_IOM_SUCCESS;
    //
    // Let's accumulate the errors
    //
    ui32IntStatus |= am_hal_iom_int_status_get(ui32Module, false);

    if (ui32IntStatus & AM_HAL_IOM_INT_SWERR)
    {
        // Error in hardware command issued or illegal access by SW
        ui32Status = AM_HAL_IOM_ERR_INVALID_OPER;
    }
    else if (ui32IntStatus & AM_HAL_IOM_INT_I2CARBERR)
    {
        // Loss of I2C multi-master arbitration
        ui32Status = AM_HAL_IOM_ERR_I2C_ARB;
    }
    else if (ui32IntStatus & AM_HAL_IOM_INT_NAK)
    {
        // I2C NAK
        ui32Status = AM_HAL_IOM_ERR_I2C_NAK;
    }
    return ui32Status;
}

//*****************************************************************************
// onebit()
//*****************************************************************************
//
// A power of 2?
// Return true if ui32Value has exactly 1 bit set, otherwise false.
//
static bool onebit(uint32_t ui32Value)
{
    return ui32Value  &&  !(ui32Value & (ui32Value - 1));
}

//*****************************************************************************
// compute_freq()
//*****************************************************************************
//
// Compute the interface frequency based on the given parameters
//
static uint32_t compute_freq(uint32_t ui32HFRCfreqHz,
                             uint32_t ui32Fsel, uint32_t ui32Div3,
                             uint32_t ui32DivEn, uint32_t ui32TotPer)
{
    uint32_t ui32Denomfinal, ui32ClkFreq;

    ui32Denomfinal = ((1 << (ui32Fsel - 1)) * (1 + ui32Div3 * 2) * (1 + ui32DivEn * (ui32TotPer)));
    ui32ClkFreq = (ui32HFRCfreqHz) / ui32Denomfinal;                           // Compute the set frequency value
    ui32ClkFreq +=  (((ui32HFRCfreqHz) % ui32Denomfinal) > (ui32Denomfinal / 2)) ? 1 : 0;

    return ui32ClkFreq;
}

//*****************************************************************************
// iom_calc_gpio()
//
// Calculate the IOM4 GPIO to assert.
//
//*****************************************************************************
static uint32_t iom_calc_gpio(uint32_t ui32ChipSelect)
{
    uint32_t      index;
    uint8_t       ui8PadRegVal, ui8FncSelVal;

    //
    // Figure out which GPIO we are using for the IOM
    //
    for ( index = 0; index < (sizeof(g_IOMPads) / sizeof(IOMPad_t)); index++ )
    {
        //
        //  Is this one of the CEn that we are using?
        //
        if ( g_IOMPads[index].channel == ui32ChipSelect )
        {
            //
            // Get the PAD register value
            //
            ui8PadRegVal = ((AM_REGVAL(AM_HAL_GPIO_PADREG(g_IOMPads[index].pad))) &
                             AM_HAL_GPIO_PADREG_M(g_IOMPads[index].pad)) >>
                             AM_HAL_GPIO_PADREG_S(g_IOMPads[index].pad);

            //
            // Get the FNCSEL field value
            //
            ui8FncSelVal = (ui8PadRegVal & 0x38) >> 3;

            //
            // Is the FNCSEL filed for this pad set to the expected value?
            //
            if ( ui8FncSelVal == g_IOMPads[index].funcsel )
            {
                // This is the GPIO we need to use.
                return g_IOMPads[index].pad;
            }
        }
    }
    return 0xDEADBEEF;
}

//*****************************************************************************
//
// Checks to see if this processor is a Rev B0 device.
//
// This is needed for the B0 IOM workaround.
//
//*****************************************************************************
bool
isRevB0(void)
{
    //
    // Check to make sure the major rev is B and the minor rev is zero.
    //
    if ( (AM_REG(MCUCTRL, CHIPREV) & 0xFF) == AM_REG_MCUCTRL_CHIPREV_REVMAJ_B )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//*****************************************************************************
//
// Checks to see if this processor is a Rev B2 device.
//
// This is needed for the B2 I2C workaround.
//
//*****************************************************************************
static bool
isRevB2(void)
{
    //
    // Check to make sure the major rev is B and the minor rev is zero.
    //
    if ( (AM_REG(MCUCTRL, CHIPREV) & 0xFF) ==
         (AM_REG_MCUCTRL_CHIPREV_REVMAJ_B | AM_REG_MCUCTRL_CHIPREV_REVMIN_REV2) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//*****************************************************************************
//
// Checks and waits for the SCL line to be high
// This is to ensure clock hi time specs are not violated in case slave did
// clock stretching in previous transaction
//
//*****************************************************************************
static am_hal_iom_status_e
internal_iom_wait_i2c_scl_hi(uint32_t ui32Module)
{
    uint32_t ui32IOMGPIO = 0xDEADBEEF;
    volatile uint32_t *pui32SCLPadreg;
    uint32_t ui32SCLPadregVal;
    uint32_t index;
    uint8_t  ui8PadRegVal;
    uint8_t  ui8FncSelVal;
    uint32_t waitStatus;

    // Need to change the SCL pin as a GPIO and poll till it is set to hi
    // For all the IOM's except for IOM2, there is a single designated pin for SCL
    // IOM2 has two choices and we need to determine which one

    //
    // Figure out which GPIO we are using for the SCL
    //
    for ( index = 0; index < (sizeof(g_I2CPads) / sizeof(I2CPad_t)); index++ )
    {
        //
        //  Is this for the IOM that we are using?
        //
        if ( g_I2CPads[index].module == ui32Module )
        {
            //
            // Get the PAD register value
            //
            ui8PadRegVal = ((AM_REGVAL(AM_HAL_GPIO_PADREG(g_I2CPads[index].pad))) &
                             AM_HAL_GPIO_PADREG_M(g_I2CPads[index].pad)) >>
                             AM_HAL_GPIO_PADREG_S(g_I2CPads[index].pad);

            //
            // Get the FNCSEL field value
            //
            ui8FncSelVal = (ui8PadRegVal & 0x38) >> 3;

            //
            // Is the FNCSEL filed for this pad set to the expected value?
            //
            if ( ui8FncSelVal == g_I2CPads[index].funcsel )
            {
                // This is the GPIO we need to use.
                ui32IOMGPIO = g_I2CPads[index].pad;
                break;
            }
        }
    }
    if (0xDEADBEEF == ui32IOMGPIO)
    {
        // SCL has not been configured
        return AM_HAL_IOM_ERR_INVALID_CFG;
    }

    //
    // Save the locations and values of the SCL pin configuration
    // information.
    //
    pui32SCLPadreg = (volatile uint32_t *)AM_HAL_GPIO_PADREG(ui32IOMGPIO);
    ui32SCLPadregVal = *pui32SCLPadreg;
    //
    // Temporarily configure the override pin as an input.
    //
    am_hal_gpio_pin_config(ui32IOMGPIO, AM_HAL_PIN_INPUT);

    //
    // Make sure SCL is high within standard timeout
    //
    waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                 AM_HAL_GPIO_RD_REG(ui32IOMGPIO), AM_HAL_GPIO_RD_M(ui32IOMGPIO),
                 AM_HAL_GPIO_RD_M(ui32IOMGPIO));

    //
    // Write the GPIO PADKEY register
    //
    AM_REGn(GPIO, 0, PADKEY) = AM_REG_GPIO_PADKEY_KEYVAL;
    // Revert back the original settings
    *pui32SCLPadreg = ui32SCLPadregVal;
    //
    // Re-lock the GPIO PADKEY register
    //
    AM_REGn(GPIO, 0, PADKEY) = 0;

    if (waitStatus != 1)
    {
        return AM_HAL_IOM_ERR_TIMEOUT;
    }

    return AM_HAL_IOM_SUCCESS;
}

//*****************************************************************************
//
//! @brief Returns the proper settings for the CLKCFG register.
//!
//! @param ui32FreqHz - The desired interface frequency in Hz.
//!        ui32Phase  - SPI phase (0 or 1).  Can affect duty cycle.
//!
//! Given a desired serial interface clock frequency, this function computes
//! the appropriate settings for the various fields in the CLKCFG register
//! and returns the 32-bit value that should be written to that register.
//! The actual interface frequency may be slightly lower than the specified
//! frequency, but the actual frequency is also returned.
//!
//! @note A couple of criteria that this algorithm follow are:
//!  1. For power savings, choose the highest FSEL possible.
//!  2. For best duty cycle, use DIV3 when possible rather than DIVEN.
//!
//! An example of #1 is that both of the following CLKCFGs would result
//! in a frequency of 428,571 Hz:  0x0E071400 and 0x1C0E1300.
//! The former is chosen by the algorithm because it results in FSEL=4
//! while the latter is FSEL=3.
//!
//! An example of #2 is that both of the following CLKCFGs would result
//! in a frequency of 2,000,000 Hz:  0x02011400 and 0x00000C00.
//! The latter is chosen by the algorithm because it results in use of DIV3
//! rather than DIVEN.
//!
//! @return An unsigned 64-bit value.
//! The lower 32-bits represent the value to use to set CLKCFG.
//! The upper 32-bits represent the actual frequency (in Hz) that will result
//! from setting CLKCFG with the lower 32-bits.
//!
//! 0 (64 bits) = error. Note that the caller must check the entire 64 bits.
//! It is not an error if only the low 32-bits are 0 (this is a valid value).
//! But the entire 64 bits returning 0 is an error.
//!
//*****************************************************************************

static
uint64_t iom_get_interface_clock_cfg(uint32_t ui32FreqHz, uint32_t ui32Phase )
{
    uint32_t ui32Fsel, ui32Div3, ui32DivEn, ui32TotPer, ui32LowPer;
    uint32_t ui32Denom, ui32v1, ui32Denomfinal, ui32ClkFreq, ui32ClkCfg;
    uint32_t ui32HFRCfreqHz;
    int32_t i32Div, i32N;

    if ( ui32FreqHz == 0 )
    {
        return 0;
    }

    //
    // Set the HFRC clock frequency.
    //
    ui32HFRCfreqHz = AM_HAL_CLKGEN_FREQ_MAX_HZ;

    //
    // Compute various parameters used for computing the optimal CLKCFG setting.
    //
    i32Div = (ui32HFRCfreqHz / ui32FreqHz) + ((ui32HFRCfreqHz % ui32FreqHz) ? 1 : 0);    // Round up (ceiling)

    //
    // Compute N (count the number of LS zeros of Div) = ctz(Div) = log2(Div & (-Div))
    //
    i32N = 31 - AM_INSTR_CLZ((i32Div & (-i32Div)));

    if ( i32N > 6 )
    {
        i32N = 6;
    }

    ui32Div3 = ( (ui32FreqHz < (ui32HFRCfreqHz / 16384))            ||
                 ( ((ui32FreqHz >= (ui32HFRCfreqHz / 3))    &&
                    (ui32FreqHz <= ((ui32HFRCfreqHz / 2) - 1)) ) ) ) ? 1 : 0;
    ui32Denom = ( 1 << i32N ) * ( 1 + (ui32Div3 * 2) );
    ui32TotPer = i32Div / ui32Denom;
    ui32TotPer += (i32Div % ui32Denom) ? 1 : 0;
    ui32v1 = 31 - AM_INSTR_CLZ(ui32TotPer);     // v1 = log2(TotPer)
    ui32Fsel = (ui32v1 > 7) ? ui32v1 + i32N - 7 : i32N;
    ui32Fsel++;

    if ( ui32Fsel > 7 )
    {
        //
        // This is an error, can't go that low.
        //
        return 0;
    }

    if ( ui32v1 > 7 )
    {
        ui32DivEn = ui32TotPer;     // Save TotPer for the round up calculation
        ui32TotPer = ui32TotPer>>(ui32v1-7);
        ui32TotPer += ((ui32DivEn) % (1 << (ui32v1 - 7))) ? 1 : 0;
    }

    ui32DivEn = ( (ui32FreqHz >= (ui32HFRCfreqHz / 4)) ||
                  ((1 << (ui32Fsel - 1)) == i32Div) ) ? 0 : 1;

    if (ui32Phase == 1)
    {
        ui32LowPer = (ui32TotPer - 2) / 2;          // Longer high phase
    }
    else
    {
        ui32LowPer = (ui32TotPer - 1) / 2;          // Longer low phase
    }

    ui32ClkCfg = AM_REG_IOMSTR_CLKCFG_FSEL(ui32Fsel)                |
                 AM_REG_IOMSTR_CLKCFG_DIV3(ui32Div3)                |
                 AM_REG_IOMSTR_CLKCFG_DIVEN(ui32DivEn)              |
                 AM_REG_IOMSTR_CLKCFG_LOWPER(ui32LowPer)            |
                 AM_REG_IOMSTR_CLKCFG_TOTPER(ui32TotPer - 1);


    //
    // Now, compute the actual frequency, which will be returned.
    //
    ui32ClkFreq = compute_freq(ui32HFRCfreqHz, ui32Fsel, ui32Div3, ui32DivEn, ui32TotPer - 1);

    //
    // Determine if the actual frequency is a power of 2 (MHz).
    //
    if ( (ui32ClkFreq % 250000) == 0 )
    {
        //
        // If the actual clock frequency is a power of 2 ranging from 250KHz up,
        // we can simplify the CLKCFG value using DIV3 (which also results in a
        // better duty cycle).
        //
        ui32Denomfinal = ui32ClkFreq / (uint32_t)250000;

        if ( onebit(ui32Denomfinal) )
        {
            //
            // These configurations can be simplified by using DIV3.  Configs
            // using DIV3 have a 50% duty cycle, while those from DIVEN will
            // have a 66/33 duty cycle.
            //
            ui32TotPer = ui32LowPer = ui32DivEn = 0;
            ui32Div3 = 1;

            //
            // Now, compute the return values.
            //
            ui32ClkFreq = compute_freq(ui32HFRCfreqHz, ui32Fsel, ui32Div3, ui32DivEn, ui32TotPer);

            ui32ClkCfg = AM_REG_IOMSTR_CLKCFG_FSEL(ui32Fsel)    |
                         AM_REG_IOMSTR_CLKCFG_DIV3(1)           |
                         AM_REG_IOMSTR_CLKCFG_DIVEN(0)          |
                         AM_REG_IOMSTR_CLKCFG_LOWPER(0)         |
                         AM_REG_IOMSTR_CLKCFG_TOTPER(0);
        }
    }

    return ( ((uint64_t)ui32ClkFreq) << 32) | (uint64_t)ui32ClkCfg;

} //iom_get_interface_clock_cfg()


//*****************************************************************************
//
//! @brief Clock setting for the I2C Clock Stretch Workaround
//!
//! This restricts the frequencies that can be used for I2C devices on
//!
//! @param  ui32FreqHz - The desired interface frequency in Hz.
//!
//! @return None.
//
//*****************************************************************************
static
uint64_t iom_get_i2c_workaround_clock_cfg(uint32_t ui32FreqHz)
{
  uint32_t      ui32Fsel;

  // Only allow certain SCL frequencies for clock stretching devices.
  if (ui32FreqHz == AM_HAL_IOM_800KHZ)
  {
    ui32Fsel = 2;
  }
  else if (ui32FreqHz == AM_HAL_IOM_400KHZ)
  {
    ui32Fsel = 3;
  }
  else if (ui32FreqHz == AM_HAL_IOM_200KHZ)
  {
    ui32Fsel = 4;
  }
  else if (ui32FreqHz == AM_HAL_IOM_100KHZ)
  {
    ui32Fsel = 5;
  }
  else  // Default is 100KHz.
  {
    ui32Fsel = 5;
  }

  // Return the resulting CLKCFG register settings.
  return (AM_REG_IOMSTR_CLKCFG_FSEL(ui32Fsel) |
    AM_REG_IOMSTR_CLKCFG_DIV3(0)              |
      AM_REG_IOMSTR_CLKCFG_DIVEN(1)           |
        AM_REG_IOMSTR_CLKCFG_LOWPER(14)       |
          AM_REG_IOMSTR_CLKCFG_TOTPER(29));

} // iom_get_i2c_workaround_clock_cfg

//*****************************************************************************
//
//! @brief Enable the IOM in the power control block.
//!
//! This function enables the desigated IOM module in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_pwrctrl_enable(uint32_t ui32Module)
{
    am_hal_debug_assert_msg(ui32Module < AM_REG_IOMSTR_NUM_MODULES,
                            "Trying to enable an IOM module that doesn't exist.");

    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_IOM0 << ui32Module);
}

//*****************************************************************************
//
//! @brief Disable the IOM in the power control block.
//!
//! This function disables the desigated IOM module in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_pwrctrl_disable(uint32_t ui32Module)
{
    am_hal_debug_assert_msg(ui32Module < AM_REG_IOMSTR_NUM_MODULES,
                            "Trying to disable an IOM module that doesn't exist.");

    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_IOM0 << ui32Module);
}

//*****************************************************************************
//
//! @brief Enables the IOM module
//!
//! @param ui32Module - The number of the IOM module to be enabled.
//!
//! This function enables the IOM module using the IFCEN bitfield in the
//! IOMSTR_CFG register.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_enable(uint32_t ui32Module)
{
    if ( ui32Module < AM_REG_IOMSTR_NUM_MODULES )
    {
        AM_REGn(IOMSTR, ui32Module, CFG) |= AM_REG_IOMSTR_CFG_IFCEN(1);
        g_bIomBusy[ui32Module] = false;
    }
}

//*****************************************************************************
//
//! @brief Disables the IOM module.
//!
//! @param ui32Module - The number of the IOM module to be disabled.
//!
//! This function disables the IOM module using the IFCEN bitfield in the
//! IOMSTR_CFG register.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_disable(uint32_t ui32Module)
{
    if ( ui32Module < AM_REG_IOMSTR_NUM_MODULES )
    {
        //
        // Wait until the bus is idle.
        //
        am_hal_iom_poll_complete(ui32Module);

        //
        // Disable the interface.
        //
        AM_REGn(IOMSTR, ui32Module, CFG) &= ~(AM_REG_IOMSTR_CFG_IFCEN(1));
    }
}

//*****************************************************************************
//
//! @brief Enable power to the selected IOM module.
//!
//! @param ui32Module - Module number for the IOM to be turned on.
//!
//! This function enables the power gate to the selected IOM module. It is
//! intended to be used along with am_hal_iom_power_off_save(). Used together,
//! these functions allow the caller to power IOM modules off to save
//! additional power without losing important configuration information.
//!
//! The am_hal_iom_power_off_save() function will save IOM configuration
//! register information to SRAM before powering off the selected IOM module.
//! This function will re-enable the IOM module, and restore those
//! configuration settings from SRAM.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_power_on_restore(uint32_t ui32Module)
{
    am_hal_debug_assert_msg(ui32Module < AM_REG_IOMSTR_NUM_MODULES,
                            "Trying to enable an IOM module that doesn't exist.");

    //
    // Make sure this restore is a companion to a previous save call.
    //
    if ( am_hal_iom_pwrsave[ui32Module].bValid == 0 )
    {
        return;
    }

    //
    // Enable power to the selected IOM.
    //
    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_IOM0 << ui32Module);

    //
    // Restore the IOM configuration registers from the structure in SRAM.
    //
    AM_REGn(IOMSTR, ui32Module, FIFOTHR) = am_hal_iom_pwrsave[ui32Module].FIFOTHR;
    AM_REGn(IOMSTR, ui32Module, CLKCFG) = am_hal_iom_pwrsave[ui32Module].CLKCFG;
    AM_REGn(IOMSTR, ui32Module, CFG) = am_hal_iom_pwrsave[ui32Module].CFG;
    AM_REGn(IOMSTR, ui32Module, INTEN) = am_hal_iom_pwrsave[ui32Module].INTEN;

    //
    // Indicates we have restored the configuration.
    //
    am_hal_iom_pwrsave[ui32Module].bValid = 0;
}

//*****************************************************************************
//
//! @brief Disable power to the selected IOM module.
//!
//! @param ui32Module - Module number for the IOM to be turned off.
//!
//! This function disables the power gate to the selected IOM module. It is
//! intended to be used along with am_hal_iom_power_on_restore(). Used together,
//! these functions allow the caller to power IOM modules off to save
//! additional power without losing important configuration information.
//!
//! The am_hal_iom_power_off_save() function will save IOM configuration
//! register information to SRAM before powering off the selected IOM module.
//! The am_hal_iom_power_on_restore() function will re-enable the IOM module
//! and restore those configuration settings from SRAM.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_power_off_save(uint32_t ui32Module)
{
    am_hal_debug_assert_msg(ui32Module < AM_REG_IOMSTR_NUM_MODULES,
                            "Trying to disable an IOM module that doesn't exist.");

    //
    // Save the IOM configuration registers to the structure in SRAM.
    //
    am_hal_iom_pwrsave[ui32Module].FIFOTHR = AM_REGn(IOMSTR, ui32Module, FIFOTHR);
    am_hal_iom_pwrsave[ui32Module].CLKCFG = AM_REGn(IOMSTR, ui32Module, CLKCFG);
    am_hal_iom_pwrsave[ui32Module].CFG = AM_REGn(IOMSTR, ui32Module, CFG);
    am_hal_iom_pwrsave[ui32Module].INTEN = AM_REGn(IOMSTR, ui32Module, INTEN);

    //
    // Indicates we have a valid saved configuration.
    //
    am_hal_iom_pwrsave[ui32Module].bValid = 1;

    //
    // Disable power to the selected IOM.
    //
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_IOM0 << ui32Module);
}

//
//! Check and correct the IOM FIFO threshold.
//
#define MAX_RW_THRESHOLD    (AM_HAL_IOM_MAX_FIFO_SIZE - 4)
#define MIN_RW_THRESHOLD    (4)
#if (AM_ASSERT_INVALID_THRESHOLD == 0)
static uint8_t check_iom_threshold(const uint8_t iom_threshold)
{
    uint8_t corrected_threshold = iom_threshold;

    if ( corrected_threshold < MIN_RW_THRESHOLD )
    {
        corrected_threshold = MIN_RW_THRESHOLD;
    }

    if ( corrected_threshold > MAX_RW_THRESHOLD )
    {
        corrected_threshold = MAX_RW_THRESHOLD;
    }

    return corrected_threshold;
}
#endif

//*****************************************************************************
//
//! @brief Sets module-wide configuration options for the IOM module.
//!
//! @param ui32Module - The instance number for the module to be configured
//! (zero or one)
//!
//! @param psConfig - Pointer to an IOM configuration structure.
//!
//! This function is used to set the interface mode (SPI or I2C), clock
//! frequency, SPI format (when relevant), and FIFO read/write interrupt
//! thresholds for the IO master. For more information on specific
//! configuration options, please see the documentation for the configuration
//! structure.
//!
//! @note The IOM module should be disabled before configuring or
//! re-configuring. This function will not re-enable the module when it
//! completes. Call the am_hal_iom_enable function when the module is
//! configured and ready to use.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_config(uint32_t ui32Module, const am_hal_iom_config_t *psConfig)
{
    uint32_t ui32Config, ui32ClkCfg;

    //
    // Start by checking the interface mode (I2C or SPI), and writing it to the
    // configuration word.
    //
    ui32Config = psConfig->ui32InterfaceMode;

    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    //
    // Check the SPI format, and OR in the bits for SPHA (clock phase) and SPOL
    // (polarity). These shouldn't have any effect in I2C mode, so it should be
    // ok to write them without checking exactly which mode we're in.
    //
    if ( psConfig->bSPHA )
    {
        ui32Config |= AM_REG_IOMSTR_CFG_SPHA(1);
    }

    if ( psConfig->bSPOL )
    {
        ui32Config |= AM_REG_IOMSTR_CFG_SPOL(1);
    }

    // Set the STARTRD based on the interface speed
    // For all I2C frequencies and SPI frequencies below 16 MHz, the STARTRD
    // field should be set to 0 to minimize the potential of the IO transfer
    // holding off a bus access to the FIFO. For SPI frequencies of 16 MHz
    // or 24 MHz, the STARTRD field must be set to a value of 2 to insure
    // enough time for the IO preread.
    if ( psConfig->ui32ClockFrequency >= 16000000UL)
    {
        ui32Config |= AM_REG_IOMSTR_CFG_STARTRD(2);
    }

    //
    // Write the resulting configuration word to the IO master CFG register for
    // the module number we were provided.
    //
    AM_REGn(IOMSTR, ui32Module, CFG) = ui32Config;

    //
    // Write the FIFO write and read thresholds to the appropriate registers.
    //
#if     (AM_ASSERT_INVALID_THRESHOLD == 1)
    am_hal_debug_assert_msg(
        (psConfig->ui8WriteThreshold <= MAX_RW_THRESHOLD), "IOM write threshold too big.");
    am_hal_debug_assert_msg(
        (psConfig->ui8ReadThreshold <= MAX_RW_THRESHOLD), "IOM read threshold too big.");
    am_hal_debug_assert_msg(
        (psConfig->ui8WriteThreshold >= MIN_RW_THRESHOLD), "IOM write threshold too small.");
    am_hal_debug_assert_msg(
        (psConfig->ui8ReadThreshold >= MIN_RW_THRESHOLD), "IOM read threshold too small.");

    AM_REGn(IOMSTR, ui32Module, FIFOTHR) =
        (AM_REG_IOMSTR_FIFOTHR_FIFOWTHR(psConfig->ui8WriteThreshold) |
         AM_REG_IOMSTR_FIFOTHR_FIFORTHR(psConfig->ui8ReadThreshold));
#elif   (AM_ASSERT_INVALID_THRESHOLD == 0)
    AM_REGn(IOMSTR, ui32Module, FIFOTHR) =
        (AM_REG_IOMSTR_FIFOTHR_FIFOWTHR(check_iom_threshold(psConfig->ui8WriteThreshold)) |
         AM_REG_IOMSTR_FIFOTHR_FIFORTHR(check_iom_threshold(psConfig->ui8ReadThreshold)));
#else
#error AM_ASSERT_INVALID_THRESHOLD must be 0 or 1.
#endif

    // Apply I2C clock stretching workaround if B2 silicon and IOM 1,2,3, or 5
    // Note: Only I2C clock speeds of AM_HAL_IOM_800KHZ, AM_HAL_IOM_400KHZ,
    // AM_HAL_IOM_200KHZ, and AM_HAL_IOM_100KHZ are allowed.  Other values will
    // result in the default of AM_HAL_IOM_100KHZ.
    if ((0 != ui32Module) && (4 != ui32Module) && (6 != ui32Module) && 
			isRevB2() && (AM_HAL_IOM_I2CMODE == psConfig->ui32InterfaceMode))
    {
      // Set SPHA field to 1 on B2 silicon to enable the feature;
      AM_REGn(IOMSTR, ui32Module, CFG) |= AM_REG_IOMSTR_CFG_SPHA_M;
      ui32ClkCfg = iom_get_i2c_workaround_clock_cfg(psConfig->ui32ClockFrequency);
    }
    else
    {
      //
      // An exception occurs in the LOWPER computation when setting an interface
      //  frequency (such as a divide by 5 frequency) which results in a 60/40
      //  duty cycle.  The 60% cycle must occur in the appropriate half-period,
      //  as only one of the half-periods is active, depending on which phase
      //  is being selected.
      // If SPHA=0 the low period must be 60%. If SPHA=1 high period must be 60%.
      // Note that the predetermined frequency parameters use the formula
      //  lowper = (totper-1)/2, which results in a 60% low period.
      //
      ui32ClkCfg = iom_get_interface_clock_cfg(psConfig->ui32ClockFrequency,
                                               psConfig->bSPHA );
    }

    if ( ui32ClkCfg )
    {
        AM_REGn(IOMSTR, ui32Module, CLKCFG) = (uint32_t)ui32ClkCfg;
    }

    //
    // Compute the status timeout value.
    //
    ui32StatusTimeout[ui32Module] = MAX_IOM_BITS * AM_HAL_IOM_MAX_FIFO_SIZE *
      IOM_OVERHEAD_FACTOR * (am_hal_clkgen_sysclk_get() / psConfig->ui32ClockFrequency);
}

//*****************************************************************************
//
//! @brief Returns the actual currently configured interface frequency in Hz.
//
//*****************************************************************************
uint32_t
am_hal_iom_frequency_get(uint32_t ui32ClkCfg)
{
    uint32_t ui32Freq;

    ui32Freq = compute_freq(AM_HAL_CLKGEN_FREQ_MAX_HZ,
    (ui32ClkCfg & AM_REG_IOMSTR_CLKCFG_FSEL_M)  >> AM_REG_IOMSTR_CLKCFG_FSEL_S,
    (ui32ClkCfg & AM_REG_IOMSTR_CLKCFG_DIV3_M)  >> AM_REG_IOMSTR_CLKCFG_DIV3_S,
    (ui32ClkCfg & AM_REG_IOMSTR_CLKCFG_DIVEN_M) >> AM_REG_IOMSTR_CLKCFG_DIVEN_S,
    (ui32ClkCfg & AM_REG_IOMSTR_CLKCFG_TOTPER_M)>> AM_REG_IOMSTR_CLKCFG_TOTPER_S);

    return ui32Freq;
}

//*****************************************************************************
//
// Helper function for the B0 workaround.
//
//*****************************************************************************
static uint32_t
iom_get_workaround_fsel(uint32_t maxFreq)
{
    uint32_t ui32Freq, ui32Fsel;
    uint32_t ui32ClkCfg = AM_REGn(IOMSTR, 4, CLKCFG);

    //
    // Starting with the current clock configuration parameters, find a value
    // of FSEL that will bring our total frequency down to or below maxFreq.
    //
    for ( ui32Fsel = 1; ui32Fsel < 8; ui32Fsel++ )
    {
        ui32Freq = compute_freq(AM_HAL_CLKGEN_FREQ_MAX_HZ, ui32Fsel,
                                AM_BFX(IOMSTR, CLKCFG, DIV3, ui32ClkCfg),
                                AM_BFX(IOMSTR, CLKCFG, DIVEN, ui32ClkCfg),
                                AM_BFX(IOMSTR, CLKCFG, TOTPER, ui32ClkCfg));

        if ( ui32Freq <= maxFreq && ui32Freq != 0 )
        {
            //
            // Return the new FSEL
            //
            return ui32Fsel;
        }
    }

    //
    // Couldn't find an appropriate frequency. This should be impossible
    // because there should always be a value of FSEL that brings the final IOM
    // frequency below 500 KHz.
    //
    am_hal_debug_assert_msg(false, "Could find a valid frequency.  Should never get here.");
    return maxFreq;
}

// Separating this piece of code in separate function to keep the impact of
// rest of the code to mimimal because of stack usage
static void
internal_iom_workaround_critical(uint32_t ui32Command,
                                 volatile uint32_t *pui32CSPadreg,
                                 uint32_t ui32CSPadregVal,
                                 uint32_t ui32DelayTime,
                                 uint32_t ui32ClkCfg,
                                 uint32_t ui32LowClkCfg,
                                 bool bRising)
{
    uint32_t ui32Critical = 0;
    //
    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // Start the write on the bus.
    //
    AM_REGn(IOMSTR, WORKAROUND_IOM, CMD) = ui32Command;

    //
    // Slow down the clock, and run the workaround loop. The workaround
    // loop runs an edge-detector on MOSI, and triggers a falling edge on
    // chip-enable on the first bit of our real data.
    //
    ((void (*)(uint32_t)) 0x0800009d)(ui32DelayTime);
    // Switch to Low Freq
    AM_REGn(IOMSTR, WORKAROUND_IOM, CLKCFG) = ui32LowClkCfg;
    iom_workaround_loop(ui32CSPadregVal, pui32CSPadreg, bRising);
    //
    // Restore the clock frequency and the normal MOSI pin function.
    //
    AM_REGn(IOMSTR, WORKAROUND_IOM, CLKCFG) = ui32ClkCfg;
    am_hal_gpio_pin_config(WORKAROUND_IOM_MOSI_PIN, WORKAROUND_IOM_MOSI_CFG);

    //
    // End the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);
}


//*****************************************************************************
//
//! @brief Workaround for an Apollo2 Rev B0 issue.
//!
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//!
//! Some Apollo2 Rev B0 devices have an issue where the first byte of a SPI
//! write transaction can have some of its bits changed from ones to zeroes. In
//! order to get around this issue, we artificially pad the SPI write data with
//! additional bytes, and manually control the CS pin for the beginning of the
//! SPI frame so that the receiving device will ignore the bytes of padding
//! that we added.
//!
//! This function acts as a helper function to higher-level spi APIs. It
//! performs the functions of am_hal_iom_fifo_write() and
//! am_hal_iom_spi_cmd_run() to get a SPI write started on the bus, including
//! all of the necessary workaround behavior.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_workaround_word_write(uint32_t ui32ChipSelect,
                                 uint32_t *pui32Data, uint32_t ui32NumBytes,
                                 uint32_t ui32Options)
{
    uint32_t ui32TransferSize;
    uint32_t ui32IOMGPIO = 0xDEADBEEF;
    volatile uint32_t *pui32CSPadreg = 0;
    uint32_t ui32CSPadregVal = 0;
    uint32_t ui32ClkCfg = 0;
    uint32_t ui32HiClkCfg, ui32LowClkCfg;
    bool bRising = 0;
    uint32_t ui32HiFreq = 0, ui32NormalFreq = 0;
    uint32_t ui32DelayTime = 0;
    uint32_t ui32LowFsel = 0;
    uint32_t ui32HiFsel = 0;
    uint32_t ui32FirstWord = 0;
    uint32_t ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, WORKAROUND_IOM, CFG, FULLDUP)) ?
                               AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);
    uint32_t ui32Command;
    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    // Note: This is a little shorter than usual, since the workaround
    // consumes an extra byte at the beginning of the transfer.
    //
    am_hal_debug_assert_msg(ui32NumBytes <= 4091, "SPI transfer too big.");

    //
    // Create a "dummy" word to add on to the beginning of the transfer
    // that will guarantee a transition between the first word and the
    // second on the bus.
    //
    // For raw transactions, this is straightforward. For transactions
    // preceded by an offset, we'll add the offset in to the "dummy" word
    // to preserve data alignment later.
    //
    // The workaround uses a critical section for precision
    // To minimize the time in critical section, we raise the SPI frequency
    // to the max possible for the initial preamble to be clocked out
    // then we switch to a 'reasonably' slow frequency to be able to reliably
    // catch the rising or falling edge by polling. Then we switch back to
    // configured frequency
    //

    // We want to slow down the clock to help us count edges more
    // accurately. Save it first, then slow it down. Also, we will
    // pre-calculate a delay for when we need to restore the SPI settings.
    //
    ui32ClkCfg = AM_REGn(IOMSTR, WORKAROUND_IOM, CLKCFG);
    // Get the largest speed we can configure within our rated speed of 16MHz
    ui32HiFsel = iom_get_workaround_fsel(16000000);
    ui32HiClkCfg = ((ui32ClkCfg & (~AM_REG_IOMSTR_CLKCFG_FSEL_M)) |
                     AM_BFV(IOMSTR, CLKCFG, FSEL, ui32HiFsel));
    // Switch to Hi Freq
    // Need to make sure we wait long enough for the hi clock to be effective
    // Delay 2 cycles based on previous frequency
    ui32NormalFreq = am_hal_iom_frequency_get(ui32ClkCfg);
    AM_REGn(IOMSTR, WORKAROUND_IOM, CLKCFG) = ui32HiClkCfg;
    ui32DelayTime = ((2 * AM_HAL_CLKGEN_FREQ_MAX_HZ) / (ui32NormalFreq * 3));
    ((void (*)(uint32_t)) 0x0800009d)(ui32DelayTime);
    //
    // Remember what frequency we'll be running at.during Hi Phase
    //
    ui32HiFreq = am_hal_iom_frequency_get(ui32HiClkCfg);

    //
    // Validate return value to prevent DIVBY0 errors.
    //
    am_hal_debug_assert_msg(ui32HiFreq > 0, "Invalid Hi Frequency for IOM.");

    // Get a reasonably slow speed (~1MHz) we can safely poll for the transition
    ui32LowFsel = iom_get_workaround_fsel(1000000);
    ui32LowClkCfg = ((ui32ClkCfg & (~AM_REG_IOMSTR_CLKCFG_FSEL_M)) |
                     AM_BFV(IOMSTR, CLKCFG, FSEL, ui32LowFsel));

    if ( ui32Options & AM_HAL_IOM_RAW )
    {
        //
        // The transition we care for is on 33rd bit.
        // Prepare to delay 27 bits past the start of the transaction
        // before getting into polling - to leave some
        // margin for compiler related variations
        //
        ui32DelayTime = ((27 * AM_HAL_CLKGEN_FREQ_MAX_HZ) / (ui32HiFreq * 3));

        if ( pui32Data[0] & 0x80 )
        {
            ui32FirstWord = 0x00000000;
            bRising = true;
        }
        else
        {
            ui32FirstWord = 0xFFFFFF00;
            bRising = false;
        }
    }
    else
    {
        //
        // The transition we care for is on 25th bit.
        // Prepare to delay 19 bits past the start of the transaction
        // before getting into polling - to leave some
        // margin for compiler related variations
        //
        ui32DelayTime = ((19 * AM_HAL_CLKGEN_FREQ_MAX_HZ) / (ui32HiFreq * 3));
        ui32FirstWord = ((ui32Options & 0xFF00) << 16);
        if ( ui32FirstWord & 0x80000000 )
        {
            bRising = true;
        }
        else
        {
            ui32FirstWord |= 0x00FFFF00;
            bRising = false;
        }
    }

    //
    // Now that weve taken care of the offset byte, we can run the
    // transaction in RAW mode.
    //
    ui32Options |= AM_HAL_IOM_RAW;

    ui32NumBytes += 4;

    //
    // Figure out how many bytes we can write to the FIFO immediately.
    //
    ui32TransferSize = (ui32NumBytes <= ui32MaxFifoSize ? ui32NumBytes :
                        ui32MaxFifoSize);

    am_hal_iom_fifo_write(WORKAROUND_IOM, &ui32FirstWord, 4);

    am_hal_iom_fifo_write(WORKAROUND_IOM, pui32Data, ui32TransferSize - 4);

    //
    // Calculate the GPIO to be controlled until the initial shift is
    // complete. Make sure we get a valid value.
    //
    ui32IOMGPIO = iom_calc_gpio(ui32ChipSelect);
    am_hal_debug_assert(0xDEADBEEF != ui32IOMGPIO);

    //
    // Save the locations and values of the CS pin configuration
    // information.
    //
    pui32CSPadreg = (volatile uint32_t *)AM_HAL_GPIO_PADREG(ui32IOMGPIO);
    ui32CSPadregVal = *pui32CSPadreg;

    //
    // Switch CS to a GPIO.
    //
    am_hal_gpio_out_bit_set(ui32IOMGPIO);
    am_hal_gpio_pin_config(ui32IOMGPIO, AM_HAL_GPIO_OUTPUT);

    //
    // Enable the input buffer on MOSI.
    //
    am_hal_gpio_pin_config(WORKAROUND_IOM_MOSI_PIN, WORKAROUND_IOM_MOSI_CFG | AM_HAL_PIN_DIR_INPUT);

    //
    // Write the GPIO PADKEY register to allow the workaround loop to
    // reconfigure chip enable.
    //
    AM_REGn(GPIO, 0, PADKEY) = AM_REG_GPIO_PADKEY_KEYVAL;
    // Preconstruct the command - to save on calculations inside critical section
    ui32Command = internal_am_hal_iom_spi_cmd_construct(AM_HAL_IOM_WRITE,
                        ui32ChipSelect, ui32NumBytes, ui32Options);
    internal_iom_workaround_critical(ui32Command,
            pui32CSPadreg, ui32CSPadregVal,
            ui32DelayTime, ui32ClkCfg,
            ui32LowClkCfg, bRising);
    //
    // Re-lock the GPIO PADKEY register
    //
    AM_REGn(GPIO, 0, PADKEY) = 0;

    //
    // Update the pointer and data counter.
    //
    ui32NumBytes -= ui32TransferSize;
    pui32Data += (ui32TransferSize - 4) >> 2;
}

//*****************************************************************************
//
//! @brief Implement an iterative spin loop.
//!
//! @param ui32Iterations - Number of iterations to delay.
//!
//! Use this function to implement a CPU busy waiting spin.  For Apollo, this
//! delay can be used for timing purposes since for Apollo, each iteration will
//! take 3 cycles.
//!
//! @return None.
//
//*****************************************************************************
#if defined(__GNUC__)
static void __attribute__((naked))
iom_workaround_loop(uint32_t ui32PadRegVal, volatile uint32_t *pui32PadReg,
                    bool bRising)
{
    //
    // Check to see if this is a "rising edge" or "falling edge" detector.
    //
    __asm("    cbz      r2, falling_edge");

    //
    // Read GPIO pin 44, and loop until it's HIGH.
    //
    __asm("rising_edge:");
    __asm("    ldr      r2, =0x40010084");
    __asm("rising_check_mosi:");
    __asm("    ldr      r3, [r2]");
    __asm("    ands     r3, r3, #0x1000");
    __asm("    beq      rising_check_mosi");

    //
    // Write the PADREG Value to the PADREG register.
    //
    __asm("    str     r0, [r1]");
    __asm("    bx      lr");

    //
    // Read GPIO pin 44, and loop until it's LOW.
    //
    __asm("falling_edge:");
    __asm("    ldr      r2, =0x40010084");
    __asm("falling_check_mosi:");
    __asm("    ldr      r3, [r2]");
    __asm("    ands     r3, r3, #0x1000");
    __asm("    bne      falling_check_mosi");

    //
    // Write the PADREG Value to the PADREG register.
    //
    __asm("    str     r0, [r1]");
    __asm("    bx      lr");
}
#elif defined(__CC_ARM)
__asm static void
iom_workaround_loop(uint32_t ui32PadRegVal, volatile uint32_t *pui32PadReg,
                    bool bRising)
{
    //
    // Check to see if this is a "rising edge" or "falling edge" detector.
    //
    cbz      r2, falling_edge

    //
    // Read GPIO pin 44, and loop until it's HIGH.
    //
rising_edge
    ldr      r2, =0x40010084
rising_check_mosi
    ldr      r3, [r2]
    ands     r3, r3, #0x1000
    beq      rising_check_mosi

    //
    // Write the PADREG Value to the PADREG register.
    //
    str     r0, [r1]
    bx      lr

    //
    // Read GPIO pin 44, and loop until it's LOW.
    //
falling_edge
    ldr      r2, =0x40010084
falling_check_mosi
    ldr      r3, [r2]
    ands     r3, r3, #0x1000
    bne      falling_check_mosi

    //
    // Write the PADREG Value to the PADREG register.
    //
    str     r0, [r1]
    bx      lr
    nop
}
#elif defined(__ICCARM__)
static void
iom_workaround_loop(uint32_t ui32PadRegVal, volatile uint32_t *pui32PadReg,
                    bool bRising)
{
    //
    // Check to see if this is a "rising edge" or "falling edge" detector.
    //
    asm(
    "    cbz      r2, falling_edge\n"

    //
    // Read GPIO pin 44, and loop until it's HIGH.
    //
    "rising_edge:\n"
    "    mov32    r2, #0x40010084\n"
    "rising_check_mosi:\n"
    "    ldr      r3, [r2]\n"
    "    ands     r3, r3, #0x1000\n"
    "    beq      rising_check_mosi\n"

    //
    // Write the PADREG Value to the PADREG register.
    //
    "    str     r0, [r1]\n"
    "    bx      lr\n"

    //
    // Read GPIO pin 44, and loop until it's LOW.
    //
    "falling_edge:\n"
    "    mov32    r2, #0x40010084\n"
    "falling_check_mosi:\n"
    "    ldr      r3, [r2]\n"
    "    ands     r3, r3, #0x1000\n"
    "    bne      falling_check_mosi\n"

    //
    // Write the PADREG Value to the PADREG register.
    //
    "    str     r0, [r1]\n"
    "    bx      lr"
    );
}
#endif

//*****************************************************************************
//
//! @brief Perform a simple write to the SPI interface.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs SPI writes to a selected SPI device.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_write(uint32_t ui32Module, uint32_t ui32ChipSelect,
                     uint32_t *pui32Data, uint32_t ui32NumBytes,
                     uint32_t ui32Options)
{
    am_hal_iom_status_e ui32Status;
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Check to see if queues have been enabled. If they are, we'll actually
    // switch to the queued interface.
    //
    if ( g_psIOMQueue[ui32Module].pui8Data != NULL )
    {
        //
        // If the queue is on, go ahead and add this transaction to the queue.
        //
        ui32Status = am_hal_iom_queue_spi_write(ui32Module, ui32ChipSelect, pui32Data,
                                   ui32NumBytes, ui32Options, 0);

        if (ui32Status == AM_HAL_IOM_SUCCESS)
        {
            //
            // Wait until the transaction actually clears.
            //
            am_hal_iom_queue_flush(ui32Module);
            // g_iom_error_status gets set in the isr handling
            ui32Status = g_iom_error_status[ui32Module];
        }

        //
        // At this point, we've completed the transaction, and we can return.
        //
    }
    else
    {
        //
        // Otherwise, we'll just do a polled transaction.
        //
        ui32Status = am_hal_iom_spi_write_nq(ui32Module, ui32ChipSelect, pui32Data,
                                ui32NumBytes, ui32Options);
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform simple SPI read operations.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs simple SPI read operations. The caller is
//! responsible for ensuring that the receive buffer is large enough to hold
//! the requested amount of data.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_read(uint32_t ui32Module, uint32_t ui32ChipSelect,
                    uint32_t *pui32Data, uint32_t ui32NumBytes,
                    uint32_t ui32Options)
{
    am_hal_iom_status_e ui32Status;
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }
    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 4096)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Check to see if queues have been enabled. If they are, we'll actually
    // switch to the queued interface.
    //
    if ( g_psIOMQueue[ui32Module].pui8Data != NULL )
    {
        //
        // If the queue is on, go ahead and add this transaction to the queue.
        //
        ui32Status = am_hal_iom_queue_spi_read(ui32Module, ui32ChipSelect, pui32Data,
                                  ui32NumBytes, ui32Options, 0);

        if (ui32Status == AM_HAL_IOM_SUCCESS)
        {
            //
            // Wait until the transaction actually clears.
            //
            am_hal_iom_queue_flush(ui32Module);
            // g_iom_error_status gets set in the isr handling
            ui32Status = g_iom_error_status[ui32Module];
        }

        //
        // At this point, we've completed the transaction, and we can return.
        //
    }
    else
    {
        //
        // Otherwise, just perform a polled transaction.
        //
        ui32Status = am_hal_iom_spi_read_nq(ui32Module, ui32ChipSelect, pui32Data,
                               ui32NumBytes, ui32Options);
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a simple full-duplex transaction to the SPI interface.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32TxData - Pointer to the bytes that will be sent.
//! @param pui32RxData - Pointer to the bytes that will be received.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs SPI full-duplex operation to a selected SPI device.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32TxData array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui32TxData array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_fullduplex(uint32_t ui32Module, uint32_t ui32ChipSelect,
                          uint32_t *pui32TxData, uint32_t *pui32RxData,
                          uint32_t ui32NumBytes, uint32_t ui32Options)
{
    am_hal_iom_status_e ui32Status;
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }
    //
    // Full-Duplex operation is only supported for Apollo2 B2 Silicon.
    //
    if (!isRevB2())
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_OPER;
        return ui32Status;
    }

    //
    // Check to see if queues have been enabled. If they are, we'll actually
    // switch to the queued interface.
    //
#if 0

    // To be implemented!!!
    if ( g_psIOMQueue[ui32Module].pui8Data != NULL )
    {
        //
        // If the queue is on, go ahead and add this transaction to the queue.
        //
        ui32Status = am_hal_iom_queue_spi_write(ui32Module, ui32ChipSelect, pui32Data,
                                   ui32NumBytes, ui32Options, 0);

        if (ui32Status == AM_HAL_IOM_SUCCESS)
        {
            //
            // Wait until the transaction actually clears.
            //
            am_hal_iom_queue_flush(ui32Module);
            // g_iom_error_status gets set in the isr handling
            ui32Status = g_iom_error_status[ui32Module];
        }

        //
        // At this point, we've completed the transaction, and we can return.
        //
    }
    else
    {
#endif
        //
        // Otherwise, we'll just do a polled transaction.
        //
        ui32Status = am_hal_iom_spi_fullduplex_nq(ui32Module, ui32ChipSelect,
                                                   pui32TxData, pui32RxData,
                                                   ui32NumBytes, ui32Options);
#if 0
    }
#endif

    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a simple write to the SPI interface (without queuing)
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs SPI writes to a selected SPI device.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_write_nq(uint32_t ui32Module, uint32_t ui32ChipSelect,
                        uint32_t *pui32Data, uint32_t ui32NumBytes,
                        uint32_t ui32Options)
{
    uint32_t ui32TransferSize;
    uint32_t ui32SpaceInFifo;
    uint32_t ui32IntConfig;
    uint32_t ui32MaxFifoSize;
    am_hal_iom_status_e ui32Status;
    uint32_t waitStatus;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 4096)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, ui32Module, CFG, FULLDUP)) ?
                       AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);
    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
    ui32IntConfig = AM_REGn(IOMSTR, ui32Module, INTEN);
    AM_REGn(IOMSTR, ui32Module, INTEN) = 0;
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // If we're on a B0 part, and we're using IOM4, our first byte coule be
    // corrupted, so we need to send a dummy word with chip-select held high to
    // get that first byte out of the way.
    //
    // That operation is tricky and detailed, so we'll call a function to do it
    // for us.
    //
    if ( WORKAROUND_IOM == ui32Module && isRevB0() )
    {
        am_hal_iom_workaround_word_write(ui32ChipSelect, pui32Data,
                                         ui32NumBytes, ui32Options);
        //
        // The workaround function is going to a partial transfer for us, but
        // we have to keep our own data-tracking variables updated. Here, we're
        // subtracting 4 bytes from the effective transfer size to account for
        // the 4 bytes of "dummy" word that we sent instead of the actual data.
        //
        ui32TransferSize = (ui32NumBytes <= (ui32MaxFifoSize - 4) ? ui32NumBytes :
                            (ui32MaxFifoSize - 4));
    }
    else
    {
        //
        // Figure out how many bytes we can write to the FIFO immediately.
        //
        ui32TransferSize = (ui32NumBytes <= ui32MaxFifoSize ? ui32NumBytes :
                            ui32MaxFifoSize);
        //
        // write our first word to the fifo.
        //

        am_hal_iom_fifo_write(ui32Module, pui32Data, ui32TransferSize);

        //
        // Start the write on the bus.
        //
        am_hal_iom_spi_cmd_run(AM_HAL_IOM_WRITE, ui32Module, ui32ChipSelect,
                               ui32NumBytes, ui32Options);
    }

    //
    // Update the pointer and data counter.
    //
    ui32NumBytes -= ui32TransferSize;
    pui32Data += ui32TransferSize >> 2;

    //
    // Keep looping until we're out of bytes to send or command complete (error).
    //
    while ( ui32NumBytes && !AM_BFRn(IOMSTR, ui32Module, INTSTAT, CMDCMP) )
    {
        //
        // This will always return a multiple of four.
        //
        ui32SpaceInFifo =  am_hal_iom_fifo_empty_slots(ui32Module);

        if ( ui32NumBytes <= ui32SpaceInFifo )
        {
            //
            // If the entire message will fit in the fifo, prepare to copy
            // everything.
            //
            ui32TransferSize = ui32NumBytes;
        }
        else
        {
            //
            // If only a portion of the message will fit in the fifo, prepare
            // to copy the largest number of 4-byte blocks possible.
            //
            ui32TransferSize = ui32SpaceInFifo & ~(0x3);
        }

        //
        // Write this chunk to the fifo.
        //
        am_hal_iom_fifo_write(ui32Module, pui32Data, ui32TransferSize);

        //
        // Update the data pointer and bytes-left count.
        //
        ui32NumBytes -= ui32TransferSize;
        pui32Data += ui32TransferSize >> 2;
    }

    //
    // Make sure CMDCMP was raised with standard timeout
    //
    waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                 AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                 AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

    if (waitStatus != 1)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
    }
    else
    {
        g_iom_error_status[ui32Module] = ui32Status = internal_iom_get_int_err(ui32Module, 0);
    }

    //
    // Re-enable IOM interrupts.
    //
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;

    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform simple SPI read operations (without queuing).
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs simple SPI read operations. The caller is
//! responsible for ensuring that the receive buffer is large enough to hold
//! the requested amount of data.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_read_nq(uint32_t ui32Module, uint32_t ui32ChipSelect,
                       uint32_t *pui32Data, uint32_t ui32NumBytes,
                       uint32_t ui32Options)
{
    uint32_t ui32BytesInFifo;
    uint32_t ui32IntConfig;
    uint32_t bCmdCmp = false;
    am_hal_iom_status_e ui32Status;
    uint32_t waitStatus;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }
    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 4096)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
    ui32IntConfig = AM_REGn(IOMSTR, ui32Module, INTEN);

    //
    // Disable IOM interrupts as we'll be polling
    //
    AM_REGn(IOMSTR, ui32Module, INTEN) = 0;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // If we're on a B0 part, and we're using IOM4, our first byte coule be
    // corrupted, so we need to send a dummy word with chip-select held high to
    // get that first byte out of the way. This is only true for spi reads with
    // OFFSET values.
    //
    // That operation is tricky and detailed, so we'll call a function to do it
    // for us.
    //
    if ( (WORKAROUND_IOM == ui32Module) && !(ui32Options & AM_HAL_IOM_RAW) &&
        isRevB0() )
    {
        am_hal_iom_workaround_word_write(ui32ChipSelect, pui32Data, 0,
                                         ui32Options | AM_HAL_IOM_CS_LOW);

        //
        // The workaround will send our offset for us, so we can run a RAW
        // command after.
        //
        ui32Options |= AM_HAL_IOM_RAW;
        //
        // Wait for the dummy word to go out over the bus.
        //
        // Make sure the command complete has also been raised
        waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                     AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                     AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

        if (waitStatus != 1)
        {
            g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
            //
            // Re-enable IOM interrupts.
            //
            // Clear interrupts
            AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
            AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;
            return ui32Status;
        }

        // Clear CMDCMP status
        AM_BFWn(IOMSTR, ui32Module, INTCLR, CMDCMP, 1);
    }

    am_hal_iom_spi_cmd_run(AM_HAL_IOM_READ, ui32Module, ui32ChipSelect,
                           ui32NumBytes, ui32Options);

    //
    // Start a loop to catch the Rx data.
    //
    while ( ui32NumBytes )
    {
        ui32BytesInFifo =  am_hal_iom_fifo_full_slots(ui32Module);

        if ( ui32BytesInFifo >= ui32NumBytes )
        {
            //
            // If the fifo contains our entire message, just copy the whole
            // thing out.
            //
            am_hal_iom_fifo_read(ui32Module, pui32Data, ui32NumBytes);
            ui32NumBytes = 0;
        }
        else if ( ui32BytesInFifo >= 4 )
        {
            //
            // If the fifo has at least one 32-bit word in it, copy whole
            // words out.
            //
            am_hal_iom_fifo_read(ui32Module, pui32Data, ui32BytesInFifo & ~0x3);
            ui32NumBytes -= ui32BytesInFifo & ~0x3;
            pui32Data += ui32BytesInFifo >> 2;
        }
        if ( bCmdCmp == true )
        {
            //
            // No more data expected. Get out of the loop
            //
            break;
        }

        bCmdCmp = AM_BFRn(IOMSTR, ui32Module, INTSTAT, CMDCMP);
    }

    //
    // Make sure CMDCMP was raised,
    //
    waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                 AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                 AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

    if (waitStatus != 1)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
    }
    else
    {
        g_iom_error_status[ui32Module] = ui32Status = internal_iom_get_int_err(ui32Module, 0);
    }

    //
    // Re-enable IOM interrupts. Make sure CMDCMP is cleared
    //
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;

    return ui32Status;

}

//*****************************************************************************
//
//! @brief Perform a simple full-duplex operation to the SPI interface (without queuing)
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param pui32Data - Pointer to the bytes that will be received.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs SPI full-duplex operation to a selected SPI device.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32TxData array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui32TxData array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_fullduplex_nq(uint32_t ui32Module, uint32_t ui32ChipSelect,
                             uint32_t *pui32TxData, uint32_t *pui32RxData,
                             uint32_t ui32NumBytes, uint32_t ui32Options)
{
    uint32_t ui32TransferSize;
    uint32_t ui32SpaceInFifo;
    uint32_t bCmdCmp = false;
    uint32_t ui32IntConfig;
    uint32_t ui32MaxFifoSize;
    am_hal_iom_status_e ui32Status;
    uint32_t waitStatus;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 4096)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Full-Duplex operation is only supported for Apollo2 B2 Silicon.
    //
    if (!isRevB2())
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_OPER;
        return ui32Status;
    }

    //
    // Put the IOM into Full-Duplex mode.
    //
    AM_REGn(IOMSTR, ui32Module, CFG) |= AM_REG_IOMSTR_CFG_FULLDUP_FULLDUP;

    ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, ui32Module, CFG, FULLDUP)) ?
                       AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);
    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
    ui32IntConfig = AM_REGn(IOMSTR, ui32Module, INTEN);
    AM_REGn(IOMSTR, ui32Module, INTEN) = 0;
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // Figure out how many bytes we can write to the FIFO immediately.
    //
    ui32TransferSize = (ui32NumBytes <= ui32MaxFifoSize ? ui32NumBytes :
                          ui32MaxFifoSize);
    //
    // write up to the maximum FIFO size into the fifo.
    //
    am_hal_iom_fifo_write(ui32Module, pui32TxData, ui32TransferSize);

    //
    // Start the write on the bus.
    //
    am_hal_iom_spi_cmd_run(AM_HAL_IOM_WRITE, ui32Module, ui32ChipSelect,
                           ui32NumBytes, ui32Options);

    //
    // Update the pointer and data counter.
    //
    pui32TxData += ui32TransferSize >> 2;

    //
    // Keep looping until we're out of bytes to receive or command complete (error).
    //
    while ( ui32NumBytes )
    {
        //
        // Wait for FIFO to empty.
        //
        while (am_hal_iom_fifo_full_slots(ui32Module) > 0);

        am_hal_iom_fifo_read(ui32Module, pui32RxData, ui32TransferSize);
        ui32NumBytes -= ui32TransferSize;
        pui32RxData += ui32TransferSize >> 2;

        //
        // Get the number of bytes that can be written (always a multiple of 4).
        //
        ui32SpaceInFifo =  am_hal_iom_fifo_empty_slots(ui32Module);

        if ( ui32NumBytes <= ui32SpaceInFifo )
        {
            //
            // If the entire message will fit in the fifo, prepare to copy
            // everything.
            //
            ui32TransferSize = ui32NumBytes;
        }
        else
        {
            //
            // If only a portion of the message will fit in the fifo, prepare
            // to copy the largest number of 4-byte blocks possible.
            //
            ui32TransferSize = ui32SpaceInFifo & ~(0x3);
        }

        //
        // Write this chunk to the fifo.
        //
        am_hal_iom_fifo_write(ui32Module, pui32TxData, ui32TransferSize);

        //
        // Update the data pointer and bytes-left count.
        //
        pui32TxData += ui32TransferSize >> 2;

        //
        // Check for Command Complete condition.
        if ( bCmdCmp == true )
        {
            //
            // No more data expected. Get out of the loop
            //
            break;
        }

        bCmdCmp = AM_BFRn(IOMSTR, ui32Module, INTSTAT, CMDCMP);

    }

    //
    // Make sure CMDCMP was raised with standard timeout
    //
    waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                 AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                 AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

    if (waitStatus != 1)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
    }
    else
    {
        g_iom_error_status[ui32Module] = ui32Status = internal_iom_get_int_err(ui32Module, 0);
    }

    //
    // Re-enable IOM interrupts.
    //
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;

    //
    // Take the IOM out of Full-Duplex mode.
    //
    AM_REGn(IOMSTR, ui32Module, CFG) &= ~AM_REG_IOMSTR_CFG_FULLDUP_FULLDUP;

    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a non-blocking write to the SPI interface.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//! @param pfnCallback - Function to call when the transaction completes.
//!
//! This function performs SPI writes to the selected SPI device.
//!
//! This function call is a non-blocking implementation. It will write as much
//! data to the FIFO as possible immediately, store a pointer to the remaining
//! data, start the transfer on the bus, and then immediately return. The
//! caller will need to make sure that \e am_hal_iom_int_service() is called
//! for IOM FIFO interrupt events and "command complete" interrupt events. The
//! \e am_hal_iom_int_service() function will refill the FIFO as necessary and
//! call the \e pfnCallback function when the transaction is finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution. Note that
//! successful execution for non-blocking call only means the transaction was
//! successfully initiated. The status of the transaction is not known till the
//! callback is called on completion
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_write_nb(uint32_t ui32Module, uint32_t ui32ChipSelect,
                        uint32_t *pui32Data, uint32_t ui32NumBytes,
                        uint32_t ui32Options,
                        am_hal_iom_callback_t pfnCallback)
{
    am_hal_iom_status_e ui32Status;
    uint32_t ui32TransferSize;
    uint32_t ui32MaxFifoSize;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status for non-blocking transfer
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }
    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 4096)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, ui32Module, CFG, FULLDUP)) ?
                      AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);

    //
    // Need to mark IOM busy to avoid another transaction to be scheduled.
    // This is to take care of a race condition in Queue mode, where the IDLE
    // set is not a guarantee that the CMDCMP has been received
    //
    g_bIomBusy[ui32Module] = true;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // Check to see if we need to do the workaround.
    //
    if ( WORKAROUND_IOM == ui32Module && isRevB0() )
    {
        //
        // Figure out how many bytes we can write to the FIFO immediately,
        // accounting for the extra word from the workaround.
        //
        ui32TransferSize = (ui32NumBytes <= (ui32MaxFifoSize - 4) ?  ui32NumBytes :
                            (ui32MaxFifoSize - 4));

        //
        // Prepare the global IOM buffer structure.
        //
        g_psIOMBuffers[ui32Module].ui32State = BUFFER_SENDING;
        g_psIOMBuffers[ui32Module].pui32Data = pui32Data + (ui32TransferSize / 4);
        g_psIOMBuffers[ui32Module].ui32BytesLeft = ui32NumBytes - ui32TransferSize;
        g_psIOMBuffers[ui32Module].pfnCallback = pfnCallback;
        g_psIOMBuffers[ui32Module].ui32Options = ui32Options;

        //
        // Start the write on the bus using the workaround. This includes both
        // the command write and the first fifo write, so we won't need to do
        // either of those things manually.
        //
        am_hal_iom_workaround_word_write(ui32ChipSelect, pui32Data,
                                         ui32NumBytes, ui32Options);
    }
    else
    {
        //
        // Figure out how many bytes we can write to the FIFO immediately.
        //
        ui32TransferSize = (ui32NumBytes <= ui32MaxFifoSize ? ui32NumBytes :
                            ui32MaxFifoSize);

        if ( am_hal_iom_fifo_write(ui32Module, pui32Data, ui32TransferSize) > 0 )
        {
            //
            // Prepare the global IOM buffer structure.
            //
            g_psIOMBuffers[ui32Module].ui32State = BUFFER_SENDING;
            g_psIOMBuffers[ui32Module].pui32Data = pui32Data;
            g_psIOMBuffers[ui32Module].ui32BytesLeft = ui32NumBytes;
            g_psIOMBuffers[ui32Module].pfnCallback = pfnCallback;
            g_psIOMBuffers[ui32Module].ui32Options = ui32Options;

            //
            // Update the pointer and the byte counter based on the portion of
            // the transfer we just sent to the fifo.
            //
            g_psIOMBuffers[ui32Module].ui32BytesLeft -= ui32TransferSize;
            g_psIOMBuffers[ui32Module].pui32Data += (ui32TransferSize / 4);

            //
            // Start the write on the bus.
            //
            am_hal_iom_spi_cmd_run(AM_HAL_IOM_WRITE, ui32Module, ui32ChipSelect,
                                   ui32NumBytes, ui32Options);
        }
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a non-blocking SPI read.
//!
//! @param ui32Module - Module number for the IOM.
//! @param ui32ChipSelect - Chip select number of the target device.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional SPI transfer options.
//! @param pfnCallback - Function to call when the transaction completes.
//!
//! This function performs SPI reads to a selected SPI device.
//!
//! This function call is a non-blocking implementation. It will start the SPI
//! transaction on the bus and store a pointer for the destination for the read
//! data, but it will not wait for the SPI transaction to finish.  The caller
//! will need to make sure that \e am_hal_iom_int_service() is called for IOM
//! FIFO interrupt events and "command complete" interrupt events. The \e
//! am_hal_iom_int_service() function will empty the FIFO as necessary,
//! transfer the data to the \e pui32Data buffer, and call the \e pfnCallback
//! function when the transaction is finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution. Note that
//! successful execution for non-blocking call only means the transaction was
//! successfully initiated. The status of the transaction is not known till the
//! callback is called on completion
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_spi_read_nb(uint32_t ui32Module, uint32_t ui32ChipSelect,
                       uint32_t *pui32Data, uint32_t ui32NumBytes,
                       uint32_t ui32Options,
                       am_hal_iom_callback_t pfnCallback)
{
    am_hal_iom_status_e ui32Status;
    uint32_t ui32IntConfig;
    uint32_t waitStatus;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }
    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 4096)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }


    //
    // Need to mark IOM busy to avoid another transaction to be scheduled.
    // This is to take care of a race condition in Queue mode, where the IDLE
    // set is not a guarantee that the CMDCMP has been received
    //
    g_bIomBusy[ui32Module] = true;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // If we're on a B0 part, and we're using IOM4, our first byte could be
    // corrupted, so we need to send a dummy word with chip-select held high to
    // get that first byte out of the way. This is only true for spi reads with
    // OFFSET values.
    //
    // That operation is tricky and detailed, so we'll call a function to do it
    // for us.
    //
    if ( (WORKAROUND_IOM == ui32Module) && !(ui32Options & AM_HAL_IOM_RAW) &&
        isRevB0() )
    {
        //
        // We might mess up the interrupt handler behavior if we allow this
        // polled transaction to complete with interrupts enabled. We'll
        // briefly turn them off here.
        //
        ui32IntConfig = AM_REGn(IOMSTR, 4, INTEN);
        AM_REGn(IOMSTR, 4, INTEN) = 0;

        am_hal_iom_workaround_word_write(ui32ChipSelect, pui32Data,
                                         0, ui32Options | AM_HAL_IOM_CS_LOW);

        //
        // The workaround will send our offset for us, so we can run a RAW
        // command after.
        //
        ui32Options |= AM_HAL_IOM_RAW;

        //
        // Wait for the dummy word to go out over the bus.
        //
        // Make sure the command complete has also been raised
        waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                     AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                     AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

        if (waitStatus != 1)
        {
            g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
            return ui32Status;
        }

        //
        // Re-mark IOM as busy
        //

        g_bIomBusy[ui32Module] = true;

        //
        // Re-enable IOM interrupts. Make sure CMDCMP is cleared
        //
        AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
        AM_REGn(IOMSTR, 4, INTEN) = ui32IntConfig;
    }

    //
    // Prepare the global IOM buffer structure.
    //
    g_psIOMBuffers[ui32Module].ui32State = BUFFER_RECEIVING;
    g_psIOMBuffers[ui32Module].pui32Data = pui32Data;
    g_psIOMBuffers[ui32Module].ui32BytesLeft = ui32NumBytes;
    g_psIOMBuffers[ui32Module].pfnCallback = pfnCallback;
    g_psIOMBuffers[ui32Module].ui32Options = ui32Options;

    //
    // Start the read transaction on the bus.
    //
    am_hal_iom_spi_cmd_run(AM_HAL_IOM_READ, ui32Module, ui32ChipSelect,
                           ui32NumBytes, ui32Options);

    return ui32Status;
}

static uint32_t
internal_am_hal_iom_spi_cmd_construct(uint32_t ui32Operation,
                                      uint32_t ui32ChipSelect,
                                      uint32_t ui32NumBytes,
                                      uint32_t ui32Options)
{
    uint32_t ui32Command;
    //
    // Start building the command from the operation parameter.
    //
    ui32Command = ui32Operation;

    //
    // Set the transfer length (the length field is split, so this requires
    // some swizzling).
    //
    ui32Command |= ((ui32NumBytes & 0xF00) << 15);
    ui32Command |= (ui32NumBytes & 0xFF);

    //
    // Set the chip select number.
    //
    ui32Command |= ((ui32ChipSelect << 16) & 0x00070000);

    //
    // Finally, OR in the rest of the options. This mask should make sure that
    // erroneous option values won't interfere with the other transfer
    // parameters.
    //
    ui32Command |= ui32Options & 0x5C00FF00;
    return ui32Command;
}
//*****************************************************************************
//
//! @brief Runs a SPI "command" through the IO master.
//!
//! @param ui32Operation - SPI action to be performed.
//!
//! @param psDevice - Structure containing information about the slave device.
//!
//! @param ui32NumBytes - Number of bytes to move (transmit or receive) with
//! this command.
//!
//! @param ui32Options - Additional SPI options to apply to this command.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_spi_cmd_run(uint32_t ui32Operation, uint32_t ui32Module,
                       uint32_t ui32ChipSelect, uint32_t ui32NumBytes,
                       uint32_t ui32Options)
{
    uint32_t ui32Command;

    am_hal_debug_assert_msg(ui32NumBytes > 0,
                            "Trying to do a 0 byte transaction");
    ui32Command = internal_am_hal_iom_spi_cmd_construct(ui32Operation,
                        ui32ChipSelect, ui32NumBytes, ui32Options);


    //
    // Write the complete command word to the IOM command register.
    //
    AM_REGn(IOMSTR, ui32Module, CMD) = ui32Command;
}

//*****************************************************************************
//
//! @brief Perform a simple write to the I2C interface (without queuing)
//!
//! @param ui32Module - Module number for the IOM.
//! @param ui32BusAddress - I2C address of the target device.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional I2C transfer options.
//!
//! This function performs I2C writes to a selected I2C device.
//!
//! This function call is a blocking implementation. It will write as much
//! data to the FIFO as possible immediately, and then refill the FIFO as data
//! is transmiitted.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui32Data array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_write_nq(uint32_t ui32Module, uint32_t ui32BusAddress,
                        uint32_t *pui32Data, uint32_t ui32NumBytes,
                        uint32_t ui32Options)
{
    uint32_t ui32TransferSize;
    uint32_t ui32SpaceInFifo;
    uint32_t ui32IntConfig;
    uint32_t ui32MaxFifoSize;
    am_hal_iom_status_e ui32Status;
    uint32_t waitStatus;
    am_hal_i2c_bit_bang_enum_e i2cBBStatus;

    //
    // Validate parameters
    //
    if ( ui32Module > AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until any earlier transactions have completed.
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Redirect to the bit-bang interface if the module number matches the
    // software I2C module.
    //
    if ( ui32Module == AM_HAL_IOM_I2CBB_MODULE )
    {
        if ( ui32Options & AM_HAL_IOM_RAW )
        {
            i2cBBStatus = am_hal_i2c_bit_bang_send(ui32BusAddress << 1, ui32NumBytes,
                                     (uint8_t *)pui32Data, 0, false,
                                     (ui32Options & AM_HAL_IOM_NO_STOP));
        }
        else
        {
            i2cBBStatus = am_hal_i2c_bit_bang_send(ui32BusAddress << 1, ui32NumBytes,
                                     (uint8_t *)pui32Data,
                                     ((ui32Options & 0xFF00) >> 8),
                                     true,
                                     (ui32Options & AM_HAL_IOM_NO_STOP));
        }

        //
        // Return. convert BB retCode to proper retCode here
        //
        g_iom_error_status[ui32Module] = ui32Status = i2c_bb_errmap[i2cBBStatus];
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 256)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, ui32Module, CFG, FULLDUP)) ?
                      AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);

    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
    ui32IntConfig = AM_REGn(IOMSTR, ui32Module, INTEN);
    AM_REGn(IOMSTR, ui32Module, INTEN) = 0;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // Figure out how many bytes we can write to the FIFO immediately.
    //
    ui32TransferSize = (ui32NumBytes <= ui32MaxFifoSize ? ui32NumBytes :
                        ui32MaxFifoSize);

    am_hal_iom_fifo_write(ui32Module, pui32Data, ui32TransferSize);

    //
    // Start the write on the bus.
    //
    ui32Status = am_hal_iom_i2c_cmd_run(AM_HAL_IOM_WRITE, ui32Module, ui32BusAddress,
                           ui32NumBytes, ui32Options);

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status = ui32Status;
        //
        // Re-enable IOM interrupts.
        //
        // Clear interrupts
        AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
        AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;
        return ui32Status;
    }
    //
    // Update the pointer and data counter.
    //
    ui32NumBytes -= ui32TransferSize;
    pui32Data += ui32TransferSize >> 2;

    //
    // Keep looping until we're out of bytes to send or command complete (error).
    //
    while ( ui32NumBytes && !AM_BFRn(IOMSTR, ui32Module, INTSTAT, CMDCMP) )
    {
        //
        // This will always return a multiple of four.
        //
        ui32SpaceInFifo =  am_hal_iom_fifo_empty_slots(ui32Module);

        if ( ui32NumBytes <= ui32SpaceInFifo )
        {
            //
            // If the entire message will fit in the fifo, prepare to copy
            // everything.
            //
            ui32TransferSize = ui32NumBytes;
        }
        else
        {
            //
            // If only a portion of the message will fit in the fifo, prepare
            // to copy the largest number of 4-byte blocks possible.
            //
            ui32TransferSize = ui32SpaceInFifo;
        }

        //
        // Write this chunk to the fifo.
        //
        am_hal_iom_fifo_write(ui32Module, pui32Data, ui32TransferSize);

        //
        // Update the data pointer and bytes-left count.
        //
        ui32NumBytes -= ui32TransferSize;
        pui32Data += ui32TransferSize >> 2;
    }

    //
    // Make sure CMDCMP was raised,
    //
    waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                 AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                 AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

    if (waitStatus != 1)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
    }
    else
    {
        g_iom_error_status[ui32Module] = ui32Status = internal_iom_get_int_err(ui32Module, 0);
    }

    //
    // Re-enable IOM interrupts.
    //
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform simple I2C read operations (without queuing).
//!
//! @param ui32Module - Module number for the IOM.
//! @param ui32BusAddress - I2C address of the target device.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional I2C transfer options.
//!
//! This function performs an I2C read to a selected I2C device.
//!
//! This function call is a blocking implementation. It will read as much
//! data from the FIFO as possible immediately, and then re-read the FIFO as more
//! data is available.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_read_nq(uint32_t ui32Module, uint32_t ui32BusAddress,
                       uint32_t *pui32Data, uint32_t ui32NumBytes,
                       uint32_t ui32Options)
{
    uint32_t ui32BytesInFifo;
    uint32_t ui32IntConfig;
    uint32_t bCmdCmp = false;
    am_hal_iom_status_e ui32Status;
    uint32_t waitStatus;
    am_hal_i2c_bit_bang_enum_e i2cBBStatus;

    //
    // Validate parameters
    //
    if ( ui32Module > AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Redirect to the bit-bang interface if the module number matches the
    // software I2C module.
    //
    if ( ui32Module == AM_HAL_IOM_I2CBB_MODULE )
    {
        if ( ui32Options & AM_HAL_IOM_RAW )
        {
            i2cBBStatus = am_hal_i2c_bit_bang_receive((ui32BusAddress << 1) | 1, ui32NumBytes,
                                        (uint8_t *)pui32Data, 0, false,
                                        (ui32Options & AM_HAL_IOM_NO_STOP));
        }
        else
        {
            i2cBBStatus = am_hal_i2c_bit_bang_receive((ui32BusAddress << 1) | 1, ui32NumBytes,
                                        (uint8_t *)pui32Data,
                                        ((ui32Options & 0xFF00) >> 8),
                                        true,
                                        (ui32Options & AM_HAL_IOM_NO_STOP));
        }

        //
        // Return. convert i2c bb retCode
        //
        g_iom_error_status[ui32Module] = ui32Status = i2c_bb_errmap[i2cBBStatus];
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 256)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
    ui32IntConfig = AM_REGn(IOMSTR, ui32Module, INTEN);
    AM_REGn(IOMSTR, ui32Module, INTEN) = 0;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    ui32Status = am_hal_iom_i2c_cmd_run(AM_HAL_IOM_READ, ui32Module, ui32BusAddress,
                           ui32NumBytes, ui32Options);

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status = ui32Status;
        //
        // Re-enable IOM interrupts.
        //
        // Clear interrupts
        AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
        AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;
        return ui32Status;
    }

    //
    // Start a loop to catch the Rx data.
    //
    while ( ui32NumBytes )
    {
        ui32BytesInFifo =  am_hal_iom_fifo_full_slots(ui32Module);

        if ( ui32BytesInFifo >= ui32NumBytes )
        {
            //
            // If the fifo contains our entire message, just copy the whole
            // thing out.
            //
            am_hal_iom_fifo_read(ui32Module, pui32Data, ui32NumBytes);
            ui32NumBytes = 0;
        }
        else if ( ui32BytesInFifo >= 4 )
        {
            //
            // If the fifo has at least one 32-bit word in it, copy whole
            // words out.
            //
            am_hal_iom_fifo_read(ui32Module, pui32Data, ui32BytesInFifo & ~0x3);

            ui32NumBytes -= ui32BytesInFifo & ~0x3;
            pui32Data += ui32BytesInFifo >> 2;
        }

        if ( bCmdCmp == true )
        {
            // No more data expected - exit out of loop
            break;
        }

        bCmdCmp = AM_BFRn(IOMSTR, ui32Module, INTSTAT, CMDCMP);
    }

    //
    // Make sure CMDCMP was raised,
    //
    waitStatus = am_hal_flash_delay_status_change(ui32StatusTimeout[ui32Module],
                 AM_REG_IOMSTRn(ui32Module) + AM_REG_IOMSTR_INTSTAT_O,
                 AM_REG_IOMSTR_INTEN_CMDCMP_M, AM_REG_IOMSTR_INTEN_CMDCMP_M);

    if (waitStatus != 1)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_TIMEOUT;
    }
    else
    {
        g_iom_error_status[ui32Module] = ui32Status = internal_iom_get_int_err(ui32Module, 0);
    }
    //
    // Re-enable IOM interrupts.
    //
    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOMSTR, ui32Module, INTEN) = ui32IntConfig;
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a simple write to the I2C interface.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32BusAddress - I2C bus address for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional options
//!
//! Performs a write to the I2C interface using the provided parameters.
//!
//! See the "Command Options" section for parameters that may be ORed together
//! and used in the \b ui32Options parameter.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_write(uint32_t ui32Module, uint32_t ui32BusAddress,
                     uint32_t *pui32Data, uint32_t ui32NumBytes,
                     uint32_t ui32Options)
{
    am_hal_iom_status_e ui32Status;
    am_hal_i2c_bit_bang_enum_e i2cBBStatus;
    //
    // Validate parameters
    //
    if ( ui32Module > AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Redirect to the bit-bang interface if the module number matches the
    // software I2C module.
    //
    if ( ui32Module == AM_HAL_IOM_I2CBB_MODULE )
    {
        if ( ui32Options & AM_HAL_IOM_RAW )
        {
            i2cBBStatus = am_hal_i2c_bit_bang_send(ui32BusAddress << 1, ui32NumBytes,
                                     (uint8_t *)pui32Data, 0, false,
                                     (ui32Options & AM_HAL_IOM_NO_STOP));
        }
        else
        {
            i2cBBStatus = am_hal_i2c_bit_bang_send(ui32BusAddress << 1, ui32NumBytes,
                                     (uint8_t *)pui32Data,
                                     ((ui32Options & 0xFF00) >> 8),
                                     true,
                                     (ui32Options & AM_HAL_IOM_NO_STOP));
        }

        //
        // Return. convert i2c bb retCode
        //
        g_iom_error_status[ui32Module] = ui32Status = i2c_bb_errmap[i2cBBStatus];
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 256)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Check to see if queues have been enabled. If they are, we'll actually
    // switch to the queued interface.
    //
    if ( g_psIOMQueue[ui32Module].pui8Data != NULL )
    {
        //
        // If the queue is on, go ahead and add this transaction to the queue.
        //
        ui32Status = am_hal_iom_queue_i2c_write(ui32Module, ui32BusAddress, pui32Data,
                                   ui32NumBytes, ui32Options, 0);

        if (ui32Status == AM_HAL_IOM_SUCCESS)
        {
            //
            // Wait until the transaction actually clears.
            //
            am_hal_iom_queue_flush(ui32Module);
            // g_iom_error_status gets set in the isr handling
            ui32Status = g_iom_error_status[ui32Module];
        }

        //
        // At this point, we've completed the transaction, and we can return.
        //
    }
    else
    {
        //
        // Otherwise, we'll just do a polled transaction.
        //
        ui32Status = am_hal_iom_i2c_write_nq(ui32Module, ui32BusAddress, pui32Data,
                                ui32NumBytes, ui32Options);
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform simple I2C read operations.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32BusAddress - I2C bus address for this transaction.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional I2C transfer options.
//!
//! This function performs simple I2C read operations. The caller is
//! responsible for ensuring that the receive buffer is large enough to hold
//! the requested amount of data. If \e bPolled is true, this function will
//! block until all of the requested data has been received and placed in the
//! user-supplied buffer. Otherwise, the function will execute the I2C read
//! command and return immediately. The user-supplied buffer will be filled
//! with the received I2C data as it comes in over the physical interface, and
//! the "command complete" interrupt bit will become active once the entire
//! message is available.
//!
//! See the "Command Options" section for parameters that may be ORed together
//! and used in the \b ui32Options parameter.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_read(uint32_t ui32Module, uint32_t ui32BusAddress,
                    uint32_t *pui32Data, uint32_t ui32NumBytes,
                    uint32_t ui32Options)
{
    am_hal_iom_status_e ui32Status;
    am_hal_i2c_bit_bang_enum_e i2cBBStatus;
    //
    // Validate parameters
    //
    if ( ui32Module > AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Redirect to the bit-bang interface if the module number matches the
    // software I2C module.
    //
    if ( ui32Module == AM_HAL_IOM_I2CBB_MODULE )
    {
        if ( ui32Options & AM_HAL_IOM_RAW )
        {
            i2cBBStatus = am_hal_i2c_bit_bang_receive((ui32BusAddress << 1) | 1, ui32NumBytes,
                                        (uint8_t *)pui32Data, 0, false,
                                        (ui32Options & AM_HAL_IOM_NO_STOP));
        }
        else
        {
            i2cBBStatus = am_hal_i2c_bit_bang_receive((ui32BusAddress << 1) | 1, ui32NumBytes,
                                        (uint8_t *)pui32Data,
                                        ((ui32Options & 0xFF00) >> 8),
                                        true,
                                        (ui32Options & AM_HAL_IOM_NO_STOP));
        }

        //
        // Return. convert i2c bb retCode
        //
        g_iom_error_status[ui32Module] = ui32Status = i2c_bb_errmap[i2cBBStatus];
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 256)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Check to see if queues have been enabled. If they are, we'll actually
    // switch to the queued interface.
    //
    if ( g_psIOMQueue[ui32Module].pui8Data != NULL )
    {
        //
        // If the queue is on, go ahead and add this transaction to the queue.
        //
        ui32Status = am_hal_iom_queue_i2c_read(ui32Module, ui32BusAddress, pui32Data,
                                  ui32NumBytes, ui32Options, 0);

        if (ui32Status == AM_HAL_IOM_SUCCESS)
        {
            //
            // Wait until the transaction actually clears.
            //
            am_hal_iom_queue_flush(ui32Module);
            // g_iom_error_status gets set in the isr handling
            ui32Status = g_iom_error_status[ui32Module];
        }

        //
        // At this point, we've completed the transaction, and we can return.
        //
    }
    else
    {
        //
        // Otherwise, just perform a polled transaction.
        //
        ui32Status = am_hal_iom_i2c_read_nq(ui32Module, ui32BusAddress, pui32Data,
                               ui32NumBytes, ui32Options);
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a non-blocking write to the I2C interface.
//!
//! @param ui32Module - Module number for the IOM.
//! @param ui32BusAddress - I2C address of the target device.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional I2C transfer options.
//! @param pfnCallback - Function to call when the transaction completes.
//!
//! This function performs I2C writes to a selected I2C device.
//!
//! This function call is a non-blocking implementation. It will write as much
//! data to the FIFO as possible immediately, store a pointer to the remaining
//! data, start the transfer on the bus, and then immediately return. The
//! caller will need to make sure that \e am_hal_iom_int_service() is called
//! for IOM FIFO interrupt events and "command complete" interrupt events. The
//! \e am_hal_iom_int_service() function will refill the FIFO as necessary and
//! call the \e pfnCallback function when the transaction is finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui32Data array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution. Note that
//! successful execution for non-blocking call only means the transaction was
//! successfully initiated. The status of the transaction is not known till the
//! callback is called on completion
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_write_nb(uint32_t ui32Module, uint32_t ui32BusAddress,
                        uint32_t *pui32Data, uint32_t ui32NumBytes,
                        uint32_t ui32Options,
                        am_hal_iom_callback_t pfnCallback)
{
    am_hal_iom_status_e ui32Status;
    uint32_t ui32TransferSize;
    uint32_t ui32MaxFifoSize;
    am_hal_i2c_bit_bang_enum_e i2cBBStatus;

    //
    // Validate parameters
    //
    if ( ui32Module > AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Redirect to the bit-bang interface if the module number matches the
    // software I2C module.
    //
    if ( ui32Module == AM_HAL_IOM_I2CBB_MODULE )
    {
        // Reset the error status for non-blocking transfer
        g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
        if ( ui32Options & AM_HAL_IOM_RAW )
        {
            i2cBBStatus = am_hal_i2c_bit_bang_send(ui32BusAddress << 1, ui32NumBytes,
                                     (uint8_t *)pui32Data, 0, false,
                                     (ui32Options & AM_HAL_IOM_NO_STOP));
        }
        else
        {
            i2cBBStatus = am_hal_i2c_bit_bang_send(ui32BusAddress << 1, ui32NumBytes,
                                     (uint8_t *)pui32Data,
                                     ((ui32Options & 0xFF00) >> 8),
                                     true,
                                     (ui32Options & AM_HAL_IOM_NO_STOP));
        }

        //
        // Return. convert i2c bb retCode
        //
        g_iom_error_status[ui32Module] = ui32Status = i2c_bb_errmap[i2cBBStatus];
        //
        // The I2C bit-bang interface is actually a blocking transfer, and it
        // doesn't trigger the interrupt handler, so we have to call the
        // callback function manually.
        //
        if ( pfnCallback )
        {
            pfnCallback();
        }
        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 256)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, ui32Module, CFG, FULLDUP)) ?
                       AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);

    //
    // Figure out how many bytes we can write to the FIFO immediately.
    //
    ui32TransferSize = (ui32NumBytes <= ui32MaxFifoSize ? ui32NumBytes :
                        ui32MaxFifoSize);

    // Need to mark IOM busy to avoid another transaction to be scheduled.
    // This is to take care of a race condition in Queue mode, where the IDLE
    // set is not a guarantee that the CMDCMP has been received
    g_bIomBusy[ui32Module] = true;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    if ( am_hal_iom_fifo_write(ui32Module, pui32Data, ui32TransferSize) > 0 )
    {
        //
        // Prepare the global IOM buffer structure.
        //
        g_psIOMBuffers[ui32Module].ui32State = BUFFER_SENDING;
        g_psIOMBuffers[ui32Module].pui32Data = pui32Data;
        g_psIOMBuffers[ui32Module].ui32BytesLeft = ui32NumBytes;
        g_psIOMBuffers[ui32Module].pfnCallback = pfnCallback;

        //
        // Update the pointer and the byte counter based on the portion of the
        // transfer we just sent to the fifo.
        //
        g_psIOMBuffers[ui32Module].ui32BytesLeft -= ui32TransferSize;
        g_psIOMBuffers[ui32Module].pui32Data += (ui32TransferSize / 4);

        //
        // Start the write on the bus.
        //
        ui32Status = am_hal_iom_i2c_cmd_run(AM_HAL_IOM_WRITE, ui32Module, ui32BusAddress,
                               ui32NumBytes, ui32Options);
        if (ui32Status != AM_HAL_IOM_SUCCESS)
        {
            g_iom_error_status[ui32Module] = ui32Status;
        }
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Perform a non-blocking I2C read.
//!
//! @param ui32Module - Module number for the IOM.
//! @param ui32ChipSelect - I2C address of the target device.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional I2C transfer options.
//! @param pfnCallback - Function to call when the transaction completes.
//!
//! This function performs an I2C read to a selected I2C device.
//!
//! This function call is a non-blocking implementation. It will start the I2C
//! transaction on the bus and store a pointer for the destination for the read
//! data, but it will not wait for the I2C transaction to finish.  The caller
//! will need to make sure that \e am_hal_iom_int_service() is called for IOM
//! FIFO interrupt events and "command complete" interrupt events. The \e
//! am_hal_iom_int_service() function will empty the FIFO as necessary,
//! transfer the data to the \e pui32Data buffer, and call the \e pfnCallback
//! function when the transaction is finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution. Note that
//! successful execution for non-blocking call only means the transaction was
//! successfully initiated. The status of the transaction is not known till the
//! callback is called on completion
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_read_nb(uint32_t ui32Module, uint32_t ui32BusAddress,
                       uint32_t *pui32Data, uint32_t ui32NumBytes,
                       uint32_t ui32Options,
                       am_hal_iom_callback_t pfnCallback)
{
    am_hal_iom_status_e ui32Status;
    am_hal_i2c_bit_bang_enum_e i2cBBStatus;
    //
    // Validate parameters
    //
    if ( ui32Module > AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    //
    // Wait until the bus is idle
    //
    am_hal_iom_poll_complete(ui32Module);

    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if (ui32NumBytes == 0)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Redirect to the bit-bang interface if the module number matches the
    // software I2C module.
    //
    if ( ui32Module == AM_HAL_IOM_I2CBB_MODULE )
    {
        // Reset the error status for non-blocking transfer
        g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
        if ( ui32Options & AM_HAL_IOM_RAW )
        {
            i2cBBStatus = am_hal_i2c_bit_bang_receive((ui32BusAddress << 1) | 1, ui32NumBytes,
                                        (uint8_t *)pui32Data, 0, false,
                                        (ui32Options & AM_HAL_IOM_NO_STOP));
        }
        else
        {
            i2cBBStatus = am_hal_i2c_bit_bang_receive((ui32BusAddress << 1) | 1, ui32NumBytes,
                                        (uint8_t *)pui32Data,
                                        ((ui32Options & 0xFF00) >> 8),
                                        true,
                                        (ui32Options & AM_HAL_IOM_NO_STOP));
        }

        //
        // Return. convert i2c bb retCode
        //
        g_iom_error_status[ui32Module] = ui32Status = i2c_bb_errmap[i2cBBStatus];
        //
        // The I2C bit-bang interface is actually a blocking transfer, and it
        // doesn't trigger the interrupt handler, so we have to call the
        // callback function manually.
        //
        if ( pfnCallback )
        {
            pfnCallback();
        }

        return ui32Status;
    }

    //
    // Make sure the transfer isn't too long for the hardware to support.
    //
    if (ui32NumBytes >= 256)
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    // Need to mark IOM busy to avoid another transaction to be scheduled.
    // This is to take care of a race condition in Queue mode, where the IDLE
    // set is not a guarantee that the CMDCMP has been received
    //
    g_bIomBusy[ui32Module] = true;

    // Clear interrupts
    AM_REGn(IOMSTR, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // Prepare the global IOM buffer structure.
    //
    g_psIOMBuffers[ui32Module].ui32State = BUFFER_RECEIVING;
    g_psIOMBuffers[ui32Module].pui32Data = pui32Data;
    g_psIOMBuffers[ui32Module].ui32BytesLeft = ui32NumBytes;
    g_psIOMBuffers[ui32Module].pfnCallback = pfnCallback;

    //
    // Start the read transaction on the bus.
    //
    ui32Status = am_hal_iom_i2c_cmd_run(AM_HAL_IOM_READ, ui32Module, ui32BusAddress,
                           ui32NumBytes, ui32Options);
    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status;
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Runs a I2C "command" through the IO master.
//!
//! @param ui32Operation - I2C action to be performed. This should either be
//! AM_HAL_IOM_WRITE or AM_HAL_IOM_READ.
//! @param psDevice - Structure containing information about the slave device.
//! @param ui32NumBytes - Number of bytes to move (transmit or receive) with
//! this command.
//! @param ui32Options - Additional I2C options to apply to this command.
//!
//! This function may be used along with am_hal_iom_fifo_write and
//! am_hal_iom_fifo_read to perform more complex I2C reads and writes.
//! This function has additional logic to make sure SCL is high before a new
//! transaction is initiated.
//!
//! @return 0 on success
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_i2c_cmd_run(uint32_t ui32Operation, uint32_t ui32Module,
                       uint32_t ui32BusAddress, uint32_t ui32NumBytes,
                       uint32_t ui32Options)
{
    uint32_t ui32Command;
    am_hal_iom_status_e ui32Status = AM_HAL_IOM_SUCCESS;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    if (ui32NumBytes == 0)
    {
        return AM_HAL_IOM_ERR_INVALID_PARAM;
    }

    //
    // Start building the command from the operation parameter.
    //
    ui32Command = ui32Operation;

    //
    // Set the transfer length.
    //
    ui32Command |= (ui32NumBytes & 0xFF);

    //
    // Set the chip select number.
    //
    ui32Command |= ((ui32BusAddress << 16) & 0x03FF0000);

    //
    // Finally, OR in the rest of the options. This mask should make sure that
    // erroneous option values won't interfere with the other transfer
    // parameters.
    //
    ui32Command |= (ui32Options & 0x5C00FF00);

    //
    // Wait for SCL to be high before initiating a new transaction
    // This is to ensure clock hi time specs are not violated in case slave did
    // clock stretching in previous transaction
    //
    ui32Status = internal_iom_wait_i2c_scl_hi(ui32Module);

    if (ui32Status == AM_HAL_IOM_SUCCESS)
    {
        //
        // Write the complete command word to the IOM command register.
        //
        AM_REGn(IOMSTR, ui32Module, CMD) = ui32Command;
    }
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Sets the repeat count for the next IOM command.
//!
//! @param ui32Module is the IOM module number.
//! @param ui32CmdCount is the number of times the next command should be
//! executed.
//!
//! @note This function is not compatible with the am_hal_iom_spi_read/write()
//! or am_hal_iom_i2c_read/write() functions. Instead, you will need to use the
//! am_hal_iom_fifo_read/write() functions and the am_hal_iom_spi/i2c_cmd_run()
//! functions.
//!
//! Example usage:
//! @code
//!
//! //
//! // Create a buffer and add 3 bytes of data to it.
//! //
//! am_hal_iom_buffer(3) psBuffer;
//! psBuffer.bytes[0] = 's';
//! psBuffer.bytes[1] = 'p';
//! psBuffer.bytes[2] = 'i';
//!
//! //
//! // Send three different bytes to the same SPI register on a remote device.
//! //
//! am_hal_iom_fifo_write(ui32Module, psBuffer.words, 3);
//!
//! am_hal_command_repeat_set(ui32Module, 3);
//!
//! am_hal_iom_spi_cmd_run(AM_HAL_IOM_WRITE, psDevice, 1,
//!                        AM_HAL_IOM_OFFSET(0x5));
//!
//! //
//! // The sequence "0x5, 's', 0x5, 'p', 0x5, 'i'" should be written to the SPI
//! // bus.
//! //
//!
//! @endcode
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_command_repeat_set(uint32_t ui32Module, uint32_t ui32CmdCount)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    AM_REGn(IOMSTR, ui32Module, CMDRPT) = ui32CmdCount;
}

//*****************************************************************************
//
//! @brief Writes data to the IOM FIFO.
//!
//! @param ui32Module - Selects the IOM module to use (zero or one).
//! @param pui32Data - Pointer to an array of the data to be written.
//! @param ui32NumBytes - Number of BYTES to copy into the FIFO.
//!
//! This function copies data from the array \e pui32Data into the IOM FIFO.
//! This prepares the data to eventually be sent as SPI or I2C data by an IOM
//! "command".
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//!
//! @note This function may be used to write partial or complete SPI or I2C
//! messages into the IOM FIFO. When writing partial messages to the FIFO, make
//! sure that the number of bytes written is a multiple of four. Only the last
//! 'part' of a message may consist of a number of bytes that is not a multiple
//! of four. If this rule is not followed, the IOM will not be able to send
//! these bytes correctly.
//!
//! @return Number of bytes actually written to the FIFO.
//
//*****************************************************************************
uint32_t
am_hal_iom_fifo_write(uint32_t ui32Module, uint32_t *pui32Data,
                      uint32_t ui32NumBytes)
{
    uint32_t ui32Index;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    //
    // Make sure we check the number of bytes we're writing to the FIFO.
    //
    am_hal_debug_assert_msg((am_hal_iom_fifo_empty_slots(ui32Module) >= ui32NumBytes),
                            "The fifo couldn't fit the requested number of bytes");

    //
    // Loop over the words in the array until we have the correct number of
    // bytes.
    //
    for ( ui32Index = 0; (4 * ui32Index) < ui32NumBytes; ui32Index++ )
    {
        //
        // Write the word to the FIFO.
        //
        AM_REGn(IOMSTR, ui32Module, FIFO) = pui32Data[ui32Index];
    }

    return ui32NumBytes;
}

//*****************************************************************************
//
//! @brief Reads data from the IOM FIFO.
//!
//! @param ui32Module - Selects the IOM module to use (zero or one).
//! @param pui32Data - Pointer to an array where the FIFO data will be copied.
//! @param ui32NumBytes - Number of bytes to copy into array.
//!
//! This function copies data from the IOM FIFO into the array \e pui32Data.
//! This is how input data from SPI or I2C transactions may be retrieved.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This function will pack the individual bytes from the physical interface
//! into 32-bit words, which are then placed into the \e pui32Data array. Only
//! the first \e ui32NumBytes bytes in this array will contain valid data.
//!
//! @return Number of bytes read from the fifo.
//
//*****************************************************************************
uint32_t
am_hal_iom_fifo_read(uint32_t ui32Module, uint32_t *pui32Data,
                     uint32_t ui32NumBytes)
{
    am_hal_iom_buffer(4) sTempBuffer;
    uint32_t i, j, ui32NumWords, ui32Leftovers;
    uint8_t *pui8Data;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    //
    // Make sure we check the number of bytes we're reading from the FIFO.
    // This doesn't make sense for Full-Duplex operations.
    //
    if ( AM_REG_IOMSTR_CFG_FULLDUP_NORMAL == (AM_REGn(IOMSTR, ui32Module, CFG) & AM_REG_IOMSTR_CFG_FULLDUP_M) )
    {
        am_hal_debug_assert_msg((am_hal_iom_fifo_full_slots(ui32Module) >= ui32NumBytes),
                            "The fifo doesn't contain the requested number of bytes.");
    }

    //
    // Figure out how many whole words we're reading from the fifo, and how
    // many bytes will be left over when we're done.
    //
    ui32NumWords = ui32NumBytes / 4;
    ui32Leftovers = ui32NumBytes - (ui32NumWords * 4);

    //
    // Copy out as many full words as we can.
    //
    for ( i = 0; i < ui32NumWords; i++ )
    {
        //
        // Copy data out of the FIFO, one word at a time.
        //
        pui32Data[i] = AM_REGn(IOMSTR, ui32Module, FIFO);
    }

    //
    // If there were leftovers, we'll copy them carefully. Pull the last word
    // from the fifo (there should only be one) into a temporary buffer. Also,
    // create an 8-bit pointer to help us copy the remaining bytes one at a
    // time.
    //
    // Note: If the data buffer we were given was truly a word pointer like the
    // definition requests, we wouldn't need to do this. It's possible to call
    // this function with a re-cast or packed pointer instead though. If that
    // happens, we want to be careful not to overwrite any data that might be
    // sitting just past the end of the destination array.
    //
    if ( ui32Leftovers )
    {
        sTempBuffer.words[0] = AM_REGn(IOMSTR, ui32Module, FIFO);
        pui8Data = (uint8_t *) (&pui32Data[i]);

        //
        // If we had leftover bytes, copy them out one byte at a time.
        //
        for ( j = 0; j < ui32Leftovers; j++ )
        {
            pui8Data[j] = sTempBuffer.bytes[j];
        }
    }

    return ui32NumBytes;
}

//*****************************************************************************
//
//! @brief Check amount of empty space in the IOM fifo.
//!
//! @param ui32Module - Module number of the IOM whose fifo should be checked.
//!
//! Returns the number of bytes that could be written to the IOM fifo without
//! causing an overflow.
//!
//! @return Amount of space available in the fifo (in bytes).
//
//*****************************************************************************
uint8_t
am_hal_iom_fifo_empty_slots(uint32_t ui32Module)
{
    uint32_t ui32MaxFifoSize;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    ui32MaxFifoSize = ((0 == AM_BFRn(IOMSTR, ui32Module, CFG, FULLDUP)) ? AM_HAL_IOM_MAX_FIFO_SIZE : AM_HAL_IOM_MAX_FIFO_SIZE / 2);

    //
    // Calculate the FIFO Remaining from the FIFO size. This will be different
    // depending on whether the IOM is configured for half-duplex or
    // full-duplex.
    //
    return (ui32MaxFifoSize - AM_BFRn(IOMSTR, ui32Module, FIFOPTR, FIFOSIZ)) & (~0x3);
}

//*****************************************************************************
//
//! @brief Check to see how much data is in the IOM fifo.
//!
//! @param ui32Module - Module number of the IOM whose fifo should be checked.
//!
//! Returns the number of bytes of data that are currently in the IOM fifo.
//!
//! @return Number of bytes in the fifo.
//
//*****************************************************************************
uint8_t
am_hal_iom_fifo_full_slots(uint32_t ui32Module)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    return AM_BFRn(IOMSTR, ui32Module, FIFOPTR, FIFOSIZ);
}

//*****************************************************************************
//
//! @brief Wait for the current IOM command to complete.
//!
//! @param ui32Module - The module number of the IOM to use.
//!
//! This function polls until the IOM bus becomes idle.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_poll_complete(uint32_t ui32Module)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    //
    // Poll on the IDLE bit in the status register.
    //
    while ( g_bIomBusy[ui32Module] );
}

//*****************************************************************************
//
//! @brief Returns the contents of the IOM status register.
//!
//! @param ui32Module IOM instance to check the status of.
//!
//! This function is just a wrapper around the IOM status register.
//!
//! @return 32-bit contents of IOM status register.
//
//*****************************************************************************
uint32_t
am_hal_iom_status_get(uint32_t ui32Module)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    return AM_REGn(IOMSTR, ui32Module, STATUS);
}

//*****************************************************************************
//
//! @brief Returns current error state of the IOM.
//!
//! @param ui32Module IOM instance to check the status of.
//!
//! This function returns status indicating whether the IOM has incurred any
//! errors or not for previous operation.
//! This function can be called when the callback is invoked to determine the
//! status of the transaction just completed.
//! This function can also be called after a blocking call, though it would
//! return the same status as returned from the call itself
//! This function should not be called for an ongoing transaction, and the
//! result of such operation is indeterministic
//!
//! @return AM_HAL_IOM_SUCCESS if all is well.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_error_status_get(uint32_t ui32Module)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        //
        // AM_HAL_IOM_ERR_INVALID_MODULE is defined as an unused interrupt bit.
        //
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }

    return (g_iom_error_status[ui32Module]);
}

//*****************************************************************************
//
//! @brief Service interrupts from the IOM.
//!
//! @param ui32Status is the IOM interrupt status as returned from
//! am_hal_iom_int_status_get()
//!
//! This function performs the necessary operations to facilitate non-blocking
//! IOM writes and reads.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_iom_int_service(uint32_t ui32Module, uint32_t ui32Status)
{
    am_hal_iom_nb_buffer *psBuffer;
    uint32_t ui32NumBytes;
    uint32_t ui32SpaceInFifo;
    uint32_t thresh;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }
    //
    // Find the buffer information for the chosen IOM module.
    //
    psBuffer = &g_psIOMBuffers[ui32Module];

    // Keep accumulating any error indications
    // This is to account for the case if the error indication comes before CMDCMP
    g_iom_error_status[ui32Module] |= ui32Status;
    //
    // Figure out what type of interrupt this was.
    //
    if ( ui32Status & AM_HAL_IOM_INT_CMDCMP )
    {
        //
        // Need to mark IOM Free
        //
        g_bIomBusy[ui32Module] = false;

        //
        // If we're not in the middle of a non-blocking call right now, there's
        // nothing for this routine to do.
        //
        if ( psBuffer->ui32State == BUFFER_IDLE )
        {
            return;
        }

        //
        // If a command just completed, we need to transfer all available data.
        //
        if ( psBuffer->ui32State == BUFFER_RECEIVING )
        {
            //
            // If we were receiving, we need to copy any remaining data out of
            // the IOM FIFO before calling the callback.
            //
            ui32NumBytes = am_hal_iom_fifo_full_slots(ui32Module);
            am_hal_iom_fifo_read(ui32Module, psBuffer->pui32Data, ui32NumBytes);
        }

        //
        // A command complete event also means that we've already transferred
        // all of the data we need, so we can mark the data buffer as IDLE.
        //
        psBuffer->ui32State = BUFFER_IDLE;

        g_iom_error_status[ui32Module] = internal_iom_get_int_err(ui32Module, g_iom_error_status[ui32Module]);
        //
        // If we have a callback, call it now.
        //
        if ( psBuffer->pfnCallback )
        {
            psBuffer->pfnCallback();
        }
    }
    else if ( ui32Status & AM_HAL_IOM_INT_THR )
    {
        //
        // If we're not in the middle of a non-blocking call right now, there's
        // nothing for this routine to do.
        //
        if ( psBuffer->ui32State == BUFFER_IDLE )
        {
            return;
        }
        //
        // If we received a threshold event in the middle of a command, we need
        // to transfer data.
        //
        if ( psBuffer->ui32State == BUFFER_SENDING )
        {
            thresh = AM_BFRn(IOMSTR, ui32Module, FIFOTHR, FIFOWTHR);
            do
            {
                ui32SpaceInFifo = am_hal_iom_fifo_empty_slots(ui32Module);

                //
                // Figure out how much data we can send.
                //
                if ( psBuffer->ui32BytesLeft <= ui32SpaceInFifo )
                {
                    //
                    // If the whole transfer will fit in the fifo, send it all.
                    //
                    ui32NumBytes = psBuffer->ui32BytesLeft;
                }
                else
                {
                    //
                    // If the transfer won't fit in the fifo completely, send as
                    // much as we can (rounded down to a multiple of four bytes).
                    //
                    ui32NumBytes = ui32SpaceInFifo;
                }

                //
                // Perform the transfer.
                //
                am_hal_iom_fifo_write(ui32Module, psBuffer->pui32Data, ui32NumBytes);

                // Clear any spurious THR interrupt that might have got raised
                // while we were adding data to FIFO
                AM_BFWn(IOMSTR, ui32Module, INTCLR, THR, 1);
                //
                // Update the pointer and the byte counter.
                //
                psBuffer->ui32BytesLeft -= ui32NumBytes;
                psBuffer->pui32Data += (ui32NumBytes / 4);

                if ( 0 == psBuffer->ui32BytesLeft )
                {
                    //
                    // Done with this transaction
                    //
                    break;
                }
            } while ( am_hal_iom_fifo_full_slots(ui32Module) <= thresh );
        }
        else
        {
            thresh = AM_BFRn(IOMSTR, ui32Module, FIFOTHR, FIFORTHR);
            while ( (ui32NumBytes = am_hal_iom_fifo_full_slots(ui32Module)) >= thresh )
            {
                //
                // If we get here, we're in the middle of a read. Transfer as much
                // data as possible out of the FIFO and into our buffer.
                //
                if ( ui32NumBytes == psBuffer->ui32BytesLeft )
                {
                    //
                    // If the fifo contains our entire message, just copy the whole
                    // thing out.
                    //
                    am_hal_iom_fifo_read(ui32Module, psBuffer->pui32Data,
                                         psBuffer->ui32BytesLeft);

                    break;
                }
                else if ( ui32NumBytes >= 4 )
                {
                    //
                    // If the fifo has at least one 32-bit word in it, copy out the
                    // biggest block we can.
                    //
                    ui32NumBytes = (ui32NumBytes & (~0x3));

                    am_hal_iom_fifo_read(ui32Module, psBuffer->pui32Data, ui32NumBytes);

                    //
                    // Update the pointer and the byte counter.
                    //
                    psBuffer->ui32BytesLeft -= ui32NumBytes;
                    psBuffer->pui32Data += (ui32NumBytes / 4);

                    // Clear any spurious THR interrupt that might have got raised
                    // while we were reading the data from FIFO
                    AM_BFWn(IOMSTR, ui32Module, INTCLR, THR, 1);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! @brief Initialize the IOM queue system.
//!
//! @param ui32Module - IOM module to be initialized for queue transfers.
//! @param psQueueMemory - Memory to be used for queueing IOM transfers.
//! @param ui32QueueMemSize - Size of the queue memory.
//!
//! This function prepares the selected IOM interface for use with the IOM
//! queue system. The IOM queue system allows the caller to start multiple IOM
//! transfers in a non-blocking way. In order to do this, the HAL requires some
//! amount of memory dedicated to keeping track of IOM transactions before they
//! can be sent to the hardware registers. This function tells the HAL what
//! memory it should use for this purpose. For more information on the IOM
//! queue interface, please see the documentation for
//! am_hal_iom_queue_spi_write().
//!
//! @note This function only needs to be called once (per module), but it must
//! be called before any other am_hal_iom_queue function.
//!
//! @note Each IOM module will need its own working space. If you intend to use
//! the queueing mechanism with more than one IOM module, you will need to
//! provide separate queue memory for each module.
//!
//! Example usage:
//!
//! @code
//!
//! //
//! // Declare an array to be used for IOM queue transactions. This array will
//! // be big enough to handle 32 IOM transactions.
//! //
//! am_hal_iom_queue_entry_t g_psQueueMemory[32];
//!
//! //
//! // Attach the IOM0 queue system to the memory we just allocated.
//! //
//! am_hal_iom_queue_init(0, g_psQueueMemory, sizeof(g_psQueueMemory));
//!
//! @endcode
//
//*****************************************************************************
void
am_hal_iom_queue_init(uint32_t ui32Module, am_hal_iom_queue_entry_t *psQueueMemory,
                      uint32_t ui32QueueMemSize)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    am_hal_queue_init(&g_psIOMQueue[ui32Module], psQueueMemory,
                      sizeof(am_hal_iom_queue_entry_t), ui32QueueMemSize);
}

//*****************************************************************************
//
//! @brief Check to see how many transactions are in the queue.
//!
//! @param ui32Module Module number for the queue to check
//!
//! This function will check to see how many transactions are in the IOM queue
//! for the selected IOM module.
//!
//! @return Number of transactions in the queue.
//
//*****************************************************************************
uint32_t
am_hal_iom_queue_length_get(uint32_t ui32Module)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    return am_hal_queue_data_left(&g_psIOMQueue[ui32Module]);
}

//*****************************************************************************
//
//! @brief Executes the next operation in the IOM queue.
//!
//! @param ui32ModuleNum - Module number for the IOM to use.
//!
//! This function checks the IOM queue to see if there are any remaining
//! transactions. If so, it will start the next available transaction in a
//! non-blocking way.
//!
//! @note This function is called automatically by am_hal_iom_queue_service().
//! You should not call this function standalone in a normal application.
//
//*****************************************************************************
void
am_hal_iom_queue_start_next_msg(uint32_t ui32Module)
{
    am_hal_iom_queue_entry_t sIOMTransaction = {0};

    uint32_t ui32ChipSelect;
    uint32_t *pui32Data;
    uint32_t ui32NumBytes;
    uint32_t ui32Options;
    am_hal_iom_callback_t pfnCallback;

    am_hal_iom_status_e ui32Status = AM_HAL_IOM_SUCCESS;
    uint32_t ui32Critical;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    //
    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // Try to get the next IOM operation from the queue.
    //
    if ( am_hal_queue_item_get(&g_psIOMQueue[ui32Module], &sIOMTransaction, 1) )
    {
        //
        // Read the operation parameters
        //
        ui32ChipSelect = sIOMTransaction.ui32ChipSelect;
        pui32Data = sIOMTransaction.pui32Data;
        ui32NumBytes = sIOMTransaction.ui32NumBytes;
        ui32Options = sIOMTransaction.ui32Options;
        pfnCallback = sIOMTransaction.pfnCallback;

        //
        // Figure out if this was a SPI or I2C write or read, and call the
        // appropriate non-blocking function.
        //
        switch ( sIOMTransaction.ui32Operation )
        {
            case AM_HAL_IOM_QUEUE_SPI_WRITE:
                ui32Status = am_hal_iom_spi_write_nb(ui32Module, ui32ChipSelect, pui32Data,
                                        ui32NumBytes, ui32Options, pfnCallback);
                break;

            case AM_HAL_IOM_QUEUE_SPI_READ:
                ui32Status = am_hal_iom_spi_read_nb(ui32Module, ui32ChipSelect, pui32Data,
                                       ui32NumBytes, ui32Options, pfnCallback);
                break;

            case AM_HAL_IOM_QUEUE_I2C_WRITE:
                ui32Status = am_hal_iom_i2c_write_nb(ui32Module, ui32ChipSelect, pui32Data,
                                        ui32NumBytes, ui32Options, pfnCallback);
                break;

            case AM_HAL_IOM_QUEUE_I2C_READ:
                ui32Status = am_hal_iom_i2c_read_nb(ui32Module, ui32ChipSelect, pui32Data,
                                       ui32NumBytes, ui32Options, pfnCallback);
                break;
        }
    }

    //
    // Exit the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        // Preserve the error
        g_iom_error_status[ui32Module] = ui32Status;
        // Call the respective callback
        pfnCallback();
    }
}

//*****************************************************************************
//
//! @brief Send a SPI frame using the IOM queue.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip-select number for this transaction.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs SPI writes to a selected SPI device.
//!
//! This function call is a queued implementation. It will write as much
//! data to the FIFO as possible immediately, store a pointer to the remaining
//! data, start the transfer on the bus, and then immediately return. If the
//! FIFO is already in use, this function will save its arguments to the IOM
//! queue and execute the transaction when the FIFO becomes available.
//!
//! The caller will need to make sure that \e am_hal_iom_queue_service() is
//! called for IOM FIFO interrupt events and "command complete" interrupt
//! events. The \e am_hal_iom_queue_service() function will refill the FIFO as
//! necessary and call the \e pfnCallback function when the transaction is
//! finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_queue_spi_write(uint32_t ui32Module, uint32_t ui32ChipSelect,
                           uint32_t *pui32Data, uint32_t ui32NumBytes,
                           uint32_t ui32Options, am_hal_iom_callback_t pfnCallback)
{
    uint32_t ui32Critical;
    am_hal_iom_status_e ui32Status;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if ( ui32NumBytes == 0 )
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // Check to see if we need to use the queue. If the IOM is idle, and
    // there's nothing in the queue already, we can go ahead and start the
    // transaction in the physical IOM. Need to check for the g_bIomBusy to
    // avoid a race condition where IDLE is set - but the command complete
    // for previous transaction has not been processed yet
    //
    if ( (g_bIomBusy[ui32Module] == false) &&
        am_hal_queue_empty(&g_psIOMQueue[ui32Module]) )
    {
        //
        // Send the packet.
        //
        ui32Status = am_hal_iom_spi_write_nb(ui32Module, ui32ChipSelect, pui32Data,
                                ui32NumBytes, ui32Options, pfnCallback);
    }
    else
    {
        //
        // Otherwise, we'll build a transaction structure and add it to the queue.
        //
        am_hal_iom_queue_entry_t sIOMTransaction;

        sIOMTransaction.ui32Operation = AM_HAL_IOM_QUEUE_SPI_WRITE;
        sIOMTransaction.ui32Module = ui32Module;
        sIOMTransaction.ui32ChipSelect = ui32ChipSelect;
        sIOMTransaction.pui32Data = pui32Data;
        sIOMTransaction.ui32NumBytes = ui32NumBytes;
        sIOMTransaction.ui32Options = ui32Options;
        sIOMTransaction.pfnCallback = pfnCallback;

        //
        // Make sure the item actually makes it into the queue
        //
        if ( am_hal_queue_item_add(&g_psIOMQueue[ui32Module], &sIOMTransaction, 1) == false )
        {
            //
            // Didn't have enough memory.
            //
            ui32Status = AM_HAL_IOM_ERR_RESOURCE_ERR;
        }
    }

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status;
    }
    //
    // Exit the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Read a SPI frame using the IOM queue.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32ChipSelect - Chip select number for this transaction.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional SPI transfer options.
//!
//! This function performs SPI reads to a selected SPI device.
//!
//! This function call is a queued implementation. It will write as much
//! data to the FIFO as possible immediately, store a pointer to the remaining
//! data, start the transfer on the bus, and then immediately return. If the
//! FIFO is already in use, this function will save its arguments to the IOM
//! queue and execute the transaction when the FIFO becomes available.
//!
//! The caller will need to make sure that \e am_hal_iom_queue_service() is
//! called for IOM FIFO interrupt events and "command complete" interrupt
//! events. The \e am_hal_iom_queue_service() function will empty the FIFO as
//! necessary and call the \e pfnCallback function when the transaction is
//! finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_queue_spi_read(uint32_t ui32Module, uint32_t ui32ChipSelect,
                          uint32_t *pui32Data, uint32_t ui32NumBytes,
                          uint32_t ui32Options, am_hal_iom_callback_t pfnCallback)
{
    uint32_t ui32Critical;
    am_hal_iom_status_e ui32Status;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if ( ui32NumBytes == 0 )
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // Check to see if we need to use the queue. If the IOM is idle, and
    // there's nothing in the queue already, we can go ahead and start the
    // transaction in the physical IOM. Need to check for the g_bIomBusy to
    // avoid a race condition where IDLE is set - but the command complete
    // for previous transaction has not been processed yet
    //
    if ( (g_bIomBusy[ui32Module] == false) &&
        am_hal_queue_empty(&g_psIOMQueue[ui32Module]) )
    {
        //
        // Send the packet.
        //
        ui32Status = am_hal_iom_spi_read_nb(ui32Module, ui32ChipSelect, pui32Data,
                               ui32NumBytes, ui32Options, pfnCallback);
    }
    else
    {
        //
        // Otherwise, we'll build a transaction structure and add it to the queue.
        //
        am_hal_iom_queue_entry_t sIOMTransaction;

        sIOMTransaction.ui32Operation = AM_HAL_IOM_QUEUE_SPI_READ;
        sIOMTransaction.ui32Module = ui32Module;
        sIOMTransaction.ui32ChipSelect = ui32ChipSelect;
        sIOMTransaction.pui32Data = pui32Data;
        sIOMTransaction.ui32NumBytes = ui32NumBytes;
        sIOMTransaction.ui32Options = ui32Options;
        sIOMTransaction.pfnCallback = pfnCallback;

        //
        // Make sure the item actually makes it into the queue
        //
        if ( am_hal_queue_item_add(&g_psIOMQueue[ui32Module], &sIOMTransaction, 1) == false )
        {
            //
            // Didn't have enough memory.
            //
            ui32Status = AM_HAL_IOM_ERR_RESOURCE_ERR;
        }
    }

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status;
    }
    //
    // Exit the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Send an I2C frame using the IOM queue.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32BusAddress - I2C address of the target device.
//! @param pui32Data - Pointer to the bytes that will be sent.
//! @param ui32NumBytes - Number of bytes to send.
//! @param ui32Options - Additional I2C transfer options.
//!
//! This function performs I2C writes to a selected I2C device.
//!
//! This function call is a queued implementation. It will write as much
//! data to the FIFO as possible immediately, store a pointer to the remaining
//! data, start the transfer on the bus, and then immediately return. If the
//! FIFO is already in use, this function will save its arguments to the IOM
//! queue and execute the transaction when the FIFO becomes available.
//!
//! The caller will need to make sure that \e am_hal_iom_queue_service() is
//! called for IOM FIFO interrupt events and "command complete" interrupt
//! events. The \e am_hal_iom_queue_service() function will refill the FIFO as
//! necessary and call the \e pfnCallback function when the transaction is
//! finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_queue_i2c_write(uint32_t ui32Module, uint32_t ui32BusAddress,
                           uint32_t *pui32Data, uint32_t ui32NumBytes,
                           uint32_t ui32Options, am_hal_iom_callback_t pfnCallback)
{
    am_hal_iom_status_e ui32Status;
    uint32_t ui32Critical;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if ( ui32NumBytes == 0 )
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // Check to see if we need to use the queue. If the IOM is idle, and
    // there's nothing in the queue already, we can go ahead and start the
    // transaction in the physical IOM. Need to check for the g_bIomBusy to
    // avoid a race condition where IDLE is set - but the command complete
    // for previous transaction has not been processed yet
    //
    if ( (g_bIomBusy[ui32Module] == false) &&
        am_hal_queue_empty(&g_psIOMQueue[ui32Module]) )
    {
        //
        // Send the packet.
        //
        ui32Status = am_hal_iom_i2c_write_nb(ui32Module, ui32BusAddress, pui32Data,
                                ui32NumBytes, ui32Options, pfnCallback);
    }
    else
    {
        //
        // Otherwise, we'll build a transaction structure and add it to the queue.
        //
        am_hal_iom_queue_entry_t sIOMTransaction;

        sIOMTransaction.ui32Operation = AM_HAL_IOM_QUEUE_I2C_WRITE;
        sIOMTransaction.ui32Module = ui32Module;
        sIOMTransaction.ui32ChipSelect = ui32BusAddress;
        sIOMTransaction.pui32Data = pui32Data;
        sIOMTransaction.ui32NumBytes = ui32NumBytes;
        sIOMTransaction.ui32Options = ui32Options;
        sIOMTransaction.pfnCallback = pfnCallback;

        //
        // Make sure the item actually makes it into the queue
        //
        if ( am_hal_queue_item_add(&g_psIOMQueue[ui32Module], &sIOMTransaction, 1) == false )
        {
            //
            // Didn't have enough memory.
            //
            ui32Status = AM_HAL_IOM_ERR_RESOURCE_ERR;
        }
    }

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status;
    }
    //
    // Exit the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);
    return ui32Status;
}

//*****************************************************************************
//
//! @brief Read a I2C frame using the IOM queue.
//!
//! @param ui32Module - Module number for the IOM
//! @param ui32BusAddress - I2C address of the target device.
//! @param pui32Data - Pointer to the array where received bytes should go.
//! @param ui32NumBytes - Number of bytes to read.
//! @param ui32Options - Additional I2C transfer options.
//!
//! This function performs I2C reads to a selected I2C device.
//!
//! This function call is a queued implementation. It will write as much
//! data to the FIFO as possible immediately, store a pointer to the remaining
//! data, start the transfer on the bus, and then immediately return. If the
//! FIFO is already in use, this function will save its arguments to the IOM
//! queue and execute the transaction when the FIFO becomes available.
//!
//! The caller will need to make sure that \e am_hal_iom_queue_service() is
//! called for IOM FIFO interrupt events and "command complete" interrupt
//! events. The \e am_hal_iom_queue_service() function will empty the FIFO as
//! necessary and call the \e pfnCallback function when the transaction is
//! finished.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32Data array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui8Data array.
//
//*****************************************************************************
am_hal_iom_status_e
am_hal_iom_queue_i2c_read(uint32_t ui32Module, uint32_t ui32BusAddress,
                          uint32_t *pui32Data, uint32_t ui32NumBytes,
                          uint32_t ui32Options, am_hal_iom_callback_t pfnCallback)
{
    uint32_t ui32Critical;
    am_hal_iom_status_e ui32Status;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return AM_HAL_IOM_ERR_INVALID_MODULE;
    }
    // Reset the error status
    ui32Status = g_iom_error_status[ui32Module] = AM_HAL_IOM_SUCCESS;
    if ( ui32NumBytes == 0 )
    {
        g_iom_error_status[ui32Module] = ui32Status = AM_HAL_IOM_ERR_INVALID_PARAM;
        return ui32Status;
    }

    //
    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // Check to see if we need to use the queue. If the IOM is idle, and
    // there's nothing in the queue already, we can go ahead and start the
    // transaction in the physical IOM. Need to check for the g_bIomBusy to
    // avoid a race condition where IDLE is set - but the command complete
    // for previous transaction has not been processed yet
    //
    if ( (g_bIomBusy[ui32Module] == false) &&
        am_hal_queue_empty(&g_psIOMQueue[ui32Module]) )
    {
        //
        // Send the packet.
        //
        ui32Status = am_hal_iom_i2c_read_nb(ui32Module, ui32BusAddress, pui32Data,
                               ui32NumBytes, ui32Options, pfnCallback);
    }
    else
    {
        //
        // Otherwise, we'll build a transaction structure and add it to the queue.
        //
        am_hal_iom_queue_entry_t sIOMTransaction;

        sIOMTransaction.ui32Operation = AM_HAL_IOM_QUEUE_I2C_READ;
        sIOMTransaction.ui32Module = ui32Module;
        sIOMTransaction.ui32ChipSelect = ui32BusAddress;
        sIOMTransaction.pui32Data = pui32Data;
        sIOMTransaction.ui32NumBytes = ui32NumBytes;
        sIOMTransaction.ui32Options = ui32Options;
        sIOMTransaction.pfnCallback = pfnCallback;

        //
        // Make sure the item actually makes it into the queue
        //
        if ( am_hal_queue_item_add(&g_psIOMQueue[ui32Module], &sIOMTransaction, 1) == false )
        {
            //
            // Didn't have enough memory.
            //
            ui32Status = AM_HAL_IOM_ERR_RESOURCE_ERR;
        }
    }

    if (ui32Status != AM_HAL_IOM_SUCCESS)
    {
        g_iom_error_status[ui32Module] = ui32Status;
    }
    //
    // Exit the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);
    return ui32Status;
}

//*****************************************************************************
//
//! @brief "Block" until the queue of IOM transactions is over.
//!
//! @param ui32Module - Module number for the IOM.
//!
//! This function will sleep the core block until the queue for the selected
//! IOM is empty. This is mainly useful for non-RTOS applications where the
//! caller needs to know that a certain IOM transaction is complete before
//! continuing with the main program flow.
//!
//! @note This function will put the core to sleep while it waits for the
//! queued IOM transactions to complete. This will save power, in most
//! situations, but it may not be the best option in all cases. \e Do \e not
//! call this function from interrupt context (the core may not wake up again).
//! \e Be \e careful using this function from an RTOS task (many RTOS
//! implementations use hardware interrupts to switch contexts, and most RTOS
//! implementations expect to control sleep behavior).
//
//*****************************************************************************
void
am_hal_iom_sleeping_queue_flush(uint32_t ui32Module)
{
    bool bWaiting = true;
    uint32_t ui32Critical;

    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    //
    // Loop forever waiting for the IOM to be idle and the queue to be empty.
    //
    while ( bWaiting )
    {
        //
        // Start a critical section.
        //
        ui32Critical = am_hal_interrupt_master_disable();

        //
        // Check the queue and the IOM itself.
        //
        if ( (g_bIomBusy[ui32Module] == false) &&
            am_hal_queue_empty(&g_psIOMQueue[ui32Module]) )
        {
            //
            // If the queue is empty and the IOM is idle, we can go ahead and
            // return.
            //
            bWaiting = false;
        }
        else
        {
            //
            // Otherwise, we should sleep until the interface is actually free.
            //
            am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_NORMAL);
        }

        //
        // End the critical section.
        //
        am_hal_interrupt_master_set(ui32Critical);
    }
}

//*****************************************************************************
//
//! @brief Service IOM transaction queue.
//!
//! @param ui32Module - Module number for the IOM to be used.
//! @param ui32Status - Interrupt status bits for the IOM module being used.
//!
//! This function handles the operation of FIFOs and the IOM queue during
//! queued IOM transactions. If you are using \e am_hal_iom_queue_spi_write()
//! or similar functions, you will need to call this function in your interrupt
//! handler.
//!
//! @note This interrupt service routine relies on the user to enable the IOM
//! interrupts for FIFO threshold and CMD complete.
//!
//! Example:
//!
//! @code
//! void
//! am_iomaster0_isr(void)
//! {
//!     uint32_t ui32Status;
//!
//!     //
//!     // Check to see which interrupt caused us to enter the ISR.
//!     //
//!     ui32Status = am_hal_iom_int_status(0, true);
//!
//!     //
//!     // Clear the interrupts. This should be done before calling service routine
//!     // as otherwise we may lose re-triggered interrupts
//!     //
//!     am_hal_iom_int_clear(ui32Status);
//!
//!     //
//!     // Fill or empty the FIFO, and either continue the current operation or
//!     // start the next one in the queue. If there was a callback, it will be
//!     // called here.
//!     //
//!     am_hal_iom_queue_service(0, ui32Status);
//! }
//! @endcode
//!
//! @return
//
//*****************************************************************************
void
am_hal_iom_queue_service(uint32_t ui32Module, uint32_t ui32Status)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    //
    // Service the FIFOs in case this was a threshold interrupt.
    //
    am_hal_iom_int_service(ui32Module, ui32Status);

    //
    // If the last interrupt was a "command complete", then the IOM should be
    // idle already or very soon. Make absolutely sure that the IOM is not in
    // use, and then start the next transaction in the queue.
    //
    if ( ui32Status & AM_HAL_IOM_INT_CMDCMP )
    {
        if ( g_psIOMQueue[ui32Module].pui8Data != NULL )
        {
            am_hal_iom_queue_start_next_msg(ui32Module);
        }
    }
}

//*****************************************************************************
//
//! @brief Enable selected IOM Interrupts.
//!
//! @param ui32Module - Module number.
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_iom.h
//!
//! Use this function to enable the IOM interrupts.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_iom_int_enable(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    AM_REGn(IOMSTR, ui32Module, INTEN) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return the enabled IOM Interrupts.
//!
//! @param ui32Module - Module number.
//!
//! Use this function to return all enabled IOM interrupts.
//!
//! @return all enabled IOM interrupts.
//
//*****************************************************************************
uint32_t
am_hal_iom_int_enable_get(uint32_t ui32Module)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    return AM_REGn(IOMSTR, ui32Module, INTEN);
}

//*****************************************************************************
//
//! @brief Disable selected IOM Interrupts.
//!
//! @param ui32Module - Module number.
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_iom.h
//!
//! Use this function to disable the IOM interrupts.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_iom_int_disable(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    AM_REGn(IOMSTR, ui32Module, INTEN) &= ~ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Clear selected IOM Interrupts.
//!
//! @param ui32Module - Module number.
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_iom.h
//!
//! Use this function to clear the IOM interrupts.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_iom_int_clear(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    AM_REGn(IOMSTR, ui32Module, INTCLR) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Set selected IOM Interrupts.
//!
//! @param ui32Module - Module number.
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_iom.h
//!
//! Use this function to set the IOM interrupts.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_iom_int_set(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return;
    }

    AM_REGn(IOMSTR, ui32Module, INTSET) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return the IOM Interrupt status.
//!
//! @param ui32Module - Module number.
//! @param bEnabledOnly - return only the enabled interrupts.
//!
//! Use this function to get the IOM interrupt status.
//!
//! @return interrupt status
//
//*****************************************************************************
uint32_t
am_hal_iom_int_status_get(uint32_t ui32Module, bool bEnabledOnly)
{
    //
    // Validate parameters
    //
    if ( ui32Module >= AM_REG_IOMSTR_NUM_MODULES )
    {
        return 0;
    }

    if ( bEnabledOnly )
    {
        uint32_t u32RetVal = AM_REGn(IOMSTR, ui32Module, INTSTAT);
        return u32RetVal & AM_REGn(IOMSTR, ui32Module, INTEN);
    }
    else
    {
        return AM_REGn(IOMSTR, ui32Module, INTSTAT);
    }
}


//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
