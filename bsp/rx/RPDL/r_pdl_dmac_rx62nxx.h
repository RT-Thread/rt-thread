/*""FILE COMMENT""*******************************************************
* System Name	: DMAC API for RX62Nxx
* File Name		: r_pdl_dmac_RX62Nxx.h
* Version		: 1.02
* Contents		: DMAC API header
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

#ifndef R_PDL_DMAC_RX62Nxx_H
#define R_PDL_DMAC_RX62Nxx_H

#define DMAC_CHANNELS	4

/* Callback function storage */
extern VoidCallBackFunc rpdl_DMAC_callback_func[];

/* Library prototypes */
bool R_DMAC_CreateAll(
	const uint8_t,
	const uint32_t,
	const uint8_t,
	volatile const void * const,
	volatile const void * const,
	const uint16_t,
	const uint16_t,
	const int32_t,
	const uint32_t,
	const uint32_t,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_DMAC_DestroyAll(
	const uint8_t
);
bool R_DMAC_ControlAll(
	const uint8_t,
	const uint16_t,
	volatile const void * const,
	volatile const void * const,
	const uint16_t,
	const uint16_t,
	const int32_t,
	const uint32_t,
	const uint32_t
);
bool R_DMAC_GetStatusAll(
	const uint8_t,
	volatile uint8_t * const,
	volatile uint32_t * const,
	volatile uint32_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const
);
bool ReturnFalse(void);

/* Macro definitions */

#define R_DMAC_Create(a, b, c, d, e, f, g, h, i, j, k, l) \
( \
( ( ((a) < DMAC_CHANNELS ) && ((l) <= IPL_MAX) ) ) ? \
R_DMAC_CreateAll( (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l) ) : \
ReturnFalse() \
)

#define R_DMAC_Control(a, b, c, d, e, f, g, h, i) \
( \
( ((a) < DMAC_CHANNELS) ) ? \
R_DMAC_ControlAll( (a), (b), (c), (d), (e), (f), (g), (h), (i) ) : \
ReturnFalse() \
)

#define R_DMAC_GetStatus(a, b, c, d, e, f) \
( \
( ((a) < DMAC_CHANNELS) ) ? \
R_DMAC_GetStatusAll( (a), (b), (c), (d), (e), (f) ) : \
ReturnFalse() \
)

#define R_DMAC_Destroy(a) \
( \
( ((a) < DMAC_CHANNELS) ) ? \
R_DMAC_DestroyAll( (a) ) : \
ReturnFalse() \
)

#endif
/* End of file */
