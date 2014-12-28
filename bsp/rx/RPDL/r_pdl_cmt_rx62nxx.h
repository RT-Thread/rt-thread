/*""FILE COMMENT""*******************************************************
* System Name	: CMT API for RX62Nxx
* File Name		: r_pdl_cmt_RX62Nxx.h
* Version		: 1.02
* Contents		: CMT API header
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

#ifndef R_PDL_CMT_RX62Nxx_H
#define R_PDL_CMT_RX62Nxx_H

#define CMT_UNITS	2
#define CMT_CHANNELS_PER_UNIT 2
#define CMT_CHANNELS (uint8_t)(CMT_UNITS * CMT_CHANNELS_PER_UNIT)

/* Callback function storage */
extern VoidCallBackFunc rpdl_CMT_callback_func[CMT_CHANNELS];

/* Global variables */
extern volatile uint8_t rpdl_CMT_one_shot[CMT_CHANNELS];

/* Library prototypes */
bool R_CMT_CreateAll(
	const uint8_t,
	const uint16_t,
	const float,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_CMT_CreateOneShotAll(
	const uint8_t,
	const uint16_t,
	const float,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_CMT_DestroyAll(
	const uint8_t
);
bool R_CMT_ControlAll(
	const uint8_t,
	const uint16_t,
	const float
);
bool R_CMT_ReadAll(
	const uint8_t,
	volatile uint8_t * const,
	volatile uint16_t * const
);
bool ReturnFalse(void);

/* Macro definitions */

#define R_CMT_Create(a, b, c, d, e) \
( \
( ( ((a) < CMT_CHANNELS ) && ((e) <= IPL_MAX) ) ) ? \
R_CMT_CreateAll( (a), (b), (c), (d), (e) ) : \
ReturnFalse() \
)

#define R_CMT_CreateOneShot(a, b, c, d, e) \
( \
( ( ((a) < CMT_CHANNELS ) && ((e) <= IPL_MAX) ) ) ? \
R_CMT_CreateOneShotAll( (a), (b), (c), (d), (e) ) : \
ReturnFalse() \
)

#define R_CMT_Destroy(a) \
( \
( (a) < CMT_UNITS ) ? \
R_CMT_DestroyAll( (a) ) : \
ReturnFalse() \
)

#define R_CMT_Control(a, b, c) \
( \
( (a) < CMT_CHANNELS ) ? \
R_CMT_ControlAll( (a), (b), (c) ) : \
ReturnFalse() \
)

#define R_CMT_Read(a, b, c) \
( \
( (a) < CMT_CHANNELS ) ? \
R_CMT_ReadAll( (a), (b), (c) ) : \
ReturnFalse() \
)

#endif
/* End of file */
