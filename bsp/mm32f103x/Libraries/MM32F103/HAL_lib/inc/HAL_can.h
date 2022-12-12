/**
******************************************************************************
* @file    HAL_can.h
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file contains all the functions prototypes for the BKP firmware
*          library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_CAN_H
#define __HAL_CAN_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"


/** @defgroup CAN_sleep_constants
* @{
*/

#define CANINITFAILED              ((uint8_t)0x00) /* CAN initialization failed */
#define CANINITOK                  ((uint8_t)0x01) /* CAN initialization ok */

/**
* @}
*/



/** @defgroup CAN_sleep_constants
* @{
*/

#define CANSLEEPFAILED              ((uint8_t)0x00) /* CAN did not enter the sleep mode */
#define CANSLEEPOK                  ((uint8_t)0x01) /* CAN entered the sleep mode */

/**
* @}
*/


/** @defgroup CAN_wake_up_constants
* @{
*/

#define CANWAKEUPFAILED             ((uint8_t)0x00) /* CAN did not leave the sleep mode */
#define CANWAKEUPOK                 ((uint8_t)0x01) /* CAN leaved the sleep mode */

/**
* @}
*/

/**
* @brief  parasmeter of CAN Mode
*/
#define CAN_BASICMode ((uint32_t)0x0)
#define CAN_PELIMode  ((uint32_t)0x80)
#define CAN_WorkMode		((uint32_t)0x80)
#define CAN_ResetMode 		((uint32_t)0x1)
#define CAN_ListenOnlyMode	((uint32_t)0x2)
#define CAN_SeftTestMode	((uint32_t)0x4)
#define CAN_FilterMode_Singal	((uint32_t)0x8)
#define CAN_FilterMode_Double	((uint32_t)0xf7)
#define CAN_SleepMode		((uint32_t)0x10)

/**
* @}
*/

/**
* @brief  parasmeter of BASIC CAN interrupt
*/
#define CAN_IT_RIE	((uint32_t)0x2)
#define CAN_IT_TIE	((uint32_t)0x4)
#define CAN_IT_EIE	((uint32_t)0x8)
#define CAN_IT_OIE	((uint32_t)0x10)

/**
* @}
*/

/**
* @brief  parasmeter of PELI CAN interrupt
*/
#define CAN_IT_RI	((uint32_t)0x1)
#define CAN_IT_TI	((uint32_t)0x2)
#define CAN_IT_EI	((uint32_t)0x4)
#define CAN_IT_DOI	((uint32_t)0x8)
#define CAN_IT_WUI	((uint32_t)0x10)
#define CAN_IT_EPI	((uint32_t)0x20)
#define CAN_IT_ALI	((uint32_t)0x40)
#define CAN_IT_BEI	((uint32_t)0x80)
#define CAN_IT_ALL	((uint32_t)0xff)

/**
* @}
*/

/**
* @brief  parasmeter of CAN Status
*/
#define CAN_STATUS_RBS	((uint32_t)0x1)
#define CAN_STATUS_DOS	((uint32_t)0x2)
#define CAN_STATUS_TBS	((uint32_t)0x4)
#define CAN_STATUS_TCS	((uint32_t)0x8)
#define CAN_STATUS_RS	((uint32_t)0x10)
#define CAN_STATUS_TS	((uint32_t)0x20)
#define CAN_STATUS_ES	((uint32_t)0x40)
#define CAN_STATUS_BS	((uint32_t)0x80)

/**
* @}
*/

/**
* @brief  parasmeter of CAN Command register
*/
#define CAN_TR	0x1
#define CAN_AT	0x2
#define CAN_RRB	0x4
#define CAN_CDO	0x8

/**
* @}
*/

/**
* @brief  CAN_Basic init structure definition
*/
typedef struct
{
    uint8_t SJW;
    uint8_t BRP;
    FlagStatus SAM;
    uint8_t TESG2;
    uint8_t TESG1;
    FunctionalState GTS;
    uint8_t CDCLK;
    uint8_t CLOSE_OPEN_CLK;
    uint8_t RXINTEN;
    uint8_t CBP;
} CAN_Basic_InitTypeDef;

/**
* @}
*/

/**
* @brief  CAN_Peli init structure definition
*/
typedef struct
{
    uint8_t SJW;
    uint8_t BRP;
    FlagStatus SAM;
    uint8_t TESG2;
    uint8_t TESG1;
    FunctionalState LOM;
    FunctionalState STM;
    FunctionalState SM;
    FunctionalState SRR;
    uint32_t EWLR;
} CAN_Peli_InitTypeDef;

/**
* @}
*/

/**
* @brief  CAN_Basic filter init structure definition
*/
typedef struct
{
    uint8_t CAN_FilterId;         /*!< Specifies the filter identification number .
  This parameter can be a value between 0x00 and 0xFF */

    uint8_t CAN_FilterMaskId;     /*!< Specifies the filter mask number or identification number,
  This parameter can be a value between 0x00 and 0xFF */
} CAN_Basic_FilterInitTypeDef;

/**
* @}
*/

/**
* @brief  CAN_Peli filter init structure definition
*/
typedef struct
{
    uint8_t AFM;
    uint8_t CAN_FilterId0;         /*!< Specifies the filter identification number
  This parameter can be a value between 0x00 and 0xFF */
    uint8_t CAN_FilterId1;
    uint8_t CAN_FilterId2;
    uint8_t CAN_FilterId3;

    uint8_t CAN_FilterMaskId0;     /*!< Specifies the filter mask number or identification number,
  This parameter can be a value between 0x00 and 0xFF */
    uint8_t CAN_FilterMaskId1;
    uint8_t CAN_FilterMaskId2;
    uint8_t CAN_FilterMaskId3;
} CAN_Peli_FilterInitTypeDef;

/**
* @}
*/

/**
* @brief  CAN_Peli transmit frame definition
*/
typedef enum {DataFrame = 0, RemoteFrame = !DataFrame} TransFrame;

/**
* @}
*/

/**
* @brief  CAN_Basic Tx message structure definition
*/
typedef struct
{
    uint8_t IDH;  /*!< Specifies the standard high identifier.
  This parameter can be a value between 0 to 0xFF. */
    uint8_t IDL;  /*!< Specifies the standard low identifier.
  This parameter can be a value between 0 to 0x7. */
    uint8_t RTR;     /*!< Specifies the type of frame for the message that will
  be transmitted. This parameter can be @TransFrame */

    uint8_t DLC;     /*!< Specifies the length of the frame that will be
  transmitted. This parameter can be a value between
  0 to 8 */

    uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0
  to 0xFF. */
} CanBasicTxMsg;

/**
* @}
*/

/**
* @brief  CAN_Basic Rx message structure definition
*/
typedef struct
{
    uint16_t ID;  /*!< Specifies the standard identifier.
  This parameter can be a value between 0 to 0x7FF. */
    uint8_t RTR;     /*!< Specifies the type of frame for the received message.
  This parameter can be a value of
  @ref TransFrame */

    uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
  This parameter can be a value between 0 to 8 */

    uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to
  0xFF. */

} CanBasicRxMsg;

/**
* @}
*/

/**
* @brief  CAN_Peli_Tx message structure definition
*/
typedef struct
{
    uint8_t IDLL;  /*!< Specifies the extended identifier.
  This parameter can be a value between 0 to 0xFF. */
    uint8_t IDLH;
    uint8_t IDHL;
    uint8_t IDHH;
    uint8_t FF;     /*!< Specifies the type of identifier for the message that
  will be transmitted. This parameter can be a value
  of @ref CAN_identifier_type */

    uint8_t RTR;     /*!< Specifies the type of frame for the message that will
  be transmitted. This parameter can be a value of
  @ref TransFrame */

    uint8_t DLC;     /*!< Specifies the length of the frame that will be
  transmitted. This parameter can be a value between
  0 to 8 */

    uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0
  to 0xFF. */
} CanPeliTxMsg;

/**
* @}
*/

/**
* @brief  CAN Rx message structure definition
*/
typedef struct
{
    uint32_t ID;  /*!< Specifies the extended identifier.
  This parameter can be a value between 0 to 0x1FFFFFFF. */
    uint8_t FF;     /*!< Specifies the type of identifier for the message that
  will be received. This parameter can be a value of
  @ref CAN_identifier_type */

    uint8_t RTR;     /*!< Specifies the type of frame for the received message.
  This parameter can be a value of
  @ref TransFrame */

    uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
  This parameter can be a value between 0 to 8 */

    uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to
  0xFF. */

} CanPeliRxMsg;




#define CANTXFAILED                 ((uint8_t)0x00) /* CAN transmission failed */
#define CANTXOK                     ((uint8_t)0x01) /* CAN transmission succeeded */
#define CANTXPENDING                ((uint8_t)0x02) /* CAN transmission pending */
#define CAN_NO_MB                   ((uint8_t)0x04) /* CAN cell did not provide an empty mailbox */


/************************ Basic and Peli Work all need function ********************/

void CAN_Mode_Cmd(CAN_TypeDef* CANx, uint32_t CAN_MODE);
void CAN_ResetMode_Cmd(CAN_TypeDef* CANx, FunctionalState NewState);
void CAN_ClearDataOverflow(CAN_TypeDef* CANx);
void CAN_ClearITPendingBit(CAN_TypeDef* CANx);


/************************ Basic Work function ********************/
void CAN_DeInit(CAN_TypeDef* CANx);
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_Basic_InitTypeDef* CAN_Basic_InitStruct);
void CAN_FilterInit(CAN_Basic_FilterInitTypeDef* CAN_Basic_FilterInitStruct);
void CAN_StructInit(CAN_Basic_InitTypeDef* CAN_Basic_InitStruct);
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState Newstate);
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanBasicTxMsg* BasicTxMessage);
void CAN_CancelTransmit(CAN_TypeDef* CANx);
void CAN_FIFORelease(CAN_TypeDef* CANx);
void CAN_Receive(CAN_TypeDef* CANx, CanBasicRxMsg* BasicRxMessage);
uint8_t CAN_Sleep(CAN_TypeDef* CANx);
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);


/************************ Peli Work function *********************/
void CAN_Peli_SleepMode_Cmd(FunctionalState NewState);
void CAN_Peli_Init(CAN_Peli_InitTypeDef* CAN_InitStruct);
void CAN_Peli_StructInit(CAN_Peli_InitTypeDef* CAN_Peli_InitStruct);
void CAN_Peli_FilterInit(CAN_Peli_FilterInitTypeDef* CAN_Peli_FilterInitStruct);
void CAN_Peli_FilterStructInit(CAN_Peli_FilterInitTypeDef* CAN_Peli_FilterInitStruct);
void CAN_Peli_Transmit(CanPeliTxMsg* PeliTxMessage);
void CAN_Peli_TransmitRepeat(CanPeliTxMsg* PeliTxMessage);
void CAN_Peli_Receive(CanPeliRxMsg* PeliRxMessage);
uint32_t CAN_Peli_GetRxFIFOInfo(void);
uint8_t CAN_Peli_GetLastErrorCode(void);
uint8_t CAN_Peli_GetReceiveErrorCounter(void);
uint8_t CAN_Peli_GetLSBTransmitErrorCounter(void);
void CAN_Peli_ITConfig(uint32_t CAN_IT, FunctionalState NewState);
ITStatus CAN_Peli_GetITStatus(uint32_t CAN_IT);
void CAN_AutoCfg_BaudParam(CAN_Peli_InitTypeDef  *CAN_Peli_InitStruct, unsigned int SrcClk, unsigned int baud );
#endif /* __HAL_CAN_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/

