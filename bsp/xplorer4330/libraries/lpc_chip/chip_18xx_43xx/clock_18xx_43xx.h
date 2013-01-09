/*
 * @brief LPC18xx/43xx clock driver
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

#ifndef __CLOCK_18XX_43XX_H_
#define __CLOCK_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CLOCK_18XX_43XX CHIP: LPC18xx/43xx Clock Driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/** @defgroup CLOCK_18XX_43XX_OPTIONS CHIP: LPC18xx/43xx Clock Driver driver options
 * @ingroup CLOCK_18XX_43XX CHIP_18XX_43XX_DRIVER_OPTIONS 
 * The clock driver has options that configure it's operation at build-time.<br/>
 * MAX_CLOCK_FREQ:
 * - This define, when set, identifies the maximumCPU clock rate of the system (change this to alter running CPU speed)
 * - When this is not defined, The maximum clock rate for the CPU is used
 * <br/><p>
 * For more information on driver options see @ref LPCOPEN_DESIGN_ARPPROACH<br/>
 * @{
 */

/**
 * @}
 */

/* Internal oscillator frequency */
#define CGU_IRC_FREQ (12000000)

#ifndef MAX_CLOCK_FREQ
#if defined(CHIP_LPC43XX)
#define MAX_CLOCK_FREQ (204000000)
#else
#define MAX_CLOCK_FREQ (180000000)
#endif
#endif /* MAX_CLOCK_FREQ */

/**
 * @brief	Enables the crystal oscillator
 * @return	Nothing
 */
void Chip_Clock_EnableCrystal(void);

/**
 * @brief	Disables the crystal oscillator
 * @return	Nothing
 */
void Chip_Clock_DisableCrystal(void);

/**
 * @brief   Configures the main PLL
 * @param   Input		: Which clock input to use as the PLL input
 * @param   MinHz		: Minimum allowable PLL output frequency
 * @param   DesiredHz	: Desired PLL output frequency
 * @param   MaxHz		: Maximum allowable PLL output frequency
 * @return	Frequency of the PLL in Hz
 * Returns the configured PLL frequency or zero if the PLL can not be configured between MinHz
 * and MaxHz. This will not wait for PLL lock. Call Chip_Clock_MainPLLLocked() to determine if
 * the PLL is locked.
 */
uint32_t Chip_Clock_SetupMainPLLHz(CGU_CLKIN_T Input, uint32_t MinHz, uint32_t DesiredHz, uint32_t MaxHz);

/**
 * @brief	Directly set the PLL multipler
 * @param   Input	: Which clock input to use as the PLL input
 * @param	mult	: How many times to multiply the input clock
 * @return	Frequency of the PLL in Hz
 */
uint32_t Chip_Clock_SetupMainPLLMult(CGU_CLKIN_T Input, uint32_t mult);

/**
 * @brief   Returns the frequency of the main PLL
 * @return	Frequency of the PLL in Hz
 * Returns zero if the main PLL is not running.
 */
uint32_t Chip_Clock_GetMainPLLHz(void);

/**
 * @brief	Disables the main PLL
 * @return	none
 * Make sure the main PLL is not needed to clock the part before disabling it.
 * Saves power if the main PLL is not needed.
 */
void Chip_Clock_DisableMainPLL(void);

/**
 * @brief   Returns the lock status of the main PLL
 * @return	true if the PLL is locked, otherwise false
 * The main PLL should be locked prior to using it as a clock input for a base clock.
 */
bool Chip_Clock_MainPLLLocked(void);

/**
 * @brief	Sets up a CGU clock divider and it's input clock
 * @param	Divider	: CGU_IDIV_T value indicating which divider to configure
 * @param	Input	: CGU_CLKIN_T value indicating which clock source to use or CLOCKINPUT_PD to power down divider
 * @param	Divisor	: value to divide Input clock by
 * @return	Nothing
 */
void Chip_Clock_SetDivider(CGU_IDIV_T Divider, CGU_CLKIN_T Input, uint32_t Divisor);

/**
 * @brief	Gets a CGU clock divider source
 * @param	Divider	: CGU_IDIV_T value indicating which divider to get the source of
 * @return	CGU_CLKIN_T indicating which clock source is set or CLOCKINPUT_PD
 */
CGU_CLKIN_T Chip_Clock_GetDividerSource(CGU_IDIV_T Divider);

/**
 * @brief	Gets a CGU clock divider divisor
 * @param	Divider	: CGU_IDIV_T value indicating which divider to get the source of
 * @return	the divider value for the divider
 */
uint32_t Chip_Clock_GetDividerDivisor(CGU_IDIV_T Divider);

/**
 * @brief	Returns the frequency of the specified input clock source
 * @param	input	: Which clock input to return the frequency of
 * @return	Frequency of input source in Hz
 * This function returns an ideal frequency and not the actual frequency. Returns
 * zero if the clock source is disabled.
 */
uint32_t Chip_Clock_GetClockInputHz(CGU_CLKIN_T input);

/**
 * @brief	Returns the frequency of the specified base clock source
 * @param	clock	: which base clock to return the frequency of.
 * @return	Frequency of base source in Hz
 * This function returns an ideal frequency and not the actual frequency. Returns
 * zero if the clock source is disabled.
 */
uint32_t Chip_Clock_GetBaseClocktHz(CGU_BASE_CLK_T clock);

/**
 * @brief	Sets a CGU Base Clock clock source
 * @param	BaseClock	: CGU_BASE_CLK_T value indicating which base clock to set
 * @param	Input		: CGU_CLKIN_T value indicating which clock source to use or CLOCKINPUT_PD to power down base clock
 * @param	autoblocken	: Enables autoblocking during frequency change if true
 * @param	powerdn		: The clock base is setup, but powered down if true
 * @return	Nothing
 */
void Chip_Clock_SetBaseClock(CGU_BASE_CLK_T BaseClock, CGU_CLKIN_T Input, bool autoblocken, bool powerdn);

/**
 * @brief	Gets a CGU Base Clock clock source
 * @param	BaseClock	: CGU_BASE_CLK_T value indicating which base clock to get inpuot clock for
 * @return	CGU_CLKIN_T indicating which clock source is set or CLOCKINPUT_PD
 */
CGU_CLKIN_T Chip_Clock_GetBaseClock(CGU_BASE_CLK_T BaseClock);

/**
 * @brief	Enables a base clock source
 * @param	BaseClock	: CGU_BASE_CLK_T value indicating which base clock to enable
 * @return	Nothing
 */
void Chip_Clock_EnableBaseClock(CGU_BASE_CLK_T BaseClock);

/**
 * @brief	Disables a base clock source
 * @param	BaseClock	: CGU_BASE_CLK_T value indicating which base clock to disable
 * @return	Nothing
 */
void Chip_Clock_DisableBaseClock(CGU_BASE_CLK_T BaseClock);

/**
 * @brief	Enables a peripheral clock and sets clock states
 * @param	clk			: CCU_CLK_T value indicating which clock to enable
 * @param	autoen		: true to enable autoblocking on a clock rate change, false to disable
 * @param	wakeupen	: true to enable wakeup mechanism, false to disable
 * @param	div			: Divider for the clock, must be 1 for most clocks, 2 supported on others
 * @return	Nothing
 */
void Chip_Clock_EnableOpts(CCU_CLK_T clk, bool autoen, bool wakeupen, int div);

/**
 * @brief	Enables a peripheral clock
 * @param	clk	: CCU_CLK_T value indicating which clock to enable
 * @return	Nothing
 */
void Chip_Clock_Enable(CCU_CLK_T clk);

/**
 * @brief	Disables a peripheral clock
 * @param	clk	: CCU_CLK_T value indicating which clock to disable
 * @return	Nothing
 */
void Chip_Clock_Disable(CCU_CLK_T clk);

/**
 * @brief	Returns a peripheral clock rate
 * @param	clk	: CCU_CLK_T value indicating which clock to get rate for
 * @return	0 if the clock is disabled, or the rate of the clock
 */
uint32_t Chip_Clock_GetRate(CCU_CLK_T clk);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_18XX_43XX_H_ */
