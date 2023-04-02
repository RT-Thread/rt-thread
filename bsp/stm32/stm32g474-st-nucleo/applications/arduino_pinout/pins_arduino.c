/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-01     Wangyuqiang  first version
 */

#include <Arduino.h>
#include <board.h>
#include "pins_arduino.h"

/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(A,2), "lpuart1"},     /* Serial-Tx */
    {D1, GET_PIN(A,3), "lpuart1"},     /* Serial-Rx */
    {D2, GET_PIN(A,10)},
    {D3, GET_PIN(B,3), "pwm2", 2},     /* PWM */
    {D4, GET_PIN(B,5)},
    {D5, GET_PIN(B,4), "pwm3", 1},     /* PWM */
    {D6, GET_PIN(B,10), "pwm2", 3},    /* PWM */
    {D7, GET_PIN(A,8)},
    {D8, GET_PIN(A,9)},
    {D9, GET_PIN(C,7), "pwm8", 2},     /* PWM */
    {D10, GET_PIN(B,6), "pwm4", 1},    /* PWM */
    {D11, GET_PIN(A,7), "pwm3", 2},    /* PWM */
    {D12, GET_PIN(A,6)},
    {D13, GET_PIN(A,5)},
    {D14, GET_PIN(B,9), "i2c1"},       /* I2C-SDA (Wire) */
    {D15, GET_PIN(B,8), "i2c1"},       /* I2C-SCL (Wire) */
    {D16, GET_PIN(C,13)},
    {A0, GET_PIN(A,0), "adc1", 1},     /* ADC */
    {A1, GET_PIN(A,1), "adc1", 2},     /* ADC */
    {A2, GET_PIN(A,4), "adc2", 17},     /* ADC */
    {A3, GET_PIN(B,0), "adc1", 15},     /* ADC */
    {A4, GET_PIN(C,1), "adc2", 7},      /* ADC */
    {A5, GET_PIN(C,0), "adc2", 6},      /* ADC */
    {A6, RT_NULL, "adc1", 3},           /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A7, RT_NULL, "adc1", 3},           /* ADC, On-Chip: internal temperature sensor, ADC_CHANNEL_TEMPSENSOR */
};
