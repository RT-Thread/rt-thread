/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "i2s.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "spacemit-audio.h"
#include "spacemit-snd-i2s.h"

#define K1_APBC_BASE                    0xd4015000UL
#define K1_APBC_SIZE                    0x100
#define K1_APBC_SSPA0                   0x80
#define K1_APBC_SSPA1                   0x84
#define K1_APBC_SSPA_AUDIO_MODE         RT_BIT(3)

#define K1_MPMU_BASE                    0xd4050000UL
#define K1_MPMU_SIZE                    0x100
#define K1_MPMU_SYSCLK_PRE_CTRL         0x08
#define K1_MPMU_ISCCR1                  0x44
#define K1_MPMU_SYSCLK_BASE_156M        RT_BIT(30)
#define K1_MPMU_I2S_BCLK_ENABLE         RT_BIT(29)

struct spacemit_i2s
{
    struct rt_device *dev;
    struct rt_ofw_node *np;

    void *regs;
    void *apbc;
    void *mpmu;
    rt_ubase_t phys;

    struct rt_clk *clk;
    struct rt_reset_control *reset;
    struct spacemit_audio_config config;

    int port;
    int users;
    rt_list_t list;
};

static rt_list_t i2s_nodes = RT_LIST_OBJECT_INIT(i2s_nodes);
static RT_DEFINE_SPINLOCK(i2s_nodes_lock);

static rt_uint32_t i2s_read(struct spacemit_i2s *i2s, rt_ubase_t reg)
{
    return HWREG32((char *)i2s->regs + reg);
}

static void i2s_write(struct spacemit_i2s *i2s, rt_ubase_t reg, rt_uint32_t value)
{
    HWREG32((char *)i2s->regs + reg) = value;
}

struct spacemit_i2s *spacemit_i2s_find(struct rt_ofw_node *np)
{
    struct spacemit_i2s *i2s;

    rt_spin_lock(&i2s_nodes_lock);
    rt_list_for_each_entry(i2s, &i2s_nodes, list)
    {
        if (i2s->np == np)
        {
            rt_spin_unlock(&i2s_nodes_lock);
            return i2s;
        }
    }
    rt_spin_unlock(&i2s_nodes_lock);

    return RT_NULL;
}

static rt_err_t spacemit_i2s_set_clock(struct spacemit_i2s *i2s,
        const struct spacemit_audio_config *config)
{
    rt_uint32_t divider, mclk_fs, ratio, target, value;
    rt_uint64_t bclk, mclk;

    bclk = (rt_uint64_t)config->samplerate * config->channels * config->samplebits;
    mclk_fs = config->mclk_fs ? config->mclk_fs : 64;
    mclk = (rt_uint64_t)config->samplerate * mclk_fs;

    if (!bclk || mclk > 0xffffffffU || mclk % bclk)
    {
        return -RT_EINVAL;
    }

    switch (mclk_fs)
    {
    case 64:
        divider = 326;
        break;
    case 128:
        divider = 652;
        break;
    case 256:
        divider = 1304;
        break;
    default:
        return -RT_EINVAL;
    }

    ratio = (rt_uint32_t)(mclk / bclk);
    switch (ratio)
    {
    case 2:
        ratio = 0;
        break;
    case 4:
        ratio = 1;
        break;
    case 6:
        ratio = 2;
        break;
    case 8:
        ratio = 3;
        break;
    default:
        return -RT_EINVAL;
    }

    target = K1_MPMU_SYSCLK_BASE_156M | (ratio << 27) |
            (divider << 15) | 32600;
    value = HWREG32((char *)i2s->mpmu + K1_MPMU_ISCCR1);
    value &= ~0x5fffffffU;
    HWREG32((char *)i2s->mpmu + K1_MPMU_ISCCR1) = value | target;

    value = HWREG32((char *)i2s->mpmu + K1_MPMU_SYSCLK_PRE_CTRL);
    HWREG32((char *)i2s->mpmu + K1_MPMU_SYSCLK_PRE_CTRL) =
            value | K1_MPMU_I2S_BCLK_ENABLE;

    if (!rt_is_err_or_null(i2s->clk))
    {
        rt_clk_set_rate(i2s->clk, (rt_uint32_t)bclk);
    }

    return RT_EOK;
}

rt_err_t spacemit_i2s_configure(struct spacemit_i2s *i2s,
        const struct spacemit_audio_config *config)
{
    rt_uint32_t fifo, psp, top;
    rt_err_t err;

    if (!i2s || !config || config->samplerate != 48000 ||
        config->channels != 2 || config->samplebits != 16)
    {
        return -RT_EINVAL;
    }

    if (i2s->users)
    {
        return rt_memcmp(&i2s->config, config, sizeof(*config)) ?
                -RT_EBUSY : RT_EOK;
    }

    if ((err = spacemit_i2s_set_clock(i2s, config)))
    {
        return err;
    }

    top = SSPA_TOP_TRAIL_DMA | SSPA_TOP_DATA_WIDTH_32 | SSPA_TOP_FRAME_PSP;
    fifo = SSPA_FIFO_RX_DMA_REQ | SSPA_FIFO_TX_DMA_REQ |
            SSPA_FIFO_RX_THRESHOLD(15) | SSPA_FIFO_TX_THRESHOLD(15);
    psp = SSPA_PSP_FRAME_WIDTH(16) | SSPA_PSP_FRAME_SYNC_RELATIVE |
            SSPA_PSP_FRAME_POLARITY;

    i2s_write(i2s, SSPA_TOP_CTRL, top);
    i2s_write(i2s, SSPA_FIFO_CTRL, fifo);
    i2s_write(i2s, SSPA_INT_EN, 0);
    i2s_write(i2s, SSPA_TIMEOUT, 0);
    i2s_write(i2s, SSPA_PSP_CTRL, psp);
    i2s_write(i2s, SSPA_NETWORK_CTRL, 0);

    i2s->config = *config;

    return RT_EOK;
}

rt_err_t spacemit_i2s_start(struct spacemit_i2s *i2s)
{
    rt_uint32_t value;

    if (!i2s)
    {
        return -RT_EINVAL;
    }

    if (!i2s->users++)
    {
        value = i2s_read(i2s, SSPA_TOP_CTRL);
        i2s_write(i2s, SSPA_TOP_CTRL, value | SSPA_TOP_ENABLE);
    }

    return RT_EOK;
}

rt_err_t spacemit_i2s_stop(struct spacemit_i2s *i2s)
{
    rt_uint32_t value;

    if (!i2s)
    {
        return -RT_EINVAL;
    }

    if (i2s->users > 0 && !--i2s->users)
    {
        value = i2s_read(i2s, SSPA_TOP_CTRL);
        i2s_write(i2s, SSPA_TOP_CTRL, value & ~SSPA_TOP_ENABLE);
    }

    return RT_EOK;
}

rt_ubase_t spacemit_i2s_fifo_phys(struct spacemit_i2s *i2s)
{
    return i2s ? i2s->phys + SSPA_DATA : 0;
}

static void spacemit_i2s_free(struct spacemit_i2s *i2s)
{
    if (!i2s)
    {
        return;
    }

    if (!rt_is_err_or_null(i2s->reset))
    {
        rt_reset_control_assert(i2s->reset);
        rt_reset_control_put(i2s->reset);
    }
    if (!rt_is_err_or_null(i2s->clk))
    {
        rt_clk_disable_unprepare(i2s->clk);
        rt_clk_put(i2s->clk);
    }
    if (i2s->regs)
    {
        rt_iounmap(i2s->regs);
    }
    if (i2s->apbc)
    {
        rt_iounmap(i2s->apbc);
    }
    if (i2s->mpmu)
    {
        rt_iounmap(i2s->mpmu);
    }

    rt_free(i2s);
}

static rt_err_t spacemit_i2s_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t phys;
    rt_uint32_t apbc_offset, value;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_i2s *i2s = rt_calloc(1, sizeof(*i2s));

    if (!i2s)
    {
        return -RT_ENOMEM;
    }

    i2s->dev = dev;
    i2s->np = dev->ofw_node;
    i2s->regs = rt_dm_dev_iomap(dev, 0);
    if (!i2s->regs || rt_dm_dev_get_address(dev, 0, &phys, RT_NULL))
    {
        err = -RT_EIO;
        goto _fail;
    }
    i2s->phys = (rt_ubase_t)phys;
    i2s->port = phys == 0xd4026000UL ? 0 : 1;

    i2s->apbc = rt_ioremap((void *)K1_APBC_BASE, K1_APBC_SIZE);
    i2s->mpmu = rt_ioremap((void *)K1_MPMU_BASE, K1_MPMU_SIZE);
    if (!i2s->apbc || !i2s->mpmu)
    {
        err = -RT_EIO;
        goto _fail;
    }

    i2s->clk = rt_clk_get_by_name(dev, "sspa-clk");
    if (rt_is_err(i2s->clk))
    {
        err = rt_ptr_err(i2s->clk);
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(i2s->clk)))
    {
        goto _fail;
    }

    i2s->reset = rt_reset_control_get_by_name(dev, "sspa-rst");
    if (rt_is_err(i2s->reset))
    {
        err = rt_ptr_err(i2s->reset);
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(i2s->reset)))
    {
        goto _fail;
    }

    apbc_offset = i2s->port ? K1_APBC_SSPA1 : K1_APBC_SSPA0;
    value = HWREG32((char *)i2s->apbc + apbc_offset);
    HWREG32((char *)i2s->apbc + apbc_offset) = value | K1_APBC_SSPA_AUDIO_MODE;

    rt_spin_lock(&i2s_nodes_lock);
    rt_list_insert_before(&i2s_nodes, &i2s->list);
    rt_spin_unlock(&i2s_nodes_lock);

    dev->user_data = i2s;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2s);

    LOG_D("%s: I2S%d controller ready", rt_dm_dev_get_name(dev), i2s->port);

    return RT_EOK;

_fail:
    spacemit_i2s_free(i2s);
    return err;
}

static rt_err_t spacemit_i2s_remove(struct rt_platform_device *pdev)
{
    struct spacemit_i2s *i2s = pdev->parent.user_data;

    if (!i2s)
    {
        return RT_EOK;
    }

    rt_spin_lock(&i2s_nodes_lock);
    rt_list_remove(&i2s->list);
    rt_spin_unlock(&i2s_nodes_lock);

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    spacemit_i2s_free(i2s);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_i2s_ofw_ids[] =
{
    { .compatible = "spacemit,spacemit-i2s0" },
    { .compatible = "spacemit,spacemit-i2s1" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_i2s_driver =
{
    .name = "spacemit-i2s",
    .ids = spacemit_i2s_ofw_ids,
    .probe = spacemit_i2s_probe,
    .remove = spacemit_i2s_remove,
};

static int spacemit_i2s_register(void)
{
    rt_platform_driver_register(&spacemit_i2s_driver);
    return 0;
}
INIT_DEVICE_EXPORT(spacemit_i2s_register);
