/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-10-16     Hydevcode         first version
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
    {D00, GET_PIN(19, 0),  "uart2"},                          /* Serial2-RX */
    {D01, GET_PIN(19, 1),  "uart2"},                          /* Serial2-TX */
    {D2, GET_PIN(0, 3)},                                   /* SPI0_CS*/
    {D3, GET_PIN(1, 1), "spi0"},                           /* SPI0_MOSI */
    {D4, GET_PIN(1, 0), "spi0"},                           /* SPI0_MISO */
    {D5, GET_PIN(0, 2), "spi0"},                           /* SPI_SCK */
    {D6, GET_PIN(0, 0), "i2c2"},                           /* I2C-SDA (Soft Wire) */
    {D7, GET_PIN(0, 1), "i2c2"},                           /* I2C-SCL (Soft Wire) */
};
