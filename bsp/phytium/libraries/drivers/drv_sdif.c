/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2023/7/11   liqiaozhong  init SD card and mount file system
 * 2023/11/8   zhugengyu    add interrupt handling for dma waiting, unify function naming
 * 2024/4/7    zhugengyu    support use two sdif device
 */

/***************************** Include Files *********************************/
#include "rtconfig.h"

#ifdef BSP_USING_SDIF
#include <rthw.h>
#include <rtdef.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include <drivers/dev_mmcsd_core.h>

#ifdef RT_USING_SMART
#include "ioremap.h"
#endif
#include "mm_aspace.h"
#include "interrupt.h"

#define LOG_TAG "sdif_drv"
#include "drv_log.h"

#include "ftypes.h"
#include "fparameters.h"
#include "fcpu_info.h"

#include "fsdif_timing.h"

#include "fsdif.h"
#include "fsdif_hw.h"

#include "drv_sdif.h"
/************************** Constant Definitions *****************************/
#define SDIF_CARD_TYPE_MICRO_SD 1
#define SDIF_CARD_TYPE_EMMC 2
#define SDIF_CARD_TYPE_SDIO 3

#define SDIF_DMA_BLK_SZ 512U
#define SDIF_MAX_BLK_TRANS 20U
#define SDIF_DMA_ALIGN SDIF_DMA_BLK_SZ

/* preserve pointer to host instance */
static struct rt_mmcsd_host *mmc_host[FSDIF_NUM] = {RT_NULL};
/**************************** Type Definitions *******************************/

typedef struct
{
    FSdif sdif;
    rt_int32_t sd_type;
    FSdifIDmaDesc *rw_desc;
    uintptr_t rw_desc_dma;
    rt_size_t rw_desc_num;
    struct rt_event event;
#define SDIF_EVENT_CARD_DETECTED (1 << 0)
#define SDIF_EVENT_COMMAND_DONE (1 << 1)
#define SDIF_EVENT_DATA_DONE (1 << 2)
#define SDIF_EVENT_ERROR_OCCUR (1 << 3)
#define SDIF_EVENT_SDIO_IRQ (1 << 4)
    void *aligned_buffer;
    uintptr_t aligned_buffer_dma;
    rt_size_t aligned_buffer_size;
    FSdifCmdData req_cmd;
    FSdifCmdData req_stop;
    FSdifData req_data;
} sdif_info_t;
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/******************************* Functions *********************************/
static void sdif_host_relax(void)
{
    rt_thread_mdelay(1);
}

void sdif_change(rt_uint32_t id)
{
    RT_ASSERT(id < FSDIF_NUM);
    if (mmc_host[id])
    {
        mmcsd_change(mmc_host[id]);
    }
}

rt_int32_t sdif_card_inserted(rt_uint32_t id)
{
    RT_ASSERT(id < FSDIF_NUM);
    if (mmc_host[id])
    {
        return mmc_host[id]->ops->get_card_status(mmc_host[id]);
    }

    return 0;
}

static void sdif_card_detect_callback(FSdif *const sdif, void *args, u32 status, u32 dmac_status)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_CARD_DETECTED);
    sdif_change(host_info->sdif.config.instance_id);
}

static void sdif_command_done_callback(FSdif *const sdif, void *args, u32 status, u32 dmac_status)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_COMMAND_DONE);
}

static void sdif_data_done_callback(FSdif *const sdif, void *args, u32 status, u32 dmac_status)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_DATA_DONE);
}

static void sdif_sdio_irq_callback(FSdif *const sdif, void *args, u32 status, u32 dmac_status)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_SDIO_IRQ);
}

static void sdif_error_occur_callback(FSdif *const sdif, void *args, u32 status, u32 dmac_status)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    LOG_E("Error occur !!!");
    LOG_E("Status: 0x%x, dmac status: 0x%x.", status, dmac_status);

    if (status & FSDIF_INT_RE_BIT)
        LOG_E("Response err. 0x%x", FSDIF_INT_RE_BIT);

    if (status & FSDIF_INT_RTO_BIT)
        LOG_E("Response timeout. 0x%x", FSDIF_INT_RTO_BIT);

    if (dmac_status & FSDIF_DMAC_STATUS_DU)
        LOG_E("Descriptor un-readable. 0x%x", FSDIF_DMAC_STATUS_DU);

    if (status & FSDIF_INT_DCRC_BIT)
        LOG_E("Data CRC error. 0x%x", FSDIF_INT_DCRC_BIT);

    if (status & FSDIF_INT_RCRC_BIT)
        LOG_E("Data CRC error. 0x%x", FSDIF_INT_RCRC_BIT);

    rt_event_send(&host_info->event, SDIF_EVENT_ERROR_OCCUR);
}

static rt_err_t sdif_pre_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    rt_err_t err = RT_EOK;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    if (host_info->sd_type != SDIF_CARD_TYPE_SDIO)
    {
        /* ignore SDIO detect command */
        if ((req->cmd->cmd_code == SD_IO_SEND_OP_COND) ||
            (req->cmd->cmd_code == SD_IO_RW_DIRECT))
        {
            req->cmd->err = -1;
            mmcsd_req_complete(host);
            err = RT_EEMPTY;
        }
    }

    if (host_info->sd_type == SDIF_CARD_TYPE_EMMC)
    {
        /* ignore micro SD detect command, not in eMMC spec. */
        if ((req->cmd->cmd_code == SD_APP_OP_COND) ||
            (req->cmd->cmd_code == APP_CMD))
        {
            req->cmd->err = -1;
            mmcsd_req_complete(host);
            err = RT_EEMPTY;
        }

        /* ignore mmcsd_send_if_cond(CMD-8) which will failed for eMMC
           but check cmd arg to let SEND_EXT_CSD (CMD-8) run */
        if ((req->cmd->cmd_code == SD_SEND_IF_COND) &&
            (req->cmd->arg == 0x1AA)) /* 0x1AA is the send_if_cond pattern, use it by care */
        {
            req->cmd->err = -1;
            mmcsd_req_complete(host);
            err = RT_EEMPTY;
        }
    }

    if ((req->cmd->cmd_code == READ_MULTIPLE_BLOCK) ||
        (req->cmd->cmd_code == WRITE_MULTIPLE_BLOCK)) /* set block count */
    {
        struct rt_mmcsd_req sbc;
        struct rt_mmcsd_cmd sbc_cmd;

        rt_memset(&sbc, 0, sizeof(sbc));
        rt_memset(&sbc_cmd, 0, sizeof(sbc_cmd));

        sbc_cmd.cmd_code = SET_BLOCK_COUNT;
        RT_ASSERT(req->data);
        sbc_cmd.arg = req->data->blks;
        sbc_cmd.flags = RESP_R1;

        LOG_I("set block_count = %d", req->data->blks);

        sbc.data = RT_NULL;
        sbc.cmd = &sbc_cmd;
        sbc.stop = RT_NULL;
        sbc.sbc = RT_NULL;
        mmcsd_send_request(host, &sbc);

        err = sbc_cmd.err;
        if (req->cmd->busy_timeout < 1000) /* in case rt-thread do not give wait timeout */
        {
            req->cmd->busy_timeout = 5000;
        }
    }

    return err;
}

static void sdif_convert_command_info(struct rt_mmcsd_host *host, struct rt_mmcsd_cmd *in_cmd, struct rt_mmcsd_data *in_data, FSdifCmdData *out_req)
{
    FSdifCmdData *out_cmd = out_req;
    FSdifData *out_data = out_req->data_p;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    out_cmd->flag = 0U;

    if (in_cmd->cmd_code == GO_IDLE_STATE)
    {
        out_cmd->flag |= FSDIF_CMD_FLAG_NEED_INIT;
    }

    if (in_cmd->cmd_code == GO_INACTIVE_STATE)
    {
        out_cmd->flag |= FSDIF_CMD_FLAG_NEED_AUTO_STOP | FSDIF_CMD_FLAG_ABORT;
    }

    if (resp_type(in_cmd) != RESP_NONE)
    {
        out_cmd->flag |= FSDIF_CMD_FLAG_EXP_RESP;

        if (resp_type(in_cmd) == RESP_R2)
        {
            /* need 136 bits long response */
            out_cmd->flag |= FSDIF_CMD_FLAG_EXP_LONG_RESP;
        }

        if ((resp_type(in_cmd) != RESP_R3) &&
            (resp_type(in_cmd) != RESP_R4))
        {
            /* most cmds need CRC */
            out_cmd->flag |= FSDIF_CMD_FLAG_NEED_RESP_CRC;
        }
    }

    if (in_data)
    {
        RT_ASSERT(out_data);
        out_cmd->flag |= FSDIF_CMD_FLAG_EXP_DATA;

        if (in_data->flags & DATA_DIR_READ)
        {
            out_cmd->flag |= FSDIF_CMD_FLAG_READ_DATA;
            out_data->buf = (void *)in_data->buf;
            out_data->buf_dma = (uintptr_t)in_data->buf + PV_OFFSET;
        }
        else if (in_data->flags & DATA_DIR_WRITE)
        {
            out_cmd->flag |= FSDIF_CMD_FLAG_WRITE_DATA;
            out_data->buf = (void *)in_data->buf;
            out_data->buf_dma = (uintptr_t)in_data->buf + PV_OFFSET;
        }
        else
        {
            RT_ASSERT(0);
        }

        out_data->blksz = in_data->blksize;
        out_data->blkcnt = in_data->blks;
        out_data->datalen = in_data->blksize * in_data->blks;

        /* handle unaligned input buffer */
        if (out_data->buf_dma % SDIF_DMA_ALIGN)
        {
            RT_ASSERT(out_data->datalen <= host_info->aligned_buffer_size);
            out_data->buf = host_info->aligned_buffer;
            out_data->buf_dma = (uintptr_t)host_info->aligned_buffer + PV_OFFSET;

            if (in_data->flags & DATA_DIR_WRITE)
            {
                /* copy the data need to write to sd card */
                memcpy(out_data->buf, in_data->buf, out_data->datalen);
            }
        }

        LOG_D("buf@%p, blksz: %d, datalen: %ld",
              out_data->buf,
              out_data->blksz,
              out_data->datalen);
    }

    out_cmd->cmdidx = in_cmd->cmd_code;
    out_cmd->cmdarg = in_cmd->arg;
    LOG_D("cmdarg: 0x%x", out_cmd->cmdarg);
}

static rt_err_t sdif_do_transfer(struct rt_mmcsd_host *host, FSdifCmdData *req_cmd, rt_int32_t timeout_ms)
{
    FError ret = FT_SUCCESS;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    rt_uint32_t event = 0U;
    rt_uint32_t wait_event = 0U;

    LOG_I("cmd-%d sending", req_cmd->cmdidx);

    if (req_cmd->data_p == RT_NULL)
    {
        wait_event = SDIF_EVENT_COMMAND_DONE;
    }
    else
    {
        wait_event = SDIF_EVENT_COMMAND_DONE | SDIF_EVENT_DATA_DONE;
    }

    ret = FSdifDMATransfer(&host_info->sdif, req_cmd);
    if (ret != FT_SUCCESS)
    {
        LOG_E("FSdifDMATransfer() fail.");
        return -RT_ERROR;
    }

    while (TRUE)
    {
        /*
         * transfer without data: wait COMMAND_DONE event
         * transfer with data: wait COMMAND_DONE and DATA_DONE event
         */
        if (rt_event_recv(&host_info->event,
                          (wait_event),
                          (RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR),
                          rt_tick_from_millisecond(1000),
                          &event) == RT_EOK)
        {
            (void)FSdifGetCmdResponse(&host_info->sdif, req_cmd);
            break;
        }

        /*
         * transfer with error: check if ERROR_OCCUR event exists, no wait
         */
        if (rt_event_recv(&host_info->event,
                          (SDIF_EVENT_ERROR_OCCUR),
                          (RT_EVENT_FLAG_AND | RT_WAITING_NO),
                          0,
                          &event) == RT_EOK)
        {
            LOG_E("Sdif DMA transfer endup with error !!!");
            return -RT_EIO;
        }

        timeout_ms -= 1000;
        if (timeout_ms <= 0)
        {
            LOG_E("Sdif DMA transfer endup with timeout !!!");
            return -RT_EIO;
        }
    }

    return RT_EOK;
}

static void sdif_send_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdifCmdData *req_cmd = &host_info->req_cmd;
    FSdifData *req_data = &host_info->req_data;

    rt_err_t err = sdif_pre_request(host, req);
    if (err != RT_EOK)
    {
        return;
    }

    rt_memset(req_cmd, 0, sizeof(FSdifCmdData));

    if (req->data)
    {
        rt_memset(req_data, 0, sizeof(FSdifData));
        req_cmd->data_p = req_data;
    }
    else
    {
        req_cmd->data_p = RT_NULL;
    }

    sdif_convert_command_info(host, req->cmd, req->data, req_cmd);

    req->cmd->err = sdif_do_transfer(host, req_cmd, req->cmd->busy_timeout);

    if (resp_type(req->cmd) & RESP_MASK)
    {
        if (resp_type(req->cmd) == RESP_R2)
        {
            req->cmd->resp[3] = req_cmd->response[0];
            req->cmd->resp[2] = req_cmd->response[1];
            req->cmd->resp[1] = req_cmd->response[2];
            req->cmd->resp[0] = req_cmd->response[3];
        }
        else
        {
            req->cmd->resp[0] = req_cmd->response[0];
        }
    }

    if (req->data && (req->data->flags & DATA_DIR_READ))
    {
        /* if it is read sd card, copy data to unaligned buffer and return */
        if ((uintptr)req->data->buf % SDIF_DMA_ALIGN)
        {
            rt_memcpy((void *)req->data->buf,
                      (void *)host_info->aligned_buffer,
                      req_cmd->data_p->datalen);
        }
    }

    mmcsd_req_complete(host);
}

static void sdif_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    FError ret = FT_SUCCESS;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdif *sdif = &host_info->sdif;
    uintptr base_addr = sdif->config.base_addr;

    if (0 != io_cfg->clock)
    {
        ret = FSdifSetClkFreq(sdif, io_cfg->clock);
        if (ret != FT_SUCCESS)
        {
            LOG_E("FSdifSetClkFreq fail.");
        }
    }

    switch (io_cfg->bus_width)
    {
    case MMCSD_BUS_WIDTH_1:
        FSdifSetBusWidth(base_addr, 1U);
        break;
    case MMCSD_BUS_WIDTH_4:
        FSdifSetBusWidth(base_addr, 4U);
        break;
    case MMCSD_BUS_WIDTH_8:
        FSdifSetBusWidth(base_addr, 8U);
        break;
    default:
        LOG_E("Invalid bus width %d", io_cfg->bus_width);
        break;
    }
}

static rt_int32_t sdif_card_status(struct rt_mmcsd_host *host)
{
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdif *sdif = &host_info->sdif;
    uintptr base_addr = sdif->config.base_addr;

    return FSdifCheckIfCardExists(base_addr) ? 1 : 0;
}

static const struct rt_mmcsd_host_ops ops =
    {
        .request = sdif_send_request,
        .set_iocfg = sdif_set_iocfg,
        .get_card_status = sdif_card_status,
        .enable_sdio_irq = RT_NULL,
        .execute_tuning = RT_NULL,
};

static void sdif_ctrl_setup_interrupt(struct rt_mmcsd_host *host)
{
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdif *sdif = &(host_info->sdif);
    FSdifConfig *config_p = &sdif->config;
    rt_uint32_t cpu_id = rt_hw_cpu_id();

    rt_hw_interrupt_set_target_cpus(config_p->irq_num, cpu_id);
    rt_hw_interrupt_set_priority(config_p->irq_num, 0xd0);

    /* register intr callback */
    rt_hw_interrupt_install(config_p->irq_num,
                            FSdifInterruptHandler,
                            sdif,
                            NULL);

    /* enable irq */
    rt_hw_interrupt_umask(config_p->irq_num);

    FSdifRegisterEvtHandler(sdif, FSDIF_EVT_CARD_DETECTED, sdif_card_detect_callback, host);
    FSdifRegisterEvtHandler(sdif, FSDIF_EVT_ERR_OCCURE, sdif_error_occur_callback, host);
    FSdifRegisterEvtHandler(sdif, FSDIF_EVT_CMD_DONE, sdif_command_done_callback, host);
    FSdifRegisterEvtHandler(sdif, FSDIF_EVT_DATA_DONE, sdif_data_done_callback, host);
    FSdifRegisterEvtHandler(sdif, FSDIF_EVT_SDIO_IRQ, sdif_sdio_irq_callback, host);

    return;
}

static rt_err_t sdif_host_init(rt_uint32_t id, rt_uint32_t type)
{
    struct rt_mmcsd_host *host = RT_NULL;
    sdif_info_t *host_info = RT_NULL;
    const FSdifConfig *default_sdif_config = RT_NULL;
    FSdifConfig sdif_config;
    rt_err_t result = RT_EOK;

    host = mmcsd_alloc_host();
    if (!host)
    {
        LOG_E("Alloc host failed");
        result = RT_ENOMEM;
        goto err_free;
    }

    host_info = rt_malloc(sizeof(sdif_info_t));
    if (!host_info)
    {
        LOG_E("Malloc host_info failed");
        result = RT_ENOMEM;
        goto err_free;
    }
    rt_memset(host_info, 0, sizeof(*host_info));

    result = rt_event_init(&host_info->event, "sdif_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(RT_EOK == result);

    host_info->aligned_buffer_size = SDIF_DMA_BLK_SZ * SDIF_MAX_BLK_TRANS;
    host_info->aligned_buffer = rt_malloc_align(host_info->aligned_buffer_size,
                                                SDIF_DMA_ALIGN);
    if (!host_info->aligned_buffer)
    {
        LOG_E("Malloc aligned buffer failed");
        result = RT_ENOMEM;
        goto err_free;
    }

    host_info->aligned_buffer_dma = (uintptr_t)host_info->aligned_buffer + PV_OFFSET;
    rt_memset(host_info->aligned_buffer, 0, host_info->aligned_buffer_size);

    host_info->rw_desc_num = (SDIF_DMA_BLK_SZ * SDIF_MAX_BLK_TRANS) / FSDIF_IDMAC_MAX_BUF_SIZE + 1;
    host_info->rw_desc = rt_malloc_align(host_info->rw_desc_num * sizeof(FSdifIDmaDesc),
                                         SDIF_DMA_ALIGN);
    if (!host_info->rw_desc)
    {
        LOG_E("Malloc rw_desc failed");
        result = RT_ENOMEM;
        goto err_free;
    }

    host_info->rw_desc_dma = (uintptr_t)host_info->rw_desc + PV_OFFSET;
    rt_memset(host_info->rw_desc, 0, host_info->rw_desc_num * sizeof(FSdifIDmaDesc));

    /* host data init */
    host->ops = &ops;
    host->freq_min = FSDIF_CLK_SPEED_400KHZ;
    if (type == SDIF_CARD_TYPE_MICRO_SD)
    {
        host->freq_max = FSDIF_CLK_SPEED_50_MHZ;
    }
    else
    {
        host->freq_max = FSDIF_CLK_SPEED_52_MHZ;
    }

    host->valid_ocr = VDD_32_33 | VDD_33_34; /* voltage 3.3v */
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_BUSWIDTH_4;
    host->max_seg_size = SDIF_DMA_BLK_SZ;    /* used in block_dev.c */
    host->max_dma_segs = SDIF_MAX_BLK_TRANS; /* physical segment number */
    host->max_blk_size = SDIF_DMA_BLK_SZ;    /* all the 4 para limits size of one blk tran */
    host->max_blk_count = SDIF_MAX_BLK_TRANS;
    host->private_data = host_info;
    host->name[0] = 's';
    host->name[1] = 'd';
    host->name[2] = '0' + id;
    host->name[3] = '\0';

    mmc_host[id] = host;

    RT_ASSERT((default_sdif_config = FSdifLookupConfig(id)) != RT_NULL);
    sdif_config = *default_sdif_config;
#ifdef RT_USING_SMART
    sdif_config.base_addr = (uintptr)rt_ioremap((void *)sdif_config.base_addr, 0x1000);
#endif
    sdif_config.trans_mode = FSDIF_IDMA_TRANS_MODE;

    if (type == SDIF_CARD_TYPE_MICRO_SD)
    {
        sdif_config.non_removable = FALSE; /* TF card is removable on board */
    }
    else if (type == SDIF_CARD_TYPE_EMMC)
    {
        sdif_config.non_removable = TRUE; /* eMMC is unremovable on board */
    }

    sdif_config.get_tuning = FSdifGetTimingSetting;

    if (FSDIF_SUCCESS != FSdifCfgInitialize(&host_info->sdif, &sdif_config))
    {
        LOG_E("SDIF controller init failed.");
        result = RT_EIO;
        goto err_free;
    }

    if (FSDIF_SUCCESS != FSdifSetIDMAList(&host_info->sdif,
                                          host_info->rw_desc,
                                          host_info->rw_desc_dma,
                                          host_info->rw_desc_num))
    {
        LOG_E("SDIF controller setup DMA failed.");
        result = RT_EIO;
        goto err_free;
    }

    FSdifRegisterRelaxHandler(&host_info->sdif, sdif_host_relax); /* SDIF delay for a while */

    host_info->sd_type = type;
    LOG_I("Init sdif-%d as %d", id, type);

    /* setup interrupt */
    sdif_ctrl_setup_interrupt(host);
    return result;

err_free:
    if (host)
    {
        mmcsd_free_host(host);
    }

    if (host_info)
    {
        if (host_info->aligned_buffer)
        {
            rt_free(host_info->aligned_buffer);
            host_info->aligned_buffer = RT_NULL;
            host_info->aligned_buffer_size = 0U;
        }

        if (host_info->rw_desc)
        {
            rt_free(host_info->rw_desc);
            host_info->rw_desc = RT_NULL;
            host_info->rw_desc_num = 0;
        }

        rt_free(host_info);
    }

    return result;
}

int rt_hw_sdif_init(void)
{
    int status = RT_EOK;
    rt_uint32_t sd_type;

    FSdifTimingInit();

#ifdef USING_SDIF0
#if defined(USE_SDIF0_TF)
    sd_type = SDIF_CARD_TYPE_MICRO_SD;
#elif defined(USE_SDIF0_EMMC)
    sd_type = SDIF_CARD_TYPE_EMMC;
#endif
    status = sdif_host_init(FSDIF0_ID, sd_type);

    if (status != RT_EOK)
    {
        LOG_E("SDIF0 init failed, status = %d", status);
        return status;
    }
#endif

#ifdef USING_SDIF1
#if defined(USE_SDIF1_TF)
    sd_type = SDIF_CARD_TYPE_MICRO_SD;
#elif defined(USE_SDIF1_EMMC)
    sd_type = SDIF_CARD_TYPE_EMMC;
#endif
    status = sdif_host_init(FSDIF1_ID, sd_type);

    if (status != RT_EOK)
    {
        LOG_E("SDIF0 init failed, status = %d", status);
        return status;
    }
#endif

    return status;
}
INIT_DEVICE_EXPORT(rt_hw_sdif_init);
#endif // #ifdef BSP_USING_SDIF