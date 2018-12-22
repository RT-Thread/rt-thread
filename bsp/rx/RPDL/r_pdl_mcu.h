/*""FILE COMMENT""*******************************************************
* System Name	: MCU API for RX62Nxx
* File Name		: r_pdl_mcu.h
* Version		: 1.02
* Contents		: MCU API header
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

#ifndef R_PDL_MCU_H
#define R_PDL_MCU_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_MCU_Control(
	uint8_t
);
bool R_MCU_GetStatus(
	uint16_t *
);

/* On-chip ROM control */
#define PDL_MCU_ROM_ENABLE	0x01u
#define PDL_MCU_ROM_DISABLE	0x02u

/* On-chip RAM control */
#define PDL_MCU_RAM_ENABLE	0x04u
#define PDL_MCU_RAM_DISABLE	0x08u

#endif
/* End of file */
