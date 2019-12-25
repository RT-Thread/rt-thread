/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
#ifndef BLE_GAP_CONN_H__
#define BLE_GAP_CONN_H__

/**@file
 *
 * @defgroup ble_gap_conn GAP Connectivity command request decoders and command response encoders
 * @{
 * @ingroup  ser_conn_s130_codecs
 *
 * @brief    GAP Connectivity command request decoders and command response encoders
 */
#include "ble_gap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Decodes @ref sd_ble_gap_authenticate command request.
 *
 * @sa @ref ble_gap_authenticate_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle
 * @param[out] pp_sec_params   Pointer to pointer to security parameters.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_authenticate_req_dec(uint8_t const * const          p_buf,
                                      uint32_t                       packet_len,
                                      uint16_t * const               p_conn_handle,
                                      ble_gap_sec_params_t * * const pp_sec_params);

/**@brief Encodes @ref sd_ble_gap_authenticate command response.
 *
 * @sa @ref ble_gap_authenticate_req_dec for request decoding.
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
uint32_t ble_gap_authenticate_rsp_enc(uint32_t         return_code,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

#if defined(NRF_SD_BLE_API_VERSION) && (NRF_SD_BLE_API_VERSION <= 5)
/**@brief Decodes @ref sd_ble_gap_adv_data_set command request.
 *
 * @sa @ref ble_gap_adv_data_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf           Pointer to beginning of command request packet.
 * @param[in]  packet_len      Length (in bytes) of request packet.
 * @param[out] pp_data         Pointer to the buffer raw data to be placed in advertisement packet.
 * @param[out] p_dlen          Pointer to data length for p_data.
 * @param[out] pp_sr_data      Pointer to the buffer raw data to be placed in scan response packet.
 * @param[out] p_srdlen        Pointer to data length for p_sr_data.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_adv_data_set_req_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint8_t * * const     pp_data,
                                      uint8_t *             p_dlen,
                                      uint8_t * * const     pp_sr_data,
                                      uint8_t *             p_srdlen);

/**@brief Encodes @ref sd_ble_gap_adv_data_set command response.
 *
 * @sa @ref ble_gap_adv_data_set_req_dec for request decoding.
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
uint32_t ble_gap_adv_data_set_rsp_enc(uint32_t         return_code,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);
#endif
/**@brief Decodes @ref sd_ble_gap_adv_start command request.
 *
 * @sa @ref ble_gap_adv_start_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_adv_params  Pointer to pointer to advertising parameters.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_adv_start_req_dec(uint8_t const * const          p_buf,
                                   uint32_t                       packet_len,
#if NRF_SD_BLE_API_VERSION > 5
                                   uint8_t *                     p_adv_handle
#else
                                   ble_gap_adv_params_t * * const pp_adv_params
#endif
#if NRF_SD_BLE_API_VERSION >= 4
                                   ,uint8_t *                     p_conn_cfg_tag
#endif
                                   );

/**@brief Encodes @ref sd_ble_gap_adv_start command response.
 *
 * @sa @ref ble_gap_adv_start_req_dec for request decoding.
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
uint32_t ble_gap_adv_start_rsp_enc(uint32_t         return_code,
                                   uint8_t * const  p_buf,
                                   uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_device_name_get command request.
 *
 * @sa @ref ble_gap_device_name_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] pp_dev_name     Pointer to pointer to device name buffer.
 * @param[out] pp_dev_name_len Pointer to pointer to device name length location.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_name_get_req_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint8_t * *           pp_dev_name,
                                         uint16_t * *          pp_dev_name_len);

/**@brief Encodes @ref sd_ble_gap_device_name_get command response.
 *
 * @param[in]      return_code     Return code indicating if command was successful or not.
 * @param[in]      p_dev_name      Pointer to device name buffer.
 * @param[in]      p_dev_name_len  Length of device name buffer.
 * @param[in]      p_buf           Pointer to buffer where encoded data command response will be
 *                                 returned.
 * @param[in, out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                 \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_name_get_rsp_enc(uint32_t              return_code,
                                         uint8_t const * const p_dev_name,
                                         uint16_t *            p_dev_name_len,
                                         uint8_t * const       p_buf,
                                         uint32_t * const      p_buf_len);

/**@brief Decodes @ref sd_ble_gap_conn_param_update command request.
 *
 * @sa @ref ble_gap_conn_param_update_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Pointer to connection handle.
 * @param[out] pp_conn_params Pointer to pointer to connection parameters.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid value for connection
 *                                    parameters field present.
 */
uint32_t ble_gap_conn_param_update_req_dec(uint8_t const * const           p_buf,
                                           uint32_t                        packet_len,
                                           uint16_t *                      p_conn_handle,
                                           ble_gap_conn_params_t * * const pp_conn_params);

/**@brief Encodes @ref sd_ble_gap_conn_param_update command response.
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
uint32_t ble_gap_conn_param_update_rsp_enc(uint32_t         return_code,
                                           uint8_t * const  p_buf,
                                           uint32_t * const p_buf_len);


/**@brief Decodes @ref sd_ble_gap_disconnect command request.
 *
 * @sa @ref ble_gap_disconnect_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[in] p_conn_handle   Pointer to Connection Handle.
 * @param[in] p_hci_status    Pointer to HCI Status Code.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_disconnect_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint16_t * const      p_conn_handle,
                                    uint8_t * const       p_hci_status);

/**@brief Encodes @ref sd_ble_gap_disconnect command response.
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
uint32_t ble_gap_disconnect_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_tx_power_set command request.
 *
 * @sa @ref ble_gap_tx_power_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[in] p_tx_power      Pointer to TX power value.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_tx_power_set_req_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
#if NRF_SD_BLE_API_VERSION > 5
                                      uint8_t * p_role, uint16_t * p_handle,
#endif
                                      int8_t *              p_tx_power);

/**@brief Encodes @ref sd_ble_gap_tx_power_set command response.
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
uint32_t ble_gap_tx_power_set_rsp_enc(uint32_t         return_code,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_ppcp_set command request.
 *
 * @sa @ref ble_gap_ppcp_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_conn_params Pointer to pointer to connection parameters to be set.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid value for connection
 *                                    parameters field present.
 */
uint32_t ble_gap_ppcp_set_req_dec(uint8_t const * const           p_buf,
                                  uint32_t                        packet_len,
                                  ble_gap_conn_params_t * * const pp_conn_params);

/**@brief Encodes @ref sd_ble_gap_ppcp_set command response.
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
uint32_t ble_gap_ppcp_set_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);


/**@brief Decodes @ref sd_ble_gap_ppcp_get command request.
 *
 * @sa @ref ble_gap_ppcp_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_conn_params Pointer to pointer to ble_gap_conn_params_t.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_ppcp_get_req_dec(uint8_t const * const           p_buf,
                                  uint16_t                        packet_len,
                                  ble_gap_conn_params_t * * const pp_conn_params);

/**@brief Encodes @ref sd_ble_gap_ppcp_get command response.
 *
 * @sa @ref ble_gap_ppcp_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_conn_params       Pointer to ble_gap_conn_params_t.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_ppcp_get_rsp_enc(uint32_t                            return_code,
                                  uint8_t * const                     p_buf,
                                  uint32_t * const                    p_buf_len,
                                  ble_gap_conn_params_t const * const p_conn_params);


uint32_t ble_gap_adv_stop_req_dec(uint8_t const * const p_buf,
                                  uint16_t              packet_len,
                                  uint8_t *             p_adv_handle);
/**@brief Encodes @ref sd_ble_gap_adv_stop command response.
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
uint32_t ble_gap_adv_stop_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_auth_key_reply command request.
 *
 * @sa @ref ble_gap_auth_key_reply_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Pointer to connection handle.
 * @param[out] p_key_type     Pointer to key type.
 * @param[out] pp_key         Pointer to pointer to buffer for incoming key.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_auth_key_reply_req_dec(uint8_t const * const p_buf,
                                        uint16_t              packet_len,
                                        uint16_t *            p_conn_handle,
                                        uint8_t *             p_key_type,
                                        uint8_t * * const     pp_key);

/**@brief Encodes @ref sd_ble_gap_auth_key_reply command response.
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
uint32_t ble_gap_auth_key_reply_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_sec_params_reply command request.
 *
 * @sa @ref ble_gap_sec_params_reply_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Pointer to connection handle.
 * @param[out] p_sec_status   Pointer to security status.
 * @param[out] pp_sec_params  Pointer to pointer to security parameters structure.
 * @param[out] pp_sec_keyset  Pointer to pointer to security keyset structure.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 * @retval NRF_ERROR_INVALID_DATA     Decoding failure. Invalid value for connection
 *                                    parameters field present.
 */
uint32_t ble_gap_sec_params_reply_req_dec(uint8_t const * const          p_buf,
                                          uint32_t                       packet_len,
                                          uint16_t *                     p_conn_handle,
                                          uint8_t *                      p_sec_status,
                                          ble_gap_sec_params_t * * const pp_sec_params,
                                          ble_gap_sec_keyset_t * * const pp_sec_keyset);

/**@brief Encodes @ref sd_ble_gap_sec_params_reply command response.
 *
 * @param[in]      return_code    Return code indicating if command was successful or not.
 * @param[in]      p_buf          Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in]      p_sec_keyset   Pointer to security keyset structure.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_sec_params_reply_rsp_enc(uint32_t                     return_code,
                                          uint8_t * const              p_buf,
                                          uint32_t * const             p_buf_len,
                                          ble_gap_sec_keyset_t * const p_sec_keyset);

/**@brief Decodes @ref sd_ble_gap_rssi_start command request.
 *
 * @sa @ref ble_gap_rssi_start_rsp_enc for response encoding.
 *
 * @param[in]  p_buf           Pointer to beginning of command request packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle.
 * @param[out] p_threshold_dbm Pointer to threshold in dBm.
 * @param[out] p_skip_count    Pointer to sample skip count.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_rssi_start_req_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint16_t *            p_conn_handle,
                                    uint8_t *             p_threshold_dbm,
                                    uint8_t *             p_skip_count);

/**@brief Encodes @ref sd_ble_gap_rssi_start command response.
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

uint32_t ble_gap_rssi_start_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_rssi_stop command request.
 *
 * @sa @ref ble_gap_rssi_stop_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] conn_handle    Pointer to connection handle.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */

uint32_t ble_gap_rssi_stop_req_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint16_t *            conn_handle);

/**@brief Encodes @ref sd_ble_gap_rssi_stop command response.
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

uint32_t ble_gap_rssi_stop_rsp_enc(uint32_t         return_code,
                                   uint8_t * const  p_buf,
                                   uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_appearance_get command request.
 *
 * @sa @ref ble_gap_appearance_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_appearance  Pointer to pointer to uint16_t appearance.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_appearance_get_req_dec(uint8_t const * const p_buf,
                                        uint16_t              packet_len,
                                        uint16_t * * const    pp_appearance);

/**@brief Encodes @ref sd_ble_gap_appearance_get command response.
 *
 * @sa @ref ble_gap_appearance_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_appearance        Pointer to uint16_t appearance.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_appearance_get_rsp_enc(uint32_t               return_code,
                                        uint8_t * const        p_buf,
                                        uint32_t * const       p_buf_len,
                                        uint16_t const * const p_appearance);


/**@brief Decodes @ref sd_ble_gap_appearance_set command request.
 *
 * @sa @ref ble_gap_tx_power_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] buf_len         Length (in bytes) of the packet.
 * @param[out] p_appearance   Pointer to the appearance.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_appearance_set_req_dec(uint8_t const * const p_buf,
                                        uint32_t              buf_len,
                                        uint16_t * const      p_appearance);

/**@brief Encodes @ref sd_ble_gap_appearance_set command response.
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
uint32_t ble_gap_appearance_set_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);


/**@brief Decodes @ref sd_ble_gap_sec_info_reply command request.
 *
 * @sa @ref ble_gap_sec_info_reply_rsp_enc for response encoding.
 *
 * @param[in] p_buf              Pointer to beginning of command request packet.
 * @param[in] packet_len         Length (in bytes) of the packet.
 * @param[out] p_conn_handle     Pointer to the Connection Handle.
 * @param[out] pp_enc_info       Pointer to pointer to Encryption Information.
 * @param[out] pp_id_info        Pointer to pointer to ID Information.
 * @param[out] pp_sign_info      Pointer to pointer to Signing Information.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_sec_info_reply_req_dec(uint8_t const * const         p_buf,
                                        uint16_t                      packet_len,
                                        uint16_t *                    p_conn_handle,
                                        ble_gap_enc_info_t * * const  pp_enc_info,
                                        ble_gap_irk_t * * const       pp_id_info,
                                        ble_gap_sign_info_t * * const pp_sign_info);

/**@brief Encodes @ref sd_ble_gap_sec_info_reply command response.
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
uint32_t ble_gap_sec_info_reply_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_device_name_set command request.
 *
 * @sa @ref ble_gap_device_name_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf              Pointer to beginning of command request packet.
 * @param[in] packet_len         Length (in bytes) of the packet.
 * @param[out] pp_write_perm     Pointer to pointer to write permissions filed.
 * @param[out] pp_dev_name       Pointer to pointer to device name string.
 * @param[out] p_dev_name_len    Pointer to device name string length.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_name_set_req_dec(uint8_t const * const             p_buf,
                                         uint32_t                          packet_len,
                                         ble_gap_conn_sec_mode_t * * const pp_write_perm,
                                         uint8_t * * const                 pp_dev_name,
                                         uint16_t * const                  p_dev_name_len);


/**@brief Encodes @ref sd_ble_gap_device_name_set command response.
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
uint32_t ble_gap_device_name_set_rsp_enc(uint32_t         return_code,
                                         uint8_t * const  p_buf,
                                         uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_conn_sec_get command request.
 *
 * @sa @ref ble_gap_conn_sec_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Pointer to Connection Handle.
 * @param[out] pp_conn_sec    Pointer to pointer to @ref ble_gap_conn_sec_t to be filled by
 *                            the SoftDevice.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_conn_sec_get_req_dec(uint8_t const * const        p_buf,
                                      uint32_t                     packet_len,
                                      uint16_t *                   p_conn_handle,
                                      ble_gap_conn_sec_t * * const pp_conn_sec);

/**@brief Encodes @ref sd_ble_gap_conn_sec_get command response.
 *
 * @sa @ref ble_gap_conn_sec_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[in] p_conn_sec          Pointer to @ref ble_gap_conn_sec_t to be encoded.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_conn_sec_get_rsp_enc(uint32_t                   return_code,
                                      ble_gap_conn_sec_t * const p_conn_sec,
                                      uint8_t * const            p_buf,
                                      uint32_t * const           p_buf_len);

#ifndef S112
/**@brief Encodes @ref sd_ble_gap_scan_stop command response.
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
uint32_t ble_gap_scan_stop_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_connect command request.
 *
 * @sa @ref ble_gap_connect_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_addr        Pointer to pointer to peer address @ref ble_gap_addr_t.
 * @param[out] pp_scan_params Pointer to pointer to @ref ble_gap_scan_params_t.
 * @param[out] pp_conn_params Pointer to pointer to @ref ble_gap_conn_params_t.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_connect_req_dec(uint8_t const * const           p_buf,
                                 uint32_t                        packet_len,
                                 ble_gap_addr_t * * const        pp_addr,
                                 ble_gap_scan_params_t * * const pp_scan_params,
                                 ble_gap_conn_params_t * * const pp_conn_params
#if NRF_SD_BLE_API_VERSION >= 4
                                 ,uint8_t *                      p_conn_cfg_tag
#endif
                                );

/**@brief Encodes @ref sd_ble_gap_connect command response.
 *
 * @sa @ref ble_gap_connect_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_connect_rsp_enc(uint32_t         return_code,
                                 uint8_t * const  p_buf,
                                 uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_scan_start command request.
 *
 * @sa @ref ble_gap_scan_start_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_scan_params Pointer to pointer to @ref ble_gap_scan_params_t.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_scan_start_req_dec(uint8_t const * const     p_buf,
                                    uint32_t                  packet_len,
                                    ble_gap_scan_params_t * * const pp_scan_params
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
                                    ,ble_data_t * * const pp_adv_report_buffer
#endif
                                    );

/**@brief Encodes @ref sd_ble_gap_scan_start command response.
 *
 * @sa @ref ble_gap_scan_start_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_scan_start_rsp_enc(uint32_t         return_code,
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
                                    ble_data_t *p_ble_data,
#endif
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Encodes @ref sd_ble_gap_connect_cancel command response.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_connect_cancel_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);


/**@brief Decodes @ref sd_ble_gap_encrypt command request.
 *
 * @sa @ref ble_gap_encrypt_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Pointer connection_handle.
 * @param[out] pp_master_id   Pointer to pointer to @ref ble_gap_master_id_t.
 * @param[out] pp_enc_info    Pointer to pointer to @ref ble_gap_enc_info_t.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */

uint32_t ble_gap_encrypt_req_dec(uint8_t        const * const p_buf,
                                 uint16_t                     packet_len,
                                 uint16_t             * const p_conn_handle,
                                 ble_gap_master_id_t ** const pp_master_id,
                                 ble_gap_enc_info_t  ** const pp_enc_info);

/**@brief Encodes @ref sd_ble_gap_encrypt command response.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_encrypt_rsp_enc(uint32_t          return_code,
                                 uint8_t   * const p_buf,
                                 uint32_t  * const p_buf_len);

#endif

/**@brief Decodes @ref sd_ble_gap_rssi_get command request.
 *
 * @sa @ref ble_gap_rssi_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[in] p_conn_handle   Connection handle.
 * @param[out] pp_rssi        Pointer to pointer to RSSI value.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_rssi_get_req_dec(uint8_t const * const p_buf,
                                  uint16_t              packet_len,
                                  uint16_t *            p_conn_handle,
                                  int8_t * * const      pp_rssi
#if NRF_SD_BLE_API_VERSION > 5
                                  ,uint8_t * * const      pp_ch_index
#endif
                                  );

/**@brief Encodes @ref sd_ble_gap_rssi_get command response.
 *
 * @sa @ref ble_gap_rssi_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_rssi              RSSI value.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_rssi_get_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len,
                                  int8_t *         p_rssi
#if NRF_SD_BLE_API_VERSION > 5
                                  ,uint8_t * p_ch_index
#endif
                                  );

/**@brief Decodes @ref sd_ble_gap_keypress_notify command request.
 *
 * @sa @ref ble_gap_keypress_notify_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Connection handle.
 * @param[out] p_kp_not       Pointer kp_not value.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_keypress_notify_req_dec(uint8_t const * const          p_buf,
                                          uint32_t                       packet_len,
                                          uint16_t *                     p_conn_handle,
                                          uint8_t *                      p_kp_not);

/**@brief Encodes @ref sd_ble_gap_keypress_notify command response.
 *
 * @sa @ref ble_gap_keypress_notify_req_dec for request decoding.
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
uint32_t ble_gap_keypress_notify_rsp_enc(uint32_t                     return_code,
                                          uint8_t * const              p_buf,
                                          uint32_t * const             p_buf_len);

/**@brief Decodes @ref sd_ble_gap_lesc_dhkey_reply command request.
 *
 * @sa @ref ble_gap_lesc_dhkey_reply_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Connection handle.
 * @param[out] pp_dhkey       Pointer to pointer to dhkey struct.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_lesc_dhkey_reply_req_dec(uint8_t const * const          p_buf,
                                          uint32_t                       packet_len,
                                          uint16_t *                     p_conn_handle,
                                          ble_gap_lesc_dhkey_t * *       pp_dhkey);

/**@brief Encodes @ref sd_ble_gap_lesc_dhkey_reply command response.
 *
 * @sa @ref ble_gap_lesc_dhkey_reply_req_dec for request decoding.
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
uint32_t ble_gap_lesc_dhkey_reply_rsp_enc(uint32_t                     return_code,
                                          uint8_t * const              p_buf,
                                          uint32_t * const             p_buf_len);

/**@brief Decodes @ref sd_ble_gap_lesc_oob_data_set command request.
 *
 * @sa @ref ble_gap_lesc_oob_data_set_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Connection handle.
 * @param[out] pp_oobd_own    Pointer to pointer to own OOB data struct.
 * @param[out] pp_oobd_peer   Pointer to pointer to peer OOB data struct.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_lesc_oob_data_set_req_dec(uint8_t const * const      p_buf,
                                          uint32_t                    packet_len,
                                          uint16_t *                  p_conn_handle,
                                          ble_gap_lesc_oob_data_t * * pp_oobd_own,
                                          ble_gap_lesc_oob_data_t * * pp_oobd_peer);

/**@brief Encodes @ref sd_ble_gap_lesc_oob_data_set command response.
 *
 * @sa @ref ble_gap_lesc_oob_data_set_req_dec for request decoding.
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
uint32_t ble_gap_lesc_oob_data_set_rsp_enc(uint32_t                    return_code,
                                          uint8_t * const              p_buf,
                                          uint32_t * const             p_buf_len);

/**@brief Decodes @ref sd_ble_gap_lesc_oob_data_get command request.
 *
 * @sa @ref ble_gap_lesc_oob_data_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_handle  Connection handle.
 * @param[out] pp_pk_own      Pointer to pointer to PK.
 * @param[out] pp_oobd_own    Pointer to pointer to own OOB data struct.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_lesc_oob_data_get_req_dec(uint8_t const * const         p_buf,
                                          uint32_t                       packet_len,
                                          uint16_t *                     p_conn_handle,
                                          ble_gap_lesc_p256_pk_t * *     pp_pk_own,
                                          ble_gap_lesc_oob_data_t * *    pp_oobd_own);

/**@brief Encodes @ref sd_ble_gap_lesc_oob_data_get command response.
 *
 * @sa @ref ble_gap_lesc_oob_data_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[in] p_oobd_own          Pointer to OOB data.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_lesc_oob_data_get_rsp_enc(uint32_t                     return_code,
                                           ble_gap_lesc_oob_data_t    * p_oobd_own,
                                           uint8_t * const              p_buf,
                                           uint32_t * const             p_buf_len);

/**@brief Decodes @ref sd_ble_gap_addr_get command request.
 *
 * @sa @ref ble_gap_addr_get_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] pp_address     Pointer to pointer to address.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_addr_get_req_dec(uint8_t const * const    p_buf,
                                  uint16_t                 packet_len,
                                  ble_gap_addr_t * * const pp_address);

/**@brief Encodes @ref sd_ble_gap_addr_get command response.
 *
 * @sa @ref ble_gap_addr_get_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_address           Pointer to @ref ble_gap_addr_t address
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_addr_get_rsp_enc(uint32_t                     return_code,
                                  uint8_t * const              p_buf,
                                  uint32_t * const             p_buf_len,
                                  ble_gap_addr_t const * const p_address);

/** @brief Decodes @ref sd_ble_gap_addr_set command request.
 *
 * @sa @ref ble_gap_addr_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf             Pointer to beginning of command request packet.
 * @param[in]  packet_len        Length (in bytes) of request packet.
 * @param[out] pp_addr           Pointer to pointer to the address structure.

 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_addr_set_req_dec(uint8_t const * const    p_buf,
                                  uint32_t                 packet_len,
                                  ble_gap_addr_t * * const pp_addr);

/**@brief Encodes @ref sd_ble_gap_addr_set command response.
 *
 * @sa @ref ble_gap_addr_set_req_dec for request decoding.
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
uint32_t ble_gap_addr_set_rsp_enc(uint32_t         return_code,
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/** @brief Decodes @ref sd_ble_gap_privacy_set command request.
 *
 * @sa @ref ble_gap_privacy_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf             Pointer to beginning of command request packet.
 * @param[in]  packet_len        Length (in bytes) of request packet.
 * @param[out] pp_privacy_params Pointer to pointer to the privacy settings structure.

 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_privacy_set_req_dec(uint8_t const * const        p_buf,
                                     uint32_t                     packet_len,
                                     ble_gap_privacy_params_t * * const pp_privacy_params);

/**@brief Encodes @ref sd_ble_gap_privacy_set command response.
 *
 * @sa @ref ble_gap_privacy_set_req_dec for request decoding.
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
uint32_t ble_gap_privacy_set_rsp_enc(uint32_t         return_code,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);

/** @brief Decodes @ref sd_ble_gap_privacy_get command request.
 *
 * @sa @ref ble_gap_privacy_get_rsp_enc for response encoding.
 *
 * @param[in]  p_buf             Pointer to beginning of command request packet.
 * @param[in]  packet_len        Length (in bytes) of request packet.
 * @param[out] pp_privacy_params Pointer to pointer to the privacy settings structure.

 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_privacy_get_req_dec(uint8_t const * const              p_buf,
                                     uint16_t                           packet_len,
                                     ble_gap_privacy_params_t * * const pp_privacy_params);

/**@brief Encodes @ref sd_ble_gap_privacy_set command response.
 *
 * @sa @ref ble_gap_privacy_set_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[out] p_privacy_params   Pointer to privacy settings structure.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_privacy_get_rsp_enc(uint32_t                               return_code,
                                     uint8_t * const                        p_buf,
                                     uint32_t * const                       p_buf_len,
                                     ble_gap_privacy_params_t const * const p_privacy_params);

/** @brief Decodes @ref sd_ble_gap_whitelist_set command request.
 *
 * @sa @ref ble_gap_whitelist_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf             Pointer to beginning of command request packet.
 * @param[in]  packet_len        Length (in bytes) of request packet.
 * @param[out] ppp_wl_addrs      Pointer to a whitelist of peer addresses.
 * @param[out] p_len             Pointer to a length of the whitelist.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_whitelist_set_req_dec(uint8_t const * const      p_buf,
                                       uint32_t                   packet_len,
                                       ble_gap_addr_t * * * const ppp_wl_addrs,
                                       uint8_t * const            p_len);

/**@brief Encodes @ref sd_ble_gap_whitelist_set command response.
 *
 * @sa @ref ble_gap_whitelist_set_req_dec for request decoding.
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
uint32_t ble_gap_whitelist_set_rsp_enc(uint32_t         return_code,
                                       uint8_t * const  p_buf,
                                       uint32_t * const p_buf_len);

/** @brief Decodes @ref sd_ble_gap_device_identities_set command request.
 *
 * @sa @ref ble_gap_device_identities_set_rsp_enc for response encoding.
 *
 * @param[in]  p_buf             Pointer to beginning of command request packet.
 * @param[in]  packet_len        Length (in bytes) of request packet.
 * @param[out] ppp_id_keys       Pointer to an array of peer identity addresses and peer IRKs.
 * @param[out] ppp_local_irks    Pointer to an array of local IRKs.
 * @param[out] p_len             Pointer to a length of the device identity list.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_identities_set_req_dec(uint8_t const * const        p_buf,
                                               uint32_t                     packet_len,
                                               ble_gap_id_key_t * * * const ppp_id_keys,
                                               ble_gap_irk_t * * * const    ppp_local_irks,
                                               uint8_t * const              p_len);

/**@brief Encodes @ref sd_ble_gap_device_identities_set command response.
 *
 * @sa @ref ble_gap_device_identities_set_req_dec for request decoding.
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
uint32_t ble_gap_device_identities_set_rsp_enc(uint32_t         return_code,
                                               uint8_t * const  p_buf,
                                               uint32_t * const p_buf_len);
#if NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)
/** @brief Decodes @ref sd_bble_gap_data_length_update command request.
 *
 * @sa @ref ble_gap_data_length_update_rsp_enc for response encoding.
 *
 * @param[in]  p_buf             Pointer to beginning of command request packet.
 * @param[in]  packet_len        Length (in bytes) of request packet.
 * @param[out] p_conn_handle     Pointer to a connection handle.
 * @param[out] pp_dl_params      Pointer to pointer to a data length params structure.
 * @param[out] pp_dl_limitation  Pointer to pointer to a data length limitation structure.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_data_length_update_req_dec(uint8_t const * const                      p_buf,
                                            uint16_t                                   packet_len,
                                            uint16_t *                                 p_conn_handle,
                                            ble_gap_data_length_params_t * * const     pp_dl_params,
                                            ble_gap_data_length_limitation_t * * const pp_dl_limitation);

/**@brief Encodes @ref sd_ble_gap_data_length_update command response.
 *
 * @sa @ref ble_gap_data_length_update_req_dec for request decoding.
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
uint32_t ble_gap_data_length_update_rsp_enc(uint32_t                                      return_code,
                                            uint8_t * const                                p_buf,
                                            uint32_t * const                               p_buf_len,
                                            ble_gap_data_length_limitation_t const * const p_dl_limitation);
#endif
#if NRF_SD_BLE_API_VERSION >= 5
/**@brief Decodes @ref sd_ble_gap_phy_update command request.
 *
 * @sa @ref ble_gap_phy_update_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle
 * @param[out] pp_gap_phys     Pointer to pointer to the struct.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_phy_update_req_dec(uint8_t const * const    p_buf,
                                     uint32_t                 packet_len,
                                     uint16_t * const         p_conn_handle,
                                     ble_gap_phys_t * * const pp_gap_phys);

/**@brief Encodes @ref sd_ble_gap_phy_update command response.
 *
 * @sa @ref ble_gap_phy_update_req_dec for request decoding.
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
uint32_t ble_gap_phy_update_rsp_enc(uint32_t         return_code,
                                     uint8_t * const  p_buf,
                                     uint32_t * const p_buf_len);
#endif

#if NRF_SD_BLE_API_VERSION >= 6
/**@brief Decodes @ref sd_ble_gap_adv_set_configure command request.
 *
 * @sa @ref ble_gap_adv_set_configure_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_conn_handle   Pointer to connection handle
 * @param[out] pp_adv_handle   Pointer to pointer to the struct.
 * @param[out] pp_adv_data     Pointer to pointer to the struct.
 * @param[out] pp_adv_params   Pointer to pointer to the struct.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_adv_set_configure_req_dec(uint8_t const * const        p_buf,
                                           uint16_t                     packet_len,
                                           uint8_t * * const            pp_adv_handle,
                                           ble_gap_adv_data_t **const   pp_adv_data,
                                           ble_gap_adv_params_t **const pp_adv_params);


/**@brief Encodes @ref sd_ble_gap_adv_set_configure command response.
 *
 * @sa @ref ble_gap_adv_set_configure_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 * @param[in] p_adv_handle        Pointer to the field to be encoded.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_adv_set_configure_rsp_enc(uint32_t               return_code,
                                           uint8_t * const        p_buf,
                                           uint32_t * const       p_buf_len,
                                           ble_gap_adv_data_t *   p_ble_adv_data,
                                           uint8_t const * const p_adv_handle);

#ifndef S112
/**@brief Decodes @ref sd_ble_gap_qos_channel_survey_start command request.
 *
 * @sa @ref ble_gap_qos_channel_survey_start_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 * @param[out] p_interval_us   Pointer to interval.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_qos_channel_survey_start_req_dec(uint8_t const * const          p_buf,
                                                  uint32_t                       packet_len,
                                                  uint32_t * const               p_interval_us);

/**@brief Encodes @ref sd_ble_gap_qos_channel_survey_start command response.
 *
 * @sa @ref ble_gap_qos_channel_survey_start_req_dec for request decoding.
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
uint32_t ble_gap_qos_channel_survey_start_rsp_enc(uint32_t         return_code,
                                                  uint8_t * const  p_buf,
                                                  uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_gap_qos_channel_survey_stop command request.
 *
 * @sa @ref ble_gap_qos_channel_survey_stop_rsp_enc for response encoding.
 *
 * @param[in] p_buf            Pointer to beginning of command request packet.
 * @param[in] packet_len       Length (in bytes) of response packet.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_gap_qos_channel_survey_stop_req_dec(uint8_t const * const          p_buf,
                                                 uint32_t                       packet_len);

/**@brief Encodes @ref sd_ble_gap_qos_channel_survey_stop command response.
 *
 * @sa @ref ble_gap_qos_channel_survey_stop_req_dec for request decoding.
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
uint32_t ble_gap_qos_channel_survey_stop_rsp_enc(uint32_t         return_code,
                                                 uint8_t * const  p_buf,
                                                 uint32_t * const p_buf_len);
#endif //!defined(S112)
#endif
/** @} */
#ifdef __cplusplus
}
#endif

#endif
