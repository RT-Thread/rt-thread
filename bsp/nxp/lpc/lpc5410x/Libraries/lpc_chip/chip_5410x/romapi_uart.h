/*
 * @brief UART ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __ROMAPI_UART_H_
#define __ROMAPI_UART_H_

#include "hw_uart_rom_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_UART_WRAPPER CHIP: UART ROM wrapper functions
 * @ingroup ROMAPI_5410X
 * @{
 */

/**
 * @brief	Get memory size in bytes needed for SPI master driver context
 * @return	Size in bytes needed for the ROM driver
 */
uint32_t ROM_UART_GetMemSize(void);

/**
 * @brief	Initialize UART ROM Driver
 * @param	pMem		: Pointer to memory area for driver context
 * @param	baseAddr	: Base address of the UART peripheral
 * @param	pUserData	: Pointer to User Data
 * @return	Pointer to the device context handle or NULL on alignment failure
 * @note	Parameter @a pMem must be a pointer to word aligned memory
 *          if the pointer is not word aligned (4-Byte) the function returns
 *          NULL.
 */
UART_HANDLE_T ROM_UART_Init(void *pMem, uint32_t baseAddr, void *pUserData);

/**
 * @brief	Configure the UART peripheral
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	pCfg	: Pointer to configuration structure #UART_CFG_T
 * @return	LPC_OK on Success, ERR_UART_PARAM if any of cfg values are invalid
 */
ErrorCode_t ROM_UART_Configure(UART_HANDLE_T hUART, const UART_CFG_T *pCfg);

/**
 * @brief	Calculate UART Baud rate parameters
 * @param	baud	: [IN/OUT] Pointer to baud rate structure
 * @return	LPC_OK on Success, ERR_UART_BAUDRATE baudrate for given frequency is not within limits
 * @sa		UART_BAUD_T
 */
ErrorCode_t ROM_UART_CalBaud(UART_BAUD_T *baud);

/**
 * @brief	Set UART Control operations
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	cfgVal	: Configuration value (one or more (OR'ed) values of #UART_BREAK_ON, #UART_TX_PAUSE etc)
 * @return	Nothing
 * @note
 * To set TX in BREAK state, use <b>ROM_UART_SetCtrl(hUART, UART_BREAK_ON)</b>, to bring TX out of BREAK state
 * use <b>ROM_UART_SetCtrl(hUART, UART_BREAK_OFF)</b>. Us the above method will set TX line to BREAK state even
 * if there is a data is being sent, hence the receiver might get a UART FRAME error and the data in progress might
 * get lost. To avoid this application can pause TX before the TX gets to BREAK state by calling, <b>
 * ROM_UART_SetCtrl(hUART, #UART_BREAK_ON | #UART_TX_PAUSE)</b> and release the break by calling <b>
 * ROM_UART_SetCtrl(hUART, #UART_BREAK_OFF | #UART_TX_RESUME)</b>.<br>
 * <b>ROM_UART_SetCtrl(hUART, #UART_TX_PAUSE)</b> will stop the TX until <b>ROM_UART_SetCtrl(hUART,
 * #UART_TX_RESUME)</b> * this could be used to implement flow-control.
 */
void ROM_UART_SetCtrl(UART_HANDLE_T hUART, uint32_t cfgVal);

/**
 * @brief	Registers a callback function associated with an event
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	cbIndex	: Index of the call-back function (Associated with an event)
 * @param	pCbFunc	: Pointer to callback function
 * @return	Success or failure
 * @retval	LPC_OK			Callback successfully registered
 * @retval	ERR_UART_PARAM	Invaild event parameter for @a cbIndex
 */
ErrorCode_t ROM_UART_RegisterCB(UART_HANDLE_T hUART, UART_CBINDEX_T cbIndex, void (*pCbFunc)(UART_HANDLE_T,
																							 UART_EVENT_T,
																							 void *));

/**
 * @brief	UART Event handler function (Usually called from interrupt handler)
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @return	Nothing
 */
void ROM_UART_Handler(UART_HANDLE_T hUART);

/**
 * @brief	Send data to UART
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	buffer	: Buffer to send
 * @param	size	: Number of items in buffer
 * @return	LPC_OK when buffer is queued successfully for sending
 * @note	If the UART Data size is 9, then buffer should be of type
 * uint16_t *, size should be number of uint16_t (not size in bytes).
 */
ErrorCode_t ROM_UART_Send(UART_HANDLE_T hUART, const void *buffer, uint16_t size);

/**
 * @brief	Receive data from UART
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	buffer	: Buffer to send
 * @param	size	: Number of items in buffer
 * @return	LPC_OK when buffer is queued successfully for receiving data
 * @note	If the UART Data size is 9, then buffer should be of type
 * uint16_t *, size should be number of uint16_t (not size in bytes).
 */
ErrorCode_t ROM_UART_Receive(UART_HANDLE_T hUART, void *buffer, uint16_t size);

/**
 * @brief	Send data to UART [Blocking]
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	buffer	: Buffer to send
 * @param	size	: Number of items in buffer
 * @return	LPC_OK when buffer is queued successfully for sending
 * @note	If the UART Data size is 9, then buffer should be of type
 * uint16_t *, size should be number of uint16_t (not size in bytes).
 * <b> This API is not in the ROM this is a wrapper API, that uses
 * @a ROM_UART_Send() and @a ROM_UART_FlushTx()</b>
 */
ErrorCode_t ROM_UART_SendBlock(UART_HANDLE_T hUART, const void *buffer, uint16_t size);

/**
 * @brief	Receive data from UART [Blocking]
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @param	buffer	: Buffer to send
 * @param	size	: Number of items in buffer
 * @return	LPC_OK when buffer is queued successfully for receiving data
 * @note	If the UART Data size is 9, then buffer should be of type
 * uint16_t *, size should be number of uint16_t (not size in bytes).
 * <b> This API is not in the ROM this is a wrapper API, that uses
 * @a ROM_UART_Receive() and @a ROM_UART_FetchRx()</b>
 */
ErrorCode_t ROM_UART_ReceiveBlock(UART_HANDLE_T hUART, void *buffer, uint16_t size);

/**
 * @brief	Wait for the current TX buffer to be sent
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @return	Nothing
 * @note	This call will bock the excution till all the data bytes are sent.
 * @sa		ROM_UART_Send()
 */
void ROM_UART_WaitTx(UART_HANDLE_T hUART);

/**
 * @brief	Complete the current Receive transfer
 * @param	hUART	: Handle to UART obtained using ROM_UART_Init()
 * @return	Nothing
 * @note	This call will bock the excution till all the data bytes are read,
 * if there is no RX in progress this call will read and discard the current
 * pending RX data and the incoming data until there is no data coming from uart
 * atleast for one data time, mainly used for discarding UART frames that had
 * started arriving and overflown before the ROM_UART_Receive was called.
 * @sa		ROM_UART_Receive()
 */
void ROM_UART_WaitRx(UART_HANDLE_T hUART);

/**
 * @brief	Return the UART ROM driver version
 * @return	Driver version number
 * @note	The returned driver version number consists of a major and minor
 * number, with the minor number in the lower 8 bits and the major number in
 * the upper 8 bits.
 */
uint16_t ROM_UART_GetDriverVersion(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROMAPI_UART_H_ */
