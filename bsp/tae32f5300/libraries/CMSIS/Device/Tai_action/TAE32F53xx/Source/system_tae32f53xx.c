/**
  ******************************************************************************
  * @file    system_tae32f53xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  *
  *
  * 1.  This file provides two functions and one global variable to be called from
  *     user application:
  *      - SystemInit(): Setups the system interrupt vector.
  *                      This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_tae32f53xx.c" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the LSI (32 KHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_tae32f53xx.c" file, to
  *    configure the system clock before to branch to main program.
  *
  * 3. The default value of HSE crystal is set to 8 MHz, refer to "HSE_VALUE".
  *    When HSE is used as system clock source, directly or through PLL, and you
  *    are using different crystal you have to adapt the HSE value to your own
  *    configuration.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx.h"


/** @addtogroup TAE_CMSIS
  * @{
  */

/** @defgroup TAE32F53xx_System TAE32F53xx System
  * @brief    TAE32F53xx System
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup TAE32F53xx_System_Private_Variables TAE32F53xx System Private Variables
  * @brief    TAE32F53xx System Private Variables
  * @{
  */

/**
  * @brief Import the Interrupt Vector Table
  */
extern void (* const __VECTOR_TABLE[])(void) ;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/** @defgroup TAE32F53xx_System_Exported_Variables TAE32F53xx System Exported Variables
  * @brief    TAE32F53xx System Exported Variables
  * @{
  */

/**
  * @brief SYSCLK System Clock Frequency (Core Clock), default value 32K.
  * @note  This variable is updated by calling SystemCoreClockUpdate()
  */
uint32_t SystemCoreClock = 32000UL;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TAE32F53xx_System_Exported_Functions TAE32F53xx System Exported Functions
  * @brief    TAE32F53xx System Exported Functions
  * @{
  */

/**
  * @brief  Initialize the Interrupt Vector.
  * @note   This function should be used only after reset.
  * @param  None
  * @return None
  */
void SystemInit(void)
{
    //Interrupt Vector Config
    SCB->VTOR = (uint32_t)__VECTOR_TABLE;
}

/**
  * @brief  Update SystemCoreClock variable
  * @note   Each time the system core clock changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  * @note   The system frequency update by this function is not the real
  *         frequency in the chip.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(uint32_t sysclk)
{
    if (sysclk) {
        SystemCoreClock = sysclk;
    }
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

