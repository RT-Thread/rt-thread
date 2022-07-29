/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-27     flybreak       the first version
 */

#include <rtthread.h>
#include <rthw.h>

#define atomic_compare_exchange_strong(obj, exp, val) \
    __atomic_compare_exchange_n(obj, exp, val, 0, \
        __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define atomic_compare_exchange_weak(obj, exp, val) \
    __atomic_compare_exchange_n(obj, exp, val, 1, \
        __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define atomic_fetch_add(obj, arg) \
    __atomic_fetch_add(obj, arg, __ATOMIC_SEQ_CST)

#define atomic_fetch_sub(obj, arg) \
    __atomic_fetch_sub(obj, arg, __ATOMIC_SEQ_CST)

#define atomic_fetch_or(obj, arg) \
    __atomic_fetch_or(obj, arg, __ATOMIC_SEQ_CST)

#define atomic_fetch_xor(obj, arg) \
    __atomic_fetch_xor(obj, arg, __ATOMIC_SEQ_CST)

#define atomic_fetch_and(obj, arg) \
    __atomic_fetch_and(obj, arg, __ATOMIC_SEQ_CST)

#define atomic_fetch_nand(obj, arg) \
    __atomic_fetch_nand(obj, arg, __ATOMIC_SEQ_CST)

rt_atomic_t rt_atomic_cas(rt_atomic_t *ptr, rt_atomic_t oldval, rt_atomic_t newval)
{
    atomic_compare_exchange_strong(ptr, &oldval, newval);
    return oldval;
}

void rt_atomic_add(rt_atomic_t *ptr, rt_atomic_t val)
{
    atomic_fetch_add(ptr, val);
}

void rt_atomic_sub(rt_atomic_t *ptr, rt_atomic_t val)
{
    atomic_fetch_sub(ptr, val);
}

void rt_atomic_or(rt_atomic_t *ptr, rt_atomic_t val)
{
    atomic_fetch_or(ptr, val);
}

void rt_atomic_xor(rt_atomic_t *ptr, rt_atomic_t val)
{
    atomic_fetch_xor(ptr, val);
}

void rt_atomic_and(rt_atomic_t *ptr, rt_atomic_t val)
{
    atomic_fetch_and(ptr, val);
}

void rt_atomic_nand(rt_atomic_t *ptr, rt_atomic_t val)
{
    atomic_fetch_nand(ptr, val);
}
