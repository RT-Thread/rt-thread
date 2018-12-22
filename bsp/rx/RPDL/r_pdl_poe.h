/*""FILE COMMENT""*******************************************************
* System Name	: POE API for RX62Nxx
* File Name		: r_pdl_poe.h
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

#ifndef R_PDL_POE_H
#define R_PDL_POE_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_POE_Set(
	uint32_t,
	uint8_t,
	uint32_t
);
bool R_POE_Create(
	uint16_t,
	void *,
	void *,
	void *,
	void *,
	uint8_t
);
bool POE_Control(
	uint8_t,
	uint16_t,
	uint16_t
);
bool R_POE_GetStatus(
	uint16_t *
);

/* Pin selection */
#define PDL_POE_PINS_0_TO_3	0x01u
#define PDL_POE_PINS_4_TO_7	0x02u
#define PDL_POE_PIN_8		0x04u
#define PDL_POE_PIN_9		0x08u

/* Input pin detection */
#define PDL_POE_0_MODE_EDGE 	0x00000001ul
#define PDL_POE_0_MODE_LOW_8 	0x00000002ul
#define PDL_POE_0_MODE_LOW_16 	0x00000004ul
#define PDL_POE_0_MODE_LOW_128 	0x00000008ul

#define PDL_POE_1_MODE_EDGE 	0x00000010ul
#define PDL_POE_1_MODE_LOW_8 	0x00000020ul
#define PDL_POE_1_MODE_LOW_16 	0x00000040ul
#define PDL_POE_1_MODE_LOW_128 	0x00000080ul

#define PDL_POE_2_MODE_EDGE 	0x00000100ul
#define PDL_POE_2_MODE_LOW_8 	0x00000200ul
#define PDL_POE_2_MODE_LOW_16 	0x00000400ul
#define PDL_POE_2_MODE_LOW_128 	0x00000800ul

#define PDL_POE_3_MODE_EDGE 	0x00001000ul
#define PDL_POE_3_MODE_LOW_8 	0x00002000ul
#define PDL_POE_3_MODE_LOW_16 	0x00004000ul
#define PDL_POE_3_MODE_LOW_128 	0x00008000ul

#define PDL_POE_4_MODE_EDGE 	0x00010000ul
#define PDL_POE_4_MODE_LOW_8 	0x00020000ul
#define PDL_POE_4_MODE_LOW_16 	0x00040000ul
#define PDL_POE_4_MODE_LOW_128 	0x00080000ul

#define PDL_POE_5_MODE_EDGE 	0x00100000ul
#define PDL_POE_5_MODE_LOW_8 	0x00200000ul
#define PDL_POE_5_MODE_LOW_16 	0x00400000ul
#define PDL_POE_5_MODE_LOW_128 	0x00800000ul

#define PDL_POE_6_MODE_EDGE 	0x01000000ul
#define PDL_POE_6_MODE_LOW_8 	0x02000000ul
#define PDL_POE_6_MODE_LOW_16 	0x04000000ul
#define PDL_POE_6_MODE_LOW_128 	0x08000000ul

#define PDL_POE_7_MODE_EDGE 	0x10000000ul
#define PDL_POE_7_MODE_LOW_8 	0x20000000ul
#define PDL_POE_7_MODE_LOW_16 	0x40000000ul
#define PDL_POE_7_MODE_LOW_128 	0x80000000ul

#define PDL_POE_8_MODE_EDGE 	0x01u
#define PDL_POE_8_MODE_LOW_8 	0x02u
#define PDL_POE_8_MODE_LOW_16 	0x04u
#define PDL_POE_8_MODE_LOW_128 	0x08u

#define PDL_POE_9_MODE_EDGE 	0x10u
#define PDL_POE_9_MODE_LOW_8 	0x20u
#define PDL_POE_9_MODE_LOW_16 	0x40u
#define PDL_POE_9_MODE_LOW_128 	0x80u

/* Pin output control */

/* High impedance request detection */
#define PDL_POE_HI_Z_REQ_8_ENABLE	0x00000001ul
#define PDL_POE_HI_Z_REQ_MTIOC0A	0x00000002ul
#define PDL_POE_HI_Z_REQ_MTIOC0B	0x00000004ul
#define PDL_POE_HI_Z_REQ_MTIOC0C	0x00000008ul
#define PDL_POE_HI_Z_REQ_MTIOC0D	0x00000010ul

#define PDL_POE_HI_Z_REQ_9_ENABLE	0x00000020ul
#define PDL_POE_HI_Z_REQ_MTIOC6A	0x00000040ul
#define PDL_POE_HI_Z_REQ_MTIOC6B	0x00000080ul
#define PDL_POE_HI_Z_REQ_MTIOC6C	0x00000100ul
#define PDL_POE_HI_Z_REQ_MTIOC6D	0x00000200ul

/* Output short detection */
#define PDL_POE_SHORT_3_4_HI_Z		0x00000400ul
#define PDL_POE_SHORT_MTIOC4BD_B	0x00000800ul
#define PDL_POE_SHORT_MTIOC4AC_B	0x00001000ul
#define PDL_POE_SHORT_MTIOC3BD_B	0x00002000ul
#define PDL_POE_SHORT_MTIOC4BD_A	0x00004000ul
#define PDL_POE_SHORT_MTIOC4AC_A	0x00008000ul
#define PDL_POE_SHORT_MTIOC3BD_A	0x00010000ul

#define PDL_POE_SHORT_9_10_HI_Z		0x00020000ul
#define PDL_POE_SHORT_MTIOC10BD		0x00040000ul
#define PDL_POE_SHORT_MTIOC10AC		0x00080000ul
#define PDL_POE_SHORT_MTIOC9BD		0x00100000ul

/* High impedance request response */
#define PDL_POE_IRQ_HI_Z_0_3_DISABLE	0x0001u
#define PDL_POE_IRQ_HI_Z_0_3_ENABLE		0x0002u
#define PDL_POE_IRQ_HI_Z_4_7_DISABLE	0x0004u
#define PDL_POE_IRQ_HI_Z_4_7_ENABLE		0x0008u
#define PDL_POE_IRQ_HI_Z_8_DISABLE		0x0010u
#define PDL_POE_IRQ_HI_Z_8_ENABLE		0x0020u
#define PDL_POE_IRQ_HI_Z_9_DISABLE		0x0040u
#define PDL_POE_IRQ_HI_Z_9_ENABLE		0x0080u

/* Output short detection response */
#define PDL_POE_IRQ_SHORT_3_4_ENABLE	0x0100u
#define PDL_POE_IRQ_SHORT_3_4_DISABLE	0x0200u
#define PDL_POE_IRQ_SHORT_9_10_ENABLE	0x0400u
#define PDL_POE_IRQ_SHORT_9_10_DISABLE	0x0800u

/* MTU channel high impedance control */
#define PDL_POE_MTU3_MTU4_HI_Z_ON	0x01u
#define PDL_POE_MTU3_MTU4_HI_Z_OFF	0x02u
#define PDL_POE_MTU0_HI_Z_ON		0x04u
#define PDL_POE_MTU0_HI_Z_OFF		0x08u
#define PDL_POE_MTU9_MTU10_HI_Z_ON	0x10u
#define PDL_POE_MTU9_MTU10_HI_Z_OFF	0x20u
#define PDL_POE_MTU6_HI_Z_ON		0x40u
#define PDL_POE_MTU6_HI_Z_OFF		0x80u

/* Event flag control */
#define PDL_POE_FLAG_POE0_CLEAR			0x0001u
#define PDL_POE_FLAG_POE1_CLEAR			0x0002u
#define PDL_POE_FLAG_POE2_CLEAR			0x0004u
#define PDL_POE_FLAG_POE3_CLEAR			0x0008u
#define PDL_POE_FLAG_POE4_CLEAR			0x0010u
#define PDL_POE_FLAG_POE5_CLEAR			0x0020u
#define PDL_POE_FLAG_POE6_CLEAR			0x0040u
#define PDL_POE_FLAG_POE7_CLEAR			0x0080u
#define PDL_POE_FLAG_POE8_CLEAR			0x0100u
#define PDL_POE_FLAG_POE9_CLEAR			0x0200u
#define PDL_POE_FLAG_SHORT_3_4_CLEAR	0x0400u
#define PDL_POE_FLAG_SHORT_9_10_CLEAR	0x0800u

#endif
/* End of file */
