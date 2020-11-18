/**
 **************************************************************************
 * File Name    : at32f4xx_dbgmcu.h
 * Description  : at32f4xx MCUDBG header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_MCUDBG_H
#define __AT32F4xx_MCUDBG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
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

#define MCUDBG_SLEEP                        ((uint32_t)0x00000001)
#define MCUDBG_STOP                         ((uint32_t)0x00000002)
#define MCUDBG_STANDBY                      ((uint32_t)0x00000004)
#define MCUDBG_IWDG_STOP                    ((uint32_t)0x00000100)
#define MCUDBG_WWDG_STOP                    ((uint32_t)0x00000200)
#define MCUDBG_TMR1_STOP                    ((uint32_t)0x00000400)
#define MCUDBG_TMR2_STOP                    ((uint32_t)0x00000800)
#define MCUDBG_TMR3_STOP                    ((uint32_t)0x00001000)
#define MCUDBG_TMR4_STOP                    ((uint32_t)0x00002000)
#define MCUDBG_CAN1_STOP                    ((uint32_t)0x00004000)
#define MCUDBG_I2C1_SMBUS_TIMEOUT           ((uint32_t)0x00008000)
#define MCUDBG_I2C2_SMBUS_TIMEOUT           ((uint32_t)0x00010000)
#define MCUDBG_TMR8_STOP                    ((uint32_t)0x00020000)
#define MCUDBG_TMR5_STOP                    ((uint32_t)0x00040000)
#define MCUDBG_TMR6_STOP                    ((uint32_t)0x00080000)
#define MCUDBG_TMR7_STOP                    ((uint32_t)0x00100000)
#define MCUDBG_TMR15_STOP                   ((uint32_t)0x00400000)
#define MCUDBG_TMR12_STOP                   ((uint32_t)0x02000000)
#define MCUDBG_TMR13_STOP                   ((uint32_t)0x04000000)
#define MCUDBG_TMR14_STOP                   ((uint32_t)0x08000000)
#define MCUDBG_TMR9_STOP                    ((uint32_t)0x10000000)
#define MCUDBG_TMR10_STOP                   ((uint32_t)0x20000000)
#define MCUDBG_TMR11_STOP                   ((uint32_t)0x40000000)
#define MCUDBG_I2C3_SMBUS_TIMEOUT           ((uint32_t)0x80000000)

#define IS_MCUDBG_PERIPH(PERIPH)            ((((PERIPH) & 0x008000F8) == 0x00) && ((PERIPH) != 0x00))
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

uint32_t MCUDBG_GetRevID(void);
uint32_t MCUDBG_GetDevID(void);
void MCUDBG_PeriphDebugModeConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_MCUDBG_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


