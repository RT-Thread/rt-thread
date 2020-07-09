/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-09     aozima       the first version
 * 2013-03-29     aozima       support JZ4770.
 * 2013-04-01     aozima       add interrupt support for JZ4770.
 * 2019-04-04     Jean-Luc     fix bug in jzmmc_submit_dma.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/mmcsd_core.h>
#include <drivers/sdio.h>

#include "board.h"
#include "drv_gpio.h"
#include "drv_clock.h"
#include "drv_mmc.h"

#include <cache.h>
#include <string.h>

#define DMA_BUFFER
#define DMA_ALIGN       (32U)
#define PIO_THRESHOLD       64  /* use pio mode if data length < PIO_THRESHOLD */

#define DBG_TAG  "SDIO"
#define DBG_LVL  DBG_INFO
#include <rtdbg.h>

/*
 * Error status including CRC_READ_ERROR, CRC_WRITE_ERROR,
 * CRC_RES_ERR, TIME_OUT_RES, TIME_OUT_READ
 */
#define ERROR_STAT          0x3f

#define JZMMC_USE_PIO       2

/* Register access macros */
#define msc_readl(host,reg)                     \
    readl((host)->hw_base + reg)
#define msc_writel(host,reg,value)              \
    writel((value), (host)->hw_base + (reg))

#define is_pio_mode(host)                       \
    (host->flags & (1 << JZMMC_USE_PIO))
#define enable_pio_mode(host)                   \
    (host->flags |= (1 << JZMMC_USE_PIO))
#define disable_pio_mode(host)                  \
    (host->flags &= ~(1 << JZMMC_USE_PIO))

/*-------------------End structure and macro define------------------------*/

#ifdef DMA_BUFFER
ALIGN(32)
uint8_t _dma_buffer_0[32 * 1024];
ALIGN(32)
uint8_t _dma_buffer_1[32 * 1024];
#endif

struct jzmmc_host *jz_host1 = RT_NULL;
volatile static int stopping_clock = 0;
volatile static int sdio_log = 0;

/*
 * Functional functions.
 *
 * These small function will be called frequently.
 */
rt_inline void enable_msc_irq(struct jzmmc_host *host, unsigned long bits)
{
    unsigned long imsk;

    imsk = msc_readl(host, MSC_IMASK_OFFSET);
    imsk &= ~bits;
    msc_writel(host, MSC_IMASK_OFFSET, imsk);
}

rt_inline void clear_msc_irq(struct jzmmc_host *host, unsigned long bits)
{
    msc_writel(host, MSC_IREG_OFFSET, bits);
}

rt_inline void disable_msc_irq(struct jzmmc_host *host, unsigned long bits)
{
    unsigned long imsk;

    imsk = msc_readl(host, MSC_IMASK_OFFSET);
    imsk |= bits;
    msc_writel(host, MSC_IMASK_OFFSET, imsk);
}

static inline int check_error_status(struct jzmmc_host *host, unsigned int status)
{
    if (status & ERROR_STAT)
    {
        LOG_D("Error status->0x%08X: cmd=%d", status, host->cmd->cmd_code);
        return -1;
    }
    return 0;
}

/* Stop the MMC clock and wait while it happens */
rt_inline rt_err_t jzmmc_stop_clock(uint32_t hw_base)
{
    uint16_t value;
    int timeout = 10000;

    stopping_clock = 1;

    value = readw(hw_base + MSC_CTRL_OFFSET);
    value &= ~MSC_CTRL_CLOCK_CONTROL_MASK;
    value |= MSC_CTRL_CLOCK_STOP;
    writew(value, hw_base + MSC_CTRL_OFFSET);

    while (timeout && (readl(hw_base + MSC_STAT_OFFSET) & MSC_STAT_CLK_EN))
    {
        timeout--;
        if (timeout == 0)
        {
            rt_kprintf("stop clock timeout!\n");
            stopping_clock = 0;
            return -RT_ETIMEOUT;
        }
        rt_thread_delay(1);
    }

    stopping_clock = 0;
    return RT_EOK;
}

/* Start the MMC clock and operation */
rt_inline void jzmmc_start_clock(uint32_t hw_base)
{
    uint16_t value;
    value = readw(hw_base + MSC_CTRL_OFFSET);
    value |= (MSC_CTRL_CLOCK_START | MSC_CTRL_START_OP);
    writew(value, hw_base + MSC_CTRL_OFFSET);
}

static int jzmmc_polling_status(struct jzmmc_host *host, unsigned int status)
{
    unsigned int cnt = 100 * 1000 * 1000;

    while(!(msc_readl(host, MSC_STAT_OFFSET) & (status | ERROR_STAT))   \
          && (--cnt));

    if (!cnt)
    {
        LOG_D("polling status(0x%08X) time out, "
            "op=%d, status=0x%08X", status,
            host->cmd->cmd_code, msc_readl(host, MSC_STAT_OFFSET));
        return -1;
    }

    if (msc_readl(host, MSC_STAT_OFFSET) & ERROR_STAT)
    {
        LOG_D("polling status(0x%08X) error, "
            "op=%d, status=0x%08X", status,
            host->cmd->cmd_code, msc_readl(host, MSC_STAT_OFFSET));
        return -1;
    }

    return 0;
}

rt_inline void jzmmc_stop_dma(struct jzmmc_host *host)
{
    /*
     * Theoretically, DMA can't be stopped when transfering, so we can only
     * diable it when it is out of DMA request.
     */
    msc_writel(host, MSC_DMAC_OFFSET, 0);
}

static void jzmmc_command_done(struct jzmmc_host *host, struct rt_mmcsd_cmd *cmd)
{
    int i;
    unsigned long res;

    uint8_t buf[16];
    uint32_t data;

    memset(cmd->resp, 0x0, sizeof(cmd->resp));

    if ((host->cmdat & MSC_CMDAT_RESP_FORMAT_MASK) == MSC_CMDAT_RESPONSE_R2)
    {
        res = msc_readl(host, MSC_RES_OFFSET);
        for (i = 0 ; i < 4 ; i++) {
            cmd->resp[i] = res << 24;
            res = msc_readl(host, MSC_RES_OFFSET);
            cmd->resp[i] |= res << 8;
            res = msc_readl(host, MSC_RES_OFFSET);
            cmd->resp[i] |= res >> 8;
        }
    }
    else if ((host->cmdat & MSC_CMDAT_RESP_FORMAT_MASK) == MSC_CMDAT_RESPONSE_NONE)
    {
    }
    else
    {
        res = msc_readl(host, MSC_RES_OFFSET);
        cmd->resp[0] = res << 24;
        res = msc_readl(host, MSC_RES_OFFSET);
        cmd->resp[0] |= res << 8;
        res = msc_readl(host, MSC_RES_OFFSET);
        cmd->resp[0] |= res & 0xff;
    }

    LOG_D("error:%d cmd->resp [%08X, %08X, %08X, %08X]\r\n\r",
             cmd->err,
             cmd->resp[0],
             cmd->resp[1],
             cmd->resp[2],
             cmd->resp[3]
            );

    clear_msc_irq(host, IFLG_END_CMD_RES);
}

static void jzmmc_data_done(struct jzmmc_host *host)
{
    struct rt_mmcsd_data *data = host->data;

    if (host->cmd->err == RT_EOK)
    {
        data->bytes_xfered = (data->blks * data->blksize);
        jzmmc_stop_dma(host);
    }
    else
    {
        jzmmc_stop_dma(host);
        data->bytes_xfered = 0;
        LOG_D("error when request done");
    }
}

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;

    for (i=0; i<buflen; i+=16)
    {
        rt_kprintf("%08X: ", i);

        for (j=0; j<16; j++)
            if (i+j < buflen)
                rt_kprintf("%02X ", buf[i+j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j=0; j<16; j++)
            if (i+j < buflen)
                rt_kprintf("%c", __is_print(buf[i+j]) ? buf[i+j] : '.');
        rt_kprintf("\n");
    }
}

/*------------------------End functional functions-------------------------*/

rt_inline void jzmmc_submit_dma(struct jzmmc_host *host, struct rt_mmcsd_data *data)
{
    host->dma_desc.nda  = 0;
    host->dma_desc.len  = data->blks * data->blksize;
    host->dma_desc.da   = virt_to_phys(data->buf);
    host->dma_desc.dcmd = DMACMD_ENDI; /* only one DMA descriptor */

#ifdef DMA_BUFFER
    if ((uint32_t)(data->buf) & (DMA_ALIGN - 1))
    {
        /* not align */
        host->dma_desc.da   = virt_to_phys(host->_dma_buffer);
        if (data->flags & DATA_DIR_WRITE)
        {
            LOG_D("%d ->", data->blks * data->blksize);
            memcpy(host->_dma_buffer, data->buf, data->blks * data->blksize);
            rt_hw_dcache_flush_range((rt_ubase_t)(host->_dma_buffer), data->blks * data->blksize);

            LOG_D("| 0x%08x", data->buf);
        }
    }
    else
    {
        if (data->flags & DATA_DIR_WRITE)
        {
            rt_hw_dcache_flush_range((rt_ubase_t)(data->buf), data->blks * data->blksize);
        }
    }
#endif
    
}

// #define PERFORMANCE_DMA
rt_inline void jzmmc_dma_start(struct jzmmc_host *host, struct rt_mmcsd_data *data)
{
    volatile int i = 120;
    uint32_t dma_addr = virt_to_phys(data->buf);
    unsigned int dma_len = data->blks * data->blksize;
    unsigned int dmac;
#ifdef PERFORMANCE_DMA
    dmac = (0x01 << DMAC_INCR_SHF) | DMAC_DMAEN | DMAC_MODE_SEL;
#else
    dmac = (0x01 << DMAC_INCR_SHF) | DMAC_DMAEN;
#endif

#ifndef DMA_BUFFER
    if ((dma_addr & (DMA_ALIGN - 1)) || (dma_len & (DMA_ALIGN - 1)))
    {
        LOG_D("DMA align, addr=0x%08x", dma_addr);
        dmac |= DMAC_ALIGNEN;
        if (dma_addr & (DMA_ALIGN - 1))
        {
            dmac |= (dma_addr & (DMA_ALIGN - 1)) << DMAC_AOFST_SHF;
        }
    }
#endif
    LOG_D("DMA start: nda 0x%08x, da 0x%08x, len 0x%04x, cmd 0x%08x", virt_to_phys(&(host->dma_desc)),
        host->dma_desc.da, host->dma_desc.len, host->dma_desc.dcmd);
     
    rt_hw_dcache_flush_range((rt_ubase_t)(&(host->dma_desc)), 32);
    while(i--);  //TODO:短暂延时,不延时会发生错误   
    msc_writel(host, MSC_DMANDA_OFFSET, virt_to_phys(&(host->dma_desc)));
    msc_writel(host, MSC_DMAC_OFFSET, dmac);
}

/*----------------------------End DMA handler------------------------------*/

/*
 * PIO transfer mode.
 *
 * Functions of PIO read/write mode that can handle 1, 2 or 3 bytes transfer
 * even though the FIFO register is 32-bits width.
 * It's better just used for test.
 */
static int wait_cmd_response(struct jzmmc_host *host)
{
    if (!(msc_readl(host, MSC_IREG_OFFSET) & IFLG_END_CMD_RES))
    {
        rt_err_t ret;

        rt_completion_init(&host->completion);

        enable_msc_irq(host, IMASK_TIME_OUT_RES | IMASK_END_CMD_RES);

        rt_hw_interrupt_umask(host->irqno);
        ret = rt_completion_wait(&host->completion, RT_TICK_PER_SECOND);

        clear_msc_irq(host, IFLG_TIMEOUT_RES | IFLG_END_CMD_RES);
        disable_msc_irq(host, IFLG_TIMEOUT_RES | IFLG_END_CMD_RES);

        if(ret == RT_EOK)
        {
            LOG_D("wait response OK!\r");
        }
        else
        {
            uint32_t value;

            value = msc_readl(host, MSC_STAT_OFFSET);
            LOG_D("stat=0x%08x", value);
            value = msc_readl(host, MSC_IREG_OFFSET);
            LOG_D("iflag=0x%08x", value);

            host->cmd->err = ret;
            LOG_D("wait END_CMD_RES timeout[uncompletion]\r");

            return -1;
        }
    }

    msc_writel(host, MSC_IREG_OFFSET, IFLG_END_CMD_RES);
    return 0;
}

static void do_pio_read(struct jzmmc_host *host,
            unsigned int *addr, unsigned int cnt)
{
    int i = 0;
    unsigned int status = 0;

    for (i = 0; i < cnt / 4; i++)
    {
        while (((status = msc_readl(host, MSC_STAT_OFFSET))
            & MSC_STAT_DATA_FIFO_EMPTY));

        if (check_error_status(host, status))
        {
            host->cmd->err = -RT_EIO;
            return;
        }
        *addr++ = msc_readl(host, MSC_RXFIFO_OFFSET);
    }

    /*
     * These codes handle the last 1, 2 or 3 bytes transfer.
     */
    if (cnt & 3)
    {
        uint32_t n = cnt & 3;
        uint32_t data = msc_readl(host, MSC_RXFIFO_OFFSET);
        uint8_t  *p = (u8 *)addr;

        while (n--)
        {
            *p++ = data;
            data >>= 8;
        }
    }
}

static void do_pio_write(struct jzmmc_host *host,
             unsigned int *addr, unsigned int cnt)
{
    int i = 0;
    unsigned int status = 0;

    for (i = 0; i < (cnt / 4); i++)
    {
        while (((status = msc_readl(host, MSC_STAT_OFFSET))
            & MSC_STAT_DATA_FIFO_FULL));

        if (check_error_status(host, status))
        {
            host->cmd->err = -RT_EIO;
            return;
        }
        msc_writel(host, MSC_TXFIFO_OFFSET, *addr++);
    }

    /*
     * These codes handle the last 1, 2 or 3 bytes transfer.
     */
    if (cnt & 3)
    {
        uint32_t data = 0;
        uint8_t *p = (uint8_t *)addr;

        for (i = 0; i < (cnt & 3); i++)
            data |= *p++ << (8 * i);

        msc_writel(host, MSC_TXFIFO_OFFSET, data);
    }
}

static inline void pio_trans_start(struct jzmmc_host *host, struct rt_mmcsd_data *data)
{
    unsigned int *addr = (unsigned int *)data->buf;
    unsigned int cnt = data->blks * data->blksize;

    if (data->flags & DATA_DIR_WRITE)
        do_pio_write(host, addr, cnt);
    else
        do_pio_read(host, addr, cnt);
}

static void pio_trans_done(struct jzmmc_host *host, struct rt_mmcsd_data *data)
{
    if (host->cmd->err == RT_EOK)
        data->bytes_xfered = data->blks * data->blksize;
    else
        data->bytes_xfered = 0;

    if (host->req->stop)
    {
        if (jzmmc_polling_status(host, MSC_STAT_AUTO_CMD_DONE) < 0)
            host->cmd->err = -RT_EIO;
    }

    if (data->flags & DATA_DIR_WRITE)
    {
        if (jzmmc_polling_status(host, MSC_STAT_PRG_DONE) < 0)
        {
            host->cmd->err  = -RT_EIO;
        }
        clear_msc_irq(host, IFLG_PRG_DONE);
    }
    else
    {
        if (jzmmc_polling_status(host, MSC_STAT_DATA_TRAN_DONE) < 0)
        {
            host->cmd->err  = -RT_EIO;
        }
        clear_msc_irq(host, IFLG_DATA_TRAN_DONE);
    }
}

/*-------------------------End PIO transfer mode---------------------------*/

/*
 * Achieve mmc_request here.
 */
static void jzmmc_data_pre(struct jzmmc_host *host, struct rt_mmcsd_data *data)
{
    unsigned int nob = data->blks;
    unsigned long cmdat,imsk;

    msc_writel(host, MSC_RDTO_OFFSET, 0xffffff);
    msc_writel(host, MSC_NOB_OFFSET, nob);
    msc_writel(host, MSC_BLKLEN_OFFSET, data->blksize);
    cmdat = MSC_CMDAT_DATA_EN;

    msc_writel(host, MSC_CMDAT_OFFSET, MSC_CMDAT_DATA_EN);

    if (data->flags & DATA_DIR_WRITE)
    {
        cmdat |= MSC_CMDAT_WRITE;
        imsk = IMASK_WR_ALL_DONE | IMASK_CRC_WRITE_ERR;
    }
    else if (data->flags & DATA_DIR_READ)
    {
        cmdat &= ~MSC_CMDAT_WRITE;
        imsk = IMASK_DMA_DATA_DONE | IMASK_TIME_OUT_READ | IMASK_CRC_READ_ERR;
    }
    else
    {
        rt_kprintf("data direction confused\n");
    }

    host->cmdat |= cmdat;

    if (!is_pio_mode(host))
    {
        jzmmc_submit_dma(host, data);
        clear_msc_irq(host, IFLG_PRG_DONE);
        enable_msc_irq(host, imsk);
    }
}

static void jzmmc_data_start(struct jzmmc_host *host, struct rt_mmcsd_data *data)
{
    if (is_pio_mode(host))
    {
        pio_trans_start(host, data);
        pio_trans_done(host, data);

        disable_pio_mode(host);
    }
    else
    {
        rt_err_t ret;

        rt_completion_init(&host->completion);

        /* start DMA */
        disable_msc_irq(host, IFLG_END_CMD_RES);
        jzmmc_dma_start(host, data);

        rt_hw_interrupt_umask(host->irqno);
        ret = rt_completion_wait(&host->completion, RT_TICK_PER_SECOND);

        if (ret != RT_EOK)
        {
            rt_kprintf("warning: msc dma timeout\n");
        }
        else
        {
            LOG_D("msc status: 0x%08x", msc_readl(host, MSC_STAT_OFFSET));

            clear_msc_irq(host, IFLG_DATA_TRAN_DONE | IFLG_DMAEND | IFLG_DMA_DATA_DONE | IFLG_TIMEOUT_RES);
            disable_msc_irq(host, IMASK_DMA_DATA_DONE | IMASK_CRC_READ_ERR);

#ifdef DMA_BUFFER
            if ((data->flags & DATA_DIR_READ))
            {
                if((uint32_t)data->buf & (DMA_ALIGN - 1))
                {
                    rt_hw_dcache_invalidate_range((rt_ubase_t)(host->_dma_buffer), data->blks * data->blksize);
                    memcpy(data->buf, host->_dma_buffer, data->blks * data->blksize);
                    LOG_D("0x%08x <-| %d", data->buf, data->blks * data->blksize);
                }
                else
                {
                    rt_hw_dcache_invalidate_range((rt_ubase_t)(data->buf), data->blks * data->blksize);
                }
                
            }
#endif
        }

        jzmmc_data_done(host);
    }
}

static void jzmmc_command_start(struct jzmmc_host *host, struct rt_mmcsd_cmd *cmd)
{
    unsigned long cmdat = 0;
    unsigned long imsk;

    /* auto send stop */
    if (host->req->stop) cmdat |= MSC_CMDAT_SEND_AS_STOP;

    /* handle response type */
    switch (cmd->flags & RESP_MASK)
    {
#define _CASE(S,D) case RESP_##S: cmdat |= MSC_CMDAT_RESPONSE_##D; break
        _CASE(R1, R1);  /* r1 */
        _CASE(R2, R2);
        _CASE(R3, R3);  /* r3 */
        _CASE(R4, R4);  /* r4 */
        _CASE(R5, R5);
        _CASE(R6, R6);
        _CASE(R7, R7);
    default:
        break;
#undef _CASE
    }
    if ((cmd->flags & RESP_MASK) == RESP_R1B) cmdat |= MSC_CMDAT_BUSY;

    host->cmdat |= cmdat;

    if (!is_pio_mode(host))
    {
        imsk = IMASK_TIME_OUT_RES | IMASK_END_CMD_RES;
        enable_msc_irq(host, imsk);
    }

    LOG_D("dat: 0x%08x", host->cmdat);
    LOG_D("resp type: %d", cmd->flags & RESP_MASK);

    writel(0xFF, host->hw_base + MSC_RESTO_OFFSET);
    writel(0xFFFFFFFF, host->hw_base + MSC_RDTO_OFFSET);

    msc_writel(host, MSC_CMD_OFFSET, cmd->cmd_code);
    msc_writel(host, MSC_ARG_OFFSET, cmd->arg);
    msc_writel(host, MSC_CMDAT_OFFSET, host->cmdat);
    msc_writel(host, MSC_CTRL_OFFSET, MSC_CTRL_START_OP);

    jzmmc_start_clock(host->hw_base);
    cmd->err = RT_EOK;

    if (is_pio_mode(host))
    {
        wait_cmd_response(host);
        jzmmc_command_done(host, host->cmd);
    }
}

static void jzmmc_sdio_request(struct rt_mmcsd_host *mmc, struct rt_mmcsd_req *req)
{
    struct jzmmc_host *host = mmc->private_data;
    char direction = '\0';

    host->req   = req;
    host->data  = req->data;
    host->cmd   = req->cmd;
    host->cmdat = 0;

    LOG_D("CMD: %d ARG: %08X", req->cmd->cmd_code, req->cmd->arg);
    if (host->data)
    {
        direction = (host->data->flags & DATA_DIR_WRITE)? 'w' : 'r';
    }

    jzmmc_stop_clock(host->hw_base);

    /* disable pio mode firstly */
    disable_pio_mode(host);

    /* clear status */
    writew(0xFFFF, host->hw_base + MSC_IREG_OFFSET);
    disable_msc_irq(host, 0xffffffff);

    if (host->flags & MSC_CMDAT_BUS_WIDTH_4BIT)
    {
        host->cmdat |= MSC_CMDAT_BUS_WIDTH_4BIT;
    }

    if(req->cmd->cmd_code == GO_IDLE_STATE)
    {
        host->cmdat |= MSC_CMDAT_INIT;
    }

    if(host->data)
    {
        LOG_D("with data, datalen = %d", host->data->blksize * host->data->blks);
        if (host->data->blksize * host->data->blks < PIO_THRESHOLD)
        {
            LOG_D(" pio mode!");
            enable_pio_mode(host);
        }

        jzmmc_data_pre(host, host->data);
    }
    else
    {
        writew(0, host->hw_base + MSC_BLKLEN_OFFSET);
        writew(0, host->hw_base + MSC_NOB_OFFSET);

        enable_pio_mode(host);
    }

    jzmmc_command_start(host, host->cmd);
    if (host->data)
    {
        jzmmc_data_start(host, host->data);
    }

    mmcsd_req_complete(mmc);
}

static void jzmmc_isr(int irqno, void* param)
{
    uint32_t pending;
    uint32_t pending_;
    
    struct jzmmc_host * host = (struct jzmmc_host *)param;

    pending_ = msc_readl(host, MSC_IREG_OFFSET);
    pending = msc_readl(host, MSC_IREG_OFFSET) & (~ msc_readl(host, MSC_IMASK_OFFSET));

    if(pending_ & IFLG_CRC_RES_ERR)
    {
        LOG_W("RES CRC err");
    }
    if(pending_ & IFLG_CRC_READ_ERR)
    {
        LOG_W("READ CRC err");
    }
    if(pending_ & IFLG_CRC_WRITE_ERR)
    {
        LOG_W("WRITE CRC err");
    }
    
    
    if (pending & IFLG_TIMEOUT_RES)
    {
        host->cmd->err = -RT_ETIMEOUT;
        LOG_D("TIMEOUT");
    }
    else if (pending & IFLG_CRC_READ_ERR)
    {
        host->cmd->err = -RT_EIO;
        LOG_W("CRC READ");
    }
    else if (pending & (IFLG_CRC_RES_ERR | IFLG_CRC_WRITE_ERR | IFLG_TIMEOUT_READ))
    {
        LOG_E("MSC ERROR, pending=0x%08x", pending);
    }

    if (pending & (IFLG_DMA_DATA_DONE | IFLG_WR_ALL_DONE))
    {
        LOG_D("msc DMA end!");

        /* disable interrupt */
        rt_hw_interrupt_mask(host->irqno);
        rt_completion_done(&host->completion);
    }
    else if (pending & (MSC_TIME_OUT_RES | MSC_END_CMD_RES))
    {
        /* disable interrupt */
        rt_hw_interrupt_mask(host->irqno);
        rt_completion_done(&host->completion);
    }
}

rt_inline void jzmmc_clk_autoctrl(struct jzmmc_host *host, unsigned int on)
{
    if(on)
    {
        if(!clk_is_enabled(host->clock))
            clk_enable(host->clock);
        if(!clk_is_enabled(host->clock_gate))
            clk_enable(host->clock_gate);
    }
    else
    {
        if(clk_is_enabled(host->clock_gate))
            clk_disable(host->clock_gate);
        if(clk_is_enabled(host->clock))
            clk_disable(host->clock);
    }
}

static int jzmmc_hardware_init(struct jzmmc_host *jz_sdio)
{
    uint32_t hw_base = jz_sdio->hw_base;
    uint32_t value;

    /* reset mmc/sd controller */
    value = readl(hw_base + MSC_CTRL_OFFSET);
    value |= MSC_CTRL_RESET;
    writel(value, hw_base + MSC_CTRL_OFFSET);
    rt_thread_delay(1);
    value &= ~MSC_CTRL_RESET;
    writel(value, hw_base + MSC_CTRL_OFFSET);

    while(readl(hw_base + MSC_STAT_OFFSET) & MSC_STAT_IS_RESETTING);

    /* mask all IRQs */
    writel(0xffffffff, hw_base + MSC_IMASK_OFFSET);
    writel(0xffffffff, hw_base + MSC_IREG_OFFSET);

    /* set timeout */
    writel(0x100, hw_base + MSC_RESTO_OFFSET);
    writel(0x1ffffff, hw_base + MSC_RDTO_OFFSET);

    /* stop MMC/SD clock */
    jzmmc_stop_clock(hw_base);

    return 0;
}

/* RT-Thread SDIO interface */
static void jzmmc_sdio_set_iocfg(struct rt_mmcsd_host *host,
                                  struct rt_mmcsd_io_cfg *io_cfg)
{
    struct jzmmc_host * jz_sdio = host->private_data;
    rt_uint32_t clkdiv;

    LOG_D("set_iocfg clock: %d", io_cfg->clock);

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        LOG_D("MMC: Setting controller bus width to 4");
        jz_sdio->flags |= MSC_CMDAT_BUS_WIDTH_4BIT;
    }
    else
    {
        jz_sdio->flags &= ~(MSC_CMDAT_BUS_WIDTH_4BIT);
        LOG_D("MMC: Setting controller bus width to 1");
    }

    if (io_cfg->clock)
    {
        unsigned int clk_set = 0, clkrt = 0;
        unsigned int clk_want = io_cfg->clock;
        unsigned int lpm = 0;

        if (io_cfg->clock > 1 * 1000 * 1000)
        {
            io_cfg->clock = 1000 * 1000;
        }

        jzmmc_clk_autoctrl(jz_sdio, 1);
        if (clk_want > 3000000)
        {
            clk_set_rate(jz_sdio->clock, io_cfg->clock);
        }
        else
        {
            clk_set_rate(jz_sdio->clock, 24000000);
        }
        clk_set = clk_get_rate(jz_sdio->clock);

        while (clk_want < clk_set)
        {
            clkrt++;
            clk_set >>= 1;
        }

        if (clkrt > 7)
        {
            LOG_E("invalid value of CLKRT: "
                "ios->clock=%d clk_want=%d "
                "clk_set=%d clkrt=%X,",
                io_cfg->clock, clk_want, clk_set, clkrt);
            return;
        }

        if (!clkrt)
        {
            LOG_D("clk_want: %u, clk_set: %luHz", io_cfg->clock, clk_get_rate(jz_sdio->clock));
        }

        writel(clkrt, jz_sdio->hw_base + MSC_CLKRT_OFFSET);

        if (clk_set > 25000000)
        {
            lpm = (0x2 << LPM_DRV_SEL_SHF) | LPM_SMP_SEL;
        }

        if(jz_sdio->sdio_clk)
        {
            writel(lpm, jz_sdio->hw_base + MSC_LPM_OFFSET);
            writel(MSC_CTRL_CLOCK_START, jz_sdio->hw_base + MSC_CTRL_OFFSET);
        }
        else
        {
            lpm |= LPM_LPM;
            writel(lpm, jz_sdio->hw_base + MSC_LPM_OFFSET);
        }
    }
    else
    {
        jzmmc_clk_autoctrl(jz_sdio, 0);
    }

    /* maybe switch power to the card */
    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        LOG_D("MMCSD_POWER_OFF\r");
        break;
    case MMCSD_POWER_UP:
        LOG_D("MMCSD_POWER_UP\r");
        break;
    case MMCSD_POWER_ON:
        LOG_D("MMCSD_POWER_ON\r");
        jzmmc_hardware_init(jz_sdio);
        // jz_mmc_set_clock(jz_sdio, io_cfg->clock);
        break;
    default:
        LOG_D("unknown power_mode %d", io_cfg->power_mode);
        break;
    }
}

static rt_int32_t jzmmc_sdio_detect(struct rt_mmcsd_host *host)
{
    LOG_D("jz47xx_SD_Detect");

    return 0;
}

static void jzmmc_sdio_enable_sdio_irq(struct rt_mmcsd_host *host,
                                        rt_int32_t enable)
{
    LOG_D("jz47xx_sdio_enable_sdio_irq, enable:%d", enable);
}

static const struct rt_mmcsd_host_ops ops =
{
    jzmmc_sdio_request,
    jzmmc_sdio_set_iocfg,
    jzmmc_sdio_detect,
    jzmmc_sdio_enable_sdio_irq,
};

int jzmmc_sdio_init(void)
{
    struct rt_mmcsd_host *host = RT_NULL;
    struct jzmmc_host *jz_host = RT_NULL;

#ifdef  RT_USING_MSC0
    host = mmcsd_alloc_host();
    jz_host = rt_malloc_align(sizeof(struct jzmmc_host), 32);
    if(!(host && jz_host))
    {
        goto err;
    }
    
    rt_memset(jz_host, 0, sizeof(struct jzmmc_host));
    /* set hardware base firstly */
    jz_host->hw_base = MSC0_BASE;
    jz_host->clock = clk_get("cgu_msc0");
    jz_host->clock_gate = clk_get("msc0");
#ifdef DMA_BUFFER
    jz_host->_dma_buffer = _dma_buffer_0;
#endif
    /* init GPIO (msc0 boot)
     *        name      pin  fun
     * X1000  MSC0_D0:  PA23  1
     * X1000  MSC0_D1:  PA22  1
     * X1000  MSC0_D2:  PA21  1
     * X1000  MSC0_D3:  PA20  1
     * X1000  MSC0_CMD: PA25  1
     * X1000  MSC0_CLK: PA24  1
     */
    {
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_20, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_21, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_22, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_23, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_24, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_25, GPIO_FUNC_1);
    }

    /* enable MSC0 clock gate. */
    clk_enable(jz_host->clock_gate);

    jz_host->msc_clock = 25UL * 1000 * 1000;    /* 25Mhz */
    host->freq_min = 400 * 1000;                /* min 400Khz. */
    host->freq_max = 25 * 1000 * 1000;          /* max 25Mhz.  */
    
    // jz_host->msc_clock = 400 * 1000;    /* 25Mhz */
    // host->freq_min = 400 * 1000;                /* min 400Khz. */
    // host->freq_max = 400 * 1000;          /* max 25Mhz.  */

    /* set clock */
    clk_set_rate(jz_host->clock, 50000000);

    host->ops = &ops;
    host->valid_ocr = VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 |
        VDD_32_33 | VDD_33_34 | VDD_34_35 | VDD_35_36;
    // host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ | MMCSD_SUP_HIGHSPEED;
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ | MMCSD_SUP_HIGHSPEED;
    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;
    host->private_data = jz_host;

    jz_host->host = host;
    jz_host->irqno = IRQ_MSC0;

    rt_hw_interrupt_install(jz_host->irqno, jzmmc_isr, jz_host, "msc0");
    rt_hw_interrupt_mask(jz_host->irqno);

    mmcsd_change(host);
#endif // RT_USING_MSC0

#ifdef  RT_USING_MSC1
    host = mmcsd_alloc_host();
    jz_host = rt_malloc(sizeof(struct jzmmc_host));
    if(!(host && jz_host))
    {
        goto err;
    }

    jz_host1 = jz_host; // for debug

    rt_memset(jz_host, 0, sizeof(struct jzmmc_host));
    jz_host->hw_base = MSC1_BASE;
    jz_host->clock = clk_get("cgu_msc1");
    jz_host->clock_gate = clk_get("msc1");
#ifdef DMA_BUFFER
    jz_host->_dma_buffer = _dma_buffer_1;
#endif
    /* init GPIO (paladin msc1 SDIO wifi)
     *        name      pin  fun
     * X1000  MSC1_D0:  PC02  0
     * X1000  MSC1_D1:  PC03  0
     * X1000  MSC1_D2:  PC04  0
     * X1000  MSC1_D3:  PC05  0
     * X1000  MSC1_CMD: PC01  0
     * X1000  MSC1_CLK: PC00  0
     *
     */
    {
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_0, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_1, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_2, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_3, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_4, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_5, GPIO_FUNC_0);
    }

    /* enable MSC1 clock gate. */
    clk_enable(jz_host->clock_gate);

    jz_host->msc_clock = 25UL * 1000 * 1000;    /* 25Mhz */
    host->freq_min = 400 * 1000;                /* min 400Khz. */
    host->freq_max = 25 * 1000 * 1000;          /* max 25Mhz.  */

    /* set clock */
    clk_set_rate(jz_host->clock, BOARD_EXTAL_CLK);

    host->ops = &ops;
    host->valid_ocr = VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 |
        VDD_32_33 | VDD_33_34 | VDD_34_35 | VDD_35_36;
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ | MMCSD_SUP_HIGHSPEED;
    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;
    host->private_data = jz_host;

    jz_host->host = host;
    jz_host->irqno = IRQ_MSC1;

    rt_hw_interrupt_install(jz_host->irqno, jzmmc_isr, jz_host, "msc1");
    rt_hw_interrupt_mask(jz_host->irqno);

    mmcsd_change(host);
#endif // RT_USING_MSC1

    return RT_EOK;

err:
    if(host)
    {
        mmcsd_free_host(host);
    }
    if(jz_host)
    {
        rt_free(jz_host);
    }

    return -RT_ENOMEM;
}
INIT_DEVICE_EXPORT(jzmmc_sdio_init);

#include <finsh.h>
int msc_status(void)
{
    uint32_t value;

    if (jz_host1)
    {
        value = msc_readl(jz_host1, MSC_STAT_OFFSET);
        rt_kprintf("status: 0x%08x\n", value);

        value = msc_readl(jz_host1, MSC_IMASK_OFFSET);
        rt_kprintf("mask  : 0x%08x -> 0x%08x\n", value, ~value);

        value = msc_readl(jz_host1, MSC_IREG_OFFSET);
        rt_kprintf("iflag : 0x%08x\n", value);

        rt_kprintf("dma   : nda 0x%08x, da 0x%08x, len 0x%04x, cmd 0x%08x\n", msc_readl(jz_host1, MSC_DMANDA_OFFSET),
            msc_readl(jz_host1, MSC_DMADA_OFFSET),
            msc_readl(jz_host1, MSC_DMALEN_OFFSET),
            msc_readl(jz_host1, MSC_DMACMD_OFFSET));

        rt_kprintf("clock : %s\n", (stopping_clock == 1)? "stopping" : "none stopping");
    }

    return 0;
}
MSH_CMD_EXPORT(msc_status, dump msc status);

int msc_log(int argc, char** argv)
{
    if (argc == 2)
        sdio_log = atoi(argv[1]);

    return 0;
}
MSH_CMD_EXPORT(msc_log, set msc log enable);
