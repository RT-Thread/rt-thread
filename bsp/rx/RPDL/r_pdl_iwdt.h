/*""FILE COMMENT""*******************************************************
* System Name	: Independent Watchdog timer API for RX62Nxx
* File Name		: r_pdl_iwdt.h
* Version		: 1.02
* Contents		: IWDT API header
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

#ifndef R_PDL_IWDT_H
#define R_PDL_IWDT_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_IWDT_Set(
	uint16_t
);
bool R_IWDT_Control(
	uint8_t
);
bool R_IWDT_Read(
	uint16_t *
);

/* Calculation selection */
#define PDL_IWDT_TIMEOUT_1024	0x0001u
#define PDL_IWDT_TIMEOUT_4096	0x0002u
#define PDL_IWDT_TIMEOUT_8192	0x0004u
#define PDL_IWDT_TIMEOUT_16384	0x0008u

#define PDL_IWDT_CLOCK_OCO_1	0x0010u
#define PDL_IWDT_CLOCK_OCO_16	0x0020u
#define PDL_IWDT_CLOCK_OCO_32	0x0040u
#define PDL_IWDT_CLOCK_OCO_64	0x0080u
#define PDL_IWDT_CLOCK_OCO_128	0x0100u
#define PDL_IWDT_CLOCK_OCO_256	0x0200u

#define PDL_IWDT_REFRESH	0x01u

#endif
/* End of file */
