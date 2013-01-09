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

#include "uart_18xx_43xx.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/** UART Ring buffer declaration*/
static UART_RingBuffer_Type rb;

/** Current Tx Interrupt enable state */
static __IO FlagStatus TxIntStat;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Get UART number based on selected UART */
static UART_ID_Type Chip_UART_Get_UARTNum(LPC_USART_Type *UARTx)
{
	if (UARTx == LPC_USART0) {
		return UART_0;
	}
	else if (UARTx == LPC_UART1) {
		return UART_1;
	}
	else if (UARTx == LPC_USART2) {
		return UART_2;
	}

	return UART_3;
}

/* Determine UART clock based in selected UART */
static CCU_CLK_T Chip_UART_DetermineClk(LPC_USART_Type *UARTx) {
	CCU_CLK_T uartclk;

	/* Pick clock for uart BASED ON SELECTED uart */
	if (UARTx == LPC_UART1) {
		uartclk = CLK_MX_UART1;
	}
	if (UARTx == LPC_USART2) {
		uartclk = CLK_MX_UART2;
	}
	if (UARTx == LPC_USART3) {
		uartclk = CLK_MX_UART3;
	}
	else {
		uartclk = CLK_MX_UART0;
	}

	return uartclk;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes the UARTx peripheral */
void Chip_UART_Init(LPC_USART_Type *UARTx)
{
	UART_ID_Type UARTPort = Chip_UART_Get_UARTNum(UARTx);

	/* Enable UART clocking. UART base clock(s) must already be enabled */
	Chip_Clock_EnableOpts(Chip_UART_DetermineClk(UARTx), true, true, 1);

	IP_UART_Init(UARTx, UARTPort);
}

/* De-initializes the UARTx peripheral */
void Chip_UART_DeInit(LPC_USART_Type *UARTx)
{
	UART_ID_Type UARTPort = Chip_UART_Get_UARTNum(UARTx);

	IP_UART_DeInit(UARTx, UARTPort);

	/* Disable UART clocking */
	Chip_Clock_Disable(Chip_UART_DetermineClk(UARTx));
}

/* Determines best dividers to get a target baud rate */
Status Chip_UART_SetBaud(LPC_USART_Type *UARTx, uint32_t baudrate)
{
	uint32_t uClk;

	/* Get UART clock rate */
	uClk = Chip_Clock_GetRate(Chip_UART_DetermineClk(UARTx));

	return IP_UART_SetBaud(UARTx, baudrate, uClk);
}

/* Enable/Disable transmission on UART TxD pin */
void Chip_UART_TxCmd(LPC_USART_Type *UARTx, FunctionalState NewState)
{
	UART_ID_Type UARTPort = Chip_UART_Get_UARTNum(UARTx);

	IP_UART_TxCmd(UARTx, UARTPort, NewState);
}

/* Get Interrupt Stream Status */
UART_Int_Status Chip_UART_GetIntStatus(LPC_USART_Type *UARTx)
{
	uint32_t intsrc, tmp, tmp1;
	UART_Int_Status ret = UART_ERROR;

	/* Determine the interrupt source */
	intsrc = Chip_UART_IntGetStatus(UARTx);

	tmp = intsrc & UART_IIR_INTID_MASK;

	/* Receive Line Status */
	if (tmp == UART_IIR_INTID_RLS) {
		/* Check line status */
		tmp1 = (uint32_t) Chip_UART_GetLineStatus(UARTx);
		/* Mask out the Receive Ready and Transmit Holding empty status */
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				 | UART_LSR_BI | UART_LSR_RXFE);
		/* If any error exist */
		if (tmp1) {
			return UART_ERROR;
		}
	}

	/* Receive Data Available or Character time-out */
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)) {
		ret |= READY_TO_RECEIVE;
	}

	/* Transmit Holding Empty */
	if (tmp == UART_IIR_INTID_THRE) {
		ret |= READY_TO_SEND;
	}
	return ret;
}

/* UART interrupt service routine */
void Chip_UART_Interrupt_Handler(LPC_USART_Type *UARTx)
{
	uint8_t tmpc;
	uint32_t rLen;
	UART_Int_Status Sts = Chip_UART_GetIntStatus(UARTx);
	if (Sts == UART_ERROR) {
		return;	/* error */

	}
	if (Sts & READY_TO_RECEIVE) {	/* ready for Read Data */
		while (1) {
			/* Call UART read function in UART driver */
			rLen = Chip_UART_Receive(UARTx, &tmpc, 1, NONE_BLOCKING);
			/* If data received */
			if (rLen) {
				/* Check if buffer is more space
				 * If no more space, remaining character will be trimmed out
				 */
				if (!__BUF_IS_FULL(rb.rx_head, rb.rx_tail)) {
					rb.rx[rb.rx_head] = tmpc;
					__BUF_INCR(rb.rx_head);
				}
			}
			/* no more data */
			else {
				break;
			}
		}
	}

	if (Sts & READY_TO_SEND) {	/* ready for Write Data */
		/* Disable THRE interrupt */
		Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, DISABLE);

		/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
		 * of data or break whenever ring buffers are empty */
		/* Wait until THR empty */
		while (Chip_UART_CheckBusy(UARTx) == SET) ;

		while (!__BUF_IS_EMPTY(rb.tx_head, rb.tx_tail)) {
			/* Move a piece of data into the transmit FIFO */
			if (Chip_UART_Send(UARTx, (uint8_t *) &rb.tx[rb.tx_tail], 1, NONE_BLOCKING)) {
				/* Update transmit ring FIFO tail pointer */
				__BUF_INCR(rb.tx_tail);
			}
			else {
				break;
			}
		}

		/* If there is no more data to send, disable the transmit
		   interrupt - else enable it or keep it enabled */
		if (__BUF_IS_EMPTY(rb.tx_head, rb.tx_tail)) {
			Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, DISABLE);
			// Reset Tx Interrupt state
			TxIntStat = RESET;
		}
		else {
			/* Set Tx Interrupt state */
			TxIntStat = SET;
			Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, ENABLE);
		}
	}
}

/* UART transmit function for interrupt mode (using ring buffers) */
uint32_t Chip_UART_Interrupt_Transmit(LPC_USART_Type *UARTx, uint8_t *txbuf, uint8_t buflen)
{
	uint8_t *data = (uint8_t *) txbuf;
	uint32_t bytes = 0;

	/* Temporarily lock out UART transmit interrupts during this
	   read so the UART transmit interrupt won't cause problems
	   with the index values */
	Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, DISABLE);

	/* Loop until transmit run buffer is full or until n_bytes
	   expires */
	while ((buflen > 0) && (!__BUF_IS_FULL(rb.tx_head, rb.tx_tail))) {
		/* Write data from buffer into ring buffer */
		rb.tx[rb.tx_head] = *data;
		data++;

		/* Increment head pointer */
		__BUF_INCR(rb.tx_head);

		/* Increment data count and decrement buffer size count */
		bytes++;
		buflen--;
	}

	/*
	 * Check if current Tx interrupt enable is reset,
	 * that means the Tx interrupt must be re-enabled
	 * due to call UART_IntTransmit() function to trigger
	 * this interrupt type
	 */
	if (TxIntStat == RESET) {
		// Disable THRE interrupt
		Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, DISABLE);

		/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
		 * of data or break whenever ring buffers are empty */
		/* Wait until THR empty */
		while (Chip_UART_CheckBusy(UARTx) == SET) ;

		while (!__BUF_IS_EMPTY(rb.tx_head, rb.tx_tail)) {
			/* Move a piece of data into the transmit FIFO */
			if (Chip_UART_Send(UARTx, (uint8_t *) &rb.tx[rb.tx_tail], 1, NONE_BLOCKING)) {
				/* Update transmit ring FIFO tail pointer */
				__BUF_INCR(rb.tx_tail);
			}
			else {
				break;
			}
		}

		/* If there is no more data to send, disable the transmit
		   interrupt - else enable it or keep it enabled */
		if (__BUF_IS_EMPTY(rb.tx_head, rb.tx_tail)) {
			Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, DISABLE);
			/* Reset Tx Interrupt state */
			TxIntStat = RESET;
		}
		else {
			/* Set Tx Interrupt state */
			TxIntStat = SET;
			Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, ENABLE);
		}
	}
	/*
	 * Otherwise, re-enables Tx Interrupt
	 */
	else {
		Chip_UART_IntConfig(UARTx, UART_INTCFG_THRE, ENABLE);
	}

	return bytes;
}

/* UART read function for interrupt mode (using ring buffers) */
uint32_t Chip_UART_Interrupt_Receive(LPC_USART_Type *UARTx, uint8_t *rxbuf, uint8_t buflen)
{
	uint8_t *data = (uint8_t *) rxbuf;
	uint32_t bytes = 0;

	/* Temporarily lock out UART receive interrupts during this
	   read so the UART receive interrupt won't cause problems
	   with the index values */
	Chip_UART_IntConfig(UARTx, UART_INTCFG_RBR, DISABLE);

	/* Loop until receive buffer ring is empty or
	    until max_bytes expires */
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb.rx_head, rb.rx_tail)))) {
		/* Read data from ring buffer into user buffer */
		*data = rb.rx[rb.rx_tail];
		data++;

		/* Update tail pointer */
		__BUF_INCR(rb.rx_tail);

		/* Increment data count and decrement buffer size count */
		bytes++;
		buflen--;
	}

	/* Re-enable UART interrupts */
	Chip_UART_IntConfig(UARTx, UART_INTCFG_RBR, ENABLE);

	return bytes;
}

/* Reset Tx and Rx ring buffer (head and tail) */
void Chip_UART_InitRingBuffer(void)
{
	TxIntStat = RESET;

	/* Reset ring buf head and tail idx */
	__BUF_RESET(rb.rx_head);
	__BUF_RESET(rb.rx_tail);
	__BUF_RESET(rb.tx_head);
	__BUF_RESET(rb.tx_tail);
}
