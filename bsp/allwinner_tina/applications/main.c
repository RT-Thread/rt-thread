/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
