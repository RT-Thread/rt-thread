/*
 * @brief LPC18xx/43xx A/D conversion driver
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

#include "adc_18xx_43xx.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*The channel to be operated on */
static uint8_t active_channel;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Returns the clock for the selected ADC */
static CCU_CLK_T Chip_ADC_GetClk(LPC_ADC_Type *pADC)
{
	CCU_CLK_T adcclk;

	if (pADC == LPC_ADC0) {
		adcclk = CLK_APB3_ADC0;
	}
	else {
		adcclk = CLK_APB3_ADC1;
	}

	return adcclk;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize the ADC peripheral and the ADC setup structure to default value */
void Chip_ADC_Init(LPC_ADC_Type *pADC, ADC_Clock_Setup_Type *ADCSetup)
{
	CCU_CLK_T adcclk = Chip_ADC_GetClk(pADC);

	/* Enable ADC clocking */
	Chip_Clock_EnableOpts(adcclk, true, true, 1);
	ADCSetup->adcPerClock = Chip_Clock_GetRate(adcclk);

	ADCSetup->adcRate = 400000;
	ADCSetup->bitsAccuracy = ADC_10BITS;
	IP_ADC_Init(pADC, ADCSetup->adcRate, ADCSetup->adcPerClock, ADCSetup->bitsAccuracy);
}

/* Select the mode starting the AD conversion */
void Chip_ADC_Set_StartMode(LPC_ADC_Type *pADC, ADC_StartMode mode, ADC_EdgeCfg EdgeOption)
{
	if ((mode != ADC_START_NOW) && (mode != ADC_NO_START)) {
		IP_ADC_EdgeStartConfig(pADC, (uint8_t) EdgeOption);
	}
	IP_ADC_SetStartMode(pADC, (uint8_t) mode);
}

/* Set the ADC Sample rate */
void Chip_ADC_Set_SampleRate(LPC_ADC_Type *pADC, ADC_Clock_Setup_Type *ADCSetup, uint32_t rate)
{
	ADCSetup->adcRate = rate;
	IP_ADC_Init(pADC, ADCSetup->adcRate, ADCSetup->adcPerClock, ADCSetup->bitsAccuracy);

}

/* Set the ADC accuracy bits */
void Chip_ADC_Set_Resolution(LPC_ADC_Type *pADC, ADC_Clock_Setup_Type *ADCSetup, ADC_Resolution resolution)
{
	ADCSetup->bitsAccuracy = resolution;
	IP_ADC_Init(pADC, ADCSetup->adcRate, ADCSetup->adcPerClock, ADCSetup->bitsAccuracy);
}

/* Enable or disable the ADC channel on ADC peripheral */
void Chip_ADC_Channel_Enable_Cmd(LPC_ADC_Type *pADC, ADC_Channel channel, FunctionalState NewState)
{
	IP_ADC_SetChannelNumber(pADC, channel, NewState);
	active_channel = channel;
}

/* Enable burst mode */
void Chip_ADC_Burst_Cmd(LPC_ADC_Type *pADC, FunctionalState NewState)
{
	IP_ADC_SetStartMode(pADC, ADC_NO_START);
	IP_ADC_SetBurstMode(pADC, NewState);
}

/* Read the ADC value and convert it to 8bits value */
Status Chip_ADC_Read_Byte(LPC_ADC_Type *pADC, uint8_t *data)
{
	uint16_t temp;
	Status rt;

	rt = IP_ADC_Get_Val(pADC, active_channel, &temp);
	*data = (uint8_t) temp;

	return rt;
}

/* Set a channel to be read A/D data */
void Chip_ADC_Active_Channel(uint8_t channel)
{
	active_channel = channel;
}
