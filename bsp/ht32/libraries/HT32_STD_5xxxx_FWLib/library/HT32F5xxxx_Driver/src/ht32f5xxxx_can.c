/*********************************************************************************************************//**
 * @file    ht32f5xxxx_can.c
 * @version $Rev:: 8284         $
 * @date    $Date:: 2024-11-22 #$
 * @brief   This file provides all the CAN firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_can.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup CAN CAN
  * @brief CAN driver modules
  * @{
  */


/* Private types -------------------------------------------------------------------------------------------*/
typedef enum
{
  IF0_NUM = 0,
  IF1_NUM,
  IF_TOTAL_NUM
} CANIF_NUMBER_Enum;

/* Private function prototypes -----------------------------------------------------------------------------*/
static HT_CANIF_TypeDef *_GetFreeIF(HT_CAN_TypeDef  *CANx);
static void _CAN_EnterInitMode(HT_CAN_TypeDef *CANx);
static void _CAN_LeaveInitMode(HT_CAN_TypeDef *CANx);
static void _CAN_SetRxMsgObj(HT_CAN_TypeDef  *CANx, u32 MsgNum, CAN_MSG_TypeDef* pCanMsg, u32 uSingleOrFifoLast);
static s32 _CAN_ReadMsgObj(HT_CAN_TypeDef *CANx, u32 MsgNum, u32 Release, CAN_MSG_TypeDef* pCanMsg, u8* data, u32* len);
static ErrStatus _CAN_SetTxMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len);
static int _CAN_GetValidMsg(HT_CAN_TypeDef *CANx);
static bool _CAN_GetNewData(HT_CAN_TypeDef *CANx, u32 MsgNum);
static bool _CAN_CheckMsgIsValid(HT_CAN_TypeDef *CANx, u32 MsgNum);
static void _CAN_ClearMsgPendingFlag(HT_CAN_TypeDef *CANx, u32 MsgNum);
static volatile bool gIsBusOff = FALSE;

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup CAN_Exported_Functions CAN exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief  Deinitialize the specified CAN registers to their default values.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval None
 ************************************************************************************************************/
void CAN_DeInit(HT_CAN_TypeDef* CANx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  if (CANx == HT_CAN0)
  {
    RSTCUReset.Bit.CAN0 = 1;
  }

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief  Set CAN operation mode and target baud-rate.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  CAN_InitStruct: pointer to a CAN_InitTypeDef structure.
 * @retval None
  ***********************************************************************************************************/
void CAN_Init(HT_CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  _CAN_EnterInitMode(CANx);

  CANx->BTR = (((u32)(CAN_InitStruct->CAN_TSEG1      - 1) << CAN_BTR_TSEG1_Pos) & CAN_BTR_TSEG1_Msk)|
              (((u32)(CAN_InitStruct->CAN_TSEG0       -1) << CAN_BTR_TSEG0_Pos) & CAN_BTR_TSEG0_Msk)|
              (((u32)(CAN_InitStruct->CAN_BRPrescaler -1) << CAN_BTR_BRP_Pos)   & CAN_BTR_BRP_Msk)  |
              (((u32)(CAN_InitStruct->CAN_SJW         -1) << CAN_BTR_SJW_Pos)   & CAN_BTR_SJW_Msk);

  CANx->BRPER = (CAN_InitStruct->CAN_BRPrescaler >> 6) & CAN_BRPE_BRPE_Msk;
  _CAN_LeaveInitMode(CANx);

  if (CAN_InitStruct->CAN_NART)
    HT_CAN0->CR |= CAN_CR_DAR;

  if (CAN_InitStruct->CAN_Mode)
  {
    CAN_EnterTestMode(CANx, CAN_InitStruct->CAN_Mode);
  }
  CAN_IntConfig(CANx, CAN_INT_EIE | CAN_INT_IE , ENABLE);

  return;
}

/**********************************************************************************************************//**
 * @brief  Enable or Disable the specified CAN interrupt.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  CAN_Int: specify if the CAN interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg CAN_INT_IE     : Module interrupt enable.
 *     @arg CAN_INT_SIE    : Status change interrupt enable.
 *     @arg CAN_INT_EIE    : Error interrupt enable.
 *     @arg CAN_INT_ALL    : All CAN interrupt
 * @param NewState: this parameter can be ENABLE or DISABLE.
 * @retval None
  ***********************************************************************************************************/
void CAN_IntConfig(HT_CAN_TypeDef *CANx, u32 CAN_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  Assert_Param(IS_CONTROL_STATUS(NewState));
  CAN_Int = CAN_Int & CAN_INT_ALL;

  _CAN_EnterInitMode(CANx);
  if (NewState != DISABLE)
  {
    CANx->CR |= CAN_Int;
  }
   else
  {
    CANx->CR = CANx->CR & ~(CAN_Int);
  }
  _CAN_LeaveInitMode(CANx);
}

/**********************************************************************************************************//**
 * @brief  Get the specified CAN INT status.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  CAN_Int: the CAN interrupt source.
 *   This parameter can be one of the following values:
 *     @arg CAN_INT_IE     : Module interrupt enable.
 *     @arg CAN_INT_SIE    : Status change interrupt enable.
 *     @arg CAN_INT_EIE    : Error interrupt enable.
 * @retval SET or RESET
  ***********************************************************************************************************/
FlagStatus CAN_GetIntStatus(HT_CAN_TypeDef* CANx, u32 CAN_Int)
{
  FlagStatus Status;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  if ((CANx->CR & CAN_Int) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }
  return Status;
}

/*********************************************************************************************************//**
 * @brief  Check whether the specified CAN flag has been set.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  CAN_Flag: specify the flag to be check.
 *   This parameter can be one of the following values:
 *     @arg CAN_FLAG_BOFF  : Busoff Status
 *     @arg CAN_FLAG_EWARN : Warning Status
 *     @arg CAN_FLAG_EPASS : Error Passive
 *     @arg CAN_FLAG_RXOK  : Received a Message Successfully
 *     @arg CAN_FLAG_TXOK  : Transmitted a Message Successfully
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus CAN_GetFlagStatus(HT_CAN_TypeDef* CANx, uint32_t CAN_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  if (CANx->SR & CAN_Flag)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**********************************************************************************************************//**
 * @brief  Clear the interrupt flag of the specified CAN.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  CAN_Flag: specify the flag that is to be cleared.
 *     @arg CAN_FLAG_RXOK  : Received a Message Successfully
 *     @arg CAN_FLAG_TXOK  : Transmitted a Message Successfully
 * @retval None
  ***********************************************************************************************************/
void CAN_ClearFlag(HT_CAN_TypeDef* CANx, uint32_t CAN_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  CANx->SR &= ~CAN_Flag;
}

/**********************************************************************************************************//**
 * @brief  Returns the CANx's last error code (LEC).
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval This function will return the CAN_ErrorCode following values:
 *    - NO_ERROR    : No Error
 *    - STUFF_ERROR : Stuff Error
 *    - FORM_ERROR  : Form Error
 *    - ACK_ERROR   : Acknowledgment Error
 *    - BIT1_EROR   : Bit Recessive Error
 *    - BIT0_ERROR  : Bit Dominant Error
 *    - CRC_ERROR   : CRC Error
 *    - NO_CHANGE   : Software Set Error
  ***********************************************************************************************************/
CAN_LastErrorCode_TypeDef CAN_GetLastErrorCode(HT_CAN_TypeDef* CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  return (CAN_LastErrorCode_TypeDef)(CANx->SR & CAN_LEC_Msk);
}

/**********************************************************************************************************//**
 * @brief  Returns the CANx Receive Error Counter (REC).
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval CAN Receive Error Counter.
  ***********************************************************************************************************/
u32 CAN_GetReceiveErrorCounter(HT_CAN_TypeDef* CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  return ((CANx->ECR & CAN_ECR_REC_MsK) >> CAN_ECR_REC_Pos);
}

/*********************************************************************************************************//**
 * @brief  Returns the LSB of the 9-bit CANx Transmit Error Counter(TEC).
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval LSB of the 9-bit CAN Transmit Error Counter.
  ***********************************************************************************************************/
u32 CAN_GetLSBTransmitErrorCounter(HT_CAN_TypeDef* CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  return (CANx->ECR & CAN_ECR_TEC_MsK);
}

/*********************************************************************************************************//**
 * @brief  Monitor CAN BusOff status.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval None
  ***********************************************************************************************************/
void CAN_BusOffRecovery(HT_CAN_TypeDef *CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  /* Get BusOff Flag                                                                                        */
  if (CANx->SR & CAN_FLAG_BOFF)
  {
    _CAN_LeaveInitMode(CANx);
  }
  return;
}

/**********************************************************************************************************//**
 * @brief  Switch the CAN into test mode.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  u8TestMask Specifies the configuration in test modes
 *         @arg CAN_MODE_BASIC              : Enable basic mode of test mode
 *         @arg CAN_MODE_SILENT             : Enable silent mode of test mode
 *         @arg CAN_MODE_LBACK              : Enable Loop Back Mode of test mode
 *         @arg CAN_MODE_MONITORER          : Sample Point can be monitored at CAN_TX pin.
 *         @arg CAN_MODE_TX_DOMINANT        : CAN_TX pin drives a dominant ('0') value
 *         @arg CAN_MODE_TX_RECESSIVE       : CAN_TX pin drives a recessive ('1') value
 * @retval None
  ***********************************************************************************************************/
void CAN_EnterTestMode(HT_CAN_TypeDef *CANx, u32 u8TestMask)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  CANx->CR |= CAN_CR_TEST;
  CANx->TR = u8TestMask;
}

/*********************************************************************************************************//**
 * @brief  Leave the test mode
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval None
  ***********************************************************************************************************/
void CAN_LeaveTestMode(HT_CAN_TypeDef *CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  CANx->CR |= CAN_CR_TEST;
  CANx->TR &= ~(CAN_MODE_LBACK | CAN_MODE_SILENT | CAN_MODE_BASIC | CAN_MODE_TX_RECESSIVE);
  CANx->CR &= (~CAN_CR_TEST);
}

/*********************************************************************************************************//**
 * @brief  The function is used to Send CAN message in BASIC mode of test mode. Before call the API,
 *         the user should be call CAN_EnterTestMode(CAN_TEST_BASIC) and let CAN controller enter
 *         basic mode of test mode. Please notice IF0 Registers used as Tx Buffer in basic mode.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the data buffer to be transmitted.
 * @param  len: Length of the data to be transmitted.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_BasicSendMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  if (CANx->SR & CAN_FLAG_BOFF)
  {
    return ERROR;
  }
  while (CANx->IF0.CREQ & CAN_FLAG_IF_BUSY)
  {
  }

  CANx->SR &= (~CAN_FLAG_TXOK);

  if (pCanMsg->IdType == CAN_STD_ID)
  {
    /* standard ID                                                                                          */
    CANx->IF0.ARB0 = 0;
    CANx->IF0.ARB1 = (((pCanMsg->Id) & CAN_STD_FRAME_Msk) << 2);
  }
  else
  {
    /* extended ID                                                                                          */
    CANx->IF0.ARB0 = (pCanMsg->Id)          & CAN_EXT_FRAME_LSB_Msk;
    CANx->IF0.ARB1 = (((pCanMsg->Id) >> 16) & CAN_EXT_FRAME_MSB_Msk) | CAN_IF_ARB1_XTD;
  }

  if (pCanMsg->FrameType)
    CANx->IF0.ARB1 |= CAN_IF_ARB1_DIR;
  else
    CANx->IF0.ARB1 &= (~CAN_IF_ARB1_DIR);

  CANx->IF0.MCR  = (CANx->IF0.MCR & (~CAN_IF_MCR_DLC_Msk)) | len;
  CANx->IF0.DA0R = ((u16)data[1] << 8) | data[0];
  CANx->IF0.DA1R = ((u16)data[3] << 8) | data[2];
  CANx->IF0.DB0R = ((u16)data[5] << 8) | data[4];
  CANx->IF0.DB1R = ((u16)data[7] << 8) | data[6];

  /* request transmission                                                                                   */
  CANx->IF0.CREQ &= (~CAN_FLAG_IF_BUSY);
  if (CANx->IF0.CREQ & CAN_FLAG_IF_BUSY)
  {
    return ERROR;
  }

  CANx->IF0.CREQ |= CAN_FLAG_IF_BUSY; /* Sending                                                            */

  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Get a message information in BASIC mode.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the buffer where received data will be stored.
 * @param  len: Pointer to a variable that will store the length of the received data.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_BasicReceiveMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8* len)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  if ((CANx->IF1.MCR & CAN_IF_MCR_NEWDAT) == 0)   /* In basic mode, receive data always save in IF1         */
  {
      return ERROR;
  }

  CANx->SR &= (~CAN_FLAG_RXOK);

  CANx->IF1.CMASK = CAN_IF_CMASK_ARB
                  | CAN_IF_CMASK_CONTROL
                  | CAN_IF_CMASK_DATAA
                  | CAN_IF_CMASK_DATAB;

  if ((CANx->IF1.MASK1 & CAN_IF_ARB1_XTD) == 0)
  {
    /* standard ID                                                                                          */
    pCanMsg->IdType = CAN_STD_ID;
    pCanMsg->Id = (CANx->IF1.MASK1 >> 2) & CAN_STD_FRAME_Msk;
  }
  else
  {
    /* extended ID                                                                                          */
    pCanMsg->IdType = CAN_EXT_ID;
    pCanMsg->Id     = (CANx->IF1.ARB1 & CAN_EXT_FRAME_MSB_Msk) << 16;
    pCanMsg->Id     |= (u32)CANx->IF1.ARB0;
  }

  *len     = CANx->IF1.MCR & CAN_IF_MCR_DLC_Msk;
  data[0] = CANx->IF1.DA0R & CAN_IF_DAT_A0_DATA0_Msk;
  data[1] = (CANx->IF1.DA0R & CAN_IF_DAT_A0_DATA1_Msk) >> CAN_IF_DAT_A0_DATA1_Pos;
  data[2] = CANx->IF1.DA1R & CAN_IF_DAT_A1_DATA2_Msk;
  data[3] = (CANx->IF1.DA1R & CAN_IF_DAT_A1_DATA3_Msk) >> CAN_IF_DAT_A1_DATA3_Pos;
  data[4] = CANx->IF1.DB0R & CAN_IF_DAT_B0_DATA4_Msk;
  data[5] = (CANx->IF1.DB0R & CAN_IF_DAT_B0_DATA5_Msk) >> CAN_IF_DAT_B0_DATA5_Pos;
  data[6] = CANx->IF1.DB1R & CAN_IF_DAT_B1_DATA6_Msk;
  data[7] = (CANx->IF1.DB1R & CAN_IF_DAT_B1_DATA7_Msk) >> CAN_IF_DAT_B1_DATA7_Pos;

  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Send CAN message.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the data buffer to be transmitted.
 * @param  len: Length of the data to be transmitted.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_Transmit(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  if (_CAN_SetTxMsg(CANx, pCanMsg, data, len) == ERROR)
  {
    return ERROR;
  }
  return (CAN_TriggerTxMsg(CANx, pCanMsg));
}

/*********************************************************************************************************//**
 * @brief  Gets the message, if received.
 *         The Interface Registers avoid conflict between the CPU accesses to the Message RAM and CAN message
 *         reception and transmission by buffering the data to be transferred.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the buffer where received data will be stored.
 * @param  len: Pointer to a variable that will store the length of the received data.
 * @retval RxStatus_TypeDef: Returns the status of the message reception. Possible values are:
 *    - MSG_OBJ_NOT_SET
 *    - MSG_NOT_RECEIVED
 *    - MSG_OVER_RUN
  ***********************************************************************************************************/
CAN_RxStatus_TypeDef CAN_Receive(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u32* len)
{
  u32 _MsgNum = pCanMsg->MsgNum;
  CAN_RxStatus_TypeDef status = MSG_OBJ_NOT_SET;
  bool firstMsg = TRUE;
  *len = 0;
  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) != FALSE)
  {
    while (1)
    {
      s32 ReadMsgStatus;
      if (_CAN_GetNewData(CANx, _MsgNum) == FALSE)
      {
        if (firstMsg == TRUE)
          status = MSG_NOT_RECEIVED;
        else
          status = MSG_RX_FINISH;
        break;
      }
      firstMsg = FALSE;
      ReadMsgStatus = _CAN_ReadMsgObj(CANx, _MsgNum, TRUE, pCanMsg, &data[*len], len);
      if (ReadMsgStatus != 0)
      {
        if (ReadMsgStatus == 2)
        {
          status = MSG_OVER_RUN;
          break;
        }
        status = MSG_RX_FINISH;
        break;
      }
      _MsgNum++;
    }
  }
  return status;
}

/*********************************************************************************************************//**
 * @brief  Cancels a transmit request.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_CancelTransmit(HT_CAN_TypeDef* CANx, CAN_MSG_TypeDef* pCanMsg)
{
  HT_CANIF_TypeDef *IFx = NULL;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return ERROR;
  }

  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }
  if ((IFx->CREQ & CAN_FLAG_IF_BUSY) == 0)
  {
    IFx->CMASK = CAN_IF_CMASK_WRRD | CAN_IF_CMASK_CLRINTPND;
    IFx->MCR   = 0;
    IFx->CREQ = pCanMsg->MsgNum;
  }

  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Discard the specified FIFO.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_DiscardRxMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return ERROR;
  }
  while (1)
  {
    HT_CANIF_TypeDef *IFx = NULL;
    while (IFx == NULL)
    {
      IFx = _GetFreeIF(CANx);
    }
    IFx->CMASK = CAN_IF_CMASK_TXRQSTNEWDAT | CAN_IF_CMASK_CONTROL;
    IFx->CREQ = pCanMsg->MsgNum;
    if (IFx->MCR & CAN_IF_MCR_EOB)
    {
      break;
    }
  }
  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  The function is used to configure several receive message objects.
 *         The Interface Registers avoid conflict between the CPU accesses to the Message RAM and CAN message
 *         reception and transmission by buffering the data to be transferred.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  FifoDepth: the number of MSG RAM of the FIFO.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_SetRxMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u32 FifoDepth)
{
  s32 i = 0;
  u32 _MsgNum;

  u32 eob;
  if (pCanMsg->MsgNum == 0)
  {
    _MsgNum = _CAN_GetValidMsg(CANx);
  }
  else
  {
    _MsgNum = pCanMsg->MsgNum;
  }
  if ((_MsgNum + FifoDepth) > MSG_OBJ_TOTAL_NUM)
  {
    return ERROR;
  }
  pCanMsg->MsgNum = _MsgNum;
  eob = 0;
  for (i = _MsgNum; i < FifoDepth + _MsgNum + 1; i++)
  {
    if (i == FifoDepth + _MsgNum)
    {
      eob = 1;
    }
    _CAN_SetRxMsgObj(CANx, i, pCanMsg, eob);
  }
  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Get the waiting status of a received message.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval TRUE: The corresponding message object has a new data bit is set, FALSE otherwise.
  ***********************************************************************************************************/
bool CAN_NewDataReceived(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg)
{

  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return FALSE;
  }
  return _CAN_GetNewData(CANx, pCanMsg->MsgNum);
}

/*********************************************************************************************************//**
 * @brief  Get the interrupt pending status of a message object.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval TRUE: The corresponding message object has a interrupt pending bit is set, FALSE otherwise.
  ***********************************************************************************************************/
bool CAN_GetMsgPending(HT_CAN_TypeDef* CANx, CAN_MSG_TypeDef* pCanMsg)
{
  u32 Pending =  CANx->IPR0;
  Pending    |=  CANx->IPR1 << 16;

  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return FALSE;
  }

  if ((Pending & 1 << (pCanMsg->MsgNum - 1)) == 0)
  {
    return FALSE;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Clear interrupt pending bit.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_ClearMsgPendingFlag(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg)
{
  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return ERROR;
  }
  _CAN_ClearMsgPendingFlag(CANx, pCanMsg->MsgNum);

  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Checks the transmission of a message object.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval 0: Transmitting, 1: Transmission successful, -1: Transmission failed.
  ***********************************************************************************************************/
s32 CAN_TransmitStatus(HT_CAN_TypeDef* CANx, CAN_MSG_TypeDef* pCanMsg)
{
  s32 TxStatus = 0;
  u32 u32Reg;
  s32 MsgNum = pCanMsg->MsgNum -1;

  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return -1;
  }

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  u32Reg = CANx->TRR0;
  u32Reg |= (CANx->TRR1 << 16);
  MsgNum = 1 << (MsgNum);
  if ((u32Reg & (MsgNum)) == 0)
  {
    TxStatus = 1;
  }

  u32Reg = CANx->NDR0;
  u32Reg |= (CANx->NDR1 << 16);
  if ((u32Reg & (MsgNum)) > 0)
  {
    TxStatus = -1;
  }
  return TxStatus;
}

/*********************************************************************************************************//**
 * @brief  Updates the data of a specified CAN message object.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the data array.
 * @param  len: Length of the data to be sent, in bytes (maximum 8 bytes).
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_UpdateTxMsgData(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len)
{
  HT_CANIF_TypeDef *IFx = NULL;

  len  &= CAN_IF_MCR_DLC_Msk;
  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }

  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return ERROR;
  }

  IFx->CMASK = CAN_IF_CMASK_WRRD | CAN_IF_CMASK_DATAA | CAN_IF_CMASK_DATAB | CAN_IF_CMASK_CONTROL;

  IFx->MCR   &=  (~CAN_IF_MCR_DLC_Msk);
  IFx->MCR   |=  (len & CAN_IF_MCR_DLC_Msk);
  IFx->DA0R  = ((u16)(data[1] << 8) | data[0]);
  IFx->DA1R  = ((u16)(data[3] << 8) | data[2]);
  IFx->DB0R  = ((u16)(data[5] << 8) | data[4]);
  IFx->DB1R  = ((u16)(data[7] << 8) | data[6]);

  IFx->CREQ = pCanMsg->MsgNum;

  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Set transmit request bit.
 *         If a transmission is requested by programming bit TxRqst/NewDat, the TxRqst will be ignored.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CAN_TriggerTxMsg(HT_CAN_TypeDef  *CANx, CAN_MSG_TypeDef* pCanMsg)
{
  HT_CANIF_TypeDef *IFx = NULL;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  if (CANx->SR & CAN_FLAG_BOFF)
  {
    return ERROR;
  }

  if (_CAN_CheckMsgIsValid(CANx, pCanMsg->MsgNum) == FALSE)
  {
    return ERROR;
  }

  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }

  IFx->CMASK  = CAN_IF_CMASK_WRRD | CAN_IF_CMASK_CONTROL;
  IFx->MCR    |= CAN_IF_MCR_NEWDAT | CAN_IF_MCR_TXRQST;
  IFx->CREQ   = pCanMsg->MsgNum;

  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Clears all pending message flags.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval None
  ***********************************************************************************************************/
void CAN_ClearAllMsgPendingFlag(HT_CAN_TypeDef *CANx)
{
  int i;
  u32 Pending =  CANx->IPR0;
  Pending    |=  CANx->IPR1 << 16;
  for (i = 0 ; i < MSG_OBJ_TOTAL_NUM ; i++)
  {
    if ((Pending & 1) == 1)
    {
      _CAN_ClearMsgPendingFlag(CANx, i + 1);
    }

    Pending = Pending >> 1;
    if (Pending == 0)
    {
      break;
    }
  }
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/
/** @defgroup CAN_Private_Functions CAN private functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief  The function is used to configure a transmit object.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the data buffer to be transmitted.
 * @param  len: Length of the data to be transmitted.
 * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus _CAN_SetTxMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len)
{
  HT_CANIF_TypeDef *IFx = NULL;
  if (pCanMsg->MsgNum == 0)
  {
    pCanMsg->MsgNum = _CAN_GetValidMsg(CANx);
  }
  if (pCanMsg->MsgNum > MSG_OBJ_TOTAL_NUM)
  {
    return ERROR;
  }

  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }

  /* update the contents needed for transmission                                                            */
  IFx->CMASK = CAN_IF_CMASK_WRRD | CAN_IF_CMASK_MASK | CAN_IF_CMASK_ARB
             | CAN_IF_CMASK_CONTROL | CAN_IF_CMASK_DATAA  | CAN_IF_CMASK_DATAB;

  if (pCanMsg->IdType == CAN_STD_ID)
  {
    /* standard ID                                                                                          */
    IFx->ARB0 = 0;
    IFx->ARB1 = (((pCanMsg->Id) & CAN_STD_FRAME_Msk) << 2) | CAN_IF_ARB1_DIR | CAN_IF_ARB1_MSGVAL;
  }
  else
  {
    /* extended ID                                                                                          */
    IFx->ARB0 = (pCanMsg->Id) & CAN_EXT_FRAME_LSB_Msk;
    IFx->ARB1 = (((pCanMsg->Id)  >> 16) & CAN_EXT_FRAME_MSB_Msk)
              | CAN_IF_ARB1_DIR | CAN_IF_ARB1_XTD | CAN_IF_ARB1_MSGVAL;
  }

  if (pCanMsg->FrameType)
    IFx->ARB1 |=   CAN_IF_ARB1_DIR;
  else
    IFx->ARB1 &= (~CAN_IF_ARB1_DIR);

  IFx->DA0R = ((u16)data[1] << 8) | data[0];
  IFx->DA1R = ((u16)data[3] << 8) | data[2];
  IFx->DB0R = ((u16)data[5] << 8) | data[4];
  IFx->DB1R = ((u16)data[7] << 8) | data[6];

  IFx->MCR = 0;

  IFx->MCR &= (~CAN_IF_MCR_RMTEN);

  IFx->MCR   |=  CAN_IF_MCR_NEWDAT | len | CAN_IF_MCR_TXIE;
  IFx->CREQ  = pCanMsg->MsgNum;
  return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Get the waiting status of a received message.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  MsgNum: Specifies the Message object number, from 1 to 32.
 * @retval TRUE: The corresponding message object has a new data bit is set, FALSE otherwise.
  ***********************************************************************************************************/
bool _CAN_GetNewData(HT_CAN_TypeDef *CANx, u32 MsgNum)
{
  u32 NewData =  CANx->NDR0;
  NewData    |=  CANx->NDR1 << 16;

  if ((NewData & 1 << (MsgNum - 1)) == 0)
  {
    return FALSE;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Get free interface.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval Free IF pointer. NULL: No IF is free
  ***********************************************************************************************************/
static HT_CANIF_TypeDef *_GetFreeIF(HT_CAN_TypeDef  *CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  if ((CANx->IF0.CREQ & CAN_FLAG_IF_BUSY) == 0)
  {
    return &CANx->IF0;
  }
  else if ((CANx->IF1.CREQ  & CAN_FLAG_IF_BUSY) == 0)
  {
    return &CANx->IF1;
  }
  else
  {
    return NULL;
   }
}

/*********************************************************************************************************//**
 * @brief  This function is used to set CAN to enter initialization mode and enable access bit timing
 *         register.After bit timing configuration ready, user must call CAN_LeaveInitMode() to leave
 *         initialization mode and lock bit timing register to let new configuration take effect.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval None
  ***********************************************************************************************************/
static void _CAN_EnterInitMode(HT_CAN_TypeDef *CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  CANx->CR |= CAN_CR_INIT;
  CANx->CR |= CAN_CR_CCE;
}

/*********************************************************************************************************//**
 * @brief  Leave initialization mode
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval None
  ***********************************************************************************************************/
static void _CAN_LeaveInitMode(HT_CAN_TypeDef *CANx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  CANx->CR &= (~(CAN_CR_INIT | CAN_CR_CCE));

  while (CANx->CR & CAN_CR_INIT); /* Check INIT bit is released                                             */
}

/*********************************************************************************************************//**
 * @brief  Set Rx message object
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  MsgNum: Specifies the Message object number, from 1 to 32.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  uSingleOrFifoLast: Specifies the end-of-buffer indicator.
 * @retval None
  ***********************************************************************************************************/
static void _CAN_SetRxMsgObj(HT_CAN_TypeDef  *CANx, u32 MsgNum, CAN_MSG_TypeDef* pCanMsg, u32 uSingleOrFifoLast)
{
  HT_CANIF_TypeDef *IFx = NULL;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));
  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }
  /* Command Setting                                                                                        */
  IFx->CMASK = CAN_IF_CMASK_WRRD    | CAN_IF_CMASK_MASK  | CAN_IF_CMASK_ARB |
               CAN_IF_CMASK_CONTROL | CAN_IF_CMASK_DATAA | CAN_IF_CMASK_DATAB;

  if (pCanMsg->IdType == CAN_STD_ID)  /* According STD/EXT ID format, Configure Mask and Arbitration register */
  {
    /* Standard Mask.(bit28..bit18).                                                                        */
    IFx->ARB0   = 0;
    IFx->ARB1   = CAN_IF_ARB1_MSGVAL | (pCanMsg->Id     & CAN_STD_FRAME_Msk) << 2;
    IFx->MASK0  = 0;
    IFx->MASK1  = CAN_IF_MASK1_MDIR  | (pCanMsg->IdMask & CAN_STD_FRAME_Msk) << 2;
  }
  else
  {
    IFx->ARB0   = pCanMsg->Id & CAN_EXT_FRAME_LSB_Msk;
    IFx->ARB1   = CAN_IF_ARB1_MSGVAL | CAN_IF_ARB1_XTD   | ((pCanMsg->Id >> 16) & CAN_EXT_FRAME_MSB_Msk);
    IFx->MASK0  = pCanMsg->IdMask & CAN_EXT_FRAME_LSB_Msk;
    IFx->MASK1  = CAN_IF_MASK1_MXTD  | CAN_IF_MASK1_MDIR | ((pCanMsg->IdMask>> 16) & CAN_EXT_FRAME_MSB_Msk);
  }

  IFx->MCR = CAN_IF_MCR_RXIE | CAN_IF_MCR_UMASK;

  if (pCanMsg->FrameType == CAN_REMOTE_FRAME)
  {

    IFx->ARB1  |= CAN_IF_ARB1_DIR;
    IFx->MCR   |= CAN_IF_MCR_RMTEN;
  }

  if (uSingleOrFifoLast)
    IFx->MCR |= CAN_IF_MCR_EOB;

  IFx->MCR &= (~CAN_IF_MCR_INTPND);
  IFx->MCR &= (~CAN_IF_MCR_NEWDAT);
  IFx->CREQ = MsgNum;
}

/*********************************************************************************************************//**
 * @brief  Gets the message
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  MsgNum: Specifies the Message object number, from 1 to 32.
 * @param  Release: Specifies the message release indicator.
 *         @arg TRUE : the message object is released when getting the data.
 *         @arg FALSE: the message object is not released.
 * @param  pCanMsg: Pointer to the message structure for transmitting or receiving data.
 * @param  data: Pointer to the buffer where received data will be stored.
 * @param  len: Pointer to a variable that will store the length of the received data.
* @retval  0: Data not empty, 1: Finish, 2: data over run
  ***********************************************************************************************************/
static s32 _CAN_ReadMsgObj(HT_CAN_TypeDef *CANx, u32 MsgNum, u32 Release, CAN_MSG_TypeDef* pCanMsg, u8* data, u32* len)
{
  HT_CANIF_TypeDef *IFx = NULL;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CAN(CANx));

  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }

  /* read the message contents                                                                              */
  IFx->CMASK = CAN_IF_CMASK_MASK
             | CAN_IF_CMASK_ARB
             | CAN_IF_CMASK_CONTROL
             | CAN_IF_CMASK_CLRINTPND
             | (Release ? CAN_IF_CMASK_TXRQSTNEWDAT : 0)
             | CAN_IF_CMASK_DATAA
             | CAN_IF_CMASK_DATAB;

  IFx->CREQ = MsgNum;

  while (IFx->CREQ & CAN_FLAG_IF_BUSY)
  {
    /*Wait                                                                                                  */
  }

  if ((IFx->ARB1 & CAN_IF_ARB1_XTD) == 0)
  {
    /* standard ID                                                                                          */
    pCanMsg->Id     = (IFx->ARB1 & CAN_IF_ARB1_ID_Msk) >> 2;
  }
  else
  {
    /* extended ID                                                                                          */
    pCanMsg->Id  = (IFx->ARB1 & CAN_EXT_FRAME_MSB_Msk) << 16;
    pCanMsg->Id |= IFx->ARB0;
  }
  if ((IFx->MCR & CAN_IF_MCR_RMTEN) == 0)
  {
    pCanMsg->FrameType     = CAN_DATA_FRAME;
  }
  else
  {
    pCanMsg->FrameType     = CAN_REMOTE_FRAME;
  }

  *len += IFx->MCR & CAN_IF_MCR_DLC_Msk;
  data[0] = IFx->DA0R & CAN_IF_DAT_A0_DATA0_Msk;
  data[1] = (IFx->DA0R & CAN_IF_DAT_A0_DATA1_Msk) >> CAN_IF_DAT_A0_DATA1_Pos;
  data[2] = IFx->DA1R & CAN_IF_DAT_A1_DATA2_Msk;
  data[3] = (IFx->DA1R & CAN_IF_DAT_A1_DATA3_Msk) >> CAN_IF_DAT_A1_DATA3_Pos;
  data[4] = IFx->DB0R & CAN_IF_DAT_B0_DATA4_Msk;
  data[5] = (IFx->DB0R & CAN_IF_DAT_B0_DATA5_Msk) >> CAN_IF_DAT_B0_DATA5_Pos;
  data[6] = IFx->DB1R & CAN_IF_DAT_B1_DATA6_Msk;
  data[7] = (IFx->DB1R & CAN_IF_DAT_B1_DATA7_Msk) >> CAN_IF_DAT_B1_DATA7_Pos;
  if ((IFx->MCR & CAN_IF_MCR_MSGLST) > 0)
  {
    IFx->CMASK =CAN_IF_CMASK_WRRD | CAN_IF_CMASK_CONTROL;
    IFx->MCR &= ~CAN_IF_MCR_MSGLST;
    IFx->CREQ = MsgNum;
    IFx->CMASK =  CAN_IF_CMASK_TXRQSTNEWDAT;
    IFx->CREQ = MsgNum;
    return 2;
  }
  if ((IFx->MCR & CAN_IF_MCR_EOB) > 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*********************************************************************************************************//**
 * @brief  Gets the first valid message object number from the CAN message valid registers (MVR0 and MVR1).
 *         This function scans through the message object table to find the first valid message object that is
 *         not set (i.e., where the corresponding bit in the message valid register is 0).
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @retval The index of the first valid message object that is not set.
 ***********************************************************************************************************/
static int _CAN_GetValidMsg(HT_CAN_TypeDef *CANx)
{
  s32 _MsgNum;
  u32 msgNumTable = CANx->MVR0;
  msgNumTable |=  CANx->MVR1 << 16;
  for (_MsgNum = 0 ; _MsgNum < MSG_OBJ_TOTAL_NUM ; _MsgNum++)
  {
    if ((msgNumTable & 1) == 0)
    {
      break;
    }
    msgNumTable = msgNumTable >> 1;
  }
  return _MsgNum + 1;
}

/*********************************************************************************************************//**
 * @brief  Checks if the specified message number is valid.
 * @param  CANx: Pointer to the CAN peripheral.
 * @param  MsgNum: The message number.
 * @retval TRUE if the message number is valid, FALSE otherwise.
 ***********************************************************************************************************/
static bool _CAN_CheckMsgIsValid(HT_CAN_TypeDef *CANx, u32 MsgNum)
{
  if ((MsgNum == 0) || (MsgNum > MSG_OBJ_TOTAL_NUM))
  {
    return FALSE;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Clears the pending flag for a specific CAN message object.
 * @param  CANx: where the CANx is the selected CAN from the CAN peripherals.
 * @param  MsgNum: The message number.
 * @retval None.
 ***********************************************************************************************************/
static void _CAN_ClearMsgPendingFlag(HT_CAN_TypeDef *CANx, u32 MsgNum)
{
  HT_CANIF_TypeDef *IFx = NULL;
  while (IFx == NULL)
  {
    IFx = _GetFreeIF(CANx);
  }
  IFx->CMASK = CAN_IF_CMASK_CLRINTPND;
  IFx->CREQ = MsgNum;
}
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
