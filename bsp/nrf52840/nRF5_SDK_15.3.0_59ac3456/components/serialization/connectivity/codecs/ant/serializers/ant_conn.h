/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#ifndef ANT_CONN_H__
#define ANT_CONN_H__


/**
 * @addtogroup ser_conn_s212_codecs Connectivity codecs for S212
 * @ingroup ser_codecs_conn
 */

/**@file
 *
 * @defgroup ant_conn Connectivity command request decoders and command response encoders
 * @{
 * @ingroup  ser_conn_s212_codecs
 *
 * @brief    Connectivity command request decoders and command response encoders.
 */
#include "ant_interface.h"

/**@brief Decodes @ref sd_ant_enable command request.
 *
 * @sa @ref ant_enable_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 * @param[out] pp_ant_enable_params Pointer to pointer to @ref ANT_ENABLE.
 *                                  \c It will be set to NULL if p_ant_enable_params is not
 *                                  present in the packet.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_enable_req_dec(uint8_t const * const p_buf,
                            uint32_t              packet_len,
                            ANT_ENABLE * * const  pp_ant_enable_params);

/**@brief Encodes @ref sd_ant_enable command response.
 *
 * @sa @ref ant_enable_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_enable_rsp_enc(uint32_t         return_code,
                            uint8_t * const  p_buf,
                            uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_assign command request.
 *
 * @sa @ref ant_channel_assign_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel to be
 *                                  assigned will be set.
 * @param[out]  p_type              Pointer to an unsigned char (1 octet) where the channel type
 *                                  to be assigned will be set.
 * @param[out]  p_network           Pointer to an unsigned char (1 octet) where the network key to
 *                                  associate with the channel will be set.
 * @param[out]  p_ext_assign        Pointer to a bit field (1 octet) where an extended assign will
 *                                  be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_assign_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint8_t * const       p_channel,
                                    uint8_t * const       p_type,
                                    uint8_t * const       p_network,
                                    uint8_t * const       p_ext_assign);

/**@brief Encodes @ref sd_ant_channel_assign command response.
 *
 * @sa @ref ant_channel_assign_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_assign_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_open command request.
 *
 * @sa @ref ant_channel_open_with_offset_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel to be
 *                                  opened will be set.
 * @param[out] p_usOffset           Pointer to a channel start time offset value.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_open_with_offset_req_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              uint8_t * const       p_channel,
                                              uint16_t * const      p_usOffset);

/**@brief Encodes @ref sd_ant_channel_open command response.
 *
 * @sa @ref ant_channel_open_with_offset_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_open_with_offset_rsp_enc(uint32_t         return_code,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_id_set command request.
 *
 * @sa @ref ant_channel_id_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 * @param[out]  p_device_number     Pointer to an unsigned short (2 octets) where the device
 *                                  number will be set.
 * @param[out]  p_device_type       Pointer to an an unsigned char (1 octet) where the device type
 *                                  will be set.
 * @param[out]  p_transmission_type Pointer to an unsigned char (1 octet) where the transmission
 *                                  type will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_id_set_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint8_t * const       p_channel,
                                    uint16_t * const      p_device_number,
                                    uint8_t * const       p_device_type,
                                    uint8_t * const       p_transmission_type);

/**@brief Encodes @ref sd_ant_channel_id_set command response.
 *
 * @sa @ref ant_channel_id_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_id_set_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_period_set command request.
 *
 * @sa @ref ant_channel_period_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  associated with the period will be set.
 * @param[out]  p_period            Pointer to an unsigned short (2 octets) where the period will
 *                                  be set. Value is in 32 kHz counts (usPeriod/32768 s).
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_period_set_req_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint8_t * const       p_channel,
                                        uint16_t * const      p_period);

/**@brief Encodes @ref sd_ant_channel_period_set command response.
 *
 * @sa @ref ant_channel_period_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_period_set_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_radio_freq_set command request.
 *
 * @sa @ref ant_channel_radio_freq_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  associated with the radio frequency will be set.
 * @param[out]  p_freq              Pointer to an unsigned char (1 octet) where the radio
 *                                  frequency will be set. Value is offset from 2400 MHz
 *                                  (eg. 2466 MHz, ucFreq = 66).
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_freq_set_req_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            uint8_t * const       p_channel,
                                            uint8_t * const       p_freq);

/**@brief Encodes @ref sd_ant_channel_radio_freq_set command response.
 *
 * @sa @ref ant_channel_radio_freq_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_freq_set_rsp_enc(uint32_t         return_code,
                                            uint8_t * const  p_buf,
                                            uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_broadcast_message_tx command request.
 *
 * @sa @ref ant_broadcast_message_tx_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel to
 *                                  send the data on will be set.
 * @param[out]  p_size              Pointer to an unsigned char (1 octet) where the size of the
 *                                  message will be set.
 * @param[out]  pp_mesg             Pointer to pointer to the buffer where the broadcast message
 *                                  will be set (array must be 8 octets).
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_broadcast_message_tx_req_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          uint8_t * const       p_channel,
                                          uint8_t * const       p_size,
                                          uint8_t * * const     pp_mesg);

/**@brief Encodes @ref sd_ant_broadcast_message_tx command response.
 *
 * @sa @ref ant_broadcast_message_tx_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_broadcast_message_tx_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_acknowledge_message_tx command request.
 *
 * @sa @ref ant_acknowledge_message_tx_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel to
 *                                  send the data on will be set.
 * @param[out]  p_size              Pointer to an unsigned char (1 octet) where the size of the
 *                                  message will be set.
 * @param[out]  pp_mesg             Pointer to pointer to the buffer where the acknowledge message
 *                                  will be set (array must be 8 octets).
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_acknowledge_message_tx_req_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            uint8_t * const       p_channel,
                                            uint8_t * const       p_size,
                                            uint8_t * * const     pp_mesg);

/**@brief Encodes @ref sd_ant_acknowledge_message_tx command response.
 *
 * @sa @ref ant_acknowledge_message_tx_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_acknowledge_message_tx_rsp_enc(uint32_t         return_code,
                                            uint8_t * const  p_buf,
                                            uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_unassign command request.
 *
 * @sa @ref ant_channel_unassign_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel to be
 *                                  unassigned will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_unassign_req_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_channel_unassign command response.
 *
 * @sa @ref ant_channel_unassign_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_unassign_rsp_enc(uint32_t         return_code,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_close command request.
 *
 * @sa @ref ant_channel_close_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel to be
 *                                  closed will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_close_req_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_channel_close command response.
 *
 * @sa @ref ant_channel_close_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_close_rsp_enc(uint32_t         return_code,
                                   uint8_t * const  p_buf,
                                   uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_network_address_set command request.
 *
 * @sa @ref  ant_network_address_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_network           Pointer to an unsigned char (1 octet) where the network number
 *                                  to assign the network address to will be set.
 * @param[out]  pp_network_key       Pointer to a pointer to where the network key (8 octets in
 *                                  length) will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_network_address_set_req_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint8_t * const       p_network,
                                         uint8_t * * const     pp_network_key);

/**@brief Encodes @ref sd_ant_network_address_set command response.
 *
 * @sa @ref ant_network_address_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_network_address_set_rsp_enc(uint32_t         return_code,
                                         uint8_t * const  p_buf,
                                         uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_radio_tx_power_set command request.
 *
 * @sa @ref ant_channel_radio_tx_power_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  to assign the radio TX power will be set.
 * @param[out]  p_tx_power          Pointer to an unsigned char (1 octet) where the ANT transmit
 *                                  power index will be set. See Radio TX Power Definitions in
 *                                  ant_parameters.h.
 * @param[out]  p_custom_tx_power   Pointer to an unsigned char (1 octet) where the custom nRF
 *                                  transmit power as defined in nrf51_bitfields.h will be set.
 *                                  Only applicable if tx_power is set to custom TX power
 *                                  selection.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_tx_power_set_req_dec(uint8_t const * const p_buf,
                                                uint32_t              packet_len,
                                                uint8_t * const       p_channel,
                                                uint8_t * const       p_tx_power,
                                                uint8_t * const       p_custom_tx_power);

/**@brief Encodes @ref sd_ant_channel_radio_tx_power_set command response.
 *
 * @sa @ref ant_channel_radio_tx_power_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_tx_power_set_rsp_enc(uint32_t         return_code,
                                                uint8_t * const  p_buf,
                                                uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_rx_search_timeout_set command request.
 *
 * @sa @ref ant_channel_rx_search_timeout_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 * @param[out]  p_timeout           Pointer to an unsigned char (1 octet) where the time-out value
 *                                  will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_rx_search_timeout_set_req_dec(uint8_t const * const p_buf,
                                                   uint32_t              packet_len,
                                                   uint8_t * const       p_channel,
                                                   uint8_t * const       p_timeout);

/**@brief Encodes @ref sd_ant_channel_rx_search_timeout_set command response.
 *
 * @sa @ref ant_channel_rx_search_timeout_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_channel_rx_search_timeout_set_rsp_enc(uint32_t         return_code,
                                                    uint8_t * const  p_buf,
                                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_low_priority_rx_search_timeout_set command request.
 *
 * @sa @ref ant_channel_low_priority_rx_search_timeout_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 * @param[out]  p_timeout           Pointer to an unsigned char (1 octet) where the time-out value
 *                                  will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_low_priority_rx_search_timeout_set_req_dec(uint8_t const * const p_buf,
                                                                uint32_t              packet_len,
                                                                uint8_t * const       p_channel,
                                                                uint8_t * const       p_timeout);

/**@brief Encodes @ref sd_ant_channel_low_priority_rx_search_timeout_set command response.
 *
 * @sa @ref ant_channel_low_priority_rx_search_timeout_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_channel_low_priority_rx_search_timeout_set_rsp_enc(uint32_t         return_code,
                                                                 uint8_t * const  p_buf,
                                                                 uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_prox_search_set command request.
 *
 * @sa @ref ant_prox_search_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                    Pointer to beginning of command request packet.
 * @param[in]  packet_len               Length (in bytes) of response packet.
 *
 * @param[out]  p_channel               Pointer to an unsigned char (1 octet) where the channel
 *                                      number will be set.
 * @param[out]  p_prox_threshold        Pointer to an unsigned char (1 octet) where the minimum
 *                                      RSSI threshold required for acquisition during a search
 *                                      will be set. See Radio Proximity Search Threshold in
 *                                      ant_parameters.h.
 * @param[out]  p_custom_prox_threshold Pointer to an unsigned char (1 octet) where the custom
 *                                      minimum RSSI threshold for acquisition during a search
 *                                      will be set. Only applicable if prox_threshold is set to
 *                                      custom proximity selection.
 *
 * @retval NRF_SUCCESS                  Decoding success.
 * @retval NRF_ERROR_NULL               Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH     Decoding failure. Incorrect buffer length.
 */
uint32_t ant_prox_search_set_req_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint8_t * const       p_channel,
                                     uint8_t * const       p_prox_threshold,
                                     uint8_t * const       p_custom_prox_threshold);

/**@brief Encodes @ref sd_ant_prox_search_set command response.
 *
 * @sa @ref ant_prox_search_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_prox_search_set_rsp_enc(uint32_t         return_code,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_search_waveform_set command request.
 *
 * @sa @ref ant_search_waveform_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel
 *                                  number will be set.
 * @param[out]  p_waveform          Pointer to an unsigned short (2 octets) where the channel
 *                                  waveform period (usWaveform/32768 s) will be set.
 *                                  Default = 316.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_search_waveform_set_req_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint8_t * const       p_channel,
                                         uint16_t * const      p_waveform);

/**@brief Encodes @ref sd_ant_search_waveform_set command response.
 *
 * @sa @ref ant_search_waveform_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_search_waveform_set_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_id_get command request.
 *
 * @sa @ref ant_channel_id_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel
 *                                  number will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_id_get_req_dec(uint8_t const * const p_buf,
                                    uint16_t              packet_len,
                                    uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_channel_id_get command response.
 *
 * @sa @ref ant_channel_id_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_device_number      Pointer to device number
 * @param[in]  p_device_type        Pointer to device type
 * @param[in]  p_transmit_type      Pointer to transmit type
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_id_get_rsp_enc(uint32_t               return_code,
                                    uint8_t * const        p_buf,
                                    uint32_t * const       p_buf_len,
                                    uint16_t const * const p_device_number,
                                    uint8_t const * const  p_device_type,
                                    uint8_t const * const  p_transmit_type);

/**@brief Decodes @ref sd_ant_channel_radio_freq_get command request.
 *
 * @sa @ref ant_channel_radio_freq_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_freq_get_req_dec(uint8_t const * const p_buf,
                                            uint16_t              packet_len,
                                            uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_channel_radio_freq_get command response.
 *
 * @sa @ref ant_channel_radio_freq_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_r_freq             Pointer to radio frequency
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_radio_freq_get_rsp_enc(uint32_t              return_code,
                                            uint8_t * const       p_buf,
                                            uint32_t * const      p_buf_len,
                                            uint8_t const * const p_r_freq);

/**@brief Decodes @ref sd_ant_channel_period_get command request.
 *
 * @sa @ref ant_channel_period_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_period_get_req_dec(uint8_t const * const p_buf,
                                        uint16_t              packet_len,
                                        uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_channel_period_get command response.
 *
 * @sa @ref ant_channel_period_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_period             Pointer to period
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_period_get_rsp_enc(uint32_t               return_code,
                                        uint8_t * const        p_buf,
                                        uint32_t * const       p_buf_len,
                                        uint16_t const * const p_period);

/**@brief Decodes @ref sd_ant_search_channel_priority_set command request.
 *
 * @sa @ref ant_search_channel_priority_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 * @param[out]  p_search_priority   Pointer to an unsigned char (1 octet) where the search
 *                                  priority value will be set. 0 to 7 (Default = 0).
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_search_channel_priority_set_req_dec(uint8_t const * const p_buf,
                                                 uint32_t              packet_len,
                                                 uint8_t * const       p_channel,
                                                 uint8_t * const       p_search_priority);

/**@brief Encodes @ref sd_ant_search_channel_priority_set command response.
 *
 * @sa @ref ant_search_channel_priority_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_search_channel_priority_set_rsp_enc(uint32_t         return_code,
                                                  uint8_t * const  p_buf,
                                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_active_search_sharing_cycles_set command request.
 *
 * @sa @ref ant_active_search_sharing_cycles_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 * @param[out]  p_cycles            Pointer to an unsigned char (1 octet) where the numbe of
 *                                  cycles will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_active_search_sharing_cycles_set_req_dec(uint8_t const * const p_buf,
                                                      uint32_t              packet_len,
                                                      uint8_t * const       p_channel,
                                                      uint8_t * const       p_cycles);

/**@brief Encodes @ref sd_ant_active_search_sharing_cycles_set command response.
 *
 * @sa @ref ant_active_search_sharing_cycles_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_active_search_sharing_cycles_set_rsp_enc(uint32_t         return_code,
                                                       uint8_t * const  p_buf,
                                                       uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_lib_config_set command request.
 *
 * @sa @ref ant_lib_config_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_ant_lib_config    Pointer to an unsigned char (1 octet) where the ANT lib
 *                                  config bit flags will be set. See ANT Library Config in
 *                                  ant_parameters.h.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_lib_config_set_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint8_t * const       p_ant_lib_config);

/**@brief Encodes @ref sd_ant_lib_config_set command response.
 *
 * @sa @ref ant_lib_config_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_lib_config_set_rsp_enc(uint32_t         return_code,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_active_search_sharing_cycles_get command request.
 *
 * @sa @ref ant_active_search_sharing_cycles_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_active_search_sharing_cycles_get_req_dec(uint8_t const * const p_buf,
                                                      uint16_t              packet_len,
                                                      uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_active_search_sharing_cycles_get command response.
 *
 * @sa @ref ant_active_search_sharing_cycles_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_cycles             Pointer to cycles.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_active_search_sharing_cycles_get_rsp_enc(uint32_t              return_code,
                                                      uint8_t * const       p_buf,
                                                      uint32_t * const      p_buf_len,
                                                      uint8_t const * const p_cycles);

/**@brief Encodes @ref sd_ant_lib_config_get command response.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_ant_lib_config     Pointer to ANT library configuration.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_lib_config_get_rsp_enc(uint32_t              return_code,
                                    uint8_t * const       p_buf,
                                    uint32_t * const      p_buf_len,
                                    uint8_t const * const p_ant_lib_config);

/**@brief Decodes @ref sd_ant_lib_config_clear command request.
 *
 * @sa @ref ant_lib_config_clear_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_ant_lib_config    Pointer to an unsigned char (1 octet) where the ANT lib config
 *                                  bit(s) to clear will be set. See ANT Library Config in
 *                                  ant_parameters.h.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_lib_config_clear_req_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint8_t * const       p_ant_lib_config);

/**@brief Encodes @ref sd_ant_lib_config_clear command response.
 *
 * @sa @ref ant_lib_config_clear_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_lib_config_clear_rsp_enc(uint32_t         return_code,
                                       uint8_t * const  p_buf,
                                       uint32_t * const p_buf_len);

/**@brief Encodes @ref sd_ant_stack_reset command response.
 *
 * @param[in] return_code           Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_stack_reset_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_rx_scan_mode_start command request.
 *
 * @sa @ref ant_rx_scan_mode_start_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                       Pointer to beginning of command request packet.
 * @param[in]  packet_len                  Length (in bytes) of response packet.
 *
 * @param[out] p_sync_channel_packets_only Pointer to an unsigned char (1 octet) where the
 *                                         synchronous channel only scanning mode will be set.
 *                                         0 = disable, 1 = enable.
 *
 * @retval NRF_SUCCESS                     Decoding success.
 * @retval NRF_ERROR_NULL                  Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH        Decoding failure. Incorrect buffer length.
 */
uint32_t ant_rx_scan_mode_start_req_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint8_t * const       p_sync_channel_packets_only);

/**@brief Encodes @ref sd_ant_rx_scan_mode_start command response.
 *
 * @sa @ref ant_rx_scan_mode_start_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_rx_scan_mode_start_rsp_enc(uint32_t         return_code,
                                         uint8_t * const  p_buf,
                                         uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_id_list_add command request.
 *
 * @sa @ref ant_id_list_add_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out] p_channel            Pointer to an unsigned char (1 octet) where the channel
 *                                  number to add the list entry to will be set.
 * @param[out] pp_dev_id            Pointer to pointer to where the Dev ID will be stored.
 * @param[out] p_list_index         Pointer to an unsigned char (1 octet) where the list
 *                                  index (0-3), will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_id_list_add_req_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint8_t * const       p_channel,
                                 uint8_t * * const     pp_dev_id,
                                 uint8_t * const       p_list_index);

/**@brief Encodes @ref sd_ant_id_list_add command response.
 *
 * @sa @ref ant_id_list_add_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_id_list_add_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_id_list_config command request.
 *
 * @sa @ref ant_id_list_config_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out] p_channel            Pointer to an unsigned char (1 octet) wher the channel number
 *                                  of the device ID list will be stored.
 * @param[out] p_id_list_size       Pointer to an unsigned char (1 octet) where the size of the
 *                                  inclusion or exclusion list (0-4) will be stored.
 * @param[out] p_inc_exc_flag       Pointer to an unsigned char (1 octet) where the type of list
 *                                  will be stored.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_id_list_config_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint8_t * const       p_channel,
                                    uint8_t * const       p_id_list_size,
                                    uint8_t * const       p_inc_exc_flag);

/**@brief Encodes @ref sd_ant_id_list_add command response.
 *
 * @sa @ref ant_id_list_config_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_id_list_config_rsp_enc(uint32_t         return_code,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_channel_status_get command request.
 *
 * @sa @ref ant_channel_status_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel number
 *                                  will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_status_get_req_dec(uint8_t const * const p_buf,
                                        uint16_t              packet_len,
                                        uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_channel_status_get command response.
 *
 * @sa @ref ant_channel_status_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_status             Pointer to status
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_channel_status_get_rsp_enc(uint32_t              return_code,
                                        uint8_t * const       p_buf,
                                        uint32_t * const      p_buf_len,
                                        uint8_t const * const p_status);

/**@brief Encodes @ref sd_ant_cw_test_mode_init command response.
 *
 * @param[in] return_code           Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_cw_test_mode_init_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_cw_test_mode command request.
 *
 * @sa @ref  ant_cw_test_mode_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_radio_freq        Pointer to an unsigned char (1 octet) where the radio
 *                                  frequency offset from 2400 MHz for continuous wave mode will be
 *                                  set. (eg. 2466 MHz, ucRadioFreq = 66).
 * @param[out]  p_tx_power          Pointer to an unsigned char (1 octet) where the ANT transmit
 *                                  power index for continuous wave mode will be set. See Radio
 *                                  TX Power Definitions in ant_parameters.h
 * @param[out]  p_custom_tx_power   Pointer to an unsigned char (1 octet) where the custom nRF
 *                                  transmit power as defined in nrf51_bitfields.h will be set. Only
 *                                  applicable if ucTxPower is set to custom TX power selection.
 * @param[out]  p_mode              Pointer to an unsigned char (1 octet) where the test mode type
 *                                  will be set.
 * @param[in] p_buf                 Pointer to buffer where encoded data command will be returned.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_cw_test_mode_req_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint8_t * const       p_radio_freq,
                                  uint8_t * const       p_tx_power,
                                  uint8_t * const       p_custom_tx_power,
                                  uint8_t * const       p_mode);

/**@brief Encodes @ref sd_ant_cw_test_mode command response.
 *
 * @sa @ref ant_cw_test_mode_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_cw_test_mode_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Encodes @ref sd_ant_version_get command response.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_version            Pointer to version.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_version_get_rsp_enc(uint32_t              return_code,
                                 uint8_t * const       p_buf,
                                 uint32_t * const      p_buf_len,
                                 uint8_t const * const p_version);

/**@brief Encodes @ref sd_ant_capabilities_get command response.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_capabilities       Pointer to ant capabilities buffer.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_capabilities_get_rsp_enc(uint32_t              return_code,
                                      uint8_t * const       p_buf,
                                      uint32_t * const      p_buf_len,
                                      uint8_t const * const p_capabilities);

/**@brief Decodes @ref sd_ant_crypto_channel_enable command request.
 *
 * @sa @ref ant_crypto_channel_enable_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel in which
 *                                  encryption mode is set will be copied to.
 * @param[out]  p_enable            Pointer to an unsigned char (1 octet) where the encryption
 *                                  mode will be set.
 * @param[out]  p_key_num           Pointer to an unsigned char (1 octet) where the key index of the
 *                                  128-bit key to be used for encryption will be set.
 * @param[out]  p_decimation_rate   Pointer to an unsigned char (1 octet) where the decimate rate to
 *                                  apply for encrypted slave channel will be set. Must be > 0.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_channel_enable_req_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint8_t * const       p_channel,
                                           uint8_t * const       p_enable,
                                           uint8_t * const       p_key_num,
                                           uint8_t * const       p_decimation_rate);

/**@brief Encodes @ref sd_ant_crypto_channel_enable command response.
 *
 * @sa @ref ant_crypto_channel_enable_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t  ant_crypto_channel_enable_rsp_enc(uint32_t         return_code,
                                            uint8_t * const  p_buf,
                                            uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_adv_burst_config_set command request.
 *
 * @sa @ref ant_adv_burst_config_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_config           Pointer to the buffer where advanced burst
 *                                  configuration will be set.
 * @param[out]  p_size              Pointer to an unsigned char (1 octet) where the size of the
 *                                  configuration parameter buffer will be set.
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_adv_burst_config_set_req_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          uint8_t * const       p_config,
                                          uint8_t * const       p_size);

/**@brief Encodes @ref sd_ant_adv_burst_config_set command response.
 *
 * @sa @ref ant_adv_burst_config_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_adv_burst_config_set_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_crypto_key_set command request.
 *
 * @sa @ref ant_crypto_key_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_key_num           Pointer to an unsigned char (1 octet) where the key index for
 *                                  assignment will be set.
 * @param[out]  pp_key              Pointer to pointer to buffer (16 octets) where the 128-bit
 *                                  AES key to be assigned to the key index will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_key_set_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint8_t * const       p_key_num,
                                    uint8_t * * const     pp_key);

/**@brief Encodes @ref sd_ant_crypto_key_set command response.
 *
 * @sa @ref ant_crypto_key_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_key_set_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_crypto_info_set command request.
 *
 * @sa @ref ant_crypto_info_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_type              Pointer to an unsigned char (1 octet) where the type of
 *                                  information being set will be copied.
 * @param[out]  pp_info             Pointer to pointer to buffer where information being set will be
 *                                  copied.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_info_set_req_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint8_t * const       p_type,
                                     uint8_t * * const     pp_info);

/**@brief Encodes @ref sd_ant_crypto_info_set command response.
 *
 * @sa @ref ant_crypto_info_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_info_set_rsp_enc(uint32_t         return_code,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_crypto_info_get command request.
 *
 * @sa @ref ant_crypto_info_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_type              Pointer to an unsigned char (1 octet) where the type of
 *                                  information being set will be copied.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_info_get_req_dec(uint8_t const * const p_buf,
                                     uint16_t              packet_len,
                                     uint8_t * const       p_type);

/**@brief Encodes @ref sd_ant_crypto_info_get command response.
 *
 * @sa @ref ant_crypto_info_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  type                 The type of information being set.
 * @param[in]  p_info               Pointer to info buffer.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_crypto_info_get_rsp_enc(uint32_t              return_code,
                                     uint8_t * const       p_buf,
                                     uint32_t * const      p_buf_len,
                                     uint8_t               type,
                                     uint8_t const * const p_info);

/**@brief Decodes @ref sd_ant_coex_config_set command request.
 *
 * @sa @ref ant_coex_config_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[in] p_channel             Pointer to an unsigned char (1 octet) where the channel for
 *                                  which the coexistence configuration is to be set will be copied.
 * @param[in] p_coex_config         Pointer to a buffer where the coexistence configuration to be set will
 *                                  be copied.
 * @param[in] p_adv_coex_config     Pointer to a buffer where the advanced coexistence configuration to be set will
 *                                  be copied.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_coex_config_set_req_dec(uint8_t const * const  p_buf,
                                     uint32_t               packet_len,
                                     uint8_t * const        p_channel,
                                     ANT_BUFFER_PTR * const p_coex_config,
                                     ANT_BUFFER_PTR * const p_adv_coex_config);

/**@brief Encodes @ref sd_ant_coex_config_set command response.
 *
 * @sa @ref ant_coex_config_set_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_coex_config_set_rsp_enc(uint32_t         return_code,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ant_coex_config_get command request.
 *
 * @sa @ref ant_channel_id_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @param[out]  p_channel           Pointer to an unsigned char (1 octet) where the channel
 *                                  number will be set.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_coex_config_get_req_dec(uint8_t const * const p_buf,
                                     uint16_t              packet_len,
                                     uint8_t * const       p_channel);

/**@brief Encodes @ref sd_ant_coex_config_get command response.
 *
 * @sa @ref ant_channel_id_get_req_dec for request decoding.
 *
 * @param[in]  return_code          Return code indicating if command was successful or not.
 * @param[out] p_buf                Pointer to buffer where encoded data command response will be
 *                                  returned.
 * @param[in,out] p_buf_len         \c in: Size of \p p_buf buffer.
 *                                  \c out: Length of encoded command response packet.
 * @param[in]  p_coex_config        Pointer to the coexistence configuration.
 * @param[in]  p_adv_coex_config    Pointer to the advanced coexistence configuration.
 *
 * @retval NRF_SUCCESS              Encoding success.
 * @retval NRF_ERROR_NULL           Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Encoding failure. Incorrect buffer length.
 */
uint32_t ant_coex_config_get_rsp_enc(uint32_t               return_code,
                                     uint8_t * const        p_buf,
                                     uint32_t * const       p_buf_len,
                                     ANT_BUFFER_PTR * const p_coex_config,
                                     ANT_BUFFER_PTR * const p_adv_coex_config);
/** @} */

#endif
