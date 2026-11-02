/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-31     RTT          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "drv.ra.gpio"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/core/dm.h>
#include <drivers/ofw.h>
#include <drivers/platform.h>
#include <drivers/pic.h>
#include <dt-bindings/pin/pin.h>

#include <hal_data.h>

#include "dev_pin_dm.h"
#include "drv_external_irq.h"

#define RA_GPIO_PIN_NR 16

struct ra_gpio_irq
{
    struct ra_external_irq *external_irq;
    int irq;
    rt_uint8_t mode;
    rt_bool_t acquired;
    rt_bool_t pic_attached;
    rt_bool_t enabled;
    void (*handler)(void *args);
    void *args;
};

struct ra_gpio
{
    struct rt_device_pin parent;
    rt_uint8_t port;
    rt_uint8_t ngpios;
    rt_uint32_t pin_cfg[RA_GPIO_PIN_NR];
    struct ra_gpio_irq irqs[RA_GPIO_PIN_NR];
};

static struct ra_gpio *device_to_ra_gpio(struct rt_device *device)
{
    struct rt_device_pin *pin = rt_container_of(device,
                                                struct rt_device_pin, parent);

    return rt_container_of(pin, struct ra_gpio, parent);
}

static bsp_io_port_pin_t ra_gpio_fsp_pin(struct ra_gpio *gpio, rt_base_t pin)
{
    return (bsp_io_port_pin_t)(((rt_uint32_t)gpio->port << 8) | pin);
}

static rt_bool_t ra_gpio_pin_is_valid(struct ra_gpio *gpio, rt_base_t pin)
{
    return pin >= 0 && pin < gpio->ngpios;
}

static rt_uint32_t ra_gpio_board_pin_cfg(struct ra_gpio *gpio, rt_base_t pin)
{
    bsp_io_port_pin_t fsp_pin = ra_gpio_fsp_pin(gpio, pin);

    for (rt_uint32_t i = 0; i < g_bsp_pin_cfg.number_of_pins; ++i)
    {
        if (g_bsp_pin_cfg.p_pin_cfg_data[i].pin == fsp_pin)
        {
            return g_bsp_pin_cfg.p_pin_cfg_data[i].pin_cfg;
        }
    }

    return 0;
}

static rt_bool_t ra_gpio_flags_are_valid(rt_uint32_t flags)
{
    rt_uint32_t bias = flags & RT_GENMASK(6, 4);
    rt_uint32_t drive = flags & (PIN_SINGLE_ENDED | PIN_LINE_OPEN_DRAIN);
    rt_uint32_t supported = PIN_ACTIVE_LOW | PIN_OPEN_DRAIN |
                            PIN_PULL_UP | PIN_PULL_DISABLE;

    if (flags & ~supported)
    {
        return RT_FALSE;
    }
    if (drive && drive != PIN_OPEN_DRAIN)
    {
        return RT_FALSE;
    }
    if (drive && bias)
    {
        return RT_FALSE;
    }
    if (bias && bias != PIN_PULL_UP && bias != PIN_PULL_DISABLE)
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void ra_gpio_mode(struct rt_device *device, rt_base_t pin,
                         rt_uint8_t mode)
{
    fsp_err_t err;
    rt_uint32_t cfg;
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (!ra_gpio_pin_is_valid(gpio, pin))
    {
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        cfg = IOPORT_CFG_PORT_DIRECTION_OUTPUT;
        break;

    case PIN_MODE_INPUT:
        cfg = IOPORT_CFG_PORT_DIRECTION_INPUT;
        break;

    case PIN_MODE_INPUT_PULLUP:
        cfg = IOPORT_CFG_PORT_DIRECTION_INPUT | IOPORT_CFG_PULLUP_ENABLE;
        break;

    case PIN_MODE_OUTPUT_OD:
        cfg = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_NMOS_ENABLE;
        break;

    case PIN_MODE_INPUT_PULLDOWN:
    default:
        LOG_E("P%u%02d mode %u is unsupported", gpio->port, pin, mode);
        return;
    }

    if (gpio->irqs[pin].external_irq)
    {
        cfg |= IOPORT_CFG_IRQ_ENABLE;
    }
    cfg |= gpio->pin_cfg[pin] & IOPORT_CFG_DRIVE_HIGH;

    err = R_IOPORT_PinCfg(&g_ioport_ctrl, ra_gpio_fsp_pin(gpio, pin), cfg);
    if (err != FSP_SUCCESS)
    {
        LOG_E("P%u%02d configure failed: %d", gpio->port, pin, err);
        return;
    }

    gpio->pin_cfg[pin] = cfg;
}

static void ra_gpio_write(struct rt_device *device, rt_base_t pin,
                          rt_uint8_t value)
{
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (ra_gpio_pin_is_valid(gpio, pin) &&
        R_IOPORT_PinWrite(&g_ioport_ctrl, ra_gpio_fsp_pin(gpio, pin),
                          value == PIN_LOW ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH) !=
            FSP_SUCCESS)
    {
        LOG_E("P%u%02d write failed", gpio->port, pin);
    }
}

static rt_ssize_t ra_gpio_read(struct rt_device *device, rt_base_t pin)
{
    fsp_err_t err;
    bsp_io_level_t level;
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (!ra_gpio_pin_is_valid(gpio, pin))
    {
        return -RT_EINVAL;
    }

    err = R_IOPORT_PinRead(&g_ioport_ctrl, ra_gpio_fsp_pin(gpio, pin), &level);
    if (err != FSP_SUCCESS)
    {
        return -RT_EIO;
    }

    return level == BSP_IO_LEVEL_LOW ? PIN_LOW : PIN_HIGH;
}

static void ra_gpio_irq_handler(int vector, void *param)
{
    struct ra_gpio_irq *irq = param;

    RT_UNUSED(vector);

    if (irq->handler)
    {
        irq->handler(irq->args);
    }
}

static rt_err_t ra_gpio_attach_irq(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t mode, void (*handler)(void *args), void *args)
{
    struct ra_gpio_irq *irq;
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (!ra_gpio_pin_is_valid(gpio, pin) || !handler ||
        !(irq = &gpio->irqs[pin])->external_irq)
    {
        return -RT_EINVAL;
    }

    if (irq->handler && (irq->handler != handler || irq->args != args ||
                         irq->mode != mode))
    {
        return -RT_EBUSY;
    }

    irq->mode = mode;
    irq->handler = handler;
    irq->args = args;

    return RT_EOK;
}

static rt_err_t ra_gpio_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t enabled)
{
    rt_err_t err, cleanup_err;
    struct ra_gpio_irq *irq;
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (!ra_gpio_pin_is_valid(gpio, pin) ||
        !(irq = &gpio->irqs[pin])->external_irq)
    {
        return -RT_EINVAL;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        if (!irq->handler)
        {
            return -RT_EINVAL;
        }
        if (irq->enabled)
        {
            return RT_EOK;
        }

        if (!irq->acquired)
        {
            irq->irq = ra_external_irq_acquire(irq->external_irq,
                                               gpio->port, pin, irq->mode);
            if (irq->irq < 0)
            {
                return irq->irq;
            }
            irq->acquired = RT_TRUE;
        }

        if (!irq->pic_attached)
        {
            err = rt_pic_attach_irq(irq->irq, ra_gpio_irq_handler, irq,
                                    "ra-gpio", RT_IRQ_F_NONE);
            if (err)
            {
                cleanup_err = ra_external_irq_release(irq->external_irq,
                                                      gpio->port, pin);
                if (!cleanup_err)
                {
                    irq->acquired = RT_FALSE;
                    irq->irq = -1;
                }
                return cleanup_err ? cleanup_err : err;
            }
            irq->pic_attached = RT_TRUE;
        }

        err = ra_external_irq_enable(irq->external_irq, gpio->port, pin);
        if (err)
        {
            cleanup_err = rt_pic_detach_irq(irq->irq, irq);
            if (cleanup_err)
            {
                return cleanup_err;
            }
            irq->pic_attached = RT_FALSE;

            cleanup_err = ra_external_irq_release(irq->external_irq,
                                                  gpio->port, pin);
            if (!cleanup_err)
            {
                irq->acquired = RT_FALSE;
                irq->irq = -1;
            }
            return cleanup_err ? cleanup_err : err;
        }

        irq->enabled = RT_TRUE;
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        if (!irq->acquired && !irq->pic_attached)
        {
            irq->enabled = RT_FALSE;
            return RT_EOK;
        }

        if (irq->enabled &&
            (err = ra_external_irq_disable(irq->external_irq,
                                           gpio->port, pin)))
        {
            return err;
        }
        irq->enabled = RT_FALSE;

        if (irq->pic_attached)
        {
            err = rt_pic_detach_irq(irq->irq, irq);
            if (err)
            {
                cleanup_err = ra_external_irq_enable(irq->external_irq,
                                                     gpio->port, pin);
                if (!cleanup_err)
                {
                    irq->enabled = RT_TRUE;
                }
                return cleanup_err ? cleanup_err : err;
            }
            irq->pic_attached = RT_FALSE;
        }

        if (irq->acquired)
        {
            err = ra_external_irq_release(irq->external_irq,
                                          gpio->port, pin);
            if (err)
            {
                cleanup_err = rt_pic_attach_irq(irq->irq,
                                                ra_gpio_irq_handler, irq, "ra-gpio", RT_IRQ_F_NONE);
                if (cleanup_err)
                {
                    return cleanup_err;
                }
                irq->pic_attached = RT_TRUE;

                cleanup_err = ra_external_irq_enable(irq->external_irq,
                                                     gpio->port, pin);
                if (!cleanup_err)
                {
                    irq->enabled = RT_TRUE;
                }
                return cleanup_err ? cleanup_err : err;
            }
            irq->acquired = RT_FALSE;
            irq->irq = -1;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t ra_gpio_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_err_t err;
    struct ra_gpio_irq *irq;
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (!ra_gpio_pin_is_valid(gpio, pin))
    {
        return -RT_EINVAL;
    }

    irq = &gpio->irqs[pin];
    if ((irq->enabled || irq->pic_attached || irq->acquired) &&
        (err = ra_gpio_irq_enable(device, pin, PIN_IRQ_DISABLE)))
    {
        return err;
    }

    irq->handler = RT_NULL;
    irq->args = RT_NULL;
    irq->mode = 0;

    return RT_EOK;
}

static rt_ssize_t ra_gpio_parse(struct rt_device *device,
                                struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    struct ra_gpio *gpio = device_to_ra_gpio(device);

    if (args->args_count != 2 || args->args[0] >= gpio->ngpios ||
        !ra_gpio_flags_are_valid(args->args[1]))
    {
        return -RT_EINVAL;
    }

    if (flags)
    {
        *flags = args->args[1];
    }

    return args->args[0];
}

static const struct rt_pin_ops ra_gpio_ops = {
    .pin_mode = ra_gpio_mode,
    .pin_write = ra_gpio_write,
    .pin_read = ra_gpio_read,
    .pin_attach_irq = ra_gpio_attach_irq,
    .pin_detach_irq = ra_gpio_detach_irq,
    .pin_irq_enable = ra_gpio_irq_enable,
    .pin_parse = ra_gpio_parse,
};

static rt_err_t ra_gpio_parse_port_irqs(struct ra_gpio *gpio,
                                        struct rt_ofw_node *np)
{
    int irq_count = 0;
    struct rt_ofw_node *irq_np;

    while ((irq_np = rt_ofw_parse_phandle(np, "port-irqs", irq_count)))
    {
        int pin_count;
        const char *irq_name;
        char pins_prop[48];
        struct ra_external_irq *external_irq;

        if (rt_ofw_prop_read_string_index(np, "port-irq-names", irq_count,
                                          &irq_name) ||
            !(external_irq = ra_external_irq_get(irq_np)))
        {
            rt_ofw_node_put(irq_np);
            return -RT_EINVAL;
        }

        rt_snprintf(pins_prop, sizeof(pins_prop), "port-%s-pins", irq_name);
        pin_count = rt_ofw_prop_count_of_size(np, pins_prop,
                                              sizeof(fdt32_t));
        if (pin_count <= 0)
        {
            rt_ofw_node_put(irq_np);
            return -RT_EINVAL;
        }

        for (int i = 0; i < pin_count; ++i)
        {
            rt_uint32_t pin;

            if (rt_ofw_prop_read_u32_index(np, pins_prop, i, &pin) ||
                pin >= gpio->ngpios || gpio->irqs[pin].external_irq)
            {
                rt_ofw_node_put(irq_np);
                return -RT_EINVAL;
            }
            gpio->irqs[pin].external_irq = external_irq;
        }

        rt_ofw_node_put(irq_np);
        ++irq_count;
    }

    return RT_EOK;
}

static rt_err_t ra_gpio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t port, ngpios = RA_GPIO_PIN_NR;
    rt_uint64_t address, size;
    struct rt_device *dev = &pdev->parent;
    struct ra_gpio *gpio = rt_calloc(1, sizeof(*gpio));

    if (!gpio)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_ofw_get_address(dev->ofw_node, 0, &address, &size)) ||
        !size ||
        (err = rt_ofw_prop_read_u32(dev->ofw_node, "port", &port)) ||
        port > 13)
    {
        err = err ? err : -RT_EINVAL;
        goto _fail;
    }
    if (address != 0x40400000UL + port * 0x20UL)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rt_ofw_prop_read_u32(dev->ofw_node, "ngpios", &ngpios);
    if (!ngpios || ngpios > RA_GPIO_PIN_NR)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    gpio->port = port;
    gpio->ngpios = ngpios;
    for (int i = 0; i < gpio->ngpios; ++i)
    {
        gpio->pin_cfg[i] = ra_gpio_board_pin_cfg(gpio, i);
        gpio->irqs[i].irq = -1;
    }

    if ((err = ra_gpio_parse_port_irqs(gpio, dev->ofw_node)))
    {
        goto _fail;
    }

    gpio->parent.ops = &ra_gpio_ops;
    if ((err = pin_api_init(&gpio->parent, gpio->ngpios)))
    {
        goto _fail;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, &gpio->parent);
    pdev->priv = gpio;

    return RT_EOK;

_fail:
    rt_free(gpio);

    return err;
}

static const struct rt_ofw_node_id ra_gpio_ofw_ids[] = {
    { .compatible = "renesas,ra-gpio-ioport" },
    { /* sentinel */ }
};

static struct rt_platform_driver ra_gpio_driver = {
    .name = "ra-gpio-ioport",
    .ids = ra_gpio_ofw_ids,
    .probe = ra_gpio_probe,
};
RT_PLATFORM_DRIVER_EXPORT(ra_gpio_driver);
