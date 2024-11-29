/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __HWSPINLOCK_H__
#define __HWSPINLOCK_H__

#include <rtdef.h>

struct rt_hwspinlock;
struct rt_hwspinlock_ops;
struct rt_hwspinlock_bank;

rt_err_t rt_hwspinlock_bank_register(struct rt_hwspinlock_bank *bank);
rt_err_t rt_hwspinlock_bank_unregister(struct rt_hwspinlock_bank *bank);

rt_err_t rt_hwspin_trylock_raw(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level);
rt_err_t rt_hwspin_lock_timeout_raw(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms, rt_ubase_t *out_irq_level);
void rt_hwspin_unlock_raw(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level);

rt_inline rt_err_t rt_hwspin_trylock(struct rt_hwspinlock *hwlock)
{
    return rt_hwspin_trylock_raw(hwlock, RT_NULL);
}

rt_inline rt_err_t rt_hwspin_trylock_irqsave(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level)
{
    return rt_hwspin_trylock_raw(hwlock, out_irq_level);
}

rt_inline rt_err_t rt_hwspin_lock_timeout(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms)
{
    return rt_hwspin_lock_timeout_raw(hwlock, timeout_ms, RT_NULL);
}

rt_inline rt_err_t rt_hwspin_lock_timeout_irqsave(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms, rt_ubase_t *out_level)
{
    return rt_hwspin_lock_timeout_raw(hwlock, timeout_ms, out_level);
}

rt_inline void rt_hwspin_unlock(struct rt_hwspinlock *hwlock)
{
    rt_hwspin_unlock_raw(hwlock, RT_NULL);
}

rt_inline void rt_hwspin_unlock_irqsave(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_level)
{
    rt_hwspin_unlock_raw(hwlock, out_level);
}

struct rt_hwspinlock *rt_hwspinlock_get(void);
struct rt_hwspinlock *rt_hwspinlock_get_by_index(struct rt_device *dev, int index);
struct rt_hwspinlock *rt_hwspinlock_get_by_name(struct rt_device *dev, const char *name);
void rt_hwspinlock_put(struct rt_hwspinlock *hwlock);

struct rt_hwspinlock *rt_ofw_get_hwspinlock_by_index(struct rt_ofw_node *np, int index);
struct rt_hwspinlock *rt_ofw_get_hwspinlock_by_name(struct rt_ofw_node *np, const char *name);

#endif /* __HWSPINLOCK_H__ */
