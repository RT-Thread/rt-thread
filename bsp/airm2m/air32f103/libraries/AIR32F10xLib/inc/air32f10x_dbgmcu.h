/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AIR32F10x_DBGMCU_H
#define __AIR32F10x_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air32f10x.h"

/** @addtogroup air32f10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup DBGMCU
  * @{
  */

/** @defgroup DBGMCU_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_SLEEP                 ((uint32_t)0x00000001)
#define DBGMCU_STOP                  ((uint32_t)0x00000002)
#define DBGMCU_STANDBY               ((uint32_t)0x00000004)
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00000100)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000200)
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000400)
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000800)
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00001000)
#define DBGMCU_TIM4_STOP             ((uint32_t)0x00002000)
#define DBGMCU_CAN1_STOP             ((uint32_t)0x00004000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00008000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00010000)
#define DBGMCU_TIM8_STOP             ((uint32_t)0x00020000)
#define DBGMCU_TIM5_STOP             ((uint32_t)0x00040000)
#define DBGMCU_TIM6_STOP             ((uint32_t)0x00080000)
#define DBGMCU_TIM7_STOP             ((uint32_t)0x00100000)
#define DBGMCU_CAN2_STOP             ((uint32_t)0x00200000)
#define DBGMCU_TIM15_STOP            ((uint32_t)0x00400000)
#define DBGMCU_TIM16_STOP            ((uint32_t)0x00800000)
#define DBGMCU_TIM17_STOP            ((uint32_t)0x01000000)
#define DBGMCU_TIM12_STOP            ((uint32_t)0x02000000)
#define DBGMCU_TIM13_STOP            ((uint32_t)0x04000000)
#define DBGMCU_TIM14_STOP            ((uint32_t)0x08000000)
#define DBGMCU_TIM9_STOP             ((uint32_t)0x10000000)
#define DBGMCU_TIM10_STOP            ((uint32_t)0x20000000)
#define DBGMCU_TIM11_STOP            ((uint32_t)0x40000000)

#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0x800000F8) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Functions
  * @{
  */

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __AIR32F10x_DBGMCU_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

