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
    {D0}, /* RX */
    {D1}, /* TX */
    {D2}, /* I2C1-SDA */
    {D3}, /* I2C1-SCL */
    {D4, GET_PIN(B,7)},
    {D5, GET_PIN(B,6)},
    {D6, GET_PIN(B,5), "pwm3", 2},/* PWM */
    {D7, GET_PIN(B,4), "pwm3", 1}, /* PWM */
    {D8, GET_PIN(B,3), "pwm2", 2}, /* PWM */
    {D9, GET_PIN(A,15), "pwm2", 1}, /* PWM */
    {D10}, /* USB-DP */
    {D11}, /* USB-DM */
    {D12}, /* UART1-RX */
    {D13}, /* UART1-TX */
    {D14, GET_PIN(A,8), "pwm1", 1}, /* PWM */
    {D15, GET_PIN(B,15)},
    {D16, GET_PIN(B,14)},
    {D17, GET_PIN(B,13), "pwm1", -1}, /* PWM */
    {D18, GET_PIN(B,12)},
    {D19, GET_PIN(C,13)}, /* user led1 */
    {D20, GET_PIN(C,14)},
    {D21, GET_PIN(C,15)},
    {D22}, /* UART2-TX */
    {D23}, /* UART2-RX */
    /* The connection of RTdunio SPI has not been completed, *
     * and it can only be used as a common GPIO at present.  */
    {D24, GET_PIN(A,5)}, /* SPI-SCK */
    {D25, GET_PIN(A,6)}, /* SPI-MISO */
    {D26, GET_PIN(A,7)}, /* SPI-MOSI */
    {D27}, /* UART3-TX */
    {D28}, /* UART3-RX */
    {A0, GET_PIN(A,0), "adc1", 0}, /* ADC */
    {A1, GET_PIN(A,1), "adc1", 1}, /* ADC */
    {A2, GET_PIN(A,4), "adc1", 4}, /* ADC */
    {A3, GET_PIN(B,0), "adc1", 8}, /* ADC */
    {A4, GET_PIN(B,1), "adc1", 9}, /* ADC */
    {A5, RT_NULL, "adc1", 17}, /* ADC, On-Chip: internal reference voltage, ADC_CHANNEL_VREFINT */
    {A6, RT_NULL, "adc1", 16} /* ADC, On-Chip: internal temperature sensor, ADC_CHANNEL_TEMPSENSOR */
};
