/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define RP1_ADC_CS                  0x00
#define RP1_ADC_RESULT              0x04
#define RP1_ADC_FCS                 0x08
#define RP1_ADC_FIFO                0x0c
#define RP1_ADC_DIV                 0x10

#define RP1_ADC_INTR                0x14
#define RP1_ADC_INTE                0x18
#define RP1_ADC_INTF                0x1c
#define RP1_ADC_INTS                0x20

#define RP1_ADC_RWTYPE_SET          0x2000
#define RP1_ADC_RWTYPE_CLR          0x3000

#define RP1_ADC_CS_RROBIN_MASK      0x1f
#define RP1_ADC_CS_RROBIN_SHIFT     16
#define RP1_ADC_CS_AINSEL_MASK      0x7
#define RP1_ADC_CS_AINSEL_SHIFT     12
#define RP1_ADC_CS_ERR_STICKY       0x400
#define RP1_ADC_CS_ERR              0x200
#define RP1_ADC_CS_READY            0x100
#define RP1_ADC_CS_START_MANY       0x8
#define RP1_ADC_CS_START_ONCE       0x4
#define RP1_ADC_CS_TS_EN            0x2
#define RP1_ADC_CS_EN               0x1

#define RP1_ADC_FCS_THRESH_MASK     0xf
#define RP1_ADC_FCS_THRESH_SHIFT    24
#define RP1_ADC_FCS_LEVEL_MASK      0xf
#define RP1_ADC_FCS_LEVEL_SHIFT     16
#define RP1_ADC_FCS_OVER            0x800
#define RP1_ADC_FCS_UNDER           0x400
#define RP1_ADC_FCS_FULL            0x200
#define RP1_ADC_FCS_EMPTY           0x100
#define RP1_ADC_FCS_DREQ_EN         0x8
#define RP1_ADC_FCS_ERR             0x4
#define RP1_ADC_FCS_SHIFR           0x2
#define RP1_ADC_FCS_EN              0x1

#define RP1_ADC_FIFO_ERR            0x8000
#define RP1_ADC_FIFO_VAL_MASK       0xfff

#define RP1_ADC_DIV_INT_MASK        0xffff
#define RP1_ADC_DIV_INT_SHIFT       8
#define RP1_ADC_DIV_FRAC_MASK       0xff
#define RP1_ADC_DIV_FRAC_SHIFT      0

enum
{
    RP1_ADC_IN,
    RP1_ADC_RAW,
    RP1_ADC_TEMP,
};

struct rp1_adc_channel
{
    rt_uint32_t type;

    const char *name;
};

struct rp1_adc
{
    struct rt_adc_device parent;

    void *regs;
    int vref_mv;

    struct rt_clk *clk;
    struct rt_regulator *vref;

    rt_size_t channel_nr;
    struct rp1_adc_channel *channel;

    struct rt_spinlock lock;
};

#define raw_to_rp1_adc(raw) rt_container_of(raw, struct rp1_adc, parent)

static rt_err_t rp1_adc_ready_wait(struct rp1_adc *radc)
{
    int retries = 10;

    while (retries && !(HWREG32(radc->regs + RP1_ADC_CS) & RP1_ADC_CS_READY))
    {
        --retries;
    }

    return retries ? 0 : -RT_EIO;
}

static rt_err_t rp1_adc_read(struct rp1_adc *radc, int channel, rt_uint32_t *val)
{
    rt_err_t err;

    rt_hw_spin_lock(&radc->lock.lock);

    HWREG32(radc->regs + RP1_ADC_RWTYPE_CLR + RP1_ADC_CS) =
            RP1_ADC_CS_AINSEL_MASK << RP1_ADC_CS_AINSEL_SHIFT;
    HWREG32(radc->regs + RP1_ADC_RWTYPE_SET + RP1_ADC_CS) =
            channel << RP1_ADC_CS_AINSEL_SHIFT;
    HWREG32(radc->regs + RP1_ADC_RWTYPE_SET + RP1_ADC_CS) =
            RP1_ADC_CS_START_ONCE;

    if ((err = rp1_adc_ready_wait(radc)))
    {
        goto _out_lock;
    }

    /* Asserted if the completed conversion had a convergence error */
    if (HWREG32(radc->regs + RP1_ADC_CS) & RP1_ADC_CS_ERR)
    {
        err = -RT_EIO;
        goto _out_lock;
    }

    *val = HWREG32(radc->regs + RP1_ADC_RESULT);

_out_lock:
    rt_hw_spin_unlock(&radc->lock.lock);

    return err;
}

static int rp1_adc_to_mv(struct rp1_adc *radc, rt_uint32_t val)
{
    return ((rt_uint64_t)radc->vref_mv * val) / 0xfff;
}

static struct rp1_adc_channel adc_channel[] =
{
    { .type = RP1_ADC_IN,   .name = "in1-input" },
    { .type = RP1_ADC_IN,   .name = "in2-input" },
    { .type = RP1_ADC_IN,   .name = "in3-input" },
    { .type = RP1_ADC_IN,   .name = "in4-input" },
    { .type = RP1_ADC_TEMP, .name = "temp1-input" },
    { .type = RP1_ADC_RAW,  .name = "in1-raw" },
    { .type = RP1_ADC_RAW,  .name = "in2-raw" },
    { .type = RP1_ADC_RAW,  .name = "in3-raw" },
    { .type = RP1_ADC_RAW,  .name = "in4-raw" },
    { .type = RP1_ADC_RAW,  .name = "temp1-raw" },
};

static rt_err_t rp1_adc_enabled(struct rt_adc_device *adc, rt_int8_t channel, rt_bool_t enabled)
{
    return RT_EOK;
}

static rt_err_t rp1_adc_convert(struct rt_adc_device *adc, rt_int8_t channel, rt_uint32_t *value)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rp1_adc_channel *chan;
    struct rp1_adc *radc = raw_to_rp1_adc(adc);

    if (channel >= radc->channel_nr)
    {
        return -RT_EINVAL;
    }

    chan = &radc->channel[channel];

    if (chan->type == RP1_ADC_TEMP)
    {
        int mv;

        HWREG32(radc->regs + RP1_ADC_RWTYPE_SET + RP1_ADC_CS) = RP1_ADC_CS_TS_EN;

        if ((err = rp1_adc_read(radc, channel, &val)))
        {
            return err;
        }

        mv = rp1_adc_to_mv(radc, val);

        /* T = 27 - (ADC_voltage - 0.706)/0.001721 */

        *value = 27000 - RT_DIV_ROUND_CLOSEST((mv - 706) * (rt_int64_t)1000000, 1721);
    }
    else if (chan->type == RP1_ADC_IN || chan->type == RP1_ADC_RAW)
    {
        if ((err = rp1_adc_read(radc, channel, &val)))
        {
            return err;
        }

        *value = val;
    }

    return RT_EOK;
}

static const struct rt_adc_ops rp1_adc_ops =
{
    .enabled = rp1_adc_enabled,
    .convert = rp1_adc_convert,
};

static void rp1_adc_free(struct rp1_adc *radc)
{
    if (radc->regs)
    {
        rt_iounmap(radc->regs);
    }

    if (!rt_is_err_or_null(radc->clk))
    {
        rt_clk_disable_unprepare(radc->clk);
        rt_clk_put(radc->clk);
    }

    rt_free(radc);
}

static rt_err_t rp1_adc_probe(struct rt_platform_device *pdev)
{
    int vref_uv;
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct rp1_adc *radc = rt_calloc(1, sizeof(*radc));

    if (!radc)
    {
        return -RT_ENOMEM;
    }

    radc->regs = rt_dm_dev_iomap(dev, 0);

    if (!radc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    radc->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(radc->clk))
    {
        err = rt_ptr_err(radc->clk);
        goto _fail;
    }

    rt_clk_set_rate(radc->clk, 50000000);
    rt_clk_prepare_enable(radc->clk);

    radc->vref = rt_regulator_get(dev, "vref");

    if (rt_is_err(radc->vref))
    {
        err = rt_ptr_err(radc->vref);
        goto _fail;
    }

    vref_uv = rt_regulator_get_voltage(radc->vref);
    radc->vref_mv = RT_DIV_ROUND_CLOSEST(vref_uv, 1000);

    radc->channel_nr = RT_ARRAY_SIZE(adc_channel);
    radc->channel = adc_channel;

    rt_spin_lock_init(&radc->lock);

    dev->user_data = radc;

    rt_dm_dev_set_name_auto(&radc->parent.parent, "adc");
    dev_name = rt_dm_dev_get_name(&radc->parent.parent);

    rt_hw_adc_register(&radc->parent, dev_name, &rp1_adc_ops, radc);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, radc);

    /* Disable interrupts */
    HWREG32(radc->regs + RP1_ADC_INTE) = 0;

    /* Enable the block, clearing any sticky error */
    HWREG32(radc->regs + RP1_ADC_CS) = RP1_ADC_CS_EN | RP1_ADC_CS_ERR_STICKY;

    return RT_EOK;

_fail:
    rp1_adc_free(radc);

    return err;
}

static rt_err_t rp1_adc_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rp1_adc *radc = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_device_unregister(&radc->parent.parent);

    rp1_adc_free(radc);

    return RT_EOK;
}

static const struct rt_ofw_node_id rp1_adc_ofw_ids[] =
{
    { .compatible = "raspberrypi,rp1-adc" },
    { /* sentinel */ }
};

static struct rt_platform_driver rp1_adc_driver =
{
    .name = "rp1-adc",
    .ids = rp1_adc_ofw_ids,

    .probe = rp1_adc_probe,
    .remove = rp1_adc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rp1_adc_driver);
