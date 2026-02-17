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

#define SARADC_DATA             0x00

#define SARADC_STAS             0x04
#define SARADC_STAS_BUSY        RT_BIT(0)

#define SARADC_CTRL             0x08
#define SARADC_CTRL_IRQ_STATUS  RT_BIT(6)
#define SARADC_CTRL_IRQ_ENABLE  RT_BIT(5)
#define SARADC_CTRL_POWER_CTRL  RT_BIT(3)
#define SARADC_CTRL_CHN_MASK    0x7

#define SARADC_DLY_PU_SOC       0x0c
#define SARADC_DLY_PU_SOC_MASK  0x3f

#define SARADC_TIMEOUT          rt_tick_from_millisecond(100)
#define SARADC_MAX_CHANNELS     8

/* v2 registers */
#define SARADC2_CONV_CON        0x000
#define SARADC_T_PD_SOC         0x004
#define SARADC_T_DAS_SOC        0x00c
#define SARADC2_END_INT_EN      0x104
#define SARADC2_ST_CON          0x108
#define SARADC2_STATUS          0x10c
#define SARADC2_END_INT_ST      0x110
#define SARADC2_DATA_BASE       0x120

#define SARADC2_EN_END_INT      RT_BIT(0)
#define SARADC2_START           RT_BIT(4)
#define SARADC2_SINGLE_MODE     RT_BIT(5)

#define SARADC2_CONV_CHANNELS   RT_GENMASK(15, 0)

struct saradc_channel
{
    int channel;
    int scan_index;

    struct
    {
        char sign;
        rt_uint8_t realbits;
        rt_uint8_t storagebits;
        rt_uint8_t repeat;
    } scan_type;

    rt_base_t info_mask_separate;
    rt_base_t info_mask_shared_by_type;

    const char *datasheet_name;
};

struct rockchip_saradc;

struct rockchip_saradc_soc_data
{
    const struct saradc_channel *channels;
    int num_channels;

    rt_ubase_t clk_rate;
    void (*start)(struct rockchip_saradc *rk_saradc, int chn);
    int (*read)(struct rockchip_saradc *rk_saradc);
    void (*power_down)(struct rockchip_saradc *rk_saradc);
};

struct rockchip_saradc
{
    struct rt_adc_device parent;

    int irq;
    void *regs;
    struct rt_clk *clk;
    struct rt_clk *pclk;
    struct rt_regulator *vref;
    struct rt_reset_control *rstc;

    const struct rockchip_saradc_soc_data *soc_data;

    rt_uint16_t last_val;
    struct saradc_channel *last_chan;

    struct rt_mutex lock;
    struct rt_completion completion;
};

#define raw_to_rockchip_saradc(raw) rt_container_of(raw, struct rockchip_saradc, parent)

#define SARADC_CHANNEL(INDEX, ID, RES)      \
{                                           \
    .channel = INDEX,                       \
    .info_mask_separate = RT_BIT(0),        \
    .info_mask_shared_by_type = RT_BIT(2),  \
    .datasheet_name = ID,                   \
    .scan_index = INDEX,                    \
    .scan_type =                            \
    {                                       \
        .sign = 'u',                        \
        .realbits = RES,                    \
        .storagebits = 16,                  \
    },                                      \
}

static void rockchip_saradc_start_v1(struct rockchip_saradc *rk_saradc, int chn)
{
    /* 8 clock periods as delay between power up and start cmd */
    HWREG32(rk_saradc->regs + SARADC_DLY_PU_SOC) = 8;
    /* Select the channel to be used and trigger conversion */
    HWREG32(rk_saradc->regs + SARADC_CTRL) = SARADC_CTRL_POWER_CTRL |
            (chn & SARADC_CTRL_CHN_MASK) | SARADC_CTRL_IRQ_ENABLE;
}

static void rockchip_saradc_reset_controller(struct rockchip_saradc *rk_saradc);

static void rockchip_saradc_start_v2(struct rockchip_saradc *rk_saradc, int chn)
{
    int val;

    if (rk_saradc->rstc)
    {
        rockchip_saradc_reset_controller(rk_saradc);
    }

    HWREG32(rk_saradc->regs + SARADC_T_DAS_SOC) = 0xc;
    HWREG32(rk_saradc->regs + SARADC_T_PD_SOC) = 0x20;

    val = RT_FIELD_PREP(SARADC2_EN_END_INT, 1);
    val |= val << 16;
    HWREG32(rk_saradc->regs + SARADC2_END_INT_EN) = val;

    val = RT_FIELD_PREP(SARADC2_START, 1) |
          RT_FIELD_PREP(SARADC2_SINGLE_MODE, 1) |
          RT_FIELD_PREP(SARADC2_CONV_CHANNELS, chn);
    val |= val << 16;
    HWREG32(rk_saradc->regs + SARADC2_CONV_CON) = val;
}

static int rockchip_saradc_read_v1(struct rockchip_saradc *rk_saradc)
{
    return HWREG32(rk_saradc->regs + SARADC_DATA);
}

static int rockchip_saradc_read_v2(struct rockchip_saradc *rk_saradc)
{
    int offset;

    /* Clear irq */
    HWREG32(rk_saradc->regs + SARADC2_END_INT_ST) = 0x1;

    offset = SARADC2_DATA_BASE + rk_saradc->last_chan->channel * 0x4;

    return HWREG32(rk_saradc->regs + offset);
}

static void rockchip_saradc_power_down_v1(struct rockchip_saradc *rk_saradc)
{
    HWREG32(rk_saradc->regs + SARADC_CTRL) = 0;
}

static const struct saradc_channel rockchip_saradc_channels[] =
{
    SARADC_CHANNEL(0, "adc0", 10),
    SARADC_CHANNEL(1, "adc1", 10),
    SARADC_CHANNEL(2, "adc2", 10),
};

static const struct rockchip_saradc_soc_data saradc_data =
{
    .channels = rockchip_saradc_channels,
    .num_channels = RT_ARRAY_SIZE(rockchip_saradc_channels),
    .clk_rate = 1000000,
    .start = rockchip_saradc_start_v1,
    .read = rockchip_saradc_read_v1,
    .power_down = rockchip_saradc_power_down_v1,
};

static const struct saradc_channel rk3066_tsadc_channels[] =
{
    SARADC_CHANNEL(0, "adc0", 12),
    SARADC_CHANNEL(1, "adc1", 12),
};

static const struct rockchip_saradc_soc_data rk3066_tsadc_data =
{
    .channels = rk3066_tsadc_channels,
    .num_channels = RT_ARRAY_SIZE(rk3066_tsadc_channels),
    .clk_rate = 50000,
    .start = rockchip_saradc_start_v1,
    .read = rockchip_saradc_read_v1,
    .power_down = rockchip_saradc_power_down_v1,
};

static const struct saradc_channel rk3399_saradc_channels[] =
{
    SARADC_CHANNEL(0, "adc0", 10),
    SARADC_CHANNEL(1, "adc1", 10),
    SARADC_CHANNEL(2, "adc2", 10),
    SARADC_CHANNEL(3, "adc3", 10),
    SARADC_CHANNEL(4, "adc4", 10),
    SARADC_CHANNEL(5, "adc5", 10),
};

static const struct rockchip_saradc_soc_data rk3399_saradc_data =
{
    .channels = rk3399_saradc_channels,
    .num_channels = RT_ARRAY_SIZE(rk3399_saradc_channels),
    .clk_rate = 1000000,
    .start = rockchip_saradc_start_v1,
    .read = rockchip_saradc_read_v1,
    .power_down = rockchip_saradc_power_down_v1,
};

static const struct saradc_channel rk3568_saradc_channels[] =
{
    SARADC_CHANNEL(0, "adc0", 10),
    SARADC_CHANNEL(1, "adc1", 10),
    SARADC_CHANNEL(2, "adc2", 10),
    SARADC_CHANNEL(3, "adc3", 10),
    SARADC_CHANNEL(4, "adc4", 10),
    SARADC_CHANNEL(5, "adc5", 10),
    SARADC_CHANNEL(6, "adc6", 10),
    SARADC_CHANNEL(7, "adc7", 10),
};

static const struct rockchip_saradc_soc_data rk3568_saradc_data =
{
    .channels = rk3568_saradc_channels,
    .num_channels = RT_ARRAY_SIZE(rk3568_saradc_channels),
    .clk_rate = 1000000,
    .start = rockchip_saradc_start_v1,
    .read = rockchip_saradc_read_v1,
    .power_down = rockchip_saradc_power_down_v1,
};

static const struct saradc_channel rk3588_saradc_channels[] =
{
    SARADC_CHANNEL(0, "adc0", 12),
    SARADC_CHANNEL(1, "adc1", 12),
    SARADC_CHANNEL(2, "adc2", 12),
    SARADC_CHANNEL(3, "adc3", 12),
    SARADC_CHANNEL(4, "adc4", 12),
    SARADC_CHANNEL(5, "adc5", 12),
    SARADC_CHANNEL(6, "adc6", 12),
    SARADC_CHANNEL(7, "adc7", 12),
};

static const struct rockchip_saradc_soc_data rk3588_saradc_data =
{
    .channels = rk3588_saradc_channels,
    .num_channels = RT_ARRAY_SIZE(rk3588_saradc_channels),
    .clk_rate = 1000000,
    .start = rockchip_saradc_start_v2,
    .read = rockchip_saradc_read_v2,
};

static void rockchip_saradc_start(struct rockchip_saradc *rk_saradc, int chn)
{
    rk_saradc->soc_data->start(rk_saradc, chn);
}

static int rockchip_saradc_read(struct rockchip_saradc *rk_saradc)
{
    return rk_saradc->soc_data->read(rk_saradc);
}

static void rockchip_saradc_power_down(struct rockchip_saradc *rk_saradc)
{
    if (rk_saradc->soc_data->power_down)
    {
        rk_saradc->soc_data->power_down(rk_saradc);
    }
}

static rt_err_t rockchip_saradc_enabled(struct rt_adc_device *adc, rt_int8_t channel, rt_bool_t enabled)
{
    return RT_EOK;
}

static rt_err_t rockchip_saradc_convert(struct rt_adc_device *adc, rt_int8_t channel, rt_uint32_t *value)
{
    rt_err_t err = RT_EOK;
    struct rockchip_saradc *rk_saradc = raw_to_rockchip_saradc(adc);

    rt_mutex_take(&rk_saradc->lock, RT_WAITING_FOREVER);

    rk_saradc->last_chan = (struct saradc_channel *)&rk_saradc->soc_data->channels[channel];
    rockchip_saradc_start(rk_saradc, channel);

    /* Select the channel to be used and trigger conversion */
    HWREG32(rk_saradc->regs + SARADC_CTRL) =SARADC_CTRL_POWER_CTRL |
            (channel & SARADC_CTRL_CHN_MASK) | SARADC_CTRL_IRQ_ENABLE;

    /* Delay 100ms */
    if (!(err = rt_completion_wait(&rk_saradc->completion, SARADC_TIMEOUT)))
    {
        *value = rk_saradc->last_val;
    }

    rt_mutex_release(&rk_saradc->lock);

    return err;
}

static const struct rt_adc_ops rockchip_saradc_ops =
{
    .enabled = rockchip_saradc_enabled,
    .convert = rockchip_saradc_convert,
};

static void rockchip_saradc_isr(int irqno, void *param)
{
    struct rockchip_saradc *rk_saradc = (struct rockchip_saradc *)param;

    /* Read value */
    rk_saradc->last_val = rockchip_saradc_read(rk_saradc);
    rk_saradc->last_val &= RT_GENMASK(rk_saradc->last_chan->scan_type.realbits - 1, 0);

    rockchip_saradc_power_down(rk_saradc);

    rt_completion_done(&rk_saradc->completion);
}

static void rockchip_saradc_reset_controller(struct rockchip_saradc *rk_saradc)
{
    rt_reset_control_assert(rk_saradc->rstc);
    rt_hw_us_delay(15);
    rt_reset_control_deassert(rk_saradc->rstc);
}

static void rockchip_saradc_free(struct rockchip_saradc *rk_saradc)
{
    if (rk_saradc->regs)
    {
        rt_iounmap(rk_saradc->regs);
    }

    if (!rt_is_err_or_null(rk_saradc->rstc))
    {
        rt_reset_control_put(rk_saradc->rstc);
    }

    if (!rt_is_err_or_null(rk_saradc->vref))
    {
        rt_regulator_disable(rk_saradc->vref);
    }

    if (!rt_is_err_or_null(rk_saradc->clk))
    {
        rt_clk_disable(rk_saradc->clk);
        rt_clk_put(rk_saradc->clk);
    }

    if (!rt_is_err_or_null(rk_saradc->pclk))
    {
        rt_clk_disable(rk_saradc->pclk);
        rt_clk_put(rk_saradc->pclk);
    }

    rt_free(rk_saradc);
}

static rt_err_t rockchip_saradc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    const struct rockchip_saradc_soc_data *soc_data = pdev->id->data;
    struct rockchip_saradc *rk_saradc = rt_calloc(1, sizeof(*rk_saradc));

    if (!rk_saradc)
    {
        return -RT_ENOMEM;
    }

    rk_saradc->soc_data = soc_data;
    rk_saradc->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_saradc->regs)
    {
        err = -RT_EIO;
        goto _free_res;
    }

    rk_saradc->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk_saradc->irq < 0)
    {
        err = rk_saradc->irq;
        goto _free_res;
    }

    rk_saradc->vref = rt_regulator_get(dev, "vref");

    if (rt_is_err(rk_saradc->vref))
    {
        err = rt_ptr_err(rk_saradc->vref);
        goto _free_res;
    }

    rk_saradc->rstc = rt_reset_control_get_by_name(dev, "saradc-apb");

    if (rt_is_err(rk_saradc->rstc))
    {
        err = rt_ptr_err(rk_saradc->rstc);
        goto _free_res;
    }

    if (rk_saradc->rstc)
    {
        rockchip_saradc_reset_controller(rk_saradc);
    }

    rk_saradc->pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(rk_saradc->pclk))
    {
        err = rt_ptr_err(rk_saradc->pclk);
        goto _free_res;
    }

    if ((err = rt_clk_enable(rk_saradc->pclk)))
    {
        goto _free_res;
    }

    rk_saradc->clk = rt_clk_get_by_name(dev, "saradc");

    if (rt_is_err(rk_saradc->clk))
    {
        err = rt_ptr_err(rk_saradc->clk);
        goto _free_res;
    }

    if ((err = rt_clk_enable(rk_saradc->clk)))
    {
        goto _free_res;
    }

    if ((err = rt_clk_set_rate(rk_saradc->clk, soc_data->clk_rate)))
    {
        goto _free_res;
    }

    if ((err = rt_regulator_enable(rk_saradc->vref)))
    {
        goto _free_res;
    }

    dev->user_data = rk_saradc;

    rt_dm_dev_set_name_auto(&rk_saradc->parent.parent, "saradc");
    dev_name = rt_dm_dev_get_name(&rk_saradc->parent.parent);

    rt_mutex_init(&rk_saradc->lock, dev_name, RT_IPC_FLAG_PRIO);
    rt_completion_init(&rk_saradc->completion);

    rt_hw_adc_register(&rk_saradc->parent, dev_name, &rockchip_saradc_ops, rk_saradc);
    rt_hw_interrupt_install(rk_saradc->irq, rockchip_saradc_isr, rk_saradc, dev_name);
    rt_hw_interrupt_umask(rk_saradc->irq);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, rk_saradc);

    return RT_EOK;

_free_res:
    rockchip_saradc_free(rk_saradc);

    return err;
}

static rt_err_t rockchip_saradc_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rockchip_saradc *rk_saradc = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_hw_interrupt_mask(rk_saradc->irq);
    rt_pic_detach_irq(rk_saradc->irq, rk_saradc);

    rt_device_unregister(&rk_saradc->parent.parent);

    rockchip_saradc_free(rk_saradc);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_saradc_ofw_ids[] =
{
    { .compatible = "rockchip,saradc", .data = &saradc_data },
    { .compatible = "rockchip,rk3066-tsadc", .data = &rk3066_tsadc_data },
    { .compatible = "rockchip,rk3399-saradc", .data = &rk3399_saradc_data },
    { .compatible = "rockchip,rk3568-saradc", .data = &rk3568_saradc_data },
    { .compatible = "rockchip,rk3588-saradc", .data = &rk3588_saradc_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_saradc_driver =
{
    .name = "rockchip-saradc",
    .ids = rockchip_saradc_ofw_ids,

    .probe = rockchip_saradc_probe,
    .remove = rockchip_saradc_remove,
};

static int rockchip_saradc_register(void)
{
    /* If the regulator is a i2c device, saradc should init later */
    rt_platform_driver_register(&rockchip_saradc_driver);

    return 0;
}
INIT_COMPONENT_EXPORT(rockchip_saradc_register);
