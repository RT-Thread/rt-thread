/*
 * @brief SPI master ROM API declarations and functions
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

#ifndef __ROMAPI_SPIM_H_
#define __ROMAPI_SPIM_H_

#include "hw_spimd.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_SPIM_WRAPPER CHIP: SPI master ROM wrapper functions
 * @ingroup ROMAPI_5410X
 * @{
 */

/**
 * @brief	Get memory size in bytes needed for SPI master driver context
 * @return	Size in bytes needed for the ROM driver
 */
uint32_t ROM_SPIM_GetMemSize(void);

/**
 * @brief	Initialize SPI master peripheral
 * @param	mem		: Pointer to memory area used to driver context
 * @param	pInit	: Pointer to SPI master init data
 * @return	NULL on error, or a pointer to the device context handle
 */
ROM_SPIM_HANDLE_T ROM_SPIM_Init(void *mem, ROM_SPIM_INIT_T *pInit);

/**
 * @brief	Register a SPI master callback
 * @param	pHandle	: Pointer to driver context handle
 * @param	cbIndex	: Callback to register
 * @param	pCB		: Pointer to callback function
 * @return	Nothing
 */
void ROM_SPIM_RegisterCallback(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_CALLBACK_T cbIndex, void *pCB);

ErrorCode_t ROM_SPIM_SetupTransfer(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_CONFIG_T *pCfg);

/**
 * @brief	Start a SPI master transfer
 * @param	pHandle	: Pointer to driver context handle
 * @param	pXfer	: Pointer to master transfer configuration
 * @return	Error code
 * @note	This function starts the transfer and returns immediately.
 */
ErrorCode_t ROM_SPIM_Transfer(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_T *pXfer);

/**
 * @brief	SPI master transfer (interrupt) handler
 * @param	pHandle	: Pointer to driver context handle
 * @return	Nothing
 * @note	This function should be called from the SPI interrupt handler and
 * is used in interrupt and DMA modes.
 */
void ROM_SPIM_TransferHandler(ROM_SPIM_HANDLE_T pHandle);

/**
 * @brief	Safely stop a SPI master transfer
 * @param	pHandle	: Pointer to driver context handle
 * @return	Nothing
 * @note	This function completes the SPI transfer at the next possible
 * transfer completion state. This should be called when DMA is used and
 * DMA transfer is complete, or whenever the transfer neesd to be aborted.
 * It will safely transmit any data already inside the SPI transmit FIFOs
 * before stopping.
 */
void ROM_SPIM_ClosePendingTransfer(ROM_SPIM_HANDLE_T pHandle);

/**
 * @brief	Return the SPI master ROM driver version
 * @return	Driver version number
 * @note	The returned driver version number consists of a major and minor
 * number, with the minor number in the lower 8 bits and the major number in
 * the upper 8 bits.
 */
uint16_t ROM_SPIM_GetDriverVersion(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROMAPI_SPIM_H_ */
