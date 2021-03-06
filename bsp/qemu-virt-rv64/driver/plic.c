/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-31     lizhirui     first version
 */


#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>
#include <riscv.h>
#include <string.h>
#include <stdlib.h>
#include <riscv_io.h>

#include "plic.h"

void plic_set_priority(rt_uint32_t source,rt_uint32_t val)
{
    volatile void *plic_priority = (void *)(rt_size_t)(PLIC_BASE_ADDR + PLIC_PRIORITY_BASE + 4 * source);
    writel(val,plic_priority);
}

void plic_set_thresh(rt_uint32_t val)
{
    volatile void *plic_thresh = (void *)(rt_size_t)(PLIC_BASE_ADDR + PLIC_CONTEXT_BASE);
    writel(val,plic_thresh);
}

void plic_set_ie(rt_uint32_t word_index,rt_uint32_t val)
{
    volatile void *plic_ie = (void *)(rt_size_t)(PLIC_BASE_ADDR + PLIC_ENABLE_BASE + word_index * 4);
    writel(val,plic_ie);
}

void plic_init()
{
    int i;

    plic_set_thresh(0);

    for(i = 0;i < 128;i++)
    {
        plic_set_priority(i,7);
    }
    
    plic_set_ie(0,0xffffffff);
    plic_set_ie(1,0xffffffff);
    plic_set_ie(2,0xffffffff);
    plic_set_ie(3,0xffffffff);

    rt_uint64_t addr;

    for(addr = 0xC001000;addr <= 0xC1F1F80;addr += 4)
    {
        *((rt_uint32_t *)addr) = 0xffffffff;
    }
}