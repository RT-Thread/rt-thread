/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 */

#include <rtthread.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sd.h>
#include <drivers/dev_mmc.h>
#include <drivers/dev_sdio.h>
#include <string.h>

#define DBG_TAG               "SDIO"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

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
static struct rt_mailbox mmcsd_hotpluge_mb;
static rt_uint32_t mmcsd_hotpluge_mb_pool[4];

void mmcsd_host_lock(struct rt_mmcsd_host *host)
{
    rt_mutex_take(&host->bus_lock, RT_WAITING_FOREVER);
}

void mmcsd_host_unlock(struct rt_mmcsd_host *host)
{
    rt_mutex_release(&host->bus_lock);
}

void mmcsd_req_complete(struct rt_mmcsd_host *host)
{
    rt_sem_release(&host->sem_ack);
}

void mmcsd_send_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    do
    {
        req->cmd->retries--;
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
    while (req->cmd->err && (req->cmd->retries > 0));


}

rt_int32_t mmcsd_send_cmd(struct rt_mmcsd_host *host,
                          struct rt_mmcsd_cmd  *cmd,
                          int                   retries)
{
    struct rt_mmcsd_req req;

    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(cmd->resp, 0, sizeof(cmd->resp));
    cmd->retries = retries;

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
        rt_thread_mdelay(1);
    }

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = GO_IDLE_STATE;
    cmd.arg = 0;
    cmd.flags = RESP_SPI_R1 | RESP_NONE | CMD_BC;

    err = mmcsd_send_cmd(host, &cmd, 0);

    rt_thread_mdelay(1);

    if (!controller_is_spi(host))
    {
        mmcsd_set_chip_select(host, MMCSD_CS_IGNORE);
        rt_thread_mdelay(1);
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
        LOG_E("allocate memory failed!");

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

    for (i = 0; i < 4; i++)
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

    buf = (rt_uint32_t *)rt_malloc(16);
    if (!buf)
    {
        LOG_E("allocate memory failed!");

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

    for (i = 0; i < 4; i++)
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
        LOG_W("clock too low!");
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

void mmcsd_set_timing(struct rt_mmcsd_host *host, rt_uint32_t timing)
{
    host->io_cfg.timing = timing;
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
    extern int __rt_ffs(int value);

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
        LOG_W("host doesn't support card's voltages!");
        ocr = 0;
    }

    return ocr;
}

rt_err_t mmcsd_set_signal_voltage(struct rt_mmcsd_host *host, unsigned char signal_voltage)
{
    rt_err_t err = RT_EOK;
    unsigned char old_signal_voltage = host->io_cfg.signal_voltage;

    host->io_cfg.signal_voltage = signal_voltage;
    if (host->ops->signal_voltage_switch)
    {
        err = host->ops->signal_voltage_switch(host, &host->io_cfg);
    }

    if (err)
    {
        host->io_cfg.signal_voltage = old_signal_voltage;
    }

    return err;
}

void mmcsd_set_initial_signal_voltage(struct rt_mmcsd_host *host)
{
    /* 3.3V -> 1.8v -> 1.2v */
    if (!mmcsd_set_signal_voltage(host, MMCSD_SIGNAL_VOLTAGE_330))
    {
        LOG_D("Initial signal voltage of %sv", "3.3");
    }
    else if (!mmcsd_set_signal_voltage(host, MMCSD_SIGNAL_VOLTAGE_180))
    {
        LOG_D("Initial signal voltage of %sv", "1.8");
    }
    else if (!mmcsd_set_signal_voltage(host, MMCSD_SIGNAL_VOLTAGE_120))
    {
        LOG_D("Initial signal voltage of %sv", "1.2");
    }
}

rt_err_t mmcsd_host_set_uhs_voltage(struct rt_mmcsd_host *host)
{
    rt_uint32_t old_clock = host->io_cfg.clock;

    host->io_cfg.clock = 0;
    mmcsd_set_iocfg(host);

    if (mmcsd_set_signal_voltage(host, MMCSD_SIGNAL_VOLTAGE_180))
    {
        return -RT_ERROR;
    }

    /* Keep clock gated for at least 10 ms, though spec only says 5 ms */
    rt_thread_mdelay(10);

    host->io_cfg.clock = old_clock;
    mmcsd_set_iocfg(host);

    return RT_EOK;
}

static void mmcsd_power_cycle(struct rt_mmcsd_host *host, rt_uint32_t ocr);

rt_err_t mmcsd_set_uhs_voltage(struct rt_mmcsd_host *host, rt_uint32_t ocr)
{
    rt_err_t err = RT_EOK;
    struct rt_mmcsd_cmd cmd;

    if (!host->ops->signal_voltage_switch)
    {
        return -RT_EINVAL;
    }

    if (!host->ops->card_busy)
    {
        LOG_W("%s: Cannot verify signal voltage switch", host->name);
    }

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = VOLTAGE_SWITCH;
    cmd.arg = 0;
    cmd.flags = RESP_R1 | CMD_AC;

    err = mmcsd_send_cmd(host, &cmd, 0);
    if (err)
    {
        goto power_cycle;
    }

    if (!controller_is_spi(host) && (cmd.resp[0] & R1_ERROR))
    {
        return -RT_EIO;
    }

    /*
     * The card should drive cmd and dat[0:3] low immediately
     * after the response of cmd11, but wait 1 ms to be sure
     */
    rt_thread_mdelay(1);
    if (host->ops->card_busy && !host->ops->card_busy(host))
    {
        err = -RT_ERROR;
        goto power_cycle;
    }

    if (mmcsd_host_set_uhs_voltage(host))
    {
        /*
         * Voltages may not have been switched, but we've already
         * sent CMD11, so a power cycle is required anyway
         */
        err = -RT_ERROR;
        goto power_cycle;
    }

    /* Wait for at least 1 ms according to spec */
    rt_thread_mdelay(1);

    /*
     * Failure to switch is indicated by the card holding
     * dat[0:3] low
     */
    if (host->ops->card_busy && host->ops->card_busy(host))
    {
        err = -RT_ERROR;
    }

power_cycle:
    if (err)
    {
        LOG_D("%s: Signal voltage switch failed, power cycling card", host->name);
        mmcsd_power_cycle(host, ocr);
    }

    return err;
}

static const rt_uint8_t tuning_blk_pattern_4bit[] =
{
    0xff, 0x0f, 0xff, 0x00, 0xff, 0xcc, 0xc3, 0xcc,
    0xc3, 0x3c, 0xcc, 0xff, 0xfe, 0xff, 0xfe, 0xef,
    0xff, 0xdf, 0xff, 0xdd, 0xff, 0xfb, 0xff, 0xfb,
    0xbf, 0xff, 0x7f, 0xff, 0x77, 0xf7, 0xbd, 0xef,
    0xff, 0xf0, 0xff, 0xf0, 0x0f, 0xfc, 0xcc, 0x3c,
    0xcc, 0x33, 0xcc, 0xcf, 0xff, 0xef, 0xff, 0xee,
    0xff, 0xfd, 0xff, 0xfd, 0xdf, 0xff, 0xbf, 0xff,
    0xbb, 0xff, 0xf7, 0xff, 0xf7, 0x7f, 0x7b, 0xde,
};

static const rt_uint8_t tuning_blk_pattern_8bit[] =
{
    0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
    0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc, 0xcc,
    0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff, 0xff,
    0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee, 0xff,
    0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd, 0xdd,
    0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff, 0xbb,
    0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff,
    0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee, 0xff,
    0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00,
    0x00, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc,
    0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff,
    0xff, 0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee,
    0xff, 0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd,
    0xdd, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff,
    0xbb, 0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff,
    0xff, 0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee,
};

rt_err_t mmcsd_send_tuning(struct rt_mmcsd_host *host, rt_uint32_t opcode, rt_err_t *cmd_error)
{
    rt_err_t err = RT_EOK;
    int size;
    rt_uint8_t *data_buf;
    const rt_uint8_t *tuning_block_pattern;
    struct rt_mmcsd_req req = {};
    struct rt_mmcsd_cmd cmd = {};
    struct rt_mmcsd_data data = {};
    struct rt_mmcsd_io_cfg *io_cfg = &host->io_cfg;

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        tuning_block_pattern = tuning_blk_pattern_8bit;
        size = sizeof(tuning_blk_pattern_8bit);
    }
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        tuning_block_pattern = tuning_blk_pattern_4bit;
        size = sizeof(tuning_blk_pattern_4bit);
    }
    else
    {
        return -RT_EINVAL;
    }

    data_buf = rt_malloc(size);
    if (!data_buf)
    {
        return -RT_ENOMEM;
    }

    rt_memset(data_buf, 0, size);
    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));
    rt_memset(&data, 0, sizeof(struct rt_mmcsd_data));

    req.cmd = &cmd;
    req.data = &data;

    cmd.cmd_code = opcode;
    cmd.flags = RESP_R1 | CMD_ADTC;

    data.blksize = size;
    data.blks = 1;
    data.flags = DATA_DIR_READ;

    /*
     * According to the tuning specs, Tuning process
     * is normally shorter 40 executions of CMD19,
     * and timeout value should be shorter than 150 ms
     */
    data.timeout_ns = 150 * 1000000;

    mmcsd_send_request(host, &req);

    if (cmd_error)
    {
        *cmd_error = cmd.err;
    }

    if (cmd.err)
    {
        err = cmd.err;
        goto out_free;
    }

    if (data.err)
    {
        err = data.err;
        goto out_free;
    }

    if (rt_memcmp(data_buf, tuning_block_pattern, size))
    {
        err = -RT_EIO;
    }

out_free:
    rt_free(data_buf);

    return err;
}

rt_err_t mmcsd_send_abort_tuning(struct rt_mmcsd_host *host, rt_uint32_t opcode)
{
    struct rt_mmcsd_cmd cmd = {};

    /*
     * eMMC specification specifies that CMD12 can be used to stop a tuning
     * command, but SD specification does not, so do nothing unless it is eMMC.
     */
    if (opcode != SEND_TUNING_BLOCK_HS200)
    {
        return 0;
    }

    cmd.cmd_code = STOP_TRANSMISSION;
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_AC;

    /*
     * For drivers that override R1 to R1b, set an arbitrary timeout based
     * on the tuning timeout i.e. 150ms.
     */
    cmd.busy_timeout = 150;

    return mmcsd_send_cmd(host, &cmd, 0);
}

static void mmcsd_power_up(struct rt_mmcsd_host *host)
{
    int bit = __rt_fls(host->valid_ocr) - 1;

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

    mmcsd_set_initial_signal_voltage(host);

    /*
     * This delay should be sufficient to allow the power supply
     * to reach the minimum voltage.
     */
    rt_thread_mdelay(10);

    host->io_cfg.clock = host->freq_min;
    host->io_cfg.power_mode = MMCSD_POWER_ON;
    mmcsd_set_iocfg(host);

    /*
     * This delay must be at least 74 clock sizes, or 1 ms, or the
     * time required to reach a stable voltage.
     */
    rt_thread_mdelay(10);
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

static void mmcsd_power_cycle(struct rt_mmcsd_host *host, rt_uint32_t ocr)
{
    mmcsd_power_off(host);

    /* Wait at least 1 ms according to SD spec */
    rt_thread_mdelay(1);

    mmcsd_power_up(host);
    mmcsd_select_voltage(host, ocr);
}

int mmcsd_wait_cd_changed(rt_int32_t timeout)
{
    struct rt_mmcsd_host *host;
    if (rt_mb_recv(&mmcsd_hotpluge_mb, (rt_ubase_t *)&host, timeout) == RT_EOK)
    {
        if (host->card == RT_NULL)
        {
            return MMCSD_HOST_UNPLUGED;
        }
        else
        {
            return MMCSD_HOST_PLUGED;
        }
    }
    return -RT_ETIMEOUT;
}
RTM_EXPORT(mmcsd_wait_cd_changed);

void mmcsd_change(struct rt_mmcsd_host *host)
{
    rt_mb_send(&mmcsd_detect_mb, (rt_ubase_t)host);
}

void mmcsd_detect(void *param)
{
    struct rt_mmcsd_host *host;
    rt_uint32_t  ocr;
    rt_int32_t  err;

    while (1)
    {
        if (rt_mb_recv(&mmcsd_detect_mb, (rt_ubase_t *)&host, RT_WAITING_FOREVER) == RT_EOK)
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
                    rt_mb_send(&mmcsd_hotpluge_mb, (rt_ubase_t)host);
                    continue;
                }

                /*
                 * detect mmc card
                 */
                err = mmc_send_op_cond(host, 0, &ocr);
                if (!err)
                {
                    if (init_mmc(host, ocr))
                        mmcsd_power_off(host);
                    mmcsd_host_unlock(host);
                    rt_mb_send(&mmcsd_hotpluge_mb, (rt_ubase_t)host);
                    continue;
                }
                mmcsd_host_unlock(host);
            }
            else
            {
                /* card removed */
                mmcsd_host_lock(host);
                if (host->card->sdio_function_num != 0)
                {
                    LOG_W("unsupport sdio card plug out!");
                }
                else
                {
                    rt_mmcsd_blk_remove(host->card);
                    rt_free(host->card);

                    host->card = RT_NULL;
                }
                mmcsd_host_unlock(host);
                rt_mb_send(&mmcsd_hotpluge_mb, (rt_ubase_t)host);
            }
        }
    }
}

void mmcsd_host_init(struct rt_mmcsd_host *host)
{
    rt_memset(host, 0, sizeof(struct rt_mmcsd_host));
    strncpy(host->name, "sd", sizeof(host->name) - 1);
    host->max_seg_size = 65535;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;

    rt_mutex_init(&host->bus_lock, "sd_bus_lock", RT_IPC_FLAG_FIFO);
    rt_sem_init(&host->sem_ack, "sd_ack", 0, RT_IPC_FLAG_FIFO);
}

struct rt_mmcsd_host *mmcsd_alloc_host(void)
{
    struct rt_mmcsd_host *host;

    host = rt_malloc(sizeof(struct rt_mmcsd_host));
    if (!host)
    {
        LOG_E("alloc host failed");

        return RT_NULL;
    }

    mmcsd_host_init(host);

    return host;
}

void mmcsd_free_host(struct rt_mmcsd_host *host)
{
    rt_mutex_detach(&host->bus_lock);
    rt_sem_detach(&host->sem_ack);
    rt_free(host);
}

rt_int32_t mmcsd_excute_tuning(struct rt_mmcsd_card *card)
{
    struct rt_mmcsd_host *host = card->host;
    rt_int32_t opcode;

    if (!host->ops->execute_tuning)
        return RT_EOK;

    if (card->card_type == CARD_TYPE_MMC)
        opcode = SEND_TUNING_BLOCK_HS200;
    else
        opcode = SEND_TUNING_BLOCK;

    return host->ops->execute_tuning(host, opcode);;
}

int rt_mmcsd_core_init(void)
{
    rt_err_t ret;

    /* initialize detect SD cart thread */
    /* initialize mailbox and create detect SD card thread */
    ret = rt_mb_init(&mmcsd_detect_mb, "mmcsdmb",
                     &mmcsd_detect_mb_pool[0], sizeof(mmcsd_detect_mb_pool) / sizeof(mmcsd_detect_mb_pool[0]),
                     RT_IPC_FLAG_FIFO);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_mb_init(&mmcsd_hotpluge_mb, "mmcsdhotplugmb",
                     &mmcsd_hotpluge_mb_pool[0], sizeof(mmcsd_hotpluge_mb_pool) / sizeof(mmcsd_hotpluge_mb_pool[0]),
                     RT_IPC_FLAG_FIFO);
    RT_ASSERT(ret == RT_EOK);
    ret = rt_thread_init(&mmcsd_detect_thread, "mmcsd_detect", mmcsd_detect, RT_NULL,
                         &mmcsd_stack[0], RT_MMCSD_STACK_SIZE, RT_MMCSD_THREAD_PREORITY, 20);
    if (ret == RT_EOK)
    {
        rt_thread_startup(&mmcsd_detect_thread);
    }

    rt_sdio_init();

    return 0;
}
INIT_PREV_EXPORT(rt_mmcsd_core_init);

