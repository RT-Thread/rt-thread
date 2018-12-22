/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2017-5-30      Bernard      the first version
 */

#include "rtthread.h"
#include "drv_clock.h"

int main(int argc, char **argv)
{
    rt_kprintf("periph_get_pll_clk:%d\n", periph_get_pll_clk());
    rt_kprintf("cpu_get_clk:%d\n", cpu_get_clk());
    rt_kprintf("ahb_get_clk:%d\n", ahb_get_clk());
    rt_kprintf("apb_get_clk:%d\n", apb_get_clk());

    return 0;
}
