/**
  ******************************************************************************
  * @file               ft32f4xx_debug.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the DBGMCU firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2025-04-08
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_DBGMCU_H
#define __FT32F4XX_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup DBGMCU
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/** @defgroup DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_SLEEP                 DBGMCU_CR_DBG_SLEEP
#define DBGMCU_STOP                  DBGMCU_CR_DBG_STOP
#define DBGMCU_STANDBY               DBGMCU_CR_DBG_STANDBY

#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF8) == 0x00) && ((PERIPH) != 0x00))

/* DEBUG MCU APB1 Freeze Register bits */
#define DBGMCU_CAN4_STOP                     DBG_CAN4_STOP
#define DBGMCU_CAN3_STOP                     DBG_CAN3_STOP
#define DBGMCU_CAN2_STOP                     DBG_CAN2_STOP
#define DBGMCU_CAN1_STOP                     DBG_CAN1_STOP
#define DBGMCU_I2C3_SMBUS_TIMEOUT_STOP       DBG_I2C3_SMBUS_STOP
#define DBGMCU_I2C2_SMBUS_TIMEOUT_STOP       DBG_I2C2_SMBUS_STOP
#define DBGMCU_I2C1_SMBUS_TIMEOUT_STOP       DBG_I2C1_SMBUS_STOP
#define DBGMCU_WWDG_STOP                     DBG_WWDG_STOP
#define DBGMCU_IWDG_STOP                     DBG_IWDG_STOP
#define DBGMCU_RTC_STOP                      DBG_RTC_STOP
#define DBGMCU_TIM14_STOP                    DBG_TIM14_STOP
#define DBGMCU_TIM13_STOP                    DBG_TIM13_STOP
#define DBGMCU_TIM12_STOP                    DBG_TIM12_STOP
#define DBGMCU_TIM7_STOP                     DBG_TIM7_STOP
#define DBGMCU_TIM6_STOP                     DBG_TIM6_STOP
#define DBGMCU_TIM5_STOP                     DBG_TIM5_STOP
#define DBGMCU_TIM4_STOP                     DBG_TIM4_STOP
#define DBGMCU_TIM3_STOP                     DBG_TIM3_STOP
#define DBGMCU_TIM2_STOP                     DBG_TIM2_STOP

#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xE11FE200) == 0x00) && ((PERIPH) != 0x00))

/* DEBUG MCU APB2 Freeze Register bits */
#define DBGMCU_EPWM4_STOP            DBG_EPWM4_STOP
#define DBGMCU_EPWM3_STOP            DBG_EPWM3_STOP
#define DBGMCU_EPWM2_STOP            DBG_EPWM2_STOP
#define DBGMCU_EPWM1_STOP            DBG_EPWM1_STOP
#define DBGMCU_TIM10_STOP            DBG_TIM10_STOP
#define DBGMCU_TIM9_STOP             DBG_TIM9_STOP
#define DBGMCU_LPTIM_STOP            DBG_LPTIM_STOP
#define DBGMCU_TIM8_STOP             DBG_TIM8_STOP
#define DBGMCU_TIM1_STOP             DBG_TIM1_STOP

#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0x87F8FFF8) == 0x00) && ((PERIPH) != 0x00))

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

#endif /* __FT32F4XX_DBGMCU_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
