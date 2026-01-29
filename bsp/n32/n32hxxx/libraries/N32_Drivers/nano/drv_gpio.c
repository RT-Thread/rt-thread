/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include "drv_gpio.h"
#include <board.h>
#include <rtthread.h>

#define GET_GPIOx(pin)   ((GPIO_Module *)(rt_uint32_t)(pin & 0xFFFFFFFFULL))
#define GET_GPIOPin(pin) ((uint16_t)(pin >> 32U))

void rt_pin_mode(rt_uint64_t pin, rt_uint8_t mode)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_Module *GPIOx = GET_GPIOx(pin);
    uint16_t GPIO_Pin = GET_GPIOPin(pin);

    RT_ASSERT(mode == PIN_MODE_OUTPUT || mode == PIN_MODE_INPUT ||
              mode == PIN_MODE_INPUT_PULLUP || mode == PIN_MODE_INPUT_PULLDOWN ||
              mode == PIN_MODE_OUTPUT_OD);

    switch((rt_ubase_t)GPIOx)
    {
        case (rt_ubase_t)GPIOA:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOA, ENABLE);
            break;
        case (rt_ubase_t)GPIOB:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOB, ENABLE);
            break;
        case (rt_ubase_t)GPIOC:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOC, ENABLE);
            break;
#ifdef GPIOD
        case (rt_ubase_t)GPIOD:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOD, ENABLE);
            break;
#endif /* GPIOD */
#ifdef GPIOE
        case (rt_ubase_t)GPIOE:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOE, ENABLE);
            break;
#endif /* GPIOE */
#ifdef GPIOF
        case (rt_ubase_t)GPIOF:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOF, ENABLE);
            break;
#endif /* GPIOF */
#ifdef GPIOG
        case (rt_ubase_t)GPIOG:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOG, ENABLE);
            break;
#endif /* GPIOG */
#ifdef GPIOH
        case (rt_ubase_t)GPIOH:
            RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOH, ENABLE);
            break;
#endif /* GPIOH */
#ifdef GPIOI
        case (rt_ubase_t)GPIOI:
            RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOI, ENABLE);
            break;
#endif /* GPIOI */
#ifdef GPIOj
        case (rt_ubase_t)GPIOj:
            RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOJ, ENABLE);
            break;
#endif /* GPIOj */
#ifdef GPIOk
        case (rt_ubase_t)GPIOk:
            RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOK, ENABLE);
            break;
#endif /* GPIOk */
    }

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_Pin;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.GPIO_Pull = GPIO_PULL_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    }

    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}

void rt_pin_write(rt_uint64_t pin, rt_uint8_t value)
{
    GPIO_Module *GPIOx = GET_GPIOx(pin);
    uint16_t GPIO_Pin = GET_GPIOPin(pin);

    RT_ASSERT(value == PIN_LOW || value == PIN_HIGH);

    GPIO_WriteBit(GPIOx, GPIO_Pin, ((value == PIN_LOW) ? Bit_RESET : Bit_SET));
}

rt_int8_t rt_pin_read(rt_uint64_t pin)
{
    GPIO_Module *GPIOx = GET_GPIOx(pin);
    uint16_t GPIO_Pin = GET_GPIOPin(pin);

    return ((GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET) ? PIN_LOW : PIN_HIGH);
}
