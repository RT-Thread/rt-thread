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
 * @file usbd_printer.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USB_PRINTER_H_
#define __USB_PRINTER_H_

#include  "usbd_ioreq.h"

#define USB_PRNT_CONFIG_DESC_SIZ                   (32U)


#define USB_PRNT_BIDIRECTIONAL                     (0x02U)


#define PRINTER_DATA_IN_PACKET_SIZE                PRINTER_DATA_MAX_PACKET_SIZE
#define PRINTER_DATA_OUT_PACKET_SIZE               PRINTER_DATA_MAX_PACKET_SIZE

#define PRINTER_STATUS_PAPER_EMPTY                 0x10U
#define PRINTER_STATUS_SELECTED                    0x08U
#define PRINTER_STATUS_NO_ERROR                    0x00U

/* printing device specific-class request */
#define PRINTER_GET_DEVICE_ID                      0x00U            /*!< get device id request */
#define PRINTER_GET_PORT_STATUS                    0x01U            /*!< get port status request */
#define PRINTER_SOFT_RESET                         0x02U            /*!< soft reset request */


typedef struct _USBD_PRNT_Itf
{
  int8_t (* Init)(void);
  int8_t (* DeInit)(void);
  int8_t (* Control_req)(uint8_t req, uint8_t *pbuf, uint16_t *length);
  int8_t (* Receive)(uint8_t *Buf, uint16_t *Len);

} USBD_PRNT_ItfTypeDef;

extern USBD_Class_cb_TypeDef  USBD_PRINTER_cb;

#endif /* __USB_PRINTER_H_ */
