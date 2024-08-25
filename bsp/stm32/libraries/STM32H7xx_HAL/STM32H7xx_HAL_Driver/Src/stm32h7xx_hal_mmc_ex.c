/**
  ******************************************************************************
  * @file    stm32h7xx_hal_mmc_ex.c
  * @author  MCD Application Team
  * @brief   MMC card Extended HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Secure Digital (MMC) peripheral:
  *           + Extended features functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   The MMC Extension HAL driver can be used as follows:
   (+) Configure Buffer0 and Buffer1 start address and Buffer size using HAL_MMCEx_ConfigDMAMultiBuffer() function.

   (+) Start Read and Write for multibuffer mode using HAL_MMCEx_ReadBlocksDMAMultiBuffer() and
       HAL_MMCEx_WriteBlocksDMAMultiBuffer() functions.

  @endverbatim
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
  * @param  pDataBuffer0: Pointer to the buffer0 that will contain/receive the transferred data
  * @param  pDataBuffer1: Pointer to the buffer1 that will contain/receive the transferred data
  * @param  BufferSize: Size of Buffer0 in Blocks. Buffer0 and Buffer1 must have the same size.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MMCEx_ConfigDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t *pDataBuffer0,
                                                 uint32_t *pDataBuffer1, uint32_t BufferSize)
{
  if (hmmc->State == HAL_MMC_STATE_READY)
  {
    hmmc->Instance->IDMABASE0 = (uint32_t) pDataBuffer0 ;
    hmmc->Instance->IDMABASE1 = (uint32_t) pDataBuffer1 ;
    hmmc->Instance->IDMABSIZE = (uint32_t)(MMC_BLOCKSIZE * BufferSize);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Reads block(s) from a specified address in a card. The received Data will be stored in Buffer0 and Buffer1.
  *         Buffer0, Buffer1 and BufferSize need to be configured by function HAL_MMCEx_ConfigDMAMultiBuffer before
  *         call this function.
  * @param  hmmc: MMC handle
  * @param  BlockAdd: Block Address from where data is to be read
  * @param  NumberOfBlocks: Total number of blocks to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MMCEx_ReadBlocksDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t BlockAdd,
                                                     uint32_t NumberOfBlocks)
{
  SDMMC_DataInitTypeDef config;
  uint32_t DmaBase0_reg;
  uint32_t DmaBase1_reg;
  uint32_t errorstate;
  uint32_t add = BlockAdd;

  if (hmmc->State == HAL_MMC_STATE_READY)
  {
    if ((BlockAdd + NumberOfBlocks) > (hmmc->MmcCard.LogBlockNbr))
    {
      hmmc->ErrorCode |= HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
      return HAL_ERROR;
    }

    /* Check the case of 4kB blocks (field DATA SECTOR SIZE of extended CSD register) */
    if (((hmmc->Ext_CSD[(MMC_EXT_CSD_DATA_SEC_SIZE_INDEX / 4)] >> MMC_EXT_CSD_DATA_SEC_SIZE_POS) & 0x000000FFU) != 0x0U)
    {
      if ((NumberOfBlocks % 8U) != 0U)
      {
        /* The number of blocks should be a multiple of 8 sectors of 512 bytes = 4 KBytes */
        hmmc->ErrorCode |= HAL_MMC_ERROR_BLOCK_LEN_ERR;
        return HAL_ERROR;
      }

      if ((BlockAdd % 8U) != 0U)
      {
        /* The address should be aligned to 8 (corresponding to 4 KBytes blocks) */
        hmmc->ErrorCode |= HAL_MMC_ERROR_ADDR_MISALIGNED;
        return HAL_ERROR;
      }
    }

    DmaBase0_reg = hmmc->Instance->IDMABASE0;
    DmaBase1_reg = hmmc->Instance->IDMABASE1;

    if ((hmmc->Instance->IDMABSIZE == 0U) || (DmaBase0_reg == 0U) || (DmaBase1_reg == 0U))
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
      add *= 512U;
    }

    /* Configure the MMC DPSM (Data Path State Machine) */
    config.DataTimeOut   = SDMMC_DATATIMEOUT;
    config.DataLength    = MMC_BLOCKSIZE * NumberOfBlocks;
    config.DataBlockSize = SDMMC_DATABLOCK_SIZE_512B;
    config.TransferDir   = SDMMC_TRANSFER_DIR_TO_SDMMC;
    config.TransferMode  = SDMMC_TRANSFER_MODE_BLOCK;
    config.DPSM          = SDMMC_DPSM_DISABLE;
    (void)SDMMC_ConfigData(hmmc->Instance, &config);

    hmmc->Instance->DCTRL |= SDMMC_DCTRL_FIFORST;

    __SDMMC_CMDTRANS_ENABLE(hmmc->Instance);

    hmmc->Instance->IDMACTRL = SDMMC_ENABLE_IDMA_DOUBLE_BUFF0;

    /* Read Blocks in DMA mode */
    hmmc->Context = (MMC_CONTEXT_READ_MULTIPLE_BLOCK | MMC_CONTEXT_DMA);

    /* Read Multi Block command */
    errorstate = SDMMC_CmdReadMultiBlock(hmmc->Instance, add);
    if (errorstate != HAL_MMC_ERROR_NONE)
    {
      hmmc->State = HAL_MMC_STATE_READY;
      hmmc->ErrorCode |= errorstate;
      return HAL_ERROR;
    }

    __HAL_MMC_ENABLE_IT(hmmc, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND |
                               SDMMC_FLAG_IDMATE | SDMMC_FLAG_IDMABTC));

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }

}

/**
  * @brief  Write block(s) to a specified address in a card. The transferred Data are stored in Buffer0 and Buffer1.
  *         Buffer0, Buffer1 and BufferSize need to be configured by function HAL_MMCEx_ConfigDMAMultiBuffer before
  *         call this function.
  * @param  hmmc: MMC handle
  * @param  BlockAdd: Block Address from where data is to be read
  * @param  NumberOfBlocks: Total number of blocks to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MMCEx_WriteBlocksDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t BlockAdd,
                                                      uint32_t NumberOfBlocks)
{
  SDMMC_DataInitTypeDef config;
  uint32_t errorstate;
  uint32_t DmaBase0_reg;
  uint32_t DmaBase1_reg;
  uint32_t add = BlockAdd;

  if (hmmc->State == HAL_MMC_STATE_READY)
  {
    if ((BlockAdd + NumberOfBlocks) > (hmmc->MmcCard.LogBlockNbr))
    {
      hmmc->ErrorCode |= HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
      return HAL_ERROR;
    }

    /* Check the case of 4kB blocks (field DATA SECTOR SIZE of extended CSD register) */
    if (((hmmc->Ext_CSD[(MMC_EXT_CSD_DATA_SEC_SIZE_INDEX / 4)] >> MMC_EXT_CSD_DATA_SEC_SIZE_POS) & 0x000000FFU) != 0x0U)
    {
      if ((NumberOfBlocks % 8U) != 0U)
      {
        /* The number of blocks should be a multiple of 8 sectors of 512 bytes = 4 KBytes */
        hmmc->ErrorCode |= HAL_MMC_ERROR_BLOCK_LEN_ERR;
        return HAL_ERROR;
      }

      if ((BlockAdd % 8U) != 0U)
      {
        /* The address should be aligned to 8 (corresponding to 4 KBytes blocks) */
        hmmc->ErrorCode |= HAL_MMC_ERROR_ADDR_MISALIGNED;
        return HAL_ERROR;
      }
    }

    DmaBase0_reg = hmmc->Instance->IDMABASE0;
    DmaBase1_reg = hmmc->Instance->IDMABASE1;

    if ((hmmc->Instance->IDMABSIZE == 0U) || (DmaBase0_reg == 0U) || (DmaBase1_reg == 0U))
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
      add *= 512U;
    }

    /* Configure the MMC DPSM (Data Path State Machine) */
    config.DataTimeOut   = SDMMC_DATATIMEOUT;
    config.DataLength    = MMC_BLOCKSIZE * NumberOfBlocks;
    config.DataBlockSize = SDMMC_DATABLOCK_SIZE_512B;
    config.TransferDir   = SDMMC_TRANSFER_DIR_TO_CARD;
    config.TransferMode  = SDMMC_TRANSFER_MODE_BLOCK;
    config.DPSM          = SDMMC_DPSM_DISABLE;
    (void)SDMMC_ConfigData(hmmc->Instance, &config);

    __SDMMC_CMDTRANS_ENABLE(hmmc->Instance);

    hmmc->Instance->IDMACTRL = SDMMC_ENABLE_IDMA_DOUBLE_BUFF0;

    /* Write Blocks in DMA mode */
    hmmc->Context = (MMC_CONTEXT_WRITE_MULTIPLE_BLOCK | MMC_CONTEXT_DMA);

    /* Write Multi Block command */
    errorstate = SDMMC_CmdWriteMultiBlock(hmmc->Instance, add);
    if (errorstate != HAL_MMC_ERROR_NONE)
    {
      hmmc->State = HAL_MMC_STATE_READY;
      hmmc->ErrorCode |= errorstate;
      return HAL_ERROR;
    }

    __HAL_MMC_ENABLE_IT(hmmc, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND |
                               SDMMC_FLAG_IDMATE | SDMMC_FLAG_IDMABTC));

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
HAL_StatusTypeDef HAL_MMCEx_ChangeDMABuffer(MMC_HandleTypeDef *hmmc, HAL_MMCEx_DMABuffer_MemoryTypeDef Buffer,
                                            uint32_t *pDataBuffer)
{
  if (Buffer == MMC_DMA_BUFFER0)
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
