/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-28     luhuadong         first version
 */

#include <rtthread.h>
#include "led.h"

int main(void)
{
    rt_kprintf("Hello, World!\n");

    led_init();

    while (1)
    {
        led_toggle();
        rt_thread_mdelay(500);
    }

    return 0;
}

static void give_me_five(void)
{
    rt_kprintf("\n");
    rt_kprintf("\n");
    rt_kprintf("                  SIFIVE, INC.\n");
    rt_kprintf("\n");
    rt_kprintf("           5555555555555555555555555\n");
    rt_kprintf("          5555                   5555\n");
    rt_kprintf("         5555                     5555\n");
    rt_kprintf("        5555                       5555\n");
    rt_kprintf("       5555       5555555555555555555555\n");
    rt_kprintf("      5555       555555555555555555555555\n");
    rt_kprintf("     5555                             5555\n");
    rt_kprintf("    5555                               5555\n");
    rt_kprintf("   5555                                 5555\n");
    rt_kprintf("  5555555555555555555555555555          55555\n");
    rt_kprintf("   55555           555555555           55555\n");
    rt_kprintf("     55555           55555           55555\n");
    rt_kprintf("       55555           5           55555\n");
    rt_kprintf("         55555                   55555\n");
    rt_kprintf("           55555               55555\n");
    rt_kprintf("             55555           55555\n");
    rt_kprintf("               55555       55555\n");
    rt_kprintf("                 55555   55555\n");
    rt_kprintf("                   555555555\n");
    rt_kprintf("                     55555\n");
    rt_kprintf("                       5\n");
    rt_kprintf("\n");

    rt_kprintf("\n");
    rt_kprintf("               Welcome to SiFive!\n");
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(give_me_five, Show the SiFive logo)
#endif
