/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-26     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "hw.mmu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void *rt_ioremap(void *paddr, size_t size)
{
    RT_UNUSED(size);
    return paddr;
}

void rt_iounmap(void *vaddr)
{
    RT_UNUSED(vaddr);
}
