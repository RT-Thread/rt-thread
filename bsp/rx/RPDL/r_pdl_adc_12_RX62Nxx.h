/*""FILE COMMENT""*******************************************************
* System Name	: 12-bit A/D converter API for RX62Nxx
* File Name		: r_pdl_adc_12_RX62Nxx.h
* Version		: 1.02
* Contents		: ADC_12 header
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

#ifndef R_PDL_ADC_12_RX62Nxx_H
#define R_PDL_ADC_12_RX62Nxx_H

extern VoidCallBackFunc rpdl_ADC_12_callback_func[];

#define ADC_12_UNITS 1

/* Library prototypes */
bool R_ADC_12_CreateAll(
	const uint8_t,
	const uint32_t,
	const uint16_t,
	const uint16_t,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_ADC_12_DestroyAll(
	const uint8_t
);
bool R_ADC_12_ControlAll(
	const uint8_t
);
bool R_ADC_12_ReadAll(
	const uint8_t,
	volatile uint16_t * const
);
bool ReturnFalse(void);

/* Macro definitions */

#define R_ADC_12_Create(a, b, c, d, e, f) \
( \
( ( ((a) < ADC_12_UNITS) && ((f) <= IPL_MAX) ) ) ? \
R_ADC_12_CreateAll( (a), (b), (c), (d), (e), (f)): \
ReturnFalse() \
)

#define R_ADC_12_Destroy(a) \
( \
( (a) < ADC_12_UNITS ) ? \
R_ADC_12_DestroyAll( (a) ): \
ReturnFalse() \
)

#define R_ADC_12_Control(a) \
( \
R_ADC_12_ControlAll( (a) ) \
)

#define R_ADC_12_Read(a, b) \
( \
( (a) < ADC_12_UNITS ) ? \
R_ADC_12_ReadAll( (a), (b) ): \
ReturnFalse() \
)

#endif
/* End of file */
