/*
 * @brief ADC ROM API declarations and functions
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

#ifndef __ROMAPI_ADC_H_
#define __ROMAPI_ADC_H_

#include "hw_adc_rom_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_ADC_WRAPPER CHIP: ADC ROM Driver wrapper functions
 * @ingroup ROMAPI_5410X
 * @{
 */

/**
 * @brief	Get memory size in bytes needed for ADC driver context
 * @return	Size in bytes needed for the ROM driver
 */
uint32_t ROM_ADC_GetMemSize(void);

/**
 * @brief	Initialize ADC ROM Driver
 * @param	pMem		: Pointer to memory area for driver context
 * @param	baseAddr	: Base address of the ADC peripheral
 * @param	pUserData	: Pointer to User Data
 * @return	Pointer to the device context handle or NULL on alignment failure
 * @note	Parameter @a pMem must be a pointer to word aligned memory
 *          if the pointer is not word aligned (4-Byte) the function returns
 *          NULL.
 */
ADC_HANDLE_T ROM_ADC_Init(void *pMem, uint32_t baseAddr, void *pUserData);

/**
 * @brief	Configure the ADC peripheral
 * @param	hADC	: Handle to ADC obtained using ROM_ADC_Init()
 * @param	pCfg	: Pointer to configuration structure #ADC_CFG_T
 * @return	Always returns LPC_OK
 */
ErrorCode_t ROM_ADC_Configure(ADC_HANDLE_T hADC, const ADC_CFG_T *pCfg);

/**
 * @brief	Calibrate ADC upon startup or wakeup after powerdown
 * @pre		ADC must be Initialized and Configured
 * @param	hADC		: Handle to ADC obtained using ROM_ADC_Init()
 * @param	sysclk_freq	: Frequency of the system
 * @return	Result of calibrarion operation
 * @retval	LPC_OK				Calibration is successful
 * @retval	ERR_ADC_NO_POWER	Unable to powerup ADC
 * @retval	ERR_TIME_OUT		Calibration operation timed-out
 */
ErrorCode_t ROM_ADC_Calibrate(ADC_HANDLE_T hADC, uint32_t sysclk_freq);

/**
 * @brief	Start the ADC peripheral
 * @pre		ADC must be properly initialized, Configured and Calibrated
 * @param	hADC		: Handle to ADC obtained using ROM_ADC_Init()
 * @param	seqIndex	: Index of the sequence to start must be one of #ADC_SEQ_A or #ADC_SEQ_B
 * @param	pBuf		: Pointer to buffer (see note below)
 * @param	szBuf		: Size of buffer (see note below)
 * @return	Result of the start operation
 * @retval	LPC_OK		Successfully started ADC sampling on given sequence or
 *                      given buffer is queued successfully (when called from #ADC_BUFFER_DONE
 *                      callback handler)
 * @retval	ERR_ADC_INVALID_SEQUENCE	Parameter @a seqIndex is not one of #ADC_SEQ_A or #ADC_SEQ_B
 * @retval	ERR_BUSY	Already a buffer is active and swap buffer is also configured
 * @note	The size of the buffer must be M x N where M is the number of channels enabled in
 *          sequence @a seqIndex, and N is the number of samples to be converted.
 *          The buffer provided by @a pBuf must be of size M x N x sizeof(uint16_t) bytes(for non-DMA).
 *          Assume that channels 1, 3, 4, 8 are enabled in sequence @a seqIndex and number of
 *          samples to be collected is N, the buffer will be filled with DATA_1[0], DATA_3[0],
 *          DATA_4[0], DATA_8[0], ... , DATA_1[N], DATA_3[N], DATA_4[N], DATA_8[N], note
 *          that the order in which the channels are enabled does not matter they will always be
 *          filled up in ascending order.
 */
ErrorCode_t ROM_ADC_StartConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex, void *pBuf, size_t szBuf);

/**
 * @brief	Handler to handle ADC events
 * @param	hADC	: Handle to ADC obtained using ROM_ADC_Init()
 * @param	hEvent	: Type of the event
 * @return	Event handling results
 * @retval	LPC_OK				Event successfully handled
 * @retval	ERR_ADC_INVALID_SEQUENCE	Event is not for the given sequence
 * @retval	ERR_FAILED		Internal ADC error (Channel enabled but no data available)
 * @retval	ERR_ADC_PARAM	Invaild event parameter for @a hEvent
 */
ErrorCode_t ROM_ADC_Handler(ADC_HANDLE_T hADC, ADC_HEVENT_T hEvent);

/**
 * @brief	Registers a callback function associated with an event
 * @param	hADC	: Handle to ADC obtained using ROM_ADC_Init()
 * @param	cbIndex	: Index of the call-back function (Associated with an event)
 * @param	pCbFunc	: Pointer to callback function
 * @return	Success or failure
 * @retval	LPC_OK			Callback successfully registered
 * @retval	ERR_ADC_PARAM	Invaild event parameter for @a cbIndex
 */
ErrorCode_t ROM_ADC_RegisterCB(ADC_HANDLE_T hADC, ADC_CBINDEX_T cbIndex, void (*pCbFunc)(ADC_HANDLE_T,
																						 ADC_CBINDEX_T,
																						 void *));

/**
 * @brief	Setup high and low threshold values for threshold 0, 1
 * @param	hADC	: Handle to ADC obtained using ROM_ADC_Init()
 * @param	valThr0	: Threshold 0 value (bits 31-16 has high value, bits 15-0 has low value)
 * @param	valThr1	: Threshold 1 value (bits 31-16 has high value, bits 15-0 has low value)
 * @return	Nothing
 */
void ROM_ADC_SetThreshold(ADC_HANDLE_T hADC, uint32_t valThr0, uint32_t valThr1);

/**
 * @brief	Configure a single channel
 * @param	hADC		: Handle to ADC obtained using ROM_ADC_Init()
 * @param	chanNum		: Channel number
 * @param	chanOpts	: Options for the channel
 * @return	LPC_OK on success, ERR_ADC_PARAM if @a chanNum is invalid
 */
ErrorCode_t ROM_ADC_ConfigureCh(ADC_HANDLE_T hADC, uint32_t chanNum, uint32_t chanOpts);

/**
 * @brief	Stop the conversion in progress
 * @param	hADC		: Handle to ADC obtained using ROM_ADC_Init()
 * @param	seqIndex	: Sequence that needs to be stopped
 * @return	LPC_OK on success, ERR_ADC_INVALID_SEQUENCE if @a seqIndex is invalid
 */
ErrorCode_t ROM_ADC_StopConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex);

/**
 * @brief	Generate software trigger for given sequence
 * @param	hADC		: Handle to ADC obtained using ROM_ADC_Init()
 * @param	seqIndex	: Sequence that needs to be triggered
 * @return	LPC_OK on success, ERR_ADC_INVALID_SEQUENCE if @a seqIndex is invalid
 */
ErrorCode_t ROM_ADC_SwTrigger(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex);

/**
 * @brief	Return the ADC ROM driver version
 * @return	Driver version number
 * @note	The returned driver version number consists of a major and minor
 * number, with the minor number in the lower 8 bits and the major number in
 * the upper 8 bits.
 */
uint16_t ROM_ADC_GetDriverVersion(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROMAPI_ADC_H_ */
