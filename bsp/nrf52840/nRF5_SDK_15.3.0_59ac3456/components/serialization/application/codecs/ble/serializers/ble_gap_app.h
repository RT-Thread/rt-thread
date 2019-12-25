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
#ifndef BLE_GAP_APP_H__
#define BLE_GAP_APP_H__

/**@file
 *
 * @defgroup ble_gap_app GAP Application command request encoders and command response decoders
 * @{
 * @ingroup  ser_app_s130_codecs
 *
 * @brief    GAP Application command request encoders and command response decoders.
 */
#include "ble.h"
#include "ble_gap.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NRF_SD_BLE_API_VERSION) && (NRF_SD_BLE_API_VERSION <= 5)
/**
 * @brief Encodes @ref sd_ble_gap_adv_data_set command request.
 *
 * @sa @ref ble_gap_adv_data_set_rsp_dec for command response decoder.
 *
 * @param[in] p_data         Raw data to be placed in advertisement packet. If NULL, no changes
 *                           are made to the current advertisement packet data.
 * @param[in] dlen           Data length for p_data. Max size: @ref BLE_GAP_ADV_SR_MAX_LEN_DEFAULT octets.
 *                           Should be 0 if p_data is NULL, can be 0 if p_data is not NULL.
 * @param[in] p_sr_data      Raw data to be placed in scan response packet. If NULL,
 *                           no changes are made to the current scan response packet data.
 * @param[in] srdlen         Data length for p_sr_data. Max size: @ref BLE_GAP_ADV_SR_MAX_LEN_DEFAULT octets.
 *                           Should be 0 if p_sr_data is NULL, can be 0 if p_data is not NULL.
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_adv_data_set_req_enc(uint8_t const * const p_data,
                                      uint8_t               dlen,
                                      uint8_t const * const p_sr_data,
                                      uint8_t               srdlen,
                                      uint8_t * const       p_buf,
                                      uint32_t * const      p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_adv_data_set command.
 *
 * @sa @ref ble_gap_adv_data_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf          Pointer to beginning of command response packet.
 * @param[in]  packet_len     Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_adv_data_set_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code);
#endif

/**
 * @brief Encodes @ref sd_ble_gap_adv_start command request.
 *
 * @sa @ref ble_gap_adv_start_rsp_dec for command response decoder.
 *
 * @param[in] p_adv_params   Pointer to advertising parameters structure.
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_adv_start_req_enc(
#if NRF_SD_BLE_API_VERSION > 5
                                   uint8_t adv_handle,
#else
                                   ble_gap_adv_params_t const * const p_adv_params,
#endif
#if NRF_SD_BLE_API_VERSION >= 4
                                   uint8_t                            conn_cfg_tag,
#endif
                                   uint8_t * const                    p_buf,
                                   uint32_t * const                   p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_adv_start command.
 *
 * @sa @ref ble_gap_adv_start_req_enc for command request encoder.
 *
 * @param[in]  p_buf          Pointer to beginning of command response packet.
 * @param[in]  packet_len     Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_adv_start_rsp_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_tx_power_set command request.
 *
 * @sa @ref ble_gap_tx_power_set_rsp_dec for command response decoder.
 *
 * @param[in]     tx_power   Radio transmit power in dBm (accepted values are -40, -30, -20, -16, -12, -8, -4, 0, and 4 dBm).
 * @param[in]     p_buf      Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_tx_power_set_req_enc(
#if NRF_SD_BLE_API_VERSION > 5
                                      uint8_t role, uint16_t handle,
#endif
                                      int8_t           tx_power,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_tx_power_set command.
 *
 * @sa @ref ble_gap_tx_power_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf         Pointer to beginning of command response packet.
 * @param[in]  packet_len    Length (in bytes) of response packet.
 * @param[out] p_result_code Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_tx_power_set_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_appearance_get command request.
 *
 * @sa @ref ble_gap_appearance_get_rsp_dec for command response decoder.
 *
 * @param[in] p_appearance   Appearance (16 bit), see @ref BLE_APPEARANCES.
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @note  \p p_appearance will not be updated by the command
 *        request encoder. Updated values are set by @ref ble_gap_appearance_get_rsp_dec.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_appearance_get_req_enc(uint16_t const * const p_appearance,
                                        uint8_t * const        p_buf,
                                        uint32_t * const       p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_appearance_get command.
 *
 * @sa @ref ble_gap_appearance_get_req_enc for command request encoder.
 *
 * @param[in] p_buf           Pointer to beginning of command response packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_appearance   Appearance (16 bit), see @ref BLE_APPEARANCES.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_appearance_get_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint16_t * const      p_appearance,
                                        uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_appearance_set command request.
 *
 * @sa @ref ble_gap_appearance_set_rsp_dec for command response decoder.
 *
 * @param[in] appearance     Appearance (16 bit), see @ref BLE_APPEARANCES.
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_appearance_set_req_enc(uint16_t         appearance,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_appearance_set command.
 *
 * @sa @ref ble_gap_appearance_set_req_enc for command request encoder.
 *
 * @param[in] p_buf           Pointer to beginning of command response packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_appearance_set_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_device_name_get command request.
 *
 * @sa @ref ble_gap_device_name_get_rsp_dec for command response decoder.
 *
 * @param[in] p_dev_name       Pointer to an empty buffer where the UTF-8 <b>non NULL-terminated</b>
 *                             string will be placed. Set to NULL to obtain the complete device
 *                             name length.
 * @param[in] p_dev_name_len   Length of the buffer pointed by p_dev_name.
 * @param[in] p_buf            Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len    \c in: Size of \p p_buf buffer.
 *                             \c out: Length of encoded command packet.
 *
 * @note  \p p_dev_name and \p  p_len will not be updated by the command
 *        request encoder. Updated values are set by @ref ble_gap_device_name_get_rsp_dec.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_name_get_req_enc(uint8_t const * const  p_dev_name,
                                         uint16_t const * const p_dev_name_len,
                                         uint8_t * const        p_buf,
                                         uint32_t * const       p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_device_name_get command.
 *
 * @sa @ref ble_gap_device_name_get_req_enc for command request encoder.
 *
 * @param[in] p_buf               Pointer to beginning of command response packet.
 * @param[in] packet_len          Length (in bytes) of response packet.
 * @param[out] p_dev_name         Pointer to an empty buffer where the UTF-8
 *                                <b>non NULL-terminated</b> string will be placed.
 * @param[in,out] p_dev_name_len  Length of the buffer pointed by p_dev_name, complete device name
 *                                length on output.
 * @param[out] p_result_code      Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_device_name_get_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint8_t * const       p_dev_name,
                                         uint16_t * const      p_dev_name_len,
                                         uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_device_name_set command request.
 *
 * @sa @ref ble_gap_device_name_set_rsp_dec for command response decoder.
 *
 * @param[in] p_write_perm   Write permissions for the Device Name characteristic, see
 *                           @ref ble_gap_conn_sec_mode_t.
 * @param[in] p_dev_name     Pointer to a UTF-8 encoded, <b>non NULL-terminated</b> string.
 * @param[in] len            Length of the UTF-8, <b>non NULL-terminated</b> string pointed
 *                           to by p_dev_name in octets (must be smaller or equal
 *                           than @ref BLE_GAP_DEVNAME_MAX_LEN).
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_name_set_req_enc(ble_gap_conn_sec_mode_t const * const p_write_perm,
                                         uint8_t const * const                 p_dev_name,
                                         uint16_t                              len,
                                         uint8_t * const                       p_buf,
                                         uint32_t * const                      p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_device_name_set command.
 *
 * @sa @ref ble_gap_device_name_set_req_enc for command request encoder.
 *
 * @param[in] p_buf              Pointer to beginning of command response packet.
 * @param[in] packet_len         Length (in bytes) of response packet.
 * @param[out] p_result_code     Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_device_name_set_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_ppcp_set command request.
 *
 * @sa @ref ble_gap_ppcp_set_rsp_dec for command response decoder.
 *
 * @param[in] p_conn_params  Pointer to a @ref ble_gap_conn_params_t structure with the
 *                           desired parameters.
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_ppcp_set_req_enc(ble_gap_conn_params_t const * const p_conn_params,
                                  uint8_t * const                     p_buf,
                                  uint32_t * const                    p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_ppcp_set command.
 *
 * @sa @ref ble_gap_ppcp_set_req_enc for command request encoder.
 *
 * @param[in] p_buf              Pointer to beginning of command response packet.
 * @param[in] packet_len         Length (in bytes) of response packet.
 * @param[out] p_result_code     Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_ppcp_set_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_conn_param_update command request.
 *
 * @sa @ref ble_gap_conn_param_update_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle     Connection handle of the connection.
 * @param[in]      p_conn_params   Pointer to desired connection parameters.
 * @param[in]      p_buf           Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                 \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_conn_param_update_req_enc(uint16_t                            conn_handle,
                                           ble_gap_conn_params_t const * const p_conn_params,
                                           uint8_t * const                     p_buf,
                                           uint32_t * const                    p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_conn_param_update command.
 *
 * @sa @ref ble_gap_conn_param_update_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_conn_param_update_rsp_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_disconnect command request.
 *
 * @sa @ref ble_gap_disconnect_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle       Connection handle of the connection.
 * @param[in]      hci_status_code   HCI status code, see @ref BLE_HCI_STATUS_CODES.
 * @param[in]      p_buf             Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len         \c in: size of \p p_buf buffer.
 *                                   \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_disconnect_req_enc(uint16_t         conn_handle,
                                    uint8_t          hci_status_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_disconnect command.
 *
 * @sa @ref ble_gap_disconnect_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_disconnect_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);


/**@brief Encodes @ref sd_ble_gap_rssi_stop command request.
 *
 * @sa @ref ble_gap_rssi_stop_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle       Connection handle of the connection.
 * @param[in]      p_buf             Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len         \c in: size of \p p_buf buffer.
 *                                   \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_rssi_stop_req_enc(uint16_t         conn_handle,
                                   uint8_t * const  p_buf,
                                   uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_rssi_stop command.
 *
 * @sa @ref ble_gap_rssi_stop_rsp_dec for command response decoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_rssi_stop_rsp_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint32_t * const      p_result_code);




/**@brief Encodes @ref sd_ble_gap_ppcp_get command request.
 *
 * @sa @ref ble_gap_ppcp_get_rsp_dec for command response decoder.
 *
 * @param[in]      p_conn_params  Pointer to a @ref ble_gap_conn_params_t structure where the
 *                                parameters will be stored.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @note  \p p_conn_params will not be updated by the command request encoder. Updated values are
 *        set by @ref ble_gap_ppcp_get_rsp_dec.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_ppcp_get_req_enc(ble_gap_conn_params_t const * const p_conn_params,
                                  uint8_t * const                     p_buf,
                                  uint32_t * const                    p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_ppcp_get command.
 *
 * @sa @ref ble_gap_ppcp_get_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_conn_params   Pointer to a @ref ble_gap_conn_params_t structure where the parameters
 *                             will be stored.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_ppcp_get_rsp_dec(uint8_t const * const         p_buf,
                                  uint32_t                      packet_len,
                                  ble_gap_conn_params_t * const p_conn_params,
                                  uint32_t * const              p_result_code);

/**@brief Encodes @ref sd_ble_gap_auth_key_reply command request.
 *
 * @sa @ref ble_gap_auth_key_reply_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle of the connection.
 * @param[in]      key_type       Key type which defines length of key data as defined for
 *                                @ref sd_ble_gap_auth_key_reply .
 * @param[in]      p_key          Pointer to a buffer which contains key
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Encoding failure. Incorrect param provided (key_type).
 */
uint32_t ble_gap_auth_key_reply_req_enc(uint16_t              conn_handle,
                                        uint8_t               key_type,
                                        uint8_t const * const p_key,
                                        uint8_t * const       p_buf,
                                        uint32_t * const      p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_auth_key_reply command.
 *
 * @sa @ref ble_gap_auth_key_reply_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_auth_key_reply_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_sec_info_reply command request.
 *
 * @sa @ref ble_gap_sec_info_reply_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle of the connection.
 * @param[in]      p_enc_info     Pointer to a @ref ble_gap_enc_info_t encryption information
 *                                structure.
 * @param[in]      p_id_info      Pointer to a @ref ble_gap_irk_t id information
 *                                structure.
 * @param[in]      p_sign_info    Pointer to a @ref ble_gap_sign_info_t signing information
 *                                structure.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_sec_info_reply_req_enc(uint16_t                    conn_handle,
                                        ble_gap_enc_info_t  const * p_enc_info,
                                        ble_gap_irk_t       const * p_id_info,
                                        ble_gap_sign_info_t const * p_sign_info,
                                        uint8_t * const             p_buf,
                                        uint32_t * const            p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_sec_info_reply command.
 *
 * @sa @ref ble_gap_sec_info_reply_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_sec_info_reply_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_sec_params_reply command request.
 *
 * @sa @ref ble_gap_sec_params_reply_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle of the connection.
 * @param[in]      sec_status     Security status, see @ref BLE_GAP_SEC_STATUS.
 * @param[in]      p_sec_params   Pointer to @ref ble_gap_sec_params_t security parameters
 *                                structure.
 * @param[in]      p_sec_keyset   Pointer to @ref ble_gap_sec_keyset_t security keys
 *                                structure.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_sec_params_reply_req_enc(uint16_t                           conn_handle,
                                          uint8_t                            sec_status,
                                          ble_gap_sec_params_t const * const p_sec_params,
                                          ble_gap_sec_keyset_t const * const p_sec_keyset,
                                          uint8_t * const                    p_buf,
                                          uint32_t * const                   p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_sec_params_reply command.
 *
 * @sa @ref ble_gap_sec_params_reply_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[in]  p_sec_keyset    Pointer to @ref ble_gap_sec_keyset_t security keys
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_sec_params_reply_rsp_dec(uint8_t const * const        p_buf,
                                          uint32_t                     packet_len,
                                          ble_gap_sec_keyset_t const * const p_sec_keyset,
                                          uint32_t * const             p_result_code);

/**@brief Encodes @ref sd_ble_gap_authenticate command request.
 *
 * @sa @ref ble_gap_authenticate_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle of the connection.
 * @param[in]      p_sec_params   Pointer to a @ref ble_gap_sec_params_t security parameters
 *                                structure.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_authenticate_req_enc(uint16_t                           conn_handle,
                                      ble_gap_sec_params_t const * const p_sec_params,
                                      uint8_t * const                    p_buf,
                                      uint32_t * const                   p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_authenticate command.
 *
 * @sa @ref ble_gap_authenticate_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_authenticate_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_adv_stop command request.
 *
 * @sa @ref ble_gap_adv_stop_rsp_dec for command response decoder.
 *
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_adv_stop_req_enc(
#if NRF_SD_BLE_API_VERSION > 5
                                  uint8_t adv_handle,
#endif
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_adv_stop command.
 *
 * @sa @ref ble_gap_adv_stop_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_adv_stop_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_conn_sec_get command request.
 *
 * @sa @ref ble_gap_conn_sec_get_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle       Connection handle of the connection.
 * @param[in]      p_conn_sec        Pointer to \ref ble_gap_conn_sec_t which will be filled in
 *                                   response.
 * @param[in]      p_buf             Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len         \c in: size of \p p_buf buffer.
 *                                   \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_conn_sec_get_req_enc(uint16_t                         conn_handle,
                                      ble_gap_conn_sec_t const * const p_conn_sec,
                                      uint8_t * const                  p_buf,
                                      uint32_t * const                 p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_conn_sec_get command.
 *
 * @sa @ref ble_gap_conn_sec_get_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] pp_conn_sec     Pointer to pointer to \ref ble_gap_conn_sec_t which will be filled by
 *                             the decoded data (if present).
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_conn_sec_get_rsp_dec(uint8_t const * const        p_buf,
                                      uint32_t                     packet_len,
                                      ble_gap_conn_sec_t * * const pp_conn_sec,
                                      uint32_t * const             p_result_code);

/**@brief Encodes @ref sd_ble_gap_rssi_start command request.
 *
 * @sa @ref ble_gap_rssi_start_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle       Connection handle of the connection.
 * @param[in]      threshold_dbm     Threshold in dBm.
 * @param[in]      skip_count        Sample skip count.
 * @param[in]      p_buf             Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len         \c in: size of \p p_buf buffer.
 *                                   \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_rssi_start_req_enc(uint16_t         conn_handle,
                                    uint8_t          threshold_dbm,
                                    uint8_t          skip_count,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_rssi_start command.
 *
 * @sa @ref ble_gap_rssi_start_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_rssi_start_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);
#ifndef S112
/**@brief Encodes @ref sd_ble_gap_scan_stop command request.
 *
 * @sa @ref ble_gap_scan_stop_rsp_dec for command response decoder.
 *
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_scan_stop_req_enc(uint8_t * const p_buf, uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_scan_stop command.
 *
 * @sa @ref ble_gap_scan_stop_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_scan_stop_rsp_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_scan_start command request.
 *
 * @sa @ref ble_gap_scan_start_rsp_dec for command response decoder.
 *
 * @param[in]      p_scan_params  Pointer to scan params structure.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_scan_start_req_enc(ble_gap_scan_params_t const *  p_scan_params,
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
                                    ble_data_t const *             p_adv_report_buffer,
#endif
                                    uint8_t * const                p_buf,
                                    uint32_t * const               p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_scan_start command.
 *
 * @sa @ref ble_gap_scan_start_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_scan_start_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_connect command request.
 *
 * @sa @ref ble_gap_connect_rsp_dec for command response decoder.
 *
 * @param[in]      p_peer_addr    Pointer to peer address.
 * @param[in]      p_scan_params  Pointer to scan params structure.
 * @param[in]      p_conn_params  Pointer to desired connection parameters.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_connect_req_enc(ble_gap_addr_t const * const        p_peer_addr,
                                 ble_gap_scan_params_t const * const p_scan_params,
                                 ble_gap_conn_params_t const * const p_conn_params,
#if NRF_SD_BLE_API_VERSION >= 4
                                 uint8_t                             conn_cfg_tag,
#endif
                                 uint8_t * const                     p_buf,
                                 uint32_t * const                    p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_connect command.
 *
 * @sa @ref ble_gap_connect_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_connect_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_connect_cancel command request.
 *
 * @sa @ref ble_gap_connect_cancel_rsp_dec for command response decoder.
 *
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_connect_cancel_req_enc(uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_connect_cancel command.
 *
 * @sa @ref ble_gap_connect_cancel_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_connect_cancel_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code);


/**@brief Encodes @ref sd_ble_gap_encrypt command request.
 *
 * @sa @ref ble_gap_encrypt_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle.
 * @param[in]      p_master_id    Pointer to a master identification structure.
 * @param[in]      p_enc_info     Pointer to desired connection parameters.
 * @param[in]      p_buf          Pointer to a ble_gap_enc_info_t encryption information structure.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */

uint32_t ble_gap_encrypt_req_enc(uint16_t                          conn_handle,
                                 ble_gap_master_id_t const * const p_master_id,
                                 ble_gap_enc_info_t const  * const p_enc_info,
                                 uint8_t                   * const p_buf,
                                 uint32_t                  * const p_buf_len);


/**@brief Decodes response to @ref sd_ble_gap_encrypt command.
 *
 * @sa @ref ble_gap_encrypt_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_encrypt_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t      * const p_result_code);
#endif //!S112

/**@brief Encodes @ref sd_ble_gap_rssi_get command request.
 *
 * @sa @ref ble_gap_rssi_get_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle.
 * @param[in]      p_rssi         Pointer to the RSSI value.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_rssi_get_req_enc(uint16_t             conn_handle,
                                  int8_t const * const p_rssi,
#if NRF_SD_BLE_API_VERSION > 5
                                  uint8_t const * const p_ch_index,
#endif
                                  uint8_t  * const     p_buf,
                                  uint32_t * const     p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_rssi_get command.
 *
 * @sa @ref ble_gap_rssi_get_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_rssi          Pointer to RSSI value.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_rssi_get_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  int8_t * const        p_rssi,
#if NRF_SD_BLE_API_VERSION > 5
                                  uint8_t * const        p_ch_index,
#endif
                                  uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_keypress_notify command request.
 *
 * @sa @ref ble_gap_keypress_notify_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle.
 * @param[in]      kp_not         See @ref sd_ble_gap_keypress_notify.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_keypress_notify_req_enc(uint16_t                           conn_handle,
                                          uint8_t                           kp_not,
                                          uint8_t * const                   p_buf,
                                          uint32_t * const                  p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_keypress_notify command.
 *
 * @sa @ref ble_gap_keypress_notify_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_keypress_notify_rsp_dec(uint8_t const * const              p_buf,
                                        uint32_t                           packet_len,
                                        uint32_t * const                   p_result_code);

/**@brief Encodes @ref sd_ble_gap_lesc_dhkey_reply command request.
 *
 * @sa @ref ble_gap_lesc_dhkey_reply_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle.
 * @param[in]      p_dhkey        See @ref sd_ble_gap_lesc_dhkey_reply.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_lesc_dhkey_reply_req_enc(uint16_t             conn_handle,
                                          ble_gap_lesc_dhkey_t const *p_dhkey,
                                          uint8_t * const      p_buf,
                                          uint32_t * const     p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_lesc_dhkey_reply command.
 *
 * @sa @ref ble_gap_lesc_dhkey_reply_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_lesc_dhkey_reply_rsp_dec(uint8_t const * const              p_buf,
                                        uint32_t                           packet_len,
                                        uint32_t * const                   p_result_code);

/**@brief Encodes @ref sd_ble_gap_lesc_oob_data_set command request.
 *
 * @sa @ref ble_gap_lesc_oob_data_set_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle.
 * @param[in]      p_oobd_own     See @ref sd_ble_gap_lesc_oob_data_set.
 * @param[in]      p_oobd_peer    See @ref sd_ble_gap_lesc_oob_data_set.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_lesc_oob_data_set_req_enc(uint16_t             conn_handle,
                                           ble_gap_lesc_oob_data_t const *p_oobd_own,
                                           ble_gap_lesc_oob_data_t const *p_oobd_peer,
                                           uint8_t * const      p_buf,
                                           uint32_t * const     p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_lesc_oob_data_set command.
 *
 * @sa @ref ble_gap_lesc_oob_data_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_lesc_oob_data_set_rsp_dec(uint8_t const * const              p_buf,
                                           uint32_t                           packet_len,
                                           uint32_t * const                   p_result_code);

/**@brief Encodes @ref sd_ble_gap_lesc_oob_data_get command request.
 *
 * @sa @ref ble_gap_lesc_oob_data_get_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle.
 * @param[in]      p_pk_own       See @ref sd_ble_gap_lesc_oob_data_get.
 * @param[in]      p_oobd_own     See @ref sd_ble_gap_lesc_oob_data_get.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_lesc_oob_data_get_req_enc(uint16_t                      conn_handle,
                                           ble_gap_lesc_p256_pk_t const *p_pk_own,
                                           ble_gap_lesc_oob_data_t      *p_oobd_own,
                                           uint8_t * const               p_buf,
                                           uint32_t * const              p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_lesc_oob_data_get command.
 *
 * @sa @ref ble_gap_lesc_oob_data_get_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] pp_oobd_own     Pointer to pointer to location where OOB data is decoded.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_lesc_oob_data_get_rsp_dec(uint8_t const * const       p_buf,
                                           uint32_t                    packet_len,
                                           ble_gap_lesc_oob_data_t  * *pp_oobd_own,
                                           uint32_t * const            p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_addr_get command request.
 *
 * @sa @ref ble_gap_addr_get_rsp_dec for command response decoder.
 *
 * @param[in] p_address      Pointer to address.
 * @param[in] p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len  \c in: Size of \p p_buf buffer.
 *                           \c out: Length of encoded command packet.
 *
 * @note  \p p_address  will not be updated by the command
 *        request encoder. Updated values are set by @ref ble_gap_addr_get_rsp_dec.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_addr_get_req_enc(ble_gap_addr_t const * const p_address,
                                  uint8_t * const              p_buf,
                                  uint32_t * const             p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_addr_get command.
 *
 * @sa @ref ble_gap_addr_get_req_enc for command request encoder.
 *
 * @param[in] p_buf           Pointer to beginning of command response packet.
 * @param[in] packet_len      Length (in bytes) of response packet.
 * @param[out] p_address      Pointer to address.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_addr_get_rsp_dec(uint8_t const * const  p_buf,
                                  uint32_t               packet_len,
                                  ble_gap_addr_t * const p_address,
                                  uint32_t * const       p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_addr_set command request.
 *
 * @sa @ref ble_gap_addr_set_rsp_dec for command response decoder.
 *
 * @param[in]     p_addr               Pointer to address structure.
 * @param[in,out] p_buf                Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len            \c in: size of \p p_buf buffer.
 *                                     \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_addr_set_req_enc(ble_gap_addr_t const * const p_addr,
                                  uint8_t * const              p_buf,
                                  uint32_t * const             p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_addr_set command.
 *
 * @sa @ref ble_gap_addr_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf          Pointer to beginning of command response packet.
 * @param[in]  packet_len     Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_addr_set_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_privacy_set command request.
 *
 * @sa @ref ble_gap_privacy_set_rsp_dec for command response decoder.
 *
 * @param[in]     p_privacy_params     Pointer to privacy settings structure.
 * @param[in,out] p_buf                Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len            \c in: size of \p p_buf buffer.
 *                                     \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_privacy_set_req_enc(ble_gap_privacy_params_t  const * p_privacy_params,
                                     uint8_t * const                   p_buf,
                                     uint32_t * const                  p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_privacy_set command.
 *
 * @sa @ref ble_gap_privacy_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf          Pointer to beginning of command response packet.
 * @param[in]  packet_len     Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_privacy_set_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_privacy_get command request.
 *
 * @sa @ref ble_gap_privacy_get_rsp_dec for command response decoder.
 *
 * @param[in]     p_privacy_params     Pointer to privacy settings structure.
 * @param[in,out] p_buf                Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len            \c in: size of \p p_buf buffer.
 *                                     \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_privacy_get_req_enc(ble_gap_privacy_params_t const * const p_privacy_params,
                                     uint8_t * const                        p_buf,
                                     uint32_t * const                       p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_privacy_get command.
 *
 * @sa @ref ble_gap_privacy_get_req_enc for command request encoder.
 *
 * @param[in]  p_buf            Pointer to beginning of command response packet.
 * @param[in]  packet_len       Length (in bytes) of response packet.
 * @param[out] p_privacy_params Pointer to privacy settings structure.
 * @param[out] p_result_code    Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_privacy_get_rsp_dec(uint8_t const * const                  p_buf,
                                     uint32_t                               packet_len,
                                     ble_gap_privacy_params_t const * const p_privacy_params,
                                     uint32_t * const                       p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_whitelist_set command request.
 *
 * @sa @ref ble_gap_whitelist_set_rsp_dec for command response decoder.
 *
 * @param[in]     pp_wl_addrs          Pointer to a whitelist of peer addresses.
 * @param[out]    len                Pointer to a length of the whitelist.
 * @param[in,out] p_buf                Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len            \c in: size of \p p_buf buffer.
 *                                     \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_whitelist_set_req_enc(ble_gap_addr_t const * const * const pp_wl_addrs,
                                       uint8_t const                        len,
                                       uint8_t * const                      p_buf,
                                       uint32_t * const                     p_buf_len);

/**
 * @brief Decodes response to @ref sd_ble_gap_whitelist_set command.
 *
 * @sa @ref ble_gap_whitelist_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf          Pointer to beginning of command response packet.
 * @param[in]  packet_len     Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_whitelist_set_rsp_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint32_t * const      p_result_code);

/**
 * @brief Encodes @ref sd_ble_gap_device_identities_set command request.
 *
 * @sa @ref ble_gap_device_identities_set_rsp_dec for command response decoder.
 *
 * @param[in]     pp_id_keys           Pointer to an array of peer identity addresses and peer IRKs.
 * @param[in]     pp_local_irks        Pointer to an array of local IRKs.
 * @param[out]    len                Pointer to a length of the device identity list.
 * @param[in,out] p_buf                Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len            \c in: size of \p p_buf buffer.
 *                                     \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_device_identities_set_req_enc(ble_gap_id_key_t const * const * const pp_id_keys,
                                               ble_gap_irk_t const * const * const    pp_local_irks,
                                               uint8_t const                          len,
                                               uint8_t * const                        p_buf,
                                               uint32_t * const                       p_buf_len);
/**
 * @brief Decodes response to @ref sd_ble_gap_device_identities_set command.
 *
 * @sa @ref ble_gap_device_identities_set_req_enc for command request encoder.
 *
 * @param[in]  p_buf          Pointer to beginning of command response packet.
 * @param[in]  packet_len     Length (in bytes) of response packet.
 * @param[out] p_result_code  Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_device_identities_set_rsp_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint32_t * const      p_result_code);

#if NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)
/**
 * @brief Encodes @ref sd_ble_gap_data_length_update command request.
 *
 * @sa @ref ble_gap_data_length_update_rsp_dec for command response decoder.
 *
 * @param[in]     conn_handle        Connection handle.
 * @param[in]     p_dl_params        Pointer to a data length params structure.
 * @param[out]    p_dl_limitation    Pointer to a data length limitation structure.
 * @param[in,out] p_buf              Pointer to buffer where encoded data command will be returned.
 * @param[in,out] p_buf_len          \c in: size of \p p_buf buffer.
 *                                   \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS               Encoding success.
 * @retval NRF_ERROR_NULL            Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_data_length_update_req_enc(uint16_t                             conn_handle,
                                            ble_gap_data_length_params_t const * p_dl_params,
                                            ble_gap_data_length_limitation_t *   p_dl_limitation,
                                            uint8_t * const                      p_buf,
                                            uint32_t * const                     p_buf_len);
/**
 * @brief Decodes response to @ref sd_ble_gap_data_length_update command.
 *
 * @sa @ref ble_gap_data_length_update_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_dl_limitation Pointer to a data length limitation structure.
 * @param[out] p_result_code   Command result code.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA    Decoding failure. Decoded operation code does not match
 *                                   expected operation code.
 */
uint32_t ble_gap_data_length_update_rsp_dec(uint8_t const * const              p_buf,
                                            uint32_t                           packet_len,
                                            ble_gap_data_length_limitation_t * p_dl_limitation,
                                            uint32_t * const                   p_result_code);
#endif

#if NRF_SD_BLE_API_VERSION >= 5
/**@brief Encodes @ref sd_ble_gap_phy_update command request.
 *
 * @sa @ref ble_gap_phy_update_rsp_dec for command response decoder.
 *
 * @param[in]      conn_handle    Connection handle of the connection.
 * @param[in]      p_gap_phys     Pointer to a @ref ble_gap_phys_t
 *                                structure.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_phy_update_req_enc(uint16_t               conn_handle,
                                     ble_gap_phys_t const * p_gap_phys,
                                     uint8_t * const        p_buf,
                                     uint32_t * const       p_buf_len);

/**@brief Decodes response to @ref sd_ble_gap_phy_update command.
 *
 * @sa @ref ble_gap_phy_update_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_phy_update_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code);
#endif

#if NRF_SD_BLE_API_VERSION >= 6
/**@brief Encodes @ref sd_ble_gap_adv_set_configure command request.
 *
 * @sa @ref ble_gap_adv_set_configure_rsp_dec for command response decoder.
 *
 * @param[in]      p_adv_handle   Advertising handle.
 * @param[in]      p_adv_data     Pointer to a @ref ble_gap_adv_data_t structure.
 * @param[in]      p_adv_params   Pointer to a @ref ble_gap_adv_params_t structure.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_adv_set_configure_req_enc(uint8_t *                   p_adv_handle,
                                           ble_gap_adv_data_t const *  p_adv_data,
                                           ble_gap_adv_params_t const *p_adv_params,
                                           uint8_t * const             p_buf,
                                           uint32_t * const            p_buf_len);


/**@brief Decodes response to @ref sd_ble_gap_adv_set_configure command.
 *
 * @sa @ref ble_gap_adv_set_configure_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_adv_handle    Advertising handle.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_adv_set_configure_rsp_dec(uint8_t const * const  p_buf,
                                           uint32_t               packet_len,
                                           uint8_t *              p_adv_handle,
                                           uint32_t * const       p_result_code);

/**@brief Encodes @ref sd_ble_gap_qos_channel_survey_start command request.
 *
 * @sa @ref ble_gap_qos_channel_survey_start_rsp_dec for command response decoder.
 *
 * @param[in]      interval_us    Interval.
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_qos_channel_survey_start_req_enc(uint32_t                interval_us,
                                                  uint8_t * const         p_buf,
                                                  uint32_t * const        p_buf_len);


/**@brief Decodes response to @ref sd_ble_gap_qos_channel_survey_start command.
 *
 * @sa @ref ble_gap_qos_channel_survey_start_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_qos_channel_survey_start_rsp_dec(uint8_t const * const p_buf,
                                                  uint32_t              packet_len,
                                                  uint32_t * const      p_result_code);

/**@brief Encodes @ref sd_ble_gap_qos_channel_survey_stop command request.
 *
 * @sa @ref ble_gap_qos_channel_survey_stop_rsp_dec for command response decoder.
 *
 * @param[in]      p_buf          Pointer to buffer where encoded data command will be returned.
 * @param[in, out] p_buf_len      \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_gap_qos_channel_survey_stop_req_enc(uint8_t * const         p_buf,
                                                 uint32_t * const        p_buf_len);


/**@brief Decodes response to @ref sd_ble_gap_qos_channel_survey_stop command.
 *
 * @sa @ref ble_gap_qos_channel_survey_stop_req_enc for command request encoder.
 *
 * @param[in]  p_buf           Pointer to beginning of command response packet.
 * @param[in]  packet_len      Length (in bytes) of response packet.
 * @param[out] p_result_code   Command response result code.
 *
 * @retval NRF_SUCCESS              Decoding success.
 * @retval NRF_ERROR_NULL           Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_DATA_SIZE      Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_DATA   Decoding failure. Decoded operation code does not match expected
 *                                  operation code.
 */
uint32_t ble_gap_qos_channel_survey_stop_rsp_dec(uint8_t const * const p_buf,
                                                 uint32_t              packet_len,
                                                 uint32_t * const      p_result_code);
#endif
/** @} */
#ifdef __cplusplus
}
#endif

#endif
