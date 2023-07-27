/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-18     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtatomic.h>

rt_atomic_t rt_hw_atomic_load(volatile rt_atomic_t *ptr)
{
    rt_atomic_t ret;

    __asm__ volatile (
        "   ldr     %0, %1\n"
        "   dmb     ish"
        : "=r" (ret)
        : "Q" (*ptr)
        : "memory");

    return ret;
}

void rt_hw_atomic_store(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    __asm__ volatile (
        "   str     %1, %0\n"
        "   dmb     ish"
        : "=Q" (*ptr)
        : "r" (val)
        : "memory");
}

#define AARCH64_ATOMIC_OP_RETURN(op, ins, constraint)               \
rt_atomic_t rt_hw_atomic_##op(volatile rt_atomic_t *ptr, rt_atomic_t in_val)    \
{                                                                   \
    rt_atomic_t tmp, val, result;                                   \
                                                                    \
    __asm__ volatile (                                              \
        "   prfm    pstl1strm, %3\n"                                \
        "1: ldxr    %0, %3\n"                                       \
        "   "#ins " %1, %0, %4\n"                                   \
        "   stlxr   %w2, %1, %3\n"                                  \
        "   cbnz    %w2, 1b\n"                                      \
        "   dmb     ish"                                            \
        : "=&r" (result), "=&r" (val), "=&r" (tmp), "+Q" (*ptr)     \
        : __RT_STRINGIFY(constraint) "r" (in_val)                   \
        : "memory");                                                \
                                                                    \
    return result;                                                  \
}

AARCH64_ATOMIC_OP_RETURN(add, add, I)
AARCH64_ATOMIC_OP_RETURN(sub, sub, J)
AARCH64_ATOMIC_OP_RETURN(and, and, K)
AARCH64_ATOMIC_OP_RETURN(or, orr, K)
AARCH64_ATOMIC_OP_RETURN(xor, eor, K)

rt_atomic_t rt_hw_atomic_exchange(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t ret, tmp;

    __asm__ volatile (
        "   prfm    pstl1strm, %2\n"
        "1: ldxr    %0, %2\n"
        "   stlxr   %w1, %3, %2\n"
        "   cbnz    %w1, 1b\n"
        "   dmb     ish"
        : "=&r" (ret), "=&r" (tmp), "+Q" (*ptr)
        : "r" (val)
        : "memory");

    return ret;
}

void rt_hw_atomic_flag_clear(volatile rt_atomic_t *ptr)
{
    rt_hw_atomic_and(ptr, 0);
}

rt_atomic_t rt_hw_atomic_flag_test_and_set(volatile rt_atomic_t *ptr)
{
    return rt_hw_atomic_or(ptr, 1);
}

rt_atomic_t rt_hw_atomic_compare_exchange_strong(volatile rt_atomic_t *ptr, rt_atomic_t *old, rt_atomic_t new)
{
    rt_atomic_t tmp, oldval;

    __asm__ volatile (
        "   prfm    pstl1strm, %2\n"
        "1: ldxr    %0, %2\n"
        "   eor     %1, %0, %3\n"
        "   cbnz    %1, 2f\n"
        "   stlxr   %w1, %4, %2\n"
        "   cbnz    %w1, 1b\n"
        "   dmb     ish\n"
        "2:"
        : "=&r" (oldval), "=&r" (tmp), "+Q" (*ptr)
        : "Kr" (*old), "r" (new)
        : "memory");

    return oldval == *old;
}
