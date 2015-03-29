/*""FILE COMMENT""*******************************************************
* System Name	: I/O Port API for RX62N (176-pin LFBGA)
* File Name		: r_pdl_io_port_RX62NxBG.h
* Version		: 1.02
* Contents		: I/O Port API header
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

#ifndef R_PDL_IO_PORT_RX62NxBG_H
#define R_PDL_IO_PORT_RX62NxBG_H

/* Library prototypes */
bool R_IO_PORT_SetAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_ReadControlAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	volatile uint8_t * const
);
bool R_IO_PORT_ReadControlRegisterAll(
	const uint8_t,
	const uint8_t,
	volatile uint8_t * const
);
bool R_IO_PORT_ModifyControlAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_ModifyControlRegisterAll(
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_ReadDataAll(
	const uint8_t,
	const uint8_t,
	volatile uint8_t * const
);
bool R_IO_PORT_ReadDataRegisterAll(
	const uint8_t,
	volatile uint8_t * const
);
bool R_IO_PORT_WriteAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_WriteRegisterAll(
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_CompareAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	VoidCallBackFunc const
);
bool R_IO_PORT_CompareRegisterAll(
	const uint8_t,
	const uint8_t,
	VoidCallBackFunc const
);
bool R_IO_PORT_ModifyDataAll(
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_ModifyDataRegisterAll(
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_WaitAll(
	const uint8_t,
	const uint8_t,
	const uint8_t
);
bool R_IO_PORT_WaitRegisterAll(
	const uint8_t,
	const uint8_t
);
bool ReturnFalse(void);

/* Macro definitions */

/* R_IO_PORT_Set */
/* Call the function if the port number is valid. */
#define R_IO_PORT_Set(a, b) \
( \
( ((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7) ) ? \
R_IO_PORT_SetAll( (uint8_t)((a) >> 8), (uint8_t)(a), (uint8_t)~(a), (b) ) : \
ReturnFalse() \
)

/* R_IO_PORT_ReadControl */
/* Call the function if the port number is valid. */
#define R_IO_PORT_ReadControl(a, b, c) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) ) ? \
R_IO_PORT_ReadControlAll( (uint8_t)((a) >> 8), (uint8_t)(a), (b), (c) ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_ReadControlRegisterAll( (uint8_t)(a), (b), (c) ) : \
ReturnFalse() \
)

/* R_IO_PORT_ModifyControl */
/* Call the function if the port number is valid. */
#define R_IO_PORT_ModifyControl(a, b, c) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) ) ? \
R_IO_PORT_ModifyControlAll( (uint8_t)((a) >> 8), (uint8_t)(a), (uint8_t)~(a), (b), (c) ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_ModifyControlRegisterAll( (uint8_t)(a), (b), (c) ) : \
ReturnFalse() \
)

/* R_IO_PORT_Read */
/* Call the function if the port number is valid. */
#define R_IO_PORT_Read(a, b) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) ) ? \
R_IO_PORT_ReadDataAll( (uint8_t)((a) >> 8), (uint8_t)(a), (b) ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_ReadDataRegisterAll( (uint8_t)(a), (b) ) : \
ReturnFalse() \
)

/* R_IO_PORT_Write */
/* Call the function if the port number is valid. */
#define R_IO_PORT_Write(a, b) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) ) ? \
R_IO_PORT_WriteAll( (uint8_t)((a) >> 8), (uint8_t)(a), (uint8_t)~(a), (b) ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_WriteRegisterAll( (uint8_t)(a), (b) ): \
ReturnFalse() \
)

/* R_IO_PORT_Compare */
/* Call the function if the port number is valid. */
#define R_IO_PORT_Compare(a, b, c) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) ) ? \
R_IO_PORT_CompareAll( (uint8_t)((a) >> 8), (uint8_t)(a), (b), (c) ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_CompareRegisterAll( (uint8_t)(a), (b), (c) ): \
ReturnFalse() \
)

/* R_IO_PORT_Modify */
/* Call the function if the port number is valid. */
#define R_IO_PORT_Modify(a, b, c) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) ) ? \
R_IO_PORT_ModifyDataAll( (uint8_t)((a) >> 8), (uint8_t)(a), (uint8_t)~(a), (b), (c) ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_ModifyDataRegisterAll( (uint8_t)(a), (b), (c) ): \
ReturnFalse() \
)

/* R_IO_PORT_Wait */
/* Call the function if the port number is valid. */
#define R_IO_PORT_Wait(a, b) \
( \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) && (b == 1u) ) ? \
R_IO_PORT_WaitAll( (uint8_t)((a) >> 8), (uint8_t)(a), (uint8_t)(a) ) : \
( (((a) >= PDL_IO_PORT_0_0) && ((a) <= PDL_IO_PORT_G_7)) && (b == 0u) ) ? \
R_IO_PORT_WaitAll( (uint8_t)((a) >> 8), (uint8_t)(a), 0 ) : \
( ((a) >= PDL_IO_PORT_0) && ((a) <= PDL_IO_PORT_G) ) ? \
R_IO_PORT_WaitRegisterAll( (uint8_t)(a), (b) ) : \
ReturnFalse() \
)

#endif
/* End of file */
