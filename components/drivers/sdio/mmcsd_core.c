/*
 * File      : mmcsd_core.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 */

#include <rtthread.h>
#include <drivers/mmcsd_core.h>
#include <drivers/sd.h>

#ifndef RT_MMCSD_STACK_SIZE
#define RT_MMCSD_STACK_SIZE 1024
#endif
#ifndef RT_MMCSD_THREAD_PREORITY
#if (RT_THREAD_PRIORITY_MAX == 32)
#define RT_MMCSD_THREAD_PREORITY  0x16
#else
#define RT_MMCSD_THREAD_PREORITY  0x40
#endif
#endif

//static struct rt_semaphore mmcsd_sem;
static struct rt_thread mmcsd_detect_thread;
static rt_uint8_t mmcsd_stack[RT_MMCSD_STACK_SIZE];
static struct rt_mailbox  mmcsd_detect_mb;
static rt_uint32_t mmcsd_detect_mb_pool[4];

void mmcsd_host_lock(struct rt_mmcsd_host *host)
{
    rt_sem_take(&host->bus_lock, RT_WAITING_FOREVER);
}

void mmcsd_host_unlock(struct rt_mmcsd_host *host)
{
    rt_sem_release(&host->bus_lock);
}

void mmcsd_req_complete(struct rt_mmcsd_host *host)
{
    rt_sem_release(&host->sem_ack);
}

void mmcsd_send_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    req->cmd->err = 0;
    req->cmd->mrq = req;
    if (req->data)
    {   
        req->cmd->data = req->data;
        req->data->err = 0;
        req->data->mrq = req;
        if (req->stop)
        {
            req->data->stop = req->stop;
            req->stop->err = 0;
            req->stop->mrq = req;
        }       
   }
    host->ops->request(host, req);
    rt_sem_take(&host->sem_ack, RT_WAITING_FOREVER);
}

rt_int32_t mmcsd_send_cmd(struct rt_mmcsd_host *host,
                          struct rt_mmcsd_cmd  *cmd,
                          int                   retries)
{
    struct rt_mmcsd_req req;

    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(cmd->resp, 0, sizeof(cmd->resp));

    req.cmd = cmd;
    cmd->data = RT_NULL;

    mmcsd_send_request(host, &req);

    return cmd->err;
}

rt_int32_t mmcsd_go_idle(struct rt_mmcsd_host *host)
{
    rt_int32_t err;
    struct rt_mmcsd_cmd cmd;

    if (!controller_is_spi(host))
    {
        mmcsd_set_chip_select(host, MMCSD_CS_HIGH);
        mmcsd_delay_ms(1);
    }

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = GO_IDLE_STATE;
    cmd.arg = 0;
    cmd.flags = RESP_SPI_R1 | RESP_NONE | CMD_BC;

    err = mmcsd_send_cmd(host, &cmd, 0);

    mmcsd_delay_ms(1);

    if (!controller_is_spi(host)) 
    {
        mmcsd_set_chip_select(host, MMCSD_CS_IGNORE);
        mmcsd_delay_ms(1);
    }

    return err;
}

rt_int32_t mmcsd_spi_read_ocr(struct rt_mmcsd_host *host,
                              rt_int32_t            high_capacity,
                              rt_uint32_t          *ocr)
{
    struct rt_mmcsd_cmd cmd;
    rt_int32_t err;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = SPI_READ_OCR;
    cmd.arg = high_capacity ? (1 << 30) : 0;
    cmd.flags = RESP_SPI_R3;

    err = mmcsd_send_cmd(host, &cmd, 0);

    *ocr = cmd.resp[1];

    return err;
}

rt_int32_t mmcsd_all_get_cid(struct rt_mmcsd_host *host, rt_uint32_t *cid)
{
    rt_int32_t err;
    struct rt_mmcsd_cmd cmd;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = ALL_SEND_CID;
    cmd.arg = 0;
    cmd.flags = RESP_R2 | CMD_BCR;

    err = mmcsd_send_cmd(host, &cmd, 3);
    if (err)
        return err;

    rt_memcpy(cid, cmd.resp, sizeof(rt_uint32_t) * 4);

    return 0;
}

rt_int32_t mmcsd_get_cid(struct rt_mmcsd_host *host, rt_uint32_t *cid)
{
    rt_int32_t err, i;
    struct rt_mmcsd_req req;
    struct rt_mmcsd_cmd cmd;
    struct rt_mmcsd_data data;
    rt_uint32_t *buf = RT_NULL;

    if (!controller_is_spi(host)) 
    {
        if (!host->card)
            return -RT_ERROR;
        rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

        cmd.cmd_code = SEND_CID;
        cmd.arg = host->card->rca << 16;
        cmd.flags = RESP_R2 | CMD_AC;
        err = mmcsd_send_cmd(host, &cmd, 3);
        if (err)
            return err;

        rt_memcpy(cid, cmd.resp, sizeof(rt_uint32_t) * 4);

        return 0;
    }

    buf = (rt_uint32_t *)rt_malloc(16);
    if (!buf) 
    {
        rt_kprintf("allocate memory failed\n");

        return -RT_ENOMEM;
    }

    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));
    rt_memset(&data, 0, sizeof(struct rt_mmcsd_data));

    req.cmd = &cmd;
    req.data = &data;

    cmd.cmd_code = SEND_CID;
    cmd.arg = 0;

    /* NOTE HACK:  the RESP_SPI_R1 is always correct here, but we
     * rely on callers to never use this with "native" calls for reading
     * CSD or CID.  Native versions of those commands use the R2 type,
     * not R1 plus a data block.
     */
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_ADTC;

    data.blksize = 16;
    data.blks = 1;
    data.flags = DATA_DIR_READ;
    data.buf = buf;
    /*
     * The spec states that CSR and CID accesses have a timeout
     * of 64 clock cycles.
     */
    data.timeout_ns = 0;
    data.timeout_clks = 64;

    mmcsd_send_request(host, &req);

    if (cmd.err || data.err)
    {
        rt_free(buf);

        return -RT_ERROR;
    }

    for (i = 0;i < 4;i++)
        cid[i] = buf[i];
    rt_free(buf);

    return 0;
}

rt_int32_t mmcsd_get_csd(struct rt_mmcsd_card *card, rt_uint32_t *csd)
{
    rt_int32_t err, i;
    struct rt_mmcsd_req req;
    struct rt_mmcsd_cmd cmd;
    struct rt_mmcsd_data data;
    rt_uint32_t *buf = RT_NULL;

    if (!controller_is_spi(card->host))
    {
        rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

        cmd.cmd_code = SEND_CSD;
        cmd.arg = card->rca << 16;
        cmd.flags = RESP_R2 | CMD_AC;
        err = mmcsd_send_cmd(card->host, &cmd, 3);
        if (err)
            return err;

        rt_memcpy(csd, cmd.resp, sizeof(rt_uint32_t) * 4);

        return 0;
    }

    buf = (rt_uint32_t*)rt_malloc(16);
    if (!buf) 
    {
        rt_kprintf("allocate memory failed\n");

        return -RT_ENOMEM;
    }

    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));
    rt_memset(&data, 0, sizeof(struct rt_mmcsd_data));

    req.cmd = &cmd;
    req.data = &data;

    cmd.cmd_code = SEND_CSD;
    cmd.arg = 0;

    /* NOTE HACK:  the RESP_SPI_R1 is always correct here, but we
     * rely on callers to never use this with "native" calls for reading
     * CSD or CID.  Native versions of those commands use the R2 type,
     * not R1 plus a data block.
     */
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_ADTC;

    data.blksize = 16;
    data.blks = 1;
    data.flags = DATA_DIR_READ;
    data.buf = buf;

    /*
     * The spec states that CSR and CID accesses have a timeout
     * of 64 clock cycles.
     */
    data.timeout_ns = 0;
    data.timeout_clks = 64;

    mmcsd_send_request(card->host, &req);

    if (cmd.err || data.err)
    {
        rt_free(buf);

        return -RT_ERROR;
    }

    for (i = 0;i < 4;i++)
        csd[i] = buf[i];
    rt_free(buf);

    return 0;
}

static rt_int32_t _mmcsd_select_card(struct rt_mmcsd_host *host,
                                     struct rt_mmcsd_card *card)
{
    rt_int32_t err;
    struct rt_mmcsd_cmd cmd;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = SELECT_CARD;

    if (card) 
    {
        cmd.arg = card->rca << 16;
        cmd.flags = RESP_R1 | CMD_AC;
    } 
    else 
    {
        cmd.arg = 0;
        cmd.flags = RESP_NONE | CMD_AC;
    }

    err = mmcsd_send_cmd(host, &cmd, 3);
    if (err)
        return err;

    return 0;
}

rt_int32_t mmcsd_select_card(struct rt_mmcsd_card *card)
{
    return _mmcsd_select_card(card->host, card);
}

rt_int32_t mmcsd_deselect_cards(struct rt_mmcsd_card *card)
{
    return _mmcsd_select_card(card->host, RT_NULL);
}

rt_int32_t mmcsd_spi_use_crc(struct rt_mmcsd_host *host, rt_int32_t use_crc)
{
    struct rt_mmcsd_cmd cmd;
    rt_int32_t err;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = SPI_CRC_ON_OFF;
    cmd.flags = RESP_SPI_R1;
    cmd.arg = use_crc;

    err = mmcsd_send_cmd(host, &cmd, 0);
    if (!err)
        host->spi_use_crc = use_crc;

    return err;
}

rt_inline void mmcsd_set_iocfg(struct rt_mmcsd_host *host)
{
    struct rt_mmcsd_io_cfg *io_cfg = &host->io_cfg;

    mmcsd_dbg("clock %uHz busmode %u powermode %u cs %u Vdd %u "
        "width %u \n",
         io_cfg->clock, io_cfg->bus_mode,
         io_cfg->power_mode, io_cfg->chip_select, io_cfg->vdd,
         io_cfg->bus_width);

    host->ops->set_iocfg(host, io_cfg);
}

/*
 * Control chip select pin on a host.
 */
void mmcsd_set_chip_select(struct rt_mmcsd_host *host, rt_int32_t mode)
{
    host->io_cfg.chip_select = mode;
    mmcsd_set_iocfg(host);
}

/*
 * Sets the host clock to the highest possible frequency that
 * is below "hz".
 */
void mmcsd_set_clock(struct rt_mmcsd_host *host, rt_uint32_t clk)
{
    if (clk < host->freq_min)
    {
        rt_kprintf("clock too low\n");
    }

    host->io_cfg.clock = clk;
    mmcsd_set_iocfg(host);
}

/*
 * Change the bus mode (open drain/push-pull) of a host.
 */
void mmcsd_set_bus_mode(struct rt_mmcsd_host *host, rt_uint32_t mode)
{
    host->io_cfg.bus_mode = mode;
    mmcsd_set_iocfg(host);
}

/*
 * Change data bus width of a host.
 */
void mmcsd_set_bus_width(struct rt_mmcsd_host *host, rt_uint32_t width)
{
    host->io_cfg.bus_width = width;
    mmcsd_set_iocfg(host);
}

void mmcsd_set_data_timeout(struct rt_mmcsd_data       *data,
                            const struct rt_mmcsd_card *card)
{
    rt_uint32_t mult;

    if (card->card_type == CARD_TYPE_SDIO) 
    {
        data->timeout_ns = 1000000000;  /* SDIO card 1s */
        data->timeout_clks = 0;

        return;
    }

    /*
     * SD cards use a 100 multiplier rather than 10
     */
    mult = (card->card_type == CARD_TYPE_SD) ? 100 : 10;

    /*
     * Scale up the multiplier (and therefore the timeout) by
     * the r2w factor for writes.
     */
    if (data->flags & DATA_DIR_WRITE)
        mult <<= card->csd.r2w_factor;

    data->timeout_ns = card->tacc_ns * mult;
    data->timeout_clks = card->tacc_clks * mult;

    /*
     * SD cards also have an upper limit on the timeout.
     */
    if (card->card_type == CARD_TYPE_SD) 
    {
        rt_uint32_t timeout_us, limit_us;

        timeout_us = data->timeout_ns / 1000;
        timeout_us += data->timeout_clks * 1000 /
            (card->host->io_cfg.clock / 1000);

        if (data->flags & DATA_DIR_WRITE)
            /*
             * The limit is really 250 ms, but that is
             * insufficient for some crappy cards.
             */
            limit_us = 300000;
        else
            limit_us = 100000;

        /*
         * SDHC cards always use these fixed values.
         */
        if (timeout_us > limit_us || card->flags & CARD_FLAG_SDHC) 
        {
            data->timeout_ns = limit_us * 1000; /* SDHC card fixed 250ms */
            data->timeout_clks = 0;
        }
    }

    if (controller_is_spi(card->host)) 
    {
        if (data->flags & DATA_DIR_WRITE) 
        {
            if (data->timeout_ns < 1000000000)
                data->timeout_ns = 1000000000;  /* 1s */
        } 
        else 
        {
            if (data->timeout_ns < 100000000)
                data->timeout_ns =  100000000;  /* 100ms */
        }
    }
}

/*
 * Mask off any voltages we don't support and select
 * the lowest voltage
 */
rt_uint32_t mmcsd_select_voltage(struct rt_mmcsd_host *host, rt_uint32_t ocr)
{
    int bit;

    ocr &= host->valid_ocr;

    bit = __rt_ffs(ocr);
    if (bit) 
    {
        bit -= 1;

        ocr &= 3 << bit;

        host->io_cfg.vdd = bit;
        mmcsd_set_iocfg(host);
    } 
    else 
    {
        rt_kprintf("host doesn't support card's voltages\n");
        ocr = 0;
    }

    return ocr;
}

static void mmcsd_power_up(struct rt_mmcsd_host *host)
{
    int bit = fls(host->valid_ocr) - 1;

    host->io_cfg.vdd = bit;
    if (controller_is_spi(host))
    {
        host->io_cfg.chip_select = MMCSD_CS_HIGH;
        host->io_cfg.bus_mode = MMCSD_BUSMODE_PUSHPULL;
    } 
    else
    {
        host->io_cfg.chip_select = MMCSD_CS_IGNORE;
        host->io_cfg.bus_mode = MMCSD_BUSMODE_OPENDRAIN;
    }
    host->io_cfg.power_mode = MMCSD_POWER_UP;
    host->io_cfg.bus_width = MMCSD_BUS_WIDTH_1;
    mmcsd_set_iocfg(host);

    /*
     * This delay should be sufficient to allow the power supply
     * to reach the minimum voltage.
     */
    mmcsd_delay_ms(10);

    host->io_cfg.clock = host->freq_min;
    host->io_cfg.power_mode = MMCSD_POWER_ON;
    mmcsd_set_iocfg(host);

    /*
     * This delay must be at least 74 clock sizes, or 1 ms, or the
     * time required to reach a stable voltage.
     */
    mmcsd_delay_ms(10);
}

static void mmcsd_power_off(struct rt_mmcsd_host *host)
{
    host->io_cfg.clock = 0;
    host->io_cfg.vdd = 0;
    if (!controller_is_spi(host)) 
    {
        host->io_cfg.bus_mode = MMCSD_BUSMODE_OPENDRAIN;
        host->io_cfg.chip_select = MMCSD_CS_IGNORE;
    }
    host->io_cfg.power_mode = MMCSD_POWER_OFF;
    host->io_cfg.bus_width = MMCSD_BUS_WIDTH_1;
    mmcsd_set_iocfg(host);
}

void mmcsd_change(struct rt_mmcsd_host *host)
{
    rt_mb_send(&mmcsd_detect_mb, (rt_uint32_t)host);
}

void mmcsd_detect(void *param)
{
    struct rt_mmcsd_host *host;
    rt_uint32_t  ocr;
    rt_int32_t  err;

    while (1) 
    {
        if (rt_mb_recv(&mmcsd_detect_mb, (rt_uint32_t*)&host, RT_WAITING_FOREVER) == RT_EOK)
        {
            if (host->card == RT_NULL)
            {
                mmcsd_host_lock(host);
                mmcsd_power_up(host);
                mmcsd_go_idle(host);

                mmcsd_send_if_cond(host, host->valid_ocr);

                err = sdio_io_send_op_cond(host, 0, &ocr);
                if (!err)
                {
                    if (init_sdio(host, ocr))
                        mmcsd_power_off(host);
                    mmcsd_host_unlock(host);
                    continue;
                }

                /*
                 * detect SD card
                 */
                err = mmcsd_send_app_op_cond(host, 0, &ocr);
                if (!err) 
                {
                    if (init_sd(host, ocr))
                        mmcsd_power_off(host);
                    mmcsd_host_unlock(host);
                    continue;
                }
                mmcsd_host_unlock(host);
            }
        }
    }
}

struct rt_mmcsd_host *mmcsd_alloc_host(void)
{
    struct rt_mmcsd_host *host;

    host = rt_malloc(sizeof(struct rt_mmcsd_host));
    if (!host) 
    {
        rt_kprintf("alloc host failed\n");

        return RT_NULL;
    }

    rt_memset(host, 0, sizeof(struct rt_mmcsd_host));

    host->max_seg_size = 65535;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;

    rt_sem_init(&host->bus_lock, "sd_bus_lock", 1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&host->sem_ack, "sd_ack", 0, RT_IPC_FLAG_FIFO);

    return host;
}

void mmcsd_free_host(struct rt_mmcsd_host *host)
{
    rt_sem_detach(&host->bus_lock);
    rt_sem_detach(&host->sem_ack);
    rt_free(host);
}

void rt_mmcsd_core_init(void)
{
    rt_err_t ret;

    /* init detect sd cart thread */
    /* init mailbox and create detect sd card thread */
    ret = rt_mb_init(&mmcsd_detect_mb, "mmcsdmb",
        &mmcsd_detect_mb_pool[0], sizeof(mmcsd_detect_mb_pool),
        RT_IPC_FLAG_FIFO);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_thread_init(&mmcsd_detect_thread, "mmcsd_detect", mmcsd_detect, RT_NULL, 
                 &mmcsd_stack[0], RT_MMCSD_STACK_SIZE, RT_MMCSD_THREAD_PREORITY, 20);
    if (ret == RT_EOK) 
    {
        rt_thread_startup(&mmcsd_detect_thread);
    }

    rt_sdio_init();
}
