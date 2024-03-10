/*
 * @brief LPC8xx GPIO driver
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

#ifndef __GPIO_8XX_H_
#define __GPIO_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup GPIO_8XX CHIP: LPC8xx GPIO driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief  GPIO port register block structure
 */
typedef struct {				/*!< GPIO_PORT Structure */
	__IO uint8_t B[128][32];	/*!< Offset 0x0000: Byte pin registers ports 0 to n; pins PIOn_0 to PIOn_31 */
	__IO uint32_t W[32][32];	/*!< Offset 0x1000: Word pin registers port 0 to n */
	__IO uint32_t DIR[32];		/*!< Offset 0x2000: Direction registers port n */
	__IO uint32_t MASK[32];		/*!< Offset 0x2080: Mask register port n */
	__IO uint32_t PIN[32];		/*!< Offset 0x2100: Portpin register port n */
	__IO uint32_t MPIN[32];		/*!< Offset 0x2180: Masked port register port n */
	__IO uint32_t SET[32];		/*!< Offset 0x2200: Write: Set register for port n Read: output bits for port n */
	__O  uint32_t CLR[32];		/*!< Offset 0x2280: Clear port n */
	__O  uint32_t NOT[32];		/*!< Offset 0x2300: Toggle port n */
	__O  uint32_t DIRSET[32];   /*!< Offset 0x2380: Set Direction */
	__O  uint32_t DIRCLR[32];   /*!< Offset 0x2400: Clear Direction */
	__O  uint32_t DIRNOT[32];   /*!< Offset 0x2480: Toggle Dirction */
} LPC_GPIO_T;

/**
 * @brief	Initialize GPIO block
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_Init(LPC_GPIO_T *pGPIO)
{
	LPC_SYSCTL->SYSAHBCLKCTRL = (1 << SYSCTL_CLOCK_GPIO) | (LPC_SYSCTL->SYSAHBCLKCTRL & ~SYSCTL_SYSAHBCLKCTRL_RESERVED);

}

/**
 * @brief	De-Initialize GPIO block
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_DeInit(LPC_GPIO_T *pGPIO)
{
	LPC_SYSCTL->SYSAHBCLKCTRL &= ~((1 << SYSCTL_CLOCK_GPIO) | SYSCTL_SYSAHBCLKCTRL_RESERVED);
}

/**
 * @brief	Set GPIO direction for a single GPIO pin
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: GPIO port to set (supports port 0 only)
 * @param	pin		: GPIO pin to set direction on as output
 * @param   isOutput: If new direction is output
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_PinSetDIR(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin, bool isOutput)
{
	
	#ifdef CHIP_LPC82X
		if (isOutput)
			pGPIO->DIRSET[port] = 1UL << pin;
		else
			pGPIO->DIRCLR[port] = 1UL << pin;
	#else
		if (isOutput)
			pGPIO->DIR[port] |= 1UL << pin;
		else
			pGPIO->DIR[port] &= ~(1UL << pin);
	#endif
}

/**
 * @brief	Get GPIO direction for a single GPIO pin
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: GPIO port to read (supports port 0 only)
 * @param	pin		: GPIO pin to get direction for
 * @return	true if the GPIO is an output, false if input
 */
STATIC INLINE bool Chip_GPIO_PinGetDIR(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin)
{
	return (bool) (((pGPIO->DIR[port]) >> pin) & 1);
}

/**
 * @brief	Toggle GPIO direction for a single GPIO pin
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: GPIO port to set (supports port 0 only)
 * @param	pin		: GPIO pin to toggle direction
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_PinToggleDIR(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin)
{
#ifdef CHIP_LPC82X
	pGPIO->DIRNOT[port] = 1UL << pin;
#else
	pGPIO->DIR[port] ^= 1UL << pin;
#endif
}

/**
 * @brief	Set a GPIO pin state via the GPIO byte register
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: GPIO port to set (supports port 0 only)
 * @param	pin		: GPIO pin to set
 * @param	setting	: true for high, false for low
 * @return	Nothing
 * @note	This function replaces Chip_GPIO_WritePortBit()
 */
STATIC INLINE void Chip_GPIO_PinSetState(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin, bool setting)
{
	pGPIO->B[port][pin] = setting;
}


/**
 * @brief	Get a GPIO pin state via the GPIO byte register
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: GPIO port to read (supports port 0 only)
 * @param	pin		: GPIO pin to get state for
 * @return	true if the GPIO is high, false if low
 * @note	This function replaces Chip_GPIO_ReadPortBit()
 */
STATIC INLINE bool Chip_GPIO_PinGetState(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin)
{
	return (bool) pGPIO->B[port][pin];
}

/**
 * @brief	Get a GPIO pin state via the GPIO byte register
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: GPIO port to read (supports port 0 only)
 * @param	pin		: GPIO pin to get state for
 * @return	true if the GPIO is high, false if low
 * @note	This function replaces Chip_GPIO_ReadPortBit()
 */
STATIC INLINE void Chip_GPIO_PinToggleState(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin)
{
	pGPIO->NOT[port] = 1UL << pin;
}

/**
 * @brief	Set GPIO direction for a all selected GPIO pins
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	pinMask	: GPIO pin mask to set direction on as output (bits 0..b for pins 0..n)
 * @param   isOutput: If new direction is output
 * @return	Nothing
 * @note	Sets multiple GPIO pins to the output direction, each bit's position that is
 * high sets the corresponding pin number for that bit to an output.
 */
STATIC INLINE void Chip_GPIO_PortSetDIR(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pinMask, bool isOutput)
{
#ifdef CHIP_LPC82X
	if (isOutput)
		pGPIO->DIRSET[port] = pinMask;
	else
		pGPIO->DIRCLR[port] = pinMask;
#else
	if (isOutput)
		pGPIO->DIR[port] |= pinMask;
	else
		pGPIO->DIR[port] &= ~pinMask;
#endif
}

/**
 * @brief	Get GPIO direction for a all GPIO pins
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @return	a bitfield containing the input and output states for each pin
 * @note	For pins 0..n, a high state in a bit corresponds to an output state for the
 * same pin, while a low  state corresponds to an input state.
 */
STATIC INLINE uint32_t Chip_GPIO_PortGetDIR(LPC_GPIO_T *pGPIO, uint8_t port)
{
	return pGPIO->DIR[port];
}

/**
 * @brief	Toggle GPIO direction for a all selected GPIO pins
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	pinMask	: GPIO pin mask Toggle direction (bits 0..n for pins 0..n)
 * @return	Nothing
 * @note	Toggles multiple GPIO pin's direction, each bit's position that is
 * high toggles direction of the corresponding pin number.
 */
STATIC INLINE void Chip_GPIO_PortToggleDIR(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pinMask)
{
#ifdef CHIP_LPC82X
	pGPIO->DIRNOT[port] = pinMask;
#else
	pGPIO->DIR[port] ^= pinMask;
#endif
}

/**
 * @brief	Set all GPIO raw pin states (regardless of masking)
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	value	: Value to set all GPIO pin states (0..n) to
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_PortSetState(LPC_GPIO_T *pGPIO, uint8_t port, uint32_t value)
{
	pGPIO->PIN[port] = value;
}

/**
 * @brief	Get all GPIO raw pin states (regardless of masking)
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @return	Current (raw) state of all GPIO pins
 */
STATIC INLINE uint32_t Chip_GPIO_PortGetState(LPC_GPIO_T *pGPIO, uint8_t port)
{
	return pGPIO->PIN[port];
}

/**
 * @brief	Toggle selected GPIO output pins to the opposite state
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	pins	: pins (0..n) to toggle
 * @return	None
 * @note	Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_GPIO_PortToggleState(LPC_GPIO_T *pGPIO, uint8_t port, uint32_t pins)
{
	pGPIO->NOT[port] = pins;
}

/**
 * @brief	Set selected GPIO output pins to the high state
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	pins	: pins (0..n) to set high
 * @return	None
 * @note	Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_GPIO_PortSetOutHigh(LPC_GPIO_T *pGPIO, uint8_t port, uint32_t bmPins)
{
	pGPIO->SET[port] = bmPins;
}

/**
 * @brief	Set selected GPIO output pins to the low state
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	pins	: pins (0..n) to set low
 * @return	None
 * @note	Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
STATIC INLINE void Chip_GPIO_PortSetOutLow(LPC_GPIO_T *pGPIO, uint8_t port, uint32_t pins)
{
	pGPIO->CLR[port] = pins;
}

/**
 * @brief	Set GPIO port mask value for GPIO masked read and write
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	mask	: Mask value for read and write (only low bits are enabled)
 * @return	Nothing
 * @note	Controls which bits are set or unset when using the masked
 * GPIO read and write functions. A low state indicates the pin is settable
 * and readable via the masked write and read functions.
 */
STATIC INLINE void Chip_GPIO_PortSetMask(LPC_GPIO_T *pGPIO, uint8_t port, uint32_t mask)
{
	pGPIO->MASK[port] = mask;
}

/**
 * @brief	Get GPIO port mask value used for GPIO masked read and write
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @return	Returns value set with the Chip_GPIO_PortSetMask() function.
 * @note	A high bit in the return value indicates that that GPIO pin for the
 * port cannot be set using the masked write function.
 */
STATIC INLINE uint32_t Chip_GPIO_PortGetMask(LPC_GPIO_T *pGPIO, uint8_t port)
{
	return pGPIO->MASK[port];
}

/**
 * @brief	Set all GPIO pin states, but mask via the MASKP0 register
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @param	value	: Value to set all GPIO pin states (0..n) to
 * @return	Nothing
 */
STATIC INLINE void Chip_GPIO_PortSetMaskedState(LPC_GPIO_T *pGPIO, uint8_t port, uint32_t value)
{
	pGPIO->MPIN[port] = value;
}

/**
 * @brief	Get all GPIO pin statesm but mask via the MASKP0 register
 * @param	pGPIO	: The base of GPIO peripheral on the chip
 * @param	port	: port Number (supports port 0 only)
 * @return	Current (masked) state of all GPIO pins
 */
STATIC INLINE uint32_t Chip_GPIO_PortGetMaskedState(LPC_GPIO_T *pGPIO, uint8_t port)
{
	return pGPIO->MPIN[port];
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_8XX_H_ */
