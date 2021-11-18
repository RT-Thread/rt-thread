/**
  ******************************************************************************
  * @file    system_stm32u5xx_s.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
  *          to be used in secure application when the system implements
  *          the TrustZone-M security.
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at secure startup just after reset
  *                      and before branch to secure main program.
  *                      This call is made inside the "startup_stm32u5xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *      - SECURE_SystemCoreClockUpdate(): Non-secure callable function to update
  *                                        the variable SystemCoreClock and return
  *                                        its value to the non-secure calling
  *                                        application. It must be called whenever
  *                                        the core clock is changed during program
  *                                        execution.
  *
  *   After each device reset the MSI (4 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32u5xx.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                     | MSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                              | 4000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                                | 4000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                           | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB3 Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        PLL1_SRC                                | No clock
  *-----------------------------------------------------------------------------
  *        PLL1_M                                  | 1
  *-----------------------------------------------------------------------------
  *        PLL1_N                                  | 8
  *-----------------------------------------------------------------------------
  *        PLL1_P                                  | 7
  *-----------------------------------------------------------------------------
  *        PLL1_Q                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL1_R                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL2_SRC                                | NA
  *-----------------------------------------------------------------------------
  *        PLL2_M                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL2_N                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL2_P                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL2_Q                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL2_R                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL3_SRC                                | NA
  *-----------------------------------------------------------------------------
  *        PLL3_M                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL3_N                                  | NA
  *-----------------------------------------------------------------------------
  *        PLL3_P                                  | NA
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB FS,               | Disabled
  *        SDIO and RNG clock                      |
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup STM32U5xx_system
  * @{
  */

/** @addtogroup STM32U5xx_System_Private_Includes
  * @{
  */

#include "stm32u5xx.h"
#include "partition_stm32u5xx.h"  /* Trustzone-M core secure attributes */
#include <math.h>

/**
  * @}
  */

/** @addtogroup STM32U5xx_System_Private_TypesDefinitions
  * @{
  */

#if defined ( __ICCARM__ )
#  define CMSE_NS_ENTRY __cmse_nonsecure_entry
#else
#  define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))
#endif
/**
  * @}
  */

/** @addtogroup STM32U5xx_System_Private_Defines
  * @{
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    16000000U /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (MSI_VALUE)
  #define MSI_VALUE    4000000U /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    16000000U /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00000000UL /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */
/******************************************************************************/
/**
  * @}
  */

/** @addtogroup STM32U5xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U5xx_System_Private_Variables
  * @{
  */
  /* The SystemCoreClock variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetHCLKFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
  uint32_t SystemCoreClock = 4000000U;

  const uint8_t  AHBPrescTable[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
  const uint8_t  APBPrescTable[8] =  {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};
  const uint32_t MSIRangeTable[16] = {48000000U,24000000U,16000000U,12000000U, 4000000U, 2000000U, 1500000U,\
                                      1000000U, 3072000U, 1536000U,1024000U, 768000U, 400000U, 200000U, 150000U, 100000U};
/**
  * @}
  */

/** @addtogroup STM32U5xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U5xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  /* SAU/IDAU, FPU and Interrupts secure/non-secure allocation settings */
  TZ_SAU_Setup();

  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));     /* set CP10 and CP11 Full Access */

    SCB_NS->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif

  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set MSION bit */
  RCC->CR = RCC_CR_MSISON;

  /* Reset CFGR register */
  RCC->CFGR1 = 0U;
  RCC->CFGR2 = 0U;
  RCC->CFGR3 = 0U;

  /* Reset HSEON, CSSON , HSION, PLLxON bits */
  RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON);

  /* Reset PLLCFGR register */
  RCC->PLL1CFGR = 0U;

  /* Reset HSEBYP bit */
  RCC->CR &= ~(RCC_CR_HSEBYP);

  /* Disable all interrupts */
  RCC->CIER = 0U;

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM1_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Depending on secure or non-secure compilation, the adequate RCC peripheral
  *         memory are is accessed thanks to RCC alias defined in stm32u5xxxx.h device file
  *         so either from RCC_S peripheral register mapped memory in secure or from
  *         RCC_NS peripheral register mapped memory in non-secure.
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
  *         (*) MSI_VALUE is a constant defined in stm32u5xx_hal.h file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSI_VALUE is a constant defined in stm32u5xx_hal.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32u5xx_hal.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
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
  uint32_t pllr, pllsource, pllm , tmp, pllfracen, msirange;
  float_t fracn1, pllvco;

  /* Get MSI Range frequency--------------------------------------------------*/
  if(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL) == 0U)
  {
    /* MSISRANGE from RCC_CSR applies */
    msirange = (RCC->CSR & RCC_CSR_MSISSRANGE) >> RCC_CSR_MSISSRANGE_Pos;
  }
  else
  {
    /* MSIRANGE from RCC_CR applies */
    msirange = (RCC->ICSCR1 & RCC_ICSCR1_MSISRANGE) >> RCC_ICSCR1_MSISRANGE_Pos;
  }

  /*MSI frequency range in HZ*/
  msirange = MSIRangeTable[msirange];

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR1 & RCC_CFGR1_SWS)
  {
  case 0x00:  /* MSI used as system clock source */
    SystemCoreClock = msirange;
    break;

  case 0x04:  /* HSI used as system clock source */
    SystemCoreClock = HSI_VALUE;
    break;

  case 0x08:  /* HSE used as system clock source */
    SystemCoreClock = HSE_VALUE;
    break;

  case 0x0C:  /* PLL used as system clock source */
    /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
    SYSCLK = PLL_VCO / PLLR
    */
    pllsource = (RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1SRC);
    pllm = ((RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1M)>> RCC_PLL1CFGR_PLL1M_Pos) + 1U;
    pllfracen = ((RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1FRACEN)>>RCC_PLL1CFGR_PLL1FRACEN_Pos);
    fracn1 = (float_t)(uint32_t)(pllfracen* ((RCC->PLL1FRACR & RCC_PLL1FRACR_PLL1FRACN)>> RCC_PLL1FRACR_PLL1FRACN_Pos));

      switch (pllsource)
      {
      case 0x00:  /* No clock sent to PLL*/
        pllvco = (float_t)0U;
        break;

      case 0x02:  /* HSI used as PLL clock source */
        pllvco = ((float_t)HSI_VALUE / (float_t)pllm);
        break;

      case 0x03:  /* HSE used as PLL clock source */
        pllvco = ((float_t)HSE_VALUE / (float_t)pllm);
        break;

      default:    /* MSI used as PLL clock source */
        pllvco = ((float_t)msirange / (float_t)pllm);
        break;
      }

      pllvco = pllvco * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1N) + (fracn1/(float_t)0x2000) + (float_t)1U);
      pllr = (((RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1R) >> RCC_PLL1DIVR_PLL1R_Pos) + 1U );
      SystemCoreClock = (uint32_t)((uint32_t)pllvco/pllr);
      break;

  default:
    SystemCoreClock = msirange;
    break;
  }
  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR2 & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}

/**
  * @brief  Secure Non-Secure-Callable function to return the current
  *         SystemCoreClock value after SystemCoreClock update.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @retval SystemCoreClock value (HCLK)
  */
CMSE_NS_ENTRY uint32_t SECURE_SystemCoreClockUpdate(void)
{
  SystemCoreClockUpdate();

  return SystemCoreClock;
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

