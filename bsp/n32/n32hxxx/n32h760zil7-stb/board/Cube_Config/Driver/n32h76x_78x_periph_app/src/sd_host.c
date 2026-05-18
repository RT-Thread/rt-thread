/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file sd_host.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "sd_host.h"

static Status_card SD_SendCardStatus(sd_card_t* card);
static void SD_configSDMABufferSize(sd_card_t *card, uint32_t *buffer, uint32_t blockCount);
static Status_card SD_SwitchFunction(sd_card_t *card,uint32_t mode);;



/* SD card block erase time, varies according to different SD cards */
#define SD_BLOCKERASE_TIME  (250U)

uint32_t SD_systick_timeoutms = 0;

Status_card SD_NormalCMD_Send(sd_card_t* card, uint32_t index,uint32_t argument,SDMMC_CardRspType responseType)
{
    Status_card status_temp;
    
    card->command.index = index;
    card->command.argument = argument; 
    card->command.type = CARD_CommandTypeNormal;
    card->command.responseType = responseType;
    card->command.flags = 0x00;
    card->command.responseErrorFlags = 0x00;
    SDMMC_SendCommand(card->SDHOSTx,&card->command,&card->TMODE_truct);
    if(SDMMC_WaitCommandDone(card->SDHOSTx,&card->command,ENABLE) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    else
    {
        status_temp = Status_Success;
    }
    return status_temp;
}


Status_card SD_AutoCMD_Send(sd_card_t* card, uint32_t index,uint32_t argument,SDMMC_CardRspType responseType)
{
    Status_card status_temp = Status_Success;
    
    /* CMD55 */
    card->command.index = SDMMC_ApplicationCommand;
    card->command.argument = card->sd_card_information.rca << 16;
    card->command.type = CARD_CommandTypeNormal;
    card->command.responseType = CARD_ResponseTypeR1;
    card->command.flags = 0x00;
    card->command.responseErrorFlags = 0x00;
    SDMMC_SendCommand(card->SDHOSTx,&card->command,&card->TMODE_truct);
    if(SDMMC_WaitCommandDone(card->SDHOSTx,&card->command,ENABLE) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    card->command.index = index;
    card->command.argument = argument; 
    card->command.type = CARD_CommandTypeNormal;
    card->command.responseType = responseType;
    card->command.flags = 0x00;
    card->command.responseErrorFlags = 0x00;
    SDMMC_SendCommand(card->SDHOSTx,&card->command,&card->TMODE_truct);
    if(SDMMC_WaitCommandDone(card->SDHOSTx,&card->command,ENABLE) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    return status_temp;
}


void SD_DecodeCid(sd_card_t* card)
{
    /* get cid */
    card->sd_card_information.cid.manufacturerID = (uint8_t)((card->command.response[3U] & 0xFF000000U) >> 24U);
    card->sd_card_information.cid.applicationID  = (uint16_t)((card->command.response[3U] & 0xFFFF00U) >> 8U);

    card->sd_card_information.cid.productName[0U] = (uint8_t)((card->command.response[3U] & 0xFFU));
    card->sd_card_information.cid.productName[1U] = (uint8_t)((card->command.response[2U] & 0xFF000000U) >> 24U);
    card->sd_card_information.cid.productName[2U] = (uint8_t)((card->command.response[2U] & 0xFF0000U) >> 16U);
    card->sd_card_information.cid.productName[3U] = (uint8_t)((card->command.response[2U] & 0xFF00U) >> 8U);
    card->sd_card_information.cid.productName[4U] = (uint8_t)((card->command.response[2U] & 0xFFU));

    card->sd_card_information.cid.productVersion = (uint8_t)((card->command.response[1U] & 0xFF000000U) >> 24U);

    card->sd_card_information.cid.productSerialNumber = (uint32_t)((card->command.response[1U] & 0xFFFFFFU) << 8U);
    card->sd_card_information.cid.productSerialNumber |= (uint32_t)((card->command.response[0U] & 0xFF000000U) >> 24U);

    card->sd_card_information.cid.manufacturerData = (uint16_t)((card->command.response[0U] & 0xFFF00U) >> 8U);
}


void SD_DecodeCsd(sd_card_t* card)
{
    card->sd_card_information.csd.csdStructure        = (uint8_t)((card->command.response[3U] & 0xC0000000U) >> 30U);
    card->sd_card_information.csd.dataReadAccessTime1 = (uint8_t)((card->command.response[3U] & 0xFF0000U) >> 16U);
    card->sd_card_information.csd.dataReadAccessTime2 = (uint8_t)((card->command.response[3U] & 0xFF00U) >> 8U);
    card->sd_card_information.csd.transferSpeed       = (uint8_t)(card->command.response[3U] & 0xFFU);
    card->sd_card_information.csd.cardCommandClass    = (uint16_t)((card->command.response[2U] & 0xFFF00000U) >> 20U);
    card->sd_card_information.csd.readBlockLength     = (uint8_t)((card->command.response[2U] & 0xF0000U) >> 16U);
    if ((card->command.response[2U] & 0x8000U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdReadBlockPartialFlag;
    }
    if ((card->command.response[2U] & 0x4000U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdWriteBlockMisalignFlag;
    }
    if ((card->command.response[2U] & 0x2000U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdReadBlockMisalignFlag;
    }
    if ((card->command.response[2U] & 0x1000U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdDsrImplementedFlag;
    }
    if (card->sd_card_information.csd.csdStructure == 0U)
    {
        card->sd_card_information.csd.deviceSize = (uint32_t)((card->command.response[2U] & 0x3FFU) << 2U);
        card->sd_card_information.csd.deviceSize |= (uint32_t)((card->command.response[1U] & 0xC0000000U) >> 30U);
        card->sd_card_information.csd.readCurrentVddMin    = (uint8_t)((card->command.response[1U] & 0x38000000U) >> 27U);
        card->sd_card_information.csd.readCurrentVddMax    = (uint8_t)((card->command.response[1U] & 0x7000000U) >> 24U);
        card->sd_card_information.csd.writeCurrentVddMin   = (uint8_t)((card->command.response[1U] & 0xE00000U) >> 20U);
        card->sd_card_information.csd.writeCurrentVddMax   = (uint8_t)((card->command.response[1U] & 0x1C0000U) >> 18U);
        card->sd_card_information.csd.deviceSizeMultiplier = (uint8_t)((card->command.response[1U] & 0x38000U) >> 15U);

        /* Get card total block count and block size. */
        card->sd_card_information.blockCount = ((card->sd_card_information.csd.deviceSize + 1U) << (card->sd_card_information.csd.deviceSizeMultiplier + 2U));
        card->sd_card_information.blockSize  = (1UL << (card->sd_card_information.csd.readBlockLength));
        if (card->sd_card_information.blockSize != FSL_SDMMC_DEFAULT_BLOCK_SIZE)
        {
            card->sd_card_information.blockCount = (card->sd_card_information.blockCount * card->sd_card_information.blockSize);
            card->sd_card_information.blockSize  = FSL_SDMMC_DEFAULT_BLOCK_SIZE;
            card->sd_card_information.blockCount = (card->sd_card_information.blockCount / card->sd_card_information.blockSize);
        }
    }
    else if (card->sd_card_information.csd.csdStructure == 1U)
    {
        card->sd_card_information.blockSize = FSL_SDMMC_DEFAULT_BLOCK_SIZE;

        card->sd_card_information.csd.deviceSize = (uint32_t)((card->command.response[2U] & 0x3FU) << 16U);
        card->sd_card_information.csd.deviceSize |= (uint32_t)((card->command.response[1U] & 0xFFFF0000U) >> 16U);
        if (card->sd_card_information.csd.deviceSize >= 0xFFFFU)
        {
            card->sd_card_information.flags |= (uint32_t)SD_SupportSdxcFlag;
        }

        card->sd_card_information.blockCount = ((card->sd_card_information.csd.deviceSize + 1U) * 1024U);
    }
    else
    {
        /* not support csd version */
    }

    if ((uint8_t)((card->command.response[1U] & 0x4000U) >> 14U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdEraseBlockEnabledFlag;
    }
    card->sd_card_information.csd.eraseSectorSize       = (uint8_t)((card->command.response[1U] & 0x3F80U) >> 7U);
    card->sd_card_information.csd.writeProtectGroupSize = (uint8_t)(card->command.response[1U] & 0x7FU);
    if ((uint8_t)(card->command.response[0U] & 0x80000000U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdWriteProtectGroupEnabledFlag;
    }
    card->sd_card_information.csd.writeSpeedFactor = (uint8_t)((card->command.response[0U] & 0x1C000000U) >> 26U);
    card->sd_card_information.csd.writeBlockLength = (uint8_t)((card->command.response[0U] & 0x3C00000U) >> 22U);
    if ((uint8_t)((card->command.response[0U] & 0x200000U) >> 21U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdWriteBlockPartialFlag;
    }
    if ((uint8_t)((card->command.response[0U] & 0x8000U) >> 15U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdFileFormatGroupFlag;
    }
    if ((uint8_t)((card->command.response[0U] & 0x4000U) >> 14U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdCopyFlag;
    }
    if ((uint8_t)((card->command.response[0U] & 0x2000U) >> 13U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdPermanentWriteProtectFlag;
    }
    if ((uint8_t)((card->command.response[0U] & 0x1000U) >> 12U) != 0U)
    {
        card->sd_card_information.csd.flags |= (uint16_t)SD_CsdTemporaryWriteProtectFlag;
    }
    card->sd_card_information.csd.fileFormat = (uint8_t)((card->command.response[0U] & 0xC00U) >> 10U);
}

static Status_card SD_SendCardStatus(sd_card_t* card)
{
    Status_card status_temp;
    uint32_t retry               = SD_CMD13_RETRY_TIMES;
    while(retry != 0U)
    {
        /* CMD13 */
        if(SD_NormalCMD_Send(card,SDMMC_SendStatus,card->sd_card_information.rca << 16,CARD_ResponseTypeR1) != Status_Success)
        {
            if(SDMMC_GetPresentFlagStatus(card->SDHOSTx,SDHOST_CommandInhibitFlag))
            {
                SDMMC_SoftWareReset(card->SDHOSTx,SDHOST_SOFTWARE_CMDLINE);
            }
            status_temp = Status_Fail;
            retry--;
        }
        else
        {
            if(((card->command.response[0] & SDMMC_MASK(SDMMC_R1ReadyForDataFlag)) != 0U) &&
                (SDMMC_R1_CURRENT_STATE(card->command.response[0U]) != (uint32_t)SDMMC_R1StateProgram))
            {
                status_temp = Status_CardStatusIdle;
            }
            else
            {
                status_temp = Status_CardStatusBusy;
            }
            break;
        }
    }
    return status_temp;
}

Status_card SD_PollingCardStatusBusy(sd_card_t* card,uint32_t timeoutMs)
{
    uint32_t timeout_temp;
    uint32_t timeout_cnt = 0;
    bool cardBusy            = false;
    Status_card status_temp  = Status_CardStatusBusy;

    SD_SysTick_start_time();
    timeout_temp = SD_systick_timeoutms;
    while(timeout_cnt < timeoutMs)
    {
        if(SDMMC_GetPresentFlagStatus(card->SDHOSTx,SDHOST_Data0LineLevelFlag) == SET)
        {
            cardBusy = false;
        }
        else
        {
            cardBusy = true;
        }

        if (cardBusy == false)
        {
            status_temp = SD_SendCardStatus(card);
            if (status_temp == Status_CardStatusIdle)
            {
                break;
            }
        }
        
        timeout_cnt = SD_User_Time_Read(timeout_temp);
    }
    
    if(SDMMC_GetFlagStatus(card->SDHOSTx,SDHOST_DataCompleteFlag) == SET)
    {
        SDMMC_ClrFlag(card->SDHOSTx,SDHOST_DataCompleteFlag);
    }

    return status_temp;
}

Status_card SD_SendSCR(sd_card_t* card)
{
    uint32_t card_scr[2];
    SDMMC_Transfer transfer;
    Status_card status_temp = Status_Success;

    SDMMC_EnableFlagStatus(card->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,DISABLE);
      
    /* CMD55 */
    if(SD_NormalCMD_Send(card,SDMMC_ApplicationCommand,card->sd_card_information.rca << 16,CARD_ResponseTypeR1) != Status_Success)
    {
        status_temp = Status_Fail;
    }

    
    transfer.data.AutoCommand12_23 = NoAutoCommand;
    transfer.data.enableIgnoreError = DISABLE;
    transfer.data.dataType = SDHOST_TransferDataNormal;
    transfer.data.blockCount = 1;
    transfer.data.blockSize = 8;
    transfer.data.rxData = card_scr;
    transfer.data.txData = NULL;

    transfer.command.index = SD_ApplicationSendScr;
    transfer.command.argument = 0x00;
    transfer.command.type = CARD_CommandTypeNormal;
    transfer.command.responseType = CARD_ResponseTypeR1;
    transfer.command.flags = 0x00;
    transfer.command.responseErrorFlags = 0x00;
    
    if(SDMMC_TransferBlocking(card->SDHOSTx,NULL,&transfer,&card->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    if(status_temp == Status_Success)
    {
        card->sd_card_information.scr.scrStructure = (uint8_t)((card_scr[0] & 0x000000F0U) >> 4);
        card->sd_card_information.scr.sdSpecification = (uint8_t)(card_scr[0] & 0x0000000FU);
        
        if((card_scr[0] & 0x00008000) != 0)
        {
            card->sd_card_information.scr.flags |= (uint8_t)SD_ScrDataStatusAfterErase;
        }
        card->sd_card_information.scr.sdSecurity = (uint8_t)((card_scr[0] & 0x00007000U) >> 12);
        card->sd_card_information.scr.sdBusWidths = (uint8_t)((card_scr[0] & 0x00000F00U) >> 8);
        if((card_scr[0] & 0x00800000) != 0)
        {
            card->sd_card_information.scr.flags |= (uint8_t)SD_ScrSdSpecification3;
        }
        card->sd_card_information.scr.commandSupport = (uint8_t)((card_scr[0] & 0x03000000U) >> 24);
        card->sd_card_information.scr.reservedForManufacturer =  (((card_scr[1] << 24) & 0xff000000) | ((card_scr[1] << 8) & 0x00ff0000) 
                                                               | ((card_scr[1] >> 8) & 0x0000ff00) | ((card_scr[1] >> 24) & 0x000000ff));
        
        if(card->sd_card_information.scr.sdSpecification == 0U)
        {
            card->sd_card_information.version = SD_SpecificationVersion1_0;
        }
        else if(card->sd_card_information.scr.sdSpecification == 1U)
        {
            card->sd_card_information.version = SD_SpecificationVersion1_1;
        }
        else if(card->sd_card_information.scr.sdSpecification == 2U)
        {
            card->sd_card_information.version = SD_SpecificationVersion2_0;
            if((card->sd_card_information.flags & SD_ScrSdSpecification3) != 0)
            {
                card->sd_card_information.version = SD_SpecificationVersion3_0;
            }
        }
        else
        {
            /* reserved */
        }
        
        if((card->sd_card_information.scr.sdBusWidths & 0x04U) != 0)
        {
            card->sd_card_information.flags |= (uint32_t)SD_Support4BitWidthFlag;
        }
        
        if((card->sd_card_information.scr.commandSupport & 0x01U) != 0)
        {
            card->sd_card_information.flags |= (uint32_t)SD_SupportSpeedClassControlCmd;
        }
        
        if((card->sd_card_information.scr.commandSupport & 0x02U) != 0)
        {
            card->sd_card_information.flags |= (uint32_t)SD_SupportSetBlockCountCmd;
        }
        
        status_temp = Status_Success;
    }
    SDMMC_EnableFlagStatus(card->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,ENABLE);

    return status_temp;
}


Status_card SD_Erase_Block(sd_card_t* card, uint32_t startBlock, uint32_t blockCount)
{
    uint32_t eraseBlockStart;
    uint32_t eraseBlockEnd; 
    Status_card status_temp  = Status_CardStatusBusy;
    uint32_t timeout_block = SD_BLOCKERASE_TIME;    /* 250ms erase timeout by default */
    
    if(startBlock + blockCount > card->sd_card_information.blockCount)
    {
        return Status_CardOutOfRange;
    }
    
    /* polling card status idle */
    status_temp = SD_PollingCardStatusBusy(card, SD_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }
    
    eraseBlockStart = startBlock;
    eraseBlockEnd   = eraseBlockStart + blockCount - 1U;
    
    /* SDSC card */
    if (0U == (card->sd_card_information.flags & (uint32_t)SD_SupportHighCapacityFlag))
    {
        eraseBlockStart = startBlock * FSL_SDMMC_DEFAULT_BLOCK_SIZE;
        eraseBlockEnd   = eraseBlockEnd * FSL_SDMMC_DEFAULT_BLOCK_SIZE;
    }
    
    /* CMD32 */
    if(SD_NormalCMD_Send(card,SD_EraseWriteBlockStart,eraseBlockStart,CARD_ResponseTypeR1) != Status_Success)    
    {
        return Status_Fail;
    }
    
    /* CMD33 */
    if(SD_NormalCMD_Send(card,SD_EraseWriteBlockEnd,eraseBlockEnd,CARD_ResponseTypeR1) != Status_Success)
    {
        return Status_Fail;
    }
    
    /* CMD38 */
    if(SD_NormalCMD_Send(card,SDMMC_Erase,0x00,CARD_ResponseTypeR1b) != Status_Success)
    {
        return Status_Fail;
    }
    
    status_temp = SD_PollingCardStatusBusy(card, timeout_block*blockCount);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }
    return status_temp;
}


static void SD_configSDMABufferSize(sd_card_t *card, uint32_t *buffer, uint32_t blockCount)
{
    SDHOST_SDMA_Buffer_Size Size;
    uint32_t address = (uint32_t)buffer;
    
    if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x1000) <= 0x1000)
    {
        Size = SDHOST_SDMABUFFERSIZE_4KB;
    }
    else if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x2000) <= 0x2000)
    {
        Size = SDHOST_SDMABUFFERSIZE_8KB;
    }
    else if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x4000) <= 0x4000)
    {
        Size = SDHOST_SDMABUFFERSIZE_16KB;
    }
    else if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x8000) <= 0x8000)
    {
        Size = SDHOST_SDMABUFFERSIZE_32KB;
    }
    else if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x10000) <= 0x10000)
    {
        Size = SDHOST_SDMABUFFERSIZE_64KB;
    }
    else if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x20000) <= 0x20000)
    {
        Size = SDHOST_SDMABUFFERSIZE_128KB;
    }
    else if(blockCount * FSL_SDMMC_DEFAULT_BLOCK_SIZE + (address%0x40000) <= 0x40000)
    {
        Size = SDHOST_SDMABUFFERSIZE_256KB;
    }
    else
    {
        Size = SDHOST_SDMABUFFERSIZE_512KB;
    }
    SDMMC_ConfigSDMABufferSize(card->SDHOSTx,Size);
}

Status_card SD_ReadBlocks(sd_card_t *card, uint32_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    SDMMC_Transfer transfer;
    SDHOST_ADMAconfig dmaConfigtemp;
    SDHOST_ADMAconfig *dmaConfig;
    Status_card status_temp;
    
    if(startBlock + blockCount > card->sd_card_information.blockCount)
    {
        return Status_CardOutOfRange;
    }
    
    /* polling card status idle */
    status_temp = SD_PollingCardStatusBusy(card, SD_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }
      
    if(card->card_workmode.dma == SDMMC_NODMA)
    {
        dmaConfig = NULL;
    }
    else if(card->card_workmode.dma == SDMMC_SDMA)
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeSimple;
        dmaConfig->admaTable = NULL;
        dmaConfig->admaTableWords = 0;
        SD_configSDMABufferSize(card,buffer,blockCount);
    }
    else //ADMA
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeAdma2;  
        dmaConfig->admaTable = buffer;
        dmaConfig->admaTableWords = (*buffer & 0xFFFF0000) >> 16;
    }
    
    transfer.data.enableIgnoreError = DISABLE;
    transfer.data.dataType = SDHOST_TransferDataNormal;
    transfer.data.blockCount = blockCount;
    transfer.data.blockSize = FSL_SDMMC_DEFAULT_BLOCK_SIZE;
    transfer.data.rxData = buffer;
    transfer.data.txData = NULL;

    if(blockCount <= 1)
    {
        transfer.command.index = SDMMC_ReadSingleBlock;
        transfer.data.AutoCommand12_23 = NoAutoCommand;
    }
    else
    {
        transfer.command.index = SDMMC_ReadMultipleBlock;
        transfer.data.AutoCommand12_23 = AutoCommand12;
    }
    transfer.command.argument = startBlock;
    transfer.command.type = CARD_CommandTypeNormal;
    transfer.command.responseType = CARD_ResponseTypeR1;
    transfer.command.flags = 0x00;
    transfer.command.responseErrorFlags = 0x00;
    
    if(SDMMC_TransferBlocking(card->SDHOSTx,dmaConfig,&transfer,&card->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    else
    {
        status_temp = Status_Success;
    }

    return status_temp;
}


Status_card SD_WriteBlocks(sd_card_t *card, uint32_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    SDMMC_Transfer transfer;
    SDHOST_ADMAconfig *dmaConfig;
    SDHOST_ADMAconfig dmaConfigtemp;
    Status_card status_temp;
    
    if(startBlock + blockCount > card->sd_card_information.blockCount)
    {
        return Status_CardOutOfRange;
    }
    
    /* polling card status idle */
    status_temp = SD_PollingCardStatusBusy(card, SD_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }
    
    if(card->card_workmode.dma == SDMMC_NODMA)
    {
        dmaConfig = NULL;
    }
    else if(card->card_workmode.dma == SDMMC_SDMA)
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeSimple;
        dmaConfig->admaTable = NULL;
        dmaConfig->admaTableWords = 0;
        SD_configSDMABufferSize(card,buffer,blockCount);
    }
    else //ADMA
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeAdma2;  
        dmaConfig->admaTable = buffer;
        dmaConfig->admaTableWords = (*buffer & 0xFFFF0000) >> 16;
    }
    transfer.data.enableIgnoreError = DISABLE;
    transfer.data.dataType = SDHOST_TransferDataNormal;
    transfer.data.blockCount = blockCount;
    transfer.data.blockSize = FSL_SDMMC_DEFAULT_BLOCK_SIZE;
    transfer.data.rxData = NULL;
    transfer.data.txData = buffer;

    if(blockCount <= 1)
    {
        transfer.command.index = SDMMC_WriteSingleBlock;
        transfer.data.AutoCommand12_23 = NoAutoCommand;
    }
    else
    {
        transfer.command.index = SDMMC_WriteMultipleBlock;
        transfer.data.AutoCommand12_23 = AutoCommand12;
    }
    transfer.command.argument = startBlock;
    transfer.command.type = CARD_CommandTypeNormal;
    transfer.command.responseType = CARD_ResponseTypeR1;
    transfer.command.flags = 0x00;
    transfer.command.responseErrorFlags = 0x00;
    
    if(SDMMC_TransferBlocking(card->SDHOSTx,dmaConfig,&transfer,&card->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    else
    {
        status_temp = Status_Success;
    }
    
    return status_temp;
}


Status_card SD_SwitchVoltage(sd_card_t *card)
{
    Status_card status_temp = Status_Success;
    uint32_t Mscnt_value;
    uint32_t Mscnt_temp;
    if((card->sd_card_information.flags & SD_SupportVoltage180v) != SD_SupportVoltage180v) 
    {
        status_temp = Status_CardNotSupportYet;
    }
    
    /* CMD11 */
    else if(SD_NormalCMD_Send(card,SD_VoltageSwitch,0x00,CARD_ResponseTypeR1) != Status_Success)
    {
        status_temp = Status_Fail;
    }
    else
    {
        SDMMC_EnableSDCLK(card->SDHOSTx,DISABLE);
        /* delay 5ms */
        Mscnt_value = 0;
        SD_SysTick_start_time();
        Mscnt_temp = SD_systick_timeoutms;
        while(Mscnt_value<1)
        {
            Mscnt_value = SD_User_Time_Read(Mscnt_temp);
        }
        
        if(SDMMC_GetPresentFlagStatus(card->SDHOSTx,(SDHOST_Data0LineLevelFlag | SDHOST_Data1LineLevelFlag | 
            SDHOST_Data2LineLevelFlag | SDHOST_Data3LineLevelFlag)) == SET)
        {
            status_temp = Status_Fail;
            return status_temp;
        }
        
        SDMMC_EnableVolSwitch(card->SDHOSTx,ENABLE);
        /* delay 5ms */
        Mscnt_value = 0;
        SD_SysTick_start_time();
        Mscnt_temp = SD_systick_timeoutms;
        while(Mscnt_value<5)
        {
            Mscnt_value = SD_User_Time_Read(Mscnt_temp);
        }
        
        if((card->SDHOSTx->CTRLSTS & SDHOST_CTRLSTS_V18SE) != SDHOST_CTRLSTS_V18SE)
        {
            status_temp = Status_Fail;
        }
        else
        {
            SDMMC_EnableSDCLK(card->SDHOSTx,ENABLE);;
            /* Wait until the SD clock is stable. */
            SDMMC_WaitSDCLKStable(card->SDHOSTx);
            
            /* delay 1ms */
            Mscnt_value = 0;
            SD_SysTick_start_time();
            Mscnt_temp = SD_systick_timeoutms;
            while(Mscnt_value<1)
            {
                Mscnt_value = SD_User_Time_Read(Mscnt_temp);
            }
            
            if(SDMMC_GetPresentFlagStatus(card->SDHOSTx,(SDHOST_Data0LineLevelFlag | SDHOST_Data1LineLevelFlag | 
            SDHOST_Data2LineLevelFlag | SDHOST_Data3LineLevelFlag)) != SET)
            {
                status_temp = Status_Fail;
            }
        }
    }
    return status_temp;
}


void sd_delay(uint32_t cnt)
{
    while(cnt--);
}

static Status_card SD_SwitchFunction(sd_card_t *card,uint32_t mode)
{
    uint32_t card_scr[16];
    uint32_t cnt_value;
    SDMMC_Transfer transfer;
    Status_card status_temp = Status_Success;
    
    if(mode > 2)
    {
        mode = mode - 2;
    }

    SDMMC_EnableFlagStatus(card->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,DISABLE);
  
    transfer.data.AutoCommand12_23 = NoAutoCommand;
    transfer.data.enableIgnoreError = DISABLE;
    transfer.data.dataType = SDHOST_TransferDataNormal;
    transfer.data.blockCount = 1;
    transfer.data.blockSize = 64;
    transfer.data.rxData = card_scr;
    transfer.data.txData = NULL;

    transfer.command.index = SD_Switch;
    transfer.command.argument = (0x00fffff0U | mode);
    transfer.command.type = CARD_CommandTypeNormal;
    transfer.command.responseType = CARD_ResponseTypeR1;
    transfer.command.flags = 0x00;
    transfer.command.responseErrorFlags = 0x00;
    
    if(SDMMC_TransferBlocking(card->SDHOSTx,NULL,&transfer,&card->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    if(status_temp == Status_Success)
    {
        for(cnt_value = 0;cnt_value< 16; cnt_value++)
        {
            card_scr[cnt_value] = swap_uint32(card_scr[cnt_value]);
        }
        
        /* -card_scr[0U]---bit511~bit480;
           -card_scr[1U]---bit479~bit448;
           -card_scr[2U]---bit447~bit416;
           -card_scr[3U]---bit415~bit384;
           -card_scr[4U]---bit383~bit352;
           According to the "switch function status[bits 511~0]" return by switch command in mode "check function":
           -Check if function 1(high speed) in function group 1 is supported by checking if bit 401 is set;
           -check if function 1 is ready and can be switched by checking if bits 379~376 equal value 1;
       */
        if((((card_scr[3] >> 16) & (1 << mode)) == 0) || (((card_scr[4] & 0x0F000000) >> 24) != mode))
        {
            status_temp = Status_CardNotSupportYet;
        }
    }
    
    if(status_temp == Status_Success)
    {
        transfer.command.argument = (0x80fffff0U | mode);
        if(SDMMC_TransferBlocking(card->SDHOSTx,NULL,&transfer,&card->TMODE_truct) != SDMMC_SUCCESS)
        {
            status_temp = Status_Fail;
        }
        
        if(status_temp == Status_Success)
        {
            for(cnt_value = 0;cnt_value< 16; cnt_value++)
            {
                card_scr[cnt_value] = swap_uint32(card_scr[cnt_value]);
            }
            
            /* According to the "switch function status[bits 511~0]" return by switch command in mode "set function":
               -check if group 1 is successfully changed to function 1 by checking if bits 379~376 equal value 1;
             */
            if(((card_scr[4] & 0x0F000000) >> 24) != mode)
            {
                status_temp = Status_CardSwitchFailed;
            }
        }
    }
    
    SDMMC_EnableFlagStatus(card->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,ENABLE);
    return status_temp;
}


Status_card SD_SelectBusTiming(sd_card_t *card)
{
    Status_card status_temp;
    if((card->sd_card_information.version <= SD_SpecificationVersion1_0) || ((card->sd_card_information.csd.cardCommandClass & SD_CommandClassSwitch) != SD_CommandClassSwitch))
    {
        status_temp =  Status_CardNotSupportYet;
    }
    else
    {
        if((card->card_workmode.mode == SDMMC_DS) || (card->card_workmode.mode == SDMMC_HS))
        {
            status_temp = SD_SwitchFunction(card,card->card_workmode.mode);
        }
        else
        {
            if((card->sd_card_information.flags & SD_SupportVoltage180v) != SD_SupportVoltage180v)
            {
                status_temp =  Status_CardNotSupportYet;
            }
            else
            {
                status_temp = SD_SwitchFunction(card,card->card_workmode.mode);
            }
        }
    }
    return status_temp;
}

/** Read User Time Since Last Set
 *  param last time.
 */
uint32_t SD_User_Time_Read(uint32_t time)
{
    if(SD_systick_timeoutms>=time)
    {
       return SD_systick_timeoutms-time;
    }
    return(0xFFFFFFFF-time+SD_systick_timeoutms);
}

/** SD_SysTick_start_time. **/
void SD_SysTick_start_time(void)
{
    SD_systick_timeoutms = 0;

}






