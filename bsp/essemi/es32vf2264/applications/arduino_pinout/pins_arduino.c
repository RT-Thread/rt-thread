/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-05     shiwa        ES32VF2264
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
    {D0, GET_PIN(C,11), "cuart2"}, /* UART2-RX */
    {D1, GET_PIN(C,10), "cuart2"}, /* UART2-TX */
    {D2, GET_PIN(B,5)}, /* GPIO0 */
    {D3, GET_PIN(C,15),"pwm3",4}, /* PWM2 GP16C4T2 CH4 */
    {D4, GET_PIN(B,4)}, /* GPIO1 */
    {D5, GET_PIN(C,7),"pwm2",2}, /* PWM2 GP16C4T1 CH2 */
    {D6, GET_PIN(C,6),"pwm0",1}, /* PWM2 AD16C4T0 CH1 */
    {D7, GET_PIN(A,8)}, /* GPIO2 */

    {D8, GET_PIN(B,11)}, /* GPIO3 */
    {D9, GET_PIN(B,10)}, /* GPIO4 */
    {D10, GET_PIN(A,4)}, /* GPIO5, SS */
    {D11, GET_PIN(A,7), "spi0"}, /* SPI0-MOSI */
    {D12, GET_PIN(A,6), "spi0"}, /* SPI0-MISO */
    {D13, GET_PIN(A,5), "spi0"}, /* SPI0-SCK */

    {D14, GET_PIN(B,3), "i2c0"}, /* I2C0-SDA */
    {D15, GET_PIN(B,2), "i2c0"}, /* I2C0-SCL */

    {D16, GET_PIN(A,15)}, /* LED3 */
    {D17, GET_PIN(C,12)}, /* LED4 */
    {D18, GET_PIN(C,13)}, /* LED5 */
    {D19, GET_PIN(C,14)}, /* LED6 */

    {D20, GET_PIN(B,7)}, /* KEY_UP */
    {D21, GET_PIN(B,9)}, /* KEY_DOWN */
    {D22, GET_PIN(B,6)}, /* KEY_LEFT */
    {D23, GET_PIN(B,8)}, /* KEY_RIGHT */
    {D24, GET_PIN(D,2)}, /* KEY_CENTER */
    {D25, GET_PIN(B,15)},        /* GPIO/SPI1_MOSI */
    {D26, GET_PIN(B,14)},         /* GPIO/SPI1_MISO */
    {D27, GET_PIN(B,13)},        /* GPIO/SPI1_SCK */
    {D28, GET_PIN(B,12)},        /* GPIO/SPI1_NSS */


    {A0, GET_PIN(C,1),"adc0",1}, /* ADC0 */
    {A1, GET_PIN(C,2),"adc0",2}, /* ADC0 */
};
