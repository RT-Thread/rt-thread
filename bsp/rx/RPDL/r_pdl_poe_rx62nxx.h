/*""FILE COMMENT""*******************************************************
* System Name	: POE API for RX62Nxx
* File Name		: r_pdl_poe_RX62Nxx.h
* Version		: 1.02
* Contents		: POE API header
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

#ifndef R_PDL_POE_RX62Nxx_H
#define R_PDL_POE_RX62Nxx_H

#define POE_INTERRUPTS	4

/* Callback function storage */
extern VoidCallBackFunc rpdl_POE_callback_func[];

/* Library prototypes */
bool R_POE_SetAll(
	const uint32_t,
	const uint8_t,
	const uint32_t
);
bool R_POE_CreateAll(
	const uint16_t,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_POE_ControlAll(
	const uint8_t,
	const uint16_t,
	const uint16_t
);
bool R_POE_GetStatusAll(
	volatile uint16_t * const
);
bool ReturnFalse(void);

/* Macro definitions */

#define R_POE_Set(a, b, c) \
( \
R_POE_SetAll( (a), (b), (c) ) \
)

#define R_POE_Create(a, b, c, d, e, f) \
( \
( ((f) <= IPL_MAX) ) ? \
R_POE_CreateAll( (a), (b), (c), (d), (e), (f) ) : \
ReturnFalse() \
)

#define R_POE_Control(a, b, c) \
( \
R_POE_ControlAll( (a), (b), (c) ) \
)

#define R_POE_GetStatus(a) \
( \
R_POE_GetStatusAll( (a) ) \
)

#endif
/* End of file */
