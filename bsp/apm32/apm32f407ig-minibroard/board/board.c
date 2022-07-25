/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     Abbcc        first version
 */

#include "board.h"

void apm32_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;

#ifdef BSP_USING_UART1
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_9, GPIO_AF_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.pupd = GPIO_PUPD_UP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_10, GPIO_AF_USART1);
#endif

#ifdef BSP_USING_UART2
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_2, GPIO_AF_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN;
    GPIO_ConfigStruct.pin = GPIO_PIN_3;
    GPIO_ConfigStruct.pupd = GPIO_PUPD_UP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_3, GPIO_AF_USART2);
#endif
}
