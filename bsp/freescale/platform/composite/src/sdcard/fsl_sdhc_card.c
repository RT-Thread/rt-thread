/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#include "fsl_sdhc_card.h"
#include "fsl_sdmmc_card.h"

#if defined(FSL_SDHC_USING_BIG_ENDIAN)
#define swap_be32(x) (x)
#else
#define swap_be32(x) (__REV(x))
#endif

#define FSL_SDCARD_REQUEST_TIMEOUT 1000

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_DelayMsec
 * Description: blocking delay msecond
 *
 *END*********************************************************************/
static void SDCARD_DRV_DelayMsec(uint32_t msec)
{
    uint32_t startTime, elapsedTime;
    assert(msec);

    startTime = OSA_TimeGetMsec();
    do
    {
        elapsedTime = OSA_TimeGetMsec() - startTime;
    } while(elapsedTime < msec);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_DecodeCsd
 * Description: decode csd register
 *
 *END*********************************************************************/
static void SDCARD_DRV_DecodeCsd(uint32_t *rawCsd, sdhc_card_t *card)
{
    sdcard_csd_t *csd;
    assert(rawCsd);
    assert(card);
    csd = &(card->csd);
    csd->csdStructure = (uint8_t)((rawCsd[3] & 0xC0000000U) >> 30);
    csd->taac = (uint8_t)((rawCsd[3] & 0xFF0000) >> 16);
    csd->nsac = (uint8_t)((rawCsd[3] & 0xFF00) >> 8);
    csd->tranSpeed = (uint8_t)(rawCsd[3] & 0xFF);
    csd->ccc = (uint16_t)((rawCsd[2] & 0xFFF00000U) >> 20);
    csd->readBlkLen = (uint8_t)((rawCsd[2] & 0xF0000) >> 16);
    if (rawCsd[2] & 0x8000)
    {
        csd->flags |= SDCARD_CSD_READ_BL_PARTIAL;
    }
    if (rawCsd[2] & 0x4000)
    {
        csd->flags |= SDCARD_CSD_WRITE_BLK_MISALIGN;
    }
    if (rawCsd[2] & 0x2000)
    {
        csd->flags |= SDCARD_CSD_READ_BLK_MISALIGN;
    }
    if (rawCsd[2] & 0x1000)
    {
        csd->flags |= SDCARD_CSD_DSR_IMP;
    }
    if (csd->csdStructure == 0)
    {
        csd->cSize = (uint32_t)((rawCsd[2] & 0x3FF) << 2);
        csd->cSize |= (uint32_t)((rawCsd[1] & 0xC0000000U) >> 30);
        csd->vddRCurrMin = (uint8_t)((rawCsd[1] & 0x38000000) >> 27);
        csd->vddRCurrMax = (uint8_t)((rawCsd[1] & 0x7000000) >> 24);
        csd->vddWCurrMin = (uint8_t)((rawCsd[1] & 0xE00000) >> 20);
        csd->vddWCurrMax = (uint8_t)((rawCsd[1] & 0x1C0000) >> 18);
        csd->cSizeMult = (uint8_t)((rawCsd[1] & 0x38000) >> 15);
        card->blockCount = (csd->cSize + 1) <<  (csd->cSizeMult + 2);
        card->blockSize = CARD_BLOCK_LEN(csd->readBlkLen);
        if (card->blockSize != FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE)
        {
            card->blockCount = card->blockCount * card->blockSize; 
            card->blockSize = FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE;
            card->blockCount = card->blockCount / card->blockSize;
        }
    }
    else if (csd->csdStructure == 1)
    {
        card->blockSize = FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE;
        csd->cSize = (uint32_t)((rawCsd[2] & 0x3F) << 16);
        csd->cSize |= (uint32_t)((rawCsd[1] & 0xFFFF0000U) >> 16);
        if (csd->cSize >= 0xFFFF)
        {
            card->caps |= SDMMC_CARD_CAPS_SDXC;
        }
        card->blockCount = (csd->cSize + 1) * 1024;
    }

    if ((uint8_t)((rawCsd[1] & 0x4000) >> 14))
    {
        csd->flags |= SDCARD_CSD_ERASE_BLK_ENABLED;
    }

    csd->sectorSize = (uint8_t)((rawCsd[1] & 0x3F80) >> 7);
    csd->wpGrpSize = (uint8_t)(rawCsd[1] & 0x7F);
    if ((uint8_t)(rawCsd[0] & 0x80000000U))
    {
        csd->flags |= SDCARD_CSD_WP_GRP_ENABLED;
    }
    csd->r2wFactor = (uint8_t)((rawCsd[0] & 0x1C000000) >> 26);
    csd->writeBlkLen = (uint8_t)((rawCsd[0] & 0x3C00000) >> 22);
    if ((uint8_t)((rawCsd[0] & 0x200000) >> 21))
    {
        csd->flags |= SDCARD_CSD_WRITE_BL_PARTIAL;
    }
    if ((uint8_t)((rawCsd[0] & 0x8000) >> 15))
    {
        csd->flags |= SDCARD_CSD_FILE_FORMAT_GROUP;
    }
    if ((uint8_t)((rawCsd[0] & 0x4000) >> 14))
    {
        csd->flags |= SDCARD_CSD_COPY;
    }
    if ((uint8_t)((rawCsd[0] & 0x2000) >> 13))
    {
        csd->flags |= SDCARD_CSD_PERM_WRITE_PROTECT;
    }
    if ((uint8_t)((rawCsd[0] & 0x1000) >> 12))
    {
        csd->flags |= SDCARD_CSD_TMP_WRITE_PROTECT;
    }
    csd->fileFormat = (uint8_t)((rawCsd[0] & 0xC00) >> 10);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_DecodeCid
 * Description: decode cid register
 *
 *END*********************************************************************/
static void SDCARD_DRV_DecodeCid(uint32_t *rawCid, sdhc_card_t *card)
{
    sdcard_cid_t *cid;
    assert(rawCid);
    assert(card);
    cid = &(card->cid);

    cid->mid = (uint8_t)((rawCid[3] & 0xFF000000) >> 24);

    cid->oid = (uint16_t)((rawCid[3] & 0xFFFF00) >> 8);

    cid->pnm[0] = (uint8_t)((rawCid[3] & 0xFF));
    cid->pnm[1] = (uint8_t)((rawCid[2] & 0xFF000000U) >> 24);
    cid->pnm[2] = (uint8_t)((rawCid[2] & 0xFF0000) >> 16);
    cid->pnm[3] = (uint8_t)((rawCid[2] & 0xFF00) >> 8);
    cid->pnm[4] = (uint8_t)((rawCid[2] & 0xFF));

    cid->prv = (uint8_t)((rawCid[1] & 0xFF000000U) >> 24);

    cid->psn = (uint32_t)((rawCid[1] & 0xFFFFFF) << 8);
    cid->psn |= (uint32_t)((rawCid[0] & 0xFF000000U) >> 24);

    cid->mdt = (uint16_t)((rawCid[0] & 0xFFF00) >> 8);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SendApplicationCmd
 * Description: send application command to card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SendApplicationCmd(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
    sdhc_status_t ret = kStatus_SDHC_NoError;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kAppCmd;
    req->argument = 0;
    if (card->cardType != kCardTypeUnknown)
    {
        req->argument = card->rca << 16;
    }
    req->respType = kSdhcRespTypeR1;

    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
        if (req->error & FSL_SDHC_REQ_ERR_CMD_TIMEOUT)
        {
            ret = kStatus_SDHC_TimeoutError;
        }
        else
        {
            ret = kStatus_SDHC_RequestFailed;
        }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return ret;
    }

    if (!(req->response[0] & SDMMC_R1_APP_CMD))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_CardNotSupport;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}
/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_AllSendCid
 * Description: send all_send_cid command
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_AllSendCid(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kAllSendCid;
    req->argument = 0;
    req->respType = kSdhcRespTypeR2;
    if (kStatus_SDHC_NoError ==
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
        memcpy(card->rawCid, req->response, sizeof(card->rawCid));
        SDCARD_DRV_DecodeCid(req->response, card);
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_NoError;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_RequestFailed;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SendRca
 * Description: send rca command to card to get relative card address
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SendRca(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kSdSendRelativeAddr;
    req->argument = 0;
    req->respType = kSdhcRespTypeR6;
    if (kStatus_SDHC_NoError ==
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
        card->rca = req->response[0] >> 16;
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_NoError;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_RequestFailed;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SendCsd
 * Description: get csd from card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SendCsd(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kSendCsd;
    req->argument = card->rca << 16;
    req->respType = kSdhcRespTypeR2;
    if (kStatus_SDHC_NoError ==
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
        memcpy(card->rawCsd, req->response, sizeof(card->rawCsd));
        SDCARD_DRV_DecodeCsd(req->response, card);
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_NoError;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_RequestFailed;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SelectCard
 * Description: select or deselect card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SelectCard(sdhc_card_t *card, bool isSelected)
{
    sdhc_request_t *req = 0;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kSelectCard;
    if (isSelected)
    {
        req->argument = card->rca << 16;
        req->respType = kSdhcRespTypeR1;
    }
    else
    {
        req->argument = 0;
        req->respType = kSdhcRespTypeNone;
    }
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SetBlockSize
 * Description:  Set the block length in bytes for SDSC cards. For SDHC cards,
 * it does not affect memory read or write commands, always 512 bytes fixed
 * block length is used.
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SetBlockSize(sdhc_card_t *card, uint32_t blockSize)
{
    sdhc_request_t *req = 0;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kSetBlockLen;
    req->argument = blockSize;
    req->respType = kSdhcRespTypeR1;

    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_Switch
 * Description: send switch command to card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_Switch(sdhc_card_t *card,
                                       uint32_t mode,
                                       uint32_t group,
                                       uint32_t value,
                                       uint32_t *resp)
{
    sdhc_request_t *req = 0;
    sdhc_data_t data = {0};
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->data = &data;

    req->cmdIndex = kSdSwitch;
    req->argument = mode << 31 | 0x00FFFFFF;
    req->argument &= ~((uint32_t)(0xF) << (group * 4));
    req->argument |= value << (group * 4);
    req->flags = FSL_SDHC_REQ_FLAGS_DATA_READ;
    req->respType = kSdhcRespTypeR1;


    data.blockSize = 64;
    data.blockCount = 1;
    data.buffer = resp;
    data.req = req;

    if (kStatus_SDHC_NoError != SDCARD_DRV_SetBlockSize(card, data.blockSize))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_SetCardBlockSizeFailed;
    }

    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_DecodeScr
 * Description: decode scr register
 *
 *END*********************************************************************/
static void SDCARD_DRV_DecodeScr(uint32_t *rawScr, sdhc_card_t *card)
{
    sdcard_scr_t *scr;
    assert(rawScr);
    assert(card);

    scr = &(card->scr);
    scr->scrStructure = (uint8_t)((rawScr[0] & 0xF0000000U) >> 28);
    scr->sdSpec = (uint8_t)((rawScr[0] & 0xF000000) >> 24);
    if ((uint8_t)((rawScr[0] & 0x800000) >> 23))
    {
        scr->flags |= SDCARD_SCR_DATA_STAT_AFTER_ERASE;
    }
    scr->sdSecurity = (uint8_t)((rawScr[0] & 0x700000) >> 20);
    scr->sdBusWidths = (uint8_t)((rawScr[0] & 0xF0000) >> 16);
    if ((uint8_t)((rawScr[0] & 0x8000) >> 15))
    {
        scr->flags |= SDCARD_SCR_SD_SPEC3;
    }
    scr->exSecurity = (uint8_t)((rawScr[0] & 0x7800) >> 10);
    scr->cmdSupport = (uint8_t)(rawScr[0] & 0x3);
    scr->reservedForMan = rawScr[1];

    switch(scr->sdSpec)
    {
        case 0:
            card->version = SDMMC_SD_VERSION_1_0;
            break;
        case 1:
            card->version = SDMMC_SD_VERSION_1_1;
            break;
        case 2:
            card->version = SDMMC_SD_VERSION_2_0;
            if (card->scr.flags & SDCARD_SCR_SD_SPEC3)
            {
                card->version = SDMMC_SD_VERSION_3_0;
            }
            break;
        default:
            break;
    }
    if (card->scr.sdBusWidths & SD_SCR_BUS_WIDTHS_4BIT)
    {
        card->caps |= SDMMC_CARD_CAPS_BUSWIDTH_4BITS;
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SendScr
 * Description: fetch scr register from card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SendScr(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
    sdhc_data_t data = {0};
    sdhc_status_t err = kStatus_SDHC_NoError;
    uint32_t rawScr[2] = {0};
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    err = SDCARD_DRV_SendApplicationCmd(card);
    if (err)
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return err;
    }

    req->data = &data;
    req->cmdIndex = kSdAppSendScr;
    req->flags = FSL_SDHC_REQ_FLAGS_DATA_READ;
    req->respType = kSdhcRespTypeR1;
    req->argument = 0;

    data.blockSize = 8;
    data.blockCount = 1;
    data.buffer = rawScr;
    data.req = req;

    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }
    rawScr[0] = swap_be32(rawScr[0]);
    rawScr[1] = swap_be32(rawScr[1]);
    memcpy(card->rawScr, rawScr, sizeof(card->rawScr));
    SDCARD_DRV_DecodeScr(rawScr, card);
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SwitchHighspeed
 * Description: switch high speed mode of the specific card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SwitchHighspeed(sdhc_card_t *card)
{
    uint32_t response[16] = {0};
    sdhc_status_t err = kStatus_SDHC_NoError;
    assert(card);

    if ((card->version < SDMMC_SD_VERSION_1_1)
         || (!(card->csd.ccc & SD_CCC_SWITCH)))
    {
        return kStatus_SDHC_CardNotSupport;
    }

    err = SDCARD_DRV_Switch(card, kSdSwitchCheck, 0, 1, response);
    if (err)
    {
        return err;
    }

    if ((!(swap_be32(response[3]) & 0x10000)) ||
        ((swap_be32(response[4]) & 0x0f000000) == 0x0F000000))
    {
        return kStatus_SDHC_CardNotSupport;
    }

    err = SDCARD_DRV_Switch(card, kSdSwitchSet, 0, 1, response);
    if (err)
    {
        return err;
    }

    if ((swap_be32(response[4]) & 0x0f000000) != 0x01000000)
    {
        err = kStatus_SDHC_SwitchFailed;
    }

    return err;

}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SetBusWidth
 * Description: set desired buswidth
 *
 *END*********************************************************************/
static uint32_t SDCARD_DRV_SetBusWidth(sdhc_card_t *card,
                                       sd_buswidth_t busWidth)
{
    sdhc_request_t *req = 0;
    sdhc_status_t err = kStatus_SDHC_NoError;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    err = SDCARD_DRV_SendApplicationCmd(card);
    if (err != kStatus_SDHC_NoError)
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return err;
    }

    req->cmdIndex = kSdAppSetBusWdith;
    req->respType = kSdhcRespTypeR1;
    req->argument = busWidth;

    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return err;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_InitSd
 * Description: initialize SD memory card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_InitSd(sdhc_card_t *card)
{
    assert(card);
    sdhc_status_t err = kStatus_SDHC_NoError;
    card->cardType = kCardTypeSd;

    if (kStatus_SDHC_NoError != SDCARD_DRV_AllSendCid(card))
    {
        return kStatus_SDHC_AllSendCidFailed;
    }

    if (kStatus_SDHC_NoError != SDCARD_DRV_SendRca(card))
    {
        return kStatus_SDHC_SendRcaFailed;
    }

    if (kStatus_SDHC_NoError != SDCARD_DRV_SendCsd(card))
    {
        return kStatus_SDHC_SendCsdFailed;
    }

    if (kStatus_SDHC_NoError != SDCARD_DRV_SelectCard(card, true))
    {
        return kStatus_SDHC_SelectCardFailed;
    }

    if (kStatus_SDHC_NoError != SDCARD_DRV_SendScr(card))
    {
        return kStatus_SDHC_SendScrFailed;
    }

    if (kStatus_SDHC_NoError !=
            SDHC_DRV_ConfigClock(card->hostInstance, SDMMC_CLK_25MHZ))
    {
        return kStatus_SDHC_SetClockFailed;
    }

    if (DOES_HOST_SUPPORT_4BITS(card->host) && DOES_CARD_SUPPORT_4BITS(card))
    {
        if (kStatus_SDHC_NoError != SDCARD_DRV_SetBusWidth(card, kSdBusWidth4Bit))
        {
            return kStatus_SDHC_SetCardWideBusFailed;
        }
        if (kStatus_SDHC_NoError !=
                SDHC_DRV_SetBusWidth(card->hostInstance, kSdhcBusWidth4Bit))
        {
            return kStatus_SDHC_SetBusWidthFailed;
        }
    }

    if (DOES_HOST_SUPPORT_HIGHSPEED(card->host))
    {
        err = SDCARD_DRV_SwitchHighspeed(card);
        if ((err != kStatus_SDHC_NoError) && (kStatus_SDHC_CardNotSupport != err))
        {
            return kStatus_SDHC_SwitchHighSpeedFailed;
        }
        else if (err == kStatus_SDHC_NoError)
        {
            if (kStatus_SDHC_NoError !=
                    SDHC_DRV_ConfigClock(card->hostInstance, SDMMC_CLK_50MHZ))
            {
                return kStatus_SDHC_SetClockFailed;
            }
        }
        else
        {
            err = kStatus_SDHC_NoError;
        }
    }

    if (SDCARD_DRV_SetBlockSize(card, FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE))
    {
        err = kStatus_SDHC_SetCardBlockSizeFailed;
    }
    return err;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_AppSendOpCond
 * Description: Send host capacity support information and asks the accessed
 * card to send its operating condition register content.
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_AppSendOpCond(sdhc_card_t *card,
                                              uint32_t acmd41Arg)
{
    sdhc_request_t *req = 0;
    sdhc_status_t err;
    uint32_t i = FSL_SDHC_CARD_MAX_VOLT_RETRIES;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kSdAppSendOpCond;
    req->argument = acmd41Arg;
    req->respType = kSdhcRespTypeR3;

    while (i--)
    {
        err = SDCARD_DRV_SendApplicationCmd(card);
        if (err != kStatus_SDHC_NoError)
        {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
            OSA_MemFree(req);
#endif
            req = NULL;
            return err;
        }

        if (kStatus_SDHC_NoError !=
                SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                              req,
                                              FSL_SDCARD_REQUEST_TIMEOUT))
        {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
            OSA_MemFree(req);
#endif
            req = NULL;
            return err;
        }

        if (req->response[0] & SDMMC_CARD_BUSY)
        {
            if (req->response[0] & SD_OCR_CCS)
            {
                card->caps |= SDMMC_CARD_CAPS_HIGHCAPACITY;
            }
            err = kStatus_SDHC_NoError;
            card->ocr = req->response[0];
            break;
        }
        err = kStatus_SDHC_TimeoutError;

        SDCARD_DRV_DelayMsec(1);
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return err;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_GoIdle
 * Description: reset all cards to idle state
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_GoIdle(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
    sdhc_status_t err;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kGoIdleState;
    err = SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                        req,
                                        FSL_SDCARD_REQUEST_TIMEOUT);
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return err;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_CheckReadOnly
 * Description: Check if the card is ready only
 *
 *END*********************************************************************/
bool SDCARD_DRV_CheckReadOnly(sdhc_card_t *card)
{
    assert(card);

    return ((card->csd.flags & SDCARD_CSD_PERM_WRITE_PROTECT) ||
            (card->csd.flags & SDCARD_CSD_TMP_WRITE_PROTECT));
}



/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_SendIfCond
 * Description: check card interface condition, which includes host supply
 * voltage information and asks the card whether card supports voltage.
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_SendIfCond(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
    sdhc_status_t err = kStatus_SDHC_NoError;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    req->cmdIndex = kSdSendIfCond;
    req->argument = 0x1AA;
    req->respType = kSdhcRespTypeR7;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
        err = kStatus_SDHC_RequestFailed;
    }
    else if ((req->response[0] & 0xFF) != 0xAA)
    {
        err = kStatus_SDHC_CardNotSupport;
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return err;
}

#if ! defined BSP_FSL_SDHC_ENABLE_AUTOCMD12
/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_StopTransmission
 * Description:  Send stop transmission command to card to stop ongoing
 * data transferring.
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_StopTransmission(sdhc_card_t *card)
{
    sdhc_request_t *req = 0;
    sdhc_status_t err = kStatus_SDHC_NoError;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif

    req->cmdIndex = kStopTransmission;
    req->flags |= FSL_SDHC_REQ_FLAGS_STOP_TRANS;
    req->argument = 0;
    req->respType = kSdhcRespTypeR1b;
    req->data = 0;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return err;
}
#endif

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_Read
 * Description: read data from specific card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_Read(sdhc_card_t *card,
                                     uint8_t *buffer,
                                     uint32_t startBlock,
                                     uint32_t blockSize,
                                     uint32_t blockCount)
{
    sdhc_request_t *req = 0;
    sdhc_data_t data = {0};
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif

    assert(card);
    assert(buffer);
    assert(blockCount);
    assert(blockSize);
    assert(blockSize == FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE);

    if ((IS_HIGHCAPACITY_CARD(card) && (blockSize != 512))
         || (blockSize > card->blockSize)
         || (blockSize > card->host->maxBlockSize)
         || (blockSize % 4))
    {
        return kStatus_SDHC_BlockSizeNotSupportError;
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif

    data.blockSize = blockSize;
    data.blockCount = blockCount;
    data.buffer = (uint32_t *)buffer;

    req->data = &data;
    req->cmdIndex = kReadMultipleBlock;
    if (data.blockCount == 1)
    {
        req->cmdIndex = kReadSingleBlock;
    }

    req->argument = startBlock;
    if (!IS_HIGHCAPACITY_CARD(card))
    {
        req->argument *= data.blockSize;
    }
    req->flags = FSL_SDHC_REQ_FLAGS_DATA_READ;
    req->respType = kSdhcRespTypeR1;

    data.req = req;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }

#if ! defined BSP_FSL_SDHC_ENABLE_AUTOCMD12
    if (data.blockCount > 1)
    {
        if (kStatus_SDHC_NoError != SDCARD_DRV_StopTransmission(card))
        {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
            OSA_MemFree(req);
#endif
            req = NULL;
            return kStatus_SDHC_StopTransmissionFailed;
        }
    }
#endif
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_Write
 * Description: write data from specific card
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_Write(sdhc_card_t *card,
                                      uint8_t *buffer,
                                      uint32_t startBlock,
                                      uint32_t blockSize,
                                      uint32_t blockCount)
{
    sdhc_request_t *req = 0;
    sdhc_data_t data = {0};
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);
    assert(buffer);
    assert(blockCount);
    assert(blockSize);
    assert(blockSize == FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE);

    if ((IS_HIGHCAPACITY_CARD(card) && (blockSize != 512))
         || (blockSize > card->blockSize)
         || (blockSize > card->host->maxBlockSize)
         || (blockSize % 4))
    {
        return kStatus_SDHC_BlockSizeNotSupportError;
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif

    data.blockSize = blockSize;
    data.blockCount = blockCount;
    data.buffer = (uint32_t *)buffer;

    req->data = &data;
    req->cmdIndex = kWriteMultipleBlock;
    if (data.blockCount == 1)
    {
        req->cmdIndex = kWriteBlock;
    }

    req->argument = startBlock;
    if (!IS_HIGHCAPACITY_CARD(card))
    {
        req->argument *= data.blockSize;
    }
    req->respType = kSdhcRespTypeR1;
    data.req = req;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }

    if (data.blockCount > 1)
    {
#if ! defined BSP_FSL_SDHC_ENABLE_AUTOCMD12
        if (kStatus_SDHC_NoError != SDCARD_DRV_StopTransmission(card))
        {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
            OSA_MemFree(req);
#endif
            req = NULL;
            return kStatus_SDHC_StopTransmissionFailed;
        }
#endif
    }
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_Erase
 * Description: erase data for the given block range
 *
 *END*********************************************************************/
static sdhc_status_t SDCARD_DRV_Erase(sdhc_card_t *card,
                                      uint32_t startBlock,
                                      uint32_t blockCount)
{
    uint32_t s, e;
    sdhc_request_t *req = 0;
#if ! defined BSP_FSL_SDHC_USING_DYNALLOC
    sdhc_request_t request = {0};
    req = &request;
#endif
    assert(card);
    assert(blockCount);

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    req = (sdhc_request_t *)OSA_MemAllocZero(sizeof(sdhc_request_t));
    if (req == NULL)
    {
        return kStatus_SDHC_OutOfMemory;
    }
#endif
    s = startBlock;
    e = s + blockCount - 1;
    if (!IS_HIGHCAPACITY_CARD(card))
    {
        s = s * FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE;
        e = e * FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE;
    }

    req->cmdIndex = kSdEraseWrBlkStart;
    req->argument = s;
    req->respType = kSdhcRespTypeR1;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }
    req->cmdIndex = kSdEraseWrBlkEnd;
    req->argument = e;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }
    req->cmdIndex = kErase;
    req->argument = 0;
    req->respType = kSdhcRespTypeR1b;
    if (kStatus_SDHC_NoError !=
            SDHC_DRV_IssueRequestBlocking(card->hostInstance,
                                          req,
                                          FSL_SDCARD_REQUEST_TIMEOUT))
    {
#if defined BSP_FSL_SDHC_USING_DYNALLOC
        OSA_MemFree(req);
#endif
        req = NULL;
        return kStatus_SDHC_RequestFailed;
    }

#if defined BSP_FSL_SDHC_USING_DYNALLOC
    OSA_MemFree(req);
#endif
    req = NULL;
    return kStatus_SDHC_NoError;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_Shutdown
 * Description: destory initialized card and shutdown the corresponding
 * host controller
 *
 *END*********************************************************************/
void SDCARD_DRV_Shutdown(sdhc_card_t *card)
{
    assert(card);
    SDCARD_DRV_SelectCard(card, false);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_Init
 * Description: initialize card on the given host controller
 *
 *END*********************************************************************/
sdhc_status_t SDCARD_DRV_Init(sdhc_host_t *host, sdhc_card_t *card)
{
    sdhc_status_t err = kStatus_SDHC_NoError;
    uint32_t acmd41Arg;
    assert(card);
    assert(host);

    card->cardType = kCardTypeUnknown;
    card->host = host;
    card->hostInstance = host->instance;

    if (SDHC_DRV_ConfigClock(card->hostInstance, SDMMC_CLK_400KHZ))
    {
        return kStatus_SDHC_SetClockFailed;
    }

    err = SDCARD_DRV_GoIdle(card);
    if (err)
    {
        return kStatus_SDHC_SetCardToIdle;
    }
    acmd41Arg = card->host->ocrSupported;

    err = SDCARD_DRV_SendIfCond(card);
    if (err == kStatus_SDHC_NoError)
    {
        /* SDHC or SDXC card */
        acmd41Arg |= SD_OCR_HCS;
        card->caps |= SDMMC_CARD_CAPS_SDHC;
    }
    else
    {
        /* SDSC card */
        err = SDCARD_DRV_GoIdle(card);
        if (err)
        {
            return kStatus_SDHC_SetCardToIdle;
        }
    }

    err = SDCARD_DRV_AppSendOpCond(card, acmd41Arg);
    if (kStatus_SDHC_TimeoutError == err)
    {
        /* MMC card */
        return kStatus_SDHC_NotSupportYet;
    }
    else if (err)
    {
        return kStatus_SDHC_SendAppOpCondFailed;
    }

    return SDCARD_DRV_InitSd(card);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_WriteBlocks
 * Description: write blocks to card with default block size
 *
 *END*********************************************************************/
sdhc_status_t SDCARD_DRV_WriteBlocks(sdhc_card_t *card,
                                     uint8_t *buffer,
                                     uint32_t startBlock,
                                     uint32_t blockCount)
{
    uint32_t blkCnt, blkLeft, blkDone;
    sdhc_status_t err = kStatus_SDHC_NoError;

    assert(card);
    assert(buffer);
    assert(blockCount);

    blkLeft = blockCount;
    blkDone = 0;

    if ((blockCount + startBlock) > card->blockCount)
    {
        return kStatus_SDHC_InvalidIORange;
    }

    while(blkLeft)
    {
        if (blkLeft > card->host->maxBlockCount)
        {
            blkLeft = blkLeft - card->host->maxBlockCount;
            blkCnt = card->host->maxBlockCount;
        }
        else
        {
            blkCnt = blkLeft;
            blkLeft = 0;
        }

        err = SDCARD_DRV_Write(card,
                          buffer + blkDone * FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE,
                          startBlock + blkDone,
                          FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE,
                          blkCnt);
        if (err != kStatus_SDHC_NoError)
        {
            return err;
        }
        blkDone += blkCnt;
    }

    return err;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_ReadBlocks
 * Description: read blocks from card with default block size
 *
 *END*********************************************************************/
sdhc_status_t SDCARD_DRV_ReadBlocks(sdhc_card_t *card,
                                    uint8_t *buffer,
                                    uint32_t startBlock,
                                    uint32_t blockCount)
{
    uint32_t blkCnt, blkLeft, blkDone;
    sdhc_status_t err = kStatus_SDHC_NoError;

    assert(card);
    assert(buffer);
    assert(blockCount);

    blkLeft = blockCount;
    blkDone = 0;

    if ((blockCount + startBlock) > card->blockCount)
    {
        return kStatus_SDHC_InvalidIORange;
    }

    while(blkLeft)
    {
        if (blkLeft > card->host->maxBlockCount)
        {
            blkLeft = blkLeft - card->host->maxBlockCount;
            blkCnt = card->host->maxBlockCount;
        }
        else
        {
            blkCnt = blkLeft;
            blkLeft = 0;
        }

        err = SDCARD_DRV_Read(card,
                          buffer + blkDone * FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE,
                          startBlock + blkDone,
                          FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE,
                          blkCnt);
        if (err != kStatus_SDHC_NoError)
        {
            return err;
        }
        blkDone += blkCnt;
    }

    return err;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDCARD_DRV_EraseBlocks
 * Description: erase block range from card with default block size
 *
 *END*********************************************************************/
sdhc_status_t SDCARD_DRV_EraseBlocks(sdhc_card_t *card,
                                     uint32_t startBlock,
                                     uint32_t blockCount)
{
    uint32_t blkDone = 0, blkLeft, blkCnt;

    assert(card);
    assert(blockCount);

    blkLeft = blockCount;
    while(blkLeft)
    {
        if (blkLeft > (card->csd.sectorSize + 1))
        {
            blkCnt = card->csd.sectorSize + 1;
            blkLeft = blkLeft - blkCnt;
        }
        else
        {
            blkCnt = blkLeft;
            blkLeft = 0;
        }

        if (kStatus_SDHC_NoError != SDCARD_DRV_Erase(card,
                                                     startBlock + blkDone,
                                                     blkCnt))
        {
            return kStatus_SDHC_CardEraseBlocksFailed;
        }

        blkDone += blkCnt;
    }
    return kStatus_SDHC_NoError;
}
