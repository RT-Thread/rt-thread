/**
 * \file
 *
 * \brief Uart Serial for SAM.
 *
 * Copyright (c) 2011-2017 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef _UART_SERIAL_H_
#define _UART_SERIAL_H_

#include "compiler.h"
#include "sysclk.h"
#if (SAMG55)
#include "flexcom.h"
#endif
#if ((!SAM4L) && (!SAMG55))
#include "uart.h"
#endif
#include "usart.h"

/** 
 * \name Serial Management Configuration
 */
//! @{
#include "conf_uart_serial.h"

//! @}

/** Input parameters when initializing RS232 and similar modes. */
typedef struct uart_rs232_options {
	/** Set baud rate of the USART (unused in slave modes). */
	uint32_t baudrate;

	/** Number of bits to transmit as a character (5-bit to 9-bit). */
	uint32_t charlength;

	/**
	 * Parity type: USART_PMODE_DISABLED_gc, USART_PMODE_EVEN_gc,
	 * USART_PMODE_ODD_gc.
	 */
	uint32_t paritytype;

	/** 1, 1.5 or 2 stop bits. */
	uint32_t stopbits;

} usart_rs232_options_t;

typedef usart_rs232_options_t usart_serial_options_t;

typedef Usart *usart_if;

/** 
 * \brief Initializes the Usart in master mode.
 *
 * \param p_usart  Base address of the USART instance.
 * \param opt      Options needed to set up RS232 communication (see
 * \ref usart_options_t).
 */
static inline void usart_serial_init(usart_if p_usart,
		usart_serial_options_t *opt)
{
#if ((!SAM4L) && (!SAMG55))
	sam_uart_opt_t uart_settings;
	uart_settings.ul_mck = sysclk_get_peripheral_hz();
	uart_settings.ul_baudrate = opt->baudrate;
	uart_settings.ul_mode = opt->paritytype;
#endif

	sam_usart_opt_t usart_settings;
	usart_settings.baudrate = opt->baudrate;
	usart_settings.char_length = opt->charlength;
	usart_settings.parity_type = opt->paritytype;
	usart_settings.stop_bits= opt->stopbits;
	usart_settings.channel_mode= US_MR_CHMODE_NORMAL;
	
#ifdef UART
	if (UART == (Uart*)p_usart) {
		sysclk_enable_peripheral_clock(ID_UART);
		/* Configure UART */
		uart_init((Uart*)p_usart, &uart_settings);
	}
#else
# ifdef UART0
	if (UART0 == (Uart*)p_usart) {
		sysclk_enable_peripheral_clock(ID_UART0);
		/* Configure UART */
		uart_init((Uart*)p_usart, &uart_settings);
	}
# endif
# ifdef UART1
	if (UART1 == (Uart*)p_usart) {
		sysclk_enable_peripheral_clock(ID_UART1);
		/* Configure UART */
		uart_init((Uart*)p_usart, &uart_settings);
	}
# endif
# ifdef UART2
	if (UART2 == (Uart*)p_usart) {
		sysclk_enable_peripheral_clock(ID_UART2);
		/* Configure UART */
		uart_init((Uart*)p_usart, &uart_settings);
	}
# endif
# ifdef UART3
	if (UART3 == (Uart*)p_usart) {
		sysclk_enable_peripheral_clock(ID_UART3);
		/* Configure UART */
		uart_init((Uart*)p_usart, &uart_settings);
	}
# endif
# ifdef UART4
	if (UART4 == (Uart*)p_usart) {
		sysclk_enable_peripheral_clock(ID_UART4);
		/* Configure UART */
		uart_init((Uart*)p_usart, &uart_settings);
	}
# endif
#endif /* ifdef UART */


#ifdef USART
	if (USART == p_usart) {
#if (!SAM4L)
		sysclk_enable_peripheral_clock(ID_USART);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
#else
# ifdef USART0
	if (USART0 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM0);
		flexcom_set_opmode(FLEXCOM0, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART0);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART1
	if (USART1 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM1);
		flexcom_set_opmode(FLEXCOM1, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART1);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART2
	if (USART2 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM2);
		flexcom_set_opmode(FLEXCOM2, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART2);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART3
	if (USART3 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM3);
		flexcom_set_opmode(FLEXCOM3, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART3);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART4
	if (USART4 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM4);
		flexcom_set_opmode(FLEXCOM4, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART4);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART5
	if (USART5 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM5);
		flexcom_set_opmode(FLEXCOM5, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART5);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART6
	if (USART6 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM6);
		flexcom_set_opmode(FLEXCOM6, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART6);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif
# ifdef USART7
	if (USART7 == p_usart) {
#if (!SAM4L)
#if (SAMG55)
		flexcom_enable(FLEXCOM7);
		flexcom_set_opmode(FLEXCOM7, FLEXCOM_USART);
#else
		sysclk_enable_peripheral_clock(ID_USART7);
#endif
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_hz());
#endif
#if (SAM4L)
		sysclk_enable_peripheral_clock(p_usart);
		/* Configure USART */
		usart_init_rs232(p_usart, &usart_settings,
				sysclk_get_peripheral_bus_hz(p_usart));
#endif
		/* Enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);
	}
# endif

#endif /* ifdef USART */

}

/**
 * \brief Sends a character with the USART.
 *
 * \param p_usart   Base address of the USART instance.
 * \param c       Character to write.
 *
 * \return Status.
 *   \retval 1  The character was written.
 *   \retval 0  The function timed out before the USART transmitter became
 * ready to send.
 */
static inline int usart_serial_putchar(usart_if p_usart, const uint8_t c)
{
#ifdef UART
	if (UART == (Uart*)p_usart) {
		while (uart_write((Uart*)p_usart, c)!=0);
		return 1;
	}
#else
# ifdef UART0
	if (UART0 == (Uart*)p_usart) {
		while (uart_write((Uart*)p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef UART1
	if (UART1 == (Uart*)p_usart) {
		while (uart_write((Uart*)p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef UART2
	if (UART2 == (Uart*)p_usart) {
		while (uart_write((Uart*)p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef UART3
	if (UART3 == (Uart*)p_usart) {
		while (uart_write((Uart*)p_usart, c)!=0);
		return 1;
	}
# endif
#endif /* ifdef UART */


#ifdef USART
	if (USART == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
#else
# ifdef USART0
	if (USART0 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART1
	if (USART1 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART2
	if (USART2 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART3
	if (USART3 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART4
	if (USART4 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART5
	if (USART5 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART6
	if (USART6 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
# ifdef USART7
	if (USART7 == p_usart) {
		while (usart_write(p_usart, c)!=0);
		return 1;
	}
# endif
#endif /* ifdef USART */

	return 0;
}
/**
 * \brief Waits until a character is received, and returns it.
 *
 * \param p_usart   Base address of the USART instance.
 * \param data   Data to read
 *
 */
static inline void usart_serial_getchar(usart_if p_usart, uint8_t *data)
{
	uint32_t val = 0;

	/* Avoid Cppcheck Warning */
	UNUSED(val);

#ifdef UART
	if (UART == (Uart*)p_usart) {
		while (uart_read((Uart*)p_usart, data));
	}
#else
# ifdef UART0
	if (UART0 == (Uart*)p_usart) {
		while (uart_read((Uart*)p_usart, data));
	}
# endif
# ifdef UART1
	if (UART1 == (Uart*)p_usart) {
		while (uart_read((Uart*)p_usart, data));
	}
# endif
# ifdef UART2
	if (UART2 == (Uart*)p_usart) {
		while (uart_read((Uart*)p_usart, data));
	}
# endif
# ifdef UART3
	if (UART3 == (Uart*)p_usart) {
		while (uart_read((Uart*)p_usart, data));
	}
# endif
#endif /* ifdef UART */


#ifdef USART
	if (USART == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
#else
# ifdef USART0
	if (USART0 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART1
	if (USART1 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART2
	if (USART2 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART3
	if (USART3 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART4
	if (USART4 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART5
	if (USART5 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART6
	if (USART6 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
# ifdef USART7
	if (USART7 == p_usart) {
		while (usart_read(p_usart, &val));
		*data = (uint8_t)(val & 0xFF);
	}
# endif
#endif /* ifdef USART */

}

/**
 * \brief Check if Received data is ready.
 *
 * \param p_usart   Base address of the USART instance.
 *
 * \retval 1 One data has been received.
 * \retval 0 No data has been received.
 */
static inline uint32_t usart_serial_is_rx_ready(usart_if p_usart)
{
#ifdef UART
	if (UART == (Uart*)p_usart) {
		return uart_is_rx_ready((Uart*)p_usart);
	}
#else
# ifdef UART0
	if (UART0 == (Uart*)p_usart) {
		return uart_is_rx_ready((Uart*)p_usart);
	}
# endif
# ifdef UART1
	if (UART1 == (Uart*)p_usart) {
		return uart_is_rx_ready((Uart*)p_usart);
	}
# endif
# ifdef UART2
	if (UART2 == (Uart*)p_usart) {
		return uart_is_rx_ready((Uart*)p_usart);
	}
# endif
# ifdef UART3
	if (UART3 == (Uart*)p_usart) {
		return uart_is_rx_ready((Uart*)p_usart);
	}
# endif
#endif /* ifdef UART */


#ifdef USART
	if (USART == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
#else
# ifdef USART0
	if (USART0 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART1
	if (USART1 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART2
	if (USART2 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART3
	if (USART3 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART4
	if (USART4 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART5
	if (USART5 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART6
	if (USART6 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
# ifdef USART7
	if (USART7 == p_usart) {
		return usart_is_rx_ready(p_usart);
	}
# endif
#endif /* ifdef USART */

	return 0;
}

/**
 * \brief Send a sequence of bytes to a USART device
 *
 * \param usart Base address of the USART instance.
 * \param data   data buffer to write
 * \param len    Length of data
 *
 */
status_code_t usart_serial_write_packet(usart_if usart, const uint8_t *data,
		size_t len);

/**
 * \brief Receive a sequence of bytes to a USART device
 *
 * \param usart Base address of the USART instance.
 * \param data   data buffer to write
 * \param len    Length of data
 *
 */
status_code_t usart_serial_read_packet(usart_if usart, uint8_t *data,
		size_t len);

#endif  /* _UART_SERIAL_H_ */
