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

#define DBG_TAG "wdt.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Watchdog Timer Registers Offset */
#define WDT_WMER                        0x00b8
#define WDT_WMR                         0x00bc
#define WDT_WVR                         0x00cc
#define WDT_WCR                         0x00c8
#define WDT_WSR                         0x00c0
#define WDT_WFAR                        0x00b0
#define WDT_WSAR                        0x00b4
#define WDT_WICR                        0x00c4

/* Default timeout is 60s */
#define SPACEMIT_WATCHDOG_MAX_TIMEOUT   255
#define SPACEMIT_WATCHDOG_EXPIRE_TIME   100
/* Touch watchdog every 30s */
#define SPACEMIT_WATCHDOG_FEED_TIMEOUT  30

#define MPMU_APRR                       0x1020
#define MPMU_APRR_WDTR                  RT_BIT(4)
#define DEFAULT_SHIFT                   8
/*
 * MPMU_APSR is a dummy reg which is used to handle reboot
 * cmds. Its layout is:
 *      bit0~7:   untouchable
 *      bit8~11:  set to 0x1 when normal boot with no parameter
 *                set to 0x5 for other valid cmds.
 */
#define MPMU_ARSR                       0x1028
#define MPMU_ARSR_REBOOT_CMD(x)         ((x) << 8)
#define MPMU_ARSR_SWR_MASK              (0xf << 8)
#define REBOOT_CMD_NORMAL               0x1
#define REBOOT_CMD_VALID                0x5

struct spa_wdt
{
    rt_watchdog_t parent;

    void *wdt_base;
    void *mpmu_base;

    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    rt_uint32_t timeout;

    rt_bool_t ctrl;
    rt_bool_t wdt_clk_open;
    rt_bool_t enable_restart_handler;

    struct rt_spinlock wdt_lock;
};

#define raw_to_spa_wdt(raw) rt_container_of(raw, struct spa_wdt, parent)

rt_inline rt_uint32_t spa_wdt_read(struct spa_wdt *swdt, unsigned reg)
{
    return HWREG32(swdt->wdt_base + reg);
}

rt_inline void spa_wdt_write_access(struct spa_wdt *swdt)
{
    HWREG32(swdt->wdt_base + WDT_WFAR) = 0xbaba;
    HWREG32(swdt->wdt_base + WDT_WSAR) = 0xeb10;
}

rt_inline void spa_wdt_write(struct spa_wdt *swdt, unsigned reg, rt_uint32_t val)
{
    spa_wdt_write_access(swdt);
    HWREG32(swdt->wdt_base + reg) = val;
}

static rt_err_t spa_wdt_set_timeout(struct spa_wdt *swdt, unsigned timeout)
{
    /*
     * the wdt timer is 16 bit,
     * frequence is 256HZ
     */
    unsigned int tick = timeout << DEFAULT_SHIFT;

    if ((long long)tick > 0xffff)
    {
        timeout = SPACEMIT_WATCHDOG_MAX_TIMEOUT;
        tick = timeout << DEFAULT_SHIFT;
    }

    spa_wdt_write(swdt, WDT_WMR, tick);

    swdt->timeout = timeout;

    return RT_EOK;
}

static void spa_enable_wdt_clk(struct spa_wdt *swdt)
{
    rt_spin_lock(&swdt->wdt_lock);

    if (!swdt->wdt_clk_open)
    {
        rt_clk_prepare_enable(swdt->clk);
        rt_reset_control_deassert(swdt->rstc);
        swdt->wdt_clk_open = RT_TRUE;
    }

    rt_spin_unlock(&swdt->wdt_lock);
}

static void spa_disable_wdt_clk(struct spa_wdt *swdt)
{
    rt_spin_lock(&swdt->wdt_lock);

    if (swdt->wdt_clk_open)
    {
        rt_clk_disable_unprepare(swdt->clk);
        rt_reset_control_assert(swdt->rstc);
        swdt->wdt_clk_open = RT_FALSE;
    }

    rt_spin_unlock(&swdt->wdt_lock);
}

static rt_err_t spa_wdt_stop(struct spa_wdt *swdt)
{
    rt_spin_lock(&swdt->wdt_lock);

    /* Reset counter */
    spa_wdt_write(swdt, WDT_WCR, 0x1);

    /* Disable WDT */
    spa_wdt_write(swdt, WDT_WMER, 0x0);

    swdt->ctrl = RT_FALSE;

    rt_spin_unlock(&swdt->wdt_lock);

    rt_thread_mdelay(3);

    spa_disable_wdt_clk(swdt);

    return RT_EOK;
}

static rt_err_t spa_wdt_start(struct spa_wdt *swdt)
{
    void *mpmu_aprr;
    rt_uint32_t reg;

    spa_enable_wdt_clk(swdt);

    rt_spin_lock(&swdt->wdt_lock);

    /* Set timeout = 100s */
    spa_wdt_set_timeout(swdt, SPACEMIT_WATCHDOG_EXPIRE_TIME);

    /* Enable counter and rstc/interrupt */
    spa_wdt_write(swdt, WDT_WMER, 0x3);

    /* Negate hardware rstc to the WDT after system rstc */
    mpmu_aprr = swdt->mpmu_base + MPMU_APRR;
    reg = HWREG32(mpmu_aprr);
    reg |= MPMU_APRR_WDTR;
    HWREG32(mpmu_aprr) = reg;

    /* Clear previous WDT status */
    spa_wdt_write(swdt, WDT_WSR, 0x0);

    swdt->ctrl = RT_TRUE;

    rt_spin_unlock(&swdt->wdt_lock);

    return RT_EOK;
}

static rt_err_t spa_wdt_ping(struct spa_wdt *swdt)
{
    rt_spin_lock(&swdt->wdt_lock);

    spa_wdt_write(swdt, WDT_WCR, 0x1);

    rt_spin_unlock(&swdt->wdt_lock);

    return RT_EOK;
}

static rt_err_t spa_wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t spa_wdt_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct spa_wdt *swdt = raw_to_spa_wdt(wdt);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)args = swdt->timeout;
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        spa_wdt_set_timeout(swdt, *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        err = -RT_ENOSYS;
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        spa_wdt_ping(swdt);
        break;

    case RT_DEVICE_CTRL_WDT_START:
        spa_wdt_start(swdt);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        spa_wdt_stop(swdt);
        break;

    default:
        err = -RT_EINVAL;
    }

    return err;
}

static const struct rt_watchdog_ops spa_wdt_ops =
{
    .init = spa_wdt_init,
    .control = spa_wdt_control,
};

static rt_err_t spa_wdt_restart_handler(struct rt_device *dev, char *cmd)
{
    rt_uint32_t reg;
    void *mpmu_arsr, *mpmu_aprr;
    rt_watchdog_t *wdt = rt_container_of(dev, rt_watchdog_t, parent);
    struct spa_wdt *swdt = raw_to_spa_wdt(wdt);

    rt_hw_spin_lock(&swdt->wdt_lock.lock);

    mpmu_arsr = swdt->mpmu_base + MPMU_ARSR;
    reg = HWREG32(mpmu_arsr);
    reg &= ~MPMU_ARSR_SWR_MASK;

    if (!cmd)
    {
        reg |= MPMU_ARSR_REBOOT_CMD(REBOOT_CMD_NORMAL);
    }
    else
    {
        reg |= MPMU_ARSR_REBOOT_CMD(REBOOT_CMD_VALID);
    }

    HWREG32(mpmu_arsr) = reg;

    spa_enable_wdt_clk(swdt);

    spa_wdt_write(swdt, WDT_WSR, 0x0);
    spa_wdt_write(swdt, WDT_WMR, 0x1);
    spa_wdt_write(swdt, WDT_WMER, 0x3);
    spa_wdt_write(swdt, WDT_WCR, 0x1);

    mpmu_aprr = swdt->mpmu_base + MPMU_APRR;
    reg = HWREG32(mpmu_aprr);
    reg |= MPMU_APRR_WDTR;
    HWREG32(mpmu_aprr) = reg;

    rt_thread_mdelay(5000);

    rt_hw_spin_unlock(&swdt->wdt_lock.lock);

    return RT_EOK;
}

#ifdef RT_USING_PM
static rt_err_t spa_wdt_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_watchdog_t *wdt = rt_container_of(device, rt_watchdog_t, parent);
    struct spa_wdt *swdt = raw_to_spa_wdt(wdt);

    if (swdt->ctrl)
    {
        spa_wdt_stop(swdt);
    }

    return RT_EOK;
}

static void spa_wdt_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_watchdog_t *wdt = rt_container_of(device, rt_watchdog_t, parent);
    struct spa_wdt *swdt = raw_to_spa_wdt(wdt);

    if (swdt->ctrl)
    {
        spa_wdt_start(swdt);
    }
}

static const struct rt_device_pm_ops spa_wdt_pm_ops =
{
    .suspend = spa_wdt_pm_suspend,
    .resume = spa_wdt_pm_resume,
};
#endif /* RT_USING_PM */

static void spa_wdt_free(struct spa_wdt *swdt)
{
    if (swdt->ctrl)
    {
        spa_wdt_stop(swdt);
    }

    spa_disable_wdt_clk(swdt);

    if (!rt_is_err_or_null(swdt->clk))
    {
        rt_clk_put(swdt->clk);
    }

    if (!rt_is_err_or_null(swdt->rstc))
    {
        rt_reset_control_put(swdt->rstc);
    }
}

static rt_err_t spa_wdt_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    void *mpmu_arsr;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct spa_wdt *swdt = rt_calloc(1, sizeof(*swdt));

    if (!swdt)
    {
        return -RT_ENOMEM;
    }

    if (!(swdt->wdt_base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(swdt->mpmu_base = rt_dm_dev_iomap(dev, 1)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    mpmu_arsr = swdt->mpmu_base + MPMU_ARSR;
    HWREG32(mpmu_arsr) = HWREG32(mpmu_arsr) & ~MPMU_ARSR_SWR_MASK;

    swdt->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(swdt->clk))
    {
        err = rt_ptr_err(swdt->clk);
        goto _fail;
    }

    swdt->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(swdt->rstc))
    {
        err = rt_ptr_err(swdt->rstc);
        goto _fail;
    }

    swdt->enable_restart_handler = rt_dm_dev_prop_read_bool(dev, "spa,wdt-enable-restart-handler");

    /*
     * The writing of some WDT registers must be
     * under the condition of that WDT clock is on
     */
    spa_enable_wdt_clk(swdt);

    rt_spin_lock_init(&swdt->wdt_lock);

    dev->user_data = swdt;

    swdt->parent.ops = &spa_wdt_ops;

    rt_dm_dev_set_name_auto(&swdt->parent.parent, "wdt");
    dev_name = rt_dm_dev_get_name(&swdt->parent.parent);

    if ((err = rt_hw_watchdog_register(&swdt->parent, dev_name, 0, swdt)))
    {
        goto _fail;
    }

#ifdef RT_USING_PM
    rt_pm_device_register(&swdt->parent.parent, &spa_wdt_pm_ops);
#endif

    if (swdt->enable_restart_handler)
    {
        rt_dm_reboot_mode_register(&swdt->parent.parent, spa_wdt_restart_handler);
    }

    return RT_EOK;

_fail:
    spa_wdt_free(swdt);

    return err;
}

static rt_err_t spa_wdt_remove(struct rt_platform_device *pdev)
{
    struct spa_wdt *swdt = pdev->parent.user_data;

#ifdef RT_USING_PM
    rt_pm_device_unregister(&swdt->parent.parent);
#endif

    rt_device_unregister(&swdt->parent.parent);

    spa_wdt_free(swdt);

    return RT_EOK;
}

static rt_err_t spa_wdt_shutdown(struct rt_platform_device *pdev)
{
    struct spa_wdt *swdt = pdev->parent.user_data;

    spa_wdt_stop(swdt);

    /* No need to disable clk if enable restart_handler */
    if (swdt->enable_restart_handler)
    {
        spa_enable_wdt_clk(swdt);
    }

    return RT_EOK;
}

static const struct rt_ofw_node_id spa_wdt_ofw_ids[] =
{
    { .compatible = "spacemit,soc-wdt" },
    { /* sentinel */ }
};

static struct rt_platform_driver spa_wdt_driver =
{
    .name = "spa-wdt",
    .ids = spa_wdt_ofw_ids,

    .probe = spa_wdt_probe,
    .remove = spa_wdt_remove,
    .shutdown = spa_wdt_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(spa_wdt_driver);
