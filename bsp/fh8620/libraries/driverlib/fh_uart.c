/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
#include "inc/fh_driverlib.h"
/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/

/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/

/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/

/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/


/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/




 /* function body */


/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/


int uart_init(uart *port)
{
	port->UART_IER = 0;
	port->UART_LCR = 0;
	//port->UART_DLL = 0;
	//port->UART_DLH = 0;
}

UINT32 uart_get_status(uart *port)
{
	return port->UART_USR;
}


void uart_configure(uart *port, enum data_bits data_bit,
					enum stop_bits stop_bit, enum parity parity,
					UINT32 buard_rate, UINT32 uart_clk)
{
	UINT32 divisor;
	UINT32 freq;
	UINT32 baud_div;
	UINT32 lcr_reg = 0;
	UINT32 ret;

	/*divisor = DIV(buard_rate);
	port->UART_LCR |= UART_LCR_DLAB;
	port->UART_DLL = divisor & 0xFF;
	port->UART_DLH = (divisor >> 8) & 0xFF;
	port->UART_LCR &= ~UART_LCR_DLAB;*/

    do{
        //clear fifo...
        port->UART_FCR = UART_FCR_RFIFOR | UART_FCR_XFIFOR;
        //read status..
        ret = uart_get_status(port);
    }while(ret & UART_USR_BUSY);
	switch (data_bit) {
		case UART_DATA_BIT5:
			lcr_reg |= UART_LCR_DLS5;
			break;
		case UART_DATA_BIT6:
			lcr_reg |= UART_LCR_DLS6;
			break;
		case UART_DATA_BIT7:
			lcr_reg |= UART_LCR_DLS7;
			break;
		case UART_DATA_BIT8:
			lcr_reg |= UART_LCR_DLS8;
			break;
		default:
			lcr_reg |= UART_LCR_DLS8;
			break;
	}

	switch (stop_bit) {
		case UART_STOP_BIT1:
			lcr_reg |= UART_LCR_STOP1;
			break;
		case UART_STOP_BIT2:
			lcr_reg |= UART_LCR_STOP2;
			break;
		default:
			lcr_reg |= UART_LCR_STOP1;
			break;
	}

	switch (parity) {
		case UART_PARITY_EVEN:
			lcr_reg |= UART_LCR_EVEN | UART_LCR_PEN;
			break;
		case UART_PARITY_ODD:
			lcr_reg |= UART_LCR_PEN;
			break;
		case UART_PARITY_ST:
			lcr_reg |= UART_LCR_SP;
			break;
		case UART_PARITY_NONE:
		default:
			break;
	}



	switch (buard_rate) {
		case 115200:
			baud_div =  BAUDRATE_115200;
			break;
		case 57600:
			baud_div =  BAUDRATE_57600;
			break;
		case 38400:
			baud_div =  BAUDRATE_38400;
			break;
		case 19200:
			baud_div =  BAUDRATE_19200;
			break;
		case 9600:
			baud_div =  BAUDRATE_9600;
			break;
		default:
			baud_div = BAUDRATE_115200;
			break;
	}

	//clear fifo
	port->UART_FCR = UART_FCR_RFIFOR | UART_FCR_XFIFOR;

	//div
	ret = port->UART_LCR;
	ret |= UART_LCR_DLAB;
	port->UART_LCR = ret;
	port->RBRTHRDLL = baud_div & 0x00ff;
	port->DLHIER = (baud_div & 0x00ff)>>8;
	/* clear DLAB */
	ret = ret & 0x7f;
	port->UART_LCR = ret;

	//line control
	port->UART_LCR = lcr_reg;
	//fifo control
	port->UART_FCR = UART_FCR_FIFOE | UART_FCR_RFIFOR | UART_FCR_XFIFOR | UART_FCR_TET_1_4 | UART_FCR_RT_ONE;

}


int uart_enable_irq(uart *port, UINT32 mode)
{
	unsigned int ret;
	ret = port->UART_IER;
	ret |= mode;
	port->UART_IER = ret;
}

int uart_disable_irq(uart *port, UINT32 mode)
{
	unsigned int ret;
	ret = port->UART_IER;
	ret &= ~mode;

	port->UART_IER = ret;
}

UINT32 uart_get_iir_status(uart *port)
{
	return port->UART_IIR;
}

UINT32 uart_get_line_status(uart *port)
{
	return port->UART_LSR;
}

UINT32 uart_is_rx_ready(uart *port)
{
	return port->UART_LSR & UART_LSR_DR;
}

UINT8 uart_getc(uart *port)
{
	return port->UART_RBR & 0xFF;
}

void uart_putc(uart *port, UINT8 c)
{
	//while(!(port->UART_USR & UART_USR_TFNF));
	port->UART_THR = c;
}

void uart_set_fifo_mode(uart *port, UINT32 fifo_mode)
{
	port->UART_FCR = fifo_mode;
}



























