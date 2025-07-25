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
#if defined(BSP_USING_SDIF_LAYER)

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

#define LOG_TAG "sdif_msg_drv"
#include "drv_log.h"

#include "ftypes.h"
#include "fparameters.h"
#include "fcpu_info.h"

#include "fsdif_timing.h"

#include "fsdif_msg.h"
#include "fsdif_msg_hw.h"

#include "drv_sdif_msg.h"
/************************** Constant Definitions *****************************/
#define SDIF_CARD_TYPE_MICRO_SD 1
#define SDIF_CARD_TYPE_EMMC     2
#define SDIF_CARD_TYPE_SDIO     3

#define SDIF_DMA_BLK_SZ    512U
#define SDIF_MAX_BLK_TRANS 1024U
#define SDIF_DMA_ALIGN     SDIF_DMA_BLK_SZ

/* preserve pointer to host instance */
static struct rt_mmcsd_host *mmc_host[FSDIF_NUM] = {RT_NULL};
/**************************** Type Definitions *******************************/
typedef struct
{
    FSdifMsgCtrl sdif;
    rt_int32_t sd_type;
    FSdifMsgIDmaDesc *rw_desc;
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
    FSdifMsgCommand req_cmd;
    FSdifMsgData req_data;
    FSdifMsgRequest req;
} sdif_info_t;
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/******************************* Functions *********************************/
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

static void sdif_card_detect_callback(FSdifMsgCtrl *const instance_p, void *args, void *data)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_CARD_DETECTED);
    sdif_change(host_info->sdif.config.instance_id);
}

static void sdif_command_done_callback(FSdifMsgCtrl *const instance_p, void *args, void *data)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_COMMAND_DONE);
}

static void sdif_data_done_callback(FSdifMsgCtrl *const instance_p, void *args, void *data)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    rt_event_send(&host_info->event, SDIF_EVENT_DATA_DONE);
}

static void sdif_error_occur_callback(FSdifMsgCtrl *const instance_p, void *args, void *data)
{
    struct rt_mmcsd_host *host = (struct rt_mmcsd_host *)args;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;

    FSdifMsgDataErrIrq *err_data = (FSdifMsgDataErrIrq *)data;

    if (err_data)
    {
        u32 status = err_data->raw_ints;
        u32 dmac_status = err_data->dmac_status;

        LOG_E("SDIF ERROR:");
        LOG_E("Status: 0x%x, dmac status: 0x%x.", status, dmac_status);

        if (status & FSDIF_INT_RE_BIT)
            LOG_E("[CMD_FAIL]Response err. 0x%x", FSDIF_INT_RE_BIT);

        if (status & FSDIF_INT_RTO_BIT)
            LOG_E("[CMD_FAIL]Response timeout. 0x%x", FSDIF_INT_RTO_BIT);

        if (dmac_status & FSDIF_DMAC_STATUS_DU)
            LOG_E("[DATA_FAIL]Descriptor un-readable. 0x%x", FSDIF_DMAC_STATUS_DU);

        if (status & FSDIF_INT_DCRC_BIT)
            LOG_E("[DATA_FAIL]Data CRC error. 0x%x", FSDIF_INT_DCRC_BIT);

        if (status & FSDIF_INT_RCRC_BIT)
            LOG_E("[DATA_FAIL]Data CRC error. 0x%x", FSDIF_INT_RCRC_BIT);

        rt_event_send(&host_info->event, SDIF_EVENT_ERROR_OCCUR);
    }
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

static rt_err_t sdif_do_transfer(struct rt_mmcsd_host *host, FSdifMsgRequest *request, rt_int32_t timeout_ms)
{
    FError ret = FT_SUCCESS;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    rt_uint32_t event = 0U;
    rt_uint32_t wait_event = 0U;

    if (request->data)
    {
        wait_event = SDIF_EVENT_COMMAND_DONE | SDIF_EVENT_DATA_DONE;
    }
    else
    {
        wait_event = SDIF_EVENT_COMMAND_DONE;
    }

    ret = FSdifMsgDMATransfer(&host_info->sdif, request);
    if (ret != FT_SUCCESS)
    {
        LOG_E("FSdifMsgDMATransfer() fail. ret = 0x%x", ret);
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
            LOG_E("SDIF dma-transfer endup with error !!!");
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

static uint32_t sdif_prepare_raw_command(struct rt_mmcsd_req *req)
{
    struct rt_mmcsd_cmd *input_cmd = req->cmd;
    struct rt_mmcsd_data *input_data = req->data;
    uint32_t opcode = input_cmd->cmd_code;
    uint32_t raw_cmd = FSDIF_CMD_INDX_SET(opcode);
    rt_uint32_t resp_type = resp_type(input_cmd);

    if (GO_IDLE_STATE == opcode)
    {
        raw_cmd |= FSDIF_CMD_INIT;
    }

    if (GO_INACTIVE_STATE == opcode)
    {
        raw_cmd |= FSDIF_CMD_STOP_ABORT;
    }

    if (RESP_NONE != resp_type)
    {
        raw_cmd |= FSDIF_CMD_RESP_EXP;

        if (RESP_R2 == resp_type)
        {
            /* need 136 bits long response */
            raw_cmd |= FSDIF_CMD_RESP_LONG;
        }

        if ((RESP_R3 != resp_type) && (RESP_R4 != resp_type))
        {
            /* most cmds need CRC */
            raw_cmd |= FSDIF_CMD_RESP_CRC;
        }
    }

    if (VOLTAGE_SWITCH == opcode)
    {
        /* CMD11 need switch voltage */
        raw_cmd |= FSDIF_CMD_VOLT_SWITCH;
    }

    if (input_data)
    {
        raw_cmd |= FSDIF_CMD_DAT_EXP;

        if (input_data->flags & DATA_DIR_WRITE)
        {
            raw_cmd |= FSDIF_CMD_DAT_WRITE;
        }
    }

    raw_cmd |= FSDIF_CMD_START;

    return raw_cmd;
}

void sdif_prepare_data_transfer(FSdifMsgDataStartData *msg_data, struct rt_mmcsd_req *req)
{
    struct rt_mmcsd_cmd *input_cmd = req->cmd;
    struct rt_mmcsd_data *input_data = req->data;

    rt_memset(msg_data, 0U, sizeof(*msg_data));

    msg_data->cmd_arg = input_cmd->arg;
    msg_data->raw_cmd = sdif_prepare_raw_command(req);
    if ((input_cmd->cmd_code == WRITE_BLOCK) ||
        (input_cmd->cmd_code == WRITE_MULTIPLE_BLOCK))
    {
        msg_data->data_flags = FSDIF_MMC_DATA_WRITE;
    }
    else
    {
        msg_data->data_flags = FSDIF_MMC_DATA_READ;
    }

    msg_data->adtc_type = FSDIF_BLOCK_RW_ADTC;
    msg_data->adma_addr = 0U; /* we do not know the descriptor addr here */
    msg_data->mrq_data_blksz = input_data->blksize;
    msg_data->mrq_data_blocks = input_data->blks;

    return;
}

static uint32_t sdif_prepare_sd_command_flags(struct rt_mmcsd_req *req)
{
    struct rt_mmcsd_cmd *input_cmd = req->cmd;
    uint32_t opcode = input_cmd->cmd_code;
    uint32_t argument = input_cmd->arg;
    uint32_t flags = 0U;

    switch(opcode)
    {
        case GO_IDLE_STATE: /* MMC_GO_IDLE_STATE 0 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_NONE | FSDIF_MMC_CMD_BC;
            break;
        case SEND_EXT_CSD: /* SD_SEND_IF_COND 8 */
            flags |= FSDIF_MMC_RSP_SPI_R7 | FSDIF_MMC_RSP_R7 | FSDIF_MMC_CMD_BCR;
            break;
        case SD_APP_OP_COND: /* SD_APP_OP_COND 41 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R3 | FSDIF_MMC_CMD_BCR;
            break;
        case VOLTAGE_SWITCH: /* SD_SWITCH_VOLTAGE 11 */
            flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case ALL_SEND_CID: /* MMC_ALL_SEND_CID 2 */
            flags |= FSDIF_MMC_RSP_R2 | FSDIF_MMC_CMD_AC;
            break;
        case SET_RELATIVE_ADDR: /* SD_SEND_RELATIVE_ADDR 3 */
            flags |= FSDIF_MMC_RSP_R6 | FSDIF_MMC_CMD_BCR;
            break;
        case SEND_CSD: /* MMC_SEND_CSD 9 */
            flags |= FSDIF_MMC_RSP_R2 | FSDIF_MMC_CMD_AC;
            break;
        case SELECT_CARD: /* MMC_SELECT_CARD 7 */
            if (argument)
            {
                flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            }
            else
            {
                flags |= FSDIF_MMC_RSP_NONE | FSDIF_MMC_CMD_AC;
            }
            break;
        case APP_CMD: /* MMC_APP_CMD 55 */
            if (argument)
            {
                flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            }
            else
            {
                flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_BCR;
            }
            break;
        case SD_APP_SEND_SCR: /* SD_APP_SEND_SCR 51 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case SD_APP_SET_BUS_WIDTH: /* SD_APP_SET_BUS_WIDTH 6 */
            flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case SEND_STATUS: /* SD_APP_SD_STATUS 13 */
            flags |= FSDIF_MMC_RSP_SPI_R2 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case SET_BLOCKLEN : /* MMC_SET_BLOCKLEN 16 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case SET_BLOCK_COUNT: /* MMC_SET_BLOCK_COUNT 23 */
            flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case WRITE_BLOCK: /* MMC_WRITE_BLOCK 24 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case WRITE_MULTIPLE_BLOCK: /* MMC_WRITE_MULTIPLE_BLOCK 25 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case READ_SINGLE_BLOCK: /* MMC_READ_SINGLE_BLOCK 17 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case READ_MULTIPLE_BLOCK: /* MMC_READ_MULTIPLE_BLOCK 18 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        default:
            LOG_E("unhandled command-%d !!!", opcode);
            break;
    }

    return flags;
}

static uint32_t sdif_prepar_emmc_command_flags(struct rt_mmcsd_req *req)
{
    struct rt_mmcsd_cmd *input_cmd = req->cmd;
    uint32_t opcode = input_cmd->cmd_code;
    uint32_t argument = input_cmd->arg;
    uint32_t flags = 0U;

    switch(opcode)
    {
        case GO_IDLE_STATE: /* MMC_GO_IDLE_STATE 0 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_NONE | FSDIF_MMC_CMD_BC;
            break;
        case SEND_OP_COND: /* MMC_SEND_OP_COND 1 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R3 | FSDIF_MMC_CMD_BCR;
            break;
        case ALL_SEND_CID: /* MMC_ALL_SEND_CID 2 */
            flags |= FSDIF_MMC_RSP_R2 | FSDIF_MMC_CMD_AC;
            break;
        case SET_RELATIVE_ADDR: /* MMC_SET_RELATIVE_ADDR 3 */
            flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case SEND_CSD: /* MMC_SEND_CSD 9 */
            flags |= FSDIF_MMC_RSP_R2 | FSDIF_MMC_CMD_AC;
            break;
        case SELECT_CARD: /* MMC_SELECT_CARD 7 */
            if (argument)
            {
                flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            }
            else
            {
                flags |= FSDIF_MMC_RSP_NONE | FSDIF_MMC_CMD_AC;
            }
            break;
        case SEND_EXT_CSD: /* MMC_SEND_EXT_CSD 8 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case SWITCH: /* MMC_SWITCH 6 */
            flags |= FSDIF_MMC_CMD_AC | FSDIF_MMC_RSP_SPI_R1B | FSDIF_MMC_RSP_R1B;
            break;
        case SEND_STATUS: /* MMC_SEND_STATUS 13 */
            flags |= FSDIF_MMC_RSP_SPI_R2 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case SET_BLOCKLEN: /* MMC_SET_BLOCKLEN 16 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case SET_BLOCK_COUNT: /* MMC_SET_BLOCK_COUNT 23 */
            flags |= FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_AC;
            break;
        case WRITE_BLOCK: /* MMC_WRITE_BLOCK 24 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case WRITE_MULTIPLE_BLOCK: /* MMC_WRITE_MULTIPLE_BLOCK 25 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case READ_SINGLE_BLOCK: /* MMC_READ_SINGLE_BLOCK 17 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        case READ_MULTIPLE_BLOCK: /* MMC_READ_MULTIPLE_BLOCK 18 */
            flags |= FSDIF_MMC_RSP_SPI_R1 | FSDIF_MMC_RSP_R1 | FSDIF_MMC_CMD_ADTC;
            break;
        default:
            LOG_E("unhandled command-%d !!!", opcode);
            break;
    }

    return flags;
}

void sdif_prepare_command_trasnfer(FSdifMsgDataStartCmd *msg_cmd, struct rt_mmcsd_req *req, rt_uint32_t type)
{
    struct rt_mmcsd_cmd *input_cmd = req->cmd;

    rt_memset(msg_cmd, 0U, sizeof(*msg_cmd));

    msg_cmd->opcode = input_cmd->cmd_code;
    msg_cmd->cmd_arg = input_cmd->arg;
    msg_cmd->raw_cmd = sdif_prepare_raw_command(req);

    if (type == SDIF_CARD_TYPE_MICRO_SD)
    {
        msg_cmd->flags = sdif_prepare_sd_command_flags(req);
    }
    else if (type == SDIF_CARD_TYPE_EMMC)
    {
        msg_cmd->flags = sdif_prepar_emmc_command_flags(req);
    }

    return;
}

static void sdif_send_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdifMsgCtrl *sdif = &host_info->sdif;
    FSdifMsgCommand *req_cmd = &host_info->req_cmd;
    FSdifMsgData *req_data = &host_info->req_data;
    FSdifMsgRequest *request = &host_info->req;

    rt_err_t err = sdif_pre_request(host, req);
    if (err != RT_EOK)
    {
        if (err != RT_EEMPTY)
        {
            LOG_E("sdif_pre_request fail.");
        }
        return;
    }

    rt_memset(request, 0U, sizeof(*request));
    if (req->data)
    {
        rt_memset(req_data, 0U, sizeof(*req_data));
        req_data->buf = (void *)(req->data->buf);
        req_data->buf_dma = (uintptr)req_data->buf + PV_OFFSET;
        request->data = req_data;

        sdif_prepare_data_transfer(&(req_data->datainfo), req);

        err = FSdifMsgSetupDMADescriptor(sdif, req_data);
        if (FSDIF_SUCCESS != err)
        {
            LOG_E("SDIF setup DMA failed, err = 0x%x", err);
            return;
        }
    }
    rt_memset(req_cmd, 0, sizeof(*req_cmd));
    request->command = req_cmd;

    sdif_prepare_command_trasnfer(&(req_cmd->cmdinfo), req, host_info->sd_type);

    req->cmd->err = sdif_do_transfer(host, request, req->cmd->busy_timeout);

    if (resp_type(req->cmd) & RESP_MASK)
    {
        if (resp_type(req->cmd) == RESP_R2)
        {
            req->cmd->resp[3] = req_cmd->response[3];
            req->cmd->resp[2] = req_cmd->response[2];
            req->cmd->resp[1] = req_cmd->response[1];
            req->cmd->resp[0] = req_cmd->response[0];
        }
        else
        {
            req->cmd->resp[0] = req_cmd->response[0];
        }
    }

    mmcsd_req_complete(host);
}

static void sdif_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    FError ret = FT_SUCCESS;
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdifMsgCtrl *sdif = &host_info->sdif;
    FSdifMsgDataSetIos target_ios;

    /* ClockData set */
    if (0 != io_cfg->clock)
    {
       target_ios.ios_clock = io_cfg->clock;
    }

    /* Timing set */
    if (0 != io_cfg->timing)
    {
        if (host_info->sd_type == SDIF_CARD_TYPE_MICRO_SD)
        {
            if (io_cfg->signal_voltage == MMCSD_SIGNAL_VOLTAGE_330)
            {
                if (target_ios.ios_clock == FSDIF_CLK_SPEED_400KHZ)
                {
                    target_ios.ios_timing = FSDIF_MMC_TIMING_LEGACY;
                }
                else
                {
                    target_ios.ios_timing = FSDIF_MMC_TIMING_SD_HS;
                }
            }
            else
            {
                switch (io_cfg->timing)
                {
                    case MMCSD_TIMING_UHS_SDR12:
                        target_ios.ios_timing = FSDIF_MMC_TIMING_UHS_SDR12;
                        break;
                    case MMCSD_TIMING_UHS_SDR25:
                        target_ios.ios_timing = FSDIF_MMC_TIMING_UHS_SDR25;
                        break;
                    case MMCSD_TIMING_UHS_SDR50:
                        target_ios.ios_timing = FSDIF_MMC_TIMING_UHS_SDR50;
                        break;
                    case MMCSD_TIMING_UHS_SDR104:
                        target_ios.ios_timing = FSDIF_MMC_TIMING_UHS_SDR104;
                        break;
                    case MMCSD_TIMING_UHS_DDR50:
                        target_ios.ios_timing = FSDIF_MMC_TIMING_UHS_DDR50;
                        break;
                    default:
                        break;
                }
            }
        }
        else if (host_info->sd_type == SDIF_CARD_TYPE_EMMC)
        {
            switch (io_cfg->timing)
            {
            case MMCSD_TIMING_LEGACY:
                target_ios.ios_timing = FSDIF_MMC_TIMING_LEGACY;
                break;
            case MMCSD_TIMING_MMC_HS:
                target_ios.ios_timing = FSDIF_MMC_TIMING_MMC_HS;
                break;
            case MMCSD_TIMING_MMC_HS200:
                target_ios.ios_timing = FSDIF_MMC_TIMING_MMC_HS200;
                break;
            case MMCSD_TIMING_MMC_HS400:
            case MMCSD_TIMING_MMC_HS400_ENH_DS:
                target_ios.ios_timing = FSDIF_MMC_TIMING_MMC_HS400;
                break;
            default:
                break;
            }
        }

    }

    /* dataBusWidth set */
    switch (io_cfg->bus_width)
    {
    case MMCSD_BUS_WIDTH_1:
        target_ios.ios_bus_width = FSDIF_MMC_BUS_WIDTH_1;
        break;
    case MMCSD_BUS_WIDTH_4:
        target_ios.ios_bus_width = FSDIF_MMC_BUS_WIDTH_4;
        break;
    case MMCSD_BUS_WIDTH_8:
        target_ios.ios_bus_width = FSDIF_MMC_BUS_WIDTH_8;
        break;
    default:
        LOG_E("Invalid bus width %d", io_cfg->bus_width);
        break;
    }

    ret = FSdifMsgSetIos(sdif, &target_ios);
    if (FSDIF_SUCCESS != ret)
    {
        LOG_E("Set card bus width failed.");
    }
}

static rt_int32_t sdif_card_status(struct rt_mmcsd_host *host)
{
    sdif_info_t *host_info = (sdif_info_t *)host->private_data;
    FSdifMsgCtrl *sdif = &host_info->sdif;

    return FSdifMsgCheckifCardExists(sdif) ? 1 : 0;
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
    FSdifMsgCtrl *sdif = &(host_info->sdif);
    FSdifMsgConfig *config_p = &sdif->config;
    rt_uint32_t cpu_id = rt_hw_cpu_id();

    rt_hw_interrupt_set_target_cpus(config_p->irq_num, cpu_id);
    rt_hw_interrupt_set_priority(config_p->irq_num, 0xc);

    /* register intr callback */
    rt_hw_interrupt_install(config_p->irq_num,
                            FSdifMsgInterruptHandler,
                            sdif,
                            NULL);

    /* enable irq */
    rt_hw_interrupt_umask(config_p->irq_num);

    return;
}

void sdif_msg_prepare_init_data(FSdifMsgDataInit *msg_data_init, rt_uint32_t type)
{
    rt_memset(msg_data_init, 0U, sizeof(*msg_data_init));

    if (type == SDIF_CARD_TYPE_MICRO_SD)
    {
        msg_data_init->caps = FSDIF_MMC_CAP_4_BIT_DATA | FSDIF_MMC_CAP_SD_HIGHSPEED |
                              FSDIF_MMC_CAP_UHS | FSDIF_MMC_CAP_CMD23;
    }
    else if (type == SDIF_CARD_TYPE_EMMC)
    {
        msg_data_init->caps = FSDIF_MMC_CAP_4_BIT_DATA | FSDIF_MMC_CAP_8_BIT_DATA |
                              FSDIF_MMC_CAP_MMC_HIGHSPEED | FSDIF_MMC_CAP_NONREMOVABLE |
                              FSDIF_MMC_CAP_1_8V_DDR | FSDIF_MMC_CAP_CMD23 | FSDIF_MMC_CAP_HW_RESET;
    }

    msg_data_init->clk_rate = FSDIF_CLK_FREQ_HZ; /*1.2GHz*/
}

static rt_err_t sdif_prepare_init_ios(FSdifMsgCtrl *const instance)
{
    FSdifMsgDataSetIos target_ios;

    target_ios.ios_clock = 0U;
    target_ios.ios_timing = FSDIF_MMC_TIMING_LEGACY;
    target_ios.ios_bus_width = FSDIF_MMC_BUS_WIDTH_1;
    target_ios.ios_power_mode = FSDIF_MMC_POWER_UP;
    if (FSDIF_SUCCESS != FSdifMsgSetIos(instance, &target_ios))
    {
        LOG_E("Set init IOS failed.");
        return -RT_ERROR;
    }

    instance->cur_ios.ios_power_mode = FSDIF_MMC_POWER_ON;
    return RT_EOK;
}

static rt_err_t sdif_prepare_init_volt(FSdifMsgCtrl *const instance, rt_uint32_t type)
{
    FSdifMsgDataSwitchVolt target_volt;

    if (type == SDIF_CARD_TYPE_MICRO_SD)
    {
        target_volt.signal_voltage = FSDIF_MMC_SIGNAL_VOLTAGE_330;
    }
    else if (type == SDIF_CARD_TYPE_EMMC)
    {
        target_volt.signal_voltage = FSDIF_MMC_SIGNAL_VOLTAGE_180;
    }

    if (FSDIF_SUCCESS != FSdifMsgSetVoltage(instance, &target_volt))
    {
        LOG_E("Set init VOLT failed.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t sdif_host_init(rt_uint32_t id, rt_uint32_t type)
{
    struct rt_mmcsd_host *host = RT_NULL;
    sdif_info_t *host_info = RT_NULL;
    const FSdifMsgConfig *default_sdif_config = RT_NULL;
    FSdifMsgConfig sdif_config;
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
    host_info->rw_desc = rt_malloc_align(host_info->rw_desc_num * sizeof(FSdifMsgIDmaDesc),
                                         SDIF_DMA_ALIGN);
    if (!host_info->rw_desc)
    {
        LOG_E("Malloc rw_desc failed");
        result = RT_ENOMEM;
        goto err_free;
    }

    host_info->rw_desc_dma = (uintptr_t)host_info->rw_desc + PV_OFFSET;
    rt_memset(host_info->rw_desc, 0, host_info->rw_desc_num * sizeof(FSdifMsgIDmaDesc));

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

    default_sdif_config = FSdifMsgLookupConfig(id);
    RT_ASSERT(default_sdif_config != RT_NULL);
    sdif_config = *default_sdif_config;
#ifdef RT_USING_SMART
    sdif_config.dev_msg.shmem = (uintptr)rt_ioremap((void *)input_cfg.msg.shmem, 0x1000);
    sdif_config.dev_msg.regfile = (uintptr)rt_ioremap((void *)input_cfg.msg.regfile, 0x1000);
#endif

    if (type == SDIF_CARD_TYPE_MICRO_SD)
    {
        sdif_config.non_removable = FALSE; /* TF card is removable on board */
    }
    else if (type == SDIF_CARD_TYPE_EMMC)
    {
        sdif_config.non_removable = TRUE; /* eMMC is unremovable on board */
    }

    sdif_msg_prepare_init_data(&(sdif_config.init), type);

    FSdifMsgCtrl *sdif = &(host_info->sdif);
    if (FSDIF_SUCCESS != FSdifMsgCfgInitialize(sdif, &sdif_config))
    {
        LOG_E("Sdif v2 ctrl init failed.");
        result = RT_EIO;
        goto err_free;
    }

    if (FSDIF_SUCCESS != FSdifMsgSetIDMAList(sdif,
                                             host_info->rw_desc,
                                             host_info->rw_desc_dma,
                                             host_info->rw_desc_num))
    {
        LOG_E("SDIF controller setup DMA failed.");
        result = RT_EIO;
        goto err_free;
    }

    host_info->sd_type = type;
    LOG_I("Init sdif-%d as %d", id, type);

    /* setup interrupt */
    sdif_ctrl_setup_interrupt(host);
    FSdifMsgRegisterEvtHandler(sdif, FSDIF_EVT_CARD_DETECTED, sdif_card_detect_callback, host);
    FSdifMsgRegisterEvtHandler(sdif, FSDIF_EVT_ERR_OCCURE, sdif_error_occur_callback, host);
    FSdifMsgRegisterEvtHandler(sdif, FSDIF_EVT_CMD_DONE, sdif_command_done_callback, host);
    FSdifMsgRegisterEvtHandler(sdif, FSDIF_EVT_DATA_DONE, sdif_data_done_callback, host);

    if (sdif_prepare_init_ios(sdif) == RT_EOK)
    {
        result = sdif_prepare_init_volt(sdif, type);
    }

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

    return status;
}
INIT_DEVICE_EXPORT(rt_hw_sdif_init);
#endif