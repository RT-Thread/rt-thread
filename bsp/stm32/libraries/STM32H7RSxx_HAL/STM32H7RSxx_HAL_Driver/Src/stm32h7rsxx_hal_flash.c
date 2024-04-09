/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_flash.c
  * @author  MCD Application Team
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the internal FLASH memory:
  *           + Program operations functions
  *           + Memory Control functions
  *           + Peripheral Errors functions
  *
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
    (+) Watermark-based area protection including PCROP and secure hide area
    (+) Block-based page protection
      (+) Error code correction (ECC) : Data in flash are 137-bits word
          (9 bits added per quad-word)

                        ##### How to use this driver #####
 ==============================================================================
    [..]
      This driver provides functions and macros to configure and program the FLASH
      memory of all STM32H7RSxx devices.

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
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
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
                               .Sector = 0U, \
                               .NbSectorsToErase = 0U
                              };
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
static void FLASH_Program_Byte(uint32_t Address, uint32_t DataAddress);
static void FLASH_Program_HalfWord(uint32_t Address, uint32_t DataAddress);
static void FLASH_Program_Word(uint32_t Address, uint32_t DataAddress);
static void FLASH_Program_DoubleWord(uint32_t Address, uint32_t DataAddress);
static void FLASH_Program_QuadWord(uint32_t Address, uint32_t DataAddress);
static void FLASH_Program_OTPHalfWord(uint32_t Address, uint32_t DataAddress);
static void FLASH_Program_OTPWord(uint32_t Address, uint32_t DataAddress);
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
  * @brief  Program a data at a specified address.
  * @param  TypeProgram  Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address  specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress)
{
  HAL_StatusTypeDef status;

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
    switch (TypeProgram)
    {
      case FLASH_TYPEPROGRAM_BYTE:
        /* Program a byte (8-bit) at a specified address */
        FLASH_Program_Byte(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_HALFWORD:
        /* Program a half-word (16-bit) at a specified address */
        FLASH_Program_HalfWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_WORD:
        /* Program a word (32-bit) at a specified address */
        FLASH_Program_Word(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_DOUBLEWORD:
        /* Program a double-word (64-bit) at a specified address */
        FLASH_Program_DoubleWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_QUADWORD:
        /* Program a quad-word (128-bit) at a specified address */
        FLASH_Program_QuadWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_OTP_HALFWORD:
        /* Program a half-word (16-bit) at a OTP address */
        FLASH_Program_OTPHalfWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_OTP_WORD:
        /* Program a word (32-bit) at a OTP address */
        FLASH_Program_OTPWord(Address, DataAddress);
        break;

      default:
        status = HAL_ERROR;
        break;
    }

    if (status != HAL_ERROR)
    {
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

      /* If the program operation is completed, disable the PG (and FW Bit in non quad-word mode) */
      CLEAR_BIT(FLASH->CR, (TypeProgram & ~(FLASH_WORD_SIZE_MASK)));
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}

/**
  * @brief  Program a data at a specified address with interrupt enabled.
  * @param  TypeProgram  Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address  specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress)
{
  HAL_StatusTypeDef status;

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

    /* Enable End of Operation and Error interrupts */
    SET_BIT(FLASH->IER, (FLASH_IT_EOP | FLASH_IT_WRPERR | FLASH_IT_PGSERR | FLASH_IT_STRBERR | FLASH_IT_INCERR));

    switch (TypeProgram)
    {
      case FLASH_TYPEPROGRAM_BYTE:
        /* Program a byte (8-bit) at a specified address */
        FLASH_Program_Byte(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_HALFWORD:
        /* Program a half-word (16-bit) at a specified address */
        FLASH_Program_HalfWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_WORD:
        /* Program a word (32-bit) at a specified address */
        FLASH_Program_Word(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_DOUBLEWORD:
        /* Program a double-word (64-bit) at a specified address */
        FLASH_Program_DoubleWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_QUADWORD:
        /* Program a quad-word (128-bit) at a specified address */
        FLASH_Program_QuadWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_OTP_HALFWORD:
        /* Program a half-word (16-bit) at a OTP address */
        FLASH_Program_OTPHalfWord(Address, DataAddress);
        break;

      case FLASH_TYPEPROGRAM_OTP_WORD:
        /* Program a word (32-bit) at a OTP address */
        FLASH_Program_OTPWord(Address, DataAddress);
        break;

      default:
        status = HAL_ERROR;

        /* Process Unlocked */
        __HAL_UNLOCK(&pFlash);
        break;
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

  /* Save Flash errors */
  error = FLASH->ISR & FLASH_FLAG_ISR_ERRORS;
  error |= (FLASH->OPTISR & FLASH_FLAG_OPTISR_ERRORS);

  /* Set parameter of the callback */
  if (pFlash.ProcedureOnGoing == FLASH_TYPEERASE_SECTORS)
  {
    param = pFlash.Sector;
  }
  else if ((pFlash.ProcedureOnGoing & FLASH_CR_PG) != 0U)
  {
    param = pFlash.Address;
  }
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }

  /* Clear operation bit on the on-going procedure */
  CLEAR_BIT(FLASH->CR, (pFlash.ProcedureOnGoing & ~(FLASH_WORD_SIZE_MASK)));

  /* Check FLASH operation error flags */
  if (error != 0U)
  {
    /* Save the error code */
    pFlash.ErrorCode |= error;

    /* Clear error programming flags */
    FLASH->ICR = (error & FLASH_FLAG_ISR_ERRORS);
    FLASH->OPTICR = (error & FLASH_FLAG_OPTISR_ERRORS);

    /* Stop the procedure ongoing */
    pFlash.ProcedureOnGoing = 0U;

    /* FLASH error interrupt user callback */
    HAL_FLASH_OperationErrorCallback(param);
  }

  /* Check FLASH End of Operation flag  */
  if ((FLASH->ISR & FLASH_FLAG_EOP) != 0U)
  {
    /* Clear FLASH End of Operation pending bit */
    FLASH->ICR = FLASH_FLAG_EOP;

    if (pFlash.ProcedureOnGoing == FLASH_TYPEERASE_SECTORS)
    {
      /* Nb of sectors to erase can be decreased */
      pFlash.NbSectorsToErase--;

      /* Check if there are still sectors to erase */
      if (pFlash.NbSectorsToErase != 0U)
      {
        /* Increment sector number */
        pFlash.Sector++;
        FLASH_SectorErase(pFlash.Sector);
      }
      else
      {
        /* No more sectors to Erase */
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
    CLEAR_BIT(FLASH->IER, (FLASH_IT_EOP | FLASH_IT_WRPERR | FLASH_IT_PGSERR | FLASH_IT_STRBERR | FLASH_IT_INCERR));

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }

  /* Check ECC Correction Error */
  if ((FLASH->IER & FLASH_IT_SNECCERR) != 0U)
  {
    if ((FLASH->ISR & FLASH_FLAG_SNECCERR) != 0U)
    {
      /* Call User callback */
      HAL_FLASHEx_EccCorrectionCallback();

      /* Clear ECC correction flag in order to allow new ECC error record */
      FLASH->ICR = FLASH_FLAG_SNECCERR;
    }
  }

  /* Check ECC Detection Error */
  if ((FLASH->IER & FLASH_IT_DBECCERR) != 0U)
  {
    if ((FLASH->ISR & FLASH_FLAG_DBECCERR) != 0U)
    {
      /* Call User callback */
      HAL_FLASHEx_EccDetectionCallback();

      /* Clear ECC detection flag in order to allow new ECC error record */
      FLASH->ICR = FLASH_FLAG_DBECCERR;
    }
  }
}

/**
  * @brief  FLASH end of operation interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                  Mass Erase: Bank number which has been requested to erase
  *                  Sector Erase: Sector which has been erased
  *                    (if 0xFFFFFFFF, it means that all the selected sectors have been erased)
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
  *                 Sector Erase: Sector number which returned an error
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
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U)
  {
    /* Authorize the FLASH Registers access */
    WRITE_REG(FLASH->KEYR, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_KEY2);

    /* verify Flash is unlocked */
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Lock the FLASH control register access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH Registers access */
  SET_BIT(FLASH->CR, FLASH_CR_LOCK);

  /* verify Flash is locked */
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U)
  {
    return HAL_OK;
  }

  return HAL_ERROR;
}

/**
  * @brief  Unlock the FLASH Option Bytes Registers access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void)
{
  if (READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK) != 0U)
  {
    /* Authorizes the Option Byte register programming */
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY1);
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY2);

    /* Verify that the Option Bytes are unlocked */
    if (READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK) != 0U)
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
  SET_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK);

  /* Verify that the Option Bytes are locked */
  if (READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK) != 0U)
  {
    return HAL_OK;
  }

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
  *            @arg HAL_FLASH_ERROR_WRP: FLASH Write protection error
  *            @arg HAL_FLASH_ERROR_PGS: FLASH Programming sequence error
  *            @arg HAL_FLASH_ERROR_STRB: FLASH Strobe error
  *            @arg HAL_FLASH_ERROR_INC: FLASH Inconsistency error
  *            @arg HAL_FLASH_ERROR_RDS: FLASH Read security error
  *            @arg HAL_FLASH_ERROR_SNECC: FLASH ECC single error
  *            @arg HAL_FLASH_ERROR_DBECC: FLASH ECC double error
  *            @arg HAL_FLASH_ERROR_CRC: FLASH CRC error
  *            @arg HAL_FLASH_ERROR_KDR: FLASH Key data register error
  *            @arg HAL_FLASH_ERROR_OBC: FLASH Options byte change error
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
  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */

  uint32_t timeout = HAL_GetTick() + Timeout;
  uint32_t error;

  while ((FLASH->SR & FLASH_SR_QW) != 0U)
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
  error = (FLASH->ISR & FLASH_FLAG_ISR_ERRORS);
  error |= (FLASH->OPTISR & FLASH_FLAG_OPTISR_ERRORS);

  if (error != 0U)
  {
    /*Save the error code*/
    pFlash.ErrorCode |= error;

    /* Clear error programming flags */
    FLASH->ICR = (error & FLASH_FLAG_ISR_ERRORS);
    FLASH->OPTICR = (error & FLASH_FLAG_OPTISR_ERRORS);

    return HAL_ERROR;
  }

  /* Check FLASH End of Operation flag  */
  if ((FLASH->ISR & FLASH_FLAG_EOP) != 0U)
  {
    /* Clear FLASH End of Operation pending bit */
    FLASH->ICR = FLASH_FLAG_EOP;
  }

  /* If there is no error flag set */
  return HAL_OK;
}

/**
  * @brief  Program a byte (8-bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_Byte(uint32_t Address, uint32_t DataAddress)
{
  uint8_t *dest_addr = (uint8_t *)Address;
  uint8_t *src_addr  = (uint8_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(Address));

  /* Set PG bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the byte */
  *dest_addr = *src_addr;

  __ISB();
  __DSB();

  /* Set FW bit */
  SET_BIT(FLASH->CR, FLASH_CR_FW);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a half-word (16-bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_HalfWord(uint32_t Address, uint32_t DataAddress)
{
  uint16_t *dest_addr = (uint16_t *)Address;
  uint16_t *src_addr  = (uint16_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(Address));

  /* Set PG bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the half-word */
  *dest_addr = *src_addr;

  __ISB();
  __DSB();

  /* Set FW bit */
  SET_BIT(FLASH->CR, FLASH_CR_FW);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a word (32-bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_Word(uint32_t Address, uint32_t DataAddress)
{
  uint8_t index = 2;
  uint16_t *dest_addr = (uint16_t *)Address;
  uint16_t *src_addr  = (uint16_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(Address));

  /* Set PG bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the word */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    index--;
  } while (index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit */
  SET_BIT(FLASH->CR, FLASH_CR_FW);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a double-word (64-bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_DoubleWord(uint32_t Address, uint32_t DataAddress)
{
  uint8_t index = 4;
  uint16_t *dest_addr = (uint16_t *)Address;
  uint16_t *src_addr  = (uint16_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(Address));

  /* Set PG bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the double-word */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    index--;
  } while (index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit */
  SET_BIT(FLASH->CR, FLASH_CR_FW);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a quad-word (128-bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_QuadWord(uint32_t Address, uint32_t DataAddress)
{
  uint8_t index = 8;
  uint16_t *dest_addr = (uint16_t *)Address;
  uint16_t *src_addr  = (uint16_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(Address));

  /* Set PG bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

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

  __ISB();
  __DSB();

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a half-word (16-bit) at a OTP address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_OTPHalfWord(uint32_t Address, uint32_t DataAddress)
{
  uint16_t *dest_addr = (uint16_t *)Address;
  uint16_t *src_addr  = (uint16_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_OTP_ADDRESS(Address));

  /* Set PG_OTP bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG_OTP);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the half-word */
  *dest_addr = *src_addr;

  __ISB();
  __DSB();

  /* Set FW bit */
  SET_BIT(FLASH->CR, FLASH_CR_FW);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program a word (32-bit) at a OTP address.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddress specifies the address of data to be programmed.
  * @retval None
  */
static void FLASH_Program_OTPWord(uint32_t Address, uint32_t DataAddress)
{
  uint8_t index = 2;
  uint16_t *dest_addr = (uint16_t *)Address;
  uint16_t *src_addr  = (uint16_t *)DataAddress;
  uint32_t primask_bit;

  /* Check the parameters */
  assert_param(IS_FLASH_OTP_ADDRESS(Address));

  /* Set PG_OTP bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG_OTP);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program the word */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    index--;
  } while (index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit */
  SET_BIT(FLASH->CR, FLASH_CR_FW);

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
