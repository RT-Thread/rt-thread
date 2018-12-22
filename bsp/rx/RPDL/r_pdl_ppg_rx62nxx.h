/*""FILE COMMENT""*******************************************************
* System Name	: PPG API for RX62Nxx
* File Name		: r_pdl_ppg_RX62Nxx.h
* Version		: 1.02
* Contents		: PPG API header
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

#ifndef R_PDL_PPG_RX62Nxx_H
#define R_PDL_PPG_RX62Nxx_H

#define PPG_UNITS			2
#define PPG_GROUPS_PER_UNIT	4
#define PPG_GROUPS	(uint8_t)(PPG_UNITS * PPG_GROUPS_PER_UNIT)

/* Library prototypes */
bool R_PPG_CreateAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint16_t,
	const uint8_t
);
bool R_PPG_DestroyAll(
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_PPG_ControlAll(
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool ReturnFalse(void);

/* Macro definitions */

#define R_PPG_Create(a, b, c) \
( \
( (a) != 0x00000000u ) ? \
R_PPG_CreateAll( (uint8_t)(((a) & 0x0F000000ul) >> 24), (uint8_t)(((a) & 0x00F00000ul) >> 20), (uint8_t)(((a) & 0x000F0000ul) >> 16), (uint8_t)(((a) & 0x0000FF00ul) >> 8), (uint8_t)(a), (b), (c) ) : \
ReturnFalse() \
)

#define R_PPG_Destroy(a) \
( \
( (a) != 0x00000000u ) ? \
R_PPG_DestroyAll( (uint8_t)(((a) & 0x0F000000ul) >> 24), (uint8_t)(((a) & 0x0000FF00ul) >> 8), (uint8_t)(a) ) : \
ReturnFalse() \
)

#define R_PPG_Control(a, b ) \
( \
( (a) != 0x00u ) ? \
R_PPG_ControlAll( (uint8_t)(((a) & 0x0F000000ul) >> 24), (uint8_t)(((a) & 0x0000FF00ul) >> 8), (b) ) : \
ReturnFalse() \
)

#endif
/* End of file */
