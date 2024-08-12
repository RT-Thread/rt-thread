#include <rtthread.h>
#include "sdhci_host.h"
#include <rtdbg.h>



static void plat_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct mmc_host *mmc= (struct mmc_host *)host;
    rt_uint32_t flags = req->cmd->flags;

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
    req->cmd->flags |= flags;
    mmc->ops->request(mmc, req);
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

    return mmc->ops->enable_sdio_irq(mmc,en);
    
}



static const struct rt_mmcsd_host_ops rt_mmcsd_ops = {
    .request = plat_request,
    .set_iocfg = plat_set_ioconfig,
    .get_card_status = plat_get_card_status,
    .enable_sdio_irq = plat_enable_sdio_irq,
    .execute_tuning = plat_execute_tuning,
};



void mmc_request_done(struct mmc_host *host, struct rt_mmcsd_req *mrq)
{
    mmcsd_req_complete(&host->rthost);
}

//add host in rtt while sdhci complete
int mmc_add_host(struct mmc_host *mmc)
{
    mmc->rthost.ops = &rt_mmcsd_ops;
    mmc->rthost.flags = mmc->caps;
    mmc->rthost.freq_max = mmc->f_max;
    mmc->rthost.freq_min = 400000;
    mmc->rthost.max_dma_segs = mmc->max_segs;
    mmc->rthost.max_seg_size = mmc->max_seg_size;
    mmc->rthost.max_blk_size = mmc->max_blk_size;
    mmc->rthost.max_blk_count = mmc->max_blk_count;
    mmc->rthost.valid_ocr = VDD_165_195;
    

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