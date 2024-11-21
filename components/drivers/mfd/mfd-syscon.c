/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <ioremap.h>
#include <drivers/ofw_io.h>
#include <drivers/syscon.h>
#include <drivers/core/dm.h>
#include <drivers/platform.h>

static struct rt_spinlock _syscon_nodes_lock = { 0 };
static rt_list_t _syscon_nodes = RT_LIST_OBJECT_INIT(_syscon_nodes);

rt_err_t rt_syscon_read(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t *out_val)
{
    if (offset < syscon->iomem_size)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&syscon->rw_lock);

        *out_val = HWREG32(syscon->iomem_base + offset);

        rt_spin_unlock_irqrestore(&syscon->rw_lock, level);

        return RT_EOK;
    }
    else
    {
        return -RT_EINVAL;
    }
}

rt_err_t rt_syscon_write(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t val)
{
    if (offset < syscon->iomem_size)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&syscon->rw_lock);

        HWREG32(syscon->iomem_base + offset) = val;

        rt_spin_unlock_irqrestore(&syscon->rw_lock, level);

        return RT_EOK;
    }
    else
    {
        return -RT_EINVAL;
    }
}

rt_err_t rt_syscon_update_bits(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t mask, rt_uint32_t val)
{
    rt_err_t err;
    rt_ubase_t level = rt_spin_lock_irqsave(&syscon->rw_lock);

    if (offset < syscon->iomem_size)
    {
        rt_uint32_t old_val = HWREG32(syscon->iomem_base + offset);

        old_val &= ~mask;

        HWREG32(syscon->iomem_base + offset) = old_val | val;

        err = RT_EOK;
    }
    else
    {
        err = -RT_EINVAL;
    }

    rt_spin_unlock_irqrestore(&syscon->rw_lock, level);

    return err;
}

static rt_err_t syscon_probe(struct rt_platform_device *pdev);

struct rt_syscon *rt_syscon_find_by_ofw_node(struct rt_ofw_node *np)
{
    rt_ubase_t level;
    struct rt_syscon *syscon = RT_NULL, *syscon_tmp;
    struct rt_platform_device syscon_pdev;

    if (!np)
    {
        goto _exit;
    }

    level = rt_spin_lock_irqsave(&_syscon_nodes_lock);

    /* ofw_data is not safety */
    rt_list_for_each_entry(syscon_tmp, &_syscon_nodes, list)
    {
        if (syscon_tmp->np == np)
        {
            syscon = syscon_tmp;
            break;
        }
    }

    rt_spin_unlock_irqrestore(&_syscon_nodes_lock, level);

    if (syscon)
    {
        goto _exit;
    }

    /* Not found, try probe this node */
    if (!rt_ofw_node_is_compatible(np, "syscon") &&
        !rt_ofw_node_is_compatible(np, "simple-mfd"))
    {
        goto _exit;
    }

    syscon_pdev.parent.ofw_node = np;

    if (!syscon_probe(&syscon_pdev))
    {
        syscon = rt_ofw_data(np);
    }

_exit:
    return syscon;
}

struct rt_syscon *rt_syscon_find_by_ofw_compatible(const char *compatible)
{
    struct rt_syscon *syscon = RT_NULL;
    struct rt_ofw_node *syscon_np = rt_ofw_find_node_by_compatible(RT_NULL, compatible);

    if (syscon_np)
    {
        syscon = rt_syscon_find_by_ofw_node(syscon_np);

        rt_ofw_node_put(syscon_np);
    }

    return syscon;
}

struct rt_syscon *rt_syscon_find_by_ofw_phandle(struct rt_ofw_node *np, const char *propname)
{
    struct rt_syscon *syscon = RT_NULL;
    struct rt_ofw_node *syscon_np = rt_ofw_parse_phandle(np, propname, 0);

    if (syscon_np)
    {
        syscon = rt_syscon_find_by_ofw_node(syscon_np);

        rt_ofw_node_put(syscon_np);
    }

    return syscon;
}

static rt_err_t syscon_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_ubase_t level;
    struct rt_ofw_node *np;
    rt_uint64_t iomem_range[2];
    struct rt_syscon *syscon = rt_calloc(1, sizeof(*syscon));

    if (!syscon)
    {
        return -RT_ENOMEM;
    }

    np = pdev->parent.ofw_node;

    if ((err = rt_ofw_get_address(np, 0, &iomem_range[0], &iomem_range[1])))
    {
        goto _fail;
    }

    syscon->iomem_size = (rt_size_t)iomem_range[1];
    syscon->iomem_base = rt_ioremap((void *)iomem_range[0], syscon->iomem_size);

    if (!syscon->iomem_base)
    {
        goto _fail;
    }

    rt_list_init(&syscon->list);
    level = rt_spin_lock_irqsave(&_syscon_nodes_lock);
    rt_list_insert_after(&_syscon_nodes, &syscon->list);
    rt_spin_unlock_irqrestore(&_syscon_nodes_lock, level);

    rt_spin_lock_init(&syscon->rw_lock);

    pdev->parent.user_data = syscon;

    syscon->np = pdev->parent.ofw_node;
    rt_ofw_data(np) = syscon;

    return RT_EOK;

_fail:
    rt_free(syscon);

    return err;
}

static rt_err_t syscon_remove(struct rt_platform_device *pdev)
{
    struct rt_syscon *syscon = pdev->parent.user_data;

    rt_iounmap(syscon->iomem_base);

    rt_free(syscon);

    return RT_EOK;
}

static const struct rt_ofw_node_id syscon_ofw_ids[] =
{
    { .compatible = "syscon" },
    { /* sentinel */ }
};

static struct rt_platform_driver syscon_driver =
{
    .name = "mfd-syscon",
    .ids = syscon_ofw_ids,

    .probe = syscon_probe,
    .remove = syscon_remove,
};

static int syscon_drv_register(void)
{
    rt_platform_driver_register(&syscon_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(syscon_drv_register);
