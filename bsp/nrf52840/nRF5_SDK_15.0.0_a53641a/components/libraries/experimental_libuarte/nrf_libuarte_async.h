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
#ifndef UART_ASYNC_H
#define UART_ASYNC_H
#include <stdint.h>
#include "sdk_errors.h"
#include <hal/nrf_uarte.h>

/** @brief Types of libuarte driver events. */
typedef enum
{
    NRF_LIBUARTE_ASYNC_EVT_RX_DATA, ///< Requested TX transfer completed.
    NRF_LIBUARTE_ASYNC_EVT_TX_DONE, ///< Requested RX transfer completed.
    NRF_LIBUARTE_ASYNC_EVT_ERROR    ///< Error reported by UARTE peripheral.
} nrf_libuarte_async_evt_type_t;

/** @brief Structure for libuarte async transfer completion event. */
typedef struct
{
    uint8_t  * p_data; ///< Pointer to memory used for transfer.
    size_t     length; ///< Number of bytes transfered.
} nrf_libuarte_async_data_t;

/** @brief Structure for libuarte async configuration. */
typedef struct
{
    uint32_t             rx_pin;     ///< RXD pin number.
    uint32_t             tx_pin;     ///< TXD pin number.
    uint32_t             cts_pin;    ///< CTS pin number.
    uint32_t             rts_pin;    ///< RTS pin number.
    uint32_t             timeout_us; ///< Receiver timeout in us unit.
    nrf_uarte_hwfc_t     hwfc;       ///< Flow control configuration.
    nrf_uarte_parity_t   parity;     ///< Parity configuration.
    nrf_uarte_baudrate_t baudrate;   ///< Baudrate.
} nrf_libuarte_async_config_t;

/** @brief Structure for libuarte error event. */
typedef struct
{
    nrf_libuarte_async_evt_type_t type; ///< Event type.
    union {
        nrf_libuarte_async_data_t rxtx; ///< RXD/TXD data.
    } data;                             ///< Union with data.
} nrf_libuarte_async_evt_t;

/**
 * @brief Interrupt event handler.
 *
 * @param[in] p_evt  Pointer to event structure. Event is allocated on the stack so it is available
 *                   only within the context of the event handler.
 */
typedef void (*nrf_libuarte_async_evt_handler)(nrf_libuarte_async_evt_t * p_evt);

/**
 * @brief Function for initializing the libuarte async library.
 *
 * @param[in] p_config     Pointer to the structure with initial configuration.
 * @param[in] evt_handler  Event handler provided by the user. Must not be NULL.
 *
 * @return NRF_SUCCESS when properly initialized. NRF_ERROR_INTERNAL otherwise.
 */
ret_code_t nrf_libuarte_async_init(nrf_libuarte_async_config_t const * p_config,
                                   nrf_libuarte_async_evt_handler      evt_handler);

/** @brief Function for uninitializing the libuarte async library */
void nrf_libuarte_async_uninit(void);

/**
 * @brief Funtrion for setting buffer and its size for received data.
 *
 * @param chunk_size  Number of bytes in chunk of data
 */
void nrf_libuarte_async_enable(size_t chunk_size);

/**
 * @brief Function for sending data asynchronously over UARTE.
 *
 * @param[in] p_data  Pointer to data.
 * @param[in] length  Number of bytes to send. Maximum possible length is
 *                    dependent on the used SoC (see the MAXCNT register
 *                    description in the Product Specification). The library
 *                    checks it with assertion.
 *
 * @retval NRF_ERROR_BUSY      Data is transferring.
 * @retval NRF_ERROR_INTERNAL  Error during configuration.
 * @retval NRF_SUCCESS         Buffer set for sending.
 */
ret_code_t nrf_libuarte_async_tx(uint8_t * p_data, size_t length);

/**
 * @brief Function for deallocating received buffer data.
 *
 * @param[in] p_data  Pointer to data.
 * @param[in] length  Number of bytes to free.
 */
void nrf_libuarte_async_rx_free(uint8_t * p_data, size_t length);

#endif //UART_ASYNC_H
