/**
  ******************************************************************************
  * @file    stm324x9i_eval_sd.c
  * @author  MCD Application Team
  * @version V2.2.1
  * @date    07-October-2015
  * @brief   This file includes the uSD card driver mounted on STM324x9I-EVAL
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
   - This driver is used to drive the micro SD external card mounted on STM324x9I-EVAL 
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
#include "stm324x9i_eval_sd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324x9I_EVAL
  * @{
  */ 
  
/** @defgroup STM324x9I_EVAL_SD
  * @{
  */ 


/** @defgroup STM324x9I_EVAL_SD_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM324x9I_EVAL_SD_Private_Defines
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM324x9I_EVAL_SD_Private_Macros
  * @{
  */    
/**
  * @}
  */  

/** @defgroup STM324x9I_EVAL_SD_Private_Variables
  * @{
  */
static SD_HandleTypeDef uSdHandle;
static SD_CardInfo uSdCardInfo;
/**
  * @}
  */ 
  
/** @defgroup STM324x9I_EVAL_SD_Private_FunctionPrototypes
  * @{
  */
static void SD_MspInit(void);
/**
  * @}
  */ 
  
/** @defgroup STM324x9I_EVAL_SD_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the SD card device.
  * @param  None
  * @retval SD status
  */
uint8_t BSP_SD_Init(void)
{ 
  uint8_t SD_state = MSD_OK;
  
  /* uSD device interface configuration */
  uSdHandle.Instance = SDIO;

  uSdHandle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
  uSdHandle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
  uSdHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
  uSdHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
  uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  uSdHandle.Init.ClockDiv            = SDIO_TRANSFER_CLK_DIV;
  
  /* Configure IO functionalities for SD detect pin */
  BSP_IO_Init(); 
  
  /* Check if the SD card is plugged in the slot */
  if(BSP_SD_IsDetected() != SD_PRESENT)
  {
    return MSD_ERROR;
  }
  
  /* HAL SD initialization */
  SD_MspInit();
  if(HAL_SD_Init(&uSdHandle, &uSdCardInfo) != SD_OK)
  {
    SD_state = MSD_ERROR;
  }
  
  /* Configure SD Bus width */
  if(SD_state == MSD_OK)
  {
    /* Enable wide operation */
    if(HAL_SD_WideBusOperation_Config(&uSdHandle, SDIO_BUS_WIDE_4B) != SD_OK)
    {
      SD_state = MSD_ERROR;
    }
    else
    {
      SD_state = MSD_OK;
    }
  }
  
  return  SD_state;
}

/**
  * @brief  Configures Interrupt mode for SD detection pin.
  * @param  None
  * @retval Returns 0
  */
uint8_t BSP_SD_ITConfig(void)
{  
  /* Configure Interrupt mode for SD detection pin */  
  BSP_IO_ConfigPin(SD_DETECT_PIN, IO_MODE_IT_FALLING_EDGE);
  
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
  if(BSP_IO_ReadPin(SD_DETECT_PIN))
  {
    status = SD_NOT_PRESENT;
  }
  
  return status;
}

/** @brief  SD detect IT treatment.
  * @param  None
  * @retval None
  */
void BSP_SD_DetectIT(void)
{
  /* Clear all pending bits */
  BSP_IO_ITClear();
  
  /* To re-enable IT */
  BSP_SD_ITConfig();
  
  /* SD detect IT callback */
  BSP_SD_DetectCallback();
}

/** @brief  SD detect IT detection callback
  * @param  None
  * @retval None
  */
__weak void BSP_SD_DetectCallback(void)
{
  /* NOTE: This function Should not be modified, when the callback is needed,
     the BSP_SD_DetectCallback could be implemented in the user file
  */ 
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
  uint8_t SD_state = MSD_OK;
  
  /* Read block(s) in DMA transfer mode */
  if(HAL_SD_ReadBlocks_DMA(&uSdHandle, pData, ReadAddr, BlockSize, NumOfBlocks) != SD_OK)
  {
    SD_state = MSD_ERROR;
  }
  
  /* Wait until transfer is complete */
  if(SD_state == MSD_OK)
  {
    if(HAL_SD_CheckReadOperation(&uSdHandle, (uint32_t)SD_DATATIMEOUT) != SD_OK)
    {
      SD_state = MSD_ERROR;
    }
    else
    {
      SD_state = MSD_OK;
    }
  }
  
  return SD_state; 
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
  uint8_t SD_state = MSD_OK;
  
  /* Write block(s) in DMA transfer mode */
  if(HAL_SD_WriteBlocks_DMA(&uSdHandle, pData, WriteAddr, BlockSize, NumOfBlocks) != SD_OK)
  {
    SD_state = MSD_ERROR;
  }
  
  /* Wait until transfer is complete */
  if(SD_state == MSD_OK)
  {
    if(HAL_SD_CheckWriteOperation(&uSdHandle, (uint32_t)SD_DATATIMEOUT) != SD_OK)
    {
      SD_state = MSD_ERROR;
    }
    else
    {
      SD_state = MSD_OK;
    }
  }
  
  return SD_state;  
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
  * @param  None
  * @retval None
  */
static void SD_MspInit(void)
{
  static DMA_HandleTypeDef dmaRxHandle;
  static DMA_HandleTypeDef dmaTxHandle;
  GPIO_InitTypeDef GPIO_Init_Structure;
  SD_HandleTypeDef *hsd = &uSdHandle;
  
  /* Enable SDIO clock */
  __SDIO_CLK_ENABLE();
  
  /* Enable DMA2 clocks */
  __DMAx_TxRx_CLK_ENABLE();

  /* Enable GPIOs clock */
  __GPIOC_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();
  
  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_HIGH;
  GPIO_Init_Structure.Alternate = GPIO_AF12_SDIO;
  
  /* GPIOC configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
   
  HAL_GPIO_Init(GPIOC, &GPIO_Init_Structure);

  /* GPIOD configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* NVIC configuration for SDIO interrupts */
  HAL_NVIC_SetPriority(SDIO_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(SDIO_IRQn);
    
  /* Configure DMA Rx parameters */
  dmaRxHandle.Init.Channel             = SD_DMAx_Rx_CHANNEL;
  dmaRxHandle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  dmaRxHandle.Init.PeriphInc           = DMA_PINC_DISABLE;
  dmaRxHandle.Init.MemInc              = DMA_MINC_ENABLE;
  dmaRxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dmaRxHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dmaRxHandle.Init.Mode                = DMA_PFCTRL;
  dmaRxHandle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
  dmaRxHandle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  dmaRxHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dmaRxHandle.Init.MemBurst            = DMA_MBURST_INC4;
  dmaRxHandle.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  dmaRxHandle.Instance = SD_DMAx_Rx_STREAM;
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hsd, hdmarx, dmaRxHandle);
  
  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dmaRxHandle);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(&dmaRxHandle);
  
  /* Configure DMA Tx parameters */
  dmaTxHandle.Init.Channel             = SD_DMAx_Tx_CHANNEL;
  dmaTxHandle.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  dmaTxHandle.Init.PeriphInc           = DMA_PINC_DISABLE;
  dmaTxHandle.Init.MemInc              = DMA_MINC_ENABLE;
  dmaTxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dmaTxHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dmaTxHandle.Init.Mode                = DMA_PFCTRL;
  dmaTxHandle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
  dmaTxHandle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  dmaTxHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dmaTxHandle.Init.MemBurst            = DMA_MBURST_INC4;
  dmaTxHandle.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  dmaTxHandle.Instance = SD_DMAx_Tx_STREAM;
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hsd, hdmatx, dmaTxHandle);
  
  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dmaTxHandle);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(&dmaTxHandle); 
  
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SD_DMAx_Rx_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(SD_DMAx_Rx_IRQn);
  
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SD_DMAx_Tx_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(SD_DMAx_Tx_IRQn);
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
