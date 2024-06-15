/*********************************************************************************************************//**
 * @file    ht32f1xxxx_rtc.c
 * @version $Rev:: 2233         $
 * @date    $Date:: 2020-10-13 #$
 * @brief   This file provides all the RTC firmware functions.
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
#include "ht32f1xxxx_rtc.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup RTC RTC
  * @brief RTC driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup RTC_Private_Define RTC private definitions
  * @{
  */
#define RTC_CR_ADDR   (HT_RTC_BASE + 0x008)
#define BB_RTCEN      BitBand(RTC_CR_ADDR, 0)
#define BB_RTCSRC     BitBand(RTC_CR_ADDR, 1)
#define BB_LSI_EN     BitBand(RTC_CR_ADDR, 2)
#define BB_LSE_EN     BitBand(RTC_CR_ADDR, 3)
#define BB_CMPCLR     BitBand(RTC_CR_ADDR, 4)
#define BB_SOP        BitBand(RTC_CR_ADDR, 5)
#define BB_ROEN       BitBand(RTC_CR_ADDR, 16)
#define BB_ROES       BitBand(RTC_CR_ADDR, 17)
#define BB_ROWM       BitBand(RTC_CR_ADDR, 18)
#define BB_ROAP       BitBand(RTC_CR_ADDR, 19)
#define BB_ROLF       BitBand(RTC_CR_ADDR, 20)
#define RPRE_MASK     (0xFFFFF0FF)

/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RTC_Exported_Functions RTC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the RTC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void RTC_DeInit(void)
{
  HT_RTC->CR = 0x00000004;
  HT_RTC->CMP = 0x0;
  HT_RTC->IWEN = 0x0;
  HT_RTC->CR |= 0x00000005;
  while (HT_RTC->CNT);
  HT_RTC->CR = 0x00000F04;
  /* Read the RTC_SR register to clear it                                                                   */
  HT_RTC->SR;
}

/*********************************************************************************************************//**
 * @brief Select the RTC timer clock source.
 * @param Source: specify the clock source of RTC and backup domain.
 *   @arg RTC_SRC_LSI : Low speed internal clock.
 *   @arg RTC_SRC_LSE : Low speed external clock.
 * @retval None
 ************************************************************************************************************/
void RTC_ClockSourceConfig(RTC_SRC_Enum Source)
{
  Assert_Param(IS_RTC_SRC(Source));

  BB_RTCSRC = Source;
}

#if (LIBCFG_RTC_LSI_LOAD_TRIM)
/*********************************************************************************************************//**
 * @brief Loads the LSI trim data.
 * @retval None
 ************************************************************************************************************/
void RTC_LSILoadTrimData(void)
{
  u32 i = 9600;

  HT_RTC->CR &= ~(1UL << 2);
  /* Insert a delay must > 1 CK_RTC                                                                         */
  while (i--);
  HT_RTC->CR |= (1UL << 2);
  while ((HT_CKCU->GCSR & 0x20) == 0);
}
#endif

/*********************************************************************************************************//**
 * @brief Select the LSE startup mode.
 * @param Mode: specify the LSE startup mode.
 *   This parameter can be one of the following values:
 *     @arg RTC_LSESM_NORMAL : Little power consumption but longer startup time.
 *     @arg RTC_LSESM_FAST   : Shortly startup time but higher power consumption.
 * @retval None
 ************************************************************************************************************/
void RTC_LSESMConfig(RTC_LSESM_Enum Mode)
{
  Assert_Param(IS_RTC_LSESM(Mode));

  BB_SOP = Mode;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LSE clock.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RTC_LSECmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == DISABLE)
  {
    BB_LSE_EN = 0;
    while (HT_CKCU->GCSR & 0x10);
  }
  else
  {
    BB_LSE_EN = 1;
    while ((HT_CKCU->GCSR & 0x10) == 0);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the compare match function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RTC_CMPCLRCmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  BB_CMPCLR = NewState;
}

/*********************************************************************************************************//**
 * @brief Configure the RTC prescaler.
 * @param Psc: Value of RTC prescaler.
 *   This parameter can be one of following values:
 *     @arg RTC_RPRE_1
 *     @arg RTC_RPRE_2
 *     @arg RTC_RPRE_4
 *     @arg RTC_RPRE_8
 *     @arg RTC_RPRE_16
 *     @arg RTC_RPRE_32
 *     @arg RTC_RPRE_64
 *     @arg RTC_RPRE_128
 *     @arg RTC_RPRE_256
 *     @arg RTC_RPRE_512
 *     @arg RTC_RPRE_1024
 *     @arg RTC_RPRE_2048
 *     @arg RTC_RPRE_4096
 *     @arg RTC_RPRE_8192
 *     @arg RTC_RPRE_16384
 *     @arg RTC_RPRE_32768
 * @retval None
 ************************************************************************************************************/
void RTC_SetPrescaler(RTC_RPRE_Enum Psc)
{
  Assert_Param(IS_RTC_PSC(Psc));

  HT_RTC->CR = (HT_RTC->CR & RPRE_MASK) | Psc;
}

/*********************************************************************************************************//**
 * @brief Return the RTC prescaler setting.
 * @retval The prescaler value. It is powered by 2 and max.is 32768.
 ************************************************************************************************************/
u16 RTC_GetPrescaler(void)
{
  u32 prescaler;

  prescaler = HT_RTC->CR >> 8;

  return ((u16)0x1 << prescaler);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the RTC timer.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RTC_Cmd(ControlStatus NewState)
{
  BB_RTCEN = NewState;
}

/*********************************************************************************************************//**
 * @brief Return the counter value.
 * @retval Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 RTC_GetCounter(void)
{
  /* !!! NOTICE !!!
     A 1/CK_RTC delay time is required if you read the RTC CNT count immediately when the RTC compare match
     occurred (in the RTC ISR or the system is wakeup from the DeepSleep1/2).
     The CK_RTC can be configured from the LSI or LSE.
  */
  return (HT_RTC->CNT);
}

/*********************************************************************************************************//**
 * @brief Configure the compare match value.
 * @param Compare: Between 0x0 ~ 0xFFFFFFFF
 * @retval None
 ************************************************************************************************************/
void RTC_SetCompare(u32 Compare)
{
  HT_RTC->CMP = Compare;
}

/*********************************************************************************************************//**
 * @brief Return the compare match value.
 * @retval Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 RTC_GetCompare(void)
{
  return (HT_RTC->CMP);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified wakeup source.
 * @param RTC_WAKEUP Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *   @arg RTC_WAKEUP_CSEC : Waken up by counter counting.
 *   @arg RTC_WAKEUP_CM   : Waken up by counter compare match with CMP register.
 *   @arg RTC_WAKEUP_OV   : Waken up by counter overflow.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RTC_WakeupConfig(u32 RTC_WAKEUP, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RTC_WAKEUP(RTC_WAKEUP));

  if (NewState != DISABLE)
  {
    HT_RTC->IWEN |= RTC_WAKEUP;
  }
  else
  {
    HT_RTC->IWEN &= ~RTC_WAKEUP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified interrupt source.
 * @param RTC_INT: Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *     @arg RTC_INT_CSEC : Assert interrupt at counter counting
 *     @arg RTC_INT_CM   : Assert interrupt at counter compare match with CMP register
 *     @arg RTC_INT_OV   : Assert interrupt at counter overflow
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RTC_IntConfig(u32 RTC_INT, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RTC_INT(RTC_INT));

  if (NewState != DISABLE)
  {
    HT_RTC->IWEN |= RTC_INT;
  }
  else
  {
    HT_RTC->IWEN &= ~RTC_INT;
  }
}

/*********************************************************************************************************//**
 * @brief Return the RTC flags.
 * @retval RTC_STS register value.
 *   This parameter can be any combination of following:
 *   - 0x0 : No flag set
 *   - 0x1 : Count flag
 *   - 0x2 : Match flag
 *   - 0x4 : Overflow flag
 * @note RTC_SR is read clear.
 ************************************************************************************************************/
u8 RTC_GetFlagStatus(void)
{
  return ((u8)HT_RTC->SR);
}

/*********************************************************************************************************//**
 * @brief Configure the RTC output function.
 * @param WMode: specify the RTC output waveform mode
 *   This parameter can be one of the following values:
 *     @arg RTC_ROWM_PULSE : Pulse mode
 *     @arg RTC_ROWM_LEVEL : Level mode
 * @param EventSel: specify the RTC output event selection
 *   This parameter can be one of the following values:
 *     @arg RTC_ROES_MATCH  : Compare match selected
 *     @arg RTC_ROES_SECOND : Second clock selected
 * @param Pol: specify the RTC output active polarity
 *   This parameter can be one of the following values:
 *     @arg RTC_ROAP_HIGH : Active level is high
 *     @arg RTC_ROAP_LOW  : Active level is low
 * @note This function will disable RTC output first.
 ************************************************************************************************************/
void RTC_OutConfig(RTC_ROWM_Enum WMode, RTC_ROES_Enum EventSel, RTC_ROAP_Enum Pol)
{
  Assert_Param(IS_RTC_ROWM(WMode));
  Assert_Param(IS_RTC_ROES(EventSel));
  Assert_Param(IS_RTC_ROAP(Pol));

  BB_ROEN = 0;
  BB_ROWM = WMode;
  BB_ROES = EventSel;
  BB_ROAP = Pol;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the RTC output.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RTC_OutCmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  BB_ROEN = NewState;
}

/*********************************************************************************************************//**
 * @brief Return the RTCOUT level mode flag.
 * @retval SET or RESET
 * @note Reads RTC_CR action will clear ROLF flag.
 ************************************************************************************************************/
FlagStatus RTC_GetOutStatus(void)
{
  return (FlagStatus)BB_ROLF;
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
