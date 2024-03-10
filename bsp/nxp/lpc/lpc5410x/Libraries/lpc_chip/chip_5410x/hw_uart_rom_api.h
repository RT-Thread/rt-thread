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

#ifndef __HW_UART_ROM_API_H
#define __HW_UART_ROM_API_H

#include <stdint.h>
#include <string.h>
#include "error.h"
#include "packing.h"
#include "hw_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_UART UART/USART ROM driver functions and definitions
 * @ingroup ROMAPI_UART_WRAPPER
 * @{
 */

/** @brief UART Handler type */
typedef void *UART_HANDLE_T;

/** @brief	UART Data transfer status */
typedef enum {
	UART_ST_DONE,		/*!< Transfer completed */
	UART_ST_BUSY,		/*!< Transfer is in progress */
	UART_ST_ERR,		/*!< Generic error */
	UART_ST_ERRPAR,		/*!< ERROR: PARITY */
	UART_ST_ERRFRM,		/*!< ERROR: Frame */
	UART_ST_ERRNOISE,	/*!< ERROR: Receiver noise */
	UART_ST_ERROVR,		/*!< ERROR: Overflow */
} UART_STATE_T;

/** @brief UART Transfer structure */
typedef PRE_PACK struct POST_PACK {
	void *buf;					/*!< Pointer to buffer */
	uint16_t count;				/*!< Number of items to be sent/received [Not number of bytes] */
	uint8_t dwidth;				/*!< Width of data items in @a buf; 0 - 8:Bits; 1 - 16:Bits */
#ifdef UARTROMV2_PRESENT
	uint8_t state;				/*!< UART TX/RX eror status see #UART_STATE_T */
	uint16_t offset;			/*!< Offset of the buffer at which data is being currently processed; usually not used by application */
#else
	volatile uint8_t state;		/*!< UART TX/RX eror status see #UART_STATE_T */
	volatile uint16_t offset;	/*!< Offset of the buffer at which data is being currently processed; usually not used by application */
#endif
	uint16_t reserved;			/*!< Reserved for alignment */
} UART_DATA_T;

/**
 * @brief	UART Baud rate calculation structure
 * @note
 * Use oversampling (@a ovr) value other than 16, only if the difference
 * between the actual baud and desired baud has an unacceptable error percentage.
 * Smaller @a ovr values can cause the sampling position within the data-bit
 * less accurate an may potentially cause more noise errors or incorrect data
 * set ovr to < 10 only when there is no other higher values suitable.
 */
typedef PRE_PACK struct POST_PACK {
	uint32_t clk;	/*!< IN: Base clock to fractional divider; OUT: "Base clock rate for UART" */
	uint32_t baud;	/*!< IN: Required baud rate; OUT: Actual baud rate */
	uint8_t ovr;	/*!< IN: Number of desired over samples [0-auto detect or values 5 to 16]; OUT: Auto detected over samples [unchanged if IN is not 0] */
	uint8_t mul;	/*!< IN: 0 - calculate MUL, 1 - do't calculate (@a clk) has UART base clock; OUT: MUL value to be set in FRG register */
	uint16_t div;	/*!< OUT: Integer divider to divide the "Base clock rate for UART" */
} UART_BAUD_T;

/** @brief	UART Callback function index
 *
 * These values must be passed by the application, when they register their
 * callbacks with the ROM driver
 */
typedef enum {
	UART_CB_START,	/*!< UART Callback for TX/RX START event; will have @a event argument set to #UART_TX_START
					   for TX start event and #UART_RX_START for RX start event */
	UART_CB_DONE,	/*!< UART Callback for TX/RX Complete event; will have @a event argument set to #UART_TX_DONE
					   for TX Done event and #UART_RX_DONE for RX done event*/
	UART_CB_DATA,	/*!< UART Callback sending TX data or receiving RX Data; will have @a event argument set
					   to #UART_TX_DATA for TX data and #UART_RX_DATA for RX data*/
	UART_CB_RXPROG,	/*!< UART Callback for every received character (progress); will have @a event argument set
					   to #UART_RX_INPROG if a character is received and more characters are arriving,
					   else it will be set to #UART_RX_NOPROG when character is received and no more characters
					   are found within one character time frame*/
	UART_CB_ERREVT,	/*!< UART Callback for any Errors/Events; @a event argument will be #UART_EV_ERROR if the
					   callback is for error event, or it will be #UART_EV_EVENT if it is nor normal events like
					   BREAK, TXPAUSE etc., */
	UART_CB_RESERVED/*!< Reserved; Should not be used */
} UART_CBINDEX_T;

/** @brief	UART Event enumerations
 *
 * These values are passed by the driver as the second argument
 * of the callback functions that are invoked by the ROM driver
 */
typedef enum {
	UART_TX_START,	/*!< UART TX Start event; @a arg will be a pointer to #UART_DATA_T that has information related to TX buffer */
	UART_RX_START,	/*!< UART RX Start event; @a arg will be a pointer to #UART_DATA_T that has information related to RX buffer
					   this event does not mean a start of RX into the given buffer, instead it means receiver has started receiving
					   new character after being idle for one character frame time */
	UART_TX_DONE,	/*!< UART TX Complete event; @a arg will be a pointer to #UART_DATA_T that has information related to TX Buffer */
	UART_RX_DONE,	/*!< UART RX Complete event; @a arg will be a pointer to #UART_DATA_T that has information related to RX Buffer */
	UART_TX_DATA,	/*!< UART Push TX data; @a arg will be pointer to #UART_DATA_T; @a buf will contain the pointer to the data
					   to be sent, @a sz will have the number of items to be sent and @a b16 will be set to 1 if the data to be
					   transmitted is of 16-bits wide (else @a b16 will be 0); after pushing the data from buf the callback should
					   set the @a sz to number of bytes remaining to be sent */
	UART_RX_DATA,	/*!< UART Pop RX data; @a arg will be pointer to #UART_DATA_T; @a buf will contain the pointer to memory where
					   receive data be stored, @a sz will have the number of items to be received and @a b16 will be set to 1 if the
					   data to be received is of 16-bits wide [Bits 9 to 15 must be 0] (else @a b16 will be 0); after reading the data
					   into buf the callback should set the @a sz to number of bytes yet to be received */
	UART_RX_INPROG,	/*!< Received a UART character and more characters are being processed by shift register */
	UART_RX_NOPROG,	/*!< Received a UART character and no more characters are received within one character time */
	UART_EV_ERROR,	/*!< UART Error; @a arg parameter will be one of the UART_ERROR_XXX (Example #UART_ERROR_FRAME) */
	UART_EV_EVENT	/*!< UART special events; @a arg parameter will be one of the UART_EVENT_XXX (Example #UART_EVENT_BREAK) */
} UART_EVENT_T;

/** @brief	UART Configuration bits
 *
 * These bits can be OR'd to get the configuration value (second parameter) for aConfigure API
 */
#undef UART_CFG_MODE32K
#undef UART_CFG_LINMODE
#define UART_CFG_7BIT      0		/*!< UART uses 7-Bit data transfer; Buffer used by Send and Receive API must be of type <b>uint8_t *</b> */
#define UART_CFG_8BIT     (1 << 2)	/*!< UART uses 8-Bit data transfer; Buffer used by Send and Receive API must be of type <b>uint8_t *</b> */
#define UART_CFG_9BIT     (1 << 3)	/*!< UART uses 9-Bit data transfer; Buffer used by Send and Receive API must be of type <b>uint16_t *</b> */
#define UART_CFG_NOPAR     0		/*!< UART Transfers do not use parity */
#define UART_CFG_EVENPAR  (2 << 5)	/*!< Enable EVEN Parity */
#define UART_CFG_ODDPAR   (3 << 4)	/*!< Enable ODD Parity */
#define UART_CFG_1STOP     0		/*!< UART Tx/Rx will use 1-stop bit at the end of transfer */
#define UART_CFG_2STOP    (1 << 6)	/*!< UART Tx/Rx will use 2-Stop bits towards end of transfers */
#define UART_CFG_MODE32K  (1 << 7)	/*!< Use 32KHz RTC clock; Needs special clocking setup to be done by the application */
#define UART_CFG_LINMODE  (1 << 8)	/*!< Break detect and generation will use LIN bus operation */
#define UART_CFG_HWFLOW   (1 << 9)	/*!< Enable Hardware flow control */
#define UART_CFG_CTSEV    (1 << 10)	/*!< Enable CTS events */
#define UART_CFG_BRKRX    (1 << 13)	/*!< Enable BREAK receive events */

/* USART Synchorous mode configurations */
#define UART_CFG_SYNMODE   (1 << 11)/*!< Synchronous Mode: Enable Synchronous mode */
#define UART_CFG_FALLING    0		/*!< Synchronous Mode: Sample data during falling edge of SCLK (Must be used with #UART_CFG_SYNMODE) */
#define UART_CFG_RISING    (1 << 12)/*!< Synchronous mode: Sample data during rising edge of SCLK (Must be used with #UART_CFG_SYNMODE) */
#define UART_CFG_MASTER    (1 << 14)/*!< Synchronous mode: USART will be the master (Must be used with #UART_CFG_SYNMODE) */

/* UART Modes */
#define UART_CFG_LOOPBACK  (1 << 15)/*!< UART will operate in diagnostic loopback mode */
#define UART_CFG_IRDAMODE  (1 << 16)/*!< UART will operate in IrDA mode */

/* RS-485 specific configurations */
#define UART_CFG_OESEL     (1 << 20)/*!< RS-485: RTS will be used to control output enable of an RS-485 transceiver */
#define UART_CFG_OETA      (1 << 18)/*!< RS-485: Deassertion of Output Enable signal will be delayed for 1 character time; should be used with #UART_CFG_OESEL */
#define UART_CFG_AUTOADDR  (1 << 19)/*!< RS-485: Enable Automatic address checking [If MSB of Rx data is 1, hadware compares it with address set with #UART_CFG_ADDR] */
#define UART_CFG_OEPOLHIGH (1 << 21)/*!< RS-485: Output enable signal is active high */
#define UART_CFG_ADDR(adr) ((adr) << 24)/*!< RS-485: Set RS-485 device address comparision */

#define UART_CFG_RXPOL     (1 << 22)/*!< Invert the RX Pin polarity; 1 considered start and 0 considered stop, with inverted data */
#define UART_CFG_TXPOL     (1 << 23)/*!< Invert the TX Pin polarity; 1 sent as start and 0 sent as stop, with inverted data */

/** @brief	UART configuration options used with UART_SetCtrl() */
#define UART_BREAK_ON       ((1UL << 0) | (1UL << 16))	/*!< Sends BREAK on the TX line till SetConfig() called with #UART_BREAK_OFF;
														   Sending BREAK when TX is in progress might make the receiver get a frame error
														   Use UART_TX_PAUSE before setting UART_BREAK_ON to safely send break  */
#define UART_BREAK_OFF      (1UL << 16)					/*!< Turns OFF break condition */
#define UART_ADDRDET_ON     ((1UL << 1) | (1UL << 17))	/*!< Enable Address detect mode in RS-485; When turned on receiver ignores all
														   incoming data that has MSB [Typically 9th Bit] as 0, when data with MSB as 1
														   is received it will cause the UART TX EVENT, software can compare the address
														   and call SetConfig with #UART_ADDRDET_OFF to resume to normal mode */
#define UART_ADDRDET_OFF    (1UL << 17)					/*!< Disable address detect mode in RS-485 */
#define UART_TX_PAUSE       ((1UL << 5) | (1UL << 21))	/*!< Pause Transmit; typically used for Software flow control implementation this,
														   will invoke callback registerd for #UART_CB_ERREVT with @a event as #UART_EV_EVENT
														   and the (void *) arg will be #UART_EVENT_TXPAUSED, the callback will be called after
														   the current data in shift register is completely transmitted */
#define UART_TX_RESUME      (1UL << 21)					/*!< Resume Transmit; typically used for Software flow control */
#define UART_CCLK_ON        ((1UL << 7) | (1UL << 23))	/*!< In Sync mode; sends continuous clock so that RX can happen independent of TX */
#define UART_CCLK_OFF       (1UL << 23)					/*!< In Sync mode; Disables continuous clock so that clock will be generated only when characters are being sent */
#define UART_CCLK_AUTO      ((1UL << 8) | (1UL << 24))	/*!< In Sync mode; Sends continuous clock until a complete character is received */
#define UART_AUTOBAUD       ((1UL << 15) | (1UL << 31))	/*!< Enables Autobaud mode; sets the DIV value based on received character */
#define UART_TXIDLE_ON      ((1UL << 3)  | (1UL << 19))	/*!< Enable event generation on TX IDLE */
#define UART_TXIDLE_OFF     (1UL << 19)					/*!< Disable event generation on TX IDLE */
#define UART_RX_STOP        (1UL << 18)

/* @brief	UART event codes for arg parameter of callback (see #UART_EV_EVENT) */
#define UART_EVENT_BREAK       0x100					/*!< UART RX line is in BREAK state */
#define UART_EVENT_NOBREAK     0x101					/*!< UART RX line restored from BREAK state */
#define UART_EVENT_TXIDLE      0x102					/*!< UART TX is idle; nothing in shift register */
#define UART_EVENT_TXPAUSED    0x103					/*!< TX is paused */
#define UART_EVENT_CTSHI       0x104					/*!< CTS line went from low to high; typically used for flow-control */
#define UART_EVENT_CTSLO       0x105					/*!< CTS line went from High to Low; typically used for flow-control */

/** @brief	Error codes for arg parameter of callback (see #UART_EV_ERROR) */
#define UART_ERROR_FRAME       0x200					/*!< UART Frame error */
#define UART_ERROR_PARITY      0x201					/*!< UART Parity error */
#define UART_ERROR_AUTOBAUD    0x202					/*!< UART Autobaud error */
#define UART_ERROR_RXNOISE     0x203					/*!< UART RX NOISE error */
#define UART_ERROR_OVERRUN     0x204					/*!< UART RX overrun error */

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a UART ROM
 * driver handle.<br>
 * To get a user context, simply use the macro on the driver's handle:
 * void *pUserData = ROM_UART_HANDLE_TOUDATA(hUART);
 */
#define ROM_UART_HANDLE_TOUDATA(p)          (void *) (*(uint32_t *) p)

/** @brief	UART Configuration data structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t cfg;		/*!< UART Configuration value; OR'ed UART_CFG_XXXX values(example #UART_CFG_8BIT) */
	uint16_t div;		/*!< UART baudrate divider value; usually calculated by using UART_CalBaud() API */
	uint8_t ovr;		/*!< UART Over sampling value; usually calculated by using UART_CalBaud() API */
	uint8_t res;		/*!< Reserved for alignment; must be 0 */
} UART_CFG_T;

/**
 * @brief	Structure that has the API pointers in ROM Table
 */
typedef PRE_PACK struct POST_PACK {
	/* Index of All the UART/USART driver APIs */
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of UART driver */
	ErrorCode_t (*CalBaud)(UART_BAUD_T *baud);	/*!< Calculates the baudrate parameters for the given frequency, baud rate */
	UART_HANDLE_T (*Init)(void *pMem, uint32_t baseAddr, void *pUserData);	/*!< Initializes the UART driver and peripheral */
	ErrorCode_t (*Configure)(UART_HANDLE_T hUART, const UART_CFG_T *cfg);	/*!< Configure the UART to given parameters */
	void (*SetCtrl)(UART_HANDLE_T hUART, uint32_t cfgVal);	/*!< Set/Clear special control operations like BREAK, IDLE, etc., */
	ErrorCode_t (*RegisterCB)(UART_HANDLE_T hUART, UART_CBINDEX_T cbIndex,
							  void (*pCbFunc)(UART_HANDLE_T, UART_EVENT_T, void *));												/*!< Registers an UART callback function */
	void (*Handler)(UART_HANDLE_T hUART);	/*!< UART Event handler, should be called from the ISR */
	ErrorCode_t (*Send)(UART_HANDLE_T hUART, const void *buffer, uint16_t size);/*!< Send data to UART */
	ErrorCode_t (*Receive)(UART_HANDLE_T hUART, void *buffer, uint16_t size);	/*!< Receive data from UART */
	void (*WaitTx)(UART_HANDLE_T hUART);/*!< Wait for UART TX to complete; Used for polling */
	void (*WaitRx)(UART_HANDLE_T hUART);/*!<  Wait for UART data receive to complete; Used for polling */
	uint32_t (*GetDriverVersion)(void);	/*!< Get the version of the Driver Firmware in ROM */
} ROM_UART_API_T;

/* UART Register offsets */
#define UART_TX_OFFSET 0x1C
#define UART_RX_OFFSET 0x14

/** @brief	Calculates UART TX register base address from UART handle */
#define UART_DMA_TXADDR(han) (*(((uint32_t *) (han)) + 1) + UART_TX_OFFSET)

/** @brief	Calculates UART RX register base address from UART handle */
#define UART_DMA_RXADDR(han) (*(((uint32_t *) (han)) + 1) + UART_RX_OFFSET)

/* REMOVE: after H/W IDLE is fixed */
#define UART_BIT_DLY(baud) ((baud) / 4800 ? 921600 / (baud) : 2400 / (baud) + 224)

/* Extern declaration so that application can access
 * pointer to the function table
 */
extern const ROM_UART_API_T  uartrom_api;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HW_UART_ROM_API_H */
