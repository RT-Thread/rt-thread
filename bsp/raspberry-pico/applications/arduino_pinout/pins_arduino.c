/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-27     ShichengChu  first version
 */

#include <Arduino.h>
#include <board.h>
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
    {D0, 0, "uart1"},                   /* Serial-TX */
    {D1, 1, "uart1"},                   /* Serial-RX */
    {D2, 2},
    {D3, 3},
    {D4, 4},
    {D5, 5},
    {D6, 6},
    {D7, 7},
    {D8, 8, "uart2"},                   /* Serial2-TX */
    {D9, 9, "uart2"},                   /* Serial2-RX */
    {D10, 10},
    {D11, 11},
    {D12, 12},
    {D13, 13},
    {D14, 14},
    {D15, 15},
    {D16, 16},
    {D17, 17},
    {D18, 18},
    {D19, 19},
    {D20, 20},
    {D21, 21},
    {D22, 22},
    {D23, 25},                          /* LED_BUILTIN */
    {D24, 26},
    {D25, 27},
};
