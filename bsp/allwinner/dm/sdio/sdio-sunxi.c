/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <cache.h>
#include <mm_aspace.h>
#include <drivers/dma.h>

#define DBG_TAG "sdio.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "dev_sdio_dm.h"

#define SUNXI_MMC_GCTRL                 0x00
#define SUNXI_MMC_CLKCR                 0x04
#define SUNXI_MMC_TMOUT                 0x08
#define SUNXI_MMC_WIDTH                 0x0c
#define SUNXI_MMC_BLKSZ                 0x10
#define SUNXI_MMC_BCNTR                 0x14
#define SUNXI_MMC_CMDR                  0x18
#define SUNXI_MMC_CARG                  0x1c
#define SUNXI_MMC_RESP0                 0x20
#define SUNXI_MMC_RESP1                 0x24
#define SUNXI_MMC_RESP2                 0x28
#define SUNXI_MMC_RESP3                 0x2c
#define SUNXI_MMC_IMASK                 0x30
#define SUNXI_MMC_RINTR                 0x38
#define SUNXI_MMC_STAS                  0x3c
#define SUNXI_MMC_FTRGL                 0x40
#define SUNXI_MMC_FUNS                  0x44
#define SUNXI_MMC_NTSR                  0x5c
#define SUNXI_MMC_HWRST                 0x78
#define SUNXI_MMC_DRV_DL                0x140
#define SUNXI_MMC_FIFO                  0x200
#define SUNXI_MMC_DMAC                  0x80
#define SUNXI_MMC_DLBA                  0x84
#define SUNXI_MMC_IDST                  0x88
#define SUNXI_MMC_IDIE                  0x8c
#define SUNXI_MMC_CHDA                  0x90
#define SUNXI_MMC_CBDA                  0x94

#define SUNXI_MMC_SOFT_RESET            RT_BIT(0)
#define SUNXI_MMC_FIFO_RESET            RT_BIT(1)
#define SUNXI_MMC_DMA_RESET             RT_BIT(2)
#define SUNXI_MMC_INT_ENABLE            RT_BIT(4)
#define SUNXI_MMC_DMA_ENABLE            RT_BIT(5)
#define SUNXI_MMC_MEMORY_ACCESS_DONE    RT_BIT(29)
#define SUNXI_MMC_ACCESS_DONE_DIRECT    RT_BIT(30)
#define SUNXI_MMC_ACCESS_BY_AHB         RT_BIT(31)
#define SUNXI_MMC_DDR_MODE              RT_BIT(10)
#define SUNXI_MMC_HW_RESET              (SUNXI_MMC_SOFT_RESET | SUNXI_MMC_FIFO_RESET | SUNXI_MMC_DMA_RESET)

#define SUNXI_MMC_CARD_CLOCK_ON         RT_BIT(16)
#define SUNXI_MMC_MASK_DATA0            RT_BIT(31)

#define SUNXI_MMC_NTSR_2X_TIMING        RT_BIT(31)
#define SUNXI_MMC_NTSR_CMD_SAMPLE_MASK  (0x3U << 4)
#define SUNXI_MMC_NTSR_DATA_SAMPLE_MASK (0x3U << 8)
#define SUNXI_MMC_DRV_DL_AUTO_PHASE     RT_BIT(7)
#define SUNXI_MMC_DRV_DL_CMD_PHASE      RT_BIT(16)
#define SUNXI_MMC_DRV_DL_DATA_PHASE     RT_BIT(17)

#define SUNXI_MMC_RESP_EXPIRE           RT_BIT(6)
#define SUNXI_MMC_LONG_RESPONSE         RT_BIT(7)
#define SUNXI_MMC_CHECK_RESP_CRC        RT_BIT(8)
#define SUNXI_MMC_DATA_EXPIRE           RT_BIT(9)
#define SUNXI_MMC_WRITE                 RT_BIT(10)
#define SUNXI_MMC_SEND_AUTO_STOP        RT_BIT(12)
#define SUNXI_MMC_WAIT_PRE_OVER         RT_BIT(13)
#define SUNXI_MMC_SEND_INIT             RT_BIT(15)
#define SUNXI_MMC_UPCLK_ONLY            RT_BIT(21)
#define SUNXI_MMC_START                 RT_BIT(31)

#define SUNXI_MMC_RESP_ERROR            RT_BIT(1)
#define SUNXI_MMC_COMMAND_DONE          RT_BIT(2)
#define SUNXI_MMC_DATA_OVER             RT_BIT(3)
#define SUNXI_MMC_TX_DATA_REQUEST       RT_BIT(4)
#define SUNXI_MMC_RX_DATA_REQUEST       RT_BIT(5)
#define SUNXI_MMC_RESP_CRC_ERROR        RT_BIT(6)
#define SUNXI_MMC_DATA_CRC_ERROR        RT_BIT(7)
#define SUNXI_MMC_RESP_TIMEOUT          RT_BIT(8)
#define SUNXI_MMC_DATA_TIMEOUT          RT_BIT(9)
#define SUNXI_MMC_FIFO_RUN_ERROR        RT_BIT(11)
#define SUNXI_MMC_HARDWARE_LOCKED       RT_BIT(12)
#define SUNXI_MMC_START_BIT_ERROR       RT_BIT(13)
#define SUNXI_MMC_END_BIT_ERROR         RT_BIT(15)
#define SUNXI_MMC_AUTO_COMMAND_DONE     RT_BIT(14)
#define SUNXI_MMC_ERROR_MASK            (SUNXI_MMC_RESP_ERROR | \
        SUNXI_MMC_RESP_CRC_ERROR | SUNXI_MMC_DATA_CRC_ERROR | \
        SUNXI_MMC_RESP_TIMEOUT | SUNXI_MMC_DATA_TIMEOUT | \
        SUNXI_MMC_FIFO_RUN_ERROR | SUNXI_MMC_HARDWARE_LOCKED | \
        SUNXI_MMC_START_BIT_ERROR | SUNXI_MMC_END_BIT_ERROR)

#define SUNXI_MMC_IDMAC_SOFT_RESET      RT_BIT(0)
#define SUNXI_MMC_IDMAC_FIX_BURST       RT_BIT(1)
#define SUNXI_MMC_IDMAC_ENABLE          RT_BIT(7)
#define SUNXI_MMC_IDMAC_TX_INT          RT_BIT(0)
#define SUNXI_MMC_IDMAC_RX_INT          RT_BIT(1)
#define SUNXI_MMC_IDMAC_FATAL_BUS       RT_BIT(2)
#define SUNXI_MMC_IDMAC_DESC_INVALID    RT_BIT(4)
#define SUNXI_MMC_IDMAC_CARD_ERROR      RT_BIT(5)
#define SUNXI_MMC_IDMAC_ABNORMAL        RT_BIT(9)
#define SUNXI_MMC_IDMAC_ERROR_MASK      (SUNXI_MMC_IDMAC_FATAL_BUS | \
        SUNXI_MMC_IDMAC_DESC_INVALID | SUNXI_MMC_IDMAC_CARD_ERROR | \
        SUNXI_MMC_IDMAC_ABNORMAL)

#define SUNXI_MMC_IDMA_DESC_DIC         RT_BIT(1)
#define SUNXI_MMC_IDMA_DESC_LAST        RT_BIT(2)
#define SUNXI_MMC_IDMA_DESC_FIRST       RT_BIT(3)
#define SUNXI_MMC_IDMA_DESC_CHAIN       RT_BIT(4)
#define SUNXI_MMC_IDMA_DESC_END_RING    RT_BIT(5)
#define SUNXI_MMC_IDMA_DESC_OWN         RT_BIT(31)

#define SUNXI_MMC_FIFO_EMPTY            RT_BIT(2)
#define SUNXI_MMC_FIFO_FULL             RT_BIT(3)
#define SUNXI_MMC_CARD_PRESENT          RT_BIT(8)
#define SUNXI_MMC_CARD_BUSY             RT_BIT(9)

#define SUNXI_MMC_WIDTH_1               0
#define SUNXI_MMC_WIDTH_4               1
#define SUNXI_MMC_WIDTH_8               2
#define SUNXI_MMC_TIMEOUT_MS            1000
#define SUNXI_MMC_CD_DEBOUNCE_MS        50
#define SUNXI_MMC_LEGACY_MAX_CLOCK      25000000
#define SUNXI_MMC_SD_HS_RETRIES         3
#define SUNXI_MMC_IDMA_DESC_SHIFT       2
#define SUNXI_MMC_IDMA_SEG_SIZE         4096U
#define SUNXI_MMC_IDMA_DESC_COUNT       8U
#define SUNXI_MMC_IDMA_MAX_SIZE         (SUNXI_MMC_IDMA_DESC_COUNT * SUNXI_MMC_IDMA_SEG_SIZE)
#define SUNXI_MMC_PIO_MAX_SIZE          4U
/* Burst 8, RX threshold 7, TX threshold 8. */
#define SUNXI_MMC_PIO_FTRGL             ((2U << 28) | (7U << 16) | 8U)
/* F101 IDMA: burst 16, RX threshold 15, TX threshold 240. */
#define SUNXI_MMC_IDMA_FTRGL            ((3U << 28) | (15U << 16) | 240U)

struct sunxi_mmc_idma_desc
{
    rt_uint32_t config;
    rt_uint32_t buf_size;
    rt_uint32_t buf_addr;
    rt_uint32_t next_desc;
};

struct sunxi_mmc
{
    struct rt_mmcsd_host *host;
    struct rt_device *dev;
    struct rt_clk *bus_clk;
    struct rt_clk *mmc_clk;
    struct rt_reset_control *reset;
    void *base;
    struct sunxi_mmc_idma_desc *idma_desc;
    rt_ubase_t idma_desc_dma;
    int irq;
    volatile rt_uint32_t irq_status;
    volatile rt_uint32_t idma_status;
    rt_uint32_t data_done_mask;
    rt_bool_t request_active;
    rt_bool_t wait_idma;
    rt_bool_t irq_installed;
    struct rt_completion completion;
    rt_base_t cd_pin;
    rt_uint8_t cd_present_level;
    rt_bool_t cd_irq_attached;
    struct rt_timer cd_timer;
    rt_bool_t cd_timer_initialized;
    rt_bool_t card_present;
    rt_bool_t card_reported;
    rt_bool_t sd_hs_rejected;
    rt_bool_t no_sdio;
};

static rt_uint32_t sunxi_mmc_read(struct sunxi_mmc *mmc, rt_uint32_t offset)
{
    return HWREG32(mmc->base + offset);
}

static void sunxi_mmc_write(struct sunxi_mmc *mmc, rt_uint32_t offset,
        rt_uint32_t value)
{
    HWREG32(mmc->base + offset) = value;
}

static rt_err_t sunxi_mmc_wait_clear(struct sunxi_mmc *mmc, rt_uint32_t offset,
        rt_uint32_t mask, rt_uint32_t timeout_ms)
{
    rt_tick_t timeout = rt_tick_get() + rt_tick_from_millisecond(timeout_ms);

    while (sunxi_mmc_read(mmc, offset) & mask)
    {
        if ((rt_int32_t)(rt_tick_get() - timeout) >= 0)
        {
            return -RT_ETIMEOUT;
        }
        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

static rt_err_t sunxi_mmc_update_clock(struct sunxi_mmc *mmc, rt_bool_t enable)
{
    rt_uint32_t clock = sunxi_mmc_read(mmc, SUNXI_MMC_CLKCR);
    rt_err_t err;

    if (enable)
    {
        clock |= SUNXI_MMC_CARD_CLOCK_ON;
    }
    else
    {
        clock &= ~SUNXI_MMC_CARD_CLOCK_ON;
    }
    clock |= SUNXI_MMC_MASK_DATA0;
    sunxi_mmc_write(mmc, SUNXI_MMC_CLKCR, clock);
    sunxi_mmc_write(mmc, SUNXI_MMC_CMDR,
            SUNXI_MMC_START | SUNXI_MMC_UPCLK_ONLY | SUNXI_MMC_WAIT_PRE_OVER);
    err = sunxi_mmc_wait_clear(mmc, SUNXI_MMC_CMDR, SUNXI_MMC_START,
            SUNXI_MMC_TIMEOUT_MS);
    sunxi_mmc_write(mmc, SUNXI_MMC_RINTR, 0xffffffff);
    clock = sunxi_mmc_read(mmc, SUNXI_MMC_CLKCR);
    sunxi_mmc_write(mmc, SUNXI_MMC_CLKCR, clock & ~SUNXI_MMC_MASK_DATA0);

    return err;
}

static rt_bool_t sunxi_mmc_is_ddr_timing(rt_uint32_t timing)
{
    return timing == MMCSD_TIMING_UHS_DDR50 ||
            timing == MMCSD_TIMING_MMC_DDR52 ||
            timing == MMCSD_TIMING_MMC_HS400 ||
            timing == MMCSD_TIMING_MMC_HS400_ENH_DS;
}

static void sunxi_mmc_set_timing(struct sunxi_mmc *mmc,
        const struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t drv_dl;
    rt_uint32_t gctrl;

    gctrl = sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL);
    if (sunxi_mmc_is_ddr_timing(io_cfg->timing))
    {
        gctrl |= SUNXI_MMC_DDR_MODE;
    }
    else
    {
        gctrl &= ~SUNXI_MMC_DDR_MODE;
    }
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL, gctrl);

    drv_dl = sunxi_mmc_read(mmc, SUNXI_MMC_DRV_DL);
    /*
     * SMHC0 uses timing mode 1.  The F101 SDK enables 2x clocking in NTSR
     * and leaves DRV_DL at its default phase for 25/50 MHz SDR transfers.
     * Selecting the delayed CMD/DATA phase here samples each byte's first
     * nibble incorrectly on the board's SD socket.
     */
    drv_dl &= ~(SUNXI_MMC_DRV_DL_AUTO_PHASE |
            SUNXI_MMC_DRV_DL_CMD_PHASE | SUNXI_MMC_DRV_DL_DATA_PHASE);
    sunxi_mmc_write(mmc, SUNXI_MMC_DRV_DL, drv_dl);
}

static void sunxi_mmc_set_clock_phase(struct sunxi_mmc *mmc)
{
    rt_uint32_t ntsr;

    ntsr = sunxi_mmc_read(mmc, SUNXI_MMC_NTSR);
    ntsr &= ~(SUNXI_MMC_NTSR_CMD_SAMPLE_MASK |
            SUNXI_MMC_NTSR_DATA_SAMPLE_MASK);
    ntsr |= SUNXI_MMC_NTSR_2X_TIMING;
    sunxi_mmc_write(mmc, SUNXI_MMC_NTSR, ntsr);
}

static void sunxi_mmc_set_iocfg(struct rt_mmcsd_host *host,
        struct rt_mmcsd_io_cfg *io_cfg)
{
    struct sunxi_mmc *mmc = host->private_data;
    struct rt_mmcsd_io_cfg effective_cfg = *io_cfg;
    rt_uint32_t width = SUNXI_MMC_WIDTH_1;
    rt_err_t err;
    rt_err_t rate_err = RT_EOK;

    /*
     * The SD core retains the HS rate reported by CMD6 even when the card
     * rejects the mode switch. Keep the host at the legacy rate in that case.
     */
    if (mmc->sd_hs_rejected &&
            effective_cfg.timing == MMCSD_TIMING_LEGACY &&
            effective_cfg.clock > SUNXI_MMC_LEGACY_MAX_CLOCK)
    {
        effective_cfg.clock = SUNXI_MMC_LEGACY_MAX_CLOCK;
    }

    if (sunxi_mmc_update_clock(mmc, RT_FALSE))
    {
        LOG_E("cannot disable card clock");
        return;
    }

    /* SMHC timing and clock-source registers are writable only while gated. */
    rt_clk_disable_unprepare(mmc->mmc_clk);

    if (effective_cfg.clock)
    {
        /* The controller consumes a module clock twice the card clock. */
        if (rt_clk_set_rate(mmc->mmc_clk, effective_cfg.clock * 2))
        {
            LOG_E("cannot set %u Hz card clock", effective_cfg.clock);
            rate_err = -RT_ERROR;
        }
    }

    if (!rate_err)
    {
        sunxi_mmc_set_timing(mmc, &effective_cfg);
    }

    err = rt_clk_prepare_enable(mmc->mmc_clk);
    if (err)
    {
        LOG_E("cannot configure card timing: %d", err);
        return;
    }
    if (rate_err)
    {
        return;
    }
    sunxi_mmc_set_clock_phase(mmc);

    switch (effective_cfg.bus_width)
    {
    case MMCSD_BUS_WIDTH_4:
        width = SUNXI_MMC_WIDTH_4;
        break;
    case MMCSD_BUS_WIDTH_8:
        width = SUNXI_MMC_WIDTH_8;
        break;
    case MMCSD_BUS_WIDTH_1:
    default:
        break;
    }
    sunxi_mmc_write(mmc, SUNXI_MMC_WIDTH, width);
    if (sunxi_mmc_update_clock(mmc, effective_cfg.clock != 0))
    {
        LOG_E("clock update timed out");
    }
}

static void sunxi_mmc_pio_xfer(struct sunxi_mmc *mmc,
        struct rt_mmcsd_data *data, rt_uint32_t *offset)
{
    rt_uint8_t *buffer = (rt_uint8_t *)data->buf;
    rt_uint32_t total = data->blksize * data->blks;
    rt_uint32_t status = sunxi_mmc_read(mmc, SUNXI_MMC_STAS);

    if (data->flags & DATA_DIR_READ)
    {
        while (!(status & SUNXI_MMC_FIFO_EMPTY) && *offset < total)
        {
            rt_uint32_t value = sunxi_mmc_read(mmc, SUNXI_MMC_FIFO);
            rt_uint32_t remaining = total - *offset;
            rt_uint32_t bytes = remaining < 4 ? remaining : 4;

            rt_memcpy(buffer + *offset, &value, bytes);
            *offset += bytes;
            status = sunxi_mmc_read(mmc, SUNXI_MMC_STAS);
        }
    }
    else
    {
        while (!(status & SUNXI_MMC_FIFO_FULL) && *offset < total)
        {
            rt_uint32_t value = 0;
            rt_uint32_t remaining = total - *offset;
            rt_uint32_t bytes = remaining < 4 ? remaining : 4;

            rt_memcpy(&value, buffer + *offset, bytes);
            sunxi_mmc_write(mmc, SUNXI_MMC_FIFO, value);
            *offset += bytes;
            status = sunxi_mmc_read(mmc, SUNXI_MMC_STAS);
        }
    }
}

static void sunxi_mmc_drain_rxfifo(struct sunxi_mmc *mmc,
        struct rt_mmcsd_data *data, rt_uint32_t *offset)
{
    rt_uint8_t *buffer = (rt_uint8_t *)data->buf;
    rt_uint32_t total = data->blksize * data->blks;

    while (!(sunxi_mmc_read(mmc, SUNXI_MMC_STAS) & SUNXI_MMC_FIFO_EMPTY) &&
            *offset < total)
    {
        rt_uint32_t value = sunxi_mmc_read(mmc, SUNXI_MMC_FIFO);
        rt_uint32_t remaining = total - *offset;
        rt_uint32_t bytes = remaining < 4 ? remaining : 4;

        rt_memcpy(buffer + *offset, &value, bytes);
        *offset += bytes;
    }
}

static void sunxi_mmc_build_idma_desc(struct sunxi_mmc *mmc,
        rt_ubase_t buffer_dma, rt_uint32_t total)
{
    rt_uint32_t count = (total + SUNXI_MMC_IDMA_SEG_SIZE - 1) /
            SUNXI_MMC_IDMA_SEG_SIZE;
    rt_uint32_t offset = 0;
    rt_uint32_t index;

    for (index = 0; index < count; index++)
    {
        struct sunxi_mmc_idma_desc *desc = &mmc->idma_desc[index];
        rt_uint32_t length = rt_min_t(rt_uint32_t,
                total - offset, SUNXI_MMC_IDMA_SEG_SIZE);

        desc->config = SUNXI_MMC_IDMA_DESC_CHAIN |
                SUNXI_MMC_IDMA_DESC_OWN | SUNXI_MMC_IDMA_DESC_DIC;
        desc->buf_size = length;
        desc->buf_addr = (buffer_dma + offset) >>
                SUNXI_MMC_IDMA_DESC_SHIFT;
        desc->next_desc = (mmc->idma_desc_dma +
                (index + 1) * sizeof(*desc)) >> SUNXI_MMC_IDMA_DESC_SHIFT;

        if (index == 0)
        {
            desc->config |= SUNXI_MMC_IDMA_DESC_FIRST;
        }
        if (index + 1 == count)
        {
            desc->config &= ~SUNXI_MMC_IDMA_DESC_DIC;
            desc->config |= SUNXI_MMC_IDMA_DESC_LAST |
                    SUNXI_MMC_IDMA_DESC_END_RING;
            desc->next_desc = 0;
        }
        offset += length;
    }

    rt_hw_cpu_dcache_clean_and_invalidate(mmc->idma_desc,
            count * sizeof(*mmc->idma_desc));
    rt_hw_dsb();
}

static rt_err_t sunxi_mmc_start_idma(struct sunxi_mmc *mmc,
        struct rt_mmcsd_data *data)
{
    rt_uint32_t total = data->blksize * data->blks;
    rt_ubase_t buffer_dma;
    rt_uint32_t gctrl;
    rt_err_t err;

    if (!mmc->irq_installed || !mmc->idma_desc ||
            total > SUNXI_MMC_IDMA_MAX_SIZE)
    {
        return -RT_ENOSYS;
    }

    buffer_dma = (rt_ubase_t)rt_kmem_v2p(data->buf);
    if (!buffer_dma || (buffer_dma & 0x3))
    {
        return -RT_EINVAL;
    }

    /*
     * Clean dirty lines before a read so they cannot overwrite DMA data,
     * and invalidate again after the transfer before the CPU reads it.
     */
    if (data->flags & DATA_DIR_READ)
    {
        rt_hw_cpu_dcache_clean_and_invalidate(data->buf, total);
    }
    else
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data->buf, total);
    }
    sunxi_mmc_build_idma_desc(mmc, buffer_dma, total);

    gctrl = sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL);
    gctrl &= ~SUNXI_MMC_ACCESS_BY_AHB;
    gctrl |= SUNXI_MMC_DMA_ENABLE | SUNXI_MMC_DMA_RESET |
            SUNXI_MMC_FIFO_RESET;
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL, gctrl);
    err = sunxi_mmc_wait_clear(mmc, SUNXI_MMC_GCTRL,
            SUNXI_MMC_DMA_RESET | SUNXI_MMC_FIFO_RESET,
            SUNXI_MMC_TIMEOUT_MS);
    if (err)
    {
        return err;
    }

    sunxi_mmc_write(mmc, SUNXI_MMC_DMAC, SUNXI_MMC_IDMAC_SOFT_RESET);
    err = sunxi_mmc_wait_clear(mmc, SUNXI_MMC_DMAC,
            SUNXI_MMC_IDMAC_SOFT_RESET, SUNXI_MMC_TIMEOUT_MS);
    if (err)
    {
        return err;
    }

    sunxi_mmc_write(mmc, SUNXI_MMC_IDST, 0x337);
    sunxi_mmc_write(mmc, SUNXI_MMC_IDIE,
            (data->flags & DATA_DIR_READ) ? SUNXI_MMC_IDMAC_RX_INT : 0);
    sunxi_mmc_write(mmc, SUNXI_MMC_DLBA, mmc->idma_desc_dma >>
            SUNXI_MMC_IDMA_DESC_SHIFT);
    sunxi_mmc_write(mmc, SUNXI_MMC_FTRGL, SUNXI_MMC_IDMA_FTRGL);
    sunxi_mmc_write(mmc, SUNXI_MMC_DMAC, SUNXI_MMC_IDMAC_FIX_BURST |
            SUNXI_MMC_IDMAC_ENABLE);

    return RT_EOK;
}

static rt_err_t sunxi_mmc_wait_memory_access(struct sunxi_mmc *mmc)
{
    rt_tick_t timeout = rt_tick_get() +
            rt_tick_from_millisecond(SUNXI_MMC_TIMEOUT_MS);

    while (!(sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL) &
            SUNXI_MMC_MEMORY_ACCESS_DONE))
    {
        if ((rt_int32_t)(rt_tick_get() - timeout) >= 0)
        {
            return -RT_ETIMEOUT;
        }
        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

static void sunxi_mmc_stop_idma(struct sunxi_mmc *mmc)
{
    rt_uint32_t gctrl;

    sunxi_mmc_write(mmc, SUNXI_MMC_IMASK, 0);
    sunxi_mmc_write(mmc, SUNXI_MMC_IDIE, 0);
    sunxi_mmc_write(mmc, SUNXI_MMC_IDST, 0x337);
    sunxi_mmc_write(mmc, SUNXI_MMC_DMAC, 0);

    gctrl = sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL);
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL, gctrl | SUNXI_MMC_DMA_RESET);
    sunxi_mmc_wait_clear(mmc, SUNXI_MMC_GCTRL, SUNXI_MMC_DMA_RESET,
            SUNXI_MMC_TIMEOUT_MS);

    gctrl = sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL);
    gctrl &= ~SUNXI_MMC_DMA_ENABLE;
    gctrl |= SUNXI_MMC_ACCESS_BY_AHB | SUNXI_MMC_FIFO_RESET;
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL, gctrl);
    sunxi_mmc_wait_clear(mmc, SUNXI_MMC_GCTRL, SUNXI_MMC_FIFO_RESET,
            SUNXI_MMC_TIMEOUT_MS);
    sunxi_mmc_write(mmc, SUNXI_MMC_FTRGL, SUNXI_MMC_PIO_FTRGL);
}

static void sunxi_mmc_isr(int vector, void *param)
{
    struct sunxi_mmc *mmc = param;
    rt_uint32_t status = sunxi_mmc_read(mmc, SUNXI_MMC_RINTR);
    rt_uint32_t idma_status = sunxi_mmc_read(mmc, SUNXI_MMC_IDST);

    (void)vector;
    if (!status && !idma_status)
    {
        return;
    }

    sunxi_mmc_write(mmc, SUNXI_MMC_RINTR, status);
    sunxi_mmc_write(mmc, SUNXI_MMC_IDST, idma_status);
    mmc->irq_status |= status;
    mmc->idma_status |= idma_status;

    if (!mmc->request_active)
    {
        return;
    }

    if ((mmc->irq_status & SUNXI_MMC_ERROR_MASK) ||
            (mmc->idma_status & SUNXI_MMC_IDMAC_ERROR_MASK) ||
            ((mmc->irq_status & mmc->data_done_mask) &&
            (!mmc->wait_idma ||
             (mmc->idma_status & SUNXI_MMC_IDMAC_RX_INT))))
    {
        rt_completion_done(&mmc->completion);
    }
}

static rt_err_t sunxi_mmc_reset_fifo(struct sunxi_mmc *mmc)
{
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL,
            sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL) | SUNXI_MMC_FIFO_RESET);

    return sunxi_mmc_wait_clear(mmc, SUNXI_MMC_GCTRL,
            SUNXI_MMC_FIFO_RESET, SUNXI_MMC_TIMEOUT_MS);
}

static rt_err_t sunxi_mmc_wait_busy(struct sunxi_mmc *mmc, rt_uint32_t timeout_ms)
{
    rt_tick_t timeout = rt_tick_get() + rt_tick_from_millisecond(timeout_ms);

    while (sunxi_mmc_read(mmc, SUNXI_MMC_STAS) & SUNXI_MMC_CARD_BUSY)
    {
        if ((rt_int32_t)(rt_tick_get() - timeout) >= 0)
        {
            return -RT_ETIMEOUT;
        }
        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

static void sunxi_mmc_request(struct rt_mmcsd_host *host,
        struct rt_mmcsd_req *request)
{
    rt_uint32_t command;
    rt_uint32_t status = 0;
    rt_uint32_t idma_status = 0;
    rt_uint32_t idma_imask = 0;
    rt_uint32_t transferred = 0;
    rt_tick_t timeout;
    rt_err_t err = RT_EOK;
    rt_bool_t use_idma = RT_FALSE;
    struct rt_mmcsd_cmd *cmd = request->cmd;
    struct rt_mmcsd_data *data = request->data;
    struct sunxi_mmc *mmc = host->private_data;
    rt_uint8_t *switch_status;
    rt_uint8_t cmd6_hs_attempt = 0;

    /* Let a fixed SD-only slot skip the generic core's SDIO CMD5 probe. */
    if (mmc->no_sdio && cmd->cmd_code == SD_IO_SEND_OP_COND)
    {
        cmd->err = -RT_EIO;
        if (data)
        {
            data->err = -RT_EIO;
            data->bytes_xfered = 0;
        }
        mmcsd_req_complete(host);
        return;
    }

    command = SUNXI_MMC_START | (cmd->cmd_code & 0x3f);
    if (cmd->cmd_code == GO_IDLE_STATE)
    {
        command |= SUNXI_MMC_SEND_INIT;
    }
    if (resp_type(cmd) != RESP_NONE)
    {
        command |= SUNXI_MMC_RESP_EXPIRE;
        if (resp_type(cmd) == RESP_R2)
        {
            command |= SUNXI_MMC_LONG_RESPONSE | SUNXI_MMC_CHECK_RESP_CRC;
        }
        else if (resp_type(cmd) != RESP_R3 && resp_type(cmd) != RESP_R4)
        {
            command |= SUNXI_MMC_CHECK_RESP_CRC;
        }
    }

_retry_cmd:
    status = 0;
    transferred = 0;
    err = RT_EOK;

    if (data)
    {
        command |= SUNXI_MMC_DATA_EXPIRE | SUNXI_MMC_WAIT_PRE_OVER;
        if (data->flags & DATA_DIR_WRITE)
        {
            command |= SUNXI_MMC_WRITE;
        }
        if (data->blks > 1)
        {
            /* F101 SMHC0 uses block mode plus its internal CMD12. */
            command |= SUNXI_MMC_SEND_AUTO_STOP;
        }
        sunxi_mmc_write(mmc, SUNXI_MMC_BLKSZ, data->blksize);
        sunxi_mmc_write(mmc, SUNXI_MMC_BCNTR, data->blksize * data->blks);

        use_idma = data->blksize * data->blks > SUNXI_MMC_PIO_MAX_SIZE;
        if (use_idma && sunxi_mmc_start_idma(mmc, data))
        {
            sunxi_mmc_stop_idma(mmc);
            use_idma = RT_FALSE;
        }
    }

    sunxi_mmc_write(mmc, SUNXI_MMC_RINTR, 0xffffffff);
    if (use_idma)
    {
        mmc->irq_status = 0;
        mmc->idma_status = 0;
        mmc->data_done_mask = data->blks > 1 ? SUNXI_MMC_AUTO_COMMAND_DONE :
                SUNXI_MMC_DATA_OVER;
        mmc->wait_idma = !!(data->flags & DATA_DIR_READ);
        mmc->request_active = RT_TRUE;
        rt_completion_init(&mmc->completion);
        /* CMD_DONE is diagnostic only; data completion remains authoritative. */
        idma_imask = SUNXI_MMC_ERROR_MASK | SUNXI_MMC_COMMAND_DONE |
                mmc->data_done_mask;
        sunxi_mmc_write(mmc, SUNXI_MMC_IMASK, idma_imask);
        sunxi_mmc_write(mmc, SUNXI_MMC_CARG, cmd->arg);
        sunxi_mmc_write(mmc, SUNXI_MMC_CMDR, command);

        err = rt_completion_wait(&mmc->completion,
                rt_tick_from_millisecond(SUNXI_MMC_TIMEOUT_MS));
        status = mmc->irq_status;
        idma_status = mmc->idma_status;
        mmc->request_active = RT_FALSE;
        sunxi_mmc_write(mmc, SUNXI_MMC_IMASK, 0);

        if (err)
        {
            LOG_E("IDMA transfer timed out: cmd=%u event=%08x/%08x",
                    cmd->cmd_code, status, idma_status);
            err = -RT_ETIMEOUT;
        }
        if (status & SUNXI_MMC_ERROR_MASK)
        {
            err = (status & (SUNXI_MMC_RESP_TIMEOUT | SUNXI_MMC_DATA_TIMEOUT)) ?
                    -RT_ETIMEOUT : -RT_EIO;
        }
        if (idma_status & SUNXI_MMC_IDMAC_ERROR_MASK)
        {
            LOG_E("IDMA transfer failed: cmd=%u rintr=%08x idst=%08x",
                    cmd->cmd_code, status, idma_status);
            err = -RT_EIO;
        }
        if (!err && (mmc->wait_idma &&
                !(idma_status & SUNXI_MMC_IDMAC_RX_INT)))
        {
            err = -RT_EIO;
        }
        if (!err && !(status & mmc->data_done_mask))
        {
            err = -RT_EIO;
        }
        if (!err)
        {
            err = sunxi_mmc_wait_memory_access(mmc);
        }
        if (!err && (data->flags & DATA_DIR_READ))
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf,
                    data->blksize * data->blks);
        }
        if (!err)
        {
            transferred = data->blksize * data->blks;
        }
        sunxi_mmc_stop_idma(mmc);
    }
    else
    {
        sunxi_mmc_write(mmc, SUNXI_MMC_CARG, cmd->arg);
        sunxi_mmc_write(mmc, SUNXI_MMC_CMDR, command);

        timeout = rt_tick_get() + rt_tick_from_millisecond(SUNXI_MMC_TIMEOUT_MS);
        for (;;)
        {
            if (data)
            {
                sunxi_mmc_pio_xfer(mmc, data, &transferred);
            }

            status = sunxi_mmc_read(mmc, SUNXI_MMC_RINTR);
            if (status & SUNXI_MMC_ERROR_MASK)
            {
                err = (status & (SUNXI_MMC_RESP_TIMEOUT | SUNXI_MMC_DATA_TIMEOUT)) ?
                        -RT_ETIMEOUT : -RT_EIO;
                break;
            }
            if ((!data && (status & SUNXI_MMC_COMMAND_DONE)) ||
                    (data && (status & (SUNXI_MMC_DATA_OVER |
                                        SUNXI_MMC_AUTO_COMMAND_DONE))))
            {
                break;
            }
            if ((rt_int32_t)(rt_tick_get() - timeout) >= 0)
            {
                err = -RT_ETIMEOUT;
                break;
            }
            rt_hw_cpu_relax();
        }

        if (!err && data && (data->flags & DATA_DIR_READ))
        {
            sunxi_mmc_drain_rxfifo(mmc, data, &transferred);
        }
        if (!err && data && transferred != data->blksize * data->blks)
        {
            err = -RT_EIO;
        }
    }

_complete:
    sunxi_mmc_write(mmc, SUNXI_MMC_RINTR, status);
    if (!err)
    {
        if (resp_type(cmd) == RESP_R2)
        {
            cmd->resp[0] = sunxi_mmc_read(mmc, SUNXI_MMC_RESP3);
            cmd->resp[1] = sunxi_mmc_read(mmc, SUNXI_MMC_RESP2);
            cmd->resp[2] = sunxi_mmc_read(mmc, SUNXI_MMC_RESP1);
            cmd->resp[3] = sunxi_mmc_read(mmc, SUNXI_MMC_RESP0);
        }
        else if (resp_type(cmd) != RESP_NONE)
        {
            cmd->resp[0] = sunxi_mmc_read(mmc, SUNXI_MMC_RESP0);
        }
        if (resp_type(cmd) == RESP_R1B)
        {
            err = sunxi_mmc_wait_busy(mmc, cmd->busy_timeout ?
                    cmd->busy_timeout : SUNXI_MMC_TIMEOUT_MS);
        }
    }

    if (cmd->cmd_code == SD_SWITCH && data && !err)
    {
        switch_status = (rt_uint8_t *)data->buf;

        if ((cmd->arg & RT_BIT(31)) && (cmd->arg & 0xf) == 1 &&
                (switch_status[16] & 0xf) != 1)
        {
            if (++cmd6_hs_attempt < SUNXI_MMC_SD_HS_RETRIES)
            {
                rt_thread_mdelay(5);
                goto _retry_cmd;
            }
            mmc->sd_hs_rejected = RT_TRUE;
            LOG_W("SD card rejected high-speed mode after %u tries; using 25 MHz legacy timing",
                    cmd6_hs_attempt);
        }
    }

    cmd->err = err;
    if (data)
    {
        data->err = err;
        data->bytes_xfered = err ? 0 : transferred;
    }
    mmcsd_req_complete(host);
}

static rt_int32_t sunxi_mmc_get_card_status(struct rt_mmcsd_host *host)
{
    struct sunxi_mmc *mmc = host->private_data;

    if (mmc->cd_pin >= 0)
    {
        return rt_pin_read(mmc->cd_pin) == mmc->cd_present_level;
    }

    return !!(sunxi_mmc_read(mmc, SUNXI_MMC_STAS) & SUNXI_MMC_CARD_PRESENT);
}

static rt_bool_t sunxi_mmc_sample_card_detect(struct sunxi_mmc *mmc)
{
    return rt_pin_read(mmc->cd_pin) == mmc->cd_present_level;
}

static void sunxi_mmc_card_detect(void *param);

static rt_uint8_t sunxi_mmc_card_detect_irq_mode(struct sunxi_mmc *mmc)
{
    rt_uint8_t next_level = mmc->card_present ?
            !mmc->cd_present_level : mmc->cd_present_level;

    return next_level ? PIN_IRQ_MODE_RISING : PIN_IRQ_MODE_FALLING;
}

static void sunxi_mmc_card_detect_disarm(struct sunxi_mmc *mmc)
{
    if (mmc->cd_irq_attached)
    {
        rt_pin_irq_enable(mmc->cd_pin, PIN_IRQ_DISABLE);
        rt_pin_detach_irq(mmc->cd_pin);
        mmc->cd_irq_attached = RT_FALSE;
    }
}

static rt_err_t sunxi_mmc_card_detect_arm(struct sunxi_mmc *mmc)
{
    rt_err_t err;
    rt_uint8_t mode;

    sunxi_mmc_card_detect_disarm(mmc);
    mode = sunxi_mmc_card_detect_irq_mode(mmc);

    err = rt_pin_attach_irq(mmc->cd_pin, mode, sunxi_mmc_card_detect, mmc);
    if (err)
    {
        return err;
    }

    err = rt_pin_irq_enable(mmc->cd_pin, PIN_IRQ_ENABLE);
    if (err)
    {
        rt_pin_detach_irq(mmc->cd_pin);
        return err;
    }

    mmc->cd_irq_attached = RT_TRUE;

    return RT_EOK;
}

static void sunxi_mmc_card_detect_debounce(void *param)
{
    struct sunxi_mmc *mmc = param;
    rt_bool_t present;
    rt_err_t err;

    sunxi_mmc_card_detect_disarm(mmc);
    rt_pin_mode(mmc->cd_pin, PIN_MODE_INPUT_PULLUP);
    present = sunxi_mmc_sample_card_detect(mmc);
    mmc->card_present = present;
    err = sunxi_mmc_card_detect_arm(mmc);
    if (err)
    {
        LOG_E("cannot arm card-detect interrupt: %d", err);
    }

    if (present == mmc->card_reported)
    {
        return;
    }

    mmc->card_reported = present;
    if (!present)
    {
        mmc->sd_hs_rejected = RT_FALSE;
    }

    mmcsd_change(mmc->host);
}

static void sunxi_mmc_card_detect(void *param)
{
    struct sunxi_mmc *mmc = param;

    /*
     * PF_DAT is invalid when the pin is multiplexed as an EINT. Use the EINT
     * only as a wakeup source and sample the pin after returning to GPIO mode.
     */
    rt_pin_irq_enable(mmc->cd_pin, PIN_IRQ_DISABLE);
    rt_timer_start(&mmc->cd_timer);
}

static rt_bool_t sunxi_mmc_card_busy(struct rt_mmcsd_host *host)
{
    struct sunxi_mmc *mmc = host->private_data;

    return !!(sunxi_mmc_read(mmc, SUNXI_MMC_STAS) & SUNXI_MMC_CARD_BUSY);
}

static const struct rt_mmcsd_host_ops sunxi_mmc_ops =
{
    .request = sunxi_mmc_request,
    .set_iocfg = sunxi_mmc_set_iocfg,
    .get_card_status = sunxi_mmc_get_card_status,
    .card_busy = sunxi_mmc_card_busy,
};

static rt_err_t sunxi_mmc_hw_init(struct sunxi_mmc *mmc)
{
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL,
            sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL) | SUNXI_MMC_HW_RESET);
    if (sunxi_mmc_wait_clear(mmc, SUNXI_MMC_GCTRL, SUNXI_MMC_HW_RESET, 250))
    {
        return -RT_ETIMEOUT;
    }
    sunxi_mmc_write(mmc, SUNXI_MMC_GCTRL,
            (sunxi_mmc_read(mmc, SUNXI_MMC_GCTRL) |
            SUNXI_MMC_INT_ENABLE | SUNXI_MMC_ACCESS_DONE_DIRECT) &
            ~SUNXI_MMC_ACCESS_BY_AHB);
    sunxi_mmc_write(mmc, SUNXI_MMC_FTRGL, SUNXI_MMC_PIO_FTRGL);
    sunxi_mmc_write(mmc, SUNXI_MMC_TMOUT, 0xffffffff);
    sunxi_mmc_write(mmc, SUNXI_MMC_IMASK, 0);
    sunxi_mmc_write(mmc, SUNXI_MMC_RINTR, 0xffffffff);

    return RT_EOK;
}

static void sunxi_mmc_free(struct sunxi_mmc *mmc)
{
    if (mmc->irq_installed)
    {
        rt_hw_interrupt_mask(mmc->irq);
        rt_pic_detach_irq(mmc->irq, mmc);
    }
    if (mmc->cd_timer_initialized)
    {
        rt_timer_stop(&mmc->cd_timer);
        rt_timer_detach(&mmc->cd_timer);
    }
    if (mmc->cd_irq_attached)
    {
        rt_pin_irq_enable(mmc->cd_pin, PIN_IRQ_DISABLE);
        rt_pin_detach_irq(mmc->cd_pin);
    }
    if (mmc->host)
    {
        mmcsd_free_host(mmc->host);
    }
    if (mmc->idma_desc)
    {
        rt_dma_free_coherent(mmc->dev,
                SUNXI_MMC_IDMA_DESC_COUNT * sizeof(*mmc->idma_desc),
                mmc->idma_desc, mmc->idma_desc_dma);
    }
    if (!rt_is_err_or_null(mmc->reset))
    {
        rt_reset_control_put(mmc->reset);
    }
    if (!rt_is_err_or_null(mmc->mmc_clk))
    {
        rt_clk_disable_unprepare(mmc->mmc_clk);
        rt_clk_put(mmc->mmc_clk);
    }
    if (!rt_is_err_or_null(mmc->bus_clk))
    {
        rt_clk_disable_unprepare(mmc->bus_clk);
        rt_clk_put(mmc->bus_clk);
    }
    if (mmc->base)
    {
        rt_iounmap(mmc->base);
    }
    rt_free(mmc);
}

static rt_err_t sunxi_mmc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint8_t unused_mode;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_mmc *mmc = rt_calloc(1, sizeof(*mmc));

    if (!mmc)
    {
        return -RT_ENOMEM;
    }
    mmc->dev = dev;
    mmc->cd_pin = -1;
    mmc->irq = -1;
    mmc->base = rt_dm_dev_iomap(dev, 0);
    if (!mmc->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    mmc->bus_clk = rt_clk_get_by_name(dev, "ahb");
    mmc->mmc_clk = rt_clk_get_by_name(dev, "mmc");
    if (rt_is_err(mmc->bus_clk) || rt_is_err(mmc->mmc_clk))
    {
        err = rt_is_err(mmc->bus_clk) ? rt_ptr_err(mmc->bus_clk) :
                rt_ptr_err(mmc->mmc_clk);
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(mmc->bus_clk)) ||
            (err = rt_clk_prepare_enable(mmc->mmc_clk)))
    {
        goto _fail;
    }
    mmc->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(mmc->reset))
    {
        err = rt_ptr_err(mmc->reset);
        goto _fail;
    }
    if (mmc->reset && (err = rt_reset_control_deassert(mmc->reset)))
    {
        goto _fail;
    }
    if ((err = sunxi_mmc_hw_init(mmc)))
    {
        goto _fail;
    }
    mmc->host = mmcsd_alloc_host();
    if (!mmc->host)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    mmc->host->ops = &sunxi_mmc_ops;
    mmc->host->freq_min = 400000;
    mmc->host->freq_max = 50000000;
    mmc->host->valid_ocr = VDD_31_32 | VDD_32_33 | VDD_33_34;
    mmc->host->private_data = mmc;
    mmc->irq = rt_dm_dev_get_irq(dev, 0);
    if (mmc->irq >= 0)
    {
        mmc->idma_desc = rt_dma_alloc_coherent(dev,
                SUNXI_MMC_IDMA_DESC_COUNT * sizeof(*mmc->idma_desc),
                &mmc->idma_desc_dma);
        if (mmc->idma_desc)
        {
            rt_hw_interrupt_install(mmc->irq, sunxi_mmc_isr, mmc,
                    "sunxi-mmc");
            rt_hw_interrupt_umask(mmc->irq);
            mmc->irq_installed = RT_TRUE;
            mmc->host->max_seg_size = SUNXI_MMC_IDMA_SEG_SIZE;
            mmc->host->max_dma_segs = SUNXI_MMC_IDMA_DESC_COUNT;
            mmc->host->max_blk_size = 512;
            mmc->host->max_blk_count = SUNXI_MMC_IDMA_MAX_SIZE / 512;
        }
        else
        {
            LOG_W("IDMA descriptor unavailable; using PIO");
        }
    }
    else
    {
        LOG_W("MMC interrupt unavailable; using PIO");
    }
    mmc->no_sdio = rt_dm_dev_prop_read_bool(dev, "no-sdio");
    if ((err = sdio_ofw_parse(dev->ofw_node, mmc->host)))
    {
        goto _fail;
    }
    sdio_host_set_name(mmc->host, RT_NULL);

    mmc->cd_pin = rt_pin_get_named_pin(dev, "cd", 0, &unused_mode,
            &mmc->cd_present_level);
    if (mmc->cd_pin >= 0)
    {
        rt_pin_mode(mmc->cd_pin, PIN_MODE_INPUT_PULLUP);
        mmc->card_present = sunxi_mmc_sample_card_detect(mmc);
        mmc->card_reported = RT_FALSE;
        rt_timer_init(&mmc->cd_timer, "sdc-cd", sunxi_mmc_card_detect_debounce,
                mmc, rt_tick_from_millisecond(SUNXI_MMC_CD_DEBOUNCE_MS),
                RT_TIMER_FLAG_ONE_SHOT);
        mmc->cd_timer_initialized = RT_TRUE;
        err = sunxi_mmc_card_detect_arm(mmc);
        if (err)
        {
            LOG_W("card-detect interrupt unavailable: %d", err);
        }
    }
    else
    {
        mmc->cd_pin = -1;
    }

    dev->user_data = mmc;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, mmc);
    if (mmc->cd_timer_initialized)
    {
        rt_timer_start(&mmc->cd_timer);
    }
    else
    {
        mmcsd_change(mmc->host);
    }

    return RT_EOK;

_fail:
    sunxi_mmc_free(mmc);
    return err;
}

static rt_err_t sunxi_mmc_remove(struct rt_platform_device *pdev)
{
    struct sunxi_mmc *mmc = pdev->parent.user_data;

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    sunxi_mmc_free(mmc);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_mmc_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-mmc" },
    { .compatible = "allwinner,sun252i-f101-emmc" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_mmc_driver =
{
    .name = "sunxi-mmc",
    .ids = sunxi_mmc_ofw_ids,
    .probe = sunxi_mmc_probe,
    .remove = sunxi_mmc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_mmc_driver);
