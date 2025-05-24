/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-29     lizhirui     first version
 * 2025-04-20     GuEe-GUI     Port to the DM
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtcompiler.h>

#include <cpu.h>
#include <sbi.h>
#include <cache.h>
#include <opcode.h>
#include <isa_ext.h>
#ifdef RT_USING_SMP
#include <smp_call.h>
#endif
#ifdef RT_USING_HWCACHE
#include <drivers/hwcache.h>
#endif

static rt_uint32_t riscv_cbom_block_size;

void riscv_cache_set_cbom_block_size(rt_uint32_t size)
{
    if (!riscv_isa_ext_test(ZICBOM))
    {
        RT_ASSERT(0);
        return;
    }

    HWREG32(&riscv_cbom_block_size) = size;
    rt_hw_wmb();
}

rt_uint32_t riscv_cache_get_cbom_block_size(void)
{
    rt_hw_rmb();
    return HWREG32(&riscv_cbom_block_size);
}

rt_always_inline void local_flush_icache_all(void)
{
    __asm__ volatile (OPC_FENCE_I:::"memory");
}

rt_inline void ipi_remote_fence_i(void *data)
{
    RT_UNUSED(data);

    local_flush_icache_all();
}

rt_weak void rt_hw_cpu_icache_enable(void)
{
#ifdef RT_USING_HWCACHE
    rt_hwcache_icache_enable();
#endif
}

rt_weak void rt_hw_cpu_icache_disable(void)
{
#ifdef RT_USING_HWCACHE
    rt_hwcache_icache_disable();
#endif
}

rt_weak rt_base_t rt_hw_cpu_icache_status(void)
{
#ifdef RT_USING_HWCACHE
    return rt_hwcache_icache_status();
#elif !defined(ARCH_RISCV_DISABLE_FENCE_I)
    return 0;
#else /* !ARCH_RISCV_DISABLE_FENCE_I */
    return !0;
#endif /* RT_USING_HWCACHE */
}

rt_weak void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
#ifdef RT_USING_HWCACHE
    rt_hwcache_icache_ops(ops, addr, size);
#elif !defined(ARCH_RISCV_DISABLE_FENCE_I)
    /*
     * RISC-V doesn't have an instruction to flush parts of the icache,
     * so instead we just flush the whole thing.
     */
    if (ops == RT_HW_CACHE_INVALIDATE)
    {
        local_flush_icache_all();

    #if (defined(RT_USING_SMP) && RT_CPUS_NR > 1) || defined(RT_USING_AMP)
    #ifndef ARCH_RISCV_M_MODE
        if (has_ipi_extension)
        {
            sbi_remote_fence_i(RT_NULL);
        }
        else
    #endif /* !ARCH_RISCV_M_MODE */
        {
            rt_smp_call_each_cpu(ipi_remote_fence_i, RT_NULL, SMP_CALL_WAIT_ALL);
        }
    #endif /* RT_USING_SMP */
    }
    RT_UNUSED(addr);
    RT_UNUSED(size);
#else /* !ARCH_RISCV_DISABLE_FENCE_I */
    RT_UNUSED(ops);
    RT_UNUSED(addr);
    RT_UNUSED(size);
#endif /* RT_USING_HWCACHE */
}

rt_weak void rt_hw_cpu_dcache_enable(void)
{
#ifdef RT_USING_HWCACHE
    rt_hwcache_dcache_enable();
#endif
}

rt_weak void rt_hw_cpu_dcache_disable(void)
{
#ifdef RT_USING_HWCACHE
    rt_hwcache_dcache_disable();
#endif
}

rt_weak rt_base_t rt_hw_cpu_dcache_status(void)
{
#ifdef RT_USING_HWCACHE
    return rt_hwcache_dcache_status();
#else
    return riscv_cache_get_cbom_block_size() == 0;
#endif
}

rt_weak void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
#ifdef RT_USING_HWCACHE
    rt_hwcache_dcache_ops(ops, addr, size);
#else
    rt_uint32_t cbom_block_size;

    cbom_block_size = riscv_cache_get_cbom_block_size();

    if (cbom_block_size)
    {
        if (ops == RT_HW_CACHE_FLUSH)
        {
            __asm__ volatile (
                    "   mv      a0, %1\n\t"
                    "   j       2f\n\t"
                    "3:\n\t"
                        OPC_CBO_CLEAN(a0)
                    "   add     a0, a0, %0\n\t"
                    "2:\n\t"
                    "   bltu    a0, %2, 3b\n\t"
                    ::"r"(cbom_block_size),
                      "r"((rt_ubase_t)addr & ~(cbom_block_size - 1UL)),
                      "r"((rt_ubase_t)addr + size)
                    : "a0");
        }
        else if (ops == RT_HW_CACHE_INVALIDATE)
        {
            __asm__ volatile (
                    "   mv      a0, %1\n\t"
                    "   j       2f\n\t"
                    "3:\n\t"
                        OPC_CBO_INVAL(a0)
                    "   add     a0, a0, %0\n\t"
                    "2:\n\t"
                    "   bltu    a0, %2, 3b\n\t"
                    ::"r"(cbom_block_size),
                      "r"((rt_ubase_t)addr & ~(cbom_block_size - 1UL)),
                      "r"((rt_ubase_t)addr + size)
                    : "a0");
        }
    }
    else
    {
        __asm__ volatile (".rept 6\n nop\n .endr\n");
    }
#endif /* RT_USING_HWCACHE */
}

rt_weak void rt_hw_cpu_icache_invalidate_all(void)
{
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, RT_NULL, ~0U);
}

rt_weak void rt_hw_cpu_icache_invalidate(void *addr, rt_size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr, size);
}

rt_weak void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, rt_size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr, size);
}

rt_weak void rt_hw_icache_invalidate_all(void)
{
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, RT_NULL, ~0U);
}

rt_weak void rt_hw_sync_cache_local(void *addr, int size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr, size);
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, addr, size);
}
