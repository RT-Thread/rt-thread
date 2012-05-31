/**
  ******************************************************************************
  * @file    stm32f0xx_crc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of CRC computation unit peripheral:
  *            + Configuration of the CRC computation unit
  *            + CRC computation of one/many 32-bit data
  *            + CRC Independent register (IDR) access
  *
  *  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    
         (+) Enable CRC AHB clock using RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE)
             function
         (+) If required, select the reverse operation on input data 
             using CRC_ReverseInputDataSelect()  
         (+) If required, enable the reverse operation on output data
             using CRC_ReverseOutputDataCmd(Enable)
         (+) use CRC_CalcCRC() function to compute the CRC of a 32-bit data
             or use CRC_CalcBlockCRC() function to compute the CRC if a 32-bit 
             data buffer
            (@) To compute the CRC of a new data use CRC_ResetDR() to reset
                 the CRC computation unit before starting the computation
                 otherwise you can get wrong CRC values.
      
     @endverbatim
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_crc.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC 
  * @brief CRC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRC_Private_Functions
  * @{
  */

/** @defgroup CRC_Group1 Configuration of the CRC computation unit functions
 *  @brief   Configuration of the CRC computation unit functions 
 *
@verbatim
 ===============================================================================
                     ##### CRC configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRC_DeInit(void)
{
  /* Set DR register to reset value */
  CRC->DR = 0xFFFFFFFF;
  /* Reset IDR register */
  CRC->IDR = 0x00;
  /* Set INIT register to reset value */
  CRC->INIT = 0xFFFFFFFF;
  /* Reset the CRC calculation unit */
  CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Resets the CRC calculation unit and sets INIT register content in DR register.
  * @param  None
  * @retval None
  */
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Selects the reverse operation to be performed on input data.
  * @param  CRC_ReverseInputData: Specifies the reverse operation on input data.
  *         This parameter can be:
  *      @arg CRC_ReverseInputData_No: No reverse operation is performed
  *      @arg CRC_ReverseInputData_8bits: reverse operation performed on 8 bits
  *      @arg CRC_ReverseInputData_16bits: reverse operation performed on 16 bits
  *      @arg CRC_ReverseInputData_32bits: reverse operation performed on 32 bits
  * @retval None
  */
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_REVERSE_INPUT_DATA(CRC_ReverseInputData));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset REV_IN bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_REV_IN);
  /* Set the reverse operation */
  tmpcr |= (uint32_t)CRC_ReverseInputData;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}

/**
  * @brief  Enables or disable the reverse operation on output data.
  *         The reverse operation on output data is performed on 32-bit.
  * @param  NewState: new state of the reverse operation on output data.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRC_ReverseOutputDataCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable reverse operation on output data */
    CRC->CR |= CRC_CR_REV_OUT;
  }
  else
  {
    /* Disable reverse operation on output data */
    CRC->CR &= (uint32_t)~((uint32_t)CRC_CR_REV_OUT);
  }
}

/**
  * @brief  Initializes the INIT register.
  * @note   After resetting CRC calculation unit, CRC_InitValue is stored in DR register
  * @param  CRC_InitValue: Programmable initial CRC value
  * @retval None
  */
void CRC_SetInitRegister(uint32_t CRC_InitValue)
{
  CRC->INIT = CRC_InitValue;
}

/**
  * @}
  */

/** @defgroup CRC_Group2 CRC computation of one/many 32-bit data functions
 *  @brief   CRC computation of one/many 32-bit data functions
 *
@verbatim
 ===============================================================================
                     ##### CRC computation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRC_Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t CRC_Data)
{
  CRC->DR = CRC_Data;
  
  return (CRC->DR);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }
  return (CRC->DR);
}

/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @retval 32-bit CRC
  */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DR);
}

/**
  * @}
  */

/** @defgroup CRC_Group3 CRC Independent Register (IDR) access functions
 *  @brief   CRC Independent Register (IDR) access (write/read) functions
 *
@verbatim
 ===============================================================================
           ##### CRC Independent Register (IDR) access functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Stores an 8-bit data in the Independent Data(ID) register.
  * @param  CRC_IDValue: 8-bit value to be stored in the ID register 					
  * @retval None
  */
void CRC_SetIDRegister(uint8_t CRC_IDValue)
{
  CRC->IDR = CRC_IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @param  None
  * @retval 8-bit value of the ID register 
  */
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDR);
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
