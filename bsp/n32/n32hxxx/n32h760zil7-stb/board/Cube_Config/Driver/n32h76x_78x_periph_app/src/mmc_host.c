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
 * @file mmc_host.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "mmc_host.h"

static Status_card MMC_SendCardStatus(mmc_card_t* mmccard);
static void MMC_configSDMABufferSize(mmc_card_t *mmccard, uint32_t *buffer, uint32_t blockCount);
//static Status_card SD_SwitchFunction(mmc_card_t *mmccard,uint32_t mode);
static Status_card MMC_SetExtendedCsdConfig(mmc_card_t *mmccard, const mmc_extended_csd_config_t *config, uint32_t timeout);

/*  mmccard block erase time, varies according to different  cards */
#define MMC_BLOCKERASE_TIME  (250U)

uint32_t MMC_systick_timeoutms = 0;

Status_card MMC_NormalCMD_Send(mmc_card_t* mmccard, uint32_t index,uint32_t argument,SDMMC_CardRspType responseType)
{
    Status_card status_temp;
    
    mmccard->command.index = index;
    mmccard->command.argument = argument; 
    mmccard->command.type = CARD_CommandTypeNormal;
    mmccard->command.responseType = responseType;
    mmccard->command.flags = 0x00;
    mmccard->command.responseErrorFlags = 0x00;
    SDMMC_SendCommand(mmccard->SDHOSTx,&mmccard->command,&mmccard->TMODE_truct);
    if(SDMMC_WaitCommandDone(mmccard->SDHOSTx,&mmccard->command,ENABLE) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    else
    {
        status_temp = Status_Success;
    }
    return status_temp;
}


Status_card MMC_AutoCMD_Send(mmc_card_t* mmccard, uint32_t index,uint32_t argument,SDMMC_CardRspType responseType)
{
    Status_card status_temp = Status_Success;
    
    /* CMD55 */
    mmccard->command.index = SDMMC_ApplicationCommand;
    mmccard->command.argument = mmccard->mmc_card_information.rca << 16;
    mmccard->command.type = CARD_CommandTypeNormal;
    mmccard->command.responseType = CARD_ResponseTypeR1;
    mmccard->command.flags = 0x00;
    mmccard->command.responseErrorFlags = 0x00;
    SDMMC_SendCommand(mmccard->SDHOSTx,&mmccard->command,&mmccard->TMODE_truct);
    if(SDMMC_WaitCommandDone(mmccard->SDHOSTx,&mmccard->command,ENABLE) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    mmccard->command.index = index;
    mmccard->command.argument = argument; 
    mmccard->command.type = CARD_CommandTypeNormal;
    mmccard->command.responseType = responseType;
    mmccard->command.flags = 0x00;
    mmccard->command.responseErrorFlags = 0x00;
    SDMMC_SendCommand(mmccard->SDHOSTx,&mmccard->command,&mmccard->TMODE_truct);
    if(SDMMC_WaitCommandDone(mmccard->SDHOSTx,&mmccard->command,ENABLE) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    return status_temp;
}


void MMC_DecodeCid(mmc_card_t* mmccard)
{
    /* get cid */
    mmccard->mmc_card_information.cid.manufacturerID = (uint8_t)((mmccard->command.response[3U] & 0xFF000000U) >> 24U);
    mmccard->mmc_card_information.cid.applicationID  = (uint16_t)((mmccard->command.response[3U] & 0xFFFF00U) >> 8U);

    mmccard->mmc_card_information.cid.productName[0U] = (uint8_t)((mmccard->command.response[3U] & 0xFFU));
    mmccard->mmc_card_information.cid.productName[1U] = (uint8_t)((mmccard->command.response[2U] & 0xFF000000U) >> 24U);
    mmccard->mmc_card_information.cid.productName[2U] = (uint8_t)((mmccard->command.response[2U] & 0xFF0000U) >> 16U);
    mmccard->mmc_card_information.cid.productName[3U] = (uint8_t)((mmccard->command.response[2U] & 0xFF00U) >> 8U);
    mmccard->mmc_card_information.cid.productName[4U] = (uint8_t)((mmccard->command.response[2U] & 0xFFU));
	mmccard->mmc_card_information.cid.productName[5U] = (uint8_t)((mmccard->command.response[1U] & 0xFF000000U) >> 24U);

    mmccard->mmc_card_information.cid.productVersion = (uint8_t)((mmccard->command.response[1U] & 0xFF000000U) >> 16U);

    mmccard->mmc_card_information.cid.productSerialNumber = (uint32_t)((mmccard->command.response[1U] & 0xFFFFU) << 16U);
    mmccard->mmc_card_information.cid.productSerialNumber |= (uint32_t)((mmccard->command.response[0U] & 0xFFFF0000U) >> 16U);

    mmccard->mmc_card_information.cid.manufacturerData = (uint16_t)((mmccard->command.response[0U] & 0xFFF00U) >> 8U);
}


void MMC_DecodeCsd(mmc_card_t* mmccard)
{
	uint32_t multiplier;
	
    mmccard->mmc_card_information.csd.csdStructureVersion               = (uint8_t)((mmccard->command.response[3U] & 0xC0000000U) >> 30U);
	mmccard->mmc_card_information.csd.systemSpecificationVersion        = (uint8_t)((mmccard->command.response[3U] & 0x3C0000000U) >> 26U);
    mmccard->mmc_card_information.csd.dataReadAccessTime1 = (uint8_t)((mmccard->command.response[3U] & 0xFF0000U) >> 16U);
    mmccard->mmc_card_information.csd.dataReadAccessTime2 = (uint8_t)((mmccard->command.response[3U] & 0xFF00U) >> 8U);
    mmccard->mmc_card_information.csd.transferSpeed       = (uint8_t)(mmccard->command.response[3U] & 0xFFU);
    mmccard->mmc_card_information.csd.cardCommandClass    = (uint16_t)((mmccard->command.response[2U] & 0xFFF00000U) >> 20U);
    mmccard->mmc_card_information.csd.readBlockLength     = (uint8_t)((mmccard->command.response[2U] & 0xF0000U) >> 16U);
    if ((mmccard->command.response[2U] & 0x8000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdReadBlockPartialFlag;
    }
    if ((mmccard->command.response[2U] & 0x4000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdWriteBlockMisalignFlag;
    }
    if ((mmccard->command.response[2U] & 0x2000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdReadBlockMisalignFlag;
    }
    if ((mmccard->command.response[2U] & 0x1000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdDsrImplementedFlag;
    }
	
	mmccard->mmc_card_information.csd.deviceSize               = (uint16_t)(((mmccard->command.response[2U] & 0x3FFU) << 2U) + ((mmccard->command.response[1U] & 0xC0000000U) >> 30U));
    mmccard->mmc_card_information.csd.readCurrentVddMin        = (uint8_t)((mmccard->command.response[1U] & 0x38000000U) >> 27U);
    mmccard->mmc_card_information.csd.readCurrentVddMax        = (uint8_t)((mmccard->command.response[1U] & 0x07000000U) >> 24U);
    mmccard->mmc_card_information.csd.writeCurrentVddMin       = (uint8_t)((mmccard->command.response[1U] & 0x00E00000U) >> 21U);
    mmccard->mmc_card_information.csd.writeCurrentVddMax       = (uint8_t)((mmccard->command.response[1U] & 0x001C0000U) >> 18U);
    mmccard->mmc_card_information.csd.deviceSizeMultiplier     = (uint8_t)((mmccard->command.response[1U] & 0x00038000U) >> 15U);
    mmccard->mmc_card_information.csd.eraseGroupSize           = (uint8_t)((mmccard->command.response[1U] & 0x00007C00U) >> 10U);
    mmccard->mmc_card_information.csd.eraseGroupSizeMultiplier = (uint8_t)((mmccard->command.response[1U] & 0x000003E0U) >> 5U);
    mmccard->mmc_card_information.csd.writeProtectGroupSize    = (uint8_t)(mmccard->command.response[1U] & 0x0000001FU);
    if ((mmccard->command.response[0U] & 0x80000000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdWriteProtectGroupEnabledFlag;
    }
    mmccard->mmc_card_information.csd.defaultEcc          = (uint8_t)((mmccard->command.response[0U] & 0x60000000U) >> 29U);
    mmccard->mmc_card_information.csd.writeSpeedFactor    = (uint8_t)((mmccard->command.response[0U] & 0x1C000000U) >> 26U);
    mmccard->mmc_card_information.csd.maxWriteBlockLength = (uint8_t)((mmccard->command.response[0U] & 0x03C00000U) >> 22U);
    if ((mmccard->command.response[0U] & 0x00200000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdWriteBlockPartialFlag;
    }
    if ((mmccard->command.response[0U] & 0x00010000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_ContentProtectApplicationFlag;
    }
    if ((mmccard->command.response[0U] & 0x00008000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdFileFormatGroupFlag;
    }
    if ((mmccard->command.response[0U] & 0x00004000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdCopyFlag;
    }
    if ((mmccard->command.response[0U] & 0x00002000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdPermanentWriteProtectFlag;
    }
    if ((mmccard->command.response[0U] & 0x00001000U) != 0U)
    {
        mmccard->mmc_card_information.csd.flags |= (uint16_t)MMC_CsdTemporaryWriteProtectFlag;
    }
    mmccard->mmc_card_information.csd.fileFormat = (uint8_t)((mmccard->command.response[0U] & 0x00000C00U) >> 10U);
    mmccard->mmc_card_information.csd.eccCode    = (uint8_t)((mmccard->command.response[0U] & 0x00000300U) >> 8U);

    /* Calculate the device total block count. */
    /* For the card capacity of witch higher than 2GB, the maximum possible value should be set to this register
    is 0xFFF. */
    if (mmccard->mmc_card_information.csd.deviceSize != 0xFFFU)
    {
        multiplier                = (2UL << (mmccard->mmc_card_information.csd.deviceSizeMultiplier + 2U - 1U));
        mmccard->mmc_card_information.userPartitionBlocks = (((mmccard->mmc_card_information.csd.deviceSize + 1UL) * multiplier) / FSL_SDMMC_DEFAULT_BLOCK_SIZE);
    }

    mmccard->mmc_card_information.blockSize = FSL_SDMMC_DEFAULT_BLOCK_SIZE;
}

static Status_card MMC_SendCardStatus(mmc_card_t* mmccard)
{
    Status_card status_temp;
    uint32_t retry               = MMC_CMD13_RETRY_TIMES;
    while(retry != 0U)
    {
        /* CMD13 */
        if(MMC_NormalCMD_Send(mmccard,SDMMC_SendStatus,mmccard->mmc_card_information.rca << 16,CARD_ResponseTypeR1) != Status_Success)
        {
            if(SDMMC_GetPresentFlagStatus(mmccard->SDHOSTx,SDHOST_CommandInhibitFlag))
            {
                SDMMC_SoftWareReset(mmccard->SDHOSTx,SDHOST_SOFTWARE_CMDLINE);
            }
            status_temp = Status_Fail;
            retry--;
        }
        else
        {
            if(((mmccard->command.response[0] & SDMMC_MASK(SDMMC_R1ReadyForDataFlag)) != 0U) &&
                (SDMMC_R1_CURRENT_STATE(mmccard->command.response[0U]) != (uint32_t)SDMMC_R1StateProgram))
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

Status_card MMC_PollingCardStatusBusy(mmc_card_t* mmccard,uint32_t timeoutMs)
{
    uint32_t timeout_temp;
    uint32_t timeout_cnt = 0;
    bool cardBusy            = false;
    Status_card status_temp  = Status_CardStatusBusy;

    MMC_SysTick_start_time();
    timeout_temp = MMC_systick_timeoutms;
    while(timeout_cnt < timeoutMs)
    {
        if(SDMMC_GetPresentFlagStatus(mmccard->SDHOSTx,SDHOST_Data0LineLevelFlag) == SET)
        {
            cardBusy = false;
        }
        else
        {
            cardBusy = true;
        }

        if (cardBusy == false)
        {
            status_temp = MMC_SendCardStatus(mmccard);
            if (status_temp == Status_CardStatusIdle)
            {
                break;
            }
        }
        
        timeout_cnt = MMC_User_Time_Read(timeout_temp);
    }
    
    if(SDMMC_GetFlagStatus(mmccard->SDHOSTx,SDHOST_DataCompleteFlag) == SET)
    {
        SDMMC_ClrFlag(mmccard->SDHOSTx,SDHOST_DataCompleteFlag);
    }

    return status_temp;
}

static Status_card MMC_SetExtendedCsdConfig(mmc_card_t *mmccard, const mmc_extended_csd_config_t *config, uint32_t timeout)
{
    Status_card status_temp;
    uint32_t parameter           = 0U;
    uint32_t timeoutMS           = timeout == 0U ? mmccard->mmc_card_information.extendedCsd.genericCMD6Timeout : timeout;

    parameter |= ((uint32_t)(config->commandSet) << MMC_SWITCH_COMMAND_SET_SHIFT);
    parameter |= ((uint32_t)(config->ByteValue) << MMC_SWITCH_VALUE_SHIFT);
    parameter |= ((uint32_t)(config->ByteIndex) << MMC_SWITCH_BYTE_INDEX_SHIFT);
    parameter |= ((uint32_t)(config->accessMode) << MMC_SWITCH_ACCESS_MODE_SHIFT);
	
    /* CMD6 */
    if(MMC_NormalCMD_Send(mmccard,MMC_Switch,parameter,CARD_ResponseTypeR1b) != Status_Success)
    {
        return Status_Fail;
    }

    /* Wait for the card write process complete because of that card read process and write process use one buffer. */
    status_temp = MMC_PollingCardStatusBusy(mmccard, timeoutMS == 0U ? MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT : timeoutMS);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }

    return Status_Success;
}

Status_card MMC_SetMaxEraseUnitSize(mmc_card_t* mmccard)
{
    uint32_t erase_group_size;
    uint32_t erase_group_multiplier;
	mmc_extended_csd_config_t extendedCsdconfig;
	
	/* Legacy mmc card , do not support the command */
    if ((mmccard->mmc_card_information.csd.systemSpecificationVersion == (uint32_t)MMC_SpecificationVersion3) &&
        (mmccard->mmc_card_information.csd.csdStructureVersion == (uint32_t)MMC_CsdStrucureVersion12))
    {
        return Status_Success;
    }
	
	if(((mmccard->mmc_card_information.flags & MMC_SupportHighCapacityFlag) == 0U)  || 
		(mmccard->mmc_card_information.extendedCsd.highCapacityEraseUnitSize == 0U) ||
		(mmccard->mmc_card_information.extendedCsd.highCapacityEraseTimeout == 0U))
	{
		erase_group_size       = mmccard->mmc_card_information.csd.eraseGroupSize;
        erase_group_multiplier = mmccard->mmc_card_information.csd.eraseGroupSizeMultiplier;
        mmccard->mmc_card_information.eraseGroupBlocks = ((erase_group_size + 1U) * (erase_group_multiplier + 1U));
	}
	else
	{
		/* Erase Unit Size = 512Kbyte * HC_ERASE_GRP_SIZE. Block size is 512 bytes. */
        mmccard->mmc_card_information.eraseGroupBlocks = (mmccard->mmc_card_information.extendedCsd.highCapacityEraseUnitSize * 1024UL);
		
		/* Enable high capacity erase unit size. */
        extendedCsdconfig.accessMode = MMC_ExtendedCsdAccessModeSetBits;
        extendedCsdconfig.ByteIndex  = (uint8_t)MMC_ExtendedCsdIndexEraseGroupDefinition;
        extendedCsdconfig.ByteValue  = 0x01U; /* The high capacity erase unit size enable bit is bit 0 */
        extendedCsdconfig.commandSet = MMC_CommandSetStandard;
		if (Status_Success != MMC_SetExtendedCsdConfig(mmccard, &extendedCsdconfig, 0U))
        {
            return Status_Fail;
        }
	}

    return Status_Success;
}



Status_card MMC_SendExtCsd(mmc_card_t* mmccard)
{
    uint32_t card_ExtCsd[512/4];
	uint8_t* ExtCsd_temp;
    SDMMC_Transfer transfer;
    Status_card status_temp = Status_Success;
	
	/* Legacy mmc card , do not support the command */
    if ((mmccard->mmc_card_information.csd.systemSpecificationVersion == (uint32_t)MMC_SpecificationVersion3) &&
        (mmccard->mmc_card_information.csd.csdStructureVersion == (uint32_t)MMC_CsdStrucureVersion12))
    {
        return status_temp;
    }

    SDMMC_EnableFlagStatus(mmccard->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,DISABLE);

    transfer.data.AutoCommand12_23 = NoAutoCommand;
    transfer.data.enableIgnoreError = ENABLE;
    transfer.data.dataType = SDHOST_TransferDataNormal;
    transfer.data.blockCount = 1;
    transfer.data.blockSize = 512;
    transfer.data.rxData = card_ExtCsd;
    transfer.data.txData = NULL;

    transfer.command.index = MMC_SendExtendedCsd;
    transfer.command.argument = 0x00;
    transfer.command.type = CARD_CommandTypeNormal;
    transfer.command.responseType = CARD_ResponseTypeR1;
    transfer.command.flags = 0x00;
    transfer.command.responseErrorFlags = 0x00;
    
    if(SDMMC_TransferBlocking(mmccard->SDHOSTx,NULL,&transfer,&mmccard->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    
    if(status_temp == Status_Success)
    {
		ExtCsd_temp = (uint8_t*)card_ExtCsd;
		
		/* Extended CSD is transferred as a data block from least byte indexed 0. */
		mmccard->mmc_card_information.extendedCsd.bootPartitionWP                 = ExtCsd_temp[173U];
		mmccard->mmc_card_information.extendedCsd.bootWPStatus                    = ExtCsd_temp[174U];
		mmccard->mmc_card_information.extendedCsd.highDensityEraseGroupDefinition = ExtCsd_temp[175U];
		mmccard->mmc_card_information.extendedCsd.bootDataBusConditions           = ExtCsd_temp[177U];
		mmccard->mmc_card_information.extendedCsd.bootConfigProtect               = ExtCsd_temp[178U];
		mmccard->mmc_card_information.extendedCsd.partitionConfig                 = ExtCsd_temp[179U];
		mmccard->mmc_card_information.extendedCsd.eraseMemoryContent              = ExtCsd_temp[181U];
		mmccard->mmc_card_information.extendedCsd.dataBusWidth                    = ExtCsd_temp[183U];
		mmccard->mmc_card_information.extendedCsd.highSpeedTiming                 = ExtCsd_temp[185U];
		mmccard->mmc_card_information.extendedCsd.powerClass                      = ExtCsd_temp[187U];
		mmccard->mmc_card_information.extendedCsd.commandSetRevision              = ExtCsd_temp[189U];
		mmccard->mmc_card_information.extendedCsd.commandSet                      = ExtCsd_temp[191U];
		mmccard->mmc_card_information.extendedCsd.extendecCsdVersion              = ExtCsd_temp[192U];
		mmccard->mmc_card_information.extendedCsd.csdStructureVersion             = ExtCsd_temp[194U];
		mmccard->mmc_card_information.extendedCsd.partitionAttribute              = ExtCsd_temp[156U];
		mmccard->mmc_card_information.extendedCsd.extPartitionSupport             = ExtCsd_temp[494U];
		mmccard->mmc_card_information.extendedCsd.cardType                        = ExtCsd_temp[196U];
		/* This field define the type of the card. The only currently valid values for this field are 0x01 and 0x03. */
		mmccard->mmc_card_information.flags |= mmccard->mmc_card_information.extendedCsd.cardType;

		mmccard->mmc_card_information.extendedCsd.ioDriverStrength = ExtCsd_temp[197U];

		mmccard->mmc_card_information.extendedCsd.partitionSwitchTimeout                    = ExtCsd_temp[199U];
		mmccard->mmc_card_information.extendedCsd.powerClass52MHz195V                       = ExtCsd_temp[200U];
		mmccard->mmc_card_information.extendedCsd.powerClass26MHz195V                       = ExtCsd_temp[201U];
		mmccard->mmc_card_information.extendedCsd.powerClass52MHz360V                       = ExtCsd_temp[202U];
		mmccard->mmc_card_information.extendedCsd.powerClass26MHz360V                       = ExtCsd_temp[203U];
		mmccard->mmc_card_information.extendedCsd.powerClass200MHZVCCQ130VVCC360V           = ExtCsd_temp[236U];
		mmccard->mmc_card_information.extendedCsd.powerClass200MHZVCCQ195VVCC360V           = ExtCsd_temp[237U];
		mmccard->mmc_card_information.extendedCsd.powerClass52MHZDDR195V                    = ExtCsd_temp[238U];
		mmccard->mmc_card_information.extendedCsd.powerClass52MHZDDR360V                    = ExtCsd_temp[239U];
		mmccard->mmc_card_information.extendedCsd.powerClass200MHZDDR360V                   = ExtCsd_temp[253U];
		mmccard->mmc_card_information.extendedCsd.minimumReadPerformance4Bit26MHz           = ExtCsd_temp[205U];
		mmccard->mmc_card_information.extendedCsd.minimumWritePerformance4Bit26MHz          = ExtCsd_temp[206U];
		mmccard->mmc_card_information.extendedCsd.minimumReadPerformance8Bit26MHz4Bit52MHz  = ExtCsd_temp[207U];
		mmccard->mmc_card_information.extendedCsd.minimumWritePerformance8Bit26MHz4Bit52MHz = ExtCsd_temp[208U];
		mmccard->mmc_card_information.extendedCsd.minimumReadPerformance8Bit52MHz           = ExtCsd_temp[209U];
		mmccard->mmc_card_information.extendedCsd.minimumWritePerformance8Bit52MHz          = ExtCsd_temp[210U];
		mmccard->mmc_card_information.extendedCsd.minReadPerformance8bitAt52MHZDDR          = ExtCsd_temp[234U];
		mmccard->mmc_card_information.extendedCsd.minWritePerformance8bitAt52MHZDDR         = ExtCsd_temp[235U];
		/* Get user partition size. */
		mmccard->mmc_card_information.extendedCsd.sectorCount = ((((uint32_t)ExtCsd_temp[215U]) << 24U) + (((uint32_t)ExtCsd_temp[214U]) << 16U) +
									(((uint32_t)ExtCsd_temp[213U]) << 8U) + (uint32_t)ExtCsd_temp[212U]);
		if ((mmccard->mmc_card_information.flags & (uint32_t)MMC_SupportHighCapacityFlag) != 0U)
		{
			mmccard->mmc_card_information.userPartitionBlocks = mmccard->mmc_card_information.extendedCsd.sectorCount;
		}

		mmccard->mmc_card_information.extendedCsd.sleepAwakeTimeout                 = ExtCsd_temp[217U];
		mmccard->mmc_card_information.extendedCsd.sleepCurrentVCCQ                  = ExtCsd_temp[219U];
		mmccard->mmc_card_information.extendedCsd.sleepCurrentVCC                   = ExtCsd_temp[220U];
		mmccard->mmc_card_information.extendedCsd.highCapacityWriteProtectGroupSize = ExtCsd_temp[221U];
		mmccard->mmc_card_information.extendedCsd.reliableWriteSectorCount          = ExtCsd_temp[222U];
		mmccard->mmc_card_information.extendedCsd.highCapacityEraseTimeout          = ExtCsd_temp[223U];
		mmccard->mmc_card_information.extendedCsd.highCapacityEraseUnitSize         = ExtCsd_temp[224U];
		mmccard->mmc_card_information.extendedCsd.accessSize                        = ExtCsd_temp[225U];

		/* Get boot partition size: 128KB * BOOT_SIZE_MULT*/
		mmccard->mmc_card_information.bootPartitionBlocks = ((128U * 1024U * ExtCsd_temp[226U]) / FSL_SDMMC_DEFAULT_BLOCK_SIZE);

		/* support HS400 data strobe */
		if (ExtCsd_temp[184] == 1U)
		{
			mmccard->mmc_card_information.flags |= (uint32_t)MMC_SupportEnhanceHS400StrobeFlag;
		}

		/* Check if card support boot mode. */
		if ((ExtCsd_temp[228U] & 0x1U) != 0U)
		{
			mmccard->mmc_card_information.flags |= (uint32_t)MMC_SupportAlternateBootFlag;
		}
		else if ((ExtCsd_temp[228U] & 0x2U) != 0U)
		{
			mmccard->mmc_card_information.flags |= (uint32_t)MMC_SupportDDRBootFlag;
		}
		else if ((ExtCsd_temp[228U] & 0x4U) != 0U)
		{
			mmccard->mmc_card_information.flags |= (uint32_t)MMC_SupportHighSpeedBootFlag;
		}
		else
		{
			/* empty with intentional */
		}
		/* cache size unit 1kb */
		mmccard->mmc_card_information.extendedCsd.cacheSize = (((uint32_t)ExtCsd_temp[252U]) << 24) | (((uint32_t)ExtCsd_temp[251U]) << 16) |
								 (((uint32_t)ExtCsd_temp[250U]) << 8) | (((uint32_t)ExtCsd_temp[249U]));

		mmccard->mmc_card_information.extendedCsd.genericCMD6Timeout  = ExtCsd_temp[248U] * 10UL;
		mmccard->mmc_card_information.extendedCsd.supportedCommandSet = ExtCsd_temp[504U];
		
		
        status_temp = Status_Success;
    }
    SDMMC_EnableFlagStatus(mmccard->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,ENABLE);

    return status_temp;
}

static Status_card MMC_CheckEraseGroupRange(mmc_card_t *mmccard, uint32_t startGroup, uint32_t endGroup)
{
    Status_card status_temp = Status_Success;
    uint32_t partitionBlocks;
    uint32_t eraseGroupBoundary;

	partitionBlocks = mmccard->mmc_card_information.userPartitionBlocks;

	/* Check if current partition's total block count is integer multiples of the erase group size. */
	if ((partitionBlocks % mmccard->mmc_card_information.eraseGroupBlocks) == 0U)
	{
		eraseGroupBoundary = (partitionBlocks / mmccard->mmc_card_information.eraseGroupBlocks);
	}
	else
	{
		/* mmccard will ignore the unavailable blocks within the last erase group automatically. */
		eraseGroupBoundary = (partitionBlocks / mmccard->mmc_card_information.eraseGroupBlocks + 1U);
	}

	/* Check if the group range accessed is within current partition's erase group boundary. */
	if ((startGroup > eraseGroupBoundary) || (endGroup > eraseGroupBoundary))
	{
		status_temp = Status_CardOutOfRange;
	}

    return status_temp;
}


Status_card MMC_EraseGroups(mmc_card_t* mmccard, uint32_t startGroup, uint32_t endGroup)
{
    uint32_t startGroupAddress;
    uint32_t endGroupAddress; 
    Status_card status_temp  = Status_CardStatusBusy;
    uint32_t timeout_value = MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT; 
	
	status_temp = MMC_CheckEraseGroupRange(mmccard, startGroup, endGroup);
	if(status_temp != Status_Success)
	{
		status_temp =  Status_CardOutOfRange;
	}
	else
	{
		/* polling mmccard status idle */
		status_temp = MMC_PollingCardStatusBusy(mmccard, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
		if (Status_CardStatusIdle != status_temp)
		{
			status_temp =  Status_PollingCardIdleFailed;
		}
	}
    
	if(status_temp == Status_CardStatusIdle)
	{
		/* Calculate the start group address and end group address */
        startGroupAddress = startGroup;
        endGroupAddress   = endGroup;
		if ((mmccard->mmc_card_information.flags & (uint32_t)MMC_SupportHighCapacityFlag) != 0U)
        {
            /* The implementation of a higher than 2GB of density of memory will not be backwards compatible with the
            lower densities.First of all the address argument for higher than 2GB of density of memory is changed to
            be sector address (512B sectors) instead of byte address */
            startGroupAddress = (startGroupAddress * (mmccard->mmc_card_information.eraseGroupBlocks));
            endGroupAddress   = (endGroupAddress * (mmccard->mmc_card_information.eraseGroupBlocks));
        }
        else
        {
            /* The address unit is byte when card capacity is lower than 2GB */
            startGroupAddress = (startGroupAddress * (mmccard->mmc_card_information.eraseGroupBlocks) * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
            endGroupAddress   = (endGroupAddress * (mmccard->mmc_card_information.eraseGroupBlocks) * FSL_SDMMC_DEFAULT_BLOCK_SIZE);
        }
		
		/* CMD35 */
		if(MMC_NormalCMD_Send(mmccard,MMC_EraseGroupStart,startGroupAddress,CARD_ResponseTypeR1) != Status_Success)    
		{
			return Status_Fail;
		}
		
		/* CMD36 */
		if(MMC_NormalCMD_Send(mmccard,MMC_EraseGroupEnd,endGroupAddress,CARD_ResponseTypeR1) != Status_Success)
		{
			return Status_Fail;
		}
		
		/* CMD38 */
		if(MMC_NormalCMD_Send(mmccard,SDMMC_Erase,0x00,CARD_ResponseTypeR1b) != Status_Success)
		{
			return Status_Fail;
		}
		
		if ((0U != (mmccard->mmc_card_information.flags & (uint32_t)MMC_SupportHighCapacityFlag)) &&
			(mmccard->mmc_card_information.extendedCsd.highCapacityEraseTimeout != 0U))
		{
			timeout_value =
				(uint32_t)mmccard->mmc_card_information.extendedCsd.highCapacityEraseTimeout * 300U * (endGroup - startGroup + 1U);
		}

		status_temp = MMC_PollingCardStatusBusy(mmccard, timeout_value);
		if (Status_CardStatusIdle != status_temp)
		{
			status_temp = Status_PollingCardIdleFailed;
		}
		else
		{
			status_temp = Status_Success;
		}
	}
	
    return status_temp;
}


static void MMC_configSDMABufferSize(mmc_card_t *mmccard, uint32_t *buffer, uint32_t blockCount)
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
    SDMMC_ConfigSDMABufferSize(mmccard->SDHOSTx,Size);
}

Status_card MMC_ReadBlocks(mmc_card_t *mmccard, uint32_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    SDMMC_Transfer transfer;
    SDHOST_ADMAconfig dmaConfigtemp;
    SDHOST_ADMAconfig *dmaConfig;
    Status_card status_temp;
    
    if(startBlock + blockCount > mmccard->mmc_card_information.userPartitionBlocks)
    {
        return Status_CardOutOfRange;
    }
    
    /* polling mmccard status idle */
    status_temp = MMC_PollingCardStatusBusy(mmccard, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }
      
    if(mmccard->card_workmode.dma == SDMMC_NODMA)
    {
        dmaConfig = NULL;
    }
    else if(mmccard->card_workmode.dma == SDMMC_SDMA)
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeSimple;
        dmaConfig->admaTable = NULL;
        dmaConfig->admaTableWords = 0;
        MMC_configSDMABufferSize(mmccard,buffer,blockCount);
    }
    else //ADMA
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeAdma2;  
        dmaConfig->admaTable = buffer;
        dmaConfig->admaTableWords = (*buffer & 0xFFFF0000) >> 16;
    }
    
    transfer.data.enableIgnoreError = ENABLE;
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
    
    if(SDMMC_TransferBlocking(mmccard->SDHOSTx,dmaConfig,&transfer,&mmccard->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    else
    {
        status_temp = Status_Success;
    }

    return status_temp;
}


Status_card MMC_WriteBlocks(mmc_card_t *mmccard, uint32_t *buffer, uint32_t startBlock, uint32_t blockCount)
{
    SDMMC_Transfer transfer;
    SDHOST_ADMAconfig *dmaConfig;
    SDHOST_ADMAconfig dmaConfigtemp;
    Status_card status_temp;
    
    if(startBlock + blockCount > mmccard->mmc_card_information.userPartitionBlocks)
    {
        return Status_CardOutOfRange;
    }
    
    /* polling mmccard status idle */
    status_temp = MMC_PollingCardStatusBusy(mmccard, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_PollingCardIdleFailed;
    }
    
    if(mmccard->card_workmode.dma == SDMMC_NODMA)
    {
        dmaConfig = NULL;
    }
    else if(mmccard->card_workmode.dma == SDMMC_SDMA)
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeSimple;
        dmaConfig->admaTable = NULL;
        dmaConfig->admaTableWords = 0;
        MMC_configSDMABufferSize(mmccard,buffer,blockCount);
    }
    else //ADMA
    {
        dmaConfig = &dmaConfigtemp;
        dmaConfig->dmaMode = DmaModeAdma2;  
        dmaConfig->admaTable = buffer;
        dmaConfig->admaTableWords = (*buffer & 0xFFFF0000) >> 16;
    }
    transfer.data.enableIgnoreError = ENABLE;
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
    
    if(SDMMC_TransferBlocking(mmccard->SDHOSTx,dmaConfig,&transfer,&mmccard->TMODE_truct) != SDMMC_SUCCESS)
    {
        status_temp = Status_Fail;
    }
    else
    {
        status_temp = Status_Success;
    }
    
    return status_temp;
}


Status_card MMC_SwitchVoltage(mmc_card_t *mmccard)
{
    Status_card status_temp = Status_Success;
    uint32_t Mscnt_value;
    uint32_t Mscnt_temp;
    if((mmccard->mmc_card_information.flags & SD_SupportVoltage180v) != SD_SupportVoltage180v) 
    {
        status_temp = Status_CardNotSupportYet;
    }
    
    /* CMD11 */
    else if(MMC_NormalCMD_Send(mmccard,SD_VoltageSwitch,0x00,CARD_ResponseTypeR1) != Status_Success)
    {
        status_temp = Status_Fail;
    }
    else
    {
        SDMMC_EnableSDCLK(mmccard->SDHOSTx,DISABLE);
        /* delay 5ms */
        Mscnt_value = 0;
        MMC_SysTick_start_time();
        Mscnt_temp = MMC_systick_timeoutms;
        while(Mscnt_value<1)
        {
            Mscnt_value = MMC_User_Time_Read(Mscnt_temp);
        }

        
        if(SDMMC_GetPresentFlagStatus(mmccard->SDHOSTx,(SDHOST_Data0LineLevelFlag | SDHOST_Data1LineLevelFlag | 
            SDHOST_Data2LineLevelFlag | SDHOST_Data3LineLevelFlag)) == SET)
        {
            status_temp = Status_Fail;
            return status_temp;
        }
        
        SDMMC_EnableVolSwitch(mmccard->SDHOSTx,ENABLE);
        /* delay 5ms */
        Mscnt_value = 0;
        MMC_SysTick_start_time();
        Mscnt_temp = MMC_systick_timeoutms;
        while(Mscnt_value<5)
        {
            Mscnt_value = MMC_User_Time_Read(Mscnt_temp);
        }
        
        if((mmccard->SDHOSTx->CTRLSTS & SDHOST_CTRLSTS_V18SE) != SDHOST_CTRLSTS_V18SE)
        {
            status_temp = Status_Fail;
        }
        else
        {
            SDMMC_EnableSDCLK(mmccard->SDHOSTx,ENABLE);;
            /* Wait until the  clock is stable. */
            SDMMC_WaitSDCLKStable(mmccard->SDHOSTx);
            
            /* delay 1ms */
            Mscnt_value = 0;
            MMC_SysTick_start_time();
            Mscnt_temp = MMC_systick_timeoutms;
            while(Mscnt_value<1)
            {
                Mscnt_value = MMC_User_Time_Read(Mscnt_temp);
            }
            
            if(SDMMC_GetPresentFlagStatus(mmccard->SDHOSTx,(SDHOST_Data0LineLevelFlag | SDHOST_Data1LineLevelFlag | 
            SDHOST_Data2LineLevelFlag | SDHOST_Data3LineLevelFlag)) != SET)
            {
                status_temp = Status_Fail;
            }
        }
    }
    return status_temp;
}


//static Status_card SD_SwitchFunction(mmc_card_t *mmccard,uint32_t mode)
//{
//    uint32_t card_scr[16];
//    uint32_t cnt_value;
//    SDMMC_Transfer transfer;
//    Status_card status_temp = Status_Success;
//    
//    if(mode > 2)
//    {
//        mode = mode - 2;
//    }

//    SDMMC_EnableFlagStatus(mmccard->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,DISABLE);
//  
//    transfer.data.AutoCommand12_23 = NoAutoCommand;
//    transfer.data.enableIgnoreError = DISABLE;
//    transfer.data.dataType = SDHOST_TransferDataNormal;
//    transfer.data.blockCount = 1;
//    transfer.data.blockSize = 64;
//    transfer.data.rxData = card_scr;
//    transfer.data.txData = NULL;

//    transfer.command.index = SD_Switch;
//    transfer.command.argument = (0x00fffff0U | mode);
//    transfer.command.type = CARD_CommandTypeNormal;
//    transfer.command.responseType = CARD_ResponseTypeR1;
//    transfer.command.flags = 0x00;
//    transfer.command.responseErrorFlags = 0x00;
//    
//    if(SDMMC_TransferBlocking(mmccard->SDHOSTx,NULL,&transfer,&mmccard->TMODE_truct) != SDMMC_SUCCESS)
//    {
//        status_temp = Status_Fail;
//    }
//    
//    if(status_temp == Status_Success)
//    {
//        for(cnt_value = 0;cnt_value< 16; cnt_value++)
//        {
//            card_scr[cnt_value] = swap_uint32(card_scr[cnt_value]);
//        }
//        
//        /* -card_scr[0U]---bit511~bit480;
//           -card_scr[1U]---bit479~bit448;
//           -card_scr[2U]---bit447~bit416;
//           -card_scr[3U]---bit415~bit384;
//           -card_scr[4U]---bit383~bit352;
//           According to the "switch function status[bits 511~0]" return by switch command in mode "check function":
//           -Check if function 1(high speed) in function group 1 is supported by checking if bit 401 is set;
//           -check if function 1 is ready and can be switched by checking if bits 379~376 equal value 1;
//       */
//        if((((card_scr[3] >> 16) & (1 << mode)) == 0) || (((card_scr[4] & 0x0F000000) >> 24) != mode))
//        {
//            log_info("\r\nError: current mmccard not support function %d\r\n", mode);
//            status_temp = Status_CardNotSupportYet;
//        }
//    }
//    
//    if(status_temp == Status_Success)
//    {
//        transfer.command.argument = (0x80fffff0U | mode);
//        if(SDMMC_TransferBlocking(mmccard->SDHOSTx,NULL,&transfer,&mmccard->TMODE_truct) != SDMMC_SUCCESS)
//        {
//            status_temp = Status_Fail;
//        }
//        
//        if(status_temp == Status_Success)
//        {
//            for(cnt_value = 0;cnt_value< 16; cnt_value++)
//            {
//                card_scr[cnt_value] = swap_uint32(card_scr[cnt_value]);
//            }
//            
//            /* According to the "switch function status[bits 511~0]" return by switch command in mode "set function":
//               -check if group 1 is successfully changed to function 1 by checking if bits 379~376 equal value 1;
//             */
//            if(((card_scr[4] & 0x0F000000) >> 24) != mode)
//            {
//                log_info("\r\nError: switch to function %d failed\r\n", mode);
//                status_temp = Status_CardSwitchFailed;
//            }
//        }
//    }
//    
//    SDMMC_EnableFlagStatus(mmccard->SDHOSTx,SDHOST_DataErrorFlag | SDHOST_CommandErrorFlag,ENABLE);
//    return status_temp;
//}


static Status_card MMC_SetMaxDataBusWidth(mmc_card_t *mmccard)
{
    Status_card status_temp = Status_Success;
	mmc_extended_csd_config_t extendedCsdconfig;
	
	extendedCsdconfig.accessMode = MMC_ExtendedCsdAccessModeWriteBits;
	extendedCsdconfig.ByteIndex  = (uint8_t)MMC_ExtendedCsdIndexBusWidth;
	extendedCsdconfig.ByteValue  = (uint8_t)MMC_DataBusWidth8bitDDR;
	extendedCsdconfig.commandSet = MMC_CommandSetStandard;

	if (mmccard->card_workmode.busWidth == MMC_DataBusWidth8bitDDR)
	{
		if(0U != (mmccard->mmc_card_information.flags & ((uint32_t)MMC_SupportHighSpeedDDR52MHZ180V300VFlag |
								   (uint32_t)MMC_SupportHighSpeedDDR52MHZ120VFlag)))
		{
			/* Set data bus width */
			extendedCsdconfig.ByteValue  = (uint8_t)MMC_DataBusWidth8bitDDR;
			if(MMC_SetExtendedCsdConfig(mmccard,&extendedCsdconfig, 0U) != Status_Success)
			{
				status_temp = Status_Fail;
			}
			else
			{
				SDMMC_ConfigBusWidth(mmccard->SDHOSTx, SDHOST_DataBusWidth8Bit);
				status_temp = Status_Success;
				mmccard->mmc_card_information.extendedCsd.dataBusWidth = MMC_DataBusWidth8bitDDR;
			}
		}
		else
		{
			status_temp = Status_CardNotSupportYet;
		}
	}

	if (mmccard->card_workmode.busWidth == MMC_DataBusWidth4bitDDR)
	{
		if(0U != (mmccard->mmc_card_information.flags & ((uint32_t)MMC_SupportHighSpeedDDR52MHZ180V300VFlag |
								   (uint32_t)MMC_SupportHighSpeedDDR52MHZ120VFlag)))
		{
			/* Set data bus width */
			extendedCsdconfig.ByteValue  = (uint8_t)MMC_DataBusWidth4bitDDR;
			if(MMC_SetExtendedCsdConfig(mmccard,&extendedCsdconfig, 0U) != Status_Success)
			{
				status_temp = Status_Fail;
			}
			else
			{
				SDMMC_ConfigBusWidth(mmccard->SDHOSTx, SDHOST_DataBusWidth4Bit);
				status_temp = Status_Success;
				mmccard->mmc_card_information.extendedCsd.dataBusWidth = MMC_DataBusWidth4bitDDR;
			}
		}
		else
		{
			status_temp = Status_CardNotSupportYet;
		}
	}

	if (mmccard->card_workmode.busWidth == MMC_DataBusWidth8bit)
	{
		/* Set data bus width */
		extendedCsdconfig.ByteValue  = (uint8_t)MMC_DataBusWidth8bit;
		if(MMC_SetExtendedCsdConfig(mmccard,&extendedCsdconfig, 0U) != Status_Success)
		{
			status_temp = Status_Fail;
		}
		else
		{
			SDMMC_ConfigBusWidth(mmccard->SDHOSTx, SDHOST_DataBusWidth8Bit);
			status_temp = Status_Success;
			mmccard->mmc_card_information.extendedCsd.dataBusWidth = MMC_DataBusWidth8bit;
		}
	}
	
	if (mmccard->card_workmode.busWidth == MMC_DataBusWidth4bit)
	{
		/* Set data bus width */
		extendedCsdconfig.ByteValue  = (uint8_t)MMC_DataBusWidth4bit;
		if(MMC_SetExtendedCsdConfig(mmccard,&extendedCsdconfig, 0U) != Status_Success)
		{
			status_temp = Status_Fail;
		}
		else
		{
			SDMMC_ConfigBusWidth(mmccard->SDHOSTx, SDHOST_DataBusWidth4Bit);
			status_temp = Status_Success;
			mmccard->mmc_card_information.extendedCsd.dataBusWidth = MMC_DataBusWidth4bit;
		}
	}

    return status_temp;
}


static Status_card MMC_SwitchHSTiming(mmc_card_t *mmccard, uint8_t timing, uint8_t driverStrength)
{
    uint8_t hsTiming = 0;

    mmc_extended_csd_config_t extendedCsdconfig;

    /* check the target driver strength support or not */
    if (((mmccard->mmc_card_information.extendedCsd.ioDriverStrength & (1U << driverStrength)) == 0U) &&
        (mmccard->mmc_card_information.extendedCsd.extendecCsdVersion >= (uint8_t)MMC_ExtendedCsdRevision16))
    {
        return Status_CardNotSupportYet;
    }
    /* calucate the register value */
    hsTiming = (timing & 0xFU) | (uint8_t)(driverStrength << 4U);

    /* Switch to high speed timing. */
    extendedCsdconfig.accessMode = MMC_ExtendedCsdAccessModeWriteBits;
    extendedCsdconfig.ByteIndex  = (uint8_t)MMC_ExtendedCsdIndexHighSpeedTiming;
    extendedCsdconfig.ByteValue  = hsTiming;
    extendedCsdconfig.commandSet = MMC_CommandSetStandard;
    if (Status_Success != MMC_SetExtendedCsdConfig(mmccard, &extendedCsdconfig, 0U))
    {
        return Status_Fail;
    }

    mmccard->mmc_card_information.extendedCsd.highSpeedTiming = hsTiming;

    return Status_Success;
}

static Status_card MMC_SwitchToHS200(mmc_card_t *mmccard)
{
    Status_card status_temp = Status_Fail;

    /* select bus width before select bus timing for HS200 mode */
    if (MMC_SetMaxDataBusWidth(mmccard) != Status_Success)
    {
        return Status_Fail;
    }

    /* switch to HS200 mode */
    if (Status_Success != MMC_SwitchHSTiming(mmccard, (uint8_t)MMC_HighSpeed200Timing, MMC_DriverStrength0))
    {
        return Status_Fail;
    }
	
	SDMMC_ConfigWorkMode(mmccard->SDHOSTx,SDMMC_SDR104);
	

//    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, freq);
//    /* config io speed and strength */
//    if (card->usrParam.ioStrength != NULL)
//    {
//        card->usrParam.ioStrength(freq);
//    }

//    /* excute tuning for HS200 */
//    if (MMC_ExecuteTuning(card) != kStatus_Success)
//    {
//        return kStatus_SDMMC_TuningFail;
//    }

    status_temp = MMC_PollingCardStatusBusy(mmccard, MMC_CARD_ACCESS_WAIT_IDLE_TIMEOUT);
    if (Status_CardStatusIdle != status_temp)
    {
        return Status_Fail;
    }

    return Status_Success;
}

static Status_card MMC_SwitchToHighSpeed(mmc_card_t *mmccard)
{
//    uint32_t freq = 0U;

    if (Status_Success != MMC_SwitchHSTiming(mmccard, (uint8_t)MMC_HighSpeedTiming, MMC_DriverStrength0))
    {
        return Status_Fail;
    }

//    if ((mmccard->mmc_card_information.flags & (uint32_t)MMC_SupportHighSpeed52MHZFlag) != 0U)
//    {
//        freq = FSL_SDMMC_CARD_MAX_BUS_FREQ(card->usrParam.maxFreq, MMC_CLOCK_52MHZ);
//    }
//    else if ((card->flags & (uint32_t)kMMC_SupportHighSpeed26MHZFlag) != 0U)
//    {
//        freq = FSL_SDMMC_CARD_MAX_BUS_FREQ(card->usrParam.maxFreq, MMC_CLOCK_26MHZ);
//    }
//    else
//    {
//        /* Intentional empty */
//    }

//    card->busClock_Hz = SDMMCHOST_SetCardClock(card->host, freq);
//    /* config io speed and strength */
//    if (card->usrParam.ioStrength != NULL)
//    {
//        card->usrParam.ioStrength(MMC_CLOCK_52MHZ);
//    }
	
    /* Set card data width, it is nessesary to config the the data bus here, to meet emmc5.0 specification,
     * when you are working in DDR mode , HS_TIMING must set before set bus width
     */
    if (MMC_SetMaxDataBusWidth(mmccard) != Status_Success)
    {
        return Status_Fail;
    }

    if ((mmccard->card_workmode.busWidth == MMC_DataBusWidth4bitDDR) || (mmccard->card_workmode.busWidth == MMC_DataBusWidth8bitDDR))
    {
        SDMMC_ConfigWorkMode(mmccard->SDHOSTx,SDMMC_DDR50);
    }
	else
	{
		SDMMC_ConfigWorkMode(mmccard->SDHOSTx,SDMMC_SDR50);
	}

//    card->busTiming = kMMC_HighSpeedTiming;

    return Status_Success;
}

Status_card MMC_SelectBusTiming(mmc_card_t *mmccard)
{
    Status_card status_temp = Status_Success;
	
	/* Legacy mmc card , do not support the command */
    if ((mmccard->mmc_card_information.csd.systemSpecificationVersion == (uint32_t)MMC_SpecificationVersion3) &&
        (mmccard->mmc_card_information.csd.csdStructureVersion == (uint32_t)MMC_CsdStrucureVersion12))
    {
        return Status_Success;
    }
	
    if(mmccard->card_workmode.busTiming == MMC_HighSpeedTimingNone)
	{
		/* if timing not specified, probe card capability from normal mode */
        mmccard->card_workmode.busTiming = MMC_NormalSpeedTiming;
	}
	
	if(mmccard->card_workmode.busTiming == MMC_HighSpeed200Timing)
	{
		if(((mmccard->card_workmode.operationVoltageflag == MMC_OperationVoltage170to195V)  || \
		   (mmccard->card_workmode.operationVoltageflag == MMC_OperationVoltage120V))  && \
		   ((mmccard->mmc_card_information.flags & (MMC_SupportHS200200MHZ180VFlag | MMC_SupportHS200200MHZ120VFlag)) != 0U))
		{
			if(MMC_SwitchToHS200(mmccard) !=  Status_Success)
			{
				return Status_Fail;
			}
			else
			{
				status_temp = Status_Success;
			}
		}
		else
		{
			status_temp = Status_CardNotSupportYet;
		}
	}
	
	if(mmccard->card_workmode.busTiming == MMC_HighSpeedTiming)
	{
		if(MMC_SwitchToHighSpeed(mmccard) !=  Status_Success)
		{
			return Status_Fail;
		}
		else
		{
			status_temp = Status_Success;
		}
	}
	
	if(mmccard->card_workmode.busTiming == MMC_NormalSpeedTiming)
	{
		/* select bus width */
		if (MMC_SetMaxDataBusWidth(mmccard) != Status_Success)
		{
			return Status_Fail;
		}
		else
		{
			status_temp = Status_Success;
		}
	}
	
    return status_temp;
}

/** Read User Time Since Last Set
 *  param last time.
 */
uint32_t MMC_User_Time_Read(uint32_t time)
{
    if(MMC_systick_timeoutms>=time)
    {
       return MMC_systick_timeoutms-time;
    }
    return(0xFFFFFFFF-time+MMC_systick_timeoutms);
}

/** MMC_SysTick_start_time. **/
void MMC_SysTick_start_time(void)
{
    MMC_systick_timeoutms = 0;

}


