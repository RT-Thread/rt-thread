/*********************************************************************************************************//**
 * @file    ht32f1xxxx_cmp_op.c
 * @version $Rev:: 129          $
 * @date    $Date:: 2017-06-14 #$
 * @brief   This file provides all the CMP_OP firmware functions.
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
#include "ht32f1xxxx_cmp_op.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup  CMP_OP CMP_OP
  * @brief CMP_OP driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup CMP_OP_Private_Define CMP_OP private definitions
  * @{
  */
#define CMP_OP_ENABLE                 (0x00000001ul)
#define CMP_OP_CANCELLATION_MODE      (0x00000004ul)
/**
  * @}
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup CMP_OP_Exported_Functions CMP_OP exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the CMP_OP peripheral registers to their default reset values.
 * @param CMP_OPx: where x can be 0 or 1 to select the CMP_OP peripheral.
 * @retval None
 ************************************************************************************************************/
void CMP_OP_DeInit(HT_CMP_OP_TypeDef* CMP_OPx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));

  if (CMP_OPx == HT_CMP_OP0)
  {
    RSTCUReset.Bit.OPA0 = 1;
  }
  else
  {
    RSTCUReset.Bit.OPA1 = 1;
  }

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure the CMP_OP peripheral as OPA or CMP mode and fill the cancellation value.
 * @param CMP_OPx: where CMP_OP is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param mode: Specify the CMP_OPx peripheral mode
 *   This parameter can be any combination of the following values:
 *     @arg OP_MODE     : Operational Amplifier mode
 *     @arg CMP_MODE    : Comparator Mode Selection
 * @param cancellation: Specify the input offset voltage cancellation value.
 * @retval None
************************************************************************************************************/
void CMP_OP_Config(HT_CMP_OP_TypeDef* CMP_OPx, u32 mode, u32 cancellation)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_MODE(mode));
  Assert_Param(IS_CMP_OP_IOVC(cancellation));

  CMP_OPx->OPACR = (CMP_OPx->OPACR & CMP_OP_ENABLE) | mode;
  CMP_OPx->OFVCR = cancellation;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CMP_OP peripheral.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param  NewState: new state of the CMP_OPx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void CMP_OP_Cmd(HT_CMP_OP_TypeDef* CMP_OPx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CMP_OPx peripheral                                                               */
    CMP_OPx->OPACR |= CMP_OP_ENABLE;
  }
  else
  {
    /* Disable the selected CMP_OPx peripheral                                                              */
    CMP_OPx->OPACR &= ~(u32)CMP_OP_ENABLE;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the CMP_OP peripheral as cancellation mode and select the source of reference input.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_REF_INPUT: Specify the the source of reference input.
 *   This parameter can be any combination of the following values:
 *     @arg CMP_OP_NEGATIVE_INPUT
 *     @arg CMP_OP_POSITIVE_INPUT
 * @retval None
************************************************************************************************************/
void CMP_OP_CancellationModeConfig(HT_CMP_OP_TypeDef* CMP_OPx, u16 CMP_OP_REF_INPUT)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_REF(CMP_OP_REF_INPUT));

  CMP_OPx->OPACR = (CMP_OPx->OPACR & CMP_OP_ENABLE) | CMP_OP_CANCELLATION_MODE | CMP_OP_REF_INPUT;
}

/*********************************************************************************************************//**
 * @brief Set input offset voltage cancellation value.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param cancellation: Specify the input offset voltage cancellation value.
 * @retval None
************************************************************************************************************/
void CMP_OP_SetCancellationVaule(HT_CMP_OP_TypeDef* CMP_OPx, u32 cancellation)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_IOVC(cancellation));

  CMP_OPx->OFVCR = cancellation;
}

/*********************************************************************************************************//**
 * @brief Get input offset voltage cancellation value.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @retval The input offset voltage cancellation value.
************************************************************************************************************/
u32 CMP_OP_GetCancellationVaule(HT_CMP_OP_TypeDef* CMP_OPx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));

  return CMP_OPx->OFVCR;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CMP_OP interrupts.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_INT: Specify the CMP_OP interrupt sources that is to be enabled or disabled.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_INT_FALLING:
 *        - CMP_OP_INT_RISING:
 * @param NewState new state of the specified ADC interrupts.
 *        This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void CMP_OP_IntConfig(HT_CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_INT(CMP_OP_INT));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    CMP_OPx->CMPIER |= CMP_OP_INT;
  }
  else
  {
    CMP_OPx->CMPIER &= ~CMP_OP_INT;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC interrupt has occurred.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_INT: Specify the interrupt status to check.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_INT_FALLING:
 *        - CMP_OP_INT_RISING:
 * @retval SET or RESET
************************************************************************************************************/
FlagStatus CMP_OP_GetIntStatus(HT_CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_INT(CMP_OP_INT));

  if ((CMP_OPx->CMPISR & CMP_OP_INT) != 0x0)
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
 * @brief Check whether the specified CMP_OP flag has been set.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_FLAG: Specify the flag to check.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_FLAG_FALLING:
 *        - CMP_OP_FLAG_RISING:
 * @retval SET or RESET
************************************************************************************************************/
FlagStatus CMP_OP_GetFlagStatus(HT_CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_FLAG)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_FLAG(CMP_OP_FLAG));

  if ((CMP_OPx->CMPRSR & CMP_OP_FLAG) != 0x0)
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
 * @brief Clear the CMP_OPx interrupt pending bits.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_INT: specifies the interrupt pending bits to be cleared.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_INT_FALLING:
 *        - CMP_OP_INT_RISING:
 * @retval None
************************************************************************************************************/
void CMP_OP_ClearIntPendingBit(HT_CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_INT(CMP_OP_INT));

  CMP_OPx->CMPICLR = CMP_OP_INT;
}

/*********************************************************************************************************//**
 * @brief Get the output status of CMP_OPx.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @retval SET or RESET
************************************************************************************************************/
FlagStatus CMP_OP_GetOutputStatus(HT_CMP_OP_TypeDef* CMP_OPx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));

  if ((CMP_OPx->OPACR & 0x00000100) != 0x0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
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
