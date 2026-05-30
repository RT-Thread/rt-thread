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

#define DBG_TAG "led.syscon"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct syscon_led
{
    struct rt_led_device parent;

    struct rt_syscon *map;
    rt_uint32_t offset;
    rt_uint32_t mask;
};

#define raw_to_syscon_led(raw) rt_container_of(raw, struct syscon_led, parent)

static rt_err_t syscon_led_set_state(struct rt_led_device *led, enum rt_led_state state)
{
    rt_err_t err = RT_EOK;
    struct syscon_led *sled = raw_to_syscon_led(led);

    switch (state)
    {
    case RT_LED_S_OFF:
        err = rt_syscon_update_bits(sled->map, sled->offset, sled->mask, 0);
        break;

    case RT_LED_S_ON:
        err = rt_syscon_update_bits(sled->map, sled->offset, sled->mask, sled->mask);
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

static rt_err_t syscon_led_get_state(struct rt_led_device *led, enum rt_led_state *out_state)
{
    rt_err_t err;
    rt_uint32_t val;
    struct syscon_led *sled = raw_to_syscon_led(led);

    if (!(err = rt_syscon_read(sled->map, sled->offset, &val)))
    {
        if ((val & ~sled->mask))
        {
            *out_state = RT_LED_S_ON;
        }
        else
        {
            *out_state = RT_LED_S_OFF;
        }
    }

    return err;
}

const static struct rt_led_ops syscon_led_ops =
{
    .set_state = syscon_led_set_state,
    .get_state = syscon_led_get_state,
};

static rt_err_t syscon_led_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *propname, *state, *trigger;
    enum rt_led_state led_state = RT_LED_S_OFF;
    struct rt_ofw_node *np = pdev->parent.ofw_node, *pnp;
    struct syscon_led *sled = rt_calloc(1, sizeof(*sled));

    if (!sled)
    {
        return -RT_ENOMEM;
    }

    if (!(pnp = rt_ofw_get_parent(np)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if ((err = rt_ofw_prop_read_u32(np, "offset", &sled->offset)) ||
        (err = rt_ofw_prop_read_u32(np, "mask", &sled->mask)))
    {
        rt_ofw_node_put(pnp);
        goto _fail;
    }

    sled->map = rt_syscon_find_by_ofw_node(pnp);
    rt_ofw_node_put(pnp);

    if (!sled->map)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pdev->parent.user_data = sled;

    sled->parent.ops = &syscon_led_ops;

    if ((err = rt_led_register(&sled->parent)))
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

    rt_led_set_state(&sled->parent, led_state);

    return RT_EOK;

_fail:
    rt_free(sled);

    return err;
}

static rt_err_t syscon_led_remove(struct rt_platform_device *pdev)
{
    struct syscon_led *sled = pdev->parent.user_data;

    rt_led_unregister(&sled->parent);

    rt_free(sled);

    return RT_EOK;
}

static const struct rt_ofw_node_id syscon_led_ofw_ids[] =
{
    { .compatible = "register-bit-led" },
    { /* sentinel */ }
};

static struct rt_platform_driver syscon_led_driver =
{
    .name = "leds-syscon",
    .ids = syscon_led_ofw_ids,

    .probe = syscon_led_probe,
    .remove = syscon_led_remove,
};
RT_PLATFORM_DRIVER_EXPORT(syscon_led_driver);
