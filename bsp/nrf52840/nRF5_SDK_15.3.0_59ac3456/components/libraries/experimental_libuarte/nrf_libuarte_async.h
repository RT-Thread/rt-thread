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
#ifndef UART_ASYNC_H
#define UART_ASYNC_H
#include <stdint.h>
#include "sdk_errors.h"
#include "nrf_balloc.h"
#include "nrf_queue.h"
#include "nrfx_ppi.h"
#include "nrfx_timer.h"
#include "nrfx_rtc.h"
#include "nrf_libuarte.h"
#include <hal/nrf_uarte.h>

/** @brief Types of libuarte driver events. */
typedef enum
{
    NRF_LIBUARTE_ASYNC_EVT_RX_DATA, ///< Requested TX transfer completed.
    NRF_LIBUARTE_ASYNC_EVT_TX_DONE, ///< Requested RX transfer completed.
    NRF_LIBUARTE_ASYNC_EVT_ERROR    ///< Error reported by UARTE peripheral.
} nrf_libuarte_async_evt_type_t;

typedef enum
{
    NRF_LIBUARTE_ASYNC_PPI_CH_RXRDY_CLEAR,
    NRF_LIBUARTE_ASYNC_PPI_CH_COMPARE_SHUTDOWN,
    NRF_LIBUARTE_ASYNC_PPI_CH_MAX
} nrf_libuarte_async_ppi_channel_t;

/** @brief Structure for libuarte async transfer completion event. */
typedef struct
{
    uint8_t  * p_data; ///< Pointer to memory used for transfer.
    size_t     length; ///< Number of bytes transfered.
} nrf_libuarte_async_data_t;


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
typedef void (*nrf_libuarte_async_evt_handler_t)(void * context, nrf_libuarte_async_evt_t * p_evt);

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

/**
 * @brief nrf_libuarte_async control block (placed in RAM).
 */
typedef struct {
    nrf_libuarte_async_evt_handler_t evt_handler;
    void * context;
    nrf_ppi_channel_t ppi_channels[NRF_LIBUARTE_ASYNC_PPI_CH_MAX];
    int32_t alloc_cnt;
    uint32_t rx_count;
    uint32_t sub_rx_count;
    uint8_t * p_curr_rx_buf;
    uint32_t rx_free_cnt;
    size_t rx_chunk_size;
    uint32_t timeout_us;
} nrf_libuarte_async_ctrl_blk_t;

/**
 * @brief nrf_libuarte_async instance structure (placed in ROM).
 */
typedef struct {
	const nrf_balloc_t * p_rx_pool;
	const nrf_queue_t * p_rx_queue;
	const nrfx_rtc_t * p_rtc;
	const nrfx_timer_t * p_timer;
	const nrf_libuarte_t * p_libuarte;
	nrf_libuarte_async_ctrl_blk_t * p_ctrl_blk;
	nrfx_rtc_handler_t rtc_handler;
} nrf_libuarte_async_t;

void nrf_libuarte_async_timeout_handler(const nrf_libuarte_async_t * p_libuarte);

#define NRF_LIBUARTE_PERIPHERAL_NOT_USED 255

#define LIBUARTE_ASYNC_DEBRACKET(...) __VA_ARGS__

#define __LIBUARTE_ASYNC_ARG_2(ignore_this, val, ...) val
#define __LIBUARTE_ASYNC_ARG_2_DEBRACKET(ignore_this, val, ...) LIBUARTE_ASYNC_DEBRACKET val

/* Macro for injecting code based on flag evaluation. If flag exists and equals 1
 * then first code is compiled in, else second option. Note that code must be
 * in the brackets. Example usage:
 *  _LIBUARTE_ASYNC_EVAL(MY_FLAG, (foo();), () )
 *  If MY_FLAG exists and equals 1 then macros resolves to foo(); call, else it resolves to
 *  empty line.
 *
 * @param _eval_level Flag to be evaluated. It's positively evaluated if exists and equals 1.
 * @param _iftrue     Macro is resolved to that code on positive flag evaluation. Code must be
 *                    in the brackets.
 * @param _iffalse    Macro is resolved to that code on negative flag evaluation. Code must be
 *                    in the brackets.
 */
#define _LIBUARTE_ASYNC_EVAL(_eval_flag, _iftrue, _iffalse) \
    _LIBUARTE_ASYNC_EVAL1(_eval_flag, _iftrue, _iffalse)

#define _LIBUARTE_ASYNC_EVAL1(_eval_flag, _iftrue, _iffalse) \
    _LIBUARTE_ASYNC_EVAL2(_LIBUARTE_ASYNC_ZZZZ##_eval_flag, _iftrue, _iffalse)

#define _LIBUARTE_ASYNC_ZZZZ1 _LIBUARTE_ASYNC_YYYY,

#define _LIBUARTE_ASYNC_EVAL2(one_or_two_args, _iftrue, _iffalse) \
    __LIBUARTE_ASYNC_ARG_2_DEBRACKET(one_or_two_args _iftrue, _iffalse)

/**
 * @brief Macro for creating instance of libuarte_async.
 *
 * Libuarte_async requires one timer-like peripheral (RTC or TIMER) for triggering RX timeout.
 * Macro will create instance only for peripheral which is used.
 *
 * @param _name        Instance name.
 * @param _uarte_idx   UARTE instance used.
 * @param _timer0_idx  TIMER instance used by libuarte for bytes counting.
 * @param _rtc1_idx    RTC instance used for timeout, set to NRF_LIBUARTE_PERIPHERAL_NOT_USED
 *                     if TIMER instance is used.
 * @param _timer1_idx  TIMER instance used for timeout, set to NRF_LIBUARTE_PERIPHERAL_NOT_USED
 *                     if RTC instance is used.
 * @param _rx_buf_size Size of single RX buffer. Size impacts accepted latency between buffer
 *                     request and providing next buffer. Next must be provided within before
 *                     _rx_buf_size bytes is received.
 * @param _rx_buf_cnt  Number of buffers in the RX buffer pool. Size impacts accepted latency
 *                     between NRF_LIBUARTE_ASYNC_EVT_RX_DATA event and
 *                     @ref nrf_libuarte_async_rx_free.
 */
#define NRF_LIBUARTE_ASYNC_DEFINE(_name, _uarte_idx, _timer0_idx,\
                                  _rtc1_idx, _timer1_idx,\
                                  _rx_buf_size, _rx_buf_cnt) \
      STATIC_ASSERT(_rx_buf_cnt >= 3, "Wrong number of RX buffers");\
      NRF_LIBUARTE_DEFINE(CONCAT_2(_name, _libuarte), _uarte_idx, _timer0_idx);\
      NRF_QUEUE_DEF(uint8_t *, CONCAT_2(_name,_rxdata_queue), _rx_buf_cnt, NRF_QUEUE_MODE_NO_OVERFLOW);\
      NRF_BALLOC_DEF(CONCAT_2(_name,_rx_pool), _rx_buf_size, _rx_buf_cnt);\
      /* Create TIMER instance only if _timer1_idx != NRF_LIBUARTE_PERIPHERAL_NOT_USED */ \
      _LIBUARTE_ASYNC_EVAL(\
              NRFX_CONCAT_3(NRFX_TIMER, _timer1_idx, _ENABLED),\
              (STATIC_ASSERT((_timer1_idx == NRF_LIBUARTE_PERIPHERAL_NOT_USED) || (CONCAT_3(NRFX_TIMER,_timer1_idx, _ENABLED) == 1), "TIMER instance not enabled");\
               static const nrfx_timer_t CONCAT_2(_name, _timer) = NRFX_TIMER_INSTANCE(_timer1_idx);),\
              (/* empty */))\
      /* Create RTC instance only if _timer1_idx != NRF_LIBUARTE_PERIPHERAL_NOT_USED */ \
      _LIBUARTE_ASYNC_EVAL(\
              NRFX_CONCAT_3(NRFX_RTC, _rtc1_idx, _ENABLED),\
              (STATIC_ASSERT((_rtc1_idx == NRF_LIBUARTE_PERIPHERAL_NOT_USED) || (CONCAT_3(NRFX_RTC,_rtc1_idx, _ENABLED) == 1), "RTC instance not enabled");\
               static const nrfx_rtc_t CONCAT_2(_name, _rtc) = NRFX_RTC_INSTANCE(_rtc1_idx);),\
              (/* empty */))\
      static nrf_libuarte_async_ctrl_blk_t CONCAT_2(_name, ctrl_blk);\
      static void CONCAT_2(_name, _rtc_handler)(nrfx_rtc_int_type_t int_type);\
      static nrf_libuarte_async_t _name = {\
              .p_rx_pool = &CONCAT_2(_name,_rx_pool),\
              .p_rx_queue =  &CONCAT_2(_name,_rxdata_queue),\
              /* If p_rtc is not NULL it means that RTC is used for RX timeout */ \
              .p_rtc = _LIBUARTE_ASYNC_EVAL(NRFX_CONCAT_3(NRFX_RTC, _rtc1_idx, _ENABLED), (&CONCAT_2(_name, _rtc)), (NULL)),\
              /* If p_timer is not NULL it means that RTC is used for RX timeout */ \
              .p_timer = _LIBUARTE_ASYNC_EVAL(NRFX_CONCAT_3(NRFX_TIMER, _timer1_idx, _ENABLED), (&CONCAT_2(_name, _timer)), (NULL)),\
              .p_libuarte = &CONCAT_2(_name, _libuarte),\
              .p_ctrl_blk = &CONCAT_2(_name, ctrl_blk),\
              _LIBUARTE_ASYNC_EVAL(\
                  NRFX_CONCAT_3(NRFX_RTC, _rtc1_idx, _ENABLED),\
                  (.rtc_handler =CONCAT_2(_name, _rtc_handler)),\
                  ()\
              )\
      };\
      /* RTC compare event is not periodic but need to be enabled again in the callback. */ \
      _LIBUARTE_ASYNC_EVAL(\
          NRFX_CONCAT_3(NRFX_RTC, _rtc1_idx, _ENABLED),\
          (\
             static void CONCAT_2(_name, _rtc_handler)(nrfx_rtc_int_type_t int_type)\
             { \
               (void)nrfx_rtc_cc_set(_name.p_rtc, 0, 32 * _name.p_ctrl_blk->timeout_us, true);\
               nrf_libuarte_async_timeout_handler(&_name);\
             }\
          ),\
          ()\
      )


/**
 * @brief Function for initializing the libuarte async library.
 *
 * @param[in] p_libuarte   Libuarte_async instance.
 * @param[in] p_config     Pointer to the structure with initial configuration.
 * @param[in] evt_handler  Event handler provided by the user. Must not be NULL.
 *
 * @return NRF_SUCCESS when properly initialized. NRF_ERROR_INTERNAL otherwise.
 */
ret_code_t nrf_libuarte_async_init(const nrf_libuarte_async_t * const p_libuarte,
                                   nrf_libuarte_async_config_t const * p_config,
                                   nrf_libuarte_async_evt_handler_t    evt_handler,
                                   void * context);

/** @brief Function for uninitializing the libuarte async library.
 *
 * @param[in] p_libuarte   Libuarte_async instance.
 */
void nrf_libuarte_async_uninit(const nrf_libuarte_async_t * const p_libuarte);

/**
 * @brief Function for enabling receiver.
 *
 * @param p_libuarte  Libuarte_async instance.
 */
void nrf_libuarte_async_enable(const nrf_libuarte_async_t * const p_libuarte);

/**
 * @brief Function for sending data asynchronously over UARTE.
 *
 * @param[in] p_libuarte Libuarte_async instance.
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
ret_code_t nrf_libuarte_async_tx(const nrf_libuarte_async_t * const p_libuarte,
                                 uint8_t * p_data, size_t length);

/**
 * @brief Function for deallocating received buffer data.
 *
 * @param[in] p_libuarte Libuarte_async instance.
 * @param[in] p_data  Pointer to data.
 * @param[in] length  Number of bytes to free.
 */
void nrf_libuarte_async_rx_free(const nrf_libuarte_async_t * const p_libuarte,
                                uint8_t * p_data, size_t length);

#endif //UART_ASYNC_H
