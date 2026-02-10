/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "reset.syscon.reboot-mode"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "reboot-mode.h"

struct syscon_reboot_mode
{
    struct rt_syscon *map;

    struct reboot_mode reboot;

    rt_uint32_t offset;
    rt_uint32_t mask;
};

static rt_err_t syscon_reboot_mode_write(struct reboot_mode *reboot,
        rt_uint32_t magic)
{
    rt_err_t err;
    struct syscon_reboot_mode *srbm;

    srbm = rt_container_of(reboot, struct syscon_reboot_mode, reboot);

    err = rt_syscon_update_bits(srbm->map, srbm->offset, srbm->mask, magic);

    if (err)
    {
        LOG_E("Update reboot mode bits failed");
    }

    return err;
}

static rt_err_t syscon_reboot_mode_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_ofw_node *np;
    struct rt_device *dev = &pdev->parent;
    struct syscon_reboot_mode *srbm = rt_calloc(1, sizeof(*srbm));

    if (!srbm)
    {
        return -RT_ENOMEM;
    }

    np = rt_ofw_get_parent(dev->ofw_node);
    srbm->map = rt_syscon_find_by_ofw_node(np);
    rt_ofw_node_put(np);

    if (!srbm->map)
    {
        err = -RT_EIO;
        goto _fail;
    }

    srbm->reboot.dev = dev;
    srbm->reboot.write = syscon_reboot_mode_write;
    srbm->mask = 0xffffffff;

    if (rt_dm_dev_prop_read_u32(dev, "offset", &srbm->offset))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rt_dm_dev_prop_read_u32(dev, "mask", &srbm->mask);

    if ((err = reboot_mode_register(&srbm->reboot)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(srbm);

    return err;
}

static const struct rt_ofw_node_id syscon_reboot_mode_ofw_ids[] =
{
    { .compatible = "syscon-reboot-mode" },
    { /* sentinel */ }
};

static struct rt_platform_driver syscon_reboot_mode_driver =
{
    .name = "reset-syscon-reboot-mode",
    .ids = syscon_reboot_mode_ofw_ids,

    .probe = syscon_reboot_mode_probe,
};

static int syscon_reboot_mode_driver_register(void)
{
    rt_platform_driver_register(&syscon_reboot_mode_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(syscon_reboot_mode_driver_register);
