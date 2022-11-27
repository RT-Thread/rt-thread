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
 * @brief SDMMCHOST detect card insert status by host controller.
 * @param base host base address.
 * @param userData user can register a application card insert callback through userData.
 */
static void SDMMCHOST_DetectCardInsertByHost(SDIF_Type *base, void *userData);

/*!
 * @brief SDMMCHOST detect card remove status by host controller.
 * @param base host base address.
 * @param userData user can register a application card insert callback through userData.
 */
static void SDMMCHOST_DetectCardRemoveByHost(SDIF_Type *base, void *userData);

/*!
 * @brief SDMMCHOST transfer complete callback.
 * @param base host base address.
 * @param handle host handle.
 * @param status interrupt status.
 * @param userData user data.
 */
static void SDMMCHOST_TransferCompleteCallback(SDIF_Type *base, void *handle, status_t status, void *userData);

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
static void SDMMCHOST_DetectCardInsertByHost(SDIF_Type *base, void *userData)
{
    sd_detect_card_t *cd = NULL;

    (void)SDMMC_OSAEventSet(&(((sdmmchost_t *)userData)->hostEvent), SDMMC_OSA_EVENT_CARD_INSERTED);
    (void)SDMMC_OSAEventClear(&(((sdmmchost_t *)userData)->hostEvent), SDMMC_OSA_EVENT_CARD_REMOVED);

    if (userData != NULL)
    {
        cd = (sd_detect_card_t *)(((sdmmchost_t *)userData)->cd);
        if (cd != NULL)
        {
            if (cd->callback != NULL)
            {
                cd->callback(true, cd->userData);
            }
        }
    }
}

static void SDMMCHOST_DetectCardRemoveByHost(SDIF_Type *base, void *userData)
{
    sd_detect_card_t *cd = NULL;

    (void)SDMMC_OSAEventSet(&(((sdmmchost_t *)userData)->hostEvent), SDMMC_OSA_EVENT_CARD_REMOVED);
    (void)SDMMC_OSAEventClear(&(((sdmmchost_t *)userData)->hostEvent), SDMMC_OSA_EVENT_CARD_INSERTED);

    if (userData != NULL)
    {
        cd = (sd_detect_card_t *)(((sdmmchost_t *)userData)->cd);
        if (cd != NULL)
        {
            if (cd->callback != NULL)
            {
                cd->callback(false, cd->userData);
            }
        }
    }
}

static void SDMMCHOST_CardInterrupt(SDIF_Type *base, void *userData)
{
    sdio_card_int_t *cardInt = NULL;

    /* application callback */
    if (userData != NULL)
    {
        cardInt = ((sdmmchost_t *)userData)->cardInt;
        if ((cardInt != NULL) && (cardInt->cardInterrupt != NULL))
        {
            cardInt->cardInterrupt(cardInt->userData);
        }
    }
}

status_t SDMMCHOST_CardIntInit(sdmmchost_t *host, void *sdioInt)
{
    host->cardInt                       = sdioInt;
    host->handle.callback.SDIOInterrupt = SDMMCHOST_CardInterrupt;
    SDMMCHOST_EnableCardInt(host, true);

    return kStatus_Success;
}

status_t SDMMCHOST_CardDetectInit(sdmmchost_t *host, void *cd)
{
    SDIF_Type *base        = host->hostController.base;
    sd_detect_card_t *sdCD = (sd_detect_card_t *)cd;
    if (cd == NULL)
    {
        return kStatus_Fail;
    }

    host->cd = cd;

    /* enable card detect interrupt */
    SDIF_EnableInterrupt(base, kSDIF_CardDetect);

    if (SDMMCHOST_CardDetectStatus(host) == (uint32_t)kSD_Inserted)
    {
        (void)SDMMC_OSAEventSet(&(host->hostEvent), SDMMC_OSA_EVENT_CARD_INSERTED);
        /* notify application about the card insertion status */
        if (sdCD->callback != NULL)
        {
            sdCD->callback(true, sdCD->userData);
        }
    }
    else
    {
        (void)SDMMC_OSAEventSet(&(host->hostEvent), SDMMC_OSA_EVENT_CARD_REMOVED);
    }

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

    sd_detect_card_t *cd = host->cd;
    uint32_t event       = 0U;

    (void)SDMMC_OSAEventGet(&(host->hostEvent), SDMMC_OSA_EVENT_CARD_INSERTED | SDMMC_OSA_EVENT_CARD_REMOVED, &event);
    if ((((event & SDMMC_OSA_EVENT_CARD_INSERTED) == SDMMC_OSA_EVENT_CARD_INSERTED) &&
         (waitCardStatus == (uint32_t)kSD_Inserted)) ||
        (((event & SDMMC_OSA_EVENT_CARD_REMOVED) == SDMMC_OSA_EVENT_CARD_REMOVED) &&
         (waitCardStatus == (uint32_t)kSD_Removed)))
    {
        return kStatus_Success;
    }

    /* Wait card inserted. */
    do
    {
        if (SDMMC_OSAEventWait(&(host->hostEvent), SDMMC_OSA_EVENT_CARD_INSERTED | SDMMC_OSA_EVENT_CARD_REMOVED,
                               timeout, &event) != kStatus_Success)
        {
            return kStatus_Fail;
        }
        else
        {
            if ((waitCardStatus == (uint32_t)kSD_Inserted) &&
                ((event & SDMMC_OSA_EVENT_CARD_INSERTED) == SDMMC_OSA_EVENT_CARD_INSERTED))
            {
                SDMMC_OSADelay(cd->cdDebounce_ms);
                if (SDMMCHOST_CardDetectStatus(host) == (uint32_t)kSD_Inserted)
                {
                    break;
                }
            }

            if (((event & SDMMC_OSA_EVENT_CARD_REMOVED) == SDMMC_OSA_EVENT_CARD_REMOVED) &&
                (waitCardStatus == (uint32_t)kSD_Removed))
            {
                break;
            }
        }
    } while (true);

    return kStatus_Success;
}

static void SDMMCHOST_TransferCompleteCallback(SDIF_Type *base, void *handle, status_t status, void *userData)
{
    uint32_t eventStatus = 0U;

    if (status == kStatus_SDIF_DataTransferFail)
    {
        eventStatus = SDMMC_OSA_EVENT_TRANSFER_DATA_FAIL;
    }
    else if (status == kStatus_SDIF_DataTransferSuccess)
    {
        eventStatus = SDMMC_OSA_EVENT_TRANSFER_DATA_SUCCESS;
    }
    else if (status == kStatus_SDIF_SendCmdFail)
    {
        eventStatus = SDMMC_OSA_EVENT_TRANSFER_CMD_FAIL;
    }
    else
    {
        eventStatus = SDMMC_OSA_EVENT_TRANSFER_CMD_SUCCESS;
    }

    (void)SDMMC_OSAEventSet(&(((sdmmchost_t *)userData)->hostEvent), eventStatus);
}

status_t SDMMCHOST_TransferFunction(sdmmchost_t *host, sdmmchost_transfer_t *content)
{
    status_t error = kStatus_Success;
    uint32_t event = 0U;
    sdif_dma_config_t dmaConfig;

    SDMMC_OSAMutexLock(&host->lock, osaWaitForever_c);

    /* clear redundant transfer event flag */
    (void)SDMMC_OSAEventClear(&(host->hostEvent),
                              SDMMC_OSA_EVENT_TRANSFER_CMD_SUCCESS | SDMMC_OSA_EVENT_TRANSFER_CMD_FAIL |
                                  SDMMC_OSA_EVENT_TRANSFER_DATA_SUCCESS | SDMMC_OSA_EVENT_TRANSFER_DATA_FAIL);

    /* user DMA mode transfer data */
    if (content->data != NULL)
    {
        (void)memset(&dmaConfig, 0, sizeof(dmaConfig));

        dmaConfig.enableFixBurstLen     = false;
        dmaConfig.mode                  = kSDIF_DualDMAMode;
        dmaConfig.dmaDesBufferStartAddr = host->dmaDesBuffer;
        dmaConfig.dmaDesBufferLen       = host->dmaDesBufferWordsNum;
        dmaConfig.dmaDesSkipLen         = 0U;
    }

    do
    {
        error = SDIF_TransferNonBlocking(host->hostController.base, &host->handle, &dmaConfig, content);
    } while (error == kStatus_SDIF_SyncCmdTimeout);

    if (error == kStatus_Success)
    {
        /* wait command event */
        if ((kStatus_Fail ==
             SDMMC_OSAEventWait(&(host->hostEvent),
                                SDMMC_OSA_EVENT_TRANSFER_CMD_SUCCESS | SDMMC_OSA_EVENT_TRANSFER_CMD_FAIL |
                                    SDMMC_OSA_EVENT_TRANSFER_DATA_SUCCESS | SDMMC_OSA_EVENT_TRANSFER_DATA_FAIL,
                                SDMMCHOST_TRANSFER_COMPLETE_TIMEOUT, &event)) ||
            ((event & SDMMC_OSA_EVENT_TRANSFER_CMD_FAIL) != 0U))
        {
            error = kStatus_Fail;
        }
        else
        {
            if (content->data != NULL)
            {
                if ((event & SDMMC_OSA_EVENT_TRANSFER_DATA_SUCCESS) == 0U)
                {
                    if (((event & SDMMC_OSA_EVENT_TRANSFER_DATA_FAIL) != 0U) ||
                        (kStatus_Fail == SDMMC_OSAEventWait(
                                             &(host->hostEvent),
                                             SDMMC_OSA_EVENT_TRANSFER_DATA_SUCCESS | SDMMC_OSA_EVENT_TRANSFER_DATA_FAIL,
                                             SDMMCHOST_TRANSFER_COMPLETE_TIMEOUT, &event) ||
                         ((event & SDMMC_OSA_EVENT_TRANSFER_DATA_FAIL) != 0U)))
                    {
                        error = kStatus_Fail;
                    }
                }
            }
        }
    }
    /*
     * error = kStatus_SDIF_DescriptorBufferLenError means that the DMA descriptor buffer not len enough for current
     * transfer, application should assign a bigger descriptor memory space.
     */
    if (error != kStatus_Success)
    {
        error = kStatus_Fail;
        /* host error recovery */
        SDMMCHOST_ErrorRecovery(host->hostController.base);
    }

    SDMMC_OSAMutexUnlock(&host->lock);

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

    sdif_transfer_callback_t sdifCallback = {0};
    sdif_host_t *sdifHost                 = &(host->hostController);
    status_t error                        = kStatus_Success;

    /* host capability flags */
    host->capability = (uint32_t)kSDMMCHOST_SupportHighSpeed | (uint32_t)kSDMMCHOST_SupportSuspendResume |
                       (uint32_t)kSDMMCHOST_SupportVoltage3v3 | (uint32_t)kSDMMCHOST_Support4BitDataWidth |
                       (uint32_t)kSDMMCHOST_Support8BitDataWidth | (uint32_t)kSDMMCHOST_SupportDetectCardByData3 |
                       (uint32_t)kSDMMCHOST_SupportDetectCardByCD | (uint32_t)kSDMMCHOST_SupportAutoCmd12;
    host->maxBlockCount = SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT;
    host->maxBlockSize  = SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH;

    /* sdmmc osa init */
    SDMMC_OSAInit();

    SDMMC_OSAMutexCreate(&host->lock);
    SDMMC_OSAMutexLock(&host->lock, osaWaitForever_c);

    /* Initialize SDIF. */
    sdifHost->config.responseTimeout       = 0xFFU;
    sdifHost->config.cardDetDebounce_Clock = 0xFFFFFFU;
    sdifHost->config.dataTimeout           = 0xFFFFFFU;
    SDIF_Init(sdifHost->base, &(sdifHost->config));

    /* Create handle for SDIF driver */
    sdifCallback.TransferComplete = SDMMCHOST_TransferCompleteCallback;
    sdifCallback.cardInserted     = SDMMCHOST_DetectCardInsertByHost;
    sdifCallback.cardRemoved      = SDMMCHOST_DetectCardRemoveByHost;
    SDIF_TransferCreateHandle(sdifHost->base, &host->handle, &sdifCallback, host);

    /* Create transfer event. */
    if (kStatus_Success != SDMMC_OSAEventCreate(&(host->hostEvent)))
    {
        error = kStatus_Fail;
    }

    SDMMC_OSAMutexUnlock(&host->lock);

    return error;
}

void SDMMCHOST_Reset(sdmmchost_t *host)
{
    SDMMC_OSAMutexLock(&host->lock, osaWaitForever_c);

    /* disable all the interrupt */
    SDIF_DisableInterrupt(host->hostController.base, kSDIF_AllInterruptStatus);

    /* make sure host controller release all the bus line. */
    (void)SDIF_Reset(host->hostController.base, kSDIF_ResetAll, SDMMCHOST_RESET_TIMEOUT_VALUE);

    /* clear all interrupt/DMA status */
    SDIF_ClearInterruptStatus(host->hostController.base, kSDIF_AllInterruptStatus);
    SDIF_ClearInternalDMAStatus(host->hostController.base, kSDIF_DMAAllStatus);

    SDMMC_OSAMutexUnlock(&host->lock);
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
    SDMMC_OSAMutexLock(&host->lock, osaWaitForever_c);
    sdif_host_t *sdifHost = &host->hostController;
    SDIF_Deinit(sdifHost->base);
    (void)SDMMC_OSAEventDestroy(&(host->hostEvent));
    SDMMC_OSAMutexDestroy(&host->lock);
}
