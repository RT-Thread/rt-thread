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
    RCM_EnableAPB2PeriphClock((RCM_APB2_PERIPH_T)(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_USART1));

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_PU;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART2
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_PU;
    GPIO_ConfigStruct.pin = GPIO_PIN_3;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif
}

void apm32_msp_sdio_init(void *Instance)
{
    GPIO_Config_T  GPIO_InitStructure;

    /* Enable the GPIO and DMA2 Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_GPIOD);

    /* Enable the SDIO Clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_SDIO);

    /* Configure the GPIO pin */
    GPIO_InitStructure.pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_InitStructure.mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.pin = GPIO_PIN_2;
    GPIO_Config(GPIOD, &GPIO_InitStructure);
}

void apm32_msp_can_init(void *Instance)
{
#if defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)
    GPIO_Config_T  GPIO_InitStructure;
    CAN_T *CANx = (CAN_T *)Instance;

    if (CAN1 == CANx)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN1);

        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOD);

        GPIO_ConfigPinRemap(GPIO_REMAP2_CAN1);

        /* CAN1 Tx */
        GPIO_InitStructure.pin   = GPIO_PIN_1;
        GPIO_InitStructure.mode  = GPIO_MODE_AF_PP;
        GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOD, &GPIO_InitStructure);

        /* CAN1 Rx */
        GPIO_InitStructure.pin = GPIO_PIN_0;
        GPIO_InitStructure.mode = GPIO_MODE_IN_FLOATING;
        GPIO_Config(GPIOD, &GPIO_InitStructure);
    }
    else if (CAN2 == CANx)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN2);

        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);

        GPIO_ConfigPinRemap(GPIO_REMAP_CAN2);

        /* CAN2 Tx */
        GPIO_InitStructure.pin   = GPIO_PIN_6;
        GPIO_InitStructure.mode  = GPIO_MODE_AF_PP;
        GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOB, &GPIO_InitStructure);

        /* CAN2 Rx */
        GPIO_InitStructure.pin  = GPIO_PIN_5;
        GPIO_InitStructure.mode = GPIO_MODE_IN_FLOATING;
        GPIO_Config(GPIOB, &GPIO_InitStructure);
    }
#endif
}
