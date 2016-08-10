/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#include <stdio.h>
#include <string.h>
#include "fsl_os_abstraction.h"

#include "fsl_sdmmc_card.h"
#include "fsl_sdcard_spi.h"

/* rate unit is divided by 1000 */
static const uint32_t g_transpeedru[] =
{
  /* 100Kbps, 1Mbps, 10Mbps, 100Mbps*/
    100, 1000, 10000, 100000,
};

/* time value multiplied by 1000 */
static const uint32_t g_transpeedtv[] =
{
       0, 1000, 1200, 1300,
    1500, 2000, 2500, 3000,
    3500, 4000, 4500, 5000,
    5500, 6000, 7000, 8000,
};

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_GenerateCRC7
 * Description: calculate CRC7
 *
 *END*********************************************************************/
static uint32_t SDSPI_DRV_GenerateCRC7(uint8_t *buffer,
                                      uint32_t length,
                                      uint32_t crc)
{
    uint32_t index;

    static const uint8_t crcTable[] = {
        0x00, 0x09, 0x12, 0x1B, 0x24, 0x2D, 0x36, 0x3F,
        0x48, 0x41, 0x5A, 0x53, 0x6C, 0x65, 0x7E, 0x77
    };

    while (length)
    {
        index = ((crc >> 3) & 0x0F) ^ ((*buffer) >> 4);
        crc = (crc << 4) ^ crcTable[index];

        index = ((crc >> 3) & 0x0F) ^ ((*buffer) & 0x0F);
        crc = (crc << 4) ^ crcTable[index];

        buffer++;
        length--;
    }

    return (crc & 0x7F);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_WaitReady
 * Description: wait ready 
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_WaitReady(sdspi_spi_t *spi)
{
    uint8_t response;
    uint32_t startTime, elapsedTime;

    startTime = OSA_TimeGetMsec();
    do
    {
        response = spi->ops->sendWord(spi, 0xFF);
        elapsedTime = OSA_TimeGetMsec() - startTime;
    } while ((response != 0xFF) && elapsedTime < 500);

    if (response != 0xFF)
    {
        return kStatus_SDSPI_CardIsBusyError;
    }

    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_SendCommand
 * Description: send command
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_SendCommand(sdspi_spi_t *spi,
                                            sdspi_request_t *req,
                                            uint32_t timeout)
{
    uint8_t buffer[6];
    uint8_t response;
    uint8_t i;
    sdspi_status_t result = kStatus_SDSPI_NoError;

    assert(spi);
    assert(req);

    result = SDSPI_DRV_WaitReady(spi);
    if ((result == kStatus_SDSPI_CardIsBusyError)
            && (req->cmdIndex != kGoIdleState))
    {
        return result;
    }

    buffer[0] = SDSPI_MAKE_CMD(req->cmdIndex);
    buffer[1] = req->argument >> 24 & 0xFF;
    buffer[2] = req->argument >> 16 & 0xFF;
    buffer[3] = req->argument >> 8 & 0xFF;
    buffer[4] = req->argument & 0xFF;
    buffer[5] = (SDSPI_DRV_GenerateCRC7(buffer, 5, 0) << 1) | 1;

    if (spi->ops->exchange(spi, buffer, NULL, sizeof(buffer)))
    {
        return kStatus_SDSPI_TransferFailed;
    }

    if (req->cmdIndex == kStopTransmission)
    {
        spi->ops->sendWord(spi, 0xFF);
    }
    /* Wait for the response coming, the left most bit which is transfered first in response is 0 */
    for (i = 0; i < 9; i++)
    {
        response = spi->ops->sendWord(spi, 0xFF);
        if (!(response & 0x80))
        {
            break;
        }
    }

    if ((response & 0x80))
    {
        return kStatus_SDSPI_Failed;
    }

    req->response[0] = response;
    switch(req->respType)
    {
        case kSdSpiRespTypeR1:
            break;
        case kSdSpiRespTypeR1b:
        {
            uint8_t busy = 0;
            uint32_t startTime, elapsedTime;
            startTime = OSA_TimeGetMsec();
            while (busy != 0xFF)
            {
                busy = spi->ops->sendWord(spi, 0xFF);
                elapsedTime = OSA_TimeGetMsec() - startTime;
                if (elapsedTime > timeout)
                {
                    break;
                }
            }
            if (busy != 0xFF)
            {
                result = kStatus_SDSPI_CardIsBusyError;
            }
            break;
        }
        case kSdSpiRespTypeR2:
            req->response[1] = spi->ops->sendWord(spi, 0xFF);
            break;
        case kSdSpiRespTypeR3:
        case kSdSpiRespTypeR7:
        default:
            for (i = 1; i <= 4; i++)/* R7 has total 5 bytes in SPI mode. */
            {
                req->response[i] = spi->ops->sendWord(spi, 0xFF);
            }
            break;
    }


    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_GoIdle
 * Description: send CMD0
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_GoIdle(sdspi_spi_t *spi, sdspi_card_t *card)
{
    uint32_t i, j;
    sdspi_request_t *req;
    assert(card);

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    /*
     * SD card will enter SPI mode if the CS is asserted (negative) during the
     * reception of the reset command (CMD0) and the card is in IDLE state.
     */
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 10; j++)
        {
            spi->ops->sendWord(spi, 0xFF);
        }

        req->cmdIndex = kGoIdleState;
        req->respType = kSdSpiRespTypeR1;
        if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }

        if (req->response[0] == SDMMC_SPI_R1_IN_IDLE_STATE)
        {
            break;
        }
    }

    if (req->response[0] != SDMMC_SPI_R1_IN_IDLE_STATE)
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }

    OSA_MemFree(req);
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_SendApplicationCmd
 * Description: send application command to card
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_SendApplicationCmd(sdspi_spi_t *spi)
{
    sdspi_request_t *req;

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    req->cmdIndex = kAppCmd;
    req->respType = kSdSpiRespTypeR1;
    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }

    if (req->response[0] && !(req->response[0] & SDMMC_SPI_R1_IN_IDLE_STATE))
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }

    OSA_MemFree(req);
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_AppSendOpCond
 * Description: Get the card to send its operating condition.
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_AppSendOpCond(sdspi_spi_t *spi,
                                              sdspi_card_t *card,
                                              uint32_t argument,
                                              uint8_t *response)
{
    sdspi_request_t *req;
    uint32_t startTime, elapsedTime = 0;
    assert(card);

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    req->cmdIndex = kSdAppSendOpCond;
    req->argument = argument;
    req->respType = kSdSpiRespTypeR1;

    startTime = OSA_TimeGetMsec();
    do
    {
        if (kStatus_SDSPI_NoError == SDSPI_DRV_SendApplicationCmd(spi))
        {
            if (kStatus_SDSPI_NoError == SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
            {
                if (!req->response[0])
                {
                    break;
                }
            }
        }
        elapsedTime = OSA_TimeGetMsec() - startTime;
    } while (elapsedTime < 1000);

    if (response)
    {
        memcpy(response, req->response, sizeof(req->response));
    }
    OSA_MemFree(req);

    if (elapsedTime < 1000)
    {
        return kStatus_SDSPI_NoError;
    }
    return kStatus_SDSPI_TimeoutError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_SendIfCond
 * Description: check card interface condition, which includes host supply
 * voltage information and asks the card whether card supports voltage.
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_SendIfCond(sdspi_spi_t *spi,
                                           sdspi_card_t *card,
                                           uint8_t pattern,
                                           uint8_t *response)
{
    sdspi_request_t *req;

    assert(card);
    assert(response);

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    req->cmdIndex = kSdSendIfCond;
    req->argument = 0x100 | (pattern & 0xFF);
    req->respType = kSdSpiRespTypeR7;
    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }

    memcpy(response, req->response, sizeof(req->response));

    OSA_MemFree(req);
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_ReadOcr
 * Description: Get OCR register from card
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_ReadOcr(sdspi_spi_t *spi, sdspi_card_t *card)
{
    uint32_t i;
    sdspi_request_t *req;
    assert(card);

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }
    req->cmdIndex = kReadOcr;
    req->respType = kSdSpiRespTypeR3;
    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }
    if (req->response[0])
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }

    card->ocr = 0;
    for (i = 4; i > 0; i--)
    {
        card->ocr |= (uint32_t) req->response[i] << ((4 - i) * 8);
    }

    OSA_MemFree(req);
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_Write
 * Description: write data to card
 *
 *END*********************************************************************/
static uint32_t SDSPI_DRV_Write(sdspi_spi_t *spi, uint8_t *buffer, uint32_t size, uint8_t token)
{
    uint8_t response;
    assert(spi);
    assert(spi->ops);
    assert(spi->ops->exchange);
    
    if (SDSPI_DRV_WaitReady(spi) != kStatus_SDSPI_NoError)
    {
        return 0;
    }

    spi->ops->sendWord(spi, token);

    if (token == SDMMC_SPI_DT_STOP_TRANSFER)
    {
        return size;
    }

    assert(size);
    assert(buffer);

    if (spi->ops->exchange(spi, buffer, NULL, size))
    {
        return 0;
    }

    /* Send CRC */
    spi->ops->sendWord(spi, 0xFF);
    spi->ops->sendWord(spi, 0xFF);

    response = spi->ops->sendWord(spi, 0xFF);
    if ((response & SDMMC_SPI_DR_MASK) != SDMMC_SPI_DR_ACCEPTED)
    {
        return 0;
    }
    return size;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_Read
 * Description: read data from card
 *
 *END*********************************************************************/
static uint32_t SDSPI_DRV_Read(sdspi_spi_t *spi, uint8_t *buffer, uint32_t size)
{
    uint32_t startTime, elapsedTime;
    uint8_t response;
    assert(spi);
    assert(spi->ops);
    assert(spi->ops->exchange);
    assert(buffer);
    assert(size);
    memset(buffer, 0xFF, size);
    startTime = OSA_TimeGetMsec();
    do
    {
        response = spi->ops->sendWord(spi, 0xFF);
        elapsedTime = OSA_TimeGetMsec() - startTime;
    } while ((response == 0xFF) && elapsedTime < 100);

    if (response != SDMMC_SPI_DT_START_SINGLE_BLK)
    {
        return 0;
    }

    if (spi->ops->exchange(spi, buffer, buffer, size))
    {
        return 0;
    }

    spi->ops->sendWord(spi, 0xFF);
    spi->ops->sendWord(spi, 0xFF);

    return size;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_SendCsd
 * Description: get CSD register from card
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_SendCsd(sdspi_spi_t *spi, sdspi_card_t *card)
{
    sdspi_request_t *req;
    assert(card);

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    req->cmdIndex = kSendCsd;
    req->respType = kSdSpiRespTypeR1;
    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }
    OSA_MemFree(req);

    if (sizeof(card->rawCsd) !=
            (SDSPI_DRV_Read(spi, card->rawCsd, sizeof(card->rawCsd))))
    {
        return kStatus_SDSPI_Failed;
    }

    /* No start single block token if found */
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_SetBlockSize
 * Description:  set the block length in bytes for SDSC cards. For SDHC cards,
 * it does not affect memory read or write commands, always 512 bytes fixed
 * block length is used.
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_SetBlockSize(sdspi_spi_t *spi, uint32_t blockSize)
{
    sdspi_request_t *req = 0;

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }
    req->cmdIndex = kSetBlockLen;
    req->argument = blockSize;
    req->respType = kSdSpiRespTypeR1;

    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        req = NULL;
        return kStatus_SDSPI_Failed;
    }

    OSA_MemFree(req);
    req = NULL;
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_CheckCapacity
 * Description: check card capacity of the card
 *
 *END*********************************************************************/
static void SDSPI_DRV_CheckCapacity(sdspi_card_t *card)
{
    uint32_t cSize, cSizeMult, readBlkLen;

    if (SDMMC_CSD_CSDSTRUCTURE_VERSION(card->rawCsd))
    {
        /* SD CSD structure v2.xx */
        cSize = SDV20_CSD_CSIZE(card->rawCsd);
        if (cSize >= 0xFFFF)
        {
            /* extended capacity */
            card->caps |= SDSPI_CAPS_SDXC;
        }
        else
        {
            card->caps |= SDSPI_CAPS_SDHC;
        }
        cSizeMult = 10;
        cSize += 1;
        readBlkLen = 9;
    }
    else
    {
        /* SD CSD structure v1.xx */
        cSize = SDMMC_CSD_CSIZE(card->rawCsd) + 1;
        cSizeMult = SDMMC_CSD_CSIZEMULT(card->rawCsd) + 2;
        readBlkLen = SDMMC_CSD_READBLK_LEN(card->rawCsd);
    }

    if (readBlkLen != 9)
    {
        /* Force to use 512-byte length block */
        cSizeMult += (readBlkLen - 9);
        readBlkLen = 9;
    }

    card->blockSize = 1 << readBlkLen;
    card->blockCount = cSize << cSizeMult;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_SendCid
 * Description: get CID information from card
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_SendCid(sdspi_spi_t *spi, sdspi_card_t *card)
{
    sdspi_request_t *req = 0;

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }
    req->cmdIndex = kSendCid;
    req->respType = kSdSpiRespTypeR1;

    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        req = NULL;
        return kStatus_SDSPI_Failed;
    }

    OSA_MemFree(req);
    req = NULL;

    if (sizeof(card->rawCid) !=
            (SDSPI_DRV_Read(spi, card->rawCid, sizeof(card->rawCid))))
    {
        return kStatus_SDSPI_Failed;
    }

    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_InitSd
 * Description: initialize SD card
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_InitSd(sdspi_spi_t *spi, sdspi_card_t *card)
{
    uint32_t maxFrequency;
    assert(spi);
    assert(spi->ops);
    assert(spi->ops->getMaxFrequency);
    assert(spi->ops->setFrequency);
    assert(card);

    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCsd(spi, card))
    {
        return kStatus_SDSPI_Failed;
    }

    /* Calculate frequency */
    maxFrequency = g_transpeedtv[SDMMC_CSD_TRANSPEED_TV(card->rawCsd)] *
                g_transpeedru[SDMMC_CSD_TRANSPEED_RU(card->rawCsd)];
    if (maxFrequency > spi->busBaudRate)
    {
        maxFrequency = spi->ops->getMaxFrequency(spi);
    }
    spi->ops->setFrequency(spi, maxFrequency);

    SDSPI_DRV_CheckCapacity(card);
    SDSPI_DRV_CheckReadOnly(spi, card);

    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCid(spi, card))
    {
        return kStatus_SDSPI_Failed;
    }

    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_Init
 * Description: initialize card on the given host controller
 *
 *END*********************************************************************/
sdspi_status_t SDSPI_DRV_Init(sdspi_spi_t *spi, sdspi_card_t *card)
{
    uint32_t startTime, elapsedTime, acmd41Arg;
    uint8_t response[5], acmd41resp[5];
    bool likelyMmc = false, likelySdV1 = false;
    assert(card);
    assert(spi);
    assert(spi->ops);
    assert(spi->ops->exchange);
    assert(spi->ops->setFrequency);
    assert(spi->ops->sendWord);

    card->cardType = kCardTypeUnknown;
    if (spi->ops->setFrequency(spi, SDMMC_CLK_400KHZ))
    {
        return kStatus_SDSPI_Failed;
    }

    if (kStatus_SDSPI_NoError != SDSPI_DRV_GoIdle(spi, card))
    {
        return kStatus_SDSPI_Failed;
    }

    acmd41Arg = 0;
    if (kStatus_SDSPI_NoError !=
            SDSPI_DRV_SendIfCond(spi, card, 0xAA, response))
    {
        likelySdV1 = true;
    }
    else if ((response[3] == 0x1) || (response[4] == 0xAA))
    {
        acmd41Arg |= SD_OCR_HCS;
    }
    else
    {
        return kStatus_SDSPI_Failed;
    }

    startTime = OSA_TimeGetMsec();
    do
    {
        if (kStatus_SDSPI_NoError !=
                SDSPI_DRV_AppSendOpCond(spi, card, acmd41Arg, acmd41resp))
        {
            if (likelySdV1)
            {
                likelyMmc = true;
                break;
            }
            return kStatus_SDSPI_Failed;
        }
        elapsedTime = OSA_TimeGetMsec() - startTime;
        if (!acmd41resp[0])
        {
            break;
        }
        if (elapsedTime > 500)
        {
            if (likelySdV1)
            {
                likelyMmc = true;
                break;
            }
        }
    } while(acmd41resp[0] == SDMMC_SPI_R1_IN_IDLE_STATE);

    if (likelyMmc)
    {
        card->cardType = kCardTypeMmc;
        return kStatus_SDSPI_NotSupportYet;
    }
    else
    {
        card->cardType = kCardTypeSd;
    }

    if (!likelySdV1)
    {
        card->version = kSdCardVersion_2_x;
        if (kStatus_SDSPI_NoError != SDSPI_DRV_ReadOcr(spi, card))
        {
            return kStatus_SDSPI_Failed;
        }
        if (card->ocr & SD_OCR_CCS)
        {
            card->caps = SDSPI_CAPS_ACCESS_IN_BLOCK;
        }
    }
    else
    {
        card->version = kSdCardVersion_1_x;
    }

    /* Force to use 512-byte length block, no matter which version  */
    if (kStatus_SDSPI_NoError != SDSPI_DRV_SetBlockSize(spi, 512))
    {
        return kStatus_SDSPI_Failed;
    }

    if (kStatus_SDSPI_NoError != SDSPI_DRV_InitSd(spi, card))
    {
        return kStatus_SDSPI_Failed;
    }

    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_StopTransmission
 * Description:  Send stop transmission command to card to stop ongoing
 * data transferring.
 *
 *END*********************************************************************/
static sdspi_status_t SDSPI_DRV_StopTransmission(sdspi_spi_t *spi)
{
    sdspi_request_t *req = 0;

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    req->cmdIndex = kStopTransmission;
    req->respType = kSdSpiRespTypeR1b;
    if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
    {
        OSA_MemFree(req);
        return kStatus_SDSPI_Failed;
    }

    OSA_MemFree(req);
    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_ReadBlocks
 * Description: read blocks from card 
 *
 *END*********************************************************************/
sdspi_status_t SDSPI_DRV_ReadBlocks(sdspi_spi_t *spi, sdspi_card_t *card, uint8_t *buffer,
                                    uint32_t startBlock, uint32_t blockCount)
{
    uint32_t offset, i;
    sdspi_request_t *req;
    assert(spi);
    assert(card);
    assert(buffer);
    assert(blockCount);

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    offset = startBlock;
    if (!IS_BLOCK_ACCESS(card))
    {
        offset *= card->blockSize;
    }
    
    req->argument = offset;
    req->respType = kSdSpiRespTypeR1;
    if (blockCount == 1)
    {
        req->cmdIndex = kReadSingleBlock;

        if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }
        OSA_MemFree(req);

        if (SDSPI_DRV_Read(spi, buffer, card->blockSize) != card->blockSize)
        {
            return kStatus_SDSPI_Failed;
        }
    }
    else
    {
        req->cmdIndex = kReadMultipleBlock;

        if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }
        OSA_MemFree(req);

        for (i = 0; i < blockCount; i++)
        {
            if (SDSPI_DRV_Read(spi, buffer, card->blockSize) != card->blockSize)
            {
                return kStatus_SDSPI_Failed;
            }
            buffer += card->blockSize;
        }
        SDSPI_DRV_StopTransmission(spi);
    }

    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_WriteBlocks
 * Description: write blocks to card 
 *
 *END*********************************************************************/
sdspi_status_t SDSPI_DRV_WriteBlocks(sdspi_spi_t *spi, sdspi_card_t *card, uint8_t *buffer,
                                     uint32_t startBlock, uint32_t blockCount)
{
    uint32_t offset, i, startTime, elapsedTime;
    uint8_t response;
    sdspi_request_t *req;
    assert(spi);
    assert(card);
    assert(buffer);
    assert(blockCount);

    if (card->state & SDSPI_STATE_WRITE_PROTECTED)
    {
        return kStatus_SDSPI_WriteProtected;
    }

    req = (sdspi_request_t *)OSA_MemAllocZero(sizeof(sdspi_request_t));
    if (req == NULL)
    {
        return kStatus_SDSPI_OutOfMemory;
    }

    offset = startBlock;
    if (!IS_BLOCK_ACCESS(card))
    {
        offset *= card->blockSize;
    }

    if (blockCount == 1)
    {
        req->cmdIndex = kWriteBlock;
        req->argument = offset;
        req->respType = kSdSpiRespTypeR1;
        if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }
        if (req->response[0])
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }

        OSA_MemFree(req);
        if (SDSPI_DRV_Write(spi, buffer, card->blockSize, SDMMC_SPI_DT_START_SINGLE_BLK) != card->blockSize)
        {
            return kStatus_SDSPI_Failed;
        }
    }
    else
    {
#if defined FSL_SDSPI_ENABLE_PRE_ERASE_ON_WRITE
        if (IS_SD_CARD(card))
        {
            /* Pre-erase before writing data */
            if (kStatus_SDSPI_NoError != SDSPI_DRV_SendApplicationCmd(spi))
            {
                OSA_MemFree(req);
                return kStatus_SDSPI_Failed;
            }
            req->cmdIndex = kSdAppSetWrBlkEraseCount;
            req->argument = blockCount;
            req->respType = kSdSpiRespTypeR1;
            if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
            {
                OSA_MemFree(req);
                return kStatus_SDSPI_Failed;
            }
            if (req->response[0])
            {
                OSA_MemFree(req);
                return kStatus_SDSPI_Failed;
            }
        }
#endif

        memset(req, 0, sizeof(sdspi_request_t));
        req->cmdIndex = kWriteMultipleBlock;
        req->argument = offset;
        req->respType = kSdSpiRespTypeR1;

        if (kStatus_SDSPI_NoError != SDSPI_DRV_SendCommand(spi, req, SDSPI_TIMEOUT))
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }
        if (req->response[0])
        {
            OSA_MemFree(req);
            return kStatus_SDSPI_Failed;
        }
        OSA_MemFree(req);

        for (i = 0; i < blockCount; i++)
        {
            if (SDSPI_DRV_Write(spi, buffer, card->blockSize, SDMMC_SPI_DT_START_MULTI_BLK) != card->blockSize)
            {
                return kStatus_SDSPI_Failed;
            }
            buffer += card->blockSize;
        }

        SDSPI_DRV_Write(spi, 0, 0, SDMMC_SPI_DT_STOP_TRANSFER);

        startTime = OSA_TimeGetMsec();
        do
        {
            response = spi->ops->sendWord(spi, 0xFF);
            elapsedTime = OSA_TimeGetMsec() - startTime;
        } while ((response != 0xFF) && (elapsedTime < 100));
    }

    return kStatus_SDSPI_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDSPI_DRV_CheckReadOnly
 * Description: check if card is read only
 *
 *END*********************************************************************/
bool SDSPI_DRV_CheckReadOnly(sdspi_spi_t* spi, sdspi_card_t *card)
{
    assert(card);

    card->state &= ~SDSPI_STATE_WRITE_PROTECTED;
    if (card->cardType != kCardTypeSd)
    {
        return false;
    }

    if (SD_CSD_PERM_WRITEPROTECT(card->rawCsd)
            || SD_CSD_TEMP_WRITEPROTECT(card->rawCsd))
    {
        card->state |= SDSPI_STATE_WRITE_PROTECTED;
        return true;
    }

    return false;
}

void SDSPI_DRV_Shutdown(sdspi_spi_t *spi, sdspi_card_t *card)
{
    assert(spi);
    assert(card);

    memset(card, 0, sizeof(sdspi_card_t));
    return;
}
