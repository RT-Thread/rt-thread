/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_can.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      CAN firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CAN_H
#define __STM32F10x_CAN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* CAN init structure definition */
typedef struct
{
  FunctionalState CAN_TTCM;
  FunctionalState CAN_ABOM;
  FunctionalState CAN_AWUM;
  FunctionalState CAN_NART;
  FunctionalState CAN_RFLM;
  FunctionalState CAN_TXFP;
  u8 CAN_Mode;
  u8 CAN_SJW;
  u8 CAN_BS1;
  u8 CAN_BS2;
  u16 CAN_Prescaler;
} CAN_InitTypeDef;

/* CAN filter init structure definition */
typedef struct
{
  u8 CAN_FilterNumber;
  u8 CAN_FilterMode;
  u8 CAN_FilterScale;
  u16 CAN_FilterIdHigh;
  u16 CAN_FilterIdLow;
  u16 CAN_FilterMaskIdHigh;
  u16 CAN_FilterMaskIdLow;
  u16 CAN_FilterFIFOAssignment;
  FunctionalState CAN_FilterActivation;
} CAN_FilterInitTypeDef;

/* CAN Tx message structure definition */
typedef struct
{
  u32 StdId;
  u32 ExtId;
  u8 IDE;
  u8 RTR;
  u8 DLC;
  u8 Data[8];
} CanTxMsg;

/* CAN Rx message structure definition */
typedef struct
{
  u32 StdId;
  u32 ExtId;
  u8 IDE;
  u8 RTR;
  u8 DLC;
  u8 Data[8];
  u8 FMI;
} CanRxMsg;

/* Exported constants --------------------------------------------------------*/

/* CAN sleep constants */
#define CANINITFAILED              ((u8)0x00) /* CAN initialization failed */
#define CANINITOK                  ((u8)0x01) /* CAN initialization failed */

/* CAN operating mode */
#define CAN_Mode_Normal             ((u8)0x00)  /* normal mode */
#define CAN_Mode_LoopBack           ((u8)0x01)  /* loopback mode */
#define CAN_Mode_Silent             ((u8)0x02)  /* silent mode */
#define CAN_Mode_Silent_LoopBack    ((u8)0x03)  /* loopback combined with silent mode */

#define IS_CAN_MODE(MODE) (((MODE) == CAN_Mode_Normal) || ((MODE) == CAN_Mode_LoopBack)|| \
                           ((MODE) == CAN_Mode_Silent) || ((MODE) == CAN_Mode_Silent_LoopBack))

/* CAN synchronisation jump width */
#define CAN_SJW_1tq                 ((u8)0x00)  /* 1 time quantum */
#define CAN_SJW_2tq                 ((u8)0x01)  /* 2 time quantum */
#define CAN_SJW_3tq                 ((u8)0x02)  /* 3 time quantum */
#define CAN_SJW_4tq                 ((u8)0x03)  /* 4 time quantum */

#define IS_CAN_SJW(SJW) (((SJW) == CAN_SJW_1tq) || ((SJW) == CAN_SJW_2tq)|| \
                         ((SJW) == CAN_SJW_3tq) || ((SJW) == CAN_SJW_4tq))

/* time quantum in bit segment 1 */
#define CAN_BS1_1tq                 ((u8)0x00)  /* 1 time quantum */
#define CAN_BS1_2tq                 ((u8)0x01)  /* 2 time quantum */
#define CAN_BS1_3tq                 ((u8)0x02)  /* 3 time quantum */
#define CAN_BS1_4tq                 ((u8)0x03)  /* 4 time quantum */
#define CAN_BS1_5tq                 ((u8)0x04)  /* 5 time quantum */
#define CAN_BS1_6tq                 ((u8)0x05)  /* 6 time quantum */
#define CAN_BS1_7tq                 ((u8)0x06)  /* 7 time quantum */
#define CAN_BS1_8tq                 ((u8)0x07)  /* 8 time quantum */
#define CAN_BS1_9tq                 ((u8)0x08)  /* 9 time quantum */
#define CAN_BS1_10tq                ((u8)0x09)  /* 10 time quantum */
#define CAN_BS1_11tq                ((u8)0x0A)  /* 11 time quantum */
#define CAN_BS1_12tq                ((u8)0x0B)  /* 12 time quantum */
#define CAN_BS1_13tq                ((u8)0x0C)  /* 13 time quantum */
#define CAN_BS1_14tq                ((u8)0x0D)  /* 14 time quantum */
#define CAN_BS1_15tq                ((u8)0x0E)  /* 15 time quantum */
#define CAN_BS1_16tq                ((u8)0x0F)  /* 16 time quantum */

#define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16tq)

/* time quantum in bit segment 2 */
#define CAN_BS2_1tq                 ((u8)0x00)  /* 1 time quantum */
#define CAN_BS2_2tq                 ((u8)0x01)  /* 2 time quantum */
#define CAN_BS2_3tq                 ((u8)0x02)  /* 3 time quantum */
#define CAN_BS2_4tq                 ((u8)0x03)  /* 4 time quantum */
#define CAN_BS2_5tq                 ((u8)0x04)  /* 5 time quantum */
#define CAN_BS2_6tq                 ((u8)0x05)  /* 6 time quantum */
#define CAN_BS2_7tq                 ((u8)0x06)  /* 7 time quantum */
#define CAN_BS2_8tq                 ((u8)0x07)  /* 8 time quantum */

#define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8tq)

/* CAN clock prescaler */
#define IS_CAN_PRESCALER(PRESCALER) (((PRESCALER) >= 1) && ((PRESCALER) <= 1024))

/* CAN filter number */
#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 13)

/* CAN filter mode */
#define CAN_FilterMode_IdMask       ((u8)0x00)  /* id/mask mode */
#define CAN_FilterMode_IdList       ((u8)0x01)  /* identifier list mode */

#define IS_CAN_FILTER_MODE(MODE) (((MODE) == CAN_FilterMode_IdMask) || \
                                  ((MODE) == CAN_FilterMode_IdList))

/* CAN filter scale */
#define CAN_FilterScale_16bit       ((u8)0x00) /* 16-bit filter scale */
#define CAN_FilterScale_32bit       ((u8)0x01) /* 2-bit filter scale */

#define IS_CAN_FILTER_SCALE(SCALE) (((SCALE) == CAN_FilterScale_16bit) || \
                                    ((SCALE) == CAN_FilterScale_32bit))

/* CAN filter FIFO assignation */
#define CAN_FilterFIFO0             ((u8)0x00)  /* Filter FIFO 0 assignment for filter x */
#define CAN_FilterFIFO1             ((u8)0x01)  /* Filter FIFO 1 assignment for filter x */

#define IS_CAN_FILTER_FIFO(FIFO) (((FIFO) == CAN_FilterFIFO0) || \
                                  ((FIFO) == CAN_FilterFIFO1))

/* CAN Tx */
#define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ((TRANSMITMAILBOX) <= ((u8)0x02))
#define IS_CAN_STDID(STDID)   ((STDID) <= ((u32)0x7FF))
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= ((u32)0x1FFFFFFF))
#define IS_CAN_DLC(DLC)       ((DLC) <= ((u8)0x08))

/* CAN identifier type */
#define CAN_ID_STD                 ((u32)0x00000000)  /* Standard Id */
#define CAN_ID_EXT                 ((u32)0x00000004)  /* Extended Id */

#define IS_CAN_IDTYPE(IDTYPE) (((IDTYPE) == CAN_ID_STD) || ((IDTYPE) == CAN_ID_EXT))

/* CAN remote transmission request */
#define CAN_RTR_DATA                ((u32)0x00000000)  /* Data frame */
#define CAN_RTR_REMOTE              ((u32)0x00000002)  /* Remote frame */

#define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_DATA) || ((RTR) == CAN_RTR_REMOTE))

/* CAN transmit constants */
#define CANTXFAILED                 ((u8)0x00) /* CAN transmission failed */
#define CANTXOK                     ((u8)0x01) /* CAN transmission succeeded */
#define CANTXPENDING                ((u8)0x02) /* CAN transmission pending */
#define CAN_NO_MB                   ((u8)0x04) /* CAN cell did not provide an empty mailbox */

/* CAN receive FIFO number constants */
#define CAN_FIFO0                 ((u8)0x00) /* CAN FIFO0 used to receive */
#define CAN_FIFO1                 ((u8)0x01) /* CAN FIFO1 used to receive */

#define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))

/* CAN sleep constants */
#define CANSLEEPFAILED              ((u8)0x00) /* CAN did not enter the sleep mode */
#define CANSLEEPOK                  ((u8)0x01) /* CAN entered the sleep mode */

/* CAN wake up constants */
#define CANWAKEUPFAILED             ((u8)0x00) /* CAN did not leave the sleep mode */
#define CANWAKEUPOK                 ((u8)0x01) /* CAN leaved the sleep mode */

/* CAN flags */
#define CAN_FLAG_EWG                ((u32)0x00000001) /* Error Warning Flag */
#define CAN_FLAG_EPV                ((u32)0x00000002) /* Error Passive Flag */
#define CAN_FLAG_BOF                ((u32)0x00000004) /* Bus-Off Flag */

#define IS_CAN_FLAG(FLAG) (((FLAG) == CAN_FLAG_EWG) || ((FLAG) == CAN_FLAG_EPV) ||\
                           ((FLAG) == CAN_FLAG_BOF))

/* CAN interrupts */
#define CAN_IT_RQCP0                ((u32)0x00000005) /* Request completed mailbox 0 */
#define CAN_IT_RQCP1                ((u32)0x00000006) /* Request completed mailbox 1 */
#define CAN_IT_RQCP2                ((u32)0x00000007) /* Request completed mailbox 2 */
#define CAN_IT_TME                  ((u32)0x00000001) /* Transmit mailbox empty */
#define CAN_IT_FMP0                 ((u32)0x00000002) /* FIFO 0 message pending */
#define CAN_IT_FF0                  ((u32)0x00000004) /* FIFO 0 full */
#define CAN_IT_FOV0                 ((u32)0x00000008) /* FIFO 0 overrun */
#define CAN_IT_FMP1                 ((u32)0x00000010) /* FIFO 1 message pending */
#define CAN_IT_FF1                  ((u32)0x00000020) /* FIFO 1 full */
#define CAN_IT_FOV1                 ((u32)0x00000040) /* FIFO 1 overrun */
#define CAN_IT_EWG                  ((u32)0x00000100) /* Error warning */
#define CAN_IT_EPV                  ((u32)0x00000200) /* Error passive */
#define CAN_IT_BOF                  ((u32)0x00000400) /* Bus-off */
#define CAN_IT_LEC                  ((u32)0x00000800) /* Last error code */
#define CAN_IT_ERR                  ((u32)0x00008000) /* Error */
#define CAN_IT_WKU                  ((u32)0x00010000) /* Wake-up */
#define CAN_IT_SLK                  ((u32)0x00020000) /* Sleep */

#define IS_CAN_ITConfig(IT) (((IT) == CAN_IT_TME)   || ((IT) == CAN_IT_FMP0)  ||\
                             ((IT) == CAN_IT_FF0)   || ((IT) == CAN_IT_FOV0)  ||\
                             ((IT) == CAN_IT_FMP1)  || ((IT) == CAN_IT_FF1)   ||\
                             ((IT) == CAN_IT_FOV1)  || ((IT) == CAN_IT_EWG)   ||\
                             ((IT) == CAN_IT_EPV)   || ((IT) == CAN_IT_BOF)   ||\
                             ((IT) == CAN_IT_LEC)   || ((IT) == CAN_IT_ERR)   ||\
                             ((IT) == CAN_IT_WKU)   || ((IT) == CAN_IT_SLK))

#define IS_CAN_ITStatus(IT) (((IT) == CAN_IT_RQCP0)  || ((IT) == CAN_IT_RQCP1)  ||\
                             ((IT) == CAN_IT_RQCP2)  || ((IT) == CAN_IT_FF0)    ||\
                             ((IT) == CAN_IT_FOV0)   || ((IT) == CAN_IT_FF1)    ||\
                             ((IT) == CAN_IT_FOV1)   || ((IT) == CAN_IT_EWG)    ||\
                             ((IT) == CAN_IT_EPV)    || ((IT) == CAN_IT_BOF)    ||\
                             ((IT) == CAN_IT_WKU)    || ((IT) == CAN_IT_SLK))

/* Exported macro ------------------------------------------------------------*/
/* Exported function protypes ----------------------------------------------- */
void CAN_DeInit(void);
u8 CAN_Init(CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_ITConfig(u32 CAN_IT, FunctionalState NewState);
u8 CAN_Transmit(CanTxMsg* TxMessage);
u8 CAN_TransmitStatus(u8 TransmitMailbox);
void CAN_CancelTransmit(u8 Mailbox);
void CAN_FIFORelease(u8 FIFONumber);
u8 CAN_MessagePending(u8 FIFONumber);
void CAN_Receive(u8 FIFONumber, CanRxMsg* RxMessage);
u8 CAN_Sleep(void);
u8 CAN_WakeUp(void);
FlagStatus CAN_GetFlagStatus(u32 CAN_FLAG);
void CAN_ClearFlag(u32 CAN_FLAG);
ITStatus CAN_GetITStatus(u32 CAN_IT);
void CAN_ClearITPendingBit(u32 CAN_IT);

#endif /* __STM32F10x_CAN_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
