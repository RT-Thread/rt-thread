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
#include <rtthread.h>

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

/**
 * @param   size is the length of the value to load.
 *
 * @param   mem is the source memory to load the value from.
 *
 * @param   _return is the pointer to the space where the loaded value will be stored.
 */
void __atomic_load(size_t size, void *mem, void *_return, int model)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_memcpy(_return, mem, size);
    rt_hw_interrupt_enable(level);
}

/**
 * @param   size is the length of the value to store.
 *
 * @param   mem is the destination memory space to store the value.
 *
 * @param   val is the pointer to the value to store.
 */
void __atomic_store(size_t size, void *mem, void *val, int model)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_memcpy(mem, val, size);
    rt_hw_interrupt_enable(level);
}

/**
 * @param   size is the length of value to exchange.
 *
 * @param   mem is the destination space to exchange.
 *
 * @param   val is the pointer of value to exchange.
 *
 * @param   _return gives back the the value before exchanging.
 */
void __atomic_exchange(size_t size, void *mem, void *val, void *_return, int model)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_memcpy(_return, mem, size);
    rt_memcpy(mem, val, size);
    rt_hw_interrupt_enable(level);
}

/**
 * @param   size is the length of value to operate.
 *
 * @param   obj is the destination value space to operate.
 *
 * @param   expected is the value to be compared with obj.
 *
 * @param   desired is the value pointer to be written into obj, under the condition that *expected equals *obj.
 *
 * @return  true if succeed in writing *desired into *obj; false if not.
*/
bool __atomic_compare_exchange(size_t size, void *obj, void *expected, void *desired, int success, int failure)
{
    rt_base_t level;
    volatile bool exchanged = false;
    level = rt_hw_interrupt_disable();
    if (rt_memcmp(obj, expected, size) == 0)
    {
        rt_memcpy(obj, desired, size);
        exchanged = true;
    }
    else
    {
        rt_memcpy(expected, obj, size);
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
