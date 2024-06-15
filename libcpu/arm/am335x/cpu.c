/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 * 2022-09-20     YangZhongQing
 *                             add IAR assembler
 */

#include <rthw.h>
#include <rtthread.h>
#include "am33xx.h"

/**
 * @addtogroup AM33xx
 */
/*@{*/

#define ICACHE_MASK (rt_uint32_t)(1 << 12)
#define DCACHE_MASK (rt_uint32_t)(1 << 2)

#if defined(__CC_ARM)
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
#elif defined(__GNUC__)
rt_inline rt_uint32_t cp15_rd(void)
{
    rt_uint32_t i;

    asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
    return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
    __asm__ __volatile__(           \
        "mrc  p15,0,r0,c1,c0,0\n\t" \
        "orr  r0,r0,%0\n\t"         \
        "mcr  p15,0,r0,c1,c0,0"     \
        :                           \
        :"r" (bit)                  \
        :"memory");
}

rt_inline void cache_disable(rt_uint32_t bit)
{
    __asm__ __volatile__(           \
        "mrc  p15,0,r0,c1,c0,0\n\t" \
        "bic  r0,r0,%0\n\t"         \
        "mcr  p15,0,r0,c1,c0,0"     \
        :                           \
        :"r" (bit)                  \
        :"memory");
}
#elif defined(__ICCARM__)
rt_inline rt_uint32_t cp15_rd(void)
{
    rt_uint32_t i;

    __asm volatile("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
    return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
    rt_uint32_t tmp;

    __asm volatile(                 \
        "mrc  p15,0,%0,c1,c0,0\n\t" \
        "orr  %0,%0,%1\n\t"         \
        "mcr  p15,0,%0,c1,c0,0"     \
        :"+r"(tmp)                  \
        :"r"(bit)                   \
        :"memory");
}

rt_inline void cache_disable(rt_uint32_t bit)
{
    rt_uint32_t tmp;

    __asm volatile(                 \
        "mrc  p15,0,%0,c1,c0,0\n\t" \
        "bic  %0,%0,%1\n\t"         \
        "mcr  p15,0,%0,c1,c0,0"     \
        :"+r"(tmp)                  \
        :"r"(bit)                   \
        :"memory");
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

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown(void)
{
    rt_base_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

/*@}*/
