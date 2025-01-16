/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */

#include <rtthread.h>
#include <mm_aspace.h>
#include "sdhci.h"
#include <string.h>
#define DBG_TAG "RT_SDHCI"
#ifdef DRV_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>
static unsigned int debug_quirks = 0;
static unsigned int debug_quirks2;
/********************************************************* */
/*                        cmd                              */
/********************************************************* */


void rt_read_reg_debug(struct rt_sdhci_host *host)
{
    rt_kprintf("0x00 addddddddddddd              = %x \n", rt_sdhci_readl(host, 0x00));
    rt_kprintf("0x04 EMMC_BLOCKSIZE              = %x \n", rt_sdhci_readw(host, 0x04));
    rt_kprintf("0x06 EMMC_BLOCKCOUNT             = %x \n", rt_sdhci_readw(host, 0x06));
    rt_kprintf("0x08 RT_SDHCI_ARGUMENT           = %x \n", rt_sdhci_readl(host, 0x08));
    rt_kprintf("0x0c EMMC_XFER_MODE              = %x \n", rt_sdhci_readw(host, 0x0c));
    rt_kprintf("0x0e RT_SDHCI_COMMAND            = %x \n", rt_sdhci_readw(host, 0x0e));
    rt_kprintf("0x24 RT_SDHCI_PRESENT_STATE      = %x \n", rt_sdhci_readl(host, 0x24));
    rt_kprintf("0x28 RT_SDHCI_HOST_CONTROL       = %x \n", rt_sdhci_readb(host, 0x28));
    rt_kprintf("0x29 RT_SDHCI_POWER_CONTROL      = %x \n", rt_sdhci_readb(host, 0x29));
    rt_kprintf("0x2a EMMC_BGAP_CTRL              = %x \n", rt_sdhci_readb(host, 0x2a));
    rt_kprintf("0x2c EMMC_CLK_CTRL               = %x \n", rt_sdhci_readw(host, 0x2c));
    rt_kprintf("0x2e EMMC_TOUT_CTRL              = %x \n", rt_sdhci_readb(host, 0x2e));
    rt_kprintf("0x2f EMMC_SW_RST                 = %x \n", rt_sdhci_readb(host, 0x2f));
    rt_kprintf("0x30 RT_SDHCI_INT_STATUS         = %x \n", rt_sdhci_readw(host, 0x30));
    rt_kprintf("0x32 RT_SDHCI_ERR_INT_STATUS     = %x \n", rt_sdhci_readw(host, 0x32));
    rt_kprintf("0x34 RT_SDHCI_INT_ENABLE         = %x \n", rt_sdhci_readw(host, 0x34));
    rt_kprintf("0x36 EMMC ERROR INT STATEN       = %x \n", rt_sdhci_readw(host, 0x36));
    rt_kprintf("0x38 EMMC NORMAL INT SIGNAL EN   = %x \n", rt_sdhci_readw(host, 0x38));
    rt_kprintf("0x3a EMMC ERROR INT SIGNAL EN    = %x \n", rt_sdhci_readw(host, 0x3a));
    rt_kprintf("0x3c EMMC_AUTO_CMD_STAT          = %x \n", rt_sdhci_readw(host, 0x3c));
    rt_kprintf("0x3e EMMC_HOST_CTRL2             = %x \n", rt_sdhci_readw(host, 0x3e));
    rt_kprintf("0x40 EMMC_CAPABILITIES1          = %x \n", rt_sdhci_readl(host, 0x40));
    rt_kprintf("0x44 EMMC_CAPABILITIES2          = %x \n", rt_sdhci_readl(host, 0x44));
    rt_kprintf("0x52 EMMC_FORC_ERR_INT_STAT      = %x \n", rt_sdhci_readw(host, 0x52));
    rt_kprintf("0x54 EMMC_ADMA_ERR_STAT          = %x \n", rt_sdhci_readb(host, 0x54));
    rt_kprintf("0x58 EMMC_ADMA_SA                = %x \n", rt_sdhci_readl(host, 0x58));
    rt_kprintf("0x66 EMMC_PRESET_SDR12           = %x \n", rt_sdhci_readw(host, 0x66));
    rt_kprintf("0x68 EMMC_PRESET_SDR25           = %x \n", rt_sdhci_readw(host, 0x68));
    rt_kprintf("0x6a EMMC_PRESET_SDR50           = %x \n", rt_sdhci_readw(host, 0x6a));
    rt_kprintf("0x6c EMMC_PRESET_SDR104          = %x \n", rt_sdhci_readw(host, 0x6c));
    rt_kprintf("0x6e EMMC_PRESET_DDR50           = %x \n", rt_sdhci_readw(host, 0x6e));
    rt_kprintf("0x78 EMMC_ADMA_ID                = %x \n", rt_sdhci_readl(host, 0x78));
    rt_kprintf("0xfe EMMC_HOST_CNTRL_VERS        = %x \n", rt_sdhci_readw(host, 0xfe));

}
static inline rt_bool_t sdhci_has_requests(struct rt_sdhci_host *host)
{
    return host->cmd || host->data_cmd;
}

static inline rt_bool_t sdhci_auto_cmd23(struct rt_sdhci_host   *host,
                                         struct rt_mmcsd_req *mrq)
{
    return mrq->sbc && (host->flags & RT_SDHCI_AUTO_CMD23);
}

static inline rt_bool_t sdhci_auto_cmd12(struct rt_sdhci_host   *host,
                                         struct rt_mmcsd_req *mrq)
{
    return !mrq->sbc && (host->flags & RT_SDHCI_AUTO_CMD12) && !mrq->cap_cmd_during_tfr;
}

static inline rt_bool_t sdhci_manual_cmd23(struct rt_sdhci_host   *host,
                                           struct rt_mmcsd_req *mrq)
{
    return mrq->sbc && !(host->flags & RT_SDHCI_AUTO_CMD23);
}

static inline rt_bool_t sdhci_data_line_cmd(struct rt_mmcsd_cmd *cmd)
{
    return cmd->data || cmd->flags & MMC_RSP_BUSY;
}

void rt_sdhci_data_irq_timeout(struct rt_sdhci_host *host, rt_bool_t enable)
{
    if (enable)
        host->ier |= RT_SDHCI_INT_DATA_TIMEOUT;
    else
        host->ier &= ~RT_SDHCI_INT_DATA_TIMEOUT;
    rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
}

void rt_sdhci_set_uhs(struct rt_sdhci_host *host, unsigned timing)
{
    rt_uint16_t ctrl_2;

    ctrl_2 = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);

    ctrl_2 &= ~RT_SDHCI_CTRL_UHS_MASK;
    if ((timing == MMC_TIMING_MMC_HS200) || (timing == MMC_TIMING_UHS_SDR104))
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR104;
    else if (timing == MMC_TIMING_UHS_SDR12)
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR12;
    else if (timing == MMC_TIMING_UHS_SDR25)
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR25;
    else if (timing == MMC_TIMING_UHS_SDR50)
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR50;
    else if ((timing == MMC_TIMING_UHS_DDR50) || (timing == MMC_TIMING_MMC_DDR52))
        ctrl_2 |= RT_SDHCI_CTRL_UHS_DDR50;
    else if (timing == MMC_TIMING_MMC_HS400)
        ctrl_2 |= RT_SDHCI_CTRL_HS400; /* Non-standard */
    rt_sdhci_writew(host, ctrl_2, RT_SDHCI_HOST_CONTROL2);
}

void rt_sdhci_set_bus_width(struct rt_sdhci_host *host, int width)
{
    rt_uint8_t ctrl;

    ctrl = rt_sdhci_readb(host, RT_SDHCI_HOST_CONTROL);
    if (width == MMC_BUS_WIDTH_8)
    {
        ctrl &= ~RT_SDHCI_CTRL_4BITBUS;
        ctrl |= RT_SDHCI_CTRL_8BITBUS;
    }
    else
    {
        if (host->mmc->caps & MMC_CAP_8_BIT_DATA)
            ctrl &= ~RT_SDHCI_CTRL_8BITBUS;
        if (width == MMC_BUS_WIDTH_4)
            ctrl |= RT_SDHCI_CTRL_4BITBUS;
        else
            ctrl &= ~RT_SDHCI_CTRL_4BITBUS;
    }
    rt_sdhci_writeb(host, ctrl, RT_SDHCI_HOST_CONTROL);
}

static inline rt_bool_t sdhci_can_64bit_dma(struct rt_sdhci_host *host)
{
    if (host->version >= RT_SDHCI_SPEC_410 && host->v4_mode)
        return host->caps & RT_SDHCI_CAN_64BIT_V4;

    return host->caps & RT_SDHCI_CAN_64BIT;
}

static void sdhci_do_enable_v4_mode(struct rt_sdhci_host *host)
{
    rt_uint16_t ctrl2;

    ctrl2 = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
    if (ctrl2 & RT_SDHCI_CTRL_V4_MODE)
        return;

    ctrl2 |= RT_SDHCI_CTRL_V4_MODE;
    rt_sdhci_writew(host, ctrl2, RT_SDHCI_HOST_CONTROL2);
}

void rt_sdhci_cleanup_host(struct rt_sdhci_host *host)
{
    return;
}

static void sdhci_set_default_irqs(struct rt_sdhci_host *host)
{
    host->ier = RT_SDHCI_INT_BUS_POWER | RT_SDHCI_INT_DATA_END_BIT | RT_SDHCI_INT_DATA_CRC | RT_SDHCI_INT_DATA_TIMEOUT | RT_SDHCI_INT_INDEX | RT_SDHCI_INT_END_BIT | RT_SDHCI_INT_CRC | RT_SDHCI_INT_TIMEOUT | RT_SDHCI_INT_DATA_END | RT_SDHCI_INT_RESPONSE;

    if (host->tuning_mode == RT_SDHCI_TUNING_MODE_2 || host->tuning_mode == RT_SDHCI_TUNING_MODE_3)
        host->ier |= RT_SDHCI_INT_RETUNE;

    rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
}


static inline void sdhci_auto_cmd_select(struct rt_sdhci_host   *host,
                                         struct rt_mmcsd_cmd *cmd,
                                         rt_uint16_t         *mode)
{
    rt_bool_t   use_cmd12 = sdhci_auto_cmd12(host, cmd->mrq) && (cmd->cmd_code != SD_IO_RW_EXTENDED);
    rt_bool_t   use_cmd23 = sdhci_auto_cmd23(host, cmd->mrq);
    rt_uint16_t ctrl2;

    if (host->version >= RT_SDHCI_SPEC_410 && host->v4_mode && (use_cmd12 || use_cmd23))
    {
        *mode |= RT_SDHCI_TRNS_AUTO_SEL;

        ctrl2 = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
        if (use_cmd23)
            ctrl2 |= RT_SDHCI_CMD23_ENABLE;
        else
            ctrl2 &= ~RT_SDHCI_CMD23_ENABLE;
        rt_sdhci_writew(host, ctrl2, RT_SDHCI_HOST_CONTROL2);

        return;
    }

    if (use_cmd12)
        *mode |= RT_SDHCI_TRNS_AUTO_CMD12;
    else if (use_cmd23)
        *mode |= RT_SDHCI_TRNS_AUTO_CMD23;
}


static rt_bool_t sdhci_present_error(struct rt_sdhci_host   *host,
                                     struct rt_mmcsd_cmd *cmd, rt_bool_t present)
{
    if (!present || host->flags & RT_SDHCI_DEVICE_DEAD)
    {
        cmd->err = -ENOMEDIUM;
        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_uint16_t sdhci_get_preset_value(struct rt_sdhci_host *host)
{
    rt_uint16_t preset = 0;

    switch (host->timing)
    {
    case MMC_TIMING_MMC_HS:
    case MMC_TIMING_SD_HS:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_HIGH_SPEED);
        break;
    case MMC_TIMING_UHS_SDR12:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_SDR12);
        break;
    case MMC_TIMING_UHS_SDR25:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_SDR25);
        break;
    case MMC_TIMING_UHS_SDR50:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_SDR50);
        break;
    case MMC_TIMING_UHS_SDR104:
    case MMC_TIMING_MMC_HS200:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_SDR104);
        break;
    case MMC_TIMING_UHS_DDR50:
    case MMC_TIMING_MMC_DDR52:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_DDR50);
        break;
    case MMC_TIMING_MMC_HS400:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_HS400);
        break;
    default:
        preset = rt_sdhci_readw(host, RT_SDHCI_PRESET_FOR_SDR12);
        break;
    }
    return preset;
}

static void sdhci_set_card_detection(struct rt_sdhci_host *host, rt_bool_t enable)
{
    rt_uint32_t present;

    if ((host->quirks & RT_SDHCI_QUIRK_BROKEN_CARD_DETECTION) || !mmc_card_is_removable(host->mmc))
        return;

    if (enable)
    {
        present = rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE) & RT_SDHCI_CARD_PRESENT;

        host->ier |= present ? RT_SDHCI_INT_CARD_REMOVE : RT_SDHCI_INT_CARD_INSERT;
    }
    else
    {
        host->ier &= ~(RT_SDHCI_INT_CARD_REMOVE | RT_SDHCI_INT_CARD_INSERT);
    }

    rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
}

static void sdhci_enable_card_detection(struct rt_sdhci_host *host)
{
    sdhci_set_card_detection(host, RT_TRUE);
}

/********************************************************* */
/*                     reset                               */
/********************************************************* */
enum sdhci_reset_reason
{
    RT_SDHCI_RESET_FOR_INIT,
    RT_SDHCI_RESET_FOR_REQUEST_ERROR,
    RT_SDHCI_RESET_FOR_REQUEST_ERROR_DATA_ONLY,
    RT_SDHCI_RESET_FOR_TUNING_ABORT,
    RT_SDHCI_RESET_FOR_CARD_REMOVED,
    RT_SDHCI_RESET_FOR_CQE_RECOVERY,
};

static rt_bool_t sdhci_needs_reset(struct rt_sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    return (!(host->flags & RT_SDHCI_DEVICE_DEAD) && ((mrq->cmd && mrq->cmd->err) || (mrq->sbc && mrq->sbc->err) || (mrq->data && mrq->data->stop && mrq->data->stop->err) || (host->quirks & RT_SDHCI_QUIRK_RESET_AFTER_REQUEST)));
}

static rt_bool_t sdhci_do_reset(struct rt_sdhci_host *host, rt_uint8_t mask)
{
    if (host->quirks & RT_SDHCI_QUIRK_NO_CARD_NO_RESET)
    {
        struct rt_mmc_host *mmc = host->mmc;

        if (!mmc->ops->get_cd(mmc))
            return RT_FALSE;
    }
    if (host->ops->reset)
    {
        host->ops->reset(host, mask);
    }
    return RT_TRUE;
}

static void sdhci_reset_for_reason(struct rt_sdhci_host *host, enum sdhci_reset_reason reason)
{
    if (host->quirks2 & RT_SDHCI_QUIRK2_ISSUE_CMD_DAT_RESET_TOGETHER)
    {
        sdhci_do_reset(host, RT_SDHCI_RESET_CMD | RT_SDHCI_RESET_DATA);
        return;
    }

    switch (reason)
    {
    case RT_SDHCI_RESET_FOR_INIT:
        sdhci_do_reset(host, RT_SDHCI_RESET_CMD | RT_SDHCI_RESET_DATA);
        break;
    case RT_SDHCI_RESET_FOR_REQUEST_ERROR:
    case RT_SDHCI_RESET_FOR_TUNING_ABORT:
    case RT_SDHCI_RESET_FOR_CARD_REMOVED:
    case RT_SDHCI_RESET_FOR_CQE_RECOVERY:
        sdhci_do_reset(host, RT_SDHCI_RESET_CMD);
        sdhci_do_reset(host, RT_SDHCI_RESET_DATA);
        break;
    case RT_SDHCI_RESET_FOR_REQUEST_ERROR_DATA_ONLY:
        sdhci_do_reset(host, RT_SDHCI_RESET_DATA);
        break;
    }
}

#define sdhci_reset_for(h, r) sdhci_reset_for_reason((h), RT_SDHCI_RESET_FOR_##r)

static void sdhci_reset_for_all(struct rt_sdhci_host *host)
{
    if (sdhci_do_reset(host, RT_SDHCI_RESET_ALL))
    {
        if (host->flags & (RT_SDHCI_USE_SDMA))
        {
            if (host->ops->enable_dma)
                host->ops->enable_dma(host);
        }
        host->preset_enabled = RT_FALSE;
    }
}


static void sdhci_runtime_pm_bus_on(struct rt_sdhci_host *host)
{
    if (host->bus_on)
        return;
    host->bus_on = RT_TRUE;
}

static void sdhci_runtime_pm_bus_off(struct rt_sdhci_host *host)
{
    if (!host->bus_on)
        return;
    host->bus_on = RT_FALSE;
}

void rt_sdhci_reset(struct rt_sdhci_host *host, rt_uint8_t mask)
{
    ssize_t timeout;

    rt_sdhci_writeb(host, mask, RT_SDHCI_SOFTWARE_RESET);

    if (mask & RT_SDHCI_RESET_ALL)
    {
        host->clock = 0;
        if (host->quirks2 & RT_SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
            sdhci_runtime_pm_bus_off(host);
    }

    timeout = rt_tick_from_millisecond(150);
    while (1)
    {
        timeout = timeout - rt_tick_get();


        if (!(rt_sdhci_readb(host, RT_SDHCI_SOFTWARE_RESET) & mask))
            break;
        if (timeout < 0)
        {
            rt_kprintf("%s: Reset 0x%x never completed.\n",
                       mmc_hostname(host->mmc), (int)mask);
            rt_read_reg_debug(host);
            return;
        }
        rt_hw_us_delay(10);
    }
}

/********************************************************* */
/*                      data                               */
/********************************************************* */
static rt_ubase_t sdhci_sdma_address(struct rt_sdhci_host *host)
{
    return (rt_ubase_t)rt_kmem_v2p(host->data->buf);
}

static void sdhci_set_adma_addr(struct rt_sdhci_host *host, rt_uint32_t addr)
{
    rt_sdhci_writel(host, lower_32_bits(addr), RT_SDHCI_ADMA_ADDRESS);
    if (host->flags & RT_SDHCI_USE_64_BIT_DMA)
        rt_sdhci_writel(host, upper_32_bits(addr), RT_SDHCI_ADMA_ADDRESS_HI);
}

static void sdhci_set_sdma_addr(struct rt_sdhci_host *host, rt_uint32_t addr)
{
    if (host->v4_mode)
        sdhci_set_adma_addr(host, addr);
    else
        rt_sdhci_writel(host, addr, RT_SDHCI_DMA_ADDRESS);
}

static void sdhci_config_dma(struct rt_sdhci_host *host)
{
    rt_uint8_t  ctrl;
    rt_uint16_t ctrl2;

    if (host->version < RT_SDHCI_SPEC_200)
        return;

    ctrl = rt_sdhci_readb(host, RT_SDHCI_HOST_CONTROL);

    ctrl &= ~RT_SDHCI_CTRL_DMA_MASK;
    if (!(host->flags & RT_SDHCI_REQ_USE_DMA))
        goto out;

    /* Note if DMA Select is zero then SDMA is selected */
    if (host->flags & RT_SDHCI_USE_64_BIT_DMA)
    {

        if (host->v4_mode)
        {
            ctrl2  = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
            ctrl2 |= RT_SDHCI_CTRL_64BIT_ADDR;
            rt_sdhci_writew(host, ctrl2, RT_SDHCI_HOST_CONTROL2);
        }
    }

out:
    rt_sdhci_writeb(host, ctrl, RT_SDHCI_HOST_CONTROL);
}

static inline void sdhci_set_block_info(struct rt_sdhci_host    *host,
                                        struct rt_mmcsd_data *data)
{
    int boundary;
    size_t total_size = data->blks * data->blksize;

    if (total_size <= 512)
        boundary = 0;  /* 4k bytes*/
    else if (total_size <= 1024)
        boundary = 1;  /* 8 KB*/
    else if (total_size <= 2048)
        boundary = 2;  /* 16 KB*/
    else if (total_size <= 4096)
        boundary = 3;  /* 32 KB*/
    else if (total_size <= 8192)
        boundary = 4;  /* 64 KB*/
    else if (total_size <= 16384)
        boundary = 5;  /* 128 KB*/
    else if (total_size <= 32768)
        boundary = 6;  /* 256 KB*/
    else
        boundary = 7;  /* 512 KB*/
    rt_sdhci_writew(host,
                 RT_SDHCI_MAKE_BLKSZ(boundary, data->blksize),
                 RT_SDHCI_BLOCK_SIZE);

    if (host->version >= RT_SDHCI_SPEC_410 && host->v4_mode && (host->quirks2 & RT_SDHCI_QUIRK2_USE_32BIT_BLK_CNT))
    {
        if (rt_sdhci_readw(host, RT_SDHCI_BLOCK_COUNT))
            rt_sdhci_writew(host, 0, RT_SDHCI_BLOCK_COUNT);
        rt_sdhci_writew(host, data->blks, RT_SDHCI_32BIT_BLK_CNT);
    }
    else
    {
        rt_sdhci_writew(host, data->blks, RT_SDHCI_BLOCK_COUNT);
    }
}

static void sdhci_set_transfer_irqs(struct rt_sdhci_host *host)
{
    rt_uint32_t pio_irqs = RT_SDHCI_INT_DATA_AVAIL | RT_SDHCI_INT_SPACE_AVAIL;
    rt_uint32_t dma_irqs = RT_SDHCI_INT_DMA_END;

    if (host->flags & RT_SDHCI_REQ_USE_DMA)
        host->ier = (host->ier & ~pio_irqs) | dma_irqs;
    else
        host->ier = (host->ier & ~dma_irqs) | pio_irqs;

    if (host->flags & (RT_SDHCI_AUTO_CMD23 | RT_SDHCI_AUTO_CMD12))
        host->ier |= RT_SDHCI_INT_AUTO_CMD_ERR;
    else
        host->ier &= ~RT_SDHCI_INT_AUTO_CMD_ERR;
    rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
}

static void sdhci_prepare_data(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    struct rt_mmcsd_data *data = cmd->data;

    LOG_D(data->blksize * data->blks > 524288);
    LOG_D(data->blksize > host->mmc->max_blk_size);
    LOG_D(data->blks > 65535);

    host->data               = data;
    host->data_early         = 0;
    host->data->bytes_xfered = 0;

    if (host->flags & RT_SDHCI_USE_SDMA)
    {
        unsigned int length_mask, offset_mask;

        host->flags |= RT_SDHCI_REQ_USE_DMA;

        length_mask = 0;
        offset_mask = 0;
        if (host->quirks & RT_SDHCI_QUIRK_32BIT_DMA_SIZE)
            length_mask = 3;
        if (host->quirks & RT_SDHCI_QUIRK_32BIT_DMA_ADDR)
            offset_mask = 3;

        if ((data->blks * data->blksize) & length_mask)
        {
            host->flags &= ~RT_SDHCI_REQ_USE_DMA;
        }
        else if ((rt_ubase_t)rt_kmem_v2p(data->buf) & offset_mask)
        {
            host->flags &= ~RT_SDHCI_REQ_USE_DMA;
        }
    }

    sdhci_config_dma(host);

    if (host->flags & RT_SDHCI_REQ_USE_DMA)
    {
        if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE)
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
        else
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data->buf, data->blks * data->blksize);

        sdhci_set_sdma_addr(host, sdhci_sdma_address(host));
    }

    if (!(host->flags & RT_SDHCI_REQ_USE_DMA))
    {
        host->blocks = data->blks;
    }

    sdhci_set_transfer_irqs(host);

    sdhci_set_block_info(host, data);
}

static void sdhci_set_mrq_done(struct rt_sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    int i;

    for (i = 0; i < RT_SDHCI_MAX_MRQS; i++)
    {
        if (host->mrqs_done[i] == mrq)
        {
            LOG_D(1);
            return;
        }
    }

    for (i = 0; i < RT_SDHCI_MAX_MRQS; i++)
    {
        if (!host->mrqs_done[i])
        {
            host->mrqs_done[i] = mrq;
            break;
        }
    }

    LOG_D(i >= RT_SDHCI_MAX_MRQS);
}

static inline rt_bool_t sdhci_defer_done(struct rt_sdhci_host   *host,
                                         struct rt_mmcsd_req *mrq)
{
    struct rt_mmcsd_data *data = mrq->data;

    return host->pending_reset || host->always_defer_done || ((host->flags & RT_SDHCI_REQ_USE_DMA) && data && data->host_cookie == COOKIE_MAPPED);
}


/********************************************************* */
/*                        pio                              */
/********************************************************* */

static void rt_sdhci_read_block_pio(struct rt_sdhci_host *host,void **buf)
{
    rt_uint32_t scratch;
    size_t      len;

    rt_uint32_t blksize = host->data->blksize;
    while (blksize)
    {
        len = min(4U, blksize);

        scratch = rt_sdhci_readl(host, RT_SDHCI_BUFFER);
        rt_memcpy(*buf, &scratch, len);

        *buf     += len;
        blksize -= len;
    }
}

static void rt_sdhci_write_block_pio(struct rt_sdhci_host *host,void **buf)
{
    size_t      blksize, len;
    rt_uint32_t scratch;
    LOG_D("PIO writing\n");

    blksize   = host->data->blksize;
    scratch   = 0;

    while (blksize)
    {
        len = min(4U, blksize);
        rt_memcpy(&scratch, *buf, len);
        *buf     += len;
        blksize -= len;
        rt_sdhci_writel(host, scratch, RT_SDHCI_BUFFER);
    }
}

static void sdhci_transfer_pio(struct rt_sdhci_host *host)
{
    rt_uint32_t mask;

    if (host->blocks == 0)
        return;

    if (host->data->flags & DATA_DIR_READ)
        mask = RT_SDHCI_DATA_AVAILABLE;
    else
        mask = RT_SDHCI_SPACE_AVAILABLE;

    if ((host->quirks & RT_SDHCI_QUIRK_BROKEN_SMALL_PIO) && (host->data->blks == 1))
    {
        mask = ~0;
    }
    void *buf = (void *)host->data->buf;
    while (rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE) & mask)
    {
        if (host->quirks & RT_SDHCI_QUIRK_PIO_NEEDS_DELAY)
            rt_hw_us_delay(100);

        if (host->data->flags & DATA_DIR_READ)
            rt_sdhci_read_block_pio(host,&buf);
        else
            rt_sdhci_write_block_pio(host,&buf);

        host->data->blks--;
        if (host->data->blks == 0)
            break;
    }
}

/********************************************************* */
/*                   config                                */
/********************************************************* */


static rt_bool_t sdhci_timing_has_preset(unsigned char timing)
{
    switch (timing)
    {
    case MMC_TIMING_UHS_SDR12:
    case MMC_TIMING_UHS_SDR25:
    case MMC_TIMING_UHS_SDR50:
    case MMC_TIMING_UHS_SDR104:
    case MMC_TIMING_UHS_DDR50:
    case MMC_TIMING_MMC_DDR52:
        return RT_TRUE;
    }
    return RT_FALSE;
}

static rt_bool_t sdhci_preset_needed(struct rt_sdhci_host *host, unsigned char timing)
{
    return !(host->quirks2 & RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN) && sdhci_timing_has_preset(timing);
}

static rt_bool_t sdhci_presetable_values_change(struct rt_sdhci_host *host, struct rt_mmcsd_io_cfg *ios)
{
    return !host->preset_enabled && (sdhci_preset_needed(host, ios->timing) || host->drv_type != ios->drv_type);
}


static void sdhci_preset_value_enable(struct rt_sdhci_host *host, rt_bool_t enable)
{
    if (host->version < RT_SDHCI_SPEC_300)
        return;

    if (host->preset_enabled != enable)
    {
        rt_uint16_t ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);

        if (enable)
            ctrl |= RT_SDHCI_CTRL_PRESET_VAL_ENABLE;
        else
            ctrl &= ~RT_SDHCI_CTRL_PRESET_VAL_ENABLE;

        rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);

        if (enable)
            host->flags |= RT_SDHCI_PV_ENABLED;
        else
            host->flags &= ~RT_SDHCI_PV_ENABLED;

        host->preset_enabled = enable;
    }
}

static void sdhci_set_power_reg(struct rt_sdhci_host *host, unsigned char mode,
                                unsigned short vdd)
{
    struct rt_mmc_host *mmc = host->mmc;

    mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);

    if (mode != MMC_POWER_OFF)
        rt_sdhci_writeb(host, RT_SDHCI_POWER_ON, RT_SDHCI_POWER_CONTROL);
    else
        rt_sdhci_writeb(host, 0, RT_SDHCI_POWER_CONTROL);
}

void rt_sdhci_set_power_with_noreg(struct rt_sdhci_host *host, unsigned char mode,
                           unsigned short vdd)
{
    rt_uint8_t pwr = 0;

    if (mode != MMC_POWER_OFF)
    {
        switch (1 << vdd)
        {
        case MMC_VDD_165_195:
        case MMC_VDD_20_21:
            pwr = RT_SDHCI_POWER_180;
            break;
        case MMC_VDD_29_30:
        case MMC_VDD_30_31:
            pwr = RT_SDHCI_POWER_300;
            break;
        case MMC_VDD_32_33:
        case MMC_VDD_33_34:
        case MMC_VDD_34_35:
        case MMC_VDD_35_36:
            pwr = RT_SDHCI_POWER_330;
            break;
        default:
            break;
        }
    }

    if (host->pwr == pwr)
        return;

    host->pwr = pwr;

    if (pwr == 0)
    {
        rt_sdhci_writeb(host, 0, RT_SDHCI_POWER_CONTROL);
        if (host->quirks2 & RT_SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
            sdhci_runtime_pm_bus_off(host);
    }
    else
    {
        if (!(host->quirks & RT_SDHCI_QUIRK_SINGLE_POWER_WRITE))
            rt_sdhci_writeb(host, 0, RT_SDHCI_POWER_CONTROL);

        if (host->quirks & RT_SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER)
            rt_sdhci_writeb(host, pwr, RT_SDHCI_POWER_CONTROL);

        pwr |= RT_SDHCI_POWER_ON;

        rt_sdhci_writeb(host, pwr, RT_SDHCI_POWER_CONTROL);

        if (host->quirks2 & RT_SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
            sdhci_runtime_pm_bus_on(host);

        if (host->quirks & RT_SDHCI_QUIRK_DELAY_AFTER_POWER)
            rt_thread_mdelay(10);
    }
}

void rt_sdhci_set_power(struct rt_sdhci_host *host, unsigned char mode,
                     unsigned short vdd)
{
    if (!host->mmc->supply.vmmc)
        rt_sdhci_set_power_with_noreg(host, mode, vdd);
    else
        sdhci_set_power_reg(host, mode, vdd);
}


int rt_sdhci_start_signal_voltage_switch(struct rt_mmc_host        *mmc,
                                      struct rt_mmcsd_io_cfg *ios)
{
    struct rt_sdhci_host *host = mmc_priv(mmc);
    rt_uint16_t        ctrl;
    int                ret;

    if (host->version < RT_SDHCI_SPEC_300)
        return 0;

    ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);

    switch (ios->signal_voltage)
    {
    case MMC_SIGNAL_VOLTAGE_330:
        if (!(host->flags & RT_SDHCI_SIGNALING_330))
            return -EINVAL;
        ctrl &= ~RT_SDHCI_CTRL_VDD_180;
        rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);

        if (!mmc->supply.vqmmc)
        {
            ret = rt_mmc_regulator_set_vqmmc(mmc, ios);
            if (ret < 0)
            {
                return -EIO;
            }
        }
        rt_thread_mdelay(5);

        ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
        if (!(ctrl & RT_SDHCI_CTRL_VDD_180))
            return 0;
        return -EAGAIN;
    case MMC_SIGNAL_VOLTAGE_180:
        if (!(host->flags & RT_SDHCI_SIGNALING_180))
            return -EINVAL;
        if (!mmc->supply.vqmmc)
        {
            ret = rt_mmc_regulator_set_vqmmc(mmc, ios);
            if (ret < 0)
            {
                LOG_D("%s: Switching to 1.8V signalling voltage failed\n",
                      mmc_hostname(mmc));
                return -EIO;
            }
        }

        ctrl |= RT_SDHCI_CTRL_VDD_180;
        rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);

        if (host->ops->voltage_switch)
            host->ops->voltage_switch(host);

        ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
        if (ctrl & RT_SDHCI_CTRL_VDD_180)
            return 0;

        LOG_D("%s: 1.8V regulator output did not become stable\n",
              mmc_hostname(mmc));

        return -EAGAIN;
    case MMC_SIGNAL_VOLTAGE_120:
        if (!(host->flags & RT_SDHCI_SIGNALING_120))
            return -EINVAL;
        if (!mmc->supply.vqmmc)
        {
            ret = rt_mmc_regulator_set_vqmmc(mmc, ios);
            if (ret < 0)
            {
                LOG_D("%s: Switching to 1.2V signalling voltage failed\n",
                      mmc_hostname(mmc));
                return -EIO;
            }
        }
        return 0;
    default:
        return 0;
    }
}


static int sdhci_get_cd(struct rt_mmc_host *mmc)
{
    struct rt_sdhci_host *host    = mmc_priv(mmc);
    int                gpio_cd = rt_mmc_gpio_get_cd(mmc);

    if (host->flags & RT_SDHCI_DEVICE_DEAD)
        return 0;

    if (!mmc_card_is_removable(mmc))
        return 1;

    if (gpio_cd >= 0)
        return !!gpio_cd;

    if (host->quirks & RT_SDHCI_QUIRK_BROKEN_CARD_DETECTION)
        return 1;

    return !!(rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE) & RT_SDHCI_CARD_PRESENT);
}

static int sdhci_check_ro(struct rt_sdhci_host *host)
{
    int       is_readonly;
    rt_base_t flags;
    flags = rt_spin_lock_irqsave(&host->lock);

    if (host->flags & RT_SDHCI_DEVICE_DEAD)
        is_readonly = 0;
    else if (host->ops->get_ro)
        is_readonly = host->ops->get_ro(host);
    else if (rt_mmc_can_gpio_ro(host->mmc))
        is_readonly = rt_mmc_gpio_get_ro(host->mmc);
    else
        is_readonly = !(rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE)
                        & RT_SDHCI_WRITE_PROTECT);

    rt_spin_unlock_irqrestore(&host->lock, flags);

    return host->quirks & RT_SDHCI_QUIRK_INVERTED_WRITE_PROTECT ? !is_readonly : is_readonly;
}

#define SAMPLE_COUNT 5
static int rt_sdhci_ro_get(struct rt_mmc_host *mmc)
{
    struct rt_sdhci_host *host = mmc_priv(mmc);
    int                i, ro_count;

    if (!(host->quirks & RT_SDHCI_QUIRK_UNSTABLE_RO_DETECT))
        return sdhci_check_ro(host);

    ro_count = 0;
    for (i = 0; i < SAMPLE_COUNT; i++)
    {
        if (sdhci_check_ro(host))
        {
            if (++ro_count > SAMPLE_COUNT / 2)
                return 1;
        }
        rt_thread_mdelay(30);
    }
    return 0;
}

static void rt_sdhci_enable_io_irq_nolock(struct rt_sdhci_host *host, int enable)
{
    if (!(host->flags & RT_SDHCI_DEVICE_DEAD))
    {
        if (enable)
            host->ier |= RT_SDHCI_INT_CARD_INT;
        else
            host->ier &= ~RT_SDHCI_INT_CARD_INT;

        rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
        rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
    }
}

static void sdhci_ack_sdio_irq(struct rt_mmc_host *mmc)
{
    rt_base_t          flags;
    struct rt_sdhci_host *host = mmc_priv(mmc);
    flags                   = rt_spin_lock_irqsave(&host->lock);
    rt_sdhci_enable_io_irq_nolock(host, RT_TRUE);
    rt_spin_unlock_irqrestore(&host->lock, flags);
}

static void sdhci_del_timer(struct rt_sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    if (sdhci_data_line_cmd(mrq->cmd))
        rt_timer_stop(&host->data_timer);
    else
        rt_timer_stop(&host->timer);
}

static unsigned int sdhci_target_timeout(struct rt_sdhci_host    *host,
                                         struct rt_mmcsd_cmd  *cmd,
                                         struct rt_mmcsd_data *data)
{
    unsigned int target_timeout;

    if (!data)
    {
        target_timeout = cmd->busy_timeout * 1000;
    }
    else
    {
        target_timeout = DIV_ROUND_UP(data->timeout_ns, 1000);
        if (host->clock && data->timeout_clks)
        {
            rt_uint32_t val;

            val = 1000000ULL * data->timeout_clks;
            if (do_div(val, host->clock))
                target_timeout++;
            target_timeout += val;
        }
    }

    return target_timeout;
}

static rt_uint8_t sdhci_calc_timeout(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd,
                                     rt_bool_t *too_big)
{
    rt_uint8_t            count;
    struct rt_mmcsd_data *data;
    unsigned              target_timeout, current_timeout;

    *too_big = RT_FALSE;

    if (host->quirks & RT_SDHCI_QUIRK_BROKEN_TIMEOUT_VAL)
        return host->max_timeout_count;

    if (cmd == NULL)
        return host->max_timeout_count;

    data = cmd->data;
    if (!data && !cmd->busy_timeout)
        return host->max_timeout_count;

    target_timeout = sdhci_target_timeout(host, cmd, data);

    count           = 0;
    current_timeout = (1 << 13) * 1000 / host->timeout_clk;
    while (current_timeout < target_timeout)
    {
        count++;
        current_timeout <<= 1;
        if (count > host->max_timeout_count)
        {
            if (!(host->quirks2 & RT_SDHCI_QUIRK2_DISABLE_HW_TIMEOUT))
                LOG_D("Too large timeout 0x%x requested for CMD%d!\n",
                      count, cmd->cmd_code);
            count    = host->max_timeout_count;
            *too_big = RT_TRUE;
            break;
        }
    }

    return count;
}

static void sdhci_calc_sw_timeout(struct rt_sdhci_host   *host,
                                  struct rt_mmcsd_cmd *cmd)
{
    struct rt_mmcsd_data   *data      = cmd->data;
    struct rt_mmc_host        *mmc       = host->mmc;
    struct rt_mmcsd_io_cfg *ios       = &mmc->ios;
    unsigned char           bus_width = 1 << ios->bus_width;
    unsigned int            blksz;
    unsigned int            freq;
    rt_uint64_t             target_timeout;
    rt_uint64_t             transfer_time;

    target_timeout  = sdhci_target_timeout(host, cmd, data);
    target_timeout *= 1000L;

    if (data)
    {
        blksz         = data->blksize;
        freq          = mmc->actual_clock ?: host->clock;
        transfer_time = (rt_uint64_t)blksz * 1000000000L * (8 / bus_width);
        do_div(transfer_time, freq);
        transfer_time = transfer_time * 2;
        host->data_timeout = data->blks * target_timeout + transfer_time;
    }
    else
    {
        host->data_timeout = target_timeout;
    }

    if (host->data_timeout)
        host->data_timeout += MMC_CMD_TRANSFER_TIME;
}


void rt_sdhci_timeout_set(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    rt_bool_t  too_big = RT_FALSE;
    rt_uint8_t count   = sdhci_calc_timeout(host, cmd, &too_big);

    if (too_big && host->quirks2 & RT_SDHCI_QUIRK2_DISABLE_HW_TIMEOUT)
    {
        sdhci_calc_sw_timeout(host, cmd);
        rt_sdhci_data_irq_timeout(host, RT_FALSE);
    }
    else if (!(host->ier & RT_SDHCI_INT_DATA_TIMEOUT))
    {
        rt_sdhci_data_irq_timeout(host, RT_FALSE);
    }

    rt_sdhci_writeb(host, count, RT_SDHCI_TIMEOUT_CONTROL);
}

static void sdhci_set_timeout(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    if (host->ops->set_timeout)
        host->ops->set_timeout(host, cmd);
    else
        rt_sdhci_timeout_set(host, cmd);
}

static void sdhci_start_timer(struct rt_sdhci_host *host, struct rt_mmcsd_req *mrq,
                            unsigned long timeout)
{
    if (sdhci_data_line_cmd(mrq->cmd))
    {
        rt_tick_t tick = rt_tick_get();

        if (timeout < tick)
        {
            timeout = tick;
        }
        tick = timeout - tick;

        rt_timer_stop(&host->data_timer);
        rt_timer_control(&host->data_timer, RT_TIMER_CTRL_SET_TIME, &tick);
        rt_timer_start(&host->data_timer);
    }
    else
    {
        rt_tick_t tick = rt_tick_get();

        if (timeout < tick)
        {
            timeout = tick;
        }
        tick = timeout - tick;

        rt_timer_stop(&host->timer);
        rt_timer_control(&host->timer, RT_TIMER_CTRL_SET_TIME, &tick);
        rt_timer_start(&host->timer);
    }
}

static void __sdhci_finish_mrq(struct rt_sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    if (host->cmd && host->cmd->mrq == mrq)
        host->cmd = NULL;

    if (host->data_cmd && host->data_cmd->mrq == mrq)
        host->data_cmd = NULL;

    if (host->deferred_cmd && host->deferred_cmd->mrq == mrq)
        host->deferred_cmd = NULL;

    if (host->data && host->data->mrq == mrq)
        host->data = NULL;

    if (sdhci_needs_reset(host, mrq))
        host->pending_reset = RT_TRUE;

    sdhci_set_mrq_done(host, mrq);

    sdhci_del_timer(host, mrq);
}

static void sdhci_finish_mrq(struct rt_sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    __sdhci_finish_mrq(host, mrq);

    rt_workqueue_submit_work(host->complete_wq, &host->complete_work, 0);
}

static void sdhci_error_out_mrqs(struct rt_sdhci_host *host, int err)
{
    if (host->data_cmd)
    {
        host->data_cmd->err = err;
        sdhci_finish_mrq(host, host->data_cmd->mrq);
    }

    if (host->cmd)
    {
        host->cmd->err = err;
        sdhci_finish_mrq(host, host->cmd->mrq);
    }
}

static void sdhci_card_event(struct rt_mmc_host *mmc)
{
    struct rt_sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        flags;
    int                present;

    if (host->ops->card_event)
        host->ops->card_event(host);

    present = mmc->ops->get_cd(mmc);

    flags = rt_spin_lock_irqsave(&host->lock);

    if (sdhci_has_requests(host) && !present)
    {
        rt_kprintf("%s: Card removed during transfer!\n",
                   mmc_hostname(mmc));
        rt_kprintf("%s: Resetting controller.\n",
                   mmc_hostname(mmc));

        sdhci_do_reset(host, RT_SDHCI_RESET_CMD);
        sdhci_do_reset(host, RT_SDHCI_RESET_DATA);
        sdhci_error_out_mrqs(host, -ENOMEDIUM);
    }

    rt_spin_unlock_irqrestore(&host->lock, flags);
}

static int sdhci_card_busy(struct rt_mmc_host *mmc)
{
    struct rt_sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        present_state;

    present_state = rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE);

    return !(present_state & RT_SDHCI_DATA_0_LVL_MASK);
}


static int sdhci_prepare_hs400_tuning(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    struct rt_sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        flags;

    flags        = rt_spin_lock_irqsave(&host->lock);
    host->flags |= RT_SDHCI_HS400_TUNING;
    rt_spin_unlock_irqrestore(&host->lock, flags);

    return 0;
}


static void sdhci_set_transfer_mode(struct rt_sdhci_host   *host,
                                    struct rt_mmcsd_cmd *cmd)
{
    rt_uint16_t           mode = 0;
    struct rt_mmcsd_data *data = cmd->data;

    if (data == NULL)
    {
        if (host->quirks2 & RT_SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD)
        {
            if (!mmc_op_tuning(cmd->cmd_code))
                rt_sdhci_writew(host, 0x0, RT_SDHCI_TRANSFER_MODE);
        }
        else
        {
            mode = rt_sdhci_readw(host, RT_SDHCI_TRANSFER_MODE);
            rt_sdhci_writew(host, mode & ~(RT_SDHCI_TRNS_AUTO_CMD12 | RT_SDHCI_TRNS_AUTO_CMD23), RT_SDHCI_TRANSFER_MODE);
        }
        return;
    }

    if (!(host->quirks2 & RT_SDHCI_QUIRK2_SUPPORT_SINGLE))
        mode = RT_SDHCI_TRNS_BLK_CNT_EN;

    if (mmc_op_multi(cmd->cmd_code) || data->blks > 1)
    {
        mode = RT_SDHCI_TRNS_BLK_CNT_EN | RT_SDHCI_TRNS_MULTI;
        sdhci_auto_cmd_select(host, cmd, &mode);
        if (sdhci_auto_cmd23(host, cmd->mrq))
            rt_sdhci_writel(host, cmd->mrq->sbc->arg, RT_SDHCI_ARGUMENT2);
    }

    if (data->flags & DATA_DIR_READ)
        mode |= RT_SDHCI_TRNS_READ;
    if (host->flags & RT_SDHCI_REQ_USE_DMA)
        mode |= RT_SDHCI_TRNS_DMA;

    rt_sdhci_writew(host, mode, RT_SDHCI_TRANSFER_MODE);
}

static rt_bool_t sdhci_send_command(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    int           flags;
    rt_uint32_t   mask;
    unsigned long timeout;
    cmd->err = 0;

    if ((host->quirks2 & RT_SDHCI_QUIRK2_STOP_WITH_TC) && cmd->cmd_code == MMC_STOP_TRANSMISSION)
        cmd->flags |= MMC_RSP_BUSY;

    mask = RT_SDHCI_CMD_INHIBIT;
    if (sdhci_data_line_cmd(cmd))
        mask |= RT_SDHCI_DATA_INHIBIT;

    if (cmd->mrq->data && (cmd == cmd->mrq->data->stop))
        mask &= ~RT_SDHCI_DATA_INHIBIT;

    if (rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE) & mask)
        return RT_FALSE;

    host->cmd          = cmd;
    host->data_timeout = 0;
    if (sdhci_data_line_cmd(cmd))
    {
        host->data_cmd = cmd;
        sdhci_set_timeout(host, cmd);
    }

    if (cmd->data)
    {
        sdhci_prepare_data(host, cmd);
    }
    rt_sdhci_writel(host, cmd->arg, RT_SDHCI_ARGUMENT);

    sdhci_set_transfer_mode(host, cmd);

    if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY))
    {
        cmd->flags &= ~MMC_RSP_BUSY;
    }

    if (!(cmd->flags & MMC_RSP_PRESENT))
        flags = RT_SDHCI_CMD_RESP_NONE;
    else if (cmd->flags & MMC_RSP_136)
        flags = RT_SDHCI_CMD_RESP_LONG;
    else if (cmd->flags & MMC_RSP_BUSY)
        flags = RT_SDHCI_CMD_RESP_SHORT_BUSY;
    else
        flags = RT_SDHCI_CMD_RESP_SHORT;

    if (cmd->flags & MMC_RSP_CRC)
        flags |= RT_SDHCI_CMD_CRC;
    if (cmd->flags & MMC_RSP_OPCODE)
        flags |= RT_SDHCI_CMD_INDEX;

    if (cmd->data || mmc_op_tuning(cmd->cmd_code))
        flags |= RT_SDHCI_CMD_DATA;

    timeout = rt_tick_get();
    if (host->data_timeout)
        timeout += rt_tick_from_millisecond(host->data_timeout * 1000);
    else if (!cmd->data && cmd->busy_timeout > 9000)
        timeout += DIV_ROUND_UP(cmd->busy_timeout, 1000) * RT_TICK_PER_SECOND + RT_TICK_PER_SECOND;
    else
        timeout += 10 * RT_TICK_PER_SECOND;
    sdhci_start_timer(host, cmd->mrq, timeout);

    rt_sdhci_writew(host, RT_SDHCI_MAKE_CMD(cmd->cmd_code, flags), RT_SDHCI_COMMAND);
    return RT_TRUE;
}

/********************************************************* */
/*                        dma                              */
/********************************************************* */
static void __sdhci_finish_data(struct rt_sdhci_host *host, rt_bool_t sw_data_timeout)
{
    struct rt_mmcsd_cmd  *data_cmd = host->data_cmd;
    struct rt_mmcsd_data *data     = host->data;

    host->data     = NULL;
    host->data_cmd = NULL;

    if (data->err)
    {
        if (!host->cmd || host->cmd == data_cmd)
            sdhci_reset_for(host, REQUEST_ERROR);
        else
            sdhci_reset_for(host, REQUEST_ERROR_DATA_ONLY);
    }

    if (data->err)
    {
        data->bytes_xfered = 0;
    }
    else
    {
        data->bytes_xfered = data->blksize * data->blks;
    }

    if (data->stop && ((!data->mrq->sbc && !sdhci_auto_cmd12(host, data->mrq)) || data->err))
    {
        if (data->mrq->cap_cmd_during_tfr)
        {
            __sdhci_finish_mrq(host, data->mrq);
        }
        else
        {
            host->cmd = NULL;
            if (!sdhci_send_command(host, data->stop))
            {
                if (sw_data_timeout)
                {
                    data->stop->err = -EIO;
                    __sdhci_finish_mrq(host, data->mrq);
                }
                else
                {
                    host->deferred_cmd = data->stop;
                }
            }
        }
    }
    else
    {
        __sdhci_finish_mrq(host, data->mrq);
    }
}

static void sdhci_finish_data(struct rt_sdhci_host *host)
{
    __sdhci_finish_data(host, RT_FALSE);
}


/********************************************************* */
/*                     irq                                 */
/********************************************************* */
static void sdhci_data_irq(struct rt_sdhci_host *host, rt_uint32_t intmask)
{
    rt_uint32_t command;

    if (intmask & RT_SDHCI_INT_DATA_AVAIL && !host->data)
    {
        command = RT_SDHCI_GET_CMD(rt_sdhci_readw(host, RT_SDHCI_COMMAND));
        if (command == MMC_SEND_TUNING_BLOCK || command == MMC_SEND_TUNING_BLOCK_HS200)
        {
            host->tuning_done = 1;
            rt_wqueue_wakeup(&host->buf_ready_int, 0);
            return;
        }
    }

    if (!host->data)
    {
        struct rt_mmcsd_cmd *data_cmd = host->data_cmd;

        if (data_cmd && (data_cmd->flags & MMC_RSP_BUSY))
        {
            if (intmask & RT_SDHCI_INT_DATA_TIMEOUT)
            {
                host->data_cmd = NULL;
                data_cmd->err  = -ETIMEDOUT;
                __sdhci_finish_mrq(host, data_cmd->mrq);
                return;
            }
            if (intmask & RT_SDHCI_INT_DATA_END)
            {
                host->data_cmd = NULL;

                if (host->cmd == data_cmd)
                    return;

                __sdhci_finish_mrq(host, data_cmd->mrq);
                return;
            }
        }


        if (host->pending_reset)
            return;
        rt_kprintf("%s: Got data interrupt 0x%08x even though no data operation was in progress.\n",
                   mmc_hostname(host->mmc), (unsigned)intmask);
        rt_read_reg_debug(host);

        return;
    }

    if (intmask & RT_SDHCI_INT_DATA_TIMEOUT)
        host->data->err = -ETIMEDOUT;
    else if (intmask & RT_SDHCI_INT_DATA_END_BIT)
        host->data->err = -EILSEQ;
    else if ((intmask & RT_SDHCI_INT_DATA_CRC) && RT_SDHCI_GET_CMD(rt_sdhci_readw(host, RT_SDHCI_COMMAND)) != MMC_BUS_TEST_R)
    {
        host->data->err = -EILSEQ;
    }


    if (host->data->err)
    {
        sdhci_finish_data(host);
    }
    else
    {
        if (intmask & (RT_SDHCI_INT_DATA_AVAIL | RT_SDHCI_INT_SPACE_AVAIL))
            sdhci_transfer_pio(host);

        if (intmask & RT_SDHCI_INT_DMA_END)
        {
            rt_uint32_t dmastart, dmanow;

            dmastart = sdhci_sdma_address(host);
            dmanow   = dmastart + host->data->bytes_xfered;
            dmanow                   = (dmanow & ~((rt_uint32_t)RT_SDHCI_DEFAULT_BOUNDARY_SIZE - 1)) + RT_SDHCI_DEFAULT_BOUNDARY_SIZE;
            host->data->bytes_xfered = dmanow - dmastart;
            LOG_D("DMA base %pad, transferred 0x%06x bytes, next %pad\n",
                  &dmastart, host->data->bytes_xfered, &dmanow);
            sdhci_set_sdma_addr(host, dmanow);
        }

        if (intmask & RT_SDHCI_INT_DATA_END)
        {
            struct rt_mmcsd_data *data = host->data;
            if (data->buf)
            {
                if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE)
                {
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
                } else {
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data->buf, data->blks * data->blksize);
                }
            }
            if (host->cmd == host->data_cmd)
            {
                host->data_early = 1;
            }
            else
            {
                sdhci_finish_data(host);
            }
        }
    }
}

static void rt_sdhci_read_rsp_136(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    int i, reg;

    for (i = 0; i < 4; i++)
    {
        reg          = RT_SDHCI_RESPONSE + (3 - i) * 4;
        cmd->resp[i] = rt_sdhci_readl(host, reg);
    }

    if (host->quirks2 & RT_SDHCI_QUIRK2_RSP_136_HAS_CRC)
        return;

    for (i = 0; i < 4; i++)
    {
        cmd->resp[i] <<= 8;
        if (i != 3)
            cmd->resp[i] |= cmd->resp[i + 1] >> 24;
    }
}

static void sdhci_command_end(struct rt_sdhci_host *host)
{
    struct rt_mmcsd_cmd *cmd = host->cmd;

    host->cmd = NULL;

    if (cmd->flags & MMC_RSP_PRESENT)
    {
        if (cmd->flags & MMC_RSP_136)
        {
            rt_sdhci_read_rsp_136(host, cmd);
        }
        else
        {
            cmd->resp[0] = rt_sdhci_readl(host, RT_SDHCI_RESPONSE);
        }
    }

    if (cmd->flags & MMC_RSP_BUSY)
    {
        if (cmd->data)
        {
            LOG_D("Cannot wait for busy signal when also doing a data transfer");
        }
        else if (!(host->quirks & RT_SDHCI_QUIRK_NO_BUSY_IRQ) && cmd == host->data_cmd)
        {
            return;
        }
    }

    if (cmd == cmd->mrq->sbc)
    {
        if (!sdhci_send_command(host, cmd->mrq->cmd))
        {
            host->deferred_cmd = cmd->mrq->cmd;
        }
    }
    else
    {
        if (host->data && host->data_early)
            sdhci_finish_data(host);

        if (!cmd->data)
            __sdhci_finish_mrq(host, cmd->mrq);
    }
}


static void sdhci_cmd_irq(struct rt_sdhci_host *host, rt_uint32_t intmask, rt_uint32_t *intmask_p)
{
    if (intmask & RT_SDHCI_INT_AUTO_CMD_ERR && host->data_cmd)
    {
        struct rt_mmcsd_req *mrq             = host->data_cmd->mrq;
        rt_uint16_t          auto_cmd_status = rt_sdhci_readw(host, RT_SDHCI_AUTO_CMD_STATUS);
        int                  data_err_bit    = (auto_cmd_status & RT_SDHCI_AUTO_CMD_TIMEOUT) ? RT_SDHCI_INT_DATA_TIMEOUT : RT_SDHCI_INT_DATA_CRC;

        if (!mrq->sbc && (host->flags & RT_SDHCI_AUTO_CMD12))
        {
            *intmask_p |= data_err_bit;
            return;
        }
    }

    if (!host->cmd)
    {
        if (host->pending_reset)
            return;
        rt_kprintf("%s: Got command interrupt 0x%08x even though no command operation was in progress.\n",
                   mmc_hostname(host->mmc), (unsigned)intmask);
        rt_read_reg_debug(host);
        return;
    }
    if (intmask & (RT_SDHCI_INT_TIMEOUT | RT_SDHCI_INT_CRC | RT_SDHCI_INT_END_BIT | RT_SDHCI_INT_INDEX))
    {
        if (intmask & RT_SDHCI_INT_TIMEOUT)
            host->cmd->err = -ETIMEDOUT;
        else
            host->cmd->err = -EILSEQ;

        /* Treat data command CRC error the same as data CRC error */
        if (host->cmd->data && (intmask & (RT_SDHCI_INT_CRC | RT_SDHCI_INT_TIMEOUT)) == RT_SDHCI_INT_CRC)
        {
            host->cmd   = NULL;
            *intmask_p |= RT_SDHCI_INT_DATA_CRC;
            return;
        }

        __sdhci_finish_mrq(host, host->cmd->mrq);
        return;
    }

    if (intmask & RT_SDHCI_INT_AUTO_CMD_ERR)
    {
        struct rt_mmcsd_req *mrq             = host->cmd->mrq;
        rt_uint16_t          auto_cmd_status = rt_sdhci_readw(host, RT_SDHCI_AUTO_CMD_STATUS);
        int                  err             = (auto_cmd_status & RT_SDHCI_AUTO_CMD_TIMEOUT) ? -ETIMEDOUT : -EILSEQ;

        if (mrq->sbc && (host->flags & RT_SDHCI_AUTO_CMD23))
        {
            mrq->sbc->err = err;
            __sdhci_finish_mrq(host, mrq);
            return;
        }
    }

    if (intmask & RT_SDHCI_INT_RESPONSE)
        sdhci_command_end(host);
}

static void sdhci_irq(int irq, void *dev_id)
{
#define IRQ_NONE 0
#define IRQ_WAIT 1
#define IRQ_DONE 2

    struct rt_mmcsd_req* mrqs_done[RT_SDHCI_MAX_MRQS] = { 0 };
    struct rt_sdhci_host   *host                      = dev_id;
    rt_uint32_t          intmask, mask, unexpected = 0;
    int                  max_loops = 16;
    int                  i, result= IRQ_NONE ;
    rt_spin_lock(&host->lock);

    if (host->runtime_suspended)
    {
        rt_spin_unlock(&host->lock);
        return;
    }

    intmask = rt_sdhci_readl(host, RT_SDHCI_INT_STATUS);
    if (!intmask || intmask == 0xffffffff)
    {
        result = IRQ_NONE;
        goto out;
    }

    do {
        LOG_D("IRQ status 0x%08x\n", intmask);

        if (host->ops->irq)
        {
            intmask = host->ops->irq(host, intmask);
            if (!intmask)
                goto cont;
        }

        /* Clear selected interrupts. */
        mask = intmask & (RT_SDHCI_INT_CMD_MASK | RT_SDHCI_INT_DATA_MASK | RT_SDHCI_INT_BUS_POWER);
        rt_sdhci_writel(host, mask, RT_SDHCI_INT_STATUS);

        if (intmask & (RT_SDHCI_INT_CARD_INSERT | RT_SDHCI_INT_CARD_REMOVE))
        {
            rt_uint32_t present = rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE) & RT_SDHCI_CARD_PRESENT;

            host->ier &= ~(RT_SDHCI_INT_CARD_INSERT | RT_SDHCI_INT_CARD_REMOVE);
            host->ier |= present ? RT_SDHCI_INT_CARD_REMOVE : RT_SDHCI_INT_CARD_INSERT;
            rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
            rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);

            rt_sdhci_writel(host, intmask & (RT_SDHCI_INT_CARD_INSERT | RT_SDHCI_INT_CARD_REMOVE), RT_SDHCI_INT_STATUS);

            host->thread_isr |= intmask & (RT_SDHCI_INT_CARD_INSERT | RT_SDHCI_INT_CARD_REMOVE);
            result            = IRQ_WAIT;
        }

        if (intmask & RT_SDHCI_INT_CMD_MASK)
            sdhci_cmd_irq(host, intmask & RT_SDHCI_INT_CMD_MASK, &intmask);

        if (intmask & RT_SDHCI_INT_DATA_MASK)
            sdhci_data_irq(host, intmask & RT_SDHCI_INT_DATA_MASK);

        if (intmask & RT_SDHCI_INT_BUS_POWER)
            rt_kprintf("%s: Card is consuming too much power!\n",
                       mmc_hostname(host->mmc));

        intmask &= ~(RT_SDHCI_INT_CARD_INSERT | RT_SDHCI_INT_CARD_REMOVE | RT_SDHCI_INT_CMD_MASK | RT_SDHCI_INT_DATA_MASK | RT_SDHCI_INT_ERROR | RT_SDHCI_INT_BUS_POWER | RT_SDHCI_INT_RETUNE | RT_SDHCI_INT_CARD_INT);

        if (intmask)
        {
            unexpected |= intmask;
            rt_sdhci_writel(host, intmask, RT_SDHCI_INT_STATUS);
        }
    cont:
        if (result == IRQ_NONE)
            result = IRQ_WAIT;
        intmask = rt_sdhci_readl(host, RT_SDHCI_INT_STATUS);
    } while (intmask && --max_loops);

    for (i = 0; i < RT_SDHCI_MAX_MRQS; i++)
    {
        struct rt_mmcsd_req *mrq = host->mrqs_done[i];

        if (!mrq)
            continue;

        if (sdhci_defer_done(host, mrq))
        {
            result = IRQ_WAIT;
        }
        else
        {
            mrqs_done[i]       = mrq;
            host->mrqs_done[i] = NULL;
        }
    }
out:
    if (host->deferred_cmd)
        result = IRQ_WAIT;

    rt_spin_unlock(&host->lock);

    for (i = 0; i < RT_SDHCI_MAX_MRQS; i++)
    {
        if (!mrqs_done[i])
            continue;

        if (host->ops->request_done)
            host->ops->request_done(host, mrqs_done[i]);
        else
            rt_mmc_request_done(host->mmc, mrqs_done[i]);
    }

    if (unexpected)
    {
        rt_kprintf("%s: Unexpected interrupt 0x%08x.\n",
               mmc_hostname(host->mmc), unexpected);
        rt_read_reg_debug(host);
    }

    if (result == IRQ_WAIT)
    {
        rt_workqueue_submit_work(host->irq_wq, &host->irq_work, 0);
    }
}

static rt_bool_t sdhci_send_command_retry(struct rt_sdhci_host   *host,
                                          struct rt_mmcsd_cmd *cmd,
                                          unsigned long        flags)
{
    struct rt_mmcsd_cmd *deferred_cmd = host->deferred_cmd;
    int                  timeout      = 10; /* Approx. 10 ms */
    rt_bool_t            present;
    while (!sdhci_send_command(host, cmd))
    {
        if (!timeout--)
        {
            rt_kprintf("%s: Controller never released inhibit bit(s).\n",
                       mmc_hostname(host->mmc));
            rt_read_reg_debug(host);
            cmd->err = -EIO;
            return RT_FALSE;
        }

        rt_spin_unlock_irqrestore(&host->lock, flags);

        rt_thread_mdelay(1);

        present = host->mmc->ops->get_cd(host->mmc);

        flags = rt_spin_lock_irqsave(&host->lock);

        if (cmd == deferred_cmd && cmd != host->deferred_cmd)
            return RT_TRUE;

        if (sdhci_present_error(host, cmd, present))
            return RT_FALSE;
    }

    if (cmd == host->deferred_cmd)
        host->deferred_cmd = NULL;

    return RT_TRUE;
}

static rt_bool_t rt_sdhci_start_request_done(struct rt_sdhci_host *host)
{
    rt_base_t            flags;
    struct rt_mmcsd_req *mrq;
    int                  i;

    flags = rt_spin_lock_irqsave(&host->lock);

    for (i = 0; i < RT_SDHCI_MAX_MRQS; i++)
    {
        mrq = host->mrqs_done[i];
        if (mrq)
            break;
    }

    if (!mrq)
    {
        rt_spin_unlock_irqrestore(&host->lock, flags);
        return RT_TRUE;
    }

    if (sdhci_needs_reset(host, mrq))
    {
        if (host->cmd || host->data_cmd)
        {
            rt_spin_unlock_irqrestore(&host->lock, flags);
            return RT_TRUE;
        }

        /* Some controllers need this kick or reset won't work here */
        if (host->quirks & RT_SDHCI_QUIRK_CLOCK_BEFORE_RESET)
            /* This is to force an update */
            host->ops->set_clock(host, host->clock);

        sdhci_reset_for(host, REQUEST_ERROR);

        host->pending_reset = RT_FALSE;
    }

    if (host->flags & RT_SDHCI_REQ_USE_DMA)
    {
        struct rt_mmcsd_data *data = mrq->data;

        if (data && data->host_cookie == COOKIE_MAPPED)
        {
            if (host->bounce_buffer)
            {
                /*
                 * On reads, copy the bounced data into the
                 * sglist
                 */
                if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE)
                {
                    unsigned int length = data->bytes_xfered;

                    if (length > host->bounce_buffer_size)
                    {
                        LOG_E("%s: bounce buffer is %u bytes but DMA claims to have transferred %u bytes\n",
                               mmc_hostname(host->mmc),
                               host->bounce_buffer_size,
                               data->bytes_xfered);
                        /* Cap it down and continue */
                        length = host->bounce_buffer_size;
                    }
                        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
                } else {
                    /* No copying, just switch ownership */
                        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data->buf, data->blks * data->blksize);
                }
            }
            data->host_cookie = COOKIE_UNMAPPED;
        }
        else {
                if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE)
                {
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
                } else {
                    /* No copying, just switch ownership */
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data->buf, data->blks * data->blksize);
                }
        }
    }

    host->mrqs_done[i] = NULL;

    rt_spin_unlock_irqrestore(&host->lock, flags);

    if (host->ops->request_done)
        host->ops->request_done(host, mrq);
    else
        rt_mmc_request_done(host->mmc, mrq);

    return RT_FALSE;
}


static void sdhci_thread_irq(struct rt_work *work, void *work_data)
{
    struct rt_sdhci_host* host = work_data;
    struct rt_mmcsd_cmd *cmd;
    rt_base_t            flags;
    rt_uint32_t          isr;

    while (!rt_sdhci_start_request_done(host));

    flags = rt_spin_lock_irqsave(&host->lock);

    isr              = host->thread_isr;
    host->thread_isr = 0;

    cmd = host->deferred_cmd;
    if (cmd && !sdhci_send_command_retry(host, cmd, flags))
        sdhci_finish_mrq(host, cmd->mrq);

    rt_spin_unlock_irqrestore(&host->lock, flags);

    if (isr & (RT_SDHCI_INT_CARD_INSERT | RT_SDHCI_INT_CARD_REMOVE))
    {
        struct rt_mmc_host *mmc = host->mmc;

        mmc->ops->card_event(mmc);
    }
}


void rt_sdhci_enable_io_irq(struct rt_mmc_host *mmc, int enable)
{
    struct rt_sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        flags;

    flags = rt_spin_lock_irqsave(&host->lock);
    rt_sdhci_enable_io_irq_nolock(host, enable);
    rt_spin_unlock_irqrestore(&host->lock, flags);
}


/********************************************************* */
/*                     request                             */
/********************************************************* */

void rt_sdhci_start_request(struct rt_mmc_host *mmc, struct rt_mmcsd_req *mrq)
{
    struct rt_sdhci_host   *host = mmc_priv(mmc);
    struct rt_mmcsd_cmd *cmd;
    rt_base_t            flags;
    rt_bool_t            present;

    /* Firstly check card presence */
    present = mmc->ops->get_cd(mmc);

    flags = rt_spin_lock_irqsave(&host->lock);

    if (sdhci_present_error(host, mrq->cmd, present))
        goto out_finish;

    cmd = sdhci_manual_cmd23(host, mrq) ? mrq->sbc : mrq->cmd;

    if (!sdhci_send_command_retry(host, cmd, flags))
        goto out_finish;

    rt_spin_unlock_irqrestore(&host->lock, flags);

    return;

out_finish:
    sdhci_finish_mrq(host, mrq);
    rt_spin_unlock_irqrestore(&host->lock, flags);
}


static void sdhci_complete_work(struct rt_work *work, void *work_data)
{
    struct rt_sdhci_host *host = work_data;

    while (!rt_sdhci_start_request_done(host));
}


/********************************************************* */
/*                     timer                               */
/********************************************************* */
static void sdhci_timeout_timer(void *parameter)
{
    struct rt_sdhci_host *host = parameter;
    rt_base_t          flags;

    flags = rt_spin_lock_irqsave(&host->lock);

    if (host->cmd && !sdhci_data_line_cmd(host->cmd))
    {
        rt_kprintf("%s: Timeout waiting for hardware cmd interrupt.\n",
                   mmc_hostname(host->mmc));
        rt_read_reg_debug(host);

        host->cmd->err = -ETIMEDOUT;
        sdhci_finish_mrq(host, host->cmd->mrq);
    }

    rt_spin_unlock_irqrestore(&host->lock, flags);
}

static void sdhci_timeout_data_timer(void *parameter)
{
    struct rt_sdhci_host *host = parameter;
    rt_base_t          flags;

    flags = rt_spin_lock_irqsave(&host->lock);

    if (host->data || host->data_cmd || (host->cmd && sdhci_data_line_cmd(host->cmd)))
    {
        rt_kprintf("%s: Timeout waiting for hardware interrupt.\n",
                   mmc_hostname(host->mmc));
        rt_read_reg_debug(host);

        if (host->data)
        {
            host->data->err = -ETIMEDOUT;
            __sdhci_finish_data(host, RT_TRUE);
            rt_workqueue_submit_work(host->complete_wq, &host->complete_work, 0);
        }
        else if (host->data_cmd)
        {
            host->data_cmd->err = -ETIMEDOUT;
            sdhci_finish_mrq(host, host->data_cmd->mrq);
        }
        else
        {
            host->cmd->err = -ETIMEDOUT;
            sdhci_finish_mrq(host, host->cmd->mrq);
        }
    }

    rt_spin_unlock_irqrestore(&host->lock, flags);
}


/********************************************************* */
/*                     tuning                              */
/********************************************************* */
int rt_sdhci_execute_tuning(struct rt_mmc_host *mmc, rt_uint32_t opcode)
{
    struct rt_sdhci_host *host         = mmc_priv(mmc);
    int                err          = 0;
    unsigned int       tuning_count = 0;
    rt_bool_t          hs400_tuning;

    hs400_tuning = host->flags & RT_SDHCI_HS400_TUNING;

    if (host->tuning_mode == RT_SDHCI_TUNING_MODE_1)
        tuning_count = host->tuning_count;

    switch (host->timing)
    {
    /* HS400 tuning is done in HS200 mode */
    case MMC_TIMING_MMC_HS400:
        err = -EINVAL;
        goto out;

    case MMC_TIMING_MMC_HS200:
        if (hs400_tuning)
            tuning_count = 0;
        break;

    case MMC_TIMING_UHS_SDR104:
    case MMC_TIMING_UHS_DDR50:
        break;

    case MMC_TIMING_UHS_SDR50:
        if (host->flags & RT_SDHCI_SDR50_NEEDS_TUNING)
            break;
        fallthrough;

    default:
        goto out;
    }

    if (host->ops->platform_execute_tuning)
    {
        err = host->ops->platform_execute_tuning(host, opcode);
        goto out;
    }

    mmc->retune_period = tuning_count;

    if (host->tuning_delay < 0)
        host->tuning_delay = opcode == MMC_SEND_TUNING_BLOCK;

    rt_sdhci_start_tuning(host);

    host->tuning_err = __sdhci_execute_tuning(host, opcode);

    rt_sdhci_end_tuning(host);
out:
    host->flags &= ~RT_SDHCI_HS400_TUNING;

    return err;
}

int __sdhci_execute_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode)
{
    int i;

    for (i = 0; i < host->tuning_loop_count; i++)
    {
        rt_uint16_t ctrl;

        rt_sdhci_send_tuning(host, opcode);

        if (!host->tuning_done)
        {
            rt_sdhci_abort_tuning(host, opcode);
            return -ETIMEDOUT;
        }

        if (host->tuning_delay > 0)
            rt_thread_mdelay(host->tuning_delay);

        ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
        if (!(ctrl & RT_SDHCI_CTRL_EXEC_TUNING))
        {
            if (ctrl & RT_SDHCI_CTRL_TUNED_CLK)
                return 0; /* Success! */
            break;
        }
    }

    LOG_D("%s: Tuning failed, falling back to fixed sampling clock\n",
          mmc_hostname(host->mmc));
    rt_sdhci_reset_tuning(host);
    return -EAGAIN;
}

void rt_sdhci_start_tuning(struct rt_sdhci_host *host)
{
    rt_uint16_t ctrl;

    ctrl  = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
    ctrl |= RT_SDHCI_CTRL_EXEC_TUNING;
    if (host->quirks2 & RT_SDHCI_QUIRK2_TUNING_WORK_AROUND)
        ctrl |= RT_SDHCI_CTRL_TUNED_CLK;
    rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);

    rt_sdhci_writel(host, RT_SDHCI_INT_DATA_AVAIL, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, RT_SDHCI_INT_DATA_AVAIL, RT_SDHCI_SIGNAL_ENABLE);
}

void rt_sdhci_end_tuning(struct rt_sdhci_host *host)
{
    rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
}

void rt_sdhci_abort_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode)
{
    rt_sdhci_reset_tuning(host);

    sdhci_reset_for(host, TUNING_ABORT);

    rt_sdhci_end_tuning(host);
}

void rt_sdhci_send_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode)
{
    struct rt_mmc_host    *mmc = host->mmc;
    struct rt_mmcsd_cmd cmd = {};
    struct rt_mmcsd_req mrq = {};
    unsigned long       flags;
    rt_uint32_t         b = host->sdma_boundary;

    flags = rt_spin_lock_irqsave(&host->lock);

    cmd.cmd_code = opcode;
    cmd.flags    = MMC_RSP_R1 | MMC_CMD_ADTC;
    cmd.mrq      = &mrq;

    mrq.cmd = &cmd;

    if (cmd.cmd_code == MMC_SEND_TUNING_BLOCK_HS200 && mmc->ios.bus_width == MMC_BUS_WIDTH_8)
        rt_sdhci_writew(host, RT_SDHCI_MAKE_BLKSZ(b, 128), RT_SDHCI_BLOCK_SIZE);
    else
        rt_sdhci_writew(host, RT_SDHCI_MAKE_BLKSZ(b, 64), RT_SDHCI_BLOCK_SIZE);

    rt_sdhci_writew(host, RT_SDHCI_TRNS_READ, RT_SDHCI_TRANSFER_MODE);

    if (!sdhci_send_command_retry(host, &cmd, flags))
    {
        rt_spin_unlock_irqrestore(&host->lock, flags);
        host->tuning_done = 0;
        return;
    }

    host->cmd = NULL;

    sdhci_del_timer(host, &mrq);

    host->tuning_done = 0;

    rt_spin_unlock_irqrestore(&host->lock, flags);
}

void rt_sdhci_reset_tuning(struct rt_sdhci_host *host)
{
    rt_uint16_t ctrl;

    ctrl  = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
    ctrl &= ~RT_SDHCI_CTRL_TUNED_CLK;
    ctrl &= ~RT_SDHCI_CTRL_EXEC_TUNING;
    rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);
}


/********************************************************* */
/*                     error                               */
/********************************************************* */
static const struct mmc_host_ops rt_sdhci_ops = {
    .request                     = rt_sdhci_start_request,
    .set_ios                     = rt_sdhci_ios_set,
    .get_cd                      = sdhci_get_cd,
    .get_ro                      = rt_sdhci_ro_get,
    .enable_sdio_irq             = rt_sdhci_enable_io_irq,
    .ack_sdio_irq                = sdhci_ack_sdio_irq,
    .start_signal_voltage_switch = rt_sdhci_start_signal_voltage_switch,
    .prepare_hs400_tuning        = sdhci_prepare_hs400_tuning,
    .execute_tuning              = rt_sdhci_execute_tuning,
    .card_event                  = sdhci_card_event,
    .card_busy                   = sdhci_card_busy,
};


void rt_sdhci_uninit_host(struct rt_sdhci_host *host, int dead)
{
    struct rt_mmc_host *mmc = host->mmc;
    unsigned long    flags;

    if (dead)
    {
        flags = rt_spin_lock_irqsave(&host->lock);

        host->flags |= RT_SDHCI_DEVICE_DEAD;

        if (sdhci_has_requests(host))
        {
            rt_kprintf("%s: Controller removed during "
                       " transfer!\n",
                       mmc_hostname(mmc));
            sdhci_error_out_mrqs(host, -ENOMEDIUM);
        }

        rt_spin_unlock_irqrestore(&host->lock, flags);
    }

    sdhci_set_card_detection(host, RT_FALSE);

    rt_mmc_remove_host(mmc);


    if (!dead)
        sdhci_reset_for_all(host);

    rt_sdhci_writel(host, 0, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, 0, RT_SDHCI_SIGNAL_ENABLE);

    rt_timer_delete(&host->timer);
    rt_timer_delete(&host->data_timer);

    rt_workqueue_destroy(host->complete_wq);

}

rt_uint16_t rt_sdhci_clk_set(struct rt_sdhci_host *host, unsigned int clock,
                           unsigned int *actual_clock)
{
    int         div      = 0; /* Initialized for compiler warning */
    int         real_div = div, clk_mul = 1;
    rt_uint16_t clk             = 0;
    rt_bool_t   switch_base_clk = RT_FALSE;

    if (host->version >= RT_SDHCI_SPEC_300)
    {
        if (host->preset_enabled)
        {
            rt_uint16_t pre_val;

            clk     = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
            pre_val = sdhci_get_preset_value(host);
            div     = FIELD_GET(RT_SDHCI_PRESET_SDCLK_FREQ_MASK, pre_val);
            if (host->clk_mul && (pre_val & RT_SDHCI_PRESET_CLKGEN_SEL))
            {
                clk      = RT_SDHCI_PROG_CLOCK_MODE;
                real_div = div + 1;
                clk_mul  = host->clk_mul;
            }
            else
            {
                real_div = max_t(int, 1, div << 1);
            }
            goto clock_set;
        }

        if (host->clk_mul)
        {
            for (div = 1; div <= 1024; div++)
            {
                if ((host->max_clk * host->clk_mul / div)
                    <= clock)
                    break;
            }
            if ((host->max_clk * host->clk_mul / div) <= clock)
            {

                clk      = RT_SDHCI_PROG_CLOCK_MODE;
                real_div = div;
                clk_mul  = host->clk_mul;
                div--;
            }
            else
            {

                switch_base_clk = RT_TRUE;
            }
        }

        if (!host->clk_mul || switch_base_clk)
        {
            if (host->max_clk <= clock)
                div = 1;
            else
            {
                for (div  = 2; div < RT_SDHCI_MAX_DIV_SPEC_300;
                     div += 2)
                {
                    if ((host->max_clk / div) <= clock)
                        break;
                }
            }
            real_div   = div;
            div      >>= 1;
            if ((host->quirks2 & RT_SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN)
                && !div && host->max_clk <= 25000000)
                div = 1;
        }
    }
    else
    {
        for (div = 1; div < RT_SDHCI_MAX_DIV_SPEC_200; div *= 2)
        {
            if ((host->max_clk / div) <= clock)
                break;
        }
        real_div   = div;
        div      >>= 1;
    }

clock_set:
    if (real_div)
        *actual_clock = (host->max_clk * clk_mul) / real_div;
    clk |= (div & RT_SDHCI_DIV_MASK) << RT_SDHCI_DIVIDER_SHIFT;
    clk |= ((div & RT_SDHCI_DIV_HI_MASK) >> RT_SDHCI_DIV_MASK_LEN)
           << RT_SDHCI_DIVIDER_HI_SHIFT;

    return clk;
}

void rt_sdhci_clk_enable(struct rt_sdhci_host *host, rt_uint16_t clk)
{
    long timeout;

    clk |= RT_SDHCI_CLOCK_INT_EN;
    rt_sdhci_writew(host, clk, RT_SDHCI_CLOCK_CONTROL);

    timeout = rt_tick_from_millisecond(150);
    while (1)
    {
        timeout = timeout - rt_tick_get();

        clk = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
        if (clk & RT_SDHCI_CLOCK_INT_STABLE)
            break;
        if (timeout < 0)
        {
            rt_kprintf("%s: Internal clock never stabilised.\n",
                       mmc_hostname(host->mmc));
            rt_read_reg_debug(host);
            return;
        }
        rt_hw_us_delay(10);
    }

    if (host->version >= RT_SDHCI_SPEC_410 && host->v4_mode)
    {
        clk |= RT_SDHCI_CLOCK_PLL_EN;
        clk &= ~RT_SDHCI_CLOCK_INT_STABLE;
        rt_sdhci_writew(host, clk, RT_SDHCI_CLOCK_CONTROL);

        timeout = rt_tick_from_millisecond(150);
        while (1)
        {
            timeout = timeout - rt_tick_get();

            clk = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
            if (clk & RT_SDHCI_CLOCK_INT_STABLE)
                break;
            if (timeout < 0)
            {
                rt_kprintf("%s: PLL clock never stabilised.\n",
                           mmc_hostname(host->mmc));
                rt_read_reg_debug(host);
                return;
            }
            rt_hw_us_delay(10);
        }
    }

    clk |= RT_SDHCI_CLOCK_CARD_EN;
    rt_sdhci_writew(host, clk, RT_SDHCI_CLOCK_CONTROL);
}

void rt_sdhci_set_clock(struct rt_sdhci_host *host, unsigned int clock)
{
    rt_uint16_t clk;

    host->mmc->actual_clock = 0;

    rt_sdhci_writew(host, 0, RT_SDHCI_CLOCK_CONTROL);

    if (clock == 0)
        return;

    clk = rt_sdhci_clk_set(host, clock, &host->mmc->actual_clock);
    rt_sdhci_clk_enable(host, clk);
}

void rt_sdhci_read_caps(struct rt_sdhci_host *host, const rt_uint16_t *ver,
                       const rt_uint32_t *caps, const rt_uint32_t *caps1)
{
    rt_uint16_t v;
    rt_uint64_t dt_caps_mask = 0;
    rt_uint64_t dt_caps      = 0;

    if (host->read_caps)
        return;

    host->read_caps = RT_TRUE;

    if (debug_quirks)
        host->quirks = debug_quirks;

    if (debug_quirks2)
        host->quirks2 = debug_quirks2;

    sdhci_reset_for_all(host);

    if (host->v4_mode)
        sdhci_do_enable_v4_mode(host);
#ifdef RT_USING_OFW
    rt_ofw_prop_read_u64(mmc_dev(host->mmc)->ofw_node,
                         "sdhci-caps-mask", &dt_caps_mask);
    rt_ofw_prop_read_u64(mmc_dev(host->mmc)->ofw_node,
                         "sdhci-caps", &dt_caps);
#endif
    v             = ver ? *ver : rt_sdhci_readw(host, RT_SDHCI_HOST_VERSION);
    host->version = (v & RT_SDHCI_SPEC_VER_MASK) >> RT_SDHCI_SPEC_VER_SHIFT;

    if (caps)
    {
        host->caps = *caps;
    }
    else
    {
        host->caps  = rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES);
        host->caps &= ~lower_32_bits(dt_caps_mask);
        host->caps |= lower_32_bits(dt_caps);
    }

    if (host->version < RT_SDHCI_SPEC_300)
        return;

    if (caps1)
    {
        host->caps1 = *caps1;
    }
    else
    {
        host->caps1  = rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES_1);
        host->caps1 &= ~upper_32_bits(dt_caps_mask);
        host->caps1 |= upper_32_bits(dt_caps);
    }
}

struct rt_sdhci_host *rt_sdhci_alloc_host(struct rt_device *dev,
                                    size_t            priv_size)
{
    struct rt_mmc_host   *mmc;
    struct rt_sdhci_host *host;

    mmc = rt_mmc_alloc_host(sizeof(struct rt_sdhci_host) + priv_size, dev);
    if (!mmc)
        return NULL;

    host               = mmc_priv(mmc);
    host->mmc          = mmc;
    host->mmc_host_ops = rt_sdhci_ops;
    mmc->ops           = &host->mmc_host_ops;

    host->flags = RT_SDHCI_SIGNALING_330;

    host->cqe_ier     = RT_SDHCI_CQE_INT_MASK;
    host->cqe_err_ier = RT_SDHCI_CQE_INT_ERR_MASK;

    host->tuning_delay      = -1;
    host->tuning_loop_count = MAX_TUNING_LOOP;

    host->sdma_boundary = RT_SDHCI_DEFAULT_BOUNDARY_ARG;

    host->max_timeout_count = 0xE;

    return host;
}

int rt_sdhci_setup_host(struct rt_sdhci_host *host)
{
    struct rt_mmc_host *mmc;
    size_t           max_current_caps;
    unsigned int     ocr_avail;
    unsigned int     override_timeout_clk;
    size_t           max_clk;
    int              ret          = 0;
    bool             enable_vqmmc = RT_FALSE;

    RT_ASSERT(host != NULL);


    mmc = host->mmc;

    if (!mmc->supply.vqmmc)
    {
        if (ret)
            return ret;
        enable_vqmmc = RT_TRUE;
    }

    LOG_D("Version:   0x%08x | Present:  0x%08x\n",
          rt_sdhci_readw(host, RT_SDHCI_HOST_VERSION),
          rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE));
    LOG_D("Caps:      0x%08x | Caps_1:   0x%08x\n",
          rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES),
          rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES_1));

    rt_sdhci_read_caps(host,RT_NULL,RT_NULL,RT_NULL);

    override_timeout_clk = host->timeout_clk;

    if (host->version > RT_SDHCI_SPEC_420)
    {
        rt_kprintf("%s: Unknown controller version (%d). You may experience problems.\n",
                   mmc_hostname(mmc), host->version);
    }

    if (host->quirks & RT_SDHCI_QUIRK_FORCE_DMA)
        host->flags |= RT_SDHCI_USE_SDMA;
    else if (!(host->caps & RT_SDHCI_CAN_DO_SDMA))
        LOG_D("Controller doesn't have SDMA capability\n");
    else
        host->flags |= RT_SDHCI_USE_SDMA;

    if ((host->quirks & RT_SDHCI_QUIRK_BROKEN_DMA) && (host->flags & RT_SDHCI_USE_SDMA))
    {
        LOG_D("Disabling DMA as it is marked broken\n");
        host->flags &= ~RT_SDHCI_USE_SDMA;
    }

    if (sdhci_can_64bit_dma(host))
        host->flags |= RT_SDHCI_USE_64_BIT_DMA;

    if (host->flags & RT_SDHCI_USE_SDMA)
    {
        if (host->ops->set_dma_mask)
            ret = host->ops->set_dma_mask(host);

        if (!ret && host->ops->enable_dma)
            ret = host->ops->enable_dma(host);

        if (ret)
        {
            rt_kprintf("%s: No suitable DMA available - falling back to PIO\n",
                       mmc_hostname(mmc));
            host->flags &= ~RT_SDHCI_USE_SDMA;

            ret = 0;
        }
    }

    if ((host->flags & RT_SDHCI_USE_64_BIT_DMA) && !host->v4_mode)
        host->flags &= ~RT_SDHCI_USE_SDMA;

    if (!(host->flags & RT_SDHCI_USE_SDMA))
    {
        host->dma_mask = DMA_BIT_MASK(64);
    }
    if (host->version >= RT_SDHCI_SPEC_300)
        host->max_clk = FIELD_GET(RT_SDHCI_CLOCK_V3_BASE_MASK, host->caps);
    else
        host->max_clk = FIELD_GET(RT_SDHCI_CLOCK_BASE_MASK, host->caps);

    host->max_clk *= 1000000;
    if (host->max_clk == 0 || host->quirks & RT_SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN)
    {
        if (!host->ops->get_max_clock)
        {
            rt_kprintf("%s: Hardware doesn't specify base clock frequency.  %p \n",
                       mmc_hostname(mmc), host->ops->get_max_clock);
            ret = -ENODEV;
            goto undma;
        }
        host->max_clk = host->ops->get_max_clock(host);
    }

    host->clk_mul = FIELD_GET(RT_SDHCI_CLOCK_MUL_MASK, host->caps1);

    if (host->clk_mul)
        host->clk_mul += 1;

    max_clk = host->max_clk;

    if (host->ops->get_min_clock)
        mmc->f_min = host->ops->get_min_clock(host);
    else if (host->version >= RT_SDHCI_SPEC_300)
    {
        if (host->clk_mul)
            max_clk = host->max_clk * host->clk_mul;

        mmc->f_min = host->max_clk / RT_SDHCI_MAX_DIV_SPEC_300;
    }
    else
        mmc->f_min = host->max_clk / RT_SDHCI_MAX_DIV_SPEC_200;

    if (!mmc->f_max || mmc->f_max > max_clk)
        mmc->f_max = max_clk;

    if (!(host->quirks & RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK))
    {
        host->timeout_clk = FIELD_GET(RT_SDHCI_TIMEOUT_CLK_MASK, host->caps);

        if (host->caps & RT_SDHCI_TIMEOUT_CLK_UNIT)
            host->timeout_clk *= 1000;

        if (host->timeout_clk == 0)
        {
            if (!host->ops->get_timeout_clock)
            {
                rt_kprintf("%s: Hardware doesn't specify timeout clock frequency.\n",
                           mmc_hostname(mmc));
                ret = -ENODEV;
                goto undma;
            }

            host->timeout_clk =
                DIV_ROUND_UP(host->ops->get_timeout_clock(host),
                             1000);
        }

        if (override_timeout_clk)
            host->timeout_clk = override_timeout_clk;

        mmc->max_busy_timeout  = host->ops->get_max_timeout_count ? host->ops->get_max_timeout_count(host) : 1 << 27;
        mmc->max_busy_timeout /= host->timeout_clk;
    }

    if (host->quirks2 & RT_SDHCI_QUIRK2_DISABLE_HW_TIMEOUT && !host->ops->get_max_timeout_count)
        mmc->max_busy_timeout = 0;

    mmc->caps  |= MMC_CAP_SDIO_IRQ | MMC_CAP_CMD23;
    mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

    if (host->quirks & RT_SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12)
        host->flags |= RT_SDHCI_AUTO_CMD12;

    if ((host->version >= RT_SDHCI_SPEC_300) && (!(host->flags & RT_SDHCI_USE_SDMA) || host->v4_mode) && !(host->quirks2 & RT_SDHCI_QUIRK2_ACMD23_BROKEN))
    {
        host->flags |= RT_SDHCI_AUTO_CMD23;
        LOG_D("Auto-CMD23 available\n");
    }
    else
    {
        LOG_D("Auto-CMD23 unavailable\n");
    }

    if (!(host->quirks & RT_SDHCI_QUIRK_FORCE_1_BIT_DATA))
        mmc->caps |= MMC_CAP_4_BIT_DATA;

    if (host->quirks2 & RT_SDHCI_QUIRK2_HOST_NO_CMD23)
        mmc->caps &= ~MMC_CAP_CMD23;

    if (host->caps & RT_SDHCI_CAN_DO_HISPD)
        mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;
    if ((host->quirks & RT_SDHCI_QUIRK_BROKEN_CARD_DETECTION) && mmc_card_is_removable(mmc) && rt_mmc_gpio_get_cd(mmc) < 0)
        mmc->caps |= MMC_CAP_NEEDS_POLL;

    if (mmc->supply.vqmmc)
    {
        if (enable_vqmmc)
        {
            host->sdhci_core_to_disable_vqmmc = !ret;
        }

        if (!regulator_is_supported_voltage(mmc->supply.vqmmc, 1700000,
                                            1950000))
            host->caps1 &= ~(RT_SDHCI_SUPPORT_SDR104 | RT_SDHCI_SUPPORT_SDR50 | RT_SDHCI_SUPPORT_DDR50);

        if (!regulator_is_supported_voltage(mmc->supply.vqmmc, 2700000,
                                            3600000))
            host->flags &= ~RT_SDHCI_SIGNALING_330;

        if (ret)
        {
            rt_kprintf("%s: Failed to enable vqmmc regulator: %d\n",
                       mmc_hostname(mmc), ret);
            mmc->supply.vqmmc = (void *)-EINVAL;
        }
    }
    if (host->quirks2 & RT_SDHCI_QUIRK2_NO_1_8_V)
    {
        host->caps1 &= ~(RT_SDHCI_SUPPORT_SDR104 | RT_SDHCI_SUPPORT_SDR50 | RT_SDHCI_SUPPORT_DDR50);
        mmc->caps2 &= ~(MMC_CAP2_HSX00_1_8V | MMC_CAP2_HS400_ES);
        mmc->caps  &= ~(MMC_CAP_1_8V_DDR | MMC_CAP_UHS);
    }

    if (host->caps1 & (RT_SDHCI_SUPPORT_SDR104 | RT_SDHCI_SUPPORT_SDR50 | RT_SDHCI_SUPPORT_DDR50))
        mmc->caps |= MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25;

    if (host->caps1 & RT_SDHCI_SUPPORT_SDR104)
    {
        mmc->caps |= MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_SDR50;

        if (!(host->quirks2 & RT_SDHCI_QUIRK2_BROKEN_HS200))
            mmc->caps2 |= MMC_CAP2_HS200;
    }
    else if (host->caps1 & RT_SDHCI_SUPPORT_SDR50)
    {
        mmc->caps |= MMC_CAP_UHS_SDR50;
    }

    if (host->quirks2 & RT_SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 && (host->caps1 & RT_SDHCI_SUPPORT_HS400))
        mmc->caps2 |= MMC_CAP2_HS400;
    if ((mmc->caps2 & MMC_CAP2_HSX00_1_2V) && (!mmc->supply.vqmmc || !regulator_is_supported_voltage(mmc->supply.vqmmc, 1100000, 1300000)))
        mmc->caps2 &= ~MMC_CAP2_HSX00_1_2V;
    if ((host->caps1 & RT_SDHCI_SUPPORT_DDR50) && !(host->quirks2 & RT_SDHCI_QUIRK2_BROKEN_DDR50))
        mmc->caps |= MMC_CAP_UHS_DDR50;

    if (host->caps1 & RT_SDHCI_USE_SDR50_TUNING)
        host->flags |= RT_SDHCI_SDR50_NEEDS_TUNING;

    if (host->caps1 & RT_SDHCI_DRIVER_TYPE_A)
        mmc->caps |= MMC_CAP_DRIVER_TYPE_A;
    if (host->caps1 & RT_SDHCI_DRIVER_TYPE_C)
        mmc->caps |= MMC_CAP_DRIVER_TYPE_C;
    if (host->caps1 & RT_SDHCI_DRIVER_TYPE_D)
        mmc->caps |= MMC_CAP_DRIVER_TYPE_D;

    host->tuning_count = FIELD_GET(RT_SDHCI_RETUNING_TIMER_COUNT_MASK,
                                   host->caps1);

    if (host->tuning_count)
        host->tuning_count = 1 << (host->tuning_count - 1);

    /* Re-tuning mode supported by the Host Controller */
    host->tuning_mode = FIELD_GET(RT_SDHCI_RETUNING_MODE_MASK, host->caps1);

    ocr_avail = 0;

    max_current_caps = rt_sdhci_readl(host, RT_SDHCI_MAX_CURRENT);

    if (!max_current_caps && mmc->supply.vmmc)
    {
        int curr = regulator_get_current_limit(mmc->supply.vmmc);
        if (curr > 0)
        {
            curr = curr / 1000; /* convert to mA */
            curr = curr / RT_SDHCI_MAX_CURRENT_MULTIPLIER;

            curr = min_t(rt_uint32_t, curr, RT_SDHCI_MAX_CURRENT_LIMIT);
            max_current_caps =
                FIELD_PREP(RT_SDHCI_MAX_CURRENT_330_MASK, curr) | FIELD_PREP(RT_SDHCI_MAX_CURRENT_300_MASK, curr) | FIELD_PREP(RT_SDHCI_MAX_CURRENT_180_MASK, curr);
        }
    }

    if (host->caps & RT_SDHCI_CAN_VDD_330)
    {
        ocr_avail |= MMC_VDD_32_33 | MMC_VDD_33_34;

        mmc->max_current_330 = FIELD_GET(RT_SDHCI_MAX_CURRENT_330_MASK,
                                         max_current_caps)
                               * RT_SDHCI_MAX_CURRENT_MULTIPLIER;
    }
    if (host->caps & RT_SDHCI_CAN_VDD_300)
    {
        ocr_avail |= MMC_VDD_29_30 | MMC_VDD_30_31;

        mmc->max_current_300 = FIELD_GET(RT_SDHCI_MAX_CURRENT_300_MASK,
                                         max_current_caps)
                               * RT_SDHCI_MAX_CURRENT_MULTIPLIER;
    }
    if (host->caps & RT_SDHCI_CAN_VDD_180)
    {
        ocr_avail |= MMC_VDD_165_195;

        mmc->max_current_180 = FIELD_GET(RT_SDHCI_MAX_CURRENT_180_MASK,
                                         max_current_caps)
                               * RT_SDHCI_MAX_CURRENT_MULTIPLIER;
    }

    if (host->ocr_mask)
        ocr_avail = host->ocr_mask;

    if (mmc->ocr_avail)
        ocr_avail = mmc->ocr_avail;

    mmc->ocr_avail      = ocr_avail;
    mmc->ocr_avail_sdio = ocr_avail;
    if (host->ocr_avail_sdio)
        mmc->ocr_avail_sdio &= host->ocr_avail_sdio;
    mmc->ocr_avail_sd = ocr_avail;
    if (host->ocr_avail_sd)
        mmc->ocr_avail_sd &= host->ocr_avail_sd;
    else
        mmc->ocr_avail_sd &= ~MMC_VDD_165_195;
    mmc->ocr_avail_mmc = ocr_avail;
    if (host->ocr_avail_mmc)
        mmc->ocr_avail_mmc &= host->ocr_avail_mmc;

    if (mmc->ocr_avail == 0)
    {
        rt_kprintf("%s: Hardware doesn't report any support voltages.\n",
                   mmc_hostname(mmc));
        ret = -ENODEV;
        goto unreg;
    }

    if ((mmc->caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_DDR50 | MMC_CAP_1_8V_DDR)) || (mmc->caps2 & (MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS400_1_8V)))
        host->flags |= RT_SDHCI_SIGNALING_180;

    if (mmc->caps2 & MMC_CAP2_HSX00_1_2V)
        host->flags |= RT_SDHCI_SIGNALING_120;

    rt_spin_lock_init(&host->lock);

    mmc->max_req_size = 524288;
    if (host->flags & RT_SDHCI_USE_SDMA)
    {
        mmc->max_segs = 1;
    }
    else
    { /* PIO */
        mmc->max_segs = RT_SDHCI_MAX_SEGS;
    }

    mmc->max_seg_size = mmc->max_req_size;

    if (host->quirks & RT_SDHCI_QUIRK_FORCE_BLK_SZ_2048)
    {
        mmc->max_blk_size = 2;
    }
    else
    {
        mmc->max_blk_size = (host->caps & RT_SDHCI_MAX_BLOCK_MASK) >> RT_SDHCI_MAX_BLOCK_SHIFT;
        if (mmc->max_blk_size >= 3)
        {
            rt_kprintf("%s: Invalid maximum block size, assuming 512 bytes\n",
                       mmc_hostname(mmc));
            mmc->max_blk_size = 0;
        }
    }

    mmc->max_blk_size = 512 << mmc->max_blk_size;

    /*
     * Maximum block count.
     */
    mmc->max_blk_count = (host->quirks & RT_SDHCI_QUIRK_NO_MULTIBLOCK) ? 1 : 65535;
    return 0;

unreg:
undma:
    return ret;
}

static void sdhci_init(struct rt_sdhci_host *host, int soft)
{
    struct rt_mmc_host *mmc = host->mmc;
    rt_base_t        flags;

    if (soft)
    {
        sdhci_do_reset(host, RT_SDHCI_RESET_CMD | RT_SDHCI_RESET_DATA);
    }
    else
    {
        sdhci_do_reset(host, RT_SDHCI_RESET_ALL);
    }
    if (host->v4_mode)
    {
        sdhci_do_enable_v4_mode(host);
    }
    flags = rt_spin_lock_irqsave(&host->lock);
    sdhci_set_default_irqs(host);
    rt_spin_unlock_irqrestore(&host->lock, flags);

    host->cqe_on = RT_FALSE;

    if (soft)
    {
        /* force clock reconfiguration */
        host->clock      = 0;
        host->reinit_uhs = RT_TRUE;
        mmc->ops->set_ios(mmc, &mmc->ios);
    }
}

static void sdhci_reinit(struct rt_sdhci_host *host)
{
    rt_uint32_t cd = host->ier & (RT_SDHCI_INT_CARD_REMOVE | RT_SDHCI_INT_CARD_INSERT);

    sdhci_init(host, 0);
    sdhci_enable_card_detection(host);

    if (cd != (host->ier & (RT_SDHCI_INT_CARD_REMOVE | RT_SDHCI_INT_CARD_INSERT)))
        rt_mmc_detect_change(host->mmc, rt_tick_from_millisecond(200));
}

int rt_sdhci_init_host(struct rt_sdhci_host *host)
{
    struct rt_mmc_host *mmc = host->mmc;
    int              ret;

    if ((mmc->caps2 & MMC_CAP2_CQE) && (host->quirks & RT_SDHCI_QUIRK_BROKEN_CQE))
    {
        mmc->caps2 &= ~MMC_CAP2_CQE;
    }

    host->complete_wq = rt_workqueue_create("sdhci", 4096, 20);
    if (!host->complete_wq)
        return -ENOMEM;

    rt_work_init(&host->complete_work, sdhci_complete_work, host);

    rt_timer_init(&host->timer, "sdhci_timer", sdhci_timeout_timer, host, 0, RT_TIMER_FLAG_SOFT_TIMER);
    rt_timer_init(&host->data_timer, "sdhci_data_timer", sdhci_timeout_data_timer, host, 0, RT_TIMER_FLAG_SOFT_TIMER);

    rt_wqueue_init(&host->buf_ready_int);

    sdhci_init(host, 0);

    host->irq_wq = rt_workqueue_create("sdhci_irq", 8192, 1);
    rt_work_init(&host->irq_work, sdhci_thread_irq, host);
    rt_hw_interrupt_install(host->irq, sdhci_irq, host, mmc_hostname(mmc));
    rt_pic_irq_unmask(host->irq);
    ret = rt_mmc_add_host(mmc);
    if (ret)
        goto unirq;

    LOG_D("%s: RT_SDHCI controller on %s [%s] using %s\n",
               mmc_hostname(mmc), host->hw_name, mmc_dev(mmc)->parent.name,
               (host->flags & RT_SDHCI_USE_SDMA) ? "DMA" : "PIO");

    sdhci_enable_card_detection(host);

    return 0;

unirq:
    sdhci_reset_for_all(host);
    rt_sdhci_writel(host, 0, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, 0, RT_SDHCI_SIGNAL_ENABLE);

    return ret;
}

int rt_sdhci_set_and_add_host(struct rt_sdhci_host *host)
{
    int ret;
    ret = rt_sdhci_setup_host(host);
    if (ret)
        return ret;

    ret = rt_sdhci_init_host(host);
    if (ret)
        goto cleanup;

    return 0;

cleanup:
    rt_sdhci_cleanup_host(host);

    return ret;
}

void rt_sdhci_ios_set(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    struct rt_sdhci_host *host           = mmc_priv(mmc);
    rt_bool_t          reinit_uhs     = host->reinit_uhs;
    rt_bool_t          turning_on_clk = RT_FALSE;
    rt_uint8_t         ctrl;

    host->reinit_uhs = RT_FALSE;

    if (ios->power_mode == MMC_POWER_UNDEFINED)
        return;

    if (host->flags & RT_SDHCI_DEVICE_DEAD)
    {
        if (mmc->supply.vmmc && ios->power_mode == MMC_POWER_OFF)
            mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
        return;
    }

    if (ios->power_mode == MMC_POWER_OFF)
    {
        rt_sdhci_writel(host, 0, RT_SDHCI_SIGNAL_ENABLE);
        sdhci_reinit(host);
    }

    if (host->version >= RT_SDHCI_SPEC_300 && (ios->power_mode == MMC_POWER_UP) && !(host->quirks2 & RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN))
        sdhci_preset_value_enable(host, RT_FALSE);

    if (!ios->clock || ios->clock != host->clock)
    {
        turning_on_clk = ios->clock && !host->clock;

        host->ops->set_clock(host, ios->clock);
        host->clock = ios->clock;

        if (host->quirks & RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK && host->clock)
        {
            host->timeout_clk = mmc->actual_clock ? mmc->actual_clock / 1000 : host->clock / 1000;
            mmc->max_busy_timeout =
                host->ops->get_max_timeout_count ? host->ops->get_max_timeout_count(host) : 1 << 27;
            mmc->max_busy_timeout /= host->timeout_clk;
        }
    }

    if (host->ops->set_power)
        host->ops->set_power(host, ios->power_mode, ios->vdd);
    else
        rt_sdhci_set_power(host, ios->power_mode, ios->vdd);

    host->ops->set_bus_width(host, ios->bus_width);

    if (!reinit_uhs && turning_on_clk && host->timing == ios->timing && host->version >= RT_SDHCI_SPEC_300 && !sdhci_presetable_values_change(host, ios))
        return;

    ctrl = rt_sdhci_readb(host, RT_SDHCI_HOST_CONTROL);

    if (!(host->quirks & RT_SDHCI_QUIRK_NO_HISPD_BIT))
    {
        if (ios->timing == MMC_TIMING_SD_HS || ios->timing == MMC_TIMING_MMC_HS || ios->timing == MMC_TIMING_MMC_HS400 || ios->timing == MMC_TIMING_MMC_HS200 || ios->timing == MMC_TIMING_MMC_DDR52 || ios->timing == MMC_TIMING_UHS_SDR50 || ios->timing == MMC_TIMING_UHS_SDR104 || ios->timing == MMC_TIMING_UHS_DDR50 || ios->timing == MMC_TIMING_UHS_SDR25)
            ctrl |= RT_SDHCI_CTRL_HISPD;
        else
            ctrl &= ~RT_SDHCI_CTRL_HISPD;
    }

    if (host->version >= RT_SDHCI_SPEC_300)
    {
        rt_uint16_t clk, ctrl_2;

        clk = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
        if (clk & RT_SDHCI_CLOCK_CARD_EN)
        {
            clk &= ~RT_SDHCI_CLOCK_CARD_EN;
            rt_sdhci_writew(host, clk, RT_SDHCI_CLOCK_CONTROL);
        }

        rt_sdhci_writeb(host, ctrl, RT_SDHCI_HOST_CONTROL);

        if (!host->preset_enabled)
        {
            ctrl_2  = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
            ctrl_2 &= ~RT_SDHCI_CTRL_DRV_TYPE_MASK;
            if (ios->drv_type == MMC_SET_DRIVER_TYPE_A)
                ctrl_2 |= RT_SDHCI_CTRL_DRV_TYPE_A;
            else if (ios->drv_type == MMC_SET_DRIVER_TYPE_B)
                ctrl_2 |= RT_SDHCI_CTRL_DRV_TYPE_B;
            else if (ios->drv_type == MMC_SET_DRIVER_TYPE_C)
                ctrl_2 |= RT_SDHCI_CTRL_DRV_TYPE_C;
            else if (ios->drv_type == MMC_SET_DRIVER_TYPE_D)
                ctrl_2 |= RT_SDHCI_CTRL_DRV_TYPE_D;
            else
            {
                LOG_D("%s: invalid driver type, default to driver type B\n",
                      mmc_hostname(mmc));
                ctrl_2 |= RT_SDHCI_CTRL_DRV_TYPE_B;
            }

            rt_sdhci_writew(host, ctrl_2, RT_SDHCI_HOST_CONTROL2);
            host->drv_type = ios->drv_type;
        }

        host->ops->set_uhs_signaling(host, ios->timing);
        host->timing = ios->timing;

        if (sdhci_preset_needed(host, ios->timing))
        {
            rt_uint16_t preset;

            sdhci_preset_value_enable(host, RT_TRUE);
            preset         = sdhci_get_preset_value(host);
            ios->drv_type  = FIELD_GET(RT_SDHCI_PRESET_DRV_MASK,
                                       preset);
            host->drv_type = ios->drv_type;
        }

        host->ops->set_clock(host, host->clock);
    }
    else
        rt_sdhci_writeb(host, ctrl, RT_SDHCI_HOST_CONTROL);
}
void rt_sdhci_free_host(struct rt_sdhci_host *host)
{
    rt_sdhci_cleanup_host(host);
    rt_free(host);
}
