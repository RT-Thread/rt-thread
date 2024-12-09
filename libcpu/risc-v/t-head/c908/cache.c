/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-29     lizhirui     first version
 * 2021-11-05     JasonHu      add C908 cache inst
 * 2022-11-09     WangXiaoyao  Support cache coherence operations;
 *                             improve portability and make
 *                             no assumption on undefined behavior
 */

#include <rthw.h>
#include <rtdef.h>
#include <board.h>
#include <riscv.h>

#include "opcode.h"
#include "cache.h"

#define L1_CACHE_BYTES (64)

/**
 * GCC version not support t-head cache flush, so we use fixed code to achieve.
 * The following function cannot be optimized.
 */
static void dcache_wb_range(unsigned long start, unsigned long end) __attribute__((optimize("O0")));
static void dcache_inv_range(unsigned long start, unsigned long end) __attribute__((optimize("O0")));
static void dcache_wbinv_range(unsigned long start, unsigned long end) __attribute__((optimize("O0")));
static void icache_inv_range(unsigned long start, unsigned long end) __attribute__((optimize("O0")));

#define CACHE_OP_RS1 %0
#define CACHE_OP_RANGE(instr)                           \
    {                                                   \
        rt_ubase_t i = start & ~(L1_CACHE_BYTES - 1);   \
        for (; i < end; i += L1_CACHE_BYTES)            \
        {                                               \
            __asm__ volatile(instr ::"r"(i)             \
                             : "memory");               \
        }                                               \
    }

static void dcache_wb_range(unsigned long start, unsigned long end)
{
    CACHE_OP_RANGE(OPC_DCACHE_CVA(CACHE_OP_RS1));
}

static void dcachel1_wb_range(unsigned long start, unsigned long end)
{
    CACHE_OP_RANGE(OPC_DCACHE_CVAL1(CACHE_OP_RS1));
}

static void dcache_inv_range(unsigned long start, unsigned long end)
{
    CACHE_OP_RANGE(OPC_DCACHE_IVA(CACHE_OP_RS1));
}

static void dcache_wbinv_range(unsigned long start, unsigned long end)
{
    CACHE_OP_RANGE(OPC_DCACHE_CIVA(CACHE_OP_RS1));
}

static void icache_inv_range(unsigned long start, unsigned long end)
{
    CACHE_OP_RANGE(OPC_ICACHE_IVA(CACHE_OP_RS1));
}

rt_inline rt_uint32_t rt_cpu_icache_line_size(void)
{
    return L1_CACHE_BYTES;
}

rt_inline rt_uint32_t rt_cpu_dcache_line_size(void)
{
    return L1_CACHE_BYTES;
}

void rt_hw_cpu_icache_invalidate_local(void *addr, int size)
{
    icache_inv_range((unsigned long)addr, (unsigned long)((unsigned char *)addr + size));
    rt_hw_cpu_sync_i();
}

void rt_hw_cpu_dcache_invalidate_local(void *addr, int size)
{
    dcache_inv_range((unsigned long)addr, (unsigned long)((unsigned char *)addr + size));
    rt_hw_cpu_sync();
}

void rt_hw_cpu_dcache_clean_local(void *addr, int size)
{
    dcache_wb_range((unsigned long)addr, (unsigned long)((unsigned char *)addr + size));
    rt_hw_cpu_sync();
}

void rt_hw_cpu_dcache_clean_invalidate_local(void *addr, int size)
{
    dcache_wbinv_range((unsigned long)addr, (unsigned long)((unsigned char *)addr + size));
    rt_hw_cpu_sync();
}

void rt_hw_cpu_dcachel1_clean_local(void *addr, int size)
{
    __asm__ volatile(OPC_DCACHE_CVAL1(a0)::
                         : "memory");
}

/**
 * =====================================================
 * Architecture Independent API
 * =====================================================
 */

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
    {
        rt_hw_cpu_icache_invalidate(addr, size);
    }
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
    {
        rt_hw_cpu_dcache_clean(addr, size);
    }
    else
    {
        rt_hw_cpu_dcache_invalidate(addr, size);
    }
}

void rt_hw_sync_cache_local(void *addr, int size)
{
    rt_hw_cpu_dcachel1_clean_local(addr, size);
    rt_hw_cpu_icache_invalidate_local(addr, size);
}
