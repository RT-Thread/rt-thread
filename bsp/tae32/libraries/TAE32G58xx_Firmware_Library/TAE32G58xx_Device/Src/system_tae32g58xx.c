/**
  ******************************************************************************
  * @file    system_tae32g58xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Source File.
  *
  *
  * 1.  This file provides two functions and one global variable to be called from
  *     user application:
  *      - SystemInit(): Setups the system interrupt vector.
  *                      This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_tae32g58xx.c" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HSI (8 MHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_tae32g58xx.c" file, to
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
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE_CMSIS
  * @{
  */

/** @defgroup TAE32G58xx_System TAE32G58xx System
  * @brief    TAE32G58xx System
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/** @defgroup TAE32G58xx_System_Private_Variables TAE32G58xx System Private Variables
  * @brief    TAE32G58xx System Private Variables
  * @{
  */

/**
  * @brief Import the Interrupt Vector Table
  */
extern void (* const __VECTOR_TABLE[])(void) ;

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/** @defgroup TAE32G58xx_System_Exported_Variables TAE32G58xx System Exported Variables
  * @brief    TAE32G58xx System Exported Variables
  * @{
  */

/**
  * @brief SYSCLK System Clock Frequency (Core Clock), default value 8M.
  * @note  This variable is updated by calling SystemCoreClockUpdate()
  */
uint32_t SystemCoreClock = 8000000UL;

/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @defgroup TAE32G58xx_System_Exported_Functions TAE32G58xx System Exported Functions
  * @brief    TAE32G58xx System Exported Functions
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

    //VCC Low Voltage Detect Disable
    WRITE_REG((SYSCTRL)->KEYR, 0x87e4);
    CLEAR_BIT((SYSCTRL)->PLCR, SYSCTRL_PLCR_VCCLVE_Msk);
    WRITE_REG((SYSCTRL)->KEYR, SYSCTRL_KEYR_KST0_Msk);

    //FPU Unit Enable, set CP10 and CP11 Full Access
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << (10 * 2)) | (3UL << (11 * 2)));
#endif
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


/* Private Functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

