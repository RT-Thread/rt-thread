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
#include <rtdevice.h>

#define DBG_TAG "video.backlight.rpi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <firmware-raspberrypi.h>

struct rpi_backlight
{
    struct rt_backlight_device parent;

    struct rpi_firmware *rpi_fw;
};

#define raw_to_rpi_backlight(raw) rt_container_of(raw, struct rpi_backlight, parent)

static rt_err_t rpi_backlight_update_status(struct rt_backlight_device *bl)
{
    rt_err_t err;
    struct rpi_backlight *rbl = raw_to_rpi_backlight(bl);
    rt_uint32_t brightness = bl->props.brightness;

    if (bl->props.power != RT_BACKLIGHT_POWER_UNBLANK)
    {
        brightness = 0;
    }

    err = rpi_firmware_property(rbl->rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_SET_BACKLIGHT, &brightness, sizeof(brightness));

    if (err)
    {
        LOG_E("Failed to set brightness");

        return err;
    }

    if ((int)brightness < 0)
    {
        LOG_E("Backlight change failed");

        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_backlight_ops rpi_backlight_ops =
{
    .update_status = rpi_backlight_update_status,
};

static rt_err_t rpi_backlight_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    struct rpi_firmware *rpi_fw;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct rpi_backlight *rbl = rt_calloc(1, sizeof(*rbl));

    if (!rbl)
    {
        return -RT_ENOMEM;
    }

    fw_np = rt_ofw_parse_phandle(np, "firmware", 0);

    if (!fw_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rpi_fw = rpi_firmware_get(fw_np);
    rt_ofw_node_put(fw_np);

    if (!rpi_fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    dev->user_data = rbl;

    rbl->rpi_fw = rpi_fw;
    rbl->parent.props.max_brightness = 255;
    rbl->parent.ops = &rpi_backlight_ops;

    if ((err = rt_backlight_register(&rbl->parent)))
    {
        goto _fail;
    }

    rt_backlight_set_brightness(&rbl->parent, 255);

    return RT_EOK;

_fail:
    if (rbl->rpi_fw)
    {
        rpi_firmware_put(rbl->rpi_fw);
    }

    rt_free(rbl);

    return err;
}

static rt_err_t rpi_backlight_remove(struct rt_platform_device *pdev)
{
    struct rpi_backlight *rbl = pdev->parent.user_data;

    rt_backlight_unregister(&rbl->parent);

    rpi_firmware_put(rbl->rpi_fw);
    rt_free(rbl);

    return RT_EOK;
}

static const struct rt_ofw_node_id rpi_backlight_ofw_ids[] =
{
    { .compatible = "raspberrypi,rpi-backlight" },
    { /* sentinel */ }
};

static struct rt_platform_driver rpi_backlight_driver =
{
    .name = "rpi-backlight",
    .ids = rpi_backlight_ofw_ids,

    .probe = rpi_backlight_probe,
    .remove = rpi_backlight_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpi_backlight_driver);
