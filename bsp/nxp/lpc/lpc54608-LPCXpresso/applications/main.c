/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_sram.h"

void link_dump(void)
{
#ifdef __GNUC__
    extern unsigned int _sdata;
    extern unsigned int _edata;
    extern unsigned int _sidata;

    extern unsigned int _sbss;
    extern unsigned int _ebss;

    #define DUMP_VAR(__VAR) \
        rt_kprintf("%-20s %p\n", #__VAR, &__VAR)

    DUMP_VAR(_sdata);
    DUMP_VAR(_edata);
    DUMP_VAR(_sidata);
    DUMP_VAR(_sbss);
    DUMP_VAR(_ebss);
#endif
}

int main(void)
{
    rt_kprintf("Hello RT-Thread!\n");

    link_dump();

    while(1)
    {
        rt_thread_mdelay(100);
    }

    return 0;
}
