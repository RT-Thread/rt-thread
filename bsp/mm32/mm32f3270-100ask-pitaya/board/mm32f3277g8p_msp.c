/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#include <hal_dma.h>
#include <hal_gpio.h>
#include <hal_rcc.h>
#include <hal_uart.h>
#include <hal_common.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void UART_MspInit(UART_Type *muart)
{
    GPIO_Init_Type gpio_init;
    if(muart == UART1)
    {
        RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_UART1, true);
        /* PB6 - UART1_TX. */
        /* PB7 - UART1_RX. */
        gpio_init.Pins  = GPIO_PIN_6;
        gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &gpio_init);
        GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

        gpio_init.Pins  = GPIO_PIN_7;
        gpio_init.PinMode  = GPIO_PinMode_In_Floating;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &gpio_init);
        GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);
    }
    else if(muart == UART2)
    {
        RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART2, true);
        /* PD5  - UART2_TX. */
        /* PD6  - UART2_RX. */
        gpio_init.Pins  = GPIO_PIN_5;
        gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &gpio_init);
        GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_7);

        gpio_init.Pins  = GPIO_PIN_6;
        gpio_init.PinMode  = GPIO_PinMode_In_Floating;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &gpio_init);
        GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_7);
    }
    else if(muart == UART3)
    {
        RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART3, true);
        /* PB10  - UART3_TX. */
        /* PB11  - UART3_RX. */
        gpio_init.Pins  = GPIO_PIN_10;
        gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &gpio_init);
        GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

        gpio_init.Pins  = GPIO_PIN_11;
        gpio_init.PinMode  = GPIO_PinMode_In_Floating;
        gpio_init.Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &gpio_init);
        GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);
    }
}


