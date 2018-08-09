/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CLI_BLE_UART)
#include "nrf_cli_ble_uart.h"
#include "ble_nus.h"
#include "nrf_ringbuf.h"
#include "app_timer.h"
#include "nrf_assert.h"
#include "nrf_ble_gatt.h"
#define NRF_LOG_MODULE_NAME cli_ble

#if NRF_CLI_BLE_UART_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_CLI_BLE_UART_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_CLI_BLE_UART_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_CLI_BLE_UART_CONFIG_DEBUG_COLOR

#else //NRF_CLI_BLE_UART_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //NRF_CLI_BLE_UART_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#if NRF_CLI_BLE_UART_MAX_CLIENTS > NRF_SDH_BLE_TOTAL_LINK_COUNT
    #error "Too few BLE peripheral links are supported by the BLE SDH module for the maximal number \
            of BLE transport instances"
#endif

#define NRF_CLI_BLE_UART_TIMEOUT_MS 50
#define OVERHEAD_LENGTH (OPCODE_LENGTH + HANDLE_LENGTH)

BLE_NUS_DEF(m_nus, NRF_CLI_BLE_UART_MAX_CLIENTS);
BLE_LINK_CTX_MANAGER_DEF(m_link_ctx_storage,
                         NRF_CLI_BLE_UART_MAX_CLIENTS,
                         sizeof(nrf_cli_ble_uart_internal_t *));

static void tx_try(nrf_cli_ble_uart_internal_t * p_instance, uint32_t threshold)
{
    uint8_t * p_out_data;
    size_t    out_data_len =
                 nrf_ble_gatt_eff_mtu_get(p_instance->p_gatt, p_instance->p_cb->conn_handle) -
                 OVERHEAD_LENGTH;

    ret_code_t err_code = nrf_ringbuf_get(p_instance->p_tx_ringbuf,
                                          &p_out_data,
                                          &out_data_len,
                                          true);

    if (err_code == NRF_SUCCESS)
    {
        if (out_data_len >= threshold)
        {
            size_t req_data_len = out_data_len;
            err_code = ble_nus_data_send(&m_nus,
                                         p_out_data,
                                         (uint16_t*)&out_data_len,
                                         p_instance->p_cb->conn_handle);

            if ((err_code == NRF_ERROR_BUSY) || (err_code == NRF_ERROR_RESOURCES))
            {
                out_data_len = 0;
            }
            NRF_LOG_INFO("Conn_handle:%d TX req_len: %d, len: %d",
                                         p_instance->p_cb->conn_handle, req_data_len, out_data_len);
            NRF_LOG_HEXDUMP_DEBUG(p_out_data, out_data_len);
            err_code = nrf_ringbuf_free(p_instance->p_tx_ringbuf, out_data_len);
            ASSERT(err_code == NRF_SUCCESS);
        }
        else
        {
            err_code = nrf_ringbuf_free(p_instance->p_tx_ringbuf, 0);
            ASSERT(err_code == NRF_SUCCESS);
        }
    }
}

static void nus_data_handler(ble_nus_evt_t * p_nus_evt)
{
    ret_code_t                     err_code = NRF_SUCCESS;
    nrf_cli_ble_uart_internal_t *  p_instance;
    nrf_cli_ble_uart_internal_t ** pp_instance;

    err_code = blcm_link_ctx_get(&m_link_ctx_storage, p_nus_evt->conn_handle, (void *) &pp_instance);
    ASSERT(err_code == NRF_SUCCESS);

    p_instance = *pp_instance;

    switch (p_nus_evt->type)
    {
        case BLE_NUS_EVT_RX_DATA:
        {
            NRF_LOG_INFO("Conn_handle:%d, Received: %d",
                     p_instance->p_cb->conn_handle, p_nus_evt->params.rx_data.length);
            NRF_LOG_HEXDUMP_DEBUG(p_nus_evt->params.rx_data.p_data, p_nus_evt->params.rx_data.length);
            size_t len = ((size_t) p_nus_evt->params.rx_data.length) & 0x0000FFFF;
            err_code = nrf_ringbuf_cpy_put(p_instance->p_rx_ringbuf,
                                           p_nus_evt->params.rx_data.p_data,
                                           (size_t *)&len);
            ASSERT(err_code == NRF_SUCCESS);

            p_instance->p_cb->handler(NRF_CLI_TRANSPORT_EVT_RX_RDY, p_instance->p_cb->p_context);
            break;
        }
        case BLE_NUS_EVT_TX_RDY:
        {
            //TX_Complete
            uint32_t max_tx_len =  nrf_ble_gatt_eff_mtu_get(p_instance->p_gatt,
                                                            p_instance->p_cb->conn_handle) -
                                                            OVERHEAD_LENGTH;
            tx_try(p_instance, max_tx_len);
            p_instance->p_cb->handler(NRF_CLI_TRANSPORT_EVT_TX_RDY, p_instance->p_cb->p_context);
            break;
        }
        case BLE_NUS_EVT_COMM_STARTED:
            p_instance->p_cb->service_started = true;
            err_code = app_timer_start(*p_instance->p_timer,
                                       APP_TIMER_TICKS(NRF_CLI_BLE_UART_TIMEOUT_MS),
                                       p_instance);
            ASSERT(err_code == NRF_SUCCESS);
            NRF_LOG_INFO("Conn_handle:%d, communication started", p_instance->p_cb->conn_handle);
            break;
        case BLE_NUS_EVT_COMM_STOPPED:
            (void)app_timer_stop(*p_instance->p_timer);
            p_instance->p_cb->service_started = false;
            NRF_LOG_INFO("Conn_handle:%d, communication stopped", p_instance->p_cb->conn_handle);
            break;
        default:
            break;
    }
}

static void timer_handler(void * p_context)
{
    nrf_cli_ble_uart_internal_t * p_instance = (nrf_cli_ble_uart_internal_t *) p_context;
    tx_try(p_instance, 1);

    ret_code_t err_code = app_timer_start(*p_instance->p_timer,
                                  APP_TIMER_TICKS(NRF_CLI_BLE_UART_TIMEOUT_MS), (void *)p_instance);
    ASSERT(err_code == NRF_SUCCESS);
    UNUSED_VARIABLE(err_code);
    UNUSED_PARAMETER(p_context);
}

ret_code_t nrf_cli_ble_uart_service_init(void)
{
    ble_nus_init_t nus_init;

    memset(&nus_init, 0, sizeof(nus_init));
    nus_init.data_handler = nus_data_handler;

    return ble_nus_init(&m_nus, &nus_init);
}

static ret_code_t cli_ble_uart_init(nrf_cli_transport_t const * p_transport,
                                    void const * p_config,
                                    nrf_cli_transport_handler_t evt_handler,
                                    void * p_context)
{
    ret_code_t                     err_code;
    nrf_cli_ble_uart_internal_t ** pp_instance;
    nrf_cli_ble_uart_internal_t  * p_instance =
                             CONTAINER_OF(p_transport, nrf_cli_ble_uart_internal_t, transport);
    nrf_cli_ble_uart_config_t * p_ble_uart_config = (nrf_cli_ble_uart_config_t *)p_config;

    p_instance->p_cb->handler         = evt_handler;
    p_instance->p_cb->p_context       = p_context;
    p_instance->p_cb->service_started = false;
    p_instance->p_cb->conn_handle     = p_ble_uart_config->conn_handle;

    NRF_LOG_INFO("Conn_handle:%d init.", p_ble_uart_config->conn_handle);
    nrf_ringbuf_init(p_instance->p_rx_ringbuf);
    nrf_ringbuf_init(p_instance->p_tx_ringbuf);

    err_code = blcm_link_ctx_get(&m_link_ctx_storage,
                                 p_ble_uart_config->conn_handle,
                                 (void *) &pp_instance);
    VERIFY_SUCCESS(err_code);

    *pp_instance = p_instance;

    return NRF_SUCCESS;
}

static ret_code_t cli_ble_uart_uninit(nrf_cli_transport_t const * p_transport)
{
    nrf_cli_ble_uart_internal_t * p_instance =
                             CONTAINER_OF(p_transport, nrf_cli_ble_uart_internal_t, transport);

    NRF_LOG_INFO("Conn_handle:%d uninit.", p_instance->p_cb->conn_handle);
    ret_code_t ret = app_timer_stop(*p_instance->p_timer);

    return ret;
}

static ret_code_t cli_ble_uart_enable(nrf_cli_transport_t const * p_transport, bool blocking)
{
    nrf_cli_ble_uart_internal_t * p_instance =
                             CONTAINER_OF(p_transport, nrf_cli_ble_uart_internal_t, transport);


    NRF_LOG_INFO("Conn_handle:%d, enable blocking:%d", blocking, p_instance->p_cb->conn_handle);
    if (blocking)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    else
    {
        ret_code_t err_code = NRF_SUCCESS;
        if (!p_instance->p_cb->timer_created)
        {
            err_code = app_timer_create(p_instance->p_timer,
                                        APP_TIMER_MODE_SINGLE_SHOT,
                                        timer_handler);
            p_instance->p_cb->timer_created = true;
        }
        return err_code;
    }
}

static ret_code_t cli_ble_uart_read(nrf_cli_transport_t const * p_transport,
                                    void *                      p_data,
                                    size_t                      length,
                                    size_t *                    p_cnt)
{
    ASSERT(p_cnt);
    nrf_cli_ble_uart_internal_t * p_instance =
                             CONTAINER_OF(p_transport, nrf_cli_ble_uart_internal_t, transport);
    *p_cnt = length;
    ret_code_t err_code = nrf_ringbuf_cpy_get(p_instance->p_rx_ringbuf, p_data, p_cnt);

    if (*p_cnt)
    {
        NRF_LOG_INFO("Conn_handle:%d, read req_len:%d read_len: %d",
                     p_instance->p_cb->conn_handle,
                     length,
                     *p_cnt);
        NRF_LOG_HEXDUMP_DEBUG(p_data, *p_cnt);
    }

    return err_code;
}

static ret_code_t cli_ble_uart_write(nrf_cli_transport_t const * p_transport,
                                     const void *                p_data,
                                     size_t                      length,
                                     size_t *                    p_cnt)
{
    ASSERT(p_cnt);
    nrf_cli_ble_uart_internal_t * p_instance =
                             CONTAINER_OF(p_transport, nrf_cli_ble_uart_internal_t, transport);
    ret_code_t err_code = NRF_SUCCESS;
    if (p_instance->p_cb->service_started)
    {
        *p_cnt = length;
        err_code = nrf_ringbuf_cpy_put(p_instance->p_tx_ringbuf, p_data, p_cnt);

        NRF_LOG_INFO("Conn_handle:%d, write req:%d, buffered:%d",
                                                     p_instance->p_cb->conn_handle, length, *p_cnt);
        NRF_LOG_HEXDUMP_DEBUG(p_data, *p_cnt);
    }
    else
    {
        NRF_LOG_INFO("Conn_handle:%d, write req:%d. Notifications not enabled",
                     p_instance->p_cb->conn_handle, length);
        *p_cnt = length;
        p_instance->p_cb->handler(NRF_CLI_TRANSPORT_EVT_TX_RDY, p_instance->p_cb->p_context);
    }
    return err_code;
}

const nrf_cli_transport_api_t nrf_cli_ble_uart_transport_api = {
        .init = cli_ble_uart_init,
        .uninit = cli_ble_uart_uninit,
        .enable = cli_ble_uart_enable,
        .read = cli_ble_uart_read,
        .write = cli_ble_uart_write,
};

#endif //NRF_MODULE_ENABLED(NRF_CLI_BLE_UART)
