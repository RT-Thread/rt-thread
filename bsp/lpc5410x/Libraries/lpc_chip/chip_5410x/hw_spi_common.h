/*
 * @brief SPI ROM API declarations and functions
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

#ifndef __HW_SPI_COMMON_H_
#define __HW_SPI_COMMON_H_

/**
 * @brief SPI register block structure
 */
typedef struct {					/*!< SPI Structure */
	volatile uint32_t  CFG;				/*!< SPI Configuration register */
	volatile uint32_t  DLY;				/*!< SPI Delay register */
	volatile uint32_t  STAT;			/*!< SPI Status register */
	volatile uint32_t  INTENSET;		/*!< SPI Interrupt Enable Set register */
	volatile uint32_t  INTENCLR;		/*!< SPI Interrupt Enable Clear register */
	volatile uint32_t  RXDAT;			/*!< SPI Receive Data register */
	volatile uint32_t  TXDATCTL;		/*!< SPI Transmit Data with Control register */
	volatile uint32_t  TXDAT;			/*!< SPI Transmit Data register */
	volatile uint32_t  TXCTRL;			/*!< SPI Transmit Control register */
	volatile uint32_t  DIV;				/*!< SPI clock Divider register */
	volatile uint32_t  INTSTAT;			/*!< SPI Interrupt Status register */
} LPC_SPI_T;

/**
 * Macro defines for SPI Configuration register
 */
#define SPI_CFG_BITMASK         (0xFBD)						/** SPI register bit mask */
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
#define SPI_TXDATCTL_BITMASK        (0xF7FFFFF)				/** SPI TXDATCTL Register BitMask */
#define SPI_TXDATCTL_DATA(n)        ((n) & 0xFFFF)			/** SPI Transmit Data */
#define SPI_TXDATCTL_CTRLMASK       (0xF7F0000)				/** SPI TXDATCTL Register BitMask for control bits only */
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
typedef enum {
	ROM_SPI_CLOCK_CPHA0_CPOL0 = 0,						/**< CPHA = 0, CPOL = 0 */
	ROM_SPI_CLOCK_MODE0 = ROM_SPI_CLOCK_CPHA0_CPOL0,	/**< Alias for CPHA = 0, CPOL = 0 */
	ROM_SPI_CLOCK_CPHA1_CPOL0 = 1,						/**< CPHA = 0, CPOL = 1 */
	ROM_SPI_CLOCK_MODE1 = ROM_SPI_CLOCK_CPHA1_CPOL0,	/**< Alias for CPHA = 0, CPOL = 1 */
	ROM_SPI_CLOCK_CPHA0_CPOL1 = 2,						/**< CPHA = 1, CPOL = 0 */
	ROM_SPI_CLOCK_MODE2 = ROM_SPI_CLOCK_CPHA0_CPOL1,	/**< Alias for CPHA = 1, CPOL = 0 */
	ROM_SPI_CLOCK_CPHA1_CPOL1 = 3,						/**< CPHA = 1, CPOL = 1 */
	ROM_SPI_CLOCK_MODE3 = ROM_SPI_CLOCK_CPHA1_CPOL1,	/**< Alias for CPHA = 1, CPOL = 1 */
} ROM_SPI_CLOCK_MODE_T;

#endif /* __HW_SPI_COMMON_H_ */
