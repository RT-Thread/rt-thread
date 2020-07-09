/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
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
#ifndef BLE_GATTC_CONN_H__
#define BLE_GATTC_CONN_H__

/**@file
 *
 * @defgroup ble_gatc_conn GATTC connectivity command request decoders and command response encoders
 * @{
 * @ingroup  ser_conn_s130_codecs
 *
 * @brief    GATTC Connectivity command request decoders and command response encoders
 */
#include "ble_gattc.h"
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Decodes @ref sd_ble_gattc_characteristics_discover command request.
 *
 * @sa @ref ble_gattc_characteristics_discover_rsp_enc for response encoding.
 *
 * @param[in] p_buf             Pointer to beginning of command request packet.
 * @param[in] packet_len        Length (in bytes) of response packet.
 * @param[out] p_conn_handle    Pointer to connection handle.
 * @param[out] pp_handle_range  Pointer to pointer to handle range.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Invalid value for handle range field present.
 */
uint32_t ble_gattc_characteristics_discover_req_dec
    (uint8_t const * const             p_buf,
    uint16_t                           packet_len,
    uint16_t * const                   p_conn_handle,
    ble_gattc_handle_range_t * * const pp_handle_range);

/**@brief Encodes @ref sd_ble_gattc_characteristics_discover command response.
 *
 * @sa @ref ble_gattc_characteristics_discover_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_characteristics_discover_rsp_enc(uint32_t         return_code,
                                                    uint8_t * const  p_buf,
                                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_descriptors_discover command request.
 *
 * @sa @ref ble_gattc_descriptors_discover_rsp_enc for response encoding.
 *
 * @param[in] p_buf             Pointer to beginning of command request packet.
 * @param[in] packet_len        Length (in bytes) of response packet.
 * @param[out] p_conn_handle    Pointer to connection handle.
 * @param[out] pp_handle_range  Pointer to pointer to handle range.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Invalid value for handle range field present.
 */
uint32_t ble_gattc_descriptors_discover_req_dec(uint8_t const * const              p_buf,
                                                uint16_t                           packet_len,
                                                uint16_t * const                   p_conn_handle,
                                                ble_gattc_handle_range_t * * const pp_handle_range);

/**@brief Encodes @ref sd_ble_gattc_descriptors_discover command response.
 *
 * @sa @ref ble_gattc_descriptors_discover_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_descriptors_discover_rsp_enc(uint32_t         return_code,
                                                uint8_t * const  p_buf,
                                                uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_relationships_discover command request.
 *
 * @sa @ref ble_gattc_relationships_discover_rsp_enc for response encoding.
 *
 * @param[in] p_buf             Pointer to beginning of command request packet.
 * @param[in] packet_len        Length (in bytes) of response packet.
 * @param[out] p_conn_handle    Pointer to connection handle.
 * @param[out] pp_handle_range  Pointer to pointer to handle range.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Invalid value for handle range field present.
 */
uint32_t ble_gattc_relationships_discover_req_dec
    (uint8_t const * const             p_buf,
    uint16_t                           packet_len,
    uint16_t * const                   p_conn_handle,
    ble_gattc_handle_range_t * * const pp_handle_range);

/**@brief Encodes @ref sd_ble_gattc_relationships_discover command response.
 *
 * @sa @ref ble_gattc_relationships_discover_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_relationships_discover_rsp_enc(uint32_t         return_code,
                                                  uint8_t * const  p_buf,
                                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_primary_services_discover command request.
 *
 * @sa @ref ble_gattc_primary_services_discover_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] p_start_handle  Pointer to start handle.
 * @param[out] pp_srvc_uuid    Pointer to pointer to service uuid.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid value for uuid field present.
 */
uint32_t ble_gattc_primary_services_discover_req_dec(uint8_t const * const p_buf,
                                                     uint16_t              packet_len,
                                                     uint16_t * const      p_conn_handle,
                                                     uint16_t * const      p_start_handle,
                                                     ble_uuid_t * * const  pp_srvc_uuid);

/**@brief Encodes @ref sd_ble_gattc_primary_services_discover command response.
 *
 * @sa @ref ble_gattc_primary_services_discover_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_primary_services_discover_rsp_enc(uint32_t         return_code,
                                                     uint8_t * const  p_buf,
                                                     uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_read command request.
 *
 * @sa @ref ble_gattc_read_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command response packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] p_handle        Pointer to handle.
 * @param[out] p_offset        Pointer to offset.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_read_req_dec(uint8_t const * const p_buf,
                                uint16_t              packet_len,
                                uint16_t * const      p_conn_handle,
                                uint16_t * const      p_handle,
                                uint16_t * const      p_offset);

/**@brief Encodes @ref sd_ble_gattc_read command response.
 *
 * @sa @ref ble_gattc_read_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_read_rsp_enc(uint32_t         return_code,
                                uint8_t * const  p_buf,
                                uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_char_values_read command request.
 *
 * @sa @ref ble_gattc_char_values_read_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command response packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] pp_handles      Pointer to pointer to handle table.
 * @param[out] p_handle_count  Pointer to handle handle table count.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */

uint32_t ble_gattc_char_values_read_req_dec(uint8_t const * const p_buf,
                                            uint16_t              packet_len,
                                            uint16_t * const      p_conn_handle,
                                            uint16_t * * const    pp_handles,
                                            uint16_t * const      p_handle_count);

/**@brief Encodes @ref sd_ble_gattc_char_values_read command response.
 *
 * @sa @ref ble_gattc_char_values_read_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_char_values_read_rsp_enc(uint32_t         return_code,
                                            uint8_t * const  p_buf,
                                            uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_write command request.
 *
 * @sa @ref ble_gattc_write_rsp_enc for response encoding.
 *
 * @param[in] p_buf             Pointer to beginning of command response packet.
 * @param[in] packet_len        Length (in bytes) of response packet.
 * @param[out] p_conn_handle    Pointer to connection handle.
 * @param[out] pp_write_params  Pointer to pointer to write parameters.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_write_req_dec(uint8_t const * const              p_buf,
                                 uint16_t                           packet_len,
                                 uint16_t * const                   p_conn_handle,
                                 ble_gattc_write_params_t * * const pp_write_params);

/**@brief Encodes @ref sd_ble_gattc_write command response.
 *
 * @sa @ref ble_gattc_write_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_write_rsp_enc(uint32_t         return_code,
                                 uint8_t * const  p_buf,
                                 uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_hv_confirm command request.
 *
 * @sa @ref ble_gattc_hv_confirm_rsp_enc for response encoding.
 *
 * @param[in] p_buf             Pointer to beginning of command response packet.
 * @param[in] packet_len        Length (in bytes) of response packet.
 * @param[out] p_conn_handle    Pointer to connection handle.
 * @param[out] p_handle         Pointer to handle of the attribute in the indication.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_hv_confirm_req_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint16_t * const      p_conn_handle,
                                      uint16_t * const      p_handle);

/**@brief Encodes @ref sd_ble_gattc_hv_confirm command response.
 *
 * @sa @ref ble_gattc_hv_confirm_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_hv_confirm_rsp_enc(uint32_t         return_code,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_char_value_by_uuid_read command request.
 *
 * @sa @ref ble_gattc_char_value_by_uuid_read_rsp_enc for response encoding.
 *
 * @param[in]  p_buf            Pointer to beginning of command request packet.
 * @param[in]  packet_len       Length (in bytes) of request packet.
 * @param[out] p_conn_handle    Pointer to connection handle of the connection.
 * @param[out] pp_uuid          Pointer to pointer to a characteristic value UUID to read.
 * @param[out] pp_handle_range  Pointer to pointer to the range of handles to perform this
 *                              procedure on.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid operation type.
 */
uint32_t ble_gattc_char_value_by_uuid_read_req_dec
    (uint8_t const * const             p_buf,
    uint16_t                           packet_len,
    uint16_t * const                   p_conn_handle,
    ble_uuid_t * * const               pp_uuid,
    ble_gattc_handle_range_t * * const pp_handle_range);

/**@brief Encodes @ref sd_ble_gattc_char_value_by_uuid_read command response.
 *
 * @sa @ref ble_gattc_char_value_by_uuid_read_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_char_value_by_uuid_read_rsp_enc(uint32_t         return_code,
                                                   uint8_t * const  p_buf,
                                                   uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_attr_info_discover command request.
 *
 * @sa @ref ble_gattc_attr_info_discover_rsp_enc for response encoding.
 *
 * @param[in]  p_buf            Pointer to beginning of command request packet.
 * @param[in]  buf_len          Length (in bytes) of request packet.
 * @param[out] p_conn_handle    Pointer to connection handle of the connection.
 * @param[out] pp_handle_range  Pointer to pointer to the range of handles.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid operation type.
 */
uint32_t ble_gattc_attr_info_discover_req_dec(uint8_t const * const              p_buf,
                                              uint16_t                           buf_len,
                                              uint16_t * const                   p_conn_handle,
                                              ble_gattc_handle_range_t * * const pp_handle_range);

/**@brief Encodes @ref sd_ble_gattc_attr_info_discover command response.
 *
 * @sa @ref ble_gattc_attr_info_discover_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_attr_info_discover_rsp_enc(uint32_t         return_code,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gattc_exchange_mtu_request command request.
 *
 * @sa @ref ble_gattc_exchange_mtu_request_rsp_enc for response encoding.
 *
 * @param[in]  p_buf            Pointer to beginning of command request packet.
 * @param[in]  packet_len       Length (in bytes) of request packet.
 * @param[out] p_conn_handle    Pointer to connection handle of the connection.
 * @param[out] p_client_rx_mtu  Pointer to Client RX MTU size.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid operation type.
 */
uint32_t ble_gattc_exchange_mtu_request_req_dec(uint8_t const * const       p_buf,
                                                uint16_t                    packet_len,
                                                uint16_t * const            p_conn_handle,
                                                uint16_t * const            p_client_rx_mtu);

/**@brief Encodes @ref sd_ble_gattc_exchange_mtu_request command response.
 *
 * @sa @ref ble_gattc_exchange_mtu_request_req_dec for request decoding.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gattc_exchange_mtu_request_rsp_enc(uint32_t         return_code,
                                                uint8_t * const  p_buf,
                                                uint32_t * const p_buf_len);

/** @} */

#ifdef __cplusplus
}
#endif

#endif

