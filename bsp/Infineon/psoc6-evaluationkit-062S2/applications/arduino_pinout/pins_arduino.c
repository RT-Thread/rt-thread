/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-08-16     LZerro         first version
 */

#include <Arduino.h>
#include "drv_gpio.h"
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
    {D00, GET_PIN(6, 4),  "uart6"},                          /* Serial6-RX */
    {D01, GET_PIN(6, 5),  "uart6"},                          /* Serial6-TX */
    {D2, GET_PIN(5, 0)},
    {D3, GET_PIN(5, 1),  "pwm0", 4},                        /* PWM */
    {D4, GET_PIN(11, 2)},
    {D5, GET_PIN(11, 3), "pwm0", 2},                        /* PWM */
    {D6, GET_PIN(11, 4), "pwm0", 3},
    {D7, GET_PIN(11, 5)},
    {D8, GET_PIN(5, 6)},
    {D9, GET_PIN(5, 7),  "pwm0", 7},                        /* PWM */
    {D10, GET_PIN(0, 5)},                                   /* SPI0_CS*/
    {D11, GET_PIN(0, 2), "spi0"},                           /* SPI0_MOSI */
    {D12, GET_PIN(0, 3), "spi0"},                           /* SPI0_MISO */
    {D13, GET_PIN(0, 4), "spi0"},                           /* SPI_SCK */
    {D14, GET_PIN(8, 1), "i2c4"},                           /* I2C-SDA (Soft Wire) */
    {D15, GET_PIN(8, 0), "i2c4"},                           /* I2C-SCL (Soft Wire) */
};
