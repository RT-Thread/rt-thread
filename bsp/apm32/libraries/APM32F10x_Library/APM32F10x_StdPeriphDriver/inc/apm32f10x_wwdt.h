/*!
 * @file        apm32f10x_wwdt.h
 *
 * @brief       This file contains all the functions prototypes for the WWDT firmware library
 *
 * @version     V1.0.1
 *
 * @date        2021-03-23
 *
 */

#ifndef __APM32F10X_WWDT_H
#define __APM32F10X_WWDT_H

#include "apm32f10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup WWDT_Driver  WWDT Driver
  @{
*/

/** @addtogroup  WWDT_Enumerations Enumerations
  @{
*/

/**
 * @brief    WWDT Timebase(Prescaler) define
 */
typedef enum
{
    WWDT_TIME_BASE_1 = 0x00000000,
    WWDT_TIME_BASE_2 = 0x00000080,
    WWDT_TIME_BASE_4 = 0x00000100,
    WWDT_TIME_BASE_8 = 0x00000180
}WWDT_TIME_BASE_T;

/**@} end of group WWDT_Enumerations*/

/** @addtogroup  WWDT_Fuctions Fuctions
  @{
*/

/** WWDT reset */
void WWDT_Reset(void);

/** Config WWDT Timebase */
void WWDT_ConfigTimebase(WWDT_TIME_BASE_T timeBase);

/** Config Window Data */
void WWDT_ConfigWindowData(uint8_t windowData);

/** Config Couter */
void WWDT_ConfigCounter(uint8_t counter);

/** Enable WWDT and Early Wakeup interrupt */
void WWDT_EnableEWI(void);
void WWDT_Enable(uint8_t count);

/** Read Flag and Clear Flag */
uint8_t WWDT_ReadFlag(void);
void WWDT_ClearFlag(void);

/**@} end of group WWDT_Fuctions*/
/**@} end of group WWDT_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_WWDT_H */
