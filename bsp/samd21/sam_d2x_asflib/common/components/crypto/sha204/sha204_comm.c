/*
 * \file
 *
 * \brief ATSHA204 file that implements the communication layer for the device
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

#include "sha204_comm.h"                //!< definitions and declarations for the Communication module
#include "sha204_timer.h"               //!< definitions for timer functions
#include "sha204_lib_return_codes.h"    //!< declarations of function return codes

uint8_t sha204c_check_crc(uint8_t *response);
uint8_t sha204c_resync(uint8_t size, uint8_t *response);

/** \brief This function calculates CRC.
 *
 * \param[in] length number of bytes in buffer
 * \param[in] data pointer to data for which CRC should be calculated
 * \param[out] crc pointer to 16-bit CRC
 */
void sha204c_calculate_crc(uint8_t length, uint8_t *data, uint8_t *crc) {
	uint8_t counter;
	uint16_t crc_register = 0;
	uint16_t polynom = 0x8005;
	uint8_t shift_register;
	uint8_t data_bit, crc_bit;

	for (counter = 0; counter < length; counter++) {
	  for (shift_register = 0x01; shift_register > 0x00; shift_register <<= 1) {
		 data_bit = (data[counter] & shift_register) ? 1 : 0;
		 crc_bit = crc_register >> 15;

		 // Shift CRC to the left by 1.
		 crc_register <<= 1;

		 if ((data_bit ^ crc_bit) != 0)
			crc_register ^= polynom;
	  }
	}
	crc[0] = (uint8_t) (crc_register & 0x00FF);
	crc[1] = (uint8_t) (crc_register >> 8);
}


/** \brief This function checks the consistency of a response.
 * \param[in] response pointer to response
 * \return status of the consistency check
 */
uint8_t sha204c_check_crc(uint8_t *response)
{
	uint8_t crc[SHA204_CRC_SIZE];
	uint8_t count = response[SHA204_BUFFER_POS_COUNT];

	count -= SHA204_CRC_SIZE;
	sha204c_calculate_crc(count, response, crc);

	return (crc[0] == response[count] && crc[1] == response[count + 1])
		? SHA204_SUCCESS : SHA204_BAD_CRC;
}


/** \brief This function wakes up a SHA204 device
 *         and receives a response.
 *  \param[out] response pointer to four-byte response
 *  \return status of the operation
 */
uint8_t sha204c_wakeup(uint8_t *response)
{
	uint8_t ret_code = sha204p_wakeup();
	if (ret_code != SHA204_SUCCESS)
		return ret_code;

	ret_code = sha204p_receive_response(SHA204_RSP_SIZE_MIN, response);
	if (ret_code != SHA204_SUCCESS)
		return ret_code;

	// Verify status response.
	if (response[SHA204_BUFFER_POS_COUNT] != SHA204_RSP_SIZE_MIN)
		ret_code = SHA204_INVALID_SIZE;
	else if (response[SHA204_BUFFER_POS_STATUS] != SHA204_STATUS_BYTE_WAKEUP)
		ret_code = SHA204_COMM_FAIL;
	else {
		if ((response[SHA204_RSP_SIZE_MIN - SHA204_CRC_SIZE] != 0x33)
					|| (response[SHA204_RSP_SIZE_MIN + 1 - SHA204_CRC_SIZE] != 0x43))
			ret_code = SHA204_BAD_CRC;
	}
	if (ret_code != SHA204_SUCCESS)
		sha204h_delay_ms(SHA204_COMMAND_EXEC_MAX);

	return ret_code;
}


/** \brief This function re-synchronizes communication.
 *
  Be aware that succeeding only after waking up the
  device could mean that it had gone to sleep and lost
  its TempKey in the process.\n
  Re-synchronizing communication is done in a maximum of
  three steps:
  <ol>
    <li>
      Try to re-synchronize without sending a Wake token.
      This step is implemented in the Physical layer.
    </li>
    <li>
      If the first step did not succeed send a Wake token.
    </li>
    <li>
      Try to read the Wake response.
    </li>
  </ol>
 *
 * \param[in] size size of response buffer
 * \param[out] response pointer to Wake-up response buffer
 * \return status of the operation
 */
uint8_t sha204c_resync(uint8_t size, uint8_t *response)
{
	// Try to re-synchronize without sending a Wake token
	// (step 1 of the re-synchronization process).
	uint8_t ret_code = sha204p_resync(size, response);
	if (ret_code == SHA204_SUCCESS)
		return ret_code;

	// We lost communication. Send a Wake pulse and try
	// to receive a response (steps 2 and 3 of the
	// re-synchronization process).
	(void) sha204p_sleep();
	ret_code = sha204c_wakeup(response);

	// Translate a return value of success into one
	// that indicates that the device had to be woken up
	// and might have lost its TempKey.
	return (ret_code == SHA204_SUCCESS ? SHA204_RESYNC_WITH_WAKEUP : ret_code);
}


/** \brief This function runs a communication sequence:
 * Append CRC to tx buffer, send command, delay, and verify response after receiving it.
 *
 * The first byte in tx buffer must be the byte count of the packet.
 * If CRC or count of the response is incorrect, or a command byte got "nacked" (TWI),
 * this function requests re-sending the response.
 * If the response contains an error status, this function resends the command.
 *
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204c_send_and_receive(struct sha204_send_and_receive_parameters *args)
{
	uint8_t ret_code = SHA204_FUNC_FAIL;
	uint8_t ret_code_resync;
	uint8_t n_retries_send;
	uint8_t n_retries_receive;
	uint8_t i;
	uint8_t status_byte;
	uint8_t count = args->tx_buffer[SHA204_BUFFER_POS_COUNT];
	uint8_t count_minus_crc = count - SHA204_CRC_SIZE;

	// Append CRC.
	sha204c_calculate_crc(count_minus_crc, args->tx_buffer, args->tx_buffer + count_minus_crc);

	// Retry loop for sending a command and receiving a response.
	n_retries_send = SHA204_RETRY_COUNT + 1;

	while ((n_retries_send-- > 0) && (ret_code != SHA204_SUCCESS)) {

		// Send command.
		ret_code = sha204p_send_command(count, args->tx_buffer);
		if (ret_code != SHA204_SUCCESS) {
			if (sha204c_resync(args->rx_size, args->rx_buffer) == SHA204_RX_NO_RESPONSE)
				// The device seems to be dead in the water.
				return ret_code;
			else
				continue;
		}

		// Wait typical command execution time and then start polling for a response.
		sha204h_delay_ms(args->poll_delay);

		// Retry loop for receiving a response.
		n_retries_receive = SHA204_RETRY_COUNT + 1;
		while (n_retries_receive-- > 0) {

			// Reset response buffer.
			for (i = 0; i < args->rx_size; i++)
				args->rx_buffer[i] = 0;

			sha204h_start_timeout_timer_ms(args->poll_timeout);
			do {
				ret_code = sha204p_receive_response(args->rx_size, args->rx_buffer);
			} while (!sha204_timer_expired && (ret_code == SHA204_RX_NO_RESPONSE));

			if (ret_code == SHA204_RX_NO_RESPONSE) {
				// We did not receive a response. Re-synchronize and send command again.
				if (sha204c_resync(args->rx_size, args->rx_buffer) == SHA204_RX_NO_RESPONSE)
					// The device seems to be dead in the water.
					return ret_code;
				else
					break;
			}

			// Check whether we received a valid response.
			if (ret_code == SHA204_INVALID_SIZE) {
				// We see 0xFF for the count when communication got out of sync.
				ret_code_resync = sha204c_resync(args->rx_size, args->rx_buffer);
				if (ret_code_resync == SHA204_SUCCESS)
					// We did not have to wake up the device. Try receiving response again.
					continue;
				if (ret_code_resync == SHA204_RESYNC_WITH_WAKEUP)
					// We could re-synchronize, but only after waking up the device.
					// Re-send command.
					break;
				else
					// We failed to re-synchronize.
					return ret_code;
			}

			// We received a response of valid size.
			// Check the consistency of the response.
			ret_code = sha204c_check_crc(args->rx_buffer);
			if (ret_code == SHA204_SUCCESS) {
				// Received valid response.
				if (args->rx_buffer[SHA204_BUFFER_POS_COUNT] > SHA204_RSP_SIZE_MIN)
					// Received non-status response. We are done.
					return ret_code;

				// Received status response.
				status_byte = args->rx_buffer[SHA204_BUFFER_POS_STATUS];

				// Translate the three possible device status error codes
				// into library return codes.
				if (status_byte == SHA204_STATUS_BYTE_PARSE)
					return SHA204_PARSE_ERROR;
				if (status_byte == SHA204_STATUS_BYTE_EXEC)
					return SHA204_CMD_FAIL;
				if (status_byte == SHA204_STATUS_BYTE_COMM) {
					// In case of the device status byte indicating a communication
					// error this function exits the retry loop for receiving a response
					// and enters the overall retry loop
					// (send command / receive response).
					ret_code = SHA204_STATUS_CRC;
					break;
				}

				// Received status response from CheckMAC, DeriveKey, GenDig,
				// Lock, Nonce, Pause, UpdateExtra, or Write command.
				return ret_code;
			}

			else {
				// Received response with incorrect CRC.
				ret_code_resync = sha204c_resync(args->rx_size, args->rx_buffer);
				if (ret_code_resync == SHA204_SUCCESS)
					// We did not have to wake up the device. Try receiving response again.
					continue;
				if (ret_code_resync == SHA204_RESYNC_WITH_WAKEUP)
					// We could re-synchronize, but only after waking up the device.
					// Re-send command.
					break;
				else
					// We failed to re-synchronize.
					return ret_code;
			} // block end of check response consistency

		} // block end of receive retry loop

	} // block end of send and receive retry loop

	return ret_code;
}
