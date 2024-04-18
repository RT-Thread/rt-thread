/*********************************************************************************************************//**
 * @file    ht32_time.c
 * @version $Rev:: 6461         $
 * @date    $Date:: 2022-11-18 #$
 * @brief   The time functions.
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
#include "ht32.h"
#include "ht32_time.h"

/*
   Tick Range: 0 ~ 2^32 / HTCFG_TIME_TICKHZ (maximum tick time)
   Interrupt Time: _HTCFG_TIME_OVERFLOW_VALUE / (HTCFG_TIME_TICKHZ * HTCFG_TIME_MULTIPLE) Second (not apply for BFTM)

  Example: 32-bit BFTM with 48 MHz Timer Clock
    HTCFG_TIME_TICKHZ = HTCFG_TIME_CLKSRC = 48000000
    Tick Range: 0 ~ 2^32 / 48000000 = 0 ~ 89.478485 Second (maximum tick time, return to 0 every 89.478485 Second)
    BFTM do not use interrupt

  Example: 16-bit SCTM with 1 us tick
    HTCFG_TIME_TICKHZ = 1000000 (Hz)
    HTCFG_TIME_MULTIPLE = 1 (1 Timer Count = 1 Tick)
    Tick Range: 0 ~ 2^32 / 1000000 = 0 ~ 4294 Second = 0 ~ 71.58 Minute (maximum tick time, return to 0 every 71.58 Minute)
    Interrupt Time: 65536 / (1000000 * 1) = 65.536 ms (Trigger interrupt every 65.536 ms)

  Example: 16-bit SCTM with 10 us tick
    HTCFG_TIME_TICKHZ = 100000 (Hz)
    HTCFG_TIME_MULTIPLE = 4 (4 Timer Count = 1 Tick)
    Tick Range: 0 ~ 2^32 / 100000 = 0 ~ 42949 Second = 0 ~ 715.82 Minute = 11.93 Hour (maximum tick time, return to 0 every 11.93 Hour)
    Interrupt Time: 65536 / (100000 * 4) = 163.84 ms (Trigger interrupt every 163.84 ms)

  Example: 16-bit GPTM with 1 ms tick
    HTCFG_TIME_TICKHZ = 1000 (Hz)
    HTCFG_TIME_MULTIPLE = 4 (4 Timer Count = 1 Tick)
    Tick Range: 0 ~ 2^32 / 1000 = 0 ~ 4294967 Second = 0 ~ 49.7 Day (maximum tick time, return to 0 every 49.7 Day)
    Interrupt Time: 65536 / (1000 * 4) = 16.384 Second (Trigger interrupt every 16.384 Second)
*/

/* Private constants ---------------------------------------------------------------------------------------*/
#define _HTCFG_TIME_CKCU_PCLK                     STRCAT2(CKCU_PCLK_, HTCFG_TIME_IPN)

#if (IS_IPN_TM(HTCFG_TIME_IPN))
// SCTM/PWM/GPTM/MCTM
#define _HTCFG_TIME_IRQn                          STRCAT2(HTCFG_TIME_IPN, _IRQn)
#define _HTCFG_TIME_IRQHandler                    STRCAT2(HTCFG_TIME_IPN, _IRQHandler)
#define _HTCFG_TIME_CLKDIV                        (HTCFG_TIME_CLKSRC / HTCFG_TIME_TICKHZ / HTCFG_TIME_MULTIPLE)
#define _HTCFG_TIME_OVERFLOW_VALUE                (65536) // 16-bit = 2^16

#if (_HTCFG_TIME_CLKDIV <= 0)
  #error "_HTCFG_TIME_CLKDIV is not correct (must >= 1)!"
#endif

#if (_HTCFG_TIME_CLKDIV > 65536)
  #error "_HTCFG_TIME_CLKDIV is not correct (must <= 65536)!"
#endif

#if ((_HTCFG_TIME_CLKDIV * HTCFG_TIME_MULTIPLE) != (HTCFG_TIME_CLKSRC / HTCFG_TIME_TICKHZ))
  #error "_HTCFG_TIME_CLKDIV is not correct (must be integer)!"
#endif
#endif

/* Private variables ---------------------------------------------------------------------------------------*/
#if (IS_IPN_TM(HTCFG_TIME_IPN))
u32 gTotalTick = 0x00000000;
u8 gIsTimeInt = FALSE;
#endif

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Time Init function.
  * @retval None
  ***********************************************************************************************************/
void Time_Init(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.HTCFG_TIME_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  #if (LIBCFG_CKCU_NO_APB_PRESCALER == 0)
  CKCU_SetPeripPrescaler(_HTCFG_TIME_CKCU_PCLK, (CKCU_APBCLKPRE_TypeDef)HTCFG_TIME_PCLK_DIV);
  #endif

  #if (IS_IPN_TM(HTCFG_TIME_IPN))

  { /* Time base configuration                                                                              */
    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = _HTCFG_TIME_CLKDIV - 1;
    TimeBaseInit.CounterReload = _HTCFG_TIME_OVERFLOW_VALUE -1;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(_HTCFG_TIME_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(_HTCFG_TIME_PORT, TM_FLAG_UEV);
  }

  /* Enable Update Event interrupt                                                                          */
  TM_IntConfig(_HTCFG_TIME_PORT, TM_INT_UEV, ENABLE);
  NVIC_EnableIRQ(_HTCFG_TIME_IRQn);

  TM_SetCounter(_HTCFG_TIME_PORT, 0x0000);
  TM_Cmd(_HTCFG_TIME_PORT, ENABLE);

  #else

  BFTM_SetCounter(_HTCFG_TIME_PORT, 0x00000000);
  BFTM_EnaCmd(_HTCFG_TIME_PORT, ENABLE);
  #endif
}

/*********************************************************************************************************//**
  * @brief  Time delay function.
  * @param  uDelayTick: Delay count based on tick.
  * @retval None
  ***********************************************************************************************************/
void Time_Delay(u32 uDelayTick)
{
  u32 uCurrent;
  u32 uStart = Time_GetTick();

  do
  {
    uCurrent = Time_GetTick();
  } while (TIME_TICKDIFF(uStart, uCurrent) < uDelayTick);
}

#if (IS_IPN_TM(HTCFG_TIME_IPN))
/*********************************************************************************************************//**
  * @brief  Gets the current time tick.
  * @retval Time Tick
  ***********************************************************************************************************/
u32 Time_GetTick(void)
{
  u32 uCount = GET_CNT();

  if (gIsTimeInt == TRUE)
  {
    gIsTimeInt = FALSE;
    uCount = GET_CNT();
    gTotalTick += (_HTCFG_TIME_OVERFLOW_VALUE / HTCFG_TIME_MULTIPLE);
  }

  return (gTotalTick + (uCount / HTCFG_TIME_MULTIPLE));
}

/*********************************************************************************************************//**
 * @brief   This function handles Timer interrupt.
 * @retval  None
 ************************************************************************************************************/
void _HTCFG_TIME_IRQHandler(void)
{
  TM_ClearFlag(_HTCFG_TIME_PORT, TM_INT_UEV);

  gIsTimeInt = TRUE;
}
#endif
