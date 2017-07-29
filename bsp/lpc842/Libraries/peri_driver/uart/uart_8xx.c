/*
 * @brief LPC8xx UART driver
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

#include "chip.h"
#include "uart_8xx.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Return UART clock ID from the UART register address */
static CHIP_SYSCTL_CLOCK_T getUARTClockID(LPC_USART_T *pUART)
{
	if (pUART == LPC_USART0) {
		return SYSCTL_CLOCK_UART0;
	}
	else if (pUART == LPC_USART1) {
		return SYSCTL_CLOCK_UART1;
	}

	return SYSCTL_CLOCK_UART2;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize the UART peripheral */
void Chip_UART_Init(LPC_USART_T *pUART)
{
	/* Enable USART clock */
	Chip_Clock_EnablePeriphClock(getUARTClockID(pUART));

	/* UART reset */
	if (pUART == LPC_USART0) {
		/* Peripheral reset control to USART0 */
		Chip_SYSCTL_PeriphReset(RESET_USART0);
	}
	else if (pUART == LPC_USART1) {
		/* Peripheral reset control to USART1 */
		Chip_SYSCTL_PeriphReset(RESET_USART1);
	}
	else {
		/* Peripheral reset control to USART2 */
		Chip_SYSCTL_PeriphReset(RESET_USART2);
	}
}

/* Initialize the UART peripheral */
void Chip_UART_DeInit(LPC_USART_T *pUART)
{
	/* Disable USART clock */
	Chip_Clock_DisablePeriphClock(getUARTClockID(pUART));
}

/* Transmit a byte array through the UART peripheral (non-blocking) */
int Chip_UART_Send(LPC_USART_T *pUART, const void *data, int numBytes)
{
	int sent = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((sent < numBytes) &&
		   ((Chip_UART_GetStatus(pUART) & UART_STAT_TXRDY) != 0)) {
		Chip_UART_SendByte(pUART, *p8);
		p8++;
		sent++;
	}

	return sent;
}

/* Transmit a byte array through the UART peripheral (blocking) */
int Chip_UART_SendBlocking(LPC_USART_T *pUART, const void *data, int numBytes)
{
	int pass, sent = 0;
	uint8_t *p8 = (uint8_t *) data;

	while (numBytes > 0) {
		pass = Chip_UART_Send(pUART, p8, numBytes);
		numBytes -= pass;
		sent += pass;
		p8 += pass;
	}

	return sent;
}

/* Read data through the UART peripheral (non-blocking) */
int Chip_UART_Read(LPC_USART_T *pUART, void *data, int numBytes)
{
	int readBytes = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((readBytes < numBytes) &&
		   ((Chip_UART_GetStatus(pUART) & UART_STAT_RXRDY) != 0)) {
		*p8 = Chip_UART_ReadByte(pUART);
		p8++;
		readBytes++;
	}

	return readBytes;
}

/* Read data through the UART peripheral (blocking) */
int Chip_UART_ReadBlocking(LPC_USART_T *pUART, void *data, int numBytes)
{
	int pass, readBytes = 0;
	uint8_t *p8 = (uint8_t *) data;

	while (numBytes > 0) {
		pass = Chip_UART_Read(pUART, p8, numBytes);
		numBytes -= pass;
		readBytes += pass;
		p8 += pass;
	}

	return readBytes;
}

/* Set baud rate for UART */
void Chip_UART_SetBaud(LPC_USART_T *pUART, uint32_t baudrate)
{
	uint32_t baudRateGenerator;
	baudRateGenerator = Chip_Clock_GetUSARTNBaseClockRate() / (16 * baudrate);
	pUART->BRG = baudRateGenerator - 1;	/* baud rate */
}

/* UART receive-only interrupt handler for ring buffers */
void Chip_UART_RXIntHandlerRB(LPC_USART_T *pUART, RINGBUFF_T *pRB)
{
	/* New data will be ignored if data not popped in time */
	while ((Chip_UART_GetStatus(pUART) & UART_STAT_RXRDY) != 0) {
		uint8_t ch = Chip_UART_ReadByte(pUART);
		RingBuf_Write(pRB, &ch, 1);
	}
}

/* UART transmit-only interrupt handler for ring buffers */
void Chip_UART_TXIntHandlerRB(LPC_USART_T *pUART, RINGBUFF_T *pRB)
{
	uint8_t ch;

	/* Fill FIFO until full or until TX ring buffer is empty */
	while (((Chip_UART_GetStatus(pUART) & UART_STAT_TXRDY) != 0) &&
		   RingBuf_Read(pRB, &ch, 1)) {
		Chip_UART_SendByte(pUART, ch);
	}
}

/* Populate a transmit ring buffer and start UART transmit */
uint32_t Chip_UART_SendRB(LPC_USART_T *pUART, RINGBUFF_T *pRB, const void *data, int count)
{
	uint32_t ret;
	uint8_t *p8 = (uint8_t *) data;

	/* Don't let UART transmit ring buffer change in the UART IRQ handler */
	Chip_UART_IntDisable(pUART, UART_INTEN_TXRDY);

	/* Move as much data as possible into transmit ring buffer */
	ret = RingBuf_Write(pRB, p8, count);
	Chip_UART_TXIntHandlerRB(pUART, pRB);

	/* Add additional data to transmit ring buffer if possible */
	ret += RingBuf_Write(pRB, (p8 + ret), (count - ret));

	/* Enable UART transmit interrupt */
	Chip_UART_IntEnable(pUART, UART_INTEN_TXRDY);

	return ret;
}

/* Copy data from a receive ring buffer */
int Chip_UART_ReadRB(LPC_USART_T *pUART, RINGBUFF_T *pRB, void *data, int bytes)
{
	(void) pUART;

	return RingBuf_Read(pRB, (uint8_t *) data, bytes);
}

/* UART receive/transmit interrupt handler for ring buffers */
void Chip_UART_IRQRBHandler(LPC_USART_T *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB)
{
	/* Handle transmit interrupt if enabled */
	if ((Chip_UART_GetStatus(pUART) & UART_STAT_TXRDY) != 0) {
		Chip_UART_TXIntHandlerRB(pUART, pTXRB);

		/* Disable transmit interrupt if the ring buffer is empty */
		if (RingBuf_GetFreeBytes(pTXRB) == 0) {
			Chip_UART_IntDisable(pUART, UART_INTEN_TXRDY);
		}
	}

	/* Handle receive interrupt */
	Chip_UART_RXIntHandlerRB(pUART, pRXRB);
}
