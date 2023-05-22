/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-13     songw4232    first version
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
    {D0, GET_PIN(G,8), "uart1"},        /* Serial-RX */
    {D1, GET_PIN(G,7), "uart1"},        /* Serial-TX */
    {D2, GET_PIN(F,15)},
    {D3, GET_PIN(E,13), "pwm1", 3},     /* PWM */
    {D4, GET_PIN(F,14)},
    {D5, GET_PIN(E,11), "pwm1", 2},     /* PWM */
    {D6, GET_PIN(E,9), "pwm1", 1},      /* PWM */
    {D7, GET_PIN(F,13)},
    {D8, GET_PIN(F,12)},
    {D9, GET_PIN(D,15), "pwm4", 4},     /* PWM */
    {D10, GET_PIN(D,14)},
    {D11, GET_PIN(A,7), "spi1"},        /* SPI-MOSI */
    {D12, GET_PIN(A,6), "spi1"},        /* SPI-MISO */
    {D13, GET_PIN(A,5), "spi1"},        /* SPI-SCK */
    {D14, GET_PIN(B,9), "i2c1"},        /* I2C-SDA (Wire) */
    {D15, GET_PIN(B,8), "i2c1"},        /* I2C-SCL (Wire) */
    {A0, GET_PIN(A,3), "adc1", 8},      /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A1, GET_PIN(A,2), "adc1", 7},      /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A2, GET_PIN(C,3), "adc1", 4},      /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A3, GET_PIN(B,0), "adc1", 15},     /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A4, GET_PIN(C,1), "adc1", 2},      /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A5, GET_PIN(C,0), "adc1", 1},      /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
};
