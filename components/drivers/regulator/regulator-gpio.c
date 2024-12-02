/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <dt-bindings/pin/state.h>

#include "regulator_dm.h"

struct regulator_gpio_state
{
    rt_uint32_t value;
    rt_uint32_t gpios;
};

struct regulator_gpio_desc
{
    rt_base_t pin;
    rt_uint32_t flags;
};

struct regulator_gpio
{
    struct rt_regulator_node parent;

    rt_base_t enable_pin;

    rt_size_t pins_nr;
    struct regulator_gpio_desc *pins_desc;

    int state;
    rt_size_t states_nr;
    struct regulator_gpio_state *states;

    const char *input_supply;
    rt_uint32_t startup_delay;
    rt_uint32_t off_on_delay;
    rt_bool_t enabled_at_boot;
    struct rt_regulator_param param;
};

#define raw_to_regulator_gpio(raw) rt_container_of(raw, struct regulator_gpio, parent)

static rt_err_t regulator_gpio_enable(struct rt_regulator_node *reg_np)
{
    struct regulator_gpio *rg = raw_to_regulator_gpio(reg_np);
    struct rt_regulator_param *param = &rg->param;

    if (param->always_on)
    {
        return RT_EOK;
    }

    if (rg->enable_pin >= 0)
    {
        rt_pin_mode(rg->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(rg->enable_pin, param->enable_active_high ? PIN_HIGH : PIN_LOW);
    }

    return RT_EOK;
}

static rt_err_t regulator_gpio_disable(struct rt_regulator_node *reg_np)
{
    struct regulator_gpio *rg = raw_to_regulator_gpio(reg_np);
    struct rt_regulator_param *param = &rg->param;

    if (param->always_on)
    {
        return RT_EOK;
    }

    if (rg->enable_pin >= 0)
    {
        rt_pin_mode(rg->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(rg->enable_pin, param->enable_active_high ? PIN_LOW : PIN_HIGH);
    }

    return RT_EOK;
}

static rt_bool_t regulator_gpio_is_enabled(struct rt_regulator_node *reg_np)
{
    struct regulator_gpio *rg = raw_to_regulator_gpio(reg_np);
    struct rt_regulator_param *param = &rg->param;

    if (param->always_on)
    {
        return RT_TRUE;
    }

    if (rg->enable_pin >= 0)
    {
        rt_uint8_t active_val = param->enable_active_high ? PIN_LOW : PIN_HIGH;

        rt_pin_mode(rg->enable_pin, PIN_MODE_INPUT);
        return rt_pin_read(rg->enable_pin) == active_val;
    }

    return RT_TRUE;
}

static rt_err_t regulator_gpio_set_voltage(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    int target = 0, best_val = RT_REGULATOR_UVOLT_INVALID;
    struct regulator_gpio *rg = raw_to_regulator_gpio(reg_np);

    for (int i = 0; i < rg->states_nr; ++i)
    {
        struct regulator_gpio_state *state = &rg->states[i];

        if (state->value < best_val &&
            state->value >= min_uvolt &&
            state->value <= max_uvolt)
        {
            target = state->gpios;
            best_val = state->value;
        }
    }

    if (best_val == RT_REGULATOR_UVOLT_INVALID)
    {
        return -RT_EINVAL;
    }

    for (int i = 0; i < rg->pins_nr; ++i)
    {
        int state = (target >> i) & 1;
        struct regulator_gpio_desc *gpiod = &rg->pins_desc[i];

        rt_pin_mode(gpiod->pin, PIN_MODE_OUTPUT);
        rt_pin_write(gpiod->pin, gpiod->flags == PIND_OUT_HIGH ? state : !state);
    }

    rg->state = target;

    return RT_EOK;
}

static int regulator_gpio_get_voltage(struct rt_regulator_node *reg_np)
{
    struct regulator_gpio *rg = raw_to_regulator_gpio(reg_np);

    for (int i = 0; i < rg->states_nr; ++i)
    {
        if (rg->states[i].gpios == rg->state)
        {
            return rg->states[i].value;
        }
    }

    return -RT_EINVAL;
}

static const struct rt_regulator_ops regulator_gpio_ops =
{
    .enable = regulator_gpio_enable,
    .disable = regulator_gpio_disable,
    .is_enabled = regulator_gpio_is_enabled,
    .set_voltage = regulator_gpio_set_voltage,
    .get_voltage = regulator_gpio_get_voltage,
};

static rt_err_t regulator_gpio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct regulator_gpio *rg = rt_calloc(1, sizeof(*rg));
    struct rt_regulator_node *rgp;

    if (!rg)
    {
        return -RT_ENOMEM;
    }

    regulator_ofw_parse(dev->ofw_node, &rg->param);

    rgp = &rg->parent;
    rgp->supply_name = rg->param.name;
    rgp->ops = &regulator_gpio_ops;
    rgp->param = &rg->param;
    rgp->dev = &pdev->parent;

    rt_dm_dev_prop_read_u32(dev, "startup-delay-us", &rg->startup_delay);
    rt_dm_dev_prop_read_u32(dev, "off-on-delay-us", &rg->off_on_delay);

    /* GPIO flags are ignored, we check by enable-active-high */
    rg->enable_pin = rt_pin_get_named_pin(dev, "enable", 0, RT_NULL, RT_NULL);

    if (rg->enable_pin < 0 && rg->enable_pin != -RT_EEMPTY)
    {
        err = rg->enable_pin;
        goto _fail;
    }

    rg->pins_nr = rt_pin_get_named_pin_count(dev, "gpios");

    if (rg->pins_nr > 0)
    {
        rg->pins_desc = rt_malloc(sizeof(*rg->pins_desc) * rg->pins_nr);

        if (!rg->pins_desc)
        {
            err = -RT_ENOMEM;

            goto _fail;
        }

        for (int i = 0; i < rg->pins_nr; ++i)
        {
            rt_uint32_t val;
            struct regulator_gpio_desc *gpiod = &rg->pins_desc[i];

            gpiod->pin = rt_pin_get_named_pin(dev, RT_NULL, i, RT_NULL, RT_NULL);

            if (gpiod->pin < 0)
            {
                err = gpiod->pin;
                goto _fail;
            }

            if (rt_dm_dev_prop_read_u32_index(dev, "gpios-states", i, &val) < 0)
            {
                gpiod->flags = PIND_OUT_HIGH;
            }
            else
            {
                gpiod->flags = val ? PIND_OUT_HIGH : PIND_OUT_LOW;
            }

            if (gpiod->flags == PIND_OUT_HIGH)
            {
                rg->state |= 1 << i;
            }
        }
    }

    rg->states_nr = rt_dm_dev_prop_count_of_u32(dev, "states") / 2;

    if (rg->states_nr < 0)
    {
        err = -RT_EIO;

        goto _fail;
    }

    rg->states = rt_malloc(sizeof(*rg->states) * rg->states_nr);

    if (!rg->states)
    {
        err = -RT_ENOMEM;

        goto _fail;
    }

    for (int i = 0; i < rg->states_nr; ++i)
    {
        rt_dm_dev_prop_read_u32_index(dev, "states", i * 2, &rg->states[i].value);
        rt_dm_dev_prop_read_u32_index(dev, "states", i * 2 + 1, &rg->states[i].gpios);
    }

    if ((err = rt_regulator_register(rgp)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (rg->pins_desc)
    {
        rt_free(rg->pins_desc);
    }
    if (rg->states)
    {
        rt_free(rg->states);
    }
    rt_free(rg);

    return err;
}

static const struct rt_ofw_node_id regulator_gpio_ofw_ids[] =
{
    { .compatible = "regulator-gpio" },
    { /* sentinel */ }
};

static struct rt_platform_driver regulator_gpio_driver =
{
    .name = "regulator-gpio",
    .ids = regulator_gpio_ofw_ids,

    .probe = regulator_gpio_probe,
};

static int regulator_gpio_register(void)
{
    rt_platform_driver_register(&regulator_gpio_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(regulator_gpio_register);
