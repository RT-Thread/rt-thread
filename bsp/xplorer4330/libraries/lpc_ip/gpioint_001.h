/*
 * @brief GPIO Interrupt Registers and control functions
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

#ifndef __GPIOINT_001_H_
#define __GPIOINT_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_GPIOINT_001 IP: GPIO Interrupt register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief GPIO Interrupt register block structure
 */
typedef struct {
	__I  uint32_t Status;		/*!< GPIO overall Interrupt Status Register */
	__I  uint32_t StatR0;		/*!< GPIO Interrupt Status Register 0 for Rising edge */
	__I  uint32_t StatF0;		/*!< GPIO Interrupt Status Register 0 for Falling edge */
	__O  uint32_t Clr0;			/*!< GPIO Interrupt Clear  Register 0 */
	__IO uint32_t EnR0;			/*!< GPIO Interrupt Enable Register 0 for Rising edge */
	__IO uint32_t EnF0;			/*!< GPIO Interrupt Enable Register 0 for Falling edge */
	uint32_t RESERVED0[3];
	__I  uint32_t StatR2;		/*!< GPIO Interrupt Status Register 2 for Rising edge */
	__I  uint32_t StatF2;		/*!< GPIO Interrupt Status Register 2 for Falling edge */
	__O  uint32_t Clr2;			/*!< GPIO Interrupt Clear  Register 2 */
	__IO uint32_t EnR2;			/*!< GPIO Interrupt Enable Register 2 for Rising edge */
	__IO uint32_t EnF2;			/*!< GPIO Interrupt Enable Register 2 for Falling edge */
} IP_GPIOINT_001_Type;

typedef enum {
	IP_GPIOINT_RISING_EDGE = 0x01,
	IP_GPIOINT_FALLING_EDGE = 0x02
} Gpio_Int_Mode_Enum;

/**
 * @brief	Enable GPIO Interrupt
 * @param	pGPIOPININT	: Pointer to GPIO interrupt register block
 * @param	PortNum		: GPIO port number interrupt, should be: 0 (port 0) or 2 (port 2)
 * @param	BitValue	: GPIO Bit value that contains all bits on GPIO to enable, should be 0 to 0xFFFFFFFF
 * @param	IntMode		: Interrupt mode, 0 = rising edge, 1 = falling edge
 * @return	None
 */
void IP_GPIOINT_IntCmd(IP_GPIOINT_001_Type *pGPIOPININT, uint8_t PortNum, uint32_t BitValue, Gpio_Int_Mode_Enum IntMode);

/**
 * @brief	Get GPIO Interrupt Status
 * @param	pGPIOPININT	: Pointer to GPIO interrupt register block
 * @param	PortNum		: GPIO port number interrupt, should be: 0 (port 0) or 2 (port 2)
 * @param	PinNum		: Pin number, should be: 0..30(with port 0) and 0..13 (with port 2)
 * @param	IntMode		: Interrupt mode, 0 = rising edge, 1 = falling edge
 * @return	true if interrupt is pending, otherwise false
 */
bool IP_GPIOINT_IntGetStatus(IP_GPIOINT_001_Type *pGPIOPININT,
							 uint8_t PortNum,
							 uint32_t PinNum,
							 Gpio_Int_Mode_Enum IntMode);

/**
 * @brief	Clear GPIO Interrupt (Edge interrupt cases only)
 * @param	pGPIOPININT	: Pointer to GPIO interrupt register block
 * @param	PortNum		: GPIO port number interrupt, should be: 0 (port 0) or 2 (port 2)
 * @param	BitValue	: GPIO Bit value that contains all bits on GPIO to enable, should be 0 to 0xFFFFFFFF
 * @return	None
 */
void IP_GPIOINT_IntClear(IP_GPIOINT_001_Type *pGPIOPININT, uint8_t PortNum, uint32_t BitValue);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPIOINT_001_H_ */
