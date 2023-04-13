/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-27     luobeihai    first version
 */

#include "board.h"

void apm32_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;

#ifdef BSP_USING_UART1
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_PU;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
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
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif
}

/**
 * apm32 timer gpio init
 *
 */
void apm32_msp_timer_init(void *Instance)
{
#ifdef BSP_USING_PWM3
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

/**
 * apm32 spi gpio init
 *
 */
void apm32_msp_spi_init(void *Instance)
{
#ifdef BSP_USING_SPI
    GPIO_Config_T gpioConfig;
    SPI_T *spi_x = (SPI_T *)Instance;

    if(spi_x == SPI2)
    {
        /* Enable related Clock */
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI2);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);

        /* Configure FLASH_SPI pins: SCK */
        gpioConfig.pin =  GPIO_PIN_13;
        gpioConfig.mode = GPIO_MODE_AF_PP;
        gpioConfig.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOB, &gpioConfig);

        /* Configure FLASH_SPI pins: MOSI */
        gpioConfig.pin = GPIO_PIN_15;
        GPIO_Config(GPIOB, &gpioConfig);

        /* Configure FLASH_SPI pins: MISO */
        gpioConfig.pin = GPIO_PIN_14;
        gpioConfig.mode = GPIO_MODE_IN_FLOATING;
        GPIO_Config(GPIOB, &gpioConfig);
    }
#endif
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
