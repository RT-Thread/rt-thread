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

#define DBG_TAG "reset.syscon.reboot"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_syscon *syscon;
static rt_uint32_t offset, value, mask;

static void syscon_reboot(void)
{
    /* Issue the reboot */
    rt_syscon_update_bits(syscon, offset, mask, value);

    rt_thread_mdelay(1000);

    LOG_E("Unable to restart system");
}

static rt_err_t syscon_reboot_probe(struct rt_platform_device *pdev)
{
    rt_err_t mask_err, value_err;
    struct rt_ofw_node *np = pdev->parent.ofw_node;

    syscon = rt_syscon_find_by_ofw_phandle(np, "regmap");

    if (!syscon)
    {
        return -RT_ERROR;
    }

    if (rt_ofw_prop_read_u32(np, "offset", &offset))
    {
        LOG_E("read '%s' fail", "offset");

        return -RT_EINVAL;
    }

    value_err = rt_ofw_prop_read_u32(np, "value", &value);
    mask_err = rt_ofw_prop_read_u32(np, "mask", &mask);

    if (value_err && mask_err)
    {
        LOG_E("read '%s' and '%s' fail", "value", "mask");

        return -RT_EINVAL;
    }

    if (value_err)
    {
        /* support old binding */
        value = mask;
        mask = 0xffffffff;
    }
    else if (mask_err)
    {
        /* support value without mask */
        mask = 0xffffffff;
    }

    if (rt_dm_machine_reset)
    {
        LOG_E("rt_dm_machine_reset have hook %p", rt_dm_machine_reset);

        return -RT_EBUSY;
    }

    rt_dm_machine_reset = syscon_reboot;

    return RT_EOK;
}

static const struct rt_ofw_node_id syscon_reboot_ofw_ids[] =
{
    { .compatible = "syscon-reboot" },
    { /* sentinel */ }
};

static struct rt_platform_driver syscon_reboot_driver =
{
    .name = "reset-syscon-reboot",
    .ids = syscon_reboot_ofw_ids,

    .probe = syscon_reboot_probe,
};

static int syscon_reboot_driver_register(void)
{
    rt_platform_driver_register(&syscon_reboot_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(syscon_reboot_driver_register);
