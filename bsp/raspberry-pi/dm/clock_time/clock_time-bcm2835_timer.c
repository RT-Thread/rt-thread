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
#include <drivers/clock_time.h>

#define REG_CONTROL     0x00
#define REG_COUNTER_LO  0x04
#define REG_COUNTER_HI  0x08
#define REG_COMPARE(n)  (0x0c + (n) * 4)
#define MAX_TIMER       4

struct bcm2835_timer;

struct bcm2835_timer_device
{
    struct rt_clock_timer_device parent;

    int id;
    int irq;
    void *compare;

    struct bcm2835_timer *timer;
};

struct bcm2835_timer
{
    void *base;

    struct bcm2835_timer_device device[MAX_TIMER];
    struct rt_clock_timer_info info;
};

#define raw_to_bcm2835_timer(raw) rt_container_of(raw, struct bcm2835_timer_device, parent)

static void bcm2835_timer_init(struct rt_clock_timer_device *timer, rt_uint32_t state)
{
    RT_UNUSED(timer);
    RT_UNUSED(state);
}

static rt_err_t bcm2835_timer_start(struct rt_clock_timer_device *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    rt_err_t err = RT_EOK;
    struct bcm2835_timer_device *timer_dev = raw_to_bcm2835_timer(timer);

    switch (mode)
    {
    case CLOCK_TIMER_MODE_ONESHOT:
        HWREG32(timer_dev->compare) = HWREG32(timer_dev->timer->base + REG_COUNTER_LO) + cnt;
        break;

    case CLOCK_TIMER_MODE_PERIOD:
        err = -RT_ENOSYS;
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    if (!err)
    {
        timer->cycles = cnt;
        timer->mode = mode;
    }

    return err;
}

static void bcm2835_timer_stop(struct rt_clock_timer_device *timer)
{
    RT_UNUSED(timer);
}

static rt_uint32_t bcm2835_timer_count_get(struct rt_clock_timer_device *timer)
{
    struct bcm2835_timer_device *timer_dev = raw_to_bcm2835_timer(timer);

    return HWREG32(timer_dev->timer->base + REG_COUNTER_LO);
}

static rt_err_t bcm2835_timer_ctrl(struct rt_clock_timer_device *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct bcm2835_timer_device *timer_dev = raw_to_bcm2835_timer(timer);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
        err = -RT_ENOSYS;
        break;

    case CLOCK_TIMER_CTRL_STOP:
        bcm2835_timer_stop(timer);
        break;

    case CLOCK_TIMER_CTRL_INFO_GET:
        if (args)
        {
            rt_memcpy(args, &timer_dev->timer->info, sizeof(timer_dev->timer->info));
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case CLOCK_TIMER_CTRL_MODE_SET:
        err = bcm2835_timer_start(timer, timer->cycles, (rt_clock_timer_mode_t)(rt_ubase_t)args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_clock_timer_ops bcm2835_timer_ops =
{
    .init = bcm2835_timer_init,
    .start = bcm2835_timer_start,
    .stop = bcm2835_timer_stop,
    .count_get = bcm2835_timer_count_get,
    .control = bcm2835_timer_ctrl,
};

static void bcm2835_timer_isr(int irqno, void *param)
{
    struct bcm2835_timer_device *timer_dev = param;
    struct bcm2835_timer *timer = timer_dev->timer;

    RT_UNUSED(irqno);

    if (HWREG32(timer->base + REG_CONTROL) & RT_BIT(timer_dev->id))
    {
        /* ACK */
        HWREG32(timer->base + REG_CONTROL) = RT_BIT(timer_dev->id);

        rt_clock_timer_isr(&timer_dev->parent);
    }
}

static rt_err_t bcm2835_timer_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t freq;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_timer *timer = rt_calloc(1, sizeof(*timer));

    if (!timer)
    {
        return -RT_ENOMEM;
    }

    timer->base = rt_dm_dev_iomap(dev, 0);

    if (!timer->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "clock-frequency", &freq))
    {
        err = -RT_EIO;
        goto _fail;
    }

    timer->info.maxfreq = freq;
    timer->info.minfreq = freq;
    timer->info.maxcnt = 0xffffffff;
    timer->info.cntmode = CLOCK_TIMER_CNTMODE_UP;

    for (int i = 0; i < RT_ARRAY_SIZE(timer->device); ++i)
    {
        struct bcm2835_timer_device *timer_dev = &timer->device[i];

        if ((timer_dev->irq = rt_dm_dev_get_irq(dev, i)) < 0)
        {
            continue;
        }

        timer_dev->id = i;
        timer_dev->compare = timer->base + REG_COMPARE(i);
        timer_dev->timer = timer;

        timer_dev->parent.ops = &bcm2835_timer_ops;
        timer_dev->parent.info = &timer->info;
        timer_dev->parent.freq = freq;

        rt_dm_dev_set_name_auto(&timer_dev->parent.parent, "timer");
        dev_name = rt_dm_dev_get_name(&timer_dev->parent.parent);

        rt_clock_timer_register(&timer_dev->parent, dev_name, RT_NULL);
        rt_pic_attach_irq(timer_dev->irq, bcm2835_timer_isr, timer_dev, dev_name, RT_IRQ_F_NONE);
        rt_pic_irq_unmask(timer_dev->irq);
    }

    dev->user_data = timer;

    return RT_EOK;

_fail:
    if (timer->base)
    {
        rt_iounmap(timer->base);
    }
    rt_free(timer);

    return err;
}

static rt_err_t bcm2835_timer_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_timer *timer = pdev->parent.user_data;

    for (int i = 0; i < RT_ARRAY_SIZE(timer->device); ++i)
    {
        struct bcm2835_timer_device *timer_dev = &timer->device[i];

        if (timer_dev->irq < 0)
        {
            continue;
        }

        bcm2835_timer_stop(&timer_dev->parent);

        rt_pic_irq_mask(timer_dev->irq);
        rt_pic_detach_irq(timer_dev->irq, timer_dev);

        rt_device_unregister(&timer_dev->parent.parent);
    }

    rt_iounmap(timer->base);
    rt_free(timer);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835_timer_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-system-timer", },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_timer_driver =
{
    .name = "clock_timer-bcm2835",
    .ids = bcm2835_timer_ofw_ids,

    .probe = bcm2835_timer_probe,
    .remove = bcm2835_timer_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_timer_driver);
