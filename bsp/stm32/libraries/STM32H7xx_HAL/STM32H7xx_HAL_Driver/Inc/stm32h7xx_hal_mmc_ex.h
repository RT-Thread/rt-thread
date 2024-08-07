/**
  ******************************************************************************
  * @file    stm32h7xx_hal_mmc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SD HAL extended module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_MMC_EX_H
#define STM32H7xx_HAL_MMC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup MMCEx
  * @brief SD HAL extended module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup MMCEx_Exported_Types MMCEx Exported Types
  * @{
  */

/** @defgroup MMCEx_Exported_Types_Group1 MMC Internal DMA Buffer structure
  * @{
  */
typedef enum
{
  MMC_DMA_BUFFER0      = 0x00U,    /*!< selects MMC internal DMA Buffer 0     */
  MMC_DMA_BUFFER1      = 0x01U,    /*!< selects MMC internal DMA Buffer 1     */

} HAL_MMCEx_DMABuffer_MemoryTypeDef;


/**
  * @}
  */

/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @defgroup MMCEx_Exported_Functions MMCEx Exported Functions
  * @{
  */

/** @defgroup MMCEx_Exported_Functions_Group1 MultiBuffer functions
  * @{
  */
HAL_StatusTypeDef HAL_MMCEx_ConfigDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t *pDataBuffer0,
                                                 uint32_t *pDataBuffer1, uint32_t BufferSize);
HAL_StatusTypeDef HAL_MMCEx_ReadBlocksDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t BlockAdd,
                                                     uint32_t NumberOfBlocks);
HAL_StatusTypeDef HAL_MMCEx_WriteBlocksDMAMultiBuffer(MMC_HandleTypeDef *hmmc, uint32_t BlockAdd,
                                                      uint32_t NumberOfBlocks);
HAL_StatusTypeDef HAL_MMCEx_ChangeDMABuffer(MMC_HandleTypeDef *hmmc, HAL_MMCEx_DMABuffer_MemoryTypeDef Buffer,
                                            uint32_t *pDataBuffer);

void HAL_MMCEx_Read_DMADoubleBuf0CpltCallback(MMC_HandleTypeDef *hmmc);
void HAL_MMCEx_Read_DMADoubleBuf1CpltCallback(MMC_HandleTypeDef *hmmc);
void HAL_MMCEx_Write_DMADoubleBuf0CpltCallback(MMC_HandleTypeDef *hmmc);
void HAL_MMCEx_Write_DMADoubleBuf1CpltCallback(MMC_HandleTypeDef *hmmc);

/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions prototypes ----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif


#endif /* STM32H7xx_HAL_MMCEx_H */
