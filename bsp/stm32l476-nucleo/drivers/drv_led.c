/*
 * File      : drv_led.c
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
 * Date           Author        Notes
 */

#include "board.h"
#include "drv_led.h"
#include <drivers/pin.h>

//the pin number can be find in :goip.c pins[].
//in nucleo-l476rg board,the green led is attached to PA5 which the number is 21.
#define LED 21

/**
 * This function light up LED
 *
 * @param led LED number (6)
 */
void led_set(int led)
{
    if (led == 0)
    {
       rt_pin_write(LED, 1);
    }
}

/**
 * This function return LED status, on or off
 *
 * @param led LED number (0-1)
 */
int led_get(int led)
{
    int ret = 0;

    if (led == 0)
    {
        ret = rt_pin_read(LED);
    }

    return ret;
}

/**
 * This function turn off LED
 *
 * @param led LED number (0-1)
 */
void led_clear(int led)
{
    if (led == 0)
    {
        rt_pin_write(LED, 0);
    }
}

/**
 * This function toggle LED, switch from on to off or vice versa
 *
 * @param led LED number (0-1)
 */
void led_toggle(int led)
{
    int ret = 0;
	
    ret = rt_pin_read(LED);
	
    if(ret==1)
    {
        ret=0;
    }
    else if(ret==0)
    {
        ret=1;
    }

    if (led == 0)
    {
        rt_pin_write(LED, ret);
    }
}

/**
 * This function light up LEDs according value of 2 least significat bits
 *
 * @param value Bit pattern
 */
void led_value(int value)
{
	rt_pin_write(LED, value);
}

/**
 * This function initialize LED interface
 */
void led_init(void)
{
	rt_pin_mode(LED, PIN_MODE_OUTPUT);
}

/**
 * This function initialize LED interface
 */
void led_deinit(void)
{
	rt_pin_mode(LED, PIN_MODE_INPUT);
}
