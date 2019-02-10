/**
  ******************************************************************************
  * @file    stm32h7xx_hal_mmc_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   MMC card Extended HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Secure Digital (MMC) peripheral:
  *           + Extended features functions
  *         
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   The MMC Extension HAL driver can be used as follows:
   (+) Configure Buffer0 and Buffer1 start address and Buffer size using HAL_MMCEx_ConfigDMAMultiBuffer() function.

   (+) Start Read and Write for multibuffer mode using HAL_MMCEx_ReadBlocksDMAMultiBuffer() and HAL_MMCEx_WriteBlocksDMAMultiBuffer() functions.
   
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

/** @defgroup MMCEx MMCEx
  * @brief MMC Extended HAL module driver
  * @{
  */

#ifdef HAL_MMC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup MMCEx_Exported_Functions
  * @{
  */

/** @addtogroup MMCEx_Exported_Functions_Group1
 *  @brief   Multibuffer functions 
 *
@verbatim    
  ==============================================================================
          ##### Multibuffer functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to configure the multibuffer mode and start read and write 
    multibuffer mode for MMC HAL driver.
      
@endverbatim
  * @{
  */

/**
  * @brief  Configure DMA Dual Buffer mode. The Data transfer is managed by an Internal DMA.
  * @param  hmmc: MMC handle
  * @param  pDataBuffer0: Pointer to the buffer0 that will contain/receive the transfered data
  * @param  pDataBuffer1: Pointer to the buffer1 that will contain/receive the transfered data
  * @param  BufferSize: Size of Buffer0 in Blocks. Buffer0 and Buffer1 must have the same size.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MMCEx_ConfigDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t * pDataBuffer0, uint32_t * pDataBuffer1, uint32_t BufferSize)
{
  if(hmmc->State == HAL_MMC_STATE_READY)
  {
    hmmc->Instance->IDMABASE0= (uint32_t) pDataBuffer0 ;
    hmmc->Instance->IDMABASE1= (uint32_t) pDataBuffer1 ;
    hmmc->Instance->IDMABSIZE= (uint32_t) BufferSize;
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
  
/**
  * @brief  Reads block(s) from a specified address in a card. The received Data will be stored in Buffer0 and Buffer1.
  *         Buffer0, Buffer1 and BufferSize need to be configured by function HAL_MMCEx_ConfigDMAMultiBuffer before call this function.
  * @param  hmmc: MMC handle
  * @param  BlockAdd: Block Address from where data is to be read  
  * @param  NumberOfBlocks: Total number of blocks to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MMCEx_ReadBlocksDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
  SDMMC_DataInitTypeDef config;
  uint32_t errorstate = HAL_MMC_ERROR_NONE;
  
  if(hmmc->State == HAL_MMC_STATE_READY)
  {
    if((BlockAdd + NumberOfBlocks) > (hmmc->MmcCard.LogBlockNbr))
    {
      hmmc->ErrorCode |= HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
      return HAL_ERROR;
    }
    
    if ((hmmc->Instance->IDMABASE0 == 0) || (hmmc->Instance->IDMABASE1 == 0) || (hmmc->Instance->IDMABSIZE == 0))
    {
      hmmc->ErrorCode = HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
      return HAL_ERROR;
    }
    
    /* Initialize data control register */
    hmmc->Instance->DCTRL = 0;
    
    hmmc->ErrorCode = HAL_MMC_ERROR_NONE;
    hmmc->State = HAL_MMC_STATE_BUSY;

    if ((hmmc->MmcCard.CardType) != MMC_HIGH_CAPACITY_CARD)
    {
      BlockAdd *= 512;
    }
    
    /* Configure the MMC DPSM (Data Path State Machine) */ 
    config.DataTimeOut   = SDMMC_DATATIMEOUT;
    config.DataLength    = BLOCKSIZE * NumberOfBlocks;
    config.DataBlockSize = SDMMC_DATABLOCK_SIZE_512B;
    config.TransferDir   = SDMMC_TRANSFER_DIR_TO_SDMMC;
    config.TransferMode  = SDMMC_TRANSFER_MODE_BLOCK;
    config.DPSM          = SDMMC_DPSM_DISABLE;
    SDMMC_ConfigData(hmmc->Instance, &config);
    
    hmmc->Instance->DCTRL |= SDMMC_DCTRL_FIFORST;
    
    __SDMMC_CMDTRANS_ENABLE( hmmc->Instance);
    
    hmmc->Instance->IDMACTRL = SDMMC_ENABLE_IDMA_DOUBLE_BUFF0; 

     __HAL_MMC_ENABLE_IT(hmmc, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND | SDMMC_FLAG_IDMATE | SDMMC_FLAG_IDMABTC));
   
    /* Read Blocks in DMA mode */
    hmmc->Context = (MMC_CONTEXT_READ_MULTIPLE_BLOCK | MMC_CONTEXT_DMA);
    
    /* Read Multi Block command */
    errorstate = SDMMC_CmdReadMultiBlock(hmmc->Instance, BlockAdd);
    if(errorstate != HAL_MMC_ERROR_NONE)
    {
      hmmc->State = HAL_MMC_STATE_READY;
      hmmc->ErrorCode |= errorstate;
      return HAL_ERROR;
    }
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
   
}

/**
  * @brief  Write block(s) to a specified address in a card. The transfered Data are stored in Buffer0 and Buffer1.
  *         Buffer0, Buffer1 and BufferSize need to be configured by function HAL_MMCEx_ConfigDMAMultiBuffer before call this function.
  * @param  hmmc: MMC handle
  * @param  BlockAdd: Block Address from where data is to be read  
  * @param  NumberOfBlocks: Total number of blocks to read
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_MMCEx_WriteBlocksDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
  SDMMC_DataInitTypeDef config;
  uint32_t errorstate = HAL_MMC_ERROR_NONE;
  
  if(hmmc->State == HAL_MMC_STATE_READY)
  {
    if((BlockAdd + NumberOfBlocks) > (hmmc->MmcCard.LogBlockNbr))
    {
      hmmc->ErrorCode |= HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
      return HAL_ERROR;
    }
    
    if ((hmmc->Instance->IDMABASE0 == 0) || (hmmc->Instance->IDMABASE1 == 0) || (hmmc->Instance->IDMABSIZE == 0))
    {
      hmmc->ErrorCode = HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
      return HAL_ERROR;
    }
    
    /* Initialize data control register */
    hmmc->Instance->DCTRL = 0;
    
    hmmc->ErrorCode = HAL_MMC_ERROR_NONE;
    
    hmmc->State = HAL_MMC_STATE_BUSY;

    if ((hmmc->MmcCard.CardType) != MMC_HIGH_CAPACITY_CARD)
    {
      BlockAdd *= 512;
    }
    
    /* Configure the MMC DPSM (Data Path State Machine) */ 
    config.DataTimeOut   = SDMMC_DATATIMEOUT;
    config.DataLength    = BLOCKSIZE * NumberOfBlocks;
    config.DataBlockSize = SDMMC_DATABLOCK_SIZE_512B;
    config.TransferDir   = SDMMC_TRANSFER_DIR_TO_CARD;
    config.TransferMode  = SDMMC_TRANSFER_MODE_BLOCK;
    config.DPSM          = SDMMC_DPSM_DISABLE;
    SDMMC_ConfigData(hmmc->Instance, &config);
    
    __SDMMC_CMDTRANS_ENABLE( hmmc->Instance);
    
    hmmc->Instance->IDMACTRL = SDMMC_ENABLE_IDMA_DOUBLE_BUFF0; 
 
    __HAL_MMC_ENABLE_IT(hmmc, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND | SDMMC_FLAG_IDMATE | SDMMC_FLAG_IDMABTC));
   
    /* Write Blocks in DMA mode */
    hmmc->Context = (MMC_CONTEXT_WRITE_MULTIPLE_BLOCK | MMC_CONTEXT_DMA);
    
    /* Write Multi Block command */
    errorstate = SDMMC_CmdWriteMultiBlock(hmmc->Instance, BlockAdd);
    if(errorstate != HAL_MMC_ERROR_NONE)
    {
      hmmc->State = HAL_MMC_STATE_READY;
      hmmc->ErrorCode |= errorstate;
      return HAL_ERROR;
    }
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }  
}

  
/**
  * @brief  Change the DMA Buffer0 or Buffer1 address on the fly.
  * @param  hmmc:           pointer to a MMC_HandleTypeDef structure.
  * @param  Buffer:        the buffer to be changed, This parameter can be one of 
  *                        the following values: MMC_DMA_BUFFER0 or MMC_DMA_BUFFER1
  * @param  pDataBuffer:   The new address
  * @note   The BUFFER0 address can be changed only when the current transfer use
  *         BUFFER1 and the BUFFER1 address can be changed only when the current 
  *         transfer use BUFFER0.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MMCEx_ChangeDMABuffer(MMC_HandleTypeDef *hmmc, HAL_MMCEx_DMABuffer_MemoryTypeDef Buffer, uint32_t *pDataBuffer)
{
  if(Buffer == MMC_DMA_BUFFER0)
  {
    /* change the buffer0 address */
    hmmc->Instance->IDMABASE0 = (uint32_t)pDataBuffer;
  }
  else
  {
    /* change the memory1 address */
    hmmc->Instance->IDMABASE1 = (uint32_t)pDataBuffer;
  }
  
  return HAL_OK;
}


/**
  * @}
  */


/**
  * @}
  */
#endif /* HAL_MMC_MODULE_ENABLED */  
/**
  * @}
  */
  
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
