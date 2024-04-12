/**************************************************************************//**
 * @file    library/Device/Holtek/HT32F5xxxx/Source/system_ht32f5xxxx_03.c
 * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Source File
 *          for the Holtek HT32F5xxxx Device Series
 * @version $Rev:: 7370         $
 * @date    $Date:: 2023-12-06 #$
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
//   HT32F0008
//   HT32F52142
//   HT32F52344, HT32F52354
//   HT32F52357, HT32F52367
//   HT32F65230, HT32F65240
//   HT50F3200T

//#define USE_HT32F0008
//#define USE_HT32F52142
//#define USE_HT32F52344_54
//#define USE_HT32F52357_67
//#define USE_HT32F65230_40
//#define USE_HT50F3200T

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
//    <e3> Enable Low Speed External Crystal Oscillator (LSE)
//          <i> Default LSE = DISABLE
//       <q4> Enable Waiting LSE Clock Ready
//                <i> Default Waiting LSE Clock Ready = ENABLE
//    </e>
//
//    <e5> Enable PLL
//                <i> Default PLL = DISABLE
//                <i> PLL Out = (((HSE or HSI) / SRC_DIV) x NF2 ) / NO2
//        <o6>  PLL Clock Source
//                <0=> CK_HSE
//                <1=> CK_HSI
//                <i> Default PLL clock source = CK_HSI
//                <i> PLL source clock must be in the range of 4 MHz to 16 MHz
//        <o7>  PLL Clock Source Divider (SRC_DIV)
//                <0=> 1
//                <1=> 2
//                <i> PLL input clock = PLL Clock Source / (SRC_DIV)
//        <o8>  PLL Feedback Clock Divider (NF2): 1 ~ 16
//                <1-16:1>
//                <i> PLL feedback clock = PLL input clock x NF2
//                <i> PLL feedback clock must be in the range of 24 MHz to 60 MHz
//        <o9>  PLL Output Clock Divider (NO2)
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <i> PLL output clock = PLL feedback clock / NO2
//                <i> PLL output clock must be in the range of 4 MHz to 60 MHz
//    </e>
//
//    <h> SystemCoreClock Configuration (CK_AHB)
//      <o10>    SystemCoreClock Source
//                <1=> CK_PLL
//                <2=> CK_HSE
//                <3=> CK_HSI
//                <6=> CK_LSE
//                <7=> CK_LSI
//                <i> Default SystemCoreClock source = CK_HSI
//      <o11>   SystemCoreClock Source Divider
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <4=> 16
//                <5=> 32
//                <i> Default SystemCoreClock source divider = 1
//    </h>
//
//    <h> FLASH Configuration
//      <o12>   Wait state
//                <0=> 0 WS
//                <1=> 1 WS
//                <2=> 2 WS
//                <9=> AUTO
//                <i>   0 WS:  1 kHz <= CK_AHB <= 20 MHz
//                <i>   1 WS: 20 MHz <  CK_AHB <= 40 MHz
//                <i>   2 WS: 40 MHz <  CK_AHB <= 60 MHz
//      <q13>   Pre-fetch Buffer Enable
//                <i> Default pre-fetch buffer = ENABLE
//      <q14>   Branch cache Enable (HT32F52357/67, HT32F65230/40, HT50F3200T Only)
//                <i> Default branch cache = ENABLE
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
#define LSE_WAIT_READY    (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define PLL_ENABLE        (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define PLL_CLK_SRC       (0)     /*!< 0: HSE,      1: HSI                                                  */
#define PLL_CLK_SRC_DIV   (1)     /*!< 0: DIV1,     1: DIV2                                                 */
#define PLL_NF2_DIV       (15)    /*!< 1~16: DIV1~DIV16                                                     */
#define PLL_NO2_DIV       (0)     /*!< 0: DIV1,     1: DIV2,   2: DIV4,   3: DIV8                           */
#define HCLK_SRC          (1)     /*!< 0: PLL,      1: PLL,    2: HSE,    3: HSI     6: LSE,    7: LSI      */
#define HCLK_DIV          (0)     /*!< 0: DIV1,     1: DIV2,   2: DIV4,   3: DIV8,   4: DIV16,  5: DIV32    */
#define WAIT_STATE        (9)     /*!< 0: WS = 0,   1: WS = 1, 2: WS = 2,            9: AUTO                */
#define PRE_FETCH_ENABLE  (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define BCACHE_ENABLE     (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define DEINIT_ENABLE     (1)     /* Set 0 for reduce code size                                             */

/*----------------------------------------------------------------------------------------------------------*/
/* PLL Out = (((HSE or HSI) / (PLL_CLK_SRC_DIV + 1)) x PLL_NF2) / PLL_NO2                                   */
/*----------------------------------------------------------------------------------------------------------*/


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
#if (HSI_VALUE != 8000000UL)
  #error "CK_HSI clock issue: must be 8 MHz!"
#endif

/**
 * @brief Check HSE frequency
 */
#if ((HSE_VALUE < 4000000UL) || (HSE_VALUE > 16000000UL))
  #error "CK_HSE clock issue: must be in the range of 4 MHz to 16 MHz!"
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
 * @brief CK_PLL definition
 */
#if (PLL_ENABLE == 1)
  /* Get CK_VCO frequency                                                                                   */
  #if (PLL_CLK_SRC == 1)
    #if (HSI_ENABLE == 0)
      #error "CK_PLL clock source issue: HSI has not been enabled"
    #else
      #define __CK_VCO    ((HSI_VALUE >> PLL_CLK_SRC_DIV) * PLL_NF2_DIV)   /*!< Select HSI as PLL source    */
    #endif
  #else
    #if (HSE_ENABLE == 0)
      #error "CK_PLL clock source issue: HSE has not been enabled!"
    #else
      #define __CK_VCO    ((HSE_VALUE >> PLL_CLK_SRC_DIV) * PLL_NF2_DIV)  /*!< Select HSE as PLL source     */
    #endif
  #endif

  #define VCO_MIN 24000000UL
  #define VCO_MAX 60000000UL
  #define PLL_MIN  4000000UL
  #define PLL_MAX 60000000UL

  /* Check CK_VCO frequency                                                                                 */
  #if ((__CK_VCO < VCO_MIN) || (__CK_VCO > VCO_MAX))
    #error "CK_VCO clock issue: must be in the range!"
  #endif

  #define __CK_PLL    (__CK_VCO >> PLL_NO2_DIV)                 /*!< Get CK_PLL frequency                   */

  /* Check CK_PLL frequency                                                                                 */
  #if ((__CK_PLL < PLL_MIN) || (__CK_PLL > PLL_MAX))
    #error "CK_PLL clock issue: must be in the range!"
  #endif
#endif

/**
 * @brief CK_SYS definition
 */
#if (HCLK_SRC == 1)
  #if (PLL_ENABLE == 1)
    #define __CK_SYS    __CK_PLL              /*!< Select PLL as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: PLL is not enable!"
  #endif
#elif (HCLK_SRC == 2)
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
#define CKAHB_MAX 60000000UL
#define WS0_CLK   20000000UL
#define WS1_CLK   40000000UL

/* Check CK_AHB frequency                                                                                   */
#if ((__CK_AHB < CKAHB_MIN) || (__CK_AHB > CKAHB_MAX))
  #error "CK_AHB clock issue: must be in the range!"
#endif

/* Check FLASH wait-state setting                                                                           */
#if ((__CK_AHB > WS1_CLK) && (WAIT_STATE < 2) || \
     (__CK_AHB > WS0_CLK) && (WAIT_STATE < 1))
  #error "FLASH wait state configuration issue!"
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

  SetBit_BB((u32)(&HT_CKCU->APBCCR1), 6);                       /* enable Backup domain register clock      */
  while (HT_PWRCU->TEST != 0x27);                               /* wait for Backup domain register ready    */

  #if (DEINIT_ENABLE == 1)
  /* De-init the setting                                                                                    */
  HT_CKCU->AHBCCR &= ~(0x3 << 10);                              /* disable IP who may use PLL as source     */
  SetBit_BB((u32)(&HT_CKCU->GCCR), 11);                         /* enable HSI                               */
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 3));                 /* wait for HSI ready                       */
  HT_CKCU->GCCR = ((HT_CKCU->GCCR & ~7UL) | 3UL);               /* select CK_SYS source                     */
  while ((HT_CKCU->CKST & 7UL) != 3UL);                         /* wait for clock switch complete           */
  HT_FLASH->CFCR = (((HT_FLASH->CFCR) & ~7UL) | 1UL);           /* set Wait State as 0 WS                   */
  HT_CKCU->AHBCFGR = 0;                                         /* set CK_AHB prescaler                     */
  ResetBit_BB((u32)(&HT_CKCU->GCCR), 9);                        /* disable PLL                              */
  SetBit_BB((u32)(&HT_CKCU->GCFGR), 8);                         /* select PLL source as HSI                 */
  #ifndef USE_HT32F65230_40
  ResetBit_BB((u32)(&HT_CKCU->GCCR), 3);                        /* disable USB PLL                          */
  SetBit_BB((u32)(&HT_CKCU->GCFGR), 9);                         /* select USB PLL source as HSI             */
  #endif
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
  #if (LSE_WAIT_READY == 1)
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 4));                 /* wait for LSE ready                       */
  #endif
#endif

  ResetBit_BB((u32)(&HT_CKCU->APBCCR1), 6);                     /* disable Backup domain register clock     */

  /* LSI initiation                                                                                         */
#if (HCLK_SRC == 7)
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 5)){};               /* wait for LSI ready                       */
#endif

  /* PLL initiation                                                                                         */
#if (PLL_ENABLE == 1)
  HT_CKCU->PLLCFGR = ((PLL_NF2_DIV & 0x0F) << 23) | (PLL_NO2_DIV << 21);  /* set PLL divider                */

  #if (PLL_CLK_SRC_DIV == 1)
    SetBit_BB((u32)(&HT_CKCU->PLLCFGR), 28);                    /* set PLL clock source divider             */
  #else
    ResetBit_BB((u32)(&HT_CKCU->PLLCFGR), 28);                  /* reset PLL clock source divider           */
  #endif

  #if (PLL_CLK_SRC == 0)
    ResetBit_BB((u32)(&HT_CKCU->GCFGR), 8);                     /* select PLL source as HSE                 */
  #else
    SetBit_BB((u32)(&HT_CKCU->GCFGR), 8);                       /* select PLL source as HSI                 */
  #endif

  SetBit_BB((u32)(&HT_CKCU->GCCR), 9);                          /* enable PLL                               */
  while (!GetBit_BB((u32)(&HT_CKCU->GCSR), 1)){};               /* wait for PLL ready                       */
#endif

  /* CK_AHB initiation                                                                                      */
#if (WAIT_STATE == 9)
  #if (__CK_AHB > WS1_CLK)
    HT_FLASH->CFCR = (((HT_FLASH->CFCR) & ~7UL) | 3UL);         /* auto-select wait state                   */
  #elif (__CK_AHB > WS0_CLK)
    HT_FLASH->CFCR = (((HT_FLASH->CFCR) & ~7UL) | 2UL);         /* auto-select wait state                   */
  #endif
#else
  HT_FLASH->CFCR = (((HT_FLASH->CFCR) & ~7UL) | (WAIT_STATE + 1));        /* manual wait state              */
#endif

  HT_CKCU->AHBCFGR = HCLK_DIV;                                  /* set CK_AHB prescaler                     */
  HT_CKCU->GCCR = ((HT_CKCU->GCCR & ~7UL) | HCLK_SRC);          /* select CK_SYS source                     */
  while ((HT_CKCU->CKST & 7UL) != HCLK_SRC);                    /* wait for clock switch complete           */

  /* Pre-fetch buffer configuration                                                                         */
#if (PRE_FETCH_ENABLE == 0)
  ResetBit_BB((u32)(&HT_FLASH->CFCR), 4);               /* 0: pre-fetch disable, 1: pre-fetch enable        */
#else
  SetBit_BB((u32)(&HT_FLASH->CFCR), 4);                 /* 0: pre-fetch disable, 1: pre-fetch enable        */
#endif

  /* Branch cache configuration                                                                             */
#if defined(USE_HT32F52357_67) || defined(USE_HT32F65230_40)
#if (BCACHE_ENABLE == 0)
  ResetBit_BB((u32)(&HT_FLASH->CFCR), 12);              /* 0: branch cache disable, 1: branch cache enable  */
#else
  SetBit_BB((u32)(&HT_FLASH->CFCR), 12);                /* 0: branch cache disable, 1: branch cache enable  */
#endif
#endif

  /* HSE power down                                                                                         */
#if ((HSE_ENABLE == 0) && (HCLK_SRC != 2) && ((PLL_ENABLE == 0) || (PLL_CLK_SRC == 1)))
  ResetBit_BB((u32)(&HT_CKCU->GCCR), 10);
#endif

  /* HSI power down                                                                                         */
#if ((HSI_ENABLE == 0) && (HCLK_SRC != 3) && ((PLL_ENABLE == 0) || (PLL_CLK_SRC == 0)))
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
  u32 PllSourceClockDiv = (HT_CKCU->PLLCFGR >> 28) & 1UL;
  u32 PllFeedbackClockDiv = (((HT_CKCU->PLLCFGR >> 23) & 15UL) == 0) ? (16) : ((HT_CKCU->PLLCFGR >> 23) & 15UL);
  u32 PllOutputClockDiv = (HT_CKCU->PLLCFGR >> 21) & 3UL;
  u32 SystemCoreClockSrc = HT_CKCU->CKST & 7UL;

  /* Get system core clock according to global clock control & configuration registers                      */
  if (SystemCoreClockSrc == 1)
  {
    if (GetBit_BB((u32)(&HT_CKCU->PLLCR), 31))
    {
      PllFeedbackClockDiv = 1;
      PllOutputClockDiv = 0;
    }

    if (GetBit_BB((u32)(&HT_CKCU->GCFGR), 8))
    {
      SystemCoreClock = (((HSI_VALUE >> PllSourceClockDiv) * PllFeedbackClockDiv) >> PllOutputClockDiv) >> SystemCoreClockDiv;
    }
    else
    {
      SystemCoreClock = (((HSE_VALUE >> PllSourceClockDiv) * PllFeedbackClockDiv) >> PllOutputClockDiv) >> SystemCoreClockDiv;
    }
  }
  else if (SystemCoreClockSrc == 2)
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
