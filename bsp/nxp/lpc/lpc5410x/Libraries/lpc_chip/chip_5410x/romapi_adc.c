/*
 * @brief ADC ROM API declarations and functions
 * These are the public ROM APIs and functions of the ADC ROM
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

/* Get memory size in bytes needed for ADC driver context */
uint32_t ROM_ADC_GetMemSize(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->GetMemSize();
#else
	return adcrom_api.GetMemSize();
#endif
}

/* Initialize the ADC ROM driver */
ADC_HANDLE_T ROM_ADC_Init(void *pMem, uint32_t baseAddr, void *pUserData)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->Init(pMem, baseAddr, pUserData);
#else
	return adcrom_api.Init(pMem, baseAddr, pUserData);
#endif
}

/* Configure the ADC peripheral */
ErrorCode_t ROM_ADC_Configure(ADC_HANDLE_T hADC, const ADC_CFG_T *pCfg)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->Configure(hADC, pCfg);
#else
	return adcrom_api.Configure(hADC, pCfg);
#endif
}

/* Calibrate the ADC */
ErrorCode_t ROM_ADC_Calibrate(ADC_HANDLE_T hADC, uint32_t sysclk_freq)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->Calibrate(hADC, sysclk_freq);
#else
	return adcrom_api.Calibrate(hADC, sysclk_freq);
#endif
}

/* Start the conversion on given SEQ */
ErrorCode_t ROM_ADC_StartConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex, void *pBuf, size_t bufCount)
{
#if defined(ROMDRIVERSV2_PRESENT)
	/* Correct index adjust bug */
	uint32_t *ptr = &((uint32_t *)hADC)[9 + seqIndex * 6];
	if (*ptr != 2) *(ptr - 1) = 0;

	return ROMAPI_ADC_API->StartConversion(hADC, seqIndex, pBuf, bufCount);
#else
	return adcrom_api.StartConversion(hADC, seqIndex, pBuf, bufCount);
#endif
}

/* ADC Event handler */
ErrorCode_t ROM_ADC_Handler(ADC_HANDLE_T hADC, ADC_HEVENT_T hEvent)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->Handler(hADC, hEvent);
#else
	return adcrom_api.Handler(hADC, hEvent);
#endif
}

/* ADC Callback register */
ErrorCode_t ROM_ADC_RegisterCB(ADC_HANDLE_T hADC, ADC_CBINDEX_T cbIndex, void (*pCbFunc)(ADC_HANDLE_T,
																						 ADC_CBINDEX_T,
																						 void *))
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->RegisterCB(hADC, cbIndex, pCbFunc);
#else
	return adcrom_api.RegisterCB(hADC, cbIndex, pCbFunc);
#endif
}

/* Set Threshold register values */
void ROM_ADC_SetThreshold(ADC_HANDLE_T hADC, uint32_t valThr0, uint32_t valThr1)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_ADC_API->SetThreshold(hADC, valThr0, valThr1);
#else
	adcrom_api.SetThreshold(hADC, valThr0, valThr1);
#endif
}

/* Configure ADC channel */
ErrorCode_t ROM_ADC_ConfigureCh(ADC_HANDLE_T hADC, uint32_t chanNum, uint32_t chanOpts)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->ConfigureCh(hADC, chanNum, chanOpts);
#else
	return adcrom_api.ConfigureCh(hADC, chanNum, chanOpts);
#endif
}

/* Stop conversion of Analog samples */
ErrorCode_t ROM_ADC_StopConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->StopConversion(hADC, seqIndex);
#else
	return adcrom_api.StopConversion(hADC, seqIndex);
#endif
}

/* Generate a software trigger */
ErrorCode_t ROM_ADC_SwTrigger(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->SwTrigger(hADC, seqIndex);
#else
	return adcrom_api.SwTrigger(hADC, seqIndex);
#endif
}

/* Get Current verion of the driver */
uint16_t ROM_ADC_GetDriverVersion(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_ADC_API->GetDriverVersion();
#else
	return adcrom_api.GetDriverVersion();
#endif
}
