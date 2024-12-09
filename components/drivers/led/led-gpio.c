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

#define DBG_TAG "led.gpio"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct gpio_led
{
    struct rt_led_device parent;

    rt_base_t pin;
    rt_uint8_t active_val;
};

#define raw_to_gpio_led(raw) rt_container_of(raw, struct gpio_led, parent);

static rt_err_t gpio_led_set_state(struct rt_led_device *led, enum rt_led_state state)
{
    rt_err_t err = RT_EOK;
    struct gpio_led *gled = raw_to_gpio_led(led);

    rt_pin_mode(gled->pin, PIN_MODE_OUTPUT);

    switch (state)
    {
    case RT_LED_S_OFF:
        rt_pin_write(gled->pin, !gled->active_val);
        break;

    case RT_LED_S_ON:
        rt_pin_write(gled->pin, gled->active_val);
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

static rt_err_t gpio_led_get_state(struct rt_led_device *led, enum rt_led_state *out_state)
{
    struct gpio_led *gled = raw_to_gpio_led(led);

    switch (rt_pin_read(gled->pin))
    {
    case PIN_LOW:
        *out_state = RT_LED_S_OFF;
        break;

    case PIN_HIGH:
        *out_state = RT_LED_S_ON;
        break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

const static struct rt_led_ops gpio_led_ops =
{
    .set_state = gpio_led_set_state,
    .get_state = gpio_led_get_state,
};

static rt_err_t ofw_append_gpio_led(struct rt_ofw_node *np)
{
    rt_err_t err;
    enum rt_led_state led_state = RT_LED_S_OFF;
    const char *propname, *state, *trigger;
    struct gpio_led *gled = rt_malloc(sizeof(*gled));

    if (!gled)
    {
        return -RT_ENOMEM;
    }

    gled->pin = rt_ofw_get_named_pin(np, RT_NULL, 0, RT_NULL, &gled->active_val);

    if (gled->pin < 0)
    {
        err = gled->pin;

        goto _fail;
    }

    gled->parent.ops = &gpio_led_ops;

    if ((err = rt_hw_led_register(&gled->parent)))
    {
        goto _fail;
    }

    if (!rt_ofw_prop_read_string(np, "default-state", &state))
    {
        if (!rt_strcmp(state, "on"))
        {
            led_state = RT_LED_S_ON;
        }
    }

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

    rt_led_set_state(&gled->parent, led_state);

    rt_ofw_data(np) = &gled->parent;

    return RT_EOK;

_fail:
    rt_free(gled);

    return err;
}

static rt_err_t gpio_led_probe(struct rt_platform_device *pdev)
{
    rt_bool_t pinctrl_apply = RT_FALSE;
    struct rt_ofw_node *led_np, *np = pdev->parent.ofw_node;

    if (rt_ofw_prop_read_bool(np, "pinctrl-0"))
    {
        pinctrl_apply = RT_TRUE;
        rt_pin_ctrl_confs_apply_by_name(&pdev->parent, RT_NULL);
    }

    rt_ofw_foreach_available_child_node(np, led_np)
    {
        rt_err_t err = ofw_append_gpio_led(led_np);

        if (err == -RT_ENOMEM)
        {
            rt_ofw_node_put(led_np);

            return err;
        }
        else if (err)
        {
            LOG_E("%s: create LED fail", rt_ofw_node_full_name(led_np));
            continue;
        }

        if (!pinctrl_apply)
        {
            struct rt_device dev_tmp;

            dev_tmp.ofw_node = led_np;
            rt_pin_ctrl_confs_apply_by_name(&dev_tmp, RT_NULL);
        }
    }

    return RT_EOK;
}

static rt_err_t gpio_led_remove(struct rt_platform_device *pdev)
{
    struct gpio_led *gled;
    struct rt_led_device *led_dev;
    struct rt_ofw_node *led_np, *np = pdev->parent.ofw_node;

    rt_ofw_foreach_available_child_node(np, led_np)
    {
        led_dev = rt_ofw_data(led_np);

        if (!led_dev)
        {
            continue;
        }

        gled = rt_container_of(led_dev, struct gpio_led, parent);

        rt_ofw_data(led_np) = RT_NULL;

        rt_hw_led_unregister(&gled->parent);

        rt_free(gled);
    }

    return RT_EOK;
}

static const struct rt_ofw_node_id gpio_led_ofw_ids[] =
{
    { .compatible = "gpio-leds" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_led_driver =
{
    .name = "led-gpio",
    .ids = gpio_led_ofw_ids,

    .probe = gpio_led_probe,
    .remove = gpio_led_remove,
};
RT_PLATFORM_DRIVER_EXPORT(gpio_led_driver);
