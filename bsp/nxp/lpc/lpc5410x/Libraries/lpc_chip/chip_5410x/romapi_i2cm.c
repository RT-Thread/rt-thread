/*
 * @brief I2C master ROM API declarations and functions
 * These are the public ROM APIs and functions of the I2C master
 * driver.
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

/* Get memory size in bytes needed for I2C master driver context */
uint32_t ROM_I2CM_GetMemSize(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CM_API->GetMemSize();
#else
	return i2cm_api.GetMemSize();
#endif
}

/* Initialize I2C master peripheral */
ROM_I2CM_HANDLE_T ROM_I2CM_Init(void *mem, const ROM_I2CM_INIT_T *pInit)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CM_API->Init(mem, pInit);
#else
	return i2cm_api.Init(mem, pInit);
#endif
}

/* Set I2C master clock rate */
uint32_t ROM_I2CM_SetClockRate(ROM_I2CM_HANDLE_T pHandle, uint32_t inRate, uint32_t i2cRate)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CM_API->SetClockRate(pHandle, inRate, i2cRate);
#else
	return i2cm_api.SetClockRate(pHandle, inRate, i2cRate);
#endif
}

/* Register a I2C master callback */
void ROM_I2CM_RegisterCallback(ROM_I2CM_HANDLE_T pHandle, ROM_I2CM_CALLBACK_T cbIndex, void *pCB)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_I2CM_API->RegisterCallback(pHandle, cbIndex, pCB);
#else
	i2cm_api.RegisterCallback(pHandle, cbIndex, pCB);
#endif
}

/* Start a I2C master transfer */
ErrorCode_t ROM_I2CM_Transfer(ROM_I2CM_HANDLE_T pHandle, ROM_I2CM_XFER_T *pXfer)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CM_API->Transfer(pHandle, pXfer);
#else
	return i2cm_api.Transfer(pHandle, pXfer);
#endif
}

/* I2C master transfer (interrupt) handler */
void ROM_I2CM_TransferHandler(ROM_I2CM_HANDLE_T pHandle)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_I2CM_API->TransferHandler(pHandle);
#else
	i2cm_api.TransferHandler(pHandle);
#endif
}

/* Return the I2C master ROM driver version */
uint16_t ROM_I2CM_GetDriverVersion(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_I2CM_API->GetDriverVersion();
#else
	return i2cm_api.GetDriverVersion();
#endif
}
