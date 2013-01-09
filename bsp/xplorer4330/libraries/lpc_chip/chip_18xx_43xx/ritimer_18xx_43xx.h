/*
 * @brief LPC18xx/43xx RITimer chip driver
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

#ifndef __RITIMER_18XX_43XX_H_
#define __RITIMER_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup RIT_18XX_43XX CHIP: LPC18xx/43xx RIT driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Initialize the RIT
 * @return	None
 */
STATIC INLINE void Chip_RIT_Init(void)
{
	IP_RIT_Init(LPC_RITIMER);
}

/**
 * @brief	DeInitialize the RIT
 * @return	None
 */
STATIC INLINE void Chip_RIT_DeInit(void)
{
	IP_RIT_DeInit(LPC_RITIMER);
}

/**
 * @brief	Enable/Disable Timer
 * @param	NewState	: ENABLE to enable timer, DISABLE to stop timer
 * @return	None
 */
STATIC INLINE void Chip_RIT_Cmd(FunctionalState NewState)
{
	IP_RIT_Enable(LPC_RITIMER, NewState);
}

/**
 * @brief	Enable or disable timer debug
 * @param	NewState	: ENABLE to halt timer whenever a hardware break condition occurs
 * @return	None
 */
STATIC INLINE void Chip_RIT_TimerDebugCmd(FunctionalState NewState)
{
	IP_RIT_TimerDebugCmd(LPC_RITIMER, NewState);
}

/**
 * @brief	Check whether interrupt flag is set or not
 * @return	Current interrupt status, either ET or UNSET
 */
STATIC INLINE IntStatus Chip_RIT_GetIntStatus(void)
{
	return IP_RIT_GetIntStatus(LPC_RITIMER);
}

/**
 * @brief	Set a tick value for the interrupt to time out
 * @param	val	: value (in ticks) of the interrupt to be set
 * @return	None
 */
STATIC INLINE void Chip_RIT_SetCOMPVAL(uint32_t val)
{
	IP_RIT_SetCOMPVAL(LPC_RITIMER, val);
}

/**
 * @brief	Enables or clears the RIT or interrupt
 * @param	val	: RIT to be set, one or more RIT_CTRL_* values
 * @return	None
 */
STATIC INLINE void Chip_RIT_EnableCTRL(uint32_t val)
{
	IP_RIT_EnableCTRL(LPC_RITIMER, val);
}

/**
 * @brief	Clears the RIT interrupt
 * @return	None
 */
STATIC INLINE void Chip_RIT_ClearInt(void)
{
	IP_RIT_EnableCTRL(LPC_RITIMER, RIT_CTRL_INT);
}

/**
 * @brief	Returns the current RIT Counter value
 * @return	the current timer counter value
 */
STATIC INLINE uint32_t Chip_RIT_GetCounter(void)
{
	return IP_RIT_GetCounter(LPC_RITIMER);
}

/**
 * @brief	Set timer interval value
 * @param	time_interval	: timer interval value (ms)
 * @return	None
 */
void Chip_RIT_SetTimerInterval(uint32_t time_interval);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RITIMER_18XX_43XX_H_ */
