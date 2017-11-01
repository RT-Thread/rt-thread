/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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

#include "fsl_card.h"
#include "fsl_sdmmc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SDIO_COMMON_CIS_TUPLE_NUM (3U) /*!< define the tuple number will be read during init */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief send card operation condition
 * @param card Card descriptor.
 * @param command argment
 *  argument = 0U , means to get the operation condition
 *  argument !=0 , set the operation condition register
 */
static status_t SDIO_SendOperationCondition(sdio_card_t *card, uint32_t argument);

/*!
 * @brief card Send relative address
 * @param card Card descriptor.
 */
static status_t SDIO_SendRca(sdio_card_t *card);

/*!
 * @brief card select card
 * @param card Card descriptor.
 * @param select/diselect flag
 */
static status_t inline SDIO_SelectCard(sdio_card_t *card, bool isSelected);

/*!
 * @brief decode CIS
 * @param card Card descriptor.
 * @param func number
 * @param data buffer pointer
 * @param tuple code
 * @param tuple link
 */
static status_t SDIO_DecodeCIS(
    sdio_card_t *card, sdio_func_num_t func, uint8_t *dataBuffer, uint32_t tplCode, uint32_t tplLink);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* define the tuple list */
static const uint32_t g_tupleList[SDIO_COMMON_CIS_TUPLE_NUM] = {
    SDIO_TPL_CODE_MANIFID, SDIO_TPL_CODE_FUNCID, SDIO_TPL_CODE_FUNCE,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t inline SDIO_SelectCard(sdio_card_t *card, bool isSelected)
{
    assert(card);

    return SDMMC_SelectCard(card->host.base, card->host.transfer, card->relativeAddress, isSelected);
}

static status_t SDIO_SendRca(sdio_card_t *card)
{
    assert(card);

    uint32_t i = FSL_SDMMC_MAX_CMD_RETRIES;

    HOST_TRANSFER content = {0};
    HOST_COMMAND command = {0};

    command.index = kSDIO_SendRelativeAddress;
    command.argument = 0U;
    command.responseType = kCARD_ResponseTypeR6;
    command.responseErrorFlags = kSDIO_StatusR6Error | kSDIO_StatusIllegalCmd | kSDIO_StatusCmdCRCError;

    content.command = &command;
    content.data = NULL;

    while (--i)
    {
        if (kStatus_Success == card->host.transfer(card->host.base, &content))
        {
            /* check illegal state and cmd CRC error, may be the voltage or clock not stable, retry the cmd*/
            if (command.response[0U] & (kSDIO_StatusIllegalCmd | kSDIO_StatusCmdCRCError))
            {
                continue;
            }

            card->relativeAddress = (command.response[0U] >> 16U);

            return kStatus_Success;
        }
    }

    return kStatus_SDMMC_TransferFailed;
}

status_t SDIO_CardInActive(sdio_card_t *card)
{
    assert(card);

    return SDMMC_SetCardInactive(card->host.base, card->host.transfer);
}

static status_t SDIO_SendOperationCondition(sdio_card_t *card, uint32_t argument)
{
    assert(card);

    HOST_TRANSFER content = {0U};
    HOST_COMMAND command = {0U};
    uint32_t i = FSL_SDMMC_MAX_VOLTAGE_RETRIES;

    command.index = kSDIO_SendOperationCondition;
    command.argument = argument;
    command.responseType = kCARD_ResponseTypeR4;

    content.command = &command;
    content.data = NULL;

    while (--i)
    {
        if (kStatus_Success != card->host.transfer(card->host.base, &content))
        {
            continue;
        }

        /* if argument equal 0, then should check and save the info */
        if (argument == 0U)
        {
            /* check if memory present */
            if ((command.response[0U] & kSDIO_OcrMemPresent) == kSDIO_OcrMemPresent)
            {
                card->memPresentFlag = true;
            }
            /* save the io number */
            card->ioTotalNumber = (command.response[0U] & kSDIO_OcrIONumber) >> 28U;
            /* save the operation condition */
            card->ocr = command.response[0U] & 0xFFFFFFU;

            break;
        }
        /* wait the card is ready for after initialization */
        else if (command.response[0U] & kSDIO_OcrPowerUpBusyFlag)
        {
            break;
        }
    }

    return ((i != 0U) ? kStatus_Success : kStatus_Fail);
}

status_t SDIO_IO_Write_Direct(sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *data, bool raw)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    HOST_TRANSFER content = {0U};
    HOST_COMMAND command = {0U};

    command.index = kSDIO_RWIODirect;
    command.argument = (func << SDIO_CMD_ARGUMENT_FUNC_NUM_POS) |
                       ((regAddr & SDIO_CMD_ARGUMENT_REG_ADDR_MASK) << SDIO_CMD_ARGUMENT_REG_ADDR_POS) |
                       (1U << SDIO_CMD_ARGUMENT_RW_POS) | ((raw ? 1U : 0U) << SDIO_DIRECT_CMD_ARGUMENT_RAW_POS) |
                       (*data & SDIO_DIRECT_CMD_DATA_MASK);
    command.responseType = kCARD_ResponseTypeR5;
    command.responseErrorFlags = (kSDIO_StatusCmdCRCError | kSDIO_StatusIllegalCmd | kSDIO_StatusError |
                                  kSDIO_StatusFunctionNumError | kSDIO_StatusOutofRange);

    content.command = &command;
    content.data = NULL;

    if (kStatus_Success != card->host.transfer(card->host.base, &content))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* read data from response */
    *data = command.response[0U] & SDIO_DIRECT_CMD_DATA_MASK;

    return kStatus_Success;
}

status_t SDIO_IO_Read_Direct(sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *data)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    HOST_TRANSFER content = {0U};
    HOST_COMMAND command = {0U};

    command.index = kSDIO_RWIODirect;
    command.argument = (func << SDIO_CMD_ARGUMENT_FUNC_NUM_POS) |
                       ((regAddr & SDIO_CMD_ARGUMENT_REG_ADDR_MASK) << SDIO_CMD_ARGUMENT_REG_ADDR_POS);
    command.responseType = kCARD_ResponseTypeR5;
    command.responseErrorFlags = (kSDIO_StatusCmdCRCError | kSDIO_StatusIllegalCmd | kSDIO_StatusError |
                                  kSDIO_StatusFunctionNumError | kSDIO_StatusOutofRange);

    content.command = &command;
    content.data = NULL;

    if (kStatus_Success != card->host.transfer(card->host.base, &content))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* read data from response */
    *data = command.response[0U] & SDIO_DIRECT_CMD_DATA_MASK;

    return kStatus_Success;
}

status_t SDIO_IO_Write_Extended(
    sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *buffer, uint32_t count, uint32_t flags)
{
    assert(card);
    assert(buffer);
    assert(func <= kSDIO_FunctionNum7);

    HOST_TRANSFER content = {0U};
    HOST_COMMAND command = {0U};
    HOST_DATA data = {0U};
    bool blockMode = false;
    bool opCode = false;

    /* check if card support block mode */
    if ((card->cccrflags & kSDIO_CCCRSupportMultiBlock) && (flags & SDIO_EXTEND_CMD_BLOCK_MODE_MASK))
    {
        blockMode = true;
    }

    if (flags & SDIO_EXTEND_CMD_OP_CODE_MASK)
    {
        opCode = true;
    }

    /* check the byte size counter in non-block mode
    * so you need read CIS for each function first,before you do read/write
    */
    if (!blockMode)
    {
        if ((func == kSDIO_FunctionNum0) && (card->commonCIS.fn0MaxBlkSize != 0U) &&
            (count > card->commonCIS.fn0MaxBlkSize))
        {
            return kStatus_SDMMC_SDIO_InvalidArgument;
        }
        else if ((func != kSDIO_FunctionNum0) && (card->funcCIS[func - 1U].ioMaxBlockSize != 0U) &&
                 (count > card->funcCIS[func - 1U].ioMaxBlockSize))
        {
            return kStatus_SDMMC_SDIO_InvalidArgument;
        }
    }

    command.index = kSDIO_RWIOExtended;
    command.argument = (func << SDIO_CMD_ARGUMENT_FUNC_NUM_POS) |
                       ((regAddr & SDIO_CMD_ARGUMENT_REG_ADDR_MASK) << SDIO_CMD_ARGUMENT_REG_ADDR_POS) |
                       (1U << SDIO_CMD_ARGUMENT_RW_POS) | (count & SDIO_EXTEND_CMD_COUNT_MASK) |
                       ((blockMode ? 1 : 0) << SDIO_EXTEND_CMD_ARGUMENT_BLOCK_MODE_POS |
                        ((opCode ? 1 : 0) << SDIO_EXTEND_CMD_ARGUMENT_OP_CODE_POS));
    command.responseType = kCARD_ResponseTypeR5;
    command.responseErrorFlags = (kSDIO_StatusCmdCRCError | kSDIO_StatusIllegalCmd | kSDIO_StatusError |
                                  kSDIO_StatusFunctionNumError | kSDIO_StatusOutofRange);

    if (blockMode)
    {
        if (func == kSDIO_FunctionNum0)
        {
            data.blockSize = card->io0blockSize;
        }
        else
        {
            data.blockSize = card->ioFBR[func - 1U].ioBlockSize;
        }
        data.blockCount = count;
    }
    else
    {
        data.blockSize = count;
        data.blockCount = 1U;
    }
    data.txData = (uint32_t *)buffer;

    content.command = &command;
    content.data = &data;

    if (kStatus_Success != card->host.transfer(card->host.base, &content))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDIO_IO_Read_Extended(
    sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *buffer, uint32_t count, uint32_t flags)
{
    assert(card);
    assert(buffer);
    assert(func <= kSDIO_FunctionNum7);

    HOST_TRANSFER content = {0U};
    HOST_COMMAND command = {0U};
    HOST_DATA data = {0U};
    bool blockMode = false;
    bool opCode = false;

    /* check if card support block mode */
    if ((card->cccrflags & kSDIO_CCCRSupportMultiBlock) && (flags & SDIO_EXTEND_CMD_BLOCK_MODE_MASK))
    {
        blockMode = true;
    }

    /* op code =0 : read/write to fixed addr
    *  op code =1 :read/write addr incrementing
     */
    if (flags & SDIO_EXTEND_CMD_OP_CODE_MASK)
    {
        opCode = true;
    }

    /* check the byte size counter in non-block mode
    * so you need read CIS for each function first,before you do read/write
    */
    if (!blockMode)
    {
        if ((func == kSDIO_FunctionNum0) && (card->commonCIS.fn0MaxBlkSize != 0U) &&
            (count > card->commonCIS.fn0MaxBlkSize))
        {
            return kStatus_SDMMC_SDIO_InvalidArgument;
        }
        else if ((func != kSDIO_FunctionNum0) && (card->funcCIS[func - 1U].ioMaxBlockSize != 0U) &&
                 (count > card->funcCIS[func - 1U].ioMaxBlockSize))
        {
            return kStatus_SDMMC_SDIO_InvalidArgument;
        }
    }

    command.index = kSDIO_RWIOExtended;
    command.argument = (func << SDIO_CMD_ARGUMENT_FUNC_NUM_POS) |
                       ((regAddr & SDIO_CMD_ARGUMENT_REG_ADDR_MASK) << SDIO_CMD_ARGUMENT_REG_ADDR_POS) |
                       (count & SDIO_EXTEND_CMD_COUNT_MASK) |
                       ((blockMode ? 1U : 0U) << SDIO_EXTEND_CMD_ARGUMENT_BLOCK_MODE_POS |
                        ((opCode ? 1U : 0U) << SDIO_EXTEND_CMD_ARGUMENT_OP_CODE_POS));
    command.responseType = kCARD_ResponseTypeR5;
    command.responseErrorFlags = (kSDIO_StatusCmdCRCError | kSDIO_StatusIllegalCmd | kSDIO_StatusError |
                                  kSDIO_StatusFunctionNumError | kSDIO_StatusOutofRange);

    if (blockMode)
    {
        if (func == kSDIO_FunctionNum0)
        {
            data.blockSize = card->io0blockSize;
        }
        else
        {
            data.blockSize = card->ioFBR[func - 1U].ioBlockSize;
        }
        data.blockCount = count;
    }
    else
    {
        data.blockSize = count;
        data.blockCount = 1U;
    }
    data.rxData = (uint32_t *)buffer;

    content.command = &command;
    content.data = &data;

    if (kStatus_Success != card->host.transfer(card->host.base, &content))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDIO_GetCardCapability(sdio_card_t *card, sdio_func_num_t func)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    uint8_t tempBuffer[20] = {0U};
    uint32_t i = 0U;

    for (i = 0U; i < 20U; i++)
    {
        if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, SDIO_FBR_BASE(func) + i, &tempBuffer[i]))
        {
            return kStatus_SDMMC_TransferFailed;
        }
    }

    switch (func)
    {
        case kSDIO_FunctionNum0:

            card->sdVersion = tempBuffer[1U];
            card->sdioVersion = tempBuffer[0U] >> 4U;
            card->cccrVersioin = tempBuffer[0U] & 0xFU;
            /* continuous SPI interrupt */
            if (tempBuffer[7U] & 0x40U)
            {
                card->cccrflags |= kSDIO_CCCRSupportContinuousSPIInt;
            }
            /* card capability register */
            card->cccrflags |= (tempBuffer[8U] & 0xDFU);
            /* master power control */
            if (tempBuffer[18U] & 0x01U)
            {
                card->cccrflags |= kSDIO_CCCRSupportMasterPowerControl;
            }
            /* high speed flag */
            if (tempBuffer[19U] & 0x01U)
            {
                card->cccrflags |= kSDIO_CCCRSupportHighSpeed;
            }
            /* common CIS pointer */
            card->commonCISPointer = tempBuffer[9U] | (tempBuffer[10U] << 8U) | (tempBuffer[11U] << 16U);

            break;

        case kSDIO_FunctionNum1:
        case kSDIO_FunctionNum2:
        case kSDIO_FunctionNum3:
        case kSDIO_FunctionNum4:
        case kSDIO_FunctionNum5:
        case kSDIO_FunctionNum6:
        case kSDIO_FunctionNum7:
            card->ioFBR[func - 1U].ioStdFunctionCode = tempBuffer[0U] & 0x0FU;
            card->ioFBR[func - 1U].ioExtFunctionCode = tempBuffer[1U];
            card->ioFBR[func - 1U].ioPointerToCIS = tempBuffer[9U] | (tempBuffer[10U] << 8U) | (tempBuffer[11U] << 16U);
            card->ioFBR[func - 1U].ioPointerToCSA =
                tempBuffer[12U] | (tempBuffer[13U] << 8U) | (tempBuffer[14U] << 16U);
            if (tempBuffer[2U] & 0x01U)
            {
                card->ioFBR[func - 1U].flags |= kSDIO_FBRSupportPowerSelection;
            }
            if (tempBuffer[0U] & 0x40U)
            {
                card->ioFBR[func - 1U].flags |= kSDIO_FBRSupportCSA;
            }

            break;

        default:
            break;
    }

    return kStatus_Success;
}

status_t SDIO_SetBlockSize(sdio_card_t *card, sdio_func_num_t func, uint32_t blockSize)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);
    assert(blockSize <= SDIO_MAX_BLOCK_SIZE);

    uint8_t temp = 0U;

    /* check the block size for block mode
    * so you need read CIS for each function first,before you do read/write
    */
    if ((func == kSDIO_FunctionNum0) && (card->commonCIS.fn0MaxBlkSize != 0U) &&
        (blockSize > card->commonCIS.fn0MaxBlkSize))
    {
        return kStatus_SDMMC_SDIO_InvalidArgument;
    }
    else if ((func != kSDIO_FunctionNum0) && (card->funcCIS[func - 1U].ioMaxBlockSize != 0U) &&
             (blockSize > card->funcCIS[func - 1U].ioMaxBlockSize))
    {
        return kStatus_SDMMC_SDIO_InvalidArgument;
    }

    temp = blockSize & 0xFFU;

    if (kStatus_Success !=
        SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, SDIO_FBR_BASE(func) + kSDIO_RegFN0BlockSizeLow, &temp, true))
    {
        return kStatus_SDMMC_SetCardBlockSizeFailed;
    }

    temp = (blockSize >> 8U) & 0xFFU;

    if (kStatus_Success !=
        SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, SDIO_FBR_BASE(func) + kSDIO_RegFN0BlockSizeHigh, &temp, true))
    {
        return kStatus_SDMMC_SetCardBlockSizeFailed;
    }

    /* record the current block size */
    if (func == kSDIO_FunctionNum0)
    {
        card->io0blockSize = blockSize;
    }
    else
    {
        card->ioFBR[func - 1U].ioBlockSize = blockSize;
    }

    return kStatus_Success;
}

status_t SDIO_CardReset(sdio_card_t *card)
{
    uint8_t reset = 0x08U;

    return SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOAbort, &reset, false);
}

status_t SDIO_SetDataBusWidth(sdio_card_t *card, sdio_bus_width_t busWidth)
{
    assert(card);

    uint8_t regBusInterface = 0U;

    /* load bus interface register */
    if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, kSDIO_RegBusInterface, &regBusInterface))
    {
        return kStatus_SDMMC_TransferFailed;
    }
    /* set bus width */
    regBusInterface |= busWidth;

    /* write to register */
    if (kStatus_Success !=
        SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegBusInterface, &regBusInterface, true))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDIO_SwitchToHighSpeed(sdio_card_t *card)
{
    assert(card);

    uint8_t temp = 0U;

    if (card->cccrflags & kSDIO_CCCRSupportHighSpeed)
    {
        /* enable high speed mode */
        temp = 0x02U;
        if (kStatus_Success != SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegHighSpeed, &temp, true))
        {
            return kStatus_SDMMC_TransferFailed;
        }
        /* either EHS=0 and SHS=0 ,the card is still in default mode  */
        if ((temp & 0x03U) == 0x03U)
        {
            /* set to 4bit data bus */
            SDIO_SetDataBusWidth(card, kSDIO_DataBus4Bit);
            HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH4BIT);
            /* high speed mode , set freq to 50MHZ */
            card->busClock_Hz = HOST_SET_CARD_CLOCK(card->host.base, card->host.sourceClock_Hz, SD_CLOCK_50MHZ);
        }
        else
        {
            return kStatus_SDMMC_SDIO_SwitchHighSpeedFail;
        }
    }

    return kStatus_Success;
}

static status_t SDIO_DecodeCIS(
    sdio_card_t *card, sdio_func_num_t func, uint8_t *dataBuffer, uint32_t tplCode, uint32_t tplLink)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    if (func == kSDIO_FunctionNum0)
    {
        /* only decode MANIFID,FUNCID,FUNCE here  */
        if (tplCode == SDIO_TPL_CODE_MANIFID)
        {
            card->commonCIS.mID = dataBuffer[0U] | (dataBuffer[1U] << 8U);
            card->commonCIS.mInfo = dataBuffer[2U] | (dataBuffer[3U] << 8U);
        }
        else if (tplCode == SDIO_TPL_CODE_FUNCID)
        {
            card->commonCIS.funcID = dataBuffer[0U];
        }
        else if (tplCode == SDIO_TPL_CODE_FUNCE)
        {
            /* max transfer block size and data size */
            card->commonCIS.fn0MaxBlkSize = dataBuffer[1U] | (dataBuffer[2U] << 8U);
            /* max transfer speed */
            card->commonCIS.maxTransSpeed = dataBuffer[3U];
        }
        else
        {
            /* reserved here */
            return kStatus_Fail;
        }
    }
    else
    {
        /* only decode FUNCID,FUNCE here  */
        if (tplCode == SDIO_TPL_CODE_FUNCID)
        {
            card->funcCIS[func].funcID = dataBuffer[0U];
        }
        else if (tplCode == SDIO_TPL_CODE_FUNCE)
        {
            if (tplLink == 0x2A)
            {
                card->funcCIS[func - 1U].funcInfo = dataBuffer[1U];
                card->funcCIS[func - 1U].ioVersion = dataBuffer[2U];
                card->funcCIS[func - 1U].cardPSN =
                    dataBuffer[3U] | (dataBuffer[4U] << 8U) | (dataBuffer[5U] << 16U) | (dataBuffer[6U] << 24U);
                card->funcCIS[func - 1U].ioCSASize =
                    dataBuffer[7U] | (dataBuffer[8U] << 8U) | (dataBuffer[9U] << 16U) | (dataBuffer[10U] << 24U);
                card->funcCIS[func - 1U].ioCSAProperty = dataBuffer[11U];
                card->funcCIS[func - 1U].ioMaxBlockSize = dataBuffer[12U] | (dataBuffer[13U] << 8U);
                card->funcCIS[func - 1U].ioOCR =
                    dataBuffer[14U] | (dataBuffer[15U] << 8U) | (dataBuffer[16U] << 16U) | (dataBuffer[17U] << 24U);
                card->funcCIS[func - 1U].ioOPMinPwr = dataBuffer[18U];
                card->funcCIS[func - 1U].ioOPAvgPwr = dataBuffer[19U];
                card->funcCIS[func - 1U].ioOPMaxPwr = dataBuffer[20U];
                card->funcCIS[func - 1U].ioSBMinPwr = dataBuffer[21U];
                card->funcCIS[func - 1U].ioSBAvgPwr = dataBuffer[22U];
                card->funcCIS[func - 1U].ioSBMaxPwr = dataBuffer[23U];
                card->funcCIS[func - 1U].ioMinBandWidth = dataBuffer[24U] | (dataBuffer[25U] << 8U);
                card->funcCIS[func - 1U].ioOptimumBandWidth = dataBuffer[26U] | (dataBuffer[27U] << 8U);
                card->funcCIS[func - 1U].ioReadyTimeout = dataBuffer[28U] | (dataBuffer[29U] << 8U);

                card->funcCIS[func - 1U].ioHighCurrentAvgCurrent = dataBuffer[34U] | (dataBuffer[35U] << 8U);
                card->funcCIS[func - 1U].ioHighCurrentMaxCurrent = dataBuffer[36U] | (dataBuffer[37U] << 8U);
                card->funcCIS[func - 1U].ioLowCurrentAvgCurrent = dataBuffer[38U] | (dataBuffer[39U] << 8U);
                card->funcCIS[func - 1U].ioLowCurrentMaxCurrent = dataBuffer[40U] | (dataBuffer[41U] << 8U);
            }
            else
            {
                return kStatus_Fail;
            }
        }
        else
        {
            return kStatus_Fail;
        }
    }

    return kStatus_Success;
}

status_t SDIO_ReadCIS(sdio_card_t *card, sdio_func_num_t func, const uint32_t *tupleList, uint32_t tupleNum)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);
    assert(tupleList);

    uint8_t tplCode = 0U;
    uint8_t tplLink = 0U;
    uint32_t cisPtr = 0U;
    uint32_t i = 0U, num = 0U;
    bool tupleMatch = false;

    uint8_t dataBuffer[255U] = {0U};

    /* get the CIS pointer for each function */
    if (func == kSDIO_FunctionNum0)
    {
        cisPtr = card->commonCISPointer;
    }
    else
    {
        cisPtr = card->ioFBR[func - 1U].ioPointerToCIS;
    }

    if (0U == cisPtr)
    {
        return kStatus_SDMMC_SDIO_ReadCISFail;
    }

    do
    {
        if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, cisPtr++, &tplCode))
        {
            return kStatus_SDMMC_TransferFailed;
        }
        /* end of chain tuple */
        if (tplCode == 0xFFU)
        {
            break;
        }

        if (tplCode == 0U)
        {
            continue;
        }

        for (i = 0; i < tupleNum; i++)
        {
            if (tplCode == tupleList[i])
            {
                tupleMatch = true;
                break;
            }
        }

        if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, cisPtr++, &tplLink))
        {
            return kStatus_SDMMC_TransferFailed;
        }
        /* end of chain tuple */
        if (tplLink == 0xFFU)
        {
            break;
        }

        if (tupleMatch)
        {
            memset(dataBuffer, 0U, 255U);
            for (i = 0; i < tplLink; i++)
            {
                if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, cisPtr++, &dataBuffer[i]))
                {
                    return kStatus_SDMMC_TransferFailed;
                }
            }
            tupleMatch = false;
            /* pharse the data */
            SDIO_DecodeCIS(card, func, dataBuffer, tplCode, tplLink);
            /* read finish then return */
            if (++num == tupleNum)
            {
                break;
            }
        }
        else
        {
            /* move pointer */
            cisPtr += tplLink;
            /* tuple code not match,continue read tuple code */
            continue;
        }
    } while (1);
    return kStatus_Success;
}

status_t SDIO_Init(sdio_card_t *card)
{
    assert(card);
    assert(card->host.base);

    status_t error = kStatus_Success;

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

    error = CardInsertDetect(card->host.base);
    if (error != kStatus_Success)
    {
        return error;
    }

    /* Identify mode ,set clock to 400KHZ. */
    card->busClock_Hz = HOST_SET_CARD_CLOCK(card->host.base, card->host.sourceClock_Hz, SDMMC_CLOCK_400KHZ);
    HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH1BIT);
    HOST_SEND_CARD_ACTIVE(card->host.base, 100U);

    /* get host capability */
    GET_HOST_CAPABILITY(card->host.base, &(card->host.capability));

    /* Get IO OCR-CMD5 with arg0 ,set new voltage if needed*/
    if (kStatus_Success != SDIO_SendOperationCondition(card, 0U))
    {
        return kStatus_SDMMC_HandShakeOperationConditionFailed;
    }

    /* there is a memonly card */
    if ((card->ioTotalNumber == 0U) && (card->memPresentFlag))
    {
        return kStatus_SDMMC_SDIO_InvalidCard;
    }
    /* verify the voltage and set the new voltage */
    if (card->host.capability.flags & kHOST_SupportV330)
    {
        if (kStatus_Success != SDIO_SendOperationCondition(card, kSDIO_OcrVdd32_33Flag | kSDIO_OcrVdd33_34Flag))
        {
            return kStatus_SDMMC_InvalidVoltage;
        }
    }
    else
    {
        return kStatus_SDMMC_InvalidVoltage;
    }

    /* send relative address ,cmd3*/
    if (kStatus_Success != SDIO_SendRca(card))
    {
        return kStatus_SDMMC_SendRelativeAddressFailed;
    }
    /* select card cmd7 */
    if (kStatus_Success != SDIO_SelectCard(card, true))
    {
        return kStatus_SDMMC_SelectCardFailed;
    }

    /* get card capability */
    if (kStatus_Success != SDIO_GetCardCapability(card, kSDIO_FunctionNum0))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* read common CIS here */
    if (SDIO_ReadCIS(card, kSDIO_FunctionNum0, g_tupleList, SDIO_COMMON_CIS_TUPLE_NUM))
    {
        return kStatus_SDMMC_SDIO_ReadCISFail;
    }

    /* freq and bus width setting */
    if (card->cccrflags & kSDIO_CCCRSupportLowSpeed4Bit)
    {
        /* set to 4bit data bus */
        SDIO_SetDataBusWidth(card, kSDIO_DataBus4Bit);
        HOST_SET_CARD_BUS_WIDTH(card->host.base, kHOST_DATABUSWIDTH4BIT);
    }
    else if (card->cccrflags & kSDIO_CCCRSupportHighSpeed)
    {
        if (kStatus_Success != SDIO_SwitchToHighSpeed(card))
        {
            return kStatus_SDMMC_SDIO_SwitchHighSpeedFail;
        }

        return kStatus_Success;
    }

    /* default mode 25MHZ */
    card->busClock_Hz = HOST_SET_CARD_CLOCK(card->host.base, card->host.sourceClock_Hz, SD_CLOCK_25MHZ);

    return kStatus_Success;
}

status_t SDIO_EnableIOInterrupt(sdio_card_t *card, sdio_func_num_t func, bool enable)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    uint8_t intEn = 0U;

    /* load io interrupt enable register */
    if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOIntEnable, &intEn))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    if (enable)
    {
        /* if already enable , do not need enable again */
        if ((((intEn >> func) & 0x01U) == 0x01U) && (intEn & 0x01U))
        {
            return kStatus_Success;
        }

        /* enable the interrupt and interrupt master */
        intEn |= (1U << func) | 0x01U;
    }
    else
    {
        /* if already disable , do not need enable again */
        if (((intEn >> func) & 0x01U) == 0x00U)
        {
            return kStatus_Success;
        }

        /* disable the interrupt, don't disable the interrupt master here */
        intEn &= ~(1U << func);
    }

    /* write to register */
    if (kStatus_Success != SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOIntEnable, &intEn, true))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDIO_EnableIO(sdio_card_t *card, sdio_func_num_t func, bool enable)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    uint8_t ioEn = 0U, ioReady = 0U;
    uint32_t i = FSL_SDMMC_MAX_VOLTAGE_RETRIES;

    /* load io enable register */
    if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOEnable, &ioEn))
    {
        return kStatus_SDMMC_TransferFailed;
    }
    /* if already enable/disable , do not need enable/disable again */
    if (((ioEn >> func) & 0x01U) == (enable ? 1U : 0U))
    {
        return kStatus_Success;
    }

    /* enable the io */
    if (enable)
    {
        ioEn |= (1U << func);
    }
    else
    {
        ioEn &= ~(1U << func);
    }

    /* write to register */
    if (kStatus_Success != SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOEnable, &ioEn, true))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* if enable io, need check the IO ready status */
    if (enable)
    {
        while (i--)
        {
            /* wait IO ready */
            if (kStatus_Success != SDIO_IO_Read_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOReady, &ioReady))
            {
                return kStatus_SDMMC_TransferFailed;
            }
            /* check if IO ready */
            if ((ioReady & (1 << func)) != 0U)
            {
                return kStatus_Success;
            }
        }
    }

    return (i == 0U) ? kStatus_Fail : kStatus_Success;
}

status_t SDIO_SelectIO(sdio_card_t *card, sdio_func_num_t func)
{
    assert(card);
    assert(func <= kSDIO_FunctionMemory);

    uint8_t ioSel = func;

    /* write to register */
    if (kStatus_Success != SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegFunctionSelect, &ioSel, true))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDIO_AbortIO(sdio_card_t *card, sdio_func_num_t func)
{
    assert(card);
    assert(func <= kSDIO_FunctionNum7);

    uint8_t ioAbort = func;

    /* write to register */
    if (kStatus_Success != SDIO_IO_Write_Direct(card, kSDIO_FunctionNum0, kSDIO_RegIOAbort, &ioAbort, true))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

void SDIO_DeInit(sdio_card_t *card)
{
    assert(card);
    /* disselect card */
    SDIO_CardReset(card);
    SDIO_SelectCard(card, false);
    HOST_Deinit(&(card->host));
    /* should re-init host */
    card->isHostReady = false;
}
