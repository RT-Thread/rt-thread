/**
 *******************************************************************************
 * @file  hc32f4a0_rtc.h
 * @brief This file contains all the functions prototypes of the RTC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_RTC_H__
#define __HC32F4A0_RTC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_RTC
 * @{
 */

#if (DDL_RTC_ENABLE == DDL_ON)

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
typedef struct
{
    uint8_t  u8ClockSource;             /*!< Specifies the RTC clock source.
                                             This parameter can be a value of @ref RTC_Clock_Source */

    uint8_t  u8HourFormat;              /*!< Specifies the RTC hour format.
                                             This parameter can be a value of @ref RTC_Hour_Format */

    uint8_t  u8PeriodInterrupt;         /*!< Specifies the RTC period interrupt.
                                             This parameter can be a value of @ref RTC_Period_Interrupt */

    uint8_t  u8ClkCompenEn;             /*!< Specifies the validity of RTC clock compensation.
                                             This parameter can be a value of @ref RTC_Clock_Compensation */

    uint16_t u16ClkCompenValue;         /*!< Specifies the value of RTC clock compensation.
                                             This parameter can be a number between Min_Data = 0 and Max_Data = 0x1FF */

    uint8_t  u8CompenMode;              /*!< Specifies the compensation mode of one Hz output.
                                             This parameter can be a value of @ref RTC_Output_Compen_Mode */
} stc_rtc_init_t;

/**
 * @brief RTC Date structure definition
 */
typedef struct
{
    uint8_t u8Year;             /*!< Specifies the RTC Year.
                                     This parameter can be a number between Min_Data = 0 and Max_Data = 99 */

    uint8_t u8Month;            /*!< Specifies the RTC Month (in Decimal format).
                                     This parameter can be a value of @ref RTC_Month */

    uint8_t u8Day;              /*!< Specifies the RTC Day.
                                     This parameter can be a number between Min_Data = 1 and Max_Data = 31 */

    uint8_t u8Weekday;          /*!< Specifies the RTC Weekday.
                                     This parameter can be a value of @ref RTC_Weekday */
} stc_rtc_date_t;

/**
 * @brief RTC Time structure definition
 */
typedef struct
{
    uint8_t u8Hour;             /*!< Specifies the RTC Hour.
                                     This parameter can be a number between Min_Data = 1 and Max_Data = 12 if the RTC_HOUR_FORMAT_12 is selected.
                                     This parameter can be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HOUR_FORMAT_24 is selected */

    uint8_t u8Minute;           /*!< Specifies the RTC Minute.
                                     This parameter can be a number between Min_Data = 0 and Max_Data = 59 */

    uint8_t u8Second;           /*!< Specifies the RTC Second.
                                     This parameter can be a number between Min_Data = 0 and Max_Data = 59 */

    uint8_t u8AmPm;             /*!< Specifies the RTC Am/Pm Time (in RTC_HOUR_FORMAT_12 mode).
                                     This parameter can be a value of @ref RTC_Hour12_AM_PM */
} stc_rtc_time_t;

/**
 * @brief RTC Alarm structure definition
 */
typedef struct
{
    uint8_t u8AlarmHour;        /*!< Specifies the RTC Alarm Hour.
                                   This parameter can be a number between Min_Data = 1 and Max_Data = 12 if the RTC_HOUR_FORMAT_12 is selected.
                                   This parameter can be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HOUR_FORMAT_24 is selected */

    uint8_t u8AlarmMinute;      /*!< Specifies the RTC Alarm Minute.
                                     This parameter can be a number between Min_Data = 0 and Max_Data = 59 */

    uint8_t u8AlarmWeekday;     /*!< Specifies the RTC Alarm Weekday.
                                     This parameter can be a value of @ref RTC_Alarm_Weekday */

    uint8_t u8AlarmAmPm;        /*!< Specifies the RTC Alarm Am/Pm Time (in RTC_HOUR_FORMAT_12 mode).
                                     This parameter can be a value of @ref RTC_Hour12_AM_PM */
} stc_rtc_alarm_t;

/**
 * @brief RTC Intrusion structure definition
 */
typedef struct
{
    uint8_t u8TimeStampEn;              /*!< Specifies the validity of RTC intrusion timestemp.
                                             This parameter can be a value of @ref RTC_Intrusion_Timestamp */

    uint8_t u8ResetBackupRegEn;         /*!< Specifies the validity of RTC intrusion event that trigger backup registers reset.
                                             This parameter can be a value of @ref RTC_Reset_Backup_Register */

    uint8_t u8Filter;                   /*!< Specifies the RTC intrusion pin filter.
                                             This parameter can be a value of @ref RTC_Intrusion_Filter */

    uint8_t u8TrigEdge;                 /*!< Specifies the RTC intrusion detect edge.
                                             This parameter can be a value of @ref RTC_Intrusion_Detect_Edge */
} stc_rtc_intrusion_t;

/**
 * @brief RTC Timestamp structure definition
 */
typedef struct
{
    stc_rtc_time_t stcTSTime;           /*!< Specifies the RTC Intrusion Timestamp Time members */

    uint8_t u8TSMonth;                  /*!< Specifies the Month of RTC timestamp (in Decimal format).
                                             This parameter can be a value of @ref RTC_Month */

    uint8_t u8TSDay;                    /*!< Specifies the Day of RTC timestamp.
                                             This parameter can be a number between Min_Data = 1 and Max_Data = 31 */
} stc_rtc_timestamp_t;

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
#define RTC_DATA_FORMAT_DEC                     (0x00U)             /*!< Decimal data format */
#define RTC_DATA_FORMAT_BCD                     (0x01U)             /*!< BCD data format     */
/**
 * @}
 */

/**
 * @defgroup RTC_Clock_Source RTC Clock Source
 * @{
 */
#define RTC_CLOCK_SOURCE_XTAL32                 (0U)                              /*!< XTAL32 Clock   */
#define RTC_CLOCK_SOURCE_RTCLRC                 (RTC_CR3_RCKSEL | RTC_CR3_LRCEN)  /*!< RTC LRC Clock  */
/**
 * @}
 */

/**
 * @defgroup RTC_Hour_Format RTC Hour Format
 * @{
 */
#define RTC_HOUR_FORMAT_12                      (0U)                /*!< 12 hour time system */
#define RTC_HOUR_FORMAT_24                      (RTC_CR1_AMPM)      /*!< 24 hour time system */
/**
 * @}
 */

/**
 * @defgroup RTC_Period_Interrupt RTC Period Interrupt
 * @{
 */
#define RTC_PERIOD_INT_INVALID                  (0U)                                /*!< Periodic interrupt invalid         */
#define RTC_PERIOD_INT_HALF_SECOND              (RTC_CR1_PRDS_0)                    /*!< Periodic interrupt per half second */
#define RTC_PERIOD_INT_ONE_SECOND               (RTC_CR1_PRDS_1)                    /*!< Periodic interrupt per second      */
#define RTC_PERIOD_INT_ONE_MINUTE               (RTC_CR1_PRDS_0 | RTC_CR1_PRDS_1)   /*!< Periodic interrupt per minute      */
#define RTC_PERIOD_INT_ONE_HOUR                 (RTC_CR1_PRDS_2)                    /*!< Periodic interrupt per hour        */
#define RTC_PERIOD_INT_ONE_DAY                  (RTC_CR1_PRDS_0 | RTC_CR1_PRDS_2)   /*!< Periodic interrupt per day         */
#define RTC_PERIOD_INT_ONE_MONTH                (RTC_CR1_PRDS_1 | RTC_CR1_PRDS_2)   /*!< Periodic interrupt per month       */
/**
 * @}
 */

/**
 * @defgroup RTC_Clock_Compensation RTC Clock Compensation
 * @{
 */
#define RTC_CLOCK_COMPEN_DISABLE                (0U)
#define RTC_CLOCK_COMPEN_ENABLE                 (RTC_ERRCRH_COMPEN)
/**
 * @}
 */

/**
 * @defgroup RTC_Output_Compen_Mode RTC Output Compensation Mode
 * @{
 */
#define RTC_OUTPUT_COMPEN_MODE_DISTRIBUTED      (0U)                    /*!< Distributed compensation 1Hz output */
#define RTC_OUTPUT_COMPEN_MODE_UNIFORM          (RTC_CR1_ONEHZSEL)      /*!< Uniform compensation 1Hz output     */
/**
 * @}
 */

/**
 * @defgroup RTC_Hour12_AM_PM RTC Hour12 AM/PM
 * @{
 */
#define RTC_HOUR12_AM_HOUR24                    (0U)                    /*!< AM or 24-hour format */
#define RTC_HOUR12_PM                           (RTC_HOUR_HOURD_1)      /*!< PM */
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
/**
 * @}
 */

/**
 * @defgroup RTC_Intrusion_Channel RTC Intrustion Channel
 * @{
 */
#define RTC_INTRU_CH0                           (0x00U)
#define RTC_INTRU_CH1                           (0x04U)
/**
 * @}
 */

/**
 * @defgroup RTC_Intrusion_Timestamp RTC Intrustion Timestamp
 * @{
 */
#define RTC_INTRU_TIMESTAMP_DISABLE             (0U)
#define RTC_INTRU_TIMESTAMP_ENABLE              (RTC_TPCR0_TSTPE0)
/**
 * @}
 */

/**
 * @defgroup RTC_Reset_Backup_Register RTC Reset Backup Register
 * @{
 */
#define RTC_RESET_BACKUP_REG_DISABLE            (0U)
#define RTC_RESET_BACKUP_REG_ENABLE             (RTC_TPCR0_TPRSTE0)
/**
 * @}
 */

/**
 * @defgroup RTC_Intrusion_Filter RTC Intrusion Filter
 * @{
 */
#define RTC_INTRU_FILTER_INVALID                (0U)                 /*!< Invalid filter function                                                                           */
#define RTC_INTRU_FILTER_THREE_TIME             (RTC_TPCR0_TPNF0_1)  /*!< The filter detection is consistent with the timing clock for 3 times                              */
#define RTC_INTRU_FILTER_THREE_TIME_CLK_DIV32   (RTC_TPCR0_TPNF0)    /*!< The filter detection is consistent with the 32 frequency division of the timing clock for 3 times */
/**
 * @}
 */

/**
 * @defgroup RTC_Intrusion_Detect_Edge RTC Intrusion Detect Edge
 * @{
 */
#define RTC_DETECT_EDGE_NONE                    (0U)                 /*!< No detect                      */
#define RTC_DETECT_EDGE_RISING                  (RTC_TPCR0_TPCT0_0)  /*!< Detect rising edge             */
#define RTC_DETECT_EDGE_FALLING                 (RTC_TPCR0_TPCT0_1)  /*!< Detect falling edge            */
#define RTC_DETECT_EDGE_RISING_FALLING          (RTC_TPCR0_TPCT0)    /*!< Detect rising and falling edge */
/**
 * @}
 */

/**
 * @defgroup RTC_Flag RTC Flag
 * @{
 */
#define RTC_FLAG_PRDF                           (RTC_CR2_PRDF)                      /*!< Period flag                    */
#define RTC_FLAG_ALMF                           (RTC_CR2_ALMF)                      /*!< Alarm flag                     */
#define RTC_FLAG_RWEN                           (RTC_CR2_RWEN)                      /*!< Read and write permission flag */
#define RTC_FLAG_TPOVF                          ((uint32_t)RTC_TPSR_TPOVF << 16U)   /*!< Intrusion overflow flag         */
#define RTC_FLAG_TPF0                           ((uint32_t)RTC_TPSR_TPF0  << 16U)   /*!< RTCIC0 intrusion flag           */
#define RTC_FLAG_TPF1                           ((uint32_t)RTC_TPSR_TPF1  << 16U)   /*!< RTCIC1 intrusion flag           */
/**
 * @}
 */

/**
 * @defgroup RTC_Interrupt RTC Interrupt
 * @{
 */
#define RTC_INT_PRDIE                           (RTC_CR2_PRDIE)                     /*!< Period interrupt          */
#define RTC_INT_ALMIE                           (RTC_CR2_ALMIE)                     /*!< Alarm interrupt           */
#define RTC_INT_TPIE0                           ((uint32_t)RTC_TPCR0_TPIE0 << 8U)   /*!< RTCIC0 intrusion interrupt */
#define RTC_INT_TPIE1                           ((uint32_t)RTC_TPCR1_TPIE1 << 16U)  /*!< RTCIC1 intrusion interrupt */
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
en_result_t RTC_DeInit(void);
en_result_t RTC_Init(const stc_rtc_init_t *pstcRtcInit);
en_result_t RTC_StructInit(stc_rtc_init_t *pstcRtcInit);
en_result_t RTC_EnterRwMode(void);
en_result_t RTC_ExitRwMode(void);
void RTC_PeriodIntConfig(uint8_t u8IntCond);
en_result_t RTC_LowPowerCheck(void);
void RTC_SetClkCompenValue(uint16_t u16CompenVal);
void RTC_Cmd(en_functional_state_t enNewSta);
void RTC_LrcCmd(en_functional_state_t enNewSta);
en_functional_state_t RTC_GetCounterState(void);
void RTC_OneHzOutputCmd(en_functional_state_t enNewSta);
void RTC_ClkCompenCmd(en_functional_state_t enNewSta);

/* Date and time functions */
en_result_t RTC_SetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate);
en_result_t RTC_GetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate);
en_result_t RTC_SetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime);
en_result_t RTC_GetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime);

/* Alarm configuration functions */
en_result_t RTC_SetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm);
en_result_t RTC_GetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm);
void RTC_AlarmCmd(en_functional_state_t enNewSta);

/* Intrusion timestamp functions */
en_result_t RTC_IntrusionConfig(uint8_t u8Ch, const stc_rtc_intrusion_t *pstcIntru);
en_result_t RTC_GetIntrusionTimestamp(uint8_t u8Format, stc_rtc_timestamp_t *pstcTimestamp);
void RTC_IntrusionCmd(uint8_t u8Ch, en_functional_state_t enNewSta);

/* Interrupt and flag management functions */
void RTC_IntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta);
en_flag_status_t RTC_GetStatus(uint32_t u32Flag);
void RTC_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* DDL_RTC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_RTC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
