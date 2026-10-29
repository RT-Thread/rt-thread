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
#include "rockchip-audio-clock.h"

#define I2S_FIFO_DEPTH          32
#define I2S_DEFAULT_MCLK_FS     256
#define I2S_CLEAR_TIMEOUT_US    100
#define I2S_PIO_WAIT_US         10
#define I2S_PIO_TIMEOUT_US      100000

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
    rt_bool_t always_on;
    rt_bool_t hdmi_path;
    rt_bool_t mclk_enabled;
    rt_bool_t running;
    rt_uint32_t tx_underruns;

    rt_uint32_t mclk_fs;
    struct rockchip_i2s_config config;
    rt_uint32_t pio_word_delay_us;

    struct rt_dma_chan *dma_tx;
    rt_ubase_t dma_addr;

    struct rt_ofw_node *np;
    rt_list_t list;
};

static rt_list_t i2s_list = RT_LIST_OBJECT_INIT(i2s_list);
static RT_DEFINE_SPINLOCK(i2s_list_lock);

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

static rt_err_t rockchip_i2s_tdm_clear_tx(struct rockchip_i2s_tdm *i2s)
{
    rt_uint32_t retry;

    i2s_writel(i2s, I2S_CLR, I2S_CLR_TXC);

    for (retry = 0; retry < I2S_CLEAR_TIMEOUT_US / 10; ++retry)
    {
        if (!(i2s_readl(i2s, I2S_CLR) & I2S_CLR_TXC))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }

    /* Match Linux's recovery for a TX FIFO that refuses to clear. */
    if (!rt_is_err_or_null(i2s->rst_tx))
    {
        rt_reset_control_reset(i2s->rst_tx);
        rt_hw_us_delay(10);
    }

    i2s_writel(i2s, I2S_CLR, I2S_CLR_TXC);
    for (retry = 0; retry < I2S_CLEAR_TIMEOUT_US / 10; ++retry)
    {
        if (!(i2s_readl(i2s, I2S_CLR) & I2S_CLR_TXC))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }

    LOG_E("TX FIFO clear timeout, clr=%08x", i2s_readl(i2s, I2S_CLR));
    return -RT_ETIMEOUT;
}

rt_err_t rockchip_i2s_tdm_hw_params(struct rockchip_i2s_tdm *i2s,
        const struct rockchip_i2s_config *cfg)
{
    rt_uint32_t mclk_rate, bclk_rate, lrck_rate;
    rt_uint32_t div_bclk, div_lrck;
    rt_uint32_t fmt = I2S_TXCR_VDW(cfg->samplebits) | I2S_CHN_2;
    rt_err_t err;

    if (!i2s || !cfg || !cfg->samplerate || !cfg->channels)
    {
        return -RT_EINVAL;
    }

    i2s->config = *cfg;
    i2s->mclk_fs = cfg->mclk_fs ? cfg->mclk_fs : I2S_DEFAULT_MCLK_FS;
    i2s->pio_word_delay_us = RT_DIV_ROUND_UP(1000000U,
            cfg->samplerate * cfg->channels);

    if (i2s->mclk_tx)
    {
        mclk_rate = cfg->samplerate * i2s->mclk_fs;

        if ((err = rockchip_audio_set_mclk(i2s->mclk_tx, mclk_rate)))
        {
            LOG_E("set mclk_tx rate %u failed", mclk_rate);
            return err;
        }

        if (!i2s->mclk_enabled && (err = rt_clk_prepare_enable(i2s->mclk_tx)))
        {
            return err;
        }

        i2s->mclk_enabled = RT_TRUE;
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

    LOG_D("%s: %u Hz %u ch %u bit, mclk=%u bclk=%u div=%u/%u regs=%08x/%08x/%08x",
            rt_dm_dev_get_name(&i2s->parent), cfg->samplerate, cfg->channels,
            cfg->samplebits, mclk_rate, bclk_rate, div_bclk, div_lrck,
            i2s_readl(i2s, I2S_TXCR), i2s_readl(i2s, I2S_CKR),
            i2s_readl(i2s, I2S_CLKDIV));

    return RT_EOK;
}

rt_err_t rockchip_i2s_tdm_start(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return -RT_EINVAL;
    }

    /*
     * HDMI I2S is kept clocked between streams.  Match the Linux sequence
     * for a new stream so stale words cannot keep the DMA request asserted.
     */
    if (i2s->always_on && i2s->hdmi_path)
    {
        i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK, I2S_XFER_TXS_STOP);
        rt_hw_us_delay(150);
    }

    /* CLR completes in the SCLK domain, which starts with XFER below. */
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

    /*
     * HDMI's always-on path keeps BCLK/LRCK and the transmitter alive
     * between DMA streams.  This is the equivalent of Linux's
     * rockchip_i2s_tdm_xfer_stop(..., false), which is intentionally a
     * no-op for the ALWAYS_ON quirk.
     */
    if (!i2s->always_on)
    {
        if (i2s->trcm_tx_only)
        {
            i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK | I2S_XFER_RXS_MASK,
                    I2S_XFER_TXS_STOP | I2S_XFER_RXS_STOP);
            rockchip_i2s_tdm_clear_tx(i2s);
        }
        else
        {
            i2s_update_bits(i2s, I2S_XFER, I2S_XFER_TXS_MASK, I2S_XFER_TXS_STOP);
            rockchip_i2s_tdm_clear_tx(i2s);
        }

        rt_hw_us_delay(150);
    }
    i2s->running = RT_FALSE;

    if (!i2s->always_on && i2s->mclk_tx && i2s->mclk_enabled)
    {
        rt_clk_disable_unprepare(i2s->mclk_tx);
        i2s->mclk_enabled = RT_FALSE;
    }

    return RT_EOK;
}

rt_ssize_t rockchip_i2s_tdm_push(struct rockchip_i2s_tdm *i2s,
        const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i = 0;
    rt_uint32_t wait_us = 0;
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
            wait_us += I2S_PIO_WAIT_US;
            if (wait_us > I2S_PIO_TIMEOUT_US)
            {
                LOG_E("TX FIFO stalled: fifo=%u xfer=%08x ckr=%08x txcr=%08x div=%08x",
                        fifo, i2s_readl(i2s, I2S_XFER), i2s_readl(i2s, I2S_CKR),
                        i2s_readl(i2s, I2S_TXCR), i2s_readl(i2s, I2S_CLKDIV));
                return -RT_ETIMEOUT;
            }
            rt_hw_us_delay(I2S_PIO_WAIT_US);
            continue;
        }

        wait_us = 0;
        i2s_writel(i2s, I2S_TXDR, buf[i] | (buf[i + 1] << 8));
        i += 2;

        /*
         * The RK3588 HDMI I2S FIFO level can stay at zero in PIO mode.
         * Pace each channel word from the configured sample rate so writes
         * cannot overrun a FIFO whose level is not observable.
         */
        rt_hw_us_delay(i2s->pio_word_delay_us);
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

    /*
     * The HDMI controller drops its first frame-sync cycle.  Seed one
     * complete stereo S16 frame before enabling its DMA request, matching
     * the Rockchip Linux driver's HDMI-path workaround.
     */
    if (i2s->hdmi_path)
    {
        i2s_writel(i2s, I2S_TXDR, 0);
    }

    i2s->tx_underruns = 0;
    i2s_update_bits(i2s, I2S_INTCR, I2S_INTCR_TXUIC, I2S_INTCR_TXUIC);

    i2s_update_bits(i2s, I2S_DMACR, I2S_DMACR_TDL_MASK | I2S_DMACR_TDE_MASK,
            I2S_DMACR_TDL(16) | I2S_DMACR_TDE_ENABLE);

    /* Give DMA a head start before the transmitter consumes the FIFO. */
    if (i2s->hdmi_path)
    {
        rt_hw_us_delay(1);
    }

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

void rockchip_i2s_tdm_dma_check_underrun(struct rockchip_i2s_tdm *i2s)
{
    if (!i2s)
    {
        return;
    }

    if (i2s_readl(i2s, I2S_INTSR) & I2S_INTSR_TXUI)
    {
        i2s->tx_underruns++;
        i2s_update_bits(i2s, I2S_INTCR, I2S_INTCR_TXUIC, I2S_INTCR_TXUIC);
    }
}

rt_uint32_t rockchip_i2s_tdm_dma_underruns(struct rockchip_i2s_tdm *i2s)
{
    return i2s ? i2s->tx_underruns : 0;
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
    i2s->always_on = rt_dm_dev_prop_read_bool(dev, "rockchip,always-on");
    i2s->hdmi_path = rt_dm_dev_prop_read_bool(dev, "rockchip,hdmi-path");

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

    if (i2s->always_on)
    {
        const struct rockchip_i2s_config default_cfg =
        {
            .samplerate = 48000,
            .channels = 2,
            .samplebits = 16,
            .mclk_fs = I2S_DEFAULT_MCLK_FS,
        };

        if ((err = rockchip_i2s_tdm_hw_params(i2s, &default_cfg)))
        {
            goto _fail;
        }

        /* This must follow every register configuration on HDMI I2S. */
        if ((err = rockchip_i2s_tdm_start(i2s)))
        {
            goto _fail;
        }
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
