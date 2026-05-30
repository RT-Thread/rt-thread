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
 * @file usbh_msc_bot.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_MSC_BOT_H__
#define __USBH_MSC_BOT_H__

/* Includes ------------------------------------------------------------------*/
#include "usbh_stdreq.h"


/** @addtogroup USBH_LIB
  * @{
  */

/** @addtogroup USBH_CLASS
  * @{
  */

/** @addtogroup USBH_MSC_CLASS
  * @{
  */
  
/** @defgroup USBH_MSC_BOT
  * @brief This file is the Header file for usbh_msc_core.c
  * @{
  */ 


/** @defgroup USBH_MSC_BOT_Exported_Types
  * @{
  */ 

typedef union _USBH_CBW_Block
{
  struct __CBW
  {
    uint32_t CBWSignature;
    uint32_t CBWTag;
    uint32_t CBWTransferLength;
    uint8_t CBWFlags;
    uint8_t CBWLUN; 
    uint8_t CBWLength;
    uint8_t CBWCB[16];
}field;
  uint8_t CBWArray[31];
}HostCBWPkt_TypeDef;

typedef enum
{
  USBH_MSC_BOT_INIT_STATE = 0,                
  USBH_MSC_BOT_RESET,                
  USBH_MSC_GET_MAX_LUN,              
  USBH_MSC_TEST_UNIT_READY,          
  USBH_MSC_READ_CAPACITY10,
  USBH_MSC_MODE_SENSE6,
  USBH_MSC_REQUEST_SENSE,            
  USBH_MSC_BOT_USB_TRANSFERS,        
  USBH_MSC_DEFAULT_APPLI_STATE,  
  USBH_MSC_CTRL_ERROR_STATE,
  USBH_MSC_UNRECOVERED_STATE
}
MSCState;


typedef struct _BOTXfer
{
uint8_t MSCState;
uint8_t MSCStateBkp;
uint8_t MSCStateCurrent;
uint8_t CmdStateMachine;
uint8_t BOTState;
uint8_t BOTStateBkp;
uint8_t* pRxTxBuff;
uint16_t DataLength;
uint8_t BOTXferErrorCount;
uint8_t BOTXferStatus;
} USBH_BOTXfer_TypeDef;


typedef union _USBH_CSW_Block
{
  struct __CSW
  {
    uint32_t CSWSignature;
    uint32_t CSWTag;
    uint32_t CSWDataResidue;
    uint8_t  CSWStatus;
  }field;
  uint8_t CSWArray[13];
}HostCSWPkt_TypeDef;

/**
  * @}
  */ 



/** @defgroup USBH_MSC_BOT_Exported_Defines
  * @{
  */ 
#define USBH_MSC_SEND_CBW                 1
#define USBH_MSC_SENT_CBW                 2
#define USBH_MSC_BOT_DATAIN_STATE         3
#define USBH_MSC_BOT_DATAOUT_STATE        4
#define USBH_MSC_RECEIVE_CSW_STATE        5
#define USBH_MSC_DECODE_CSW               6
#define USBH_MSC_BOT_ERROR_IN             7
#define USBH_MSC_BOT_ERROR_OUT            8


#define USBH_MSC_BOT_CBW_SIGNATURE        0x43425355
#define USBH_MSC_BOT_CBW_TAG              0x20304050             
#define USBH_MSC_BOT_CSW_SIGNATURE        0x53425355           
#define USBH_MSC_CSW_DATA_LENGTH          0x000D
#define USBH_MSC_BOT_CBW_PACKET_LENGTH    31
#define USBH_MSC_CSW_LENGTH               13  
#define USBH_MSC_CSW_MAX_LENGTH           63     

/* CSW Status Definitions */
#define USBH_MSC_CSW_CMD_PASSED           0x00
#define USBH_MSC_CSW_CMD_FAILED           0x01
#define USBH_MSC_CSW_PHASE_ERROR          0x02

#define USBH_MSC_SEND_CSW_DISABLE         0
#define USBH_MSC_SEND_CSW_ENABLE          1

#define USBH_MSC_DIR_IN                   0
#define USBH_MSC_DIR_OUT                  1
#define USBH_MSC_BOTH_DIR                 2

//#define USBH_MSC_PAGE_LENGTH                 0x40
#define USBH_MSC_PAGE_LENGTH              512


#define CBW_CB_LENGTH                     16
#define CBW_LENGTH                        10
#define CBW_LENGTH_TEST_UNIT_READY         6

#define USB_REQ_BOT_RESET                0xFF
#define USB_REQ_GET_MAX_LUN              0xFE

#define MAX_BULK_STALL_COUNT_LIMIT       0x04   /* If STALL is seen on Bulk 
                                         Endpoint continuously, this means 
                                         that device and Host has phase error
                                         Hence a Reset is needed */

/**
  * @}
  */ 

/** @defgroup USBH_MSC_BOT_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USBH_MSC_BOT_Exported_Variables
  * @{
  */ 
extern USBH_BOTXfer_TypeDef USBH_MSC_BOTXferParam;
extern HostCBWPkt_TypeDef USBH_MSC_CBWData;
extern HostCSWPkt_TypeDef USBH_MSC_CSWData;
/**
  * @}
  */ 

/** @defgroup USBH_MSC_BOT_Exported_FunctionsPrototype
  * @{
  */ 
void USBH_MSC_HandleBOTXfer(USB_CORE_MODULE *pdev,
                            USBH_HOST *phost);
uint8_t USBH_MSC_DecodeCSW(USB_CORE_MODULE *pdev,
                           USBH_HOST *phost);
void USBH_MSC_Init(USB_CORE_MODULE *pdev);
USBH_Status USBH_MSC_BOT_Abort(USB_CORE_MODULE *pdev, 
                               USBH_HOST *phost,
                               uint8_t direction);
/**
  * @}
  */ 

#endif  //__USBH_MSC_BOT_H__

