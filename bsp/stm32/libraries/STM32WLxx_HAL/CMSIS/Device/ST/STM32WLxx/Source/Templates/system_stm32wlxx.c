/**
  ******************************************************************************
  * @file    system_stm32wlxx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32wlxx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the MSI (4 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32wlxx.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                    | MSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 4000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 4000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 1
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 8
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 7
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_R                                  | 2
  *-----------------------------------------------------------------------------
  *        PLLSAI1_P                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI1_Q                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI1_R                              | NA
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Apache License, Version 2.0,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/Apache-2.0
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32WLxx_system
  * @{
  */

/** @addtogroup stm32WLxx_System_Private_Includes
  * @{
  */

#include "stm32wlxx.h"

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    (32000000UL) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (MSI_VALUE)
   #define MSI_VALUE    (4000000UL) /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    (16000000UL) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (LSI_VALUE)
 #define LSI_VALUE  (32000UL)       /*!< Value of LSI in Hz*/
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
  #define LSE_VALUE    (32768UL)    /*!< Value of LSE in Hz*/
#endif /* LSE_VALUE */

/**
  * @}
  */

/** @addtogroup STM32WLxx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WLxx_System_Private_Defines
  * @{
  */

/* Note: Following vector table addresses must be defined in line with linker
         configuration. */
/*!< Uncomment the following line if you need to relocate CPU1 CM4 and/or CPU2
     CM0+ vector table anywhere in Sram or Flash. Else vector table will be kept
     at address 0x00 which correspond to automatic remap of boot address selected */
/* #define USER_VECT_TAB_ADDRESS */
#if defined(USER_VECT_TAB_ADDRESS)
#ifdef CORE_CM0PLUS
 /*!< Uncomment this line for user vector table remap in Sram else user remap
      will be done in Flash. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   SRAM2_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x100. */
#define VECT_TAB_OFFSET         0x00008000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x100. */
#else
#define VECT_TAB_BASE_ADDRESS   FLASH_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x100. */
#define VECT_TAB_OFFSET         0x00020000U        /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x100. */
#endif
#else /* CORE_CM4 */
 /*!< Uncomment this line for user vector table remap in Sram else user remap
      will be done in Flash. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   SRAM1_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
#else
#define VECT_TAB_BASE_ADDRESS   FLASH_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
#endif
#endif
#endif

/**
  * @}
  */

/** @addtogroup STM32WLxx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WLxx_System_Private_Variables
  * @{
  */
  /* The SystemCoreClock variable is updated in three ways:
      1) from within HAL_Init()
      2) by calling CMSIS function SystemCoreClockUpdate()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  */
  uint32_t SystemCoreClock  = 4000000UL; /*CPU1: M4 on MSI clock after startup (4MHz)*/

  const uint32_t AHBPrescTable[16UL] = {1UL, 3UL, 5UL, 1UL, 1UL, 6UL, 10UL, 32UL, 2UL, 4UL, 8UL, 16UL, 64UL, 128UL, 256UL, 512UL};

  const uint32_t APBPrescTable[8UL]  = {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};

  const uint32_t MSIRangeTable[16UL] = {100000UL, 200000UL, 400000UL, 800000UL, 1000000UL, 2000000UL, \
    4000000UL, 8000000UL, 16000000UL, 24000000UL, 32000000UL, 48000000UL, 0UL, 0UL, 0UL, 0UL}; /* 0UL values are incorrect cases */
/**
  * @}
  */

/** @addtogroup STM32WLxx_System_Private_FunctionPrototypes
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32WLxx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
#if defined(USER_VECT_TAB_ADDRESS)
  /* Configure the Vector Table location add offset address ------------------*/
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET;
#endif

  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << (10UL*2UL))|(3UL << (11UL*2UL)));  /* set CP10 and CP11 Full Access */
#endif
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is MSI, SystemCoreClock will contain the MSI_VALUE(*)
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(***)
  *             or HSI_VALUE(*) or MSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (*) MSI_VALUE is a constant defined in stm32wlxx_hal.h file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSI_VALUE is a constant defined in stm32wlxx_hal_conf.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32wlxx_hal_conf.h file (default value
  *              32 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmp, msirange, pllvco, pllr, pllsource , pllm;

 /* Get MSI Range frequency--------------------------------------------------*/

   /* Get MSI Range frequency--------------------------------------------------*/
   if((RCC->CR & RCC_CR_MSIRGSEL) == 0U)
   { /* MSISRANGE from RCC_CSR applies */
     msirange = (RCC->CSR & RCC_CSR_MSISRANGE) >> 8U;
   }
   else
   { /* MSIRANGE from RCC_CR applies */
     msirange = (RCC->CR & RCC_CR_MSIRANGE) >> 4U;
   }
   /*MSI frequency range in HZ*/
   msirange = MSIRangeTable[msirange];


  /*SystemCoreClock=HAL_RCC_GetSysClockFreq();*/
  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case 0x00:   /* MSI used as system clock source */
      SystemCoreClock = msirange;
      break;

    case 0x04:  /* HSI used as system clock source */
      /* HSI used as system clock source */
        SystemCoreClock = HSI_VALUE;
      break;

    case 0x08:  /* HSE used as system clock source */
      SystemCoreClock = HSE_VALUE;
      break;

    case 0x0C: /* PLL used as system clock  source */
      /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
         SYSCLK = PLL_VCO / PLLR
         */
      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
      pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1UL ;

      switch (pllsource)
      {
        case 0x02:  /* HSI used as PLL clock source */
          pllvco = (HSI_VALUE / pllm);
          break;

        case 0x03:  /* HSE used as PLL clock source */
          pllvco = (HSE_VALUE / pllm);
          break;

        default:    /* MSI used as PLL clock source */
          pllvco = (msirange / pllm);
          break;
      }

      pllvco = pllvco * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos);
      pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) + 1UL);

      SystemCoreClock = pllvco/pllr;
      break;

    default:
      SystemCoreClock = msirange;
      break;
  }

  /* Compute HCLK clock frequency --------------------------------------------*/
#if defined(DUAL_CORE) &&  defined(CORE_CM0PLUS)
  /* Get HCLK2 prescaler */
  tmp = AHBPrescTable[((RCC->EXTCFGR & RCC_EXTCFGR_C2HPRE) >> RCC_EXTCFGR_C2HPRE_Pos)];
#else
  /* Get HCLK1 prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
#endif

  /* Core clock frequency */
  SystemCoreClock = SystemCoreClock / tmp;
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
