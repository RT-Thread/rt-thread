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
#include "ble_gatts_conn.h"
#include "conn_mw_ble_gatts.h"
#include "ble_serialization.h"

uint32_t conn_mw_ble_gatts_service_add(uint8_t const * const p_rx_buf,
                                       uint32_t              rx_buf_len,
                                       uint8_t * const       p_tx_buf,
                                       uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t      type;
    ble_uuid_t   uuid   = {0};
    ble_uuid_t * p_uuid = &uuid;
    uint16_t     handle;
    uint16_t *   p_handle = &handle;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_service_add_req_dec(p_rx_buf, rx_buf_len, &type, &p_uuid, &p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_service_add(type, p_uuid, p_handle);

    err_code = ble_gatts_service_add_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_characteristic_add(uint8_t const * const p_rx_buf,
                                              uint32_t              rx_buf_len,
                                              uint8_t * const       p_tx_buf,
                                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t service_handle;

    //Preparing char_md
    ble_gatts_char_md_t char_md;

    uint8_t             char_user_desc[BLE_GATTS_VAR_ATTR_LEN_MAX];
    ble_gatts_char_pf_t char_pf;
    ble_gatts_attr_md_t user_desc_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_md_t sccd_md;

    char_md.char_user_desc_size = sizeof (char_user_desc);
    char_md.p_char_user_desc    = char_user_desc;
    char_md.p_char_pf           = &char_pf;
    char_md.p_user_desc_md      = &user_desc_md;
    char_md.p_cccd_md           = &cccd_md;
    char_md.p_sccd_md           = &sccd_md;

    ble_gatts_char_md_t * p_char_md = &char_md;

    //Preparing attr_char_value
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t             value[BLE_GATTS_VAR_ATTR_LEN_MAX];

    attr_char_value.p_uuid    = &uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof (value);
    attr_char_value.p_value   = value;

    ble_gatts_attr_t * p_attr_char_value = &attr_char_value;

    //Preparing handles
    ble_gatts_char_handles_t   handles;
    ble_gatts_char_handles_t * p_handles = &handles;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_characteristic_add_req_dec(p_rx_buf, rx_buf_len, &service_handle,
                                                    &p_char_md, &p_attr_char_value, &p_handles);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_characteristic_add(service_handle, p_char_md,
                                                  p_attr_char_value, p_handles);

    err_code = ble_gatts_characteristic_add_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len,
                                                    p_handles);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;

}

uint32_t conn_mw_ble_gatts_include_add(uint8_t const * const p_rx_buf,
                                       uint32_t              rx_buf_len,
                                       uint8_t * const       p_tx_buf,
                                       uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   service_handle;
    uint16_t   inc_srvc_handle;
    uint16_t   handle;
    uint16_t * p_handle = &handle;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_include_add_req_dec(p_rx_buf, rx_buf_len, &service_handle,
                                             &inc_srvc_handle, &p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_include_add(service_handle, inc_srvc_handle, p_handle);

    err_code = ble_gatts_include_add_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_descriptor_add(uint8_t const * const p_rx_buf,
                                          uint32_t              rx_buf_len,
                                          uint8_t * const       p_tx_buf,
                                          uint32_t * const      p_tx_buf_len)
{

    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t            char_handle;
    uint8_t             attr_value[BLE_GATTS_VAR_ATTR_LEN_MAX];
    ble_uuid_t          char_uuid;
    ble_gatts_attr_md_t metadata;
    ble_gatts_attr_t    attr;
    ble_gatts_attr_t *  p_attr = &attr;

    attr.p_uuid    = &char_uuid;
    attr.p_attr_md = &metadata;
    attr.p_value   = attr_value;
    attr.init_len  = sizeof (attr_value);

    uint16_t   handle;
    uint16_t * p_handle = &handle;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_descriptor_add_req_dec(p_rx_buf, rx_buf_len, &char_handle, &p_attr,
                                                &p_handle);

    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_descriptor_add(char_handle, p_attr, p_handle);

    err_code = ble_gatts_descriptor_add_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_value_set(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t          conn_handle;
    uint16_t          handle;
    uint8_t           attr_val_table[BLE_GATTS_VAR_ATTR_LEN_MAX];
    ble_gatts_value_t attr_val =
    {
        .len = sizeof (attr_val_table),
        .offset = 0,
        .p_value = attr_val_table
    };
    ble_gatts_value_t * p_attr_val = &attr_val;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_value_set_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &handle, &p_attr_val);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_value_set(conn_handle, handle, p_attr_val);

    err_code = ble_gatts_value_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_attr_val);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_value_get(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t   handle;
    uint8_t    val[BLE_GATTS_VAR_ATTR_LEN_MAX];
    ble_gatts_value_t attr_value;
    ble_gatts_value_t * p_attr_value = &attr_value;

    attr_value.p_value = val;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_value_get_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &handle, &p_attr_value);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    sd_err_code = sd_ble_gatts_value_get(conn_handle, handle, p_attr_value);

    err_code = ble_gatts_value_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_attr_value);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_hvx(uint8_t const * const p_rx_buf,
                               uint32_t              rx_buf_len,
                               uint8_t * const       p_tx_buf,
                               uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint8_t    data[BLE_GATTS_VAR_ATTR_LEN_MAX];
    uint8_t *  p_data = data;
    uint16_t   len    = sizeof data;
    uint16_t * p_len  = &len;

    ble_gatts_hvx_params_t   hvx_params;
    ble_gatts_hvx_params_t * p_hvx_params = &hvx_params;

    hvx_params.p_len  = p_len;
    hvx_params.p_data = p_data;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_hvx_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_hvx_params);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    sd_err_code = sd_ble_gatts_hvx(conn_handle, p_hvx_params);

    p_len    = (p_hvx_params) ? p_hvx_params->p_len : NULL;
    err_code = ble_gatts_hvx_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_service_changed(uint8_t const * const p_rx_buf,
                                           uint32_t              rx_buf_len,
                                           uint8_t * const       p_tx_buf,
                                           uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t conn_handle;
    uint16_t start_handle;
    uint16_t end_handle;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_service_changed_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &start_handle,
                                                 &end_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_service_changed(conn_handle, start_handle, end_handle);

    err_code = ble_gatts_service_changed_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_rw_authorize_reply(uint8_t const * const p_rx_buf,
                                              uint32_t              rx_buf_len,
                                              uint8_t * const       p_tx_buf,
                                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t conn_handle;

    uint8_t                                 data[BLE_GATTS_VAR_ATTR_LEN_MAX];
    ble_gatts_rw_authorize_reply_params_t   auth_params;
    ble_gatts_rw_authorize_reply_params_t * p_auth_params = &auth_params;

    auth_params.params.read.p_data = data;
    auth_params.params.read.len    = sizeof (data);

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_rw_authorize_reply_req_dec(p_rx_buf, rx_buf_len, &conn_handle,
                                                    &p_auth_params);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_rw_authorize_reply(conn_handle, p_auth_params);

    err_code = ble_gatts_rw_authorize_reply_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_sys_attr_set(uint8_t const * const p_rx_buf,
                                        uint32_t              rx_buf_len,
                                        uint8_t * const       p_tx_buf,
                                        uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t conn_handle;

    uint8_t sys_attr[BLE_GATTS_VAR_ATTR_LEN_MAX];

    uint8_t * p_sys_attr   = sys_attr;
    uint16_t  sys_attr_len = sizeof (sys_attr);

    uint32_t flags;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_sys_attr_set_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_sys_attr,
                                              &sys_attr_len, &flags);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_sys_attr_set(conn_handle, p_sys_attr, sys_attr_len, flags);

    err_code = ble_gatts_sys_attr_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_sys_attr_get(uint8_t const * const p_rx_buf,
                                        uint32_t              rx_buf_len,
                                        uint8_t * const       p_tx_buf,
                                        uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t conn_handle;

    uint8_t sys_attr[BLE_GATTS_VAR_ATTR_LEN_MAX];

    uint8_t *  p_sys_attr     = sys_attr;
    uint16_t   sys_attr_len   = sizeof (sys_attr);
    uint16_t * p_sys_attr_len = &sys_attr_len;

    uint32_t   flags;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_sys_attr_get_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_sys_attr,
                                              &p_sys_attr_len, &flags);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_sys_attr_get(conn_handle, p_sys_attr, p_sys_attr_len, flags);

    err_code = ble_gatts_sys_attr_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_sys_attr,
                                              p_sys_attr_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_attr_get(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   handle;

    ble_gatts_attr_md_t md;
    ble_gatts_attr_md_t * p_md = &md;
    ble_uuid_t uuid;
    ble_uuid_t * p_uuid = &uuid;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_attr_get_req_dec(p_rx_buf, rx_buf_len, &handle, &p_uuid, &p_md);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_attr_get(handle, p_uuid, p_md);

    err_code = ble_gatts_attr_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_uuid, p_md);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_initial_user_handle_get(uint8_t const * const p_rx_buf,
                                                   uint32_t              rx_buf_len,
                                                   uint8_t * const       p_tx_buf,
                                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   handle;
    uint16_t * p_handle = &handle;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_initial_user_handle_get_req_dec(p_rx_buf, rx_buf_len, &p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_initial_user_handle_get(p_handle);

    err_code = ble_gatts_initial_user_handle_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gatts_exchange_mtu_reply(uint8_t const * const p_rx_buf,
                                              uint32_t              rx_buf_len,
                                              uint8_t * const       p_tx_buf,
                                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t * p_conn_handle = &conn_handle;
    uint16_t   server_rx_mtu;
    uint16_t * p_server_rx_mtu = &server_rx_mtu;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gatts_exchange_mtu_reply_req_dec(p_rx_buf, rx_buf_len, p_conn_handle, p_server_rx_mtu);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gatts_exchange_mtu_reply(conn_handle, server_rx_mtu);

    err_code = ble_gatts_exchange_mtu_reply_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
