/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#include <Arduino.h>
#include <board.h>
#include "pins_arduino.h"

const pin_map_t pin_map_table[]=
{
    /*
        {Arduino Pin, RT-Thread Pin [, Device Name(PWM or ADC), Channel]}
        [] means optional
        Digital pins must NOT give the device name and channel.
        Analog pins MUST give the device name and channel(ADC or PWM).
    */
    {0, GET_PIN(A,3)},  /* D0, RX */
    {1, GET_PIN(A,2)},  /* D1, TX */
    {2, GET_PIN(A,10)}, /* D2 */
    {3, GET_PIN(B,3), "pwm2", 2},   /* D3, PWM */
    {4, GET_PIN(B,5)},  /* D4 */
    {5, GET_PIN(B,4), "pwm3", 1},   /* D5, PWM */
    {6, GET_PIN(B,10), "pwm2", 3},  /* D6, PWM */
    {7, GET_PIN(A,8)},  /* D7 */
    {8, GET_PIN(A,9)},  /* D8 */
    {9, GET_PIN(C,7), "pwm3", 2},   /* D9, PWM */
    {10, GET_PIN(B,6)}, /* D10 */
    {11, GET_PIN(A,7)}, /* D11 */
    {12, GET_PIN(A,6)}, /* D12 */
    {13, GET_PIN(A,5)}, /* D13 */
    {14, GET_PIN(B,9)}, /* D14 */
    {15, GET_PIN(B,8)}, /* D15 */
    {16, GET_PIN(A,0), "adc1", 0},  /* A0 */
    {17, GET_PIN(A,1), "adc1", 1},  /* A1 */
    {18, GET_PIN(A,4), "adc1", 4},  /* A2 */
    {19, GET_PIN(B,0), "adc1", 8},  /* A3 */
    {20, GET_PIN(C,1), "adc1", 11}, /* A4 */
    {21, GET_PIN(C,0), "adc1", 10}  /* A5 */
};

/* initialization for BSP; maybe a blank function  */
void initVariant(void)
{
    /* Nothing needs to initialize for this BSP */
}
