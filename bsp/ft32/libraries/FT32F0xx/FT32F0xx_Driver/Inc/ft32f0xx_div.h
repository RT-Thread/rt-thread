/**
  ******************************************************************************
  * @file               FT32f0xx_div.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the dividor firmware
  *                     library.
  * @version            V1.0.0
  * @data               2021-12-01
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_DIV_H
#define __FT32F0XX_DIV_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"
#include <stdint.h>
/** @addtogroup DIV
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  DIV Status
  */
typedef enum
{
    DIV_COMPLETE  = 0,
    DIV_ERROR_DIV0ERR,
    DIV_ERROR_DIV0V,
}DIV_Status;

/**
  * @brief  Dividor Data structure definition
  */
typedef struct
{
    uint32_t DIV_quotient;          /*!< Selects The feedback resister of the OPA. */
    uint32_t DIV_remainder;          /*!< Selects The compensate cap of the OPA.*/
}DIV_ResultTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DIV_interrupts_definition
  * @{
  */

#define DIV_IT_DIV0ERR                              DIV_SC_DIV0IE
#define DIV_IT_DIVOV                                DIV_SC_DIVOVIE
#define IS_DIV_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFFEB) == (uint32_t)RESET))

#define IS_DIV_GET_IT(IT) (((IT) == DIV_IT_DIV0ERR) || ((IT) == DIV_IT_DIVOV))

#define IS_DIV_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFFEB0) == (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup DIV_flags_definition
  * @{
  */

#define DIV_FLAG_BUSY                               DIV_SC_DIVBUSY
#define DIV_FLAG_DIV0ERR                            DIV_SC_DIV0ERR
#define DIV_FLAG_DIVOV                              DIV_SC_DIVOV

#define IS_DIV_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFFFFF5) == (uint32_t)RESET))

#define IS_DIV_GET_FLAG(FLAG) (((FLAG) == DIV_FLAG_BUSY)   || ((FLAG) == DIV_FLAG_DIV0ERR) || ((FLAG) == DIV_FLAG_DIV0ERR))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* DIV Calculating functions *****************************************/
DIV_Status DivS32ByS16(DIV_ResultTypeDef* pResult,int32_t divedent,int16_t dividor);

/* Interrupts and flags management functions **********************************/
void DIV_ITConfig(uint32_t DIV_IT, FunctionalState NewState);
FlagStatus DIV_GetFlagStatus(uint32_t DIV_FLAG);
void DIV_ClearFlag(uint32_t DIV_FLAG);
ITStatus DIV_GetITStatus(uint32_t DIV_IT);
void DIV_ClearITPendingBit(uint32_t DIV_IT);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F0XX_DIV_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
