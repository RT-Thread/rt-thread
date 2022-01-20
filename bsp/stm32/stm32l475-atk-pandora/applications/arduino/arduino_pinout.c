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
#include "arduino_pinout.h"

const pin_map_t pin_map_table[ARDUINO_PINOUT_PIN_MAX]=
{
    /*
        {Arduino Pin, RT-Thread Pin [, Device Name(PWM or ADC), Channel]}
        [] means optional
        Digital pins must NOT give the device name and channel.
        Analog pins MUST give the device name and channel(ADC or PWM).
    */
    {0}, /* D0, RX */
    {1}, /* D1, TX */
    {2, GET_PIN(D,10)}, /* D2, BSP:KEY0 */
    {3}, /* D3, PWM */
    {4, GET_PIN(D,9)}, /* D4, BSP:KEY1 */
    {5, GET_PIN(D,8)}, /* D5, BSP:KEY2 */
    {6}, /* D6, PWM */
    {7}, /* D7 */
    {8, GET_PIN(E,7)}, /* D8, BSP: RED-LED */
    {9}, /* D9, PWM */
    {10, GET_PIN(E,9), "pwm1", 1}, /* D10, PWM, BSP: BLUE-LED */
    {11, GET_PIN(B,8), "pwm4", 3}, /* D11, PWM */
    {12, GET_PIN(B,2)}, /* D12, BSP: BEEP */
    {13, GET_PIN(E,8)}, /* D13, LED_BUILTIN, BSP: GREEN-LED */
    {14, GET_PIN(C,2), "adc1", 3}, /* D14, A0 */
    {15}, /* D15, A1 */
    {16}, /* D16, A2 */
    {17}, /* D17, A3 */
    {18}, /* D18, A4 */
    {19} /* D19, A5 */
};

/* initialization for BSP; maybe a blank function  */
void initVariant(void)
{
    /* Nothing needs to initialize for this BSP */
}
