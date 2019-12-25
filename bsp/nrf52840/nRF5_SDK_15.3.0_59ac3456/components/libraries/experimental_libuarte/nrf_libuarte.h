/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#include "nrfx_ppi.h"
#include "nrfx_timer.h"
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

/**
 * @brief PPI channels used by libuarte
 */
typedef enum
{
    NRF_LIBUARTE_PPI_CH_EXT_TRIGGER_STARTRX_EN_ENDRX_STARTX,
    NRF_LIBUARTE_PPI_CH_RXSTARTED_EXT_TSK,
    NRF_LIBUARTE_PPI_CH_EXT_STOP_STOPRX,
    NRF_LIBUARTE_PPI_CH_EXT_STOP_GROUPS_EN,
    NRF_LIBUARTE_PPI_CH_RXRDY_TIMER_COUNT,

    NRF_LIBUARTE_PPI_CH_RX_MAX,
    NRF_LIBUARTE_PPI_CH_ENDRX_STARTRX = NRF_LIBUARTE_PPI_CH_RX_MAX,
    NRF_LIBUARTE_PPI_CH_ENDRX_EXT_TSK,

    NRF_LIBUARTE_PPI_CH_RX_GROUP_MAX,

    NRF_LIBUARTE_PPI_CH_ENDTX_STARTTX = NRF_LIBUARTE_PPI_CH_RX_GROUP_MAX,

    NRF_LIBUARTE_PPI_CH_MAX
} nrf_libuarte_ppi_channel_t;

/**
 * @brief PPI groups used by libuarte
 */
typedef enum
{
    NRF_LIBUARTE_PPI_GROUP_ENDRX_STARTRX, ///< Group used for controlling PPI connection between ENDRX and STARTRX
    NRF_LIBUARTE_PPI_GROUP_ENDRX_EXT_RXDONE_TSK, ///< Group used for controlling PPI connection between ENDRX and RXDONE
    NRF_LIBUARTE_PPI_GROUP_MAX
} nrf_libuarte_ppi_group_t;

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

typedef void (*nrf_libuarte_evt_handler_t)(void * context,
                                           nrf_libuarte_evt_t * p_evt);

extern const IRQn_Type libuarte_irqn[];

typedef struct {
    nrf_ppi_channel_t ppi_channels[NRF_LIBUARTE_PPI_CH_MAX];
    nrf_ppi_channel_group_t ppi_groups[NRF_LIBUARTE_PPI_GROUP_MAX];

    uint8_t * p_tx;
    size_t tx_len;
    size_t tx_cur_idx;

    uint8_t * p_cur_rx;
    uint8_t * p_next_rx;
    uint8_t * p_next_next_rx;
    nrf_libuarte_evt_handler_t evt_handler;
    uint32_t last_rx_byte_cnt;
    uint32_t last_pin_rx_byte_cnt;
    uint32_t chunk_size;
    void * context;
    uint16_t tx_chunk8;

} nrf_libuarte_ctrl_blk_t;

typedef struct {
    nrf_libuarte_ctrl_blk_t * ctrl_blk;
    nrfx_timer_t timer;
    NRF_UARTE_Type * uarte;
} nrf_libuarte_t;

#define NRF_LIBUARTE_DEFINE(_name, _uarte_idx, _timer_idx) \
    STATIC_ASSERT(_uarte_idx < UARTE_COUNT, "UARTE instance not present");\
    STATIC_ASSERT(CONCAT_2(NRF_LIBUARTE_UARTE,_uarte_idx) == 1, "UARTE instance not enabled");\
    STATIC_ASSERT(CONCAT_3(NRFX_TIMER,_timer_idx, _ENABLED) == 1, "Timer instance not enabled");\
    static nrf_libuarte_ctrl_blk_t CONCAT_2(_name, ctrl_blk); \
    static const nrf_libuarte_t _name = { \
        .ctrl_blk = &CONCAT_2(_name, ctrl_blk), \
        .timer = NRFX_TIMER_INSTANCE(_timer_idx), \
        .uarte = CONCAT_2(NRF_UARTE, _uarte_idx),\
    }

/**
 * @brief Function for initializing the libUARTE library.
 *
 * @param[in] p_libuarte   Pointer to libuarte instance.
 * @param[in] p_config     Pointer to the structure with initial configuration.
 * @param[in] evt_handler  Event handler provided by the user. Must not be NULL.
 * @param[in] context      User context passed in the callback.
 *
 * @return NRF_SUCCESS when properly initialized. NRF_ERROR_INTERNAL otherwise.
 */
ret_code_t nrf_libuarte_init(const nrf_libuarte_t * const p_libuarte,
                             nrf_libuarte_config_t * p_config,
                             nrf_libuarte_evt_handler_t evt_handler, void * context);

/**
 * @brief Function for uninitializing the libUARTE library.
 *
 * @param[in] p_libuarte     Pointer to libuarte instance.
 */
void nrf_libuarte_uninit(const nrf_libuarte_t * const p_libuarte);

/**
 * @brief Function for sending data over UARTE using EasyDMA.
 *
 * @param[in] p_libuarte Pointer to libuarte instance.
 * @param[in] p_data     Pointer to data.
 * @param[in] len        Number of bytes to send.
 *
 * @retval NRF_ERROR_BUSY      Data is transferring.
 * @retval NRF_ERROR_INTERNAL  Error during PPI channel configuration.
 * @retval NRF_SUCCESS         Buffer set for sending.
 */
ret_code_t nrf_libuarte_tx(const nrf_libuarte_t * const p_libuarte, uint8_t * p_data, size_t len);

/**
 * @brief Function for starting receiving data with additional configuration of external
 *        trigger to start receiving.
 *
 * @param p_libuarte      Pointer to libuarte instance.
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
ret_code_t nrf_libuarte_rx_start(const nrf_libuarte_t * const p_libuarte,
                                 uint8_t * p_data, size_t len, bool ext_trigger_en);

/**
 * @brief Function for setting a buffer for data that will be later received in UARTE.
 *
 * @param p_libuarte  Pointer to libuarte instance.
 * @param p_data      Pointer to data.
 * @param len         Number of bytes to receive. Maximum possible length is
 *                    dependent on the used SoC (see the MAXCNT register
 *                    description in the Product Specification). The library
 *                    checks it with an assertion.
 */
void nrf_libuarte_rx_buf_rsp(const nrf_libuarte_t * const p_libuarte,
                             uint8_t * p_data, size_t len);

/**
 * @brief Function for stopping receiving data over UARTE.
 *
 * @param p_libuarte       Pointer to libuarte instance.
 */
void nrf_libuarte_rx_stop(const nrf_libuarte_t * const p_libuarte);

/** @} */

#endif //NRF_libuarte_H
