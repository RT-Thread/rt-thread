/*""FILE COMMENT""*******************************************************
* System Name	: DAC API for RX62Nxx
* File Name		: r_pdl_dac_10.h
* Version		: 1.02
* Contents		: CRC function prototypes
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

#ifndef R_PDL_DAC_H
#define R_PDL_DAC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_DAC_10_Create(
	uint8_t,
	uint16_t,
	uint16_t
);
bool R_DAC_10_Destroy(
	uint8_t
);
bool R_DAC_10_Write(
	uint8_t,
	uint16_t,
	uint16_t
);

/* Channel selection */
#define PDL_DAC_10_CHANNEL_0	0x01u
#define PDL_DAC_10_CHANNEL_1	0x02u

/* Data alignment */
#define PDL_DAC_10_ALIGN_LEFT	0x04u
#define PDL_DAC_10_ALIGN_RIGHT	0x08u

#endif
/* End of file */
