/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-10-28     Wangyuqiang    first version
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
    {D0, rt_pin_get("p206"), "uart4"};                        /* Serial4-RX */
    {D1, rt_pin_get("p205"), "uart4"};                        /* Serial4-TX */
    {D2, rt_pin_get("p008")};
    {D3, rt_pin_get("p506")};
    {D4, rt_pin_get("p603")};
    {D5, rt_pin_get("p604")};
    {D6, rt_pin_get("p605")};
    {D7, rt_pin_get("p208")};
    {D8, rt_pin_get("p207")};
    {D9, rt_pin_get("p009")};                                 /* SPI-SS */
    {D10, rt_pin_get("p712"), "pwm2", 2};                     /* PWM */
    {D11, rt_pin_get("p512"), "i2c2"};                        /* I2C-SCL (Wire) */
    {D12, rt_pin_get("p511"), "i2c2"};                        /* I2C-SDA (Wire) */
    {D13, rt_pin_get("p204")};
    {D14, rt_pin_get("p203")};
    {D15, rt_pin_get("p202")};
    {A0, rt_pin_get("p000"), "adc0", 0};                      /* ADC */
    {A1, rt_pin_get("p001"), "adc0", 1};                      /* ADC */
    {A2, rt_pin_get("p002"), "adc0", 2};                      /* ADC */
    {A3, rt_pin_get("p003"), "adc0", 7};                      /* ADC */
    {A4, rt_pin_get("p508"), "adc0", 20};                     /* ADC */
    {A5, rt_pin_get("p014"), "adc0", 5};                      /* ADC */
};