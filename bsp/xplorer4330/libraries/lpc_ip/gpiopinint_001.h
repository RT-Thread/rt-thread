/*
 * @brief GPIO Pin Interrupt Registers and control functions
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

#ifndef __GPIOPININT_001_H_
#define __GPIOPININT_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_GPIOPININT_001 IP: GPIO Pin Interrupt register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief GPIO pin interrupt register block structure
 */
typedef struct {				/*!< GPIO_PIN_INT Structure */
	__IO uint32_t  ISEL;		/*!< Pin Interrupt Mode register */
	__IO uint32_t  IENR;		/*!< Pin Interrupt Enable (Rising) register */
	__O  uint32_t  SIENR;		/*!< Set Pin Interrupt Enable (Rising) register */
	__O  uint32_t  CIENR;		/*!< Clear Pin Interrupt Enable (Rising) register */
	__IO uint32_t  IENF;		/*!< Pin Interrupt Enable Falling Edge / Active Level register */
	__O  uint32_t  SIENF;		/*!< Set Pin Interrupt Enable Falling Edge / Active Level register */
	__O  uint32_t  CIENF;		/*!< Clear Pin Interrupt Enable Falling Edge / Active Level address */
	__IO uint32_t  RISE;		/*!< Pin Interrupt Rising Edge register */
	__IO uint32_t  FALL;		/*!< Pin Interrupt Falling Edge register */
	__IO uint32_t  IST;			/*!< Pin Interrupt Status register */
} IP_GPIOPININT_001_Type;

typedef enum {
	IP_GPIOPININT_RISING_EDGE = 0x01,
	IP_GPIOPININT_FALLING_EDGE = 0x02,
	IP_GPIOPININT_ACTIVE_HIGH_LEVEL = 0x04,
	IP_GPIOPININT_ACTIVE_LOW_LEVEL = 0x08
} Gpio_PinInt_Mode_Enum;

/**
 * @brief	Enable GPIO Interrupt
 * @param	pGPIOPININT : Pointer to GPIO interrupt register block
 * @param	PortNum		: GPIO port number interrupt
 * @param	IntMode		: Interrupt mode, should be:
 *							0: Rising edge interrupt mode
 *							1: Falling edge interrupt mode
 *							2: Active-High interrupt mode
 *							3: Active-Low interrupt mode
 * @return	None
 */
void IP_GPIOPININT_IntCmd(IP_GPIOPININT_001_Type *pGPIOPININT, uint8_t PortNum, Gpio_PinInt_Mode_Enum IntMode);

/**
 * @brief	Get GPIO Interrupt Status
 * @param	pGPIOPININT : Pointer to GPIO interrupt register block
 * @param	PortNum		: GPIO port number interrupt
 * @return	true if interrupt is pending, otherwise false
 */
STATIC INLINE bool IP_GPIOPININT_IntGetStatus(IP_GPIOPININT_001_Type *pGPIOPININT, uint8_t PortNum)
{
	return (bool) (((pGPIOPININT->IST) >> PortNum) & 0x01);
}

/**
 * @brief	Clear GPIO Interrupt (Edge interrupt cases only)
 * @param	pGPIOPININT : Pointer to GPIO interrupt register block
 * @param	PortNum		: GPIO port number interrupt
 * @return	None
 */
STATIC INLINE void IP_GPIOPININT_IntClear(IP_GPIOPININT_001_Type *pGPIOPININT, uint8_t PortNum)
{
	if (!(pGPIOPININT->ISEL & (1 << PortNum))) {
		pGPIOPININT->IST |= (1 << PortNum);
	}
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPIOPININT_001_H_ */
