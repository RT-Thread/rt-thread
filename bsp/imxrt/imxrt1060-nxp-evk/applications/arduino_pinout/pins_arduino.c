/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-06     WangShun     first version
 */

#include <Arduino.h>
#include <board.h>
#include "pins_arduino.h"
#include "drv_gpio.h"
/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(1,23), "uart1"},        /* Serial1-TX */
    {D1, GET_PIN(1,22), "uart1"},        /* Serial1-RX */
    {D2, GET_PIN(1,11)},
    {D3, GET_PIN(1,24), "pwm4", 1},      /* PWM */
    {D4, GET_PIN(1,9), "pwm2", 4},       /* PWM */
    {D5, GET_PIN(1,10), "pwm1", 4},      /* PWM */
    {D6, GET_PIN(1,18)},
    {D7, GET_PIN(1,19)},
    {D8, GET_PIN(1,3)},
    {D9, GET_PIN(1,2)},      
    {D10, GET_PIN(3,13)},
    {D11, GET_PIN(3,14)},
    {D12, GET_PIN(3,15)},
    {D13, GET_PIN(3,12)},
    {D14, GET_PIN(1,17), "i2c1"},        /* I2C-SDA (Wire) */
    {D15, GET_PIN(1,16), "i2c1"},        /* I2C-SCL (Wire) */
    {A0, GET_PIN(1,26), "adc1", 0},      /* ADC */
    {A1, GET_PIN(1,27), "adc1", 1},      /* ADC */
    {A2, GET_PIN(1,20), "adc1", 2},      /* ADC */
    {A3, GET_PIN(1,21), "adc1", 3},      /* ADC */
};
