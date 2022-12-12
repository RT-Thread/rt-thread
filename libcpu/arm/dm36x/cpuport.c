/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#include <rthw.h>
#include <rtthread.h>

#define ICACHE_MASK (rt_uint32_t)(1 << 12)
#define DCACHE_MASK (rt_uint32_t)(1 << 2)

extern void machine_reset(void);
extern void machine_shutdown(void);

#ifdef __GNUC__
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
rt_weak void rt_hw_cpu_reset()
{

    rt_kprintf("Restarting system...\n");
    machine_reset();

    while(1);   /* loop forever and wait for reset to happen */

    /* NEVER REACHED */
}

/**
 *  shutdown CPU
 *
 */
rt_weak void rt_hw_cpu_shutdown()
{
    rt_base_t level;
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
#elif defined(__IAR_SYSTEMS_ICC__)
int __rt_ffs(int value)
{
    if (value == 0)
        return value;

    __ASM("RSB  r4, r0, #0");
    __ASM("AND  r4, r4, r0");
    __ASM("CLZ  r4, r4");
    __ASM("RSB  r0, r4, #32");
}
#elif defined(__GNUC__)
int __rt_ffs(int value)
{
    if (value == 0)
        return value;

    value &= (-value);
    asm ("clz %0, %1": "=r"(value) :"r"(value));

    return (32 - value);
}
#endif

#endif


/*@}*/
