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

#include "rtc_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize the the RTC peripheral */
void IP_RTC_Init(IP_RTC_001_T *pRTC)
{
	do {
		/* Reset RTC clock*/
		pRTC->CCR = RTC_CCR_CTCRST | RTC_CCR_CCALEN;
	} while (pRTC->CCR != (RTC_CCR_CTCRST | RTC_CCR_CCALEN));
	do {
		/* Finish resetting RTC clock */
		pRTC->CCR = RTC_CCR_CCALEN;
	} while (pRTC->CCR != RTC_CCR_CCALEN);

	/* Clear counter increment and alarm interrupt */
	pRTC->ILR = RTC_IRL_RTCCIF | RTC_IRL_RTCALF;
	while (pRTC->ILR != 0) {}

	/* Clear all register to be default */
	pRTC->CIIR = 0x00;
	pRTC->AMR = 0xFF;
	pRTC->CALIBRATION = 0x00;
}

/* Reset clock tick counter in the RTC peripheral */
void IP_RTC_ResetClockTickCounter(IP_RTC_001_T *pRTC)
{
	pRTC->CCR |= RTC_CCR_CTCRST;
	pRTC->CCR &= (~RTC_CCR_CTCRST) & RTC_CCR_BITMASK;
}

/* Start/Stop RTC peripheral */
void IP_RTC_Enable(IP_RTC_001_T *pRTC, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		do {
			pRTC->CCR |= RTC_CCR_CLKEN;
		} while ((pRTC->CCR & RTC_CCR_CLKEN) == 0);
	}
	else {
		pRTC->CCR &= (~RTC_CCR_CLKEN) & RTC_CCR_BITMASK;
	}
}

/* Enable/Disable Counter increment interrupt for a time type in the RTC peripheral */
void IP_RTC_CntIncrIntConfig(IP_RTC_001_T *pRTC, uint32_t cntrMask,
							 FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pRTC->CIIR |= cntrMask;
	}

	else {
		pRTC->CIIR &= (~cntrMask) & RTC_AMR_CIIR_BITMASK;
		while (pRTC->CIIR & cntrMask) {}
	}

}

/* Enable/Disable Alarm interrupt for a time type in the RTC peripheral */
void IP_RTC_AlarmIntConfig(IP_RTC_001_T *pRTC, uint32_t alarmMask,
						   FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pRTC->AMR &= (~alarmMask) & RTC_AMR_CIIR_BITMASK;
	}
	else {
		pRTC->AMR |= (alarmMask);
		while ((pRTC->AMR & alarmMask) == 0) {}
	}
}

/* Set current time value for a time type in the RTC peripheral */
void IP_RTC_SetTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype, uint32_t TimeValue)
{
	pRTC->TIME[Timetype] = TimeValue;
}

/* Get current time value for a type time type */
uint32_t IP_RTC_GetTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype)
{
	return pRTC->TIME[Timetype];
}

/* Set full time in the RTC peripheral */
void IP_RTC_SetFullTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_TIMEINDEX_T i;
	uint32_t secs = 0xFF;

	/* Write time to registers and verify second tick didn't update during the
	   write cycle. If it did, the time may not be consistent across all fields,
	   so write the time again */
	while (secs != pRTC->TIME[RTC_TIMETYPE_SECOND]) {
		/* Write seconds first */
		for (i = RTC_TIMETYPE_SECOND; i < RTC_TIMETYPE_LAST; i++) {
			pRTC->TIME[i] = pFullTime->time[i];
		}

		secs = pRTC->TIME[RTC_TIMETYPE_SECOND];
	}
}

/* Get full time from the RTC peripheral */
void IP_RTC_GetFullTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_TIMEINDEX_T i;
	uint32_t secs = 0xFF;

	/* Read full time, but verify second tick didn't change during the read. If
	   it did, re-read the time again so it will be consistent across all fields. */
	while (secs != pRTC->TIME[RTC_TIMETYPE_SECOND]) {
		secs = pFullTime->time[RTC_TIMETYPE_SECOND] = pRTC->TIME[RTC_TIMETYPE_SECOND];
		for (i = RTC_TIMETYPE_MINUTE; i < RTC_TIMETYPE_LAST; i++) {
			pFullTime->time[i] = pRTC->TIME[i];
		}
	}
}

/* Set alarm time value for a time type */
void IP_RTC_SetAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype, uint32_t ALValue)
{
	pRTC->ALRM[Timetype] = ALValue;
}

/* Get alarm time value for a time */
uint32_t IP_RTC_GetAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIMEINDEX_T Timetype)
{
	return pRTC->ALRM[Timetype];
}

/* Set full alarm time in the RTC peripheral */
void IP_RTC_SetFullAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_TIMEINDEX_T i;

	for (i = RTC_TIMETYPE_SECOND; i < RTC_TIMETYPE_LAST; i++) {
		pRTC->ALRM[i] = pFullTime->time[i];
	}
}

/* Get full alarm time in the RTC peripheral */
void IP_RTC_GetFullAlarmTime(IP_RTC_001_T *pRTC, IP_RTC_TIME_T *pFullTime)
{
	IP_RTC_TIMEINDEX_T i;

	for (i = RTC_TIMETYPE_SECOND; i < RTC_TIMETYPE_LAST; i++) {
		pFullTime->time[i] = pRTC->ALRM[i];
	}
}

/* Enable/Disable calibration counter in the RTC peripheral */
void IP_RTC_CalibCounterCmd(IP_RTC_001_T *pRTC, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		do {
			pRTC->CCR &= (~RTC_CCR_CCALEN) & RTC_CCR_BITMASK;
		} while (pRTC->CCR & RTC_CCR_CCALEN);
	}
	else {
		pRTC->CCR |= RTC_CCR_CCALEN;
	}
}

/* Configures Calibration in the RTC peripheral */
void IP_RTC_CalibConfig(IP_RTC_001_T *pRTC, uint32_t CalibValue, uint8_t CalibDir)
{
	pRTC->CALIBRATION = ((CalibValue - 1) & RTC_CALIBRATION_CALVAL_MASK)
						| ((CalibDir == RTC_CALIB_DIR_BACKWARD) ? RTC_CALIBRATION_LIBDIR : 0);
}
