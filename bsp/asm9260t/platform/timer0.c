/*
 * File      : timer0.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2015, RT-Thread Development Team
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
 * 2015-04-29     ArdaFu       first version
 */

#include "timer0.h"
#include "asm9260t.h"
#include "rtthread.h"
void hw_timer0_init(void)
{
    uint32_t pclk;

    // enable timer0's clock, reset timer0
    outl((1<<4), REG_SET(HW_AHBCLKCTRL1));
    outl((1<<4), REG_CLR(HW_PRESETCTRL1));
    outl((1<<4), REG_SET(HW_PRESETCTRL1));

    outl((1<<0), REG_CLR(HW_TIMER0_TCR));

    outl((3<<0), REG_CLR(HW_TIMER0_CTCR));

    outl((3<<0), REG_CLR(HW_TIMER0_DIR));

    outl(0, REG_CLR(HW_TIMER0_PR));
    outl(0, REG_CLR(HW_TIMER0_PC));

    outl((7<<0), REG_CLR(HW_TIMER0_MCR));
    outl((3<<0), REG_SET(HW_TIMER0_MCR));

    pclk = (inl(HW_SYSPLLCTRL)&0x1FF)*1000000u/4u;
    outl(pclk/RT_TICK_PER_SECOND, HW_TIMER0_MR0);

    outl((1<<4), REG_SET(HW_TIMER0_TCR));
    outl((1<<4), REG_CLR(HW_TIMER0_TCR));
    outl((1<<0), REG_SET(HW_TIMER0_TCR));
}
