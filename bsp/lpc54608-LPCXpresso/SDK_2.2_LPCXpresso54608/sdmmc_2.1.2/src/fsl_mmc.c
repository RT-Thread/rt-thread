/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include "fsl_card.h"
#include "fsl_sdmmc.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/
/*! @brief The divide value used to avoid float point calculation when calculate max speed in normal mode. */
#define DIVIDER_IN_TRANSFER_SPEED (10U)

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
static status_t inline MMC_SelectCard(mmc_card_t *card, bool isSelected);

/*!
 * @brief Wait write process complete.
 *
 * @param card Card descriptor.
 * @retval kStatus_Timeout Operation timeout.
 * @retval kStatus_Success Operate successfully.
 */
static status_t inline MMC_WaitWriteComplete(mmc_card_t *card);

/*!
 * @brief Send SET_BLOCK_COUNT command.
 *
 * @param card Card descriptor.
 * @param blockCount Block count.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t inline MMC_SetBlockCount(mmc_card_t *card, uint32_t blockCount);

/*!
 * @brief Send GO_IDLE command to reset all cards to idle state
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t inline MMC_GoIdle(mmc_card_t *card);

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
static status_t inline MMC_SetBlockSize(mmc_card_t *card, uint32_t blockSize);

/*!
 * @brief switch voltage.
 *
 * @param card Card descriptor.
 * @param opcode use to send operation condition
 * @retval kStatus_SDMMC_HostNotSupport Host doesn't support the voltage window to access the card.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SwitchVoltage(mmc_card_t *card, uint32_t *opCode);

/*!
 * @brief Send SEND_OPERATION_CONDITION command to validate if the card support host's voltage window
 *
 * @param card Card descriptor.
 * @param cmd argument
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
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Wait write complete failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SetExtendedCsdConfig(mmc_card_t *card, const mmc_extended_csd_config_t *config);

/*!
 * @brief Decode the Extended CSD register
 *
 * @param card Card descriptor.
 * @param rawExtendedCsd Raw extended CSD register content.
 */
static void MMC_DecodeExtendedCsd(mmc_card_t *card, uint32_t *rawExtendedCsd);

/*!
 * @brief Send SEND_EXTENDED_CSD command to get the content of the Extended CSD register
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t MMC_SendExtendedCsd(mmc_card_t *card);

/*!
 * @brief Set the power class of the card at specific bus width and host intended voltage window.
 *
 * @param card Card descriptor.
 * @param width Data bus width.
 * @return The power class value.
 */
static status_t MMC_SetPowerClass(mmc_card_t *card, mmc_data_bus_width_t width);

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
 * @retval kStatus_SDMMC_SetDataBusWidthFailed switch fail
 * @retval kStatus_Success switch success
 */
static status_t MMC_SetMaxDataBusWidth(mmc_card_t *card);

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
 * @brief select card driver strength
 *
 * @param card Card descriptor.
 * @retval kStatus_Success switch success
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed , config extend csd register fail
 */
static status_t MMC_SelectCardDriverStrength(mmc_card_t *card, uint8_t driverStrength);
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
 */
static status_t inline MMC_ExecuteTuning(mmc_card_t *card);

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
 * @brief card transfer function wrapper
 * This function is used to do tuning before transfer if the cmd won't casue re-tuning
 * request, then you can call host transfer function directly
 * @param base HOST peripheral base address.
 * @param transfer function pointer
 * @param transfer content
 * @param retry times
 * @retval kStatus_SDMMC_TransferFailed transfer fail
 * @retval kStatus_SDMMC_TuningFail tuning fail
 * @retval kStatus_Success transfer success
 */
static status_t MMC_Transfer(mmc_card_t *card, HOST_TRANSFER *content, uint32_t retry);

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
static status_t inline MMC_SelectCard(mmc_card_t *card, bool isSelected)
{
    assert(card);

    return SDMMC_SelectCard(card->host.base, card->host.transfer, card->relativeAddress, isSelected);
}

static status_t inline MMC_SetBlockCount(mmc_card_t *card, uint32_t blockCount)
{
    assert(card);

    return SDMMC_SetBlockCount(card->host.base, card->host.transfer, blockCount);
}

static status_t inline MMC_GoIdle(mmc_card_t *card)
{
    assert(card);

    return SDMMC_GoIdle(card->host.base, card->host.transfer);
}

static status_t inline MMC_SetBlockSize(mmc_card_t *card, uint32_t blockSize)
{
    assert(card);

    return SDMMC_SetBlockSize(card->host.base, card->host.transfer, blockSize);
}

static status_t MMC_ExecuteTuning(mmc_card_t *card)
{
    assert(card);

    uint32_t blockSize = 0U;

    if (card->flags & kMMC_DataBusWidth4BitFlag)
    {
        blockSize = 64U;
    }
    else if (card->flags & kMMC_DataBusWidth8BitFlag)
    {
        blockSize = 128U;
    }
    else
    {
        /* do not need tuning in this situation */
        return kStatus_Success;
    }

    return SDMMC_ExecuteTuning(card->host.base, kMMC_SendTuningBlock, blockSize);
}

static status_t MMC_Transfer(mmc_card_t *card, HOST_TRANSFER *content, uint32_t retry)
{
    assert(card->host.transfer);
    assert(content);
    status_t error;

    do
    {
        error = card->host.transfer(card->host.base, content);
        if ((error == HOST_RETUNING_REQUEST) &&
            ((card->currentTiming == kMMC_HighSpeed200Timing) || (card->currentTiming == kMMC_HighSpeed400Timing)))
        {
            /* execute re-tuning */
            if (MMC_ExecuteTuning(card) != kStatus_Success)
            {
                error = kStatus_SDMMC_TuningFail;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (error != kStatus_Success)
        {
            error = kStatus_SDMMC_TransferFailed;
        }
        else
        {
        }

        if (retry != 0U)
        {
            retry--;
        }
        else
        {
            break;
        }

    } while ((error != kStatus_Success) && (error != kStatus_SDMMC_TuningFail));

    return error;
}

static status_t inline MMC_WaitWriteComplete(mmc_card_t *card)
{
    assert(card);

    HOST_TRANSFER content = {0};
    HOST_COMMAND command = {0};

    command.index = kSDMMC_SendStatus;
    command.argument = card->relativeAddress << 16U;
    command.responseType = kCARD_ResponseTypeR1;
    command.responseErrorFlags = kSDMMC_R1ErrorAllFlag;

    do
    {
        content.command = &command;
        content.data = 0U;
        if (kStatus_Success != MMC_Transfer(card, &content, 1U))
        {
            return kStatus_SDMMC_TransferFailed;
        }

        if ((command.response[0U] & kSDMMC_R1ReadyForDataFlag) &&
            (SDMMC_R1_CURRENT_STATE(command.response[0U]) != kSDMMC_R1StateProgram))
        {
            break;
        }
    } while (true);

    return kStatus_Success;
}

static status_t MMC_StopTransmission(mmc_card_t *card)
{
    assert(card);

    HOST_TRANSFER content = {0};
    HOST_COMMAND command = {0};

    command.index = kSDMMC_StopTransmission;
    command.argument = 0U;
    command.type = kCARD_CommandTypeAbort;
    command.responseType = kCARD_ResponseTypeR1b;
    command.responseErrorFlags = kSDMMC_R1ErrorAllFlag;

    content.command = &command;
    content.data = 0U;
    if (kStatus_Success != MMC_Transfer(card, &content, 2U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

static status_t MMC_SwitchVoltage(mmc_card_t *card, uint32_t *opCode)
{
    mmc_voltage_window_t tempVoltage;
    /* Get host's voltage window. */
    if (((card->host.capability.flags & kHOST_SupportV330) || (card->host.capability.flags & kHOST_SupportV300)) &&
        (card->ocr & MMC_OCR_V270TO360_MASK) && ((card->hostVoltageWindow == kMMC_VoltageWindowNone) ||
                                                 (card->hostVoltageWindow == kMMC_VoltageWindows270to360)))
    {
        /* Save host intended voltage range */
        tempVoltage = kMMC_VoltageWindows270to360;
        /* set the opcode */
        *opCode = MMC_OCR_V270TO360_MASK;
        /*do not need switch voltage here*/
        HOST_SWITCH_VOLTAGE180V(card->host.base, false);
    }

    if ((card->host.capability.flags & kHOST_SupportV180) && (card->ocr & MMC_OCR_V170TO195_MASK) &&
        ((card->hostVoltageWindow == kMMC_VoltageWindowNone) ||
         (card->hostVoltageWindow == kMMC_VoltageWindow170to195)))
    {
        /* Save host intended voltage range */
        tempVoltage = kMMC_VoltageWindow170to195;
        /* set the opcode */
        *opCode = MMC_OCR_V170TO195_MASK;
        /*switch voltage to 1.8V here*/
        HOST_SWITCH_VOLTAGE180V(card->host.base, true);
    }

    card->hostVoltageWindow = tempVoltage;
    /* reserve 1.2V voltage case */

    return kStatus_Success;
}

static status_t MMC_SendOperationCondition(mmc_card_t *card, uint32_t arg)
{
    assert(card);
    assert(card->host.transfer);

    HOST_COMMAND command = {0};
    HOST_TRANSFER content = {0};
    status_t error;
    uint32_t i = FSL_SDMMC_MAX_VOLTAGE_RETRIES;

    /* Send CMD1 with the intended voltage range in the argument(either 0x00FF8000 or 0x00000080) */
    command.index = kMMC_SendOperationCondition;
    command.argument = arg;
    command.responseType = kCARD_ResponseTypeR3;

    content.command = &command;
    content.data = NULL;
    do
    {
        if (kStatus_Success != card->host.transfer(card->host.base, &content))
        {
            return kStatus_SDMMC_TransferFailed;
        }

        if (arg == 0U)
        {
            error = kStatus_Success;
            card->ocr = command.response[0U];
        }
        /* Repeat CMD1 until the busy bit is cleared. */
        else if (!(command.response[0U] & MMC_OCR_BUSY_MASK))
        {
            error = kStatus_Timeout;
        }
        else
        {
            error = kStatus_Success;
        }
    } while ((i--) && (error != kStatus_Success));

    return error;
}

static status_t MMC_SetRelativeAddress(mmc_card_t *card)
{
    assert(card);
    assert(card->host.transfer);

    HOST_COMMAND command = {0};
    HOST_TRANSFER content = {0};

    /* Send CMD3 with a chosen relative address, with value greater than 1 */
    command.index = kMMC_SetRelativeAddress;
    command.argument = (MMC_DEFAULT_RELATIVE_ADDRESS << 16U);
    command.responseType = kCARD_ResponseTypeR1;

    content.command = &command;
    content.data = NULL;
    if ((kStatus_Success == card->host.transfer(card->host.base, &content)) ||
        (!((command.response[0U]) & kSDMMC_R1ErrorAllFlag)))
    {
        card->relativeAddress = MMC_DEFAULT_RELATIVE_ADDRESS;
        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static void MMC_DecodeCsd(mmc_card_t *card, uint32_t *rawCsd)
{
    assert(card);
    assert(rawCsd);

    mmc_csd_t *csd;
    uint32_t multiplier;

    csd = &(card->csd);
    csd->csdStructureVersion = (uint8_t)((rawCsd[3U] & 0xC0000000U) >> 30U);
    csd->systemSpecificationVersion = (uint8_t)((rawCsd[3U] & 0x3C000000U) >> 26U);
    csd->dataReadAccessTime1 = (uint8_t)((rawCsd[3U] & 0xFF0000U) >> 16U);
    csd->dataReadAccessTime2 = (uint8_t)((rawCsd[3U] & 0xFF00U) >> 8U);
    csd->transferSpeed = (uint8_t)(rawCsd[3U] & 0xFFU);
    csd->cardCommandClass = (uint16_t)((rawCsd[2U] & 0xFFF00000U) >> 20U);
    /* Max block length read/write one time */
    csd->readBlockLength = (uint8_t)((rawCsd[2U] & 0xF0000U) >> 16U);
    if (rawCsd[2U] & 0x8000U)
    {
        csd->flags |= kMMC_CsdReadBlockPartialFlag;
    }
    if (rawCsd[2U] & 0x4000U)
    {
        csd->flags |= kMMC_CsdWriteBlockMisalignFlag;
    }
    if (rawCsd[2U] & 0x2000U)
    {
        csd->flags |= kMMC_CsdReadBlockMisalignFlag;
    }
    if (rawCsd[2U] & 0x1000U)
    {
        csd->flags |= kMMC_CsdDsrImplementedFlag;
    }
    csd->deviceSize = (uint16_t)(((rawCsd[2U] & 0x3FFU) << 2U) + ((rawCsd[1U] & 0xC0000000U) >> 30U));
    csd->readCurrentVddMin = (uint8_t)((rawCsd[1U] & 0x38000000U) >> 27U);
    csd->readCurrentVddMax = (uint8_t)((rawCsd[1U] & 0x07000000U) >> 24U);
    csd->writeCurrentVddMin = (uint8_t)((rawCsd[1U] & 0x00E00000U) >> 21U);
    csd->writeCurrentVddMax = (uint8_t)((rawCsd[1U] & 0x001C0000U) >> 18U);
    csd->deviceSizeMultiplier = (uint8_t)((rawCsd[1U] & 0x00038000U) >> 15U);
    csd->eraseGroupSize = (uint8_t)((rawCsd[1U] & 0x00007C00U) >> 10U);
    csd->eraseGroupSizeMultiplier = (uint8_t)((rawCsd[1U] & 0x000003E0U) >> 5U);
    csd->writeProtectGroupSize = (uint8_t)(rawCsd[1U] & 0x0000001FU);
    if (rawCsd[0U] & 0x80000000U)
    {
        csd->flags |= kMMC_CsdWriteProtectGroupEnabledFlag;
    }
    csd->defaultEcc = (uint8_t)((rawCsd[0U] & 0x60000000U) >> 29U);
    csd->writeSpeedFactor = (uint8_t)((rawCsd[0U] & 0x1C000000U) >> 26U);
    csd->maxWriteBlockLength = (uint8_t)((rawCsd[0U] & 0x03C00000U) >> 22U);
    if (rawCsd[0U] & 0x00200000U)
    {
        csd->flags |= kMMC_CsdWriteBlockPartialFlag;
    }
    if (rawCsd[0U] & 0x00010000U)
    {
        csd->flags |= kMMC_ContentProtectApplicationFlag;
    }
    if (rawCsd[0U] & 0x00008000U)
    {
        csd->flags |= kMMC_CsdFileFormatGroupFlag;
    }
    if (rawCsd[0U] & 0x00004000U)
    {
        csd->flags |= kMMC_CsdCopyFlag;
    }
    if (rawCsd[0U] & 0x00002000U)
    {
        csd->flags |= kMMC_CsdPermanentWriteProtectFlag;
    }
    if (rawCsd[0U] & 0x00001000U)
    {
        csd->flags |= kMMC_CsdTemporaryWriteProtectFlag;
    }
    csd->fileFormat = (uint8_t)((rawCsd[0U] & 0x00000C00U) >> 10U);
    csd->eccCode = (uint8_t)((rawCsd[0U] & 0x00000300U) >> 8U);

    /* Calculate the device total block count. */
    /* For the card capacity of witch higher than 2GB, the maximum possible value should be set to this register
    is 0xFFF. */
    if (card->csd.deviceSize != 0xFFFU)
    {
        multiplier = (2U << (card->csd.deviceSizeMultiplier + 2U - 1U));
        card->userPartitionBlocks = (((card->csd.deviceSize + 1U) * multiplier) / FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    }
    else
    {
        card->flags |= kMMC_SupportHighCapacityFlag;
    }
    card->blockSize = FSL_SDMMC_DEFAULT_BLOCK_SIZE;
}

static void MMC_SetMaxFrequency(mmc_card_t *card)
{
    assert(card);

    uint32_t frequencyUnit;
    uint32_t multiplierFactor;
    uint32_t maxBusClock_Hz;

    /* g_fsdhcCommandUnitInTranSpeed and g_transerSpeedMultiplierFactor are used to calculate the max speed in normal
    mode not high speed mode.
    For cards supporting version 4.0, 4.1, and 4.2 of the specification, the value shall be 20MHz(0x2A).
    For cards supporting version 4.3, the value shall be 26 MHz (0x32H). In High speed mode, the max
    frequency is decided by CARD_TYPE in Extended CSD. */
    frequencyUnit = g_transerSpeedFrequencyUnit[READ_MMC_TRANSFER_SPEED_FREQUENCY_UNIT(card->csd)];
    multiplierFactor = g_transerSpeedMultiplierFactor[READ_MMC_TRANSFER_SPEED_MULTIPLIER(card->csd)];
    maxBusClock_Hz = (frequencyUnit * multiplierFactor) / DIVIDER_IN_TRANSFER_SPEED;
    card->busClock_Hz = HOST_SET_CARD_CLOCK(card->host.base, card->host.sourceClock_Hz, maxBusClock_Hz);
}

static status_t MMC_SetMaxEraseUnitSize(mmc_card_t *card)
{
    assert(card);

    uint32_t erase_group_size;
    uint32_t erase_group_multiplier;
    mmc_extended_csd_config_t extendedCsdconfig;

    if (((!(card->flags & kMMC_SupportHighCapacityFlag)) || (card->extendedCsd.highCapacityEraseUnitSize == 0)) ||
        (card->extendedCsd.highCapacityEraseTimeout == 0))
    {
        erase_group_size = card->csd.eraseGroupSize;
        erase_group_multiplier = card->csd.eraseGroupSizeMultiplier;
        card->eraseGroupBlocks = ((erase_group_size + 1U) * (erase_group_multiplier + 1U));
    }
    else
    {
        /* Erase Unit Size = 512Kbyte * HC_ERASE_GRP_SIZE. Block size is 512 bytes. */
        card->eraseGroupBlocks = (card->extendedCsd.highCapacityEraseUnitSize * 1024U);
        /* Enable high capacity erase unit size. */
        extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeSetBits;
        extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexEraseGroupDefinition;
        extendedCsdconfig.ByteValue = 0x01U; /* The high capacity erase unit size enable bit is bit 0 */
        extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
        if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
        {
            return kStatus_SDMMC_ConfigureExtendedCsdFailed;
        }
    }

    return kStatus_Success;
}

static status_t MMC_SetExtendedCsdConfig(mmc_card_t *card, const mmc_extended_csd_config_t *config)
{
    assert(card);
    assert(card->host.transfer);
    assert(config);

    uint32_t parameter = 0U;
    HOST_COMMAND command = {0};
    HOST_TRANSFER content = {0};

    parameter |= ((uint32_t)(config->commandSet) << MMC_SWITCH_COMMAND_SET_SHIFT);
    parameter |= ((uint32_t)(config->ByteValue) << MMC_SWITCH_VALUE_SHIFT);
    parameter |= ((uint32_t)(config->ByteIndex) << MMC_SWITCH_BYTE_INDEX_SHIFT);
    parameter |= ((uint32_t)(config->accessMode) << MMC_SWITCH_ACCESS_MODE_SHIFT);

    command.index = kMMC_Switch;
    command.argument = parameter;
    command.responseType = kCARD_ResponseTypeR1b; /* Send switch command to set the pointed byte in Extended CSD. */

    content.command = &command;
    content.data = NULL;
    if (kStatus_Success != MMC_Transfer(card, &content, 2U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Wait for the card write process complete because of that card read process and write process use one buffer. */
    if (kStatus_Success != MMC_WaitWriteComplete(card))
    {
        return kStatus_SDMMC_WaitWriteCompleteFailed;
    }

    return kStatus_Success;
}

static void MMC_DecodeExtendedCsd(mmc_card_t *card, uint32_t *rawExtendedCsd)
{
    assert(card);
    assert(rawExtendedCsd);

    uint8_t *buffer = (uint8_t *)rawExtendedCsd;
    mmc_extended_csd_t *extendedCsd = &(card->extendedCsd);

    /* Extended CSD is transferred as a data block from least byte indexed 0. */
    extendedCsd->highDensityEraseGroupDefinition = buffer[175U];
    extendedCsd->bootDataBusWidth = buffer[177U];
    extendedCsd->partitionConfig = buffer[179U];
    extendedCsd->eraseMemoryContent = buffer[181U];
    extendedCsd->dataBusWidth = buffer[183U];
    extendedCsd->highSpeedTiming = buffer[185U];
    extendedCsd->powerClass = buffer[187U];
    extendedCsd->commandSetRevision = buffer[189U];
    extendedCsd->commandSet = buffer[191U];
    extendedCsd->extendecCsdVersion = buffer[192U];
    extendedCsd->csdStructureVersion = buffer[194U];

    extendedCsd->cardType = buffer[196U];
    /* This field define the type of the card. The only currently valid values for this field are 0x01 and 0x03. */
    card->flags |= extendedCsd->cardType;

    extendedCsd->ioDriverStrength = buffer[197U];

    extendedCsd->powerClass52MHz195V = buffer[200U];
    extendedCsd->powerClass26MHz195V = buffer[201U];
    extendedCsd->powerClass52MHz360V = buffer[202U];
    extendedCsd->powerClass26MHz360V = buffer[203U];
    extendedCsd->powerClass200MHZVCCQ130VVCC360V = buffer[236U];
    extendedCsd->powerClass200MHZVCCQ195VVCC360V = buffer[237U];
    extendedCsd->powerClass52MHZDDR195V = buffer[238U];
    extendedCsd->powerClass52MHZDDR360V = buffer[239U];
    extendedCsd->powerClass200MHZDDR360V = buffer[253U];
    extendedCsd->minimumReadPerformance4Bit26MHz = buffer[205U];
    extendedCsd->minimumWritePerformance4Bit26MHz = buffer[206U];
    extendedCsd->minimumReadPerformance8Bit26MHz4Bit52MHz = buffer[207U];
    extendedCsd->minimumWritePerformance8Bit26MHz4Bit52MHz = buffer[208U];
    extendedCsd->minimumReadPerformance8Bit52MHz = buffer[209U];
    extendedCsd->minimumWritePerformance8Bit52MHz = buffer[210U];
    extendedCsd->minReadPerformance8bitAt52MHZDDR = buffer[234U];
    extendedCsd->minWritePerformance8bitAt52MHZDDR = buffer[235U];
    /* Get user partition size. */
    extendedCsd->sectorCount = ((((uint32_t)buffer[215U]) << 24U) + (((uint32_t)buffer[214U]) << 16U) +
                                (((uint32_t)buffer[213U]) << 8U) + (uint32_t)buffer[212U]);
    if (card->flags & kMMC_SupportHighCapacityFlag)
    {
        card->userPartitionBlocks = card->extendedCsd.sectorCount;
    }

    extendedCsd->sleepAwakeTimeout = buffer[217U];
    extendedCsd->sleepCurrentVCCQ = buffer[219U];
    extendedCsd->sleepCurrentVCC = buffer[220U];
    extendedCsd->highCapacityWriteProtectGroupSize = buffer[221U];
    extendedCsd->reliableWriteSectorCount = buffer[222U];
    extendedCsd->highCapacityEraseTimeout = buffer[223U];
    extendedCsd->highCapacityEraseUnitSize = buffer[224U];
    extendedCsd->accessSize = buffer[225U];

    /* Get boot partition size. */
    extendedCsd->bootSizeMultiplier = buffer[226U];
    card->bootPartitionBlocks = ((128U * 1024U * extendedCsd->bootSizeMultiplier) / FSL_SDMMC_DEFAULT_BLOCK_SIZE);

    /* Check if card support alternate boot. */
    extendedCsd->bootInformation = buffer[228U];
    if (extendedCsd->bootInformation & kMMC_SupportAlternateBoot)
    {
        card->flags |= kMMC_SupportAlternateBootFlag;
    }
    else if (extendedCsd->bootInformation & kMMC_SupportDDRBootFlag)
    {
        card->flags |= kMMC_SupportDDRBootFlag;
    }
    else if (extendedCsd->bootInformation & kMMC_SupportHighSpeedBoot)
    {
        card->flags |= kMMC_SupportHighSpeedBootFlag;
    }
    else
    {
    }
    /* cache size unit 1kb */
    extendedCsd->cacheSize = (((uint32_t)buffer[252U]) << 24) | (((uint32_t)buffer[251U]) << 16) |
                             (((uint32_t)buffer[250U]) << 8) | (((uint32_t)buffer[249U]));

    extendedCsd->supportedCommandSet = buffer[504U];
}

static status_t MMC_SendExtendedCsd(mmc_card_t *card)
{
    assert(card);
    assert(card->host.transfer);

    HOST_COMMAND command = {0};
    HOST_TRANSFER content = {0};
    HOST_DATA data = {0};
    uint32_t i;

    command.index = kMMC_SendExtendedCsd;
    command.argument = 0U;
    command.responseType = kCARD_ResponseTypeR1;

    data.blockCount = 1U;
    data.blockSize = MMC_EXTENDED_CSD_BYTES;
    data.rxData = card->rawExtendedCsd;

    content.command = &command;
    content.data = &data;
    if ((kStatus_Success == card->host.transfer(card->host.base, &content)) &&
        (!(command.response[0U] & kSDMMC_R1ErrorAllFlag)))
    {
        /* The response is from bit 127:8 in R2, corresponding to command.response[3][31:0] to
        command.response[0U][31:8] */
        for (i = 0U; i < MMC_EXTENDED_CSD_BYTES / 4U; i++)
        {
            switch (card->host.config.endianMode)
            {
                case kHOST_EndianModeLittle:
                    /* Doesn't need to switch byte sequence when decode bytes as little endian sequence. */
                    break;
                case kHOST_EndianModeBig:
                    /* In big endian mode, the SD bus byte transferred first is the byte stored in highest position
                    in a word which cause 4 byte's sequence in a word is not consistent with their original sequence
                    from card. */
                    card->rawExtendedCsd[i] = SWAP_WORD_BYTE_SEQUENCE(card->rawExtendedCsd[i]);
                    break;
                case kHOST_EndianModeHalfWordBig:
                    card->rawExtendedCsd[i] = SWAP_HALF_WROD_BYTE_SEQUENCE(card->rawExtendedCsd[i]);
                    break;
                default:
                    return kStatus_SDMMC_NotSupportYet;
            }
        }
        MMC_DecodeExtendedCsd(card, card->rawExtendedCsd);

        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static status_t MMC_SetPowerClass(mmc_card_t *card, mmc_data_bus_width_t width)
{
    assert(card);

    uint8_t mask = 0, shift = 0U;
    uint8_t powerClass = 0;
    mmc_extended_csd_config_t extendedCsdconfig;

    switch (width)
    {
        case kMMC_DataBusWidth4bit:
            mask = MMC_POWER_CLASS_4BIT_MASK; /* The mask of 4 bit bus width's power class */
            shift = 0U;
            break;
        case kMMC_DataBusWidth8bit:
            mask = MMC_POWER_CLASS_8BIT_MASK; /* The mask of 8 bit bus width's power class */
            shift = 4U;
            break;
        case kMMC_DataBusWidth1bit:
        default:
            break;
    }

    switch (card->hostVoltageWindow)
    {
        case kMMC_VoltageWindow170to195:

            if (card->currentTiming == kMMC_HighSpeed200Timing)
            {
                powerClass = ((card->extendedCsd.powerClass200MHZVCCQ195VVCC360V) & mask);
            }
            else if (card->currentTiming == kMMC_HighSpeed400Timing)
            {
                powerClass = ((card->extendedCsd.powerClass200MHZDDR360V) & mask);
            }
            else if (card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming)
            {
                powerClass = ((card->extendedCsd.powerClass52MHZDDR195V) & mask);
            }
            else if (card->currentTiming == kMMC_HighSpeed52MHZTiming)
            {
                powerClass = ((card->extendedCsd.powerClass52MHz195V) & mask);
            }
            else if (card->currentTiming == kMMC_HighSpeed26MHZTiming)
            {
                powerClass = ((card->extendedCsd.powerClass26MHz195V) & mask);
            }
            else
            {
            }
            break;
        case kMMC_VoltageWindows270to360:

            if (card->currentTiming == kMMC_HighSpeed26MHZTiming)
            {
                powerClass = ((card->extendedCsd.powerClass26MHz360V) & mask);
            }
            else if (card->currentTiming == kMMC_HighSpeed52MHZTiming)
            {
                powerClass = ((card->extendedCsd.powerClass52MHz360V) & mask);
            }
            else if (card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming)
            {
                powerClass = ((card->extendedCsd.powerClass52MHZDDR360V) & mask);
            }
            else
            {
            }

            break;
        default:
            powerClass = 0;
            break;
    }
    /* due to 8bit power class position [7:4] */
    powerClass >>= shift;

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexPowerClass;
    extendedCsdconfig.ByteValue = powerClass;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }
    /* restore power class */
    card->extendedCsd.powerClass = powerClass;

    return kStatus_Success;
}

static status_t MMC_SendTestPattern(mmc_card_t *card, uint32_t blockSize, uint32_t *pattern)
{
    assert(card);
    assert(card->host.transfer);
    assert(blockSize <= FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    assert(pattern);

    HOST_TRANSFER content = {0};
    HOST_COMMAND command = {0};
    HOST_DATA data = {0};

    command.index = kMMC_SendingBusTest;
    command.argument = 0U;
    command.responseType = kCARD_ResponseTypeR1;

    /* Ignore errors in bus test procedure to improve chances that the test will work. */
    data.enableIgnoreError = true;
    data.blockCount = 1U;
    data.blockSize = blockSize;
    data.txData = pattern;

    content.command = &command;
    content.data = &data;
    if ((kStatus_Success != card->host.transfer(card->host.base, &content)) ||
        (command.response[0U] & kSDMMC_R1ErrorAllFlag))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

static status_t MMC_ReceiveTestPattern(mmc_card_t *card, uint32_t blockSize, uint32_t *pattern)
{
    assert(card);
    assert(card->host.transfer);
    assert(blockSize <= FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    assert(pattern);

    HOST_TRANSFER content = {0};
    HOST_COMMAND command = {0};
    HOST_DATA data = {0};

    command.index = kMMC_BusTestRead;
    command.responseType = kCARD_ResponseTypeR1;

    /* Ignore errors in bus test procedure to improve chances that the test will work. */
    data.enableIgnoreError = true;
    data.blockCount = 1U;
    data.blockSize = blockSize;
    data.rxData = pattern;

    content.command = &command;
    content.data = &data;
    if ((kStatus_Success != card->host.transfer(card->host.base, &content)) ||
        ((command.response[0U]) & kSDMMC_R1ErrorAllFlag))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

static status_t MMC_TestDataBusWidth(mmc_card_t *card, mmc_data_bus_width_t width)
{
    assert(card);

    uint32_t blockSize;
    uint32_t sendPattern[2U] = {0};
    uint32_t receivedPattern[2U] = {0};
    uint32_t xorMask;
    uint32_t xorResult, tempResult = 0U;

    /* For 8 data lines the data block would be (MSB to LSB): 0x0000_0000_0000_AA55,
    For 4 data lines the data block would be (MSB to LSB): 0x0000_005A,
    For only 1 data line the data block would be: 0x80 */
    switch (width)
    {
        case kMMC_DataBusWidth8bit:
            blockSize = 8U;
            sendPattern[0U] = 0xAA55U;
            xorMask = 0xFFFFU;
            xorResult = 0xFFFFU;
            break;
        case kMMC_DataBusWidth4bit:
            blockSize = 4U;
            sendPattern[0U] = 0x5AU;
            xorMask = 0xFFU;
            xorResult = 0xFFU;
            break;
        default:
            blockSize = 4U;
            sendPattern[0U] = 0x80U;
            xorMask = 0xFFU;
            xorResult = 0xC0U;
            break;
    }
    switch (card->host.config.endianMode)
    {
        case kHOST_EndianModeLittle:
            /* Doesn't need to switch byte sequence when decodes bytes as little endian sequence. */
            break;
        case kHOST_EndianModeBig:
            /* In big endian mode, the byte transferred first is the byte stored in highest byte position in a word
            which will cause the card receive the inverted byte sequence in a word in bus test procedure. So the
            sequence of 4 bytes stored in a word should be converted. */
            sendPattern[0] = SWAP_WORD_BYTE_SEQUENCE(sendPattern[0]);
            xorMask = SWAP_WORD_BYTE_SEQUENCE(xorMask);
            xorResult = SWAP_WORD_BYTE_SEQUENCE(xorResult);
            break;
        case kHOST_EndianModeHalfWordBig:
            /* In half word big endian mode, the byte transferred first is the lower byte in the higher half word.
            0xAA55U should be converted to 0xAA550000U to set the 0x55 to be the first byte to transfer. */
            sendPattern[0] = SWAP_HALF_WROD_BYTE_SEQUENCE(sendPattern[0]);
            xorMask = SWAP_HALF_WROD_BYTE_SEQUENCE(xorMask);
            xorResult = SWAP_HALF_WROD_BYTE_SEQUENCE(xorResult);
            sendPattern[0] = SWAP_WORD_BYTE_SEQUENCE(sendPattern[0]);
            xorMask = SWAP_WORD_BYTE_SEQUENCE(xorMask);
            xorResult = SWAP_WORD_BYTE_SEQUENCE(xorResult);
            break;
        default:
            return kStatus_SDMMC_NotSupportYet;
    }

    if (kStatus_Success != MMC_SendTestPattern(card, blockSize, sendPattern))
    {
        return kStatus_SDMMC_SendTestPatternFailed;
    }
    if (kStatus_Success != MMC_ReceiveTestPattern(card, blockSize, receivedPattern))
    {
        return kStatus_SDMMC_ReceiveTestPatternFailed;
    }

    tempResult = (sendPattern[0U] ^ receivedPattern[0U]) & xorMask;
    /* XOR the send pattern and receive pattern */
    if (tempResult != xorResult)
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

static status_t MMC_SetDataBusWidth(mmc_card_t *card, mmc_data_bus_width_t width)
{
    assert(card);

    mmc_extended_csd_config_t extendedCsdconfig;

    /* Set power class corresponding to bus width. From the Extended CSD the host can learn the power class of the card
    and choose to work with a wider data bus. */
    if (kStatus_Success != MMC_SetPowerClass(card, width))
    {
        return kStatus_SDMMC_SetPowerClassFail;
    }

    if ((width == kMMC_DataBusWidth4bit) && ((card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming) ||
                                             (card->currentTiming == kMMC_HighSpeedDDR52120VTiming)))
    {
        width = kMMC_DataBusWidth4bitDDR;
    }

    if ((width == kMMC_DataBusWidth8bit) &&
        ((card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming) ||
         (card->currentTiming == kMMC_HighSpeedDDR52120VTiming) || (card->currentTiming == kMMC_HighSpeed400Timing)))
    {
        width = kMMC_DataBusWidth8bitDDR;
    }

    /* Set data bus width */
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexBusWidth;
    extendedCsdconfig.ByteValue = width;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }
    /* restore data bus width */
    card->extendedCsd.dataBusWidth = width;

    return kStatus_Success;
}

static status_t MMC_SetMaxDataBusWidth(mmc_card_t *card)
{
    assert(card);

    status_t error = kStatus_Fail;

    /* Test and set the data bus width for card. */
    if (card->host.capability.flags & kHOST_Support8BitBusWidth)
    {
        HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH8BIT);
        if ((kStatus_Success == MMC_TestDataBusWidth(card, kMMC_DataBusWidth8bit)) &&
            (kStatus_Success == MMC_SetDataBusWidth(card, kMMC_DataBusWidth8bit)))
        {
            card->flags |= kMMC_DataBusWidth8BitFlag;
            error = kStatus_Success;
        }
    }
    /* HS400 mode only support 8bit data bus */
    if ((error == kStatus_Fail) && (card->currentTiming == kMMC_HighSpeed400Timing))
    {
        return kStatus_SDMMC_SetDataBusWidthFailed;
    }

    if ((error == kStatus_Fail) && (card->host.capability.flags & kHOST_Support4BitBusWidth))
    {
        HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH4BIT);
        if ((kStatus_Success == MMC_TestDataBusWidth(card, kMMC_DataBusWidth4bit)) &&
            (kStatus_Success == MMC_SetDataBusWidth(card, kMMC_DataBusWidth4bit)))
        {
            card->flags |= kMMC_DataBusWidth4BitFlag;
            error = kStatus_Success;
        }
    }

    /* HS200/DDR mode only support 4bit/8bit data bus */
    if ((error == kStatus_Fail) && ((card->currentTiming == kMMC_HighSpeed200Timing) ||
                                    (card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming) ||
                                    (card->currentTiming == kMMC_HighSpeedDDR52120VTiming)))
    {
        return kStatus_SDMMC_SetDataBusWidthFailed;
    }

    if (error == kStatus_Fail)
    {
        card->flags |= kMMC_DataBusWidth1BitFlag;
        /* Card's data bus width will be default 1 bit mode. */
        HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH1BIT);
    }

    return kStatus_Success;
}

static status_t MMC_SelectCardDriverStrength(mmc_card_t *card, uint8_t driverStrength)
{
    assert(card);

    uint8_t ioStrength = 0U;
    mmc_extended_csd_config_t extendedCsdconfig;

    ioStrength = card->extendedCsd.highSpeedTiming | (uint8_t)(driverStrength << 4U);

    /* Switch to high speed timing. */
    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexHighSpeedTiming;
    extendedCsdconfig.ByteValue = ioStrength;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.highSpeedTiming |= ioStrength;

    return kStatus_Success;
}

static status_t MMC_SelectBusTiming(mmc_card_t *card)
{
    assert(card);

    uint32_t value = 0U;
    uint32_t targetFreq = 0U;

    mmc_extended_csd_config_t extendedCsdconfig;

    /* 1.8V and 1.2V timing select */
    if (((kHOST_SupportHS200 != HOST_NOT_SUPPORT) || (kHOST_SupportHS400 != HOST_NOT_SUPPORT) ||
         (kHOST_SupportDDR50 != HOST_NOT_SUPPORT)) &&
        ((card->hostVoltageWindow == kMMC_VoltageWindow170to195) || (card->hostVoltageWindow == kMMC_VoltageWindow120)))
    {
        switch (card->currentTiming)
        {
            case kMMC_HighSpeedTimingNone:
            case kMMC_HighSpeed400Timing:
                if ((card->host.capability.flags & kHOST_SupportHS400) &&
                    (card->flags & kMMC_SupportHS400DDR200MHZ180VFlag))
                {
                    value = kMMC_HighSpeed400Timing;
                    card->currentTiming = kMMC_HighSpeed400Timing;
                    targetFreq = HOST_SUPPORT_HS400_FREQ;
                    break;
                }
            case kMMC_HighSpeed200Timing:
                if ((card->flags & kMMC_SupportHS200200MHZ180VFlag) &&
                    ((card->host.capability.flags & kHOST_SupportHS200)))
                {
                    value = kMMC_HighSpeed200Timing;
                    card->currentTiming = kMMC_HighSpeed200Timing;
                    targetFreq = HOST_SUPPORT_HS200_FREQ;
                    break;
                }
            case kMMC_HighSpeedDDR52120VTiming:
            case kMMC_HighSpeedDDR52180V300VTiming:
                if ((card->hostVoltageWindow == kMMC_VoltageWindow170to195))
                {
                    if ((card->flags & kMMC_SupportHighSpeedDDR52MHZ180V300VFlag) &&
                        (card->host.capability.flags & kHOST_SupportDDR50))
                    {
                        targetFreq = MMC_CLOCK_DDR52;
                        value = kMMC_HighSpeedTiming;
                        card->currentTiming = kMMC_HighSpeedDDR52180V300VTiming;
                        break;
                    }
                }
                else
                {
                    if ((card->flags & kMMC_SupportHighSpeedDDR52MHZ120VFlag) &&
                        (card->host.capability.flags & kHOST_SupportDDR50))
                    {
                        value = kMMC_HighSpeedTiming;
                        targetFreq = MMC_CLOCK_DDR52;
                        card->currentTiming = kMMC_HighSpeedDDR52120VTiming;
                        break;
                    }
                }
            case kMMC_HighSpeed52MHZTiming:
                if (card->flags & kMMC_SupportHighSpeed52MHZFlag)
                {
                    value = kMMC_HighSpeedTiming;
                    targetFreq = MMC_CLOCK_52MHZ;
                    card->currentTiming = kMMC_HighSpeed52MHZTiming;
                    break;
                }
            case kMMC_HighSpeed26MHZTiming:
                if (card->flags & kMMC_SupportHighSpeed26MHZFlag)
                {
                    value = kMMC_HighSpeedTiming;
                    targetFreq = MMC_CLOCK_26MHZ;
                    card->currentTiming = kMMC_HighSpeed26MHZTiming;
                    break;
                }

            default:
                return kStatus_SDMMC_SwitchBusTimingFailed;
        }
    }
    /* 3.3V timing */
    else if (((card->host.capability.flags) & kHOST_SupportHighSpeed) || (kHOST_SupportDDR50 != HOST_NOT_SUPPORT))
    {
        /* high speed mode */
        value = kMMC_HighSpeedTiming;

        switch (card->currentTiming)
        {
            case kMMC_HighSpeedTimingNone:
            case kMMC_HighSpeed400Timing:
            case kMMC_HighSpeed200Timing:
            case kMMC_HighSpeedDDR52120VTiming:
            case kMMC_HighSpeedDDR52180V300VTiming:
                if ((card->flags & kMMC_SupportHighSpeedDDR52MHZ180V300VFlag) &&
                    (kHOST_SupportDDR50 != HOST_NOT_SUPPORT))
                {
                    targetFreq = MMC_CLOCK_DDR52;
                    card->currentTiming = kMMC_HighSpeedDDR52180V300VTiming;
                    break;
                }
            case kMMC_HighSpeed52MHZTiming:
                if (card->flags & kMMC_SupportHighSpeed52MHZFlag)
                {
                    targetFreq = MMC_CLOCK_52MHZ;
                    card->currentTiming = kMMC_HighSpeed52MHZTiming;
                    break;
                }
            case kMMC_HighSpeed26MHZTiming:
                if (card->flags & kMMC_SupportHighSpeed26MHZFlag)
                {
                    targetFreq = MMC_CLOCK_26MHZ;
                    card->currentTiming = kMMC_HighSpeed26MHZTiming;
                    break;
                }
            default:
                return kStatus_SDMMC_SwitchBusTimingFailed;
        }
    }
    else
    {
        /*default mode*/
        value = 0U;
        card->currentTiming = kMMC_HighSpeedTimingNone;
    }

    if (card->currentTiming == kMMC_HighSpeed200Timing)
    {
        /* select bus width before select bus timing for HS200 mode */
        if (MMC_SetMaxDataBusWidth(card) != kStatus_Success)
        {
            return kStatus_SDMMC_SetDataBusWidthFailed;
        }
    }

    if (card->currentTiming != kMMC_HighSpeedTimingNone)
    {
        /* Switch to high speed timing. */
        extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
        extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexHighSpeedTiming;
        extendedCsdconfig.ByteValue = value;
        extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
        if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
        {
            return kStatus_SDMMC_ConfigureExtendedCsdFailed;
        }
        card->extendedCsd.highSpeedTiming |= value;

        /* Set card data width, it is nessesary to config the the data bus here, to meet emmc5.0 specification,
        * when you are working in DDR mode , HS_TIMING must set before set bus width
        */
        if (card->currentTiming != kMMC_HighSpeed200Timing)
        {
            if (MMC_SetMaxDataBusWidth(card) != kStatus_Success)
            {
                return kStatus_SDMMC_SetDataBusWidthFailed;
            }
        }
        card->busClock_Hz = HOST_SET_CARD_CLOCK(card->host.base, card->host.sourceClock_Hz, targetFreq);
    }

    if ((card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming) ||
        (card->currentTiming == kMMC_HighSpeedDDR52120VTiming) || (card->currentTiming == kMMC_HighSpeed400Timing))
    {
        HOST_ENABLE_DDR_MODE(card->host.base, true);
        /* enable HS400 mode */
        if (card->currentTiming == kMMC_HighSpeed400Timing)
        {
            HOST_ENABLE_HS400_MODE(card->host.base, true);
        }
    }
    return kStatus_Success;
}

static void MMC_DecodeCid(mmc_card_t *card, uint32_t *rawCid)
{
    assert(card);
    assert(rawCid);

    mmc_cid_t *cid;

    cid = &(card->cid);
    cid->manufacturerID = (uint8_t)((rawCid[3U] & 0xFF000000U) >> 24U);
    cid->applicationID = (uint16_t)((rawCid[3U] & 0xFFFF00U) >> 8U);

    cid->productName[0U] = (uint8_t)((rawCid[3U] & 0xFFU));
    cid->productName[1U] = (uint8_t)((rawCid[2U] & 0xFF000000U) >> 24U);
    cid->productName[2U] = (uint8_t)((rawCid[2U] & 0xFF0000U) >> 16U);
    cid->productName[3U] = (uint8_t)((rawCid[2U] & 0xFF00U) >> 8U);
    cid->productName[4U] = (uint8_t)((rawCid[2U] & 0xFFU));

    cid->productVersion = (uint8_t)((rawCid[1U] & 0xFF000000U) >> 24U);

    cid->productSerialNumber = (uint32_t)((rawCid[1U] & 0xFFFFFFU) << 8U);
    cid->productSerialNumber |= (uint32_t)((rawCid[0U] & 0xFF000000U) >> 24U);

    cid->manufacturerData = (uint16_t)((rawCid[0U] & 0xFFF00U) >> 8U);
}

static status_t MMC_AllSendCid(mmc_card_t *card)
{
    assert(card);
    assert(card->host.transfer);

    HOST_TRANSFER content = {0};
    HOST_COMMAND command = {0};

    command.index = kSDMMC_AllSendCid;
    command.argument = 0U;
    command.responseType = kCARD_ResponseTypeR2;

    content.command = &command;
    content.data = NULL;
    if (kStatus_Success == card->host.transfer(card->host.base, &content))
    {
        memcpy(card->rawCid, command.response, sizeof(card->rawCid));
        MMC_DecodeCid(card, command.response);

        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static status_t MMC_SendCsd(mmc_card_t *card)
{
    assert(card);
    assert(card->host.transfer);

    HOST_COMMAND command = {0};
    HOST_TRANSFER content = {0};

    command.index = kSDMMC_SendCsd;
    command.argument = (card->relativeAddress << 16U);
    command.responseType = kCARD_ResponseTypeR2;

    content.command = &command;
    content.data = 0U;
    if (kStatus_Success == card->host.transfer(card->host.base, &content))
    {
        memcpy(card->rawCsd, command.response, sizeof(card->rawCsd));
        /* The response is from bit 127:8 in R2, corresponding to command.response[3][31:0] to
        command.response[0U][31:8]. */
        MMC_DecodeCsd(card, card->rawCsd);

        return kStatus_Success;
    }

    return kStatus_SDMMC_TransferFailed;
}

static status_t MMC_CheckBlockRange(mmc_card_t *card, uint32_t startBlock, uint32_t blockCount)
{
    assert(card);
    assert(blockCount);

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
    assert(card);

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
    assert(card);
    assert(card->host.transfer);
    assert(buffer);
    assert(blockCount);
    assert(blockSize);
    assert(blockSize == FSL_SDMMC_DEFAULT_BLOCK_SIZE);

    HOST_COMMAND command = {0};
    HOST_DATA data = {0};
    HOST_TRANSFER content = {0};
    status_t error;

    if (((card->flags & kMMC_SupportHighCapacityFlag) && (blockSize != 512U)) || (blockSize > card->blockSize) ||
        (blockSize > card->host.capability.maxBlockLength) || (blockSize % 4U))
    {
        return kStatus_SDMMC_CardNotSupport;
    }

    /* Wait for the card write process complete because of that card read process and write process use one buffer. */
    if (kStatus_Success != MMC_WaitWriteComplete(card))
    {
        return kStatus_SDMMC_WaitWriteCompleteFailed;
    }

    data.blockSize = blockSize;
    data.blockCount = blockCount;
    data.rxData = (uint32_t *)buffer;
    data.enableAutoCommand12 = true;
    command.index = kSDMMC_ReadMultipleBlock;
    if (data.blockCount == 1U)
    {
        command.index = kSDMMC_ReadSingleBlock;
    }
    else
    {
        if ((!(data.enableAutoCommand12)) && (card->enablePreDefinedBlockCount))
        {
            /* If enabled the pre-define count read/write feature of the card, need to set block count firstly. */
            if (kStatus_Success != MMC_SetBlockCount(card, blockCount))
            {
                return kStatus_SDMMC_SetBlockCountFailed;
            }
        }
    }
    command.argument = startBlock;
    if (!(card->flags & kMMC_SupportHighCapacityFlag))
    {
        command.argument *= data.blockSize;
    }
    command.responseType = kCARD_ResponseTypeR1;
    command.responseErrorFlags = kSDMMC_R1ErrorAllFlag;

    content.command = &command;
    content.data = &data;

    /* should check tuning error during every transfer */
    error = MMC_Transfer(card, &content, 0U);
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
    assert(card);
    assert(card->host.transfer);
    assert(buffer);
    assert(blockCount);
    assert(blockSize);
    assert(blockSize == FSL_SDMMC_DEFAULT_BLOCK_SIZE);

    HOST_COMMAND command = {0};
    HOST_DATA data = {0};
    HOST_TRANSFER content = {0};
    status_t error;

    /* Check address range */
    if (((card->flags & kMMC_SupportHighCapacityFlag) && (blockSize != 512U)) || (blockSize > card->blockSize) ||
        (blockSize > card->host.capability.maxBlockLength) || (blockSize % 4U))
    {
        return kStatus_SDMMC_CardNotSupport;
    }

    /* Wait for the card's buffer to be not full to write to improve the write performance. */
    while ((GET_HOST_STATUS(card->host.base) & CARD_DATA0_STATUS_MASK) != CARD_DATA0_NOT_BUSY)
    {
    }

    data.blockSize = blockSize;
    data.blockCount = blockCount;
    data.txData = (const uint32_t *)buffer;
    data.enableAutoCommand12 = true;

    command.index = kSDMMC_WriteMultipleBlock;
    if (data.blockCount == 1U)
    {
        command.index = kSDMMC_WriteSingleBlock;
    }
    else
    {
        if ((!(data.enableAutoCommand12)) && (card->enablePreDefinedBlockCount))
        {
            /* If enabled the pre-define count read/write featue of the card, need to set block count firstly */
            if (kStatus_Success != MMC_SetBlockCount(card, blockCount))
            {
                return kStatus_SDMMC_SetBlockCountFailed;
            }
        }
    }
    command.argument = startBlock;
    if (!(card->flags & kMMC_SupportHighCapacityFlag))
    {
        command.argument *= blockSize;
    }
    command.responseType = kCARD_ResponseTypeR1;
    command.responseErrorFlags = kSDMMC_R1ErrorAllFlag;

    content.command = &command;
    content.data = &data;

    /* should check tuning error during every transfer */
    error = MMC_Transfer(card, &content, 0U);
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

status_t MMC_Init(mmc_card_t *card)
{
    assert(card);

    status_t error = kStatus_Success;
    uint32_t opcode = 0U;

    if (!card->isHostReady)
    {
        error = HOST_Init(&(card->host));
        if (error != kStatus_Success)
        {
            return error;
        }
        /* set the host status flag, after the card re-plug in, don't need init host again */
        card->isHostReady = true;
    }

    /* voltage switch to normal but not 1.8V */
    HOST_SWITCH_VOLTAGE180V(card->host.base, false);
    /* reset DATA bus width */
    HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH1BIT);
    /* disable tuning */
    HOST_EXECUTE_STANDARD_TUNING_ENABLE(card->host.base, false);
    /* Disable DDR mode */
    HOST_ENABLE_DDR_MODE(card->host.base, false);
    /* get host capability first */
    GET_HOST_CAPABILITY(card->host.base, &(card->host.capability));
    /* Set clock to 400KHz. */
    card->busClock_Hz = HOST_SET_CARD_CLOCK(card->host.base, card->host.sourceClock_Hz, SDMMC_CLOCK_400KHZ);
    /* Send CMD0 to reset the bus */
    if (kStatus_Success != MMC_GoIdle(card))
    {
        return kStatus_SDMMC_GoIdleFailed;
    }

    /* Hand-shaking with card to validata the voltage range Host first sending its expected
       information.*/
    if (kStatus_Success != MMC_SendOperationCondition(card, 0U))
    {
        return kStatus_SDMMC_HandShakeOperationConditionFailed;
    }

    /* switch the host voltage which the card can support */
    if (kStatus_Success != MMC_SwitchVoltage(card, &opcode))
    {
        return kStatus_SDMMC_HandShakeOperationConditionFailed;
    }

    /* Get host's access mode. */
    if (card->host.capability.maxBlockLength >= FSL_SDMMC_DEFAULT_BLOCK_SIZE)
    {
        opcode |= kMMC_AccessModeSector << MMC_OCR_ACCESS_MODE_SHIFT;
    }
    else
    {
        opcode |= kMMC_AccessModeSector << MMC_OCR_ACCESS_MODE_SHIFT;
    }

    if (kStatus_Success != MMC_SendOperationCondition(card, opcode))
    {
        return kStatus_SDMMC_HandShakeOperationConditionFailed;
    }

    /* Get card CID */
    if (kStatus_Success != MMC_AllSendCid(card))
    {
        return kStatus_SDMMC_AllSendCidFailed;
    }

    /* Set the card relative address */
    if (kStatus_Success != MMC_SetRelativeAddress(card))
    {
        return kStatus_SDMMC_SetRelativeAddressFailed;
    }

    /* Get the CSD register content */
    if (kStatus_Success != MMC_SendCsd(card))
    {
        return kStatus_SDMMC_SendCsdFailed;
    }

    /* Set to maximum speed in normal mode. */
    MMC_SetMaxFrequency(card);

    /* Send CMD7 with the card's relative address to place the card in transfer state. Puts current selected card in
    transfer state. */
    if (kStatus_Success != MMC_SelectCard(card, true))
    {
        return kStatus_SDMMC_SelectCardFailed;
    }

    /* Get Extended CSD register content. */
    if (kStatus_Success != MMC_SendExtendedCsd(card))
    {
        return kStatus_SDMMC_SendExtendedCsdFailed;
    }
    /* set block size */
    if (MMC_SetBlockSize(card, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
    {
        return kStatus_SDMMC_SetCardBlockSizeFailed;
    }

    /* switch to host support speed mode, then switch MMC data bus width and select power class */
    if (kStatus_Success != MMC_SelectBusTiming(card))
    {
        return kStatus_SDMMC_SwitchBusTimingFailed;
    }

    if ((card->currentTiming == kMMC_HighSpeed200Timing) || (card->currentTiming == kMMC_HighSpeed400Timing))
    {
        /* config IO strength */
        HOST_CONFIG_MMC_IO(CARD_BUS_FREQ_200MHZ, CARD_BUS_STRENGTH_7);
        /* excute tuning for HS200 and HS400*/
        if (MMC_ExecuteTuning(card) != kStatus_Success)
        {
            return kStatus_SDMMC_TuningFail;
        }
        /* config driver strength */
        if (kStatus_Success != MMC_SelectCardDriverStrength(card, kMMC_DriverStrength0))
        {
            return kStatus_SDMMC_SetDriverStrengthFail;
        }
    }
    else if ((card->currentTiming == kMMC_HighSpeedDDR52180V300VTiming) ||
             (card->currentTiming == kMMC_HighSpeedDDR52120VTiming))
    {
        /*config IO strength*/
        HOST_CONFIG_MMC_IO(CARD_BUS_FREQ_100MHZ1, CARD_BUS_STRENGTH_4);
    }
    else
    {
        HOST_CONFIG_MMC_IO(CARD_BUS_FREQ_50MHZ, CARD_BUS_STRENGTH_3);
    }

    /* Set to max erase unit size */
    if (kStatus_Success != MMC_SetMaxEraseUnitSize(card))
    {
        return kStatus_SDMMC_EnableHighCapacityEraseFailed;
    }

    /* Set card default to access non-boot partition */
    card->currentPartition = kMMC_AccessPartitionUserAera;

    return kStatus_Success;
}

void MMC_Deinit(mmc_card_t *card)
{
    assert(card);

    MMC_SelectCard(card, false);
    HOST_Deinit(&(card->host));
    /* should re-init host */
    card->isHostReady = false;
}

bool MMC_CheckReadOnly(mmc_card_t *card)
{
    assert(card);

    return ((card->csd.flags & kMMC_CsdPermanentWriteProtectFlag) ||
            (card->csd.flags & kMMC_CsdTemporaryWriteProtectFlag));
}

status_t MMC_SelectPartition(mmc_card_t *card, mmc_access_partition_t partitionNumber)
{
    assert(card);

    uint8_t bootConfig;
    mmc_extended_csd_config_t extendedCsdconfig;

    bootConfig = card->extendedCsd.partitionConfig;
    bootConfig &= ~MMC_BOOT_CONFIG_PARTITION_ACCESS_MASK;
    bootConfig |= ((uint32_t)partitionNumber << MMC_BOOT_CONFIG_PARTITION_ACCESS_SHIFT);

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexBootConfig;
    extendedCsdconfig.ByteValue = bootConfig;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    /* Save current configuration. */
    card->extendedCsd.partitionConfig = bootConfig;
    card->currentPartition = partitionNumber;

    return kStatus_Success;
}

status_t MMC_ReadBlocks(mmc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    assert(card);
    assert(buffer);
    assert(blockCount);

    uint32_t blockCountOneTime; /* The block count can be erased in one time sending READ_BLOCKS command. */
    uint32_t blockDone;         /* The blocks has been read. */
    uint32_t blockLeft;         /* Left blocks to be read. */
    uint8_t *nextBuffer;
    status_t error = kStatus_Success;

    blockLeft = blockCount;
    blockDone = 0U;
    if (kStatus_Success != MMC_CheckBlockRange(card, startBlock, blockCount))
    {
        return kStatus_InvalidArgument;
    }

    while (blockLeft)
    {
        if (blockLeft > card->host.capability.maxBlockCount)
        {
            blockLeft = blockLeft - card->host.capability.maxBlockCount;
            blockCountOneTime = card->host.capability.maxBlockCount;
        }
        else
        {
            blockCountOneTime = blockLeft;
            blockLeft = 0U;
        }

        nextBuffer = (buffer + blockDone * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
        error = MMC_Read(card, nextBuffer, (startBlock + blockDone), FSL_SDMMC_DEFAULT_BLOCK_SIZE, blockCount);
        if (error != kStatus_Success)
        {
            return error;
        }

        blockDone += blockCountOneTime;
    }

    return error;
}

status_t MMC_WriteBlocks(mmc_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    assert(card);
    assert(buffer);
    assert(blockCount);

    uint32_t blockCountOneTime;
    uint32_t blockLeft;
    uint32_t blockDone;
    const uint8_t *nextBuffer;
    status_t error = kStatus_Success;

    blockLeft = blockCount;
    blockDone = 0U;
    if (kStatus_Success != MMC_CheckBlockRange(card, startBlock, blockCount))
    {
        return kStatus_InvalidArgument;
    }

    while (blockLeft)
    {
        if (blockLeft > card->host.capability.maxBlockCount)
        {
            blockLeft = blockLeft - card->host.capability.maxBlockCount;
            blockCountOneTime = card->host.capability.maxBlockCount;
        }
        else
        {
            blockCountOneTime = blockLeft;
            blockLeft = 0U;
        }

        nextBuffer = (buffer + blockDone * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
        error = MMC_Write(card, nextBuffer, (startBlock + blockDone), FSL_SDMMC_DEFAULT_BLOCK_SIZE, blockCount);
        if (error != kStatus_Success)
        {
            return error;
        }

        blockDone += blockCountOneTime;
    }

    return error;
}

status_t MMC_EraseGroups(mmc_card_t *card, uint32_t startGroup, uint32_t endGroup)
{
    assert(card);
    assert(card->host.transfer);

    uint32_t startGroupAddress;
    uint32_t endGroupAddress;
    HOST_COMMAND command = {0};
    HOST_TRANSFER content = {0};

    if (kStatus_Success != MMC_CheckEraseGroupRange(card, startGroup, endGroup))
    {
        return kStatus_InvalidArgument;
    }

    /* Wait for the card's buffer to be not full to write to improve the write performance. */
    while ((GET_HOST_STATUS(card->host.base) & CARD_DATA0_STATUS_MASK) != CARD_DATA0_NOT_BUSY)
    {
    }

    /* Calculate the start group address and end group address */
    startGroupAddress = startGroup;
    endGroupAddress = endGroup;
    if (card->flags & kMMC_SupportHighCapacityFlag)
    {
        /* The implementation of a higher than 2GB of density of memory will not be backwards compatible with the
        lower densities.First of all the address argument for higher than 2GB of density of memory is changed to
        be sector address (512B sectors) instead of byte address */
        startGroupAddress = (startGroupAddress * (card->eraseGroupBlocks));
        endGroupAddress = (endGroupAddress * (card->eraseGroupBlocks));
    }
    else
    {
        /* The address unit is byte when card capacity is lower than 2GB */
        startGroupAddress = (startGroupAddress * (card->eraseGroupBlocks) * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
        endGroupAddress = (endGroupAddress * (card->eraseGroupBlocks) * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    }

    /* Set the start erase group address */
    command.index = kMMC_EraseGroupStart;
    command.argument = startGroupAddress;
    command.responseType = kCARD_ResponseTypeR1;
    command.responseErrorFlags = kSDMMC_R1ErrorAllFlag;

    content.command = &command;
    content.data = NULL;
    if (kStatus_Success != MMC_Transfer(card, &content, 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Set the end erase group address */
    command.index = kMMC_EraseGroupEnd;
    command.argument = endGroupAddress;

    content.command = &command;
    content.data = NULL;
    if (kStatus_Success != MMC_Transfer(card, &content, 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Start the erase process */
    command.index = kSDMMC_Erase;
    command.argument = 0U;
    command.responseType = kCARD_ResponseTypeR1b;
    command.responseErrorFlags = kSDMMC_R1ErrorAllFlag;

    content.command = &command;
    content.data = NULL;
    if (kStatus_Success != MMC_Transfer(card, &content, 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t MMC_SetBootConfig(mmc_card_t *card, const mmc_boot_config_t *config)
{
    assert(card);
    assert(config);

    uint8_t bootParameter;
    mmc_extended_csd_config_t extendedCsdconfig;

    if (kMMC_ExtendedCsdRevision13 != card->extendedCsd.extendecCsdVersion) /* Only V4.3 support fast boot */
    {
        return kStatus_SDMMC_NotSupportYet;
    }

    /* Set the BOOT_CONFIG field of Extended CSD */
    bootParameter = card->extendedCsd.partitionConfig;
    bootParameter &= ~(MMC_BOOT_CONFIG_ACK_MASK);
    bootParameter &= ~(MMC_BOOT_CONFIG_PARTITION_ENABLE_MASK);
    bootParameter |= ((config->enableBootAck ? 1U : 0U) << MMC_BOOT_CONFIG_ACK_SHIFT);
    bootParameter |= ((uint32_t)(config->bootPartition) << MMC_BOOT_CONFIG_PARTITION_ENABLE_SHIFT);

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexBootConfig;
    extendedCsdconfig.ByteValue = bootParameter;
    extendedCsdconfig.commandSet = kMMC_CommandSetStandard;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
    {
        return kStatus_SDMMC_ConfigureExtendedCsdFailed;
    }

    card->extendedCsd.partitionConfig = bootParameter;

    /*Set BOOT_BUS_WIDTH in Extended CSD */
    bootParameter = card->extendedCsd.bootDataBusWidth;
    bootParameter &= ~(MMC_BOOT_BUS_WIDTH_RESET_MASK);
    bootParameter &= ~(MMC_BOOT_BUS_WIDTH_WIDTH_MASK);
    bootParameter |= ((config->retainBootBusWidth ? 1U : 0U) << MMC_BOOT_BUS_WIDTH_RESET_SHIFT);
    bootParameter |= ((uint32_t)(config->bootDataBusWidth) << MMC_BOOT_BUS_WIDTH_WIDTH_SHIFT);

    extendedCsdconfig.accessMode = kMMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex = kMMC_ExtendedCsdIndexBootBusWidth;
    extendedCsdconfig.ByteValue = bootParameter;
    if (kStatus_Success != MMC_SetExtendedCsdConfig(card, &extendedCsdconfig))
    {
        return kStatus_SDMMC_ConfigureBootFailed;
    }

    card->extendedCsd.bootDataBusWidth = bootParameter;

    return kStatus_Success;
}
