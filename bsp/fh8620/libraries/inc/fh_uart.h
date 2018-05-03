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

#ifndef FH_UART_H_
#define FH_UART_H_

 /****************************************************************************
 * #include section
 *	add #include here if any
 ***************************************************************************/
#include "fh_def.h"

 /****************************************************************************
 * #define section
 *	add constant #define here if any
 ***************************************************************************/

#define UART_RBR RBRTHRDLL
#define UART_THR RBRTHRDLL
#define UART_DLL RBRTHRDLL

#define UART_DLH DLHIER
#define UART_IER DLHIER

#define UART_IIR IIRFCR
#define UART_FCR IIRFCR

/* LSR register bits */
#define UART_LSR_DR    (1 << 0)
#define UART_LSR_OE    (1 << 1)
#define UART_LSR_PE    (1 << 2)
#define UART_LSR_FE    (1 << 3)
#define UART_LSR_BI    (1 << 4)
#define UART_LSR_THER  (1 << 5)
#define UART_LST_TEMT  (1 << 6)
#define UART_LSR_RFE   (1 << 7)

/* LCR register bits */
#define UART_LCR_DLS5   0x00
#define UART_LCR_DLS6   0x01
#define UART_LCR_DLS7   0x02
#define UART_LCR_DLS8   0x03
#define UART_LCR_STOP1  0
#define UART_LCR_STOP2  (1 << 2)
#define UART_LCR_PEN    (1 << 3)
#define UART_LCR_EVEN   (1 << 4)
#define UART_LCR_SP     (1 << 5)
#define UART_LCR_BC     (1 << 6)
#define UART_LCR_DLAB   (1 << 7)

/* MCR register bits */
#define UART_MCR_DTR    (1 << 0)
#define UART_MCR_RTS    (1 << 1)
#define UART_MCR_OUT1   (1 << 2)
#define UART_MCR_OUT2   (1 << 3)
#define UART_MCR_LB     (1 << 4)
#define UART_MCR_AFCE   (1 << 5)
#define UART_MCR_SIRE   (1 << 6)

/* FCR register bits */
#define UART_FCR_FIFOE  (1 << 0)
#define UART_FCR_RFIFOR (1 << 1)
#define UART_FCR_XFIFOR (1 << 2)
#define UART_FCR_DMAM   (1 << 3)
#define UART_FCR_TET_EMPTY (0x00 << 4)
#define UART_FCR_TET_TWO   (0x01 << 4)
#define UART_FCR_TET_1_4   (0x02 << 4)
#define UART_FCR_TET_1_2   (0x03 << 4)
#define UART_FCR_RT_ONE    (0x00 << 6)
#define UART_FCR_RT_1_4    (0x01 << 6)
#define UART_FCR_RT_1_2    (0x02 << 6)
#define UART_FCR_RT_L2     (0x03 << 6)

/* IER register bits */
#define UART_IER_ERBFI   (1 << 0)
#define UART_IER_ETBEI   (1 << 1)
#define UART_IER_ELSI    (1 << 2)
#define UART_IER_EDSSI   (1 << 3)
#define UART_IER_PTIME   (1 << 7)

/* USR register bits */
#define UART_USR_BUSY    (1 << 0)
#define UART_USR_TFNF    (1 << 1)
#define UART_USR_TFE     (1 << 2)
#define UART_USR_RNFE    (1 << 3)
#define UART_USR_RFE     (1 << 4)

/* IIR register bits */
#define UART_IIR_RIID_MASK 0x0f
#define UART_IIR_MODEM    0x00
#define UART_IIR_NOINT    0x01
#define UART_IIR_THREMPTY 0x02
#define UART_IIR_RDATD    0x04
#define UART_IIR_RLINEST  0x06
#define UART_IIR_BUSY     0x07
#define UART_IIR_CHRTOUT  0x0c
#define UART_IIR_FIFOSE  (0x03 << 6)

//uart baudrate cofig
//#define 	UART_CLOCK_FREQ   	(27000000)   //27MHZ
//
//#define DIV(n)	(((UART_CLOCK_FREQ/(n))+8)/16)


 /****************************************************************************
 * ADT section
 *	add Abstract Data Type definition here
 ***************************************************************************/




typedef struct {
	RwReg RBRTHRDLL; /* UART_RBR, UART_THR, UART_DLL */
	RwReg DLHIER;    /* UART_DLH, UART_IER */
	RwReg IIRFCR;    /* UART_IIR, UART_FCR */
	RwReg UART_LCR; /*(0x000c) */
	RwReg UART_MCR; /*(0x0010) */
	RwReg UART_LSR; /*(0x0014) */
	RwReg UART_MSR; /*(0x0018) */
	RwReg UART_SCR; /*(0x001c) */
	RwReg reserved[20];
	RwReg UART_FAR; /* (0x0070) */
	RwReg UART_TFR; /* (0x0074) */
	RwReg UART_RFW; /* (0x0078) */
	RwReg UART_USR; /* (0x007c) */
	RwReg UART_TFL; /* (0x0080) */
	RwReg UART_RFL; /* (0x0084) */
	RwReg UART_SRR; /* (0x0088) */
	RwReg reserved1[3];
	RwReg UART_SFE;  /* (0x0098) */
	RwReg UART_SRT;  /* (0x009c) */
	RwReg UART_STET; /* (0x00a0) */
	RwReg UART_HTX;  /* (0x00a4) */
	RwReg UART_DMASA; /* (0x00a8) */
	RwReg reserved2[18];
	RwReg UART_CPR;  /* (0x00f4) */
	RwReg UART_UCV;  /* (0x00f8) */
	RwReg UART_CTR;  /* (0x00fc) */
}uart;



struct fh_uart {
	uart *uart_port;
	int irq;
};





enum data_bits {
	UART_DATA_BIT5 = 0,
	UART_DATA_BIT6 = 1,
	UART_DATA_BIT7 = 2,
	UART_DATA_BIT8 = 3
};

enum stop_bits {
	UART_STOP_BIT1   = 0,
	UART_STOP_BIT1_5 = 1,
	UART_STOP_BIT2   = 2
};

enum parity {
	UART_PARITY_NONE = 0,
	UART_PARITY_EVEN = 1,
	UART_PARITY_ODD  = 2,
	UART_PARITY_ST   = 3 /* Stick Parity */
};


#define 	UART_CLOCK_FREQ   	(30000000)   //30MHZ
typedef enum enum_uart_baudrate{
	BAUDRATE_9600 	= (((UART_CLOCK_FREQ/9600)+8)/16),
	BAUDRATE_19200 	= (((UART_CLOCK_FREQ/19200)+8)/16),
	BAUDRATE_38400  = (((UART_CLOCK_FREQ/38400)+8)/16),
	BAUDRATE_57600  = (((UART_CLOCK_FREQ/57600)+8)/16),
	BAUDRATE_115200 = (((UART_CLOCK_FREQ/115200)+8)/16),
	BAUDRATE_194000 = (((UART_CLOCK_FREQ/194000)+8)/16),
}uart_baudrate_e;

/****************************************************************************
*  extern variable declaration section
***************************************************************************/

extern int uart_init(uart *port);

extern UINT32 uart_get_status(uart *port);

extern void uart_configure(uart *port, enum data_bits data_bit,
					enum stop_bits stop_bit, enum parity parity,
					UINT32 buard_rate, UINT32 uart_clk);


extern int uart_enable_irq(uart *port, UINT32 mode);

extern int uart_disable_irq(uart *port, UINT32 mode);

extern UINT32 uart_get_iir_status(uart *port);

extern UINT32 uart_get_line_status(uart *port);

extern UINT32 uart_is_rx_ready(uart *port);

extern UINT8 uart_getc(uart *port);

extern void uart_putc(uart *port, UINT8 c);

extern void uart_set_fifo_mode(uart *port, UINT32 fifo_mode);

/****************************************************************************
*  section
*	add function prototype here if any
***************************************************************************/




#endif /* #ifndef _TIMER_ */

