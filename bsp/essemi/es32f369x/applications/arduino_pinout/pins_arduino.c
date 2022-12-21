/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-07     shiwa        Adapt ES32F369x
 */
#include <Arduino.h>
#include <board.h>
#include "drv_gpio.h"
#include "pins_arduino.h"

/*
    {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
    [] means optional
    Digital pins must NOT give the device name and channel.
    Analog pins MUST give the device name and channel(ADC, PWM or DAC).
    Arduino Pin must keep in sequence.
*/
const pin_map_t pin_map_table[]=
{
    {D0, GET_PIN(E,3), "uart2"}, /* UART2-RX */
    {D1, GET_PIN(E,2), "uart2"}, /* UART2-TX */
    {D2, GET_PIN(E,4)}, /* GPIO0 */
    {D3, GET_PIN(A,2),"pwm2",3}, /* PWM2 GP32C4T0 CH3 */
    {D4, GET_PIN(E,5)}, /* GPIO1 */
    {D5, GET_PIN(A,1),"pwm2",2}, /* PWM2 GP32C4T0 CH2 */
    {D6, GET_PIN(A,0),"pwm2",1}, /* PWM2 GP32C4T0 CH1 */
    {D7, GET_PIN(E,6)}, /* GPIO2 */

    {D8, GET_PIN(B,8)}, /* GPIO3 */
    {D9, GET_PIN(B,9)}, /* GPIO4 */
    {D10, GET_PIN(B,0)}, /* GPIO5, SS */
    {D11, GET_PIN(B,5), "spi0"}, /* SPI0-MOSI */
    {D12, GET_PIN(B,4), "spi0"}, /* SPI0-MISO */
    {D13, GET_PIN(D,3), "spi0"}, /* SPI0-SCK */

    {D14, GET_PIN(B,7), "i2c0"}, /* I2C0-SDA */
    {D15, GET_PIN(B,6), "i2c0"}, /* I2C0-SCL */

    {D16, GET_PIN(C,8)}, /* LED4 */
    {D17, GET_PIN(C,12)}, /* LED5 */
    {D18, GET_PIN(C,7)}, /* LED6 */
    {D19, GET_PIN(C,6)}, /* LED7 */

    {D20, GET_PIN(F,1)}, /* KEY_UP */
    {D21, GET_PIN(F,4)}, /* KEY_DOWN */
    {D22, GET_PIN(F,6)}, /* KEY_LEFT */
    {D23, GET_PIN(F,0)}, /* KEY_RIGHT */
    {D24, GET_PIN(F,7)}, /* KEY_CENTER */

    {A0, GET_PIN(C,0),"adc0",0}, /* ADC0 */
    {A1, GET_PIN(C,1),"adc0",1}, /* ADC0 */
    {A2, GET_PIN(C,2),"adc0",2}, /* ADC0 */
    {A3, GET_PIN(C,3),"adc0",3}, /* ADC0 */
    {A4, GET_PIN(A,4),"adc0",4}, /* ADC0 */
    {A5, GET_PIN(A,5),"adc0",5}, /* ADC0 */
};
