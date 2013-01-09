/*
 * @brief SSP Registers and control functions
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

#ifndef __SSP_001_H_
#define __SSP_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_SSP_001 IP: SSP register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief SSP register block structure
 */
typedef struct {			/*!< SSPn Structure         */
	__IO uint32_t CR0;		/*!< Control Register 0. Selects the serial clock rate, bus type, and data size. */
	__IO uint32_t CR1;		/*!< Control Register 1. Selects master/slave and other modes. */
	__IO uint32_t DR;		/*!< Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO. */
	__I  uint32_t SR;		/*!< Status Register        */
	__IO uint32_t CPSR;		/*!< Clock Prescale Register */
	__IO uint32_t IMSC;		/*!< Interrupt Mask Set and Clear Register */
	__I  uint32_t RIS;		/*!< Raw Interrupt Status Register */
	__I  uint32_t MIS;		/*!< Masked Interrupt Status Register */
	__O  uint32_t ICR;		/*!< SSPICR Interrupt Clear Register */
#if !defined(CHIP_LPC111X_CXX) && !defined(CHIP_LPC11UXX)	/* no DMA on LPC11xx or LPC11Uxx */
	__IO uint32_t DMACR;	/*!< SSPn DMA control register */
#endif
} IP_SSP_001_Type;

/**
 * Macro defines for CR0 register
 */

/** SSP data size select, must be 4 bits to 16 bits */
#define SSP_CR0_DSS(n)          ((uint32_t) ((n) & 0xF))
/** SSP control 0 Motorola SPI mode */
#define SSP_CR0_FRF_SPI         ((uint32_t) (0 << 4))
/** SSP control 0 TI synchronous serial mode */
#define SSP_CR0_FRF_TI          ((uint32_t) (1 << 4))
/** SSP control 0 National Micro-wire mode */
#define SSP_CR0_FRF_MICROWIRE   ((uint32_t) (2 << 4))
/** SPI clock polarity bit (used in SPI mode only), (1) = maintains the
   bus clock high between frames, (0) = low */
#define SSP_CR0_CPOL_LO     ((uint32_t) (0))
#define SSP_CR0_CPOL_HI     ((uint32_t) (1 << 6))
/** SPI clock out phase bit (used in SPI mode only), (1) = captures data
   on the second clock transition of the frame, (0) = first */
#define SSP_CR0_CPHA_FIRST  ((uint32_t) (0))
#define SSP_CR0_CPHA_SECOND ((uint32_t) (1 << 7))
/** SSP serial clock rate value load macro, divider rate is
   PERIPH_CLK / (cpsr * (SCR + 1)) */
#define SSP_CR0_SCR(n)      ((uint32_t) ((n & 0xFF) << 8))
/** SSP CR0 bit mask */
#define SSP_CR0_BITMASK     ((uint32_t) (0xFFFF))
/** SSP CR0 bit mask */
#define SSP_CR0_BITMASK     ((uint32_t) (0xFFFF))
/** SSP serial clock rate value load macro, divider rate is
   PERIPH_CLK / (cpsr * (SCR + 1)) */
#define SSP_CR0_SCR(n)      ((uint32_t) ((n & 0xFF) << 8))

/**
 * Macro defines for CR1 register
 */

/** SSP control 1 loopback mode enable bit */
#define SSP_CR1_LBM_EN      ((uint32_t) (1 << 0))
/** SSP control 1 enable bit */
#define SSP_CR1_SSP_EN      ((uint32_t) (1 << 1))
/** SSP control 1 slave enable */
#define SSP_CR1_SLAVE_EN    ((uint32_t) (1 << 2))
#define SSP_CR1_MASTER_EN   ((uint32_t) (0))
/** SSP control 1 slave out disable bit, disables transmit line in slave
   mode */
#define SSP_CR1_SO_DISABLE  ((uint32_t) (1 << 3))
/** SSP CR1 bit mask */
#define SSP_CR1_BITMASK     ((uint32_t) (0x0F))

/** SSP CPSR bit mask */
#define SSP_CPSR_BITMASK    ((uint32_t) (0xFF))
/**
 * Macro defines for DR register
 */

/** SSP data bit mask */
#define SSP_DR_BITMASK(n)   ((n) & 0xFFFF)

/**
 * Macro defines for SR register
 */

/** SSP SR bit mask */
#define SSP_SR_BITMASK  ((uint32_t) (0x1F))

/** ICR bit mask */
#define SSP_ICR_BITMASK ((uint32_t) (0x03))

/**
 * @brief SSP Type of Status
 */
typedef enum {
	SSP_STAT_TFE = ((uint32_t)(1 << 0)),/**< TX FIFO Empty */
	SSP_STAT_TNF = ((uint32_t)(1 << 1)),/**< TX FIFO not full */
	SSP_STAT_RNE = ((uint32_t)(1 << 2)),/**< RX FIFO not empty */
	SSP_STAT_RFF = ((uint32_t)(1 << 3)),/**< RX FIFO full */
	SSP_STAT_BSY = ((uint32_t)(1 << 4)),/**< SSP Busy */
} SSP_Status_Type;

/**
 * @brief SSP Type of Interrupt Mask
 */
typedef enum {
	SSP_RORIM = ((uint32_t)(1 << 0)),	/**< Overun */
	SSP_RTIM = ((uint32_t)(1 << 1)),/**< TimeOut */
	SSP_RXIM = ((uint32_t)(1 << 2)),/**< Rx FIFO is at least half full */
	SSP_TXIM = ((uint32_t)(1 << 3)),/**< Tx FIFO is at least half empty */
	SSP_INT_MASK_BITMASK = ((uint32_t)(0xF)),
} SSP_Int_Mask_Type;

/**
 * @brief SSP Type of Mask Interrupt Status
 */
typedef enum {
	SSP_RORMIS = ((uint32_t)(1 << 0)),	/**< Overun */
	SSP_RTMIS = ((uint32_t)(1 << 1)),	/**< TimeOut */
	SSP_RXMIS = ((uint32_t)(1 << 2)),	/**< Rx FIFO is at least half full */
	SSP_TXMIS = ((uint32_t)(1 << 3)),	/**< Tx FIFO is at least half empty */
	SSP_MASK_INT_STAT_BITMASK = ((uint32_t)(0xF)),
} SSP_Mask_Int_Status_Type;

/**
 * @brief SSP Type of Raw Interrupt Status
 */
typedef enum {
	SSP_RORRIS = ((uint32_t)(1 << 0)),	/**< Overun */
	SSP_RTRIS = ((uint32_t)(1 << 1)),	/**< TimeOut */
	SSP_RXRIS = ((uint32_t)(1 << 2)),	/**< Rx FIFO is at least half full */
	SSP_TXRIS = ((uint32_t)(1 << 3)),	/**< Tx FIFO is at least half empty */
	SSP_RAW_INT_STAT_BITMASK = ((uint32_t)(0xF)),
} SSP_Raw_Int_Status_Type;

typedef enum {
	SSP_RORIC = 0x0,
	SSP_RTIC = 0x1,
	SSP_INT_CLEAR_BITMASK = 0x3,
} SSP_Int_Clear_Type;

typedef enum SSP_DMA_Type {
	SSP_DMA_RX = (1u),	/**< DMA RX Enable */
	SSP_DMA_TX = (1u << 1),	/**< DMA TX Enable */
} SSP_DMA_Type;

/**
 * @brief	Disable SSP operation
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @return	 Nothing
 * The SSP controller is disabled
 */
void IP_SSP_DeInit(IP_SSP_001_Type *pSSP);

/**
 * @brief	Enable/Disable SSP operation
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	 Nothing
 */
void IP_SSP_Cmd(IP_SSP_001_Type *pSSP, FunctionalState NewState);

/**
 * @brief	Enable/Disable loopback mode
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	 Nothing
 * Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin
 */
void IP_SSP_LoopBackCmd(IP_SSP_001_Type *pSSP, FunctionalState NewState);

/**
 * @brief	Get the current status of SSP controller
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @param	Stat	: Type of status, should be :
 *						- SSP_STAT_TFE
 *						- SSP_STAT_TNF
 *						- SSP_STAT_RNE
 *						- SSP_STAT_RFF
 *						- SSP_STAT_BSY
 * @return	 SSP controller status, SET or RESET
 */
FlagStatus IP_SSP_GetStatus(IP_SSP_001_Type *pSSP, SSP_Status_Type Stat);

/**
 * @brief	Get the masked interrupt status
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @return	 SSP Masked Interrupt Status Register value
 * The return value contains a 1 for each interrupt condition that is asserted and enabled (masked)
 */
uint32_t IP_SSP_GetIntStatus(IP_SSP_001_Type *pSSP);

/**
 * @brief	Get the raw interrupt status
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @param	RawInt	: Interrupt condition to be get status, shoud be :
 *						- SSP_RORRIS
 *						- SSP_RTRIS
 *						- SSP_RXRIS
 *						- SSP_TXRIS
 * @return	 Raw interrupt status corresponding to interrupt condition , SET or RESET
 * Get the status of each interrupt condition ,regardless of whether or not the interrupt is enabled
 */
IntStatus IP_SSP_GetRawIntStatus(IP_SSP_001_Type *pSSP, SSP_Raw_Int_Status_Type RawInt);

/**
 * @brief	Get the number of bits transferred in each frame
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @return	 the number of bits transferred in each frame minus one
 * The return value is 0x03 -> 0xF corresponding to 4bit -> 16bit transfer
 */
uint8_t IP_SSP_GetDataSize(IP_SSP_001_Type *pSSP);

/**
 * @brief	Clear the corresponding interrupt condition(s) in the SSP controller
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @param	IntClear: Type of cleared interrupt, should be :
 *						- SSP_RORIC
 *						- SSP_RTIC
 * @return	 Nothing
 * Software can clear one or more interrupt condition(s) in the SSP controller
 */
void IP_SSP_ClearIntPending(IP_SSP_001_Type *pSSP, SSP_Int_Clear_Type IntClear);

/**
 * @brief	Enable/Disable interrupt for the SSP
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	IntType		: Type of interrupt condition to be enable/disable, should be :
 *							- SSP_RORIM
 *							- SSP_RTIM
 *							- SSP_RXIM
 *							- SSP_TXIM
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	 Nothing
 */
void IP_SSP_Int_Enable(IP_SSP_001_Type *pSSP, SSP_Int_Mask_Type IntType, FunctionalState NewState);

/**
 * @brief	Get received SSP data
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @return	 SSP 16-bit data received
 */
uint16_t IP_SSP_ReceiveFrame(IP_SSP_001_Type *pSSP);

/**
 * @brief	Send SSP 16-bit data
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @param	tx_data	: SSP 16-bit data to be transmited
 * @return	 Nothing
 */
void IP_SSP_SendFrame(IP_SSP_001_Type *pSSP, uint16_t tx_data);

/**
 * @brief	Set up output clocks per bit for SSP bus
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	clk_rate	fs: The number of prescaler-output clocks per bit on the bus, minus one
 * @param	prescale	: The factor by which the Prescaler divides the SSP peripheral clock PCLK
 * @return	 Nothing
 * The bit frequency is PCLK / (prescale x[clk_rate+1])
 */
void IP_SSP_Set_ClockRate(IP_SSP_001_Type *pSSP, uint32_t clk_rate, uint32_t prescale);

/**
 * @brief	Set up the SSP frame format
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	bits		: The number of bits transferred in each frame, should be SSP_BITS_4 to SSP_BITS_16
 * @param	frameFormat	: Frame format, should be :
 *							- SSP_FRAMEFORMAT_SPI
 *							- SSP_FRAMEFORMAT_TI
 *							- SSP_FRAMEFORMAT_MICROWIRE
 * @param	clockFormat	: Select Clock polarity and Clock phase, should be :
 *							- SSP_CLOCK_CPHA0_CPOL0
 *							- SSP_CLOCK_CPHA0_CPOL1
 *							- SSP_CLOCK_CPHA1_CPOL0
 *							- SSP_CLOCK_CPHA1_CPOL1
 * @return	 Nothing
 * Note: The clockFormat is only used in SPI mode
 */
void IP_SSP_Set_Format(IP_SSP_001_Type *pSSP, uint32_t bits, uint32_t frameFormat, uint32_t clockFormat);

/**
 * @brief	Set the SSP working as master or slave mode
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @param	mode	: Operating mode, should be
 *						- SSP_MODE_MASTER
 *						- SSP_MODE_SLAVE
 * @return	 Nothing
 */
void IP_SSP_Set_Mode(IP_SSP_001_Type *pSSP, uint32_t mode);

/**
 * @brief	Enable/Disable DMA for SSP
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	ssp_dma_t	: DMA set up for transmit/receive SSP, should be
 *							- SSP_DMA_RX
 *							- SSP_DMA_TX
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	 Nothing
 */
void IP_SSP_DMA_Cmd(IP_SSP_001_Type *pSSP, SSP_DMA_Type ssp_dma_t, FunctionalState NewState);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SSP_001_H_ */
