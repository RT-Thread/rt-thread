/*""FILE COMMENT""*******************************************************
* System Name	: Real-time clock API for RX62Nxx
* File Name		: r_pdl_rtc_RX62Nxx.h
* Version		: 1.02
* Contents		: RTC header
* Customer		:
* Model			:
* Order			:
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
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

#ifndef R_PDL_RTC_RX62Nxx_H
#define R_PDL_RTC_RX62Nxx_H

extern VoidCallBackFunc rpdl_RTC_Periodic_callback_func;
extern VoidCallBackFunc rpdl_RTC_Alarm_callback_func;

/* Library prototypes */
bool R_RTC_CreateAll(
	const uint32_t,
	const uint32_t,
	const uint32_t,
	const uint32_t,
	const uint32_t,
	VoidCallBackFunc const,
	const uint8_t,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_RTC_ControlAll(
	const uint32_t,
	const uint16_t,
	const uint32_t,
	const uint32_t,
	const uint32_t,
	const uint32_t
);
bool R_RTC_ReadAll(
	volatile uint8_t * const,
	volatile uint32_t * const,
	volatile uint32_t * const
);
bool ReturnFalse(void);

/* Macro definitions */

#define R_RTC_Create(a, b, c, d, e, f, g, h, i) \
( \
( ((g) <= IPL_MAX) && ((i) <= IPL_MAX) ) ? \
R_RTC_CreateAll( (a), (b), (c), (d), (e), (f), (g), (h), (i) ): \
ReturnFalse() \
)

#define R_RTC_Control(a, b, c, d, e, f) \
( \
R_RTC_ControlAll( (a), (b), (c), (d), (e), (f) ) \
)

#define R_RTC_Read(a, b, c) \
( \
R_RTC_ReadAll( (a), (b), (c) ) \
)

#endif
/* End of file */
