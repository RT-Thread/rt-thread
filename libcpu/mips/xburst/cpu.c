/*
 * File      : cpu.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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
 * 2010-07-09     Bernard      first version
 * 2010-09-11     Bernard      add CPU reset implementation
 */
#include <rtthread.h>
#include <board.h>

/**
 * @addtogroup Ingenic
 */
/*@{*/

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset()
{
    /* open the watch-dog */
    REG_WDT_TCSR  = WDT_TCSR_EXT_EN;
    REG_WDT_TCSR |= WDT_TCSR_PRESCALE_1024;
    REG_WDT_TDR   = 0x03;
    REG_WDT_TCNT  = 0x00;
    REG_WDT_TCER |= WDT_TCER_TCEN;

    rt_kprintf("reboot system...\n");
    while (1);
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
    rt_kprintf("shutdown...\n");

    while (1);
}

/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}

/*@}*/
