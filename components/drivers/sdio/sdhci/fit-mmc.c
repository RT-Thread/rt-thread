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


static void rt_plat_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct rt_mmc_host *mmc   = (struct rt_mmc_host *)host;
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
            void *dma_buffer = rt_malloc(req->data->blks * req->data->blksize);
            void *req_buf    = NULL;

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
            }else{
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
    struct rt_mmc_host *mmc = (struct rt_mmc_host *)host;

    LOG_D("clock:%d,width:%d,power:%d,vdd:%d,timing:%d\n",
          iocfg->clock, iocfg->bus_width,
          iocfg->power_mode, iocfg->vdd, iocfg->timing);

    mmc->ops->set_ios(mmc, iocfg);
}

static rt_int32_t rt_plat_get_card_status(struct rt_mmcsd_host *host)
{
    struct rt_mmc_host *mmc = (struct rt_mmc_host *)host;

    return mmc->ops->get_cd(mmc);
}

static rt_int32_t rt_plat_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode)
{
    struct rt_mmc_host *mmc = (struct rt_mmc_host *)host;

    return mmc->ops->execute_tuning(mmc, opcode);
}

static void rt_plat_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
    struct rt_mmc_host *mmc = (struct rt_mmc_host *)host;

    return mmc->ops->enable_sdio_irq(mmc, en);
}


static const struct rt_mmcsd_host_ops rt_mmcsd_ops = {
    .request         = rt_plat_request,
    .set_iocfg       = rt_plat_set_ioconfig,
    .get_card_status = rt_plat_get_card_status,
    .enable_sdio_irq = rt_plat_enable_sdio_irq,
    .execute_tuning  = rt_plat_execute_tuning,
};


void rt_mmc_request_done(struct rt_mmc_host *host, struct rt_mmcsd_req *mrq)
{
    mmcsd_req_complete(&host->rthost);
}

/*add host in rtt while sdhci complete*/
int rt_mmc_add_host(struct rt_mmc_host *mmc)
{
    mmc->rthost.ops           = &rt_mmcsd_ops;
    mmc->rthost.flags         = mmc->caps;
    mmc->rthost.freq_max      = mmc->f_max;
    mmc->rthost.freq_min      = 400000;
    mmc->rthost.max_dma_segs  = mmc->max_segs;
    mmc->rthost.max_seg_size  = mmc->max_seg_size;
    mmc->rthost.max_blk_size  = mmc->max_blk_size;
    mmc->rthost.max_blk_count = mmc->max_blk_count;
    mmc->rthost.valid_ocr     = VDD_165_195|VDD_20_21|VDD_21_22|VDD_22_23|VDD_24_25|VDD_25_26|VDD_26_27|VDD_27_28|VDD_28_29|VDD_29_30|VDD_30_31|VDD_32_33|VDD_33_34|VDD_34_35|VDD_35_36;


    mmcsd_change(&mmc->rthost);
    return 0;
}

struct rt_mmc_host *rt_mmc_alloc_host(int extra, struct rt_device *dev)
{
    struct rt_mmc_host *mmc;

    mmc = rt_malloc(sizeof(*mmc) + extra);
    if (mmc)
    {
        rt_memset(mmc, 0, sizeof(*mmc) + extra);
        mmc->parent = dev;
        mmcsd_host_init(&mmc->rthost);
    }

    return mmc;
}

void rt_mmc_remove_host(struct rt_mmc_host *host)
{
    rt_free(host);
}

int rt_mmc_abort_tuning(struct rt_mmc_host *host, rt_uint32_t opcode)
{
    return 0;
}


int rt_mmc_gpio_get_cd(struct rt_mmc_host *host)
{
    return -ENOSYS;
}

void rt_mmc_detect_change(struct rt_mmc_host *host, unsigned long delay)
{
}


int rt_mmc_regulator_set_vqmmc(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    return 0;
}

rt_bool_t rt_mmc_can_gpio_ro(struct rt_mmc_host *host)
{
    return RT_FALSE;
}

int rt_mmc_gpio_get_ro(struct rt_mmc_host *host)
{
    return 0;
}

int rt_mmc_send_abort_tuning(struct rt_mmc_host *host, rt_uint32_t opcode)
{
    return 0;
}
int rt_mmc_of_parse(struct rt_mmc_host *host)
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


void rt_mmc_free_host(struct rt_mmc_host *host)
{
}

rt_bool_t rt_mmc_can_gpio_cd(struct rt_mmc_host *host)
{
    return RT_FALSE;
}

int mmc_regulator_get_supply(struct rt_mmc_host *mmc)
{
    mmc->supply.vmmc  = -RT_NULL;
    mmc->supply.vqmmc = -RT_NULL;

    return 0;
}
int regulator_get_current_limit(struct regulator *regulator)
{
    return 0;
}

int regulator_is_supported_voltage(struct regulator *regulator,

                                   int min_uV, int max_uV)
{
    return 0;
}
