/**
 **************************************************************************
 * File Name    : at32f4xx_ertc.h
 * Description  : at32f4xx ERTC header file
 * Date         : 2018-03-15
 * Version      : V1.0.4
 **************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_ERTC_H
#define __AT32F4xx_ERTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup ERTC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ERTC Init structures definition  
  */ 
typedef struct
{
  uint32_t ERTC_HourFormat;   /*!< Specifies the ERTC Hour Format.
                             This parameter can be a value of @ref RTC_Hour_Formats */
  
  uint32_t ERTC_AsynchPrediv; /*!< Specifies the ERTC Asynchronous Predivider value.
                             This parameter must be set to a value lower than 0x7F */
  
  uint32_t ERTC_SynchPrediv;  /*!< Specifies the ERTC Synchronous Predivider value.
                             This parameter must be set to a value lower than 0x7FFF */
}ERTC_InitType;

/** 
  * @brief  ERTC Time structure definition  
  */
typedef struct
{
  uint8_t ERTC_Hours;    /*!< Specifies the ERTC Time Hour.
                        This parameter must be set to a value in the 0-12 range
                        if the ERTC_HourFormat_12 is selected or 0-23 range if
                        the ERTC_HourFormat_24 is selected. */

  uint8_t ERTC_Minutes;  /*!< Specifies the ERTC Time Minutes.
                        This parameter must be set to a value in the 0-59 range. */
  
  uint8_t ERTC_Seconds;  /*!< Specifies the ERTC Time Seconds.
                        This parameter must be set to a value in the 0-59 range. */

  uint8_t ERTC_AMPM;      /*!< Specifies the ERTC AM/PM Time.
                        This parameter can be a value of @ref RTC_AM_PM_Definitions */
}ERTC_TimeType; 

/** 
  * @brief  ERTC Date structure definition  
  */
typedef struct
{
  uint8_t ERTC_WeekDay; /*!< Specifies the ERTC Date WeekDay.
                        This parameter can be a value of @ref RTC_WeekDay_Definitions */
  
  uint8_t ERTC_Month;   /*!< Specifies the ERTC Date Month (in BCD format).
                        This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t ERTC_Date;     /*!< Specifies the ERTC Date.
                        This parameter must be set to a value in the 1-31 range. */
  
  uint8_t ERTC_Year;     /*!< Specifies the ERTC Date Year.
                        This parameter must be set to a value in the 0-99 range. */
}ERTC_DateType;

/** 
  * @brief  ERTC Alarm structure definition  
  */
typedef struct
{
  ERTC_TimeType ERTC_AlarmTime;     /*!< Specifies the ERTC Alarm Time members. */

  uint32_t ERTC_AlarmMask;            /*!< Specifies the ERTC Alarm Masks.
                                     This parameter can be a value of @ref RTC_AlarmMask_Definitions */

  uint32_t ERTC_AlarmDateWeekSel;  /*!< Specifies the ERTC Alarm is on Date or WeekDay.
                                     This parameter can be a value of @ref RTC_AlarmDateWeekDay_Definitions */
  
  uint8_t ERTC_AlarmDateWeek;      /*!< Specifies the ERTC Alarm Date/WeekDay.
                                     If the Alarm Date is selected, this parameter
                                     must be set to a value in the 1-31 range.
                                     If the Alarm WeekDay is selected, this 
                                     parameter can be a value of @ref RTC_WeekDay_Definitions */
}ERTC_AlarmType;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */ 


/** @defgroup RTC_Hour_Formats 
  * @{
  */ 
#define ERTC_HourFormat_24              ((uint32_t)0x00000000)
#define ERTC_HourFormat_12              ((uint32_t)0x00000040)
#define IS_ERTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == ERTC_HourFormat_12) || \
                                         ((FORMAT) == ERTC_HourFormat_24))
/**
  * @}
  */ 

/** @defgroup RTC_Asynchronous_Predivider 
  * @{
  */ 
#define IS_ERTC_ASYNCH_PRDIV(PRDIV)   ((PRDIV) <= 0x7F)
 
/**
  * @}
  */ 


/** @defgroup RTC_Synchronous_Predivider 
  * @{
  */ 
#define IS_ERTC_SYNCH_PRDIV(PRDIV)    ((PRDIV) <= 0x7FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Time_Definitions 
  * @{
  */ 
#define IS_ERTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_ERTC_HOUR24(HOUR)            ((HOUR) <= 23)
#define IS_ERTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
#define IS_ERTC_SECONDS(SECONDS)        ((SECONDS) <= 59)

/**
  * @}
  */ 

/** @defgroup RTC_AM_PM_Definitions 
  * @{
  */ 
#define ERTC_H12_AM                     ((uint8_t)0x00)
#define ERTC_H12_PM                     ((uint8_t)0x40)
#define IS_ERTC_H12(AMPM) (((AMPM) == ERTC_H12_AM) || ((AMPM) == ERTC_H12_PM))

/**
  * @}
  */ 

/** @defgroup RTC_Year_Date_Definitions 
  * @{
  */ 
#define IS_ERTC_YEAR(YEAR)              ((YEAR) <= 99)

/**
  * @}
  */ 

/** @defgroup RTC_Month_Date_Definitions 
  * @{
  */ 

/* Coded in BCD format */
#define ERTC_Month_JAN                  ((uint8_t)0x01)
#define ERTC_Month_FEB                  ((uint8_t)0x02)
#define ERTC_Month_MAR                  ((uint8_t)0x03)
#define ERTC_Month_APR                  ((uint8_t)0x04)
#define ERTC_Month_MAY                  ((uint8_t)0x05)
#define ERTC_Month_JUN                  ((uint8_t)0x06)
#define ERTC_Month_JUL                  ((uint8_t)0x07)
#define ERTC_Month_AUG                  ((uint8_t)0x08)
#define ERTC_Month_SEP                  ((uint8_t)0x09)
#define ERTC_Month_OCT                  ((uint8_t)0x10)
#define ERTC_Month_NOV                  ((uint8_t)0x11)
#define ERTC_Month_DEC                  ((uint8_t)0x12)
#define IS_ERTC_MONTH(MONTH)            (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_ERTC_DATE(DATE)              (((DATE) >= 1) && ((DATE) <= 31))

/**
  * @}
  */ 

/** @defgroup RTC_WeekDay_Definitions 
  * @{
  */ 
  
#define ERTC_Week_MON                   ((uint8_t)0x01)
#define ERTC_Week_TUES                  ((uint8_t)0x02)
#define ERTC_Week_WED                   ((uint8_t)0x03)
#define ERTC_Week_THUR                  ((uint8_t)0x04)
#define ERTC_Week_FRI                   ((uint8_t)0x05)
#define ERTC_Week_SAT                   ((uint8_t)0x06)
#define ERTC_Week_SUN                   ((uint8_t)0x07)
#define IS_ERTC_WEEK(WEEK)      (((WEEK) == ERTC_Week_MON) || \
                                 ((WEEK) == ERTC_Week_TUES) || \
                                 ((WEEK) == ERTC_Week_WED) || \
                                 ((WEEK) == ERTC_Week_THUR) || \
                                 ((WEEK) == ERTC_Week_FRI) || \
                                 ((WEEK) == ERTC_Week_SAT) || \
                                 ((WEEK) == ERTC_Week_SUN))
/**
  * @}
  */ 


/** @defgroup RTC_Alarm_Definitions
  * @{
  */ 
#define IS_ERTC_ALARM_DATE_WEEK_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
#define IS_ERTC_ALARM_DATE_WEEK_WEEK(WEEK) (((WEEK) == ERTC_Week_MON) || \
                                                    ((WEEK) == ERTC_Week_TUES) || \
                                                    ((WEEK) == ERTC_Week_WED) || \
                                                    ((WEEK) == ERTC_Week_THUR) || \
                                                    ((WEEK) == ERTC_Week_FRI) || \
                                                    ((WEEK) == ERTC_Week_SAT) || \
                                                    ((WEEK) == ERTC_Week_SUN))

/**
  * @}
  */ 


/** @defgroup RTC_AlarmDateWeekDay_Definitions 
  * @{
  */ 
#define ERTC_AlarmDateWeekSel_Date       ((uint32_t)0x00000000)
#define ERTC_AlarmDateWeekSel_Week       ((uint32_t)0x40000000)

#define IS_ERTC_ALARM_DATE_WEEK_SEL(SEL) (((SEL) == ERTC_AlarmDateWeekSel_Date) || \
                                            ((SEL) == ERTC_AlarmDateWeekSel_Week))

/**
  * @}
  */ 


/** @defgroup RTC_AlarmMask_Definitions 
  * @{
  */ 
#define ERTC_AlarmMask_None                ((uint32_t)0x00000000)
#define ERTC_AlarmMask_DateWeek            ((uint32_t)0x80000000)
#define ERTC_AlarmMask_Hours               ((uint32_t)0x00800000)
#define ERTC_AlarmMask_Minutes             ((uint32_t)0x00008000)
#define ERTC_AlarmMask_Seconds             ((uint32_t)0x00000080)
#define ERTC_AlarmMask_All                 ((uint32_t)0x80808080)
#define IS_ALARM_MASK(MASK)  (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)

/**
  * @}
  */ 

/** @defgroup RTC_Alarms_Definitions 
  * @{
  */ 
#define ERTC_AlA                       ((uint32_t)0x00000100)
#define ERTC_AlB                       ((uint32_t)0x00000200)
#define IS_ERTC_ALARM(ALARM)     (((ALARM) == ERTC_AlA) || ((ALARM) == ERTC_AlB))
#define IS_ERTC_CMD_ALARM(ALARM) (((ALARM) & (ERTC_AlA | ERTC_AlB)) != (uint32_t)RESET)

/**
  * @}
  */ 

  /** @defgroup RTC_Alarm_Sub_Seconds_Masks_Definitions
  * @{
  */ 
#define ERTC_AlarmSubSecondMask_All          ((uint32_t)0x00000000) /*!< All Alarm SS fields are masked. 
                                                                       There is no comparison on sub seconds 
                                                                       for Alarm */
#define ERTC_AlarmSubSecondMask_SBS14_1      ((uint32_t)0x01000000) /*!< SS[14:1] are don't care in Alarm 
                                                                       comparison. Only SS[0] is compared. */
#define ERTC_AlarmSubSecondMask_SBS14_2      ((uint32_t)0x02000000) /*!< SS[14:2] are don't care in Alarm 
                                                                       comparison. Only SS[1:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_3      ((uint32_t)0x03000000) /*!< SS[14:3] are don't care in Alarm 
                                                                       comparison. Only SS[2:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_4      ((uint32_t)0x04000000) /*!< SS[14:4] are don't care in Alarm 
                                                                       comparison. Only SS[3:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_5      ((uint32_t)0x05000000) /*!< SS[14:5] are don't care in Alarm 
                                                                       comparison. Only SS[4:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_6      ((uint32_t)0x06000000) /*!< SS[14:6] are don't care in Alarm 
                                                                       comparison. Only SS[5:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_7      ((uint32_t)0x07000000) /*!< SS[14:7] are don't care in Alarm 
                                                                       comparison. Only SS[6:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_8      ((uint32_t)0x08000000) /*!< SS[14:8] are don't care in Alarm 
                                                                       comparison. Only SS[7:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_9      ((uint32_t)0x09000000) /*!< SS[14:9] are don't care in Alarm 
                                                                       comparison. Only SS[8:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_10     ((uint32_t)0x0A000000) /*!< SS[14:10] are don't care in Alarm 
                                                                       comparison. Only SS[9:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_11     ((uint32_t)0x0B000000) /*!< SS[14:11] are don't care in Alarm 
                                                                       comparison. Only SS[10:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_12     ((uint32_t)0x0C000000) /*!< SS[14:12] are don't care in Alarm 
                                                                       comparison.Only SS[11:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14_13     ((uint32_t)0x0D000000) /*!< SS[14:13] are don't care in Alarm 
                                                                       comparison. Only SS[12:0] are compared */
#define ERTC_AlarmSubSecondMask_SBS14        ((uint32_t)0x0E000000) /*!< SS[14] is don't care in Alarm 
                                                                       comparison.Only SS[13:0] are compared */
#define ERTC_AlarmSubSecondMask_None         ((uint32_t)0x0F000000) /*!< SS[14:0] are compared and must match 
                                                                       to activate alarm. */
#define IS_ERTC_ALARM_SUB_SECOND_MASK(MASK)  (((MASK) == ERTC_AlarmSubSecondMask_All) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_1) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_2) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_3) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_4) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_5) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_6) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_7) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_8) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_9) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_10) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_11) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_12) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14_13) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_SBS14) || \
                                              ((MASK) == ERTC_AlarmSubSecondMask_None))
/**
  * @}
  */ 

/** @defgroup RTC_Alarm_Sub_Seconds_Value
  * @{
  */ 

#define IS_ERTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Wakeup_Timer_Definitions 
  * @{
  */ 
#define ERTC_WakeUpClockSelect_RTCCLK_Div16        ((uint32_t)0x00000000)
#define ERTC_WakeUpClockSelect_RTCCLK_Div8         ((uint32_t)0x00000001)
#define ERTC_WakeUpClockSelect_RTCCLK_Div4         ((uint32_t)0x00000002)
#define ERTC_WakeUpClockSelect_RTCCLK_Div2         ((uint32_t)0x00000003)
#define ERTC_WakeUpClockSelect_CK_SPRE_16bits      ((uint32_t)0x00000004)
#define ERTC_WakeUpClockSelect_CK_SPRE_17bits      ((uint32_t)0x00000006)
#define IS_ERTC_WAKEUP_CLOCK_SELECT(CLOCK) (((CLOCK) == ERTC_WakeUpClockSelect_RTCCLK_Div16) || \
                                    ((CLOCK) == ERTC_WakeUpClockSelect_RTCCLK_Div8) || \
                                    ((CLOCK) == ERTC_WakeUpClockSelect_RTCCLK_Div4) || \
                                    ((CLOCK) == ERTC_WakeUpClockSelect_RTCCLK_Div2) || \
                                    ((CLOCK) == ERTC_WakeUpClockSelect_CK_SPRE_16bits) || \
                                    ((CLOCK) == ERTC_WakeUpClockSelect_CK_SPRE_17bits))
#define IS_ERTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= 0xFFFF)
/**
  * @}
  */ 

/** @defgroup RTC_Time_Stamp_Edges_definitions 
  * @{
  */ 
#define ERTC_TimeStampEdge_Rising          ((uint32_t)0x00000000)
#define ERTC_TimeStampEdge_Falling         ((uint32_t)0x00000008)
#define IS_ERTC_TIMESTAMP_EDGE(EDGE) (((EDGE) == ERTC_TimeStampEdge_Rising) || \
                                     ((EDGE) == ERTC_TimeStampEdge_Falling))
/**
  * @}
  */ 

/** @defgroup RTC_Output_selection_Definitions 
  * @{
  */ 
#define ERTC_Output_Disable             ((uint32_t)0x00000000)
#define ERTC_Output_AlarmA              ((uint32_t)0x00200000)
#define ERTC_Output_AlarmB              ((uint32_t)0x00400000)
#define ERTC_Output_WakeUp              ((uint32_t)0x00600000)
 
#define IS_ERTC_OUTPUT(OUTPUT) (((OUTPUT) == ERTC_Output_Disable) || \
                               ((OUTPUT) == ERTC_Output_AlarmA) || \
                               ((OUTPUT) == ERTC_Output_AlarmB) || \
                               ((OUTPUT) == ERTC_Output_WakeUp))

/**
  * @}
  */ 

/** @defgroup RTC_Output_Polarity_Definitions 
  * @{
  */ 
#define ERTC_OutputPolarity_High           ((uint32_t)0x00000000)
#define ERTC_OutputPolarity_Low            ((uint32_t)0x00100000)
#define IS_ERTC_OUTPUT_OPOL(OPOL) (((OPOL) == ERTC_OutputPolarity_High) || \
                                ((OPOL) == ERTC_OutputPolarity_Low))
/**
  * @}
  */ 


/** @defgroup RTC_Digital_Calibration_Definitions 
  * @{
  */ 
#define ERTC_DataCalSign_Positive            ((uint32_t)0x00000000) 
#define ERTC_DataCalSign_Negative            ((uint32_t)0x00000080)
#define IS_ERTC_DATACAL_SIGN(SIGN) (((SIGN) == ERTC_DataCalSign_Positive) || \
                                 ((SIGN) == ERTC_DataCalSign_Negative))
#define IS_ERTC_DATACAL_VALUE(VALUE) ((VALUE) < 0x20)

/**
  * @}
  */ 

 /** @defgroup RTC_Calib_Output_selection_Definitions 
  * @{
  */ 
#define ERTC_CalOutput_512Hz            ((uint32_t)0x00000000) 
#define ERTC_CalOutput_1Hz              ((uint32_t)0x00080000)
#define IS_ERTC_CAL_OUTPUT(OUTPUT)  (((OUTPUT) == ERTC_CalOutput_512Hz) || \
                                      ((OUTPUT) == ERTC_CalOutput_1Hz))
/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_period_Definitions 
  * @{
  */ 
#define ERTC_SmoothCalPeriod_32sec   ((uint32_t)0x00000000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 32s,  else 2exp20 RTCCLK seconds */
#define ERTC_SmoothCalPeriod_16sec   ((uint32_t)0x00002000) /*!<  if RTCCLK = 32768 Hz, Smooth calibration 
                                                             period is 16s, else 2exp19 RTCCLK seconds */
#define ERTC_SmoothCalPeriod_8sec    ((uint32_t)0x00004000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 8s, else 2exp18 RTCCLK seconds */
#define IS_ERTC_SMOOTH_CAL_PERIOD(PERIOD) (((PERIOD) == ERTC_SmoothCalPeriod_32sec) || \
                                             ((PERIOD) == ERTC_SmoothCalPeriod_16sec) || \
                                             ((PERIOD) == ERTC_SmoothCalPeriod_8sec))
                                          
/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_Plus_pulses_Definitions 
  * @{
  */ 
#define ERTC_SmoothCalAddPulses_Set    ((uint32_t)0x00008000) /*!<  The number of RTCCLK pulses added  
                                                                during a X -second window = Y - CALM[8:0]. 
                                                                 with Y = 512, 256, 128 when X = 32, 16, 8 */
#define ERTC_SmoothCalAddPulses_Reset  ((uint32_t)0x00000000) /*!<  The number of RTCCLK pulses subbstited
                                                                 during a 32-second window =   CALM[8:0]. */
#define IS_ERTC_SMOOTH_CAL_ADD(ADD) (((ADD) == ERTC_SmoothCalAddPulses_Set) || \
                                         ((ADD) == ERTC_SmoothCalAddPulses_Reset))

/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_Minus_pulses_Definitions 
  * @{
  */ 
#define  IS_ERTC_SMOOTH_CAL_VALUE(VALUE) ((VALUE) <= 0x000001FF)

/**
  * @}
  */

/** @defgroup RTC_DayLightSaving_Definitions 
  * @{
  */ 
#define ERTC_DayLightSaving_SUB1H   ((uint32_t)0x00020000)
#define ERTC_DayLightSaving_ADD1H   ((uint32_t)0x00010000)
#define IS_ERTC_DAYLIGHT_SAVING(SAVE) (((SAVE) == ERTC_DayLightSaving_SUB1H) || \
                                      ((SAVE) == ERTC_DayLightSaving_ADD1H))

#define ERTC_StoreOperation_Reset        ((uint32_t)0x00000000)
#define ERTC_StoreOperation_Set          ((uint32_t)0x00040000)
#define IS_ERTC_STORE_OPERATION(OPERATION) (((OPERATION) == ERTC_StoreOperation_Reset) || \
                                           ((OPERATION) == ERTC_StoreOperation_Set))
/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Trigger_Definitions 
  * @{
  */ 
#define ERTC_TamperTrig_RisingEdge            ((uint32_t)0x00000000)
#define ERTC_TamperTrig_FallingEdge           ((uint32_t)0x00000001)
#define ERTC_TamperTrig_LowLevel              ((uint32_t)0x00000000)
#define ERTC_TamperTrig_HighLevel             ((uint32_t)0x00000001)
#define IS_ERTC_TAMPER_TRIG(TRIG) (((TRIG) == ERTC_TamperTrig_RisingEdge) || \
                                        ((TRIG) == ERTC_TamperTrig_FallingEdge) || \
                                        ((TRIG) == ERTC_TamperTrig_LowLevel) || \
                                        ((TRIG) == ERTC_TamperTrig_HighLevel)) 

/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Filter_Definitions 
  * @{
  */ 
#define ERTC_TamperFilter_Disable   ((uint32_t)0x00000000) /*!< Tamper filter is disabled */

#define ERTC_TamperFilter_2Sample   ((uint32_t)0x00000800) /*!< Tamper is activated after 2 
                                                          consecutive samples at the active level */
#define ERTC_TamperFilter_4Sample   ((uint32_t)0x00001000) /*!< Tamper is activated after 4 
                                                          consecutive samples at the active level */
#define ERTC_TamperFilter_8Sample   ((uint32_t)0x00001800) /*!< Tamper is activated after 8 
                                                          consecutive samples at the active level. */
#define IS_ERTC_TAMPER_FILTER(FILTER) (((FILTER) == ERTC_TamperFilter_Disable) || \
                                      ((FILTER) == ERTC_TamperFilter_2Sample) || \
                                      ((FILTER) == ERTC_TamperFilter_4Sample) || \
                                      ((FILTER) == ERTC_TamperFilter_8Sample))
/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Sampling_Frequencies_Definitions 
  * @{
  */ 
#define ERTC_TamperSamplingFreq_CLK_Div32768  ((uint32_t)0x00000000) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 32768 */
#define ERTC_TamperSamplingFreq_CLK_Div16384  ((uint32_t)0x000000100) /*!< Each of the tamper inputs are sampled
                                                                            with a frequency =  RTCCLK / 16384 */
#define ERTC_TamperSamplingFreq_CLK_Div8192   ((uint32_t)0x00000200) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 8192  */
#define ERTC_TamperSamplingFreq_CLK_Div4096   ((uint32_t)0x00000300) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 4096  */
#define ERTC_TamperSamplingFreq_CLK_Div2048   ((uint32_t)0x00000400) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 2048  */
#define ERTC_TamperSamplingFreq_CLK_Div1024   ((uint32_t)0x00000500) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 1024  */
#define ERTC_TamperSamplingFreq_CLK_Div512    ((uint32_t)0x00000600) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 512   */
#define ERTC_TamperSamplingFreq_CLK_Div256    ((uint32_t)0x00000700) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 256   */
#define IS_ERTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div32768) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div16384) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div8192) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div4096) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div2048) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div1024) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div512) || \
                                           ((FREQ) ==ERTC_TamperSamplingFreq_CLK_Div256))

/**
  * @}
  */

  /** @defgroup RTC_Tamper_Pin_Precharge_Duration_Definitions 
  * @{
  */ 
#define ERTC_TamperPrechargeDuration_1RTCCLK ((uint32_t)0x00000000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 1 RTCCLK cycle */
#define ERTC_TamperPrechargeDuration_2RTCCLK ((uint32_t)0x00002000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 2 RTCCLK cycles */
#define ERTC_TamperPrechargeDuration_4RTCCLK ((uint32_t)0x00004000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 4 RTCCLK cycles */
#define ERTC_TamperPrechargeDuration_8RTCCLK ((uint32_t)0x00006000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 8 RTCCLK cycles */

#define IS_ERTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == ERTC_TamperPrechargeDuration_1RTCCLK) || \
                                                    ((DURATION) == ERTC_TamperPrechargeDuration_2RTCCLK) || \
                                                    ((DURATION) == ERTC_TamperPrechargeDuration_4RTCCLK) || \
                                                    ((DURATION) == ERTC_TamperPrechargeDuration_8RTCCLK))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Pins_Definitions 
  * @{
  */ 
#define ERTC_TAMP_1 ERTC_TPAF_TM1E
#define ERTC_TAMP_2 ERTC_TPAF_TM2E
#define IS_ERTC_TAMP(TAMP) (((TAMP) == ERTC_TAMP_1) || ((TAMP) == ERTC_TAMP_2))

/**
  * @}
  */

/** @defgroup RTC_Tamper_Pin_Selection 
  * @{
  */ 
#define ERTC_TAMPPIN_Default       ((uint32_t)0x00000000)
#define ERTC_TAMPPIN_Pos1          ((uint32_t)0x00010000)
#define IS_ERTC_TAMP_PIN(PIN)      (((PIN) == ERTC_TAMPPIN_Default) || \
                                    ((PIN) == ERTC_TAMPPIN_Pos1))
/* Legacy Defines */
#define ERTC_TAMPPIN_PC13           ERTC_TAMPPIN_Default
#define ERTC_TAMPPIN_PI8            ERTC_TAMPPIN_Pos1
/**
  * @}
  */ 

/** @defgroup RTC_TimeStamp_Pin_Selection 
  * @{
  */ 
#define ERTC_TimeStampPin_PC13              ((uint32_t)0x00000000)
#define ERTC_TimeStampPin_PI8               ((uint32_t)0x00020000)
#define IS_ERTC_TIMESTAMP_PIN(PIN) (((PIN) == ERTC_TimeStampPin_PC13) || \
                                   ((PIN) == ERTC_TimeStampPin_PI8))

/**
  * @}
  */ 

/** @defgroup RTC_Output_Type_ALARM_OUT 
  * @{
  */ 
#define ERTC_OutputType_OpenDrain           ((uint32_t)0x00000000)
#define ERTC_OutputType_PushPull            ((uint32_t)0x00040000)
#define IS_ERTC_OUTPUT_TYPE(TYPE) (((TYPE) == ERTC_OutputType_OpenDrain) || \
                                  ((TYPE) == ERTC_OutputType_PushPull))

/**
  * @}
  */ 

/** @defgroup RTC_Add_1_Second_Parameter_Definitions
  * @{
  */ 
#define ERTC_ShiftAdd1S_Reset      ((uint32_t)0x00000000)
#define ERTC_ShiftAdd1S_Set        ((uint32_t)0x80000000)
#define IS_ERTC_SHIFT_ADD1S(SEL) (((SEL) == ERTC_ShiftAdd1S_Reset) || \
                                 ((SEL) == ERTC_ShiftAdd1S_Set))
/**
  * @}
  */ 

/** @defgroup RTC_Substract_Fraction_Of_Second_Value
  * @{
  */ 
#define IS_ERTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)

/**
  * @}
  */

/** @defgroup RTC_Backup_Registers_Definitions 
  * @{
  */

#define ERTC_BKP_DT0                       ((uint32_t)0x00000000)
#define ERTC_BKP_DT1                       ((uint32_t)0x00000001)
#define ERTC_BKP_DT2                       ((uint32_t)0x00000002)
#define ERTC_BKP_DT3                       ((uint32_t)0x00000003)
#define ERTC_BKP_DT4                       ((uint32_t)0x00000004)
#define ERTC_BKP_DT5                       ((uint32_t)0x00000005)
#define ERTC_BKP_DT6                       ((uint32_t)0x00000006)
#define ERTC_BKP_DT7                       ((uint32_t)0x00000007)
#define ERTC_BKP_DT8                       ((uint32_t)0x00000008)
#define ERTC_BKP_DT9                       ((uint32_t)0x00000009)
#define ERTC_BKP_DT10                      ((uint32_t)0x0000000A)
#define ERTC_BKP_DT11                      ((uint32_t)0x0000000B)
#define ERTC_BKP_DT12                      ((uint32_t)0x0000000C)
#define ERTC_BKP_DT13                      ((uint32_t)0x0000000D)
#define ERTC_BKP_DT14                      ((uint32_t)0x0000000E)
#define ERTC_BKP_DT15                      ((uint32_t)0x0000000F)
#define ERTC_BKP_DT16                      ((uint32_t)0x00000010)
#define ERTC_BKP_DT17                      ((uint32_t)0x00000011)
#define ERTC_BKP_DT18                      ((uint32_t)0x00000012)
#define ERTC_BKP_DT19                      ((uint32_t)0x00000013)
#define IS_ERTC_BKP(BKP)                  (((BKP) == ERTC_BKP_DT0) || \
                                           ((BKP) == ERTC_BKP_DT1) || \
                                           ((BKP) == ERTC_BKP_DT2) || \
                                           ((BKP) == ERTC_BKP_DT3) || \
                                           ((BKP) == ERTC_BKP_DT4) || \
                                           ((BKP) == ERTC_BKP_DT5) || \
                                           ((BKP) == ERTC_BKP_DT6) || \
                                           ((BKP) == ERTC_BKP_DT7) || \
                                           ((BKP) == ERTC_BKP_DT8) || \
                                           ((BKP) == ERTC_BKP_DT9) || \
                                           ((BKP) == ERTC_BKP_DT10) || \
                                           ((BKP) == ERTC_BKP_DT11) || \
                                           ((BKP) == ERTC_BKP_DT12) || \
                                           ((BKP) == ERTC_BKP_DT13) || \
                                           ((BKP) == ERTC_BKP_DT14) || \
                                           ((BKP) == ERTC_BKP_DT15) || \
                                           ((BKP) == ERTC_BKP_DT16) || \
                                           ((BKP) == ERTC_BKP_DT17) || \
                                           ((BKP) == ERTC_BKP_DT18) || \
                                           ((BKP) == ERTC_BKP_DT19))
/**
  * @}
  */ 

/** @defgroup RTC_Input_parameter_format_definitions 
  * @{
  */ 
#define ERTC_Format_BIN                    ((uint32_t)0x000000000)
#define ERTC_Format_BCD                    ((uint32_t)0x000000001)
#define IS_ERTC_FORMAT(FORMAT) (((FORMAT) == ERTC_Format_BIN) || ((FORMAT) == ERTC_Format_BCD))

/**
  * @}
  */ 

/** @defgroup RTC_Flags_Definitions 
  * @{
  */ 
#define ERTC_FLAG_RECALPDF                 ((uint32_t)0x00010000)
#define ERTC_FLAG_TP1F                     ((uint32_t)0x00002000)
#define ERTC_FLAG_TP2F                     ((uint32_t)0x00004000) 
#define ERTC_FLAG_TSOF                     ((uint32_t)0x00001000)
#define ERTC_FLAG_TSF                      ((uint32_t)0x00000800)
#define ERTC_FLAG_WATF                     ((uint32_t)0x00000400)
#define ERTC_FLAG_ALBF                     ((uint32_t)0x00000200)
#define ERTC_FLAG_ALAF                     ((uint32_t)0x00000100)
#define ERTC_FLAG_INITF                    ((uint32_t)0x00000040)
#define ERTC_FLAG_RSF                      ((uint32_t)0x00000020)
#define ERTC_FLAG_INITS                    ((uint32_t)0x00000010)
#define ERTC_FLAG_SFP                      ((uint32_t)0x00000008)
#define ERTC_FLAG_WATWF                    ((uint32_t)0x00000004)
#define ERTC_FLAG_ALBWF                    ((uint32_t)0x00000002)
#define ERTC_FLAG_ALAWF                    ((uint32_t)0x00000001)
#define IS_ERTC_GET_FLAG(FLAG) (((FLAG) == ERTC_FLAG_TSOF) || ((FLAG) == ERTC_FLAG_TSF) || \
                                ((FLAG) == ERTC_FLAG_WATF) || ((FLAG) == ERTC_FLAG_ALBF) || \
                                ((FLAG) == ERTC_FLAG_ALAF) || ((FLAG) == ERTC_FLAG_INITF) || \
                                ((FLAG) == ERTC_FLAG_RSF) || ((FLAG) == ERTC_FLAG_WATWF) || \
                                ((FLAG) == ERTC_FLAG_ALBWF) || ((FLAG) == ERTC_FLAG_ALAWF) || \
                                ((FLAG) == ERTC_FLAG_TP1F) || ((FLAG) == ERTC_FLAG_RECALPDF) || \
                                ((FLAG) == ERTC_FLAG_TP2F) ||((FLAG) == ERTC_FLAG_SFP))
#define IS_ERTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFF00DF) == (uint32_t)RESET))
/**
  * @}
  */ 

/** @defgroup RTC_Interrupts_Definitions 
  * @{
  */ 
#define ERTC_INT_TS                         ((uint32_t)0x00008000)
#define ERTC_INT_WAT                        ((uint32_t)0x00004000)
#define ERTC_INT_ALB                        ((uint32_t)0x00002000)
#define ERTC_INT_ALA                        ((uint32_t)0x00001000)
#define ERTC_INT_TAMP                       ((uint32_t)0x00000004) /* Used only to Enable the Tamper Interrupt */
#define ERTC_INT_TAMP1                      ((uint32_t)0x00020000)
#define ERTC_INT_TAMP2                      ((uint32_t)0x00040000)

#define IS_ERTC_CONFIG_INT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFF0FFB) == (uint32_t)RESET))
#define IS_ERTC_GET_INT(IT) (((IT) == ERTC_INT_TS) || ((IT) == ERTC_INT_WAT) || \
                           ((IT) == ERTC_INT_ALB) || ((IT) == ERTC_INT_ALA) || \
                           ((IT) == ERTC_INT_TAMP1) || ((IT) == ERTC_INT_TAMP2))
#define IS_ERTC_CLEAR_INT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFF90FFF) == (uint32_t)RESET))

/**
  * @}
  */ 

/** @defgroup RTC_Legacy 
  * @{
  */ 
#define ERTC_DigitalCalConfig  ERTC_CoarseCalConfig
#define ERTC_DigitalCalCmd     ERTC_CoarseCalCmd

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the ERTC configuration to the default reset state *****/
ErrorStatus ERTC_Reset(void);

/* Initialization and Configuration functions *********************************/
ErrorStatus ERTC_Init(ERTC_InitType* ERTC_InitStruct);
void ERTC_StructInit(ERTC_InitType* ERTC_InitStruct);
void ERTC_WriteProtectionCmd(FunctionalState NewState);
ErrorStatus ERTC_EnterInitMode(void);
void ERTC_ExitInitMode(void);
ErrorStatus ERTC_WaitForSynchro(void);
ErrorStatus ERTC_RefClockCmd(FunctionalState NewState);
void ERTC_BypassShadowCmd(FunctionalState NewState);

/* Time and Date configuration functions **************************************/
ErrorStatus ERTC_SetTimeValue(uint32_t ERTC_Format, ERTC_TimeType* ERTC_TimeStruct);
void ERTC_TimeStructInit(ERTC_TimeType* ERTC_TimeStruct);
void ERTC_GetTimeValue(uint32_t ERTC_Format, ERTC_TimeType* ERTC_TimeStruct);
uint32_t ERTC_GetSubSecondValue(void);
ErrorStatus ERTC_SetDateValue(uint32_t ERTC_Format, ERTC_DateType* ERTC_DateStruct);
void ERTC_DateStructInit(ERTC_DateType* ERTC_DateStruct);
void ERTC_GetDateValue(uint32_t ERTC_Format, ERTC_DateType* ERTC_DateStruct);

/* Alarms (Alarm A and Alarm B) configuration functions  **********************/
void ERTC_SetAlarmValue(uint32_t ERTC_Format, uint32_t ERTC_Alarm, ERTC_AlarmType* ERTC_AlarmStruct);
void ERTC_AlarmStructInit(ERTC_AlarmType* ERTC_AlarmStruct);
void ERTC_GetAlarmValue(uint32_t ERTC_Format, uint32_t ERTC_Alarm, ERTC_AlarmType* ERTC_AlarmStruct);
ErrorStatus ERTC_AlarmCmd(uint32_t ERTC_Alarm, FunctionalState NewState);
void ERTC_AlarmSubSecondConfig(uint32_t ERTC_Alarm, uint32_t ERTC_AlarmSubSecondValue, uint32_t ERTC_AlarmSubSecondMask);
uint32_t ERTC_GetAlarmSubSecond(uint32_t ERTC_Alarm);

/* WakeUp Timer configuration functions ***************************************/
void ERTC_WakeUpClockConfig(uint32_t ERTC_WakeUpClock);
void ERTC_SetWakeUpCounter(uint32_t ERTC_WakeUpCounter);
uint32_t ERTC_GetWakeUpCounter(void);
ErrorStatus ERTC_WakeUpCmd(FunctionalState NewState);

/* Daylight Saving configuration functions ************************************/
void ERTC_DayLightSavingConfig(uint32_t ERTC_DayLightSaving, uint32_t ERTC_StoreOperation);
uint32_t ERTC_GetStoreOperation(void);

/* Output pin Configuration function ******************************************/
void ERTC_OutputConfig(uint32_t ERTC_Output, uint32_t ERTC_OutputPolarity);

/* Digital Calibration configuration functions *********************************/
ErrorStatus ERTC_CoarseCalConfig(uint32_t ERTC_CalSign, uint32_t Value);
ErrorStatus ERTC_CoarseCalCmd(FunctionalState NewState);
void ERTC_CalOutputCmd(FunctionalState NewState);
void ERTC_CalOutputConfig(uint32_t ERTC_CalOutput);
ErrorStatus ERTC_SmoothCalConfig(uint32_t ERTC_SmoothCalPeriod, 
                                  uint32_t ERTC_SmoothCalPlusPulses,
                                  uint32_t ERTC_SmouthCalMinusPulsesValue);

/* TimeStamp configuration functions ******************************************/
void ERTC_TimeStampCmd(uint32_t ERTC_TimeStampEdge, FunctionalState NewState);
void ERTC_GetTimeStamp(uint32_t ERTC_Format, ERTC_TimeType* ERTC_StampTimeStruct,
                                      ERTC_DateType* ERTC_StampDateStruct);
uint32_t ERTC_GetTimeStampSubSecond(void);

/* Tampers configuration functions ********************************************/
void ERTC_TamperTriggerConfig(uint32_t ERTC_Tamper, uint32_t ERTC_TamperTrigger);
void ERTC_TamperCmd(uint32_t ERTC_Tamper, FunctionalState NewState);
void ERTC_TamperFilterConfig(uint32_t ERTC_TamperFilter);
void ERTC_TamperSamplingFreqConfig(uint32_t ERTC_TamperSamplingFreq);
void ERTC_TamperPinsPrechargeDuration(uint32_t ERTC_TamperPrechargeDuration);
void ERTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState);
void ERTC_TamperPullUpCmd(FunctionalState NewState);

/* Backup Data Registers configuration functions ******************************/
void ERTC_WriteBackupRegister(uint32_t ERTC_BKP_DT, uint32_t Data);
uint32_t ERTC_ReadBackupRegister(uint32_t ERTC_BKP_DT);

/* ERTC Tamper and TimeStamp Pins Selection and Output Type Config configuration
   functions ******************************************************************/
void ERTC_TamperPinSelection(uint32_t ERTC_TamperPin);
void ERTC_TimeStampPinSelection(uint32_t ERTC_TimeStampPin);
void ERTC_OutputTypeConfig(uint32_t ERTC_OutputType);

/* RTC_Shift_control_synchonisation_functions *********************************/
ErrorStatus ERTC_SynchroShiftConfig(uint32_t ERTC_ShiftAdd1S, uint32_t ERTC_ShiftSubFS);

/* Interrupts and flags management functions **********************************/
void ERTC_INTConfig(uint32_t ERTC_INT, FunctionalState NewState);
FlagStatus ERTC_GetFlagStatus(uint32_t ERTC_FLAG);
void ERTC_ClearFlag(uint32_t ERTC_FLAG);
ITStatus ERTC_GetINTStatus(uint32_t ERTC_INT);
void ERTC_ClearINTPendingBINT(uint32_t ERTC_INT);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_RCC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
