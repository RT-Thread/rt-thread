/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     peterfan     Add copyright header.
 */

#include <rthw.h>
#include <stdint.h>
#include <stdbool.h>

/*
* override gcc builtin atomic function for std::atomic<int64_t>, std::atomic<uint64_t>
* @see https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
*/
uint64_t __atomic_load_8(volatile void *ptr, int memorder)
{
    volatile uint64_t *val_ptr = (volatile uint64_t *)ptr;
    rt_base_t level;
    uint64_t tmp;
    level = rt_hw_interrupt_disable();
    tmp = *val_ptr;
    rt_hw_interrupt_enable(level);
    return tmp;
}

void __atomic_store_8(volatile void *ptr, uint64_t val, int memorder)
{
    volatile uint64_t *val_ptr = (volatile uint64_t *)ptr;
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    *val_ptr = val;
    rt_hw_interrupt_enable(level);
}

uint64_t __atomic_exchange_8(volatile void *ptr, uint64_t val, int memorder)
{
    volatile uint64_t *val_ptr = (volatile uint64_t *)ptr;
    rt_base_t level;
    uint64_t tmp;
    level = rt_hw_interrupt_disable();
    tmp = *val_ptr;
    *val_ptr = val;
    rt_hw_interrupt_enable(level);
    return tmp;
}

bool __atomic_compare_exchange_8(volatile void *ptr, volatile void *expected, uint64_t desired, bool weak, int success_memorder, int failure_memorder)
{
    volatile uint64_t *val_ptr = (volatile uint64_t *)ptr;
    volatile uint64_t *expected_ptr = (volatile uint64_t *)expected;
    rt_base_t level;
    bool exchanged;
    level = rt_hw_interrupt_disable();
    if (*val_ptr == *expected_ptr)
    {
        *val_ptr = desired;
        exchanged = true;
    }
    else
    {
        *expected_ptr = *val_ptr;
        exchanged = false;
    }
    rt_hw_interrupt_enable(level);
    return exchanged;
}

#define __atomic_fetch_op_8(OPNAME, OP) \
uint64_t __atomic_fetch_##OPNAME##_8(volatile void *ptr, uint64_t val, int memorder) {\
    volatile uint64_t* val_ptr = (volatile uint64_t*)ptr;\
    rt_base_t level;\
    uint64_t tmp;\
    level = rt_hw_interrupt_disable();\
    tmp = *val_ptr;\
    *val_ptr OP##= val;\
    rt_hw_interrupt_enable(level);\
    return tmp;\
}

__atomic_fetch_op_8(add, +)
__atomic_fetch_op_8(sub, -)
__atomic_fetch_op_8( and, &)
__atomic_fetch_op_8( or, |)
__atomic_fetch_op_8(xor, ^)
