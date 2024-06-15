/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-02     tanek        first implementation
 * 2019-04-27     misonyo      update to cortex-m7 series
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdef.h>
#include <board.h>

/* The L1-caches on all CortexÂ®-M7s are divided into lines of 32 bytes. */
#define L1CACHE_LINESIZE_BYTE       (32)

#ifdef RT_USING_CACHE

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
    rt_uint32_t address = (rt_uint32_t)addr & (rt_uint32_t) ~(L1CACHE_LINESIZE_BYTE - 1);
    rt_int32_t size_byte = size + address - (rt_uint32_t)addr;
    rt_uint32_t linesize = 32U;
    if (ops & RT_HW_CACHE_INVALIDATE)
    {
        __DSB();
        while (size_byte > 0)
        {
            SCB->ICIMVAU = address;
            address += linesize;
            size_byte -= linesize;
        }
        __DSB();
        __ISB();
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
    rt_uint32_t startAddr = (rt_uint32_t)addr & (rt_uint32_t)~(L1CACHE_LINESIZE_BYTE - 1);
    rt_uint32_t size_byte = size + (rt_uint32_t)addr - startAddr;
    rt_uint32_t clean_invalid = RT_HW_CACHE_FLUSH | RT_HW_CACHE_INVALIDATE;

    if ((ops & clean_invalid) == clean_invalid)
    {
        SCB_CleanInvalidateDCache_by_Addr((rt_uint32_t *)startAddr, size_byte);
    }
    else if (ops & RT_HW_CACHE_FLUSH)
    {
        SCB_CleanDCache_by_Addr((rt_uint32_t *)startAddr, size_byte);
    }
    else if (ops & RT_HW_CACHE_INVALIDATE)
    {
        SCB_InvalidateDCache_by_Addr((rt_uint32_t *)startAddr, size_byte);
    }
    else
    {
        RT_ASSERT(0);
    }
}

#endif /* RT_USING_CACHE */

