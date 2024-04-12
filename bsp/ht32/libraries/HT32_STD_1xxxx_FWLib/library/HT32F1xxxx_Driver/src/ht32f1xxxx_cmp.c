/*********************************************************************************************************//**
 * @file    ht32f1xxxx_cmp.c
 * @version $Rev:: 2794         $
 * @date    $Date:: 2022-11-25 #$
 * @brief   This file provides all the CMP firmware functions.
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
#include "ht32f1xxxx_cmp.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup CMP CMP
  * @brief CMP driver modules
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup CMP_Exported_Functions CMP exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the CMP0 and CMP1 peripheral registers to their default reset values.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @retval None
 ************************************************************************************************************/
void CMP_DeInit(HT_CMP_TypeDef* HT_CMPn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  if (HT_CMPn == NULL) // Remove the compiler warning
  {
  }

  RSTCUReset.Bit.CMP = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Unprotect the selected comparator configuration before setting the Comparator Control Register.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @retval None
 ************************************************************************************************************/
void CMP_UnprotectConfig(HT_CMP_TypeDef* HT_CMPn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));

  /* Set the unlock code corresponding to selected comparator                                               */
  HT_CMPn->CR = CMP_PROTECT_KEY;
}

/*********************************************************************************************************//**
 * @brief Initialize the CMP peripheral according to the specified parameters in the CMP_InitStruct.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param CMP_InitStruct: pointer to a CMP_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void CMP_Init(HT_CMP_TypeDef* HT_CMPn, CMP_InitTypeDef* CMP_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_CMP_Wakeup_Set(CMP_InitStruct->CMP_Wakeup));
  Assert_Param(IS_CMP_OutputSelection(CMP_InitStruct->CMP_OutputSelection));
  Assert_Param(IS_CMP_ScalerSource(CMP_InitStruct->CMP_ScalerSource));
  Assert_Param(IS_CMP_ScalerOutputBuf(CMP_InitStruct->CMP_ScalerOutputBuf));
  Assert_Param(IS_CMP_ScalerEnable(CMP_InitStruct->CMP_ScalerEnable));
  Assert_Param(IS_CMP_CoutSynchronized(CMP_InitStruct->CMP_CoutSync));
  Assert_Param(IS_CMP_OutputPol_Set(CMP_InitStruct->CMP_OutputPol));
  Assert_Param(IS_CMP_InvInputSelection(CMP_InitStruct->CMP_InvInputSelection));
  Assert_Param(IS_CMP_Hysteresis_Set(CMP_InitStruct->CMP_Hysteresis));
  Assert_Param(IS_CMP_Speed_Set(CMP_InitStruct->CMP_Speed));

  HT_CMPn->CR |= CMP_InitStruct->CMP_Wakeup | CMP_InitStruct->CMP_OutputSelection | CMP_InitStruct->CMP_ScalerSource | \
                 CMP_InitStruct->CMP_ScalerOutputBuf | CMP_InitStruct->CMP_ScalerEnable | CMP_InitStruct->CMP_CoutSync | \
                 CMP_InitStruct->CMP_OutputPol | CMP_InitStruct->CMP_InvInputSelection | CMP_InitStruct->CMP_Hysteresis | \
                 CMP_InitStruct->CMP_Speed;
}

/*********************************************************************************************************//**
 * @brief Fill each CMP_InitStruct member with its default value.
 * @param CMP_InitStruct: pointer to an CMP_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void CMP_StructInit(CMP_InitTypeDef* CMP_InitStruct)
{
  /* CMP_InitStruct members default value                                                                   */
  CMP_InitStruct->CMP_Wakeup = CMP_WUP_DISABLE;
  CMP_InitStruct->CMP_OutputSelection = CMP_TRIG_NONE;
  CMP_InitStruct->CMP_ScalerSource = CMP_SCALER_SRC_VDDA;
  CMP_InitStruct->CMP_ScalerOutputBuf = CMP_SCALER_OBUF_DISABLE;
  CMP_InitStruct->CMP_ScalerEnable = CMP_SCALER_DISABLE;
  CMP_InitStruct->CMP_CoutSync = CMP_ASYNC_OUTPUT;
  CMP_InitStruct->CMP_OutputPol = CMP_NONINV_OUTPUT;
  CMP_InitStruct->CMP_InvInputSelection = CMP_EXTERNAL_CN_IN;
  CMP_InitStruct->CMP_Hysteresis = CMP_NO_HYSTERESIS;
  CMP_InitStruct->CMP_Speed = CMP_LOW_SPEED;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CMP peripheral.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CMP_Cmd(HT_CMP_TypeDef* HT_CMPn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_CMPn->CR |= CMP_ENABLE;
  }
  else
  {
    HT_CMPn->CR &= ~(u32)CMP_ENABLE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CMP interrupts.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param CMP_INT_x: specify the CMP interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg CMP_INT_RE : CMP rising edge interrupt
 *     @arg CMP_INT_FE : CMP falling edge interrupt
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CMP_IntConfig(HT_CMP_TypeDef* HT_CMPn, u32 CMP_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_CMP_INT(CMP_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_CMPn->IER |= CMP_INT_x;
  }
  else
  {
    HT_CMPn->IER &= ~CMP_INT_x;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CMP edge detection.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param CMP_xE_Detect: specify the CMP edge detection that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg CMP_RE_Detect : CMP rising edge detection
 *     @arg CMP_FE_Detect : CMP falling edge detection
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CMP_EdgeDetectConfig(HT_CMP_TypeDef* HT_CMPn, u32 CMP_xE_Detect, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_CMP_EdgeDetect(CMP_xE_Detect));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_CMPn->TFR = (HT_CMPn->TFR | CMP_xE_Detect) & 0xfffffffc;
  }
  else
  {
    HT_CMPn->TFR = (HT_CMPn->TFR & (~CMP_xE_Detect)) & 0xfffffffc;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified CM flag has been set.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param CMP_FLAG_x: specify the flag to be checked.
 *   This parameter can be any combination of the following values:
 *     @arg CMP_FLAG_RE : CMP rising edge flag
 *     @arg CMP_FLAG_FE : CMP falling edge flag
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus CMP_GetFlagStatus(HT_CMP_TypeDef* HT_CMPn, u32 CMP_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_CMP_FLAG(CMP_FLAG_x));

  if ((HT_CMPn->TFR & CMP_FLAG_x) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear flags of the specified CMP.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param CMP_FLAG_x: specify the flag to be checked.
 *   This parameter can be any combination of the following values:
 *     @arg CMP_FLAG_RE : CMP rising edge flag
 *     @arg CMP_FLAG_FE : CMP falling edge flag
 * @retval None
 ************************************************************************************************************/
void CMP_ClearFlag(HT_CMP_TypeDef* HT_CMPn, u32 CMP_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_CMP_FLAG(CMP_FLAG_x));

  /* Clear the flags                                                                                        */
  HT_CMPn->TFR = (HT_CMPn->TFR & 0xfffffffc) | CMP_FLAG_x;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-Mx when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
}

/*********************************************************************************************************//**
 * @brief Get the output status of the specified CMP.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus CMP_GetOutputStatus(HT_CMP_TypeDef* HT_CMPn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));

  if ((HT_CMPn-> CR & CMP_OUTPUT_HIGH) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Set the specified reference value in the data register of the scaler.
 * @param HT_CMPn: where HT_CMPn is the selected CMP from the CMP peripherals.
 * @param Scaler_Value: value to be loaded in the selected data register
 * @retval None
 ************************************************************************************************************/
void CMP_SetScalerValue(HT_CMP_TypeDef* HT_CMPn, u8 Scaler_Value)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP(HT_CMPn));
  Assert_Param(IS_SCALER_VALUE(Scaler_Value));

  /* Set the scaler reference value register                                                                */
  HT_CMPn->VALR = (u32)Scaler_Value;
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
