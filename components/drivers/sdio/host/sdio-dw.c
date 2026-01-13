/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 * 2023-02-25     GuEe-GUI     add EDMA support
 */

#include <rtthread.h>

#define DBG_TAG "sdio.dw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>

#include "sdio-dw.h"

/* Common flag combinations */
#define PINT(x)                     SDIO_DW_INT_##x
#define SDIO_DW_DATA_ERROR_FLAGS    (PINT(DRTO) | PINT(DCRC) | PINT(HTO) | PINT(SBE) | PINT(EBE) | PINT(HLE))
#define SDIO_DW_CMD_ERROR_FLAGS     (PINT(RTO) | PINT(RCRC) | PINT(RESP_ERR) | PINT(HLE))
#define SDIO_DW_ERROR_FLAGS         (SDIO_DW_DATA_ERROR_FLAGS | SDIO_DW_CMD_ERROR_FLAGS)
#define SDIO_DW_SEND_STATUS         1
#define SDIO_DW_RECV_STATUS         2
#define SDIO_DW_DMA_THRESHOLD       16

#define SDIO_DW_FREQ_HZ_MAX         200000000
#define SDIO_DW_FREQ_HZ_MIN         100000

#define PINTC(x)                    SDIO_DW_IDMAC_INT_##x
#define SDIO_DW_IDMAC_INT_CLR       (PINTC(AI) | PINTC(NI) | PINTC(CES) | PINTC(DU) | PINTC(FBE) | PINTC(RI) | PINTC(TI))

#define DESC_RING_BUF_SZ            ARCH_PAGE_SIZE
#define NSEC_PER_SEC                1000000000L
#define USEC_PER_MSEC               1000L
#define MSEC_PER_SEC                1000L

struct idmac_desc64
{
    rt_uint32_t des0;   /* Control descriptor */
#define IDMAC_OWN_CLR64(x) !((x) & rt_cpu_to_le32(IDMAC_DES0_OWN))

    rt_uint32_t des1;   /* Reserved */

    rt_uint32_t des2;   /* Buffer sizes */
#define IDMAC_64ADDR_SET_BUFFER1_SIZE(d, s) \
    ((d)->des2 = ((d)->des2 & rt_cpu_to_le32(0x03ffe000)) | ((rt_cpu_to_le32(s)) & rt_cpu_to_le32(0x1fff)))

    rt_uint32_t des3;   /* Reserved */

    rt_uint32_t des4;   /* Lower 32-bits of buffer address pointer 1 */
    rt_uint32_t des5;   /* Upper 32-bits of buffer address pointer 1 */

    rt_uint32_t des6;   /* Lower 32-bits of next descriptor address */
    rt_uint32_t des7;   /* Upper 32-bits of next descriptor address */
};

struct idmac_desc32
{
    rt_le32_t des0;     /* Control Descriptor */
#define IDMAC_DES0_DIC  RT_BIT(1)
#define IDMAC_DES0_LD   RT_BIT(2)
#define IDMAC_DES0_FD   RT_BIT(3)
#define IDMAC_DES0_CH   RT_BIT(4)
#define IDMAC_DES0_ER   RT_BIT(5)
#define IDMAC_DES0_CES  RT_BIT(30)
#define IDMAC_DES0_OWN  RT_BIT(31)
    rt_le32_t des1;     /* Buffer sizes */

#define IDMAC_32ADDR_SET_BUFFER1_SIZE(d, s) \
    ((d)->des1 = ((d)->des1 & rt_cpu_to_le32(0x03ffe000)) | (rt_cpu_to_le32((s) & 0x1fff)))

    rt_le32_t des2;     /* Buffer 1 physical address */
    rt_le32_t des3;     /* Buffer 2 physical address */
};

/* Each descriptor can transfer up to 4KB of data in chained mode */
#define DW_MCI_DESC_DATA_LENGTH 0x1000

static rt_bool_t sdio_dw_ctrl_reset(struct sdio_dw *sd, rt_uint32_t reset)
{
    rt_uint32_t ctrl;
    rt_tick_t start;
    int timeout = rt_tick_from_millisecond(500);

    ctrl = sdio_dw_readl(sd, CTRL);
    ctrl |= reset;
    sdio_dw_writel(sd, CTRL, ctrl);

    start = rt_tick_get();

    while ((sdio_dw_readl(sd, CTRL) & reset))
    {
        if ((rt_tick_get() - start) > timeout)
        {
            LOG_E("Timeout resetting block (ctrl reset 0x%x)", ctrl & reset);

            return RT_FALSE;
        }

        rt_hw_cpu_relax();
    }

    return RT_TRUE;
}

static void sdio_dw_wait_while_busy(struct sdio_dw *sd, rt_uint32_t cmd_flags)
{
    if ((cmd_flags & SDIO_DW_CMD_PRV_DAT_WAIT) && !(cmd_flags & SDIO_DW_CMD_VOLT_SWITCH))
    {
        rt_tick_t start = rt_tick_get();
        int timeout = rt_tick_from_millisecond(500);

        while ((sdio_dw_readl(sd, STATUS) & SDIO_DW_STATUS_BUSY))
        {
            if ((rt_tick_get() - start) > timeout)
            {
                LOG_E("Wait busy fail");

                break;
            }

            rt_hw_cpu_relax();
        }
    }
}

static void sdio_dw_send_cmd(struct sdio_dw_slot *slot, rt_uint32_t cmd, rt_uint32_t arg)
{
    rt_tick_t start;
    struct sdio_dw *sd = slot->sd;
    int timeout = rt_tick_from_millisecond(500);

    sdio_dw_writel(sd, CMDARG, arg);
    rt_hw_wmb();
    sdio_dw_wait_while_busy(sd, cmd);
    sdio_dw_writel(sd, CMD, SDIO_DW_CMD_START | cmd);

    start = rt_tick_get();

    while ((sdio_dw_readl(sd, CMD) & SDIO_DW_CMD_START))
    {
        if ((rt_tick_get() - start) > timeout)
        {
            LOG_E("Wait command start fail");

            break;
        }

        rt_hw_cpu_relax();
    }
}

rt_inline void sdio_dw_set_cto(struct sdio_dw *sd)
{
    rt_ubase_t level;
    rt_uint32_t cto_clks, cto_div, cto_ms;

    cto_clks = sdio_dw_readl(sd, TMOUT) & 0xff;
    cto_div = (sdio_dw_readl(sd, CLKDIV) & 0xff) * 2;

    if (cto_div == 0)
    {
        cto_div = 1;
    }

    cto_ms = RT_DIV_ROUND_UP_ULL((rt_uint64_t)MSEC_PER_SEC * cto_clks * cto_div,
            sd->bus_hz);

    /* Add a bit spare time */
    cto_ms += 10;

    /*
     * The durations we're working with are fairly short so we have to be extra
     * careful about synchronization here.  Specifically in hardware a command
     * timeout is _at most_ 5.1 ms, so that means we expect an interrupt
     * (either command done or timeout) to come rather quickly after the
     * sdio_dw_writel.  ...but just in case we have a long interrupt latency
     * let's add a bit of paranoia.
     *
     * In general we'll assume that at least an interrupt will be asserted in
     * hardware by the time the cto_timer runs.  ...and if it hasn't been
     * asserted in hardware by that time then we'll assume it'll never come.
     */
    level = rt_spin_lock_irqsave(&sd->irq_lock);

    if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_CMD_COMPLETE))
    {
        rt_tick_t tick = rt_tick_from_millisecond(cto_ms) + 1;

        rt_timer_control(&sd->cto_timer, RT_TIMER_CTRL_SET_TIME, &tick);

        rt_timer_start(&sd->cto_timer);
    }

    rt_spin_unlock_irqrestore(&sd->irq_lock, level);
}

static void sdio_dw_start_cmd(struct sdio_dw_slot *slot, rt_uint32_t cmd,
        rt_uint32_t arg)
{
    struct sdio_dw *sd = slot->sd;

    sdio_dw_writel(sd, CMDARG, arg);
    rt_hw_wmb();
    sdio_dw_wait_while_busy(sd, cmd);
    sdio_dw_writel(sd, CMD, SDIO_DW_CMD_START | cmd);

    /* Response expected command only */
    if ((cmd & SDIO_DW_CMD_RESP_EXP))
    {
        sdio_dw_set_cto(sd);
    }
}

rt_inline void send_stop_abort(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    struct rt_mmcsd_cmd *stop = &sd->stop_abort;

    sdio_dw_start_cmd(sd->slot, sd->stop_cmdr, stop->arg);
}

/* DMA interface functions */
static void sdio_dw_stop_dma(struct sdio_dw *sd)
{
    if (sd->using_dma)
    {
        sd->dma_ops->stop(sd);
        sd->dma_ops->cleanup(sd);
    }

    /* Data transfer was stopped by the interrupt handler */
    rt_bitmap_set_bit(&sd->pending_events, EVENT_XFER_COMPLETE);
}

static rt_uint32_t sdio_dw_prep_stop_abort(struct sdio_dw *sd, struct rt_mmcsd_cmd *cmd)
{
    rt_uint32_t cmdr;
    struct rt_mmcsd_cmd *stop;

    if (!cmd->data)
    {
        return 0;
    }

    stop = &sd->stop_abort;
    cmdr = cmd->cmd_code;
    rt_memset(stop, 0, sizeof(*stop));

    if (cmdr == READ_SINGLE_BLOCK ||
        cmdr == READ_MULTIPLE_BLOCK ||
        cmdr == WRITE_BLOCK ||
        cmdr == WRITE_MULTIPLE_BLOCK ||
        cmdr == SEND_TUNING_BLOCK ||
        cmdr == SEND_TUNING_BLOCK_HS200 ||
        cmdr == GEN_CMD)
    {
        stop->cmd_code = STOP_TRANSMISSION;
        stop->arg = 0;
        stop->flags = CMD_AC;
    }
    else if (cmdr == SD_IO_RW_EXTENDED)
    {
        stop->cmd_code = SD_IO_RW_DIRECT;
        stop->arg |= (1 << 31) | (0 << 28) | ((cmd->arg >> 28) & 0x7);
        stop->flags = RESP_SPI_R5 | CMD_AC;
    }
    else
    {
        return 0;
    }

    cmdr = stop->cmd_code | SDIO_DW_CMD_STOP | SDIO_DW_CMD_RESP_CRC | SDIO_DW_CMD_RESP_EXP;

    if (!rt_bitmap_test_bit(&sd->slot->flags, DW_MMC_CARD_NO_USE_HOLD))
    {
        cmdr |= SDIO_DW_CMD_USE_HOLD_REG;
    }

    return cmdr;
}

static void sdio_dw_idmac_reset(struct sdio_dw *sd)
{
    /* Software reset of DMA */
    sdio_dw_writel(sd, BMOD, sdio_dw_readl(sd, BMOD) | SDIO_DW_IDMAC_SWRESET);
}

static rt_err_t sdio_dw_idmac_init(struct sdio_dw *sd)
{
    int i;
    rt_err_t err = RT_EOK;

    if (sd->dma_64bit_address)
    {
        struct idmac_desc64 *p;
        /* Number of descriptors in the ring buffer */
        sd->ring_size = DESC_RING_BUF_SZ / sizeof(struct idmac_desc64);

        /* Forward link the descriptor list */
        for (i = 0, p = sd->dma_buf; i < sd->ring_size - 1; ++i, ++p)
        {
            p->des6 = (sd->dma_buf_phy + (sizeof(struct idmac_desc64) * (i + 1))) & 0xffffffff;
            p->des7 = (rt_uint64_t)(sd->dma_buf_phy + (sizeof(struct idmac_desc64) * (i + 1))) >> 32;
            /* Initialize reserved and buffer size fields to "0" */
            p->des0 = 0;
            p->des1 = 0;
            p->des2 = 0;
            p->des3 = 0;
        }

        /* Set the last descriptor as the end-of-ring descriptor */
        p->des6 = sd->dma_buf_phy & 0xffffffff;
        p->des7 = (rt_uint64_t)sd->dma_buf_phy >> 32;
        p->des0 = IDMAC_DES0_ER;
    }
    else
    {
        struct idmac_desc32 *p;
        /* Number of descriptors in the ring buffer */
        sd->ring_size = DESC_RING_BUF_SZ / sizeof(struct idmac_desc32);

        /* Forward link the descriptor list */
        for (i = 0, p = sd->dma_buf; i < sd->ring_size - 1; ++i, ++p)
        {
            p->des3 = rt_cpu_to_le32(sd->dma_buf_phy + (sizeof(struct idmac_desc32) * (i + 1)));
            p->des0 = 0;
            p->des1 = 0;
        }

        /* Set the last descriptor as the end-of-ring descriptor */
        p->des3 = rt_cpu_to_le32(sd->dma_buf_phy);
        p->des0 = rt_cpu_to_le32(IDMAC_DES0_ER);
    }

    sdio_dw_idmac_reset(sd);

    if (sd->dma_64bit_address)
    {
        /* Mask out interrupts - get Tx & Rx complete only */
        sdio_dw_writel(sd, IDSTS64, SDIO_DW_IDMAC_INT_CLR);
        sdio_dw_writel(sd, IDINTEN64, PINTC(NI) | PINTC(RI) | PINTC(TI));

        /* Set the descriptor base address */
        sdio_dw_writel(sd, DBADDRL, sd->dma_buf_phy & 0xffffffff);
        sdio_dw_writel(sd, DBADDRU, (rt_uint64_t)sd->dma_buf_phy >> 32);
    }
    else
    {
        /* Mask out interrupts - get Tx & Rx complete only */
        sdio_dw_writel(sd, IDSTS, SDIO_DW_IDMAC_INT_CLR);
        sdio_dw_writel(sd, IDINTEN, PINTC(NI) | PINTC(RI) | PINTC(TI));

        /* Set the descriptor base address */
        sdio_dw_writel(sd, DBADDR, sd->dma_buf_phy);
    }

    return err;
}

rt_inline rt_err_t sdio_dw_prepare_desc64(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    rt_uint32_t desc_len;
    rt_uint64_t mem_addr;
    int timeout = rt_tick_from_millisecond(100);
    struct idmac_desc64 *desc_first, *desc_last, *desc;

    desc_first = desc_last = desc = sd->dma_buf;
    mem_addr = (rt_uint64_t)rt_kmem_v2p(sd->last_buf);

    for (rt_uint32_t length = sd->last_remain; length; ++desc)
    {
        rt_tick_t start = rt_tick_get();

        desc_len = rt_min_t(rt_uint32_t, length, DW_MCI_DESC_DATA_LENGTH);
        length -= desc_len;

        /*
         * Wait for the former clear OWN bit operation of IDMAC to make sure
         * that this descriptor isn't still owned by IDMAC as IDMAC's write ops
         * and CPU's read ops are asynchronous.
         */
        while ((HWREG32(&desc->des0) & IDMAC_DES0_OWN))
        {
            if ((rt_tick_get() - start) > timeout)
            {
                goto _err_own_bit;
            }

            rt_hw_cpu_relax();
        }

        /* Set the OWN bit and disable interrupts for this descriptor */
        desc->des0 = IDMAC_DES0_OWN | IDMAC_DES0_DIC | IDMAC_DES0_CH;

        /* Buffer length */
        IDMAC_64ADDR_SET_BUFFER1_SIZE(desc, desc_len);

        /* Physical address to DMA to/from */
        desc->des4 = mem_addr & 0xffffffff;
        desc->des5 = mem_addr >> 32;

        /* Update physical address for the next desc */
        mem_addr += desc_len;

        /* Save pointer to the last descriptor */
        desc_last = desc;
    }

    /* Set first descriptor */
    desc_first->des0 |= IDMAC_DES0_FD;

    /* Set last descriptor */
    desc_last->des0 &= ~(IDMAC_DES0_CH | IDMAC_DES0_DIC);
    desc_last->des0 |= IDMAC_DES0_LD;

    return RT_EOK;

_err_own_bit:
    /* restore the descriptor chain as it's polluted */
    LOG_D("Descriptor is still owned by IDMAC");

    rt_memset(sd->dma_buf, 0, DESC_RING_BUF_SZ);
    sdio_dw_idmac_init(sd);

    return -RT_EINVAL;
}

rt_inline rt_err_t sdio_dw_prepare_desc32(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    rt_uint32_t desc_len, mem_addr;
    int timeout = rt_tick_from_millisecond(100);
    struct idmac_desc32 *desc_first, *desc_last, *desc;

    desc_first = desc_last = desc = sd->dma_buf;
    mem_addr = (rt_ubase_t)rt_kmem_v2p(sd->last_buf);

    for (rt_uint32_t length = sd->last_remain; length; ++desc)
    {
        rt_tick_t start = rt_tick_get();

        desc_len = rt_min_t(rt_uint32_t, length, DW_MCI_DESC_DATA_LENGTH);
        length -= desc_len;

        /*
         * Wait for the former clear OWN bit operation of IDMAC to make sure
         * that this descriptor isn't still owned by IDMAC as IDMAC's write ops
         * and CPU's read ops are asynchronous.
         */
        while (!IDMAC_OWN_CLR64(HWREG32(&desc->des0)))
        {
            if ((rt_tick_get() - start) > timeout)
            {
                goto _err_own_bit;
            }

            rt_hw_cpu_relax();
        }

        /* Set the OWN bit and disable interrupts for this descriptor */
        desc->des0 = rt_cpu_to_le32(IDMAC_DES0_OWN | IDMAC_DES0_DIC | IDMAC_DES0_CH);

        /* Buffer length */
        IDMAC_32ADDR_SET_BUFFER1_SIZE(desc, desc_len);

        /* Physical address to DMA to/from */
        desc->des2 = rt_cpu_to_le32(mem_addr);

        /* Update physical address for the next desc */
        mem_addr += desc_len;

        /* Save pointer to the last descriptor */
        desc_last = desc;
    }

    /* Set first descriptor */
    desc_first->des0 |= rt_cpu_to_le32(IDMAC_DES0_FD);

    /* Set last descriptor */
    desc_last->des0 &= rt_cpu_to_le32(~(IDMAC_DES0_CH | IDMAC_DES0_DIC));
    desc_last->des0 |= rt_cpu_to_le32(IDMAC_DES0_LD);

    return RT_EOK;

_err_own_bit:
    /* restore the descriptor chain as it's polluted */
    LOG_D("Descriptor is still owned by IDMAC");

    rt_memset(sd->dma_buf, 0, DESC_RING_BUF_SZ);
    sdio_dw_idmac_init(sd);

    return -RT_EINVAL;
}

static rt_err_t sdio_dw_idmac_start(struct sdio_dw *sd)
{
    rt_err_t err = RT_EOK;

    if (sd->dma_64bit_address)
    {
        err = sdio_dw_prepare_desc64(sd, sd->data);
    }
    else
    {
        err = sdio_dw_prepare_desc32(sd, sd->data);
    }

    if (err)
    {
        goto _out;
    }

    /* Drain writebuffer */
    rt_hw_wmb();

    /* Make sure to reset DMA in case we did PIO before this */
    sdio_dw_ctrl_reset(sd, SDIO_DW_CTRL_DMA_RESET);
    sdio_dw_idmac_reset(sd);

    /* Select IDMAC interface */
    sdio_dw_writel(sd, CTRL, sdio_dw_readl(sd, CTRL) | SDIO_DW_CTRL_USE_IDMAC);

    /* Drain writebuffer */
    rt_hw_wmb();

    /* Enable the IDMAC */
    sdio_dw_writel(sd, BMOD, sdio_dw_readl(sd, BMOD) | SDIO_DW_IDMAC_ENABLE | SDIO_DW_IDMAC_FB);

    /* Start it running */
    sdio_dw_writel(sd, PLDMND, 1);

_out:
    return err;
}

static rt_err_t sdio_dw_idmac_complete(struct sdio_dw *sd)
{
    rt_err_t err = RT_EOK;
    struct rt_mmcsd_data *data = sd->data;

    sd->dma_ops->cleanup(sd);

    if (data)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
        rt_bitmap_set_bit(&sd->pending_events, EVENT_XFER_COMPLETE);
        rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);
    }

    return err;
}

static rt_err_t sdio_dw_idmac_stop(struct sdio_dw *sd)
{
    rt_uint32_t reg;

    /* Disable and reset the IDMAC interface */
    reg = sdio_dw_readl(sd, CTRL);
    reg &= ~SDIO_DW_CTRL_USE_IDMAC;
    reg |= SDIO_DW_CTRL_DMA_RESET;
    sdio_dw_writel(sd, CTRL, reg);

    /* Stop the IDMAC running */
    reg = sdio_dw_readl(sd, BMOD);
    reg &= ~(SDIO_DW_IDMAC_ENABLE | SDIO_DW_IDMAC_FB);
    reg |= SDIO_DW_IDMAC_SWRESET;
    sdio_dw_writel(sd, BMOD, reg);

    return RT_EOK;
}

static rt_err_t sdio_dw_idmac_cleanup(struct sdio_dw *sd)
{
    return RT_EOK;
}

static const struct sdio_dw_dma_ops sdio_dw_idmac_ops =
{
    .init = sdio_dw_idmac_init,
    .start = sdio_dw_idmac_start,
    .complete = sdio_dw_idmac_complete,
    .stop = sdio_dw_idmac_stop,
    .cleanup = sdio_dw_idmac_cleanup,
};

static void edma_callback(struct rt_dma_chan *chan, rt_size_t size)
{
    struct sdio_dw *sd = chan->priv;

    sd->dma_ops->complete(sd);
}

static rt_err_t sdio_dw_edmac_init(struct sdio_dw *sd)
{
    rt_err_t err = RT_EOK;

    sd->edma_chan = rt_dma_chan_request(sd->bus_dev, "rx-tx");

    if (rt_is_err(sd->edma_chan))
    {
        err = rt_ptr_err(sd->edma_chan);
        LOG_E("Get external DMA channel error = %s", rt_strerror(err));

        sd->edma_chan = RT_NULL;
    }
    else if (!sd->edma_chan)
    {
        err = -RT_ERROR;
    }
    else
    {
        sd->edma_chan->callback = edma_callback;
        sd->edma_chan->priv = sd;
    }

    return err;
}

static rt_err_t sdio_dw_edmac_start(struct sdio_dw *sd)
{
    rt_err_t err;
    struct rt_dma_slave_config config;
    struct rt_dma_slave_transfer transfer;

    rt_memset(&config, 0, sizeof(config));
    config.src_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;

    config.src_addr = (rt_ubase_t)rt_kmem_v2p(sd->last_buf);
    config.dst_addr = (rt_ubase_t)rt_kmem_v2p(sd->fifo_base);

    config.dst_maxburst = 1 << (((sdio_dw_readl(sd, FIFOTH) >> 28) & 0x7) + 1);
    config.dst_maxburst = config.dst_maxburst == 2 ? 1 : config.dst_maxburst;
    config.src_maxburst = config.dst_maxburst;

    if (sd->data->flags & DATA_DIR_READ)
    {
        config.direction = RT_DMA_DEV_TO_MEM;
    }
    else
    {
        config.direction = RT_DMA_MEM_TO_DEV;
    }

    if ((err = rt_dma_chan_config(sd->edma_chan, &config)))
    {
        LOG_E("Config EDMAC error = %s", rt_strerror(err));
        return err;
    }

    rt_memset(&transfer, 0, sizeof(transfer));
    transfer.src_addr = config.src_addr;
    transfer.dst_addr = config.dst_addr;
    transfer.buffer_len = sd->last_remain;

    if ((err = rt_dma_prep_single(sd->edma_chan, &transfer)))
    {
        LOG_E("Prepare EDMAC error = %s", rt_strerror(err));
        return err;
    }

    return rt_dma_chan_start(sd->edma_chan);
}

static rt_err_t sdio_dw_edmac_complete(struct sdio_dw *sd)
{
    rt_err_t err = RT_EOK;
    struct rt_mmcsd_data *data = sd->data;

    sd->dma_ops->cleanup(sd);

    if (data)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data->buf, data->blks * data->blksize);
        rt_bitmap_set_bit(&sd->pending_events, EVENT_XFER_COMPLETE);
        rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);
    }

    return err;
}

static rt_err_t sdio_dw_edmac_stop(struct sdio_dw *sd)
{
    return rt_dma_chan_stop(sd->edma_chan);
}

static rt_err_t sdio_dw_edmac_cleanup(struct sdio_dw *sd)
{
    return RT_EOK;
}

static rt_err_t sdio_dw_edmac_exit(struct sdio_dw *sd)
{
    if (sd->edma_chan)
    {
        rt_dma_chan_release(sd->edma_chan);
        sd->edma_chan = RT_NULL;
    }

    return RT_EOK;
}

static const struct sdio_dw_dma_ops sdio_dw_edmac_ops =
{
    .init = sdio_dw_edmac_init,
    .start = sdio_dw_edmac_start,
    .complete = sdio_dw_edmac_complete,
    .stop = sdio_dw_edmac_stop,
    .cleanup = sdio_dw_edmac_cleanup,
    .exit = sdio_dw_edmac_exit,
};

static rt_bool_t sdio_dw_get_cd(struct sdio_dw_slot *slot)
{
    rt_bool_t present;
    struct sdio_dw *sd = slot->sd;

    if (!controller_is_removable(slot->host))
    {
        present = RT_TRUE;
    }
    else
    {
        present = (sdio_dw_readl(sd, CDETECT) & (1 << slot->id)) == 0;
    }

    return present;
}

static void sdio_dw_adjust_fifoth(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    static const rt_uint32_t mszs[] = { 1, 4, 8, 16, 32, 64, 128, 256 };
    rt_uint32_t blksz = data->blksize;
    rt_uint32_t fifo_width = 1 << sd->data_shift;
    rt_uint32_t blksz_depth = blksz / fifo_width, fifoth_val;
    rt_uint32_t msize = 0, rx_wmark = 1, tx_wmark, tx_wmark_invers;
    int idx = RT_ARRAY_SIZE(mszs) - 1;

    /* PIO should ship this scenario */
    if (!sd->use_dma)
    {
        return;
    }

    tx_wmark = (sd->fifo_depth) / 2;
    tx_wmark_invers = sd->fifo_depth - tx_wmark;

    /* MSIZE is '1', if blksz is not a multiple of the FIFO width */
    if (blksz % fifo_width)
    {
        goto _done;
    }

    do {
        if (!((blksz_depth % mszs[idx]) || (tx_wmark_invers % mszs[idx])))
        {
            msize = idx;
            rx_wmark = mszs[idx] - 1;

            break;
        }
    } while (--idx > 0);
    /* If idx is '0', it won't be tried Thus, initial values are uesed */

_done:
    fifoth_val = SDIO_DW_SET_FIFOTH(msize, rx_wmark, tx_wmark);
    sdio_dw_writel(sd, FIFOTH, fifoth_val);
}

static void sdio_dw_ctrl_thld(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    rt_uint8_t enable;
    rt_uint16_t thld_size;
    rt_uint32_t blksz_depth, fifo_depth;
    rt_uint32_t blksz = data->blksize;

    /*
     * CDTHRCTL doesn't exist prior to 240A (in fact that register offset is
     * in the FIFO region, so we really shouldn't access it).
     */
    if (sd->verid < SDIO_DW_240A ||
        (sd->verid < SDIO_DW_280A && (data->flags & DATA_DIR_WRITE)))
    {
        return;
    }

    /*
     * Card write Threshold is introduced since 2.80a
     * It's used when HS400 mode is enabled.
     */
    if ((data->flags & DATA_DIR_WRITE) && sd->timing != MMCSD_TIMING_MMC_HS400)
    {
        goto _disable;
    }

    if ((data->flags & DATA_DIR_WRITE))
    {
        enable = SDIO_DW_CARD_WR_THR_EN;
    }
    else
    {
        enable = SDIO_DW_CARD_RD_THR_EN;
    }

    if (sd->timing != MMCSD_TIMING_MMC_HS200 &&
        sd->timing != MMCSD_TIMING_UHS_SDR104 &&
        sd->timing != MMCSD_TIMING_MMC_HS400)
    {
        goto _disable;
    }

    blksz_depth = blksz / (1 << sd->data_shift);
    fifo_depth = sd->fifo_depth;

    if (blksz_depth > fifo_depth)
    {
        goto _disable;
    }

    /*
     * If (blksz_depth) >= (fifo_depth >> 1), should be 'thld_size <= blksz'
     * If (blksz_depth) <  (fifo_depth >> 1), should be thld_size = blksz
     * Currently just choose blksz.
     */
    thld_size = blksz;
    sdio_dw_writel(sd, CDTHRCTL, SDIO_DW_SET_THLD(thld_size, enable));

    return;

_disable:
    sdio_dw_writel(sd, CDTHRCTL, 0);
}

static rt_err_t sdio_dw_submit_data_dma(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    rt_uint32_t temp;
    rt_ubase_t level;

    sd->using_dma = RT_FALSE;

    /* If we don't have a channel, we can't do DMA */
    if (!sd->use_dma)
    {
        return -RT_ENOSYS;
    }

    sd->using_dma = RT_TRUE;

    /*
     * Decide the MSIZE and RX/TX Watermark. If current block size is same with
     * previous size, no need to update fifoth.
     */
    if (sd->prev_blksz != data->blksize)
    {
        sdio_dw_adjust_fifoth(sd, data);
    }

    /* Enable the DMA interface */
    temp = sdio_dw_readl(sd, CTRL);
    temp |= SDIO_DW_CTRL_DMA_ENABLE;
    sdio_dw_writel(sd, CTRL, temp);

    /* Disable RX/TX IRQs, let DMA handle it */
    level = rt_spin_lock_irqsave(&sd->irq_lock);
    temp = sdio_dw_readl(sd, INTMASK);
    temp &= ~(PINT(RXDR) | PINT(TXDR));
    sdio_dw_writel(sd, INTMASK, temp);
    rt_spin_unlock_irqrestore(&sd->irq_lock, level);

    /* Flush data to memory */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, sd->last_buf, sd->last_remain);

    if (sd->dma_ops->start(sd))
    {
        /* We can't do DMA, try PIO for this one */
        sd->dma_ops->stop(sd);

        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static void sdio_dw_submit_data(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    rt_ubase_t level;
    rt_uint32_t temp;

    data->err = -RT_ERROR;
    sd->data = data;
    sd->last_buf = data->buf;
    sd->last_remain = data->blks * data->blksize;

    if ((data->flags & DATA_DIR_READ))
    {
        sd->dir_status = SDIO_DW_RECV_STATUS;
    }
    else
    {
        sd->dir_status = SDIO_DW_SEND_STATUS;
    }

    sdio_dw_ctrl_thld(sd, data);

    if (sdio_dw_submit_data_dma(sd, data))
    {
        sd->part_buf_start = 0;
        sd->part_buf_count = 0;

        sdio_dw_writel(sd, RINTSTS, PINT(TXDR) | PINT(RXDR));

        level = rt_spin_lock_irqsave(&sd->irq_lock);
        temp = sdio_dw_readl(sd, INTMASK);
        temp |= PINT(TXDR) | PINT(RXDR);
        sdio_dw_writel(sd, INTMASK, temp);
        rt_spin_unlock_irqrestore(&sd->irq_lock, level);

        temp = sdio_dw_readl(sd, CTRL);
        temp &= ~SDIO_DW_CTRL_DMA_ENABLE;
        sdio_dw_writel(sd, CTRL, temp);

        /*
         * Use the initial fifoth_val for PIO mode. If wm_algined is set, we set
         * watermark same as data size. If next issued data may be transfered by
         * DMA mode, prev_blksz should be invalidated.
         */
        if (sd->wm_aligned)
        {
            sdio_dw_adjust_fifoth(sd, data);
        }
        else
        {
            sdio_dw_writel(sd, FIFOTH, sd->fifoth_val);
        }
        sd->prev_blksz = 0;
    }
    else
    {
        /*
         * Keep the current block size.
         * It will be used to decide whether to update fifoth register next time.
         */
        sd->prev_blksz = data->blksize;
    }
}

static void sdio_dw_setup_bus(struct sdio_dw_slot *slot, rt_bool_t force_clkinit)
{
    struct sdio_dw *sd = slot->sd;
    rt_uint32_t clock = slot->clock;
    rt_uint32_t cmd_bits = SDIO_DW_CMD_UPD_CLK | SDIO_DW_CMD_PRV_DAT_WAIT;

    /* We must continue to set bit 28 in CMD until the change is complete */
    if (sd->state == STATE_WAITING_CMD11_DONE)
    {
        cmd_bits |= SDIO_DW_CMD_VOLT_SWITCH;
    }

    if (!clock)
    {
        sdio_dw_writel(sd, CLKENA, 0);
        sdio_dw_send_cmd(slot, cmd_bits, 0);
    }
    else if (clock != sd->current_speed || force_clkinit)
    {
        rt_uint32_t clk_en_a, div = sd->bus_hz / clock;

        if (sd->bus_hz % clock && sd->bus_hz > clock)
        {
            /* Move the + 1 after the divide to prevent over-clocking the card */
            div += 1;
        }

        div = (sd->bus_hz != clock) ? RT_DIV_ROUND_UP(div, 2) : 0;

        if (clock != slot->clk_old &&
            !rt_bitmap_test_bit(&slot->flags, DW_MMC_CARD_NEEDS_POLL) &&
            !force_clkinit)
        {
            LOG_D("Bus speed (slot %d) = %uHz (slot req %uHz, actual %uHZ div = %d)",
                    slot->id, sd->bus_hz, clock,
                    div ? ((sd->bus_hz / div) >> 1) : sd->bus_hz, div);
        }

        /* Disable clock */
        sdio_dw_writel(sd, CLKENA, 0);
        sdio_dw_writel(sd, CLKSRC, 0);

        /* Inform CIU */
        sdio_dw_send_cmd(slot, cmd_bits, 0);

        /* Set clock to desired speed */
        sdio_dw_writel(sd, CLKDIV, div);

        /* Inform CIU */
        sdio_dw_send_cmd(slot, cmd_bits, 0);

        /* Enable clock; only low power if no SDIO */
        clk_en_a = SDIO_DW_CLKEN_ENABLE << slot->id;
        if (!rt_bitmap_test_bit(&slot->flags, DW_MMC_CARD_NO_LOW_PWR))
        {
            clk_en_a |= SDIO_DW_CLKEN_LOW_PWR << slot->id;
        }
        sdio_dw_writel(sd, CLKENA, clk_en_a);

        /* Inform CIU */
        sdio_dw_send_cmd(slot, cmd_bits, 0);

        /* Keep the last clock value that was requested from core */
        slot->clk_old = clock;
    }

    sd->current_speed = clock;

    /* Set the current slot bus width */
    sdio_dw_writel(sd, CTYPE, (slot->ctype << slot->id));
}

static void sdio_dw_set_data_timeout(struct sdio_dw *sd, rt_uint32_t timeout_ns)
{
    rt_uint64_t tmp;
    rt_uint32_t clk_div, tmout;
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    if (drv_data && drv_data->set_data_timeout)
    {
        drv_data->set_data_timeout(sd, timeout_ns);

        return;
    }

    clk_div = (sdio_dw_readl(sd, CLKDIV) & 0xff) * 2;

    if (clk_div == 0)
    {
        clk_div = 1;
    }

    tmp = RT_DIV_ROUND_UP_ULL((rt_uint64_t)timeout_ns * sd->bus_hz, NSEC_PER_SEC);
    tmp = RT_DIV_ROUND_UP_ULL(tmp, clk_div);

    /* TMOUT[7:0] (RESPONSE_TIMEOUT): Set maximum */
    tmout = 0xff;

    /* TMOUT[31:8] (DATA_TIMEOUT) */
    if (!tmp || tmp > 0xffffff)
    {
        tmout |= (0xffffff << 8);
    }
    else
    {
        tmout |= (tmp & 0xffffff) << 8;
    }

    sdio_dw_writel(sd, TMOUT, tmout);
}

/* Push final bytes to part_buf, only use during push */
static void sdio_dw_set_part_bytes(struct sdio_dw *sd, void *buf, int cnt)
{
    rt_memcpy((void *)&sd->part_buf, buf, cnt);
    sd->part_buf_count = cnt;
}

/* Append bytes to part_buf, only use during push */
static int sdio_dw_push_part_bytes(struct sdio_dw *sd, void *buf, int cnt)
{
    cnt = rt_min(cnt, (1 << sd->data_shift) - sd->part_buf_count);
    rt_memcpy((void *)&sd->part_buf + sd->part_buf_count, buf, cnt);
    sd->part_buf_count += cnt;

    return cnt;
}

/* Pull first bytes from part_buf, only use during pull */
static int sdio_dw_pull_part_bytes(struct sdio_dw *sd, void *buf, int cnt)
{
    cnt = rt_min_t(int, cnt, sd->part_buf_count);

    if (cnt)
    {
        rt_memcpy(buf, (void *)&sd->part_buf + sd->part_buf_start, cnt);
        sd->part_buf_count -= cnt;
        sd->part_buf_start += cnt;
    }

    return cnt;
}

/* Pull final bytes from the part_buf, assuming it's just been filled */
static void sdio_dw_pull_final_bytes(struct sdio_dw *sd, void *buf, int cnt)
{
    rt_memcpy(buf, &sd->part_buf, cnt);
    sd->part_buf_start = cnt;
    sd->part_buf_count = (1 << sd->data_shift) - cnt;
}

static void sdio_dw_push_data16(struct sdio_dw *sd, void *buf, int cnt)
{
    struct rt_mmcsd_data *data = sd->data;
    int init_cnt = cnt;

    /* Try and push anything in the part_buf */
    if ((sd->part_buf_count))
    {
        int len = sdio_dw_push_part_bytes(sd, buf, cnt);

        buf += len;
        cnt -= len;

        if (sd->part_buf_count == 2)
        {
            sdio_dw_fifo_writew(sd, sd->part_buf16);
            sd->part_buf_count = 0;
        }
    }
#ifndef ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
    if (((rt_ubase_t)buf & 0x1))
    {
        while (cnt >= 2)
        {
            rt_uint16_t aligned_buf[64];
            int len = rt_min(cnt & -2, (int)sizeof(aligned_buf));
            int items = len >> 1;

            /* rt_memcpy from input buffer into aligned buffer */
            rt_memcpy(aligned_buf, buf, len);
            buf += len;
            cnt -= len;

            /* Push data from aligned buffer into fifo */
            for (int i = 0; i < items; ++i)
            {
                sdio_dw_fifo_writew(sd, aligned_buf[i]);
            }
        }
    }
    else
#endif /* !ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS */
    {
        rt_uint16_t *pdata = buf;

        for (; cnt >= 2; cnt -= 2)
        {
            sdio_dw_fifo_writew(sd, *pdata++);
        }
        buf = pdata;
    }
    /* Put anything remaining in the part_buf */
    if (cnt)
    {
        sdio_dw_set_part_bytes(sd, buf, cnt);

        /* Push data if we have reached the expected data length */
        if ((data->bytes_xfered + init_cnt) == (data->blksize * data->blks))
        {
            sdio_dw_fifo_writew(sd, sd->part_buf16);
        }
    }
}

static void sdio_dw_pull_data16(struct sdio_dw *sd, void *buf, int cnt)
{
#ifndef ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
    if (((rt_ubase_t)buf & 0x1))
    {
        while (cnt >= 2)
        {
            /* Pull data from fifo into aligned buffer */
            rt_uint16_t aligned_buf[64];
            int len = rt_min(cnt & -2, (int)sizeof(aligned_buf));
            int items = len >> 1;

            for (int i = 0; i < items; ++i)
            {
                aligned_buf[i] = sdio_dw_fifo_readw(sd);
            }

            /* rt_memcpy from aligned buffer into output buffer */
            rt_memcpy(buf, aligned_buf, len);
            buf += len;
            cnt -= len;
        }
    }
    else
#endif /* !ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS */
    {
        rt_uint16_t *pdata = buf;

        for (; cnt >= 2; cnt -= 2)
        {
            *pdata++ = sdio_dw_fifo_readw(sd);
        }
        buf = pdata;
    }
    if (cnt)
    {
        sd->part_buf16 = sdio_dw_fifo_readw(sd);
        sdio_dw_pull_final_bytes(sd, buf, cnt);
    }
}

static void sdio_dw_push_data32(struct sdio_dw *sd, void *buf, int cnt)
{
    struct rt_mmcsd_data *data = sd->data;
    int init_cnt = cnt;

    /* Try and push anything in the part_buf */
    if ((sd->part_buf_count))
    {
        int len = sdio_dw_push_part_bytes(sd, buf, cnt);

        buf += len;
        cnt -= len;

        if (sd->part_buf_count == 4)
        {
            sdio_dw_fifo_writel(sd, sd->part_buf32);
            sd->part_buf_count = 0;
        }
    }
#ifndef ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
    if (((rt_ubase_t)buf & 0x3))
    {
        while (cnt >= 4)
        {
            rt_uint32_t aligned_buf[32];
            int len = rt_min(cnt & -4, (int)sizeof(aligned_buf));
            int items = len >> 2;

            /* rt_memcpy from input buffer into aligned buffer */
            rt_memcpy(aligned_buf, buf, len);
            buf += len;
            cnt -= len;

            /* Push data from aligned buffer into fifo */
            for (int i = 0; i < items; ++i)
            {
                sdio_dw_fifo_writel(sd, aligned_buf[i]);
            }
        }
    }
    else
#endif /* !ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS */
    {
        rt_uint32_t *pdata = buf;

        for (; cnt >= 4; cnt -= 4)
        {
            sdio_dw_fifo_writel(sd, *pdata++);
        }
        buf = pdata;
    }
    /* Put anything remaining in the part_buf */
    if (cnt)
    {
        sdio_dw_set_part_bytes(sd, buf, cnt);

        /* Push data if we have reached the expected data length */
        if ((data->bytes_xfered + init_cnt) == (data->blksize * data->blks))
        {
            sdio_dw_fifo_writel(sd, sd->part_buf32);
        }
    }
}

static void sdio_dw_pull_data32(struct sdio_dw *sd, void *buf, int cnt)
{
#ifndef ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
    if (((rt_ubase_t)buf & 0x3))
    {
        while (cnt >= 4)
        {
            /* Pull data from fifo into aligned buffer */
            rt_uint32_t aligned_buf[32];
            int len = rt_min(cnt & -4, (int)sizeof(aligned_buf));
            int items = len >> 2;

            for (int i = 0; i < items; ++i)
            {
                aligned_buf[i] = sdio_dw_fifo_readl(sd);
            }

            /* rt_memcpy from aligned buffer into output buffer */
            rt_memcpy(buf, aligned_buf, len);
            buf += len;
            cnt -= len;
        }
    }
    else
#endif /* !ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS */
    {
        rt_uint32_t *pdata = buf;

        for (; cnt >= 4; cnt -= 4)
        {
            *pdata++ = sdio_dw_fifo_readl(sd);
        }
        buf = pdata;
    }
    if (cnt)
    {
        sd->part_buf32 = sdio_dw_fifo_readl(sd);
        sdio_dw_pull_final_bytes(sd, buf, cnt);
    }
}

static void sdio_dw_push_data64(struct sdio_dw *sd, void *buf, int cnt)
{
    struct rt_mmcsd_data *data = sd->data;
    int init_cnt = cnt;

    /* Try and push anything in the part_buf */
    if ((sd->part_buf_count))
    {
        int len = sdio_dw_push_part_bytes(sd, buf, cnt);

        buf += len;
        cnt -= len;

        if (sd->part_buf_count == 8)
        {
            sdio_dw_fifo_writeq(sd, sd->part_buf64);
            sd->part_buf_count = 0;
        }
    }
#ifndef ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
    if (((rt_ubase_t)buf & 0x7))
    {
        while (cnt >= 8)
        {
            rt_uint64_t aligned_buf[16];
            int len = rt_min(cnt & -8, (int)sizeof(aligned_buf));
            int items = len >> 3;

            /* rt_memcpy from input buffer into aligned buffer */
            rt_memcpy(aligned_buf, buf, len);
            buf += len;
            cnt -= len;

            /* Push data from aligned buffer into fifo */
            for (int i = 0; i < items; ++i)
            {
                sdio_dw_fifo_writeq(sd, aligned_buf[i]);
            }
        }
    }
    else
#endif /* !ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS */
    {
        rt_uint64_t *pdata = buf;

        for (; cnt >= 8; cnt -= 8)
        {
            sdio_dw_fifo_writeq(sd, *pdata++);
        }
        buf = pdata;
    }
    /* Put anything remaining in the part_buf */
    if (cnt)
    {
        sdio_dw_set_part_bytes(sd, buf, cnt);

        /* Push data if we have reached the expected data length */
        if ((data->bytes_xfered + init_cnt) == (data->blksize * data->blks))
        {
            sdio_dw_fifo_writeq(sd, sd->part_buf64);
        }
    }
}

static void sdio_dw_pull_data64(struct sdio_dw *sd, void *buf, int cnt)
{
#ifndef ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
    if (((rt_ubase_t)buf & 0x7))
    {
        while (cnt >= 8)
        {
            /* Pull data from fifo into aligned buffer */
            rt_uint64_t aligned_buf[16];
            int len = rt_min(cnt & -8, (int)sizeof(aligned_buf));
            int items = len >> 3;

            for (int i = 0; i < items; ++i)
            {
                aligned_buf[i] = sdio_dw_fifo_readq(sd);
            }

            /* rt_memcpy from aligned buffer into output buffer */
            rt_memcpy(buf, aligned_buf, len);
            buf += len;
            cnt -= len;
        }
    }
    else
#endif /* !ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS */
    {
        rt_uint64_t *pdata = buf;

        for (; cnt >= 8; cnt -= 8)
        {
            *pdata++ = sdio_dw_fifo_readq(sd);
        }
        buf = pdata;
    }
    if (cnt)
    {
        sd->part_buf64 = sdio_dw_fifo_readq(sd);
        sdio_dw_pull_final_bytes(sd, buf, cnt);
    }
}

static void sdio_dw_pull_data(struct sdio_dw *sd, void *buf, int cnt)
{
    /* Get remaining partial bytes */
    int len = sdio_dw_pull_part_bytes(sd, buf, cnt);

    if (len != cnt)
    {
        buf += len;
        cnt -= len;

        /* Get the rest of the data */
        sd->pull_data(sd, buf, cnt);
    }
}

static void sdio_dw_read_data_pio(struct sdio_dw *sd, rt_bool_t dto)
{
    void *buf;
    int shift = sd->data_shift;
    struct rt_mmcsd_data *data = sd->data;
    rt_uint32_t status, remain, fcnt, len;

    buf = sd->last_buf;
    remain = sd->last_remain;

    do {
        if (!remain)
        {
            break;
        }

        do {
            fcnt = (SDIO_DW_GET_FCNT(sdio_dw_readl(sd, STATUS)) << shift) + sd->part_buf_count;
            len = rt_min(remain, fcnt);

            if (!len)
            {
                break;
            }

            sdio_dw_pull_data(sd, buf, len);
            data->bytes_xfered += len;
            buf += len;
            remain -= len;
        } while (remain);

        status = sdio_dw_readl(sd, MINTSTS);
        sdio_dw_writel(sd, RINTSTS, PINT(RXDR));
    /* If the RXDR is ready read again */
    } while ((status & PINT(RXDR)) || (dto && SDIO_DW_GET_FCNT(sdio_dw_readl(sd, STATUS))));

    sd->last_buf = remain ? buf : RT_NULL;
    sd->last_remain = remain;

    rt_hw_wmb();
    rt_bitmap_set_bit(&sd->pending_events, EVENT_XFER_COMPLETE);
}

static void sdio_dw_write_data_pio(struct sdio_dw *sd)
{
    void *buf;
    int shift = sd->data_shift;
    struct rt_mmcsd_data *data = sd->data;
    rt_uint32_t status, remain, fcnt, len, fifo_depth;

    buf = sd->last_buf;
    remain = sd->last_remain;
    fifo_depth = sd->fifo_depth;

    do {
        if (!remain)
        {
            break;
        }

        do {
            fcnt = ((fifo_depth - SDIO_DW_GET_FCNT(sdio_dw_readl(sd, STATUS))) << shift) - sd->part_buf_count;
            len = rt_min(remain, fcnt);

            if (!len)
            {
                break;
            }

            sd->push_data(sd, buf, len);
            data->bytes_xfered += len;
            buf += len;
            remain -= len;
        } while (remain);

        status = sdio_dw_readl(sd, MINTSTS);
        sdio_dw_writel(sd, RINTSTS, PINT(TXDR));
    /* If TXDR write again */
    } while ((status & PINT(TXDR)));

    sd->last_buf = remain ? buf : RT_NULL;
    sd->last_remain = remain;

    rt_hw_wmb();
    rt_bitmap_set_bit(&sd->pending_events, EVENT_XFER_COMPLETE);
}

static void sdio_dw_init_dma(struct sdio_dw *sd)
{
    int addr_config;

    /*
    * Check tansfer mode from HCON[17:16]
    * Clear the ambiguous description of dw_mmc databook:
    *   2b'00: No DMA Interface -> Actually means using Internal DMA block
    *   2b'01: DesignWare DMA Interface -> Synopsys DW-DMA block
    *   2b'10: Generic DMA Interface -> non-Synopsys generic DMA block
    *   2b'11: Non DW DMA Interface -> pio only
    * Compared to DesignWare DMA Interface, Generic DMA Interface has a simpler
    * request/acknowledge handshake mechanism and both of them are regarded as
    * external dma master for dw_mmc.
    */
    sd->use_dma = SDIO_DW_GET_TRANS_MODE(sdio_dw_readl(sd, HCON));

    if (sd->use_dma == DMA_INTERFACE_IDMA)
    {
        sd->use_dma = TRANS_MODE_IDMAC;
    }
    else if (sd->use_dma == DMA_INTERFACE_DWDMA || sd->use_dma == DMA_INTERFACE_GDMA)
    {
        sd->use_dma = TRANS_MODE_EDMAC;
    }
    else
    {
        goto _no_dma;
    }

    /* Determine which DMA interface to use */
    if (sd->use_dma == TRANS_MODE_IDMAC)
    {
        /* Check ADDR_CONFIG bit in HCON to find IDMAC address bus width */
        addr_config = SDIO_DW_GET_ADDR_CONFIG(sdio_dw_readl(sd, HCON));

        /* Supports IDMAC in 64/32-bit address mode */
        sd->dma_64bit_address = (addr_config == 1);
        LOG_D("IDMAC supports %s-bit address mode", sd->dma_64bit_address ? "64" : "32");

        /* Alloc memory for translation */
        sd->dma_buf = rt_dma_alloc_coherent(sd->bus_dev, DESC_RING_BUF_SZ, &sd->dma_buf_phy);

        if (!sd->dma_buf)
        {
            LOG_E("Could not alloc DMA memory witch cache");

            goto _no_dma;
        }

        sd->dma_ops = &sdio_dw_idmac_ops;
        LOG_D("Using internal DMA controller");
    }
    else
    {
        if (!rt_dm_dev_prop_read_bool(&sd->parent, "dma-names") ||
            !rt_dm_dev_prop_read_bool(&sd->parent, "dmas"))
        {
            goto _no_dma;
        }

        sd->dma_ops = &sdio_dw_edmac_ops;
        LOG_D("Using external DMA controller");
    }

    if (sd->dma_ops->init && sd->dma_ops->start && sd->dma_ops->stop && sd->dma_ops->cleanup)
    {
        if (sd->dma_ops->init(sd))
        {
            LOG_E("Unable to initialize DMA Controller");
            goto _no_dma;
        }
    }
    else
    {
        LOG_E("DMA initialization not found");
        goto _no_dma;
    }

    return;

_no_dma:
    LOG_D("Using PIO mode");
    sd->use_dma = TRANS_MODE_PIO;
}

static rt_bool_t sdio_dw_reset(struct sdio_dw *sd)
{
    rt_err_t res = RT_FALSE;
    rt_uint32_t flags = SDIO_DW_CTRL_RESET | SDIO_DW_CTRL_FIFO_RESET;

    if (sd->use_dma)
    {
        flags |= SDIO_DW_CTRL_DMA_RESET;
    }

    if (sdio_dw_ctrl_reset(sd, flags))
    {
        int timeout = 500 * USEC_PER_MSEC;
        /* In all cases we clear the RAWINTS register to clear any interrupts */
        sdio_dw_writel(sd, RINTSTS, 0xffffffff);

        if (!sd->use_dma)
        {
            res = RT_TRUE;
            goto _ciu_out;
        }

        /* Wait for dma_req to be cleared */
        while ((sdio_dw_readl(sd, STATUS) & SDIO_DW_STATUS_DMA_REQ) && timeout--)
        {
            rt_hw_cpu_relax();
        }

        if (time <= 0)
        {
            LOG_E("Timeout waiting for dma_req to be cleared in reset");
            goto _ciu_out;
        }

        /* when using DMA next we reset the fifo again */
        if (!sdio_dw_ctrl_reset(sd, SDIO_DW_CTRL_FIFO_RESET))
        {
            goto _ciu_out;
        }
    }
    else
    {
        /* If the controller reset bit did clear, then set clock regs */
        if (!(sdio_dw_readl(sd, CTRL) & SDIO_DW_CTRL_RESET))
        {
            LOG_E("FIFO/DMA reset bits didn't clear but ciu was reset, doing clock update");

            goto _ciu_out;
        }
    }

    if (sd->use_dma == TRANS_MODE_IDMAC)
    {
        /* It is also required that we reinit idmac */
        sdio_dw_idmac_init(sd);
    }

    res = RT_TRUE;

_ciu_out:
    /* After a CTRL reset we need to have CIU set clock registers  */
    sdio_dw_send_cmd(sd->slot, SDIO_DW_CMD_UPD_CLK, 0);

    return res;
}

static void sdio_dw_start_request(struct sdio_dw *sd, struct rt_mmcsd_cmd *cmd)
{
    rt_uint32_t cmd_flags;
    struct sdio_dw_slot *slot = sd->slot;
    struct rt_mmcsd_data *data = cmd->data;

    if (sd->state == STATE_WAITING_CMD11_DONE)
    {
        sd->state = STATE_IDLE;
    }

    if (sd->state == STATE_IDLE)
    {
        sd->state = STATE_SENDING_CMD;
    }

    sd->req = sd->slot->req;
    sd->cmd = cmd;

    sd->pending_events = 0;
    sd->cmd_status = 0;
    sd->data_status = 0;
    sd->dir_status = 0;

    if (data)
    {
        sdio_dw_set_data_timeout(sd, data->timeout_ns);
        sdio_dw_writel(sd, BYTCNT, data->blksize * data->blks);
        sdio_dw_writel(sd, BLKSIZ, data->blksize);
    }

    cmd_flags = cmd->cmd_code;

    if (cmd->cmd_code == STOP_TRANSMISSION ||
        cmd->cmd_code == GO_IDLE_STATE ||
        cmd->cmd_code == GO_INACTIVE_STATE ||
        (cmd->cmd_code == SD_IO_RW_DIRECT && ((cmd->arg >> 9) & 0x1ffff) == SDIO_REG_CCCR_IO_ABORT))
    {
        cmd_flags |= SDIO_DW_CMD_STOP;
    }
    else if (cmd->cmd_code != SEND_STATUS && data)
    {
        cmd_flags |= SDIO_DW_CMD_PRV_DAT_WAIT;
    }

    if (cmd->cmd_code == VOLTAGE_SWITCH)
    {
        rt_uint32_t clk_en_a;

        /* Special bit makes CMD11 not die */
        cmd_flags |= SDIO_DW_CMD_VOLT_SWITCH;

        /* Change state to continue to handle CMD11 weirdness */
        sd->state = STATE_SENDING_CMD11;

        /*
         * We need to disable low power mode (automatic clock stop) while
         * doing voltage switch so we don't confuse the card, since stopping
         * the clock is a specific part of the UHS voltage change dance.
         *
         * Note that low power mode (SDIO_DW_CLKEN_LOW_PWR) will be
         * unconditionally turned back on in dw_mci_setup_bus() if it's ever
         * called with a non-zero clock.  That shouldn't happen until the
         * voltage change is all done.
         */
        clk_en_a = sdio_dw_readl(sd, CLKENA);
        clk_en_a &= ~(SDIO_DW_CLKEN_LOW_PWR << slot->id);
        sdio_dw_writel(sd, CLKENA, clk_en_a);
        sdio_dw_send_cmd(sd->slot, SDIO_DW_CMD_UPD_CLK | SDIO_DW_CMD_PRV_DAT_WAIT, 0);
    }

    switch (resp_type(cmd))
    {
    case RESP_NONE:
        break;

    case RESP_R1:
    case RESP_R5:
    case RESP_R6:
    case RESP_R7:
    case RESP_R1B:
        cmd_flags |= SDIO_DW_CMD_RESP_EXP;
        cmd_flags |= SDIO_DW_CMD_RESP_CRC;
        break;

    case RESP_R2:
        cmd_flags |= SDIO_DW_CMD_RESP_EXP;
        cmd_flags |= SDIO_DW_CMD_RESP_CRC;
        cmd_flags |= SDIO_DW_CMD_RESP_LONG;
        break;

    case RESP_R3:
    case RESP_R4:
        cmd_flags |= SDIO_DW_CMD_RESP_EXP;
        break;

    default:
        LOG_D("Unsupported cmd type = %x", resp_type(cmd));
        break;
    }

    if (data)
    {
        cmd_flags |= SDIO_DW_CMD_DAT_EXP;

        if ((data->flags & DATA_DIR_WRITE))
        {
            cmd_flags |= SDIO_DW_CMD_DAT_WR;
        }
    }

    if (!rt_bitmap_test_bit(&slot->flags, DW_MMC_CARD_NO_USE_HOLD))
    {
        cmd_flags |= SDIO_DW_CMD_USE_HOLD_REG;
    }

    if (rt_bitmap_test_bit(&slot->flags, DW_MMC_CARD_NEED_INIT))
    {
        cmd_flags |= SDIO_DW_CMD_INIT;
        rt_bitmap_clear_bit(&slot->flags, DW_MMC_CARD_NEED_INIT);
    }

    if (data)
    {
        sdio_dw_submit_data(sd, data);
        /* Drain writebuffer */
        rt_hw_wmb();
    }

    sdio_dw_start_cmd(slot, cmd_flags, cmd->arg);

    if (cmd->cmd_code == VOLTAGE_SWITCH)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&sd->irq_lock);

        if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_CMD_COMPLETE))
        {
            rt_tick_t tick = rt_tick_from_millisecond(500) + 1;

            rt_timer_control(&sd->cmd11_timer, RT_TIMER_CTRL_SET_TIME, &tick);

            rt_timer_start(&sd->cmd11_timer);
        }

        rt_spin_unlock_irqrestore(&sd->irq_lock, level);
    }

    sd->stop_cmdr = sdio_dw_prep_stop_abort(sd, cmd);
}

static void sdio_dw_end_request(struct sdio_dw *sd)
{
    sd->slot->req = RT_NULL;
    sd->req = RT_NULL;

    if (sd->state == STATE_SENDING_CMD11)
    {
        sd->state = STATE_WAITING_CMD11_DONE;
    }
    else
    {
        sd->state = STATE_IDLE;
    }

    rt_hw_spin_unlock(&sd->lock.lock);

    mmcsd_req_complete(sd->slot->host);

    rt_hw_spin_lock(&sd->lock.lock);
}

static rt_err_t sdio_dw_cmd_complete(struct sdio_dw *sd, struct rt_mmcsd_cmd *cmd)
{
    rt_uint32_t status = sd->cmd_status;

    sd->cmd_status = 0;

    /* Read the response from the card (up to 16 bytes) */
    if (resp_type(cmd) == RESP_R2)
    {
        cmd->resp[0] = sdio_dw_readl(sd, RESP3);
        cmd->resp[1] = sdio_dw_readl(sd, RESP2);
        cmd->resp[2] = sdio_dw_readl(sd, RESP1);
        cmd->resp[3] = sdio_dw_readl(sd, RESP0);
    }
    else
    {
        cmd->resp[0] = sdio_dw_readl(sd, RESP0);
    }

    if ((status & PINT(RTO)))
    {
        cmd->err = -RT_ETIMEOUT;
    }
    else if ((resp_type(cmd) & (RESP_R1 | RESP_R5 | RESP_R6 | RESP_R7 | RESP_R1B)) &&
        (status & PINT(RCRC)))
    {
        cmd->err = -RT_EIO;
    }
    else if ((status & PINT(RESP_ERR)))
    {
        cmd->err = -RT_EIO;
    }
    else
    {
        cmd->err = RT_EOK;
    }

    return cmd->err;
}

static int sdio_dw_data_complete(struct sdio_dw *sd, struct rt_mmcsd_data *data)
{
    rt_uint32_t status = sd->data_status;

    if (status & SDIO_DW_DATA_ERROR_FLAGS)
    {
        if (status & PINT(DRTO))
        {
            data->err = -RT_ETIMEOUT;
        }
        else if (status & PINT(DCRC))
        {
            data->err = -RT_EIO;
        }
        else if (status & PINT(EBE))
        {
            if (sd->dir_status == SDIO_DW_SEND_STATUS)
            {
                /*
                 * No data CRC status was returned. The number of bytes
                 * transferred will be exaggerated in PIO mode.
                 */
                data->bytes_xfered = 0;
                data->err = -RT_ETIMEOUT;
            }
            else if (sd->dir_status == SDIO_DW_RECV_STATUS)
            {
                data->err = -RT_EIO;
            }
        }
        else
        {
            /* PINT(SBE) is included */
            data->err = -RT_EIO;
        }

        LOG_D("Data error, status 0x%x", status);

        /* After an error, there may be data lingering in the FIFO */
        sdio_dw_reset(sd);
    }
    else
    {
        data->bytes_xfered = data->blks * data->blksize;
        data->err = RT_EOK;
    }

    return data->err;
}

static void sdio_dw_mmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct sdio_dw_slot *slot = host->private_data;
    struct sdio_dw *sd = slot->sd;

    /*
     * The check for card presence and queueing of the request must be atomic,
     * otherwise the card could be removed in between and the request wouldn't
     * fail until another card was inserted.
     */
    if (!sdio_dw_get_cd(slot))
    {
        req->cmd->err = -RT_EIO;
        mmcsd_req_complete(host);

        return;
    }

    rt_hw_spin_lock(&sd->lock.lock);

    sd->slot->req = req;
    sdio_dw_start_request(sd, req->sbc ? : req->cmd);

    rt_hw_spin_unlock(&sd->lock.lock);
}

static void sdio_dw_mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *ios)
{
    rt_err_t err;
    rt_uint32_t regs;
    struct sdio_dw_slot *slot = host->private_data;
    struct sdio_dw *sd = slot->sd;
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    /* Bus */
    switch (ios->bus_width)
    {
    case MMCSD_BUS_WIDTH_4:
        slot->ctype = SDIO_DW_CTYPE_4BIT;
        break;

    case MMCSD_BUS_WIDTH_8:
        slot->ctype = SDIO_DW_CTYPE_8BIT;
        break;

    default:
        slot->ctype = SDIO_DW_CTYPE_1BIT;
        break;
    }

    regs = sdio_dw_readl(sd, UHS_REG);

    /* DDR mode set */
    if (ios->timing == MMCSD_TIMING_MMC_DDR52 ||
        ios->timing == MMCSD_TIMING_UHS_DDR50 ||
        ios->timing == MMCSD_TIMING_MMC_HS400)
    {
        regs |= ((0x1 << slot->id) << 16);
    }
    else
    {
        regs &= ~((0x1 << slot->id) << 16);
    }

    sdio_dw_writel(sd, UHS_REG, regs);
    sd->timing = ios->timing;

    /*
     * Use mirror of ios->clock to prevent race with mmc core ios update when
     * finding the minimum.
     */
    slot->clock = ios->clock;

    if (drv_data && drv_data->set_iocfg)
    {
        drv_data->set_iocfg(sd, ios);
    }

    /* Power */
    switch (ios->power_mode)
    {
    case MMCSD_POWER_UP:
        if (host->supply.vmmc)
        {
            err = sdio_regulator_set_ocr(host, host->supply.vmmc, ios->vdd);

            if (err)
            {
                LOG_E("Failed to enable vmmc regulator error = %s", rt_strerror(err));

                return;
            }
        }
        rt_bitmap_set_bit(&slot->flags, DW_MMC_CARD_NEED_INIT);
        regs = sdio_dw_readl(sd, PWREN);
        regs |= (1 << slot->id);
        sdio_dw_writel(sd, PWREN, regs);
        break;

    case MMCSD_POWER_ON:
        if (!sd->vqmmc_enabled)
        {
            if (host->supply.vqmmc)
            {
                err = rt_regulator_enable(host->supply.vqmmc);

                if (err)
                {
                    LOG_E("Failed to enable vqmmc error = %s", rt_strerror(err));
                }
                else
                {
                    sd->vqmmc_enabled = RT_TRUE;
                }
            }
            else
            {
                sd->vqmmc_enabled = RT_TRUE;
            }

            sdio_dw_ctrl_reset(sd, SDIO_DW_CTRL_ALL_RESET_FLAGS);
        }

        /* Adjust clock / bus width after power is up */
        sdio_dw_setup_bus(slot, RT_FALSE);
        break;

    case MMCSD_POWER_OFF:
        /* Turn clock off before power goes down */
        sdio_dw_setup_bus(slot, RT_FALSE);

        if (host->supply.vmmc)
        {
            sdio_regulator_set_ocr(host, host->supply.vmmc, 0);
        }

        if (host->supply.vqmmc && sd->vqmmc_enabled)
        {
            rt_regulator_disable(host->supply.vqmmc);
        }

        sd->vqmmc_enabled = RT_FALSE;

        regs = sdio_dw_readl(sd, PWREN);
        regs &= ~(1 << slot->id);
        sdio_dw_writel(sd, PWREN, regs);
        break;

    default:
        LOG_E("Invalid power_mode value %x", ios->power_mode);
        break;
    }

    if (sd->state == STATE_WAITING_CMD11_DONE && ios->clock != 0)
    {
        sd->state = STATE_IDLE;
    }
}

static rt_int32_t sdio_dw_mmc_get_card_status(struct rt_mmcsd_host *host)
{
    return 0;
}

static void sdio_dw_mmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    rt_ubase_t level;
    rt_uint32_t int_mask, clk_en_a_old, clk_en_a;
    struct sdio_dw_slot *slot = host->private_data;
    struct sdio_dw *sd = slot->sd;
    const rt_uint32_t clken_low_pwr = SDIO_DW_CLKEN_LOW_PWR << slot->id;

    /*
     * Low power mode will stop the card clock when idle. According to the
     * description of the CLKENA register we should disable low power mode for
     * SDIO cards if we need SDIO interrupts to work.
     */
    clk_en_a_old = sdio_dw_readl(sd, CLKENA);

    if (enable)
    {
        rt_bitmap_set_bit(&slot->flags, DW_MMC_CARD_NO_LOW_PWR);
        clk_en_a = clk_en_a_old & ~clken_low_pwr;
    }
    else
    {
        rt_bitmap_clear_bit(&slot->flags, DW_MMC_CARD_NO_LOW_PWR);
        clk_en_a = clk_en_a_old | clken_low_pwr;
    }

    if (clk_en_a != clk_en_a_old)
    {
        sdio_dw_writel(sd, CLKENA, clk_en_a);
        sdio_dw_send_cmd(slot, SDIO_DW_CMD_UPD_CLK | SDIO_DW_CMD_PRV_DAT_WAIT, 0);
    }

    level = rt_spin_lock_irqsave(&sd->irq_lock);

    /* Enable/disable Slot Specific SDIO interrupt */
    int_mask = sdio_dw_readl(sd, INTMASK);
    if (enable)
    {
        int_mask |= SDIO_DW_INT_SDIO(slot->sdio_id);
    }
    else
    {
        int_mask &= ~SDIO_DW_INT_SDIO(slot->sdio_id);
    }
    sdio_dw_writel(sd, INTMASK, int_mask);

    rt_spin_unlock_irqrestore(&sd->irq_lock, level);
}

static rt_int32_t sdio_dw_mmc_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode)
{
    struct sdio_dw_slot *slot = host->private_data;
    struct sdio_dw *sd = slot->sd;
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    if (drv_data && drv_data->execute_tuning)
    {
        return drv_data->execute_tuning(slot, opcode);
    }

    return -RT_EINVAL;
}

static rt_bool_t sdio_dw_mmc_card_busy(struct rt_mmcsd_host *host)
{
    rt_uint32_t status;
    struct sdio_dw_slot *slot = host->private_data;

    /* Check the busy bit which is low when DAT[3:0] (the data lines) are 0000 */
    status = sdio_dw_readl(slot->sd, STATUS);

    return !!(status & SDIO_DW_STATUS_BUSY);
}

static rt_err_t sdio_dw_mmc_signal_voltage_switch(struct rt_mmcsd_host *host,
    struct rt_mmcsd_io_cfg *ios)
{
    rt_uint32_t uhs, v18;
    struct sdio_dw_slot *slot = host->private_data;
    struct sdio_dw *sd = slot->sd;
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    v18 = SDIO_DW_UHS_18V << slot->id;

    if (drv_data && drv_data->switch_voltage)
    {
        return drv_data->switch_voltage(host, ios);
    }

    /*
     * Program the voltage.  Note that some instances of dw_mmc may use
     * the UHS_REG for this.  For other instances (like exynos) the UHS_REG
     * does no harm but you need to set the regulator directly.  Try both.
     */
    uhs = sdio_dw_readl(sd, UHS_REG);
    if (ios->signal_voltage == MMCSD_SIGNAL_VOLTAGE_330)
    {
        uhs &= ~v18;
    }
    else
    {
        uhs |= v18;
    }

    if (host->supply.vqmmc)
    {
        rt_err_t err = sdio_regulator_set_vqmmc(host, ios);

        if (err < 0)
        {
            LOG_D("Regulator set error %s to %s V", rt_strerror(err),
                    uhs & v18 ? "1.8" : "3.3");

            return err;
        }
    }
    sdio_dw_writel(sd, UHS_REG, uhs);

    return RT_EOK;
}

static const struct rt_mmcsd_host_ops sdio_dw_mmc_ops =
{
    .request = sdio_dw_mmc_request,
    .set_iocfg = sdio_dw_mmc_set_iocfg,
    .get_card_status = sdio_dw_mmc_get_card_status,
    .enable_sdio_irq = sdio_dw_mmc_enable_sdio_irq,
    .execute_tuning = sdio_dw_mmc_execute_tuning,
    .card_busy = sdio_dw_mmc_card_busy,
    .signal_voltage_switch = sdio_dw_mmc_signal_voltage_switch,
};

static void sdio_dw_set_drto(struct sdio_dw *sd)
{
    rt_ubase_t level;
    rt_uint32_t drto_clks, drto_div, drto_ms;
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    if (drv_data && drv_data->get_drto_clks)
    {
        drto_clks = drv_data->get_drto_clks(sd);
    }
    else
    {
        drto_clks = sdio_dw_readl(sd, TMOUT) >> 8;
    }

    drto_div = (sdio_dw_readl(sd, CLKDIV) & 0xff) * 2;

    if (drto_div == 0)
    {
        drto_div = 1;
    }

    drto_ms = RT_DIV_ROUND_UP_ULL((rt_uint64_t)MSEC_PER_SEC * drto_clks * drto_div,
            sd->bus_hz);

    /* Add a bit spare time */
    drto_ms += 10;

    level = rt_spin_lock_irqsave(&sd->irq_lock);

    if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_DATA_COMPLETE))
    {
        rt_tick_t tick = rt_tick_from_millisecond(drto_ms);

        rt_timer_control(&sd->dto_timer, RT_TIMER_CTRL_SET_TIME, &tick);

        rt_timer_start(&sd->dto_timer);
    }

    rt_spin_unlock_irqrestore(&sd->irq_lock, level);
}

static rt_bool_t sdio_dw_clear_pending_cmd_complete(struct sdio_dw *sd)
{
    if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_CMD_COMPLETE))
    {
        return RT_FALSE;
    }

    rt_timer_stop(&sd->cto_timer);
    rt_bitmap_clear_bit(&sd->pending_events, EVENT_CMD_COMPLETE);

    return RT_TRUE;
}

static rt_bool_t sdio_dw_clear_pending_data_complete(struct sdio_dw *sd)
{
    if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_DATA_COMPLETE))
    {
        return RT_FALSE;
    }

    rt_timer_stop(&sd->dto_timer);
    rt_bitmap_clear_bit(&sd->pending_events, EVENT_DATA_COMPLETE);

    return RT_TRUE;
}

static void sdio_dw_state_change(struct rt_work *work, void *work_data)
{
    rt_err_t err;
    rt_uint32_t state, prev_state;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_data *data;
    struct sdio_dw *sd = rt_container_of(work, struct sdio_dw, state_work);

    rt_hw_spin_lock(&sd->lock.lock);

    state = sd->state;
    req = sd->req;
    data = sd->data;

_next_status:
    prev_state = state;

    switch (state)
    {
    case STATE_IDLE:
    case STATE_WAITING_CMD11_DONE:
        break;

    case STATE_SENDING_CMD11:
    case STATE_SENDING_CMD:
        if (!sdio_dw_clear_pending_cmd_complete(sd))
        {
            break;
        }

        cmd = sd->cmd;
        sd->cmd = RT_NULL;
        err = sdio_dw_cmd_complete(sd, cmd);
        if (cmd == req->sbc && !err)
        {
            sdio_dw_start_request(sd, req->cmd);

            goto _unlock;
        }

        if (cmd->data && err)
        {
            if (err != -RT_ETIMEOUT && sd->dir_status == SDIO_DW_RECV_STATUS)
            {
                state = STATE_SENDING_DATA;

                goto _check_status;
            }

            send_stop_abort(sd, data);
            sdio_dw_stop_dma(sd);
            state = STATE_SENDING_STOP;
            break;
        }

        if (!cmd->data || err)
        {
            sdio_dw_end_request(sd);

            goto _unlock;
        }

        prev_state = state = STATE_SENDING_DATA;

        /* Fall through */
    case STATE_SENDING_DATA:
        if (rt_bitmap_test_bit(&sd->pending_events, EVENT_DATA_ERROR))
        {
            rt_bitmap_clear_bit(&sd->pending_events, EVENT_DATA_ERROR);

            if (!(sd->data_status & (PINT(DRTO) | PINT(EBE))))
            {
                send_stop_abort(sd, data);
            }

            sdio_dw_stop_dma(sd);
            state = STATE_DATA_ERROR;
            break;
        }

        if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_XFER_COMPLETE))
        {
            /*
             * If all data-related interrupts don't come within the given time
             * in reading data state.
             */
            if (sd->dir_status == SDIO_DW_RECV_STATUS)
            {
                sdio_dw_set_drto(sd);
            }

            break;
        }
        rt_bitmap_clear_bit(&sd->pending_events, EVENT_XFER_COMPLETE);

        /*
         * Handle an EVENT_DATA_ERROR that might have shown up before the
         * transfer completed. This might not have been caught by the check
         * above because the interrupt could have gone off between the previous
         * check and the check for transfer complete.
         *
         * Technically this ought not be needed assuming we get a DATA_COMPLETE
         * eventually (we'll notice the error and end the request), but it
         * shouldn't hurt.
         *
         * This has the advantage of sending the stop command.
         */
        if (rt_bitmap_test_bit(&sd->pending_events, EVENT_DATA_ERROR))
        {
            rt_bitmap_clear_bit(&sd->pending_events, EVENT_DATA_ERROR);

            if (!(sd->data_status & (PINT(DRTO) | PINT(EBE))))
            {
                send_stop_abort(sd, data);
            }

            sdio_dw_stop_dma(sd);
            state = STATE_DATA_ERROR;
            break;
        }
        prev_state = state = STATE_DATA_BUSY;

        /* Fall through */
    case STATE_DATA_BUSY:
        if (!sdio_dw_clear_pending_data_complete(sd))
        {
            /*
             * If data error interrupt comes but data over interrupt doesn't
             * come within the given time. In reading data state.
             */
            if (sd->dir_status == SDIO_DW_RECV_STATUS)
            {
                sdio_dw_set_drto(sd);
            }

            break;
        }

        sd->data = RT_NULL;
        err = sdio_dw_data_complete(sd, data);

        if (!err)
        {
            if (!data->stop || req->sbc)
            {
                if (req->sbc && data->stop)
                {
                    data->stop->err = RT_EOK;
                }

                sdio_dw_end_request(sd);

                goto _unlock;
            }

            /* Stop command for open-ended transfer */
            if (data->stop)
            {
                send_stop_abort(sd, data);
            }
        }
        else
        {
            /*
             * If we don't have a command complete now we'll never get one since
             * we just reset everything; better end the request.
             *
             * If we do have a command complete we'll fall through to the
             * STATE_SENDING_STOP command and everything will be peachy keen.
             */
            if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_CMD_COMPLETE))
            {
                sd->cmd = RT_NULL;

                sdio_dw_end_request(sd);

                goto _unlock;
            }
        }

        /* If err has non-zero, stop-abort command has been already issued. */
        prev_state = state = STATE_SENDING_STOP;

    /* Fall through */
    case STATE_SENDING_STOP:
        if (!sdio_dw_clear_pending_cmd_complete(sd))
        {
            break;
        }

        /* CMD error in data command */
        if (req->cmd->err && req->data)
        {
            sdio_dw_reset(sd);
        }

        sd->cmd = RT_NULL;
        sd->data = RT_NULL;

        if (!req->sbc && req->stop)
        {
            sdio_dw_cmd_complete(sd, req->stop);
        }
        else
        {
            sd->cmd_status = 0;
        }

        sdio_dw_end_request(sd);
        goto _unlock;

    case STATE_DATA_ERROR:
        if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_XFER_COMPLETE))
        {
            break;
        }
        rt_bitmap_clear_bit(&sd->pending_events, EVENT_XFER_COMPLETE);

        state = STATE_DATA_BUSY;
        break;

    default:
        break;
    }

_check_status:
    if (state != prev_state)
    {
        goto _next_status;
    }

    sd->state = state;
_unlock:
    rt_hw_spin_unlock(&sd->lock.lock);
}

static void sdio_dw_cmd11_timer(void *param)
{
    struct sdio_dw *sd = param;

    if (sd->state != STATE_SENDING_CMD11)
    {
        LOG_W("Unexpected CMD11 timeout");

        return;
    }

    sd->cmd_status = PINT(RTO);
    rt_bitmap_set_bit(&sd->pending_events, EVENT_CMD_COMPLETE);
    rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);
}

static void sdio_dw_cto_timer(void *param)
{
    rt_ubase_t level;
    rt_uint32_t pending;
    struct sdio_dw *sd = param;

    level = rt_spin_lock_irqsave(&sd->irq_lock);

    /*
     * If somehow we have very bad interrupt latency it's remotely possible that
     * the timer could fire while the interrupt is still pending or while the
     * interrupt is midway through running. Let's be paranoid and detect those
     * two cases.  Note that this is paranoia is somewhat justified because in
     * this function we don't actually cancel the pending command in the
     * controller, we just assume it will never come.
     */
    /* Read-only mask reg */
    pending = sdio_dw_readl(sd, MINTSTS);

    if ((pending & (SDIO_DW_CMD_ERROR_FLAGS | PINT(CMD_DONE))))
    {
        /* The interrupt should fire; no need to act but we can warn */
        LOG_W("Unexpected interrupt latency");

        goto _unlock;
    }

    if (rt_bitmap_test_bit(&sd->pending_events, EVENT_CMD_COMPLETE))
    {
        /* Presumably interrupt handler couldn't delete the timer */
        LOG_W("CTO timeout when already completed");

        goto _unlock;
    }

    /*
     * Continued paranoia to make sure we're in the state we expect.
     * This paranoia isn't really justified but it seems good to be safe.
     */
    switch (sd->state)
    {
    case STATE_SENDING_CMD11:
    case STATE_SENDING_CMD:
    case STATE_SENDING_STOP:
        /*
         * If CMD_DONE interrupt does NOT come in sending command state, we
         * should notify the driver to terminate current transfer and report a
         * command timeout to the core.
         */
        sd->cmd_status = PINT(RTO);
        rt_bitmap_set_bit(&sd->pending_events, EVENT_CMD_COMPLETE);
        rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);
        break;

    default:
        LOG_W("Unexpected command timeout, state %d", sd->state);
        break;
    }

_unlock:
    rt_spin_unlock_irqrestore(&sd->irq_lock, level);
}

static void sdio_dw_dto_timer(void *param)
{
    rt_ubase_t level;
    rt_uint32_t pending;
    struct sdio_dw *sd = param;

    level = rt_spin_lock_irqsave(&sd->irq_lock);

    /*
     * The DTO timer is much longer than the CTO timer, so it's even less likely
     * that we'll these cases, but it pays to be paranoid.
     */
    /* Read-only mask reg */
    pending = sdio_dw_readl(sd, MINTSTS);

    if ((pending & PINT(DATA_OVER)))
    {
        /* The interrupt should fire; no need to act but we can warn */
        LOG_W("Unexpected data interrupt latency");

        goto _unlock;
    }

    if (rt_bitmap_test_bit(&sd->pending_events, EVENT_DATA_COMPLETE))
    {
        /* Presumably interrupt handler couldn't delete the timer */
        LOG_W("DTO timeout when already completed");

        goto _unlock;
    }

    /*
     * Continued paranoia to make sure we're in the state we expect.
     * This paranoia isn't really justified but it seems good to be safe.
     */
    switch (sd->state)
    {
    case STATE_SENDING_DATA:
    case STATE_DATA_BUSY:
        /*
         * If DTO interrupt does NOT come in sending data state, we should
         * notify the driver to terminate current transfer and report a data
         * timeout to the core.
         */
        sd->data_status = PINT(DRTO);
        rt_bitmap_set_bit(&sd->pending_events, EVENT_DATA_ERROR);
        rt_bitmap_set_bit(&sd->pending_events, EVENT_DATA_COMPLETE);
        rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);
        break;

    default:
        LOG_W("Unexpected data timeout, state %d", sd->state);
        break;
    }

_unlock:
    rt_spin_unlock_irqrestore(&sd->irq_lock, level);
}

static void sdio_dw_cmd_interrupt(struct sdio_dw *sd, rt_uint32_t status)
{
    rt_timer_stop(&sd->cto_timer);

    if (!sd->cmd_status)
    {
        sd->cmd_status = status;
    }

    /* Drain writebuffer */
    rt_hw_wmb();

    rt_bitmap_set_bit(&sd->pending_events, EVENT_CMD_COMPLETE);
    rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);
}

static void sdio_dw_isr(int irqno, void *param)
{
    rt_uint32_t pending;
    struct sdio_dw *sd = (struct sdio_dw *)param;
    struct sdio_dw_slot *slot = sd->slot;

    /* Read-only mask reg */
    pending = sdio_dw_readl(sd, MINTSTS);

    if (pending)
    {
        if (sd->state == STATE_SENDING_CMD11 && (pending & PINT(VOLT_SWITCH)))
        {
            sdio_dw_writel(sd, RINTSTS, PINT(VOLT_SWITCH));
            pending &= ~PINT(VOLT_SWITCH);

            rt_hw_spin_lock(&sd->irq_lock.lock);
            sdio_dw_cmd_interrupt(sd, pending);
            rt_hw_spin_unlock(&sd->irq_lock.lock);

            rt_timer_stop(&sd->cmd11_timer);
        }

        if ((pending & SDIO_DW_CMD_ERROR_FLAGS))
        {
            rt_hw_spin_lock(&sd->irq_lock.lock);

            rt_timer_stop(&sd->cto_timer);
            sdio_dw_writel(sd, RINTSTS, SDIO_DW_CMD_ERROR_FLAGS);
            sd->cmd_status = pending;
            rt_hw_wmb();
            rt_bitmap_set_bit(&sd->pending_events, EVENT_CMD_COMPLETE);

            rt_hw_spin_unlock(&sd->irq_lock.lock);
        }

        if ((pending & SDIO_DW_DATA_ERROR_FLAGS))
        {
            rt_hw_spin_lock(&sd->irq_lock.lock);

            if ((sd->quirks & SDIO_DW_QUIRK_EXTENDED_TMOUT))
            {
                rt_timer_stop(&sd->dto_timer);
            }

            sdio_dw_writel(sd, RINTSTS, SDIO_DW_DATA_ERROR_FLAGS);
            sd->data_status = pending;
            rt_hw_wmb();
            rt_bitmap_set_bit(&sd->pending_events, EVENT_DATA_ERROR);

            if ((sd->quirks & SDIO_DW_QUIRK_EXTENDED_TMOUT))
            {
                /* In case of error, we cannot expect a DTO */
                rt_bitmap_set_bit(&sd->pending_events, EVENT_DATA_COMPLETE);
            }
            rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);

            rt_hw_spin_unlock(&sd->irq_lock.lock);
        }

        if ((pending & PINT(DATA_OVER)))
        {
            rt_hw_spin_lock(&sd->irq_lock.lock);

            rt_timer_stop(&sd->dto_timer);

            sdio_dw_writel(sd, RINTSTS, PINT(DATA_OVER));
            if (!sd->data_status)
            {
                sd->data_status = pending;
            }
            rt_hw_wmb();

            if (sd->dir_status == SDIO_DW_RECV_STATUS && sd->data && sd->data->buf)
            {
                sdio_dw_read_data_pio(sd, RT_TRUE);
            }
            rt_bitmap_set_bit(&sd->pending_events, EVENT_DATA_COMPLETE);

            rt_workqueue_urgent_work(sd->state_wq, &sd->state_work);

            rt_hw_spin_unlock(&sd->irq_lock.lock);
        }

        if ((pending & PINT(RXDR)))
        {
            sdio_dw_writel(sd, RINTSTS, PINT(RXDR));

            if (sd->dir_status == SDIO_DW_RECV_STATUS && sd->data && sd->data->buf)
            {
                sdio_dw_read_data_pio(sd, RT_FALSE);
            }
        }

        if ((pending & PINT(TXDR)))
        {
            sdio_dw_writel(sd, RINTSTS, PINT(TXDR));

            if (sd->dir_status == SDIO_DW_SEND_STATUS && sd->data && sd->data->buf)
            {
                sdio_dw_write_data_pio(sd);
            }
        }

        if ((pending & PINT(CMD_DONE)))
        {
            rt_hw_spin_lock(&sd->irq_lock.lock);

            sdio_dw_writel(sd, RINTSTS, PINT(CMD_DONE));
            sdio_dw_cmd_interrupt(sd, pending);

            rt_hw_spin_unlock(&sd->irq_lock.lock);
        }

        if ((pending & PINT(CD)))
        {
            sdio_dw_writel(sd, RINTSTS, PINT(CD));
            mmcsd_change(slot->host);
        }

        if ((pending & SDIO_DW_INT_SDIO(slot->sdio_id)))
        {
            sdio_dw_writel(sd, RINTSTS, SDIO_DW_INT_SDIO(slot->sdio_id));
            sdio_dw_mmc_enable_sdio_irq(slot->host, RT_FALSE);
            sdio_irq_wakeup(slot->host);
        }
    }

    if (sd->use_dma != TRANS_MODE_IDMAC)
    {
        return;
    }

    /* Handle IDMA interrupts */
    pending = sd->dma_64bit_address ? sdio_dw_readl(sd, IDSTS64) : sdio_dw_readl(sd, IDSTS);

    if ((pending & (PINTC(TI) | PINTC(RI))))
    {
        if (sd->dma_64bit_address)
        {
            sdio_dw_writel(sd, IDSTS64, PINTC(TI) | PINTC(RI));
            sdio_dw_writel(sd, IDSTS64, PINTC(NI));
        }
        else
        {
            sdio_dw_writel(sd, IDSTS, PINTC(TI) | PINTC(RI));
            sdio_dw_writel(sd, IDSTS, PINTC(NI));
        }

        if (!rt_bitmap_test_bit(&sd->pending_events, EVENT_DATA_ERROR))
        {
            sd->dma_ops->complete(sd);
        }
    }
}

#ifdef RT_USING_OFW
static rt_err_t sdio_dw_parse_ofw(struct sdio_dw *sd)
{
    struct rt_ofw_node *np = sd->parent.ofw_node;
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    rt_ofw_prop_read_u32(np, "fifo-depth", &sd->fifo_depth);
    rt_ofw_prop_read_u32(np, "card-detect-delay", &sd->detect_delay_ms);
    rt_ofw_prop_read_u32(np, "data-addr", &sd->data_addr_override);

    if (rt_ofw_prop_read_bool(np, "fifo-watermark-aligned"))
    {
        sd->wm_aligned = RT_TRUE;
    }

    rt_ofw_prop_read_u32(np, "clock-frequency", &sd->bus_hz);

    if (drv_data && drv_data->parse_ofw)
    {
        return drv_data->parse_ofw(sd);
    }

    return RT_EOK;
}
#else
rt_inline rt_err_t sdio_dw_parse_ofw(struct sdio_dw *sd)
{
    return -RT_ENOSYS;
}
#endif /* RT_USING_OFW */

static rt_err_t sdio_dw_init_slot(struct sdio_dw *sd)
{
    rt_err_t err;
    struct sdio_dw_slot *slot;
    struct rt_mmcsd_host *host = mmcsd_alloc_host();

    if (!host)
    {
        return -RT_ENOMEM;
    }

    slot = rt_calloc(1, sizeof(*slot));

    if (!slot)
    {
        err = -RT_ENOMEM;
        goto _free;
    }

    err = sdio_regulator_get_supply(&sd->parent, host);

    if (err)
    {
        goto _free;
    }

    host->ops = &sdio_dw_mmc_ops;
    host->private_data = slot;
    slot->host = host;
    slot->sd = sd;
    sd->slot = slot;

    slot->id = 0;
    slot->sdio_id = sd->sdio_id0 + slot->id;

    err = sdio_ofw_parse(sd->parent.ofw_node, host);

    if (err)
    {
        goto _free;
    }

    if (!host->valid_ocr)
    {
        host->valid_ocr = VDD_32_33 | VDD_33_34;
    }

    if (sd->minimum_speed)
    {
        host->freq_min = sd->minimum_speed;
    }
    else
    {
        host->freq_min = SDIO_DW_FREQ_HZ_MIN;
    }

    if (!host->freq_max)
    {
        host->freq_max = SDIO_DW_FREQ_HZ_MAX;
    }

    /* Useful defaults if platform data is unset. */
    if (sd->use_dma == TRANS_MODE_IDMAC)
    {
        host->max_dma_segs = sd->ring_size;
        host->max_blk_size = 65535;
        host->max_seg_size = DESC_RING_BUF_SZ;
        host->max_blk_count = (host->max_seg_size * sd->ring_size) / 512;
    }
    else if (sd->use_dma == TRANS_MODE_EDMAC)
    {
        host->max_dma_segs = 64;
        host->max_blk_size = 65535;
        host->max_blk_count = 65535;
        host->max_seg_size = host->max_blk_size * host->max_blk_count;
    }
    else
    {
        /* TRANS_MODE_PIO */
        host->max_dma_segs = 64;
        host->max_blk_size = 65535;
        host->max_blk_count = 512;
        host->max_seg_size = host->max_blk_size * host->max_blk_count;
    }

    return RT_EOK;

_free:
    if (host)
    {
        mmcsd_free_host(host);
    }
    if (slot)
    {
        rt_free(slot);
    }
    return err;
}

static void sdio_dw_free(struct sdio_dw *sd)
{
    if (!rt_is_err_or_null(sd->rstc))
    {
        rt_reset_control_assert(sd->rstc);
        rt_reset_control_put(sd->rstc);
    }

    if (!rt_is_err_or_null(sd->ciu_clk))
    {
        rt_clk_disable_unprepare(sd->ciu_clk);
        rt_clk_put(sd->ciu_clk);
    }

    if (!rt_is_err_or_null(sd->biu_clk))
    {
        rt_clk_disable_unprepare(sd->biu_clk);
        rt_clk_put(sd->biu_clk);
    }

    if (sd->use_dma && sd->dma_ops->exit)
    {
        sd->dma_ops->exit(sd);
    }

    if (sd->dma_buf)
    {
        rt_dma_free_coherent(sd->bus_dev,
                DESC_RING_BUF_SZ, sd->dma_buf, sd->dma_buf_phy);
    }
}

rt_err_t sdio_dw_probe(struct sdio_dw *sd)
{
    int i, len;
    rt_err_t err = RT_EOK;
    char dev_name[RT_NAME_MAX];
    const struct sdio_dw_drv_data *drv_data = sd->drv_data;

    err = sdio_dw_parse_ofw(sd);

    if (err && err != -RT_ENOSYS)
    {
        goto _free_res;
    }

    sd->rstc = rt_reset_control_get_by_name(&sd->parent, "reset");

    if (rt_is_err(sd->rstc))
    {
        LOG_E("Reset controller not found");

        err = rt_ptr_err(sd->rstc);
        goto _free_res;
    }

    if (sd->rstc)
    {
        rt_reset_control_assert(sd->rstc);
        rt_hw_us_delay(20);
        rt_reset_control_deassert(sd->rstc);
    }

    sd->biu_clk = rt_clk_get_by_name(&sd->parent, "biu");
    sd->ciu_clk = rt_clk_get_by_name(&sd->parent, "ciu");

    if (rt_is_err(sd->biu_clk) || rt_is_err(sd->ciu_clk))
    {
        /* board has init clock */
        if (sd->bus_hz)
        {
            goto _out_clk;
        }

        err = rt_is_err(sd->biu_clk) ? rt_ptr_err(sd->biu_clk) : rt_ptr_err(sd->ciu_clk);
        goto _free_res;
    }

    err = rt_clk_prepare_enable(sd->ciu_clk);

    if (err)
    {
        goto _free_res;
    }

    if (sd->bus_hz)
    {
        rt_clk_set_rate(sd->ciu_clk, sd->bus_hz);
    }

    sd->bus_hz = rt_clk_get_rate(sd->ciu_clk);

    if (!sd->bus_hz)
    {
        err = -RT_EIO;
        LOG_E("Bus speed not found");
        goto _free_res;
    }

_out_clk:
    if (drv_data && drv_data->init)
    {
        err = drv_data->init(sd);

        if (err)
        {
            goto _free_res;
        }
    }

    rt_spin_lock_init(&sd->lock);
    rt_spin_lock_init(&sd->irq_lock);

    /*
     * Get the host data width - this assumes that HCON has been set with the
     * correct values.
     */
    i = SDIO_DW_GET_HDATA_WIDTH(sdio_dw_readl(sd, HCON));
    if (!i)
    {
        sd->push_data = sdio_dw_push_data16;
        sd->pull_data = sdio_dw_pull_data16;
        sd->data_shift = 1;
    }
    else if (i == 2)
    {
        sd->push_data = sdio_dw_push_data64;
        sd->pull_data = sdio_dw_pull_data64;
        sd->data_shift = 3;
    }
    else
    {
        /* Check for a reserved value, and warn if it is */
        if (i != 1)
        {
            LOG_W("HCON reports a reserved host data width, defaulting to 32-bit access");
        }

        sd->push_data = sdio_dw_push_data32;
        sd->pull_data = sdio_dw_pull_data32;
        sd->data_shift = 2;
    }

    /* Reset all blocks */
    if (!sdio_dw_ctrl_reset(sd, SDIO_DW_CTRL_ALL_RESET_FLAGS))
    {
        err = -RT_EIO;

        goto _free_res;
    }

    sdio_dw_init_dma(sd);

    /* Clear the interrupts for the host controller */
    sdio_dw_writel(sd, RINTSTS, 0xffffffff);
    /* Disable all mmc interrupt first */
    sdio_dw_writel(sd, INTMASK, 0);

    /* Put in max timeout */
    sdio_dw_writel(sd, TMOUT, 0xffffffff);

    /*
     * FIFO threshold settings:
     *  Rx Mark = fifo_size / 2 - 1,
     *  Tx Mark = fifo_size / 2
     *  DMA Size = 8
     */
    if (sd->fifo_depth)
    {
        /*
         * Power-on value of RX_WMark is FIFO_DEPTH-1, but this may have been
         * overwritten by the bootloader, just like we're about to do, so if you
         * know the value for your hardware, you should put it in the platform
         * data.
         */
        sd->fifo_depth = sdio_dw_readl(sd, FIFOTH);
        sd->fifo_depth = 1 + ((sd->fifo_depth >> 16) & 0xfff);
    }
    sd->fifoth_val = SDIO_DW_SET_FIFOTH(0x2, sd->fifo_depth / 2 - 1, sd->fifo_depth / 2);
    sdio_dw_writel(sd, FIFOTH, sd->fifoth_val);

    /* Disable clock to CIU */
    sdio_dw_writel(sd, CLKENA, 0);
    sdio_dw_writel(sd, CLKSRC, 0);

    /*
     * In 2.40a spec, Data offset is changed.
     * Need to check the version-id and set data-offset for DATA register.
     */
    sd->verid = SDIO_DW_GET_VERID(sdio_dw_readl(sd, VERID));
    LOG_D("Version ID is %04x", sd->verid);

    if (sd->data_addr_override)
    {
        sd->fifo_base = sd->base + sd->data_addr_override;
    }
    else if (sd->verid < SDIO_DW_240A)
    {
        sd->fifo_base = sd->base + DATA_OFFSET;
    }
    else
    {
        sd->fifo_base = sd->base + DATA_240A_OFFSET;
    }

    /*
     * Enable interrupts for command done, data over, data empty, receive ready
     * and error such as transmit, receive timeout, crc error
     */
    sdio_dw_writel(sd, INTMASK, PINT(CMD_DONE) | PINT(DATA_OVER) | PINT(TXDR) | PINT(RXDR) | SDIO_DW_ERROR_FLAGS);
    /* Enable mci interrupt */
    sdio_dw_writel(sd, CTRL, SDIO_DW_CTRL_INT_ENABLE);

    /* Enable GPIO interrupt */
    sdio_dw_writel(sd, INTMASK, sdio_dw_readl(sd, INTMASK) | PINT(CD));

    /* We need at least one slot to succeed */
    err = sdio_dw_init_slot(sd);

    if (err)
    {
        goto _free_res;
    }

    /* Now that slots are all setup, we can enable card detect */
    sdio_dw_writel(sd, INTMASK, sdio_dw_readl(sd, INTMASK) | PINT(CD));

    len = sdio_host_set_name(sd->slot->host, dev_name);

    sd->state_wq = rt_workqueue_create(dev_name, RT_SYSTEM_WORKQUEUE_STACKSIZE,
            RT_MMCSD_THREAD_PRIORITY);

    if (!sd->state_wq)
    {
        err = -RT_ENOMEM;

        goto _free_res;
    }

    rt_work_init(&sd->state_work, sdio_dw_state_change, sd);

    rt_hw_interrupt_install(sd->irq, sdio_dw_isr, sd, dev_name);
    rt_hw_interrupt_umask(sd->irq);

    rt_strncpy(&dev_name[len], "-cmd11", sizeof(dev_name) - len);
    rt_timer_init(&sd->cmd11_timer, dev_name, sdio_dw_cmd11_timer, sd,
            0, RT_TIMER_FLAG_PERIODIC);

    rt_strncpy(&dev_name[len], "-cto", sizeof(dev_name) - len);
    rt_timer_init(&sd->cto_timer, dev_name, sdio_dw_cto_timer, sd,
            0, RT_TIMER_FLAG_PERIODIC);

    rt_strncpy(&dev_name[len], "-dto", sizeof(dev_name) - len);
    rt_timer_init(&sd->dto_timer, dev_name, sdio_dw_dto_timer, sd,
            0, RT_TIMER_FLAG_PERIODIC);

    mmcsd_change(sd->slot->host);

    return err;

_free_res:
    sdio_dw_free(sd);

    return err;
}

rt_err_t sdio_dw_remove(struct sdio_dw *sd)
{
    if (sd->slot)
    {
        mmcsd_free_host(sd->slot->host);
    }

    sdio_dw_writel(sd, RINTSTS, 0xffffffff);
    /* Disable all mmc interrupt first */
    sdio_dw_writel(sd, INTMASK, 0);

    /* Disable clock to CIU */
    sdio_dw_writel(sd, CLKENA, 0);
    sdio_dw_writel(sd, CLKSRC, 0);

    rt_hw_interrupt_mask(sd->irq);
    rt_pic_detach_irq(sd->irq, sd);

    rt_timer_detach(&sd->cmd11_timer);
    rt_timer_detach(&sd->cto_timer);
    rt_timer_detach(&sd->dto_timer);

    sdio_dw_free(sd);

    return RT_EOK;
}
