/**************************************************************************//**
 * @file    library/Device/Holtek/HT32F5xxxx/Source/system_ht32f5xxxx_04.c
 * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Source File
 *          for the Holtek HT32F5xxxx Device Series
 * @version $Rev:: 7119         $
 * @date    $Date:: 2023-08-15 #$
 *
 * @note
 * Copyright (C) Holtek Semiconductor Inc. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) supplies this software for Cortex-M processor-based
 * microcontrollers. This file can be freely distributed within development
 * tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

// Supported Device
// ========================================
//   HT32F50220, HT32F50230
//   HT32F50231, HT32F50241
//   HT50F32002
//   HT32F59041
//   HF5032
//   HT32F61641
//   HT32F59046
//   HT32F61041

//#define USE_HT32F50220_30
//#define USE_HT32F50231_41
//#define USE_HT50F32002
//#define USE_HT32F59041
//#define USE_HF5032
//#define USE_HT32F61641
//#define USE_HT32F59046
//#define USE_HT32F61041

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup HT32F5xxxx_system HT32F5xxxx System
  * @{
  */


#include "ht32f5xxxx_01.h"

/** @addtogroup HT32F5xxxx_System_Private_Defines
  * @{
  */
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
//    <q1> Enable High Speed External Crystal Oscillator (HSE)
//          <i> Default HSE = DISABLE
//
//    <q3> Enable Low Speed External Crystal Oscillator (LSE)
//          <i> Default LSE = DISABLE
//
//    <h> SystemCoreClock Configuration (CK_AHB)
//      <o4>    SystemCoreClock Source
//                <2=> CK_HSE
//                <3=> CK_HSI
//                <6=> CK_LSE
//                <7=> CK_LSI
//                <i> Default SystemCoreClock source = CK_HSI
//      <o5>    SystemCoreClock Source Divider
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <4=> 16
//                <5=> 32
//                <i> Default SystemCoreClock source divider = 2
//    </h>
*/

/* !!! NOTICE !!!
   HSI must keep turn on when doing the Flash operation (Erase/Program).
*/

/* !!! NOTICE !!!
 * How to adjust the value of High Speed External oscillator (HSE)?
   The default value of HSE is define by "HSE_VALUE" in "ht32fxxxxx_nn.h".
   If your board uses a different HSE speed, please add a new compiler preprocessor
   C define, "HSE_VALUE=n000000" ("n" represents n MHz) in the toolchain/IDE,
   or edit the "HSE_VALUE" in the "ht32f5xxxx_conf.h" file.
   Take Keil MDK-ARM for instance, to set HSE as 16 MHz:
   "Option of Taret -> C/C++ > Preprocessor Symbols"
      Define: USE_HT32_DRIVER, USE_HT32Fxxxxx_SK, USE_HT32Fxxxxx_xx, USE_MEM_HT32Fxxxxx, HSE_VALUE=16000000
                                                                                         ^^ Add "HSE_VALUE"
                                                                                            define as above.
*/
#define HSI_ENABLE        (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define HSE_ENABLE        (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define LSI_ENABLE        (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define LSE_ENABLE        (0)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define HCLK_SRC          (2)     /*!< 0: N/A       1: N/A     2: HSE,    3: HSI     6: LSE,    7: LSI      */
#define HCLK_DIV          (0)     /*!< 0: DIV1,     1: DIV2,   2: DIV4,   3: DIV8,   4: DIV16,  5: DIV32    */
#define DEINIT_ENABLE     (1)     /* Set 0 for reduce code size                                             */

/*--------------------- WDT Configuration ----------------------------------
//
//    <e0> Enable WDT Configuration
//      <o1> WDT Prescaler Selection
//           <0=> CK_WDT / 1
//           <1=> CK_WDT / 2
//           <2=> CK_WDT / 4
//           <3=> CK_WDT / 8
//           <4=> CK_WDT / 16
//           <5=> CK_WDT / 32
//           <6=> CK_WDT / 64
//           <7=> CK_WDT / 128
//      <o2> WDT Reload Value <1-4095:1>
//      <q3> Enable WDT Reset function
//      <o4> WDT Sleep Halt mode
//           <0=> No halt
//           <1=> Halt in DeepSleep1
//           <2=> Halt in Sleep & DeepSleep1
//   </e>
*/
#define WDT_ENABLE        (0)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define WDT_PRESCALER     (5)     /*!< 0: 1/1, 1: 1/2, 2: 1/4, 3: 1/8, 4: 1/16, 5: 1/32, 6: 1/64, 7: 1/128  */
#define WDT_RELOAD        (2000)  /*!< 0 ~ 4095, 12 bit                                                     */
#define WDT_RESET_ENABLE  (1)     /*!< 0: No Reset, 1: Reset when WDT over flow                             */
#define WDT_SLEEP_HALT    (2)     /*!< 0: No halt,  1: Halt in DeepSleep1, 2: Halt in Sleep & DeepSleep1    */

/**
 * @brief Check HSI frequency
 */
#if (HSI_VALUE != 20000000UL)
  #error "CK_HSI clock issue: must be 20 MHz!"
#endif

/**
 * @brief Check HSE frequency
 */
#if ((HSE_VALUE < 4000000UL) || (HSE_VALUE > 20000000UL))
  #error "CK_HSE clock issue: must be in the range of 4 MHz to 20 MHz!"
#endif

/**
 * @brief Check LSI frequency
 */
#if (LSI_VALUE != 32000UL)
  #error "CK_LSI clock issue: must be 32 kHz!"
#endif

/**
 * @brief Check LSE frequency
 */
#if (LSE_VALUE != 32768UL)
  #error "CK_LSE clock issue: must be 32.768 kHz!"
#endif

/**
 * @brief CK_SYS definition
 */
#if (HCLK_SRC == 2)
  #if (HSE_ENABLE == 1)
    #define __CK_SYS    HSE_VALUE             /*!< Select HSE as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: HSE is not enable!"
  #endif
#elif (HCLK_SRC == 3)
  #if (HSI_ENABLE == 1)
    #define __CK_SYS    HSI_VALUE             /*!< Select HSI as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: HSI is not enable!"
  #endif
#elif (HCLK_SRC == 6)
  #if (LSE_ENABLE == 1)
    #define __CK_SYS    LSE_VALUE             /*!< Select LSE as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: LSE is not enable!"
  #endif
#elif (HCLK_SRC == 7)
  #if (LSI_ENABLE == 1)
    #define __CK_SYS    LSI_VALUE             /*!< Select LSI as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: LSI is not enable!"
  #endif
#else
  #error "CK_SYS clock source issue: No clock source is selected!"
#endif

/**
 * @brief CK_AHB definition
 */
#define __CK_AHB    (__CK_SYS >> HCLK_DIV)    /*!< Get CK_AHB frequency                                     */

#define CKAHB_MIN 1000UL
#define CKAHB_MAX 20000000UL

/* Check CK_AHB frequency                                                                                   */
#if ((__CK_AHB < CKAHB_MIN) || (__CK_AHB > CKAHB_MAX))
  #error "CK_AHB clock issue: must be in the range!"
#endif
/**
  * @}
  */

/** @addtogroup HT32F5xxxx_System_Private_Variables
  * @{
  */
__IO uint32_t SystemCoreClock = __CK_AHB;   /*!< SystemCoreClock = CK_AHB                                   */
/**
  * @}
  */

/** @addtogroup HT32F5xxxx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initializes the system clocks and the embedded Flash.
  * @note   This function should be used after reset.
  * @retval None
  */
void SystemInit(void)
{
#if (WDT_ENABLE == 1)
  HT_CKCU->APBCCR1 |= (0x1 << 4);
  HT_WDT->PR = 0x35CA;
  HT_WDT->MR0 = 0;
  HT_WDT->MR1 = ((HT_WDT->MR1 & 0xFFF) | (WDT_PRESCALER << 12));
  HT_WDT->MR0 = WDT_RELOAD | (WDT_RESET_ENABLE << 13) | (WDT_SLEEP_HALT << 14) | (0x1 << 16);
  HT_WDT->CR = 0x5FA00001;
#else
  #if (DEINIT_ENABLE == 1)
  HT_RSTCU->APBPRST1 = (1 << 4);
  #endif
#endif

  SetBit_BB((u32)(&HT_CKCU->APBCCR1), 6);                       /* enable VDD power domain register clock   */

  #if (DEINIT_ENABLE == 1)
  /* De-init the setting                                                                                    */
  SetBit_BB((u32)(&HT_CKCU->GCCR), 11);                         /* enable HSI                               */
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 3));                 /* wait for HSI ready                       */
  HT_CKCU->GCCR = ((HT_CKCU->GCCR & ~7UL) | 3UL);               /* select CK_SYS source                     */
  while ((HT_CKCU->CKST & 7UL) != 3UL);                         /* wait for clock switch complete           */
  HT_CKCU->AHBCFGR = 1;                                         /* set CK_AHB prescaler                     */
  #endif

  /* HSE initiation                                                                                         */
#if (HSE_ENABLE == 1)
  SetBit_BB((u32)(&HT_CKCU->GCCR), 10);                         /* enable HSE                               */
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 2)){};               /* wait for HSE ready                       */
#endif

  /* LSE initiation                                                                                         */
#if (LSE_ENABLE == 1)
  do {
    SetBit_BB((u32)(&HT_RTC->CR), 3);                           /* enable LSE                               */
  } while (!GetBit_BB((u32)(&HT_RTC->CR), 3));
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 4));                 /* wait for LSE ready                       */
#endif

  ResetBit_BB((u32)(&HT_CKCU->APBCCR1), 6);                     /* disable Backup domain register clock     */

  /* LSI initiation                                                                                         */
#if (HCLK_SRC == 7)
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 5)){};               /* wait for LSI ready                       */
#endif

  HT_CKCU->AHBCFGR = HCLK_DIV;                                  /* set CK_AHB prescaler                     */
  HT_CKCU->GCCR = ((HT_CKCU->GCCR & ~7UL) | HCLK_SRC);          /* select CK_SYS source                     */
  while ((HT_CKCU->CKST & 7UL) != HCLK_SRC);                    /* wait for clock switch complete           */

  /* HSE power down                                                                                         */
#if ((HSE_ENABLE == 0) && (HCLK_SRC != 2))
  ResetBit_BB((u32)(&HT_CKCU->GCCR), 10);
#endif

  /* HSI power down                                                                                         */
#if ((HSI_ENABLE == 0) && (HCLK_SRC != 3))
  ResetBit_BB((u32)(&HT_CKCU->GCCR), 11);
#endif
}

/**
  * @brief  Update SystemCoreClock
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  u32 SystemCoreClockDiv = HT_CKCU->AHBCFGR & 7UL;
  u32 SystemCoreClockSrc = HT_CKCU->CKST & 7UL;

  /* Get system core clock according to global clock control & configuration registers                      */
  if (SystemCoreClockSrc == 2)
  {
    SystemCoreClock = HSE_VALUE >> SystemCoreClockDiv;
  }
  else if (SystemCoreClockSrc == 3)
  {
    SystemCoreClock = HSI_VALUE >> SystemCoreClockDiv;
  }
  else if (SystemCoreClockSrc == 6)
  {
    SystemCoreClock = LSE_VALUE >> SystemCoreClockDiv;
  }
  else if (SystemCoreClockSrc == 7)
  {
    SystemCoreClock = LSI_VALUE >> SystemCoreClockDiv;
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

/******************* (C) COPYRIGHT Holtek Semiconductor Inc. *****END OF FILE***                            */
