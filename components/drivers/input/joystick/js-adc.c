/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "input.js.adc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct adc_joystick_axis
{
    rt_uint32_t code;
    rt_uint32_t range[2];
    rt_uint32_t fuzz;
    rt_uint32_t flat;
    rt_uint32_t channel;
    rt_uint32_t inverted;

    struct rt_adc_device *adc_dev;
};

struct adc_joysticks
{
    struct rt_input_device parent;

    rt_uint32_t num_axis;
    struct adc_joystick_axis axis[];
};

static void adc_joysticks_poll(struct rt_input_device *idev)
{
    int value;
    struct adc_joysticks *aj = rt_container_of(idev, struct adc_joysticks, parent);

    for (int i = 0; i < aj->num_axis; ++i)
    {
        struct adc_joystick_axis *axis = &aj->axis[i];

        value = rt_adc_read(axis->adc_dev, axis->channel);
        if (value < 0)
        {
            return;
        }

        if (axis->inverted)
        {
            value = (int)(axis->range[0] + axis->range[1]) - value;
        }

        rt_input_report_abs(&aj->parent, axis->code, value);
    }

    rt_input_sync(&aj->parent);
}

static rt_err_t adc_joystick_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t interval;
    rt_uint32_t num_axis;
    struct adc_joysticks *aj;
    struct adc_joystick_axis *axis;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *axis_np;

    num_axis = rt_ofw_get_child_count(np);

    if (!num_axis)
    {
        LOG_E("Keymap is missing");

        return -RT_EINVAL;
    }

    aj = rt_calloc(1, sizeof(*aj) + sizeof(struct adc_joystick_axis) * num_axis);

    if (!aj)
    {
        return -RT_ENOMEM;
    }

    rt_ofw_foreach_child_node(np, axis_np)
    {
        rt_uint32_t reg;
        const char *propname;

        if (rt_ofw_prop_read_u32(axis_np, "reg", &reg))
        {
            err = -RT_EINVAL;
            rt_ofw_node_put(axis_np);
            goto _fail;
        }

        if (reg >= num_axis)
        {
            LOG_E("%s: reg %u out of range (num_axis %u)",
                  rt_ofw_node_full_name(axis_np), reg, num_axis);
            rt_ofw_node_put(axis_np);
            err = -RT_EINVAL;
            goto _fail;
        }

        axis = &aj->axis[reg];

        if (axis->adc_dev)
        {
            LOG_E("%s: duplicate reg %u", rt_ofw_node_full_name(axis_np), reg);
            rt_ofw_node_put(axis_np);
            err = -RT_EINVAL;
            goto _fail;
        }

        axis->adc_dev = rt_iio_channel_get_by_index(dev, reg, &axis->channel);

        if (!axis->adc_dev)
        {
            rt_ofw_node_put(axis_np);

            LOG_E("ADC device not found");
            err = -RT_EINVAL;
            goto _fail;
        }

        if (rt_ofw_prop_read_u32(axis_np, "abs-flat", &axis->flat))
        {
            axis->flat = 0;
        }

        if (rt_ofw_prop_read_u32(axis_np, "abs-fuzz", &axis->fuzz))
        {
            axis->fuzz = 0;
        }

        if (rt_ofw_prop_read_u32_array_index(axis_np, "abs-range", 0, 2, axis->range))
        {
            LOG_E("%s: Axis[%d] missing %s", rt_ofw_node_full_name(axis_np), reg, "abs-range");
            rt_ofw_node_put(axis_np);
            err = -RT_EINVAL;
            goto _fail;
        }

        axis->inverted = 0;
        if (axis->range[0] > axis->range[1])
        {
            rt_uint32_t t = axis->range[0];

            axis->range[0] = axis->range[1];
            axis->range[1] = t;
            axis->inverted = 1;
        }

        if (!(propname = rt_ofw_get_prop_fuzzy_name(axis_np, ",code$")) ||
            rt_ofw_prop_read_u32(axis_np, propname, &axis->code))
        {
            LOG_E("%s: Axis[%d] missing %s", rt_ofw_node_full_name(axis_np), reg, "*,code");
            rt_ofw_node_put(axis_np);
            err = -RT_EINVAL;
            goto _fail;
        }

        rt_input_set_absinfo(&aj->parent, axis->code,
                             axis->range[0], axis->range[1], axis->fuzz, axis->flat);
        rt_input_set_capability(&aj->parent, EV_ABS, axis->code);
    }

    for (int i = 0; i < num_axis; ++i)
    {
        if (!aj->axis[i].adc_dev)
        {
            LOG_E("Axis[%d] is missing", i);
            err = -RT_EINVAL;
            goto _fail;
        }
    }

    aj->num_axis = num_axis;

    if (rt_ofw_prop_read_u32(np, "poll-interval", &interval))
    {
        interval = 200;
    }

    if ((err = rt_input_setup_polling(&aj->parent, adc_joysticks_poll)))
    {
        goto _fail;
    }

    rt_input_set_poll_interval(&aj->parent, interval);

    if ((err = rt_input_device_register(&aj->parent)))
    {
        goto _fail;
    }

    dev->user_data = aj;

    return RT_EOK;

_fail:
    rt_input_remove_config(&aj->parent);
    rt_free(aj);

    return err;
}

static rt_err_t adc_joystick_remove(struct rt_platform_device *pdev)
{
    struct adc_joysticks *aj = pdev->parent.user_data;

    pdev->parent.user_data = RT_NULL;
    rt_input_device_unregister(&aj->parent);

    rt_free(aj);

    return RT_EOK;
}

static const struct rt_ofw_node_id adc_joystick_ofw_ids[] = {
    { .compatible = "adc-joystick" },
    { /* sentinel */ }
};

static struct rt_platform_driver adc_joystick_driver = {
    .name = "adc-joystick",
    .ids = adc_joystick_ofw_ids,

    .probe = adc_joystick_probe,
    .remove = adc_joystick_remove,
};
RT_PLATFORM_DRIVER_EXPORT(adc_joystick_driver);
