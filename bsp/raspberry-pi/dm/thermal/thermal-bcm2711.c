/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "thermal.bcm2711"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define AVS_RO_TEMP_STATUS              0x200
#define AVS_RO_TEMP_STATUS_VALID_MSK    (RT_BIT(16) | RT_BIT(10))
#define AVS_RO_TEMP_STATUS_DATA_MSK     RT_GENMASK(9, 0)

struct bcm2711_thermal
{
    struct rt_thermal_zone_device parent;

    struct rt_syscon *regmap;
};

#define raw_to_bcm2711_thermal(raw) rt_container_of(raw, struct bcm2711_thermal, parent)

static rt_err_t bcm2711_thermal_zone_get_temp(struct rt_thermal_zone_device *zdev,
        int *out_temp)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rt_thermal_zone_params *tz_params;
    struct bcm2711_thermal *btz = raw_to_bcm2711_thermal(zdev);

    if ((err = rt_syscon_read(btz->regmap, AVS_RO_TEMP_STATUS, &val)))
    {
        return err;
    }

    if (!(val & AVS_RO_TEMP_STATUS_VALID_MSK))
    {
        return -RT_EIO;
    }

    val &= AVS_RO_TEMP_STATUS_DATA_MSK;
    tz_params = &btz->parent.params;

    /* Convert a HW code to a temperature reading (millidegree celsius) */
    *out_temp = tz_params->slope * val + tz_params->offset;

    return RT_EOK;
}

const static struct rt_thermal_zone_ops bcm2711_thermal_zone_ops =
{
    .get_temp = bcm2711_thermal_zone_get_temp,
};

static rt_err_t bcm2711_thermal_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_ofw_node *pnp;
    struct rt_device *dev = &pdev->parent;
    struct bcm2711_thermal *btz = rt_calloc(1, sizeof(*btz));

    if (!btz)
    {
        return -RT_ENOMEM;
    }

    pnp = rt_ofw_get_parent(dev->ofw_node);

    if (!pnp)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    btz->regmap = rt_syscon_find_by_ofw_node(pnp);
    rt_ofw_node_put(pnp);

    if (!btz->regmap)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    btz->parent.parent.ofw_node = dev->ofw_node;
    btz->parent.ops = &bcm2711_thermal_zone_ops;

    rt_dm_dev_set_name(&btz->parent.parent, "bcm2711");

    if ((err = rt_thermal_zone_device_register(&btz->parent)))
    {
        goto _fail;
    }

    dev->user_data = btz;

    return RT_EOK;

_fail:
    rt_free(btz);

    return err;
}

static rt_err_t bcm2711_thermal_remove(struct rt_platform_device *pdev)
{
    struct bcm2711_thermal *btz = pdev->parent.user_data;

    rt_thermal_zone_device_unregister(&btz->parent);

    rt_free(btz);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2711_thermal_ofw_ids[] =
{
    { .compatible = "brcm,bcm2711-thermal" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2711_thermal_driver =
{
    .name = "bcm2711-thermal",
    .ids = bcm2711_thermal_ofw_ids,

    .probe = bcm2711_thermal_probe,
    .remove = bcm2711_thermal_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2711_thermal_driver);
