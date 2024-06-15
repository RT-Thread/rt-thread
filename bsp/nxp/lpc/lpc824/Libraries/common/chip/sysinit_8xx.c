/*
 * @brief LPC8xx Chip specific SystemInit
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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
#define _CHIP_COMMON_
#include "board_lpc.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
#define	CONFIG_MAIN_FREQ		60000000
#define	CONFIG_SYS_FREQ			MAX_CLOCK_FREQ

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Setup system clocking */
void Chip_SetupXtalClocking(void)
{
	/* EXT oscillator < 15MHz */
	Chip_Clock_SetPLLBypass(false, false);

	/* Turn on the SYSOSC by clearing the power down bit */
	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_SYSOSC_PD);

	/* Select the PLL input to the external oscillator */
	Chip_Clock_SetSystemPLLSource(SYSCTL_PLLCLKSRC_SYSOSC);

	/* Setup FLASH access to 2 clocks (up to 30MHz) */
	Chip_FMC_SetFLASHAccess(FLASHTIM_30MHZ_CPU);

	/* Power down PLL to change the PLL divider ratio */
	Chip_SYSCTL_PowerDown(SYSCTL_SLPWAKE_SYSPLL_PD);

	/* Configure the PLL M and P dividers */
	/* Setup PLL for main oscillator rate ((FCLKIN = 12MHz) * 5)/2 = 30MHz */
	Chip_Clock_SetupSystemPLL(4, 1);

	/* Turn on the PLL by clearing the power down bit */
	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_SYSPLL_PD);

/* Enable the clock to the Switch Matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);

	/* Wait for PLL to lock */
	while (!Chip_Clock_IsSystemPLLLocked()) {}

	Chip_Clock_SetSysClockDiv(2);

	/* Set main clock source to the system PLL. This will drive 24MHz
	   for the main clock and 24MHz for the system clock */
	Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);
}

/* Set up and initialize hardware prior to call to main */
void Chip_SetupIrcClocking(void)
{
	Chip_IRC_SetFreq(CONFIG_MAIN_FREQ, CONFIG_SYS_FREQ);
}

/* Set up and initialize hardware prior to call to main */
/* 在main()函数之前调用此函数做基本的初始化工作 */
void SystemInit(void)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
	#ifdef USE_IRC_AS_ROOT_CLOCK
		/* Use 12MHz IRC as clock source */
		Chip_SetupIrcClocking();	
	#else
		/* Use Xtal or external clock_in as clock source*/
	 Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
 	 Chip_SWM_EnableFixedPin(SWM_FIXED_XTALIN);
   Chip_SWM_EnableFixedPin(SWM_FIXED_XTALOUT);
 //  Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
   Chip_IOCON_PinSetMode(LPC_IOCON, IOCON_PIO8, PIN_MODE_INACTIVE);
   Chip_IOCON_PinSetMode(LPC_IOCON, IOCON_PIO9, PIN_MODE_INACTIVE);
                 
		Chip_SetupXtalClocking();		
	#endif
}
