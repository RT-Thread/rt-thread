/**
  ******************************************************************************
  * @file    stm324x9i_eval_nor.c
  * @author  MCD Application Team
  * @version V2.2.1
  * @date    07-October-2015
  * @brief   This file includes a standard driver for the M29W256GL70ZA6E NOR flash memory 
  *          device mounted on STM324x9I-EVAL evaluation board.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive the M29W128GL NOR flash external memory mounted
     on STM324x9I-EVAL evaluation board.
   - This driver does not need a specific component driver for the NOR device
     to be included with.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the NOR external memory using the BSP_NOR_Init() function. This 
       function includes the MSP layer hardware resources initialization and the
       FMC controller configuration to interface with the external NOR memory.
  
  + NOR flash operations
     o NOR external memory can be accessed with read/write operations once it is
       initialized.
       Read/write operation can be performed with AHB access using the functions
       BSP_NOR_ReadData()/BSP_NOR_WriteData(). The BSP_NOR_WriteData() performs write operation
       of an amount of data by unit (halfword). You can also perform a program data
       operation of an amount of data using the function BSP_NOR_ProgramData().
     o The function BSP_NOR_Read_ID() returns the chip IDs stored in the structure 
       "NOR_IDTypeDef". (see the NOR IDs in the memory data sheet)
     o Perform erase block operation using the function BSP_NOR_Erase_Block() and by
       specifying the block address. You can perform an erase operation of the whole 
       chip by calling the function BSP_NOR_Erase_Chip(). 
     o After other operations, the function BSP_NOR_ReturnToReadMode() allows the NOR 
       flash to return to read mode to perform read operations on it. 
 
------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm324x9i_eval_nor.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324x9I_EVAL
  * @{
  */ 
  
/** @defgroup STM324x9I_EVAL_NOR
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/

/** @defgroup STM324x9I_EVAL_NOR_Private_Types_Definitions
  * @{
  */ 
  
/* Private define ------------------------------------------------------------*/

/** @defgroup STM324x9I_EVAL_NOR_Private_Defines
  * @{
  */
  
/* Private macro -------------------------------------------------------------*/

/** @defgroup STM324x9I_EVAL_NOR_Private_Macros
  * @{
  */  
  
/* Private variables ---------------------------------------------------------*/

/** @defgroup STM324x9I_EVAL_NOR_Private_Variables
  * @{
  */       
static NOR_HandleTypeDef norHandle;
static FMC_NORSRAM_TimingTypeDef Timing;

/**
  * @}
  */ 

/* Private function prototypes -----------------------------------------------*/

/** @defgroup STM324x9I_EVAL_NOR_Private_Function_Prototypes
  * @{
  */ 
 
/* Private functions ---------------------------------------------------------*/
    
/** @defgroup STM324x9I_EVAL_NOR_Private_Functions
  * @{
  */ 
static void NOR_MspInit(void);

/**
  * @}
  */
    
/**
  * @brief  Initializes the NOR device.
  * @param  None
  * @retval NOR memory status
  */
uint8_t BSP_NOR_Init(void)
{ 
  norHandle.Instance  = FMC_NORSRAM_DEVICE;
  norHandle.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;
  
  /* NOR device configuration */  
  Timing.AddressSetupTime      = 4;
  Timing.AddressHoldTime       = 3;
  Timing.DataSetupTime         = 7;
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision           = 2;
  Timing.DataLatency           = 2;
  Timing.AccessMode            = FMC_ACCESS_MODE_A;
  
  norHandle.Init.NSBank             = FMC_NORSRAM_BANK1;
  norHandle.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  norHandle.Init.MemoryType         = FMC_MEMORY_TYPE_NOR;
  norHandle.Init.MemoryDataWidth    = NOR_MEMORY_WIDTH;
  norHandle.Init.BurstAccessMode    = NOR_BURSTACCESS;
  norHandle.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  norHandle.Init.WrapMode           = FMC_WRAP_MODE_DISABLE;
  norHandle.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  norHandle.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  norHandle.Init.WaitSignal         = FMC_WAIT_SIGNAL_ENABLE;
  norHandle.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  norHandle.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_ENABLE;
  norHandle.Init.WriteBurst         = NOR_WRITEBURST;
  norHandle.Init.ContinuousClock    = CONTINUOUSCLOCK_FEATURE;
    
  /* NOR controller initialization */
  NOR_MspInit();
  
  if(HAL_NOR_Init(&norHandle, &Timing, &Timing) != HAL_OK)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  }
}

/**
  * @brief  Reads an amount of data from the NOR device.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of data to read    
  * @retval NOR memory status
  */
uint8_t BSP_NOR_ReadData(uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  if(HAL_NOR_ReadBuffer(&norHandle, NOR_DEVICE_ADDR + uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  }
}

/**
  * @brief  Returns the NOR memory to read mode.
  * @param  None 
  * @retval None
  */
void BSP_NOR_ReturnToReadMode(void)
{
   HAL_NOR_ReturnToReadMode(&norHandle);
}

/**
  * @brief  Writes an amount of data to the NOR device.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of data to write    
  * @retval NOR memory status
  */
uint8_t BSP_NOR_WriteData(uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  uint32_t index = uwDataSize;
  
  while(index > 0)
  {
    /* Write data to NOR */
    HAL_NOR_Program(&norHandle, (uint32_t *)(NOR_DEVICE_ADDR + uwStartAddress), pData);
    
    /* Read NOR device status */
    if(HAL_NOR_GetStatus(&norHandle, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT) != NOR_SUCCESS)
    {
      return NOR_STATUS_ERROR;
    }
    
    /* Update the counters */
    index--;
    uwStartAddress += 2;
    pData++; 
  }
  
  return NOR_STATUS_OK;
}

/**
  * @brief  Programs an amount of data to the NOR device.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of data to write    
  * @retval NOR memory status
  */
uint8_t BSP_NOR_ProgramData(uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  /* Send NOR program buffer operation */
  HAL_NOR_ProgramBuffer(&norHandle, uwStartAddress, pData, uwDataSize);
  
  /* Return the NOR memory status */
  if(HAL_NOR_GetStatus(&norHandle, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT) != NOR_SUCCESS)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  }
}

/**
  * @brief  Erases the specified block of the NOR device. 
  * @param  BlockAddress: Block address to erase  
  * @retval NOR memory status
  */
uint8_t BSP_NOR_Erase_Block(uint32_t BlockAddress)
{
  /* Send NOR erase block operation */
  HAL_NOR_Erase_Block(&norHandle, BlockAddress, NOR_DEVICE_ADDR);
  
  /* Return the NOR memory status */  
  if(HAL_NOR_GetStatus(&norHandle, NOR_DEVICE_ADDR, BLOCKERASE_TIMEOUT) != NOR_SUCCESS)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  }
}

/**
  * @brief  Erases the entire NOR chip.
  * @param  None
  * @retval NOR memory status
  */
uint8_t BSP_NOR_Erase_Chip(void)
{
  /* Send NOR Erase chip operation */
  HAL_NOR_Erase_Chip(&norHandle, NOR_DEVICE_ADDR);
  
  /* Return the NOR memory status */
  if(HAL_NOR_GetStatus(&norHandle, NOR_DEVICE_ADDR, CHIPERASE_TIMEOUT) != NOR_SUCCESS)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  } 
}

/**
  * @brief  Reads NOR flash IDs.
  * @param  pNOR_ID : Pointer to NOR ID structure
  * @retval NOR memory status
  */
uint8_t BSP_NOR_Read_ID(NOR_IDTypeDef *pNOR_ID)
{
  if(HAL_NOR_Read_ID(&norHandle, pNOR_ID) != HAL_OK)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  }
}

/**
  * @brief  Initializes the NOR MSP.
  * @param  None
  * @retval None
  */
static void NOR_MspInit(void)
{
  GPIO_InitTypeDef GPIO_Init_Structure;
  
  /* Enable FMC clock */
  __FMC_CLK_ENABLE();

  /* Enable GPIOs clock */
  __GPIOD_CLK_ENABLE();
  __GPIOE_CLK_ENABLE();
  __GPIOF_CLK_ENABLE();
  __GPIOG_CLK_ENABLE();
  
  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_HIGH;
  GPIO_Init_Structure.Alternate = GPIO_AF12_FMC;
  
  /* GPIOD configuration */
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6   |\
                              GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* GPIOE configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6   |\
                              GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);
  
  /* GPIOF configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);
  
  /* GPIOG configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5;
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure); 
}

/**
  * @brief  NOR BSP Wait for Ready/Busy signal.
  * @param  hnor: Pointer to NOR handle
  * @param  Timeout: Timeout duration  
  * @retval None
  */
void HAL_NOR_MspWait(NOR_HandleTypeDef *hnor, uint32_t Timeout)
{
  uint32_t timeout = Timeout;
  
  /* Polling on Ready/Busy signal */
  while((HAL_GPIO_ReadPin(NOR_READY_BUSY_GPIO, NOR_READY_BUSY_PIN) != NOR_BUSY_STATE) && (timeout > 0)) 
  {
    timeout--;
  }
  
  timeout = Timeout;
  
  /* Polling on Ready/Busy signal */
  while((HAL_GPIO_ReadPin(NOR_READY_BUSY_GPIO, NOR_READY_BUSY_PIN) != NOR_READY_STATE) && (timeout > 0)) 
  {
    timeout--;
  }  
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
