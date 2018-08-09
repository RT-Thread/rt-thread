/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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
#ifndef NRF_LOG_BACKEND_LIBUARTE_H__
#define NRF_LOG_BACKEND_LIBUARTE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_cli.h"
#include "nrf_libuarte.h"
#include "nrf_ringbuf.h"
#include "app_timer.h"

/**@file
 *
 * @defgroup nrf_cli_libuarte libUARTE command line interface transport layer.
 * @ingroup nrf_cli
 *
 * @{
 *
 */

/**
 * @brief Command line interface transport.
 * */
extern const nrf_cli_transport_api_t cli_libuarte_transport_api;

typedef struct cli_libuarte_internal_s cli_libuarte_internal_t;

typedef struct {
    nrf_cli_transport_handler_t   handler;
    void *                        p_context;
    bool                          blocking;
} cli_libuarte_internal_cb_t;

struct cli_libuarte_internal_s {
    nrf_cli_transport_t      transport;
    cli_libuarte_internal_cb_t * p_cb;
    nrf_ringbuf_t const *    p_rx_ringbuf;
    nrf_ringbuf_t const *    p_tx_ringbuf;
};

typedef struct
{
    uint32_t             tx_pin;
    uint32_t             rx_pin;
    nrf_uarte_hwfc_t     hwfc;          ///< Flow control configuration.
    nrf_uarte_parity_t   parity;        ///< Parity configuration.
    nrf_uarte_baudrate_t baudrate;      ///< Baudrate.
} cli_libuarte_config_t;

/**@brief CLI libUARTE transport definition.
 *
 * @param _name      Name of instance.
 * @param _tx_buf_sz Size of TX ring buffer.
 * @param _rx_buf_sz Size of RX ring buffer.
 */
#define NRF_CLI_LIBUARTE_DEF(_name, _tx_buf_sz, _rx_buf_sz)   \
    NRF_RINGBUF_DEF(CONCAT_2(_name,_tx_ringbuf), _tx_buf_sz); \
    NRF_RINGBUF_DEF(CONCAT_2(_name,_rx_ringbuf), _rx_buf_sz); \
    static cli_libuarte_internal_cb_t CONCAT_2(_name, _cb);   \
    static const cli_libuarte_internal_t _name = {            \
        .transport = {.p_api = &cli_libuarte_transport_api},  \
        .p_cb = &CONCAT_2(_name, _cb),                        \
        .p_rx_ringbuf = &CONCAT_2(_name,_rx_ringbuf),         \
        .p_tx_ringbuf = &CONCAT_2(_name,_tx_ringbuf),         \
    }
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_LOG_BACKEND_LIBUARTE_H__ */
