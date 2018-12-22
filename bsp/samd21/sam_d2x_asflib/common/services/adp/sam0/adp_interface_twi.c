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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <compiler.h>
#include <system.h>

#include <asf.h>
#include <adp_interface.h>

#define EDBG_TWI EDBG_I2C_MODULE
#define TWI_EDBG_SLAVE_ADDR 0x28
#define TIMEOUT 1000

struct i2c_master_module i2c_master_instance;

/**
* \brief Initialize EDBG I2C communication for SAM0
*
*/
enum status_code adp_interface_init(void)
{
	enum status_code return_value;

	system_init();

	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	config_i2c_master.buffer_timeout = 10000;
	return_value = i2c_master_init(&i2c_master_instance, EDBG_TWI, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
	return return_value;
}

static enum status_code adp_interface_send(uint8_t* tx_buf, uint16_t length)
{
	enum status_code status;
	
	struct i2c_master_packet packet = {
		.address = TWI_EDBG_SLAVE_ADDR,
		.data_length = length,
		.data = tx_buf,
	};
	/* Send data to PC */
	status = i2c_master_write_packet_wait(&i2c_master_instance, &packet);
	
	return status;
}

/**
* \brief Read response on I2C from PC
*
* return Status
* \param[in]  rx_buf  Pointer to receive the data
* \param[in]  length  The length of the read data
* \param[out] rx_buf  Pointer to store the received SPI character
*/
enum status_code adp_interface_read_response(uint8_t* rx_buf, uint16_t length)
{
	enum status_code status = STATUS_ERR_IO;
	uint8_t data_len = 0;

	struct i2c_master_packet packet = {
		.address = TWI_EDBG_SLAVE_ADDR,
		.data_length = 1,
		.data = &data_len,
	};
	i2c_master_read_packet_wait(&i2c_master_instance, &packet);
	
	if (data_len != 0)
	{
		packet.data_length = data_len;
		packet.data = rx_buf;
		status = i2c_master_read_packet_wait(&i2c_master_instance, &packet);
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
