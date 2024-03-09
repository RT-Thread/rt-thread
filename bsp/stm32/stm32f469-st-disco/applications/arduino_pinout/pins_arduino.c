/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     liYony       first version
 */

#include <Arduino.h>
#include "pins_arduino.h"
#include <drv_gpio.h>

#define DBG_TAG    "RTduino.pins_arduino"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(G,9), "uart3"},        /* Serial-Rx */
    {D1, GET_PIN(G,14), "uart3"},       /* Serial-Tx */
    {D2, GET_PIN(G,13)},
    {D3, GET_PIN(A,1), "pwm2", 2},      /* PWM */
    {D4, GET_PIN(G,12)},
    {D5, GET_PIN(A,2), "pwm2", 3},      /* PWM */
    {D6, GET_PIN(A,6), "pwm3", 1},      /* PWM */
    {D7, GET_PIN(G,11)},
    {D8, GET_PIN(G,10)},
    {D9, GET_PIN(A,7), "pwm3", 2},      /* PWM */
    {D10, GET_PIN(H,6), "pwm12", 1},    /* PWM */
    {D11, GET_PIN(B,15), "pwm12", 2},   /* PWM */
    {D12, GET_PIN(B,14)},
    {D13, GET_PIN(D,3)},                /* LED_BUILTIN */
    {D14, GET_PIN(B,9), "i2c1"},        /* I2C-SDA (Wire) */
    {D15, GET_PIN(B,8), "i2c1"},        /* I2C-SCL (Wire) */
    {D16, GET_PIN(A,0)},                /* user button */
    {D17, GET_PIN(G,6)},                /* user LED */
    {D18, GET_PIN(D,4)},                /* user LED */
    {D19, GET_PIN(D,5)},                /* user LED */
    {D20, GET_PIN(K,3)},                /* user LED */
    {A0, GET_PIN(B,1), "adc1", 9},      /* ADC */
    {A1, GET_PIN(C,2), "adc1", 12},     /* ADC */
    {A2, GET_PIN(C,3), "adc1", 13},     /* ADC */
    {A3, GET_PIN(C,4), "adc1", 14},     /* ADC */
    {A4, GET_PIN(C,5), "adc1", 15},     /* ADC */
    {A5, GET_PIN(A,4), "adc1", 4},      /* ADC */
    {A6, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal reference voltage */
    {A7, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal temperature sensor */
};

#ifdef RTDUINO_USING_SPI
void switchToSPI(const char *bus_name)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(!rt_strcmp(bus_name, "spi2"))
    {
        __HAL_RCC_SPI2_CLK_ENABLE();

        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14 | GPIO_PIN_15);

        /**SPI2 GPIO Configuration
        PD3     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        LOG_I("D11, D12 and D13 will switch from PWM to SPI");
    }
}
#endif /* RTDUINO_USING_SPI */
