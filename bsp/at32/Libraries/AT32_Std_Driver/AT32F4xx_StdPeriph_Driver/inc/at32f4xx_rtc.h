/**
 **************************************************************************
 * File Name    : at32f4xx_rtc.h
 * Description  : at32f4xx RTC header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_RTC_H
#define __AT32F4xx_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Exported_Constants
  * @{
  */

/** @defgroup RTC_interrupts_define
  * @{
  */

#define RTC_INT_OV                          ((uint16_t)0x0004)  /*!< Overflow interrupt */
#define RTC_INT_ALA                         ((uint16_t)0x0002)  /*!< Alarm interrupt */
#define RTC_INT_PACE                        ((uint16_t)0x0001)  /*!< Second interrupt */
#define IS_RTC_INT(INT)                     ((((INT) & (uint16_t)0xFFF8) == 0x00) && ((INT) != 0x00))
#define IS_RTC_GET_INT(INT)                 (((INT) == RTC_INT_OV) || ((INT) == RTC_INT_ALA) || \
                                             ((INT) == RTC_INT_PACE))
/**
  * @}
  */

/** @defgroup RTC_interrupts_flags
  * @{
  */

#define RTC_FLAG_RTF                        ((uint16_t)0x0020)  /*!< RTC Operation OFF flag */
#define RTC_FLAG_RSYNF                      ((uint16_t)0x0008)  /*!< Registers Synchronized flag */
#define RTC_FLAG_OV                         ((uint16_t)0x0004)  /*!< Overflow flag */
#define RTC_FLAG_ALA                        ((uint16_t)0x0002)  /*!< Alarm flag */
#define RTC_FLAG_PACE                       ((uint16_t)0x0001)  /*!< Second flag */
#define IS_RTC_CLEAR_FLAG(FLAG)             ((((FLAG) & (uint16_t)0xFFF0) == 0x00) && ((FLAG) != 0x00))
#define IS_RTC_GET_FLAG(FLAG)               (((FLAG) == RTC_FLAG_RTF) || ((FLAG) == RTC_FLAG_RSYNF) || \
                                             ((FLAG) == RTC_FLAG_OV)  || ((FLAG) == RTC_FLAG_ALA)   || \
                                             ((FLAG) == RTC_FLAG_PACE))
#define IS_RTC_DIV(DIV)                      ((DIV) <= 0xFFFFF)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RTC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions
  * @{
  */

void RTC_INTConfig(uint16_t RTC_INT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
uint32_t  RTC_GetCounter(void);
void RTC_SetCounter(uint32_t CounterValue);
void RTC_SetDIV(uint32_t PrescalerValue);
void RTC_SetAlarmValue(uint32_t AlarmValue);
uint32_t  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG);
void RTC_ClearFlag(uint16_t RTC_FLAG);
ITStatus RTC_GetINTStatus(uint16_t RTC_INT);
void RTC_ClearINTPendingBit(uint16_t RTC_INT);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_RTC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


