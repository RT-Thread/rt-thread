/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <dt-bindings/pin/pin.h>

#include "dev_pin_dm.h"

static const char * const gpio_suffixes[] =
{
    "gpios", "gpio"
};

rt_ssize_t rt_ofw_get_named_pin(struct rt_ofw_node *np, const char *propname, int index,
        rt_uint8_t *out_mode, rt_uint8_t *out_value)
{
    rt_ssize_t pin = -1;
    rt_uint8_t mode;
    rt_uint8_t value;
    rt_uint32_t flags;
    char gpios_name[64];
    struct rt_device_pin *pin_dev = 0;
    struct rt_ofw_node *pin_dev_np = 0;
    struct rt_ofw_cell_args pin_args = {0};

    if (!np && index < 0)
    {
        return -RT_EINVAL;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(gpio_suffixes); ++i)
    {
        if (propname)
        {
            rt_snprintf(gpios_name, sizeof(gpios_name), "%s-%s", propname, gpio_suffixes[i]);
        }
        else
        {
            rt_snprintf(gpios_name, sizeof(gpios_name), "%s", gpio_suffixes[i]);
        }

        pin = rt_ofw_parse_phandle_cells(np, gpios_name, "#gpio-cells", index, &pin_args);

        if (pin >= 0)
        {
            break;
        }
    }

    if (pin < 0)
    {
        return pin;
    }

    pin_dev_np = pin_args.data;

    if (!rt_ofw_data(pin_dev_np))
    {
        rt_platform_ofw_request(pin_dev_np);
    }

    pin_dev = rt_ofw_data(pin_dev_np);

    if (!pin_dev)
    {
        pin = -RT_ERROR;

        goto _out_converts;
    }

    value = PIN_LOW;
    mode = PIN_MODE_OUTPUT;

    if (pin_dev->ops->pin_parse)
    {
        pin = pin_dev->ops->pin_parse(&pin_dev->parent, &pin_args, &flags);
    }
    else
    {
        /*
         * We always assume that the args[0] is the pin number if driver not
         * implemented `pin_parse`.
         */
        pin = pin_args.args[0];

        goto _out_converts;
    }

    if (out_mode)
    {
        if (flags & PIN_OPEN_DRAIN)
        {
            mode = PIN_MODE_OUTPUT_OD;
        }

        switch (flags & RT_GENMASK(6, 4))
        {
        case PIN_PULL_UP:
            mode = PIN_MODE_INPUT_PULLUP;
            break;

        case PIN_PULL_DOWN:
            mode = PIN_MODE_INPUT_PULLDOWN;
            break;

        case PIN_PULL_DISABLE:
            mode = PIN_MODE_INPUT;
            break;
        }
    }

    if (out_value)
    {
        if ((flags & 1) == PIN_ACTIVE_HIGH)
        {
            value = PIN_HIGH;
        }
        else if ((flags & 1) == PIN_ACTIVE_LOW)
        {
            value = PIN_LOW;
        }
    }

_out_converts:
    rt_ofw_node_put(pin_dev_np);

    if (pin >= 0)
    {
        /* Get virtual pin */
        pin += pin_dev->pin_start;

        if (out_mode)
        {
            *out_mode = mode;
        }

        if (out_value)
        {
            *out_value = value;
        }
    }

    return pin;
}

rt_ssize_t rt_ofw_get_named_pin_count(struct rt_ofw_node *np, const char *propname)
{
    char gpios_name[64];
    rt_ssize_t count = 0;

    if (!np)
    {
        return -RT_EINVAL;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(gpio_suffixes); ++i)
    {
        if (propname)
        {
            rt_snprintf(gpios_name, sizeof(gpios_name), "%s-%s", propname, gpio_suffixes[i]);
        }
        else
        {
            rt_snprintf(gpios_name, sizeof(gpios_name), "%s", gpio_suffixes[i]);
        }

        count = rt_ofw_count_phandle_cells(np, propname, "#gpio-cells");

        if (count > 0)
        {
            break;
        }
    }

    return count;
}
