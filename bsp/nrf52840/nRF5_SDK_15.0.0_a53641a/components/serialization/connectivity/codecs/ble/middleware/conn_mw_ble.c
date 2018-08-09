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
#include "ble_conn.h"
#include "conn_mw_ble.h"
#include "ble_serialization.h"
#include "conn_ble_user_mem.h"
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION >= 5
#include "nrf_sdh_ble.h"
#endif
#include <string.h>
extern sercon_ble_user_mem_t m_conn_user_mem_table[];

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t conn_mw_ble_tx_packet_count_get(uint8_t const * const p_rx_buf,
                                         uint32_t              rx_buf_len,
                                         uint8_t * const       p_tx_buf,
                                         uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t   count;
    uint16_t  conn_handle;
    uint8_t * p_count = &count;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_tx_packet_count_get_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_count);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_tx_packet_count_get(conn_handle, p_count);

    err_code = ble_tx_packet_count_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_count);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
#endif
uint32_t conn_mw_ble_uuid_vs_add(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    ble_uuid128_t   uuid;
    ble_uuid128_t * p_uuid = &uuid;
    uint8_t         uuid_type;
    uint8_t *       p_uuid_type = &uuid_type;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_uuid_vs_add_req_dec(p_rx_buf, rx_buf_len, &p_uuid, &p_uuid_type);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_uuid_vs_add(p_uuid, p_uuid_type);

    err_code = ble_uuid_vs_add_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_uuid_type);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    return err_code;
}

uint32_t conn_mw_ble_uuid_decode(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t      raw_uuid[16];
    uint8_t      uuid_len   = sizeof (raw_uuid);
    uint8_t *    p_raw_uuid = raw_uuid;
    ble_uuid_t   uuid;
    ble_uuid_t * p_uuid   = &uuid;
    uint32_t     err_code = NRF_SUCCESS;
    uint32_t     sd_err_code;

    err_code = ble_uuid_decode_req_dec(p_rx_buf, rx_buf_len, &uuid_len, &p_raw_uuid, &p_uuid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_uuid_decode(uuid_len, p_raw_uuid, p_uuid);

    err_code = ble_uuid_decode_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_uuid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_uuid_encode(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t      raw_uuid[16];
    uint8_t      uuid_len   = sizeof (raw_uuid);
    uint8_t *    p_uuid_len = &uuid_len;
    uint8_t *    p_raw_uuid = raw_uuid;
    ble_uuid_t   uuid;
    ble_uuid_t * p_uuid   = &uuid;
    uint32_t     err_code = NRF_SUCCESS;
    uint32_t     sd_err_code;

    memset(&uuid, 0, sizeof(uuid));
    err_code = ble_uuid_encode_req_dec(p_rx_buf, rx_buf_len, &p_uuid, &p_uuid_len, &p_raw_uuid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_uuid_encode(p_uuid, p_uuid_len, p_raw_uuid);

    err_code = ble_uuid_encode_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, uuid_len, p_raw_uuid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_version_get(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    ble_version_t   version;
    ble_version_t * p_version = &version;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_version_get_req_dec(p_rx_buf, rx_buf_len, &p_version);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_version_get(p_version);

    err_code = ble_version_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_version);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
uint32_t conn_mw_ble_opt_get(uint8_t const * const p_rx_buf,
                             uint32_t              rx_buf_len,
                             uint8_t * const       p_tx_buf,
                             uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t   opt_id;
    ble_opt_t  opt;
    ble_opt_t *p_opt = &opt;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_opt_get_req_dec(p_rx_buf, rx_buf_len, &opt_id, &p_opt);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    uint16_t act_latency;
    uint8_t passkey[BLE_GAP_PASSKEY_LEN];
    /* Initialaize appropriate pointers inside opt union based on opt_id */
   switch (opt_id)
   {
       case BLE_GAP_OPT_LOCAL_CONN_LATENCY:
           opt.gap_opt.local_conn_latency.p_actual_latency = &act_latency;
           break;
       case BLE_GAP_OPT_PASSKEY:
           opt.gap_opt.passkey.p_passkey = passkey;
           break;
   }
    sd_err_code = sd_ble_opt_get(opt_id, p_opt);

    err_code = ble_opt_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, opt_id, p_opt);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_opt_set(uint8_t const * const p_rx_buf,
                             uint32_t              rx_buf_len,
                             uint8_t * const       p_tx_buf,
                             uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t      opt_id = 0xFFFFFFFF;
    uint16_t      act_latency;
    uint8_t       passkey[BLE_GAP_PASSKEY_LEN];
    uint32_t      err_code = NRF_SUCCESS;

    /* Pre-decode type of ble_opt_t union */
    err_code = ble_opt_id_pre_dec(p_rx_buf, rx_buf_len, &opt_id);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    ble_opt_t  opt;
    ble_opt_t *p_opt = &opt;
    /* Initialaize appropriate pointers inside opt union based on opt_id */
    switch (opt_id)
    {
        case BLE_GAP_OPT_LOCAL_CONN_LATENCY:
            opt.gap_opt.local_conn_latency.p_actual_latency = &act_latency;
            break;
        case BLE_GAP_OPT_PASSKEY:
            opt.gap_opt.passkey.p_passkey = passkey;
            break;
    }

    uint32_t   sd_err_code;

    err_code = ble_opt_set_req_dec(p_rx_buf, rx_buf_len, &opt_id, &p_opt);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_opt_set(opt_id, p_opt);

    err_code = ble_opt_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}


uint32_t conn_mw_ble_enable(uint8_t const * const p_rx_buf,
                            uint32_t              rx_buf_len,
                            uint8_t * const       p_tx_buf,
                            uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t app_ram_base;

/*lint --e{10} --e{19} --e{27} --e{40} --e{529} -save suppress Error 27: Illegal character */
#if defined(_WIN32) ||  defined(__unix) || defined(__APPLE__)
    uint32_t ram_start = 0;
#elif defined ( __CC_ARM )
    extern uint32_t Image$$RW_IRAM1$$Base;
    volatile uint32_t ram_start = (uint32_t) &Image$$RW_IRAM1$$Base;
#elif defined ( __ICCARM__ )
    extern uint32_t __ICFEDIT_region_RAM_start__;
    volatile uint32_t ram_start = (uint32_t) &__ICFEDIT_region_RAM_start__;
#elif defined   ( __GNUC__ )
    extern uint32_t __data_start__;
    volatile uint32_t ram_start = (uint32_t) &__data_start__;
#endif
    app_ram_base = ram_start;
    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
    ble_enable_params_t   params;
    ble_enable_params_t * p_params = &params;
    ble_conn_bw_counts_t conn_bw_counts;
    params.common_enable_params.p_conn_bw_counts = &conn_bw_counts;

    uint8_t gap_device_name_value[BLE_GAP_DEVNAME_MAX_LEN];
    ble_gap_device_name_t device_name;
    device_name.max_len = BLE_GAP_DEVNAME_MAX_LEN;
    device_name.p_value = gap_device_name_value;
    params.gap_enable_params.p_device_name = &device_name;

    err_code = ble_enable_req_dec(p_rx_buf, rx_buf_len, &p_params);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_enable(p_params, &app_ram_base);
#else
    err_code = ble_enable_req_dec(p_rx_buf, rx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION <= 4
    //Enable BLE SDH to enable events from BLE.
    sd_err_code = sd_ble_enable(&app_ram_base);
#else
    //Enable BLE SDH to enable events from BLE.
    sd_err_code = nrf_sdh_ble_enable(&app_ram_base);
#endif
#endif

    err_code = ble_enable_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_user_mem_reply(uint8_t const * const p_rx_buf,
                                    uint32_t              rx_buf_len,
                                    uint8_t * const       p_tx_buf,
                                    uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    ble_user_mem_block_t   mem_block;
    ble_user_mem_block_t * p_mem_block = &mem_block;
    uint32_t               err_code = NRF_SUCCESS;
    uint32_t               user_mem_tab_index;
    uint16_t               conn_handle;
    /* Allocate user memory context for SoftDevice */

    uint32_t   sd_err_code;

    err_code = ble_user_mem_reply_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_mem_block);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    if (p_mem_block != NULL)
    {
        //Use the context if p_mem_block was not null
        err_code = conn_ble_user_mem_context_create(&user_mem_tab_index);
        SER_ASSERT(err_code == NRF_SUCCESS, err_code);
        m_conn_user_mem_table[user_mem_tab_index].conn_handle = conn_handle;
        m_conn_user_mem_table[user_mem_tab_index].mem_block.len = p_mem_block->len;
        p_mem_block = &(m_conn_user_mem_table[user_mem_tab_index].mem_block);
    }

    sd_err_code = sd_ble_user_mem_reply(conn_handle, p_mem_block);

    err_code = ble_user_mem_reply_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
#if NRF_SD_BLE_API_VERSION >= 4
uint32_t conn_mw_ble_cfg_set(uint8_t const * const p_rx_buf,
                            uint32_t              rx_buf_len,
                            uint8_t * const       p_tx_buf,
                            uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t app_ram_base;

/*lint --e{10} --e{19} --e{27} --e{40} --e{529} -save suppress Error 27: Illegal character */
#if defined(_WIN32) ||  defined(__unix) || defined(__APPLE__)
    uint32_t ram_start = 0;
#elif defined ( __CC_ARM )
    extern uint32_t Image$$RW_IRAM1$$Base;
    volatile uint32_t ram_start = (uint32_t) &Image$$RW_IRAM1$$Base;
#elif defined ( __ICCARM__ )
    extern uint32_t __ICFEDIT_region_RAM_start__;
    volatile uint32_t ram_start = (uint32_t) &__ICFEDIT_region_RAM_start__;
#elif defined   ( __GNUC__ )
    extern uint32_t __data_start__;
    volatile uint32_t ram_start = (uint32_t) &__data_start__;
#endif
    app_ram_base = ram_start;
    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;
    uint32_t cfg_id;
    ble_cfg_t cfg;
    uint8_t gap_device_name_value[BLE_GAP_DEVNAME_MAX_LEN];
    cfg.gap_cfg.device_name_cfg.p_value = gap_device_name_value;
    cfg.gap_cfg.device_name_cfg.max_len = BLE_GAP_DEVNAME_MAX_LEN;
    ble_cfg_t * p_cfg = &cfg;

    err_code = ble_cfg_set_req_dec(p_rx_buf, rx_buf_len, &cfg_id, &p_cfg);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_cfg_set(cfg_id,p_cfg, app_ram_base);

    err_code = ble_cfg_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
#endif
