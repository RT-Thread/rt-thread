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
#ifndef __FSL_GPIO_HAL_H__
#define __FSL_GPIO_HAL_H__
 
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
 
/*!
 * @addtogroup gpio_hal
 * @{
 */

/*!
 * @file fsl_gpio_hal.h
 *
 * @brief GPIO hardware driver configuration. Use these functions to set the GPIO input/output, 
 * set output logic or get input logic. Check the GPIO header file for base pointer. Each 
 * GPIO instance has 32 pins with numbers from 0 to 31.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief GPIO direction definition*/
typedef enum _gpio_pin_direction {
    kGpioDigitalInput  = 0U, /*!< Set current pin as digital input*/
    kGpioDigitalOutput = 1U  /*!< Set current pin as digital output*/
} gpio_pin_direction_t;

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Sets the individual GPIO pin to general input or output.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.) 
 * @param pin  GPIO port pin number 
 * @param direction  GPIO directions
 *        - kGpioDigitalInput: set to input
 *        - kGpioDigitalOutput: set to output
 */
void GPIO_HAL_SetPinDir(GPIO_Type * base, uint32_t pin,
                        gpio_pin_direction_t direction);

/*!
 * @brief Sets the GPIO port pins to general input or output.
 *
 * This function  operates all 32 port pins.
 * 
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pinDirectionMap  GPIO directions bit map
 *        - 0: set to input
 *        - 1: set to output
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_SetPortDir(GPIO_Type * base, uint32_t pinDirectionMap)
{
    GPIO_WR_PDDR(base, pinDirectionMap);
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the current direction of the individual GPIO pin.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 * @return GPIO directions
 *        - kGpioDigitalInput: corresponding pin is set to input.
 *        - kGpioDigitalOutput: corresponding pin is set to output.
 */
static inline gpio_pin_direction_t GPIO_HAL_GetPinDir(GPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    return (gpio_pin_direction_t)((GPIO_RD_PDDR(base) >> pin) & 1U);
} 

/*!
 * @brief Gets the GPIO port pins direction.
 *
 * This function  gets all 32-pin directions as a 32-bit integer.
 * 
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO directions. Each bit represents one pin. For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline uint32_t GPIO_HAL_GetPortDir(GPIO_Type * base)
{
    return GPIO_RD_PDDR(base);
} 

/* @} */

/*!
 * @name Output Operation
 * @{
 */

/*!
 * @brief Sets the output level of the individual GPIO pin to logic 1 or 0.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 * @param output  pin output logic level
 */
void GPIO_HAL_WritePinOutput(GPIO_Type * base, uint32_t pin, uint32_t output);

/*!
 * @brief Reads the current pin output.
 * 
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 * @return current pin output status. 0 - Low logic, 1 - High logic
 */
static inline uint32_t GPIO_HAL_ReadPinOutput(GPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    return ((GPIO_RD_PDOR(base) >> pin) & 0x1U);
}

/*!
 * @brief Sets the output level of the individual GPIO pin to logic 1.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 */
static inline void GPIO_HAL_SetPinOutput(GPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    GPIO_WR_PSOR(base, 1U << pin);
}

/*!
 * @brief Clears the output level of the individual GPIO pin to logic 0.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 */
static inline void GPIO_HAL_ClearPinOutput(GPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    GPIO_WR_PCOR(base, 1U << pin);
}

/*!
 * @brief Reverses the current output logic of the individual GPIO pin.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 */
static inline void GPIO_HAL_TogglePinOutput(GPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    GPIO_WR_PTOR(base, 1U << pin);
}

/*!
 * @brief Sets the output of the GPIO port pins to a specific logic value.
 *
 * This function  operates all 32 port pins.
 * 
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.) 
 * @param portOutput  data to configure the GPIO output. Each bit represents one pin. For each bit:
 *        - 0: set logic level 0 to pin
 *        - 1: set logic level 1 to pin
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_WritePortOutput(GPIO_Type * base, uint32_t portOutput)
{
    GPIO_WR_PDOR(base, portOutput);
}

/*!
 * @brief Reads out all pin output status of the current port.
 *
 * This function  operates all 32 port pins.
 * 
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.) 
 * @return current port output status. Each bit represents one pin. For each bit:
 *        - 0: corresponding pin is outputting logic level 0
 *        - 1: corresponding pin is outputting logic level 1
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline uint32_t GPIO_HAL_ReadPortOutput(GPIO_Type * base)
{
    return GPIO_RD_PDOR(base);
}

/*!
 * @brief Sets the output level of the GPIO port pins to logic 1.
 *
 * This function  operates all 32 port pins.
 *
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param portOutput GPIO output port pin mask. Each bit represents one pin. For each bit:
 *        - 0: pin output will not be changed.
 *        - 1: pin output will be set to logic level 1
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_SetPortOutput(GPIO_Type * base, uint32_t portOutput)
{
    GPIO_WR_PSOR(base, portOutput);
}

/*!
 * @brief Clears the output level of the GPIO port pins to logic 0.
 * 
 * This function  operates all 32 port pins.
 *
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param portOutput  mask of GPIO output pins. Each bit represents one pin. For each bit:
 *        - 0: pin output will not be changed.
 *        - 1: pin output will be set to logic level 0
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_ClearPortOutput(GPIO_Type * base, uint32_t portOutput)
{
    GPIO_WR_PCOR(base, portOutput);
}

/*!
 * @brief Reverses the current output logic of the GPIO port pins.
 * 
 * This function  operates all 32 port pins.
 *
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param portOutput  mask of GPIO output pins. Each bit represents one pin. For each bit:
 *        - 0: pin output will not be changed.
 *        - 1: pin output logic level will be reversed.
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_TogglePortOutput(GPIO_Type * base, uint32_t portOutput)
{
    GPIO_WR_PTOR(base, portOutput);
}

/* @} */

/*!
 * @name Input Operation
 * @{
 */

/*!
 * @brief Reads the current input value of the individual GPIO pin.
 * 
 * @param base  GPIO base pointer(PTA, PTB, PTC, etc.)
 * @param pin  GPIO port pin number
 * @return GPIO port input value
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1
 */
static inline uint32_t GPIO_HAL_ReadPinInput(GPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    return (GPIO_RD_PDIR(base) >> pin) & 1U;
}

/*!
 * @brief Reads the current input value of a specific GPIO port.
 *
 * This function  gets all 32-pin input as a 32-bit integer.
 * 
 * @param base GPIO base pointer(PTA, PTB, PTC, etc.)
 * @return GPIO port input data. Each bit represents one pin. For each bit:
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 *         - LSB: pin 0
 *         - MSB: pin 31
 */
static inline uint32_t GPIO_HAL_ReadPortInput(GPIO_Type * base)
{
    return GPIO_RD_PDIR(base);
}

/* @} */

/*!
 * @name FGPIO Operation
 *
 * @note FGPIO (Fast GPIO) is only available in a few MCUs. FGPIO and GPIO share the same
 *       peripheral but use different registers. FGPIO is closer to the core than the regular GPIO
 *       and it's faster to read and write.
 * @{
 */

#if FSL_FEATURE_GPIO_HAS_FAST_GPIO

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Sets the individual FGPIO pin to general input or output.
 *
 * @param base FGPIO base pointer(FPTA, FPTB, FPTC, etc.) 
 * @param pin  FGPIO port pin number 
 * @param direction  FGPIO directions
 *        - kGpioDigitalInput: set to input
 *        - kGpioDigitalOutput: set to output
 */
void FGPIO_HAL_SetPinDir(FGPIO_Type * base, uint32_t pin,
                        gpio_pin_direction_t direction);

/*!
 * @brief Sets the FGPIO port pins to general input or output.
 *
 * This function  operates all 32 port pins.
 *
 * @param base  FGPIO base pointer (FPTA, FPTB, FPTC, etc.)
 * @param pinDirectionMap  FGPIO directions bit map
 *        - 0: set to input
 *        - 1: set to output
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void FGPIO_HAL_SetPortDir(FGPIO_Type * base, uint32_t pinDirectionMap)
{
    FGPIO_WR_PDDR(base, pinDirectionMap);
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the current direction of the individual FGPIO pin.
 * 
 * @param base  FGPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 * @return FGPIO directions
 *        - kGpioDigitalInput: corresponding pin is set to input.
 *        - kGpioDigitalOutput: corresponding pin is set to output.
 */
static inline gpio_pin_direction_t FGPIO_HAL_GetPinDir(FGPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    return (gpio_pin_direction_t)((FGPIO_RD_PDDR(base) >> pin) & 1U);
} 

/*!
 * @brief Gets the FGPIO port pins direction.
 *
 * This function  gets all 32-pin directions as a 32-bit integer.
 * 
 * @param base  FGPIO base pointer (FPTA, FPTB, FPTC, etc.)
 * @return FGPIO directions. Each bit represents one pin. For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline uint32_t FGPIO_HAL_GetPortDir(FGPIO_Type * base)
{
    return FGPIO_RD_PDDR(base);
}

/* @} */

/*!
 * @name Output Operation
 * @{
 */

/*!
 * @brief Sets the output level of the individual FGPIO pin to logic 1 or 0.
 * 
 * @param base  FGPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 * @param output  pin output logic level
 */
void FGPIO_HAL_WritePinOutput(FGPIO_Type * base, uint32_t pin, uint32_t output);

/*!
 * @brief Reads the current FGPIOpin output.
 * 
 * @param base  FGPIO base pointer (FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 * @return current pin output status. 0 - Low logic, 1 - High logic
 */
static inline uint32_t FGPIO_HAL_ReadPinOutput(FGPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    return ((FGPIO_RD_PDOR(base) >> pin) & 0x1U);
}

/*!
 * @brief Sets the output level of an individual FGPIO pin to logic 1.
 * 
 * @param base  GPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 */
static inline void FGPIO_HAL_SetPinOutput(FGPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    FGPIO_WR_PSOR(base, 1U << pin);
}

/*!
 * @brief Clears the output level of an individual FGPIO pin to logic 0.
 * 
 * @param base  GPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 */
static inline void FGPIO_HAL_ClearPinOutput(FGPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    FGPIO_WR_PCOR(base, 1U << pin);
}

/*!
 * @brief Reverses the current output logic of an individual FGPIO pin.
 * 
 * @param base  GPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 */
static inline void FGPIO_HAL_TogglePinOutput(FGPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    FGPIO_WR_PTOR(base, 1U << pin);
}

/*!
 * @brief Sets the output of the FGPIO port pins to a specific logic value. 
 *
 * This function  affects all 32 port pins.
 * 
 * @param base  GPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param portOutput  data to configure the GPIO output. Each bit represents one pin. For each bit:
 *        - 0: set logic level 0 to pin.
 *        - 1: set logic level 1 to pin.
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void FGPIO_HAL_WritePortOutput(FGPIO_Type * base, uint32_t portOutput)
{
    FGPIO_WR_PDOR(base, portOutput);
}

/*!
 * @brief Reads out all pin output status of the current port.
 *
 * This function  operates all 32 port pins.
 * 
 * @param base  FGPIO base pointer (FPTA, FPTB, FPTC, etc.) 
 * @return current port output status. Each bit represents one pin. For each bit:
 *        - 0: corresponding pin is outputting logic level 0
 *        - 1: corresponding pin is outputting logic level 1
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline uint32_t FGPIO_HAL_ReadPortOutput(FGPIO_Type * base)
{
    return FGPIO_RD_PDOR(base);
}

/*!
 * @brief Sets the output level of the FGPIO port pins to logic 1.
 *
 * This function  affects all 32 port pins.
 *
 * @param base  FGPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param portOutput  mask of FGPIO output pins. Each bit represents one pin. For each bit:
 *        - 0: pin output will not be changed.
 *        - 1: pin output will be set to logic level 1
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void FGPIO_HAL_SetPortOutput(FGPIO_Type * base, uint32_t portOutput)
{
    FGPIO_WR_PSOR(base, portOutput);
}

/*!
 * @brief Clears the output level of the FGPIO port pins to logic 0.
 *
 * This function  affects all 32 port pins.
 *
 * @param base  FGPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param portOutput  mask of FGPIO output pins. Each bit represents one pin. For each bit:
 *        - 0: pin output will not be changed.
 *        - 1: pin output will be set to logic level 0
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void FGPIO_HAL_ClearPortOutput(FGPIO_Type * base, uint32_t portOutput)
{
    FGPIO_WR_PCOR(base, portOutput);
}

/*!
 * @brief Reverses the current output logic of the FGPIO port pins.
 *
 * This function  affects all 32 port pins.
 * 
 * @param base  FGPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param portOutput  mask of FGPIO output pins. Each bit represents one pin. For each bit:
 *        - 0: pin output will not be changed.
 *        - 1: pin output logic level will be reversed.
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void FGPIO_HAL_TogglePortOutput(FGPIO_Type * base, uint32_t portOutput)
{
    FGPIO_WR_PTOR(base, portOutput);
}

/* @} */

/*!
 * @name Input Operation
 * @{ 
 */

/*!
 * @brief Gets the current input value of an individual FGPIO pin.
 * 
 * @param base  GPIO base pointer(FPTA, FPTB, FPTC, etc.)
 * @param pin  FGPIO port pin number
 * @return FGPIO port input data
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 */
static inline uint32_t FGPIO_HAL_ReadPinInput(FGPIO_Type * base, uint32_t pin)
{
    assert(pin < 32);
    return (FGPIO_RD_PDIR(base) >> pin) & 1U;
}

/*!
 * @brief Gets the current input value of a specific FGPIO port.
 *
 * This function  gets all 32-pin input as a 32-bit integer.
 * 
 * @param base  GPIO base pointer(FPTA, FPTB, FPTC, etc.). 
 * @return FGPIO port input data. Each bit represents one pin. For each bit:
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 *         - LSB: pin 0
 *         - MSB: pin 31
 */
static inline uint32_t FGPIO_HAL_ReadPortInput(FGPIO_Type * base)
{
    return FGPIO_RD_PDIR(base);
}

/* @} */

#endif /* FSL_FEATURE_GPIO_HAS_FAST_GPIO*/

#if defined(__cplusplus)
}
#endif
 
/*! @} */
 
#endif /* __FSL_GPIO_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/


