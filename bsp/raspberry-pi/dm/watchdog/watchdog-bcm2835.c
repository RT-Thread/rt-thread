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

#include <bcm2835-pm.h>

#define PM_RSTC                     0x1c
#define PM_RSTS                     0x20
#define PM_WDOG                     0x24

#define PM_PASSWORD                 0x5a000000

#define PM_WDOG_TIME_SET            0x000fffff
#define PM_RSTC_WRCFG_CLR           0xffffffcf
#define PM_RSTS_HADWRH_SET          0x00000040
#define PM_RSTC_WRCFG_SET           0x00000030
#define PM_RSTC_WRCFG_FULL_RESET    0x00000020
#define PM_RSTC_RESET               0x00000102

/*
 * The Raspberry Pi firmware uses the RSTS register to know which partition
 * to boot from. The partition value is spread into bits 0, 2, 4, 6, 8, 10.
 * Partition 63 is a special partition used by the firmware to indicate halt.
 */
#define PM_RSTS_RASPBERRYPI_HALT    0x555

#define SECS_TO_WDOG_TICKS(x) ((x) << 16)
#define WDOG_TICKS_TO_SECS(x) ((x) >> 16)

#define USEC_PER_SEC 1000000L

struct bcm2835_wdt
{
    rt_watchdog_t parent;

    void *base;
    rt_uint32_t timeout;
    struct rt_spinlock lock;
};

#define raw_to_bcm2835_wdt(raw) rt_container_of(raw, struct bcm2835_wdt, parent)

static struct bcm2835_wdt *bcm2835_power_off_wdt;

static void bcm2835_wdt_start(struct bcm2835_wdt *bcm2835_wdt)
{
    rt_uint32_t cur;
    rt_ubase_t level = rt_spin_lock_irqsave(&bcm2835_wdt->lock);

    HWREG32(bcm2835_wdt->base + PM_WDOG) = PM_PASSWORD | (SECS_TO_WDOG_TICKS(bcm2835_wdt->timeout) & PM_WDOG_TIME_SET);
    cur = HWREG32(bcm2835_wdt->base + PM_RSTC);
    HWREG32(bcm2835_wdt->base + PM_RSTC) = PM_PASSWORD | (cur & PM_RSTC_WRCFG_CLR) | PM_RSTC_WRCFG_FULL_RESET;

    rt_spin_unlock_irqrestore(&bcm2835_wdt->lock, level);
}

static void bcm2835_wdt_stop(struct bcm2835_wdt *bcm2835_wdt)
{
    HWREG32(bcm2835_wdt->base + PM_RSTC) = PM_PASSWORD | PM_RSTC_RESET;
}

static rt_uint32_t bcm2835_wdt_get_timeleft(struct bcm2835_wdt *bcm2835_wdt)
{
    rt_uint32_t value = HWREG32(bcm2835_wdt->base + PM_WDOG);

    return WDOG_TICKS_TO_SECS(value & PM_WDOG_TIME_SET);
}

static void bcm2835_restart(struct bcm2835_wdt *bcm2835_wdt)
{
    rt_uint32_t val;

    /* Use a timeout of 10 ticks (~150us) */
    HWREG32(bcm2835_wdt->base + PM_WDOG) = 10 | PM_PASSWORD;
    val = HWREG32(bcm2835_wdt->base + PM_RSTC);
    val &= PM_RSTC_WRCFG_CLR;
    val |= PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET;
    HWREG32(bcm2835_wdt->base + PM_RSTC) = val;

    /* No sleeping, possibly atomic. */
    rt_thread_mdelay(1);
}

static rt_err_t bcm2835_wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t bcm2835_wdt_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct bcm2835_wdt *bcm2835_wdt = raw_to_bcm2835_wdt(wdt);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)args = bcm2835_wdt->timeout / USEC_PER_SEC;
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        bcm2835_wdt->timeout = *(rt_uint32_t *)args * USEC_PER_SEC;
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(rt_uint32_t *)args = bcm2835_wdt_get_timeleft(bcm2835_wdt) / USEC_PER_SEC;
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        bcm2835_wdt->timeout = 0;
        break;

    case RT_DEVICE_CTRL_WDT_START:
        bcm2835_wdt_start(bcm2835_wdt);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        bcm2835_wdt_stop(bcm2835_wdt);
        break;

    default:
        status = -RT_EINVAL;
    }

    return status;
}

static const struct rt_watchdog_ops bcm2835_wdt_ops =
{
    .init = bcm2835_wdt_init,
    .control = bcm2835_wdt_control,
};

static void bcm2835_wdt_power_off(void)
{
    rt_uint32_t val;
    struct bcm2835_wdt *bcm2835_wdt = bcm2835_power_off_wdt;

    /*
     * We set the watchdog hard reset bit here to distinguish this reset from
     * the normal (full) reset. bootcode.bin will not reboot after a hard reset.
     */
    val = HWREG32(bcm2835_wdt->base + PM_RSTS);
    val |= PM_PASSWORD | PM_RSTS_RASPBERRYPI_HALT;
    HWREG32(bcm2835_wdt->base + PM_RSTS) = val;

    /* Continue with normal reset mechanism */
    bcm2835_restart(bcm2835_wdt);
}

static void bcm2835_wdt_power_reboot(void)
{
    struct bcm2835_wdt *bcm2835_wdt = bcm2835_power_off_wdt;

    /* Continue with normal reset mechanism */
    bcm2835_restart(bcm2835_wdt);
}

static rt_err_t bcm2835_wdt_probe(struct rt_platform_device *pdev)
{
    const char *dev_name;
    struct bcm2835_pm *pm = pdev->priv;
    struct rt_ofw_node *np = pm->ofw_node;
    struct bcm2835_wdt *bcm2835_wdt = rt_calloc(1, sizeof(*bcm2835_wdt));

    if (!bcm2835_wdt)
    {
        return -RT_ENOMEM;
    }

    bcm2835_wdt->base = pm->base;
    rt_spin_lock_init(&bcm2835_wdt->lock);

    bcm2835_power_off_wdt = bcm2835_wdt;

    if (rt_ofw_prop_read_bool(np, "system-power-controller"))
    {
        if (!rt_dm_machine_shutdown)
        {
            rt_dm_machine_shutdown = bcm2835_wdt_power_off;
        }
    }

    if (!rt_dm_machine_reset)
    {
        rt_dm_machine_reset = bcm2835_wdt_power_reboot;
    }

    pdev->parent.user_data = bcm2835_wdt;

    bcm2835_wdt->parent.ops = &bcm2835_wdt_ops;

    rt_dm_dev_set_name_auto(&bcm2835_wdt->parent.parent, "wdt");
    dev_name = rt_dm_dev_get_name(&bcm2835_wdt->parent.parent);
    rt_hw_watchdog_register(&bcm2835_wdt->parent, dev_name, 0, bcm2835_wdt);

    return RT_EOK;
}

static rt_err_t bcm2835_wdt_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_wdt *bcm2835_wdt = pdev->parent.user_data;

    bcm2835_wdt_stop(bcm2835_wdt);

    rt_device_unregister(&bcm2835_wdt->parent.parent);

    if (rt_dm_machine_shutdown == bcm2835_wdt_power_off)
    {
        rt_dm_machine_shutdown = RT_NULL;
    }

    if (rt_dm_machine_reset == bcm2835_wdt_power_reboot)
    {
        rt_dm_machine_reset = RT_NULL;
    }

    bcm2835_power_off_wdt = RT_NULL;

    rt_free(bcm2835_wdt);

    return RT_EOK;
}

static struct rt_platform_driver bcm2835_wdt_driver =
{
    .name = "bcm2835-wdt",
    .probe = bcm2835_wdt_probe,
    .remove = bcm2835_wdt_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_wdt_driver);
