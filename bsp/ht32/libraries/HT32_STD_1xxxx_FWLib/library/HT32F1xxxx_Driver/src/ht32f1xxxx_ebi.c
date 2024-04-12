/********************************************************************************************************//**
 * @file    ht32f1xxxx_ebi.c
 * @version $Rev:: 2788         $
 * @date    $Date:: 2022-11-24 #$
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
#include "ht32f1xxxx_ebi.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
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
  u32 offset = EBI_InitStruct->EBI_Bank * 0x10;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_EBI_BANK(EBI_InitStruct->EBI_Bank));
  Assert_Param(IS_EBI_MODE(EBI_InitStruct->EBI_Mode));
  #if (LIBCFG_EBI_BYTELAND_ASYNCREADY)
  Assert_Param(IS_EBI_BYTELANE(EBI_InitStruct->EBI_ByteLane));
  Assert_Param(IS_EBI_ARDY(EBI_InitStruct->EBI_AsynchronousReady));
  Assert_Param(IS_EBI_ARDY_TIMEOUT(EBI_InitStruct->EBI_ARDYTimeOut));
  Assert_Param(IS_EBI_BL_POLARITY(EBI_InitStruct->EBI_ByteLanePolarity));
  Assert_Param(IS_EBI_ARDY_POLARITY(EBI_InitStruct->EBI_ReadySignalPolarity));
  #endif
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
  #if !(LIBCFG_EBI_V01)
  Assert_Param(IS_EBI_PAGE_MODE(EBI_InitStruct->EBI_PageMode));
  Assert_Param(IS_EBI_PAGE_LENGTH(EBI_InitStruct->EBI_PageLength));
  Assert_Param(IS_EBI_PAGE_HIT_MODE(EBI_InitStruct->EBI_PageHitMode));
  Assert_Param(IS_EBI_PAGE_ACCESS_TIME(EBI_InitStruct->EBI_PageAccessTime));
  Assert_Param(IS_EBI_PAGE_OPEN_TIME(EBI_InitStruct->EBI_PageOpenTime));
  #endif


  *((u32 *)((u32)&HT_EBI->ATR0 + offset)) = EBI_InitStruct->EBI_AddressSetupTime |
                                            (EBI_InitStruct->EBI_AddressHoldTime << 8);
#if (LIBCFG_EBI_V01)
*((u32 *)((u32)&HT_EBI->RTR0 + offset)) = EBI_InitStruct->EBI_ReadSetupTime |
                                            (EBI_InitStruct->EBI_ReadStrobeTime << 8) |
                                            (EBI_InitStruct->EBI_ReadHoldTime << 16);
#else
*((u32 *)((u32)&HT_EBI->RTR0 + offset)) = EBI_InitStruct->EBI_ReadSetupTime |
                                            (EBI_InitStruct->EBI_ReadStrobeTime << 8) |
                                            (EBI_InitStruct->EBI_ReadHoldTime << 16) |
                                            EBI_InitStruct->EBI_PageMode;
#endif
  *((u32 *)((u32)&HT_EBI->WTR0 + offset)) = EBI_InitStruct->EBI_WriteSetupTime |
                                            (EBI_InitStruct->EBI_WriteStrobeTime << 8) |
                                            (EBI_InitStruct->EBI_WriteHoldTime << 16);
  *((u32 *)((u32)&HT_EBI->PR0 + offset)) = EBI_InitStruct->EBI_ChipSelectPolarity |
                                           (EBI_InitStruct->EBI_ReadEnablePolarity << 1) |
                                           (EBI_InitStruct->EBI_AddressLatchPolarity << 3) |
                                           #if (LIBCFG_EBI_BYTELAND_ASYNCREADY)
                                           (EBI_InitStruct->EBI_ReadySignalPolarity << 4) |
                                           (EBI_InitStruct->EBI_ByteLanePolarity << 5) |
                                           #endif
                                           (EBI_InitStruct->EBI_WriteEnablePolarity << 2);


  /*------------------------- EBI Control Register Configuration -------------------------------------------*/
  tmp = (3 << (bank * 2)) | (0x00001000 << bank) |
        (0x00010000 << (bank * 2)) | (0x00020000 << (bank * 2)) |
        (0x01000000 << bank);
  tmp = HT_EBI->CR & (~tmp);
  HT_EBI->CR = (EBI_InitStruct->EBI_Mode << (bank * 2)) |
               (EBI_InitStruct->EBI_IdleCycle << bank) |
               #if (LIBCFG_EBI_BYTELAND_ASYNCREADY)
               (EBI_InitStruct->EBI_AsynchronousReady << (bank * 2)) |
               (EBI_InitStruct->EBI_ARDYTimeOut << (bank * 2)) |
               (EBI_InitStruct->EBI_ByteLane << bank) |
               #endif
               (EBI_InitStruct->EBI_IdleCycleTime << 28) | tmp;

  #if !(LIBCFG_EBI_V01)
  if (EBI_InitStruct->EBI_PageMode)
  {
    Assert_Param(IS_EBI_PAGE_LENGTH(EBI_InitStruct->EBI_PageLength));
    Assert_Param(IS_EBI_PAGE_HIT_MODE(EBI_InitStruct->EBI_PageHitMode));
    Assert_Param(IS_EBI_PAGE_ACCESS_TIME(EBI_InitStruct->EBI_PageAccessTime));
    Assert_Param(IS_EBI_PAGE_OPEN_TIME(EBI_InitStruct->EBI_PageOpenTime));

    HT_EBI->PCR = EBI_InitStruct->EBI_PageLength | EBI_InitStruct->EBI_PageHitMode |
                  (EBI_InitStruct->EBI_PageAccessTime << 8) | (EBI_InitStruct->EBI_PageOpenTime << 16);
  }
  #endif
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
  #if (LIBCFG_EBI_BYTELAND_ASYNCREADY)
  EBI_InitStruct->EBI_ByteLane = EBI_BYTELANE_DISABLE;
  EBI_InitStruct->EBI_AsynchronousReady = EBI_ASYNCHRONOUSREADY_DISABLE;
  EBI_InitStruct->EBI_ARDYTimeOut = EBI_ARDYTIMEOUT_DISABLE;
  EBI_InitStruct->EBI_ByteLanePolarity = EBI_BYTELANEPOLARITY_LOW;
  EBI_InitStruct->EBI_ReadySignalPolarity = EBI_READYSIGNALPOLARITY_LOW;
  #endif
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
  #if !(LIBCFG_EBI_V01)
  EBI_InitStruct->EBI_PageMode = EBI_PAGEMODE_DISABLE;
  EBI_InitStruct->EBI_PageLength = EBI_PAGELENGTH_4;
  EBI_InitStruct->EBI_PageHitMode = EBI_PAGEHITMODE_ADDINC;
  EBI_InitStruct->EBI_PageAccessTime = 0xF;
  EBI_InitStruct->EBI_PageOpenTime = 0xFF;
  #endif
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

#if !(LIBCFG_EBI_V01)
/*********************************************************************************************************//**
  * @brief  Enable or Disable the specified EBI interrupt.
  * @param  EBI_Int: specify the EBI interrupt source to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg EBI_INT_TOUT   : ARDY time out interrupt
  *     @arg EBI_INT_ACCDIS : Access disabled bank interrupt
  *     @arg EBI_INT_ACCRES : Access under software reset interrupt
  *     @arg EBI_INT_ALL    : All EBI interrupt
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void EBI_IntConfig(u32 EBI_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EBI_INT(EBI_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_EBI->IEN |= EBI_Int;
  }
  else
  {
    HT_EBI->IEN &= (u32)~EBI_Int;
  }
}

/*********************************************************************************************************//**
  * @brief  Check whether the specified EBI interrupt has been occurred.
  * @param  EBI_IntFlag: specify the EBI interrupt to be check.
  *   This parameter can be one of the following values:
  *     @arg EBI_INT_TOUT   : ARDY time out interrupt
  *     @arg EBI_INT_ACCERR : Access disabled bank or under software reset interrupt
  * @retval SET or RESET
  ***********************************************************************************************************/
FlagStatus EBI_GetIntStatus(u32 EBI_IntFlag)
{
  u32 status = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_EBI_INT_FLAG(EBI_IntFlag));

  status = HT_EBI->IF;

  if ((status & EBI_IntFlag) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
  * @brief  Clear the specified EBI interrupt flag.
  * @param  EBI_IntFlag: specify the interrupt flag that is to be cleared.
  *   This parameter can be any combination of the following values:
  *     @arg EBI_INT_TOUT   : ARDY time out interrupt flag
  *     @arg EBI_INT_ACCERR : Access disabled bank or under software reset interrupt flag
  * @retval None
  ***********************************************************************************************************/
void EBI_ClearIntFlag(u32 EBI_IntFlag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EBI_INT_FLAG(EBI_IntFlag));

  HT_EBI->IFC = EBI_IntFlag;
}
#endif

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

#if (LIBCFG_EBI_BYTELAND_ASYNCREADY)
/*********************************************************************************************************//**
 * @brief Check whether the specified EBI ARDY flag has been set.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus EBI_GetARDYStatus(void)
{
  if (HT_EBI->SR & 0x10)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}
#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
