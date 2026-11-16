/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "input.sunxi-lradc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define LRADC_CTRL                     0x00
#define LRADC_INTC                     0x04
#define LRADC_INTS                     0x08
#define LRADC_DATA0                    0x0c

#define LRADC_FIRST_CONVERT_DLY(n)     ((n) << 24)
#define LRADC_LEVELA_B_CNT(n)          ((n) << 8)
#define LRADC_HOLD_EN                  RT_BIT(6)
#define LRADC_SAMPLE_RATE(n)           ((n) << 2)
#define LRADC_ENABLE                   RT_BIT(0)

#define LRADC_CHAN0_KEYUP              RT_BIT(4)
#define LRADC_CHAN0_KEYDOWN            RT_BIT(1)
#define LRADC_DATA_MASK                RT_GENMASK(5, 0)
#define LRADC_DATA_MAX                 63U
#define LRADC_DEFAULT_VREF_MV          1800U

struct sunxi_lradc_key
{
    rt_uint32_t voltage_mv;
    rt_uint32_t code;
};

struct sunxi_lradc
{
    struct rt_input_device parent;

    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *reset;
    struct sunxi_lradc_key *keys;
    int irq;
    rt_uint32_t keys_nr;
    rt_uint32_t vref_mv;
    rt_uint32_t pressed_code;
    rt_bool_t clk_enabled;
    rt_bool_t irq_attached;
    rt_bool_t registered;
};

static rt_uint32_t sunxi_lradc_find_key(struct sunxi_lradc *lradc,
        rt_uint32_t voltage_mv)
{
    rt_uint32_t key = 0;
    rt_uint32_t closest = RT_UINT32_MAX;
    rt_uint32_t index;

    for (index = 0; index < lradc->keys_nr; ++index)
    {
        rt_uint32_t expected = lradc->keys[index].voltage_mv;
        rt_uint32_t difference = expected > voltage_mv ?
                expected - voltage_mv : voltage_mv - expected;

        if (difference < closest)
        {
            closest = difference;
            key = lradc->keys[index].code;
        }
    }

    return key;
}

static void sunxi_lradc_isr(int irq, void *param)
{
    rt_uint32_t status;
    struct sunxi_lradc *lradc = param;

    RT_UNUSED(irq);

    status = HWREG32(lradc->base + LRADC_INTS);
    if (status & LRADC_CHAN0_KEYUP)
    {
        if (lradc->pressed_code)
        {
            rt_input_report_key(&lradc->parent, lradc->pressed_code, 0);
            rt_input_sync(&lradc->parent);
            lradc->pressed_code = 0;
        }
    }
    if ((status & LRADC_CHAN0_KEYDOWN) && !lradc->pressed_code)
    {
        rt_uint32_t sample = HWREG32(lradc->base + LRADC_DATA0) &
                LRADC_DATA_MASK;
        rt_uint32_t voltage_mv = sample * lradc->vref_mv / LRADC_DATA_MAX;

        lradc->pressed_code = sunxi_lradc_find_key(lradc, voltage_mv);
        if (lradc->pressed_code)
        {
            rt_input_report_key(&lradc->parent, lradc->pressed_code, 1);
            rt_input_sync(&lradc->parent);
        }
    }

    HWREG32(lradc->base + LRADC_INTS) = status;
}

static void sunxi_lradc_release(struct sunxi_lradc *lradc)
{
    if (lradc->base)
    {
        HWREG32(lradc->base + LRADC_INTC) = 0;
        HWREG32(lradc->base + LRADC_CTRL) = 0;
    }
    if (lradc->irq_attached)
    {
        rt_pic_irq_mask(lradc->irq);
        rt_pic_detach_irq(lradc->irq, lradc);
    }
    if (lradc->registered)
    {
        rt_input_device_unregister(&lradc->parent);
    }
    if (lradc->clk_enabled)
    {
        rt_clk_disable_unprepare(lradc->clk);
    }
    if (!rt_is_err_or_null(lradc->reset))
    {
        rt_reset_control_assert(lradc->reset);
        rt_reset_control_put(lradc->reset);
    }
    if (!rt_is_err_or_null(lradc->clk))
    {
        rt_clk_put(lradc->clk);
    }
    if (lradc->base)
    {
        rt_iounmap(lradc->base);
    }
    rt_free(lradc->keys);
    rt_free(lradc);
}

static rt_err_t sunxi_lradc_read_keymap(struct sunxi_lradc *lradc,
        struct rt_ofw_node *np)
{
    rt_uint32_t index = 0;
    struct rt_ofw_node *child;

    lradc->keys_nr = rt_ofw_get_child_count(np);
    if (!lradc->keys_nr)
    {
        return -RT_ENOENT;
    }
    lradc->keys = rt_calloc(lradc->keys_nr, sizeof(*lradc->keys));
    if (!lradc->keys)
    {
        return -RT_ENOMEM;
    }

    rt_ofw_foreach_available_child_node(np, child)
    {
        const char *code_prop;
        struct sunxi_lradc_key *key = &lradc->keys[index];

        if (rt_ofw_prop_read_u32(child, "voltage", &key->voltage_mv) ||
                !(code_prop = rt_ofw_get_prop_fuzzy_name(child, ",code$")) ||
                rt_ofw_prop_read_u32(child, code_prop, &key->code))
        {
            rt_ofw_node_put(child);
            return -RT_EINVAL;
        }
        if ((rt_uint64_t)key->voltage_mv * LRADC_DATA_MAX >
                (rt_uint64_t)lradc->vref_mv * 2U)
        {
            rt_ofw_node_put(child);
            return -RT_EINVAL;
        }
        rt_input_set_capability(&lradc->parent, EV_KEY, key->code);
        ++index;
    }

    lradc->keys_nr = index;
    return RT_EOK;
}

static rt_err_t sunxi_lradc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_lradc *lradc = rt_calloc(1, sizeof(*lradc));

    if (!lradc)
    {
        return -RT_ENOMEM;
    }
    lradc->base = rt_dm_dev_iomap(dev, 0);
    lradc->clk = rt_clk_get_by_name(dev, "bus");
    lradc->reset = rt_reset_control_get_by_name(dev, "bus");
    lradc->irq = rt_dm_dev_get_irq(dev, 0);
    if (!lradc->base || rt_is_err(lradc->clk) || rt_is_err(lradc->reset) ||
            lradc->irq < 0)
    {
        err = lradc->irq < 0 ? lradc->irq : -RT_EIO;
        goto _fail;
    }

    lradc->vref_mv = LRADC_DEFAULT_VREF_MV * 3U / 4U;
    rt_ofw_prop_read_u32(dev->ofw_node, "allwinner,vref-millivolt",
            &lradc->vref_mv);
    if ((err = sunxi_lradc_read_keymap(lradc, dev->ofw_node)))
    {
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(lradc->reset)) ||
            (err = rt_clk_prepare_enable(lradc->clk)))
    {
        goto _fail;
    }
    lradc->clk_enabled = RT_TRUE;

    if ((err = rt_pic_attach_irq(lradc->irq, sunxi_lradc_isr, lradc,
                    "sunxi-lradc", 0)))
    {
        goto _fail;
    }
    lradc->irq_attached = RT_TRUE;

    HWREG32(lradc->base + LRADC_INTS) = RT_UINT32_MAX;
    HWREG32(lradc->base + LRADC_CTRL) = LRADC_FIRST_CONVERT_DLY(2) |
            LRADC_LEVELA_B_CNT(1) | LRADC_HOLD_EN |
            LRADC_SAMPLE_RATE(0) | LRADC_ENABLE;
    HWREG32(lradc->base + LRADC_INTC) = LRADC_CHAN0_KEYUP |
            LRADC_CHAN0_KEYDOWN;
    rt_pic_irq_unmask(lradc->irq);

    if ((err = rt_dm_dev_set_name_auto(&lradc->parent.parent, "lradc")) ||
            (err = rt_input_device_register(&lradc->parent)))
    {
        goto _fail;
    }
    lradc->registered = RT_TRUE;
    name = rt_dm_dev_get_name(&lradc->parent.parent);
    LOG_I("%s: %u ladder key(s), %u mV reference", name,
            lradc->keys_nr, lradc->vref_mv);
    dev->user_data = lradc;

    return RT_EOK;

_fail:
    sunxi_lradc_release(lradc);
    return err;
}

static rt_err_t sunxi_lradc_remove(struct rt_platform_device *pdev)
{
    struct sunxi_lradc *lradc = pdev->parent.user_data;

    pdev->parent.user_data = RT_NULL;
    sunxi_lradc_release(lradc);
    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_lradc_ofw_ids[] =
{
    { .compatible = "allwinner,sun50i-h616-lradc" },
    { .compatible = "allwinner,sun50i-r329-lradc" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_lradc_driver =
{
    .name = "sunxi-lradc",
    .ids = sunxi_lradc_ofw_ids,
    .probe = sunxi_lradc_probe,
    .remove = sunxi_lradc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_lradc_driver);
