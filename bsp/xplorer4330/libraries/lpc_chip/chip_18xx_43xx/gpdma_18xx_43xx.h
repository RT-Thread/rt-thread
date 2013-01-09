/*
 * @brief LPC18xx/43xx DMA driver
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
 * intellectual property rights. NXP Semiconductors assumes no responsibility
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

#ifndef __GPDMA_18XX_43XX_H_
#define __GPDMA_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup GPDMA_18XX_43XX CHIP: LPC18xx/43xx General Purpose DMA driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/** Number of channels on GPDMA */
#define GPDMA_NUMBER_CHANNELS 8

/** DMA Connection number definitions */
#define GPDMA_CONN_MEMORY           ((0UL))			/**< MEMORY             */
#define GPDMA_CONN_MAT0_0           ((1UL))			/**< MAT0.0             */
#define GPDMA_CONN_UART0_Tx         ((2UL))			/**< UART0 Tx           */
#define GPDMA_CONN_MAT0_1           ((3UL))			/**< MAT0.1             */
#define GPDMA_CONN_UART0_Rx         ((4UL))			/**< UART0 Rx           */
#define GPDMA_CONN_MAT1_0           ((5UL))			/**< MAT1.0             */
#define GPDMA_CONN_UART1_Tx         ((6UL))			/**< UART1 Tx           */
#define GPDMA_CONN_MAT1_1           ((7UL))			/**< MAT1.1             */
#define GPDMA_CONN_UART1_Rx         ((8UL))			/**< UART1 Rx           */
#define GPDMA_CONN_MAT2_0           ((9UL))			/**< MAT2.0             */
#define GPDMA_CONN_UART2_Tx         ((10UL))		/**< UART2 Tx           */
#define GPDMA_CONN_MAT2_1           ((11UL))		/**< MAT2.1             */
#define GPDMA_CONN_UART2_Rx         ((12UL))		/**< UART2 Rx           */
#define GPDMA_CONN_MAT3_0           ((13UL))		/**< MAT3.0             */
#define GPDMA_CONN_UART3_Tx         ((14UL))		/**< UART3 Tx           */
#define GPDMA_CONN_SCT_0            ((15UL))		/**< SCT timer channel 0*/
#define GPDMA_CONN_MAT3_1           ((16UL))		/**< MAT3.1             */
#define GPDMA_CONN_UART3_Rx         ((17UL))		/**< UART3 Rx           */
#define GPDMA_CONN_SCT_1            ((18UL))		/**< SCT timer channel 1*/
#define GPDMA_CONN_SSP0_Rx          ((19UL))		/**< SSP0 Rx            */
#define GPDMA_CONN_I2S_Tx_Channel_0 ((20UL))		/**< I2S channel 0      */
#define GPDMA_CONN_SSP0_Tx          ((21UL))		/**< SSP0 Tx            */
#define GPDMA_CONN_I2S_Rx_Channel_1 ((22UL))		/**< I2S channel 1      */
#define GPDMA_CONN_SSP1_Rx          ((23UL))		/**< SSP1 Rx            */
#define GPDMA_CONN_SSP1_Tx          ((24UL))		/**< SSP1 Tx            */
#define GPDMA_CONN_ADC_0            ((25UL))		/**< ADC 0              */
#define GPDMA_CONN_ADC_1            ((26UL))		/**< ADC 1              */
#define GPDMA_CONN_DAC              ((27UL))		/**< DAC                */
#define GPDMA_CONN_I2S_Tx_Channel_1 ((28UL))		/**< I2S channel 0      */
#define GPDMA_CONN_I2S_Rx_Channel_0 ((29UL))		/**< I2S channel 0      */

/** Burst size in Source and Destination definitions */
#define GPDMA_BSIZE_1   ((0UL))	/**< Burst size = 1 */
#define GPDMA_BSIZE_4   ((1UL))	/**< Burst size = 4 */
#define GPDMA_BSIZE_8   ((2UL))	/**< Burst size = 8 */
#define GPDMA_BSIZE_16  ((3UL))	/**< Burst size = 16 */
#define GPDMA_BSIZE_32  ((4UL))	/**< Burst size = 32 */
#define GPDMA_BSIZE_64  ((5UL))	/**< Burst size = 64 */
#define GPDMA_BSIZE_128 ((6UL))	/**< Burst size = 128 */
#define GPDMA_BSIZE_256 ((7UL))	/**< Burst size = 256 */

/** Width in Source transfer width and Destination transfer width definitions */
#define GPDMA_WIDTH_BYTE        ((0UL))	/**< Width = 1 byte */
#define GPDMA_WIDTH_HALFWORD    ((1UL))	/**< Width = 2 bytes */
#define GPDMA_WIDTH_WORD        ((2UL))	/**< Width = 4 bytes */

/** Flow control definitions */
#define DMA_CONTROLLER 0		/**< Flow control is DMA controller*/
#define SRC_PER_CONTROLLER 1	/**< Flow control is Source peripheral controller*/
#define DST_PER_CONTROLLER 2	/**< Flow control is Destination peripheral controller*/

typedef struct {
	FunctionalState ChannelStatus;
} DMA_ChannelHandle_t;

#define Chip_GPDMA_IntGetStatus(type, channel) IP_GPDMA_IntGetStatus(LPC_GPDMA, type, channel)

#define Chip_GPDMA_ClearIntPending(type, channel) IP_GPDMA_ClearIntPending(LPC_GPDMA, type, channel)

#define Chip_GPDMA_ChannelCmd(channelNum, NewState) IP_GPDMA_ChannelCmd(LPC_GPDMA, channelNum, NewState)

/**
 * @brief	Initialize the GPDMA
 * @return	Nothing
 */
void Chip_GPDMA_Init(void);

/**
 * @brief	Stop a stream DMA transfer
 * @param	ChannelNum	:	Channel Number to be closed
 * @return	Nothing
 */
void Chip_DMA_Stop(uint8_t ChannelNum);

/**
 * @brief	The GPDMA stream interrupt status checking
 * @param	ChannelNum		:	Channel Number to be checked on interruption
 * @return	Status:
 *              - SUCCESS	: DMA transfer success
 *              - ERROR		: DMA transfer failed
 */
Status  Chip_DMA_Interrupt(uint8_t ChannelNum);

/**
 * @brief	Get a free GPDMA channel for one DMA connection
 * @param	PeripheralConnection_ID		:	Some chip fix each peripheral DMA connection on a specified channel ( have not used in 18xx/43xx )
 * @return	The channel number which is selected
 */
uint8_t Chip_DMA_GetFreeChannel(uint32_t PeripheralConnection_ID);

/**
 * @brief	Do a DMA transfer M2M, M2P,P2M or P2P
 * @param	ChannelNum		:	Channel used for transfer
 * @param	src				:	Address of Memory or PeripheralConnection_ID which is the source
 * @param	dst				:	Address of Memory or PeripheralConnection_ID which is the destination
 * @param	TransferType	:	Select the transfer controller and the type of transfer. Should be:
 *                               - GPDMA_TRANSFERTYPE_M2M_CONTROLLER_DMA
 *                               - GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA
 *                               - GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA
 *                               - GPDMA_TRANSFERTYPE_P2P_CONTROLLER_DMA
 *                               - GPDMA_TRANSFERTYPE_P2P_CONTROLLER_DestPERIPHERAL
 *                               - GPDMA_TRANSFERTYPE_M2P_CONTROLLER_PERIPHERAL
 *                               - GPDMA_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL
 *                               - GPDMA_TRANSFERTYPE_P2P_CONTROLLER_SrcPERIPHERAL
 * @param	Size			:	The number of DMA transfers
 * @return	Nothing
 */
void Chip_DMA_Transfer(uint8_t ChannelNum, uint32_t src, uint32_t dst, FlowControlType TransferType, uint32_t Size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPDMA_18XX_43XX_H_ */
