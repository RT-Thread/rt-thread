/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-08     WangShun     first version
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
    {D0, GET_PIN(A,9),  "uart1"},       /* Serial1-TX */
    {D1, GET_PIN(A,10), "uart1"},       /* Serial1-RX */
    {D2, GET_PIN(B,4)},
    {D3, GET_PIN(B,6), "pwm4", 1},      /* PWM */
    {D4, GET_PIN(B,7), "pwm4", 2},      /* PWM */
    {D5, GET_PIN(B,8), "pwm4", 3},      /* PWM */
    {D6, GET_PIN(B,9), "pwm4", 4},      /* PWM */
    {D7, GET_PIN(A,8), "pwm1", 1},      /* PWM */
    {D8, GET_PIN(B,1), "pwm3", 4},      /* PWM */
    {D9, GET_PIN(B,0), "pwm3", 3},      /* PWM */
    {D10, GET_PIN(B,12)},
    {D11, GET_PIN(B,15)},
    {D12, GET_PIN(B,14)},
    {D13, GET_PIN(B,13)},
    {D14, GET_PIN(B,11), "i2c1"},       /* I2C-SDA (Wire) */
    {D15, GET_PIN(B,10), "i2c1"},       /* I2C-SCL (Wire) */
    {A0, GET_PIN(A,0), "adc1", 0},      /* ADC */
    {A1, GET_PIN(A,1), "adc1", 1},      /* ADC */
    {A2, GET_PIN(A,2), "adc1", 2},      /* ADC */
    {A3, GET_PIN(A,3), "adc1", 3},      /* ADC */
    {A4, GET_PIN(A,4), "adc1", 4},      /* ADC */
    {A5, GET_PIN(A,5), "adc1", 5},      /* ADC */
};
