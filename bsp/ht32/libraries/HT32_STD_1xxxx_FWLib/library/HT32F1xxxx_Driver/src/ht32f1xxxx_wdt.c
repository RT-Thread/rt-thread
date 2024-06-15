/*********************************************************************************************************//**
 * @file    ht32f1xxxx_wdt.c
 * @version $Rev:: 2797         $
 * @date    $Date:: 2022-11-28 #$
 * @brief   This file provides all the WDT firmware functions.
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
#include "ht32f1xxxx_wdt.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup WDT WDT
  * @brief WDT driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup WDT_Private_Define WDT private definitions
  * @{
  */

/* WDT Restart Key                                                                                          */
#define RESTART_KEY            ((u32)0x5FA00000)

/* WDT Protect mask                                                                                         */
#define PRCT_SET               ((u32)0x0000CA35)
#define PRCT_RESET             ((u32)0x000035CA)

/* WDT WDTFIEN mask                                                                                         */
#define MODE0_WDTFIEN_SET      ((u32)0x00001000)
#define MODE0_WDTFIEN_RESET    ((u32)0xFFFFEFFF)

/* WDT WDTRSTEN mask                                                                                        */
#define MODE0_WDTRETEN_SET     ((u32)0x00002000)
#define MODE0_WDTRETEN_RESET   ((u32)0xFFFFDFFF)

/* WDT WDTEN mask                                                                                           */
#define MODE0_WDTEN_SET        ((u32)0x00010000)
#define MODE0_WDTEN_RESET      ((u32)0xFFFEFFFF)

/* WDT WDTLOCK mask                                                                                         */
#define MODE0_WDTLOCK_SET      ((u32)0x00000010)
#define MODE0_WDTLOCK_RESET    ((u32)0x00000000)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup WDT_Exported_Functions WDT exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the WDT peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void WDT_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.WDT = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the WDT.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void WDT_Cmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_WDT->MR0 |= MODE0_WDTEN_SET;
  }
  else
  {
    HT_WDT->MR0 &= MODE0_WDTEN_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the WDT to run or halt in sleep and deep sleep1 mode.
 * @param WDT_Mode:
 *   This parameter can be one of the following values:
 *     @arg MODE0_WDTSHLT_BOTH  : WDT runs in sleep and deep sleep1 mode
 *     @arg MODE0_WDTSHLT_SLEEP : WDT runs in sleep mode
 *     @arg MODE0_WDTSHLT_HALT  : WDT halts in sleep and deep sleep1 mode
 * @retval None
 ************************************************************************************************************/
void WDT_HaltConfig(u32 WDT_Mode)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_WDT_WDTSHLT_MODE(WDT_Mode));

  HT_WDT->MR0 = ((WDT_Mode) | (HT_WDT->MR0 & 0x00013FFF));
}

#if (LIBCFG_WDT_INT)
/*********************************************************************************************************//**
 * @brief  Enable or Disable the WDT interrupt when WDT meets underflow or error.
 * @param  NewState: This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void WDT_IntConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_WDT->MR0 |= MODE0_WDTFIEN_SET;
  }
  else
  {
    HT_WDT->MR0 &= MODE0_WDTFIEN_RESET;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable the WDT Reset when WDT meets underflow or error.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void WDT_ResetCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_WDT->MR0 |= MODE0_WDTRETEN_SET;
  }
  else
  {
    HT_WDT->MR0 &= MODE0_WDTRETEN_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable protection mechanism of the WDT.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void WDT_ProtectCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_WDT->PR = PRCT_SET;
  }
  else
  {
    HT_WDT->PR = PRCT_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Set reload value of the WDT.
 * @param WDT_WDTV : specify the WDT Reload value.
 *   This parameter must be a number between 0 and 0x0FFF
 * @retval None
 ************************************************************************************************************/
void WDT_SetReloadValue(u16 WDT_WDTV)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_WDT_RELOAD(WDT_WDTV));

  HT_WDT->MR0 = WDT_WDTV | (HT_WDT->MR0 & 0x0000F000);
}

/*********************************************************************************************************//**
 * @brief Get the current reload value of the WDT.
 * @retval WDT reload value between 0 and 0x0FFF
 ************************************************************************************************************/
u16 WDT_GetReloadValue(void)
{
  return ((u16)(HT_WDT->MR0 & 0xFFF));
}

/*********************************************************************************************************//**
 * @brief Set delta value of the WDT.
 * @param WDT_WDTD : specify the WDT Delta value.
 *   This parameter must be a number between 0 and 0x0FFF
 * @retval None
 ************************************************************************************************************/
void WDT_SetDeltaValue(u16 WDT_WDTD)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_WDT_DELTA(WDT_WDTD));

  HT_WDT->MR1 = (WDT_WDTD | (HT_WDT->MR1 & 0x00007000));
}

/*********************************************************************************************************//**
 * @brief Get current delta value of the WDT.
 * @retval WDT delta value between 0 and 0x0FFF
 ************************************************************************************************************/
u16 WDT_GetDeltaValue(void)
{
  return ((u16)(HT_WDT->MR1 & 0xFFF));
}

/*********************************************************************************************************//**
 * @brief Set prescaler value of the WDT.
 * @param WDT_PRESCALER: specify the WDT Prescaler value.
 *   This parameter can be one of the following values:
 *     @arg WDT_PRESCALER_1   : WDT prescaler set to 1
 *     @arg WDT_PRESCALER_2   : WDT prescaler set to 2
 *     @arg WDT_PRESCALER_4   : WDT prescaler set to 4
 *     @arg WDT_PRESCALER_8   : WDT prescaler set to 8
 *     @arg WDT_PRESCALER_16  : WDT prescaler set to 16
 *     @arg WDT_PRESCALER_32  : WDT prescaler set to 32
 *     @arg WDT_PRESCALER_64  : WDT prescaler set to 64
 *     @arg WDT_PRESCALER_128 : WDT prescaler set to 128
 * @retval None
 ************************************************************************************************************/
void WDT_SetPrescaler(u16 WDT_PRESCALER)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_WDT_PRESCALER(WDT_PRESCALER));

  HT_WDT->MR1 = (WDT_PRESCALER | (HT_WDT->MR1 & 0x00000FFF));
}

/*********************************************************************************************************//**
 * @brief Get the current prescaler value of the WDT.
 * @retval WDT prescaler value
 ************************************************************************************************************/
u8 WDT_GetPrescaler(void)
{
  u32 tmp;

  tmp = HT_WDT->MR1 & 0x7000;
  tmp >>= 12;
  return ((u8)0x1 << tmp);
}

/*********************************************************************************************************//**
 * @brief WDT Restart (Reload WDT Counter)
 * @retval None
 ************************************************************************************************************/
void WDT_Restart(void)
{
  HT_WDT->CR = RESTART_KEY | 0x1;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified WDT flag has been set.
 * @param WDT_FLAG: specify the flag to be check.
 *   This parameter can be one of the following values:
 *     @arg WDT_FLAG_UNDERFLOW : WDT underflow active
 *     @arg WDT_FLAG_ERROR     : WDT error active
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus WDT_GetFlagStatus(u32 WDT_FLAG)
{
  u32 statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_WDT_FLAG(WDT_FLAG));

  statusreg = HT_WDT->SR;

  if (statusreg != WDT_FLAG)
  {
    bitstatus = RESET;
  }
  else
  {
    bitstatus = SET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the WDTLOCK.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void WDT_LockCmd(ControlStatus NewState)
{
  u32 uRegVale;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  uRegVale =  HT_WDT->CSR;
  if (NewState != DISABLE)
  {
    HT_WDT->CSR |= (MODE0_WDTLOCK_SET | (uRegVale & 0x00000001));
  }
  else
  {
    HT_WDT->CSR &= (MODE0_WDTLOCK_RESET | (uRegVale & 0x00000001));
  }
}

/*********************************************************************************************************//**
 * @brief WDT source select.
 * @param WDT_SOURCE: LSI or LSE of the WDT source.
 *   This parameter can be one of the following values:
 *     @arg WDT_SOURCE_LSI :
 *     @arg WDT_SOURCE_LSE :
 * @retval None
 ************************************************************************************************************/
void WDT_SourceConfig(u32 WDT_SOURCE)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_WDT_SOURCE_SELECT(WDT_SOURCE));

  if (WDT_SOURCE != WDT_SOURCE_LSE)
  {
    HT_WDT->CSR = WDT_SOURCE_LSI;
  }
  else
  {
    HT_WDT->CSR = WDT_SOURCE_LSE;
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
