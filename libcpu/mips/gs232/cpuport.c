/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Change Logs:
 * Date                Author         Notes
 * 2010-07-09     Bernard        first version
 * 2010-09-11     Bernard        add CPU reset implementation
 * 2015-07-06     chinesebear  modified for loongson 1c
 */

#include <rtthread.h>
#include "gs232.h"

/**
 * @addtogroup Loongson GS232
 */

/*@{*/

/**
 * this function will reset CPU
 *
 */
RT_WEAK void rt_hw_cpu_reset(void)
{
    /* open the watch-dog */
    WDT_EN = 0x01; 		/* watch dog enable */
    WDT_TIMER = 0x01;	/* watch dog will be timeout after 1 tick */
    WDT_SET = 0x01;		/* watch dog start */

    rt_kprintf("reboot system...\n");
    while (1);
}

/**
 * this function will shutdown CPU
 *
 */
RT_WEAK void rt_hw_cpu_shutdown(void)
{
    rt_kprintf("shutdown...\n");

    while (1);
}


#define Hit_Invalidate_I    0x10
#define Hit_Invalidate_D    0x11
#define CONFIG_SYS_CACHELINE_SIZE   32
#define Hit_Writeback_Inv_D 0x15


void flush_cache(unsigned long start_addr, unsigned long size)
{
    unsigned long lsize = CONFIG_SYS_CACHELINE_SIZE;
    unsigned long addr = start_addr & ~(lsize - 1);
    unsigned long aend = (start_addr + size - 1) & ~(lsize - 1);

    while (1) {
        cache_op(Hit_Writeback_Inv_D, addr);
        cache_op(Hit_Invalidate_I, addr);
        if (addr == aend)
            break;
        addr += lsize;
    }
}


/*@}*/

