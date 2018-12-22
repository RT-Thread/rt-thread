/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2015, RT-Thread Develop Team
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
 * 2015-04-14     ArdaFu      first version
 */

#include <rtthread.h>
#include <board.h>
#include "led.h"
#include "gpio.h"

//ASM9260T EVK pin 16-7 LED0, 0: ON, 1 : OFF
void led_init(void)
{
     // enable IOCONFIG GPIO
    outl(((1UL<<25) | (1UL<<4)) , REG_SET(HW_AHBCLKCTRL0));
    HW_SetPinMux(16,7,0);
    HW_GpioSetDir(16,7,1);
}

void led_on(int num)
{
    HW_GpioClrVal(16, 7 );
}

void led_off(int num)
{
    HW_GpioSetVal(16, 7 );
}
