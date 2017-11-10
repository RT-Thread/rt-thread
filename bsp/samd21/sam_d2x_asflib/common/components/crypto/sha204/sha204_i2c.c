/*
 * \file
 *
 * \brief ATSHA204 file that implements the I2C layer for the device
 *
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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

#include "conf_twim.h"
#include "conf_atsha204.h"
#include "twi_master.h"
#include "sha204_physical.h"            // declarations that are common to all interface implementations
#include "sha204_lib_return_codes.h"    // declarations of function return codes
#include "sha204_timer.h"               // definitions for delay functions

/** 
 * \brief This enumeration lists all packet types sent to a SHA204 device.
 *
 * The following byte stream is sent to a SHA204 TWI device:
 *    {I2C start} {I2C address} {word address} [{data}] {I2C stop}.
 * Data are only sent after a word address of value #SHA204_I2C_PACKET_FUNCTION_NORMAL.
 */
enum i2c_word_address {
	SHA204_I2C_PACKET_FUNCTION_RESET,  //!< Reset device.
	SHA204_I2C_PACKET_FUNCTION_SLEEP,  //!< Put device into Sleep mode.
	SHA204_I2C_PACKET_FUNCTION_IDLE,   //!< Put device into Idle mode.
	SHA204_I2C_PACKET_FUNCTION_NORMAL  //!< Write / evaluate data that follow this word address byte.
};


//! I2C address can be changed by calling #sha204p_set_device_id.
static uint8_t device_address = SHA204_I2C_DEFAULT_ADDRESS >> 1;


/** \brief This function initializes peripherals (timer and communication).
 */
void sha204p_init(void)
{
	// Initialize timer.
	sha204h_timer_init();

	// Initialize interrupt vectors.
	irq_initialize_vectors();

	// Enable interrupts.
	cpu_irq_enable();
}


/** 
 * \brief This I2C function sets the I2C address.
 *         Communication functions will use this address.
 *
 *  \param[in] id I2C address
 */
void sha204p_set_device_id(uint8_t id)
{
	device_address = id >> 1;
}


/** 
 * \brief This I2C function generates a Wake-up pulse and delays.
 * \return status of the operation
 */
uint8_t sha204p_wakeup(void)
{
	twi_package_t twi_package;
	twi_options_t twi_options = {.speed = 133333};
   
	// Set SDA low for 60 us. Speed is therefore: f = 1 / 0.00006 / 8 = 133,333.
	// Generating the Stop condition adds 20 us for this particular implementation / target,
	// but a longer wake pulse is okay.
	twi_master_disable(ATSHA204_TWI_PORT);
	int twi_master_setup_status = twi_master_setup(ATSHA204_TWI_PORT, &twi_options);
	if (twi_master_setup_status != STATUS_OK)
		return SHA204_COMM_FAIL;

	twi_package.chip = 0;
	twi_package.addr_length = 0;
	twi_package.length = 0;
	twi_package.buffer = NULL;

	// This call will return a nack error.
	(void) twi_master_write(ATSHA204_TWI_PORT, &twi_package);

	sha204h_delay_ms(SHA204_WAKEUP_DELAY);
	
	// Set I2C speed back to communication speed.
	twi_master_enable(ATSHA204_TWI_PORT);
	twi_options.speed = ATSHA204_TWI_SPEED;
	return (uint8_t) twi_master_setup(ATSHA204_TWI_PORT, &twi_options);
}


/** 
 * \brief This function sends a I2C packet enclosed by a I2C start and stop to a SHA204 device.
 *
 *         This function combines a I2C packet send sequence that is common to all packet types.
 *         Only if word_address is \ref SHA204_I2C_PACKET_FUNCTION_NORMAL, count and buffer parameters are
 *         expected to be non-zero.
 * \param[in] word_address packet function code listed in #i2c_word_address
 * \param[in] count number of bytes in data buffer
 * \param[in] buffer pointer to data buffer
 * \return status of the operation
 */
static uint8_t sha204p_send(uint8_t word_address, uint8_t count, uint8_t *buffer)
{
	twi_package_t twi_package = {
		.chip = device_address,
		.addr_length = 1,
		.length = count,
		.buffer = (void *) buffer,
		.addr[0] = word_address
	};
	return (twi_master_write(ATSHA204_TWI_PORT, &twi_package) ? SHA204_COMM_FAIL : SHA204_SUCCESS);
}


/** 
 * \brief This I2C function sends a command to the device.
 * \param[in] count number of bytes to send
 * \param[in] command pointer to command buffer
 * \return status of the operation
 */
uint8_t sha204p_send_command(uint8_t count, uint8_t *command)
{
	return sha204p_send(SHA204_I2C_PACKET_FUNCTION_NORMAL, count, command);
}


/** 
 * \brief This I2C function puts the SHA204 device into idle state.
 * \return status of the operation
 */
uint8_t sha204p_idle(void)
{
	return sha204p_send(SHA204_I2C_PACKET_FUNCTION_IDLE, 0, NULL);
}


/** 
 * \brief This I2C function puts the SHA204 device into low-power state.
 * \return status of the operation
 */
uint8_t sha204p_sleep(void)
{
	return sha204p_send(SHA204_I2C_PACKET_FUNCTION_SLEEP, 0, NULL);
}


/** 
 * \brief This I2C function resets the I/O buffer of the SHA204 device.
 * \return status of the operation
 */
uint8_t sha204p_reset_io(void)
{
	return sha204p_send(SHA204_I2C_PACKET_FUNCTION_RESET, 0, NULL);
}


/** 
 * \brief This I2C function receives a response from the SHA204 device.
 *
 * \param[in] size size of receive buffer
 * \param[out] response pointer to receive buffer
 * \return status of the operation
 */
uint8_t sha204p_receive_response(uint8_t size, uint8_t *response)
{
    // Read count.
	twi_package_t twi_package = {
		.chip = device_address,
		.addr_length = 0,
		.length = 1,
		.buffer = (void *) response
	};
	status_code_t i2c_status = twi_master_read(ATSHA204_TWI_PORT, &twi_package);
	if (i2c_status != STATUS_OK)
	    return (i2c_status == ERR_TIMEOUT ? SHA204_TIMEOUT : SHA204_RX_NO_RESPONSE);

	uint8_t count = response[SHA204_BUFFER_POS_COUNT];
	if ((count < SHA204_RSP_SIZE_MIN) || (count > SHA204_RSP_SIZE_MAX))
		return SHA204_INVALID_SIZE;
	   
	// Read packet remainder.
    twi_package.length = (count > size) ? size : count;
    twi_package.length--;
    twi_package.buffer = response + 1;
    return (twi_master_read(ATSHA204_TWI_PORT, &twi_package) ? SHA204_COMM_FAIL : SHA204_SUCCESS);
}


/** 
 * \brief This I2C function resynchronizes communication.
 *
 * Parameters are not used for I2C.\n
 * Re-synchronizing communication is done in a maximum of three steps
 * listed below. This function implements the first step. Since
 * steps 2 and 3 (sending a Wake-up token and reading the response)
 * are the same for I2C and SWI, they are
 * implemented in the communication layer (\ref sha204c_resync).
 * See the excerpt from the SHA204 data sheet below.
  <ol>
     <li>
       To ensure an IO channel reset, the system should send
       the standard I2C software reset sequence, as follows:
       <ul>
         <li>a Start condition</li>
         <li>nine cycles of SCL, with SDA held high</li>
         <li>another Start condition</li>
         <li>a Stop condition</li>
       </ul>
       It should then be possible to send a read sequence and
       if synchronization has completed properly the ATSHA204 will
       acknowledge the device address. The chip may return data or
       may leave the bus floating (which the system will interpret
       as a data value of 0xFF) during the data periods.\n
       If the chip does acknowledge the device address, the system
       should reset the internal address counter to force the
       ATSHA204 to ignore any partial input command that may have
       been sent. This can be accomplished by sending a write
       sequence to word address 0x00 (Reset), followed by a
       Stop condition.
     </li>
     <li>
       If the chip does NOT respond to the device address with an ACK,
       then it may be asleep. In this case, the system should send a
       complete Wake token and wait t_whi after the rising edge. The
       system may then send another read sequence and if synchronization
       has completed the chip will acknowledge the device address.
     </li>
     <li>
       If the chip still does not respond to the device address with
       an acknowledge, then it may be busy executing a command. The
       system should wait the longest TEXEC and then send the
       read sequence, which will be acknowledged by the chip.
     </li>
  </ol>
 * \param[in] size size of response buffer
 * \param[out] response pointer to response buffer
 * \return status of the operation
 */
uint8_t sha204p_resync(uint8_t size, uint8_t *response)
{
	// Generate Start, nine clocks, Stop.
	// (Adding a Repeat Start before the Stop would additionally
	// prevent erroneously writing a byte, but a Stop right after a
	// Start is not "legal" for I2C and the SHA204 will not write
	// anything without a successful CRC check.)
	twi_package_t twi_package = {
		.chip = (uint8_t) 0xFF,
		.addr_length = 1,
		.length = 0,
		.buffer = (void *) response,
		.addr[0] = 0
	};
	(void) twi_master_read(ATSHA204_TWI_PORT, &twi_package);

	return sha204p_reset_io();
}
