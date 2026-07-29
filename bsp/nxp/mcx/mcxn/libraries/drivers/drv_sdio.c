/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang         the first version
 * 2019-07-19     yandld      The first version for MCXN
 * 2023-02-0      Alex Yang    update driver
 */


#include <rtdevice.h>
#include "fsl_usdhc.h"


#ifdef RT_USING_SDIO

//#define MMCSD_DEBUG

#ifdef MMCSD_DEBUG
#define MMCSD_DGB       rt_kprintf
#else
#define MMCSD_DGB(fmt, ...)
#endif


#define USDHC_ADMA_TABLE_WORDS      (32U)        /* define the ADMA descriptor table length */
#define USDHC_ADMA2_ADDR_ALIGN      (4U)        /* define the ADMA2 descriptor table addr align size */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t g_usdhcAdma2Table[USDHC_ADMA_TABLE_WORDS], USDHC_ADMA2_ADDR_ALIGN);

struct mcx_mmcsd
{
    struct rt_mmcsd_host *host;
    USDHC_Type          *USDHC;
    uint32_t *usdhc_adma2_table;
};


#define USDHC_DMA_MODE kUSDHC_DmaModeAdma2
#define USDHC_ENDIAN_MODE kUSDHC_EndianModeLittle


#define USDHC_READ_BURST_LEN        (8U)        /*!< number of words USDHC read in a single burst */
#define USDHC_WRITE_BURST_LEN       (8U)        /*!< number of words USDHC write in a single burst */
#define USDHC_DATA_TIMEOUT          (0xFU)      /*!< data timeout counter value */
#define SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH     (4096U)
#define SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT      (USDHC_MAX_BLOCK_COUNT)

/* Read/write watermark level. The bigger value indicates DMA has higher read/write performance. */
#define USDHC_READ_WATERMARK_LEVEL  (0x80U)
#define USDHC_WRITE_WATERMARK_LEVEL (0x80U)


static void SDMMCHOST_ErrorRecovery(USDHC_Type *base)
{
    uint32_t status = 0U;
    /* get host present status */
    status = USDHC_GetPresentStatusFlags(base);
    /* check command inhibit status flag */
    if ((status & kUSDHC_CommandInhibitFlag) != 0U)
    {
        /* reset command line */
        USDHC_Reset(base, kUSDHC_ResetCommand, 1000U);
    }
    /* check data inhibit status flag */
    if ((status & kUSDHC_DataInhibitFlag) != 0U)
    {
        /* reset data line */
        USDHC_Reset(base, kUSDHC_ResetData, 1000U);
    }
}




static void mcx_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct mcx_mmcsd *mmcsd;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;
    status_t error;
    usdhc_adma_config_t dmaConfig;
    usdhc_transfer_t fsl_content = {0};
    usdhc_command_t fsl_command = {0};
    usdhc_data_t fsl_data = {0};
    rt_uint32_t *buf = NULL;

    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(req != RT_NULL);

    mmcsd = (struct mcx_mmcsd *)host->private_data;
    RT_ASSERT(mmcsd != RT_NULL);

    cmd = req->cmd;
    RT_ASSERT(cmd != RT_NULL);

    MMCSD_DGB("\tcmd->cmd_code: %02d, cmd->arg: %08x, cmd->flags: %08x --> ", cmd->cmd_code, cmd->arg, cmd->flags);

    data = cmd->data;

    rt_memset(&dmaConfig, 0, sizeof(usdhc_adma_config_t));
    /* config adma */
    dmaConfig.dmaMode = USDHC_DMA_MODE;
    dmaConfig.burstLen = kUSDHC_EnBurstLenForINCR;
    dmaConfig.admaTable = mmcsd->usdhc_adma2_table;
    dmaConfig.admaTableWords = USDHC_ADMA_TABLE_WORDS;

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

        fsl_data.enableAutoCommand23 = false;

        fsl_data.enableIgnoreError = false;
        fsl_data.dataType = kUSDHC_TransferDataNormal;  //todo : update data type
        fsl_data.blockSize = data->blksize;
        fsl_data.blockCount = data->blks;

        MMCSD_DGB(" blksize:%d, blks:%d ", fsl_data.blockSize, fsl_data.blockCount);

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

    error = USDHC_TransferBlocking(mmcsd->USDHC, &dmaConfig, &fsl_content);
    if (error != kStatus_Success)
    {
        SDMMCHOST_ErrorRecovery(mmcsd->USDHC);
        MMCSD_DGB(" ***USDHC_TransferBlocking error: %d*** --> \n", error);
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
        MMCSD_DGB(" resp 0x%08X 0x%08X 0x%08X 0x%08X\n",
                  cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    }
    else
    {
        cmd->resp[0] = fsl_command.response[0];
        MMCSD_DGB(" resp 0x%08X\n", cmd->resp[0]);
    }

    mmcsd_req_complete(host);

    return;

}



static void mcx_sdmmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    MMCSD_DGB("%s\r\n", __FUNCTION__);
    struct mcx_mmcsd *mmcsd;

    mmcsd = (struct mcx_mmcsd *) host->private_data;

    uint32_t sdxc_clock = io_cfg->clock;

    MMCSD_DGB("sdxc_clock:%d\r\n", sdxc_clock);
    MMCSD_DGB("bus_width:%d\r\n", io_cfg->bus_width);

    if (sdxc_clock != 0U)
    {
        USDHC_SetSdClock(mmcsd->USDHC, CLOCK_GetUsdhcClkFreq(), sdxc_clock);

        switch (io_cfg->bus_width)
        {
        case MMCSD_BUS_WIDTH_4:
            USDHC_SetDataBusWidth(mmcsd->USDHC, kUSDHC_DataBusWidth4Bit);
            break;
        case MMCSD_BUS_WIDTH_8:
            USDHC_SetDataBusWidth(mmcsd->USDHC, kUSDHC_DataBusWidth4Bit);
            break;
        default:
            USDHC_SetDataBusWidth(mmcsd->USDHC, kUSDHC_DataBusWidth1Bit);
            break;
        }
    }

    rt_thread_mdelay(20);
}

static const struct rt_mmcsd_host_ops mcx_mmcsd_host_ops =
{
    .request = mcx_sdmmc_request,
    .set_iocfg = mcx_sdmmc_set_iocfg,
    .get_card_status = NULL,
    .enable_sdio_irq = NULL, // Do not use the interrupt mode, use DMA instead
};




int rt_hw_sdio_init(void)
{
    struct rt_mmcsd_host *host = RT_NULL;
    struct mcx_mmcsd *mmcsd = RT_NULL;

    host = mmcsd_alloc_host();
    if (!host)
    {
        return -RT_ERROR;
    }

    mmcsd = rt_malloc(sizeof(struct mcx_mmcsd));
    if (!mmcsd)
    {
        MMCSD_DGB("alloc mci failed\n");
        goto err;
    }

    rt_memset(mmcsd, 0, sizeof(struct mcx_mmcsd));

    mmcsd->USDHC = USDHC0;
    mmcsd->usdhc_adma2_table = g_usdhcAdma2Table;

    host->ops = &mcx_mmcsd_host_ops;
    host->freq_min = 375000;
    host->freq_max = 50000000;
    host->valid_ocr = VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_BUSWIDTH_4 | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;

    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH;
    host->max_blk_count = SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT;

    mmcsd->host = host;

    /* attach FRO HF to USDHC */
    CLOCK_SetClkDiv(kCLOCK_DivUSdhcClk, 1u);
    CLOCK_AttachClk(kFRO_HF_to_USDHC);

    MMCSD_DGB("SDIO clock:%dHz\r\n", CLOCK_GetUsdhcClkFreq());

    /* Initializes SDHC. */
    usdhc_config_t config;
    config.dataTimeout = USDHC_DATA_TIMEOUT;
    config.endianMode = USDHC_ENDIAN_MODE;
    config.readWatermarkLevel = USDHC_READ_WATERMARK_LEVEL;
    config.writeWatermarkLevel = USDHC_WRITE_WATERMARK_LEVEL;
    config.readBurstLen = USDHC_READ_BURST_LEN;
    config.writeBurstLen = USDHC_WRITE_BURST_LEN;
    USDHC_Init(USDHC0, &config);

    host->private_data = mmcsd;

    mmcsd_change(host);

    return 0;

err:
    mmcsd_free_host(host);

    return -RT_ENOMEM;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

#endif /* endif RT_USING_SDIO */
