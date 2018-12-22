/*""FILE COMMENT""*******************************************************
* System Name	: Timer TMR API for RX62Nxx
* File Name		: r_pdl_tmr_RX62Nxx.h
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

#ifndef R_PDL_TMR_RX62Nxx_H
#define R_PDL_TMR_RX62Nxx_H

#define TMR_UNITS 				2
#define TMR_CHANNELS_PER_UNIT	2
#define TMR_CHANNELS (uint8_t)(TMR_UNITS * TMR_CHANNELS_PER_UNIT)

/* One-shot modes */
#define CHANNEL_MODE	0x01u
#define UNIT_MODE		0x02u

/* Callback function storage */
extern VoidCallBackFunc rpdl_TMR_Overflow_callback_func[TMR_CHANNELS];
extern VoidCallBackFunc rpdl_TMR_CMA_callback_func[TMR_CHANNELS];
extern VoidCallBackFunc rpdl_TMR_CMB_callback_func[TMR_CHANNELS];

/* Global variables */
extern volatile  uint8_t rpdl_TMR_tcsr_setting[TMR_CHANNELS];
extern volatile  uint8_t rpdl_TMR_tccr8_setting[TMR_CHANNELS];
extern volatile uint16_t rpdl_TMR_tccr16_setting[TMR_UNITS];
extern volatile  uint8_t rpdl_TMR_one_shot[TMR_CHANNELS];

/* Library prototypes */
bool R_TMR_SetAll(
	const uint8_t
);
bool R_TMR_CreateChannelAll(
	const uint8_t,
	const uint32_t,
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_TMR_CreateUnitAll(
	const uint8_t,
	const uint32_t,
	const uint8_t,
	const uint16_t,
	const uint16_t,
	const uint16_t,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_TMR_CreatePeriodicChannelAll(
	const uint8_t,
	const uint32_t,
	const float,
	const float,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_TMR_CreatePeriodicUnitAll(
	const uint8_t,
	const uint32_t,
	const float,
	const float,
	VoidCallBackFunc const,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_TMR_CreateOneShotChannelAll(
	const uint8_t,
	const uint32_t,
	const float,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_TMR_CreateOneShotUnitAll(
	const uint8_t,
	const uint32_t,
	const float,
	VoidCallBackFunc const,
	const uint8_t
);
bool R_TMR_DestroyAll(
	const uint8_t
);
bool R_TMR_ControlChannelAll(
	const uint8_t,
	const uint32_t,
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_TMR_ControlUnitAll(
	const uint8_t,
	const uint32_t,
	const uint16_t,
	const uint16_t,
	const uint16_t
);
bool R_TMR_ControlPeriodicChannelAll(
	const uint8_t,
	const uint32_t,
	const float,
	const float
);
bool R_TMR_ControlPeriodicUnitAll(
	const uint8_t,
	const uint32_t,
	const float,
	const float
);
bool R_TMR_ReadChannelAll(
	const uint8_t,
	volatile uint8_t * const,
	volatile uint8_t * const,
	volatile uint8_t * const,
	volatile uint8_t * const
);
bool R_TMR_ReadUnitAll(
	const uint8_t,
	volatile uint8_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const
);
bool ReturnFalse(void);

/* Macro definitions */

#if defined (DEVICE_PACKAGE_LFBGA_176) || defined (DEVICE_PACKAGE_TFLGA_145) || \
	defined (DEVICE_PACKAGE_LQFP_144)
#define R_TMR_Set(a) \
( R_TMR_SetAll( (a) ) )
#else
#define R_TMR_Set(a) \
( ReturnFalse() )
#endif

#define R_TMR_CreateChannel(a, b, c, d, e, f, g, h, i, j) \
( \
( ((a) < TMR_CHANNELS) && ((j) <= IPL_MAX) ) ? \
R_TMR_CreateChannelAll( (a), (b), (c), (d), (e), (f), (g), (h), (i), (j) ) : \
ReturnFalse() \
)

#define R_TMR_CreateUnit(a, b, c, d, e, f, g, h, i, j) \
( \
( ((a) < TMR_UNITS) && ((j) <= IPL_MAX) ) ? \
R_TMR_CreateUnitAll( (a), (b), (c), (d), (e), (f), (g), (h), (i), (j) ): \
ReturnFalse() \
)

#define R_TMR_CreatePeriodic(a, b, c, d, e, f, g) \
( \
( ((a) > PDL_TMR_UNIT1) || ((g) > IPL_MAX) ) ? \
ReturnFalse() : \
( (a) <= PDL_TMR_TMR3) ? \
R_TMR_CreatePeriodicChannelAll( (a), (b), (c), (d), (e), (f), (g) ) : \
R_TMR_CreatePeriodicUnitAll( (a - PDL_TMR_UNIT0), (b), (c), (d), (e), (f), (g) ) \
)

#define R_TMR_CreateOneShot(a, b, c, d, e) \
( \
( ((a) > PDL_TMR_UNIT1) || ((e) > IPL_MAX) ) ? \
ReturnFalse() : \
( (a) <= PDL_TMR_TMR3 ) ? \
R_TMR_CreateOneShotChannelAll( (a), (b), (c), (d), (e) ) : \
R_TMR_CreateOneShotUnitAll( (a - PDL_TMR_UNIT0), (b), (c), (d), (e) ) \
)

#define R_TMR_Destroy(a) \
( \
( (a) < TMR_UNITS ) ? \
R_TMR_DestroyAll( (a) ) : \
ReturnFalse() \
)

#define R_TMR_ControlChannel(a, b, c, d, e) \
( \
( (a) < TMR_CHANNELS ) ? \
R_TMR_ControlChannelAll( (a), (b), (c), (d), (e) ) : \
ReturnFalse() \
)

#define R_TMR_ControlUnit(a, b, c, d, e) \
( \
( (a) < TMR_UNITS ) ? \
R_TMR_ControlUnitAll( (a), (b), (c), (d), (e) ): \
ReturnFalse() \
)

#define R_TMR_ControlPeriodic(a, b, c, d) \
( \
( (a) > PDL_TMR_UNIT1 ) ? \
ReturnFalse() : \
( (a) <= PDL_TMR_TMR3 ) ? \
R_TMR_ControlPeriodicChannelAll( (a), (b), (float)(c), (float)(d) ) : \
R_TMR_ControlPeriodicUnitAll( (a - PDL_TMR_UNIT0), (b), (float)(c), (float)(d) ) \
)

#define R_TMR_ReadChannel(a, b, c, d, e) \
( \
( (a) < TMR_CHANNELS ) ? \
R_TMR_ReadChannelAll( (a), (b), (c), (d), (uint8_t *)(e) ) : \
ReturnFalse() \
)

#define R_TMR_ReadUnit(a, b, c, d, e) \
( \
( (a) < TMR_UNITS ) ? \
R_TMR_ReadUnitAll( (a), (b), (c), (d), (e) ) : \
ReturnFalse() \
)

#endif
/* End of file */
