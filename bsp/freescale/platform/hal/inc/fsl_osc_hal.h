/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_OSC_HAL_H__)
#define __FSL_OSC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_OSC_COUNT

/*! @addtogroup osc_hal*/
/*! @{*/

/*! @file fsl_osc_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Oscillator capacitor load configurations.*/
typedef enum _osc_capacitor_config {
    kOscCapacitor2p = OSC_CR_SC2P_MASK,     /*!< 2 pF capacitor load */
    kOscCapacitor4p = OSC_CR_SC4P_MASK,     /*!< 4 pF capacitor load */
    kOscCapacitor8p = OSC_CR_SC8P_MASK,     /*!< 8 pF capacitor load */
    kOscCapacitor16p = OSC_CR_SC16P_MASK    /*!< 16 pF capacitor load */
} osc_capacitor_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name oscillator control APIs*/
/*@{*/

/*!
 * @brief Enables the external reference clock for the oscillator.
 *
 * This function  enables the external reference clock output 
 * for the oscillator, OSCERCLK. This clock is used
 * by many peripherals. It should be enabled at an early system initialization
 * stage to ensure the peripherals can select and use it.
 *
 * @param base Oscillator register base address
 * @param enable   enable/disable the clock
 */
static inline void OSC_HAL_SetExternalRefClkCmd(OSC_Type * base, bool enable)
{
    OSC_BWR_CR_ERCLKEN(base, enable);
}

/*!
 * @brief Gets the external reference clock enable setting for the oscillator.
 *
 * This function gets the external reference clock output enable setting
 * for the oscillator , OSCERCLK. This clock  is used
 * by many peripherals. It should be enabled at an early system initialization
 * stage to ensure the peripherals could select and use it.
 * 
 * @param base Oscillator register base address
 * @return Clock enable/disable setting
 */
static inline bool OSC_HAL_GetExternalRefClkCmd(OSC_Type * base)
{
    return (bool)OSC_BRD_CR_ERCLKEN(base);
}

/*!
 * @brief Enables/disables the external reference clock in stop mode.
 *
 * This function  enables/disables the external reference clock (OSCERCLK) when an
 * MCU enters the stop mode. 
 *
 * @param base Oscillator register base address
 * @param enable   enable/disable setting
 */
static inline void OSC_HAL_SetExternalRefClkInStopModeCmd(OSC_Type * base, bool enable)
{
    OSC_BWR_CR_EREFSTEN(base, enable);
}

/*!
 * @brief Sets the capacitor configuration for the oscillator.
 *
 * This function sets the specified capacitors configuration for the 
 * oscillator. This should be done in the early system level initialization function call
 * based on the system configuration.
 *
 * @param base Oscillator register base address
 * @param bitMask Bit mask for the capacitor load option.
 *
 * Example:
   @code
   // To enable only 2 pF and 8 pF capacitor load, please use like this.
   OSC_HAL_SetCapacitor(OSC, kOscCapacitor2p | kOscCapacitor8p);
   @endcode
 */
void OSC_HAL_SetCapacitor(OSC_Type * base, uint32_t bitMask);

#if FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER
/*!
 * @brief Sets the external reference clock divider.
 *
 * This function sets the divider for the external reference clock.
 *
 * @param base Oscillator register base address
 * @param divider   Divider settings
 */
static inline void OSC_HAL_SetExternalRefClkDiv(OSC_Type * base, uint32_t divider)
{
    OSC_BWR_DIV_ERPS(base, divider);
}

/*!
 * @brief Gets the external reference clock divider.
 *
 * This function gets the divider for the external reference clock.
 *
 * @param base Oscillator register base address
 * @return Divider settings
 */
static inline uint32_t OSC_HAL_GetExternalRefClkDiv(OSC_Type * base)
{
    return OSC_BRD_DIV_ERPS(base);
}
#endif

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_OSC_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

