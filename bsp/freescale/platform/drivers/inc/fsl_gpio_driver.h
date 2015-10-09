/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#ifndef __FSL_GPIO_DRIVER_H__
#define __FSL_GPIO_DRIVER_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"

/*!
 * @addtogroup gpio_driver
 * @{
 */

/*!
 * @file
 *
 * The GPIO driver uses the virtual GPIO name rather than an actual port and a
 * pin number. By using the virtual name, each pin name is self-explanatory.
 * To use the GPIO driver, an enumeration variable must be predefined in the
 * user application files. The variable saves all GPIO pin information used
 * in a project.
 *
 * This example shows how to define the enumeration variable.
   @code
   // This is the enumeration to define virtual GPIO pin names.
   // These members are used by "uint32_t pinName" in
   // gpio_output_pin_user_config_t
   // and gpio_input_pin_user_config_t. Usually defined in a header file.
   enum _gpio_pins
   {
       kGpioLED1  = GPIO_MAKE_PIN(GPIOA_IDX, 5), // Orange LED.
       kGpioLED2  = GPIO_MAKE_PIN(GPIOA_IDX, 6), // Yellow LED.
       kGpioLED3  = GPIO_MAKE_PIN(GPIOA_IDX, 7), // Green LED.
       kGpioLED4  = GPIO_MAKE_PIN(GPIOB_IDX, 8), // Red LED.
   };
   @endcode
 *
 * The port features such as "digital filter", "pull", are valid when
 * they are available in one of the pins. That doesn't mean, however, that all pins have the
 * capability to use such features. See the related reference manual for
 * accurate pin features.
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for GPIO instances. */
extern GPIO_Type * const g_gpioBase[GPIO_INSTANCE_COUNT];

/*! @brief Table of base addresses for PORT instances. */
extern PORT_Type * const g_portBase[PORT_INSTANCE_COUNT];

/* Table to save PORT IRQ enumeration numbers defined in CMSIS header file */
extern const IRQn_Type g_portIrqId[PORT_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name GPIO Pin Macros
 * @{
 */

/*! @brief Indicates the end of a pin configuration structure.*/
#define GPIO_PINS_OUT_OF_RANGE (0xFFFFFFFFU)

/*! @brief Bits shifted for the GPIO port number. */
#define GPIO_PORT_SHIFT (0x8U)

/*! @brief Combines the port number and the pin number into a single scalar value. */
#define GPIO_MAKE_PIN(r,p) (((r)<< GPIO_PORT_SHIFT) | (p))

/*! @brief Extracts the port number from a combined port and pin value.*/
#define GPIO_EXTRACT_PORT(v) (((v) >> GPIO_PORT_SHIFT) & 0xFFU)

/*! @brief Extracts the pin number from a combined port and pin value.*/
#define GPIO_EXTRACT_PIN(v) ((v) & 0xFFU)

/* @} */

/*!
 * @brief The GPIO input pin configuration structure.
 *
 * Although every pin is configurable, valid configurations depend on a specific
 * device. Users should check the related reference manual to ensure that the
 * specific feature is valid in an individual pin. A configuration of
 * unavailable features is harmless, but takes no effect.
 */
typedef struct GpioInputPin {
    #if FSL_FEATURE_PORT_HAS_PULL_ENABLE
    bool isPullEnable;                  /*!< Enable or disable pull. */
    #endif
    #if FSL_FEATURE_PORT_HAS_PULL_SELECTION
    port_pull_t pullSelect;             /*!< Select internal pull(up/down) resistor.*/
    #endif
    #if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
    bool isPassiveFilterEnabled;        /*!< Enable or disable passive filter.*/
    #endif
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
    /* Digital filter clock source and width should be pre-configured using the port HAL.*/
    bool isDigitalFilterEnabled;        /*!< Enable or disable digital filter.*/
    #endif
    #if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
    port_interrupt_config_t interrupt;  /*!< Select interrupt/DMA request.*/
    #endif
} gpio_input_pin_t;

/*!
 * @brief The GPIO output pin configuration structure.
 *
 * Although every pin is configurable, valid configurations
 * depend on a specific device. Users should check the related reference manual to
 * ensure that the specific feature is valid in an individual pin. The configuration of
 * unavailable features is harmless, but takes no effect.
 */
typedef struct GpioOutputPin {
    uint32_t outputLogic;               /*!< Set default output logic.*/
    #if FSL_FEATURE_PORT_HAS_SLEW_RATE
    port_slew_rate_t slewRate;          /*! Select fast/slow slew rate.*/
    #endif
    #if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
    port_drive_strength_t driveStrength;/*!< Select low/high drive strength.*/
    #endif
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    bool isOpenDrainEnabled;            /*!< Enable or disable open drain.*/
    #endif
} gpio_output_pin_t;

/*!
 * @brief The GPIO input pin structure.
 *
 * Although the pinName is defined as a uint32_t type, values assigned to the pinName
 * should be the enumeration names defined in the enum _gpio_pins.
 */
typedef struct GpioInputPinUserConfig {
    uint32_t pinName;        /*!< Virtual pin name from enumeration defined by the user.*/
    gpio_input_pin_t config; /*!< Input pin configuration structure.*/
} gpio_input_pin_user_config_t;

/*!
 * @brief The GPIO output pin structure.
 *
 * Although the pinName is defined as a uint32_t type, values assigned to the pinName
 * should be the enumeration names defined in the enum _gpio_pins.
 */
typedef struct GpioOutputPinUserConfig {
    uint32_t pinName;        /*!< Virtual pin name from enumeration defined by the user.*/
    gpio_output_pin_t config;/*!< Input pin configuration structure.*/
} gpio_output_pin_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes all GPIO pins used by the board.
 *
 * To initialize the GPIO driver, define two arrays similar to the gpio_input_pin_user_config_t
 * inputPin[] array and the gpio_output_pin_user_config_t outputPin[] array in the user file.
 * Then, call the GPIO_DRV_Init() function and pass in the two arrays. If the input or output
 * pins are not needed, pass in a NULL.
 *
 * This is an example to define an input pin array:
   @code
   // Configure the kGpioPTA2 as digital input.
   gpio_input_pin_user_config_t inputPin[] = {
     {
         .pinName = kGpioPTA2,
         .config.isPullEnable = false,
         .config.pullSelect = kPortPullDown,
         .config.isPassiveFilterEnabled = false,
         .config.interrupt = kPortIntDisabled,
     },
     {
        // Note: This pinName must be defined here to indicate the end of the array.
        .pinName = GPIO_PINS_OUT_OF_RANGE,
     }
   };
   @endcode
 *
 * @param inputPins input GPIO pins pointer.
 * @param outputPins output GPIO pins pointer.
 */
void GPIO_DRV_Init(const gpio_input_pin_user_config_t * inputPins,
                   const gpio_output_pin_user_config_t * outputPins);

/*!
 * @brief Initializes one GPIO input pin used by the board.
 *
 * @param inputPin input GPIO pins pointer.
 */
void GPIO_DRV_InputPinInit(const gpio_input_pin_user_config_t *inputPin);

/*!
 * @brief Initializes one GPIO output pin used by the board.
 *
 * @param outputPin output GPIO pins pointer.
 */
void GPIO_DRV_OutputPinInit(const gpio_output_pin_user_config_t *outputPin);

/* @} */

/*!
 * @name Pin Direction
 * @{
 */

/*!
 * @brief Gets the current direction of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @return GPIO directions.
 *         - kGpioDigitalInput: corresponding pin is set as digital input.
 *         - kGpioDigitalOutput: corresponding pin is set as digital output.
 */
gpio_pin_direction_t GPIO_DRV_GetPinDir(uint32_t pinName);

/*!
 * @brief Sets the current direction of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param direction GPIO directions.
 *         - kGpioDigitalInput: corresponding pin is set as digital input.
 *         - kGpioDigitalOutput: corresponding pin is set as digital output.
 */

void GPIO_DRV_SetPinDir(uint32_t pinName, gpio_pin_direction_t direction);
/* @} */

/*!
 * @name Output Operations
 * @{
 */

/*!
 * @brief Sets the output level of the individual GPIO pin to the logic 1 or 0.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param output  pin output logic level.
 *        - 0: corresponding pin output low logic level.
 *        - Non-0: corresponding pin output high logic level.
 */
void GPIO_DRV_WritePinOutput(uint32_t pinName, uint32_t output);

/*!
 * @brief Sets the output level of the individual GPIO pin to the logic 1.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void GPIO_DRV_SetPinOutput(uint32_t pinName);

/*!
 * @brief Sets the output level of the individual GPIO pin to the logic 0.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void GPIO_DRV_ClearPinOutput(uint32_t pinName);

/*!
 * @brief Reverses current output logic of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void GPIO_DRV_TogglePinOutput(uint32_t pinName);

/* @} */

/*!
 * @name Input Operations
 * @{
 */

/*!
 * @brief Reads the current input value of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @return GPIO port input value.
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 */
uint32_t GPIO_DRV_ReadPinInput(uint32_t pinName);

#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
/*!
 * @brief Enables or disables the digital filter in a single port.
 *
 * Each bit of the 32-bit register represents one pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param isDigitalFilterEnabled  digital filter enable/disable.
 *        - false: digital filter is disabled on the corresponding pin.
 *        - true : digital filter is enabled on the corresponding pin.
 */
void GPIO_DRV_SetDigitalFilterCmd(uint32_t pinName, bool isDigitalFilterEnabled);
#endif

/* @} */

/*!
 * @name Interrupt
 * @{
 */

/*!
 * @brief Reads the individual pin-interrupt status flag.
 *
 * If a pin is configured to generate the DMA request,  the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @return current pin interrupt status flag
 *         - 0: interrupt is not detected.
 *         - 1: interrupt is detected.
 */
bool GPIO_DRV_IsPinIntPending(uint32_t pinName);

/*!
 * @brief Clears the individual GPIO pin interrupt status flag.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void GPIO_DRV_ClearPinIntFlag(uint32_t pinName);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __FSL_GPIO_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

