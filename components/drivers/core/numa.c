/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-24     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.numa"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pic.h>

struct numa_memory
{
    rt_list_t list;

    int nid;
    rt_uint64_t start;
    rt_uint64_t end;

    union
    {
        void *ofw_node;
    };
};

static rt_bool_t numa_enabled = RT_FALSE;
static int cpu_numa_map[RT_CPUS_NR] rt_section(".bss.noclean.numa");
static rt_list_t numa_memory_nodes rt_section(".bss.noclean.numa");

int rt_numa_cpu_id(int cpuid)
{
    if (!numa_enabled)
    {
        return -RT_ENOSYS;
    }

    return cpuid < RT_ARRAY_SIZE(cpu_numa_map) ? cpu_numa_map[cpuid] : -RT_EINVAL;
}

int rt_numa_device_id(struct rt_device *dev)
{
    rt_uint32_t nid = (rt_uint32_t)-RT_ENOSYS;

    if (!numa_enabled)
    {
        return nid;
    }

    return rt_dm_dev_prop_read_u32(dev, "numa-node-id", &nid) ? : (int)nid;
}

rt_err_t rt_numa_memory_affinity(rt_uint64_t phy_addr, rt_bitmap_t *out_affinity)
{
    struct numa_memory *nm;

    if (!out_affinity)
    {
        return -RT_EINVAL;
    }

    if (!numa_enabled)
    {
        /* Default to CPU#0 */
        RT_IRQ_AFFINITY_SET(out_affinity, 0);

        return RT_EOK;
    }

    rt_memset(out_affinity, 0, sizeof(*out_affinity) * RT_BITMAP_LEN(RT_CPUS_NR));

    rt_list_for_each_entry(nm, &numa_memory_nodes, list)
    {
        if (phy_addr >= nm->start && phy_addr < nm->end)
        {
            for (int i = 0; i < RT_ARRAY_SIZE(cpu_numa_map); ++i)
            {
                if (cpu_numa_map[i] == nm->nid)
                {
                    RT_IRQ_AFFINITY_SET(out_affinity, i);
                }
            }

            return RT_EOK;
        }
    }

    return -RT_EEMPTY;
}

#ifdef RT_USING_OFW
static int numa_ofw_init(void)
{
    int i = 0;
    rt_uint32_t nid;
    const char *numa_conf;
    struct rt_ofw_node *np = RT_NULL;

    numa_conf = rt_ofw_bootargs_select("numa=", 0);

    if (!numa_conf || rt_strcmp(numa_conf, "on"))
    {
        return (int)RT_EOK;
    }

    numa_enabled = RT_TRUE;

    for (int i = 0; i < RT_ARRAY_SIZE(cpu_numa_map); ++i)
    {
        cpu_numa_map[i] = -RT_ENOSYS;
    }

    rt_list_init(&numa_memory_nodes);

    rt_ofw_foreach_cpu_node(np)
    {
        rt_ofw_prop_read_u32(np, "numa-node-id", (rt_uint32_t *)&cpu_numa_map[i]);

        if (++i >= RT_CPUS_NR)
        {
            break;
        }
    }

    rt_ofw_foreach_node_by_type(np, "memory")
    {
        if (!rt_ofw_prop_read_u32(np, "numa-node-id", &nid))
        {
            int mem_nr = rt_ofw_get_address_count(np);

            for (i = 0; i < mem_nr; ++i)
            {
                rt_uint64_t addr, size;
                struct numa_memory *nm;

                if (rt_ofw_get_address(np, i, &addr, &size))
                {
                    continue;
                }

                nm = rt_malloc(sizeof(*nm));

                if (!nm)
                {
                    LOG_E("No memory to record NUMA[%d] memory[%p, %p] info",
                            nid, addr, addr + size);

                    return (int)-RT_ENOMEM;
                }

                nm->start = addr;
                nm->end = addr + size;
                nm->ofw_node = np;

                rt_list_init(&nm->list);
                rt_list_insert_before(&numa_memory_nodes, &nm->list);
            }
        }
    }

    return 0;
}
INIT_CORE_EXPORT(numa_ofw_init);
#endif /* RT_USING_OFW */
