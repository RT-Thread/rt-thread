/**
  ******************************************************************************
  * @brief   MCUDBG header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_MCUDBG_H
#define __GD32F10X_MCUDBG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup MCUDBG
  * @{
  */

/* Exported types ------------------------------------------------------------*/



/* Exported constants --------------------------------------------------------*/

/** @defgroup MCUDBG_Exported_Constants
  * @{
  */
#define MCUDBG_SLEEP_HOLD               ((uint32_t)0x00000001)
#define MCUDBG_DEEPSLEEP_HOLD           ((uint32_t)0x00000002)
#define MCUDBG_STDBY_HOLD               ((uint32_t)0x00000004)
#define MCUDBG_IWDG_HOLD                ((uint32_t)0x00000100)
#define MCUDBG_WWDG_HOLD                ((uint32_t)0x00000200)
#define MCUDBG_TIMER1_HOLD              ((uint32_t)0x00000400)
#define MCUDBG_TIMER2_HOLD              ((uint32_t)0x00000800)
#define MCUDBG_TIMER3_HOLD              ((uint32_t)0x00001000)
#define MCUDBG_TIMER4_HOLD              ((uint32_t)0x00002000)
#define MCUDBG_CAN1_HOLD                ((uint32_t)0x00004000)
#define MCUDBG_I2C1_HOLD                ((uint32_t)0x00008000)
#define MCUDBG_I2C2_HOLD                ((uint32_t)0x00010000)
#define MCUDBG_TIMER5_HOLD              ((uint32_t)0x00020000)
#define MCUDBG_TIMER6_HOLD              ((uint32_t)0x00040000)
#define MCUDBG_TIMER7_HOLD              ((uint32_t)0x00080000)
#define MCUDBG_TIMER8_HOLD              ((uint32_t)0x00100000)
#define MCUDBG_CAN2_HOLD                ((uint32_t)0x00200000)
#define MCUDBG_TIMER12_HOLD             ((uint32_t)0x02000000)
#define MCUDBG_TIMER13_HOLD             ((uint32_t)0x04000000)
#define MCUDBG_TIMER14_HOLD             ((uint32_t)0x08000000)
#define MCUDBG_TIMER9_HOLD              ((uint32_t)0x10000000)
#define MCUDBG_TIMER10_HOLD             ((uint32_t)0x20000000)
#define MCUDBG_TIMER11_HOLD             ((uint32_t)0x40000000)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup MCUDBG_Exported_Functions
  * @{
  */

uint32_t MCUDBG_GetREVID(void);
uint32_t MCUDBG_GetDEVID(void);
void MCUDBG_PeriphConfig(uint32_t MCUDBG_Periph, TypeState NewValue);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_MCUDBG_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

