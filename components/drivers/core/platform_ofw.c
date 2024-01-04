/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     GuEe-GUI     the first version
 */

#include <rtthread.h>

#define DBG_TAG "drv.platform"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/ofw_io.h>
#include <drivers/ofw_fdt.h>
#include <drivers/platform.h>
#include <drivers/core/dm.h>

#include "../ofw/ofw_internal.h"

static const struct rt_ofw_node_id platform_ofw_ids[] =
{
    { .compatible = "simple-bus", },
#ifdef RT_USING_MFD
    { .compatible = "simple-mfd", },
#endif
#ifdef RT_USING_ISA
    { .compatible = "isa", },
#endif
#ifdef RT_USING_AMBA_BUS
    /*
     * Maybe ARM has replaced it with compatible: "arm,primecell" and will not
     * used anymore in the future.
     */
    { .compatible = "arm,amba-bus", },
#endif
    { /* sentinel */ }
};

static void ofw_device_rename(struct rt_device *dev)
{
    rt_uint32_t mask;
    rt_uint64_t addr;
    const char *dev_name = dev->parent.name;
    struct rt_ofw_node *np = dev->ofw_node;

#if RT_NAME_MAX > 0
    if (dev_name[0] == '\0')
    {
        dev_name = RT_NULL;
    }
#endif

    while (np->parent)
    {
        if (!rt_ofw_get_address(np, 0, &addr, RT_NULL))
        {
            const char *node_name = rt_fdt_node_name(np->full_name);
            rt_size_t tag_len = strchrnul(node_name, '@') - node_name;

            if (!rt_ofw_prop_read_u32(np, "mask", &mask))
            {
                rt_dm_dev_set_name(dev, dev_name ? "%lx.%x.%.*s:%s" : "%lx.%x.%.*s",
                    addr, __rt_ffs(mask) - 1, tag_len, node_name, dev_name);
            }
            else
            {
                rt_dm_dev_set_name(dev, dev_name ? "%lx.%.*s:%s" : "%lx.%.*s",
                    addr, tag_len, node_name, dev_name);
            }

            return;
        }

        rt_dm_dev_set_name(dev, dev_name ? "%s:%s" : "%s",
                rt_fdt_node_name(np->full_name), dev_name);

        np = np->parent;
    }
}

static struct rt_platform_device *alloc_ofw_platform_device(struct rt_ofw_node *np)
{
    struct rt_platform_device *pdev = rt_platform_device_alloc("");

    if (pdev)
    {
        /* inc reference of dt-node */
        rt_ofw_node_get(np);
        rt_ofw_node_set_flag(np, RT_OFW_F_PLATFORM);

#ifdef RT_USING_OFW
        pdev->parent.ofw_node = np;
#endif

        ofw_device_rename(&pdev->parent);
    }
    else
    {
        LOG_E("Alloc device fail for %s", rt_ofw_node_full_name(np));
    }

    return pdev;
}

static rt_err_t platform_ofw_device_probe_once(struct rt_ofw_node *parent_np)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *np;
    struct rt_platform_device *pdev;

    rt_ofw_foreach_available_child_node(parent_np, np)
    {
        const char *name;
        struct rt_ofw_node_id *id;
        struct rt_ofw_prop *compat_prop = RT_NULL;

        LOG_D("%s found in %s", np->full_name, parent_np->full_name);

        /* Is system node or have driver */
        if (rt_ofw_node_test_flag(np, RT_OFW_F_SYSTEM) ||
            rt_ofw_node_test_flag(np, RT_OFW_F_READLY))
        {
            continue;
        }

        compat_prop = rt_ofw_get_prop(np, "compatible", RT_NULL);
        name = rt_ofw_node_name(np);

        /* Not have name and compatible */
        if (!compat_prop && (name == (const char *)"<NULL>" || !rt_strcmp(name, "<NULL>")))
        {
            continue;
        }

        id = rt_ofw_prop_match(compat_prop, platform_ofw_ids);

        if (id && np->child)
        {
            /* scan next level */
            err = platform_ofw_device_probe_once(np);

            if (err)
            {
                rt_ofw_node_put(np);
                LOG_E("%s bus probe fail", np->full_name);

                break;
            }
        }

        pdev = alloc_ofw_platform_device(np);

        if (!pdev)
        {
            rt_ofw_node_put(np);
            err = -RT_ENOMEM;

            break;
        }

        pdev->dev_id = ofw_alias_node_id(np);
        LOG_D("%s register to bus", np->full_name);

        rt_platform_device_register(pdev);
    }

    return err;
}

rt_err_t rt_platform_ofw_device_probe_child(struct rt_ofw_node *np)
{
    rt_err_t err;
    struct rt_ofw_node *parent = rt_ofw_get_parent(np);

    if (parent && rt_strcmp(parent->name, "/") &&
        rt_ofw_get_prop(np, "compatible", RT_NULL) &&
        !rt_ofw_node_test_flag(np, RT_OFW_F_PLATFORM))
    {
        struct rt_platform_device *pdev = alloc_ofw_platform_device(np);

        if (pdev)
        {
            err = rt_platform_device_register(pdev);
        }
        else
        {
            err = -RT_ENOMEM;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    rt_ofw_node_put(parent);

    return err;
}

static int platform_ofw_device_probe(void)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *node;

    if (ofw_node_root)
    {
        err = platform_ofw_device_probe_once(ofw_node_root);

        rt_ofw_node_put(ofw_node_root);

        if ((node = rt_ofw_find_node_by_path("/firmware")))
        {
            platform_ofw_device_probe_once(node);
            rt_ofw_node_put(node);
        }

        if ((node = rt_ofw_get_child_by_compatible(ofw_node_chosen, "simple-framebuffer")))
        {
            platform_ofw_device_probe_once(node);
            rt_ofw_node_put(node);
        }
    }
    else
    {
        err = -RT_ENOSYS;
    }

    return (int)err;
}
INIT_PLATFORM_EXPORT(platform_ofw_device_probe);
