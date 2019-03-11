/*
 * File      : drv_cache.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-02     tanek        first implementation
 */

#include <rtthread.h>
#include <rthw.h>
#include <fsl_cache.h>

void rt_hw_cpu_icache_enable(void)
{
    SCB_EnableICache();
}

void rt_hw_cpu_icache_disable(void)
{
    SCB_DisableICache();
}

rt_base_t rt_hw_cpu_icache_status(void)
{
    return 0;
}

void rt_hw_cpu_icache_ops(int ops, void* addr, int size)
{
    if (ops & RT_HW_CACHE_INVALIDATE)
    {
        ICACHE_InvalidateByRange((uint32_t)addr, size);
    }
}

void rt_hw_cpu_dcache_enable(void)
{
    SCB_EnableDCache();
}

void rt_hw_cpu_dcache_disable(void)
{
    SCB_DisableDCache();
}

rt_base_t rt_hw_cpu_dcache_status(void)
{
    return 0;
}

void rt_hw_cpu_dcache_ops(int ops, void* addr, int size)
{
    if (ops & (RT_HW_CACHE_FLUSH | RT_HW_CACHE_INVALIDATE))
    {
        DCACHE_CleanInvalidateByRange((uint32_t)addr, size);
    }
    else if (ops & RT_HW_CACHE_FLUSH)
    {
        DCACHE_CleanByRange((uint32_t)addr, size);
    }
    else if (ops & RT_HW_CACHE_INVALIDATE)
    {
        DCACHE_InvalidateByRange((uint32_t)addr, size);
    }
    else
    {
        RT_ASSERT(0);
    }
}
