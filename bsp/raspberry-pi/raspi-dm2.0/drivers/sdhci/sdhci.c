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
#include "sdhci.h"
#include <string.h>
#define DBG_TAG "SDHCI"
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


void read_reg(struct sdhci_host *host)
{
    rt_kprintf("0x00 addddddddddddd           = %x \n", sdhci_readl(host, 0x00));
    rt_kprintf("0x04 EMMC_BLOCKSIZE           = %x \n", sdhci_readw(host, 0x04));
    rt_kprintf("0x06 EMMC_BLOCKCOUNT          = %x \n", sdhci_readw(host, 0x06));
    rt_kprintf("0x08 SDHCI_ARGUMENT           = %x \n", sdhci_readl(host, 0x08));
    rt_kprintf("0x0c EMMC_XFER_MODE           = %x \n", sdhci_readw(host, 0x0c));
    rt_kprintf("0x0e SDHCI_COMMAND            = %x \n", sdhci_readw(host, 0x0e));
    rt_kprintf("0x24 SDHCI_PRESENT_STATE      = %x \n", sdhci_readl(host, 0x24));
    rt_kprintf("0x28 SDHCI_HOST_CONTROL       = %x \n", sdhci_readb(host, 0x28));
    rt_kprintf("0x29 SDHCI_POWER_CONTROL      = %x \n", sdhci_readb(host, 0x29));
    rt_kprintf("0x2a EMMC_BGAP_CTRL           = %x \n", sdhci_readb(host, 0x2a));
    rt_kprintf("0x2c EMMC_CLK_CTRL            = %x \n", sdhci_readw(host, 0x2c));
    rt_kprintf("0x2e EMMC_TOUT_CTRL           = %x \n", sdhci_readb(host, 0x2e));
    rt_kprintf("0x2f EMMC_SW_RST              = %x \n", sdhci_readb(host, 0x2f));
    rt_kprintf("0x30 SDHCI_INT_STATUS         = %x \n", sdhci_readw(host, 0x30));
    rt_kprintf("0x32 SDHCI_ERR_INT_STATUS     = %x \n", sdhci_readw(host, 0x32));
    rt_kprintf("0x34 SDHCI_INT_ENABLE         = %x \n", sdhci_readw(host, 0x34));
    rt_kprintf("0x36 EMMC ERROR INT STATEN    = %x \n", sdhci_readw(host, 0x36));
    rt_kprintf("0x38 EMMC NORMAL INT SIGNAL EN= %x \n", sdhci_readw(host, 0x38));
    rt_kprintf("0x3a EMMC ERROR INT SIGNAL EN = %x \n", sdhci_readw(host, 0x3a));
    rt_kprintf("0x3c EMMC_AUTO_CMD_STAT       = %x \n", sdhci_readw(host, 0x3c));
    rt_kprintf("0x3e EMMC_HOST_CTRL2          = %x \n", sdhci_readw(host, 0x3e));
    rt_kprintf("0x40 EMMC_CAPABILITIES1       = %x \n", sdhci_readl(host, 0x40));
    rt_kprintf("0x44 EMMC_CAPABILITIES2       = %x \n", sdhci_readl(host, 0x44));
    rt_kprintf("0x52 EMMC_FORC_ERR_INT_STAT   = %x \n", sdhci_readw(host, 0x52));
    rt_kprintf("0x54 EMMC_ADMA_ERR_STAT       = %x \n", sdhci_readb(host, 0x54));
    rt_kprintf("0x58 EMMC_ADMA_SA       = %x \n", sdhci_readl(host, 0x58));
    rt_kprintf("0x66 EMMC_PRESET_SDR12        = %x \n", sdhci_readw(host, 0x66));
    rt_kprintf("0x68 EMMC_PRESET_SDR25        = %x \n", sdhci_readw(host, 0x68));
    rt_kprintf("0x6a EMMC_PRESET_SDR50        = %x \n", sdhci_readw(host, 0x6a));
    rt_kprintf("0x6c EMMC_PRESET_SDR104       = %x \n", sdhci_readw(host, 0x6c));
    rt_kprintf("0x6e EMMC_PRESET_DDR50        = %x \n", sdhci_readw(host, 0x6e));
    rt_kprintf("0x78 EMMC_ADMA_ID             = %x \n", sdhci_readl(host, 0x78));
    rt_kprintf("0xfe EMMC_HOST_CNTRL_VERS     = %x \n", sdhci_readw(host, 0xfe));

}
static inline rt_bool_t sdhci_has_requests(struct sdhci_host *host)
{
    return host->cmd || host->data_cmd;
}

static inline rt_bool_t sdhci_auto_cmd23(struct sdhci_host   *host,
                                         struct rt_mmcsd_req *mrq)
{
    return mrq->sbc && (host->flags & SDHCI_AUTO_CMD23);
}

static inline rt_bool_t sdhci_auto_cmd12(struct sdhci_host   *host,
                                         struct rt_mmcsd_req *mrq)
{
    return !mrq->sbc && (host->flags & SDHCI_AUTO_CMD12) && !mrq->cap_cmd_during_tfr;
}

static inline rt_bool_t sdhci_manual_cmd23(struct sdhci_host   *host,
                                           struct rt_mmcsd_req *mrq)
{
    return mrq->sbc && !(host->flags & SDHCI_AUTO_CMD23);
}

static inline rt_bool_t sdhci_data_line_cmd(struct rt_mmcsd_cmd *cmd)
{
    return cmd->data || cmd->flags & MMC_RSP_BUSY;
}

void sdhci_set_data_timeout_irq(struct sdhci_host *host, rt_bool_t enable)
{
    if (enable)
        host->ier |= SDHCI_INT_DATA_TIMEOUT;
    else
        host->ier &= ~SDHCI_INT_DATA_TIMEOUT;
    sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
    sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

void sdhci_set_uhs_signaling(struct sdhci_host *host, unsigned timing)
{
    rt_uint16_t ctrl_2;

    ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
    /* Select Bus Speed Mode for host */
    ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
    if ((timing == MMC_TIMING_MMC_HS200) || (timing == MMC_TIMING_UHS_SDR104))
        ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
    else if (timing == MMC_TIMING_UHS_SDR12)
        ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
    else if (timing == MMC_TIMING_UHS_SDR25)
        ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
    else if (timing == MMC_TIMING_UHS_SDR50)
        ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
    else if ((timing == MMC_TIMING_UHS_DDR50) || (timing == MMC_TIMING_MMC_DDR52))
        ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
    else if (timing == MMC_TIMING_MMC_HS400)
        ctrl_2 |= SDHCI_CTRL_HS400; /* Non-standard */
    sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);
}

void sdhci_set_bus_width(struct sdhci_host *host, int width)
{
    rt_uint8_t ctrl;

    ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);
    if (width == MMC_BUS_WIDTH_8)
    {
        ctrl &= ~SDHCI_CTRL_4BITBUS;
        ctrl |= SDHCI_CTRL_8BITBUS;
    }
    else
    {
        if (host->mmc->caps & MMC_CAP_8_BIT_DATA)
            ctrl &= ~SDHCI_CTRL_8BITBUS;
        if (width == MMC_BUS_WIDTH_4)
            ctrl |= SDHCI_CTRL_4BITBUS;
        else
            ctrl &= ~SDHCI_CTRL_4BITBUS;
    }
    sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}

static inline rt_bool_t sdhci_can_64bit_dma(struct sdhci_host *host)
{
    /*
     * According to SD Host Controller spec v4.10, bit[27] added from
     * version 4.10 in Capabilities Register is used as 64-bit System
     * Address support for V4 mode.
     */
    if (host->version >= SDHCI_SPEC_410 && host->v4_mode)
        return host->caps & SDHCI_CAN_64BIT_V4;

    return host->caps & SDHCI_CAN_64BIT;
}

static void sdhci_do_enable_v4_mode(struct sdhci_host *host)
{
    rt_uint16_t ctrl2;

    ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
    if (ctrl2 & SDHCI_CTRL_V4_MODE)
        return;

    ctrl2 |= SDHCI_CTRL_V4_MODE;
    sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);
}

void sdhci_cleanup_host(struct sdhci_host *host)
{
    struct mmc_host *mmc = host->mmc;

    if (host->sdhci_core_to_disable_vqmmc)
        regulator_disable(mmc->supply.vqmmc);

    if (host->align_buffer)
        dma_free_coherent(mmc_dev(mmc), host->align_buffer_sz + host->adma_table_sz, host->align_buffer,
                          host->align_addr);

    host->adma_table   = NULL;
    host->align_buffer = NULL;
}

static void sdhci_set_default_irqs(struct sdhci_host *host)
{
    host->ier = SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT | SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC | SDHCI_INT_TIMEOUT | SDHCI_INT_DATA_END | SDHCI_INT_RESPONSE;

    if (host->tuning_mode == SDHCI_TUNING_MODE_2 || host->tuning_mode == SDHCI_TUNING_MODE_3)
        host->ier |= SDHCI_INT_RETUNE;

    sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
    sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}


static inline void sdhci_auto_cmd_select(struct sdhci_host   *host,
                                         struct rt_mmcsd_cmd *cmd,
                                         rt_uint16_t         *mode)
{
    rt_bool_t   use_cmd12 = sdhci_auto_cmd12(host, cmd->mrq) && (cmd->cmd_code != SD_IO_RW_EXTENDED);
    rt_bool_t   use_cmd23 = sdhci_auto_cmd23(host, cmd->mrq);
    rt_uint16_t ctrl2;

    /*
     * In case of Version 4.10 or later, use of 'Auto CMD Auto
     * Select' is recommended rather than use of 'Auto CMD12
     * Enable' or 'Auto CMD23 Enable'. We require Version 4 Mode
     * here because some controllers (e.g sdhci-of-dwmshc) expect it.
     */
    if (host->version >= SDHCI_SPEC_410 && host->v4_mode && (use_cmd12 || use_cmd23))
    {
        *mode |= SDHCI_TRNS_AUTO_SEL;

        ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
        if (use_cmd23)
            ctrl2 |= SDHCI_CMD23_ENABLE;
        else
            ctrl2 &= ~SDHCI_CMD23_ENABLE;
        sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);

        return;
    }

    /*
     * If we are sending CMD23, CMD12 never gets sent
     * on successful completion (so no Auto-CMD12).
     */
    if (use_cmd12)
        *mode |= SDHCI_TRNS_AUTO_CMD12;
    else if (use_cmd23)
        *mode |= SDHCI_TRNS_AUTO_CMD23;
}


static rt_bool_t sdhci_present_error(struct sdhci_host   *host,
                                     struct rt_mmcsd_cmd *cmd, rt_bool_t present)
{
    if (!present || host->flags & SDHCI_DEVICE_DEAD)
    {
        cmd->err = -ENOMEDIUM;
        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_uint16_t sdhci_get_preset_value(struct sdhci_host *host)
{
    rt_uint16_t preset = 0;

    switch (host->timing)
    {
    case MMC_TIMING_MMC_HS:
    case MMC_TIMING_SD_HS:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_HIGH_SPEED);
        break;
    case MMC_TIMING_UHS_SDR12:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR12);
        break;
    case MMC_TIMING_UHS_SDR25:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR25);
        break;
    case MMC_TIMING_UHS_SDR50:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR50);
        break;
    case MMC_TIMING_UHS_SDR104:
    case MMC_TIMING_MMC_HS200:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR104);
        break;
    case MMC_TIMING_UHS_DDR50:
    case MMC_TIMING_MMC_DDR52:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_DDR50);
        break;
    case MMC_TIMING_MMC_HS400:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_HS400);
        break;
    default:
        preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR12);
        break;
    }
    return preset;
}

static void sdhci_set_card_detection(struct sdhci_host *host, rt_bool_t enable)
{
    rt_uint32_t present;

    if ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) || !mmc_card_is_removable(host->mmc))
        return;

    if (enable)
    {
        present = sdhci_readl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT;

        host->ier |= present ? SDHCI_INT_CARD_REMOVE : SDHCI_INT_CARD_INSERT;
    }
    else
    {
        host->ier &= ~(SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT);
    }

    sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
    sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

static void sdhci_enable_card_detection(struct sdhci_host *host)
{
    sdhci_set_card_detection(host, RT_TRUE);
}

static inline int sdhci_external_dma_init(struct sdhci_host *host)
{
    return -EOPNOTSUPP;
}

static inline void sdhci_external_dma_release(struct sdhci_host *host)
{
}

static inline void sdhci_external_dma_prepare_data(struct sdhci_host   *host,
                                                   struct rt_mmcsd_cmd *cmd)
{
    /* This should never happen */
}

static inline void sdhci_external_dma_pre_transfer(struct sdhci_host   *host,
                                                   struct rt_mmcsd_cmd *cmd)
{
}

static inline struct dma_chan *sdhci_external_dma_channel(struct sdhci_host    *host,
                                                          struct rt_mmcsd_data *data)
{
    return NULL;
}

/********************************************************* */
/*                     reset                               */
/********************************************************* */
enum sdhci_reset_reason
{
    SDHCI_RESET_FOR_INIT,
    SDHCI_RESET_FOR_REQUEST_ERROR,
    SDHCI_RESET_FOR_REQUEST_ERROR_DATA_ONLY,
    SDHCI_RESET_FOR_TUNING_ABORT,
    SDHCI_RESET_FOR_CARD_REMOVED,
    SDHCI_RESET_FOR_CQE_RECOVERY,
};

static rt_bool_t sdhci_needs_reset(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    return (!(host->flags & SDHCI_DEVICE_DEAD) && ((mrq->cmd && mrq->cmd->err) || (mrq->sbc && mrq->sbc->err) || (mrq->data && mrq->data->stop && mrq->data->stop->err) || (host->quirks & SDHCI_QUIRK_RESET_AFTER_REQUEST)));
}

static rt_bool_t sdhci_do_reset(struct sdhci_host *host, rt_uint8_t mask)
{
    if (host->quirks & SDHCI_QUIRK_NO_CARD_NO_RESET)
    {
        struct mmc_host *mmc = host->mmc;

        if (!mmc->ops->get_cd(mmc))
            return RT_FALSE;
    }
    if (host->ops->reset)
    {
        host->ops->reset(host, mask);
    }
    return RT_TRUE;
}

static void sdhci_reset_for_reason(struct sdhci_host *host, enum sdhci_reset_reason reason)
{
    if (host->quirks2 & SDHCI_QUIRK2_ISSUE_CMD_DAT_RESET_TOGETHER)
    {
        sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
        return;
    }

    switch (reason)
    {
    case SDHCI_RESET_FOR_INIT:
        sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
        break;
    case SDHCI_RESET_FOR_REQUEST_ERROR:
    case SDHCI_RESET_FOR_TUNING_ABORT:
    case SDHCI_RESET_FOR_CARD_REMOVED:
    case SDHCI_RESET_FOR_CQE_RECOVERY:
        sdhci_do_reset(host, SDHCI_RESET_CMD);
        sdhci_do_reset(host, SDHCI_RESET_DATA);
        break;
    case SDHCI_RESET_FOR_REQUEST_ERROR_DATA_ONLY:
        sdhci_do_reset(host, SDHCI_RESET_DATA);
        break;
    }
}

#define sdhci_reset_for(h, r) sdhci_reset_for_reason((h), SDHCI_RESET_FOR_##r)

static void sdhci_reset_for_all(struct sdhci_host *host)
{
    if (sdhci_do_reset(host, SDHCI_RESET_ALL))
    {
        if (host->flags & (SDHCI_USE_SDMA))
        {
            if (host->ops->enable_dma)
                host->ops->enable_dma(host);
        }
        /* Resetting the controller clears many */
        host->preset_enabled = RT_FALSE;
    }
}


static void sdhci_runtime_pm_bus_on(struct sdhci_host *host)
{
    if (host->bus_on)
        return;
    host->bus_on = RT_TRUE;
}

static void sdhci_runtime_pm_bus_off(struct sdhci_host *host)
{
    if (!host->bus_on)
        return;
    host->bus_on = RT_FALSE;
}

void sdhci_reset(struct sdhci_host *host, rt_uint8_t mask)
{
    ssize_t timeout;

    sdhci_writeb(host, mask, SDHCI_SOFTWARE_RESET);

    if (mask & SDHCI_RESET_ALL)
    {
        host->clock = 0;
        /* Reset-all turns off SD Bus Power */
        if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
            sdhci_runtime_pm_bus_off(host);
    }

    timeout = rt_tick_from_millisecond(150);
    while (1)
    {
        timeout = timeout - rt_tick_get();


        if (!(sdhci_readb(host, SDHCI_SOFTWARE_RESET) & mask))
            break;
        if (timeout < 0)
        {
            rt_kprintf("%s: Reset 0x%x never completed.\n",
                       mmc_hostname(host->mmc), (int)mask);
            sdhci_dumpregs(host);
            return;
        }
        rt_hw_us_delay(10);
    }
}

/********************************************************* */
/*                      data                               */
/********************************************************* */
static void sdhci_initialize_data(struct sdhci_host    *host,
                                  struct rt_mmcsd_data *data)
{
    /* Sanity checks */
    LOG_D(data->blksize * data->blks > 524288);
    LOG_D(data->blksize > host->mmc->max_blk_size);
    LOG_D(data->blks > 65535);

    host->data               = data;
    host->data_early         = 0;
    host->data->bytes_xfered = 0;
}

static rt_ubase_t sdhci_sdma_address(struct sdhci_host *host)
{
    return (rt_ubase_t)rt_kmem_v2p(host->data->buf);
}

static void sdhci_set_adma_addr(struct sdhci_host *host, rt_uint32_t addr)
{
    sdhci_writel(host, lower_32_bits(addr), SDHCI_ADMA_ADDRESS);
    if (host->flags & SDHCI_USE_64_BIT_DMA)
        sdhci_writel(host, upper_32_bits(addr), SDHCI_ADMA_ADDRESS_HI);
}

static void sdhci_set_sdma_addr(struct sdhci_host *host, rt_uint32_t addr)
{
    if (host->v4_mode)
        sdhci_set_adma_addr(host, addr);
    else
        sdhci_writel(host, addr, SDHCI_DMA_ADDRESS);
}

static void sdhci_config_dma(struct sdhci_host *host)
{
    rt_uint8_t  ctrl;
    rt_uint16_t ctrl2;

    if (host->version < SDHCI_SPEC_200)
        return;

    ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);

    /*
     * Always adjust the DMA selection as some controllers
     * (e.g. JMicron) can't do PIO properly when the selection
     * is ADMA.
     */
    ctrl &= ~SDHCI_CTRL_DMA_MASK;
    if (!(host->flags & SDHCI_REQ_USE_DMA))
        goto out;

    /* Note if DMA Select is zero then SDMA is selected */
    if (host->flags & SDHCI_USE_64_BIT_DMA)
    {
        /*
         * If v4 mode, all supported DMA can be 64-bit addressing if
         * controller supports 64-bit system address, otherwise only
         * ADMA can support 64-bit addressing.
         */
        if (host->v4_mode)
        {
            ctrl2  = sdhci_readw(host, SDHCI_HOST_CONTROL2);
            ctrl2 |= SDHCI_CTRL_64BIT_ADDR;
            sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);
        }
    }

out:
    sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}

static inline void sdhci_set_block_info(struct sdhci_host    *host,
                                        struct rt_mmcsd_data *data)
{
    /* Set the DMA boundary value and block size */
    sdhci_writew(host,
                 SDHCI_MAKE_BLKSZ(7, data->blksize),
                 SDHCI_BLOCK_SIZE);
    /*
     * For Version 4.10 onwards, if v4 mode is enabled, 32-bit Block Count
     * can be supported, in that case 16-bit block count register must be 0.
     */
    if (host->version >= SDHCI_SPEC_410 && host->v4_mode && (host->quirks2 & SDHCI_QUIRK2_USE_32BIT_BLK_CNT))
    {
        if (sdhci_readw(host, SDHCI_BLOCK_COUNT))
            sdhci_writew(host, 0, SDHCI_BLOCK_COUNT);
        sdhci_writew(host, data->blks, SDHCI_32BIT_BLK_CNT);
    }
    else
    {
        sdhci_writew(host, data->blks, SDHCI_BLOCK_COUNT);
    }
}

static void sdhci_set_transfer_irqs(struct sdhci_host *host)
{
    rt_uint32_t pio_irqs = SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL;
    rt_uint32_t dma_irqs = SDHCI_INT_DMA_END;

    if (host->flags & SDHCI_REQ_USE_DMA)
        host->ier = (host->ier & ~pio_irqs) | dma_irqs;
    else
        host->ier = (host->ier & ~dma_irqs) | pio_irqs;

    if (host->flags & (SDHCI_AUTO_CMD23 | SDHCI_AUTO_CMD12))
        host->ier |= SDHCI_INT_AUTO_CMD_ERR;
    else
        host->ier &= ~SDHCI_INT_AUTO_CMD_ERR;
    sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
    sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

static void sdhci_prepare_data(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    struct rt_mmcsd_data *data = cmd->data;

    sdhci_initialize_data(host, data);

    if (host->flags & SDHCI_USE_SDMA)
    {
        unsigned int length_mask, offset_mask;

        host->flags |= SDHCI_REQ_USE_DMA;

        /*
         * FIXME: This doesn't account for merging when mapping the
         * scatterlist.
         *
         * The assumption here being that alignment and lengths are
         * the same after DMA mapping to device address space.
         */
        length_mask = 0;
        offset_mask = 0;
        if (host->quirks & SDHCI_QUIRK_32BIT_DMA_SIZE)
            length_mask = 3;
        if (host->quirks & SDHCI_QUIRK_32BIT_DMA_ADDR)
            offset_mask = 3;


        if (length_mask | offset_mask)
        {
            host->flags &= ~SDHCI_REQ_USE_DMA;
        }
    }

    sdhci_config_dma(host);

    if (host->flags & SDHCI_REQ_USE_DMA)
    {
        if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE)
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
        else
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data->buf, data->blks * data->blksize);

        sdhci_set_sdma_addr(host, sdhci_sdma_address(host));
    }

    if (!(host->flags & SDHCI_REQ_USE_DMA))
    {
        host->blocks = data->blks;
    }

    sdhci_set_transfer_irqs(host);

    sdhci_set_block_info(host, data);
}

static void sdhci_set_mrq_done(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    int i;

    for (i = 0; i < SDHCI_MAX_MRQS; i++)
    {
        if (host->mrqs_done[i] == mrq)
        {
            LOG_D(1);
            return;
        }
    }

    for (i = 0; i < SDHCI_MAX_MRQS; i++)
    {
        if (!host->mrqs_done[i])
        {
            host->mrqs_done[i] = mrq;
            break;
        }
    }

    LOG_D(i >= SDHCI_MAX_MRQS);
}

static inline rt_bool_t sdhci_defer_done(struct sdhci_host   *host,
                                         struct rt_mmcsd_req *mrq)
{
    struct rt_mmcsd_data *data = mrq->data;

    return host->pending_reset || host->always_defer_done || ((host->flags & SDHCI_REQ_USE_DMA) && data && data->host_cookie == COOKIE_MAPPED);
}


/********************************************************* */
/*                        pio                              */
/********************************************************* */

static void sdhci_read_block_pio(struct sdhci_host *host,void **buf)
{
    rt_uint32_t scratch;
    size_t      len;
    rt_uint32_t blksize = host->data->blksize;
    while (blksize)
    {
        len = min(4U, blksize);

        scratch = sdhci_readl(host, SDHCI_BUFFER);
        rt_memcpy(*buf, &scratch, len);

        *buf     += len;
        blksize -= len;
    }
}

static void sdhci_write_block_pio(struct sdhci_host *host,void **buf)
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
        sdhci_writel(host, scratch, SDHCI_BUFFER);
    }
}

static void sdhci_transfer_pio(struct sdhci_host *host)
{
    rt_uint32_t mask;

    if (host->blocks == 0)
        return;

    if (host->data->flags & DATA_DIR_READ)
        mask = SDHCI_DATA_AVAILABLE;
    else
        mask = SDHCI_SPACE_AVAILABLE;

    /*
     * Some controllers (JMicron JMB38x) mess up the buffer bits
     * for transfers < 4 bytes. As long as it is just one block,
     * we can ignore the bits.
     */
    if ((host->quirks & SDHCI_QUIRK_BROKEN_SMALL_PIO) && (host->data->blks == 1))
    {
        mask = ~0;
    }
    void *buf = (void *)host->data->buf;
    while (sdhci_readl(host, SDHCI_PRESENT_STATE) & mask)
    {
        if (host->quirks & SDHCI_QUIRK_PIO_NEEDS_DELAY)
            rt_hw_us_delay(100);

        if (host->data->flags & DATA_DIR_READ)
            sdhci_read_block_pio(host,&buf);
        else
            sdhci_write_block_pio(host,&buf);

        host->data->blks--;
        if (host->data->blks == 0)
            break;

        /* host->data->buf += host->data->blksize;*/
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

static rt_bool_t sdhci_preset_needed(struct sdhci_host *host, unsigned char timing)
{
    return !(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN) && sdhci_timing_has_preset(timing);
}

static rt_bool_t sdhci_presetable_values_change(struct sdhci_host *host, struct rt_mmcsd_io_cfg *ios)
{
    /*
     * Preset Values are: Driver Strength, Clock Generator and SDCLK/RCLK
     * Frequency. Check if preset values need to be enabled, or the Driver
     * Strength needs updating. Note, clock changes are handled separately.
     */
    return !host->preset_enabled && (sdhci_preset_needed(host, ios->timing) || host->drv_type != ios->drv_type);
}


static void sdhci_enable_preset_value(struct sdhci_host *host, rt_bool_t enable)
{
    /* Host Controller v3.00 defines preset value registers */
    if (host->version < SDHCI_SPEC_300)
        return;

    /*
     * We only enable or disable Preset Value if they are not already
     * enabled or disabled respectively. Otherwise, we bail out.
     */
    if (host->preset_enabled != enable)
    {
        rt_uint16_t ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);

        if (enable)
            ctrl |= SDHCI_CTRL_PRESET_VAL_ENABLE;
        else
            ctrl &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;

        sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);

        if (enable)
            host->flags |= SDHCI_PV_ENABLED;
        else
            host->flags &= ~SDHCI_PV_ENABLED;

        host->preset_enabled = enable;
    }
}

static void sdhci_set_power_reg(struct sdhci_host *host, unsigned char mode,
                                unsigned short vdd)
{
    struct mmc_host *mmc = host->mmc;

    mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);

    if (mode != MMC_POWER_OFF)
        sdhci_writeb(host, SDHCI_POWER_ON, SDHCI_POWER_CONTROL);
    else
        sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);
}

void sdhci_set_power_noreg(struct sdhci_host *host, unsigned char mode,
                           unsigned short vdd)
{
    rt_uint8_t pwr = 0;

    if (mode != MMC_POWER_OFF)
    {
        switch (1 << vdd)
        {
        case MMC_VDD_165_195:
        /*
         * Without a regulator, SDHCI does not support 2.0v
         * so we only get here if the driver deliberately
         * added the 2.0v range to ocr_avail. Map it to 1.8v
         * for the purpose of turning on the power.
         */
        case MMC_VDD_20_21:
            pwr = SDHCI_POWER_180;
            break;
        case MMC_VDD_29_30:
        case MMC_VDD_30_31:
            pwr = SDHCI_POWER_300;
            break;
        case MMC_VDD_32_33:
        case MMC_VDD_33_34:
        /*
         * 3.4 ~ 3.6V are valid only for those platforms where it's
         * known that the voltage range is supported by hardware.
         */
        case MMC_VDD_34_35:
        case MMC_VDD_35_36:
            pwr = SDHCI_POWER_330;
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
        sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);
        if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
            sdhci_runtime_pm_bus_off(host);
    }
    else
    {
        /*
         * Spec says that we should clear the power reg before setting
         * a new value. Some controllers don't seem to like this though.
         */
        if (!(host->quirks & SDHCI_QUIRK_SINGLE_POWER_WRITE))
            sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);

        /*
         * At least the Marvell CaFe chip gets confused if we set the
         * voltage and set turn on power at the same time, so set the
         * voltage first.
         */
        if (host->quirks & SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER)
            sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

        pwr |= SDHCI_POWER_ON;

        sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

        if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
            sdhci_runtime_pm_bus_on(host);

        /*
         * Some controllers need an extra 10ms delay of 10ms before
         * they can apply clock after applying power
         */
        if (host->quirks & SDHCI_QUIRK_DELAY_AFTER_POWER)
            rt_thread_mdelay(10);
    }
}

void sdhci_set_power(struct sdhci_host *host, unsigned char mode,
                     unsigned short vdd)
{
    if (!host->mmc->supply.vmmc)
        sdhci_set_power_noreg(host, mode, vdd);
    else
        sdhci_set_power_reg(host, mode, vdd);
}


int sdhci_start_signal_voltage_switch(struct mmc_host        *mmc,
                                      struct rt_mmcsd_io_cfg *ios)
{
    struct sdhci_host *host = mmc_priv(mmc);
    rt_uint16_t        ctrl;
    int                ret;

    /*
     * Signal Voltage Switching is only applicable for Host Controllers
     * v3.00 and above.
     */
    if (host->version < SDHCI_SPEC_300)
        return 0;

    ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);

    switch (ios->signal_voltage)
    {
    case MMC_SIGNAL_VOLTAGE_330:
        if (!(host->flags & SDHCI_SIGNALING_330))
            return -EINVAL;
        /* Set 1.8V Signal Enable in the Host Control2 register to 0 */
        ctrl &= ~SDHCI_CTRL_VDD_180;
        sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);

        if (!mmc->supply.vqmmc)
        {
            ret = mmc_regulator_set_vqmmc(mmc, ios);
            if (ret < 0)
            {
                return -EIO;
            }
        }
        /* Wait for 5ms */
        rt_thread_mdelay(5);
        /* 3.3V regulator output should be stable within 5 ms */
        ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
        if (!(ctrl & SDHCI_CTRL_VDD_180))
            return 0;
        return -EAGAIN;
    case MMC_SIGNAL_VOLTAGE_180:
        if (!(host->flags & SDHCI_SIGNALING_180))
            return -EINVAL;
        if (!mmc->supply.vqmmc)
        {
            ret = mmc_regulator_set_vqmmc(mmc, ios);
            if (ret < 0)
            {
                LOG_D("%s: Switching to 1.8V signalling voltage failed\n",
                      mmc_hostname(mmc));
                return -EIO;
            }
        }

        /*
         * Enable 1.8V Signal Enable in the Host Control2
         * register
         */
        ctrl |= SDHCI_CTRL_VDD_180;
        sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);

        /* Some controller need to do more when switching */
        if (host->ops->voltage_switch)
            host->ops->voltage_switch(host);

        /* 1.8V regulator output should be stable within 5 ms */
        ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
        if (ctrl & SDHCI_CTRL_VDD_180)
            return 0;

        LOG_D("%s: 1.8V regulator output did not become stable\n",
              mmc_hostname(mmc));

        return -EAGAIN;
    case MMC_SIGNAL_VOLTAGE_120:
        if (!(host->flags & SDHCI_SIGNALING_120))
            return -EINVAL;
        if (!mmc->supply.vqmmc)
        {
            ret = mmc_regulator_set_vqmmc(mmc, ios);
            if (ret < 0)
            {
                LOG_D("%s: Switching to 1.2V signalling voltage failed\n",
                      mmc_hostname(mmc));
                return -EIO;
            }
        }
        return 0;
    default:
        /* No signal voltage switch required */
        return 0;
    }
}


static int sdhci_get_cd(struct mmc_host *mmc)
{
    struct sdhci_host *host    = mmc_priv(mmc);
    int                gpio_cd = mmc_gpio_get_cd(mmc);

    if (host->flags & SDHCI_DEVICE_DEAD)
        return 0;

    /* If nonremovable, assume that the card is always present. */
    if (!mmc_card_is_removable(mmc))
        return 1;

    /*
     * Try slot gpio detect, if defined it take precedence
     * over build in controller functionality
     */
    if (gpio_cd >= 0)
        return !!gpio_cd;

    /* If polling, assume that the card is always present. */
    if (host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION)
        return 1;

    /* Host native card detect */
    return !!(sdhci_readl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT);
}

static int sdhci_check_ro(struct sdhci_host *host)
{
    int       is_readonly;
    rt_base_t flags;
    flags = rt_spin_lock_irqsave(&host->lock);

    if (host->flags & SDHCI_DEVICE_DEAD)
        is_readonly = 0;
    else if (host->ops->get_ro)
        is_readonly = host->ops->get_ro(host);
    else if (mmc_can_gpio_ro(host->mmc))
        is_readonly = mmc_gpio_get_ro(host->mmc);
    else
        is_readonly = !(sdhci_readl(host, SDHCI_PRESENT_STATE)
                        & SDHCI_WRITE_PROTECT);

    rt_spin_unlock_irqrestore(&host->lock, flags);

    /* This quirk needs to be replaced by a callback-function later */
    return host->quirks & SDHCI_QUIRK_INVERTED_WRITE_PROTECT ? !is_readonly : is_readonly;
}

#define SAMPLE_COUNT 5
static int sdhci_get_ro(struct mmc_host *mmc)
{
    struct sdhci_host *host = mmc_priv(mmc);
    int                i, ro_count;

    if (!(host->quirks & SDHCI_QUIRK_UNSTABLE_RO_DETECT))
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

static void sdhci_enable_sdio_irq_nolock(struct sdhci_host *host, int enable)
{
    if (!(host->flags & SDHCI_DEVICE_DEAD))
    {
        if (enable)
            host->ier |= SDHCI_INT_CARD_INT;
        else
            host->ier &= ~SDHCI_INT_CARD_INT;

        sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
        sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
    }
}

static void sdhci_ack_sdio_irq(struct mmc_host *mmc)
{
    rt_base_t          flags;
    struct sdhci_host *host = mmc_priv(mmc);
    flags                   = rt_spin_lock_irqsave(&host->lock);
    sdhci_enable_sdio_irq_nolock(host, RT_TRUE);
    rt_spin_unlock_irqrestore(&host->lock, flags);
}

static void sdhci_del_timer(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    if (sdhci_data_line_cmd(mrq->cmd))
        rt_timer_stop(&host->data_timer);
    else
        rt_timer_stop(&host->timer);
}

static unsigned int sdhci_target_timeout(struct sdhci_host    *host,
                                         struct rt_mmcsd_cmd  *cmd,
                                         struct rt_mmcsd_data *data)
{
    unsigned int target_timeout;

    /* timeout in us */
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

            /*
             * data->timeout_clks is in units of clock cycles.
             * host->clock is in Hz.  target_timeout is in us.
             * Hence, us = 1000000 * cycles / Hz.  Round up.
             */
            val = 1000000ULL * data->timeout_clks;
            if (do_div(val, host->clock))
                target_timeout++;
            target_timeout += val;
        }
    }

    return target_timeout;
}

static rt_uint8_t sdhci_calc_timeout(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd,
                                     rt_bool_t *too_big)
{
    rt_uint8_t            count;
    struct rt_mmcsd_data *data;
    unsigned              target_timeout, current_timeout;

    *too_big = RT_FALSE;

    /*
     * If the host controller provides us with an incorrect timeout
     * value, just skip the check and use the maximum. The hardware may take
     * longer to time out, but that's much better than having a too-short
     * timeout value.
    */
    if (host->quirks & SDHCI_QUIRK_BROKEN_TIMEOUT_VAL)
        return host->max_timeout_count;

    /* Unspecified command, assume max */
    if (cmd == NULL)
        return host->max_timeout_count;

    data = cmd->data;
    /* Unspecified timeout, assume max */
    if (!data && !cmd->busy_timeout)
        return host->max_timeout_count;

    /* timeout in us */
    target_timeout = sdhci_target_timeout(host, cmd, data);

    /*
     * Figure out needed cycles.
     * We do this in steps in order to fit inside a 32 bit int.
     * The first step is the minimum timeout, which will have a
     * minimum resolution of 6 bits:
     * (1) 2^13*1000 > 2^22,
     * (2) host->timeout_clk < 2^16
     *     =>
     *     (1) / (2) > 2^6
     */
    count           = 0;
    current_timeout = (1 << 13) * 1000 / host->timeout_clk;
    while (current_timeout < target_timeout)
    {
        count++;
        current_timeout <<= 1;
        if (count > host->max_timeout_count)
        {
            if (!(host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT))
                LOG_D("Too large timeout 0x%x requested for CMD%d!\n",
                      count, cmd->cmd_code);
            count    = host->max_timeout_count;
            *too_big = RT_TRUE;
            break;
        }
    }

    return count;
}

static void sdhci_calc_sw_timeout(struct sdhci_host   *host,
                                  struct rt_mmcsd_cmd *cmd)
{
    struct rt_mmcsd_data   *data      = cmd->data;
    struct mmc_host        *mmc       = host->mmc;
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
        /* multiply by '2' to account for any unknowns */
        transfer_time = transfer_time * 2;
        /* calculate timeout for the entire data */
        host->data_timeout = data->blks * target_timeout + transfer_time;
    }
    else
    {
        host->data_timeout = target_timeout;
    }

    if (host->data_timeout)
        host->data_timeout += MMC_CMD_TRANSFER_TIME;
}


void __sdhci_set_timeout(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    rt_bool_t  too_big = RT_FALSE;
    rt_uint8_t count   = sdhci_calc_timeout(host, cmd, &too_big);

    if (too_big && host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT)
    {
        sdhci_calc_sw_timeout(host, cmd);
        sdhci_set_data_timeout_irq(host, RT_FALSE);
    }
    else if (!(host->ier & SDHCI_INT_DATA_TIMEOUT))
    {
        sdhci_set_data_timeout_irq(host, RT_FALSE);
    }

    sdhci_writeb(host, count, SDHCI_TIMEOUT_CONTROL);
}

static void sdhci_set_timeout(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    if (host->ops->set_timeout)
        host->ops->set_timeout(host, cmd);
    else
        __sdhci_set_timeout(host, cmd);
}

static void sdhci_mod_timer(struct sdhci_host *host, struct rt_mmcsd_req *mrq,
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

static void __sdhci_finish_mrq(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
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

static void sdhci_finish_mrq(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
    __sdhci_finish_mrq(host, mrq);

    rt_workqueue_submit_work(host->complete_wq, &host->complete_work, 0);
}

static void sdhci_error_out_mrqs(struct sdhci_host *host, int err)
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

static void sdhci_card_event(struct mmc_host *mmc)
{
    struct sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        flags;
    int                present;

    /* First check if client has provided their own card event */
    if (host->ops->card_event)
        host->ops->card_event(host);

    present = mmc->ops->get_cd(mmc);

    flags = rt_spin_lock_irqsave(&host->lock);

    /* Check sdhci_has_requests() first in case we are runtime suspended */
    if (sdhci_has_requests(host) && !present)
    {
        rt_kprintf("%s: Card removed during transfer!\n",
                   mmc_hostname(mmc));
        rt_kprintf("%s: Resetting controller.\n",
                   mmc_hostname(mmc));

        sdhci_do_reset(host, SDHCI_RESET_CMD);
        sdhci_do_reset(host, SDHCI_RESET_DATA);
        sdhci_error_out_mrqs(host, -ENOMEDIUM);
    }

    rt_spin_unlock_irqrestore(&host->lock, flags);
}

static int sdhci_card_busy(struct mmc_host *mmc)
{
    struct sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        present_state;

    /* Check whether DAT[0] is 0 */
    present_state = sdhci_readl(host, SDHCI_PRESENT_STATE);

    return !(present_state & SDHCI_DATA_0_LVL_MASK);
}


static int sdhci_prepare_hs400_tuning(struct mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    struct sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        flags;

    flags        = rt_spin_lock_irqsave(&host->lock);
    host->flags |= SDHCI_HS400_TUNING;
    rt_spin_unlock_irqrestore(&host->lock, flags);

    return 0;
}


static void sdhci_set_transfer_mode(struct sdhci_host   *host,
                                    struct rt_mmcsd_cmd *cmd)
{
    rt_uint16_t           mode = 0;
    struct rt_mmcsd_data *data = cmd->data;

    if (data == NULL)
    {
        if (host->quirks2 & SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD)
        {
            /* must not clear SDHCI_TRANSFER_MODE when tuning */
            if (!mmc_op_tuning(cmd->cmd_code))
                sdhci_writew(host, 0x0, SDHCI_TRANSFER_MODE);
        }
        else
        {
            /* clear Auto CMD settings for no data CMDs */
            mode = sdhci_readw(host, SDHCI_TRANSFER_MODE);
            sdhci_writew(host, mode & ~(SDHCI_TRNS_AUTO_CMD12 | SDHCI_TRNS_AUTO_CMD23), SDHCI_TRANSFER_MODE);
        }
        return;
    }


    if (!(host->quirks2 & SDHCI_QUIRK2_SUPPORT_SINGLE))
        mode = SDHCI_TRNS_BLK_CNT_EN;

    if (mmc_op_multi(cmd->cmd_code) || data->blks > 1)
    {
        mode = SDHCI_TRNS_BLK_CNT_EN | SDHCI_TRNS_MULTI;
        sdhci_auto_cmd_select(host, cmd, &mode);
        if (sdhci_auto_cmd23(host, cmd->mrq))
            sdhci_writel(host, cmd->mrq->sbc->arg, SDHCI_ARGUMENT2);
    }

    if (data->flags & DATA_DIR_READ)
        mode |= SDHCI_TRNS_READ;
    if (host->flags & SDHCI_REQ_USE_DMA)
        mode |= SDHCI_TRNS_DMA;

    sdhci_writew(host, mode, SDHCI_TRANSFER_MODE);
}

static rt_bool_t sdhci_send_command(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    int           flags;
    rt_uint32_t   mask;
    unsigned long timeout;
    /* Initially, a command has no error */
    cmd->err = 0;

    if ((host->quirks2 & SDHCI_QUIRK2_STOP_WITH_TC) && cmd->cmd_code == MMC_STOP_TRANSMISSION)
        cmd->flags |= MMC_RSP_BUSY;

    mask = SDHCI_CMD_INHIBIT;
    if (sdhci_data_line_cmd(cmd))
        mask |= SDHCI_DATA_INHIBIT;

    /* We shouldn't wait for data inihibit for stop commands, even
       though they might use busy signaling */
    if (cmd->mrq->data && (cmd == cmd->mrq->data->stop))
        mask &= ~SDHCI_DATA_INHIBIT;

    if (sdhci_readl(host, SDHCI_PRESENT_STATE) & mask)
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
        if (host->use_external_dma)
            sdhci_external_dma_prepare_data(host, cmd);
        else
            sdhci_prepare_data(host, cmd);
    }
    sdhci_writel(host, cmd->arg, SDHCI_ARGUMENT);

    sdhci_set_transfer_mode(host, cmd);

    if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY))
    {
        /*
         * This does not happen in practice because 136-bit response
         * commands never have busy waiting, so rather than complicate
         * the error path, just remove busy waiting and continue.
         */
        cmd->flags &= ~MMC_RSP_BUSY;
    }

    if (!(cmd->flags & MMC_RSP_PRESENT))
        flags = SDHCI_CMD_RESP_NONE;
    else if (cmd->flags & MMC_RSP_136)
        flags = SDHCI_CMD_RESP_LONG;
    else if (cmd->flags & MMC_RSP_BUSY)
        flags = SDHCI_CMD_RESP_SHORT_BUSY;
    else
        flags = SDHCI_CMD_RESP_SHORT;

    if (cmd->flags & MMC_RSP_CRC)
        flags |= SDHCI_CMD_CRC;
    if (cmd->flags & MMC_RSP_OPCODE)
        flags |= SDHCI_CMD_INDEX;

    /* CMD19 is special in that the Data Present Select should be set */
    if (cmd->data || mmc_op_tuning(cmd->cmd_code))
        flags |= SDHCI_CMD_DATA;

    timeout = rt_tick_get();
    if (host->data_timeout)
        timeout += rt_tick_from_millisecond(host->data_timeout * 1000);
    else if (!cmd->data && cmd->busy_timeout > 9000)
        timeout += DIV_ROUND_UP(cmd->busy_timeout, 1000) * RT_TICK_PER_SECOND + RT_TICK_PER_SECOND;
    else
        timeout += 10 * RT_TICK_PER_SECOND;
    sdhci_mod_timer(host, cmd->mrq, timeout);

    if (host->use_external_dma)
        sdhci_external_dma_pre_transfer(host, cmd);

    sdhci_writew(host, SDHCI_MAKE_CMD(cmd->cmd_code, flags), SDHCI_COMMAND);
    return RT_TRUE;
}

/********************************************************* */
/*                        dma                              */
/********************************************************* */
static void __sdhci_finish_data(struct sdhci_host *host, rt_bool_t sw_data_timeout)
{
    struct rt_mmcsd_cmd  *data_cmd = host->data_cmd;
    struct rt_mmcsd_data *data     = host->data;

    host->data     = NULL;
    host->data_cmd = NULL;

    /*
     * The controller needs a reset of internal state machines upon error
     * conditions.
     */
    if (data->err)
    {
        if (!host->cmd || host->cmd == data_cmd)
            sdhci_reset_for(host, REQUEST_ERROR);
        else
            sdhci_reset_for(host, REQUEST_ERROR_DATA_ONLY);
    }

    /*
     * The specification states that the block count register must
     * be updated, but it does not specify at what point in the
     * data flow. That makes the register entirely useless to read
     * back so we have to assume that nothing made it to the card
     * in the event of an error.
     */
    if (data->err)
    {
        data->bytes_xfered = 0;
    }
    else
    {
        data->bytes_xfered = data->blksize * data->blks;
    }
    /*
     * Need to send CMD12 if -
     * a) open-ended multiblock transfer not using auto CMD12 (no CMD23)
     * b) error in multiblock transfer
     */
    if (data->stop && ((!data->mrq->sbc && !sdhci_auto_cmd12(host, data->mrq)) || data->err))
    {
        /*
         * 'cap_cmd_during_tfr' request must not use the command line
         * after mmc_command_done() has been called. It is upper layer's
         * responsibility to send the stop command if required.
         */
        if (data->mrq->cap_cmd_during_tfr)
        {
            __sdhci_finish_mrq(host, data->mrq);
        }
        else
        {
            /* Avoid triggering warning in sdhci_send_command() */
            host->cmd = NULL;
            if (!sdhci_send_command(host, data->stop))
            {
                if (sw_data_timeout)
                {
                    /*
                     * This is anyway a sw data timeout, so
                     * give up now.
                     */
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

static void sdhci_finish_data(struct sdhci_host *host)
{
    __sdhci_finish_data(host, RT_FALSE);
}


/********************************************************* */
/*                     irq                                 */
/********************************************************* */
static void sdhci_data_irq(struct sdhci_host *host, rt_uint32_t intmask)
{
    rt_uint32_t command;
    /*
     * CMD19 generates _only_ Buffer Read Ready interrupt if
     * use sdhci_send_tuning.
     * Need to exclude this case: PIO mode and use mmc_send_tuning,
     * If not, sdhci_transfer_pio will never be called, make the
     * SDHCI_INT_DATA_AVAIL always there, stuck in irq storm.
     */
    if (intmask & SDHCI_INT_DATA_AVAIL && !host->data)
    {
        command = SDHCI_GET_CMD(sdhci_readw(host, SDHCI_COMMAND));
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

        /*
         * The "data complete" interrupt is also used to
         * indicate that a busy state has ended. See comment
         * above in sdhci_cmd_irq().
         */
        if (data_cmd && (data_cmd->flags & MMC_RSP_BUSY))
        {
            if (intmask & SDHCI_INT_DATA_TIMEOUT)
            {
                host->data_cmd = NULL;
                data_cmd->err  = -ETIMEDOUT;
                __sdhci_finish_mrq(host, data_cmd->mrq);
                return;
            }
            if (intmask & SDHCI_INT_DATA_END)
            {
                host->data_cmd = NULL;
                /*
                 * Some cards handle busy-end interrupt
                 * before the command completed, so make
                 * sure we do things in the proper order.
                 */
                if (host->cmd == data_cmd)
                    return;

                __sdhci_finish_mrq(host, data_cmd->mrq);
                return;
            }
        }

        /*
         * SDHCI recovers from errors by resetting the cmd and data
         * circuits. Until that is done, there very well might be more
         * interrupts, so ignore them in that case.
         */
        if (host->pending_reset)
            return;
        rt_kprintf("%s: Got data interrupt 0x%08x even though no data operation was in progress.\n",
                   mmc_hostname(host->mmc), (unsigned)intmask);
        sdhci_dumpregs(host);

        return;
    }

    if (intmask & SDHCI_INT_DATA_TIMEOUT)
        host->data->err = -ETIMEDOUT;
    else if (intmask & SDHCI_INT_DATA_END_BIT)
        host->data->err = -EILSEQ;
    else if ((intmask & SDHCI_INT_DATA_CRC) && SDHCI_GET_CMD(sdhci_readw(host, SDHCI_COMMAND)) != MMC_BUS_TEST_R)
    {
        host->data->err = -EILSEQ;
    }
    if (host->data->err)
    {
        sdhci_finish_data(host);
    }
    else
    {
        if (intmask & (SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL))
            sdhci_transfer_pio(host);

        /*
         * We currently don't do anything fancy with DMA
         * boundaries, but as we can't disable the feature
         * we need to at least restart the transfer.
         *
         * According to the spec sdhci_readl(host, SDHCI_DMA_ADDRESS)
         * should return a valid address to continue from, but as
         * some controllers are faulty, don't trust them.
         */
        if (intmask & SDHCI_INT_DMA_END)
        {
            rt_uint32_t dmastart, dmanow;

            dmastart = sdhci_sdma_address(host);
            dmanow   = dmastart + host->data->bytes_xfered;
            /*
             * Force update to the next DMA block boundary.
             */
            dmanow                   = (dmanow & ~((rt_uint32_t)SDHCI_DEFAULT_BOUNDARY_SIZE - 1)) + SDHCI_DEFAULT_BOUNDARY_SIZE;
            host->data->bytes_xfered = dmanow - dmastart;
            LOG_D("DMA base %pad, transferred 0x%06x bytes, next %pad\n",
                  &dmastart, host->data->bytes_xfered, &dmanow);
            sdhci_set_sdma_addr(host, dmanow);
        }

        if (intmask & SDHCI_INT_DATA_END)
        {
            if (host->cmd == host->data_cmd)
            {
                /*
                 * Data managed to finish before the
                 * command completed. Make sure we do
                 * things in the proper order.
                 */
                host->data_early = 1;
            }
            else
            {
                sdhci_finish_data(host);
            }
        }
    }
}

static void sdhci_read_rsp_136(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
    int i, reg;

    for (i = 0; i < 4; i++)
    {
        reg          = SDHCI_RESPONSE + (3 - i) * 4;
        cmd->resp[i] = sdhci_readl(host, reg);
    }

    if (host->quirks2 & SDHCI_QUIRK2_RSP_136_HAS_CRC)
        return;

    /* CRC is stripped so we need to do some shifting */
    for (i = 0; i < 4; i++)
    {
        cmd->resp[i] <<= 8;
        if (i != 3)
            cmd->resp[i] |= cmd->resp[i + 1] >> 24;
    }
}

static void sdhci_finish_command(struct sdhci_host *host)
{
    struct rt_mmcsd_cmd *cmd = host->cmd;

    host->cmd = NULL;

    if (cmd->flags & MMC_RSP_PRESENT)
    {
        if (cmd->flags & MMC_RSP_136)
        {
            sdhci_read_rsp_136(host, cmd);
        }
        else
        {
            cmd->resp[0] = sdhci_readl(host, SDHCI_RESPONSE);
        }
    }
    /*
     * The host can send and interrupt when the busy state has
     * ended, allowing us to wait without wasting CPU cycles.
     * The busy signal uses DAT0 so this is similar to waiting
     * for data to complete.
     *
     * Note: The 1.0 specification is a bit ambiguous about this
     *       feature so there might be some problems with older
     *       controllers.
     */
    if (cmd->flags & MMC_RSP_BUSY)
    {
        if (cmd->data)
        {
            LOG_D("Cannot wait for busy signal when also doing a data transfer");
        }
        else if (!(host->quirks & SDHCI_QUIRK_NO_BUSY_IRQ) && cmd == host->data_cmd)
        {
            /* Command complete before busy is ended */
            return;
        }
    }

    /* Finished CMD23, now send actual command. */
    if (cmd == cmd->mrq->sbc)
    {
        if (!sdhci_send_command(host, cmd->mrq->cmd))
        {
            host->deferred_cmd = cmd->mrq->cmd;
        }
    }
    else
    {
        /* Processed actual command. */
        if (host->data && host->data_early)
            sdhci_finish_data(host);

        if (!cmd->data)
            __sdhci_finish_mrq(host, cmd->mrq);
    }
}


static void sdhci_cmd_irq(struct sdhci_host *host, rt_uint32_t intmask, rt_uint32_t *intmask_p)
{
    /* Handle auto-CMD12 error */
    if (intmask & SDHCI_INT_AUTO_CMD_ERR && host->data_cmd)
    {
        struct rt_mmcsd_req *mrq             = host->data_cmd->mrq;
        rt_uint16_t          auto_cmd_status = sdhci_readw(host, SDHCI_AUTO_CMD_STATUS);
        int                  data_err_bit    = (auto_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ? SDHCI_INT_DATA_TIMEOUT : SDHCI_INT_DATA_CRC;

        /* Treat auto-CMD12 error the same as data error */
        if (!mrq->sbc && (host->flags & SDHCI_AUTO_CMD12))
        {
            *intmask_p |= data_err_bit;
            return;
        }
    }

    if (!host->cmd)
    {
        /*
         * SDHCI recovers from errors by resetting the cmd and data
         * circuits.  Until that is done, there very well might be more
         * interrupts, so ignore them in that case.
         */
        if (host->pending_reset)
            return;
        rt_kprintf("%s: Got command interrupt 0x%08x even though no command operation was in progress.\n",
                   mmc_hostname(host->mmc), (unsigned)intmask);
        sdhci_dumpregs(host);
        return;
    }
    if (intmask & (SDHCI_INT_TIMEOUT | SDHCI_INT_CRC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX))
    {
        if (intmask & SDHCI_INT_TIMEOUT)
            host->cmd->err = -ETIMEDOUT;
        else
            host->cmd->err = -EILSEQ;

        /* Treat data command CRC error the same as data CRC error */
        if (host->cmd->data && (intmask & (SDHCI_INT_CRC | SDHCI_INT_TIMEOUT)) == SDHCI_INT_CRC)
        {
            host->cmd   = NULL;
            *intmask_p |= SDHCI_INT_DATA_CRC;
            return;
        }

        __sdhci_finish_mrq(host, host->cmd->mrq);
        return;
    }

    /* Handle auto-CMD23 error */
    if (intmask & SDHCI_INT_AUTO_CMD_ERR)
    {
        struct rt_mmcsd_req *mrq             = host->cmd->mrq;
        rt_uint16_t          auto_cmd_status = sdhci_readw(host, SDHCI_AUTO_CMD_STATUS);
        int                  err             = (auto_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ? -ETIMEDOUT : -EILSEQ;

        if (mrq->sbc && (host->flags & SDHCI_AUTO_CMD23))
        {
            mrq->sbc->err = err;
            __sdhci_finish_mrq(host, mrq);
            return;
        }
    }

    if (intmask & SDHCI_INT_RESPONSE)
        sdhci_finish_command(host);
}

static void sdhci_irq(int irq, void *dev_id)
{
    struct rt_mmcsd_req *mrqs_done[SDHCI_MAX_MRQS] = {0};
    struct sdhci_host   *host                      = dev_id;
    rt_uint32_t          intmask, mask, unexpected = 0;
    int                  max_loops = 16;
    int                  i, result;
    rt_spin_lock(&host->lock);

    if (host->runtime_suspended)
    {
        rt_spin_unlock(&host->lock);
    }

    intmask = sdhci_readl(host, SDHCI_INT_STATUS);
    if (!intmask || intmask == 0xffffffff)
    {
        result = 0;
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
        mask = intmask & (SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK | SDHCI_INT_BUS_POWER);
        sdhci_writel(host, mask, SDHCI_INT_STATUS);

        if (intmask & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE))
        {
            rt_uint32_t present = sdhci_readl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT;

            /*
             * There is a observation on i.mx esdhc.  INSERT
             * bit will be immediately set again when it gets
             * cleared, if a card is inserted.  We have to mask
             * the irq to prevent interrupt storm which will
             * freeze the system.  And the REMOVE gets the
             * same situation.
             *
             * More testing are needed here to ensure it works
             * for other platforms though.
             */
            host->ier &= ~(SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE);
            host->ier |= present ? SDHCI_INT_CARD_REMOVE : SDHCI_INT_CARD_INSERT;
            sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
            sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);

            sdhci_writel(host, intmask & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE), SDHCI_INT_STATUS);

            host->thread_isr |= intmask & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE);
            result            = RT_EOK;
        }

        if (intmask & SDHCI_INT_CMD_MASK)
            sdhci_cmd_irq(host, intmask & SDHCI_INT_CMD_MASK, &intmask);

        if (intmask & SDHCI_INT_DATA_MASK)
            sdhci_data_irq(host, intmask & SDHCI_INT_DATA_MASK);

        if (intmask & SDHCI_INT_BUS_POWER)
            rt_kprintf("%s: Card is consuming too much power!\n",
                       mmc_hostname(host->mmc));

        intmask &= ~(SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE | SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK | SDHCI_INT_ERROR | SDHCI_INT_BUS_POWER | SDHCI_INT_RETUNE | SDHCI_INT_CARD_INT);

        if (intmask)
        {
            unexpected |= intmask;
            sdhci_writel(host, intmask, SDHCI_INT_STATUS);
        }
    cont:
        intmask = sdhci_readl(host, SDHCI_INT_STATUS);
    } while (intmask && --max_loops);

    /* Determine if mrqs can be completed immediately */
    for (i = 0; i < SDHCI_MAX_MRQS; i++)
    {
        struct rt_mmcsd_req *mrq = host->mrqs_done[i];

        if (!mrq)
            continue;

        if (sdhci_defer_done(host, mrq))
        {
            result = RT_EOK;
        }
        else
        {
            mrqs_done[i]       = mrq;
            host->mrqs_done[i] = NULL;
        }
    }
out:
    if (host->deferred_cmd)
        result = RT_EOK;

    rt_spin_unlock(&host->lock);

    /* Process mrqs ready for immediate completion */
    for (i = 0; i < SDHCI_MAX_MRQS; i++)
    {
        if (!mrqs_done[i])
            continue;

        if (host->ops->request_done)
            host->ops->request_done(host, mrqs_done[i]);
        else
            mmc_request_done(host->mmc, mrqs_done[i]);
    }

    if (unexpected)
    {
        sdhci_dumpregs(host);
    }

    if (result == RT_EOK)
    {
        rt_workqueue_submit_work(host->irq_wq, &host->irq_work, 0);
    }
}

static rt_bool_t sdhci_send_command_retry(struct sdhci_host   *host,
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
            sdhci_dumpregs(host);
            cmd->err = -EIO;
            return RT_FALSE;
        }

        rt_spin_unlock_irqrestore(&host->lock, flags);

        rt_thread_mdelay(1);

        present = host->mmc->ops->get_cd(host->mmc);

        flags = rt_spin_lock_irqsave(&host->lock);

        /* A deferred command might disappear, handle that */
        if (cmd == deferred_cmd && cmd != host->deferred_cmd)
            return RT_TRUE;

        if (sdhci_present_error(host, cmd, present))
            return RT_FALSE;
    }

    if (cmd == host->deferred_cmd)
        host->deferred_cmd = NULL;

    return RT_TRUE;
}

static rt_bool_t sdhci_request_done(struct sdhci_host *host)
{
    rt_base_t            flags;
    struct rt_mmcsd_req *mrq;
    int                  i;

    flags = rt_spin_lock_irqsave(&host->lock);

    for (i = 0; i < SDHCI_MAX_MRQS; i++)
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

    /*
     * The controller needs a reset of internal state machines
     * upon error conditions.
     */
    if (sdhci_needs_reset(host, mrq))
    {
        /*
         * Do not finish until command and data lines are available for
         * reset. Note there can only be one other mrq, so it cannot
         * also be in mrqs_done, otherwise host->cmd and host->data_cmd
         * would both be null.
         */
        if (host->cmd || host->data_cmd)
        {
            rt_spin_unlock_irqrestore(&host->lock, flags);
            return RT_TRUE;
        }

        /* Some controllers need this kick or reset won't work here */
        if (host->quirks & SDHCI_QUIRK_CLOCK_BEFORE_RESET)
            /* This is to force an update */
            host->ops->set_clock(host, host->clock);

        sdhci_do_reset(host, SDHCI_RESET_CMD);
        sdhci_do_reset(host, SDHCI_RESET_DATA);

        host->pending_reset = RT_FALSE;
    }

    /*
     * Always unmap the data buffers if they were mapped by
     * sdhci_prepare_data() whenever we finish with a request.
     * This avoids leaking DMA mappings on error.
     */
    if (host->flags & SDHCI_REQ_USE_DMA)
    {
        struct rt_mmcsd_data *data = mrq->data;

        if (host->use_external_dma && data && (mrq->cmd->err || data->err))
        {
            host->mrqs_done[i] = NULL;
            sdhci_set_mrq_done(host, mrq);
        }
    }

    host->mrqs_done[i] = NULL;

    rt_spin_unlock_irqrestore(&host->lock, flags);

    if (host->ops->request_done)
        host->ops->request_done(host, mrq);
    else
        mmc_request_done(host->mmc, mrq);

    return RT_FALSE;
}


static void sdhci_thread_irq(struct rt_work *work, void *work_data)
{
    struct sdhci_host   *host = work_data;
    struct rt_mmcsd_cmd *cmd;
    rt_base_t            flags;
    rt_uint32_t          isr;

    while (!sdhci_request_done(host));

    flags = rt_spin_lock_irqsave(&host->lock);

    isr              = host->thread_isr;
    host->thread_isr = 0;

    cmd = host->deferred_cmd;
    if (cmd && !sdhci_send_command_retry(host, cmd, flags))
        sdhci_finish_mrq(host, cmd->mrq);

    rt_spin_unlock_irqrestore(&host->lock, flags);

    if (isr & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE))
    {
        struct mmc_host *mmc = host->mmc;

        mmc->ops->card_event(mmc);
    }
}


void sdhci_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
    struct sdhci_host *host = mmc_priv(mmc);
    rt_uint32_t        flags;

    flags = rt_spin_lock_irqsave(&host->lock);
    sdhci_enable_sdio_irq_nolock(host, enable);
    rt_spin_unlock_irqrestore(&host->lock, flags);
}


/********************************************************* */
/*                     request                             */
/********************************************************* */

void sdhci_request(struct mmc_host *mmc, struct rt_mmcsd_req *mrq)
{
    struct sdhci_host   *host = mmc_priv(mmc);
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
    struct sdhci_host *host = work_data;

    while (!sdhci_request_done(host));
}


/********************************************************* */
/*                     timer                               */
/********************************************************* */
static void sdhci_timeout_timer(void *parameter)
{
    struct sdhci_host *host = parameter;
    rt_base_t          flags;

    flags = rt_spin_lock_irqsave(&host->lock);

    if (host->cmd && !sdhci_data_line_cmd(host->cmd))
    {
        rt_kprintf("%s: Timeout waiting for hardware cmd interrupt.\n",
                   mmc_hostname(host->mmc));
        sdhci_dumpregs(host);

        host->cmd->err = -ETIMEDOUT;
        sdhci_finish_mrq(host, host->cmd->mrq);
    }

    rt_spin_unlock_irqrestore(&host->lock, flags);
}

static void sdhci_timeout_data_timer(void *parameter)
{
    struct sdhci_host *host = parameter;
    rt_base_t          flags;

    flags = rt_spin_lock_irqsave(&host->lock);

    if (host->data || host->data_cmd || (host->cmd && sdhci_data_line_cmd(host->cmd)))
    {
        rt_kprintf("%s: Timeout waiting for hardware interrupt.\n",
                   mmc_hostname(host->mmc));
        sdhci_dumpregs(host);

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
int sdhci_execute_tuning(struct mmc_host *mmc, rt_uint32_t opcode)
{
    struct sdhci_host *host         = mmc_priv(mmc);
    int                err          = 0;
    unsigned int       tuning_count = 0;
    rt_bool_t          hs400_tuning;

    hs400_tuning = host->flags & SDHCI_HS400_TUNING;

    if (host->tuning_mode == SDHCI_TUNING_MODE_1)
        tuning_count = host->tuning_count;

    /*
     * The Host Controller needs tuning in case of SDR104 and DDR50
     * mode, and for SDR50 mode when Use Tuning for SDR50 is set in
     * the Capabilities register.
     * If the Host Controller supports the HS200 mode then the
     * tuning function has to be executed.
     */
    switch (host->timing)
    {
    /* HS400 tuning is done in HS200 mode */
    case MMC_TIMING_MMC_HS400:
        err = -EINVAL;
        goto out;

    case MMC_TIMING_MMC_HS200:
        /*
         * Periodic re-tuning for HS400 is not expected to be needed, so
         * disable it here.
         */
        if (hs400_tuning)
            tuning_count = 0;
        break;

    case MMC_TIMING_UHS_SDR104:
    case MMC_TIMING_UHS_DDR50:
        break;

    case MMC_TIMING_UHS_SDR50:
        if (host->flags & SDHCI_SDR50_NEEDS_TUNING)
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

    sdhci_start_tuning(host);

    host->tuning_err = __sdhci_execute_tuning(host, opcode);

    sdhci_end_tuning(host);
out:
    host->flags &= ~SDHCI_HS400_TUNING;

    return err;
}

int __sdhci_execute_tuning(struct sdhci_host *host, rt_uint32_t opcode)
{
    int i;

    /*
     * Issue opcode repeatedly till Execute Tuning is set to 0 or the number
     * of loops reaches tuning loop count.
     */
    for (i = 0; i < host->tuning_loop_count; i++)
    {
        rt_uint16_t ctrl;

        sdhci_send_tuning(host, opcode);

        if (!host->tuning_done)
        {
            sdhci_abort_tuning(host, opcode);
            return -ETIMEDOUT;
        }

        /* Spec does not require a delay between tuning cycles */
        if (host->tuning_delay > 0)
            rt_thread_mdelay(host->tuning_delay);

        ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
        if (!(ctrl & SDHCI_CTRL_EXEC_TUNING))
        {
            if (ctrl & SDHCI_CTRL_TUNED_CLK)
                return 0; /* Success! */
            break;
        }
    }

    LOG_D("%s: Tuning failed, falling back to fixed sampling clock\n",
          mmc_hostname(host->mmc));
    sdhci_reset_tuning(host);
    return -EAGAIN;
}

void sdhci_start_tuning(struct sdhci_host *host)
{
    rt_uint16_t ctrl;

    ctrl  = sdhci_readw(host, SDHCI_HOST_CONTROL2);
    ctrl |= SDHCI_CTRL_EXEC_TUNING;
    if (host->quirks2 & SDHCI_QUIRK2_TUNING_WORK_AROUND)
        ctrl |= SDHCI_CTRL_TUNED_CLK;
    sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);

    /*
     * As per the Host Controller spec v3.00, tuning command
     * generates Buffer Read Ready interrupt, so enable that.
     *
     * Note: The spec clearly says that when tuning sequence
     * is being performed, the controller does not generate
     * interrupts other than Buffer Read Ready interrupt. But
     * to make sure we don't hit a controller bug, we _only_
     * enable Buffer Read Ready interrupt here.
     */
    sdhci_writel(host, SDHCI_INT_DATA_AVAIL, SDHCI_INT_ENABLE);
    sdhci_writel(host, SDHCI_INT_DATA_AVAIL, SDHCI_SIGNAL_ENABLE);
}

void sdhci_end_tuning(struct sdhci_host *host)
{
    sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
    sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

void sdhci_abort_tuning(struct sdhci_host *host, rt_uint32_t opcode)
{
    sdhci_reset_tuning(host);

    sdhci_reset_for(host, TUNING_ABORT);

    sdhci_end_tuning(host);
}

void sdhci_send_tuning(struct sdhci_host *host, rt_uint32_t opcode)
{
    struct mmc_host    *mmc = host->mmc;
    struct rt_mmcsd_cmd cmd = {};
    struct rt_mmcsd_req mrq = {};
    unsigned long       flags;
    rt_uint32_t         b = host->sdma_boundary;

    flags = rt_spin_lock_irqsave(&host->lock);

    cmd.cmd_code = opcode;
    cmd.flags    = MMC_RSP_R1 | MMC_CMD_ADTC;
    cmd.mrq      = &mrq;

    mrq.cmd = &cmd;
    /*
     * In response to CMD19, the card sends 64 bytes of tuning
     * block to the Host Controller. So we set the block size
     * to 64 here.
     */
    if (cmd.cmd_code == MMC_SEND_TUNING_BLOCK_HS200 && mmc->ios.bus_width == MMC_BUS_WIDTH_8)
        sdhci_writew(host, SDHCI_MAKE_BLKSZ(b, 128), SDHCI_BLOCK_SIZE);
    else
        sdhci_writew(host, SDHCI_MAKE_BLKSZ(b, 64), SDHCI_BLOCK_SIZE);

    /*
     * The tuning block is sent by the card to the host controller.
     * So we set the TRNS_READ bit in the Transfer Mode register.
     * This also takes care of setting DMA Enable and Multi Block
     * Select in the same register to 0.
     */
    sdhci_writew(host, SDHCI_TRNS_READ, SDHCI_TRANSFER_MODE);

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

void sdhci_reset_tuning(struct sdhci_host *host)
{
    rt_uint16_t ctrl;

    ctrl  = sdhci_readw(host, SDHCI_HOST_CONTROL2);
    ctrl &= ~SDHCI_CTRL_TUNED_CLK;
    ctrl &= ~SDHCI_CTRL_EXEC_TUNING;
    sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);
}


/********************************************************* */
/*                     error                               */
/********************************************************* */

void sdhci_dumpregs(struct sdhci_host *host)
{
#define SDHCI_DUMP rt_kprintf
    SDHCI_DUMP("============ SDHCI REGISTER DUMP ===========\n");

    SDHCI_DUMP("Sys addr:  0x%08x | Version:  0x%08x\n",
               sdhci_readl(host, SDHCI_DMA_ADDRESS),
               sdhci_readw(host, SDHCI_HOST_VERSION));
    SDHCI_DUMP("Blk size:  0x%08x | Blk cnt:  0x%08x\n",
               sdhci_readw(host, SDHCI_BLOCK_SIZE),
               sdhci_readw(host, SDHCI_BLOCK_COUNT));
    SDHCI_DUMP("Argument:  0x%08x | Trn mode: 0x%08x\n",
               sdhci_readl(host, SDHCI_ARGUMENT),
               sdhci_readw(host, SDHCI_TRANSFER_MODE));
    SDHCI_DUMP("Present:   0x%08x | Host ctl: 0x%08x\n",
               sdhci_readl(host, SDHCI_PRESENT_STATE),
               sdhci_readb(host, SDHCI_HOST_CONTROL));
    SDHCI_DUMP("Power:     0x%08x | Blk gap:  0x%08x\n",
               sdhci_readb(host, SDHCI_POWER_CONTROL),
               sdhci_readb(host, SDHCI_BLOCK_GAP_CONTROL));
    SDHCI_DUMP("Wake-up:   0x%08x | Clock:    0x%08x\n",
               sdhci_readb(host, SDHCI_WAKE_UP_CONTROL),
               sdhci_readw(host, SDHCI_CLOCK_CONTROL));
    SDHCI_DUMP("Timeout:   0x%08x | Int stat: 0x%08x\n",
               sdhci_readb(host, SDHCI_TIMEOUT_CONTROL),
               sdhci_readl(host, SDHCI_INT_STATUS));
    SDHCI_DUMP("Int enab:  0x%08x | Sig enab: 0x%08x\n",
               sdhci_readl(host, SDHCI_INT_ENABLE),
               sdhci_readl(host, SDHCI_SIGNAL_ENABLE));
    SDHCI_DUMP("ACmd stat: 0x%08x | Slot int: 0x%08x\n",
               sdhci_readw(host, SDHCI_AUTO_CMD_STATUS),
               sdhci_readw(host, SDHCI_SLOT_INT_STATUS));
    SDHCI_DUMP("Caps:      0x%08x | Caps_1:   0x%08x\n",
               sdhci_readl(host, SDHCI_CAPABILITIES),
               sdhci_readl(host, SDHCI_CAPABILITIES_1));
    SDHCI_DUMP("Cmd:       0x%08x | Max curr: 0x%08x\n",
               sdhci_readw(host, SDHCI_COMMAND),
               sdhci_readl(host, SDHCI_MAX_CURRENT));
    SDHCI_DUMP("Resp[0]:   0x%08x | Resp[1]:  0x%08x\n",
               sdhci_readl(host, SDHCI_RESPONSE),
               sdhci_readl(host, SDHCI_RESPONSE + 4));
    SDHCI_DUMP("Resp[2]:   0x%08x | Resp[3]:  0x%08x\n",
               sdhci_readl(host, SDHCI_RESPONSE + 8),
               sdhci_readl(host, SDHCI_RESPONSE + 12));
    SDHCI_DUMP("Host ctl2: 0x%08x\n",
               sdhci_readw(host, SDHCI_HOST_CONTROL2));


    if (host->ops->dump_vendor_regs)
        host->ops->dump_vendor_regs(host);

    SDHCI_DUMP("============================================\n");
}


static const struct mmc_host_ops sdhci_ops = {
    .request                     = sdhci_request,
    .set_ios                     = sdhci_set_ios,
    .get_cd                      = sdhci_get_cd,
    .get_ro                      = sdhci_get_ro,
    .enable_sdio_irq             = sdhci_enable_sdio_irq,
    .ack_sdio_irq                = sdhci_ack_sdio_irq,
    .start_signal_voltage_switch = sdhci_start_signal_voltage_switch,
    .prepare_hs400_tuning        = sdhci_prepare_hs400_tuning,
    .execute_tuning              = sdhci_execute_tuning,
    .card_event                  = sdhci_card_event,
    .card_busy                   = sdhci_card_busy,
};


void sdhci_remove_host(struct sdhci_host *host, int dead)
{
    struct mmc_host *mmc = host->mmc;
    unsigned long    flags;

    if (dead)
    {
        flags = rt_spin_lock_irqsave(&host->lock);

        host->flags |= SDHCI_DEVICE_DEAD;

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

    mmc_remove_host(mmc);


    if (!dead)
        sdhci_reset_for_all(host);

    sdhci_writel(host, 0, SDHCI_INT_ENABLE);
    sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);

    rt_timer_delete(&host->timer);
    rt_timer_delete(&host->data_timer);

    rt_workqueue_destroy(host->complete_wq);

    if (host->use_external_dma)
        sdhci_external_dma_release(host);

    host->align_buffer = NULL;
}

rt_uint16_t sdhci_calc_clk(struct sdhci_host *host, unsigned int clock,
                           unsigned int *actual_clock)
{
    int         div      = 0; /* Initialized for compiler warning */
    int         real_div = div, clk_mul = 1;
    rt_uint16_t clk             = 0;
    rt_bool_t   switch_base_clk = RT_FALSE;

    if (host->version >= SDHCI_SPEC_300)
    {
        if (host->preset_enabled)
        {
            rt_uint16_t pre_val;

            clk     = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
            pre_val = sdhci_get_preset_value(host);
            div     = FIELD_GET(SDHCI_PRESET_SDCLK_FREQ_MASK, pre_val);
            if (host->clk_mul && (pre_val & SDHCI_PRESET_CLKGEN_SEL))
            {
                clk      = SDHCI_PROG_CLOCK_MODE;
                real_div = div + 1;
                clk_mul  = host->clk_mul;
            }
            else
            {
                real_div = max_t(int, 1, div << 1);
            }
            goto clock_set;
        }

        /*
         * Check if the Host Controller supports Programmable Clock
         * Mode.
         */
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
                /*
                 * Set Programmable Clock Mode in the Clock
                 * Control register.
                 */
                clk      = SDHCI_PROG_CLOCK_MODE;
                real_div = div;
                clk_mul  = host->clk_mul;
                div--;
            }
            else
            {
                /*
                 * Divisor can be too small to reach clock
                 * speed requirement. Then use the base clock.
                 */
                switch_base_clk = RT_TRUE;
            }
        }

        if (!host->clk_mul || switch_base_clk)
        {
            /* Version 3.00 divisors must be a multiple of 2. */
            if (host->max_clk <= clock)
                div = 1;
            else
            {
                for (div  = 2; div < SDHCI_MAX_DIV_SPEC_300;
                     div += 2)
                {
                    if ((host->max_clk / div) <= clock)
                        break;
                }
            }
            real_div   = div;
            div      >>= 1;
            if ((host->quirks2 & SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN)
                && !div && host->max_clk <= 25000000)
                div = 1;
        }
    }
    else
    {
        /* Version 2.00 divisors must be a power of 2. */
        for (div = 1; div < SDHCI_MAX_DIV_SPEC_200; div *= 2)
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
    clk |= (div & SDHCI_DIV_MASK) << SDHCI_DIVIDER_SHIFT;
    clk |= ((div & SDHCI_DIV_HI_MASK) >> SDHCI_DIV_MASK_LEN)
           << SDHCI_DIVIDER_HI_SHIFT;

    return clk;
}

void sdhci_enable_clk(struct sdhci_host *host, rt_uint16_t clk)
{
    long timeout;

    clk |= SDHCI_CLOCK_INT_EN;
    sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

    /* Wait max 150 ms */
    timeout = rt_tick_from_millisecond(150);
    while (1)
    {
        timeout = timeout - rt_tick_get();

        clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
        if (clk & SDHCI_CLOCK_INT_STABLE)
            break;
        if (timeout < 0)
        {
            rt_kprintf("%s: Internal clock never stabilised.\n",
                       mmc_hostname(host->mmc));
            sdhci_dumpregs(host);
            return;
        }
        rt_hw_us_delay(10);
    }

    if (host->version >= SDHCI_SPEC_410 && host->v4_mode)
    {
        clk |= SDHCI_CLOCK_PLL_EN;
        clk &= ~SDHCI_CLOCK_INT_STABLE;
        sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

        /* Wait max 150 ms */
        timeout = rt_tick_from_millisecond(150);
        while (1)
        {
            timeout = timeout - rt_tick_get();

            clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
            if (clk & SDHCI_CLOCK_INT_STABLE)
                break;
            if (timeout < 0)
            {
                rt_kprintf("%s: PLL clock never stabilised.\n",
                           mmc_hostname(host->mmc));
                sdhci_dumpregs(host);
                return;
            }
            rt_hw_us_delay(10);
        }
    }

    clk |= SDHCI_CLOCK_CARD_EN;
    sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}

void sdhci_set_clock(struct sdhci_host *host, unsigned int clock)
{
    rt_uint16_t clk;

    host->mmc->actual_clock = 0;

    sdhci_writew(host, 0, SDHCI_CLOCK_CONTROL);

    if (clock == 0)
        return;

    clk = sdhci_calc_clk(host, clock, &host->mmc->actual_clock);
    sdhci_enable_clk(host, clk);
}

void __sdhci_read_caps(struct sdhci_host *host, const rt_uint16_t *ver,
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
    v             = ver ? *ver : sdhci_readw(host, SDHCI_HOST_VERSION);
    host->version = (v & SDHCI_SPEC_VER_MASK) >> SDHCI_SPEC_VER_SHIFT;

    if (caps)
    {
        host->caps = *caps;
    }
    else
    {
        host->caps  = sdhci_readl(host, SDHCI_CAPABILITIES);
        host->caps &= ~lower_32_bits(dt_caps_mask);
        host->caps |= lower_32_bits(dt_caps);
    }

    if (host->version < SDHCI_SPEC_300)
        return;

    if (caps1)
    {
        host->caps1 = *caps1;
    }
    else
    {
        host->caps1  = sdhci_readl(host, SDHCI_CAPABILITIES_1);
        host->caps1 &= ~upper_32_bits(dt_caps_mask);
        host->caps1 |= upper_32_bits(dt_caps);
    }
}

struct sdhci_host *sdhci_alloc_host(struct rt_device *dev,
                                    size_t            priv_size)
{
    struct mmc_host   *mmc;
    struct sdhci_host *host;

    mmc = mmc_alloc_host(sizeof(struct sdhci_host) + priv_size, dev);
    if (!mmc)
        return NULL;

    host               = mmc_priv(mmc);
    host->mmc          = mmc;
    host->mmc_host_ops = sdhci_ops;
    mmc->ops           = &host->mmc_host_ops;

    host->flags = SDHCI_SIGNALING_330;

    host->cqe_ier     = SDHCI_CQE_INT_MASK;
    host->cqe_err_ier = SDHCI_CQE_INT_ERR_MASK;

    host->tuning_delay      = -1;
    host->tuning_loop_count = MAX_TUNING_LOOP;

    host->sdma_boundary = SDHCI_DEFAULT_BOUNDARY_ARG;

    /*
     * The DMA table descriptor count is calculated as the maximum
     * number of segments times 2, to allow for an alignment
     * descriptor for each segment, plus 1 for a nop end descriptor.
     */

    host->max_timeout_count = 0xE;

    return host;
}

int sdhci_setup_host(struct sdhci_host *host)
{
    struct mmc_host *mmc;
    size_t           max_current_caps;
    unsigned int     ocr_avail;
    unsigned int     override_timeout_clk;
    size_t           max_clk;
    int              ret          = 0;
    bool             enable_vqmmc = RT_FALSE;

    RT_ASSERT(host != NULL);


    mmc = host->mmc;

    /*
     * If there are external regulators, get them. Note this must be done
     * early before resetting the host and reading the capabilities so that
     * the host can take the appropriate action if regulators are not
     * available.
     */
    if (!mmc->supply.vqmmc)
    {
        if (ret)
            return ret;
        enable_vqmmc = RT_TRUE;
    }

    LOG_D("Version:   0x%08x | Present:  0x%08x\n",
          sdhci_readw(host, SDHCI_HOST_VERSION),
          sdhci_readl(host, SDHCI_PRESENT_STATE));
    LOG_D("Caps:      0x%08x | Caps_1:   0x%08x\n",
          sdhci_readl(host, SDHCI_CAPABILITIES),
          sdhci_readl(host, SDHCI_CAPABILITIES_1));

    sdhci_read_caps(host);

    override_timeout_clk = host->timeout_clk;

    if (host->version > SDHCI_SPEC_420)
    {
        rt_kprintf("%s: Unknown controller version (%d). You may experience problems.\n",
                   mmc_hostname(mmc), host->version);
    }

    if (host->quirks & SDHCI_QUIRK_FORCE_DMA)
        host->flags |= SDHCI_USE_SDMA;
    else if (!(host->caps & SDHCI_CAN_DO_SDMA))
        LOG_D("Controller doesn't have SDMA capability\n");
    else
        host->flags |= SDHCI_USE_SDMA;

    if ((host->quirks & SDHCI_QUIRK_BROKEN_DMA) && (host->flags & SDHCI_USE_SDMA))
    {
        LOG_D("Disabling DMA as it is marked broken\n");
        host->flags &= ~SDHCI_USE_SDMA;
    }

    if (sdhci_can_64bit_dma(host))
        host->flags |= SDHCI_USE_64_BIT_DMA;

    if (host->flags & SDHCI_USE_SDMA)
    {
        if (host->ops->set_dma_mask)
            ret = host->ops->set_dma_mask(host);

        if (!ret && host->ops->enable_dma)
            ret = host->ops->enable_dma(host);

        if (ret)
        {
            rt_kprintf("%s: No suitable DMA available - falling back to PIO\n",
                       mmc_hostname(mmc));
            host->flags &= ~SDHCI_USE_SDMA;

            ret = 0;
        }
    }

    /* SDMA does not support 64-bit DMA if v4 mode not set */
    if ((host->flags & SDHCI_USE_64_BIT_DMA) && !host->v4_mode)
        host->flags &= ~SDHCI_USE_SDMA;
    /*
     * If we use DMA, then it's up to the caller to set the DMA
     * mask, but PIO does not need the hw shim so we set a new
     * mask here in that case.
     */

    if (!(host->flags & SDHCI_USE_SDMA))
    {
        host->dma_mask = DMA_BIT_MASK(64);
    }
    if (host->version >= SDHCI_SPEC_300)
        host->max_clk = FIELD_GET(SDHCI_CLOCK_V3_BASE_MASK, host->caps);
    else
        host->max_clk = FIELD_GET(SDHCI_CLOCK_BASE_MASK, host->caps);

    host->max_clk *= 1000000;
    if (host->max_clk == 0 || host->quirks & SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN)
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

    /*
     * In case of Host Controller v3.00, find out whether clock
     * multiplier is supported.
     */
    host->clk_mul = FIELD_GET(SDHCI_CLOCK_MUL_MASK, host->caps1);

    /*
     * In case the value in Clock Multiplier is 0, then programmable
     * clock mode is not supported, otherwise the actual clock
     * multiplier is one more than the value of Clock Multiplier
     * in the Capabilities Register.
     */
    if (host->clk_mul)
        host->clk_mul += 1;

    /*
     * Set host parameters.
     */
    max_clk = host->max_clk;

    if (host->ops->get_min_clock)
        mmc->f_min = host->ops->get_min_clock(host);
    else if (host->version >= SDHCI_SPEC_300)
    {
        if (host->clk_mul)
            max_clk = host->max_clk * host->clk_mul;
        /*
         * Divided Clock Mode minimum clock rate is always less than
         * Programmable Clock Mode minimum clock rate.
         */
        mmc->f_min = host->max_clk / SDHCI_MAX_DIV_SPEC_300;
    }
    else
        mmc->f_min = host->max_clk / SDHCI_MAX_DIV_SPEC_200;

    if (!mmc->f_max || mmc->f_max > max_clk)
        mmc->f_max = max_clk;

    if (!(host->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK))
    {
        host->timeout_clk = FIELD_GET(SDHCI_TIMEOUT_CLK_MASK, host->caps);

        if (host->caps & SDHCI_TIMEOUT_CLK_UNIT)
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

    if (host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT && !host->ops->get_max_timeout_count)
        mmc->max_busy_timeout = 0;

    mmc->caps  |= MMC_CAP_SDIO_IRQ | MMC_CAP_CMD23;
    mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

    if (host->quirks & SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12)
        host->flags |= SDHCI_AUTO_CMD12;

    /*
     * For v3 mode, Auto-CMD23 stuff only works in ADMA or PIO.
     * For v4 mode, SDMA may use Auto-CMD23 as well.
     */
    if ((host->version >= SDHCI_SPEC_300) && (!(host->flags & SDHCI_USE_SDMA) || host->v4_mode) && !(host->quirks2 & SDHCI_QUIRK2_ACMD23_BROKEN))
    {
        host->flags |= SDHCI_AUTO_CMD23;
        LOG_D("Auto-CMD23 available\n");
    }
    else
    {
        LOG_D("Auto-CMD23 unavailable\n");
    }

    /*
     * A controller may support 8-bit width, but the board itself
     * might not have the pins brought out.  Boards that support
     * 8-bit width must set "mmc->caps |= MMC_CAP_8_BIT_DATA;" in
     * their platform code before calling sdhci_add_host(), and we
     * won't assume 8-bit width for hosts without that CAP.
     */
    if (!(host->quirks & SDHCI_QUIRK_FORCE_1_BIT_DATA))
        mmc->caps |= MMC_CAP_4_BIT_DATA;

    if (host->quirks2 & SDHCI_QUIRK2_HOST_NO_CMD23)
        mmc->caps &= ~MMC_CAP_CMD23;

    if (host->caps & SDHCI_CAN_DO_HISPD)
        mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;
    if ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) && mmc_card_is_removable(mmc) && mmc_gpio_get_cd(mmc) < 0)
        mmc->caps |= MMC_CAP_NEEDS_POLL;

    if (mmc->supply.vqmmc)
    {
        if (enable_vqmmc)
        {
            host->sdhci_core_to_disable_vqmmc = !ret;
        }

        /* If vqmmc provides no 1.8V signalling, then there's no UHS */
        if (!regulator_is_supported_voltage(mmc->supply.vqmmc, 1700000,
                                            1950000))
            host->caps1 &= ~(SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_DDR50);

        /* In eMMC case vqmmc might be a fixed 1.8V regulator */
        if (!regulator_is_supported_voltage(mmc->supply.vqmmc, 2700000,
                                            3600000))
            host->flags &= ~SDHCI_SIGNALING_330;

        if (ret)
        {
            rt_kprintf("%s: Failed to enable vqmmc regulator: %d\n",
                       mmc_hostname(mmc), ret);
            mmc->supply.vqmmc = (void *)-EINVAL;
        }
    }
    if (host->quirks2 & SDHCI_QUIRK2_NO_1_8_V)
    {
        host->caps1 &= ~(SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_DDR50);
        /*
         * The SDHCI controller in a SoC might support HS200/HS400
         * (indicated using mmc-hs200-1_8v/mmc-hs400-1_8v dt property),
         * but if the board is modeled such that the IO lines are not
         * connected to 1.8v then HS200/HS400 cannot be supported.
         * Disable HS200/HS400 if the board does not have 1.8v connected
         * to the IO lines. (Applicable for other modes in 1.8v)
         */
        mmc->caps2 &= ~(MMC_CAP2_HSX00_1_8V | MMC_CAP2_HS400_ES);
        mmc->caps  &= ~(MMC_CAP_1_8V_DDR | MMC_CAP_UHS);
    }

    /* Any UHS-I mode in caps implies SDR12 and SDR25 support. */
    if (host->caps1 & (SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_DDR50))
        mmc->caps |= MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25;

    /* SDR104 supports also implies SDR50 support */
    if (host->caps1 & SDHCI_SUPPORT_SDR104)
    {
        mmc->caps |= MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_SDR50;
        /* SD3.0: SDR104 is supported so (for eMMC) the caps2
         * field can be promoted to support HS200.
         */
        if (!(host->quirks2 & SDHCI_QUIRK2_BROKEN_HS200))
            mmc->caps2 |= MMC_CAP2_HS200;
    }
    else if (host->caps1 & SDHCI_SUPPORT_SDR50)
    {
        mmc->caps |= MMC_CAP_UHS_SDR50;
    }

    if (host->quirks2 & SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 && (host->caps1 & SDHCI_SUPPORT_HS400))
        mmc->caps2 |= MMC_CAP2_HS400;
    if ((mmc->caps2 & MMC_CAP2_HSX00_1_2V) && (!mmc->supply.vqmmc || !regulator_is_supported_voltage(mmc->supply.vqmmc, 1100000, 1300000)))
        mmc->caps2 &= ~MMC_CAP2_HSX00_1_2V;
    if ((host->caps1 & SDHCI_SUPPORT_DDR50) && !(host->quirks2 & SDHCI_QUIRK2_BROKEN_DDR50))
        mmc->caps |= MMC_CAP_UHS_DDR50;

    /* Does the host need tuning for SDR50? */
    if (host->caps1 & SDHCI_USE_SDR50_TUNING)
        host->flags |= SDHCI_SDR50_NEEDS_TUNING;

    /* Driver Type(s) (A, C, D) supported by the host */
    if (host->caps1 & SDHCI_DRIVER_TYPE_A)
        mmc->caps |= MMC_CAP_DRIVER_TYPE_A;
    if (host->caps1 & SDHCI_DRIVER_TYPE_C)
        mmc->caps |= MMC_CAP_DRIVER_TYPE_C;
    if (host->caps1 & SDHCI_DRIVER_TYPE_D)
        mmc->caps |= MMC_CAP_DRIVER_TYPE_D;

    /* Initial value for re-tuning timer count */
    host->tuning_count = FIELD_GET(SDHCI_RETUNING_TIMER_COUNT_MASK,
                                   host->caps1);

    /*
     * In case Re-tuning Timer is not disabled, the actual value of
     * re-tuning timer will be 2 ^ (n - 1).
     */
    if (host->tuning_count)
        host->tuning_count = 1 << (host->tuning_count - 1);

    /* Re-tuning mode supported by the Host Controller */
    host->tuning_mode = FIELD_GET(SDHCI_RETUNING_MODE_MASK, host->caps1);

    ocr_avail = 0;

    /*
     * According to SD Host Controller spec v3.00, if the Host System
     * can afford more than 150mA, Host Driver should set XPC to 1. Also
     * the value is meaningful only if Voltage Support in the Capabilities
     * register is set. The actual current value is 4 times the register
     * value.
     */
    max_current_caps = sdhci_readl(host, SDHCI_MAX_CURRENT);

    if (!max_current_caps && mmc->supply.vmmc)
    {
        int curr = regulator_get_current_limit(mmc->supply.vmmc);
        if (curr > 0)
        {
            /* convert to SDHCI_MAX_CURRENT format */
            curr = curr / 1000; /* convert to mA */
            curr = curr / SDHCI_MAX_CURRENT_MULTIPLIER;

            curr = min_t(rt_uint32_t, curr, SDHCI_MAX_CURRENT_LIMIT);
            max_current_caps =
                FIELD_PREP(SDHCI_MAX_CURRENT_330_MASK, curr) | FIELD_PREP(SDHCI_MAX_CURRENT_300_MASK, curr) | FIELD_PREP(SDHCI_MAX_CURRENT_180_MASK, curr);
        }
    }

    if (host->caps & SDHCI_CAN_VDD_330)
    {
        ocr_avail |= MMC_VDD_32_33 | MMC_VDD_33_34;

        mmc->max_current_330 = FIELD_GET(SDHCI_MAX_CURRENT_330_MASK,
                                         max_current_caps)
                               * SDHCI_MAX_CURRENT_MULTIPLIER;
    }
    if (host->caps & SDHCI_CAN_VDD_300)
    {
        ocr_avail |= MMC_VDD_29_30 | MMC_VDD_30_31;

        mmc->max_current_300 = FIELD_GET(SDHCI_MAX_CURRENT_300_MASK,
                                         max_current_caps)
                               * SDHCI_MAX_CURRENT_MULTIPLIER;
    }
    if (host->caps & SDHCI_CAN_VDD_180)
    {
        ocr_avail |= MMC_VDD_165_195;

        mmc->max_current_180 = FIELD_GET(SDHCI_MAX_CURRENT_180_MASK,
                                         max_current_caps)
                               * SDHCI_MAX_CURRENT_MULTIPLIER;
    }

    /* If OCR set by host, use it instead. */
    if (host->ocr_mask)
        ocr_avail = host->ocr_mask;

    /* If OCR set by external regulators, give it highest prio. */
    if (mmc->ocr_avail)
        ocr_avail = mmc->ocr_avail;

    mmc->ocr_avail      = ocr_avail;
    mmc->ocr_avail_sdio = ocr_avail;
    if (host->ocr_avail_sdio)
        mmc->ocr_avail_sdio &= host->ocr_avail_sdio;
    mmc->ocr_avail_sd = ocr_avail;
    if (host->ocr_avail_sd)
        mmc->ocr_avail_sd &= host->ocr_avail_sd;
    else /* normal SD controllers don't support 1.8V */
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
        host->flags |= SDHCI_SIGNALING_180;

    if (mmc->caps2 & MMC_CAP2_HSX00_1_2V)
        host->flags |= SDHCI_SIGNALING_120;

    rt_spin_lock_init(&host->lock);

    /*
     * Maximum number of sectors in one transfer. Limited by SDMA boundary
     * size (512KiB). Note some tuning modes impose a 4MiB limit, but this
     * is less anyway.
     */
    mmc->max_req_size = 524288;

    /*
     * Maximum number of segments. Depends on if the hardware
     * can do scatter/gather or not.
     */
    if (host->flags & SDHCI_USE_SDMA)
    {
        mmc->max_segs = 1;
    }
    else
    { /* PIO */
        mmc->max_segs = SDHCI_MAX_SEGS;
    }
    /*
     * Maximum segment size. Could be one segment with the maximum number
     * of bytes. When doing hardware scatter/gather, each entry cannot
     * be larger than 64 KiB though.
     */
    mmc->max_seg_size = mmc->max_req_size;

    /*
     * Maximum block size. This varies from controller to controller and
     * is specified in the capabilities register.
     */
    if (host->quirks & SDHCI_QUIRK_FORCE_BLK_SZ_2048)
    {
        mmc->max_blk_size = 2;
    }
    else
    {
        mmc->max_blk_size = (host->caps & SDHCI_MAX_BLOCK_MASK) >> SDHCI_MAX_BLOCK_SHIFT;
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
    mmc->max_blk_count = (host->quirks & SDHCI_QUIRK_NO_MULTIBLOCK) ? 1 : 65535;
    return 0;

unreg:
undma:
    return ret;
}

static void sdhci_init(struct sdhci_host *host, int soft)
{
    struct mmc_host *mmc = host->mmc;
    rt_base_t        flags;

    if (soft)
    {
        sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
    }
    else
    {
        sdhci_do_reset(host, SDHCI_RESET_ALL);
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

static void sdhci_reinit(struct sdhci_host *host)
{
    rt_uint32_t cd = host->ier & (SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT);

    sdhci_init(host, 0);
    sdhci_enable_card_detection(host);

    /*
     * A change to the card detect bits indicates a change in present state,
     * refer sdhci_set_card_detection(). A card detect interrupt might have
     * been missed while the host controller was being reset, so trigger a
     * rescan to check.
     */
    if (cd != (host->ier & (SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT)))
        mmc_detect_change(host->mmc, rt_tick_from_millisecond(200));
}

int __sdhci_add_host(struct sdhci_host *host)
{
    struct mmc_host *mmc = host->mmc;
    int              ret;

    if ((mmc->caps2 & MMC_CAP2_CQE) && (host->quirks & SDHCI_QUIRK_BROKEN_CQE))
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
    ret = mmc_add_host(mmc);
    if (ret)
        goto unirq;

    rt_kprintf("%s: SDHCI controller on %s [%s] using %s\n",
               mmc_hostname(mmc), host->hw_name, mmc_dev(mmc)->parent.name,
               (host->flags & SDHCI_USE_SDMA) ? "DMA" : "PIO");

    sdhci_enable_card_detection(host);

    return 0;

unirq:
    sdhci_reset_for_all(host);
    sdhci_writel(host, 0, SDHCI_INT_ENABLE);
    sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);

    return ret;
}

int sdhci_add_host(struct sdhci_host *host)
{
    int ret;
    ret = sdhci_setup_host(host);
    if (ret)
        return ret;

    ret = __sdhci_add_host(host);
    if (ret)
        goto cleanup;

    return 0;

cleanup:
    sdhci_cleanup_host(host);

    return ret;
}

void sdhci_set_ios(struct mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    struct sdhci_host *host           = mmc_priv(mmc);
    rt_bool_t          reinit_uhs     = host->reinit_uhs;
    rt_bool_t          turning_on_clk = RT_FALSE;
    rt_uint8_t         ctrl;

    host->reinit_uhs = RT_FALSE;

    if (ios->power_mode == MMC_POWER_UNDEFINED)
        return;

    if (host->flags & SDHCI_DEVICE_DEAD)
    {
        if (mmc->supply.vmmc && ios->power_mode == MMC_POWER_OFF)
            mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
        return;
    }

    /*
     * Reset the chip on each power off.
     * Should clear out any weird states.
     */
    if (ios->power_mode == MMC_POWER_OFF)
    {
        sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);
        sdhci_reinit(host);
    }

    if (host->version >= SDHCI_SPEC_300 && (ios->power_mode == MMC_POWER_UP) && !(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN))
        sdhci_enable_preset_value(host, RT_FALSE);

    if (!ios->clock || ios->clock != host->clock)
    {
        turning_on_clk = ios->clock && !host->clock;

        host->ops->set_clock(host, ios->clock);
        host->clock = ios->clock;

        if (host->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK && host->clock)
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
        sdhci_set_power(host, ios->power_mode, ios->vdd);

    if (host->ops->platform_send_init_74_clocks)
        host->ops->platform_send_init_74_clocks(host, ios->power_mode);

    host->ops->set_bus_width(host, ios->bus_width);

    /*
     * Special case to avoid multiple clock changes during voltage
     * switching.
     */
    if (!reinit_uhs && turning_on_clk && host->timing == ios->timing && host->version >= SDHCI_SPEC_300 && !sdhci_presetable_values_change(host, ios))
        return;

    ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);

    if (!(host->quirks & SDHCI_QUIRK_NO_HISPD_BIT))
    {
        if (ios->timing == MMC_TIMING_SD_HS || ios->timing == MMC_TIMING_MMC_HS || ios->timing == MMC_TIMING_MMC_HS400 || ios->timing == MMC_TIMING_MMC_HS200 || ios->timing == MMC_TIMING_MMC_DDR52 || ios->timing == MMC_TIMING_UHS_SDR50 || ios->timing == MMC_TIMING_UHS_SDR104 || ios->timing == MMC_TIMING_UHS_DDR50 || ios->timing == MMC_TIMING_UHS_SDR25)
            ctrl |= SDHCI_CTRL_HISPD;
        else
            ctrl &= ~SDHCI_CTRL_HISPD;
    }

    if (host->version >= SDHCI_SPEC_300)
    {
        rt_uint16_t clk, ctrl_2;

        /*
         * According to SDHCI Spec v3.00, if the Preset Value
         * Enable in the Host Control 2 register is set, we
         * need to reset SD Clock Enable before changing High
         * Speed Enable to avoid generating clock glitches.
         */
        clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
        if (clk & SDHCI_CLOCK_CARD_EN)
        {
            clk &= ~SDHCI_CLOCK_CARD_EN;
            sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
        }

        sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

        if (!host->preset_enabled)
        {
            /*
             * We only need to set Driver Strength if the
             * preset value enable is not set.
             */
            ctrl_2  = sdhci_readw(host, SDHCI_HOST_CONTROL2);
            ctrl_2 &= ~SDHCI_CTRL_DRV_TYPE_MASK;
            if (ios->drv_type == MMC_SET_DRIVER_TYPE_A)
                ctrl_2 |= SDHCI_CTRL_DRV_TYPE_A;
            else if (ios->drv_type == MMC_SET_DRIVER_TYPE_B)
                ctrl_2 |= SDHCI_CTRL_DRV_TYPE_B;
            else if (ios->drv_type == MMC_SET_DRIVER_TYPE_C)
                ctrl_2 |= SDHCI_CTRL_DRV_TYPE_C;
            else if (ios->drv_type == MMC_SET_DRIVER_TYPE_D)
                ctrl_2 |= SDHCI_CTRL_DRV_TYPE_D;
            else
            {
                LOG_D("%s: invalid driver type, default to driver type B\n",
                      mmc_hostname(mmc));
                ctrl_2 |= SDHCI_CTRL_DRV_TYPE_B;
            }

            sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);
            host->drv_type = ios->drv_type;
        }

        host->ops->set_uhs_signaling(host, ios->timing);
        host->timing = ios->timing;

        if (sdhci_preset_needed(host, ios->timing))
        {
            rt_uint16_t preset;

            sdhci_enable_preset_value(host, RT_TRUE);
            preset         = sdhci_get_preset_value(host);
            ios->drv_type  = FIELD_GET(SDHCI_PRESET_DRV_MASK,
                                       preset);
            host->drv_type = ios->drv_type;
        }

        /* Re-enable SD Clock */
        host->ops->set_clock(host, host->clock);
    }
    else
        sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}
void sdhci_free_host(struct sdhci_host *host)
{
    sdhci_cleanup_host(host);
    rt_free(host);
}
