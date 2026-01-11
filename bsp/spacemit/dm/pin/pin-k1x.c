/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <bitmap.h>

#define DBG_TAG "pin.k1"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "dev_pin_dm.h"

#define GPLR    0x0
#define GPDR    0xc
#define GPSR    0x18
#define GPCR    0x24
#define GRER    0x30
#define GFER    0x3c
#define GEDR    0x48
#define GSDR    0x54
#define GCDR    0x60
#define GSRER   0x6c
#define GCRER   0x78
#define GSFER   0x84
#define GCFER   0x90
#define GAPMASK 0x9c
#define GCPMASK 0xa8

#define K1X_BANK_GPIO_NUMBER            32
#define BANK_GPIO_MASK                  (K1X_BANK_GPIO_NUMBER - 1)

#define k1x_gpio_to_bank_idx(gpio)      ((gpio) / K1X_BANK_GPIO_NUMBER)
#define k1x_gpio_to_bank_offset(gpio)   ((gpio) & BANK_GPIO_MASK)

struct k1x_gpio_bank
{
    void *reg_bank;
    rt_uint32_t irq_mask;
    rt_uint32_t irq_rising_edge;
    rt_uint32_t irq_falling_edge;

    RT_BITMAP_DECLARE(value, K1X_BANK_GPIO_NUMBER);
};

struct k1x_gpio_chip
{
    struct rt_device_pin parent;

    int irq;
    void *reg_base;

    unsigned int nbank;
    struct k1x_gpio_bank *banks;
};

#define raw_to_k1x_gpio_chip(raw) rt_container_of(raw, struct k1x_gpio_chip, parent)

static void k1x_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_uint32_t bit, offset;
    struct k1x_gpio_chip *k1x_chip = raw_to_k1x_gpio_chip(device);
    struct k1x_gpio_bank *bank = &k1x_chip->banks[k1x_gpio_to_bank_idx(pin)];

    offset = k1x_gpio_to_bank_offset(pin);
    bit = RT_BIT(offset);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
    case PIN_MODE_OUTPUT_OD:
        HWREG32(bank->reg_bank + (rt_bitmap_test_bit(bank->value, offset) ? GPSR : GPCR)) = bit;
        HWREG32(bank->reg_bank + GSDR) = bit;
        break;

    case PIN_MODE_INPUT:
    case PIN_MODE_INPUT_PULLUP:
    case PIN_MODE_INPUT_PULLDOWN:
        HWREG32(bank->reg_bank + GCDR) = bit;
        break;

    default:
        break;
    }
}

static void k1x_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    rt_uint32_t bit, offset, reg;
    struct k1x_gpio_chip *k1x_chip = raw_to_k1x_gpio_chip(device);
    struct k1x_gpio_bank *bank = &k1x_chip->banks[k1x_gpio_to_bank_idx(pin)];

    offset = k1x_gpio_to_bank_offset(pin);
    bit = RT_BIT(offset);

    if (HWREG32(bank->reg_bank + GPDR) & bit)
    {
        if (value)
        {
            reg = GPSR;
            rt_bitmap_set_bit(bank->value, offset);
        }
        else
        {
            reg = GPCR;
            rt_bitmap_clear_bit(bank->value, offset);
        }

        HWREG32(bank->reg_bank + reg) = bit;
    }
}

static rt_ssize_t k1x_pin_read(struct rt_device *device, rt_base_t pin)
{
    rt_uint32_t bit;
    struct k1x_gpio_chip *k1x_chip = raw_to_k1x_gpio_chip(device);
    struct k1x_gpio_bank *bank = &k1x_chip->banks[k1x_gpio_to_bank_idx(pin)];

    bit = RT_BIT(k1x_gpio_to_bank_offset(pin));

    return !!(HWREG32(bank->reg_bank + GPLR) & bit);
}

static rt_err_t k1x_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_uint32_t bit;
    struct k1x_gpio_chip *k1x_chip = raw_to_k1x_gpio_chip(device);
    struct k1x_gpio_bank *bank = &k1x_chip->banks[k1x_gpio_to_bank_idx(pin)];

    bit = RT_BIT(k1x_gpio_to_bank_offset(pin));

    if (enabled)
    {
        bank->irq_mask |= bit;

        /* Set the bit of rising and falling edge detection if the gpio has. */
        HWREG32(bank->reg_bank + GSRER) = bit & bank->irq_rising_edge;
        HWREG32(bank->reg_bank + GSFER) = bit & bank->irq_falling_edge;
    }
    else
    {
        bank->irq_mask &= ~bit;

        /* Clear the bit of rising and falling edge detection. */
        HWREG32(bank->reg_bank + GCRER) = bit;
        HWREG32(bank->reg_bank + GCFER) = bit;
    }

    return RT_EOK;
}

static rt_err_t k1x_pin_irq_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_uint32_t bit;
    struct k1x_gpio_chip *k1x_chip = raw_to_k1x_gpio_chip(device);
    struct k1x_gpio_bank *bank = &k1x_chip->banks[k1x_gpio_to_bank_idx(pin)];

    bit = RT_BIT(k1x_gpio_to_bank_offset(pin));

    if (mode == PIN_IRQ_MODE_RISING)
    {
        bank->irq_rising_edge |= bit;
        HWREG32(bank->reg_bank + GSRER) = bit;
    }
    else
    {
        bank->irq_rising_edge &= ~bit;
        HWREG32(bank->reg_bank + GCRER) = bit;
    }

    if (mode == PIN_IRQ_MODE_FALLING)
    {
        bank->irq_falling_edge |= bit;
        HWREG32(bank->reg_bank + GSFER) = bit;
    }
    else
    {
        bank->irq_falling_edge &= ~bit;
        HWREG32(bank->reg_bank + GCFER) = bit;
    }

    return RT_EOK;
}

static rt_ssize_t k1x_pin_parse(struct rt_device *device,
        struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    rt_base_t gpio_pin;
    rt_err_t err = RT_EOK;

    if (flags)
    {
        *flags = args->args[1];
    }

    gpio_pin = args->args[0];

    for (int i = 0;; ++i)
    {
        rt_base_t gpio_start, pad_start;
        struct rt_device_pin *pinctrl;
        struct rt_ofw_cell_args gpio_ranges;

        if (rt_ofw_parse_phandle_cells(device->ofw_node, "gpio-ranges",
            "#gpio-range-cells", i, &gpio_ranges))
        {
            break;
        }

        gpio_start = gpio_ranges.args[0];
        pad_start = gpio_ranges.args[1];

        if (gpio_pin < gpio_start || gpio_pin > gpio_start + gpio_ranges.args[2])
        {
            rt_ofw_node_put(gpio_ranges.data);
            continue;
        }

        if (!(pinctrl = rt_ofw_data(gpio_ranges.data)))
        {
            err = -RT_EIO;
            goto _end;
        }

        err = pin_gpio_request(pinctrl, pad_start + (gpio_pin - gpio_start), args->args[1]);

    _end:
        rt_ofw_node_put(gpio_ranges.data);

        break;
    }

    return err ? : gpio_pin;
}

static const struct rt_pin_ops k1x_pin_ops =
{
    .pin_mode = k1x_pin_mode,
    .pin_write = k1x_pin_write,
    .pin_read = k1x_pin_read,
    .pin_irq_enable = k1x_pin_irq_enable,
    .pin_irq_mode = k1x_pin_irq_mode,
    .pin_parse = k1x_pin_parse,
};

static void k1x_gpio_isr(int irqno, void *param)
{
    int n;
    rt_uint32_t gedr;
    rt_bitmap_t pending;
    struct k1x_gpio_bank *bank;
    struct k1x_gpio_chip *k1x_chip = param;

    for (int i = 0; i < k1x_chip->nbank; ++i)
    {
        bank = &k1x_chip->banks[i];

        gedr = HWREG32(bank->reg_bank + GEDR);
        if (!gedr)
        {
            continue;
        }

        HWREG32(bank->reg_bank + GEDR) = gedr;
        gedr = gedr & bank->irq_mask;

        if (!gedr)
        {
            continue;
        }
        pending = gedr;

        rt_bitmap_for_each_set_bit(&pending, n, RT_BITS_PER_LONG)
        {
            rt_base_t pin = (i * K1X_BANK_GPIO_NUMBER) | (n & BANK_GPIO_MASK);

            HWREG32(bank->reg_bank + GEDR) = (1 << k1x_gpio_to_bank_offset(pin));

            pin_pic_handle_isr(&k1x_chip->parent, pin);
        }
    }
}

static rt_err_t k1x_gpio_probe(struct rt_platform_device *pdev)
{
    int i = 0;
    rt_err_t err;
    const char *name;
    struct rt_clk *clk = RT_NULL;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *child;
    struct k1x_gpio_bank *bank;
    struct k1x_gpio_chip *k1x_chip = rt_calloc(1, sizeof(*k1x_chip));

    if (!k1x_chip)
    {
        return -RT_ENOMEM;
    }

    if (!(k1x_chip->reg_base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((k1x_chip->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = k1x_chip->irq;
        goto _fail;
    }

    k1x_chip->nbank = rt_ofw_get_child_count(np);
    k1x_chip->banks = rt_calloc(k1x_chip->nbank, sizeof(*k1x_chip->banks));

    if (!k1x_chip->banks)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_ofw_foreach_child_node(np, child)
    {
        rt_uint32_t offset;

        if ((err = rt_ofw_prop_read_u32(child, "reg-offset", &offset)))
        {
            rt_ofw_node_put(child);
            goto _fail;
        }

        k1x_chip->banks[i++].reg_bank = k1x_chip->reg_base + offset;
    }

    clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(clk))
    {
        err = rt_ptr_err(clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(clk)))
    {
        LOG_E("Fail to enable gpio clock");
        goto _fail;
    }

    rt_dm_dev_set_name_auto(&k1x_chip->parent.parent, "gpio");
    name = rt_dm_dev_get_name(&k1x_chip->parent.parent);

    rt_hw_interrupt_install(k1x_chip->irq, k1x_gpio_isr, k1x_chip, name);
    rt_hw_interrupt_umask(k1x_chip->irq);

    k1x_chip->parent.ops = &k1x_pin_ops;
    k1x_chip->parent.parent.ofw_node = np;
    pin_api_init(&k1x_chip->parent, k1x_chip->nbank * K1X_BANK_GPIO_NUMBER);
    pin_pic_init(&k1x_chip->parent, k1x_chip->irq);

    rt_ofw_data(np) = &k1x_chip->parent;

    /* Clear all GPIO edge detects */
    for (i = 0; i < k1x_chip->nbank; ++i)
    {
        bank = &k1x_chip->banks[i];
        HWREG32(bank->reg_bank + GCFER) = 0xffffffff;
        HWREG32(bank->reg_bank + GCRER) = 0xffffffff;
        /* Unmask edge detection to AP. */
        HWREG32(bank->reg_bank + GAPMASK) = 0xffffffff;
    }

    return RT_EOK;
_fail:
    if (!rt_is_err_or_null(clk))
    {
        rt_clk_disable_unprepare(clk);
        rt_clk_put(clk);
    }

    if (k1x_chip->reg_base)
    {
        rt_iounmap(k1x_chip->reg_base);
    }

    if (k1x_chip->banks)
    {
        rt_free(k1x_chip->banks);
    }

    rt_free(k1x_chip);

    return err;
}

static const struct rt_ofw_node_id k1x_gpio_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-gpio" },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_gpio_driver =
{
    .name = "k1x-gpio",
    .ids = k1x_gpio_ofw_ids,

    .probe = k1x_gpio_probe,
};

static int k1x_gpio_register(void)
{
    rt_platform_driver_register(&k1x_gpio_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(k1x_gpio_register);
