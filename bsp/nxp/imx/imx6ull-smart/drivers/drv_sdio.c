/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        first version
 * 2021-07-07     linzhenxing  add sd card drivers in mmu
 * 2021-07-14     linzhenxing  add emmc
 */

#include <rtthread.h>
#include <rthw.h>
#include <drivers/dev_mmcsd_core.h>
#include <ioremap.h>

#include <board.h>
#include <fsl_usdhc.h>
#include <fsl_gpio.h>
#include <fsl_iomuxc.h>

#include <ioremap.h>
#include <string.h>
#define DBG_TAG               "drv_sdio"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

#define CACHE_LINESIZE              (32)

#define USDHC_ADMA_TABLE_WORDS      (8U)        /* define the ADMA descriptor table length */
#define USDHC_ADMA2_ADDR_ALIGN      (4U)        /* define the ADMA2 descriptor table addr align size */
#define IMXRT_MAX_FREQ              (52UL * 1000UL * 1000UL)

#define USDHC_ADMA_TABLE_WORDS      (8U)        /* define the ADMA descriptor table length */
#define USDHC_ADMA2_ADDR_ALIGN      (4U)        /* define the ADMA2 descriptor table addr align size */
#define USDHC_READ_BURST_LEN        (8U)        /*!< number of words USDHC read in a single burst */
#define USDHC_WRITE_BURST_LEN       (8U)        /*!< number of words USDHC write in a single burst */
#define USDHC_DATA_TIMEOUT          (0xFU)      /*!< data timeout counter value */

/* Read/write watermark level. The bigger value indicates DMA has higher read/write performance. */
#define USDHC_READ_WATERMARK_LEVEL  (0x80U)
#define USDHC_WRITE_WATERMARK_LEVEL (0x80U)

/* DMA mode */
#define USDHC_DMA_MODE kUSDHC_DmaModeAdma2

/* Endian mode. */
#define USDHC_ENDIAN_MODE kUSDHC_EndianModeLittle

static uint32_t g_usdhcAdma2Table[USDHC_ADMA_TABLE_WORDS];
struct rt_mmcsd_host *host1;
struct rt_mmcsd_host *host2;
static rt_mutex_t mmcsd_mutex = RT_NULL;

void host_change(void);

struct imxrt_mmcsd
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_cmd *cmd;

    struct rt_timer timer;

    rt_uint32_t *buf;

    usdhc_host_t usdhc_host;
    clock_div_t usdhc_div;
    clock_ip_name_t ip_clock;

    uint32_t *usdhc_adma2_table;
};

/*! @name Configuration */
/*@{*/

/*!
 * @brief Sets the IOMUXC pin mux mode.
 * @note The first five parameters can be filled with the pin function ID macros.
 *
 * This is an example to set the ENET1_RX_DATA0 Pad as FLEXCAN1_TX:
 * @code
 * IOMUXC_SetPinMux(IOMUXC_ENET1_RX_DATA0_FLEXCAN1_TX, 0);
 * @endcode
 *
 * This is an example to set the GPIO1_IO02 Pad as I2C1_SCL:
 * @code
 * IOMUXC_SetPinMux(IOMUXC_GPIO1_IO02_I2C1_SCL, 0);
 * @endcode
 *
 * @param muxRegister  The pin mux register.
 * @param muxMode      The pin mux mode.
 * @param inputRegister The select input register.
 * @param inputDaisy   The input daisy.
 * @param configRegister  The config register.
 * @param inputOnfield   Software input on field.
 */
static inline void _IOMUXC_SetPinMux(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield)
{
    *((volatile uint32_t *)rt_ioremap((void*)muxRegister, 0x4)) =
        IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(muxMode) | IOMUXC_SW_MUX_CTL_PAD_SION(inputOnfield);

    if (inputRegister)
    {
        *((volatile uint32_t *)rt_ioremap((void*)inputRegister, 0x4)) = IOMUXC_SELECT_INPUT_DAISY(inputDaisy);
    }
}

/*!
 * @brief Sets the IOMUXC pin configuration.
 * @note The previous five parameters can be filled with the pin function ID macros.
 *
 * This is an example to set pin configuration for IOMUXC_GPIO1_IO02_I2C1_SCL:
 * @code
 * IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO02_I2C1_SCL, IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(2U));
 * @endcode
 *
 * @param muxRegister  The pin mux register.
 * @param muxMode      The pin mux mode.
 * @param inputRegister The select input register.
 * @param inputDaisy   The input daisy.
 * @param configRegister  The config register.
 * @param configValue   The pin config value.
 */
static inline void _IOMUXC_SetPinConfig(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue)
{
    if (configRegister)
    {
        *((volatile uint32_t *)rt_ioremap((void*)configRegister, 0x4)) = configValue;
    }
}

static void _mmcsd_gpio_init(struct imxrt_mmcsd *mmcsd)
{

    CLOCK_EnableClock(kCLOCK_Iomuxc);          /* iomuxc clock (iomuxc_clk_enable): 0x03u */
#ifdef RT_USING_SDIO1
    /* uSDHC1 pins start*/
    _IOMUXC_SetPinMux(IOMUXC_UART1_RTS_B_USDHC1_CD_B, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_UART1_RTS_B_USDHC1_CD_B,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    _IOMUXC_SetPinMux(IOMUXC_SD1_CLK_USDHC1_CLK, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_SD1_CLK_USDHC1_CLK,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    _IOMUXC_SetPinMux(IOMUXC_SD1_CMD_USDHC1_CMD, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_SD1_CMD_USDHC1_CMD,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    _IOMUXC_SetPinMux(IOMUXC_SD1_DATA0_USDHC1_DATA0, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_SD1_DATA0_USDHC1_DATA0,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    _IOMUXC_SetPinMux(IOMUXC_SD1_DATA1_USDHC1_DATA1, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_SD1_DATA1_USDHC1_DATA1,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    _IOMUXC_SetPinMux(IOMUXC_SD1_DATA2_USDHC1_DATA2, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_SD1_DATA2_USDHC1_DATA2,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    _IOMUXC_SetPinMux(IOMUXC_SD1_DATA3_USDHC1_DATA3, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_SD1_DATA3_USDHC1_DATA3,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    /* uSDHC1 pins end*/
#endif

#ifdef RT_USING_SDIO2
    /* uSDHC2 pins start*/
    _IOMUXC_SetPinMux(IOMUXC_NAND_WE_B_USDHC2_CMD, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_WE_B_USDHC2_CMD,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_RE_B_USDHC2_CLK, 0U);

    _IOMUXC_SetPinConfig(IOMUXC_NAND_RE_B_USDHC2_CLK,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_ALE_USDHC2_RESET_B, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_ALE_USDHC2_RESET_B,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA00_USDHC2_DATA0, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA00_USDHC2_DATA0,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA01_USDHC2_DATA1, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA01_USDHC2_DATA1,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA02_USDHC2_DATA2, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA02_USDHC2_DATA2,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA03_USDHC2_DATA3, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA03_USDHC2_DATA3,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA04_USDHC2_DATA4, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA04_USDHC2_DATA4,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA05_USDHC2_DATA5, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA05_USDHC2_DATA5,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA06_USDHC2_DATA6, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA06_USDHC2_DATA6,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    _IOMUXC_SetPinMux(IOMUXC_NAND_DATA07_USDHC2_DATA7, 0U);
    _IOMUXC_SetPinConfig(IOMUXC_NAND_DATA07_USDHC2_DATA7,
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(7U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PUS(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    /* uSDHC2 pins end*/
#endif
}
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

static void _mmcsd_host_init(struct imxrt_mmcsd *mmcsd)
{
    usdhc_host_t *usdhc_host = &mmcsd->usdhc_host;

    /* Initializes SDHC. */
    usdhc_host->config.dataTimeout = USDHC_DATA_TIMEOUT;
    usdhc_host->config.endianMode = USDHC_ENDIAN_MODE;
    usdhc_host->config.readWatermarkLevel = USDHC_READ_WATERMARK_LEVEL;
    usdhc_host->config.writeWatermarkLevel = USDHC_WRITE_WATERMARK_LEVEL;
    usdhc_host->config.readBurstLen = USDHC_READ_BURST_LEN;
    usdhc_host->config.writeBurstLen = USDHC_WRITE_BURST_LEN;

    USDHC_Init(usdhc_host->base, &(usdhc_host->config));
}

static void _mmcsd_clk_init(struct imxrt_mmcsd *mmcsd)
{
    CLOCK_EnableClock(mmcsd->ip_clock);
    CLOCK_SetDiv(mmcsd->usdhc_div, 5U);
}

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

    rt_mutex_take(mmcsd_mutex, RT_WAITING_FOREVER);

    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(req != RT_NULL);

    mmcsd = (struct imxrt_mmcsd *)host->private_data;
    RT_ASSERT(mmcsd != RT_NULL);

    cmd = req->cmd;
    RT_ASSERT(cmd != RT_NULL);

    LOG_D("\tcmd->cmd_code: %02d, cmd->arg: %08x, cmd->flags: %08x --> ", cmd->cmd_code, cmd->arg, cmd->flags);

    data = cmd->data;

    memset(&dmaConfig, 0, sizeof(usdhc_adma_config_t));
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
        fsl_data.blockSize = data->blksize;
        fsl_data.blockCount = data->blks;

        LOG_D(" blksize:%d, blks:%d ", fsl_data.blockSize, fsl_data.blockCount);

        if (((rt_uint32_t)data->buf & (CACHE_LINESIZE - 1)) ||         // align cache(32byte)
                ((rt_uint32_t)data->buf >  0x00000000 && (rt_uint32_t)data->buf < 0x00080000) /*||  // ITCM
            ((rt_uint32_t)data->buf >= 0x20000000 && (rt_uint32_t)data->buf < 0x20080000)*/)    // DTCM
        {

            buf = rt_malloc_align(fsl_data.blockSize * fsl_data.blockCount, CACHE_LINESIZE);
            RT_ASSERT(buf != RT_NULL);

            LOG_D(" malloc buf: %p, data->buf:%p, %d ", buf, data->buf, fsl_data.blockSize * fsl_data.blockCount);
        }


        if ((cmd->cmd_code == WRITE_BLOCK) || (cmd->cmd_code == WRITE_MULTIPLE_BLOCK))
        {
            if (buf)
            {
                LOG_D(" write(data->buf to buf) ");
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
    if (error == kStatus_Fail)
    {
        SDMMCHOST_ErrorRecovery(mmcsd->usdhc_host.base);
        LOG_D(" ***USDHC_TransferBlocking error: %d*** --> \n", error);
        cmd->err = -RT_ERROR;
    }

    if (buf)
    {
        if (fsl_data.rxData)
        {
            LOG_D("read copy buf to data->buf ");
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
        LOG_D(" resp 0x%08X 0x%08X 0x%08X 0x%08X\n",
                  cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    }
    else
    {
        cmd->resp[0] = fsl_command.response[0];
        LOG_D(" resp 0x%08X\n", cmd->resp[0]);
    }

    mmcsd_req_complete(host);

    rt_mutex_release(mmcsd_mutex);
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
    src_clk = (CLOCK_GetSysPfdFreq(kCLOCK_Pfd2) / (CLOCK_GetDiv(mmcsd->usdhc_div) + 1U));

    LOG_D("\tsrc_clk: %d, usdhc_clk: %d, bus_width: %d\n", src_clk, usdhc_clk, bus_width);
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

static const struct rt_mmcsd_host_ops ops =
{
    _mmc_request,
    _mmc_set_iocfg,
    RT_NULL,//_mmc_get_card_status,
    RT_NULL,//_mmc_enable_sdio_irq,
};

rt_int32_t imxrt_mci_init(void)
{
#ifdef RT_USING_SDIO1
    struct imxrt_mmcsd *mmcsd1;

    host1 = mmcsd_alloc_host();
    if (!host1)
    {
        return -RT_ERROR;
    }

    mmcsd1 = rt_malloc(sizeof(struct imxrt_mmcsd));
    if (!mmcsd1)
    {
        LOG_E("alloc mci failed\n");
        goto err;
    }

    rt_memset(mmcsd1, 0, sizeof(struct imxrt_mmcsd));
    mmcsd1->usdhc_host.base = (USDHC_Type *)rt_ioremap((void*)USDHC1_BASE, 0x1000);
    mmcsd1->usdhc_div = kCLOCK_Usdhc1Div;
    mmcsd1->usdhc_adma2_table = g_usdhcAdma2Table;

    strncpy(host1->name, "sd", sizeof(host1->name)-1);
    host1->ops = &ops;
    host1->freq_min = 375000;
    host1->freq_max = 25000000;
    host1->valid_ocr = VDD_32_33 | VDD_33_34;
    host1->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | \
                  MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
    host1->max_seg_size = 65535;
    host1->max_dma_segs = 2;
    host1->max_blk_size = 512;
    host1->max_blk_count = 4096;

    mmcsd1->host = host1;
    _mmcsd_clk_init(mmcsd1);
    _mmcsd_gpio_init(mmcsd1);
    _mmcsd_host_init(mmcsd1);

     host1->private_data = mmcsd1;

     mmcsd_change(host1);
#endif

#ifdef RT_USING_SDIO2
    struct imxrt_mmcsd *mmcsd2;
    host2 = mmcsd_alloc_host();
    if (!host2)
    {
        return -RT_ERROR;
    }

    mmcsd2 = rt_malloc(sizeof(struct imxrt_mmcsd));
    if (!mmcsd2)
    {
        LOG_E("alloc mci failed\n");
        goto err;
    }

    rt_memset(mmcsd2, 0, sizeof(struct imxrt_mmcsd));
    mmcsd2->usdhc_host.base = (USDHC_Type *)rt_ioremap((void*)USDHC2_BASE, 0x1000);
    mmcsd2->usdhc_div = kCLOCK_Usdhc1Div;
    mmcsd2->usdhc_adma2_table = g_usdhcAdma2Table;

    strncpy(host2->name, "emmc", sizeof(host2->name)-1);
    host2->ops = &ops;
    host2->freq_min = 375000;
    host2->freq_max = 52000000;
    host2->valid_ocr = VDD_35_36;
    host2->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | \
                  MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
    host2->max_seg_size = 65535;
    host2->max_dma_segs = 2;
    host2->max_blk_size = 512;
    host2->max_blk_count = 4096;

    mmcsd2->host = host2;
    _mmcsd_clk_init(mmcsd2);
    _mmcsd_gpio_init(mmcsd2);
    _mmcsd_host_init(mmcsd2);

    host2->private_data = mmcsd2;
    mmcsd_change(host2);
#endif
    mmcsd_mutex = rt_mutex_create("mmutex", RT_IPC_FLAG_FIFO);
    if (mmcsd_mutex == RT_NULL)
    {
        LOG_E("create mmcsd mutex failed.\n");
        return -1;
    }

    return 0;

err:
#ifdef RT_USING_SDIO1
    mmcsd_free_host(host1);
#endif
#ifdef RT_USING_SDIO2
    mmcsd_free_host(host2);
#endif
    return -RT_ENOMEM;
}

INIT_DEVICE_EXPORT(imxrt_mci_init);
void host_change(void)
{
    mmcsd_change(host1);
}


