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

#include <assert.h>
#include <string.h>

#include "fsl_sdspi.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/
#define IS_BLOCK_ACCESS(x) ((x)->flags & kSDSPI_SupportHighCapacityFlag)

/* Card command maximum timeout value */
#define FSL_SDSPI_TIMEOUT (1000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Wait card to be ready state.
 *
 * @param host Host state.
 * @param milliseconds Timeout time in millseconds.
 * @retval kStatus_SDSPI_ExchangeFailed Exchange data over SPI failed.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_WaitReady(sdspi_host_t *host, uint32_t milliseconds);

/*!
 * @brief Calculate CRC7
 *
 * @param buffer Data buffer.
 * @param length Data length.
 * @param crc The orginal crc value.
 * @return Generated CRC7.
 */
static uint32_t SDSPI_GenerateCRC7(uint8_t *buffer, uint32_t length, uint32_t crc);

/*!
 * @brief Send command.
 *
 * @param host Host state.
 * @param command The command to be wrote.
 * @param timeout The timeout value.
 * @retval kStatus_SDSPI_WaitReadyFailed Wait ready failed.
 * @retval kStatus_SDSPI_ExchangeFailed Exchange data over SPI failed.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_Fail Send command failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SendCommand(sdspi_host_t *host, sdspi_command_t *command, uint32_t timeout);

/*!
 * @brief Send GO_IDLE command.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_ExchangeFailed Send timing byte failed.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_GoIdle(sdspi_card_t *card);

/*!
 * @brief Send GET_INTERFACE_CONDITION command.
 *
 * This function checks card interface condition, which includes host supply voltage information and asks the card
 * whether it supports voltage.
 *
 * @param card Card descriptor.
 * @param pattern The check pattern.
 * @param response Buffer to save the command response.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SendInterfaceCondition(sdspi_card_t *card, uint8_t pattern, uint8_t *response);

/*!
 * @brief Send SEND_APPLICATION_COMMAND command.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SendApplicationCmd(sdspi_card_t *card);

/*!
 * @brief Send GET_OPERATION_CONDITION command.
 *
 * @param card Card descriptor.
 * @param argument Operation condition.
 * @param response Buffer to save command response.
 * @retval kStatus_Timeout Timeout.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_ApplicationSendOperationCondition(sdspi_card_t *card, uint32_t argument, uint8_t *response);

/*!
 * @brief Send READ_OCR command to get OCR register content.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_ReadOcr(sdspi_card_t *card);

/*!
 * @brief Send SET_BLOCK_SIZE command.
 *
 * This function sets the block length in bytes for SDSC cards. For SDHC cards, it does not affect memory
 * read or write commands, always 512 bytes fixed block length is used.
 * @param card Card descriptor.
 * @param blockSize Block size.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SetBlockSize(sdspi_card_t *card, uint32_t blockSize);

/*!
 * @brief Read data from card
 *
 * @param host Host state.
 * @param buffer Buffer to save data.
 * @param size The data size to read.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_SDSPI_ExchangeFailed Exchange data over SPI failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_Read(sdspi_host_t *host, uint8_t *buffer, uint32_t size);

/*!
 * @brief Decode CSD register
 *
 * @param card Card descriptor.
 * @param rawCsd Raw CSD register content.
 */
static void SDSPI_DecodeCsd(sdspi_card_t *card, uint8_t *rawCsd);

/*!
 * @brief Send GET-CSD command.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ReadFailed Read data blocks failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SendCsd(sdspi_card_t *card);

/*!
 * @brief Set card to max frequence in normal mode.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SetFrequencyFailed Set frequency failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SetMaxFrequencyNormalMode(sdspi_card_t *card);

/*!
 * @brief Check the capacity of the card
 *
 * @param card Card descriptor.
 */
static void SDSPI_CheckCapacity(sdspi_card_t *card);

/*!
 * @brief Decode raw CID register.
 *
 * @param card Card descriptor.
 * @param rawCid Raw CID register content.
 */
static void SDSPI_DecodeCid(sdspi_card_t *card, uint8_t *rawCid);

/*!
 * @brief Send GET-CID command
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ReadFailed Read data blocks failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SendCid(sdspi_card_t *card);

/*!
 * @brief Decode SCR register.
 *
 * @param card Card descriptor.
 * @param rawScr Raw SCR register content.
 */
static void SDSPI_DecodeScr(sdspi_card_t *card, uint8_t *rawScr);

/*!
 * @brief Send SEND_SCR command.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ReadFailed Read data blocks failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_SendScr(sdspi_card_t *card);

/*!
 * @brief Send STOP_TRANSMISSION command to card to stop ongoing data transferring.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_StopTransmission(sdspi_card_t *card);

/*!
 * @brief Write data to card
 *
 * @param host Host state.
 * @param buffer Data to send.
 * @param size Data size.
 * @param token The data token.
 * @retval kStatus_SDSPI_WaitReadyFailed Card is busy error.
 * @retval kStatus_SDSPI_ExchangeFailed Exchange data over SPI failed.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDSPI_Write(sdspi_host_t *host, uint8_t *buffer, uint32_t size, uint8_t token);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Rate unit(divided by 1000) of transfer speed in non-high-speed mode. */
static const uint32_t g_transferSpeedRateUnit[] = {
    /* 100Kbps, 1Mbps, 10Mbps, 100Mbps*/
    100U, 1000U, 10000U, 100000U,
};

/* Multiplier factor(multiplied by 1000) of transfer speed in non-high-speed mode. */
static const uint32_t g_transferSpeedMultiplierFactor[] = {
    0U, 1000U, 1200U, 1300U, 1500U, 2000U, 2500U, 3000U, 3500U, 4000U, 4500U, 5000U, 5500U, 6000U, 7000U, 8000U,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t SDSPI_WaitReady(sdspi_host_t *host, uint32_t milliseconds)
{
    uint8_t response;
    uint8_t timingByte = 0xFFU; /* The byte need to be sent as read/write data block timing requirement */
    uint32_t startTime;
    uint32_t currentTime;
    uint32_t elapsedTime;

    startTime = host->getCurrentMilliseconds();
    do
    {
        if (kStatus_Success != host->exchange(&timingByte, &response, 1U))
        {
            return kStatus_SDSPI_ExchangeFailed;
        }

        currentTime = host->getCurrentMilliseconds();
        elapsedTime = (currentTime - startTime);
    } while ((response != 0xFFU) && (elapsedTime < milliseconds));

    /* Response 0xFF means card is still busy. */
    if (response != 0xFFU)
    {
        return kStatus_SDSPI_ResponseError;
    }

    return kStatus_Success;
}

static uint32_t SDSPI_GenerateCRC7(uint8_t *buffer, uint32_t length, uint32_t crc)
{
    uint32_t index;

    static const uint8_t crcTable[] = {0x00U, 0x09U, 0x12U, 0x1BU, 0x24U, 0x2DU, 0x36U, 0x3FU,
                                       0x48U, 0x41U, 0x5AU, 0x53U, 0x6CU, 0x65U, 0x7EU, 0x77U};

    while (length)
    {
        index = (((crc >> 3U) & 0x0FU) ^ ((*buffer) >> 4U));
        crc = ((crc << 4U) ^ crcTable[index]);

        index = (((crc >> 3U) & 0x0FU) ^ ((*buffer) & 0x0FU));
        crc = ((crc << 4U) ^ crcTable[index]);

        buffer++;
        length--;
    }

    return (crc & 0x7FU);
}

static status_t SDSPI_SendCommand(sdspi_host_t *host, sdspi_command_t *command, uint32_t timeout)
{
    assert(host);
    assert(command);

    uint8_t buffer[6U];
    uint8_t response;
    uint8_t i;
    uint8_t timingByte = 0xFFU; /* The byte need to be sent as read/write data block timing requirement */

    if ((kStatus_Success != SDSPI_WaitReady(host, timeout)) && (command->index != kSDMMC_GoIdleState))
    {
        return kStatus_SDSPI_WaitReadyFailed;
    }

    /* Send command. */
    buffer[0U] = (command->index | 0x40U);
    buffer[1U] = ((command->argument >> 24U) & 0xFFU);
    buffer[2U] = ((command->argument >> 16U) & 0xFFU);
    buffer[3U] = ((command->argument >> 8U) & 0xFFU);
    buffer[4U] = (command->argument & 0xFFU);
    buffer[5U] = ((SDSPI_GenerateCRC7(buffer, 5U, 0U) << 1U) | 1U);
    if (host->exchange(buffer, NULL, sizeof(buffer)))
    {
        return kStatus_SDSPI_ExchangeFailed;
    }

    /* Wait for the response coming, the left most bit which is transfered first in first response byte is 0 */
    for (i = 0U; i < 9U; i++)
    {
        if (kStatus_Success != host->exchange(&timingByte, &response, 1U))
        {
            return kStatus_SDSPI_ExchangeFailed;
        }

        /* Check if response 0 coming. */
        if (!(response & 0x80U))
        {
            break;
        }
    }
    if (response & 0x80U) /* Max index byte is high means response comming. */
    {
        return kStatus_SDSPI_ResponseError;
    }

    /* Receve all the response content. */
    command->response[0U] = response;
    switch (command->responseType)
    {
        case kSDSPI_ResponseTypeR1:
            break;
        case kSDSPI_ResponseTypeR1b:
            if (kStatus_Success != SDSPI_WaitReady(host, timeout))
            {
                return kStatus_SDSPI_WaitReadyFailed;
            }
            break;
        case kSDSPI_ResponseTypeR2:
            if (kStatus_Success != host->exchange(&timingByte, &(command->response[1U]), 1U))
            {
                return kStatus_SDSPI_ExchangeFailed;
            }
            break;
        case kSDSPI_ResponseTypeR3:
        case kSDSPI_ResponseTypeR7:
            /* Left 4 bytes in response type R3 and R7(total 5 bytes in SPI mode) */
            if (kStatus_Success != host->exchange(&timingByte, &(command->response[1U]), 4U))
            {
                return kStatus_SDSPI_ExchangeFailed;
            }
            break;
        default:
            return kStatus_Fail;
    }

    return kStatus_Success;
}

static status_t SDSPI_GoIdle(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);

    sdspi_host_t *host;
    sdspi_command_t command = {0};
    uint32_t retryCount = 200U;

    host = card->host;
    /* SD card will enter SPI mode if the CS is asserted (negative) during the reception of the reset command (CMD0)
    and the card will be IDLE state. */
    while (retryCount--)
    {
        command.index = kSDMMC_GoIdleState;
        command.responseType = kSDSPI_ResponseTypeR1;
        if ((kStatus_Success == SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT)) &&
            (command.response[0U] == kSDSPI_R1InIdleStateFlag))
        {
            break;
        }
    }

    return kStatus_Success;
}

static status_t SDSPI_SendInterfaceCondition(sdspi_card_t *card, uint8_t pattern, uint8_t *response)
{
    assert(card);
    assert(card->host);

    sdspi_command_t command = {0};
    sdspi_host_t *host;

    host = card->host;
    command.index = kSD_SendInterfaceCondition;
    command.argument = (0x100U | (pattern & 0xFFU));
    command.responseType = kSDSPI_ResponseTypeR7;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    memcpy(response, command.response, sizeof(command.response));

    return kStatus_Success;
}

static status_t SDSPI_SendApplicationCmd(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);

    sdspi_host_t *host;
    sdspi_command_t command = {0};

    host = card->host;
    command.index = kSDMMC_ApplicationCommand;
    command.responseType = kSDSPI_ResponseTypeR1;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    if ((command.response[0U]) && (!(command.response[0U] & kSDSPI_R1InIdleStateFlag)))
    {
        return kStatus_SDSPI_ResponseError;
    }

    return kStatus_Success;
}

static status_t SDSPI_ApplicationSendOperationCondition(sdspi_card_t *card, uint32_t argument, uint8_t *response)
{
    assert(card);
    assert(card->host);
    assert(response);

    sdspi_command_t command = {0};
    uint32_t startTime;
    uint32_t currentTime;
    uint32_t elapsedTime = 0U;
    sdspi_host_t *host;

    host = card->host;
    command.index = kSD_ApplicationSendOperationCondition;
    command.argument = argument;
    command.responseType = kSDSPI_ResponseTypeR1;
    startTime = host->getCurrentMilliseconds();
    do
    {
        if (kStatus_Success == SDSPI_SendApplicationCmd(card))
        {
            if (kStatus_Success == SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
            {
                if (!command.response[0U])
                {
                    break;
                }
            }
        }

        currentTime = host->getCurrentMilliseconds();
        elapsedTime = (currentTime - startTime);
    } while (elapsedTime < FSL_SDSPI_TIMEOUT);

    if (response)
    {
        memcpy(response, command.response, sizeof(command.response));
    }
    if (elapsedTime < FSL_SDSPI_TIMEOUT)
    {
        return kStatus_Success;
    }

    return kStatus_Timeout;
}

static status_t SDSPI_ReadOcr(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);

    uint32_t i;
    sdspi_host_t *host;
    sdspi_command_t command = {0};

    host = card->host;
    command.index = kSDMMC_ReadOcr;
    command.responseType = kSDSPI_ResponseTypeR3;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    if (command.response[0U])
    {
        return kStatus_SDSPI_ResponseError;
    }

    /* Switch the bytes sequence. All register's content is transferred from highest byte to lowest byte. */
    card->ocr = 0U;
    for (i = 4U; i > 0U; i--)
    {
        card->ocr |= (uint32_t)command.response[i] << ((4U - i) * 8U);
    }

    return kStatus_Success;
}

static status_t SDSPI_SetBlockSize(sdspi_card_t *card, uint32_t blockSize)
{
    assert(card);
    assert(card->host);

    sdspi_command_t command = {0};
    sdspi_host_t *host;

    host = card->host;
    command.index = kSDMMC_SetBlockLength;
    command.argument = blockSize;
    command.responseType = kSDSPI_ResponseTypeR1;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    return kStatus_Success;
}

static status_t SDSPI_Read(sdspi_host_t *host, uint8_t *buffer, uint32_t size)
{
    assert(host);
    assert(host->exchange);
    assert(buffer);
    assert(size);

    uint32_t startTime;
    uint32_t currentTime;
    uint32_t elapsedTime;
    uint8_t response, i;
    uint8_t timingByte = 0xFFU; /* The byte need to be sent as read/write data block timing requirement */

    memset(buffer, 0xFFU, size);

    /* Wait data token comming */
    startTime = host->getCurrentMilliseconds();
    do
    {
        if (kStatus_Success != host->exchange(&timingByte, &response, 1U))
        {
            return kStatus_SDSPI_ExchangeFailed;
        }

        currentTime = host->getCurrentMilliseconds();
        elapsedTime = (currentTime - startTime);
    } while ((response == 0xFFU) && (elapsedTime < 100U));

    /* Check data token and exchange data. */
    if (response != kSDSPI_DataTokenBlockRead)
    {
        return kStatus_SDSPI_ResponseError;
    }
    if (host->exchange(buffer, buffer, size))
    {
        return kStatus_SDSPI_ExchangeFailed;
    }

    /* Get 16 bit CRC */
    for (i = 0U; i < 2U; i++)
    {
        if (kStatus_Success != host->exchange(&timingByte, &response, 1U))
        {
            return kStatus_SDSPI_ExchangeFailed;
        }
    }

    return kStatus_Success;
}

static void SDSPI_DecodeCsd(sdspi_card_t *card, uint8_t *rawCsd)
{
    assert(rawCsd);
    assert(card);

    sd_csd_t *csd;

    csd = &(card->csd);
    csd->csdStructure = (rawCsd[0U] >> 6U);
    csd->dataReadAccessTime1 = rawCsd[1U];
    csd->dataReadAccessTime2 = rawCsd[2U];
    csd->transferSpeed = rawCsd[3U];
    csd->cardCommandClass = (((uint32_t)rawCsd[4U] << 4U) | ((uint32_t)rawCsd[5U] >> 4U));
    csd->readBlockLength = ((rawCsd)[5U] & 0xFU);
    if (rawCsd[6U] & 0x80U)
    {
        csd->flags |= kSD_CsdReadBlockPartialFlag;
    }
    if (rawCsd[6U] & 0x40U)
    {
        csd->flags |= kSD_CsdWriteBlockMisalignFlag;
    }
    if (rawCsd[6U] & 0x20U)
    {
        csd->flags |= kSD_CsdReadBlockMisalignFlag;
    }
    if (rawCsd[6U] & 0x10U)
    {
        csd->flags |= kSD_CsdDsrImplementedFlag;
    }

    /* Some fileds is different when csdStructure is different. */
    if (csd->csdStructure == 0U) /* Decode the bits when CSD structure is version 1.0 */
    {
        csd->deviceSize =
            ((((uint32_t)rawCsd[6] & 0x3U) << 10U) | ((uint32_t)rawCsd[7U] << 2U) | ((uint32_t)rawCsd[8U] >> 6U));
        csd->readCurrentVddMin = ((rawCsd[8U] >> 3U) & 7U);
        csd->readCurrentVddMax = (rawCsd[8U] >> 7U);
        csd->writeCurrentVddMin = ((rawCsd[9U] >> 5U) & 7U);
        csd->writeCurrentVddMax = (rawCsd[9U] >> 2U);
        csd->deviceSizeMultiplier = (((rawCsd[9U] & 3U) << 1U) | (rawCsd[10U] >> 7U));
        card->blockCount = (csd->deviceSize + 1U) << (csd->deviceSizeMultiplier + 2U);
        card->blockSize = (1U << (csd->readBlockLength));
        if (card->blockSize != FSL_SDSPI_DEFAULT_BLOCK_SIZE)
        {
            card->blockCount = (card->blockCount * card->blockSize);
            card->blockSize = FSL_SDSPI_DEFAULT_BLOCK_SIZE;
            card->blockCount = (card->blockCount / card->blockSize);
        }
    }
    else if (csd->csdStructure == 1U) /* Decode the bits when CSD structure is version 2.0 */
    {
        card->blockSize = FSL_SDSPI_DEFAULT_BLOCK_SIZE;
        csd->deviceSize =
            ((((uint32_t)rawCsd[7U] & 0x3FU) << 16U) | ((uint32_t)rawCsd[8U] << 8U) | ((uint32_t)rawCsd[9U]));
        if (csd->deviceSize >= 0xFFFFU)
        {
            card->flags |= kSDSPI_SupportSdxcFlag;
        }
        card->blockCount = ((csd->deviceSize + 1U) * 1024U);
    }
    else
    {
    }

    if ((rawCsd[10U] >> 6U) & 1U)
    {
        csd->flags |= kSD_CsdEraseBlockEnabledFlag;
    }
    csd->eraseSectorSize = (((rawCsd[10U] & 0x3FU) << 1U) | (rawCsd[11U] >> 7U));
    csd->writeProtectGroupSize = (rawCsd[11U] & 0x7FU);
    if (rawCsd[12U] >> 7U)
    {
        csd->flags |= kSD_CsdWriteProtectGroupEnabledFlag;
    }
    csd->writeSpeedFactor = ((rawCsd[12U] >> 2U) & 7U);
    csd->writeBlockLength = (((rawCsd[12U] & 3U) << 2U) | (rawCsd[13U] >> 6U));
    if ((rawCsd[13U] >> 5U) & 1U)
    {
        csd->flags |= kSD_CsdWriteBlockPartialFlag;
    }
    if (rawCsd[14U] >> 7U)
    {
        csd->flags |= kSD_CsdFileFormatGroupFlag;
    }
    if ((rawCsd[14U] >> 6U) & 1U)
    {
        csd->flags |= kSD_CsdCopyFlag;
    }
    if ((rawCsd[14U] >> 5U) & 1U)
    {
        csd->flags |= kSD_CsdPermanentWriteProtectFlag;
    }
    if ((rawCsd[14U] >> 4U) & 1U)
    {
        csd->flags |= kSD_CsdTemporaryWriteProtectFlag;
    }
    csd->fileFormat = ((rawCsd[14U] >> 2U) & 3U);
}

static status_t SDSPI_SendCsd(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);

    sdspi_command_t command = {0};
    sdspi_host_t *host;

    host = card->host;
    command.index = kSDMMC_SendCsd;
    command.responseType = kSDSPI_ResponseTypeR1;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    if (kStatus_Success != SDSPI_Read(host, card->rawCsd, sizeof(card->rawCsd)))
    {
        return kStatus_SDSPI_ReadFailed;
    }

    SDSPI_DecodeCsd(card, card->rawCsd);

    return kStatus_Success;
}

static status_t SDSPI_SetMaxFrequencyNormalMode(sdspi_card_t *card)
{
    uint32_t maxFrequency;

    /* Calculate max frequency card supported in non-high-speed mode. */
    maxFrequency = g_transferSpeedRateUnit[SD_RD_TRANSFER_SPEED_RATE_UNIT(card->csd)] *
                   g_transferSpeedMultiplierFactor[SD_RD_TRANSFER_SPEED_TIME_VALUE(card->csd)];
    if (maxFrequency > card->host->busBaudRate)
    {
        maxFrequency = card->host->busBaudRate;
    }

    if (kStatus_Success != card->host->setFrequency(maxFrequency))
    {
        return kStatus_SDSPI_SetFrequencyFailed;
    }

    return kStatus_Success;
}

static void SDSPI_CheckCapacity(sdspi_card_t *card)
{
    uint32_t deviceSize;
    uint32_t deviceSizeMultiplier;
    uint32_t readBlockLength;

    if (card->csd.csdStructure)
    {
        /* SD CSD structure v2.xx */
        deviceSize = card->csd.deviceSize;
        if (deviceSize >= 0xFFFFU) /* Bigger than 32GB */
        {
            /* extended capacity */
            card->flags |= kSDSPI_SupportSdxcFlag;
        }
        else
        {
            card->flags |= kSDSPI_SupportSdhcFlag;
        }
        deviceSizeMultiplier = 10U;
        deviceSize += 1U;
        readBlockLength = 9U;
    }
    else
    {
        /* SD CSD structure v1.xx */
        deviceSize = (card->csd.deviceSize + 1U);
        deviceSizeMultiplier = (card->csd.deviceSizeMultiplier + 2U);
        readBlockLength = card->csd.readBlockLength;
        /* Card maximum capacity is 2GB when CSD structure version is 1.0 */
        card->flags |= kSDSPI_SupportSdscFlag;
    }
    if (readBlockLength != 9U)
    {
        /* Force to use 512-byte length block */
        deviceSizeMultiplier += (readBlockLength - 9U);
        readBlockLength = 9U;
    }

    card->blockSize = (1U << readBlockLength);
    card->blockCount = (deviceSize << deviceSizeMultiplier);
}

static void SDSPI_DecodeCid(sdspi_card_t *card, uint8_t *rawCid)
{
    assert(card);
    assert(rawCid);

    sd_cid_t *cid = &(card->cid);
    cid->manufacturerID = rawCid[0U];
    cid->applicationID = (((uint32_t)rawCid[1U] << 8U) | (uint32_t)(rawCid[2U]));
    memcpy(cid->productName, &rawCid[3U], SD_PRODUCT_NAME_BYTES);
    cid->productVersion = rawCid[8U];
    cid->productSerialNumber = (((uint32_t)rawCid[9U] << 24U) | ((uint32_t)rawCid[10U] << 16U) |
                                ((uint32_t)rawCid[11U] << 8U) | ((uint32_t)rawCid[12U]));
    cid->manufacturerData = ((((uint32_t)rawCid[13U] & 0x0FU) << 8U) | ((uint32_t)rawCid[14U]));
}

static status_t SDSPI_SendCid(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);

    sdspi_command_t command = {0};
    sdspi_host_t *host;

    host = card->host;
    command.index = kSDMMC_SendCid;
    command.responseType = kSDSPI_ResponseTypeR1;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    if (kStatus_Success != (SDSPI_Read(host, card->rawCid, sizeof(card->rawCid))))
    {
        return kStatus_SDSPI_ReadFailed;
    }

    SDSPI_DecodeCid(card, card->rawCid);

    return kStatus_Success;
}

static void SDSPI_DecodeScr(sdspi_card_t *card, uint8_t *rawScr)
{
    assert(card);
    assert(rawScr);

    sd_scr_t *scr = &(card->scr);
    scr->scrStructure = ((rawScr[0U] & 0xF0U) >> 4U);
    scr->sdSpecification = (rawScr[0U] & 0x0FU);
    if (rawScr[1U] & 0x80U)
    {
        scr->flags |= kSD_ScrDataStatusAfterErase;
    }
    scr->sdSecurity = ((rawScr[1U] & 0x70U) >> 4U);
    scr->sdBusWidths = (rawScr[1U] & 0x0FU);
    if (rawScr[2U] & 0x80U)
    {
        scr->flags |= kSD_ScrSdSpecification3;
    }
    scr->extendedSecurity = ((rawScr[2U] & 0x78U) >> 3U);
    scr->commandSupport = (rawScr[3U] & 0x03U);
    scr->reservedForManufacturer = (((uint32_t)rawScr[4U] << 24U) | ((uint32_t)rawScr[5U] << 16U) |
                                    ((uint32_t)rawScr[6U] << 8U) | (uint32_t)rawScr[7U]);
}

static status_t SDSPI_SendScr(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);

    sdspi_command_t command = {0};
    sdspi_host_t *host;

    host = card->host;
    if (kStatus_Success != SDSPI_SendApplicationCmd(card))
    {
        return kStatus_SDSPI_SendApplicationCommandFailed;
    }

    command.index = kSD_ApplicationSendScr;
    command.responseType = kSDSPI_ResponseTypeR1;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    if (kStatus_Success != (SDSPI_Read(host, card->rawScr, sizeof(card->rawScr))))
    {
        return kStatus_SDSPI_ReadFailed;
    }

    SDSPI_DecodeScr(card, card->rawScr);

    return kStatus_Success;
}

static status_t SDSPI_StopTransmission(sdspi_card_t *card)
{
    sdspi_command_t command = {0};
    sdspi_host_t *host;

    host = card->host;
    command.index = kSDMMC_StopTransmission;
    command.responseType = kSDSPI_ResponseTypeR1b;
    if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_SendCommandFailed;
    }

    return kStatus_Success;
}

static status_t SDSPI_Write(sdspi_host_t *host, uint8_t *buffer, uint32_t size, uint8_t token)
{
    assert(host);
    assert(host->exchange);

    uint8_t response;
    uint8_t i;
    uint8_t timingByte = 0xFFU; /* The byte need to be sent as read/write data block timing requirement */

    if (kStatus_Success != SDSPI_WaitReady(host, FSL_SDSPI_TIMEOUT))
    {
        return kStatus_SDSPI_WaitReadyFailed;
    }

    /* Write data token. */
    if (host->exchange(&token, NULL, 1U))
    {
        return kStatus_SDSPI_ExchangeFailed;
    }
    if (token == kSDSPI_DataTokenStopTransfer)
    {
        return kStatus_Success;
    }

    if ((!size) || (!buffer))
    {
        return kStatus_InvalidArgument;
    }

    /* Write data. */
    if (kStatus_Success != host->exchange(buffer, NULL, size))
    {
        return kStatus_SDSPI_ExchangeFailed;
    }

    /* Get the last two bytes CRC */
    for (i = 0U; i < 2U; i++)
    {
        if (host->exchange(&timingByte, NULL, 1U))
        {
            return kStatus_SDSPI_ExchangeFailed;
        }
    }

    /* Get the response token. */
    if (host->exchange(&timingByte, &response, 1U))
    {
        return kStatus_SDSPI_ExchangeFailed;
    }
    if ((response & SDSPI_DATA_RESPONSE_TOKEN_MASK) != kSDSPI_DataResponseTokenAccepted)
    {
        return kStatus_SDSPI_ResponseError;
    }

    return kStatus_Success;
}

status_t SDSPI_Init(sdspi_card_t *card)
{
    assert(card);
    assert(card->host);
    assert(card->host->setFrequency);
    assert(card->host->exchange);
    assert(card->host->getCurrentMilliseconds);

    sdspi_host_t *host;
    uint32_t applicationCommand41Argument = 0U;
    uint32_t startTime;
    uint32_t currentTime;
    uint32_t elapsedTime;
    uint8_t response[5U];
    uint8_t applicationCommand41Response[5U];
    bool likelySdV1 = false;

    host = card->host;
    /* Card must be initialized in 400KHZ. */
    if (host->setFrequency(SDMMC_CLOCK_400KHZ))
    {
        return kStatus_SDSPI_SetFrequencyFailed;
    }

    /* Reset the card by CMD0. */
    if (kStatus_Success != SDSPI_GoIdle(card))
    {
        return kStatus_SDSPI_GoIdleFailed;
    }

    /* Check the card's supported interface condition. */
    if (kStatus_Success != SDSPI_SendInterfaceCondition(card, 0xAAU, response))
    {
        likelySdV1 = true;
    }
    else if ((response[3U] == 0x1U) || (response[4U] == 0xAAU))
    {
        applicationCommand41Argument |= kSD_OcrHostCapacitySupportFlag;
    }
    else
    {
        return kStatus_SDSPI_SendInterfaceConditionFailed;
    }

    /* Set card's interface condition according to host's capability and card's supported interface condition */
    startTime = host->getCurrentMilliseconds();
    do
    {
        if (kStatus_Success !=
            SDSPI_ApplicationSendOperationCondition(card, applicationCommand41Argument, applicationCommand41Response))
        {
            return kStatus_SDSPI_SendOperationConditionFailed;
        }

        currentTime = host->getCurrentMilliseconds();
        elapsedTime = (currentTime - startTime);
        if (elapsedTime > 500U)
        {
            return kStatus_Timeout;
        }

        if (!applicationCommand41Response[0U])
        {
            break;
        }
    } while (applicationCommand41Response[0U] & kSDSPI_R1InIdleStateFlag);

    if (!likelySdV1)
    {
        if (kStatus_Success != SDSPI_ReadOcr(card))
        {
            return kStatus_SDSPI_ReadOcrFailed;
        }
        if (card->ocr & kSD_OcrCardCapacitySupportFlag)
        {
            card->flags |= kSDSPI_SupportHighCapacityFlag;
        }
    }

    /* Force to use 512-byte length block, no matter which version.  */
    if (kStatus_Success != SDSPI_SetBlockSize(card, 512U))
    {
        return kStatus_SDSPI_SetBlockSizeFailed;
    }
    if (kStatus_Success != SDSPI_SendCsd(card))
    {
        return kStatus_SDSPI_SendCsdFailed;
    }

    /* Set to max frequency according to the max frequency information in CSD register. */
    SDSPI_SetMaxFrequencyNormalMode(card);

    /* Save capacity, read only attribute and CID, SCR registers. */
    SDSPI_CheckCapacity(card);
    SDSPI_CheckReadOnly(card);
    if (kStatus_Success != SDSPI_SendCid(card))
    {
        return kStatus_SDSPI_SendCidFailed;
    }
    if (kStatus_Success != SDSPI_SendScr(card))
    {
        return kStatus_SDSPI_SendCidFailed;
    }

    return kStatus_Success;
}

void SDSPI_Deinit(sdspi_card_t *card)
{
    assert(card);

    memset(card, 0, sizeof(sdspi_card_t));
}

bool SDSPI_CheckReadOnly(sdspi_card_t *card)
{
    assert(card);

    if ((card->csd.flags & kSD_CsdPermanentWriteProtectFlag) || (card->csd.flags & kSD_CsdTemporaryWriteProtectFlag))
    {
        return true;
    }

    return false;
}

status_t SDSPI_ReadBlocks(sdspi_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    assert(card);
    assert(card->host);
    assert(buffer);
    assert(blockCount);

    uint32_t offset;
    uint32_t i;
    sdspi_command_t command = {0};
    sdspi_host_t *host;

    offset = startBlock;
    if (!IS_BLOCK_ACCESS(card))
    {
        offset *= card->blockSize;
    }

    /* Send command and reads data. */
    host = card->host;
    command.argument = offset;
    command.responseType = kSDSPI_ResponseTypeR1;
    if (blockCount == 1U)
    {
        command.index = kSDMMC_ReadSingleBlock;
        if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
        {
            return kStatus_SDSPI_SendCommandFailed;
        }

        if (kStatus_Success != SDSPI_Read(host, buffer, card->blockSize))
        {
            return kStatus_SDSPI_ReadFailed;
        }
    }
    else
    {
        command.index = kSDMMC_ReadMultipleBlock;
        if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
        {
            return kStatus_SDSPI_SendCommandFailed;
        }

        for (i = 0U; i < blockCount; i++)
        {
            if (kStatus_Success != SDSPI_Read(host, buffer, card->blockSize))
            {
                return kStatus_SDSPI_ReadFailed;
            }
            buffer += card->blockSize;
        }

        /* Write stop transmission command after the last data block. */
        if (kStatus_Success != SDSPI_StopTransmission(card))
        {
            return kStatus_SDSPI_StopTransmissionFailed;
        }
    }

    return kStatus_Success;
}

status_t SDSPI_WriteBlocks(sdspi_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    assert(card);
    assert(card->host);
    assert(buffer);
    assert(blockCount);

    uint32_t offset;
    uint32_t i;
    sdspi_host_t *host;
    sdspi_command_t command = {0};

    if (SDSPI_CheckReadOnly(card))
    {
        return kStatus_SDSPI_WriteProtected;
    }

    offset = startBlock;
    if (!IS_BLOCK_ACCESS(card))
    {
        offset *= card->blockSize;
    }

    /* Send command and writes data. */
    host = card->host;
    if (blockCount == 1U)
    {
        command.index = kSDMMC_WriteSingleBlock;
        command.argument = offset;
        command.responseType = kSDSPI_ResponseTypeR1;
        if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
        {
            return kStatus_SDSPI_SendCommandFailed;
        }

        if (command.response[0U])
        {
            return kStatus_SDSPI_ResponseError;
        }

        if (kStatus_Success != SDSPI_Write(host, buffer, card->blockSize, kSDSPI_DataTokenSingleBlockWrite))
        {
            return kStatus_SDSPI_WriteFailed;
        }
    }
    else
    {
#if defined FSL_SDSPI_ENABLE_PRE_ERASE_ON_WRITE
        /* Pre-erase before writing data */
        if (kStatus_Success != SDSPI_SendApplicationCmd(card))
        {
            return kStatus_SDSPI_SendApplicationCommandFailed;
        }

        command.index = kSDAppSetWrBlkEraseCount;
        command.argument = blockCount;
        command.responseType = kSDSPI_ResponseTypeR1;
        if (kStatus_Success != SDSPI_SendCommand(host->base, &command, FSL_SDSPI_TIMEOUT))
        {
            return kStatus_SDSPI_SendCommandFailed;
        }

        if (req->response[0U])
        {
            return kStatus_SDSPI_ResponseError;
        }
#endif

        memset(&command, 0U, sizeof(sdspi_command_t));
        command.index = kSDMMC_WriteMultipleBlock;
        command.argument = offset;
        command.responseType = kSDSPI_ResponseTypeR1;
        if (kStatus_Success != SDSPI_SendCommand(host, &command, FSL_SDSPI_TIMEOUT))
        {
            return kStatus_SDSPI_SendCommandFailed;
        }

        if (command.response[0U])
        {
            return kStatus_SDSPI_ResponseError;
        }

        for (i = 0U; i < blockCount; i++)
        {
            if (kStatus_Success != SDSPI_Write(host, buffer, card->blockSize, kSDSPI_DataTokenMultipleBlockWrite))
            {
                return kStatus_SDSPI_WriteFailed;
            }
            buffer += card->blockSize;
        }
        if (kStatus_Success != SDSPI_Write(host, 0U, 0U, kSDSPI_DataTokenStopTransfer))
        {
            return kStatus_SDSPI_WriteFailed;
        }

        /* Wait the card programming end. */
        if (kStatus_Success != SDSPI_WaitReady(host, FSL_SDSPI_TIMEOUT))
        {
            return kStatus_SDSPI_WaitReadyFailed;
        }
    }

    return kStatus_Success;
}
