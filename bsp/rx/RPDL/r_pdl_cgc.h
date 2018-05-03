/*""FILE COMMENT""*******************************************************
* System Name	: CGC API
* File Name		: r_pdl_cgc.h
* Version		: 1.02
* Contents		: CGC header
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

#ifndef R_PDL_CGC_H
#define R_PDL_CGC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_CGC_Set(
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint16_t
);

bool R_CGC_Control(
	uint16_t
);

bool R_CGC_GetStatus(
	uint8_t *
);

/* BCLK pin putput control */
#define PDL_CGC_BCLK_DISABLE		0x0001u
#define PDL_CGC_BCLK_DIV_1			0x0002u
#define PDL_CGC_BCLK_DIV_2			0x0004u
#define PDL_CGC_BCLK_HIGH			0x0008u

/* SDCLK pin putput control */
#define PDL_CGC_SDCLK_DISABLE		0x0010u
#define PDL_CGC_SDCLK_ENABLE		0x0020u

/* Oscillation Stop Detection control */
#define PDL_CGC_OSC_STOP_ENABLE		0x0040u
#define PDL_CGC_OSC_STOP_DISABLE	0x0080u

/* Sub-clock oscillator control */
#define PDL_CGC_SUB_CLOCK_ENABLE	0x0100u
#define PDL_CGC_SUB_CLOCK_DISABLE	0x0200u

#endif
/* End of file */
