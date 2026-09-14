/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-29     lizhirui     first version
 * 2021-11-05     JasonHu      add c906/c908 cache inst
 * 2022-11-09     WangXiaoyao  Support cache coherence operations;
 *                             improve portability and make
 *                             no assumption on undefined behavior
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#include <rthw.h>
#include <rtcompiler.h>

#include <cache.h>
#include <opcode.h>
#ifdef RT_USING_SMP
#include <smp_call.h>
#endif

#define THEAD_CMD_OP(_op, _sync_op, _start, _size, _cachesize)      \
    rt_ubase_t _block = (rt_ubase_t)_start & ~(_cachesize - 1UL)    \
    rt_ubase_t _end = (rt_ubase_t)_start + _size;                   \
    for (; _block < _end; _block += _cachesize)                     \
    {                                                               \
        __asm__ volatile (_op(%0)::"r"(_block):"memory");           \
    }                                                               \
    __asm__ volatile (_sync_op:::"memory");

static void thead_icache_invalidate_local(void *data)
{
    rt_ubase_t *start_size = data;
    rt_uint32_t cachesize = riscv_cache_get_cbom_block_size();

    THEAD_CMD_OP(OPC_ICACHE_IVA, OPC_SYNC_IS, start_size[0], start_size[1], cachesize);
}

static void thead_icache_invalidate(void *addr, int size)
{
    rt_ubase_t start_size[2] = { (rt_ubase_t)addr, size };

    thead_icache_invalidate_local(start_size);

#ifdef RT_USING_SMP
    rt_smp_call_each_cpu(thead_icache_invalidate_local, start_size, SMP_CALL_WAIT_ALL);
#endif
}

static void thead_icache_invalidate_all_local(void *data)
{
    RT_UNUSED(data);

    __asm__ volatile(OPC_ICACHE_IALL "\n\t" OPC_SYNC_I:::"memory");
}

static void thead_icache_invalidate_all(void)
{
    thead_icache_invalidate_all_local(RT_NULL);

#ifdef RT_USING_SMP
    rt_smp_call_each_cpu(thead_icache_invalidate_all_local, RT_NULL, SMP_CALL_WAIT_ALL);
#endif
}

static void thead_dcache_invalidate(void *addr, int size)
{
    rt_uint32_t cachesize = riscv_cache_get_cbom_block_size();

    THEAD_CMD_OP(OPC_DCACHE_IVA, OPC_SYNC_S, addr, size, cachesize);
}

static void thead_dcache_clean(void *addr, int size)
{
    rt_uint32_t cachesize = riscv_cache_get_cbom_block_size();

    THEAD_CMD_OP(OPC_DCACHE_CVA, OPC_SYNC_S, addr, size, cachesize);
}

static void thead_dcache_flush(void *addr, int size)
{
    rt_uint32_t cachesize = riscv_cache_get_cbom_block_size();

    THEAD_CMD_OP(OPC_DCACHE_CIVA, OPC_SYNC_S, addr, size, cachesize);
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
        thead_dcache_clean(addr, size);
    }
    else
    {
        thead_dcache_invalidate(addr, size);
    }
}

void rt_hw_cpu_icache_invalidate_all(void)
{
    thead_icache_invalidate_all();
}

void rt_hw_cpu_icache_invalidate(void *addr, rt_size_t size)
{
    thead_icache_invalidate(addr, size);
}

void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, rt_size_t size)
{
    thead_dcache_flush(addr, size);
}

void rt_hw_icache_invalidate_all(void)
{
    thead_icache_invalidate_all();
}

/**
 * @brief Synchronize cache to Point of Unification
 */
void rt_hw_sync_cache_local(void *addr, int size)
{
    __asm__ volatile(OPC_DCACHE_CVAL1(a0)::: "memory");

    thead_icache_invalidate(addr, size);
}
