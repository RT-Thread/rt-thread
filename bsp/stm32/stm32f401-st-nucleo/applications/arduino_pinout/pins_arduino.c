/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-19     Meco Man     first version
 * 2022-07-26     liYony       Perfect PWM (docking of complementary outputs)
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
    {D0}, /* RX */
    {D1}, /* TX */
    {D2, GET_PIN(A,10)},
    {D3, GET_PIN(B,3), "pwm2", 2}, /* PWM2-CH2 */
    {D4, GET_PIN(B,5)},
    {D5, GET_PIN(B,4), "pwm3", 1}, /* PWM3-CH1 */
    {D6, GET_PIN(B,10), "pwm2", 3}, /* PWM2-CH3 */
    {D7, GET_PIN(A,8)},
    {D8, GET_PIN(A,9)},
    {D9, GET_PIN(C,7), "pwm3", 2}, /* PWM3-CH2 */
    {D10, GET_PIN(B,6), "pwm4", 1}, /* PWM4-CH1 */
    {D11, GET_PIN(A,7), "pwm1", -1}, /* PWM1-CH1N */
    {D12, GET_PIN(A,6)},
    {D13, GET_PIN(A,5)},
    {D14}, /* I2C1-SDA */
    {D15}, /* I2C1-SCL */
    {D16, GET_PIN(C,13)}, /* user button */
    {A0, GET_PIN(A,0), "adc1", 0}, /* ADC */
    {A1, GET_PIN(A,1), "adc1", 1}, /* ADC */
    {A2, GET_PIN(A,4), "adc1", 4}, /* ADC */
    {A3, GET_PIN(B,0), "adc1", 8}, /* ADC */
    {A4, GET_PIN(C,1), "adc1", 11}, /* ADC */
    {A5, GET_PIN(C,0), "adc1", 10}, /* ADC */
    {A6, RT_NULL, "adc1", 17}, /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A7, RT_NULL, "adc1", 16} /* ADC, On-Chip: internal temperature sensor, ADC_CHANNEL_TEMPSENSOR */
};
