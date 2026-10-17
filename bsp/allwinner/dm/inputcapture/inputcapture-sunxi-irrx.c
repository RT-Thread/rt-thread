/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "inputcap.sunxi-irrx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_IRRX_CTRL                 0x00
#define SUNXI_IRRX_RXCTRL               0x10
#define SUNXI_IRRX_RXFIFO               0x20
#define SUNXI_IRRX_RXINT                0x2c
#define SUNXI_IRRX_RXSTA                0x30
#define SUNXI_IRRX_CONFIG               0x34

#define SUNXI_IRRX_GEN                  RT_BIT(0)
#define SUNXI_IRRX_RXEN                 RT_BIT(1)
#define SUNXI_IRRX_ENABLE               RT_GENMASK(5, 4)
#define SUNXI_IRRX_MODE_BOTH            (1U << 6)
#define SUNXI_IRRX_POLARITY_INVERT      RT_BIT(2)

#define SUNXI_IRRX_IRQ_OVERRUN          RT_BIT(0)
#define SUNXI_IRRX_IRQ_PACKET_END       RT_BIT(1)
#define SUNXI_IRRX_IRQ_AVAILABLE        RT_BIT(4)
#define SUNXI_IRRX_IRQ_ENABLE           RT_GENMASK(5, 0)
#define SUNXI_IRRX_FIFO_LEVEL(n)        (((n) - 1U) << 8)
#define SUNXI_IRRX_FIFO_COUNT(v)        (((v) >> 8) & 0x7f)

#define SUNXI_IRRX_SAMPLE_DIV           256U
#define SUNXI_IRRX_SAMPLE_CLOCK_MHZ     24U

struct sunxi_irrx
{
    struct rt_inputcapture_device parent;

    void *regs;
    struct rt_clk *mod_clk;
    struct rt_clk *bus_clk;
    struct rt_reset_control *reset;
    int irq;
    rt_uint32_t pulse_cycles;
    rt_uint32_t pulsewidth_us;
    rt_bool_t pulse_level;
    rt_bool_t pulse_pending;
    rt_bool_t mod_clk_enabled;
    rt_bool_t bus_clk_enabled;
    rt_bool_t irq_attached;
    rt_bool_t opened;
};

#define raw_to_sunxi_irrx(raw) \
    rt_container_of(raw, struct sunxi_irrx, parent)

static rt_uint32_t sunxi_irrx_cycles_to_us(rt_uint32_t cycles)
{
    rt_uint64_t value;

    value = (rt_uint64_t)cycles * SUNXI_IRRX_SAMPLE_DIV;

    return (rt_uint32_t)((value + SUNXI_IRRX_SAMPLE_CLOCK_MHZ / 2U) /
            SUNXI_IRRX_SAMPLE_CLOCK_MHZ);
}

static rt_err_t sunxi_irrx_get_pulsewidth(
        struct rt_inputcapture_device *inputcapture,
        rt_uint32_t *pulsewidth_us)
{
    struct sunxi_irrx *irrx = raw_to_sunxi_irrx(inputcapture);

    *pulsewidth_us = irrx->pulsewidth_us;

    return RT_EOK;
}

static void sunxi_irrx_report(struct sunxi_irrx *irrx)
{
    if (!irrx->pulse_pending)
    {
        return;
    }

    irrx->pulsewidth_us = sunxi_irrx_cycles_to_us(irrx->pulse_cycles);
    rt_hw_inputcapture_isr(&irrx->parent, irrx->pulse_level);
    irrx->pulse_cycles = 0;
    irrx->pulse_pending = RT_FALSE;
}

static void sunxi_irrx_store_sample(struct sunxi_irrx *irrx,
        rt_uint8_t sample)
{
    rt_bool_t level = (sample & RT_BIT(7)) != 0;
    rt_uint32_t cycles = sample & RT_GENMASK(6, 0);

    if (!cycles)
    {
        return;
    }

    if (irrx->pulse_pending && irrx->pulse_level == level)
    {
        irrx->pulse_cycles += cycles;
        return;
    }

    sunxi_irrx_report(irrx);
    irrx->pulse_cycles = cycles;
    irrx->pulse_level = level;
    irrx->pulse_pending = RT_TRUE;
}

static void sunxi_irrx_isr(int irq, void *param)
{
    rt_uint32_t count;
    rt_uint32_t i;
    rt_uint32_t status;
    struct sunxi_irrx *irrx = param;

    RT_UNUSED(irq);

    status = HWREG32(irrx->regs + SUNXI_IRRX_RXSTA);
    count = SUNXI_IRRX_FIFO_COUNT(status);
    for (i = 0; i < count; ++i)
    {
        sunxi_irrx_store_sample(irrx,
                HWREG32(irrx->regs + SUNXI_IRRX_RXFIFO));
    }

    if (status & SUNXI_IRRX_IRQ_PACKET_END)
    {
        sunxi_irrx_report(irrx);
    }
    if (status & SUNXI_IRRX_IRQ_OVERRUN)
    {
        LOG_W("receive FIFO overrun");
        irrx->pulse_cycles = 0;
        irrx->pulse_pending = RT_FALSE;
    }

    HWREG32(irrx->regs + SUNXI_IRRX_RXSTA) = status;
}

static rt_err_t sunxi_irrx_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t err;
    struct sunxi_irrx *irrx = raw_to_sunxi_irrx(inputcapture);

    if (irrx->opened)
    {
        return RT_EOK;
    }

    if ((err = rt_reset_control_deassert(irrx->reset)))
    {
        return err;
    }
    if ((err = rt_clk_prepare_enable(irrx->mod_clk)))
    {
        goto _assert_reset;
    }
    irrx->mod_clk_enabled = RT_TRUE;
    if ((err = rt_clk_prepare_enable(irrx->bus_clk)))
    {
        goto _disable_mod_clk;
    }
    irrx->bus_clk_enabled = RT_TRUE;

    irrx->pulse_cycles = 0;
    irrx->pulse_pending = RT_FALSE;
    HWREG32(irrx->regs + SUNXI_IRRX_CTRL) = 0;
    HWREG32(irrx->regs + SUNXI_IRRX_RXINT) = 0;
    HWREG32(irrx->regs + SUNXI_IRRX_RXSTA) = RT_UINT32_MAX;
    HWREG32(irrx->regs + SUNXI_IRRX_CONFIG) = 2U | (32U << 2) |
            (11U << 8) | (32U << 16);
    HWREG32(irrx->regs + SUNXI_IRRX_RXCTRL) = SUNXI_IRRX_POLARITY_INVERT;
    HWREG32(irrx->regs + SUNXI_IRRX_RXINT) = SUNXI_IRRX_IRQ_OVERRUN |
            SUNXI_IRRX_IRQ_PACKET_END | SUNXI_IRRX_IRQ_AVAILABLE |
            SUNXI_IRRX_FIFO_LEVEL(20);
    HWREG32(irrx->regs + SUNXI_IRRX_CTRL) = SUNXI_IRRX_GEN |
            SUNXI_IRRX_RXEN | SUNXI_IRRX_ENABLE | SUNXI_IRRX_MODE_BOTH;
    irrx->opened = RT_TRUE;
    rt_pic_irq_unmask(irrx->irq);

    return RT_EOK;

_disable_mod_clk:
    rt_clk_disable_unprepare(irrx->mod_clk);
    irrx->mod_clk_enabled = RT_FALSE;
_assert_reset:
    rt_reset_control_assert(irrx->reset);

    return err;
}

static rt_err_t sunxi_irrx_close(struct rt_inputcapture_device *inputcapture)
{
    struct sunxi_irrx *irrx = raw_to_sunxi_irrx(inputcapture);

    if (!irrx->opened)
    {
        return RT_EOK;
    }

    rt_pic_irq_mask(irrx->irq);
    HWREG32(irrx->regs + SUNXI_IRRX_RXINT) = 0;
    HWREG32(irrx->regs + SUNXI_IRRX_CTRL) = 0;
    rt_reset_control_assert(irrx->reset);
    if (irrx->bus_clk_enabled)
    {
        rt_clk_disable_unprepare(irrx->bus_clk);
        irrx->bus_clk_enabled = RT_FALSE;
    }
    if (irrx->mod_clk_enabled)
    {
        rt_clk_disable_unprepare(irrx->mod_clk);
        irrx->mod_clk_enabled = RT_FALSE;
    }
    irrx->pulse_cycles = 0;
    irrx->pulse_pending = RT_FALSE;
    irrx->opened = RT_FALSE;

    return RT_EOK;
}

static const struct rt_inputcapture_ops sunxi_irrx_ops =
{
    .open = sunxi_irrx_open,
    .close = sunxi_irrx_close,
    .get_pulsewidth = sunxi_irrx_get_pulsewidth,
};

static void sunxi_irrx_release(struct sunxi_irrx *irrx)
{
    if (irrx->opened)
    {
        sunxi_irrx_close(&irrx->parent);
    }
    if (irrx->irq_attached)
    {
        rt_pic_irq_disable(irrx->irq);
        rt_pic_detach_irq(irrx->irq, irrx);
    }
    if (!rt_is_err_or_null(irrx->reset))
    {
        rt_reset_control_put(irrx->reset);
    }
    if (!rt_is_err_or_null(irrx->mod_clk))
    {
        rt_clk_put(irrx->mod_clk);
    }
    if (!rt_is_err_or_null(irrx->bus_clk))
    {
        rt_clk_put(irrx->bus_clk);
    }
    if (irrx->regs)
    {
        rt_iounmap(irrx->regs);
    }
    rt_free(irrx);
}

static rt_err_t sunxi_irrx_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_irrx *irrx = rt_calloc(1, sizeof(*irrx));

    if (!irrx)
    {
        return -RT_ENOMEM;
    }

    irrx->regs = rt_dm_dev_iomap(dev, 0);
    if (!irrx->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    irrx->mod_clk = rt_clk_get_by_name(dev, "mod");
    irrx->bus_clk = rt_clk_get_by_name(dev, "bus");
    irrx->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err_or_null(irrx->mod_clk) ||
            rt_is_err_or_null(irrx->bus_clk) ||
            rt_is_err_or_null(irrx->reset))
    {
        err = rt_is_err(irrx->mod_clk) ? rt_ptr_err(irrx->mod_clk) :
                (rt_is_err(irrx->bus_clk) ? rt_ptr_err(irrx->bus_clk) :
                (rt_is_err(irrx->reset) ? rt_ptr_err(irrx->reset) : -RT_ENOENT));
        goto _fail;
    }

    irrx->irq = rt_dm_dev_get_irq(dev, 0);
    if (irrx->irq < 0)
    {
        err = irrx->irq;
        goto _fail;
    }
    if ((err = rt_pic_attach_irq(irrx->irq, sunxi_irrx_isr, irrx,
            "irrx", RT_IRQ_F_NONE)))
    {
        goto _fail;
    }
    irrx->irq_attached = RT_TRUE;
    rt_pic_irq_mask(irrx->irq);

    name = rt_dm_dev_get_name(dev);
    irrx->parent.ops = &sunxi_irrx_ops;
    if ((err = rt_device_inputcapture_register(&irrx->parent, name, irrx)))
    {
        goto _fail;
    }

    dev->user_data = irrx;

    return RT_EOK;

_fail:
    sunxi_irrx_release(irrx);
    return err;
}

static const struct rt_ofw_node_id sunxi_irrx_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-irrx" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_irrx_driver =
{
    .name = "sunxi-irrx",
    .ids = sunxi_irrx_ofw_ids,
    .probe = sunxi_irrx_probe,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_irrx_driver);
