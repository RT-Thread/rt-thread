/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <string.h>
#include <drivers/dev_mmcsd_core.h>
#include <dm36x.h>
#include "mmcsd.h"
#include "edma.h"

#define RT_USING_MMCSD0

#define MMCSD_DEBUG         0
#if MMCSD_DEBUG
#define mmc_dbg(fmt, ...)   rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define mmc_dbg(fmt, ...)
#endif

#define MMU_NOCACHE_ADDR(a)         ((rt_uint32_t)a | (1UL<<29))
#define CACHE_LINE_SIZE 32


extern void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size);
extern void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size);

#define EVT_QUEUE_NUM               0   /* EDMA3 Event queue number. */

static unsigned rw_threshold = 32;
static rt_bool_t use_dma = RT_TRUE;

enum DATA_DIR_TYPE
{
    DM365_MMC_DATADIR_NONE = 0,
    DM365_MMC_DATADIR_READ,
    DM365_MMC_DATADIR_WRITE,
};

struct mmc_dm365_host
{
    struct rt_mmcsd_host        *mmc;
    struct rt_mmcsd_req         *req;
    struct rt_mmcsd_data        *data;
    struct rt_mmcsd_cmd         *cmd;
    struct edmacc_param     tx_template;
    struct edmacc_param     rx_template;

    rt_uint32_t mmc_input_clk;
    rt_uint32_t ns_in_one_cycle;    /* for ns in one cycle calculation */

    mmcsd_regs_t *mmcsd_regs;
    rt_uint8_t  bus_mode;

    enum DATA_DIR_TYPE  data_dir;

    rt_uint32_t rxdma;
    rt_uint32_t txdma;
    rt_bool_t   use_dma;
    rt_bool_t   do_dma;

    rt_uint8_t *buffer;
    rt_uint32_t buffer_bytes_left;
    rt_uint32_t bytes_left;

    rt_uint8_t *dma_buffer;
    rt_bool_t   use_dma_buffer;
    rt_bool_t   sdio_int;
};

void *mmc_priv(struct rt_mmcsd_host *host)
{
    return (void *)host->private_data;
}

static void delay_us(rt_uint32_t us)
{
    rt_uint32_t len;
    for (;us > 0; us --)
        for (len = 0; len < 10; len++ );
}

/*******************************************************************************************************
** 函数名称: calculate_freq_for_card()
** 功能描述: 此函数用于计算设置SD卡频率所需的分频数
**
** 输　入: host            ->  DM365 MMC host句柄
**         mmc_req_freq ->  MMC工作频率
**
** 输　出: 分频值
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static rt_uint32_t calculate_freq_for_card(struct mmc_dm365_host *host, rt_uint32_t mmc_req_freq)
{
    rt_uint32_t mmc_freq = 0;
    rt_uint32_t mmc_pclk = 0;
    rt_uint32_t mmc_push_pull_divisor = 0;

    mmc_pclk = host->mmc_input_clk;

    if (mmc_req_freq && mmc_pclk > (2 * mmc_req_freq))
        mmc_push_pull_divisor = ((rt_uint32_t)mmc_pclk / (2 * mmc_req_freq)) - 1;
    else
        mmc_push_pull_divisor = 0;

    mmc_freq = (rt_uint32_t)mmc_pclk / (2 * (mmc_push_pull_divisor + 1));

    if (mmc_freq > mmc_req_freq)
        mmc_push_pull_divisor = mmc_push_pull_divisor + 1;

    /* Convert ns to clock cycles */
    if (mmc_req_freq <= 400000)
        host->ns_in_one_cycle = (1000000)/(((mmc_pclk/(2*(mmc_push_pull_divisor+1)))/1000));
    else
        host->ns_in_one_cycle = (1000000)/(((mmc_pclk/(2*(mmc_push_pull_divisor+1)))/1000000));

    return mmc_push_pull_divisor;
}

/*******************************************************************************************************
** 函数名称: calculate_freq_for_card()
** 功能描述: 此函数用于计算MMC clock分频数
**
** 输　入: host            ->  DM365 MMC host句柄
**         ios          ->  MMC 操作句柄
**
** 输　出: 读取到的PHY寄存器值
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void calculate_clk_divider(struct rt_mmcsd_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    rt_uint32_t temp = 0;
    rt_uint32_t mmc_pclk = 0;
    rt_uint32_t open_drain_freq = 0;
    rt_uint32_t mmc_push_pull_freq = 0;
    struct mmc_dm365_host *host = mmc_priv(mmc);

    mmc_pclk = host->mmc_input_clk;

    if (ios->bus_mode == MMCSD_BUSMODE_OPENDRAIN)
    {
        /* Ignoring the init clock value passed for fixing the inter
         * operability with different cards.
         */
        open_drain_freq = ((rt_uint32_t)mmc_pclk / (2 * MMCSD_INIT_CLOCK)) - 1;

        if (open_drain_freq > 0xFF)
            open_drain_freq = 0xFF;

        temp = host->mmcsd_regs->MMCCLK & ~MMCCLK_CLKRT_MASK;
        temp |= open_drain_freq;
        host->mmcsd_regs->MMCCLK = temp;


        /* Convert ns to clock cycles */
        host->ns_in_one_cycle = (1000000) / (MMCSD_INIT_CLOCK / 1000);
    }
    else
    {
        mmc_push_pull_freq = calculate_freq_for_card(host, ios->clock);

        if (mmc_push_pull_freq > 0xFF)
            mmc_push_pull_freq = 0xFF;

        temp = host->mmcsd_regs->MMCCLK & ~MMCCLK_CLKEN;
        host->mmcsd_regs->MMCCLK = temp;

        delay_us(10);

        temp = host->mmcsd_regs->MMCCLK & ~MMCCLK_CLKRT_MASK;
        temp |= mmc_push_pull_freq;
        host->mmcsd_regs->MMCCLK = temp;

        host->mmcsd_regs->MMCCLK = temp | MMCCLK_CLKEN;

        delay_us(10);
    }
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_set_ios()
** 功能描述: 此函数是mmc设置设置
**
** 输　入: mmc         ->  mmc host 句柄
**         ios          ->  mmc 操作句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_set_ios(struct rt_mmcsd_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    struct mmc_dm365_host *host = mmc_priv(mmc);

    mmc_dbg("clock %dHz busmode %d powermode %d Vdd %04x\n", ios->clock, ios->bus_mode, ios->power_mode, ios->vdd);

    switch (ios->bus_width)
    {
    case MMCSD_BUS_WIDTH_8:
        mmc_dbg("Enabling 8 bit mode\n");
        host->mmcsd_regs->MMCCTL = (host->mmcsd_regs->MMCCTL & ~MMCCTL_WIDTH_4_BIT) | MMCCTL_WIDTH_8_BIT;
        break;
    case MMCSD_BUS_WIDTH_4:
        mmc_dbg("Enabling 4 bit mode\n");
        host->mmcsd_regs->MMCCTL = (host->mmcsd_regs->MMCCTL & ~MMCCTL_WIDTH_8_BIT) | MMCCTL_WIDTH_4_BIT;
        break;
    case MMCSD_BUS_WIDTH_1:
        mmc_dbg("Enabling 1 bit mode\n");
        host->mmcsd_regs->MMCCTL = host->mmcsd_regs->MMCCTL & ~(MMCCTL_WIDTH_8_BIT | MMCCTL_WIDTH_4_BIT);
        break;
    }

    calculate_clk_divider(mmc, ios);

    host->bus_mode = ios->bus_mode;
    if (ios->power_mode == MMCSD_POWER_UP)
    {
        unsigned long timeout = rt_tick_get() + 500;
        rt_bool_t lose = 1;

        host->mmcsd_regs->MMCARGHL = 0;
        host->mmcsd_regs->MMCCMD = MMCCMD_INITCK;

        while (rt_tick_get() < timeout)
        {
            rt_uint32_t tmp = host->mmcsd_regs->MMCST0;

            if (tmp & MMCST0_RSPDNE)
            {
                lose = 0;
                break;
            }
        }
        if (lose)
            mmc_dbg("powerup timeout\n");
    }
}

/*******************************************************************************************************
** 函数名称: dm365_fifo_data_trans()
** 功能描述: 此函数是fifo模式传输
**
** 输　入: host            ->  DM365 mmc host 句柄
**         n            ->  传输字节数
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void dm365_fifo_data_trans(struct mmc_dm365_host *host, rt_uint32_t n)
{
    rt_uint8_t *p;
    rt_uint32_t i;

    p = host->buffer;

    if (host->bytes_left < n)
        n = host->bytes_left;

    host->bytes_left -= n;

    /* NOTE:  we never transfer more than rw_threshold bytes
     * to/from the fifo here; there's no I/O overlap.
     * This also assumes that access width( i.e. ACCWD) is 4 bytes
     */
    if (host->data_dir == DM365_MMC_DATADIR_WRITE)
    {
        for (i = 0; i < (n >> 2); i++)
        {
            host->mmcsd_regs->MMCDXR = *((rt_uint32_t *)p);
            p = p + 4;
        }
        if (n & 3)
        {
            rt_kprintf("to do ... \n");
//          iowrite8_rep(host->base + MMCSD_MMCDXR, p, (n & 3));
            p = p + (n & 3);
        }
    }
    else
    {
        for (i = 0; i < (n >> 2); i++)
        {
            *((rt_uint32_t *)p) = host->mmcsd_regs->MMCDRR;
            p  = p + 4;
        }
        if (n & 3)
        {
            rt_kprintf("to do ... \n");
//          ioread8_rep(host->base + MMCSD_MMCDRR, p, (n & 3));
            p = p + (n & 3);
        }
    }
    host->buffer = p;
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_start_command()
** 功能描述: 此函数是开始发送SD命令
**
** 输　入: host            ->  DM365 mmc host 句柄
**         cmd          ->  SD命令句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_start_command(struct mmc_dm365_host *host, struct rt_mmcsd_cmd *cmd)
{
    rt_uint32_t cmd_reg = 0;
    rt_uint32_t im_val;

    host->cmd = cmd;

    switch (resp_type(cmd))
    {
    case RESP_R1B:
        /* There's some spec confusion about when R1B is
         * allowed, but if the card doesn't issue a BUSY
         * then it's harmless for us to allow it.
         */
        cmd_reg |= MMCCMD_BSYEXP;
        /* FALLTHROUGH */
    case RESP_R1:       /* 48 bits, CRC */
    case RESP_R4:
    case RESP_R5:
    case RESP_R6:
    case RESP_R7:
        cmd_reg |= MMCCMD_RSPFMT_R1456;
        break;
    case RESP_R2:       /* 136 bits, CRC */
        cmd_reg |= MMCCMD_RSPFMT_R2;
        break;
    case RESP_R3:       /* 48 bits, no CRC */
        cmd_reg |= MMCCMD_RSPFMT_R3;
        break;
    default:
        cmd_reg |= MMCCMD_RSPFMT_NONE;
        mmc_dbg("unknown resp_type %04x\n", resp_type(cmd));
        break;
    }

    /* Set command index */
    cmd_reg |= cmd->cmd_code;

    /* Enable EDMA transfer triggers */
    if (host->do_dma == RT_TRUE)
        cmd_reg |= MMCCMD_DMATRIG;

    if (host->data != RT_NULL && host->data_dir == DM365_MMC_DATADIR_READ)
        cmd_reg |= MMCCMD_DMATRIG;

    /* Setting whether command involves data transfer or not */
    if (cmd->data)
        cmd_reg |= MMCCMD_WDATX;

    /* Setting whether stream or block transfer */
    if (cmd->flags & MMC_DATA_STREAM)
    {
        mmc_dbg("to do\n");
        cmd_reg |= MMCCMD_STRMTP;
    }

    /* Setting whether data read or write */
    if (host->data_dir == DM365_MMC_DATADIR_WRITE)
        cmd_reg |= MMCCMD_DTRW;

    if (host->bus_mode == MMCSD_BUSMODE_PUSHPULL)
    {
        cmd_reg |= MMCCMD_PPLEN;
    }

    /* set Command timeout */
    host->mmcsd_regs->MMCTOR = 0x1FFF;

    /* Enable interrupt (calculate here, defer until FIFO is stuffed). */
    im_val =  MMCST0_RSPDNE | MMCST0_CRCRS | MMCST0_TOUTRS;
    if (host->data_dir == DM365_MMC_DATADIR_WRITE)
    {
        im_val |= MMCST0_DATDNE | MMCST0_CRCWR;

        if (host->do_dma == RT_FALSE)
            im_val |= MMCST0_DXRDY;
    }
    else if (host->data_dir == DM365_MMC_DATADIR_READ)
    {
        im_val |= MMCST0_DATDNE | MMCST0_CRCRD | MMCST0_TOUTRD;

        if (host->do_dma == RT_FALSE)
            im_val |= MMCST0_DRRDY;
    }

    /*
     * Before non-DMA WRITE commands the controller needs priming:
     * FIFO should be populated with 32 bytes i.e. whatever is the FIFO size
     */
    if ((host->do_dma == RT_FALSE) && (host->data_dir == DM365_MMC_DATADIR_WRITE))
        dm365_fifo_data_trans(host, rw_threshold);

    host->mmcsd_regs->MMCARGHL = cmd->arg;
    host->mmcsd_regs->MMCCMD = cmd_reg;
    host->mmcsd_regs->MMCIM = im_val;
}

/*******************************************************************************************************
** 函数名称: dm365_abort_dma()
** 功能描述: 此函数终止DMA传输
**
** 输　入: host            ->  DM365 mmc host 句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void dm365_abort_dma(struct mmc_dm365_host *host)
{
    int sync_dev;

    if (host->data_dir == DM365_MMC_DATADIR_READ)
        sync_dev = host->rxdma;
    else
        sync_dev = host->txdma;

    //EDMA3DisableTransfer(EDMA0CC0_REG_BASE, sync_dev, EDMA3_TRIG_MODE_EVENT);
    edma_stop(sync_dev);
    edma_clean_channel(sync_dev);
}

/*******************************************************************************************************
** 函数名称: mmc_request_done()
** 功能描述: 此函数用于结束处理一个MMC请求
**
** 输　入: host            ->  DM365 mmc host 句柄
**         mrq          ->  request 句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
void mmc_request_done(struct rt_mmcsd_host *host, struct rt_mmcsd_req *mrq)
{
    struct rt_mmcsd_cmd *cmd = mrq->cmd;
    int err = cmd->err;

    if (err && cmd->retries)
    {
        mmc_dbg("req failed (CMD%u): %d, retrying...\n", cmd->cmd_code, err);

        cmd->retries--;
        cmd->err = 0;
        host->ops->request(host, mrq);
    }
    else
    {
        mmc_dbg("%s: req done (CMD%u): %d: %08x %08x %08x %08x\n",
            "dm365 host", cmd->cmd_code, err,
            cmd->resp[0], cmd->resp[1],
            cmd->resp[2], cmd->resp[3]);

        if (mrq->data)
        {
            mmc_dbg("%s:     %d bytes transferred: %d\n",
                "dm365 host",
                mrq->data->bytes_xfered, mrq->data->err);
        }

        if (mrq->stop)
        {
            mmc_dbg("%s:     (CMD%u): %d: %08x %08x %08x %08x\n",
                "dm365 host", mrq->stop->cmd_code,
                mrq->stop->err,
                mrq->stop->resp[0], mrq->stop->resp[1],
                mrq->stop->resp[2], mrq->stop->resp[3]);
        }

        mmcsd_req_complete(host);
    }
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_xfer_done()
** 功能描述: 数据传送结束调用此函数
**
** 输　入: host            ->  DM365 mmc host 句柄
**         data         ->  data 句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_xfer_done(struct mmc_dm365_host *host, struct rt_mmcsd_data *data)
{
    host->data = RT_NULL;

    if (host->mmc->flags & MMCSD_SUP_SDIO_IRQ) {
        /*
         * SDIO Interrupt Detection work-around as suggested by
         * Davinci Errata (TMS320DM355 Silicon Revision 1.1 Errata
         * 2.1.6): Signal SDIO interrupt only if it is enabled by core
         */
        if (host->sdio_int && !(host->mmcsd_regs->SDIOST0 &
                    SDIOST0_DAT1_HI)) {
            host->mmcsd_regs->SDIOIST = SDIOIST_IOINT;
            sdio_irq_wakeup(host->mmc);
        }
    }

    if (host->do_dma == RT_TRUE)
    {
        dm365_abort_dma(host);

        if (data->flags & DATA_DIR_READ)
        {
            /* read operation */
            if (host->use_dma_buffer == RT_TRUE)
            {
                /* copy DMA buffer to read buffer */
                memcpy(data->buf, (void*)MMU_NOCACHE_ADDR(host->dma_buffer), data->blks * data->blksize);
            }
            /*else
            {
                mmu_invalidate_dcache((rt_uint32_t)data->buf, data->blks * data->blksize);
            }*/
        }

        host->do_dma = RT_FALSE;
    }

    host->data_dir = DM365_MMC_DATADIR_NONE;

    if (!data->stop || (host->cmd && host->cmd->err))
    {
        mmc_request_done(host->mmc, data->mrq);
        host->mmcsd_regs->MMCIM = 0;
    }
    else
        mmc_dm365_start_command(host, data->stop);
}

static void mmc_dm365_dma_cb(unsigned channel, rt_uint16_t ch_status, void *data)
{
    if (DMA_COMPLETE != ch_status) {
        struct mmc_dm365_host *host = data;

        /* Currently means:  DMA Event Missed, or "null" transfer
         * request was seen.  In the future, TC errors (like bad
         * addresses) might be presented too.
         */
        mmc_dbg("DMA %s error\n",
            (host->data->flags & MMC_DATA_WRITE)
                ? "write" : "read");
        host->data->err = -RT_EIO;
        mmc_dm365_xfer_done(host, host->data);
    }
}


/*******************************************************************************************************
** 函数名称: mmc_dm365_dma_setup()
** 功能描述: DMA 设置函数
**
** 输　入: host            ->  DM365 mmc host 句柄
**         tx           ->  布尔变量，用于判断Tx或者是Rx
**         template     ->  用于保存EDMA3CCPaRAMEntry机构数据
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_dma_setup(struct mmc_dm365_host *host, rt_bool_t tx, struct edmacc_param *template)
{
    rt_uint32_t       sync_dev;
    const rt_uint16_t acnt = 4;
    const rt_uint16_t bcnt = rw_threshold >> 2;
    const rt_uint16_t   ccnt = 0;
    rt_uint32_t     src_port = 0;
    rt_uint32_t     dst_port = 0;
    rt_int16_t      src_bidx, dst_bidx;
    rt_int16_t      src_cidx, dst_cidx;

    //edmacc_param paramSet;

    /*
     * A-B Sync transfer:  each DMA request is for one "frame" of
     * rw_threshold bytes, broken into "acnt"-size chunks repeated
     * "bcnt" times.  Each segment needs "ccnt" such frames; since
     * we tell the block layer our mmc->max_seg_size limit, we can
     * trust (later) that it's within bounds.
     *
     * The FIFOs are read/written in 4-byte chunks (acnt == 4) and
     * EDMA will optimize memory operations to use larger bursts.
     */
    if (tx)
    {
        sync_dev = host->txdma;

        /* src_prt, ccnt, and link to be set up later */
        /*paramSet.srcBIdx = acnt;
        paramSet.srcCIdx = acnt * bcnt;

        paramSet.destAddr = (rt_uint32_t)&(host->mmcsd_regs->MMCDXR);
        paramSet.destBIdx = 0;
        paramSet.destCIdx = 0;*/
        /* src_prt, ccnt, and link to be set up later */
        src_bidx = acnt;
        src_cidx = acnt * bcnt;

        dst_port = (rt_uint32_t)&(host->mmcsd_regs->MMCDXR);
        dst_bidx = 0;
        dst_cidx = 0;
    }
    else
    {
        sync_dev = host->rxdma;

        /* dst_prt, ccnt, and link to be set up later */
        /*paramSet.srcAddr = (rt_uint32_t)&(host->mmcsd_regs->MMCDRR);
        paramSet.srcBIdx = 0;
        paramSet.srcCIdx = 0;

        paramSet.destBIdx = acnt;
        paramSet.destCIdx = acnt * bcnt;*/
        src_port = (rt_uint32_t)&(host->mmcsd_regs->MMCDRR);
        src_bidx = 0;
        src_cidx = 0;

        /* dst_prt, ccnt, and link to be set up later */
        dst_bidx = acnt;
        dst_cidx = acnt * bcnt;
    }
    /*
     * We can't use FIFO mode for the FIFOs because MMC FIFO addresses
     * are not 256-bit (32-byte) aligned.  So we use INCR, and the W8BIT
     * parameter is ignored.
     */
    edma_set_src(sync_dev, src_port, INCR, W8BIT);
    edma_set_dest(sync_dev, dst_port, INCR, W8BIT);

    edma_set_src_index(sync_dev, src_bidx, src_cidx);
    edma_set_dest_index(sync_dev, dst_bidx, dst_cidx);

    edma_set_transfer_params(sync_dev, acnt, bcnt, ccnt, 8, ABSYNC);

    edma_read_slot(sync_dev, template);

    /* don't bother with irqs or chaining */
    template->opt |= EDMA_CHAN_SLOT(sync_dev) << 12;

#if 0
    paramSet.opt = 0u;
    /* Src & Dest are in INCR modes */
    paramSet.opt &= 0xFFFFFFFCu;
    /* Program the TCC */
    paramSet.opt |= ((sync_dev << EDMA3CC_OPT_TCC_SHIFT) & EDMA3CC_OPT_TCC);

    paramSet.aCnt = acnt;
    paramSet.bCnt = bcnt;

    /* AB Sync Transfer Mode */
    paramSet.opt |= (1 << EDMA3CC_OPT_SYNCDIM_SHIFT);

    /* Now, write the PaRAM Set. */
    EDMA3SetPaRAM(EDMA0CC0_REG_BASE, sync_dev, &paramSet);

    EDMA3GetPaRAM(EDMA0CC0_REG_BASE, sync_dev, template);
#endif
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_send_dma_request()
** 功能描述: 发送DMA请求
**
** 输　入: host            ->  DM365 mmc host 句柄
**         data         ->  DMA传送数据结构句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_send_dma_request(struct mmc_dm365_host *host, struct rt_mmcsd_data *data)
{
    //struct EDMA3CCPaRAMEntry *template;
    struct edmacc_param *template;
    rt_uint32_t buf_ptr;
    rt_uint32_t channel;
    rt_uint32_t bytes_left = host->bytes_left;
    rt_uint32_t count = host->bytes_left;
    const rt_uint32_t shift = ffs(rw_threshold) - 1;

    if (host->use_dma_buffer == RT_TRUE)
        buf_ptr = host->dma_buffer;//MMU_NOCACHE_ADDR(host->dma_buffer);
    else
        buf_ptr = (rt_uint32_t)data->buf;

    if (host->data_dir == DM365_MMC_DATADIR_WRITE)
    {
        template = &host->tx_template;
        channel = host->txdma;
    }
    else
    {
        template = &host->rx_template;
        channel = host->rxdma;
    }

    template->link_bcntrld = 0xffff;
    //template->bCntReload = 0x0;

    if (count > bytes_left)
        count = bytes_left;
    bytes_left -= count;

    if (host->data_dir == DM365_MMC_DATADIR_WRITE)
        template->src = buf_ptr;
    else
        template->dst = buf_ptr;
    template->ccnt = count >> shift;

    edma_write_slot(channel, template);

    edma_clear_event(channel);

    /*EDMA3SetPaRAM(EDMA0CC0_REG_BASE, channel, template);
    EDMA3ClrEvt(EDMA0CC0_REG_BASE, channel);
    EDMA3EnableTransfer(EDMA0CC0_REG_BASE, channel, EDMA3_TRIG_MODE_EVENT);*/
    edma_start(channel);
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_start_dma_transfer()
** 功能描述: 开始DMA传输
**
** 输　入: host            ->  DM365 mmc host 句柄
**         data         ->  DMA传送数据结构句柄
**
** 输　出: DMA传输字节数
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static int mmc_dm365_start_dma_transfer(struct mmc_dm365_host *host, struct rt_mmcsd_data *data)
{
    /* set initial value */
    host->use_dma_buffer = RT_FALSE;

    if (!(data->flags & DATA_DIR_READ))
    {
        if ((rt_uint32_t)data->buf & (RT_ALIGN_SIZE - 1))
        {
            /* not align to basic size, use DMA buffer */
            host->use_dma_buffer = RT_TRUE;
            memcpy((void*)MMU_NOCACHE_ADDR(host->dma_buffer), data->buf, data->blks * data->blksize);
        }
        else
        {
            rt_uint32_t addr;
            addr = ((rt_uint32_t)data->buf & ~(CACHE_LINE_SIZE - 1));
            /* write data case, always clean DCache */
            mmu_clean_dcache(addr, (data->blks + 1)* data->blksize);
        }
    }
    else
    {
        /* whether align to cache line in read operation */
        if (((rt_uint32_t)data->buf) & (CACHE_LINE_SIZE - 1))
            host->use_dma_buffer = RT_TRUE;
        else
            mmu_invalidate_dcache((rt_uint32_t)data->buf, data->blks * data->blksize);
    }

    host->do_dma = RT_TRUE;
    mmc_dm365_send_dma_request(host, data);

    return 0;
}

#if 0
/*******************************************************************************************************
** 函数名称: acquire_dma_channels()
** 功能描述: 获取DMA channel
**
** 输　入: host            ->  DM365 mmc host 句柄
**
** 输　出: DMA 通道号
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static int acquire_dma_channels(struct mmc_dm365_host *host)
{
    int r;

    /* Acquire master DMA write channel */
    r = EDMA3RequestChannel(EDMA0CC0_REG_BASE, EDMA3_CHANNEL_TYPE_DMA, host->txdma, host->txdma, EVT_QUEUE_NUM);
    if (r < 0)
    {
        rt_kprintf("alloc %s channel err %d\n", "tx", r);
        return r;
    }
    mmc_dm365_dma_setup(host, RT_TRUE, &host->tx_template);

    /* Acquire master DMA read channel */
    r = EDMA3RequestChannel(EDMA0CC0_REG_BASE, EDMA3_CHANNEL_TYPE_DMA, host->rxdma, host->rxdma, EVT_QUEUE_NUM);
    if (r < 0)
    {
        rt_kprintf("alloc %s channel err %d\n", "rx", r);
        goto free_master_write;
    }
    mmc_dm365_dma_setup(host, RT_FALSE, &host->rx_template);

    return 0;

free_master_write:
    EDMA3FreeChannel(EDMA0CC0_REG_BASE, EDMA3_CHANNEL_TYPE_DMA, host->txdma, EDMA3_TRIG_MODE_EVENT, host->txdma, EVT_QUEUE_NUM);

    return r;
}
#endif
static int acquire_dma_channels(struct mmc_dm365_host *host)
{
    //u32 link_size;
    int r, i;

    /* Acquire master DMA write channel */
    r = edma_alloc_channel(host->txdma, mmc_dm365_dma_cb, host,
            EVENTQ_DEFAULT);
    if (r < 0) {
        mmc_dbg("alloc %s channel err %d\n",
                "tx", r);
        return r;
    }
    mmc_dm365_dma_setup(host, RT_TRUE, &host->tx_template);

    /* Acquire master DMA read channel */
    r = edma_alloc_channel(host->rxdma, mmc_dm365_dma_cb, host,
            EVENTQ_DEFAULT);
    if (r < 0) {
        mmc_dbg("alloc %s channel err %d\n",
                "rx", r);
        goto free_master_write;
    }
    mmc_dm365_dma_setup(host, RT_FALSE, &host->rx_template);

    /* Allocate parameter RAM slots, which will later be bound to a
     * channel as needed to handle a scatterlist.
     */
#if 0
    link_size = min_t(unsigned, host->nr_sg, ARRAY_SIZE(host->links));
    for (i = 0; i < link_size; i++) {
        r = edma_alloc_slot(EDMA_CTLR(host->txdma), EDMA_SLOT_ANY);
        if (r < 0) {
            mmc_dbg("dma PaRAM alloc --> %d\n",
                r);
            break;
        }
        host->links[i] = r;
    }
    host->n_link = i;
#endif

    return 0;

free_master_write:
    edma_free_channel(host->txdma);

    return r;
}


/*******************************************************************************************************
** 函数名称: mmc_dm365_prepare_data()
** 功能描述: 准备 DMA 数据
**
** 输　入: host            ->  DM365 mmc host 句柄
**         req          ->  SD request 结构句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_prepare_data(struct mmc_dm365_host *host, struct rt_mmcsd_req *req)
{
    int timeout;
    int fifo_lev;
    struct rt_mmcsd_data *data = req->data;

    fifo_lev = (rw_threshold == 64) ? MMCFIFOCTL_FIFOLEV : 0;

    host->data = data;
    if (data == RT_NULL)
    {
        host->data_dir = DM365_MMC_DATADIR_NONE;
        host->mmcsd_regs->MMCBLEN = 0;
        host->mmcsd_regs->MMCNBLK = 0;
        return;
    }

    mmc_dbg("%s %s, %d blocks of %d bytes\n",
        (data->flags & DATA_STREAM) ? "stream" : "block",
        (data->flags & DATA_DIR_WRITE) ? "write" : "read",
        data->blks, data->blksize);
    mmc_dbg("  DTO %d cycles + %d ns\n",
        data->timeout_clks, data->timeout_ns);
    timeout = data->timeout_clks + (data->timeout_ns / host->ns_in_one_cycle);
    if (timeout > 0xffff)
        timeout = 0xffff;

    host->mmcsd_regs->MMCTOD = timeout;
    host->mmcsd_regs->MMCNBLK = data->blks;
    host->mmcsd_regs->MMCBLEN = data->blksize;

    /* Configure the FIFO */
    switch (data->flags & DATA_DIR_WRITE)
    {
    case DATA_DIR_WRITE:
        host->data_dir = DM365_MMC_DATADIR_WRITE;
        host->mmcsd_regs->MMCFIFOCTL = fifo_lev | MMCFIFOCTL_FIFODIR_WR | MMCFIFOCTL_FIFORST;
        host->mmcsd_regs->MMCFIFOCTL = fifo_lev | MMCFIFOCTL_FIFODIR_WR;
        break;

    default:
        host->data_dir = DM365_MMC_DATADIR_READ;
        host->mmcsd_regs->MMCFIFOCTL = fifo_lev | MMCFIFOCTL_FIFODIR_RD | MMCFIFOCTL_FIFORST;
        host->mmcsd_regs->MMCFIFOCTL = fifo_lev | MMCFIFOCTL_FIFODIR_RD;
        break;
    }

    host->buffer = RT_NULL;
    host->bytes_left = data->blks * data->blksize;

    /* For now we try to use DMA whenever we won't need partial FIFO
     * reads or writes, either for the whole transfer (as tested here)
     * or for any individual scatterlist segment (tested when we call
     * start_dma_transfer).
     *
     * While we *could* change that, unusual block sizes are rarely
     * used.  The occasional fallback to PIO should't hurt.
     */
    if ((host->use_dma == RT_TRUE) && (host->bytes_left & (rw_threshold - 1)) == 0 &&
            mmc_dm365_start_dma_transfer(host, data) == 0)
    {
        /* zero this to ensure we take no PIO paths */
        host->bytes_left = 0;
    }
    else
    {
        /* Revert to CPU Copy */
        host->buffer = (rt_uint8_t*)req->data->buf;
    }
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_request()
** 功能描述: 此函数实现SD request操作
**
** 输　入: host            ->  DM365 mmc host 句柄
**         req          ->  SD request 结构句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_request(struct rt_mmcsd_host *mmc, struct rt_mmcsd_req *req)
{
    struct mmc_dm365_host *host = mmc_priv(mmc);
    unsigned long timeout = rt_tick_get() + 900;
    rt_uint32_t mmcst1 = 0;

    /* Card may still be sending BUSY after a previous operation,
     * typically some kind of write.  If so, we can't proceed yet.
     */
    while (rt_tick_get() < timeout)
    {
        mmcst1  = host->mmcsd_regs->MMCST1;
        if (!(mmcst1 & MMCST1_BUSY))
            break;
    }
    if (mmcst1 & MMCST1_BUSY)
    {
        mmc_dbg("still BUSY? bad ... \n");
        req->cmd->err = -RT_ETIMEOUT;
        mmc_request_done(mmc, req);
        return;
    }

    host->do_dma = RT_FALSE;
    mmc_dm365_prepare_data(host, req);
    mmc_dm365_start_command(host, req->cmd);
}

static void mmc_dm365_enable_sdio_irq(struct rt_mmcsd_host *mmc, rt_int32_t enable)
{
    struct mmc_dm365_host *host = mmc_priv(mmc);

    if (enable)
    {
        if (!(host->mmcsd_regs->SDIOST0 & SDIOST0_DAT1_HI))
        {
            host->mmcsd_regs->SDIOIST = SDIOIST_IOINT;
            sdio_irq_wakeup(host->mmc);
        }
        else
        {
            host->sdio_int = RT_TRUE;
            host->mmcsd_regs->SDIOIEN |= SDIOIEN_IOINTEN;
        }
    }
    else
    {
        host->sdio_int = RT_FALSE;
        host->mmcsd_regs->SDIOIEN &= ~SDIOIEN_IOINTEN;
    }
}


static const struct rt_mmcsd_host_ops mmc_dm365_ops =
{
    mmc_dm365_request,
    mmc_dm365_set_ios,
    RT_NULL,
    mmc_dm365_enable_sdio_irq
};

/*******************************************************************************************************
** 函数名称: mmc_dm365_reset_ctrl()
** 功能描述: 此函数用于reset mmc控制器
**
** 输　入: host            ->  DM365 mmc host 句柄
**         val          ->  判断做reset还是enable
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_reset_ctrl(struct mmc_dm365_host *host, int val)
{
    rt_uint32_t temp;

    temp = host->mmcsd_regs->MMCCTL;

    if (val)    /* reset */
        temp |= MMCCTL_CMDRST | MMCCTL_DATRST;
    else        /* enable */
        temp &= ~(MMCCTL_CMDRST | MMCCTL_DATRST);

    host->mmcsd_regs->MMCCTL = temp;

    delay_us(10);
}

/*******************************************************************************************************
** 函数名称: init_mmcsd_host()
** 功能描述: 此函数用于初始化DM365 MMCSD控制器
**
** 输　入: host            ->  DM365 mmc host 句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void init_mmcsd_host(struct mmc_dm365_host *host)
{
    mmc_dm365_reset_ctrl(host, 1);

    host->mmcsd_regs->MMCCLK = 0;
    host->mmcsd_regs->MMCCLK = MMCCLK_CLKEN;

    host->mmcsd_regs->MMCTOR = 0x1FFF;
    host->mmcsd_regs->MMCTOD = 0xFFFF;

    mmc_dm365_reset_ctrl(host, 0);
}

/*******************************************************************************************************
** 函数名称: mmc_dm365_cmd_done()
** 功能描述: 结束SD 命令后调用此函数
**
** 输　入: host            ->  DM365 mmc host 句柄
**         cmd          ->  SD 命令结构句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_cmd_done(struct mmc_dm365_host *host, struct rt_mmcsd_cmd *cmd)
{
    host->cmd = RT_NULL;

    if (resp_type(cmd) != RESP_NONE)
    {
        if (resp_type(cmd) == RESP_R2)
        {
            /* response type 2 */
            cmd->resp[3] = host->mmcsd_regs->MMCRSP01;
            cmd->resp[2] = host->mmcsd_regs->MMCRSP23;
            cmd->resp[1] = host->mmcsd_regs->MMCRSP45;
            cmd->resp[0] = host->mmcsd_regs->MMCRSP67;
        }
        else
        {
            /* response types 1, 1b, 3, 4, 5, 6 */
            cmd->resp[0] = host->mmcsd_regs->MMCRSP67;
        }
    }

    if (host->data == RT_NULL || cmd->err)
    {
        if (cmd->err == -RT_ETIMEOUT)
            cmd->mrq->cmd->retries = 0;
        mmc_request_done(host->mmc, cmd->mrq);
        host->mmcsd_regs->MMCIM = 0;
    }
}

/*******************************************************************************************************
** 函数名称: dm365_abort_data()
** 功能描述: 此函数用于终止数据传输
**
** 输　入: host            ->  DM365 mmc host 句柄
**         data         ->  data 结构句柄
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void dm365_abort_data(struct mmc_dm365_host *host, struct rt_mmcsd_data *data)
{
    mmc_dm365_reset_ctrl(host, 1);
    mmc_dm365_reset_ctrl(host, 0);
}

static void mmc_dm365_sdio_irq(int irq, void *param)
{
    struct mmc_dm365_host *host = (struct mmc_dm365_host *)param;
    rt_uint32_t status;

    status = host->mmcsd_regs->SDIOIST;//readl(host->base + DAVINCI_SDIOIST);
    if (status & SDIOIST_IOINT) {
        mmc_dbg("SDIO interrupt status %x\n", status);
        //writel(status | SDIOIST_IOINT, host->base + DAVINCI_SDIOIST);
        host->mmcsd_regs->SDIOIST = status | SDIOIST_IOINT;
        sdio_irq_wakeup(host->mmc);
    }
}


/*******************************************************************************************************
** 函数名称: mmc_dm365_irq()
** 功能描述: MMCSD的中断处理程序
**
** 输　入: irq ->中断向量号
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void mmc_dm365_irq(int irq, void *param)
{
    struct mmc_dm365_host *host = (struct mmc_dm365_host *)param;
    rt_uint32_t status, qstatus;
    int end_command = 0;
    int end_transfer = 0;
    struct rt_mmcsd_data *data = host->data;

    if (host->cmd == RT_NULL && host->data == RT_NULL)
    {
        status = host->mmcsd_regs->MMCST0;
        mmc_dbg("Spurious interrupt 0x%04x\n", status);
        /* Disable the interrupt from mmcsd */
        host->mmcsd_regs->MMCIM = 0;
        return;
    }

    status = host->mmcsd_regs->MMCST0;
    qstatus = status;

    /* handle FIFO first when using PIO for data.
     * bytes_left will decrease to zero as I/O progress and status will
     * read zero over iteration because this controller status
     * register(MMCST0) reports any status only once and it is cleared
     * by read. So, it is not unbouned loop even in the case of
     * non-dma.
     */
    while (host->bytes_left && (status & (MMCST0_DXRDY | MMCST0_DRRDY)))
    {
        dm365_fifo_data_trans(host, rw_threshold);
        status = host->mmcsd_regs->MMCST0;
        if (!status)
            break;
        qstatus |= status;
    }

    if (qstatus & MMCST0_DATDNE)
    {
        /* All blocks sent/received, and CRC checks passed */
        if (data != RT_NULL)
        {
            if ((host->do_dma == RT_FALSE) && (host->bytes_left > 0))
            {
                /* if datasize < rw_threshold
                 * no RX ints are generated
                 */
                rt_kprintf("to do! host->bytes_left=0x%x\n", host->bytes_left);
                dm365_fifo_data_trans(host, host->bytes_left);
            }
            end_transfer = 1;
            data->bytes_xfered = data->blks* data->blksize;
        }
        else
        {
            mmc_dbg("DATDNE with no host->data\n");
        }
    }

    if (qstatus & MMCST0_TOUTRD)
    {
        /* Read data timeout */
        data->err = -RT_ETIMEOUT;
        end_transfer = 1;

        mmc_dbg("read data timeout, status %x\n", qstatus);
        rt_kprintf("read data timeout, status %x\n", qstatus);

        dm365_abort_data(host, data);
    }

    if (qstatus & (MMCST0_CRCWR | MMCST0_CRCRD))
    {
        /* Data CRC error */
        data->err = -RT_ERROR;
        end_transfer = 1;

        /* NOTE:  this controller uses CRCWR to report both CRC
         * errors and timeouts (on writes).  MMCDRSP values are
         * only weakly documented, but 0x9f was clearly a timeout
         * case and the two three-bit patterns in various SD specs
         * (101, 010) aren't part of it ...
         */
        if (qstatus & MMCST0_CRCWR)
        {
            rt_uint32_t temp = host->mmcsd_regs->MMCDRSP;

            if (temp == 0x9f)
                data->err = -RT_ETIMEOUT;
        }
        mmc_dbg("data %s %s error\n", (qstatus & MMCST0_CRCWR) ? "write" : "read", (data->err == -110) ? "timeout" : "CRC");

        rt_kprintf("data %s %s error\n", (qstatus & MMCST0_CRCWR) ? "write" : "read", (data->err == -110) ? "timeout" : "CRC");

        dm365_abort_data(host, data);
    }

    if (qstatus & MMCST0_TOUTRS)
    {
        /* Command timeout */
        if (host->cmd)
        {
            mmc_dbg("CMD%d timeout, status %x\n", host->cmd->cmd_code, qstatus);
            host->cmd->err = -RT_ETIMEOUT;
            if (data)
            {
                end_transfer = 1;
                dm365_abort_data(host, data);
            }
            else
                end_command = 1;
        }
    }

    if (qstatus & MMCST0_CRCRS)
    {
        /* Command CRC error */
        mmc_dbg("Command CRC error\n");
        if (host->cmd)
        {
            host->cmd->err = -RT_ERROR;
            end_command = 1;
        }
    }

    if (qstatus & MMCST0_RSPDNE)
    {
        /* End of command phase */
        end_command = (int) host->cmd;
    }

    if (end_command)
        mmc_dm365_cmd_done(host, host->cmd);
    if (end_transfer)
        mmc_dm365_xfer_done(host, data);

    return;
}
#if 0

/*******************************************************************************************************
** 函数名称: rt_hw_edma_init()
** 功能描述: 此函数用于初始化EDMA3
**
** 输　入: 无
**
** 输　出: 无
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
static void rt_hw_edma_init(void)
{
    psc_transition(PSC0, DOMAIN0, LPSC_TPCC, PSC_ENABLE);
    psc_transition(PSC0, DOMAIN0, LPSC_TPTC0, PSC_ENABLE);

    /* Initialization of EDMA3 */
    edma3_init(EDMA0CC0_REG_BASE, EVT_QUEUE_NUM);

    /* Register EDMA3 Interrupts */
//  ConfigureAINTCIntEDMA3();
}
#endif
/*******************************************************************************************************
** 函数名称: rt_hw_mmcsd_init()
** 功能描述: 此函数用于初始化MMC驱动模块
**
** 输　入: 无
**
** 输　出: 如果初始化成功，返回0；如果初始化失败，返回-RT_ENOMEM
**
** 全局变量:
** 调用模块: 无
**
********************************************************************************************************/
int rt_hw_mmcsd_init(void)
{
    struct clk  *clk;
    struct mmc_dm365_host *dm365_host;
    struct rt_mmcsd_host *mmc = RT_NULL;

    mmc = mmcsd_alloc_host();
    if (!mmc)
    {
        mmc_dbg("alloc mmc failed\n");
        return -RT_ERROR;
    }

    dm365_host = rt_malloc(sizeof(struct mmc_dm365_host));
    if (!dm365_host)
    {
        mmc_dbg("alloc mci failed\n");
        goto err;
    }

    rt_memset(dm365_host, 0, sizeof(struct mmc_dm365_host));

#ifdef RT_USING_MMCSD0
    //psc_transition(PSC0, DOMAIN0, LPSC_MMCSD0, PSC_ENABLE);
    //pinmux_config(PINMUX_MMCSD0_REG, PINMUX_MMCSD0_MASK, PINMUX_MMCSD0_VAL);
    psc_change_state(DAVINCI_DM365_LPSC_MMC_SD0, PSC_ENABLE);
    dm365_host->mmcsd_regs = (mmcsd_regs_t *)DM365_MMC_SD0_BASE;
#else
#ifdef RT_USING_MMCSD1
    psc_transition(PSC1, DOMAIN0, LPSC_MMCSD1, PSC_ENABLE);
    pinmux_config(PINMUX_MMCSD1_REG, PINMUX_MMCSD1_MASK, PINMUX_MMCSD1_VAL);
    dm365_host->mmcsd_regs = MMCSD1;
#endif
#endif

    //rt_hw_edma_init();

    clk = clk_get("MMCSDCLK0");
    dm365_host->mmc_input_clk = clk_get_rate(clk);
    dm365_host->rxdma = DM365_DMA_MMC0RXEVT;
    dm365_host->txdma = DM365_DMA_MMC0TXEVT;
    dm365_host->use_dma = use_dma;
    if ((dm365_host->use_dma == RT_TRUE)&& acquire_dma_channels(dm365_host) != 0)
    {
        dm365_host->use_dma = RT_FALSE;
    }
    else
    {
        dm365_host->dma_buffer = (rt_uint8_t*)rt_malloc_align(64*1024, 32);
        if (dm365_host->dma_buffer == RT_NULL)
            dm365_host->use_dma = RT_FALSE;
    }

    mmc->ops = &mmc_dm365_ops;
    mmc->freq_min = 312500;
    mmc->freq_max = 25000000;
    mmc->valid_ocr = VDD_32_33 | VDD_33_34;
    mmc->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE;
    mmc->flags |= MMCSD_SUP_SDIO_IRQ;

    dm365_host->mmc = mmc;
    mmc->private_data = dm365_host;

    /* install interrupt */
#ifdef RT_USING_MMCSD0
    rt_hw_interrupt_install(IRQ_DM3XX_MMCINT0, mmc_dm365_irq,
                            (void *)dm365_host, "MMC0");
    rt_hw_interrupt_umask(IRQ_DM3XX_MMCINT0);
    rt_hw_interrupt_install(IRQ_DM3XX_SDIOINT0, mmc_dm365_sdio_irq,
                            (void *)dm365_host, "SDIO0");
    rt_hw_interrupt_umask(IRQ_DM3XX_SDIOINT0);
#endif
#ifdef RT_USING_MMCSD1
    rt_hw_interrupt_install(MMCSD_INT1, mmc_dm365_irq,
                            (void *)dm365_host, "MMC1");
    rt_hw_interrupt_umask(MMCSD_INT1);
#endif

    init_mmcsd_host(dm365_host);

    mmcsd_change(mmc);

    return 0;

err:
    mmcsd_free_host(mmc);

    return -RT_ENOMEM;
}

INIT_DEVICE_EXPORT(rt_hw_mmcsd_init);

