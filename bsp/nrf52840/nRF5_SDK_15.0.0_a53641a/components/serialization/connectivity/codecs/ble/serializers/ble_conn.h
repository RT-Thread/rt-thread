/**
 * Copyright (c) 2013 - 2018, Nordic Semiconductor ASA
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
#ifndef BLE_CONN_H__
#define BLE_CONN_H__

/**
 * @addtogroup ser_conn_s130_codecs Connectivity codecs for S132 and S140
 * @ingroup ser_codecs_conn
 */

/**@file
 *
 * @defgroup ble_conn Connectivity command request decoders and command response encoders
 * @{
 * @ingroup  ser_conn_s130_codecs
 *
 * @brief    Connectivity command request decoders and command response encoders.
 */
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
/**@brief Decodes @ref sd_ble_tx_packet_count_get command request.
 *
 * @sa @ref ble_tx_packet_count_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Pointer to connection handle.
 * @param[out] pp_count       Pointer to pointer to location for count.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_tx_packet_count_get_req_dec(uint8_t const * const p_buf,
                                         uint16_t              packet_len,
                                         uint16_t      * const p_conn_handle,
                                         uint8_t * * const     pp_count);

/**@brief Encodes @ref sd_ble_tx_packet_count_get command response.
 *
 * @sa @ref ble_tx_packet_count_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_count             Pointer to count value.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_tx_packet_count_get_rsp_enc(uint32_t              return_code,
                                         uint8_t * const       p_buf,
                                         uint32_t * const      p_buf_len,
                                         uint8_t const * const p_count);
#endif

/**@brief Event encoding dispatcher.
 *
 * The event encoding dispatcher will route the event packet to the correct encoder which in turn
 * encodes the contents of the event and updates the \p p_buf buffer.
 *
 * @param[in] p_event          Pointer to the \ref ble_evt_t buffer that shall be encoded.
 * @param[in] event_len        Size (in bytes) of \p p_event buffer.
 * @param[out] p_buf           Pointer to the beginning of a buffer for encoded event packet.
 * @param[in,out] p_buf_len    \c in: Size (in bytes) of \p p_buf buffer.
 *                             \c out: Length of encoded contents in \p p_buf.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_NOT_SUPPORTED   Event encoder is not implemented.
 */
uint32_t ble_event_enc(ble_evt_t const * const p_event,
                       uint32_t                event_len,
                       uint8_t * const         p_buf,
                       uint32_t * const        p_buf_len);

/**@brief Decodes @ref sd_ble_version_get command request.
 *
 * @sa @ref ble_version_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_version     Pointer to pointer to @ref ble_version_t address.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_version_get_req_dec(uint8_t const * const   p_buf,
                                 uint16_t                packet_len,
                                 ble_version_t * * const pp_version);

/**@brief Encodes @ref sd_ble_version_get command response.
 *
 * @sa @ref ble_version_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_version           Pointer to @ref ble_version_t address.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_version_get_rsp_enc(uint32_t                    return_code,
                                 uint8_t * const             p_buf,
                                 uint32_t * const            p_buf_len,
                                 ble_version_t const * const p_version);


/**@brief Decodes @ref sd_ble_opt_get command request.
 *
 * @sa @ref ble_opt_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_opt_id       Pointer to pointer to @ref ble_version_t address.
 * @param[out] pp_opt         Pointer to pointer to @ref ble_opt_t address.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_opt_get_req_dec(uint8_t const * const   p_buf,
                             uint16_t                packet_len,
                             uint32_t *  const       p_opt_id,
                             ble_opt_t **const       pp_opt );


/**@brief Encodes @ref sd_ble_opt_get command response.
 *
 * @sa @ref ble_opt_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] opt_id              identifies type of ble_opt_t union
 * @param[in] p_opt               Pointer to @ref ble_opt_t union.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */

uint32_t ble_opt_get_rsp_enc(uint32_t                return_code,
                             uint8_t * const         p_buf,
                             uint32_t * const        p_buf_len,
                             uint32_t                opt_id,
                             ble_opt_t const * const p_opt);


/**@brief Decodes @ref sd_ble_opt_set command request.
 *
 * @sa @ref ble_opt_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_opt_id       Pointer to @ref ble_opt_t union type identifier.
 * @param[out] pp_opt         Pointer to pointer to @ref ble_opt_t union.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_opt_set_req_dec(uint8_t const * const   p_buf,
                             uint16_t                packet_len,
                             uint32_t *  const       p_opt_id,
                             ble_opt_t **const       pp_opt );


/**@brief Encodes @ref sd_ble_opt_set command response.
 *
 * @sa @ref ble_opt_set_req_dec for request decoding.
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

uint32_t ble_opt_set_rsp_enc(uint32_t                return_code,
                             uint8_t * const         p_buf,
                             uint32_t * const        p_buf_len);


/**@brief Decodes @ref sd_ble_uuid_encode command request.
 *
 * @sa @ref ble_uuid_encode_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_uuid        Pointer to pointer to @ref ble_uuid_t structure.
 * @param[out] pp_uuid_le_len Pointer to pointer to the length of encoded UUID.
 * @param[out] pp_uuid_le     Pointer to pointer to buffer where encoded UUID will be stored.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_uuid_encode_req_dec(uint8_t const * const p_buf,
                                 uint16_t              packet_len,
                                 ble_uuid_t * * const  pp_uuid,
                                 uint8_t * * const     pp_uuid_le_len,
                                 uint8_t * * const     pp_uuid_le);

/**@brief Encodes @ref sd_ble_uuid_encode command response.
 *
 * @sa @ref ble_uuid_encode_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] uuid_le_len         Length of the encoded UUID.
 * @param[in] p_uuid_le           Pointer to the buffer with encoded UUID.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_uuid_encode_rsp_enc(uint32_t              return_code,
                                 uint8_t * const       p_buf,
                                 uint32_t * const      p_buf_len,
                                 uint8_t               uuid_le_len,
                                 uint8_t const * const p_uuid_le);

/**@brief Decodes @ref sd_ble_uuid_decode command request.
 *
 * @sa @ref ble_uuid_decode_rsp_enc for response encoding.
 *
 * @param[in]  p_buf           Pointer to beginning of command request packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_uuid_le_len   Pointer to the length of encoded UUID.
 * @param[out] pp_uuid_le      Pointer to pointer to buffer where encoded UUID will be stored.
 * @param[out] pp_uuid         Pointer to pointer to @ref ble_uuid_t structure.
 *                             \c It will be set to NULL if p_uuid is not present in the packet.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_uuid_decode_req_dec(uint8_t const * const p_buf,
                                 uint32_t const        packet_len,
                                 uint8_t *             p_uuid_le_len,
                                 uint8_t * * const     pp_uuid_le,
                                 ble_uuid_t * * const  pp_uuid);

/**@brief Encodes @ref sd_ble_uuid_decode command response.
 *
 * @sa @ref ble_uuid_decode_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_uuid              Pointer to the buffer with encoded UUID.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_uuid_decode_rsp_enc(uint32_t                 return_code,
                                 uint8_t * const          p_buf,
                                 uint32_t * const         p_buf_len,
                                 ble_uuid_t const * const p_uuid);

/**@brief Decodes @ref sd_ble_uuid_vs_add command request.
 *
 * @sa @ref ble_uuid_vs_add_rsp_enc for response encoding.
 *
 * @param[in]  p_buf        Pointer to beginning of command request packet.
 * @param[in]  packet_len   Length (in bytes) of response packet.
 * @param[out] pp_uuid      Pointer to pointer to UUID.
 *                          \c It will be set to NULL if p_uuid is not present in the packet.
 * @param[out] pp_uuid_type Pointer to pointer to UUID type.
 *                          \c It will be set to NULL if p_uuid_type is not present in the packet.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ble_uuid_vs_add_req_dec(uint8_t const * const   p_buf,
                                 uint16_t                packet_len,
                                 ble_uuid128_t * * const pp_uuid,
                                 uint8_t * * const       pp_uuid_type);

/**@brief Encodes @ref sd_ble_uuid_vs_add command response.
 *
 * @sa @ref ble_uuid_vs_add_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_uuid_type         Pointer to the UUID type.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_uuid_vs_add_rsp_enc(uint32_t              return_code,
                                 uint8_t * const       p_buf,
                                 uint32_t * const      p_buf_len,
                                 uint8_t const * const p_uuid_type);

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
/**@brief Decodes @ref sd_ble_enable command request.
 *
 * @sa @ref ble_enable_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 * @param[out] pp_ble_enable_params Pointer to pointer to ble_enable_params_t.
 *                                  \c It will be set to NULL if p_ble_enable_params is not present in the packet.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ble_enable_req_dec(uint8_t const * const         p_buf,
                            uint32_t                      packet_len,
                            ble_enable_params_t * * const pp_ble_enable_params);
#else
/**@brief Decodes @ref sd_ble_enable command request.
 *
 * @sa @ref ble_enable_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ble_enable_req_dec(uint8_t const * const         p_buf,
                            uint32_t                      packet_len);

#endif
/**@brief Encodes @ref sd_ble_enable command response.
 *
 * @sa @ref ble_enable_req_dec for request decoding.
 *
 * @param[in]  return_code        Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_enable_rsp_enc(uint32_t         return_code,
                            uint8_t * const  p_buf,
                            uint32_t * const p_buf_len);

/**@brief Pre-decodes opt_id of @ref ble_opt_t for middleware.
 *
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] packet_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in,out] p_opt_id        Pointer to opt_id which identifies type of @ref ble_opt_t union.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_opt_id_pre_dec(uint8_t const * const   p_buf,
                            uint16_t                packet_len,
                            uint32_t *  const       p_opt_id);

/**@brief Decodes @ref sd_ble_user_mem_reply command request.
 *
 * @sa @ref ble_user_mem_reply_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 * @param[in]  p_conn_handle        Pointer to Connection Handle.
 * @param[in,out] pp_block          Pointer to pointer to ble_user_mem_block_t.
 *                                  \c It will be set to NULL if p_block is not present in the packet.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ble_user_mem_reply_req_dec(uint8_t const * const          p_buf,
                                    uint32_t                       packet_len,
                                    uint16_t * const               p_conn_handle,
                                    ble_user_mem_block_t * * const pp_block);

/**@brief Encodes @ref sd_ble_user_mem_reply command response.
 *
 * @sa @ref ble_user_mem_reply_req_dec for request decoding.
 *
 * @param[in]  return_code        Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_user_mem_reply_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

#if NRF_SD_BLE_API_VERSION >= 4
/**@brief Decodes @ref sd_ble_cfg_set command request.
 *
 * @sa @ref ble_cfg_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf                Pointer to beginning of command request packet.
 * @param[in]  packet_len           Length (in bytes) of response packet.
 * @param[in]  p_cfg_id             Pointer to ConfigurationId.
 * @param[in,out] pp_cfg            Pointer to pointer to configuration struct.
 *                                  \c It will be set to NULL if p_block is not present in the packet.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ble_cfg_set_req_dec(uint8_t const * const p_buf,
                            uint32_t               packet_len,
                            uint32_t *             p_cfg_id,
                            ble_cfg_t * * const    pp_cfg);

/**@brief Encodes @ref sd_ble_cfg_set command response.
 *
 * @sa @ref ble_cfg_set_req_dec for request decoding.
 *
 * @param[in]  return_code        Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_cfg_set_rsp_enc(uint32_t        return_code,
                            uint8_t * const  p_buf,
                            uint32_t * const p_buf_len);

#endif

/** @} */


#ifdef __cplusplus
}
#endif

#endif
