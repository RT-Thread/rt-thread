/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

#include <drivers/platform.h>
#include <drivers/core/dm.h>

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

static rt_err_t platform_ofw_device_probe_once(struct rt_ofw_node *parent_np)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *np, *child;
    struct rt_platform_device *pdev;

    rt_ofw_foreach_available_child_node(parent_np, np)
    {
        const char *name;
        struct rt_ofw_node_id *id;
        struct rt_ofw_prop *compat_prop = RT_NULL;

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

        if (id && (child = rt_ofw_get_next_child(np, RT_NULL)))
        {
            /* scan next level */
            err = platform_ofw_device_probe_once(child);

            rt_ofw_node_put(child);

            if (err)
            {
                LOG_E("%s bus probe fail", np->full_name);

                break;
            }
        }

        pdev = rt_platform_device_alloc(np->name);

        if (!pdev)
        {
            err = -RT_ENOMEM;

            break;
        }

        /* inc reference of dt-node */
        rt_ofw_node_get(np);
        rt_ofw_node_set_flag(np, RT_OFW_F_PLATFORM);

        pdev->parent.ofw_node = np;

        rt_platform_device_register(pdev);
    }

    return err;
}

static int platform_ofw_device_probe(void)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *root_np;

    root_np = rt_ofw_find_node_by_path("/");

    if (root_np)
    {
        err = platform_ofw_device_probe_once(root_np);

        rt_ofw_node_put(root_np);
    }
    else
    {
        err = -RT_ENOSYS;
    }

    return (int)err;
}
INIT_PLATFORM_EXPORT(platform_ofw_device_probe);
