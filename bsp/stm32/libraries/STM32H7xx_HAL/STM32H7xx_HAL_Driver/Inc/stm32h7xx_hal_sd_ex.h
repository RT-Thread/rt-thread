/**
  ******************************************************************************
  * @file    stm32h7xx_hal_sd_ex.h
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
#ifndef STM32H7xx_HAL_SD_EX_H
#define STM32H7xx_HAL_SD_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup SDEx
  * @brief SD HAL extended module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SDEx_Exported_Types SDEx Exported Types
  * @{
  */

/** @defgroup SDEx_Exported_Types_Group1 SD Card Internal DMA Buffer structure
  * @{
  */
typedef enum
{
  SD_DMA_BUFFER0      = 0x00U,    /*!< selects SD internal DMA Buffer 0     */
  SD_DMA_BUFFER1      = 0x01U,    /*!< selects SD internal DMA Buffer 1     */

} HAL_SDEx_DMABuffer_MemoryTypeDef;

/**
  * @}
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SDEx_Exported_Functions SDEx Exported Functions
  * @{
  */

/** @defgroup SDEx_Exported_Functions_Group1 MultiBuffer functions
  * @{
  */

HAL_StatusTypeDef HAL_SDEx_ConfigDMAMultiBuffer(SD_HandleTypeDef *hsd, uint32_t *pDataBuffer0, uint32_t *pDataBuffer1,
                                                uint32_t BufferSize);
HAL_StatusTypeDef HAL_SDEx_ReadBlocksDMAMultiBuffer(SD_HandleTypeDef *hsd, uint32_t BlockAdd, uint32_t NumberOfBlocks);
HAL_StatusTypeDef HAL_SDEx_WriteBlocksDMAMultiBuffer(SD_HandleTypeDef *hsd, uint32_t BlockAdd, uint32_t NumberOfBlocks);
HAL_StatusTypeDef HAL_SDEx_ChangeDMABuffer(SD_HandleTypeDef *hsd, HAL_SDEx_DMABuffer_MemoryTypeDef Buffer,
                                           uint32_t *pDataBuffer);

void HAL_SDEx_Read_DMADoubleBuf0CpltCallback(SD_HandleTypeDef *hsd);
void HAL_SDEx_Read_DMADoubleBuf1CpltCallback(SD_HandleTypeDef *hsd);
void HAL_SDEx_Write_DMADoubleBuf0CpltCallback(SD_HandleTypeDef *hsd);
void HAL_SDEx_Write_DMADoubleBuf1CpltCallback(SD_HandleTypeDef *hsd);

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


#endif /* stm32h7xx_HAL_SD_EX_H */
