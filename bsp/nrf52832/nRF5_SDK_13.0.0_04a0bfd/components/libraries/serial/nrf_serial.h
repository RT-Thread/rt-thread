/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_SERIAL_H__
#define NRF_SERIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "nrf_drv_uart.h"
#include "nrf_queue.h"
#include "nrf_mtx.h"
#include "app_timer.h"


/**@file
 *
 * @defgroup nrf_serial Serial port abstraction layer
 * @{
 * @ingroup app_common
 *
 * @brief Serial module interface.
 * @details This module is more sophisticated than @ref nrf_drv_uart. It internally uses
 * mutex, queues, and app_timer. You can configure it to work in three different modes
 * (polling, interrupt, DMA). API can be configured to work in synchronous mode. Both read and write
 * methods have a timeout parameter. Asynchronous mode is available by passing 0 as the
 * timeout parameter.
 * @warning Do not use synchronous API (timeout_ms parameter > 0) in IRQ
 *          context. It may lead to a deadlock because the timeout interrupt cannot
 *          preempt the current IRQ context.
 */

typedef struct nrf_serial_s nrf_serial_t;

/**
 * @brief Serial port mode.
 * */
typedef enum {
    NRF_SERIAL_MODE_POLLING,    /**< Polling mode.*/
    NRF_SERIAL_MODE_IRQ,        /**< Interrupt mode.*/
    NRF_SERIAL_MODE_DMA,        /**< DMA mode.*/
} nrf_serial_mode_t;



/**
 * @brief Creates an instance of @ref nrf_drv_uart_config_t.
 *
 * @param _name         Instance name.
 * @param _rx_pin       RX pin number.
 * @param _tx_pin       TX pin number.
 * @param _rts_pin      RTS pin number.
 * @param _cts_pin      CTS pin number.
 * @param _flow_control Flow control enable/disable (@ref nrf_uart_hwfc_t).
 * @param _parity       Parity enable/disable (@ref nrf_uart_parity_t).
 * @param _baud_rate    Baud rate (@ref nrf_uart_baudrate_t).
 * @param _irq_prio     Interrupt priority.
 *
 * */
#define NRF_SERIAL_DRV_UART_CONFIG_DEF(_name,            \
                                       _rx_pin,          \
                                       _tx_pin,          \
                                       _rts_pin,         \
                                       _cts_pin,         \
                                       _flow_control,    \
                                       _parity,          \
                                       _baud_rate,       \
                                       _irq_prio)        \
    static const nrf_drv_uart_config_t _name = {         \
            .pselrxd = _rx_pin,                          \
            .pseltxd = _tx_pin,                          \
            .pselrts = _rts_pin,                         \
            .pselcts = _cts_pin,                         \
            .hwfc = _flow_control,                       \
            .parity = _parity,                           \
            .baudrate = _baud_rate,                      \
            .interrupt_priority = _irq_prio,             \
    }

/**
 * @brief Serial port RX and TX queues.
 *
 * @note Use the @ref NRF_SERIAL_QUEUES_DEF macro to create an instance of this
 *       structure.
 * */
typedef struct {
    nrf_queue_t const * p_rxq;    //!< Receive queue handle.
    nrf_queue_t const * p_txq;    //!< Transmit queue handle.
} nrf_serial_queues_t;

/**
 * @brief Creates an instance of serial port queues.
 *
 * @param _name     Instance name.
 * @param _tx_size  TX queue size.
 * @param _rx_size  RX queue size.
 * */
#define NRF_SERIAL_QUEUES_DEF(_name, _tx_size, _rx_size)                       \
    NRF_QUEUE_DEF(uint8_t, _name##_rxq, _rx_size, NRF_QUEUE_MODE_NO_OVERFLOW); \
    NRF_QUEUE_DEF(uint8_t, _name##_txq, _tx_size, NRF_QUEUE_MODE_NO_OVERFLOW); \
    static const nrf_serial_queues_t _name = {                                 \
        .p_rxq = &_name##_rxq,                                                 \
        .p_txq = &_name##_txq,                                                 \
    }

/**
 * @brief Serial buffers. Data slices used by @ref nrf_drv_uart_tx and
 *        @ref nrf_drv_uart_rx.
 *
 * @note Use the @ref NRF_SERIAL_BUFFERS_DEF macro to create an instance of this
 *       structure.
 * */
typedef struct {
    void * p_txb;     //!< TX buffer.
    void * p_rxb;     //!< RX buffer.
    uint8_t tx_size;  //!< TX buffer size.
    uint8_t rx_size;  //!< RX buffer size.
} nrf_serial_buffers_t;

/**
 * @brief Creates an instance of serial port buffers.
 *
 * @param _name     Instance name.
 * @param _tx_size  TX buffer size.
 * @param _rx_size  RX buffer size.
 * */
#define NRF_SERIAL_BUFFERS_DEF(_name, _tx_size, _rx_size)           \
    STATIC_ASSERT_MSG((_tx_size) <= UINT8_MAX, NRF_SERIAL_TX_SIZE); \
    STATIC_ASSERT_MSG((_rx_size) <= UINT8_MAX, NRF_SERIAL_RX_SIZE); \
    static uint8_t _name##_txb[_tx_size];                           \
    static uint8_t _name##_rxb[_rx_size];                           \
    static const nrf_serial_buffers_t _name = {                     \
        .p_txb = _name##_txb,                                       \
        .p_rxb = _name##_rxb,                                       \
        .tx_size = sizeof(_name##_txb),                             \
        .rx_size = sizeof(_name##_rxb),                             \
    }

/**
 * @brief Events generated by this module.
 * */
typedef enum {
    NRF_SERIAL_EVENT_TX_DONE,   //!< Chunk of data has been sent.
    NRF_SERIAL_EVENT_RX_DATA,   //!< New chunk of data has been received.
    NRF_SERIAL_EVENT_DRV_ERR,   //!< Internal driver error.
    NRF_SERIAL_EVENT_FIFO_ERR,  //!< RX FIFO overrun.
} nrf_serial_event_t;

/**
 * @brief Event handler type.
 * */
typedef void (*nrf_serial_evt_handler_t)(struct nrf_serial_s const * p_serial,
                                         nrf_serial_event_t event);

/**
 * @brief Sleep handler type.
 * */
typedef void (*nrf_serial_sleep_handler_t)(void);

/**
 * @brief Configuration of UART serial interface.
 *
 * @note Use the @ref NRF_SERIAL_CONFIG_DEF macro to create an instance of this
 *       structure.
 *
 */
typedef struct {
    nrf_serial_mode_t mode;         //!< Serial port mode.

    nrf_serial_queues_t const *  p_queues;      //!< Serial port queues.
    nrf_serial_buffers_t const * p_buffers;     //!< DMA buffers.
    nrf_serial_evt_handler_t     ev_handler;    //!< Event handler.
    nrf_serial_sleep_handler_t   sleep_handler; //!< Sleep mode handler.
} nrf_serial_config_t;

/**
 * @brief Creates an instance of serial port configuration.
 *
 * @param _name       Instance name.
 * @param _mode       Serial port mode.
 * @param _queues     Serial port queues. NULL can be passed in @ref NRF_SERIAL_MODE_POLLING mode.
 * @param _buffers    Serial port buffers. NULL can be passed in @ref NRF_SERIAL_MODE_POLLING mode.
 * @param _ev_handler Serial port event handler. NULL can be passed in any mode.
 * @param _sleep      Serial port sleep handler. NULL can be passed in any mode.
 * */
#define NRF_SERIAL_CONFIG_DEF(_name, _mode, _queues, _buffers, _ev_handler, _sleep)  \
    static const nrf_serial_config_t _name = {                                       \
        .mode = _mode,                                                               \
        .p_queues = _queues,                                                         \
        .p_buffers = _buffers,                                                       \
        .ev_handler = _ev_handler,                                                   \
        .sleep_handler = _sleep,                                                     \
    }

#define NRF_SERIAL_RX_ENABLED_FLAG (1u << 0)    //!< Receiver enable flag.
#define NRF_SERIAL_TX_ENABLED_FLAG (1u << 1)    //!< Transmitter enable flag.

/**
 * @brief Serial port context. Contains all data structures that need
 *        to be stored in RAM memory.
 * */
typedef struct {
    nrf_serial_config_t const * p_config;   //!< Serial port configuration.

    nrf_mtx_t write_lock;   //!< Write operation lock.
    nrf_mtx_t read_lock;    //!< Read operation lock.

    uint8_t flags;         //!< Transmitter/receiver enable flags.
} nrf_serial_ctx_t;

/**
 * @brief Serial port instance declaration.
 *
 * @note Use @ref NRF_SERIAL_UART_DEF macro to create an instance of this
 *       structure.
 * */
struct nrf_serial_s {
    nrf_drv_uart_t instance;   //!< Driver instance.
    nrf_serial_ctx_t * p_ctx;  //!< Driver context.

    app_timer_id_t const * p_tx_timer;  //!< TX timeout timer.
    app_timer_id_t const * p_rx_timer;  //!< RX timeout timer.
};

/**
 * @brief Creates an instance of a serial port.
 *
 * @param _name             Instance name.
 * @param _instance_number  Driver instance number (@ref NRF_DRV_UART_INSTANCE).
 * */
#define NRF_SERIAL_UART_DEF(_name, _instance_number)                        \
    APP_TIMER_DEF(_name##_rx_timer);                                        \
    APP_TIMER_DEF(_name##_tx_timer);                                        \
    static nrf_serial_ctx_t _name##_ctx;                                    \
    static const nrf_serial_t _name = {                                     \
        .instance = NRF_DRV_UART_INSTANCE(_instance_number),                \
        .p_ctx = &_name##_ctx,                                              \
        .p_tx_timer = &_name##_tx_timer,                                    \
        .p_rx_timer = &_name##_rx_timer,                                    \
    }


/**
 * @brief Maximum value of timeout. API might be blocked indefinitely if this value is
 *        not set.*/
#define NRF_SERIAL_MAX_TIMEOUT UINT32_MAX

/**
 * @brief Function for initializing a serial port. Serial port can be initialized
 *        in various modes that are defined by nrf_serial_mode_t.
 * - NRF_SERIAL_MODE_POLLING - Simple polling mode. API calls will be
 *                           synchronous. There is no need to define queues or buffers.
 *                           No events will be generated.
 * - NRF_SERIAL_MODE_IRQ - Interrupt mode. API can be set to work in synchronous or
 *                       asynchronous mode. Queues and buffers must be passed
 *                       during initialization. Events will be generated if
 *                       a non NULL handler is passed as the ev_handler parameter.
 * - NRF_SERIAL_MODE_DMA - Similar to @ref NRF_SERIAL_MODE_IRQ. Uses EasyDMA.
 *
 *
 * @param p_serial          Serial port instance.
 * @param p_drv_uart_config UART driver configuration. Cannot be NULL.
 * @param p_config          Serial port configuration. Cannot be NULL. This object must be created
 *							using the @ref NRF_SERIAL_CONFIG_DEF macro.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_serial_init(nrf_serial_t const * p_serial,
                           nrf_drv_uart_config_t const * p_drv_uart_config,
                           nrf_serial_config_t const * p_config);


/**
 * @brief Function for uninitializing a serial port.
 *
 * @param p_serial  Serial port instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_serial_uninit(nrf_serial_t const * p_serial);


/**
 * @brief Function for writing to a serial port.
 *
 * @param p_serial   Serial port instance.
 * @param p_data     Transmit buffer pointer.
 * @param size       Transmit buffer size.
 * @param p_written  Amount of data actually written to the serial port.
 *                   NULL pointer can be passed.
 * @param timeout_ms Operation timeout, in milliseconds. Pass 0 to operate in
 *                   non blocking mode.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_serial_write(nrf_serial_t const * p_serial,
                            void const * p_data,
                            size_t size,
                            size_t * p_written,
                            uint32_t timeout_ms);

/**
 * @brief Function for reading from a serial port.
 *
 * @param p_serial   Serial port instance.
 * @param p_data     Receive buffer pointer.
 * @param size       Receive buffer size.
 * @param p_read     Amount of data actually read from the serial port.
 *                   NULL pointer can be passed.
 * @param timeout_ms Operation timeout, in milliseconds. Pass 0 to operate in
 *                   non blocking mode.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_serial_read(nrf_serial_t const * p_serial,
                           void * p_data,
                           size_t size,
                           size_t * p_read,
                           uint32_t timeout_ms);

/**
 * @brief Function for flushing a serial port TX queue.
 *
 * @param p_serial   Serial port instance.
 * @param timeout_ms Operation timeout, in milliseconds. Pass 0 to operate in
 *                   non blocking mode.
 * @return Standard error code.
 * */
ret_code_t nrf_serial_flush(nrf_serial_t const * p_serial, uint32_t timeout_ms);


/**
 * @brief Function for aborting a serial port transmission.
 * Aborts the current ongoing transmission and resets TX FIFO.
 *
 * @param p_serial  Serial port instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_serial_tx_abort(nrf_serial_t const * p_serial);

/**
 * @brief Function for draining the serial port receive RX FIFO.
 * Drains HW FIFO and resets RX FIFO.
 *
 * @param p_serial  Serial port instance.
 *
 * @return Standard error code.
 * */
ret_code_t nrf_serial_rx_drain(nrf_serial_t const * p_serial);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_SERIAL_H__ */
