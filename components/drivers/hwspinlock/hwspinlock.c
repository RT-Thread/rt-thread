/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <cpuport.h>

#define DBG_TAG "rtdm.hwspinlock"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "hwspinlock_dm.h"

static struct rt_spinlock hwspinlock_ops_lock = {};
static rt_list_t hwspinlock_bank_nodes = RT_LIST_OBJECT_INIT(hwspinlock_bank_nodes);

rt_err_t rt_hwspinlock_bank_register(struct rt_hwspinlock_bank *bank)
{
    struct rt_hwspinlock *hwlock;

    if (!bank || !bank->ops || bank->locks_nr <= 0 || !bank->dev)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&bank->list);
    rt_ref_init(&bank->ref);

    hwlock = &bank->locks[0];

    for (int i = 0; i < bank->locks_nr; ++i, ++hwlock)
    {
        rt_spin_lock_init(&hwlock->lock);
        hwlock->used = RT_FALSE;
    }

    rt_spin_lock(&hwspinlock_ops_lock);
    rt_list_insert_after(&hwspinlock_bank_nodes, &bank->list);
    rt_spin_unlock(&hwspinlock_ops_lock);

    rt_dm_dev_bind_fwdata(bank->dev, RT_NULL, bank);

    return RT_EOK;
}

rt_err_t rt_hwspinlock_bank_unregister(struct rt_hwspinlock_bank *bank)
{
    rt_err_t err;

    if (!bank)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&hwspinlock_ops_lock);

    if (rt_ref_read(&bank->ref) == 1)
    {
        rt_dm_dev_unbind_fwdata(bank->dev, RT_NULL);

        err = RT_EOK;
    }
    else
    {
        err = -RT_EBUSY;
    }

    rt_spin_unlock(&hwspinlock_ops_lock);

    return err;
}

rt_err_t rt_hwspin_trylock_raw(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level)
{
    rt_err_t err;

    if (rt_unlikely(!hwlock))
    {
        return -RT_EINVAL;
    }

    if (out_irq_level)
    {
        *out_irq_level = rt_spin_lock_irqsave(&hwlock->lock);
    }
    else
    {
        rt_spin_lock(&hwlock->lock);
    }

    err = hwlock->bank->ops->trylock(hwlock);

    if (rt_unlikely(err))
    {
        if (out_irq_level)
        {
            rt_spin_unlock_irqrestore(&hwlock->lock, *out_irq_level);
        }
        else
        {
            rt_spin_unlock(&hwlock->lock);
        }
    }

    rt_hw_dmb();

    return err;
}

rt_err_t rt_hwspin_lock_timeout_raw(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms, rt_ubase_t *out_irq_level)
{
    rt_err_t err;
    rt_tick_t timeout = rt_tick_get() + rt_tick_from_millisecond(timeout_ms);

    for (;;)
    {
        err = rt_hwspin_trylock_raw(hwlock, out_irq_level);

        if (err != -RT_EBUSY)
        {
            break;
        }

        if (timeout < rt_tick_get())
        {
            return -RT_ETIMEOUT;
        }

        if (hwlock->bank->ops->relax)
        {
            hwlock->bank->ops->relax(hwlock);
        }
    }

    return err;
}

void rt_hwspin_unlock_raw(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level)
{
    if (rt_unlikely(!hwlock))
    {
        return;
    }

    rt_hw_dmb();

    hwlock->bank->ops->unlock(hwlock);

    if (out_irq_level)
    {
        rt_spin_unlock_irqrestore(&hwlock->lock, *out_irq_level);
    }
    else
    {
        rt_spin_unlock(&hwlock->lock);
    }
}

static struct rt_hwspinlock *hwspinlock_get(struct rt_hwspinlock_bank *bank, int id)
{
    struct rt_hwspinlock *hwlock = RT_NULL;

    if (bank)
    {
        int offset = id - bank->base_id;

        if (!bank->locks[offset].used)
        {
            hwlock = &bank->locks[offset];
        }
    }
    else
    {
        rt_list_for_each_entry(bank, &hwspinlock_bank_nodes, list)
        {
            hwlock = rt_err_ptr(-RT_EBUSY);

            for (int i = 0; i < bank->locks_nr; ++i)
            {
                if (!bank->locks[i].used)
                {
                    hwlock = &bank->locks[i];
                    goto _found;
                }
            }
        }
    }

_found:
    if (!rt_is_err_or_null(hwlock))
    {
        hwlock->used = RT_TRUE;
    }

    return hwlock;
}

struct rt_hwspinlock *rt_hwspinlock_get(void)
{
    struct rt_hwspinlock *lock;

    rt_spin_lock(&hwspinlock_ops_lock);

    lock = hwspinlock_get(RT_NULL, -1);

    rt_spin_unlock(&hwspinlock_ops_lock);

    return lock;
}

struct rt_hwspinlock *rt_hwspinlock_get_by_index(struct rt_device *dev, int index)
{
    return rt_ofw_get_hwspinlock_by_index(dev->ofw_node, index);
}

struct rt_hwspinlock *rt_hwspinlock_get_by_name(struct rt_device *dev, const char *name)
{
    return rt_ofw_get_hwspinlock_by_name(dev->ofw_node, name);
}

static void hwspinlock_release(struct ref *r)
{
    struct rt_hwspinlock_bank *bank = rt_container_of(r, struct rt_hwspinlock_bank, ref);

    LOG_E("%s is release", rt_dm_dev_get_name(bank->dev));
    (void)bank;

    RT_ASSERT(0);
}

void rt_hwspinlock_put(struct rt_hwspinlock *hwlock)
{
    if (hwlock)
    {
        rt_ref_put(&hwlock->bank->ref, &hwspinlock_release);
        hwlock->used = RT_TRUE;
    }
}

struct rt_hwspinlock *rt_ofw_get_hwspinlock_by_index(struct rt_ofw_node *np, int index)
{
    rt_err_t err;
    struct rt_ofw_node *bank_np;
    struct rt_ofw_cell_args args;
    struct rt_hwspinlock *lock;
    struct rt_hwspinlock_bank *bank;

    if (!np && index < 0)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    err = rt_ofw_parse_phandle_cells(np, "hwlocks", "#hwlock-cells", index, &args);

    if (err)
    {
        return rt_err_ptr(err);
    }

    bank_np = args.data;

    if (!rt_ofw_data(bank_np))
    {
        rt_platform_ofw_request(bank_np);
    }

    rt_spin_lock(&hwspinlock_ops_lock);

    bank = rt_ofw_data(bank_np);
    rt_ofw_node_put(bank_np);

    if (!bank || args.args_count != 1)
    {
        lock = rt_err_ptr(-RT_ENOSYS);
    }
    else
    {
        lock = hwspinlock_get(bank, bank->base_id + args.args[0]);
    }

    rt_spin_unlock(&hwspinlock_ops_lock);

    return lock;
}

struct rt_hwspinlock *rt_ofw_get_hwspinlock_by_name(struct rt_ofw_node *np, const char *name)
{
    int index;

    if (!np || !name)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    index = rt_ofw_prop_index_of_string(np, "hwlock-names", name);

    if (index < 0)
    {
        return rt_err_ptr(index);
    }

    return rt_ofw_get_hwspinlock_by_index(np, index);
}
