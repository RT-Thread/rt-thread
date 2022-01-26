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
