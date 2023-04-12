/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     liYony       first version
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
    {D0, GET_PIN(G,9), "uart3"},        /* Serial-Rx */
    {D1, GET_PIN(G,14), "uart3"},       /* Serial-Tx */
    {D2, GET_PIN(G,13)},
    {D3, GET_PIN(A,1), "pwm2", 2},      /* PWM */
    {D4, GET_PIN(G,12)},
    {D5, GET_PIN(A,2), "pwm2", 3},      /* PWM */
    {D6, GET_PIN(A,6), "pwm3", 1},      /* PWM */
    {D7, GET_PIN(G,11)},
    {D8, GET_PIN(G,10)},
    {D9, GET_PIN(A,7), "pwm3", 2},      /* PWM */
    {D10, GET_PIN(H,6), "pwm12", 1},    /* PWM */
    {D11, GET_PIN(B,15), "pwm12", 2},   /* PWM */
    {D12, GET_PIN(B,14)},
    {D13, GET_PIN(D,3)},                /* LED_BUILTIN */
    {D14, GET_PIN(B,9), "i2c1"},        /* I2C-SDA (Wire) */
    {D15, GET_PIN(B,8), "i2c1"},        /* I2C-SCL (Wire) */
    {D16, GET_PIN(A,0)},                /* user button */
    {D17, GET_PIN(G,6)},                /* user LED */
    {D18, GET_PIN(D,4)},                /* user LED */
    {D19, GET_PIN(D,5)},                /* user LED */
    {D20, GET_PIN(K,3)},                /* user LED */
    {A0, GET_PIN(B,1), "adc1", 9},      /* ADC */
    {A1, GET_PIN(C,2), "adc1", 12},     /* ADC */
    {A2, GET_PIN(C,3), "adc1", 13},     /* ADC */
    {A3, GET_PIN(C,4), "adc1", 14},     /* ADC */
    {A4, GET_PIN(C,5), "adc1", 15},     /* ADC */
    {A5, GET_PIN(A,4), "adc1", 4},      /* ADC */
    {A6, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal reference voltage */
    {A7, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal temperature sensor */
};
