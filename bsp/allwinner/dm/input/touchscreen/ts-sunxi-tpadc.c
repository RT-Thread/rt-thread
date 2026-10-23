/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "input.ts.sunxi-tpadc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_TPADC_CTRL0             0x00
#define SUNXI_TPADC_CTRL1             0x04
#define SUNXI_TPADC_CTRL2             0x08
#define SUNXI_TPADC_CTRL3             0x0c
#define SUNXI_TPADC_FIFO_CTRL         0x10
#define SUNXI_TPADC_FIFO_STATUS       0x14
#define SUNXI_TPADC_DATA              0x24

#define SUNXI_TPADC_CTRL1_CALIBRATE   RT_BIT(7)
#define SUNXI_TPADC_CTRL1_ENABLE      RT_BIT(5)
#define SUNXI_TPADC_FIFO_FLUSH        RT_BIT(4)
#define SUNXI_TPADC_FIFO_DOWN_IRQ     RT_BIT(0)
#define SUNXI_TPADC_FIFO_UP_IRQ       RT_BIT(1)
#define SUNXI_TPADC_FIFO_DATA_IRQ     RT_BIT(16)
#define SUNXI_TPADC_FIFO_OVERRUN_IRQ  RT_BIT(17)
#define SUNXI_TPADC_FIFO_TRIGGER      (1U << 8)
#define SUNXI_TPADC_STATUS_UP         RT_BIT(1)
#define SUNXI_TPADC_STATUS_DATA       RT_BIT(16)
#define SUNXI_TPADC_STATUS_OVERRUN    RT_BIT(17)
#define SUNXI_TPADC_DATA_MASK         RT_GENMASK(11, 0)

struct sunxi_tpadc
{
    struct rt_input_device parent;

    void *regs;
    struct rt_clk *mod_clk;
    struct rt_clk *bus_clk;
    struct rt_reset_control *reset;
    int irq;
    rt_bool_t mod_clk_enabled;
    rt_bool_t bus_clk_enabled;
    rt_bool_t irq_attached;
    rt_bool_t input_registered;
    rt_bool_t touch_down;
};

static void sunxi_tpadc_report_up(struct sunxi_tpadc *tpadc)
{
    if (!tpadc->touch_down)
    {
        return;
    }

    rt_input_report_touch_inactive(&tpadc->parent, RT_FALSE);
    rt_input_report_key(&tpadc->parent, BTN_TOUCH, RT_FALSE);
    rt_input_sync(&tpadc->parent);
    tpadc->touch_down = RT_FALSE;
}

static void sunxi_tpadc_isr(int irq, void *param)
{
    rt_uint32_t status;
    rt_uint32_t x;
    rt_uint32_t y;
    struct sunxi_tpadc *tpadc = param;

    RT_UNUSED(irq);

    status = HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_STATUS);
    if (status & SUNXI_TPADC_STATUS_DATA)
    {
        x = HWREG32(tpadc->regs + SUNXI_TPADC_DATA) & SUNXI_TPADC_DATA_MASK;
        y = HWREG32(tpadc->regs + SUNXI_TPADC_DATA) & SUNXI_TPADC_DATA_MASK;

        if (!tpadc->touch_down)
        {
            rt_input_report_key(&tpadc->parent, BTN_TOUCH, RT_TRUE);
            tpadc->touch_down = RT_TRUE;
        }

        rt_input_report_touch_inactive(&tpadc->parent, RT_TRUE);
        rt_input_report_touch_position(&tpadc->parent, x, y, RT_FALSE);
        rt_input_sync(&tpadc->parent);
    }

    if (status & SUNXI_TPADC_STATUS_UP)
    {
        sunxi_tpadc_report_up(tpadc);
    }

    if (status & SUNXI_TPADC_STATUS_OVERRUN)
    {
        LOG_W("touch FIFO overrun");
    }

    HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_STATUS) = status;
}

static rt_err_t sunxi_tpadc_calibrate(struct sunxi_tpadc *tpadc)
{
    rt_uint32_t timeout;

    HWREG32(tpadc->regs + SUNXI_TPADC_CTRL1) |= SUNXI_TPADC_CTRL1_CALIBRATE;
    for (timeout = 0; timeout < 1000; ++timeout)
    {
        if (!(HWREG32(tpadc->regs + SUNXI_TPADC_CTRL1) &
                SUNXI_TPADC_CTRL1_CALIBRATE))
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t sunxi_tpadc_start(struct sunxi_tpadc *tpadc)
{
    rt_err_t err;
    rt_uint32_t fifo_ctrl;

    HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_CTRL) = SUNXI_TPADC_FIFO_FLUSH;
    HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_STATUS) = RT_UINT32_MAX;

    if ((err = sunxi_tpadc_calibrate(tpadc)))
    {
        return err;
    }

    /* 24 MHz source, 2 us acquisition time, and 1 kHz sample interval. */
    HWREG32(tpadc->regs + SUNXI_TPADC_CTRL0) = 149 | (8U << 16) |
            (3U << 20) | RT_BIT(23) | (15U << 24);
    HWREG32(tpadc->regs + SUNXI_TPADC_CTRL1) = SUNXI_TPADC_CTRL1_ENABLE;
    HWREG32(tpadc->regs + SUNXI_TPADC_CTRL2) = 0x800fff | RT_BIT(24) |
            (15U << 28);
    HWREG32(tpadc->regs + SUNXI_TPADC_CTRL3) = 1 | RT_BIT(2);

    fifo_ctrl = SUNXI_TPADC_FIFO_DOWN_IRQ | SUNXI_TPADC_FIFO_UP_IRQ |
            SUNXI_TPADC_FIFO_DATA_IRQ | SUNXI_TPADC_FIFO_OVERRUN_IRQ |
            SUNXI_TPADC_FIFO_TRIGGER;
    HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_CTRL) = fifo_ctrl;
    HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_STATUS) = RT_UINT32_MAX;

    return RT_EOK;
}

static rt_err_t sunxi_tpadc_release(struct sunxi_tpadc *tpadc)
{
    rt_err_t err;

    if (tpadc->input_registered)
    {
        err = rt_input_device_unregister(&tpadc->parent);
        if (err)
        {
            return err;
        }
        tpadc->input_registered = RT_FALSE;
    }
    else
    {
        rt_input_remove_config(&tpadc->parent);
    }

    if (tpadc->irq_attached)
    {
        rt_pic_irq_disable(tpadc->irq);
        rt_pic_detach_irq(tpadc->irq, tpadc);
    }
    if (tpadc->regs)
    {
        HWREG32(tpadc->regs + SUNXI_TPADC_FIFO_CTRL) = 0;
        HWREG32(tpadc->regs + SUNXI_TPADC_CTRL1) = 0;
    }
    if (!rt_is_err_or_null(tpadc->reset))
    {
        rt_reset_control_assert(tpadc->reset);
        rt_reset_control_put(tpadc->reset);
    }
    if (tpadc->mod_clk_enabled)
    {
        rt_clk_disable_unprepare(tpadc->mod_clk);
    }
    if (tpadc->bus_clk_enabled)
    {
        rt_clk_disable_unprepare(tpadc->bus_clk);
    }
    if (!rt_is_err_or_null(tpadc->mod_clk))
    {
        rt_clk_put(tpadc->mod_clk);
    }
    if (!rt_is_err_or_null(tpadc->bus_clk))
    {
        rt_clk_put(tpadc->bus_clk);
    }
    if (tpadc->regs)
    {
        rt_iounmap(tpadc->regs);
    }
    rt_free(tpadc);

    return RT_EOK;
}

static rt_err_t sunxi_tpadc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_touch_info touch_info = {};
    struct rt_device *dev = &pdev->parent;
    struct sunxi_tpadc *tpadc = rt_calloc(1, sizeof(*tpadc));

    if (!tpadc)
    {
        return -RT_ENOMEM;
    }

    tpadc->regs = rt_dm_dev_iomap(dev, 0);
    if (!tpadc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    tpadc->mod_clk = rt_clk_get_by_name(dev, "mod");
    tpadc->bus_clk = rt_clk_get_by_name(dev, "bus");
    tpadc->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err_or_null(tpadc->mod_clk) ||
            rt_is_err_or_null(tpadc->bus_clk) ||
            rt_is_err_or_null(tpadc->reset))
    {
        err = rt_is_err(tpadc->mod_clk) ? rt_ptr_err(tpadc->mod_clk) :
                (rt_is_err(tpadc->bus_clk) ? rt_ptr_err(tpadc->bus_clk) :
                (rt_is_err(tpadc->reset) ? rt_ptr_err(tpadc->reset) : -RT_ENOENT));
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(tpadc->reset)) ||
            (err = rt_clk_prepare_enable(tpadc->mod_clk)))
    {
        goto _fail;
    }
    tpadc->mod_clk_enabled = RT_TRUE;
    if ((err = rt_clk_prepare_enable(tpadc->bus_clk)))
    {
        goto _fail;
    }
    tpadc->bus_clk_enabled = RT_TRUE;

    if ((tpadc->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = tpadc->irq;
        goto _fail;
    }

    tpadc->parent.parent.ofw_node = dev->ofw_node;
    if ((err = rt_input_set_capability(&tpadc->parent, EV_KEY, BTN_TOUCH)) ||
            (err = rt_input_set_capability(&tpadc->parent, EV_ABS, ABS_X)) ||
            (err = rt_input_set_capability(&tpadc->parent, EV_ABS, ABS_Y)))
    {
        goto _fail;
    }
    rt_input_set_absinfo(&tpadc->parent, ABS_X, 0, 4095, 0, 0);
    rt_input_set_absinfo(&tpadc->parent, ABS_Y, 0, 4095, 0, 0);

    touch_info.type = RT_TOUCH_TYPE_RESISTANCE;
    touch_info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    if ((err = rt_input_setup_touch(&tpadc->parent, 0, &touch_info)))
    {
        goto _fail;
    }
    if ((err = rt_input_device_register(&tpadc->parent)))
    {
        goto _fail;
    }
    tpadc->input_registered = RT_TRUE;

    if ((err = rt_pic_attach_irq(tpadc->irq, sunxi_tpadc_isr, tpadc,
            "tpadc", RT_IRQ_F_NONE)))
    {
        goto _fail;
    }
    tpadc->irq_attached = RT_TRUE;

    if ((err = sunxi_tpadc_start(tpadc)))
    {
        goto _fail;
    }
    rt_pic_irq_enable(tpadc->irq);

    dev->user_data = tpadc;

    return RT_EOK;

_fail:
    sunxi_tpadc_release(tpadc);
    return err;
}

static rt_err_t sunxi_tpadc_remove(struct rt_platform_device *pdev)
{
    struct sunxi_tpadc *tpadc = pdev->parent.user_data;

    return sunxi_tpadc_release(tpadc);
}

static const struct rt_ofw_node_id sunxi_tpadc_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-tpadc" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_tpadc_driver =
{
    .name = "sunxi-tpadc",
    .ids = sunxi_tpadc_ofw_ids,
    .probe = sunxi_tpadc_probe,
    .remove = sunxi_tpadc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_tpadc_driver);
