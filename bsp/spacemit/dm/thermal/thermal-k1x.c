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

#define DBG_TAG "thermal.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define BITS(_start, _end)                  ((RT_BIT(_end) - RT_BIT(_start)) + RT_BIT(_end))

#define MAX_SENSOR_NUMBER                   5
#define TEMPERATURE_OFFSET                  278

#define REG_TSEN_INT_MASK                   0x14
#define TSEN_EMERGENT_INT_OFFSET            23
#define REG_EMERGENT_REBOOT_TEMP_THR        0x68
#define REG_EMERGENT_REBOOT_TEMP_THR_MSK    0xffff

#define REG_TSEN_TIME_CTRL                  0x0c
#define BITS_TIME_CTRL_MASK                 BITS(0, 23)
#define VALUE_FILTER_PERIOD                 (0x3000 << 8)
#define BITS_RST_ADC_CNT                    BITS(4, 7)
#define VALUE_WAIT_REF_CNT                  (0xf << 0)

#define BIT_TSEN_RAW_SEL                    RT_BIT(7)
#define BIT_TEMP_MODE                       RT_BIT(3)
#define BIT_EN_SENSOR                       RT_BIT(0)
#define BITS_TSEN_SW_CTRL                   BITS(18, 21)
#define BITS_CTUNE                          BITS(8, 11)
#define REG_TSEN_PCTRL                      0x00

#define REG_TSEN_PCTRL2                     0x04
#define BITS_SDM_CLK_SEL                    BITS(14, 15)
#define BITS_SDM_CLK_SEL_24M                (0 << 14)

#define TSEN_INT_MASK                       RT_BIT(0)
#define BIT_HW_AUTO_MODE                    RT_BIT(23)

#define MAX_SENSOR_NUMBER                   5

struct sensor_enable
{
    rt_uint32_t bjt_en;
    rt_uint32_t offset;
    rt_uint32_t bit_msk;
    rt_uint32_t en_val;
};

struct sensor_data
{
    rt_uint32_t data_reg;
    rt_uint32_t offset;
    rt_uint32_t bit_msk;
};

struct sensor_thrsh
{
    rt_uint32_t temp_thrsh;
    rt_uint32_t low_offset;
    rt_uint32_t high_offset;
};

struct k1x_thermal_sensor_desc
{
    rt_uint32_t int_msk;
    rt_uint32_t int_clr;
    rt_uint32_t int_sta;
    rt_uint32_t offset;
    rt_uint32_t bit_msk;
    struct sensor_enable se;
    struct sensor_data sd;
    struct sensor_thrsh sr;
};

struct k1x_thermal;

struct k1x_thermal_sensor
{
    struct rt_thermal_zone_device parent;

    void *regs;
    struct k1x_thermal_sensor_desc *desc;
};

#define raw_to_k1x_thermal_sensor(raw) rt_container_of(raw, struct k1x_thermal_sensor, parent)

struct k1x_thermal
{
    int irq;
    void *regs;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    /* Sensor range */
    rt_uint32_t sr[2];
    struct k1x_thermal_sensor *sensors;
};

static rt_err_t k1x_thermal_get_temp(struct rt_thermal_zone_device *zdev, int *out_temp)
{
    struct k1x_thermal_sensor *sensor = raw_to_k1x_thermal_sensor(zdev);
    struct k1x_thermal_sensor_desc *desc = sensor->desc;

    *out_temp = HWREG32(sensor->regs + desc->sd.data_reg);
    *out_temp &= desc->sd.bit_msk;
    *out_temp >>= desc->sd.offset;
    *out_temp -= TEMPERATURE_OFFSET;
    *out_temp *= 1000;

    return RT_EOK;
}

static rt_err_t k1x_thermal_set_trips(struct rt_thermal_zone_device *zdev,
        int low_temp, int high_temp)
{
    rt_uint32_t temp;
    int over_thrsh = high_temp, under_thrsh = low_temp;
    struct k1x_thermal_sensor *sensor = raw_to_k1x_thermal_sensor(zdev);
    struct k1x_thermal_sensor_desc *desc = sensor->desc;

    /* Set overflow */
    over_thrsh /= 1000;
    over_thrsh += TEMPERATURE_OFFSET;

    temp = HWREG32(sensor->regs + desc->sr.temp_thrsh);
    temp &= ~0xffff0000;
    temp |= (over_thrsh << desc->sr.high_offset);
    HWREG32(sensor->regs + desc->sr.temp_thrsh) = temp;

    /* set underflow */
    if (low_temp < 0)
    {
        under_thrsh = 0;
    }

    under_thrsh /= 1000;
    under_thrsh += TEMPERATURE_OFFSET;
    temp = HWREG32(sensor->regs + desc->sr.temp_thrsh);
    temp &= ~0xffff;
    temp |= (under_thrsh << desc->sr.low_offset);
    HWREG32(sensor->regs + desc->sr.temp_thrsh) = temp;

    return RT_EOK;
}

static const struct rt_thermal_zone_ops k1x_thermal_ops =
{
    .get_temp = k1x_thermal_get_temp,
    .set_trips = k1x_thermal_set_trips,
};

static void k1x_thermal_isr(int irqno, void *param)
{
    rt_uint32_t status, msk;
    struct k1x_thermal_sensor *sensor = param;
    struct k1x_thermal_sensor_desc *desc = sensor->desc;

    /* Get the status */
    status = HWREG32(sensor->regs + desc->int_sta);
    status &= desc->bit_msk;

    if (!status)
    {
        return;
    }

    /* Then clear the pending */
    msk = HWREG32(sensor->regs + desc->int_clr);
    msk |= status;
    HWREG32(sensor->regs + desc->int_clr) = msk;

    rt_thermal_zone_device_update(&sensor->parent, RT_THERMAL_MSG_EVENT_UNSPECIFIED);
}

static rt_err_t init_sensors(struct rt_device *dev, struct k1x_thermal *thermal,
        struct k1x_thermal_sensor_desc *desc)
{
    rt_err_t err;
    rt_uint32_t temp;

    /* Read the sensor range */
    err = rt_dm_dev_prop_read_u32_array_index(dev, "sensor_range", 0, 2, thermal->sr);
    if (err < 0)
    {
        LOG_E("Get sensor range error");
        return err;
    }

    if (thermal->sr[1] >= MAX_SENSOR_NUMBER)
    {
        LOG_E("Un-fitable sensor range");
        return -RT_EINVAL;
    }

    /* First: disable all the interrupts */
    HWREG32(thermal->regs + REG_TSEN_INT_MASK) = 0xffffffff;

    /*
     * Decrease filter period time from 0x4000 to 0x3000, that
     * means decrease 1/4 ADC sampling time for each sensor.
     */
    temp = HWREG32(thermal->regs + REG_TSEN_TIME_CTRL);
    temp &= ~BITS_TIME_CTRL_MASK;
    temp |= VALUE_FILTER_PERIOD;
    temp |= BITS_RST_ADC_CNT;
    temp |= VALUE_WAIT_REF_CNT;
    HWREG32(thermal->regs + REG_TSEN_TIME_CTRL) = temp;

    /*
     * Enable all sensors' auto mode, enable dither control,
     * consecutive mode, and power up sensor.
     */
    temp = HWREG32(thermal->regs + REG_TSEN_PCTRL);
    temp |= BIT_TSEN_RAW_SEL | BIT_TEMP_MODE | BIT_EN_SENSOR;
    temp &= ~BITS_TSEN_SW_CTRL;
    temp &= ~BITS_CTUNE;
    HWREG32(thermal->regs + REG_TSEN_PCTRL) = temp;

    /* Select 24M clk for high speed mode */
    temp = HWREG32(thermal->regs + REG_TSEN_PCTRL2);
    temp &= ~BITS_SDM_CLK_SEL;
    temp |= BITS_SDM_CLK_SEL_24M;
    HWREG32(thermal->regs + REG_TSEN_PCTRL2) = temp;

    /* Enable the sensor interrupt */
    for (int i = thermal->sr[0]; i <= thermal->sr[1]; ++i)
    {
        temp = HWREG32(thermal->regs + desc->se.bjt_en);
        temp &= ~desc->se.bit_msk;
        temp |= (desc->se.en_val << desc->se.offset);
        HWREG32(thermal->regs + desc->se.bjt_en) = temp;
    }

    return 0;
}

static void enable_sensors(struct k1x_thermal *thermal)
{
    HWREG32(thermal->regs + REG_TSEN_INT_MASK) =
            HWREG32(thermal->regs + REG_TSEN_INT_MASK) | TSEN_INT_MASK;
    HWREG32(thermal->regs + REG_TSEN_PCTRL) =
            HWREG32(thermal->regs + REG_TSEN_PCTRL) | BIT_HW_AUTO_MODE;
}

static void enable_sensor_irq(struct k1x_thermal_sensor *sensor)
{
    rt_uint32_t temp;
    struct k1x_thermal_sensor_desc *desc = sensor->desc;

    /* Clear the interrupt */
    temp = HWREG32(sensor->regs + desc->int_clr);
    temp |= desc->bit_msk;
    HWREG32(sensor->regs + desc->int_clr) = temp;

    /* Enable the interrupt */
    temp = HWREG32(sensor->regs + desc->int_msk);
    temp &= ~desc->bit_msk;
    HWREG32(sensor->regs + desc->int_msk) = temp;
}

static void k1x_thermal_free(struct k1x_thermal *thermal)
{
    if (!thermal->regs)
    {
        rt_iounmap(thermal->regs);
    }

    if (!rt_is_err_or_null(thermal->clk))
    {
        rt_clk_disable_unprepare(thermal->clk);
        rt_clk_put(thermal->clk);
    }

    if (!rt_is_err_or_null(thermal->rstc))
    {
        rt_reset_control_assert(thermal->rstc);
        rt_reset_control_put(thermal->rstc);
    }

    if (thermal->sensors)
    {
        rt_free(thermal->sensors);
    }

    rt_free(thermal);
}

static rt_err_t k1x_thermal_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct k1x_thermal *thermal;
    struct k1x_thermal_sensor_desc *desc = (void *)pdev->id->data;

    if (!desc)
    {
        return -RT_EINVAL;
    }

    if (!(thermal = rt_calloc(1, sizeof(*thermal))))
    {
        return -RT_ENOMEM;
    }

    thermal->regs = rt_dm_dev_iomap(dev, 0);
    if (!thermal->regs)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    thermal->irq = rt_dm_dev_get_irq(dev, 0);
    if (thermal->irq < 0)
    {
        err = thermal->irq;
        goto _fail;
    }

    thermal->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(thermal->rstc))
    {
        err = rt_ptr_err(thermal->rstc);
        goto _fail;
    }

    rt_reset_control_deassert(thermal->rstc);

    thermal->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(thermal->clk))
    {
        err = rt_ptr_err(thermal->clk);
        goto _fail;
    }

    rt_clk_prepare_enable(thermal->clk);

    /* Initialize the sensors */
    if ((err = init_sensors(dev, thermal, desc)))
    {
        goto _fail;
    }

    thermal->sensors = rt_calloc(thermal->sr[1] - thermal->sr[0], sizeof(*thermal->sensors));
    if (!thermal->sensors)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    /* Then register the thermal zone */
    for (int i = thermal->sr[0]; i <= thermal->sr[1]; ++i)
    {
        struct k1x_thermal_sensor *sensor;
        struct rt_thermal_zone_device *tz;

        sensor = &thermal->sensors[i - thermal->sr[0]];
        sensor->regs = thermal->regs;
        sensor->desc = desc;

        tz = &sensor->parent;
        tz->ops = &k1x_thermal_ops;
        tz->parent.ofw_node = dev->ofw_node;

        rt_dm_dev_set_name(&tz->parent, "tk1x-tz-%d", i);
        rt_thermal_zone_device_register(tz);

        rt_hw_interrupt_install(thermal->irq, k1x_thermal_isr, sensor,
                rt_dm_dev_get_name(&tz->parent));

        /* Enable sensor low & higth threshold interrupt */
        enable_sensor_irq(sensor);
    }

    /* Enable the sensor interrupt & using auto mode */
    enable_sensors(thermal);

    rt_hw_interrupt_umask(thermal->irq);

    dev->user_data = thermal;

    return RT_EOK;

_fail:
    k1x_thermal_free(thermal);

    return err;
}

static rt_err_t k1x_thermal_remove(struct rt_platform_device *pdev)
{
    struct k1x_thermal *thermal = pdev->parent.user_data;

    rt_hw_interrupt_mask(thermal->irq);

    for (int i = thermal->sr[0]; i <= thermal->sr[1]; ++i)
    {
        struct k1x_thermal_sensor *sensor;

        sensor = &thermal->sensors[i - thermal->sr[0]];

        rt_pic_detach_irq(thermal->irq, sensor);
        rt_thermal_zone_device_unregister(&sensor->parent);
    }

    k1x_thermal_free(thermal);

    return RT_EOK;
}

static struct k1x_thermal_sensor_desc gsdesc[] =
{
    /* bjt0: local, sensor internal temperature */
    [0] =
    {
        .int_msk = 0x14, .int_clr = 0x10, .int_sta = 0x18, .offset = 0x0, .bit_msk = 0x6,
        .se = { .bjt_en = 0x8, .en_val = 0x1, .offset = 0x0, .bit_msk = 0x1, },
        .sd = { .data_reg = 0x20, .offset = 0x0, .bit_msk = 0xffff, },
        .sr = { .temp_thrsh = 0x40, .low_offset = 0x0, .high_offset = 16, },
    },

    /* bjt1: top */
    [1] =
    {
        .int_msk = 0x14, .int_clr = 0x10, .int_sta = 0x18, .offset = 0x3, .bit_msk = 0x18,
        .se = { .bjt_en = 0x8, .en_val = 0x1, .offset = 0x1, .bit_msk = 0x2, },
        .sd = { .data_reg = 0x20, .offset = 16, .bit_msk = 0xffff0000, },
        .sr = { .temp_thrsh = 0x44, .low_offset = 0x0, .high_offset = 16, },
    },

    /* bjt2: gpu */
    [2] =
    {
        .int_msk = 0x14, .int_clr = 0x10, .int_sta = 0x18, .offset = 0x5, .bit_msk = 0x60,
        .se = { .bjt_en = 0x8, .en_val = 0x1, .offset = 0x2, .bit_msk = 0x4, },
        .sd = { .data_reg = 0x24, .offset = 0, .bit_msk = 0xffff, },
        .sr = { .temp_thrsh = 0x48, .low_offset = 0x0, .high_offset = 16, },
    },

    /* bjt3: cluster0 */
    [3] =
    {
        .int_msk = 0x14, .int_clr = 0x10, .int_sta = 0x18, .offset = 0x7, .bit_msk = 0x180,
        .se = { .bjt_en = 0x8, .en_val = 0x1, .offset = 0x3, .bit_msk = 0x8, },
        .sd = { .data_reg = 0x24, .offset = 16, .bit_msk = 0xffff0000, },
        .sr = { .temp_thrsh = 0x4c, .low_offset = 0x0, .high_offset = 16, },
    },

    /* bjt4: cluster1 */
    [4] =
    {
        .int_msk = 0x14, .int_clr = 0x10, .int_sta = 0x18, .offset = 0x9, .bit_msk = 0x600,
        .se = { .bjt_en = 0x8, .en_val = 0x1, .offset = 0x4, .bit_msk = 0x10, },
        .sd = { .data_reg = 0x28, .offset = 0, .bit_msk = 0xffff, },
        .sr = { .temp_thrsh = 0x50, .low_offset = 0x0, .high_offset = 16, },
    },
};

static const struct rt_ofw_node_id k1x_thermal_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-tsensor", .data = gsdesc, },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_thermal_driver =
{
    .name = "k1x-thermal",
    .ids = k1x_thermal_ofw_ids,

    .probe = k1x_thermal_probe,
    .remove = k1x_thermal_remove,
};
RT_PLATFORM_DRIVER_EXPORT(k1x_thermal_driver);
