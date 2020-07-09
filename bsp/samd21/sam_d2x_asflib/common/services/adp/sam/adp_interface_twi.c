/**
 * \file
 *
 * \brief ADP service implementation
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
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

#include <compiler.h>
#include <asf.h>
#include "adp_interface.h"

//! \name Embedded debugger TWI interface definitions
//@{
#define EDBG_TWI_MODULE           TWI0
//@}

#define TWI_EDBG_SLAVE_ADDR 0x28
#define TIMEOUT 1000

/**
* \brief Initialize EDBG TWI interface for SAM4S
*
*/
enum status_code adp_interface_init(void)
{
	sysclk_init();

	/* Configure the TWI interface */
	twi_master_options_t opt = {
		.speed = 100000,
		.chip  = TWI_EDBG_SLAVE_ADDR
	};
	return twi_master_setup(EDBG_TWI_MODULE, &opt);
}

/**
* \brief Send data on TWI
*
* \param[in] data   Pointer to data to send
* \param[in] length Number of bytes to send
*/
static enum status_code adp_interface_send(uint8_t* tx_buf, uint16_t length)
{
	twi_package_t packet_write = {
		.chip         = TWI_EDBG_SLAVE_ADDR, /* TWI slave bus address */
		.buffer       = tx_buf,        /* transfer data source buffer */
		.length       = length               /* transfer data size (bytes) */
	};
	return twi_master_write(EDBG_TWI_MODULE, &packet_write);
}

/**
* \brief Read data on TWI
*
* \param[out] data   Pointer to place received data
* \param[in]  length Number of bytes to receive
*/
enum status_code adp_interface_read_response(uint8_t *data,	uint16_t length)
{
	enum status_code status = ERR_IO_ERROR;
	uint8_t data_len = 0;
	
	twi_package_t packet_read = {
		.chip         = TWI_EDBG_SLAVE_ADDR, // TWI slave bus address
		.buffer       = &data_len,                // transfer data destination buffer
		.length       = 1               // transfer data size (bytes)
	};
	twi_master_read(EDBG_TWI_MODULE, &packet_read);
	
	if(data_len != 0){
		packet_read.length = data_len;
		packet_read.buffer = data;
		status = twi_master_read(EDBG_TWI_MODULE, &packet_read);	
	}

	return status;
}

/**
* \brief Sends and reads protocol packet data byte on I2C
*
* \param[in]  tx_buf  Pointer to send the protocol packet data
* \param[in]  length  The length of the send protocol packet data
* \param[out] rx_buf  Pointer to store the received I2C character
*/
void adp_interface_transceive_procotol(uint8_t* tx_buf, uint16_t length, uint8_t* rx_buf)
{
	adp_interface_send(tx_buf, length);
	adp_interface_read_response(rx_buf, length);
}

