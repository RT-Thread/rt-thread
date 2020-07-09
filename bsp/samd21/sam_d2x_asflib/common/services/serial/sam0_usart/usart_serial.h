/**
 * \file
 *
 * \brief USART Serial wrapper service for the SAM D/L/C/R devices.
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
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
#ifndef _USART_SERIAL_H_
#define _USART_SERIAL_H_

#include "compiler.h"
#include "status_codes.h"
#include "usart.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \name Serial Management Configuration */

typedef Sercom * usart_inst_t;

//struct usart_module usart;

/*! \brief Initializes the Usart in serial mode.
 *
 * \param[in,out] module  Software instance of the USART to initialize.
 * \param[in]     hw      Base address of the hardware USART.
 * \param[in]     config  Configuration settings for the USART.
 *
 * \retval true if the initialization was successful
 * \retval false if initialization failed (error in baud rate calculation)
 */
static inline bool usart_serial_init(
		struct usart_module *const module,
		usart_inst_t const hw,
		const struct usart_config *const config)
{
	if (usart_init(module, hw, config) == STATUS_OK) {
		return true;
	}
	else {
		return false;
	}
}

/** \brief Sends a character with the USART.
 *
 * \param[in,out] module  Software instance of the USART.
 * \param[in]     c       Character to write.
 *
 * \return Status code
 */
static inline enum status_code usart_serial_putchar(
		struct usart_module *const module,
		uint8_t c)
{
	while(STATUS_OK !=usart_write_wait(module, c));

	return STATUS_OK;
}

/** \brief Waits until a character is received, and returns it.
 *
 * \param[in,out] module  Software instance of the USART.
 * \param[out]    c       Destination for the read character.
 */
static inline void usart_serial_getchar(
		struct usart_module *const module,
		uint8_t *c)
{
	uint16_t temp = 0;

	while(STATUS_OK != usart_read_wait(module, &temp));

	*c = temp;
}

/**
 * \brief Send a sequence of bytes to USART device
 *
 * \param[in,out] module   Software instance of the USART.
 * \param[in]     tx_data  Data buffer to read the data to write from.
 * \param[in]     length   Length of data to write.
 */
static inline enum status_code usart_serial_write_packet(
		struct usart_module *const module,
		const uint8_t *tx_data,
		uint16_t length)
{
	return usart_write_buffer_wait(module, tx_data, length);
}

/**
 * \brief Receive a sequence of bytes from USART device
 *
 * \param[in,out] module   Software instance of the USART.
 * \param[out]    rx_data  Data buffer to store the read data into.
 * \param[in]     length   Length of data to read.
 */
static inline enum status_code usart_serial_read_packet(
		struct usart_module *const module,
		uint8_t *rx_data,
		uint16_t length)
{
	return usart_read_buffer_wait(module, rx_data, length);
}

#ifdef __cplusplus
}
#endif

#endif  // _USART_SERIAL_H_
