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
 * @file usbh_msc_scsi.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_MSC_SCSI_H__
#define __USBH_MSC_SCSI_H__

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
  
/** @defgroup USBH_MSC_SCSI
  * @brief This file is the Header file for usbh_msc_scsi.c
  * @{
  */ 


/** @defgroup USBH_MSC_SCSI_Exported_Types
  * @{
  */ 
typedef enum {
  USBH_MSC_OK = 0,
  USBH_MSC_FAIL = 1,
  USBH_MSC_PHASE_ERROR = 2,
  USBH_MSC_BUSY = 3
}USBH_MSC_Status_TypeDef;

typedef enum {
  CMD_UNINITIALIZED_STATE =0,
  CMD_SEND_STATE,
  CMD_WAIT_STATUS
} CMD_STATES_TypeDef;  



typedef struct __MassStorageParameter
{
  uint32_t MSCapacity;
  uint32_t MSSenseKey; 
  uint16_t MSPageLength;
  uint8_t MSBulkOutEp;
  uint8_t MSBulkInEp;
  uint8_t MSWriteProtect;
} MassStorageParameter_TypeDef;
/**
  * @}
  */ 



/** @defgroup USBH_MSC_SCSI_Exported_Defines
  * @{
  */ 



#define OPCODE_TEST_UNIT_READY            0X00
#define OPCODE_READ_CAPACITY10            0x25
#define OPCODE_MODE_SENSE6                0x1A
#define OPCODE_READ10                     0x28
#define OPCODE_WRITE10                    0x2A
#define OPCODE_REQUEST_SENSE              0x03

#define DESC_REQUEST_SENSE                0X00
#define ALLOCATION_LENGTH_REQUEST_SENSE   63 
#define XFER_LEN_READ_CAPACITY10           8
#define XFER_LEN_MODE_SENSE6              63

#define MASK_MODE_SENSE_WRITE_PROTECT     0x80
#define MODE_SENSE_PAGE_CONTROL_FIELD     0x00
#define MODE_SENSE_PAGE_CODE              0x3F
#define DISK_WRITE_PROTECTED              0x01
/**
  * @}
  */ 

/** @defgroup USBH_MSC_SCSI_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup _Exported_Variables
  * @{
  */ 
extern MassStorageParameter_TypeDef USBH_MSC_Param;
/**
  * @}
  */ 

/** @defgroup USBH_MSC_SCSI_Exported_FunctionsPrototype
  * @{
  */ 
uint8_t USBH_MSC_TestUnitReady(USB_CORE_MODULE *pdev);
uint8_t USBH_MSC_ReadCapacity10(USB_CORE_MODULE *pdev);
uint8_t USBH_MSC_ModeSense6(USB_CORE_MODULE *pdev);
uint8_t USBH_MSC_RequestSense(USB_CORE_MODULE *pdev);
uint8_t USBH_MSC_Write10(USB_CORE_MODULE *pdev, uint8_t *,uint32_t ,
                         uint32_t );
uint8_t USBH_MSC_Read10(USB_CORE_MODULE *pdev,
                        uint8_t *,
                        uint32_t ,
                        uint32_t );
void USBH_MSC_StateMachine(USB_CORE_MODULE *pdev);

/**
  * @}
  */ 

#endif  //__USBH_MSC_SCSI_H__
