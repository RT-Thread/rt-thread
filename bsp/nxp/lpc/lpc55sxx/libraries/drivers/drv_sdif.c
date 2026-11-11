/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang         the first version
 * 2019-07-19     Magicoe      The first version for LPC55S6x
 * 2023-02-0      Alex Yang    update driver
 */

#include "board.h"
#include <rtdevice.h>
#include "fsl_sdif.h"


#ifdef RT_USING_SDIO

//#define MMCSD_DEBUG

#ifdef MMCSD_DEBUG
#define MMCSD_DGB       rt_kprintf
#else
#define MMCSD_DGB(fmt, ...)
#endif

#define SDMMCHOST_RESET_TIMEOUT_VALUE (1000000U)

struct lpc_mmcsd
{
    struct rt_mmcsd_host *host;
    SDIF_Type *SDIFx;
    uint32_t sdmmcHostDmaBuffer[0x40];
};


static void SDMMCHOST_ErrorRecovery(SDIF_Type *base)
{
    (void)SDIF_Reset(base, kSDIF_ResetAll, SDMMCHOST_RESET_TIMEOUT_VALUE);
    /* the host controller clock will be disabled by the reset operation, so re-send the clock sync command to enable
    the output clock */
    sdif_command_t clockSync = {
        .flags = kSDIF_WaitPreTransferComplete | kSDIF_CmdUpdateClockRegisterOnly, .index = 0U, .argument = 0U};
    (void)SDIF_SendCommand(base, &clockSync, 0U);
}



static void lpc_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{

    struct lpc_mmcsd *mmcsd;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;
    rt_uint32_t *buf = NULL;

    status_t error;

    mmcsd = (struct lpc_mmcsd *) host->private_data;
    cmd = req->cmd;
    data = cmd->data;

    sdif_dma_config_t dmaConfig;

    dmaConfig.enableFixBurstLen     = false;
    dmaConfig.mode                  = kSDIF_ChainDMAMode;
    dmaConfig.dmaDesBufferStartAddr = mmcsd->sdmmcHostDmaBuffer;
    dmaConfig.dmaDesBufferLen       = 0x40;
    dmaConfig.dmaDesSkipLen         = 0U;

    sdif_transfer_t fsl_content = {0};
    sdif_command_t fsl_command = {0};
    sdif_data_t fsl_data = {0};

    fsl_content.command = &fsl_command;
    fsl_content.data = &fsl_data;

   // MMCSD_DGB("ARG:0x%X, CODE:0x%X\r\n", cmd->arg, cmd->cmd_code);


    fsl_command.index = cmd->cmd_code;
    fsl_command.argument = cmd->arg;

    if (cmd->cmd_code == STOP_TRANSMISSION)
        fsl_command.type = kCARD_CommandTypeAbort;
    else
        fsl_command.type = kCARD_CommandTypeNormal;

    switch (cmd->flags & RESP_MASK)
    {
    case RESP_NONE:
        fsl_command.responseType = kCARD_ResponseTypeNone;
        break;
    case RESP_R1:
        fsl_command.responseType = kCARD_ResponseTypeR1;
        break;
    case RESP_R1B:
        fsl_command.responseType = kCARD_ResponseTypeR1b;
        break;
    case RESP_R2:
        fsl_command.responseType = kCARD_ResponseTypeR2;
        break;
    case RESP_R3:
        fsl_command.responseType = kCARD_ResponseTypeR3;
        break;
    case RESP_R4:
        fsl_command.responseType = kCARD_ResponseTypeR4;
        break;
    case RESP_R6:
        fsl_command.responseType = kCARD_ResponseTypeR6;
        break;
    case RESP_R7:
        fsl_command.responseType = kCARD_ResponseTypeR7;
        break;
    case RESP_R5:
        fsl_command.responseType = kCARD_ResponseTypeR5;
        break;
    default:
        RT_ASSERT(NULL);
    }

    fsl_command.flags = 0;
    fsl_content.command = &fsl_command;

    if (data)
    {

        if (req->stop != NULL)
            fsl_data.enableAutoCommand12 = true;
        else
            fsl_data.enableAutoCommand12 = false;

        fsl_data.enableIgnoreError = false;
        fsl_data.blockSize = data->blksize;
        fsl_data.blockCount = data->blks;

        if ((cmd->cmd_code == WRITE_BLOCK) || (cmd->cmd_code == WRITE_MULTIPLE_BLOCK))
        {
            if (buf)
            {
                MMCSD_DGB(" write(data->buf to buf) ");
                rt_memcpy(buf, data->buf, fsl_data.blockSize * fsl_data.blockCount);
                fsl_data.txData = (uint32_t const *)buf;
            }
            else
            {
                fsl_data.txData = (uint32_t const *)data->buf;
            }

            fsl_data.rxData = NULL;
        }
        else
        {
            if (buf)
            {
                fsl_data.rxData = (uint32_t *)buf;
            }
            else
            {
                fsl_data.rxData = (uint32_t *)data->buf;
            }

            fsl_data.txData = NULL;
        }

        fsl_content.data = &fsl_data;
    }
    else
    {
        fsl_content.data = NULL;
    }

    error = SDIF_TransferBlocking(mmcsd->SDIFx, &dmaConfig, &fsl_content);
    if (error != kStatus_Success)
    {
        SDMMCHOST_ErrorRecovery(mmcsd->SDIFx);
        MMCSD_DGB(" ***SDIF_TransferBlocking error: %d*** --> \n", error);
        cmd->err = -RT_ERROR;
    }

    if (buf)
    {
        if (fsl_data.rxData)
        {
            MMCSD_DGB("read copy buf to data->buf ");
            rt_memcpy(data->buf, buf, fsl_data.blockSize * fsl_data.blockCount);
        }

        rt_free_align(buf);
    }

    if ((cmd->flags & RESP_MASK) == RESP_R2)
    {
        cmd->resp[3] = fsl_command.response[0];
        cmd->resp[2] = fsl_command.response[1];
        cmd->resp[1] = fsl_command.response[2];
        cmd->resp[0] = fsl_command.response[3];
     //   MMCSD_DGB(" resp 0x%08X 0x%08X 0x%08X 0x%08X\n", cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);

    }
    else
    {
        cmd->resp[0] = fsl_command.response[0];
       // MMCSD_DGB(" resp 0x%08X\n", cmd->resp[0]);
    }

    mmcsd_req_complete(host);

}








static void lpc_sdmmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    //rt_kprintf("%s\r\n", __FUNCTION__);
    struct lpc_mmcsd *mmcsd;

    mmcsd = (struct lpc_mmcsd *) host->private_data;

    uint32_t sdxc_clock = io_cfg->clock;

    MMCSD_DGB("sdxc_clock:%d\r\n", sdxc_clock);
    MMCSD_DGB("bus_width:%d\r\n", io_cfg->bus_width);

    if (sdxc_clock != 0U)
    {
        SDIF_SetCardClock(mmcsd->SDIFx, CLOCK_GetSdioClkFreq(), sdxc_clock);

        switch (io_cfg->bus_width)
        {
        case MMCSD_BUS_WIDTH_4:
            SDIF_SetCardBusWidth(mmcsd->SDIFx, kSDIF_Bus4BitWidth);
            break;
        case MMCSD_BUS_WIDTH_8:
            SDIF_SetCardBusWidth(mmcsd->SDIFx, kSDIF_Bus8BitWidth);
            break;
        default:
            SDIF_SetCardBusWidth(mmcsd->SDIFx, kSDIF_Bus1BitWidth);
            break;
        }
    }

    rt_thread_mdelay(20);
}

static const struct rt_mmcsd_host_ops lpc_mmcsd_host_ops =
{
    .request = lpc_sdmmc_request,
    .set_iocfg = lpc_sdmmc_set_iocfg,
    .get_card_status = NULL,
    .enable_sdio_irq = NULL, // Do not use the interrupt mode, use DMA instead
};




int rt_hw_sdio_init(void)
{
    struct rt_mmcsd_host *host = NULL;
    struct lpc_mmcsd *mmcsd = NULL;

    host = mmcsd_alloc_host();
    if (!host)
    {
        return -RT_ERROR;
    }

    mmcsd = rt_malloc(sizeof(struct lpc_mmcsd));
    if (!mmcsd)
    {
        rt_kprintf("alloc mci failed\n");
        goto err;
    }

    rt_memset(mmcsd, 0, sizeof(struct lpc_mmcsd));
    mmcsd->SDIFx = SDIF;

    host->ops = &lpc_mmcsd_host_ops;
    host->freq_min = 375000;
    host->freq_max = 50000000;
    host->valid_ocr = VDD_30_31 | VDD_31_32 | VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_BUSWIDTH_4 | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;

    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;

    mmcsd->host = host;

    /* Perform necessary initialization */
    CLOCK_AttachClk(kMAIN_CLK_to_SDIO_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivSdioClk, (uint32_t)(SystemCoreClock / FSL_FEATURE_SDIF_MAX_SOURCE_CLOCK + 1U), true);

    MMCSD_DGB("SDIO clock:%dHz\r\n", CLOCK_GetSdioClkFreq());

    sdif_config_t sdif_config = {0};

    sdif_config.responseTimeout       = 0xFFU;
    sdif_config.cardDetDebounce_Clock = 0xFFFFFFU;
    sdif_config.dataTimeout           = 0xFFFFFFU;
    SDIF_Init(mmcsd->SDIFx, &sdif_config);

    SDIF_EnableCardPower(mmcsd->SDIFx, false);
    SDIF_EnableCardPower(mmcsd->SDIFx, true);

    host->private_data = mmcsd;

    mmcsd_change(host);

    return 0;

err:
    mmcsd_free_host(host);

    return -RT_ENOMEM;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

#endif /* endif RT_USING_SDIO */
