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
#ifndef NRF_LIBUARTE_H
#define NRF_LIBUARTE_H

#include "sdk_errors.h"
#include "nrf_uarte.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup nrf_libuarte libUARTE
 * @ingroup app_common
 *
 * @brief Module for reliable communication over UARTE.
 *
 * @{
 */

typedef enum
{
    NRF_LIBUARTE_EVT_RX_DATA,    ///< Data received.
    NRF_LIBUARTE_EVT_RX_BUF_REQ, ///< Requesting new buffer for receiving data.
    NRF_LIBUARTE_EVT_TX_DONE,    ///< Requested TX transfer completed.
    NRF_LIBUARTE_EVT_ERROR       ///< Error reported by the UARTE peripheral.
} nrf_libuarte_evt_type_t;

typedef struct
{
    uint8_t  * p_data; ///< Pointer to the data to be sent or received.
    size_t     length; ///< Length of the data.
} nrf_libuarte_data_t;

typedef struct
{
    nrf_libuarte_evt_type_t type; ///< Event type.
    union {
        nrf_libuarte_data_t rxtx; ///< Data provided for transfer completion events.
    } data;
} nrf_libuarte_evt_t;

typedef struct {
    uint32_t             tx_pin;        ///< TXD pin number.
    uint32_t             rx_pin;        ///< RXD pin number.
    uint32_t             cts_pin;       ///< CTS pin number.
    uint32_t             rts_pin;       ///< RTS pin number.
    uint32_t             startrx_evt;   ///< Event to trigger STARTRX task in UARTE.
    uint32_t             endrx_evt;     ///< Event to trigger STOPRX task in UARTE.
    uint32_t             rxstarted_tsk; ///< Task to be triggered when RXSTARTED UARTE event occurs.
    uint32_t             rxdone_tsk;    ///< Task to be triggered when ENDRX UARTE event occurs.
    nrf_uarte_hwfc_t     hwfc;          ///< Flow control configuration.
    nrf_uarte_parity_t   parity;        ///< Parity configuration.
    nrf_uarte_baudrate_t baudrate;      ///< Baud rate.
    uint8_t              irq_priority;  ///< Interrupt priority.
} nrf_libuarte_config_t;

typedef void (*nrf_libuarte_evt_handler_t)(nrf_libuarte_evt_t * p_evt);

/**
 * @brief Function for initializing the libUARTE library.
 *
 * @param[in] p_config     Pointer to the structure with initial configuration.
 * @param[in] evt_handler  Event handler provided by the user. Must not be NULL.
 *
 * @return NRF_SUCCESS when properly initialized. NRF_ERROR_INTERNAL otherwise.
 */
ret_code_t nrf_libuarte_init(nrf_libuarte_config_t * p_config, nrf_libuarte_evt_handler_t evt_handler);

/** @brief Function for uninitializing the libUARTE library. */
void nrf_libuarte_uninit(void);

/**
 * @brief Function for sending data over UARTE using EasyDMA.
 *
 * @param[in] p_data  Pointer to data.
 * @param[in] len     Number of bytes to send.
 *
 * @retval NRF_ERROR_BUSY      Data is transferring.
 * @retval NRF_ERROR_INTERNAL  Error during PPI channel configuration.
 * @retval NRF_SUCCESS         Buffer set for sending.
 */
ret_code_t nrf_libuarte_tx(uint8_t * p_data, size_t len);

/**
 * @brief Function for starting receiving data with additional configuration of external
 *        trigger to start receiving.
 *
 * @param p_data          Pointer to data.
 * @param len             Number of bytes to receive. Maximum possible length is
 *                        dependent on the used SoC (see the MAXCNT register
 *                        description in the Product Specification). The library
 *                        checks it with an assertion.
 * @param ext_trigger_en  True to disable immediate start.
 *
 * @retval NRF_ERROR_INTERNAL  Error during PPI channel configuration.
 * @retval NRF_SUCCESS         Buffer set for receiving.
 */
ret_code_t nrf_libuarte_rx_start(uint8_t * p_data, size_t len, bool ext_trigger_en);

/**
 * @brief Function for setting a buffer for data that will be later received in UARTE.
 *
 * @param p_data  Pointer to data.
 * @param len     Number of bytes to receive. Maximum possible length is
 *                dependent on the used SoC (see the MAXCNT register
 *                description in the Product Specification). The library
 *                checks it with an assertion.
 */
void nrf_libuarte_rx_buf_rsp(uint8_t * p_data, size_t len);

/** @brief Function for stopping receiving data over UARTE. */
void nrf_libuarte_rx_stop(void);

/** @} */

#endif //NRF_libuarte_H
