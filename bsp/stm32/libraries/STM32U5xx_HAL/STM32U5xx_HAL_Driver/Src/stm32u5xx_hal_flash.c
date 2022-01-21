/**
  ******************************************************************************
  * @file    stm32u5xx_hal_flash.c
  * @author  MCD Application Team
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the internal FLASH memory:
  *           + Program operations functions
  *           + Memory Control functions
  *           + Peripheral Errors functions
  *
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
 @verbatim
  ==============================================================================
                        ##### FLASH peripheral features #####
  ==============================================================================

  [..] The Flash memory interface manages CPU AHB C-Bus accesses to the Flash memory.
       It implements the erase and program Flash memory operations and the read
     and write protection mechanisms.

  [..] The Flash memory interface implements the TrustZone security features (TZ) supported
       by ARM Cortex-M33 core (CM33).

  [..] The FLASH main features are:
      (+) Flash memory read operations
      (+) Flash memory program/erase operations
      (+) Read / write protections
      (+) Option bytes programming
    (+) TrustZone aware
    (+) Watermark-based area protection including the secure hide area
    (+) Block-based page protection
      (+) Error code correction (ECC) : Data in flash are 137-bits word
          (9 bits added per quad-word)

                        ##### How to use this driver #####
 ==============================================================================
    [..]
      This driver provides functions and macros to configure and program the FLASH
      memory of all STM32U5xx devices.

      (#) Flash Memory IO Programming functions:
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and
                HAL_FLASH_Lock() functions
           (++) Program functions: quad-words and burst program (8 quad-words)
           (++) There are two modes of programming :
            (+++) Polling mode using HAL_FLASH_Program() function
            (+++) Interrupt mode using HAL_FLASH_Program_IT() function

      (#) Interrupts and flags management functions :
           (++) Handle FLASH interrupts by calling HAL_FLASH_IRQHandler()
           (++) Callback functions are called when the flash operations are finished :
                HAL_FLASH_EndOfOperationCallback() when everything is ok, otherwise
                HAL_FLASH_OperationErrorCallback()
           (++) Get error flag status by calling HAL_GetError()

      (#) Option bytes management functions :
           (++) Lock and Unlock the option bytes using HAL_FLASH_OB_Unlock() and
                HAL_FLASH_OB_Lock() functions
           (++) Launch the reload of the option bytes using HAL_FLASH_Launch() function.
                In this case, a reset is generated

    [..]
      In addition to these functions, this driver includes a set of macros allowing
      to handle the following operations:
       (+) Set the latency
       (+) Enable/Disable the Flash power-down during low-power run and sleep modes
       (+) Enable/Disable the Flash interrupts
       (+) Monitor the Flash flags status

 @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */
/**
  * @brief  Variable used for Program/Erase sectors under interruption
  */
FLASH_ProcessTypeDef pFlash = {.Lock = HAL_UNLOCKED, \
                               .ErrorCode = HAL_FLASH_ERROR_NONE, \
                               .ProcedureOnGoing = 0U, \
                               .Address = 0U, \
                               .Bank = FLASH_BANK_1, \
                               .Page = 0U, \
                               .NbPagesToErase = 0U
                              };
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
static void          FLASH_Program_QuadWord(uint32_t Address, uint32_t DataAddress);
static void          FLASH_Program_Burst(uint32_t Address, uint32_t DataAddress);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_Exported_Functions_Group1 Programming operation functions
  *  @brief   Programming operation functions
  *
@verbatim
 ===============================================================================
                  ##### Programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the FLASH
    program operations.

@endverbatim
  * @{
  */

/**
  * @brief  Program a quad-word or a burst of 8 quad-words at a specified address.
  * @param  TypeProgram  Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address  specifies the address to be programmed.
  *         This parameter shall be aligned to the Flash word (128 bits)
  * @param  DataAddress specifies the address of data to be programmed.
  *         This parameter shall be 32-bit aligned
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress)
{
  HAL_StatusTypeDef status;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Set current operation type */
    pFlash.ProcedureOnGoing = TypeProgram;

    /* Access to SECCR or NSCR depends on operation type */
    reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

    if ((TypeProgram & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEPROGRAM_QUADWORD)
    {
      /* Program a quad-word (128-bit) at a specified address */
      FLASH_Program_QuadWord(Address, DataAddress);
    }
    else
    {
      /* Program a burst of 8 quad-words at a specified address */
      FLASH_Program_Burst(Address, DataAddress);
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

    /* If the program operation is completed, disable the PG (and BWR Bit in Burst programming mode) */
    CLEAR_BIT((*reg_cr), (TypeProgram & ~(FLASH_NON_SECURE_MASK)));
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}

/**
  * @brief  Program a quad-word or a burst of 8 quad-words at a specified address with interrupt enabled.
  * @param  TypeProgram  Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address  specifies the address to be programmed.
  *         This parameter shall be aligned to the Flash word (128 bits)
  * @param  DataAddress specifies the address of data to be programmed.
  *         This parameter shall be 32-bit aligned
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress)
{
  HAL_StatusTypeDef status;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else
  {
    /* Set internal variables used by the IRQ handler */
    pFlash.ProcedureOnGoing = TypeProgram;
    pFlash.Address = Address;

    /* Access to SECCR or NSCR depends on operation type */
    reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

    /* Enable End of Operation and Error interrupts */
    (*reg_cr) |= (FLASH_IT_EOP | FLASH_IT_OPERR);

    if ((TypeProgram & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEPROGRAM_QUADWORD)
    {
      /* Program a quad-word (128-bit) at a specified address */
      FLASH_Program_QuadWord(Address, DataAddress);
    }
    else
    {
      /* Program a burst of 8 quad-words at a specified address */
      FLASH_Program_Burst(Address, DataAddress);
    }
  }

  return status;
}

/**
  * @brief  Handle FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t param = 0U;
  uint32_t error;
  __IO uint32_t *reg_cr;
  __IO uint32_t *reg_sr;

  /* Access to CR and SR registers depends on operation type */
  reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);
  reg_sr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECSR) : &(FLASH_NS->NSSR);

  /* Save Flash errors */
  error = (*reg_sr) & FLASH_FLAG_SR_ERRORS;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  error |= (FLASH->NSSR & FLASH_FLAG_OPTWERR);
#endif /* __ARM_FEATURE_CMSE */

  /* Set parameter of the callback */
  if ((pFlash.ProcedureOnGoing & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_PAGES)
  {
    param = pFlash.Page;
  }
  else if ((pFlash.ProcedureOnGoing & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_MASSERASE)
  {
    param = pFlash.Bank;
  }
  else if ((pFlash.ProcedureOnGoing & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEPROGRAM_QUADWORD)
  {
    param = pFlash.Address;
  }
  else if ((pFlash.ProcedureOnGoing & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEPROGRAM_BURST)
  {
    param = pFlash.Address;
  }
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }

  /* Clear operation bit on the on-going procedure */
  CLEAR_BIT((*reg_cr), (pFlash.ProcedureOnGoing & ~(FLASH_NON_SECURE_MASK)));

  /* Check FLASH operation error flags */
  if (error != 0U)
  {
    /* Save the error code */
    pFlash.ErrorCode |= error;

    /* Clear error programming flags */
    (*reg_sr) = error;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    if ((error & FLASH_FLAG_OPTWERR) != 0U)
    {
      FLASH->NSSR = FLASH_FLAG_OPTWERR;
    }
#endif /* __ARM_FEATURE_CMSE */

    /* Stop the procedure ongoing */
    pFlash.ProcedureOnGoing = 0U;

    /* FLASH error interrupt user callback */
    HAL_FLASH_OperationErrorCallback(param);
  }

  /* Check FLASH End of Operation flag  */
  if (((*reg_sr) & FLASH_FLAG_EOP) != 0U)
  {
    /* Clear FLASH End of Operation pending bit */
    (*reg_sr) = FLASH_FLAG_EOP;

    if ((pFlash.ProcedureOnGoing & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_PAGES)
    {
      /* Nb of pages to erase can be decreased */
      pFlash.NbPagesToErase--;

      /* Check if there are still pages to erase */
      if (pFlash.NbPagesToErase != 0U)
      {
        /* Increment page number */
        pFlash.Page++;
        FLASH_PageErase(pFlash.Page, pFlash.Bank);
      }
      else
      {
        /* No more pages to Erase */
        pFlash.ProcedureOnGoing = 0U;
        param = 0xFFFFFFFFU;
      }
    }
    else
    {
      /*Clear the procedure ongoing*/
      pFlash.ProcedureOnGoing = 0U;
    }

    /* FLASH EOP interrupt user callback */
    HAL_FLASH_EndOfOperationCallback(param);
  }

  if (pFlash.ProcedureOnGoing == 0U)
  {
    /* Disable End of Operation and Error interrupts */
    (*reg_cr) &= ~(FLASH_IT_EOP | FLASH_IT_OPERR);

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
}

/**
  * @brief  FLASH end of operation interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                  Mass Erase: Bank number which has been requested to erase
  *                  Page Erase: Page which has been erased
  *                    (if 0xFFFFFFFF, it means that all the selected pages have been erased)
  *                  Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASH_EndOfOperationCallback could be implemented in the user file
   */
}

/**
  * @brief  FLASH operation error interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                 Mass Erase: Bank number which has been requested to erase
  *                 Page Erase: Page number which returned an error
  *                 Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASH_OperationErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group2 Peripheral Control functions
  *  @brief   Management functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the FLASH
    memory operations.

@endverbatim
  * @{
  */

/**
  * @brief  Unlock the FLASH control register access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (READ_BIT(FLASH->NSCR, FLASH_NSCR_LOCK) != 0U)
  {
    /* Authorize the FLASH Registers access */
    WRITE_REG(FLASH->NSKEYR, FLASH_KEY1);
    WRITE_REG(FLASH->NSKEYR, FLASH_KEY2);

    /* verify Flash is unlocked */
    if (READ_BIT(FLASH->NSCR, FLASH_NSCR_LOCK) != 0U)
    {
      status = HAL_ERROR;
    }
  }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if (status == HAL_OK)
  {
    if (READ_BIT(FLASH->SECCR, FLASH_SECCR_LOCK) != 0U)
    {
      /* Authorize the FLASH Registers access */
      WRITE_REG(FLASH->SECKEYR, FLASH_KEY1);
      WRITE_REG(FLASH->SECKEYR, FLASH_KEY2);

      /* verify Flash is unlocked */
      if (READ_BIT(FLASH->SECCR, FLASH_SECCR_LOCK) != 0U)
      {
        status = HAL_ERROR;
      }
    }
  }
#endif /* __ARM_FEATURE_CMSE */

  return status;
}

/**
  * @brief  Lock the FLASH control register access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Set the LOCK Bit to lock the FLASH Registers access */
  SET_BIT(FLASH->NSCR, FLASH_NSCR_LOCK);

  /* verify Flash is locked */
  if (READ_BIT(FLASH->NSCR, FLASH_NSCR_LOCK) != 0U)
  {
    status = HAL_OK;
  }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if (status == HAL_OK)
  {
    SET_BIT(FLASH->SECCR, FLASH_SECCR_LOCK);

    /* verify Flash is locked */
    if (READ_BIT(FLASH->SECCR, FLASH_SECCR_LOCK) != 0U)
    {
      status = HAL_OK;
    }
  }
#endif /* __ARM_FEATURE_CMSE */

  return status;
}

/**
  * @brief  Unlock the FLASH Option Bytes Registers access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void)
{
  if (READ_BIT(FLASH->NSCR, FLASH_NSCR_OPTLOCK) != 0U)
  {
    /* Authorizes the Option Byte register programming */
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY1);
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY2);

    /* Verify that the Option Bytes are unlocked */
    if (READ_BIT(FLASH->NSCR, FLASH_NSCR_OPTLOCK) != 0U)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Lock the FLASH Option Bytes Registers access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void)
{
  /* Set the OPTLOCK Bit to lock the FLASH Option Byte Registers access */
  SET_BIT(FLASH->NSCR, FLASH_NSCR_OPTLOCK);

  /* Verify that the Option Bytes are locked */
  if (READ_BIT(FLASH->NSCR, FLASH_NSCR_OPTLOCK) != 0U)
  {
    return HAL_OK;
  }

  return HAL_ERROR;
}

/**
  * @brief  Launch the option byte loading.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void)
{
  /* Set the bit to force the option byte reloading */
  SET_BIT(FLASH->NSCR, FLASH_NSCR_OBL_LAUNCH);

  /* We should not reach here : Option byte launch generates Option byte reset
     so return error */
  return HAL_ERROR;
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group3 Peripheral State and Errors functions
  *  @brief   Peripheral Errors functions
  *
@verbatim
 ===============================================================================
                ##### Peripheral Errors functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time Errors of the FLASH peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Get the specific FLASH error flag.
  * @retval FLASH_ErrorCode The returned value can be:
  *            @arg HAL_FLASH_ERROR_NONE: No error set
  *            @arg HAL_FLASH_ERROR_OP: FLASH Operation error
  *            @arg HAL_FLASH_ERROR_PROG: FLASH Programming error
  *            @arg HAL_FLASH_ERROR_WRP: FLASH Write protection error
  *            @arg HAL_FLASH_ERROR_PGA: FLASH Programming alignment error
  *            @arg HAL_FLASH_ERROR_SIZ: FLASH Size error
  *            @arg HAL_FLASH_ERROR_PGS: FLASH Programming sequence error
  *            @arg HAL_FLASH_ERROR_OPTW: FLASH Option modification error
  */
uint32_t HAL_FLASH_GetError(void)
{
  return pFlash.ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @addtogroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout maximum flash operation timeout
  * @retval HAL Status
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout)
{
  /* Wait for the FLASH operation to complete by polling on BUSY and WDW flags to be reset.
     Even if the FLASH operation fails, the BUSY & WDW flags will be reset, and an error flag will be set */

  uint32_t timeout = HAL_GetTick() + Timeout;
  uint32_t error;
  __IO uint32_t *reg_sr;

  /* Access to SECSR or NSSR registers depends on operation type */
  reg_sr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECSR) : &(FLASH_NS->NSSR);

  while (((*reg_sr) & (FLASH_FLAG_BSY | FLASH_FLAG_WDW)) != 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (HAL_GetTick() >= timeout)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Check FLASH operation error flags */
  error = ((*reg_sr) & FLASH_FLAG_SR_ERRORS);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  error |= (FLASH->NSSR & FLASH_FLAG_OPTWERR);
#endif /* __ARM_FEATURE_CMSE */

  if (error != 0U)
  {
    /*Save the error code*/
    pFlash.ErrorCode |= error;

    /* Clear error programming flags */
    (*reg_sr) = error;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    if ((error & FLASH_FLAG_OPTWERR) != 0U)
    {
      FLASH->NSSR = FLASH_FLAG_OPTWERR;
    }
#endif /* __ARM_FEATURE_CMSE */

    return HAL_ERROR;
  }

  /* Check FLASH End of Operation flag  */
  if (((*reg_sr) & FLASH_FLAG_EOP) != 0U)
  {
    /* Clear FLASH End of Operation pending bit */
    (*reg_sr) = FLASH_FLAG_EOP;
  }

  /* If there is no error flag set */
  return HAL_OK;
}

/**
  * @brief  Program a quad-word (128-bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_QuadWord(uint32_t Address, uint32_t DataAddress)
{
  uint8_t index = 4;
  uint32_t *dest_addr = (uint32_t *)Address;
  uint32_t *src_addr  = (uint32_t *)DataAddress;
  uint32_t primask_bit;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Access to SECCR or NSCR registers depends on operation type */
  reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

  /* Set PG bit */
  SET_BIT((*reg_cr), FLASH_NSCR_PG);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the quad-word */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    index--;
  } while (index != 0U);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a burst of 8x quad-words at a specified address.
  * @param  Address: specifies the address to be programmed.
  * @param  DataAddress: specifies the address where the data are stored.
  * @retval None
  */
static void FLASH_Program_Burst(uint32_t Address, uint32_t DataAddress)
{
  uint8_t burst_index = FLASH_NB_WORDS_IN_BURST;
  uint32_t *dest_addr = (uint32_t *)Address;
  uint32_t *src_addr = (uint32_t *)DataAddress;
  uint32_t primask_bit;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(Address));

  /* Access to SECCR or NSCR registers depends on operation type */
  reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

  /* Set PG and BWR bits */
  SET_BIT((*reg_cr), (FLASH_NSCR_PG | FLASH_NSCR_BWR));

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the burst */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    burst_index--;
  } while (burst_index != 0U);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

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

