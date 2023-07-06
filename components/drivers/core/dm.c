/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-20     ErikChan     the first version
 */

#include <rtthread.h>

#include <drivers/core/rtdm.h>

#ifdef RT_USING_SMP
static int rti_secondary_cpu_start(void)
{
    return 0;
}
INIT_EXPORT(rti_secondary_cpu_start, "6.end");

static int rti_secondary_cpu_end(void)
{
    return 0;
}
INIT_EXPORT(rti_secondary_cpu_end, "7.end");

void rt_dm_secondary_cpu_init(void)
{
#if RT_DEBUG_INIT
    int result;
    const struct rt_init_desc *desc;

    rt_kprintf("do secondary cpu initialization.\n");
    for (desc = &__rt_init_desc_rti_secondary_cpu_start; desc < &__rt_init_desc_rti_secondary_cpu_end; ++desc)
    {
        rt_kprintf("initialize %s", desc->fn_name);
        result = desc->fn();
        rt_kprintf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_secondary_cpu_start; fn_ptr < &__rt_init_rti_secondary_cpu_end; ++fn_ptr)
    {
        (*fn_ptr)();
    }
#endif /* RT_DEBUG_INIT */
}
#endif /* RT_USING_SMP */

struct prefix_track
{
    rt_list_t list;

    int uid;
    const char *prefix;
};
static struct rt_spinlock _prefix_nodes_lock;
static rt_list_t _prefix_nodes = RT_LIST_OBJECT_INIT(_prefix_nodes);

int rt_dm_set_dev_name_auto(rt_device_t dev, const char *prefix)
{
    int uid = -1;
    struct prefix_track *pt = RT_NULL;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(prefix != RT_NULL);

    RT_DEBUG_NOT_IN_INTERRUPT;

    rt_spin_lock(&_prefix_nodes_lock);

    rt_list_for_each_entry(pt, &_prefix_nodes, list)
    {
        /* caller always input constants string, check ptr is faster */
        if (pt->prefix == prefix || !rt_strcmp(pt->prefix, prefix))
        {
            uid = ++pt->uid;
            break;
        }
    }

    rt_spin_unlock(&_prefix_nodes_lock);

    if (uid < 0)
    {
        pt = rt_malloc(sizeof(*pt));

        if (!pt)
        {
            return -RT_ENOMEM;
        }

        rt_list_init(&pt->list);

        pt->uid = uid = 0;
        pt->prefix = prefix;

        rt_spin_lock(&_prefix_nodes_lock);

        rt_list_insert_before(&_prefix_nodes, &pt->list);

        rt_spin_unlock(&_prefix_nodes_lock);
    }

    return rt_dm_set_dev_name(dev, "%s%u", prefix, uid);
}

int rt_dm_get_dev_name_id(rt_device_t dev)
{
    int id = 0, len;
    const char *name;

    RT_ASSERT(dev != RT_NULL);

    name = rt_dm_get_dev_name(dev);
    len = rt_strlen(name) - 1;
    name += len;

    while (len --> 0)
    {
        if (*name < '0' || *name > '9')
        {
            while (*(++name))
            {
                id *= 10;
                id += *name - '0';
            }

            break;
        }

        --name;
    }

    return id;
}

int rt_dm_set_dev_name(rt_device_t dev, const char *format, ...)
{
    int n;
    va_list arg_ptr;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(format != RT_NULL);

    va_start(arg_ptr, format);
    n = rt_vsnprintf(dev->parent.name, RT_NAME_MAX, format, arg_ptr);
    va_end(arg_ptr);

    return n;
}

const char *rt_dm_get_dev_name(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    return dev->parent.name;
}
