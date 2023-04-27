/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-17     Rbb666       first version
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
    {D0, GET_PIN(8,0), "i2c4"},                        /* I2C-SCL (Wire) */
    {D1, GET_PIN(8,1), "i2c4"},                        /* I2C-SDA (Wire) */
    {D2, GET_PIN(0,4), "spi0"},                        /* SPI-SCK */
    {D3, GET_PIN(0,3), "spi0"},                        /* SPI-MISO */
    {D4, GET_PIN(0,2), "spi0"},                        /* SPI-MOSI */
    {D5, GET_PIN(0,5)},                                /* SPI-SS */
    {D6, GET_PIN(5,7), "pwm0", 7},                     /* PWM */
    {D7, GET_PIN(5,6), "pwm1", 7},                     /* PWM */
    {D8, GET_PIN(11,5), "pwm1", 3},                    /* PWM */
    {D9, GET_PIN(11,4), "pwm1", 1},                    /* PWM */
    {D10, GET_PIN(11,3), "pwm1", 2},                   /* PWM */
    {D11, GET_PIN(11,2), "pwm0", 2},                   /* PWM */
    {D12, GET_PIN(5,1), "pwm1", 4},                    /* PWM */
    {D13, GET_PIN(5,0), "pwm0", 4},                    /* PWM */
    {D14, GET_PIN(11,1), "uart5"},                     /* Serial2-TX */
    {D15, GET_PIN(11,0), "uart5"},                     /* Serial2-RX */
};
