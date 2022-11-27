/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdmmc_host.h"
#include "fsl_sdmmc_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SDMMCHOST_TRANSFER_COMPLETE_TIMEOUT (~0U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief SDMMCHOST error recovery.
 * @param base host base address.
 */
static void SDMMCHOST_ErrorRecovery(SDIF_Type *base);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t SDMMCHOST_CardIntInit(sdmmchost_t *host, void *sdioInt)
{
    host->cardInt = sdioInt;

    return kStatus_Success;
}

status_t SDMMCHOST_CardDetectInit(sdmmchost_t *host, void *cd)
{
    if (cd == NULL)
    {
        return kStatus_Fail;
    }

    host->cd = cd;

    return kStatus_Success;
}

uint32_t SDMMCHOST_CardDetectStatus(sdmmchost_t *host)
{
    SDIF_Type *base        = host->hostController.base;
    sd_detect_card_t *sdCD = (sd_detect_card_t *)host->cd;

#if defined(FSL_FEATURE_SDIF_ONE_INSTANCE_SUPPORT_TWO_CARD) && FSL_FEATURE_SDIF_ONE_INSTANCE_SUPPORT_TWO_CARD
    if (((host->hostPort == 0U) &&
         (SDIF_DetectCardInsert(base, sdCD->type == kSD_DetectCardByHostDATA3 ? true : false) == 1U)) ||
        ((host->hostPort == 1U) &&
         (SDIF_DetectCard1Insert(base, sdCD->type == kSD_DetectCardByHostDATA3 ? true : false) == 1U)))
#else
    if ((host->hostPort == 0U) &&
        (SDIF_DetectCardInsert(base, sdCD->type == kSD_DetectCardByHostDATA3 ? true : false) == 1U))
#endif
    {
        return kSD_Inserted;
    }

    return kSD_Removed;
}

status_t SDMMCHOST_PollingCardDetectStatus(sdmmchost_t *host, uint32_t waitCardStatus, uint32_t timeout)
{
    assert(host != NULL);
    assert(host->cd != NULL);

    sd_detect_card_t *cd        = host->cd;
    uint32_t cardInsertedStatus = kSD_Removed;

    /* Wait card inserted. */
    do
    {
        cardInsertedStatus = SDMMCHOST_CardDetectStatus(host);

        if ((waitCardStatus == (uint32_t)kSD_Inserted) && (cardInsertedStatus == (uint32_t)kSD_Inserted))
        {
            SDMMC_OSADelay(cd->cdDebounce_ms);
            if (SDMMCHOST_CardDetectStatus(host) == (uint32_t)kSD_Inserted)
            {
                break;
            }
        }

        if ((cardInsertedStatus == (uint32_t)kSD_Removed) && (waitCardStatus == (uint32_t)kSD_Removed))
        {
            break;
        }
    } while (true);

    return kStatus_Success;
}

status_t SDMMCHOST_TransferFunction(sdmmchost_t *host, sdmmchost_transfer_t *content)
{
    status_t error = kStatus_Success;
    sdif_dma_config_t dmaConfig;

    (void)memset(&dmaConfig, 0, sizeof(dmaConfig));

    /* user DMA mode transfer data */
    if (content->data != NULL)
    {
        dmaConfig.enableFixBurstLen     = false;
        dmaConfig.mode                  = kSDIF_ChainDMAMode;
        dmaConfig.dmaDesBufferStartAddr = host->dmaDesBuffer;
        dmaConfig.dmaDesBufferLen       = host->dmaDesBufferWordsNum;
        dmaConfig.dmaDesSkipLen         = 0U;
    }

    error = SDIF_TransferBlocking(host->hostController.base, &dmaConfig, content);

    if (error != kStatus_Success)
    {
        error = kStatus_Fail;
        /* host error recovery */
        SDMMCHOST_ErrorRecovery(host->hostController.base);
    }

    return error;
}

static void SDMMCHOST_ErrorRecovery(SDIF_Type *base)
{
    (void)SDIF_Reset(base, kSDIF_ResetAll, SDMMCHOST_RESET_TIMEOUT_VALUE);
    /* the host controller clock will be disabled by the reset operation, so re-send the clock sync command to enable
    the output clock */
    sdif_command_t clockSync = {
        .flags = kSDIF_WaitPreTransferComplete | kSDIF_CmdUpdateClockRegisterOnly, .index = 0U, .argument = 0U};
    (void)SDIF_SendCommand(base, &clockSync, 0U);
}

void SDMMCHOST_SetCardPower(sdmmchost_t *host, bool enable)
{
    if (host->hostPort == 0U)
    {
        SDIF_EnableCardPower(host->hostController.base, enable);
    }
#if defined(FSL_FEATURE_SDIF_ONE_INSTANCE_SUPPORT_TWO_CARD) && FSL_FEATURE_SDIF_ONE_INSTANCE_SUPPORT_TWO_CARD
    else
    {
        SDIF_EnableCard1Power(host->hostController.base, enable);
    }
#endif

    if (enable)
    {
        /* perform SDIF host controller reset only when DATA BUSY is assert */
        if ((SDIF_GetControllerStatus(host->hostController.base) & SDIF_STATUS_DATA_BUSY_MASK) != 0U)
        {
            (void)SDIF_Reset(host->hostController.base, kSDIF_ResetAll, SDMMCHOST_RESET_TIMEOUT_VALUE);
        }
    }
}

void SDMMCHOST_ConvertDataToLittleEndian(sdmmchost_t *host, uint32_t *data, uint32_t wordSize, uint32_t format)
{
    uint32_t temp = 0U;

    if (format == kSDMMC_DataPacketFormatMSBFirst)
    {
        for (uint32_t i = 0U; i < wordSize; i++)
        {
            temp    = data[i];
            data[i] = SWAP_WORD_BYTE_SEQUENCE(temp);
        }
    }
}

status_t SDMMCHOST_Init(sdmmchost_t *host)
{
    assert(host != NULL);

    sdif_host_t *sdifHost = &(host->hostController);

    /* sdmmc osa init */
    SDMMC_OSAInit();
    /* host capability flags */
    host->capability = (uint32_t)kSDMMCHOST_SupportHighSpeed | (uint32_t)kSDMMCHOST_SupportSuspendResume |
                       (uint32_t)kSDMMCHOST_SupportVoltage3v3 | (uint32_t)kSDMMCHOST_Support4BitDataWidth |
                       (uint32_t)kSDMMCHOST_Support8BitDataWidth | (uint32_t)kSDMMCHOST_SupportDetectCardByData3 |
                       (uint32_t)kSDMMCHOST_SupportDetectCardByCD | (uint32_t)kSDMMCHOST_SupportAutoCmd12;
    host->maxBlockCount = SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT;
    host->maxBlockSize  = SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH;
    /* Initialize SDIF. */
    sdifHost->config.responseTimeout       = 0xFFU;
    sdifHost->config.cardDetDebounce_Clock = 0xFFFFFFU;
    sdifHost->config.dataTimeout           = 0xFFFFFFU;
    SDIF_Init(sdifHost->base, &(sdifHost->config));

    return kStatus_Success;
}

void SDMMCHOST_Reset(sdmmchost_t *host)
{
    /* disable all the interrupt */
    SDIF_DisableInterrupt(host->hostController.base, kSDIF_AllInterruptStatus);
    /* make sure host controller release all the bus line. */
    (void)SDIF_Reset(host->hostController.base, kSDIF_ResetAll, 100);
    /* clear all interrupt/DMA status */
    SDIF_ClearInterruptStatus(host->hostController.base, kSDIF_AllInterruptStatus);
    SDIF_ClearInternalDMAStatus(host->hostController.base, kSDIF_DMAAllStatus);
}

void SDMMCHOST_SetCardBusWidth(sdmmchost_t *host, uint32_t dataBusWidth)
{
    if (host->hostPort == 0U)
    {
        SDIF_SetCardBusWidth(host->hostController.base, dataBusWidth == (uint32_t)kSDMMC_BusWdith1Bit ?
                                                            kSDIF_Bus1BitWidth :
                                                            dataBusWidth == (uint32_t)kSDMMC_BusWdith4Bit ?
                                                            kSDIF_Bus4BitWidth :
                                                            kSDIF_Bus8BitWidth);
    }
#if defined(FSL_FEATURE_SDIF_ONE_INSTANCE_SUPPORT_TWO_CARD) && FSL_FEATURE_SDIF_ONE_INSTANCE_SUPPORT_TWO_CARD
    else
    {
        SDIF_SetCard1BusWidth(host->hostController.base, dataBusWidth == (uint32_t)kSDMMC_BusWdith1Bit ?
                                                             kSDIF_Bus1BitWidth :
                                                             dataBusWidth == (uint32_t)kSDMMC_BusWdith4Bit ?
                                                             kSDIF_Bus4BitWidth :
                                                             kSDIF_Bus8BitWidth);
    }
#endif
}

void SDMMCHOST_Deinit(sdmmchost_t *host)
{
    sdif_host_t *sdifHost = &host->hostController;
    SDIF_Deinit(sdifHost->base);
}
