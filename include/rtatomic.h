/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-14     WangShun     first version
 */
#ifndef RT_ATOMIC_ISRs_H__
#define RT_ATOMIC_ISRs_H__

#include <rthw.h>
#include <rtthread.h>
extern rt_base_t rt_hw_interrupt_disable(void);
extern void rt_hw_interrupt_enable(rt_base_t level);

__attribute__((always_inline)) static inline  rt_atomic_t rt_isr_atomic_exchange(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr = val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline  rt_atomic_t rt_isr_atomic_add(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr += val;
    rt_hw_interrupt_enable(level);
    return temp;    
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_sub(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr -= val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_xor(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr  = (*ptr)^val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_and(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr  = (*ptr)&val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_or(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr  = (*ptr)|val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_load(rt_atomic_t *ptr)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_store(rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_atomic_t temp = *ptr;
    *ptr = val;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_flag_test_and_set(rt_atomic_t *ptr)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    if(*ptr==0)
    {
        temp =0;
        *ptr =1;
    }else
       temp =1;
    rt_hw_interrupt_enable(level);
    return temp;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_flag_clear(rt_atomic_t *ptr)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    *ptr = 0;
    rt_hw_interrupt_enable(level);
    return 0;
}

__attribute__((always_inline)) static inline rt_atomic_t rt_isr_atomic_compare_exchange_strong(rt_atomic_t *ptr1, rt_atomic_t *ptr2, rt_atomic_t desired)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    if((*ptr1)!=(*ptr2))
        temp = 0;
    else
    {
        *ptr1=desired;
        temp = 1;
    }
    rt_hw_interrupt_enable(level);
    return temp;
}
#endif
