/*
 * @brief LPC18xx/43xx SSP driver
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

#ifndef __SSP_18XX_43XX_H_
#define __SSP_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SSP_18XX_43XX CHIP: LPC18xx/43xx SSP driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/*
 * @brief SSP clock format
 */
typedef enum SSP_ClockFormat {
	SSP_CLOCK_CPHA0_CPOL0 = (0 << 6),		/**< CPHA = 0, CPOL = 0 */
	SSP_CLOCK_CPHA0_CPOL1 = (1u << 6),		/**< CPHA = 0, CPOL = 1 */
	SSP_CLOCK_CPHA1_CPOL0 = (2u << 6),		/**< CPHA = 1, CPOL = 0 */
	SSP_CLOCK_CPHA1_CPOL1 = (3u << 6),		/**< CPHA = 1, CPOL = 1 */
	SSP_CLOCK_MODE0 = SSP_CLOCK_CPHA0_CPOL0,/**< alias */
	SSP_CLOCK_MODE1 = SSP_CLOCK_CPHA1_CPOL0,/**< alias */
	SSP_CLOCK_MODE2 = SSP_CLOCK_CPHA0_CPOL1,/**< alias */
	SSP_CLOCK_MODE3 = SSP_CLOCK_CPHA1_CPOL1,/**< alias */
} SSP_ClockFormat;

/*
 * @brief SSP frame format
 */
typedef enum SSP_FrameFormat {
	SSP_FRAMEFORMAT_SPI = (0 << 4),			/**< Frame format: SPI */
	SSP_FRAMEFORMAT_TI = (1u << 4),			/**< Frame format: TI SSI */
	SSP_FRAMEFORMAT_MICROWIRE = (2u << 4),	/**< Frame format: Microwire */
} SSP_FrameFormat;

/*
 * @brief Number of bits per frame
 */
typedef enum SSP_Bits {
	SSP_BITS_4 = (3u << 0),		/**< 4 bits/frame */
	SSP_BITS_5 = (4u << 0),		/**< 5 bits/frame */
	SSP_BITS_6 = (5u << 0),		/**< 6 bits/frame */
	SSP_BITS_7 = (6u << 0),		/**< 7 bits/frame */
	SSP_BITS_8 = (7u << 0),		/**< 8 bits/frame */
	SSP_BITS_9 = (8u << 0),		/**< 9 bits/frame */
	SSP_BITS_10 = (9u << 0),	/**< 10 bits/frame */
	SSP_BITS_11 = (10u << 0),	/**< 11 bits/frame */
	SSP_BITS_12 = (11u << 0),	/**< 12 bits/frame */
	SSP_BITS_13 = (12u << 0),	/**< 13 bits/frame */
	SSP_BITS_14 = (13u << 0),	/**< 14 bits/frame */
	SSP_BITS_15 = (14u << 0),	/**< 15 bits/frame */
	SSP_BITS_16 = (15u << 0),	/**< 16 bits/frame */
} SSP_Bits;

/*
 * @brief SSP config format
 */
typedef struct SSP_ConfigFormat {
	SSP_Bits bits;				/**< Format config: bits/frame */
	SSP_ClockFormat clockFormat;/**< Format config: clock phase/polarity */
	SSP_FrameFormat frameFormat;/**< Format config: SPI/TI/Microwire */
} SSP_ConfigFormat;

/*
 * @brief SSP mode
 */
typedef enum SSP_Mode {
	SSP_MODE_MASTER = (0 << 2),	/**< Master mode */
	SSP_MODE_SLAVE = (1u << 2),	/**< Slave mode */
} SSP_Mode;

/*
 * @brief SPI address
 */
typedef struct {
	uint8_t port;
	uint8_t pin;
} SPI_Address_t;

/*
 * @brief SSP data setup structure
 */
typedef struct {
	void      *tx_data;	/**< Pointer to transmit data */
	uint32_t  tx_cnt;	/**< Transmit counter */
	void      *rx_data;	/**< Pointer to transmit data */
	uint32_t  rx_cnt;	/**< Receive counter */
	uint32_t  length;	/**< Length of transfer data */
} Chip_SSP_DATA_SETUP_Type;

/** SSP configuration parameter defines */
/** Clock phase control bit */
#define SSP_CPHA_FIRST          SSP_CR0_CPHA_FIRST
#define SSP_CPHA_SECOND         SSP_CR0_CPHA_SECOND

/** Clock polarity control bit */
/* There's no bug here!!!
 * - If bit[6] in SSPnCR0 is 0: SSP controller maintains the bus clock low between frames.
 * That means the active clock is in HI state.
 * - If bit[6] in SSPnCR0 is 1 (SSP_CR0_CPOL_HI): SSP controller maintains the bus clock
 * high between frames. That means the active clock is in LO state.
 */
#define SSP_CPOL_HI             SSP_CR0_CPOL_LO
#define SSP_CPOL_LO             SSP_CR0_CPOL_HI

/** SSP master mode enable */
#define SSP_SLAVE_MODE          SSP_CR1_SLAVE_EN
#define SSP_MASTER_MODE         SSP_CR1_MASTER_EN

/**
 * @brief	Get the current status of SSP controller
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @param	Stat	: Type of status, should be :
 *						- SSP_STAT_TFE
 *						- SSP_STAT_TNF
 *						- SSP_STAT_RNE
 *						- SSP_STAT_RFF
 *						- SSP_STAT_BSY
 * @return	SSP controller status, SET or RESET
 */
STATIC INLINE FlagStatus Chip_SSP_GetStatus(LPC_SSP_Type *pSSP, SSP_Status_Type Stat)
{
	return IP_SSP_GetStatus(pSSP, Stat);
}

/**
 * @brief	Enable/Disable SSP operation
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	Nothing
 */
STATIC INLINE void Chip_SSP_Cmd(LPC_SSP_Type *pSSP, FunctionalState NewState)
{
	IP_SSP_Cmd(pSSP, NewState);
}

/**
 * @brief	Disable SSP operation
 * @param	pSSP	: The base of SSP peripheral on the chip
 * @return	Nothing
 * The SSP controller is disabled
 */
STATIC INLINE void Chip_SSP_DeInit(LPC_SSP_Type *pSSP)
{
	IP_SSP_DeInit(pSSP);
}

/**
 * @brief	Enable/Disable loopback mode
 * @param	pSSP		: The base of SSP peripheral on the chip
 * @param	NewState	: New state, ENABLE or DISABLE
 * @return	Nothing
 * Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin
 */
STATIC INLINE void Chip_SSP_LoopBackCmd(LPC_SSP_Type *pSSP, FunctionalState NewState)
{
	IP_SSP_LoopBackCmd(pSSP, NewState);
}

/**
 * @brief   Clean all data in RX FIFO of SSP
 * @param	pSSP			: The base SSP peripheral on the chip
 * @return	Nothing
 */
void Chip_SSP_Int_FlushData(LPC_SSP_Type *pSSP);

/**
 * @brief   SSP Interrupt Read/Write with 8-bit frame width
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	xf_setup		: Pointer to a SSP_DATA_SETUP_Type structure that contains specified
 * 							information about transmit/receive data	configuration
 * @return	SUCCESS or ERROR
 */
Status Chip_SSP_Int_RWFrames8Bits(LPC_SSP_Type *pSSP, Chip_SSP_DATA_SETUP_Type *xf_setup);

/**
 * @brief   SSP Interrupt Read/Write with 16-bit frame width
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	xf_setup		: Pointer to a SSP_DATA_SETUP_Type structure that contains specified
 * 							information about transmit/receive data	configuration
 * @return	SUCCESS or ERROR
 */
Status Chip_SSP_Int_RWFrames16Bits(LPC_SSP_Type *pSSP, Chip_SSP_DATA_SETUP_Type *xf_setup);

/**
 * @brief   SSP Polling Read/Write in blocking mode
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	xf_setup		: Pointer to a SSP_DATA_SETUP_Type structure that contains specified
 * 							information about transmit/receive data	configuration
 * @return	Actual data length has been transferred
 *
 * This function can be used in both master and slave mode. It starts with writing phase and after that,
 * a reading phase is generated to read any data available in RX_FIFO. All needed information is prepared
 * through xf_setup param.
 */
uint32_t Chip_SSP_RWFrames_Blocking(LPC_SSP_Type *pSSP, Chip_SSP_DATA_SETUP_Type *xf_setup);

/**
 * @brief   SSP Polling Write in blocking mode
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	buffer			: Buffer address
 * @param	buffer_len		: Buffer length
 * @return	Actual data length has been transferred
 *
 * This function can be used in both master and slave mode. First, a writing operation will send
 * the needed data. After that, a dummy reading operation is generated to clear data buffer
 */
uint32_t Chip_SSP_WriteFrames_Blocking(LPC_SSP_Type *pSSP, uint8_t *buffer, uint32_t buffer_len);

/**
 * @brief   Note here
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	buffer			: Buffer address
 * @param	buffer_len		: The length of buffer
 * @return	Actual data length has been transferred
 *
 * This function can be used in both master and slave mode. First, a dummy writing operation is generated
 * to clear data buffer. After that, a reading operation will receive the needed data
 */
uint32_t Chip_SSP_ReadFrames_Blocking(LPC_SSP_Type *pSSP, uint8_t *buffer, uint32_t buffer_len);

/**
 * @brief   Initialize the SSP
 * @param	pSSP			: The base SSP peripheral on the chip
 * @return	Nothing
 */
void Chip_SSP_Init(LPC_SSP_Type *pSSP);

/**
 * @brief   Set the SSP operating modes, master or slave
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	master			: 1 to set master, 0 to set slave
 * @return	Nothing
 */
void Chip_SSP_Set_Master(LPC_SSP_Type *pSSP, bool master);

/**
 * @brief   Set the clock frequency for SSP interface
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	bit_rate		: The SSP bit rate
 * @return	Nothing
 */
void Chip_SSP_Set_BitRate(LPC_SSP_Type *pSSP, uint32_t bit_rate);

/**
 * @brief   Set up the SSP frame format
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	format			: Structure used to format frame
 * @return	Nothing
 */
void Chip_SSP_Set_Format(LPC_SSP_Type *pSSP, SSP_ConfigFormat *format);

/**
 * @brief   Enable/Disable SSP interrupt
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	NewState		: ENABLE or DISABLE interrupt
 * @return	Nothing
 */
void Chip_SSP_Int_Cmd(LPC_SSP_Type *pSSP, FunctionalState NewState);

/**
 * @brief   Enable/Disable DMA
 * @param	pSSP			: The base SSP peripheral on the chip
 * @param	NewState		: ENABLE or DISABLE DMA
 * @return	Nothing
 */
void Chip_SSP_DMA_Cmd(LPC_SSP_Type *pSSP, FunctionalState NewState);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SSP_18XX_43XX_H_ */
