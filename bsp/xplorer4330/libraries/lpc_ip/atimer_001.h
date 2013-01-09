/*
 * @brief Alarm Timer Registers and control functions
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

#ifndef __ATIMER_001_H_
#define __ATIMER_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_ATIMER_001 IP: ATimer register block and driver
 * @ingroup IP_Drivers
 * Alarm timer
 * @{
 */

/**
 * @brief Alarm Timer register block structure
 */
typedef struct {					/*!< ATIMER Structure       */
	__IO uint32_t DOWNCOUNTER;		/*!< Downcounter register   */
	__IO uint32_t PRESET;			/*!< Preset value register  */
	__I  uint32_t RESERVED0[1012];
	__O  uint32_t CLR_EN;			/*!< Interrupt clear enable register */
	__O  uint32_t SET_EN;			/*!< Interrupt set enable register */
	__I  uint32_t STATUS;			/*!< Status register        */
	__I  uint32_t ENABLE;			/*!< Enable register        */
	__O  uint32_t CLR_STAT;			/*!< Clear register         */
	__O  uint32_t SET_STAT;			/*!< Set register           */
} IP_ATIMER_001_Type;

/**
 * @brief	Close ATIMER device
 * @param	pATimer	:  Pointer to timer device
 * @return	None
 * Important: 32KHz clock must be enabled in CREG prior to this call. See
 * the User Manual for more information.
 */
void IP_ATIMER_DeInit(IP_ATIMER_001_Type *pATimer);

/**
 * @brief	Clear ATIMER Interrupt Status
 * @param	pATimer	: Pointer to timer device
 * @return	None
 */
STATIC INLINE void IP_ATIMER_ClearIntStatus(IP_ATIMER_001_Type *pATimer)
{
	pATimer->CLR_STAT = 1;
}

/**
 * @brief	Set ATIMER Interrupt Status
 * @param	pATimer	: Pointer to timer device
 * @return	None
 */
STATIC INLINE void IP_ATIMER_SetIntStatus(IP_ATIMER_001_Type *pATimer)
{
	pATimer->SET_STAT = 1;
}
/**
 * @brief	Enable ATIMER Interrupt
 * @param	pATimer	: Pointer to timer device
 * @return	None
 */
STATIC INLINE void IP_ATIMER_IntEnable(IP_ATIMER_001_Type *pATimer)
{
	pATimer->SET_EN = 1;
}

/**
 * @brief	Disable ATIMER Interrupt
 * @param	pATimer	: Pointer to timer device
 * @return	None
 */
STATIC INLINE void IP_ATIMER_IntDisable(IP_ATIMER_001_Type *pATimer)
{
	pATimer->CLR_EN = 1;
}

/**
 * @brief	Update Preset value
 * @param	pATimer	: Pointer to timer device
 * @param	PresetValue	updated preset value
 * @return	Nothing
 */
STATIC INLINE void IP_ATIMER_UpdatePresetValue(IP_ATIMER_001_Type *pATimer, uint32_t PresetValue)
{
	pATimer->PRESET = PresetValue;
}

/**
 * @brief	Read value of preset register
 * @param	pATimer	: Pointer to timer/counter device
 * @return	Value of capture register
 */
STATIC INLINE uint32_t IP_ATIMER_GetPresetValue(IP_ATIMER_001_Type *pATimer)
{
	return pATimer->PRESET;
}

/**
 * @brief	Returns enable state of ATimer interrupt
 * @param	pATimer	: Pointer to timer/counter device
 * @return	!0 if the ATimer interrupt is enabled, otherwise 0
 */
STATIC INLINE uint32_t IP_ATIMER_GetIntEnableState(IP_ATIMER_001_Type *pATimer)
{
	return pATimer->ENABLE;
}

/**
 * @brief	Returns current pending state of ATimer interrupt
 * @param	pATimer	: Pointer to timer/counter device
 * @return	!0 if the ATimer interrupt is asserted, otherwise 0
 */
STATIC INLINE uint32_t IP_ATIMER_GetIntPendingState(IP_ATIMER_001_Type *pATimer)
{
	return pATimer->STATUS;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ATIMER_001_H_ */
