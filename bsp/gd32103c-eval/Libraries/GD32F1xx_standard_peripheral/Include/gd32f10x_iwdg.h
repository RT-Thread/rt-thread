/**
  ******************************************************************************
  * @brief   IWDG header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_IWDG_H
#define __GD32F10X_IWDG_H

/* Exported macro ------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup IWDG
  * @{
  */

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/** @defgroup IWDG_WriteAccess
  * @{
  */
#define IWDG_WRITEACCESS_ENABLE     ((uint16_t)0x5555)
#define IWDG_WRITEACCESS_DISABLE    ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup IWDG_prescaler
  * @{
  */
#define IWDG_PRESCALER_4            ((uint8_t)0x00)
#define IWDG_PRESCALER_8            ((uint8_t)0x01)
#define IWDG_PRESCALER_16           ((uint8_t)0x02)
#define IWDG_PRESCALER_32           ((uint8_t)0x03)
#define IWDG_PRESCALER_64           ((uint8_t)0x04)
#define IWDG_PRESCALER_128          ((uint8_t)0x05)
#define IWDG_PRESCALER_256          ((uint8_t)0x06)

/**
  * @}
  */

/** @defgroup IWDG_Flag
  * @{
  */
#define IWDG_BIT_PUD                IWDG_STR_PUD
#define IWDG_BIT_RUD                IWDG_STR_RUD
#define IWDG_BIT_WUD                IWDG_STR_WUD

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_functions
  * @{
  */
/* Prescaler and Counter configuration functions ******************************/
void IWDG_Write_Enable(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t PrescalerValue);
void IWDG_SetReloadValue(uint16_t ReloadValue);
void IWDG_ReloadCounter(void);

/* IWDG activation function ***************************************************/
void IWDG_Enable(void);

/* Flag management function ***************************************************/
TypeState IWDG_GetBitState(uint16_t IWDG_FLAG);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __IWDG_GD32F10X_H */

/**
  * @}
  */

/**
  * @}
  */
