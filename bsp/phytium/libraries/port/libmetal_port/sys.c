/*
 * Copyright : (C) 2025 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: sys.c
 * Created Date: 2025-04-30 15:18:08
 * Last Modified: 2025-05-07 14:53:21
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0    LiuSM    2025-04-30 15:18:08  First version
 */

#include <metal/compiler.h>
#include <metal/io.h>
#include <metal/sys.h>
#include <stdint.h>
#include "faarch.h"
#include "mmu.h"
#include "cache.h"
#include "rtthread.h"

#define _DISABLE_INTERRUPTS()           \
    __asm volatile("MSR DAIFSET, #2" :: \
                    : "memory");     \
    __asm volatile("DSB SY");           \
    __asm volatile("ISB SY");

#define _ENABLE_INTERRUPTS()            \
    __asm volatile("MSR DAIFCLR, #2" :: \
                    : "memory");     \
    __asm volatile("DSB SY");           \
    __asm volatile("ISB SY");

void sys_irq_restore_enable(unsigned int flags)
{
#ifdef __aarch64__
    _ENABLE_INTERRUPTS();
#else
    MTCPSR(flags);
#endif
}

unsigned int sys_irq_save_disable(void)
{
    unsigned int state = 0;

#ifdef __aarch64__
    _DISABLE_INTERRUPTS();
#else
    state = MFCPSR();
    MTCPSR(state | 0xc0);
#endif

    return state;
}

void metal_machine_cache_flush(void *addr, unsigned int len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)addr, len);;
}

void metal_machine_cache_invalidate(void *addr, unsigned int len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)addr, len);
}

/**
 * @brief poll function until some event happens
 */
void metal_weak metal_generic_default_poll(void)
{
    metal_asm volatile("wfi");
}



 void *metal_machine_io_mem_map(void *va, metal_phys_addr_t pa,
                                size_t size, unsigned int flags)
{
    // rt_aspace_t aspace = NULL;
    // aspace = (rt_aspace_t)rt_malloc(sizeof(*aspace));
    // printf("sys_io_mem_map: va=%p, pa=0x%lx, size=0x%lx, flags=0x%x\n", va, pa, size, flags);
    // printf("sys_io_mem_map: aspace=0x%p\n", aspace);
    // int err = RT_EOK;
    // void *ret;
    // ret = rt_hw_mmu_map(aspace, va, pa, size, flags);
    // if (ret == RT_NULL)
    // {
    //     err = -RT_ERROR;
    // }
    // return err;
    (void)va;
    (void)pa;
    (void)size;
    (void)flags;

    return va;
}

