/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-22     ChuShicheng  first version
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
    {D0, 50},
    {D1, 49, "pwm1", 3},                /* PWM */
    {D2, 57, "uart1"},                  /* Serial-RX */
    {D3, 28, "uart1"},                  /* Serial-TX */
    {D4, 39, "pwm2", 1},                /* PWM */
    {D5, 40, "pwm2", 2},                /* PWM */
    {D6, 37},                           /* LED_BUILTIN */
    {D7, 43, "pwm1", 0},                /* PWM */
    {D8, 41},
    {D9, 38, "pwm2", 0},                /* PWM */
    {D10, 34},
    {D11, 27},
    {D12, 36},
    {D13, 35},
    {D14, 54, "pwm3", 2},               /* PWM */
    {D15, 53},
    {D16, 15, "i2c1"},                  /* I2C-SCL (Wire) */
    {D17, 14, "i2c1"},                  /* I2C-SDA (Wire) */
    {A0, 17, "adc0", 8},                /* ADC */
    {A1, 24, "adc0", 0},                /* ADC */
    {A2, RT_NULL, "adc0", 26},          /* ADC, On-Chip: internal temperature sensor, ADC_CHANNEL_TEMPSENSOR */
    {A3, RT_NULL, "adc0", 13},          /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
};
