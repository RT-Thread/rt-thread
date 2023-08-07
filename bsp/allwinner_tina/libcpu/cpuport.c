/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rthw.h>
#include <rtthread.h>

#define ICACHE_MASK    (rt_uint32_t)(1 << 12)
#define DCACHE_MASK    (rt_uint32_t)(1 << 2)

extern void machine_reset(void);
extern void machine_shutdown(void);

#if defined(__GNUC__) || defined(__ICCARM__)
rt_inline rt_uint32_t cp15_rd(void)
{
    rt_uint32_t i;

    __asm volatile("mrc p15, 0, %0, c1, c0, 0":"=r"(i));
    return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
    __asm volatile(\
                   "mrc  p15,0,r0,c1,c0,0\n\t"    \
                   "orr  r0,r0,%0\n\t"            \
                   "mcr  p15,0,r0,c1,c0,0"        \
                   :                              \
                   : "r"(bit)                     \
                   : "memory");
}

rt_inline void cache_disable(rt_uint32_t bit)
{
    __asm volatile(\
                   "mrc  p15,0,r0,c1,c0,0\n\t"    \
                   "bic  r0,r0,%0\n\t"            \
                   "mcr  p15,0,r0,c1,c0,0"        \
                   :                              \
                   : "r"(bit)                     \
                   : "memory");
}
#endif

#if defined(__CC_ARM)
rt_inline rt_uint32_t cp15_rd(void)
{
    rt_uint32_t i;

    __asm volatile
    {
        mrc p15, 0, i, c1, c0, 0
    }

    return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
    rt_uint32_t value;

    __asm volatile
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, bit
        mcr p15, 0, value, c1, c0, 0
    }
}

rt_inline void cache_disable(rt_uint32_t bit)
{
    rt_uint32_t value;

    __asm volatile
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, bit
        mcr p15, 0, value, c1, c0, 0
    }
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
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{

    rt_kprintf("Restarting system...\n");
    machine_reset();

    while (1);   /* loop forever and wait for reset to happen */

    /* NEVER REACHED */
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown(void)
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    machine_shutdown();
    while (level)
    {
        RT_ASSERT(0);
    }
}

#ifdef RT_USING_CPU_FFS
/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
#if defined(__CC_ARM)
int __rt_ffs(int value)
{
    register rt_uint32_t x;

    if (value == 0)
        return value;

    __asm
    {
        rsb x, value, #0
        and x, x, value
        clz x, x
        rsb x, x, #32
    }

    return x;
}
#elif defined(__GNUC__) || defined(__ICCARM__)
int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}
#endif

#endif


/*@}*/
