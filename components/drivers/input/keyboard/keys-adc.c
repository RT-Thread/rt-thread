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

#define DBG_TAG "input.keyboard.adc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct adc_keys_button
{
    rt_uint32_t voltage;
    rt_uint32_t keycode;
};

struct adc_keys
{
    struct rt_input_device parent;
    struct rt_adc_device *adc_dev;

    int channel;
    rt_uint32_t num_keys;
    rt_uint32_t last_key;
    rt_uint32_t keyup_voltage;
    struct adc_keys_button kbtn[];
};

static void adc_keys_poll(struct rt_input_device *idev)
{
    int value, keycode = 0;
    rt_uint32_t diff, closest = 0xffffffff;
    struct adc_keys *tk = rt_container_of(idev, struct adc_keys, parent);

    value = rt_adc_read(tk->adc_dev, tk->channel);

    if (value < 0)
    {
        /* Forcibly release key if any was pressed */
        value = tk->keyup_voltage;
    }
    else
    {
        for (int i = 0; i < tk->num_keys; ++i)
        {
            rt_uint32_t sample = (rt_uint32_t)value;

            diff = tk->kbtn[i].voltage > sample ? tk->kbtn[i].voltage - sample : sample - tk->kbtn[i].voltage;

            if (diff < closest)
            {
                closest = diff;
                keycode = tk->kbtn[i].keycode;
            }
        }
    }

    if (value >= 0)
    {
        rt_uint32_t sample = (rt_uint32_t)value;
        rt_uint32_t keyup_diff = tk->keyup_voltage > sample ? tk->keyup_voltage - sample : sample - tk->keyup_voltage;

        if (keyup_diff < closest)
        {
            keycode = 0;
        }
    }

    if (tk->last_key && tk->last_key != keycode)
    {
        rt_input_report_key(&tk->parent, tk->last_key, 0);
    }

    if (keycode && tk->last_key != keycode)
    {
        rt_input_report_key(&tk->parent, keycode, 1);
    }

    if (tk->last_key != keycode)
    {
        rt_input_sync(&tk->parent);
    }

    tk->last_key = keycode;
}

static rt_err_t adc_key_probe(struct rt_platform_device *pdev)
{
    int i = 0;
    rt_err_t err;
    rt_uint32_t interval;
    rt_uint32_t num_keys;
    struct adc_keys *tk;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *key_np;

    num_keys = rt_ofw_get_child_count(np);

    if (!num_keys)
    {
        LOG_E("Keymap is missing");

        return -RT_EINVAL;
    }

    tk = rt_calloc(1, sizeof(*tk) + sizeof(struct adc_keys_button) * num_keys);

    if (!tk)
    {
        return -RT_ENOMEM;
    }

    tk->adc_dev = rt_iio_channel_get_by_name(dev, "buttons", &tk->channel);

    if (!tk->adc_dev)
    {
        LOG_E("ADC device not found");

        err = -RT_EINVAL;
        goto _fail;
    }

    rt_ofw_foreach_child_node(np, key_np)
    {
        const char *propname;

        if (rt_ofw_prop_read_u32(key_np, "press-threshold-microvolt",
                                 &tk->kbtn[i].voltage))
        {
            LOG_E("%s: Key with invalid or missing %s",
                  rt_ofw_node_full_name(key_np), "press-threshold-microvolt");
            rt_ofw_node_put(key_np);

            err = -RT_EINVAL;
            goto _fail;
        }

        tk->kbtn[i].voltage /= 1000;

        if (!(propname = rt_ofw_get_prop_fuzzy_name(key_np, ",code$")) ||
            rt_ofw_prop_read_u32(key_np, propname, &tk->kbtn[i].keycode))
        {
            LOG_E("%s: Key with invalid or missing %s",
                  rt_ofw_node_full_name(key_np), "*,code");
            rt_ofw_node_put(key_np);

            err = -RT_EINVAL;
            goto _fail;
        }

        rt_input_set_capability(&tk->parent, EV_KEY, tk->kbtn[i].keycode);

        ++i;
    }

    tk->num_keys = num_keys;

    if (rt_ofw_prop_read_u32(np, "keyup-threshold-microvolt", &tk->keyup_voltage))
    {
        LOG_E("Invalid or missing keyup voltage");

        err = -RT_EINVAL;
        goto _fail;
    }

    tk->keyup_voltage /= 1000;

    if (rt_ofw_prop_read_u32(np, "poll-interval", &interval))
    {
        interval = 200;
    }

    if ((err = rt_input_setup_polling(&tk->parent, adc_keys_poll)))
    {
        goto _fail;
    }

    rt_input_set_poll_interval(&tk->parent, interval);

    if ((err = rt_input_device_register(&tk->parent)))
    {
        goto _fail;
    }

    dev->user_data = tk;

    return RT_EOK;

_fail:
    rt_input_remove_config(&tk->parent);
    rt_free(tk);

    return err;
}

static rt_err_t adc_key_remove(struct rt_platform_device *pdev)
{
    struct adc_keys *tk = pdev->parent.user_data;

    pdev->parent.user_data = RT_NULL;
    rt_input_device_unregister(&tk->parent);

    rt_free(tk);

    return RT_EOK;
}

static const struct rt_ofw_node_id adc_key_ofw_ids[] = {
    { .compatible = "adc-keys" },
    { /* sentinel */ }
};

static struct rt_platform_driver adc_key_driver = {
    .name = "adc-keys",
    .ids = adc_key_ofw_ids,

    .probe = adc_key_probe,
    .remove = adc_key_remove,
};
RT_PLATFORM_DRIVER_EXPORT(adc_key_driver);
