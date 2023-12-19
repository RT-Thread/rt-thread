/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "pin_dm.h"

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

static rt_err_t pin_dm_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
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

static struct rt_pic_ops pin_dm_ops =
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
        struct rt_pin_irqchip *irqchip = &gpio->irqchip;

        if (pin >= irqchip->pin_range[0] && pin <= irqchip->pin_range[1])
        {
            struct rt_pic_irq *pirq;

            pirq = rt_pic_find_irq(&irqchip->parent, pin - irqchip->pin_range[0]);

            if (pirq->irq >= 0)
            {
                err = rt_pic_handle_isr(pirq);
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
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t pin_pic_init(struct rt_device_pin *gpio)
{
    rt_err_t err;

    if (gpio)
    {
        struct rt_pin_irqchip *irqchip = &gpio->irqchip;

        if (irqchip->pin_range[0] >= 0 && irqchip->pin_range[1] >= irqchip->pin_range[0])
        {
            struct rt_pic *pic = &irqchip->parent;
            rt_size_t pin_nr = irqchip->pin_range[1] - irqchip->pin_range[0] + 1;

            pic->priv_data = gpio;
            pic->ops = &pin_dm_ops;
            /* Make sure the type of gpio for pic */
            gpio->parent.parent.type = RT_Object_Class_Device;
            rt_pic_default_name(&irqchip->parent);

            err = rt_pic_linear_irq(pic, pin_nr);
            rt_pic_user_extends(pic);
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
