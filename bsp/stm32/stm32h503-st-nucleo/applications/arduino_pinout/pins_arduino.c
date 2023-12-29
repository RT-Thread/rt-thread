/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-12-25     ChuShicheng    first version
 */

#include <Arduino.h>
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
    {D0, GET_PIN(B, 15), "uart1"},          /* Serial-RX */
    {D1, GET_PIN(B, 14), "uart1"},          /* Serial-TX */
    {D2, GET_PIN(A, 10)},
    {D3, GET_PIN(B, 3)},
    {D4, GET_PIN(B, 5)},
    {D5, GET_PIN(B, 4), "pwm1", 2},         /* PWM */
    {D6, GET_PIN(B, 10), "pwm2", 3},        /* PWM */
    {D7, GET_PIN(A, 8)},
    {D8, GET_PIN(C, 7)},
    {D9, GET_PIN(C, 6), "pwm3", 1},         /* PWM */
    {D10, GET_PIN(C, 9), "pwm3", 4},        /* PWM */
    {D11, GET_PIN(A, 7), "pwm3", 2},        /* PWM */
    {D12, GET_PIN(A, 6)},
    {D13, GET_PIN(A, 5)},
    {D14, GET_PIN(B, 7), "i2c1"},           /* I2C-SDA (Wire) */
    {D15, GET_PIN(B, 6), "i2c1"},           /* I2C-SCL (Wire) */
    {A0, GET_PIN(A, 0), "adc1", 0},         /* ADC */
    {A1, GET_PIN(A, 1), "adc1", 1},         /* ADC */
    {A2, GET_PIN(A, 2), "adc1", 14},        /* ADC */
    {A3, GET_PIN(B, 0), "adc1", 9},         /* ADC */
    {A4, GET_PIN(C, 1), "adc1", 11},        /* ADC */
    {A5, GET_PIN(C, 0), "adc1", 10},        /* ADC */
};
