/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define SUNXI_WDT_IRQ_EN            0x00
#define SUNXI_WDT_CTRL              0x10
#define SUNXI_WDT_CFG               0x14
#define SUNXI_WDT_MODE              0x18

#define SUNXI_WDT_CTRL_RELOAD       (RT_BIT(0) | (0x0a57 << 1))
#define SUNXI_WDT_MODE_ENABLE       RT_BIT(0)
#define SUNXI_WDT_TIMEOUT_SHIFT     4
#define SUNXI_WDT_TIMEOUT_MASK      RT_GENMASK(7, 4)
#define SUNXI_WDT_RESET_MASK        RT_GENMASK(1, 0)
#define SUNXI_WDT_RESET_SYSTEM      1
#define SUNXI_WDT_KEY               0x16aa0000

static const rt_uint8_t sunxi_wdt_timeout_codes[] =
{
    [1] = 0x1, [2] = 0x2, [3] = 0x3, [4] = 0x4,
    [5] = 0x5, [6] = 0x6, [8] = 0x7, [10] = 0x8,
    [12] = 0x9, [14] = 0xa, [16] = 0xb,
};

struct sunxi_wdt
{
    rt_watchdog_t parent;
    void *base;
    rt_uint32_t timeout;
    const rt_uint8_t *timeout_codes;
};

#define to_sunxi_wdt(raw) rt_container_of(raw, struct sunxi_wdt, parent)

static struct sunxi_wdt *machine_wdt;

static const rt_uint8_t sunxi_wdt_timeout_codes_v2[] =
{
    [1] = 0x5, [2] = 0x6, [3] = 0x7, [4] = 0x8,
    [5] = 0x9, [6] = 0xa, [8] = 0xb, [10] = 0xc,
    [12] = 0xd, [14] = 0xe, [16] = 0xf,
};

static rt_uint32_t sunxi_wdt_select_timeout(struct sunxi_wdt *wdt,
        rt_uint32_t requested)
{
    rt_uint32_t timeout;

    for (timeout = rt_max_t(rt_uint32_t, requested, 1); timeout <= 16; ++timeout)
    {
        if (wdt->timeout_codes[timeout])
        {
            return timeout;
        }
    }

    return 0;
}

static void sunxi_wdt_ping(struct sunxi_wdt *wdt)
{
    HWREG32(wdt->base + SUNXI_WDT_CTRL) = SUNXI_WDT_CTRL_RELOAD;
}

static rt_err_t sunxi_wdt_set_timeout(struct sunxi_wdt *wdt,
        rt_uint32_t requested)
{
    rt_uint32_t timeout = sunxi_wdt_select_timeout(wdt, requested);
    rt_uint32_t value;

    if (!timeout)
    {
        return -RT_EINVAL;
    }

    value = HWREG32(wdt->base + SUNXI_WDT_MODE);
    value &= ~SUNXI_WDT_TIMEOUT_MASK;
    value |= wdt->timeout_codes[timeout] << SUNXI_WDT_TIMEOUT_SHIFT;
    HWREG32(wdt->base + SUNXI_WDT_MODE) = value | SUNXI_WDT_KEY;

    wdt->timeout = timeout;
    sunxi_wdt_ping(wdt);

    return RT_EOK;
}

static rt_err_t sunxi_wdt_start(struct sunxi_wdt *wdt)
{
    rt_uint32_t value;
    rt_err_t err;

    if ((err = sunxi_wdt_set_timeout(wdt, wdt->timeout)))
    {
        return err;
    }

    value = HWREG32(wdt->base + SUNXI_WDT_CFG);
    value &= ~SUNXI_WDT_RESET_MASK;
    value |= SUNXI_WDT_RESET_SYSTEM;
    HWREG32(wdt->base + SUNXI_WDT_CFG) = value | SUNXI_WDT_KEY;

    value = HWREG32(wdt->base + SUNXI_WDT_MODE);
    HWREG32(wdt->base + SUNXI_WDT_MODE) = value | SUNXI_WDT_MODE_ENABLE |
            SUNXI_WDT_KEY;

    return RT_EOK;
}

static void sunxi_wdt_stop(struct sunxi_wdt *wdt)
{
    HWREG32(wdt->base + SUNXI_WDT_MODE) = SUNXI_WDT_KEY;
}

static void sunxi_wdt_machine_reset(void)
{
    struct sunxi_wdt *wdt = machine_wdt;

    if (!wdt)
    {
        return;
    }

    sunxi_wdt_stop(wdt);
    HWREG32(wdt->base + SUNXI_WDT_IRQ_EN) = 0;
    HWREG32(wdt->base + SUNXI_WDT_CFG) = SUNXI_WDT_KEY |
            SUNXI_WDT_RESET_SYSTEM;
    HWREG32(wdt->base + SUNXI_WDT_MODE) = SUNXI_WDT_KEY |
            SUNXI_WDT_MODE_ENABLE;

    for (;;)
    {
        rt_hw_cpu_relax();
    }
}

static rt_err_t sunxi_wdt_init(rt_watchdog_t *watchdog)
{
    RT_UNUSED(watchdog);
    return RT_EOK;
}

static rt_err_t sunxi_wdt_control(rt_watchdog_t *watchdog, int cmd,
        void *args)
{
    struct sunxi_wdt *wdt = to_sunxi_wdt(watchdog);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        if (!args)
        {
            return -RT_EINVAL;
        }
        *(rt_uint32_t *)args = wdt->timeout;
        return RT_EOK;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (!args)
        {
            return -RT_EINVAL;
        }
        return sunxi_wdt_set_timeout(wdt, *(rt_uint32_t *)args);
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        sunxi_wdt_ping(wdt);
        return RT_EOK;
    case RT_DEVICE_CTRL_WDT_START:
        return sunxi_wdt_start(wdt);
    case RT_DEVICE_CTRL_WDT_STOP:
        sunxi_wdt_stop(wdt);
        return RT_EOK;
    default:
        return -RT_EINVAL;
    }
}

static const struct rt_watchdog_ops sunxi_wdt_ops =
{
    .init = sunxi_wdt_init,
    .control = sunxi_wdt_control,
};

static rt_err_t sunxi_wdt_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_wdt *wdt = rt_calloc(1, sizeof(*wdt));

    if (!wdt)
    {
        return -RT_ENOMEM;
    }

    wdt->base = rt_dm_dev_iomap(dev, 0);
    if (!wdt->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (rt_ofw_node_is_compatible(dev->ofw_node,
            "allwinner,sun252i-f101-wdt"))
    {
        wdt->timeout_codes = sunxi_wdt_timeout_codes_v2;
    }
    else
    {
        wdt->timeout_codes = sunxi_wdt_timeout_codes;
    }
    wdt->timeout = 16;
    sunxi_wdt_stop(wdt);
    wdt->parent.ops = &sunxi_wdt_ops;
    wdt->parent.parent.ofw_node = dev->ofw_node;
    rt_dm_dev_set_name_auto(&wdt->parent.parent, "wdt");
    name = rt_dm_dev_get_name(&wdt->parent.parent);

    if ((err = rt_hw_watchdog_register(&wdt->parent, name, 0, wdt)))
    {
        goto _fail;
    }

    dev->user_data = wdt;
    if (!rt_dm_machine_reset)
    {
        machine_wdt = wdt;
        rt_dm_machine_reset = sunxi_wdt_machine_reset;
    }
    return RT_EOK;

_fail:
    if (wdt->base)
    {
        rt_iounmap(wdt->base);
    }
    rt_free(wdt);
    return err;
}

static rt_err_t sunxi_wdt_remove(struct rt_platform_device *pdev)
{
    struct sunxi_wdt *wdt = pdev->parent.user_data;

    if (machine_wdt == wdt)
    {
        machine_wdt = RT_NULL;
        rt_dm_machine_reset = RT_NULL;
    }
    sunxi_wdt_stop(wdt);
    rt_device_unregister(&wdt->parent.parent);
    rt_iounmap(wdt->base);
    rt_free(wdt);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_wdt_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-wdt" },
    { .compatible = "allwinner,sun20i-d1-wdt" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_wdt_driver =
{
    .name = "sunxi-wdt",
    .ids = sunxi_wdt_ofw_ids,
    .probe = sunxi_wdt_probe,
    .remove = sunxi_wdt_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_wdt_driver);
