/*
 * @brief UART ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef  _HW_UART_H
#define  _HW_UART_H

#define UART_DRIVER_VERSION   0x0100

/*******************
 * INCLUDE FILES    *
 ********************/
#include <stdint.h>

/* UART Status Register bits */
#define UART_RXRDY           (1 << 0)	/* Receive data ready */
#define UART_RXIDLE          (1 << 1)	/* Receiver Idle */
#define UART_TXRDY           (1 << 2)	/* Transmitter ready */
#define UART_TXIDLE          (1 << 3)	/* Transmitter Idle */
#define UART_RXDERR          (0xF100)	/* overrun err, frame err, parity err, RxNoise err */
#define UART_TXDERR          (0x0200)	/* underrun err */
#define UART_START           (0x1000)

/* UART Interrupt register bits */
#define UART_INT_RXRDY          (1 << 0)
#define UART_INT_TXRDY          (1 << 2)
#define UART_INT_TXIDLE         (1 << 3)
#define UART_INT_CTS            (1 << 5)
#define UART_INT_TXDIS          (1 << 6)
#define UART_INT_OVR            (1 << 8)
#define UART_INT_BREAK          (1 << 11)
#define UART_INT_START          (1 << 12)
#define UART_INT_FRMERR         (1 << 13)
#define UART_INT_PARERR         (1 << 14)
#define UART_INT_RXNOISE        (1 << 15)
#define UART_INT_ABAUDERR       (1 << 16)

/* Configuration register bits */
#define UARTEN      1

#define UART_CTL_TXDIS          (1UL << 6)
#define UART_CTL_TXBRKEN        (1UL << 1)
#define UART_CTL_AUTOBAUD       (1UL << 16)
#define UART_CFG_RES            (2UL | (1UL << 10) | (1UL << 13) | (1UL << 17) | (0xFFUL << 24))
#define UART_CFG_ENABLE          1
#define UART_PAR_MASK           (3 << 4)
#define UART_DATA_MASK          (3 << 2)
#define UART_CTL_RES            (1UL | (7UL << 3) | (1UL << 7) | (0x3FUL << 10) | (0x7FFFUL << 17))
#define UART_IDLE_MASK          (1 << 3)
#define UART_STAT_CTS           (1 << 4)
#define UART_STAT_BREAK         (1 << 10)
#define UART_STAT_RXIDLE        (1 << 1)

/*******************
 * EXPORTED MACROS  *
 ********************/
#define     ECHO_EN             1
#define     ECHO_DIS            0

/*********************
 * EXPORTED TYPEDEFS  *
 **********************/

typedef struct {		/* UART registers Structure          */
	volatile uint32_t CFG;				/*!< Offset: 0x000 Configuration register  */
	volatile uint32_t CTL;				/*!< Offset: 0x004 Control register */
	volatile uint32_t STAT;				/*!< Offset: 0x008 Status register */
	volatile uint32_t INTENSET;			/*!< Offset: 0x00C Interrupt Enable Read and Set register */
	volatile uint32_t INTENCLR;			/*!< Offset: 0x010 Interrupt Enable Clear register */
	const volatile uint32_t RXDAT;		/*!< Offset: 0x014 Receiver Data register */
	const volatile uint32_t RXDATSTAT;	/*!< Offset: 0x018 Rx Data with status */
	volatile uint32_t TXDAT;			/*!< Offset: 0x01C Transmitter Data Register */
	volatile uint32_t BRG;				/*!< Offset: 0x020 Baud Rate Generator register */
	const volatile uint32_t INTSTAT;	/*!< Offset: 0x024 Interrupt Status register */
	volatile uint32_t OSR;				/*!< Offset: 0x028 Oversampling register */
	volatile uint32_t ADR;				/*!< Offset: 0x02C Address register (for automatic address matching) */
} UART_REGS_T;
typedef UART_REGS_T LPC_USART_T;

#endif /* _HW_UART_H */
