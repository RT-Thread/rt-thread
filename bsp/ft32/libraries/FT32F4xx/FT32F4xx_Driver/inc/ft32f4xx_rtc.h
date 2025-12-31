/**
  ******************************************************************************
  * @file               ft32f4xx_rtc.h
  * @author             Rwang
  * @brief              This file contains all the functions prototypes for the RTC firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2025-03-24
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_RTC_H
#define __FT32F4XX_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f407xe.h"



/** @addtogroup RTC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  RTC Init structures definition
  */
typedef struct
{
    uint32_t RTC_HourFormat;   /*!< Specifies the RTC Hour Format.
                             This parameter can be a value of @ref RTC_Hour_Formats */

    uint32_t RTC_AsynchPrediv; /*!< Specifies the RTC Asynchronous Predivider value.
                             This parameter must be set to a value lower than 0x7F */

    uint32_t RTC_SynchPrediv;  /*!< Specifies the RTC Synchronous Predivider value.
                             This parameter must be set to a value lower than 0x1FFF */
} RTC_InitTypeDef;

/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
    uint8_t RTC_Hours;    /*!< Specifies the RTC Time Hour.
                        This parameter must be set to a value in the 0-12 range
                        if the RTC_HourFormat_12 is selected or 0-23 range if
                        the RTC_HourFormat_24 is selected. */

    uint8_t RTC_Minutes;  /*!< Specifies the RTC Time Minutes.
                        This parameter must be set to a value in the 0-59 range. */

    uint8_t RTC_Seconds;  /*!< Specifies the RTC Time Seconds.
                        This parameter must be set to a value in the 0-59 range. */

    uint8_t RTC_H12;      /*!< Specifies the RTC AM/PM Time.
                        This parameter can be a value of @ref RTC_AM_PM_Definitions */
} RTC_TimeTypeDef;

/**
  * @brief  RTC Date structure definition
  */
typedef struct
{
    uint8_t RTC_WeekDay; /*!< Specifies the RTC Date WeekDay.
                        This parameter can be a value of @ref RTC_WeekDay_Definitions */

    uint8_t RTC_Month;   /*!< Specifies the RTC Date Month.
                        This parameter can be a value of @ref RTC_Month_Date_Definitions */

    uint8_t RTC_Date;     /*!< Specifies the RTC Date.
                        This parameter must be set to a value in the 1-31 range. */

    uint8_t RTC_Year;     /*!< Specifies the RTC Date Year.
                        This parameter must be set to a value in the 0-99 range. */
} RTC_DateTypeDef;

/**
  * @brief  RTC Alarm structure definition
  */
typedef struct
{
    RTC_TimeTypeDef RTC_AlarmTime;     /*!< Specifies the RTC Alarm Time members. */

    uint32_t RTC_AlarmMask;            /*!< Specifies the RTC Alarm Masks.
                                      This parameter can be a value of @ref RTC_AlarmMask_Definitions */

    uint32_t RTC_AlarmDateWeekDaySel;  /*!< Specifies the RTC Alarm is on Date or WeekDay.
                                      This parameter can be a value of @ref RTC_AlarmDateWeekDay_Definitions */

    uint8_t RTC_AlarmDateWeekDay;      /*!< Specifies the RTC Alarm Date/WeekDay.
                                      This parameter must be set to a value in the 1-31 range
                                      if the Alarm Date is selected.
                                      This parameter can be a value of @ref RTC_WeekDay_Definitions
                                      if the Alarm WeekDay is selected. */
} RTC_AlarmTypeDef;



/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */


/** @defgroup RTC_Hour_Formats
  * @{
  */
#define RTC_HourFormat_24              ((uint32_t)0x00000000)
#define RTC_HourFormat_12              RTC_CR_FMT
#define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == RTC_HourFormat_12) || \
                                        ((FORMAT) == RTC_HourFormat_24))
/**
  * @}
  */

/** @defgroup RTC_Asynchronous_Predivider PREDIV_A[6:0]
  * @{
  */
#define IS_RTC_ASYNCH_PREDIV(PREDIV)    ((PREDIV) <= 0x7F)
/**
  * @}
  */


/** @defgroup RTC_Synchronous_Predivider PREDIV_S[14:0]
  * @{
  */
#define IS_RTC_SYNCH_PREDIV(PREDIV)     ((PREDIV) <= 0x7FFF)
/**
  * @}
  */

/** @defgroup RTC_Weakup_counter WUT[15:0]
  * @{
  */
#define IS_RTC_WeakUp_CNT(CNT)  ((CNT) <= 0xFFFF)
/**
  * @}
  */


/** @defgroup RTC_Time_Definitions
  * @{
  */
#define IS_RTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_RTC_HOUR24(HOUR)            ((HOUR) <= 23)
#define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
#define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= 59)
/**
  * @}
  */

/** @defgroup RTC_AM_PM_Definitions
  * @{
  */
#define RTC_H12_AM                     ((uint32_t)0x00000000)
#define RTC_H12_PM                     ((uint32_t)0x00000001)
#define IS_RTC_H12(PM)                 (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))
/**
  * @}
  */

/** @defgroup RTC_Year_Date_Definitions
  * @{
  */
#define IS_RTC_YEAR(YEAR)              ((YEAR) <= 99)
/**
  * @}
  */

/** @defgroup RTC_Month_Date_Definitions
  * @{
  */
#define RTC_Month_January              ((uint8_t)0x01)
#define RTC_Month_February             ((uint8_t)0x02)
#define RTC_Month_March                ((uint8_t)0x03)
#define RTC_Month_April                ((uint8_t)0x04)
#define RTC_Month_May                  ((uint8_t)0x05)
#define RTC_Month_June                 ((uint8_t)0x06)
#define RTC_Month_July                 ((uint8_t)0x07)
#define RTC_Month_August               ((uint8_t)0x08)
#define RTC_Month_September            ((uint8_t)0x09)
#define RTC_Month_October              ((uint8_t)0x10)
#define RTC_Month_November             ((uint8_t)0x11)
#define RTC_Month_December             ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)            (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_RTC_DATE(DATE)              (((DATE)  >= 1) && ((DATE)  <= 31))
/**
  * @}
  */

/** @defgroup RTC_WeekDay_Definitions
  * @{
  */
#define RTC_Weekday_Monday             ((uint8_t)0x01)
#define RTC_Weekday_Tuesday            ((uint8_t)0x02)
#define RTC_Weekday_Wednesday          ((uint8_t)0x03)
#define RTC_Weekday_Thursday           ((uint8_t)0x04)
#define RTC_Weekday_Friday             ((uint8_t)0x05)
#define RTC_Weekday_Saturday           ((uint8_t)0x06)
#define RTC_Weekday_Sunday             ((uint8_t)0x07)
#define IS_RTC_WEEKDAY(WEEKDAY)       (((WEEKDAY) == RTC_Weekday_Monday)    || \
                                       ((WEEKDAY) == RTC_Weekday_Tuesday)   || \
                                       ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                       ((WEEKDAY) == RTC_Weekday_Thursday)  || \
                                       ((WEEKDAY) == RTC_Weekday_Friday)    || \
                                       ((WEEKDAY) == RTC_Weekday_Saturday)  || \
                                       ((WEEKDAY) == RTC_Weekday_Sunday)       )
/**
  * @}
  */

/** @defgroup RTC_Alarm_Definitions
  * @{
  */
#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE)       (((DATE) > 0) && ((DATE) <= 31))
#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday)    || \
                                                    ((WEEKDAY) == RTC_Weekday_Tuesday)   || \
                                                    ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Thursday)  || \
                                                    ((WEEKDAY) == RTC_Weekday_Friday)    || \
                                                    ((WEEKDAY) == RTC_Weekday_Saturday)  || \
                                                    ((WEEKDAY) == RTC_Weekday_Sunday)       )
/**
  * @}
  */


/** @defgroup RTC_AlarmDateWeekDay_Definitions
  * @{
  */
#define RTC_AlarmDateWeekDaySel_Date      ((uint32_t)0x00000000)
#define RTC_AlarmDateWeekDaySel_WeekDay   RTC_ALRMAR_WDSEL

#define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == RTC_AlarmDateWeekDaySel_Date)   || \
                                            ((SEL) == RTC_AlarmDateWeekDaySel_WeekDay)   )
/**
  * @}
  */


/** @defgroup RTC_AlarmMask_Definitions
  * @{
  */
#define RTC_AlarmMask_None                ((uint32_t)0x00000000)
#define RTC_AlarmMask_DateWeekDay         ((uint32_t)0x80000000)
#define RTC_AlarmMask_Hours               ((uint32_t)0x00800000)
#define RTC_AlarmMask_Minutes             ((uint32_t)0x00008000)
#define RTC_AlarmMask_Seconds             ((uint32_t)0x00000080)
#define RTC_AlarmMask_All                 ((uint32_t)0x80808080)
#define IS_RTC_ALARM_MASK(MASK)          (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)
/**
  * @}
  */

/** @defgroup RTC_Alarm_Definitions(RTC_ALARMA or RTC_ALARMB)
  * @{
  */
#define RTC_Alarm_A               ((uint32_t)0x00000100)
#define RTC_Alarm_B               ((uint32_t)0x00000200)
#define IS_RTC_ALARM(ALARM)       (((ALARM) == RTC_Alarm_A) || ((ALARM) == RTC_Alarm_B))
#define IS_RTC_CMD_ALARM(ALARM)   ((((ALARM) & (RTC_Alarm_A)) != (uint32_t)RESET) || \
                                   (((ALARM) & (RTC_Alarm_B)) != (uint32_t)RESET)    )
/**
  * @}
  */

/** @defgroup RTC_Alarm_Sub_Seconds_Masks Definitions.
  * @{
  */
#define RTC_AlarmSubSecondMask_All            ((uint8_t)0x00) /*!< All Alarm SS fields are masked.
                                                                There is no comparison on sub second for Alarm */
#define RTC_AlarmSubSecondMask_SS14_1         ((uint8_t)0x01) /*!< SS[14:1] are don't care in Alarm
                                                                comparison. Only SS[0] is compared. */
#define RTC_AlarmSubSecondMask_SS14_2         ((uint8_t)0x02) /*!< SS[14:2] are don't care in Alarm
                                                                comparison. Only SS[1:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_3         ((uint8_t)0x03) /*!< SS[14:3] are don't care in Alarm
                                                                comparison. Only SS[2:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_4         ((uint8_t)0x04) /*!< SS[14:4] are don't care in Alarm
                                                                comparison. Only SS[3:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_5         ((uint8_t)0x05) /*!< SS[14:5] are don't care in Alarm
                                                                comparison. Only SS[4:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_6         ((uint8_t)0x06) /*!< SS[14:6] are don't care in Alarm
                                                                comparison. Only SS[5:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_7         ((uint8_t)0x07) /*!< SS[14:7] are don't care in Alarm
                                                                comparison. Only SS[6:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_8         ((uint8_t)0x08) /*!< SS[14:8] are don't care in Alarm
                                                                comparison. Only SS[7:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_9         ((uint8_t)0x09) /*!< SS[14:9] are don't care in Alarm
                                                                comparison. Only SS[8:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_10        ((uint8_t)0x0A) /*!< SS[14:10] are don't care in Alarm
                                                                comparison. Only SS[9:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_11        ((uint8_t)0x0B) /*!< SS[14:11] are don't care in Alarm
                                                                comparison. Only SS[10:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_12        ((uint8_t)0x0C) /*!< SS[14:12] are don't care in Alarm
                                                                comparison.Only SS[11:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_13        ((uint8_t)0x0D) /*!< SS[14:13] are don't care in Alarm
                                                                comparison. Only SS[12:0] are compared */
#define RTC_AlarmSubSecondMask_SS14           ((uint8_t)0x0E) /*!< SS[14] is don't care in Alarm
                                                                comparison.Only SS[13:0] are compared */
#define RTC_AlarmSubSecondMask_None           ((uint8_t)0x0F) /*!< SS[14:0] are compared and must match
                                                                to activate alarm. */
#define IS_RTC_ALARM_SUB_SECOND_MASK(MASK)   (((MASK) == RTC_AlarmSubSecondMask_All)     || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_1)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_2)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_3)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_4)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_5)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_6)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_7)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_8)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_9)  || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_10) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_11) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_12) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_13) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14)    || \
                                              ((MASK) == RTC_AlarmSubSecondMask_None)       )
/**
  * @}
  */

/** @defgroup RTC_Alarm_Sub_Seconds_Value
  * @{
  */
#define IS_RTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)
/**
  * @}
  */

/**
  * @}
  */
/** @defgroup RTC_Time_Stamp_Edges_definitions
  * @{
  */
#define RTC_TimeStampEdge_Rising          ((uint32_t)0x00000000)
#define RTC_TimeStampEdge_Falling         ((uint32_t)0x00000008)
#define IS_RTC_TIMESTAMP_EDGE(EDGE)      (((EDGE) == RTC_TimeStampEdge_Rising) || \
                                          ((EDGE) == RTC_TimeStampEdge_Falling)   )
/**
  * @}
  */

/** @defgroup RTC_Output_selection_Definitions
  * @{
  */
#define RTC_Output_Disable             ((uint32_t)0x00000000)
#define RTC_Output_AlarmA              ((uint32_t)0x00200000)
#define RTC_Output_AlarmB              ((uint32_t)0x00400000)
#define RTC_Output_WakeUp              ((uint32_t)0x00600000)
#define IS_RTC_OUTPUT(OUTPUT)         (((OUTPUT) == RTC_Output_Disable) || \
                                       ((OUTPUT) == RTC_Output_AlarmA)  || \
                                       ((OUTPUT) == RTC_Output_AlarmB)  || \
                                       ((OUTPUT) == RTC_Output_WakeUp)     )
/**
  * @}
  */

/** @defgroup RTC_Output_Polarity_Definitions
  * @{
  */
#define RTC_OutputPolarity_High           ((uint32_t)0x00000000)
#define RTC_OutputPolarity_Low            ((uint32_t)0x00100000)
#define IS_RTC_OUTPUT_POL(POL)           (((POL) == RTC_OutputPolarity_High) || \
                                          ((POL) == RTC_OutputPolarity_Low))
/**
  * @}
  */


/** @defgroup RTC_Calib_Output_selection_Definitions
  * @{
  */
#define RTC_CalibOutput_512Hz            ((uint32_t)0x00000000)
#define RTC_CalibOutput_1Hz              ((uint32_t)0x00080000)
#define IS_RTC_CALIB_OUTPUT(OUTPUT)     (((OUTPUT) == RTC_CalibOutput_512Hz) || \
                                         ((OUTPUT) == RTC_CalibOutput_1Hz))
/**
  * @}
  */

/** @defgroup RTC_Rough_Calib_Symbol_selection_Definitions
  * @{
  */
#define RTC_RoughCalibSymbol_Positive          ((uint32_t)0x00000000)
#define RTC_RoughCalibSymbol_Negative          ((uint32_t)0x00000080)
#define IS_RTC_ROUGH_CALIB_SYMBOL(SYMBOL)     (((SYMBOL) == RTC_RoughCalibSymbol_Positive) || \
                                               ((SYMBOL) == RTC_RoughCalibSymbol_Negative))
/**
  * @}
  */

/** @defgroup RTC_Rough_Calib_Dc_Value
  * @{
  */
#define IS_RTC_ROUGH_CALIB_DC_VALUE(VALUE)     ((VALUE) <= 0x0000001F)
/**
  * @}
  */


/** @defgroup RTC_Smooth_calib_period_Definitions
  * @{
  */
#define RTC_SmoothCalibPeriod_32sec   ((uint32_t)0x00000000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 32s,  else 2exp20 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_16sec   ((uint32_t)0x00002000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 16s, else 2exp19 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_8sec    ((uint32_t)0x00004000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 8s, else 2exp18 RTCCLK seconds */
#define  IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SmoothCalibPeriod_32sec) || \
                                             ((PERIOD) == RTC_SmoothCalibPeriod_16sec) || \
                                             ((PERIOD) == RTC_SmoothCalibPeriod_8sec)     )
/**
  * @}
  */

/** @defgroup RTC_Smooth_calib_Plus_pulses_Definitions
  * @{
  */
#define RTC_SmoothCalibPlusPulses_Set    ((uint32_t)0x00008000) /*!<  The number of RTCCLK pulses added
                                                                during a X -second window = Y - CALM[8:0].
                                                                 with Y = 512, 256, 128 when X = 32, 16, 8 */
#define RTC_SmoothCalibPlusPulses_Reset  ((uint32_t)0x00000000) /*!<  The number of RTCCLK pulses subbstited
                                                                 during a 32-second window =   CALM[8:0]. */
#define  IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == RTC_SmoothCalibPlusPulses_Set)   || \
                                         ((PLUS) == RTC_SmoothCalibPlusPulses_Reset)    )
/**
  * @}
  */

/** @defgroup RTC_Smooth_calib_Minus_pulses_Definitions
  * @{
  */
#define  IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= 0x000001FF)
/**
  * @}
  */

/** @defgroup RTC_DayLightSaving_Definitions
  * @{
  */
#define RTC_DayLightSaving_SUB1H   ((uint32_t)0x00020000)
#define RTC_DayLightSaving_ADD1H   ((uint32_t)0x00010000)
#define IS_RTC_DAYLIGHT_SAVING(SAVING) (((SAVING) == RTC_DayLightSaving_SUB1H) || \
                                        ((SAVING) == RTC_DayLightSaving_ADD1H))

#define RTC_StoreOperation_Reset        ((uint32_t)0x00000000)
#define RTC_StoreOperation_Set          ((uint32_t)0x00040000)
#define IS_RTC_STORE_OPERATION(OPERATION) (((OPERATION) == RTC_StoreOperation_Reset) || \
                                           ((OPERATION) == RTC_StoreOperation_Set)      )
/**
  * @}
  */

/** @defgroup RTC_Tamper_Trigger1_Definitions
  * @{
  */
#define RTC_TamperTrigger_RisingEdge            ((uint32_t)0x00000000)
#define RTC_TamperTrigger_FallingEdge           ((uint32_t)0x00000002)
#define RTC_TamperTrigger_LowLevel              ((uint32_t)0x00000000)
#define RTC_TamperTrigger_HighLevel             ((uint32_t)0x00000002)
#define IS_RTC_TAMPER_TRIGGER(TRIGGER)   (((TRIGGER) == RTC_TamperTrigger_RisingEdge)  || \
                                          ((TRIGGER) == RTC_TamperTrigger_FallingEdge) || \
                                          ((TRIGGER) == RTC_TamperTrigger_LowLevel)    || \
                                          ((TRIGGER) == RTC_TamperTrigger_HighLevel)      )
/**
  * @}
  */


/** @defgroup RTC_Tamper_Filter_Definitions
  * @{
  */
#define RTC_TamperFilter_Disable   ((uint32_t)0x00000000) /*!< Tamper filter is disabled */

#define RTC_TamperFilter_2Sample   ((uint32_t)0x00000800) /*!< Tamper is activated after 2
                                                          consecutive samples at the active level */
#define RTC_TamperFilter_4Sample   ((uint32_t)0x00001000) /*!< Tamper is activated after 4
                                                          consecutive samples at the active level */
#define RTC_TamperFilter_8Sample   ((uint32_t)0x00001800) /*!< Tamper is activated after 8
                                                          consecutive samples at the active leve. */
#define IS_RTC_TAMPER_FILTER(FILTER) (((FILTER) == RTC_TamperFilter_Disable) || \
                                      ((FILTER) == RTC_TamperFilter_2Sample) || \
                                      ((FILTER) == RTC_TamperFilter_4Sample) || \
                                      ((FILTER) == RTC_TamperFilter_8Sample))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Sampling_Frequencies_Definitions
  * @{
  */
#define RTC_TamperSamplingFreq_RTCCLK_Div32768 ((uint32_t)0x00000000) /*!< Tamper inputs sampled frequency = RTCCLK/32768 */
#define RTC_TamperSamplingFreq_RTCCLK_Div16384 ((uint32_t)0x00000100) /*!< Tamper inputs sampled frequency = RTCCLK/16384 */
#define RTC_TamperSamplingFreq_RTCCLK_Div8192  ((uint32_t)0x00000200) /*!< Tamper inputs sampled frequency = RTCCLK/8192  */
#define RTC_TamperSamplingFreq_RTCCLK_Div4096  ((uint32_t)0x00000300) /*!< Tamper inputs sampled frequency = RTCCLK/4096  */
#define RTC_TamperSamplingFreq_RTCCLK_Div2048  ((uint32_t)0x00000400) /*!< Tamper inputs sampled frequency = RTCCLK/2048  */
#define RTC_TamperSamplingFreq_RTCCLK_Div1024  ((uint32_t)0x00000500) /*!< Tamper inputs sampled frequency = RTCCLK/1024  */
#define RTC_TamperSamplingFreq_RTCCLK_Div512   ((uint32_t)0x00000600) /*!< Tamper inputs sampled frequency = RTCCLK/512   */
#define RTC_TamperSamplingFreq_RTCCLK_Div256   ((uint32_t)0x00000700) /*!< Tamper inputs sampled frequency = RTCCLK/256   */
#define IS_RTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div32768) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div16384) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div8192)  || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div4096)  || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div2048)  || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div1024)  || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div512)   || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div256)      )
/**
  * @}
  */

/** @defgroup RTC_Tamper_Pin_Precharge_Duration_Definitions
* @{
*/
#define RTC_TamperPrechargeDuration_1RTCCLK ((uint32_t)0x00000000)  /*!< Tamper pins are precharged 1 RTCCLK */
#define RTC_TamperPrechargeDuration_2RTCCLK ((uint32_t)0x00002000)  /*!< Tamper pins are precharged 2 RTCCLK */
#define RTC_TamperPrechargeDuration_4RTCCLK ((uint32_t)0x00004000)  /*!< Tamper pins are precharged 4 RTCCLK */
#define RTC_TamperPrechargeDuration_8RTCCLK ((uint32_t)0x00006000)  /*!< Tamper pins are precharged 8 RTCCLK */

#define IS_RTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == RTC_TamperPrechargeDuration_1RTCCLK) || \
                                                    ((DURATION) == RTC_TamperPrechargeDuration_2RTCCLK) || \
                                                    ((DURATION) == RTC_TamperPrechargeDuration_4RTCCLK) || \
                                                    ((DURATION) == RTC_TamperPrechargeDuration_8RTCCLK)    )
/**
  * @}
  */

/** @defgroup RTC_Tamper_Pins_Definitions
  * @{
  */
#define RTC_Tamper_1            RTC_TAFCR_TAMP1E /*!< Tamper detection enable for input tamper 1 */
#define RTC_Tamper_2            RTC_TAFCR_TAMP2E /*!< Tamper detection enable for input tamper 2 */
#define IS_RTC_TAMPER(TAMPER) ((((TAMPER) & (uint32_t)0xFFFFFFF6) == 0x00) && ((TAMPER) != (uint32_t)RESET))
/**
  * @}
  */

/** @defgroup RTC_Output_Type_ALARM_OUT
  * @{
  */
#define RTC_OutputType_OpenDrain           ((uint32_t)0x00000000)
#define RTC_OutputType_PushPull            ((uint32_t)0x00040000)
#define IS_RTC_OUTPUT_TYPE(TYPE) (((TYPE) == RTC_OutputType_OpenDrain) || \
                                  ((TYPE) == RTC_OutputType_PushPull))
#define RTC_PC13_OutputType_GPIO           ((uint32_t)0x00000000)
#define RTC_PC13_OutputType_PushPull       ((uint32_t)0x00080000)
#define IS_RTC_PC13_OUTPUT_TYPE(TYPE)     (((TYPE) == RTC_PC13_OutputType_GPIO)     || \
                                           ((TYPE) == RTC_PC13_OutputType_PushPull))
/**
  * @}
  */

/** @defgroup RTC_Pc15_Output_Type_Data
  * @{
  */
#define RTC_PC15_OutputType_GPIO           ((uint32_t)0x00000000)
#define RTC_PC15_OutputType_PushPull       ((uint32_t)0x00800000)
#define IS_RTC_PC15_OUTPUT_TYPE(TYPE)     (((TYPE) == RTC_PC15_OutputType_GPIO)     || \
                                           ((TYPE) == RTC_PC15_OutputType_PushPull))
#define RTC_PC15_OutputData_0              ((uint32_t)0x00000000)
#define RTC_PC15_OutputData_1              ((uint32_t)0x00400000)
#define IS_RTC_PC15_OUTPUT_DATA(DATA)     (((DATA) == RTC_PC15_OutputData_0)        || \
                                           ((DATA) == RTC_PC15_OutputData_1))
/**
  * @}
  */

/** @defgroup RTC_Pc14_Output_Type_Data
  * @{
  */
#define RTC_PC14_OutputType_GPIO           ((uint32_t)0x00000000)
#define RTC_PC14_OutputType_PushPull       ((uint32_t)0x00200000)
#define IS_RTC_PC14_OUTPUT_TYPE(TYPE)     (((TYPE) == RTC_PC14_OutputType_GPIO)     || \
                                           ((TYPE) == RTC_PC14_OutputType_PushPull))
#define RTC_PC14_OutputData_0              ((uint32_t)0x00000000)
#define RTC_PC14_OutputData_1              ((uint32_t)0x00100000)
#define IS_RTC_PC14_OUTPUT_DATA(DATA)     (((DATA) == RTC_PC14_OutputData_0)        || \
                                           ((DATA) == RTC_PC14_OutputData_1))
/**
  * @}
  */

/** @defgroup RTC_Add_1_Second_Parameter_Definitions
  * @{
  */
#define RTC_ShiftAdd1S_Reset      ((uint32_t)0x00000000)
#define RTC_ShiftAdd1S_Set        ((uint32_t)0x80000000)
#define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == RTC_ShiftAdd1S_Reset) || \
                                 ((SEL) == RTC_ShiftAdd1S_Set))
/**
  * @}
  */

/** @defgroup RTC_Substract_Fraction_Of_Second_Value
  * @{
  */
#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RTC_Input_parameter_format_definitions
  * @{
  */
#define RTC_Format_BIN                    ((uint32_t)0x000000000)
#define RTC_Format_BCD                    ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_Format_BIN) || ((FORMAT) == RTC_Format_BCD))

/**
  * @}
  */

/** @defgroup RTC_Flags_Definitions
  * @{
  */
#define RTC_FLAG_RECALPF                  RTC_ISR_RECALPF
#define RTC_FLAG_TAMP2F                   RTC_ISR_TAMP2F
#define RTC_FLAG_TAMP1F                   RTC_ISR_TAMP1F
#define RTC_FLAG_TSOVF                    RTC_ISR_TSOVF
#define RTC_FLAG_TSF                      RTC_ISR_TSF
#define RTC_FLAG_WUTF                     RTC_ISR_WUTF
#define RTC_FLAG_ALRBF                    RTC_ISR_ALRBF
#define RTC_FLAG_ALRAF                    RTC_ISR_ALRAF
#define RTC_FLAG_INITF                    RTC_ISR_INITF
#define RTC_FLAG_RSF                      RTC_ISR_RSF
#define RTC_FLAG_INITS                    RTC_ISR_INITS
#define RTC_FLAG_SHPF                     RTC_ISR_SHPF
#define RTC_FLAG_WUTWF                    RTC_ISR_WUTWF
#define RTC_FLAG_ALRBWF                   RTC_ISR_ALRBWF
#define RTC_FLAG_ALRAWF                   RTC_ISR_ALRAWF

#define IS_RTC_GET_FLAG(FLAG)    (((FLAG) == RTC_FLAG_RECALPF) || ((FLAG) == RTC_FLAG_TAMP2F) || \
                                  ((FLAG) == RTC_FLAG_TAMP1F)  || ((FLAG) == RTC_FLAG_TSOVF)  || \
                                  ((FLAG) == RTC_FLAG_TSF)     || ((FLAG) == RTC_FLAG_WUTF)   || \
                                  ((FLAG) == RTC_FLAG_ALRBF)   || ((FLAG) == RTC_FLAG_ALRAF)  || \
                                  ((FLAG) == RTC_FLAG_INITF)   || ((FLAG) == RTC_FLAG_RSF)    || \
                                  ((FLAG) == RTC_FLAG_INITS)   || ((FLAG) == RTC_FLAG_SHPF)   || \
                                  ((FLAG) == RTC_FLAG_WUTWF)   || ((FLAG) == RTC_FLAG_ALRBWF) || \
                                  ((FLAG) == RTC_FLAG_ALRAWF))
#define IS_RTC_CLEAR_FLAG(FLAG)  (((FLAG) == RTC_FLAG_TAMP2F)  || ((FLAG) == RTC_FLAG_TAMP1F) || \
                                  ((FLAG) == RTC_FLAG_TSOVF)   || ((FLAG) == RTC_FLAG_TSF)    || \
                                  ((FLAG) == RTC_FLAG_WUTF)    || ((FLAG) == RTC_FLAG_ALRBF)  || \
                                  ((FLAG) == RTC_FLAG_ALRAF)   || ((FLAG) == RTC_FLAG_RSF)     )
/**
  * @}
  */

/** @defgroup RTC_Interrupts_Definitions
  * @{
  */
#define RTC_IT_TS_EN                         ((uint32_t)0x00008000)
#define RTC_IT_WUT_EN                        ((uint32_t)0x00004000)
#define RTC_IT_ALRB_EN                       ((uint32_t)0x00002000)
#define RTC_IT_ALRA_EN                       ((uint32_t)0x00001000)
#define RTC_IT_TAMP_EN                       ((uint32_t)0x00000004) /* Used only to Enable the Tamper Interrupt */


#define IS_RTC_CONFIG_IT(IT) (((IT) == RTC_IT_TS_EN)    || ((IT) == RTC_IT_WUT_EN)   || \
                              ((IT) == RTC_IT_ALRB_EN)  || ((IT) == RTC_IT_ALRA_EN)  || \
                              ((IT) == RTC_IT_TAMP_EN))
#define IS_RTC_GET_IT(IT)    (((IT) == RTC_IT_TS_EN)    || ((IT) == RTC_IT_WUT_EN)   || \
                              ((IT) == RTC_IT_ALRB_EN)  || ((IT) == RTC_IT_ALRA_EN)  || \
                              ((IT) == RTC_IT_TAMP_EN))

#define RTC_IT_TAMP2_FLAG                    ((uint32_t)0x00008000)
#define RTC_IT_TAMP1_FLAG                    ((uint32_t)0x00004000)
#define RTC_IT_TS_FLAG                       ((uint32_t)0x00000800)
#define RTC_IT_WUT_FLAG                      ((uint32_t)0x00000400)
#define RTC_IT_ALRB_FLAG                     ((uint32_t)0x00000200)
#define RTC_IT_ALRA_FLAG                     ((uint32_t)0x00000100)

#define IS_RTC_CLEAR_IT(IT) (((IT) == RTC_IT_TAMP2_FLAG) || ((IT) == RTC_IT_TAMP1_FLAG) || \
                             ((IT) == RTC_IT_TS_FLAG)    || ((IT) == RTC_IT_WUT_FLAG)   || \
                             ((IT) == RTC_IT_ALRB_FLAG)  || ((IT) == RTC_IT_ALRB_FLAG))
/**
  * @}
  */

/** @defgroup RTC_WeakUp_Clk_Choose
  * @{
  */
#define RTC_WeakUp_RTCCLK_Div16           ((uint32_t)0x00000000)/*auto weakup cnt clk use rtcclk/16*/
#define RTC_WeakUp_RTCCLK_Div8            ((uint32_t)0x00000001)/*auto weakup cnt clk use rtcclk/8*/
#define RTC_WeakUp_RTCCLK_Div4            ((uint32_t)0x00000002)/*auto weakup cnt clk use rtcclk/4*/
#define RTC_WeakUp_RTCCLK_Div2            ((uint32_t)0x00000003)/*auto weakup cnt clk use rtcclk/2*/
#define RTC_WeakUp_RTCCLK_CkSpre4         ((uint32_t)0x00000004)/*auto weakup cnt clk use ck_spre */
#define RTC_WeakUp_RTCCLK_CkSpre5         ((uint32_t)0x00000005)/*auto weakup cnt clk use ck_spre */
#define RTC_WeakUp_RTCCLK_CkSpre6         ((uint32_t)0x00000006)/*auto weakup cnt clk use ck_spre */
#define RTC_WeakUp_RTCCLK_CkSpre7         ((uint32_t)0x00000007)/*auto weakup cnt clk use ck_spre */


#define IS_RTC_WEAKUP_COUNT_FREQ(FREQ) (((FREQ) == RTC_WeakUp_RTCCLK_Div16)   || ((FREQ) == RTC_WeakUp_RTCCLK_Div8)    || \
                                        ((FREQ) == RTC_WeakUp_RTCCLK_Div4)    || ((FREQ) == RTC_WeakUp_RTCCLK_Div2)    || \
                                        ((FREQ) == RTC_WeakUp_RTCCLK_CkSpre4) || ((FREQ) == RTC_WeakUp_RTCCLK_CkSpre5) || \
                                        ((FREQ) == RTC_WeakUp_RTCCLK_CkSpre6) || ((FREQ) == RTC_WeakUp_RTCCLK_CkSpre7))

/** @defgroup RTC_Auto_Weakup_Count_Value
  * @{
  */
#define IS_RTC_WKUP_COUNTER(COUNTER) ((COUNTER) <= 0x0000FFFF)
/**
  * @}
  */

#define RTC_BackUp0Reg                   ((uint32_t)0x00000000)/*choose rtc_bkp0  register*/
#define RTC_BackUp1Reg                   ((uint32_t)0x00000001)/*choose rtc_bkp1  register*/
#define RTC_BackUp2Reg                   ((uint32_t)0x00000002)/*choose rtc_bkp2  register*/
#define RTC_BackUp3Reg                   ((uint32_t)0x00000003)/*choose rtc_bkp3  register*/
#define RTC_BackUp4Reg                   ((uint32_t)0x00000004)/*choose rtc_bkp4  register*/
#define RTC_BackUp5Reg                   ((uint32_t)0x00000005)/*choose rtc_bkp5  register*/
#define RTC_BackUp6Reg                   ((uint32_t)0x00000006)/*choose rtc_bkp6  register*/
#define RTC_BackUp7Reg                   ((uint32_t)0x00000007)/*choose rtc_bkp7  register*/
#define RTC_BackUp8Reg                   ((uint32_t)0x00000008)/*choose rtc_bkp8  register*/
#define RTC_BackUp9Reg                   ((uint32_t)0x00000009)/*choose rtc_bkp9  register*/
#define RTC_BackUp10Reg                  ((uint32_t)0x0000000A)/*choose rtc_bkp10 register*/
#define RTC_BackUp11Reg                  ((uint32_t)0x0000000B)/*choose rtc_bkp11 register*/
#define RTC_BackUp12Reg                  ((uint32_t)0x0000000C)/*choose rtc_bkp12 register*/
#define RTC_BackUp13Reg                  ((uint32_t)0x0000000D)/*choose rtc_bkp13 register*/
#define RTC_BackUp14Reg                  ((uint32_t)0x0000000E)/*choose rtc_bkp14 register*/
#define RTC_BackUp15Reg                  ((uint32_t)0x0000000F)/*choose rtc_bkp15 register*/
#define RTC_BackUp16Reg                  ((uint32_t)0x00000010)/*choose rtc_bkp16 register*/
#define RTC_BackUp17Reg                  ((uint32_t)0x00000011)/*choose rtc_bkp17 register*/
#define RTC_BackUp18Reg                  ((uint32_t)0x00000012)/*choose rtc_bkp18 register*/
#define RTC_BackUp19Reg                  ((uint32_t)0x00000013)/*choose rtc_bkp19 register*/

#define IS_RTC_BACKUP_REG(REG) (((REG) == RTC_BackUp0Reg)  || ((REG) == RTC_BackUp1Reg)  || \
                                ((REG) == RTC_BackUp2Reg)  || ((REG) == RTC_BackUp3Reg)  || \
                                ((REG) == RTC_BackUp4Reg)  || ((REG) == RTC_BackUp5Reg)  || \
                                ((REG) == RTC_BackUp6Reg)  || ((REG) == RTC_BackUp7Reg)  || \
                                ((REG) == RTC_BackUp8Reg)  || ((REG) == RTC_BackUp9Reg)  || \
                                ((REG) == RTC_BackUp10Reg) || ((REG) == RTC_BackUp11Reg) || \
                                ((REG) == RTC_BackUp12Reg) || ((REG) == RTC_BackUp13Reg) || \
                                ((REG) == RTC_BackUp14Reg) || ((REG) == RTC_BackUp15Reg) || \
                                ((REG) == RTC_BackUp16Reg) || ((REG) == RTC_BackUp17Reg) || \
                                ((REG) == RTC_BackUp18Reg) || ((REG) == RTC_BackUp19Reg))

/** @defgroup RTC_Backup_Data_Value
  * @{
  */
#define IS_RTC_BACKUP_DATA(DATA) ((DATA) <= 0xFFFFFFFF)
/**
  * @}
  */



/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*  Function used to set the RTC configuration to the default reset state *****/
ErrorStatus RTC_DeInit(void);/* reset the rtc register */

/* Initialization and Configuration functions *********************************/
void RTC_SetInit(RTC_InitTypeDef* RTC_InitStruct);/* config rtc's hour format,async and sync value struct */
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct);/* config rtc's hour format,async sync's specific value */
void RTC_WriteProtectionCmd(FunctionalState NewState);/* Function used open rtc write protect */
ErrorStatus RTC_EnterInitMode(void);/* Funtion used check enter initial mode if has error */
void RTC_ExitInitMode(void);/* Function used exit initial mode */
ErrorStatus RTC_WaitForSynchro(void);/* Function used wait calendar register be synchronized */
void RTC_RefClockCmd(FunctionalState NewState);/* Function used enable reference clock detection */
void RTC_BypassShadowCmd(FunctionalState NewState);/* Function used enable bypass */

/* Time and Date configuration functions **************************************/
void RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);/* Function used set rtc time register */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct);/* Function used set rtc time struct */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);/* get the rtc time from the rtc_tr register */
uint32_t RTC_GetSubSecond(void);/* Function used get the rtc sub-seconds */
void RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);/* Function used set rtc date register*/
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct);/* Function used set rtc date struct */
uint32_t RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);/* get the rtc date from the rtc_dr register */

/* Alarms (Alarm A and Alarm B) configuration functions  **********************************/
/* Function used config alarma/amarmb */
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct);/*Function used set rtc alarm struct */
/* Function used get alarma/amarmb */
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);/* Function used alarm enable or disable */
/* Function used config alarma/alarmb's subsecond */
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint8_t RTC_AlarmSubSecondMask);
/* Function used get alarma/alarmb's subsecond */
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm);

/* Daylight Saving configuration functions ************************************/
/* Function used config DayLightSaving ADD1H/SUB1H and Storeoperation set/clear BKP*/
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation);
uint32_t RTC_GetStoreOperation(void);/* Function used get StoreOperation RTC_CR[BKP]==0/1  */

/* Output pin Configuration function ******************************************/
/* Function used config RTC_ALARM output select alraf/alrbf/wutf and polarity high/low*/
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity);

/* Smooth Calibration configuration functions ********************************/
void RTC_CalibOutputCmd(FunctionalState NewState);/* Function used config RTC_CALIB output enable */
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput);/* Function used config RTC_CALIB output 512Hz/1Hz */
/* Function used config SmoothCalib CALP/CALW8/CALW16/CALM[8:0] */
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue);

/* Rough Digtial Calibration configuration functions ********************************/
/* Function used config DigtialRoughCalib DCS/DC[4:0] */
void RTC_RoughCalibration(FunctionalState NewState);/* Function used rough calibration enable or disable */
void RTC_RoughDigtialCalibConfig(uint32_t RTC_RoughCalibPolarity,
                                 uint32_t RTC_RoughCalibMinusPulsesValue);

/* TimeStamp configuration functions ******************************************/
/* Function used Enable RTC_TimeStamp and config occur edge */
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState);
/* Function used get RTC_TimeStamp TS and TD Register's value */
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct, RTC_DateTypeDef* RTC_StampDateStruct);
/* Function used get RTC_TimeStamp SubSecond Register's value */
uint32_t RTC_GetTimeStampSubSecond(void);

/* Tampers configuration functions ********************************************/
/* Function used config tamp1trg and tamp2trg is edge or level */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger);
/* Function used enable tamp1 and tamp2 */
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState);
/* Function used config tamp1 and tamp2's filter  */
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter);
/* Function used config tamp1 and tamp2's sampling frequence */
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq);
/* Function used config tamp1 and tamp2's precharge time */
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration);
/* Function used config tamp1 and tamp2 event as timestamp */
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState);
/* Function used config tamp1 and tamp2 pull_up forbidden */
void RTC_TamperPullUpCmd(FunctionalState NewState);

/* Output Type Config configuration functions *********************************/
/* Function used config RTC_ALARM(PC13) output type*/
void RTC_OutputTypeConfig(uint32_t RTC_OutputType);
/* Function used config RTC_ALARM(PC13) mode*/
void RTC_OutputModeConfig(uint32_t RTC_OutputMode);
/* Function used config pc15 output type and data */
void RTC_Pc15_OutputTypeDataConfig(uint32_t RTC_Pc15_OutputType, uint32_t RTC_Pc15_OutputData);
/* Function used config pc14 output type and data */
void RTC_Pc14_OutputTypeDataConfig(uint32_t RTC_Pc14_OutputType, uint32_t RTC_Pc14_OutputData);

/* RTC_Shift_control_synchonisation_functions *********************************/
/* Function used config shif control register add1s or substract a number of second */
/* Return config status error or success */
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS);

/* Interrupts and flags management functions **********************************/
/* Function used Enable rtc_ts/wut/alra/alrb/tamp interrupt */
void RTC_ITConfig(uint32_t RTC_IT_ENABLE, FunctionalState NewState);
/* Function used get rtc_tsf/wutf/alraf/alrbf/tamp1f/tamp2f */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG);
/* Function used clear rtc_flag */
void RTC_ClearFlag(uint32_t RTC_FLAG);
/* Function used get interrupt status */
ITStatus RTC_GetITStatus(uint32_t RTC_IT_ENABLE);
/* Function used clear interrupt flag */
void RTC_ClearITPendingBit(uint32_t RTC_IT_FLAG);

/* Auto Weakup Config configuration functions **********************************/
/* Function used Enable Auto WeakUp */
void RTC_WeakUpCmd(FunctionalState NewState);
/* Function used set RTC Auto WeakUp Counter Register's value */
void RTC_SetWeakUpCounter(uint32_t RTC_WeakUp_Counter);
/* Function used get RTC Auto WeakUp Counter Register's value */
uint32_t RTC_GetWeakUpCounter(void);
/* Function used config Auto WeakUp Count frequence */
void RTC_WeakUpCountFreqConfig(uint32_t RTC_WeakUpCountFreq);

/* Backup Data Config configuration functions **********************************/
/* Function used config backup register */
void RTC_BackUpRegConfig(uint32_t RTC_BackUpReg, uint32_t RTC_BackUpRegData);
/* Function used get RTC_BackUp Register's value */
uint32_t RTC_GetBackUpReg(uint32_t RTC_BackUpReg);



#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_RTC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
