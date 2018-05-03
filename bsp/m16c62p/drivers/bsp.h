/*
 * File      : bsp.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-09     fify      the first version
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
*/

#ifndef  __BSP_H__
#define  __BSP_H__

#include <rtthread.h>

#define CPU_CLK_FREQ 14000000                    /* CPU frequency, in Hz*/

void system_init(void);

void led_on(void);
void led_off(void);

#endif
