/*
 * @brief Real Time Clock registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __RTC_001_H_
#define __RTC_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_RTC_001 IP: RTC register block and driver
 * @ingroup IP_Drivers
 * Real Time Clock
 * @{
 */

/**
 * @brief RTC time type option
 */
typedef enum {
	RTC_TIMETYPE_SECOND,		/*!< Second */
	RTC_TIMETYPE_MINUTE,		/*!< Month */
	RTC_TIMETYPE_HOUR,			/*!< Hour */
	RTC_TIMETYPE_DAYOFMONTH,	/*!< Day of month */
	RTC_TIMETYPE_DAYOFWEEK,		/*!< Day of week */
	RTC_TIMETYPE_DAYOFYEAR,		/*!< Day of year */
	RTC_TIMETYPE_MONTH,			/*!< Month */
	RTC_TIMETYPE_YEAR,			/*!< Year */
	RTC_TIMETYPE_LAST
} IP_RTC_TIMEINDEX_T;

/**
 * @brief Real Time Clock register block structure
 */
typedef struct {							/*!< RTC Structure          */
	__O  uint32_t  ILR;						/*!< Interrupt Location Register */
	__I  uint32_t  RESERVED0;
	__IO uint32_t  CCR;						/*!< Clock Control Register */
	__IO uint32_t  CIIR;					/*!< Counter Increment Interrupt Register */
	__IO uint32_t  AMR;						/*!< Alarm Mask Register    */
	__I  uint32_t  CTIME[3];				/*!< Consolidated Time Register 0,1,2 */
	__IO uint32_t  TIME[RTC_TIMETYPE_LAST];	/*!< Timer field registers */
	__IO uint32_t  CALIBRATION;				/*!< Calibration Value Register */
#if defined(CHIP_LPC177X_8X)
	__IO uint32_t GPREG[5];					/*!< General Purpose Storage Registers */
	__IO uint32_t RTC_AUXEN;				/*!< */
	__IO uint32_t RTC_AUX;					/*!< */
#else
	__I  uint32_t  RESERVED1[7];
#endif
	__IO uint32_t  ALRM[RTC_TIMETYPE_LAST];	/*!< Alarm field registers */
#if defined(CHIP_LPC177X_8X)
	__IO uint32_t ERSTATUS;
#endif
} IP_RTC_001_T;

/**
 * @brief ILR register definitions
 */
/** ILR register mask */
#define RTC_ILR_BITMASK         ((0x00000003))
/** Bit inform the source interrupt is counter increment*/
#define RTC_IRL_RTCCIF          ((1 << 0))
/** Bit inform the source interrupt is alarm match*/
#define RTC_IRL_RTCALF          ((1 << 1))

/**
 * @brief CCR register definitions
 */
/** CCR register mask */
#define RTC_CCR_BITMASK         ((0x00000013))
/** Clock enable */
#define RTC_CCR_CLKEN           ((1 << 0))
/** Clock reset */
#define RTC_CCR_CTCRST          ((1 << 1))
/** Calibration counter enable */
#define RTC_CCR_CCALEN          ((1 << 4))

/**
 * @brief CIIR and AMR register definitions
 */
/** Counter Increment Interrupt bit for second */
#define RTC_AMR_CIIR_IMSEC          ((1 << 0))
/** Counter Increment Interrupt bit for minute */
#define RTC_AMR_CIIR_IMMIN          ((1 << 1))
/** Counter Increment Interrupt bit for hour */
#define RTC_AMR_CIIR_IMHOUR         ((1 << 2))
/** Counter Increment Interrupt bit for day of month */
#define RTC_AMR_CIIR_IMDOM          ((1 << 3))
/** Counter Increment Interrupt bit for day of week */
#define RTC_AMR_CIIR_IMDOW          ((1 << 4))
/** Counter Increment Interrupt bit for day of year */
#define RTC_AMR_CIIR_IMDOY          ((1 << 5))
/** Counter Increment Interrupt bit for month */
#define RTC_AMR_CIIR_IMMON          ((1 << 6))
/** Counter Increment Interrupt bit for year */
#define RTC_AMR_CIIR_IMYEAR         ((1 << 7))
/** CIIR bit mask */
#define RTC_AMR_CIIR_BITMASK        ((0xFF))

/**
 * @brief RTC_AUX register definitions
 */
/** RTC Oscillator Fail detect flag */
#define RTC_AUX_RTC_OSCF        ((1 << 4))

/**
 * @brief RTC_AUXEN register definitions
 */
/** Oscillator Fail Detect interrupt enable*/
#define RTC_AUXEN_RTC_OSCFEN    ((1 << 4))

/**
 * @brief Consolidated Time Register 0 definitions
 */
#define RTC_CTIME0_SECONDS_MASK     ((0x3F))
#define RTC_CTIME0_MINUTES_MASK     ((0x3F00))
#define RTC_CTIME0_HOURS_MASK       ((0x1F0000))
#define RTC_CTIME0_DOW_MASK         ((0x7000000))

/**
 * @brief Consolidated Time Register 1 definitions
 */
#define RTC_CTIME1_DOM_MASK         ((0x1F))
#define RTC_CTIME1_MONTH_MASK       ((0xF00))
#define RTC_CTIME1_YEAR_MASK        ((0xFFF0000))

/**
 * @brief Consolidated Time Register 2 definitions
 */
#define RTC_CTIME2_DOY_MASK         ((0xFFF))

/**
 * @brief Time Counter Group and Alarm register group
 */
/** SEC register mask */
#define RTC_SEC_MASK            (0x0000003F)
/** MIN register mask */
#define RTC_MIN_MASK            (0x0000003F)
/** HOUR register mask */
#define RTC_HOUR_MASK           (0x0000001F)
/** DOM register mask */
#define RTC_DOM_MASK            (0x0000001F)
/** DOW register mask */
#define RTC_DOW_MASK            (0x00000007)
/** DOY register mask */
#define RTC_DOY_MASK            (0x000001FF)
/** MONTH register mask */
#define RTC_MONTH_MASK          (0x0000000F)
/** YEAR register mask */
#define RTC_YEAR_MASK           (0x00000FFF)

#define RTC_SECOND_MAX      59	/*!< Maximum value of second */
#define RTC_MINUTE_MAX      59	/*!< Maximum value of minute*/
#define RTC_HOUR_MAX        23	/*!< Maximum value of hour*/
#define RTC_MONTH_MIN       1	/*!< Minimum value of month*/
#define RTC_MONTH_MAX       12	/*!< Maximum value of month*/
#define RTC_DAYOFMONTH_MIN  1	/*!< Minimum value of day of month*/
#define RTC_DAYOFMONTH_MAX  31	/*!< Maximum value of day of month*/
#define RTC_DAYOFWEEK_MAX   6	/*!< Maximum value of day of week*/
#define RTC_DAYOFYEAR_MIN   1	/*!< Minimum value of day of year*/
#define RTC_DAYOFYEAR_MAX   366	/*!< Maximum value of day of year*/
#define RTC_YEAR_MAX        4095/*!< Maximum value of year*/

/**
 * @brief Calibration register
 */
/** Calibration value */
#define RTC_CALIBRATION_CALVAL_MASK     ((0x1FFFF))
/** Calibration direction */
#define RTC_CALIBRATION_LIBDIR          ((1 << 17))
/** Calibration max value */
#define RTC_CALIBRATION_MAX             ((0x20000))
/** Calibration definitions */
#define RTC_CALIB_DIR_FORWARD           ((uint8_t) (0))
#define RTC_CALIB_DIR_BACKWARD          ((uint8_t) (1))

/* Check Parameter Definitions */
/** Macro to determine if it is valid RTC peripheral */
#define PARAM_pRTC(x)   (((uint32_t *) x) == ((uint32_t *) LPC_RTC))

/* Macro check RTC interrupt type */
#define PARAM_RTC_INT(n)    ((n == RTC_INT_COUNTER_INCREASE) || (n == RTC_INT_ALARM))

/* Macro check RTC calibration type */
#define PARAM_RTC_CALIB_DIR(n)  ((n == RTC_CALIB_DIR_FORWARD) || (n == RTC_CALIB_DIR_BACKWARD))

/**
 * @brief RTC enumeration
 */

/** @brief RTC interrupt source */
typedef enum {
	RTC_INT_COUNTER_INCREASE = RTC_IRL_RTCCIF,	/*!<  Counter Increment Interrupt */
	RTC_INT_ALARM = RTC_IRL_RTCALF				/*!< The alarm interrupt */
} IP_RTC_INT_OPT;

typedef struct {
	uint32_t time[RTC_TIMETYPE_LAST];
} IP_RTC_TIME_T;

/**
 * @brief	Initialize the RTC peripheral
 * @param	pRTC	: pointer to RTC peripheral block
 * @return	None
 */
void IP_RTC_Init(IP_RTC_001_T *pRTC);

/**
 * @brief	De-initialize the RTC peripheral
 * @param	pRTC	: pointer to RTC peripheral block
 * @return	None
 */
STATIC INLINE void IP_RTC_DeInit(IP_RTC_001_T *pRTC)
{
	pRTC->CCR = 0x00;
}

/**
 * @brief	Reset clock tick counter in the RTC peripheral
 * @param	pRTC	: pointer to RTC peripheral block
 * @return	None
 */
void IP_RTC_ResetClockTickCounter(IP_RTC_001_T *pRTC);

/**
 * @brief	Start/Stop RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	NewState	:  ENABLE or DISABLE
 * @return	None
 */
void IP_RTC_Enable(IP_RTC_001_T *pRTC, FunctionalState NewState);

/**
 * @brief	Enable/Disable Counter increment interrupt for a time type in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	cntrMask	: Or'ed bit values for time types (RTC_AMR_CIIR_IM*)
 * @param	NewState		: ENABLE or DISABLE
 * @return	None
 */
void IP_RTC_CntIncrIntConfig(IP_RTC_001_T *pRTC, uint32_t cntrMask, FunctionalState NewState);

/**
 * @brief	Enable/Disable Alarm interrupt for a time type in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	alarmMask	: Or'ed bit values for ALARM types (RTC_AMR_CIIR_IM*)
 * @param	NewState		: ENABLE or DISABLE
 * @return	None
 */
void IP_RTC_AlarmIntConfig(IP_RTC_001_T *pRTC, uint32_t alarmMask, FunctionalState NewState);

/**
 * @brief	Set current time value for a time type in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	Timetype	: time field index type to set
 * @param	TimeValue	: Value to palce in time field
 * @return	None
 */
void IP_RTC_SetTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype, uint32_t TimeValue);

/**
 * @brief	Get current time value for a type time type
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	Timetype	: Time field index type to get
 * @return	Value of time field according to specified time type
 */
uint32_t IP_RTC_GetTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype);

/**
 * @brief	Set full time in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	pFullTime	: Pointer to full time data
 * @return	None
 */
void IP_RTC_SetFullTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime);

/**
 * @brief	Get full time from the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	pFullTime	: Pointer to full time record to fill
 * @return	None
 */
void IP_RTC_GetFullTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime);

/**
 * @brief	Set alarm time value for a time type
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	Timetype	: Time index field to set
 * @param	ALValue		: Alarm time value to set
 * @return	None
 */
void IP_RTC_SetAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype, uint32_t ALValue);

/**
 * @brief	Get alarm time value for a time type
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	Timetype	: Time index field to get
 * @return	Value of Alarm time according to specified time type
 */
uint32_t IP_RTC_GetAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype);

/**
 * @brief	Set full alarm time in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	pFullTime	: Pointer to full time record to set alarm
 * @return	None
 */
void IP_RTC_SetFullAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime);

/**
 * @brief	Get full alarm time in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	pFullTime	: Pointer to full time record to fill
 * @return	None
 */
void IP_RTC_GetFullAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime);

/**
 * @brief	Enable/Disable calibration counter in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	NewState	: New State of this function, should be:
 *							- ENABLE	:The calibration counter is enabled and counting
 *							- DISABLE	:The calibration counter is disabled and reset to zero
 * @return		None
 */
void IP_RTC_CalibCounterCmd(IP_RTC_001_T *pRTC, FunctionalState NewState);

/**
 * @brief	Configures Calibration in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	CalibValue	: Calibration value, should be in range from 0 to 131,072
 * @param	CalibDir : Calibration Direction, should be:
 *						- RTC_CALIB_DIR_FORWARD		:Forward calibration
 *						- RTC_CALIB_DIR_BACKWARD	:Backward calibration
 * @return	None
 */
void IP_RTC_CalibConfig(IP_RTC_001_T *pRTC, uint32_t CalibValue, uint8_t CalibDir);

/**
 * @brief	Clear specified Location interrupt pending in the RTC peripheral
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	IntType	: Interrupt location type, should be:
 *						- RTC_INT_COUNTER_INCREASE	:Clear Counter Increment Interrupt pending.
 *						- RTC_INT_ALARM				:Clear alarm interrupt pending
 * @return	None
 */
STATIC INLINE void IP_RTC_ClearIntPending(IP_RTC_001_T *pRTC, uint32_t IntType)
{
	pRTC->ILR = IntType;
}

/**
 * @brief	Check whether if specified location interrupt in the
 *              RTC peripheral is set or not
 * @param	pRTC		: pointer to RTC peripheral block
 * @param	IntType	: Interrupt location type, should be:
 *						- RTC_INT_COUNTER_INCREASE: Counter Increment Interrupt block generated an interrupt.
 *						- RTC_INT_ALARM: Alarm generated an interrupt.
 * @return	Current state of specified interrupt in RTC peripheral, SET or RESET
 */
STATIC INLINE IntStatus IP_RTC_GetIntPending(IP_RTC_001_T *pRTC, uint32_t IntType)
{
	return (pRTC->ILR & IntType) ? SET : RESET;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_001_H_ */
