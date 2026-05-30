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

#define DBG_TAG "led.pwm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct pwm_led
{
    struct rt_led_device parent;

    struct rt_device_pwm *pwm_dev;
    struct rt_pwm_configuration pwm_conf;

    rt_uint32_t max_brightness;
    rt_uint32_t brightness;
    rt_bool_t active_low;
    rt_bool_t enabled;
};

#define raw_to_pwm_led(raw) rt_container_of(raw, struct pwm_led, parent)

static rt_err_t pwm_led_set_state(struct rt_led_device *led, enum rt_led_state state)
{
    rt_err_t err = RT_EOK;
    struct rt_pwm_configuration pwm_conf = {};
    struct pwm_led *pled = raw_to_pwm_led(led);

    switch (state)
    {
    case RT_LED_S_OFF:
        if ((err = rt_pwm_set(pled->pwm_dev,
                pled->pwm_conf.channel, pled->pwm_conf.period, 0)))
        {
            break;
        }

        if (!(err = rt_pwm_disable(pled->pwm_dev, pled->pwm_conf.channel)))
        {
            pled->enabled = RT_FALSE;
        }
        break;

    case RT_LED_S_ON:
        pwm_conf.channel = pled->pwm_conf.channel;
        pwm_conf.period = pled->pwm_conf.period;
        pwm_conf.pulse = pled->pwm_conf.pulse;
        pwm_conf.complementary = pled->active_low;

        if ((err = rt_device_control(&pled->pwm_dev->parent, PWM_CMD_SET, &pwm_conf)))
        {
            break;
        }

        if (!(err = rt_pwm_enable(pled->pwm_dev, pled->pwm_conf.channel)))
        {
            pled->enabled = RT_TRUE;
        }
        break;

    case RT_LED_S_TOGGLE:
        err = led->ops->get_state(led, &state);

        if (!err)
        {
            err = led->ops->set_state(led, state == RT_LED_S_OFF ? RT_LED_S_ON : RT_LED_S_OFF);
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return err;
}

static rt_err_t pwm_led_get_state(struct rt_led_device *led, enum rt_led_state *out_state)
{
    struct pwm_led *pled = raw_to_pwm_led(led);

    *out_state = pled->enabled ? RT_LED_S_ON : RT_LED_S_OFF;

    return RT_EOK;
}

static rt_err_t pwm_led_set_brightness(struct rt_led_device *led, rt_uint32_t brightness)
{
    struct pwm_led *pled = raw_to_pwm_led(led);
    rt_uint64_t duty = pled->pwm_conf.period;

    duty *= brightness;
    rt_do_div(duty, pled->max_brightness);

    if (pled->active_low)
    {
        duty = pled->pwm_conf.period - duty;
    }

    pled->pwm_conf.pulse = duty;

    return rt_pwm_set(pled->pwm_dev,
            pled->pwm_conf.channel, pled->pwm_conf.period, pled->pwm_conf.pulse);
}

const static struct rt_led_ops pwm_led_ops =
{
    .set_state = pwm_led_set_state,
    .get_state = pwm_led_get_state,
    .set_brightness = pwm_led_set_brightness,
};

static rt_err_t ofw_append_pwm_led(struct rt_ofw_node *np)
{
    rt_err_t err;
    rt_bool_t need_set_brightness = RT_TRUE;
    enum rt_led_state led_state = RT_LED_S_OFF;
    const char *propname, *state, *trigger;
    struct rt_ofw_node *pwm_np;
    struct rt_ofw_cell_args pwm_args;
    struct pwm_led *pled = rt_calloc(1, sizeof(*pled));

    if (!pled)
    {
        return -RT_ENOMEM;
    }

    pled->active_low = rt_ofw_prop_read_bool(np, "active-low");

    if (rt_ofw_prop_read_u32(np, "max-brightness", &pled->max_brightness))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (rt_ofw_parse_phandle_cells(np, "pwms", "#pwm-cells", 0, &pwm_args))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pwm_np = pwm_args.data;

    if (!rt_ofw_data(pwm_np))
    {
        rt_platform_ofw_request(pwm_np);
    }

    pled->pwm_dev = rt_ofw_data(pwm_np);
    rt_ofw_node_put(pwm_np);

    if (!pled->pwm_dev)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pled->pwm_conf.channel = pwm_args.args[0];
    pled->pwm_conf.period = pwm_args.args[1];

    pled->parent.ops = &pwm_led_ops;

    if ((err = rt_led_register(&pled->parent)))
    {
        goto _fail;
    }

    if (!rt_ofw_prop_read_string(np, "default-state", &state))
    {
        rt_pwm_get(pled->pwm_dev, &pled->pwm_conf);

        if (!rt_strcmp(state, "on"))
        {
            led_state = RT_LED_S_ON;
            pled->brightness = pled->max_brightness;
        }
        else if (!rt_strcmp(state, "keep"))
        {
            if (pled->pwm_conf.period)
            {
                rt_uint64_t brightness;

                brightness = pled->max_brightness;
                brightness *= pled->pwm_conf.pulse;
                rt_do_div(brightness, pled->pwm_conf.period);

                pled->brightness = brightness;

                need_set_brightness = RT_FALSE;
            }
            else
            {
                goto _out_state_check;
            }
        }

        pled->pwm_conf.period = pwm_args.args[1];
    }

_out_state_check:
    if ((propname = rt_ofw_get_prop_fuzzy_name(np, "default-trigger$")))
    {
        if (!rt_ofw_prop_read_string(np, propname, &trigger))
        {
            if (!rt_strcmp(trigger, "heartbeat") ||
                !rt_strcmp(trigger, "timer"))
            {
                led_state = RT_LED_S_BLINK;
            }
        }
    }

    rt_led_set_state(&pled->parent, led_state);

    if (need_set_brightness)
    {
        pwm_led_set_brightness(&pled->parent, pled->brightness);
    }

    rt_ofw_data(np) = &pled->parent;

    return RT_EOK;

_fail:
    rt_free(pled);

    return err;
}

static rt_err_t pwm_led_probe(struct rt_platform_device *pdev)
{
    struct rt_ofw_node *led_np, *np = pdev->parent.ofw_node;

    rt_ofw_foreach_available_child_node(np, led_np)
    {
        rt_err_t err = ofw_append_pwm_led(led_np);

        if (err == -RT_ENOMEM)
        {
            rt_ofw_node_put(led_np);

            return err;
        }
        else if (err)
        {
            LOG_E("%s: create LED fail", rt_ofw_node_full_name(led_np));
        }
    }

    return RT_EOK;
}

static rt_err_t pwm_led_remove(struct rt_platform_device *pdev)
{
    struct pwm_led *pled;
    struct rt_led_device *led_dev;
    struct rt_ofw_node *led_np, *np = pdev->parent.ofw_node;

    rt_ofw_foreach_available_child_node(np, led_np)
    {
        led_dev = rt_ofw_data(led_np);

        if (!led_dev)
        {
            continue;
        }

        pled = rt_container_of(led_dev, struct pwm_led, parent);

        rt_ofw_data(led_np) = RT_NULL;

        rt_led_unregister(&pled->parent);

        rt_free(pled);
    }

    return RT_EOK;
}

static const struct rt_ofw_node_id pwm_led_ofw_ids[] =
{
    { .compatible = "pwm-leds" },
    { /* sentinel */ }
};

static struct rt_platform_driver pwm_led_driver =
{
    .name = "led-pwm",
    .ids = pwm_led_ofw_ids,

    .probe = pwm_led_probe,
    .remove = pwm_led_remove,
};
RT_PLATFORM_DRIVER_EXPORT(pwm_led_driver);
