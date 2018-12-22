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

#ifndef __CLOCK_8XX_H_
#define __CLOCK_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CLOCK_8XX CHIP: LPC8xx Clock Driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/* Internal oscillator frequency */
#define SYSCTL_IRC_FREQ     (12000000)
#ifndef MAX_CLOCK_FREQ
#define MAX_CLOCK_FREQ		(30000000)
#endif

/**
 * Clock sources for system and USB PLLs
 */
typedef enum CHIP_SYSCTL_PLLCLKSRC {
	SYSCTL_PLLCLKSRC_IRC = 0,		/*!< Internal oscillator */
	SYSCTL_PLLCLKSRC_SYSOSC,		/*!< Crystal (system) oscillator */
	SYSCTL_PLLCLKSRC_RESERVED,
	SYSCTL_PLLCLKSRC_EXT_CLKIN,	/*!< External clock input */
} CHIP_SYSCTL_PLLCLKSRC_T;

/**
 * Watchdog oscillator analog output frequency selection
 * values enum (plus or minus 40%)
 */
typedef enum CHIP_WDTLFO_OSC {
	WDTLFO_OSC_ILLEGAL,
	WDTLFO_OSC_0_60,	/*!< 0.6 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_05,	/*!< 1.05 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_40,	/*!< 1.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_75,	/*!< 1.75 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_10,	/*!< 2.1 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_40,	/*!< 2.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_70,	/*!< 2.7 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_00,	/*!< 3.0 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_25,	/*!< 3.25 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_50,	/*!< 3.5 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_75,	/*!< 3.75 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_00,	/*!< 4.0 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_20,	/*!< 4.2 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_40,	/*!< 4.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_60		/*!< 4.6 MHz watchdog/LFO rate */
} CHIP_WDTLFO_OSC_T;

/**
 * Clock sources for main system clock
 */
typedef enum CHIP_SYSCTL_MAINCLKSRC {
	SYSCTL_MAINCLKSRC_IRC = 0,		/*!< Internal oscillator */
	SYSCTL_MAINCLKSRC_PLLIN,		/*!< System PLL input */
	SYSCTL_MAINCLKSRC_WDTOSC,		/*!< Watchdog oscillator rate */
	SYSCTL_MAINCLKSRC_PLLOUT,		/*!< System PLL output */
} CHIP_SYSCTL_MAINCLKSRC_T;

/**
 * System and peripheral clocks enum
 */
typedef enum CHIP_SYSCTL_CLOCK {
	SYSCTL_CLOCK_SYS = 0,	/*!< System clock */
	SYSCTL_CLOCK_ROM,		/*!< ROM clock */
	SYSCTL_CLOCK_RAM,		/*!< RAM clock */
	SYSCTL_CLOCK_FLASHREG,	/*!< FLASH register interface clock */
	SYSCTL_CLOCK_FLASH,		/*!< FLASH array access clock */
	SYSCTL_CLOCK_I2C0,		/*!< I2C0 clock */
	SYSCTL_CLOCK_GPIO,		/*!< GPIO clock */
	SYSCTL_CLOCK_SWM,		/*!< Switch matrix clock */
	SYSCTL_CLOCK_SCT,		/*!< State configurable timer clock */
	SYSCTL_CLOCK_WKT,		/*!< Self wake-up timer clock */
	SYSCTL_CLOCK_MRT,		/*!< Multi-rate timer clock */
	SYSCTL_CLOCK_SPI0,		/*!< SPI0 clock */
	SYSCTL_CLOCK_SPI1,		/*!< SPI01 clock */
	SYSCTL_CLOCK_CRC,		/*!< CRC clock */
	SYSCTL_CLOCK_UART0,		/*!< UART0 clock */
	SYSCTL_CLOCK_UART1,		/*!< UART1 clock */
	SYSCTL_CLOCK_UART2,		/*!< UART2 clock */
	SYSCTL_CLOCK_WWDT,		/*!< Watchdog clock */
	SYSCTL_CLOCK_IOCON,		/*!< IOCON clock */
	SYSCTL_CLOCK_ACOMP,		/*!< Analog comparator clock */

	/* LPC82x Specific Clocks */
	SYSCTL_CLOCK_I2C1 = 21, /*!< I2C1 Clock */
	SYSCTL_CLOCK_I2C2,      /*!< I2C2 Clock */
	SYSCTL_CLOCK_I2C3,      /*!< I2C3 Clock */
	SYSCTL_CLOCK_ADC,       /*!< 12-Bit ADC Clock */
	SYSCTL_CLOCK_MTB = 26,  /*!< Macro Trace Buffer [USED FOR DEBUGGING] */
	SYSCTL_CLOCK_DMA = 29,  /*!< DMA Clock */
} CHIP_SYSCTL_CLOCK_T;

/* Clock name alias */
#define SYSCTL_CLOCK_I2C       SYSCTL_CLOCK_I2C0
#define SYSCTL_CLOCK_ACMP     SYSCTL_CLOCK_ACOMP

/**
 * Clock sources for CLKOUT
 */
typedef enum CHIP_SYSCTL_CLKOUTSRC {
	SYSCTL_CLKOUTSRC_IRC = 0,		/*!< Internal oscillator for CLKOUT */
	SYSCTL_CLKOUTSRC_SYSOSC,		/*!< System oscillator for CLKOUT */
	SYSCTL_CLKOUTSRC_WDTOSC,		/*!< Watchdog oscillator for CLKOUT */
	SYSCTL_CLKOUTSRC_MAINSYSCLK,	/*!< Main system clock for CLKOUT */
} CHIP_SYSCTL_CLKOUTSRC_T;

/**
 * @brief	Set System PLL divider values
 * @param	msel    : PLL feedback divider value
 * @param	psel    : PLL post divider value
 * @return	Nothing
 * @note	See the user manual for how to setup the PLL
 */
STATIC INLINE void Chip_Clock_SetupSystemPLL(uint8_t msel, uint8_t psel)
{
	LPC_SYSCTL->SYSPLLCTRL = (msel & 0x1F) | ((psel & 0x3) << 5);
}

/**
 * @brief	Read System PLL status
 * @return	true if the PLL is locked, false if not locked
 */
STATIC INLINE bool Chip_Clock_IsSystemPLLLocked(void)
{
	return (bool) ((LPC_SYSCTL->SYSPLLSTAT & 1) != 0);
}

/**
 * @brief	Setup Watchdog oscillator rate and divider
 * @param	wdtclk	: Selected watchdog clock rate
 * @param	div		: Watchdog divider value, even value between 2 and 64
 * @return	Nothing
 * @note	Watchdog rate = selected rate divided by divider rate
 */
STATIC INLINE void Chip_Clock_SetWDTOSC(CHIP_WDTLFO_OSC_T wdtclk, uint8_t div)
{
	LPC_SYSCTL->WDTOSCCTRL  = (((uint32_t) wdtclk) << 5) | ((div >> 1) - 1);
}

/**
 * @brief   Returns the main clock source
 * @return	Main clock source
 */
STATIC INLINE CHIP_SYSCTL_MAINCLKSRC_T Chip_Clock_GetMainClockSource(void)
{
	return (CHIP_SYSCTL_MAINCLKSRC_T) (LPC_SYSCTL->MAINCLKSEL & ~SYSCTL_MAINCLKSEL_RESERVED);
}

/**
 * @brief	Set system clock divider
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetSysClockDiv(uint32_t div)
{
	LPC_SYSCTL->SYSAHBCLKDIV  = div;
}

/**
 * @brief	Enable system or peripheral clock
 * @param	clk	: Clock to enable
 * @return	Nothing
 */
STATIC INLINE void Chip_Clock_EnablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
	LPC_SYSCTL->SYSAHBCLKCTRL = (1 << clk) | (LPC_SYSCTL->SYSAHBCLKCTRL & ~SYSCTL_SYSAHBCLKCTRL_RESERVED);
}

/**
 * @brief	Disable system or peripheral clock
 * @param	clk	: Clock to disable
 * @return	Nothing
 */
STATIC INLINE void Chip_Clock_DisablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
	LPC_SYSCTL->SYSAHBCLKCTRL &= ~((1 << clk) | SYSCTL_SYSAHBCLKCTRL_RESERVED);
}

/**
 * @brief	Set UART divider clock
 * @param	div	: divider for UART clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The UART clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetUARTClockDiv(uint32_t div)
{
	LPC_SYSCTL->UARTCLKDIV = div;
}

/**
 * @brief	Return UART divider
 * @return	divider for UART clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetUARTClockDiv(void)
{
	return LPC_SYSCTL->UARTCLKDIV & ~SYSCTL_UARTCLKDIV_RESERVED;
}

/**
 * @brief	Set The USART Fractional Generator Divider
 * @param   div  :  Fractional Generator Divider value, should be 0xFF
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCTL_SetUSARTFRGDivider(uint8_t div)
{
	LPC_SYSCTL->UARTFRGDIV = (uint32_t) div;
}

/**
 * @brief	Get The USART Fractional Generator Divider
 * @return	Value of USART Fractional Generator Divider
 */
STATIC INLINE uint32_t Chip_SYSCTL_GetUSARTFRGDivider(void)
{
	return LPC_SYSCTL->UARTFRGDIV & ~SYSCTL_UARTFRGDIV_RESERVED;
}

/**
 * @brief	Set The USART Fractional Generator Multiplier
 * @param   mult  :  An 8-bit value (0-255) U_PCLK = UARTCLKDIV/(1 + MULT/256)
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCTL_SetUSARTFRGMultiplier(uint8_t mult)
{
	LPC_SYSCTL->UARTFRGMULT = (uint32_t) mult;
}

/**
 * @brief	Get The USART Fractional Generator Multiplier
 * @return	Value of USART Fractional Generator Multiplier
 */
STATIC INLINE uint32_t Chip_SYSCTL_GetUSARTFRGMultiplier(void)
{
	return LPC_SYSCTL->UARTFRGMULT & ~SYSCTL_UARTFRGMULT_RESERVED;
}

/**
 * @brief	Set USART 0/1/2 UART base rate (up to main clock rate)
 * @param	rate	: Desired rate for fractional divider/multipler output
 * @param	fEnable	: true to use fractional clocking, false for integer clocking
 * @return	Actual rate generated
 * @note	USARTs 0 - 2 use the same base clock for their baud rate
 *			basis. This function is used to generate that clock, while the
 *			UART driver's SetBaud functions will attempt to get the closest
 *			baud rate from this base clock without altering it. This needs
 *			to be setup prior to individual UART setup.<br>
 *			UARTs need a base clock 16x faster than the baud rate, so if you
 *			need a 115.2Kbps baud rate, you will need a clock rate of at
 *			least (115.2K * 16). The UART base clock is generated from the
 *			main system clock, so fractional clocking may be the only
 *			possible choice when using a low main system clock frequency.
 *			Do not alter the FRGCLKDIV register after this call.
 */
uint32_t Chip_Clock_SetUSARTNBaseClockRate(uint32_t rate, bool fEnable);

/**
 * @brief	Get USART 0/1/2 UART base rate
 * @return	USART 0/1/2 UART base rate
 */
uint32_t Chip_Clock_GetUSARTNBaseClockRate(void);

/**
 * @brief	Returns the main oscillator clock rate
 * @return	main oscillator clock rate
 */
STATIC INLINE uint32_t Chip_Clock_GetMainOscRate(void)
{
	return OscRateIn;
}

/**
 * @brief	Returns the internal oscillator (IRC) clock rate
 * @return	internal oscillator (IRC) clock rate
 */
STATIC INLINE uint32_t Chip_Clock_GetIntOscRate(void)
{
	return SYSCTL_IRC_FREQ;
}

/**
 * @brief	Returns the external clock input rate
 * @return	External clock input rate
 */
STATIC INLINE uint32_t Chip_Clock_GetExtClockInRate(void)
{
	return ExtRateIn;
}

/**
 * @brief	Set System PLL clock source
 * @param	src	: Clock source for system PLL
 * @return	Nothing
 * @note	This function will also toggle the clock source update register
 * to update the clock source
 */
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCTL_PLLCLKSRC_T src);

/**
 * @brief	Bypass System Oscillator and set oscillator frequency range
 * @param	bypass	: Flag to bypass oscillator
 * @param	highfr	: Flag to set oscillator range from 15-25 MHz
 * @return	Nothing
 * @note	Sets the PLL input to bypass the oscillator. This would be
 * used if an external clock that is not an oscillator is attached
 * to the XTALIN pin.
 */
void Chip_Clock_SetPLLBypass(bool bypass, bool highfr);

/**
 * @brief	Set main system clock source
 * @param	src	: Clock source for main system
 * @return	Nothing
 * @note	This function will also toggle the clock source update register
 * to update the clock source
 */
void Chip_Clock_SetMainClockSource(CHIP_SYSCTL_MAINCLKSRC_T src);

/**
 * @brief	Set CLKOUT clock source and divider
 * @param	src	: Clock source for CLKOUT
 * @param	div	: divider for CLKOUT clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The CLKOUT clock
 * rate is the clock source divided by the divider. This function will
 * also toggle the clock source update register to update the clock
 * source.
 */
void Chip_Clock_SetCLKOUTSource(CHIP_SYSCTL_CLKOUTSRC_T src, uint32_t div);

/**
 * @brief	Return estimated watchdog oscillator rate
 * @return	Estimated watchdog oscillator rate
 * @note	This rate is accurate to plus or minus 40%.
 */
uint32_t Chip_Clock_GetWDTOSCRate(void);

/**
 * @brief	Return System PLL input clock rate
 * @return	System PLL input clock rate
 */
uint32_t Chip_Clock_GetSystemPLLInClockRate(void);

/**
 * @brief	Return System PLL output clock rate
 * @return	System PLL output clock rate
 */
uint32_t Chip_Clock_GetSystemPLLOutClockRate(void);

/**
 * @brief	Return main clock rate
 * @return	main clock rate
 */
uint32_t Chip_Clock_GetMainClockRate(void);

/**
 * @brief	Return system clock rate
 * @return	system clock rate
 */
uint32_t Chip_Clock_GetSystemClockRate(void);

/**
 * @brief	Get IOCONCLKDIV clock rate
 * @param	reg	: Divider register to get
 * @return	The clock rate going to the IOCON glitch filter
 * @note	Use 0 to disable, or a divider value of 1 to 255.
 */
uint32_t Chip_Clock_GetIOCONCLKDIVClockRate(CHIP_PIN_CLKDIV_T reg);

/**
 * @brief	Set IOCONCLKDIV divider
 * @param	reg	: divider register to set
 * @param	div	: divider value for IOCONCLKDIV[reg] clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255.
 */
void Chip_Clock_SetIOCONCLKDIV(CHIP_PIN_CLKDIV_T reg, uint8_t div);

/**
 * @}
 */

 /** @defgroup IRC_8XX CHIP: LPC8xx IRC Configuration
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

 /**
 * @brief	set main / system clock using IRC and PLL
 * @param	main: main clock frequency (in MHz)
 * @param	sys	: system clock frequency (in MHz)
 * @return	bool: Success = true / fail = false
 * @note	This is a table based function. The table uses both the 
 *			main frequency and the system frequency to set the PLL.
 *			All useful main / system clock combinations are in the table.
 *			See irc_8xx.c for details.
 */
bool Chip_IRC_SetFreq(uint32_t main, uint32_t sys);

 /**
 * @brief	Set main / system clock using IRC and PLL
 * @param	sys	: system clock frequency (in MHz)
 * @return	Nothing
 * @note	This function uses the ROM set_pll() function.
 */
void Chip_IRC_SetFreq_ROM(uint32_t sys);

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_8XX_H_ */
