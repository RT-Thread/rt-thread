/*********************************************************************************************************//**
 * @file    ht32f5xxxx_tkey.c
 * @version $Rev:: 5500         $
 * @date    $Date:: 2021-07-20 #$
 * @brief   This file provides all the TKEY firmware functions.
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
#include "ht32f5xxxx_tkey.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup TKEY TKEY
  * @brief TKEY driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup TKEY_Private_Define TKEY private definitions
  * @{
  */
#define TKCLKSEL_MASK           (0x80000000)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup TKEY_Exported_Functions TKEY exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the TKEY peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void TKEY_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.TKEY = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure Touch key IP clock source.
 * @param Sel: Specify the Touch key IP clock source..
 *   This parameter can be one of the following values:
 *     @arg TKEY_PCLK : PCLK.
 *     @arg TKEY_LSI : LSI.
 * @retval None
 ************************************************************************************************************/
void TKEY_IPClockConfig(TKEY_IP_CLK_Enum Sel)
{
  Assert_Param(IS_TKEY_IP_CLK(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & TKCLKSEL_MASK) | (Sel << 31);
}

/*********************************************************************************************************//**
 * @brief Configure the RefOSC Delay time.
 * @param Sel: Specify the periodic auto scan mode time out.
 *   This parameter can be one of the following values:
 *     @arg TKEY_RefOSC_DelayTime_0 : 4 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_1 : 2 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_2 : 4 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_3 : 8 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_4 : 16 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_5 : 32 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_6 : 64 RefOSC clock.
 *     @arg TKEY_RefOSC_DelayTime_7 : 4 RefOSC clock.
 * @retval None
 ************************************************************************************************************/
void TKEY_RefOSCDelayTimeConfig(TKEY_RefOSC_DelayTime_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_RefOSC_DelayTime(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & ~(7 << 13)) | Sel;
}
/*********************************************************************************************************//**
 * @brief Configure the periodic auto scan mode time out.
 * @param Sel: Specify the periodic auto scan mode time out.
 *   This parameter can be one of the following values:
 *     @arg TKEY_PASM_TIMEOUT_0 : 2^13/FLIRC.
 *     @arg TKEY_PASM_TIMEOUT_1 : 2^14/FLIRC.
 *     @arg TKEY_PASM_TIMEOUT_2 : 2^15/FLIRC.
 *     @arg TKEY_PASM_TIMEOUT_3 : 2^16/FLIRC.
 *     @arg TKEY_PASM_TIMEOUT_4 : 2^17/FLIRC.
 *     @arg TKEY_PASM_TIMEOUT_5 : 2^18/FLIRC.
 * @retval None
 ************************************************************************************************************/
void TKEY_PASMTimeoutConfig(TKEY_PASM_TIMEOUT_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_PASM_TIMEOUT(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & ~(7 << 10)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the periodic auto scan mode period.
 * @param Sel: Specify the periodic auto scan mode period.
 *   This parameter can be one of the following values:
 *     @arg TKEY_PASM_PERIOD_0 : 2^14/FLIRC.
 *     @arg TKEY_PASM_PERIOD_1 : 2^13/FLIRC.
 *     @arg TKEY_PASM_PERIOD_2 : 2^12/FLIRC.
 *     @arg TKEY_PASM_PERIOD_3 : 2^11/FLIRC.
 * @retval None
 ************************************************************************************************************/
void TKEY_PASMPeriodConfig(TKEY_PASM_PERIOD_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_PASM_PERIOD(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & ~(3 << 8)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the touch key 16-bit counter clock source.
 * @param Sel: Specify the 16-bit counter clock source.
 *   This parameter can be one of the following values:
 *     @arg TKEY_TK16S_CLK_0 : TKCLK/16.
 *     @arg TKEY_TK16S_CLK_1 : TKCLK/32.
 *     @arg TKEY_TK16S_CLK_2 : TKCLK/64.
 *     @arg TKEY_TK16S_CLK_3 : TKCLK/128.
 * @retval None
 ************************************************************************************************************/
void TKEY_16BitCounterClockConfig(TKEY_TK16S_CLK_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_TK16S_CLK(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & ~(3 << 5)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the touch key OSC frequency.
 * @param Sel: Specify the Touch Key frequency.
 *   This parameter can be one of the following values:
 *     @arg TKEY_TKFS_FREQ_0 : 1MHz.
 *     @arg TKEY_TKFS_FREQ_1 : 3MHz.
 *     @arg TKEY_TKFS_FREQ_2 : 7MHz.
 *     @arg TKEY_TKFS_FREQ_3 : 11MHz.
 * @retval None
 ************************************************************************************************************/
void TKEY_OSCFreqConfig(TKEY_TKFS_FREQ_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_TKFS_FREQ(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & ~(3 << 3)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the touch key operation mode.
 * @param Sel: Specify the Touch Key mode.
 *   This parameter can be one of the following values:
 *     @arg TKEY_MODE_AUTOSCAN : Auto scan mode.
 *     @arg TKEY_MODE_MANUAL   : Manual mode.
 *     @arg TKEY_MODE_PASM     : Periodic auto scan mode.
 * @retval None
 ************************************************************************************************************/
void TKEY_ModeConfig(TKEY_MODE_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_MODE(Sel));

  HT_TKEY->TKCR = (HT_TKEY->TKCR & ~(3 << 1)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Touch Key detection control.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TKEY_StartCmd(ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_TKEY->TKCR |= (1 << 0);
  }
  else
  {
    HT_TKEY->TKCR &= ~(1 << 0);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified TKEY interrupt.
 * @param TKEY_Int: specify if the TKEY interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg TKEY_INT_TKRCOVE : 8-bit time slot counter overflow interrupt
 *     @arg TKEY_INT_TKTHE   : Touch Key threshold match interrupt
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TKEY_IntConfig(u32 TKEY_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_INT(TKEY_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_TKEY->TKIER |= TKEY_Int;
  }
  else
  {
    HT_TKEY->TKIER &= ~TKEY_Int;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified TKEY flag has been set or not.
 * @param TKEY_Flag: specify the flag that is to be check.
 *   This parameter can be one of the following values:
 *     @arg TKEY_FLAG_TKBUSY  : Touch Key busy flag
 *     @arg TKEY_FLAG_TKCFOV  : Touch Key 16-bit C/F counter overflow flag
 *     @arg TKEY_FLAG_TK16OV  : Touch Key 16-bit counter overflow flag
 *     @arg TKEY_FLAG_TKRCOVF : 8-bit time slot counter overflow flag
 *     @arg TKEY_FLAG_TKTHF   : Touch Key threshold match flag
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus TKEY_GetFlagStatus(u32 TKEY_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_FLAG(TKEY_Flag));

  if ((HT_TKEY->TKSR & TKEY_Flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified TKEY flag.
 * @param TKEY_Flag: specify the flag that is to be cleared.
 *   This parameter can be one of the following values:
 *     @arg TKEY_FLAG_TKCFOV  : Touch Key 16-bit C/F counter overflow flag
 *     @arg TKEY_FLAG_TK16OV  : Touch Key 16-bit counter overflow flag
 *     @arg TKEY_FLAG_TKRCOVF : 8-bit time slot counter overflow flag
 *     @arg TKEY_FLAG_TKTHF   : Touch Key threshold match flag
 * @retval None
 ************************************************************************************************************/
void TKEY_ClearFlag(u32 TKEY_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKEY_FLAG_CLEAR(TKEY_Flag));

  HT_TKEY->TKSR = TKEY_Flag;
}

/*********************************************************************************************************//**
 * @brief Get the touch key 16-bit counter value.
 * @retval The counter value
 ************************************************************************************************************/
u32 TKEY_Get16BitCounterValue(void)
{
  return HT_TKEY->TKCNTR;
}

/*********************************************************************************************************//**
 * @brief Set the 8-bit time slot counter reload value.
 * @param Reload: Specify the counter reload value.
 * @retval None
 ************************************************************************************************************/
void TKEY_Set8BitCounterReload(u32 Reload)
{
  HT_TKEY->TKTSCRR = Reload;
}

/*********************************************************************************************************//**
 * @brief Get the 8-bit time slot counter reload value.
 * @retval The counter reload value
 ************************************************************************************************************/
u32 TKEY_Get8BitCounterReload(void)
{
  return HT_TKEY->TKTSCRR;
}

/*********************************************************************************************************//**
 * @brief Configure the 8-bit time slot counter clock source.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Sel: Specify the 8-bit time slot counter clock source.
 *   This parameter can be one of the following values:
 *     @arg TKM_TSS_CLK_0 : Ref OSC.
 *     @arg TKM_TSS_CLK_1 : TKCLK/32.
 *     @arg TKM_TSS_CLK_2 : TKCLK/64.
 *     @arg TKM_TSS_CLK_3 : TKCLK/128.
 * @retval None
 ************************************************************************************************************/
void TKM_TimeSlotCounterClockConfig(TKM_Enum TKMn, TKM_TSS_CLK_Enum Sel)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_TSS_CLK(Sel));

  TKMx->CR = (TKMx->CR & ~(3 << 8)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Reference OSC.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TKM_RefOSCCmd(TKM_Enum TKMn, ControlStatus NewState)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    TKMx->CR |=  (1 << 7);
  }
  else
  {
    TKMx->CR &= ~(1 << 7);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Key OSC.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TKM_KeyOSCCmd(TKM_Enum TKMn, ControlStatus NewState)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    TKMx->CR |= (1 << 6);
  }
  else
  {
    TKMx->CR &= ~(1 << 6);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Multi-frequency.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TKM_MultiFreqCmd(TKM_Enum TKMn, ControlStatus NewState)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    TKMx->CR |= (1 << 5);
  }
  else
  {
    TKMx->CR &= ~(1 << 5);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the C/F OSC frequency-hopping.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Sel: Specify the C/F OSC frequency-hopping method.
 *   This paramter can be one of the following values:
 *     @arg TKM_SOF_CTRL_SW :
 *     @arg TKM_SOF_CTRL_HW :
 * @retval None
 ************************************************************************************************************/
void TKM_SOFCtrlConfig(TKM_Enum TKMn, TKM_SOF_CTRL_Enum Sel)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_SOF_CTRL(Sel));

  TKMx->CR = (TKMx->CR & ~(1 << 3)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the Key OSC and the Reference OSC frequency.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Sel: Specify the OSC frequency.
 *   This paramter can be one of the following values:
 *     @arg TKM_SOF_FREQ_0 : 1.020MHz.
 *     @arg TKM_SOF_FREQ_1 : 1.040MHz.
 *     @arg TKM_SOF_FREQ_2 : 1.059MHz.
 *     @arg TKM_SOF_FREQ_3 : 1.074MHz.
 *     @arg TKM_SOF_FREQ_4 : 1.085MHz.
 *     @arg TKM_SOF_FREQ_5 : 1.099MHz.
 *     @arg TKM_SOF_FREQ_6 : 1.111MHz.
 *     @arg TKM_SOF_FREQ_7 : 1.125MHz.
 * @retval None
 ************************************************************************************************************/
void TKM_SOFFreqConfig(TKM_Enum TKMn, TKM_SOF_FREQ_Enum Sel)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_SOF_FREQ(Sel));

  TKMx->CR = (TKMx->CR & ~(7 << 0)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified Touch Key.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TKM_KeyCmd(TKM_Enum TKMn, TKM_KEY_Enum Key, ControlStatus NewState)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    TKMx->KCFGR |= (1 << Key);
  }
  else
  {
    TKMx->KCFGR &= ~(1 << Key);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the Time Slot X key selection (for auto scan mode & Periodic auto scan mode).
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Slot: TKM_TIME_SLOT_0 ~ TKM_TIME_SLOT_3
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @retval None
 ************************************************************************************************************/
void TKM_TimeSlotKeyConfig(TKM_Enum TKMn, TKM_TIME_SLOT_Enum Slot, TKM_KEY_Enum Key)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));
  u32 offset = (16 + (Slot * 2));

  /* Check the parameters */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_TIME_SLOT(Slot));
  Assert_Param(IS_TKM_KEY(Key));

  TKMx->KCFGR = (TKMx->KCFGR & ~(3 << offset)) | (Key << offset);
}

/*********************************************************************************************************//**
 * @brief Configure the Key threshold.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @param Sel: Specify the Key threshold.
 *   This parameter can be one of the following values:
 *     @arg TKM_KEY_THR_LOWER :
 *     @arg TKM_KEY_THR_UPPER :
 * @retval None
 ************************************************************************************************************/
void TKM_KeyThresholdConfig(TKM_Enum TKMn, TKM_KEY_Enum Key, TKM_KEY_THR_Enum Sel)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));
  u32 offset = (8 + Key);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));
  Assert_Param(IS_TKM_KEY_THR(Sel));

  TKMx->KCFGR = (TKMx->KCFGR & ~(1 << offset)) | (Sel << offset);
}

/*********************************************************************************************************//**
 * @brief Check whether the specified key threshold match flag has been set or not.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus TKM_GetMatchFlagStatus(TKM_Enum TKMn, TKM_KEY_Enum Key)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  if ((TKMx->SR & (1 << Key)) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified key threshold match flag.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @retval None
 ************************************************************************************************************/
void TKM_ClearMatchFlag(TKM_Enum TKMn, TKM_KEY_Enum Key)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  TKMx->SR = (1 << Key);
}

/*********************************************************************************************************//**
 * @brief Set the reference OSC capacitor value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Value: Specify the capacitor value between 0x000 ~ 0x3FF.
 * @retval None
 ************************************************************************************************************/
void TKM_SetRefOSCCapacitor(TKM_Enum TKMn, u32 Value)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));

  TKMx->ROCPR = Value;
}

/*********************************************************************************************************//**
 * @brief Get the reference OSC capacitor value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @retval The capacitor value
 ************************************************************************************************************/
u32 TKM_GetRefOSCCapacitor(TKM_Enum TKMn)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));

  return TKMx->ROCPR;
}

/*********************************************************************************************************//**
 * @brief Set the key capacitor value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @param Value: Specify the capacitor value between 0x000 ~ 0x3FF.
 * @retval None
 ************************************************************************************************************/
void TKM_SetKeyCapacitor(TKM_Enum TKMn, TKM_KEY_Enum Key, u32 Value)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  *(vu32*)((u32)&TKMx->K3CPR + ((3 - Key) * 4)) = Value;
}

/*********************************************************************************************************//**
 * @brief Get the key capacitor value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @retval The capacitor value
 ************************************************************************************************************/
u32 TKM_GetKeyCapacitor(TKM_Enum TKMn, TKM_KEY_Enum Key)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  return *(vu32*)((u32)&TKMx->K3CPR + ((3 - Key) * 4));
}

/*********************************************************************************************************//**
 * @brief Get the 16-bit C/F counter value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @retval The counter value
 ************************************************************************************************************/
u32 TKM_Get16BitCFCounterValue(TKM_Enum TKMn)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));

  return TKMx->CFCNTR;
}

/*********************************************************************************************************//**
 * @brief Get the key counter value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @retval None
 ************************************************************************************************************/
u32 TKM_GetKeyCounterValue(TKM_Enum TKMn, TKM_KEY_Enum Key)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  return *(vu32*)((u32)&TKMx->K3CNTR + ((3 - Key) * 4));
}

/*********************************************************************************************************//**
 * @brief Set the key threshold value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @param Value: Specify the key threshold value between 0x0000 ~ 0xFFFF.
 * @retval None
 ************************************************************************************************************/
void TKM_SetKeyThreshold(TKM_Enum TKMn, TKM_KEY_Enum Key, u32 Value)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  *(vu32*)((u32)&TKMx->K3THR + ((3 - Key) * 4)) = Value;
}

/*********************************************************************************************************//**
 * @brief Get the key threshold value.
 * @param TKMn: TKM_0 ~ TKM_5
 * @param Key: TKM_KEY_0 ~ TKM_KEY_3
 * @retval The threshold value
 ************************************************************************************************************/
u32 TKEY_GetKeyThreshold(TKM_Enum TKMn, TKM_KEY_Enum Key)
{
  HT_TKM_TypeDef *TKMx = (HT_TKM_TypeDef *)((u32)&HT_TKEY->TKM0 + (TKMn * 0x100));

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TKM(TKMn));
  Assert_Param(IS_TKM_KEY(Key));

  return *(vu32*)((u32)&TKMx->K3THR + ((3 - Key) * 4));
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
