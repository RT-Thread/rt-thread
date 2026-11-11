/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

/*
 * Note: as per Raspberry Foundation FAQ
 * (https://www.raspberrypi.org/help/faqs/#performanceOperatingTemperature)
 * the recommended temperature range for the SoC -40C to +85C
 * so the trip limit is set to 80C.
 * this applies to all the BCM283X SoC
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "thermal.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define BCM2835_TS_TSENSCTL                     0x00
#define BCM2835_TS_TSENSSTAT                    0x04

#define BCM2835_TS_TSENSCTL_PRWDW               RT_BIT(0)
#define BCM2835_TS_TSENSCTL_RSTB                RT_BIT(1)

/*
 * bandgap reference voltage in 6 mV increments
 * 000b = 1178 mV, 001b = 1184 mV, ... 111b = 1220 mV
 */
#define BCM2835_TS_TSENSCTL_CTRL_BITS           3
#define BCM2835_TS_TSENSCTL_CTRL_SHIFT          2
#define BCM2835_TS_TSENSCTL_CTRL_MASK               \
        RT_GENMASK(BCM2835_TS_TSENSCTL_CTRL_BITS +  \
                BCM2835_TS_TSENSCTL_CTRL_SHIFT - 1, \
                BCM2835_TS_TSENSCTL_CTRL_SHIFT)
#define BCM2835_TS_TSENSCTL_CTRL_DEFAULT        1
#define BCM2835_TS_TSENSCTL_EN_INT              RT_BIT(5)
#define BCM2835_TS_TSENSCTL_DIRECT              RT_BIT(6)
#define BCM2835_TS_TSENSCTL_CLR_INT             RT_BIT(7)
#define BCM2835_TS_TSENSCTL_THOLD_SHIFT         8
#define BCM2835_TS_TSENSCTL_THOLD_BITS          10
#define BCM2835_TS_TSENSCTL_THOLD_MASK               \
        RT_GENMASK(BCM2835_TS_TSENSCTL_THOLD_BITS +  \
                BCM2835_TS_TSENSCTL_THOLD_SHIFT - 1, \
                BCM2835_TS_TSENSCTL_THOLD_SHIFT)
/*
 * time how long the block to be asserted in reset
 * which based on a clock counter (TSENS clock assumed)
 */
#define BCM2835_TS_TSENSCTL_RSTDELAY_SHIFT      18
#define BCM2835_TS_TSENSCTL_RSTDELAY_BITS       8
#define BCM2835_TS_TSENSCTL_REGULEN             RT_BIT(26)

#define BCM2835_TS_TSENSSTAT_DATA_BITS          10
#define BCM2835_TS_TSENSSTAT_DATA_SHIFT         0
#define BCM2835_TS_TSENSSTAT_DATA_MASK               \
        RT_GENMASK(BCM2835_TS_TSENSSTAT_DATA_BITS +  \
                BCM2835_TS_TSENSSTAT_DATA_SHIFT - 1, \
                BCM2835_TS_TSENSSTAT_DATA_SHIFT)
#define BCM2835_TS_TSENSSTAT_VALID              RT_BIT(10)
#define BCM2835_TS_TSENSSTAT_INTERRUPT          RT_BIT(11)

struct bcm2835_thermal
{
    struct rt_thermal_zone_device parent;

    void *regs;
    struct rt_clk *clk;
};

#define raw_to_bcm2835_thermal(raw) rt_container_of(raw, struct bcm2835_thermal, parent)

static int bcm2835_thermal_adc2temp(rt_uint32_t adc, int offset, int slope)
{
    return offset + slope * adc;
}

static int bcm2835_thermal_temp2adc(int temp, int offset, int slope)
{
    temp -= offset;
    temp /= slope;

    if (temp < 0)
    {
        temp = 0;
    }

    if (temp >= RT_BIT(BCM2835_TS_TSENSSTAT_DATA_BITS))
    {
        temp = RT_BIT(BCM2835_TS_TSENSSTAT_DATA_BITS) - 1;
    }

    return temp;
}

static rt_err_t bcm2835_thermal_zone_get_temp(struct rt_thermal_zone_device *zdev,
        int *out_temp)
{
    rt_uint32_t val;
    struct rt_thermal_zone_params *tz_params;
    struct bcm2835_thermal *btz = raw_to_bcm2835_thermal(zdev);

    val = HWREG32(btz->regs + BCM2835_TS_TSENSSTAT);

    if (!(val & BCM2835_TS_TSENSSTAT_VALID))
    {
        return -RT_EIO;
    }

    val &= BCM2835_TS_TSENSSTAT_DATA_MASK;
    tz_params = &btz->parent.params;

    *out_temp = bcm2835_thermal_adc2temp(val, tz_params->offset, tz_params->slope);

    return RT_EOK;
}

const static struct rt_thermal_zone_ops bcm2835_thermal_zone_ops =
{
    .get_temp = bcm2835_thermal_zone_get_temp,
};

static rt_err_t bcm2835_thermal_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    rt_ubase_t rate;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_thermal *btz = rt_calloc(1, sizeof(*btz));

    if (!btz)
    {
        return -RT_ENOMEM;
    }

    btz->regs = rt_dm_dev_iomap(dev, 0);

    if (!btz->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    btz->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(btz->clk))
    {
        err = rt_ptr_err(btz->clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(btz->clk)))
    {
        goto _fail;
    }

    rate = rt_clk_get_rate(btz->clk);

    if (rate < 1920000 || rate > 5000000)
    {
        LOG_W("Clock running at %u Hz is outside of the recommended range: 1.92 to 5MHz", rate);
    }

    btz->parent.parent.ofw_node = dev->ofw_node;
    btz->parent.ops = &bcm2835_thermal_zone_ops;

    rt_dm_dev_set_name(&btz->parent.parent, "bcm2835");

    if ((err = rt_thermal_zone_device_register(&btz->parent)))
    {
        goto _fail;
    }

    /*
     * right now the FW does set up the HW-block, so we are not
     * touching the configuration registers.
     * But if the HW is not enabled, then set it up
     * using "sane" values used by the firmware right now.
     */
    val = HWREG32(btz->regs + BCM2835_TS_TSENSCTL);

    if (!(val & BCM2835_TS_TSENSCTL_RSTB))
    {
        int offset, slope;
        struct rt_thermal_trip trip;
        struct rt_thermal_zone_device *tz = &btz->parent;
        struct rt_thermal_zone_params *tz_params = &tz->params;

        slope = tz_params->slope;
        offset = tz_params->offset;

        if ((err = rt_thermal_zone_get_trip(tz, 0, &trip)))
        {
            rt_thermal_zone_device_unregister(tz);

            LOG_E("Read trip error = %s", rt_strerror(err));
            goto _fail;
        }

        /* set bandgap reference voltage and enable voltage regulator */
        val = (BCM2835_TS_TSENSCTL_CTRL_DEFAULT <<
                BCM2835_TS_TSENSCTL_CTRL_SHIFT) | BCM2835_TS_TSENSCTL_REGULEN;

        /* use the recommended reset duration */
        val |= 0xfe << BCM2835_TS_TSENSCTL_RSTDELAY_SHIFT;

        /*  trip_adc value from info */
        val |= bcm2835_thermal_temp2adc(trip.temperature, offset, slope)
                << BCM2835_TS_TSENSCTL_THOLD_SHIFT;

        /* write the value back to the register as 2 steps */
        HWREG32(btz->regs + BCM2835_TS_TSENSCTL) = val;
        val |= BCM2835_TS_TSENSCTL_RSTB;
        HWREG32(btz->regs + BCM2835_TS_TSENSCTL) = val;
    }

    dev->user_data = btz;

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(btz->clk))
    {
        rt_clk_disable_unprepare(btz->clk);
        rt_clk_put(btz->clk);
    }

    rt_free(btz);

    return err;
}

static rt_err_t bcm2835_thermal_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_thermal *btz = pdev->parent.user_data;

    rt_thermal_zone_device_unregister(&btz->parent);

    rt_clk_disable_unprepare(btz->clk);
    rt_clk_put(btz->clk);

    rt_free(btz);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835_thermal_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-thermal" },
    { .compatible = "brcm,bcm2836-thermal" },
    { .compatible = "brcm,bcm2837-thermal" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_thermal_driver =
{
    .name = "bcm2835-thermal",
    .ids = bcm2835_thermal_ofw_ids,

    .probe = bcm2835_thermal_probe,
    .remove = bcm2835_thermal_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_thermal_driver);
