/*********************************************************************************************************//**
 * @file    ht32_cm0plus_misc.c
 * @version $Rev:: 7888         $
 * @date    $Date:: 2024-07-22 #$
 * @brief   This file provides all the miscellaneous firmware functions.
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
#include "ht32_cm0plus_misc.h"
#include "ht32_div.c"
#include "ht32_rand.c"
#ifdef HTCFG_TIME_IPSEL
#include "ht32_time.c"
#endif

/** @addtogroup HT32_Peripheral_Driver HT32 Peripheral Driver
  * @{
  */

/** @defgroup MISC MISC
  * @brief MISC driver modules
  * @{
  */


/* Private definitions -------------------------------------------------------------------------------------*/
/** @defgroup MISC_Private_Define MISC private definitions
  * @{
  */
#define AIRCR_VECTKEY_MASK    ((u32)0x05FA0000)
#define CTRL_TICKINT_SET      ((u32)0x00000002)
#define CTRL_TICKINT_RESET    ((u32)0xFFFFFFFD)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup MISC_Exported_Functions MISC exported functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  Set the vector table location and Offset.
  * @param  NVIC_VectTable: Specify if the vector table is in FLASH or RAM.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VECTTABLE_RAM
  *     @arg NVIC_VECTTABLE_FLASH
  * @param  NVIC_Offset: Vector Table base offset field.
  *   This value must be a multiple of 0x100.
  * @retval None
  ***********************************************************************************************************/
void NVIC_SetVectorTable(u32 NVIC_VectTable, u32 NVIC_Offset)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_NVIC_VECTTABLE(NVIC_VectTable));
  Assert_Param(IS_NVIC_OFFSET(NVIC_Offset));

  SCB->VTOR = NVIC_VectTable | (NVIC_Offset & (u32)0x1FFFFF80);
}

/*********************************************************************************************************//**
  * @brief  Select which low power mode to execute to the system.
  * @param  NVIC_LowPowerMode:  Specify the new low power mode to execute to the system.
  *   This parameter can be one of the following values:
  *     @arg NVIC_LOWPOWER_SEVONPEND
  *     @arg NVIC_LOWPOWER_SLEEPDEEP
  *     @arg NVIC_LOWPOWER_SLEEPONEXIT
  * @param  NewState: new state of low power condition.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void NVIC_LowPowerConfig(u8 NVIC_LowPowerMode,  ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_NVIC_LOWPOWER(NVIC_LowPowerMode));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SCB->SCR |= NVIC_LowPowerMode;
  }
  else
  {
    SCB->SCR &= (u32)(~(u32)NVIC_LowPowerMode);
  }
}

/*********************************************************************************************************//**
  * @brief  Set the pending bit for a system handler.
  * @param  SystemHandler: Specify the system handler pending bit to be set.
  *   This parameter can be one of the following values:
  *     @arg SYSTEMHANDLER_NMI
  *     @arg SYSTEMHANDLER_PSV
  *     @arg SYSTEMHANDLER_SYSTICK
  * @retval None
  ***********************************************************************************************************/
void NVIC_SetPendingSystemHandler(u32 SystemHandler)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_NVIC_SYSTEMHANDLER(SystemHandler));

  /* Set the corresponding System Handler pending bit                                                       */
  SCB->ICSR |= SystemHandler;
}

/*********************************************************************************************************//**
  * @brief  Configure the SysTick clock source.
  * @param  SysTick_ClockSource: Specify the SysTick clock source.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_SRC_STCLK  : External reference clock is selected as SysTick clock source.
  *     @arg SYSTICK_SRC_FCLK   : AHB clock is selected as SysTick clock source.
  * @retval  None
  ***********************************************************************************************************/
void SYSTICK_ClockSourceConfig(u32 SysTick_ClockSource)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SYSTICK_CLOCK_SOURCE(SysTick_ClockSource));

  if (SysTick_ClockSource == SYSTICK_SRC_FCLK)
  {
    SysTick->CTRL |= SYSTICK_SRC_FCLK;
  }
  else
  {
    SysTick->CTRL &= SYSTICK_SRC_STCLK;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick counter.
  * @param  SysTick_Counter: new state of the SysTick counter.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_COUNTER_DISABLE  : Disable counter
  *     @arg SYSTICK_COUNTER_ENABLE   : Enable counter
  *     @arg SYSTICK_COUNTER_CLEAR    : Clear counter value to 0
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_CounterCmd(u32 SysTick_Counter)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SYSTICK_COUNTER(SysTick_Counter));

  if (SysTick_Counter == SYSTICK_COUNTER_CLEAR)
  {
    SysTick->VAL = SYSTICK_COUNTER_CLEAR;
  }
  else
  {
    if (SysTick_Counter == SYSTICK_COUNTER_ENABLE)
    {
      SysTick->CTRL |= SYSTICK_COUNTER_ENABLE;
    }
    else
    {
      SysTick->CTRL &= SYSTICK_COUNTER_DISABLE;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick Interrupt.
  * @param  NewState: new state of the SysTick Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_IntConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SysTick->CTRL |= CTRL_TICKINT_SET;
  }
  else
  {
    SysTick->CTRL &= CTRL_TICKINT_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Set SysTick counter reload value.
  * @param  SysTick_Reload: SysTick reload new value.
  *   This parameter must be a number between 1 and 0xFFFFFF.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_SetReloadValue(u32 SysTick_Reload)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SYSTICK_RELOAD(SysTick_Reload));

  SysTick->LOAD = SysTick_Reload;
}

/*********************************************************************************************************//**
  * @brief  Reverse bits.
  * @param  in: Input data
  * @retval uRBIT
  ***********************************************************************************************************/
u32 RBIT(u32 in)
{
  u32 uRBIT = 0;
  s32 i;

  for (i = 31; i >=0; i--)
  {
    uRBIT |= ((in & 0x1) << i);
    in = in >> 1;
  }

  return uRBIT;
}

#if 0
// Copy the code below to the begin of the main().
// START

  #if (HTCFG_STACK_USAGE_ANALYSIS == 1)
  /* !!! NOTICE !!!
     Please update the Keil HT32 PACK and HT32 Firmware Library to the latest version to make sure the
     Stack Usage Analysis function works properly.
  */
  /*
    Set HTCFG_STACK_USAGE_ANALYSIS as 1 in the "ht32xxxxxx_conf.h" to enable Stack Usage Analysis feature.
    This feature is only applicable to the Keil MDK-ARM. Please call the "StackUsageAnalysisInit()" function
    in the begin of the "main()".
    The "StackUsageAnalysisInit()" parameter shall be the start address of the vector table.
    Under Keil Debug mode, tick "View > Watch Window > HT32 Stack Usage Analysis" to show the stack usage
    information. Those information is only valid after calling "StackUsageAnalysisInit()" function.
  */
  StackUsageAnalysisInit(0x00000000);
  #endif

// END
#endif

#if (HTCFG_STACK_USAGE_ANALYSIS == 1)
#if defined (__CC_ARM)
#define STACKLIMITADDR  0x20000010
#define STACKSTART      0x20000014
u32 _StackLimit __attribute__((at(STACKLIMITADDR)))= HT_SRAM_BASE + LIBCFG_RAM_SIZE;
u32 _StackStart __attribute__((at(STACKSTART)))= HT_SRAM_BASE;
/*********************************************************************************************************//**
  * @brief  Stack Usage Analysis Init
  * @retval None
  ***********************************************************************************************************/
__ASM void StackUsageAnalysisInit(u32 addr)
{
  extern _StackLimit;
  extern __HT_check_sp;
  extern _StackStart;
  LDR R0, [r0]
  LDR R1, =_StackLimit
  STR R0, [r1]

  LDR R0, =__HT_check_sp
  LDR R1, =_StackStart
  STR R0, [r1]
  MOV R1, SP
  LDR R2, =0xCDCDCDCD
  LDR R3, =0xABABABAB
  STR R3, [ R0 ]
  B Loop_Check
Loop
  STR R2, [ R0 ]
Loop_Check
  ADDS R0, R0, #0x04
  CMP R0, R1
  BLT Loop
  BX LR
  ALIGN
}
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define STACKLIMITADDR  "0x20000010"
#define STACKSTART      "0x20000014"
u32 _StackLimit __attribute__((section(".ARM.__at_"STACKLIMITADDR))) = HT_SRAM_BASE + LIBCFG_RAM_SIZE;
u32 _StackStart __attribute__((section(".ARM.__at_"STACKSTART))) = HT_SRAM_BASE;
/*********************************************************************************************************//**
  * @brief  Stack Usage Analysis Init
  * @retval None
  ***********************************************************************************************************/
__attribute__((noinline)) void StackUsageAnalysisInit(u32 addr)
{
  __ASM volatile ("  LDR R0, [r0]");
  __ASM volatile ("  LDR R1, =_StackLimit");
  __ASM volatile ("  STR R0, [r1]");

  __ASM volatile ("  LDR R0, =__HT_check_sp");
  __ASM volatile ("  LDR R1, =_StackStart");
  __ASM volatile ("  STR R0, [r1]");
  __ASM volatile ("  MOV R1, SP");
  __ASM volatile ("  LDR R2, =0xCDCDCDCD");
  __ASM volatile ("  LDR R3, =0xABABABAB");
  __ASM volatile ("  STR R3, [ R0 ]");
  __ASM volatile ("  B Loop_Check");
  __ASM volatile ("Loop:");
  __ASM volatile ("  STR R2, [ R0 ]");
  __ASM volatile ("Loop_Check:");
  __ASM volatile ("  ADDS R0, R0, #0x04");
  __ASM volatile ("  CMP R0, R1");
  __ASM volatile ("  BLT Loop");
  __ASM volatile ("  BX LR");
}
#endif
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
