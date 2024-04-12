/********************************************************************************************************//**
 * @file    ht32f5xxxx_ebi.c
 * @version $Rev:: 2772         $
 * @date    $Date:: 2018-05-15 #$
 * @brief   This file provides all the EBI firmware functions.
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
#include "ht32f5xxxx_ebi.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup EBI EBI
  * @brief EBI driver modules
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup EBI_Exported_Functions EBI exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitializes the EBI peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void EBI_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.EBI = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initializes the EBI peripheral according to the specified parameters in the EBI_InitStruct.
 * @param EBI_InitStruct: pointer to a EBI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void EBI_Init(EBI_InitTypeDef* EBI_InitStruct)
{
  u32 tmp;
  u32 bank = EBI_InitStruct->EBI_Bank;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_EBI_BANK(EBI_InitStruct->EBI_Bank));
  Assert_Param(IS_EBI_MODE(EBI_InitStruct->EBI_Mode));
  Assert_Param(IS_EBI_IDLECYCLE(EBI_InitStruct->EBI_IdleCycle));
  Assert_Param(IS_EBI_CS_POLARITY(EBI_InitStruct->EBI_ChipSelectPolarity));
  Assert_Param(IS_EBI_ALE_POLARITY(EBI_InitStruct->EBI_AddressLatchPolarity));
  Assert_Param(IS_EBI_WE_POLARITY(EBI_InitStruct->EBI_WriteEnablePolarity));
  Assert_Param(IS_EBI_RE_POLARITY(EBI_InitStruct->EBI_ReadEnablePolarity));
  Assert_Param(IS_EBI_IDLE_CYCLE_TIME(EBI_InitStruct->EBI_IdleCycleTime));
  Assert_Param(IS_EBI_ADDRESS_SETUP_TIME(EBI_InitStruct->EBI_AddressSetupTime));
  Assert_Param(IS_EBI_ADDRESS_HOLD_TIME(EBI_InitStruct->EBI_AddressHoldTime));
  Assert_Param(IS_EBI_WRITE_SETUP_TIME(EBI_InitStruct->EBI_WriteSetupTime));
  Assert_Param(IS_EBI_WRITE_STROBE_TIME(EBI_InitStruct->EBI_WriteStrobeTime));
  Assert_Param(IS_EBI_WRITE_HOLD_TIME(EBI_InitStruct->EBI_WriteHoldTime));
  Assert_Param(IS_EBI_READ_SETUP_TIME(EBI_InitStruct->EBI_ReadSetupTime));
  Assert_Param(IS_EBI_READ_STROBE_TIME(EBI_InitStruct->EBI_ReadStrobeTime));

  HT_EBI->ATR = EBI_InitStruct->EBI_AddressSetupTime |
                (EBI_InitStruct->EBI_AddressHoldTime << 8);
  HT_EBI->RTR = EBI_InitStruct->EBI_ReadSetupTime |
                (EBI_InitStruct->EBI_ReadStrobeTime << 8) |
                (EBI_InitStruct->EBI_ReadHoldTime << 16);

  HT_EBI->WTR = EBI_InitStruct->EBI_WriteSetupTime |
                (EBI_InitStruct->EBI_WriteStrobeTime << 8) |
                (EBI_InitStruct->EBI_WriteHoldTime << 16);
  HT_EBI->PR = EBI_InitStruct->EBI_ChipSelectPolarity |
               (EBI_InitStruct->EBI_ReadEnablePolarity << 1) |
               (EBI_InitStruct->EBI_WriteEnablePolarity << 2) |
               (EBI_InitStruct->EBI_AddressLatchPolarity << 3);


  /*------------------------- EBI Control Register Configuration -------------------------------------------*/
  tmp = (3 << (bank * 2)) | (0x00001000 << bank) |
        (0x00010000 << (bank * 2)) | (0x00020000 << (bank * 2)) |
        (0x01000000 << bank);
  tmp = HT_EBI->CR & (~tmp);
  HT_EBI->CR = (EBI_InitStruct->EBI_Mode << (bank * 2)) |
               (EBI_InitStruct->EBI_IdleCycle << bank) |
               (EBI_InitStruct->EBI_IdleCycleTime << 28) | tmp;
}

/*********************************************************************************************************//**
 * @brief  Fills each EBI_InitStruct member with its default value.
 * @param  EBI_InitStruct: pointer to an EBI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void EBI_StructInit(EBI_InitTypeDef* EBI_InitStruct)
{
  /* Initialize the EBI structure parameters values                                                         */
  EBI_InitStruct->EBI_Bank = EBI_BANK_0;
  EBI_InitStruct->EBI_Mode = EBI_MODE_D8A8;
  EBI_InitStruct->EBI_IdleCycle = EBI_IDLECYCLE_DISABLE;
  EBI_InitStruct->EBI_ChipSelectPolarity = EBI_CHIPSELECTPOLARITY_LOW;
  EBI_InitStruct->EBI_AddressLatchPolarity = EBI_ADDRESSLATCHPOLARITY_LOW;
  EBI_InitStruct->EBI_WriteEnablePolarity = EBI_WRITEENABLEPOLARITY_LOW;
  EBI_InitStruct->EBI_ReadEnablePolarity = EBI_READENABLEPOLARITY_LOW;
  EBI_InitStruct->EBI_IdleCycleTime = 0xF;
  EBI_InitStruct->EBI_AddressSetupTime = 0xF;
  EBI_InitStruct->EBI_AddressHoldTime = 0xF;
  EBI_InitStruct->EBI_WriteSetupTime = 0xF;
  EBI_InitStruct->EBI_WriteStrobeTime = 0x3F;
  EBI_InitStruct->EBI_WriteHoldTime = 0xF;
  EBI_InitStruct->EBI_ReadSetupTime = 0xF;
  EBI_InitStruct->EBI_ReadStrobeTime = 0x3F;
  EBI_InitStruct->EBI_ReadHoldTime = 0xF;
}

/*********************************************************************************************************//**
 * @brief  Enable or Disable the EBI peripheral.
 * @param  EBI_Bank: EBI Bank.
 *   This parameter can be one of the following values:
 *     @arg EBI_BANK_0 : EBI Bank 0
 *     @arg EBI_BANK_1 : EBI Bank 1
 *     @arg EBI_BANK_2 : EBI Bank 2
 *     @arg EBI_BANK_3 : EBI Bank 3
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void EBI_Cmd(u32 EBI_Bank, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EBI_BANK(EBI_Bank));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_EBI->CR |= (0x100 << EBI_Bank);
  }
  else
  {
    HT_EBI->CR &= ~(0x100 << EBI_Bank);
  }
}

/*********************************************************************************************************//**
 * @brief  Check whether the specified EBI busy flag has been set.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus EBI_GetBusyStatus(void)
{
  if (HT_EBI->SR & 0x1)
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
