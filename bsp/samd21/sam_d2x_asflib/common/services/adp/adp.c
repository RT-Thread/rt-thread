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

#include "adp.h"
#include "adp_interface.h"
#include "status_codes.h"
#include <string.h>

/** ID of last received message */
static uint8_t last_received_message_id = 0xff;
/** true if valid message has been received */
static bool packet_received = false;
/** Number of bytes received */
static uint16_t bytes_received;
/** Judge previous received data */
static uint8_t prev_data = 0;
/** The length of received data */
static uint16_t length_received;
/** Current state */
static enum rx_state_e rx_state;

uint16_t adp_add_send_byte(uint8_t* buffer, uint8_t index, uint8_t* data, uint16_t length)
{
	for(uint16_t i = 0; i < length; i++) {
		if (*(data + i) == ADP_TOKEN){
			*(buffer + index) = ADP_TOKEN;
			index++;
		}
		*(buffer + index) = *(data + i);
		index++;
	}

	return index;
}

/**
* \internal Handle incoming data byte
*
* \param[in] data New data byte to handle
*
* \return
* \retval true Given data byte is part of message data
* \retval false Given data byte is not part of message data
*/
static bool adp_add_receive_byte(uint8_t data)
{
	static uint8_t message_id;

	if ((rx_state == RX_STATE_GOT_SYMBOL) && (data != ADP_TOKEN)) {
		/* Abort packet reception, new packet incoming */
		rx_state = RX_STATE_WAIT_LENGTH_LSB;
	}

	switch (rx_state) {
		case RX_STATE_IDLE:
			packet_received = false;
			last_received_message_id = 0xFF;
			/* We are waiting for a new packet. */
			if (data != ADP_TOKEN) {
				return false;
			}
			/* Got start symbol, wait for message ID */
			rx_state = RX_STATE_WAIT_MSG_ID;
			return false;

		case RX_STATE_WAIT_MSG_ID:
			if (data == ADP_TOKEN) {
				/* Restart. Don't change state. Wait for new message ID */
				return false;
			}
			message_id = data;
			rx_state = RX_STATE_WAIT_LENGTH_LSB;
			return false;

		case RX_STATE_WAIT_LENGTH_LSB:
			if (data == ADP_TOKEN) {
				if (prev_data != ADP_TOKEN) {
					prev_data = ADP_TOKEN;
					return false;
				}
			}
			length_received = data;
			rx_state = RX_STATE_WAIT_LENGTH_MSB;
			prev_data = 0;
			return false;

		case RX_STATE_WAIT_LENGTH_MSB:
			if (data == ADP_TOKEN) {
				if (prev_data != ADP_TOKEN) {
					prev_data = ADP_TOKEN;
					return false;
				}
			}
			length_received += (uint16_t)data << 8;
			prev_data = 0;
			/* Got valid length, do we expect data? */
			if (length_received == 0) {
				/* No data here, wait for next packet */
				rx_state = RX_STATE_IDLE;
				packet_received = true;
				last_received_message_id = message_id;
				return false;
			}

			/* Wait for packet data */
			bytes_received = 0;
			rx_state = RX_STATE_GET_DATA;
			return false;

		case RX_STATE_GET_DATA:
		case RX_STATE_GOT_SYMBOL:
			if ((data == ADP_TOKEN) && (rx_state == RX_STATE_GET_DATA)) {
				rx_state = RX_STATE_GOT_SYMBOL;
				return false;
			}
			/* Add new data to rx buffer */
			bytes_received++;
			/* Are we done yet? */
			if (length_received == bytes_received) {
				/* Yes we are! */
				packet_received = true;
				rx_state = RX_STATE_IDLE;
				last_received_message_id = message_id;
				return true;
			}
			/* Not done yet.. keep on receiving */
			rx_state = RX_STATE_GET_DATA;
			return true;
	}
	return false;
}

static bool adp_is_received(void)
{
	if (bytes_received == 0) {
		return false;
	}
	return packet_received;
}

static uint8_t adp_packet_received_get_id(void)
{
	return last_received_message_id;
}

static bool adp_protocol_add_byte(uint8_t rx_id, uint8_t* rx_buf, uint8_t length, uint8_t* protocol_buf)
{
	uint8_t i;

	for (i = 0; i < length; i++)
	{
		if (adp_add_receive_byte(*(rx_buf + i)) == true) {
			/* This is a data byte */
			protocol_buf[bytes_received - 1] = *(rx_buf + i);
		}
		if (adp_is_received() & (adp_packet_received_get_id() == rx_id)) {
			return true;
		}
	}
	return false;
}

static bool adp_check_for_response(uint8_t rx_id, uint8_t* protocol_buf, uint8_t length)
{
	uint8_t retry;
	bool status = false;
	uint8_t rx_buf[ADP_MAX_PACKET_DATA_SIZE] = {0,};

	retry = 50;
	length = length + ADP_LENGTH_PACKET_HEADER;
	packet_received = false;
	while((adp_is_received() == false) & (retry-- > 0)) {	
		if(adp_interface_read_response(rx_buf, length) == STATUS_OK) {
			status = adp_protocol_add_byte(rx_id, rx_buf, length, protocol_buf);
			if(status == true) {
				break;
			}
		}
	}
	
	return status;
}

static void adp_wait_for_response(uint8_t rx_id, uint8_t* protocol_buf, uint8_t length)
{
	uint8_t rx_buf[ADP_MAX_PACKET_DATA_SIZE] = {0,};

	packet_received = false;
	length = length + ADP_LENGTH_PACKET_HEADER;
	while((adp_is_received() == false)) {
		if(adp_interface_read_response(rx_buf, length) == STATUS_OK) {
			adp_protocol_add_byte(rx_id, rx_buf, length, protocol_buf);
		}
	}
}

/**
* \brief Initialization of the ADP service
*
* \return None
*/
void adp_init(void)
{
	adp_interface_init();
}

/**
* \brief Send handshake to PC and check for response
*
* \param[in]  protocol_version  ADP version used in this implementation
* \param[out] status            Status returned by PC
*
* \return PC returned valid response to out handshake
* \retval true  If we got valid response
* \retval false If we didn't receive a valid handshake response
*/
static bool adp_request_handshake(uint8_t protocol_version, uint8_t options, uint8_t* protocol_buf)
{
	uint16_t data_length = MSQ_REQ_HANDSHAKE_LEN + ADP_LENGTH_PACKET_HEADER;
	uint8_t key[8] = ADP_HANDSHAKE_KEY;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	struct adp_msg_request_handshake msg_request_handshake;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_REQ_HANDSHAKE;
	msg_format.data_length = MSQ_REQ_HANDSHAKE_LEN;
	
	msg_request_handshake.protocol_version = protocol_version;
	msg_request_handshake.options = options;
	memcpy(&msg_request_handshake.key, key, 8);
	memcpy((uint8_t*)&msg_format.data, &msg_request_handshake, sizeof(msg_request_handshake));
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	return adp_check_for_response(MSG_RES_HANDSHAKE, protocol_buf, 1);
}


/**
* \brief Send handshake to PC until we get a valid response
*
* \warning Blocking function
*
* \return Handshake status. See /ref something
*/
enum adp_handshake_status adp_wait_for_handshake(void)
{
	uint8_t handshake_status;

	/* Keep sending handshake until we get something back */
	while (adp_request_handshake(ADP_VERSION, ADP_HANDSHAKE_OPTIONS_GPIO, &handshake_status) == false) {
	}

	/* Return status */
	return ((enum adp_handshake_status)handshake_status);
}


/**
* \brief Request status from PC
*
* Sends a MSG_REQ_STATUS and waits for response
*
* \return PC Status. See /ref something
*/
enum adp_status_code adp_request_status(void)
{
	uint16_t data_length = MSG_REQ_STATUS_LEN + ADP_LENGTH_PACKET_HEADER;
	uint16_t status;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;

	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_REQ_STATUS;
	msg_format.data_length = MSG_REQ_STATUS_LEN;

	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	/* Wait for response from PC */
	adp_wait_for_response(MSG_RES_STATUS, (uint8_t*)&status, 2);
	return ((enum adp_status_code)status);
}


/**
* \brief Send MSG_CONF_INFO message and wait for response
*
* \param[in] title       Application title
* \param[in] description Application description
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_configure_info(const char* title, const char* description)
{
	uint16_t title_len;
	uint16_t description_len;
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	
	struct adp_msg_format msg_format;

	/* Add null-termination to length */
	title_len = strlen(title) + 1;
	description_len = strlen(description) + 1;
	/* Make sure the strings are not too long */
	Assert(title_len + description_len <= ADP_MAX_PACKET_DATA_SIZE);	
	
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};

	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_INFO;
	msg_format.data_length = title_len + description_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)title, title_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)description, description_len);
	data_length = ADP_LENGTH_PACKET_HEADER + index;

	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);

	return (ack == ADP_ACK_OK);
}

/**
* \brief Send MSG_CONF_STREAM and wait for response
*
* \param[in] config Configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_configure_stream(struct adp_msg_configure_stream *const config, const char* label)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t label_len;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};

	/* Add null-termination to length */
	label_len = strlen(label) + 1;
	/* Make sure the strings are not too long */
	Assert(label_len <= ADP_MAX_PACKET_DATA_SIZE);
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_STREAM;
	msg_format.data_length = MSG_CONF_STREAM_LEN + label_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->stream_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->type, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->mode, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->state, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}


/**
* \brief Send MSG_CONF_TOGGLE_STREAM and wait for response
*
* \param[in] stream_id ID of stream to toggle
* \param[in] state     New state for given stream
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_toggle_stream(struct adp_msg_toggle_stream *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_TOGGLE_STREAM;
	msg_format.data_length = MSG_CONF_TOGGLE_STREAM_LEN;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->stream_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->state, 1);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}


/**
* \brief Send MSG_CONF_GRAPH and wait for response
*
* \param[in] config Graph configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_configure_graph(struct adp_msg_configure_graph *const config, \
						const char* graph_label, const char* x_label)
{
	uint8_t ack;
	uint16_t graph_label_len, x_label_len;

	/* Add 0-termination to label string length */
	graph_label_len = strlen(graph_label) + 1;
	x_label_len = strlen(x_label) + 1;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_GRAPH_LEN + graph_label_len + x_label_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_GRAPH;
	msg_format.data_length = MSG_CONF_GRAPH_LEN + graph_label_len + x_label_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)graph_label, graph_label_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_min, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_max, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)x_label, x_label_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_scale_numerator, MSG_CONF_GRAPH_LEN - 10);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}


/**
* \brief Send MSG_CONF_TERMINAL and wait for response
*
* \param[in] config Terminal configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_configure_terminal(struct adp_msg_conf_terminal *const config, const char* label)
{
	uint8_t ack;
	uint16_t label_len;

	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_TERMINAL_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_TERMINAL;
	msg_format.data_length = MSG_CONF_TERMINAL_LEN + label_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->terminal_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->width, MSG_CONF_TERMINAL_LEN - 1);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Send MSG_CONF_ADD_TO_TERMINAL and wait for response
*
* \param[in] config Stream-to-terminal configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_stream_to_terminal(struct adp_msg_add_stream_to_terminal *const config, const char* tag_text)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t tag_text_len;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	/* Add 0-termination to label string length */
	tag_text_len = strlen(tag_text) + 1;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_ADD_TO_TERMINAL_LEN + tag_text_len <= ADP_MAX_PACKET_DATA_SIZE);
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_ADD_TO_TERMINAL;
	msg_format.data_length = MSG_CONF_ADD_TO_TERMINAL_LEN + tag_text_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->terminal_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->stream_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->mode, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->text_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)tag_text, tag_text_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->tag_text_color, 3);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}


/**
* \brief Send MSG_CONF_AXIS and wait for response
*
* \param[in] config Axis configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_axis_to_graph(struct adp_msg_conf_axis *const config, const char* label)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint16_t label_len;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_AXIS_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_AXIS;
	msg_format.data_length = MSG_CONF_AXIS_LEN + label_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->axis_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_min, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_max, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_scale_numerator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_scale_denominator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->mode, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->color, 3);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}


/**
* \brief Send MSG_CONF_ADD_STREAM_TO_AXIS and wait for response
*
* \param[in] config Axis configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_stream_to_axis(struct adp_msg_add_stream_to_axis *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_ADD_STREAM_TO_AXIS;
	msg_format.data_length = MSG_CONF_ADD_STREAM_TO_AXIS_LEN;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->axis_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->stream_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->sample_rate_numerator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->sample_rate_denominator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_scale_numerator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_scale_denominator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_offset, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->mode, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_thickness, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_color, 3);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}


/**
* \brief Send MSG_CONF_CURSOR_TO_GRAPH and wait for response
*
* \param[in] config Cursor configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_cursor_to_graph(struct adp_msg_add_cursor_to_graph *const config, const char* label)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint16_t label_len;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_CURSOR_TO_GRAPH_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_CURSOR_TO_GRAPH;
	msg_format.data_length = MSG_CONF_CURSOR_TO_GRAPH_LEN;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->stream_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->axis_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->thickness, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->initial_value, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->minimum_value, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->maximum_value, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->scale_numerator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->scale_denominator, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->scale_offset, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_style, 1);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Send MSG_CONF_CURSOR_TO_GRAPH and wait for response
*
* \param[in] config         Cursor configuration struct
* \param[in] tag_high_state Tag text to display when GPIO pin is high.
* \param[in] tag_low_state  Tag text to display when GPIO pin is low.
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_gpio_to_graph(struct adp_msg_conf_gpio_to_graph *const config, \
					const char* tag_high_state, const char* tag_low_state)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint16_t label_len, tag_high_state_len, tag_low_state_len;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	/* Add 0-termination to label string length */
	tag_high_state_len = strlen(tag_high_state) + 1;
	tag_low_state_len = strlen(tag_low_state) + 1;
	label_len = tag_high_state_len + tag_low_state_len;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_GPIO_TO_GRAPH_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_GPIO_TO_GRAPH;
	msg_format.data_length = MSG_CONF_GPIO_TO_GRAPH_LEN + label_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->gpio_number, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_id, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)tag_high_state, tag_high_state_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)tag_low_state, tag_low_state_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->mode, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_thickness, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_color_high_state, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_color_low_state, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->line_style, 1);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a dashboard
*
* \param[in] config    Pointer to dashboard configuration data struct
* \param[in] label     Dashboard label (0-terminated string)
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_dashboard(struct adp_msg_conf_dashboard *const config, const char* label)
{
	uint8_t ack;
	uint16_t label_len;

	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	Assert(MSG_CONF_DASHBOARD_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD;
	msg_format.data_length = MSG_CONF_DASHBOARD_LEN + label_len;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index,(uint8_t*)&config->dashboard_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->height, 2);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

static uint16_t adp_add_dashboard_element_common_send_byte(uint8_t* add_buf, uint16_t index, \
									struct adp_msg_conf_dashboard_element_common *const config)
{
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->dashboard_id, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->element_id, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->z_index, 1);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->x, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->y, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->width, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->height, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->element_type, 1);
	
	return index;
}

/**
* \brief Add a label to dashboard
*
* \param[in] config    Pointer to dashboard label struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_label_to_dashboard(struct adp_msg_conf_dashboard_element_label *const config, const char* label)
{
	uint8_t ack;
	uint16_t label_len;

	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	Assert(ADP_ELEMENT_TYPE_LABEL_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_LABEL_LEN + label_len;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->font_size, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->attribute, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->horisontal_alignment, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->vertical_alignment, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->background_transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->background_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->foreground_transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->foreground_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a button to dashboard
*
* \param[in] config    Pointer to dashboard button struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_button_to_dashboard(struct adp_msg_conf_dashboard_element_button *const config, const char* label)
{
	uint8_t ack;
	uint16_t label_len;

	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	Assert(ADP_ELEMENT_TYPE_BUTTON_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_BUTTON_LEN + label_len;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
										(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->font_size, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)label, label_len);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a slider to dashboard
*
* \param[in] config    Pointer to dashboard slider struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_slider_to_dashboard(struct adp_msg_conf_dashboard_element_slider *const config)
{	
		uint8_t ack;
		uint16_t data_length;
		uint16_t index = 0;
		uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
		
		struct adp_msg_format msg_format;
		
		msg_format.protocol_token = ADP_TOKEN;
		msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
		msg_format.data_length = ADP_ELEMENT_TYPE_SLIDER_LEN;
		index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
												(struct adp_msg_conf_dashboard_element_common *)config);
		index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->minimum_value, 4);
		index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->maximum_value, 4);
		index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->initial_value, 4);
		data_length = ADP_LENGTH_PACKET_HEADER + index;
		
		/* Send the protocol packet data */
		adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
		
		/* Wait for response and return status */
		adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
		return (ack == ADP_ACK_OK);
}

/**
* \brief Add a progress bar to dashboard
*
* \param[in] config    Pointer to dashboard progress bar struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_progress_to_dashboard(struct adp_msg_conf_dashboard_element_progress *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_PROGRESS_LEN;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->minimum_value, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->maximum_value, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->initial_value, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->color, 3);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a signal to dashboard
*
* \param[in] config    Pointer to dashboard signal struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_signal_to_dashboard(struct adp_msg_conf_dashboard_element_signal *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_SIGNAL_LEN;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->on_transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->on_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->off_transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->off_color, 3);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a segment display to dashboard
*
* \param[in] config    Pointer to dashboard segment struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_segment_to_dashboard(struct adp_msg_conf_dashboard_element_segment *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_SEGMENT_LEN;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->segment_count, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->base, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->transparency, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->color, 3);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a graph to dashboard
*
* \param[in] config    Pointer to dashboard graph struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_graph_to_dashboard(struct adp_msg_conf_dashboard_element_graph *const config, const char* title)
{
	uint8_t ack;
	uint16_t title_len;

	/* Add 0-termination to label string length */
	title_len = strlen(title) + 1;

	/* Make sure label isn't too big */
	Assert(ADP_ELEMENT_TYPE_GRAPH_LEN + title_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_GRAPH_LEN + title_len;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
										(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->title_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->background_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->graph_background_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)title, title_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->plot_count, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_min, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->x_max, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_min, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->y_max, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->mode, 1);
	
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add data fields to dashboard
*
* \param[in] config    Pointer to dashboard text struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_text_to_dashboard(struct adp_msg_conf_dashboard_element_text *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_TEXT_LEN;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->minimum, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->maximum, 4);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->value, 4);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a radio to dashboard
*
* \param[in] config    Pointer to dashboard radio struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_radio_to_dashboard(struct adp_msg_conf_dashboard_element_radio *const config, const char* text)
{
	uint8_t ack;
	uint16_t text_len;

	/* Add 0-termination to label string length */
	text_len = strlen(text) + 1;

	/* Make sure label isn't too big */
	Assert(ADP_ELEMENT_TYPE_RADIO_LEN + text_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_RADIO_LEN + text_len;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->font_size, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->number_items, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->orientation, 1);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)text, text_len);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Add a pie to dashboard
*
* \param[in] config    Pointer to dashboard pie struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_pie_to_dashboard(struct adp_msg_conf_dashboard_element_pie *const config, const char* title)
{
	uint8_t ack;
	uint16_t title_len;

	/* Add 0-termination to label string length */
	title_len = strlen(title) + 1;

	/* Make sure label isn't too big */
	Assert(ADP_ELEMENT_TYPE_PIE_LEN + title_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length = ADP_ELEMENT_TYPE_PIE_LEN + title_len;
	index = adp_add_dashboard_element_common_send_byte((uint8_t*)&msg_format.data, index, \
											(struct adp_msg_conf_dashboard_element_common *)config);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->background_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->title_color, 3);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)title, title_len);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->number_slices, 1);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

/**
* \brief Connect a stream to dashboard element
*
* \param[in] config    Pointer to stream element configuration struct
*
* \return Status from PC
* \retval true   Message received and accepted
* \retval false  Message received but not accepted
*/
bool adp_add_stream_to_element(struct adp_conf_add_stream_to_element *const config)
{
	uint8_t ack;
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_ADD_STREAM_TO_ELEMENT;
	msg_format.data_length = MSG_CONF_ADD_STREAM_TO_ELEMENT_LEN;
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->dashboard_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->element_id, 2);
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&config->stream_id, 2);
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);

	/* Wait for response and return status */
	adp_wait_for_response(MSG_CONF_ACK, &ack, 1);
	return (ack == ADP_ACK_OK);
}

bool adp_transceive_stream(struct adp_msg_data_stream *const stream_data, uint8_t *protocol_buf)
{
	uint8_t stream_num;	
	uint16_t data_length;
	uint16_t index = 0;
	uint8_t rx_buf[ADP_MAX_PACKET_LENGTH] = {0,};
	
	struct adp_msg_format msg_format;
	
	index = adp_add_send_byte((uint8_t*)&msg_format.data, index, (uint8_t*)&stream_data->number_of_streams, 1);
	/* find packet size */
	for (stream_num = 0; stream_num < stream_data->number_of_streams; stream_num++) {
		index = adp_add_send_byte((uint8_t*)&msg_format.data, index, \
						(uint8_t*)&stream_data->stream[stream_num].stream_id, 2);
		index = adp_add_send_byte((uint8_t*)&msg_format.data, index, \
						(uint8_t*)&stream_data->stream[stream_num].data_size, 1);
		index = adp_add_send_byte((uint8_t*)&msg_format.data, index, \
						stream_data->stream[stream_num].data, \
						stream_data->stream[stream_num].data_size);
	}
	
	msg_format.protocol_token = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_DATA_STREAM;
	msg_format.data_length = index;
	data_length = ADP_LENGTH_PACKET_HEADER + index;
	
	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t*)&msg_format, data_length, rx_buf);
	
	return adp_protocol_add_byte(MSG_RES_DATA, rx_buf, data_length, protocol_buf);
}


/**
* \brief Send and read data on one single stream
*
* \param[in] stream_id ID of stream
* \param[in] data      Pointer to data to send
* \param[in] data_size Size of data to send
*
* \return None
*/
bool adp_transceive_single_stream(uint16_t stream_id, uint8_t* data, uint8_t data_size, uint8_t* protocol_buf)
{
	struct adp_msg_data_stream data_stream;
	volatile uint8_t status;

	data_stream.number_of_streams = 1;
	data_stream.stream[0].stream_id = stream_id;
	data_stream.stream[0].data_size = data_size;
	data_stream.stream[0].data = data;
	status = adp_transceive_stream(&data_stream, protocol_buf);
	
	return status;
}

