/*
 * @brief I2C slave ROM API declarations and functions
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

#ifndef __ROMAPI_I2CS_H_
#define __ROMAPI_I2CS_H_

#include "hw_i2csd.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_I2CS_WRAPPER CHIP: I2C slave ROM wrapper functions
 * @ingroup ROMAPI_5410X
 * @{
 */

/**
 * @brief	Get memory size in bytes needed for I2C slave driver context
 * @return	Size in bytes needed for the ROM driver
 */
uint32_t ROM_I2CS_GetMemSize(void);

/**
 * @brief	Initialize I2C slave peripheral
 * @param	mem		: Pointer to memory area used to driver context
 * @param	pInit	: Pointer to I2C slave init data
 * @return	NULL on error, or a pointer to the device context handle
 */
ROM_I2CS_HANDLE_T ROM_I2CS_Init(void *mem, ROM_I2CS_INIT_T *pInit);

/**
 * @brief	Set I2C slave clock rate
 * @param	pHandle		: Pointer to driver context handle
 * @param	pSlaveSetup	: Slave setup data
 * @return	Nothing
 * @note	See the use model for more information on how to setup slave addresses.
 */
void ROM_I2CS_SetupSlave(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_SLAVE_T *pSlaveSetup);

/**
 * @brief	Register a I2C slave callback
 * @param	pHandle	: Pointer to driver context handle
 * @param	cbIndex	: Callback to register
 * @param	pCB		: Pointer to callback function
 * @return	Nothing
 */
void ROM_I2CS_RegisterCallback(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_CALLBACK_T cbIndex, void *pCB);

/**
 * @brief	Queues an I2C slave transfer
 * @param	pHandle	: Pointer to driver context handle
 * @param	pXfer	: Pointer to slave transfer configuration
 * @return	Always returns LPC_OK
 * @note	This functions never blocks.
 */
ErrorCode_t ROM_I2CS_Transfer(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_XFER_T *pXfer);

/**
 * @brief	I2C slave transfer (interrupt) handler
 * @param	pHandle	: Pointer to driver context handle
 * @return	Nothing
 * @note	This function should be called from the I2C interrupt handler and
 * is used in interrupt and DMA modes.
 */
void ROM_I2CS_TransferHandler(ROM_I2CS_HANDLE_T pHandle);

/**
 * @brief	Return the I2C slave ROM driver version
 * @return	Driver version number
 * @note	The returned driver version number consists of a major and minor
 * number, with the minor number in the lower 8 bits and the major number in
 * the upper 8 bits.
 */
uint16_t ROM_I2CS_GetDriverVersion(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROMAPI_I2CS_H_ */
