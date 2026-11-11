/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.governor"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static RT_DEFINE_SPINLOCK(dvfs_governor_nodes_lock);
static rt_list_t dvfs_governor_nodes = RT_LIST_OBJECT_INIT(dvfs_governor_nodes);

static struct rt_dvfs_governor *dvfs_governor_find(rt_uint32_t governor, const char *name)
{
    struct rt_dvfs_governor *gov;

    rt_list_for_each_entry(gov, &dvfs_governor_nodes, list)
    {
        if (governor != RT_UINT32_MAX && gov->type == governor)
        {
            return gov;
        }
        else if (name && !rt_strncmp(name, gov->name, sizeof(gov->name) - 1))
        {
            return gov;
        }
    }

    return RT_NULL;
}

rt_err_t rt_dvfs_governor_register(struct rt_dvfs_governor *gov)
{
    rt_err_t err = RT_EOK;

    if (!gov)
    {
        return -RT_EINVAL;
    }

    RT_ASSERT(gov->set_frequency != RT_NULL);

    rt_spin_lock(&dvfs_governor_nodes_lock);

    if (dvfs_governor_find(gov->type, gov->name))
    {
        LOG_E("Governor %s[%u] is exists", gov->name, gov->type);
        err = -RT_EFULL;

        goto _out_lock;
    }

    rt_list_init(&gov->list);
    rt_ref_init(&gov->ref);
    rt_list_insert_before(&dvfs_governor_nodes, &gov->list);

_out_lock:
    rt_spin_unlock(&dvfs_governor_nodes_lock);

    return err;
}

rt_err_t rt_dvfs_governor_unregister(struct rt_dvfs_governor *gov)
{
    rt_err_t err = RT_EOK;

    if (!gov)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&dvfs_governor_nodes_lock);

    if (rt_ref_read(&gov->ref) > 1)
    {
        err = -RT_EBUSY;
        goto _out_lock;
    }

    rt_list_remove(&gov->list);

_out_lock:
    rt_spin_unlock(&dvfs_governor_nodes_lock);

    return err;
}

struct rt_dvfs_governor *rt_dvfs_governor_get(rt_uint32_t governor)
{
    struct rt_dvfs_governor *gov;

    rt_spin_lock(&dvfs_governor_nodes_lock);

    if ((gov = dvfs_governor_find(governor, RT_NULL)))
    {
        rt_ref_get(&gov->ref);
    }

    rt_spin_unlock(&dvfs_governor_nodes_lock);

    return gov;
}

struct rt_dvfs_governor *rt_dvfs_governor_get_by_name(const char *name)
{
    struct rt_dvfs_governor *gov;

    rt_spin_lock(&dvfs_governor_nodes_lock);

    if ((gov = dvfs_governor_find(RT_UINT32_MAX, name)))
    {
        rt_ref_get(&gov->ref);
    }

    rt_spin_unlock(&dvfs_governor_nodes_lock);

    return gov;
}

static void dvfs_governor_release(struct rt_ref *ref)
{
}

void rt_dvfs_governor_put(struct rt_dvfs_governor *gov)
{
    if (!gov)
    {
        return;
    }

    rt_ref_put(&gov->ref, dvfs_governor_release);
}
