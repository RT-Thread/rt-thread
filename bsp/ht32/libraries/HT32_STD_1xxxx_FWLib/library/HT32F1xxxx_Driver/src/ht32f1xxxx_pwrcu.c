/*********************************************************************************************************//**
 * @file    ht32f1xxxx_pwrcu.c
 * @version $Rev:: 2970         $
 * @date    $Date:: 2023-10-25 #$
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
#include "ht32f1xxxx_pwrcu.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
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
#define APBCCR1_ADDR      (HT_CKCU_BASE  + 0x30)
#define BAKCR_ADDR        (HT_PWRCU_BASE + 0x04)
#define LVDCSR_ADDR       (HT_PWRCU_BASE + 0x10)

#define BB_ADCEN          BitBand(APBCCR1_ADDR, 24)
#define BB_RTCEN          BitBand(APBCCR1_ADDR, 6)

#define BB_LDOLCM         BitBand(BAKCR_ADDR, 2)
#define BB_LDOOFF         BitBand(BAKCR_ADDR, 3)
#define BB_DMOSON         BitBand(BAKCR_ADDR, 7)
#define BB_WUPEN          BitBand(BAKCR_ADDR, 8)
#define BB_WUPIEN         BitBand(BAKCR_ADDR, 9)
#define BB_VRDYSC         BitBand(BAKCR_ADDR, 12)
#define BB_DMOSSTS        BitBand(BAKCR_ADDR, 15)

#define BB_BODEN          BitBand(LVDCSR_ADDR, 0)
#define BB_BODRIS         BitBand(LVDCSR_ADDR, 1)
#define BB_BODF           BitBand(LVDCSR_ADDR, 3)
#define BB_LVDEN          BitBand(LVDCSR_ADDR, 16)
#define BB_LVDF           BitBand(LVDCSR_ADDR, 19)
#define BB_LVDIWEN        BitBand(LVDCSR_ADDR, 20)
#define BB_LVDEWEN        BitBand(LVDCSR_ADDR, 21)

#define LDOFTRM_MASK      0xFFFFFFCF
#define LVDS_MASK         0xFFB9FFFF
#define BAKRST_SET        0x1
#define BAKTEST_READY     0x27
#define TIME_OUT          48000000

#define SLEEPDEEP_SET     0x04      /*!< Cortex SLEEPDEEP bit                                               */
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize Backup domain which contains PWRCU and RTC units.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeInit(void)
{
  HT_PWRCU->CR = BAKRST_SET;
  while(HT_PWRCU->CR & 0xFFFFEFFF); /* Skip Bit 12 when wait RESET finish.                                  */
  while (HT_PWRCU->SR);             /* Waits until the BAKPORF be cleared by read                           */
}

/*********************************************************************************************************//**
 * @brief Waits, until the PWRCU can be accessed.
 * @retval PWRCU_TIMEOUT or PWRCU_OK
 ************************************************************************************************************/
PWRCU_Status PWRCU_CheckReadyAccessed(void)
{
  u32 wTimeOutCnt = TIME_OUT;

#if (!LIBCFG_NO_BACK_DOMAIN)
  /* Set the ISO control bit                                                                                */
  HT_CKCU->LPCR = 0x1;
#endif

  while (--wTimeOutCnt)
  {
    if (HT_PWRCU->TEST == BAKTEST_READY)
    {
      #if (!LIBCFG_NO_BACK_DOMAIN)
      u32 write = ~HT_PWRCU->BAKREG[9];
      u32 backup = HT_PWRCU->BAKREG[9];
      while (1)
      {
        HT_PWRCU->BAKREG[9] = write;
        if (HT_PWRCU->BAKREG[9] == write) break;
      }
      HT_PWRCU->BAKREG[9] = backup;
      #endif
      return PWRCU_OK;
    }
  }
  return PWRCU_TIMEOUT;
}

/*********************************************************************************************************//**
 * @brief Return the flags of PWRCU.
 * @retval This function will return one of the following:
 *   - 0x0000                                   : There is no flag is set.
 *   - 0x0001 (PWRCU_FLAG_PWRPOR)               : Backup domain power-on reset flag has been set.
 *   - 0x0002 (PWRCU_FLAG_PD)                   : Power-Down flag has been set.
 *   - 0x0100 (PWRCU_FLAG_WUP)                  : External WAKEUP pin flag has been set.
 *   - 0x0102 (PWRCU_FLAG_PD | PWRCU_FLAG_WUP)  : Both PDF and WUPF flags have been set.
 ************************************************************************************************************/
u16 PWRCU_GetFlagStatus(void)
{
  u32 uRTCStatus = 0;
  u32 uStatus;
  uRTCStatus = BB_RTCEN;

  BB_RTCEN = 1;

  uStatus =  HT_PWRCU->SR;
  BB_RTCEN = uRTCStatus;

  return uStatus;
}

#if (!LIBCFG_NO_BACK_DOMAIN)
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
  u32 uADCStatus = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = BB_RTCEN;
  uADCStatus = BB_ADCEN;

  BB_RTCEN = 1;
  BB_ADCEN = 0;

  BB_DMOSON = 0;
  BB_LDOOFF = 0;

  BB_RTCEN = uRTCStatus;
  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }
  BB_ADCEN = uADCStatus;
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
  u32 uADCStatus = 0;
  #if (!LIBCFG_PWRCU_LDO_LEGACY)
  u32 uLDOStatus = 0;
  #endif

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = BB_RTCEN;
  uADCStatus = BB_ADCEN;

  BB_RTCEN = 1;
  BB_ADCEN = 0;

  if (BB_DMOSSTS == 0)
  {
    BB_DMOSON = 0;
    BB_DMOSON = 1;
  }
  BB_LDOOFF = 0;

  BB_RTCEN = uRTCStatus;

  #if (!LIBCFG_PWRCU_LDO_LEGACY)
  uLDOStatus = HT_PWRCU->CR & ~LDOFTRM_MASK;
  if (uLDOStatus >= PWRCU_LDO_OFFSET_ADD3P)
  {
    CKCU_PSRCWKUPCmd(ENABLE);
  }
  #endif

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  #if (!LIBCFG_PWRCU_LDO_LEGACY)
  if (uLDOStatus >= PWRCU_LDO_OFFSET_ADD3P)
  {
    PWRCU_SetLDOFTRM((PWRCU_LDOFTRM_Enum)uLDOStatus);
    CKCU_PSRCWKUPCmd(DISABLE);

    if ((HT_CKCU->GCCR >> 9) & 1)
    {
      while (CKCU_GetClockReadyStatus(CKCU_FLAG_PLLRDY) != SET);
    }
  }
  #endif

  BB_ADCEN = uADCStatus;
}

/*********************************************************************************************************//**
 * @brief Enter POWER-DOWN Mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_PowerDown(void)
{
  u32 uRTCStatus = 0;
  u32 uADCStatus = 0;

  uRTCStatus = BB_RTCEN;
  uADCStatus = BB_ADCEN;

  BB_RTCEN = 1;
  BB_ADCEN = 0;

  #if (LIBCFG_RTC_LSI_LOAD_TRIM)
  {
    static u8 isLSITrimLoaded = FALSE;
    if (isLSITrimLoaded == FALSE)
    {
      u32 i = 9600;
      isLSITrimLoaded = TRUE;
      HT_RTC->CR &= ~(1UL << 2);
      /* Insert a delay must > 1 CK_RTC                                                                     */
      while (i--);
      HT_RTC->CR |= (1UL << 2);
      while ((HT_CKCU->GCSR & 0x20) == 0);
    }
  }
  #endif

  BB_DMOSON = 0;
  BB_LDOOFF = 1;

  BB_RTCEN = uRTCStatus;

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  /* Enters power-down mode                                                                                 */
  __WFE();

  BB_ADCEN = uADCStatus;
}

#if (LIBCFG_PWRCU_LDO_LEGACY)
#else
/*********************************************************************************************************//**
 * @brief Configure LDO output voltage fine trim.
 * @param VolOffset: LDO default output voltage offset.
 *   This parameter can be one of following:
 *     @arg PWRCU_LDO_DEFAULT      : default output voltage
 *     @arg PWRCU_LDO_OFFSET_DEC5P : default output voltage offset -5%
 *     @arg PWRCU_LDO_OFFSET_ADD3P : default output voltage offset +3%
 *     @arg PWRCU_LDO_OFFSET_ADD7P : default output voltage offset +7%
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetLDOFTRM(PWRCU_LDOFTRM_Enum VolOffset)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LDOFTRM(VolOffset));

  do {
    HT_PWRCU->CR = (HT_PWRCU->CR & LDOFTRM_MASK) | VolOffset;
  } while ((HT_PWRCU->CR & ~LDOFTRM_MASK) != VolOffset);
}
#endif

/*********************************************************************************************************//**
 * @brief Configure LVD voltage level.
 * @param Level: Low voltage detect level.
 *   This parameter can be one of the following:
 *   HT32F165x:
 *     @arg PWRCU_LVDS_2V7 : 2.7 V
 *     @arg PWRCU_LVDS_2V8 : 2.9 V
 *     @arg PWRCU_LVDS_2V9 : 2.9 V
 *     @arg PWRCU_LVDS_3V  : 3.0 V
 *     @arg PWRCU_LVDS_3V1 : 3.1 V
 *     @arg PWRCU_LVDS_3V2 : 3.2 V
 *     @arg PWRCU_LVDS_3V4 : 3.4 V
 *     @arg PWRCU_LVDS_3V5 : 3.5 V
 *   HT32F123xx:
 *     @arg PWRCU_LVDS_2V25 : 2.25 V
 *     @arg PWRCU_LVDS_2V4  : 2.40 V
 *     @arg PWRCU_LVDS_2V55 : 2.55 V
 *     @arg PWRCU_LVDS_2V7  : 2.70 V
 *     @arg PWRCU_LVDS_2V85 : 2.85 V
 *     @arg PWRCU_LVDS_3V   : 3.00 V
 *     @arg PWRCU_LVDS_3V15 : 3.15 V
 *     @arg PWRCU_LVDS_3V3  : 3.30 V
 *   HT32F12364:
 *     @arg PWRCU_LVDS_1V75 : 1.75 V
 *     @arg PWRCU_LVDS_1V95 : 1.95 V
 *     @arg PWRCU_LVDS_2V15 : 2.15 V
 *     @arg PWRCU_LVDS_2V35 : 2.35 V
 *     @arg PWRCU_LVDS_2V55 : 2.55 V
 *     @arg PWRCU_LVDS_2V75 : 2.75 V
 *     @arg PWRCU_LVDS_2V95 : 2.95 V
 *     @arg PWRCU_LVDS_3V15 : 3.15 V
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

  BB_LVDEN = NewState;
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

  BB_BODEN = NewState;
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

  BB_BODRIS = Selection;
}

/*********************************************************************************************************//**
 * @brief Return the flag status of LVD.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetLVDFlagStatus(void)
{
  return (FlagStatus)BB_LVDF;
}

/*********************************************************************************************************//**
 * @brief Return the flag status of BOD.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetBODFlagStatus(void)
{
  return (FlagStatus)BB_BODF;
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

  if (BB_DMOSSTS == 0)
  {
    BB_DMOSON = 0;
  }

  BB_DMOSON = NewState;
}

#if (LIBCFG_PWRCU_LDO_LEGACY)
#else
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
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LDOMODE(Sel));

  if (Sel == PWRCU_LDO_NORMAL)
  {
    BB_LDOLCM = 0;
  }
  else
  {
    BB_LDOLCM = 1;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Configure VDD18/VDD15 power good source.
 * @param Sel: Specify VDD18/VDD15 power good source.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_VRDYSC_BKISO : Vdd18/Vdd15 power good source come from BK_ISO bit in CKCU unit
 *     @arg PWRCU_VRDYSC_VPOR  : Vdd18/Vdd15 power good source come from Vdd18/Vdd15 power on reset
 * @retval None
 ************************************************************************************************************/
void PWRCU_VRDYSourceConfig(PWRCU_VRDYSC_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_VRDYSC(Sel));

  BB_VRDYSC = Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LVD interrupt wakeup function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  BB_LVDIWEN = NewState;
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

  BB_LVDEWEN = NewState;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinCmd(ControlStatus NewState)
{
  u32 uRTCStatus = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  uRTCStatus = BB_RTCEN;

  BB_RTCEN = 1;

  BB_WUPEN = NewState;

  BB_RTCEN = uRTCStatus;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin interrupt function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinIntConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  BB_WUPIEN = NewState;
}

#if (LIBCFG_PWRCU_HSI_READY_COUNTER)
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
