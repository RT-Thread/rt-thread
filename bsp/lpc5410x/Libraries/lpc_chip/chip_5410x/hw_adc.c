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

#include <string.h>
#include "hw_adc_rom_api.h"

/** @brief	ADC ROM Driver Version */
#define ADC_DRIVER_VERSION 0x0100

/* Internal defines */
#define SEQ_A_MASK     0x7C0C5FFF
#define SEQ_B_MASK     0x5C0C5FFF
#define CTRL_MASK      0x00007F00

#define ADC_STATE_INACTIVE   0
#define ADC_STATE_IDLE       1
#define ADC_STATE_ACTIVE     2

/** @brief	Channel flags offset */
#define CB_THRES(ch)   (1UL << (ch))
#define CB_DATA(ch)    (0x10000UL << (ch))

/* ADC Buffer management */
typedef struct {
	uint16_t        *pCurr;		/* ReceiveBuffer Pointer */
	size_t          szCurr;		/* Receive Count */
	uint16_t        *pNext;		/* Ring Buffer Pointer */
	size_t          szNext;		/* Receive Count */
	uint32_t        idx;		/* Current index */
	int32_t         state;		/* State of ADC */
} ADC_BUFFER_T;

/* ADC Driver internal data structure */
typedef struct {
	void            *pUserData;		/* Pointer to user data */
	ADC_REGS_T      *pREGS;			/* Pointer to Registers */
	uint32_t        valSeq[2];		/* Stored SEQ A/B Values */
	ADC_BUFFER_T    buffer[2];		/* Buffers to store converted data */
	uint32_t        flags;			/* flags */
	uint32_t        regThrSel;		/* Threshold flags */
	uint32_t        regInt;			/* Interrupt register */
	uint32_t        flag1;			/* Flags Extra */
	void(*cbTable[ADC_CBIDX_RESERVED]) (ADC_HANDLE_T, ADC_CBINDEX_T, void *);
} ADC_DRIVER_T;

/* Prototype defines */
static ErrorCode_t ADC_StopConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex);

/* PRIVATE: Invoke a call back function */
static void _ADC_InvokeCallback(ADC_DRIVER_T *pADC, ADC_CBINDEX_T idx, void *param)
{
	if (pADC->cbTable[idx]) {
		pADC->cbTable[idx]((ADC_HANDLE_T) pADC, idx, param);
	}
}

/* PRIVATE: Extract, format data and store into user buffer  */
static ErrorCode_t _ADC_GetData(ADC_DRIVER_T *pADC, ADC_SEQ_INDEX_T seqIndex, uint32_t data)
{
	uint8_t ch = ADC_DR_CHANNEL(data);
	ADC_BUFFER_T *buf = &pADC->buffer[seqIndex];
	uint16_t *pDat = &buf->pCurr[buf->idx++];

	/* Ignore extra data */
	if (!buf->szCurr) {
		return LPC_OK;
	}

	/* If data is not vaild something is wrong! */
	if (!(data & ADC_SEQ_GDAT_DATAVALID)) {
		return ERR_FAILED;
	}

	data >>= 4;
	if (!(pADC->flag1 & (1UL << ch))) {
		data &= 0xFFF;
	}

	*pDat = data;
	/* Invoke the call back for single data read if enabled */
	if (pADC->flags & CB_DATA(ch)) {
		_ADC_InvokeCallback(pADC, ADC_CHDATA, (void *) ((ch << 16) | data));
	}
	return LPC_OK;
}

/* PRIVATE: Reads data from the GDAT or DAT register based on mode of operation */
static ErrorCode_t _ADC_ReadData(ADC_DRIVER_T *pADC, ADC_SEQ_INDEX_T seqIndex)
{
	ADC_REGS_T *pREGS = pADC->pREGS;
	int i;

	/* Check if this is End-of-Seq or End-of-SingleConversion */
	if (!(pADC->valSeq[seqIndex] & ADC_SEQ_CTRL_MODE_EOS)) {
		return _ADC_GetData(pADC, seqIndex, pREGS->SEQ_GDAT[seqIndex]);
	}

	/* Read channels having conversion data */
	for (i = 0; i < sizeof(pREGS->DAT) / sizeof(pREGS->DAT[0]); i++) {
		if (pADC->valSeq[seqIndex] & ADC_SEQ_CTRL_CHANSEL(i)) {
			if (_ADC_GetData(pADC, seqIndex, pREGS->DAT[i]) != LPC_OK) {
				return ERR_FAILED;
			}
		}
	}
	return LPC_OK;
}

/* PRIVATE: Overflow handler */
static ErrorCode_t _ADC_Handle_Overflow(ADC_DRIVER_T *pADC, uint32_t flag)
{
	_ADC_InvokeCallback(pADC, ADC_OVERFLOW, (void *) ((flag >> 12) & 0x3FFF));
	return LPC_OK;
}

/* PRIVATE: ADC Sequence event handler function */
static ErrorCode_t _ADC_Handler_Seq(ADC_DRIVER_T *pADC, ADC_SEQ_INDEX_T seqIndex)
{
	ADC_REGS_T *pREGS = pADC->pREGS;
	ADC_BUFFER_T *buf = &pADC->buffer[seqIndex];
	uint32_t flag = pREGS->FLAGS;
	uint32_t tmp;

	/* Check if overrun is enabled and got an overrun */
	tmp = flag & ADC_FLAGS_SEQN_OVRRUN_MASK(seqIndex);

	if (!(flag & ADC_FLAGS_SEQN_INT_MASK(seqIndex))) {
		return ERR_ADC_INVALID_SEQUENCE;
	}

	if (_ADC_ReadData(pADC, seqIndex) != LPC_OK) {
		return ERR_FAILED;
	}

	/* Handle the overflow */
	if (tmp) {
		_ADC_Handle_Overflow(pADC, flag);
	}

	/* Clear the interrupt if it is for EOS and not EOC */
	if (pADC->valSeq[seqIndex] & ADC_SEQ_CTRL_MODE_EOS) {
		pREGS->FLAGS = ADC_FLAGS_SEQN_INT_MASK(seqIndex);
	}

	/* See if we are done with our buffer */
	if (buf->idx >= buf->szCurr) {
		_ADC_InvokeCallback(pADC, (ADC_CBINDEX_T) (ADC_BUFFER_DONE + (ADC_CBINDEX_T)seqIndex), buf->pCurr);
		if (!buf->pNext || !buf->szNext) {
			buf->pCurr = 0;
			buf->szCurr = 0;

			/* Nothing more to do stop the ADC */
			ADC_StopConversion(pADC, seqIndex);
			return LPC_OK;
		}
		buf->pCurr = buf->pNext;
		buf->szCurr = buf->szNext;
		buf->pNext = 0;
		buf->idx = buf->szNext = 0;
	}

	/* If we are not in burst mode we must trigger next sample */
	if (!((pADC->valSeq[seqIndex] >> 12) & 0x1F) && !(pADC->valSeq[seqIndex] & ADC_SEQ_CTRL_BURST)) {
		pREGS->SEQ_CTRL[seqIndex] = pADC->valSeq[seqIndex];
	}

	return LPC_OK;
}

/* PRIVATE: ADC sequence handler polling mode */
static ErrorCode_t _ADC_Handler_SeqPoll(ADC_DRIVER_T *pADC, ADC_SEQ_INDEX_T seqIndex)
{
	ADC_REGS_T *pREGS = pADC->pREGS;
	ErrorCode_t ret = LPC_OK;

	/* Poll as long as the sequence is enabled */
	while (pREGS->SEQ_CTRL[seqIndex] & ADC_SEQ_CTRL_SEQ_ENA) {
		if (!(pREGS->FLAGS & ADC_FLAGS_SEQN_INT_MASK(seqIndex))) {
			continue;
		}
		ret = _ADC_Handler_Seq(pADC, seqIndex);
		if (ret != LPC_OK) {
			break;
		}
	}
	return ret;
}

/* PRIVATE: Handler for Overflow event */
static ErrorCode_t _ADC_Handler_Ovr(ADC_DRIVER_T *pADC)
{
	uint32_t flags = pADC->pREGS->FLAGS;

	/* Invoke Sequence handler to clear-out the data */
	if (flags & ADC_FLAGS_SEQA_OVRRUN_MASK) {
		return _ADC_Handler_Seq(pADC, ADC_SEQ_A);
	}
	else if (flags & ADC_FLAGS_SEQB_OVRRUN_MASK) {
		return _ADC_Handler_Seq(pADC, ADC_SEQ_B);
	}
	else {
		return ERR_FAILED;
	}
}

/* PRIVATE: Threshold event handler */
static ErrorCode_t _ADC_Handler_Thres(ADC_DRIVER_T *pADC)
{
	uint32_t flags = pADC->pREGS->FLAGS;

	if (!(flags & ADC_FLAGS_THCMP_INT_MASK)) {
		return ERR_FAILED;
	}

	flags &= 0xFFF;

	/* Clear out the interrupts */
	pADC->pREGS->FLAGS = flags;
	_ADC_InvokeCallback(pADC, ADC_THRESHOLD, (void *) flags);

	return LPC_OK;
}

/* EXPORTED API: Register a call-back function */
ErrorCode_t ADC_RegisterCallback(ADC_HANDLE_T hADC, ADC_CBINDEX_T idx, void (*cb_func)(ADC_HANDLE_T,
																					   ADC_CBINDEX_T,
																					   void *))
{
	if (idx < ADC_CBIDX_RESERVED) {
		((ADC_DRIVER_T *) hADC)->cbTable[idx] = cb_func;
	}
	else {
		return ERR_ADC_PARAM;
	}
	return LPC_OK;
}

/* EXPORTED API: ADC Initialization function */
ADC_HANDLE_T ADC_Init(void *mem, uint32_t base_addr, void *args)
{
	ADC_DRIVER_T *pADC;

	/* Check if the memory is word aligned */
	if ((uint32_t) mem & 0x3) {
		return NULL;
	}

	/* Assign memory provided by application */
	pADC = (ADC_DRIVER_T *) mem;
	memset(pADC, 0, sizeof(ADC_DRIVER_T));

	/* Assign the base address */
	pADC->pREGS = (ADC_REGS_T *) base_addr;
	pADC->pUserData = args;

	/* To be safe stop the ADC in case it is not stopped */
	pADC->pREGS->SEQ_CTRL[0] = 0x00;
	pADC->pREGS->SEQ_CTRL[1] = 0x00;

	return (ADC_HANDLE_T) pADC;
}

/* EXPORTED API: Setup the ADC threshold registers */
void ADC_SetThreshold(ADC_HANDLE_T hADC, uint32_t valThres0, uint32_t valThres1)
{
	ADC_REGS_T *pREGS = ((ADC_DRIVER_T *) hADC)->pREGS;
	pREGS->THR0_LOW = (valThres0 << ADC_THR_VAL_POS) & ADC_THR_VAL_MASK;
	pREGS->THR1_LOW = (valThres1 << ADC_THR_VAL_POS) & ADC_THR_VAL_MASK;
	valThres0 >>= 16;
	valThres1 >>= 16;
	pREGS->THR0_HIGH = (valThres0 << ADC_THR_VAL_POS) & ADC_THR_VAL_MASK;
	pREGS->THR1_HIGH = (valThres1 << ADC_THR_VAL_POS) & ADC_THR_VAL_MASK;
}

/* EXPORTED API: Calibrate the ADC */
ErrorCode_t ADC_Calibrate(ADC_HANDLE_T handle, uint32_t sysclk_freq)
{
	ADC_REGS_T *pREGS = ((ADC_DRIVER_T *) handle)->pREGS;
	volatile uint32_t i;

	pREGS->STARTUP = ADC_STARTUP_ENABLE;
	for ( i = 0; i < 0x10; i++ ) {}
	if ( !(pREGS->STARTUP & ADC_STARTUP_ENABLE) ) {
		return ERR_ADC_NO_POWER;
	}

	/* If not in by-pass mode do the calibration */
	if ( (pREGS->CALIBR & ADC_CALREQD) && !(pREGS->CTRL & ADC_CR_BYPASS) ) {
		uint32_t ctrl = pREGS->CTRL & (CTRL_MASK | 0xFF);
		uint32_t tmp = ctrl;

		/* Set ADC to SYNC mode */
		tmp &= ~ADC_CR_ASYNC_MODE;

		/* To be safe run calibration at 1MHz UM permits upto 30MHz */
		if (sysclk_freq > 1000000UL) {
			pREGS->CTRL = tmp | (((sysclk_freq / 1000000UL) - 1) & 0xFF);
		}

		/* Calibration is needed, do it now. */
		pREGS->CALIBR = ADC_CALIB;
		i = 0xF0000;
		while ( (pREGS->CALIBR & ADC_CALIB) && --i ) {}
		pREGS->CTRL = ctrl;
		return i ? LPC_OK : ERR_TIME_OUT;
	}

	/* A dummy conversion cycle will be performed. */
	pREGS->STARTUP = (pREGS->STARTUP | ADC_STARTUP_INIT) & 0x03;
	i = 0x7FFFF;
	while ( (pREGS->STARTUP & ADC_STARTUP_INIT) && --i ) {}
	return i ? LPC_OK : ERR_TIME_OUT;
}

/* EXPORTED API: Configure the ADC */
ErrorCode_t ADC_Configure(ADC_HANDLE_T hADC, const ADC_CFG_T *pCfg)
{
	ADC_DRIVER_T *pADC = hADC;
	ADC_REGS_T *pREGS = pADC->pREGS;

	pADC->valSeq[ADC_SEQ_A] = ADC_SEQ_CTRL_SEQ_ENA | ADC_SEQ_CTRL_START | (pCfg->flagSeqA & SEQ_A_MASK);
	pADC->valSeq[ADC_SEQ_B] = ADC_SEQ_CTRL_SEQ_ENA | ADC_SEQ_CTRL_START | (pCfg->flagSeqB & SEQ_B_MASK);

	/* START is not required for BURST or H/W Trigger */
	if ((pCfg->flagSeqA & ADC_SEQ_CTRL_TRIGGER_MASK)) {
		pADC->valSeq[ADC_SEQ_A] &= ~ADC_SEQ_CTRL_START;
	}

	/* START is not required for BURST or H/W Trigger */
	if ((pCfg->flagSeqB & ADC_SEQ_CTRL_TRIGGER_MASK)) {
		pADC->valSeq[ADC_SEQ_B] &= ~ADC_SEQ_CTRL_START;
	}

	pREGS->CTRL = (pCfg->flagCfg & CTRL_MASK) | (pCfg->clkDiv & ADC_CR_CLKDIV_MASK);

	/* Enable/Disable overflow interrupt */
	if (pCfg->flagCfg & ENABLE_OVR) {
		pADC->regInt |= ADC_INTEN_OVRRUN_ENABLE;
	}
	else {
		pADC->regInt &= ~ADC_INTEN_OVRRUN_ENABLE;
	}

	return LPC_OK;
}

/* EXPORTED API: Configure channel specific options */
ErrorCode_t ADC_ConfigureChannel(ADC_HANDLE_T hADC, uint32_t chanNum, uint32_t chanOpts)
{
	ADC_DRIVER_T *pADC = hADC;

	/* Sanity check */
	if (chanNum > ADC_MAX_CHANNEL_NUM) {
		return ERR_ADC_PARAM;
	}

	pADC->regInt &= ~(0x18 << (chanNum * 2));

	if (chanOpts & ADC_CH_THRES_SEL1) {
		pADC->regThrSel |= 1 << chanNum;
	}
	else {
		pADC->regThrSel &= ~(1 << chanNum);
	}

	if (chanOpts & ADC_CH_THRES_CROSSING) {
		pADC->regInt |= 0x10 << (chanNum * 2);
	}
	else if (chanOpts & ADC_CH_THRES_OUTSIDE) {
		pADC->regInt |= 0x08 << (chanNum * 2);
	}

	if (chanOpts & ADC_CH_DATA_CALLBACK) {
		pADC->flags |= CB_DATA(chanNum);
	}
	else {
		pADC->flags &= ~CB_DATA(chanNum);
	}

	if (chanOpts & ADC_CH_THRES_CALLBACK) {
		pADC->flags |= CB_THRES(chanNum);
	}
	else {
		pADC->flags &= ~CB_THRES(chanNum);
	}

	if (chanOpts & ADC_CH_THRES_DATA) {
		pADC->flag1 |= 1 << chanNum;
	}
	else {
		pADC->flag1 &= ~(1 << chanNum);
	}

	return LPC_OK;
}

/* EXPORTED API: Start analog to digital conversion on selected sequence */
ErrorCode_t ADC_StartConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex, void *buff, size_t bufCount)
{
	ADC_DRIVER_T *pADC = hADC;
	ADC_BUFFER_T *buf = &pADC->buffer[seqIndex];

	/* Sanity check on parameters */
	if ((uint32_t) seqIndex > ADC_SEQ_B) {
		return ERR_ADC_INVALID_SEQUENCE;
	}

	/* If an active conversion is going on set the buffer ptr */
	if (buf->state == ADC_STATE_ACTIVE) {
		if (buf->szNext) {
			return ERR_BUSY;
		}
		buf->pNext = buff;
		buf->szNext  = bufCount;
		return LPC_OK;
	}

	/* Assign the buffers */
	buf->pCurr = buff;
	buf->szCurr = bufCount;
	buf->idx = 0;

	/* Invoke the call back before start */
	_ADC_InvokeCallback(pADC, (ADC_CBINDEX_T) (ADC_START_SEQ + (ADC_CBINDEX_T)seqIndex), (void *) &pADC->pREGS);

	buf->state = ADC_STATE_ACTIVE;
	pADC->pREGS->SEQ_CTRL[seqIndex] = pADC->valSeq[seqIndex] & ~(ADC_SEQ_CTRL_SEQ_ENA | ADC_SEQ_CTRL_START);
	pADC->regInt |= (1 << seqIndex);
	pADC->pREGS->INTEN = pADC->regInt;
	pADC->pREGS->CHAN_THRSEL = pADC->regThrSel;
	pADC->pREGS->SEQ_CTRL[seqIndex] = pADC->valSeq[seqIndex];

	return LPC_OK;
}

ErrorCode_t ADC_SwTrigger(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex)
{
	ADC_DRIVER_T *pADC = hADC;

	/* Sanity check on parameters */
	if ((uint32_t) seqIndex > ADC_SEQ_B) {
		return ERR_ADC_INVALID_SEQUENCE;
	}

	pADC->pREGS->SEQ_CTRL[seqIndex] = pADC->valSeq[seqIndex] | ADC_SEQ_CTRL_SEQ_ENA | ADC_SEQ_CTRL_START;
	return LPC_OK;
}

/* EXPORTED API: Stop conversion on a given sequence */
ErrorCode_t ADC_StopConversion(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex)
{
	ADC_DRIVER_T *pADC = hADC;

	/* Sanity check on parameters */
	if ((uint32_t) seqIndex > ADC_SEQ_B) {
		return ERR_ADC_INVALID_SEQUENCE;
	}

	pADC->regInt &= ~(1 << seqIndex);
	pADC->pREGS->INTEN = pADC->regInt;	/* Disable interrupts */
	pADC->buffer[seqIndex].state = ADC_STATE_IDLE;	/* Set state to IDLE */

	/* Stop and disable the sequence */
	pADC->pREGS->SEQ_CTRL[seqIndex] = pADC->valSeq[seqIndex] &
									  ~(ADC_SEQ_CTRL_SEQ_ENA | ADC_SEQ_CTRL_BURST | ADC_SEQ_CTRL_START);
	_ADC_InvokeCallback(hADC, (ADC_CBINDEX_T)(ADC_STOP_SEQ + (ADC_CBINDEX_T)seqIndex), 0);
	return LPC_OK;
}

/* EXPORTED API: ADC Event handler */
ErrorCode_t ADC_Handler(ADC_HANDLE_T hADC, ADC_HEVENT_T hEvent)
{
	ADC_DRIVER_T *pADC = hADC;

	switch (hEvent) {
	case ADC_EV_SEQ_A_POLL:
		return _ADC_Handler_SeqPoll(pADC, ADC_SEQ_A);

	case ADC_EV_SEQ_B_POLL:
		return _ADC_Handler_SeqPoll(pADC, ADC_SEQ_B);

	case ADC_EV_SEQ_A_INT:
		return _ADC_Handler_Seq(pADC, ADC_SEQ_A);

	case ADC_EV_SEQ_B_INT:
		return _ADC_Handler_Seq(pADC, ADC_SEQ_B);

	case ADC_EV_SEQ_A_DMA:
		if (!(pADC->valSeq[ADC_SEQ_A] & 0x3F000)) {
			ADC_SwTrigger(hADC, ADC_SEQ_A);
		}
		return LPC_OK;

	case ADC_EV_SEQ_B_DMA:
		if (!(pADC->valSeq[ADC_SEQ_B] & 0x3F000)) {
			ADC_SwTrigger(hADC, ADC_SEQ_B);
		}
		return LPC_OK;

	case ADC_EV_OVR_INT:
		return _ADC_Handler_Ovr(pADC);

	case ADC_EV_THRES_INT:
		return _ADC_Handler_Thres(pADC);

	default:
		return ERR_ADC_PARAM;
	}
}

/* EXPROTED API: Returns memory required for ADC driver */
uint32_t ADC_GetMemSize(void)
{
	return sizeof(ADC_DRIVER_T);
}

/* EXPORTED API: Function to Get the firmware Version */
uint32_t ADC_GetDriverVersion(void)
{
	return ADC_DRIVER_VERSION;
}

/**
 * @brief	Table of the addresses of all the 12-Bit ADC functions
 * @note	This table of function pointers is the API interface.
 */
const ROM_ADC_API_T  adcrom_api = {
	ADC_GetMemSize,
	ADC_Init,
	ADC_Configure,
	ADC_ConfigureChannel,
	ADC_SetThreshold,
	ADC_RegisterCallback,
	ADC_Calibrate,
	ADC_Handler,
	ADC_StartConversion,
	ADC_StopConversion,
	ADC_SwTrigger,
	ADC_GetDriverVersion,
};
