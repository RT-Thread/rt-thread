/*
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
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
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

/** @defgroup BOARD_KEIL_MCB_18574357_SYSINIT LPC1857 and LPC4357 Keil MCB board System Init code
 * @ingroup BOARD_KEIL_MCB_18574357
 * The System initialization code is called prior to the application and
 * initializes the board for run-time operation. Board initialization
 * for the Keil MCB boards includes clock setup, default pin muxing, and
 * memory configuration.
 *
 * With the exception of stack space, no RW memory is used for this call.
 *
 * LPC1857 and LPC4357 Keil MCB setup<BR>
 *  Clocking:<BR>
 *   All base clocks enabled by default (Save power by disabling un-needed clocks)<BR>
 *   CPU PLL set to maximum clock frequency (as defined by MAX_CLOCK_FREQ value)<BR>
 *   SPIFI FLASH clock setup for fastest speed<BR>
 *  Pin muxing:<BR>
 *   Sets up various pin mux functions for the board (Ethernet, LEDs, etc.)<BR>
 *   Sets up the external memory controller signals<BR>
 *  Memory:<BR>
 *   Sets up DRAM and NOR FLASH.
 * @{
 */

#ifndef CORE_M0
/* SCR pin definitions for pin muxing */
typedef struct {
	uint8_t pingrp;	/* Pin group */
	uint8_t pinnum;	/* Pin number */
	uint8_t pincfg;	/* Pin configuration for SCU */
	uint8_t funcnum;/* Function number */
} PINMUX_GRP_T;

/* Structure for initial base clock states */
struct CLK_BASE_STATES {
	CGU_BASE_CLK_T clk;	/* Base clock */
	CGU_CLKIN_T clkin;	/* Base clock source, see UM for allowable souorces per base clock */
	bool autoblock_enab;/* Set to true to enable autoblocking on frequency change */
	bool powerdn;		/* Set to true if the base clock is initially powered down */
};

/* Initial base clock states are mostly on */
STATIC const struct CLK_BASE_STATES InitClkStates[] = {
	{CLK_BASE_SAFE, CLKIN_IRC, true, false},
	{CLK_BASE_APB1, CLKIN_MAINPLL, true, false},
	{CLK_BASE_APB3, CLKIN_MAINPLL, true, false},
	{CLK_BASE_USB0, CLKIN_USBPLL, true, false},
#if defined(CHIP_LPC43XX)
	{CLK_BASE_PERIPH, CLKIN_MAINPLL, true, false},
#endif
	{CLK_BASE_USB1, CLKIN_USBPLL, true, false},
#if defined(CHIP_LPC43XX)
	{CLK_BASE_SPI, CLKIN_MAINPLL, true, false},
#endif
	{CLK_BASE_PHY_TX, CLKIN_ENET_TX, true, false},
#if defined(USE_RMII)
	{CLK_BASE_PHY_RX, CLKIN_ENET_TX, true, false},
#else
	{CLK_BASE_PHY_RX, CLKIN_ENET_RX, true, false},
#endif
	{CLK_BASE_LCD, CLKIN_MAINPLL, true, true},
#if defined(CHIP_LPC43XX)
	{CLK_BASE_VADC, CLKIN_MAINPLL, true, true},
#endif
	{CLK_BASE_SDIO, CLKIN_MAINPLL, true, false},
	{CLK_BASE_SSP0, CLKIN_MAINPLL, true, false},
	{CLK_BASE_SSP1, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART0, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART1, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART2, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART3, CLKIN_MAINPLL, true, false},
	{CLK_BASE_OUT, CLKINPUT_PD, true, false},
	{CLK_BASE_APLL, CLKINPUT_PD, true, false},
	{CLK_BASE_CGU_OUT0, CLKINPUT_PD, true, false},
	{CLK_BASE_CGU_OUT1, CLKINPUT_PD, true, false}
};

/* SPIFI high speed pin mode setup */
STATIC const PINMUX_GRP_T spifipinmuxing[] = {
	{0x3, 3,  (MD_PLN_FAST),  FUNC3},
	{0x3, 4,  (MD_PLN_FAST),  FUNC3},
	{0x3, 5,  (MD_PLN_FAST),  FUNC3},
	{0x3, 6,  (MD_PLN_FAST),  FUNC3},
	{0x3, 7,  (MD_PLN_FAST),  FUNC3},
	{0x3, 8,  (MD_PLN_FAST),  FUNC3}
};

/* Setup system clocking */
STATIC void SystemSetupClocking(void)
{
	int i;

	/* Setup FLASH acceleration to target clock rate prior to clock switch */
	Chip_CREG_SetFlashAcceleration(MAX_CLOCK_FREQ);

	/* Switch main system clocking to crystal */
	Chip_Clock_EnableCrystal();
	Chip_Clock_SetBaseClock(CLK_BASE_MX, CLKIN_CRYSTAL, true, false);

	/* Setup PLL for 100MHz and switch main system clocking */
	Chip_Clock_SetupMainPLLHz(CLKIN_CRYSTAL, CRYSTAL_MAIN_FREQ_IN, 100 * 1000000, 100 * 1000000);
	Chip_Clock_SetBaseClock(CLK_BASE_MX, CLKIN_MAINPLL, true, false);

	/* Setup PLL for maximum clock */
	Chip_Clock_SetupMainPLLHz(CLKIN_CRYSTAL, CRYSTAL_MAIN_FREQ_IN, MAX_CLOCK_FREQ, MAX_CLOCK_FREQ);

	/* Setup system base clocks and initial states. This won't enable and
	   disable individual clocks, but sets up the base clock sources for
	   each individual peripheral clock. */
	for (i = 0; i < (sizeof(InitClkStates) / sizeof(InitClkStates[0])); i++) {
		Chip_Clock_SetBaseClock(InitClkStates[i].clk, InitClkStates[i].clkin,
								InitClkStates[i].autoblock_enab, InitClkStates[i].powerdn);
	}

	/* Reset and enable 32Khz oscillator */
	LPC_CREG->CREG0 &= ~((1 << 3) | (1 << 2));
	LPC_CREG->CREG0 |= (1 << 1) | (1 << 0);

	/* SPIFI pin setup is done prior to setting up system clocking */
	for (i = 0; i < (sizeof(spifipinmuxing) / sizeof(spifipinmuxing[0])); i++) {
		Chip_SCU_PinMux(spifipinmuxing[i].pingrp, spifipinmuxing[i].pinnum,
						spifipinmuxing[i].pincfg, spifipinmuxing[i].funcnum);
	}

	/* Setup a divider E for main PLL clock switch SPIFI clock to that divider.
	   Divide rate is based on CPU speed and speed of SPI FLASH part. */
#if (MAX_CLOCK_FREQ > 180000000)
	Chip_Clock_SetDivider(CLK_IDIV_E, CLKIN_MAINPLL, 5);
#else
	Chip_Clock_SetDivider(CLK_IDIV_E, CLKIN_MAINPLL, 4);
#endif
	Chip_Clock_SetBaseClock(CLK_BASE_SPIFI, CLKIN_IDIVE, true, false);
}

STATIC const PINMUX_GRP_T pinmuxing[] = {
	/* RMII pin group */
	{0x1, 19, (MD_EHS | MD_PLN | MD_EZI | MD_ZI),  FUNC0},
	{0x0, 1,  (MD_EHS | MD_PLN | MD_ZI),           FUNC6},
	{0x1, 18, (MD_EHS | MD_PLN | MD_ZI),           FUNC3},
	{0x1, 20, (MD_EHS | MD_PLN | MD_ZI),           FUNC3},
	{0x1, 17, (MD_EHS | MD_PLN | MD_EZI | MD_ZI),  FUNC3},
	{0xC, 1,  (MD_EHS | MD_PLN | MD_ZI),           FUNC3},
	{0x1, 16, (MD_EHS | MD_PLN | MD_EZI | MD_ZI),  FUNC7},
	{0x1, 15, (MD_EHS | MD_PLN | MD_EZI | MD_ZI),  FUNC3},
	{0x0, 0,  (MD_EHS | MD_PLN | MD_EZI | MD_ZI),  FUNC2},
	/* External data lines D0 .. D15 */
	{0x1, 7,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 8,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 9,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 10, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 11, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 12, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 13, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 14, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x5, 4,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 5,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 6,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 7,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 0,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 1,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 2,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x5, 3,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 2,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 3,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 4,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 5,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 6,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 7,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 8,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 9,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xE, 5,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 6,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 7,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 8,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 9,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 10, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 11, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 12, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	/* Address lines A0 .. A23 */
	{0x2, 9,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x2, 10, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x2, 11, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x2, 12, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x2, 13, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 0,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x1, 1,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x1, 2,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x2, 8,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x2, 7,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x2, 6,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x2, 2,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x2, 1,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x2, 0,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x6, 8,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC1},
	{0x6, 7,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC1},
	{0xD, 16, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 15, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xE, 0,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 1,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 2,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 3,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xE, 4,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xA, 4,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	/* EMC control signals */
	{0x1, 4,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x6, 6,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC1},
	{0xD, 13, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xD, 10, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0x6, 9,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 6,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x6, 4,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x6, 5,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{PINMUX_CLK, 0,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC0},
	{PINMUX_CLK, 1,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC0},
	{PINMUX_CLK, 2,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC0},
	{PINMUX_CLK, 3,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC0},
	{0x6, 11, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x6, 12, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x6, 10, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0xD, 0,  (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC2},
	{0xE, 13, (MD_PLN | MD_EZI | MD_ZI | MD_EHS),  FUNC3},
	{0x1, 3,  MD_PLN_FAST,                         FUNC3},
	{0x1, 4,  MD_PLN_FAST,                         FUNC3},
	{0x6, 6,  MD_PLN_FAST,                         FUNC1},
	{0x1, 5,  MD_PLN_FAST,                         FUNC3},
	{0x1, 6,  MD_PLN_FAST,                         FUNC3},
	/* Board LEDs */
	{0xD, 10, (MD_PLN),                            FUNC4},
	{0xD, 11, (MD_PLN),                            FUNC4},
	{0xD, 12, (MD_PLN),                            FUNC4},
	{0xD, 13, (MD_PLN),                            FUNC4},
	{0xD, 14, (MD_PLN),                            FUNC4},
	{0x9, 0,  (MD_PLN),                            FUNC0},
	{0x9, 1,  (MD_PLN),                            FUNC0},
	{0x9, 2,  (MD_PLN),                            FUNC0},
	/* SSP0 */
	{0xF, 0,  (MD_PLN_FAST),                       FUNC0},
	{0xF, 1,  (MD_PLN_FAST),                       FUNC4},
	{0xF, 2,  (MD_PLN_FAST),                       FUNC2},
	{0xF, 3,  (MD_PLN_FAST),                       FUNC2},
	/* LCD interface, 16bpp */
	{0x4, 1,  MD_PUP,                              FUNC5},
	{0x4, 2,  MD_PUP,                              FUNC2},
	{0x4, 5,  MD_PUP,                              FUNC2},
	{0x4, 6,  MD_PUP,                              FUNC2},
	{0x4, 7,  MD_PUP,                              FUNC0},
	{0x4, 9,  MD_PUP,                              FUNC2},
	{0x4, 10, MD_PUP,                              FUNC2},
	{0x7, 0,  MD_PUP,                              FUNC0},
	{0x7, 6,  MD_PUP,                              FUNC3},
	{0x8, 3,  MD_PUP,                              FUNC3},
	{0x8, 4,  MD_PUP,                              FUNC3},
	{0x8, 5,  MD_PUP,                              FUNC3},
	{0x8, 6,  MD_PUP,                              FUNC3},
	{0x8, 7,  MD_PUP,                              FUNC3},
	{0xB, 0,  MD_PUP,                              FUNC2},
	{0xB, 1,  MD_PUP,                              FUNC2},
	{0xB, 2,  MD_PUP,                              FUNC2},
	{0xB, 3,  MD_PUP,                              FUNC2},
	{0xB, 4,  MD_PUP,                              FUNC2},
	{0xB, 5,  MD_PUP,                              FUNC2},
	{0xB, 6,  MD_PUP,                              FUNC2},
	/*  I2S  */
	{0x3, 0,  MD_PLN_FAST,                         FUNC2},
	{0x6, 0,  MD_PLN_FAST,                         FUNC4},
	{0x7, 2,  MD_PLN_FAST,                         FUNC2},
	{0x6, 2,  MD_PLN_FAST,                         FUNC3},
	{0x7, 1,  MD_PLN_FAST,                         FUNC2},
	{0x6, 1,  MD_PLN_FAST,                         FUNC3},
};

/* Sets up system pin muxing */
STATIC void SystemSetupMuxing(void)
{
	int i;

	/* Setup system level pin muxing */
	for (i = 0; i < (sizeof(pinmuxing) / sizeof(pinmuxing[0])); i++) {
		Chip_SCU_PinMux(pinmuxing[i].pingrp, pinmuxing[i].pinnum,
						pinmuxing[i].pincfg, pinmuxing[i].funcnum);
	}
}

/* EMC clock delay */
#define CLK0_DELAY 7

/* Keil SDRAM timing and chip Config */
STATIC const IP_EMC_DYN_CONFIG_Type MT48LC4M32_config = {
	EMC_NANOSECOND(64000000 / 4096),	/* Row refresh time */
	0x01,	/* Command Delayed */
	EMC_NANOSECOND(18),
	EMC_NANOSECOND(42),
	EMC_NANOSECOND(70),
	EMC_CLOCK(0x01),
	EMC_CLOCK(0x05),
	EMC_NANOSECOND(12),
	EMC_NANOSECOND(60),
	EMC_NANOSECOND(60),
	EMC_NANOSECOND(70),
	EMC_NANOSECOND(12),
	EMC_CLOCK(0x02),
	{
		{
			EMC_ADDRESS_DYCS0,	/* Keil Board uses DYCS0 for SDRAM */
			3,	/* RAS */

			EMC_DYN_MODE_WBMODE_PROGRAMMED |
			EMC_DYN_MODE_OPMODE_STANDARD |
			EMC_DYN_MODE_CAS_3 |
			EMC_DYN_MODE_BURST_TYPE_SEQUENTIAL |
			EMC_DYN_MODE_BURST_LEN_4,

			EMC_DYN_CONFIG_DATA_BUS_32 |
			EMC_DYN_CONFIG_LPSDRAM |
			EMC_DYN_CONFIG_4Mx32_4BANKS_12ROWS_8COLS |
			EMC_DYN_CONFIG_MD_SDRAM
		},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	}
};

/* Keil NorFlash timing and chip Config */
/* FIXME : Keil NOR FLASH not yet tested */
STATIC const IP_EMC_STATIC_CONFIG_Type S29GL64N90_config = {
	0,
	EMC_STATIC_CONFIG_MEM_WIDTH_32 |
	EMC_STATIC_CONFIG_CS_POL_ACTIVE_LOW |
	EMC_STATIC_CONFIG_BLS_HIGH /* |
							      EMC_CONFIG_BUFFER_ENABLE*/,

	EMC_NANOSECOND(0),
	EMC_NANOSECOND(65),
	EMC_NANOSECOND(90),
	EMC_NANOSECOND(90),
	EMC_NANOSECOND(35),
	EMC_CLOCK(4)
};

/* Setup external memories */
STATIC void SystemSetupMemory(void)
{
	/* Setup EMC Delays */
	/* Move all clock delays together */
	LPC_SCU->EMCDELAYCLK = ((CLK0_DELAY) | (CLK0_DELAY << 4) | (CLK0_DELAY << 8) | (CLK0_DELAY << 12));

	/* Setup EMC Clock Divider for divide by 2 */
	Chip_Clock_EnableOpts(CLK_MX_EMC_DIV, true, true, 2);
	LPC_CREG->CREG6 |= (1 << 16);
	Chip_Clock_Enable(CLK_MX_EMC);

	/* Init EMC Controller -Enable-LE mode- clock ratio 1:1 */
	Chip_EMC_Init(1, 0, 0);
	/* Init EMC Dynamic Controller */
	Chip_EMC_Dynamic_Init((IP_EMC_DYN_CONFIG_Type *) &MT48LC4M32_config);
	/* Init EMC Static Controller CS0 */
	Chip_EMC_Static_Init((IP_EMC_STATIC_CONFIG_Type *) &S29GL64N90_config);

	/* Enable Buffer for External Flash */
	LPC_EMC->STATICCONFIG0 |= 1 << 19;
}

#endif

/**
 * @brief	Setup the system
 *			SystemInit() is called prior to the application and sets up system
 *			clocking, memory, and any resources needed prior to the application
 *			starting.
 * @return	none
 */
void SystemInit(void)
{
#if defined(CORE_M3) || defined(CORE_M4)
	unsigned int *pSCB_VTOR = (unsigned int *) 0xE000ED08;

#if defined(__IAR_SYSTEMS_ICC__)
	extern void *__vector_table;

	*pSCB_VTOR = (unsigned int) &__vector_table;
#elif defined(__CODE_RED)
	extern void *g_pfnVectors;

	*pSCB_VTOR = (unsigned int) &g_pfnVectors;
#elif defined(__ARMCC_VERSION)
	extern void *__Vectors;

	*pSCB_VTOR = (unsigned int) &__Vectors;
#endif

#if defined(__FPU_PRESENT) && __FPU_PRESENT == 1
	fpuInit();
#endif

	/* Setup system clocking and memory. This is done early to allow the
	   application and tools to clear memory and use scatter loading to
	   external memory. */
	SystemSetupClocking();
	SystemSetupMuxing();
	SystemSetupMemory();
#endif
}

/**
 * @}
 */
