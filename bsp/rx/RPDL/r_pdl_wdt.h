/*""FILE COMMENT""*******************************************************
* System Name	: WDT API for RX62Nxx
* File Name		: r_pdl_wdt.h
* Version		: 1.02
* Contents		: WDT API header
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

#ifndef R_PDL_WDT_H
#define R_PDL_WDT_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_WDT_Create(
	uint16_t,
	void *,
	uint8_t
);
bool R_WDT_Control(
	uint8_t
);
bool R_WDT_Read(
	uint8_t *
);

/* Calculation selection */
#define PDL_WDT_PCLK_DIV_4		0x0001u
#define PDL_WDT_PCLK_DIV_64		0x0002u
#define PDL_WDT_PCLK_DIV_128	0x0004u
#define PDL_WDT_PCLK_DIV_512	0x0008u
#define PDL_WDT_PCLK_DIV_2048	0x0010u
#define PDL_WDT_PCLK_DIV_8192	0x0020u
#define PDL_WDT_PCLK_DIV_32768	0x0040u
#define PDL_WDT_PCLK_DIV_131072	0x0080u

/* MCU reset control */
#define PDL_WDT_RESET_DISABLE	0x0100u
#define PDL_WDT_RESET_ENABLE	0x0200u

/* Timer counter control */
#define PDL_WDT_STOP			0x01u
#define PDL_WDT_RESET_COUNTER	0x02u

#endif
/* End of file */
