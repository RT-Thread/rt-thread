/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-21     Meco Man     first version
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
    {D0, GET_PIN(G,9), "uart3"},        /* Serial-xx */
    {D1, GET_PIN(G,14), "uart3"},       /* Serial-xx */
    {D2, GET_PIN(F,15)},
    {D3, GET_PIN(E,13), "pwm1", 3},     /* PWM */
    {D4, GET_PIN(F,14)},
    {D5, GET_PIN(E,11), "pwm1", 2},     /* PWM */
    {D6, GET_PIN(E,9), "pwm1", 1},      /* PWM */
    {D7, GET_PIN(F,13)},
    {D8, GET_PIN(F,12)},
    {D9, GET_PIN(D,15), "pwm4", 4},     /* PWM */
    {D10, GET_PIN(D,14), "pwm4", 3},    /* PWM */
    {D11, GET_PIN(A,7), "pwm14", 1},    /* PWM */
    {D12, GET_PIN(A,6)},
    {D13, GET_PIN(A,5)},
    {D14, GET_PIN(B,9), "i2c1"},        /* I2C-SDA (Wire) */
    {D15, GET_PIN(B,8), "i2c1"},        /* I2C-SCL (Wire) */
    {D16, GET_PIN(C,13)},               /* USER KEY */
    {D17, GET_PIN(B,0)},                /* LED_BUILTIN, USER LED1 */
    {D18, GET_PIN(B,7)},                /* USER LED2 */
    {D19, GET_PIN(B,14)},               /* USER LED3 */
    {A0, GET_PIN(A,3), "adc1", 3},      /* ADC */
    {A1, GET_PIN(C,0), "adc1", 10},     /* ADC */
    {A2, GET_PIN(C,3), "adc1", 13},     /* ADC */
    {A3, GET_PIN(C,1), "adc1", 11},     /* ADC */
    {A4, GET_PIN(C,4), "adc1", 14},     /* ADC */
    {A5, GET_PIN(C,5), "adc1", 15},     /* ADC */
    {A6, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal reference voltage */
    {A7, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal temperature sensor */
};

#ifdef RTDUINO_USING_SPI
void switchToSPI(const char *bus_name)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(!rt_strcmp(bus_name, "spi1"))
    {
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

        /**SPI1 GPIO Configuration
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        LOG_I("D11, D12 and D13 will switch from PWM to SPI");
    }
}
#endif /* RTDUINO_USING_SPI */
