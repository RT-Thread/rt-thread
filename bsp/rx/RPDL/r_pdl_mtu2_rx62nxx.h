/*""FILE COMMENT""*******************************************************
* System Name	: Multi-function Timer Pulse Unit API for RX62N
* File Name		: r_pdl_MTU2_RX62Nxx.h
* Version		: 1.02
* Contents		: MTU2 API header
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

#ifndef R_PDL_MTU2_RX62Nxx_H
#define R_PDL_MTU2_RX62Nxx_H

#define MTU2_UNITS 				2
#define MTU2_CHANNELS_PER_UNIT	6
#define MTU2_CHANNELS (uint8_t)(MTU2_UNITS * MTU2_CHANNELS_PER_UNIT)

/* Callback function storage */
extern VoidCallBackFunc rpdl_MTU2_func1_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_func2_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_func3_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_func4_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_TGRE_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_TGRF_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_Overflow_callback_func[MTU2_CHANNELS];
extern VoidCallBackFunc rpdl_MTU2_Underflow_callback_func[MTU2_CHANNELS];

typedef struct R_MTU2_Create_parameters
{
	uint32_t data2;
	uint32_t data3;
	uint32_t data4;
	uint16_t data5;
	uint32_t data6;
	uint32_t data7;
	uint32_t data8;
	uint16_t data9;
	uint16_t data10;
	uint16_t data11;
	uint16_t data12;
	uint16_t data13;
	uint16_t data14;
	uint16_t data15;
	uint16_t data16;
	uint16_t data17;
	uint16_t data18;
	VoidCallBackFunc func1;
	VoidCallBackFunc func2;
	VoidCallBackFunc func3;
	VoidCallBackFunc func4;
	uint8_t data19;
	VoidCallBackFunc func5;
	VoidCallBackFunc func6;
	VoidCallBackFunc func7;
	VoidCallBackFunc func8;
	uint8_t data20;
} R_MTU2_Create_structure;

typedef struct R_MTU2_ControlChannel_parameters
{
	uint8_t data2;
	uint16_t data3;
	uint16_t data4;
	uint16_t data5;
	uint16_t data6;
	uint16_t data7;
	uint16_t data8;
	uint16_t data9;
	uint16_t data10;
	uint16_t data11;
	uint16_t data12;
} R_MTU2_ControlChannel_structure;

typedef struct R_MTU2_ControlUnit_parameters
{
	uint16_t data2;
	uint32_t data3;
	uint32_t data4;
	uint16_t data5;
	uint32_t data6;
	uint8_t data7;
	uint16_t data8;
	uint16_t data9;
	uint16_t data10;
} R_MTU2_ControlUnit_structure;

/* Library prototypes */
bool R_MTU2_SetAll(
	const uint16_t
);
bool R_MTU2_CreateAll(
	const uint8_t,
	R_MTU2_Create_structure * const
);
bool R_MTU2_DestroyAll(
	const uint8_t
);
bool R_MTU2_ControlChannelAll(
	const uint8_t,
	R_MTU2_ControlChannel_structure * const
);
bool R_MTU2_ControlUnitAll(
	const uint8_t,
	R_MTU2_ControlUnit_structure * const
);
bool R_MTU2_ReadChannelAll(
	const uint8_t,
	volatile uint8_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const
);
bool R_MTU2_ReadUnitAll(
	const uint8_t,
	volatile uint16_t * const,
	volatile uint8_t * const
);
bool ReturnFalse(void);
void R_MTU2_Create_load_defaults(R_MTU2_Create_structure * const);

/* Macro definitions */

#define R_MTU2_Set(a) \
( \
R_MTU2_SetAll( (a) ) \
)

#define R_MTU2_Create(a, b) \
( \
( (a) < MTU2_CHANNELS ) ? \
R_MTU2_CreateAll( (a), (b) ) : \
ReturnFalse() \
)

#define R_MTU2_ControlChannel(a, b) \
( \
( (a) < MTU2_CHANNELS ) ? \
R_MTU2_ControlChannelAll( (a), (b) ) : \
ReturnFalse() \
)

#define R_MTU2_ControlUnit(a, b) \
( \
( (a) < MTU2_UNITS ) ? \
R_MTU2_ControlUnitAll( (a), (b) ) : \
ReturnFalse() \
)

#define R_MTU2_ReadChannel(a, b, c, d, e, f, g, h, i) \
( \
( (a) < MTU2_CHANNELS ) ? \
R_MTU2_ReadChannelAll( (a), (b), (c), (d), (e), (f), (g), (h), (i) ) : \
ReturnFalse() \
)

#define R_MTU2_ReadUnit(a, b, c) \
( \
( (a) < MTU2_UNITS ) ? \
R_MTU2_ReadUnitAll( (a), (b), (c) ) : \
ReturnFalse() \
)

#define R_MTU2_Destroy(a) \
( \
( (a) < MTU2_UNITS ) ? \
R_MTU2_DestroyAll( (a) ) : \
ReturnFalse() \
)

#endif
/* End of file */
