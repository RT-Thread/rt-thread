/*
 * @brief GPIO Registers and Functions
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

#ifndef __GPIO_001_H_
#define __GPIO_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup GPIO_ADC_001 IP: GPIO register block and driver
 * @ingroup IP_Drivers
 * @{
 */

#define GPIO_PORT_BITS 32

#if defined(CHIP_LPC11UXX)
#define GPIO_PORT_COUNT 2
#endif

#if defined(CHIP_LPC18XX) || defined(CHIP_LPC43XX)
#define GPIO_PORT_COUNT 6
#endif

/**
 * @brief  GPIO port register block structure
 */
typedef struct {										/*!< GPIO_PORT Structure    */
	__IO uint8_t B[GPIO_PORT_COUNT][32];				/*!< Byte pin registers port 0 to 5; pins PIOn_0 to PIOn_31 */
	__I  uint8_t RESERVED0[4096 - (GPIO_PORT_COUNT * 32 * sizeof(uint8_t))];
	__IO uint32_t W[GPIO_PORT_COUNT][32];				/*!< Word pin registers port 0 to 5 */
	__I  uint8_t  RESERVED1[4096 - (GPIO_PORT_COUNT * 32 * sizeof(uint32_t))];
	__IO uint32_t DIR[GPIO_PORT_COUNT];					/*!< Direction registers port n */
	__I  uint32_t  RESERVED2[32 - GPIO_PORT_COUNT];
	__IO uint32_t MASK[GPIO_PORT_COUNT];				/*!< Mask register port n   */
	__I  uint32_t  RESERVED3[32 - GPIO_PORT_COUNT];
	__IO uint32_t PIN[GPIO_PORT_COUNT];					/*!< Portpin register port n */
	__I  uint32_t  RESERVED4[32 - GPIO_PORT_COUNT];
	__IO uint32_t MPIN[GPIO_PORT_COUNT];				/*!< Masked port register port n */
	__I  uint32_t  RESERVED5[32 - GPIO_PORT_COUNT];
	__IO uint32_t SET[GPIO_PORT_COUNT];					/*!< Write: Set register for port n Read: output bits for port n */
	__I  uint32_t  RESERVED6[32 - GPIO_PORT_COUNT];
	__O  uint32_t CLR[GPIO_PORT_COUNT];					/*!< Clear port n           */
	__I  uint32_t  RESERVED7[32 - GPIO_PORT_COUNT];
	__O  uint32_t NOT[GPIO_PORT_COUNT];					/*!< Toggle port n          */
} IP_GPIO_001_Type;

/**
 * @brief	Initialize GPIO block
 * @param	pGPIO	: The Base Address of the GPIO block
 * @return	Nothing
 */
STATIC INLINE void IP_GPIO_Init(IP_GPIO_001_Type *pGPIO)
{}

/**
 * @brief	Set a GPIO port/bit state
 * @param	pGPIO	: The Base Address of the GPIO block
 * @param	Port	: GPIO port to set
 * @param	Bit		: GPIO bit to set
 * @param	Setting	: true for high, false for low
 * @return	Nothing
 */
STATIC INLINE void IP_GPIO_WritePortBit(IP_GPIO_001_Type *pGPIO, uint32_t Port, uint8_t Bit, bool Setting)
{
	pGPIO->B[Port][Bit] = Setting;
}

/**
 * @brief	Seta GPIO direction
 * @param	pGPIO	: The Base Address of the GPIO block
 * @param	Port	: GPIO port to set
 * @param	Bit		: GPIO bit to set
 * @param	Setting	: true for output, false for input
 * @return	Nothing
 */
STATIC INLINE void IP_GPIO_WriteDirBit(IP_GPIO_001_Type *pGPIO, uint32_t Port, uint8_t Bit, bool Setting)
{
	if (Setting) {
		pGPIO->DIR[Port] |= 1UL << Bit;
	}
	else {
		pGPIO->DIR[Port] &= ~(1UL << Bit);
	}
}

/**
 * @brief	Read a GPIO state
 * @param	pGPIO	: The Base Address of the GPIO block
 * @param	Port	: GPIO port to read
 * @param	Bit		: GPIO bit to read
 * @return	true of the GPIO is high, false if low
 */
STATIC INLINE bool IP_GPIO_ReadPortBit(IP_GPIO_001_Type *pGPIO, uint32_t Port, uint8_t Bit)
{
	return (bool) pGPIO->B[Port][Bit];
}

/**
 * @brief	Read a GPIO direction (out ot in)
 * @param	pGPIO	: The Base Address of the GPIO block
 * @param	Port	: GPIO port to read
 * @param	Bit		: GPIO bit to read
 * @return	true of the GPIO is an output, false if input
 */
STATIC INLINE bool IP_GPIO_ReadDirBit(IP_GPIO_001_Type *pGPIO, uint32_t Port, uint8_t Bit)
{
	return (bool) (((pGPIO->DIR[Port]) >> Bit) & 1);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_001_H_ */
