/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __HWSPINLOCK_DM_H__
#define __HWSPINLOCK_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/misc.h>
#include <ref.h>

struct rt_hwspinlock
{
    struct rt_hwspinlock_bank *bank;
    struct rt_spinlock lock;

    rt_bool_t used;
    void *priv;
};

struct rt_hwspinlock_ops
{
    rt_err_t (*trylock)(struct rt_hwspinlock *hwlock);
    void (*unlock)(struct rt_hwspinlock *hwlock);
    void (*relax)(struct rt_hwspinlock *hwlock);
};

struct rt_hwspinlock_bank
{
    rt_list_t list;
    struct rt_ref ref;

    struct rt_device *dev;
    const struct rt_hwspinlock_ops *ops;

    int base_id;
    rt_size_t locks_nr;
    struct rt_hwspinlock locks[];
};

#define hwspinlock_bank_alloc(obj, locks_nr) \
    rt_calloc(1, sizeof(typeof(*obj)) + sizeof(struct rt_hwspinlock) * (locks_nr))

rt_inline int hwspinlock_find_id(struct rt_hwspinlock *hwlock)
{
    return hwlock->bank->base_id + (hwlock - &hwlock->bank->locks[0]);
}

#endif /* __HWSPINLOCK_DM_H__ */
