/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-11     luobeiahi    first version
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

void apm32_msp_spi_init(void *Instance)
{
#ifdef BSP_USING_SPI
    // TODO
#endif
}

void apm32_msp_timer_init(void *Instance)
{
#ifdef BSP_USING_PWM
    GPIO_Config_T gpio_config;
    TMR_T *tmr_x = (TMR_T *)Instance;

    if (tmr_x == TMR3)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_AFIO);

        GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);

        /* TMR3 channel 1 gpio config */
        gpio_config.pin = GPIO_PIN_6;
        gpio_config.mode = GPIO_MODE_AF_PP;
        gpio_config.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 2 gpio config */
        gpio_config.pin = GPIO_PIN_7;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 3 gpio config */
        gpio_config.pin = GPIO_PIN_8;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 4 gpio config */
        gpio_config.pin = GPIO_PIN_9;
        GPIO_Config(GPIOC, &gpio_config);
    }
#endif
}

void apm32_msp_can_init(void *Instance)
{
#ifdef BSP_USING_CAN1
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
#endif
}
