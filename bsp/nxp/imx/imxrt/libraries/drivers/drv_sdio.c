/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <drivers/mmcsd_core.h>

#include <board.h>
#include <fsl_usdhc.h>
#include <fsl_gpio.h>
#include <fsl_iomuxc.h>

#include <finsh.h>

#define RT_USING_SDIO1
#define RT_USING_SDIO2

//#define DEBUG

#ifdef DEBUG
static int enable_log = 1;

#define MMCSD_DGB(fmt, ...)                 \
    do                                      \
    {                                       \
        if (enable_log)                     \
        {                                   \
            rt_kprintf(fmt, ##__VA_ARGS__); \
        }                                   \
    } while (0)
#else
#define MMCSD_DGB(fmt, ...)
#endif

#define CACHE_LINESIZE              (32)


#define IMXRT_MAX_FREQ              (25UL * 1000UL * 1000UL)

#define USDHC_READ_BURST_LEN        (8U)        /*!< number of words USDHC read in a single burst */
#define USDHC_WRITE_BURST_LEN       (8U)        /*!< number of words USDHC write in a single burst */
#define USDHC_DATA_TIMEOUT          (0xFU)      /*!< data timeout counter value */
#define SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH     (4096U)
#define SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT      (USDHC_MAX_BLOCK_COUNT)

/* Read/write watermark level. The bigger value indicates DMA has higher read/write performance. */
#define USDHC_READ_WATERMARK_LEVEL  (0x80U)
#define USDHC_WRITE_WATERMARK_LEVEL (0x80U)

/* DMA mode */
#define USDHC_DMA_MODE kUSDHC_DmaModeAdma2

/* Endian mode. */
#define USDHC_ENDIAN_MODE kUSDHC_EndianModeLittle

//#ifdef SOC_IMXRT1170_SERIES
#define USDHC_ADMA_TABLE_WORDS      (32U)        /* define the ADMA descriptor table length */
#define USDHC_ADMA2_ADDR_ALIGN      (4U)        /* define the ADMA2 descriptor table addr align size */
//#else
//#define USDHC_ADMA_TABLE_WORDS      (8U)        /* define the ADMA descriptor table length */
//#define USDHC_ADMA2_ADDR_ALIGN      (4U)        /* define the ADMA2 descriptor table addr align size */
//#endif

//rt_align(USDHC_ADMA2_ADDR_ALIGN) uint32_t g_usdhcAdma2Table[USDHC_ADMA_TABLE_WORDS] SECTION("NonCacheable");
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t g_usdhcAdma2Table[USDHC_ADMA_TABLE_WORDS], USDHC_ADMA2_ADDR_ALIGN);
struct imxrt_mmcsd
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_cmd *cmd;

    struct rt_timer timer;

    rt_uint32_t *buf;

    //USDHC_Type *base;
    usdhc_host_t usdhc_host;
#ifndef SOC_IMXRT1170_SERIES
    clock_div_t usdhc_div;
#endif
    clock_ip_name_t ip_clock;

    uint32_t *usdhc_adma2_table;
};

#ifndef CODE_STORED_ON_SDCARD
static void _mmcsd_gpio_init(struct imxrt_mmcsd *mmcsd)
{

//    CLOCK_EnableClock(kCLOCK_Iomuxc);          /* iomuxc clock (iomuxc_clk_enable): 0x03u */
}
#endif

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

#ifndef CODE_STORED_ON_SDCARD
static void _mmcsd_host_init(struct imxrt_mmcsd *mmcsd)
{
    usdhc_host_t *usdhc_host = &mmcsd->usdhc_host;

    /* Initializes SDHC. */
    usdhc_host->config.dataTimeout = USDHC_DATA_TIMEOUT;
    usdhc_host->config.endianMode = USDHC_ENDIAN_MODE;
    usdhc_host->config.readWatermarkLevel = USDHC_READ_WATERMARK_LEVEL;
    usdhc_host->config.writeWatermarkLevel = USDHC_WRITE_WATERMARK_LEVEL;
#if !(defined(FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN) && FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN)
    usdhc_host->config.readBurstLen = USDHC_READ_BURST_LEN;
    usdhc_host->config.writeBurstLen = USDHC_WRITE_BURST_LEN;
#endif
    USDHC_Init(usdhc_host->base, &(usdhc_host->config));
}

static void _mmcsd_clk_init(struct imxrt_mmcsd *mmcsd)
{
    CLOCK_EnableClock(mmcsd->ip_clock);
#if !defined(SOC_IMXRT1170_SERIES) && !defined(SOC_MIMXRT1062DVL6A)
    CLOCK_SetDiv(mmcsd->usdhc_div, 5U);
#endif
}

static void _mmcsd_isr_init(struct imxrt_mmcsd *mmcsd)
{
    //NVIC_SetPriority(USDHC1_IRQn, 5U);
}
#endif

static void _mmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct imxrt_mmcsd *mmcsd;
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

    mmcsd = (struct imxrt_mmcsd *)host->private_data;
    RT_ASSERT(mmcsd != RT_NULL);

    cmd = req->cmd;
    RT_ASSERT(cmd != RT_NULL);

    MMCSD_DGB("\tcmd->cmd_code: %02d, cmd->arg: %08x, cmd->flags: %08x --> ", cmd->cmd_code, cmd->arg, cmd->flags);

    data = cmd->data;

    rt_memset(&dmaConfig, 0, sizeof(usdhc_adma_config_t));
    /* config adma */
    dmaConfig.dmaMode = USDHC_DMA_MODE;
#if !(defined(FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN) && FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN)
    dmaConfig.burstLen = kUSDHC_EnBurstLenForINCR;
#endif
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

        if (((rt_uint32_t)data->buf & (CACHE_LINESIZE - 1)) ||         // align cache(32byte)
                ((rt_uint32_t)data->buf >  0x00000000 && (rt_uint32_t)data->buf < 0x00080000) /*||  // ITCM
            ((rt_uint32_t)data->buf >= 0x20000000 && (rt_uint32_t)data->buf < 0x20080000)*/)    // DTCM
        {

            buf = rt_malloc_align(fsl_data.blockSize * fsl_data.blockCount, CACHE_LINESIZE);
            RT_ASSERT(buf != RT_NULL);

            MMCSD_DGB(" malloc buf: %p, data->buf:%p, %d ", buf, data->buf, fsl_data.blockSize * fsl_data.blockCount);
        }


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

    error = USDHC_TransferBlocking(mmcsd->usdhc_host.base, &dmaConfig, &fsl_content);
    if (error != kStatus_Success)
    {
        SDMMCHOST_ErrorRecovery(mmcsd->usdhc_host.base);
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

static void _mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{

    struct imxrt_mmcsd *mmcsd;
    unsigned int usdhc_clk;
    unsigned int bus_width;
    uint32_t src_clk;

    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);
    RT_ASSERT(io_cfg != RT_NULL);

    mmcsd = (struct imxrt_mmcsd *)host->private_data;
    usdhc_clk = io_cfg->clock;
    bus_width = io_cfg->bus_width;

    if (usdhc_clk > IMXRT_MAX_FREQ)
        usdhc_clk = IMXRT_MAX_FREQ;
#ifdef SOC_IMXRT1170_SERIES
    clock_root_config_t rootCfg = {0};
   /* SYS PLL2 528MHz. */
   const clock_sys_pll2_config_t sysPll2Config = {
       .ssEnable = false,
   };

   CLOCK_InitSysPll2(&sysPll2Config);
   CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd2, 24);

   rootCfg.mux = 4;
   rootCfg.div = 2;
   CLOCK_SetRootClock(kCLOCK_Root_Usdhc1, &rootCfg);
    src_clk = CLOCK_GetRootClockFreq(kCLOCK_Root_Usdhc1);
#elif defined(SOC_MIMXRT1062DVL6A)
    CLOCK_InitSysPll(&sysPllConfig_BOARD_BootClockRUN);
    /*configure system pll PFD0 fractional divider to 24, output clock is 528MHZ * 18 / 24 = 396 MHZ*/
    CLOCK_InitSysPfd(kCLOCK_Pfd0, 24U);
    /* Configure USDHC clock source and divider */
    CLOCK_SetDiv(kCLOCK_Usdhc1Div, 1U); /* USDHC clock root frequency maximum: 198MHZ */
    CLOCK_SetMux(kCLOCK_Usdhc1Mux, 1U);
    src_clk =  396000000U / 2U;
#else
    src_clk = (CLOCK_GetSysPfdFreq(kCLOCK_Pfd2) / (CLOCK_GetDiv(mmcsd->usdhc_div) + 1U));
#endif
       MMCSD_DGB("\tsrc_clk: %d, usdhc_clk: %d, bus_width: %d\n", src_clk, usdhc_clk, bus_width);

    if (usdhc_clk)
    {
        USDHC_SetSdClock(mmcsd->usdhc_host.base, src_clk, usdhc_clk);

        /* Change bus width */
        if (bus_width == MMCSD_BUS_WIDTH_8)
            USDHC_SetDataBusWidth(mmcsd->usdhc_host.base, kUSDHC_DataBusWidth8Bit);
        else if (bus_width == MMCSD_BUS_WIDTH_4)
            USDHC_SetDataBusWidth(mmcsd->usdhc_host.base, kUSDHC_DataBusWidth4Bit);
        else if (bus_width == MMCSD_BUS_WIDTH_1)
            USDHC_SetDataBusWidth(mmcsd->usdhc_host.base, kUSDHC_DataBusWidth1Bit);
        else
            RT_ASSERT(RT_NULL);
    }
}

#ifdef DEBUG
static void log_toggle(int en)
{
    enable_log = en;
}
FINSH_FUNCTION_EXPORT(log_toggle, toglle log dumple);
#endif

static const struct rt_mmcsd_host_ops ops =
{
    _mmc_request,
    _mmc_set_iocfg,
    RT_NULL,//_mmc_get_card_status,
    RT_NULL,//_mmc_enable_sdio_irq,
};

rt_int32_t _imxrt_mci_init(void)
{
    struct rt_mmcsd_host *host;
    struct imxrt_mmcsd *mmcsd;

#if (defined(FSL_FEATURE_USDHC_HAS_HS400_MODE) && (FSL_FEATURE_USDHC_HAS_HS400_MODE))
    uint32_t hs400Capability = 0U;
#endif

    host = mmcsd_alloc_host();
    if (!host)
    {
        return -RT_ERROR;
    }

    mmcsd = rt_malloc(sizeof(struct imxrt_mmcsd));
    if (!mmcsd)
    {
        rt_kprintf("alloc mci failed\n");
        goto err;
    }

    rt_memset(mmcsd, 0, sizeof(struct imxrt_mmcsd));
    mmcsd->usdhc_host.base = USDHC1;
//#ifndef SOC_IMXRT1170_SERIES
//    mmcsd->usdhc_div = kCLOCK_Usdhc1Div;
//#endif
    mmcsd->usdhc_adma2_table = g_usdhcAdma2Table;

    host->ops = &ops;
    host->freq_min = 375000;
    host->freq_max = 25000000;
    host->valid_ocr = VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | \
                  MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;

#if defined(FSL_FEATURE_USDHC_INSTANCE_SUPPORT_HS400_MODEn) && (FSL_FEATURE_USDHC_INSTANCE_SUPPORT_HS400_MODEn)
    hs400Capability = (uint32_t)FSL_FEATURE_USDHC_INSTANCE_SUPPORT_HS400_MODEn(mmcsd->usdhc_host.base);
#endif
#if (defined(FSL_FEATURE_USDHC_HAS_HS400_MODE) && (FSL_FEATURE_USDHC_HAS_HS400_MODE))
    if (hs400Capability != 0U)
    {
        host->flags |= (uint32_t)MMCSD_SUP_HIGHSPEED_HS400;
    }

#endif

    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
//#ifdef SOC_IMXRT1170_SERIES
    host->max_blk_size = SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH;
    host->max_blk_count = SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT;
//#else
//    host->max_blk_size = 512;
//    host->max_blk_count = 4096;
//#endif
    mmcsd->host = host;

#ifndef CODE_STORED_ON_SDCARD
    _mmcsd_clk_init(mmcsd);
    _mmcsd_isr_init(mmcsd);
    _mmcsd_gpio_init(mmcsd);
    _mmcsd_host_init(mmcsd);
#endif

    host->private_data = mmcsd;

    mmcsd_change(host);

    return 0;

err:
    mmcsd_free_host(host);

    return -RT_ENOMEM;
}

int imxrt_mci_init(void)
{
    /* initilize sd card */
    _imxrt_mci_init();

    return 0;
}
INIT_DEVICE_EXPORT(imxrt_mci_init);
