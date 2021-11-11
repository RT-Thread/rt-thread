/**
  ******************************************************************************
  * @file    stm32l5xx_hal_flash_ramfunc.c
  * @author  MCD Application Team
  * @brief   FLASH RAMFUNC driver.
  *          This file provides a Flash firmware functions which should be
  *          executed from internal SRAM
  *            + Option Byte DBANK Programming
  *            + FLASH Power Down in Run mode
  *
  *  @verbatim
  ==============================================================================
                   ##### Flash RAM functions #####
  ==============================================================================

    *** ARM Compiler ***
    --------------------
    [..] RAM functions are defined using the toolchain options.
         Functions that are executed in RAM should reside in a separate
         source module. Using the 'Options for File' dialog you can simply change
         the 'Code / Const' area of a module to a memory space in physical RAM.
         Available memory areas are declared in the 'Target' tab of the
         Options for Target' dialog.

    *** ICCARM Compiler ***
    -----------------------
    [..] RAM functions are defined using a specific toolchain keyword "__ramfunc".

    *** GNU Compiler ***
    --------------------
    [..] RAM functions are defined using a specific toolchain attribute
         "__attribute__((section(".RamFunc")))".

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @defgroup FLASH_RAMFUNC FLASH RAMFUNC
  * @brief FLASH functions executed from RAM
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup FLASH_RAMFUNC_Exported_Functions FLASH in RAM function Exported Functions
  * @{
  */

/** @defgroup FLASH_RAMFUNC_Exported_Functions_Group1 RAM Execution functions
 *  @brief   RAM Execution functions
 *
@verbatim
 ===============================================================================
                      ##### RAM Execution functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions that should be executed from RAM.

@endverbatim
  * @{
  */

/**
  * @brief  Enable the Power down in Run Mode
  * @note   This function should be called and executed from SRAM memory
  * @retval HAL status
  */
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_EnableRunPowerDown(void)
{
  /* Enable the Power Down in Run mode*/
  __HAL_FLASH_POWER_DOWN_ENABLE();

  return HAL_OK;
}

/**
  * @brief  Disable the Power down in Run Mode
  * @note   This function should be called and executed from SRAM memory
  * @retval HAL status
  */
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_DisableRunPowerDown(void)
{
  /* Disable the Power Down in Run mode*/
  __HAL_FLASH_POWER_DOWN_DISABLE();

  return HAL_OK;
}

/**
  * @brief  Program the FLASH DBANK User Option Byte.
  *
  * @note   To configure the user option bytes, the option lock bit OPTLOCK must
  *         be cleared with the call of the HAL_FLASH_OB_Unlock() function.
  * @note   To modify the DBANK option byte, all secure protection mechanism
  *         should be deactivated. It should be done before DBANK modification
  *         otherwise OPTWERR will be set. The secure areas should be reactived after
  *         the modifications
  *
  * @param  DBankConfig: The FLASH DBANK User Option Byte value.
  *          This parameter  can be one of the following values:
  *            @arg OB_DBANK_128_BITS: Single-bank with 128-bits data
  *            @arg OB_DBANK_64_BITS: Dual-bank with 64-bits data
  *
  * @retval HAL status
  */
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_OB_DBankConfig(uint32_t DBankConfig)
{
  uint32_t count, reg;
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Check if the Watermark-based secure area of 1st bank is deactivated */
  reg = FLASH->SECWM1R1;
  if ((reg & FLASH_SECWM1R1_SECWM1_PSTRT) > ((reg & FLASH_SECWM1R1_SECWM1_PEND) >> FLASH_SECWM1R1_SECWM1_PEND_Pos))
  {
    /* Check if the Watermark-based secure area of 2nd bank is deactivated */
    reg = FLASH->SECWM2R1;
    if ((reg & FLASH_SECWM2R1_SECWM2_PSTRT) > ((reg & FLASH_SECWM2R1_SECWM2_PEND) >> FLASH_SECWM2R1_SECWM2_PEND_Pos))
    {
#endif
      /* Disable WRP zone 1 of 1st bank if needed */
      reg = FLASH->WRP1AR;
      if ((reg & FLASH_WRP1AR_WRP1A_PSTRT) <= ((reg & FLASH_WRP1AR_WRP1A_PEND) >> FLASH_WRP1AR_WRP1A_PEND_Pos))
      {
        MODIFY_REG(FLASH->WRP1AR, (FLASH_WRP1AR_WRP1A_PSTRT | FLASH_WRP1AR_WRP1A_PEND), FLASH_WRP1AR_WRP1A_PSTRT);
      }

      /* Disable WRP zone 1 of 2nd bank if needed */
      reg = FLASH->WRP1BR;
      if ((reg & FLASH_WRP1BR_WRP1B_PSTRT) <= ((reg & FLASH_WRP1BR_WRP1B_PEND) >> FLASH_WRP1BR_WRP1B_PEND_Pos))
      {
        MODIFY_REG(FLASH->WRP1BR, (FLASH_WRP1BR_WRP1B_PSTRT | FLASH_WRP1BR_WRP1B_PEND), FLASH_WRP1BR_WRP1B_PSTRT);
      }

      /* Disable WRP zone 2 of 1st bank if needed */
      reg = FLASH->WRP2AR;
      if ((reg & FLASH_WRP2AR_WRP2A_PSTRT) <= ((reg & FLASH_WRP2AR_WRP2A_PEND) >> FLASH_WRP2AR_WRP2A_PEND_Pos))
      {
        MODIFY_REG(FLASH->WRP2AR, (FLASH_WRP2AR_WRP2A_PSTRT | FLASH_WRP2AR_WRP2A_PEND), FLASH_WRP2AR_WRP2A_PSTRT);
      }

      /* Disable WRP zone 2 of 2nd bank if needed */
      reg = FLASH->WRP2BR;
      if ((reg & FLASH_WRP2BR_WRP2B_PSTRT) <= ((reg & FLASH_WRP2BR_WRP2B_PEND) >> FLASH_WRP2BR_WRP2B_PEND_Pos))
      {
        MODIFY_REG(FLASH->WRP2BR, (FLASH_WRP2BR_WRP2B_PSTRT | FLASH_WRP2BR_WRP2B_PEND), FLASH_WRP2BR_WRP2B_PSTRT);
      }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
      /* Disable the Block-based secure area of 1st bank if needed */
      if (FLASH->SECBB1R1 != 0u)
      {
        FLASH->SECBB1R1 = 0u;
      }

      if (FLASH->SECBB1R2 != 0u)
      {
        FLASH->SECBB1R2 = 0u;
      }

      if (FLASH->SECBB1R3 != 0u)
      {
        FLASH->SECBB1R3 = 0u;
      }

      if (FLASH->SECBB1R4 != 0u)
      {
        FLASH->SECBB1R4 = 0u;
      }

      /* Disable the Block-based secure area of 2nd bank if needed */
      if (FLASH->SECBB2R1 != 0u)
      {
        FLASH->SECBB2R1 = 0u;
      }

      if (FLASH->SECBB2R2 != 0u)
      {
        FLASH->SECBB2R2 = 0u;
      }

      if (FLASH->SECBB2R3 != 0u)
      {
        FLASH->SECBB2R3 = 0u;
      }

      if (FLASH->SECBB2R4 != 0u)
      {
        FLASH->SECBB2R4 = 0u;
      }
#endif

      /* Modify the DBANK user option byte */
      MODIFY_REG(FLASH->OPTR, FLASH_OPTR_DBANK, DBankConfig);

      /* Set OPTSTRT Bit */
      SET_BIT(FLASH->NSCR, FLASH_NSCR_OPTSTRT);

      /* Wait for last operation to be completed */
      /* 8 is the number of required instruction cycles for the below loop statement (timeout expressed in ms) */
      count = FLASH_TIMEOUT_VALUE * (SystemCoreClock / 8U / 1000U);
      do
      {
        if (count == 0U)
        {
          break;
        }
        count--;
      } while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != 0U);

      /* If the option byte program operation is completed, disable the OPTSTRT Bit */
      CLEAR_BIT(FLASH->NSCR, FLASH_NSCR_OPTSTRT);

      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);

      if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTWERR) == 0U)
      {
        /* Set the bit to force the option byte reloading */
        SET_BIT(FLASH->NSCR, FLASH_NSCR_OBL_LAUNCH);
      }
      else
      {
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTWERR);
        pFlash.ErrorCode |= FLASH_FLAG_OPTWERR;        
      }
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    }
  }
#endif
  return status;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
