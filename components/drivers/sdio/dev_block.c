/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 * 2023-08-08     GuEe-GUI      port to the block
 */

#include <rtthread.h>
#include <drivers/blk.h>
#include <drivers/misc.h>
#include <drivers/dev_mmcsd_core.h>

#define DBG_TAG               "SDIO"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

#ifndef RT_MMCSD_MAX_PARTITION
#define RT_MMCSD_MAX_PARTITION 16
#endif

struct mmcsd_blk_device
{
    struct rt_blk_disk parent;
    struct rt_mmcsd_card *card;

    rt_size_t max_req_size;
    struct rt_device_blk_geometry geometry;
};

#define raw_to_mmcsd_blk(raw) rt_container_of(raw, struct mmcsd_blk_device, parent)

#ifdef RT_USING_DM
static struct rt_dm_ida sdio_ida = RT_DM_IDA_INIT(SDIO);
#endif

static int __send_status(struct rt_mmcsd_card *card, rt_uint32_t *status, unsigned retries)
{
    int err;
    struct rt_mmcsd_cmd cmd;

    cmd.busy_timeout = 0;
    cmd.cmd_code = SEND_STATUS;
    cmd.arg = card->rca << 16;
    cmd.flags = RESP_R1 | CMD_AC;
    err = mmcsd_send_cmd(card->host, &cmd, retries);
    if (err)
        return err;

    if (status)
        *status = cmd.resp[0];

    return 0;
}

static int card_busy_detect(struct rt_mmcsd_card *card, unsigned int timeout_ms,
                            rt_uint32_t *resp_errs)
{
    int timeout = rt_tick_from_millisecond(timeout_ms);
    int err = 0;
    rt_uint32_t status;
    rt_tick_t start;

    start = rt_tick_get();
    do
    {
        rt_bool_t out = (int)(rt_tick_get() - start) > timeout;

        err = __send_status(card, &status, 5);
        if (err)
        {
            LOG_E("error %d requesting status", err);
            return err;
        }

        /* Accumulate any response error bits seen */
        if (resp_errs)
            *resp_errs |= status;

        if (out)
        {
            LOG_E("wait card busy timeout");
            return -RT_ETIMEOUT;
        }
        /*
         * Some cards mishandle the status bits,
         * so make sure to check both the busy
         * indication and the card state.
         */
    }
    while (!(status & R1_READY_FOR_DATA) ||
            (R1_CURRENT_STATE(status) == 7));

    return err;
}

rt_int32_t mmcsd_num_wr_blocks(struct rt_mmcsd_card *card)
{
    rt_int32_t err;
    rt_uint32_t blocks;

    struct rt_mmcsd_req req;
    struct rt_mmcsd_cmd cmd;
    struct rt_mmcsd_data data;
    rt_uint32_t timeout_us;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = APP_CMD;
    cmd.arg = card->rca << 16;
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_AC;

    err = mmcsd_send_cmd(card->host, &cmd, 0);
    if (err)
        return -RT_ERROR;
    if (!controller_is_spi(card->host) && !(cmd.resp[0] & R1_APP_CMD))
        return -RT_ERROR;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = SD_APP_SEND_NUM_WR_BLKS;
    cmd.arg = 0;
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_ADTC;

    rt_memset(&data, 0, sizeof(struct rt_mmcsd_data));

    data.timeout_ns = card->tacc_ns * 100;
    data.timeout_clks = card->tacc_clks * 100;

    timeout_us = data.timeout_ns / 1000;
    timeout_us += data.timeout_clks * 1000 /
                  (card->host->io_cfg.clock / 1000);

    if (timeout_us > 100000)
    {
        data.timeout_ns = 100000000;
        data.timeout_clks = 0;
    }

    data.blksize = 4;
    data.blks = 1;
    data.flags = DATA_DIR_READ;
    data.buf = &blocks;

    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));

    req.cmd = &cmd;
    req.data = &data;

    mmcsd_send_request(card->host, &req);

    if (cmd.err || data.err)
        return -RT_ERROR;

    return blocks;
}

static rt_err_t rt_mmcsd_req_blk(struct rt_mmcsd_card *card,
                                 rt_uint32_t           sector,
                                 void                 *buf,
                                 rt_size_t             blks,
                                 rt_uint8_t            dir)
{
    struct rt_mmcsd_cmd  cmd, stop;
    struct rt_mmcsd_data  data;
    struct rt_mmcsd_req  req;
    struct rt_mmcsd_host *host = card->host;
    rt_uint32_t r_cmd, w_cmd;

    mmcsd_host_lock(host);
    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));
    rt_memset(&stop, 0, sizeof(struct rt_mmcsd_cmd));
    rt_memset(&data, 0, sizeof(struct rt_mmcsd_data));
    req.cmd = &cmd;
    req.data = &data;

    cmd.arg = sector;
    if (!(card->flags & CARD_FLAG_SDHC))
    {
        cmd.arg <<= 9;
    }
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_ADTC;

    data.blksize = SECTOR_SIZE;
    data.blks  = blks;

    if (blks > 1)
    {
        if (!controller_is_spi(card->host) || !dir)
        {
            req.stop = &stop;
            stop.cmd_code = STOP_TRANSMISSION;
            stop.arg = 0;
            stop.flags = RESP_SPI_R1B | RESP_R1B | CMD_AC;
        }
        r_cmd = READ_MULTIPLE_BLOCK;
        w_cmd = WRITE_MULTIPLE_BLOCK;
    }
    else
    {
        req.stop = RT_NULL;
        r_cmd = READ_SINGLE_BLOCK;
        w_cmd = WRITE_BLOCK;
    }

    if (!controller_is_spi(card->host) && (card->flags & 0x8000))
    {
        /* last request is WRITE,need check busy */
        card_busy_detect(card, 10000, RT_NULL);
    }

    if (!dir)
    {
        cmd.cmd_code = r_cmd;
        data.flags |= DATA_DIR_READ;
        card->flags &= 0x7fff;
    }
    else
    {
        cmd.cmd_code = w_cmd;
        data.flags |= DATA_DIR_WRITE;
        card->flags |= 0x8000;
    }

    mmcsd_set_data_timeout(&data, card);
    data.buf = buf;

    mmcsd_send_request(host, &req);

    mmcsd_host_unlock(host);

    if (cmd.err || data.err || stop.err)
    {
        LOG_E("mmcsd request blocks error");
        LOG_E("%d,%d,%d, 0x%08x,0x%08x",
              cmd.err, data.err, stop.err, data.flags, sector);

        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_int32_t mmcsd_set_blksize(struct rt_mmcsd_card *card)
{
    struct rt_mmcsd_cmd cmd;
    int err;

    /* Block-addressed cards ignore MMC_SET_BLOCKLEN. */
    if (card->flags & CARD_FLAG_SDHC)
        return 0;

    mmcsd_host_lock(card->host);
    cmd.cmd_code = SET_BLOCKLEN;
    cmd.arg = 512;
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_AC;
    err = mmcsd_send_cmd(card->host, &cmd, 5);
    mmcsd_host_unlock(card->host);

    if (err)
    {
        LOG_E("MMCSD: unable to set block size to %d: %d", cmd.arg, err);

        return -RT_ERROR;
    }

    return 0;
}

static rt_ssize_t mmcsd_blk_read(struct rt_blk_disk *disk, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    rt_err_t err;
    rt_size_t offset = 0;
    rt_size_t req_size = 0;
    rt_size_t remain_size = sector_count;
    void *rd_ptr = (void *)buffer;
    struct mmcsd_blk_device *blk_dev = raw_to_mmcsd_blk(disk);

    while (remain_size)
    {
        req_size = rt_min_t(rt_size_t, remain_size, blk_dev->max_req_size);

        err = rt_mmcsd_req_blk(blk_dev->card, sector + offset, rd_ptr, req_size, 0);

        if (err)
        {
            return err;
        }

        offset += req_size;
        rd_ptr = (void *)((rt_uint8_t *)rd_ptr + (req_size << 9));
        remain_size -= req_size;
    }

    return sector_count - remain_size;
}

static rt_ssize_t mmcsd_blk_write(struct rt_blk_disk *disk, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    rt_err_t err;
    rt_size_t offset = 0;
    rt_size_t req_size = 0;
    rt_size_t remain_size = sector_count;
    void *wr_ptr = (void *)buffer;
    struct mmcsd_blk_device *blk_dev = raw_to_mmcsd_blk(disk);

    while (remain_size)
    {
        req_size = rt_min_t(rt_size_t, remain_size, blk_dev->max_req_size);

        err = rt_mmcsd_req_blk(blk_dev->card, sector + offset, wr_ptr, req_size, 1);

        if (err)
        {
            return err;
        }

        offset += req_size;
        wr_ptr = (void *)((rt_uint8_t *)wr_ptr + (req_size << 9));
        remain_size -= req_size;
    }

    return sector_count - remain_size;
}

static rt_err_t mmcsd_blk_getgeome(struct rt_blk_disk *disk,
        struct rt_device_blk_geometry *geometry)
{
    struct mmcsd_blk_device *blk_dev = raw_to_mmcsd_blk(disk);

    rt_memcpy(geometry, &blk_dev->geometry, sizeof(*geometry));

    return RT_EOK;
}

static const struct rt_blk_disk_ops mmcsd_blk_ops =
{
    .read = mmcsd_blk_read,
    .write = mmcsd_blk_write,
    .getgeome = mmcsd_blk_getgeome,
};

rt_int32_t rt_mmcsd_blk_probe(struct rt_mmcsd_card *card)
{
    rt_err_t err;
    struct rt_mmcsd_host *host = card->host;
    struct mmcsd_blk_device *blk_dev = rt_calloc(1, sizeof(*blk_dev));

    if (!blk_dev)
    {
        return -RT_ENOMEM;
    }
    card->blk_dev = blk_dev;

#ifdef RT_USING_DM
    blk_dev->parent.ida = &sdio_ida;
#endif
    blk_dev->parent.parallel_io = RT_FALSE;
    blk_dev->parent.removable = controller_is_removable(host);
    blk_dev->parent.ops = &mmcsd_blk_ops;
    blk_dev->parent.max_partitions = RT_MMCSD_MAX_PARTITION;

    blk_dev->card = card;
    blk_dev->max_req_size = rt_min_t(rt_size_t,
            host->max_dma_segs * host->max_seg_size,
            host->max_blk_count * host->max_blk_size) >> 9;
    blk_dev->geometry.bytes_per_sector = 1 << 9;
    blk_dev->geometry.block_size = card->card_blksize;
    blk_dev->geometry.sector_count = card->card_capacity * (1024 / 512);

    /* Set blk size before partitions probe, Why? */
    if ((err = mmcsd_set_blksize(card)))
    {
        goto _fail;
    }
    rt_thread_mdelay(1);

#ifdef RT_USING_DM
    rt_dm_dev_set_name(&blk_dev->parent.parent, host->name);
#else
    rt_strncpy(blk_dev->parent.parent.parent.name, host->name, RT_NAME_MAX);
#endif

    if ((err = rt_hw_blk_disk_register(&blk_dev->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    card->blk_dev = RT_NULL;
    free(blk_dev);

    return err;
}

void rt_mmcsd_blk_remove(struct rt_mmcsd_card *card)
{
    struct mmcsd_blk_device *blk_dev = card->blk_dev;

    if (!blk_dev)
    {
        return;
    }

    if (!rt_hw_blk_disk_unregister(&blk_dev->parent))
    {
        card->blk_dev = RT_NULL;
        rt_free(blk_dev);
    }
}
