/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "fsl_mmc.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/
/*! @brief The divide value used to avoid float point calculation when calculate max speed in normal mode. */
#define DIVIDER_IN_TRANSFER_SPEED (10U)
/*! @brief MMC CMD1 retry times */
#ifndef MMC_CMD1_RETRY_TIMES
#define MMC_CMD1_RETRY_TIMES (10000U)
#endif
#ifndef MMC_CMD13_RETRY_TIMES
#define MMC_CMD13_RETRY_TIMES (1000000U)
#endif
#ifndef MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT
#define MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT (10000U)
#endif
/*!@brief power reset delay */
#define MMC_POWER_RESET_DELAY (500U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Send SELECT_CARD command to set the card enter or exit transfer state.
 *
 * @param card Card descriptor.
 * @param isSelected True to enter transfer state.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static inline status_t MMC_SelectCard(mmc_card_t *card, bool isSelected);

/*!
 * @brief Send SET_BLOCK_COUNT command.
 *
 * @param card Card descriptor.
 * @param blockCount Block count.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static inline status_t MMC_SetBlockCount(mmc_card_t *card, uint32_t blockCount);

/*!
 * @brief Send GO_IDLE command to reset all cards to idle state
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static inline status_t MMC_GoIdle(mmc_card_t *card);

/*!
 * @brief Send STOP_TRANSMISSION command to card to stop ongoing data transferring.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_StopTransmission(mmc_card_t *card);

/*!
 * @brief Send SET_BLOCK_SIZE command to set the block length in bytes for MMC cards.
 *
 * @param card Card descriptor.
 * @param blockSize Block size.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static inline status_t MMC_SetBlockSize(mmc_card_t *card, uint32_t blockSize);

/*!
 * @brief Send SEND_OPERATION_CONDITION command to validate if the card support host's voltage window
 *
 * @param card Card descriptor.
 * @param arg Command argument.
 * @retval kStatus_SDMMC_TransferFailed Transfers failed.
 * @retval kStatus_Timeout Operation timeout.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SendOperationCondition(mmc_card_t *card, uint32_t arg);

/*!
 * @brief Send SET_RCA command to set the relative address of the card.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SetRelativeAddress(mmc_card_t *card);

/*!
 * @brief Decode CSD register content.
 *
 * @param card Card descriptor.
 * @param rawCsd raw CSD register content.
 */
static void MMC_DecodeCsd(mmc_card_t *card, uint32_t *rawCsd);

/*!
 * @brief Set the card to max transfer speed in non-high speed mode.
 *
 * @param card Card descriptor.
 */
static void MMC_SetMaxFrequency(mmc_card_t *card);

/*!
 * @brief Set erase unit size of the card
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure Extended CSD failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SetMaxEraseUnitSize(mmc_card_t *card);

/*!
 * @brief Send SWITCH command to set the specific byte in Extended CSD.
 *
 * Example:
   @code
   mmc_extended_csd_config_t config;
   config.accessMode = kMMC_ExtendedCsdAccessModeSetBits;
   config.ByteIndex = 1U;
   config.ByteValue = 0x033U;
   config.commandSet = kMMC_CommandSetStandard;
   MMC_SetExtendedCsdConfig(card, &config);
   @endcode
 *
 * @param card Card descriptor.
 * @param config Configuration for Extended CSD.
 * @param timeout switch command timeout value.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Wait write complete failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SetExtendedCsdConfig(mmc_card_t *card, const mmc_extended_csd_config_t *config, uint32_t timeout);

/*!
 * @brief Decode the Extended CSD register
 *
 * @param card Card descriptor.
 * @param rawExtendedCsd Raw extended CSD register content.
 */
static void MMC_DecodeExtendedCsd(mmc_card_t *card, uint32_t *rawExtendedCsd);

/*!
 * @brief Send SEND_EXTENDED_CSD command to get the content of the Extended CSD register
 * Allow read the special byte index value if targetAddr is not NULL
 * @param card Card descriptor.
 * @param targetAddr Pointer to store the target byte value.
 * @param byteIndex Target byte index.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SendExtendedCsd(mmc_card_t *card, uint8_t *targetAddr, uint32_t byteIndex);

/*!
 * @brief Set the power class of the card at specific bus width and host intended voltage window.
 *
 * @param card Card descriptor.
 * @return The power class switch status.
 */
static status_t MMC_SetPowerClass(mmc_card_t *card);

/*!
 * @brief Send test pattern to get the functional pin in the MMC bus
 *
 * @param card Card descriptor.
 * @param blockSize Test pattern block size.
 * @param pattern Test pattern data buffer.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SendTestPattern(mmc_card_t *card, uint32_t blockSize, uint32_t *pattern);

/*!
 * @brief Receive test pattern reversed by the card.
 *
 * @param card Card descriptor.
 * @param blockSize Test pattern block size.
 * @param pattern Test pattern data buffer.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_ReceiveTestPattern(mmc_card_t *card, uint32_t blockSize, uint32_t *pattern);

/*!
 * @brief Bus test procedure to get the functional data pin in the bus
 *
 * @param card Card descriptor.
 * @param width Data bus width.
 * @retval kStatus_SDMMC_SendTestPatternFailed Send test pattern failed.
 * @retval kStatus_SDMMC_ReceiveTestPatternFailed Receive test pattern failed.
 * @retval kStatus_Fail Test failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_TestDataBusWidth(mmc_card_t *card, mmc_data_bus_width_t width);

/*!
 * @brief Send SET_BUS_WIDTH command to set the bus width.
 *
 * @param card Card descriptor.
 * @param width Data bus width.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure extended CSD failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SetDataBusWidth(mmc_card_t *card, mmc_data_bus_width_t width);

/*!
 * @brief Set max the bus width automatically
 *
 * @param card Card descriptor.
 * @param targetTiming switch target timing
 * @retval kStatus_SDMMC_SetDataBusWidthFailed switch fail.
 * @retval kStatus_Success switch success.
 */
static status_t MMC_SetMaxDataBusWidth(mmc_card_t *card, mmc_high_speed_timing_t targetTiming);

/*!
 * @brief Switch the card to high speed mode
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure extended CSD failed.
 * @retval kStatus_SDMMC_CardNotSupport Card doesn't support high speed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SelectBusTiming(mmc_card_t *card);

/*!
 * @brief select card HS_TIMING value and card driver strength
 *
 * @param card Card descriptor.
 * @param timing Timing interface value.
 * @param driverStrength driver strength value.
 * @retval kStatus_Success switch success.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed , config extend csd register fail.
 */
static status_t MMC_SwitchHSTiming(mmc_card_t *card, uint8_t timing, uint8_t driverStrength);

/*!
 * @brief switch to HS400 mode.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure extended CSD failed.
 * @retval kStatus_SDMMC_SwitchBusTimingFailed switch bus timing fail.
 * @retval kStatus_SDMMC_SetDataBusWidthFailed switch bus width fail.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SwitchToHS400(mmc_card_t *card);

/*!
 * @brief switch to HS200 mode.
 *
 * @param card Card descriptor.
 * @param freq Target frequency.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure extended CSD failed.
 * @retval kStatus_SDMMC_TuningFail tuning fail.
 * @retval kStatus_SDMMC_SetDataBusWidthFailed switch bus width fail.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SwitchToHS200(mmc_card_t *card, uint32_t freq);

/*!
 * @brief switch to HS400 mode.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure extended CSD failed.
 * @retval kStatus_SDMMC_SetDataBusWidthFailed switch bus width fail.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SwitchToHighSpeed(mmc_card_t *card);

/*!
 * @brief Decode CID register
 *
 * @param card Card descriptor.
 * @param rawCid Raw CID register content.
 */
static void MMC_DecodeCid(mmc_card_t *card, uint32_t *rawCid);

/*!
 * @brief Send ALL_SEND_CID command
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_AllSendCid(mmc_card_t *card);

/*!
 * @brief Send SEND_CSD command to get CSD from card
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SendCsd(mmc_card_t *card);

/*!
 * @brief Check if the block range accessed is within current partition.
 *
 * @param card Card descriptor.
 * @param startBlock Start block to access.
 * @param blockCount Block count to access.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_CheckBlockRange(mmc_card_t *card, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Check if the erase group range accessed is within current partition.
 *
 * @param card Card descriptor.
 * @param startGroup Start group to access.
 * @param endGroup End group to access.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_CheckEraseGroupRange(mmc_card_t *card, uint32_t startGroup, uint32_t endGroup);

/*!
 * @brief MMC excute tuning function.
 *
 * @param card Card descriptor.
 * @retval kStatus_Success Operate successfully.
 * @retval kStatus_SDMMC_TuningFail tuning fail.
 * @retval kStatus_SDMMC_TransferFailed transfer fail
 */
static inline status_t MMC_ExecuteTuning(mmc_card_t *card);
/*!
 * @brief Read data from specific MMC card
 *
 * @param card Card descriptor.
 * @param buffer Buffer to save received data.
 * @param startBlock Start block to read.
 * @param blockSize Block size.
 * @param blockCount Block count to read.
 * @retval kStatus_SDMMC_CardNotSupport Card doesn't support.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Wait write complete failed.
 * @retval kStatus_SDMMC_SetBlockCountFailed Set block count failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_Read(
    mmc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockSize, uint32_t blockCount);

/*!
 * @brief Write data from specific MMC card
 *
 * @param card Card descriptor.
 * @param buffer Buffer to hold the data to write.
 * @param startBlock Start block to write.
 * @param blockSize Block size.
 * @param blockCount Block count to write.
 * @retval kStatus_SDMMC_CardNotSupport Card doesn't support.
 * @retval kStatus_SDMMC_SetBlockCountFailed Set block count failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_Write(
    mmc_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockSize, uint32_t blockCount);

/*!
 * @brief MMC card erase function
 *
 * @param card Card descriptor.
 * @param startGroupAddress start erase group address.
 * @param endGroupAddress end erase group address.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_Erase(mmc_card_t *card, uint32_t startGroupAddress, uint32_t endGroupAddress);

/*!
 * @brief card transfer function wrapper
 * This function is used to do tuning before transfer if the cmd won't casue re-tuning
 * request, then you can call host transfer function directly
 * @param card Card descriptor.
 * @param content Transfer content.
 * @param retry Retry times.
 * @retval kStatus_SDMMC_TransferFailed transfer fail
 * @retval kStatus_SDMMC_TuningFail tuning fail
 * @retval kStatus_Success transfer success
 */
static status_t MMC_Transfer(mmc_card_t *card, sdmmchost_transfer_t *content, uint32_t retry);

/*!
 * @brief card validate operation voltage
 * This function is used to validate the operation voltage bettwen host and card
 *
 * @param card Card descriptor.
 * @param opcode Retry times.
 * @retval kStatus_Fail the operation voltage condition doesn't match between card and host
 * @retval kStatus_Success voltage validate successfully
 */
static status_t MMC_ValidateOperationVoltage(mmc_card_t *card, uint32_t *opcode);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Frequency unit defined in TRANSFER SPEED field in CSD */
static const uint32_t g_transerSpeedFrequencyUnit[] = {100000U, 1000000U, 10000000U, 100000000U};
/* The multiplying value defined in TRANSFER SPEED field in CSD */
static const uint32_t g_transerSpeedMultiplierFactor[] = {0U,  10U, 12U, 13U, 15U, 20U, 26U, 30U,
                                                          35U, 40U, 45U, 52U, 55U, 60U, 70U, 80U};

/*******************************************************************************
 * Code
 ******************************************************************************/
static inline status_t MMC_SelectCard(mmc_card_t *card, bool isSelected)
{
    assert(card != NULL);

    return SDMMC_SelectCard(card->host, card->relativeAddress, isSelected);
}

static inline status_t MMC_SetBlockCount(mmc_card_t *card, uint32_t blockCount)
{
    assert(card != NULL);

    return SDMMC_SetBlockCount(card->host, blockCount);
}

static inline status_t MMC_GoIdle(mmc_card_t *card)
{
    assert(card != NULL);

    return SDMMC_GoIdle(card->host);
}

static inline status_t MMC_SetBlockSize(mmc_card_t *card, uint32_t blockSize)
{
    assert(card != NULL);

    return SDMMC_SetBlockSize(card->host, blockSize);
}

static status_t MMC_ExecuteTuning(mmc_card_t *card)
{
    assert(card != NULL);

    uint32_t blockSize = 0U;

    if (card->busWidth == kMMC_DataBusWidth4bit)
    {
        blockSize = 64U;
    }
    else if (card->busWidth == kMMC_DataBusWidth8bit)
    {
        blockSize = 128U;
    }
    else
    {
        /* do not need tuning in this situation */
        return kStatus_Success;
    }

    return SDMMCHOST_ExecuteTuning(card->host, (uint32_t)kMMC_SendTuningBlock,
                                   (uint32_t *)FSL_SDMMC_CARD_INTERNAL_BUFFER_ALIGN_ADDR(card->internalBuffer),
                                   blockSize);
}

static status_t MMC_Transfer(mmc_card_t *card, sdmmchost_transfer_t *content, uint32_t retry)
{
    assert(content != NULL);
    status_t error;
    uint32_t retuningCount = 3U;

    do
    {
        error = SDMMCHOST_TransferFunction(card->host, content);

        if (error == kStatus_Success)
        {
            break;
        }

        if (((retry == 0U) && (content->data != NULL)) || (error == kStatus_SDMMC_ReTuningRequest))
        {
            /* abort previous transfer firstly */
            (void)MMC_StopTransmission(card);

            if (card->busTiming == kMMC_HighSpeed200Timing)
            {
                if (--retuningCount == 0U)
                {
                    break;
                }
                /* perform retuning */
                if (MMC_ExecuteTuning(card) != kStatus_Success)
                {
                    error = kStatus_SDMMC_TuningFail;
                    SDMMC_LOG("\r\nError: retuning failed.");
                    break;
                }
                else
                {
                    SDMMC_LOG("\r\nlog: retuning successfully.");
                    continue;
                }
            }
        }

        if (retry != 0U)
        {
            retry--;
        }
        else
        {
            break;
        }

    } while (true);

    return error;
}

static status_t MMC_SendStatus(mmc_card_t *card, uint32_t *status)
{
    assert(card != NULL);
    status_t error               = kStatus_Success;
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    uint32_t retry               = 10;

    command.index        = (uint32_t)kSDMMC_SendStatus;
    command.argument     = card->relativeAddress << 16U;
    command.responseType = kCARD_ResponseTypeR1;

    content.command = &command;
    content.data    = NULL;

    while (retry != 0U)
    {
        error = MMC_Transfer(card, &content, 2U);
        if ((--retry == 0U) && (error != kStatus_Success))
        {
            return kStatus_SDMMC_TransferFailed;
        }

        if (kStatus_Success == error)
        {
            break;
        }
    }

    *status = command.response[0U];

    return error;
}

status_t MMC_PollingCardStatusBusy(mmc_card_t *card, bool checkStatus, uint32_t timeoutMs)
{
    assert(card != NULL);

    uint32_t statusTimeoutUs = timeoutMs * 1000U;
    bool cardBusy            = false;
    status_t error           = kStatus_SDMMC_CardStatusBusy;
    uint32_t status          = 0U;

    do
    {
        cardBusy = SDMMCHOST_IsCardBusy(card->host);

        if (cardBusy == false)
        {
            if (checkStatus)
            {
                error = MMC_SendStatus(card, &status);
                if (kStatus_Success == error)
                {
                    /* check the response error */
                    if (0U != (status & (SDMMC_R1_ALL_ERROR_FLAG | SDMMC_MASK(kSDMMC_R1SwitchErrorFlag))))
                    {
                        SDMMC_LOG("\r\nError: CMD13 report switch error %x.", status);

                        error = kStatus_SDMMC_SwitchFailed;
                    }
                    else if ((0U != (status & SDMMC_MASK(kSDMMC_R1ReadyForDataFlag))) &&
                             (SDMMC_R1_CURRENT_STATE(status) != (uint32_t)kSDMMC_R1StateProgram))
                    {
                        error = kStatus_SDMMC_CardStatusIdle;
                        break;
                    }
                    else
                    {
                        SDMMC_LOG("\r\nWarning: CMD13 report busy %x.", status);
                        error = kStatus_SDMMC_CardStatusBusy;
                    }
                }
                else
                {
                    error = kStatus_SDMMC_TransferFailed;
                    break;
                }
            }
            else
            {
                error = kStatus_SDMMC_CardStatusIdle;
                break;
            }
        }

        if (statusTimeoutUs != 0U)
        {
            /* Delay 125us to throttle the polling rate */
            statusTimeoutUs -= SDMMC_OSADelayUs(125U);
        }

    } while (statusTimeoutUs != 0U);

    return error;
}

static status_t MMC_StopTransmission(mmc_card_t *card)
{
    assert(card != NULL);

    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index              = (uint32_t)kSDMMC_StopTransmission;
    command.argument           = 0U;
    command.type               = kCARD_CommandTypeAbort;
    command.responseType       = kCARD_ResponseTypeR1b;
    command.responseErrorFlags = SDMMC_R1_ALL_ERROR_FLAG;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

static status_t MMC_SendOperationCondition(mmc_card_t *card, uint32_t arg)
{
    assert(card != NULL);

    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};
    status_t error;
    uint32_t i = MMC_CMD1_RETRY_TIMES;

    /* Send CMD1 with the intended voltage range in the argument(either 0x00FF8000 or 0x00000080) */
    command.index        = (uint32_t)kMMC_SendOperationCondition;
    command.argument     = arg;
    command.responseType = kCARD_ResponseTypeR3;

    content.command = &command;
    content.data    = NULL;
    do
    {
        error = SDMMCHOST_TransferFunction(card->host, &content);

        if (error == kStatus_Success)
        {
            /* record OCR register */
            card->ocr = command.response[0U];

            if ((arg == 0U) && (command.response[0U] != 0U))
            {
                error = kStatus_Success;
            }
            /* Repeat CMD1 until the busy bit is cleared. */
            else if (0U == (command.response[0U] & MMC_OCR_BUSY_MASK))
            {
                error = kStatus_Timeout;
            }
            else
            {
                error = kStatus_Success;
                if (((card->ocr & MMC_OCR_ACCESS_MODE_MASK) >> MMC_OCR_ACCESS_MODE_SHIFT) ==
                    (uint32_t)kMMC_AccessModeSector)
                {
                    card->flags |= (uint32_t)kMMC_SupportHighCapacityFlag;
                }
            }
        }

        SDMMC_OSADelay(10U);

    } while ((0U != i--) && (error != kStatus_Success));

    return error;
}

static status_t MMC_SetRelativeAddress(mmc_card_t *card)
{
    assert(card != NULL);

    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};
    status_t error               = kStatus_Success;

    /* Send CMD3 with a chosen relative address, with value greater than 1 */
    command.index        = (uint32_t)kMMC_SetRelativeAddress;
    command.argument     = (MMC_DEFAULT_RELATIVE_ADDRESS << 16U);
    command.responseType = kCARD_ResponseTypeR1;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if ((kStatus_Success == error) || (0U == ((command.response[0U]) & SDMMC_R1_ALL_ERROR_FLAG)))
    {
        card->relativeAddress = MMC_DEFAULT_RELATIVE_ADDRESS;
        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static void MMC_DecodeCsd(mmc_card_t *card, uint32_t *rawCsd)
{
    assert(card != NULL);
    assert(rawCsd != NULL);

    mmc_csd_t *csd;
    uint32_t multiplier;

    csd                             = &(card->csd);
    csd->csdStructureVersion        = (uint8_t)((rawCsd[3U] & 0xC0000000U) >> 30U);
    csd->systemSpecificationVersion = (uint8_t)((rawCsd[3U] & 0x3C000000U) >> 26U);
    csd->dataReadAccessTime1        = (uint8_t)((rawCsd[3U] & 0xFF0000U) >> 16U);
    csd->dataReadAccessTime2        = (uint8_t)((rawCsd[3U] & 0xFF00U) >> 8U);
    csd->transferSpeed              = (uint8_t)(rawCsd[3U] & 0xFFU);
    csd->cardCommandClass           = (uint16_t)((rawCsd[2U] & 0xFFF00000U) >> 20U);
    /* Max block length read/write one time */
    csd->readBlockLength = (uint8_t)((rawCsd[2U] & 0xF0000U) >> 16U);
    if ((rawCsd[2U] & 0x8000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdReadBlockPartialFlag;
    }
    if ((rawCsd[2U] & 0x4000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdWriteBlockMisalignFlag;
    }
    if ((rawCsd[2U] & 0x2000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdReadBlockMisalignFlag;
    }
    if ((rawCsd[2U] & 0x1000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdDsrImplementedFlag;
    }
    csd->deviceSize               = (uint16_t)(((rawCsd[2U] & 0x3FFU) << 2U) + ((rawCsd[1U] & 0xC0000000U) >> 30U));
    csd->readCurrentVddMin        = (uint8_t)((rawCsd[1U] & 0x38000000U) >> 27U);
    csd->readCurrentVddMax        = (uint8_t)((rawCsd[1U] & 0x07000000U) >> 24U);
    csd->writeCurrentVddMin       = (uint8_t)((rawCsd[1U] & 0x00E00000U) >> 21U);
    csd->writeCurrentVddMax       = (uint8_t)((rawCsd[1U] & 0x001C0000U) >> 18U);
    csd->deviceSizeMultiplier     = (uint8_t)((rawCsd[1U] & 0x00038000U) >> 15U);
    csd->eraseGroupSize           = (uint8_t)((rawCsd[1U] & 0x00007C00U) >> 10U);
    csd->eraseGroupSizeMultiplier = (uint8_t)((rawCsd[1U] & 0x000003E0U) >> 5U);
    csd->writeProtectGroupSize    = (uint8_t)(rawCsd[1U] & 0x0000001FU);
    if ((rawCsd[0U] & 0x80000000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdWriteProtectGroupEnabledFlag;
    }
    csd->defaultEcc          = (uint8_t)((rawCsd[0U] & 0x60000000U) >> 29U);
    csd->writeSpeedFactor    = (uint8_t)((rawCsd[0U] & 0x1C000000U) >> 26U);
    csd->maxWriteBlockLength = (uint8_t)((rawCsd[0U] & 0x03C00000U) >> 22U);
    if ((rawCsd[0U] & 0x00200000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdWriteBlockPartialFlag;
    }
    if ((rawCsd[0U] & 0x00010000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_ContentProtectApplicationFlag;
    }
    if ((rawCsd[0U] & 0x00008000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdFileFormatGroupFlag;
    }
    if ((rawCsd[0U] & 0x00004000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdCopyFlag;
    }
    if ((rawCsd[0U] & 0x00002000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdPermanentWriteProtectFlag;
    }
    if ((rawCsd[0U] & 0x00001000U) != 0U)
    {
        csd->flags |= (uint16_t)kMMC_CsdTemporaryWriteProtectFlag;
    }
    csd->fileFormat = (uint8_t)((rawCsd[0U] & 0x00000C00U) >> 10U);
    csd->eccCode    = (uint8_t)((rawCsd[0U] & 0x00000300U) >> 8U);

    /* Calculate the device total block count. */
    /* For the card capacity of witch higher than 2GB, the maximum possible value should be set to this register
    is 0xFFF. */
    if (card->csd.deviceSize != 0xFFFU)
    {
        multiplier                = (2UL << (card->csd.deviceSizeMultiplier + 2U - 1U));
        card->userPartitionBlocks = (((card->csd.deviceSize + 1UL) * multiplier) / FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    }

    card->blockSize = FSL_SDMMC_DEFAULT_BLOCK_SIZE;
}

static void MMC_SetMaxFrequency(mmc_card_t *card)
{
    assert(card != NULL);

    uint32_t frequencyUnit;
    uint32_t multiplierFactor;
    uint32_t maxBusClock_Hz;

    /* g_fsdhcCommandUnitInTranSpeed and g_transerSpeedMultiplierFactor are used to calculate the max speed in normal
    mode not high speed mode.
    For cards supporting version 4.0, 4.1, and 4.2 of the specification, the value shall be 20MHz(0x2A).
    For cards supporting version 4.3, the value shall be 26 MHz (0x32H). In High speed mode, the max
    frequency is decided by CARD_TYPE in Extended CSD. */
    frequencyUnit     = g_transerSpeedFrequencyUnit[READ_MMC_TRANSFER_SPEED_FREQUENCY_UNIT(card->csd)];
    multiplierFactor  = g_transerSpeedMultiplierFactor[READ_MMC_TRANSFER_SPEED_MULTIPLIER(card->csd)];
    maxBusClock_Hz    = (frequencyUnit * multiplierFactor) / DIVIDER_IN_TRANSFER_SPEED;
    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, maxBusClock_Hz);
}

static status_t MMC_SetMaxEraseUnitSize(mmc_card_t *card)
{
    assert(card != NULL);

    uint32_t erase_group_size;
    uint32_t erase_group_multiplier;
    mmc_extended_csd_config_t extendedCsdconfig;

    /* Legacy mmc card , do not support the command */
    if ((card->csd.systemSpecificationVersion == (uint32_t)kMMC_SpecificationVersion3) &&
        (card->csd.csdStructureVersion == (uint32_t)kMMC_CsdStrucureVersion12))
    {
        return kStatus_Success;
    }

    if (((0U == (card->flags & (uint32_t)kMMC_SupportHighCapacityFlag)) ||
         (card->extendedCsd.highCapacityEraseUnitSize == 0U)) ||
        (card->extendedCsd.highCapacityEraseTimeout == 0U))
    {
        erase_group_size       = card->csd.eraseGroupSize;
        erase_group_multiplier = card->csd.eraseGroupSizeMultiplier;
        card->eraseGroupBlocks = ((erase_group_size + 1U) * (erase_group_multiplier + 1U));
    }
    else
    {
        /* Erase Unit Size = 512Kbyte * HC_ERASE_GRP_SIZE. Block size is 512 bytes. */
        card->eraseGroupBlocks = (card->extendedCsd.highCapacityEraseUnitSize * 1024UL);
        /* Enable high capacity erase unit size. */
        extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeSetBits;
        extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexEraseGroupDefinition;
        extendedCsdconfig.ByteValue  = 0x01U; /* The high capacity erase unit size enable bit is bit 0 */
        extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
        if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
        {
            return kStatus_SDMMC_ConfigureExtendedCsdFailed;
        }
    }

    return kStatus_Success;
}

static status_t MMC_SetExtendedCsdConfig(mmc_card_t *card, const mmc_extended_csd_config_t *config, uint32_t timeout)
{
    assert(card != NULL);
    assert(config != NULL);

    status_t error               = kStatus_Success;
    uint32_t parameter           = 0U;
    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};
    uint32_t timeoutMS           = timeout == 0U ? card->extendedCsd.genericCMD6Timeout : timeout;

    parameter |= ((uint32_t)(config->commandSet) << MMC_SWITCH_COMMAND_SET_SHIFT);
    parameter |= ((uint32_t)(config->ByteValue) << MMC_SWITCH_VALUE_SHIFT);
    parameter |= ((uint32_t)(config->ByteIndex) << MMC_SWITCH_BYTE_INDEX_SHIFT);
    parameter |= ((uint32_t)(config->accessMode) << MMC_SWITCH_ACCESS_MODE_SHIFT);
    command.index        = (uint32_t)kMMC_Switch;
    command.argument     = parameter;
    command.responseType = kCARD_ResponseTypeR1b; /* Send switch command to set the pointed byte in Extended CSD. */
    command.responseErrorFlags = SDMMC_R1_ALL_ERROR_FLAG | SDMMC_MASK(kSDMMC_R1SwitchErrorFlag);

    content.command = &command;
    content.data    = NULL;
    error           = MMC_Transfer(card, &content, 2U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Wait for the card write process complete because of that card read process and write process use one buffer. */
    error = MMC_PollingCardStatusBusy(card, true, timeoutMS == 0U ? MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT : timeoutMS);
    if (kStatus_SDMMC_CardStatusIdle != error)
    {
        return kStatus_SDMMC_PollingCardIdleFailed;
    }

    return kStatus_Success;
}

static void MMC_DecodeExtendedCsd(mmc_card_t *card, uint32_t *rawExtendedCsd)
{
    assert(card != NULL);
    assert(rawExtendedCsd != NULL);

    uint8_t *buffer                 = (uint8_t *)rawExtendedCsd;
    mmc_extended_csd_t *extendedCsd = &(card->extendedCsd);

    /* Extended CSD is transferred as a data block from least byte indexed 0. */
    extendedCsd->bootPartitionWP                 = buffer[173U];
    extendedCsd->bootWPStatus                    = buffer[174U];
    extendedCsd->highDensityEraseGroupDefinition = buffer[175U];
    extendedCsd->bootDataBusConditions           = buffer[177U];
    extendedCsd->bootConfigProtect               = buffer[178U];
    extendedCsd->partitionConfig                 = buffer[179U];
    extendedCsd->eraseMemoryContent              = buffer[181U];
    extendedCsd->dataBusWidth                    = buffer[183U];
    extendedCsd->highSpeedTiming                 = buffer[185U];
    extendedCsd->powerClass                      = buffer[187U];
    extendedCsd->commandSetRevision              = buffer[189U];
    extendedCsd->commandSet                      = buffer[191U];
    extendedCsd->extendecCsdVersion              = buffer[192U];
    extendedCsd->csdStructureVersion             = buffer[194U];
    extendedCsd->partitionAttribute              = buffer[156U];
    extendedCsd->extPartitionSupport             = buffer[494U];
    extendedCsd->cardType                        = buffer[196U];
    /* This field define the type of the card. The only currently valid values for this field are 0x01 and 0x03. */
    card->flags |= extendedCsd->cardType;

    extendedCsd->ioDriverStrength = buffer[197U];

    extendedCsd->partitionSwitchTimeout                    = buffer[199U];
    extendedCsd->powerClass52MHz195V                       = buffer[200U];
    extendedCsd->powerClass26MHz195V                       = buffer[201U];
    extendedCsd->powerClass52MHz360V                       = buffer[202U];
    extendedCsd->powerClass26MHz360V                       = buffer[203U];
    extendedCsd->powerClass200MHZVCCQ130VVCC360V           = buffer[236U];
    extendedCsd->powerClass200MHZVCCQ195VVCC360V           = buffer[237U];
    extendedCsd->powerClass52MHZDDR195V                    = buffer[238U];
    extendedCsd->powerClass52MHZDDR360V                    = buffer[239U];
    extendedCsd->powerClass200MHZDDR360V                   = buffer[253U];
    extendedCsd->minimumReadPerformance4Bit26MHz           = buffer[205U];
    extendedCsd->minimumWritePerformance4Bit26MHz          = buffer[206U];
    extendedCsd->minimumReadPerformance8Bit26MHz4Bit52MHz  = buffer[207U];
    extendedCsd->minimumWritePerformance8Bit26MHz4Bit52MHz = buffer[208U];
    extendedCsd->minimumReadPerformance8Bit52MHz           = buffer[209U];
    extendedCsd->minimumWritePerformance8Bit52MHz          = buffer[210U];
    extendedCsd->minReadPerformance8bitAt52MHZDDR          = buffer[234U];
    extendedCsd->minWritePerformance8bitAt52MHZDDR         = buffer[235U];
    /* Get user partition size. */
    extendedCsd->sectorCount = ((((uint32_t)buffer[215U]) << 24U) + (((uint32_t)buffer[214U]) << 16U) +
                                (((uint32_t)buffer[213U]) << 8U) + (uint32_t)buffer[212U]);
    if ((card->flags & (uint32_t)kMMC_SupportHighCapacityFlag) != 0U)
    {
        card->userPartitionBlocks = card->extendedCsd.sectorCount;
    }

    extendedCsd->sleepAwakeTimeout                 = buffer[217U];
    extendedCsd->sleepCurrentVCCQ                  = buffer[219U];
    extendedCsd->sleepCurrentVCC                   = buffer[220U];
    extendedCsd->highCapacityWriteProtectGroupSize = buffer[221U];
    extendedCsd->reliableWriteSectorCount          = buffer[222U];
    extendedCsd->highCapacityEraseTimeout          = buffer[223U];
    extendedCsd->highCapacityEraseUnitSize         = buffer[224U];
    extendedCsd->accessSize                        = buffer[225U];

    /* Get boot partition size: 128KB * BOOT_SIZE_MULT*/
    card->bootPartitionBlocks = ((128U * 1024U * buffer[226U]) / FSL_SDMMC_DEFAULT_BLOCK_SIZE);

    /* support HS400 data strobe */
    if (buffer[184] == 1U)
    {
        card->flags |= (uint32_t)kMMC_SupportEnhanceHS400StrobeFlag;
    }

    /* Check if card support boot mode. */
    if ((buffer[228U] & 0x1U) != 0U)
    {
        card->flags |= (uint32_t)kMMC_SupportAlternateBootFlag;
    }
    else if ((buffer[228U] & 0x2U) != 0U)
    {
        card->flags |= (uint32_t)kMMC_SupportDDRBootFlag;
    }
    else if ((buffer[228U] & 0x4U) != 0U)
    {
        card->flags |= (uint32_t)kMMC_SupportHighSpeedBootFlag;
    }
    else
    {
        /* empty with intentional */
    }
    /* cache size unit 1kb */
    extendedCsd->cacheSize = (((uint32_t)buffer[252U]) << 24) | (((uint32_t)buffer[251U]) << 16) |
                             (((uint32_t)buffer[250U]) << 8) | (((uint32_t)buffer[249U]));

    extendedCsd->genericCMD6Timeout  = buffer[248U] * 10UL;
    extendedCsd->supportedCommandSet = buffer[504U];
}

static status_t MMC_SendExtendedCsd(mmc_card_t *card, uint8_t *targetAddr, uint32_t byteIndex)
{
    assert(card != NULL);

    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};
    sdmmchost_data_t data        = {0};
    uint32_t *alignBuffer        = (uint32_t *)FSL_SDMMC_CARD_INTERNAL_BUFFER_ALIGN_ADDR(card->internalBuffer);
    status_t error               = kStatus_Success;

    /* Legacy mmc card , do not support the command */
    if ((card->csd.systemSpecificationVersion == (uint32_t)kMMC_SpecificationVersion3) &&
        (card->csd.csdStructureVersion == (uint32_t)kMMC_CsdStrucureVersion12))
    {
        return kStatus_Success;
    }

    (void)memset(alignBuffer, 0, MMC_EXTENDED_CSD_BYTES);

    command.index        = (uint32_t)kMMC_SendExtendedCsd;
    command.argument     = 0U;
    command.responseType = kCARD_ResponseTypeR1;

    data.blockCount = 1U;
    data.blockSize  = MMC_EXTENDED_CSD_BYTES;
    data.rxData     = alignBuffer;

    content.command = &command;
    content.data    = &data;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if ((kStatus_Success == error) && (0U == (command.response[0U] & SDMMC_R1_ALL_ERROR_FLAG)))
    {
        SDMMCHOST_ConvertDataToLittleEndian(card->host, alignBuffer, MMC_EXTENDED_CSD_BYTES / 4U,
                                            kSDMMC_DataPacketFormatLSBFirst);
        if (targetAddr != NULL)
        {
            *targetAddr = (uint8_t)alignBuffer[byteIndex];
        }
        else
        {
            MMC_DecodeExtendedCsd(card, alignBuffer);
        }

        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static status_t MMC_SetPowerClass(mmc_card_t *card)
{
    assert(card != NULL);

    uint8_t mask = 0, shift = 0U;
    uint8_t powerClass = 0;
    mmc_extended_csd_config_t extendedCsdconfig;

    /* Legacy mmc card , do not support the command */
    if ((card->csd.systemSpecificationVersion == (uint32_t)kMMC_SpecificationVersion3) &&
        (card->csd.csdStructureVersion == (uint32_t)kMMC_CsdStrucureVersion12))
    {
        return kStatus_Success;
    }

    if ((card->busWidth == kMMC_DataBusWidth4bit) || (card->busWidth == kMMC_DataBusWidth4bitDDR))
    {
        mask  = MMC_POWER_CLASS_4BIT_MASK; /* The mask of 4 bit bus width's power class */
        shift = 0U;
    }
    else if ((card->busWidth == kMMC_DataBusWidth8bit) || (card->busWidth == kMMC_DataBusWidth8bitDDR))
    {
        mask  = MMC_POWER_CLASS_8BIT_MASK; /* The mask of 8 bit bus width's power class */
        shift = 4U;
    }
    else
    {
        return kStatus_Success;
    }

    switch (card->hostVoltageWindowVCC)
    {
        case kMMC_VoltageWindows270to360:

            if (card->busTiming == kMMC_HighSpeed200Timing)
            {
                if (card->hostVoltageWindowVCCQ == kMMC_VoltageWindow170to195)
                {
                    powerClass = ((card->extendedCsd.powerClass200MHZVCCQ195VVCC360V) & mask);
                }
                else if (card->hostVoltageWindowVCCQ == kMMC_VoltageWindow120)
                {
                    powerClass = ((card->extendedCsd.powerClass200MHZVCCQ130VVCC360V) & mask);
                }
                else
                {
                    /* intentional empty */
                }
            }
            else if (card->busTiming == kMMC_HighSpeed400Timing)
            {
                powerClass = ((card->extendedCsd.powerClass200MHZDDR360V) & mask);
            }
            else if ((card->busTiming == kMMC_HighSpeedTiming) && (card->busWidth > kMMC_DataBusWidth8bit))
            {
                powerClass = ((card->extendedCsd.powerClass52MHZDDR360V) & mask);
            }
            else if ((card->busTiming == kMMC_HighSpeedTiming) && (card->busClock_Hz > MMC_CLOCK_26MHZ))
            {
                powerClass = ((card->extendedCsd.powerClass52MHz360V) & mask);
            }
            else if (card->busTiming == kMMC_HighSpeedTiming)
            {
                powerClass = ((card->extendedCsd.powerClass26MHz360V) & mask);
            }
            else
            {
                /* intentional empty */
            }

            break;

        case kMMC_VoltageWindow170to195:

            if ((card->busTiming == kMMC_HighSpeedTiming) && (card->busClock_Hz <= MMC_CLOCK_26MHZ))
            {
                powerClass = ((card->extendedCsd.powerClass26MHz195V) & mask);
            }
            else if ((card->busTiming == kMMC_HighSpeedTiming) && (card->busClock_Hz > MMC_CLOCK_26MHZ))
            {
                powerClass = ((card->extendedCsd.powerClass52MHz195V) & mask);
            }
            else if ((card->busTiming == kMMC_HighSpeedTiming) && (card->busWidth > kMMC_DataBusWidth8bit))
            {
                powerClass = ((card->extendedCsd.powerClass52MHZDDR195V) & mask);
            }
            else
            {
                /* intentional empty */
            }

            break;
        default:
            powerClass = 0;
            break;
    }

    /* due to 8bit power class position [7:4] */
    powerClass >>= shift;

    if (powerClass > 0U)
    {
        extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
        extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexPowerClass;
        extendedCsdconfig.ByteValue  = powerClass;
        extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
        if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
        {
            return kStatus_SDMMC_ConfigureExtendedCsdFailed;
        }
        /* restore power class */
        card->extendedCsd.powerClass = powerClass;
    }

    return kStatus_Success;
}

static status_t MMC_SendTestPattern(mmc_card_t *card, uint32_t blockSize, uint32_t *pattern)
{
    assert(card != NULL);
    assert(blockSize <= FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    assert(pattern != NULL);

    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    sdmmchost_data_t data        = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kMMC_SendingBusTest;
    command.argument     = 0U;
    command.responseType = kCARD_ResponseTypeR1;

    /* Ignore errors in bus test procedure to improve chances that the test will work. */
    data.enableIgnoreError = true;
    data.blockCount        = 1U;
    data.blockSize         = blockSize;
    data.txData            = pattern;

    content.command = &command;
    content.data    = &data;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if ((kStatus_Success != error) || ((command.response[0U] & SDMMC_R1_ALL_ERROR_FLAG) != 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

static status_t MMC_ReceiveTestPattern(mmc_card_t *card, uint32_t blockSize, uint32_t *pattern)
{
    assert(card != NULL);
    assert(blockSize <= FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    assert(pattern != NULL);

    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    sdmmchost_data_t data        = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kMMC_BusTestRead;
    command.responseType = kCARD_ResponseTypeR1;

    /* Ignore errors in bus test procedure to improve chances that the test will work. */
    data.enableIgnoreError = true;
    data.blockCount        = 1U;
    data.blockSize         = blockSize;
    data.rxData            = pattern;

    content.command = &command;
    content.data    = &data;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if ((kStatus_Success != error) || (((command.response[0U]) & SDMMC_R1_ALL_ERROR_FLAG) != 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

static status_t MMC_TestDataBusWidth(mmc_card_t *card, mmc_data_bus_width_t width)
{
    assert(card != NULL);

    uint32_t blockSize       = 0U;
    uint32_t tempsendPattern = 0U;
    uint32_t *tempPattern    = (uint32_t *)FSL_SDMMC_CARD_INTERNAL_BUFFER_ALIGN_ADDR(card->internalBuffer);
    uint32_t xorMask         = 0U;
    uint32_t xorResult       = 0U;

    /* For 8 data lines the data block would be (MSB to LSB): 0x0000_0000_0000_AA55,
    For 4 data lines the data block would be (MSB to LSB): 0x0000_005A,
    For only 1 data line the data block would be: 0x80 */
    switch (width)
    {
        case kMMC_DataBusWidth8bit:
        case kMMC_DataBusWidth8bitDDR:
            blockSize       = 8U;
            tempPattern[0U] = 0xAA55U;
            xorMask         = 0xFFFFU;
            xorResult       = 0xFFFFU;
            break;
        case kMMC_DataBusWidth4bit:
        case kMMC_DataBusWidth4bitDDR:
            blockSize       = 4U;
            tempPattern[0U] = 0x5AU;
            xorMask         = 0xFFU;
            xorResult       = 0xFFU;
            break;
        default:
            blockSize       = 4U;
            tempPattern[0U] = 0x80U;
            xorMask         = 0xFFU;
            xorResult       = 0xC0U;
            break;
    }

    SDMMCHOST_ConvertDataToLittleEndian(card->host, &tempPattern[0], 1U, kSDMMC_DataPacketFormatLSBFirst);
    SDMMCHOST_ConvertDataToLittleEndian(card->host, &xorMask, 1U, kSDMMC_DataPacketFormatLSBFirst);
    SDMMCHOST_ConvertDataToLittleEndian(card->host, &xorResult, 1U, kSDMMC_DataPacketFormatLSBFirst);

    (void)MMC_SendTestPattern(card, blockSize, tempPattern);
    /* restore the send pattern */
    tempsendPattern = tempPattern[0U];
    /* reset the global buffer */
    tempPattern[0U] = 0U;

    (void)MMC_ReceiveTestPattern(card, blockSize, tempPattern);

    /* XOR the send pattern and receive pattern */
    if (((tempPattern[0U] ^ tempsendPattern) & xorMask) != xorResult)
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

static status_t MMC_SetDataBusWidth(mmc_card_t *card, mmc_data_bus_width_t width)
{
    assert(card != NULL);

    mmc_extended_csd_config_t extendedCsdconfig;

    /* Set data bus width */
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexBusWidth;
    extendedCsdconfig.ByteValue  = (uint8_t)width;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }
    /* restore data bus width */
    card->extendedCsd.dataBusWidth = (uint8_t)width;

    return kStatus_Success;
}

static status_t MMC_SetMaxDataBusWidth(mmc_card_t *card, mmc_high_speed_timing_t targetTiming)
{
    assert(card != NULL);

    status_t error = kStatus_Fail;

    do
    {
        if (card->busWidth == kMMC_DataBusWidth1bit)
        {
            card->busWidth = kMMC_DataBusWidth8bitDDR;
        }

        if (card->busWidth == kMMC_DataBusWidth8bitDDR)
        {
            if (((card->host->capability &
                  ((uint32_t)kSDMMCHOST_Support8BitDataWidth | (uint32_t)kSDMMCHOST_SupportDDRMode)) ==
                 ((uint32_t)kSDMMCHOST_Support8BitDataWidth | (uint32_t)kSDMMCHOST_SupportDDRMode)) &&
                (0U != (card->flags & ((uint32_t)kMMC_SupportHighSpeedDDR52MHZ180V300VFlag |
                                       (uint32_t)kMMC_SupportHighSpeedDDR52MHZ120VFlag))) &&
                ((targetTiming == kMMC_HighSpeedTiming) || (targetTiming == kMMC_HighSpeed400Timing)) &&
                ((card->usrParam.capability & (uint32_t)kSDMMC_Support8BitWidth) != 0U))
            {
                SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith8Bit);
                if (kStatus_Success == MMC_TestDataBusWidth(card, kMMC_DataBusWidth8bitDDR))
                {
                    if (kStatus_Success == MMC_SetDataBusWidth(card, kMMC_DataBusWidth8bitDDR))
                    {
                        error          = kStatus_Success;
                        card->busWidth = kMMC_DataBusWidth8bitDDR;
                        break;
                    }
                }

                /* HS400 mode only support 8bit data bus */
                if (card->busTiming == kMMC_HighSpeed400Timing)
                {
                    return kStatus_SDMMC_SetDataBusWidthFailed;
                }
            }
            card->busWidth = kMMC_DataBusWidth4bitDDR;
        }

        if (card->busWidth == kMMC_DataBusWidth4bitDDR)
        {
            if (((card->host->capability &
                  ((uint32_t)kSDMMCHOST_Support4BitDataWidth | (uint32_t)kSDMMCHOST_SupportDDRMode)) ==
                 ((uint32_t)kSDMMCHOST_Support4BitDataWidth | (uint32_t)kSDMMCHOST_SupportDDRMode)) &&
                (0U != (card->flags & ((uint32_t)kMMC_SupportHighSpeedDDR52MHZ180V300VFlag |
                                       (uint32_t)kMMC_SupportHighSpeedDDR52MHZ120VFlag))) &&
                ((targetTiming == kMMC_HighSpeedTiming) || (targetTiming == kMMC_HighSpeed400Timing)))
            {
                SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith4Bit);
                if (kStatus_Success == MMC_TestDataBusWidth(card, kMMC_DataBusWidth4bitDDR))
                {
                    if (kStatus_Success == MMC_SetDataBusWidth(card, kMMC_DataBusWidth4bitDDR))
                    {
                        error          = kStatus_Success;
                        card->busWidth = kMMC_DataBusWidth4bitDDR;
                        break;
                    }
                }
            }
            card->busWidth = kMMC_DataBusWidth8bit;
        }

        if (card->busWidth == kMMC_DataBusWidth8bit)
        {
            if (((card->host->capability & (uint32_t)kSDMMCHOST_Support8BitDataWidth) != 0U) &&
                ((targetTiming == kMMC_HighSpeedTiming) || (targetTiming == kMMC_HighSpeed200Timing)) &&
                ((card->usrParam.capability & (uint32_t)kSDMMC_Support8BitWidth) != 0U))
            {
                SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith8Bit);
                if (kStatus_Success == MMC_TestDataBusWidth(card, kMMC_DataBusWidth8bit))
                {
                    if (kStatus_Success == MMC_SetDataBusWidth(card, kMMC_DataBusWidth8bit))
                    {
                        error          = kStatus_Success;
                        card->busWidth = kMMC_DataBusWidth8bit;
                        break;
                    }
                }
            }
            card->busWidth = kMMC_DataBusWidth4bit;
        }

        if (card->busWidth == kMMC_DataBusWidth4bit)
        {
            if (((card->host->capability & (uint32_t)kSDMMCHOST_Support8BitDataWidth) != 0U) &&
                ((targetTiming == kMMC_HighSpeedTiming) || (targetTiming == kMMC_HighSpeed200Timing)))
            {
                SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith4Bit);
                if (kStatus_Success == MMC_TestDataBusWidth(card, kMMC_DataBusWidth4bit))
                {
                    if (kStatus_Success == MMC_SetDataBusWidth(card, kMMC_DataBusWidth4bit))
                    {
                        error          = kStatus_Success;
                        card->busWidth = kMMC_DataBusWidth4bit;
                        break;
                    }
                }
                /* HS200 mode only support 4bit/8bit data bus */
                if (targetTiming == kMMC_HighSpeed200Timing)
                {
                    return kStatus_SDMMC_SetDataBusWidthFailed;
                }
            }
        }

    } while (false);

    if (error == kStatus_Fail)
    {
        /* Card's data bus width will be default 1 bit mode. */
        SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith1Bit);
        card->busWidth = kMMC_DataBusWidth1bit;
    }

    return kStatus_Success;
}

static status_t MMC_SwitchHSTiming(mmc_card_t *card, uint8_t timing, uint8_t driverStrength)
{
    assert(card != NULL);

    uint8_t hsTiming = 0;

    mmc_extended_csd_config_t extendedCsdconfig;

    /* check the target driver strength support or not */
    if (((card->extendedCsd.ioDriverStrength & (1U << driverStrength)) == 0U) &&
        (card->extendedCsd.extendecCsdVersion >= (uint8_t)kMMC_ExtendedCsdRevision17))
    {
        return kStatus_SDMMC_NotSupportYet;
    }
    /* calucate the register value */
    hsTiming = (timing & 0xFU) | (uint8_t)(driverStrength << 4U);

    /* Switch to high speed timing. */
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexHighSpeedTiming;
    extendedCsdconfig.ByteValue  = hsTiming;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.highSpeedTiming = hsTiming;

    return kStatus_Success;
}

static status_t MMC_SwitchToHighSpeed(mmc_card_t *card)
{
    assert(card != NULL);

    uint32_t freq = 0U;

    if (kStatus_Success != MMC_SwitchHSTiming(card, (uint8_t)kMMC_HighSpeedTiming, kMMC_DriverStrength0))
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    if ((card->flags & (uint32_t)kMMC_SupportHighSpeed52MHZFlag) != 0U)
    {
        freq = FSL_SDMMC_CARD_MAX_BUS_FREQ(card->usrParam.maxFreq, MMC_CLOCK_52MHZ);
    }
    else if ((card->flags & (uint32_t)kMMC_SupportHighSpeed26MHZFlag) != 0U)
    {
        freq = FSL_SDMMC_CARD_MAX_BUS_FREQ(card->usrParam.maxFreq, MMC_CLOCK_26MHZ);
    }
    else
    {
        /* Intentional empty */
    }

    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, freq);
    /* config io speed and strength */
    if (card->usrParam.ioStrength != NULL)
    {
        card->usrParam.ioStrength(MMC_CLOCK_52MHZ);
    }
    /* Set card data width, it is nessesary to config the the data bus here, to meet emmc5.0 specification,
     * when you are working in DDR mode , HS_TIMING must set before set bus width
     */
    if (MMC_SetMaxDataBusWidth(card, kMMC_HighSpeedTiming) != kStatus_Success)
    {
        return kStatus_SDMMC_SetDataBusWidthFailed;
    }

    if ((card->busWidth == kMMC_DataBusWidth4bitDDR) || (card->busWidth == kMMC_DataBusWidth8bitDDR))
    {
        SDMMCHOST_EnableDDRMode(card->host, true, 0U);
    }

    card->busTiming = kMMC_HighSpeedTiming;

    return kStatus_Success;
}

static status_t MMC_SwitchToHS200(mmc_card_t *card, uint32_t freq)
{
    assert(card != NULL);

    status_t error = kStatus_Fail;

    if ((card->hostVoltageWindowVCCQ != kMMC_VoltageWindow170to195) &&
        (card->hostVoltageWindowVCCQ != kMMC_VoltageWindow120))
    {
        return kStatus_SDMMC_InvalidVoltage;
    }

    /* select bus width before select bus timing for HS200 mode */
    if (MMC_SetMaxDataBusWidth(card, kMMC_HighSpeed200Timing) != kStatus_Success)
    {
        return kStatus_SDMMC_SetDataBusWidthFailed;
    }

    /* switch to HS200 mode */
    if (kStatus_Success != MMC_SwitchHSTiming(card, (uint8_t)kMMC_HighSpeed200Timing, kMMC_DriverStrength0))
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, freq);
    /* config io speed and strength */
    if (card->usrParam.ioStrength != NULL)
    {
        card->usrParam.ioStrength(freq);
    }

    /* excute tuning for HS200 */
    if (MMC_ExecuteTuning(card) != kStatus_Success)
    {
        return kStatus_SDMMC_TuningFail;
    }

    card->busTiming = kMMC_HighSpeed200Timing;

    error = MMC_PollingCardStatusBusy(card, true, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (kStatus_SDMMC_CardStatusIdle != error)
    {
        return kStatus_SDMMC_PollingCardIdleFailed;
    }

    return kStatus_Success;
}

static status_t MMC_SwitchToHS400(mmc_card_t *card)
{
    assert(card != NULL);

    uint32_t status    = 0U;
    uint32_t hs400Freq = FSL_SDMMC_CARD_MAX_BUS_FREQ(card->usrParam.maxFreq, MMC_CLOCK_HS400);
    status_t error     = kStatus_Fail;

    if ((card->hostVoltageWindowVCCQ != kMMC_VoltageWindow170to195) &&
        (card->hostVoltageWindowVCCQ != kMMC_VoltageWindow120))
    {
        return kStatus_SDMMC_InvalidVoltage;
    }

    if (card->host->hostController.sourceClock_Hz < MMC_CLOCK_HS400)
    {
        hs400Freq = card->host->hostController.sourceClock_Hz;
    }

    if ((card->host->hostController.sourceClock_Hz > MMC_CLOCK_HS400) &&
        (card->host->hostController.sourceClock_Hz % MMC_CLOCK_HS400 != 0U))
    {
        hs400Freq = card->host->hostController.sourceClock_Hz /
                    (card->host->hostController.sourceClock_Hz / MMC_CLOCK_HS400 + 1U);
    }
    /* HS400 mode support 8 bit data bus only */
    card->busWidth = kMMC_DataBusWidth8bit;
    /* switch to HS200 perform tuning */
    if (kStatus_Success != MMC_SwitchToHS200(card, hs400Freq / 2U))
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    /* check data bus width is 8 bit , otherwise return false*/
    if (card->busWidth != kMMC_DataBusWidth8bit)
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    /*
     * For the issue found in stress test of repeat emmc initialization operation, after HS200 switch complete, the emmc
     * status not correct for switching to high speed, normally the emmc should stay in TRAN state, but sometimes the
     * emmc status is in DATA state which will cause switch to High speed failed. when such issue happen, software will
     * try to use CMD12 to reset the emmc status to TRAN before switch to high speed for HS400.
     */
    error = MMC_SendStatus(card, &status);
    if (error != kStatus_Success)
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    if (SDMMC_R1_CURRENT_STATE(status) == (uint32_t)kSDMMC_R1StateSendData)
    {
        SDMMC_LOG("status uncorrect for switching to High speed timing, try use CMD12 to get back to TRAN state\r\n");
        /* try to get back to transfer state before switch to High speed */
        (void)MMC_StopTransmission(card);
    }

    /*switch to high speed*/
    if (kStatus_Success != MMC_SwitchHSTiming(card, (uint8_t)kMMC_HighSpeedTiming, kMMC_DriverStrength0))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    /* switch to high speed first */
    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, MMC_CLOCK_52MHZ);
    /* config io strength */
    if (card->usrParam.ioStrength != NULL)
    {
        card->usrParam.ioStrength(MMC_CLOCK_52MHZ);
    }

    card->busTiming = kMMC_HighSpeed400Timing;
    /* switch to 8 bit DDR data bus width */
    if (kStatus_Success != MMC_SetDataBusWidth(card, kMMC_DataBusWidth8bitDDR))
    {
        return kStatus_SDMMC_SetDataBusWidthFailed;
    }
    /* switch to HS400 */
    if (kStatus_Success != MMC_SwitchHSTiming(card, (uint8_t)kMMC_HighSpeed400Timing, kMMC_DriverStrength0))
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }
    /* config to target freq */
    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, hs400Freq / 2U);
    /* config io speed and strength */
    if (card->usrParam.ioStrength != NULL)
    {
        card->usrParam.ioStrength(MMC_CLOCK_HS200);
    }
    /* enable HS400 mode */
    SDMMCHOST_EnableHS400Mode(card->host, true);
    /* enable DDR mode */
    SDMMCHOST_EnableDDRMode(card->host, true, 0U);
    /* config strobe DLL*/
    SDMMCHOST_EnableStrobeDll(card->host, true);

    return kStatus_Success;
}

static status_t MMC_SelectBusTiming(mmc_card_t *card)
{
    assert(card != NULL);

    /* Legacy mmc card , do not support the command */
    if ((card->csd.systemSpecificationVersion == (uint8_t)kMMC_SpecificationVersion3) &&
        (card->csd.csdStructureVersion == (uint8_t)kMMC_CsdStrucureVersion12))
    {
        return kStatus_Success;
    }

    do
    {
        if (card->busTiming == kMMC_HighSpeedTimingNone)
        {
            /* if timing not specified, probe card capability from HS400 mode */
            card->busTiming = kMMC_HighSpeed400Timing;
        }

        if (card->busTiming == kMMC_EnhanceHighSpeed400Timing)
        {
            return kStatus_SDMMC_NotSupportYet;
        }

        if (card->busTiming == kMMC_HighSpeed400Timing)
        {
            if (((card->host->capability & (uint32_t)kSDMMCHOST_SupportHS400) != 0U) &&
                ((card->hostVoltageWindowVCCQ == kMMC_VoltageWindow170to195) ||
                 (card->hostVoltageWindowVCCQ == kMMC_VoltageWindow120)) &&
                ((card->flags &
                  ((uint32_t)kMMC_SupportHS400DDR200MHZ180VFlag | (uint32_t)kMMC_SupportHS400DDR200MHZ120VFlag)) != 0U))
            {
                /* switch to HS400 */
                if (kStatus_Success != MMC_SwitchToHS400(card))
                {
                    return kStatus_SDMMC_SwitchBusTimingFailed;
                }
                break;
            }

            card->busTiming = kMMC_HighSpeed200Timing;
        }

        if (card->busTiming == kMMC_HighSpeed200Timing)
        {
            if (((card->host->capability & (uint32_t)kSDMMCHOST_SupportHS200) != 0U) &&
                ((card->hostVoltageWindowVCCQ == kMMC_VoltageWindow170to195) ||
                 (card->hostVoltageWindowVCCQ == kMMC_VoltageWindow120)) &&
                (0U != (card->flags &
                        ((uint32_t)kMMC_SupportHS200200MHZ180VFlag | (uint32_t)kMMC_SupportHS200200MHZ120VFlag))))
            {
                if (kStatus_Success !=
                    MMC_SwitchToHS200(card, FSL_SDMMC_CARD_MAX_BUS_FREQ(card->usrParam.maxFreq, MMC_CLOCK_HS200)))
                {
                    return kStatus_SDMMC_SwitchBusTimingFailed;
                }
                break;
            }

            card->busTiming = kMMC_HighSpeedTiming;
        }

        if (card->busTiming == kMMC_HighSpeedTiming)
        {
            if (kStatus_Success != MMC_SwitchToHighSpeed(card))
            {
                return kStatus_SDMMC_SwitchBusTimingFailed;
            }
            break;
        }
    } while (false);

    return kStatus_Success;
}

static void MMC_DecodeCid(mmc_card_t *card, uint32_t *rawCid)
{
    assert(card != NULL);
    assert(rawCid != NULL);

    mmc_cid_t *cid;

    cid                 = &(card->cid);
    cid->manufacturerID = (uint8_t)((rawCid[3U] & 0xFF000000U) >> 24U);
    cid->applicationID  = (uint16_t)((rawCid[3U] & 0xFFFF00U) >> 8U);

    cid->productName[0U] = (uint8_t)((rawCid[3U] & 0xFFU));
    cid->productName[1U] = (uint8_t)((rawCid[2U] & 0xFF000000U) >> 24U);
    cid->productName[2U] = (uint8_t)((rawCid[2U] & 0xFF0000U) >> 16U);
    cid->productName[3U] = (uint8_t)((rawCid[2U] & 0xFF00U) >> 8U);
    cid->productName[4U] = (uint8_t)((rawCid[2U] & 0xFFU));

    cid->productVersion = (uint8_t)((rawCid[1U] & 0xFF000000U) >> 24U);

    cid->productSerialNumber = (uint32_t)((rawCid[1U] & 0xFFFFFFU) << 8U);
    cid->productSerialNumber |= (uint32_t)((rawCid[0U] & 0xFF000000U) >> 24U);

    cid->manufacturerData = (uint8_t)((rawCid[0U] & 0xFFF00U) >> 8U);
}

static status_t MMC_AllSendCid(mmc_card_t *card)
{
    assert(card != NULL);

    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kSDMMC_AllSendCid;
    command.argument     = 0U;
    command.responseType = kCARD_ResponseTypeR2;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if (kStatus_Success == error)
    {
        (void)memcpy(card->internalBuffer, (uint8_t *)command.response, 16U);
        MMC_DecodeCid(card, command.response);

        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static status_t MMC_SendCsd(mmc_card_t *card)
{
    assert(card != NULL);

    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kSDMMC_SendCsd;
    command.argument     = (card->relativeAddress << 16U);
    command.responseType = kCARD_ResponseTypeR2;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(card->host, &content);
    if (kStatus_Success == error)
    {
        (void)memcpy(card->internalBuffer, (uint8_t *)command.response, 16U);
        /* The response is from bit 127:8 in R2, corresponding to command.response[3][31:0] to
        command.response[0U][31:8]. */
        MMC_DecodeCsd(card, (uint32_t *)(uint32_t)card->internalBuffer);

        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static status_t MMC_CheckBlockRange(mmc_card_t *card, uint32_t startBlock, uint32_t blockCount)
{
    assert(card != NULL);
    assert(blockCount != 0U);

    status_t error = kStatus_Success;
    uint32_t partitionBlocks;

    switch (card->currentPartition)
    {
        case kMMC_AccessPartitionUserAera:
        {
            partitionBlocks = card->userPartitionBlocks;
            break;
        }
        case kMMC_AccessPartitionBoot1:
        case kMMC_AccessPartitionBoot2:
        {
            /* Boot partition 1 and partition 2 have the same partition size. */
            partitionBlocks = card->bootPartitionBlocks;
            break;
        }
        default:
            error = kStatus_InvalidArgument;
            break;
    }
    /* Check if the block range accessed is within current partition's block boundary. */
    if ((error == kStatus_Success) && ((startBlock + blockCount) > partitionBlocks))
    {
        error = kStatus_InvalidArgument;
    }

    return error;
}

static status_t MMC_CheckEraseGroupRange(mmc_card_t *card, uint32_t startGroup, uint32_t endGroup)
{
    assert(card != NULL);

    status_t error = kStatus_Success;
    uint32_t partitionBlocks;
    uint32_t eraseGroupBoundary;

    switch (card->currentPartition)
    {
        case kMMC_AccessPartitionUserAera:
        {
            partitionBlocks = card->userPartitionBlocks;
            break;
        }
        case kMMC_AccessPartitionBoot1:
        case kMMC_AccessPartitionBoot2:
        {
            /* Boot partition 1 and partition 2 have the same partition size. */
            partitionBlocks = card->bootPartitionBlocks;
            break;
        }
        default:
            error = kStatus_InvalidArgument;
            break;
    }

    if (error == kStatus_Success)
    {
        /* Check if current partition's total block count is integer multiples of the erase group size. */
        if ((partitionBlocks % card->eraseGroupBlocks) == 0U)
        {
            eraseGroupBoundary = (partitionBlocks / card->eraseGroupBlocks);
        }
        else
        {
            /* Card will ignore the unavailable blocks within the last erase group automatically. */
            eraseGroupBoundary = (partitionBlocks / card->eraseGroupBlocks + 1U);
        }

        /* Check if the group range accessed is within current partition's erase group boundary. */
        if ((startGroup > eraseGroupBoundary) || (endGroup > eraseGroupBoundary))
        {
            error = kStatus_InvalidArgument;
        }
    }

    return error;
}

static status_t MMC_Read(
    mmc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockSize, uint32_t blockCount)
{
    assert(card != NULL);
    assert(buffer != NULL);
    assert(blockCount != 0U);
    assert(blockSize != 0U);
    assert(blockSize == FSL_SDMMC_DEFAULT_BLOCK_SIZE);

    sdmmchost_cmd_t command      = {0};
    sdmmchost_data_t data        = {0};
    sdmmchost_transfer_t content = {0};
    status_t error;

    if ((((card->flags & (uint32_t)kMMC_SupportHighCapacityFlag) != 0U) && (blockSize != 512U)) ||
        (blockSize > card->blockSize) || (blockSize > card->host->maxBlockSize) || (0U != (blockSize % 4U)))
    {
        return kStatus_SDMMC_CardNotSupport;
    }

    error = MMC_PollingCardStatusBusy(card, true, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (kStatus_SDMMC_CardStatusIdle != error)
    {
        SDMMC_LOG("Error : read failed with wrong card status\r\n");
        return kStatus_SDMMC_PollingCardIdleFailed;
    }

    data.blockSize           = blockSize;
    data.blockCount          = blockCount;
    data.rxData              = (uint32_t *)(uint32_t)buffer;
    data.enableAutoCommand12 = true;
    command.index            = (uint32_t)kSDMMC_ReadMultipleBlock;
    if (data.blockCount == 1U)
    {
        command.index = (uint32_t)kSDMMC_ReadSingleBlock;
    }
    else
    {
        if (card->enablePreDefinedBlockCount)
        {
            data.enableAutoCommand12 = false;
            /* If enabled the pre-define count read/write feature of the card, need to set block count firstly. */
            if (kStatus_Success != MMC_SetBlockCount(card, blockCount))
            {
                return kStatus_SDMMC_SetBlockCountFailed;
            }
        }
    }
    command.argument = startBlock;
    if (0U == (card->flags & (uint32_t)kMMC_SupportHighCapacityFlag))
    {
        command.argument *= data.blockSize;
    }
    command.responseType       = kCARD_ResponseTypeR1;
    command.responseErrorFlags = SDMMC_R1_ALL_ERROR_FLAG;

    content.command = &command;
    content.data    = &data;

    /* should check tuning error during every transfer */
    error = MMC_Transfer(card, &content, 3U);
    if (kStatus_Success != error)
    {
        return error;
    }

    /* When host's AUTO_COMMAND12 feature isn't enabled and PRE_DEFINED_COUNT command isn't enabled in multiple
    blocks transmission, sends STOP_TRANSMISSION command. */
    if ((blockCount > 1U) && (!(data.enableAutoCommand12)) && (!card->enablePreDefinedBlockCount))
    {
        if (kStatus_Success != MMC_StopTransmission(card))
        {
            return kStatus_SDMMC_StopTransmissionFailed;
        }
    }

    return kStatus_Success;
}

static status_t MMC_Write(
    mmc_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockSize, uint32_t blockCount)
{
    assert(card != NULL);
    assert(buffer != NULL);
    assert(blockCount != 0U);
    assert(blockSize != 0U);
    assert(blockSize == FSL_SDMMC_DEFAULT_BLOCK_SIZE);

    sdmmchost_cmd_t command      = {0};
    sdmmchost_data_t data        = {0};
    sdmmchost_transfer_t content = {0};
    status_t error;

    /* Check address range */
    if ((((card->flags & (uint32_t)kMMC_SupportHighCapacityFlag) != 0U) && (blockSize != 512U)) ||
        (blockSize > card->blockSize) || (blockSize > card->host->maxBlockSize) || (0U != (blockSize % 4U)))
    {
        return kStatus_SDMMC_CardNotSupport;
    }

    /* send CMD13 to make sure card is ready for data */
    error = MMC_PollingCardStatusBusy(card, true, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (kStatus_SDMMC_CardStatusIdle != error)
    {
        SDMMC_LOG("Error : write card busy with wrong card status\r\n");
        return kStatus_SDMMC_PollingCardIdleFailed;
    }

    data.blockSize           = blockSize;
    data.blockCount          = blockCount;
    data.txData              = (const uint32_t *)(uint32_t)buffer;
    data.enableAutoCommand12 = true;

    command.index = (uint32_t)kSDMMC_WriteMultipleBlock;
    if (data.blockCount == 1U)
    {
        command.index = (uint32_t)kSDMMC_WriteSingleBlock;
    }
    else
    {
        if (card->enablePreDefinedBlockCount)
        {
            data.enableAutoCommand12 = false;
            /* If enabled the pre-define count read/write featue of the card, need to set block count firstly */
            if (kStatus_Success != MMC_SetBlockCount(card, blockCount))
            {
                return kStatus_SDMMC_SetBlockCountFailed;
            }
        }
    }
    command.argument = startBlock;
    if (0U == (card->flags & (uint32_t)kMMC_SupportHighCapacityFlag))
    {
        command.argument *= blockSize;
    }
    command.responseType       = kCARD_ResponseTypeR1;
    command.responseErrorFlags = SDMMC_R1_ALL_ERROR_FLAG;

    content.command = &command;
    content.data    = &data;

    /* should check tuning error during every transfer */
    error = MMC_Transfer(card, &content, 3U);
    if (kStatus_Success != error)
    {
        return error;
    }

    /* When host's AUTO_COMMAND12 feature isn't enabled and PRE_DEFINED_COUNT command isn't enabled in multiple
    blocks transmission, sends STOP_TRANSMISSION command. */
    if ((blockCount > 1U) && (!(data.enableAutoCommand12)) && (!card->enablePreDefinedBlockCount))
    {
        if (kStatus_Success != MMC_StopTransmission(card))
        {
            return kStatus_SDMMC_StopTransmissionFailed;
        }
    }

    return kStatus_Success;
}

static status_t MMC_ValidateOperationVoltage(mmc_card_t *card, uint32_t *opcode)
{
    status_t status = kStatus_Fail;

    if (card->hostVoltageWindowVCC == kMMC_VoltageWindow170to195)
    {
        if ((card->ocr & MMC_OCR_V170TO195_MASK) != 0U)
        {
            *opcode |= MMC_OCR_V170TO195_MASK;
            status = kStatus_Success;
        }
    }
    else if (card->hostVoltageWindowVCC == kMMC_VoltageWindows270to360)
    {
        if ((card->ocr & MMC_OCR_V270TO360_MASK) != 0U)
        {
            *opcode |= MMC_OCR_V270TO360_MASK;
            status = kStatus_Success;
        }
    }
    else
    {
        /* Intentional empty */
    }

    return status;
}

static status_t mmccard_init(mmc_card_t *card)
{
    assert(card != NULL);
    assert((card->hostVoltageWindowVCC != kMMC_VoltageWindowNone) &&
           (card->hostVoltageWindowVCC != kMMC_VoltageWindow120));
    assert(card->hostVoltageWindowVCCQ != kMMC_VoltageWindowNone);

    uint32_t opcode = 0U;
    status_t error  = kStatus_Success;

    if (!card->isHostReady)
    {
        return kStatus_SDMMC_HostNotReady;
    }
    /* set DATA bus width */
    SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith1Bit);
    /* Set clock to 400KHz. */
    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, SDMMC_CLOCK_400KHZ);

    error = MMC_GoIdle(card);
    /* Send CMD0 to reset the bus */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_GoIdleFailed;
    }

    /* Hand-shaking with card to validata the voltage range Host first sending its expected
       information.*/
    error = MMC_SendOperationCondition(card, 0U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_HandShakeOperationConditionFailed;
    }

    error = MMC_ValidateOperationVoltage(card, &opcode);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_InvalidVoltage;
    }

    /* Get host's access mode. */
    opcode |= (card->host->maxBlockSize >= FSL_SDMMC_DEFAULT_BLOCK_SIZE ?
                   (uint32_t)kMMC_AccessModeSector << MMC_OCR_ACCESS_MODE_SHIFT :
                   (uint32_t)kMMC_AccessModeByte << MMC_OCR_ACCESS_MODE_SHIFT);

    error = MMC_SendOperationCondition(card, opcode);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_HandShakeOperationConditionFailed;
    }

    /* Get card CID */
    error = MMC_AllSendCid(card);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_AllSendCidFailed;
    }

    error = MMC_SetRelativeAddress(card);
    /* Set the card relative address */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SetRelativeAddressFailed;
    }

    error = MMC_SendCsd(card);
    /* Get the CSD register content */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SendCsdFailed;
    }

    /* Set to maximum speed in normal mode. */
    MMC_SetMaxFrequency(card);

    /* Send CMD7 with the card's relative address to place the card in transfer state. Puts current selected card in
    transfer state. */
    error = MMC_SelectCard(card, true);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SelectCardFailed;
    }

    /* Get Extended CSD register content. */
    error = MMC_SendExtendedCsd(card, NULL, 0U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SendExtendedCsdFailed;
    }

    error = MMC_SetMaxEraseUnitSize(card);
    /* Set to max erase unit size */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_EnableHighCapacityEraseFailed;
    }

    error = MMC_SetBlockSize(card, FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    /* set block size */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SetCardBlockSizeFailed;
    }

    error = MMC_SelectBusTiming(card);
    /* switch to host support speed mode, then switch MMC data bus width and select power class */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    error = MMC_SetPowerClass(card);
    /* switch power class */
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_SetPowerClassFail;
    }

    /* trying to enable the cache */
    (void)MMC_EnableCacheControl(card, true);

    /* Set card default to access non-boot partition */
    card->currentPartition = kMMC_AccessPartitionUserAera;

    return kStatus_Success;
}

status_t MMC_CardInit(mmc_card_t *card)
{
    assert(card != NULL);

    status_t error = kStatus_Success;
    /* create mutex lock */
    (void)SDMMC_OSAMutexCreate(&card->lock);
    (void)SDMMC_OSAMutexLock(&card->lock, osaWaitForever_c);

    error = mmccard_init(card);

    (void)SDMMC_OSAMutexUnlock(&card->lock);

    return error;
}

void MMC_CardDeinit(mmc_card_t *card)
{
    assert(card != NULL);

    (void)SDMMC_OSAMutexLock(&card->lock, osaWaitForever_c);

    (void)MMC_SelectCard(card, false);

    (void)SDMMC_OSAMutexDestroy(&card->lock);
}

status_t MMC_HostInit(mmc_card_t *card)
{
    assert(card != NULL);

    if (!card->isHostReady)
    {
        if (SDMMCHOST_Init(card->host) != kStatus_Success)
        {
            return kStatus_Fail;
        }
    }

    /* set the host status flag, after the card re-plug in, don't need init host again */
    card->isHostReady = true;

    return kStatus_Success;
}

void MMC_HostDeinit(mmc_card_t *card)
{
    assert(card != NULL);

    SDMMCHOST_Deinit(card->host);
    /* should re-init host */
    card->isHostReady = false;
}

void MMC_HostReset(SDMMCHOST_CONFIG *host)
{
    SDMMCHOST_Reset(host);
}

void MMC_HostDoReset(mmc_card_t *card)
{
    SDMMCHOST_Reset(card->host);
}

void MMC_SetCardPower(mmc_card_t *card, bool enable)
{
    SDMMCHOST_SetCardPower(card->host, enable);
    SDMMC_OSADelay(MMC_POWER_RESET_DELAY);
}

status_t MMC_Init(mmc_card_t *card)
{
    assert(card != NULL);

    status_t error = kStatus_Success;

    if (!card->isHostReady)
    {
        if (MMC_HostInit(card) != kStatus_Success)
        {
            error = kStatus_SDMMC_HostNotReady;
        }
    }
    else
    {
        /* reset the host */
        MMC_HostDoReset(card);
    }

    if (error == kStatus_Success)
    {
        /* reset card power */
        MMC_SetCardPower(card, false);
        MMC_SetCardPower(card, true);

        error = MMC_CardInit(card);
        if (error != kStatus_Success)
        {
            error = kStatus_SDMMC_CardInitFailed;
        }
    }

    return error;
}

void MMC_Deinit(mmc_card_t *card)
{
    assert(card != NULL);

    MMC_CardDeinit(card);
    MMC_HostDeinit(card);
}

bool MMC_CheckReadOnly(mmc_card_t *card)
{
    assert(card != NULL);

    return (((card->csd.flags & (uint16_t)kMMC_CsdPermanentWriteProtectFlag) != 0U) ||
            ((card->csd.flags & (uint16_t)kMMC_CsdTemporaryWriteProtectFlag) != 0U));
}

status_t MMC_SelectPartition(mmc_card_t *card, mmc_access_partition_t partitionNumber)
{
    assert(card != NULL);

    uint8_t bootConfig;
    mmc_extended_csd_config_t extendedCsdconfig;
    status_t error = kStatus_Success;

    (void)SDMMC_OSAMutexLock(&card->lock, osaWaitForever_c);

    bootConfig = card->extendedCsd.partitionConfig;
    bootConfig &= ~(uint8_t)MMC_PARTITION_CONFIG_PARTITION_ACCESS_MASK;
    bootConfig |= ((uint8_t)partitionNumber << MMC_PARTITION_CONFIG_PARTITION_ACCESS_SHIFT);

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexPartitionConfig;
    extendedCsdconfig.ByteValue  = bootConfig;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success !=
        MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, (uint32_t)card->extendedCsd.partitionSwitchTimeout * 10U))
    {
        error = kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }
    else
    {
        /* Save current configuration. */
        card->extendedCsd.partitionConfig = bootConfig;
        card->currentPartition            = partitionNumber;
    }

    (void)SDMMC_OSAMutexUnlock(&card->lock);

    return error;
}

status_t MMC_ReadBlocks(mmc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    assert(card != NULL);
    assert(buffer != NULL);
    assert(blockCount != 0U);

    uint32_t blockCountOneTime; /* The block count can be erased in one time sending READ_BLOCKS command. */
    uint32_t blockDone;         /* The blocks has been read. */
    uint32_t blockLeft;         /* Left blocks to be read. */
    uint8_t *nextBuffer;
    bool dataAddrAlign   = true;
    uint8_t *alignBuffer = (uint8_t *)FSL_SDMMC_CARD_INTERNAL_BUFFER_ALIGN_ADDR(card->internalBuffer);
    status_t error       = kStatus_Success;

    (void)SDMMC_OSAMutexLock(&card->lock, osaWaitForever_c);

    blockLeft = blockCount;
    blockDone = 0U;
    error     = MMC_CheckBlockRange(card, startBlock, blockCount);
    if (kStatus_Success != error)
    {
        error = kStatus_InvalidArgument;
    }
    else
    {
        while (blockLeft != 0U)
        {
            nextBuffer = (uint8_t *)((uint32_t)buffer + blockDone * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
            if (!card->noInteralAlign && (!dataAddrAlign || ((((uint32_t)nextBuffer) & (sizeof(uint32_t) - 1U)) != 0U)))
            {
                blockLeft--;
                blockCountOneTime = 1U;
                (void)memset(alignBuffer, 0, FSL_SDMMC_DEFAULT_BLOCK_SIZE);
                dataAddrAlign = false;
            }
            else
            {
                if (blockLeft > card->host->maxBlockCount)
                {
                    blockLeft         = (blockLeft - card->host->maxBlockCount);
                    blockCountOneTime = card->host->maxBlockCount;
                }
                else
                {
                    blockCountOneTime = blockLeft;
                    blockLeft         = 0U;
                }
            }

            error = MMC_Read(card, dataAddrAlign ? nextBuffer : (uint8_t *)alignBuffer, (startBlock + blockDone),
                             FSL_SDMMC_DEFAULT_BLOCK_SIZE, blockCountOneTime);
            if (kStatus_Success != error)
            {
                error = kStatus_SDMMC_TransferFailed;
                break;
            }

            blockDone += blockCountOneTime;

            if (!card->noInteralAlign && (!dataAddrAlign))
            {
                (void)memcpy(nextBuffer, alignBuffer, FSL_SDMMC_DEFAULT_BLOCK_SIZE);
            }
        }
    }

    (void)SDMMC_OSAMutexUnlock(&card->lock);

    return error;
}

status_t MMC_WriteBlocks(mmc_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    assert(card != NULL);
    assert(buffer != NULL);
    assert(blockCount != 0U);

    uint32_t blockCountOneTime;
    uint32_t blockLeft;
    uint32_t blockDone;
    const uint8_t *nextBuffer;
    bool dataAddrAlign   = true;
    uint8_t *alignBuffer = (uint8_t *)FSL_SDMMC_CARD_INTERNAL_BUFFER_ALIGN_ADDR(card->internalBuffer);
    status_t error       = kStatus_Success;

    (void)SDMMC_OSAMutexLock(&card->lock, osaWaitForever_c);

    blockLeft = blockCount;
    blockDone = 0U;

    error = MMC_CheckBlockRange(card, startBlock, blockCount);
    if (kStatus_Success != error)
    {
        error = kStatus_InvalidArgument;
    }
    else
    {
        while (blockLeft != 0U)
        {
            nextBuffer = (uint8_t *)((uint32_t)buffer + blockDone * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
            if (!card->noInteralAlign && (!dataAddrAlign || (0U != (((uint32_t)nextBuffer) & (sizeof(uint32_t) - 1U)))))
            {
                blockLeft--;
                blockCountOneTime = 1U;
                (void)memcpy(alignBuffer, nextBuffer, FSL_SDMMC_DEFAULT_BLOCK_SIZE);
                dataAddrAlign = false;
            }
            else
            {
                if (blockLeft > card->host->maxBlockCount)
                {
                    blockLeft         = (blockLeft - card->host->maxBlockCount);
                    blockCountOneTime = card->host->maxBlockCount;
                }
                else
                {
                    blockCountOneTime = blockLeft;
                    blockLeft         = 0U;
                }
            }
            error = MMC_Write(card, dataAddrAlign ? nextBuffer : (uint8_t *)alignBuffer, (startBlock + blockDone),
                              FSL_SDMMC_DEFAULT_BLOCK_SIZE, blockCountOneTime);
            if (kStatus_Success != error)
            {
                error = kStatus_SDMMC_TransferFailed;
                break;
            }

            blockDone += blockCountOneTime;
            if (!card->noInteralAlign && (!dataAddrAlign))
            {
                (void)memset(alignBuffer, 0, FSL_SDMMC_DEFAULT_BLOCK_SIZE);
            }
        }
    }

    (void)SDMMC_OSAMutexUnlock(&card->lock);

    return error;
}

status_t MMC_EnableCacheControl(mmc_card_t *card, bool enable)
{
    assert(card != NULL);

    uint8_t cacheCtrl = 0;

    mmc_extended_csd_config_t extendedCsdconfig;

    /* check the target driver strength support or not */
    if (card->extendedCsd.cacheSize == 0U)
    {
        SDMMC_LOG("The cache is not supported by the mmc device\r\n");
        return kStatus_SDMMC_NotSupportYet;
    }

    if (enable)
    {
        cacheCtrl = MMC_CACHE_CONTROL_ENABLE;
    }

    /* Switch to high speed timing. */
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexCacheControl;
    extendedCsdconfig.ByteValue  = cacheCtrl;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        SDMMC_LOG("cache enabled failed\r\n");
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.cacheCtrl = cacheCtrl;

    return kStatus_Success;
}

status_t MMC_FlushCache(mmc_card_t *card)
{
    assert(card != NULL);

    mmc_extended_csd_config_t extendedCsdconfig;
    status_t error = kStatus_Success;

    /* check the target driver strength support or not */
    if ((card->extendedCsd.cacheSize == 0U) || (card->extendedCsd.cacheCtrl != MMC_CACHE_CONTROL_ENABLE))
    {
        SDMMC_LOG("The cache is not supported or not enabled, please check\r\n");
        error = kStatus_SDMMC_NotSupportYet;
    }
    else
    {
        /* Switch to high speed timing. */
        extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
        extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexFlushCache;
        extendedCsdconfig.ByteValue  = MMC_CACHE_TRIGGER_FLUSH;
        extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
        if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
        {
            SDMMC_LOG("cache flush failed\r\n");
            error = kStatus_SDMMC_ConfigureExtendedCsdFailed;
        }
    }

    return error;
}

status_t MMC_SetSleepAwake(mmc_card_t *card, mmc_sleep_awake_t state)
{
    assert(card != NULL);
    status_t error = kStatus_Success;

    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};

    if (card->extendedCsd.extendecCsdVersion <=
        (uint32_t)kMMC_ExtendedCsdRevision13) /* V4.3 or above version card support boot mode */
    {
        return kStatus_SDMMC_NotSupportYet;
    }

    error = MMC_PollingCardStatusBusy(card, false, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (kStatus_SDMMC_CardStatusIdle != error)
    {
        return kStatus_SDMMC_PollingCardIdleFailed;
    }

    /* deselect the card before enter into sleep state */
    if (state == kMMC_Sleep)
    {
        if (MMC_SelectCard(card, false) != kStatus_Success)
        {
            return kStatus_SDMMC_DeselectCardFailed;
        }
    }

    command.index        = (uint32_t)kMMC_SleepAwake;
    command.argument     = ((uint32_t)state << 15U) | (card->relativeAddress << 16U);
    command.responseType = kCARD_ResponseTypeR1b;

    content.command = &command;
    content.data    = NULL;

    error = MMC_Transfer(card, &content, 0U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Sleep awake timeout value 100ns * 2^sleepAwakeTimeout */
    error = MMC_PollingCardStatusBusy(card, false, (1UL << card->extendedCsd.sleepAwakeTimeout) / 10000U);
    if (kStatus_SDMMC_CardStatusIdle != error)
    {
        return kStatus_SDMMC_PollingCardIdleFailed;
    }

    /* select the card after wake up */
    if (state == kMMC_Awake)
    {
        if (MMC_SelectCard(card, true) != kStatus_Success)
        {
            return kStatus_SDMMC_SelectCardFailed;
        }
    }

    return kStatus_Success;
}

static status_t MMC_Erase(mmc_card_t *card, uint32_t startGroupAddress, uint32_t endGroupAddress)
{
    sdmmchost_cmd_t command      = {0};
    sdmmchost_transfer_t content = {0};
    status_t error               = kStatus_Success;

    /* Set the start erase group address */
    command.index              = (uint32_t)kMMC_EraseGroupStart;
    command.argument           = startGroupAddress;
    command.responseType       = kCARD_ResponseTypeR1;
    command.responseErrorFlags = SDMMC_R1_ALL_ERROR_FLAG;

    content.command = &command;
    content.data    = NULL;
    error           = MMC_Transfer(card, &content, 0U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Set the end erase group address */
    command.index    = (uint32_t)kMMC_EraseGroupEnd;
    command.argument = endGroupAddress;

    content.command = &command;
    content.data    = NULL;
    error           = MMC_Transfer(card, &content, 0U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Start the erase process */
    command.index              = (uint32_t)kSDMMC_Erase;
    command.argument           = 0U;
    command.responseType       = kCARD_ResponseTypeR1b;
    command.responseErrorFlags = SDMMC_R1_ALL_ERROR_FLAG;

    content.command = &command;
    content.data    = NULL;
    error           = MMC_Transfer(card, &content, 0U);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t MMC_EraseGroups(mmc_card_t *card, uint32_t startGroup, uint32_t endGroup)
{
    assert(card != NULL);

    uint32_t startGroupAddress;
    uint32_t endGroupAddress;
    status_t error        = kStatus_Success;
    uint32_t eraseTimeout = MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT;

    (void)SDMMC_OSAMutexLock(&card->lock, osaWaitForever_c);

    error = MMC_CheckEraseGroupRange(card, startGroup, endGroup);
    if (kStatus_Success != error)
    {
        error = kStatus_InvalidArgument;
    }
    else
    {
        error = MMC_PollingCardStatusBusy(card, true, 0U);
        if (error != kStatus_SDMMC_CardStatusIdle)
        {
            error = kStatus_SDMMC_PollingCardIdleFailed;
        }
    }

    if (error == kStatus_SDMMC_CardStatusIdle)
    {
        /* Calculate the start group address and end group address */
        startGroupAddress = startGroup;
        endGroupAddress   = endGroup;
        if ((card->flags & (uint32_t)kMMC_SupportHighCapacityFlag) != 0U)
        {
            /* The implementation of a higher than 2GB of density of memory will not be backwards compatible with the
            lower densities.First of all the address argument for higher than 2GB of density of memory is changed to
            be sector address (512B sectors) instead of byte address */
            startGroupAddress = (startGroupAddress * (card->eraseGroupBlocks));
            endGroupAddress   = (endGroupAddress * (card->eraseGroupBlocks));
        }
        else
        {
            /* The address unit is byte when card capacity is lower than 2GB */
            startGroupAddress = (startGroupAddress * (card->eraseGroupBlocks) * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
            endGroupAddress   = (endGroupAddress * (card->eraseGroupBlocks) * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
        }

        error = MMC_Erase(card, startGroupAddress, endGroupAddress);
        if (error == kStatus_Success)
        {
            if ((0U != (card->flags & (uint32_t)kMMC_SupportHighCapacityFlag)) &&
                (card->extendedCsd.highCapacityEraseTimeout != 0U))
            {
                eraseTimeout =
                    (uint32_t)card->extendedCsd.highCapacityEraseTimeout * 300U * (endGroup - startGroup + 1U);
            }

            error = MMC_PollingCardStatusBusy(card, true, eraseTimeout);
            if (kStatus_SDMMC_CardStatusIdle != error)
            {
                error = kStatus_SDMMC_PollingCardIdleFailed;
            }
            else
            {
                error = kStatus_Success;
            }
        }
    }

    (void)SDMMC_OSAMutexUnlock(&card->lock);

    return error;
}

status_t MMC_SetBootConfigWP(mmc_card_t *card, uint8_t wp)
{
    assert(card != NULL);

    mmc_extended_csd_config_t extendedCsdconfig;
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexBootConfigWP;
    extendedCsdconfig.ByteValue  = wp;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.bootConfigProtect = wp;

    return kStatus_Success;
}

status_t MMC_SetBootPartitionWP(mmc_card_t *card, mmc_boot_partition_wp_t bootPartitionWP)
{
    assert(card != NULL);

    mmc_extended_csd_config_t extendedCsdconfig;
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexBootPartitionWP;
    extendedCsdconfig.ByteValue  = (uint8_t)bootPartitionWP;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.bootPartitionWP = (uint8_t)bootPartitionWP;

    return kStatus_Success;
}

status_t MMC_SetBootConfig(mmc_card_t *card, const mmc_boot_config_t *config)
{
    assert(card != NULL);
    assert(config != NULL);

    uint8_t bootParameter;
    uint8_t bootBusWidth = (uint8_t)config->bootDataBusWidth;
    mmc_extended_csd_config_t extendedCsdconfig;

    if (card->extendedCsd.extendecCsdVersion <=
        (uint32_t)kMMC_ExtendedCsdRevision13) /* V4.3 or above version card support boot mode */
    {
        return kStatus_SDMMC_NotSupportYet;
    }

    /* Set the BOOT_CONFIG field of Extended CSD */
    bootParameter = card->extendedCsd.partitionConfig;
    bootParameter &=
        ~((uint8_t)MMC_PARTITION_CONFIG_BOOT_ACK_MASK | (uint8_t)MMC_PARTITION_CONFIG_PARTITION_ENABLE_MASK);
    bootParameter |= ((config->enableBootAck ? 1U : 0U) << MMC_PARTITION_CONFIG_BOOT_ACK_SHIFT);
    bootParameter |= ((uint8_t)(config->bootPartition) << MMC_PARTITION_CONFIG_PARTITION_ENABLE_SHIFT);

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexPartitionConfig;
    extendedCsdconfig.ByteValue  = bootParameter;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.partitionConfig = bootParameter;

    /* data bus remapping */
    if (bootBusWidth == (uint8_t)kMMC_DataBusWidth1bit)
    {
        bootBusWidth = 0U;
    }
    else if ((bootBusWidth == (uint8_t)kMMC_DataBusWidth4bit) || (bootBusWidth == (uint8_t)kMMC_DataBusWidth4bitDDR))
    {
        bootBusWidth = 1U;
    }
    else
    {
        bootBusWidth = 2U;
    }

    /*Set BOOT_BUS_CONDITIONS in Extended CSD */
    bootParameter = card->extendedCsd.bootDataBusConditions;
    bootParameter &= (uint8_t) ~(MMC_BOOT_BUS_CONDITION_RESET_BUS_CONDITION_MASK |
                                 MMC_BOOT_BUS_CONDITION_BUS_WIDTH_MASK | MMC_BOOT_BUS_CONDITION_BOOT_MODE_MASK);
    bootParameter |=
        (uint8_t)((config->retainBootbusCondition ? 1U : 0U) << MMC_BOOT_BUS_CONDITION_RESET_BUS_CONDITION_SHIFT);
    bootParameter |= bootBusWidth << MMC_BOOT_BUS_CONDITION_BUS_WIDTH_SHIFT;
    bootParameter |= ((uint8_t)(config->bootTimingMode) << MMC_BOOT_BUS_CONDITION_BOOT_MODE_SHIFT) &
                     MMC_BOOT_BUS_CONDITION_BOOT_MODE_MASK;

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)kMMC_ExtendedCsdIndexBootBusConditions;
    extendedCsdconfig.ByteValue  = bootParameter;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig, 0U))
    {
        return kStatus_SDMMC_ConfigureBootFailed;
    }

    card->extendedCsd.bootDataBusConditions = bootParameter;
    /* check and configure the boot config write protect */
    bootParameter = (uint8_t)config->pwrBootConfigProtection | (((uint8_t)config->premBootConfigProtection) << 4U);
    if (bootParameter != (card->extendedCsd.bootConfigProtect))
    {
        if (kStatus_Success != MMC_SetBootConfigWP(card, bootParameter))
        {
            return kStatus_SDMMC_ConfigureBootFailed;
        }
    }
    /* check and configure the boot partition write protect */
    if (card->extendedCsd.bootPartitionWP != (uint8_t)(config->bootPartitionWP))
    {
        if (kStatus_Success != MMC_SetBootPartitionWP(card, config->bootPartitionWP))
        {
            return kStatus_SDMMC_ConfigureBootFailed;
        }
    }

    return kStatus_Success;
}

status_t MMC_StartBoot(mmc_card_t *card,
                       const mmc_boot_config_t *mmcConfig,
                       uint8_t *buffer,
                       sdmmchost_boot_config_t *hostConfig)
{
    assert(card != NULL);
    assert(mmcConfig != NULL);
    assert(buffer != NULL);

    sdmmchost_cmd_t command = {0};
    uint32_t tempClock      = 0U;

    if (!card->isHostReady)
    {
        return kStatus_Fail;
    }

    /* send card active */
    SDMMCHOST_SendCardActive(card->host);
    /* enable MMC boot */
    SDMMCHOST_EnableBoot(card->host, true);

    if (mmcConfig->bootTimingMode == kMMC_BootModeSDRWithDefaultTiming)
    {
        /* Set clock to 400KHz. */
        tempClock = SDMMC_CLOCK_400KHZ;
    }
    else
    {
        /* Set clock to 52MHZ. */
        tempClock = MMC_CLOCK_52MHZ;
    }
    (void)SDMMCHOST_SetCardClock(card->host, tempClock);

    if (((card->host->capability & (uint32_t)kSDMMCHOST_SupportDDRMode) != 0U) &&
        (mmcConfig->bootTimingMode == kMMC_BootModeDDRTiming))
    {
        /* enable DDR mode */
        SDMMCHOST_EnableDDRMode(card->host, true, 0U);
    }

    /* data bus remapping */
    if (mmcConfig->bootDataBusWidth == kMMC_DataBusWidth1bit)
    {
        SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith1Bit);
    }
    else if ((mmcConfig->bootDataBusWidth == kMMC_DataBusWidth4bit) ||
             (mmcConfig->bootDataBusWidth == kMMC_DataBusWidth4bitDDR))
    {
        SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith4Bit);
    }
    else
    {
        SDMMCHOST_SetCardBusWidth(card->host, kSDMMC_BusWdith8Bit);
    }

    if (kMMC_BootModeAlternative == mmcConfig->bootMode)
    {
        /* alternative boot mode */
        command.argument = 0xFFFFFFFAU;
    }

    command.index = (uint32_t)kSDMMC_GoIdleState;

    /* should check tuning error during every transfer*/
    if (kStatus_Success != SDMMCHOST_StartBoot(card->host, hostConfig, &command, buffer))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t MMC_ReadBootData(mmc_card_t *card, uint8_t *buffer, sdmmchost_boot_config_t *hostConfig)
{
    assert(card != NULL);
    assert(buffer != NULL);

    /* should check tuning error during every transfer*/
    if (kStatus_Success != SDMMCHOST_ReadBootData(card->host, hostConfig, buffer))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t MMC_StopBoot(mmc_card_t *card, uint32_t bootMode)
{
    assert(card != NULL);
    /* Disable boot mode */
    if ((uint32_t)kMMC_BootModeAlternative == bootMode)
    {
        /* Send CMD0 to reset the bus */
        if (kStatus_Success != MMC_GoIdle(card))
        {
            return kStatus_SDMMC_GoIdleFailed;
        }
    }
    /* disable MMC boot */
    SDMMCHOST_EnableBoot(card->host, false);

    return kStatus_Success;
}
