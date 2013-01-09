/*
 * @brief LPC18xx/43xx WWDT chip driver
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

#ifndef __WWDT_18XX_43XX_H_
#define __WWDT_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup WWDT_18XX_43XX CHIP: LPC18xx/43xx WWDT driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/** WDT oscillator frequency value */
#define WDT_OSC     (CGU_IRC_FREQ)

/** WWDT interrupt enable bit */
#define WWDT_WDMOD_WDEN             ((uint32_t) (1 << 0))
/** WWDT interrupt enable bit */
#define WWDT_WDMOD_WDRESET          ((uint32_t) (1 << 1))
/** WWDT time out flag bit */
#define WWDT_WDMOD_WDTOF            ((uint32_t) (1 << 2))
/** WDT Time Out flag bit */
#define WWDT_WDMOD_WDINT            ((uint32_t) (1 << 3))
/** WWDT Protect flag bit */
#define WWDT_WDMOD_WDPROTECT        ((uint32_t) (1 << 4))

/** Minimum tick count for timer value and window value */
#define WWDT_TICKS_MIN 0xFF

/** Maximum tick count for timer value and window value */
#define WWDT_TICKS_MAX 0xFFFFFF

/**
 * @brief	Initialize the Watchdog timer
 * @return	None
 */
void Chip_WWDT_Init(void);

/**
 * @brief	Set WDT timeout constant value used for feed
 * @param	timeout	: WDT timeout in ticks, between WWDT_TICKS_MIN and WWDT_TICKS_MAX
 * @return	none
 */
STATIC INLINE void Chip_WWDT_SetTimeOut(uint32_t timeout)
{
	LPC_WWDT->TC = timeout;
}

/**
 * @brief	Feed watchdog timer
 * @return	None
 * If this function isn't called, a watchdog timer warning will occur.
 * After the warning, a timeout will occur if a feed has happened.
 */
STATIC INLINE void Chip_WWDT_Feed(void)
{
	LPC_WWDT->FEED = 0xAA;
	LPC_WWDT->FEED = 0x55;
}

/**
 * @brief	Set WWDT warning interrupt
 * @param	timeout	: WDT warning in ticks, between 0 and 1023
 * @return	None
 * This is the number of ticks after the watchdog interrupt that the
 * warning interrupt will be generated.
 */
STATIC INLINE void Chip_WWDT_SetWarning(uint32_t timeout)
{
	LPC_WWDT->WARNINT = timeout;
}

/**
 * @brief	Set WWDT window time
 * @param	timeout	: WDT timeout in ticks, between WWDT_TICKS_MIN and WWDT_TICKS_MAX
 * @return	none
 * The watchdog timer must be fed between the timeout from the Chip_WWDT_SetTimeOut()
 * function and this function, with this function defining the last tick before the
 * watchdog window interrupt occurs.
 */
STATIC INLINE void Chip_WWDT_SetWindow(uint32_t timeout)
{
	LPC_WWDT->WINDOW = timeout;
}

/**
 * @brief	Enable watchdog timer options
 * @param	options : An or'ed set of options of values
 *						WWDT_WDMOD_WDEN, WWDT_WDMOD_WDRESET, and WWDT_WDMOD_WDPROTECT
 * @return	None
 * You can enable more than one option at once (ie, WWDT_WDMOD_WDRESET |
 * WWDT_WDMOD_WDPROTECT), but use the WWDT_WDMOD_WDEN after all other options
 * are set (or unset) with no other options.
 */
STATIC INLINE void Chip_WWDT_SetOption(uint32_t options)
{
	LPC_WWDT->MOD |= options;
}

/**
 * @brief	Disable/clear watchdog timer options
 * @param	options : An or'ed set of options of values
 *						WWDT_WDMOD_WDEN, WWDT_WDMOD_WDRESET, and WWDT_WDMOD_WDPROTECT
 * @return	None
 * You can disable more than one option at once (ie, WWDT_WDMOD_WDRESET |
 * WWDT_WDMOD_WDTOF).
 */
STATIC INLINE void Chip_WWDT_UnsetOption(uint32_t options)
{
	LPC_WWDT->MOD &= ~options;
}

/**
 * @brief	Enable WWDT activity
 * @return	None
 */
STATIC INLINE void Chip_WWDT_Start(void)
{
	Chip_WWDT_SetOption(WWDT_WDMOD_WDEN);
	Chip_WWDT_Feed();
}

/**
 * @brief	Read WWDT status flag
 * @return	Watchdog status, an Or'ed value of WWDT_WDMOD_*
 */
STATIC INLINE uint32_t Chip_WWDT_GetStatus(void)
{
	return LPC_WWDT->MOD;
}

/**
 * @brief	Clear WWDT interrupt status flags
 * @param	flag	: Or'ed value of status flag(s) that you want to clear, should be:
 *              - WWDT_WDMOD_WDTOF: Clear watchdog timeout flag
 *              - WWDT_WDMOD_WDINT: Clear watchdog warning flag
 * @return	None
 */
void Chip_WWDT_ClearStatusFlag(uint32_t status);

/**
 * @brief	Get the current value of WDT
 * @return	current value of WDT
 */
STATIC INLINE uint32_t WWDT_GetCurrentCount(void)
{
	return LPC_WWDT->TV;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __WWDT_18XX_43XX_H_ */
