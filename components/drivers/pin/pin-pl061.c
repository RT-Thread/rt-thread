/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "dev_pin_dm.h"

#define PL061_DIR       0x400
#define PL061_IS        0x404
#define PL061_IBE       0x408
#define PL061_IEV       0x40c
#define PL061_IE        0x410
#define PL061_RIS       0x414
#define PL061_MIS       0x418
#define PL061_IC        0x41c

#define PL061_GPIO_NR   8

struct pl061
{
    struct rt_device_pin parent;

    int irq;
    void *base;

    struct rt_clk *pclk;
    struct rt_spinlock spinlock;
};

#define raw_to_pl061(raw) rt_container_of(raw, struct pl061, parent)

rt_inline rt_uint8_t pl061_read(struct pl061 *pl061, int offset)
{
    return HWREG8(pl061->base + offset);
}

rt_inline void pl061_write(struct pl061 *pl061, int offset, rt_uint8_t value)
{
    HWREG8(pl061->base + offset) = value;
}

static void pl061_isr(int irqno, void *param)
{
    rt_uint8_t mask = 0;
    rt_ubase_t pending, level;
    struct pl061 *pl061 = (struct pl061 *)param;

    level = rt_spin_lock_irqsave(&pl061->spinlock);

    pending = pl061_read(pl061, PL061_MIS);

    rt_spin_unlock_irqrestore(&pl061->spinlock, level);

    if (pending)
    {
        for (int pin = 0; pin < PL061_GPIO_NR; ++pin)
        {
            if (pending & RT_BIT(pin))
            {
                mask |= RT_BIT(pin);

                pin_pic_handle_isr(&pl061->parent, pin);
            }
        }

        level = rt_spin_lock_irqsave(&pl061->spinlock);

        pl061_write(pl061, PL061_IC, mask);

        rt_spin_unlock_irqrestore(&pl061->spinlock, level);
    }
}

static void pl061_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    struct pl061 *pl061 = raw_to_pl061(device);

    if (pin >= 0 && pin < PL061_GPIO_NR)
    {
        rt_base_t level = rt_spin_lock_irqsave(&pl061->spinlock);

        switch (mode)
        {
        case PIN_MODE_OUTPUT:

            pl061_write(pl061, RT_BIT(pin + 2), 1 << pin);
            pl061_write(pl061, PL061_DIR, pl061_read(pl061, PL061_DIR) | RT_BIT(pin));

            /*
             * gpio value is set again, because pl061 doesn't allow to set value
             * of a gpio pin before configuring it in OUT mode.
             */
            pl061_write(pl061, RT_BIT(pin + 2), 1 << pin);

            break;

        case PIN_MODE_INPUT:

            pl061_write(pl061, PL061_DIR, pl061_read(pl061, PL061_DIR) & ~RT_BIT(pin));

            break;

        default:
            break;
        }

        rt_spin_unlock_irqrestore(&pl061->spinlock, level);
    }
}

static void pl061_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    struct pl061 *pl061 = raw_to_pl061(device);

    if (pin >= 0 && pin < PL061_GPIO_NR)
    {
        pl061_write(pl061, RT_BIT(pin + 2), !!value << pin);
    }
}

static rt_ssize_t pl061_pin_read(struct rt_device *device, rt_base_t pin)
{
    rt_int8_t value = -RT_EINVAL;
    struct pl061 *pl061 = raw_to_pl061(device);

    if (pin >= 0 && pin < PL061_GPIO_NR)
    {
        value = !!pl061_read(pl061, RT_BIT(pin + 2));
    }

    return value;
}

static rt_err_t pl061_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_err_t err = RT_EOK;
    struct pl061 *pl061 = raw_to_pl061(device);

    if (pin >= 0 && pin < PL061_GPIO_NR)
    {
        rt_uint8_t gpioie, mask = RT_BIT(pin);
        rt_ubase_t level = rt_spin_lock_irqsave(&pl061->spinlock);

        if (enabled)
        {
            gpioie = pl061_read(pl061, PL061_IE) | mask;
        }
        else
        {
            gpioie = pl061_read(pl061, PL061_IE) & ~mask;
        }

        pl061_write(pl061, PL061_IE, gpioie);

        rt_spin_unlock_irqrestore(&pl061->spinlock, level);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static rt_err_t pl061_pin_irq_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_err_t err = RT_EOK;
    struct pl061 *pl061 = raw_to_pl061(device);

    if (pin >= 0 && pin < PL061_GPIO_NR)
    {
        rt_uint8_t gpiois, gpioibe, gpioiev, bit = RT_BIT(pin);
        rt_ubase_t level = rt_spin_lock_irqsave(&pl061->spinlock);

        gpioiev = pl061_read(pl061, PL061_IEV);
        gpiois  = pl061_read(pl061, PL061_IS);
        gpioibe = pl061_read(pl061, PL061_IBE);

        if (mode == PIN_IRQ_MODE_HIGH_LEVEL || mode == PIN_IRQ_MODE_LOW_LEVEL)
        {
            rt_bool_t polarity = (mode == PIN_IRQ_MODE_HIGH_LEVEL);

            /* Disable edge detection */
            gpioibe &= ~bit;
            /* Enable level detection */
            gpiois |= bit;

            /* Select polarity */
            if (polarity)
            {
                gpioiev |= bit;
            }
            else
            {
                gpioiev &= ~bit;
            }
        }
        else if (mode == PIN_IRQ_MODE_RISING_FALLING)
        {
            /* Disable level detection */
            gpiois &= ~bit;
            /* Select both edges, setting this makes PL061_EV be ignored */
            gpioibe |= bit;
        }
        else if (mode == PIN_IRQ_MODE_RISING || mode == PIN_IRQ_MODE_FALLING)
        {
            rt_bool_t rising = (mode == PIN_IRQ_MODE_RISING);

            /* Disable level detection */
            gpiois &= ~bit;
            /* Clear detection on both edges */
            gpioibe &= ~bit;

            /* Select edge */
            if (rising)
            {
                gpioiev |= bit;
            }
            else
            {
                gpioiev &= ~bit;
            }
        }
        else
        {
            /* No trigger: disable everything */
            gpiois  &= ~bit;
            gpioibe &= ~bit;
            gpioiev &= ~bit;
        }

        pl061_write(pl061, PL061_IS, gpiois);
        pl061_write(pl061, PL061_IBE, gpioibe);
        pl061_write(pl061, PL061_IEV, gpioiev);

        rt_spin_unlock_irqrestore(&pl061->spinlock, level);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static const struct rt_pin_ops pl061_pin_ops =
{
    .pin_mode = pl061_pin_mode,
    .pin_write = pl061_pin_write,
    .pin_read = pl061_pin_read,
    .pin_irq_enable = pl061_pin_irq_enable,
    .pin_irq_mode = pl061_pin_irq_mode,
};

static rt_err_t pl061_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct pl061 *pl061 = rt_calloc(1, sizeof(*pl061));

    if (!pl061)
    {
        return -RT_ENOMEM;
    }

    pl061->base = rt_dm_dev_iomap(dev, 0);

    if (!pl061->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    pl061->irq = rt_dm_dev_get_irq(dev, 0);

    if (pl061->irq < 0)
    {
        err = pl061->irq;

        goto _fail;
    }

    pl061->pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(pl061->pclk))
    {
        err = rt_ptr_err(pl061->pclk);

        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(pl061->pclk)))
    {
        goto _fail;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, &pl061->parent);

    rt_spin_lock_init(&pl061->spinlock);

    pl061->parent.ops = &pl061_pin_ops;
    pin_api_init(&pl061->parent, PL061_GPIO_NR);
    pin_pic_init(&pl061->parent, pl061->irq);

    rt_hw_interrupt_install(pl061->irq, pl061_isr, pl061, "gpio-pl061");
    rt_hw_interrupt_umask(pl061->irq);

    return RT_EOK;

_fail:
    if (pl061->base)
    {
        rt_iounmap(pl061->base);
    }

    if (!rt_is_err_or_null(pl061->pclk))
    {
        rt_clk_disable_unprepare(pl061->pclk);
        rt_clk_put(pl061->pclk);
    }

    rt_free(pl061);

    return err;
}

static const struct rt_ofw_node_id pl061_ofw_ids[] =
{
    { .compatible = "arm,pl061" },
    { /* sentinel */ }
};

static struct rt_platform_driver pl061_driver =
{
    .name = "pin-pl061",
    .ids = pl061_ofw_ids,

    .probe = pl061_probe,
};

static int pl061_drv_register(void)
{
    rt_platform_driver_register(&pl061_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(pl061_drv_register);
