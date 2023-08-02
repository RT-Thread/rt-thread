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
 */

/***************************** Include Files *********************************/
#include <rthw.h>
#include <rtthread.h>

#ifdef BSP_USING_SDIO
#include <rtdevice.h>
#include <rtdbg.h>
#include <drivers/mmcsd_core.h>

#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif
#include "mm_aspace.h"

#include "ftypes.h"
#if defined(TARGET_E2000)
    #include "fparameters.h"
#endif
#include "fparameters_comm.h"

#include "fsdio.h"
#include "fsdio_hw.h"

#include "drv_sdio.h"
/************************** Constant Definitions *****************************/
#ifdef USING_SDIO0
    #define SDIO_CONTROLLER_ID    FSDIO0_ID
#elif defined (USING_SDIO1)
    #define SDIO_CONTROLLER_ID    FSDIO1_ID
#elif defined (USING_EMMC)
    #define SDIO_CONTROLLER_ID    FSDIO0_ID
#endif
#define SDIO_TF_CARD_HOST_ID  0x1
#define SDIO_MALLOC_CAP_DESC  256U
#define SDIO_DMA_ALIGN        512U
#define SDIO_DMA_BLK_SZ       512U
#define SDIO_VALID_OCR        0x00FFFF80 /* supported voltage range is 1.65v-3.6v (VDD_165_195-VDD_35_36) */
#define SDIO_MAX_BLK_TRANS    20U
/**************************** Type Definitions *******************************/
typedef struct
{
    FSdio *mmcsd_instance;
    FSdioIDmaDesc *rw_desc;
    rt_err_t (*transfer)(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req, FSdioCmdData *cmd_data_p);
} mmcsd_info_t;
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/*******************************Api Functions*********************************/
static void fsdio_host_relax(void)
{
    rt_thread_mdelay(1);
}

static rt_err_t fsdio_ctrl_init(struct rt_mmcsd_host *host)
{
    mmcsd_info_t *private_data_t = (mmcsd_info_t *)host->private_data;
    FSdio *mmcsd_instance = RT_NULL;
    const FSdioConfig *default_mmcsd_config = RT_NULL;
    FSdioConfig mmcsd_config;
    FSdioIDmaDesc *rw_desc = RT_NULL;

    mmcsd_instance = rt_malloc(sizeof(FSdio));
    if (!mmcsd_instance)
    {
        LOG_E("Malloc mmcsd_instance failed");
        return RT_ERROR;
    }

    rw_desc = rt_malloc_align(SDIO_MAX_BLK_TRANS * sizeof(FSdioIDmaDesc), SDIO_MALLOC_CAP_DESC);
    if (!rw_desc)
    {
        LOG_E("Malloc rw_desc failed");
        return RT_ERROR;
    }

    rt_memset(mmcsd_instance, 0, sizeof(FSdio));
    rt_memset(rw_desc, 0, SDIO_MAX_BLK_TRANS * sizeof(FSdioIDmaDesc));

    /* SDIO controller init */
    RT_ASSERT((default_mmcsd_config = FSdioLookupConfig(SDIO_CONTROLLER_ID)) != RT_NULL);
    mmcsd_config = *default_mmcsd_config; /* load default config */
#ifdef RT_USING_SMART
    mmcsd_config.base_addr = (uintptr)rt_ioremap((void *)mmcsd_config.base_addr, 0x1000);
#endif
    mmcsd_config.trans_mode = FSDIO_IDMA_TRANS_MODE;
#ifdef USING_EMMC
    mmcsd_config.non_removable = TRUE; /* eMMC is unremovable on board */
#else
    mmcsd_config.non_removable = FALSE; /* TF card is removable on board */
#endif


    if (FSDIO_SUCCESS != FSdioCfgInitialize(mmcsd_instance, &mmcsd_config))
    {
        LOG_E("SDIO controller init failed.");
        return RT_ERROR;
    }

    if (FSDIO_SUCCESS != FSdioSetIDMAList(mmcsd_instance, rw_desc, SDIO_MAX_BLK_TRANS))
    {
        LOG_E("SDIO controller setup DMA failed.");
        return RT_ERROR;
    }
    mmcsd_instance->desc_list.first_desc_p = (uintptr)rw_desc + PV_OFFSET;

    FSdioRegisterRelaxHandler(mmcsd_instance, fsdio_host_relax); /* SDIO delay for a while */

    private_data_t->mmcsd_instance = mmcsd_instance;
    private_data_t->rw_desc = rw_desc;

    rt_kprintf("SDIO controller init success!\r\n");
    return RT_EOK;
}

rt_inline rt_err_t sdio_dma_transfer(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req, FSdioCmdData *req_cmd)
{
    FError ret = FT_SUCCESS;
    mmcsd_info_t *private_data_t = (mmcsd_info_t *)host->private_data;
    FSdio *mmcsd_instance = private_data_t->mmcsd_instance;

    ret = FSdioDMATransfer(mmcsd_instance, req_cmd);
    if (ret != FT_SUCCESS)
    {
        LOG_E("FSdioDMATransfer() fail.");
        return -RT_ERROR;
    }

    ret = FSdioPollWaitDMAEnd(mmcsd_instance, req_cmd);
    if (ret != FT_SUCCESS)
    {
        LOG_E("FSdioPollWaitDMAEnd() fail.");
        return -RT_ERROR;
    }

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

    return RT_EOK;
}

static void mmc_request_send(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    /* ignore some SDIO-ONIY cmd */
    if ((req->cmd->cmd_code == SD_IO_SEND_OP_COND) || (req->cmd->cmd_code == SD_IO_RW_DIRECT))
    {
        req->cmd->err = -1;
        goto skip_cmd;
    }

    mmcsd_info_t *private_data_t = (mmcsd_info_t *)host->private_data;
    FSdioCmdData req_cmd;
    FSdioCmdData req_stop;
    FSdioData req_data;
    rt_uint32_t *data_buf_aligned = RT_NULL;
    rt_uint32_t cmd_flag = resp_type(req->cmd);

    rt_memset(&req_cmd, 0, sizeof(FSdioCmdData));
    rt_memset(&req_stop, 0, sizeof(FSdioCmdData));
    rt_memset(&req_data, 0, sizeof(FSdioData));

    /* convert req into ft driver type */
    if (req->cmd->cmd_code == GO_IDLE_STATE)
    {
        req_cmd.flag |= FSDIO_CMD_FLAG_NEED_INIT;
    }

    if (req->cmd->cmd_code == GO_INACTIVE_STATE)
    {
        req_cmd.flag |= FSDIO_CMD_FLAG_NEED_AUTO_STOP;
    }

    if ((cmd_flag != RESP_R3) && (cmd_flag != RESP_R4) && (cmd_flag != RESP_NONE))
    {
        req_cmd.flag |= FSDIO_CMD_FLAG_NEED_RESP_CRC;
    }

    if (cmd_flag & RESP_MASK)
    {
        req_cmd.flag |= FSDIO_CMD_FLAG_EXP_RESP;

        if (cmd_flag == RESP_R2)
        {
            req_cmd.flag |= FSDIO_CMD_FLAG_EXP_LONG_RESP;
        }
    }

    if (req->data) /* transfer command with data */
    {
        data_buf_aligned = rt_malloc_align(SDIO_DMA_BLK_SZ * req->data->blks, SDIO_DMA_ALIGN);
        if (!data_buf_aligned)
        {
            LOG_E("Malloc data_buf_aligned failed");
            return;
        }
        rt_memset(data_buf_aligned, 0, SDIO_DMA_BLK_SZ * req->data->blks);

        req_cmd.flag |= FSDIO_CMD_FLAG_EXP_DATA;

        req_data.blksz = req->data->blksize;
        req_data.blkcnt = req->data->blks;
        req_data.datalen = req->data->blksize * req->data->blks;
        if ((uintptr)req->data->buf % SDIO_DMA_ALIGN) /* data buffer should be 512-aligned */
        {
            if (req->data->flags & DATA_DIR_WRITE)
            {
                rt_memcpy((void *)data_buf_aligned, (void *)req->data->buf, req_data.datalen);
            }
            req_data.buf = (rt_uint8_t *)data_buf_aligned;
            req_data.buf_p = (uintptr)data_buf_aligned + PV_OFFSET;
        }
        else
        {
            req_data.buf = (rt_uint8_t *)req->data->buf;
            req_data.buf_p = (uintptr)req->data->buf + PV_OFFSET;
        }
        req_cmd.data_p = &req_data;

        if (req->data->flags & DATA_DIR_READ)
        {
            req_cmd.flag |= FSDIO_CMD_FLAG_READ_DATA;
        }
        else if (req->data->flags & DATA_DIR_WRITE)
        {
            req_cmd.flag |= FSDIO_CMD_FLAG_WRITE_DATA;
        }
    }

    req_cmd.cmdidx = req->cmd->cmd_code;
    req_cmd.cmdarg = req->cmd->arg;

    /* do cmd and data transfer */
    req->cmd->err = (private_data_t->transfer)(host, req, &req_cmd);
    if (req->cmd->err != RT_EOK)
    {
        LOG_E("transfer failed in %s", __func__);
    }

    if (req->data && (req->data->flags & DATA_DIR_READ))
    {
        if ((uintptr)req->data->buf % SDIO_DMA_ALIGN) /* data buffer should be 512-aligned */
        {
            rt_memcpy((void *)req->data->buf, (void *)data_buf_aligned, req_data.datalen);
        }
    }

    /* stop cmd */
    if (req->stop)
    {
        req_stop.cmdidx = req->stop->cmd_code;
        req_stop.cmdarg = req->stop->arg;
        if (req->stop->flags & RESP_MASK)
        {
            req_stop.flag |= FSDIO_CMD_FLAG_READ_DATA;
            if (resp_type(req->stop) == RESP_R2)
                req_stop.flag |= FSDIO_CMD_FLAG_EXP_LONG_RESP;
        }
        req->stop->err = (private_data_t->transfer)(host, req, &req_stop);
    }

    if (data_buf_aligned)
        rt_free_align(data_buf_aligned);

skip_cmd:
    mmcsd_req_complete(host);
}

static void mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    FError ret = FT_SUCCESS;
    mmcsd_info_t *private_data_t = (mmcsd_info_t *)host->private_data;
    FSdio *mmcsd_instance = private_data_t->mmcsd_instance;
    uintptr base_addr = mmcsd_instance->config.base_addr;

    if (0 != io_cfg->clock)
    {
        ret = FSdioSetClkFreq(mmcsd_instance, io_cfg->clock);
        if (ret != FT_SUCCESS)
        {
            LOG_E("FSdioSetClkFreq fail.");
        }
    }

    switch (io_cfg->bus_width)
    {
    case MMCSD_BUS_WIDTH_1:
        FSdioSetBusWidth(base_addr, 1U);
        break;
    case MMCSD_BUS_WIDTH_4:
        FSdioSetBusWidth(base_addr, 4U);
        break;
    case MMCSD_BUS_WIDTH_8:
        FSdioSetBusWidth(base_addr, 8U);
        break;
    default:
        LOG_E("Invalid bus width %d", io_cfg->bus_width);
        break;
    }
}

static const struct rt_mmcsd_host_ops ops =
{
    mmc_request_send,
    mmc_set_iocfg,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

int ft_mmcsd_init(void)
{
    /* variables init */
    struct rt_mmcsd_host *host = RT_NULL;
    mmcsd_info_t *private_data = RT_NULL;

    host = mmcsd_alloc_host();
    if (!host)
    {
        LOG_E("Alloc host failed");
        goto err_free;
    }

    private_data = rt_malloc(sizeof(mmcsd_info_t));
    if (!private_data)
    {
        LOG_E("Malloc private_data failed");
        goto err_free;
    }

    rt_memset(private_data, 0, sizeof(mmcsd_info_t));
    private_data->transfer = sdio_dma_transfer;

    /* host data init */
    host->ops = &ops;
    host->freq_min = 400000;
    host->freq_max = 50000000;
    host->valid_ocr = SDIO_VALID_OCR; /* the voltage range supported is 1.65v-3.6v */
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_BUSWIDTH_4;
    host->max_seg_size = SDIO_DMA_BLK_SZ; /* used in block_dev.c */
    host->max_dma_segs = SDIO_MAX_BLK_TRANS; /* physical segment number */
    host->max_blk_size = SDIO_DMA_BLK_SZ; /* all the 4 para limits size of one blk tran */
    host->max_blk_count = SDIO_MAX_BLK_TRANS;
    host->private_data = private_data;

    if (RT_EOK != fsdio_ctrl_init(host))
    {
        LOG_E("fsdio_ctrl_init() failed");
        goto err_free;
    }

    mmcsd_change(host);

    return RT_EOK;

err_free:
    if (host)
        rt_free(host);
    if (private_data->mmcsd_instance)
        rt_free(private_data->mmcsd_instance);
    if (private_data->rw_desc)
        rt_free_align(private_data->rw_desc);
    if (private_data)
        rt_free(private_data);

    return -RT_EOK;
}
INIT_DEVICE_EXPORT(ft_mmcsd_init);
#endif // #ifdef RT_USING_SDIO