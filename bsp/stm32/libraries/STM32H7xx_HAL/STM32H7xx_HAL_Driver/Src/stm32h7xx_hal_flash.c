/**
  ******************************************************************************
  * @file    stm32h7xx_hal_flash.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
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
           
  [..] The Flash memory interface manages CPU AXI I-Code and D-Code accesses 
       to the Flash memory. It implements the erase and program Flash memory operations 
       and the read and write protection mechanisms.
      
  

  [..] The FLASH main features are:
      (+) Flash memory read operations
      (+) Flash memory program/erase operations
      (+) Read / write protections
      (+) Option bytes programming      
      (+) Error code correction (ECC) : Data in flash are 266-bits word
          (10 bits added per double word)
      
      
                        ##### How to use this driver #####
 ==============================================================================
    [..]                             
      This driver provides functions and macros to configure and program the FLASH
      memory of all STM32H7xx devices.
   
      (#) FLASH Memory IO Programming functions:
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and
                HAL_FLASH_Lock() functions
           (++) Program functions: double word only
           (++) There Two modes of programming :
            (+++) Polling mode using HAL_FLASH_Program() function
            (+++) Interrupt mode using HAL_FLASH_Program_IT() function
    
      (#) Interrupts and flags management functions : 
           (++) Handle FLASH interrupts by calling HAL_FLASH_IRQHandler()
           (++) Callback functions are called when the flash operations are finished :
                HAL_FLASH_EndOfOperationCallback() when everything is ok, otherwise
                HAL_FLASH_OperationErrorCallback()
           (++) Get error flag status by calling HAL_FLASH_GetError()
      
      (#) Option bytes management functions :
           (++) Lock and Unlock the option bytes using HAL_FLASH_OB_Unlock() and
                HAL_FLASH_OB_Lock() functions
           (++) Launch the reload of the option bytes using HAL_FLASH_Launch() function.
                In this case, a reset is generated
    [..] 
      In addition to these functions, this driver includes a set of macros allowing
      to handle the following operations:
       (+) Set the latency
       (+) Enable/Disable the FLASH interrupts
       (+) Monitor the FLASH flags status
     [..]
    (@) For any Flash memory program operation (erase or program), the CPU clock frequency
        (HCLK) must be at least 1MHz. 
    (@) The contents of the Flash memory are not guaranteed if a device reset occurs during 
        a Flash memory operation.
    (@) Any attempt to read the Flash memory while it is being written or erased, causes the 
        bus to stall. Read operations are processed correctly once the program operation has 
        completed. This means that code or data fetches cannot be performed while a write/erase 
        operation is ongoing
    
 @endverbatim                      
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/ 
/** @addtogroup FLASH_Private_Constants
  * @{
  */
#define FLASH_TIMEOUT_VALUE       ((uint32_t)50000U)/* 50 s */
/**
  * @}
  */         
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FLASH_ProcessTypeDef pFlash;
/* Private function prototypes -----------------------------------------------*/
static void FLASH_SetErrorCode(uint32_t Bank);
/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASH_Private_Functions FLASH Private functions
  * @{
  */

/** @defgroup FLASH_Group1 Programming operation functions 
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
  * @brief  Program flash word of 256 bits at a specified address
  * @param  TypeProgram Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  FlashAddress specifies the address to be programmed.
  * @param  DataAddress specifies the address of data (256 bits) to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t FlashAddress, uint64_t DataAddress)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  __IO uint64_t *dest_addr = (__IO uint64_t *)FlashAddress;
  __IO uint64_t *src_addr = (__IO uint64_t*)((uint32_t)DataAddress);
  uint32_t bank;
  uint8_t row_index = 4;
  
  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(FlashAddress));

  if(IS_FLASH_PROGRAM_ADDRESS_BANK1(FlashAddress))
  {
    bank = FLASH_BANK_1;
  }
  else
  {
    bank = FLASH_BANK_2;    
  }
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, bank);
  
  if(status == HAL_OK)
  {
    if(bank == FLASH_BANK_1)
    {
      /* Clear bank 1 pending flags (if any) */ 
      __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1 | FLASH_FLAG_QW_BANK1 | FLASH_FLAG_WBNE_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK1); 
  
      /* Set PG bit */
      SET_BIT(FLASH->CR1, FLASH_CR_PG);
    }
    else
    {
      /* Clear bank 2 pending flags (if any) */ 
      __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2 | FLASH_FLAG_QW_BANK2 | FLASH_FLAG_WBNE_BANK2 | FLASH_FLAG_ALL_ERRORS_BANK2); 
  
      /* Set PG bit */
      SET_BIT(FLASH->CR2, FLASH_CR_PG);  
    }
  
    /* Program the 256 bits flash word */
    do
    {
      *dest_addr++ = *src_addr++;
    } while (--row_index != 0);

    __DSB();
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, bank);
    
    if(bank == FLASH_BANK_1)
    {
      /* Check FLASH End of Operation flag  */
      if (__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_EOP_BANK1))
      {
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1);
      }
    
      /* If the program operation is completed, disable the PG*/
      CLEAR_BIT(FLASH->CR1, FLASH_CR_PG);
    }
    else
    {
      /* Check FLASH End of Operation flag  */
      if (__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_EOP_BANK2))
      {
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2);
      }
    
      /* If the program operation is completed, disable the PG */
      CLEAR_BIT(FLASH->CR2, FLASH_CR_PG);
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;  
}

/**
  * @brief  Program flash words of 256 bits at a specified address with interrupt enabled.
  * @param  TypeProgram Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  FlashAddress specifies the address to be programmed.
  * @param  DataAddress specifies the address of data (256 bits) to be programmed
  * 
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t FlashAddress, uint64_t DataAddress)
{
  HAL_StatusTypeDef status = HAL_OK;
  __IO uint64_t *dest_addr = (__IO uint64_t*)FlashAddress;
  __IO uint64_t *src_addr = (__IO uint64_t*)((uint32_t)DataAddress);
  uint32_t bank;
  uint8_t row_index = 4;

  /* Process Locked */
  __HAL_LOCK(&pFlash);
  
  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(FlashAddress));  

  if(IS_FLASH_PROGRAM_ADDRESS_BANK1(FlashAddress))
  {
    bank = FLASH_BANK_1;
    pFlash.ProcedureOnGoing = FLASH_PROC_PROGRAM_BANK1;
  }
  else
  {
    bank = FLASH_BANK_2;
    pFlash.ProcedureOnGoing = FLASH_PROC_PROGRAM_BANK2;    
  }  

  /* Set internal variables used by the IRQ handler */
  pFlash.Address = FlashAddress;
    
  if(bank == FLASH_BANK_1)
  {
    /* Clear bank 1 pending flags (if any) */ 
    __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK1); 
  
    /* Set PG bit */
    SET_BIT(FLASH->CR1, FLASH_CR_PG);
  
    /* Enable End of Operation and Error interrupts for Bank 1 */
    __HAL_FLASH_ENABLE_IT_BANK1(FLASH_IT_EOP_BANK1    | FLASH_IT_WRPERR_BANK1 | FLASH_IT_PGSERR_BANK1 | \
                                FLASH_IT_STRBERR_BANK1 | FLASH_IT_INCERR_BANK1 | FLASH_IT_OPERR_BANK1); 
  }
  else
  {
    /* Clear bank 2 pending flags (if any) */ 
    __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2 | FLASH_FLAG_ALL_ERRORS_BANK2); 
  
    /* Set PG bit */
    SET_BIT(FLASH->CR2, FLASH_CR_PG);
    
    /* Enable End of Operation and Error interrupts for Bank2*/
    __HAL_FLASH_ENABLE_IT_BANK2(FLASH_IT_EOP_BANK2    | FLASH_IT_WRPERR_BANK2 | FLASH_IT_PGSERR_BANK2 | \
                                FLASH_IT_STRBERR_BANK2 | FLASH_IT_INCERR_BANK2 | FLASH_IT_OPERR_BANK2);    
  }

  /* Program the 256 bits flash word */
  do
  {
    *dest_addr++ = *src_addr++;
  } while (--row_index != 0);

  return status;  
}

/**
  * @brief This function handles FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t temp;

  /* Check FLASH Bank1 End of Operation flag  */
  if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_SR_EOP) != RESET)
  {
    if(pFlash.ProcedureOnGoing == FLASH_PROC_SECTERASE_BANK1)
    {
      /*Nb of sector to erased can be decreased*/
      pFlash.NbSectorsToErase--;

      /* Check if there are still sectors to erase*/
      if(pFlash.NbSectorsToErase != 0)
      {
        temp = pFlash.Sector;
        /*Indicate user which sector has been erased*/
        HAL_FLASH_EndOfOperationCallback(temp);

        /* Clear pending flags (if any) */  
        /* Clear bank 1 pending flags (if any) */ 
        __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK1);  

        /*Increment sector number*/
        temp = ++pFlash.Sector;
        FLASH_Erase_Sector(temp, FLASH_BANK_1/*pFlash.Bank*/, pFlash.VoltageForErase);
      }
      else
      {
        /*No more sectors to Erase, user callback can be called.*/
        /*Reset Sector and stop Erase sectors procedure*/
        pFlash.Sector = temp = 0xFFFFFFFF;
        pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(temp);
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1);
      }
    }
    else 
    {
      if((pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE_BANK1) || (pFlash.ProcedureOnGoing == FLASH_PROC_ALLBANK_MASSERASE))
      {
        /*MassErase ended. Return the selected bank*/
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(FLASH_BANK_1);
      }
      else if(pFlash.ProcedureOnGoing == FLASH_PROC_PROGRAM_BANK1)
      {
        /*Program ended. Return the selected address*/
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(pFlash.Address);
      }
      
      if((pFlash.ProcedureOnGoing != FLASH_PROC_SECTERASE_BANK2) && \
         (pFlash.ProcedureOnGoing != FLASH_PROC_MASSERASE_BANK2)&& \
         (pFlash.ProcedureOnGoing != FLASH_PROC_PROGRAM_BANK2))
      {
        pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1);
      }
    }
  }

 /* Check FLASH Bank2 End of Operation flag  */
  if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_SR_EOP) != RESET)
  {
    if(pFlash.ProcedureOnGoing == FLASH_PROC_SECTERASE_BANK2)
    {
      /*Nb of sector to erased can be decreased*/
      pFlash.NbSectorsToErase--;

      /* Check if there are still sectors to erase*/
      if(pFlash.NbSectorsToErase != 0)
      {
        temp = pFlash.Sector;
        /*Indicate user which sector has been erased*/
        HAL_FLASH_EndOfOperationCallback(temp);

        /* Clear pending flags (if any) */  
        /* Clear bank 2 pending flags (if any) */ 
        __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2 | FLASH_FLAG_ALL_ERRORS_BANK2);  

        /*Increment sector number*/
        temp = ++pFlash.Sector;
        FLASH_Erase_Sector(temp, FLASH_BANK_2 /*pFlash.Bank*/, pFlash.VoltageForErase);
      }
      else
      {
        /*No more sectors to Erase, user callback can be called.*/
        /*Reset Sector and stop Erase sectors procedure*/
        pFlash.Sector = temp = 0xFFFFFFFF;
        pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(temp);
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2);
      }
    }
    else 
    {
      if((pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE_BANK2) || (pFlash.ProcedureOnGoing == FLASH_PROC_ALLBANK_MASSERASE))
      {
        /*MassErase ended. Return the selected bank*/
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(FLASH_BANK_2);
      }
      else
      {
        /*Program ended. Return the selected address*/
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(pFlash.Address);
      }

      if((pFlash.ProcedureOnGoing != FLASH_PROC_SECTERASE_BANK1) && \
          (pFlash.ProcedureOnGoing != FLASH_PROC_MASSERASE_BANK1)&& \
          (pFlash.ProcedureOnGoing != FLASH_PROC_PROGRAM_BANK1))
      {
        pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2);
      }
    }
  }
  
  /* Check FLASH Bank1 operation error flags */
  if(__HAL_FLASH_GET_FLAG_BANK1((FLASH_FLAG_EOP_BANK1    | FLASH_FLAG_WRPERR_BANK1 | FLASH_FLAG_PGSERR_BANK1 | \
                                 FLASH_FLAG_STRBER_BANK1R | FLASH_FLAG_INCERR_BANK1 | FLASH_FLAG_OPERR_BANK1)) != RESET)
  {
    if(pFlash.ProcedureOnGoing == FLASH_PROC_SECTERASE_BANK1)
    {
      /*return the faulty sector*/
      temp = pFlash.Sector;
      pFlash.Sector = 0xFFFFFFFF;
    }
    else if((pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE_BANK1) || (pFlash.ProcedureOnGoing == FLASH_PROC_ALLBANK_MASSERASE))
    {
      /*return the faulty bank*/
      temp = FLASH_BANK_1;
    }
    else
    {
      /*return the faulty address*/
      temp = pFlash.Address;
    }
    
    /*Save the Error code*/
    FLASH_SetErrorCode(FLASH_BANK_1);

    /* FLASH error interrupt user callback */
    HAL_FLASH_OperationErrorCallback(temp);
    /* Clear FLASH error pending bits */
    __HAL_FLASH_CLEAR_FLAG_BANK1((FLASH_FLAG_EOP_BANK1    | FLASH_FLAG_WRPERR_BANK1 | FLASH_FLAG_PGSERR_BANK1 | \
                                  FLASH_FLAG_STRBER_BANK1R | FLASH_FLAG_INCERR_BANK1 | FLASH_FLAG_OPERR_BANK1));

    /*Stop the procedure ongoing*/
    pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
  }
  
 /* Check FLASH Bank2 operation error flags */
  if(__HAL_FLASH_GET_FLAG_BANK2((FLASH_FLAG_EOP_BANK2    | FLASH_FLAG_WRPERR_BANK2 | FLASH_FLAG_PGSERR_BANK2 | \
                                 FLASH_FLAG_STRBER_BANK2R | FLASH_FLAG_INCERR_BANK2 | FLASH_FLAG_OPERR_BANK2)) != RESET)
                 
  {
    if(pFlash.ProcedureOnGoing == FLASH_PROC_SECTERASE_BANK2)
    {
      /*return the faulty sector*/
      temp = pFlash.Sector;
      pFlash.Sector = 0xFFFFFFFF;
    }
    else if((pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE_BANK2) || (pFlash.ProcedureOnGoing == FLASH_PROC_ALLBANK_MASSERASE))
    {
      /*return the faulty bank*/
      temp = FLASH_BANK_2;
    }
    else
    {
      /*return the faulty address*/
      temp = pFlash.Address;
    }
    
    /*Save the Error code*/
    FLASH_SetErrorCode(FLASH_BANK_2);

    /* FLASH error interrupt user callback */
    HAL_FLASH_OperationErrorCallback(temp);
    /* Clear FLASH error pending bits */
    __HAL_FLASH_CLEAR_FLAG_BANK2((FLASH_FLAG_EOP_BANK2    | FLASH_FLAG_WRPERR_BANK2 | FLASH_FLAG_PGSERR_BANK2 | \
                                  FLASH_FLAG_STRBER_BANK2R | FLASH_FLAG_INCERR_BANK2 |   FLASH_FLAG_OPERR_BANK2));

    /*Stop the procedure ongoing*/
    pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
  }  
  
  if(pFlash.ProcedureOnGoing == FLASH_PROC_NONE)
  {
    /* Disable Bank1 Operation and Error source interrupt */
    __HAL_FLASH_DISABLE_IT_BANK1(FLASH_IT_EOP_BANK1    | FLASH_IT_WRPERR_BANK1 | FLASH_IT_PGSERR_BANK1 | \
                                 FLASH_IT_STRBERR_BANK1 | FLASH_IT_INCERR_BANK1 | FLASH_IT_OPERR_BANK1);
                
    /* Disable Bank2 Operation and Error source interrupt */
    __HAL_FLASH_DISABLE_IT_BANK2(FLASH_IT_EOP_BANK2    | FLASH_IT_WRPERR_BANK2 | FLASH_IT_PGSERR_BANK2 | \
                                 FLASH_IT_STRBERR_BANK2 | FLASH_IT_INCERR_BANK2 | FLASH_IT_OPERR_BANK2); 

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  
}

/**
  * @brief  FLASH end of operation interrupt callback
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                  Mass Erase Bank number which has been requested to erase
  *                  Sectors Erase: Sector which has been erased 
  *                    (if 0xFFFFFFFF, it means that all the selected sectors have been erased)
  *                  Program Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FLASH_EndOfOperationCallback could be implemented in the user file
   */ 
}

/**
  * @brief  FLASH operation error interrupt callback
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                 Mass Erase: Bank number which has been requested to erase
  *                 Sectors Erase: Sector number which returned an error
  *                 Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FLASH_OperationErrorCallback could be implemented in the user file
   */ 
}

/**
  * @}
  */ 

/** @defgroup FLASH_Group2 Peripheral Control functions 
 *  @brief   management functions 
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
  * @brief  Unlock the FLASH control registers access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
  if((READ_BIT(FLASH->CR1, FLASH_CR_LOCK) != RESET) && (READ_BIT(FLASH->CR2, FLASH_CR_LOCK) != RESET))
  {
    /* Authorize the FLASH A Registers access */
    WRITE_REG(FLASH->KEYR1, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR1, FLASH_KEY2);
  
    /* Authorize the FLASH B Registers access */
    WRITE_REG(FLASH->KEYR2, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR2, FLASH_KEY2);
  }
  else
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

/**
  * @brief  Locks the FLASH control registers access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH A Registers access */
  SET_BIT(FLASH->CR1, FLASH_CR_LOCK);
  
  /* Set the LOCK Bit to lock the FLASH B Registers access */
  SET_BIT(FLASH->CR2, FLASH_CR_LOCK);
  
  return HAL_OK;  
}

/**
  * @brief  Unlock the FLASH Option Control Registers access.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void)
{
  if(READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK) != RESET)
  {
    /* Authorizes the Option Byte register programming */
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPT_KEY1);
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPT_KEY2);
  }
  else
  {
    return HAL_ERROR;
  }  
  
  return HAL_OK;  
}

/**
  * @brief  Lock the FLASH Option Control Registers access.
  * @retval HAL Status 
  */
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void)
{
  /* Set the OPTLOCK Bit to lock the FLASH A and B Option Byte Registers access */
  SET_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK);
  
  return HAL_OK;  
}

/**
  * @brief  Launch the option byte loading.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Set OPTSTRT Bit */
  SET_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTSTART);  

  /* Wait for OB change operation to be completed */
  status = FLASH_OB_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  return status; 
}

/**
  * @}
  */

/** @defgroup FLASH_Group3 Peripheral State and Errors functions 
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
  * @retval HAL_FLASH_ERRORCode The returned value can be:
  *            @arg HAL_FLASH_ERROR_NONE: No error set 
  *
  *            @arg HAL_FLASH_ERROR_WRP_BANK1: Write Protection Error on Bank 1
  *            @arg HAL_FLASH_ERROR_PGS_BANK1  : Program Sequence Error on Bank 1
  *            @arg HAL_FLASH_ERROR_STRB_BANK1 : Strobe Error on Bank 1
  *            @arg HAL_FLASH_ERROR_INC_BANK1  : Inconsistency Error on Bank 1
  *            @arg HAL_FLASH_ERROR_OPE_BANK1  : Operation Error on Bank 1
  *            @arg HAL_FLASH_ERROR_RDP_BANK1  : Read Protection Error on Bank 1
  *            @arg HAL_FLASH_ERROR_RDS_BANK1  : Read Secured Error on Bank 1 
  *            @arg HAL_FLASH_ERROR_SNECC_BANK1: SNECC Error on Bank 1 
  *            @arg HAL_FLASH_ERROR_DBECC_BANK1: Double Detection ECC on Bank 1
  *
  *            @arg HAL_FLASH_ERROR_WRP_BANK2  : Write Protection Error on Bank 2
  *            @arg HAL_FLASH_ERROR_PGS_BANK2  : Program Sequence Error on Bank 2
  *            @arg HAL_FLASH_ERROR_STRB_BANK2 : Strobe Error on Bank 2
  *            @arg HAL_FLASH_ERROR_INC_BANK2  : Inconsistency Error on Bank 2
  *            @arg HAL_FLASH_ERROR_OPE_BANK2  : Operation Error on Bank 2
  *            @arg HAL_FLASH_ERROR_RDP_BANK2  : Read Protection Error on Bank 2
  *            @arg HAL_FLASH_ERROR_RDS_BANK2  : Read Secured Error on Bank 2 
  *            @arg HAL_FLASH_ERROR_SNECC_BANK2: SNECC Error on Bank 2 
  *            @arg HAL_FLASH_ERROR_DBECC_BANK2: Double Detection ECC on Bank 2  
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

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout maximum flash operation timeout
  * @param  Bank flash FLASH_BANK_1 or FLASH_BANK_2
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout, uint32_t Bank)
{
  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */
    
  uint32_t bsyflag, errorflag = 0;  
  uint32_t timeout = HAL_GetTick() + Timeout;
  
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Bank));
  
  if(Bank == FLASH_BANK_1)
  {
    bsyflag = FLASH_FLAG_BSY_BANK1 | FLASH_FLAG_QW_BANK1;

    if((FLASH->OPTCR & FLASH_OPTCR_SWAP_BANK) == 0)
    {
      bsyflag |= FLASH_FLAG_WBNE_BANK1;
    }
    else
    {
      bsyflag |= FLASH_FLAG_WBNE_BANK2;
    }      
  }
  else
  {
    bsyflag = FLASH_FLAG_BSY_BANK2 | FLASH_FLAG_QW_BANK2;

    if((FLASH->OPTCR & FLASH_OPTCR_SWAP_BANK) == 0)
    {
      bsyflag |= FLASH_FLAG_WBNE_BANK2;
    }
    else
    {
      bsyflag |= FLASH_FLAG_WBNE_BANK1;
    }    
  }
     
  while(__HAL_FLASH_GET_FLAG(bsyflag)) 
  { 
    if(Timeout != HAL_MAX_DELAY)
    {
      if(HAL_GetTick() >= timeout)
      {
        return HAL_TIMEOUT;
      }
    } 
  }
  
  if((Bank == FLASH_BANK_1) && ((FLASH->SR1 & FLASH_FLAG_ALL_ERRORS_BANK1) != RESET))
  {
    errorflag = FLASH_FLAG_ALL_ERRORS_BANK1;
  }
  else if((Bank == FLASH_BANK_2) && ((FLASH->SR2 & FLASH_FLAG_ALL_ERRORS_BANK2 & 0x7FFFFFFF) != RESET))
  {
    errorflag = FLASH_FLAG_ALL_ERRORS_BANK2;
  }

  if(errorflag != 0)
  {
    /*Save the error code*/
    FLASH_SetErrorCode(Bank);
    
    /* Clear error programming flags */
    __HAL_FLASH_CLEAR_FLAG(errorflag);

    return HAL_ERROR;
  }

  /* If there is an error flag set */
  return HAL_OK;  
}

/**
  * @brief  Wait for a FLASH Option Bytes change operation to complete.
  * @param  Timeout maximum flash operation timeout
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef FLASH_OB_WaitForLastOperation(uint32_t Timeout)
{
  uint32_t timeout = HAL_GetTick() + Timeout;
  
  /* Wait for the FLASH Option Bytes change operation to complete by polling on OPT_BUSY flag to be reset.*/
  while(FLASH->OPTSR_CUR & FLASH_OPTSR_OPT_BUSY) 
  { 
    if(Timeout != HAL_MAX_DELAY)
    {
      if(HAL_GetTick() >= timeout)
      {
        return HAL_TIMEOUT;
      }
    } 
  }
  if(FLASH->OPTSR_CUR & FLASH_OPTSR_OPTCHANGEERR)
  {
    /*Save the error code*/
    pFlash.ErrorCode |= HAL_FLASH_ERROR_OB_CHANGE;
    
    /*Clear the OB error flag*/
    FLASH->OPTCCR |= FLASH_OPTCCR_CLR_OPTCHANGEERR;
    
    return HAL_ERROR;    
  }

  /* If there is an error flag set */
  return HAL_OK;  
}

/**
  * @brief  Set the specific FLASH error flag.
  * @retval None
  */
static void FLASH_SetErrorCode(uint32_t Bank)
{  
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
  
  if(Bank == FLASH_BANK_1)
  {
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_WRPERR_BANK1))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_WRP_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_PGSERR_BANK1))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_PGS_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_STRBER_BANK1R))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_STRB_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_INCERR_BANK1))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_INC_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_OPERR_BANK1))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_OPE_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_RDPERR_BANK1))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_RDP_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_RDSERR_BANK1))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_RDS_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_SNECCE_BANK1RR))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_SNECC_BANK1;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_DBECCE_BANK1RR))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_DBECC_BANK1;
    }  
  }
  else if(Bank == FLASH_BANK_2)
  {
    if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_WRPERR_BANK2))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_WRP_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_PGSERR_BANK2))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_PGS_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_STRBER_BANK2R))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_STRB_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_INCERR_BANK2))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_INC_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_OPERR_BANK2))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_OPE_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_RDPERR_BANK2))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_RDP_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_RDSERR_BANK2))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_RDS_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK1(FLASH_FLAG_SNECCE_BANK2RR))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_SNECC_BANK2;
    }
    if(__HAL_FLASH_GET_FLAG_BANK2(FLASH_FLAG_DBECCE_BANK2RR))
    {
      pFlash.ErrorCode |= HAL_FLASH_ERROR_DBECC_BANK2;
    }  
  }
} 

#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
