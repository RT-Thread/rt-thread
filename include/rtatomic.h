/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-14     WangShun     first version
 * 2023-05-20     Bernard      add stdc atomic detection.
 */
#ifndef __RT_ATOMIC_H__
#define __RT_ATOMIC_H__

#include <rthw.h>

#if !defined(__cplusplus)

rt_atomic_t rt_hw_atomic_load(volatile rt_atomic_t *ptr);
void rt_hw_atomic_store(volatile rt_atomic_t *ptr, rt_atomic_t val);
rt_atomic_t rt_hw_atomic_add(volatile rt_atomic_t *ptr, rt_atomic_t val);
rt_atomic_t rt_hw_atomic_sub(volatile rt_atomic_t *ptr, rt_atomic_t val);
rt_atomic_t rt_hw_atomic_and(volatile rt_atomic_t *ptr, rt_atomic_t val);
rt_atomic_t rt_hw_atomic_or(volatile rt_atomic_t *ptr, rt_atomic_t val);
rt_atomic_t rt_hw_atomic_xor(volatile rt_atomic_t *ptr, rt_atomic_t val);
rt_atomic_t rt_hw_atomic_exchange(volatile rt_atomic_t *ptr, rt_atomic_t val);
void rt_hw_atomic_flag_clear(volatile rt_atomic_t *ptr);
rt_atomic_t rt_hw_atomic_flag_test_and_set(volatile rt_atomic_t *ptr);
rt_atomic_t rt_hw_atomic_compare_exchange_strong(volatile rt_atomic_t *ptr, rt_atomic_t *expected, rt_atomic_t desired);

/* To detect stdatomic */
#if !defined(RT_USING_HW_ATOMIC) && !defined(RT_USING_STDC_ATOMIC)
#if defined(__GNUC__) && defined(RT_USING_LIBC) && !defined(__STDC_NO_ATOMICS__)
#define RT_USING_STDC_ATOMIC
#endif /* __GNUC__ && .. */
#endif /* !RT_USING_HW_ATOMIC && !RT_USING_STDC_ATOMIC */

#if defined(RT_USING_HW_ATOMIC)
#define rt_atomic_load(ptr) rt_hw_atomic_load(ptr)
#define rt_atomic_store(ptr, v) rt_hw_atomic_store(ptr, v)
#define rt_atomic_add(ptr, v) rt_hw_atomic_add(ptr, v)
#define rt_atomic_sub(ptr, v) rt_hw_atomic_sub(ptr, v)
#define rt_atomic_and(ptr, v) rt_hw_atomic_and(ptr, v)
#define rt_atomic_or(ptr, v)  rt_hw_atomic_or(ptr, v)
#define rt_atomic_xor(ptr, v) rt_hw_atomic_xor(ptr, v)
#define rt_atomic_exchange(ptr, v) rt_hw_atomic_exchange(ptr, v)
#define rt_atomic_flag_clear(ptr) rt_hw_atomic_flag_clear(ptr)
#define rt_atomic_flag_test_and_set(ptr) rt_hw_atomic_flag_test_and_set(ptr)
#define rt_atomic_compare_exchange_strong(ptr, v,des) rt_hw_atomic_compare_exchange_strong(ptr, v ,des)

#elif defined(RT_USING_STDC_ATOMIC)

#ifndef __STDC_NO_ATOMICS__
#define rt_atomic_load(ptr) atomic_load(ptr)
#define rt_atomic_store(ptr, v) atomic_store(ptr, v)
#define rt_atomic_add(ptr, v) atomic_fetch_add(ptr, v)
#define rt_atomic_sub(ptr, v) atomic_fetch_sub(ptr, v)
#define rt_atomic_and(ptr, v) atomic_fetch_and(ptr, v)
#define rt_atomic_or(ptr, v)  atomic_fetch_or(ptr, v)
#define rt_atomic_xor(ptr, v) atomic_fetch_xor(ptr, v)
#define rt_atomic_exchange(ptr, v) atomic_exchange(ptr, v)
#define rt_atomic_flag_clear(ptr) atomic_flag_clear(ptr)
#define rt_atomic_flag_test_and_set(ptr) atomic_flag_test_and_set(ptr)
#define rt_atomic_compare_exchange_strong(ptr, v,des) atomic_compare_exchange_strong(ptr, v ,des)
#else
#error "The standard library C doesn't support the atomic operation"
#endif /* __STDC_NO_ATOMICS__ */

#else
#include <rthw.h>
#define rt_atomic_load(ptr) rt_soft_atomic_load(ptr)
#define rt_atomic_store(ptr, v) rt_soft_atomic_store(ptr, v)
#define rt_atomic_add(ptr, v) rt_soft_atomic_add(ptr, v)
#define rt_atomic_sub(ptr, v) rt_soft_atomic_sub(ptr, v)
#define rt_atomic_and(ptr, v) rt_soft_atomic_and(ptr, v)
#define rt_atomic_or(ptr, v)  rt_soft_atomic_or(ptr, v)
#define rt_atomic_xor(ptr, v) rt_soft_atomic_xor(ptr, v)
#define rt_atomic_exchange(ptr, v) rt_soft_atomic_exchange(ptr, v)
#define rt_atomic_flag_clear(ptr) rt_soft_atomic_flag_clear(ptr)
#define rt_atomic_flag_test_and_set(ptr) rt_soft_atomic_flag_test_and_set(ptr)
#define rt_atomic_compare_exchange_strong(ptr, v,des) rt_soft_atomic_compare_exchange_strong(ptr, v ,des)

rt_inline rt_atomic_t rt_soft_atomic_exchange(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = val;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline rt_atomic_t rt_soft_atomic_add(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr += val;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline rt_atomic_t rt_soft_atomic_sub(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr -= val;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline rt_atomic_t rt_soft_atomic_xor(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = (*ptr) ^ val;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline rt_atomic_t rt_soft_atomic_and(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = (*ptr) & val;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline rt_atomic_t rt_soft_atomic_or(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = (*ptr) | val;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline rt_atomic_t rt_soft_atomic_load(volatile rt_atomic_t *ptr)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    temp = *ptr;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline void rt_soft_atomic_store(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    *ptr = val;
    rt_hw_interrupt_enable(level);
}

rt_inline rt_atomic_t rt_soft_atomic_flag_test_and_set(volatile rt_atomic_t *ptr)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    if (*ptr == 0)
    {
        temp = 0;
        *ptr = 1;
    }
    else
        temp = 1;
    rt_hw_interrupt_enable(level);
    return temp;
}

rt_inline void rt_soft_atomic_flag_clear(volatile rt_atomic_t *ptr)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    *ptr = 0;
    rt_hw_interrupt_enable(level);
}

rt_inline rt_atomic_t rt_soft_atomic_compare_exchange_strong(volatile rt_atomic_t *ptr1, rt_atomic_t *ptr2,
        rt_atomic_t desired)
{
    rt_base_t level;
    rt_atomic_t temp;
    level = rt_hw_interrupt_disable();
    if ((*ptr1) != (*ptr2))
    {
        *ptr2 = *ptr1;
        temp = 0;
    }
    else
    {
        *ptr1 = desired;
        temp = 1;
    }
    rt_hw_interrupt_enable(level);
    return temp;
}
#endif /* RT_USING_STDC_ATOMIC */

rt_inline rt_bool_t rt_atomic_dec_and_test(volatile rt_atomic_t *ptr)
{
    return rt_atomic_sub(ptr, 1) == 0;
}

rt_inline rt_atomic_t rt_atomic_fetch_add_unless(volatile rt_atomic_t *ptr, rt_atomic_t a, rt_atomic_t u)
{
    rt_atomic_t c = rt_atomic_load(ptr);

    do {
        if (c == u)
        {
            break;
        }
    } while (!rt_atomic_compare_exchange_strong(ptr, &c, c + a));

    return c;
}

rt_inline rt_bool_t rt_atomic_add_unless(volatile rt_atomic_t *ptr, rt_atomic_t a, rt_atomic_t u)
{
    return rt_atomic_fetch_add_unless(ptr, a, u) != u;
}

rt_inline rt_bool_t rt_atomic_inc_not_zero(volatile rt_atomic_t *ptr)
{
    return rt_atomic_add_unless(ptr, 1, 0);
}

#endif /* __cplusplus */

#endif /* __RT_ATOMIC_H__ */
