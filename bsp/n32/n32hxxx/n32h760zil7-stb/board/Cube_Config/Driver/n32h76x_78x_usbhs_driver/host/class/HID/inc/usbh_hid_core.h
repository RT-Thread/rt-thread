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
 * @file usbh_hid_core.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_HID_CORE_H
#define __USBH_HID_CORE_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usbh_stdreq.h"
#include "usbhs_bsp.h"
#include "usbh_ioreq.h"
#include "usbh_hcs.h"
 
/** @addtogroup USBH_LIB
  * @{
  */

/** @addtogroup USBH_CLASS
  * @{
  */

/** @addtogroup USBH_HID_CLASS
  * @{
  */
  
/** @defgroup USBH_HID_CORE
  * @brief This file is the Header file for USBH_HID_CORE.c
  * @{
  */ 


/** @defgroup USBH_HID_CORE_Exported_Types
  * @{
  */ 

#define HID_MIN_POLL          10

/* States for HID State Machine */
typedef enum
{
  HID_IDLE= 0,
  HID_SEND_DATA,
  HID_BUSY,
  HID_GET_DATA,   
  HID_SYNC,     
  HID_POLL,
  HID_ERROR,
}
HID_State;

typedef enum
{
  HID_REQ_IDLE = 0,
  HID_REQ_GET_REPORT_DESC,
  HID_REQ_GET_HID_DESC,
  HID_REQ_SET_IDLE,
  HID_REQ_SET_PROTOCOL,
  HID_REQ_SET_REPORT,

}
HID_CtlState;

typedef struct HID_cb
{
  void  (*Init)   (void);             
  void  (*Decode) (uint8_t *data);       
  
} HID_cb_TypeDef;

typedef  struct  _HID_Report 
{
    uint8_t   ReportID;    
    uint8_t   ReportType;  
    uint16_t  UsagePage;   
    uint32_t  Usage[2]; 
    uint32_t  NbrUsage;                      
    uint32_t  UsageMin;                      
    uint32_t  UsageMax;                      
    int32_t   LogMin;                        
    int32_t   LogMax;                        
    int32_t   PhyMin;                        
    int32_t   PhyMax;                        
    int32_t   UnitExp;                       
    uint32_t  Unit;                          
    uint32_t  ReportSize;                    
    uint32_t  ReportCnt;                     
    uint32_t  Flag;                          
    uint32_t  PhyUsage;                      
    uint32_t  AppUsage;                      
    uint32_t  LogUsage;   
} 
HID_Report_TypeDef;

/* Structure for HID process */
typedef struct _HID_Process
{
  uint8_t              buff[64];
  uint8_t              hc_num_in; 
  uint8_t              hc_num_out; 
  HID_State            state; 
  uint8_t              HIDIntOutEp;
  uint8_t              HIDIntInEp;
  HID_CtlState         ctl_state;
  uint16_t             length;
  uint8_t              ep_addr;
  uint16_t             poll; 
  __IO uint16_t        timer; 
  HID_cb_TypeDef             *cb;
}
HID_Machine_TypeDef;

/**
  * @}
  */ 

/** @defgroup USBH_HID_CORE_Exported_Defines
  * @{
  */ 

#define USB_HID_REQ_GET_REPORT       0x01
#define USB_HID_GET_IDLE             0x02
#define USB_HID_GET_PROTOCOL         0x03
#define USB_HID_SET_REPORT           0x09
#define USB_HID_SET_IDLE             0x0A
#define USB_HID_SET_PROTOCOL         0x0B    
/**
  * @}
  */ 

/** @defgroup USBH_HID_CORE_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USBH_HID_CORE_Exported_Variables
  * @{
  */ 
extern USBH_Class_cb_TypeDef  USBH_HID_cb;
/**
  * @}
  */ 

/** @defgroup USBH_HID_CORE_Exported_FunctionsPrototype
  * @{
  */ 

USBH_Status USBH_Set_Report (USB_CORE_MODULE *pdev,
                             USBH_HOST *phost,
                                  uint8_t reportType,
                                  uint8_t reportId,
                                  uint8_t reportLen,
                                  uint8_t* reportBuff);
/**
  * @}
  */ 


#endif /* __USBH_HID_CORE_H */
