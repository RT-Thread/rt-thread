/*
 * @brief Usart Registers and control functions
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

#ifndef __USART_001_H_
#define __USART_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_USART_001 IP: USART register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief USART register block structure
 */
typedef struct {							/*!< USARTn Structure       */

	union {
		__IO uint32_t  DLL;					/*!< Divisor Latch LSB. Least significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider (DLAB = 1). */
		__O  uint32_t  THR;					/*!< Transmit Holding Register. The next character to be transmitted is written here (DLAB = 0). */
		__I  uint32_t  RBR;					/*!< Receiver Buffer Register. Contains the next received character to be read (DLAB = 0). */
	};

	union {
		__IO uint32_t IER;					/*!< Interrupt Enable Register. Contains individual interrupt enable bits for the 7 potential UART interrupts (DLAB = 0). */
		__IO uint32_t DLM;					/*!< Divisor Latch MSB. Most significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider (DLAB = 1). */
	};

	union {
		__O  uint32_t FCR;					/*!< FIFO Control Register. Controls UART FIFO usage and modes. */
		__I  uint32_t IIR;					/*!< Interrupt ID Register. Identifies which interrupt(s) are pending. */
	};

	__IO uint32_t LCR;						/*!< Line Control Register. Contains controls for frame formatting and break generation. */
	__IO uint32_t MCR;						/*!< Modem Control Register. Only present on USART ports with full modem support. */
	__I  uint32_t LSR;						/*!< Line Status Register. Contains flags for transmit and receive status, including line errors. */
	__I  uint32_t MSR;						/*!< Modem Status Register. Only present on USART ports with full modem support. */
	__IO uint32_t SCR;						/*!< Scratch Pad Register. Eight-bit temporary storage for software. */
	__IO uint32_t ACR;						/*!< Auto-baud Control Register. Contains controls for the auto-baud feature. */
	__IO uint32_t ICR;						/*!< IrDA control register (not all UARTS) */
	__IO uint32_t FDR;						/*!< Fractional Divider Register. Generates a clock input for the baud rate divider. */
	__IO uint32_t OSR;						/*!< Oversampling Register. Controls the degree of oversampling during each bit time. Only on some UARTS. */
	__IO uint32_t TER1;						/*!< Transmit Enable Register. Turns off USART transmitter for use with software flow control. */
	uint32_t  RESERVED0[3];
	__IO uint32_t HDEN;						/*!< Half-duplex enable Register- only on some UARTs */
	__I  uint32_t RESERVED1[1];
	__IO uint32_t SCICTRL;					/*!< Smart card interface control register- only on some UARTs */
	__IO uint32_t RS485CTRL;				/*!< RS-485/EIA-485 Control. Contains controls to configure various aspects of RS-485/EIA-485 modes. */
	__IO uint32_t RS485ADRMATCH;			/*!< RS-485/EIA-485 address match. Contains the address match value for RS-485/EIA-485 mode. */
	__IO uint32_t RS485DLY;					/*!< RS-485/EIA-485 direction control delay. */
	union {
		__IO uint32_t SYNCCTRL;				/*!< Synchronous mode control register. Only on USARTs. */
		__I  uint32_t FIFOLVL;				/*!< FIFO Level register. Provides the current fill levels of the transmit and receive FIFOs. */
	};

	__IO uint32_t TER2;						/*!< Transmit Enable Register. Only on LPC177X_8X UART4 and LPC18XX/43XX USART0/2/3. */
} IP_USART_001_Type;

#define UART_BLOCKING_TIMEOUT           (0xFFFFFFFFUL)	/*!< UART time-out definitions in case of using Read/Write function with Blocking Flag mode */

#define UART_ACCEPTED_BAUDRATE_ERROR    (3)				/*!< Acceptable UART baudrate error */

/* --------------------- BIT DEFINITIONS -------------------------------------- */
/**
 * @brief Macro defines for UARTn Receiver Buffer Register
 */
#define UART_RBR_MASKBIT    ((uint8_t) 0xFF)		/*!< UART Received Buffer mask bit (8 bits) */

/**
 * @brief Macro defines for UARTn Transmit Holding Register
 */
#define UART_THR_MASKBIT    ((uint8_t) 0xFF)		/*!< UART Transmit Holding mask bit (8 bits) */

/**
 * @brief Macro defines for UARTn Divisor Latch LSB register
 */
#define UART_LOAD_DLL(div)  ((div) & 0xFF)			/*!< Macro for loading least significant halfs of divisors */
#define UART_DLL_MASKBIT    ((uint8_t) 0xFF)		/*!< Divisor latch LSB bit mask */

/**
 * @brief Macro defines for UARTn Divisor Latch MSB register
 */
#define UART_DLM_MASKBIT    ((uint8_t) 0xFF)		/*!< Divisor latch MSB bit mask */
#define UART_LOAD_DLM(div)  (((div) >> 8) & 0xFF)	/*!< Macro for loading most significant halfs of divisors */

/**
 * @brief Macro defines for UART interrupt enable register
 */
#define UART_IER_RBRINT_EN      ((uint32_t) (1 << 0))	/*!< RBR Interrupt enable*/
#define UART_IER_THREINT_EN     ((uint32_t) (1 << 1))	/*!< THR Interrupt enable*/
#define UART_IER_RLSINT_EN      ((uint32_t) (1 << 2))	/*!< RX line status interrupt enable*/
#define UART_IER_MSINT_EN       ((uint32_t) (1 << 3))	/*!< Modem status interrupt enable */
#define UART_IER_CTSINT_EN      ((uint32_t) (1 << 7))	/*!< CTS1 signal transition interrupt enable */
#define UART_IER_ABEOINT_EN     ((uint32_t) (1 << 8))	/*!< Enables the end of auto-baud interrupt */
#define UART_IER_ABTOINT_EN     ((uint32_t) (1 << 9))	/*!< Enables the auto-baud time-out interrupt */
#define UART_IER_BITMASK        ((uint32_t) (0x307))	/*!< UART interrupt enable register bit mask */
#define UART1_IER_BITMASK       ((uint32_t) (0x38F))	/*!< UART1 interrupt enable register bit mask */

/**
 * @brief Macro defines for UART interrupt identification register
 */
#define UART_IIR_INTSTAT_PEND   ((uint32_t) (1 << 0))	/*!<Interrupt Status - Active low */
#define UART_IIR_INTID_RLS      ((uint32_t) (3 << 1))	/*!<Interrupt identification: Receive line status*/
#define UART_IIR_INTID_RDA      ((uint32_t) (2 << 1))	/*!<Interrupt identification: Receive data available*/
#define UART_IIR_INTID_CTI      ((uint32_t) (6 << 1))	/*!<Interrupt identification: Character time-out indicator*/
#define UART_IIR_INTID_THRE     ((uint32_t) (1 << 1))	/*!<Interrupt identification: THRE interrupt*/
#define UART_IIR_INTID_MODEM    ((uint32_t) (0 << 1))	/*!<Interrupt identification: Modem interrupt*/
#define UART_IIR_INTID_MASK     ((uint32_t) (7 << 1))	/*!<Interrupt identification: Interrupt ID mask */
#define UART_IIR_FIFO_EN        ((uint32_t) (3 << 6))	/*!<These bits are equivalent to UnFCR[0] */
#define UART_IIR_ABEO_INT       ((uint32_t) (1 << 8))	/*!< End of auto-baud interrupt */
#define UART_IIR_ABTO_INT       ((uint32_t) (1 << 9))	/*!< Auto-baud time-out interrupt */
#define UART_IIR_BITMASK        ((uint32_t) (0x3CF))	/*!< UART interrupt identification register bit mask */

/**
 * @brief Macro defines for UART FIFO control register
 */
#define UART_FCR_FIFO_EN        ((uint8_t) (1 << 0))	/*!< UART FIFO enable */
#define UART_FCR_RX_RS          ((uint8_t) (1 << 1))	/*!< UART FIFO RX reset */
#define UART_FCR_TX_RS          ((uint8_t) (1 << 2))	/*!< UART FIFO TX reset */
#define UART_FCR_DMAMODE_SEL    ((uint8_t) (1 << 3))	/*!< UART DMA mode selection */
#define UART_FCR_TRG_LEV0       ((uint8_t) (0))			/*!< UART FIFO trigger level 0: 1 character */
#define UART_FCR_TRG_LEV1       ((uint8_t) (1 << 6))	/*!< UART FIFO trigger level 1: 4 character */
#define UART_FCR_TRG_LEV2       ((uint8_t) (2 << 6))	/*!< UART FIFO trigger level 2: 8 character */
#define UART_FCR_TRG_LEV3       ((uint8_t) (3 << 6))	/*!< UART FIFO trigger level 3: 14 character */
#define UART_FCR_BITMASK        ((uint8_t) (0xCF))		/*!< UART FIFO control bit mask */
#define UART_TX_FIFO_SIZE       (16)

/**
 * @brief Macro defines for UART line control register
 */
#define UART_LCR_WLEN5          ((uint8_t) (0))				/*!< UART 5 bit data mode */
#define UART_LCR_WLEN6          ((uint8_t) (1 << 0))		/*!< UART 6 bit data mode */
#define UART_LCR_WLEN7          ((uint8_t) (2 << 0))		/*!< UART 7 bit data mode */
#define UART_LCR_WLEN8          ((uint8_t) (3 << 0))		/*!< UART 8 bit data mode */
#define UART_LCR_SBS_1BIT       ((uint8_t) (0 << 2))		/*!< UART One Stop Bit Select */
#define UART_LCR_SBS_2BIT       ((uint8_t) (1 << 2))		/*!< UART Two Stop Bits Select */
#define UART_LCR_PARITY_EN      ((uint8_t) (1 << 3))		/*!< UART Parity Enable */
#define UART_LCR_PARITY_DIS     ((uint8_t) (0 << 3))		/*!< UART Parity Disable */
#define UART_LCR_PARITY_ODD     ((uint8_t) (0))				/*!< UART Odd Parity Select */
#define UART_LCR_PARITY_EVEN    ((uint8_t) (1 << 4))		/*!< UART Even Parity Select */
#define UART_LCR_PARITY_F_1     ((uint8_t) (2 << 4))		/*!< UART force 1 stick parity */
#define UART_LCR_PARITY_F_0     ((uint8_t) (3 << 4))		/*!< UART force 0 stick parity */
#define UART_LCR_BREAK_EN       ((uint8_t) (1 << 6))		/*!< UART Transmission Break enable */
#define UART_LCR_DLAB_EN        ((uint8_t) (1 << 7))		/*!< UART Divisor Latches Access bit enable */
#define UART_LCR_BITMASK        ((uint8_t) (0xFF))			/*!< UART line control bit mask */

/**
 * @brief Macro defines for UART Modem control register
 */
#define UART_MCR_DTR_CTRL       ((uint8_t) (1 << 0))		/*!< Source for modem output pin DTR */
#define UART_MCR_RTS_CTRL       ((uint8_t) (1 << 1))		/*!< Source for modem output pin RTS */
#define UART_MCR_LOOPB_EN       ((uint8_t) (1 << 4))		/*!< Loop back mode select */
#define UART_MCR_AUTO_RTS_EN    ((uint8_t) (1 << 6))		/*!< Enable Auto RTS flow-control */
#define UART_MCR_AUTO_CTS_EN    ((uint8_t) (1 << 7))		/*!< Enable Auto CTS flow-control */
#define UART_MCR_BITMASK        ((uint8_t) (0x0F3))			/*!< UART1 bit mask value */

/**
 * @brief Macro defines for UART line status register
 */
#define UART_LSR_RDR        ((uint8_t) (1 << 0))	/*!<Line status register: Receive data ready*/
#define UART_LSR_OE         ((uint8_t) (1 << 1))	/*!<Line status register: Overrun error*/
#define UART_LSR_PE         ((uint8_t) (1 << 2))	/*!<Line status register: Parity error*/
#define UART_LSR_FE         ((uint8_t) (1 << 3))	/*!<Line status register: Framing error*/
#define UART_LSR_BI         ((uint8_t) (1 << 4))	/*!<Line status register: Break interrupt*/
#define UART_LSR_THRE       ((uint8_t) (1 << 5))	/*!<Line status register: Transmit holding register empty*/
#define UART_LSR_TEMT       ((uint8_t) (1 << 6))	/*!<Line status register: Transmitter empty*/
#define UART_LSR_RXFE       ((uint8_t) (1 << 7))	/*!<Error in RX FIFO*/
#define UART_LSR_BITMASK    ((uint8_t) (0xFF))		/*!<UART Line status bit mask */

/**
 * @brief Macro defines for UART Modem status register
 */
#define UART_MSR_DELTA_CTS      ((uint8_t) (1 << 0))	/*!< Set upon state change of input CTS */
#define UART_MSR_DELTA_DSR      ((uint8_t) (1 << 1))	/*!< Set upon state change of input DSR */
#define UART_MSR_LO2HI_RI       ((uint8_t) (1 << 2))	/*!< Set upon low to high transition of input RI */
#define UART_MSR_DELTA_DCD      ((uint8_t) (1 << 3))	/*!< Set upon state change of input DCD */
#define UART_MSR_CTS            ((uint8_t) (1 << 4))	/*!< Clear To Send State */
#define UART_MSR_DSR            ((uint8_t) (1 << 5))	/*!< Data Set Ready State */
#define UART_MSR_RI             ((uint8_t) (1 << 6))	/*!< Ring Indicator State */
#define UART_MSR_DCD            ((uint8_t) (1 << 7))	/*!< Data Carrier Detect State */
#define UART_MSR_BITMASK        ((uint8_t) (0xFF))		/*!< MSR register bit-mask value */

/**
 * @brief Macro defines for UART Scratch Pad register
 */
#define UART_SCR_BIMASK     ((uint8_t) (0xFF))			/*!< UART Scratch Pad bit mask */

/**
 * @brief Macro defines for UART Auto baudrate control register
 */
#define UART_ACR_START              ((uint32_t) (1 << 0))	/*!< UART Auto-baud start */
#define UART_ACR_MODE               ((uint32_t) (1 << 1))	/*!< UART Auto baudrate Mode 1 */
#define UART_ACR_AUTO_RESTART       ((uint32_t) (1 << 2))	/*!< UART Auto baudrate restart */
#define UART_ACR_ABEOINT_CLR        ((uint32_t) (1 << 8))	/*!< UART End of auto-baud interrupt clear */
#define UART_ACR_ABTOINT_CLR        ((uint32_t) (1 << 9))	/*!< UART Auto-baud time-out interrupt clear */
#define UART_ACR_BITMASK            ((uint32_t) (0x307))	/*!< UART Auto Baudrate register bit mask */

/**
 * @brief Macro defines for UART IrDA control register
 */
#define UART_ICR_IRDAEN         ((uint32_t) (1 << 0))			/*!< IrDA mode enable */
#define UART_ICR_IRDAINV        ((uint32_t) (1 << 1))			/*!< IrDA serial input inverted */
#define UART_ICR_FIXPULSE_EN    ((uint32_t) (1 << 2))			/*!< IrDA fixed pulse width mode */
#define UART_ICR_PULSEDIV(n)    ((uint32_t) ((n & 0x07) << 3))	/*!< PulseDiv - Configures the pulse when FixPulseEn = 1 */
#define UART_ICR_BITMASK        ((uint32_t) (0x3F))				/*!< UART IRDA bit mask */

/**
 * @brief Macro defines for UART half duplex register
 */
#define UART_HDEN_HDEN          ((uint32_t) (1 << 0))			/*!< enable half-duplex mode*/

/**
 * @brief Macro defines for UART smart card interface control register
 */
#define UART_SCICTRL_SCIEN      ((uint32_t) (1 << 0))				/*!< enable asynchronous half-duplex smart card interface*/
#define UART_SCICTRL_NACKDIS    ((uint32_t) (1 << 1))				/*!< NACK response is inhibited*/
#define UART_SCICTRL_PROTSEL_T1 ((uint32_t) (1 << 2))				/*!< ISO7816-3 protocol T1 is selected*/
#define UART_SCICTRL_TXRETRY(n) ((uint32_t) ((n & 0x07) << 5))		/*!< number of retransmission*/
#define UART_SCICTRL_GUARDTIME(n)   ((uint32_t) ((n & 0xFF) << 8))	/*!< Extra guard time*/

/**
 * @brief Macro defines for UART synchronous control register
 */
#define UART_SYNCCTRL_SYNC      ((uint32_t) (1 << 0))			/*!< enable synchronous mode*/
#define UART_SYNCCTRL_CSRC_MASTER   ((uint32_t) (1 << 1))		/*!< synchronous master mode*/
#define UART_SYNCCTRL_FES       ((uint32_t) (1 << 2))			/*!< sample on falling edge*/
#define UART_SYNCCTRL_TSBYPASS  ((uint32_t) (1 << 3))			/*!< to be defined*/
#define UART_SYNCCTRL_CSCEN     ((uint32_t) (1 << 4))			/*!< continuous running clock enable (master mode only)*/
#define UART_SYNCCTRL_STARTSTOPDISABLE  ((uint32_t) (1 << 5))	/*!< do not send start/stop bit*/
#define UART_SYNCCTRL_CCCLR     ((uint32_t) (1 << 6))			/*!< stop continuous clock*/

/**
 * @brief Macro defines for UART Fractional divider register
 */
#define UART_FDR_DIVADDVAL(n)   ((uint32_t) (n & 0x0F))			/*!< Baud-rate generation pre-scaler divisor */
#define UART_FDR_MULVAL(n)      ((uint32_t) ((n << 4) & 0xF0))	/*!< Baud-rate pre-scaler multiplier value */
#define UART_FDR_BITMASK        ((uint32_t) (0xFF))				/*!< UART Fractional Divider register bit mask */

/**
 * @brief Macro defines for UART Tx Enable register
 */
#define UART_TER1_TXEN          ((uint8_t) (1 << 7))		/*!< Transmit enable bit */
#define UART_TER1_BITMASK       ((uint8_t) (0x80))			/*!< UART Transmit Enable Register bit mask */
#define UART_TER2_TXEN      ((uint8_t) (1 << 0))			/*!< Transmit enable bit */
#define UART_TER2_BITMASK   ((uint8_t) (0x01))				/*!< UART Transmit Enable Register bit mask */

/**
 * @brief Macro defines for UART1 RS485 Control register
 */
#define UART_RS485CTRL_NMM_EN       ((uint32_t) (1 << 0))	/*!< RS-485/EIA-485 Normal Multi-drop Mode (NMM) is disabled */
#define UART_RS485CTRL_RX_DIS       ((uint32_t) (1 << 1))	/*!< The receiver is disabled */
#define UART_RS485CTRL_AADEN        ((uint32_t) (1 << 2))	/*!< Auto Address Detect (AAD) is enabled */
#define UART_RS485CTRL_SEL_DTR      ((uint32_t) (1 << 3))	/*!< If direction control is enabled (bit DCTRL = 1), pin DTR is
															    used for direction control */
#define UART_RS485CTRL_DCTRL_EN ((uint32_t) (1 << 4))		/*!< Enable Auto Direction Control */
#define UART_RS485CTRL_OINV_1       ((uint32_t) (1 << 5))	/*!< This bit reverses the polarity of the direction
															   control signal on the RTS (or DTR) pin. The direction control pin
															   will be driven to logic "1" when the transmitter has data to be sent */
#define UART_RS485CTRL_BITMASK      ((uint32_t) (0x3F))		/*!< RS485 control bit-mask value */

/**
 * @brief Macro defines for UART1 RS-485 Address Match register
 */
#define UART_RS485ADRMATCH_BITMASK ((uint8_t) (0xFF))		/*!< Bit mask value */

/**
 * @brief Macro defines for UART1 RS-485 Delay value register
 */
#define UART_RS485DLY_BITMASK       ((uint8_t) (0xFF))		/*!< Bit mask value */

/**
 * @brief Macro defines for UART FIFO Level register
 */
#define UART_FIFOLVL_RXFIFOLVL(n)   ((uint32_t) (n & 0x0F))			/*!< Reflects the current level of the UART receiver FIFO */
#define UART_FIFOLVL_TXFIFOLVL(n)   ((uint32_t) ((n >> 8) & 0x0F))	/*!< Reflects the current level of the UART transmitter FIFO */
#define UART_FIFOLVL_BITMASK        ((uint32_t) (0x0F0F))			/*!< UART FIFO Level Register bit mask */

/**
 * @brief Macro defines for Ring Buffer
 */
#define UART_RING_BUFSIZE 256															/*!< buffer size definition */
#define __BUF_MASK (UART_RING_BUFSIZE - 1)												/*!< Buf mask */
#define __BUF_IS_FULL(head, tail) ((tail & __BUF_MASK) == ((head + 1) & __BUF_MASK))	/*!< Check buf is full or not */
#define __BUF_WILL_FULL(head, tail) ((tail & __BUF_MASK) == ((head + 2) & __BUF_MASK))	/*!< Check buf will be full in next receiving or not */
#define __BUF_IS_EMPTY(head, tail) ((head & __BUF_MASK) == (tail & __BUF_MASK))			/*!< Check buf is empty */
#define __BUF_RESET(bufidx) (bufidx = 0)												/*!< Reset buf */
#define __BUF_INCR(bufidx)  (bufidx = (bufidx + 1) & __BUF_MASK)						/*!< Increase buf */

/**
 * @brief UART Ring buffer structure
 */
typedef struct {
	__IO uint32_t tx_head;					/*!< UART Tx ring buffer head index */
	__IO uint32_t tx_tail;					/*!< UART Tx ring buffer tail index */
	__IO uint32_t rx_head;					/*!< UART Rx ring buffer head index */
	__IO uint32_t rx_tail;					/*!< UART Rx ring buffer tail index */
	__IO uint8_t  tx[UART_RING_BUFSIZE];	/*!< UART Tx data ring buffer */
	__IO uint8_t  rx[UART_RING_BUFSIZE];	/*!< UART Rx data ring buffer */
} UART_RingBuffer_Type;

/**
 * @brief UART Line Status Type definition
 */
typedef enum {
	UART_LINESTAT_RDR   = UART_LSR_RDR,			/*!< Line status register: Receive data ready*/
	UART_LINESTAT_OE    = UART_LSR_OE,			/*!< Line status register: Overrun error*/
	UART_LINESTAT_PE    = UART_LSR_PE,			/*!< Line status register: Parity error*/
	UART_LINESTAT_FE    = UART_LSR_FE,			/*!< Line status register: Framing error*/
	UART_LINESTAT_BI    = UART_LSR_BI,			/*!< Line status register: Break interrupt*/
	UART_LINESTAT_THRE  = UART_LSR_THRE,		/*!< Line status register: Transmit holding register empty*/
	UART_LINESTAT_TEMT  = UART_LSR_TEMT,		/*!< Line status register: Transmitter empty*/
	UART_LINESTAT_RXFE  = UART_LSR_RXFE			/*!< Error in RX FIFO*/
} IP_UART_LS_Type;

/**
 * @brief UART End of Auto-baudrate type definition
 */
typedef enum {
	UART_AUTOBAUD_INTSTAT_ABEO      = UART_IIR_ABEO_INT,		/*!< UART End of auto-baud interrupt  */
	UART_AUTOBAUD_INTSTAT_ABTO      = UART_IIR_ABTO_INT			/*!< UART Auto-baud time-out interrupt  */
} IP_UART_ABEO_Type;

/**
 * @brief UART Full modem -  Signal states definition
 */
typedef enum {
	INACTIVE = 0,			/*!< In-active state */
	ACTIVE = !INACTIVE		/*!< Active state */
} IP_UART_SignalState;

/**
 * @brief UART modem status type definition
 */
typedef enum {
	UART_MODEM_STAT_DELTA_CTS   = UART_MSR_DELTA_CTS,		/*!< Set upon state change of input CTS */
	UART_MODEM_STAT_DELTA_DSR   = UART_MSR_DELTA_DSR,		/*!< Set upon state change of input DSR */
	UART_MODEM_STAT_LO2HI_RI    = UART_MSR_LO2HI_RI,		/*!< Set upon low to high transition of input RI */
	UART_MODEM_STAT_DELTA_DCD   = UART_MSR_DELTA_DCD,		/*!< Set upon state change of input DCD */
	UART_MODEM_STAT_CTS         = UART_MSR_CTS,				/*!< Clear To Send State */
	UART_MODEM_STAT_DSR         = UART_MSR_DSR,				/*!< Data Set Ready State */
	UART_MODEM_STAT_RI          = UART_MSR_RI,				/*!< Ring Indicator State */
	UART_MODEM_STAT_DCD         = UART_MSR_DCD				/*!< Data Carrier Detect State */
} IP_UART_MODEM_STAT_type;

/**
 * @brief Modem output pin type definition
 */
typedef enum {
	UART_MODEM_PIN_DTR          = 0,		/*!< Source for modem output pin DTR */
	UART_MODEM_PIN_RTS						/*!< Source for modem output pin RTS */
} IP_UART_MODEM_PIN_Type;

/**
 * @brief UART Modem mode type definition
 */
typedef enum {
	UART_MODEM_MODE_LOOPBACK    = 0,		/*!< Loop back mode select */
	UART_MODEM_MODE_AUTO_RTS,				/*!< Enable Auto RTS flow-control */
	UART_MODEM_MODE_AUTO_CTS				/*!< Enable Auto CTS flow-control */
} IP_UART_MODEM_MODE_Type;

/**
 * @brief UART Interrupt Type definitions
 */
typedef enum {
	UART_INTCFG_RBR = 0,	/*!< RBR Interrupt enable*/
	UART_INTCFG_THRE,		/*!< THR Interrupt enable*/
	UART_INTCFG_RLS,		/*!< RX line status interrupt enable*/
	UART_INTCFG_MS,			/*!< Modem status interrupt enable */
	UART_INTCFG_CTS,		/*!< CTS1 signal transition interrupt enable */
	UART_INTCFG_ABEO,		/*!< Enables the end of auto-baud interrupt */
	UART_INTCFG_ABTO		/*!< Enables the auto-baud time-out interrupt */
} UART_INT_Type;

/**
 * @brief UART Parity type definitions
 */
typedef enum {
	UART_PARITY_NONE = 0,									/*!< No parity */
	UART_PARITY_ODD = (4 << 3),								/*!< Odd parity */
	UART_PARITY_EVEN = (5 << 3),							/*!< Even parity */
	UART_PARITY_SP_1 = (6 << 3),							/*!< Forced "1" stick parity */
	UART_PARITY_SP_0 = (7 << 3)								/*!< Forced "0" stick parity */
} UART_PARITY_Type;

/**
 * @brief FIFO Level type definitions
 */
typedef enum {
	UART_FIFO_TRGLEV0 = 0,	/*!< UART FIFO trigger level 0: 1 character */
	UART_FIFO_TRGLEV1,		/*!< UART FIFO trigger level 1: 4 character */
	UART_FIFO_TRGLEV2,		/*!< UART FIFO trigger level 2: 8 character */
	UART_FIFO_TRGLEV3		/*!< UART FIFO trigger level 3: 14 character */
} UART_FITO_LEVEL_Type;

/**
 * @brief UART Stop bit type definitions
 */
typedef enum {
	UART_STOPBIT_1 = 0,							/*!< UART One Stop Bit Select */
	UART_STOPBIT_2 = (1 << 2)					/*!< UART Two Stop Bits Select */
} UART_STOPBIT_Type;

/**
 * @brief UART Databit type definitions
 */
typedef enum {
	UART_DATABIT_5      = 0,			/*!< UART 5 bit data mode */
	UART_DATABIT_6,						/*!< UART 6 bit data mode */
	UART_DATABIT_7,						/*!< UART 7 bit data mode */
	UART_DATABIT_8						/*!< UART 8 bit data mode */
} UART_DATABIT_Type;

/**
 * @brief UART ID
 */
typedef enum {
	UART_0 = 0,
	UART_1,
	UART_2,
	UART_3,
	UART_4,
} UART_ID_Type;

/**
 * @brief UART Interrupt Status
 */
typedef enum {
	UART_ERROR = 1,
	READY_TO_SEND,
	READY_TO_RECEIVE = 4,
} UART_Int_Status;

/**
 * @brief UART FIFO Configuration Structure definition
 */
typedef struct {
	FunctionalState FIFO_ResetRxBuf;	/*!< Reset Rx FIFO command state , should be:
										   - ENABLE: Reset Rx FIFO in UART
										   - DISABLE: Do not reset Rx FIFO  in UART
										 */
	FunctionalState FIFO_ResetTxBuf;	/*!< Reset Tx FIFO command state , should be:
										   - ENABLE: Reset Tx FIFO in UART
										   - DISABLE: Do not reset Tx FIFO  in UART
										 */
	FunctionalState FIFO_DMAMode;		/*!< DMA mode, should be:
										   - ENABLE: Enable DMA mode in UART
										   - DISABLE: Disable DMA mode in UART
										 */
	UART_FITO_LEVEL_Type FIFO_Level;	/*!< Rx FIFO trigger level, should be:
										   - UART_FIFO_TRGLEV0: UART FIFO trigger level 0: 1 character
										   - UART_FIFO_TRGLEV1: UART FIFO trigger level 1: 4 character
										   - UART_FIFO_TRGLEV2: UART FIFO trigger level 2: 8 character
										   - UART_FIFO_TRGLEV3: UART FIFO trigger level 3: 14 character
										 */
} UART_FIFO_CFG_Type;

/**
 * @brief	Initializes the UARTx peripheral according to the specified parameters in the UART_ConfigStruct.
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	UARTPort	: UART ID type
 * @return	Nothing
 */
void IP_UART_Init(IP_USART_001_Type *LPC_UART, UART_ID_Type UARTPort);

/**
 * @brief	De-initializes the UARTx peripheral registers to their default reset values.
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	UARTPort	: UART ID type
 * @return	Nothing
 */
void IP_UART_DeInit(IP_USART_001_Type *LPC_UART, UART_ID_Type UARTPort);

/**
 * @brief	Determines best dividers to get a target clock rate
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	baudrate	: Desired UART baud rate.
 * @param	uClk		: Current Uart Block Clock.
 * @return	Error status, could be SUCCESS or ERROR
 */
Status IP_UART_SetBaud(IP_USART_001_Type *LPC_UART, uint32_t baudrate, uint32_t uClk);

/**
 * @brief	Configure data width, parity mode and stop bits
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	Databits	: UART Data width, should be:
 *                  		UART_DATABIT_5: UART 5 bit data mode
 *                  		UART_DATABIT_6: UART 6 bit data mode
 *                  		UART_DATABIT_7: UART 7 bit data mode
 *                  		UART_DATABIT_8: UART 8 bit data mode
 * @param	Parity		: UART Parity mode, should be:
 *                  		UART_PARITY_NONE: No parity
 *                  		UART_PARITY_ODD:  Odd parity
 *                  		UART_PARITY_EVEN: Even parity
 *                  		UART_PARITY_SP_1: Forced "1" stick parity
 *                  		UART_PARITY_SP_0: Forced "0" stick parity
 * @param	Stopbits	: Number of stop bits, should be:
 *                  		UART_STOPBIT_1: One Stop Bit Select
 *                  		UART_STOPBIT_2: Two Stop Bits Select
 * @return	Nothing
 */
void IP_UART_ConfigData(IP_USART_001_Type *LPC_UART,
						UART_DATABIT_Type Databits,
						UART_PARITY_Type Parity,
						UART_STOPBIT_Type Stopbits);

/* UART Send/Receive functions -------------------------------------------------*/
/**
 * @brief	Transmit a single data through UART peripheral
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	Data		: Data to transmit (must be 8-bit long)
 * @return	Status, should be ERROR (THR is empty, ready to send) or SUCCESS (THR is not empty)
 */
Status IP_UART_SendByte(IP_USART_001_Type *LPC_UART, uint8_t Data);

/**
 * @brief	Receive a single data from UART peripheral
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	*Data		: Pointer to Data to receive (must be 8-bit long)
 * @return	Status, should be ERROR or (Receive data is ready) or SUCCESS (Receive data is not ready yet)
 */
Status IP_UART_ReceiveByte(IP_USART_001_Type *LPC_UART, uint8_t *Data);

/**
 * @brief	Send a block of data via UART peripheral
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	txbuf		: Pointer to Transmit buffer
 * @param	buflen		: Length of Transmit buffer
 * @param   flag		: Flag used in  UART transfer, should be NONE_BLOCKING or BLOCKING
 * @return	Number of bytes sent
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 */
uint32_t IP_UART_Send(IP_USART_001_Type *LPC_UART, uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag);

/**
 * @brief	Receive a block of data via UART peripheral
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	rxbuf		: Pointer to Received buffer
 * @param	buflen		: Length of Received buffer
 * @param   flag		: Flag mode, should be NONE_BLOCKING or BLOCKING
 * @return	Number of bytes received
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 */
uint32_t IP_UART_Receive(IP_USART_001_Type *LPC_UART, uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag);

/* UART operate functions -------------------------------------------------------*/
/**
 * @brief	Enable or disable specified UART interrupt.
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	UARTIntCfg	: Specifies the interrupt flag, should be one of the following:
 *                  - UART_INTCFG_RBR   : RBR Interrupt enable
 *                  - UART_INTCFG_THRE  : THR Interrupt enable
 *                  - UART_INTCFG_RLS   : RX line status interrupt enable
 *                  - UART1_INTCFG_MS	: Modem status interrupt enable (UART1 only)
 *                  - UART1_INTCFG_CTS	: CTS1 signal transition interrupt enable (UART1 only)
 *                  - UART_INTCFG_ABEO  : Enables the end of auto-baud interrupt
 *                  - UART_INTCFG_ABTO  : Enables the auto-baud time-out interrupt
 * @param	NewState	: New state of specified UART interrupt type, should be:
 *                  - ENALBE	: Enable this UART interrupt type
 *                  - DISALBE	: Disable this UART interrupt type
 * @return	Nothing
 */
void IP_UART_IntConfig(IP_USART_001_Type *LPC_UART, UART_INT_Type UARTIntCfg, FunctionalState NewState);

/**
 * @brief	Get Source Interrupt
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @return	Return the value of IIR register
*/
uint32_t IP_UART_IntGetStatus(IP_USART_001_Type *LPC_UART);

/**
 * @brief	Force BREAK character on UART line, output pin UARTx TXD is forced to logic 0
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
void IP_UART_ForceBreak(IP_USART_001_Type *LPC_UART);

/**
 * @brief	Get current value of Line Status register in UART peripheral.
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @return	Current value of Line Status register in UART peripheral
 *
 * Note:	The return value of this function must be ANDed with each member in UART_LS_Type
 * enumeration to determine current flag status corresponding to each Line status type. Because
 * some flags in Line Status register will be cleared after reading, the next reading Line
 * Status register could not be correct. So this function used to read Line status register
 * in one time only, then the return value used to check all flags.
 */
uint8_t IP_UART_GetLineStatus(IP_USART_001_Type *LPC_UART);

/**
 * @brief	Check whether if UART is busy or not
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @return	RESET if UART is not busy, otherwise return SET.
 */
FlagStatus IP_UART_CheckBusy(IP_USART_001_Type *LPC_UART);

/**
 * @brief	Enable/Disable transmission on UART TxD pin
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	UARTPort	: UART ID type
 * @param	NewState	: New State of Tx transmission function, should be ENABLE or DISABLE
 * @return	Nothing
 */
void IP_UART_TxCmd(IP_USART_001_Type *LPC_UART, UART_ID_Type UARTPort, FunctionalState NewState);

/* UART FIFO functions ----------------------------------------------------------*/
/**
 * @brief	Configure FIFO function on selected UART peripheral
 * @param	LPC_UART	: Pointer to selected UARTx peripheral
 * @param	FIFOCfg		: Pointer to a UART_FIFO_CFG_Type Structure that contains specified information about FIFO configuration
 * @return	Nothing
 */
void IP_UART_FIFOConfig(IP_USART_001_Type *LPC_UART, UART_FIFO_CFG_Type *FIFOCfg);

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
void IP_UART_FIFOConfigStructInit(UART_FIFO_CFG_Type *UART_FIFOInitStruct);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USART_001_H_ */
