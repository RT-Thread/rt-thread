/*
 * File      : portserial.c
 * This file is part of freemodbus in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-04     yi.qiu      first version
 */
 
#include <rtthread.h>

#include "port.h"
#include "serial.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#define UART1	((struct uartport *)&U1BASE)

/* ----------------------- static functions ---------------------------------*/
static void rt_serial1_handler(int vector);
static void prvvUARTTxReadyISR(void);
static void prvvUARTRxISR(void);
extern rt_uint32_t PCLK;

/* ----------------------- Start implementation -----------------------------*/
void vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
	if( xRxEnable )
	{
		INTSUBMSK  &= ~(BIT_SUB_RXD1);
	}
	else
	{
		INTSUBMSK |= (BIT_SUB_RXD1);
	}
	if( xTxEnable )
	{
		INTSUBMSK &= ~(BIT_SUB_TXD1);
		prvvUARTTxReadyISR();
	}
	else
	{
		INTSUBMSK |= (BIT_SUB_TXD1);
	}
}

void vMBPortClose( void )
{
	/* null */
}

BOOL xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
   	int i;

	/* FIFO enable, Tx/Rx FIFO clear */
	UART1->ufcon = 0x0;
	/* disable the flow control */
	UART1->umcon = 0x0;
	/* Normal,No parity,1 stop,8 bit */
	UART1->ulcon = 0x3;
	/*
	 * tx=level,rx=edge,disable timeout int.,enable rx error int.
	 * normal,interrupt or polling
	 */
	UART1->ucon = 0x245;
	/* Set uart0 bps */
	UART1->ubrd = (rt_int32_t)(PCLK / (ulBaudRate * 16)) - 1;
	
	for (i = 0; i < 100; i++);

	SUBSRCPND |= BIT_SUB_RXD1;
	SUBSRCPND |= BIT_SUB_TXD1;

	rt_hw_interrupt_install(INTUART1, rt_serial1_handler, RT_NULL);
	rt_hw_interrupt_umask(INTUART1);

	return TRUE;
}

BOOL xMBPortSerialPutByte( CHAR ucByte )
{
	/* wait for room in the transmit FIFO */
	while(!(USTAT1 & USTAT_TXB_EMPTY));

	UTXH1 = (UCHAR)ucByte;
	
	return TRUE;
}

BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
	while (!(USTAT1 & USTAT_RCV_READY));

	*pucByte = URXH1;
	
	return TRUE;
}

static void rt_serial1_handler(int vector)
{	
	if (SUBSRCPND & BIT_SUB_RXD1)
	{			
		SUBSRCPND |= BIT_SUB_RXD1;
		prvvUARTRxISR();
	}	
	else if (SUBSRCPND & BIT_SUB_TXD1)
	{
		SUBSRCPND |= BIT_SUB_TXD1;	
		prvvUARTTxReadyISR();
	}		
}

/* 
 * Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
static void prvvUARTTxReadyISR( void )
{
	pxMBFrameCBTransmitterEmpty(  );
}

/* 
 * Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
	pxMBFrameCBByteReceived(  );
}
