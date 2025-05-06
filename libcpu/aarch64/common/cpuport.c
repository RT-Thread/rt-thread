/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-21     Zhangyan     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

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
int __rt_ffs(int value)
{
#ifdef __GNUC__
    return __builtin_ffs(value);
#else
    __asm__ volatile (
        "rbit w1, %w0\n"
        "cmp %w0, 0\n"
        "clz w1, w1\n"
        "csinc %w0, wzr, w1, eq\n"
        : "=r"(value)
        : "0"(value)
    );
    return value;
#endif
}

unsigned long __rt_ffsl(unsigned long value)
{
#ifdef __GNUC__
    return __builtin_ffsl(value);
#else
    if (!value)
    {
        return 0;
    }

    __asm__ volatile ("rbit %0, %0" : "+r" (value));

    return __rt_clz(value);
#endif
}

unsigned long __rt_clz(unsigned long value)
{
#ifdef __GNUC__
    return __builtin_clz(value);
#else
    unsigned long val;

    __asm__ volatile ("clz %0, %1"
        :"=r"(val)
        :"r"(value));

    return val;
#endif
}

#endif /* RT_USING_CPU_FFS */
