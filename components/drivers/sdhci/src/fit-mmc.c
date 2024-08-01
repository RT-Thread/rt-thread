#include <rtthread.h>
#include "head.h"



static void plat_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{

}

static void plat_set_ioconfig(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{

}

static rt_int32_t plat_get_card_status(struct rt_mmcsd_host *host)
{

}

static rt_int32_t plat_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode)
{

}

static rt_int32_t plat_switch_uhs_voltage(struct rt_mmcsd_host *host)
{

}

static void plat_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{

}



static const struct rt_mmcsd_host_ops rt_mmcsd_ops = {
    .request = plat_request,
    .set_iocfg = plat_set_ioconfig,
    .get_card_status = plat_get_card_status,
    .enable_sdio_irq = plat_enable_sdio_irq,
    .execute_tuning = plat_execute_tuning,
    .switch_uhs_voltage = plat_switch_uhs_voltage,
};



void mmc_request_done(struct mmc_host *host, struct rt_mmc_req *mrq)
{
    mmcsd_req_complete(&host->rthost);
}

//add host in rtt while sdhci complete
int mmc_add_host(struct mmc_host *mmc)
{
    mmc->rthost.ops = &rt_mmcsd_ops;
    mmc->rthost.flags = mmc->caps;
    mmc->rthost.freq_max = mmc->f_max;
    mmc->rthost.freq_min = mmc->f_min;
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
