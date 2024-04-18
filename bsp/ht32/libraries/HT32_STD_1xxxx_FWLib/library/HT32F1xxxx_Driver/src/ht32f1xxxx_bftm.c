/*********************************************************************************************************//**
 * @file    ht32f1xxxx_bftm.c
 * @version $Rev:: 2789         $
 * @date    $Date:: 2022-11-24 #$
 * @brief   This file provides all the BFTM firmware functions.
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
#include "ht32f1xxxx_bftm.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup BFTM BFTM
  * @brief BFTM driver modules
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup BFTM_Exported_Functions BFTM exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the specified BFTM registers to their default values.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @retval None
 ************************************************************************************************************/
void BFTM_DeInit(HT_BFTM_TypeDef* HT_BFTMn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  if (HT_BFTMn == HT_BFTM0)
  {
    RSTCUReset.Bit.BFTM0 = 1;
  }
  else if (HT_BFTMn == HT_BFTM1)
  {
    RSTCUReset.Bit.BFTM1 = 1;
  }
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void BFTM_EnaCmd(HT_BFTM_TypeDef* HT_BFTMn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_BFTMn->CR |= (1UL << 2);
  }
  else
  {
    HT_BFTMn->CR &= ~(1UL << 2);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the CMP register value of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @param uCompare: Specify a value to the CMP register.
 * @retval None
 ************************************************************************************************************/
void BFTM_SetCompare(HT_BFTM_TypeDef* HT_BFTMn, BFTM_DataTypeDef uCompare)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  HT_BFTMn->CMP = uCompare;
}

/*********************************************************************************************************//**
 * @brief Get the CMP register value of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @retval The value of the CMP register
 ************************************************************************************************************/
u32 BFTM_GetCompare(HT_BFTM_TypeDef* HT_BFTMn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  return HT_BFTMn->CMP;
}

/*********************************************************************************************************//**
 * @brief Set the CNTR register value of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @param uCounter: Specify a new value to the CNTR register.
 * @retval None
 ************************************************************************************************************/
void BFTM_SetCounter(HT_BFTM_TypeDef* HT_BFTMn, BFTM_DataTypeDef uCounter)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  HT_BFTMn->CNTR = uCounter;
}

/*********************************************************************************************************//**
 * @brief Get the CNTR register value of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @retval The value of the CNTR register
 ************************************************************************************************************/
u32 BFTM_GetCounter(HT_BFTM_TypeDef* HT_BFTMn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  return HT_BFTMn->CNTR;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the one shot mode of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void BFTM_OneShotModeCmd(HT_BFTM_TypeDef* HT_BFTMn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_BFTMn->CR |= (1UL << 1);
  }
  else
  {
    HT_BFTMn->CR &= ~(1UL << 1);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified BFTM interrupt.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void BFTM_IntConfig(HT_BFTM_TypeDef* HT_BFTMn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_BFTMn->CR |= BFTM_INT_MATCH;
  }
  else
  {
    HT_BFTMn->CR &= ~BFTM_INT_MATCH;
  }
}

/*********************************************************************************************************//**
 * @brief Get the flag status of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus BFTM_GetFlagStatus(HT_BFTM_TypeDef* HT_BFTMn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  if (HT_BFTMn->SR & BFTM_FLAG_MATCH)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the interrupt flag of the specified BFTM.
 * @param HT_BFTMn: where the HT_BFTMn is the selected BFTM from the BFTM peripherals.
 * @retval None
 ************************************************************************************************************/
void BFTM_ClearFlag(HT_BFTM_TypeDef* HT_BFTMn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_BFTM(HT_BFTMn));

  HT_BFTMn->SR &= ~BFTM_FLAG_MATCH;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-Mx when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
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
