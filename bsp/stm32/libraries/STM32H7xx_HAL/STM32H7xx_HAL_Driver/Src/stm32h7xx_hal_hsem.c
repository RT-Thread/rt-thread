/**
  ******************************************************************************
  * @file    stm32h7xx_hal_hsem.c
  * @author  MCD Application Team
  * @brief   HSEM HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the semaphore peripheral:
  *           + Semaphore Take function (2-Step Procedure) , non blocking
  *           + Semaphore FastTake function (1-Step Procedure) , non blocking
  *           + Semaphore Status check
  *           + Semaphore Clear Key Set and Get
  *           + Release and release all functions
  *           + Semaphore notification enabling and disabling and callnack functions
  *           + IRQ handler management
  *
  *      
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
  [..]
      (#)Take a semaphore In 2-Step mode Using function HAL_HSEM_Take. This function takes as parameters :
           (++) the semaphore ID from 0 to 31
           (++) the process ID from 0 to 255
      (#) Fast Take semaphore In 1-Step mode Using function HAL_HSEM_FastTake. This function takes as parameter :
           (++) the semaphore ID from 0_ID to 31. Note that the process ID value is implicitly assumed as zero
      (#) Check if a semaphore is Taken using function HAL_HSEM_IsSemTaken. This function takes as parameter : 
          (++) the semaphore ID from 0_ID to 31
          (++) It returns 1 if the given semaphore is taken otherwise (Free) zero.
      (#)Release a semaphore using function with HAL_HSEM_Release. This function takes as parameters :
           (++) the semaphore ID from 0 to 31
           (++) the process ID from 0 to 255:
           (++) Note: If ProcessID and MasterID match, semaphore is freed, and an interrupt
         may be generated when enabled (notification activated). If ProcessID or MasterID does not match, 
         semaphore remains taken (locked).
         
      (#)Release all semaphores at once taken by a given Master using function HAL_HSEM_Release_All
          This function takes as parameters :
           (++) the Release Key (value from 0 to 0xFFFF) can be Set or Get respectively by 
              HAL_HSEM_SetClearKey() or HAL_HSEM_GetClearKey functions
           (++) the Master ID:
           (++) Note: If the Key and MasterID match, all semaphores taken by the given CPU that corresponds
           to MasterID  will be freed, and an interrupt may be generated when enabled (notification activated). If the
           Key or the MasterID doesn't match, semaphores remains taken (locked).
              
      (#)Semaphores Release all key functions:
         (++)  HAL_HSEM_SetClearKey() to set semaphore release all Key
         (++)  HAL_HSEM_GetClearKey() to get release all Key
      (#)Semaphores notification functions :
         (++)  HAL_HSEM_ActivateNotification to activate a notification callback on
               a given semaphores Mask (bitfield). When one or more semaphores defined by the mask are released
               the callback HAL_HSEM_FreeCallback will be asserted giving as parameters a mask of the released
               semaphores (bitfield).       

         (++)  HAL_HSEM_DeactivateNotification to deactivate the notification of a given semaphores Mask (bitfield).
         (++) See the description of the macro __HAL_HSEM_SEMID_TO_MASK to check how to calculate a semaphore mask
                Used by the notification functions
     *** HSEM HAL driver macros list ***
     ============================================= 
     [..] Below the list of most used macros in HSEM HAL driver.

      (+) __HAL_HSEM_SEMID_TO_MASK: Helper macro to convert a Semaphore ID to a Mask.
      [..] Example of use :
      [..] mask = __HAL_HSEM_SEMID_TO_MASK(8)  |  __HAL_HSEM_SEMID_TO_MASK(21) | __HAL_HSEM_SEMID_TO_MASK(25). 
      [..] All next macros take as parameter a semaphore Mask (bitfiled) that can be constructed using  __HAL_HSEM_SEMID_TO_MASK as the above example.
      (+) __HAL_HSEM_ENABLE_IT: Enable the specified semaphores Mask interrupts.
      (+) __HAL_HSEM_DISABLE_IT: Disable the specified semaphores Mask interrupts.
      (+) __HAL_HSEM_GET_IT: Checks whether the specified semaphore interrupt has occurred or not. 
      (+) __HAL_HSEM_GET_FLAG: Get the semaphores status release flags.
      (+) __HAL_HSEM_CLEAR_FLAG: Clear the semaphores status release flags.

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

/** @defgroup HSEM HSEM
  * @brief HSEM HAL module driver
  * @{
  */

#ifdef HAL_HSEM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
    
/** @defgroup HSEM_Exported_Functions  HSEM Exported Functions
  * @{
  */

/** @defgroup HSEM_Exported_Functions_Group1 Take and Release functions
 *  @brief    HSEM Take and Release functions 
 *
@verbatim
 ==============================================================================
              ##### HSEM Take and Release functions #####
 ==============================================================================
[..] This section provides functions allowing to:
      (+) Take a semaphore with 2 Step method 
      (+) Fast Take a semaphore with 1 Step method
      (+) Check semaphore state Taken or not  
      (+) Release a semaphore
      (+) Release all semaphore at once

@endverbatim
  * @{
  */


/**
  * @brief  Take a semaphore in 2 Step mode. 
  * @param  SemID: semaphore ID from 0 to 31  
  * @param  ProcessID: Process ID from 0 to 255 
  * @retval HAL status
*/
HAL_StatusTypeDef  HAL_HSEM_Take(uint32_t SemID, uint32_t ProcessID)
{          
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));
  assert_param(IS_HSEM_PROCESSID(ProcessID));
  
  /* First step  write R register with MasterID, processID and take bit=1*/
  HSEM->R[SemID] = ((ProcessID & HSEM_R_PROCID) | ((HAL_GetCurrentCPUID() << POSITION_VAL(HSEM_R_MASTERID)) & HSEM_R_MASTERID) | HSEM_R_LOCK);

  /* second step : read the R register . Take achieved if MasterID and processID match and take bit set to 1 */
  if(HSEM->R[SemID] == ((ProcessID & HSEM_R_PROCID) | ((HAL_GetCurrentCPUID() << POSITION_VAL(HSEM_R_MASTERID)) & HSEM_R_MASTERID) | HSEM_R_LOCK))
  {
    /*take success when MasterID and ProcessID match and take bit set*/
    return HAL_OK; 
  } 

  /* Semaphore take fails*/
  return HAL_ERROR;
}
  
/**
  * @brief  Fast Take a semaphore with 1 Step mode. 
  * @param  SemID: semaphore ID from 0 to 31    
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_HSEM_FastTake(uint32_t SemID)
{     
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));
 
  /* Read the RLR register to take the semaphore */    
  if(HSEM->RLR[SemID] == (((HAL_GetCurrentCPUID() << POSITION_VAL(HSEM_R_MASTERID)) & HSEM_RLR_MASTERID) | HSEM_RLR_LOCK))
  {
    /*take success when MasterID match and take bit set*/
    return HAL_OK;
  }

  /* Semaphore take fails */  
  return HAL_ERROR;  
} 
  
/**
  * @brief  Check semaphore state Taken or not. 
  * @param  SemID: semaphore ID
  * @retval HAL HSEM state
  */
uint32_t HAL_HSEM_IsSemTaken(uint32_t SemID)
{
  return ((HSEM->R[SemID] & HSEM_R_LOCK) != 0U);  
} 
  

/**
  * @brief  Release a semaphore. 
  * @param  SemID: semaphore ID from 0 to 31   
  * @param  ProcessID: Process ID from 0 to 255 
  * @retval None
*/
void  HAL_HSEM_Release(uint32_t SemID, uint32_t ProcessID)
{  
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));
  assert_param(IS_HSEM_PROCESSID(ProcessID));  
  
  /* Clear the semaphore by writing to the R register : the MasterID , the processID and take bit = 0  */
  HSEM->R[SemID] = ((ProcessID & HSEM_R_PROCID) | ((HAL_GetCurrentCPUID() << POSITION_VAL(HSEM_R_MASTERID)) & HSEM_R_MASTERID));

}

/**
  * @brief  Release All semaphore used by a given Master . 
  * @param  Key: Semaphore Key , value from 0 to 0xFFFF
  * @param  MasterID: MasterID of the CPU that is using semaphores to be Released 
  * @retval None
*/
void HAL_HSEM_ReleaseAll(uint32_t Key, uint32_t MasterID)
{
  assert_param(IS_HSEM_KEY(Key));  
  assert_param(IS_HSEM_MASTERID(MasterID));  
  
  HSEM->CR = (((Key << POSITION_VAL(HSEM_KEYR_KEY)) & HSEM_CR_KEY ) | ((MasterID << POSITION_VAL(HSEM_CR_MASTERID)) & HSEM_CR_MASTERID)); 
}

/**
  * @}
  */

/** @defgroup HSEM_Exported_Functions_Group2 HSEM Set and Get Key functions 
 *  @brief    HSEM Set and Get Key functions. 
 *
@verbatim
  ==============================================================================
              ##### HSEM Set and Get Key functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Set semaphore Key
      (+) Get semaphore Key
@endverbatim

  * @{
  */

/**
  * @brief  Set semaphore Key . 
  * @param  Key: Semaphore Key , value from 0 to 0xFFFF
  * @retval None
*/
void  HAL_HSEM_SetClearKey(uint32_t Key)
{
  assert_param(IS_HSEM_KEY(Key));
  
  MODIFY_REG(HSEM->KEYR, HSEM_KEYR_KEY, (Key << POSITION_VAL(HSEM_KEYR_KEY)));
     
}

/**
  * @brief  Get semaphore Key . 
  * @retval Semaphore Key , value from 0 to 0xFFFF
*/
uint32_t HAL_HSEM_GetClearKey(void)
{
  return (HSEM->KEYR >> POSITION_VAL(HSEM_KEYR_KEY));
}

/**
  * @}
  */
  
/** @defgroup HSEM_Exported_Functions_Group3 HSEM IRQ handler management  
 *  @brief    HSEM Notification functions.
 *
@verbatim   
  ==============================================================================
      ##### HSEM IRQ handler management and Notification functions #####
  ==============================================================================  
[..]  This section provides HSEM IRQ handler and Notification function.

@endverbatim
  * @{
  */

/**
  * @brief  Activate Semaphore release Notification for a given Semaphores Mask . 
  * @param  SemMask: Mask of Released semaphores
  * @retval Semaphore Key
*/
void HAL_HSEM_ActivateNotification(uint32_t SemMask)
{
  /*Activate interrupt for CM7 Master */
  HSEM->IER |= SemMask;     
}

/**
  * @brief  Deactivate Semaphore release Notification for a given Semaphores Mask . 
  * @param  SemMask: Mask of Released semaphores
  * @retval Semaphore Key
*/
void HAL_HSEM_DeactivateNotification(uint32_t SemMask)
{

  /*Deactivate interrupt  for CM7 Master */
  HSEM->IER &= ~SemMask;     
}

/**
  * @brief  This function handles HSEM interrupt request.
  * @retval None
*/
void HAL_HSEM_IRQHandler(void)
{
  uint32_t statusreg = 0U;

  /* Get the list of masked freed semaphores*/
  statusreg = HSEM->MISR;

  /*Disable Interrupts*/
  HSEM->IER &= ~((uint32_t)statusreg);
  
  /*Clear Flags*/
  HSEM->ICR |=  ((uint32_t)statusreg); 


  /* Call FreeCallback */ 
  HAL_HSEM_FreeCallback(statusreg);  
}

/**
  * @brief Semaphore Released Callback.
  * @param SemMask: Mask of Released semaphores
  * @retval None
  */
__weak void HAL_HSEM_FreeCallback(uint32_t SemMask)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(SemMask);
  
  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_HSEM_FreeCallback can be implemented in the user file
  */
}  

/**
  * @}
  */
  
/**
  * @}
  */

#endif /* HAL_HSEM_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
