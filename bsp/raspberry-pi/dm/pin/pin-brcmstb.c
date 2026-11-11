/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pin.brcmstb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dev_pin_dm.h>
#include <drivers/ofw_irq.h>

enum gio_reg_index
{
    GIO_REG_ODEN = 0,
    GIO_REG_DATA,
    GIO_REG_IODIR,
    GIO_REG_EC,
    GIO_REG_EI,
    GIO_REG_MASK,
    GIO_REG_LEVEL,
    GIO_REG_STAT,
    NUMBER_OF_GIO_REGISTERS
};

#define MAX_GPIO_PER_BANK   32
#define brcmstb_gpio_bit(pin) RT_BIT((pin) % MAX_GPIO_PER_BANK)

struct brcmstb_gpio;

struct brcmstb_gpio_bank
{
    int id;
    struct brcmstb_gpio *gpio;

    rt_uint32_t width;
};

struct brcmstb_gpio
{
    struct rt_device_pin parent;

    void *base;
    int irq;

    struct rt_spinlock lock;

    rt_uint32_t num_banks;
    struct brcmstb_gpio_bank *banks;
};

extern rt_err_t brcmstb_l2_intc_request_node(struct rt_ofw_node *np);

rt_inline struct brcmstb_gpio_bank *raw_to_brcmstb_gpio_bank(struct rt_device *raw, rt_ubase_t pin)
{
    struct brcmstb_gpio *gpio = rt_container_of(raw, struct brcmstb_gpio, parent);
    rt_ubase_t bank_id = pin / MAX_GPIO_PER_BANK;

    if (bank_id >= gpio->num_banks)
    {
        return RT_NULL;
    }

    return &gpio->banks[bank_id];
}

rt_inline rt_bool_t brcmstb_gpio_bank_is_valid(struct brcmstb_gpio_bank *bank, rt_base_t pin)
{
    return bank && bank->width && (pin % MAX_GPIO_PER_BANK) < bank->width;
}

rt_inline rt_uint32_t brcmstb_gpio_valid_mask(struct brcmstb_gpio_bank *bank)
{
    if (bank->width >= MAX_GPIO_PER_BANK)
    {
        return 0xffffffffU;
    }

    return RT_BIT(bank->width) - 1;
}

rt_inline rt_uint32_t brcmstb_gpio_offset(struct brcmstb_gpio_bank *bank, rt_uint32_t reg)
{
    return bank->id * NUMBER_OF_GIO_REGISTERS * sizeof(rt_uint32_t) + reg * sizeof(rt_uint32_t);
}

rt_inline rt_uint32_t brcmstb_gpio_readl(struct brcmstb_gpio_bank *bank, rt_uint32_t reg)
{
    return HWREG32(bank->gpio->base + brcmstb_gpio_offset(bank, reg));
}

rt_inline void brcmstb_gpio_writel(struct brcmstb_gpio_bank *bank, rt_uint32_t reg, rt_uint32_t value)
{
    HWREG32(bank->gpio->base + brcmstb_gpio_offset(bank, reg)) = value;
}

static void brcmstb_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_ubase_t level;
    rt_uint32_t oden, iodir, bit = brcmstb_gpio_bit(pin);
    struct brcmstb_gpio_bank *bank = raw_to_brcmstb_gpio_bank(device, pin);

    if (!brcmstb_gpio_bank_is_valid(bank, pin))
    {
        return;
    }

    level = rt_spin_lock_irqsave(&bank->gpio->lock);

    oden = brcmstb_gpio_readl(bank, GIO_REG_ODEN);
    iodir = brcmstb_gpio_readl(bank, GIO_REG_IODIR);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        brcmstb_gpio_writel(bank, GIO_REG_ODEN, oden & ~bit);
        brcmstb_gpio_writel(bank, GIO_REG_IODIR, iodir & ~bit);
        break;

    case PIN_MODE_OUTPUT_OD:
        brcmstb_gpio_writel(bank, GIO_REG_ODEN, oden | bit);
        brcmstb_gpio_writel(bank, GIO_REG_IODIR, iodir & ~bit);
        break;

    case PIN_MODE_INPUT:
    case PIN_MODE_INPUT_PULLUP:
    case PIN_MODE_INPUT_PULLDOWN:
        brcmstb_gpio_writel(bank, GIO_REG_IODIR, iodir | bit);
        break;

    default:
        break;
    }

    rt_spin_unlock_irqrestore(&bank->gpio->lock, level);
}

static void brcmstb_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    rt_ubase_t level;
    rt_uint32_t data, bit = brcmstb_gpio_bit(pin);
    struct brcmstb_gpio_bank *bank = raw_to_brcmstb_gpio_bank(device, pin);

    if (!brcmstb_gpio_bank_is_valid(bank, pin))
    {
        return;
    }

    level = rt_spin_lock_irqsave(&bank->gpio->lock);

    data = brcmstb_gpio_readl(bank, GIO_REG_DATA);
    if (value)
    {
        data |= bit;
    }
    else
    {
        data &= ~bit;
    }
    brcmstb_gpio_writel(bank, GIO_REG_DATA, data);

    rt_spin_unlock_irqrestore(&bank->gpio->lock, level);
}

static rt_ssize_t brcmstb_gpio_read(struct rt_device *device, rt_base_t pin)
{
    struct brcmstb_gpio_bank *bank = raw_to_brcmstb_gpio_bank(device, pin);

    if (!brcmstb_gpio_bank_is_valid(bank, pin))
    {
        return 0;
    }

    return !!(brcmstb_gpio_readl(bank, GIO_REG_DATA) & brcmstb_gpio_bit(pin));
}

static rt_err_t brcmstb_gpio_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_ubase_t level;
    rt_uint32_t imask, mask = brcmstb_gpio_bit(pin);
    struct brcmstb_gpio_bank *bank = raw_to_brcmstb_gpio_bank(device, pin);

    if (!brcmstb_gpio_bank_is_valid(bank, pin))
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&bank->gpio->lock);

    imask = brcmstb_gpio_readl(bank, GIO_REG_MASK);
    if (enabled)
    {
        imask |= mask;
    }
    else
    {
        imask &= ~mask;
    }
    brcmstb_gpio_writel(bank, GIO_REG_MASK, imask);

    rt_spin_unlock_irqrestore(&bank->gpio->lock, level);

    return RT_EOK;
}

static rt_err_t brcmstb_gpio_irq_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_ubase_t level;
    rt_uint32_t mask = brcmstb_gpio_bit(pin);
    rt_uint32_t int_level, ilevel;
    rt_uint32_t edge_config, iedge_config;
    rt_uint32_t edge_insensitive, iedge_insensitive;
    struct brcmstb_gpio_bank *bank = raw_to_brcmstb_gpio_bank(device, pin);

    if (!brcmstb_gpio_bank_is_valid(bank, pin))
    {
        return -RT_EINVAL;
    }

    switch (mode)
    {
    case PIN_IRQ_MODE_LOW_LEVEL:
        int_level = mask;
        edge_config = 0;
        edge_insensitive = 0;
        break;

    case PIN_IRQ_MODE_HIGH_LEVEL:
        int_level = mask;
        edge_config = mask;
        edge_insensitive = 0;
        break;

    case PIN_IRQ_MODE_FALLING:
        int_level = 0;
        edge_config = 0;
        edge_insensitive = 0;
        break;

    case PIN_IRQ_MODE_RISING:
        int_level = 0;
        edge_config = mask;
        edge_insensitive = 0;
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        int_level = 0;
        edge_config = 0;
        edge_insensitive = mask;
        break;

    default:
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&bank->gpio->lock);

    iedge_config = brcmstb_gpio_readl(bank, GIO_REG_EC) & ~mask;
    iedge_insensitive = brcmstb_gpio_readl(bank, GIO_REG_EI) & ~mask;
    ilevel = brcmstb_gpio_readl(bank, GIO_REG_LEVEL) & ~mask;

    brcmstb_gpio_writel(bank, GIO_REG_EC, iedge_config | edge_config);
    brcmstb_gpio_writel(bank, GIO_REG_EI, iedge_insensitive | edge_insensitive);
    brcmstb_gpio_writel(bank, GIO_REG_LEVEL, ilevel | int_level);

    rt_spin_unlock_irqrestore(&bank->gpio->lock, level);

    return RT_EOK;
}

static rt_err_t brcmstb_gpio_attach_irq(struct rt_device *device, rt_base_t pin,
        rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_err_t err;
    struct brcmstb_gpio *gpio = rt_container_of(device, struct brcmstb_gpio, parent);
    struct rt_pin_irq_hdr *legacy_isr;

    if (!brcmstb_gpio_bank_is_valid(raw_to_brcmstb_gpio_bank(device, pin), pin))
    {
        return -RT_EINVAL;
    }

    if (!gpio->parent.legacy_isr)
    {
        return -RT_ENOSYS;
    }

    err = brcmstb_gpio_irq_mode(device, pin, mode);
    if (err)
    {
        return err;
    }

    legacy_isr = &gpio->parent.legacy_isr[pin];
    legacy_isr->pin = pin;
    legacy_isr->mode = mode;
    legacy_isr->hdr = hdr;
    legacy_isr->args = args;

    return RT_EOK;
}

static rt_ssize_t brcmstb_gpio_parse(struct rt_device *device, struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    struct brcmstb_gpio_bank *bank;
    rt_base_t pin;

    if (!args || args->args_count < 2)
    {
        return -RT_EINVAL;
    }

    pin = args->args[0];
    bank = raw_to_brcmstb_gpio_bank(device, pin);
    if (!brcmstb_gpio_bank_is_valid(bank, pin))
    {
        return -RT_EINVAL;
    }

    if (flags)
    {
        *flags = args->args[1];
    }

    return pin;
}

static const struct rt_pin_ops brcmstb_gpio_ops =
{
    .pin_mode = brcmstb_gpio_mode,
    .pin_write = brcmstb_gpio_write,
    .pin_read = brcmstb_gpio_read,
    .pin_attach_irq = brcmstb_gpio_attach_irq,
    .pin_irq_enable = brcmstb_gpio_irq_enable,
    .pin_irq_mode = brcmstb_gpio_irq_mode,
    .pin_parse = brcmstb_gpio_parse,
};

static void brcmstb_gpio_isr(int irqno, void *param)
{
    rt_ubase_t level;
    rt_uint32_t mask, status;
    struct brcmstb_gpio *gpio = param;

    RT_UNUSED(irqno);

    for (int i = 0; i < gpio->num_banks; ++i)
    {
        struct brcmstb_gpio_bank *bank = &gpio->banks[i];

        while (RT_TRUE)
        {
            level = rt_spin_lock_irqsave(&gpio->lock);
            status = brcmstb_gpio_readl(bank, GIO_REG_STAT);
            status &= brcmstb_gpio_readl(bank, GIO_REG_MASK);
            status &= brcmstb_gpio_valid_mask(bank);
            rt_spin_unlock_irqrestore(&gpio->lock, level);

            if (!status)
            {
                break;
            }

            for (rt_ubase_t pin = 0; pin < bank->width; ++pin)
            {
                mask = RT_BIT(pin);

                if (mask & status)
                {
                    brcmstb_gpio_writel(bank, GIO_REG_STAT, mask);
                    pin_pic_handle_isr(&gpio->parent, bank->id * MAX_GPIO_PER_BANK + pin);
                }
            }
        }
    }
}

static void brcmstb_gpio_apply_hogs(struct brcmstb_gpio *gpio)
{
    struct rt_device *dev = &gpio->parent.parent;
    struct rt_ofw_node *child;

    rt_ofw_foreach_child_node(dev->ofw_node, child)
    {
        rt_uint32_t cells[2];
        rt_ssize_t nr;
        struct brcmstb_gpio_bank *bank;

        if (!rt_ofw_get_prop(child, "gpio-hog", RT_NULL))
        {
            continue;
        }

        nr = rt_ofw_prop_read_u32_array_index(child, "gpios", 0, 2, cells);
        if (nr < 2)
        {
            continue;
        }

        bank = raw_to_brcmstb_gpio_bank(dev, cells[0]);
        if (!brcmstb_gpio_bank_is_valid(bank, cells[0]))
        {
            continue;
        }

        if (rt_ofw_get_prop(child, "input", RT_NULL))
        {
            brcmstb_gpio_mode(dev, cells[0], PIN_MODE_INPUT);
        }
        else if (rt_ofw_get_prop(child, "output-high", RT_NULL))
        {
            brcmstb_gpio_write(dev, cells[0], 1);
            brcmstb_gpio_mode(dev, cells[0], PIN_MODE_OUTPUT);
        }
        else if (rt_ofw_get_prop(child, "output-low", RT_NULL))
        {
            brcmstb_gpio_write(dev, cells[0], 0);
            brcmstb_gpio_mode(dev, cells[0], PIN_MODE_OUTPUT);
        }
    }
}

static rt_err_t brcmstb_gpio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = -RT_EINVAL;
    const fdt32_t *cell;
    rt_uint32_t num_banks, value;
    struct rt_ofw_prop *prop;
    struct rt_device *dev = &pdev->parent;
    struct brcmstb_gpio_bank *bank = RT_NULL;
    struct brcmstb_gpio *gpio = rt_calloc(1, sizeof(*gpio));

    if (!gpio)
    {
        return -RT_ENOMEM;
    }

    gpio->base = rt_dm_dev_iomap(dev, 0);

    if (!gpio->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (dev->ofw_node)
    {
        struct rt_ofw_node *irq_parent;

        irq_parent = rt_ofw_find_irq_parent(dev->ofw_node, RT_NULL);
        if (irq_parent)
        {
            brcmstb_l2_intc_request_node(irq_parent);
            rt_ofw_node_put(irq_parent);
        }
    }

    gpio->irq = rt_dm_dev_get_irq(dev, 0);

    if (gpio->irq < 0 && gpio->irq != -RT_EEMPTY && gpio->irq != -RT_EIO)
    {
        err = gpio->irq;
        goto _fail;
    }

    num_banks = 0;
    rt_ofw_foreach_prop_u32(dev->ofw_node, "brcm,gpio-bank-widths", prop, cell, value)
    {
        struct brcmstb_gpio_bank *new_bank;

        if (!(new_bank = rt_realloc(bank, sizeof(*bank) * (num_banks + 1))))
        {
            LOG_E("No memory for bank(%u)", num_banks + 1);
            err = -RT_ENOMEM;
            goto _fail;
        }

        bank = new_bank;
        new_bank += num_banks;

        rt_memset(new_bank, 0, sizeof(*new_bank));
        new_bank->id = num_banks;
        new_bank->gpio = gpio;

        if (value > MAX_GPIO_PER_BANK)
        {
            LOG_E("Invalid bank width %u", value);
            goto _fail;
        }

        new_bank->width = value;
        ++num_banks;
    }

    if (!num_banks)
    {
        LOG_E("No valid gpio banks described");
        goto _fail;
    }

    gpio->num_banks = num_banks;
    gpio->banks = bank;
    rt_spin_lock_init(&gpio->lock);

    gpio->parent.ops = &brcmstb_gpio_ops;
    pin_api_init(&gpio->parent, MAX_GPIO_PER_BANK * gpio->num_banks);

    if (gpio->irq >= 0)
    {
        for (rt_ubase_t i = 0; i < gpio->num_banks; ++i)
        {
            brcmstb_gpio_writel(&gpio->banks[i], GIO_REG_MASK, 0);
        }

        pin_pic_init(&gpio->parent, gpio->irq);
        rt_hw_interrupt_install(gpio->irq, brcmstb_gpio_isr, gpio, "brcmstb-gpio");
        rt_hw_interrupt_umask(gpio->irq);
    }

    rt_ofw_data(dev->ofw_node) = &gpio->parent;

    brcmstb_gpio_apply_hogs(gpio);

    return RT_EOK;

_fail:
    if (bank)
    {
        rt_free(bank);
    }

    if (gpio->base)
    {
        rt_iounmap(gpio->base);
    }

    rt_free(gpio);

    return err;
}

static const struct rt_ofw_node_id brcmstb_gpio_ofw_ids[] =
{
    { .compatible = "brcm,brcmstb-gpio" },
    { /* sentinel */ }
};

static struct rt_platform_driver brcmstb_gpio_driver =
{
    .name = "brcmstb-gpio",
    .ids = brcmstb_gpio_ofw_ids,

    .probe = brcmstb_gpio_probe,
};

static int brcmstb_gpio_register(void)
{
    rt_platform_driver_register(&brcmstb_gpio_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(brcmstb_gpio_register);
