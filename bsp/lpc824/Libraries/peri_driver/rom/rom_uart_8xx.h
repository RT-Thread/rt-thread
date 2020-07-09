/*
 * @brief LPC8xx UART ROM API declarations and functions
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

#ifndef __ROM_UART_8XX_H_
#define __ROM_UART_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup UARTROM_8XX CHIP: LPC8xx UART ROM API declarations and functions
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief UART ROM driver - UART errors in UART configuration used in uart_init function
 */
#define OVERRUN_ERR_EN		(1 << 0)	/*!< Bit 0: Enable overrun error */
#define UNDERRUN_ERR_EN		(1 << 1)	/*!< Bit 1: Enable underrun error */
#define FRAME_ERR_EN		(1 << 2)	/*!< Bit 2: enable frame error */
#define PARITY_ERR_EN		(1 << 3)	/*!< Bit 3: enable parity error */
#define RXNOISE_ERR_EN		(1 << 4)	/*!< Bit 4: enable receive noise error */

/**
 * Macros for UART errors
 */
/*!< Enable all the UART errors */
#define ALL_ERR_EN			(OVERRUN_ERR_EN | UNDERRUN_ERR_EN | FRAME_ERR_EN | PARITY_ERR_EN | \
							 RXNOISE_ERR_EN)
/*!< Disable all the errors */
#define NO_ERR_EN			(0)

/**
 * Transfer mode values in UART parameter structure.
 * Used in uart_get_line & uart_put_line function
 */
/*!< 0x00: uart_get_line: stop transfer when the buffer is full */
/*!< 0x00: uart_put_line: stop transfer when the buffer is empty */
#define TX_MODE_BUF_EMPTY		(0x00)
#define RX_MODE_BUF_FULL		(0x00)
/*!< 0x01: uart_get_line: stop transfer when CRLF are received */
/*!< 0x01: uart_put_line: transfer stopped after reaching \0 and CRLF is sent out after that */
#define TX_MODE_SZERO_SEND_CRLF	(0x01)
#define RX_MODE_CRLF_RECVD		(0x01)
/*!< 0x02: uart_get_line: stop transfer when LF are received */
/*!< 0x02: uart_put_line: transfer stopped after reaching \0. And LF is sent out after that */
#define TX_MODE_SZERO_SEND_LF	(0x02)
#define RX_MODE_LF_RECVD		(0x02)
/*!< 0x03: uart_get_line: RESERVED */
/*!< 0x03: uart_put_line: transfer stopped after reaching \0 */
#define TX_MODE_SZERO			(0x03)

/**
 * @brief UART ROM driver modes
 */
#define DRIVER_MODE_POLLING		(0x00)	/*!< Polling mode */
#define DRIVER_MODE_INTERRUPT	(0x01)	/*!< Interrupt mode */
#define DRIVER_MODE_DMA			(0x02)	/*!< DMA mode */

/**
 * @brief UART ROM driver UART handle
 */
typedef void UART_HANDLE_T;

/**
 * @brief UART ROM driver UART callback function
 */
typedef void (*UART_CALLBK_T)(uint32_t err_code, uint32_t n);

/**
 * @brief UART ROM driver UART DMA callback function
 */
typedef void (*UART_DMA_REQ_T)(uint32_t src_adr, uint32_t dst_adr, uint32_t size);

/**
 * @brief UART ROM driver configutaion structure
 */
typedef struct {
	uint32_t sys_clk_in_hz;		/*!< main clock in Hz */
	uint32_t baudrate_in_hz;	/*!< Baud rate in Hz */
	uint8_t  config;			/*!< Configuration value */
								/*!<  bit1:0  Data Length: 00: 7 bits length, 01: 8 bits length, others: reserved */
								/*!<  bit3:2  Parity: 00: No Parity, 01: reserved, 10: Even, 11: Odd */
								/*!<  bit4:   Stop Bit(s): 0: 1 Stop bit, 1: 2 Stop bits */
	uint8_t sync_mod;			/*!< Sync mode settings */
								/*!<  bit0:  Mode: 0: Asynchronous mode, 1: Synchronous  mode */
								/*!<  bit1:  0: Un_RXD is sampled on the falling edge of SCLK */
								/*!<         1: Un_RXD is sampled on the rising edge of SCLK */
								/*!<  bit2:  0: Start and stop bits are transmitted as in asynchronous mode) */
								/*!<         1: Start and stop bits are not transmitted) */
								/*!<  bit3:  0: The UART is a  slave in Synchronous mode */
								/*!<         1: The UART is a master in Synchronous mode */
	uint16_t error_en;			/*!< Errors to be enabled */
								/*!<  bit0: Overrun Errors Enabled */
								/*!<  bit1: Underrun Errors Enabled */
								/*!<  bit2: FrameErr Errors Enabled */
								/*!<  bit3: ParityErr Errors Enabled */
								/*!<  bit4: RxNoise Errors Enabled */
} UART_CONFIG_T;

/**
 * @brief UART ROM driver parameter structure
 */
typedef struct {
	uint8_t         *buffer;		/*!< Pointer to data buffer */
	uint32_t        size;			/*!< Size of the buffer */
	uint16_t        transfer_mode;	/*!< Transfer mode settings */
									/*!<   0x00: uart_get_line: stop transfer when the buffer is full */
									/*!<   0x00: uart_put_line: stop transfer when the buffer is empty */
									/*!<   0x01: uart_get_line: stop transfer when CRLF are received */
									/*!<   0x01: uart_put_line: transfer stopped after reaching \0 and CRLF is sent out after that */
									/*!<   0x02: uart_get_line: stop transfer when LF are received */
									/*!<   0x02: uart_put_line: transfer stopped after reaching \0 and LF is sent out after that */
									/*!<   0x03: uart_get_line: RESERVED */
									/*!<   0x03: uart_put_line: transfer stopped after reaching \0 */
	uint16_t        driver_mode;	/*!< Driver mode */
									/*!<  0x00: Polling mode, function blocked until transfer completes */
									/*!<  0x01: Interrupt mode, function immediately returns, callback invoked when transfer completes */
									/*!<  0x02: DMA mode, in case DMA block is available, DMA req function is called for UART DMA channel setup, then callback function indicate that transfer completes */
	UART_CALLBK_T   callback_func_pt;	/*!< callback function pointer */
	UART_DMA_REQ_T  dma_req_func_pt;	/*!< UART DMA channel setup function pointer, not applicable on LPC8xx */
} UART_PARAM_T;

/**
 * @brief UART ROM driver APIs structure
 */
typedef struct UARTD_API {
	/*!< UART Configuration functions */
	uint32_t        (*uart_get_mem_size)(void);	/*!< Get the memory size needed by one Min UART instance */
	UART_HANDLE_T * (*uart_setup)(uint32_t base_addr, uint8_t * ram);	/*!< Setup Min UART instance with provided memory and return the handle to this instance */
	uint32_t        (*uart_init)(UART_HANDLE_T *handle, UART_CONFIG_T *set);	/*!< Setup baud rate and operation mode for uart, then enable uart */

	/*!< UART polling functions block until completed */
	uint8_t         (*uart_get_char)(UART_HANDLE_T *handle);	/*!< Receive one Char from uart. This functions is only returned after Char is received. In case Echo is enabled, the received data is sent out immediately */
	void            (*uart_put_char)(UART_HANDLE_T *handle, uint8_t data);	/*!< Send one Char through uart. This function is only returned after data is sent */
	uint32_t        (*uart_get_line)(UART_HANDLE_T *handle, UART_PARAM_T *param);	/*!< Receive multiple bytes from UART */
	uint32_t        (*uart_put_line)(UART_HANDLE_T *handle, UART_PARAM_T *param);	/*!< Send string (end with \0) or raw data through UART */

	/*!< UART interrupt functions return immediately and callback when completed */
	void            (*uart_isr)(UART_HANDLE_T *handle);	/*!< UART interrupt service routine. To use this routine, the corresponding USART interrupt must be enabled. This function is invoked by the user ISR */
} UARTD_API_T;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROM_UART_8XX_H_ */
