/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-14     WangShun     first version
 */
#ifndef RT_ATOMIC_SOFT_H__
#define RT_ATOMIC_SOFT_H__

#include <rthw.h>
#include <rtthread.h>
extern rt_base_t rt_hw_interrupt_disable(void);
extern void rt_hw_interrupt_enable(rt_base_t level);

__attribute__((always_inline)) static inline  rt_atomic_t rt_isr_atomic_exchange(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline  rt_atomic_t rt_isr_atomic_add(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr += val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_sub(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr -= val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_xor(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr  = (*ptr)^val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_and(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr  = (*ptr)&val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_or(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr  = (*ptr)|val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_load(volatile rt_atomic_t *ptr)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline void rt_isr_atomic_store(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    *ptr = val;
    rt_hw_interrupt_enable(level);
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_flag_test_and_set(volatile rt_atomic_t *ptr)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    if(*ptr==0){
        temp =0;
        *ptr =1;
    }else
        temp =1;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline void rt_isr_atomic_flag_clear(volatile rt_atomic_t *ptr)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    *ptr = 0;
    rt_hw_interrupt_enable(level);
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_compare_exchange_strong(volatile rt_atomic_t *ptr1, rt_atomic_t *ptr2, rt_atomic_t desired)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    if((*ptr1)!=(*ptr2)){
        *ptr2 = *ptr1;
        temp = 0;
    }
    else{
        *ptr1=desired;
        temp = *ptr1;
    }
    rt_hw_interrupt_enable(level);
    return temp;
}
#endif
