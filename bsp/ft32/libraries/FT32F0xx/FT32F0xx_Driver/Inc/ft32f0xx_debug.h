/**
  ******************************************************************************
  * @file               ft32f0xx_debug.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the DBGMCU firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_DBGMCU_H
#define __FT32F0XX_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"


/** @addtogroup DBGMCU
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/** @defgroup DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_STOP                  DBGMCU_CR_DBG_STOP
#define DBGMCU_STANDBY               DBGMCU_CR_DBG_STANDBY
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF9) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM2_STOP             DBGMCU_APB1_FZ_DBG_TIM2_STOP
#define DBGMCU_TIM3_STOP             DBGMCU_APB1_FZ_DBG_TIM3_STOP
#define DBGMCU_TIM6_STOP             DBGMCU_APB1_FZ_DBG_TIM6_STOP
#define DBGMCU_TIM7_STOP             DBGMCU_APB1_FZ_DBG_TIM7_STOP
#define DBGMCU_TIM14_STOP            DBGMCU_APB1_FZ_DBG_TIM14_STOP
#define DBGMCU_RTC_STOP              DBGMCU_APB1_FZ_DBG_RTC_STOP
#define DBGMCU_WWDG_STOP             DBGMCU_APB1_FZ_DBG_WWDG_STOP
#define DBGMCU_IWDG_STOP             DBGMCU_APB1_FZ_DBG_IWDG_STOP
#define DBGMCU_I2C1_SMBUS_TIMEOUT    DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT
#define DBGMCU_CAN1_STOP             DBGMCU_APB1_FZ_DBG_CAN1_STOP
#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xFDDFE2CC) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM1_STOP             DBGMCU_APB2_FZ_DBG_TIM1_STOP
#define DBGMCU_TIM15_STOP            DBGMCU_APB2_FZ_DBG_TIM15_STOP
#define DBGMCU_TIM16_STOP            DBGMCU_APB2_FZ_DBG_TIM16_STOP
#define DBGMCU_TIM17_STOP            DBGMCU_APB2_FZ_DBG_TIM17_STOP
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFF8F7FF) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Device and Revision ID management functions ********************************/
uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);

/* Peripherals Configuration functions ****************************************/
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_DBGMCU_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
