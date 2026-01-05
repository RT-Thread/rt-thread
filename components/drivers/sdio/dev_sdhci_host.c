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
#include <rtdevice.h>

#define DBG_TAG "SDHCI"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

#include "dev_sdio_dm.h"
#include "dev_sdhci_dm.h"

static void rt_plat_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    rt_uint32_t flags = req->cmd->flags;
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    switch (flags & RESP_MASK)
    {
    case RESP_NONE:
        flags |= MMC_RSP_NONE;
        break;
    case RESP_R1:
        flags |= MMC_RSP_R1;
        break;
    case RESP_R1B:
        flags |= MMC_RSP_R1B;
        break;
    case RESP_R2:
        flags |= MMC_RSP_R2;
        break;
    case RESP_R3:
        flags |= MMC_RSP_R3;
        break;
    case RESP_R4:
        flags |= MMC_RSP_R4;
        break;
    case RESP_R5:
        flags |= MMC_RSP_R5;
        break;
    case RESP_R6:
        flags |= MMC_RSP_R6;
        break;
    case RESP_R7:
        flags |= MMC_RSP_R7;
        break;
    }

    if (req->data)
    {
        if ((rt_uint64_t)rt_kmem_v2p(req->data->buf) > 0xffffffff)
        {
            void *req_buf = RT_NULL;
            void *dma_buffer = rt_malloc(req->data->blks * req->data->blksize);

            if (req->data->flags & DATA_DIR_WRITE)
            {
                rt_memcpy(dma_buffer, req->data->buf, req->data->blks * req->data->blksize);
                req_buf        = req->data->buf;
                req->data->buf = dma_buffer;
            }
            else if (req->data->flags & DATA_DIR_READ)
            {
                req_buf        = req->data->buf;
                req->data->buf = dma_buffer;
            }
            req->cmd->flags |= flags;
            mmc->ops->request(mmc, req);

            rt_sem_take(&host->sem_ack, RT_WAITING_FOREVER);

            if (req->data->flags & DATA_DIR_READ)
            {
                rt_memcpy(req_buf, dma_buffer, req->data->blksize * req->data->blks);
                req->data->buf = req_buf;
            }
            else
            {
                req->data->buf = req_buf;
            }

            rt_free(dma_buffer);
            rt_sem_release(&host->sem_ack);
        }
        else
        {
            req->cmd->flags |= flags;
            mmc->ops->request(mmc, req);
        }
    }
    else
    {
        req->cmd->flags |= flags;
        mmc->ops->request(mmc, req);
    }
}

static void rt_plat_set_ioconfig(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *iocfg)
{
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    LOG_D("clock: %u, width: %u, power: %u, vdd: %u, timing: %u",
          iocfg->clock, iocfg->bus_width,
          iocfg->power_mode, iocfg->vdd, iocfg->timing);

    mmc->ops->set_ios(mmc, iocfg);
}

static rt_int32_t rt_plat_get_card_status(struct rt_mmcsd_host *host)
{
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    return mmc->ops->get_cd(mmc);
}

static rt_int32_t rt_plat_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode)
{
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    return mmc->ops->execute_tuning(mmc, opcode);
}

static void rt_plat_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    return mmc->ops->enable_sdio_irq(mmc, en);
}

static rt_bool_t rt_plat_card_busy(struct rt_mmcsd_host *host)
{
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    return mmc->ops->card_busy(mmc);
}

static rt_err_t rt_plat_signal_voltage_switch(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    struct rt_mmc_host *mmc = rt_container_of(host, struct rt_mmc_host, rthost);

    return mmc->ops->start_signal_voltage_switch(mmc, io_cfg);
}

static const struct rt_mmcsd_host_ops rt_mmcsd_ops =
{
    .request                = rt_plat_request,
    .set_iocfg              = rt_plat_set_ioconfig,
    .get_card_status        = rt_plat_get_card_status,
    .enable_sdio_irq        = rt_plat_enable_sdio_irq,
    .execute_tuning         = rt_plat_execute_tuning,
    .card_busy              = rt_plat_card_busy,
    .signal_voltage_switch  = rt_plat_signal_voltage_switch,
};

void rt_mmc_request_done(struct rt_mmc_host *host, struct rt_mmcsd_req *mrq)
{
    mmcsd_req_complete(&host->rthost);
}

/* Add host in rtt while sdhci complete */
rt_err_t rt_mmc_add_host(struct rt_mmc_host *mmc)
{
    mmc->rthost.ops           = &rt_mmcsd_ops;
    mmc->rthost.flags         = mmc->caps;
    mmc->rthost.freq_max      = mmc->f_max;
    mmc->rthost.freq_min      = mmc->f_min;
    mmc->rthost.max_dma_segs  = mmc->max_segs;
    mmc->rthost.max_seg_size  = mmc->max_seg_size;
    mmc->rthost.max_blk_size  = mmc->max_blk_size;
    mmc->rthost.max_blk_count = mmc->max_blk_count;
    mmc->rthost.valid_ocr     = mmc->ocr_avail;

    mmcsd_change(&mmc->rthost);

    return RT_EOK;
}

struct rt_mmc_host *rt_mmc_alloc_host(int extra, struct rt_device *dev)
{
    struct rt_mmc_host *mmc;

    mmc = rt_calloc(1, sizeof(*mmc) + extra);
    if (mmc)
    {
        mmc->parent = dev;
        mmcsd_host_init(&mmc->rthost);
    }

    return mmc;
}

void rt_mmc_remove_host(struct rt_mmc_host *host)
{
    rt_free(host);
}

rt_err_t rt_mmc_abort_tuning(struct rt_mmc_host *host, rt_uint32_t opcode)
{
    return RT_EOK;
}

rt_err_t rt_mmc_gpio_get_cd(struct rt_mmc_host *host)
{
    return -RT_ENOSYS;
}

void rt_mmc_detect_change(struct rt_mmc_host *host, rt_ubase_t delay)
{
}

rt_bool_t rt_mmc_can_gpio_ro(struct rt_mmc_host *host)
{
    return RT_FALSE;
}

rt_err_t rt_mmc_gpio_get_ro(struct rt_mmc_host *host)
{
    return RT_EOK;
}

rt_err_t rt_mmc_send_abort_tuning(struct rt_mmc_host *host, rt_uint32_t opcode)
{
    return RT_EOK;
}

rt_err_t rt_mmc_of_parse(struct rt_mmc_host *host)
{
    rt_err_t err;
    struct rt_device *dev = host->parent;

    if (!dev || !dev->ofw_node)
    {
        return RT_EOK;
    }

    err = sdio_ofw_parse(dev->ofw_node, &host->rthost);
    if (err)
    {
        return err;
    }

    host->caps |= host->rthost.flags;

    if (rt_dm_dev_prop_read_bool(dev, "no-sdio"))
    {
        host->caps2 |= MMC_CAP2_NO_SDIO;
    }

    if (rt_dm_dev_prop_read_bool(dev, "no-sd"))
    {
        host->caps2 |= MMC_CAP2_NO_SD;
    }

    return RT_EOK;
}

void rt_mmc_free_host(struct rt_mmc_host *host)
{
}

rt_bool_t rt_mmc_can_gpio_cd(struct rt_mmc_host *host)
{
    return RT_FALSE;
}
