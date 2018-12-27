/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
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
 * 2011-01-13     weety      first version
 */

#include <rtthread.h>
#include <at91sam9g45.h>
#include "led.h"

// BYHX A-Plus Board
#define LED0    (1UL << 30)
#define LED1    (1UL << 31)
#define LED2    (1UL << 29)
#define LED3    (1UL << 28)
#define LED_ALL     (LED0 | LED1 | LED2 | LED3)

void led_init(void)
{
	AT91C_BASE_PIOC->PIO_PER   = LED_ALL;
	AT91C_BASE_PIOC->PIO_OER   = LED_ALL;
	AT91C_BASE_PIOC->PIO_PPUER = LED_ALL;
	AT91C_BASE_PIOC->PIO_SODR  = LED_ALL;
}

const static rt_uint32_t m_leds[] = { LED0, LED1, LED2, LED3 };

void led_on(int num)
{
    if (num < 4) AT91C_BASE_PIOC->PIO_CODR = m_leds[num];
}

void led_off(int num)
{
    if (num < 4) AT91C_BASE_PIOC->PIO_SODR = m_leds[num];
}
