/*
 * @brief LPC18xx/43xx UART chip driver
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

#ifndef __UART_18XX_43XX_H_
#define __UART_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup 18XX_43XX CHIP: LPC18xx/43xx UART Driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Configure data width, parity mode and stop bits
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	Databits	: UART Data width, should be:
 *                          UART_DATABIT_5: UART 5 bit data mode
 *                          UART_DATABIT_6: UART 6 bit data mode
 *                          UART_DATABIT_7: UART 7 bit data mode
 *                          UART_DATABIT_8: UART 8 bit data mode
 * @param	Parity		: UART Parity mode, should be:
 *                          UART_PARITY_NONE: No parity
 *                          UART_PARITY_ODD:  Odd parity
 *                          UART_PARITY_EVEN: Even parity
 *                          UART_PARITY_SP_1: Forced "1" stick parity
 *                          UART_PARITY_SP_0: Forced "0" stick parity
 * @param	Stopbits	: Number of stop bits, should be:
 *                          UART_STOPBIT_1: One Stop Bit Select
 *                          UART_STOPBIT_2: Two Stop Bits Select
 * @return	Nothing
 */
STATIC INLINE void Chip_UART_ConfigData(LPC_USART_Type *UARTx,
										UART_DATABIT_Type Databits,
										UART_PARITY_Type Parity,
										UART_STOPBIT_Type Stopbits)
{
	IP_UART_ConfigData(UARTx, Databits, Parity, Stopbits);
}

/**
 * @brief	Send a block of data via UART peripheral
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	txbuf		: Pointer to Transmit buffer
 * @param	buflen		: Length of Transmit buffer
 * @param   flag		: Flag used in  UART transfer, should be NONE_BLOCKING or BLOCKING
 * @return	Number of bytes sent
 */
STATIC INLINE uint32_t Chip_UART_Send(LPC_USART_Type *UARTx, uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
	return IP_UART_Send(UARTx, txbuf, buflen, flag);
}

/**
 * @brief	Receive a block of data via UART peripheral
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	rxbuf		: Pointer to Received buffer
 * @param	buflen		: Length of Received buffer
 * @param   flag		: Flag mode, should be NONE_BLOCKING or BLOCKING
 * @return	Number of bytes received
 */
STATIC INLINE uint32_t Chip_UART_Receive(LPC_USART_Type *UARTx,
										 uint8_t *rxbuf,
										 uint32_t buflen,
										 TRANSFER_BLOCK_Type flag)
{
	return IP_UART_Receive(UARTx, rxbuf, buflen, flag);
}

/* UART FIFO functions ----------------------------------------------------------*/
/**
 * @brief	Configure FIFO function on selected UART peripheral
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	FIFOCfg		: Pointer to a UART_FIFO_CFG_Type Structure that contains specified information about FIFO configuration
 * @return	Nothing
 */
STATIC INLINE void Chip_UART_FIFOConfig(LPC_USART_Type *UARTx, UART_FIFO_CFG_Type *FIFOCfg)
{
	IP_UART_FIFOConfig(UARTx, FIFOCfg);
}

/**
 * @brief	Fills each UART_FIFOInitStruct member with its default value:
 *			- FIFO_DMAMode = DISABLE
 *			- FIFO_Level = UART_FIFO_TRGLEV0
 *			- FIFO_ResetRxBuf = ENABLE
 *			- FIFO_ResetTxBuf = ENABLE
 *			- FIFO_State = ENABLE
 * @param	UART_FIFOInitStruct	: Pointer to a UART_FIFO_CFG_Type structure which will be initialized.
 * @return	Nothing
 */
STATIC INLINE void Chip_UART_FIFOConfigStructInit(UART_FIFO_CFG_Type *UART_FIFOInitStruct)
{
	IP_UART_FIFOConfigStructInit(UART_FIFOInitStruct);
}

/* UART operate functions -------------------------------------------------------*/
/**
 * @brief	Enable or disable specified UART interrupt.
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	UARTIntCfg	: Specifies the interrupt flag, should be one of the following:
 *                  - UART_INTCFG_RBR   : RBR Interrupt enable
 *                  - UART_INTCFG_THRE  : THR Interrupt enable
 *                  - UART_INTCFG_RLS   : RX line status interrupt enable
 *                  - UART1_INTCFG_MS	: Modem status interrupt enable (UART1 only)
 *                  - UART1_INTCFG_CTS	: CTS1 signal transition interrupt enable (UART1 only)
 *                  - UART_INTCFG_ABEO  : Enables the end of auto-baud interrupt
 *                  - UART_INTCFG_ABTO  : Enables the auto-baud time-out interrupt
 * @param	NewState	: New state of specified UART interrupt type, should be ENALBE or DISALBE
 * @return	Nothing
 */
STATIC INLINE void Chip_UART_IntConfig(LPC_USART_Type *UARTx, UART_INT_Type UARTIntCfg, FunctionalState NewState)
{
	IP_UART_IntConfig(UARTx, UARTIntCfg, NewState);
}

/**
 * @brief	Get Source Interrupt
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Return the value of IIR register
 */
STATIC INLINE uint32_t Chip_UART_IntGetStatus(LPC_USART_Type *UARTx)
{
	return IP_UART_IntGetStatus(UARTx);
}

/**
 * @brief	Get current value of Line Status register in UART peripheral.
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Current value of Line Status register in UART peripheral
 */
STATIC INLINE uint8_t Chip_UART_GetLineStatus(LPC_USART_Type *UARTx)
{
	return IP_UART_GetLineStatus(UARTx);
}

/**
 * @brief	Check whether if UART is busy or not
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	RESET if UART is not busy, otherwise return SET.
 */
STATIC INLINE FlagStatus Chip_UART_CheckBusy(LPC_USART_Type *UARTx)
{
	return IP_UART_CheckBusy(UARTx);
}

/**
 * @brief	Force BREAK character on UART line, output pin UARTx TXD is forced to logic 0
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
STATIC INLINE void Chip_UART_ForceBreak(LPC_USART_Type *UARTx)
{
	IP_UART_ForceBreak(UARTx);
}

/**
 * @brief	Transmit a single data through UART peripheral
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	Data		: Data to transmit (must be 8-bit long)
 * @return	Status, should be ERROR (THR is empty, ready to send) or SUCCESS (THR is not empty)
 */
STATIC INLINE Status Chip_UART_SendByte(LPC_USART_Type *UARTx, uint8_t Data)
{
	return IP_UART_SendByte(UARTx, Data);
}

/**
 * @brief	Receive a single data from UART peripheral
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	*Data		: Pointer to Data to receive (must be 8-bit long)
 * @return	Status, should be ERROR or (Receive data is ready) or SUCCESS (Receive data is not ready yet)
 */
STATIC INLINE Status Chip_UART_ReceiveByte(LPC_USART_Type *UARTx, uint8_t *Data)
{
	return IP_UART_ReceiveByte(UARTx, Data);
}

/**
 * @brief	Initializes the UARTx peripheral.
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
void Chip_UART_Init(LPC_USART_Type *UARTx);

/**
 * @brief	De-initializes the UARTx peripheral.
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
void Chip_UART_DeInit(LPC_USART_Type *UARTx);

/**
 * @brief	Determines best dividers to get a target baud rate
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	baudrate	: Desired UART baud rate.
 * @return	Error status, could be SUCCESS or ERROR
 */
Status Chip_UART_SetBaud(LPC_USART_Type *UARTx, uint32_t baudrate);

/**
 * @brief	Enable/Disable transmission on UART TxD pin
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @param	NewState	: New State of Tx transmission function, should be ENABLE or DISABLE
 * @return Nothing
 */
void Chip_UART_TxCmd(LPC_USART_Type *UARTx, FunctionalState NewState);

/**
 * @brief	Get Interrupt Stream Status
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Return the interrupt status, should be:
 *              - UART_ERROR
 *              - READY_TO_RECEIVE
 *              - READY_TO_SEND
 */
UART_Int_Status Chip_UART_GetIntStatus(LPC_USART_Type *UARTx);

/**
 * @brief	Uart interrupt service routine (chip layer)
 * @param	UARTx		: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
void Chip_UART_Interrupt_Handler (LPC_USART_Type *UARTx);

/**
 * @brief	UART transmit function for interrupt mode (using ring buffers)
 * @param	UARTx	: Selected UART peripheral used to send data, should be UART0
 * @param	txbuf	: Pointer to Transmit buffer
 * @param	buflen	: Length of Transmit buffer
 * @return	Number of bytes actually sent to the ring buffer
 */
uint32_t Chip_UART_Interrupt_Transmit(LPC_USART_Type *UARTx, uint8_t *txbuf, uint8_t buflen);

/**
 * @brief	UART read function for interrupt mode (using ring buffers)
 * @param	UARTx	: Selected UART peripheral used to send data, should be UART0
 * @param	rxbuf	: Pointer to Received buffer
 * @param	buflen	: Length of Received buffer
 * @return	Number of bytes actually read from the ring buffer
 */
uint32_t Chip_UART_Interrupt_Receive(LPC_USART_Type *UARTx, uint8_t *rxbuf, uint8_t buflen);

/**
 * @brief	Reset Tx and Rx ring buffer (head and tail)
 * @return	Nothing
 */
void Chip_UART_InitRingBuffer(void);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif /* __UART_18XX_43XX_H_ */
