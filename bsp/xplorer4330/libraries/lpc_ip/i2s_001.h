/*
 * @brief I2S Registers and control functions
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

#ifndef __I2S_001_H_
#define __I2S_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_I2S_001 IP: I2S register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief I2S register block structure
 */
typedef struct {				/*!< I2S Structure */
	__IO uint32_t DAO;			/*!< I2S Digital Audio Output Register. Contains control bits for the I2S transmit channel */
	__IO uint32_t DAI;			/*!< I2S Digital Audio Input Register. Contains control bits for the I2S receive channel */
	__O uint32_t TXFIFO;		/*!< I2S Transmit FIFO. Access register for the 8 x 32-bit transmitter FIFO */
	__I uint32_t RXFIFO;		/*!< I2S Receive FIFO. Access register for the 8 x 32-bit receiver FIFO */
	__I uint32_t STATE;			/*!< I2S Status Feedback Register. Contains status information about the I2S interface */
	__IO uint32_t DMA1;			/*!< I2S DMA Configuration Register 1. Contains control information for DMA request 1 */
	__IO uint32_t DMA2;			/*!< I2S DMA Configuration Register 2. Contains control information for DMA request 2 */
	__IO uint32_t IRQ;			/*!< I2S Interrupt Request Control Register. Contains bits that control how the I2S interrupt request is generated */
	__IO uint32_t TXRATE;		/*!< I2S Transmit MCLK divider. This register determines the I2S TX MCLK rate by specifying the value to divide PCLK by in order to produce MCLK */
	__IO uint32_t RXRATE;		/*!< I2S Receive MCLK divider. This register determines the I2S RX MCLK rate by specifying the value to divide PCLK by in order to produce MCLK */
	__IO uint32_t TXBITRATE;	/*!< I2S Transmit bit rate divider. This register determines the I2S transmit bit rate by specifying the value to divide TX_MCLK by in order to produce the transmit bit clock */
	__IO uint32_t RXBITRATE;	/*!< I2S Receive bit rate divider. This register determines the I2S receive bit rate by specifying the value to divide RX_MCLK by in order to produce the receive bit clock */
	__IO uint32_t TXMODE;		/*!< I2S Transmit mode control */
	__IO uint32_t RXMODE;		/*!< I2S Receive mode control */
} IP_I2S_001_Type;

/**
 * @brief I2S configuration parameter defines
 */
/** I2S Wordwidth bit */
#define I2S_WORDWIDTH_8     (0UL << 0)
#define I2S_WORDWIDTH_16    (1UL << 0)
#define I2S_WORDWIDTH_32    (3UL << 0)
/** I2S Channel bit */
#define I2S_STEREO          (0UL << 2)
#define I2S_MONO            (1UL << 2)
/** I2S Master/Slave mode bit */
#define I2S_MASTER_MODE     (0UL << 5)
#define I2S_SLAVE_MODE      (1UL << 5)
/** I2S Stop bit */
#define I2S_STOP_ENABLE     (0UL << 3)
#define I2S_STOP_DISABLE    (1UL << 3)
/** I2S Reset bit */
#define I2S_RESET_ENABLE    (1UL << 4)
#define I2S_RESET_DISABLE   (0UL << 4)
/** I2S Mute bit */
#define I2S_MUTE_ENABLE     (1UL << 15)
#define I2S_MUTE_DISABLE    (0UL << 15)

/**
 * @brief Macro defines for DAO-Digital Audio Output register
 */

/** I2S wordwide - the number of bytes in data*/
#define I2S_DAO_WORDWIDTH_8     ((uint32_t) (0))	/** 8 bit	*/
#define I2S_DAO_WORDWIDTH_16    ((uint32_t) (1))	/** 16 bit	*/
#define I2S_DAO_WORDWIDTH_32    ((uint32_t) (3))	/** 32 bit	*/
#define I2S_DAO_WORDWIDTH_MASK  ((uint32_t) (3))
/** I2S control mono or stereo format */
#define I2S_DAO_MONO            ((uint32_t) (1 << 2))
/** I2S control stop mode */
#define I2S_DAO_STOP            ((uint32_t) (1 << 3))
/** I2S control reset mode */
#define I2S_DAO_RESET           ((uint32_t) (1 << 4))
/** I2S control master/slave mode */
#define I2S_DAO_SLAVE           ((uint32_t) (1 << 5))
/** I2S word select half period minus one */
#define I2S_DAO_WS_HALFPERIOD(n)    ((uint32_t) ((n & 0x1FF) << 6))
#define I2S_DAO_WS_HALFPERIOD_MASK  ((uint32_t) ((0x1FF) << 6))
/** I2S control mute mode */
#define I2S_DAO_MUTE            ((uint32_t) (1 << 15))

/**
 * @brief Macro defines for DAI-Digital Audio Input register
 */

/** I2S wordwide - the number of bytes in data*/
#define I2S_DAI_WORDWIDTH_8     ((uint32_t) (0))	/** 8 bit	*/
#define I2S_DAI_WORDWIDTH_16    ((uint32_t) (1))	/** 16 bit	*/
#define I2S_DAI_WORDWIDTH_32    ((uint32_t) (3))	/** 32 bit	*/
#define I2S_DAI_WORDWIDTH_MASK  ((uint32_t) (3))
/** I2S control mono or stereo format */
#define I2S_DAI_MONO            ((uint32_t) (1 << 2))
/** I2S control stop mode */
#define I2S_DAI_STOP            ((uint32_t) (1 << 3))
/** I2S control reset mode */
#define I2S_DAI_RESET           ((uint32_t) (1 << 4))
/** I2S control master/slave mode */
#define I2S_DAI_SLAVE           ((uint32_t) (1 << 5))
/** I2S word select half period minus one (9 bits)*/
#define I2S_DAI_WS_HALFPERIOD(n)    ((uint32_t) ((n & 0x1FF) << 6))
#define I2S_DAI_WS_HALFPERIOD_MASK  ((uint32_t) ((0x1FF) << 6))

/**
 * @brief Macro defines for STAT register (Status Feedback register)
 */

/** I2S Status Receive or Transmit Interrupt */
#define I2S_STATE_IRQ       ((uint32_t) (1))
/** I2S Status Receive or Transmit DMA1 */
#define I2S_STATE_DMA1      ((uint32_t) (1 << 1))
/** I2S Status Receive or Transmit DMA2 */
#define I2S_STATE_DMA2      ((uint32_t) (1 << 2))
/** I2S Status Current level of the Receive FIFO (5 bits)*/
#define I2S_STATE_RX_LEVEL(n)   ((uint32_t) ((n & 1F) << 8))
/** I2S Status Current level of the Transmit FIFO (5 bits)*/
#define I2S_STATE_TX_LEVEL(n)   ((uint32_t) ((n & 1F) << 16))

/**
 * @brief Macro defines for DMA1 register (DMA1 Configuration register)
 */

/** I2S control DMA1 for I2S receive */
#define I2S_DMA1_RX_ENABLE      ((uint32_t) (1))
/** I2S control DMA1 for I2S transmit */
#define I2S_DMA1_TX_ENABLE      ((uint32_t) (1 << 1))
/** I2S set FIFO level that trigger a receive DMA request on DMA1 */
#define I2S_DMA1_RX_DEPTH(n)    ((uint32_t) ((n & 0x1F) << 8))
/** I2S set FIFO level that trigger a transmit DMA request on DMA1 */
#define I2S_DMA1_TX_DEPTH(n)    ((uint32_t) ((n & 0x1F) << 16))

/**
 * @brief Macro defines for DMA2 register (DMA2 Configuration register)
 */

/** I2S control DMA2 for I2S receive */
#define I2S_DMA2_RX_ENABLE      ((uint32_t) (1))
/** I2S control DMA1 for I2S transmit */
#define I2S_DMA2_TX_ENABLE      ((uint32_t) (1 << 1))
/** I2S set FIFO level that trigger a receive DMA request on DMA1 */
#define I2S_DMA2_RX_DEPTH(n)    ((uint32_t) ((n & 0x1F) << 8))
/** I2S set FIFO level that trigger a transmit DMA request on DMA1 */
#define I2S_DMA2_TX_DEPTH(n)    ((uint32_t) ((n & 0x1F) << 16))

/**
 * @brief Macro defines for IRQ register (Interrupt Request Control register)
 */

/** I2S control I2S receive interrupt */
#define I2S_IRQ_RX_ENABLE       ((uint32_t) (1))
/** I2S control I2S transmit interrupt */
#define I2S_IRQ_TX_ENABLE       ((uint32_t) (1 << 1))
/** I2S set the FIFO level on which to create an irq request */
#define I2S_IRQ_RX_DEPTH(n)     ((uint32_t) ((n & 0x0F) << 8))
#define I2S_IRQ_RX_DEPTH_MASK   ((uint32_t) ((0x0F) << 8))
/** I2S set the FIFO level on which to create an irq request */
#define I2S_IRQ_TX_DEPTH(n)     ((uint32_t) ((n & 0x0F) << 16))
#define I2S_IRQ_TX_DEPTH_MASK   ((uint32_t) ((0x0F) << 16))

/**
 * @brief Macro defines for TXRATE/RXRATE register (Transmit/Receive Clock Rate register)
 */

/** I2S Transmit MCLK rate denominator */
#define I2S_TXRATE_Y_DIVIDER(n) ((uint32_t) (n & 0xFF))
/** I2S Transmit MCLK rate denominator */
#define I2S_TXRATE_X_DIVIDER(n) ((uint32_t) ((n & 0xFF) << 8))
/** I2S Receive MCLK rate denominator */
#define I2S_RXRATE_Y_DIVIDER(n) ((uint32_t) (n & 0xFF))
/** I2S Receive MCLK rate denominator */
#define I2S_RXRATE_X_DIVIDER(n) ((uint32_t) ((n & 0xFF) << 8))

/**
 * @brief Macro defines for TXBITRATE & RXBITRATE register (Transmit/Receive Bit Rate register)
 */

#define I2S_TXBITRATE(n)    ((uint32_t) (n & 0x3F))
#define I2S_RXBITRATE(n)    ((uint32_t) (n & 0x3F))

/**
 * @brief Macro defines for TXMODE/RXMODE register (Transmit/Receive Mode Control register)
 */

/** I2S Transmit select clock source (2 bits)*/
#define I2S_TXMODE_CLKSEL(n)    ((uint32_t) (n & 0x03))
/** I2S Transmit control 4-pin mode */
#define I2S_TXMODE_4PIN_ENABLE  ((uint32_t) (1 << 2))
/** I2S Transmit control the TX_MCLK output */
#define I2S_TXMODE_MCENA        ((uint32_t) (1 << 3))
/** I2S Receive select clock source */
#define I2S_RXMODE_CLKSEL(n)    ((uint32_t) (n & 0x03))
/** I2S Receive control 4-pin mode */
#define I2S_RXMODE_4PIN_ENABLE  ((uint32_t) (1 << 2))
/** I2S Receive control the TX_MCLK output */
#define I2S_RXMODE_MCENA        ((uint32_t) (1 << 3))

/**
 * @brief I2S transmit/receive mode for configuration
 */
typedef enum {
	I2S_TX_MODE,
	I2S_RX_MODE,
} IP_I2S_TRxMode_Type;

/**
 * @brief I2S DMA request channel define
 */
typedef enum {
	IP_I2S_DMA_REQUEST_NUMBER_1,
	IP_I2S_DMA_REQUEST_NUMBER_2,
} IP_I2S_DMARequestNumber_Type;

/**********************************************************************************
 * I2S Init/DeInit functions
 *********************************************************************************/

/**
 * @brief	Initialize for I2S
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 */
void IP_I2S_Init(IP_I2S_001_Type *pI2S);

/**
 * @brief	Shutdown I2S
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 * Reset all relative registers (DMA, transmit/receive control, interrupt) to default value
 */
void IP_I2S_DeInit(IP_I2S_001_Type *pI2S);

/**********************************************************************************
 * I2S configuration functions
 *********************************************************************************/

/**
 * @brief	Selects the number of bytes in data
 * @param	pI2S		: The base of I2S peripheral on the chip
 * @param	TRMode		: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	wordwidth	: Data width, should be :
 *							- I2S_WORDWIDTH_8
 *							- I2S_WORDWIDTH_16
 *							- I2S_WORDWIDTH_32
 * @return	Nothing
 */
void IP_I2S_SetWordWidth(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t wordwidth);

/**
 * @brief	Set I2S data format is monaural or stereo
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	mono	: Data channel, should be
 *						- I2S_STEREO
 *						- I2S_MONO
 * @return	Nothing
 */
void IP_I2S_SetMono(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t mono);

/**
 * @brief	Set I2S interface in master/slave mode
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	mode	: Interface mode, should be
 *						- I2S_MASTER_MODE
 *						- I2S_SLAVE_MODE
 * @return	Nothing
 */
void IP_I2S_SetMasterSlaveMode(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t mode);

/**
 * @brief	Set the clock frequency for I2S interface
 * @param	pI2S			: The base of I2S peripheral on the chip
 * @param	TRMode			: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	mclk_divider	: Clock divider. This value plus one is used to divide MCLK to produce the clock frequency for I2S interface
 * @return	 Nothing
 * The value depends on the audio sample rate desired and the data size and format(stereo/mono) used.
 * For example, a 48 kHz sample rate for 16-bit stereo data requires a bit rate of 48 000 x 16 x 2 = 1.536 MHz. So the mclk_divider should be MCLK/1.536 MHz
 */
void IP_I2S_SetBitRate(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t mclk_divider);

/**
 * @brief	Set the MCLK rate by using a fractional rate generator, dividing down the frequency of PCLK
 * @param	pI2S		: The base of I2S peripheral on the chip
 * @param	TRMode		: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	x_divider	: I2S transmit MCLK rate numerator
 * @param	y_devider	: I2S transmit MCLK rate denominator
 * @return	Nothing
 * Values of the numerator (X) and the denominator (Y) must be chosen to
 * produce a frequency twice that desired for the transmitter MCLK, which
 * must be an integer multiple of the transmitter bit clock rate.
 * The equation for the fractional rate generator is:
 * MCLK = PCLK * (X/Y) /2
 * Note: If the value of X or Y is 0, then no clock is generated. Also, the value of Y must be
 * greater than or equal to X.
 */
void IP_I2S_SetXYDivider(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint8_t x_divider, uint8_t y_devider);

/**
 * @brief	Set word select (WS) half period
 * @param	pI2S			: The base of I2S peripheral on the chip
 * @param	TRMode			: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	ws_halfperiod	: I2S word select half period minus one
 * @return	Nothing
 * The Word Select period is configured separately for I2S input and I2S output.
 * For example: if the WS is 64clk period -> ws_halfperiod = 31
 */
void IP_I2S_SetWS_Halfperiod(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t ws_halfperiod);

/**
 * @brief	Set the I2S operating modes
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	clksel	: Clock source selection for the receive bit clock divider
 * @param	fpin	: Receive 4-pin mode selection
 * @param	mcena	: Enable for the RX_MCLK output
 * @return	Nothing
 * In addition to master and slave modes, which are independently configurable for
 * the transmitter and the receiver, several different clock sources are possible,
 * including variations that share the clock and/or WS between the transmitter and
 * receiver. It also allows using I2S with fewer pins, typically four.
 */
void IP_I2S_ModeConfig(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t clksel, uint32_t fpin, uint32_t mcena);

/**
 * @brief	Get the current level of the Transmit/Receive FIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Current level of the Transmit/Receive FIFO
 */
uint8_t IP_I2S_GetLevel(IP_I2S_001_Type *pI2S, uint8_t TRMode);

/**********************************************************************************
 * I2S operate functions
 *********************************************************************************/

/**
 * @brief	Send a 32-bit data to TXFIFO for transmition
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	data	: Data to be transmited
 * @return	Nothing
 * The function writes to TXFIFO without checking any condition.
 */
void IP_I2S_Send(IP_I2S_001_Type *pI2S, uint32_t data);

/**
 * @brief	Get received data from RXFIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Data received in RXFIFO
 * The function reads from RXFIFO without checking any condition.
 */
uint32_t IP_I2S_Receive(IP_I2S_001_Type *pI2S);

/**
 * @brief	Start the I2S
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 */
void IP_I2S_Start(IP_I2S_001_Type *pI2S, uint8_t TRMode);

/**
 * @brief	Disables accesses on FIFOs, places the transmit channel in mute mode
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 */
void IP_I2S_Pause(IP_I2S_001_Type *pI2S, uint8_t TRMode);

/**
 * @brief	Transmit channel sends only zeroes
 * @param	pI2S		: The base of I2S peripheral on the chip
 * @param	NewState	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 * The data output from I2S transmit channel is always zeroes
 */
void IP_I2S_Mute(IP_I2S_001_Type *pI2S, FunctionalState NewState);

/**
 * @brief	Stop I2S asynchronously
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 * Pause, resets the transmit channel and FIFO asynchronously
 */
void IP_I2S_Stop(IP_I2S_001_Type *pI2S, uint8_t TRMode);

/**********************************************************************************
 * I2S DMA functions
 *********************************************************************************/

/**
 * @brief	Set the FIFO level on which to create an DMA request
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	DMANum	: I2S DMA request number, should be
 *						- IP_I2S_DMA_REQUEST_NUMBER_1
 *						- IP_I2S_DMA_REQUEST_NUMBER_2
 * @param	depth	: FIFO level on which to create an DMA request
 * @return	Nothing
 * DMA request is generated when rx_depth_dma <= rx_level or tx_depth_dma >= tx_level
 */
void IP_I2S_SetFIFODepthDMA(IP_I2S_001_Type *pI2S, uint8_t TRMode, IP_I2S_DMARequestNumber_Type DMANum, uint32_t depth);

/**
 * @brief	Enable/Disable DMA for the I2S
 * @param	pI2S		: The base of I2S peripheral on the chip
 * @param	TRMode		: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	DMANum		: I2S DMA request number, should be
 *							- IP_I2S_DMA_REQUEST_NUMBER_1
 *							- IP_I2S_DMA_REQUEST_NUMBER_2
 * @param	NewState	: ENABLE or DISABLE DMA
 * @return	Nothing
 */
void IP_I2S_DMACmd(IP_I2S_001_Type *pI2S, IP_I2S_DMARequestNumber_Type DMANum, uint8_t TRMode, FunctionalState NewState);

/**********************************************************************************
 * I2S IRQ functions
 *********************************************************************************/

/**
 * @brief	Enable/Disable interrupt for the I2S
 * @param	pI2S		: The base of I2S peripheral on the chip
 * @param	TRMode		: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	NewState	: ENABLE or DISABLE Interrupt
 * @return	Nothing
 * Interrupt request is generated when rx_depth_irq <= rx_level or tx_depth_irq >= tx_level
 */
void IP_I2S_InterruptCmd(IP_I2S_001_Type *pI2S, uint8_t TRMode, FunctionalState NewState);

/**
 * @brief	Set the FIFO level on which to create an irq request
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @param	depth	: FIFO level on which to create an irq request
 * @return	 Nothing
 */
void IP_I2S_SetFIFODepthIRQ(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t depth);

/**
 * @brief	Get the status of I2S interrupt
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	I2S interrupt status, SET or RESET
 */
Status IP_I2S_GetIntStatus(IP_I2S_001_Type *pI2S, uint8_t TRMode);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __I2S_001_H_ */
