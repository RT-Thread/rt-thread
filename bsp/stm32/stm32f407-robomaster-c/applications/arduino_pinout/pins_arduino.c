/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-20     default      first version
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
    {D0, GET_PIN(H,11)},                /* LED_BUILTIN */
    {D1, GET_PIN(B,7), "uart1"},        /* Serial-RX */
    {D2, GET_PIN(A,9), "uart1"},        /* Serial-TX */
    {D3, GET_PIN(G,9), "uart6"},        /* Serial-RX */
    {D4, GET_PIN(G,14), "uart6"},       /* Serial-TX */
    {D5, GET_PIN(F,1), "i2c1"},         /* I2C-SCL (Wire) */
    {D6, GET_PIN(F,0), "i2c1"},         /* I2C-SDA (Wire) */
    {D7, GET_PIN(E,9), "pwm1", 1},      /* PWM */
    {D8, GET_PIN(E,11), "pwm1", 2},     /* PWM */
    {D9, GET_PIN(E,13), "pwm1", 3},     /* PWM */
    {D10, GET_PIN(E,14), "pwm1", 4},    /* PWM */
    {D11, GET_PIN(C,6), "pwm8", 1},     /* PWM */
    {D12, GET_PIN(I,6), "pwm8", 2},     /* PWM */
    {D13, GET_PIN(I,7), "pwm8", 3},     /* PWM */
    {A0, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal temperature sensor */
    {A1, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal reference voltage */
};
