/*""FILE COMMENT""*******************************************************
* System Name	: Real-time clock API for RX62Nxx
* File Name		: r_pdl_rtc.h
* Version		: 1.02
* Contents		: RTC function prototypes
* Customer		:
* Model			:
* Order			:
* CPU			: RX
* Compiler		: RXC
* OS			:
* Programmer	:
* Note			:
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FILE COMMENT END""**************************************************/

#ifndef R_PDL_RTC_H
#define R_PDL_RTC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_RTC_Create(
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	void *,
	uint8_t,
	void *,
	uint8_t
);
bool R_RTC_Control(
	uint32_t,
	uint16_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t
);
bool R_RTC_Read(
	uint8_t *,
	uint32_t *,
	uint32_t *
);

/* Alarm control */
#define PDL_RTC_ALARM_HOUR_DISABLE		0x00000001ul
#define PDL_RTC_ALARM_HOUR_ENABLE		0x00000002ul
#define PDL_RTC_ALARM_MINUTE_DISABLE	0x00000004ul
#define PDL_RTC_ALARM_MINUTE_ENABLE		0x00000008ul
#define PDL_RTC_ALARM_SECOND_DISABLE	0x00000010ul
#define PDL_RTC_ALARM_SECOND_ENABLE		0x00000020ul
#define PDL_RTC_ALARM_YEAR_DISABLE		0x00000040ul
#define PDL_RTC_ALARM_YEAR_ENABLE		0x00000080ul
#define PDL_RTC_ALARM_MONTH_DISABLE		0x00000100ul
#define PDL_RTC_ALARM_MONTH_ENABLE		0x00000200ul
#define PDL_RTC_ALARM_DAY_DISABLE		0x00000400ul
#define PDL_RTC_ALARM_DAY_ENABLE		0x00000800ul
#define PDL_RTC_ALARM_DOW_DISABLE		0x00001000ul
#define PDL_RTC_ALARM_DOW_ENABLE		0x00002000ul

#define PDL_RTC_ALARM_TIME_DISABLE \
(PDL_RTC_ALARM_HOUR_DISABLE | PDL_RTC_ALARM_MINUTE_DISABLE | PDL_RTC_ALARM_SECOND_DISABLE)
#define PDL_RTC_ALARM_TIME_ENABLE \
(PDL_RTC_ALARM_HOUR_ENABLE | PDL_RTC_ALARM_MINUTE_ENABLE | PDL_RTC_ALARM_SECOND_ENABLE)
#define PDL_RTC_ALARM_DATE_DISABLE \
	(PDL_RTC_ALARM_YEAR_DISABLE | PDL_RTC_ALARM_MONTH_DISABLE | \
	PDL_RTC_ALARM_DAY_DISABLE | PDL_RTC_ALARM_DOW_DISABLE)
#define PDL_RTC_ALARM_DATE_ENABLE \
	(PDL_RTC_ALARM_YEAR_ENABLE | PDL_RTC_ALARM_MONTH_ENABLE | \
	PDL_RTC_ALARM_DAY_ENABLE | PDL_RTC_ALARM_DOW_ENABLE)

/* Periodic interrupt selection */
#define PDL_RTC_PERIODIC_DISABLE		0x00004000ul
#define PDL_RTC_PERIODIC_256_HZ			0x00008000ul
#define PDL_RTC_PERIODIC_64_HZ			0x00010000ul
#define PDL_RTC_PERIODIC_16_HZ			0x00020000ul
#define PDL_RTC_PERIODIC_4_HZ			0x00040000ul
#define PDL_RTC_PERIODIC_2_HZ			0x00080000ul
#define PDL_RTC_PERIODIC_1_HZ			0x00100000ul
#define PDL_RTC_PERIODIC_2S				0x00200000ul

/* Clock output control */
#define PDL_RTC_OUTPUT_DISABLE			0x00400000ul
#define PDL_RTC_OUTPUT_ENABLE			0x00800000ul

/* Clock control */
#define PDL_RTC_CLOCK_STOP				0x01000000ul
#define PDL_RTC_CLOCK_START				0x02000000ul

/* 30-second adjustment control */
#define PDL_RTC_ADJUST_START			0x04000000ul
 
/* Reset control */
#define PDL_RTC_RESET_START				0x08000000ul

/* Current time counter selection */
#define PDL_RTC_UPDATE_CURRENT_HOUR		0x0001u
#define PDL_RTC_UPDATE_CURRENT_MINUTE	0x0002u
#define PDL_RTC_UPDATE_CURRENT_SECOND	0x0004u
#define PDL_RTC_UPDATE_CURRENT_TIME	\
(PDL_RTC_UPDATE_CURRENT_HOUR | PDL_RTC_UPDATE_CURRENT_MINUTE | PDL_RTC_UPDATE_CURRENT_SECOND)

/* Current date counter selection */
#define PDL_RTC_UPDATE_CURRENT_YEAR		0x0008u
#define PDL_RTC_UPDATE_CURRENT_MONTH	0x0010u
#define PDL_RTC_UPDATE_CURRENT_DAY		0x0020u
#define PDL_RTC_UPDATE_CURRENT_DOW		0x0040u
#define PDL_RTC_UPDATE_CURRENT_DATE \
(PDL_RTC_UPDATE_CURRENT_YEAR | PDL_RTC_UPDATE_CURRENT_MONTH | PDL_RTC_UPDATE_CURRENT_DAY | PDL_RTC_UPDATE_CURRENT_DOW)

/* Alarm time counter selection */
#define PDL_RTC_UPDATE_ALARM_HOUR		0x0080u
#define PDL_RTC_UPDATE_ALARM_MINUTE		0x0100u
#define PDL_RTC_UPDATE_ALARM_SECOND		0x0200u
#define PDL_RTC_UPDATE_ALARM_TIME \
(PDL_RTC_UPDATE_ALARM_HOUR | PDL_RTC_UPDATE_ALARM_MINUTE | PDL_RTC_UPDATE_ALARM_SECOND)

/* Alarm date counter selection */
#define PDL_RTC_UPDATE_ALARM_YEAR		0x0400u
#define PDL_RTC_UPDATE_ALARM_MONTH		0x0800u
#define PDL_RTC_UPDATE_ALARM_DAY		0x1000u
#define PDL_RTC_UPDATE_ALARM_DOW		0x2000u
#define PDL_RTC_UPDATE_ALARM_DATE \
(PDL_RTC_UPDATE_ALARM_YEAR | PDL_RTC_UPDATE_ALARM_MONTH	| PDL_RTC_UPDATE_ALARM_DAY	| PDL_RTC_UPDATE_ALARM_DOW)

#endif
/* End of file */
