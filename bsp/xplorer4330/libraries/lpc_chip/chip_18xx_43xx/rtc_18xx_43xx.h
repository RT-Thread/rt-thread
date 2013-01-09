/*
 * @brief LPC18xx/43xx RTC driver
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

#ifndef __RTC_18XX_43XX_H_
#define __RTC_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup RTC_18XX_43XX CHIP: LPC18xx/43xx RTC driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Initialize the RTC peripheral
 * @return	None
 */
void Chip_RTC_Init(void);

/**
 * @brief	De-initialize the RTC peripheral
 * @return	None
 */
STATIC INLINE void Chip_RTC_DeInit(void)
{
	IP_RTC_DeInit(LPC_RTC);
}

/**
 * @brief	Reset clock tick counter in the RTC peripheral
 * @return	None
 */
STATIC INLINE void Chip_RTC_ResetClockTickCounter(void)
{
	IP_RTC_ResetClockTickCounter(LPC_RTC);
}

/**
 * @brief	Start/Stop RTC peripheral
 * @param	NewState	: New State of this function, should be:
 *							- ENABLE	:The time counters are enabled
 *							- DISABLE	:The time counters are disabled
 * @return	None
 */
STATIC INLINE void Chip_RTC_Enable(FunctionalState NewState)
{
	IP_RTC_Enable(LPC_RTC, NewState);
}

/**
 * @brief	Enable/Disable Counter increment interrupt for a time type
 *			in the RTC peripheral
 * @param	cntrMask	: Or'ed bit values for time types (RTC_AMR_CIIR_IM*)
 * @param	NewState	: ENABLE or DISABLE
 * @return	None
 */
STATIC INLINE void Chip_RTC_CntIncrIntConfig(uint32_t cntrMask, FunctionalState NewState)
{
	IP_RTC_CntIncrIntConfig(LPC_RTC, cntrMask, NewState);
}

/**
 * @brief	Enable/Disable Alarm interrupt for a time type
 *			in the RTC peripheral
 * @param	alarmMask	: Or'ed bit values for ALARM types (RTC_AMR_CIIR_IM*)
 * @param	NewState	: ENABLE or DISABLE
 * @return	None
 */
STATIC INLINE void Chip_RTC_AlarmIntConfig(uint32_t alarmMask, FunctionalState NewState)
{
	IP_RTC_AlarmIntConfig(LPC_RTC, alarmMask, NewState);
}

/**
 * @brief		Set current time value for a time type in the RTC peripheral
 * @param		Timetype	: time field index type to set
 * @param		TimeValue	: Value to palce in time field
 * @return		None
 */
STATIC INLINE void Chip_RTC_SetTime(IP_RTC_TIMEINDEX_T Timetype, uint32_t TimeValue)
{
	IP_RTC_SetTime(LPC_RTC, Timetype, TimeValue);
}

/**
 * @brief	Get current time value for a type time type
 * @param	Timetype	: Time field index type to get
 * @return	Value of time field according to specified time type
 */
STATIC INLINE uint32_t Chip_RTC_GetTime(IP_RTC_TIMEINDEX_T Timetype)
{
	return IP_RTC_GetTime(LPC_RTC, Timetype);
}

/**
 * @brief	Set full time in the RTC peripheral
 * @param	pFullTime	: Pointer to full time data
 * @return	None
 */
STATIC INLINE void Chip_RTC_SetFullTime(IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_SetFullTime(LPC_RTC, pFullTime);
}

/**
 * @brief	Get full time from the RTC peripheral
 * @param	pFullTime	: Pointer to full time record to fill
 * @return	None
 */
STATIC INLINE void Chip_RTC_GetFullTime(IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_GetFullTime(LPC_RTC, pFullTime);
}

/**
 * @brief	Set alarm time value for a time type
 * @param	Timetype	: Time index field to set
 * @param	ALValue		: Alarm time value to set
 * @return	None
 */
STATIC INLINE void Chip_RTC_SetAlarmTime(IP_RTC_TIMEINDEX_T Timetype, uint32_t ALValue)
{
	IP_RTC_SetAlarmTime(LPC_RTC, Timetype, ALValue);
}

/**
 * @brief	Get alarm time value for a time type
 * @param	Timetype	: Time index field to get
 * @return	Value of Alarm time according to specified time type
 */
STATIC INLINE uint32_t Chip_RTC_GetAlarmTime(IP_RTC_TIMEINDEX_T Timetype)
{
	return IP_RTC_GetAlarmTime(LPC_RTC, Timetype);
}

/**
 * @brief	Set full alarm time in the RTC peripheral
 * @param	pFullTime	: Pointer to full time record to set alarm
 * @return	None
 */
STATIC INLINE void Chip_RTC_SetFullAlarmTime(IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_SetFullAlarmTime(LPC_RTC, pFullTime);
}

/**
 * @brief	Get full alarm time in the RTC peripheral
 * @param	pFullTime	: Pointer to full time record to fill
 * @return	None
 */
STATIC INLINE void Chip_RTC_GetFullAlarmTime(IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_GetFullAlarmTime(LPC_RTC, pFullTime);
}

/**
 * @brief	Write value to General purpose registers
 * @param	index	: General purpose register index
 * @param	Value	: Value to write
 * @return	None
 * Note: These General purpose registers can be used to store important

 * information when the main power supply is off. The value in these

 * registers is not affected by chip reset. These registers are

 * powered in the RTC power domain.
 */
STATIC INLINE void Chip_REGFILE_Write(uint8_t index, uint32_t Value)
{
	IP_REGFILE_Write(LPC_REGFILE, index, Value);
}

/**
 * @brief	Read value from General purpose registers
 * @param	index	: General purpose register index
 * @return	Read Value
 * These General purpose registers can be used to store important

 * information when the main power supply is off. The value in these

 * registers is not affected by chip reset. These registers are

 * powered in the RTC power domain.
 */
STATIC INLINE uint32_t Chip_REGFILE_Read(uint8_t index)
{
	return IP_REGFILE_Read(LPC_REGFILE, index);
}

/**
 * @brief	Enable/Disable calibration counter in the RTC peripheral
 * @param	NewState	: New State of this function, should be:
 *							- ENABLE	:The calibration counter is enabled and counting
 *							- DISABLE	:The calibration counter is disabled and reset to zero
 * @return	None
 */
STATIC INLINE void Chip_RTC_CalibCounterCmd(FunctionalState NewState)
{
	IP_RTC_CalibCounterCmd(LPC_RTC, NewState);
}

/**
 * @brief	Configures Calibration in the RTC peripheral
 * @param	CalibValue	: Calibration value, should be in range from 0 to 131,072
 * @param	CalibDir	: Calibration Direction, should be:
 *							- RTC_CALIB_DIR_FORWARD		:Forward calibration
 *							- RTC_CALIB_DIR_BACKWARD	:Backward calibration
 * @return	None
 */
STATIC INLINE void Chip_RTC_CalibConfig(uint32_t CalibValue, uint8_t CalibDir)
{
	IP_RTC_CalibConfig(LPC_RTC, CalibValue, CalibDir);
}

/**
 * @brief	Clear specified Location interrupt pending in the RTC peripheral
 * @param	IntType	: Interrupt location type, should be:
 *						- RTC_INT_COUNTER_INCREASE	:Clear Counter Increment Interrupt pending.
 *						- RTC_INT_ALARM				:Clear alarm interrupt pending
 * @return	None
 */
STATIC INLINE void Chip_RTC_ClearIntPending(uint32_t IntType)
{
	IP_RTC_ClearIntPending(LPC_RTC, IntType);
}

/**
 * @brief	Check whether if specified location interrupt in the
 *              RTC peripheral is set or not
 * @param	IntType	: Interrupt location type, should be:
 *						- RTC_INT_COUNTER_INCREASE: Counter Increment Interrupt block generated an interrupt.
 *						- RTC_INT_ALARM: Alarm generated an interrupt.
 * @return	New state of specified Location interrupt in RTC peripheral, SET OR RESET
 */
STATIC INLINE IntStatus Chip_RTC_GetIntPending(uint32_t IntType)
{
	return IP_RTC_GetIntPending(LPC_RTC, IntType);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_18XX_43XX_H_ */
