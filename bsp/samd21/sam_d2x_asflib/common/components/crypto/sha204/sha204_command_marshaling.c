/*
 * \file
 *
 * \brief ATSHA204 file that implements the command marshaling layer for the device
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

#include <string.h>                    // needed for memcpy()

#include "sha204_lib_return_codes.h"   // declarations of function return codes
#include "sha204_command_marshaling.h"    // definitions and declarations for the Command module

/** \brief This function checks the parameters for sha204m_execute().
 *
 * \param[in, out] args pointer to parameter structure
 * \return status of the operation
 */
static uint8_t sha204m_check_parameters(struct sha204_command_parameters *args)
{
#ifdef SHA204_CHECK_PARAMETERS

	uint8_t len = args->data_len_1 + args->data_len_2 + args->data_len_3 + SHA204_CMD_SIZE_MIN;
	if (!args->tx_buffer || args->tx_size < len || args->rx_size < SHA204_RSP_SIZE_MIN || !args->rx_buffer)
		return SHA204_BAD_PARAM;

	if ((args->data_len_1 > 0 && !args->data_1) || (args->data_len_2 > 0 && !args->data_2) || (args->data_len_3 > 0 && !args->data_3))
		return SHA204_BAD_PARAM;

	// Check parameters depending on op-code.
	switch (args->op_code) {
	case SHA204_CHECKMAC:
		if (
				// no null pointers allowed
				!args->data_1 || !args->data_2
				// No reserved bits should be set.
				|| (args->param_1 | CHECKMAC_MODE_MASK) != CHECKMAC_MODE_MASK
				// key_id > 15 not allowed
				|| args->param_2 > SHA204_KEY_ID_MAX
			)
			return SHA204_BAD_PARAM;
		break;

	case SHA204_DERIVE_KEY:
		if (((args->param_1 & ~DERIVE_KEY_RANDOM_FLAG) != 0)
					 || (args->param_2 > SHA204_KEY_ID_MAX))
			return SHA204_BAD_PARAM;
		break;

	case SHA204_DEVREV:
		break;

	case SHA204_GENDIG:
		if ((args->param_1 != GENDIG_ZONE_OTP) && (args->param_1 != GENDIG_ZONE_DATA))
			return SHA204_BAD_PARAM;
		break;

	case SHA204_HMAC:
		if ((args->param_1 & ~HMAC_MODE_MASK) != 0)
			return SHA204_BAD_PARAM;
		break;

	case SHA204_LOCK:
		if (((args->param_1 & ~LOCK_ZONE_MASK) != 0)
					|| ((args->param_1 & LOCK_ZONE_NO_CRC) && (args->param_2 != 0)))
			return SHA204_BAD_PARAM;
		break;

	case SHA204_MAC:
		if (((args->param_1 & ~MAC_MODE_MASK) != 0)
					|| (((args->param_1 & MAC_MODE_BLOCK2_TEMPKEY) == 0) && !args->data_1))
			return SHA204_BAD_PARAM;
		break;

	case SHA204_NONCE:
		if (!args->data_1
				|| (args->param_1 > NONCE_MODE_PASSTHROUGH)
				|| (args->param_1 == NONCE_MODE_INVALID)
			)
			return SHA204_BAD_PARAM;
		break;

	case SHA204_PAUSE:
		break;

	case SHA204_RANDOM:
		if (args->param_1 > RANDOM_NO_SEED_UPDATE)
			return SHA204_BAD_PARAM;
		break;

	case SHA204_READ:
		if (((args->param_1 & ~READ_ZONE_MASK) != 0)
					|| ((args->param_1 & READ_ZONE_MODE_32_BYTES) && (args->param_1 == SHA204_ZONE_OTP)))
			return SHA204_BAD_PARAM;
		break;

	case SHA204_UPDATE_EXTRA:
		if (args->param_1 > UPDATE_CONFIG_BYTE_86)
			return SHA204_BAD_PARAM;
		break;

	case SHA204_WRITE:
		if (!args->data_1 || ((args->param_1 & ~WRITE_ZONE_MASK) != 0))
			return SHA204_BAD_PARAM;
		break;

	default:
		// unknown op-code
		return SHA204_BAD_PARAM;
	}

	return SHA204_SUCCESS;

#else
	return SHA204_SUCCESS;
#endif
}


/** \brief This function creates a command packet, sends it, and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_execute(struct sha204_command_parameters *args)
{
	uint8_t *p_buffer;
	uint8_t len;
	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer
	};

	uint8_t ret_code = sha204m_check_parameters(args);
	if (ret_code != SHA204_SUCCESS)
		return ret_code;

	// Supply delays and response size.
	switch (args->op_code) {
	case SHA204_CHECKMAC:
		comm_parameters.poll_delay = CHECKMAC_DELAY;
		comm_parameters.poll_timeout = CHECKMAC_EXEC_MAX - CHECKMAC_DELAY;
		comm_parameters.rx_size = CHECKMAC_RSP_SIZE;
		break;

	case SHA204_DERIVE_KEY:
		comm_parameters.poll_delay = DERIVE_KEY_DELAY;
		comm_parameters.poll_timeout = DERIVE_KEY_EXEC_MAX - DERIVE_KEY_DELAY;
		comm_parameters.rx_size = DERIVE_KEY_RSP_SIZE;
		break;

	case SHA204_DEVREV:
		comm_parameters.poll_delay = DEVREV_DELAY;
		comm_parameters.poll_timeout = DEVREV_EXEC_MAX - DEVREV_DELAY;
		comm_parameters.rx_size = DEVREV_RSP_SIZE;
		break;

	case SHA204_GENDIG:
		comm_parameters.poll_delay = GENDIG_DELAY;
		comm_parameters.poll_timeout = GENDIG_EXEC_MAX - GENDIG_DELAY;
		comm_parameters.rx_size = GENDIG_RSP_SIZE;
		break;

	case SHA204_HMAC:
		comm_parameters.poll_delay = HMAC_DELAY;
		comm_parameters.poll_timeout = HMAC_EXEC_MAX - HMAC_DELAY;
		comm_parameters.rx_size = HMAC_RSP_SIZE;
		break;

	case SHA204_LOCK:
		comm_parameters.poll_delay = LOCK_DELAY;
		comm_parameters.poll_timeout = LOCK_EXEC_MAX - LOCK_DELAY;
		comm_parameters.rx_size = LOCK_RSP_SIZE;
		break;

	case SHA204_MAC:
		comm_parameters.poll_delay = MAC_DELAY;
		comm_parameters.poll_timeout = MAC_EXEC_MAX - MAC_DELAY;
		comm_parameters.rx_size = MAC_RSP_SIZE;
		break;

	case SHA204_NONCE:
		comm_parameters.poll_delay = NONCE_DELAY;
		comm_parameters.poll_timeout = NONCE_EXEC_MAX - NONCE_DELAY;
		comm_parameters.rx_size = args->param_1 == NONCE_MODE_PASSTHROUGH
							? NONCE_RSP_SIZE_SHORT : NONCE_RSP_SIZE_LONG;
		break;

	case SHA204_PAUSE:
		comm_parameters.poll_delay = PAUSE_DELAY;
		comm_parameters.poll_timeout = PAUSE_EXEC_MAX - PAUSE_DELAY;
		comm_parameters.rx_size = PAUSE_RSP_SIZE;
		break;

	case SHA204_RANDOM:
		comm_parameters.poll_delay = RANDOM_DELAY;
		comm_parameters.poll_timeout = RANDOM_EXEC_MAX - RANDOM_DELAY;
		comm_parameters.rx_size = RANDOM_RSP_SIZE;
		break;

	case SHA204_READ:
		comm_parameters.poll_delay = READ_DELAY;
		comm_parameters.poll_timeout = READ_EXEC_MAX - READ_DELAY;
		comm_parameters.rx_size = (args->param_1 & SHA204_ZONE_COUNT_FLAG)
							? READ_32_RSP_SIZE : READ_4_RSP_SIZE;
		break;

	case SHA204_UPDATE_EXTRA:
		comm_parameters.poll_delay = UPDATE_DELAY;
		comm_parameters.poll_timeout = UPDATE_EXEC_MAX - UPDATE_DELAY;
		comm_parameters.rx_size = UPDATE_RSP_SIZE;
		break;

	case SHA204_WRITE:
		comm_parameters.poll_delay = WRITE_DELAY;
		comm_parameters.poll_timeout = WRITE_EXEC_MAX - WRITE_DELAY;
		comm_parameters.rx_size = WRITE_RSP_SIZE;
		break;

	default:
		comm_parameters.poll_delay = 0;
		comm_parameters.poll_timeout = SHA204_COMMAND_EXEC_MAX;
		comm_parameters.rx_size = args->rx_size;
	}

	// Assemble command.
	len = args->data_len_1 + args->data_len_2 + args->data_len_3 + SHA204_CMD_SIZE_MIN;
	p_buffer = args->tx_buffer;
	*p_buffer++ = len;
	*p_buffer++ = args->op_code;
	*p_buffer++ = args->param_1;
	*p_buffer++ = args->param_2 & 0xFF;
	*p_buffer++ = args->param_2 >> 8;

	if (args->data_len_1 > 0) {
		memcpy(p_buffer, args->data_1, args->data_len_1);
		p_buffer += args->data_len_1;
	}
	if (args->data_len_2 > 0) {
		memcpy(p_buffer, args->data_2, args->data_len_2);
		p_buffer += args->data_len_2;
	}
	if (args->data_len_3 > 0) {
		memcpy(p_buffer, args->data_3, args->data_len_3);
		p_buffer += args->data_len_3;
	}

	sha204c_calculate_crc(len - SHA204_CRC_SIZE, args->tx_buffer, p_buffer);

	// Send command and receive response.
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a CheckMAC command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_check_mac(struct sha204_check_mac_parameters *args)
{
	if (		// no null pointers allowed
				!args->tx_buffer || !args->rx_buffer || !args->client_response || !args->other_data
				// No reserved bits should be set.
				|| (args->mode | CHECKMAC_MODE_MASK) != CHECKMAC_MODE_MASK
				// key_id > 15 not allowed
				|| args->key_id > SHA204_KEY_ID_MAX)
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = CHECKMAC_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_CHECKMAC;
	args->tx_buffer[CHECKMAC_MODE_IDX] = args->mode & CHECKMAC_MODE_MASK;
	args->tx_buffer[CHECKMAC_KEYID_IDX]= args->key_id;
	args->tx_buffer[CHECKMAC_KEYID_IDX + 1] = 0;
	if (args->client_challenge == NULL)
		memset(&args->tx_buffer[CHECKMAC_CLIENT_CHALLENGE_IDX], 0, CHECKMAC_CLIENT_CHALLENGE_SIZE);
	else
		memcpy(&args->tx_buffer[CHECKMAC_CLIENT_CHALLENGE_IDX], args->client_challenge, CHECKMAC_CLIENT_CHALLENGE_SIZE);

	memcpy(&args->tx_buffer[CHECKMAC_CLIENT_RESPONSE_IDX], args->client_response, CHECKMAC_CLIENT_RESPONSE_SIZE);
	memcpy(&args->tx_buffer[CHECKMAC_DATA_IDX], args->other_data, CHECKMAC_OTHER_DATA_SIZE);

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = CHECKMAC_RSP_SIZE,
		.poll_delay = CHECKMAC_DELAY,
		.poll_timeout = CHECKMAC_EXEC_MAX - CHECKMAC_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a DeriveKey command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_derive_key(struct sha204_derive_key_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer || ((args->use_random & ~DERIVE_KEY_RANDOM_FLAG) != 0)
				 || (args->target_key > SHA204_KEY_ID_MAX))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_DERIVE_KEY;
	args->tx_buffer[DERIVE_KEY_RANDOM_IDX] = args->use_random;
	args->tx_buffer[DERIVE_KEY_TARGETKEY_IDX] = args->target_key;
	args->tx_buffer[DERIVE_KEY_TARGETKEY_IDX + 1] = 0;
	if (args->mac != NULL)
	{
		memcpy(&args->tx_buffer[DERIVE_KEY_MAC_IDX], args->mac, DERIVE_KEY_MAC_SIZE);
		args->tx_buffer[SHA204_COUNT_IDX] = DERIVE_KEY_COUNT_LARGE;
	}
	else
		args->tx_buffer[SHA204_COUNT_IDX] = DERIVE_KEY_COUNT_SMALL;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = DERIVE_KEY_RSP_SIZE,
		.poll_delay = DERIVE_KEY_DELAY,
		.poll_timeout = DERIVE_KEY_EXEC_MAX - DERIVE_KEY_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a DevRev command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_dev_rev(struct sha204_dev_rev_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer)
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = DEVREV_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_DEVREV;

	// Parameters are 0.
	args->tx_buffer[DEVREV_PARAM1_IDX] =
	args->tx_buffer[DEVREV_PARAM2_IDX] =
	args->tx_buffer[DEVREV_PARAM2_IDX + 1] = 0;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = DEVREV_RSP_SIZE,
		.poll_delay = DEVREV_DELAY,
		.poll_timeout = DEVREV_EXEC_MAX - DEVREV_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a GenDig command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_gen_dig(struct sha204_gen_dig_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer
				|| ((args->zone != GENDIG_ZONE_OTP) && (args->zone != GENDIG_ZONE_DATA)))
		return SHA204_BAD_PARAM;

	if (((args->zone == GENDIG_ZONE_OTP) && (args->key_id > SHA204_OTP_BLOCK_MAX))
				|| ((args->zone == GENDIG_ZONE_DATA) && (args->key_id > SHA204_KEY_ID_MAX)))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_GENDIG;
	args->tx_buffer[GENDIG_ZONE_IDX] = args->zone;
	args->tx_buffer[GENDIG_KEYID_IDX] = args->key_id;
	args->tx_buffer[GENDIG_KEYID_IDX + 1] = 0;
	if (args->other_data != NULL)
	{
		memcpy(&args->tx_buffer[GENDIG_DATA_IDX], args->other_data, GENDIG_OTHER_DATA_SIZE);
		args->tx_buffer[SHA204_COUNT_IDX] = GENDIG_COUNT_DATA;
	}
	else
		args->tx_buffer[SHA204_COUNT_IDX] = GENDIG_COUNT;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = GENDIG_RSP_SIZE,
		.poll_delay = GENDIG_DELAY,
		.poll_timeout = GENDIG_EXEC_MAX - GENDIG_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends an HMAC command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_hmac(struct sha204_hmac_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer || ((args->mode & ~HMAC_MODE_MASK) != 0))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = HMAC_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_HMAC;
	args->tx_buffer[HMAC_MODE_IDX] = args->mode;

	// Although valid key identifiers are only
	// from 0 to 15, all 16 bits are used in the HMAC message.
	args->tx_buffer[HMAC_KEYID_IDX] = args->key_id & 0xFF;
	args->tx_buffer[HMAC_KEYID_IDX + 1] = args->key_id >> 8;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = HMAC_RSP_SIZE,
		.poll_delay = HMAC_DELAY,
		.poll_timeout = HMAC_EXEC_MAX - HMAC_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a Lock command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_lock(struct sha204_lock_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer || ((args->zone & ~LOCK_ZONE_MASK) != 0)
				|| ((args->zone & LOCK_ZONE_NO_CRC) && (args->summary != 0)))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = LOCK_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_LOCK;
	args->tx_buffer[LOCK_ZONE_IDX] = args->zone & LOCK_ZONE_MASK;
	args->tx_buffer[LOCK_SUMMARY_IDX]= args->summary & 0xFF;
	args->tx_buffer[LOCK_SUMMARY_IDX + 1]= args->summary >> 8;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = LOCK_RSP_SIZE,
		.poll_delay = LOCK_DELAY,
		.poll_timeout = LOCK_EXEC_MAX - LOCK_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a MAC command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_mac(struct sha204_mac_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer || ((args->mode & ~MAC_MODE_MASK) != 0)
				|| (((args->mode & MAC_MODE_BLOCK2_TEMPKEY) == 0) && !args->challenge))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = MAC_COUNT_SHORT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_MAC;
	args->tx_buffer[MAC_MODE_IDX] = args->mode;
	args->tx_buffer[MAC_KEYID_IDX] = args->key_id & 0xFF;
	args->tx_buffer[MAC_KEYID_IDX + 1] = args->key_id >> 8;
	if ((args->mode & MAC_MODE_BLOCK2_TEMPKEY) == 0)
	{
		memcpy(&args->tx_buffer[MAC_CHALLENGE_IDX], args->challenge, MAC_CHALLENGE_SIZE);
		args->tx_buffer[SHA204_COUNT_IDX] = MAC_COUNT_LONG;
	}

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = MAC_RSP_SIZE,
		.poll_delay = MAC_DELAY,
		.poll_timeout = MAC_EXEC_MAX - MAC_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a Nonce command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_nonce(struct sha204_nonce_parameters *args)
{
	uint8_t rx_size;

	if (!args->tx_buffer || !args->rx_buffer || !args->num_in
				|| (args->mode > NONCE_MODE_PASSTHROUGH) || (args->mode == NONCE_MODE_INVALID))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_NONCE;
	args->tx_buffer[NONCE_MODE_IDX] = args->mode;

	// 2. parameter is 0.
	args->tx_buffer[NONCE_PARAM2_IDX] =
	args->tx_buffer[NONCE_PARAM2_IDX + 1] = 0;

	if (args->mode != NONCE_MODE_PASSTHROUGH)
	{
		memcpy(&args->tx_buffer[NONCE_INPUT_IDX], args->num_in, NONCE_NUMIN_SIZE);
		args->tx_buffer[SHA204_COUNT_IDX] = NONCE_COUNT_SHORT;
		rx_size = NONCE_RSP_SIZE_LONG;
	}
	else
	{
		memcpy(&args->tx_buffer[NONCE_INPUT_IDX], args->num_in, NONCE_NUMIN_SIZE_PASSTHROUGH);
		args->tx_buffer[SHA204_COUNT_IDX] = NONCE_COUNT_LONG;
		rx_size = NONCE_RSP_SIZE_SHORT;
	}

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = rx_size,
		.poll_delay = NONCE_DELAY,
		.poll_timeout = NONCE_EXEC_MAX - NONCE_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a Pause command to SWI devices and receives a response from the selected device.
 *         All others pause.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_pause(struct sha204_pause_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer)
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = PAUSE_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_PAUSE;
	args->tx_buffer[PAUSE_SELECT_IDX] = args->selector;

	// 2. parameter is 0.
	args->tx_buffer[PAUSE_PARAM2_IDX] =
	args->tx_buffer[PAUSE_PARAM2_IDX + 1] = 0;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = PAUSE_RSP_SIZE,
		.poll_delay = PAUSE_DELAY,
		.poll_timeout = PAUSE_EXEC_MAX - PAUSE_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a Random command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_random(struct sha204_random_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer || (args->mode > RANDOM_NO_SEED_UPDATE))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = RANDOM_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_RANDOM;
	args->tx_buffer[RANDOM_MODE_IDX] = args->mode & RANDOM_SEED_UPDATE;

	// 2. parameter is 0.
	args->tx_buffer[RANDOM_PARAM2_IDX] =
	args->tx_buffer[RANDOM_PARAM2_IDX + 1] = 0;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = RANDOM_RSP_SIZE,
		.poll_delay = RANDOM_DELAY,
		.poll_timeout = RANDOM_EXEC_MAX - RANDOM_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends a Read command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_read(struct sha204_read_parameters *args)
{
	uint8_t rx_size;
	uint16_t address;

	if (!args->tx_buffer || !args->rx_buffer || ((args->zone & ~READ_ZONE_MASK) != 0)
				|| ((args->zone & READ_ZONE_MODE_32_BYTES) && (args->zone == SHA204_ZONE_OTP)))
		return SHA204_BAD_PARAM;

	// If we would just mask address bits, we would
	// read from an address that was not intended.
	address = args->address >> 2;
	if ((args->zone & SHA204_ZONE_MASK) == SHA204_ZONE_CONFIG) {
		if (address > SHA204_ADDRESS_MASK_CONFIG)
			return SHA204_BAD_PARAM;
	}		
	if ((args->zone & SHA204_ZONE_MASK) == SHA204_ZONE_OTP) {
		if (address > SHA204_ADDRESS_MASK_OTP)
			// If we would just mask this bit, we would
			// read from an address that was not intended.
			return SHA204_BAD_PARAM;
	}		
	if ((args->zone & SHA204_ZONE_MASK) == SHA204_ZONE_DATA) {
		if (address > SHA204_ADDRESS_MASK)
			// If we would just mask this bit, we would
			// read from an address that was not intended.
			return SHA204_BAD_PARAM;
	}

	args->tx_buffer[SHA204_COUNT_IDX] = READ_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_READ;
	args->tx_buffer[READ_ZONE_IDX] = args->zone;
	args->tx_buffer[READ_ADDR_IDX] = (uint8_t) address;
	args->tx_buffer[READ_ADDR_IDX + 1] = 0;

	rx_size = (args->zone & SHA204_ZONE_COUNT_FLAG) ? READ_32_RSP_SIZE : READ_4_RSP_SIZE;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = rx_size,
		.poll_delay = READ_DELAY,
		.poll_timeout = READ_EXEC_MAX - READ_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/** \brief This function sends an UpdateExtra command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_update_extra(struct sha204_update_extra_parameters *args)
{
	if (!args->tx_buffer || !args->rx_buffer || (args->mode > UPDATE_CONFIG_BYTE_86))
		return SHA204_BAD_PARAM;

	args->tx_buffer[SHA204_COUNT_IDX] = UPDATE_COUNT;
	args->tx_buffer[SHA204_OPCODE_IDX] = SHA204_UPDATE_EXTRA;
	args->tx_buffer[UPDATE_MODE_IDX] = args->mode;
	args->tx_buffer[UPDATE_VALUE_IDX] = args->new_value;
	args->tx_buffer[UPDATE_VALUE_IDX + 1] = 0;

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = UPDATE_RSP_SIZE,
		.poll_delay = UPDATE_DELAY,
		.poll_timeout = UPDATE_EXEC_MAX - UPDATE_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}


/**\brief This function sends a Write command to the device and receives its response.
 * \param[in, out]  args pointer to parameter structure
 * \return status of the operation
 */
uint8_t sha204m_write(struct sha204_write_parameters *args)
{
	uint8_t *p_command;
	uint8_t count;
	uint16_t address;

	if (!args->tx_buffer || !args->rx_buffer || !args->new_value || ((args->zone & ~WRITE_ZONE_MASK) != 0))
		return SHA204_BAD_PARAM;

	// If we would just mask address bits, we would
	// read from an address that was not intended.
	address = args->address >> 2;
	if ((args->zone & SHA204_ZONE_MASK) == SHA204_ZONE_CONFIG) {
		if (address > SHA204_ADDRESS_MASK_CONFIG)
			return SHA204_BAD_PARAM;
	}		
	if ((args->zone & SHA204_ZONE_MASK) == SHA204_ZONE_OTP) {
		if (address > SHA204_ADDRESS_MASK_OTP)
			// If we would just mask this bit, we would
			// read from an address that was not intended.
			return SHA204_BAD_PARAM;
	}		
	if ((args->zone & SHA204_ZONE_MASK) == SHA204_ZONE_DATA) {
		if (address > SHA204_ADDRESS_MASK)
			// If we would just mask this bit, we would
			// read from an address that was not intended.
			return SHA204_BAD_PARAM;
	}

	p_command = &args->tx_buffer[SHA204_OPCODE_IDX];
	*p_command++ = SHA204_WRITE;
	*p_command++ = args->zone;
	*p_command++ = (uint8_t) address;
	*p_command++ = 0;

	count = (args->zone & SHA204_ZONE_COUNT_FLAG) ? SHA204_ZONE_ACCESS_32 : SHA204_ZONE_ACCESS_4;
	memcpy(p_command, args->new_value, count);
	p_command += count;

	if (args->mac != NULL)
	{
		memcpy(p_command, args->mac, WRITE_MAC_SIZE);
		p_command += WRITE_MAC_SIZE;
	}

	// Supply count.
	args->tx_buffer[SHA204_COUNT_IDX] = (uint8_t) (p_command - &args->tx_buffer[0] + SHA204_CRC_SIZE);

	struct sha204_send_and_receive_parameters comm_parameters = {
		.tx_buffer = args->tx_buffer,
		.rx_buffer = args->rx_buffer,
		.rx_size = WRITE_RSP_SIZE,
		.poll_delay = WRITE_DELAY,
		.poll_timeout = WRITE_EXEC_MAX - WRITE_DELAY
	};
	return sha204c_send_and_receive(&comm_parameters);
}
