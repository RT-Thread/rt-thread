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

#define DBG_TAG "reset.reboot.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct spacemit_reboot
{
    void *regs;
};

static rt_err_t spacemit_notify_reboot(struct rt_device *dev, char *cmd)
{
    struct spacemit_reboot *reboot = dev->user_data;

    if (cmd)
    {
        if (!rt_strcmp(cmd, "fastboot"))
        {
            HWREG32(reboot->regs) = 0x55a;
        }
        else if (!rt_strcmp(cmd, "uboot"))
        {
            HWREG32(reboot->regs) = 0x55f;
        }
    }

    return RT_EOK;
}

static rt_err_t spacemit_reboot_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_reboot *reboot = rt_calloc(1, sizeof(*reboot));

    if (!reboot)
    {
        return -RT_ENOMEM;
    }

    if (!(reboot->regs = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = rt_dm_reboot_mode_register(dev, spacemit_notify_reboot)))
    {
        goto _fail;
    }

    dev->user_data = reboot;

    return RT_EOK;

_fail:
    if (reboot->regs)
    {
        rt_iounmap(reboot->regs);
    }

    rt_free(reboot);

    return err;
}

static rt_err_t spacemit_reboot_remove(struct rt_platform_device *pdev)
{
    struct spacemit_reboot *reboot = pdev->parent.user_data;

    rt_dm_reboot_mode_unregister(&pdev->parent);

    rt_iounmap(reboot->regs);

    rt_free(reboot);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_reboot_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-reboot", },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_reboot_driver =
{
    .name = "spacemit-reboot",
    .ids = spacemit_reboot_ofw_ids,

    .probe = spacemit_reboot_probe,
    .remove = spacemit_reboot_remove,
};

static int spacemit_reboot_drv_register(void)
{
    rt_platform_driver_register(&spacemit_reboot_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_reboot_drv_register);
