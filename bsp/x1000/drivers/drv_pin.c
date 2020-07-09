/*
 * File      : drv_pin.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_gpio.h"

#define CORE_BOARD_PIN_NUMBERS  94      //Halley2

#define __X1000_PIN(index, port, pin) { 0, GPIO_PORT_##port, GPIO_Pin_##pin}
#define __X1000_PIN_DEFAULT {-1, 0, 0}


struct pin_index
{
    int         index;
    uint32_t    port;
    uint32_t    pin;
};


static const struct pin_index pins[] =
{
    __X1000_PIN_DEFAULT,            //0 NULL
    __X1000_PIN_DEFAULT,            //1 RST
    __X1000_PIN(2,B,26),
    __X1000_PIN(3,B,25),

    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,

    __X1000_PIN(17,B,7),
    __X1000_PIN(18,B,6),
    __X1000_PIN(19,B,10),

    __X1000_PIN(20,B,9),
    __X1000_PIN(21,B,8),
    __X1000_PIN(22,B,13),
    __X1000_PIN(23,B,11),
    __X1000_PIN(24,B,12),
    __X1000_PIN(25,B,15),
    __X1000_PIN(26,B,14),
    __X1000_PIN(27,B,16),
    __X1000_PIN(28,A,1),
    __X1000_PIN(29,A,0),
    __X1000_PIN(30,B,18),
    __X1000_PIN(31,A,3),
    __X1000_PIN(32,A,2),
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN_DEFAULT,
    __X1000_PIN(37,A,4),
    __X1000_PIN(38,A,6),
    __X1000_PIN(39,B,17),
    __X1000_PIN(40,B,20),
    __X1000_PIN(41,A,5),
    __X1000_PIN(42,A,7),
    __X1000_PIN(43,A,8),
    __X1000_PIN(44,A,9),
    __X1000_PIN(45,A,11),
    __X1000_PIN(46,B,19),
    __X1000_PIN(47,A,10),
};
