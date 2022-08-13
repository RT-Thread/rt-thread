/*!
 * @file        apm32f4xx_rtc.h
 *
 * @brief       This file contains all the functions prototypes for the RTC firmware library.
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_RTC_H
#define __APM32F4XX_RTC_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup RTC_Driver
  @{
*/

/** @defgroup RTC_Enumerations
  @{
*/

/**
 * @brief RTC Hour Formats
 */
typedef enum
{
    RTC_HOURFORMAT_24,  /*!< 24 hour/day format */
    RTC_HOURFORMAT_12   /*!< AM/PM hour format */
} RTC_HOUR_FORMAT_T;

/**
 * @brief RTC Input parameter format
 */
typedef enum
{
    RTC_FORMAT_BIN, /*!< Format in BIN */
    RTC_FORMAT_BCD  /*!< Format in BCD */
} RTC_FORMAT_T;

/**
 * @brief RTC AM PM
 */
typedef enum
{
    RTC_H12_AM, /*!< Set RTC time to AM */
    RTC_H12_PM  /*!< Set RTC time to PM */
} RTC_H12_T;

/**
 * @brief RTC MONTH
 */
typedef enum
{
    RTC_MONTH_JANUARY   = 0x01, /*!< January */
    RTC_MONTH_FEBRUARY  = 0x02, /*!< February */
    RTC_MONTH_MARCH     = 0x03, /*!< March */
    RTC_MONTH_APRIL     = 0x04, /*!< April */
    RTC_MONTH_MAY       = 0x05, /*!< May */
    RTC_MONTH_JUNE      = 0x06, /*!< June */
    RTC_MONTH_JULY      = 0x07, /*!< July */
    RTC_MONTH_AUGUST    = 0x08, /*!< August */
    RTC_MONTH_SEPTEMBER = 0x09, /*!< September */
    RTC_MONTH_OCTOBER   = 0x10, /*!< October */
    RTC_MONTH_NOVEMBER  = 0x11, /*!< November */
    RTC_MONTH_DECEMBER  = 0x12  /*!< December */
} RTC_MONTH_T;

/**
 * @brief RTC WEEKDAY
 */
typedef enum
{
    RTC_WEEKDAY_MONDAY    = 0x01,   /*!< Set Monday as the weekend */
    RTC_WEEKDAY_TUESDAY   = 0x02,   /*!< Set Tuesday as the weekend */
    RTC_WEEKDAY_WEDNESDAY = 0x03,   /*!< Set Wednesday as the weekend */
    RTC_WEEKDAY_THURSDAY  = 0x04,   /*!< Set Thursday as the weekend */
    RTC_WEEKDAY_FRIDAY    = 0x05,   /*!< Set Friday as the weekend */
    RTC_WEEKDAY_SATURDAY  = 0x06,   /*!< Set Saturday as the weekend */
    RTC_WEEKDAY_SUNDAY    = 0x07    /*!< Set sunday as the weekend */
} RTC_WEEKDAY_T;

/**
 * @brief RTC AlarmDateWeekDay
 */
typedef enum
{
    RTC_WEEKDAY_SEL_DATE,       /*!< Select DAYU to represent the date */
    RTC_WEEKDAY_SEL_WEEKDAY     /*!< Select DAYU to represent the weekday */
} RTC_WEEKDAY_SEL_T;

/**
 * @brief  RTC AlarmMask
 */
typedef enum
{
    RTC_MASK_NONE        = (uint32_t)0x00000000,    /*!< No mask */
    RTC_MASK_DATEWEEK    = (int32_t)0x80000000,     /*!< Dateweek mask */
    RTC_MASK_HOURS       = (uint32_t)0x00800000,    /*!< Hours mask */
    RTC_MASK_MINUTES     = (uint32_t)0x00008000,    /*!< Minutes mask */
    RTC_MASK_SECONDS     = (uint32_t)0x00000080,    /*!< Seconds mask */
    RTC_MASK_ALL         = (int32_t)0x80808080      /*!< All mask  */
} RTC_MASK_T;

/**
 * @brief RTC ALARMA ALARMB
 */
typedef enum
{
    RTC_ALARM_A = 0x0100,   /*!< Select Alarm A */
    RTC_ALARM_B = 0x0200    /*!< Select Alarm B */
} RTC_ALARM_T;

/**
 * @brief RTC_ALARM_SS description
 */
typedef enum
{
    RTC_ALARM_SUBSEC_MASK_ALL ,   /*!< All Alarm SUBSEC fields are masked */
    RTC_ALARM_SUBSEC_MASK_14_1,   /*!< Mask SUBSEC[14:1] and Alarm comparison is SUBSEC[0] */
    RTC_ALARM_SUBSEC_MASK_14_2,   /*!< Mask SUBSEC[14:2] and Alarm comparison is SUBSEC[1:0] */
    RTC_ALARM_SUBSEC_MASK_14_3,   /*!< Mask SUBSEC[14:3] and Alarm comparison is SUBSEC[2:0] */
    RTC_ALARM_SUBSEC_MASK_14_4,   /*!< Mask SUBSEC[14:4] and Alarm comparison is SUBSEC[3:0] */
    RTC_ALARM_SUBSEC_MASK_14_5,   /*!< Mask SUBSEC[14:5] and Alarm comparison is SUBSEC[4:0] */
    RTC_ALARM_SUBSEC_MASK_14_6,   /*!< Mask SUBSEC[14:6] and Alarm comparison is SUBSEC[5:0] */
    RTC_ALARM_SUBSEC_MASK_14_7,   /*!< Mask SUBSEC[14:7] and Alarm comparison is SUBSEC[6:0] */
    RTC_ALARM_SUBSEC_MASK_14_8,   /*!< Mask SUBSEC[14:8] and Alarm comparison is SUBSEC[7:0] */
    RTC_ALARM_SUBSEC_MASK_14_9,   /*!< Mask SUBSEC[14:9] and Alarm comparison is SUBSEC[8:0] */
    RTC_ALARM_SUBSEC_MASK_14_10,  /*!< Mask SUBSEC[14:10] and Alarm comparison is SUBSEC[9:0] */
    RTC_ALARM_SUBSEC_MASK_14_11,  /*!< Mask SUBSEC[14:11] and Alarm comparison is SUBSEC[10:0] */
    RTC_ALARM_SUBSEC_MASK_14_12,  /*!< Mask SUBSEC[14:12] and Alarm comparison is SUBSEC[11:0] */
    RTC_ALARM_SUBSEC_MASK_14_13,  /*!< Mask SUBSEC[14:13] and Alarm comparison is SUBSEC[12:0] */
    RTC_ALARM_SUBSEC_MASK_14,     /*!< Mask SUBSEC[14] and Alarm comparison is SUBSEC[13:0] */
    RTC_ALARM_SUBSEC_MASK_NONE    /*!< Alarm comparison is all the SUBSEC bit */
} RTC_ALARM_SUBSEC_MASK_T;

/**
 * @brief RTC Wakeup clock select
 */
typedef enum
{
    RTC_WAKEUP_CLOCK_RTC_DIV16   = 0x00, /*!<  Wakeup Clock select to RTC/16 */
    RTC_WAKEUP_CLOCK_RTC_DIV8    = 0x01, /*!<  Wakeup Clock select to RTC/8 */
    RTC_WAKEUP_CLOCK_RTC_DIV4    = 0x02, /*!<  Wakeup Clock select to RTC/4 */
    RTC_WAKEUP_CLOCK_RTC_DIV2    = 0x03, /*!<  Wakeup Clock select to RTC/2 */
    RTC_WAKEUP_CLOCK_CK_SPRE_16B = 0x04, /*!<  Wakeup Clock select to clk_spre */
    RTC_WAKEUP_CLOCK_CK_SPRE_17B = 0x06  /*!<  Wakeup Clock select to clk_spre */
} RTC_WAKEUP_CLOCK_T;

/**
 * @brief RTC Time Stamp Edges
 */
typedef enum
{
    RTC_TIMESTAMP_EDGE_RISING,  /*!< Rising edge generates a timestamp event */
    RTC_TIMESTAMP_EDGE_FALLING  /*!< Falling edge generates a timestamp event */
} RTC_TIMESTAMP_EDGE_T;

/**
 * @brief RTC Output selection
 */
typedef enum
{
    RTC_OUT_SEL_DISABLE,    /*!< Disable RTC output */
    RTC_OUT_SEL_ALARM_A,    /*!< Select alarm A as RTC output */
    RTC_OUT_SEL_ALARM_B,    /*!< Select alarm B as RTC output */
    RTC_OUT_SEL_WAKEUP      /*!< Select wake up as RTC output */
} RTC_OUT_SEL_T;

/**
 * @brief RTC Output Polarity
 */
typedef enum
{
    RTC_OUT_POLARITY_HIGH,  /*!< The output polarity is high */
    RTC_OUT_POLARITY_LOW    /*!< The output polarity is low */
} RTC_OUT_POLARITY_T;

/**
 * @brief RTC Digital Calibration sign
 */
typedef enum
{
    RTC_CALIB_SIGN_POSITIVE,    /*!< The Calibration sign is positive */
    RTC_CALIB_SIGN_NEGATIVE     /*!< The Calibration sign is negative */
} RTC_CALIB_SIGN_T;

/**
 * @brief RTC Calibration Output selection
 */
typedef enum
{
    RTC_CALIB_OUTPUT_512HZ, /*!< Calibration output is 512 Hz */
    RTC_CALIB_OUTPUT_1HZ    /*!< Calibration output is 1 Hz */
} RTC_CALIB_OUTPUT_T;

/**
 * @brief RTC Smooth Calibration period
 */
typedef enum
{
    RTC_SCP_32SEC, /*!< if RTCCLK is 32768 Hz, Smooth calibration period will be 32s,
                        else 2exp20 RTCCLK seconds */
    RTC_SCP_16SEC, /*!< if RTCCLK is 32768 Hz, Smooth calibration period will be 16s,
                        else 2exp19 RTCCLK seconds */
    RTC_SCP_8SEC   /*!< if RTCCLK is 32768 Hz, Smooth calibration period will be 8s,
                        else 2exp18 RTCCLK seconds */
} RTC_SCP_T;

/**
 * @brief  RTC Smooth Calibration Plus pulses
 */
typedef enum
{
    RTC_SCPP_RESET, /*!< Add one RTCCLK puls every 2**11 pulses */
    RTC_SCPP_SET    /*!< No RTCCLK pulses are added */
} RTC_SCPP_T;

/**
 * @brief RTC DayLight Saving
 */
typedef enum
{
    RTC_DLS_SUB_1H, /*!< Winter time change */
    RTC_DLS_ADD_1H  /*!< Summer time change */
} RTC_DLS_T;

/**
 * @brief RTC Store Operation to Backup bit
 */
typedef enum
{
    RTC_BACKUP_RESET,   /*!< Reset backup value */
    RTC_BACKUP_SET      /*!< Set backup value */
} RTC_BACKUP_T;

/**
 * @brief RTC Tamper Trigger
 */
typedef enum
{
    RTC_TAMPER_TRIGGER_EDGE_RISING  = 0,    /*!< Rising Edge of the tamper pin causes tamper event */
    RTC_TAMPER_TRIGGER_EDGE_FALLING = 1,    /*!< Falling Edge of the tamper pin causes tamper event */
    RTC_TAMPER_TRIGGER_LEVEL_LOW    = 0,    /*!< Low Level of the tamper pin causes tamper event */
    RTC_TAMPER_TRIGGER_LEVEL_HIGH   = 1     /*!< High Level of the tamper pin causes tamper event */
} RTC_TAMPER_TRIGGER_T;

/**
 * @brief Tampers Filter
 */
typedef enum
{
    RTC_TAMPER_FILTER_DISABLE,  /*!< Tamper filter is disabled */
    RTC_TAMPER_FILTER_2SAMPLE,  /*!< Tamper is activated after 2 consecutive samples at the active level */
    RTC_TAMPER_FILTER_4SAMPLE,  /*!< Tamper is activated after 4 consecutive samples at the active level */
    RTC_TAMPER_FILTER_8SAMPLE   /*!< Tamper is activated after 8 consecutive samples at the active level */
} RTC_TAMPER_FILTER_T;

/**
 * @brief Tampers Sampling Frequency
 */
typedef enum
{
    RTC_TSF_DIV_32768, /*!< Tampers Sampling Frequency = RTC_CLK / 32768 */
    RTC_TSF_DIV_16384, /*!< Tampers Sampling Frequency = RTC_CLK / 16384 */
    RTC_TSF_DIV_8192,  /*!< Tampers Sampling Frequency = RTC_CLK / 8192 */
    RTC_TSF_DIV_4096,  /*!< Tampers Sampling Frequency = RTC_CLK / 4096 */
    RTC_TSF_DIV_2048,  /*!< Tampers Sampling Frequency = RTC_CLK / 2048 */
    RTC_TSF_DIV_1024,  /*!< Tampers Sampling Frequency = RTC_CLK / 1024 */
    RTC_TSF_DIV_512,   /*!< Tampers Sampling Frequency = RTC_CLK / 512 */
    RTC_TSF_DIV_256    /*!< Tampers Sampling Frequency = RTC_CLK / 256 */
} RTC_TSF_DIV_T;

/**
 * @brief Tamper Precharge Duration
 */
typedef enum
{
    RTC_TPD_RTCCLK_1, /*!< Duration is 1 RTCCLK cycle */
    RTC_TPD_RTCCLK_2, /*!< Duration is 2 RTCCLK cycle */
    RTC_TPD_RTCCLK_4, /*!< Duration is 4 RTCCLK cycle */
    RTC_TPD_RTCCLK_8  /*!< Duration is 8 RTCCLK cycle */
} RTC_TPD_RTCCLK_T;

/**
 * @brief RTC Tamper Pin Selection
 */
typedef enum
{
    RTC_TAMPER_PIN_AF1, /*!< RTC_TAMP1 is mapped to PC13 */
    RTC_TAMPER_PIN_AF2  /*!< RTC_TAMP1 is mapped to PI8 */
} RTC_TAMPER_PIN_T;

/**
 * @brief RTC TimeStamp Pin Selection
 */
typedef enum
{
    RTC_TIMESTAMP_PIN_AF1, /*!< TimeStamp Pin is mapped to PC13 */
    RTC_TIMESTAMP_PIN_AF2  /*!< TimeStamp Pin is mapped to PI8 */
} RTC_TIMESTAMP_PIN_T;

/**
 * @brief RTC Output Type ALARM OUT
 */
typedef enum
{
    RTC_OUTPUT_OD, /*!< RTC_ALARM output Open-drain */
    RTC_OUTPUT_PP  /*!< RTC_ALARM output Push-pull */
} RTC_OUTPUT_T;

/**
 * @brief RTC Add 1 Second Parameter
 */
typedef enum
{
    RTC_SHIFT_ADD1S_RESET,  /*!< No effect */
    RTC_SHIFT_ADD1S_SET     /*!< Add one second to the clock calendar */
} RTC_SHIFT_ADD1S_T;

/**
 * @brief RTC_Backup register
 */
typedef enum
{
    RTC_BAKP_REG_0,  /*!< Backup register 0 */
    RTC_BAKP_REG_1,  /*!< Backup register 1 */
    RTC_BAKP_REG_2,  /*!< Backup register 2 */
    RTC_BAKP_REG_3,  /*!< Backup register 3 */
    RTC_BAKP_REG_4,  /*!< Backup register 4 */
    RTC_BAKP_REG_5,  /*!< Backup register 5 */
    RTC_BAKP_REG_6,  /*!< Backup register 6 */
    RTC_BAKP_REG_7,  /*!< Backup register 7 */
    RTC_BAKP_REG_8,  /*!< Backup register 8 */
    RTC_BAKP_REG_9,  /*!< Backup register 9 */
    RTC_BAKP_REG_10, /*!< Backup register 10 */
    RTC_BAKP_REG_11, /*!< Backup register 11 */
    RTC_BAKP_REG_12, /*!< Backup register 12 */
    RTC_BAKP_REG_13, /*!< Backup register 13 */
    RTC_BAKP_REG_14, /*!< Backup register 14 */
    RTC_BAKP_REG_15, /*!< Backup register 15 */
    RTC_BAKP_REG_16, /*!< Backup register 16 */
    RTC_BAKP_REG_17, /*!< Backup register 17 */
    RTC_BAKP_REG_18, /*!< Backup register 18 */
    RTC_BAKP_REG_19  /*!< Backup register 19 */
} RTC_BAKP_REG_T;

/**
 * @brief RTC flag
 */
typedef enum
{
    RTC_FLAG_AAWF  = BIT0,  /*!< Alarm A Write Flag */
    RTC_FLAG_ABWF  = BIT1,  /*!< Alarm B Write Flag */
    RTC_FLAG_WTWF  = BIT2,  /*!< Wakeup Timer Write Flag */
    RTC_FLAG_SOPF  = BIT3,  /*!< Shift Operation Pending Flag */
    RTC_FLAG_ISF   = BIT4,  /*!< Initialization State Flag */
    RTC_FLAG_RSF   = BIT5,  /*!< Registers Synchronization Flag */
    RTC_FLAG_INTF  = BIT6,  /*!< Register Initialization Flag */
    RTC_FLAG_ALRAF = BIT8,  /*!< Alarm A Match Flag */
    RTC_FLAG_ALRBF = BIT9,  /*!< Alarm B Match Flag */
    RTC_FLAG_WTF   = BIT10, /*!< Wakeup Timer Flag */
    RTC_FLAG_TSF   = BIT11, /*!< Time Stamp Flag */
    RTC_FLAG_TSOF  = BIT12, /*!< Time Stamp Overflow Flag */
    RTC_FLAG_TP1F  = BIT13, /*!< Tamper 1 event Detection Flag */
    RTC_FLAG_TP2F  = BIT14, /*!< Tamper 2 event Detection Flag */
    RTC_FLAG_RPF   = BIT16  /*!< Recalibration Pending Flag */
} RTC_FLAG_T;

/**
 * @brief RTC Interrupts  Flag
 */
typedef enum
{
    RTC_INT_FLAG_ALRA  = (uint32_t)0x00001000, /*!< Alarm A interrupt flag */
    RTC_INT_FLAG_ALRB  = (uint32_t)0x00002000, /*!< Alarm B interrupt flag */
    RTC_INT_FLAG_WT    = (uint32_t)0x00004000, /*!< Time Stamp interrupt flag */
    RTC_INT_FLAG_TS    = (uint32_t)0x00008000, /*!< WakeUp Timer interrupt flag */
    RTC_INT_FLAG_TAMP1 = (uint32_t)0x00020001, /*!< Tamper1 event interrupt flag */
    RTC_INT_FLAG_TAMP2 = (uint32_t)0x00040001  /*!< Tamper2 event interrupt flag */
} RTC_INT_FLAG_T;

/**
 * @brief RTC Interrupts
 */
typedef enum
{
    RTC_INT_ALRA = BIT12, /*!< Alarm A interrupt */
    RTC_INT_ALRB = BIT13, /*!< Alarm B interrupt */
    RTC_INT_WT   = BIT14, /*!< WakeUp Timer interrupt */
    RTC_INT_TS   = BIT15, /*!< Time Stamp interrupt */
    RTC_INT_TAMP = BIT2   /*!< Tamper Interrupt in TACFG register */
} RTC_INT_T;

/**
 * @brief Selected RTC Tamper Pin
 */
typedef enum
{
    RTC_TAMPER_1,   /*!< Select Tamper 1 */
    RTC_TAMPER_2    /*!< Select Tamper 2 */
} RTC_TAMPER_T;

/**@} end of group RTC_Enumerations*/

/** @addtogroup RTC_Structure Data Structure
  @{
*/

/**
 * @brief  RTC Init structures definition
 */
typedef struct
{
    RTC_HOUR_FORMAT_T format;       /*!< RTC hour formats selection */
    uint32_t          asynchPrediv; /*!< Asynchronous prescaler coefficient setting */
    uint32_t          synchPrediv;  /*!< Synchronous prescaler coefficient setting */
} RTC_Config_T;

/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
    uint8_t   hours;    /*!< Set hours of RTC time */
    uint8_t   minutes;  /*!< Set minutes of RTC time */
    uint8_t   seconds;  /*!< Set seconds of RTC time */
    RTC_H12_T h12;      /*!< Set RTC time to AM or PM */
} RTC_TimeConfig_T;

/**
  * @brief  RTC Date structure definition
  */
typedef struct
{
    RTC_WEEKDAY_T weekday;  /*!< Set weekday of RTC date */
    RTC_MONTH_T   month;    /*!< Set month of RTC date */
    uint8_t       date;     /*!< Set date of RTC date */
    uint8_t       year;     /*!< Set year of RTC date */
} RTC_DateConfig_T;

/**
  * @brief  RTC ALRMA structure definition
  */
typedef struct
{
    RTC_TimeConfig_T  time;                 /*!< Set RTC time */
    uint32_t          alarmMask;            /*!< Set alarm mask */
    RTC_WEEKDAY_SEL_T alarmDateWeekDaySel;  /*!< Set weekday's DAYU of alarm date */
    uint8_t           alarmDateWeekDay;     /*!< Set weekday of alarm date */
} RTC_AlarmConfig_T;

/**@} end of group RTC_Structure*/

/** @addtogroup RTC_Functions
  @{
*/

/* RTC reset */
uint8_t RTC_Reset(void);

/* Initialization and Configuration */
uint8_t RTC_Config(RTC_Config_T* rtcConfig);
void RTC_ConfigStructInit(RTC_Config_T* rtcConfig);
void RTC_EnableWriteProtection(void);
void RTC_DisableWriteProtection(void);
uint8_t RTC_EnableInit(void);
void RTC_DisableInit(void);
uint8_t RTC_WaitForSynchro(void);
uint8_t RTC_EnableRefClock(void);
uint8_t RTC_DisableRefClock(void);
void RTC_EnableBypassShadow(void);
void RTC_DisableBypassShadow(void);

/* Time */
uint8_t RTC_ConfigTime(RTC_FORMAT_T format, RTC_TimeConfig_T* timeConfig);
void RTC_ConfigTimeStructInit(RTC_TimeConfig_T* timeConfig);
void RTC_ReadTime(RTC_FORMAT_T format, RTC_TimeConfig_T* time);
uint32_t RTC_ReadSubSecond(void);

/* Date */
uint8_t RTC_ConfigDate(RTC_FORMAT_T format, RTC_DateConfig_T* dateConfig);
void RTC_ConfigDateStructInit(RTC_DateConfig_T* dateConfig);
void RTC_ReadDate(RTC_FORMAT_T format, RTC_DateConfig_T* date);

/* Alarms (Alarm A and Alarm B)*/
void RTC_ConfigAlarm(RTC_FORMAT_T format, RTC_ALARM_T alarm, RTC_AlarmConfig_T* alarmConfig);
void RTC_ConfigAlarmStructInit(RTC_AlarmConfig_T* alarmConfig);
void RTC_ReadAlarm(RTC_FORMAT_T format, RTC_ALARM_T alarm, RTC_AlarmConfig_T* alarmConfig);
void RTC_EnableAlarmA(void);
uint8_t RTC_DisableAlarmA(void);
void RTC_EnableAlarmB(void);
uint8_t RTC_DisableAlarmB(void);
void RTC_ConfigAlarmSubSecond(RTC_ALARM_T alarm, uint32_t val, RTC_ALARM_SUBSEC_MASK_T mask);
uint16_t RTC_ReadAlarmSubSecond(RTC_ALARM_T alarm);

/* WakeUp Timer */
void RTC_ConfigWakeUpClock(RTC_WAKEUP_CLOCK_T wakeUpClock);
void RTC_ConfigWakeUpValue(uint16_t wakeUpValue);
uint16_t RTC_ReadWakeUpValue(void);
void RTC_EnableWakeUp(void);
uint8_t RTC_DisableWakeUp(void);

/* Daylight Saving */
void RTC_ConfigDayLightSaving(RTC_DLS_T saving, RTC_BACKUP_T bit);
uint8_t RTC_ReadStoreOperation(void);

/* Alarm Output */
void RTC_ConfigOutput(RTC_OUT_SEL_T outputSel, RTC_OUT_POLARITY_T polarity);

/* Coarse Digital Calibration */
uint8_t RTC_ConfigCoarseCalib(RTC_CALIB_SIGN_T calibSign, uint32_t value);
uint8_t RTC_EnableCoarseCalib(void);
uint8_t RTC_DisableCoarseCalib(void);

/* Calibration Output */
void RTC_EnableCalibOutput(void);
void RTC_DisableCalibOutput(void);
void RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_T calib);

/* Smooth Digital Calibration */
uint8_t RTC_ConfigSmoothCalib(RTC_SCP_T period, RTC_SCPP_T calibPulse, uint16_t value);

/* TimeStamp */
void RTC_EnableTimeStamp(RTC_TIMESTAMP_EDGE_T edge);
void RTC_DisableTimeStamp(void);
void RTC_ReadTimeDate(RTC_FORMAT_T format, RTC_TimeConfig_T* time, RTC_DateConfig_T* date);
uint16_t RTC_ReadTimeStampSubSecond(void);

/* Tamper */
void RTC_ConfigTamperTrigger(RTC_TAMPER_T tamper, RTC_TAMPER_TRIGGER_T trigger);
void RTC_EnableTamper(RTC_TAMPER_T tamper);
void RTC_DisableTamper(RTC_TAMPER_T tamper);
void RTC_ConfigFilter(RTC_TAMPER_FILTER_T filter);
void RTC_ConfigSamplingFreq(RTC_TSF_DIV_T freq);
void RTC_PinsPrechargeDuration(RTC_TPD_RTCCLK_T duration);
void RTC_EnableTDE(void);
void RTC_DisableTDE(void);
void RTC_EnablePullUp(void);
void RTC_DisablePullUp(void);

/* Backup Data Registers */
void RTC_WriteBackup(RTC_BAKP_REG_T backupReg, uint32_t data);
uint32_t RTC_ReadBackup(RTC_BAKP_REG_T backup);

/* Tamper and TimeStamp Pins mapping */
void RTC_ConfigTamperPin(RTC_TAMPER_PIN_T tamperPin);
void RTC_ConfigTimeStampPin(RTC_TIMESTAMP_PIN_T timeStampPin);
/* Output Type */
void RTC_ConfigOutputType(RTC_OUTPUT_T outputType);

/* Shift control synchonisation */
uint8_t RTC_ConfigSynchroShift(RTC_SHIFT_ADD1S_T add1S, uint16_t subFS);

/* Interrupts and flags */
void RTC_EnableInterrupt(uint32_t interrupt);
void RTC_DisableInterrupt(uint32_t interrupt);
uint8_t RTC_ReadStatusFlag(RTC_FLAG_T flag);
void RTC_ClearStatusFlag(uint32_t flag);
uint8_t RTC_ReadIntFlag(RTC_INT_FLAG_T flag);
void RTC_ClearIntFlag(uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_RTC_H */

/**@} end of group RTC_Enumerations */
/**@} end of group RTC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
