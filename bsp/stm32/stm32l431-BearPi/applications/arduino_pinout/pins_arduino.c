/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-01     liYony       first version
 */

#include <Arduino.h>
#include "pins_arduino.h"
#include <drv_gpio.h>

/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(A,1), "spi1"},         /* SPI-SCK */
    {D1, GET_PIN(A,4)},                 /* SPI-SS */
    {D2, GET_PIN(A,0)},
    {D3, GET_PIN(B,9)},
    {D4, GET_PIN(B,8), "pwm16", 1},     /* PWM */
    {D5, GET_PIN(B,6), "i2c1"},         /* I2C-SCL (Wire) */
    {D6, GET_PIN(B,7), "i2c1"},         /* I2C-SDA (Wire) */
    {D7, GET_PIN(A,6), "spi1"},         /* SPI-MISO */
    {D8, GET_PIN(A,12), "spi1"},        /* SPI-MOSI */
    {D9, GET_PIN(C,9)},
    {D10, GET_PIN(C,4), "uart3"},       /* Serial2-Tx */
    {D11, GET_PIN(C,5), "uart3"},       /* Serial2-Rx */
    {D12, GET_PIN(A,8), "pwm1", 1},     /* PWM */
    {A0, GET_PIN(C,2), "adc1", 3},      /* ADC */
    {A1, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal reference voltage */
    {A2, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal temperature sensor */
    {DAC0, GET_PIN(A,5), "dac1", 2},    /* DAC */
};
