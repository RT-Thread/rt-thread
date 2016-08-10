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

#include "fsl_gpio_hal.h"

#if FSL_FEATURE_SOC_GPIO_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_HAL_SetPinDir
 * Description   : Set individual gpio pin to general input or output.
 *
 *END**************************************************************************/
void GPIO_HAL_SetPinDir(GPIO_Type * base, uint32_t pin, gpio_pin_direction_t direction)
{
    assert(pin < 32);

    if (direction == kGpioDigitalOutput)
    {
        GPIO_SET_PDDR(base, 1U << pin);
    }
    else
    {
        GPIO_CLR_PDDR(base, 1U << pin);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_HAL_WritePinOutput
 * Description   : Set output level of individual gpio pin to logic 1 or 0.
 *
 *END**************************************************************************/
void GPIO_HAL_WritePinOutput(GPIO_Type * base, uint32_t pin, uint32_t output)
{
    assert(pin < 32);

    if (output != 0U)
    {
        GPIO_WR_PSOR(base, 1U << pin); /* Set pin output to high level.*/
    }
    else
    {
        GPIO_WR_PCOR(base, 1U << pin); /* Set pin output to low level.*/
    }
}

#if FSL_FEATURE_GPIO_HAS_FAST_GPIO

/*FUNCTION**********************************************************************
 *
 * Function Name : FGPIO_HAL_SetPinDir
 * Description   : Set individual gpio pin to general input or output.
 *
 *END**************************************************************************/
void FGPIO_HAL_SetPinDir(FGPIO_Type * base, uint32_t pin, gpio_pin_direction_t direction)
{
    if (direction == kGpioDigitalOutput)
    {
        FGPIO_SET_PDDR(base, 1U << pin);
    }
    else
    {
        FGPIO_CLR_PDDR(base, 1U << pin);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FGPIO_HAL_WritePinOutput
 * Description   : Set output level of individual gpio pin to logic 1 or 0.
 *
 *END**************************************************************************/
void FGPIO_HAL_WritePinOutput(FGPIO_Type * base, uint32_t pin, uint32_t output)
{
    if (output != 0U)
    {
        FGPIO_WR_PSOR(base, 1U << pin); /* Set pin output to high level.*/
    }
    else
    {
        FGPIO_WR_PCOR(base, 1U << pin); /* Set pin output to low level.*/
    }
}

#endif

#endif /* FSL_FEATURE_SOC_GPIO_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/
