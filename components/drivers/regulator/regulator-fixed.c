/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "regulator_dm.h"

struct regulator_fixed
{
    struct rt_regulator_node parent;
    struct rt_regulator_param param;

    rt_base_t enable_pin;
    const char *input_supply;
};

#define raw_to_regulator_fixed(raw) rt_container_of(raw, struct regulator_fixed, parent)

static rt_err_t regulator_fixed_enable(struct rt_regulator_node *reg_np)
{
    struct regulator_fixed *rf = raw_to_regulator_fixed(reg_np);
    struct rt_regulator_param *param = &rf->param;

    if (rf->enable_pin < 0 || param->always_on)
    {
        return RT_EOK;
    }

    rt_pin_mode(rf->enable_pin, PIN_MODE_OUTPUT);
    rt_pin_write(rf->enable_pin, param->enable_active_high ? PIN_HIGH : PIN_LOW);

    return RT_EOK;
}

static rt_err_t regulator_fixed_disable(struct rt_regulator_node *reg_np)
{
    struct regulator_fixed *rf = raw_to_regulator_fixed(reg_np);
    struct rt_regulator_param *param = &rf->param;

    if (rf->enable_pin < 0 || param->always_on)
    {
        return RT_EOK;
    }

    rt_pin_mode(rf->enable_pin, PIN_MODE_OUTPUT);
    rt_pin_write(rf->enable_pin, param->enable_active_high ? PIN_LOW: PIN_HIGH);

    return RT_EOK;
}

static rt_bool_t regulator_fixed_is_enabled(struct rt_regulator_node *reg_np)
{
    rt_uint8_t active;
    struct regulator_fixed *rf = raw_to_regulator_fixed(reg_np);
    struct rt_regulator_param *param = &rf->param;

    if (rf->enable_pin < 0 || param->always_on)
    {
        return RT_TRUE;
    }

    rt_pin_mode(rf->enable_pin, PIN_MODE_INPUT);
    active = rt_pin_read(rf->enable_pin);

    if (param->enable_active_high)
    {
        return active == PIN_HIGH;
    }

    return active == PIN_LOW;
}

static int regulator_fixed_get_voltage(struct rt_regulator_node *reg_np)
{
    struct regulator_fixed *rf = raw_to_regulator_fixed(reg_np);

    return rf->param.min_uvolt + (rf->param.max_uvolt - rf->param.min_uvolt) / 2;
}

static const struct rt_regulator_ops regulator_fixed_ops =
{
    .enable = regulator_fixed_enable,
    .disable = regulator_fixed_disable,
    .is_enabled = regulator_fixed_is_enabled,
    .get_voltage = regulator_fixed_get_voltage,
};

static rt_err_t regulator_fixed_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rt_device *dev = &pdev->parent;
    struct regulator_fixed *rf = rt_calloc(1, sizeof(*rf));
    struct rt_regulator_node *rnp;

    if (!rf)
    {
        return -RT_ENOMEM;
    }

    regulator_ofw_parse(dev->ofw_node, &rf->param);

    rnp = &rf->parent;
    rnp->supply_name = rf->param.name;
    rnp->ops = &regulator_fixed_ops;
    rnp->param = &rf->param;
    rnp->dev = &pdev->parent;

    rf->enable_pin = rt_pin_get_named_pin(dev, "enable", 0, RT_NULL, RT_NULL);

    if (rf->enable_pin < 0)
    {
        rf->enable_pin = rt_pin_get_named_pin(dev, RT_NULL, 0, RT_NULL, RT_NULL);
    }

    if (rf->enable_pin < 0)
    {
        rf->enable_pin = -1;
    }

    rt_pin_ctrl_confs_apply(dev, 0);

    if (!rt_dm_dev_prop_read_u32(dev, "startup-delay-us", &val))
    {
        rf->param.enable_delay = val;
    }

    if (!rt_dm_dev_prop_read_u32(dev, "off-on-delay-us", &val))
    {
        rf->param.off_on_delay = val;
    }

    if ((err = rt_regulator_register(rnp)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(rf);

    return err;
}

static const struct rt_ofw_node_id regulator_fixed_ofw_ids[] =
{
    { .compatible = "regulator-fixed" },
    { /* sentinel */ }
};

static struct rt_platform_driver regulator_fixed_driver =
{
    .name = "reg-fixed-voltage",
    .ids = regulator_fixed_ofw_ids,

    .probe = regulator_fixed_probe,
};

static int regulator_fixed_register(void)
{
    rt_platform_driver_register(&regulator_fixed_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(regulator_fixed_register);
