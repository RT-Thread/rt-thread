/*!
 * @file       apm32f10x_pmu.h
 *
 * @brief      This file contains all the functions prototypes for the PMU firmware library.
 *
 * @version    V1.0.1
 *
 * @date       2021-03-23
 *
 */

#ifndef __APM32F10X_PMU_H
#define __APM32F10X_PMU_H

#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup PMU_Driver PMU Driver
  @{
*/

/** @addtogroup PMU_Enumerations Enumerations
  @{
*/

typedef enum
{
    PMU_PVD_LEVEL_2V2    = 0x00,    //!< PVD detection level set to 2.2V
    PMU_PVD_LEVEL_2V3    = 0x01,    //!< PVD detection level set to 2.3V
    PMU_PVD_LEVEL_2V4    = 0x02,    //!< PVD detection level set to 2.4V
    PMU_PVD_LEVEL_2V5    = 0x03,    //!< PVD detection level set to 2.5V
    PMU_PVD_LEVEL_2V6    = 0x04,    //!< PVD detection level set to 2.6V
    PMU_PVD_LEVEL_2V7    = 0x05,    //!< PVD detection level set to 2.7V
    PMU_PVD_LEVEL_2V8    = 0x06,    //!< PVD detection level set to 2.8V
    PMU_PVD_LEVEL_2V9    = 0x07,    //!< PVD detection level set to 2.9V
} PMU_PVD_LEVEL_T;

typedef enum
{
    PMU_REGULATOR_ON       = 0x00,
    PMU_REGULATOR_LOWPOWER = 0x01
} PMU_REGULATOR_T;

typedef enum
{
    PMU_STOP_ENTRY_WFI     = 0x01,
    PMU_STOP_ENTRY_WFE     = 0x02
} PMU_STOP_ENTRY_T;

typedef enum
{
    PMU_FLAG_WUE,
    PMU_FLAG_SB,
    PMU_FLAG_PVDO
} PMU_FLAG_T;

/**@} end of group PMU_Enumerations*/


/** @addtogroup PMU_Fuctions Fuctions
  @{
*/

/** PMU Reset */
void PMU_Reset(void);

/** Configuration and Operation modes */
void PMU_EnableBackupAccess(void);
void PMU_DisableBackupAccess(void);
void PMU_EnablePVD(void);
void PMU_DisablePVD(void);
void PMU_ConfigPVDLevel(PMU_PVD_LEVEL_T level);
void PMU_EnableWakeUpPin(void);
void PMU_DisableWakeUpPin(void);
void PMU_EnterSTOPMode(PMU_REGULATOR_T regulator, PMU_STOP_ENTRY_T entry);
void PMU_EnterSTANDBYMode(void);

/** flags */
uint8_t PMU_ReadStatusFlag(PMU_FLAG_T flag);
void PMU_ClearStatusFlag(PMU_FLAG_T flag);

/**@} end of group PMU_Fuctions*/
/**@} end of group PMU_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_PMU_H */
