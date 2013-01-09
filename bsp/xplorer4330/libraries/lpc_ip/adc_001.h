/*
 * @brief ADC Registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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

#ifndef __ADC_001_H_
#define __ADC_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_ADC_001 IP: 10 or 12-bit ADC register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief 10 or 12-bit ADC register block structure
 */
typedef struct {					/*!< ADCn Structure */
	__IO uint32_t CR;				/*!< A/D Control Register. The AD0CR register must be written to select the operating mode before A/D conversion can occur. */
	__I  uint32_t GDR;				/*!< A/D Global Data Register. Contains the result of the most recent A/D conversion. */
	__I  uint32_t RESERVED0;
	__IO uint32_t INTEN;			/*!< A/D Interrupt Enable Register. This register contains enable bits that allow the DONE flag of each A/D channel to be included or excluded from contributing to the generation of an A/D interrupt. */
	__I  uint32_t DR[8];			/*!< A/D Channel Data Register. This register contains the result of the most recent conversion completed on channel n. */
	__I  uint32_t STAT;				/*!< A/D Status Register. This register contains DONE and OVERRUN flags for all of the A/D channels, as well as the A/D interrupt flag. */
#if !defined(CHIP_LPC18XX) && !defined(CHIP_LPC43XX)
	__IO uint32_t ADTRM;
#endif
} IP_ADC_001_Type;

/**
 * @brief ADC register support bitfields and mask
 */
#define ADC_DR_RESULT(n)        ((((n) >> 6) & 0x3FF))	/*!< Mask for getting the ADC data read value */
#define ADC_DR_DONE(n)          (((n) >> 31))			/*!< Mask for reading the ADC done status */
#define ADC_DR_OVERRUN(n)       ((((n) >> 30) & (1UL)))	/*!< Mask for reading the ADC overrun status */
#define ADC_CR_CH_SEL(n)        ((1UL << (n)))			/*!< Selects which of the AD0.0:7 pins is (are) to be sampled and converted */
#define ADC_CR_CLKDIV(n)        ((((n) & 0xFF) << 8))	/*!< The APB clock (PCLK) is divided by (this value plus one) to produce the clock for the A/D */
#define ADC_CR_BURST            ((1UL << 16))			/*!< Repeated conversions A/D enable bit */
#define ADC_CR_BITACC(n)        ((((n) & 0x7) << 17))	/*!< Number of ADC accuracy bits */
#define ADC_CR_PDN              ((1UL << 21))			/*!< ADC convert in power down mode */
#define ADC_CR_START_MASK       ((7UL << 24))			/*!< ADC start mask bits */
#define ADC_CR_START_MODE_SEL(SEL)  ((SEL << 24))		/*!< Select Start Mode */
#define ADC_CR_START_NOW        ((1UL << 24))			/*!< Start conversion now */
#define ADC_CR_START_CTOUT15    ((2UL << 24))			/*!< Start conversion when the edge selected by bit 27 occurs on CTOUT_15 */
#define ADC_CR_START_CTOUT8     ((3UL << 24))			/*!< Start conversion when the edge selected by bit 27 occurs on CTOUT_8 */
#define ADC_CR_START_ADCTRIG0   ((4UL << 24))			/*!< Start conversion when the edge selected by bit 27 occurs on ADCTRIG0 */
#define ADC_CR_START_ADCTRIG1   ((5UL << 24))			/*!< Start conversion when the edge selected by bit 27 occurs on ADCTRIG1 */
#define ADC_CR_START_MCOA2      ((6UL << 24))			/*!< Start conversion when the edge selected by bit 27 occurs on Motocon PWM output MCOA2 */
#define ADC_CR_EDGE             ((1UL << 27))			/*!< Start conversion on a falling edge on the selected CAP/MAT signal */

/**
 * @brief	ADC status register used for IP drivers
 */
typedef enum {
	ADC_DR_DONE_STAT,	/*!< ADC data register staus */
	ADC_DR_OVERRUN_STAT,/*!< ADC data overrun staus */
	ADC_DR_ADINT_STAT	/*!< ADC interrupt status */
} IP_ADC_Status;

/**
 * @brief	Initialize for ADC
 * @param	pADC			: The base of ADC peripheral on the chip
 * @param	adcRate			: Sample rate of A/D converter
 * @param	adcPerClock		: The APB clock
 * @param	bitsAccuracy	: The accuracy of LSB value, should be ADC_10BITS -> ADC_3BITS
 * @return	 Nothing
 * Disable all ADC interrupts, set bit PDN, set ADC clock frequency
 * This is not the sample rate, but the clock for the ADC machine, and is usually set to
 * maximum. Applications may choose a lower frequency if they have high-impedance sources.
 * This is because a lower clock frequency produces a longer sampling time.
 */
void IP_ADC_Init(IP_ADC_001_Type *pADC, uint32_t adcRate, uint32_t adcPerClock, uint8_t bitsAccuracy);

/**
 * @brief	Shutdown ADC
 * @param	pADC	: The base of ADC peripheral on the chip
 * @return	Nothing
 * Reset the ADC control and INTEN Register to reset values (disabled)
 */
void IP_ADC_DeInit(IP_ADC_001_Type *pADC);

/**
 * @brief	Set burst mode for ADC
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	NewState	: ENABLE for burst mode, or DISABLE for normal mode
 * @return	Nothing
 */
void IP_ADC_SetBurstMode(IP_ADC_001_Type *pADC, FunctionalState NewState);

/**
 * @brief	Get the ADC value
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	channel		: Channel to be read value, should be 0..7
 * @param	data		: Data buffer to store the A/D value
 * @return	Status		: SUCCESS or ERROR
 */
Status IP_ADC_Get_Val(IP_ADC_001_Type *pADC, uint8_t channel, uint16_t *data);

/**
 * @brief	Get ADC Channel status from ADC data register
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	channel		: Channel number, should be 0..7
 * @param	StatusType	: Register to read, ADC_DR_DONE_STAT, ADC_DR_OVERRUN_STAT, or ADC_DR_ADINT_STAT
 * @return	Channel status, SET or RESET
 */
FlagStatus IP_ADC_GetStatus(IP_ADC_001_Type *pADC, uint8_t channel, uint32_t StatusType);

/**
 * @brief	Set the edge start condition
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	edge_mode	: 0 = rising, != = falling
 * @return	Nothing
 */
void IP_ADC_EdgeStartConfig(IP_ADC_001_Type *pADC, uint8_t edge_mode);

/**
 * @brief	Enable/Disable ADC channel number
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	channel		: Channel number
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	Nothing
 */
void IP_ADC_SetChannelNumber(IP_ADC_001_Type *pADC, uint8_t channel, FunctionalState NewState);

/**
 * @brief	Set start mode for ADC
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	start_mode	: Start mode choose one of modes in 'ADC_START_*' enumeration type definitions
 * @return	Nothing
 */
void IP_ADC_SetStartMode(IP_ADC_001_Type *pADC, uint8_t start_mode);

/**
 * @brief	Enable/Disable interrupt for ADC channel
 * @param	pADC		: The base of ADC peripheral on the chip
 * @param	channel		: Channel assert the interrupt
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	Nothing
 */
void IP_ADC_Int_Enable(IP_ADC_001_Type *pADC, uint8_t channel, FunctionalState NewState);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_001_H_ */
