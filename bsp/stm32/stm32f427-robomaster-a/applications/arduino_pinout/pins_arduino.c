/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-21     ChuShicheng  first version
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
    {D0, GET_PIN(F,14)},                /* LED_BUILTIN */
    {D1, GET_PIN(D,9), "uart3"},        /* Serial-RX */
    {D2, GET_PIN(D,8), "uart3"},        /* Serial-TX */
    {D3, GET_PIN(G,9), "uart6"},        /* Serial-RX */
    {D4, GET_PIN(G,14), "uart6"},       /* Serial-TX */
    {D5, GET_PIN(E,0), "uart8"},        /* Serial-RX */
    {D6, GET_PIN(E,1), "uart8"},        /* Serial-TX */
    {D7, GET_PIN(E,7), "uart7"},        /* Serial-RX */
    {D8, GET_PIN(E,8), "uart7"},        /* Serial-TX */
    {D9, GET_PIN(H,6), "pwm12", 1},     /* BSP: Buzzer, PWM */
    {D10, GET_PIN(D,12), "pwm4", 1},    /* PWM */
    {D11, GET_PIN(D,13), "pwm4", 2},    /* PWM */
    {D12, GET_PIN(D,14), "pwm4", 3},    /* PWM */
    {D13, GET_PIN(D,15), "pwm4", 4},    /* PWM */
    {D14, GET_PIN(H,10), "pwm5", 1},    /* PWM */
    {D15, GET_PIN(H,11), "pwm5", 2},    /* PWM */
    {D16, GET_PIN(H,12), "pwm5", 3},    /* PWM */
    {D17, GET_PIN(I,0), "pwm5", 4},     /* PWM */
    {D18, GET_PIN(A,0), "pwm2", 1},     /* PWM */
    {D19, GET_PIN(A,1), "pwm2", 2},     /* PWM */
    {D20, GET_PIN(A,2), "pwm2", 3},     /* PWM */
    {D21, GET_PIN(A,3), "pwm2", 4},     /* PWM */
    {D22, GET_PIN(I,5), "pwm8", 1},     /* PWM */
    {D23, GET_PIN(I,6), "pwm8", 2},     /* PWM */
    {D24, GET_PIN(I,7), "pwm8", 3},     /* PWM */
    {D25, GET_PIN(I,2), "pwm8", 4},     /* PWM */
    {D26, GET_PIN(F,1)},
    {D27, GET_PIN(F,0)},
    {D28, GET_PIN(E,4), "i2c1"},        /* I2C-SCL (Wire) */
    {D29, GET_PIN(E,5), "i2c1"},        /* I2C-SDA (Wire) */
    {D30, GET_PIN(E,6)},
    {D31, GET_PIN(E,12)},
    {D32, GET_PIN(C,2)},
    {D33, GET_PIN(B,0)},
    {D34, GET_PIN(C,3)},
    {D35, GET_PIN(B,1)},
    {D36, GET_PIN(C,4)},
    {D37, GET_PIN(C,0)},
    {D38, GET_PIN(C,5)},
    {D39, GET_PIN(C,1)},
    {D40, GET_PIN(A,5)},
    {D41, GET_PIN(A,4)},
    {D42, GET_PIN(F,10)},
    {D43, GET_PIN(I,9)},
    {A0, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal temperature sensor */
    {A1, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal reference voltage */
};
