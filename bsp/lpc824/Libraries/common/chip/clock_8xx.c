/*
 * @brief LPC8xx clock driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
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
#define _CHIP_COMMON_
#include "chip.h"


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Inprecise clock rates for the watchdog oscillator */
static const uint32_t wdtOSCRate[WDTLFO_OSC_4_60 + 1] = {
	0,					/* WDT_OSC_ILLEGAL */
	600000,				/* WDT_OSC_0_60 */
	1050000,			/* WDT_OSC_1_05 */
	1400000,			/* WDT_OSC_1_40 */
	1750000,			/* WDT_OSC_1_75 */
	2100000,			/* WDT_OSC_2_10 */
	2400000,			/* WDT_OSC_2_40 */
	2700000,			/* WDT_OSC_2_70 */
	3000000,			/* WDT_OSC_3_00 */
	3250000,			/* WDT_OSC_3_25 */
	3500000,			/* WDT_OSC_3_50 */
	3750000,			/* WDT_OSC_3_75 */
	4000000,			/* WDT_OSC_4_00 */
	4200000,			/* WDT_OSC_4_20 */
	4400000,			/* WDT_OSC_4_40 */
	4600000				/* WDT_OSC_4_60 */
};

 typedef struct {
	uint16_t	freq_main;			//	main clock frequency in MHz
	uint16_t	freq_sys;			//	system (CPU) clock frequency in MHz
	uint16_t	freq_fcco;			//	FCCO clock frequency in MHz
	uint16_t	msel;				//	MSEL (pre-decremented)
	uint16_t	psel;				//	PSEL (pre-decremented)
	uint16_t	divider;			//	SYSAHBCLKDIV
} LPC_8XX_PLL_T;
 
/*
 *	This table contains all useful PLL configurations
 *	for "integer" MHZ (e.g. 1MHz, 2MHz, etc.) frequencies.
 *
 *	This table has two inputs:
 *	- freq_main: This is the main frequency.
 *	- freq_sys: This is the system (CPU) frequency.
 *	These are used to select which table entry to use.
 *
 *	There are many ways to get some frequencies. For example,
 *	there are eight ways to make the CPU run at 12MHZ. If the peripheral bus
 *	needs to run very fast, it's possible to set the main clock
 *	up to 96MHz. If low power is a requirement, it's possible to set the main
 *	clock to 12MHz.
 *
 *	All the rest of the table entries are outputs.
 *	- freq_fcco is simply an FYI value. It is not used for programming.
 *	- MSEL / PSEL / divider are used to program the PLL.
 */
static const LPC_8XX_PLL_T config_tab[] = {
	{	  12,   12,  192,    0,    3,    1	},		// 12.0000MHz
	{	  12,    6,  192,    0,    3,    2	},		//  6.0000MHz
	{	  12,    4,  192,    0,    3,    3	},		//  4.0000MHz
	{	  12,    3,  192,    0,    3,    4	},		//  3.0000MHz
	{	  12,    2,  192,    0,    3,    6	},		//  2.0000MHz
	{	  12,    1,  192,    0,    3,   12	},		//  1.0000MHz
	{	  24,   24,  192,    1,    2,    1	},		// 24.0000MHz
	{	  24,   12,  192,    1,    2,    2	},		// 12.0000MHz
	{	  24,    8,  192,    1,    2,    3	},		//  8.0000MHz
	{	  24,    6,  192,    1,    2,    4	},		//  6.0000MHz
	{	  24,    4,  192,    1,    2,    6	},		//  4.0000MHz
	{	  24,    3,  192,    1,    2,    8	},		//  3.0000MHz
	{	  24,    2,  192,    1,    2,   12	},		//  2.0000MHz
	{	  24,    1,  192,    1,    2,   24	},		//  1.0000MHz
	{	  36,   18,  288,    2,    2,    2	},		// 18.0000MHz
	{	  36,   12,  288,    2,    2,    3	},		// 12.0000MHz
	{	  36,    9,  288,    2,    2,    4	},		//  9.0000MHz
	{	  36,    6,  288,    2,    2,    6	},		//  6.0000MHz
	{	  36,    4,  288,    2,    2,    9	},		//  4.0000MHz
	{	  36,    3,  288,    2,    2,   12	},		//  3.0000MHz
	{	  36,    2,  288,    2,    2,   18	},		//  2.0000MHz
	{	  36,    1,  288,    2,    2,   36	},		//  1.0000MHz
	{	  48,   24,  192,    3,    1,    2	},		// 24.0000MHz
	{	  48,   16,  192,    3,    1,    3	},		// 16.0000MHz
	{	  48,   12,  192,    3,    1,    4	},		// 12.0000MHz
	{	  48,    8,  192,    3,    1,    6	},		//  8.0000MHz
	{	  48,    6,  192,    3,    1,    8	},		//  6.0000MHz
	{	  48,    4,  192,    3,    1,   12	},		//  4.0000MHz
	{	  48,    3,  192,    3,    1,   16	},		//  3.0000MHz
	{	  48,    2,  192,    3,    1,   24	},		//  2.0000MHz
	{	  48,    1,  192,    3,    1,   48	},		//  1.0000MHz
	{	  60,   30,  240,    4,    1,    2	},		// 30.0000MHz
	{	  60,   20,  240,    4,    1,    3	},		// 20.0000MHz
	{	  60,   15,  240,    4,    1,    4	},		// 15.0000MHz
	{	  60,   12,  240,    4,    1,    5	},		// 12.0000MHz
	{	  60,   10,  240,    4,    1,    6	},		// 10.0000MHz
	{	  60,    6,  240,    4,    1,   10	},		//  6.0000MHz
	{	  60,    5,  240,    4,    1,   12	},		//  5.0000MHz
	{	  60,    4,  240,    4,    1,   15	},		//  4.0000MHz
	{	  60,    3,  240,    4,    1,   20	},		//  3.0000MHz
	{	  60,    2,  240,    4,    1,   30	},		//  2.0000MHz
	{	  60,    1,  240,    4,    1,   60	},		//  1.0000MHz
	{	  72,   24,  288,    5,    1,    3	},		// 24.0000MHz
	{	  72,   18,  288,    5,    1,    4	},		// 18.0000MHz
	{	  72,   12,  288,    5,    1,    6	},		// 12.0000MHz
	{	  72,    9,  288,    5,    1,    8	},		//  9.0000MHz
	{	  72,    8,  288,    5,    1,    9	},		//  8.0000MHz
	{	  72,    6,  288,    5,    1,   12	},		//  6.0000MHz
	{	  72,    4,  288,    5,    1,   18	},		//  4.0000MHz
	{	  72,    3,  288,    5,    1,   24	},		//  3.0000MHz
	{	  72,    2,  288,    5,    1,   36	},		//  2.0000MHz
	{	  72,    1,  288,    5,    1,   72	},		//  1.0000MHz
	{	  84,   28,  168,    6,    0,    3	},		// 28.0000MHz
	{	  84,   21,  168,    6,    0,    4	},		// 21.0000MHz
	{	  84,   14,  168,    6,    0,    6	},		// 14.0000MHz
	{	  84,   12,  168,    6,    0,    7	},		// 12.0000MHz
	{	  84,    7,  168,    6,    0,   12	},		//  7.0000MHz
	{	  84,    6,  168,    6,    0,   14	},		//  6.0000MHz
	{	  84,    4,  168,    6,    0,   21	},		//  4.0000MHz
	{	  84,    3,  168,    6,    0,   28	},		//  3.0000MHz
	{	  84,    2,  168,    6,    0,   42	},		//  2.0000MHz
	{	  84,    1,  168,    6,    0,   84	},		//  1.0000MHz
	{	  96,   24,  192,    7,    0,    4	},		// 24.0000MHz
	{	  96,   16,  192,    7,    0,    6	},		// 16.0000MHz
	{	  96,   12,  192,    7,    0,    8	},		// 12.0000MHz
	{	  96,    8,  192,    7,    0,   12	},		//  8.0000MHz
	{	  96,    6,  192,    7,    0,   16	},		//  6.0000MHz
	{	  96,    4,  192,    7,    0,   24	},		//  4.0000MHz
	{	  96,    3,  192,    7,    0,   32	},		//  3.0000MHz
	{	  96,    2,  192,    7,    0,   48	},		//  2.0000MHz
	{	  96,    1,  192,    7,    0,   96	},		//  1.0000MHz
};
static const uint16_t config_tab_ct = sizeof(config_tab) / sizeof(LPC_8XX_PLL_T);
static uint16_t config_tab_idx = 0;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
/* System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

static void pll_config(const LPC_8XX_PLL_T* pll_cfg)
{
	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_IRC_PD);									/* turn on the IRC by clearing the power down bit */
	Chip_Clock_SetSystemPLLSource(SYSCTL_PLLCLKSRC_IRC);						/* select PLL input to be IRC */
	Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_IRC);
	Chip_FMC_SetFLASHAccess(FLASHTIM_30MHZ_CPU);								/* setup FLASH access to 2 clocks (up to 30MHz) */
	Chip_SYSCTL_PowerDown(SYSCTL_SLPWAKE_SYSPLL_PD);							/* power down PLL to change the PLL divider ratio */
	Chip_Clock_SetupSystemPLL(pll_cfg->msel, pll_cfg->psel);					/* configure the PLL */
	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_SYSPLL_PD);								/* turn on the PLL by clearing the power down bit */
	while (!Chip_Clock_IsSystemPLLLocked()) {}									/* wait for PLL to lock */
	Chip_Clock_SetSysClockDiv(pll_cfg->divider);								/* load the divider */
	Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);					/* enable the new Frequency */
}

/* Compute a WDT or LFO rate */
static uint32_t Chip_Clock_GetWDTLFORate(uint32_t reg)
{
	uint32_t div;
	CHIP_WDTLFO_OSC_T clk;

	/* Get WDT oscillator settings */
	clk = (CHIP_WDTLFO_OSC_T) ((reg >> 5) & 0xF);
	div = reg & 0x1F;

	/* Compute clock rate and divided by divde value */
	return wdtOSCRate[clk] / ((div + 1) << 1);
}

/* Compute PLL frequency */
static uint32_t Chip_Clock_GetPLLFreq(uint32_t PLLReg, uint32_t inputRate)
{
	uint32_t m_val = ((PLLReg & 0x1F) + 1);

	return (inputRate * m_val);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

bool Chip_IRC_SetFreq(uint32_t main, uint32_t sys)
{
	uint16_t	freq_m = main/1000000;											/* main frequency in MHz */
	uint16_t	freq_s = sys/1000000;											/* system frequency in MHz */
	bool		found = false;													/* frequencies found */
	uint32_t	i = 0;

	if (freq_s > 30)															/* if system frequency is higher than 30MHz... */
		return false;															/* ...don't attempt to set it */
	if (freq_m > 96)															/* if main frequency is higher than 96MHz... */
		return false;															/* ...don't attempt to set it */
	
	for (i=0; i<config_tab_ct; i++) {											/* loop through table */
		if ((freq_m == config_tab[i].freq_main) && (freq_s == config_tab[i].freq_sys)) {	/* attempt to find a match */
			config_tab_idx = i;													/* save the data for later */
			found = true;														/* set state to found */
			break;																/* go config the PLL */
		}
	}
	if (found == true) {														/* if a match has been found */
		pll_config(&config_tab[config_tab_idx]);								/* configure the PLL */
	}

	return found;																/* return operation status */
}

// Open this API only if ROM headers are included
#ifdef LPC_PWRD_API
void Chip_IRC_SetFreq_ROM(uint32_t sys)
{
	uint32_t cmd[4], resp[2];

	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_IRC_PD);									/* Turn on the IRC by clearing the power down bit */
	Chip_Clock_SetSystemPLLSource(SYSCTL_PLLCLKSRC_IRC);						/* Select PLL input to be IRC */
	Chip_FMC_SetFLASHAccess(FLASHTIM_30MHZ_CPU);								/* Setup FLASH access to 2 clocks (up to 30MHz) */
	
	cmd[0] = Chip_Clock_GetIntOscRate() / 1000;									/* in KHz */
	cmd[1] = sys / 1000;														/* system clock rate in kHz */
	cmd[2] = CPU_FREQ_EQU;
	cmd[3] = sys / 10000;														/* Timeout. See UM10601, section 23.4.1.3 for details */
	LPC_PWRD_API->set_pll(cmd, resp);											/* Attempt to set the PLL */

	while (resp[0] != PLL_CMD_SUCCESS) {}										/* Dead loop on fail */
}
#else

#endif

/* Update system core clock rate, should be called if the system has
   a clock rate change */
void SystemCoreClockUpdate(void)
{
	/* CPU core speed */
	SystemCoreClock = Chip_Clock_GetSystemClockRate();
}
/* Set System PLL clock source */
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCTL_PLLCLKSRC_T src)
{
	LPC_SYSCTL->SYSPLLCLKSEL  = (uint32_t) src;
    
    /* sequnce a 0 followed by 1 to update PLL source selection */
	LPC_SYSCTL->SYSPLLCLKUEN  = 0;  
	LPC_SYSCTL->SYSPLLCLKUEN  = 1;  
}

/* Bypass System Oscillator and set oscillator frequency range */
void Chip_Clock_SetPLLBypass(bool bypass, bool highfr)
{
	uint32_t ctrl = 0;

	if (bypass) {
		ctrl |= (1 << 0);
	}
	if (highfr) {
		ctrl |= (1 << 1);
	}

	LPC_SYSCTL->SYSOSCCTRL = ctrl;
}

/* Set main system clock source */
void Chip_Clock_SetMainClockSource(CHIP_SYSCTL_MAINCLKSRC_T src)
{
	LPC_SYSCTL->MAINCLKSEL  = (uint32_t) src;
    
    /* sequnce a 0 followed by 1 to update MAINCLK source selection */
	LPC_SYSCTL->MAINCLKUEN  = 0;
	LPC_SYSCTL->MAINCLKUEN  = 1;
}

/* Set CLKOUT clock source and divider */
void Chip_Clock_SetCLKOUTSource(CHIP_SYSCTL_CLKOUTSRC_T src, uint32_t div)
{
	LPC_SYSCTL->CLKOUTSEL = (uint32_t) src;
    
    /* sequnce a 0 followed by 1 to update CLKOUT source selection */
	LPC_SYSCTL->CLKOUTUEN = 0;
	LPC_SYSCTL->CLKOUTUEN = 1;
	LPC_SYSCTL->CLKOUTDIV = div;
}

/* Return estimated watchdog oscillator rate */
uint32_t Chip_Clock_GetWDTOSCRate(void)
{
	return Chip_Clock_GetWDTLFORate(LPC_SYSCTL->WDTOSCCTRL & ~SYSCTL_WDTOSCCTRL_RESERVED);
}

/* Return System PLL input clock rate */
uint32_t Chip_Clock_GetSystemPLLInClockRate(void)
{
	uint32_t clkRate;

	switch ((CHIP_SYSCTL_PLLCLKSRC_T) (LPC_SYSCTL->SYSPLLCLKSEL & 0x3)) {
	case SYSCTL_PLLCLKSRC_IRC:
		clkRate = Chip_Clock_GetIntOscRate();
		break;

	case SYSCTL_PLLCLKSRC_SYSOSC:
		clkRate = Chip_Clock_GetMainOscRate();
		break;

	case SYSCTL_PLLCLKSRC_EXT_CLKIN:
		clkRate = Chip_Clock_GetExtClockInRate();
		break;

	default:
		clkRate = 0;
	}

	return clkRate;
}

/* Return System PLL output clock rate */
uint32_t Chip_Clock_GetSystemPLLOutClockRate(void)
{
	return Chip_Clock_GetPLLFreq((LPC_SYSCTL->SYSPLLCTRL & ~SYSCTL_SYSPLLCTRL_RESERVED),
								 Chip_Clock_GetSystemPLLInClockRate());
}

/* Return main clock rate */
uint32_t Chip_Clock_GetMainClockRate(void)
{
	uint32_t clkRate = 0;

	switch ((CHIP_SYSCTL_MAINCLKSRC_T) (LPC_SYSCTL->MAINCLKSEL & 0x3)) {
	case SYSCTL_MAINCLKSRC_IRC:
		clkRate = Chip_Clock_GetIntOscRate();
		break;

	case SYSCTL_MAINCLKSRC_PLLIN:
		clkRate = Chip_Clock_GetSystemPLLInClockRate();
		break;

	case SYSCTL_MAINCLKSRC_WDTOSC:
		clkRate = Chip_Clock_GetWDTOSCRate();
		break;

	case SYSCTL_MAINCLKSRC_PLLOUT:
		clkRate = Chip_Clock_GetSystemPLLOutClockRate();
		break;
	}

	return clkRate;
}

/* Return system clock rate */
uint32_t Chip_Clock_GetSystemClockRate(void)
{
	/* No point in checking for divide by 0 */
	return Chip_Clock_GetMainClockRate() / (LPC_SYSCTL->SYSAHBCLKDIV & ~SYSCTL_SYSAHBCLKDIV_RESERVED);
}

/* Get USART 0/1/2 UART base rate */
uint32_t Chip_Clock_GetUSARTNBaseClockRate(void)
{
	uint64_t inclk;
	uint32_t div;

	div = (uint32_t) Chip_Clock_GetUARTClockDiv();
	if (div == 0) {
		/* Divider is 0 so UART clock is disabled */
		inclk = 0;
	}
	else {
		uint32_t mult, divf;

		/* Input clock into FRG block is the divided main system clock */
		inclk = (uint64_t) (Chip_Clock_GetMainClockRate() / div);

		divf = Chip_SYSCTL_GetUSARTFRGDivider();
		if (divf == 0xFF) {
			/* Fractional part is enabled, get multiplier */
			mult = (uint32_t) Chip_SYSCTL_GetUSARTFRGMultiplier();

			/* Get fractional error */
			inclk = (inclk * 256) / (uint64_t) (256 + mult);
		}
	}

	return (uint32_t) inclk;
}

/* Set USART 0/1/2 UART base rate */
uint32_t Chip_Clock_SetUSARTNBaseClockRate(uint32_t rate, bool fEnable)
{
	uint32_t div, inclk;

	/* Input clock into FRG block is the main system clock */
	inclk = Chip_Clock_GetMainClockRate();

	/* Get integer divider for coarse rate */
	div = inclk / rate;
	if (div == 0) {
		div = 1;
	}

	/* Approximated rate with only integer divider */
	Chip_Clock_SetUARTClockDiv((uint8_t) div);

	if (fEnable) {
		uint32_t uart_fra_multiplier;

		/* Reset FRG */
		Chip_SYSCTL_PeriphReset(RESET_UARTFBRG);

		/* Enable fractional divider */
		Chip_SYSCTL_SetUSARTFRGDivider(0xFF);

		/* Compute the fractional divisor (the lower byte is the
		   fractional portion) */
		uart_fra_multiplier = ((inclk / div) * 256) / rate;

		/* ...just the fractional portion (the lower byte) */
		Chip_SYSCTL_SetUSARTFRGMultiplier((uint8_t) uart_fra_multiplier);
	}
	else {
		/* Disable fractional generator and use integer divider only */
		Chip_SYSCTL_SetUSARTFRGDivider(0);
	}

	return Chip_Clock_GetUSARTNBaseClockRate();
}

/* Get the IOCONCLKDIV clock rate */
uint32_t Chip_Clock_GetIOCONCLKDIVClockRate(CHIP_PIN_CLKDIV_T reg)
{
	uint32_t div = LPC_SYSCTL->IOCONCLKDIV[reg] & ~SYSCTL_IOCONCLKDIV_RESERVED;
	uint32_t main_clk = Chip_Clock_GetMainClockRate();
	
	return (div == 0) ? 0 : (main_clk / div);
}

void Chip_Clock_SetIOCONCLKDIV(CHIP_PIN_CLKDIV_T reg, uint8_t div)
{
	int t_reg = IOCONCLK_MAX-reg;
	LPC_SYSCTL->IOCONCLKDIV[t_reg] = div;
}
