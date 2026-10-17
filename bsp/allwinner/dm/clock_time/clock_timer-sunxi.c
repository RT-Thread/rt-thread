/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "timer.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_TIMER_IRQ_EN             0x00
#define SUNXI_TIMER_IRQ_STA            0x04
#define SUNXI_TIMER_CTL(id)            (0x10 + (id) * 0x10)
#define SUNXI_TIMER_INTV(id)           (0x14 + (id) * 0x10)
#define SUNXI_TIMER_CNT(id)            (0x18 + (id) * 0x10)

#define SUNXI_TIMER_CTL_ENABLE         RT_BIT(0)
#define SUNXI_TIMER_CTL_RELOAD         RT_BIT(1)
#define SUNXI_TIMER_CTL_CLK_SRC_MASK   RT_GENMASK(3, 2)
#define SUNXI_TIMER_CTL_CLK_SRC_24M    (1U << 2)
#define SUNXI_TIMER_CTL_PRESCALE_MASK  RT_GENMASK(6, 4)
#define SUNXI_TIMER_CTL_ONESHOT        RT_BIT(7)

#define SUNXI_HSTIMER_IRQ_EN           0x00
#define SUNXI_HSTIMER_IRQ_STA          0x04
#define SUNXI_HSTIMER_CTL(id)          (0x20 + (id) * 0x20)
#define SUNXI_HSTIMER_INTV_LO(id)      (0x24 + (id) * 0x20)
#define SUNXI_HSTIMER_INTV_HI(id)      (0x28 + (id) * 0x20)
#define SUNXI_HSTIMER_CNT_LO(id)       (0x2c + (id) * 0x20)

#define SUNXI_HSTIMER_CTL_ENABLE       RT_BIT(0)
#define SUNXI_HSTIMER_CTL_RELOAD       RT_BIT(1)
#define SUNXI_HSTIMER_CTL_ONESHOT      RT_BIT(7)

#define SUNXI_TIMER_CHANNELS           2
#define SUNXI_TIMER_24M_FREQ           24000000U

enum sunxi_timer_kind
{
    SUNXI_TIMER,
    SUNXI_HSTIMER,
};

struct sunxi_timer_controller;

struct sunxi_timer_channel
{
    struct rt_clock_timer_device parent;

    struct sunxi_timer_controller *controller;
    int id;
    int irq;
    rt_bool_t registered;
    rt_bool_t irq_attached;
};

struct sunxi_timer_controller
{
    enum sunxi_timer_kind kind;
    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *reset;
    struct rt_clock_timer_info info;
    struct sunxi_timer_channel channels[SUNXI_TIMER_CHANNELS];
    rt_bool_t clk_enabled;
};

#define to_sunxi_timer_channel(raw) \
    rt_container_of(raw, struct sunxi_timer_channel, parent)

static void sunxi_timer_stop(struct sunxi_timer_channel *channel)
{
    rt_uint32_t value;
    struct sunxi_timer_controller *controller = channel->controller;

    if (controller->kind == SUNXI_TIMER)
    {
        value = HWREG32(controller->base + SUNXI_TIMER_CTL(channel->id));
        HWREG32(controller->base + SUNXI_TIMER_CTL(channel->id)) =
                value & ~SUNXI_TIMER_CTL_ENABLE;
    }
    else
    {
        value = HWREG32(controller->base + SUNXI_HSTIMER_CTL(channel->id));
        HWREG32(controller->base + SUNXI_HSTIMER_CTL(channel->id)) =
                value & ~SUNXI_HSTIMER_CTL_ENABLE;
    }
}

static void sunxi_clock_timer_init(struct rt_clock_timer_device *timer,
        rt_uint32_t state)
{
    rt_uint32_t mask;
    struct sunxi_timer_channel *channel = to_sunxi_timer_channel(timer);
    struct sunxi_timer_controller *controller = channel->controller;

    mask = RT_BIT(channel->id);
    sunxi_timer_stop(channel);

    if (controller->kind == SUNXI_TIMER)
    {
        HWREG32(controller->base + SUNXI_TIMER_IRQ_STA) = mask;
        if (state)
        {
            HWREG32(controller->base + SUNXI_TIMER_IRQ_EN) |= mask;
        }
        else
        {
            HWREG32(controller->base + SUNXI_TIMER_IRQ_EN) &= ~mask;
        }
    }
    else
    {
        HWREG32(controller->base + SUNXI_HSTIMER_IRQ_STA) = mask;
        if (state)
        {
            HWREG32(controller->base + SUNXI_HSTIMER_IRQ_EN) |= mask;
        }
        else
        {
            HWREG32(controller->base + SUNXI_HSTIMER_IRQ_EN) &= ~mask;
        }
    }
}

static rt_err_t sunxi_clock_timer_start(struct rt_clock_timer_device *timer,
        rt_uint32_t count, rt_clock_timer_mode_t mode)
{
    rt_uint32_t value;
    struct sunxi_timer_channel *channel = to_sunxi_timer_channel(timer);
    struct sunxi_timer_controller *controller = channel->controller;

    if (!count || (mode != CLOCK_TIMER_MODE_ONESHOT &&
            mode != CLOCK_TIMER_MODE_PERIOD))
    {
        return -RT_EINVAL;
    }

    sunxi_timer_stop(channel);

    if (controller->kind == SUNXI_TIMER)
    {
        HWREG32(controller->base + SUNXI_TIMER_INTV(channel->id)) = count;
        value = HWREG32(controller->base + SUNXI_TIMER_CTL(channel->id));
        value &= ~(SUNXI_TIMER_CTL_CLK_SRC_MASK |
                SUNXI_TIMER_CTL_PRESCALE_MASK | SUNXI_TIMER_CTL_ONESHOT);
        value |= SUNXI_TIMER_CTL_CLK_SRC_24M;
        if (mode == CLOCK_TIMER_MODE_ONESHOT)
        {
            value |= SUNXI_TIMER_CTL_ONESHOT;
        }
        HWREG32(controller->base + SUNXI_TIMER_CTL(channel->id)) =
                value | SUNXI_TIMER_CTL_ENABLE | SUNXI_TIMER_CTL_RELOAD;
    }
    else
    {
        HWREG32(controller->base + SUNXI_HSTIMER_INTV_HI(channel->id)) = 0;
        HWREG32(controller->base + SUNXI_HSTIMER_INTV_LO(channel->id)) = count;
        value = HWREG32(controller->base + SUNXI_HSTIMER_CTL(channel->id));
        value &= ~SUNXI_HSTIMER_CTL_ONESHOT;
        if (mode == CLOCK_TIMER_MODE_ONESHOT)
        {
            value |= SUNXI_HSTIMER_CTL_ONESHOT;
        }
        HWREG32(controller->base + SUNXI_HSTIMER_CTL(channel->id)) =
                value | SUNXI_HSTIMER_CTL_ENABLE | SUNXI_HSTIMER_CTL_RELOAD;
    }

    timer->cycles = count;
    timer->mode = mode;

    return RT_EOK;
}

static void sunxi_clock_timer_stop(struct rt_clock_timer_device *timer)
{
    sunxi_timer_stop(to_sunxi_timer_channel(timer));
}

static rt_uint32_t sunxi_clock_timer_count_get(struct rt_clock_timer_device *timer)
{
    struct sunxi_timer_channel *channel = to_sunxi_timer_channel(timer);
    struct sunxi_timer_controller *controller = channel->controller;

    if (controller->kind == SUNXI_TIMER)
    {
        return HWREG32(controller->base + SUNXI_TIMER_CNT(channel->id));
    }

    return HWREG32(controller->base + SUNXI_HSTIMER_CNT_LO(channel->id));
}

static rt_err_t sunxi_clock_timer_control(struct rt_clock_timer_device *timer,
        rt_uint32_t cmd, void *args)
{
    struct sunxi_timer_channel *channel = to_sunxi_timer_channel(timer);
    struct sunxi_timer_controller *controller = channel->controller;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
        if (!args || *(rt_int32_t *)args != timer->freq)
        {
            return -RT_ENOSYS;
        }
        return RT_EOK;

    case CLOCK_TIMER_CTRL_STOP:
        sunxi_timer_stop(channel);
        return RT_EOK;

    case CLOCK_TIMER_CTRL_INFO_GET:
        if (!args)
        {
            return -RT_EINVAL;
        }
        *(struct rt_clock_timer_info *)args = controller->info;
        return RT_EOK;

    case CLOCK_TIMER_CTRL_MODE_SET:
        return sunxi_clock_timer_start(timer, timer->cycles,
                (rt_clock_timer_mode_t)(rt_ubase_t)args);

    default:
        return -RT_ENOSYS;
    }
}

static const struct rt_clock_timer_ops sunxi_clock_timer_ops =
{
    .init = sunxi_clock_timer_init,
    .start = sunxi_clock_timer_start,
    .stop = sunxi_clock_timer_stop,
    .count_get = sunxi_clock_timer_count_get,
    .control = sunxi_clock_timer_control,
};

static void sunxi_clock_timer_isr(int irqno, void *parameter)
{
    rt_uint32_t mask;
    struct sunxi_timer_channel *channel = parameter;
    struct sunxi_timer_controller *controller = channel->controller;

    RT_UNUSED(irqno);

    mask = RT_BIT(channel->id);
    if (controller->kind == SUNXI_TIMER)
    {
        if (!(HWREG32(controller->base + SUNXI_TIMER_IRQ_STA) & mask))
        {
            return;
        }
        HWREG32(controller->base + SUNXI_TIMER_IRQ_STA) = mask;
    }
    else
    {
        if (!(HWREG32(controller->base + SUNXI_HSTIMER_IRQ_STA) & mask))
        {
            return;
        }
        HWREG32(controller->base + SUNXI_HSTIMER_IRQ_STA) = mask;
    }

    rt_clock_timer_isr(&channel->parent);
}

static void sunxi_clock_timer_release(struct sunxi_timer_controller *controller)
{
    int i;

    for (i = 0; i < SUNXI_TIMER_CHANNELS; ++i)
    {
        struct sunxi_timer_channel *channel = &controller->channels[i];

        if (channel->irq_attached)
        {
            rt_pic_irq_mask(channel->irq);
            rt_pic_detach_irq(channel->irq, channel);
        }
        if (channel->registered)
        {
            rt_device_unregister(&channel->parent.parent);
        }
    }
    if (!rt_is_err_or_null(controller->reset))
    {
        rt_reset_control_assert(controller->reset);
        rt_reset_control_put(controller->reset);
    }
    if (controller->clk_enabled)
    {
        rt_clk_disable_unprepare(controller->clk);
    }
    if (!rt_is_err_or_null(controller->clk))
    {
        rt_clk_put(controller->clk);
    }
    if (controller->base)
    {
        rt_iounmap(controller->base);
    }
    rt_free(controller);
}

static rt_err_t sunxi_clock_timer_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t frequency = SUNXI_TIMER_24M_FREQ;
    const char *prefix;
    struct rt_device *dev = &pdev->parent;
    enum sunxi_timer_kind kind = (rt_ubase_t)pdev->id->data;
    struct sunxi_timer_controller *controller = rt_calloc(1, sizeof(*controller));

    if (!controller)
    {
        return -RT_ENOMEM;
    }

    controller->kind = kind;
    controller->base = rt_dm_dev_iomap(dev, 0);
    if (!controller->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (kind == SUNXI_HSTIMER)
    {
        controller->clk = rt_clk_get_by_name(dev, "bus");
        controller->reset = rt_reset_control_get_by_name(dev, "bus");
        if (rt_is_err(controller->clk) || rt_is_err(controller->reset))
        {
            err = rt_is_err(controller->clk) ? rt_ptr_err(controller->clk) :
                    rt_ptr_err(controller->reset);
            goto _fail;
        }
        if ((err = rt_reset_control_deassert(controller->reset)) ||
                (err = rt_clk_prepare_enable(controller->clk)))
        {
            goto _fail;
        }
        controller->clk_enabled = RT_TRUE;
        frequency = rt_clk_get_rate(controller->clk);
        if (!frequency)
        {
            err = -RT_EIO;
            goto _fail;
        }
        prefix = "hstimer";
    }
    else
    {
        rt_dm_dev_prop_read_u32(dev, "clock-frequency", &frequency);
        prefix = "timer";
    }

    controller->info.maxfreq = frequency;
    controller->info.minfreq = frequency;
    controller->info.maxcnt = RT_UINT32_MAX;
    controller->info.cntmode = CLOCK_TIMER_CNTMODE_DW;

    for (int i = 0; i < SUNXI_TIMER_CHANNELS; ++i)
    {
        char name[RT_NAME_MAX];
        struct sunxi_timer_channel *channel = &controller->channels[i];

        channel->controller = controller;
        channel->id = i;
        channel->irq = rt_dm_dev_get_irq(dev, i);
        if (channel->irq < 0)
        {
            err = channel->irq;
            goto _fail;
        }

        channel->parent.ops = &sunxi_clock_timer_ops;
        channel->parent.info = &controller->info;
        channel->parent.freq = frequency;
        rt_snprintf(name, sizeof(name), "%s%d", prefix, i);

        if ((err = rt_clock_timer_register(&channel->parent, name, controller)))
        {
            goto _fail;
        }
        channel->registered = RT_TRUE;

        if ((err = rt_pic_attach_irq(channel->irq, sunxi_clock_timer_isr,
                        channel, name, RT_IRQ_F_NONE)))
        {
            goto _fail;
        }
        channel->irq_attached = RT_TRUE;
        rt_pic_irq_unmask(channel->irq);
    }

    dev->user_data = controller;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, controller);

    return RT_EOK;

_fail:
    sunxi_clock_timer_release(controller);

    return err;
}

static rt_err_t sunxi_clock_timer_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct sunxi_timer_controller *controller = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);
    sunxi_clock_timer_release(controller);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_clock_timer_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-timer", .data = (void *)SUNXI_TIMER },
    { .compatible = "allwinner,sun252i-f101-hstimer", .data = (void *)SUNXI_HSTIMER },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_clock_timer_driver =
{
    .name = "clock-timer-sunxi",
    .ids = sunxi_clock_timer_ofw_ids,
    .probe = sunxi_clock_timer_probe,
    .remove = sunxi_clock_timer_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_clock_timer_driver);
