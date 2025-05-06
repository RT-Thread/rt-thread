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
#include <rtdbg.h>
#include <mmu.h>
#include <drivers/core/dm.h>


static void plat_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct mmc_host *mmc   = (struct mmc_host *)host;
    rt_uint32_t      flags = req->cmd->flags;

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
            void *dma_buffer = rt_malloc(ARCH_PAGE_SIZE);
            void *req_buf    = NULL;

            if (req->data->blks * req->data->blksize > ARCH_PAGE_SIZE)
            {
                dma_buffer = rt_realloc(dma_buffer, req->data->blks * req->data->blksize);
            }

            if (req->data->flags & DATA_DIR_WRITE)
            {
                rt_memcpy(dma_buffer, req->data->buf, req->data->blks * req->data->blksize);
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

static void plat_set_ioconfig(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *iocfg)
{
    struct mmc_host *mmc = (struct mmc_host *)host;

    LOG_D("clock:%d,width:%d,power:%d,vdd:%d,timing:%d\n",
          iocfg->clock, iocfg->bus_width,
          iocfg->power_mode, iocfg->vdd, iocfg->timing);

    mmc->ops->set_ios(mmc, iocfg);
}

static rt_int32_t plat_get_card_status(struct rt_mmcsd_host *host)
{
    struct mmc_host *mmc = (struct mmc_host *)host;

    return mmc->ops->get_cd(mmc);
}

static rt_int32_t plat_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode)
{
    struct mmc_host *mmc = (struct mmc_host *)host;

    return mmc->ops->execute_tuning(mmc, opcode);
}

static void plat_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
    struct mmc_host *mmc = (struct mmc_host *)host;

    return mmc->ops->enable_sdio_irq(mmc, en);
}


static const struct rt_mmcsd_host_ops rt_mmcsd_ops = {
    .request         = plat_request,
    .set_iocfg       = plat_set_ioconfig,
    .get_card_status = plat_get_card_status,
    .enable_sdio_irq = plat_enable_sdio_irq,
    .execute_tuning  = plat_execute_tuning,
};


void mmc_request_done(struct mmc_host *host, struct rt_mmcsd_req *mrq)
{
    mmcsd_req_complete(&host->rthost);
}

/*add host in rtt while sdhci complete*/
int mmc_add_host(struct mmc_host *mmc)
{
    mmc->rthost.ops           = &rt_mmcsd_ops;
    mmc->rthost.flags         = mmc->caps;
    mmc->rthost.freq_max      = mmc->f_max;
    mmc->rthost.freq_min      = 400000;
    mmc->rthost.max_dma_segs  = mmc->max_segs;
    mmc->rthost.max_seg_size  = mmc->max_seg_size;
    mmc->rthost.max_blk_size  = mmc->max_blk_size;
    mmc->rthost.max_blk_count = mmc->max_blk_count;
    mmc->rthost.valid_ocr     = VDD_33_34 | VDD_32_33 | VDD_31_32 | VDD_30_31 | VDD_165_195 | VDD_20_21;


    mmcsd_change(&mmc->rthost);
    return 0;
}

struct mmc_host *mmc_alloc_host(int extra, struct rt_device *dev)
{
    struct mmc_host *mmc;

    mmc = rt_malloc(sizeof(*mmc) + extra);
    if (mmc)
    {
        rt_memset(mmc, 0, sizeof(*mmc) + extra);
        mmc->parent = dev;
        mmcsd_host_init(&mmc->rthost);
    }

    return mmc;
}

void mmc_remove_host(struct mmc_host *host)
{
    rt_free(host);
}

int mmc_abort_tuning(struct mmc_host *host, rt_uint32_t opcode)
{
    return 0;
}


int mmc_gpio_get_cd(struct mmc_host *host)
{
    return -ENOSYS;
}

void mmc_detect_change(struct mmc_host *host, unsigned long delay)
{
}


int mmc_regulator_set_vqmmc(struct mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    return 0;
}

rt_bool_t mmc_can_gpio_ro(struct mmc_host *host)
{
    return RT_FALSE;
}

int mmc_gpio_get_ro(struct mmc_host *host)
{
    return 0;
}

int mmc_send_abort_tuning(struct mmc_host *host, rt_uint32_t opcode)
{
    return 0;
}
int mmc_of_parse(struct mmc_host *host)
{
    struct rt_device *dev = host->parent;
    rt_uint32_t       bus_width;

    if (!dev || !dev->ofw_node)
        return 0;

    /* "bus-width" is translated to MMC_CAP_*_BIT_DATA flags */
    if (rt_dm_dev_prop_read_u32(dev, "bus-width", &bus_width) < 0)
    {
        bus_width = 1;
    }

    switch (bus_width)
    {
    case 8:
        host->caps |= MMC_CAP_8_BIT_DATA;
        break; /* Hosts capable of 8-bit can also do 4 bits */
    case 4:
        host->caps |= MMC_CAP_4_BIT_DATA;
        break;
    case 1:
        break;
    default:
        return -EINVAL;
    }

    /* f_max is obtained from the optional "max-frequency" property */
    rt_dm_dev_prop_read_u32(dev, "max-frequency", &host->f_max);

    if (rt_dm_dev_prop_read_bool(dev, "cap-mmc-highspeed"))
    {
        host->caps |= MMC_CAP_MMC_HIGHSPEED;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-hs200-1_8v"))
    {
        host->caps |= MMC_CAP2_HS200_1_8V_SDR;
    }

    if (rt_dm_dev_prop_read_bool(dev, "non-removable"))
    {
        host->caps |= MMC_CAP_NONREMOVABLE;
    }

    if (rt_dm_dev_prop_read_bool(dev, "no-sdio"))
    {
        host->caps2 |= MMC_CAP2_NO_SDIO;
    }

    if (rt_dm_dev_prop_read_bool(dev, "no-sd"))
    {
        host->caps2 |= MMC_CAP2_NO_SD;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-ddr-3_3v"))
    {
        host->caps |= MMC_CAP_3_3V_DDR;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-ddr-1_8v"))
    {
        host->caps |= MMC_CAP_1_8V_DDR;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-ddr-1_2v"))
    {
        host->caps |= MMC_CAP_1_2V_DDR;
    }

    return 0;
}


void mmc_free_host(struct mmc_host *host)
{
}

rt_bool_t mmc_can_gpio_cd(struct mmc_host *host)
{
    return RT_FALSE;
}
