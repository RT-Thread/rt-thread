/*""FILE COMMENT""*******************************************************
* System Name	: EXDMAC API for RX62Nxx
* File Name		: r_pdl_exdmac.h
* Version		: 1.02
* Contents		: EXDMAC API header
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

#ifndef R_PDL_EXDMAC_H
#define R_PDL_EXDMAC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_EXDMAC_Create(
	uint8_t,
	uint32_t,
	uint16_t,
	uint8_t,
	void *,
	void *,
	uint16_t,
	uint16_t,
	int32_t,
	uint32_t,
	uint32_t,
	void *,
	uint8_t
);
bool R_EXDMAC_Destroy(
	uint8_t
);
bool R_EXDMAC_Control(
	uint8_t,
	uint16_t,
	void *,
	void *,
	uint16_t,
	uint16_t,
	int32_t,
	uint32_t,
	uint32_t
);
bool R_EXDMAC_GetStatus(
	uint8_t,
	uint8_t *,
	uint32_t *,
	uint32_t *,
	uint16_t *,
	uint16_t *
);
	
/* Transfer mode selection */
#define PDL_EXDMAC_NORMAL						0x00000001ul
#define PDL_EXDMAC_REPEAT						0x00000002ul
#define PDL_EXDMAC_BLOCK						0x00000004ul
#define PDL_EXDMAC_CLUSTER						0x00000008ul
#define PDL_EXDMAC_SOURCE						0x00000010ul
#define PDL_EXDMAC_DESTINATION					0x00000020ul

/* Address addition direction selection */
#define PDL_EXDMAC_SOURCE_ADDRESS_FIXED			0x00000040ul
#define PDL_EXDMAC_SOURCE_ADDRESS_PLUS			0x00000080ul
#define PDL_EXDMAC_SOURCE_ADDRESS_MINUS			0x00000100ul
#define PDL_EXDMAC_SOURCE_ADDRESS_OFFSET		0x00000200ul
#define PDL_EXDMAC_DESTINATION_ADDRESS_FIXED	0x00000400ul
#define PDL_EXDMAC_DESTINATION_ADDRESS_PLUS		0x00000800ul
#define PDL_EXDMAC_DESTINATION_ADDRESS_MINUS	0x00001000ul
#define PDL_EXDMAC_DESTINATION_ADDRESS_OFFSET	0x00002000ul

/* Address mode selection */
#define PDL_EXDMAC_ADDRESS_MODE_READ			0x00004000ul
#define PDL_EXDMAC_ADDRESS_MODE_WRITE			0x00008000ul
#define PDL_EXDMAC_ADDRESS_MODE_DUAL			0x00010000ul

/* Transfer data size */
#define PDL_EXDMAC_SIZE_8						0x00020000ul
#define PDL_EXDMAC_SIZE_16						0x00040000ul
#define PDL_EXDMAC_SIZE_32						0x00080000ul

/* Pin selection */
#define PDL_EXDMAC_PIN_A			0x0001u
#define PDL_EXDMAC_PIN_B			0x0002u
#define PDL_EXDMAC_PIN_C			0x0004u

/* EDACKn pin output control */
#define PDL_EXDMAC_EDACK_DISABLE	0x0008u
#define PDL_EXDMAC_EDACK_LOW		0x0010u
#define PDL_EXDMAC_EDACK_HIGH		0x0020u
#define PDL_EXDMAC_EDACK_SYNC		0x0040u
#define PDL_EXDMAC_EDACK_WAIT		0x0080u

/* Trigger selection */
#define PDL_EXDMAC_TRIGGER_SW		0x0100u
#define PDL_EXDMAC_TRIGGER_RISING	0x0200u
#define PDL_EXDMAC_TRIGGER_FALLING	0x0400u
#define PDL_EXDMAC_TRIGGER_LOW		0x0800u
#define PDL_EXDMAC_TRIGGER_MTU1		0x1000u

/* Interrupt generation */
#define PDL_EXDMAC_IRQ_END				0x01u
#define PDL_EXDMAC_IRQ_ESCAPE_END		0x02u
#define PDL_EXDMAC_IRQ_REPEAT_SIZE_END	0x04u
#define PDL_EXDMAC_IRQ_EXT_SOURCE		0x08u
#define PDL_EXDMAC_IRQ_EXT_DESTINATION	0x10u

/* DTC trigger control */
#define PDL_EXDMAC_DTC_TRIGGER_DISABLE	0x20u
#define PDL_EXDMAC_DTC_TRIGGER_ENABLE	0x40u

/* Enable / suspend control */
#define PDL_EXDMAC_ENABLE						0x0001u
#define PDL_EXDMAC_SUSPEND						0x0002u

/* Software trigger control */
#define PDL_EXDMAC_START						0x0004u
#define PDL_EXDMAC_START_RUN					0x0008u
#define PDL_EXDMAC_STOP							0x0010u

/* Transfer end interrupt flag control */
#define PDL_EXDMAC_CLEAR_DTIF					0x0020u
#define PDL_EXDMAC_CLEAR_ESIF					0x0040u

/* Modify registers selection */
#define PDL_EXDMAC_UPDATE_SOURCE				0x0080u
#define PDL_EXDMAC_UPDATE_DESTINATION			0x0100u
#define PDL_EXDMAC_UPDATE_COUNT					0x0200u
#define PDL_EXDMAC_UPDATE_SIZE					0x0400u
#define PDL_EXDMAC_UPDATE_OFFSET				0x0800u
#define PDL_EXDMAC_UPDATE_REPEAT_SOURCE			0x1000u
#define PDL_EXDMAC_UPDATE_REPEAT_DESTINATION	0x2000u

#endif
/* End of file */
