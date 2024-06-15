/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-02     Meco Man     the first version
 */

#include "drv_gpio.h"
#include <board.h>
#include <rtthread.h>

#define GET_GPIOx(pin)   ((GPIO_TypeDef *)(rt_uint32_t)(pin & 0xFFFFFFFFULL))
#define GET_GPIOPin(pin) ((uint16_t)(pin >> 32U))

void rt_pin_mode(rt_uint64_t pin, rt_uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef *GPIOx = GET_GPIOx(pin);
    uint16_t GPIO_Pin = GET_GPIOPin(pin);

    RT_ASSERT(mode == PIN_MODE_OUTPUT || mode == PIN_MODE_INPUT ||
              mode == PIN_MODE_INPUT_PULLUP || mode == PIN_MODE_INPUT_PULLDOWN ||
              mode == PIN_MODE_OUTPUT_OD);

    switch((rt_ubase_t)GPIOx)
    {
        case (rt_ubase_t)GPIOA:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case (rt_ubase_t)GPIOB:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case (rt_ubase_t)GPIOC:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
#ifdef GPIOD
        case (rt_ubase_t)GPIOD:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
#endif /* GPIOD */
#ifdef GPIOE
        case (rt_ubase_t)GPIOE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
#endif /* GPIOE */
#ifdef GPIOF
        case (rt_ubase_t)GPIOF:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
#endif /* GPIOF */
#ifdef GPIOG
        case (rt_ubase_t)GPIOG:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
#endif /* GPIOG */
#ifdef GPIOH
        case (rt_ubase_t)GPIOH:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
#endif /* GPIOH */
#ifdef GPIOI
        case (rt_ubase_t)GPIOI:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
#endif /* GPIOI */
    }

    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }

    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void rt_pin_write(rt_uint64_t pin, rt_uint8_t value)
{
    GPIO_TypeDef *GPIOx = GET_GPIOx(pin);
    uint16_t GPIO_Pin = GET_GPIOPin(pin);

    RT_ASSERT(value == PIN_LOW || value == PIN_HIGH);

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, (value == PIN_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

rt_int8_t rt_pin_read(rt_uint64_t pin)
{
    GPIO_TypeDef *GPIOx = GET_GPIOx(pin);
    uint16_t GPIO_Pin = GET_GPIOPin(pin);

    return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET ? PIN_LOW : PIN_HIGH;
}
