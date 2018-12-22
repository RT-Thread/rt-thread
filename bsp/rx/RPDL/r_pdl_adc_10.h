/*""FILE COMMENT""*******************************************************
* System Name	: ADC converter API for RX62Nxx
* File Name		: r_pdl_adc_10.h
* Version		: 1.02
* Contents		: ADC function prototypes
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

#ifndef R_PDL_ADC_10_H
#define R_PDL_ADC_10_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_ADC_10_Create(
	uint8_t,
	uint32_t,
	uint32_t,
	float,
	void *,
	uint8_t
);
bool R_ADC_10_Destroy(
	uint8_t
);
bool R_ADC_10_Control(
	uint16_t
);
bool R_ADC_10_Read(
	uint8_t,
	uint16_t *
);

/* Scan mode */
#define PDL_ADC_10_MODE_SINGLE					0x00000001u
#define PDL_ADC_10_MODE_CONTINUOUS_SCAN			0x00000002u
#define PDL_ADC_10_MODE_ONE_CYCLE_SCAN			0x00000004u

/* Channel selection */
#define PDL_ADC_10_CHANNELS_OPTION_1			0x00000008u
#define PDL_ADC_10_CHANNELS_OPTION_2			0x00000010u
#define PDL_ADC_10_CHANNELS_OPTION_3			0x00000020u
#define PDL_ADC_10_CHANNELS_OPTION_4			0x00000040u

/* Trigger selection */
#define PDL_ADC_10_TRIGGER_SOFTWARE				0x00000080u 
#define PDL_ADC_10_TRIGGER_MTU0_MTU4_CMIC_A		0x00000100u 
#define PDL_ADC_10_TRIGGER_TMR0_CM_A			0x00000200u 
#define PDL_ADC_10_TRIGGER_ADTRG0				0x00000400u 
#define PDL_ADC_10_TRIGGER_ADTRG1				0x00000800u 
#define PDL_ADC_10_TRIGGER_MTU0_CMIC			0x00001000u 
#define PDL_ADC_10_TRIGGER_MTU6_MTU10_CMIC_A	0x00002000u 
#define PDL_ADC_10_TRIGGER_MTU4_CM				0x00004000u 
#define PDL_ADC_10_TRIGGER_MTU10_CM				0x00008000u 

/* Data alignment */
#define PDL_ADC_10_DATA_ALIGNMENT_LEFT			0x00010000u
#define PDL_ADC_10_DATA_ALIGNMENT_RIGHT			0x00020000u

/* DMAC / DTC trigger control */
#define PDL_ADC_10_DMAC_DTC_TRIGGER_DISABLE		0x00040000u
#define PDL_ADC_10_DMAC_TRIGGER_ENABLE			0x00080000u
#define PDL_ADC_10_DTC_TRIGGER_ENABLE			0x00100000u

/* Sampling time calcuation control */
#define PDL_ADC_10_ADSSTR_CALCULATE				0x00200000u
#define PDL_ADC_10_ADSSTR_SPECIFY				0x00400000u

/* Pin selection */
#define PDL_ADC_10_PIN_ADTRG0_A					0x00800000u
#define PDL_ADC_10_PIN_ADTRG0_B					0x01000000u

/* Self-Diagnostic */									
#define PDL_ADC_10_SINGLE_AN0_SW				(PDL_ADC_10_MODE_SINGLE | \
												 PDL_ADC_10_CHANNELS_OPTION_1 | \
												 PDL_ADC_10_TRIGGER_SOFTWARE)
#define PDL_ADC_10_ADDIAGR_DISABLE				0x02000000u
#define PDL_ADC_10_ADDIAGR_VREF_0				0x04000000u
#define PDL_ADC_10_ADDIAGR_VREF_0_5				0x08000000u
#define PDL_ADC_10_ADDIAGR_VREF_1				0x10000000u
#define PDL_ADC_10_SELF_DIAGNOSTIC_DISABLE		(PDL_ADC_10_ADDIAGR_DISABLE)
#define PDL_ADC_10_SELF_DIAGNOSTIC_VREF_0		(PDL_ADC_10_SINGLE_AN0_SW | PDL_ADC_10_ADDIAGR_VREF_0)
#define PDL_ADC_10_SELF_DIAGNOSTIC_VREF_0_5		(PDL_ADC_10_SINGLE_AN0_SW | PDL_ADC_10_ADDIAGR_VREF_0_5)
#define PDL_ADC_10_SELF_DIAGNOSTIC_VREF_1		(PDL_ADC_10_SINGLE_AN0_SW | PDL_ADC_10_ADDIAGR_VREF_1)

/* On / off control */
#define PDL_ADC_10_0_ON		0x0001u
#define PDL_ADC_10_0_OFF	0x0002u
#define PDL_ADC_10_1_ON		0x0004u
#define PDL_ADC_10_1_OFF	0x0008u

/* CPU control */
#define PDL_ADC_10_CPU_ON	0x0100u
#define PDL_ADC_10_CPU_OFF	0x0200u

#endif
/* End of file */
