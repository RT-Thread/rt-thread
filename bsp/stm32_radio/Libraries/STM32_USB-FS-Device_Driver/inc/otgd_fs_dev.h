/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otg_dev.h
* Author             : STMicroelectronics
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : linking defines
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OTG_DEV_H__
#define __OTG_DEV_H__

#ifdef STM32F10X_CL

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Endpoint types */
#define OTG_DEV_EP_TYPE_CONTROL       0
#define OTG_DEV_EP_TYPE_ISOC          1
#define OTG_DEV_EP_TYPE_BULK          2
#define OTG_DEV_EP_TYPE_INT           3

/* Endpoint Addresses (w/direction) */
#define EP0_OUT                    0x00  
#define EP0_IN                     0x80  
#define EP1_OUT                    0x01  
#define EP1_IN                     0x81  
#define EP2_OUT                    0x02  
#define EP2_IN                     0x82  
#define EP3_OUT                    0x03  
#define EP3_IN                     0x83  


/*-*-*-*-*-*-*-*-*-* Replace the usb_regs.h defines -*-*-*-*-*-*-*-*-*-*-*-*-*/
/* endpoints enumeration */
#define ENDP0   ((uint8_t)0)
#define ENDP1   ((uint8_t)1)
#define ENDP2   ((uint8_t)2)
#define ENDP3   ((uint8_t)3)
#define ENDP4   ((uint8_t)4)
#define ENDP5   ((uint8_t)5)
#define ENDP6   ((uint8_t)6)
#define ENDP7   ((uint8_t)7)

/* EP Transmit status defines */
#define EP_TX_DIS              DEV_EP_TX_DIS)  /* EndPoint TX DISabled */
#define EP_TX_STALL            DEV_EP_TX_STALL /* EndPoint TX STALLed */
#define EP_TX_NAK              DEV_EP_TX_NAK   /* EndPoint TX NAKed */
#define EP_TX_VALID            DEV_EP_TX_VALID /* EndPoint TX VALID */

/* EP Transmit status defines */
#define EP_RX_DIS              DEV_EP_RX_DIS   /* EndPoint RX DISabled */
#define EP_RX_STALL            DEV_EP_RX_STALL /* EndPoint RX STALLed */
#define EP_RX_NAK              DEV_EP_RX_NAK   /* EndPoint RX NAKed */
#define EP_RX_VALID            DEV_EP_RX_VALID /* EndPoint RX VALID */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/* Exported macro ------------------------------------------------------------*/
#define _GetEPTxStatus(bEpNum)        ((uint16_t)OTG_DEV_GetEPTxStatus(bEpNum))
#define _GetEPRxStatus(bEpNum)        ((uint16_t)OTG_DEV_GetEPRxStatus(bEpNum))

#define _SetEPTxStatus(bEpNum,wState) (OTG_DEV_SetEPTxStatus(bEpNum, wState))
#define _SetEPRxStatus(bEpNum,wState) (OTG_DEV_SetEPRxStatus(bEpNum, wState))

#define _SetEPTxValid(bEpNum)         (OTG_DEV_SetEPTxStatus(bEpNum, EP_TX_VALID))
#define _SetEPRxValid(bEpNum)         (OTG_DEV_SetEPRxStatus(bEpNum, EP_RX_VALID))

#define _GetTxStallStatus(bEpNum)     (OTG_DEV_GetEPTxStatus(bEpNum) == EP_TX_STALL)
#define _GetRxStallStatus(bEpNum)     (OTG_DEV_GetEPRxStatus(bEpNum) == EP_RX_STALL) 

/* Define the callbacks for updating the USB state machine */
#define OTGD_FS_DEVICE_RESET              Device_Property.Reset()

/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void OTG_DEV_Init(void);
void OTG_DEV_EP_Init(uint8_t bEpAdd, uint8_t bEpType, uint16_t wEpMaxPackSize);

void OTG_DEV_SetEPRxStatus(uint8_t bEpnum, uint32_t status);
void OTG_DEV_SetEPTxStatus(uint8_t bEpnum, uint32_t status); 
uint32_t OTG_DEV_GetEPRxStatus(uint8_t bEpnum); 
uint32_t OTG_DEV_GetEPTxStatus(uint8_t bEpnum); 

void USB_DevDisconnect(void);
void USB_DevConnect(void);


/*-*-*-*-*-*-*-*-*-* Replace the usb_regs.h prototypes *-*-*-*-*-*-*-*-*-*-*-*/
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState);
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState);
uint16_t GetEPTxStatus(uint8_t bEpNum);
uint16_t GetEPRxStatus(uint8_t bEpNum);
void SetEPTxValid(uint8_t bEpNum);
void SetEPRxValid(uint8_t bEpNum);
uint16_t GetTxStallStatus(uint8_t bEpNum);
uint16_t GetRxStallStatus(uint8_t bEpNum);
void SetEPTxCount(uint8_t bEpNum, uint16_t wCount);
void SetEPRxCount(uint8_t bEpNum, uint16_t wCount);

uint16_t ToWord(uint8_t, uint8_t);
uint16_t ByteSwap(uint16_t);
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

#endif /* STM32F10X_CL */

#endif /* __OTG_DEV_H__ */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

