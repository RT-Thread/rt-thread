/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#include <rthw.h>

#define DBG_TAG "audio.sai"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rockchip-sai.h"
#include "rockchip-audio-clock.h"

#define SAI_TXCR             0x00
#define SAI_FSCR             0x04
#define SAI_MONO_CR          0x0c
#define SAI_XFER             0x10
#define SAI_CLR              0x14
#define SAI_CKR              0x18
#define SAI_DMACR            0x24
#define SAI_INTCR            0x28
#define SAI_TXDR             0x30
#define SAI_PATH_SEL         0x38
#define SAI_TX_SLOT_MASK0    0x3c
#define SAI_TX_SHIFT         0x64
#define SAI_VERSION          0x70
#define SAI_STATUS           0x6c

#define SAI_TXCR_I2S         (RT_BIT(22) | RT_BIT(10))
#define SAI_TXCR_STEREO      RT_BIT(11)
#define SAI_TXCR_SLOT_32     (31U << 5)
#define SAI_FSCR_STEREO_32   (RT_BIT(24) | (31U << 12) | 63U)
#define SAI_CLK_EN           RT_BIT(0)
#define SAI_FS_EN            RT_BIT(1)
#define SAI_TX_EN            RT_BIT(2)
#define SAI_TX_IDLE          RT_BIT(7)
#define SAI_FS_IDLE          RT_BIT(6)
#define SAI_TX_CLEAR         RT_BIT(0)
#define SAI_DMA_TX_EN        RT_BIT(8)
#define SAI_DMA_THRESHOLD    16U
#define SAI_TX_UNDERRUN_CLR  RT_BIT(2)
#define SAI_VER_2307         0x23073576
#define SAI_VER_2311         0x23112118

struct rockchip_sai
{
    rt_list_t list;
    struct rt_ofw_node *np;
    void *regs;
    rt_uint64_t phys;
    struct rt_clk *hclk;
    struct rt_clk *mclk;
    struct rt_reset_control *rst_h;
    struct rt_reset_control *rst_m;
    struct rt_dma_chan *dma_tx;
    rt_uint32_t version;
    rt_bool_t configured;
    rt_bool_t running;
};

static rt_list_t sai_list = RT_LIST_OBJECT_INIT(sai_list);
static RT_DEFINE_SPINLOCK(sai_lock);

static rt_err_t sai_poll(struct rockchip_sai *sai, rt_uint32_t reg,
        rt_uint32_t mask, rt_uint32_t value)
{
    int timeout;

    for (timeout = 0; timeout < 1000; ++timeout)
    {
        if ((HWREG32(sai->regs + reg) & mask) == value)
        {
            return RT_EOK;
        }
        rt_hw_us_delay(1);
    }
    LOG_E("%s: register %x timeout", sai->np->name, reg);
    return -RT_ETIMEOUT;
}

static rt_err_t sai_idle(struct rockchip_sai *sai, rt_bool_t frame)
{
    rt_uint32_t reg = SAI_XFER;
    rt_uint32_t mask = frame ? SAI_FS_IDLE : SAI_TX_IDLE;

    if (sai->version >= SAI_VER_2307)
    {
        reg = SAI_STATUS;
        mask = frame ? RT_BIT(1) : RT_BIT(2);
        if (sai->version >= SAI_VER_2311)
        {
            mask >>= 1;
        }
    }
    return sai_poll(sai, reg, mask, mask);
}

struct rockchip_sai *rockchip_sai_find(struct rt_ofw_node *np)
{
    struct rockchip_sai *sai;
    struct rockchip_sai *found;

    found = RT_NULL;

    rt_spin_lock(&sai_lock);
    rt_list_for_each_entry(sai, &sai_list, list)
    {
        if (sai->np == np)
        {
            found = sai;
            break;
        }
    }
    rt_spin_unlock(&sai_lock);
    return found;
}

struct rt_dma_chan *rockchip_sai_dma_tx(struct rockchip_sai *sai)
{
    return sai->dma_tx;
}

rt_ubase_t rockchip_sai_txdr_phys(struct rockchip_sai *sai)
{
    return sai->phys + SAI_TXDR;
}

rt_err_t rockchip_sai_hw_params(struct rockchip_sai *sai,
        const struct rockchip_i2s_config *cfg)
{
    rt_err_t err;
    rt_uint32_t mclk;
    rt_uint32_t div;
    rt_uint64_t actual;
    rt_uint64_t delta;

    if (cfg->channels != 2 || cfg->samplebits != 16 ||
        (cfg->samplerate != 44100 && cfg->samplerate != 48000) ||
        (cfg->mclk_fs != 128 && cfg->mclk_fs != 256))
    {
        return -RT_EINVAL;
    }
    if (sai->running)
    {
        return -RT_EBUSY;
    }

    sai->configured = RT_FALSE;
    mclk = cfg->samplerate * cfg->mclk_fs;
    if ((err = rockchip_audio_set_mclk(sai->mclk, mclk)))
    {
        return err;
    }
    actual = rt_clk_get_rate(sai->mclk);
    delta = actual > mclk ? actual - mclk : mclk - actual;
    if (delta > mclk / 100000)
    {
        LOG_E("%s: mclk=%lu, expected %u", sai->np->name,
                (rt_ubase_t)actual, mclk);
        return -RT_EINVAL;
    }
    div = cfg->mclk_fs / 64;

    HWREG32(sai->regs + SAI_CKR) = (div - 1) << 3;
    HWREG32(sai->regs + SAI_TXCR) = SAI_TXCR_I2S | SAI_TXCR_STEREO |
            SAI_TXCR_SLOT_32 | 15;
    HWREG32(sai->regs + SAI_FSCR) = SAI_FSCR_STEREO_32;
    HWREG32(sai->regs + SAI_TX_SHIFT) = 2;
    HWREG32(sai->regs + SAI_MONO_CR) = 0;
    HWREG32(sai->regs + SAI_DMACR) = SAI_DMA_THRESHOLD;
    sai->configured = RT_TRUE;
    return RT_EOK;
}

rt_err_t rockchip_sai_start(struct rockchip_sai *sai)
{
    if (!sai->configured)
    {
        return -RT_EINVAL;
    }
    if (sai->running)
    {
        return RT_EOK;
    }

    /* Allow the divider to settle before enabling BCLK and frame sync. */
    rt_hw_us_delay(20);
    HWREG32(sai->regs + SAI_XFER) = SAI_CLK_EN | SAI_FS_EN;
    HWREG32(sai->regs + SAI_INTCR) = SAI_TX_UNDERRUN_CLR;
    HWREG32(sai->regs + SAI_DMACR) = SAI_DMA_THRESHOLD | SAI_DMA_TX_EN;
    HWREG32(sai->regs + SAI_XFER) = SAI_CLK_EN | SAI_FS_EN | SAI_TX_EN;
    sai->running = RT_TRUE;
    return RT_EOK;
}

rt_err_t rockchip_sai_stop(struct rockchip_sai *sai)
{
    rt_err_t err;
    rt_err_t result;

    if (!sai->running)
    {
        return RT_EOK;
    }

    HWREG32(sai->regs + SAI_DMACR) = SAI_DMA_THRESHOLD;
    HWREG32(sai->regs + SAI_XFER) = SAI_CLK_EN | SAI_FS_EN;
    result = sai_idle(sai, RT_FALSE);
    HWREG32(sai->regs + SAI_CLR) = SAI_TX_CLEAR;
    err = sai_poll(sai, SAI_CLR, SAI_TX_CLEAR, 0);
    if (!result)
    {
        result = err;
    }
    HWREG32(sai->regs + SAI_XFER) = 0;
    err = sai_idle(sai, RT_TRUE);
    if (!result)
    {
        result = err;
    }
    rt_hw_us_delay(40);
    sai->running = RT_FALSE;
    if (result)
    {
        sai->configured = RT_FALSE;
    }
    return result;
}

static rt_err_t sai_reset(struct rt_reset_control *rst)
{
    rt_err_t err;

    if ((err = rt_reset_control_assert(rst)))
    {
        return err;
    }
    rt_hw_us_delay(10);
    err = rt_reset_control_deassert(rst);
    rt_hw_us_delay(10);
    return err;
}

static rt_err_t rockchip_sai_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_sai *sai;
    int i;

    sai = rt_calloc(1, sizeof(*sai));

    if (!sai)
    {
        return -RT_ENOMEM;
    }
    sai->np = dev->ofw_node;
    sai->regs = rt_dm_dev_iomap(dev, 0);
    if (!sai->regs)
    {
        err = -RT_EIO;
        goto _free;
    }
    if ((err = rt_dm_dev_get_address(dev, 0, &sai->phys, RT_NULL)))
    {
        goto _unmap;
    }
    sai->hclk = rt_clk_get_by_name(dev, "hclk");
    sai->mclk = rt_clk_get_by_name(dev, "mclk");
    sai->rst_h = rt_reset_control_get_by_name(dev, "h");
    sai->rst_m = rt_reset_control_get_by_name(dev, "m");
    if (rt_is_err(sai->hclk) || rt_is_err(sai->mclk) ||
        rt_is_err(sai->rst_h) || rt_is_err(sai->rst_m))
    {
        err = -RT_EIO;
        LOG_E("%s: missing clock or reset", sai->np->name);
        goto _put;
    }
    if ((err = rt_clk_prepare_enable(sai->hclk)))
    {
        goto _put;
    }
    if ((err = rt_clk_prepare_enable(sai->mclk)))
    {
        goto _disable_hclk;
    }
    /* Reset the bus domain first to restore master mode before resetting MCLK. */
    if ((err = sai_reset(sai->rst_h)) || (err = sai_reset(sai->rst_m)))
    {
        goto _disable_mclk;
    }
    sai->version = HWREG32(sai->regs + SAI_VERSION);
    HWREG32(sai->regs + SAI_XFER) = 0;
    HWREG32(sai->regs + SAI_DMACR) = 0;
    HWREG32(sai->regs + SAI_INTCR) = SAI_TX_UNDERRUN_CLR;
    HWREG32(sai->regs + SAI_PATH_SEL) = 0xe4e4;
    for (i = 0; i < 4; ++i)
    {
        HWREG32(sai->regs + SAI_TX_SLOT_MASK0 + i * 4) = 0;
    }

    sai->dma_tx = rt_dma_chan_request(dev, "tx");
    if (rt_is_err_or_null(sai->dma_tx))
    {
        err = rt_is_err(sai->dma_tx) ? rt_ptr_err(sai->dma_tx) : -RT_ENOSYS;
        LOG_E("%s: TX DMA unavailable (%d)", sai->np->name, err);
        goto _disable_mclk;
    }
    rt_spin_lock(&sai_lock);
    rt_list_insert_before(&sai_list, &sai->list);
    rt_spin_unlock(&sai_lock);
    dev->user_data = sai;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, sai);
    LOG_D("%s: SAI playback ready, version=%08x", sai->np->name, sai->version);
    return RT_EOK;

_disable_mclk:
    rt_clk_disable_unprepare(sai->mclk);
_disable_hclk:
    rt_clk_disable_unprepare(sai->hclk);
_put:
    if (!rt_is_err_or_null(sai->rst_m))
    {
        rt_reset_control_put(sai->rst_m);
    }
    if (!rt_is_err_or_null(sai->rst_h))
    {
        rt_reset_control_put(sai->rst_h);
    }
    if (!rt_is_err_or_null(sai->mclk))
    {
        rt_clk_put(sai->mclk);
    }
    if (!rt_is_err_or_null(sai->hclk))
    {
        rt_clk_put(sai->hclk);
    }
_unmap:
    rt_iounmap(sai->regs);
_free:
    rt_free(sai);
    return err;
}

static rt_err_t rockchip_sai_remove(struct rt_platform_device *pdev)
{
    struct rockchip_sai *sai = pdev->parent.user_data;
    rt_err_t err;

    err = rt_dma_chan_stop(sai->dma_tx);
    if (!err)
    {
        err = rockchip_sai_stop(sai);
    }
    if (err)
    {
        return err;
    }
    rt_dma_chan_release(sai->dma_tx);
    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    rt_spin_lock(&sai_lock);
    rt_list_remove(&sai->list);
    rt_spin_unlock(&sai_lock);
    rt_reset_control_assert(sai->rst_m);
    rt_reset_control_assert(sai->rst_h);
    rt_reset_control_put(sai->rst_m);
    rt_reset_control_put(sai->rst_h);
    rt_clk_disable_unprepare(sai->mclk);
    rt_clk_disable_unprepare(sai->hclk);
    rt_clk_put(sai->mclk);
    rt_clk_put(sai->hclk);
    rt_iounmap(sai->regs);
    rt_free(sai);
    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_sai_ids[] =
{
    { .compatible = "rockchip,rk3528-sai" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_sai_driver =
{
    .name = "rockchip-sai",
    .ids = rockchip_sai_ids,
    .probe = rockchip_sai_probe,
    .remove = rockchip_sai_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_sai_driver);
