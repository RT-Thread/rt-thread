/**
 *******************************************************************************
 * @file  hc32_ll_rtc.h
 * @brief This file contains all the functions prototypes of the RTC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Delete intrusion function
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_RTC_H__
#define __HC32_LL_RTC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_RTC
 * @{
 */

#if (LL_RTC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Types RTC Global Types
 * @{
 */

/**
 * @brief RTC Init structure definition
 */
typedef struct {
    uint8_t  u8ClockSrc;                /*!< Specifies the RTC clock source.
                                             This parameter can be a value of @ref RTC_Clock_Source */
    uint8_t  u8HourFormat;              /*!< Specifies the RTC hour format.
                                             This parameter can be a value of @ref RTC_Hour_Format */
    uint8_t  u8IntPeriod;               /*!< Specifies the RTC interrupt period.
                                             This parameter can be a value of @ref RTC_Interrupt_Period */
    uint8_t  u8ClockCompen;             /*!< Specifies the validity of RTC clock compensation.
                                             This parameter can be a value of @ref RTC_Clock_Compensation */
    uint8_t  u8CompenMode;              /*!< Specifies the mode of RTC clock compensation.
                                             This parameter can be a value of @ref RTC_Clock_Compensation_Mode */
    uint16_t u16CompenValue;            /*!< Specifies the value of RTC clock compensation.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 0x1FF */
} stc_rtc_init_t;

/**
 * @brief RTC Date structure definition
 */
typedef struct {
    uint8_t u8Year;                     /*!< Specifies the RTC Year.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 99 */
    uint8_t u8Month;                    /*!< Specifies the RTC Month (in Decimal format).
                                             This parameter can be a value of @ref RTC_Month */
    uint8_t u8Day;                      /*!< Specifies the RTC Day.
                                             This parameter can be a number between Min_Data = 1 and Max_Data = 31 */
    uint8_t u8Weekday;                  /*!< Specifies the RTC Weekday.
                                             This parameter can be a value of @ref RTC_Weekday */
} stc_rtc_date_t;

/**
 * @brief RTC Time structure definition
 */
typedef struct {
    uint8_t u8Hour;                     /*!< Specifies the RTC Hour.
                                             This parameter can be a number between Min_Data = 1 and Max_Data = 12 if the RTC_HOUR_FMT_12H is selected.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HOUR_FMT_24H is selected */
    uint8_t u8Minute;                   /*!< Specifies the RTC Minute.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 59 */
    uint8_t u8Second;                   /*!< Specifies the RTC Second.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 59 */
    uint8_t u8AmPm;                     /*!< Specifies the RTC Am/Pm Time (in RTC_HOUR_FMT_12H mode).
                                             This parameter can be a value of @ref RTC_Hour12_AM_PM */
} stc_rtc_time_t;

/**
 * @brief RTC Alarm structure definition
 */
typedef struct {
    uint8_t u8AlarmHour;                /*!< Specifies the RTC Alarm Hour.
                                           This parameter can be a number between Min_Data = 1 and Max_Data = 12 if the RTC_HOUR_FMT_12H is selected.
                                           This parameter can be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HOUR_FMT_24H is selected */
    uint8_t u8AlarmMinute;              /*!< Specifies the RTC Alarm Minute.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 59 */
    uint8_t u8AlarmWeekday;             /*!< Specifies the RTC Alarm Weekday.
                                             This parameter can be a value of @ref RTC_Alarm_Weekday */
    uint8_t u8AlarmAmPm;                /*!< Specifies the RTC Alarm Am/Pm Time (in RTC_HOUR_FMT_12H mode).
                                             This parameter can be a value of @ref RTC_Hour12_AM_PM */
} stc_rtc_alarm_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Macros RTC Global Macros
 * @{
 */

/**
 * @defgroup RTC_Data_Format RTC Data Format
 * @{
 */
#define RTC_DATA_FMT_DEC                        (0x00U)     /*!< Decimal data format */
#define RTC_DATA_FMT_BCD                        (0x01U)     /*!< BCD data format     */
/**
 * @}
 */

/**
 * @defgroup RTC_Decimal_BCD_Conversion RTC Decimal BCD Conversion
 * @{
 */
#define RTC_DEC2BCD(__DATA__)                   ((((__DATA__) / 10U) << 4U) + ((__DATA__) % 10U))
#define RTC_BCD2DEC(__DATA__)                   ((((__DATA__) >> 4U) * 10U) + ((__DATA__) & 0x0FU))
/**
 * @}
 */

/**
 * @defgroup RTC_Clock_Source RTC Clock Source
 * @{
 */
#define RTC_CLK_SRC_XTAL32                      (0U)                                    /*!< XTAL32 Clock            */
#define RTC_CLK_SRC_LRC                         (RTC_CR3_RCKSEL | RTC_CR3_LRCEN)        /*!< RTC LRC Clock           */
#define RTC_CLK_SRC_XTAL_DIV                    (RTC_CR3_RCKSEL | PWC_PWRC6_RTCCKSEL_0) /*!< XTAL Fractional Divider */
#define RTC_CLK_SRC_EXTCLK                      (RTC_CR3_RCKSEL | PWC_PWRC6_RTCCKSEL_1) /*!< External Clock          */
/**
 * @}
 */

/**
 * @defgroup RTC_Hour_Format RTC Hour Format
 * @{
 */
#define RTC_HOUR_FMT_12H                        (0U)                /*!< 12 hour time system */
#define RTC_HOUR_FMT_24H                        (RTC_CR1_AMPM)      /*!< 24 hour time system */
/**
 * @}
 */

/**
 * @defgroup RTC_Interrupt_Period RTC Interrupt Period
 * @{
 */
#define RTC_INT_PERIOD_INVD                     (0U)                          /*!< Interrupt period invalid         */
#define RTC_INT_PERIOD_PER_HALF_SEC             (0x01U << RTC_CR1_PRDS_POS)   /*!< Interrupt period per half second */
#define RTC_INT_PERIOD_PER_SEC                  (0x02U << RTC_CR1_PRDS_POS)   /*!< Interrupt period per second      */
#define RTC_INT_PERIOD_PER_MINUTE               (0x03U << RTC_CR1_PRDS_POS)   /*!< Interrupt period per minute      */
#define RTC_INT_PERIOD_PER_HOUR                 (0x04U << RTC_CR1_PRDS_POS)   /*!< Interrupt period per hour        */
#define RTC_INT_PERIOD_PER_DAY                  (0x05U << RTC_CR1_PRDS_POS)   /*!< Interrupt period per day         */
#define RTC_INT_PERIOD_PER_MONTH                (0x06U << RTC_CR1_PRDS_POS)   /*!< Interrupt period per month       */
/**
 * @}
 */

/**
 * @defgroup RTC_Clock_Compensation RTC Clock Compensation
 * @{
 */
#define RTC_CLK_COMPEN_DISABLE                  (0U)
#define RTC_CLK_COMPEN_ENABLE                   (RTC_ERRCRH_COMPEN)
/**
 * @}
 */

/**
 * @defgroup RTC_Clock_Compensation_Mode RTC Clock Compensation Mode
 * @{
 */
#define RTC_CLK_COMPEN_MD_DISTRIBUTED           (0U)                    /*!< Distributed compensation 1Hz output */
#define RTC_CLK_COMPEN_MD_UNIFORM               (RTC_CR1_ONEHZSEL)      /*!< Uniform compensation 1Hz output     */
/**
 * @}
 */

/**
 * @defgroup RTC_Hour12_AM_PM RTC Hour12 AM/PM
 * @{
 */
#define RTC_HOUR_24H                            (0U)                /*!< 24-hour format */
#define RTC_HOUR_12H_AM                         (0U)                /*!< AM in 12-hour  */
#define RTC_HOUR_12H_PM                         (RTC_HOUR_HOURD_1)  /*!< PM in 12-hour  */
/**
 * @}
 */

/**
 * @defgroup RTC_Month RTC Month
 * @{
 */
#define RTC_MONTH_JANUARY                       (0x01U)
#define RTC_MONTH_FEBRUARY                      (0x02U)
#define RTC_MONTH_MARCH                         (0x03U)
#define RTC_MONTH_APRIL                         (0x04U)
#define RTC_MONTH_MAY                           (0x05U)
#define RTC_MONTH_JUNE                          (0x06U)
#define RTC_MONTH_JULY                          (0x07U)
#define RTC_MONTH_AUGUST                        (0x08U)
#define RTC_MONTH_SEPTEMBER                     (0x09U)
#define RTC_MONTH_OCTOBER                       (0x0AU)
#define RTC_MONTH_NOVEMBER                      (0x0BU)
#define RTC_MONTH_DECEMBER                      (0x0CU)
/**
 * @}
 */

/**
 * @defgroup RTC_Weekday RTC Weekday
 * @{
 */
#define RTC_WEEKDAY_SUNDAY                      (0x00U)
#define RTC_WEEKDAY_MONDAY                      (0x01U)
#define RTC_WEEKDAY_TUESDAY                     (0x02U)
#define RTC_WEEKDAY_WEDNESDAY                   (0x03U)
#define RTC_WEEKDAY_THURSDAY                    (0x04U)
#define RTC_WEEKDAY_FRIDAY                      (0x05U)
#define RTC_WEEKDAY_SATURDAY                    (0x06U)
/**
 * @}
 */

/**
 * @defgroup RTC_Alarm_Weekday RTC Alarm Weekday
 * @{
 */
#define RTC_ALARM_WEEKDAY_SUNDAY                (0x01U)
#define RTC_ALARM_WEEKDAY_MONDAY                (0x02U)
#define RTC_ALARM_WEEKDAY_TUESDAY               (0x04U)
#define RTC_ALARM_WEEKDAY_WEDNESDAY             (0x08U)
#define RTC_ALARM_WEEKDAY_THURSDAY              (0x10U)
#define RTC_ALARM_WEEKDAY_FRIDAY                (0x20U)
#define RTC_ALARM_WEEKDAY_SATURDAY              (0x40U)
#define RTC_ALARM_WEEKDAY_EVERYDAY              (0x7FU)
/**
 * @}
 */

/**
 * @defgroup RTC_Flag RTC Flag
 * @{
 */
#define RTC_FLAG_RD_WR                          (RTC_CR2_RWEN)                      /*!< Read and write permission flag */
#define RTC_FLAG_ALARM                          (RTC_CR2_ALMF)                      /*!< Alarm flag                     */
#define RTC_FLAG_PERIOD                         (RTC_CR2_PRDF)                      /*!< Period flag                    */
#define RTC_FLAG_ALL                            (RTC_FLAG_RD_WR | RTC_FLAG_ALARM | RTC_FLAG_PERIOD)
#define RTC_FLAG_CLR_ALL                        (RTC_FLAG_ALARM | RTC_FLAG_PERIOD)
/**
 * @}
 */

/**
 * @defgroup RTC_Interrupt RTC Interrupt
 * @{
 */
#define RTC_INT_PERIOD                          (RTC_CR2_PRDIE)                     /*!< Period interrupt          */
#define RTC_INT_ALARM                           (RTC_CR2_ALMIE)                     /*!< Alarm interrupt           */
#define RTC_INT_ALL                             (RTC_INT_PERIOD | RTC_INT_ALARM)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup RTC_Global_Functions
 * @{
 */

/* Initialization and configuration functions */
int32_t RTC_DeInit(void);
int32_t RTC_Init(const stc_rtc_init_t *pstcRtcInit);
int32_t RTC_StructInit(stc_rtc_init_t *pstcRtcInit);
int32_t RTC_EnterRwMode(void);
int32_t RTC_ExitRwMode(void);

/* Control configuration */
int32_t RTC_ConfirmLPMCond(void);
void RTC_SetIntPeriod(uint8_t u8Period);
void RTC_SetClockSrc(uint8_t u8Src);
void RTC_SetClockCompenValue(uint16_t u16Value);
en_functional_state_t RTC_GetCounterState(void);
void RTC_Cmd(en_functional_state_t enNewState);
void RTC_LrcCmd(en_functional_state_t enNewState);
void RTC_OneHzOutputCmd(en_functional_state_t enNewState);
void RTC_ClockCompenCmd(en_functional_state_t enNewState);

/* Date and time functions */
int32_t RTC_SetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate);
int32_t RTC_GetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate);
int32_t RTC_SetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime);
int32_t RTC_GetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime);

/* Alarm configuration functions */
int32_t RTC_SetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm);
int32_t RTC_GetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm);
void RTC_AlarmCmd(en_functional_state_t enNewState);

/* Interrupt and flag management functions */
void RTC_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState);
en_flag_status_t RTC_GetStatus(uint32_t u32Flag);
void RTC_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* LL_RTC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_RTC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
