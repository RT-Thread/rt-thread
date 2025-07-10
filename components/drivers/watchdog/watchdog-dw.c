/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define WDOG_CONTROL_REG_OFFSET             0x00
#define WDOG_CONTROL_REG_WDT_EN_MASK        0x01
#define WDOG_CONTROL_REG_RESP_MODE_MASK     0x02
#define WDOG_TIMEOUT_RANGE_REG_OFFSET       0x04
#define WDOG_TIMEOUT_RANGE_TOPINIT_SHIFT    4
#define WDOG_CURRENT_COUNT_REG_OFFSET       0x08
#define WDOG_COUNTER_RESTART_REG_OFFSET     0x0c
#define WDOG_COUNTER_RESTART_KICK_VALUE     0x76
#define WDOG_INTERRUPT_STATUS_REG_OFFSET    0x10
#define WDOG_INTERRUPT_CLEAR_REG_OFFSET     0x14
#define WDOG_COMP_PARAMS_5_REG_OFFSET       0xe4
#define WDOG_COMP_PARAMS_4_REG_OFFSET       0xe8
#define WDOG_COMP_PARAMS_3_REG_OFFSET       0xec
#define WDOG_COMP_PARAMS_2_REG_OFFSET       0xf0
#define WDOG_COMP_PARAMS_1_REG_OFFSET       0xf4
#define WDOG_COMP_PARAMS_1_USE_FIX_TOP      (1 << 6)
#define WDOG_COMP_VERSION_REG_OFFSET        0xf8
#define WDOG_COMP_TYPE_REG_OFFSET           0xfc

/* There are sixteen TOPs (timeout periods) that can be set in the watchdog. */
#define DW_WDT_NUM_TOPS                     16
#define DW_WDT_FIX_TOP(idx)                 (1U << (16 + idx))
#define DW_WDT_DEFAULT_SECONDS              30

#define MSEC_PER_SEC 1000L

enum dw_wdt_rmod
{
    DW_WDT_RMOD_RESET = 1,
    DW_WDT_RMOD_IRQ
};

struct dw_wdt_timeout
{
    rt_uint32_t top_val;
    rt_uint32_t sec;
    rt_uint32_t msec;
};

struct dw_wdt
{
    rt_watchdog_t parent;

    void *base;
    int irq;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    rt_ubase_t rate;
    enum dw_wdt_rmod rmod;
    struct dw_wdt_timeout timeouts[DW_WDT_NUM_TOPS];
    /* Save/Restore */
    rt_uint32_t user;
    rt_uint32_t timeout;
    rt_uint32_t pretimeout;
    rt_uint32_t max_hw_heartbeat_ms;

    struct rt_device_notify pretimeout_notify;
};

#define raw_to_dw_wdt(raw) rt_container_of(raw, struct dw_wdt, parent)

static const rt_uint32_t dw_wdt_fix_tops[DW_WDT_NUM_TOPS] =
{
    DW_WDT_FIX_TOP(0), DW_WDT_FIX_TOP(1), DW_WDT_FIX_TOP(2), DW_WDT_FIX_TOP(3),
    DW_WDT_FIX_TOP(4), DW_WDT_FIX_TOP(5), DW_WDT_FIX_TOP(6), DW_WDT_FIX_TOP(7),
    DW_WDT_FIX_TOP(8), DW_WDT_FIX_TOP(9), DW_WDT_FIX_TOP(10), DW_WDT_FIX_TOP(11),
    DW_WDT_FIX_TOP(12), DW_WDT_FIX_TOP(13), DW_WDT_FIX_TOP(14), DW_WDT_FIX_TOP(15)
};

rt_inline int dw_wdt_is_enabled(struct dw_wdt *dw_wdt)
{
    return HWREG32(dw_wdt->base + WDOG_CONTROL_REG_OFFSET) & WDOG_CONTROL_REG_WDT_EN_MASK;
}

static void dw_wdt_update_mode(struct dw_wdt *dw_wdt, enum dw_wdt_rmod rmod)
{
    rt_uint32_t val = HWREG32(dw_wdt->base + WDOG_CONTROL_REG_OFFSET);

    if (rmod == DW_WDT_RMOD_IRQ)
    {
        val |= WDOG_CONTROL_REG_RESP_MODE_MASK;
    }
    else
    {
        val &= ~WDOG_CONTROL_REG_RESP_MODE_MASK;
    }

    HWREG32(dw_wdt->base + WDOG_CONTROL_REG_OFFSET) = val;

    dw_wdt->rmod = rmod;
}

static rt_uint32_t dw_wdt_find_best_top(struct dw_wdt *dw_wdt, rt_uint32_t timeout, rt_uint32_t *top_val)
{
    int idx;

    /*
     * Find a TOP with timeout greater or equal to the requested number. Note
     * we'll select a TOP with maximum timeout if the requested timeout couldn't
     * be reached.
     */
    for (idx = 0; idx < DW_WDT_NUM_TOPS; ++idx)
    {
        if (dw_wdt->timeouts[idx].sec >= timeout)
        {
            break;
        }
    }

    if (idx == DW_WDT_NUM_TOPS)
    {
        --idx;
    }

    *top_val = dw_wdt->timeouts[idx].top_val;

    return dw_wdt->timeouts[idx].sec;
}

static rt_uint32_t dw_wdt_get_max_timeout_ms(struct dw_wdt *dw_wdt)
{
    rt_uint64_t msec;
    struct dw_wdt_timeout *timeout = &dw_wdt->timeouts[DW_WDT_NUM_TOPS - 1];

    msec = (rt_uint64_t)timeout->sec * MSEC_PER_SEC + timeout->msec;

    return msec < RT_UINT32_MAX ? msec : RT_UINT32_MAX;
}

static rt_uint32_t dw_wdt_get_timeout(struct dw_wdt *dw_wdt)
{
    int idx;
    int top_val = HWREG32(dw_wdt->base + WDOG_TIMEOUT_RANGE_REG_OFFSET) & 0xF;

    for (idx = 0; idx < DW_WDT_NUM_TOPS; ++idx)
    {
        if (dw_wdt->timeouts[idx].top_val == top_val)
        {
            break;
        }
    }

    /*
     * In IRQ mode due to the two stages counter, the actual timeout is twice
     * greater than the TOP setting.
     */
    return dw_wdt->timeouts[idx].sec * dw_wdt->rmod;
}

static int dw_wdt_keep_alive(struct dw_wdt *dw_wdt)
{
    HWREG32(dw_wdt->base + WDOG_COUNTER_RESTART_REG_OFFSET) = WDOG_COUNTER_RESTART_KICK_VALUE;

    return 0;
}

static void dw_wdt_set_timeout(struct dw_wdt *dw_wdt, rt_uint32_t top_s)
{
    rt_uint32_t top_val;
    rt_uint32_t timeout;

    /*
     * Note IRQ mode being enabled means having a non-zero pre-timeout setup.
     * In this case we try to find a TOP as close to the half of the requested
     * timeout as possible since DW Watchdog IRQ mode is designed in two stages
     * way - first timeout rises the pre-timeout interrupt, second timeout
     * performs the system reset. So basically the effective watchdog-caused
     * reset happens after two watchdog TOPs elapsed.
     */
    timeout = dw_wdt_find_best_top(dw_wdt, RT_DIV_ROUND_UP(top_s, dw_wdt->rmod), &top_val);

    if (dw_wdt->rmod == DW_WDT_RMOD_IRQ)
    {
        dw_wdt->pretimeout = timeout;
    }
    else
    {
        dw_wdt->pretimeout = 0;
    }

    /*
     * Set the new value in the watchdog.  Some versions of dw_wdt have have
     * TOPINIT in the TIMEOUT_RANGE register (as per CP_WDT_DUAL_TOP in
     * WDT_COMP_PARAMS_1).  On those we effectively get a pat of the watchdog
     * right here.
     */
    HWREG32(dw_wdt->base + WDOG_TIMEOUT_RANGE_REG_OFFSET) = top_val | top_val << WDOG_TIMEOUT_RANGE_TOPINIT_SHIFT;

    dw_wdt_keep_alive(dw_wdt);

    /*
     * In case users set bigger timeout value than HW can support,
     * kernel(watchdog_dev.c) helps to feed watchdog before wdd->max_hw_heartbeat_ms
     */
    if (top_s * 1000 <= dw_wdt->max_hw_heartbeat_ms)
    {
        dw_wdt->timeout = timeout * dw_wdt->rmod;
    }
    else
    {
        dw_wdt->timeout = top_s;
    }
}

static void dw_wdt_set_pretimeout(struct dw_wdt *dw_wdt, rt_uint32_t req)
{
    /*
     * We ignore actual value of the timeout passed from user-space using it as
     * a flag whether the pretimeout functionality is intended to be activated.
     */
    dw_wdt_update_mode(dw_wdt, req ? DW_WDT_RMOD_IRQ : DW_WDT_RMOD_RESET);
    dw_wdt_set_timeout(dw_wdt, dw_wdt->timeout);
}

static void dw_wdt_arm_system_reset(struct dw_wdt *dw_wdt)
{
    rt_uint32_t val = HWREG32(dw_wdt->base + WDOG_CONTROL_REG_OFFSET);

    /* Disable/enable interrupt mode depending on the RMOD flag. */
    if (dw_wdt->rmod == DW_WDT_RMOD_IRQ)
    {
        val |= WDOG_CONTROL_REG_RESP_MODE_MASK;
    }
    else
    {
        val &= ~WDOG_CONTROL_REG_RESP_MODE_MASK;
    }

    /* Enable watchdog. */
    HWREG32(dw_wdt->base + WDOG_CONTROL_REG_OFFSET) = val | WDOG_CONTROL_REG_WDT_EN_MASK;
}

static int dw_wdt_start(struct dw_wdt *dw_wdt)
{
    rt_clk_enable(dw_wdt->clk);

    dw_wdt_set_timeout(dw_wdt, dw_wdt->timeout);
    dw_wdt_keep_alive(dw_wdt);
    dw_wdt_arm_system_reset(dw_wdt);

    return 0;
}

static int dw_wdt_stop(struct dw_wdt *dw_wdt)
{
    /*
     * The DesignWare watchdog cannot be stopped once it has been started so we
     * do not implement a stop function. The watchdog core will continue to send
     * heartbeat requests after the watchdog device has been closed.
     */
    rt_clk_disable(dw_wdt->clk);

    rt_reset_control_assert(dw_wdt->rstc);
    rt_reset_control_deassert(dw_wdt->rstc);

    return 0;
}

static rt_uint32_t dw_wdt_get_timeleft(struct dw_wdt *dw_wdt)
{
    rt_uint32_t val, sec;

    val = HWREG32(dw_wdt->base + WDOG_CURRENT_COUNT_REG_OFFSET);
    sec = val / dw_wdt->rate;

    if (dw_wdt->rmod == DW_WDT_RMOD_IRQ)
    {
        val = HWREG32(dw_wdt->base + WDOG_INTERRUPT_STATUS_REG_OFFSET);

        if (!val)
        {
            sec += dw_wdt->pretimeout;
        }
    }

    return sec;
}

static rt_err_t dw_wdt_init_timeouts(struct dw_wdt *dw_wdt)
{
    int val, tidx;
    rt_uint64_t msec;
    struct dw_wdt_timeout tout, *dst;
    const rt_uint32_t *tops = dw_wdt_fix_tops;

    /*
     * Convert the specified TOPs into an array of watchdog timeouts. We walk
     * over the passed TOPs array and calculate corresponding timeouts in
     * seconds and milliseconds. The milliseconds granularity is needed to
     * distinguish the TOPs with very close timeouts and to set the watchdog max
     * heartbeat setting further.
     */
    for (val = 0; val < DW_WDT_NUM_TOPS; ++val)
    {
        tout.top_val = val;
        tout.sec = tops[val] / dw_wdt->rate;
        msec = (rt_uint64_t)tops[val] * MSEC_PER_SEC;
        rt_do_div(msec, dw_wdt->rate);
        tout.msec = msec - ((rt_uint64_t)tout.sec * MSEC_PER_SEC);

        /*
         * Find a suitable place for the current TOP in the timeouts array so
         * that the list is remained in the ascending order.
         */
        for (tidx = 0; tidx < val; ++tidx)
        {
            dst = &dw_wdt->timeouts[tidx];

            if (tout.sec > dst->sec || (tout.sec == dst->sec && tout.msec >= dst->msec))
            {
                continue;
            }
            else
            {
                struct dw_wdt_timeout tmp = *dst;

                *dst = tout;
                tout = tmp;
            }
        }

        dw_wdt->timeouts[val] = tout;
    }

    if (!dw_wdt->timeouts[DW_WDT_NUM_TOPS - 1].sec)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t dw_wdt_init(rt_watchdog_t *wdt)
{
    rt_err_t status = RT_EOK;
    struct dw_wdt *dw_wdt = raw_to_dw_wdt(wdt);

    /* Enable normal reset without pre-timeout by default. */
    dw_wdt_update_mode(dw_wdt, DW_WDT_RMOD_RESET);

    if (dw_wdt_init_timeouts(dw_wdt))
    {
        return -RT_ERROR;
    }

    dw_wdt->max_hw_heartbeat_ms = dw_wdt_get_max_timeout_ms(dw_wdt);

    /*
     * If the watchdog is already running, use its already configured timeout.
     * Otherwise use the default or the value provided through devicetree.
     */
    if (dw_wdt_is_enabled(dw_wdt))
    {
        dw_wdt->timeout = dw_wdt_get_timeout(dw_wdt);
    }
    else
    {
        dw_wdt->timeout = DW_WDT_DEFAULT_SECONDS;
    }

    return status;
}

static rt_err_t dw_wdt_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct dw_wdt *dw_wdt = raw_to_dw_wdt(wdt);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)args = dw_wdt_get_timeout(dw_wdt);
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        dw_wdt_set_timeout(dw_wdt, *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(rt_uint32_t *)args = dw_wdt_get_timeleft(dw_wdt);
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        dw_wdt_set_pretimeout(dw_wdt, dw_wdt->pretimeout);
        dw_wdt_keep_alive(dw_wdt);
        break;

    case RT_DEVICE_CTRL_WDT_START:
        dw_wdt_start(dw_wdt);
        dw_wdt->user++;
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        dw_wdt_stop(dw_wdt);
        dw_wdt->user--;
        break;

    case RT_DEVICE_CTRL_NOTIFY_SET:
        rt_hw_interrupt_mask(dw_wdt->irq);
        if (args)
        {
            rt_memcpy(&dw_wdt->pretimeout_notify, args, sizeof(dw_wdt->pretimeout_notify));
        }
        else
        {
            rt_memset(&dw_wdt->pretimeout_notify, 0, sizeof(dw_wdt->pretimeout_notify));
        }
        rt_hw_interrupt_umask(dw_wdt->irq);
        break;

    default:
        status = -RT_EINVAL;
    }

    return status;
}

static const struct rt_watchdog_ops dw_wdt_ops =
{
    .init = dw_wdt_init,
    .control = dw_wdt_control,
};

#ifdef RT_USING_PM
static rt_err_t dw_wdt_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_watchdog_t *wdt = rt_container_of(device, rt_watchdog_t, parent);
    struct dw_wdt *dw_wdt = raw_to_dw_wdt(wdt);

    dw_wdt->timeout = dw_wdt_get_timeleft(dw_wdt) / dw_wdt->rate;
    dw_wdt_stop(dw_wdt);

    return RT_EOK;
}

static void dw_wdt_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_watchdog_t *wdt = rt_container_of(device, rt_watchdog_t, parent);
    struct dw_wdt *dw_wdt = raw_to_dw_wdt(wdt);

    if (!dw_wdt->user)
    {
        return;
    }

    if (!dw_wdt_init(wdt))
    {
        dw_wdt_start(dw_wdt);
    }
}

static const struct rt_device_pm_ops dw_wdt_pm_ops =
{
    .suspend = dw_wdt_pm_suspend,
    .resume = dw_wdt_pm_resume,
};
#endif /* RT_USING_PM */

static void dw_wdt_isr(int irqno, void *param)
{
    struct dw_wdt *wdt = (struct dw_wdt *)param;

    if (!HWREG32(wdt->base + WDOG_INTERRUPT_STATUS_REG_OFFSET))
    {
        return;
    }

    /* Clear the IRQ status (EOI) */
    (void)HWREG32(wdt->base + WDOG_INTERRUPT_CLEAR_REG_OFFSET);

    if (wdt->pretimeout_notify.notify)
    {
        wdt->pretimeout_notify.notify(wdt->pretimeout_notify.dev);
    }
}

static void dw_wdt_free(struct dw_wdt *dw_wdt)
{
    if (dw_wdt->base)
    {
        rt_iounmap(dw_wdt->base);
    }

    if (!rt_is_err_or_null(dw_wdt->clk))
    {
        rt_clk_disable(dw_wdt->clk);
    }

    if (!rt_is_err_or_null(dw_wdt->rstc))
    {
        rt_reset_control_assert(dw_wdt->rstc);
        rt_reset_control_put(dw_wdt->rstc);
    }

    rt_free(dw_wdt);
}

static rt_err_t dw_wdt_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct dw_wdt *dw_wdt = rt_calloc(1, sizeof(*dw_wdt));

    if (!dw_wdt)
    {
        return -RT_ENOMEM;
    }

    dw_wdt->base = rt_dm_dev_iomap(dev, 0);

    if (!dw_wdt->base)
    {
        err = -RT_EIO;
        goto _free_res;
    }

    dw_wdt->irq = rt_dm_dev_get_irq(dev, 0);

    if (dw_wdt->irq < 0)
    {
        err = dw_wdt->irq;
        goto _free_res;
    }

    dw_wdt->clk = rt_clk_get_by_name(dev, "pclk");

    if (rt_is_err(dw_wdt->clk))
    {
        dw_wdt->clk = rt_clk_get_by_index(dev, 0);

        if (rt_is_err(dw_wdt->clk))
        {
            err = rt_ptr_err(dw_wdt->clk);
            goto _free_res;
        }
    }

    dw_wdt->rstc = rt_reset_control_get_by_index(dev, 0);

    if (rt_is_err(dw_wdt->rstc))
    {
        err = rt_ptr_err(dw_wdt->rstc);
        goto _free_res;
    }

    rt_reset_control_deassert(dw_wdt->rstc);

    dev->user_data = dw_wdt;

    dw_wdt->rate = rt_clk_get_rate(dw_wdt->clk);
    dw_wdt->parent.ops = &dw_wdt_ops;

    rt_dm_dev_set_name_auto(&dw_wdt->parent.parent, "wdt");
    dev_name = rt_dm_dev_get_name(&dw_wdt->parent.parent);

    rt_hw_interrupt_install(dw_wdt->irq, dw_wdt_isr, dw_wdt, dev_name);
    rt_hw_interrupt_umask(dw_wdt->irq);

#ifdef RT_USING_PM
    rt_pm_device_register(&dw_wdt->parent.parent, &dw_wdt_pm_ops);
#endif

    rt_hw_watchdog_register(&dw_wdt->parent, dev_name, 0, dw_wdt);

    return RT_EOK;

_free_res:
    dw_wdt_free(dw_wdt);

    return err;
}

static rt_err_t dw_wdt_remove(struct rt_platform_device *pdev)
{
    struct dw_wdt *dw_wdt = pdev->parent.user_data;

    rt_hw_interrupt_mask(dw_wdt->irq);
    rt_pic_detach_irq(dw_wdt->irq, dw_wdt);

#ifdef RT_USING_PM
    rt_pm_device_unregister(&dw_wdt->parent.parent);
#endif

    rt_device_unregister(&dw_wdt->parent.parent);

    dw_wdt_free(dw_wdt);

    return RT_EOK;
}

static const struct rt_ofw_node_id dw_wdt_ofw_ids[] =
{
    { .compatible = "snps,dw-wdt" },
    { /* sentinel */ }
};

static struct rt_platform_driver dw_wdt_driver =
{
    .name = "dw-wdt",
    .ids = dw_wdt_ofw_ids,

    .probe = dw_wdt_probe,
    .remove = dw_wdt_remove,
};
RT_PLATFORM_DRIVER_EXPORT(dw_wdt_driver);
