/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pinctrl.single"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define EDGE_CLEAR      6
#define EDGE_FALL_EN    5
#define EDGE_RISE_EN    4

#define PCS_F_AIB       RT_BIT(0)

struct pcs_func_vals
{
    void *reg;
    rt_uint32_t val;
    rt_uint32_t mask;
};

struct pcs_soc_data
{
    rt_uint32_t flags;
};

struct pcs_device
{
    struct rt_device_pin parent;

    struct rt_clk *psc_clk;
    struct rt_reset_control *psc_rstc;

    void *base;
    void *gedge_flag_base;
    rt_size_t size;
    rt_uint32_t width;
    rt_uint32_t fmask;
    rt_uint32_t pinctrl_argc;
    rt_bool_t bits_per_mux;

    struct rt_spinlock lock;

    unsigned (*read)(void *reg);
    void (*write)(void *reg, unsigned val);

    const struct pcs_soc_data *soc_data;
};

#define raw_to_pcs_device(raw) rt_container_of(raw, struct pcs_device, parent)

static unsigned pcs_readb(void *reg)
{
    return HWREG8(reg);
}

static unsigned pcs_readw(void *reg)
{
    return HWREG16(reg);
}

static unsigned pcs_readl(void *reg)
{
    return HWREG32(reg);
}

static void pcs_writeb(void *reg, unsigned val)
{
    HWREG8(reg) = val;
}

static void pcs_writew(void *reg, unsigned val)
{
    HWREG16(reg) = val;
}

static void pcs_writel(void *reg, unsigned val)
{
    HWREG32(reg) = val;
}

static void pcs_confs_apply_once(struct pcs_device *pcs, struct pcs_func_vals *vals)
{
    rt_ubase_t level;
    unsigned val, mask;

    level = rt_spin_lock_irqsave(&pcs->lock);

    val = pcs->read(vals->reg);

    if (pcs->bits_per_mux)
    {
        mask = vals->mask;
    }
    else
    {
        mask = pcs->fmask;
    }

    val &= ~mask;
    val |= (vals->val & mask);
    pcs->write(vals->reg, val);

    rt_spin_unlock_irqrestore(&pcs->lock, level);
}

static rt_err_t pcs_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    rt_uint32_t value;
    const fdt32_t *cell;
    struct pcs_func_vals vals;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *conf_np = fw_conf_np;
    struct pcs_device *pcs = raw_to_pcs_device(device);

    rt_ofw_foreach_prop_u32(conf_np, "pinctrl-single,pins", prop, cell, value)
    {
        vals.reg = pcs->base + value;

        cell = rt_ofw_prop_next_u32(prop, cell, &value);
        vals.val = value;

        if (pcs->pinctrl_argc == 3)
        {
            cell = rt_ofw_prop_next_u32(prop, cell, &value);

            if (pcs->bits_per_mux)
            {
                vals.mask = value;
            }
            else
            {
                vals.val |= value;
                vals.mask = pcs->fmask;
            }
        }
        else
        {
            vals.mask = 0;
        }

        pcs_confs_apply_once(pcs, &vals);
    }

    return RT_EOK;
}

static rt_err_t pcs_gpio_request(struct rt_device *device, rt_base_t gpio, rt_uint32_t flags)
{
    rt_base_t gpio_start;
    struct pcs_func_vals vals;
    struct rt_ofw_cell_args gpio_range;
    struct rt_ofw_node *np = device->ofw_node;
    struct pcs_device *pcs = raw_to_pcs_device(device);

    for (int i = 0;; ++i)
    {
        if (rt_ofw_parse_phandle_cells(np, "pinctrl-single,gpio-range",
            "#pinctrl-single,gpio-range-cells", i, &gpio_range))
        {
            break;
        }

        gpio_start = gpio_range.args[0];

        if (gpio < gpio_start || gpio >= gpio_start + gpio_range.args[1])
        {
            rt_ofw_node_put(gpio_range.data);
            continue;
        }

        vals.reg = pcs->base + gpio * (pcs->width / 8);
        vals.val = gpio_range.args[2];
        vals.mask = pcs->fmask;

        pcs_confs_apply_once(pcs, &vals);

        rt_ofw_node_put(gpio_range.data);
        break;
    }

    return RT_EOK;
}

static const struct rt_pin_ops pcs_ops =
{
    .pin_ctrl_confs_apply = pcs_confs_apply,
    .pin_ctrl_gpio_request = pcs_gpio_request,
};

static rt_err_t pcs_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t address, size;
    struct rt_device *dev = &pdev->parent;
    struct pcs_device *pcs = rt_calloc(1, sizeof(*pcs));

    if (!pcs)
    {
        return -RT_ENOMEM;
    }
    pcs->soc_data = pdev->id->data;

    if ((err = rt_dm_dev_get_address(dev, 0, &address, &size)))
    {
        goto _fail;
    }

    pcs->size = size;
    pcs->base = rt_ioremap((void *)address, size);
    if (!pcs->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    pcs->psc_rstc = rt_reset_control_get_by_name(dev, "aib_rst");
    if (rt_is_err(pcs->psc_rstc))
    {
        err = rt_ptr_err(pcs->psc_rstc);
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(pcs->psc_rstc)))
    {
        goto _fail;
    }

    pcs->psc_clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(pcs->psc_clk))
    {
        err = rt_ptr_err(pcs->psc_clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(pcs->psc_clk)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "#pinctrl-cells", &pcs->pinctrl_argc)))
    {
        goto _fail;
    }
    ++pcs->pinctrl_argc;

    if ((err = rt_dm_dev_prop_read_u32(dev, "pinctrl-single,register-width", &pcs->width)))
    {
        goto _fail;
    }

    rt_dm_dev_prop_read_u32(dev, "pinctrl-single,function-mask", &pcs->fmask);

    pcs->bits_per_mux = rt_dm_dev_prop_read_bool(dev, "pinctrl-single,bit-per-mux");

    if (pcs->soc_data->flags & PCS_F_AIB)
    {
        if (!(pcs->gedge_flag_base = rt_dm_dev_iomap(dev, 1)))
        {
            err = -RT_EIO;
            goto _fail;
        }
    }

    switch (pcs->width)
    {
    case 8:
        pcs->read = pcs_readb;
        pcs->write = pcs_writeb;
        break;
    case 16:
        pcs->read = pcs_readw;
        pcs->write = pcs_writew;
        break;
    case 32:
        pcs->read = pcs_readl;
        pcs->write = pcs_writel;
        break;
    default:
        err = -RT_EINVAL;
        goto _fail;
    }

    if (pcs->soc_data->flags & PCS_F_AIB)
    {
        unsigned regval;
        void *base = pcs->base + 4;

        for (int i = 4; i < pcs->size; i += 4, base += 4)
        {
            regval = pcs->read(base);
            regval |= (1 << EDGE_CLEAR);
            regval &= ~(1 << EDGE_FALL_EN);
            regval &= ~(1 << EDGE_RISE_EN);
            pcs->write(base, regval);
        }
    }

    rt_spin_lock_init(&pcs->lock);

    pcs->parent.ops = &pcs_ops;
    pcs->parent.parent.ofw_node = dev->ofw_node;

    rt_ofw_data(dev->ofw_node) = &pcs->parent;

    return RT_EOK;

_fail:
    if (pcs->base)
    {
        rt_iounmap(pcs->base);
    }

    if (!rt_is_err_or_null(pcs->psc_rstc))
    {
        rt_reset_control_assert(pcs->psc_rstc);
        rt_reset_control_put(pcs->psc_rstc);
    }

    if (!rt_is_err_or_null(pcs->psc_clk))
    {
        rt_clk_put(pcs->psc_clk);
    }

    if (pcs->soc_data->flags & PCS_F_AIB)
    {
        if (pcs->gedge_flag_base)
        {
            rt_iounmap(pcs->gedge_flag_base);
        }
    }

    rt_free(pcs);

    return err;
}

static const struct pcs_soc_data pinctrl_single =
{
};

static const struct pcs_soc_data pinconf_single_aib =
{
    .flags = PCS_F_AIB,
};

static const struct rt_ofw_node_id pcs_ofw_ids[] =
{
    { .compatible = "ti,am437-padconf", .data = &pinctrl_single },
    { .compatible = "ti,am654-padconf", .data = &pinctrl_single },
    { .compatible = "ti,dra7-padconf", .data = &pinctrl_single },
    { .compatible = "ti,omap3-padconf", .data = &pinctrl_single },
    { .compatible = "ti,omap4-padconf", .data = &pinctrl_single },
    { .compatible = "ti,omap5-padconf", .data = &pinctrl_single },
    { .compatible = "pinctrl-single", .data = &pinctrl_single },
    { .compatible = "pinconf-single", .data = &pinctrl_single },
    { .compatible = "pinconf-single-aib", .data = &pinconf_single_aib },
    { /* sentinel */ }
};

static struct rt_platform_driver pcs_driver =
{
    .name = "pinctrl-single",
    .ids = pcs_ofw_ids,

    .probe = pcs_probe,
};

static int pcs_register(void)
{
    rt_platform_driver_register(&pcs_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(pcs_register);
