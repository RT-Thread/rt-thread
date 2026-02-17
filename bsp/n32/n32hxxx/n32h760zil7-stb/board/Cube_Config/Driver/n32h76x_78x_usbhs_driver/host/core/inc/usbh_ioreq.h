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
 * @file usbh_ioreq.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __USBH_IOREQ_H__
#define __USBH_IOREQ_H__

#include "usbhs_conf.h"
#include "usbh_core.h"
#include "usbh_def.h"

#define USBH_SETUP_PKT_SIZE   8
#define USBH_EP0_EP_NUM       0
#define USBH_MAX_PACKET_SIZE  0x40

USBH_Status USBH_CtrlSendSetup(USB_CORE_MODULE *USBx, uint8_t *buff, uint8_t hch_num);

USBH_Status USBH_CtrlSendData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num);

USBH_Status USBH_CtrlReceiveData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num);

USBH_Status USBH_BulkReceiveData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num);

USBH_Status USBH_BulkSendData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num);

USBH_Status USBH_InterruptReceiveData(USB_CORE_MODULE *USBx, uint8_t *buff, uint8_t length, uint8_t hch_num);

USBH_Status USBH_InterruptSendData(USB_CORE_MODULE *USBx, uint8_t *buff, uint8_t length, uint8_t hch_num);

USBH_Status USBH_CtrlReq(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t *buff,uint16_t length);

USBH_Status USBH_IsocReceiveData(USB_CORE_MODULE *USBx, uint8_t *buff, uint32_t length, uint8_t hch_num);

USBH_Status USBH_IsocSendData(USB_CORE_MODULE *USBx, uint8_t *buff, uint32_t length, uint8_t hch_num);

#endif /* __USBH_IOREQ_H__ */
