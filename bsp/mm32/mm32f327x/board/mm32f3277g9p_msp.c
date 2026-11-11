/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-05     mazhiyuan   first version
 */

#include <hal_common.h>
#include <hal_gpio.h>
#include <hal_rcc.h>
#include <hal_uart.h>

void UART_MspInit(UART_Type *muart)
{
    GPIO_Init_Type gpio_init;

    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOA, true);

    if (muart == UART1)
    {
        RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_UART1, true);

        gpio_init.Pins = GPIO_PIN_9;
        gpio_init.PinMode = GPIO_PinMode_AF_PushPull;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &gpio_init);
        GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_7);

        gpio_init.Pins = GPIO_PIN_10;
        gpio_init.PinMode = GPIO_PinMode_In_Floating;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &gpio_init);
        GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_7);
    }
    else if (muart == UART2)
    {
        RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART2, true);

        gpio_init.Pins = GPIO_PIN_2;
        gpio_init.PinMode = GPIO_PinMode_AF_PushPull;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &gpio_init);
        GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_7);

        gpio_init.Pins = GPIO_PIN_3;
        gpio_init.PinMode = GPIO_PinMode_In_Floating;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &gpio_init);
        GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_7);
    }
}
