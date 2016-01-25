/**
  ******************************************************************************
  * @file    stm32469i_eval_nor.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file includes a standard driver for the M29W256GL70ZA6E NOR flash memory
  *          device mounted on STM32469I-EVAL evaluation board.
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
     on STM32469I-EVAL evaluation board.
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
#include "stm32469i_eval_nor.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-EVAL
  * @{
  */

/** @defgroup STM32469I-EVAL_NOR STM32469I-EVAL NOR
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup STM32469I-EVAL_NOR_Private_Types_Definitions STM32469I-EVAL NOR Private Types Definitions
  * @{
  */

/* Private define ------------------------------------------------------------*/

/** @defgroup STM32469I-EVAL_NOR_Private_Defines STM32469I-EVAL NOR Private Defines
  * @{
  */

/* Private macro -------------------------------------------------------------*/

/** @defgroup STM32469I-EVAL_NOR_Private_Macros STM32469I-EVAL NOR Private Macros
  * @{
  */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32469I-EVAL_NOR_Private_Variables STM32469I-EVAL NOR Private Variables
  * @{
  */
NOR_HandleTypeDef NorHandle;
static FMC_NORSRAM_TimingTypeDef Timing;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup STM32469I-EVAL_NOR_Private_Function_Prototypes STM32469I-EVAL NOR Private Function Prototypes
  * @{
  */



/**
  * @}
  */

/**
  * @brief  Initializes the NOR device.
  * @retval NOR memory status
  */
uint8_t BSP_NOR_Init(void)
{
  NorHandle.Instance  = FMC_NORSRAM_DEVICE;
  NorHandle.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;

  /* NOR device configuration */
  Timing.AddressSetupTime      = 8;
  Timing.AddressHoldTime       = 3;
  Timing.DataSetupTime         = 9;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision           = 2;
  Timing.DataLatency           = 2;
  Timing.AccessMode            = FMC_ACCESS_MODE_A;

  NorHandle.Init.NSBank             = FMC_NORSRAM_BANK1;
  NorHandle.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  NorHandle.Init.MemoryType         = FMC_MEMORY_TYPE_NOR;
  NorHandle.Init.MemoryDataWidth    = NOR_MEMORY_WIDTH;
  NorHandle.Init.BurstAccessMode    = NOR_BURSTACCESS;
  NorHandle.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  NorHandle.Init.WrapMode           = FMC_WRAP_MODE_DISABLE;
  NorHandle.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  NorHandle.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  NorHandle.Init.WaitSignal         = FMC_WAIT_SIGNAL_ENABLE;
  NorHandle.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  NorHandle.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_ENABLE;
  NorHandle.Init.WriteBurst         = NOR_WRITEBURST;
  NorHandle.Init.ContinuousClock    = CONTINUOUSCLOCK_FEATURE;

  /* NOR controller initialization */
  BSP_NOR_MspInit(&NorHandle, NULL);

  if(HAL_NOR_Init(&NorHandle, &Timing, &Timing) != HAL_OK)
  {
    return NOR_STATUS_ERROR;
  }
  else
  {
    return NOR_STATUS_OK;
  }
}

/**
  * @brief  DeInitializes the NOR device.
  * @retval NOR memory status
  */
uint8_t BSP_NOR_DeInit(void)
{
  /* NOR controller initialization */
  BSP_NOR_MspDeInit(&NorHandle, NULL);

  if(HAL_NOR_DeInit(&NorHandle) != HAL_OK)
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
  if(HAL_NOR_ReadBuffer(&NorHandle, NOR_DEVICE_ADDR + uwStartAddress, pData, uwDataSize) != HAL_OK)
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
  */
void BSP_NOR_ReturnToReadMode(void)
{
   HAL_NOR_ReturnToReadMode(&NorHandle);
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
    HAL_NOR_Program(&NorHandle, (uint32_t *)(NOR_DEVICE_ADDR + uwStartAddress), pData);

    /* Read NOR device status */
    if(HAL_NOR_GetStatus(&NorHandle, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
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
  HAL_NOR_ProgramBuffer(&NorHandle, uwStartAddress, pData, uwDataSize);

  /* Return the NOR memory status */
  if(HAL_NOR_GetStatus(&NorHandle, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
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
  HAL_NOR_Erase_Block(&NorHandle, BlockAddress, NOR_DEVICE_ADDR);

  /* Return the NOR memory status */
  if(HAL_NOR_GetStatus(&NorHandle, NOR_DEVICE_ADDR, BLOCKERASE_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
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
  * @retval NOR memory status
  */
uint8_t BSP_NOR_Erase_Chip(void)
{
  /* Send NOR Erase chip operation */
  HAL_NOR_Erase_Chip(&NorHandle, NOR_DEVICE_ADDR);

  /* Return the NOR memory status */
  if(HAL_NOR_GetStatus(&NorHandle, NOR_DEVICE_ADDR, CHIPERASE_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
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
  if(HAL_NOR_Read_ID(&NorHandle, pNOR_ID) != HAL_OK)
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
  * @param  hnor: pointer to nor structure
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_NOR_MspInit(NOR_HandleTypeDef *hnor, void *Params)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF12_FMC;

  /* GPIOD configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6   |\
                              GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* GPIOE configuration */
  gpio_init_structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6   |\
                              GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);

  /* GPIOF configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);

  /* GPIOG configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5;
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);
}

/**
  * @brief  DeInitializes the NOR MSP.
  * @param  hnor pointer to NOR structure
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  * @retval status
  */
__weak uint8_t BSP_NOR_MspDeInit(NOR_HandleTypeDef *hnor, void *Params)
{
  /* FMC won't be disabled because common to other functionalities */

  /* Disable only NOR specific GPIOs */
  HAL_GPIO_DeInit(GPIOD, (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));

  return HAL_OK;

}

/**
  * @brief  NOR BSP Wait for Ready/Busy signal.
  * @param  hnor: Pointer to NOR handle
  * @param  Timeout: Timeout duration
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

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
