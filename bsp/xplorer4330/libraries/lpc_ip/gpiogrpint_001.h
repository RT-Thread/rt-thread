/*
 * @brief GPIO Group Interrupt Registers and control functions
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

#ifndef __GPIOGRPINT_001_H_
#define __GPIOGRPINT_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_GPIOGRPINT_001 IP: GPIO Grouped Interrupts register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief GPIO grouped interrupt register block structure
 */
typedef struct {					/*!< GPIO_GROUP_INTn Structure */
	__IO uint32_t  CTRL;			/*!< GPIO grouped interrupt control register */
	__I  uint32_t  RESERVED0[7];
	__IO uint32_t  PORT_POL[8];		/*!< GPIO grouped interrupt port polarity register */
	__IO uint32_t  PORT_ENA[8];		/*!< GPIO grouped interrupt port m enable register */
} IP_GPIOGROUPINT_001_Type;

/**
 * @brief	GPIO Group Interrupt Pin Initialization
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @param	PortComb	: GPIO group combined enable, should be: 0 (OR functionality) and 1 (AND functionality)
 * @param	PortTrigger	: GPIO group interrupt trigger, should be: 0 (Edge-triggered) 1 (Level triggered)
 * @return	None
 */
STATIC INLINE void IP_GPIOGP_IntInit(IP_GPIOGROUPINT_001_Type *pGPIOGPINT, uint8_t PortComb, uint8_t PortTrigger)
{
	pGPIOGPINT->CTRL = ((PortTrigger & 0x1) << 2) | ((PortComb & 0x1) << 1);
}

/**
 * @brief	GPIO Group Interrupt Pin Add to Group
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @param	PortNum		: GPIO port number, should be 0 to 7
 * @param	PinNum		: GPIO pin number, should be 0 to 31
 * @param	ActiveMode	: GPIO active mode, should be 0 (active LOW) and 1 (active HIGH)
 * @return	None
 */
void IP_GPIOGP_IntPinAdd(IP_GPIOGROUPINT_001_Type *pGPIOGPINT, uint8_t PortNum, uint8_t PinNum, bool ActiveMode);

/**
 * @brief	GPIO Group Interrupt Pin Remove from Group
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @param	PortNum		: GPIO port number, should be 0 to 7
 * @param	PinNum		: GPIO pin number, should be 0 to 31
 * @return	None
 */
STATIC INLINE void IP_GPIOGP_IntPinRemove(IP_GPIOGROUPINT_001_Type *pGPIOGPINT, uint8_t PortNum, uint8_t PinNum)
{
	/* configure to PORT_ENA register */
	pGPIOGPINT->PORT_ENA[PortNum] &= ~(1 << PinNum);
}

/**
 * @brief	Get GPIO Group Interrupt Get Status
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @return	true if interrupt is pending, otherwise false
 */
STATIC INLINE bool IP_GPIOGP_IntGetStatus(IP_GPIOGROUPINT_001_Type *pGPIOGPINT)
{
	return (bool) (pGPIOGPINT->CTRL & 0x01);
}

/**
 * @brief	Clear GPIO Group Interrupt
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @return	None
 */
STATIC INLINE void IP_GPIOGP_IntClear(IP_GPIOGROUPINT_001_Type *pGPIOGPINT)
{
	pGPIOGPINT->CTRL |= 0x01;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPIOGRPINT_001_H_ */
