/*""FILE COMMENT""*******************************************************
* System Name	: Timer TMR API for RX62Nxx
* File Name		: r_pdl_tmr.h
* Version		: 1.02
* Contents		: Timer TMR API header
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

#ifndef R_PDL_TMR_H
#define R_PDL_TMR_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_TMR_Set(
	uint8_t
);
bool R_TMR_CreateChannel(
	uint8_t,
	uint32_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	void *,
	void *,
	void *,
	uint8_t
);
bool R_TMR_CreateUnit(
	uint8_t,
	uint32_t,
	uint8_t,
	uint16_t,
	uint16_t,
	uint16_t,
	void *,
	void *,
	void *,
	uint8_t
);
bool R_TMR_CreatePeriodic(
	uint8_t,
	uint32_t,
	float,
	float,
	void *,
	void *,
	uint8_t
);
bool R_TMR_CreateOneShot(
	uint8_t,
	uint32_t,
	float,
	void *,
	uint8_t
);
bool R_TMR_Destroy(
	uint8_t
); 
bool R_TMR_ControlChannel(
	uint8_t,
	uint32_t,
	uint8_t,
	uint8_t,
	uint8_t
);
bool R_TMR_ControlUnit(
	uint8_t,
	uint32_t,
	uint16_t,
	uint16_t,
	uint16_t
);
bool R_TMR_ControlPeriodic(
	uint8_t,
	uint32_t,
	float,
	float
);
bool R_TMR_ReadChannel(
	uint8_t,
	uint8_t *,
	uint8_t *,
	uint8_t *,
	uint8_t *
);
bool R_TMR_ReadUnit(
	uint8_t,
	uint8_t *,
	uint16_t *,
	uint16_t *,
	uint16_t *
);

/* Pin selection */
#define PDL_TMR_PIN_TMR0_A	0x01u
#define PDL_TMR_PIN_TMR0_B	0x02u
#define PDL_TMR_PIN_TMR1_A	0x04u
#define PDL_TMR_PIN_TMR1_B	0x08u
#define PDL_TMR_PIN_TMR2_A	0x10u
#define PDL_TMR_PIN_TMR2_B	0x20u
#define PDL_TMR_PIN_TMR3_A	0x40u
#define PDL_TMR_PIN_TMR3_B	0x80u

/* Counter clock sources */
#define PDL_TMR_CLK_OFF						0x00000001ul
#define PDL_TMR_CLK_EXT_RISING				0x00000002ul
#define PDL_TMR_CLK_EXT_FALLING				0x00000004ul
#define PDL_TMR_CLK_EXT_BOTH				0x00000008ul
#define PDL_TMR_CLK_PCLK_DIV_1				0x00000010ul
#define PDL_TMR_CLK_PCLK_DIV_2				0x00000020ul
#define PDL_TMR_CLK_PCLK_DIV_8				0x00000040ul
#define PDL_TMR_CLK_PCLK_DIV_32				0x00000080ul
#define PDL_TMR_CLK_PCLK_DIV_64				0x00000100ul
#define PDL_TMR_CLK_PCLK_DIV_1024			0x00000200ul
#define PDL_TMR_CLK_PCLK_DIV_8192			0x00000400ul
#define PDL_TMR_CLK_TMR1_OVERFLOW			0x00000800ul
#define PDL_TMR_CLK_TMR3_OVERFLOW			0x00001000ul
#define PDL_TMR_CLK_TMR0_CM_A				0x00002000ul
#define PDL_TMR_CLK_TMR2_CM_A				0x00004000ul

/* A/D trigger control */
#define PDL_TMR_ADC_TRIGGER_DISABLE			0x00008000ul
#define PDL_TMR_ADC_TRIGGER_ENABLE			0x00010000ul

/* Counter clearing options */
#define PDL_TMR_CLEAR_DISABLE				0x00020000ul
#define PDL_TMR_CLEAR_CM_A					0x00040000ul
#define PDL_TMR_CLEAR_CM_B					0x00080000ul
#define PDL_TMR_CLEAR_RESET_RISING			0x00100000ul
#define PDL_TMR_CLEAR_RESET_HIGH			0x00200000ul

/* DTC CMA trigger control */
#define PDL_TMR_CM_A_DTC_TRIGGER_DISABLE	0x00400000ul
#define PDL_TMR_CM_A_DTC_TRIGGER_ENABLE		0x00800000ul

/* DTC CMB trigger control */
#define PDL_TMR_CM_B_DTC_TRIGGER_DISABLE	0x01000000ul
#define PDL_TMR_CM_B_DTC_TRIGGER_ENABLE		0x02000000ul

/* Output control options */
#define PDL_TMR_OUTPUT_IGNORE_CM_A	0x01u
#define PDL_TMR_OUTPUT_LOW_CM_A		0x02u
#define PDL_TMR_OUTPUT_HIGH_CM_A	0x04u
#define PDL_TMR_OUTPUT_INV_CM_A		0x08u
#define PDL_TMR_OUTPUT_IGNORE_CM_B	0x10u
#define PDL_TMR_OUTPUT_LOW_CM_B		0x20u
#define PDL_TMR_OUTPUT_HIGH_CM_B	0x40u
#define PDL_TMR_OUTPUT_INV_CM_B		0x80u

/* Channels and units */
#define PDL_TMR_TMR0	0
#define PDL_TMR_TMR1	1
#define PDL_TMR_TMR2	2
#define PDL_TMR_TMR3	3
#define PDL_TMR_UNIT0	4
#define PDL_TMR_UNIT1	5

/* Period or frequency selection */
#define PDL_TMR_PERIOD						0x00000001ul
#define PDL_TMR_FREQUENCY					0x00000002ul

/* Output pin control */
#define PDL_TMR_OUTPUT_HIGH					0x00000004ul
#define PDL_TMR_OUTPUT_LOW					0x00000008ul
#define PDL_TMR_OUTPUT_OFF					0x00000010ul
#define PDL_TMR_OUTPUT_ENABLE				0x00000020ul
#define PDL_TMR_OUTPUT_DISABLE				0x00000040ul

/* ADC trigger control */
#define PDL_TMR_ADC_TRIGGER_ON				0x00000080ul
#define PDL_TMR_ADC_TRIGGER_OFF				0x00000100ul

/* Pulse DTC trigger control */
#define PDL_TMR_PULSE_DTC_TRIGGER_DISABLE	0x00000200ul
#define PDL_TMR_PULSE_DTC_TRIGGER_ENABLE	0x00000400ul

/* Period DTC trigger control */
#define PDL_TMR_PERIOD_DTC_TRIGGER_DISABLE	0x00000800ul
#define PDL_TMR_PERIOD_DTC_TRIGGER_ENABLE	0x00001000ul

/* CPU control */
#define PDL_TMR_CPU_ON						0x00002000ul
#define PDL_TMR_CPU_OFF						0x00004000ul

/* Timer counter control */
#define PDL_TMR_STOP						0x00008000ul
#define PDL_TMR_START						0x00010000ul

/* Register selections */
#define PDL_TMR_COUNTER						0x00020000ul
#define PDL_TMR_TIME_CONSTANT_A				0x00040000ul
#define PDL_TMR_TIME_CONSTANT_B				0x00080000ul

#endif
/* End of file */
