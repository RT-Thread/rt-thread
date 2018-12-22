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

#include "romapi_5410x.h"

/* Get memory size in bytes needed for ADC driver context */
uint32_t ROM_UART_GetMemSize(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->GetMemSize();
#else
	return uartrom_api.GetMemSize();
#endif
}

/* Initialize the UART ROM driver */
UART_HANDLE_T ROM_UART_Init(void *pMem, uint32_t baseAddr, void *pUserData)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->Init(pMem, baseAddr, pUserData);
#else
	return uartrom_api.Init(pMem, baseAddr, pUserData);
#endif
}

/* Configure the UART peripheral */
ErrorCode_t ROM_UART_Configure(UART_HANDLE_T hUART, const UART_CFG_T *pCfg)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->Configure(hUART, pCfg);
#else
	return uartrom_api.Configure(hUART, pCfg);
#endif
}

/* Calculate baudrate dividers and oversampling values */
ErrorCode_t ROM_UART_CalBaud(UART_BAUD_T *baud)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->CalBaud(baud);
#else
	return uartrom_api.CalBaud(baud);
#endif
}

/* Set/Clear special control operations like BREAK, IDLE, etc., */
void ROM_UART_SetCtrl(UART_HANDLE_T hUART, uint32_t cfgVal)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_UART_API->SetCtrl(hUART, cfgVal);
#else
	uartrom_api.SetCtrl(hUART, cfgVal);
#endif
}

/* Registers an UART callback function */
ErrorCode_t ROM_UART_RegisterCB(UART_HANDLE_T hUART, UART_CBINDEX_T cbIndex, void (*pCbFunc)(UART_HANDLE_T,
																							 UART_EVENT_T,
																							 void *))
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->RegisterCB(hUART, cbIndex, pCbFunc);
#else
	return uartrom_api.RegisterCB(hUART, cbIndex, pCbFunc);
#endif
}

/* UART Event handler, should be called from the ISR */
void ROM_UART_Handler(UART_HANDLE_T hUART)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_UART_API->Handler(hUART);
#else
	uartrom_api.Handler(hUART);
#endif
}

/* Send data to UART */
ErrorCode_t ROM_UART_Send(UART_HANDLE_T hUART, const void *buffer, uint16_t size)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->Send(hUART, buffer, size);
#else
	return uartrom_api.Send(hUART, buffer, size);
#endif
}

/* Receive data from UART */
ErrorCode_t ROM_UART_Receive(UART_HANDLE_T hUART, void *buffer, uint16_t size)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->Receive(hUART, buffer, size);
#else
	return uartrom_api.Receive(hUART, buffer, size);
#endif
}

/* Wait for UART TX to complete; Used for polling */
void ROM_UART_WaitTx(UART_HANDLE_T hUART)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_UART_API->WaitTx(hUART);
#else
	uartrom_api.WaitTx(hUART);
#endif
}

/* Wait for UART data receive to complete; Used for polling */
void ROM_UART_WaitRx(UART_HANDLE_T hUART)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_UART_API->WaitRx(hUART);
#else
	uartrom_api.WaitRx(hUART);
#endif
}

/* Get Current verion of the UART ROM driver */
uint16_t ROM_UART_GetDriverVersion(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_UART_API->GetDriverVersion();
#else
	return uartrom_api.GetDriverVersion();
#endif
}
