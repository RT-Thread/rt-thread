/*
 * @brief LPC8XX SPI common functions and definitions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef __SPI_8XX_H__
#define __SPI_8XX_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SPI_COMMON_8XX CHIP: LPC8XX SPI common functions and definitions
 * @ingroup CHIP_8XX_Drivers
 * @{
 */
/**
 * @brief SPI register block structure
 */
typedef struct {					/*!< SPI Structure */
	__IO uint32_t  CFG;				/*!< SPI Configuration register */
	__IO uint32_t  DLY;				/*!< SPI Delay register */
	__IO uint32_t  STAT;			/*!< SPI Status register */
	__IO uint32_t  INTENSET;		/*!< SPI Interrupt Enable Set register */
	__O  uint32_t  INTENCLR;		/*!< SPI Interrupt Enable Clear register */
	__I  uint32_t  RXDAT;			/*!< SPI Receive Data register */
	__IO uint32_t  TXDATCTL;		/*!< SPI Transmit Data with Control register */
	__IO uint32_t  TXDAT;			/*!< SPI Transmit Data register */
	__IO uint32_t  TXCTRL;			/*!< SPI Transmit Control register */
	__IO uint32_t  DIV;				/*!< SPI clock Divider register */
	__I  uint32_t  INTSTAT;			/*!< SPI Interrupt Status register */
} LPC_SPI_T;

/* Reserved bits masks for registers */
#define SPI_CFG_RESERVED            ((1<<1)|(1<<6)|0xfffffe00)
#define SPI_DLY_RESERVED            0xffff0000
#define SPI_STAT_RESERVED           (~0x1ff)
#define SPI_INTENSET_RESERVED       (~0x3f)
#define SPI_INTENCLR_RESERVED       (~0x3f)
#define SPI_RXDAT_RESERVED          ((7<<17)|(0x7ffu<<21))
#define SPI_TXDATCTL_RESERVED       ((7<<17)|(1<<23)|(0xfu<<28))
#define SPI_TXDAT_RESERVED          0xffff0000
#define SPI_TXCTRL_RESERVED         (0xffff|(7<<17)|(1<<23)|(0xfu<<28))
#define SPI_DIV_RESERVED            0xffff0000
#define SPI_INTSTAT_RESERVED        (~0x3f)

/**
 * Macro defines for SPI Configuration register
 */
#define SPI_CFG_BITMASK         (0x1BD)						/** SPI register bit mask */
#define SPI_CFG_SPI_EN          (1 << 0)					/** SPI Slave Mode Select */
#define SPI_CFG_SLAVE_EN        (0 << 0)					/** SPI Master Mode Select */
#define SPI_CFG_MASTER_EN       (1 << 2)					/** SPI MSB First mode enable */
#define SPI_CFG_MSB_FIRST_EN    (0 << 3)					/** SPI LSB First mode enable */
#define SPI_CFG_LSB_FIRST_EN    (1 << 3)					/** SPI Clock Phase Select */
#define SPI_CFG_CPHA_FIRST      (0 << 4)					/** Capture data on the first edge, Change data on the following edge */
#define SPI_CFG_CPHA_SECOND     (1 << 4)					/** SPI Clock Polarity Select */
#define SPI_CFG_CPOL_LO         (0 << 5)					/** The rest state of the clock (between frames) is low. */
#define SPI_CFG_CPOL_HI         (1 << 5)					/** The rest state of the clock (between frames) is high. */
#define SPI_CFG_LBM_EN          (1 << 7)					/** SPI control 1 loopback mode enable */
#define SPI_CFG_SPOL_LO         (0 << 8)					/** SPI SSEL0 Polarity Select */
#define SPI_CFG_SPOL_HI         (1 << 8)					/** SSEL0 is active High */
#define SPI_CFG_SPOLNUM_HI(n)   (1 << ((n) + 8))			/** SSELN is active High, selects 0 - 3 */

/**
 * Macro defines for SPI Delay register
 */
#define  SPI_DLY_BITMASK            (0xFFFF)				/** SPI DLY Register Mask */
#define  SPI_DLY_PRE_DELAY(n)       (((n) & 0x0F) << 0)		/** Time in SPI clocks between SSEL assertion and the beginning of a data frame */
#define  SPI_DLY_POST_DELAY(n)      (((n) & 0x0F) << 4)		/** Time in SPI clocks between the end of a data frame and SSEL deassertion. */
#define  SPI_DLY_FRAME_DELAY(n)     (((n) & 0x0F) << 8)		/** Minimum time in SPI clocks between adjacent data frames. */
#define  SPI_DLY_TRANSFER_DELAY(n)  (((n) & 0x0F) << 12)	/** Minimum time in SPI clocks that the SSEL is deasserted between transfers. */

/**
 * Macro defines for SPI Status register
 */
#define SPI_STAT_BITMASK            (0x1FF)					/** SPI STAT Register BitMask */
#define SPI_STAT_RXRDY              (1 << 0)				/** Receiver Ready Flag */
#define SPI_STAT_TXRDY              (1 << 1)				/** Transmitter Ready Flag */
#define SPI_STAT_RXOV               (1 << 2)				/** Receiver Overrun interrupt flag */
#define SPI_STAT_TXUR               (1 << 3)				/** Transmitter Underrun interrupt flag (In Slave Mode only) */
#define SPI_STAT_SSA                (1 << 4)				/** Slave Select Assert */
#define SPI_STAT_SSD                (1 << 5)				/** Slave Select Deassert */
#define SPI_STAT_STALLED            (1 << 6)				/** Stalled status flag */
#define SPI_STAT_EOT                (1 << 7)				/** End Transfer flag */
#define SPI_STAT_MSTIDLE            (1 << 8)				/** Idle status flag */

/**
 * Macro defines for SPI Interrupt Enable read and Set register
 */
#define SPI_INTENSET_BITMASK        (0x3F)					/** SPI INTENSET Register BitMask */
#define SPI_INTENSET_RXDYEN         (1 << 0)				/** Enable Interrupt when receiver data is available */
#define SPI_INTENSET_TXDYEN         (1 << 1)				/** Enable Interrupt when the transmitter holding register is available. */
#define SPI_INTENSET_RXOVEN         (1 << 2)				/**  Enable Interrupt when a receiver overrun occurs */
#define SPI_INTENSET_TXUREN         (1 << 3)				/**  Enable Interrupt when a transmitter underrun occurs (In Slave Mode Only)*/
#define SPI_INTENSET_SSAEN          (1 << 4)				/**  Enable Interrupt when the Slave Select is asserted.*/
#define SPI_INTENSET_SSDEN          (1 << 5)				/**  Enable Interrupt when the Slave Select is deasserted..*/

/**
 * Macro defines for SPI Interrupt Enable Clear register
 */
#define SPI_INTENCLR_BITMASK        (0x3F)					/** SPI INTENCLR Register BitMask */
#define SPI_INTENCLR_RXDYEN         (1 << 0)				/** Disable Interrupt when receiver data is available */
#define SPI_INTENCLR_TXDYEN         (1 << 1)				/** Disable Interrupt when the transmitter holding register is available. */
#define SPI_INTENCLR_RXOVEN         (1 << 2)				/** Disable Interrupt when a receiver overrun occurs */
#define SPI_INTENCLR_TXUREN         (1 << 3)				/** Disable Interrupt when a transmitter underrun occurs (In Slave Mode Only) */
#define SPI_INTENCLR_SSAEN          (1 << 4)				/** Disable Interrupt when the Slave Select is asserted. */
#define SPI_INTENCLR_SSDEN          (1 << 5)				/** Disable Interrupt when the Slave Select is deasserted.. */

/**
 * Macro defines for SPI Receiver Data register
 */
#define SPI_RXDAT_BITMASK           (0x1FFFFF)				/** SPI RXDAT Register BitMask */
#define SPI_RXDAT_DATA(n)           ((n) & 0xFFFF)			/** Receiver Data  */
#define SPI_RXDAT_RXSSELN_ACTIVE    (0 << 16)				/** The state of SSEL pin is active */
#define SPI_RXDAT_RXSSELN_INACTIVE  ((1 << 16)				/** The state of SSEL pin is inactive */
#define SPI_RXDAT_RXSSELNUM_INACTIVE(n) (1 << ((n) + 16))	/** The state of SSELN pin is inactive */
#define SPI_RXDAT_SOT               (1 << 20)				/** Start of Transfer flag  */

/**
 * Macro defines for SPI Transmitter Data and Control register
 */
#define SPI_TXDATCTL_BITMASK        (0xF71FFFF)				/** SPI TXDATCTL Register BitMask */
#define SPI_TXDATCTL_DATA(n)        ((n) & 0xFFFF)			/** SPI Transmit Data */
#define SPI_TXDATCTL_CTRLMASK       (0xF710000)				/** SPI TXDATCTL Register BitMask for control bits only */
#define SPI_TXDATCTL_ASSERT_SSEL    (0 << 16)				/** Assert SSEL0 pin */
#define SPI_TXDATCTL_DEASSERT_SSEL  (1 << 16)				/** Deassert SSEL0 pin */
#define SPI_TXDATCTL_DEASSERTNUM_SSEL(n)    (1 << ((n) + 16))	/** Deassert SSELN pin */
#define SPI_TXDATCTL_DEASSERT_ALL   (0xF << 16)				/** Deassert all SSEL pins */
#define SPI_TXDATCTL_EOT            (1 << 20)				/** End of Transfer flag (TRANSFER_DELAY is applied after sending the current frame) */
#define SPI_TXDATCTL_EOF            (1 << 21)				/** End of Frame flag (FRAME_DELAY is applied after sending the current part) */
#define SPI_TXDATCTL_RXIGNORE       (1 << 22)				/** Receive Ignore Flag */
#define SPI_TXDATCTL_FLEN(n)        (((n) & 0x0F) << 24)	/** Frame length - 1 */

/**
 * Macro defines for SPI Transmitter Data Register
 */
#define SPI_TXDAT_DATA(n)           ((n) & 0xFFFF)			/** SPI Transmit Data */

/**
 * Macro defines for SPI Transmitter Control register
 */
#define SPI_TXCTL_BITMASK           (0xF7F0000)				/** SPI TXDATCTL Register BitMask */
#define SPI_TXCTL_ASSERT_SSEL       (0 << 16)				/** Assert SSEL0 pin */
#define SPI_TXCTL_DEASSERT_SSEL     (1 << 16)				/** Deassert SSEL0 pin */
#define SPI_TXCTL_DEASSERTNUM_SSEL(n)   (1 << ((n) + 16))	/** Deassert SSELN pin */
#define SPI_TXDATCTL_DEASSERT_ALL   (0xF << 16)				/** Deassert all SSEL pins */
#define SPI_TXCTL_EOT               (1 << 20)				/** End of Transfer flag (TRANSFER_DELAY is applied after sending the current frame) */
#define SPI_TXCTL_EOF               (1 << 21)				/** End of Frame flag (FRAME_DELAY is applied after sending the current part) */
#define SPI_TXCTL_RXIGNORE          (1 << 22)				/** Receive Ignore Flag */
#define SPI_TXCTL_FLEN(n)           ((((n) - 1) & 0x0F) << 24)	/** Frame length, 0 - 16 */
#define SPI_TXCTL_FLENMASK          (0xF << 24)				/** Frame length mask */

/**
 * Macro defines for SPI Divider register
 */
#define SPI_DIV_VAL(n)          ((n) & 0xFFFF)				/** Rate divider value mask (In Master Mode only)*/

/**
 * Macro defines for SPI Interrupt Status register
 */
#define SPI_INTSTAT_BITMASK         (0x3F)					/** SPI INTSTAT Register Bitmask */
#define SPI_INTSTAT_RXRDY           (1 << 0)				/** Receiver Ready Flag */
#define SPI_INTSTAT_TXRDY           (1 << 1)				/** Transmitter Ready Flag */
#define SPI_INTSTAT_RXOV            (1 << 2)				/** Receiver Overrun interrupt flag */
#define SPI_INTSTAT_TXUR            (1 << 3)				/** Transmitter Underrun interrupt flag (In Slave Mode only) */
#define SPI_INTSTAT_SSA             (1 << 4)				/** Slave Select Assert */
#define SPI_INTSTAT_SSD             (1 << 5)				/** Slave Select Deassert */

/** @brief SPI Clock Mode*/
#define SPI_CLOCK_CPHA0_CPOL0 (SPI_CFG_CPOL_LO | SPI_CFG_CPHA_FIRST)	/**< CPHA = 0, CPOL = 0 */
#define SPI_CLOCK_MODE0 SPI_CLOCK_CPHA0_CPOL0							/**< Alias for CPHA = 0, CPOL = 0 */
#define SPI_CLOCK_CPHA1_CPOL0 SPI_CFG_CPOL_LO | SPI_CFG_CPHA_SECOND		/**< CPHA = 0, CPOL = 1 */
#define SPI_CLOCK_MODE1 SPI_CLOCK_CPHA1_CPOL0							/**< Alias for CPHA = 0, CPOL = 1 */
#define SPI_CLOCK_CPHA0_CPOL1 SPI_CFG_CPOL_HI | SPI_CFG_CPHA_FIRST		/**< CPHA = 1, CPOL = 0 */
#define SPI_CLOCK_MODE2 SPI_CLOCK_CPHA0_CPOL1							/**< Alias for CPHA = 1, CPOL = 0 */
#define SPI_CLOCK_CPHA1_CPOL1 SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND		/**< CPHA = 1, CPOL = 1 */
#define SPI_CLOCK_MODE3 SPI_CLOCK_CPHA1_CPOL1							/**< Alias for CPHA = 1, CPOL = 1 */

/**
 * @brief	Set SPI CFG register values
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: CFG register bits to set, amd OR'ed value of SPI_CFG_* definitions
 * @return	Nothing
 * @note	This function safely sets only the selected bits in the SPI CFG register.
 * It can be used to enable multiple bits at once.
 */
STATIC INLINE void Chip_SPI_SetCFGRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	/* Update CFG register with only selected bits disabled */
	pSPI->CFG = bits | (pSPI->CFG & SPI_CFG_BITMASK);
}

/**
 * @brief	Clear SPI CFG register values
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: CFG register bits to clear, amd OR'ed value of SPI_CFG_* definitions
 * @return	Nothing
 * @note	This function safely clears only the selected bits in the SPI CFG register.
 * It can be used to disable multiple bits at once.
 */
STATIC INLINE void Chip_SPI_ClearCFGRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	/* Update CFG register with only selected bits disabled */
	pSPI->CFG = ~bits & (pSPI->CFG & SPI_CFG_BITMASK);
}

/**
 * @brief   Initialize the SPI
 * @param	pSPI	: The base SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_Init(LPC_SPI_T *pSPI)
{
	/* Enable SPI clock and reset IP */
	if (pSPI == LPC_SPI1) {
		Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SPI1);
		Chip_SYSCTL_PeriphReset(RESET_SPI1);
	} else {
		Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SPI0);
		Chip_SYSCTL_PeriphReset(RESET_SPI0);
	}
}

/**
 * @brief	Disable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_Disable(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_SPI_EN);
}

/**
 * @brief	Disable SPI operation
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	The SPI controller is disabled.
 */
STATIC INLINE void Chip_SPI_DeInit(LPC_SPI_T *pSPI)
{
	Chip_SPI_Disable(pSPI);
	if (pSPI == LPC_SPI1) {
		Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SPI1);
	} else {
		Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SPI0);
	}
}

/**
 * @brief	Enable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_Enable(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_SPI_EN);
}

/**
 * @brief	Enable SPI master mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note SPI slave mode will be disabled with this call. All SPI SSEL
 * lines will also be deasserted.
 */
STATIC INLINE void Chip_SPI_EnableMasterMode(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_MASTER_EN);

	/* Deassert all chip selects, only in master mode */
	pSPI->TXCTRL = SPI_TXDATCTL_DEASSERT_ALL;
}

/**
 * @brief	Enable SPI slave mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note SPI master mode will be disabled with this call.
 */
STATIC INLINE void Chip_SPI_EnableSlaveMode(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_MASTER_EN);
}

/**
 * @brief	Enable LSB First transfers
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_EnableLSBFirst(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_LSB_FIRST_EN);
}

/**
 * @brief	Enable MSB First transfers
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_EnableMSBFirst(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_LSB_FIRST_EN);
}


/**
 * @brief	Set SPI mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	mode	: SPI mode to set the SPI interface to
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SetSPIMode(LPC_SPI_T *pSPI, uint32_t mode)
{
	Chip_SPI_ClearCFGRegBits(pSPI, (SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND));
	Chip_SPI_SetCFGRegBits(pSPI, (uint32_t) mode);
}

/**
 * @brief	Set polarity on the SPI chip select high
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	csNum	: Chip select number, 0 - 3
 * @return	Nothing
 * @note	SPI chip select polarity is active high.
 */
STATIC INLINE void Chip_SPI_SetCSPolHigh(LPC_SPI_T *pSPI, uint8_t csNum)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_SPOLNUM_HI(csNum));
}

/**
 * @brief	Set polarity on the SPI chip select low
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	csNum	: Chip select number, 0 - 3
 * @return	Nothing
 * @note	SPI chip select polarity is active low.
 */
STATIC INLINE void Chip_SPI_SetCSPolLow(LPC_SPI_T *pSPI, uint8_t csNum)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_SPOLNUM_HI(csNum));
}

/**
 * @brief	Setup SPI configuration
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	config	: ORed spi configuration flags
 * @return	Nothing
 * @note	Possible values that can be ORed in @a config are
 * SPI_CLOCK_* (example: #SPI_CLOCK_CPHA0_CPOL0) along with
 * SPI_CFG_* (example: #SPI_CFG_SPI_EN).
 */
STATIC INLINE void Chip_SPI_ConfigureSPI(LPC_SPI_T *pSPI, uint32_t config)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_MASTER_EN | SPI_CFG_LSB_FIRST_EN |
			SPI_CFG_CPHA_SECOND | SPI_CFG_CPOL_HI);
	Chip_SPI_SetCFGRegBits(pSPI, config);

	/* Deassert all chip selects, only in master mode */
	pSPI->TXCTRL = SPI_TXDATCTL_DEASSERT_ALL;
}

/**
 * @brief	Get the current status of SPI controller
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	SPI Status (Or-ed bit value of SPI_STAT_*)
 * @note	Mask the return value with a value of type SPI_STAT_* to determine
 * if that status is active.
 */
STATIC INLINE uint32_t Chip_SPI_GetStatus(LPC_SPI_T *pSPI)
{
	return pSPI->STAT & ~SPI_STAT_RESERVED;
}

/**
 * @brief	Clear SPI status
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flag	: Clear Flag (Or-ed bit value of SPI_STAT_*)
 * @return	Nothing
 * @note	Only SPI_STAT_RXOV, SPI_STAT_TXUR, SPI_STAT_SSA, and
 * SPI_STAT_SSD statuses can be cleared.
 */
STATIC INLINE void Chip_SPI_ClearStatus(LPC_SPI_T *pSPI, uint32_t Flag)
{
	pSPI->STAT = Flag;
}

/**
 * @brief	Enable a SPI interrupt
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flag	: Or'ed value of SPI_INTENSET_* values to enable
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_EnableInts(LPC_SPI_T *pSPI, uint32_t Flag)
{
	pSPI->INTENSET = Flag;
}

/**
 * @brief	Disable a SPI interrupt
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flag	: Or'ed value of SPI_INTENCLR_* values to disable
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_DisableInts(LPC_SPI_T *pSPI, uint32_t Flag)
{
	pSPI->INTENCLR = Flag;
}

/**
 * @brief	Return enabled SPI interrupts
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	An Or'ed value of SPI_INTENSET_* values
 * @note	Mask the return value with a SPI_INTENSET_* value to determine
 * if the interrupt is enabled.
 */
STATIC INLINE uint32_t Chip_SPI_GetEnabledInts(LPC_SPI_T *pSPI)
{
	return pSPI->INTENSET & ~SPI_INTENSET_RESERVED;
}

/**
 * @brief	Return pending SPI interrupts
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	An Or'ed value of SPI_INTSTAT_* values
 * @note	Mask the return value with a SPI_INTSTAT_* value to determine
 * if the interrupt is pending.
 */
STATIC INLINE uint32_t Chip_SPI_GetPendingInts(LPC_SPI_T *pSPI)
{
	return pSPI->INTSTAT & ~SPI_INTSTAT_RESERVED;
}

/**
 * @brief	Flush FIFOs
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_FlushFifos(LPC_SPI_T *pSPI)
{
	Chip_SPI_Disable(pSPI);
	Chip_SPI_Enable(pSPI);
}

/**
 * @brief	Read raw data from receive FIFO with status bits
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Current value in receive data FIFO plus status bits
 */
STATIC INLINE uint32_t Chip_SPI_ReadRawRXFifo(LPC_SPI_T *pSPI)
{
	return pSPI->RXDAT & ~SPI_RXDAT_RESERVED;
}

/**
 * @brief	Read data from receive FIFO masking off status bits
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Current value in receive data FIFO
 * @note	The return value is masked with 0xFFFF to not exceed 16-bits. All
 * other status bits are thrown away. This register should only be read if it
 * has data in it. This function is useful for systems that don't need SPI
 * select (SSEL) monitoring.
 */
STATIC INLINE uint32_t Chip_SPI_ReadRXData(LPC_SPI_T *pSPI)
{
	return pSPI->RXDAT & 0xFFFF;
}

/**
 * @brief	Write data to transmit FIFO
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	data	: Data to write
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_WriteTXData(LPC_SPI_T *pSPI, uint16_t data)
{
	pSPI->TXDAT = (uint32_t) data;
}

/**
 * @brief	Set SPI TXCTRL register control options
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: TXCTRL register bits to set, amd OR'ed value of SPI_TXDATCTL_* definitions
 * @return	Nothing
 * @note	This function safely sets only the selected bits in the SPI TXCTRL register.
 * It can be used to enable multiple bits at once.
 */
STATIC INLINE void Chip_SPI_SetTXCTRLRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	pSPI->TXCTRL = bits | (pSPI->TXCTRL & SPI_TXDATCTL_CTRLMASK);
}

/**
 * @brief	Clear SPI TXCTRL register control options
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: TXCTRL register bits to clear, amd OR'ed value of SPI_TXDATCTL_* definitions
 * @return	Nothing
 * @note	This function safely clears only the selected bits in the SPI TXCTRL register.
 * It can be used to disable multiple bits at once.
 */
STATIC INLINE void Chip_SPI_ClearTXCTRLRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	pSPI->TXCTRL = ~bits & (pSPI->TXCTRL & SPI_TXDATCTL_CTRLMASK);
}

/**
 * @brief	Set TX control options (safe)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	ctrlBits	: Or'ed control bits to set
 * @return	Nothing
 * @note	Selectable control states include SPI_TXCTL_DEASSERTNUM_SSEL(0/1/2/3),
 * SPI_TXCTL_EOT, SPI_TXCTL_EOF, SPI_TXCTL_RXIGNORE, and SPI_TXCTL_FLEN(bits).
 */
STATIC INLINE void Chip_SPI_SetTXCtl(LPC_SPI_T *pSPI, uint32_t ctrlBits)
{
	Chip_SPI_SetTXCTRLRegBits(pSPI, ctrlBits);
}

/**
 * @brief	Clear TX control options (safe)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	ctrlBits	: Or'ed control bits to clear
 * @return	Nothing
 * @note	Selectable control states include SPI_TXCTL_DEASSERTNUM_SSEL(0/1/2/3),
 * SPI_TXCTL_EOT, SPI_TXCTL_EOF, SPI_TXCTL_RXIGNORE, and SPI_TXCTL_FLEN(bits).
 */
STATIC INLINE void Chip_SPI_ClearTXCtl(LPC_SPI_T *pSPI, uint32_t ctrlBits)
{
	Chip_SPI_ClearTXCTRLRegBits(pSPI, ctrlBits);
}

/**
 * @brief	Set TX data transfer size in bits
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	ctrlBits	: Number of bits to transmit and receive, must be 1 to 16
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SetXferSize(LPC_SPI_T *pSPI, uint32_t ctrlBits)
{
	Chip_SPI_ClearTXCTRLRegBits(pSPI, SPI_TXCTL_FLENMASK);
	Chip_SPI_SetTXCTRLRegBits(pSPI, SPI_TXCTL_FLEN(ctrlBits));
}

/**
 * @}
 */

 
/** @defgroup SPI_8XX CHIP: LPC8xx SPI driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/** @brief SPI Mode*/
typedef enum {
	SPI_MODE_MASTER = SPI_CFG_MASTER_EN,		/* Master Mode */
	SPI_MODE_SLAVE = SPI_CFG_SLAVE_EN,			/* Slave Mode */
} SPI_MODE_T;

/** @brief SPI Data Order Mode*/
typedef enum IP_SPI_DATA_ORDER {
	SPI_DATA_MSB_FIRST = SPI_CFG_MSB_FIRST_EN,			/* Standard Order */
	SPI_DATA_LSB_FIRST = SPI_CFG_LSB_FIRST_EN,			/* Reverse Order */
} SPI_DATA_ORDER_T;

/** @brief SPI SSEL Polarity definition*/
typedef enum IP_SPI_SSEL_POL {
	SPI_SSEL_ACTIVE_LO = SPI_CFG_SPOL_LO,			/* SSEL is active Low*/
	SPI_SSEL_ACTIVE_HI = SPI_CFG_SPOL_HI,			/* SSEL is active  High */
} SPI_SSEL_POL_T;

/**
 * @brief SPI Configure Struct
 */
typedef struct {
	SPI_MODE_T             Mode;			/* Mode Select */
	uint32_t               ClockMode;		/* CPHA CPOL Select */
	SPI_DATA_ORDER_T       DataOrder;		/* MSB/LSB First */
	SPI_SSEL_POL_T         SSELPol;		/* SSEL Polarity Select */
	uint16_t                ClkDiv;			/* SPI Clock Divider Value */
} SPI_CONFIG_T;

/**
 * @brief SPI Delay Configure Struct
 */
typedef struct {
	uint8_t     PreDelay;				/* Pre-delay value in SPI clock time */
	uint8_t     PostDelay;				/* Post-delay value in SPI clock time */
	uint8_t     FrameDelay;				/* Delay value between frames of a transfer in SPI clock time */
	uint8_t     TransferDelay;			/* Delay value between transfers in SPI clock time */
} SPI_DELAY_CONFIG_T;

/**
 * @brief SPI data setup structure
 */
typedef struct {
	uint16_t  *pTx;	/**< Pointer to data buffer*/
	uint32_t  TxCnt;/* Transmit Counter */
	uint16_t  *pRx;	/**< Pointer to data buffer*/
	uint32_t  RxCnt;/* Transmit Counter */
	uint32_t  Length;	/**< Data Length*/
	uint16_t  DataSize;	/** < The size of a frame (1-16)*/
} SPI_DATA_SETUP_T;

/**
 * @brief	Calculate the divider for SPI clock
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	bitRate	: Expected clock rate
 * @return	Divider value
 */
uint32_t Chip_SPI_CalClkRateDivider(LPC_SPI_T *pSPI, uint32_t bitRate);

/**
 * @brief	Config SPI Delay parameters
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	pConfig	: SPI Delay Configure Struct
 * @return	 Nothing
 * @note	The SPI controller is disabled
 */
void Chip_SPI_DelayConfig(LPC_SPI_T *pSPI, SPI_DELAY_CONFIG_T *pConfig);

/**
 * @brief   Enable/Disable SPI interrupt
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	IntMask		: Interrupt mask
 * @param	NewState		: ENABLE or DISABLE interrupt
 * @return	Nothing
 */
void Chip_SPI_Int_Cmd(LPC_SPI_T *pSPI, uint32_t IntMask, FunctionalState NewState);

/**
 * @brief	Enable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */

/**
 * @brief	Enable loopback mode
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin
 */
STATIC INLINE void Chip_SPI_EnableLoopBack(LPC_SPI_T *pSPI)
{
	pSPI->CFG = SPI_CFG_LBM_EN | (pSPI->CFG & ~SPI_CFG_RESERVED);
}

/**
 * @brief	Disable loopback mode
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin
 */
STATIC INLINE void Chip_SPI_DisableLoopBack(LPC_SPI_T *pSPI)
{
	pSPI->CFG &= (~SPI_CFG_LBM_EN) & SPI_CFG_BITMASK;
}

/**
 * @brief	Set control information including SSEL, EOT, EOF RXIGNORE and FLEN
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flen	: Data size (1-16)
 * @param	Flag	: Flag control (Or-ed values of SPI_TXCTL_*)
 * @note	The control information has no effect unless data is later written to TXDAT
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SetControlInfo(LPC_SPI_T *pSPI, uint8_t Flen, uint32_t Flag)
{
	pSPI->TXCTRL = Flag | SPI_TXDATCTL_FLEN(Flen - 1);
}

/**
 * @brief	 Send the first Frame of a transfer (Rx Ignore)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendFirstFrame_RxIgnore(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_FLEN(
		DataSize - 1) | SPI_TXDATCTL_DATA(Data);
}

/**
 * @brief	 Send the first Frame of a transfer
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendFirstFrame(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_FLEN(DataSize - 1) | SPI_TXDATCTL_DATA(
		Data);
}

/**
 * @brief	 Send the middle Frame of a transfer
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendMidFrame(LPC_SPI_T *pSPI, uint16_t Data)
{
	pSPI->TXDAT = SPI_TXDAT_DATA(Data);
}

/**
 * @brief	 Send the last Frame of a transfer (Rx Ignore)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendLastFrame_RxIgnore(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT | SPI_TXDATCTL_RXIGNORE |
					 SPI_TXDATCTL_FLEN(DataSize - 1) | SPI_TXDATCTL_DATA(Data);
}

/**
 * @brief	 Send the last Frame of a transfer
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendLastFrame(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
					 SPI_TXDATCTL_FLEN(DataSize - 1) | SPI_TXDATCTL_DATA(Data);
}

/**
 * @brief	 Read data received
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @return	Receive data
 */
STATIC INLINE uint16_t Chip_SPI_ReceiveFrame(LPC_SPI_T *pSPI)
{
	return SPI_RXDAT_DATA(pSPI->RXDAT);
}

/**
 * @brief   SPI Interrupt Read/Write
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	xf_setup		: Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	SUCCESS or ERROR
 */
Status Chip_SPI_Int_RWFrames(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief   SPI Polling Read/Write in blocking mode
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pXfSetup		: Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	Actual data length has been transferred
 * @note
 * This function can be used in both master and slave mode. It starts with writing phase and after that,
 * a reading phase is generated to read any data available in RX_FIFO. All needed information is prepared
 * through xf_setup param.
 */
uint32_t Chip_SPI_RWFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup);

/**
 * @brief   SPI Polling Write in blocking mode
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pXfSetup			:Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	Actual data length has been transferred
 * @note
 * This function can be used in both master and slave mode. First, a writing operation will send
 * the needed data. After that, a dummy reading operation is generated to clear data buffer
 */
uint32_t Chip_SPI_WriteFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup);

/**
 * @brief   SPI Polling Read in blocking mode
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pXfSetup			:Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	Actual data length has been read
 * @note
 * This function can be used in both master and slave mode. First, a writing operation will send
 * the needed data. After that, a dummy reading operation is generated to clear data buffer
 */
uint32_t Chip_SPI_ReadFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup);

/**
 * @}
 */
 
 
/** @defgroup SPI_MASTER_8XX CHIP: LPC8XX SPI master driver
 * @ingroup SPI_COMMON_8XX
 * @{
 */

/**
 * @brief	Get SPI master bit rate
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	The actual SPI clock bit rate
 */
uint32_t Chip_SPIM_GetClockRate(LPC_SPI_T *pSPI);

/**
 * @brief	Set SPI master bit rate
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	rate	: Desired clock bit rate for the SPI interface
 * @return	The actual SPI clock bit rate
 * @note	This function will set the SPI clock divider to get closest
 * to the desired rate as possible.
 */
uint32_t Chip_SPIM_SetClockRate(LPC_SPI_T *pSPI, uint32_t rate);

/**
 * @brief SPI Delay Configure Struct
 */
typedef struct {
	uint8_t PreDelay;					/** Pre-delay value in SPI clocks, 0 - 15 */
	uint8_t PostDelay;					/** Post-delay value in SPI clocks, 0 - 15 */
	uint8_t FrameDelay;					/** Delay value between frames of a transfer in SPI clocks, 0 - 15 */
	uint8_t TransferDelay;				/** Delay value between transfers in SPI clocks, 1 - 16 */
} SPIM_DELAY_CONFIG_T;

/**
 * @brief	Config SPI Delay parameters
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	pConfig	: SPI Delay Configure Struct
 * @return	Nothing
 */
void Chip_SPIM_DelayConfig(LPC_SPI_T *pSPI, SPIM_DELAY_CONFIG_T *pConfig);

/**
 * @brief	Forces an end of transfer for the current master transfer
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Use this function to perform an immediate end of trasnfer for the
 * current master operation. If the master is currently transferring data started
 * with the Chip_SPIM_Xfer function, this terminates the transfer after the
 * current byte completes and completes the transfer.
 */
STATIC INLINE void Chip_SPIM_ForceEndOfTransfer(LPC_SPI_T *pSPI)
{
	pSPI->STAT = SPI_STAT_EOT;
}

/**
 * @brief	Assert a SPI select
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	sselNum	: SPI select to assert, 0 - 3
 * @return	Nothing
 */
void Chip_SPIM_AssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum);

/**
 * @brief	Deassert a SPI select
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	sselNum	: SPI select to deassert, 0 - 3
 * @return	Nothing
 */
void Chip_SPIM_DeAssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum);

/**
 * @brief	Enable loopback mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin.
 */
STATIC INLINE void Chip_SPIM_EnableLoopBack(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_LBM_EN);
}

/**
 * @brief	Disable loopback mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPIM_DisableLoopBack(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_LBM_EN);
}

struct SPIM_XFER;

/** @brief SPI master select assert callback
 * This callback is called from the SPI master handler when the SPI master
 * selects the slave (asserts SSEL).
 */
typedef void (*SPIMasterXferCSAssert)(struct SPIM_XFER *pMasterXfer);

/** @brief SPI master send data callback
 * This callback is called from the SPI master handler when the SPI master
 * needs a data buffer to send.
 */
typedef void (*SPIMasterXferSend)(struct SPIM_XFER *pMasterXfer);

/** @brief SPI master receive data callback
 * This callback is called from the SPI master handler when the SPI master
 * needs a buffer to place data into.
 */
typedef void (*SPIMasterXferRecv)(struct SPIM_XFER *pMasterXfer);

/** @brief SPI master transfer select deassert data callback
 * This callback is called from the SPI master handler when the SPI master
 * deasserts the slave select.
 */
typedef void (*SPIMMasterXferCSDeAssert)(struct SPIM_XFER *pMasterXfer);

/** @brief SPI master transfer done data callback
 * This callback is called from the SPI master handler when the SPI master
 * has completed the transfer and becomes idle.
 */
typedef void (*SPIMMasterXferDone)(struct SPIM_XFER *pMasterXfer);

/** SPI slave callback functions */
typedef struct {
	SPIMasterXferCSAssert   masterXferCSAssert;		/** SPI transfer CS assert, called when a slave select is asserted */
	SPIMasterXferSend       masterXferSend;			/** SPI transfer data receive buffer callback, called when a send buffer is needed */
	SPIMasterXferRecv       masterXferRecv;			/** SPI transfer send buffer callback, called when send buffer is needed (and SPI_TXCTL_RXIGNORE option is not set) */
	SPIMMasterXferCSDeAssert mMasterXferCSDeAssert;	/** SPI transfer CS deassert, called when a slave select is deasserted */
	SPIMMasterXferDone      mMasterXferDone;		/** SPI transfer done callback, called when transfer is complete */
} SPIM_CALLBACKS_T;

/** Slave transfer data context */
typedef struct SPIM_XFER {
	const SPIM_CALLBACKS_T *pCB;	/** Pointer to SPI master data callback functions */
	union {							/** Pointer to receive buffer, set to NULL to toss receeive data */
		uint8_t *pRXData8;			/** Receive buffer used with data transfer size <= 8-bits, modified by driver */
		uint16_t *pRXData16;		/** Receive buffer used with data transfer size > 8-bits, modified by driver */
	};

	union {							/** Pointer to transmit buffer, set to NULL to transmit 0x0 */
		uint8_t *pTXData8;			/** Send buffer used with data transfer size <= 8-bits, modified by driver */
		uint16_t *pTXData16;		/** Send buffer used with data transfer size > 8-bits, modified by driver */
	};

	uint32_t options;				/** Master transfer options, an OR'ed value of SPI_TXCTL_EOT, SPI_TXCTL_EOF, SPI_TXCTL_RXIGNORE, and SPI_TXCTL_FLEN(bits) */
	uint16_t rxCount;				/** Size of the pRXData buffer in items (not bytes), modified by driver */
	uint16_t txCount;				/** Number of items (not bytes) to send in pTXData buffer, modified by driver */
	uint16_t dataRXferred;			/** Total items (not bytes) received, modified by driver */
	uint16_t dataTXferred;			/** Total items (not bytes) transmitted, modified by driver */
	uint8_t sselNum;				/** Slave number assigned to this transfer, 0 - 3, used by driver to select slave */
	bool    terminate;				/** Transfer will terminate when txCount goes to 0 and master goes idle, must be set before last byte is sent */
} SPIM_XFER_T;

/**
 * @brief	SPI master transfer state change handler
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIM_XFER_T structure see notes below
 * @return	Nothing
 * @note	See @ref SPIM_XFER_T for more information on this function. When using
 * this function, the SPI master interrupts should be enabled and setup in the SPI
 * interrupt handler to call this function when they fire. This function is meant
 * to be called from the interrupt handler.
 */
void Chip_SPIM_XferHandler(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer);

/**
 * @brief	Start non-blocking SPI master transfer
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIM_XFER_T structure see notes below
 * @return	Nothing
 * @note	This function starts a non-blocking SPI master transfer with the
 * parameters setup in the passed @ref SPIM_XFER_T structure. Once the transfer is
 * started, the interrupt handler must call Chip_SPIM_XferHandler to keep the
 * transfer going and fed with data. This function should only be called when
 * the master is idle.<br>
 *
 * This function must be called with the options and sselNum fields correctly
 * setup. Initial data buffers and the callback pointer must also be setup. No
 * sanity checks are performed on the passed data.<br>
 *
 * Example call:<br>
 * SPIM_XFER_T mxfer;
 * mxfer.pCB = &masterCallbacks;
 * mxfer.sselNum = 2; // Use chip select 2
 * mxfer.options = SPI_TXCTL_FLEN(8); // 8 data bits, supports 1 - 16 bits
 * mxfer.options |= SPI_TXCTL_EOT | SPI_TXCTL_EOF; // Apply frame and transfer delays to master transfer
 * mxfer.options |= SPI_TXCTL_RXIGNORE; // Ignore RX data, will toss receive data regardless of pRXData8 or pRXData16 buffer
 * mxfer.pTXData8 = SendBuffer;
 * mxfer.txCount = 16; // Number of bytes to send before SPIMasterXferSend callback is called
 * mxfer.pRXData8 = RecvBuffer; // Will not receive data if pRXData8/pRXData16 is NULL or SPI_TXCTL_RXIGNORE option is set
 * mxfer.rxCount = 16; // Number of bytes to receive before SPIMasterXferRecv callback is called
 * Chip_SPIM_Xfer(LPC_SPI0, &mxfer); // Start transfer
 *
 * Note that the transfer, once started, needs to be constantly fed by the callbacks.
 * The txCount and rxCount field only indicate the buffer size before the callbacks are called.
 * To terminate the transfer, the SPIMasterXferSend callback must set the terminate field.
 */
void Chip_SPIM_Xfer(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer);

/**
 * @brief	Perform blocking SPI master transfer
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIM_XFER_T structure see notes below
 * @return	Nothing
 * @note	This function starts a blocking SPI master transfer with the
 * parameters setup in the passed @ref SPIM_XFER_T structure. Once the transfer is
 * started, the callbacks in Chip_SPIM_XferHandler may be called to keep the
 * transfer going and fed with data. SPI interrupts must be disabled prior to
 * calling this function. It is not recommended to use this function.<br>
 */
void Chip_SPIM_XferBlocking(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer);

/**
 * @}
 */
 
 
/** @defgroup SPI_SLAVE_8XX CHIP: LPC8XX SPI slave driver
 * @ingroup SPI_COMMON_8XX
 * @{
 */

/**
 * Macro defines for SPI Status register
 */

/* Clear RXOV Flag */
#define SPI_STAT_CLR_RXOV       ((uint32_t) (1 << 2))
/* Clear TXUR Flag */
#define SPI_STAT_CLR_TXUR       ((uint32_t) (1 << 3))
/* Clear SSA Flag */
#define SPI_STAT_CLR_SSA        ((uint32_t) (1 << 4))
/* Clear SSD Flag */
#define SPI_STAT_CLR_SSD        ((uint32_t) (1 << 5))

struct SPIS_XFER;

/** @brief SPI slave select assertion callback
 * This callback is called from the SPI slave handler when an SPI slave select (SSEL)
 * is initially asserted. It is used to indicate the start of a slave transfer that
 * will happen on the bus.
 */
typedef void (*SPISlaveXferCSAssert)(struct SPIS_XFER *pSlaveXfer);

/** @brief SPI slave send data callback
 * This callback is called from the SPI slave handler when an SPI slave select (SSEL)
 * needs a data buffer to send.
 */
typedef void (*SPISlaveXferSend)(struct SPIS_XFER *pSlaveXfer);

/** @brief SPI slave receive data callback
 * This callback is called from the SPI slave handler when an SPI slave select (SSEL)
 * needs a buffer to place data.
 */
typedef void (*SPISlaveXferRecv)(struct SPIS_XFER *pSlaveXfer);

/** @brief SPI slave select de-assertion callback
 * This callback is called from the SPI slave handler when an SPI slave select (SSEL)
 * is de-asserted. It can be used to indicate the end of a transfer.
 */
typedef void (*SPISlaveXferCSDeAssert)(struct SPIS_XFER *pSlaveXfer);

/** SPI slave callback functions */
typedef struct {
	SPISlaveXferCSAssert    slaveXferCSAssert;		/** SPI transfer start callback, called on SPI CS assertion */
	SPISlaveXferSend        slaveXferSend;			/** SPI transfer data receive buffer callback, called when a receive buffer is needed */
	SPISlaveXferRecv        slaveXferRecv;			/** SPI transfer send buffer callback, called when data is needed */
	SPISlaveXferCSDeAssert  slaveXferCSDeAssert;	/** SPI transfer completion callback, called on SPI CS deassertion */
} SPIS_CALLBACKS_T;

/** Slave transfer data context */
typedef struct SPIS_XFER {
	const SPIS_CALLBACKS_T *pCB;	/** Pointer to SPI slave callback functions */
	union {							/** Pointer to receive buffer, set to NULL to toss receeive data */
		uint8_t *pRXData8;			/** Receive buffer used with data transfer size <= 8-bits, modified by driver */
		uint16_t *pRXData16;		/** Receive buffer used with data transfer size > 8-bits, modified by driver */
	};

	union {							/** Pointer to transmit buffer, set to NULL to transmit 0x0 */
		uint8_t *pTXData8;			/** Send buffer used with data transfer size <= 8-bits, modified by driver */
		uint16_t *pTXData16;		/** Send buffer used with data transfer size > 8-bits, modified by driver */
	};

	uint16_t rxCount;				/** Size of the pRXData buffer in items (not bytes), modified by driver */
	uint16_t txCount;				/** Number of items (not bytes) to send in pTXData buffer, modified by driver */
	uint16_t dataRXferred;			/** Total items (not bytes) received, modified by driver */
	uint16_t dataTXferred;			/** Total items (not bytes) transmitted, modified by driver */
	uint8_t sselNum;				/** Slave number assigned to this transfer, 0 - 3, modified by driver */
} SPIS_XFER_T;

/**
 * @brief	SPI slave transfer state change handler
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIS_XFER_T structure see notes below
 * @return	returns 0 on success, or SPI_STAT_RXOV and/or SPI_STAT_TXUR on an error
 * @note	See @ref SPIS_XFER_T for more information on this function. When using
 * this function, the SPI slave interrupts should be enabled and setup in the SPI
 * interrupt handler to call this function when they fire. This function is meant
 * to be called from the interrupt handler. The @ref SPIS_XFER_T data does not need
 * to be setup prior to the call and should be setup by the callbacks instead.<br>
 *
 * The callbacks are handled in the interrupt handler. If you are getting overflow
 * or underflow errors, you might need to lower the speed of the master clock or
 * extend the master's select assetion time.<br>
 */
uint32_t Chip_SPIS_XferHandler(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer);

/**
 * @brief	Pre-buffers slave transmit data
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIS_XFER_T structure see notes below
 * @return	Nothing
 * @note Pre-buffering allows the slave to prime the transmit FIFO with data prior to
 * the master starting a transfer. If data is not pre-buffered, the initial slave
 * transmit data will always be 0x0 with a slave transmit underflow status.
 * Pre-buffering is best used when only a single slave select is used by an
 * application.
 */
STATIC INLINE void Chip_SPIS_PreBuffSlave(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer)
{
	Chip_SPIS_XferHandler(pSPI, xfer);
}

/**
 * @brief	SPI slave transfer blocking function
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIS_XFER_T structure
 * @return	returns 0 on success, or SPI_STAT_RXOV and/or SPI_STAT_TXUR on an error
 * @note	This function performs a blocking transfer on the SPI slave interface.
 * It is not recommended to use this function. Once this function is called, it
 * will block forever until a slave transfer consisting of a slave SSEL assertion,
 * and de-assertion occur. The callbacks are still used for slave data buffer
 * management. SPI interrupts must be disabled prior to calling this function.
 */
uint32_t Chip_SPIS_XferBlocking(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer);

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __SPI_8XX_H__ */
