/**
 **************************************************************************
 * File Name    : at32f4xx_pwr.h
 * Description  : at32f4xx PWR header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_PWR_H
#define __AT32F4xx_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
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

#define PWR_PVDS_2V2                        ((uint32_t)0x00000000)
#define PWR_PVDS_2V3                        ((uint32_t)0x00000020)
#define PWR_PVDS_2V4                        ((uint32_t)0x00000040)
#define PWR_PVDS_2V5                        ((uint32_t)0x00000060)
#define PWR_PVDS_2V6                        ((uint32_t)0x00000080)
#define PWR_PVDS_2V7                        ((uint32_t)0x000000A0)
#define PWR_PVDS_2V8                        ((uint32_t)0x000000C0)
#define PWR_PVDS_2V9                        ((uint32_t)0x000000E0)
#define IS_PWR_PVD_LEVEL(LEVEL)             (((LEVEL) == PWR_PVDS_2V2) || ((LEVEL) == PWR_PVDS_2V3)|| \
                                             ((LEVEL) == PWR_PVDS_2V4) || ((LEVEL) == PWR_PVDS_2V5)|| \
                                             ((LEVEL) == PWR_PVDS_2V6) || ((LEVEL) == PWR_PVDS_2V7)|| \
                                             ((LEVEL) == PWR_PVDS_2V8) || ((LEVEL) == PWR_PVDS_2V9))
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry 
  * @{
  */

#define PWR_SLEEPEntry_WFI              ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE              ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))

/** @defgroup Regulator_state_is_STOP_mode
  * @{
  */
#define PWR_Regulator_ON                    ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower              ((uint32_t)0x00000001)
#define IS_PWR_REGULATOR(REGULATOR)         (((REGULATOR) == PWR_Regulator_ON) || \
                                             ((REGULATOR) == PWR_Regulator_LowPower))
/**
  * @}
  */

/** @defgroup STOP_mode_entry
  * @{
  */

#define PWR_STOPEntry_WFI                   ((uint8_t)0x01)
#define PWR_STOPEntry_WFE                   ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY)            (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))

/**
  * @}
  */

/** @defgroup PWR_Flag
  * @{
  */

#define PWR_FLAG_WUF                        ((uint32_t)0x00000001)
#define PWR_FLAG_SBF                        ((uint32_t)0x00000002)
#define PWR_FLAG_PVDO                       ((uint32_t)0x00000004)
#define IS_PWR_GET_FLAG(FLAG)               (((FLAG) == PWR_FLAG_WUF) || ((FLAG) == PWR_FLAG_SBF) || \
                                             ((FLAG) == PWR_FLAG_PVDO))

#define IS_PWR_CLEAR_FLAG(FLAG)             (((FLAG) == PWR_FLAG_WUF) || ((FLAG) == PWR_FLAG_SBF))
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

void PWR_Reset(void);
void PWR_BackupAccessCtrl(FunctionalState NewState);
void PWR_PVDCtrl(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinCtrl(FunctionalState NewState);
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry);
#if defined (AT32F403xx) || defined (AT32F413xx)
    void PWR_EnterSTOPMode(uint8_t PWR_STOPEntry);
#else
    void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
#endif
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_PWR_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


