/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

struct gpio_desc
{
    rt_base_t pin;
    rt_uint8_t flags;
};

rt_packed(struct gpio_mapping
{
    rt_uint32_t limit_ua;
    rt_uint32_t gpiodata;
});

struct gpio_charger
{
    struct rt_power_supply parent;

    struct gpio_desc gpiod;
    struct gpio_desc charge_status;

    rt_ssize_t current_limit_gpios_nr;
    struct gpio_desc *current_limit_gpios;
    struct gpio_mapping *current_limit_map;

    rt_uint32_t current_limit_map_size;
    rt_uint32_t charge_current_limit;

    /* To be fill */
    enum rt_power_supply_property gpio_charger_properties[3];
};

static rt_err_t set_charge_current_limit(struct gpio_charger *gpioc, int val)
{
    int i;
    struct gpio_mapping mapping;
    struct gpio_desc *gpios = gpioc->current_limit_gpios;

    if (!gpioc->current_limit_map_size)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < gpioc->current_limit_map_size; i++)
    {
        if (gpioc->current_limit_map[i].limit_ua <= val)
        {
            break;
        }
    }
    mapping = gpioc->current_limit_map[i];

    for (i = 0; i < gpioc->current_limit_gpios_nr; i++)
    {
        rt_bool_t val = (mapping.gpiodata >> i) & 1;
        struct gpio_desc *gpio = &gpios[gpioc->current_limit_gpios_nr - i - 1];

        rt_pin_mode(gpio->pin, PIN_MODE_OUTPUT);
        rt_pin_write(gpio->pin, val ? gpio->flags : !gpio->flags);
    }

    gpioc->charge_current_limit = mapping.limit_ua;

    return RT_EOK;
}

static rt_err_t gpio_charger_get_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop, union rt_power_supply_property_val *val)
{
    struct gpio_charger *gpioc = rt_container_of(psy, struct gpio_charger, parent);

    switch (prop)
    {
    case RT_POWER_SUPPLY_PROP_ONLINE:
        rt_pin_mode(gpioc->gpiod.pin, PIN_MODE_INPUT);
        val->intval = rt_pin_read(gpioc->gpiod.pin) == gpioc->gpiod.flags;
        break;

    case RT_POWER_SUPPLY_PROP_STATUS:
        rt_pin_mode(gpioc->charge_status.pin, PIN_MODE_INPUT);
        if (rt_pin_read(gpioc->charge_status.pin) == gpioc->charge_status.flags)
        {
            val->intval = RT_POWER_SUPPLY_STATUS_CHARGING;
        }
        else
        {
            val->intval = RT_POWER_SUPPLY_STATUS_NOT_CHARGING;
        }
        break;

    case RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
        val->intval = gpioc->charge_current_limit;
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t gpio_charger_set_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop, const union rt_power_supply_property_val *val)
{
    struct gpio_charger *gpioc = rt_container_of(psy, struct gpio_charger, parent);

    switch (prop)
    {
    case RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
        return set_charge_current_limit(gpioc, val->intval);

    default:
        return -EINVAL;
    }

    return RT_EOK;
}

static const struct rt_power_supply_ops gpio_charger_ops =
{
    .get_property = gpio_charger_get_property,
    .set_property = gpio_charger_set_property,
};

static void gpio_charger_isr(void *args)
{
    struct gpio_charger *gpioc = args;

    rt_power_supply_changed(&gpioc->parent);
}

static rt_err_t init_charge_current_limit(struct rt_device *dev,
        struct gpio_charger *gpioc)
{
    rt_ssize_t len;
    rt_uint32_t cur_limit = RT_UINT32_MAX;

    gpioc->current_limit_gpios_nr = rt_pin_get_named_pin_count(dev, "charge-current-limit");
    if (gpioc->current_limit_gpios_nr <= 0)
    {
        return gpioc->current_limit_gpios_nr;
    }

    gpioc->current_limit_gpios = rt_malloc(gpioc->current_limit_gpios_nr *
            sizeof(*gpioc->current_limit_gpios));
    if (!gpioc->current_limit_gpios)
    {
        return RT_EOK;
    }

    len = rt_dm_dev_prop_count_of_u32(dev, "charge-current-limit-mapping");
    if (len < 0)
    {
        return len;
    }

    if (len == 0 || len % 2)
    {
        return -RT_EINVAL;
    }
    gpioc->current_limit_map_size = len / 2;

    gpioc->current_limit_map = rt_malloc(gpioc->current_limit_map_size *
            sizeof(*gpioc->current_limit_map));
    if (!gpioc->current_limit_map)
    {
        return -RT_ENOMEM;
    }

    len = rt_dm_dev_prop_read_u32_array_index(dev, "charge-current-limit-mapping",
            0, (int)len, (rt_uint32_t *)(void *)gpioc->current_limit_map);
    if (len < 0)
    {
        return len;
    }

    for (int i = 0; i < gpioc->current_limit_map_size; ++i)
    {
        if (gpioc->current_limit_map[i].limit_ua > cur_limit)
        {
            return -RT_EINVAL;
        }

        cur_limit = gpioc->current_limit_map[i].limit_ua;
    }

    /* Default to smallest current limitation for safety reasons */
    len = gpioc->current_limit_map_size - 1;
    set_charge_current_limit(gpioc, gpioc->current_limit_map[len].limit_ua);

    return RT_EOK;
}

static rt_err_t gpio_charger_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    int num_props = 0;
    const char *chargetype;
    struct gpio_charger *gpioc;
    struct rt_device *dev = &pdev->parent;

    gpioc = rt_calloc(1, sizeof(*gpioc));

    if (!gpioc)
    {
        return -RT_ENOMEM;
    }

    gpioc->gpiod.pin = rt_pin_get_named_pin(dev, RT_NULL, 0, RT_NULL, &gpioc->gpiod.flags);

    if (gpioc->gpiod.pin < 0 && gpioc->gpiod.pin != -RT_EEMPTY)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (gpioc->gpiod.pin >= 0)
    {
        gpioc->gpio_charger_properties[num_props] = RT_POWER_SUPPLY_PROP_ONLINE;
        ++num_props;
    }

    gpioc->charge_status.pin = rt_pin_get_named_pin(dev, "charge-status", 0,
            RT_NULL, &gpioc->charge_status.flags);

    if (gpioc->charge_status.pin < 0 && gpioc->charge_status.pin != -RT_EEMPTY)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (gpioc->charge_status.pin >= 0)
    {
        gpioc->gpio_charger_properties[num_props] = RT_POWER_SUPPLY_PROP_STATUS;
        ++num_props;
    }

    if ((err = init_charge_current_limit(dev, gpioc)))
    {
        goto _fail;
    }

    if (gpioc->current_limit_map)
    {
        gpioc->gpio_charger_properties[num_props] = RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX;
        ++num_props;
    }

    if (!rt_dm_dev_prop_read_string(dev, "charger-type", &chargetype))
    {
        if (!rt_strcmp("unknown", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_UNKNOWN;
        }
        else if (!rt_strcmp("battery", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_BATTERY;
        }
        else if (!rt_strcmp("ups", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_UPS;
        }
        else if (!rt_strcmp("mains", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_MAINS;
        }
        else if (!rt_strcmp("usb-sdp", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_USB_SDP;
        }
        else if (!rt_strcmp("usb-dcp", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_USB_DCP;
        }
        else if (!rt_strcmp("usb-cdp", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_USB_CDP;
        }
        else if (!rt_strcmp("usb-aca", chargetype))
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_USB_ACA;
        }
        else
        {
            gpioc->parent.type = RT_POWER_SUPPLY_TYPE_UNKNOWN;
        }
    }

    gpioc->parent.dev = dev,
    gpioc->parent.properties_nr = num_props,
    gpioc->parent.properties = gpioc->gpio_charger_properties,
    gpioc->parent.ops = &gpio_charger_ops;

    if ((err = rt_power_supply_register(&gpioc->parent)))
    {
        goto _fail;
    }

    rt_pin_mode(gpioc->gpiod.pin, PIN_MODE_INPUT);
    rt_pin_attach_irq(gpioc->gpiod.pin, PIN_IRQ_MODE_RISING, gpio_charger_isr, gpioc);
    rt_pin_irq_enable(gpioc->gpiod.pin, RT_TRUE);

    rt_pin_mode(gpioc->charge_status.pin, PIN_MODE_INPUT);
    rt_pin_attach_irq(gpioc->charge_status.pin, PIN_IRQ_MODE_RISING, gpio_charger_isr, gpioc);
    rt_pin_irq_enable(gpioc->charge_status.pin, RT_TRUE);

    return RT_EOK;
_fail:
    if (gpioc->current_limit_map)
    {
        rt_free(gpioc->current_limit_map);
    }
    if (gpioc->current_limit_gpios)
    {
        rt_free(gpioc->current_limit_gpios);
    }
    rt_free(gpioc);

    return err;
}

static const struct rt_ofw_node_id gpio_charger_ofw_ids[] =
{
    { .compatible = "gpio-charger" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_charger_driver =
{
    .name = "gpio-charger",
    .ids = gpio_charger_ofw_ids,

    .probe = gpio_charger_probe,
};
RT_PLATFORM_DRIVER_EXPORT(gpio_charger_driver);
