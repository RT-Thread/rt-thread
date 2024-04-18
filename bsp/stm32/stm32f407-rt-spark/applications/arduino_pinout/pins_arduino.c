/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-04-10     Li ZhenHong    first version
 */

#include <Arduino.h>
#include "pins_arduino.h"
#include <drv_gpio.h>

/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(A, 10), "uart1"},          /* Serial-RX */
    {D1, GET_PIN(A, 9), "uart1"},           /* Serial-TX */
    {D2, GET_PIN(A, 8)},
    {D3, GET_PIN(B, 10), "pwm2", 3},        /* PWM */
    {D4, GET_PIN(A, 1)},
    {D5, GET_PIN(B, 14)},
    {D6, GET_PIN(B, 11), "pwm2", 4},        /* PWM */
    {D7, GET_PIN(B, 15)},
    {D8, GET_PIN(F, 15)},
    {D9, GET_PIN(E, 11), "pwm1", 2},        /* PWM */
    {D10, GET_PIN(E, 13), "pwm1", 3},       /* PWM */
    {D11, GET_PIN(D, 12), "pwm4", 1},       /* PWM */
    {D12, GET_PIN(D, 10)},
    {D13, GET_PIN(D, 8)},
    {D14, GET_PIN(E, 14)},
    {D15, GET_PIN(E, 12)},
    {D16, GET_PIN(E, 15)},
    {D17, GET_PIN(D, 9)},
    {D18, GET_PIN(G, 2)},
    {D19, GET_PIN(B, 2)},
    {D20, GET_PIN(G, 0)},
    {D21, GET_PIN(A, 0)},
    {D22, GET_PIN(G, 5), "sspi1"},          /* SOFT-SPI-SCK */
    {D23, GET_PIN(G, 3), "sspi1"},          /* SOFT-SPI-SCK */
    {D24, GET_PIN(G, 1), "sspi1"},          /* SOFT-SPI-SCK */
    {D25, GET_PIN(G, 7), "i2c4"},           /* I2C-SCL (Wire) */
    {D26, GET_PIN(D, 7), "i2c4"},           /* I2C-SDA (Wire) */
    {D27, GET_PIN(B, 6), "i2c5"},           /* I2C-SCL (Wire) */
    {D28, GET_PIN(B, 7), "i2c5"},           /* I2C-SDA (Wire) */
    {D29, GET_PIN(G, 6)},                   /* SPI-SS */
    {D30, GET_PIN(G, 4)},
    {D31, GET_PIN(A, 2), "uart2"},          /* Serial2-TX */
    {D32, GET_PIN(A, 3), "uart2"},          /* Serial2-RX */
    {D33, GET_PIN(F, 12)},                  /* On-Board R_LED */
    {D34, GET_PIN(F, 11)},                  /* On-Board B_LED */
    {D35, GET_PIN(B, 0)},                   /* On_Board Buzzer */
    {D36, GET_PIN(C, 5)},                   /* On-Board KEY_UP */
    {D37, GET_PIN(C, 1)},                   /* On-Board KEY_DOWM */
    {D38, GET_PIN(C, 0)},                   /* On-Board KEY_LEFT */
    {D39, GET_PIN(C, 4)},                   /* On-Board KEY_RIGHT */
    {A0, GET_PIN(F, 6), "adc3", 4},         /* ADC */
    {A1, GET_PIN(F, 7), "adc3", 5},         /* ADC */
    {A2, GET_PIN(F, 4), "adc3", 14},        /* ADC */
    {A3, GET_PIN(F, 5), "adc3", 15},        /* ADC */
    {DAC0, GET_PIN(A, 4), "dac1", 1},       /* DAC */
};
