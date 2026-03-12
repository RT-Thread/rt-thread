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
#include "pinctrl-rockchip.h"

#define GPIO_TYPE_V1    0
#define GPIO_TYPE_V2    0x01000c2b
#define GPIO_TYPE_V2_1  0x0101157c

static const struct rockchip_gpio_regs _gpio_regs_v1 =
{
    .port_dr        = 0x00,
    .port_ddr       = 0x04,
    .int_en         = 0x30,
    .int_mask       = 0x34,
    .int_type       = 0x38,
    .int_polarity   = 0x3c,
    .int_status     = 0x40,
    .int_rawstatus  = 0x44,
    .debounce       = 0x48,
    .port_eoi       = 0x4c,
    .ext_port       = 0x50,
};

static const struct rockchip_gpio_regs _gpio_regs_v2 =
{
    .port_dr        = 0x00,
    .port_ddr       = 0x08,
    .int_en         = 0x10,
    .int_mask       = 0x18,
    .int_type       = 0x20,
    .int_polarity   = 0x28,
    .int_bothedge   = 0x30,
    .int_status     = 0x50,
    .int_rawstatus  = 0x58,
    .debounce       = 0x38,
    .dbclk_div_en   = 0x40,
    .dbclk_div_con  = 0x48,
    .port_eoi       = 0x60,
    .ext_port       = 0x70,
    .version_id     = 0x78,
};

rt_inline void gpio_writel_v2(void *base, rt_uint32_t val)
{
    HWREG32(base) = (val & 0xffff) | 0xffff0000U;
    HWREG32(base + 0x4) = (val >> 16) | 0xffff0000U;
}

rt_inline rt_uint32_t gpio_readl_v2(void *base)
{
    return HWREG32(base + 0x4) << 16 | HWREG32(base);
}

rt_inline void rockchip_gpio_writel(struct rockchip_pin_bank *pin_bank, rt_uint32_t value, int offset)
{
    void *base = pin_bank->reg_base + offset;

    if (pin_bank->gpio_type == GPIO_TYPE_V2)
    {
        gpio_writel_v2(base, value);
    }
    else
    {
        HWREG32(base) = value;
    }
}

rt_inline rt_uint32_t rockchip_gpio_readl(struct rockchip_pin_bank *pin_bank, int offset)
{
    rt_uint32_t value;
    void *base = pin_bank->reg_base + offset;

    if (pin_bank->gpio_type == GPIO_TYPE_V2)
    {
        value = gpio_readl_v2(base);
    }
    else
    {
        value = HWREG32(base);
    }

    return value;
}

rt_inline void rockchip_gpio_writel_bit(struct rockchip_pin_bank *pin_bank,
        rt_uint32_t bit, rt_uint32_t value, int offset)
{
    rt_uint32_t data;
    void *base = pin_bank->reg_base + offset;

    if (pin_bank->gpio_type == GPIO_TYPE_V2)
    {
        if (value)
        {
            data = RT_BIT(bit % 16) | RT_BIT(bit % 16 + 16);
        }
        else
        {
            data = RT_BIT(bit % 16 + 16);
        }
        HWREG32(bit >= 16 ? base + 0x4 : base) = data;
    }
    else
    {
        data = HWREG32(base);
        data &= ~RT_BIT(bit);

        if (value)
        {
            data |= RT_BIT(bit);
        }
        HWREG32(base) = data;
    }
}

rt_inline rt_uint32_t rockchip_gpio_readl_bit(struct rockchip_pin_bank *pin_bank,
        rt_uint32_t bit, int offset)
{
    rt_uint32_t data;
    void *base = pin_bank->reg_base + offset;

    if (pin_bank->gpio_type == GPIO_TYPE_V2)
    {
        data = HWREG32(bit >= 16 ? base + 0x4 : base);
        data >>= bit % 16;
    }
    else
    {
        data = HWREG32(base);
        data >>= bit;
    }

    return data & 1;
}

static void rk_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_base_t level;
    struct rockchip_pin_bank *pin_bank = raw_pin_to_bank(device);
    struct rockchip_pin_ctrl *pinctrl = pin_bank->drvdata->pinctrl;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
    case PIN_MODE_OUTPUT_OD:
        pinctrl->set_mux(pin_bank, pin, RK_FUNC_GPIO);

        level = rt_spin_lock_irqsave(&pin_bank->spinlock);
        rockchip_gpio_writel_bit(pin_bank, pin, 1, pin_bank->gpio_regs->port_ddr);
        rt_spin_unlock_irqrestore(&pin_bank->spinlock, level);
        break;

    case PIN_MODE_INPUT:
    case PIN_MODE_INPUT_PULLUP:
    case PIN_MODE_INPUT_PULLDOWN:
        pinctrl->set_mux(pin_bank, pin, RK_FUNC_GPIO);

        level = rt_spin_lock_irqsave(&pin_bank->spinlock);
        rockchip_gpio_writel_bit(pin_bank, pin, 0, pin_bank->gpio_regs->port_ddr);
        rt_spin_unlock_irqrestore(&pin_bank->spinlock, level);
        break;

    default:
        break;
    }
}

static void rk_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    struct rockchip_pin_bank *pin_bank = raw_pin_to_bank(device);

    rockchip_gpio_writel_bit(pin_bank, pin, value, pin_bank->gpio_regs->port_dr);
}

static rt_ssize_t rk_pin_read(struct rt_device *device, rt_base_t pin)
{
    rt_uint32_t data;
    struct rockchip_pin_bank *pin_bank = raw_pin_to_bank(device);

    data = HWREG32(pin_bank->reg_base + pin_bank->gpio_regs->ext_port);
    data >>= pin;

    return data & 1;
}

static rt_err_t rk_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_base_t level;
    struct rockchip_pin_bank *pin_bank = raw_pin_to_bank(device);

    level = rt_spin_lock_irqsave(&pin_bank->spinlock);

    if (enabled)
    {
        pin_bank->mask_cache &= ~RT_BIT(pin);
    }
    else
    {
        pin_bank->mask_cache |= RT_BIT(pin);
    }
    rockchip_gpio_writel(pin_bank, pin_bank->mask_cache, pin_bank->gpio_regs->int_mask);

    rt_spin_unlock_irqrestore(&pin_bank->spinlock, level);

    return RT_EOK;
}

static rt_err_t rk_pin_irq_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_base_t level;
    rt_err_t err = RT_EOK;
    rt_uint32_t mask, int_level, polarity, data;
    struct rockchip_pin_bank *pin_bank = raw_pin_to_bank(device);
    const struct rockchip_gpio_regs *reg = pin_bank->gpio_regs;

    level = rt_spin_lock_irqsave(&pin_bank->spinlock);

    rockchip_gpio_writel_bit(pin_bank, pin, 0, reg->port_ddr);

    mask = RT_BIT(pin);
    int_level = rockchip_gpio_readl(pin_bank, reg->int_type);
    polarity = rockchip_gpio_readl(pin_bank, reg->int_polarity);

    if (mode == PIN_IRQ_MODE_RISING_FALLING)
    {
        if (pin_bank->gpio_type == GPIO_TYPE_V2)
        {
            rockchip_gpio_writel_bit(pin_bank, pin, 1, reg->int_bothedge);
            goto _end;
        }
        else
        {
            pin_bank->toggle_edge_mode |= mask;
            int_level &= ~mask;

            /*
             * Determine gpio state. If 1 next interrupt should be
             * low otherwise high.
             */
            data = HWREG32(pin_bank->reg_base + reg->ext_port);

            if (data & mask)
            {
                polarity &= ~mask;
            }
            else
            {
                polarity |= mask;
            }
        }
    }
    else
    {
        if (pin_bank->gpio_type == GPIO_TYPE_V2)
        {
            rockchip_gpio_writel_bit(pin_bank, pin, 0, reg->int_bothedge);
        }
        else
        {
            pin_bank->toggle_edge_mode &= ~mask;
        }

        switch (mode)
        {
        case PIN_IRQ_MODE_RISING:
            int_level |= mask;
            polarity |= mask;
            break;

        case PIN_IRQ_MODE_FALLING:
            int_level |= mask;
            polarity &= ~mask;
            break;

        case PIN_IRQ_MODE_HIGH_LEVEL:
            int_level &= ~mask;
            polarity |= mask;
            break;

        case PIN_IRQ_MODE_LOW_LEVEL:
            int_level &= ~mask;
            polarity &= ~mask;
            break;

        default:
            err = -RT_EINVAL;
            goto _end;
        }
    }

    rockchip_gpio_writel(pin_bank, int_level, reg->int_type);
    rockchip_gpio_writel(pin_bank, polarity, reg->int_polarity);

_end:
    rt_spin_unlock_irqrestore(&pin_bank->spinlock, level);

    return err;
}

static rt_err_t rk_pin_debounce(struct rt_device *device, rt_base_t pin, rt_uint32_t debounce)
{
    rt_uint64_t div;
    rt_uint32_t cur_div_reg;
    rt_bool_t div_debounce_support;
    rt_ubase_t level, div_reg, freq, max_debounce;
    struct rockchip_pin_bank *pin_bank = raw_pin_to_bank(device);
    const struct rockchip_gpio_regs *reg = pin_bank->gpio_regs;

    if (pin_bank->gpio_type == GPIO_TYPE_V2 && !rt_is_err(pin_bank->db_clk))
    {
        div_debounce_support = RT_TRUE;

        freq = rt_clk_get_rate(pin_bank->db_clk);
        max_debounce = (RT_GENMASK(23, 0) + 1) * 2 * 1000000 / freq;
        if (debounce > max_debounce)
        {
            return -RT_EINVAL;
        }

        div = debounce * freq;
        div_reg = RT_DIV_ROUND_CLOSEST_ULL(div, 2 * 1000000L) - 1;
    }
    else
    {
        div_debounce_support = RT_FALSE;
    }

    level = rt_spin_lock_irqsave(&pin_bank->spinlock);

    /* Only the v1 needs to configure div_en and div_con for dbclk */
    if (debounce)
    {
        if (div_debounce_support)
        {
            /* Configure the max debounce from consumers */
            cur_div_reg = HWREG32(pin_bank->reg_base + reg->dbclk_div_con);

            if (cur_div_reg < div_reg)
            {
                HWREG32(pin_bank->reg_base + reg->dbclk_div_con) = div_reg;
            }

            rockchip_gpio_writel_bit(pin_bank, pin, 1, reg->dbclk_div_en);
        }

        rockchip_gpio_writel_bit(pin_bank, pin, 1, reg->debounce);
    }
    else
    {
        if (div_debounce_support)
        {
            rockchip_gpio_writel_bit(pin_bank, pin, 0, reg->dbclk_div_en);
        }

        rockchip_gpio_writel_bit(pin_bank, pin, 0, reg->debounce);
    }

    rt_spin_unlock_irqrestore(&pin_bank->spinlock, level);

    /* Enable or disable dbclk at last */
    if (div_debounce_support)
    {
        if (debounce)
        {
            rt_clk_prepare_enable(pin_bank->db_clk);
        }
        else
        {
            rt_clk_disable_unprepare(pin_bank->db_clk);
        }
    }

    return RT_EOK;
}

static rt_ssize_t rk_pin_parse(struct rt_device *device, struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    if (flags)
    {
        *flags = args->args[1];
    }

    return args->args[0];
}

static const struct rt_pin_ops rk_pin_ops =
{
    .pin_mode = rk_pin_mode,
    .pin_write = rk_pin_write,
    .pin_read = rk_pin_read,
    .pin_irq_enable = rk_pin_irq_enable,
    .pin_irq_mode = rk_pin_irq_mode,
    .pin_debounce = rk_pin_debounce,
    .pin_parse = rk_pin_parse,
};

static void rk_pin_isr(int irqno, void *param)
{
    rt_uint32_t pending;
    struct rockchip_pin_bank *pin_bank = param;

    pending = HWREG32(pin_bank->reg_base + pin_bank->gpio_regs->int_status);

    for (rt_ubase_t pin = 0; pin < 32 && pending; ++pin)
    {
        rt_uint32_t clr = RT_BIT(pin);

        if (!(clr & pending))
        {
            continue;
        }

        if (clr & pin_bank->toggle_edge_mode)
        {
            rt_uint32_t data, data_old, polarity;

            data = HWREG32(pin_bank->reg_base + pin_bank->gpio_regs->ext_port);

            do {
                rt_ubase_t level = rt_spin_lock_irqsave(&pin_bank->spinlock);

                polarity = HWREG32(pin_bank->reg_base + pin_bank->gpio_regs->int_polarity);

                if (data & clr)
                {
                    polarity &= ~clr;
                }
                else
                {
                    polarity |= clr;
                }
                HWREG32(pin_bank->reg_base + pin_bank->gpio_regs->int_polarity) = polarity;

                rt_spin_unlock_irqrestore(&pin_bank->spinlock, level);

                data_old = data;
                data = HWREG32(pin_bank->reg_base + pin_bank->gpio_regs->ext_port);
            } while ((data & clr) != (data_old & clr));
        }

        pin_pic_handle_isr(&pin_bank->parent, pin);

        rockchip_gpio_writel_bit(pin_bank, pin, 1, pin_bank->gpio_regs->port_eoi);

        /* clear this pin irq */
        pending &= ~clr;
    }
}

static rt_err_t rockchip_gpio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    int id, version;
    const char *name;
    struct rockchip_pin_bank *pin_bank;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    struct rt_ofw_node *npp = rt_ofw_get_parent(np);
    struct rockchip_pinctrl_device *pinctrl_dev = rt_ofw_data(npp);
    struct rockchip_pin_ctrl *pinctrl = pinctrl_dev->pinctrl;

    rt_ofw_node_put(npp);

    if ((id = pdev->dev_id) < 0)
    {
        static int gpio_uid = 0;

        id = gpio_uid++;
    }

    pin_bank = &pinctrl->pin_banks[id];

    pin_bank->reg_base = rt_ofw_iomap(np, 0);

    if (!pin_bank->reg_base)
    {
        err = -RT_EIO;
        goto _out_res;
    }

    pin_bank->irq = rt_ofw_get_irq(np, 0);

    if (pin_bank->irq < 0)
    {
        err = pin_bank->irq;
        goto _out_res;
    }

    pin_bank->clk = rt_ofw_get_clk(np, 0);

    if (rt_is_err(pin_bank->clk))
    {
        err = rt_ptr_err(pin_bank->clk);
        goto _out_res;
    }

    rt_clk_prepare_enable(pin_bank->clk);

    version = HWREG32(pin_bank->reg_base + _gpio_regs_v2.version_id);

    if (version == GPIO_TYPE_V2 || version == GPIO_TYPE_V2_1)
    {
        pin_bank->gpio_regs = &_gpio_regs_v2;
        pin_bank->gpio_type = GPIO_TYPE_V2;

        pin_bank->db_clk = rt_ofw_get_clk(np, 1);

        if (rt_is_err(pin_bank->db_clk))
        {
            err = rt_ptr_err(pin_bank->db_clk);
            goto _out_res;
        }

        rt_clk_prepare_enable(pin_bank->db_clk);
    }
    else
    {
        pin_bank->gpio_regs = &_gpio_regs_v1;
        pin_bank->gpio_type = GPIO_TYPE_V1;
    }

    rt_dm_dev_set_name_auto(&pin_bank->parent.parent, "gpio");
    name = rt_dm_dev_get_name(&pin_bank->parent.parent);

    rt_hw_interrupt_install(pin_bank->irq, rk_pin_isr, pin_bank, name);
    rt_hw_interrupt_umask(pin_bank->irq);

    rockchip_gpio_writel(pin_bank, 0xffffffffU, pin_bank->gpio_regs->int_mask);
    rockchip_gpio_writel(pin_bank, 0xffffffffU, pin_bank->gpio_regs->port_eoi);
    rockchip_gpio_writel(pin_bank, 0xffffffffU, pin_bank->gpio_regs->int_en);

    pin_bank->mask_cache = 0xffffffffU;
    rt_spin_lock_init(&pin_bank->spinlock);

    pin_bank->parent.ops = &rk_pin_ops;
    pin_api_init(&pin_bank->parent, 32);
    pin_pic_init(&pin_bank->parent, pin_bank->irq);

    rt_ofw_data(np) = &pin_bank->parent;

    return RT_EOK;

_out_res:
    if (pin_bank->reg_base)
    {
        rt_iounmap(pin_bank->reg_base);
    }

    if (rt_is_err_or_null(pin_bank->clk))
    {
        rt_clk_disable_unprepare(pin_bank->clk);
        rt_clk_put(pin_bank->clk);
    }

    if (rt_is_err_or_null(pin_bank->db_clk))
    {
        rt_clk_disable_unprepare(pin_bank->db_clk);
        rt_clk_put(pin_bank->db_clk);
    }

    return err;
}

static const struct rt_ofw_node_id rockchip_gpio_ofw_ids[] =
{
    { .compatible = "rockchip,gpio-bank" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_gpio_driver =
{
    .name = "rockchip-gpio",
    .ids = rockchip_gpio_ofw_ids,

    .probe = rockchip_gpio_probe,
};

static int rockchip_gpio_register(void)
{
    rt_platform_driver_register(&rockchip_gpio_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rockchip_gpio_register);
