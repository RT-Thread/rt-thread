/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef HAL_UART_H_INCLUDED
#define HAL_UART_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

/** @file
 * This file contains declarations of the routines, types and macros to implement the UART protocol.
 *
 * @defgroup hal_uart HAL UART protocol
 * @{
 * @brief Module to declare HAL UART protocol
 */

/** @brief Maximum size in bytes of input and output buffers. */
#define MAX_QUEUE_LENGTH         0xffffu

/** @brief Maximum size in bytes of data can be stored in hardware unit output buffer. */
#define MAX_TX_CHUNK_SIZE        UCHAR_MAX

/** @brief UART baudrate. */
typedef enum
{
    HAL_UART_BAUDRATE_38400,           /**< 38400 bits per second.*/
    HAL_UART_BAUDRATE_115200,          /**< 115200 bits per second.*/
    HAL_UART_BAUDRATE_230400           /**< 230400 bits per second.*/
} hal_uart_baudrate_t;

/** @brief UART parity check. */
typedef enum
{
    HAL_UART_PARITY_NONE,              /**< Do not check parity.*/
    HAL_UART_PARITY_EVEN               /**< Check even parity.*/
} hal_uart_parity_t;

/** @brief UART flow control. */
typedef enum
{
    HAL_UART_FLOW_CONTROL_DISABLED,    /**< Flow control is disabled.*/
    HAL_UART_FLOW_CONTROL_ENABLED,     /**< Flow control is enabled.*/
} hal_uart_flow_control_t;

/** @brief UART character size settings. */
typedef enum
{
    HAL_UART_FIVE_BITS_CHAR = 5,       /**< 5 bits character.*/
    HAL_UART_SIX_BITS_CHAR,            /**< 6 bits character.*/
    HAL_UART_SEVEN_BITS_CHAR,          /**< 7 bits character.*/
    HAL_UART_EIGHT_BITS_CHAR,          /**< 8 bits character.*/
} hal_uart_char_size_t;

/** @brief UART stop bits settings. */
typedef enum
{
    HAL_UART_ONE_STOP_BIT,             /**< 1 stop bit.*/
    HAL_UART_ONEHALF_STOP_BITS,        /**< 1.5 stop bits.*/
    HAL_UART_TWO_STOP_BITS,            /**< 2 stop bits.*/
} hal_uart_stop_bits_t;

/** @brief Represents error source for the UART driver. There might be other values,
 * representing clearer elaborating of error statuses, if this module is used
 * with Windows or Linux.
 */
typedef enum
{
    HAL_UART_ERROR_NONE = 0,           /**< Success.*/
    HAL_UART_ERROR_TX_OVERFLOW = 252,  /**< This error happens when amount of elements in
                                            the transmitter ring buffer exceeds its size.
                                            All the data above limit is not placed into
                                            buffer.*/
    HAL_UART_ERROR_RX_OVERFLOW = 253,  /**< This error happens when amount of elements in
                                            the receiver ring buffer exceeds its size.
                                            All the unread data is overwritten with new
                                            received data.*/
    HAL_UART_ERROR_RX_UNDERFLOW = 254, /**< This error happens when the user-side software
                                            tries to read more elements than it is available
                                            in the receive buffer.
                                            The user-side buffer will be filled with all available
                                            characters and then the error handler is started.*/
    HAL_UART_ERROR_HW_ERROR = 255,     /**< There is some unrecoverable error in hardware.*/
} hal_uart_error_t;

/**
 * @brief User-side handler of UART read and write events.
 *
 * @param[in] channel event channel number.
 * @param[in] char_count number of characters successfully sent before entering
 *                   the callback function.
 */
typedef void (*hal_uart_handler_t)(uint32_t channel, size_t char_count);

/**
 * @brief User-side handler for UART error events.
 *
 * @param[in] channel event channel number.
 * @param[in] error_id call reason.
 */
typedef void (*hal_uart_error_handler_t)(uint32_t channel, hal_uart_error_t error_id);

/** @brief HAL UART configuration structure.
 */
typedef struct
{
    uint32_t                   module;        /**< UART module number. By now zero
                                                   is the only option.*/
    uint32_t                   tx_pin;        /**< Number of pin used as TX.*/
    uint32_t                   rx_pin;        /**< Number of pin used as RX.*/
    uint32_t                   cts_pin;       /**< Number of pin used as CTS.*/
    uint32_t                   rts_pin;       /**< Number of pin used as RTS.*/
    hal_uart_baudrate_t        baudrate;      /**< Baudrate selector.*/
    hal_uart_parity_t          parity;        /**< Parity selector.*/
    hal_uart_flow_control_t    flow_control;  /**< Flow control selector.*/
    hal_uart_char_size_t       char_size;     /**< Size of char in bits.*/
    hal_uart_stop_bits_t       stop_bits;     /**< Stop bits number.*/
} hal_uart_config_t;

/**
 * @brief This structure defines the UART module operation.
 *
 * If \a write_buffer_ptr is defined as NULL, then sending data will work
 * in blocking way, that is call for \a hal_uart_write will be completed
 * only after sending of the last byte passed as input parameter.
 *
 * If \a read_buffer_ptr is defined as NULL, then driver will drop every
 * received byte.
 */
typedef struct
{
    hal_uart_config_t          uart_config;       /**< UART settings struct.*/
    hal_uart_handler_t         write_handler;     /**< Callback function for write operation.*/
    void                     * write_buffer_ptr;  /**< User-side buffer for write operation.*/
    size_t                     write_buffer_size; /**< Size of write operation buffer.*/
    hal_uart_handler_t         read_handler;      /**< Callback function for read operation.*/
    void                     * read_buffer_ptr;   /**< User-side buffer for read operation.*/
    size_t                     read_buffer_size;  /**< Size of read operation buffer.*/
    hal_uart_error_handler_t   error_handler;     /**< Callback function in case of something
                                                       goes wrong.*/
} hal_uart_descriptor_t;

/**
 * @brief Configures UART interface using input parameter.
 *
 * @param[in] config pointer to a config struct.
 * @param[in] descriptor pointer to a descriptor struct.
 *
 * @return Return status of operation.
 */
hal_uart_error_t hal_uart_open(const hal_uart_config_t * config,
                               const hal_uart_descriptor_t * descriptor);

/**
 * @brief Sends data in a non-blocking way.
 *
 * @param[in] descriptor pointer to the UART module operation structure.
 * @param[in] data pointer to the user-side buffer of output data.
 * @param[in] length number of bytes to transmit.
 *
 * If descriptor has a non-null \a write_buffer_ptr then this function will use it
 * as a temporary buffer and will copy input \a data to it before starting
 * transmit. If descriptor has the NULL \a write_buffer_ptr, then the user-side code
 * is responsible to retain \a data until \a write_handler is called.
 */
void hal_uart_write(const hal_uart_descriptor_t * descriptor,
                    const uint8_t * data,
                    const size_t length);

/**
 * @brief Sends a null-terminated C-string in a non-blocking way.
 *
 * @param[in] descriptor pointer to the UART module operation structure.
 * @param[in] s null-terminated string to send.
 */
void hal_uart_puts(const hal_uart_descriptor_t * descriptor, const char * s);

/**
 * @brief Receives data in a non-blocking way.
 *
 * @param[in] descriptor pointer to the UART module operation structure.
 * @param[out] data pointer to the user-side buffer used to receive data.
 * @param[in] length number of bytes to receive.
 *
 * If descriptor has a non-null \a read_buffer_ptr, then this function is used to
 * copy input characters from it to \a data.
 * If \a read_buffer_ptr is NULL, then this function ignores all inputs.
 */
void hal_uart_read(const hal_uart_descriptor_t * descriptor,
                   uint8_t * data,
                   const size_t length);

/**
 * @brief Returns number of bytes available to read from the income buffer of the
 * driver.
 *
 * @param[in] descriptor pointer to driver structure.
 *
 * @return Number of bytes available to read.
 */
size_t hal_uart_read_buffer_size_get(const hal_uart_descriptor_t * descriptor);

/**
 * @brief Returns number of bytes available to write to the outgoing buffer of the
 * driver.
 *
 * @param[in] descriptor pointer to driver structure.
 *
 * @return Number of bytes available to write.
 */
size_t hal_uart_write_buffer_size_get(const hal_uart_descriptor_t * descriptor);

/**
 * @brief This function deallocates resources previously allocated by hal_uart_open.
 *
 * @param[in] descriptor pointer to driver structure.
 *
 * @return Return status of operation.
 */
hal_uart_error_t hal_uart_close(const hal_uart_descriptor_t * descriptor);


#if defined(CONFIG_TRACE) && defined(CONFIG_DEBUG)

/**
 * @brief Finalizes remaining trace data output to UART.
 *
 * @details This debugging feature is needed to finalize buffered trace output
 *          to UART before commencing non-buffered assertion output.
 */
void hal_uart_trace_finalize(void);

#endif

/** @} */

#endif /* HAL_UART_H_INCLUDED */
