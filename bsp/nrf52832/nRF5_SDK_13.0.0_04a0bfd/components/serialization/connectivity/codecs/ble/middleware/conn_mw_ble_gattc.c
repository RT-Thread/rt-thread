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
#include "ble_gattc_conn.h"
#include "conn_mw_ble_gattc.h"
#include "ble_serialization.h"

#if  defined(BLE_GATT_MTU_SIZE_DEFAULT) && !defined(GATT_MTU_SIZE_DEFAULT)
#define GATT_MTU_SIZE_DEFAULT BLE_GATT_MTU_SIZE_DEFAULT
#endif

#if  defined(BLE_GATT_ATT_MTU_DEFAULT) && !defined(GATT_MTU_SIZE_DEFAULT)
#define GATT_MTU_SIZE_DEFAULT BLE_GATT_ATT_MTU_DEFAULT
#endif
/** Maximum length of p_value in \ref ble_gattc_write_params_t. See Bluetooth 4.0 spec: 3.4.5.1 and
 *  3.4.5.3. */
#define BLE_GATTC_WRITE_P_VALUE_LEN_MAX    (GATT_MTU_SIZE_DEFAULT - 3)

/** See Bluetooth 4.0 spec: 3.4.4.7. */
#define BLE_GATTC_HANDLE_COUNT_LEN_MAX     ((GATT_MTU_SIZE_DEFAULT - 1) / 2)

uint32_t conn_mw_ble_gattc_primary_services_discover(uint8_t const * const p_rx_buf,
                                                     uint32_t              rx_buf_len,
                                                     uint8_t * const       p_tx_buf,
                                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t     conn_handle;
    uint16_t     start_handle;
    ble_uuid_t   srvc_uuid;
    ble_uuid_t * p_srvc_uuid = &srvc_uuid;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_primary_services_discover_req_dec(p_rx_buf,
                                                           rx_buf_len,
                                                           &conn_handle,
                                                           &start_handle,
                                                           &p_srvc_uuid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_primary_services_discover(conn_handle, start_handle, p_srvc_uuid);

    err_code = ble_gattc_primary_services_discover_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_relationships_discover(uint8_t const * const p_rx_buf,
                                                  uint32_t              rx_buf_len,
                                                  uint8_t * const       p_tx_buf,
                                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t                   conn_handle;
    ble_gattc_handle_range_t   handle_range;
    ble_gattc_handle_range_t * p_handle_range = &handle_range;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_relationships_discover_req_dec(p_rx_buf, rx_buf_len,
                                                        &conn_handle, &p_handle_range);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_relationships_discover(conn_handle, p_handle_range);

    err_code = ble_gattc_relationships_discover_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_characteristics_discover(uint8_t const * const p_rx_buf,
                                                    uint32_t              rx_buf_len,
                                                    uint8_t * const       p_tx_buf,
                                                    uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t                   conn_handle;
    ble_gattc_handle_range_t   handle_range;
    ble_gattc_handle_range_t * p_handle_range = &handle_range;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_characteristics_discover_req_dec(p_rx_buf, rx_buf_len,
                                                          &conn_handle, &p_handle_range);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_characteristics_discover(conn_handle, p_handle_range);

    err_code = ble_gattc_characteristics_discover_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_descriptors_discover(uint8_t const * const p_rx_buf,
                                                uint32_t              rx_buf_len,
                                                uint8_t * const       p_tx_buf,
                                                uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t                   conn_handle;
    ble_gattc_handle_range_t   handle_range;
    ble_gattc_handle_range_t * p_handle_range = &handle_range;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_descriptors_discover_req_dec(p_rx_buf, rx_buf_len,
                                                      &conn_handle, &p_handle_range);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_descriptors_discover(conn_handle, p_handle_range);

    err_code = ble_gattc_descriptors_discover_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_char_value_by_uuid_read(uint8_t const * const p_rx_buf,
                                                   uint32_t              rx_buf_len,
                                                   uint8_t * const       p_tx_buf,
                                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t conn_handle;

    ble_uuid_t   uuid   = {0};
    ble_uuid_t * p_uuid = &uuid;

    ble_gattc_handle_range_t   handle_range;
    ble_gattc_handle_range_t * p_handle_range = &handle_range;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_char_value_by_uuid_read_req_dec(p_rx_buf, rx_buf_len,
                                                         &conn_handle, &p_uuid, &p_handle_range);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_char_value_by_uuid_read(conn_handle, p_uuid, p_handle_range);

    err_code = ble_gattc_char_value_by_uuid_read_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_read(uint8_t const * const p_rx_buf,
                                uint32_t              rx_buf_len,
                                uint8_t * const       p_tx_buf,
                                uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t * p_conn_handle = &conn_handle;

    uint16_t   handle;
    uint16_t * p_handle = &handle;

    uint16_t   offset;
    uint16_t * p_offset = &offset;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_read_req_dec(p_rx_buf, rx_buf_len, p_conn_handle, p_handle, p_offset);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_read(conn_handle, handle, offset);

    err_code = ble_gattc_read_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_char_values_read(uint8_t const * const p_rx_buf,
                                            uint32_t              rx_buf_len,
                                            uint8_t * const       p_tx_buf,
                                            uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t * p_conn_handle = &conn_handle;

    uint16_t   handles[BLE_GATTC_HANDLE_COUNT_LEN_MAX];
    uint16_t * p_handles = handles;

    uint16_t   handle_count   = BLE_GATTC_HANDLE_COUNT_LEN_MAX;
    uint16_t * p_handle_count = &handle_count;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_char_values_read_req_dec(p_rx_buf,
                                                  rx_buf_len,
                                                  p_conn_handle,
                                                  &p_handles,
                                                  p_handle_count);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_char_values_read(conn_handle, p_handles, handle_count);

    err_code = ble_gattc_char_values_read_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_write(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t * p_conn_handle = &conn_handle;

    uint8_t value[BLE_GATTC_WRITE_P_VALUE_LEN_MAX];

    ble_gattc_write_params_t   write_params   = {0};
    ble_gattc_write_params_t * p_write_params = &write_params;

    p_write_params->len     = BLE_GATTC_WRITE_P_VALUE_LEN_MAX;
    p_write_params->p_value = value;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_write_req_dec(p_rx_buf, rx_buf_len, p_conn_handle, &p_write_params);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_write(conn_handle, p_write_params);

    err_code = ble_gattc_write_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_hv_confirm(uint8_t const * const p_rx_buf,
                                      uint32_t              rx_buf_len,
                                      uint8_t * const       p_tx_buf,
                                      uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    uint16_t   conn_handle;
    uint16_t * p_conn_handle = &conn_handle;

    uint16_t   handle;
    uint16_t * p_handle = &handle;

    err_code = ble_gattc_hv_confirm_req_dec(p_rx_buf, rx_buf_len, p_conn_handle, p_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_hv_confirm(conn_handle, handle);

    err_code = ble_gattc_hv_confirm_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_attr_info_discover(uint8_t const * const p_rx_buf,
                                              uint32_t              rx_buf_len,
                                              uint8_t * const       p_tx_buf,
                                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t * p_conn_handle = &conn_handle;

    ble_gattc_handle_range_t   range   = {0};
    ble_gattc_handle_range_t * p_range = &range;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_attr_info_discover_req_dec(p_rx_buf, rx_buf_len, p_conn_handle, &p_range);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_attr_info_discover(conn_handle, p_range);

    err_code = ble_gattc_attr_info_discover_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_gattc_exchange_mtu_request(uint8_t const * const p_rx_buf,
                                                uint32_t              rx_buf_len,
                                                uint8_t * const       p_tx_buf,
                                                uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t   client_rx_mtu;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_gattc_exchange_mtu_request_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &client_rx_mtu);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_gattc_exchange_mtu_request(conn_handle, client_rx_mtu);

    err_code = ble_gattc_exchange_mtu_request_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
