/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-22     ChuShicheng  first version
 * 2023-02-23     Wangyuqiang  second version
 */

#include <Arduino.h>
#include <board.h>
#include <drv_pin.h>
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
    {D0, GET_PINS(1,24), "uart2"},      /* Serial2-RX */
    {D1, GET_PINS(0,27), "uart2"},      /* Serial2-TX */
    {D2, GET_PINS(0,15)},
    {D3, GET_PINS(1,6)},
    {D4, GET_PINS(1,7), "pwm2", 2},     /* PWM */
    {D5, GET_PINS(1,4), "pwm2", 1},     /* PWM */
    {D6, GET_PINS(1,10), "pwm1", 0},    /* PWM */
    {D7, GET_PINS(1,9)},
    {D8, GET_PINS(1,8)},
    {D9, GET_PINS(1,5)},
    {D10, GET_PINS(1,1)},
    {D11, GET_PINS(0,26)},
    {D12, GET_PINS(1,3)},
    {D13, GET_PINS(1,2)},
    {D14, GET_PINS(1,21), "i2c4"},      /* I2C-SDA (Wire) */
    {D15, GET_PINS(1,20), "i2c4"},      /* I2C-SCL (Wire) */
    {A0, GET_PINS(0,16), "adc0", 8},    /* ADC */
    {A1, GET_PINS(0,23), "adc0", 0},    /* ADC */
    {A2, RT_NULL},
    {A3, GET_PINS(1,31)},
    {A4, GET_PINS(0,13), "i2c1"},       /* I2C-SDA (Wire) */
    {A5, GET_PINS(0,14), "i2c1"},       /* I2C-SCL (Wire) */
    {A6, RT_NULL, "adc0", 13},          /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A7, RT_NULL, "adc0", 26},          /* ADC, On-Chip: internal temperature sensor, ADC_CHANNEL_TEMPSENSOR */
};
