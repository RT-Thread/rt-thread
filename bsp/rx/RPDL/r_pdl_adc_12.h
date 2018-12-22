/*""FILE COMMENT""*******************************************************
* System Name	: 12-bit ADC converter API for RX62Nxx
* File Name		: r_pdl_adc_12.h
* Version		: 1.02
* Contents		: ADC_12 function prototypes
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

#ifndef R_PDL_ADC_12_H
#define R_PDL_ADC_12_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_ADC_12_Create(
	uint8_t,
	uint32_t,
	uint16_t,
	uint16_t,
	void *,
	uint8_t
);
bool R_ADC_12_Destroy(
	uint8_t
);
bool R_ADC_12_Control(
	uint8_t
);
bool R_ADC_12_Read(
	uint8_t,
	uint16_t *
);

/* Scan mode */
#define PDL_ADC_12_SCAN_SINGLE				0x00000001ul
#define PDL_ADC_12_SCAN_CONTINUOUS			0x00000002ul

// Input channel selection
#define PDL_ADC_12_CHANNEL_0				0x00000004ul
#define PDL_ADC_12_CHANNEL_1				0x00000008ul
#define PDL_ADC_12_CHANNEL_2				0x00000010ul
#define PDL_ADC_12_CHANNEL_3				0x00000020ul
#define PDL_ADC_12_CHANNEL_4				0x00000040ul
#define PDL_ADC_12_CHANNEL_5				0x00000080ul
#define PDL_ADC_12_CHANNEL_6				0x00000100ul
#define PDL_ADC_12_CHANNEL_7				0x00000200ul

/* Clock division */
#define PDL_ADC_12_DIV_1					0x00000400ul
#define PDL_ADC_12_DIV_2					0x00000800ul
#define PDL_ADC_12_DIV_4					0x00001000ul
#define PDL_ADC_12_DIV_8					0x00002000ul

/* Data alignment */
#define PDL_ADC_12_DATA_ALIGNMENT_LEFT		0x00004000ul
#define PDL_ADC_12_DATA_ALIGNMENT_RIGHT		0x00008000ul

/* Result register clearing */
#define PDL_ADC_12_RETAIN_RESULT			0x00010000ul
#define PDL_ADC_12_CLEAR_RESULT				0x00020000ul

/* DMAC / DTC trigger control */
#define PDL_ADC_12_DMAC_DTC_TRIGGER_DISABLE	0x00040000ul
#define PDL_ADC_12_DMAC_TRIGGER_ENABLE		0x00080000ul
#define PDL_ADC_12_DTC_TRIGGER_ENABLE		0x00100000ul

/* Trigger selection */
#define PDL_ADC_12_TRIGGER_SOFTWARE			0x0001u
#define PDL_ADC_12_TRIGGER_ADTRG0			0x0002u
#define PDL_ADC_12_TRIGGER_MTU0_ICCM_A		0x0004u
#define PDL_ADC_12_TRIGGER_MTU0_ICCM_B		0x0008u
#define PDL_ADC_12_TRIGGER_MTU0_MTU4_ICCM	0x0010u
#define PDL_ADC_12_TRIGGER_MTU6_MTU10_ICCM	0x0020u
#define PDL_ADC_12_TRIGGER_MTU0_CM_E		0x0040u
#define PDL_ADC_12_TRIGGER_MTU0_CM_F		0x0080u
#define PDL_ADC_12_TRIGGER_MTU4_CM			0x0100u
#define PDL_ADC_12_TRIGGER_MTU10_CM			0x0200u
#define PDL_ADC_12_TRIGGER_TMR0				0x0400u
#define PDL_ADC_12_TRIGGER_TMR2				0x0800u

/* Pin selection */
#define PDL_ADC_12_PIN_ADTRG0_A				0x1000u
#define PDL_ADC_12_PIN_ADTRG0_B				0x2000u

/* Value addition mode selection */
#define PDL_ADC_12_VALUE_ADD_CHANNEL_0	0x0001u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_1	0x0002u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_2	0x0004u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_3	0x0008u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_4	0x0010u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_5	0x0020u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_6	0x0040u
#define PDL_ADC_12_VALUE_ADD_CHANNEL_7	0x0080u

/* Value addition count selection */
#define PDL_ADC_12_VALUE_ADD_TIME_1		0x0100u 
#define PDL_ADC_12_VALUE_ADD_TIME_2		0x0200u 
#define PDL_ADC_12_VALUE_ADD_TIME_3		0x0400u 
#define PDL_ADC_12_VALUE_ADD_TIME_4		0x0800u 

/* On / off control */
#define PDL_ADC_12_0_ON		0x01u
#define PDL_ADC_12_0_OFF	0x02u

/* CPU control */
#define PDL_ADC_12_CPU_OFF	0x04u

#endif
/* End of file */
