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

#ifndef __HW_ADC_ROM_API_H
#define __HW_ADC_ROM_API_H

#include <stdint.h>
#include <string.h>
#include "error.h"
#include "packing.h"
#include "hw_adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_ADC ADC (12-Bit) ROM driver functions and definitions
 * @ingroup ROMAPI_ADC_WRAPPER
 * @{
 */

/** @brief ADC Handler type */
typedef void *ADC_HANDLE_T;

/** @brief	ADC SEQ Options */
#define TRIG_SOFT      (0UL << 12)		/*!< Software Trigger */
#define TRIG_PININT0   (0UL << 12)		/*!< Hardware Trigger on PININT0 */
#define TRIG_PININT1   (1UL << 12)		/*!< Hardware Trigger on PININT1 */
#define TRIG_ARMTXEV   (5UL << 12)		/*!< Hardware Trigger on ARM_TXEV */
#define TRIG_POL_NEG   0				/*!< Trigger polarity is negative */
#define TRIG_POL_POS   (1UL << 18)		/*!< Trigger polarity is positive */
#define BYPASS_SYNC    (1UL << 19)		/*!< Bypass Synchronization Filp-Flop */
#define MODE_BURST     (1UL << 27)		/*!< Enable Burst mode */
#define MODE_SINGLE    (1UL << 28)		/*!< Enable Single mode */
#define SEQA_PIRO_HIGH (1UL << 29)		/*!< Set SEQA as HIGH Priority */
#define MODE_EOC       (0UL << 30)		/*!< Event after end of Conversion */
#define MODE_EOS       (1UL << 30)		/*!< Event after end of sequence */
#define ENABLE_CH(ch)  (1UL << (ch))	/*!< Enable the channel number */

/* Gets the ADC trigger from configuration */
#define ADC_TRIGGER(cfg) (((cfg) & 0x3F000) >> 12)

/** @brief	ADC DMA source address offsets */
#define ADC_DMA_SRC_SEQA    4			/*!< DMA Source offset for SEQ_A */
#define ADC_DMA_SRC_SEQB    5			/*!< DMA Source offset for SEQ_B */
#define ADC_DMA_SRC_CH0     8			/*!< DMA Source offset for CH0 */
#define ADC_DMA_SRC_CH1     9			/*!< DMA Source offset for CH1 */
#define ADC_DMA_SRC_CH2     10			/*!< DMA Source offset for CH2 */
#define ADC_DMA_SRC_CH3     11			/*!< DMA Source offset for CH3 */
#define ADC_DMA_SRC_CH4     12			/*!< DMA Source offset for CH4 */
#define ADC_DMA_SRC_CH5     13			/*!< DMA Source offset for CH5 */
#define ADC_DMA_SRC_CH6     14			/*!< DMA Source offset for CH6 */
#define ADC_DMA_SRC_CH7     15			/*!< DMA Source offset for CH7 */
#define ADC_DMA_SRC_CH8     16			/*!< DMA Source offset for CH8 */
#define ADC_DMA_SRC_CH9     17			/*!< DMA Source offset for CH9 */
#define ADC_DMA_SRC_CH10    18			/*!< DMA Source offset for CH10 */
#define ADC_DMA_SRC_CH11    19			/*!< DMA Source offset for CH11 */

/** @brief	ADC DMA Source address calculator */
#define ADC_DMA_ADDR(ptr, src) ((*(uint32_t *) (ptr)) + ((src) << 2))

/** @brief	ADC CTRL Options */
#define MODE_SYNC      (0UL << 8)		/*!< Set ADC to synchoronous mode */
#define MODE_ASYNC     (1UL << 8)		/*!< Set ADC to asynchoronous mode */
#define RESOL_6BIT     (0UL << 9)		/*!< Set ADC Resolution to 6 bits */
#define RESOL_8BIT     (1UL << 9)		/*!< Set ADC Resolution to 8 bits */
#define RESOL_10BIT    (2UL << 9)		/*!< Set ADC Resolution to 10 bits */
#define RESOL_12BIT    (3UL << 9)		/*!< Set ADC Resolution to 12 bits */
#define BYPASS_CALIB   (1UL << 11)		/*!< Bypass calibration data */
#define SAMPLE_TIME(x) (((x) & 7) << 12)	/*!< Set the Sample Time to @a x */
#define ENABLE_OVR     (1UL << 24)		/*!< Enable Overflow interrupt */

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a ADC ROM
 * driver handle.<br>
 * To get a user context, simply use the macro on the driver's handle:
 * void *pUserData = ROM_ADC_HANDLE_TOUDATA(hADC);
 */
#define ROM_ADC_HANDLE_TOUDATA(p)          (void *) (*(uint32_t *) p)

/** @brief	ADC Threshold select */
#define SEL_THRES1(ch) (1UL << (ch))	/*!< Select THRESHOLD-1 register */
#define EN_THRES(ch)   (1UL << (16 + (ch)))	/*!< Enable Threshold compare */

/** @brief	Convert DMA data to channel data */
#define ADC_DATA_CH(data) (((data) >> 4) & 0xFFFF)

/**@brief	Threshold ranges */
#define ADC_THRES_ABOVE      2		/*!< Threshold is above THRES_HI */
#define ADC_THRES_BELOW      1		/*!< Threshold is below THRES_LO */
#define ADC_THRES_INSIDE     0		/*!< Threshold is inside the range */
#define ADC_THRES_RANGE(data) (((data) >> 12) & 0x3)	/*!< Get Threshold range data */

/**@brief	Threshold crossings */
#define ADC_THRES_UP         3		/*!< Threshold crossing UP */
#define ADC_THRES_DOWN       2		/*!< Threshold crossing DOWN */
#define ADC_THRES_NONE       0		/*!< No threshold crossing */
#define ADC_THRES_CORSS(data)   (((data) >> 14) & 0x3)	/*!< Get threshold crossing data */

/* @brief	ADC Configuration data structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t flagSeqA;	/*!< Options for SEQ_A, like triggers, burst/single mode etc; */
	uint32_t flagSeqB;	/*!< Options for SEQ_B, like triggers, burst/single mode etc; */
	uint32_t flagCfg;	/*!< ADC Configuration flags, like SYNC/ASYNC mode select resolution select etc; see #MODE_SYNC, #RESOL_6BIT, #BYPASS_CALIB and #SAMPLE_TIME */
	uint32_t clkDiv;	/*!< Clock divider value to be used in SYNC mode; not valid #MODE_ASYNC is present in #flagCfg */
} ADC_CFG_T;

/** @brief	Event handler, event types */
typedef enum {
	ADC_EV_SEQ_A_POLL,		/*!< SEQ_A Polling */
	ADC_EV_SEQ_B_POLL,		/*!< SEQ_B Polling */
	ADC_EV_SEQ_A_INT,		/*!< SEQ_A Interrupt */
	ADC_EV_SEQ_B_INT,		/*!< SEQ_B Interrupt */
	ADC_EV_SEQ_A_DMA,		/*!< SEQ_A DMA Event */
	ADC_EV_SEQ_B_DMA,		/*!< SEQ_B DMA Event */
	ADC_EV_OVR_INT,			/*!< Overflow interrupt */
	ADC_EV_THRES_INT,		/*!< Threshold interrupt */
} ADC_HEVENT_T;

/** @brief	Channel configuration options */
#define ADC_CH_THRES_SEL1           0x01	/*!< Use THRES1 for threshold compare */
#define ADC_CH_THRES_CALLBACK       0x02	/*!< Enable threshold callback event */
#define ADC_CH_THRES_OUTSIDE        0x04	/*!< Enable threshold outside event */
#define ADC_CH_THRES_CROSSING       0x08	/*!< Enable threshold crossing event */
#define ADC_CH_DATA_CALLBACK        0x10	/*!< Enable callback for data available */
#define ADC_CH_THRES_DATA           0x20	/*!< Add threshold value to DATA */

/** @brief	Macros to extract information from call-back flags */
#define ADC_OVR_SEQ_A(flag)         (((flag) >> 12) & 1)	/*!< Overflow in SEQ_A */
#define ADC_OVR_SEQ_B(flag)         (((flag) >> 13) & 1)	/*!< Overflow in SEQ_B */

/** @brief	Index to call-back functions */
typedef enum {
	ADC_START_SEQ,							/*!< Start SEQ event */
	ADC_START_SEQ_A = ADC_START_SEQ,		/*!< Start SEQ_A event */
	ADC_START_SEQ_B,						/*!< Start SEQ_B event */
	ADC_STOP_SEQ,							/*!< Stop SEQ event */
	ADC_STOP_SEQ_A = ADC_STOP_SEQ,			/*!< Stop SEQ_A event */
	ADC_STOP_SEQ_B,							/*!< Stop SEQ_B event */
	ADC_BUFFER_DONE,						/*!< ADC Buffer full event */
	ADC_BUFFER_DONE_A = ADC_BUFFER_DONE,	/*!< ADC Buffer full event for SEQ_A */
	ADC_BUFFER_DONE_B,						/*!< ADC Buffer full event for SEQ_B */
	ADC_CHDATA,								/*!< Data for Channel available */
	ADC_OVERFLOW,							/*!< Over flow event */
	ADC_THRESHOLD,							/*!< Threshold event */
	ADC_CBIDX_RESERVED,						/*!< Reserved value (should not be used) */
} ADC_CBINDEX_T;

/** @brief	ADC Sequence index */
typedef enum {
	ADC_SEQ_A,								/*!< Index for Sequence A */
	ADC_SEQ_B,								/*!< Index for Sequence B */
} ADC_SEQ_INDEX_T;

/**
 * @brief	Structure that has the API pointers in ROM Table
 */
typedef PRE_PACK struct POST_PACK {
	/* Index of All the 12-Bit ADC driver APIs */
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of ADC driver */
	ADC_HANDLE_T (*Init)(void *pMem, uint32_t baseAddr, void *pUserData);	/*!< Initializes the ADC driver and peripheral */
	ErrorCode_t (*Configure)(ADC_HANDLE_T hADC, const ADC_CFG_T *pCfg);	/*!< Configure the ADC to given parameters like resolution etc. */
	ErrorCode_t (*ConfigureCh)(ADC_HANDLE_T hADC, uint32_t chanNum, uint32_t chanOpts);	/*!< Configure channel specific options */
	void (*SetThreshold)(ADC_HANDLE_T hADC, uint32_t valThr0, uint32_t valThr1);/*!< Set the threshold values for THRES0 (HIGH & LOW) and THRES1 (HIGH & LOW) */
	ErrorCode_t (*RegisterCB)(ADC_HANDLE_T hADC, ADC_CBINDEX_T cbIndex,
							  void (*pCbFunc)(ADC_HANDLE_T, ADC_CBINDEX_T, void *));											/*!< Registers an ADC callback function */
	ErrorCode_t (*Calibrate)(ADC_HANDLE_T hADC, uint32_t sysclk_freq);	/*!< Calibrate the ADC peripheral */
	ErrorCode_t (*Handler)(ADC_HANDLE_T hADC, ADC_HEVENT_T event);	/*!< ADC Event handler, should be called from the ISR */
	ErrorCode_t (*StartConversion)(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex, void *buffer, size_t bufCount);	/*!< Start sampling of ADC inputs */
	ErrorCode_t (*StopConversion)(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex);	/*!< Stop sampling of ADC inputs */
	ErrorCode_t (*SwTrigger)(ADC_HANDLE_T hADC, ADC_SEQ_INDEX_T seqIndex);	/*!< Generate a software trigger */
	uint32_t (*GetDriverVersion)(void);	/*!< Get the version of the Driver Firmware in ROM */
} ROM_ADC_API_T;

/* Extern declaration so that application can access
 * pointer to the function table
 */
extern const ROM_ADC_API_T  adcrom_api;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HW_ADCD_ROM_API_H */
