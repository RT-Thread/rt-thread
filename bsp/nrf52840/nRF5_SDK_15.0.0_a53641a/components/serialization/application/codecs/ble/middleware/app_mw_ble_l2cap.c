/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include "ble_gap.h"
#include <stdint.h>
#include "ble_serialization.h"
#include "ser_sd_transport.h"
#include "ble_l2cap_app.h"
#include "app_error.h"

#if defined(NRF_SD_BLE_API_VERSION) && ((NRF_SD_BLE_API_VERSION < 4) || (NRF_SD_BLE_API_VERSION >=5))
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

#endif
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
/**@brief Command response callback function for @ref ble_l2cap_cid_register_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_cid_register_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_cid_register_rsp_dec(p_buffer,
                                       length,
                                       &result_code);

    APP_ERROR_CHECK(err_code);

    return result_code;
}

#ifndef _sd_ble_l2cap_cid_register
#define _sd_ble_l2cap_cid_register sd_ble_l2cap_cid_register
#endif
uint32_t _sd_ble_l2cap_cid_register(uint16_t cid)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    const uint32_t err_code = ble_l2cap_cid_register_req_enc(cid,
                                                             &(p_buffer[1]),
                                                             &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_cid_register_rsp_dec);
}

/**@brief Command response callback function for @ref ble_l2cap_cid_unregister_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_cid_unregister_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_cid_unregister_rsp_dec(p_buffer,
                                         length,
                                         &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_cid_unregister
#define _sd_ble_l2cap_cid_unregister sd_ble_l2cap_cid_unregister
#endif
uint32_t _sd_ble_l2cap_cid_unregister(uint16_t cid)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    const uint32_t err_code = ble_l2cap_cid_unregister_req_enc(cid,
                                                               &(p_buffer[1]),
                                                               &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_cid_unregister_rsp_dec);
}

/**@brief Command response callback function for @ref ble_l2cap_tx_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_tx_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_tx_rsp_dec(p_buffer,
                             length,
                             &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_tx
#define _sd_ble_l2cap_tx sd_ble_l2cap_tx
#endif
uint32_t _sd_ble_l2cap_tx(uint16_t                         conn_handle,
                         ble_l2cap_header_t const * const p_header,
                         uint8_t const * const            p_data)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    const uint32_t err_code = ble_l2cap_tx_req_enc(conn_handle, p_header, p_data,
                                                   &(p_buffer[1]),
                                                   &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_tx_rsp_dec);
}

#endif

#if NRF_SD_BLE_API_VERSION >= 5
static void * mp_out_params[1];
/**@brief Command response callback function for @ref ble_l2cap_ch_setup_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_ch_setup_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_ch_setup_rsp_dec(p_buffer,
                             length,
                             (uint16_t *)mp_out_params[0],
                             &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_ch_setup
#define _sd_ble_l2cap_ch_setup sd_ble_l2cap_ch_setup
#endif
uint32_t _sd_ble_l2cap_ch_setup(uint16_t                          conn_handle,
                                uint16_t *                        p_local_cid,
                                ble_l2cap_ch_setup_params_t const *p_params)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    mp_out_params[0] = p_local_cid;
    const uint32_t err_code = ble_l2cap_ch_setup_req_enc(conn_handle, p_local_cid, p_params,
                                                   &(p_buffer[1]),
                                                   &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_ch_setup_rsp_dec);
}

/**@brief Command response callback function for @ref ble_l2cap_ch_release_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_ch_release_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_ch_release_rsp_dec(p_buffer,
                             length,
                             &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_ch_release
#define _sd_ble_l2cap_ch_release sd_ble_l2cap_ch_release
#endif
uint32_t _sd_ble_l2cap_ch_release(uint16_t conn_handle,
                                  uint16_t local_cid)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    const uint32_t err_code = ble_l2cap_ch_release_req_enc(conn_handle, local_cid,
                                                   &(p_buffer[1]),
                                                   &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_ch_release_rsp_dec);
}


/**@brief Command response callback function for @ref ble_l2cap_ch_rx_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_ch_rx_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_ch_rx_rsp_dec(p_buffer,
                             length,
                             &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_ch_rx
#define _sd_ble_l2cap_ch_rx sd_ble_l2cap_ch_rx
#endif
uint32_t _sd_ble_l2cap_ch_rx(uint16_t conn_handle, uint16_t local_cid, ble_data_t const *p_sdu_buf)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    const uint32_t err_code = ble_l2cap_ch_rx_req_enc(conn_handle, local_cid, p_sdu_buf,
                                                   &(p_buffer[1]),
                                                   &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_ch_rx_rsp_dec);
}


/**@brief Command response callback function for @ref ble_l2cap_ch_tx_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_ch_tx_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_ch_tx_rsp_dec(p_buffer,
                             length,
                             &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_ch_tx
#define _sd_ble_l2cap_ch_tx sd_ble_l2cap_ch_tx
#endif
uint32_t _sd_ble_l2cap_ch_tx(uint16_t conn_handle, uint16_t local_cid, ble_data_t const *p_sdu_buf)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    const uint32_t err_code = ble_l2cap_ch_tx_req_enc(conn_handle, local_cid, p_sdu_buf,
                                                   &(p_buffer[1]),
                                                   &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_ch_tx_rsp_dec);
}

/**@brief Command response callback function for @ref ble_l2cap_ch_flow_control_req_enc BLE command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t l2cap_ch_flow_control_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =
        ble_l2cap_ch_flow_control_rsp_dec(p_buffer,
                             length,
                             (uint16_t *)mp_out_params[0],
                             &result_code);

    APP_ERROR_CHECK(err_code);



    return result_code;
}

#ifndef _sd_ble_l2cap_ch_flow_control
#define _sd_ble_l2cap_ch_flow_control sd_ble_l2cap_ch_flow_control
#endif
uint32_t _sd_ble_l2cap_ch_flow_control(uint16_t conn_handle,
                                       uint16_t local_cid,
                                       uint16_t credits,
                                       uint16_t *p_credits)
{

    uint8_t * p_buffer;
    uint32_t  buffer_length = 0;

    tx_buf_alloc(&p_buffer, (uint16_t *)&buffer_length);
    mp_out_params[0] = p_credits;
    const uint32_t err_code = ble_l2cap_ch_flow_control_req_enc(conn_handle, local_cid, credits, p_credits,
                                                   &(p_buffer[1]),
                                                   &buffer_length);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      l2cap_ch_flow_control_rsp_dec);
}
#endif
