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

#ifndef __SCU_18XX_43XX_H_
#define __SCU_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SCU_18XX_43XX CHIP: LPC18xx/43xx SCU Driver (configures pin functions)
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief System Control Unit register block
 */
typedef struct {
	__IO uint32_t  SFSP[16][32];
	__I  uint32_t  RESERVED0[256];
	__IO uint32_t  SFSCLK[4];			/*!< Pin configuration register for pins CLK0-3 */
	__I  uint32_t  RESERVED16[28];
	__IO uint32_t  SFSUSB;				/*!< Pin configuration register for USB */
	__IO uint32_t  SFSI2C0;				/*!< Pin configuration register for I2C0-bus pins */
	__IO uint32_t  ENAIO[3];			/*!< Analog function select registerS */
	__I  uint32_t  RESERVED17[27];
	__IO uint32_t  EMCDELAYCLK;			/*!< EMC clock delay register */
	__I  uint32_t  RESERVED18[63];
	__IO uint32_t  PINTSEL0;			/*!< Pin interrupt select register for pin interrupts 0 to 3. */
	__IO uint32_t  PINTSEL1;			/*!< Pin interrupt select register for pin interrupts 4 to 7. */
} LPC_SCU_Type;

/** Port offset definition */
#define PORT_OFFSET     0x80

/** Pin offset definition */
#define PIN_OFFSET      0x04

/** Disable pull-down and pull-up resistor at resistor at pad */
#define MD_PUP  (0x0 << 3)

/** Enable pull-down resistor at pad */
#define MD_BUK  (0x1 << 3)

/** Enable pull-up resistor at pad */
#define MD_PLN  (0x2 << 3)

/** Enable pull-down and pull-up resistor at resistor at pad (repeater mode) */
#define MD_PDN  (0x3 << 3)

/** Enable fast slew rate */
#define MD_EHS  (0x1 << 5)

/** Input buffer enable */
#define MD_EZI  (0x1 << 6)

/** Disable input glitch filter */
#define MD_ZI   (0x1 << 7)

/** EHD driver strength low bit */
#define MD_EHD0 (0x1 << 8)

/** EHD driver strength high bit */
#define MD_EHD1 (0x1 << 8)

#define MD_PLN_FAST (MD_PLN | MD_EZI | MD_ZI | MD_EHS)

/** Pin configuration for STANDARD/FAST mode I2C */
#define I2C0_STANDARD_FAST_MODE  (1 << 3 | 1 << 11)

/** Pin configuration for Fast-mode Plus I2C */
#define I2C0_FAST_MODE_PLUS (2 << 1 | 1 << 3 | 1 << 7 | 1 << 10 | 1 << 11)

#define FUNC0           0x0				/** Pin function 0 */
#define FUNC1           0x1				/** Pin function 1 */
#define FUNC2           0x2				/** Pin function 2 */
#define FUNC3           0x3				/** Pin function 3 */
#define FUNC4           0x4				/** Pin function 4 */
#define FUNC5           0x5				/** Pin function 5 */
#define FUNC6           0x6				/** Pin function 6 */
#define FUNC7           0x7				/** Pin function 7 */

/** Returns the SFSP register address in the SCU for a pin and port */
#define LPC_SCU_PIN(LPC_SCU_BASE, po, pi) (*(volatile int *) ((LPC_SCU_BASE) + ((po) * 0x80) + ((pi) * 0x4))

/** Returns the address in the SCU for a SFSCLK clock register */
#define LPC_SCU_CLK(LPC_SCU_BASE, c) (*(volatile int *) ((LPC_SCU_BASE) +0xC00 + ((c) * 0x4)))

#define PINMUX_CLK 0xFF

/**
 * @brief	Configure pin function
 * @param	port	: Port number, should be: 0..15
 * @param	pin		: Pin number, should be: 0..31
 * @param	mode	: Pin mode, should be:
 *                  - MD_PUP	:Pull-up enabled
 *                  - MD_BUK	:Plain input
 *                  - MD_PLN	:Repeater mode
 *                  - MD_PDN	:Pull-down enabled
 * @param	func	: Function mode, should be: FUNC0 to FUNC7
 * @return	None
 */
void Chip_SCU_PinMux(uint8_t port, uint8_t pin, uint8_t mode, uint8_t func);

/**
 * @brief	GPIO Interrupt Pin Select
 * @param	PortSel	: GPIO PINTSEL interrupt, should be: 0 to 7
 * @param	PortNum	: GPIO port number interrupt, should be: 0 to 7
 * @param	PinNum	: GPIO pin number Interrupt , should be: 0 to 31
 * @return	None
 */
void Chip_SCU_GPIOIntPinSel(uint8_t PortSel, uint8_t PortNum, uint8_t PinNum);

/**
 * @brief	I2C Pin Configuration
 * @param	I2C0Mode	: I2C0 mode, should be:
 *                  - I2C0_STANDARD_FAST_MODE: Standard/Fast mode transmit
 *                  - I2C0_FAST_MODE_PLUS: Fast-mode Plus transmit
 * @return	None
 */
STATIC INLINE void Chip_SCU_I2C0PinConfig(uint32_t I2C0Mode)
{
	LPC_SCU->SFSI2C0 = I2C0Mode;
}

/**
 * @brief	ADC Pin Configuration
 * @param	ADC_ID	: ADC number
 * @param	channel	: ADC channel
 * @return	None
 */
STATIC INLINE void Chip_SCU_ADC_Channel_Config(uint32_t ADC_ID, uint8_t channel)
{
	LPC_SCU->ENAIO[ADC_ID] |= 1UL << channel;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SCU_18XX_43XX_H_ */
