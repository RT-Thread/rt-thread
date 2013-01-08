/*
 * @brief EMC Registers and control functions
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

#include "emc_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* DIV function with result rounded up */
#define EMC_DIV_ROUND_UP(x, y)  ((x + y - 1) / y)

#ifndef EMC_SUPPORT_ONLY_PL172
/* Get ARM External Memory Controller Version */
static uint32_t EMC_GetARMPeripheralID(IP_EMC_001_Type *pEMC)
{
	uint32_t *RegAdd;
	RegAdd = (uint32_t *) ((uint32_t) pEMC + 0xFE0);
	return (RegAdd[0] & 0xFF) | ((RegAdd[1] & 0xFF) << 8) |
		   ((RegAdd[2] & 0xFF) << 16) | (RegAdd[3] << 24);
}

#endif

/* Calculate Clock Count from Timing Unit(nanoseconds) */
static uint32_t EMC_TimingParamConvert(uint32_t EMC_Clock, int32_t input_ns, uint32_t adjust)
{
	uint32_t temp;
	if (input_ns < 0) {
		return (-input_ns) >> 8;
	}
	temp = EMC_Clock / 1000000;		/* MHz calculation */
	temp = temp * input_ns / 1000;

	/* round up */
	temp += 0xFF;

	/* convert to simple integer number format */
	temp >>= 8;
	if (temp > adjust) {
		return temp - adjust;
	}

	return 0;
}

/* Get Dynamic Memory Device Colum len */
static uint32_t EMC_GetColsLen(uint32_t DynConfig)
{
	uint32_t DevBusWidth;
	DevBusWidth = (DynConfig >> EMC_DYN_CONFIG_DEV_BUS_BIT) & 0x03;
	if (DevBusWidth == 2) {
		return 8;
	}
	else if (DevBusWidth == 1) {
		return ((DynConfig >> (EMC_DYN_CONFIG_DEV_SIZE_BIT + 1)) & 0x03) + 8;
	}
	else if (DevBusWidth == 0) {
		return ((DynConfig >> (EMC_DYN_CONFIG_DEV_SIZE_BIT + 1)) & 0x03) + 9;
	}

	return 0;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes the Dynamic Controller according to the specified parameters
   in the IP_EMC_DYN_CONFIG_Type */
void IP_EMC_Dynamic_Init(IP_EMC_001_Type *pEMC, IP_EMC_DYN_CONFIG_Type *Dynamic_Config, uint32_t EMC_Clock)
{
	uint32_t ChipSelect, tmpclk;
	int i;

	for (ChipSelect = 0; ChipSelect < 4; ChipSelect++) {
		IP_EMC_001_Type *EMC_Reg_add = (IP_EMC_001_Type *) ((uint32_t) pEMC + (ChipSelect << 5));

		EMC_Reg_add->DYNAMICRASCAS0    = Dynamic_Config->DevConfig[ChipSelect].RAS |
										 ((Dynamic_Config->DevConfig[ChipSelect].ModeRegister <<
										   (8 - EMC_DYN_MODE_CAS_BIT)) & 0xF00);
		EMC_Reg_add->DYNAMICCONFIG0    = Dynamic_Config->DevConfig[ChipSelect].DynConfig;
	}
	pEMC->DYNAMICREADCONFIG = Dynamic_Config->ReadConfig;	/* Read strategy */

	pEMC->DYNAMICRP         = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tRP, 1);
	pEMC->DYNAMICRAS        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tRAS, 1);
	pEMC->DYNAMICSREX       = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tSREX, 1);
	pEMC->DYNAMICAPR        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tAPR, 1);
	pEMC->DYNAMICDAL        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tDAL, 0);
	pEMC->DYNAMICWR         = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tWR, 1);
	pEMC->DYNAMICRC         = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tRC, 1);
	pEMC->DYNAMICRFC        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tRFC, 1);
	pEMC->DYNAMICXSR        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tXSR, 1);
	pEMC->DYNAMICRRD        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tRRD, 1);
	pEMC->DYNAMICMRD        = EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->tMRD, 1);

	/* TIM_Waitus(100); */
	/*TODO: if Timer driver is ready, it should replace below "for" delay technic */
	for (i = 0; i < 1000; i++) {	/* wait 100us */
	}
	pEMC->DYNAMICCONTROL    = 0x00000183;	/* Issue NOP command */

	/* TIM_Waitus(200); */						   /* wait 200us */
	/*TODO: if Timer driver is ready, it should replace below "for" delay technic */
	for (i = 0; i < 1000; i++) {}
	pEMC->DYNAMICCONTROL    = 0x00000103;	/* Issue PALL command */

	pEMC->DYNAMICREFRESH = 2;	/* ( 2 * 16 ) -> 32 clock cycles */

	/* TIM_Waitus(200); */						   /* wait 200us */
	for (i = 0; i < 80; i++) {}

	tmpclk = EMC_DIV_ROUND_UP(EMC_TimingParamConvert(EMC_Clock, Dynamic_Config->RefreshPeriod, 0), 16);
	pEMC->DYNAMICREFRESH    = tmpclk;

	pEMC->DYNAMICCONTROL    = 0x00000083;	/* Issue MODE command */

	for (ChipSelect = 0; ChipSelect < 4; ChipSelect++) {
		/*uint32_t burst_length;*/
		uint32_t DynAddr;
		uint8_t Col_len;

		Col_len = EMC_GetColsLen(Dynamic_Config->DevConfig[ChipSelect].DynConfig);
		/* get bus wide: if 32bit, len is 4 else if 16bit len is 2 */
		/* burst_length = 1 << ((((Dynamic_Config->DynConfig[ChipSelect] >> 14) & 1)^1) +1); */
		if (Dynamic_Config->DevConfig[ChipSelect].DynConfig & (1 << EMC_DYN_CONFIG_DATA_BUS_WIDTH_BIT)) {
			/*32bit bus */
			/*burst_length = 2;*/
			Col_len += 2;
		}
		else {
			/*burst_length = 4;*/
			Col_len += 1;
		}
		DynAddr = Dynamic_Config->DevConfig[ChipSelect].BaseAddr;

		if (DynAddr != 0) {
			uint32_t temp;
			uint32_t ModeRegister;
			ModeRegister = Dynamic_Config->DevConfig[ChipSelect].ModeRegister;
			temp = *((volatile uint32_t *) (DynAddr | (ModeRegister << Col_len)));
			temp = temp;
		}
	}
	pEMC->DYNAMICCONTROL    = 0x00000000;	/* Issue NORMAL command */

	/* enable buffers */
	pEMC->DYNAMICCONFIG0    |= 1 << 19;
	pEMC->DYNAMICCONFIG1    |= 1 << 19;
	pEMC->DYNAMICCONFIG2    |= 1 << 19;
	pEMC->DYNAMICCONFIG3    |= 1 << 19;
}

/* Set Deep Sleep Mode for Dynamic Memory Controller */
void IP_EMC_Dynamic_DeepSleepMode(IP_EMC_001_Type *pEMC, uint32_t Enable)
{
	if (Enable) {
		pEMC->DYNAMICCONTROL |= 1 << EMC_DYN_CONTROL_DEEPSLEEP_BIT;
	}
	else {
		pEMC->DYNAMICCONTROL &= ~(1 << EMC_DYN_CONTROL_DEEPSLEEP_BIT);
	}
}

/* Enable Dynamic Memory Controller */
void IP_EMC_Dynamic_Enable(IP_EMC_001_Type *pEMC, uint8_t Enable)
{
	if (Enable) {
		pEMC->DYNAMICCONTROL |= EMC_DYN_CONTROL_ENABLE;
	}
	else {
		pEMC->DYNAMICCONTROL &= ~EMC_DYN_CONTROL_ENABLE;
	}
}

/* Initializes the Static Controller according to the specified parameters
 * in the IP_EMC_STATIC_CONFIG_Type
 */
void IP_EMC_Static_Init(IP_EMC_001_Type *pEMC, IP_EMC_STATIC_CONFIG_Type *Static_Config, uint32_t EMC_Clock)
{
	IP_EMC_001_Type *EMC_Reg_add = (IP_EMC_001_Type *) ((uint32_t) pEMC + ((Static_Config->ChipSelect) << 5));
	EMC_Reg_add->STATICCONFIG0      = Static_Config->Config;
	EMC_Reg_add->STATICWAITWEN0     = EMC_TimingParamConvert(EMC_Clock, Static_Config->WaitWen, 1);
	EMC_Reg_add->STATICWAITOEN0     = EMC_TimingParamConvert(EMC_Clock, Static_Config->WaitOen, 0);
	EMC_Reg_add->STATICWAITRD0      = EMC_TimingParamConvert(EMC_Clock, Static_Config->WaitRd, 1);
	EMC_Reg_add->STATICWAITPAG0     = EMC_TimingParamConvert(EMC_Clock, Static_Config->WaitPage, 1);
	EMC_Reg_add->STATICWAITWR0      = EMC_TimingParamConvert(EMC_Clock, Static_Config->WaitWr, 2);
	EMC_Reg_add->STATICWAITTURN0    = EMC_TimingParamConvert(EMC_Clock, Static_Config->WaitTurn, 1);
}

/* Mirror CS1 to CS0 and DYCS0 */
void IP_EMC_Mirror(IP_EMC_001_Type *pEMC, uint32_t Enable)
{
	if (Enable) {
		pEMC->CONTROL |= 1 << 1;
	}
	else {
		pEMC->CONTROL &= ~(1 << 1);
	}
}

/* Enable EMC */
void IP_EMC_Enable(IP_EMC_001_Type *pEMC, uint32_t Enable)
{
	if (Enable) {
		pEMC->CONTROL |= 1;
	}
	else {
		pEMC->CONTROL &= ~(1);
	}
}

/* Set EMC LowPower Mode */
void IP_EMC_LowPowerMode(IP_EMC_001_Type *pEMC, uint32_t Enable)
{
	if (Enable) {
		pEMC->CONTROL |= 1 << 2;
	}
	else {
		pEMC->CONTROL &= ~(1 << 2);
	}
}

/* Initialize EMC */
void IP_EMC_Init(IP_EMC_001_Type *pEMC, uint32_t Enable, uint32_t ClockRatio, uint32_t EndianMode)
{
	pEMC->CONFIG    = (EndianMode ? 1 : 0) | ((ClockRatio ? 1 : 0) << 8);

	/* Enable EMC 001 Normal Memory Map, No low power mode */
	pEMC->CONTROL     = (Enable ? 1 : 0);
}

/* Set Static Memory Extended Wait in Clock */
void IP_EMC_SetStaticExtendedWait(IP_EMC_001_Type *pEMC, uint32_t Wait16Clks)
{
	pEMC->STATICEXTENDEDWAIT = Wait16Clks;
}
