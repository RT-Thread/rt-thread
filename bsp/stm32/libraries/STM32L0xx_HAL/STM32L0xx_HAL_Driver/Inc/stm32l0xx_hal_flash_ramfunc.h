/**
  ******************************************************************************
  * @file    stm32l0xx_hal_flash_ramfunc.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH RAMFUNC driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_FLASH_RAMFUNC_H
#define __STM32L0xx_FLASH_RAMFUNC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH_RAMFUNC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 


/* Exported functions --------------------------------------------------------*/

/** @addtogroup FLASH_RAMFUNC_Exported_Functions
  * @{
  */

/*
  * @brief  FLASH memory functions that should be executed from internal SRAM.
  *         These functions are defined inside the "stm32l0xx_hal_flash_ramfunc.c"
  *         file.
  */
  
/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group1
  * @{
  */

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_EnableRunPowerDown(void);
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_DisableRunPowerDown(void);

/**
  * @}
  */ 

/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group2
  * @{
  */

#if defined(FLASH_PECR_PARALLBANK)

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_EraseParallelPage(uint32_t Page_Address1, uint32_t Page_Address2);
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_ProgramParallelHalfPage(uint32_t Address1, uint32_t* pBuffer1, uint32_t Address2, uint32_t* pBuffer2);

#endif /* FLASH_PECR_PARALLBANK */

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_HalfPageProgram(uint32_t Address, uint32_t* pBuffer);

/**
  * @}
  */ 

/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group3
  * @{
  */
__RAM_FUNC  HAL_StatusTypeDef HAL_FLASHEx_GetError(uint32_t *Error);
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

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_FLASH_RAMFUNC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
