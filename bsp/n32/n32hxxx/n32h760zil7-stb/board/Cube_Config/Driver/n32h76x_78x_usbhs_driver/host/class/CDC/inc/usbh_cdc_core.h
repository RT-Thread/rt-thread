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
 * @file usbh_cdc_core.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USBH_CDC_CORE_H
#define __USBH_CDC_CORE_H


#include "usbh_cdc_funct.h"



/*Comuncation Calss codes*/
#define COMMUNICATION_DEVICE_CLASS_CODE                         0x02
#define COMMUNICATION_INTERFACE_CLASS_CODE                      0x02

/*Data Interface Class Codes*/
#define DATA_INTERFACE_CLASS_CODE                               0x0A

/*Communcation sub class codes*/
#define RESERVED                                                0x00
#define DIRECT_LINE_CONTROL_MODEL                               0x01
#define ABSTRACT_CONTROL_MODEL                                  0x02
#define TELEPHONE_CONTROL_MODEL                                 0x03
#define MULTICHANNEL_CONTROL_MODEL                              0x04   
#define CAPI_CONTROL_MODEL                                      0x05
#define ETHERNET_NETWORKING_CONTROL_MODEL                       0x06
#define ATM_NETWORKING_CONTROL_MODEL                            0x07


/*Communication Interface Class Control Protocol Codes*/
#define NO_CLASS_SPECIFIC_PROTOCOL_CODE                         0x00
#define COMMON_AT_COMMAND                                       0x01
#define VENDOR_SPECIFIC                                         0xFF


#define CS_INTERFACE                                            0x24
#define CDC_PAGE_SIZE_64                                        0x40


/* States for CDC State Machine */
typedef enum
{
    CDC_IDLE= 0,
    CDC_READ_DATA,
    CDC_SEND_DATA,
    CDC_DATA_SENT,
    CDC_BUSY,
    CDC_GET_DATA,   
    CDC_POLL,
    CDC_CTRL_STATE
}
CDC_State;

/* CDC Transfer State */
typedef struct _CDCXfer
{
    volatile CDC_State CDCState;
    uint8_t* pRxTxBuff;
    uint8_t* pFillBuff;
    uint8_t* pEmptyBuff;
    uint32_t BufferLen;
    uint16_t DataLength;
} CDC_Xfer_TypeDef;

typedef struct CDC_UserCb
{
    void  (*Send)       (uint8_t  *);             
    void  (*Receive)    (uint8_t *);       

} CDC_Usercb_TypeDef;

/* Structure for CDC process */
typedef struct _CDC_CommInterface
{
    uint8_t              hc_num_in; 
    uint8_t              hc_num_out;
    uint8_t              notificationEp;
    CDC_State            state; 
    uint8_t              buff[8];
    uint16_t             length;
    uint8_t              ep_addr;  
}
CDC_CommInterface_Typedef ;

typedef struct _CDC_DataInterface
{
    uint8_t              hc_num_in; 
    uint8_t              hc_num_out;
    uint8_t              cdcOutEp;
    uint8_t              cdcInEp;
    CDC_State            state; 
    uint8_t              buff[8];
    uint16_t             length;
    uint8_t              ep_addr;
}
CDC_DataInterface_Typedef ;

/* Structure for CDC process */
typedef struct _CDC_Process
{
    CDC_CommInterface_Typedef CDC_CommItf;
    CDC_DataInterface_Typedef CDC_DataItf;
}
CDC_Machine_TypeDef;

extern USBH_Class_cb_TypeDef  USBH_CDC_cb;

void  CDC_SendData(uint8_t *data, uint16_t length);
void  CDC_StartReception( USB_CORE_MODULE *pdev);
void  CDC_StopReception( USB_CORE_MODULE *pdev);


#endif /* __USBH_CDC_CORE_H */
