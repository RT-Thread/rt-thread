/*
 * @brief LPC18xx/43xx GPIO driver
 *
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

#ifndef __GPIO_18XX_43XX_H_
#define __GPIO_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup GPIO_18XX_43XX CHIP: LPC18xx/43xx GPIO Driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Initialize GPIO block
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_Init(void)
{
	IP_GPIO_Init(LPC_GPIO_PORT);
}

/**
 * @brief	Set a GPIO port/bit state
 * @param	Port	: GPIO port to set
 * @param	Bit		: GPIO bit to set
 * @param	Setting	: true for high, false for low
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_WritePortBit(uint32_t Port, uint8_t Bit, bool Setting)
{
	IP_GPIO_WritePortBit(LPC_GPIO_PORT, Port, Bit, Setting);
}

/**
 * @brief	Seta GPIO direction
 * @param	Port	: GPIO port to set
 * @param	Bit		: GPIO bit to set
 * @param	Setting	: true for output, false for input
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_WriteDirBit(uint32_t Port, uint8_t Bit, bool Setting)
{
	IP_GPIO_WriteDirBit(LPC_GPIO_PORT, Port, Bit, Setting);
}

/**
 * @brief	Read a GPIO state
 * @param	Port	: GPIO port to read
 * @param	Bit		: GPIO bit to read
 * @return	true of the GPIO is high, false if low
 */
STATIC INLINE bool Chip_GPIO_ReadPortBit(uint32_t Port, uint8_t Bit)
{
	return IP_GPIO_ReadPortBit(LPC_GPIO_PORT, Port, Bit);
}

/**
 * @brief	Read a GPIO direction (out ot in)
 * @param	Port	: GPIO port to read
 * @param	Bit		: GPIO bit to read
 * @return	true of the GPIO is an output, false if input
 */
STATIC INLINE bool Chip_GPIO_ReadDirBit(uint32_t Port, uint8_t Bit)
{
	return IP_GPIO_ReadDirBit(LPC_GPIO_PORT, Port, Bit);
}

/**
 * @brief	Enable GPIO Interrupt
 * @param	PortNum		: GPIO port number interrupt, should be: 0 to 7
 * @param	BitValue	: GPIO bit to enable (Not used)
 * @param	IntMode		: Interrupt mode, should be:
 *							0: Rising edge interrupt mode
 *							1: Falling edge interrupt mode
 *							2: Active-High interrupt mode
 *							3: Active-Low interrupt mode
 * @return	None
 */
STATIC INLINE void Chip_GPIO_IntCmd(uint8_t PortNum, uint8_t BitValue, Gpio_PinInt_Mode_Enum IntMode)
{
	IP_GPIOPININT_IntCmd(LPC_GPIO_PIN_INT, PortNum, IntMode);
}

/**
 * @brief	Get GPIO Interrupt Status
 * @param	PortNum		: GPIO port number interrupt, should be: 0 to 7
 * @param	PinNum		: GPIO pin to check (Not used)
 * @param	IntMode		: Interrupt mode (Not used)
 * @return	true if interrupt is pending, otherwise false
 */
STATIC INLINE bool Chip_GPIO_IntGetStatus(uint8_t PortNum, uint8_t PinNum, uint8_t IntMode)
{
	return IP_GPIOPININT_IntGetStatus(LPC_GPIO_PIN_INT, PortNum);
}

/**
 * @brief	Clear GPIO Interrupt (Edge interrupt cases only)
 * @param	PortNum		: GPIO port number interrupt, should be: 0 to 7
 * @param	BitValue	: GPIO bit to clear (Not used)
 * @return	None
 */
STATIC INLINE void Chip_GPIO_IntClear(uint8_t PortNum, uint8_t BitValue)
{
	IP_GPIOPININT_IntClear(LPC_GPIO_PIN_INT, PortNum);
}

/**
 * @brief	GPIO Group Interrupt Pin Initialization
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @param	PortComb	: GPIO group combined enable, should be: 0 (OR functionality) and 1 (AND functionality)
 * @param	PortTrigger	: GPIO group interrupt trigger, should be: 0 (Edge-triggered) 1 (Level triggered)
 * @return	None
 */
STATIC INLINE void Chip_GPIOGP_IntInit(IP_GPIOGROUPINT_001_Type *pGPIOGPINT, uint8_t PortComb, uint8_t PortTrigger)
{
	IP_GPIOGP_IntInit(pGPIOGPINT, PortComb, PortTrigger);
}

/**
 * @brief	GPIO Group Interrupt Pin Add to Group
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @param	PortNum		: GPIO port number, should be 0 to 7
 * @param	PinNum		: GPIO pin number, should be 0 to 31
 * @param	ActiveMode	: GPIO active mode, should be 0 (active LOW) and 1 (active HIGH)
 * @return	None
 */
STATIC INLINE void Chip_GPIOGP_IntPinAdd(IP_GPIOGROUPINT_001_Type *pGPIOGPINT,
								  uint8_t PortNum,
								  uint8_t PinNum,
								  bool ActiveMode)
{
	IP_GPIOGP_IntPinAdd(pGPIOGPINT, PortNum, PinNum, ActiveMode);
}

/**
 * @brief	GPIO Group Interrupt Pin Remove from Group
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @param	PortNum		: GPIO port number, should be 0 to 7
 * @param	PinNum		: GPIO pin number, should be 0 to 31
 * @return	None
 */
STATIC INLINE void Chip_GPIOGP_IntPinRemove(IP_GPIOGROUPINT_001_Type *pGPIOGPINT, uint8_t PortNum, uint8_t PinNum)
{
	IP_GPIOGP_IntPinRemove(pGPIOGPINT, PortNum, PinNum);
}

/**
 * @brief	Get GPIO Group Interrupt Get Status
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @return	true if interrupt is pending, otherwise false
 */
STATIC INLINE bool Chip_GPIOGP_IntGetStatus(IP_GPIOGROUPINT_001_Type *pGPIOGPINT)
{
	return IP_GPIOGP_IntGetStatus(pGPIOGPINT);
}

/**
 * @brief	Clear GPIO Group Interrupt
 * @param	pGPIOGPINT	: Pointer to GPIOIR register block
 * @return	None
 */
STATIC INLINE void Chip_GPIOGP_IntClear(IP_GPIOGROUPINT_001_Type *pGPIOGPINT)
{
	IP_GPIOGP_IntClear(pGPIOGPINT);
}

/**
 * @brief	Set Direction for a GPIO port
 * @param	portNum		: Port Number
 * @param	bitValue	: GPIO bit to set
 * @param	out			: Direction value, 0 = input, !0 = output
 * @return	None
 * Bits set to '0' are not altered.
 */
void Chip_GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t out);

/**
 * @brief	Set Direction for a GPIO port
 * @param	portNum		: Port Number
 * @param	bitValue	: GPIO bit to set
 * @param	out			: Direction value, 0 = input, !0 = output
 * @return	None
 * Bits set to '0' are not altered.
 */
STATIC INLINE void Chip_FIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t out)
{
	/* Same with Chip_GPIO_SetDir() */
	Chip_GPIO_SetDir(portNum, bitValue, out);
}

/**
 * @brief	Set a GPIO port/bit to the high state
 * @param	portNum		: Port number
 * @param	bitValue	: Bit(s) in the port to set high
 * @return	None
 * Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_FIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	/* Same with GPIO_SetValue() */
	LPC_GPIO_PORT->SET[portNum] = bitValue;
}

/**
 * @brief	Set a GPIO port/bit to the low state
 * @param	portNum		: Port number
 * @param	bitValue	: Bit(s) in the port to set low
 * @return	None
 * Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_FIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	/* Same with GPIO_ClearValue() */
	LPC_GPIO_PORT->CLR[portNum] = bitValue;
}

/**
 * @brief	Read current bit states for the selected port
 * @param	portNum	: Port number to read
 * @return	Current value of GPIO port
 * The current states of the bits for the port are read, regardless of
 * whether the GPIO port bits are input or output.
 */
STATIC INLINE uint32_t Chip_FIO_ReadValue(uint8_t portNum)
{
	/* Same with GPIO_ReadValue() */
	return LPC_GPIO_PORT->PIN[portNum];
}

/**
 * @brief	Set a GPIO port/bit to the high state
 * @param	portNum		: Port number
 * @param	bitValue	: Bit(s) in the port to set high
 * @return	None
 * Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_GPIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_PORT->SET[portNum] = bitValue;
}

/**
 * @brief	Set a GPIO port/bit to the low state
 * @param	portNum		: Port number
 * @param	bitValue	: Bit(s) in the port to set low
 * @return	None
 * Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_GPIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_PORT->CLR[portNum] = bitValue;
}

/**
 * @brief	Read current bit states for the selected port
 * @param	portNum	: Port number to read
 * @return	Current value of GPIO port
 * The current states of the bits for the port are read, regardless of
 * whether the GPIO port bits are input or output.
 */
STATIC INLINE uint32_t Chip_GPIO_ReadValue(uint8_t portNum)
{
	return LPC_GPIO_PORT->PIN[portNum];
}

/**
 * @}
 */

 #ifdef __cplusplus
}
#endif

#endif /* __GPIO_18XX_43XX_H_ */
