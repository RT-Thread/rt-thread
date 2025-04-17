/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <drivers/dev_mmcsd_core.h>
#include <at91sam926x.h>
#include "at91_mci.h"

#define USE_SLOT_B
//#define RT_MCI_DBG

#ifdef RT_MCI_DBG
#define mci_dbg(fmt, ...)  rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define mci_dbg(fmt, ...)
#endif

#define MMU_NOCACHE_ADDR(a)         ((rt_uint32_t)a | (1UL<<31))

extern void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size);
extern void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size);


#define AT91_MCI_ERRORS (AT91_MCI_RINDE | AT91_MCI_RDIRE | AT91_MCI_RCRCE   \
        | AT91_MCI_RENDE | AT91_MCI_RTOE | AT91_MCI_DCRCE       \
        | AT91_MCI_DTOE | AT91_MCI_OVRE | AT91_MCI_UNRE)

#define at91_mci_read(reg)  readl(AT91SAM9260_BASE_MCI + (reg))
#define at91_mci_write(reg, val)    writel((val), AT91SAM9260_BASE_MCI + (reg))


#define REQ_ST_INIT (1U << 0)
#define REQ_ST_CMD  (1U << 1)
#define REQ_ST_STOP (1U << 2)

struct at91_mci {
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_cmd *cmd;
    struct rt_timer timer;
    //struct rt_semaphore sem_ack;
    rt_uint32_t *buf;
    rt_uint32_t current_status;
};

/*
 * Reset the controller and restore most of the state
 */
static void at91_reset_host()
{
    rt_uint32_t mr;
    rt_uint32_t sdcr;
    rt_uint32_t dtor;
    rt_uint32_t imr;
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();

    imr = at91_mci_read(AT91_MCI_IMR);

    at91_mci_write(AT91_MCI_IDR, 0xffffffff);

    /* save current state */
    mr = at91_mci_read(AT91_MCI_MR) & 0x7fff;
    sdcr = at91_mci_read(AT91_MCI_SDCR);
    dtor = at91_mci_read(AT91_MCI_DTOR);

    /* reset the controller */
    at91_mci_write(AT91_MCI_CR, AT91_MCI_MCIDIS | AT91_MCI_SWRST);

    /* restore state */
    at91_mci_write(AT91_MCI_CR, AT91_MCI_MCIEN);
    at91_mci_write(AT91_MCI_MR, mr);
    at91_mci_write(AT91_MCI_SDCR, sdcr);
    at91_mci_write(AT91_MCI_DTOR, dtor);
    at91_mci_write(AT91_MCI_IER, imr);

    /* make sure sdio interrupts will fire */
    at91_mci_read(AT91_MCI_SR);
    rt_hw_interrupt_enable(level);

}


/*
 * Enable the controller
 */
static void at91_mci_enable()
{
    rt_uint32_t mr;

    at91_mci_write(AT91_MCI_CR, AT91_MCI_MCIEN);
    at91_mci_write(AT91_MCI_IDR, 0xffffffff);
    at91_mci_write(AT91_MCI_DTOR, AT91_MCI_DTOMUL_1M | AT91_MCI_DTOCYC);
    mr = AT91_MCI_PDCMODE | 0x34a;

    mr |= AT91_MCI_RDPROOF | AT91_MCI_WRPROOF;

    at91_mci_write(AT91_MCI_MR, mr);

    /* use Slot A or B (only one at same time) */
    at91_mci_write(AT91_MCI_SDCR, 1); /* use slot b */
}

/*
 * Disable the controller
 */
static void at91_mci_disable()
{
    at91_mci_write(AT91_MCI_CR, AT91_MCI_MCIDIS | AT91_MCI_SWRST);
}

static void at91_timeout_timer(void *data)
{
    struct at91_mci *mci;

    mci = (struct at91_mci *)data;

    if (mci->req)
    {
        rt_kprintf("Timeout waiting end of packet\n");

        if (mci->current_status == REQ_ST_CMD)
        {
            if (mci->req->cmd && mci->req->data)
            {
                mci->req->data->err = -RT_ETIMEOUT;
            }
            else
            {
                if (mci->req->cmd)
                    mci->req->cmd->err = -RT_ETIMEOUT;
            }
        }
        else if (mci->current_status == REQ_ST_STOP)
        {
            mci->req->stop->err = -RT_ETIMEOUT;
        }

        at91_reset_host();
        mmcsd_req_complete(mci->host);
    }
}

/*
 * Prepare a dma read
 */
static void at91_mci_init_dma_read(struct at91_mci *mci)
{
    rt_uint8_t i;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;
    rt_uint32_t length;

    mci_dbg("pre dma read\n");

    cmd = mci->cmd;
    if (!cmd)
    {
        mci_dbg("no command\n");
        return;
    }

    data = cmd->data;
    if (!data)
    {
        mci_dbg("no data\n");
        return;
    }

    for (i = 0; i < 1; i++)
    {
        /* Check to see if this needs filling */
        if (i == 0)
        {
            if (at91_mci_read(AT91_PDC_RCR) != 0)
            {
                mci_dbg("Transfer active in current\n");
                continue;
            }
        }
        else {
            if (at91_mci_read(AT91_PDC_RNCR) != 0)
            {
                mci_dbg("Transfer active in next\n");
                continue;
            }
        }

        length = data->blksize * data->blks;
        mci_dbg("dma address = %08X, length = %d\n", data->buf, length);

        if (i == 0)
        {
            at91_mci_write(AT91_PDC_RPR, (rt_uint32_t)(data->buf));
            at91_mci_write(AT91_PDC_RCR, (data->blksize & 0x3) ? length : length / 4);
        }
        else
        {
            at91_mci_write(AT91_PDC_RNPR, (rt_uint32_t)(data->buf));
            at91_mci_write(AT91_PDC_RNCR, (data->blksize & 0x3) ? length : length / 4);
        }
    }

    mci_dbg("pre dma read done\n");
}

/*
 * Send a command
 */
static void at91_mci_send_command(struct at91_mci *mci, struct rt_mmcsd_cmd *cmd)
{
    rt_uint32_t cmdr, mr;
    rt_uint32_t block_length;
    struct rt_mmcsd_data *data = cmd->data;
    struct rt_mmcsd_host *host = mci->host;

    rt_uint32_t blocks;
    rt_uint32_t ier = 0;
    rt_uint32_t length;

    mci->cmd = cmd;

    /* Needed for leaving busy state before CMD1 */
    if ((at91_mci_read(AT91_MCI_SR) & AT91_MCI_RTOE) && (cmd->cmd_code == 1))
    {
        mci_dbg("Clearing timeout\n");
        at91_mci_write(AT91_MCI_ARGR, 0);
        at91_mci_write(AT91_MCI_CMDR, AT91_MCI_OPDCMD);
        while (!(at91_mci_read(AT91_MCI_SR) & AT91_MCI_CMDRDY))
        {
            /* spin */
            mci_dbg("Clearing: SR = %08X\n", at91_mci_read(AT91_MCI_SR));
        }
    }

    cmdr = cmd->cmd_code;

    if (resp_type(cmd) == RESP_NONE)
        cmdr |= AT91_MCI_RSPTYP_NONE;
    else
    {
        /* if a response is expected then allow maximum response latancy */
        cmdr |= AT91_MCI_MAXLAT;
        /* set 136 bit response for R2, 48 bit response otherwise */
        if (resp_type(cmd) == RESP_R2)
            cmdr |= AT91_MCI_RSPTYP_136;
        else
            cmdr |= AT91_MCI_RSPTYP_48;
    }

    if (data)
    {

        block_length = data->blksize;
        blocks = data->blks;

        /* always set data start - also set direction flag for read */
        if (data->flags & DATA_DIR_READ)
            cmdr |= (AT91_MCI_TRDIR | AT91_MCI_TRCMD_START);
        else if (data->flags & DATA_DIR_WRITE)
            cmdr |= AT91_MCI_TRCMD_START;

        if (data->flags & DATA_STREAM)
            cmdr |= AT91_MCI_TRTYP_STREAM;
        if (data->blks > 1)
            cmdr |= AT91_MCI_TRTYP_MULTIPLE;
    }
    else
    {
        block_length = 0;
        blocks = 0;
    }

    /*if (cmd->cmd_code == GO_IDLE_STATE)
    {
        cmdr |= AT91_MCI_SPCMD_INIT;
    }*/

    if (cmd->cmd_code == STOP_TRANSMISSION)
        cmdr |= AT91_MCI_TRCMD_STOP;

    if (host->io_cfg.bus_mode == MMCSD_BUSMODE_OPENDRAIN)
        cmdr |= AT91_MCI_OPDCMD;

    /*
     * Set the arguments and send the command
     */
    mci_dbg("Sending command %d as %08X, arg = %08X, blocks = %d, length = %d (MR = %08X)\n",
        cmd->cmd_code, cmdr, cmd->arg, blocks, block_length, at91_mci_read(AT91_MCI_MR));

    if (!data)
    {
        at91_mci_write(AT91_PDC_PTCR, AT91_PDC_TXTDIS | AT91_PDC_RXTDIS);
        at91_mci_write(AT91_PDC_RPR, 0);
        at91_mci_write(AT91_PDC_RCR, 0);
        at91_mci_write(AT91_PDC_RNPR, 0);
        at91_mci_write(AT91_PDC_RNCR, 0);
        at91_mci_write(AT91_PDC_TPR, 0);
        at91_mci_write(AT91_PDC_TCR, 0);
        at91_mci_write(AT91_PDC_TNPR, 0);
        at91_mci_write(AT91_PDC_TNCR, 0);
        ier = AT91_MCI_CMDRDY;
    }
    else
    {
        /* zero block length and PDC mode */
        mr = at91_mci_read(AT91_MCI_MR) & 0x5fff;
        mr |= (data->blksize & 0x3) ? AT91_MCI_PDCFBYTE : 0;
        mr |= (block_length << 16);
        mr |= AT91_MCI_PDCMODE;
        at91_mci_write(AT91_MCI_MR, mr);

        at91_mci_write(AT91_MCI_BLKR,
            AT91_MCI_BLKR_BCNT(blocks) |
            AT91_MCI_BLKR_BLKLEN(block_length));

        /*
         * Disable the PDC controller
         */
        at91_mci_write(AT91_PDC_PTCR, AT91_PDC_RXTDIS | AT91_PDC_TXTDIS);

        if (cmdr & AT91_MCI_TRCMD_START)
        {
            if (cmdr & AT91_MCI_TRDIR)
            {
                /*
                 * Handle a read
                 */

                mmu_invalidate_dcache((rt_uint32_t)data->buf, data->blksize*data->blks);
                at91_mci_init_dma_read(mci);
                ier = AT91_MCI_ENDRX /* | AT91_MCI_RXBUFF */;
            }
            else
            {
                /*
                 * Handle a write
                 */
                length = block_length * blocks;
                /*
                 * at91mci MCI1 rev2xx Data Write Operation and
                 * number of bytes erratum
                 */
                if (length < 12)
                {
                    length = 12;
                    mci->buf = rt_malloc(length);
                    if (!mci->buf)
                    {
                        rt_kprintf("rt alloc tx buffer failed\n");
                        cmd->err = -RT_ENOMEM;
                        mmcsd_req_complete(mci->host);
                        return;
                    }
                    rt_memset(mci->buf, 0, 12);
                    rt_memcpy(mci->buf, data->buf, length);
                    mmu_clean_dcache((rt_uint32_t)mci->buf, length);
                    at91_mci_write(AT91_PDC_TPR, (rt_uint32_t)(mci->buf));
                    at91_mci_write(AT91_PDC_TCR, (data->blksize & 0x3) ?
                            length : length / 4);
                }
                else
                {
                    mmu_clean_dcache((rt_uint32_t)data->buf, data->blksize*data->blks);
                    at91_mci_write(AT91_PDC_TPR, (rt_uint32_t)(data->buf));
                    at91_mci_write(AT91_PDC_TCR, (data->blksize & 0x3) ?
                            length : length / 4);
                }
                mci_dbg("Transmitting %d bytes\n", length);
                ier = AT91_MCI_CMDRDY;
            }
        }
    }

    /*
     * Send the command and then enable the PDC - not the other way round as
     * the data sheet says
     */

    at91_mci_write(AT91_MCI_ARGR, cmd->arg);
    at91_mci_write(AT91_MCI_CMDR, cmdr);

    if (cmdr & AT91_MCI_TRCMD_START)
    {
        if (cmdr & AT91_MCI_TRDIR)
            at91_mci_write(AT91_PDC_PTCR, AT91_PDC_RXTEN);
    }

    /* Enable selected interrupts */
    at91_mci_write(AT91_MCI_IER, AT91_MCI_ERRORS | ier);
}

/*
 * Process the next step in the request
 */
static void at91_mci_process_next(struct at91_mci *mci)
{
    if (mci->current_status == REQ_ST_INIT)
    {
        mci->current_status = REQ_ST_CMD;
        at91_mci_send_command(mci, mci->req->cmd);
    }
    else if ((mci->current_status == REQ_ST_CMD) && mci->req->stop)
    {
        mci->current_status = REQ_ST_STOP;
        at91_mci_send_command(mci, mci->req->stop);
    }
    else
    {
        rt_timer_stop(&mci->timer);
        /* the mci controller hangs after some transfers,
         * and the workaround is to reset it after each transfer.
         */
        at91_reset_host();
        mmcsd_req_complete(mci->host);
    }
}

/*
 * Handle an MMC request
 */
static void at91_mci_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    rt_uint32_t timeout = RT_TICK_PER_SECOND;
    struct at91_mci *mci = host->private_data;
    mci->req = req;
    mci->current_status = REQ_ST_INIT;

    rt_timer_control(&mci->timer, RT_TIMER_CTRL_SET_TIME, (void*)&timeout);
    rt_timer_start(&mci->timer);

    at91_mci_process_next(mci);
}

/*
 * Handle transmitted data
 */
static void at91_mci_handle_transmitted(struct at91_mci *mci)
{
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;

    mci_dbg("Handling the transmit\n");

    /* Disable the transfer */
    at91_mci_write(AT91_PDC_PTCR, AT91_PDC_RXTDIS | AT91_PDC_TXTDIS);

    /* Now wait for cmd ready */
    at91_mci_write(AT91_MCI_IDR, AT91_MCI_TXBUFE);

    cmd = mci->cmd;
    if (!cmd) return;

    data = cmd->data;
    if (!data) return;

    if (data->blks > 1)
    {
        mci_dbg("multiple write : wait for BLKE...\n");
        at91_mci_write(AT91_MCI_IER, AT91_MCI_BLKE);
    } else
        at91_mci_write(AT91_MCI_IER, AT91_MCI_NOTBUSY);
}


/*
 * Handle after a dma read
 */
static void at91_mci_post_dma_read(struct at91_mci *mci)
{
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;

    mci_dbg("post dma read\n");

    cmd = mci->cmd;
    if (!cmd)
    {
        mci_dbg("no command\n");
        return;
    }

    data = cmd->data;
    if (!data)
    {
        mci_dbg("no data\n");
        return;
    }

    at91_mci_write(AT91_MCI_IDR, AT91_MCI_ENDRX);
    at91_mci_write(AT91_MCI_IER, AT91_MCI_RXBUFF);

    mci_dbg("post dma read done\n");
}

/*Handle after command sent ready*/
static int at91_mci_handle_cmdrdy(struct at91_mci *mci)
{
    if (!mci->cmd)
        return 1;
    else if (!mci->cmd->data)
    {
        if (mci->current_status == REQ_ST_STOP)
        {
            /*After multi block write, we must wait for NOTBUSY*/
            at91_mci_write(AT91_MCI_IER, AT91_MCI_NOTBUSY);
        }
        else return 1;
    }
    else if (mci->cmd->data->flags & DATA_DIR_WRITE)
    {
        /*After sendding multi-block-write command, start DMA transfer*/
        at91_mci_write(AT91_MCI_IER, AT91_MCI_TXBUFE | AT91_MCI_BLKE);
        at91_mci_write(AT91_PDC_PTCR, AT91_PDC_TXTEN);
    }

    /* command not completed, have to wait */
    return 0;
}

/*
 * Handle a command that has been completed
 */
static void at91_mci_completed_command(struct at91_mci *mci, rt_uint32_t status)
{
    struct rt_mmcsd_cmd *cmd = mci->cmd;
    struct rt_mmcsd_data *data = cmd->data;

    at91_mci_write(AT91_MCI_IDR, 0xffffffff & ~(AT91_MCI_SDIOIRQA | AT91_MCI_SDIOIRQB));

    cmd->resp[0] = at91_mci_read(AT91_MCI_RSPR(0));
    cmd->resp[1] = at91_mci_read(AT91_MCI_RSPR(1));
    cmd->resp[2] = at91_mci_read(AT91_MCI_RSPR(2));
    cmd->resp[3] = at91_mci_read(AT91_MCI_RSPR(3));

    if (mci->buf)
    {
        //rt_memcpy(data->buf, mci->buf, data->blksize*data->blks);
        rt_free(mci->buf);
        mci->buf = RT_NULL;
    }

    mci_dbg("Status = %08X/%08x [%08X %08X %08X %08X]\n",
         status, at91_mci_read(AT91_MCI_SR),
         cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);

    if (status & AT91_MCI_ERRORS)
    {
        if ((status & AT91_MCI_RCRCE) && (resp_type(cmd) & (RESP_R3|RESP_R4)))
        {
            cmd->err = 0;
        }
        else
        {
            if (status & (AT91_MCI_DTOE | AT91_MCI_DCRCE))
            {
                if (data)
                {
                    if (status & AT91_MCI_DTOE)
                        data->err = -RT_ETIMEOUT;
                    else if (status & AT91_MCI_DCRCE)
                        data->err = -RT_ERROR;
                }
            }
            else
            {
                if (status & AT91_MCI_RTOE)
                    cmd->err = -RT_ETIMEOUT;
                else if (status & AT91_MCI_RCRCE)
                    cmd->err = -RT_ERROR;
                else
                    cmd->err = -RT_ERROR;
            }

            rt_kprintf("error detected and set to %d/%d (cmd = %d)\n",
                cmd->err, data ? data->err : 0,
                 cmd->cmd_code);
        }
    }
    else
        cmd->err = 0;

    at91_mci_process_next(mci);
}

/*
 * Handle an interrupt
 */
static void at91_mci_irq(int irq, void *param)
{
    struct at91_mci *mci = (struct at91_mci *)param;
    rt_int32_t completed = 0;
    rt_uint32_t int_status, int_mask;

    int_status = at91_mci_read(AT91_MCI_SR);
    int_mask = at91_mci_read(AT91_MCI_IMR);

    mci_dbg("MCI irq: status = %08X, %08X, %08X\n", int_status, int_mask,
        int_status & int_mask);

    int_status = int_status & int_mask;

    if (int_status & AT91_MCI_ERRORS)
    {
        completed = 1;

        if (int_status & AT91_MCI_UNRE)
            mci_dbg("MMC: Underrun error\n");
        if (int_status & AT91_MCI_OVRE)
            mci_dbg("MMC: Overrun error\n");
        if (int_status & AT91_MCI_DTOE)
            mci_dbg("MMC: Data timeout\n");
        if (int_status & AT91_MCI_DCRCE)
            mci_dbg("MMC: CRC error in data\n");
        if (int_status & AT91_MCI_RTOE)
            mci_dbg("MMC: Response timeout\n");
        if (int_status & AT91_MCI_RENDE)
            mci_dbg("MMC: Response end bit error\n");
        if (int_status & AT91_MCI_RCRCE)
            mci_dbg("MMC: Response CRC error\n");
        if (int_status & AT91_MCI_RDIRE)
            mci_dbg("MMC: Response direction error\n");
        if (int_status & AT91_MCI_RINDE)
            mci_dbg("MMC: Response index error\n");
    }
    else
    {
        /* Only continue processing if no errors */

        if (int_status & AT91_MCI_TXBUFE)
        {
            mci_dbg("TX buffer empty\n");
            at91_mci_handle_transmitted(mci);
        }

        if (int_status & AT91_MCI_ENDRX)
        {
            mci_dbg("ENDRX\n");
            at91_mci_post_dma_read(mci);
        }

        if (int_status & AT91_MCI_RXBUFF)
        {
            mci_dbg("RX buffer full\n");
            at91_mci_write(AT91_PDC_PTCR, AT91_PDC_RXTDIS | AT91_PDC_TXTDIS);
            at91_mci_write(AT91_MCI_IDR, AT91_MCI_RXBUFF | AT91_MCI_ENDRX);
            completed = 1;
        }

        if (int_status & AT91_MCI_ENDTX)
            mci_dbg("Transmit has ended\n");

        if (int_status & AT91_MCI_NOTBUSY)
        {
            mci_dbg("Card is ready\n");
            //at91_mci_update_bytes_xfered(host);
            completed = 1;
        }

        if (int_status & AT91_MCI_DTIP)
            mci_dbg("Data transfer in progress\n");

        if (int_status & AT91_MCI_BLKE)
        {
            mci_dbg("Block transfer has ended\n");
            if (mci->req->data && mci->req->data->blks > 1)
            {
                /* multi block write : complete multi write
                 * command and send stop */
                completed = 1;
            }
            else
            {
                at91_mci_write(AT91_MCI_IER, AT91_MCI_NOTBUSY);
            }
        }

        /*if (int_status & AT91_MCI_SDIOIRQA)
            rt_mmcsd_signal_sdio_irq(host->mmc);*/

        if (int_status & AT91_MCI_SDIOIRQB)
            sdio_irq_wakeup(mci->host);

        if (int_status & AT91_MCI_TXRDY)
            mci_dbg("Ready to transmit\n");

        if (int_status & AT91_MCI_RXRDY)
            mci_dbg("Ready to receive\n");

        if (int_status & AT91_MCI_CMDRDY)
        {
            mci_dbg("Command ready\n");
            completed = at91_mci_handle_cmdrdy(mci);
        }
    }

    if (completed)
    {
        mci_dbg("Completed command\n");
        at91_mci_write(AT91_MCI_IDR, 0xffffffff & ~(AT91_MCI_SDIOIRQA | AT91_MCI_SDIOIRQB));
        at91_mci_completed_command(mci, int_status);
    }
    else
        at91_mci_write(AT91_MCI_IDR, int_status & ~(AT91_MCI_SDIOIRQA | AT91_MCI_SDIOIRQB));

}


/*
 * Set the IOCFG
 */
static void at91_mci_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t clkdiv;
    //struct at91_mci *mci = host->private_data;
    rt_uint32_t at91_master_clock = clk_get_rate(clk_get("mck"));

    if (io_cfg->clock == 0)
    {
        /* Disable the MCI controller */
        at91_mci_write(AT91_MCI_CR, AT91_MCI_MCIDIS);
        clkdiv = 0;
    }
    else
    {
        /* Enable the MCI controller */
        at91_mci_write(AT91_MCI_CR, AT91_MCI_MCIEN);

        if ((at91_master_clock % (io_cfg->clock * 2)) == 0)
            clkdiv = ((at91_master_clock / io_cfg->clock) / 2) - 1;
        else
            clkdiv = (at91_master_clock / io_cfg->clock) / 2;

        mci_dbg("clkdiv = %d. mcck = %ld\n", clkdiv,
            at91_master_clock / (2 * (clkdiv + 1)));
    }
    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        mci_dbg("MMC: Setting controller bus width to 4\n");
        at91_mci_write(AT91_MCI_SDCR, at91_mci_read(AT91_MCI_SDCR) | AT91_MCI_SDCBUS);
    }
    else
    {
        mci_dbg("MMC: Setting controller bus width to 1\n");
        at91_mci_write(AT91_MCI_SDCR, at91_mci_read(AT91_MCI_SDCR) & ~AT91_MCI_SDCBUS);
    }

    /* Set the clock divider */
    at91_mci_write(AT91_MCI_MR, (at91_mci_read(AT91_MCI_MR) & ~AT91_MCI_CLKDIV) | clkdiv);

    /* maybe switch power to the card */
    switch (io_cfg->power_mode)
    {
        case MMCSD_POWER_OFF:
            break;
        case MMCSD_POWER_UP:
            break;
        case MMCSD_POWER_ON:
            /*at91_mci_write(AT91_MCI_ARGR, 0);
            at91_mci_write(AT91_MCI_CMDR, 0|AT91_MCI_SPCMD_INIT|AT91_MCI_OPDCMD);
            mci_dbg("MCI_SR=0x%08x\n", at91_mci_read(AT91_MCI_SR));
            while (!(at91_mci_read(AT91_MCI_SR) & AT91_MCI_CMDRDY))
            {

            }
            mci_dbg("at91 mci power on\n");*/
            break;
        default:
            rt_kprintf("unknown power_mode %d\n", io_cfg->power_mode);
            break;
    }

}


static void at91_mci_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    at91_mci_write(enable ? AT91_MCI_IER : AT91_MCI_IDR, AT91_MCI_SDIOIRQB);
}


static const struct rt_mmcsd_host_ops ops = {
    at91_mci_request,
    at91_mci_set_iocfg,
        RT_NULL,
    at91_mci_enable_sdio_irq,
};

void at91_mci_detect(int irq, void *param)
{
    rt_kprintf("mmcsd gpio detected\n");
}

static void mci_gpio_init()
{
#ifdef USE_SLOT_B
    at91_sys_write(AT91_PIOA + PIO_PUER, (1 << 0)|(1 << 1)|(1 << 3)|(1 << 4)|(1 << 5));
    at91_sys_write(AT91_PIOA + PIO_PUDR, (1 << 8));
    at91_sys_write(AT91_PIOA + PIO_BSR, (1 << 0)|(1 << 1)|(1 << 3)|(1 << 4)|(1 << 5));
    at91_sys_write(AT91_PIOA + PIO_ASR, (1 << 8));
    at91_sys_write(AT91_PIOA + PIO_PDR, (1 << 0)|(1 << 1)|(1 << 3)|(1 << 4)|(1 << 5)|(1 << 8));

    at91_sys_write(AT91_PIOA + PIO_IDR, (1 << 6)|(1 << 7));
    at91_sys_write(AT91_PIOA + PIO_PUER, (1 << 6)|(1 << 7));
    at91_sys_write(AT91_PIOA + PIO_ODR, (1 << 6)|(1 << 7));
    at91_sys_write(AT91_PIOA + PIO_PER, (1 << 6)|(1 << 7));
#else
    at91_sys_write(AT91_PIOA + PIO_PUER, (1 << 6)|(1 << 7)|(1 << 9)|(1 << 10)|(1 << 11));
    at91_sys_write(AT91_PIOA + PIO_ASR, (1 << 6)|(1 << 7)|(1 << 9)|(1 << 10)|(1 << 11)|(1 << 8));
    at91_sys_write(AT91_PIOA + PIO_PDR, (1 << 6)|(1 << 7)|(1 << 9)|(1 << 10)|(1 << 11)|(1 << 8));
#endif
}

int at91_mci_init(void)
{
    struct rt_mmcsd_host *host;
    struct at91_mci *mci;

    host = mmcsd_alloc_host();
    if (!host)
    {
        return -RT_ERROR;
    }

    mci = rt_malloc(sizeof(struct at91_mci));
    if (!mci)
    {
        rt_kprintf("alloc mci failed\n");
        goto err;
    }

    rt_memset(mci, 0, sizeof(struct at91_mci));

    host->ops = &ops;
    host->freq_min = 375000;
    host->freq_max = 25000000;
    host->valid_ocr = VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | \
                MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;

    mci->host = host;

    mci_gpio_init();
    at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_MCI); //enable MCI clock

    at91_mci_disable();
    at91_mci_enable();

    /* instal interrupt */
    rt_hw_interrupt_install(AT91SAM9260_ID_MCI, at91_mci_irq,
                            (void *)mci, "MMC");
    rt_hw_interrupt_umask(AT91SAM9260_ID_MCI);
    rt_hw_interrupt_install(gpio_to_irq(AT91_PIN_PA7),
                            at91_mci_detect, RT_NULL, "MMC_DETECT");
    rt_hw_interrupt_umask(gpio_to_irq(AT91_PIN_PA7));

    rt_timer_init(&mci->timer, "mci_timer",
        at91_timeout_timer,
        mci,
        RT_TICK_PER_SECOND,
        RT_TIMER_FLAG_PERIODIC);

    //rt_timer_start(&mci->timer);

    //rt_sem_init(&mci->sem_ack, "sd_ack", 0, RT_IPC_FLAG_FIFO);

    host->private_data = mci;

    mmcsd_change(host);

    return 0;

err:
    mmcsd_free_host(host);

    return -RT_ENOMEM;
}

INIT_DEVICE_EXPORT(at91_mci_init);

#include "finsh.h"
FINSH_FUNCTION_EXPORT(at91_mci_init, at91sam9260 sd init);

void mci_dump(void)
{
    rt_uint32_t i;

    rt_kprintf("PIOA_PSR=0x%08x\n", at91_sys_read(AT91_PIOA+PIO_PSR));
    rt_kprintf("PIOA_ABSR=0x%08x\n", at91_sys_read(AT91_PIOA+PIO_ABSR));
    rt_kprintf("PIOA_PUSR=0x%08x\n", at91_sys_read(AT91_PIOA+PIO_PUSR));

    for (i = 0; i <= 0x4c; i += 4) {
        rt_kprintf("0x%08x:0x%08x\n", AT91SAM9260_BASE_MCI+i, at91_mci_read(i));
    }
}

FINSH_FUNCTION_EXPORT(mci_dump, dump register for mci);
