/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>

#define DBG_TAG "i2s.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rockchip.h"
#include "rockchip-i2s-tdm.h"

#define I2S_FIFO_DEPTH      32
#define I2S_DEFAULT_MCLK_FS 256

struct rockchip_i2s_tdm
{
    struct rt_device parent;

    void *regs;
    rt_ubase_t phys;
    int irq;

    struct rt_clk *hclk;
    struct rt_clk *mclk_tx;
    struct rt_clk *mclk_rx;
    struct rt_reset_control *rst_tx;
    struct rt_reset_control *rst_rx;
    struct rt_syscon *grf;

    rt_bool_t trcm_tx_only;
    rt_bool_t playback_only;
    rt_bool_t running;

    rt_uint32_t mclk_fs;
    struct rockchip_i2s_config config;

    struct rt_dma_chan *dma_tx;
    rt_ubase_t dma_addr;

    struct rt_ofw_node *np;
    rt_list_t list;
};

static rt_list_t i2s_list = RT_LIST_OBJECT_INIT(i2s_list);
static RT_DEFINE_SPINLOCK(i2s_list_lock);

static rt_err_t rockchip_i2s_tdm_set_mclk(struct rockchip_i2s_tdm *i2s,
        rt_ubase_t rate)
{
    struct rt_clk_cell *cell, *parent;
    struct rt_clk *clk;
    rt_err_t err;

    cell = i2s->mclk_tx->cell;

    /* Skip pass-through gates and configure the first programmable clock. */
    while (cell->parents_nr == 1 && !cell->ops->set_rate)
    {
        cell = rt_clk_cell_get_parent_by_index(cell, 0);
        if (!cell)
        {
            return -RT_ENOSYS;
        }
    }

    if (cell->ops->set_rate)
    {
        clk = rt_clk_cell_get_clk(cell, RT_NULL);
        return clk ? rt_clk_set_rate(clk, rate) : -RT_ENOMEM;
    }

    /* Rockchip I2S muxes use an internal fractional clock for audio rates. */
    for (rt_uint8_t index = 0; index < cell->parents_nr; ++index)
    {
        parent = rt_clk_cell_get_parent_by_index(cell, index);
        if (!parent || !parent->ops->set_rate)
        {
            continue;
        }

        if (rt_clk_cell_round_rate(parent, rate) != rate)
        {
            continue;
        }

        clk = rt_clk_cell_get_clk(parent, RT_NULL);
        if (!clk || (err = rt_clk_set_rate(clk, rate)))
        {
            continue;
        }

        if ((err = rt_clk_cell_set_parent(cell, parent)))
        {
            return err;
        }

        return RT_EOK;
    }

    return -RT_ENOSYS;
}

rt_inline rt_uint32_t i2s_readl(struct rockchip_i2s_tdm *i2s, rt_ubase_t reg)
{
    return HWREG32(i2s->regs + reg);
}

rt_inline void i2s_writel(struct rockchip_i2s_tdm *i2s, rt_ubase_t reg, rt_uint32_t val)
{
    HWREG32(i2s->regs + reg) = val;
}

rt_inline void i2s_update_bits(struct rockchip_i2s_tdm *i2s,
        rt_ubase_t reg, rt_uint32_t mask, rt_uint32_t val)
{
    rt_uint32_t tmp = i2s_readl(i2s, reg);

    tmp &= ~mask;
    tmp |= (val & mask);
    i2s_writel(i2s, reg, tmp);
}

struct rockchip_i2s_tdm *rockchip_i2s_tdm_find(struct rt_ofw_node *np)
{
    struct rockchip_i2s_tdm *i2s;

    rt_spin_lock(&i2s_list_lock);
    rt_list_for_each_entry(i2s, &i2s_list, list)
    {
        if (i2s->np == np)
        {
            rt_spin_unlock(&i2s_list_lock);
            return i2s;
        }
    }
    rt_spin_unlock(&i2s_list_lock);

    return RT_NULL;
}

static rt_err_t rockchip_i2s_tdm_grf_init(struct rockchip_i2s_tdm *i2s)
{
    rt_uint64_t addr;

    if (!i2s->trcm_tx_only || !i2s->grf)
    {
        return RT_EOK;
    }

    if (rt_dm_dev_get_address(&i2s->parent, 0, &addr, RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (addr == 0xfe410000)
    {
        return rt_syscon_write(i2s->grf, RK3568_I2S1_GRF_REG, RK3568_I2S1_CLK_TXONLY);
    }

    return RT_EOK;
}

static rt_err_t rockchip_i2s_tdm_set_fmt(struct rockchip_i2s_tdm *i2s)
{
    rt_uint32_t val = I2S_CKR_MSS_MASTER | I2S_CKR_CKP_NORMAL |
            I2S_CKR_TLP_NORMAL | I2S_CKR_RLP_NORMAL;
    rt_uint32_t txcr = I2S_TXCR_IBM_NORMAL | I2S_TXCR_TFS_I2S | I2S_CHN_2;

    if (i2s->trcm_tx_only)
    {
        val |= I2S_CKR_TRCM_TXONLY;
    }

    i2s_update_bits(i2s, I2S_CKR, I2S_CKR_MSS_MASK | I2S_CKR_TRCM_MASK |
            (3 << 24) | (1 << 26), val);
    i2s_update_bits(i2s, I2S_TXCR, I2S_TXCR_VDW_MASK | I2S_TXCR_CSR_MASK |
            (3 << 5) | (3 << 9), txcr | I2S_TXCR_VDW(16));

    return RT_EOK;
}

rt_err_t rockchip_i2s_tdm_hw_params(struct rockchip_i2s_tdm *i2s,
        const struct rockchip_i2s_config *cfg)
{
    rt_uint32_t mclk_rate, bclk_rate, lrck_rate;
    rt_uint32_t div_bclk, div_lrck;
    rt_uint32_t fmt = I2S_TXCR_VDW(cfg->samplebits) | I2S_CHN_2;
    rt_err_t err;

    if (!i2s || !cfg)
    {
        return -RT_EINVAL;
    }

    i2s->config = *cfg;
    i2s->mclk_fs = cfg->mclk_fs ? cfg->mclk_fs : I2S_DEFAULT_MCLK_FS;

    if (i2s->mclk_tx)
    {
        mclk_rate = cfg->samplerate * i2s->mclk_fs;

        if ((err = rockchip_i2s_tdm_set_mclk(i2s, mclk_rate)))
        {
            LOG_E("set mclk_tx rate %u failed", mclk_rate);
            return err;
        }

        if ((err = rt_clk_prepare_enable(i2s->mclk_tx)))
        {
            return err;
        }
    }

    mclk_rate = i2s->mclk_tx ? rt_clk_get_rate(i2s->mclk_tx) : (cfg->samplerate * i2s->mclk_fs);
    lrck_rate = cfg->samplerate;
    /* Rockchip and DW-HDMI use two 32-bit I2S slots by default. */
    bclk_rate = I2S_DEFAULT_FRAME_WIDTH * lrck_rate;

    if (!bclk_rate)
    {
        return -RT_EINVAL;
    }

    div_bclk = RT_DIV_ROUND_CLOSEST(mclk_rate, bclk_rate);
    div_lrck = RT_DIV_ROUND_CLOSEST(bclk_rate, lrck_rate);

    if (div_bclk < 1)
    {
        div_bclk = 1;
    }

    if (div_lrck < 1)
    {
        div_lrck = 1;
    }

    rockchip_i2s_tdm_set_fmt(i2s);

    i2s_update_bits(i2s, I2S_CLKDIV, I2S_CLKDIV_TXM_MASK, I2S_CLKDIV_TXM(div_bclk));
    i2s_update_bits(i2s, I2S_CKR, I2S_CKR_TSD_MASK, I2S_CKR_TSD(div_lrck));
    i2s_update_bits(i2s, I2S_TXCR, I2S_TXCR_VDW_MASK | I2S_TXCR_CSR_MASK, fmt);

    return RT_EOK;
}

rt_err_t rockchip_i2s_tdm_start(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return -RT_EINVAL;
    }

    if (i2s->rst_tx)
    {
        rt_reset_control_assert(i2s->rst_tx);
        rt_reset_control_deassert(i2s->rst_tx);
    }

    i2s_writel(i2s, I2S_CLR, I2S_CLR_TXC);

    if (i2s->trcm_tx_only)
    {
        i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK | I2S_XFER_RXS_MASK,
                I2S_XFER_TXS_START | I2S_XFER_RXS_START);
    }
    else
    {
        i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK, I2S_XFER_TXS_START);
    }

    i2s->running = RT_TRUE;

    return RT_EOK;
}

rt_err_t rockchip_i2s_tdm_stop(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return -RT_EINVAL;
    }

    if (i2s->trcm_tx_only)
    {
        i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK | I2S_XFER_RXS_MASK,
                I2S_XFER_TXS_STOP | I2S_XFER_RXS_STOP);
        i2s_writel(i2s, I2S_CLR, I2S_CLR_TXC);
    }
    else
    {
        i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK, I2S_XFER_TXS_STOP);
        i2s_writel(i2s, I2S_CLR, I2S_CLR_TXC);
    }

    rt_hw_us_delay(150);
    i2s->running = RT_FALSE;

    if (i2s->mclk_tx)
    {
        rt_clk_disable_unprepare(i2s->mclk_tx);
    }

    return RT_EOK;
}

rt_ssize_t rockchip_i2s_tdm_push(struct rockchip_i2s_tdm *i2s,
        const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i = 0;
    rt_uint32_t fifo;

    if (!i2s || !buf || !size)
    {
        return 0;
    }

    while (i + 1 < size)
    {
        fifo = i2s_readl(i2s, I2S_TXFIFOLR) & I2S_FIFOLR_TFL0_MASK;

        if (fifo >= I2S_FIFO_DEPTH)
        {
            rt_thread_mdelay(1);
            continue;
        }

        i2s_writel(i2s, I2S_TXDR, buf[i] | (buf[i + 1] << 8));
        i += 2;
    }

    return i;
}

struct rt_dma_chan *rockchip_i2s_tdm_get_dma_tx(struct rockchip_i2s_tdm *i2s)
{
    return i2s ? i2s->dma_tx : RT_NULL;
}

rt_ubase_t rockchip_i2s_tdm_txdr_phys(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return 0;
    }

    return i2s->phys + I2S_TXDR;
}

rt_err_t rockchip_i2s_tdm_dma_enable(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return -RT_EINVAL;
    }

    i2s_update_bits(i2s, I2S_DMACR, I2S_DMACR_TDL_MASK | I2S_DMACR_TDE_MASK,
            I2S_DMACR_TDL(16) | I2S_DMACR_TDE_ENABLE);

    return RT_EOK;
}

rt_err_t rockchip_i2s_tdm_dma_disable(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return -RT_EINVAL;
    }

    i2s_update_bits(i2s, I2S_DMACR, I2S_DMACR_TDE_MASK, 0);

    return RT_EOK;
}

static rt_err_t rockchip_i2s_tdm_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_i2s_tdm *i2s;
    struct rt_ofw_node *grf_np;

    i2s = rt_calloc(1, sizeof(*i2s));

    if (!i2s)
    {
        return -RT_ENOMEM;
    }

    i2s->np = dev->ofw_node;
    i2s->parent.ofw_node = dev->ofw_node;
    i2s->trcm_tx_only = rt_dm_dev_prop_read_bool(dev, "rockchip,trcm-sync-tx-only");
    i2s->playback_only = rt_dm_dev_prop_read_bool(dev, "rockchip,playback-only");

    i2s->regs = rt_dm_dev_iomap(dev, 0);

    if (!i2s->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rt_dm_dev_get_address(dev, 0, &i2s->phys, RT_NULL);

    i2s->hclk = rt_clk_get_by_name(dev, "hclk");
    i2s->mclk_tx = rt_clk_get_by_name(dev, "mclk_tx");
    i2s->mclk_rx = rt_clk_get_by_name(dev, "mclk_rx");
    i2s->rst_tx = rt_reset_control_get_by_name(dev, "tx-m");
    i2s->rst_rx = rt_reset_control_get_by_name(dev, "rx-m");

    if (!rt_is_err(i2s->hclk))
    {
        rt_clk_prepare_enable(i2s->hclk);
    }

    if ((grf_np = rt_ofw_parse_phandle(dev->ofw_node, "rockchip,grf", 0)))
    {
        i2s->grf = rt_syscon_find_by_ofw_node(grf_np);
        rt_ofw_node_put(grf_np);
    }

    if ((err = rockchip_i2s_tdm_grf_init(i2s)))
    {
        goto _fail;
    }

    i2s->dma_tx = rt_dma_chan_request(dev, "tx");

    if (rt_is_err_or_null(i2s->dma_tx))
    {
        LOG_W("No DMA tx channel, using PIO");
        i2s->dma_tx = RT_NULL;
    }
    else
    {
        LOG_D("I2S DMA tx channel ready");
    }

    rt_spin_lock(&i2s_list_lock);
    rt_list_insert_before(&i2s_list, &i2s->list);
    rt_spin_unlock(&i2s_list_lock);

    dev->user_data = i2s;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2s);

    LOG_D("I2S/TDM probed at %p", i2s->regs);

    return RT_EOK;

_fail:
    rt_free(i2s);

    return err;
}

static rt_err_t rockchip_i2s_tdm_remove(struct rt_platform_device *pdev)
{
    struct rockchip_i2s_tdm *i2s = pdev->parent.user_data;

    if (!i2s)
    {
        return RT_EOK;
    }

    rt_spin_lock(&i2s_list_lock);
    rt_list_remove(&i2s->list);
    rt_spin_unlock(&i2s_list_lock);

    if (i2s->dma_tx)
    {
        rt_dma_chan_release(i2s->dma_tx);
        i2s->dma_tx = RT_NULL;
    }

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);

    if (!rt_is_err(i2s->hclk))
    {
        rt_clk_disable_unprepare(i2s->hclk);
    }

    rt_free(i2s);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_i2s_tdm_ofw_ids[] =
{
    { .compatible = "rockchip,rk3568-i2s-tdm" },
    { .compatible = "rockchip,rk3588-i2s-tdm" },
    { .compatible = "rockchip,rk3308-i2s-tdm" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_i2s_tdm_driver =
{
    .name = "rockchip-i2s-tdm",
    .ids = rockchip_i2s_tdm_ofw_ids,
    .probe = rockchip_i2s_tdm_probe,
    .remove = rockchip_i2s_tdm_remove,
};

static int rockchip_i2s_tdm_register(void)
{
    rt_platform_driver_register(&rockchip_i2s_tdm_driver);

    return 0;
}
INIT_DEVICE_EXPORT(rockchip_i2s_tdm_register);
