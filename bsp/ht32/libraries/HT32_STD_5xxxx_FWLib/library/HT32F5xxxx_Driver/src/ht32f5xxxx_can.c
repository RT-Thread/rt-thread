/*********************************************************************************************************//**
 * @file    ht32f5xxxx_can.c
 * @version $Rev:: 7187         $
 * @date    $Date:: 2023-08-31 #$
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
static CANIF_NUMBER_Enum GetFreeIF(HT_CAN_TypeDef  *CANx);

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
 * @brief  This function is used to set CAN to enter initialization mode and enable access bit timing
 *         register.After bit timing configuration ready, user must call CAN_LeaveInitMode()
 *         to leave initialization mode and lock bit timing register to let new configuration
 *         take effect.
 * @param  CANx: The pointer to CAN module base address.
 * @retval None
  ***********************************************************************************************************/
void CAN_EnterInitMode(HT_CAN_TypeDef *CANx)
{
  CANx->CR |= CAN_CR_INIT_Msk;
  CANx->CR |= CAN_CR_CCE_Msk;
}

/*********************************************************************************************************//**
 * @brief  Leave initialization mode
 * @param  CANx: The pointer to CAN module base address.
 * @retval None
  ***********************************************************************************************************/
void CAN_LeaveInitMode(HT_CAN_TypeDef *CANx)
{
  CANx->CR &= (~(CAN_CR_INIT_Msk | CAN_CR_CCE_Msk));

  while(CANx->CR & CAN_CR_INIT_Msk); /* Check INIT bit is released */
}

/*********************************************************************************************************//**
 * @brief  This function is used to Wait message into message buffer in basic mode. Please notice the
 *         function is polling NEWDAT bit of MCR register by while loop and it is used in basic mode.
 * @param  CANx: The pointer to CAN module base address.
 * @retval None
  ***********************************************************************************************************/
void CAN_WaitMsg(HT_CAN_TypeDef *CANx)
{
  CANx->SR = 0x0; /* clr status */

  while(1)
  {
    if(CANx->IF1.MCR & CAN_IF_MCR_NEWDAT_Msk)   /* check new data */
    {
      /*DEBUG_PRINTF("New Data IN\n");*/
      break;
    }
    if(CANx->SR & CAN_SR_RXOK_Msk)
    {
      /*DEBUG_PRINTF("Rx OK\n");*/
    }
    if(CANx->SR & CAN_SR_LEC_Msk)
    {
      /*DEBUG_PRINTF("Error\n");*/
    }
  }
}

/*********************************************************************************************************//**
 * @brief  Get current bit rate
 * @param  CANx: The pointer to CAN module base address.
 * @retval Current Bit-Rate (kilo bit per second)
  ***********************************************************************************************************/
u32 CAN_GetCANBitRate(HT_CAN_TypeDef  *CANx)
{
  u32 wTseg1, wTseg2;
  u32 wBpr;

  wTseg1 = (CANx->BTR & CAN_BTR_TSEG0_Msk) >> CAN_BTR_TSEG0_Pos;
  wTseg2 = (CANx->BTR & CAN_BTR_TSEG1_Msk) >> CAN_BTR_TSEG1_Pos;
  wBpr  = CANx->BTR & CAN_BTR_BRP_Msk;
  wBpr |= CANx->BRPER << 6;

  return (SystemCoreClock / (wBpr + 1) / (wTseg1 + wTseg2 + 3));
}

/**********************************************************************************************************//**
 * @brief  Switch the CAN into test mode.
 * @param  CANx: The pointer to CAN module base address.
 * @param  u8TestMask Specifies the configuration in test modes
 *         @arg CAN_TEST_BASIC_Msk               : Enable basic mode of test mode
 *         @arg CAN_TEST_SILENT_Msk              : Enable silent mode of test mode
 *         @arg CAN_TEST_LBACK_Msk               : Enable Loop Back Mode of test mode
 *         @arg CAN_TEST_TX0_Msk/CAN_TEST_TX1_Msk: Control CAN_TX pin bit field
 * @retval None
  ***********************************************************************************************************/
void CAN_EnterTestMode(HT_CAN_TypeDef *CANx, u32 u8TestMask)
{
  CANx->CR |= CAN_CR_TEST_Msk;
  CANx->TR = u8TestMask;
}

/*********************************************************************************************************//**
 * @brief  Leave the test mode
 * @param  CANx: The pointer to CAN module base address.
 * @retval None
  ***********************************************************************************************************/
void CAN_LeaveTestMode(HT_CAN_TypeDef *CANx)
{
  CANx->CR |= CAN_CR_TEST_Msk;
  CANx->TR &= ~(CAN_TEST_LBACK_Msk | CAN_TEST_SILENT_Msk | CAN_TEST_BASIC_Msk);
  CANx->CR &= (~CAN_CR_TEST_Msk);
}

/*********************************************************************************************************//**
 * @brief  Get the waiting status of a received message.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgObj: Specifies the Message object number, from 0 to 31. 0 No message object has new data.
  ***********************************************************************************************************/
u32 CAN_IsNewDataReceived(HT_CAN_TypeDef *CANx, u32 MsgObj)
{
  MsgObj--;
  return (MsgObj < 16 ? CANx->NDR0 & (1 << MsgObj) : CANx->NDR1 & (1 << (MsgObj - 16)));
}

/*********************************************************************************************************//**
 * @brief  The function is used to Send CAN message in BASIC mode of test mode. Before call the API,
 *         the user should be call CAN_EnterTestMode(CAN_TEST_BASIC) and let CAN controller enter
 *         basic mode of test mode. Please notice IF0 Registers used as Tx Buffer in basic mode.
 * @param  CANx: The pointer to CAN module base address.
 * @param  pCanMsg: Pointer to the message structure containing data to transmit.
 * @retval TRUE:  Transmission OK, FALSE: Check busy flag of interface 0 is timeout
  ***********************************************************************************************************/
s32 CAN_BasicSendMsg(HT_CAN_TypeDef *CANx, STR_CANMSG_T_TypeDef* pCanMsg)
{
  u32 i = 0;
  while(CANx->IF0.CREQ & CAN_IF_CREQ_BUSY_Msk);

  CANx->SR &= (~CAN_SR_TXOK_Msk);

  if(pCanMsg->IdType == CAN_STD_ID)
  {
    /* standard ID*/
    CANx->IF0.ARB0 = 0;
    CANx->IF0.ARB1 = (((pCanMsg->Id) & 0x7FF) << 2) ;
  }
  else
  {
    /* extended ID*/
    CANx->IF0.ARB0 = (pCanMsg->Id) & 0xFFFF;
    CANx->IF0.ARB1 = ((pCanMsg->Id) & 0x1FFF0000) >> 16  | CAN_IF_ARB1_XTD_Msk;
  }

  if(pCanMsg->FrameType)
    CANx->IF0.ARB1 |= CAN_IF_ARB1_DIR_Msk;
  else
    CANx->IF0.ARB1 &= (~CAN_IF_ARB1_DIR_Msk);

  CANx->IF0.MCR = (CANx->IF0.MCR & (~CAN_IF_MCR_DLC_Msk)) | pCanMsg->DLC;
  CANx->IF0.DA0R = ((u16)pCanMsg->Data[1] << 8) | pCanMsg->Data[0];
  CANx->IF0.DA1R = ((u16)pCanMsg->Data[3] << 8) | pCanMsg->Data[2];
  CANx->IF0.DB0R = ((u16)pCanMsg->Data[5] << 8) | pCanMsg->Data[4];
  CANx->IF0.DB1R = ((u16)pCanMsg->Data[7] << 8) | pCanMsg->Data[6];

  /* request transmission*/
  CANx->IF0.CREQ &= (~CAN_IF_CREQ_BUSY_Msk);
  if(CANx->IF0.CREQ & CAN_IF_CREQ_BUSY_Msk)
  {
    return FALSE;
  }

  CANx->IF0.CREQ |= CAN_IF_CREQ_BUSY_Msk; /* Sending */

  for(i = 0; i < 0xFFFFF; i++)
  {
    if((CANx->IF0.CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
      break;
  }

  if(i >= 0xFFFFFFF)
  {
    return FALSE;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Get a message information in BASIC mode.
 * @param  CANx: The pointer to CAN module base address.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 * @retval FALSE: No any message received, TRUE: Receive a message success.
  ***********************************************************************************************************/
s32 CAN_BasicReceiveMsg(HT_CAN_TypeDef *CANx, STR_CANMSG_T_TypeDef* pCanMsg)
{
  if((CANx->IF1.MCR & CAN_IF_MCR_NEWDAT_Msk) == 0)   /* In basic mode, receive data always save in IF1 */
  {
      return FALSE;
  }

  CANx->SR &= (~CAN_SR_RXOK_Msk);

  CANx->IF1.CMASK = CAN_IF_CMASK_ARB_Msk
                  | CAN_IF_CMASK_CONTROL_Msk
                  | CAN_IF_CMASK_DATAA_Msk
                  | CAN_IF_CMASK_DATAB_Msk;

  if((CANx->IF1.MASK1 & CAN_IF_ARB1_XTD_Msk) == 0)
  {
    /* standard ID*/
    pCanMsg->IdType = CAN_STD_ID;
    pCanMsg->Id = (CANx->IF1.MASK1 >> 2) & 0x07FF;
  }
  else
  {
    /* extended ID*/
    pCanMsg->IdType = CAN_EXT_ID;
    pCanMsg->Id  = (CANx->IF1.ARB1 & 0x1FFF) << 16;
    pCanMsg->Id |= (u32)CANx->IF1.ARB0;
  }

  pCanMsg->FrameType = !((CANx->IF1.ARB1 & CAN_IF_ARB1_DIR_Msk) >> CAN_IF_ARB1_DIR_Pos);

  pCanMsg->DLC     = CANx->IF1.MCR & CAN_IF_MCR_DLC_Msk;
  pCanMsg->Data[0] = CANx->IF1.DA0R & CAN_IF_DAT_A0_DATA0_Msk;
  pCanMsg->Data[1] = (CANx->IF1.DA0R & CAN_IF_DAT_A0_DATA1_Msk) >> CAN_IF_DAT_A0_DATA1_Pos;
  pCanMsg->Data[2] = CANx->IF1.DA1R & CAN_IF_DAT_A1_DATA2_Msk;
  pCanMsg->Data[3] = (CANx->IF1.DA1R & CAN_IF_DAT_A1_DATA3_Msk) >> CAN_IF_DAT_A1_DATA3_Pos;
  pCanMsg->Data[4] = CANx->IF1.DB0R & CAN_IF_DAT_B0_DATA4_Msk;
  pCanMsg->Data[5] = (CANx->IF1.DB0R & CAN_IF_DAT_B0_DATA5_Msk) >> CAN_IF_DAT_B0_DATA5_Pos;
  pCanMsg->Data[6] = CANx->IF1.DB1R & CAN_IF_DAT_B1_DATA6_Msk;
  pCanMsg->Data[7] = (CANx->IF1.DB1R & CAN_IF_DAT_B1_DATA7_Msk) >> CAN_IF_DAT_B1_DATA7_Pos;

  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Set Rx message object
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgObj: Specifies the Message object number, from 0 to 31.
 *         @arg CAN_STD_ID (standard ID, 11-bit)
 *         @arg CAN_EXT_ID (extended ID, 29-bit)
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 * @retval TRUE: SUCCESS, FALSE: No useful interface.
  ***********************************************************************************************************/
s32 CAN_SetRxMsgObj(HT_CAN_TypeDef  *CANx, u32 MsgObj, STR_CANMSG_R_TypeDef* pCanMsg)
{
  u32 u8MsgIfNum = 0;

  if((u8MsgIfNum = GetFreeIF(CANx)) == 2)                         /* Check Free Interface for configure */
  {
      return FALSE;
  }

  if (u8MsgIfNum == 1)
  {
    /* Command Setting */
    CANx->IF1.CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                      CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

    if(pCanMsg->IdType == CAN_STD_ID)    /* According STD/EXT ID format,Configure Mask and Arbitration register */
    {
      CANx->IF1.ARB0 = 0;
      CANx->IF1.ARB1 = CAN_IF_ARB1_MSGVAL_Msk | (pCanMsg->Id & 0x7FF) << 2;
      CANx->IF1.MASK0 = pCanMsg->MASK0;
      CANx->IF1.MASK1 = pCanMsg->MASK1;
    }
    else
    {
      CANx->IF1.ARB0 = pCanMsg->Id & 0xFFFF;
      CANx->IF1.ARB1 = CAN_IF_ARB1_MSGVAL_Msk | CAN_IF_ARB1_XTD_Msk | (pCanMsg->Id & 0x1FFF0000) >> 16;
    }

    CANx->IF1.MCR |= CAN_IF_MCR_RXIE_Msk | pCanMsg->MCR ;

    if(pCanMsg->UMASK)
    {
      CANx->IF1.MCR |= CAN_IF_MCR_UMASK_Msk;
      CANx->IF1.MASK0 = pCanMsg->MASK0;
      CANx->IF1.MASK1 = pCanMsg->MASK1;
    }

    if(pCanMsg->RMTEN)
      CANx->IF1.MCR |= CAN_IF_MCR_RMTEN_Msk;
    else
      CANx->IF1.MCR &= (~CAN_IF_MCR_RMTEN_Msk);

    if(pCanMsg->EOB)
      CANx->IF1.MCR |= CAN_IF_MCR_EOB_Msk;
    else
      CANx->IF1.MCR &= (~CAN_IF_MCR_EOB_Msk);

    CANx->IF1.MCR &= (~CAN_IF_MCR_INTPND_Msk);
    CANx->IF1.MCR &= (~CAN_IF_MCR_NEWDAT_Msk);
    CANx->IF1.DA0R  = 0;
    CANx->IF1.DA1R  = 0;
    CANx->IF1.DB0R  = 0;
    CANx->IF1.DB1R  = 0;
    CANx->IF1.CREQ = MsgObj+1;
  }
  else
  {
    /* Command Setting */
    CANx->IF0.CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                      CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

    if(pCanMsg->IdType == CAN_STD_ID)    /* According STD/EXT ID format,Configure Mask and Arbitration register */
    {
      CANx->IF0.ARB0 = 0;
      CANx->IF0.ARB1 = CAN_IF_ARB1_MSGVAL_Msk | (pCanMsg->Id & 0x7FF) << 2;
      CANx->IF0.MASK0 = pCanMsg->MASK0;
      CANx->IF0.MASK1 = pCanMsg->MASK1;
    }
    else
    {
      CANx->IF0.ARB0 = pCanMsg->Id & 0xFFFF;
      CANx->IF0.ARB1 = CAN_IF_ARB1_MSGVAL_Msk | CAN_IF_ARB1_XTD_Msk | (pCanMsg->Id & 0x1FFF0000) >> 16;
    }

    CANx->IF0.MCR |= CAN_IF_MCR_RXIE_Msk | pCanMsg->MCR ;

    if(pCanMsg->UMASK)
    {
      CANx->IF0.MCR |= CAN_IF_MCR_UMASK_Msk;
      CANx->IF0.MASK0 = pCanMsg->MASK0;
      CANx->IF0.MASK1 = pCanMsg->MASK1;
    }

    if(pCanMsg->RMTEN)
      CANx->IF0.MCR |= CAN_IF_MCR_RMTEN_Msk;
    else
      CANx->IF0.MCR &= (~CAN_IF_MCR_RMTEN_Msk);

    if(pCanMsg->EOB)
      CANx->IF0.MCR |= CAN_IF_MCR_EOB_Msk;
    else
      CANx->IF0.MCR &= (~CAN_IF_MCR_EOB_Msk);

    CANx->IF0.MCR &= (~CAN_IF_MCR_INTPND_Msk);
    CANx->IF0.MCR &= (~CAN_IF_MCR_NEWDAT_Msk);
    CANx->IF0.DA0R  = 0;
    CANx->IF0.DA1R  = 0;
    CANx->IF0.DB0R  = 0;
    CANx->IF0.DB1R  = 0;
    CANx->IF0.CREQ = MsgObj+1;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Gets the message
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgObj: Specifies the Message object number, from 0 to 31.
 * @param  Release: Specifies the message release indicator.
 *         @arg TRUE : the message object is released when getting the data.
 *         @arg FALSE: the message object is not released.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 * @retval TRUE Success, FALSE No any message received
  ***********************************************************************************************************/
s32 CAN_ReadMsgObj(HT_CAN_TypeDef *CANx, u32 MsgObj, u32 Release, STR_CANMSG_T_TypeDef* pCanMsg)
{
  u32 u8MsgIfNum = 0;

  if(!CAN_IsNewDataReceived(CANx, MsgObj))
  {
    return FALSE;
  }

  if((u8MsgIfNum = GetFreeIF(CANx)) == 2)                         /* Check Free Interface for configure */
  {
    return FALSE;
  }

  CANx->SR &= (~CAN_SR_RXOK_Msk);

  if (u8MsgIfNum == 1)
  {
  /* read the message contents*/
    CANx->IF1.CMASK = CAN_IF_CMASK_MASK_Msk
                    | CAN_IF_CMASK_ARB_Msk
                    | CAN_IF_CMASK_CONTROL_Msk
                    | CAN_IF_CMASK_CLRINTPND_Msk
                    | (Release ? CAN_IF_CMASK_TXRQSTNEWDAT_Msk : 0)
                    | CAN_IF_CMASK_DATAA_Msk
                    | CAN_IF_CMASK_DATAB_Msk;

    CANx->IF1.CREQ = MsgObj;

    while(CANx->IF1.CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
      /*Wait*/
    }

    if((CANx->IF1.ARB1 & CAN_IF_ARB1_XTD_Msk) == 0)
    {
      /* standard ID*/
      pCanMsg->IdType = CAN_STD_ID;
      pCanMsg->Id     = (CANx->IF1.ARB1 & CAN_IF_ARB1_ID_Msk) >> 2;
    }
    else
    {
      /* extended ID*/
      pCanMsg->IdType = CAN_EXT_ID;
      pCanMsg->Id  = (CANx->IF1.ARB1 & 0x1FFF) << 16 ;
      pCanMsg->Id |= CANx->IF1.ARB0;
    }
    pCanMsg->MCR     = CANx->IF1.MCR;
    pCanMsg->DLC     = CANx->IF1.MCR & CAN_IF_MCR_DLC_Msk;
    pCanMsg->EOB     = CANx->IF1.MCR & CAN_IF_MCR_EOB_Msk;
    pCanMsg->Data[0] = CANx->IF1.DA0R & CAN_IF_DAT_A0_DATA0_Msk;
    pCanMsg->Data[1] = (CANx->IF1.DA0R & CAN_IF_DAT_A0_DATA1_Msk) >> CAN_IF_DAT_A0_DATA1_Pos;
    pCanMsg->Data[2] = CANx->IF1.DA1R & CAN_IF_DAT_A1_DATA2_Msk;
    pCanMsg->Data[3] = (CANx->IF1.DA1R & CAN_IF_DAT_A1_DATA3_Msk) >> CAN_IF_DAT_A1_DATA3_Pos;
    pCanMsg->Data[4] = CANx->IF1.DB0R & CAN_IF_DAT_B0_DATA4_Msk;
    pCanMsg->Data[5] = (CANx->IF1.DB0R & CAN_IF_DAT_B0_DATA5_Msk) >> CAN_IF_DAT_B0_DATA5_Pos;
    pCanMsg->Data[6] = CANx->IF1.DB1R & CAN_IF_DAT_B1_DATA6_Msk;
    pCanMsg->Data[7] = (CANx->IF1.DB1R & CAN_IF_DAT_B1_DATA7_Msk) >> CAN_IF_DAT_B1_DATA7_Pos;
  }
  else
  {
    /* read the message contents*/
    CANx->IF0.CMASK = CAN_IF_CMASK_MASK_Msk
                    | CAN_IF_CMASK_ARB_Msk
                    | CAN_IF_CMASK_CONTROL_Msk
                    | CAN_IF_CMASK_CLRINTPND_Msk
                    | (Release ? CAN_IF_CMASK_TXRQSTNEWDAT_Msk : 0)
                    | CAN_IF_CMASK_DATAA_Msk
                    | CAN_IF_CMASK_DATAB_Msk;

    CANx->IF0.CREQ = MsgObj;

    while(CANx->IF0.CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
      /*Wait*/
    }

    if((CANx->IF0.ARB1 & CAN_IF_ARB1_XTD_Msk) == 0)
    {
      /* standard ID*/
      pCanMsg->IdType = CAN_STD_ID;
      pCanMsg->Id     = (CANx->IF0.ARB1 & CAN_IF_ARB1_ID_Msk) >> 2;
    }
    else
    {
      /* extended ID*/
      pCanMsg->IdType = CAN_EXT_ID;
      pCanMsg->Id  = (CANx->IF0.ARB1 & 0x1FFF) << 16;
      pCanMsg->Id |= CANx->IF0.ARB0;
    }

    pCanMsg->MCR     = CANx->IF0.MCR;
    pCanMsg->DLC     = CANx->IF0.MCR & CAN_IF_MCR_DLC_Msk;
    pCanMsg->EOB     = CANx->IF0.MCR & CAN_IF_MCR_EOB_Msk;
    pCanMsg->Data[0] = CANx->IF0.DA0R & CAN_IF_DAT_A0_DATA0_Msk;
    pCanMsg->Data[1] = (CANx->IF0.DA0R & CAN_IF_DAT_A0_DATA1_Msk) >> CAN_IF_DAT_A0_DATA1_Pos;
    pCanMsg->Data[2] = CANx->IF0.DA1R & CAN_IF_DAT_A1_DATA2_Msk;
    pCanMsg->Data[3] = (CANx->IF0.DA1R & CAN_IF_DAT_A1_DATA3_Msk) >> CAN_IF_DAT_A1_DATA3_Pos;
    pCanMsg->Data[4] = CANx->IF0.DB0R & CAN_IF_DAT_B0_DATA4_Msk;
    pCanMsg->Data[5] = (CANx->IF0.DB0R & CAN_IF_DAT_B0_DATA5_Msk) >> CAN_IF_DAT_B0_DATA5_Pos;
    pCanMsg->Data[6] = CANx->IF0.DB1R & CAN_IF_DAT_B1_DATA6_Msk;
    pCanMsg->Data[7] = (CANx->IF0.DB1R & CAN_IF_DAT_B1_DATA7_Msk) >> CAN_IF_DAT_B1_DATA7_Pos;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Set bus baud-rate.
 * @param  CANx: The pointer to CAN module base address.
 * @param  wBaudRate: The target CAN baud-rate. The range of u32BaudRate is 1~1000KHz.
 * @retval CurrentBitRate: Real baud-rate value.
  ***********************************************************************************************************/
u32 CAN_SetBaudRate(HT_CAN_TypeDef *CANx, u32 wBaudRate)
{
  u32 wTseg0, wTseg1;
  u32 wBrp;
  u32 wValue;

  CAN_EnterInitMode(CANx);

  SystemCoreClockUpdate();

  wTseg0 = 2;
  wTseg1 = 1;

  wValue = SystemCoreClock / wBaudRate;

  while(1)
  {
    if(((wValue % (wTseg0 + wTseg1 + 3)) == 0))
      break;
    if(wTseg1 < 7)
      wTseg1++;

    if((wValue % (wTseg0 + wTseg1 + 3)) == 0)
      break;
    if(wTseg0 < 15)
      wTseg0++;
    else
    {
      wTseg0 = 2;
      wTseg1 = 1;
      break;
    }
  }

  wBrp  = SystemCoreClock / (wBaudRate) / (wTseg0 + wTseg1 + 3) - 1;

  wValue = ((u32)wTseg1 << CAN_BTR_TSEG1_Pos) | ((u32)wTseg0 << CAN_BTR_TSEG0_Pos) |
            (wBrp & CAN_BTR_BRP_Msk) | (CANx->BTR & CAN_BTR_SJW_Msk);
  CANx->BTR = wValue;
  CANx->BRPER = (wBrp >> 6) & 0x0F;

  CAN_LeaveInitMode(CANx);

  return (CAN_GetCANBitRate(CANx));
}

/*********************************************************************************************************//**
 * @brief  The function is used to disable all CAN interrupt.
 * @param  CANx: The pointer to CAN module base address.
 * @retval None
  ***********************************************************************************************************/
void CAN_Close(HT_CAN_TypeDef *CANx)
{
  CAN_DisableInt(CANx, (CAN_CR_IE_Msk | CAN_CR_SIE_Msk | CAN_CR_EIE_Msk));
}

/*********************************************************************************************************//**
 * @brief  Set CAN operation mode and target baud-rate.
 * @param  CANx: The pointer to CAN module base address.
 * @param  wBaudRate The target CAN baud-rate. The range of u32BaudRate is 1~1000KHz.
 * @param  wMode The CAN operation mode.
 *         @arg  CAN_NORMAL_MODE : Normal operation.
 *         @arg  CAN_BASIC_MODE  : Basic operation.
 *         @arg  CAN_SILENT_MODE : Silent operation.
 *         @arg  CAN_LBACK_MODE  : Loop Back operation.
 *         @arg  CAN_LBS_MODE    : Loop Back combined with Silent  operation.
 * @retval u32CurrentBitRate Real baud-rate value.
  ***********************************************************************************************************/
u32 CAN_Open(HT_CAN_TypeDef *CANx, u32 wBaudRate, u32 wMode)
{
  u32 CurrentBitRate;

  CurrentBitRate = CAN_SetBaudRate(CANx, wBaudRate);

  if(wMode)
    CAN_EnterTestMode(CANx, wMode);

  return CurrentBitRate;
}

/*********************************************************************************************************//**
 * @brief  The function is used to configure a transmit object.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgNum: Specifies the Message object number, from 0 to 31.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 * @retval FALSE No useful interface, TRUE Config message object success.
  ***********************************************************************************************************/
s32 CAN_SetTxMsg(HT_CAN_TypeDef *CANx, u32 MsgNum , STR_CANMSG_T_TypeDef* pCanMsg)
{
  u32 MsgIfNum = 0;
  u32 i = 0;

  while((MsgIfNum = GetFreeIF(CANx)) == 2)
  {
    i++;
    if(i > 0x10000000)
    return FALSE;
  }

  /* update the contents needed for transmission*/
  if(MsgIfNum ==0)
  {
    CANx->IF0.CMASK = 0xF3;  /* CAN_CMASK_WRRD_Msk | CAN_CMASK_MASK_Msk | CAN_CMASK_ARB_Msk
                                         | CAN_CMASK_CONTROL_Msk | CAN_CMASK_DATAA_Msk  | CAN_CMASK_DATAB_Msk ; */

    if(pCanMsg->IdType == CAN_STD_ID)
    {
      /* standard ID*/
      CANx->IF0.ARB0 = 0;
      CANx->IF0.ARB1 = (((pCanMsg->Id) & 0x7FF) << 2) | CAN_IF_ARB1_DIR_Msk | CAN_IF_ARB1_MSGVAL_Msk;
    }
    else
    {
      /* extended ID*/
      CANx->IF0.ARB0 = (pCanMsg->Id) & 0xFFFF;
      CANx->IF0.ARB1 = ((pCanMsg->Id) & 0x1FFF0000) >> 16 | CAN_IF_ARB1_DIR_Msk
                                    | CAN_IF_ARB1_XTD_Msk | CAN_IF_ARB1_MSGVAL_Msk;
    }

    if(pCanMsg->FrameType)
      CANx->IF0.ARB1 |=   CAN_IF_ARB1_DIR_Msk;
    else
      CANx->IF0.ARB1 &= (~CAN_IF_ARB1_DIR_Msk);

    CANx->IF0.DA0R = ((u16)pCanMsg->Data[1] << 8) | pCanMsg->Data[0];
    CANx->IF0.DA1R = ((u16)pCanMsg->Data[3] << 8) | pCanMsg->Data[2];
    CANx->IF0.DB0R = ((u16)pCanMsg->Data[5] << 8) | pCanMsg->Data[4];
    CANx->IF0.DB1R = ((u16)pCanMsg->Data[7] << 8) | pCanMsg->Data[6];
    CANx->IF0.MCR = 0;
    if(pCanMsg->RMTEN)
      CANx->IF0.MCR |= CAN_IF_MCR_RMTEN_Msk;
    else
      CANx->IF0.MCR &= (~CAN_IF_MCR_RMTEN_Msk);
    if(pCanMsg->EOB)
      CANx->IF0.MCR |= CAN_IF_MCR_EOB_Msk;
    else
      CANx->IF0.MCR &= (~CAN_IF_MCR_EOB_Msk);

    CANx->IF0.MCR   |=  CAN_IF_MCR_NEWDAT_Msk | pCanMsg->DLC | CAN_IF_MCR_TXIE_Msk  ;
    CANx->IF0.CREQ   = MsgNum +1;
  }
  else
  {
    CANx->IF1.CMASK = 0xF3;  /* CAN_CMASK_WRRD_Msk | CAN_CMASK_MASK_Msk | CAN_CMASK_ARB_Msk
                                         | CAN_CMASK_CONTROL_Msk | CAN_CMASK_DATAA_Msk  | CAN_CMASK_DATAB_Msk ; */

    if(pCanMsg->IdType == CAN_STD_ID)
    {
      /* standard ID*/
      CANx->IF1.ARB0 = 0;
      CANx->IF1.ARB1 = (((pCanMsg->Id) & 0x7FF) << 2) | CAN_IF_ARB1_DIR_Msk | CAN_IF_ARB1_MSGVAL_Msk;
    }
    else
    {
      /* extended ID*/
      CANx->IF1.ARB0 = (pCanMsg->Id) & 0xFFFF;
      CANx->IF1.ARB1 = ((pCanMsg->Id) & 0x1FFF0000) >> 16 | CAN_IF_ARB1_DIR_Msk
                                    | CAN_IF_ARB1_XTD_Msk | CAN_IF_ARB1_MSGVAL_Msk;
    }

    if(pCanMsg->FrameType)
      CANx->IF1.ARB1 |=   CAN_IF_ARB1_DIR_Msk;
    else
      CANx->IF1.ARB1 &= (~CAN_IF_ARB1_DIR_Msk);

    CANx->IF1.DA0R = ((u16)pCanMsg->Data[1] << 8) | pCanMsg->Data[0];
    CANx->IF1.DA1R = ((u16)pCanMsg->Data[3] << 8) | pCanMsg->Data[2];
    CANx->IF1.DB0R = ((u16)pCanMsg->Data[5] << 8) | pCanMsg->Data[4];
    CANx->IF1.DB1R = ((u16)pCanMsg->Data[7] << 8) | pCanMsg->Data[6];

    CANx->IF1.MCR = 0;

    if(pCanMsg->RMTEN)
      CANx->IF1.MCR |= CAN_IF_MCR_RMTEN_Msk;
    else
      CANx->IF1.MCR &= (~CAN_IF_MCR_RMTEN_Msk);

    if(pCanMsg->EOB)
      CANx->IF1.MCR |= CAN_IF_MCR_EOB_Msk;
    else
      CANx->IF1.MCR &= (~CAN_IF_MCR_EOB_Msk);

    CANx->IF1.MCR   |=  CAN_IF_MCR_NEWDAT_Msk | pCanMsg->DLC | CAN_IF_MCR_TXIE_Msk  ;
    CANx->IF1.CREQ   = MsgNum +1;
  }
  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Set transmit request bit.
 *         If a transmission is requested by programming bit TxRqst/NewDat (IFn_CMASK[2]), the TxRqst
 *         (IFn_MCON[8]) will be ignored.
 * @param  CANx: The pointer to CAN module base address.
 * @param  u32MsgNum: Specifies the Message object number, from 0 to 31.
 * @retval TRUE: Start transmit message.
  ***********************************************************************************************************/
s32 CAN_TriggerTxMsg(HT_CAN_TypeDef  *CANx, u32 u32MsgNum)
{
  CANx->SR &= (~CAN_SR_TXOK_Msk);

  /* read the message contents*/
  CANx->IF1.CMASK = CAN_IF_CMASK_CLRINTPND_Msk
                  | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;

  CANx->IF1.CREQ =  u32MsgNum+1;

  while(CANx->IF1.CREQ & CAN_IF_CREQ_BUSY_Msk)
  {
      /*Wait*/
  }
  CANx->IF0.CMASK  = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
  CANx->IF0.CREQ  = u32MsgNum+1;

  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Enable CAN interrupt.
 *         The application software has two possibilities to follow the source of a message interrupt.
 *         First, it can follow the IntId in the Interrupt Register and second it can poll the Interrupt Pending Register.
 * @param  CANx: The pointer to CAN module base address.
 * @param  u32Mask: Interrupt Mask.
 *         @arg CAN_CR_IE_Msk : Module interrupt enable.
 *         @arg CAN_CR_SIE_Msk: Status change interrupt enable.
 *         @arg CAN_CR_EIE_Msk: Error interrupt enable.
 * @retval None
  ***********************************************************************************************************/
void CAN_EnableInt(HT_CAN_TypeDef *CANx, u32 u32Mask)
{
  CAN_EnterInitMode(CANx);

  CANx->CR = (CANx->CR & 0xF1) | ((u32Mask & CAN_CR_IE_Msk) ? CAN_CR_IE_Msk : 0)
              | ((u32Mask & CAN_CR_SIE_Msk) ? CAN_CR_SIE_Msk : 0)
              | ((u32Mask & CAN_CR_EIE_Msk) ? CAN_CR_EIE_Msk : 0);


  CAN_LeaveInitMode(CANx);
}

/*********************************************************************************************************//**
 * @brief  Disable CAN interrupt.
 * @param  CANx: The pointer to CAN module base address.
 * @param  Mask: Interrupt Mask. (CAN_CR_IE_Msk / CAN_CR_SIE_Msk / CAN_CR_EIE_Msk).
 * @retval None
  ***********************************************************************************************************/
void CAN_DisableInt(HT_CAN_TypeDef *CANx, u32 Mask)
{
  CAN_EnterInitMode(CANx);

  CANx->CR = CANx->CR & ~(CAN_CR_IE_Msk | ((Mask & CAN_CR_SIE_Msk) ? CAN_CR_SIE_Msk : 0)
                            | ((Mask & CAN_CR_EIE_Msk) ? CAN_CR_EIE_Msk : 0));

  CAN_LeaveInitMode(CANx);
}


/*********************************************************************************************************//**
 * @brief  The function is used to configure a receive message object.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgNum: Specifies the Message object number, from 0 to 31.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 *     @arg CAN_STD_ID: The 11-bit identifier.
 *     @arg CAN_EXT_ID: The 29-bit identifier.
 * @retval FALSE No useful interface, TRUE Configure a receive message object success.
  ***********************************************************************************************************/
s32 CAN_SetRxMsg(HT_CAN_TypeDef *CANx, u32 MsgNum , STR_CANMSG_R_TypeDef* pCanMsg)
{
  u32 TimeOutCount = 0;

  while(CAN_SetRxMsgObj(CANx, MsgNum, pCanMsg) == FALSE)
  {
    TimeOutCount++;

    if(TimeOutCount >= 0x10000000) return FALSE;
  }

  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  The function is used to configure several receive message objects.
 *         The Interface Registers avoid conflict between the CPU accesses to the Message RAM and CAN message
 *         reception and transmission by buffering the data to be transferred.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgNum: The starting MSG RAM number(0 ~ 31).
 * @param  MsgCount: the number of MSG RAM of the FIFO.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 *         @arg CAN_STD_ID: The 11-bit identifier.
 *         @arg CAN_EXT_ID: The 29-bit identifier.
 * @retval FALSE No useful interface, TRUE Configure receive message objects success.
  ***********************************************************************************************************/
s32 CAN_SetMultiRxMsg(HT_CAN_TypeDef *CANx, u32 MsgNum , u32 MsgCount, STR_CANMSG_R_TypeDef* pCanMsg)
{
  u32 i = 0;
  u32 TimeOutCount;

  for(i = 1; i < MsgCount+1; i++)
  {
    TimeOutCount = 0;
    pCanMsg->EOB = 0;

    if(i == MsgCount)
      pCanMsg->EOB=1;

    while(CAN_SetRxMsgObj(CANx, MsgNum, pCanMsg) == FALSE)
    {
      TimeOutCount++;

      if(TimeOutCount >= 0x10000000)
        return FALSE;
    }
    MsgNum ++;
  }

  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Send CAN message.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgNum: Specifies the Message object number, from 0 to 31.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 * @retval FALSE: 1. When operation in basic mode: Transmit message time out.
 *                2. When operation in normal mode: No useful interface.
 *         TRUE: Transmit Message success.
  ***********************************************************************************************************/
s32 CAN_Transmit(HT_CAN_TypeDef *CANx, u32 MsgNum , STR_CANMSG_T_TypeDef* pCanMsg)
{
  if((CANx->CR & CAN_CR_TEST_Msk) && (CANx->TR & CAN_TEST_BASIC_Msk))
  {
    return (CAN_BasicSendMsg(CANx, pCanMsg));
  }
  else
  {
    if(CAN_SetTxMsg(CANx, MsgNum, pCanMsg) == FALSE)
        return FALSE;

    CANx->SR &= (~CAN_SR_TXOK_Msk);

    /* read the message contents*/
    CANx->IF1.CMASK = CAN_IF_CMASK_CLRINTPND_Msk
                    | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;

    CANx->IF1.CREQ =  MsgNum+1;

    while(CANx->IF1.CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
      /*Wait*/
    }
    CANx->IF0.CMASK  = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    CANx->IF0.CREQ   = MsgNum+1;
  }

  return TRUE;
}

/*********************************************************************************************************//**
 * @brief  Gets the message, if received.
 *         The Interface Registers avoid conflict between the CPU accesses to the Message RAM and CAN message
 *         reception and transmission by buffering the data to be transferred.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgNum: Specifies the Message object number, from 0 to 31.
 * @param  pCanMsg: Pointer to the message structure where received data is copied.
 * @retval FALSE: No any message received, TRUE: Receive Message success.
  ***********************************************************************************************************/
s32 CAN_Receive(HT_CAN_TypeDef *CANx, u32 MsgNum , STR_CANMSG_T_TypeDef* pCanMsg)
{
  if((CANx->CR & CAN_CR_TEST_Msk) && (CANx->TR & CAN_TEST_BASIC_Msk))
  {
    return (CAN_BasicReceiveMsg(CANx, pCanMsg));
  }
  else
  {
    return CAN_ReadMsgObj(CANx, MsgNum, TRUE, pCanMsg);
  }
}

/*********************************************************************************************************//**
 * @brief  Clear interrupt pending bit.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgNum: Specifies the Message object number, from 0 to 31.
 * @retval None
  ***********************************************************************************************************/
void CAN_CLR_INT_PENDING_BIT(HT_CAN_TypeDef *CANx, u32 MsgNum)
{
  u32 u32IFBusyCount = 0;

  while(u32IFBusyCount < 0x10000000)
  {
    if((CANx->IF0.CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
    {
      CANx->IF0.CMASK = CAN_IF_CMASK_CLRINTPND_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
      CANx->IF0.CREQ = MsgNum+1;
      break;
    }
    else if((CANx->IF1.CREQ  & CAN_IF_CREQ_BUSY_Msk) == 0)
    {
      CANx->IF1.CMASK = CAN_IF_CMASK_CLRINTPND_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
      CANx->IF1.CREQ = MsgNum+1;
      break;
    }

    u32IFBusyCount++;
  }
}

/*********************************************************************************************************//**
 * @brief  The function is used to configure Mask as the message object.
 * @param  CANx: The pointer to CAN module base address.
 * @param  MsgObj: Specifies the Message object number, from 0 to 31.
 * @param  MaskMsg: Pointer to the message structure where received data is copied.
 *         @arg CAN_STD_ID: The 11-bit identifier.
 *         @arg CAN_EXT_ID: The 29-bit identifier.
 * @retval FALSE No useful interface, TRUE Configure a receive message object success.
  ***********************************************************************************************************/
s32 CAN_MsgObjMaskConfig(HT_CAN_TypeDef *CANx, u32 MsgObj, STR_CANMSG_R_TypeDef* MaskMsg)
{
  if(MaskMsg->IdType == CAN_STD_ID)
  {
    /* standard ID*/
    CANx->IF0.ARB0 = 0;
    CANx->IF0.ARB1 = (((MaskMsg->Id) & 0x7FF) << 2)  | CAN_IF_ARB1_MSGVAL_Msk ;

    /* Set the Mask Standard ID(11-bit) for IFn Mask Register is used for acceptance filtering*/
    CANx->IF0.MASK0 =  0;
    CANx->IF0.MASK1 = ((MaskMsg->Id & 0x7FF) << 2) ;
  }
  else
  {
    /* extended ID*/
    CANx->IF0.ARB0 = (MaskMsg->Id) & 0xFFFF;
    CANx->IF0.ARB1 = ((MaskMsg->Id) & 0x1FFF0000) >> 16 | CAN_IF_ARB1_DIR_Msk
                   | CAN_IF_ARB1_XTD_Msk | CAN_IF_ARB1_MSGVAL_Msk;
    /* Set the Mask Extended ID(29-bit) for IFn Mask Register is used for acceptance filtering*/
    CANx->IF0.MASK0 = (MaskMsg->Id) & 0xFFFF;
    CANx->IF0.MASK1 = ((MaskMsg->Id) & 0x1FFF0000) >> 16 ;
  }

  if(MaskMsg->u8Xtd)
    CANx->IF0.MASK1 |= CAN_IF_MASK1_MXTD_Msk;            /* The extended identifier bit (IDE) is used for acceptance filtering */
  else
    CANx->IF0.MASK1 &= (~CAN_IF_MASK1_MXTD_Msk);  /* The extended identifier bit (IDE) has no effect on the acceptance filtering */

  if(MaskMsg->u8Dir)
    CANx->IF0.MASK1 |= CAN_IF_MASK1_MDIR_Msk;     /* The message direction bit (Dir) is used for acceptance filtering */
  else
    CANx->IF0.MASK1 &= (~CAN_IF_MASK1_MDIR_Msk);  /* The message direction bit (Dir) has no effect on the acceptance filtering */

  CANx->IF0.MCR |= CAN_IF_MCR_UMASK_Msk;                 /* Use Mask (Msk28-0, MXtd, and MDir) for acceptance filtering */

  /* Update the contents needed for transmission*/
  CANx->IF0.CMASK = CAN_IF_CMASK_WRRD_Msk      /* Transfer data from the selected Message Buffer Registers to the Message Object addressed */
                  | CAN_IF_CMASK_MASK_Msk;     /* Transfer Identifier Mask + MDir + MXtd to Message Object  */

  CANx->IF0.DA0R  = 0;
  CANx->IF0.DA1R  = 0;
  CANx->IF0.DB0R  = 0;
  CANx->IF0.DB1R  = 0;

  /* Set the Message Object in the Message RAM is selected for data transfer */
  CANx->IF0.CREQ  = 1 + MsgObj;

  return TRUE;
}

/* Private functions ----------------------------------------------------------------------------------------*/
/** @defgroup CAN_Private_Functions CAN private functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief  Check if SmartCard slot is presented.
 * @param  CANx: The pointer to CAN module base address.
* @retval Free IF number. IF0_NUM or IF1_NUM or IF_TOTAL_NUM (No IF is free)
  ***********************************************************************************************************/
static CANIF_NUMBER_Enum GetFreeIF(HT_CAN_TypeDef  *CANx)
{
  if((CANx->IF0.CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
      return IF0_NUM;
  else if((CANx->IF1.CREQ  & CAN_IF_CREQ_BUSY_Msk) == 0)
      return IF1_NUM;
  else
      return IF_TOTAL_NUM;
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

/**
  * @}
  */
