/*********************************************************************************************************//**
 * @file    ht32f66xxx_pid.c
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   This file provides all the PID firmware functions.
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
#include "ht32f66xxx_pid.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup PID PID
  * @brief PID driver modules
  * @{
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @addtogroup PID_Exported_Functions PID exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the HT_PIDn peripheral registers to their default reset values.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @retval None
 ************************************************************************************************************/
void PID_DeInit(HT_PID_TypeDef* HT_PIDn)
{
   RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));

  if (HT_PIDn == HT_PID0)
  {
    RSTCUReset.Bit.PID0 = 1;
  }

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the HT_PIDn PID_Mode peripheral according to the specified parameters in the PID_InitTypeDef.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_Mode: where PID_Mode is the selected PID mode.
 *   This parameter can be one of the following values:
 *     @arg PID_SPD_MODE
 *     @arg PID_IQ_MODE
 *     @arg PID_ID_MODE
 *     @arg PID_FWNK_MODE
 *     @arg PID_PLL_MODE
 *     @arg PID_USR_MODE
 * @param PID_Para: where PID_Para is PID paramater structure.
 * @retval None
 ************************************************************************************************************/
void PID_Init(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode, PID_InitTypeDef* PID_Para)
{
  HT_PIDPARA_TypeDef * gPID_ModePara = &(HT_PIDn->SPD);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_MODE(PID_Mode));

  (gPID_ModePara + PID_Mode)->KPIR     = PID_Para->KP;
  (gPID_ModePara + PID_Mode)->KIIR     = PID_Para->KI;
  (gPID_ModePara + PID_Mode)->KDIR     = PID_Para->KD;
  (gPID_ModePara + PID_Mode)->IFVMAXLR = PID_Para->UI_MAX;
  (gPID_ModePara + PID_Mode)->IFVMINLR = PID_Para->UI_MIN;
  (gPID_ModePara + PID_Mode)->PIDORLR  = (u32)((PID_Para->OUT_MAX << 16) | ((u16)PID_Para->OUT_MIN));
  (gPID_ModePara + PID_Mode)->LEIR     = PID_Para->ERRn_1;
  (gPID_ModePara + PID_Mode)->LIFVR    = PID_Para->UIn_1;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PID interrupts.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_INT_x: Specify the PID interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg PID_INT_CMP :
 *     @arg PID_INT_OVF :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PID_IntConfig(HT_PID_TypeDef* HT_PIDn, u32 PID_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_INT(PID_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_PIDn->CR |= PID_INT_x;
  }
  else
  {
    HT_PIDn->CR &= ~PID_INT_x;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified PID interrupt has occurred.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_INT_x: Specify the PID interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg PID_INT_CMP :
 *     @arg PID_INT_OVF :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PID_GetIntStatus(HT_PID_TypeDef* HT_PIDn, u32 PID_INT_x)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_INT(PID_INT_x));

  if ((HT_PIDn->CR & (PID_INT_x << PID_INT_Status_Pos)) != RESET)
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
 * @brief Clear the PID interrupt pending bits.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_INT_x: Specify the PID interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg PID_INT_CMP :
 *     @arg PID_INT_OVF :
 * @retval None
 ************************************************************************************************************/
void PID_ClearIntPendingBit(HT_PID_TypeDef* HT_PIDn, u32 PID_INT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_INT(PID_INT_x));

  HT_PIDn->CR |= (PID_INT_x << PID_INT_Clear_Pos);
}

/*********************************************************************************************************//**
 * @brief Set the PID ERR(n) value of the common parameters.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param ERRn: where ERRn is PID Controller Error Input Value.
 * @retval None
 ************************************************************************************************************/
void PID_SetComPara_ERRn(HT_PID_TypeDef* HT_PIDn, s32 ERRn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));

  HT_PIDn->EIVR  = ERRn;
}

/*********************************************************************************************************//**
 * @brief Set the PID UI_input(n) value of the common parameters.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param UI_Input: where UI_Input is PID Controller integrator accumulation selection.
 * @retval None
 ************************************************************************************************************/
void PID_SetComPara_UI_Input(HT_PID_TypeDef* HT_PIDn, s32 UI_Input)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));

  HT_PIDn->IFIVR = UI_Input;
}

/*********************************************************************************************************//**
 * @brief Enable compute the PID calculation.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_Mode: where PID_Mode is the selected PID mode.
 *   This parameter can be one of the following values:
 *     @arg PID_SPD_MODE
 *     @arg PID_IQ_MODE
 *     @arg PID_ID_MODE
 *     @arg PID_FWNK_MODE
 *     @arg PID_PLL_MODE
 *     @arg PID_USR_MODE
 * @retval None
 ************************************************************************************************************/
void PID_Compute(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_MODE(PID_Mode));

  HT_PIDn->CR &= ~(u32)PID_CR_MODSEL_Msk;
  HT_PIDn->CR |= (PID_Mode << PID_CR_MODSEL_Pos) | (PID_CR_PIDEN);
}

/*********************************************************************************************************//**
 * @brief Return the PID ouput result value.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @retval The Value of PID result.
 ************************************************************************************************************/
s16  PID_GetOutResult(HT_PID_TypeDef* HT_PIDn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));

  return HT_PIDn->ORR;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified PID flag has been set.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_FLAG_x: Specify the flag to check.
 *   This parameter can be any combination of the following values:
 *     @arg PID_FLAG_CMP :
 *     @arg PID_FLAG_OVF :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PID_GetFlagStatus(HT_PID_TypeDef* HT_PIDn, u32 PID_FLAG_x)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_FLAG(PID_FLAG_x));

  if ((HT_PIDn->CR & PID_FLAG_x) != RESET)
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
 * @brief Enable or Disable the integrator accumulation value set by UI_input(n).
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PID_UI_InputCmd(HT_PID_TypeDef* HT_PIDn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_PIDn->CR |= PID_CR_UIF;
  }
  else
  {
    HT_PIDn->CR &= ~(u32)PID_CR_UIF;
  }
}

/*********************************************************************************************************//**
 * @brief Return the PID last error input value (ERRn_1) for the selected PID mode.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_Mode: where PID_Mode is the selected PID mode.
 *   This parameter can be one of the following values:
 *     @arg PID_SPD_MODE
 *     @arg PID_IQ_MODE
 *     @arg PID_ID_MODE
 *     @arg PID_FWNK_MODE
 *     @arg PID_PLL_MODE
 *     @arg PID_USR_MODE
 * @retval The Value of ERRn_1 for the selected PID mode.
 ************************************************************************************************************/
s32  PID_GetERRn_1(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode)
{
  HT_PIDPARA_TypeDef * gPID_ModePara = &(HT_PIDn->SPD);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_MODE(PID_Mode));

  return (gPID_ModePara + PID_Mode)->LEIR;
}

/*********************************************************************************************************//**
 * @brief Return the PID last integral function value (UIn_1) for the selected PID mode.
 * @param HT_PIDn: where HT_PIDn is the selected PID from the PID peripherals.
 * @param PID_Mode: where PID_Mode is the selected PID mode.
 *   This parameter can be one of the following values:
 *     @arg PID_SPD_MODE
 *     @arg PID_IQ_MODE
 *     @arg PID_ID_MODE
 *     @arg PID_FWNK_MODE
 *     @arg PID_PLL_MODE
 *     @arg PID_USR_MODE
 * @retval The Value of UIn_1 for the selected PID mode.
 ************************************************************************************************************/
s32  PID_GetUIn_1(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode)
{
  HT_PIDPARA_TypeDef * gPID_ModePara = &(HT_PIDn->SPD);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PID(HT_PIDn));
  Assert_Param(IS_PID_MODE(PID_Mode));
  return   (gPID_ModePara + PID_Mode)->LIFVR;
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
