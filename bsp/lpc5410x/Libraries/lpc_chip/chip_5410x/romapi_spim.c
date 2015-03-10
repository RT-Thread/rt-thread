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

#include "romapi_5410x.h"

/* Get memory size in bytes needed for SPI master driver context */
uint32_t ROM_SPIM_GetMemSize(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_SPIM_API->GetMemSize();
#else
	return spim_api.GetMemSize();
#endif
}

/* Initialize SPI master peripheral */
ROM_SPIM_HANDLE_T ROM_SPIM_Init(void *mem, ROM_SPIM_INIT_T *pInit)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_SPIM_API->Init(mem, pInit);
#else
	return spim_api.Init(mem, pInit);
#endif
}

void ROM_SPIM_RegisterCallback(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_CALLBACK_T cbIndex, void *pCB)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_SPIM_API->RegisterCallback(pHandle, cbIndex, pCB);
#else
	spim_api.RegisterCallback(pHandle, cbIndex, pCB);
#endif
}

ErrorCode_t ROM_SPIM_SetupTransfer(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_CONFIG_T *pCfg)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_SPIM_API->SetupTransfer(pHandle, pCfg);
#else
	return spim_api.SetupTransfer(pHandle, pCfg);
#endif
}

ErrorCode_t ROM_SPIM_Transfer(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_T *pXfer)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_SPIM_API->Transfer(pHandle, pXfer);
#else
	return spim_api.Transfer(pHandle, pXfer);
#endif
}

void ROM_SPIM_TransferHandler(ROM_SPIM_HANDLE_T pHandle)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_SPIM_API->TransferHandler(pHandle);
#else
	spim_api.TransferHandler(pHandle);
#endif
}

void ROM_SPIM_ClosePendingTransfer(ROM_SPIM_HANDLE_T pHandle)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_SPIM_API->ClosePendingTransfer(pHandle);
#else
	spim_api.ClosePendingTransfer(pHandle);
#endif
}

/* Return the SPI master ROM driver version */
uint16_t ROM_SPIM_GetDriverVersion(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_SPIM_API->GetDriverVersion();
#else
	return spim_api.GetDriverVersion();
#endif
}
