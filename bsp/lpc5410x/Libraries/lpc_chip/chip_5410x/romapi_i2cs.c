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

#include "romapi_5410x.h"

/* Get memory size in bytes needed for I2C slave driver context */
uint32_t ROM_I2CS_GetMemSize(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CS_API->GetMemSize();
#else
	return i2cs_api.GetMemSize();
#endif
}

/* Initialize I2C slave peripheral */
ROM_I2CS_HANDLE_T ROM_I2CS_Init(void *mem, ROM_I2CS_INIT_T *pInit)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CS_API->Init(mem, pInit);
#else
	return i2cs_api.Init(mem, pInit);
#endif
}

/* Set I2C slave clock rate */
void ROM_I2CS_SetupSlave(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_SLAVE_T *pSlaveSetup)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_I2CS_API->SetupSlave(pHandle, pSlaveSetup);
#else
	i2cs_api.SetupSlave(pHandle, pSlaveSetup);
#endif
}

/* Register a I2C slave callback */
void ROM_I2CS_RegisterCallback(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_CALLBACK_T cbIndex, void *pCB)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_I2CS_API->RegisterCallback(pHandle, cbIndex, pCB);
#else
	i2cs_api.RegisterCallback(pHandle, cbIndex, pCB);
#endif
}

/* Start a I2C slave transfer */
ErrorCode_t ROM_I2CS_Transfer(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_XFER_T *pXfer)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CS_API->Transfer(pHandle, pXfer);
#else
	return i2cs_api.Transfer(pHandle, pXfer);
#endif
}

/* I2C slave transfer (interrupt) handler */
void ROM_I2CS_TransferHandler(ROM_I2CS_HANDLE_T pHandle)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_I2CS_API->TransferHandler(pHandle);
#else
	i2cs_api.TransferHandler(pHandle);
#endif
}

/* Return the I2C slave ROM driver version */
uint16_t ROM_I2CS_GetDriverVersion(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CS_API->GetDriverVersion();
#else
	return i2cs_api.GetDriverVersion();
#endif
}
