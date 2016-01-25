/**
  ******************************************************************************
  * @file    stm32469i_eval_sram.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file includes the SRAM driver for the IS61WV102416BLL-10M memory
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
   - This driver is used to drive the IS61WV102416BLL-10M SRAM external memory mounted
     on STM32469I-EVAL evaluation board.
   - This driver does not need a specific component driver for the SRAM device
     to be included with.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the SRAM external memory using the BSP_SRAM_Init() function. This
       function includes the MSP layer hardware resources initialization and the
       FMC controller configuration to interface with the external SRAM memory.

  + SRAM read/write operations
     o SRAM external memory can be accessed with read/write operations once it is
       initialized.
       Read/write operation can be performed with AHB access using the functions
       BSP_SRAM_ReadData()/BSP_SRAM_WriteData(), or by DMA transfer using the functions
       BSP_SRAM_ReadData_DMA()/BSP_SRAM_WriteData_DMA().
     o The AHB access is performed with 16-bit width transaction, the DMA transfer
       configuration is fixed at single (no burst) halfword transfer
       (see the BSP_SRAM_MspInit() __weak function). This function BSP_SRAM_MspInit()
       can be surcharged by application code above BSP.
     o User can implement his own functions for read/write access with his desired
       configurations.
     o If interrupt mode is used for DMA transfer, the function BSP_SRAM_DMA_IRQHandler()
       is called in IRQ handler file, to serve the generated interrupt once the DMA
       transfer is complete.

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32469i_eval_sram.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-EVAL
  * @{
  */

/** @defgroup STM32469I-EVAL_SRAM STM32469I-EVAL SRAM
  * @{
  */

/** @defgroup STM32469I-EVAL_SRAM_Private_Types_Definitions STM32469I-EVAL SRAM Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_SRAM_Private_Defines STM32469I-EVAL Private Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_SRAM_Private_Macros STM32469I-EVAL Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_SRAM_Private_Variables STM32469I-EVAL Private Variables
  * @{
  */
static SRAM_HandleTypeDef sramHandle;
static FMC_NORSRAM_TimingTypeDef Timing;
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_SRAM_Private_Function_Prototypes STM32469I-EVAL Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32469I-EVAL_SRAM_Private_Functions STM32469I-EVAL Private Functions
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32469I-EVAL_SRAM_Exported_Functions STM32469I-EVAL Exported Functions
  * @{
  */

/**
  * @brief  Initializes the SRAM device.
  * @retval SRAM status
  */
uint8_t BSP_SRAM_Init(void)
{
  sramHandle.Instance = FMC_NORSRAM_DEVICE;
  sramHandle.Extended = FMC_NORSRAM_EXTENDED_DEVICE;

  /* SRAM device configuration */
  Timing.AddressSetupTime      = 2;
  Timing.AddressHoldTime       = 1;
  Timing.DataSetupTime         = 2;
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision           = 2;
  Timing.DataLatency           = 2;
  Timing.AccessMode            = FMC_ACCESS_MODE_A;

  sramHandle.Init.NSBank             = FMC_NORSRAM_BANK2;
  sramHandle.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  sramHandle.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;
  sramHandle.Init.MemoryDataWidth    = SRAM_MEMORY_WIDTH;
  sramHandle.Init.BurstAccessMode    = SRAM_BURSTACCESS;
  sramHandle.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  sramHandle.Init.WrapMode           = FMC_WRAP_MODE_DISABLE;
  sramHandle.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  sramHandle.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  sramHandle.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;
  sramHandle.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  sramHandle.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  sramHandle.Init.WriteBurst         = SRAM_WRITEBURST;
  sramHandle.Init.ContinuousClock    = CONTINUOUSCLOCK_FEATURE;

  /* SRAM controller initialization */
  /* __weak function can be surcharged by the application code */
  BSP_SRAM_MspInit(&sramHandle, (void*)NULL);
  if(HAL_SRAM_Init(&sramHandle, &Timing, &Timing) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  DeInitializes the SRAM device.
  * @retval SRAM status : SRAM_OK or SRAM_ERROR.
  */
uint8_t BSP_SRAM_DeInit(void)
{
  static uint8_t sramstatus = SRAM_ERROR;

  /* SRAM device configuration */
  sramHandle.Instance = FMC_NORSRAM_DEVICE;

  if(HAL_SRAM_DeInit(&sramHandle) == HAL_OK)
  {
    sramstatus = SRAM_OK;

  /* SRAM controller De-initialization */
    BSP_SRAM_MspDeInit(&sramHandle, (void *)NULL);
  }

  return sramstatus;
}

/**
  * @brief  Reads an amount of data from the SRAM device in polling mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory
  * @retval SRAM status : SRAM_OK or SRAM_ERROR.
  */
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  if(HAL_SRAM_Read_16b(&sramHandle, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Reads an amount of data from the SRAM device in DMA mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory
  * @retval SRAM status : SRAM_OK or SRAM_ERROR.
  */
uint8_t BSP_SRAM_ReadData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  if(HAL_SRAM_Read_DMA(&sramHandle, (uint32_t *)uwStartAddress, (uint32_t *)pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Writes an amount of data from the SRAM device in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory
  * @retval SRAM status : SRAM_OK or SRAM_ERROR.
  */
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  if(HAL_SRAM_Write_16b(&sramHandle, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Writes an amount of data from the SRAM device in DMA mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory
  * @retval SRAM status : SRAM_OK or SRAM_ERROR.
  */
uint8_t BSP_SRAM_WriteData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  if(HAL_SRAM_Write_DMA(&sramHandle, (uint32_t *)uwStartAddress, (uint32_t *)pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Handles SRAM DMA transfer interrupt request.
  */
void BSP_SRAM_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(sramHandle.hdma);
}

/**
  * @brief  Initializes SRAM MSP.
  * @note   This function can be surcharged by application code.
  * @param  hsram  : pointer on SRAM handle
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_SRAM_MspInit(SRAM_HandleTypeDef *hsram, void *Params)
{
  static DMA_HandleTypeDef dma_handle;
  GPIO_InitTypeDef         gpio_init_structure;

  if(hsram != (SRAM_HandleTypeDef *)NULL)
  {
    /* Enable FMC clock */
    __HAL_RCC_FMC_CLK_ENABLE();

    /* Enable chosen DMAx clock */
    __SRAM_DMAx_CLK_ENABLE();

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
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 |\
                            GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |\
                            GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &gpio_init_structure);

    /* GPIOE configuration */
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3| GPIO_PIN_4 | GPIO_PIN_7     |\
                            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
                            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &gpio_init_structure);

    /* GPIOF configuration */
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                            GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &gpio_init_structure);

    /* GPIOG configuration */
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                            GPIO_PIN_5 | GPIO_PIN_9;
    HAL_GPIO_Init(GPIOG, &gpio_init_structure);

    /* Configure common DMA parameters */
    dma_handle.Init.Channel             = SRAM_DMAx_CHANNEL;
    dma_handle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
    dma_handle.Init.PeriphInc           = DMA_PINC_ENABLE;
    dma_handle.Init.MemInc              = DMA_MINC_ENABLE;
    dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    dma_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    dma_handle.Init.Mode                = DMA_NORMAL;
    dma_handle.Init.Priority            = DMA_PRIORITY_HIGH;
    dma_handle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    dma_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    dma_handle.Init.MemBurst            = DMA_MBURST_SINGLE;
    dma_handle.Init.PeriphBurst         = DMA_PBURST_SINGLE;

    dma_handle.Instance = SRAM_DMAx_STREAM;

    /* Associate the DMA handle */
    __HAL_LINKDMA(hsram, hdma, dma_handle);

    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&dma_handle);

    /* Configure the DMA Stream */
    HAL_DMA_Init(&dma_handle);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(SRAM_DMAx_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(SRAM_DMAx_IRQn);

  } /* of if(hsram != (SRAM_HandleTypeDef *)NULL) */
}

/**
  * @brief  DeInitializes SRAM MSP.
  * @note   This function can be surcharged by application code.
  * @param  hsram : pointer on SRAM handle
  * @param  Params: pointer on additional configuration parameters, can be NULL.
  * @retval None
  */
__weak void BSP_SRAM_MspDeInit(SRAM_HandleTypeDef *hsram, void *Params)
{
    static DMA_HandleTypeDef dma_handle;

    if(hsram != (SRAM_HandleTypeDef  *)NULL)
    {
      /* Disable NVIC configuration for DMA interrupt */
      HAL_NVIC_DisableIRQ(SRAM_DMAx_IRQn);

      /* Deinitialize the stream for new transfer */
      dma_handle.Instance = SRAM_DMAx_STREAM;
      HAL_DMA_DeInit(&dma_handle);

      /* DeInit GPIO pins can be done in the application
       (by surcharging this __weak function) */

      /* GPIO pins clock, FMC clock and DMA clock can be shut down in the application
       by surcharging this __weak function */

    } /* of if(hsram != (SRAM_HandleTypeDef  *)NULL) */
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
