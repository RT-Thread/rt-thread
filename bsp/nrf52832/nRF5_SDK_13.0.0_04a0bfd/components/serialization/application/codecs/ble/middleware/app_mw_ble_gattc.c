/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#include <stdint.h>
#include "ble_gattc.h"
#include "ble_gattc_app.h"
#include "ble_serialization.h"
#include "ser_sd_transport.h"
#include "app_error.h"

static void tx_buf_alloc(uint8_t * * p_data, uint16_t * p_len)
{
    uint32_t err_code;

    do
    {
        err_code = ser_sd_transport_tx_alloc(p_data, p_len);
    }
    while (err_code != NRF_SUCCESS);
    *p_data[0] = SER_PKT_TYPE_CMD;
    *p_len    -= 1;
}
/**@brief Command response callback function for @ref sd_ble_gattc_primary_services_discover BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_primary_services_discover_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_primary_services_discover_rsp_dec(p_buffer,
                                                                          length,
                                                                          &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_primary_services_discover
#define _sd_ble_gattc_primary_services_discover sd_ble_gattc_primary_services_discover
#endif
uint32_t _sd_ble_gattc_primary_services_discover(uint16_t                 conn_handle,
                                                uint16_t                 start_handle,
                                                ble_uuid_t const * const p_srvc_uuid)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_primary_services_discover_req_enc(conn_handle,
                                                                          start_handle,
                                                                          p_srvc_uuid,
                                                                          &(p_buffer[1]),
                                                                          &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_primary_services_discover_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_relationships_discover BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_relationships_discover_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_relationships_discover_rsp_dec(p_buffer,
                                                                       length,
                                                                       &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_relationships_discover
#define _sd_ble_gattc_relationships_discover sd_ble_gattc_relationships_discover
#endif
uint32_t _sd_ble_gattc_relationships_discover(uint16_t                               conn_handle,
                                             ble_gattc_handle_range_t const * const p_handle_range)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_relationships_discover_req_enc(conn_handle,
                                                                       p_handle_range,
                                                                       &(p_buffer[1]),
                                                                       &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_relationships_discover_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_characteristics_discover BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_characteristics_discover_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_characteristics_discover_rsp_dec(p_buffer,
                                                                         length,
                                                                         &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_characteristics_discover
#define _sd_ble_gattc_characteristics_discover sd_ble_gattc_characteristics_discover
#endif
uint32_t _sd_ble_gattc_characteristics_discover(
    uint16_t conn_handle,
    ble_gattc_handle_range_t const * const
    p_handle_range)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_characteristics_discover_req_enc(conn_handle,
                                                                         p_handle_range,
                                                                         &(p_buffer[1]),
                                                                         &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_characteristics_discover_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_descriptors_discover BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_descriptors_discover_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_descriptors_discover_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_descriptors_discover
#define _sd_ble_gattc_descriptors_discover sd_ble_gattc_descriptors_discover
#endif
uint32_t _sd_ble_gattc_descriptors_discover(uint16_t                               conn_handle,
                                           ble_gattc_handle_range_t const * const p_handle_range)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_descriptors_discover_req_enc(conn_handle,
                                                                     p_handle_range,
                                                                     &(p_buffer[1]),
                                                                     &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_descriptors_discover_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_char_value_by_uuid_read BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_char_value_by_uuid_read_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_char_value_by_uuid_read_rsp_dec(p_buffer,
                                                                        length,
                                                                        &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_char_value_by_uuid_read
#define _sd_ble_gattc_char_value_by_uuid_read sd_ble_gattc_char_value_by_uuid_read
#endif
uint32_t _sd_ble_gattc_char_value_by_uuid_read(uint16_t                               conn_handle,
                                              ble_uuid_t const * const               p_uuid,
                                              ble_gattc_handle_range_t const * const p_handle_range)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_char_value_by_uuid_read_req_enc(conn_handle,
                                                                        p_uuid,
                                                                        p_handle_range,
                                                                        &(p_buffer[1]),
                                                                        &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_char_value_by_uuid_read_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_read BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_read_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_read_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_read
#define _sd_ble_gattc_read sd_ble_gattc_read
#endif
uint32_t _sd_ble_gattc_read(uint16_t conn_handle,
                           uint16_t handle,
                           uint16_t offset)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_read_req_enc(conn_handle,
                                                     handle,
                                                     offset,
                                                     &(p_buffer[1]),
                                                     &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_read_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_char_values_read BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_char_values_read_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_char_values_read_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_char_values_read
#define _sd_ble_gattc_char_values_read sd_ble_gattc_char_values_read
#endif
uint32_t _sd_ble_gattc_char_values_read(uint16_t               conn_handle,
                                       uint16_t const * const p_handles,
                                       uint16_t               handle_count)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_char_values_read_req_enc(conn_handle,
                                                                 p_handles,
                                                                 handle_count,
                                                                 &(p_buffer[1]),
                                                                 &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_char_values_read_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_write BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_write_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_write_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_write
#define _sd_ble_gattc_write sd_ble_gattc_write
#endif
uint32_t _sd_ble_gattc_write(uint16_t                               conn_handle,
                            ble_gattc_write_params_t const * const p_write_params)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_write_req_enc(conn_handle,
                                                      p_write_params,
                                                      &(p_buffer[1]),
                                                      &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_write_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_hv_confirm BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_hv_confirm_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_hv_confirm_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_gattc_hv_confirm
#define _sd_ble_gattc_hv_confirm sd_ble_gattc_hv_confirm
#endif
uint32_t _sd_ble_gattc_hv_confirm(uint16_t conn_handle,
                                 uint16_t handle)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_hv_confirm_req_enc(conn_handle,
                                                           handle,
                                                           &(p_buffer[1]),
                                                           &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_hv_confirm_rsp_dec);
}


/**@brief Command response callback function for @ref sd_ble_gattc_info_discover BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_attr_info_discover_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_attr_info_discover_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);

    return result_code;
}

#ifndef _sd_ble_gattc_attr_info_discover
#define _sd_ble_gattc_attr_info_discover sd_ble_gattc_attr_info_discover
#endif
uint32_t _sd_ble_gattc_attr_info_discover(uint16_t                               conn_handle,
                                        ble_gattc_handle_range_t const * const p_handle_range)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_attr_info_discover_req_enc(conn_handle,
                                                                   p_handle_range,
                                                                   &(p_buffer[1]),
                                                                   &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_attr_info_discover_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ble_gattc_write BLE command.
 *
 * Callback for decoding the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t gattc_exchange_mtu_request_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_gattc_exchange_mtu_request_rsp_dec(p_buffer, length, &result_code);

    APP_ERROR_CHECK(err_code);
    return result_code;
}

#ifndef _sd_ble_gattc_exchange_mtu_request
#define _sd_ble_gattc_exchange_mtu_request sd_ble_gattc_exchange_mtu_request
#endif
uint32_t _sd_ble_gattc_exchange_mtu_request(uint16_t conn_handle,
                                           uint16_t client_rx_mtu)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);

    const uint32_t err_code = ble_gattc_exchange_mtu_request_req_enc(conn_handle,
                                                                     client_rx_mtu,
                                                                     &(p_buffer[1]),
                                                                     &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      gattc_exchange_mtu_request_rsp_dec);
}
