/*""FILE COMMENT""*******************************************************
* System Name	: PPG API for RX62Nxx
* File Name		: r_pdl_PPG.h
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

#ifndef R_PDL_PPG_H
#define R_PDL_PPG_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_PPG_Create(
	uint32_t,
	uint16_t,
	uint8_t
);
bool R_PPG_Destroy(
	uint32_t
);
bool R_PPG_Control(
	uint32_t,
	uint8_t
);

/* Output pin selection */
#define PDL_PPG_PO0		(PDL_PPG_GROUP_0 | 0x01u)
#define PDL_PPG_PO1		(PDL_PPG_GROUP_0 | 0x02u)
#define PDL_PPG_PO2		(PDL_PPG_GROUP_0 | 0x04u)
#define PDL_PPG_PO3		(PDL_PPG_GROUP_0 | 0x08u)
#define PDL_PPG_PO4		(PDL_PPG_GROUP_1 | 0x10u)
#define PDL_PPG_PO5		(PDL_PPG_GROUP_1 | 0x20u)
#define PDL_PPG_PO6		(PDL_PPG_GROUP_1 | 0x40u)
#define PDL_PPG_PO7		(PDL_PPG_GROUP_1 | 0x80u)
#define PDL_PPG_PO8		(PDL_PPG_GROUP_2 | 0x01u)
#define PDL_PPG_PO9		(PDL_PPG_GROUP_2 | 0x02u)
#define PDL_PPG_PO10	(PDL_PPG_GROUP_2 | 0x04u)
#define PDL_PPG_PO11	(PDL_PPG_GROUP_2 | 0x08u)
#define PDL_PPG_PO12	(PDL_PPG_GROUP_3 | 0x10u)
#define PDL_PPG_PO13	(PDL_PPG_GROUP_3 | 0x20u)
#define PDL_PPG_PO14	(PDL_PPG_GROUP_3 | 0x40u)
#define PDL_PPG_PO15	(PDL_PPG_GROUP_3 | 0x80u)
#define PDL_PPG_PO16	(PDL_PPG_GROUP_4 | 0x01u)
#define PDL_PPG_PO17	(PDL_PPG_GROUP_4 | 0x02u)
#define PDL_PPG_PO18	(PDL_PPG_GROUP_4 | 0x04u)
#define PDL_PPG_PO19	(PDL_PPG_GROUP_4 | 0x08u)
#define PDL_PPG_PO20	(PDL_PPG_GROUP_5 | 0x10u)
#define PDL_PPG_PO21	(PDL_PPG_GROUP_5 | 0x20u)
#define PDL_PPG_PO22	(PDL_PPG_GROUP_5 | 0x40u)
#define PDL_PPG_PO23	(PDL_PPG_GROUP_5 | 0x80u)
#define PDL_PPG_PO24	(PDL_PPG_GROUP_6 | 0x01u)
#define PDL_PPG_PO25	(PDL_PPG_GROUP_6 | 0x02u)
#define PDL_PPG_PO26	(PDL_PPG_GROUP_6 | 0x04u)
#define PDL_PPG_PO27	(PDL_PPG_GROUP_6 | 0x08u)
#define PDL_PPG_PO28	(PDL_PPG_GROUP_7 | 0x10u)
#define PDL_PPG_PO29	(PDL_PPG_GROUP_7 | 0x20u)
#define PDL_PPG_PO30	(PDL_PPG_GROUP_7 | 0x40u)
#define PDL_PPG_PO31	(PDL_PPG_GROUP_7 | 0x80u)

/* Output trigger selection */
#define PDL_PPG_TRIGGER_MTU0	0x0001u
#define PDL_PPG_TRIGGER_MTU1	0x0002u
#define PDL_PPG_TRIGGER_MTU2	0x0004u
#define PDL_PPG_TRIGGER_MTU3	0x0008u
#define PDL_PPG_TRIGGER_MTU6	0x0010u
#define PDL_PPG_TRIGGER_MTU7	0x0020u
#define PDL_PPG_TRIGGER_MTU8	0x0040u
#define PDL_PPG_TRIGGER_MTU9	0x0080u

/* Non-overlap control */
#define PDL_PPG_NORMAL			0x0100u
#define PDL_PPG_NON_OVERLAP		0x0200u

/* Invert control */
#define PDL_PPG_DIRECT			0x0400u
#define PDL_PPG_INVERT			0x0800u

/* Group selection */
#define PDL_PPG_GROUP_0	0x00000100u
#define PDL_PPG_GROUP_1	0x00110200u
#define PDL_PPG_GROUP_2	0x00220400u
#define PDL_PPG_GROUP_3	0x00330800u
#define PDL_PPG_GROUP_4	0x01041000u
#define PDL_PPG_GROUP_5	0x01152000u
#define PDL_PPG_GROUP_6	0x01264000u
#define PDL_PPG_GROUP_7	0x01378000u

#endif
/* End of file */
