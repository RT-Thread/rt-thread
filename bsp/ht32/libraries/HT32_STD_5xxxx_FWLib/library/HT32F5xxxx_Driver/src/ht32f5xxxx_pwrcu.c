/*********************************************************************************************************//**
 * @file    ht32f5xxxx_pwrcu.c
 * @version $Rev:: 6386         $
 * @date    $Date:: 2022-10-27 #$
 * @brief   This file provides all the Power Control Unit firmware functions.
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
#include "ht32f5xxxx_pwrcu.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup PWRCU PWRCU
  * @brief PWRCU driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Private_Define PWRCU private definitions
  * @{
  */
#define Set_RTCEN         SetBit_BB((u32)&HT_CKCU->APBCCR1, 6);
#define Reset_RTCEN       ResetBit_BB((u32)&HT_CKCU->APBCCR1, 6);
#define Get_RTCEN         GetBit_BB((u32)&HT_CKCU->APBCCR1, 6)

#define Set_LDOMODE       SetBit_BB((u32)&HT_PWRCU->CR, 2)
#define Reset_LDOMODE     ResetBit_BB((u32)&HT_PWRCU->CR, 2)

#define Set_LDOOFF        SetBit_BB((u32)&HT_PWRCU->CR, 3)
#define Reset_LDOOFF      ResetBit_BB((u32)&HT_PWRCU->CR, 3)

#define Set_DMOSON        SetBit_BB((u32)&HT_PWRCU->CR, 7)
#define Reset_DMOSON      ResetBit_BB((u32)&HT_PWRCU->CR, 7)

#define Set_WUP0EN        SetBit_BB((u32)&HT_PWRCU->CR, 8)
#define Reset_WUP0EN      ResetBit_BB((u32)&HT_PWRCU->CR, 8)

#if (LIBCFG_PWRCU_WAKEUP1)
#define Set_WUP1EN        SetBit_BB((u32)&HT_PWRCU->CR, 10)
#define Reset_WUP1EN      ResetBit_BB((u32)&HT_PWRCU->CR, 10)
#endif

#if (LIBCFG_PWRCU_V15_READY_SOURCE)
#define Set_V15RDYSC      SetBit_BB((u32)&HT_PWRCU->CR, 12)
#define Reset_V15RDYSC    ResetBit_BB((u32)&HT_PWRCU->CR, 12)
#endif

#define Set_DMOSSTS       SetBit_BB((u32)&HT_PWRCU->CR, 15)
#define Reset_DMOSSTS     ResetBit_BB((u32)&HT_PWRCU->CR, 15)
#define Get_DMOSSTS       GetBit_BB((u32)&HT_PWRCU->CR, 15)

#define Set_BODEN         SetBit_BB((u32)&HT_PWRCU->LVDCSR, 0)
#define Reset_BODEN       ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 0)

#define Set_BODRIS        SetBit_BB((u32)&HT_PWRCU->LVDCSR, 1)
#define Reset_BODRIS      ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 1)

#define Set_BODF          SetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)
#define Reset_BODF        ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)
#define Get_BODF          GetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)

#define Set_LVDEN         SetBit_BB((u32)&HT_PWRCU->LVDCSR, 16)
#define Reset_LVDEN       ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 16)

#define Set_LVDF          SetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)
#define Reset_LVDF        ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)
#define Get_LVDF          GetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)

#define Set_LVDIWEN       SetBit_BB((u32)&HT_PWRCU->LVDCSR, 20)
#define Reset_LVDIWEN     ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 20)

#define Set_LVDEWEN       SetBit_BB((u32)&HT_PWRCU->LVDCSR, 21)
#define Reset_LVDEWEN     ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 21)

#define SLEEPDEEP_SET     0x04      /*!< Cortex SLEEPDEEP bit                                               */

#define PWRRST_SET        0x1
#define PWRTEST_READY     0x27
#define TIME_OUT          24000000
#define WUP0TYPE_MASK     0xFFFCFFFF
#define WUP1TYPE_MASK     0xFFF3FFFF
#define LVDS_MASK         0xFFB9FFFF
#define VREG_V_MASK       0xF3FFFFFF
#define VREG_M_MASK       0xFCFFFFFF
#define PWRRST_SET        0x1
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize backup domain which contains PWRCU and RTC units.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeInit(void)
{
  HT_PWRCU->CR = PWRRST_SET;
  while(HT_PWRCU->CR & 0xFFFFEFFF); /* Skip Bit 12 because it isn't of valuable reference.                  */
  #if (LIBCFG_PWRCU_NO_PORF)
  #else
  while (HT_PWRCU->SR);    /* Waits until the PWRPORF be cleared by read                                    */
  #endif
}

#if (!LIBCFG_NO_PWRCU_TEST_REG)
/*********************************************************************************************************//**
 * @brief Waits, until the PWRCU can be accessed.
 * @retval PWRCU_TIMEOUT or PWRCU_OK
 ************************************************************************************************************/
PWRCU_Status PWRCU_CheckReadyAccessed(void)
{
  u32 wTimeOutCnt = TIME_OUT;

  while (--wTimeOutCnt)
  {
    if (HT_PWRCU->TEST == PWRTEST_READY)
    {
      return PWRCU_OK;
    }
  }
  return PWRCU_TIMEOUT;
}
#endif

/*********************************************************************************************************//**
 * @brief Return the flags of PWRCU.
 * @retval This function will return one of the following:
 *   - 0x0000                                   : There is no flag is set.
 *   - 0x0001 (PWRCU_FLAG_PWRPOR)               : VDD power domain power-on reset flag has been set.
 *   - 0x0002 (PWRCU_FLAG_PD)                   : Power-Down flag has been set.
 *   - 0x0010 (PWRCU_FLAG_POR)                  : Power-on reset flag has been set.
 *   - 0x0100 (PWRCU_FLAG_WUP0)                 : External WAKEUP0 pin flag has been set.
 *   - 0x0200 (PWRCU_FLAG_WUP1)                 : External WAKEUP1 pin flag has been set.
 ************************************************************************************************************/
u16 PWRCU_GetFlagStatus(void)
{
  return HT_PWRCU->SR;
}

#if (LIBCFG_BAKREG)
/*********************************************************************************************************//**
 * @brief Return the value of specified backup register.
 * @param BAKREGx: Number of backup register. Where x can be 0 ~ 9.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BAKREG(BAKREGx));

  return HT_PWRCU->BAKREG[BAKREGx];
}

/*********************************************************************************************************//**
 * @brief Write the DATA to specified backup register.
 * @param BAKREGx : Number of backup registers. Where x can be 0 ~ 9.
 * @param DATA : Must between 0x0 ~ 0xFFFFFFFF.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BAKREG(BAKREGx));

  HT_PWRCU->BAKREG[BAKREGx] = DATA;
}
#endif

/*********************************************************************************************************//**
 * @brief Enter SLEEP mode.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register                                                  */
  SCB->SCR &= ~(u32)SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }
}

/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 1.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  Reset_DMOSON;
  Reset_LDOOFF;

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  SCB->SCR &= ~(u32)SLEEPDEEP_SET;
}

/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 2.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  if (Get_DMOSSTS == 0)
  {
    Reset_DMOSON;
    Set_DMOSON;
  }
  Reset_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  SCB->SCR &= ~(u32)SLEEPDEEP_SET;
}

#if !defined(USE_HT32F52220_30)
/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 2.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep2Ex(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  u32 uBackUp[4];

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;
  uBackUp[0] = HT_RTC->CMP;
  uBackUp[1] = HT_RTC->IWEN;
  uBackUp[2] = HT_RTC->CR;
  uBackUp[3] = HT_EXTI->WAKUPCR;

  Set_DMOSON;
  Reset_LDOOFF;

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  if (HT_EXTI->WAKUPFLG)
  {
    HT_EXTI->WAKUPCR &= ~(0xFFFF);
    HT_EXTI->WAKUPFLG = 0xFFFF;
    HT_RTC->CR &= (~1UL);
    HT_RTC->CMP = 1;
    HT_RTC->IWEN = (1 << 9);
    HT_RTC->CR = (1 << 4) | (1 << 2) | (1 << 0);
    __SEV();
    __WFE();
    __WFE();
    HT_RTC->CR &= (~1UL);
    rw((u32)&HT_RTC->SR);

    HT_RTC->CMP = uBackUp[0];
    HT_RTC->IWEN = uBackUp[1];
    HT_RTC->CR = uBackUp[2];
    HT_EXTI->WAKUPCR = uBackUp[3];
  }

  SCB->SCR &= ~(u32)SLEEPDEEP_SET;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }
}
#endif

#if (!LIBCFG_PWRCU_NO_PD_MODE)
/*********************************************************************************************************//**
 * @brief Enter POWER-DOWN Mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_PowerDown(void)
{
  u32 uRTCStatus = 0;

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  #if (LIBCFG_RTC_LSI_LOAD_TRIM)
  {
    static u8 isLSITrimLoaded = FALSE;
    if (isLSITrimLoaded == FALSE)
    {
      u32 i = 4800;
      isLSITrimLoaded = TRUE;
      HT_RTC->CR &= ~(1UL << 2);
      /* Insert a delay must > 1 CK_RTC                                                                     */
      while (i--);
      HT_RTC->CR |= (1UL << 2);
      while ((HT_CKCU->GCSR & 0x20) == 0);
    }
  }
  #endif

  Reset_DMOSON;
  Set_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  /* Enters power-down mode                                                                                 */
  __SEV();
  __WFE();
  __WFE();

  {
    u32 X = (16 * 250);
    while (X--);
  }

  NVIC_SystemReset();
}
#endif

/*********************************************************************************************************//**
 * @brief Configure LVD voltage level.
 * @param Level: Low voltage detect level.
 *   This parameter can be one of the following:
 *   VDD 2.0 ~ 3.6V version:
 *     @arg PWRCU_LVDS_2V25 : 2.25 V
 *     @arg PWRCU_LVDS_2V4  : 2.40 V
 *     @arg PWRCU_LVDS_2V55 : 2.55 V
 *     @arg PWRCU_LVDS_2V7  : 2.70 V
 *     @arg PWRCU_LVDS_2V85 : 2.85 V
 *     @arg PWRCU_LVDS_3V   : 3.00 V
 *     @arg PWRCU_LVDS_3V15 : 3.15 V
 *     @arg PWRCU_LVDS_3V3  : 3.30 V
 *   VDD 1.65 ~ 3.6V version:
 *     @arg PWRCU_LVDS_1V75 : 1.75 V
 *     @arg PWRCU_LVDS_1V95 : 1.95 V
 *     @arg PWRCU_LVDS_2V15 : 2.15 V
 *     @arg PWRCU_LVDS_2V35 : 2.35 V
 *     @arg PWRCU_LVDS_2V55 : 2.55 V
 *     @arg PWRCU_LVDS_2V75 : 2.75 V
 *     @arg PWRCU_LVDS_2V95 : 2.95 V
 *     @arg PWRCU_LVDS_3V15 : 3.15 V
 *   VDD 5.0V version:
 *     @arg PWRCU_LVDS_2V65 : 2.65 V
 *     @arg PWRCU_LVDS_2V85 : 2.85 V
 *     @arg PWRCU_LVDS_3V05 : 3.05 V
 *     @arg PWRCU_LVDS_3V25 : 3.25 V
 *     @arg PWRCU_LVDS_3V45 : 3.45 V
 *     @arg PWRCU_LVDS_4V25 : 4.25 V
 *     @arg PWRCU_LVDS_4V45 : 4.45 V
 *     @arg PWRCU_LVDS_4V65 : 4.65 V
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LVDS(Level));

  HT_PWRCU->LVDCSR = (HT_PWRCU->LVDCSR & LVDS_MASK) | Level;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LVD function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDEN;
  }
  else
  {
    Reset_LVDEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable BOD reset function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_BODEN;
  }
  else
  {
    Reset_BODEN;
  }
}

/*********************************************************************************************************//**
 * @brief Select when the BOD occurs, the action for the cause Reset or Interrupt.
 * @param Selection: BOD reset or interrupt selection.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_BODRIS_RESET : Reset the whole chip
 *     @arg PWRCU_BODRIS_INT   : Assert interrupt
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BODRIS(Selection));

  if (Selection != PWRCU_BODRIS_RESET)
  {
    Set_BODRIS;
  }
  else
  {
    Reset_BODRIS;
  }
}

/*********************************************************************************************************//**
 * @brief Return the flag status of LVD.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetLVDFlagStatus(void)
{
  return (FlagStatus)Get_LVDF;
}

/*********************************************************************************************************//**
 * @brief Return the flag status of BOD.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetBODFlagStatus(void)
{
  return (FlagStatus)Get_BODF;
}

/*********************************************************************************************************//**
 * @brief Return the DMOS status.
 * @retval This function will return one of the following values:
 *    - PWRCU_DMOS_STS_ON              : DMOS on
 *    - PWRCU_DMOS_STS_OFF             : DMOS off
 *    - PWRCU_DMOS_STS_OFF_BY_BODRESET : DMOS off caused by brow out reset
 ************************************************************************************************************/
PWRCU_DMOSStatus PWRCU_GetDMOSStatus(void)
{
  u32 wDmosStatus = HT_PWRCU->CR & 0x8080;

  if (wDmosStatus == 0x0)
  {
    return PWRCU_DMOS_STS_OFF;
  }
  else if (wDmosStatus == 0x8080)
  {
    return PWRCU_DMOS_STS_ON;
  }
  else
  {
    return PWRCU_DMOS_STS_OFF_BY_BODRESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable DMOS function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DMOSCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (Get_DMOSSTS == 0)
  {
    Reset_DMOSON;
  }

  if (NewState != DISABLE)
  {
    Set_DMOSON;
  }
  else
  {
    Reset_DMOSON;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the LDO operation mode.
 * @param Sel: Specify the LDO mode.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_LDO_NORMAL     : The LDO is operated in normal current mode
 *     @arg PWRCU_LDO_LOWCURRENT : The LDO is operated in low current mode
 * @retval None
 ************************************************************************************************************/
void PWRCU_LDOConfig(PWRCU_LDOMODE_Enum Sel)
{
  u32 uRTCStatus = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LDOMODE(Sel));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  if (Sel == PWRCU_LDO_NORMAL)
  {
    Reset_LDOMODE;
  }
  else
  {
    Set_LDOMODE;
  }

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }
}

#if (LIBCFG_PWRCU_V15_READY_SOURCE)
/*********************************************************************************************************//**
 * @brief Configure VDD15 power good source.
 * @param Sel: specifies VDD15 power good source.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_V15RDYSC_V33ISO : Vdd15 power good source come from V33_ISO bit in CKCU unit
 *     @arg PWRCU_V15RDYSC_V15POR : Vdd15 power good source come from Vdd15 power-on reset
 * @retval None
 ************************************************************************************************************/
void PWRCU_V15RDYSourceConfig(PWRCU_V15RDYSC_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_V15RDYSC(Sel));

  if (Sel == PWRCU_V15RDYSC_V33ISO)
  {
    Reset_V15RDYSC;
  }
  else
  {
    Set_V15RDYSC;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable the LVD interrupt wakeup function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDIWEN;
  }
  else
  {
    Reset_LVDIWEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LVD event wakeup function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDEventWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDEWEN;
  }
  else
  {
    Reset_LVDEWEN;
  }
}

#if (LIBCFG_PWRCU_VREG)
/*********************************************************************************************************//**
 * @brief Configure the VREG output voltage.
 * @param Volt: VREG output voltage.
 *   This parameter can be one of the following:
 *     @arg PWRCU_VREG_4V0 : 4.0 V
 *     @arg PWRCU_VREG_3V3 : 3.3 V
 *     @arg PWRCU_VREG_3V0 : 3.0 V
 *     @arg PWRCU_VREG_2V5 : 2.5 V
 *     @arg PWRCU_VREG_1V8 : 1.8 V
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetVREG(PWRCU_VREG_VOLT_Enum Volt)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_VREG_VOLT(Volt));

  HT_PWRCU->CR = (HT_PWRCU->CR & VREG_V_MASK) | Volt;
}

/*********************************************************************************************************//**
 * @brief Configure the VREG operation mode.
 * @param Mode: VREG operation mode.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_VREG_DISABLE : The VREG is disabled
 *     @arg PWRCU_VREG_ENABLE  : The VREG is enabled
 *     @arg PWRCU_VREG_BYPASS  : The VREG is bypassed
 * @retval None
 ************************************************************************************************************/
void PWRCU_VREGConfig(PWRCU_VREG_MODE_Enum Mode)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_VREG_MODE(Mode));

  HT_PWRCU->CR = (HT_PWRCU->CR & VREG_M_MASK) | Mode;
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_WUP0EN;
  }
  else
  {
    Reset_WUP0EN;
  }
}

#if (LIBCFG_PWRCU_WAKEUP_V01)
/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin function.
 * @param Pin: specify the WAKEUP pin number.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WAKEUP_PIN_0 :
 *     @arg PWRCU_WAKEUP_PIN_1 :
 * @param Type: specify the WAKEUP pin type.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WUP_POSITIVE_EDGE :
 *     @arg PWRCU_WUP_NEGATIVE_EDGE :
 *     @arg PWRCU_WUP_HIGH_LEVEL    :
 *     @arg PWRCU_WUP_LOW_LEVEL     :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupMultiPinCmd(PWRCU_WUP_Enum Pin, PWRCU_WUPTYPE_Enum Type, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_WAKEUPPIN(Pin));
  Assert_Param(IS_PWRCU_TRIGGERTYPE(Type));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
    {
      HT_PWRCU->CR = (HT_PWRCU->CR & WUP0TYPE_MASK) | (Type << 16);
      Set_WUP0EN;
    }
    else
    {
      HT_PWRCU->CR = (HT_PWRCU->CR & WUP1TYPE_MASK) | (Type << 18);
      Set_WUP1EN;
    }
  }
  else
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
      Reset_WUP0EN;
    else
      Reset_WUP1EN;
  }
}
#endif

#if defined(USE_HT32F52342_52) || defined(USE_HT32F5826)
/*********************************************************************************************************//**
 * @brief Configure HSI ready counter bit length.
 * @param BitLength: HSI ready counter bit length.
 *   This parameter can be one of following:
 *     @arg PWRCU_HSIRCBL_4 : 4 bits
 *     @arg PWRCU_HSIRCBL_5 : 5 bits
 *     @arg PWRCU_HSIRCBL_6 : 6 bits
 *     @arg PWRCU_HSIRCBL_7 : 7 bits (Default)
 * @retval None
 ************************************************************************************************************/
void PWRCU_HSIReadyCounterBitLengthConfig(PWRCU_HSIRCBL_Enum BitLength)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_HSIRCBL(BitLength));

  HT_PWRCU->HSIRCR = BitLength;
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
