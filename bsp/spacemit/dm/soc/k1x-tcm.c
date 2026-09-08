/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "soc.k1x-tcm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <csr.h>
#include <spacemit.h>

static struct rt_memheap *tcm_heap[RT_CPUS_NR];

void *tcm_alloc_cpu(int cpuid, rt_size_t size)
{
    if (cpuid < RT_ARRAY_SIZE(tcm_heap) && tcm_heap[cpuid])
    {
        return rt_memheap_alloc(tcm_heap[cpuid], size);
    }

    return RT_NULL;
}

void tcm_free_cpu(int cpuid, void *ptr)
{
    if (cpuid < RT_ARRAY_SIZE(tcm_heap) && tcm_heap[cpuid])
    {
        rt_memheap_free(ptr);
    }
}

static rt_err_t spacemit_tcm_probe(struct rt_platform_device *pdev)
{
    struct rt_ofw_node *np = pdev->parent.ofw_node, *tcm_np;

    csr_write(CSR_TCMCFG, TCM_EN);

    rt_ofw_foreach_child_node(np, tcm_np)
    {
        int cpuid = 0;
        void *tcm_base;
        rt_uint64_t addr, size;
        const char *string, *node_name;

        if (rt_ofw_get_address(tcm_np, 0, &addr, &size))
        {
            continue;
        }

        string = node_name = rt_fdt_node_name(tcm_np->full_name);
        string += sizeof("core") - 1;

        while (*string >= '0' && *string <= '9')
        {
            cpuid *= 10;
            cpuid += *string - '0';

            ++string;
        }

        tcm_heap[cpuid] = rt_calloc(1, sizeof(struct rt_memheap));

        if (!tcm_heap[cpuid])
        {
            return -RT_ENOMEM;
        }

        if (!(tcm_base = rt_ioremap_cached((void *)addr, size)))
        {
            rt_free(tcm_heap[cpuid]);
            return -RT_EIO;
        }

        if (rt_memheap_init(tcm_heap[cpuid], node_name, tcm_base, size))
        {
            rt_free(tcm_heap[cpuid]);
            tcm_heap[cpuid] = RT_NULL;
        }
    }

    return RT_EOK;
}

static rt_err_t spacemit_tcm_shutdown(struct rt_platform_device *pdev)
{
    csr_clear(CSR_TCMCFG, TCM_EN);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_tcm_ofw_ids[] =
{
    { .compatible = "spacemit,k1-x-tcm"  },
    { .compatible = "spacemit,k1-pro-tcm" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_tcm_driver =
{
    .name   = "spacemit-tcm",
    .ids    = spacemit_tcm_ofw_ids,

    .probe  = spacemit_tcm_probe,
    .shutdown  = spacemit_tcm_shutdown,
};

static int spacemit_tcm_drv_register(void)
{
    rt_platform_driver_register(&spacemit_tcm_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_tcm_drv_register);
