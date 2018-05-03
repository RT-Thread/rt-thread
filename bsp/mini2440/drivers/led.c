/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-12-27     rdghx        mini2440
 */

/**
 * @addtogroup mini2440
 */
/*@{*/

#include <s3c24x0.h>
#include "led.h"

void rt_hw_led_init(void)
{
	/* GPB5,GPB6,GPB7,GPB8 for LED */
	GPBCON = GPBCON & (~(0xff << 10)) | (0x55 << 10);
	GPBUP  |= (0x0f << 5);
}

void rt_hw_led_on(unsigned char value)
{
	GPBDAT &= ~ ((value & 0x0f) << 5);
}

void rt_hw_led_off(unsigned char value)
{
	GPBDAT |= (value & 0x0f) << 5;
}

/*@}*/

