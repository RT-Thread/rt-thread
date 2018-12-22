/*
 * @brief LPC8xx IOCON register block and driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
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

#ifndef __IOCON_8XX_H_
#define __IOCON_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IOCON_8XX CHIP: LPC8xx IOCON register block and driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

#define NUM_IOCON_PIO  (29)

/**
 * @brief Array of IOCON pin definitions passed to Chip_IOCON_SetPinMuxing() must be in this format
 */
typedef struct {
	uint32_t pin:8;			/* Pin number */
	uint32_t modefunc:24;	/* Function and mode */
} PINMUX_GRP_T;

/**
 * @brief	IOCON register block structure
 * @note	When accessing this register structure, use the PIOn enumeration
 * as the array index as the pin assignments are not mapped 1-1 with the
 * IOCON structure.<br>
 * Incorrect: LPC_IOCON->PIO0[0] = 0x1; // Index 0 does not map to pin 0!<br>
 * Correct: LPC_IOCON->PIO0[IOCON_PIO0] = 0x1; // Enumeration PIO0 maps to pin 0
 */
typedef struct {		/*!< (@ 0x40044000) IOCONFIG Structure     */
	__IO uint32_t PIO0[NUM_IOCON_PIO + 2]; /* 2 added for reserved register */
} LPC_IOCON_T;

/**
 * @brief IOCON Register bit definitions
 */
/* Pin Mode mask */
#define PIN_MODE_MASK           (0x3 <<  3)
#define PIN_MODE_BITNUM         (3)

/* Pin Hysteresis mask */
#define PIN_HYS_MASK            (0x1 <<  5)
#define PIN_HYS_BITNUM          (5)

/* Pin invert input mask */
#define PIN_INV_MASK            (0x1 <<  6)
#define PIN_INV_BITNUM          (6)

/* Pin open drain mode mask */
#define PIN_OD_MASK             (0x1 << 10)
#define PIN_OD_BITNUM           (10)

/* Pin digital filter sample mode mask */
#define PIN_SMODE_MASK          (0x3 << 11)
#define PIN_SMODE_BITNUM        (11)

/* Pin clock divider mask */
#define PIN_CLKDIV_MASK         (0x7 << 13)
#define PIN_CLKDIV_BITNUM       (13)

/* Pin I2C mode mask - valid for PIO10 & PIO11 only */
#define PIN_I2CMODE_MASK        (0x3 <<  8)
#define PIN_I2CMODE_BITNUM      (8)

/**
 * @brief IOCON Pin Numbers enum
 * Maps a pin number to an IOCON (register) array index. IOCON indexes
 * are not mapped 1-1 with pin numbers. When access the PIO0 array in
 * the LPC_IOCON_T structure, the array should be indexed with one of
 * these enumerations based on the pin that will have it's settings
 * changed.<br>
 * Example: LPC_IOCON->PIO0[IOCON_PIO0] = 0x1; // Enumeration PIO0 maps to pin 0
 */
typedef enum CHIP_PINx {
	IOCON_PIO0  =  0x11,	/*!< PIN 0 */
	IOCON_PIO1  =  0x0B,	/*!< PIN 1 */
	IOCON_PIO2  =  0x06,	/*!< PIN 2 */
	IOCON_PIO3  =  0x05,	/*!< PIN 3 */
	IOCON_PIO4  =  0x04,	/*!< PIN 4 */
	IOCON_PIO5  =  0x03,	/*!< PIN 5 */
	/* The following pins are not present in DIP8 packages */
	IOCON_PIO6  =  0x10,	/*!< PIN 6 */
	IOCON_PIO7  =  0x0F,	/*!< PIN 7 */
	IOCON_PIO8  =  0x0E,	/*!< PIN 8 */
	IOCON_PIO9  =  0x0D,	/*!< PIN 9 */
	IOCON_PIO10 =  0x08,	/*!< PIN 10 */
	IOCON_PIO11 =  0x07,	/*!< PIN 11 */
	IOCON_PIO12 =  0x02,	/*!< PIN 12 */
	IOCON_PIO13 =  0x01,	/*!< PIN 13 */
	/* The following pins are not present in DIP8 & TSSOP16 packages */
	IOCON_PIO14 =  0x12,	/*!< PIN 14 */
	IOCON_PIO15 =  0x0A,	/*!< PIN 15 */
	IOCON_PIO16 =  0x09,	/*!< PIN 16 */
	IOCON_PIO17 =  0x00,	/*!< PIN 17 */
	IOCON_PIO_NUL0 = 0x0C,	/*!< PIN NULL */

	/* The following pins are not present in DIP8, TSSOP16 & TSSOP20 packages */
	IOCON_PIO18 =  0x1E,	/*!< PIN 18 */
	IOCON_PIO19 =  0x1D,	/*!< PIN 19 */
	IOCON_PIO20 =  0x1C,	/*!< PIN 20 */
	IOCON_PIO21 =  0x1B,	/*!< PIN 21 */
	IOCON_PIO22 =  0x1A,	/*!< PIN 22 */
	IOCON_PIO23 =  0x19,	/*!< PIN 23 */
	IOCON_PIO24 =  0x18,	/*!< PIN 24 */
	IOCON_PIO25 =  0x17,	/*!< PIN 25 */
	IOCON_PIO26 =  0x16,	/*!< PIN 26 */
	IOCON_PIO27 =  0x15,	/*!< PIN 27 */
	IOCON_PIO28 =  0x14,	/*!< PIN 28 */
	IOCON_PIO_NUL1 = 0x13,	/*!< PIN NULL */
} CHIP_PINx_T;

/**
 * @brief IOCON Pin Modes enum
 */
typedef enum CHIP_PIN_MODE {
	PIN_MODE_INACTIVE = 0,	/*!< Inactive mode */
	PIN_MODE_PULLDN = 1,	/*!< Pull Down mode */
	PIN_MODE_PULLUP = 2,	/*!< Pull up mode */
	PIN_MODE_REPEATER = 3	/*!< Repeater mode */
} CHIP_PIN_MODE_T;

/**
 * @brief IOCON Digital Filter Sample modes enum
 */
typedef enum CHIP_PIN_SMODE {
	PIN_SMODE_BYPASS = 0,	/*!< Bypass input filter */
	PIN_SMODE_CYC1 = 1,		/*!< Input pulses shorter than 1 filter clock cycle are rejected */
	PIN_SMODE_CYC2 = 2,		/*!< Input pulses shorter than 2 filter clock cycles are rejected */
	PIN_SMODE_CYC3 = 3		/*!< Input pulses shorter than 3 filter clock cycles are rejected */
} CHIP_PIN_SMODE_T;

/**
 * @brief IOCON I2C Modes enum (Only for I2C pins PIO0_10 and PIO0_11)
 */
typedef enum CHIP_PIN_I2CMODE {
	PIN_I2CMODE_STDFAST = 0,	/*!< I2C standard mode/Fast mode */
	PIN_I2CMODE_GPIO = 1,		/*!< Standard I/O functionality */
	PIN_I2CMODE_FASTPLUS = 2	/*!< I2C Fast plus mode */
} CHIP_PIN_I2CMODE_T;

/**
 * @brief	Sets I/O Control pin mux
 * @param	pIOCON		: The base of IOCON peripheral on the chip
 * @param	pin			: GPIO pin to mux
 * @param	modefunc	: OR'ed values or type IOCON_*
 * @return	Nothing
 */
STATIC INLINE void Chip_IOCON_PinMuxSet(LPC_IOCON_T *pIOCON, uint8_t pin, uint32_t modefunc)
{
	pIOCON->PIO0[pin] = modefunc;
}

/**
 * @brief	Set all I/O Control pin muxing
 * @param	pIOCON	    : The base of IOCON peripheral on the chip
 * @param	pinArray    : Pointer to array of pin mux selections
 * @param	arrayLength : Number of entries in pinArray
 * @return	Nothing
 */
void Chip_IOCON_SetPinMuxing(LPC_IOCON_T *pIOCON, const PINMUX_GRP_T* pinArray, uint32_t arrayLength);

/**
 * @brief	Sets pull-up or pull-down mode for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @param	mode	: Mode (Pull-up/Pull-down mode)
 * @return	Nothing
 * @note	Do not use with pins PIO10 and PIO11.
 */
void Chip_IOCON_PinSetMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_MODE_T mode);

/**
 * @brief	Enable or disable hysteresis for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @param	enable	: true to enable, false to disable
 * @return	Nothing
 * @note	Do not use with pins PIO10 and PIO11.
 */
void Chip_IOCON_PinSetHysteresis(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, bool enable);

/**
 * @brief	Enable hysteresis for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @return	Nothing
 * @note	Do not use with pins PIO10 and PIO11.
 */
STATIC INLINE void Chip_IOCON_PinEnableHysteresis(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	pIOCON->PIO0[pin] |= PIN_HYS_MASK;
}

/**
 * @brief	Disable hysteresis for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @return	Nothing
 * @note	Do not use with pins PIO10 and PIO11.
 */
STATIC INLINE void Chip_IOCON_PinDisableHysteresis(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	pIOCON->PIO0[pin] &= ~PIN_HYS_MASK;
}

/**
 * @brief	Enable or disable invert input for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @param	invert	: true to invert, false to not to invert
 * @return	Nothing
 */
void Chip_IOCON_PinSetInputInverted(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, bool invert);

/**
 * @brief	Enable invert input for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @return	Nothing
 */
STATIC INLINE void Chip_IOCON_PinEnableInputInverted(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	pIOCON->PIO0[pin] |= PIN_INV_MASK;
}

/**
 * @brief	Disable invert input for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @return	Nothing
 */
STATIC INLINE void Chip_IOCON_PinDisableInputInverted(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	pIOCON->PIO0[pin] &= ~PIN_INV_MASK;
}

/**
 * @brief	Enables or disables open-drain mode for a pin
 * @param	pIOCON		: The base of IOCON peripheral on the chip
 * @param	pin			: Pin number
 * @param	open_drain	: true to enable open-drain mode,
 *                        false to disable open-drain mode
 * @return	Nothing
 */
void Chip_IOCON_PinSetOpenDrainMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, bool open_drain);

/**
 * @brief	Enables open-drain mode for a pin
 * @param	pIOCON		: The base of IOCON peripheral on the chip
 * @param	pin			: Pin number
 * @return	Nothing
 */
STATIC INLINE void Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	pIOCON->PIO0[pin] |= PIN_OD_MASK;
}

/**
 * @brief	Disables open-drain mode for a pin
 * @param	pIOCON		: The base of IOCON peripheral on the chip
 * @param	pin			: Pin number
 * @return	Nothing
 */
STATIC INLINE void Chip_IOCON_PinDisableOpenDrainMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	pIOCON->PIO0[pin] &= ~PIN_OD_MASK;
}

/**
 * @brief	Set pin mode to default after reset
 * @param	pIOCON		: The base of IOCON peripheral on the chip
 * @param	pin			: Pin number
 * @return	Nothing
 */
STATIC INLINE void Chip_IOCON_PinSetToDefault(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin)
{
	if (pin == IOCON_PIO10 || pin == IOCON_PIO11)
		pIOCON->PIO0[pin] = 0x80;
	else
		pIOCON->PIO0[pin] = 0x90;
}

/**
 * @brief	Sets the digital filter sampling mode for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @param	smode	: 0x0 = bypass, 0x[1..3] = 1 to 3 clock cycles.
 * @return	Nothing
 */
void Chip_IOCON_PinSetSampleMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_SMODE_T smode);

/**
 * @brief	Select peripheral clock divider for input filter sampling clock
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @param	clkdiv	: 0 = no divisor, 1...6 = PCLK/clkdiv
 * @return	Nothing
 */
void Chip_IOCON_PinSetClockDivisor(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_CLKDIV_T clkdiv);

/**
 * @brief	Set I2C mode for a pin
 * @param	pIOCON	: The base of IOCON peripheral on the chip
 * @param	pin		: Pin number
 * @param	mode	: 0:Standard/Fast I2C 1: GPIO 2: Fast Plus
 * @return	Nothing
 * @note	Valid for pins PIO0_10 and PIO0_11 only.
 */
void Chip_IOCON_PinSetI2CMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_I2CMODE_T mode);

/**
 * @}
 */

 
/** @defgroup SWM_8XX CHIP: LPC8xx Switch Matrix Driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief LPC8XX Switch Matrix register block structure
 */
typedef struct {
#if defined(CHIP_LPC82X)
	__IO uint32_t PINASSIGN[12];	/*!< Pin Assign register array */
	__I  uint32_t RESERVED0[100];
#else
	__IO uint32_t PINASSIGN[9];		/*!< Pin Assign register array */
	__I  uint32_t RESERVED0[103];
#endif
	__IO uint32_t PINENABLE0;		/*!< Pin Enable register */
} LPC_SWM_T;

#if defined(CHIP_LPC82X)
#define SWM_PINENABLE0_RESERVED  (~0x1ffffff)
#else
#define SWM_PINENABLE0_RESERVED  (~0x1ff)
#endif

/**
 * @brief LPC8XX Switch Matrix Movable pins
 */
#if defined(CHIP_LPC82X)
typedef enum CHIP_SWM_PIN_MOVABLE {
	SWM_U0_TXD_O,                /*!< PINASSIGN0 - UART0 TXD Output */
	SWM_U0_RXD_I,                /*!< PINASSIGN0 - UART0 RXD Input */
	SWM_U0_RTS_O,                /*!< PINASSIGN0 - UART0 RTS Output */
	SWM_U0_CTS_I,                /*!< PINASSIGN0 - UART0 CTS Input */

	SWM_U0_SCLK_IO = 0x10,       /*!< PINASSIGN1 - UART0 SCLK I/O */
	SWM_U1_TXD_O,                /*!< PINASSIGN1 - UART1 TXD Output */
	SWM_U1_RXD_I,                /*!< PINASSIGN1 - UART1 RXD Input */
	SWM_U1_RTS_O,                /*!< PINASSIGN1 - UART1 RTS Output */

	SWM_U1_CTS_I = 0x20,         /*!< PINASSIGN2 - UART1 CTS Input */
	SWM_U1_SCLK_IO,              /*!< PINASSIGN2 - UART1 SCLK I/O */
	SWM_U2_TXD_O,                /*!< PINASSIGN2 - UART2 TXD Output */
	SWM_U2_RXD_I,                /*!< PINASSIGN2 - UART2 RXD Input */

	SWM_U2_RTS_O = 0x30,         /*!< PINASSIGN3 - UART2 RTS Output */
	SWM_U2_CTS_I,                /*!< PINASSIGN3 - UART2 CTS Input */
	SWM_U2_SCLK_IO,              /*!< PINASSIGN3 - UART2 SCLK I/O */
	SWM_SPI0_SCK_IO,             /*!< PINASSIGN3 - SPI0 SCK I/O */

	SWM_SPI0_MOSI_IO = 0x40,     /*!< PINASSIGN4 - SPI0 MOSI I/O */
	SWM_SPI0_MISO_IO,            /*!< PINASSIGN4 - SPI0 MISO I/O */
	SWM_SPI0_SSEL0_IO,           /*!< PINASSIGN4 - SPI0 SSEL0 I/O */
	SWM_SPI0_SSEL1_IO,           /*!< PINASSIGN4 - SPI0 SSEL1 I/O */

	SWM_SPI0_SSEL2_IO = 0x50,    /*!< PINASSIGN5 - SPI0 SSEL2 I/O */
	SWM_SPI0_SSEL3_IO,           /*!< PINASSIGN5 - SPI0 SSEL3 I/O */
	SWM_SPI1_SCK_IO,             /*!< PINASSIGN5 - SPI1 SCK I/O */
	SWM_SPI1_MOSI_IO,            /*!< PINASSIGN5 - SPI1 MOSI I/O */

	SWM_SPI1_MISO_IO = 0x60,     /*!< PINASSIGN6 - SPI1 MISO I/O */
	SWM_SPI1_SSEL0_IO,           /*!< PINASSIGN6 - SPI1 SSEL0 I/O */
	SWM_SPI1_SSEL1_IO,           /*!< PINASSIGN6 - SPI1 SSEL1 I/O */
	SWM_SCT_IN0_I,               /*!< PINASSIGN6 - SCT INPUT_0 Input */

	SWM_SCT_IN1_I = 0x70,        /*!< PINASSIGN7 - SCT INPUT_1 Input */
	SWM_SCT_IN2_I,               /*!< PINASSIGN7 - SCT INPUT_2 Input */
	SWM_SCT_IN3_I,               /*!< PINASSIGN7 - SCT INPUT_3 Input */
	SWM_SCT_OUT0_O,              /*!< PINASSIGN7 - SCT OUTPUT_0 Output */

	SWM_SCT_OUT1_O = 0x80,       /*!< PINASSIGN8 - SCT OUTPUT_1 Output */
	SWM_SCT_OUT2_O,              /*!< PINASSIGN8 - SCT OUTPUT_2 Output */
	SWM_SCT_OUT3_O,              /*!< PINASSIGN8 - SCT OUTPUT_3 Output */
	SWM_SCT_OUT4_O,              /*!< PINASSIGN8 - SCT OUTPUT_4 Output */

	SWM_SCT_OUT5_O = 0x90,       /*!< PINASSIGN9 - SCT OUTPUT_5 Output */
	SWM_I2C1_SDA_IO,             /*!< PINASSIGN9 - I2C1 SDA I/O */
	SWM_I2C1_SCL_IO,             /*!< PINASSIGN9 - I2C1 SCL I/O */
	SWM_I2C2_SDA_IO,             /*!< PINASSIGN9 - I2C2 SDA I/O */

	SWM_I2C2_SCL_IO = 0xA0,      /*!< PINASSIGN10 - I2C2 SCL I/O */
	SWM_I2C3_SDA_IO,             /*!< PINASSIGN10 - I2C3 SDA I/O */
	SWM_I2C3_SCL_IO,             /*!< PINASSIGN10 - I2C3 SCL I/O */
	SWM_ADC_PINTRIG0_I,          /*!< PINASSIGN10 - ADC PIN TRIGGER-0 Input */

	SWM_ADC_PINTRIG1_I = 0xB0,   /*!< PINASSIGN11 - ADC PIN TRIGGER-1 Input */
	SWM_ACMP_O_O,                /*!< PINASSIGN11 - ACMP OUT Output */
	SWM_CLKOUT_O,                /*!< PINASSIGN11 - CLKOUT Output */
	SWM_GPIO_INT_BMAT_O,         /*!< PINASSIGN11 - GPIO INT BMAT Output */

} CHIP_SWM_PIN_MOVABLE_T;
#else
typedef enum CHIP_SWM_PIN_MOVABLE  {
	SWM_U0_TXD_O        = 0x00,	/*!< PINASSIGN0 - UART0 TXD Output */
	SWM_U0_RXD_I        = 0x01,	/*!< PINASSIGN0 - UART0 RXD Input */
	SWM_U0_RTS_O        = 0x02,	/*!< PINASSIGN0 - UART0 RTS Output */
	SWM_U0_CTS_I        = 0x03,	/*!< PINASSIGN0 - UART0 CTS Input */
	SWM_U0_SCLK_IO      = 0x10,	/*!< PINASSIGN1 - UART0 SCLK I/O */
	SWM_U1_TXD_O        = 0x11,	/*!< PINASSIGN1 - UART1 TXD Output */
	SWM_U1_RXD_I        = 0x12,	/*!< PINASSIGN1 - UART1 RXD Input */
	SWM_U1_RTS_O        = 0x13,	/*!< PINASSIGN1 - UART1 RTS Output */
	SWM_U1_CTS_I        = 0x20,	/*!< PINASSIGN2 - UART1 CTS Input */
	SWM_U1_SCLK_IO      = 0x21,	/*!< PINASSIGN2 - UART1 SCLK I/O */
	SWM_U2_TXD_O        = 0x22,	/*!< PINASSIGN2 - UART2 TXD Output */
	SWM_U2_RXD_I        = 0x23,	/*!< PINASSIGN2 - UART2 RXD Input */
	SWM_U2_RTS_O        = 0x30,	/*!< PINASSIGN3 - UART2 RTS Output */
	SWM_U2_CTS_I        = 0x31,	/*!< PINASSIGN3 - UART2 CTS Input */
	SWM_U2_SCLK_IO      = 0x32,	/*!< PINASSIGN3 - UART2 SCLK I/O */
	SWM_SPI0_SCK_IO     = 0x33,	/*!< PINASSIGN3 - SPI0 SCK I/O */
	SWM_SPI0_MOSI_IO    = 0x40,	/*!< PINASSIGN4 - SPI0 MOSI I/O */
	SWM_SPI0_MISO_IO    = 0x41,	/*!< PINASSIGN4 - SPI0 MISO I/O */
	SWM_SPI0_SSEL_IO    = 0x42,	/*!< PINASSIGN4 - SPI0 SSEL I/O */
	SWM_SPI1_SCK_IO     = 0x43,	/*!< PINASSIGN4 - SPI1 SCK I/O */
	SWM_SPI1_MOSI_IO    = 0x50,	/*!< PINASSIGN5 - SPI1 MOSI I/O */
	SWM_SPI1_MISO_IO    = 0x51,	/*!< PINASSIGN5 - SPI1 MISO I/O */
	SWM_SPI1_SSEL_IO    = 0x52,	/*!< PINASSIGN5 - SPI1 SSEL I/O */
	SWM_CTIN_0_I        = 0x53,	/*!< PINASSIGN5 - CTIN0 Input */
	SWM_CTIN_1_I        = 0x60,	/*!< PINASSIGN6 - CTIN1 Input */
	SWM_CTIN_2_I        = 0x61,	/*!< PINASSIGN6 - CTIN2 Input */
	SWM_CTIN_3_I        = 0x62,	/*!< PINASSIGN6 - CTIN3 Input */
	SWM_CTOUT_0_O       = 0x63,	/*!< PINASSIGN6 - CTOUT0 Output */
	SWM_CTOUT_1_O       = 0x70,	/*!< PINASSIGN7 - CTOUT1 Output */
	SWM_CTOUT_2_O       = 0x71,	/*!< PINASSIGN7 - CTOUT2 Output */
	SWM_CTOUT_3_O       = 0x72,	/*!< PINASSIGN7 - CTOUT3 Output */
	SWM_I2C_SDA_IO      = 0x73,	/*!< PINASSIGN7 - I2C SDA I/O */
	SWM_I2C_SCL_IO      = 0x80,	/*!< PINASSIGN8 - I2C SCL I/O */
	SWM_ACMP_O_O        = 0x81,	/*!< PINASSIGN8 - I2C ACMP Output */
	SWM_CLKOUT_O        = 0x82,	/*!< PINASSIGN8 - I2C CLKOUT Output */
	SWM_GPIO_INT_BMAT_O = 0x83,	/*!< PINASSIGN8 - I2C GPIO INT BMAT Output */
} CHIP_SWM_PIN_MOVABLE_T;
#endif

/**
 * @brief LPC8XX Switch Matrix Fixed pins
 */
#if defined(CHIP_LPC82X)
typedef enum CHIP_SWM_PIN_FIXED    {
	SWM_FIXED_ACMP_I1 = 0,	/*!< ACMP I1 */
	SWM_FIXED_ACMP_I2 = 1,	/*!< ACMP I2 */
	SWM_FIXED_ACMP_I3 = 2,	/*!< ACMP I3 */
	SWM_FIXED_ACMP_I4 = 3,	/*!< ACMP I4 */
	SWM_FIXED_SWCLK   = 4,	/*!< SWCLK */
	SWM_FIXED_SWDIO   = 5,	/*!< SWDIO */
	SWM_FIXED_XTALIN  = 6,	/*!< XTALIN */
	SWM_FIXED_XTALOUT = 7,	/*!< XTALOUT */
	SWM_FIXED_RST     = 8,	/*!< Reset */
	SWM_FIXED_CLKIN   = 9,	/*!< Clock Input */
	SWM_FIXED_VDDCMP  = 10,	/*!< VDD */
	SWM_FIXED_I2C0_SDA  = 11,	/*!< I2C0 SDA */
	SWM_FIXED_I2C0_SCL  = 12,	/*!< I2C0 SCL */
	SWM_FIXED_ADC0    = 13,	/*!< ADC0 */
	SWM_FIXED_ADC1    = 14,	/*!< ADC1 */
	SWM_FIXED_ADC2    = 15,	/*!< ADC2 */
	SWM_FIXED_ADC3    = 16,	/*!< ADC3 */
	SWM_FIXED_ADC4    = 17,	/*!< ADC4 */
	SWM_FIXED_ADC5    = 18,	/*!< ADC5 */
	SWM_FIXED_ADC6    = 19,	/*!< ADC6 */
	SWM_FIXED_ADC7    = 20,	/*!< ADC7 */
	SWM_FIXED_ADC8    = 21,	/*!< ADC8 */
	SWM_FIXED_ADC9    = 22,	/*!< ADC9 */
	SWM_FIXED_ADC10   = 23,	/*!< ADC10 */
	SWM_FIXED_ADC11   = 24,	/*!< ADC11 */
} CHIP_SWM_PIN_FIXED_T;
#else
typedef enum CHIP_SWM_PIN_FIXED    {
	SWM_FIXED_ACMP_I1 = 0,	/*!< ACMP I1 */
	SWM_FIXED_ACMP_I2 = 1,	/*!< ACMP I2 */
	SWM_FIXED_SWCLK   = 2,	/*!< SWCLK */
	SWM_FIXED_SWDIO   = 3,	/*!< SWDIO */
	SWM_FIXED_XTALIN  = 4,	/*!< XTALIN */
	SWM_FIXED_XTALOUT = 5,	/*!< XTALOUT */
	SWM_FIXED_RST     = 6,	/*!< Reset */
	SWM_FIXED_CLKIN   = 7,	/*!< Clock Input */
	SWM_FIXED_VDDCMP  = 8	/*!< VDD */
} CHIP_SWM_PIN_FIXED_T;
#endif

/**
 * @brief	Initialise the SWM module
 * @return	Nothing
 * @note	This function only enables the SWM clock.
 */
STATIC INLINE void Chip_SWM_Init(void)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
}

/**
 * @brief	Deinitialise the SWM module
 * @return	Nothing
 * @note	This function only disables the SWM clock.
 */
STATIC INLINE void Chip_SWM_Deinit(void)
{
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
}

/**
 * @brief	Assign movable pin function to physical pin in Switch Matrix
 * @param	movable	: Movable pin function
 * @param	assign	: Physical pin to be assigned
 * @return	Nothing
 */
void Chip_SWM_MovablePinAssign(CHIP_SWM_PIN_MOVABLE_T movable, uint8_t assign);

/**
 * @brief	Enables or Disable Fixed Function Pin in the Switch Matrix
 * @param	pin		: Pin to be enabled or disabled
 * @param	enable	: True to enable the pin, False to disable the pin
 * @return	Nothing
 */
void Chip_SWM_FixedPinEnable(CHIP_SWM_PIN_FIXED_T pin, bool enable);

/**
 * @brief	Enables a Fixed Function Pin in the Switch Matrix
 * @param	pin		: Pin to be enabled
 * @return	Nothing
 */
STATIC INLINE void Chip_SWM_EnableFixedPin(CHIP_SWM_PIN_FIXED_T pin)
{
	LPC_SWM->PINENABLE0 &= ~((1 << (uint32_t) pin) | SWM_PINENABLE0_RESERVED);
}

/**
 * @brief	Disables a Fixed Function Pin in the Switch Matrix
 * @param	pin		: Pin to be disabled
 * @return	Nothing
 */
STATIC INLINE void Chip_SWM_DisableFixedPin(CHIP_SWM_PIN_FIXED_T pin)
{
	LPC_SWM->PINENABLE0 = (1 << (uint32_t) pin) | (LPC_SWM->PINENABLE0 & ~SWM_PINENABLE0_RESERVED);
}

/**
 * @brief	Tests whether a fixed pin is enabled or disabled in the Switch Matrix
 * @param	pin		: The pin to test whether it is enabled or disabled
 * @return	True if the pin is enabled, False if disabled
 */
STATIC INLINE bool Chip_SWM_IsEnabled(CHIP_SWM_PIN_FIXED_T pin)
{
	return (bool) ((LPC_SWM->PINENABLE0 & (1 << (uint32_t) pin)) == 0);
}

/**
 * @}
 */

 
#ifdef __cplusplus
}
#endif

#endif /* __IOCON_8XX_H_ */

