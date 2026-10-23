/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "thermal.h616"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define H616_THS_CTL        0x00
#define H616_THS_ENABLE     0x04
#define H616_THS_PERIOD     0x08
#define H616_THS_IRQ_ENABLE 0x10
#define H616_THS_FILTER     0x30
#define H616_THS_CALIB      0xa0
#define H616_THS_DATA       0xc0
#define H616_THS_SENSORS    4
#define H616_THS_MASK       0xfff

struct h616_thermal
{
    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *reset;
    rt_bool_t clock_enabled;
    rt_bool_t reset_deasserted;
    struct rt_thermal_zone_device zones[H616_THS_SENSORS];
};

static int h616_ths_temperature(unsigned int raw)
{
    return 263655 - (int)raw * 81;
}

static rt_err_t h616_ths_get_temp(struct rt_thermal_zone_device *zone, int *temp)
{
    struct h616_thermal *ths = zone->priv;
    rt_uint32_t raw = HWREG32(ths->base + H616_THS_DATA + zone->zone_id * 4);

    raw &= H616_THS_MASK;
    if (!raw)
    {
        return -RT_EBUSY;
    }

    /* Factory deviation is applied only to readings, not calibration. */
    *temp = h616_ths_temperature(raw) + 8000;
    return RT_EOK;
}

static const struct rt_thermal_zone_ops h616_ths_ops = {
    .get_temp = h616_ths_get_temp,
};

static rt_err_t h616_ths_calibrate(struct rt_device *dev, struct h616_thermal *ths)
{
    rt_uint8_t data[8];
    rt_uint16_t words[4];
    rt_uint32_t regs[2] = { 0, 0 };
    struct rt_nvmem_cell *cell;
    rt_ssize_t size;
    int i, factory_temp;

    cell = rt_nvmem_get_cell_by_name(dev, "calibration");
    if (rt_is_err(cell))
    {
        return rt_ptr_err(cell);
    }
    if (!cell)
    {
        return -RT_ENOENT;
    }
    size = rt_nvmem_cell_read(cell, data, sizeof(data));
    rt_nvmem_put_cell(cell);
    if (size != sizeof(data))
    {
        return size < 0 ? size : -RT_EIO;
    }

    for (i = 0; i < 4; ++i)
    {
        words[i] = data[2 * i] | ((rt_uint16_t)data[2 * i + 1] << 8);
    }
    if (!(words[0] & H616_THS_MASK) || (words[0] & H616_THS_MASK) == H616_THS_MASK)
    {
        return -RT_EINVAL;
    }
    factory_temp = (words[0] & H616_THS_MASK) * 100;

    for (i = 0; i < H616_THS_SENSORS; ++i)
    {
        int raw, calibration;

        /* Sensor 3 occupies the high nibbles of the other three words. */
        raw = i == 3 ? (words[1] >> 12) | ((words[2] >> 12) << 4) |
                           ((words[3] >> 12) << 8)
                     : words[i + 1] & H616_THS_MASK;
        calibration = 0x800 - (h616_ths_temperature(raw) - factory_temp) / 81;
        if (calibration < 0 || calibration > H616_THS_MASK)
        {
            return -RT_EINVAL;
        }
        regs[i / 2] |= (rt_uint32_t)calibration << ((i % 2) * 16);
    }

    for (i = 0; i < 2; ++i)
    {
        rt_uint32_t value = HWREG32(ths->base + H616_THS_CALIB + i * 4);
        HWREG32(ths->base + H616_THS_CALIB + i * 4) =
            (value & ~0x0fff0fffU) | regs[i];
    }
    return RT_EOK;
}

static rt_err_t h616_ths_enable_analog(struct rt_device *dev)
{
    struct rt_ofw_node *np;
    struct rt_syscon *syscon;
    void *base;

    np = rt_ofw_parse_phandle(dev->ofw_node, "allwinner,sram", 0);
    if (!np)
    {
        /* Older U-Boot trees omit the THS SRAM phandle. */
        np = rt_ofw_find_node_by_compatible(RT_NULL, "allwinner,sun50i-h616-system-control");
    }
    if (!np)
    {
        return -RT_ENOENT;
    }

    syscon = rt_syscon_find_by_ofw_node(np);
    if (syscon)
    {
        rt_ofw_node_put(np);
        return rt_syscon_update_bits(syscon, 0, RT_BIT(16), 0);
    }

    /* Legacy trees lack the generic syscon compatible as well. */
    base = rt_ofw_iomap(np, 0);
    rt_ofw_node_put(np);
    if (!base)
    {
        return -RT_EIO;
    }
    HWREG32(base) &= ~RT_BIT(16);
    rt_iounmap(base);
    return RT_EOK;
}

static void h616_ths_release(struct h616_thermal *ths)
{
    if (ths->clock_enabled)
    {
        HWREG32(ths->base + H616_THS_ENABLE) = 0;
        rt_clk_disable_unprepare(ths->clk);
    }
    if (ths->reset_deasserted)
    {
        rt_reset_control_assert(ths->reset);
    }
    if (ths->clk && !rt_is_err(ths->clk))
    {
        rt_clk_put(ths->clk);
    }
    if (ths->reset && !rt_is_err(ths->reset))
    {
        rt_reset_control_put(ths->reset);
    }
    if (ths->base)
    {
        rt_iounmap(ths->base);
    }
    rt_free(ths);
}

static rt_err_t h616_ths_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct h616_thermal *ths;
    rt_err_t err;
    int i, registered = 0;

    ths = rt_calloc(1, sizeof(*ths));
    if (!ths)
    {
        return -RT_ENOMEM;
    }
    ths->base = rt_dm_dev_iomap(dev, 0);
    if (!ths->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    ths->clk = rt_clk_get_by_name(dev, "bus");
    ths->reset = rt_reset_control_get_by_index(dev, 0);
    if (!ths->clk || rt_is_err(ths->clk) || !ths->reset || rt_is_err(ths->reset))
    {
        err = -RT_ENOENT;
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(ths->reset)))
    {
        goto _fail;
    }
    ths->reset_deasserted = RT_TRUE;
    if ((err = rt_clk_prepare_enable(ths->clk)))
    {
        goto _fail;
    }
    ths->clock_enabled = RT_TRUE;

    HWREG32(ths->base + H616_THS_ENABLE) = 0;
    HWREG32(ths->base + H616_THS_IRQ_ENABLE) = 0;
    if ((err = h616_ths_enable_analog(dev)) ||
        (err = h616_ths_calibrate(dev, ths)))
    {
        LOG_E("THS setup/calibration failed: %d", err);
        goto _fail;
    }
    HWREG32(ths->base + H616_THS_CTL) = (479 << 16) | 47;
    HWREG32(ths->base + H616_THS_FILTER) = RT_BIT(2) | 1;
    HWREG32(ths->base + H616_THS_PERIOD) = 365 << 12;
    HWREG32(ths->base + H616_THS_ENABLE) = 0xf;

    for (i = 0; i < H616_THS_SENSORS; ++i)
    {
        struct rt_thermal_zone_device *zone = &ths->zones[i];

        zone->parent.ofw_node = dev->ofw_node;
        zone->zone_id = i;
        zone->priv = ths;
        zone->ops = &h616_ths_ops;
        zone->polling_delay = rt_tick_from_millisecond(1000);
        rt_dm_dev_set_name(&zone->parent, "sun50i-h616-ths");
        err = rt_thermal_zone_device_register(zone);
        if (err)
        {
            LOG_E("sensor %d registration failed: %d", i, err);
            continue;
        }
        /* DT zones with no polling expect IRQs; this driver uses polling. */
        rt_mutex_take(&zone->mutex, RT_WAITING_FOREVER);
        if (!zone->polling_delay)
        {
            zone->polling_delay = rt_tick_from_millisecond(1000);
        }
        rt_mutex_release(&zone->mutex);
        rt_work_submit(&zone->poller, zone->polling_delay);
        ++registered;
    }
    if (!registered)
    {
        goto _fail;
    }
    dev->user_data = ths;
    return RT_EOK;

_fail:
    h616_ths_release(ths);
    return err;
}

static rt_err_t h616_ths_remove(struct rt_platform_device *pdev)
{
    /* Permanent SoC sensors: keep resources while thermal pollers are live. */
    return -RT_EBUSY;
}

static const struct rt_ofw_node_id h616_ths_ids[] = {
    { .compatible = "allwinner,sun50i-h616-ths" },
    { /* sentinel */ }
};

static struct rt_platform_driver h616_ths_driver = {
    .name = "thermal-sun50i-h616",
    .ids = h616_ths_ids,
    .probe = h616_ths_probe,
    .remove = h616_ths_remove,
};
RT_PLATFORM_DRIVER_EXPORT(h616_ths_driver);
