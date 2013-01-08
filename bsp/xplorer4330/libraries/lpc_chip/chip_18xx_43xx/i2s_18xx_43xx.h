/*
 * @brief LPC18xx/43xx I2S driver
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

#ifndef __I2S_18XX_43XX_H_
#define __I2S_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup I2S_18XX_43XX CHIP: LPC18xx/43xx I2S driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

#define I2S_DMA_REQUEST_NUMBER_1 IP_I2S_DMA_REQUEST_NUMBER_1
#define I2S_DMA_REQUEST_NUMBER_2 IP_I2S_DMA_REQUEST_NUMBER_2

/**
 * @brief I2S Audio Format Structure
 */
typedef struct {
	uint32_t SampleRate;	/*!< Sample Rate */
	uint8_t ChannelNumber;	/*!< Channel Number - 1 is mono, 2 is stereo */
	uint8_t WordWidth;		/*!< Word Width - 8, 16 or 32 bits */
} Chip_I2S_Audio_Format_Type;

/**
 * @brief	Initialize for I2S
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_I2S_Init(LPC_I2S_Type *pI2S)
{
	IP_I2S_Init(pI2S);
}

/**
 * @brief	Shutdown I2S
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 * Reset all relative registers (DMA, transmit/receive control, interrupt) to default value
 */
STATIC INLINE void Chip_I2S_DeInit(LPC_I2S_Type *pI2S)
{
	IP_I2S_DeInit(pI2S);
}

/**
 * @brief	Send a 32-bit data to TXFIFO for transmition
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	data	: Data to be transmited
 * @return	Nothing
 * The function writes to TXFIFO without checking any condition.
 */
STATIC INLINE void Chip_I2S_Send(LPC_I2S_Type *pI2S, uint32_t data)
{
	IP_I2S_Send(pI2S, data);
}

/**
 * @brief	Get received data from RXFIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Data received in RXFIFO
 * The function reads from RXFIFO without checking any condition.
 */
STATIC INLINE uint32_t Chip_I2S_Receive(LPC_I2S_Type *pI2S)
{
	return IP_I2S_Receive(pI2S);
}

/**
 * @brief	Start the I2S
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 */
STATIC INLINE void Chip_I2S_Start(LPC_I2S_Type *pI2S, uint8_t TRMode)
{
	IP_I2S_Start(pI2S, TRMode);
}

/**
 * @brief	Disables accesses on FIFOs, places the transmit channel in mute mode
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 */
STATIC INLINE void Chip_I2S_Pause(LPC_I2S_Type *pI2S, uint8_t TRMode)
{
	IP_I2S_Pause(pI2S, TRMode);
}

/**
 * @brief	Transmit channel sends only zeroes
 * @param	pI2S		: The base of I2S peripheral on the chip
 * @param	NewState	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 * The data output from I2S transmit channel is always zeroes
 */
STATIC INLINE void Chip_I2S_Mute(LPC_I2S_Type *pI2S, FunctionalState NewState)
{
	IP_I2S_Mute(pI2S, NewState);
}

/**
 * @brief	Stop I2S asynchronously
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Nothing
 * Pause, resets the transmit channel and FIFO asynchronously
 */
STATIC INLINE void Chip_I2S_Stop(LPC_I2S_Type *pI2S, uint8_t TRMode)
{
	IP_I2S_Stop(pI2S, TRMode);
}

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
STATIC INLINE void Chip_I2S_ModeConfig(LPC_I2S_Type *pI2S,
										 uint8_t TRMode,
										 uint32_t clksel,
										 uint32_t fpin,
										 uint32_t mcena)
{
	IP_I2S_ModeConfig(pI2S, TRMode, clksel, fpin, mcena);
}

/**
 * @brief	Get the current level of the Transmit/Receive FIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	TRMode	: Transmit/Receive mode, should be I2S_RX_MODE or I2S_TX_MODE
 * @return	Current level of the Transmit/Receive FIFO
 */
STATIC INLINE uint8_t Chip_I2S_GetLevel(LPC_I2S_Type *pI2S, uint8_t TRMode)
{
	return IP_I2S_GetLevel(pI2S, TRMode);
}

/**
 * @brief   Configure I2S for Audio Format input
 * @param	pI2S			: The base I2S peripheral on the chip
 * @param	TRMode			: Mode Rx/Tx
 * @param	audio_format	: Audio Format
 * @return	SUCCESS or ERROR
 */
Status Chip_I2S_Config(LPC_I2S_Type *pI2S, uint8_t TRMode, Chip_I2S_Audio_Format_Type *audio_format);

/**
 * @brief   Enable/Disable Interrupt with a specific FIFO depth
 * @param	pI2S			: The base I2S peripheral on the chip
 * @param	TRMode			: Mode Rx/Tx
 * @param	NewState		: ENABLE or DISABLE interrupt
 * @param	FIFO_Depth		: FIFO level creating an irq request
 * @return	Nothing
 */
void Chip_I2S_Int_Cmd(LPC_I2S_Type *pI2S, uint8_t TRMode, FunctionalState NewState, uint8_t FIFO_Depth);

/**
 * @brief   Enable/Disable DMA with a specific FIFO depth
 * @param	pI2S			: The base I2S peripheral on the chip
 * @param	TRMode			: Mode Rx/Tx
 * @param	DMANum			: Should be
 *								- IP_I2S_DMA_REQUEST_NUMBER_1 : Using DMA1
 *								- IP_I2S_DMA_REQUEST_NUMBER_2 : Using DMA2
 * @param	NewState		: ENABLE or DISABLE interrupt
 * @param	FIFO_Depth		: FIFO level creating an irq request
 * @return	Nothing
 */
void Chip_I2S_DMA_Cmd(LPC_I2S_Type *pI2S, uint8_t TRMode, uint8_t DMANum, FunctionalState NewState, uint8_t FIFO_Depth);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __I2S_18XX_43XX_H_ */
