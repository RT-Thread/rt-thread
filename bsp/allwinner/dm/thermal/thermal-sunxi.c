/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "thermal.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_THS_CTL                 0x00
#define SUNXI_THS_EN                  0x04
#define SUNXI_THS_PCTL                0x08
#define SUNXI_THS_MFC                 0x30
#define SUNXI_THS_CALIB               0xa0
#define SUNXI_THS_DATA                0xc0

#define SUNXI_GPADC_CTRL              0x04
#define SUNXI_GPADC_VCM_BUF_EN        RT_BIT(0)

#define SUN252I_F101_THS_CAL_MASK     RT_GENMASK(11, 0)

struct sunxi_thermal
{
    struct rt_thermal_zone_device zone;

    void *ths;
    void *gpadc;
    rt_uint32_t sid_calibration;
    rt_bool_t sid_calibration_valid;
    struct rt_clk *ths_clk;
    struct rt_clk *gpadc_clk;
    struct rt_reset_control *ths_reset;
    struct rt_reset_control *gpadc_reset;
    rt_bool_t ths_clk_enabled;
    rt_bool_t gpadc_clk_enabled;
};

#define to_sunxi_thermal(raw) rt_container_of(raw, struct sunxi_thermal, zone)

static int sun252i_f101_ths_raw_to_temp(rt_uint32_t raw)
{
    if (raw > 1839)
    {
        return (2822 - raw) * 66;
    }

    return (2835 - raw) * 65;
}

static void sun252i_f101_ths_calibrate(struct sunxi_thermal *ths)
{
    int ft_temp;
    int sensor_temp;
    int delta;
    int cdata;
    rt_uint32_t value;
    rt_uint32_t calibration;

    if (!ths->sid_calibration_valid)
    {
        LOG_W("thermal calibration data is unavailable");
        return;
    }

    value = ths->sid_calibration;
    ft_temp = value & SUN252I_F101_THS_CAL_MASK;
    calibration = (value >> 12) & SUN252I_F101_THS_CAL_MASK;
    if (!ft_temp)
    {
        LOG_W("thermal calibration data is empty");
        return;
    }

    sensor_temp = sun252i_f101_ths_raw_to_temp(calibration);
    delta = (ft_temp * 100 - sensor_temp) / -66;
    cdata = 0x800 - delta;
    if (cdata < 0 || cdata > SUN252I_F101_THS_CAL_MASK)
    {
        LOG_W("thermal calibration value is invalid");
        return;
    }

    value = HWREG32(ths->ths + SUNXI_THS_CALIB);
    value &= ~SUN252I_F101_THS_CAL_MASK;
    value |= cdata;
    HWREG32(ths->ths + SUNXI_THS_CALIB) = value;
}

static rt_err_t sun252i_f101_thermal_get_temp(struct rt_thermal_zone_device *zdev,
        int *out_temp)
{
    rt_uint32_t raw;
    struct sunxi_thermal *ths = to_sunxi_thermal(zdev);

    raw = HWREG32(ths->ths + SUNXI_THS_DATA) & SUN252I_F101_THS_CAL_MASK;
    if (!raw)
    {
        return -EAGAIN;
    }

    *out_temp = sun252i_f101_ths_raw_to_temp(raw);

    return RT_EOK;
}

static const struct rt_thermal_zone_ops sun252i_f101_thermal_ops =
{
    .get_temp = sun252i_f101_thermal_get_temp,
};

static void sun252i_f101_thermal_release(struct sunxi_thermal *ths)
{
    if (ths->ths)
    {
        HWREG32(ths->ths + SUNXI_THS_EN) = 0;
    }
    if (!rt_is_err_or_null(ths->ths_reset))
    {
        rt_reset_control_assert(ths->ths_reset);
        rt_reset_control_put(ths->ths_reset);
    }
    if (!rt_is_err_or_null(ths->gpadc_reset))
    {
        rt_reset_control_assert(ths->gpadc_reset);
        rt_reset_control_put(ths->gpadc_reset);
    }
    if (ths->ths_clk_enabled)
    {
        rt_clk_disable_unprepare(ths->ths_clk);
    }
    if (ths->gpadc_clk_enabled)
    {
        rt_clk_disable_unprepare(ths->gpadc_clk);
    }
    if (!rt_is_err_or_null(ths->ths_clk))
    {
        rt_clk_put(ths->ths_clk);
    }
    if (!rt_is_err_or_null(ths->gpadc_clk))
    {
        rt_clk_put(ths->gpadc_clk);
    }
    if (ths->gpadc)
    {
        rt_iounmap(ths->gpadc);
    }
    if (ths->ths)
    {
        rt_iounmap(ths->ths);
    }
    rt_free(ths);
}

static rt_err_t sun252i_f101_thermal_map_calibration(struct rt_device *dev,
        struct sunxi_thermal *ths)
{
    rt_err_t err;
    struct rt_nvmem_cell *cell;

    cell = rt_nvmem_get_cell_by_name(dev, "calibration");
    if (rt_is_err_or_null(cell))
    {
        return rt_is_err(cell) ? rt_ptr_err(cell) : -RT_ENOENT;
    }

    err = rt_nvmem_cell_read_u32(cell, &ths->sid_calibration);
    rt_nvmem_put_cell(cell);
    if (err == sizeof(ths->sid_calibration))
    {
        ths->sid_calibration_valid = RT_TRUE;
        return RT_EOK;
    }

    return err < 0 ? err : -RT_EIO;
}

static rt_err_t sun252i_f101_thermal_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_thermal *ths = rt_calloc(1, sizeof(*ths));

    if (!ths)
    {
        return -RT_ENOMEM;
    }

    ths->ths = rt_ofw_iomap_by_name(dev->ofw_node, "ths");
    ths->gpadc = rt_ofw_iomap_by_name(dev->ofw_node, "gpadc");
    if (!ths->ths || !ths->gpadc)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ths->ths_clk = rt_clk_get_by_name(dev, "ths");
    ths->gpadc_clk = rt_clk_get_by_name(dev, "gpadc");
    ths->ths_reset = rt_reset_control_get_by_name(dev, "ths");
    ths->gpadc_reset = rt_reset_control_get_by_name(dev, "gpadc");
    if (rt_is_err(ths->ths_clk) || rt_is_err(ths->gpadc_clk) ||
            rt_is_err(ths->ths_reset) || rt_is_err(ths->gpadc_reset))
    {
        err = rt_is_err(ths->ths_clk) ? rt_ptr_err(ths->ths_clk) :
                (rt_is_err(ths->gpadc_clk) ? rt_ptr_err(ths->gpadc_clk) :
                (rt_is_err(ths->ths_reset) ? rt_ptr_err(ths->ths_reset) :
                rt_ptr_err(ths->gpadc_reset)));
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(ths->gpadc_reset)) ||
            (err = rt_reset_control_deassert(ths->ths_reset)) ||
            (err = rt_clk_prepare_enable(ths->gpadc_clk)))
    {
        goto _fail;
    }
    ths->gpadc_clk_enabled = RT_TRUE;
    if ((err = rt_clk_prepare_enable(ths->ths_clk)))
    {
        goto _fail;
    }
    ths->ths_clk_enabled = RT_TRUE;

    HWREG32(ths->gpadc + SUNXI_GPADC_CTRL) |= SUNXI_GPADC_VCM_BUF_EN;
    HWREG32(ths->ths + SUNXI_THS_CTL) = (479 << 16) | 47;
    HWREG32(ths->ths + SUNXI_THS_MFC) = RT_BIT(2) | 1;
    HWREG32(ths->ths + SUNXI_THS_PCTL) = 28 << 12;
    HWREG32(ths->ths + SUNXI_THS_EN) = 1;

    if ((err = sun252i_f101_thermal_map_calibration(dev, ths)))
    {
        LOG_W("thermal sensor will run without eFuse calibration: %s", rt_strerror(err));
    }
    else
    {
        sun252i_f101_ths_calibrate(ths);
    }

    /* Four averaged samples take roughly 20 ms with the configured period. */
    rt_hw_us_delay(20000);

    ths->zone.parent.ofw_node = dev->ofw_node;
    ths->zone.ops = &sun252i_f101_thermal_ops;
    /* The F101 DTS has no thermal-zone policy from which to obtain a delay. */
    ths->zone.polling_delay = rt_tick_from_millisecond(1000);
    rt_dm_dev_set_name(&ths->zone.parent, "sun252i-ths");
    if ((err = rt_thermal_zone_device_register(&ths->zone)))
    {
        goto _fail;
    }

    dev->user_data = ths;

    return RT_EOK;

_fail:
    sun252i_f101_thermal_release(ths);

    return err;
}

static rt_err_t sun252i_f101_thermal_remove(struct rt_platform_device *pdev)
{
    struct sunxi_thermal *ths = pdev->parent.user_data;

    rt_thermal_zone_device_unregister(&ths->zone);
    sun252i_f101_thermal_release(ths);

    return RT_EOK;
}

static const struct rt_ofw_node_id sun252i_f101_thermal_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-thermal" },
    { /* sentinel */ }
};

static struct rt_platform_driver sun252i_f101_thermal_driver =
{
    .name = "sun252i-thermal",
    .ids = sun252i_f101_thermal_ofw_ids,
    .probe = sun252i_f101_thermal_probe,
    .remove = sun252i_f101_thermal_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sun252i_f101_thermal_driver);
