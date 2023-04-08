/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 * 2022-09-18     Meco Man     sort pinout out
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
    {D0, GET_PIN(A,10), "uart1"},       /* Serial-Rx */
    {D1, GET_PIN(A,9), "uart1"},        /* Serial-Tx */
    {D2, GET_PIN(B,9)},
    {D3, GET_PIN(D,15), "pwm4", 4},     /* PWM */
    {D4, GET_PIN(A,8)},
    {D5, GET_PIN(D,14)},
    {D6, GET_PIN(B,11), "pwm2", 4},     /* PWM */
    {D7, GET_PIN(B,14)},
    {D8, GET_PIN(B,12)},
    {D9, GET_PIN(D,12), "pwm4", 1},     /* PWM */
    {D10, GET_PIN(B,10), "pwm2", 3},    /* PWM */
    {D11, GET_PIN(B,8), "pwm4", 3},     /* PWM */
    {D12, GET_PIN(B,15)},
    {D13, GET_PIN(B,13)},
    {D14, GET_PIN(A,1)},                /* BSP: MOTOR-A */
    {D15, GET_PIN(A,0)},                /* BSP: MOTOR-B */
    {D16, GET_PIN(B,2)},                /* BSP: BEEP */
    {D17, GET_PIN(D,10)},               /* BSP: KEY0 */
    {D18, GET_PIN(D,9)},                /* BSP: KEY1 */
    {D19, GET_PIN(D,8)},                /* BSP: KEY2 */
    {D20, GET_PIN(C,13)},               /* BSP: KEY-WKUP */
    {D21, GET_PIN(E,7)},                /* BSP: RED-LED */
    {D22, GET_PIN(E,8)},                /* LED_BUILTIN, BSP: GREEN-LED */
    {D23, GET_PIN(E,9), "pwm1", 1},     /* PWM, BSP: BLUE-LED */
    {D24, GET_PIN(B,0)},                /* BSP: INFRARED EMISSION */
    {D25, GET_PIN(B,1)},                /* BSP: INFRARED RECEPTION */
    {D26, GET_PIN(D,4)},                /* BSP: WIRELESS CE */
    {D27, GET_PIN(D,3)},                /* BSP: WIRELESS IRQ */
    {D28, GET_PIN(D,5)},                /* SPI-SS, BSP: WIRELESS CS */
    {D29, GET_PIN(B,13), "spi2"},       /* SPI-SCK */
    {D30, GET_PIN(B,14), "spi2"},       /* SPI-MISO */
    {D31, GET_PIN(B,15), "spi2"},       /* SPI-MOSI */
    {D32, GET_PIN(C,7), "i2c1"},        /* I2C-SDA (Wire) */
    {D33, GET_PIN(C,6), "i2c1"},        /* I2C-SCL (Wire) */
    {D34, GET_PIN(A,2), "uart2"},       /* Serial2-Tx */
    {D35, GET_PIN(A,3), "uart2"},       /* Serial2-Rx */
    {A0, GET_PIN(C,2), "adc1", 3},      /* ADC */
    {A1, GET_PIN(C,4), "adc1", 13},     /* ADC */
    {A2, RT_NULL, "adc1", RT_ADC_INTERN_CH_VREF},   /* ADC, On-Chip: internal reference voltage */
    {A3, RT_NULL, "adc1", RT_ADC_INTERN_CH_TEMPER}, /* ADC, On-Chip: internal temperature sensor */
    {DAC0, GET_PIN(A,4), "dac1", 1},    /* DAC */
};
