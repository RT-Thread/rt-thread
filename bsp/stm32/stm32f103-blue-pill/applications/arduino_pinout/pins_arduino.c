/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-05     liYony       first version
 */
#include <Arduino.h>
#include <board.h>
#include "pins_arduino.h"

/*
    {Arduino Pin, RT-Thread Pin [, Device Name(PWM or ADC), Channel]}
    [] means optional
    Digital pins must NOT give the device name and channel.
    Analog pins MUST give the device name and channel(ADC, PWM or DAC).
    Arduino Pin must keep in sequence.
*/
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(B,7)},
    {D1, GET_PIN(B,6)},
    {D2, GET_PIN(B,5), "pwm3", 2},/* PWM */
    {D3, GET_PIN(B,4), "pwm3", 1}, /* PWM */
    {D4, GET_PIN(B,3), "pwm2", 2}, /* PWM */
    {D5, GET_PIN(A,15), "pwm2", 1}, /* PWM */
    {D6, GET_PIN(A,8)},
    {D7, GET_PIN(B,12)},
    {D8, GET_PIN(C,13)}, /* LED_BUILTIN */
    {D9, GET_PIN(C,14)},
    {D10, GET_PIN(C,15)},
    {D11, GET_PIN(A,0)},
    {D12, GET_PIN(B,0), "pwm3", 3}, /* PWM */
    {D13, GET_PIN(B,1), "pwm3", 4}, /* PWM */
    {A0, GET_PIN(A,1), "adc1", 1}, /* ADC */
    {A1, GET_PIN(A,4), "adc1", 4}, /* ADC */
    {A2, GET_PIN(A,5), "adc1", 5}, /* ADC */
    {A3, GET_PIN(A,6), "adc1", 6}, /* ADC */
    {A4, GET_PIN(A,7), "adc1", 7}, /* ADC */
    {A5, RT_NULL, "adc1", 17}, /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A6, RT_NULL, "adc1", 16} /* ADC, On-Chip: internal temperature sensor, ADC_CHANNEL_TEMPSENSOR */
};
/* 
 * Before RTdunio is used, you can do some necessary initialization through this function
 */
void initVariant()
{
    /* JTAG-DP Disabled and SW-DP enabled */
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); 
}