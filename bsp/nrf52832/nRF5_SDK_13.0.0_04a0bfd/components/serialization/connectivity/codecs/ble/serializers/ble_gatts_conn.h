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
#ifndef BLE_GATTS_CONN_H__
#define BLE_GATTS_CONN_H__

/**@file
 *
 * @defgroup ble_gatts_conn GATTS Connectivity command request decoders and command response encoders
 * @{
 * @ingroup  ser_conn_s130_codecs
 *
 * @brief    GATTS Connectivity command request decoders and command response encoders.
 */

#include "ble_gatts.h"
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Decodes @ref sd_ble_gatts_value_get command request.
 *
 * @sa @ref ble_gatts_value_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf               Pointer to beginning of command request packet.
 * @param[in] packet_len          Length (in bytes) of request packet.
 * @param[out] p_conn_handle      Pointer to the connection_handle.
 * @param[out] p_handle           Pointer to the attribute_handle.
 * @param[out] pp_value           Pointer to pointer to the Attribute Value structure.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_value_get_req_dec(uint8_t const * const       p_buf,
                                     uint16_t                    packet_len,
                                     uint16_t * const            p_conn_handle,
                                     uint16_t * const            p_handle,
                                     ble_gatts_value_t * * const pp_value);

/**@brief Encodes @ref sd_ble_gatts_value_get command response.
 *
 * @sa @ref ble_gatts_value_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_value             Pointer to Attribute Value structure.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_value_get_rsp_enc(uint32_t                   return_code,
                                     uint8_t * const            p_buf,
                                     uint32_t * const           p_buf_len,
                                     ble_gatts_value_t * const  p_value);

/**@brief Decodes @ref sd_ble_gatts_characteristic_add command request.
 *
 * @sa @ref ble_gatts_characteristic_add_rsp_enc for response encoding.
 *
 * @param[in] p_buf               Pointer to beginning of command request packet.
 * @param[in] packet_len          Length (in bytes) of request packet.
 * @param[out] p_service_handle   Pointer to the service_handle.
 * @param[out] constpp_char_md    Pointer to pointer to the location where Characteristic metadata
 *                                will be decoded.
 * @param[out] pp_attr_char_value Pointer to pointer to the location where GATT Attribute will be
 *                                decoded.
 * @param[out] pp_handles         Pointer to pointer to the location where Characteristic definition
 *                                handles will be decoded.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_characteristic_add_req_dec(uint8_t const * const              p_buf,
                                              uint32_t                           packet_len,
                                              uint16_t *                         p_service_handle,
                                              ble_gatts_char_md_t * *            constpp_char_md,
                                              ble_gatts_attr_t * * const         pp_attr_char_value,
                                              ble_gatts_char_handles_t * * const pp_handles);

/**@brief Encodes @ref ble_gatts_sys_attr_get_rsp_enc command response.
 *
 * @sa @ref ble_gatts_sys_attr_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_handles           Pointer to handle struct to be encoded.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_characteristic_add_rsp_enc(uint32_t                               return_code,
                                              uint8_t * const                        p_buf,
                                              uint32_t * const                       p_buf_len,
                                              ble_gatts_char_handles_t const * const p_handles);

/**@brief Decodes @ref sd_ble_gatts_include_add command request.
 *
 * @sa @ref ble_gatts_include_add_rsp_enc for response encoding.
 *
 * @param[in] p_buf               Pointer to beginning of command request packet.
 * @param[in] packet_len          Length (in bytes) of request packet.
 * @param[out] p_service_handle   Pointer to the service_handle.
 * @param[out] p_inc_srvc_handle  Pointer to the handle of the included service.
 * @param[out] pp_include_handle  Pointer to Pointer to 16-bit word where the assigned handle will be stored.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */

uint32_t ble_gatts_include_add_req_dec(uint8_t const * const p_buf,
                                       uint16_t              packet_len,
                                       uint16_t * const      p_service_handle,
                                       uint16_t * const      p_inc_srvc_handle,
                                       uint16_t * * const    pp_include_handle);

/**@brief Encodes @ref ble_gatts_include_add_rsp_enc command response.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_include_handle    Pointer to a 16-bit word where the assigned handle was stored.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */

uint32_t ble_gatts_include_add_rsp_enc(uint32_t               return_code,
                                       uint8_t * const        p_buf,
                                       uint32_t * const       p_buf_len,
                                       uint16_t const * const p_include_handle);

/**@brief Decodes @ref sd_ble_gatts_service_add command request.
 *
 * @sa @ref ble_gatts_service_add_rsp_enc for response encoding.
 *
 * @param[in] p_buf               Pointer to beginning of command request packet.
 * @param[in] packet_len          Length (in bytes) of request packet.
 * @param[out] p_type             Pointer to the service type.
 * @param[out] pp_uuid            Pointer to pointer to service UUID.
 * @param[out] pp_handle          Pointer to pointer to a 16-bit word where the assigned handle will be stored.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */

uint32_t ble_gatts_service_add_req_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint8_t * const       p_type,
                                       ble_uuid_t * * const  pp_uuid,
                                       uint16_t * * const    pp_handle);

/**@brief Encodes @ref ble_gatts_service_add_rsp_enc command response.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_handle            Pointer to a 16-bit word where the assigned handle was stored.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */

uint32_t ble_gatts_service_add_rsp_enc(uint32_t               return_code,
                                       uint8_t * const        p_buf,
                                       uint32_t * const       p_buf_len,
                                       uint16_t const * const p_handle);

/**@brief Decodes @ref ble_gatts_sys_attr_get_req_dec command request.
 *
 * @sa @ref ble_gatts_sys_attr_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf                 Pointer to beginning of command request packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_conn_handle        Pointer to connectiton handle.
 * @param[out] pp_sys_attr_data     Pointer to pointer to buffer where system attributes data will be filled in.
 * @param[out] pp_sys_attr_data_len Pointer to pointer to variable which contains size of buffer for system attributes.
 * @param[out] p_flags              Pointer to additional optional flags.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gatts_sys_attr_get_req_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint16_t * const      p_conn_handle,
                                        uint8_t * * const     pp_sys_attr_data,
                                        uint16_t * * const    pp_sys_attr_data_len,
                                        uint32_t * const      p_flags);

/**@brief Encodes @ref ble_gatts_sys_attr_get_rsp_enc command response.
 *
 * @sa @ref ble_gatts_sys_attr_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_sys_attr_data     Pointer to buffer where system attributes data are stored.
 * @param[in] p_sys_attr_data_len Pointer to variable which contains size of buffer for system attributes.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_sys_attr_get_rsp_enc(uint32_t               return_code,
                                        uint8_t * const        p_buf,
                                        uint32_t * const       p_buf_len,
                                        uint8_t const * const  p_sys_attr_data,
                                        uint16_t const * const p_sys_attr_data_len);

/**@brief Decodes @ref sd_ble_gatts_value_set command request.
 *
 * @sa @ref ble_gatts_value_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf          Pointer to beginning of command request packet.
 * @param[in] packet_len     Length (in bytes) of response packet.
 * @param[out] p_conn_handle Pointer to connection handle.
 * @param[out] p_handle      Pointer to attribute handle.
 * @param[out] pp_value      Pointer to pointer to attribute value structure.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */

uint32_t ble_gatts_value_set_req_dec(uint8_t const * const       p_buf,
                                     uint16_t                    packet_len,
                                     uint16_t *                  p_conn_handle,
                                     uint16_t *                  p_handle,
                                     ble_gatts_value_t * * const pp_value);

/**@brief Encodes @ref sd_ble_gatts_value_set command response.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf         Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len     \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in]      p_value        \c in: size of value returned when value was written with success
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_value_set_rsp_enc(uint32_t            return_code,
                                     uint8_t * const     p_buf,
                                     uint32_t * const    p_buf_len,
                                     ble_gatts_value_t * p_value);

/**@brief Decodes @ref sd_ble_gatts_sys_attr_set command request.
 *
 * @sa @ref ble_gatts_sys_attr_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf                Pointer to beginning of command request packet.
 * @param[in] packet_len           Length (in bytes) of request packet.
 * @param[out] p_conn_handle       Pointer to the buffer raw data to be placed in advertisement packet.
 * @param[out] pp_sys_attr_data    Pointer to pointer to system attribute data.
 * @param[out] p_sys_attr_data_len Pointer to data length for system attribute data.
 * @param[out] p_flags             Pointer to additional optional flags.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_sys_attr_set_req_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint16_t * const      p_conn_handle,
                                        uint8_t * * const     pp_sys_attr_data,
                                        uint16_t * const      p_sys_attr_data_len,
                                        uint32_t * const      p_flags);

/**@brief Encodes @ref sd_ble_gatts_sys_attr_set command response.
 *
 * @sa @ref ble_gatts_sys_attr_set_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_sys_attr_set_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes @ref ble_gatts_hvx_req_dec command request.
 *
 * @sa @ref ble_gatts_hvx_rsp_enc for response encoding.
 *
 * @param[in] p_buf                Pointer to beginning of command request packet.
 * @param[in] packet_len           Length (in bytes) of request packet.
 * @param[out] p_conn_handle       Pointer to the buffer raw data to be placed in advertisement packet.
 * @param[out] pp_hvx_params       Pointer to an HVx parameters structure.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_hvx_req_dec(uint8_t const * const            p_buf,
                               uint32_t                         packet_len,
                               uint16_t * const                 p_conn_handle,
                               ble_gatts_hvx_params_t * * const pp_hvx_params);

/**@brief Encodes @ref ble_gatts_hvx_rsp_enc command response.
 *
 * @sa @ref ble_gatts_hvx_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_bytes_written     Pointer to number of bytes written.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_hvx_rsp_enc(uint32_t               return_code,
                               uint8_t * const        p_buf,
                               uint32_t * const       p_buf_len,
                               uint16_t const * const p_bytes_written);

/**@brief Decodes @ref sd_ble_gatts_descriptor_add command request.
 *
 * @sa @ref ble_gatts_descriptor_add_rsp_enc for response encoding.
 *
 * @param[in] p_buf                Pointer to beginning of command request packet.
 * @param[in] packet_len           Length (in bytes) of request packet.
 * @param[out] p_char_handle       Pointer to buffer where characteristic handle will be.
                                   returned.
 * @param[out] pp_attr             Pointer to pointer to an attribute structure.
 * @param[out] pp_handle           Pointer to pointer to descriptor handle.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_descriptor_add_req_dec(uint8_t const * const      p_buf,
                                          uint32_t                   packet_len,
                                          uint16_t * const           p_char_handle,
                                          ble_gatts_attr_t * * const pp_attr,
                                          uint16_t * * const         pp_handle);

/**@brief Encodes @ref sd_ble_gatts_descriptor_add command response.
 *
 * @sa @ref ble_gatts_descriptor_add_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_handle            Pointer to descriptor handle value.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_descriptor_add_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len,
                                          uint16_t *        p_handle);

/**@brief Decodes @ref sd_ble_gatts_rw_authorize_reply command request.
 *
 * @sa @ref ble_gatts_rw_authorize_reply_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] pp_reply_params Pointer to pointer to \ref ble_gatts_rw_authorize_reply_params_t .
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */

uint32_t ble_gatts_rw_authorize_reply_req_dec(
    uint8_t const * const p_buf,
    uint32_t
    packet_len,
    uint16_t *
    p_conn_handle,
    ble_gatts_rw_authorize_reply_params_t * * const
    pp_reply_params);

/**@brief Encodes @ref sd_ble_gatts_rw_authorize_reply command response.
 *
 * @sa @ref ble_gatts_rw_authorize_reply_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_rw_authorize_reply_rsp_enc(uint32_t         return_code,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gatts_service_changed command request.
 *
 * @sa @ref ble_gatts_service_changed_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] p_start_handle  Pointer to start handle.
 * @param[out] p_end_handle    Pointer to end handle.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gatts_service_changed_req_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint16_t *            p_conn_handle,
                                           uint16_t *            p_start_handle,
                                           uint16_t *            p_end_handle);

/**@brief Encodes @ref sd_ble_gatts_service_changed command response.
 *
 * @sa @ref ble_gatts_service_changed_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_service_changed_rsp_enc(uint32_t         return_code,
                                           uint8_t * const  p_buf,
                                           uint32_t * const p_buf_len);

/**@brief Decodes @ref ble_gatts_attr_get_req_dec command request.
 *
 * @sa @ref ble_gatts_attr_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf                 Pointer to beginning of command request packet.
 * @param[in] packet_len            Length (in bytes) of response packet.
 * @param[out] p_handle             Pointer to handle.
 * @param[out] pp_uuid              Pointer to pointer to location for decoded uuid structure.
 * @param[out] pp_md                Pointer to pointer to location for md structure.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gatts_attr_get_req_dec(uint8_t   const * const p_buf,
                                    uint32_t                packet_len,
                                    uint16_t              * p_handle,
                                    ble_uuid_t          * * pp_uuid,
                                    ble_gatts_attr_md_t * * pp_md);

/**@brief Encodes @ref ble_gatts_attr_get_rsp_enc command response.
 *
 * @sa @ref ble_gatts_attr_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_uuid              Pointer to structure to be encoded.
 * @param[in] p_md                Pointer to structure to be encoded.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_attr_get_rsp_enc(uint32_t               return_code,
                                    uint8_t * const        p_buf,
                                    uint32_t * const       p_buf_len,
                                    ble_uuid_t           * p_uuid,
                                    ble_gatts_attr_md_t  * p_md);

/**@brief Decodes @ref ble_gatts_initial_user_handle_get_req_dec command request.
 *
 * @sa @ref ble_gatts_initial_user_handle_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                 Pointer to beginning of command request packet.
 * @param[in]  packet_len            Length (in bytes) of response packet.
 * @param[out] pp_handle             Pointer to pointer to handle.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gatts_initial_user_handle_get_req_dec(uint8_t   const * const p_buf,
                                                   uint32_t                packet_len,
                                                   uint16_t            * * pp_handle);

/**@brief Encodes @ref ble_gatts_initial_user_handle_get_rsp_enc command response.
 *
 * @sa @ref ble_gatts_initial_user_handle_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_handle            Pointer to handle to be encoded.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_initial_user_handle_get_rsp_enc(uint32_t           return_code,
                                                   uint8_t * const    p_buf,
                                                   uint32_t * const   p_buf_len,
                                                   uint16_t         * p_handle);

/**@brief Decodes @ref sd_ble_gatts_rw_authorize_reply command request.
 *
 *     @ref ble_gatts_exchange_mtu_reply_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] p_server_rx_mtu Pointer to Server RX MTU size.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */

uint32_t ble_gatts_exchange_mtu_reply_req_dec(uint8_t const * const       p_buf,
                                              uint16_t                    packet_len,
                                              uint16_t * const            p_conn_handle,
                                              uint16_t * const            p_server_rx_mtu);

/**@brief Encodes @ref sd_ble_gatts_rw_authorize_reply command response.
 *
 *     @ref ble_gatts_exchange_mtu_reply_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gatts_exchange_mtu_reply_rsp_enc(uint32_t         return_code,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //BLE_GATTS_CONN_H__

