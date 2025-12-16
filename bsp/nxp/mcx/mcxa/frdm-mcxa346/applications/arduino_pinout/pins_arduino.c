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
    {D0, GET_PINS(2,3), "uart2"},      /* Serial2-RX */
    {D1, GET_PINS(2,2), "uart2"},      /* Serial2-TX */
    {D2, GET_PINS(3,31)},
    {D3, GET_PINS(3,14), "pwm1", 1},    /* PWM */
    {D4, GET_PINS(4,7)},   
    {D5, GET_PINS(3,1), "pwm0", 0},     /* PWM */
    {D6, GET_PINS(3,17), "pwm1", 0},    /* PWM */
    {D7, GET_PINS(3,22)},
    {D8, GET_PINS(4,3)},
    {D9, GET_PINS(3,13), "pwm1", 2},     /* PWM */
    {D10, GET_PINS(3,11),"spi1"},     /* SPI-SS */
    {D11, GET_PINS(3,8), "spi1"},     /* SPI-SDO */
    {D12, GET_PINS(3,9), "spi1"},     /* SPI-SDI */
    {D13, GET_PINS(3,10),"spi1"},    /* SPI-SCK */
    {D18, GET_PINS(1,8),"i2c2"},      /* I2C-SDA (Wire) */
    {D19, GET_PINS(1,9),"i2c2"},      /* I2C-SCL (Wire) */
    {A0, GET_PINS(1,14),"adc1", 12},    /* ADC */
    {A1, GET_PINS(2,5), "adc1", 1},     /* ADC */
    {A2, GET_PINS(2,7),"adc0", 7},      /* ADC */
    {A3, GET_PINS(3,30),"adc1", 21},
    {A4, GET_PINS(1,0),"i2c1"},       /* I2C-SDA (Wire) */
    {A5, GET_PINS(1,1),"i2c1"},       /* I2C-SCL (Wire) */
   
};