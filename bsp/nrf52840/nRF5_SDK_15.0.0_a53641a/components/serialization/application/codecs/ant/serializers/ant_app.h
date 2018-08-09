/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef ANT_APP_H__
#define ANT_APP_H__

/**
 * @addtogroup ser_app_s212_codecs Application codecs for S212
 * @ingroup ser_codecs_app
 */

/**@file
 *
 * @defgroup ant_app Application command request encoders and command response decoders
 * @{
 * @ingroup  ser_app_s212_codecs
 *
 * @brief    Application command request encoders and command response decoders.
 */
//#include "ble.h"
#include "ant_interface.h"

/**@brief Encodes @ref sd_ant_enable command request.
 *
 * @sa @ref ant_enable_rsp_dec for command response decoder.
 *
 * @param[in] p_ant_enable_params   Pointer to an @ref ANT_ENABLE structure.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_enable_req_enc(ANT_ENABLE *     p_ant_enable_params,
                            uint8_t * const  p_buf,
                            uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_enable command.
 *
 * @sa @ref ant_enable_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_enable_rsp_dec(uint8_t const * const p_buf,
                            uint32_t              packet_len,
                            uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_assign command request.
 *
 * @sa @ref ant_channel_assign_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  to assign.
 * @param[in] channel_type          Channel Type is an unsigned char (1 octet) denoting the
 *                                  channel type. See Assign Channel Parameters/Assign Channel
 *                                  Types in ant_parameters.h.
 * @param[in] network               Network is an unsigned char (1 octet) denoting the network
 *                                  key to associate with the channel.
 * @param[in] ext_assign            Ext Assign is a bit field (1 octet) for an extended
 *                                  assign. See Ext. Assign Channel Parameters in
 *                                  ant_parameters.h.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_assign_req_enc(uint8_t          channel,
                                    uint8_t          channel_type,
                                    uint8_t          network,
                                    uint8_t          ext_assign,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_assign command.
 *
 * @sa @ref ant_channel_assign_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_assign_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_open command request.
 *
 * @sa @ref ant_channel_open_with_offset_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel to
 *                                  open.
 * @param[in] usOffset              Denote the offset from which to start the channel.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_open_with_offset_req_enc(uint8_t          channel,
                                              uint16_t         usOffset,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_open command.
 *
 * @sa @ref ant_channel_open_with_offset_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_open_with_offset_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_id_set command request.
 *
 * @sa @ref ant_channel_id_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to set.
 * @param[in] device_number         Device Number is an unsigned short (2 octets) denoting the
 *                                  device number.
 * @param[in] device_type           Device Type is an unsigned char (1 octet) denoting the device
 *                                  type.
 * @param[in] transmit_type         Transmit Type is an unsigned char (1 octet) denoting the
 *                                  transmission type.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_id_set_req_enc(uint8_t          channel,
                                    uint16_t         device_number,
                                    uint8_t          device_type,
                                    uint8_t          transmit_type,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_id_set command.
 *
 * @sa @ref ant_channel_id_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_id_set_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_period_set command request.
 *
 * @sa @ref ant_channel_period_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to set the period to.
 * @param[in] period                Period is an unsigned short (2 octets) denoting the period in
 *                                  32 kHz counts (usPeriod/32768 s).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_period_set_req_enc(uint8_t          channel,
                                        uint16_t         period,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_period_set command.
 *
 * @sa @ref ant_channel_period_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_period_set_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_radio_freq_set command request.
 *
 * @sa @ref ant_channel_radio_freq_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to set to.
 * @param[in] freq                  Freq is an unsigned char (1 octet) denoting the radio
 *                                  frequency offset from 2400 MHz (eg. 2466 MHz, ucFreq = 66).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_freq_set_req_enc(uint8_t          channel,
                                            uint8_t          freq,
                                            uint8_t * const  p_buf,
                                            uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_radio_freq_set command.
 *
 * @sa @ref ant_channel_radio_freq_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                     Pointer to beginning of command response packet.
 * @param[in] packet_len                Length (in bytes) of response packet.
 * @param[out] p_result_code            Command result code.
 *
 * @retval NRF_SUCCESS                  Success.
 * @retval NRF_ERROR_INVALID_LENGTH     Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE          Decoding failure. Length of \p p_event is too small to
 *                                      hold decoded event.
 */
uint32_t ant_channel_radio_freq_set_rsp_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_broadcast_message_tx command request.
 *
 * @sa @ref ant_broadcast_message_tx_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel to
 *                                  send the data on.
 * @param[in] size                  Size is an unsigned char (1 octet) denoting the size of the
 *                                  message, ucSize must be 8.
 * @param[in] p_mesg                Mesg is the buffer where the message is located (array must be
 *                                  8 octets).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_broadcast_message_tx_req_enc(uint8_t               channel,
                                          uint8_t               size,
                                          uint8_t const * const p_mesg,
                                          uint8_t * const       p_buf,
                                          uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_broadcast_message_tx command.
 *
 * @sa @ref ant_broadcast_message_tx_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_broadcast_message_tx_rsp_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          uint32_t * const      p_result_code);


/**@brief Encodes @ref sd_ant_acknowledge_message_tx command request.
 *
 * @sa @ref ant_acknowledge_message_tx_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel to
 *                                  send the data on.
 * @param[in] size                  Size is an unsigned char (1 octet) denoting the size of the
 *                                  message, ucSize must be 8.
 * @param[in] p_mesg                Mesg is the buffer where the message is located (array must be
 *                                  8 octets).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_acknowledge_message_tx_req_enc(uint8_t               channel,
                                            uint8_t               size,
                                            uint8_t const * const p_mesg,
                                            uint8_t * const       p_buf,
                                            uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_acknowledge_message_tx command.
 *
 * @sa @ref ant_acknowledge_message_tx_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_acknowledge_message_tx_rsp_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_unassign command request.
 *
 * @sa @ref ant_channel_unassign_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  to unassign.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_unassign_req_enc(uint8_t          channel,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_unassign command.
 *
 * @sa @ref ant_channel_unassign_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_unassign_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_close command request.
 *
 * @sa @ref ant_channel_close_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  to close.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_close_req_enc(uint8_t          channel,
                                   uint8_t * const  p_buf,
                                   uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_close command.
 *
 * @sa @ref ant_channel_close_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_close_rsp_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_network_address_set command request.
 *
 * @sa @ref ant_network_address_set_rsp_dec for command response decoder.
 *
 * @param[in] network               Network is an unsigned char (1 octet) denoting the network
 *                                  number to assign the network address to.
 * @param[in] p_network_key         Network key is the pointer to location of the Network Key (8
 *                                  octets in length).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_network_address_set_req_enc(uint8_t               network,
                                         uint8_t const * const p_network_key,
                                         uint8_t * const       p_buf,
                                         uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_network_address_set command.
 *
 * @sa @ref ant_network_address_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_network_address_set_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_radio_tx_power_set command request.
 *
 * @sa @ref ant_channel_radio_tx_power_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to assign the radio TX power.
 * @param[in] tx_power              TX Power is an unsigned char (1 octet) denoting the ANT
 *                                  transmit power index. See Radio TX Power Definitions in
 *                                  ant_parameters.h.
 * @param[in] custom_tx_power       Custom TX Power is an unsigned char (1 octet) denoting the
 *                                  custom nRF transmit power as defined in nrf51_bitfields.h.
 *                                  Only applicable if tx_power is set to custom TX power
 *                                  selection.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_tx_power_set_req_enc(uint8_t          channel,
                                                uint8_t          tx_power,
                                                uint8_t          custom_tx_power,
                                                uint8_t * const  p_buf,
                                                uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_radio_tx_power_set command.
 *
 * @sa @ref ant_channel_radio_tx_power_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_radio_tx_power_set_rsp_dec(uint8_t const * const p_buf,
                                                uint32_t              packet_len,
                                                uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_rx_search_timeout_set command request.
 *
 * @sa @ref ant_channel_rx_search_timeout_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to set.
 * @param[in] timeout               Timeout is an unsigned char (1 octet) denoting the time-out
 *                                  value.
 *                                  When applied to an assigned slave channel, ucTimeout is in 2.5
 *                                  second increments. Default = 10 (25 s) at channel assignment.
 *                                  When applied to an assigned master channel, ucTimeout is in
 *                                  250 ms increments. Default = 0 (disabled) at channel assignment
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_rx_search_timeout_set_req_enc(uint8_t          channel,
                                                   uint8_t          timeout,
                                                   uint8_t * const  p_buf,
                                                   uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_rx_search_timeout_set command.
 *
 * @sa @ref ant_channel_rx_search_timeout_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_rx_search_timeout_set_rsp_dec(uint8_t const * const p_buf,
                                                   uint32_t              packet_len,
                                                   uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_low_priority_rx_search_timeout_set command request.
 *
 * @sa @ref ant_channel_low_priority_rx_search_timeout_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to set.
 * @param[in] timeout               Timeout is an unsigned char (1 octet) denoting the time-out
 *                                  value in 2.5 seconds increments. Default = 2 (5s).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_low_priority_rx_search_timeout_set_req_enc(uint8_t          channel,
                                                                uint8_t          timeout,
                                                                uint8_t * const  p_buf,
                                                                uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_low_priority_rx_search_timeout_set command.
 *
 * @sa @ref ant_channel_low_priority_rx_search_timeout_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_low_priority_rx_search_timeout_set_rsp_dec(uint8_t const * const p_buf,
                                                                uint32_t              packet_len,
                                                                uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_prox_search_set command request.
 *
 * @sa @ref ant_prox_search_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] prox_threshold        Prox threshold is an unsigned char (1 octet) denoting the
 *                                  minimum RSSI threshold required for acquisition during a
 *                                  search. See Radio Proximity Search Threshold in
 *                                  ant_parameters.h.
 * @param[in] custom_prox_threshold Custom prox threshold is an unsigned char (1 octet) denoting
 *                                  the custom minimum RSSI threshold for acquisition during a
 *                                  search. Only applicable if ucProxThreshold is set to custom
 *                                  proximity selection.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_prox_search_set_req_enc(uint8_t          channel,
                                     uint8_t          prox_threshold,
                                     uint8_t          custom_prox_threshold,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_prox_search_set command.
 *
 * @sa @ref ant_prox_search_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_prox_search_set_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_search_waveform_set command request.
 *
 * @sa @ref ant_search_waveform_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] waveform              Waveform is an unsigned short (2 octets) denoting the channel
 *                                  waveform period (usWaveform/32768 s). Default = 316.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_search_waveform_set_req_enc(uint8_t          channel,
                                         uint16_t         waveform,
                                         uint8_t * const  p_buf,
                                         uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_search_waveform_set command.
 *
 * @sa @ref ant_search_waveform_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_search_waveform_set_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_id_get command request.
 *
 * @sa @ref ant_channel_id_get_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_id_get_req_enc(uint8_t          channel,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_id_get command.
 *
 * @sa @ref ant_channel_id_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_device_number       Pointer to device number.
 * @param[in] p_device_type         Pointer to device type.
 * @param[in] p_transmit_type       Pointer to transmit type.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_id_get_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    void * const          p_device_number,
                                    void * const          p_device_type,
                                    void * const          p_transmit_type,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_radio_freq_get command request.
 *
 * @sa @ref ant_channel_radio_freq_get_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_freq_get_req_enc(uint8_t          channel,
                                            uint8_t * const  p_buf,
                                            uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_radio_freq_get command.
 *
 * @sa @ref ant_channel_radio_freq_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_r_freq              Pointer to radio frequency.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_radio_freq_get_rsp_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            void * const          p_r_freq,
                                            uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_period_get command request.
 *
 * @sa @ref ant_channel_period_get_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_period_get_req_enc(uint8_t          channel,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_period_get command.
 *
 * @sa @ref ant_channel_period_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_period              Pointer to period
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_period_get_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        void *                p_period,
                                        uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_search_channel_priority_set command request.
 *
 * @sa @ref ant_search_channel_priority_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] search_priority       Search Priority is an unsigned char (1 octet) denoting the
 *                                  search priority value. 0 to 7 (Default = 0).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_search_channel_priority_set_req_enc(uint8_t          channel,
                                                 uint8_t          search_priority,
                                                 uint8_t * const  p_buf,
                                                 uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_search_channel_priority_set command.
 *
 * @sa @ref ant_search_channel_priority_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_search_channel_priority_set_rsp_dec(uint8_t const * const p_buf,
                                                 uint32_t              packet_len,
                                                 uint32_t * const      p_result_code);


/**@brief Encodes @ref sd_ant_active_search_sharing_cycles_set command request.
 *
 * @sa @ref ant_active_search_sharing_cycles_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] cycles                Cycles is an unsigned char (1 octet) denoting the number of
 *                                  cycles to set.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_active_search_sharing_cycles_set_req_enc(uint8_t          channel,
                                                      uint8_t          cycles,
                                                      uint8_t * const  p_buf,
                                                      uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_active_search_sharing_cycles_set command.
 *
 * @sa @ref ant_active_search_sharing_cycles_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_active_search_sharing_cycles_set_rsp_dec(uint8_t const * const p_buf,
                                                      uint32_t              packet_len,
                                                      uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_lib_config_set command request.
 *
 * @sa @ref ant_lib_config_set_rsp_dec for command response decoder.
 *
 * @param[in] ant_lib_config        ANT Lib Config an unsigned char (1 octet) denoting the ANT lib
 *                                  config bit flags. See ANT Library Config in ant_parameters.h.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_lib_config_set_req_enc(uint8_t          ant_lib_config,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_lib_config_set command.
 *
 * @sa @ref ant_lib_config_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_lib_config_set_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_active_search_sharing_cycles_get command request.
 *
 * @sa @ref ant_active_search_sharing_cycles_get_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_active_search_sharing_cycles_get_req_enc(uint8_t          channel,
                                                      uint8_t * const  p_buf,
                                                      uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_active_search_sharing_cycles_get command.
 *
 * @sa @ref ant_active_search_sharing_cycles_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_cycles              Pointer to cycles.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_active_search_sharing_cycles_get_rsp_dec(uint8_t const * const p_buf,
                                                      uint32_t              packet_len,
                                                      void * const          p_cycles,
                                                      uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_lib_config_get command request.
 *
 * @sa @ref ant_lib_config_get_rsp_dec for command response decoder.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_lib_config_get_req_enc(uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_lib_config_get command.
 *
 * @sa @ref ant_lib_config_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_ant_lib_config      Pointer to the ANT library configuration.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_lib_config_get_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    void * const          p_ant_lib_config,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_lib_config_clear command request.
 *
 * @sa @ref ant_lib_config_clear_rsp_dec for command response decoder.
 *
 * @param[in] ant_lib_config        ANT lib config is an unsigned char (1 octet) denoting the
 *                                  ANT lib config bit(s) to clear. See ANT Library Config in
 *                                  ant_parameters.h.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_lib_config_clear_req_enc(uint8_t          ant_lib_config,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_lib_config_clear command.
 *
 * @sa @ref ant_lib_config_clear_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_lib_config_clear_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_stack_reset command request.
 *
 * @sa @ref ant_stack_reset_rsp_dec for command response decoder.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_stack_reset_req_enc(uint8_t * const  p_buf,
                                 uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_stack_reset command.
 *
 * @sa @ref ant_stack_reset_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_stack_reset_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_rx_scan_mode_start command request.
 *
 * @sa @ref ant_rx_scan_mode_start_rsp_dec for command response decoder.
 *
 * @param[in] sync_channel_packets_only Sync channel packets only is an unsigned char (1 octet)
 *                                      denoting synchronous channel only scanning mode.
 *                                      0 = disable, 1 = enable.
 * @param[in] p_buf                     Pointer to buffer where encoded data command will be
 *                                      returned.
 * @param[in,out] p_buf_len             \c in: Size of \p p_buf buffer.
 *                                      \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                  Encoding success.
 * @retval NRF_ERROR_NULL               Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH     Encoding failure. Incorrect buffer length.
 */
uint32_t ant_rx_scan_mode_start_req_enc(uint8_t          sync_channel_packets_only,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_rx_scan_mode_start command.
 *
 * @sa @ref ant_rx_scan_mode_start_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_rx_scan_mode_start_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_id_list_add command request.
 *
 * @sa @ref ant_id_list_add_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number to add the list entry to.
 * @param[in] p_dev_id              Dev ID is the pointer to the buffer (4 octets) containing
 *                                  device ID information with the following format:
 *                                  Byte0 = DeviceNumber_LSB
 *                                  Byte1 = DeviceNumber_MSB
 *                                  Byte2 = DeviceType
 *                                  Byte3 = TransType
 * @param[in] list_index            List index is an unsigned char (1 octet) denoting the index
 *                                  where the specified channel ID is to be placed in the list (0-3).
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_id_list_add_req_enc(uint8_t               channel,
                                 uint8_t const * const p_dev_id,
                                 uint8_t               list_index,
                                 uint8_t * const       p_buf,
                                 uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_id_list_add command.
 *
 * @sa @ref ant_id_list_add_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_id_list_add_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_id_list_config command request.
 *
 * @sa @ref ant_id_list_config_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the
 *                                  channel number of the device ID list.
 * @param[in] id_list_size          ID list size is an unsigned char (1 octet) denoting the size of
 *                                  the inclusion or exclusion list (0-4).
 * @param[in] inc_exc_flag          Inc exc flag is an unsigned char (1 octet) denoting the type of
 *                                  list as Include(0) or Exclude(1).
 * @param[in] channel
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_id_list_config_req_enc(uint8_t               channel,
                                    uint8_t               id_list_size,
                                    uint8_t               inc_exc_flag,
                                    uint8_t * const       p_buf,
                                    uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_id_list_config command.
 *
 * @sa @ref ant_id_list_config_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_id_list_config_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_channel_status_get command request.
 *
 * @sa @ref ant_channel_status_get_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel
 *                                  number.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_status_get_req_enc(uint8_t          channel,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_channel_status_get command.
 *
 * @sa @ref ant_channel_status_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_status              Pointer to status
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_channel_status_get_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        void * const          p_status,
                                        uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_cw_test_mode_init command request.
 *
 * @sa @ref ant_cw_test_mode_init_rsp_dec for command response decoder.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_cw_test_mode_init_req_enc(uint8_t * const  p_buf,
                                       uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_cw_test_mode_init command.
 *
 * @sa @ref ant_cw_test_mode_init_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_cw_test_mode_init_rsp_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_cw_test_mode command request.
 *
 * @sa @ref ant_cw_test_mode_rsp_dec for command response decoder.
 *
 * @param[in] radio_freq            Radio freq is an unsigned char (1 octet) denoting the radio
 *                                  frequency offset from 2400 MHz for continuous wave mode.
 *                                  (eg. 2466 MHz, ucRadioFreq = 66).
 * @param[in] tx_power              TX Power is an unsigned char (1 octet) denoting the ANT transmit
 *                                  power index for continuous wave mode. See Radio TX Power
 *                                  Definitions in ant_parameters.h
 * @param[in] custom_tx_power       Custom TX power is an unsigned char (1 octet) denoting the
 *                                  custom nRF transmit power as defined in nrf51_bitfields.h. Only
 *                                  applicable if ucTxPower is set to custom TX power selection.
 * @param[in] mode                  Mode is an unsigned char (1 octet) denoting test mode type where
 *                                  0 = cw tx carrier transmission, 1 = cw tx modulated transmission.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_cw_test_mode_req_enc(uint8_t          radio_freq,
                                  uint8_t          tx_power,
                                  uint8_t          custom_tx_power,
                                  uint8_t          mode,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_cw_test_mode command.
 *
 * @sa @ref ant_cw_test_mode_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_cw_test_mode_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_version_get command request.
 *
 * @sa @ref ant_version_get_rsp_dec for command response decoder.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_version_get_req_enc(uint8_t * const  p_buf,
                                 uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_version_get command.
 *
 * @sa @ref ant_version_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_version             Pointer to version string buffer.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_version_get_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 void * * const        p_version,
                                 uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_capabilities_get command request.
 *
 * @sa @ref ant_capabilities_get_rsp_dec for command response decoder.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_capabilities_get_req_enc(uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_capabilities_get command.
 *
 * @sa @ref ant_capabilities_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] pp_capabilities       Pointer to pointer to capabilities buffer.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_capabilities_get_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      void * * const        pp_capabilities,
                                      uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_crypto_channel_enable command request.
 *
 * @sa @ref ant_crypto_channel_enable_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel in
 *                                  which encryption mode is set.
 * @param[in] enable                Enable is an unsigned char (1 octet) denoting the encryption
 *                                  mode. See Encrypted Channel Defines in ant_parameters.h.
 * @param[in] key_num               Key num is an unsigned char (1 octet) denoting the key index of
 *                                  the 128-bit key to be used for encryption. The key index range
 *                                  is bound by the number of encrypted channels configured by
 *                                  sd_ant_enable(). If sd_ant_enable() is not used then by default
 *                                  key num is 0. Range is [0 to (num encrypted channels - 1)], if
 *                                  1 or more encrypted channels are configured.
 * @param[in] decimation_rate       Decimation rate is an unsigned char (1 octet) denoting the
 *                                  decimate rate to apply for encrypted slave channel. Must be > 0.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_channel_enable_req_enc(uint8_t          channel,
                                           uint8_t          enable,
                                           uint8_t          key_num,
                                           uint8_t          decimation_rate,
                                           uint8_t * const  p_buf,
                                           uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_crypto_channel_enable command.
 *
 * @sa @ref ant_crypto_channel_enable_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_crypto_channel_enable_rsp_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_adv_burst_config_set command request.
 *
 * @sa @ref ant_adv_burst_config_set_rsp_dec for command response decoder.
 *
 * @param[in] p_config              Config is a buffer containing the advanced burst
 *                                  configuration to be set.
 * @param[in] size                  Size is an unsigned char (1 octet) denoting the size of the
 *                                  configuration parameter buffer.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_adv_burst_config_set_req_enc(uint8_t const * const p_config,
                                          uint8_t               size,
                                          uint8_t * const       p_buf,
                                          uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_adv_burst_config_set command.
 *
 * @sa @ref ant_adv_burst_config_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_adv_burst_config_set_rsp_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_crypto_key_set command request.
 *
 * @sa @ref ant_crypto_key_set_rsp_dec for command response decoder.
 *
 * @param[in] key_num               Key num is an unsigned char (1 octet) denoting the key index for
 *                                  assignment.
 * @param[in] p_key                 Buffer (16 octets) containing the 128-bit AES key to be
 *                                  assigned to the key index.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_key_set_req_enc(uint8_t               key_num,
                                    uint8_t const * const p_key,
                                    uint8_t * const       p_buf,
                                    uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_crypto_key_set command.
 *
 * @sa @ref ant_crypto_key_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_crypto_key_set_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_crypto_info_set command request.
 *
 * @sa @ref ant_crypto_info_set_rsp_dec for command response decoder.
 *
 * @param[in] type                  Type is an unsigned char (1 octet) denoting the type of
 *                                  information being set.
 * @param[in] p_info                Pointer to a buffer buffer containing the information being set.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_info_set_req_enc(uint8_t               type,
                                     uint8_t const * const p_info,
                                     uint8_t * const       p_buf,
                                     uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ant_crypto_info_set command.
 *
 * @sa @ref ant_crypto_info_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_crypto_info_set_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_crypto_info_get command request.
 *
 * @sa @ref ant_crypto_info_get_rsp_dec for command response decoder.
 *
 * @param[in] type                  Type is an unsigned char (1 octet) denoting the type of
 *                                  information being set.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_info_get_req_enc(uint8_t          type,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_crypto_info_get command.
 *
 * @sa @ref ant_crypto_info_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_info                Pointer to the info buffer.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_crypto_info_get_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     void * const          p_info,
                                     uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_coex_config_set command request.
 *
 * @sa @ref ant_coex_config_set_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel for
 *                                  which the coexistence configuration is to be set
 * @param[in] p_config              Pointer to a buffer containing the configuration to be set.
 * @param[in] p_adv_coex_config     Pointer to a buffer containing the advanced coexistence configuration
 *                                  to be set.
 *
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_coex_config_set_req_enc(uint8_t                      channel,
                                     ANT_BUFFER_PTR const * const p_config,
                                     ANT_BUFFER_PTR const * const p_adv_coex_config,
                                     uint8_t * const              p_buf,
                                     uint32_t * const             p_buf_len);

/**@brief Decodes response to @ref sd_ant_coex_config_set command.
 *
 * @sa @ref ant_coex_config_set_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_coex_config_set_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ant_coex_config_get command request.
 *
 * @sa @ref ant_coex_config_get_rsp_dec for command response decoder.
 *
 * @param[in] channel               Channel is an unsigned char (1 octet) denoting the channel to
 *                                  query.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_coex_config_get_req_enc(uint8_t          channel,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ant_coex_config_get command.
 *
 * @sa @ref ant_coex_config_get_req_enc for command request encoder.
 *
 * @param[in] p_buf                 Pointer to beginning of command response packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[in] p_coex_config         Pointer to the coexistence configuration buffer.
 * @param[in] p_adv_coex_config     Pointer to the advanced coexistence configuration buffer.
 * @param[out] p_result_code        Command result code.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Length of \p p_event is too small to
 *                                  hold decoded event.
 */
uint32_t ant_coex_config_get_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     void * const          p_coex_config,
                                     void * const          p_adv_coex_config,
                                     uint32_t * const      p_result_code);
/** @} */
#endif
