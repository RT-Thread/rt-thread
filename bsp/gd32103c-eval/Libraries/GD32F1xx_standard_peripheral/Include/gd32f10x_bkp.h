/**
  ******************************************************************************
  * @brief   BKP header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_BKP_H
#define __GD32F10X_BKP_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup BKP
  * @{
  */

/** @defgroup BKP_Exported_Constants
  * @{
  */

/** @defgroup TAMPER_pin_active_level
  * @{
  */
#define BKP_TPAL_HIGH              ((uint16_t)0x0000)
#define BKP_TPAL_LOW               ((uint16_t)0x0002)

/**
  * @}
  */

/** @defgroup RTC_output_on_the_TAMPER_pin
  * @{
  */
#define BKP_RTCOUTPUT_NULL         ((uint16_t)0x0000)
#define BKP_RTCOUTPUT_CLKCAL       ((uint16_t)0x0080)
#define BKP_RTCOUTPUT_ALARM        ((uint16_t)0x0100)
#define BKP_RTCOUTPUT_SECOND       ((uint16_t)0x0300)

/**
  * @}
  */

/** @defgroup Backup_Data_Register
  * @{
  */
#define BKP_DR1                    ((uint16_t)0x0004)
#define BKP_DR2                    ((uint16_t)0x0008)
#define BKP_DR3                    ((uint16_t)0x000C)
#define BKP_DR4                    ((uint16_t)0x0010)
#define BKP_DR5                    ((uint16_t)0x0014)
#define BKP_DR6                    ((uint16_t)0x0018)
#define BKP_DR7                    ((uint16_t)0x001C)
#define BKP_DR8                    ((uint16_t)0x0020)
#define BKP_DR9                    ((uint16_t)0x0024)
#define BKP_DR10                   ((uint16_t)0x0028)
#define BKP_DR11                   ((uint16_t)0x0040)
#define BKP_DR12                   ((uint16_t)0x0044)
#define BKP_DR13                   ((uint16_t)0x0048)
#define BKP_DR14                   ((uint16_t)0x004C)
#define BKP_DR15                   ((uint16_t)0x0050)
#define BKP_DR16                   ((uint16_t)0x0054)
#define BKP_DR17                   ((uint16_t)0x0058)
#define BKP_DR18                   ((uint16_t)0x005C)
#define BKP_DR19                   ((uint16_t)0x0060)
#define BKP_DR20                   ((uint16_t)0x0064)
#define BKP_DR21                   ((uint16_t)0x0068)
#define BKP_DR22                   ((uint16_t)0x006C)
#define BKP_DR23                   ((uint16_t)0x0070)
#define BKP_DR24                   ((uint16_t)0x0074)
#define BKP_DR25                   ((uint16_t)0x0078)
#define BKP_DR26                   ((uint16_t)0x007C)
#define BKP_DR27                   ((uint16_t)0x0080)
#define BKP_DR28                   ((uint16_t)0x0084)
#define BKP_DR29                   ((uint16_t)0x0088)
#define BKP_DR30                   ((uint16_t)0x008C)
#define BKP_DR31                   ((uint16_t)0x0090)
#define BKP_DR32                   ((uint16_t)0x0094)
#define BKP_DR33                   ((uint16_t)0x0098)
#define BKP_DR34                   ((uint16_t)0x009C)
#define BKP_DR35                   ((uint16_t)0x00A0)
#define BKP_DR36                   ((uint16_t)0x00A4)
#define BKP_DR37                   ((uint16_t)0x00A8)
#define BKP_DR38                   ((uint16_t)0x00AC)
#define BKP_DR39                   ((uint16_t)0x00B0)
#define BKP_DR40                   ((uint16_t)0x00B4)
#define BKP_DR41                   ((uint16_t)0x00B8)
#define BKP_DR42                   ((uint16_t)0x00BC)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup BKP_Exported_Functions
  * @{
  */
void BKP_DeInit(void);
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);
void BKP_RTCOutputConfig(uint16_t BKP_RTCOUTPUT);
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);
void BKP_TamperPinConfig(uint16_t BKP_TPAL, TypeState NewValue);
void BKP_TamperINT_Enable(TypeState NewValue);
TypeState BKP_GetBitState(void);
void BKP_ClearBitState(void);
TypeState BKP_GetIntBitState(void);
void BKP_ClearIntBitState(void);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_BKP_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

