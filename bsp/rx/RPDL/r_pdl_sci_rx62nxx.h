/*""FILE COMMENT""*******************************************************
* System Name	: Serial Communication Interface API for RX62Nxx
* File Name		: r_pdl_sci_RX62Nxx.h
* Version		: 1.02
* Contents		: Serial Interface API header
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

#ifndef R_PDL_SCI_RX62Nxx_H
#define R_PDL_SCI_RX62Nxx_H

#define SCI_CHANNELS 7

/* Globals */
extern volatile const uint8_t * rpdl_SCI_tx_string_pointer[SCI_CHANNELS];
extern volatile uint8_t * rpdl_SCI_rx_string_pointer[SCI_CHANNELS];
extern volatile uint8_t * rpdl_SCI_rx_string_start[SCI_CHANNELS];
extern volatile uint16_t rpdl_SCI_rx_counter[SCI_CHANNELS];
extern volatile uint16_t rpdl_SCI_tx_counter[SCI_CHANNELS];
extern volatile uint16_t rpdl_SCI_rx_threshold[SCI_CHANNELS];
extern volatile uint16_t rpdl_SCI_tx_threshold[SCI_CHANNELS];
extern volatile uint8_t rpdl_SCI_tx_using_irq[SCI_CHANNELS];
extern volatile uint8_t rpdl_SCI_rx_using_irq[SCI_CHANNELS];
extern volatile uint8_t rpdl_SCI_sync_simultaneous[SCI_CHANNELS];
extern volatile uint8_t rpdl_SCI_MP_mode[SCI_CHANNELS];
extern volatile uint8_t rpdl_SCI_MP_rx_stationID[SCI_CHANNELS];

/* Callback function prototypes */
extern VoidCallBackFunc rpdl_SCI_TX_End_callback_func[SCI_CHANNELS];
extern VoidCallBackFunc rpdl_SCI_RX_End_callback_func[SCI_CHANNELS];
extern VoidCallBackFunc	rpdl_SCI_RX_Error_callback_func[SCI_CHANNELS];

/* Library prototypes */
bool R_SCI_SetAll(
	const uint8_t
);
bool R_SCI_CreateAll(
	const uint8_t,
	const uint32_t,
	const uint32_t,
	const uint8_t
);
bool R_SCI_CreateAsyncAll(
	const uint8_t,
	const uint32_t,
	const uint32_t,
	const uint8_t
);
bool R_SCI_CreateSyncAll(
	const uint8_t,
	const uint32_t,
	const uint32_t,
	const uint8_t
);
bool R_SCI_CreateSmartAll(
	const uint8_t,
	const uint32_t,
	const uint32_t,
	const uint8_t
);
bool R_SCI_DestroyAll(
	const uint8_t
);
bool R_SCI_SendAll(
	const uint8_t,
	const uint16_t,
	volatile const uint8_t * const,
	const uint16_t,
	VoidCallBackFunc const
);
bool R_SCI_SendStationID(
	const uint8_t,
	const uint16_t 
);
bool R_SCI_SendData(
	const uint8_t,
	const uint16_t,
	volatile const uint8_t * const,
	const uint16_t,
	VoidCallBackFunc const
);
bool R_SCI_ReceiveAll(
	const uint8_t,
	const uint16_t,
	volatile uint8_t * const,
	const uint16_t,
	VoidCallBackFunc const,
	VoidCallBackFunc const
);
bool R_SCI_ReceiveStationID(
	const uint8_t,
	const uint16_t,
	VoidCallBackFunc const,
	VoidCallBackFunc const
);
bool R_SCI_ReceiveData(
	const uint8_t,
	const uint16_t,
	volatile uint8_t * const,
	const uint16_t,
	VoidCallBackFunc const,
	VoidCallBackFunc const
);
bool R_SCI_ControlAll(
	const uint8_t,
	const uint8_t
);
bool R_SCI_GetStatusAll(
	const uint8_t,
	volatile uint8_t * const,
	volatile uint8_t * const,
	volatile uint16_t * const,
	volatile uint16_t * const
);
bool ReturnFalse(void);

/* Macro definitions */
#define R_SCI_Set(a) \
( R_SCI_SetAll( (a) ) )

#define R_SCI_Create(a, b, c, d) \
( \
( ((a) >= SCI_CHANNELS) || ((a) == 4) || ((c) == 0) || ((d) > IPL_MAX) )? \
ReturnFalse(): \
R_SCI_CreateAll( (a), (b), (c), (d) )\
)

#define R_SCI_Destroy(a) \
( \
(((a) < SCI_CHANNELS) && ((a) != 4)) ? \
R_SCI_DestroyAll( (a) ): \
ReturnFalse() \
)

#define R_SCI_Send(a, b, c, d, e) \
( \
(((a) < SCI_CHANNELS) && ((a) != 4)) ? \
R_SCI_SendAll( (a), (b), (c), (d), (e) ): \
ReturnFalse() \
)

#define R_SCI_Receive(a, b, c, d, e, f) \
( \
(((a) < SCI_CHANNELS) && ((a) != 4)) ? \
R_SCI_ReceiveAll( (a), (b), (c), (d), (e), (f) ): \
ReturnFalse() \
)

#define R_SCI_Control(a, b) \
( \
(((a) < SCI_CHANNELS) && ((a) != 4)) ? \
R_SCI_ControlAll( (a), (b) ): \
ReturnFalse() \
)

#define R_SCI_GetStatus(a, b, c, d, e) \
( \
(((a) < SCI_CHANNELS) && ((a) != 4)) ? \
R_SCI_GetStatusAll( (a), (b), (c), (d), (e) ): \
ReturnFalse() \
)

#endif
/* End of file */
