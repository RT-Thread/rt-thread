/**
******************************************************************************
* @file    HAL_pwr.h
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file contains all the functions prototypes for the PWR firmware
*          library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_PWR_H
#define __HAL_PWR_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup PWR
* @{
*/

/** @defgroup PWR_Exported_Types
* @{
*/

/**
* @}
*/

/** @defgroup PWR_Exported_Constants
* @{
*/


/** @defgroup PVD_detection_level
* @{
*/

#define PWR_PVDLevel_1V8          ((uint32_t)0x00000000)
#define PWR_PVDLevel_2V1          ((uint32_t)0x00000200)
#define PWR_PVDLevel_2V4          ((uint32_t)0x00000400)
#define PWR_PVDLevel_2V7          ((uint32_t)0x00000600)
#define PWR_PVDLevel_3V0          ((uint32_t)0x00000800)
#define PWR_PVDLevel_3V3          ((uint32_t)0x00000A00)
#define PWR_PVDLevel_3V6          ((uint32_t)0x00000C00)
#define PWR_PVDLevel_3V9          ((uint32_t)0x00000E00)
#define PWR_PVDLevel_4V2          ((uint32_t)0x00001000)
#define PWR_PVDLevel_4V5          ((uint32_t)0x00001200)
#define PWR_PVDLevel_4V8          ((uint32_t)0x00001400)
#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_1V8) || ((LEVEL) == PWR_PVDLevel_2V1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2V4) || ((LEVEL) == PWR_PVDLevel_2V7)|| \
                                 ((LEVEL) == PWR_PVDLevel_3V0) || ((LEVEL) == PWR_PVDLevel_3V3)|| \
                                 ((LEVEL) == PWR_PVDLevel_3V6) || ((LEVEL) == PWR_PVDLevel_3V9)|| \
                                 ((LEVEL) == PWR_PVDLevel_4V2) || ((LEVEL) == PWR_PVDLevel_4V5)|| \
                                 ((LEVEL) == PWR_PVDLevel_4V8))


/**
* @}
*/

/** @defgroup Regulator_state_is_STOP_mode
* @{
*/

#define PWR_Regulator_ON          ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower    ((uint32_t)0x00000002)
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))
/**
* @}
*/

/** @defgroup STOP_mode_entry
* @{
*/

#define PWR_STOPEntry_WFI         ((uint8_t)0x01)
#define PWR_STOPEntry_WFE         ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))

/**
* @}
*/

/** @defgroup PWR_Flag
* @{
*/

#define PWR_FLAG_WU               ((uint32_t)0x00000001)
#define PWR_FLAG_SB               ((uint32_t)0x00000002)
#define PWR_FLAG_PVDO             ((uint32_t)0x00000004)
#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
/**
* @}
*/

/**
* @}
*/

/** @defgroup PWR_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup PWR_Exported_Functions
* @{
*/

void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#endif /* __HAL_PWR_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
