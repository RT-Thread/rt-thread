/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define TIMER_LOAD_COUNT0               0x00
#define TIMER_LOAD_COUNT1               0x04
#define TIMER_CURRENT_VALUE0            0x08
#define TIMER_CURRENT_VALUE1            0x0c
#define TIMER_CONTROL_REG3288           0x10
#define TIMER_CONTROL_REG3399           0x1c
#define TIMER_INT_STATUS                0x18

#define TIMER_DISABLE                   0x0
#define TIMER_ENABLE                    0x1
#define TIMER_MODE_FREE_RUNNING         (0 << 1)
#define TIMER_MODE_USER_DEFINED_COUNT   (1 << 1)
#define TIMER_INT_UNMASK                (1 << 2)

#define HZ                              100

struct rk_timer
{
    struct rt_hwtimer_device parent;

    void *base;
    void *ctrl;
    struct rt_clk *clk;
    struct rt_clk *pclk;

    int irq;
    rt_uint32_t freq;
    rt_uint32_t cycle;
    rt_bool_t status;

    struct rt_hwtimer_info info;
};

#define raw_to_rk_timer(raw) rt_container_of(raw, struct rk_timer, parent)

struct rk_timer_data
{
    rt_uint32_t ctrl_reg;
};

rt_inline void rk_timer_disable(struct rk_timer *timer)
{
    HWREG32(timer->ctrl) = TIMER_DISABLE;
}

rt_inline void rk_timer_enable(struct rk_timer *timer, rt_uint32_t flags)
{
    HWREG32(timer->ctrl) = TIMER_ENABLE | flags;
}

rt_inline rt_uint32_t rk_timer_current_value(struct rk_timer *timer)
{
    return HWREG32(timer->base + TIMER_CURRENT_VALUE0);
}

static void rk_timer_update_counter(unsigned long cycles, struct rk_timer *timer)
{
    HWREG32(timer->base + TIMER_LOAD_COUNT0) = cycles;
    HWREG32(timer->base + TIMER_LOAD_COUNT1) = 0;
}

static void rk_timer_interrupt_clear(struct rk_timer *timer)
{
    HWREG32(timer->base + TIMER_INT_STATUS) = 1;
}

static void rk_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
}

static rt_err_t rk_timer_start(struct rt_hwtimer_device *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    rt_err_t err = RT_EOK;
    struct rk_timer *rk_timer = raw_to_rk_timer(timer);

    switch (mode)
    {
    case HWTIMER_MODE_ONESHOT:
        rk_timer_disable(rk_timer);
        rk_timer_update_counter(cnt, rk_timer);
        rk_timer_enable(rk_timer, TIMER_MODE_USER_DEFINED_COUNT | TIMER_INT_UNMASK);
        break;

    case HWTIMER_MODE_PERIOD:
        rk_timer_disable(rk_timer);
        rk_timer_update_counter(rk_timer->freq / HZ - 1, rk_timer);
        rk_timer_enable(rk_timer, TIMER_MODE_FREE_RUNNING | TIMER_INT_UNMASK);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    if (!err)
    {
        rk_timer->cycle = cnt;
        rk_timer->status = RT_TRUE;
    }

    return err;
}

static void rk_timer_stop(struct rt_hwtimer_device *timer)
{
    struct rk_timer *rk_timer = raw_to_rk_timer(timer);

    rk_timer->status = RT_FALSE;
    rk_timer_disable(rk_timer);
}

static rt_uint32_t rk_timer_count_get(struct rt_hwtimer_device *timer)
{
    struct rk_timer *rk_timer = raw_to_rk_timer(timer);

    return rk_timer_current_value(rk_timer);
}

static rt_err_t rk_timer_ctrl(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rk_timer *rk_timer = raw_to_rk_timer(timer);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        err = -RT_ENOSYS;
        break;

    case HWTIMER_CTRL_STOP:
        rk_timer_stop(timer);
        break;

    case HWTIMER_CTRL_INFO_GET:
        if (args)
        {
            rt_memcpy(args, &rk_timer->info, sizeof(rk_timer->info));
        }
        else
        {
            err = -RT_ERROR;
        }
        break;

    case HWTIMER_CTRL_MODE_SET:
        err = rk_timer_start(timer, rk_timer->cycle, (rt_hwtimer_mode_t)args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_hwtimer_ops rk_timer_ops =
{
    .init = rk_timer_init,
    .start = rk_timer_start,
    .stop = rk_timer_stop,
    .count_get = rk_timer_count_get,
    .control = rk_timer_ctrl,
};

static void rk_timer_isr(int irqno, void *param)
{
    struct rk_timer *rk_timer = (struct rk_timer *)param;

    rk_timer_interrupt_clear(rk_timer);

    if (rk_timer->status)
    {
        rt_device_hwtimer_isr(&rk_timer->parent);
    }
}

static void rk_timer_free(struct rk_timer *timer)
{
    if (timer->base)
    {
        rt_iounmap(timer->base);
    }

    if (!rt_is_err_or_null(timer->pclk))
    {
        rt_clk_put(timer->pclk);
    }

    if (!rt_is_err_or_null(timer->clk))
    {
        rt_clk_put(timer->clk);
    }

    rt_free(timer);
}

static rt_err_t rk_timer_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct rk_timer *timer = rt_calloc(1, sizeof(*timer));
    const struct rk_timer_data *timer_data = pdev->id->data;

    if (!timer)
    {
        return -RT_ENOMEM;
    }

    if (rt_is_err(timer->pclk = rt_clk_get_by_name(dev, "pclk")))
    {
        err = rt_ptr_err(timer->pclk);

        goto _fail;
    }

    if (rt_is_err(timer->clk = rt_clk_get_by_name(dev, "timer")))
    {
        err = rt_ptr_err(timer->clk);

        goto _fail;
    }

    timer->base = rt_dm_dev_iomap(dev, 0);

    if (!timer->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    dev->user_data = timer;

    timer->ctrl = timer->base + timer_data->ctrl_reg;

    rt_clk_enable(timer->pclk);
    rt_clk_enable(timer->clk);
    timer->freq = rt_clk_get_rate(timer->clk);
    timer->irq = rt_dm_dev_get_irq(dev, 0);

    rk_timer_interrupt_clear(timer);
    rk_timer_disable(timer);

    timer->parent.ops = &rk_timer_ops;
    timer->parent.info = &timer->info;

    timer->info.maxfreq = timer->freq;
    timer->info.minfreq = timer->freq;
    timer->info.maxcnt = 0xffffffff;
    timer->info.cntmode = HWTIMER_CNTMODE_UP;

    rt_dm_dev_set_name_auto(&timer->parent.parent, "timer");
    dev_name = rt_dm_dev_get_name(&timer->parent.parent);

    rt_device_hwtimer_register(&timer->parent, dev_name, RT_NULL);
    rt_hw_interrupt_install(timer->irq, rk_timer_isr, timer, dev_name);
    rt_hw_interrupt_umask(timer->irq);

    return RT_EOK;

_fail:
    rk_timer_free(timer);

    return err;
}

static rt_err_t rk_timer_remove(struct rt_platform_device *pdev)
{
    struct rk_timer *timer = pdev->parent.user_data;

    rt_hw_interrupt_mask(timer->irq);
    rt_pic_detach_irq(timer->irq, timer);

    rk_timer_stop(&timer->parent);

    rt_device_unregister(&timer->parent.parent);

    rk_timer_free(timer);

    return RT_EOK;
}

static const struct rk_timer_data rk3288_timer_data =
{
    .ctrl_reg = TIMER_CONTROL_REG3288,
};

static const struct rk_timer_data rk3399_timer_data =
{
    .ctrl_reg = TIMER_CONTROL_REG3399,
};

static const struct rt_ofw_node_id rk_timer_ofw_ids[] =
{
    { .compatible = "rockchip,rk3288-timer", .data = &rk3288_timer_data },
    { .compatible = "rockchip,rk3399-timer", .data = &rk3399_timer_data },
    { /* sentinel */ }
};

static struct rt_platform_driver rk_timer_driver =
{
    .name = "hwtimer-rockchip",
    .ids = rk_timer_ofw_ids,

    .probe = rk_timer_probe,
    .remove = rk_timer_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk_timer_driver);
