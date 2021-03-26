/**
  ******************************************************************************
  * @brief   RTC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_RTC_H
#define __GD32F10X_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_Exported_Defines
  * @{
  */

/** @defgroup RTC_Interrupt_Def
  * @{
  */
#define RTC_INT_OVF                        ((uint16_t)0x0004)  /*!< Overflow interrupt */
#define RTC_INT_AF                         ((uint16_t)0x0002)  /*!< Alarm interrupt */
#define RTC_INT_SF                         ((uint16_t)0x0001)  /*!< Second interrupt */

/**
  * @}
  */

/** @defgroup RTC_Interrupts_Flags
  * @{
  */
#define RTC_FLAG_LWOFF                     ((uint16_t)0x0020)  /*!< Last write operation finished flag */
#define RTC_FLAG_RSF                       ((uint16_t)0x0008)  /*!< Registers Synchronized flag */
#define RTC_FLAG_OVF                       ((uint16_t)0x0004)  /*!< Overflow flag */
#define RTC_FLAG_AF                        ((uint16_t)0x0002)  /*!< Alarm flag */
#define RTC_FLAG_SF                        ((uint16_t)0x0001)  /*!< Second flag */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions
  * @{
  */
void RTC_INT_Enable(uint16_t RTC_int, TypeState NewValue);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
uint32_t  RTC_GetCounter(void);
void RTC_SetCounter(uint32_t CounterValue);
void RTC_SetPrescaler(uint32_t PrescalerValue);
void RTC_SetAlarm(uint32_t AlarmTime);
uint32_t  RTC_GetDividerValue(void);
void RTC_WaitLWOFF(void);
void RTC_WaitRSF(void);
TypeState RTC_GetBitState(uint16_t RTC_flag);
void RTC_ClearBitState(uint16_t RTC_flag);
TypeState RTC_GetIntBitState(uint16_t RTC_INT);
void RTC_ClearIntBitState(uint16_t RTC_INT);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_RTC_H */

/**
  * @}
  */

/**
  * @}
  */
