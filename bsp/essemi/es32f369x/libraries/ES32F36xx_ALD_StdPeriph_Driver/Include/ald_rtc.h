/**
  ******************************************************************************
  * @file    ald_rtc.h
  * @brief   Header file of RTC Module driver.
  *
  * @version V1.0
  * @date    16 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *******************************************************************************
  */

#ifndef __ALD_RTC_H__
#define __ALD_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_Public_Types RTC Public Types
  * @{
  */

/**
  * @brief Hours format
  */
typedef enum {
	RTC_HOUR_FORMAT_24 = 0x0,	/**< 24-hours format */
	RTC_HOUR_FORMAT_12 = 0x1,	/**< 12-hours format */
} rtc_hour_format_t;

/**
  * @brief Output mode
  */
typedef enum {
	RTC_OUTPUT_DISABLE = 0x0,	/**< Disable output */
	RTC_OUTPUT_ALARM_A = 0x1,	/**< Output alarm_a signal */
	RTC_OUTPUT_ALARM_B = 0x2,	/**< Output alarm_b signal */
	RTC_OUTPUT_WAKEUP  = 0x3,	/**< Output wakeup signal */
} rtc_output_select_t;

/**
  * @brief Output polarity
  */
typedef enum {
	RTC_OUTPUT_POLARITY_HIGH = 0x0,	/**< Polarity is high */
	RTC_OUTPUT_POLARITY_LOW  = 0x1,	/**< Polarity is low */
} rtc_output_polarity_t;

/**
  * @brief Initialization structure
  */
typedef struct {
	rtc_hour_format_t hour_format;		/**< Hours format */
	uint32_t asynch_pre_div;		/**< Asynchronous predivider value */
	uint32_t synch_pre_div;			/**< Synchronous predivider value */
	rtc_output_select_t output;		/**< Output signal type */
	rtc_output_polarity_t output_polarity;	/**< Output polarity */
} rtc_init_t;

/**
  * @brief Source select
  */
typedef enum {
	RTC_SOURCE_LOSC        = 0x0,	/**< LOSC */
	RTC_SOURCE_LRC         = 0x1,	/**< LRC */
	RTC_SOURCE_HRC_DIV_1M  = 0x2,	/**< HRC divide to 1MHz */
	RTC_SOURCE_HOSC_DIV_1M = 0x3,	/**< HOSC divide to 1MHz */
} rtc_source_sel_t;

/**
  * @brief Time structure
  */
typedef struct {
	uint8_t hour;		/**< Hours */
	uint8_t minute;		/**< Minutes */
	uint8_t second;		/**< Seconds */
	uint16_t sub_sec;	/**< Sub-seconds */
} rtc_time_t;

/**
  * @brief Date structure
  */
typedef struct {
	uint8_t week;	/**< Weeks */
	uint8_t day;	/**< days */
	uint8_t month;	/**< months */
	uint8_t year;	/**< years */
} rtc_date_t;

/**
  * @brief Data format
  */
typedef enum {
	RTC_FORMAT_DEC = 0,	/**< Decimal */
	RTC_FORMAT_BCD = 1,	/**< BSD */
} rtc_format_t;

/**
  * @brief Index of alarm
  */
typedef enum {
	RTC_ALARM_A = 0x0,	/**< Alarm-A */
	RTC_ALARM_B = 0x1,	/**< Alarm-B */
} rtc_alarm_idx_t;

/**
  * @brief Alarm mask
  */
typedef enum {
	RTC_ALARM_MASK_NONE     = 0x0,		/**< Mask is disable */
	RTC_ALARM_MASK_WEEK_DAY = (1U << 30),	/**< Mask week or day */
	RTC_ALARM_MASK_HOUR     = (1U << 23),	/**< Mask hour */
	RTC_ALARM_MASK_MINUTE   = (1U << 15),	/**< Mask minute */
	RTC_ALARM_MASK_SECOND   = (1U << 7),	/**< Mask second */
	RTC_ALARM_MASK_ALL      = 0x40808080,	/**< Mask all */
} rtc_alarm_mask_t;

/**
  * @brief Alarm sub-second mask
  */
typedef enum {
	RTC_ALARM_SS_MASK_NONE  = 0xF,	/**< Mask is disable */
	RTC_ALARM_SS_MASK_14_1  = 0x1,	/**< Mask bit(1-14) */
	RTC_ALARM_SS_MASK_14_2  = 0x2,	/**< Mask bit(2-14) */
	RTC_ALARM_SS_MASK_14_3  = 0x3,	/**< Mask bit(3-14) */
	RTC_ALARM_SS_MASK_14_4  = 0x4,	/**< Mask bit(4-14) */
	RTC_ALARM_SS_MASK_14_5  = 0x5,	/**< Mask bit(5-14) */
	RTC_ALARM_SS_MASK_14_6  = 0x6,	/**< Mask bit(6-14) */
	RTC_ALARM_SS_MASK_14_7  = 0x7,	/**< Mask bit(7-14) */
	RTC_ALARM_SS_MASK_14_8  = 0x8,	/**< Mask bit(8-14) */
	RTC_ALARM_SS_MASK_14_9  = 0x9,	/**< Mask bit(9-14) */
	RTC_ALARM_SS_MASK_14_10 = 0xA,	/**< Mask bit(10-14) */
	RTC_ALARM_SS_MASK_14_11 = 0xB,	/**< Mask bit(11-14) */
	RTC_ALARM_SS_MASK_14_12 = 0xC,	/**< Mask bit(12-14) */
	RTC_ALARM_SS_MASK_14_13 = 0xD,	/**< Mask bit(13-14) */
	RTC_ALARM_SS_MASK_14    = 0xE,	/**< Mask bit14 */
	RTC_ALARM_SS_MASK_ALL   = 0x0,	/**< Mask bit(0-14) */
} rtc_sub_second_mask_t;

/**
  * @brief Alarm select week or day */
typedef enum {
	RTC_SELECT_DAY  = 0x0,	/**< Alarm select day */
	RTC_SELECT_WEEK = 0x1,	/**< Alarm select week */
} rtc_week_day_sel_t;

/**
  * @brief Alarm structure
  */
typedef struct {
	rtc_alarm_idx_t idx;		/**< Index of alarm */
	rtc_time_t time;		/**< Time structure */
	uint32_t mask;			/**< Alarm mask */
	rtc_sub_second_mask_t ss_mask;	/**< Alarm sub-second mask */
	rtc_week_day_sel_t sel;		/**< Select week or day */

	union {
		uint8_t week;		/**< Alarm select week */
		uint8_t day;		/**< Alarm select day */
	};
} rtc_alarm_t;

/**
  * @brief Time stamp signel select
  */
typedef enum {
	RTC_TS_SIGNAL_SEL_TAMPER0 = 0,	/**< Select tamper0 */
	RTC_TS_SIGNAL_SEL_TAMPER1 = 1,	/**< Select tamper1 */
} rtc_ts_signal_sel_t;

/**
  * @brief Time stamp trigger style
  */
typedef enum {
	RTC_TS_RISING_EDGE  = 0,	/**< Rising edge */
	RTC_TS_FALLING_EDGE = 1,	/**< Falling edge */
} rtc_ts_trigger_style_t;

/**
  * @brief Index of tamper
  */
typedef enum {
	RTC_TAMPER_0 = 0,	/**< Tamper0 */
	RTC_TAMPER_1 = 1,	/**< Tamper1 */
} rtc_tamper_idx_t;

/**
  * @brief Tamper trigger type
  */
typedef enum {
	RTC_TAMPER_TRIGGER_LOW  = 0,	/**< High trigger */
	RTC_TAMPER_TRIGGER_HIGH = 1,	/**< Low trigger */
} rtc_tamper_trigger_t;

/**
  * @brief Tamper sampling frequency
  */
typedef enum {
	RTC_TAMPER_SAMPLING_FREQ_32768 = 0,	/**< RTCCLK / 32768 */
	RTC_TAMPER_SAMPLING_FREQ_16384 = 1,	/**< RTCCLK / 16384 */
	RTC_TAMPER_SAMPLING_FREQ_8192  = 2,	/**< RTCCLK / 8192 */
	RTC_TAMPER_SAMPLING_FREQ_4096  = 3,	/**< RTCCLK / 4096 */
	RTC_TAMPER_SAMPLING_FREQ_2048  = 4,	/**< RTCCLK / 2048 */
	RTC_TAMPER_SAMPLING_FREQ_1024  = 5,	/**< RTCCLK / 1024 */
	RTC_TAMPER_SAMPLING_FREQ_512   = 6,	/**< RTCCLK / 512 */
	RTC_TAMPER_SAMPLING_FREQ_256   = 7,	/**< RTCCLK / 256 */
} rtc_tamper_sampling_freq_t;

/**
  * @brief Tamper filter time
  */
typedef enum {
	RTC_TAMPER_DURATION_1 = 0,	/**< Duration 1 sampling */
	RTC_TAMPER_DURATION_2 = 1,	/**< Duration 2 sampling */
	RTC_TAMPER_DURATION_4 = 2,	/**< Duration 4 sampling */
	RTC_TAMPER_DURATION_8 = 3,	/**< Duration 8 sampling */
} rtc_tamper_duration_t;

/**
  * @brief Tamper structure
  */
typedef struct {
	rtc_tamper_idx_t idx;			/**< Index of tamper */
	rtc_tamper_trigger_t trig;		/**< Trigger type */
	rtc_tamper_sampling_freq_t freq;	/**< Sampling frequency */
	rtc_tamper_duration_t dur;		/**< Filter time */
	type_func_t ts;				/**< Enable/Disable trigger time stamp event */
} rtc_tamper_t;

/**
  * @brief Wake-up clock
  */
typedef enum {
	RTC_WAKEUP_CLOCK_DIV_16   = 0,	/**< RTCCLK / 16 */
	RTC_WAKEUP_CLOCK_DIV_8    = 1,	/**< RTCCLK / 8 */
	RTC_WAKEUP_CLOCK_DIV_4    = 2,	/**< RTCCLK / 4 */
	RTC_WAKEUP_CLOCK_DIV_2    = 3,	/**< RTCCLK / 2 */
	RTC_WAKEUP_CLOCK_1HZ      = 4,	/**< 1Hz */
	RTC_WAKEUP_CLOCK_1HZ_PULS = 6,	/**< 1Hz and WUT + 65536 */
} rtc_wakeup_clock_t;

/**
  * @brief RTC clock output type
  */
typedef enum {
	RTC_CLOCK_OUTPUT_32768 = 0,	/**< 32768Hz */
	RTC_CLOCK_OUTPUT_1024  = 1,	/**< 1024Hz */
	RTC_CLOCK_OUTPUT_32    = 2,	/**< 32Hz */
	RTC_CLOCK_OUTPUT_1     = 3,	/**< 1Hz */
	RTC_CLOCK_OUTPUT_CAL_1 = 4,	/**< 1Hz after calibration */
	RTC_CLOCK_OUTPUT_EXA_1 = 5,	/**< Exact 1Hz */
} rtc_clock_output_t;

/**
  * @ Calibration frequency
  */
typedef enum {
	RTC_CALI_FREQ_10_SEC = 0,	/**< Calibrate every 10 seconds */
	RTC_CALI_FREQ_20_SEC = 1,	/**< Calibrate every 20 seconds */
	RTC_CALI_FREQ_1_MIN  = 2,	/**< Calibrate every 1 minute */
	RTC_CALI_FREQ_2_MIN  = 3,	/**< Calibrate every 2 minutes */
	RTC_CALI_FREQ_5_MIN  = 4,	/**< Calibrate every 5 minutes */
	RTC_CALI_FREQ_10_MIN = 5,	/**< Calibrate every 10 minutes */
	RTC_CALI_FREQ_20_MIN = 6,	/**< Calibrate every 20 minutes */
	RTC_CALI_FREQ_1_SEC  = 7,	/**< Calibrate every 1 second */
} rtc_cali_freq_t;

/**
  * @brief Temperature compensate type
  */
typedef enum {
	RTC_CALI_TC_NONE          = 0,	/**< Temperature compensate disable */
	RTC_CALI_TC_AUTO_BY_HW    = 1,	/**< Temperature compensate by hardware */
	RTC_CALI_TC_AUTO_BY_SF    = 2,	/**< Temperature compensate by software */
	RTC_CALI_TC_AUTO_BY_HW_SF = 3,	/**< Temperature compensate by hardware, trigger by software */
} rtc_cali_tc_t;

/**
  * @ Calculate frequency
  */
typedef enum {
	RTC_CALI_CALC_FREQ_10_SEC = 0,	/**< Calculate every 10 seconds */
	RTC_CALI_CALC_FREQ_20_SEC = 1,	/**< Calculate every 20 seconds */
	RTC_CALI_CALC_FREQ_1_MIN  = 2,	/**< Calculate every 1 minute */
	RTC_CALI_CALC_FREQ_2_MIN  = 3,	/**< Calculate every 2 minutes */
	RTC_CALI_CALC_FREQ_5_MIN  = 4,	/**< Calculate every 5 minutes */
	RTC_CALI_CALC_FREQ_10_MIN = 5,	/**< Calculate every 10 minutes */
	RTC_CALI_CALC_FREQ_20_MIN = 6,	/**< Calculate every 20 minutes */
	RTC_CALI_CALC_FREQ_1_HOUR = 7,	/**< Calculate every 1 hour */
} rtc_cali_calc_freq_t;

/**
  * @brief Calibration algorithm
  */
typedef enum {
	RTC_CALI_CALC_4 = 0,	/**< 4-polynomial */
	RTC_CALI_CALC_2 = 1,	/**< 2-parabola */
} rtc_cali_calc_t;

/**
  * @brief Calibration structure
  */
typedef struct {
	rtc_cali_freq_t cali_freq;	/**< calibrate frequency */
	rtc_cali_tc_t tc;		/**< Temperature compensate type */
	rtc_cali_calc_freq_t calc_freq;	/**< Calculate frequency */
	rtc_cali_calc_t calc;		/**< algorithm */
	type_func_t acc;		/**< Enable/Disable decimal accumulate */
} rtc_cali_t;

/**
  * @brief Interrupt type
  */
typedef enum {
	RTC_IT_SEC  = (1U << 0),	/**< Second */
	RTC_IT_MIN  = (1U << 1),	/**< Minute */
	RTC_IT_HR   = (1U << 2),	/**< Hour */
	RTC_IT_DAY  = (1U << 3),	/**< Day */
	RTC_IT_MON  = (1U << 4),	/**< Month */
	RTC_IT_YR   = (1U << 5),	/**< Year */
	RTC_IT_ALMA = (1U << 8),	/**< Alarm-A */
	RTC_IT_ALMB = (1U << 9),	/**< Alarm-B */
	RTC_IT_TS   = (1U << 10),	/**< Time stamp */
	RTC_IT_TSOV = (1U << 11),	/**< Time stamp overflow */
	RTC_IT_TP0  = (1U << 12),	/**< Tamper-0 */
	RTC_IT_TP1  = (1U << 13),	/**< Tamper-1 */
	RTC_IT_RSC  = (1U << 16),	/**< Synchronous complete */
	RTC_IT_SFC  = (1U << 17),	/**< Shift complete */
	RTC_IT_WU   = (1U << 18),	/**< Wake-up */
	RTC_IT_TCC  = (1U << 24),	/**< Temperature compensate complete */
	RTC_IT_TCE  = (1U << 25),	/**< Temperature compensate error */
} rtc_it_t;

/**
  * @brief Interrupt flag
  */
typedef enum {
	RTC_IF_SEC  = (1U << 0),	/**< Second */
	RTC_IF_MIN  = (1U << 1),	/**< Minute */
	RTC_IF_HR   = (1U << 2),	/**< Hour */
	RTC_IF_DAY  = (1U << 3),	/**< Day */
	RTC_IF_MON  = (1U << 4),	/**< Month */
	RTC_IF_YR   = (1U << 5),	/**< Year */
	RTC_IF_ALMA = (1U << 8),	/**< Alarm-A */
	RTC_IF_ALMB = (1U << 9),	/**< Alarm-B */
	RTC_IF_TS   = (1U << 10),	/**< Time stamp */
	RTC_IF_TSOV = (1U << 11),	/**< Time stamp overflow */
	RTC_IF_TP0  = (1U << 12),	/**< Tamper-0 */
	RTC_IF_TP1  = (1U << 13),	/**< Tamper-1 */
	RTC_IF_RSC  = (1U << 16),	/**< Synchronous complete */
	RTC_IF_SFC  = (1U << 17),	/**< Shift complete */
	RTC_IF_WU   = (1U << 18),	/**< Wake-up */
	RTC_IF_TCC  = (1U << 24),	/**< Temperature compensate complete */
	RTC_IF_TCE  = (1U << 25),	/**< Temperature compensate error */
} rtc_flag_t;
/**
  * @}
  */

/** @defgroup RTC_Public_Macro RTC Public Macros
  * @{
  */
#define RTC_UNLOCK()		(WRITE_REG(RTC->WPR, 0x55AAAA55))
#define RTC_LOCK()		(WRITE_REG(RTC->WPR, 0x0))
#define RTC_BY_PASS_ENABLE()			\
do {						\
	RTC_UNLOCK();				\
	SET_BIT(RTC->CON, RTC_CON_SHDBP_MSK);	\
	RTC_LOCK();				\
} while (0)
#define RTC_BY_PASS_DISABLE()			\
do {						\
	RTC_UNLOCK();				\
	CLEAR_BIT(RTC->CON, RTC_CON_SHDBP_MSK);	\
	RTC_LOCK();				\
} while (0)
#define RTC_SUMMER_TIME_ENABLE()		\
do {						\
	RTC_UNLOCK();				\
	SET_BIT(RTC->CON, RTC_CON_ADD1H_MSK);	\
	RTC_LOCK();				\
} while (0)
#define RTC_SUMMER_TIME_DISABLE()		\
do {						\
	RTC_UNLOCK();				\
	CLEAR_BIT(RTC->CON, RTC_CON_ADD1H_MSK);	\
	RTC_LOCK();				\
} while (0)
#define RTC_WINTER_TIME_ENABLE()		\
do {						\
	RTC_UNLOCK();				\
	SET_BIT(RTC->CON, RTC_CON_SUB1H_MSK);	\
	RTC_LOCK();				\
} while (0)
#define RTC_WINTER_TIME_DISABLE()		\
do {						\
	RTC_UNLOCK();				\
	CLEAR_BIT(RTC->CON, RTC_CON_SUB1H_MSK);	\
	RTC_LOCK();				\
} while (0)
/**
 * @}
 */

/** @defgroup CAN_Private_Macros CAN Private Macros
  * @{
  */
#define RTC_CALI_UNLOCK()	(WRITE_REG(RTC->CALWPR, 0x699655AA))
#define RTC_CALI_LOCK()		(WRITE_REG(RTC->CALWPR, 0x0))
#define ALARM_MASK_ALL		0x40808080
#define RTC_TIMEOUT_VALUE	100

#define IS_SHIFT_SUB_SS(x)	((x) < (1U << 15))
#define IS_RTC_HOUR_FORMAT(x)	(((x) == RTC_HOUR_FORMAT_24) || \
                                 ((x) == RTC_HOUR_FORMAT_12))
#define IS_RTC_OUTPUT_SEL(x)	(((x) == RTC_OUTPUT_DISABLE) || \
                                 ((x) == RTC_OUTPUT_ALARM_A) || \
                                 ((x) == RTC_OUTPUT_ALARM_B) || \
                                 ((x) == RTC_OUTPUT_WAKEUP))
#define IS_RTC_OUTPUT_POLARITY(x)	(((x) == RTC_OUTPUT_POLARITY_HIGH) || \
                                         ((x) == RTC_OUTPUT_POLARITY_LOW))
#define IS_RTC_SOURCE_SEL(x)	(((x) == RTC_SOURCE_LOSC)        || \
                                 ((x) == RTC_SOURCE_LRC)         || \
                                 ((x) == RTC_SOURCE_HRC_DIV_1M ) || \
                                 ((x) == RTC_SOURCE_HOSC_DIV_1M))
#define IS_RTC_ALARM(x)		(((x) == RTC_ALARM_A) || \
                                 ((x) == RTC_ALARM_B))
#define IS_RTC_ALARM_SEL(x)	(((x) == RTC_SELECT_DAY) || \
                                 ((x) == RTC_SELECT_WEEK))
#define IS_RTC_ALARM_MASK(x)	(((x) == RTC_ALARM_MASK_NONE)     || \
                                 ((x) == RTC_ALARM_MASK_WEEK_DAY) || \
                                 ((x) == RTC_ALARM_MASK_HOUR)     || \
                                 ((x) == RTC_ALARM_MASK_MINUTE)   || \
                                 ((x) == RTC_ALARM_MASK_SECOND)   || \
                                 ((x) == RTC_ALARM_MASK_ALL))
#define IS_RTC_ALARM_SS_MASK(x)	(((x) == RTC_ALARM_SS_MASK_NONE)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_1)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_2)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_3)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_4)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_5)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_6)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_7)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_8)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_9)  || \
                                 ((x) == RTC_ALARM_SS_MASK_14_10) || \
                                 ((x) == RTC_ALARM_SS_MASK_14_11) || \
                                 ((x) == RTC_ALARM_SS_MASK_14_12) || \
                                 ((x) == RTC_ALARM_SS_MASK_14_13) || \
                                 ((x) == RTC_ALARM_SS_MASK_14)    || \
                                 ((x) == RTC_ALARM_SS_MASK_ALL))
#define IS_RTC_TS_SIGNAL(x)	(((x) == RTC_TS_SIGNAL_SEL_TAMPER0) || \
                                 ((x) == RTC_TS_SIGNAL_SEL_TAMPER1))
#define IS_RTC_TS_STYLE(x)	(((x) == RTC_TS_RISING_EDGE) || \
                                 ((x) == RTC_TS_FALLING_EDGE))
#define IS_RTC_FORMAT(x)	(((x) == RTC_FORMAT_DEC) || \
                                 ((x) == RTC_FORMAT_BCD))
#define IS_RTC_TAMPER(x)	(((x) == RTC_TAMPER_0) || \
                                 ((x) == RTC_TAMPER_1))
#define IS_RTC_TAMPER_TRIGGER(x)	(((x) == RTC_TAMPER_TRIGGER_LOW) || \
                                         ((x) == RTC_TAMPER_TRIGGER_HIGH))
#define IS_RTC_TAMPER_SAMPLING_FREQ(x)	(((x) == RTC_TAMPER_SAMPLING_FREQ_32768) || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_16384) || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_8192)  || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_4096)  || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_2048)  || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_1024)  || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_512)   || \
                                         ((x) == RTC_TAMPER_SAMPLING_FREQ_256))
#define IS_RTC_TAMPER_DURATION(x)	(((x) == RTC_TAMPER_DURATION_1) || \
                                         ((x) == RTC_TAMPER_DURATION_2) || \
                                         ((x) == RTC_TAMPER_DURATION_4) || \
                                         ((x) == RTC_TAMPER_DURATION_8))
#define IS_RTC_WAKEUP_CLOCK(x)	(((x) == RTC_WAKEUP_CLOCK_DIV_16) || \
                                 ((x) == RTC_WAKEUP_CLOCK_DIV_8)  || \
                                 ((x) == RTC_WAKEUP_CLOCK_DIV_4)  || \
                                 ((x) == RTC_WAKEUP_CLOCK_DIV_2)  || \
                                 ((x) == RTC_WAKEUP_CLOCK_1HZ)    || \
                                 ((x) == RTC_WAKEUP_CLOCK_1HZ_PULS))
#define IS_RTC_CLOCK_OUTPUT(x)	(((x) == RTC_CLOCK_OUTPUT_32768) || \
                                 ((x) == RTC_CLOCK_OUTPUT_1024)  || \
                                 ((x) == RTC_CLOCK_OUTPUT_32)    || \
                                 ((x) == RTC_CLOCK_OUTPUT_1)     || \
                                 ((x) == RTC_CLOCK_OUTPUT_CAL_1) || \
                                 ((x) == RTC_CLOCK_OUTPUT_EXA_1))
#define IS_RTC_CALI_FREQ(x)	(((x) == RTC_CALI_FREQ_10_SEC) || \
                                 ((x) == RTC_CALI_FREQ_20_SEC) || \
                                 ((x) == RTC_CALI_FREQ_1_MIN)  || \
                                 ((x) == RTC_CALI_FREQ_2_MIN)  || \
                                 ((x) == RTC_CALI_FREQ_5_MIN)  || \
                                 ((x) == RTC_CALI_FREQ_10_MIN) || \
                                 ((x) == RTC_CALI_FREQ_20_MIN) || \
                                 ((x) == RTC_CALI_FREQ_1_SEC))
#define IS_RTC_CALI_TC(x)	(((x) == RTC_CALI_TC_NONE)       || \
                                 ((x) == RTC_CALI_TC_AUTO_BY_HW) || \
                                 ((x) == RTC_CALI_TC_AUTO_BY_SF) || \
                                 ((x) == RTC_CALI_TC_AUTO_BY_HW_SF))
#define IS_RTC_CALC_FREQ(x)	(((x) == RTC_CALI_CALC_FREQ_10_SEC) || \
                                 ((x) == RTC_CALI_CALC_FREQ_20_SEC) || \
                                 ((x) == RTC_CALI_CALC_FREQ_1_MIN)  || \
                                 ((x) == RTC_CALI_CALC_FREQ_2_MIN)  || \
                                 ((x) == RTC_CALI_CALC_FREQ_5_MIN)  || \
                                 ((x) == RTC_CALI_CALC_FREQ_10_MIN) || \
                                 ((x) == RTC_CALI_CALC_FREQ_20_MIN) || \
                                 ((x) == RTC_CALI_CALC_FREQ_1_HOUR))
#define IS_RTC_CALI_CALC(x)	(((x) == RTC_CALI_CALC_4) || \
                                 ((x) == RTC_CALI_CALC_2))
#define IS_RTC_IT(x)		(((x) == RTC_IT_SEC)  || \
                                 ((x) == RTC_IT_MIN)  || \
                                 ((x) == RTC_IT_HR)   || \
                                 ((x) == RTC_IT_DAY)  || \
                                 ((x) == RTC_IT_MON)  || \
                                 ((x) == RTC_IT_YR)   || \
                                 ((x) == RTC_IT_ALMA) || \
                                 ((x) == RTC_IT_ALMB) || \
                                 ((x) == RTC_IT_TS)   || \
                                 ((x) == RTC_IT_TSOV) || \
                                 ((x) == RTC_IT_TP0)  || \
                                 ((x) == RTC_IT_TP1)  || \
                                 ((x) == RTC_IT_RSC)  || \
                                 ((x) == RTC_IT_SFC)  || \
                                 ((x) == RTC_IT_WU)   || \
                                 ((x) == RTC_IT_TCC)  || \
                                 ((x) == RTC_IT_TCE))
#define IS_RTC_IF(x)		(((x) == RTC_IF_SEC)  || \
                                 ((x) == RTC_IF_MIN)  || \
                                 ((x) == RTC_IF_HR)   || \
                                 ((x) == RTC_IF_DAY)  || \
                                 ((x) == RTC_IF_MON)  || \
                                 ((x) == RTC_IF_YR)   || \
                                 ((x) == RTC_IF_ALMA) || \
                                 ((x) == RTC_IF_ALMB) || \
                                 ((x) == RTC_IF_TS)   || \
                                 ((x) == RTC_IF_TSOV) || \
                                 ((x) == RTC_IF_TP0)  || \
                                 ((x) == RTC_IF_TP1)  || \
                                 ((x) == RTC_IF_RSC)  || \
                                 ((x) == RTC_IF_SFC)  || \
                                 ((x) == RTC_IF_WU)   || \
                                 ((x) == RTC_IF_TCC)  || \
                                 ((x) == RTC_IF_TCE))
#define IS_RTC_SECOND(x)	((x) < 60)
#define IS_RTC_MINUTE(x)	((x) < 60)
#define IS_RTC_HOUR(x)		((x) < 24)
#define IS_RTC_DAY(x)		(((x) > 0) && ((x) < 32))
#define IS_RTC_MONTH(x)		(((x) > 0) && ((x) < 13))
#define IS_RTC_YEAR(x)		((x) < 100)
/**
  * @}
  */

/** @addtogroup RTC_Public_Functions
  * @{
  */

/** @addtogroup RTC_Public_Functions_Group1
  *  @{
  */
/* Initialization functions */
void ald_rtc_reset(void);
void ald_rtc_init(rtc_init_t *init);
void ald_rtc_source_select(rtc_source_sel_t sel);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group2
  * @{
  */
/* Time and date operation functions */
ald_status_t ald_rtc_set_time(rtc_time_t *time, rtc_format_t format);
ald_status_t ald_rtc_set_date(rtc_date_t *date, rtc_format_t format);
void ald_rtc_get_time(rtc_time_t *time, rtc_format_t format);
void ald_rtc_get_date(rtc_date_t *date, rtc_format_t format);
int32_t ald_rtc_get_date_time(rtc_date_t *date, rtc_time_t *time, rtc_format_t format);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group3
  * @{
  */
/* Alarm functions */
void ald_rtc_set_alarm(rtc_alarm_t *alarm, rtc_format_t format);
void ald_rtc_get_alarm(rtc_alarm_t *alarm, rtc_format_t format);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group4
  * @{
  */
/* Time stamp functions */
void ald_rtc_set_time_stamp(rtc_ts_signal_sel_t sel, rtc_ts_trigger_style_t style);
void ald_rtc_cancel_time_stamp(void);
void ald_rtc_get_time_stamp(rtc_time_t *ts_time, rtc_date_t *ts_date, rtc_format_t format);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group5
  * @{
  */
/* Tamper functions */
void ald_rtc_set_tamper(rtc_tamper_t *tamper);
void ald_rtc_cancel_tamper(rtc_tamper_idx_t idx);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group6
  * @{
  */
/* Wakeup functions */
void ald_rtc_set_wakeup(rtc_wakeup_clock_t clock, uint16_t value);
void ald_rtc_cancel_wakeup(void);
uint16_t ald_rtc_get_wakeup_timer_value(void);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group7
  * @{
  */
/* Clock output functions */
ald_status_t ald_rtc_set_clock_output(rtc_clock_output_t clock);
void ald_rtc_cancel_clock_output(void);
/**
  * @}
  */
/** @addtogroup RTC_Public_Functions_Group8
  * @{
  */
/* Control functions */
void ald_rtc_interrupt_config(rtc_it_t it, type_func_t state);
void ald_rtc_alarm_cmd(rtc_alarm_idx_t idx, type_func_t state);
ald_status_t ald_rtc_set_shift(type_func_t add_1s, uint16_t sub_ss);
void ald_rtc_set_cali(rtc_cali_t *config);
void ald_rtc_cancel_cali(void);
ald_status_t ald_rtc_get_cali_status(void);
void ald_rtc_write_temp(uint16_t temp);
it_status_t ald_rtc_get_it_status(rtc_it_t it);
flag_status_t ald_rtc_get_flag_status(rtc_flag_t flag);
void ald_rtc_clear_flag_status(rtc_flag_t flag);
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif
