/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-14     WangShun     first version
 */

#include <rtthread.h>

#include <asm-generic.h>

rt_atomic_t rt_hw_atomic_exchange(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoswap." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");

    return result;
}

rt_atomic_t rt_hw_atomic_add(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoadd." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");

    return result;
}

rt_atomic_t rt_hw_atomic_sub(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    val = -val;
    __asm__ volatile ("amoadd." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");

    return result;
}

rt_atomic_t rt_hw_atomic_xor(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoxor." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");

    return result;
}

rt_atomic_t rt_hw_atomic_and(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoand." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");

    return result;
}

rt_atomic_t rt_hw_atomic_or(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoor." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");

    return result;
}

rt_atomic_t rt_hw_atomic_load(volatile rt_atomic_t *ptr)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoxor." REG_WIDTH " %0, x0, (%1)" : "=r"(result) : "r"(ptr) : "memory");

    return result;
}

void rt_hw_atomic_store(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoswap." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
}

rt_atomic_t rt_hw_atomic_flag_test_and_set(volatile rt_atomic_t *ptr)
{
    rt_atomic_t result = 0, temp = 1;

    __asm__ volatile ("amoor." REG_WIDTH " %0, %1, (%2)" : "=r"(result) : "r"(temp), "r"(ptr) : "memory");

    return result;
}

void rt_hw_atomic_flag_clear(volatile rt_atomic_t *ptr)
{
    rt_atomic_t result = 0;

    __asm__ volatile ("amoand." REG_WIDTH " %0, x0, (%1)" : "=r"(result) :"r"(ptr) : "memory");
}

rt_atomic_t rt_hw_atomic_compare_exchange_strong(volatile rt_atomic_t *ptr, rt_atomic_t *old, rt_atomic_t desired)
{
    rt_atomic_t tmp = *old, result = 0;

    __asm__ volatile (
            " fence iorw, ow\n"
            "1: lr." REG_WIDTH ".aq  %[result], (%[ptr])\n"
            "   bne      %[result], %[tmp], 2f\n"
            "   sc." REG_WIDTH ".rl  %[tmp], %[desired], (%[ptr])\n"
            "   bnez     %[tmp], 1b\n"
            "   li  %[result], 1\n"
            "   j 3f\n"
            " 2:" REG_S "  %[result], (%[old])\n"
            "   li  %[result], 0\n"
            " 3:\n"
            : [result]"+r" (result), [tmp]"+r" (tmp), [ptr]"+r" (ptr)
            : [desired]"r" (desired), [old]"r"(old)
            : "memory");

    return result;
}
