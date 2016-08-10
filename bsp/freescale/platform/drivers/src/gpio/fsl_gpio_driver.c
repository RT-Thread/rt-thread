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

#include "fsl_gpio_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_GPIO_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_Init
 * Description   : Initialize all GPIO pins used by board.
 * To initialize the GPIO driver, two arrays similar with
 * gpio_input_pin_user_config_t inputPin[] and
 * gpio_output_pin_user_config_t outputPin[] should be defined in user's file.
 * Then simply call GPIO_DRV_Init() and pass into these two arrays. If input
 * or output pins is not needed, pass in a NULL.
 *
 *END**************************************************************************/
void GPIO_DRV_Init(const gpio_input_pin_user_config_t * inputPins,
                   const gpio_output_pin_user_config_t * outputPins)
{
    if (inputPins)
    {
        /* Initialize input pins.*/
        while (inputPins->pinName != GPIO_PINS_OUT_OF_RANGE)
        {
            GPIO_DRV_InputPinInit(inputPins++);
        }
    }

    if (outputPins)
    {
        /* Initialize output pins.*/
        while (outputPins->pinName != GPIO_PINS_OUT_OF_RANGE)
        {
            GPIO_DRV_OutputPinInit(outputPins++);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_InputPinInit
 * Description   : Initialize one GPIO input pin used by board.
 *
 *END**************************************************************************/
void GPIO_DRV_InputPinInit(const gpio_input_pin_user_config_t *inputPin)
{
    /* Get actual port and pin number.*/
    uint32_t port = GPIO_EXTRACT_PORT(inputPin->pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(inputPin->pinName);
    GPIO_Type * gpioBase = g_gpioBase[port];
    PORT_Type * portBase = g_portBase[port];

    /* Un-gate port clock*/
    CLOCK_SYS_EnablePortClock(port);

    /* Set current pin as gpio.*/
    PORT_HAL_SetMuxMode(portBase, pin, kPortMuxAsGpio);

    /* Set current pin as digital input.*/
    GPIO_HAL_SetPinDir(gpioBase, pin, kGpioDigitalInput);

    /* Configure GPIO input features. */
    #if FSL_FEATURE_PORT_HAS_PULL_ENABLE
    PORT_HAL_SetPullCmd(portBase, pin, inputPin->config.isPullEnable);
    #endif
    #if FSL_FEATURE_PORT_HAS_PULL_SELECTION
    PORT_HAL_SetPullMode(portBase, pin, inputPin->config.pullSelect);
    #endif
    #if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
    PORT_HAL_SetPassiveFilterCmd(portBase, pin,
            inputPin->config.isPassiveFilterEnabled);
    #endif
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
    PORT_HAL_SetDigitalFilterCmd(portBase, pin,
            inputPin->config.isDigitalFilterEnabled);
    #endif
    #if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
    PORT_HAL_SetPinIntMode(portBase, pin, inputPin->config.interrupt);

    /* Configure NVIC */
    if ((inputPin->config.interrupt) && (g_portIrqId[port]))
    {
        /* Enable GPIO interrupt.*/
        INT_SYS_EnableIRQ(g_portIrqId[port]);
    }
    #endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_OutputPinInit
 * Description   : Initialize one GPIO output pin used by board.
 *
 *END**************************************************************************/
void GPIO_DRV_OutputPinInit(const gpio_output_pin_user_config_t *outputPin)
{
    /* Get actual port and pin number.*/
    uint32_t port = GPIO_EXTRACT_PORT(outputPin->pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(outputPin->pinName);
    GPIO_Type * gpioBase = g_gpioBase[port];
    PORT_Type * portBase = g_portBase[port];

    /* Un-gate port clock*/
    CLOCK_SYS_EnablePortClock(port);

    /* Set current pin as gpio.*/
    PORT_HAL_SetMuxMode(portBase, pin, kPortMuxAsGpio);

    /* Set current pin as digital output.*/
    GPIO_HAL_SetPinDir(gpioBase, pin, kGpioDigitalOutput);

    /* Configure GPIO output features. */
    GPIO_HAL_WritePinOutput(gpioBase, pin, outputPin->config.outputLogic);
    #if FSL_FEATURE_PORT_HAS_SLEW_RATE
    PORT_HAL_SetSlewRateMode(portBase, pin, outputPin->config.slewRate);
    #endif
    #if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
    PORT_HAL_SetDriveStrengthMode(portBase, pin, outputPin->config.driveStrength);
    #endif
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    PORT_HAL_SetOpenDrainCmd(portBase, pin, outputPin->config.isOpenDrainEnabled);
    #endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_GetPinDir
 * Description   : Get current direction of individual GPIO pin.
 *
 *END**************************************************************************/
gpio_pin_direction_t GPIO_DRV_GetPinDir(uint32_t pinName)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    return GPIO_HAL_GetPinDir(gpioBase, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_SetPinDir
 * Description   : Set current direction of individual GPIO pin.
 *
 *END**************************************************************************/
void GPIO_DRV_SetPinDir(uint32_t pinName, gpio_pin_direction_t direction)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    GPIO_HAL_SetPinDir(gpioBase, pin, direction);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_WritePinOutput
 * Description   : Set output level of individual GPIO pin to logic 1 or 0.
 *
 *END**************************************************************************/
void GPIO_DRV_WritePinOutput(uint32_t pinName, uint32_t output)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    GPIO_HAL_WritePinOutput(gpioBase, pin, output);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_SetPinOutput
 * Description   : Set output level of individual GPIO pin to logic 1.
 *
 *END**************************************************************************/
void GPIO_DRV_SetPinOutput(uint32_t pinName)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    GPIO_HAL_SetPinOutput(gpioBase, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_ClearPinOutput
 * Description   : Set output level of individual GPIO pin to logic 0.
 *
 *END**************************************************************************/
void GPIO_DRV_ClearPinOutput(uint32_t pinName)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    GPIO_HAL_ClearPinOutput(gpioBase, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_TogglePinOutput
 * Description   : Reverse current output logic of individual GPIO pin.
 *
 *END**************************************************************************/
void GPIO_DRV_TogglePinOutput(uint32_t pinName)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    GPIO_HAL_TogglePinOutput(gpioBase, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_ReadPinInput
 * Description   : Read current input value of individual GPIO pin.
 *
 *END**************************************************************************/
uint32_t GPIO_DRV_ReadPinInput(uint32_t pinName)
{
    GPIO_Type * gpioBase = g_gpioBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    return GPIO_HAL_ReadPinInput(gpioBase, pin);
}

#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_SetDigitalFilterCmd
 * Description   : Enable or disable digital filter in one single port.
 *
 *END**************************************************************************/
void GPIO_DRV_SetDigitalFilterCmd(uint32_t pinName, bool isDigitalFilterEnabled)
{
    PORT_Type * portBase = g_portBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    PORT_HAL_SetDigitalFilterCmd(portBase, pin, isDigitalFilterEnabled);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_IsPinIntPending
 * Description   : Read the individual pin-interrupt status flag.
 *
 *END**************************************************************************/
bool GPIO_DRV_IsPinIntPending(uint32_t pinName)
{
    PORT_Type * portBase = g_portBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    return PORT_HAL_IsPinIntPending(portBase, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_DRV_ClearPinIntFlag
 * Description   : Clear individual GPIO pin interrupt status flag.
 *
 *END**************************************************************************/
void GPIO_DRV_ClearPinIntFlag(uint32_t pinName)
{
    PORT_Type * portBase = g_portBase[GPIO_EXTRACT_PORT(pinName)];
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    PORT_HAL_ClearPinIntFlag(portBase, pin);
}

#endif /* FSL_FEATURE_SOC_GPIO_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

