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

#define DBG_TAG "hwtimer.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define TMR_CCR                 0x000c
#define TMR_TN_MM(n, m)         (0x0010 + ((n) << 4) + ((m) << 2))
#define TMR_CR(n)               (0x0090 + ((n) << 2))
#define TMR_SR(n)               (0x0080 + ((n) << 2))
#define TMR_IER(n)              (0x0060 + ((n) << 2))
#define TMR_PLVR(n)             (0x0040 + ((n) << 2))
#define TMR_PLCR(n)             (0x0050 + ((n) << 2))
#define TMR_WMER                0x0068
#define TMR_WMR                 0x006c
#define TMR_WVR                 0x00cc
#define TMR_WSR                 0x00c0
#define TMR_ICR(n)              (0x0070 + ((n) << 2))
#define TMR_WICR                0x00c4
#define TMR_CER                 0x0000
#define TMR_CMR                 0x0004
#define TMR_WCR                 0x00c8
#define TMR_WFAR                0x00b0
#define TMR_WSAR                0x00b4
#define TMR_CRSR                0x0008

#define TMR_CCR_CS_0(x)         (((x) & 0x3) << 0)
#define TMR_CCR_CS_1(x)         (((x) & 0x3) << 2)
#define TMR_CCR_CS_2(x)         (((x) & 0x3) << 5)

#define MAX_DELTA               0xfffffffe
#define MIN_DELTA               5

#define SPACEMIT_MAX_COUNTER    3
#define SPACEMIT_MAX_TIMER      3

#define TMR_CER_COUNTER(cid)    (1 << (cid))
#define SPACEMIT_ALL_COUNTERS   ((1 << SPACEMIT_MAX_COUNTER) - 1)

#define SPACEMIT_TIMER_ALL_CPU  0xffffffff

#define CLOCK_32KHZ             32768

struct spacemit_timer;

struct spacemit_timer_counter
{
    struct rt_hwtimer_device parent;
    struct rt_hwtimer_info info;

    struct spacemit_timer *timer;

    int irq;
    rt_uint32_t cid;
    rt_uint32_t cycle;
    rt_uint32_t freq;
};

#define raw_to_spacemit_timer_counter(raw) rt_container_of(raw, struct spacemit_timer_counter, parent)

struct spacemit_timer
{
    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    rt_uint32_t tid;
    rt_uint32_t freq;
    rt_uint32_t fc_freq;
    rt_uint32_t apb_freq;
    rt_uint32_t loop_delay_fastclk;

    struct spacemit_timer_counter counter[SPACEMIT_MAX_COUNTER];
    struct rt_spinlock tm_lock;
};

static rt_err_t timer_counter_switch_clock(struct spacemit_timer *timer, rt_uint32_t freq);

static void timer_write_check(struct spacemit_timer *timer,
        rt_uint32_t reg, rt_uint32_t val, rt_uint32_t mask,
        rt_bool_t clr, rt_bool_t clk_switch)
{
    int loop = 3, retry = 100;
    rt_uint32_t t_read, t_check = clr ? !val : val;

_retry:
    HWREG32(timer->base + reg) = val;

    if (clk_switch)
    {
        timer_counter_switch_clock(timer, timer->fc_freq);
    }

    t_read = HWREG32(timer->base + reg);

    while (((t_read & mask) != (t_check & mask)) && loop)
    {
        /* Avoid trying frequently to worsen bus contention */
        rt_hw_us_delay(30);

        t_read = HWREG32(timer->base + reg);
        --loop;

        if (!loop)
        {
            loop = 3;

            if (--retry)
            {
                goto _retry;
            }
            else
            {
                return;
            }
        }
    }
}

static rt_err_t timer_counter_switch_clock(struct spacemit_timer *timer, rt_uint32_t freq)
{
    rt_uint32_t ccr, val, mask;

    ccr = HWREG32(timer->base + TMR_CCR);

    switch (timer->tid)
    {
    case 0:
        mask = TMR_CCR_CS_0(3);
        break;
    case 1:
        mask = TMR_CCR_CS_1(3);
        break;
    case 2:
        mask = TMR_CCR_CS_2(3);
        break;
    default:
        return -RT_EINVAL;
    }

    ccr &= ~mask;

    if (freq == timer->fc_freq)
    {
        val = 0;
    }
    else if (freq == CLOCK_32KHZ)
    {
        val = 1;
    }
    else
    {
        LOG_E("Timer %d: invalid clock rate %u", timer->tid, freq);
        return -RT_EINVAL;
    }

    switch (timer->tid)
    {
    case 0:
        ccr |= TMR_CCR_CS_0(val);
        break;
    case 1:
        ccr |= TMR_CCR_CS_1(val);
        break;
    case 2:
        ccr |= TMR_CCR_CS_2(val);
        break;
    }

    timer_write_check(timer, TMR_CCR, ccr, mask, RT_FALSE, RT_FALSE);

    return RT_EOK;
}

static void timer_counter_disable(struct spacemit_timer_counter *cnt)
{
    rt_uint32_t cer;
    rt_bool_t clk_switch = RT_FALSE;
    struct spacemit_timer *timer = cnt->timer;

    if (cnt->freq != timer->fc_freq)
    {
        clk_switch = RT_TRUE;
    }

    /* Disable counter */
    cer = HWREG32(timer->base + TMR_CER);
    timer_write_check(timer, TMR_CER, (cer & ~(1 << cnt->cid)), (1 << cnt->cid), RT_FALSE, clk_switch);
}

static void timer_counter_enable(struct spacemit_timer_counter *cnt)
{
    rt_uint32_t cer;
    struct spacemit_timer *timer = cnt->timer;

    /* Switch to original clock */
    if (cnt->freq != timer->fc_freq)
    {
        timer_counter_switch_clock(timer, cnt->freq);
    }

    /* Enable timer */
    cer = HWREG32(timer->base + TMR_CER);

    timer_write_check(timer, TMR_CER, (cer | (1 << cnt->cid)), (1 << cnt->cid), RT_FALSE, RT_FALSE);
}

static void spacemit_timer_init(struct rt_hwtimer_device *hwtimer, rt_uint32_t state)
{
}

static rt_err_t spacemit_timer_start(struct rt_hwtimer_device *hwtimer,
        rt_uint32_t cycle, rt_hwtimer_mode_t mode)
{
    rt_ubase_t level;
    struct spacemit_timer_counter *cnt = raw_to_spacemit_timer_counter(hwtimer);

    if (mode != HWTIMER_MODE_ONESHOT)
    {
        return -RT_ENOSYS;
    }

    level = rt_spin_lock_irqsave(&cnt->timer->tm_lock);

    /* If the timer counter is enabled, first disable it. */
    if (HWREG32(cnt->timer->base + TMR_CER) & (1 << cnt->cid))
    {
        timer_counter_disable(cnt);
    }

    /* Setup new counter value */
    timer_write_check(cnt->timer, TMR_TN_MM(cnt->cid, 0), (cycle - 1), (rt_uint32_t)(-1), RT_FALSE, RT_FALSE);

    /* enable the matching interrupt */
    timer_write_check(cnt->timer, TMR_IER(cnt->cid), 0x1, 0x1, RT_FALSE, RT_FALSE);

    timer_counter_enable(cnt);

    cnt->cycle = cycle;

    rt_spin_unlock_irqrestore(&cnt->timer->tm_lock, level);

    return RT_EOK;
}

static void spacemit_timer_stop(struct rt_hwtimer_device *hwtimer)
{
    rt_ubase_t level;
    struct spacemit_timer_counter *cnt = raw_to_spacemit_timer_counter(hwtimer);

    level = rt_spin_lock_irqsave(&cnt->timer->tm_lock);

    timer_counter_disable(cnt);

    rt_spin_unlock_irqrestore(&cnt->timer->tm_lock, level);
}

static rt_err_t spacemit_timer_ctrl(struct rt_hwtimer_device *hwtimer,
        rt_uint32_t cmd, void *args)
{
    rt_ubase_t level;
    rt_err_t err = RT_EOK;
    struct spacemit_timer_counter *cnt = raw_to_spacemit_timer_counter(hwtimer);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        level = rt_spin_lock_irqsave(&cnt->timer->tm_lock);
        err = timer_counter_switch_clock(cnt->timer, *(rt_int32_t *)args);
        rt_spin_unlock_irqrestore(&cnt->timer->tm_lock, level);
        break;

    case HWTIMER_CTRL_STOP:
        spacemit_timer_stop(hwtimer);
        break;

    case HWTIMER_CTRL_INFO_GET:
        if (args)
        {
            rt_memcpy(args, &cnt->info, sizeof(cnt->info));
        }
        else
        {
            err = -RT_ERROR;
        }
        break;

    case HWTIMER_CTRL_MODE_SET:
        err = spacemit_timer_start(hwtimer, cnt->cycle, (rt_hwtimer_mode_t)args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_hwtimer_ops spacemit_timer_ops =
{
    .init = spacemit_timer_init,
    .start = spacemit_timer_start,
    .stop = spacemit_timer_stop,
    .control = spacemit_timer_ctrl,
};

static void spacemit_timer_isr(int irqno, void *param)
{
    rt_ubase_t level;
    struct spacemit_timer_counter *cnt = param;

    level = rt_spin_lock_irqsave(&cnt->timer->tm_lock);

    /* We only use match #0 for the counter. */
    if (HWREG32(cnt->timer->base + TMR_SR(cnt->cid)) & 0x1)
    {
        timer_counter_disable(cnt);

        /* Disable the interrupt. */
        timer_write_check(cnt->timer, TMR_IER(cnt->cid), 0, 0x7, RT_FALSE, RT_FALSE);
        /* Clear interrupt status */
        timer_write_check(cnt->timer, TMR_ICR(cnt->cid), 0x1, 0x7, RT_TRUE, RT_FALSE);

        rt_spin_unlock_irqrestore(&cnt->timer->tm_lock, level);

        rt_device_hwtimer_isr(&cnt->parent);

        return;
    }

    rt_spin_unlock_irqrestore(&cnt->timer->tm_lock, level);
}

static void spacemit_timer_free(struct spacemit_timer *timer)
{
    if (timer->base)
    {
        rt_iounmap(timer->base);
    }

    if (!rt_is_err_or_null(timer->clk))
    {
        rt_clk_put(timer->clk);
    }

    rt_free(timer);
}

static rt_err_t spacemit_timer_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    rt_uint32_t val, delay;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *child_np;
    struct spacemit_timer *timer = rt_calloc(1, sizeof(*timer));

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

    if (rt_is_err(timer->clk = rt_clk_get_by_index(dev, 0)))
    {
        err = rt_ptr_err(timer->clk);
        goto _fail;
    }

    if (rt_is_err(timer->rstc = rt_reset_control_get_by_index(dev, 0)))
    {
        err = rt_ptr_err(timer->rstc);
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,timer-id", &timer->tid)))
    {
        goto _fail;
    }

    if (timer->tid >= SPACEMIT_MAX_TIMER)
    {
        err = -RT_EFULL;
        goto _fail;
    }

    /* Timer's fast clock and apb frequency */
    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,timer-fastclk-frequency", &timer->fc_freq)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,timer-apb-frequency", &timer->apb_freq)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,timer-frequency", &timer->freq)))
    {
        goto _fail;
    }

    /*
     * Need use loop for more safe register's accessing,
     * so at here dynamically calculate the loop time.
     */
    if (!timer->fc_freq || !timer->apb_freq)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(timer->clk)))
    {
        goto _fail;
    }

    if ((err = rt_clk_set_rate(timer->clk, timer->fc_freq)))
    {
        goto _fail;
    }

    rt_reset_control_deassert(timer->rstc);

    /*
     * The calculation formula for the loop cycle is:
     *
     * (1) need wait for 2 timer's clock cycle:
     *        1             2
     *     ------- x 2 = -------
     *     fc_freq       fc_freqtimer_counter_enable(evt);
     *
     * (2) convert to apb clock cycle:
     *        2          1        apb_freq * 2
     *     ------- / -------- = ----------------
     *     fc_freq   apb_freq       fc_freq
     *
     * (3) every apb register's accessing will take 8 apb clock cycle,
     *     also consider add extral one more time for safe way;
     *     so finally need loop times for the apb register accessing:
     *
     *       (apb_freq * 2)
     *     ------------------ / 8 + 1
     *          fc_freq
     */
    delay = ((timer->apb_freq * 2) / timer->fc_freq / 8) + 1;
    timer->loop_delay_fastclk = delay;

    rt_spin_lock_init(&timer->tm_lock);

    /* Switch to fastclk before disable all counters. */
    timer_counter_switch_clock(timer, timer->fc_freq);

    /* Disalbe all counters */
    val = HWREG32(timer->base + TMR_CER) & ~SPACEMIT_ALL_COUNTERS;
    HWREG32(timer->base + TMR_CER) = val;

    /* Disable matching interrupt */
    HWREG32(timer->base + TMR_IER(0)) = 0x0;
    HWREG32(timer->base + TMR_IER(1)) = 0x0;
    HWREG32(timer->base + TMR_IER(2)) = 0x0;

    while (delay--)
    {
        /* Clear pending interrupt status */
        HWREG32(timer->base + TMR_ICR(0)) = 0x1;
        HWREG32(timer->base + TMR_ICR(1)) = 0x1;
        HWREG32(timer->base + TMR_ICR(2)) = 0x1;
        HWREG32(timer->base + TMR_CER) = val;
    }

    rt_ofw_foreach_available_child_node(np, child_np)
    {
        rt_uint32_t cpu, ratio;
        struct spacemit_timer_counter *cnt;

        if (!rt_ofw_node_is_compatible(child_np, "spacemit,timer-match"))
        {
            continue;
        }

        if (rt_ofw_prop_read_u32(child_np, "spacemit,timer-counter-id", &val))
        {
            continue;
        }

        if (val >= SPACEMIT_MAX_TIMER)
        {
            LOG_W("Found a counter %s with id = %d > %d",
                    rt_ofw_node_full_name(child_np), val, SPACEMIT_MAX_TIMER);
            continue;
        }

        cnt = &timer->counter[val];
        cnt->cid = val;
        cnt->freq = timer->freq;

        if (cnt->timer)
        {
            LOG_W("Found a repeat counter %s with id = %d",
                    rt_ofw_node_full_name(child_np), cnt->cid);
            continue;
        }

        if (cnt->timer)
        {
            LOG_W("Found a repeat counter %s with id = %d",
                    rt_ofw_node_full_name(child_np), cnt->cid);
            continue;
        }

        if (rt_ofw_prop_read_bool(child_np, "spacemit,timer-broadcast"))
        {
            cpu = SPACEMIT_TIMER_ALL_CPU;
        }
        else
        {
            cpu = rt_hw_cpu_id();
            rt_ofw_prop_read_u32(child_np, "spacemit,timer-counter-cpu", &cpu);
        }

        if ((cnt->irq = rt_ofw_get_irq(child_np, 0)) < 0)
        {
            continue;
        }

        /* Hareware init */
        if (timer_counter_switch_clock(timer, cnt->freq))
        {
            continue;
        }

        ratio = timer->fc_freq / timer->freq;
        delay = timer->loop_delay_fastclk * ratio;

        /* Set timer to free-running mode */
        val = HWREG32(timer->base + TMR_CMR) | TMR_CER_COUNTER(cnt->cid);
        HWREG32(timer->base + TMR_CMR) = val;

        /* Free-running */
        HWREG32(timer->base + TMR_PLCR(cnt->cid)) = 0x0;
        /* Clear status */
        HWREG32(timer->base + TMR_ICR(cnt->cid)) = 0x7;

        /* Enable counter */
        val = HWREG32(timer->base + TMR_CER) | TMR_CER_COUNTER(cnt->cid);
        HWREG32(timer->base + TMR_CER) = val;

        while (delay--)
        {
            HWREG32(timer->base + TMR_CER) = val;
        }

        cnt->timer = timer;

        cnt->parent.ops = &spacemit_timer_ops;
        cnt->parent.info = &cnt->info;

        cnt->info.maxfreq = timer->fc_freq;
        cnt->info.minfreq = CLOCK_32KHZ;
        cnt->info.maxcnt = 0xffffffff;
        cnt->info.cntmode = HWTIMER_CNTMODE_UP;

        rt_dm_dev_set_name_auto(&cnt->parent.parent, "timer");
        dev_name = rt_dm_dev_get_name(&cnt->parent.parent);

        rt_hw_interrupt_install(cnt->irq, spacemit_timer_isr, cnt, dev_name);
        rt_hw_interrupt_umask(cnt->irq);

        if (cpu != SPACEMIT_TIMER_ALL_CPU)
        {
            RT_IRQ_AFFINITY_DECLARE(affinity) = { 0 };

            RT_IRQ_AFFINITY_SET(affinity, cpu);

            rt_pic_irq_set_affinity(cnt->irq, affinity);
        }

        rt_device_hwtimer_register(&cnt->parent, dev_name, RT_NULL);
    }

    dev->user_data = timer;

    return RT_EOK;

_fail:
    spacemit_timer_free(timer);

    return err;
}

static rt_err_t spacemit_timer_remove(struct rt_platform_device *pdev)
{
    struct spacemit_timer *timer = pdev->parent.user_data;

    for (int i = 0; i < SPACEMIT_MAX_TIMER; ++i)
    {
        struct spacemit_timer_counter *cnt = &timer->counter[i];

        if (cnt->timer)
        {
            continue;
        }

        rt_hw_interrupt_mask(cnt->irq);
        rt_pic_detach_irq(cnt->irq, cnt);

        rt_device_unregister(&cnt->parent.parent);
    }

    spacemit_timer_free(timer);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_timer_ofw_ids[] =
{
    { .compatible = "spacemit,soc-timer" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_timer_driver =
{
    .name = "hwtimer-spacemit",
    .ids = spacemit_timer_ofw_ids,

    .probe = spacemit_timer_probe,
    .remove = spacemit_timer_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_timer_driver);
