/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "s3c24x0.h"

/**
 * @addtogroup S3C24X0
 */
/*@{*/

#define ICACHE_MASK (rt_uint32_t)(1 << 12)
#define DCACHE_MASK (rt_uint32_t)(1 << 2)
#define CACHE_LINE_SIZE 32

#ifdef __GNUC__
rt_inline rt_uint32_t cp15_rd(void)
{
    rt_uint32_t i;

    asm("mrc p15, 0, %0, c1, c0, 0"
        : "=r"(i));
    return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
    __asm__ __volatile__(
        "mrc  p15,0,r0,c1,c0,0\n\t"
        "orr  r0,r0,%0\n\t"
        "mcr  p15,0,r0,c1,c0,0"
        :
        : "r"(bit)
        : "memory");
}

rt_inline void cache_disable(rt_uint32_t bit)
{
    __asm__ __volatile__(
        "mrc  p15,0,r0,c1,c0,0\n\t"
        "bic  r0,r0,%0\n\t"
        "mcr  p15,0,r0,c1,c0,0"
        :
        : "r"(bit)
        : "memory");
}

void dcache_clean(rt_uint32_t buffer, rt_uint32_t size)
{
    unsigned int ptr;

    ptr = buffer & ~(CACHE_LINE_SIZE - 1);

    while (ptr < buffer + size)
    {
        asm volatile("mcr p15, 0, %0, c7, c10, 1": :"r"(ptr));

        ptr += CACHE_LINE_SIZE;
    }
}

void dcache_invalidate(rt_uint32_t buffer, rt_uint32_t size)
{
    unsigned int ptr;

    ptr = buffer & ~(CACHE_LINE_SIZE - 1);

    while (ptr < buffer + size)
    {
        asm volatile("mcr p15, 0, %0, c7, c6, 1": :"r"(ptr));

        ptr += CACHE_LINE_SIZE;
    }
}

void icache_invalidate()
{
    asm volatile("mcr p15, 0, %0, c7, c5, 0": :"r"(0));
}
#endif

#ifdef __CC_ARM
rt_inline rt_uint32_t cp15_rd(void)
{
    rt_uint32_t i;

    __asm
    {
        mrc p15, 0, i, c1, c0, 0
    }

    return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
    rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, bit
        mcr p15, 0, value, c1, c0, 0
    }
}

rt_inline void cache_disable(rt_uint32_t bit)
{
    rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, bit
        mcr p15, 0, value, c1, c0, 0
    }
}

void dcache_clean(rt_uint32_t buffer, rt_uint32_t size)
{
    unsigned int ptr;

    ptr = buffer & ~(CACHE_LINE_SIZE - 1);

    while (ptr < buffer + size)
    {
        __asm volatile { mcr p15, 0, ptr, c7, c10, 1 }
        ptr += CACHE_LINE_SIZE;
    }
}

void dcache_invalidate(rt_uint32_t buffer, rt_uint32_t size)
{
    unsigned int ptr;

    ptr = buffer & ~(CACHE_LINE_SIZE - 1);

    while (ptr < buffer + size)
    {
        __asm volatile { mcr p15, 0, ptr, c7, c6, 1 }
        ptr += CACHE_LINE_SIZE;
    }
}

void icache_invalidate()
{
    register rt_uint32_t value;

    value = 0;

    __asm volatile { mcr p15, 0, value, c7, c5, 0 }
}

#endif

/**
 * enable I-Cache
 *
 */
void rt_hw_cpu_icache_enable()
{
    cache_enable(ICACHE_MASK);
}

/**
 * disable I-Cache
 *
 */
void rt_hw_cpu_icache_disable()
{
    cache_disable(ICACHE_MASK);
}

/**
 * return the status of I-Cache
 *
 */
rt_base_t rt_hw_cpu_icache_status()
{
    return (cp15_rd() & ICACHE_MASK);
}

/**
 * enable D-Cache
 *
 */
void rt_hw_cpu_dcache_enable()
{
    cache_enable(DCACHE_MASK);
}

/**
 * disable D-Cache
 *
 */
void rt_hw_cpu_dcache_disable()
{
    cache_disable(DCACHE_MASK);
}

/**
 * return the status of D-Cache
 *
 */
rt_base_t rt_hw_cpu_dcache_status()
{
    return (cp15_rd() & DCACHE_MASK);
}

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
        icache_invalidate(); /* TODO: only invalidate an addr range */
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
        dcache_clean(addr, size);
    else if (ops == RT_HW_CACHE_INVALIDATE)
        dcache_invalidate(addr, size);
}

/**
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{
    /* Disable all interrupt except the WDT */
    INTMSK = (~((rt_uint32_t)1 << INTWDT));

    /* Disable watchdog */
    WTCON = 0x0000;

    /* Initialize watchdog timer count register */
    WTCNT = 0x0001;

    /* Enable watchdog timer; assert reset at timer timeout */
    WTCON = 0x0021;

    while (1)
        ; /* loop forever and wait for reset to happen */

    /* NEVER REACHED */
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

/*@}*/
