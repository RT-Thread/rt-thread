//*****************************************************************************
//
//  am_hal_gpio.c
//! @file
//!
//! @brief Functions for interfacing with the GPIO module
//!
//! @addtogroup gpio2 GPIO
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

//*****************************************************************************
//
// Array of function pointers for handling GPIO interrupts.
//
//*****************************************************************************
am_hal_gpio_handler_t am_hal_gpio_ppfnHandlers[64];

//*****************************************************************************
//
//! @brief Read the configuration information for the given pin..
//!
//! @param ui32GPIONum is the GPIO number whose configuration we want to read.
//!
//! This function reads the PADREG, GPIO CFG, and ALTPAD registers for the
//! given GPIO and returns them in the following format:
//!
//! ( (ALTPAD << 16) | (CFG << 8) | PADREG)
//!
//! This is the same format used by the \e am_hal_gpio_pin_config()
//! function-like macro.
//!
//! @return Pin configuration information.
//
//*****************************************************************************
uint32_t
am_hal_gpio_pin_config_read(uint32_t ui32PinNumber)
{
    uint32_t ui32CfgVal, ui32PadregVal, ui32AltPadVal;

    am_hal_debug_assert_msg(ui32PinNumber <= 63, "Invalid GPIO number.");

    ui32CfgVal    = AM_HAL_GPIO_CFG_R(ui32PinNumber);
    ui32PadregVal = AM_HAL_GPIO_PADREG_R(ui32PinNumber);
    ui32AltPadVal = AM_HAL_GPIO_ALTPADREG_R(ui32PinNumber);

    return ( (ui32CfgVal    << CFGVAL_GPIOCFG_S)    |
             (ui32PadregVal << CFGVAL_PADREG_S)     |
             (ui32AltPadVal << CFGVAL_ALTPAD_S) );
}

//*****************************************************************************
//
//! @brief Get the state of ALL GPIOs from the INPUT READ REGISTER.
//!
//! This function retrieves the state of ALL GPIOs from the INPUT READ
//! REGISTER.
//!
//! @return the state for the requested GPIO or -1 for error.
//
//*****************************************************************************
uint64_t
am_hal_gpio_input_read(void)
{
    //
    // Combine upper or lower GPIO words into one 64 bit return value.
    //
    uint64_t ui64RetVal;

    ui64RetVal  = ((uint64_t) AM_REGn(GPIO, 0, RDB)) << 32;
    ui64RetVal |= ((uint64_t) AM_REGn(GPIO, 0, RDA)) << 0;

    return ui64RetVal;
}

//*****************************************************************************
//
//! @brief Get the state of ALL GPIOs from the DATA OUTPUT REGISTER.
//!
//! This function retrieves the state of ALL GPIOs from the DATA OUTPUT
//! REGISTER.
//!
//! @return the state for the requested GPIO or -1 for error.
//
//*****************************************************************************
uint64_t
am_hal_gpio_out_read(void)
{
    //
    // Combine upper or lower GPIO words into one 64 bit return value.
    //
    uint64_t ui64RetVal;

    ui64RetVal  = ((uint64_t) AM_REGn(GPIO, 0, WTB)) << 32;
    ui64RetVal |= ((uint64_t) AM_REGn(GPIO, 0, WTA)) << 0;

    return ui64RetVal;
}

//*****************************************************************************
//
//! @brief Gets the state of one GPIO from the DATA ENABLE REGISTER.
//!
//! @param ui32BitNum - GPIO number.
//!
//! This function gets the state of one GPIO from the DATA ENABLE REGISTER.
//!
//! @return the current state for the requested GPIO.
//
//*****************************************************************************
uint32_t
am_hal_gpio_out_enable_bit_get(uint32_t ui32BitNum)
{
    //
    // Return 0 or 1.
    //

    return (AM_HAL_GPIO_EN(ui32BitNum) & AM_HAL_GPIO_EN_M(ui32BitNum)) ? 1 : 0;
}

//*****************************************************************************
//
//! @brief Gets the state of ALL GPIOs from the DATA ENABLE REGISTER.
//!
//! @param ui32BitNum - GPIO number.
//!
//! This function gets the state of all GPIOs from the DATA ENABLE REGISTER.
//!
//! @return the current state for the ALL GPIOs.
//
//*****************************************************************************
uint64_t
am_hal_gpio_out_enable_get(void)
{
    //
    // Combine upper or lower GPIO words into one 64 bit return value.
    //
    uint64_t ui64RetVal;

    ui64RetVal  = ((uint64_t) AM_REGn(GPIO, 0, ENB)) << 32;
    ui64RetVal |= ((uint64_t) AM_REGn(GPIO, 0, ENA)) << 0;

    return ui64RetVal;
}

//*****************************************************************************
//
//! @brief Enable selected GPIO Interrupts.
//!
//! @param ui64InterruptMask - GPIOs to enable interrupts on.
//!
//! Use this function to enable the GPIO interrupts.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_gpio_int_enable(uint64_t ui64InterruptMask)
{
    //
    // Enable the interrupts.
    //
    AM_REG(GPIO, INT1EN) |= (ui64InterruptMask >> 32);
    AM_REG(GPIO, INT0EN) |= (ui64InterruptMask & 0xFFFFFFFF);
}

//*****************************************************************************
//
//! @brief Enable selected GPIO Interrupts.
//!
//! Use this function to enable the GPIO interrupts.
//!
//! @return logical or of all enabled interrupts. Use AM_HAL_GPIO_BITx to mask
//! interrupts of interest.
//
//*****************************************************************************
uint64_t
am_hal_gpio_int_enable_get(void)
{
    //
    // Return enabled interrupts.
    //
    uint64_t ui64RetVal;

    ui64RetVal  = ((uint64_t) AM_REGn(GPIO, 0, INT1EN)) << 32;
    ui64RetVal |= ((uint64_t) AM_REGn(GPIO, 0, INT0EN)) << 0;

    return ui64RetVal;
}

//*****************************************************************************
//
//! @brief Disable selected GPIO Interrupts.
//!
//! @param ui64InterruptMask - GPIOs to disable interrupts on.
//!
//! Use this function to disable the GPIO interrupts.
//!
//! ui64InterruptMask should be a logical or of AM_HAL_GPIO_BITx defines.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_gpio_int_disable(uint64_t ui64InterruptMask)
{
    //
    // Disable the interrupts.
    //
    AM_CRITICAL_BEGIN_ASM
    AM_REG(GPIO, INT1EN) &= ~(ui64InterruptMask >> 32);
    AM_REG(GPIO, INT0EN) &= ~(ui64InterruptMask & 0xFFFFFFFF);
    AM_CRITICAL_END_ASM
}

//*****************************************************************************
//
//! @brief Clear selected GPIO Interrupts.
//!
//! @param ui64InterruptMask - GPIOs to clear interrupts on.
//!
//! Use this function to clear the GPIO interrupts.
//!
//! ui64InterruptMask should be a logical or of AM_HAL_GPIO_BITx defines.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_gpio_int_clear(uint64_t ui64InterruptMask)
{
    //
    // Clear the interrupts.
    //
    AM_CRITICAL_BEGIN_ASM
    AM_REG(GPIO, INT1CLR) = (ui64InterruptMask >> 32);
    AM_REG(GPIO, INT0CLR) = (ui64InterruptMask & 0xFFFFFFFF);
    AM_CRITICAL_END_ASM
}

//*****************************************************************************
//
//! @brief Set selected GPIO Interrupts.
//!
//! @param ui64InterruptMask - GPIOs to set interrupts on.
//!
//! Use this function to set the GPIO interrupts.
//!
//! ui64InterruptMask should be a logical or of AM_HAL_GPIO_BITx defines.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_gpio_int_set(uint64_t ui64InterruptMask)
{
    //
    // Set the interrupts.
    //
    AM_REG(GPIO, INT1SET) = (ui64InterruptMask >> 32);
    AM_REG(GPIO, INT0SET) = (ui64InterruptMask & 0xFFFFFFFF);
}

//*****************************************************************************
//
//! @brief Set selected GPIO Interrupts.
//!
//! @param bEnabledOnly - return the status of only the enabled interrupts.
//!
//! Use this function to set the GPIO interrupts.
//!
//! @return None
//
//*****************************************************************************
uint64_t
am_hal_gpio_int_status_get(bool bEnabledOnly)
{
    uint64_t ui64RetVal, ui64Mask;

    //
    // Combine upper or lower GPIO words into one 64 bit return value.
    //
    ui64Mask   = 0xFFFFFFFFFFFFFFFF;

    AM_CRITICAL_BEGIN_ASM
    ui64RetVal  = ((uint64_t) AM_REGn(GPIO, 0, INT1STAT)) << 32;
    ui64RetVal |= ((uint64_t) AM_REGn(GPIO, 0, INT0STAT)) << 0;

    if ( bEnabledOnly )
    {
        ui64Mask    = ((uint64_t) AM_REGn(GPIO, 0, INT1EN)) << 32;
        ui64Mask   |= ((uint64_t) AM_REGn(GPIO, 0, INT0EN)) << 0;
    }

    ui64RetVal &= ui64Mask;
    AM_CRITICAL_END_ASM

    return ui64RetVal;
}

//*****************************************************************************
//
//! @brief Convenience function for responding to pin interrupts.
//!
//! @param ui64Status is the interrupt status as returned by
//! am_hal_gpio_int_status_get()
//!
//! This function may be called from am_hal_gpio_isr() to read the status of
//! the GPIO interrupts, determine which pin(s) caused the most recent
//! interrupt, and call an interrupt handler function to respond. The interrupt
//! handler to be called must be first registered with the
//! am_hal_gpio_int_register() function.
//!
//! In the event that multiple GPIO interrupts are active, the corresponding
//! interrupt handlers will be called in numerical order by GPIO number
//! starting with the lowest GPIO number.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_gpio_int_service(uint64_t ui64Status)
{
    uint32_t ui32Status;
    uint32_t ui32Clz;

    am_hal_gpio_handler_t pfnHandler;

    //
    // Handle any active interrupts in the lower 32 bits
    //
    ui32Status = (uint32_t) ui64Status;
    while ( ui32Status )
    {
        //
        // Pick one of any remaining active interrupt bits
        //
#ifdef __IAR_SYSTEMS_ICC__
        ui32Clz = __CLZ(ui32Status);
#else
        ui32Clz = __builtin_clz(ui32Status);
#endif

        //
        // Turn off the bit we picked in the working copy
        //
        ui32Status &= ~(0x80000000 >> ui32Clz);

        //
        // Check the bit handler table to see if there is an interrupt handler
        // registered for this particular bit.
        //
        pfnHandler = am_hal_gpio_ppfnHandlers[31 - ui32Clz];
        if ( pfnHandler )
        {
            //
            // If we found an interrupt handler routine, call it now.
            //
            pfnHandler();
        }
    }

    //
    // Handle any active interrupts in the upper 32 bits
    //
    ui32Status = (uint32_t) (ui64Status >> 32);
    while ( ui32Status )
    {
        //
        // Pick one of any remaining active interrupt bits
        //
#ifdef __IAR_SYSTEMS_ICC__
        ui32Clz = __CLZ(ui32Status);
#else
        ui32Clz = __builtin_clz(ui32Status);
#endif

        //
        // Turn off the bit we picked in the working copy
        //
        ui32Status &= ~(0x80000000 >> ui32Clz);

        //
        // Check the bit handler table to see if there is an interrupt handler
        // registered for this particular bit.
        //
        pfnHandler = am_hal_gpio_ppfnHandlers[63 - ui32Clz];
        if ( pfnHandler )
        {
            //
            // If we found an interrupt handler routine, call it now.
            //
            pfnHandler();
        }
    }
}

//*****************************************************************************
//
//! @brief Register an interrupt handler for an individual GPIO pin.
//!
//! @param ui32GPIONumber - GPIO number to assign this interrupt handler to.
//! @param pfnHandler - Function to call when this GPIO interrupt is received.
//!
//! This function allows the caller to specify a function that should be called
//! any time a GPIO interrupt is received on a particular pin. Registering an
//! interrupt handler using this function adds the function pointer to an array
//! in SRAM. This interrupt handler will be called by am_hal_gpio_int_service()
//! whenever the ui64Status parameter indicates that the corresponding pin is
//! asserting it's interrupt.
//!
//! To remove an interrupt handler that has already been registered, the
//! pfnHandler parameter may be set to zero.
//!
//! @note This function will not have any effect unless the
//! am_hal_gpio_int_service() function is being used.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_gpio_int_register(uint32_t ui32GPIONumber,
                         am_hal_gpio_handler_t pfnHandler)
{
    //
    // Check to make sure the GPIO number is valid. (Debug builds only)
    //
    am_hal_debug_assert_msg(ui32GPIONumber < 64, "GPIO number out of range.");

    am_hal_gpio_ppfnHandlers[ui32GPIONumber] = pfnHandler;
}

//*****************************************************************************
//
//! @brief Get the state of one GPIO polarity bit.
//!
//! @param ui32BitNum - GPIO number.
//!
//! This function gets the state of one GPIO polarity bit.
//!
//! @note When the bit is a zero the interrupt polarity is rising edge.
//!
//! @return the current polarity.
//
//*****************************************************************************
bool
am_hal_gpio_int_polarity_bit_get(uint32_t ui32BitNum)
{
    //
    // Check the GPIO_CFGx register's interrupt polarity bit corresponding to
    // this pin number.
    //
    return (AM_REGVAL(AM_HAL_GPIO_CFG(ui32BitNum)) &
            AM_HAL_GPIO_POL_M(ui32BitNum));
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
