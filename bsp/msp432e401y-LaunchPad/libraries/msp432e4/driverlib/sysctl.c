//*****************************************************************************
//
// sysctl.c - Driver for the system controller.
//
// Copyright (c) 2005-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

#include "types.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_nvic.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_flash.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"
#include "sysctl.h"

//*****************************************************************************
//
// The flash shift used in the math to calculate the flash sector size.
//
//*****************************************************************************
#ifndef FLASH_PP_MAINSS_S
    #define FLASH_PP_MAINSS_S       16
#endif

//*****************************************************************************
//
// This macro converts the XTAL value provided in the ui32Config parameter to
// an index to the g_pui32Xtals array.
//
//*****************************************************************************
#define SysCtlXtalCfgToIndex(a) ((a & 0x7c0) >> 6)

//*****************************************************************************
//
// An array that maps the crystal number in RCC to a frequency.
//
//*****************************************************************************
static const uint32_t g_pui32Xtals[] =
{
    5000000,
    6000000,
    8000000,
    10000000,
    12000000,
    16000000,
    18000000,
    20000000,
    24000000,
    25000000
};

//*****************************************************************************
//
// Maximum number of VCO entries in the g_pui32XTALtoVCO and
// g_pui32VCOFrequencies structures for a device.
//
//*****************************************************************************
#define MAX_VCO_ENTRIES         2
#define MAX_XTAL_ENTRIES        18

//*****************************************************************************
//
// These macros are used in the g_pui32XTALtoVCO table to make it more
// readable.
//
//*****************************************************************************
#define PLL_M_TO_REG(mi, mf)                                                  \
        ((uint32_t)mi | (uint32_t)(mf << SYSCTL_PLLFREQ0_MFRAC_S))
#define PLL_N_TO_REG(n)                                                       \
        ((uint32_t)(n - 1) << SYSCTL_PLLFREQ1_N_S)
#define PLL_Q_TO_REG(q)                                                       \
        ((uint32_t)(q - 1) << SYSCTL_PLLFREQ1_Q_S)

//*****************************************************************************
//
// Look up of the values that go into the PLLFREQ0 and PLLFREQ1 registers.
//
//*****************************************************************************
static const uint32_t g_pppui32XTALtoVCO[MAX_VCO_ENTRIES][MAX_XTAL_ENTRIES][3] =
{
    {
        //
        // VCO 320 MHz
        //
        { PLL_M_TO_REG(64, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 5 MHz
        { PLL_M_TO_REG(160, 0),  PLL_N_TO_REG(3), PLL_Q_TO_REG(2) },     // 6 MHz
        { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 8 MHz
        { PLL_M_TO_REG(32, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 10 MHz
        { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(3), PLL_Q_TO_REG(2) },     // 12 MHz
        { PLL_M_TO_REG(20, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 16 MHz
        { PLL_M_TO_REG(160, 0),  PLL_N_TO_REG(9), PLL_Q_TO_REG(2) },     // 18 MHz
        { PLL_M_TO_REG(16, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 20 MHz
        { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(3), PLL_Q_TO_REG(2) },     // 24 MHz
        { PLL_M_TO_REG(64, 0),   PLL_N_TO_REG(5), PLL_Q_TO_REG(2) },     // 25 MHz
    },
    {
        //
        // VCO 480 MHz
        //
        { PLL_M_TO_REG(96, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 5 MHz
        { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 6 MHz
        { PLL_M_TO_REG(60, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 8 MHz
        { PLL_M_TO_REG(48, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 10 MHz
        { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 12 MHz
        { PLL_M_TO_REG(30, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 16 MHz
        { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(3), PLL_Q_TO_REG(2) },     // 18 MHz
        { PLL_M_TO_REG(24, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 20 MHz
        { PLL_M_TO_REG(20, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) },     // 24 MHz
        { PLL_M_TO_REG(96, 0),   PLL_N_TO_REG(5), PLL_Q_TO_REG(2) },     // 25 MHz
    },
};

//*****************************************************************************
//
// The mapping of system clock frequency to flash memory timing parameters.
//
//*****************************************************************************
static const struct
{
    uint32_t ui32Frequency;
    uint32_t ui32MemTiming;
}
g_sXTALtoMEMTIM[] =
{
    {
        16000000, (SYSCTL_MEMTIM0_FBCHT_0_5 | SYSCTL_MEMTIM0_FBCE |
                   (0 << SYSCTL_MEMTIM0_FWS_S) |
                   SYSCTL_MEMTIM0_EBCHT_0_5 | SYSCTL_MEMTIM0_EBCE |
                   (0 << SYSCTL_MEMTIM0_EWS_S) |
                   SYSCTL_MEMTIM0_MB1)
    },
    {
        40000000, (SYSCTL_MEMTIM0_FBCHT_1_5 | (1 << SYSCTL_MEMTIM0_FWS_S) |
                   SYSCTL_MEMTIM0_EBCHT_1_5 | (1 << SYSCTL_MEMTIM0_EWS_S) |
                   SYSCTL_MEMTIM0_MB1)
    },
    {
        60000000, (SYSCTL_MEMTIM0_FBCHT_2 | (2 << SYSCTL_MEMTIM0_FWS_S) |
                   SYSCTL_MEMTIM0_EBCHT_2 | (2 << SYSCTL_MEMTIM0_EWS_S) |
                   SYSCTL_MEMTIM0_MB1)
    },
    {
        80000000, (SYSCTL_MEMTIM0_FBCHT_2_5 | (3 << SYSCTL_MEMTIM0_FWS_S) |
                   SYSCTL_MEMTIM0_EBCHT_2_5 | (3 << SYSCTL_MEMTIM0_EWS_S) |
                   SYSCTL_MEMTIM0_MB1)
    },
    {
        100000000, (SYSCTL_MEMTIM0_FBCHT_3 | (4 << SYSCTL_MEMTIM0_FWS_S) |
                    SYSCTL_MEMTIM0_EBCHT_3 | (4 << SYSCTL_MEMTIM0_EWS_S) |
                    SYSCTL_MEMTIM0_MB1)
    },
    {
        120000000, (SYSCTL_MEMTIM0_FBCHT_3_5 | (5 << SYSCTL_MEMTIM0_FWS_S) |
                    SYSCTL_MEMTIM0_EBCHT_3_5 | (5 << SYSCTL_MEMTIM0_EWS_S) |
                    SYSCTL_MEMTIM0_MB1)
    },
};

//*****************************************************************************
//
// Get the correct memory timings for a given system clock value.
//
//*****************************************************************************
static uint32_t
_SysCtlMemTimingGet(uint32_t ui32SysClock)
{
    uint_fast8_t ui8Idx;

    //
    // Loop through the flash memory timings.
    //
    for (ui8Idx = 0;
            ui8Idx < (sizeof(g_sXTALtoMEMTIM) / sizeof(g_sXTALtoMEMTIM[0]));
            ui8Idx++)
    {
        //
        // See if the system clock frequency is less than the maximum frequency
        // for this flash memory timing.
        //
        if (ui32SysClock <= g_sXTALtoMEMTIM[ui8Idx].ui32Frequency)
        {
            //
            // This flash memory timing is the best choice for the system clock
            // frequency, so return it now.
            //
            return (g_sXTALtoMEMTIM[ui8Idx].ui32MemTiming);
        }
    }

    //
    // An appropriate flash memory timing could not be found, so the device is
    // being clocked too fast.  Return the default flash memory timing.
    //
    return (0);
}

//*****************************************************************************
//
// Calculate the system frequency from the register settings base on the
// oscillator input.
//
//*****************************************************************************
static uint32_t
_SysCtlFrequencyGet(uint32_t ui32Xtal)
{
    uint32_t ui32Result;
    uint_fast16_t ui16F1, ui16F2;
    uint_fast16_t ui16PInt, ui16PFract;
    uint_fast8_t ui8Q, ui8N;

    //
    // Extract all of the values from the hardware registers.
    //
    ui16PFract = ((HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_MFRAC_M) >>
                  SYSCTL_PLLFREQ0_MFRAC_S);
    ui16PInt = HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_MINT_M;
    ui8Q = (((HWREG(SYSCTL_PLLFREQ1) & SYSCTL_PLLFREQ1_Q_M) >>
             SYSCTL_PLLFREQ1_Q_S) + 1);
    ui8N = (((HWREG(SYSCTL_PLLFREQ1) & SYSCTL_PLLFREQ1_N_M) >>
             SYSCTL_PLLFREQ1_N_S) + 1);

    //
    // Divide the crystal value by N.
    //
    ui32Xtal /= (uint32_t)ui8N;

    //
    // Calculate the multiplier for bits 9:5.
    //
    ui16F1 = ui16PFract / 32;

    //
    // Calculate the multiplier for bits 4:0.
    //
    ui16F2 = ui16PFract - (ui16F1 * 32);

    //
    // Get the integer portion.
    //
    ui32Result = ui32Xtal * (uint32_t)ui16PInt;

    //
    // Add first fractional bits portion(9:0).
    //
    ui32Result += (ui32Xtal * (uint32_t)ui16F1) / 32;

    //
    // Add the second fractional bits portion(4:0).
    //
    ui32Result += (ui32Xtal * (uint32_t)ui16F2) / 1024;

    //
    // Divide the result by Q.
    //
    ui32Result = ui32Result / (uint32_t)ui8Q;

    //
    // Return the resulting PLL frequency.
    //
    return (ui32Result);
}

//*****************************************************************************
//
// Look up of the possible VCO frequencies.
//
//*****************************************************************************
static const uint32_t g_pui32VCOFrequencies[MAX_VCO_ENTRIES] =
{
    160000000,                              // VCO 320
    240000000,                              // VCO 480
};

//*****************************************************************************
//
// The base addresses of the various peripheral control registers.
//
//*****************************************************************************
#define SYSCTL_PPBASE           0x400fe300
#define SYSCTL_SRBASE           0x400fe500
#define SYSCTL_RCGCBASE         0x400fe600
#define SYSCTL_SCGCBASE         0x400fe700
#define SYSCTL_DCGCBASE         0x400fe800
#define SYSCTL_PCBASE           0x400fe900
#define SYSCTL_PRBASE           0x400fea00

//*****************************************************************************
//
//! \internal
//! Checks a peripheral identifier.
//!
//! \param ui32Peripheral is the peripheral identifier.
//!
//! This function determines if a peripheral identifier is valid.
//!
//! \return Returns \b true if the peripheral identifier is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static bool
_SysCtlPeripheralValid(uint32_t ui32Peripheral)
{
    return ((ui32Peripheral == SYSCTL_PERIPH_ADC0) ||
            (ui32Peripheral == SYSCTL_PERIPH_ADC1) ||
            (ui32Peripheral == SYSCTL_PERIPH_CAN0) ||
            (ui32Peripheral == SYSCTL_PERIPH_CAN1) ||
            (ui32Peripheral == SYSCTL_PERIPH_COMP0) ||
            (ui32Peripheral == SYSCTL_PERIPH_CCM0) ||
            (ui32Peripheral == SYSCTL_PERIPH_EEPROM0) ||
            (ui32Peripheral == SYSCTL_PERIPH_EPHY0) ||
            (ui32Peripheral == SYSCTL_PERIPH_EMAC0) ||
            (ui32Peripheral == SYSCTL_PERIPH_EPI0) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOA) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOB) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOC) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOD) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOE) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOF) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOG) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOH) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOJ) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOK) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOL) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOM) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPION) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOP) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOQ) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOR) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOS) ||
            (ui32Peripheral == SYSCTL_PERIPH_GPIOT) ||
            (ui32Peripheral == SYSCTL_PERIPH_HIBERNATE) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C0) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C1) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C2) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C3) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C4) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C5) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C6) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C7) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C8) ||
            (ui32Peripheral == SYSCTL_PERIPH_I2C9) ||
            (ui32Peripheral == SYSCTL_PERIPH_LCD0) ||
            (ui32Peripheral == SYSCTL_PERIPH_PWM0) ||
            (ui32Peripheral == SYSCTL_PERIPH_PWM1) ||
            (ui32Peripheral == SYSCTL_PERIPH_QEI0) ||
            (ui32Peripheral == SYSCTL_PERIPH_QEI1) ||
            (ui32Peripheral == SYSCTL_PERIPH_SSI0) ||
            (ui32Peripheral == SYSCTL_PERIPH_SSI1) ||
            (ui32Peripheral == SYSCTL_PERIPH_SSI2) ||
            (ui32Peripheral == SYSCTL_PERIPH_SSI3) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER0) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER1) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER2) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER3) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER4) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER5) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER6) ||
            (ui32Peripheral == SYSCTL_PERIPH_TIMER7) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART0) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART1) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART2) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART3) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART4) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART5) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART6) ||
            (ui32Peripheral == SYSCTL_PERIPH_UART7) ||
            (ui32Peripheral == SYSCTL_PERIPH_UDMA) ||
            (ui32Peripheral == SYSCTL_PERIPH_USB0) ||
            (ui32Peripheral == SYSCTL_PERIPH_WDOG0) ||
            (ui32Peripheral == SYSCTL_PERIPH_WDOG1));
}
#endif

//*****************************************************************************
//
//! Gets the size of the SRAM.
//!
//! This function determines the size of the SRAM on the device.
//!
//! \return The total number of bytes of SRAM.
//
//*****************************************************************************
uint32_t
SysCtlSRAMSizeGet(void)
{
    return ((HWREG(FLASH_SSIZE) + 1) * 256);
}

//*****************************************************************************
//
//! Gets the size of the flash.
//!
//! This function determines the size of the flash on the device.
//!
//! \return The total number of bytes of flash.
//
//*****************************************************************************
uint32_t
SysCtlFlashSizeGet(void)
{
    //
    // Get the flash size from the FLASH_PP register.
    //
    return (2048 * ((HWREG(FLASH_PP) & FLASH_PP_SIZE_M) + 1));
}

//*****************************************************************************
//
//! Gets the size of a single eraseable sector of flash.
//!
//! This function determines the flash sector size on the device.
//! This size determines the erase granularity of the device flash.
//!
//! \return The number of bytes in a single flash sector.
//
//*****************************************************************************
uint32_t
SysCtlFlashSectorSizeGet(void)
{
    //
    // Get the flash sector size from the FLASH_PP register.
    //
    return (1 << (10 +
                  ((HWREG(FLASH_PP) &
                    FLASH_PP_MAINSS_M) >> FLASH_PP_MAINSS_S)));
}

//*****************************************************************************
//
//! Determines if a peripheral is present.
//!
//! \param ui32Peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is present in the
//! device.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return Returns \b true if the specified peripheral is present and \b false
//! if it is not.
//
//*****************************************************************************
bool
SysCtlPeripheralPresent(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // See if this peripheral is present.
    //
    return (HWREGBITW(SYSCTL_PPBASE + ((ui32Peripheral & 0xff00) >> 8),
                      ui32Peripheral & 0xff));
}

//*****************************************************************************
//
//! Determines if a peripheral is ready.
//!
//! \param ui32Peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is ready to be
//! accessed.  The peripheral may be in a non-ready state if it is not enabled,
//! is being held in reset, or is in the process of becoming ready after being
//! enabled or taken out of reset.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return Returns \b true if the specified peripheral is ready and \b false
//! if it is not.
//
//*****************************************************************************
bool
SysCtlPeripheralReady(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // See if this peripheral is ready.
    //
    return (HWREGBITW(SYSCTL_PRBASE + ((ui32Peripheral & 0xff00) >> 8),
                      ui32Peripheral & 0xff));
}

//*****************************************************************************
//
//! Powers on a peripheral.
//!
//! \param ui32Peripheral is the peripheral to be powered on.
//!
//! This function turns on the power to a peripheral.  The peripheral continues
//! to receive power even when its clock is not enabled.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_CAN0,\b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_EMAC,
//! \b SYSCTL_PERIPH_EPHY, \b SYSCTL_PERIPH_LCD0, \b SYSCTL_PERIPH_USB0
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralPowerOn(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Power on this peripheral.
    //
    HWREGBITW(SYSCTL_PCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 1;
}

//*****************************************************************************
//
//! Powers off a peripheral.
//!
//! \param ui32Peripheral is the peripheral to be powered off.
//!
//! This function allows the power to a peripheral to be turned off.  The
//! peripheral continues to receive power when its clock is enabled, but
//! the power is removed when its clock is disabled.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_CAN0,\b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_EMAC,
//! \b SYSCTL_PERIPH_EPHY, \b SYSCTL_PERIPH_LCD0, \b SYSCTL_PERIPH_USB0
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralPowerOff(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Power off this peripheral.
    //
    HWREGBITW(SYSCTL_PCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 0;
}

//*****************************************************************************
//
//! Performs a software reset of a peripheral.
//!
//! \param ui32Peripheral is the peripheral to reset.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! de-asserted, returning the internal state of the peripheral to its reset
//! condition.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralReset(uint32_t ui32Peripheral)
{
    volatile uint_fast8_t ui8Delay;

    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Put the peripheral into the reset state.
    //
    HWREGBITW(SYSCTL_SRBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 1;

    //
    // Delay for a little bit.
    //
    for (ui8Delay = 0; ui8Delay < 16; ui8Delay++)
    {
    }

    //
    // Take the peripheral out of the reset state.
    //
    HWREGBITW(SYSCTL_SRBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 0;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param ui32Peripheral is the peripheral to enable.
//!
//! This function enables a peripheral.  At power-up, all peripherals are
//! disabled; they must be enabled in order to operate or respond to register
//! reads/writes.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \note It takes five clock cycles after the write to enable a peripheral
//! before the the peripheral is actually enabled.  During this time, attempts
//! to access the peripheral result in a bus fault.  Care should be taken
//! to ensure that the peripheral is not accessed during this brief time
//! period.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Enable this peripheral.
    //
    HWREGBITW(SYSCTL_RCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 1;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param ui32Peripheral is the peripheral to disable.
//!
//! This function disables a peripheral.  Once disabled, they do not operate or
//! respond to register reads/writes.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Disable this peripheral.
    //
    HWREGBITW(SYSCTL_RCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 0;
}

//*****************************************************************************
//
//! Enables a peripheral in sleep mode.
//!
//! \param ui32Peripheral is the peripheral to enable in sleep mode.
//!
//! This function allows a peripheral to continue operating when the processor
//! goes into sleep mode.  Because the clocking configuration of the device
//! does not change, any peripheral can safely continue operating while the
//! processor is in sleep mode and can therefore wake the processor from sleep
//! mode.
//!
//! Sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral sleep mode
//! configuration is maintained but has no effect when sleep mode is entered.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralSleepEnable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Enable this peripheral in sleep mode.
    //
    HWREGBITW(SYSCTL_SCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 1;
}

//*****************************************************************************
//
//! Disables a peripheral in sleep mode.
//!
//! \param ui32Peripheral is the peripheral to disable in sleep mode.
//!
//! This function causes a peripheral to stop operating when the processor goes
//! into sleep mode.  Disabling peripherals while in sleep mode helps to lower
//! the current draw of the device.  If enabled (via SysCtlPeripheralEnable()),
//! the peripheral automatically resumes operation when the processor
//! leaves sleep mode, maintaining its entire state from before sleep mode was
//! entered.
//!
//! Sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral sleep mode
//! configuration is maintained but has no effect when sleep mode is entered.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralSleepDisable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Disable this peripheral in sleep mode.
    //
    HWREGBITW(SYSCTL_SCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 0;
}

//*****************************************************************************
//
//! Enables a peripheral in deep-sleep mode.
//!
//! \param ui32Peripheral is the peripheral to enable in deep-sleep mode.
//!
//! This function allows a peripheral to continue operating when the processor
//! goes into deep-sleep mode.  Because the clocking configuration of the
//! device may change, not all peripherals can safely continue operating while
//! the processor is in deep-sleep mode.  Those that must run at a particular
//! frequency (such as a UART) do not work as expected if the clock changes.
//! It is the responsibility of the caller to make sensible choices.
//!
//! Deep-sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral deep-sleep mode
//! configuration is maintained but has no effect when deep-sleep mode is
//! entered.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDeepSleepEnable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Enable this peripheral in deep-sleep mode.
    //
    HWREGBITW(SYSCTL_DCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 1;
}

//*****************************************************************************
//
//! Disables a peripheral in deep-sleep mode.
//!
//! \param ui32Peripheral is the peripheral to disable in deep-sleep mode.
//!
//! This function causes a peripheral to stop operating when the processor goes
//! into deep-sleep mode.  Disabling peripherals while in deep-sleep mode helps
//! to lower the current draw of the device, and can keep peripherals that
//! require a particular clock frequency from operating when the clock changes
//! as a result of entering deep-sleep mode.  If enabled (via
//! SysCtlPeripheralEnable()), the peripheral automatically resumes
//! operation when the processor leaves deep-sleep mode, maintaining its entire
//! state from before deep-sleep mode was entered.
//!
//! Deep-sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral deep-sleep mode
//! configuration is maintained but has no effect when deep-sleep mode is
//! entered.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC0, \b SYSCTL_PERIPH_ADC1, \b SYSCTL_PERIPH_CAN0,
//! \b SYSCTL_PERIPH_CAN1, \b SYSCTL_PERIPH_CCM0,\b SYSCTL_PERIPH_COMP0,
//! \b SYSCTL_PERIPH_EEPROM0, \b SYSCTL_PERIPH_EMAC, \b SYSCTL_PERIPH_EPHY,
//! \b SYSCTL_PERIPH_EPI0,
//! \b SYSCTL_PERIPH_GPIOA, \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC,
//! \b SYSCTL_PERIPH_GPIOD, \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF,
//! \b SYSCTL_PERIPH_GPIOG, \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_GPIOJ,
//! \b SYSCTL_PERIPH_GPIOK, \b SYSCTL_PERIPH_GPIOL, \b SYSCTL_PERIPH_GPIOM,
//! \b SYSCTL_PERIPH_GPION, \b SYSCTL_PERIPH_GPIOP, \b SYSCTL_PERIPH_GPIOQ,
//! \b SYSCTL_PERIPH_GPIOR, \b SYSCTL_PERIPH_GPIOS, \b SYSCTL_PERIPH_GPIOT,
//! \b SYSCTL_PERIPH_HIBERNATE,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_I2C2,
//! \b SYSCTL_PERIPH_I2C3, \b SYSCTL_PERIPH_I2C4, \b SYSCTL_PERIPH_I2C5,
//! \b SYSCTL_PERIPH_I2C6, \b SYSCTL_PERIPH_I2C7, \b SYSCTL_PERIPH_I2C8,
//! \b SYSCTL_PERIPH_I2C9, \b SYSCTL_PERIPH_LCD0,
//! \b SYSCTL_PERIPH_ONEWIRE0,
//! \b SYSCTL_PERIPH_PWM0, \b SYSCTL_PERIPH_PWM1, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_SSI2, \b SYSCTL_PERIPH_SSI3, \b SYSCTL_PERIPH_TIMER0,
//! \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2, \b SYSCTL_PERIPH_TIMER3,
//! \b SYSCTL_PERIPH_TIMER4, \b SYSCTL_PERIPH_TIMER5, \b SYSCTL_PERIPH_TIMER6,
//! \b SYSCTL_PERIPH_TIMER7, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, \b SYSCTL_PERIPH_UART3, \b SYSCTL_PERIPH_UART4,
//! \b SYSCTL_PERIPH_UART5, \b SYSCTL_PERIPH_UART6, \b SYSCTL_PERIPH_UART7,
//! \b SYSCTL_PERIPH_UDMA, \b SYSCTL_PERIPH_USB0, \b SYSCTL_PERIPH_WDOG0,
//! or \b SYSCTL_PERIPH_WDOG1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDeepSleepDisable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Disable this peripheral in deep-sleep mode.
    //
    HWREGBITW(SYSCTL_DCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 0;
}

//*****************************************************************************
//
//! Controls peripheral clock gating in sleep and deep-sleep mode.
//!
//! \param bEnable is a boolean that is \b true if the sleep and deep-sleep
//! peripheral configuration should be used and \b false if not.
//!
//! This function controls how peripherals are clocked when the processor goes
//! into sleep or deep-sleep mode.  By default, the peripherals are clocked the
//! same as in run mode; if peripheral clock gating is enabled, they are
//! clocked according to the configuration set by
//! SysCtlPeripheralSleepEnable(), SysCtlPeripheralSleepDisable(),
//! SysCtlPeripheralDeepSleepEnable(), and SysCtlPeripheralDeepSleepDisable().
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralClockGating(bool bEnable)
{
    //
    // Enable peripheral clock gating as requested.
    //
    if (bEnable)
    {
        HWREG(SYSCTL_RSCLKCFG) |= SYSCTL_RSCLKCFG_ACG;
    }
    else
    {
        HWREG(SYSCTL_RSCLKCFG) &= ~SYSCTL_RSCLKCFG_ACG;
    }
}

//*****************************************************************************
//
//! Registers an interrupt handler for the system control interrupt.
//!
//! \param pfnHandler is a pointer to the function to be called when the system
//! control interrupt occurs.
//!
//! This function registers the handler to be called when a system control
//! interrupt occurs.  This function enables the global interrupt in the
//! interrupt controller; specific system control interrupts must be enabled
//! via SysCtlIntEnable().  It is the interrupt handler's responsibility to
//! clear the interrupt source via SysCtlIntClear().
//!
//! System control can generate interrupts when the PLL achieves lock, if the
//! internal LDO current limit is exceeded, if the internal oscillator fails,
//! if the main oscillator fails, if the internal LDO output voltage droops too
//! much, if the external voltage droops too much, or if the PLL fails.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    IntRegister(INT_SYSCTL, pfnHandler);

    //
    // Enable the system control interrupt.
    //
    IntEnable(INT_SYSCTL);
}

//*****************************************************************************
//
//! Unregisters the interrupt handler for the system control interrupt.
//!
//! This function unregisters the handler to be called when a system control
//! interrupt occurs.  This function also masks off the interrupt in the
//! interrupt controller so that the interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntUnregister(void)
{
    //
    // Disable the interrupt.
    //
    IntDisable(INT_SYSCTL);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_SYSCTL);
}

//*****************************************************************************
//
//! Enables individual system control interrupt sources.
//!
//! \param ui32Ints is a bit mask of the interrupt sources to be enabled.  Must
//! be a logical OR of \b SYSCTL_INT_BOR0, \b SYSCTL_INT_VDDA_OK,
//! \b SYSCTL_INT_MOSC_PUP, \b SYSCTL_INT_USBPLL_LOCK,
//! \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_BOR, and/or
//! \b SYSCTL_INT_BOR1.
//!
//! This function enables the indicated system control interrupt sources.  Only
//! the sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntEnable(uint32_t ui32Ints)
{
    //
    // Enable the specified interrupts.
    //
    HWREG(SYSCTL_IMC) |= ui32Ints;
}

//*****************************************************************************
//
//! Disables individual system control interrupt sources.
//!
//! \param ui32Ints is a bit mask of the interrupt sources to be disabled.
//! Must be a logical OR of \b SYSCTL_INT_BOR0, \b SYSCTL_INT_VDDA_OK,
//! \b SYSCTL_INT_MOSC_PUP, \b SYSCTL_INT_USBPLL_LOCK,
//! \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_BOR, and/or
//! \b SYSCTL_INT_BOR1.
//!
//! This function disables the indicated system control interrupt sources.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt; disabled sources have no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntDisable(uint32_t ui32Ints)
{
    //
    // Disable the specified interrupts.
    //
    HWREG(SYSCTL_IMC) &= ~(ui32Ints);
}

//*****************************************************************************
//
//! Clears system control interrupt sources.
//!
//! \param ui32Ints is a bit mask of the interrupt sources to be cleared.  Must
//! be a logical OR of \b SYSCTL_INT_BOR0, \b SYSCTL_INT_VDDA_OK,
//! \b SYSCTL_INT_MOSC_PUP, \b SYSCTL_INT_USBPLL_LOCK,
//! \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_BOR, and/or
//! \b SYSCTL_INT_BOR1.
//!
//! The specified system control interrupt sources are cleared, so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep it from being called again immediately on exit.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntClear(uint32_t ui32Ints)
{
    //
    // Clear the requested interrupt sources.
    //
    HWREG(SYSCTL_MISC) = ui32Ints;
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param bMasked is false if the raw interrupt status is required and true if
//! the masked interrupt status is required.
//!
//! This function returns the interrupt status for the system controller.
//! Either the raw interrupt status or the status of interrupts that are
//! allowed to reflect to the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b SYSCTL_INT_BOR0, \b SYSCTL_INT_VDDA_OK,
//! \b SYSCTL_INT_MOSC_PUP, \b SYSCTL_INT_USBPLL_LOCK,
//! \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_BOR, and/or
//! \b SYSCTL_INT_BOR1.
//
//*****************************************************************************
uint32_t
SysCtlIntStatus(bool bMasked)
{
    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if (bMasked)
    {
        return (HWREG(SYSCTL_MISC));
    }
    else
    {
        return (HWREG(SYSCTL_RIS));
    }
}

//*****************************************************************************
//
//! Sets the output voltage of the LDO when the device enters deep-sleep
//! mode.
//!
//! \param ui32Voltage is the required output voltage from the LDO while in
//! deep-sleep mode.
//!
//! This function sets the output voltage of the LDO while in deep-sleep mode.
//! The \e ui32Voltage parameter specifies the output voltage of the LDO and
//! must be one of the following values: \b SYSCTL_LDO_0_90V,
//! \b SYSCTL_LDO_0_95V, \b SYSCTL_LDO_1_00V, \b SYSCTL_LDO_1_05V,
//! \b SYSCTL_LDO_1_10V, \b SYSCTL_LDO_1_15V, or \b SYSCTL_LDO_1_20V.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLDODeepSleepSet(uint32_t ui32Voltage)
{
    //
    // Check the arguments.
    //
    ASSERT((ui32Voltage == SYSCTL_LDO_0_90V) ||
           (ui32Voltage == SYSCTL_LDO_0_95V) ||
           (ui32Voltage == SYSCTL_LDO_1_00V) ||
           (ui32Voltage == SYSCTL_LDO_1_05V) ||
           (ui32Voltage == SYSCTL_LDO_1_10V) ||
           (ui32Voltage == SYSCTL_LDO_1_15V) ||
           (ui32Voltage == SYSCTL_LDO_1_20V));

    //
    // Set the deep-sleep LDO voltage to the requested value.
    //
    HWREG(SYSCTL_LDODPCTL) = ui32Voltage;
}

//*****************************************************************************
//
//! Returns the output voltage of the LDO when the device enters deep-sleep
//! mode.
//!
//! This function returns the output voltage of the LDO when the device is
//! in deep-sleep mode, as specified by the control register.
//!
//! \return Returns the deep-sleep-mode voltage of the LDO; is one of
//! \b SYSCTL_LDO_0_90V, \b SYSCTL_LDO_0_95V, \b SYSCTL_LDO_1_00V,
//! \b SYSCTL_LDO_1_05V, \b SYSCTL_LDO_1_10V, \b SYSCTL_LDO_1_15V, or
//! \b SYSCTL_LDO_1_20V.
//
//*****************************************************************************
uint32_t
SysCtlLDODeepSleepGet(void)
{
    //
    // Return the deep-sleep-mode LDO voltage setting.
    //
    return (HWREG(SYSCTL_LDODPCTL));
}

//*****************************************************************************
//
//! Configures the power to the flash and SRAM while in sleep mode.
//!
//! \param ui32Config is the required flash and SRAM power configuration.
//!
//! This function allows the power configuration of the flash and SRAM while in
//! sleep mode to be set.  The \e ui32Config parameter is the logical OR of the
//! flash power configuration and the SRAM power configuration.
//!
//! The flash power configuration is specified as either:
//!
//! - \b SYSCTL_FLASH_NORMAL - The flash is left in fully powered mode,
//!    providing fast wake-up time but higher power consumption.
//! - \b SYSCTL_FLASH_LOW_POWER - The flash is in low power mode, providing
//!   reduced power consumption but longer wake-up time.
//!
//! The SRAM power configuration is specified as one of:
//!
//! - \b SYSCTL_SRAM_NORMAL - The SRAM is left in fully powered mode, providing
//!   fast wake-up time but higher power consumption.
//! - \b SYSCTL_SRAM_STANDBY - The SRAM is placed into a lower power mode,
//!   providing reduced power consumption but longer wake-up time.
//! - \b SYSCTL_SRAM_LOW_POWER - The SRAM is placed into lowest power mode,
//!   providing further reduced power consumption but longer wake-up time.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlSleepPowerSet(uint32_t ui32Config)
{
    //
    // Set the sleep-mode flash and SRAM power configuration.
    //
    HWREG(SYSCTL_SLPPWRCFG) = ui32Config;
}

//*****************************************************************************
//
//! Configures the power to the flash and SRAM while in deep-sleep mode.
//!
//! \param ui32Config is the required flash and SRAM power configuration.
//!
//! This function allows the power configuration of the flash and SRAM while in
//! deep-sleep mode to be set.  The \e ui32Config parameter is the logical OR
//! of the flash power configuration and the SRAM power configuration.
//!
//! The flash power configuration is specified as either:
//!
//! - \b SYSCTL_FLASH_NORMAL - The flash is left in fully powered mode,
//!    providing fast wake-up time but higher power consumption.
//! - \b SYSCTL_FLASH_LOW_POWER - The flash is in low power mode, providing
//!   reduced power consumption but longer wake-up time.
//!
//! The SRAM power configuration is specified as one of:
//!
//! - \b SYSCTL_LDO_SLEEP - The LDO is in sleep mode.
//! - \b SYSCTL_TEMP_LOW_POWER - The temperature sensor in low power mode.
//! - \b SYSCTL_SRAM_NORMAL - The SRAM is left in fully powered mode, providing
//!   fast wake-up time but higher power consumption.
//! - \b SYSCTL_SRAM_STANDBY - The SRAM is placed into a lower power mode,
//!   providing reduced power consumption but longer wake-up time.
//! - \b SYSCTL_SRAM_LOW_POWER - The SRAM is placed into lowest power mode,
//!   providing further reduced power consumption but longer wake-up time.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleepPowerSet(uint32_t ui32Config)
{
    //
    // Set the deep-sleep-mode flash and SRAM power configuration.
    //
    HWREG(SYSCTL_DSLPPWRCFG) = ui32Config;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a software reset of the entire device.  The
//! processor and all peripherals are reset and all device registers are
//! returned to their default values (with the exception of the reset cause
//! register, which maintains its current value but has the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlReset(void)
{
    //
    // Perform a software reset request.  This request causes the device to
    // reset, no further code is executed.
    //
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while (1)
    {
    }
}

//*****************************************************************************
//
//! Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode; it does not return
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralSleepEnable() continue to operate and can wake up the
//! processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlSleep(void)
{
    //
    // Wait for an interrupt.
    //
    CPUwfi();
}

//*****************************************************************************
//
//! Puts the processor into deep-sleep mode.
//!
//! This function places the processor into deep-sleep mode; it does not return
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralDeepSleepEnable() continue to operate and can wake up
//! the processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleep(void)
{
    //
    // Enable deep-sleep.
    //
    HWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;

    //
    // Wait for an interrupt.
    //
    CPUwfi();

    //
    // Disable deep-sleep so that a future sleep works correctly.
    //
    HWREG(NVIC_SYS_CTRL) &= ~(NVIC_SYS_CTRL_SLEEPDEEP);
}

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function returns the reason(s) for a reset.  Because the reset
//! reasons are sticky until either cleared by software or a power-on reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason is a logical OR of \b SYSCTL_CAUSE_HSRVREQ,
//! \b SYSCTL_CAUSE_HIB, \b SYSCTL_CAUSE_WDOG1, \b SYSCTL_CAUSE_SW,
//! \b SYSCTL_CAUSE_WDOG0, \b SYSCTL_CAUSE_BOR, \b SYSCTL_CAUSE_POR,
//! and/or \b SYSCTL_CAUSE_EXT.
//!
//! \return Returns the reason(s) for a reset.
//
//*****************************************************************************
uint32_t
SysCtlResetCauseGet(void)
{
    //
    // Return the reset reasons.
    //
    return (HWREG(SYSCTL_RESC));
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param ui32Causes are the reset causes to be cleared; must be a logical OR
//! of \b SYSCTL_CAUSE_HSRVREQ, \b SYSCTL_CAUSE_HIB, \b SYSCTL_CAUSE_WDOG1,
//! \b SYSCTL_CAUSE_SW, \b SYSCTL_CAUSE_WDOG0, \b SYSCTL_CAUSE_BOR,
//! \b SYSCTL_CAUSE_POR, and/or \b SYSCTL_CAUSE_EXT.
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtlResetCauseGet().
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlResetCauseClear(uint32_t ui32Causes)
{
    //
    // Clear the given reset reasons.
    //
    HWREG(SYSCTL_RESC) &= ~(ui32Causes);
}

//*****************************************************************************
//
//! Provides a small delay.
//!
//! \param ui32Count is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a delay by executing a simple
//! 3 instruction cycle loop a given number of times.  It is written in
//! assembly to keep the loop instruction count consistent across tool chains.
//!
//! It is important to note that this function does NOT provide an accurate
//! timing mechanism.  Although the delay loop is 3 instruction cycles long,
//! the execution time of the loop will vary dramatically depending upon the
//! application's interrupt environment (the loop will be interrupted unless
//! run with interrupts disabled and this is generally an unwise thing to do)
//! and also the current system clock rate and flash timings (wait states and
//! the operation of the prefetch buffer affect the timing).
//!
//! For better accuracy, the ROM version of this function may be used.  This
//! version will not suffer from flash- and prefect buffer-related timing
//! variability but will still be delayed by interrupt service routines.
//!
//! For best accuracy, a system timer should be used with code either polling
//! for a particular timer value being exceeded or processing the timer
//! interrupt to determine when a particular time period has elapsed.
//!
//! \return None.
//
//*****************************************************************************
#if defined(__ICCARM__) || defined(DOXYGEN)
void
SysCtlDelay(uint32_t ui32Count)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(codered) || defined(__GNUC__) || defined(sourcerygxx)
void __attribute__((naked))
SysCtlDelay(uint32_t ui32Count)
{
    __asm("    subs    r0, #1\n"
          "    bne     SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
SysCtlDelay(uint32_t ui32Count)
{
    subs    r0, #1;
    bne     SysCtlDelay;
    bx      lr;
}
#endif
//
// For CCS implement this function in pure assembly.  This prevents the TI
// compiler from doing funny things with the optimizer.
//
#if defined(__TI_ARM__)
__asm("    .sect \".text:SysCtlDelay\"\n"
      "    .clink\n"
      "    .thumbfunc SysCtlDelay\n"
      "    .thumb\n"
      "    .global SysCtlDelay\n"
      "SysCtlDelay:\n"
      "    subs r0, #1\n"
      "    bne.n SysCtlDelay\n"
      "    bx lr\n");
#endif

//*****************************************************************************
//
//! Sets the configuration of the main oscillator (MOSC) control.
//!
//! \param ui32Config is the required configuration of the MOSC control.
//!
//! This function configures the control of the main oscillator.  The
//! \e ui32Config is specified as the logical OR of the following values:
//!
//! - \b SYSCTL_MOSC_VALIDATE enables the MOSC verification circuit that
//!   detects a failure of the main oscillator (such as a loss of the clock).
//! - \b SYSCTL_MOSC_INTERRUPT indicates that a MOSC failure should generate an
//!   interrupt instead of resetting the processor.
//! - \b SYSCTL_MOSC_NO_XTAL indicates that there is no crystal or oscillator
//!   connected to the OSC0/OSC1 pins, allowing power consumption to be
//!   reduced.
//! - \b SYSCTL_MOSC_PWR_DIS disable power to the main oscillator.  If this
//!   parameter is not specified, the MOSC input remains powered.
//! - \b SYSCTL_MOSC_LOWFREQ MOSC is less than 10 MHz.
//! - \b SYSCTL_MOSC_HIGHFREQ MOSC is greater than 10 MHz.
//! - \b SYSCTL_MOSC_SESRC specifies that the MOSC is a single-ended
//!   oscillator connected to OSC0.  If this parameter is not specified, the
//!   input is assumed to be a crystal.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlMOSCConfigSet(uint32_t ui32Config)
{
    //
    // Configure the MOSC control.
    //
    HWREG(SYSCTL_MOSCCTL) = ui32Config;
}

//*****************************************************************************
//
//! Calibrates the precision internal oscillator.
//!
//! \param ui32Type is the type of calibration to perform.
//!
//! This function performs a calibration of the PIOSC.  There are three types
//! of calibration available; the desired calibration type as specified in
//! \e ui32Type is one of:
//!
//! - \b SYSCTL_PIOSC_CAL_AUTO to perform automatic calibration using the
//!   32-kHz clock from the hibernate module as a reference.  This type is
//!   only possible if the hibernate module is enabled, a 32.768-kHz
//!   clock source is attached to the XOSC0/1 pins and the hibernate module's
//!   RTC is also enabled.
//!
//! - \b SYSCTL_PIOSC_CAL_FACT to reset the PIOSC calibration to the factory
//!   provided calibration.
//!
//! - \b SYSCTL_PIOSC_CAL_USER to set the PIOSC calibration to a user-supplied
//!   value.  The value to be used is ORed into the lower 7-bits of this value,
//!   with 0x40 being the ``nominal'' value (in other words, if everything were
//!   perfect, 0x40 provides exactly 16 MHz).  Values larger than 0x40
//!   slow down PIOSC, and values smaller than 0x40 speed up PIOSC.
//!
//! \return Returns 1 if the calibration was successful and 0 if it failed.
//
//*****************************************************************************
uint32_t
SysCtlPIOSCCalibrate(uint32_t ui32Type)
{
    //
    // Perform the requested calibration.  If performing user calibration, the
    // UTEN bit must be set with one write, then the UT field in a second
    // write, and the UPDATE bit in a final write.  For other calibration
    // types, a single write to set UPDATE or CAL is all that is required.
    //
    if (ui32Type & (SYSCTL_PIOSCCAL_UTEN | SYSCTL_PIOSCCAL_UPDATE))
    {
        HWREG(SYSCTL_PIOSCCAL) = ui32Type & SYSCTL_PIOSCCAL_UTEN;
        HWREG(SYSCTL_PIOSCCAL) =
            ui32Type & (SYSCTL_PIOSCCAL_UTEN | SYSCTL_PIOSCCAL_UT_M);
    }
    HWREG(SYSCTL_PIOSCCAL) = ui32Type;

    //
    // See if an automatic calibration was requested.
    //
    if (ui32Type & SYSCTL_PIOSCCAL_CAL)
    {
        //
        // Wait for the automatic calibration to complete.
        //
        while ((HWREG(SYSCTL_PIOSCSTAT) & SYSCTL_PIOSCSTAT_CR_M) == 0)
        {
        }

        //
        // If the automatic calibration failed, return an error.
        //
        if ((HWREG(SYSCTL_PIOSCSTAT) & SYSCTL_PIOSCSTAT_CR_M) !=
                SYSCTL_PIOSCSTAT_CRPASS)
        {
            return (0);
        }
    }

    //
    // The calibration was successful.
    //
    return (1);
}

//*****************************************************************************
//
//! Sets the type of reset issued due to certain reset events.
//!
//! \param ui32Behavior specifies the types of resets for each of the
//! configurable reset events.
//!
//! This function sets the types of reset issued when a configurable reset
//! event occurs.  The reset events that are configurable are: Watchdog 0 or 1,
//! a brown out and the external RSTn pin.  The valid actions are either a
//! system reset or a full POR sequence. See the technical reference manual for
//! more information on the differences between a full POR and a system reset.
//! All reset behaviors can be configured with a single call using the logical OR
//! of the values defined below. Any reset option that is not specifically set
//! remains configured for its default behavior. Either POR or system reset can
//! be selected for each reset cause.
//!
//! Valid values are logical combinations of the following:
//!
//! - \b SYSCTL_ONRST_WDOG0_POR configures a Watchdog 0 reset to perform a full
//!   POR.
//! - \b SYSCTL_ONRST_WDOG0_SYS configures a Watchdog 0 reset to perform a
//!   system reset.
//! - \b SYSCTL_ONRST_WDOG1_POR configures a Watchdog 1 reset to perform a full
//!   POR.
//! - \b SYSCTL_ONRST_WDOG1_SYS configures a Watchdog 1 reset to perform a
//!   system reset.
//! - \b SYSCTL_ONRST_BOR_POR configures a brown-out reset to perform a full
//!   POR.
//! - \b SYSCTL_ONRST_BOR_SYS configures a brown-out reset to perform a system
//!   reset.
//! - \b SYSCTL_ONRST_EXT_POR configures an external pin reset to perform a
//!   full POR.
//! - \b SYSCTL_ONRST_EXT_SYS configures an external pin reset to perform a
//!   system reset.
//!
//! \b Example: Set Watchdog 0 reset to trigger a POR and a brown-out reset
//! to trigger a system reset while leaving the remaining resets with their
//! default behaviors.
//!
//! \verbatim
//! SysCtlResetBehaviorSet(SYSCTL_ONRST_WDOG0_POR | SYSCTL_ONRST_BOR_SYS);
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlResetBehaviorSet(uint32_t ui32Behavior)
{
    HWREG(SYSCTL_RESBEHAVCTL) = ui32Behavior;
}

//*****************************************************************************
//
//! Returns the current types of reset issued due to reset events.
//!
//! This function returns the types of resets issued when a configurable reset
//! occurs.  The value returned is a logical OR combination of the valid values
//! that are described in the documentation for the \e ui32Behavior parameter
//! of the SysCtlResetBehaviorSet() function.
//!
//! \return The reset behaviors for all configurable resets.
//
//*****************************************************************************
uint32_t
SysCtlResetBehaviorGet(void)
{
    return (HWREG(SYSCTL_RESBEHAVCTL));
}

//*****************************************************************************
//
//! Configures the system clock.
//!
//! \param ui32Config is the required configuration of the device clocking.
//! \param ui32SysClock is the requested processor frequency.
//!
//! This function configures the main system clocking for the device.  The
//! input frequency, oscillator source, whether or not to enable the PLL, and
//! the system clock divider are all configured with this function.  This
//! function configures the system frequency to the closest available divisor
//! of one of the fixed PLL VCO settings provided in the \e ui32Config
//! parameter.  The caller sets the \e ui32SysClock parameter to request the
//! system clock frequency, and this function then attempts to match this using
//! the values provided in the \e ui32Config parameter.  If this function
//! cannot exactly match the requested frequency, it picks the closest
//! frequency that is lower than the requested frequency.  The \e ui32Config
//! parameter provides the remaining configuration options using a set of
//! defines that are a logical OR of several different values, many of which
//! are grouped into sets where only one of the set can be chosen.  This
//! function returns the current system frequency which may not match the
//! requested frequency.
//!
//! If the application is using an external crystal then the frequency is
//! set by using one of the following values:
//! \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_6MHZ, \b SYSCTL_XTAL_8MHZ,
//! \b SYSCTL_XTAL_10MHZ, \b SYSCTL_XTAL_12MHZ, \b SYSCTL_XTAL_16MHZ,
//! \b SYSCTL_XTAL_18MHZ, \b SYSCTL_XTAL_20MHZ, \b SYSCTL_XTAL_24MHZ, or
//! \b SYSCTL_XTAL_25MHz.
//!
//! The oscillator source is chosen with one of the following values:
//!
//! - \b SYSCTL_OSC_MAIN to use an external crystal or oscillator.
//! - \b SYSCTL_OSC_INT to use the 16-MHz precision internal oscillator.
//! - \b SYSCTL_OSC_INT30 to use the internal low frequency oscillator.
//! - \b SYSCTL_OSC_EXT32 to use the hibernate modules 32.786-kHz oscillator.
//!
//! The system clock source is chosen with one of the following values:
//!
//! - \b SYSCTL_USE_PLL is used to select the PLL output as the system clock.
//! - \b SYSCTL_USE_OSC is used to choose one of the oscillators as the
//! system clock.
//!
//! The PLL VCO frequency is chosen with one of the the following values:
//!
//! - \b SYSCTL_CFG_VCO_480 to set the PLL VCO output to 480-MHz
//! - \b SYSCTL_CFG_VCO_320 to set the PLL VCO output to 320-MHz
//!
//! Example: Configure the system clocking to be 40 MHz with a 320-MHz PLL
//! setting using the 16-MHz internal oscillator.
//!
//! \verbatim
//! SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320,
//!                    40000000);
//! \endverbatim
//!
//! \return The actual configured system clock frequency in Hz or zero if the
//! value could not be changed due to a parameter error or PLL lock failure.
//
//*****************************************************************************
uint32_t
SysCtlClockFreqSet(uint32_t ui32Config, uint32_t ui32SysClock)
{
    int32_t i32Timeout, i32VCOIdx, i32XtalIdx;
    uint32_t ui32MOSCCTL;
    uint32_t ui32Delay;
    uint32_t ui32SysDiv, ui32Osc, ui32OscSelect, ui32RSClkConfig;

    //
    // Get the index of the crystal from the ui32Config parameter.
    //
    i32XtalIdx = SysCtlXtalCfgToIndex(ui32Config);

    //
    // Determine which non-PLL source was selected.
    //
    if ((ui32Config & 0x38) == SYSCTL_OSC_INT)
    {
        //
        // Use the nominal frequency for the PIOSC oscillator and set the
        // crystal select.
        //
        ui32Osc = 16000000;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;
        ui32OscSelect |= SYSCTL_RSCLKCFG_PLLSRC_PIOSC;

        //
        // Force the crystal index to the value for 16-MHz.
        //
        i32XtalIdx = SysCtlXtalCfgToIndex(SYSCTL_XTAL_16MHZ);
    }
    else if ((ui32Config & 0x38) == SYSCTL_OSC_INT30)
    {
        //
        // Use the nominal frequency for the low frequency oscillator.
        //
        ui32Osc = 30000;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_LFIOSC;
    }
    else if ((ui32Config & 0x38) == (SYSCTL_OSC_EXT32 & 0x38))
    {
        //
        // Use the RTC frequency.
        //
        ui32Osc = 32768;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_RTC;
    }
    else if ((ui32Config & 0x38) == SYSCTL_OSC_MAIN)
    {
        //
        // Bounds check the source frequency for the main oscillator.  The is
        // because the PLL tables in the g_pppui32XTALtoVCO structure range
        // from 5MHz to 25MHz.
        //
        if ((i32XtalIdx > (SysCtlXtalCfgToIndex(SYSCTL_XTAL_25MHZ))) ||
                (i32XtalIdx < (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ))))
        {
            return (0);
        }

        ui32Osc = g_pui32Xtals[i32XtalIdx];

        //
        // Set the PLL source select to MOSC.
        //
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_MOSC;
        ui32OscSelect |= SYSCTL_RSCLKCFG_PLLSRC_MOSC;

        //
        // Clear MOSC power down, high oscillator range setting, and no crystal
        // present setting.
        //
        ui32MOSCCTL = HWREG(SYSCTL_MOSCCTL) &
                      ~(SYSCTL_MOSCCTL_OSCRNG | SYSCTL_MOSCCTL_PWRDN |
                        SYSCTL_MOSCCTL_NOXTAL);

        //
        // Increase the drive strength for MOSC of 10 MHz and above.
        //
        if (i32XtalIdx >= (SysCtlXtalCfgToIndex(SYSCTL_XTAL_10MHZ) -
                           (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ))))
        {
            ui32MOSCCTL |= SYSCTL_MOSCCTL_OSCRNG;
        }

        HWREG(SYSCTL_MOSCCTL) = ui32MOSCCTL;

        //
        // Timeout using the legacy delay value.
        //
        ui32Delay = 524288;

        while ((HWREG(SYSCTL_RIS) & SYSCTL_RIS_MOSCPUPRIS) == 0)
        {
            ui32Delay--;

            if (ui32Delay == 0)
            {
                break;
            }
        }

        //
        // If the main oscillator failed to start up then do not switch to
        // it and return.
        //
        if (ui32Delay == 0)
        {
            return (0);
        }


    }
    else
    {
        //
        // This was an invalid request because no oscillator source was
        // indicated.
        //
        ui32Osc = 0;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;
    }

    //
    // Check if the running with the PLL enabled was requested.
    //
    if ((ui32Config & SYSCTL_USE_OSC) == SYSCTL_USE_PLL)
    {
        //
        // ui32Config must be SYSCTL_OSC_MAIN or SYSCTL_OSC_INT.
        //
        if (((ui32Config & 0x38) != SYSCTL_OSC_MAIN) &&
                ((ui32Config & 0x38) != SYSCTL_OSC_INT))
        {
            return (0);
        }

        //
        // Get the VCO index out of the ui32Config parameter.
        //
        i32VCOIdx = (ui32Config >> 24) & 7;

        //
        // Check that the VCO index is not out of bounds.
        //
        ASSERT(i32VCOIdx < MAX_VCO_ENTRIES);

        //
        // Set the memory timings for the maximum external frequency since
        // this could be a switch to PIOSC or possibly to MOSC which can be
        // up to 25MHz.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(25000000);

        //
        // Clear the old PLL divider and source in case it was set.
        //
        ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG) &
                          ~(SYSCTL_RSCLKCFG_PSYSDIV_M |
                            SYSCTL_RSCLKCFG_OSCSRC_M |
                            SYSCTL_RSCLKCFG_PLLSRC_M | SYSCTL_RSCLKCFG_USEPLL);

        //
        // Update the memory timings to match running from PIOSC.
        //
        ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

        //
        // Update clock configuration to switch back to PIOSC.
        //
        HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;

        //
        // The table starts at 5 MHz so modify the index to match this.
        //
        i32XtalIdx -= SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ);

        //
        // Calculate the System divider such that we get a frequency that is
        // the closest to the requested frequency without going over.
        //
        ui32SysDiv = (g_pui32VCOFrequencies[i32VCOIdx] + ui32SysClock - 1) /
                     ui32SysClock;

        //
        // Set the oscillator source.
        //
        HWREG(SYSCTL_RSCLKCFG) |= ui32OscSelect;

        //
        // Set the M, N and Q values provided from the table and preserve
        // the power state of the main PLL.
        //
        HWREG(SYSCTL_PLLFREQ1) =
            g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][1];
        HWREG(SYSCTL_PLLFREQ1) |= PLL_Q_TO_REG(ui32SysDiv);
        HWREG(SYSCTL_PLLFREQ0) =
            (g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][0] |
             (HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_PLLPWR));

        //
        // Calculate the actual system clock as PSYSDIV is always div-by 2.
        //
        ui32SysClock = _SysCtlFrequencyGet(ui32Osc) / 2;

        //
        // Set the Flash and EEPROM timing values.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(ui32SysClock);

        //
        // Check if the PLL is already powered up.
        //
        if (HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_PLLPWR)
        {
            //
            // Trigger the PLL to lock to the new frequency.
            //
            HWREG(SYSCTL_RSCLKCFG) |= SYSCTL_RSCLKCFG_NEWFREQ;
        }
        else
        {
            //
            // Power up the PLL.
            //
            HWREG(SYSCTL_PLLFREQ0) |= SYSCTL_PLLFREQ0_PLLPWR;
        }

        //
        // Wait until the PLL has locked.
        //
        for (i32Timeout = 32768; i32Timeout > 0; i32Timeout--)
        {
            if ((HWREG(SYSCTL_PLLSTAT) & SYSCTL_PLLSTAT_LOCK))
            {
                break;
            }
        }

        //
        // If the loop above did not timeout then switch over to the PLL
        //
        if (i32Timeout)
        {
            ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);
            ui32RSClkConfig |= (1 << SYSCTL_RSCLKCFG_PSYSDIV_S) |
                               ui32OscSelect | SYSCTL_RSCLKCFG_USEPLL;
            ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

            //
            // Set the new clock configuration.
            //
            HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;
        }
        else
        {
            ui32SysClock = 0;
        }
    }
    else
    {
        //
        // Set the Flash and EEPROM timing values for PIOSC.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(16000000);

        //
        // Make sure that the PLL is powered down since it is not being used.
        //
        HWREG(SYSCTL_PLLFREQ0) &= ~SYSCTL_PLLFREQ0_PLLPWR;

        //
        // Clear the old PLL divider and source in case it was set.
        //
        ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);
        ui32RSClkConfig &= ~(SYSCTL_RSCLKCFG_OSYSDIV_M |
                             SYSCTL_RSCLKCFG_OSCSRC_M |
                             SYSCTL_RSCLKCFG_USEPLL);

        //
        // Update the memory timings.
        //
        ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

        //
        // Set the new clock configuration.
        //
        HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;

        //
        // If zero given as the system clock then default to divide by 1.
        //
        if (ui32SysClock == 0)
        {
            ui32SysDiv = 0;
        }
        else
        {
            //
            // Calculate the System divider based on the requested
            // frequency.
            //
            ui32SysDiv = ui32Osc / ui32SysClock;

            //
            // If the system divisor is not already zero, subtract one to
            // set the value in the register which requires the value to
            // be n-1.
            //
            if (ui32SysDiv != 0)
            {
                ui32SysDiv -= 1;
            }

            //
            // Calculate the system clock.
            //
            ui32SysClock = ui32Osc / (ui32SysDiv + 1);
        }

        //
        // Set the memory timing values for the new system clock.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(ui32SysClock);

        //
        // Set the new system clock values.
        //
        ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);
        ui32RSClkConfig |= (ui32SysDiv << SYSCTL_RSCLKCFG_OSYSDIV_S) |
                           ui32OscSelect;

        //
        // Update the memory timings.
        //
        ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

        //
        // Set the new clock configuration.
        //
        HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;
    }

    //
    // Finally change the OSCSRC back to PIOSC
    //
    HWREG(SYSCTL_RSCLKCFG) &= ~(SYSCTL_RSCLKCFG_OSCSRC_M);

    return (ui32SysClock);
}

//*****************************************************************************
//
//! Sets the clock configuration of the device while in deep-sleep mode.
//!
//! \param ui32Div is the clock divider when in deep-sleep mode.
//! \param ui32Config is the configuration of the device clocking while
//! in deep-sleep mode.
//!
//! This function configures the clocking of the device while in deep-sleep
//! mode.  The \e ui32Config parameter selects the oscillator and the
//! \e ui32Div parameter sets the clock divider used in deep-sleep mode.  The
//! valid values for the \e ui32Div parameter range from 1 to 1024.
//!
//! The oscillator source is chosen from one of the following values:
//! \b SYSCTL_DSLP_OSC_MAIN, \b SYSCTL_DSLP_OSC_INT, \b SYSCTL_DSLP_OSC_INT30,
//! or \b SYSCTL_DSLP_OSC_EXT32.  The \b SYSCTL_DSLP_OSC_EXT32 option is only
//! available when the hibernation module is enabled.
//!
//! The precision internal oscillator can be powered down in deep-sleep mode by
//! specifying \b SYSCTL_DSLP_PIOSC_PD.  The precision internal oscillator is
//! not powered down if it is required for operation while in deep-sleep
//! (based on other configuration settings).
//!
//! The main oscillator can be powered down in deep-sleep mode by
//! specifying \b SYSCTL_DSLP_MOSC_PD.  The main oscillator is
//! not powered down if it is required for operation while in deep-sleep
//! (based on other configuration settings).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleepClockConfigSet(uint32_t ui32Div, uint32_t ui32Config)
{
    uint32_t ui32Value;

    ASSERT(ui32Div != 0);
    //
    // Initialize the value with the divider.
    //
    ui32Value = ui32Div - 1;

    //
    // Set the clock source selection
    //
    switch (ui32Config & SYSCTL_DSCLKCFG_DSOSCSRC_M)
    {
    //
    // Choose the main external oscillator.
    //
    case SYSCTL_DSLP_OSC_MAIN:
    {
        ui32Value |= SYSCTL_DSCLKCFG_DSOSCSRC_MOSC;

        break;
    }

    //
    // Choose the low frequency oscillator.
    //
    case SYSCTL_DSLP_OSC_INT30:
    {
        ui32Value |= SYSCTL_DSCLKCFG_DSOSCSRC_LFIOSC;

        break;
    }

    //
    // Choose the low frequency oscillator.
    //
    case SYSCTL_DSLP_OSC_EXT32:
    {
        ui32Value |= SYSCTL_DSCLKCFG_DSOSCSRC_RTC;

        break;
    }
    //
    // The zero value uses the PIOSC as the clock source.
    //
    case SYSCTL_DSLP_OSC_INT:
    default:
    {
        break;
    }
    }

    //
    // Set the PIOSC power down bit.
    //
    if (ui32Config & SYSCTL_DSLP_PIOSC_PD)
    {
        ui32Value |= SYSCTL_DSCLKCFG_PIOSCPD;
    }

    //
    // Set the MOSC power down disable bit.
    //
    if (ui32Config & SYSCTL_DSLP_MOSC_DPD)
    {
        ui32Value |= SYSCTL_DSCLKCFG_MOSCDPD;
    }

    //
    // Update the deep-sleep clock configuration.
    //
    HWREG(SYSCTL_DSCLKCFG) = ui32Value;
}

//*****************************************************************************
//
//! Configures the response to system voltage events.
//!
//! \param ui32Config holds the configuration options for the voltage events.
//!
//! This function configures the response to voltage-related events.
//! These events are triggered when the voltage rails drop below certain
//! levels.  The \e ui32Config parameter provides the configuration for the
//! voltage events and is a combination of the \b SYSCTL_VEVENT_* values.
//!
//! The response to a brown out on the VDDA rail is set by using one of the
//! following values:
//! - \b SYSCTL_VEVENT_VDDABO_NONE - There is no action taken on a VDDA
//!      brown out.
//! - \b SYSCTL_VEVENT_VDDABO_INT - A system interrupt is generated when a
//!      VDDA brown out occurs.
//! - \b SYSCTL_VEVENT_VDDABO_NMI - An NMI is generated when a VDDA brown out
//!      occurs.
//! - \b SYSCTL_VEVENT_VDDABO_RST - A reset is generated when a VDDA brown out
//!      occurs.  The type of reset that is generated is controller by the
//!      \b SYSCTL_ONRST_BOR_* setting passed into the SysCtlResetBehaviorSet()
//!      function.
//!
//! The response to a brown out on the VDD rail is set by using one of the
//! following values:
//! - \b SYSCTL_VEVENT_VDDBO_NONE - There is no action taken on a VDD
//!      brown out.
//! - \b SYSCTL_VEVENT_VDDBO_INT - A system interrupt is generated when a
//!      VDD brown out occurs.
//! - \b SYSCTL_VEVENT_VDDBO_NMI - An NMI is generated when a VDD brown out
//!      occurs.
//! - \b SYSCTL_VEVENT_VDDBO_RST - A reset is generated when a VDD brown out
//!      occurs.  The type of reset that is generated is controller by the
//!      \b SYSCTL_ONRST_BOR_* setting passed into the SysCtlResetBehaviorSet()
//!      function.
//!
//! \b Example: Configure the voltage events to trigger an interrupt on a VDDA
//! brown out, an NMI on a VDDC brown out and a reset on a VDD brown out.
//!
//! \verbatim
//!
//! //
//! // Configure the BOR rest to trigger a full POR.  This is needed because
//! // the SysCtlVoltageEventConfig() call is triggering a reset so the type
//! // of reset is specified by this call.
//! //
//! SysCtlResetBehaviorSet(SYSCTL_ONRST_BOR_POR);
//!
//! //
//! // Trigger an interrupt on a VDDA brown out and a reset on a VDD brown out.
//! //
//! SysCtlVoltageEventConfig(SYSCTL_VEVENT_VDDABO_INT |
//!                          SYSCTL_VEVENT_VDDBO_RST);
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlVoltageEventConfig(uint32_t ui32Config)
{
    //
    // Set the requested events.
    //
    HWREG(SYSCTL_PTBOCTL) = ui32Config;
}

//*****************************************************************************
//
//! Returns the voltage event status.
//!
//! This function returns the voltage event status for the system controller.
//! The value returned is a logical OR of the following values:
//! - \b SYSCTL_VESTAT_VDDBOR a brown-out event occurred on the VDD rail.
//! - \b SYSCTL_VESTAT_VDDABOR a brown-out event occurred on the VDDA rail.
//!
//! The values returned from this function can be passed to the
//! SysCtlVoltageEventClear() to clear the current voltage event status.
//! Because voltage events are not cleared due to a reset, the voltage event
//! status must be cleared by calling SysCtlVoltageEventClear().
//!
//! \b Example: Clear the current voltage event status.
//!
//! \verbatim
//! uint32_t ui32VoltageEvents;
//!
//! //
//! // Read the current voltage event status.
//! //
//! ui32VoltageEvents = SysCtlVoltageEventStatus();
//!
//! //
//! // Clear all the current voltage events.
//! //
//! SysCtlVoltageEventClear(ui32VoltageEvents);
//! \endverbatim
//!
//! \return The current voltage event status.
//!
//
//*****************************************************************************
uint32_t
SysCtlVoltageEventStatus(void)
{
    //
    // Return the current voltage event status.
    //
    return (HWREG(SYSCTL_PWRTC));
}

//*****************************************************************************
//
//! Clears the voltage event status.
//!
//! \param ui32Status is a bit mask of the voltage events to clear.
//!
//! This function clears the current voltage events status for the values
//! specified in the \e ui32Status parameter.  The \e ui32Status value must be
//! a logical OR of the following values:
//! - \b SYSCTL_VESTAT_VDDBOR a brown-out event occurred on the VDD rail.
//! - \b SYSCTL_VESTAT_VDDABOR a brown-out event occurred on the VDDA rail.
//!
//! \b Example: Clear the current voltage event status.
//!
//! \verbatim
//! //
//! // Clear all the current voltage events.
//! //
//! SysCtlVoltageEventClear(SysCtlVoltageEventStatus());
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlVoltageEventClear(uint32_t ui32Status)
{
    //
    // Clear the requested voltage events.
    //
    HWREG(SYSCTL_PWRTC) |= ui32Status;
}

//*****************************************************************************
//
//! Gets the effective VCO frequency.
//!
//! \param ui32Crystal holds the crystal value used for the PLL.
//! \param pui32VCOFrequency is a pointer to the storage location which holds
//! value of the VCO computed.
//!
//! This function calculates the VCO of the PLL before the system divider is
//! applied
//!
//! \return \b true if the PLL is configured correctly and a VCO is valid or
//! \b false if the PLL is not used
//
//*****************************************************************************
bool
SysCtlVCOGet(uint32_t ui32Crystal, uint32_t *pui32VCOFrequency)
{
    int32_t i32XtalIdx;
    uint32_t ui32RSClkConfig, ui32PLLFreq0, ui32PLLFreq1, ui32Osc;
    uint32_t ui32MInt, ui32MFrac, ui32NDiv, ui32QDiv, ui32TempVCO;

    //
    // Read the RSCLKCFG register to determine if PLL is being used.
    //
    ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);

    //
    // Check if PLL is used.
    //
    if ((ui32RSClkConfig & SYSCTL_RSCLKCFG_USEPLL) != SYSCTL_RSCLKCFG_USEPLL)
    {
        //
        // Return error if PLL is not used.
        //
        *pui32VCOFrequency = 0;
        return (false);
    }

    //
    // Get the index of the crystal from the ui32Config parameter.
    //
    i32XtalIdx = SysCtlXtalCfgToIndex(ui32Crystal);

    //
    // Get the value of the crystal frequency based on the index
    //
    ui32Osc = g_pui32Xtals[i32XtalIdx];

    //
    // Read the PLLFREQ0 and PLLFREQ1 registers to get information on the
    // MINT, MFRAC, N and Q values of the PLL
    //
    ui32PLLFreq0 = HWREG(SYSCTL_PLLFREQ0);
    ui32PLLFreq1 = HWREG(SYSCTL_PLLFREQ1);

    ui32MInt = (ui32PLLFreq0 & SYSCTL_PLLFREQ0_MINT_M) >>
               SYSCTL_PLLFREQ0_MINT_S;
    ui32MFrac = (ui32PLLFreq0 & SYSCTL_PLLFREQ0_MFRAC_M) >>
                SYSCTL_PLLFREQ0_MFRAC_S;
    ui32NDiv = (ui32PLLFreq1 & SYSCTL_PLLFREQ1_N_M) >>
               SYSCTL_PLLFREQ1_N_S;
    ui32QDiv = (ui32PLLFreq1 & SYSCTL_PLLFREQ1_Q_M) >>
               SYSCTL_PLLFREQ1_Q_S;

    //
    // Calculate the VCO at the output of the PLL
    //
    ui32TempVCO = (ui32Osc * ui32MInt) + ((ui32Osc * ui32MFrac) / 1024);
    ui32TempVCO /= ((ui32NDiv + 1) * (ui32QDiv + 1));

    *pui32VCOFrequency = ui32TempVCO;
    return (true);
}

//*****************************************************************************
//
//! Returns the current NMI status.
//!
//! This function returns the NMI status for the system controller.  The valid
//! values for the \e ui32Ints parameter are a logical OR of the following
//! values:
//! - \b SYSCTL_NMI_MOSCFAIL the main oscillator is not present or did not
//!   start.
//! - \b SYSCTL_NMI_TAMPER a tamper event has been detected.
//! - \b SYSCTL_NMI_WDT0 watchdog 0 generated a timeout.
//! - \b SYSCTL_NMI_WDT1 watchdog 1 generated a timeout.
//! - \b SYSCTL_NMI_POWER a power event occurred.
//! - \b SYSCTL_NMI_EXTERNAL an external NMI pin asserted.
//!
//! \b Example: Clear all current NMI status flags.
//!
//! \verbatim
//!
//! //
//! // Clear all the current NMI sources.
//! //
//! SysCtlNMIClear(SysCtlNMIStatus());
//! \endverbatim
//!
//! \return The current NMI status.
//
//*****************************************************************************
uint32_t
SysCtlNMIStatus(void)
{
    return (HWREG(SYSCTL_NMIC));
}

//*****************************************************************************
//
//! Clears NMI sources.
//!
//! \param ui32Ints is a bit mask of the non-maskable interrupt sources.
//!
//! This function clears the current NMI status specified in the \e ui32Ints
//! parameter.  The valid values for the \e ui32Ints parameter are a logical OR
//! of the following values:
//! - \b SYSCTL_NMI_MOSCFAIL the main oscillator is not present or did not
//!   start.
//! - \b SYSCTL_NMI_TAMPER a tamper event has been detected.
//! - \b SYSCTL_NMI_WDT0 watchdog 0 generated a timeout.
//! - \b SYSCTL_NMI_WDT1 watchdog 1 generated a timeout.
//! - \b SYSCTL_NMI_POWER a power event occurred.
//! - \b SYSCTL_NMI_EXTERNAL an external NMI pin asserted.
//!
//! \b Example: Clear all current NMI status flags.
//!
//! \verbatim
//!
//! //
//! // Clear all the current NMI sources.
//! //
//! SysCtlNMIClear(SysCtlNMIStatus());
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlNMIClear(uint32_t ui32Ints)
{
    //
    // Clear the requested interrupt sources.
    //
    HWREG(SYSCTL_NMIC) &= ~ui32Ints;
}

//*****************************************************************************
//
//! Configures and enables or disables the clock output on the DIVSCLK pin.
//!
//! \param ui32Config holds the configuration options including enabling or
//! disabling the clock output on the DIVSCLK pin.
//! \param ui32Div is the divisor for the clock selected in the \e ui32Config
//! parameter.
//!
//! This function selects the source for the DIVSCLK, enables or disables
//! the clock output and provides an output divider value.  The \e ui32Div
//! parameter specifies the divider for the selected clock source and has a
//! valid range of 1-256.  The \e ui32Config parameter configures
//! the DIVSCLK output based on the following settings:
//!
//! The first setting allows the output to be enabled or disabled.
//! - \b SYSCTL_CLKOUT_EN - enable the DIVSCLK output.
//! - \b SYSCTL_CLKOUT_DIS - disable the DIVSCLK output (default).
//!
//! The next group of settings selects the source for the DIVSCLK.
//! - \b SYSCTL_CLKOUT_SYSCLK - use the current system clock as the
//!      source (default).
//! - \b SYSCTL_CLKOUT_PIOSC - use the PIOSC as the source.
//! - \b SYSCTL_CLKOUT_MOSC - use the MOSC as the source.
//!
//! \b Example: Enable the PIOSC divided by 4 as the DIVSCLK output.
//!
//! \verbatim
//!
//! //
//! // Enable the PIOSC divided by 4 as the DIVSCLK output.
//! //
//! SysCtlClockOutConfig(SYSCTL_DIVSCLK_EN | SYSCTL_DIVSCLK_SRC_PIOSC, 4);
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClockOutConfig(uint32_t ui32Config, uint32_t ui32Div)
{
    ASSERT(ui32Div != 0);
    ASSERT((ui32Config & ~(SYSCTL_CLKOUT_EN | SYSCTL_CLKOUT_DIS |
                           SYSCTL_CLKOUT_SYSCLK | SYSCTL_CLKOUT_PIOSC |
                           SYSCTL_CLKOUT_MOSC)) == 0);

    //
    // Set the requested configuration and divisor.
    //
    HWREG(SYSCTL_DIVSCLK) = ui32Config | ((ui32Div - 1) &
                                          SYSCTL_DIVSCLK_DIV_M);
}

//*****************************************************************************
//
//! Configures the alternate peripheral clock source.
//!
//! \param ui32Config holds the configuration options for the alternate
//! peripheral clock.
//!
//! This function configures the alternate peripheral clock.  The alternate
//! peripheral clock is used to provide a known clock in all operating modes
//! to peripherals that support using the alternate peripheral clock as an
//! input clock.  The \e ui32Config parameter value provides the clock input
//! source using one of the following values:
//! - \b SYSCTL_ALTCLK_PIOSC - use the PIOSC as the alternate clock
//!      source (default).
//! - \b SYSCTL_ALTCLK_RTCOSC - use the Hibernate module RTC clock as the
//!      alternate clock source.
//! - \b SYSCTL_ALTCLK_LFIOSC - use the low-frequency internal oscillator as
//!      the alternate clock source.
//!
//! \b Example: Select the Hibernate module RTC clock as the alternate clock
//! source.
//!
//! \verbatim
//!
//! //
//! // Select the Hibernate module RTC clock as the alternate clock source.
//! //
//! SysCtlAltClkConfig(SYSCTL_ALTCLK_RTCOSC);
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlAltClkConfig(uint32_t ui32Config)
{
    //
    // Set the requested configuration and divisor.
    //
    HWREG(SYSCTL_ALTCLKCFG) = ui32Config;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
