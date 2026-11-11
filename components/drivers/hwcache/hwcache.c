/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <drivers/hwcache.h>

#define DBG_TAG "rtdm.hwcache"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct rt_hwcache_ops *rt_dm_cpu_dcache_ops = RT_NULL;
struct rt_hwcache_ops *rt_dm_cpu_icache_ops = RT_NULL;

static void hwcache_enable(struct rt_hwcache_ops *ops)
{
    if (ops && ops->enable)
    {
        ops->enable();
    }
}

static void hwcache_disable(struct rt_hwcache_ops *ops)
{
    if (ops && ops->enable)
    {
        ops->enable();
    }
}

static rt_base_t hwcache_status(struct rt_hwcache_ops *ops)
{
    if (ops && ops->status)
    {
        return ops->status();
    }

    return 0;
}

static void hwcache_ops(struct rt_hwcache_ops *ops, int op, void *addr, int size)
{
    if (ops)
    {
        if (op == RT_HW_CACHE_FLUSH)
        {
            if (ops->flush)
            {
                ops->flush(addr, size);
            }
        }
        else if (op == RT_HW_CACHE_INVALIDATE)
        {
            if (ops->invalidate)
            {
                ops->invalidate(addr, size);
            }
        }
    }
}

void rt_hwcache_icache_enable(void)
{
    hwcache_enable(rt_dm_cpu_icache_ops);
}

void rt_hwcache_icache_disable(void)
{
    hwcache_disable(rt_dm_cpu_icache_ops);
}

rt_base_t rt_hwcache_icache_status(void)
{
    return hwcache_status(rt_dm_cpu_icache_ops);
}

void rt_hwcache_icache_ops(int ops, void *addr, int size)
{
    hwcache_ops(rt_dm_cpu_icache_ops, ops, addr, size);
}

void rt_hwcache_dcache_enable(void)
{
    hwcache_enable(rt_dm_cpu_dcache_ops);
}

void rt_hwcache_dcache_disable(void)
{
    hwcache_disable(rt_dm_cpu_dcache_ops);
}

rt_base_t rt_hwcache_dcache_status(void)
{
    return hwcache_status(rt_dm_cpu_dcache_ops);
}

void rt_hwcache_dcache_ops(int ops, void *addr, int size)
{
    hwcache_ops(rt_dm_cpu_dcache_ops, ops, addr, size);
}

#ifdef RT_USING_OFW
RT_OFW_STUB_RANGE_EXPORT(hwcache, _hwcache_ofw_start, _hwcache_ofw_end);

static rt_err_t ofw_hwcache_init(void)
{
    struct rt_ofw_node *cache_np;

    rt_ofw_foreach_allnodes(cache_np)
    {
        rt_ofw_stub_probe_range(cache_np, &_hwcache_ofw_start, &_hwcache_ofw_end);
    }

    return RT_EOK;
}
#else
static rt_err_t ofw_hwcache_init(void)
{
    return RT_EOK;
}
#endif /* !RT_USING_OFW */

rt_err_t rt_hwcache_init(void)
{
    rt_err_t err;

    LOG_D("init start");

    err = ofw_hwcache_init();

    LOG_D("init end");

    return err;
}
