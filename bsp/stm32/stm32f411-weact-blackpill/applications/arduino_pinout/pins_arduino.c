/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     ChuShicheng  first version
 */

#include <Arduino.h>
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
    {D0, GET_PIN(C,13)},                /* LED_BUILTIN */
    {D1, GET_PIN(C,14), "i2c1"},        /* I2C-SDA (Wire) */
    {D2, GET_PIN(C,15), "i2c1"},        /* I2C-SCL (Wire) */
    {D3, GET_PIN(A,2), "uart2"},        /* Serial-TX */
    {D4, GET_PIN(A,3), "uart2"},        /* Serial-RX */
    {D5, GET_PIN(B,2)},
    {D6, GET_PIN(B,10)},
    {D7, GET_PIN(B,9), "pwm4", 4},      /* PWM */
    {D8, GET_PIN(B,8), "pwm4", 3},      /* PWM */
    {D9, GET_PIN(B,7), "pwm4", 2},      /* PWM */
    {D10, GET_PIN(B,6), "pwm4", 1},     /* PWM */
    {D11, GET_PIN(B,5), "spi1"},        /* SPI-MOSI */
    {D12, GET_PIN(B,4), "spi1"},        /* SPI-MISO */
    {D13, GET_PIN(B,3), "spi1"},        /* SPI-SCK */
    {D14, GET_PIN(A,15), "spi1"},       /* SPI-SS */
    {D15, GET_PIN(A,12), "usb"},        /* SerialUSB */
    {D16, GET_PIN(A,11), "usb"},        /* SerialUSB */
    {D17, GET_PIN(A,10), "uart1"},      /* Serial-RX */
    {D18, GET_PIN(A,9), "uart1"},       /* Serial-TX */
    {D19, GET_PIN(A,8)},
    {D20, GET_PIN(B,15), "pwm1", -3},   /* PWM */
    {D21, GET_PIN(B,14), "pwm1", -2},   /* PWM */
    {D22, GET_PIN(B,13), "pwm1", -1},   /* PWM */
    {D23, GET_PIN(B,12)},
    {A0, GET_PIN(A,0), "adc1", 0},      /* ADC */
    {A1, GET_PIN(A,1), "adc1", 1},      /* ADC */
    {A2, GET_PIN(A,4), "adc1", 4},      /* ADC */
    {A3, GET_PIN(A,5), "adc1", 5},      /* ADC */
    {A4, GET_PIN(A,6), "adc1", 6},      /* ADC */
    {A5, GET_PIN(A,7), "adc1", 7},      /* ADC */
    {A6, GET_PIN(B,0), "adc1", 8},      /* ADC */
    {A7, GET_PIN(B,1), "adc1", 9},      /* ADC */
    {A8, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal reference voltage */
    {A9, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal temperature sensor */
};
