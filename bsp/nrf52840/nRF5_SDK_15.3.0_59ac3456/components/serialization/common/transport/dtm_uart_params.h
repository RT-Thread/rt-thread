/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
#ifndef DTM_UART_PARAMS_H__
#define DTM_UART_PARAMS_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup ble_dtm_app
 */


/**@brief Enumeration of supported baud rates. */
typedef enum
{
    UART_BAUD_RATE_1200,     /**< Baud rate 1200. */
    UART_BAUD_RATE_2400,     /**< Baud rate 2400. */
    UART_BAUD_RATE_4800,     /**< Baud rate 4800. */
    UART_BAUD_RATE_9600,     /**< Baud rate 9600. */
    UART_BAUD_RATE_14400,    /**< Baud rate 14400. */
    UART_BAUD_RATE_19200,    /**< Baud rate 19200. */
    UART_BAUD_RATE_28800,    /**< Baud rate 28800. */
    UART_BAUD_RATE_38400,    /**< Baud rate 38400. */
    UART_BAUD_RATE_57600,    /**< Baud rate 57600. */
    UART_BAUD_RATE_76800,    /**< Baud rate 76800. */
    UART_BAUD_RATE_115200,   /**< Baud rate 115200. */
    UART_BAUD_RATE_230400,   /**< Baud rate 230400. */
    UART_BAUD_RATE_250000,   /**< Baud rate 250000. */
    UART_BAUD_RATE_460800,   /**< Baud rate 460800. */
    UART_BAUD_RATE_921600,   /**< Baud rate 921600. */
    UART_BAUD_RATE_1000000,  /**< Baud rate 1000000. */
    UART_BAUD_RATE_MAX       /**< Enumeration upper bound. */
} app_uart_stream_baud_rate_t;

/**@brief UART communication structure holding configuration settings for the peripheral.
 */
typedef struct
{
    uint8_t                     rx_pin_no;      /**< RX pin number. */
    uint8_t                     tx_pin_no;      /**< TX pin number. */
    uint8_t                     rts_pin_no;     /**< RTS pin number, only used if flow control is enabled. */
    uint8_t                     cts_pin_no;     /**< CTS pin number, only used if flow control is enabled. */
    bool                        use_parity;     /**< Even parity if TRUE, no parity if FALSE. */
    app_uart_stream_baud_rate_t baud_rate;      /**< Baud rate configuration. */
} app_uart_stream_comm_params_t;


#ifdef __cplusplus
}
#endif

#endif // DTM_UART_PARAMS_H__
