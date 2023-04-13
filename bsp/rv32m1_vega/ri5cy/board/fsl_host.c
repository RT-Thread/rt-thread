/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_host.h"
#include "board.h"
#include "fsl_gpio.h"
#ifdef BOARD_USDHC_CD_PORT_BASE
#include "fsl_port.h"
#endif

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief host controller error recovery.
 * @param host base address.
 */
static void Host_ErrorRecovery(HOST_TYPE *hostBase);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* DMA descriptor should allocate at non-cached memory */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t g_usdhcAdma2Table[USDHC_ADMA_TABLE_WORDS], USDHC_ADMA2_ADDR_ALIGN);
extern volatile uint32_t g_timeMilliseconds;
static volatile bool g_sdInsertedFlag;

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Card detect. */
status_t CardInsertDetect(HOST_TYPE *hostBase)
{
    return kStatus_Success;
}

/* User defined transfer function. */
static status_t USDHC_TransferFunction(USDHC_Type *base, usdhc_transfer_t *content)
{
    status_t error = kStatus_Success;

    usdhc_adma_config_t dmaConfig;

    if (content != NULL && content->data != NULL)
    {
        memset(&dmaConfig, 0, sizeof(usdhc_adma_config_t));
        /* config adma */
        dmaConfig.dmaMode = USDHC_DMA_MODE;
        dmaConfig.burstLen = kUSDHC_EnBurstLenForINCR;
        dmaConfig.admaTable = g_usdhcAdma2Table;
        dmaConfig.admaTableWords = USDHC_ADMA_TABLE_WORDS;
    }

    error = USDHC_TransferBlocking(base, &dmaConfig, content);

    if (error == kStatus_Fail)
    {
        /* host error recovery */
        Host_ErrorRecovery(base);
    }

    return error;
}

static void Host_ErrorRecovery(HOST_TYPE *hostBase)
{
    uint32_t status = 0U;
    /* get host present status */
    status = USDHC_GetPresentStatusFlags(hostBase);
    /* check command inhibit status flag */
    if ((status & kUSDHC_CommandInhibitFlag) != 0U)
    {
        /* reset command line */
        USDHC_Reset(hostBase, kUSDHC_ResetCommand, 100U);
    }
    /* check data inhibit status flag */
    if ((status & kUSDHC_DataInhibitFlag) != 0U)
    {
        /* reset data line */
        USDHC_Reset(hostBase, kUSDHC_ResetData, 100U);
    }
}

status_t HOST_Init(void *host)
{
    usdhc_host_t *usdhcHost = (usdhc_host_t *)host;

    /* init card power control */
    HOST_INIT_SD_POWER();
    HOST_INIT_MMC_POWER();

    /* Initializes USDHC. */
    usdhcHost->config.dataTimeout = USDHC_DATA_TIMEOUT;
    usdhcHost->config.endianMode = USDHC_ENDIAN_MODE;
    usdhcHost->config.readWatermarkLevel = USDHC_READ_WATERMARK_LEVEL;
    usdhcHost->config.writeWatermarkLevel = USDHC_WRITE_WATERMARK_LEVEL;
    usdhcHost->config.readBurstLen = USDHC_READ_BURST_LEN;
    usdhcHost->config.writeBurstLen = USDHC_WRITE_BURST_LEN;

    USDHC_Init(usdhcHost->base, &(usdhcHost->config));

    /* Define transfer function. */
    usdhcHost->transfer = USDHC_TransferFunction;

    return kStatus_Success;
}

void HOST_Reset(HOST_TYPE *hostBase)
{
    /* voltage switch to normal but not 1.8V */
    HOST_SWITCH_VOLTAGE180V(hostBase, false);
    /* Disable DDR mode */
    HOST_ENABLE_DDR_MODE(hostBase, false);
    /* disable tuning */
    HOST_EXECUTE_STANDARD_TUNING_ENABLE(hostBase, false);
    /* Disable HS400 mode */
    HOST_ENABLE_HS400_MODE(hostBase, false);
    /* Disable DLL */
    HOST_ENABLE_STROBE_DLL(hostBase, false);
}

void HOST_Deinit(void *host)
{
    usdhc_host_t *usdhcHost = (usdhc_host_t *)host;
    USDHC_Deinit(usdhcHost->base);
}
