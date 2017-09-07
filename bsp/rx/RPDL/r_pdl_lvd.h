/*""FILE COMMENT""*******************************************************
* System Name	: Voltage detection circuit API for RX62Nxx
* File Name		: r_pdl_lvd.h
* Version		: 1.02
* Contents		: LVD API header
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

#ifndef R_PDL_LVD_H
#define R_PDL_LVD_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool LVD_Control(
	uint8_t
);

/* LVD2 and LVD1 control */
#define PDL_LVD_VDET2_DISABLE_VDET1_DISABLE		0x01u
#define PDL_LVD_VDET2_DISABLE_VDET1_RESET		0x02u
#define PDL_LVD_VDET2_DISABLE_VDET1_INTERRUPT	0x04u
#define PDL_LVD_VDET2_RESET_VDET1_DISABLE		0x08u
#define PDL_LVD_VDET2_INTERRUPT_VDET1_DISABLE	0x10u
#define PDL_LVD_VDET2_INTERRUPT_VDET1_RESET		0x20u

#endif
/* End of file */
