/**
  ******************************************************************************
  * @brief   PWR header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_PWR_H
#define __GD32F10X_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup PWR
  * @{
  */

/** @defgroup PWR_Exported_Constants
  * @{
  */

/** @defgroup PWR_Low_Voltage_Detector_Threshold
  * @{
  */
#define PWR_LVDT_0                    PWR_CTLR_LVDT_2V2
#define PWR_LVDT_1                    PWR_CTLR_LVDT_2V3
#define PWR_LVDT_2                    PWR_CTLR_LVDT_2V4
#define PWR_LVDT_3                    PWR_CTLR_LVDT_2V5
#define PWR_LVDT_4                    PWR_CTLR_LVDT_2V6
#define PWR_LVDT_5                    PWR_CTLR_LVDT_2V7
#define PWR_LVDT_6                    PWR_CTLR_LVDT_2V8
#define PWR_LVDT_7                    PWR_CTLR_LVDT_2V9

/**
  * @}
  */

/** @defgroup PWR_LDO_state_in_Deep-sleep_mode
  * @{
  */
#define PWR_LDO_ON                    ((uint32_t)0x00000000)
#define PWR_LDO_LOWPOWER              PWR_CTLR_LDOLP

/**
  * @}
  */

/** @defgroup PWR_Sleep_mode_entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI            ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE            ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup PWR_Deep-sleep_mode_entry
  * @{
  */
#define PWR_DEEPSLEEPENTRY_WFI        ((uint8_t)0x01)
#define PWR_DEEPSLEEPENTRY_WFE        ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup PWR_Standby_mode_entry
  * @{
  */
#define PWR_STDBYENTRY_WFI            ((uint8_t)0x01)
#define PWR_STDBYENTRY_WFE            ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup PWR_Flag
  * @{
  */
#define PWR_FLAG_WKUP                 PWR_STR_WUF
#define PWR_FLAG_STB                  PWR_STR_SBF
#define PWR_FLAG_LVDF                 PWR_STR_LVDF

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PWR_Exported_Functions
  * @{
  */
void PWR_DeInit(void);
void PWR_BackupAccess_Enable(TypeState NewValue);
void PWR_LVDConfig(uint32_t PWR_LVDT, TypeState NewValue);
void PWR_WKUP_Pin_Enable(TypeState NewValue);
void PWR_SLEEPMode_Entry(uint8_t PWR_SLEEPENTRY);
void PWR_DEEPSLEEPMode_Entry(uint32_t PWR_LDO, uint8_t PWR_DEEPSLEEPENTRY);
void PWR_STDBYMode_Entry(uint8_t PWR_STDBYENTRY);
TypeState PWR_GetBitState(uint32_t PWR_FLAG);
void PWR_ClearBitState(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_PWR_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

