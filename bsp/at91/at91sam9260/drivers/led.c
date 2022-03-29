/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#include <rtthread.h>
#include <at91sam926x.h>
#include "led.h"

#if 1
// GB9260 board
#define PIO_LED     AT91_PIOB
#define LED1        (1 << 25)   // LED_SYS
#define LED2        (0)
#define LED3        (1 << 23)   // LED_USR
#define LED_ALL     (LED1 | LED2 | LED3)
#else
#define PIO_LED     AT91_PIOC
#define LED1        (1 << 8)
#define LED2        (1 << 11)
#define LED3        (1 << 6)
#define LED_ALL     (LED1 | LED2 | LED3)
#endif

void led_init(void)
{
    at91_sys_write(PIO_LED+0x00, LED_ALL);
    at91_sys_write(PIO_LED+0x10, LED_ALL);
    at91_sys_write(PIO_LED+0x64, LED_ALL);
    at91_sys_write(PIO_LED+0x30, LED_ALL);
}

void led_on(int num)
{
    switch(num)
    {
        case 1:
            at91_sys_write(PIO_LED+0x34, LED1);
            break;
        case 2:
            at91_sys_write(PIO_LED+0x34, LED2);
            break;
        case 3:
            at91_sys_write(PIO_LED+0x34, LED3);
            break;
        default:
            break;
    }
}

void led_off(int num)
{
    switch(num)
    {
        case 1:
            at91_sys_write(PIO_LED+0x30, LED1);
            break;
        case 2:
            at91_sys_write(PIO_LED+0x30, LED2);
            break;
        case 3:
            at91_sys_write(PIO_LED+0x30, LED3);
            break;
        default:
            break;
    }
}
