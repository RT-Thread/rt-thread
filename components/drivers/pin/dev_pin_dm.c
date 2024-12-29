/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "dev_pin_dm.h"

static rt_size_t pin_total_nr = 0;
static struct rt_spinlock pin_lock = {};
static rt_list_t pin_nodes = RT_LIST_OBJECT_INIT(pin_nodes);

static struct rt_device_pin *pin_device_find(rt_ubase_t pin)
{
    struct rt_device_pin *gpio = RT_NULL, *gpio_tmp;

    rt_spin_lock(&pin_lock);

    rt_list_for_each_entry(gpio_tmp, &pin_nodes, list)
    {
        if (pin >= gpio_tmp->pin_start &&
            pin - gpio_tmp->pin_start < gpio_tmp->pin_nr)
        {
            gpio = gpio_tmp;
            break;
        }
    }

    rt_spin_unlock(&pin_lock);

    return gpio;
}

static void pin_api_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio && gpio->ops->pin_mode)
    {
        gpio->ops->pin_mode(&gpio->parent, pin - gpio->pin_start, mode);
    }
}

static void pin_api_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio && gpio->ops->pin_write)
    {
        gpio->ops->pin_write(&gpio->parent, pin - gpio->pin_start, value);
    }
}

static rt_ssize_t pin_api_read(struct rt_device *device, rt_base_t pin)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio && gpio->ops->pin_read)
    {
        return gpio->ops->pin_read(&gpio->parent, pin - gpio->pin_start);
    }

    return -RT_EINVAL;
}

static rt_err_t pin_api_attach_irq(struct rt_device *device, rt_base_t pin,
        rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio)
    {
        rt_base_t pin_index = pin - gpio->pin_start;

        if (!gpio->ops->pin_attach_irq)
        {
            rt_err_t err;
            struct rt_pin_irq_hdr *legacy_isr;

            if ((err = gpio->ops->pin_irq_mode(&gpio->parent, pin_index, mode)))
            {
                return err;
            }

            legacy_isr = &gpio->legacy_isr[pin_index];
            legacy_isr->pin = pin_index;
            legacy_isr->mode = mode;
            legacy_isr->hdr = hdr;
            legacy_isr->args = args;

            return RT_EOK;
        }
        else
        {
            return gpio->ops->pin_attach_irq(&gpio->parent, pin_index, mode, hdr, args);
        }
    }

    return -RT_EINVAL;
}

static rt_err_t pin_api_detach_irq(struct rt_device *device, rt_base_t pin)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio)
    {
        rt_base_t pin_index = pin - gpio->pin_start;

        if (!gpio->ops->pin_detach_irq)
        {
            struct rt_pin_irq_hdr *legacy_isr;

            legacy_isr = &gpio->legacy_isr[pin_index];
            rt_memset(legacy_isr, 0, sizeof(*legacy_isr));

            return RT_EOK;
        }
        else
        {
            return gpio->ops->pin_detach_irq(&gpio->parent, pin);
        }
    }

    return -RT_EINVAL;
}

static rt_err_t pin_api_irq_enable(struct rt_device *device, rt_base_t pin,
        rt_uint8_t enabled)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio && gpio->ops->pin_irq_enable)
    {
        return gpio->ops->pin_irq_enable(&gpio->parent, pin - gpio->pin_start, enabled);
    }

    return -RT_EINVAL;
}

static rt_base_t pin_api_get(const char *name)
{
    rt_base_t res = -RT_EINVAL;
    struct rt_device_pin *gpio;

    rt_spin_lock(&pin_lock);

    rt_list_for_each_entry(gpio, &pin_nodes, list)
    {
        if (gpio->ops->pin_get && !(res = gpio->ops->pin_get(name)))
        {
            break;
        }
    }

    rt_spin_unlock(&pin_lock);

    return res;
}

static rt_err_t pin_api_debounce(struct rt_device *device, rt_base_t pin,
        rt_uint32_t debounce)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio && gpio->ops->pin_debounce)
    {
        return gpio->ops->pin_debounce(&gpio->parent, pin - gpio->pin_start, debounce);
    }

    return -RT_EINVAL;
}

static rt_err_t pin_api_irq_mode(struct rt_device *device, rt_base_t pin,
        rt_uint8_t mode)
{
    struct rt_device_pin *gpio = pin_device_find(pin);

    if (gpio && gpio->ops->pin_irq_mode)
    {
        return gpio->ops->pin_irq_mode(&gpio->parent, pin - gpio->pin_start, mode);
    }

    return -RT_EINVAL;
}

static const struct rt_pin_ops pin_api_dm_ops =
{
    .pin_mode = pin_api_mode,
    .pin_write = pin_api_write,
    .pin_read = pin_api_read,
    .pin_attach_irq = pin_api_attach_irq,
    .pin_detach_irq = pin_api_detach_irq,
    .pin_irq_enable = pin_api_irq_enable,
    .pin_get = pin_api_get,
    .pin_debounce = pin_api_debounce,
    .pin_irq_mode = pin_api_irq_mode,
};

rt_err_t pin_api_init(struct rt_device_pin *gpio, rt_size_t pin_nr)
{
    rt_err_t err = RT_EOK;

    if (!gpio || !gpio->ops)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&pin_lock);

    if (rt_list_isempty(&pin_nodes))
    {
        rt_spin_unlock(&pin_lock);
        rt_device_pin_register("gpio", &pin_api_dm_ops, RT_NULL);
        rt_spin_lock(&pin_lock);
    }

    gpio->pin_start = pin_total_nr;
    gpio->pin_nr = pin_nr;
    pin_total_nr += pin_nr;

    rt_list_init(&gpio->list);
    rt_list_insert_before(&pin_nodes, &gpio->list);

    rt_spin_unlock(&pin_lock);

    return err;
}

static void pin_dm_irq_mask(struct rt_pic_irq *pirq)
{
    struct rt_device_pin *gpio = pirq->pic->priv_data;

    gpio->ops->pin_irq_enable(&gpio->parent, pirq->hwirq, 0);
}

static void pin_dm_irq_unmask(struct rt_pic_irq *pirq)
{
    struct rt_device_pin *gpio = pirq->pic->priv_data;

    gpio->ops->pin_irq_enable(&gpio->parent, pirq->hwirq, 1);
}

static rt_err_t pin_dm_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    rt_uint8_t pin_mode;
    struct rt_device_pin *gpio = pirq->pic->priv_data;

    switch (mode)
    {
    case RT_IRQ_MODE_EDGE_RISING:
        pin_mode = PIN_IRQ_MODE_RISING;
        break;

    case RT_IRQ_MODE_EDGE_FALLING:
        pin_mode = PIN_IRQ_MODE_FALLING;
        break;

    case RT_IRQ_MODE_EDGE_BOTH:
        pin_mode = PIN_IRQ_MODE_RISING_FALLING;
        break;

    case RT_IRQ_MODE_LEVEL_HIGH:
        pin_mode = PIN_IRQ_MODE_HIGH_LEVEL;
        break;

    case RT_IRQ_MODE_LEVEL_LOW:
        pin_mode = PIN_IRQ_MODE_LOW_LEVEL;
        break;

    default:
        return -RT_ENOSYS;
    }

    return gpio->ops->pin_irq_mode(&gpio->parent, pirq->hwirq, pin_mode);
}

static int pin_dm_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq = -1;
    struct rt_device_pin *gpio = pic->priv_data;
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    if (pirq)
    {
        irq = rt_pic_config_irq(pic, hwirq, hwirq);

        if (irq >= 0)
        {
            rt_pic_cascade(pirq, gpio->irqchip.irq);
            rt_pic_irq_set_triger_mode(irq, mode);
        }
    }

    return irq;
}

static rt_err_t pin_dm_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 2)
    {
        out_pirq->hwirq = args->args[0];
        out_pirq->mode = args->args[1] & RT_IRQ_MODE_MASK;
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

const static struct rt_pic_ops pin_dm_ops =
{
    .name = "GPIO",
    .irq_enable = pin_dm_irq_mask,
    .irq_disable = pin_dm_irq_unmask,
    .irq_mask = pin_dm_irq_mask,
    .irq_unmask = pin_dm_irq_unmask,
    .irq_set_triger_mode = pin_dm_irq_set_triger_mode,
    .irq_map = pin_dm_irq_map,
    .irq_parse = pin_dm_irq_parse,
};

rt_err_t pin_pic_handle_isr(struct rt_device_pin *gpio, rt_base_t pin)
{
    rt_err_t err;

    if (gpio)
    {
        rt_ubase_t pin_index = pin;
        struct rt_pin_irqchip *irqchip = &gpio->irqchip;

        if (pin_index < gpio->pin_nr)
        {
            struct rt_pic_irq *pirq;
            struct rt_pin_irq_hdr *legacy_isr;

            pirq = rt_pic_find_irq(&irqchip->parent, pin_index);

            if (pirq->irq >= 0)
            {
                err = rt_pic_handle_isr(pirq);
            }
            else
            {
                err = -RT_EINVAL;
            }

            legacy_isr = &gpio->legacy_isr[pin_index];

            if (legacy_isr->hdr)
            {
                legacy_isr->hdr(legacy_isr->args);
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t pin_pic_init(struct rt_device_pin *gpio, int pin_irq)
{
    rt_err_t err;

    if (gpio)
    {
        struct rt_pin_irqchip *irqchip = &gpio->irqchip;
        struct rt_pic *pic = &irqchip->parent;

        irqchip->irq = pin_irq;

        if (!gpio->pin_nr)
        {
            return -RT_EINVAL;
        }

        gpio->legacy_isr = rt_calloc(gpio->pin_nr, sizeof(*gpio->legacy_isr));

        if (!gpio->legacy_isr)
        {
            return -RT_ENOMEM;
        }

        pic->priv_data = gpio;
        pic->ops = &pin_dm_ops;
        /* Make sure the type of gpio for pic */
        gpio->parent.parent.type = RT_Object_Class_Device;
        rt_pic_default_name(&irqchip->parent);

        err = rt_pic_linear_irq(pic, gpio->pin_nr);
        rt_pic_user_extends(pic);

        err = RT_EOK;
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_ssize_t rt_pin_get_named_pin(struct rt_device *dev, const char *propname, int index,
        rt_uint8_t *out_mode, rt_uint8_t *out_value)
{
    rt_ssize_t res = -RT_ENOSYS;

    RT_ASSERT(dev != RT_NULL);

#ifdef RT_USING_OFW
    if (dev->ofw_node)
    {
        res = rt_ofw_get_named_pin(dev->ofw_node, propname, index, out_mode, out_value);
    }
    else
    {
        res = -RT_EINVAL;
    }
#endif /* RT_USING_OFW */

    return res;
}

rt_ssize_t rt_pin_get_named_pin_count(struct rt_device *dev, const char *propname)
{
    rt_ssize_t count = -RT_ENOSYS;

    RT_ASSERT(dev != RT_NULL);

#ifdef RT_USING_OFW
    if (dev->ofw_node)
    {
        count = rt_ofw_get_named_pin_count(dev->ofw_node, propname);
    }
    else
    {
        count = -RT_EINVAL;
    }
#endif /* RT_USING_OFW */

    return count;
}
