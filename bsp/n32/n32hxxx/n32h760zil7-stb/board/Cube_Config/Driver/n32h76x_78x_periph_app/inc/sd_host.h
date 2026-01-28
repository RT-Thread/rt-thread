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
 * @file sd_host.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __SD_HOST_H__
#define __SD_HOST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdmmc_spec.h"
#include "n32h76x_78x_sdmmc.h"



/* SDSPI individual commands */
typedef enum
{
    kSDSPI_CommandCrc = 59U, /* Command crc protection on/off */
} sdspi_command_t;

/* SD card individual application commands */
typedef enum
{
    SD_ApplicationSetBusWdith             = 6U,  /* Set Bus Width */
    SD_ApplicationStatus                  = 13U, /* Send SD status */
    SD_ApplicationSendNumberWriteBlocks   = 22U, /* Send Number Of Written Blocks */
    SD_ApplicationSetWriteBlockEraseCount = 23U, /* Set Write Block Erase Count */
    SD_ApplicationSendOperationCondition  = 41U, /* Send Operation Condition */
    SD_ApplicationSetClearCardDetect      = 42U, /* Set Connnect/Disconnect pull up on detect pin */
    SD_ApplicationSendScr                 = 51U, /* Send Scr */
} sd_application_command_t;



/* card cmd13 retry times */
#define SD_CMD13_RETRY_TIMES (10)
/* card access idle timeout value */
#define SD_CARD_ACCESS_WAIT_IDLE_TIMEOUT (600U) /* more then 500ms timeout value */


/* Record information of card */
typedef struct
{
    uint32_t flags;         /* sd card Flags */
    uint32_t busy;          /* busy status */
    uint32_t ocr;           /* Raw OCR content,, only 24bit avalible for SDIO card */
    sd_cid   cid;           /* CID */
    uint32_t rca;           /* Relative address of the card */
    sd_csd_t csd;           /* CSD */
    uint32_t blockCount;    /* Card total block number */
    uint32_t blockSize;     /* Card block size */
    sd_scr_t scr;           /* SCR */
    uint32_t version;       /* Card version */
//    sd_status_t stat;       /* sd 512 bit status */  
}sd_card_info;


/* card bus width */
typedef enum
{
    SDMMC_BusWdith1Bit = 0U, /* card bus 1 width */
    SDMMC_BusWdith4Bit = 1U, /* card bus 4 width */
    SDMMC_BusWdith8Bit = 2U, /* card bus 8 width */
}sd_buswidth_t;




/* card operation voltage */
typedef enum
{
    SD_OperationVoltageNone = 0U, /* indicate current voltage setting is not setting by suser*/
    SD_OperationVoltage330V = 1U, /* card operation voltage around 3.3v */
    SD_OperationVoltage300V = 2U, /* card operation voltage around 3.0v */
    SD_OperationVoltage180V = 3U, /* card operation voltage around 1.8v */
}sd_operation_voltage_t;

/* SD card communication method and speed */
typedef struct
{
    uint32_t busClock_Hz;   /* SD bus clock frequency united in Hz */
    sd_buswidth_t busWidth; /* set DATA bus width */
    SD_ModeConfig mode;         /* work mode */
    sdmmc_dma_t dma;           /* dma mode */  
    sd_operation_voltage_t operationVoltageflag; /* card current operation voltage */
}sd_card_workmode;

/* SD card state
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct
{
    SDHOST_Module* SDHOSTx; /* Host device */
    SDMMC_Module* SDMMCx;   /* SDMMC */
    SDMMC_CMD command;
    sd_card_info sd_card_information;
    sd_card_workmode card_workmode;
    SDHOST_TMODE_struct  TMODE_truct;
} sd_card_t;


/* Default block size */
#define FSL_SDMMC_DEFAULT_BLOCK_SIZE (512U)

Status_card SD_NormalCMD_Send(sd_card_t* card, uint32_t index,uint32_t argument,SDMMC_CardRspType responseType);
Status_card SD_AutoCMD_Send(sd_card_t* card, uint32_t index,uint32_t argument,SDMMC_CardRspType responseType);

void SD_DecodeCid(sd_card_t* card);
void SD_DecodeCsd(sd_card_t* card);
Status_card SD_PollingCardStatusBusy(sd_card_t* card,uint32_t timeoutMs);
Status_card SD_SendSCR(sd_card_t* card);
Status_card SD_Erase_Block(sd_card_t* card, uint32_t startBlock, uint32_t blockCount);
Status_card SD_ReadBlocks(sd_card_t *card, uint32_t *buffer, uint32_t startBlock, uint32_t blockCount);
Status_card SD_WriteBlocks(sd_card_t *card, uint32_t *buffer, uint32_t startBlock, uint32_t blockCount);
Status_card SD_SwitchVoltage(sd_card_t *card);
Status_card SD_SelectBusTiming(sd_card_t *card);

/* delay function */
extern uint32_t SD_systick_timeoutms;
uint32_t SD_User_Time_Read(uint32_t time);
void SD_SysTick_start_time(void);

#ifdef __cplusplus
}
#endif

#endif /* __SD_HOST_H__ */

