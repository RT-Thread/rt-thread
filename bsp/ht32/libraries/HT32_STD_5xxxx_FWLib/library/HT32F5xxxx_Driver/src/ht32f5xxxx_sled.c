/*********************************************************************************************************//**
 * @file    ht32f5xxxx_sled.c
 * @version $Rev:: 3309         $
 * @date    $Date:: 2018-12-12 #$
 * @brief   This file provides all the SLED firmware functions.
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
#include "ht32f5xxxx_sled.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup SLED SLED
  * @brief SLED driver modules
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup SLED_Exported_Functions SLED exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the specified SLED peripheral registers to their default reset values.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval None
 ************************************************************************************************************/
void SLED_DeInit(HT_SLED_TypeDef* SLEDx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));

  if (SLEDx == HT_SLED0)
  {
    RSTCUReset.Bit.SLED0 = 1;
  }
  #if(LIBCFG_SLED1)
  else if (SLEDx == HT_SLED1)
  {
    RSTCUReset.Bit.SLED1 = 1;
  }
  #endif

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the specified SLED peripheral according to the specified parameters in the SLED_InitStruct.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @param SLED_InitStruct: pointer to a SLED_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SLED_Init(HT_SLED_TypeDef* SLEDx, SLED_InitTypeDef* SLED_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));

  SLEDx->CDR = (SLED_InitStruct->BaudRate       <<  8)
             | (SLED_InitStruct->ClockPrescaler <<  0);

  SLEDx->TCR = (SLED_InitStruct->TRST           << 16)
             | (SLED_InitStruct->T1H            <<  8)
             | (SLED_InitStruct->T0H            <<  0);

  SLEDx->CR = (SLED_InitStruct->SyncState       << 10)
            | (SLED_InitStruct->IdleState       <<  9)
            | (SLED_InitStruct->ResetState      <<  8)
            | (SLED_InitStruct->SyncMode        <<  3)
            | (SLED_InitStruct->OutputPolarity  <<  2);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SLED peripheral.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SLED_Cmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SLEDx->CR |= (1 << 0);
  }
  else
  {
    SLEDx->CR &= ~(1 << 0);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SLED output.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SLED_OutputCmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SLEDx->CR |= (1 << 1);
  }
  else
  {
    SLEDx->CR &= ~(1 << 1);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SLED PDMA request.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SLED_PDMACmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SLEDx->CR |= (1 << 4);
  }
  else
  {
    SLEDx->CR &= ~(1 << 4);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SLED interrupt.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SLED_IntCmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SLEDx->CR |= (1 << 5);
  }
  else
  {
    SLEDx->CR &= ~(1 << 5);
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified SLED interrupt flag.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval None
 ************************************************************************************************************/
void SLED_ClearIntFlag(HT_SLED_TypeDef* SLEDx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));

  SLEDx->SR |= (1 << 5);
}

/*********************************************************************************************************//**
 * @brief Insert a Reset Code on the specified SLED.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval None
 ************************************************************************************************************/
void SLED_InsertResetCode(HT_SLED_TypeDef* SLEDx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));

  SLEDx->CR |= (1 << 15);
}

/*********************************************************************************************************//**
 * @brief Return the FIFO status of the specified SLED.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus SLED_GetResetCodeStatus(HT_SLED_TypeDef* SLEDx)
{
  if ((SLEDx->CR & (1 << 15)) != RESET)
    return SET;
  else
    return RESET;
}

/*********************************************************************************************************//**
 * @brief Return the BUSY status of the specified SLED.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus SLED_GetBusyStatus(HT_SLED_TypeDef* SLEDx)
{
  if (SLEDx->SR & 1)
    return SET;
  else
    return RESET;
}

/*********************************************************************************************************//**
 * @brief Set the specified SLED FIFO trigger level.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @param FifoLevel: specify the FIFO trigger level.
 *   This parameter can be one of the following values:
 *     @arg SLED_FIFO_LEVEL_0 : data request will be inserted when FIFO data count is equal to 0
 *     @arg SLED_FIFO_LEVEL_1 : data request will be inserted when FIFO data count is less than or equal to 1
 *     @arg SLED_FIFO_LEVEL_2 : data request will be inserted when FIFO data count is less than or equal to 2
 *     @arg SLED_FIFO_LEVEL_3 : data request will be inserted when FIFO data count is less than or equal to 3
 * @retval None
 ************************************************************************************************************/
void SLED_FIFOTrigLevelConfig(HT_SLED_TypeDef* SLEDx, u8 FifoLevel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));
  Assert_Param(IS_SLED_FIFO_LEVEL(FifoLevel));

  SLEDx->FCR = FifoLevel;
}

/*********************************************************************************************************//**
 * @brief Return the FIFO status of the specified SLED.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval The number of data in FIFO.
 ************************************************************************************************************/
u8 SLED_GetFIFOStatus(HT_SLED_TypeDef* SLEDx)
{
  return (SLEDx->FCR >> 24);
}

/*********************************************************************************************************//**
 * @brief Reset the specified SLED FIFO.
 * @param SLEDx: where SLEDx is the selected SLED from the SLED peripherals.
 * @retval None
 ************************************************************************************************************/
void SLED_FIFOReset(HT_SLED_TypeDef* SLEDx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SLED(SLEDx));

  SLEDx->FCR |= (1 << 0);
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
