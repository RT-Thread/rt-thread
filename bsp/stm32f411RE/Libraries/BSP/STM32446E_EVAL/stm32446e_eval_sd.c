/**
  ******************************************************************************
  * @file    stm32446e_eval_sd.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file includes the uSD card driver mounted on STM32446E-EVAL
  *          evaluation board.
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
   - This driver is used to drive the micro SD external card mounted on STM32446E-EVAL
     evaluation board.
   - This driver does not need a specific component driver for the micro SD device
     to be included with.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the micro SD card using the BSP_SD_Init() function. This 
       function includes the MSP layer hardware resources initialization and the
       SDIO interface configuration to interface with the external micro SD. It 
       also includes the micro SD initialization sequence.
     o To check the SD card presence you can use the function BSP_SD_IsDetected() which 
       returns the detection status 
     o If SD presence detection interrupt mode is desired, you must configure the 
       SD detection interrupt mode by calling the function BSP_SD_ITConfig(). The interrupt 
       is generated as an external interrupt whenever the micro SD card is 
       plugged/unplugged in/from the evaluation board. The SD detection interrupt
       is handled by calling the function BSP_SD_DetectIT() which is called in the IRQ
       handler file, the user callback is implemented in the function BSP_SD_DetectCallback().
     o The function BSP_SD_GetCardInfo() is used to get the micro SD card information 
       which is stored in the structure "HAL_SD_CardInfoTypedef".
  
  + Micro SD card operations
     o The micro SD card can be accessed with read/write block(s) operations once 
       it is ready for access. The access can be performed whether using the polling 
       mode by calling the functions BSP_SD_ReadBlocks()/BSP_SD_WriteBlocks(), or by DMA 
       transfer using the functions BSP_SD_ReadBlocks_DMA()/BSP_SD_WriteBlocks_DMA()
     o The DMA transfer complete is used with interrupt mode. Once the SD transfer
       is complete, the SD interrupt is handled using the function BSP_SD_IRQHandler(),
       the DMA Tx/Rx transfer complete are handled using the functions
       BSP_SD_DMA_Tx_IRQHandler()/BSP_SD_DMA_Rx_IRQHandler(). The corresponding user callbacks 
       are implemented by the user at application level. 
     o The SD erase block(s) is performed using the function BSP_SD_Erase() with specifying
       the number of blocks to erase.
     o The SD runtime status is returned when calling the function BSP_SD_GetStatus().
 
------------------------------------------------------------------------------*/ 

/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval_sd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32446E_EVAL
  * @{
  */ 
  
/** @defgroup STM32446E_EVAL_SD STM32446E-EVAL SD
  * @{
  */ 


/** @defgroup STM32446E_EVAL_SD_Private_TypesDefinitions STM32446E Eval Sd Private TypesDef
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_SD_Private_Defines STM32446E Eval Sd Private Defines
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM32446E_EVAL_SD_Private_Macros STM32446E Eval Sd Private Macro
  * @{
  */    
/**
  * @}
  */  

/** @defgroup STM32446E_EVAL_SD_Private_Variables STM32446E Eval Sd Private Variables
  * @{
  */
static SD_HandleTypeDef uSdHandle;
static SD_CardInfo uSdCardInfo;
static uint8_t UseExtiModeDetection = 0;

/**
  * @}
  */ 
  
/** @defgroup STM32446E_EVAL_SD_Private_FunctionPrototypes STM32446E Eval Sd Private Prototypes
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM32446E_EVAL_SD_Private_Functions STM32446E Eval Sd Private Functions
  * @{
  */

/**
  * @brief  Initializes the SD card device.
  * @param  None
  * @retval SD status
  */
uint8_t BSP_SD_Init(void)
{ 
  uint8_t sd_state = MSD_OK;
  
  /* uSD device interface configuration */
  uSdHandle.Instance = SDIO;

  uSdHandle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
  uSdHandle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
  uSdHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
  uSdHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
  uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_ENABLE;
  uSdHandle.Init.ClockDiv            = SDIO_TRANSFER_CLK_DIV;
  
  /* Initialize IO functionalities (MFX) used by SD detect pin */
  BSP_IO_Init(); 
  
  /* Check if the SD card is plugged in the slot */
  BSP_IO_ConfigPin(SD_DETECT_PIN, IO_MODE_INPUT);
  if(BSP_SD_IsDetected() != SD_PRESENT)
  {
    return MSD_ERROR_SD_NOT_PRESENT;
  }
  
  /* Msp SD initialization */
  BSP_SD_MspInit(&uSdHandle, NULL);

  /* HAL SD initialization */
  if(HAL_SD_Init(&uSdHandle, &uSdCardInfo) != SD_OK)
  {
    sd_state = MSD_ERROR;
  }
  
  /* Configure SD Bus width */
  if(sd_state == MSD_OK)
  {
    /* Enable wide operation */
    if(HAL_SD_WideBusOperation_Config(&uSdHandle, SDIO_BUS_WIDE_4B) != SD_OK)
    {
      sd_state = MSD_ERROR;
    }
    else
    {
      sd_state = MSD_OK;
    }
  }
  
  return  sd_state;
}

/**
  * @brief  DeInitializes the SD card device.
  * @param  None
  * @retval SD status
  */
uint8_t BSP_SD_DeInit(void)
{ 
  uint8_t sd_state = MSD_OK;
 
  uSdHandle.Instance = SDIO;
  
  /* Set back Mfx pin to INPUT mode in case it was in exti */
  UseExtiModeDetection = 0;
  BSP_IO_ConfigPin(SD_DETECT_PIN, IO_MODE_INPUT);

  /* HAL SD deinitialization */
  if(HAL_SD_DeInit(&uSdHandle) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  /* Msp SD deinitialization */
  uSdHandle.Instance = SDIO;
  BSP_SD_MspDeInit(&uSdHandle, NULL);
  
  return  sd_state;
}

/**
  * @brief  Configures Interrupt mode for SD detection pin.
  * @param  None
  * @retval Returns 0
  */
uint8_t BSP_SD_ITConfig(void)
{  
  /* Configure Interrupt mode for SD detection pin */  
  /* Note: disabling exti mode can be done calling SD_DeInit() */
  UseExtiModeDetection = 1;  
  BSP_SD_IsDetected();

  return 0;
}

/**
 * @brief  Detects if SD card is correctly plugged in the memory slot or not.
 * @param  None
 * @retval Returns if SD is detected or not
 */
uint8_t BSP_SD_IsDetected(void)
{
  __IO uint8_t status = SD_PRESENT;
  
  /* Check SD card detect pin */
  if((BSP_IO_ReadPin(SD_DETECT_PIN)&SD_DETECT_PIN) != SD_DETECT_PIN)
  {
     if (UseExtiModeDetection)
     {
      BSP_IO_ConfigPin(SD_DETECT_PIN, IO_MODE_IT_RISING_EDGE);
     }

  }
  else
  {
    status = SD_NOT_PRESENT;
    if (UseExtiModeDetection)
    {
      BSP_IO_ConfigPin(SD_DETECT_PIN, IO_MODE_IT_FALLING_EDGE);
    }
  }
 
  return status;
}



/**
  * @brief  Reads block(s) from a specified address in an SD card, in polling mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  ReadAddr: Address from where data is to be read  
  * @param  BlockSize: SD card data block size, that should be 512
  * @param  NumOfBlocks: Number of SD blocks to read 
  * @retval SD status
  */
uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint64_t ReadAddr, uint32_t BlockSize, uint32_t NumOfBlocks)
{
  if(HAL_SD_ReadBlocks(&uSdHandle, pData, ReadAddr, BlockSize, NumOfBlocks) != SD_OK)
  {
    return MSD_ERROR;
  }
  else
  {
    return MSD_OK;
  }
}

/**
  * @brief  Writes block(s) to a specified address in an SD card, in polling mode. 
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  WriteAddr: Address from where data is to be written  
  * @param  BlockSize: SD card data block size, that should be 512
  * @param  NumOfBlocks: Number of SD blocks to write
  * @retval SD status
  */
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint64_t WriteAddr, uint32_t BlockSize, uint32_t NumOfBlocks)
{
  if(HAL_SD_WriteBlocks(&uSdHandle, pData, WriteAddr, BlockSize, NumOfBlocks) != SD_OK)
  {
    return MSD_ERROR;
  }
  else
  {
    return MSD_OK;
  }
}

/**
  * @brief  Reads block(s) from a specified address in an SD card, in DMA mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  ReadAddr: Address from where data is to be read  
  * @param  BlockSize: SD card data block size, that should be 512
  * @param  NumOfBlocks: Number of SD blocks to read 
  * @retval SD status
  */
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint64_t ReadAddr, uint32_t BlockSize, uint32_t NumOfBlocks)
{
  uint8_t sd_state = MSD_OK;
  
  /* Read block(s) in DMA transfer mode */
  if(HAL_SD_ReadBlocks_DMA(&uSdHandle, pData, ReadAddr, BlockSize, NumOfBlocks) != SD_OK)
  {
    sd_state = MSD_ERROR;
  }
  
  /* Wait until transfer is complete */
  if(sd_state == MSD_OK)
  {
    if(HAL_SD_CheckReadOperation(&uSdHandle, (uint32_t)SD_DATATIMEOUT) != SD_OK)
    {
      sd_state = MSD_ERROR;
    }
    else
    {
      sd_state = MSD_OK;
    }
  }
  
  return sd_state; 
}

/**
  * @brief  Writes block(s) to a specified address in an SD card, in DMA mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  WriteAddr: Address from where data is to be written  
  * @param  BlockSize: SD card data block size, that should be 512
  * @param  NumOfBlocks: Number of SD blocks to write 
  * @retval SD status
  */
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint64_t WriteAddr, uint32_t BlockSize, uint32_t NumOfBlocks)
{
  uint8_t sd_state = MSD_OK;
  
  /* Write block(s) in DMA transfer mode */
  if(HAL_SD_WriteBlocks_DMA(&uSdHandle, pData, WriteAddr, BlockSize, NumOfBlocks) != SD_OK)
  {
    sd_state = MSD_ERROR;
  }
  
  /* Wait until transfer is complete */
  if(sd_state == MSD_OK)
  {
    if(HAL_SD_CheckWriteOperation(&uSdHandle, (uint32_t)SD_DATATIMEOUT) != SD_OK)
    {
      sd_state = MSD_ERROR;
    }
    else
    {
      sd_state = MSD_OK;
    }
  }
  
  return sd_state;  
}

/**
  * @brief  Erases the specified memory area of the given SD card. 
  * @param  StartAddr: Start byte address
  * @param  EndAddr: End byte address
  * @retval SD status
  */
uint8_t BSP_SD_Erase(uint64_t StartAddr, uint64_t EndAddr)
{
  if(HAL_SD_Erase(&uSdHandle, StartAddr, EndAddr) != SD_OK)
  {
    return MSD_ERROR;
  }
  else
  {
    return MSD_OK;
  }
}

/**
  * @brief  Initializes the SD MSP.
  * @param  hsd: SD handle
  * @retval None
  */
__weak void BSP_SD_MspInit(SD_HandleTypeDef *hsd, void *Params)
{
  static DMA_HandleTypeDef dma_rx_handle;
  static DMA_HandleTypeDef dma_tx_handle;
  GPIO_InitTypeDef gpio_init_structure;

  /* SD pins are in conflict with Camera pins therefore Camera is power down */
  /* __weak function can be modified by the application */
  BSP_IO_ConfigPin(RSTI_PIN, IO_MODE_OUTPUT);
  BSP_IO_ConfigPin(XSDN_PIN, IO_MODE_OUTPUT);
  /* De-assert the camera STANDBY pin (active high) */
  BSP_IO_WritePin(XSDN_PIN, BSP_IO_PIN_RESET);
  /* Assert the camera RSTI pin (active low) */
  BSP_IO_WritePin(RSTI_PIN, BSP_IO_PIN_RESET);
  HAL_Delay(100);
  
  /* Enable SDIO clock */
  __HAL_RCC_SDIO_CLK_ENABLE();
  
  /* Enable DMA2 clocks */
  __DMAx_TxRx_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  
  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF12_SDIO;
  
  /* GPIOC configuration */
  gpio_init_structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
   
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);

  /* GPIOD configuration */
  gpio_init_structure.Pin = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* NVIC configuration for SDIO interrupts */
  HAL_NVIC_SetPriority(SDIO_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(SDIO_IRQn);
    
  /* Configure DMA Rx parameters */
  dma_rx_handle.Init.Channel             = SD_DMAx_Rx_CHANNEL;
  dma_rx_handle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  dma_rx_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
  dma_rx_handle.Init.MemInc              = DMA_MINC_ENABLE;
  dma_rx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dma_rx_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dma_rx_handle.Init.Mode                = DMA_PFCTRL;
  dma_rx_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
  dma_rx_handle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  dma_rx_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dma_rx_handle.Init.MemBurst            = DMA_MBURST_INC4;
  dma_rx_handle.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  dma_rx_handle.Instance = SD_DMAx_Rx_STREAM;
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hsd, hdmarx, dma_rx_handle);
  
  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dma_rx_handle);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(&dma_rx_handle);
  
  /* Configure DMA Tx parameters */
  dma_tx_handle.Init.Channel             = SD_DMAx_Tx_CHANNEL;
  dma_tx_handle.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  dma_tx_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
  dma_tx_handle.Init.MemInc              = DMA_MINC_ENABLE;
  dma_tx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dma_tx_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dma_tx_handle.Init.Mode                = DMA_PFCTRL;
  dma_tx_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
  dma_tx_handle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  dma_tx_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dma_tx_handle.Init.MemBurst            = DMA_MBURST_INC4;
  dma_tx_handle.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  dma_tx_handle.Instance = SD_DMAx_Tx_STREAM;
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hsd, hdmatx, dma_tx_handle);
  
  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dma_tx_handle);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(&dma_tx_handle); 
  
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SD_DMAx_Rx_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(SD_DMAx_Rx_IRQn);
  
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SD_DMAx_Tx_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(SD_DMAx_Tx_IRQn);
}

/**
  * @brief  DeInitializes the SD MSP.
  * @param  hsd: SD handle
  * @retval None
  */
__weak void BSP_SD_MspDeInit(SD_HandleTypeDef *hsd, void *Params)
{
    static DMA_HandleTypeDef dma_rx_handle;
    static DMA_HandleTypeDef dma_tx_handle;

    /* Disable NVIC for DMA transfer complete interrupts */
    HAL_NVIC_DisableIRQ(SD_DMAx_Rx_IRQn);
    HAL_NVIC_DisableIRQ(SD_DMAx_Tx_IRQn);
  
    /* Deinitialize the stream for new transfer */
    dma_rx_handle.Instance = SD_DMAx_Rx_STREAM;
    HAL_DMA_DeInit(&dma_rx_handle);
  
    /* Deinitialize the stream for new transfer */
    dma_tx_handle.Instance = SD_DMAx_Tx_STREAM;
    HAL_DMA_DeInit(&dma_tx_handle);
  
    /* Disable NVIC for SDIO interrupts */
    HAL_NVIC_DisableIRQ(SDIO_IRQn);

    /* DeInit GPIO pins can be done in the application 
       (by surcharging this __weak function) */

    /* Disable SDIO clock */
    __HAL_RCC_SDIO_CLK_DISABLE();

    /* GPIO pins clock and DMA clocks can be shut down in the application 
       by surcharging this __weak function */ 
}

/**
  * @brief  Handles SD card interrupt request.
  * @param  None
  * @retval None
  */
void BSP_SD_IRQHandler(void)
{
  HAL_SD_IRQHandler(&uSdHandle);
}

/**
  * @brief  Handles SD DMA Tx transfer interrupt request.
  * @param  None
  * @retval None
  */
void BSP_SD_DMA_Tx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(uSdHandle.hdmatx); 
}

/**
  * @brief  Handles SD DMA Rx transfer interrupt request.
  * @param  None
  * @retval None
  */
void BSP_SD_DMA_Rx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(uSdHandle.hdmarx);
}

/**
  * @brief  Gets the current SD card data status.
  * @param  None
  * @retval Data transfer state.
  *          This value can be one of the following values:
  *            @arg  SD_TRANSFER_OK: No data transfer is acting
  *            @arg  SD_TRANSFER_BUSY: Data transfer is acting
  *            @arg  SD_TRANSFER_ERROR: Data transfer error 
  */
HAL_SD_TransferStateTypedef BSP_SD_GetStatus(void)
{
  return(HAL_SD_GetStatus(&uSdHandle));
}

/**
  * @brief  Get SD information about specific SD card.
  * @param  CardInfo: Pointer to HAL_SD_CardInfoTypedef structure
  * @retval None 
  */
void BSP_SD_GetCardInfo(HAL_SD_CardInfoTypedef *CardInfo)
{
  /* Get SD card Information */
  HAL_SD_Get_CardInfo(&uSdHandle, CardInfo);
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
