/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HOSAL_UART_H__
#define __HOSAL_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_uart UART
 *  HOSAL UART API
 *
 *  @{
 */

#include <stdio.h>
#include <stdint.h>
#include "hosal_dma.h"

#define HOSAL_UART_AUTOBAUD_0X55     1   /**< @brief UART auto baudrate detection using codeword 0x55 */
#define HOSAL_UART_AUTOBAUD_STARTBIT 2   /**< @brief UART auto baudrate detection using start bit */

#define HOSAL_UART_TX_CALLBACK       1   /**< @brief UART tx idle interrupt callback */
#define HOSAL_UART_RX_CALLBACK       2   /**< @brief UART rx complete callback */
#define HOSAL_UART_TX_DMA_CALLBACK   3   /**< @brief UART tx DMA trans complete callback */
#define HOSAL_UART_RX_DMA_CALLBACK   4   /**< @brief UART rx DMA trans complete callback */

#define HOSAL_UART_BAUD_SET          1   /**< @brief UART baud set */
#define HOSAL_UART_BAUD_GET          2   /**< @brief UART baud get */
#define HOSAL_UART_DATA_WIDTH_SET    3   /**< @brief UART data width set */
#define HOSAL_UART_DATA_WIDTH_GET    4   /**< @brief UART data width get */
#define HOSAL_UART_STOP_BITS_SET     5   /**< @brief UART stop bits set */
#define HOSAL_UART_STOP_BITS_GET     6   /**< @brief UART stop bits get */
#define HOSAL_UART_FLOWMODE_SET      7   /**< @brief UART flow mode set */
#define HOSAL_UART_FLOWSTAT_GET      8   /**< @brief UART flow state get */
#define HOSAL_UART_PARITY_SET        9   /**< @brief UART flow mode set */
#define HOSAL_UART_PARITY_GET       10   /**< @brief UART flow state get */
#define HOSAL_UART_MODE_SET         11   /**< @brief UART mode set */
#define HOSAL_UART_MODE_GET         12   /**< @brief UART mode get */
#define HOSAL_UART_FREE_TXFIFO_GET  13   /**< @brief UART free tx fifo get */
#define HOSAL_UART_FREE_RXFIFO_GET  14   /**< @brief UART free rx fifo get */
#define HOSAL_UART_FLUSH            15   /**< @brief Wait for the send to complete */
#define HOSAL_UART_TX_TRIGGER_ON    16   /**< @brief UART TX trigger on */
#define HOSAL_UART_TX_TRIGGER_OFF   17   /**< @brief UART TX trigger off */
#define HOSAL_UART_DMA_TX_START     18   /**< @brief UART DMA TX start trans */
#define HOSAL_UART_DMA_RX_START     19   /**< @brief UART DMA RX start trans */

/**
 * @brief hosal uart callback
 *
 * @param[in] p_arg  Set the custom parameters specified when the callback function is set
 *
 * @return
 *  - 0 : on success
 *  - EIO : if an error occurred with any step
 */
typedef int (*hosal_uart_callback_t)(void *p_arg);

/**
 * @brief UART data width
 */
typedef enum {
    HOSAL_DATA_WIDTH_5BIT,
    HOSAL_DATA_WIDTH_6BIT,
    HOSAL_DATA_WIDTH_7BIT,
    HOSAL_DATA_WIDTH_8BIT,
    HOSAL_DATA_WIDTH_9BIT
} hosal_uart_data_width_t;

/**
 * @brief UART stop bits
 */
typedef enum {
    HOSAL_STOP_BITS_1 = 1,
    HOSAL_STOP_BITS_2 = 3
} hosal_uart_stop_bits_t;

/**
 * @brief UART flow control
 */
typedef enum {
    HOSAL_FLOW_CONTROL_DISABLED,
    HOSAL_FLOW_CONTROL_RTS,
    HOSAL_FLOW_CONTROL_CTS,
    HOSAL_FLOW_CONTROL_CTS_RTS
} hosal_uart_flow_control_t;

/**
 * @brief UART parity
 */
typedef enum {
    HOSAL_NO_PARITY,
    HOSAL_ODD_PARITY,
    HOSAL_EVEN_PARITY
} hosal_uart_parity_t;

/**
 * @brief UART mode
 */
typedef enum {
    HOSAL_UART_MODE_POLL,            /**< @brief UART poll mode (default mode) */
    HOSAL_UART_MODE_INT_TX,          /**< @brief UART TX int mode */
    HOSAL_UART_MODE_INT_RX,          /**< @brief UART RX int mode */
    HOSAL_UART_MODE_INT,             /**< @brief UART TX and RX int mode */
} hosal_uart_mode_t;

/**
 * @brief UART DMA configuration
 */
typedef struct {
    /**
     * @brief UART DMA trans buffer
     * When the transmission is TX, the address is the src address
     * When the transmission is RX, the address is the dest address
     */
    uint8_t *dma_buf;

    uint32_t dma_buf_size; 	/**< @brief UART DMA trans buffer size */
} hosal_uart_dma_cfg_t;

/**
 * @brief UART configuration
 */
typedef struct {
    uint8_t                   uart_id;	/**< @brief UART id */
    uint8_t                   tx_pin;		/**< @brief UART tx pin */
    uint8_t                   rx_pin;		/**< @brief UART rx pin */
    uint8_t                   cts_pin;	/**< @brief UART cts pin */
    uint8_t                   rts_pin;	/**< @brief UART rts pin */
    uint32_t                  baud_rate;	/**< @brief UART baud rate */
    hosal_uart_data_width_t   data_width;	/**< @brief UART data width */
    hosal_uart_parity_t       parity;		/**< @brief UART parity bit */
    hosal_uart_stop_bits_t    stop_bits;	/**< @brief UART stop btis */
    hosal_uart_flow_control_t flow_control;	/**< @brief UART flow control */
    hosal_uart_mode_t         mode;		/**< @brief UART int or pull mode */
} hosal_uart_config_t;

/**
 * @brief UART device type
 */
typedef struct {
    uint8_t       port;			/**< @brief UART port */
    hosal_uart_config_t config;		/**< @brief UART config */
    hosal_uart_callback_t tx_cb;		/**< @brief UART tx callback */
    void *p_txarg;				/**< @brief UART tx callback arg */
    hosal_uart_callback_t rx_cb;		/**< @brief UART rx callback */
    void *p_rxarg;				/**< @brief UART rx callback arg */
    hosal_uart_callback_t txdma_cb;		/**< @brief UART tx dma callback */
    void *p_txdma_arg;				/**< @brief UART tx dma callback arg */
    hosal_uart_callback_t rxdma_cb;		/**< @brief UART rx dma callback */
    void *p_rxdma_arg;				/**< @brief UART rx dma callback arg */
    hosal_dma_chan_t dma_tx_chan;		/**< @brief UART dma tx channel */
    hosal_dma_chan_t dma_rx_chan;		/**< @brief UART dma rx channel */
    void         *priv;			/**< @brief UART private data */
} hosal_uart_dev_t;

/**
 * @brief define a UART default config
 *
 * @param[in] cfg  config define
 * @param[in] id  uart id
 * @param[in] tx  uart tx pin
 * @param[in] rx  uart rx pin
 * @param[in] baud  uart baud
 *
 */
#define HOSAL_UART_CFG_DECL(cfg, id, tx, rx, baud) \
    hosal_uart_config_t cfg =  {                   \
        .uart_id = id,                             \
        .tx_pin = tx,                              \
        .rx_pin = rx,                              \
        .cts_pin = 255,                            \
        .rts_pin = 255,                            \
        .baud_rate = baud,                         \
        .data_width = HOSAL_DATA_WIDTH_8BIT,       \
        .parity = HOSAL_NO_PARITY,                 \
        .stop_bits = HOSAL_STOP_BITS_1,            \
        .mode = HOSAL_UART_MODE_POLL,              \
    };

/**
 * @brief define a UART device
 *
 * @param[in] dev  uart device
 * @param[in] id  uart id
 * @param[in] tx  uart tx pin
 * @param[in] rx  uart rx pin
 * @param[in] baud  uart baud
 */
#define HOSAL_UART_DEV_DECL(dev, id, tx, rx, baud) \
    hosal_uart_dev_t dev = {                       \
        .config =  {                               \
            .uart_id = id,                         \
            .tx_pin = tx,                          \
            .rx_pin = rx,                          \
            .cts_pin = 255,                        \
            .rts_pin = 255,                        \
            .baud_rate = baud,                     \
            .data_width = HOSAL_DATA_WIDTH_8BIT,   \
            .parity = HOSAL_NO_PARITY,             \
            .stop_bits = HOSAL_STOP_BITS_1,        \
            .mode = HOSAL_UART_MODE_POLL,          \
        },                                         \
    };
/**
 * @brief Get auto baudrate on a UART interface
 *
 * @param[in]  uart    the UART interface
 * @param[in]  mode    auto baudrate detection mode(codeword 0x55 or start bit)
 *
 * @return  
 *	- = 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_abr_get(hosal_uart_dev_t *uart, uint8_t mode);

/**
 * @brief Initialises a UART interface
 *
 * @param[in]  uart  the interface which should be initialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_init(hosal_uart_dev_t *uart);

/**
 * @brief Poll transmit data on a UART interface
 *
 * @param[in]  uart     the UART interface
 * @param[in]  txbuf    pointer to the start of data
 * @param[in]  size     number of bytes to transmit
 *
 * @return  
 *	- > 0  on success
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_send(hosal_uart_dev_t *uart, const void *txbuf, uint32_t size);

/**
 * @brief Poll receive data on a UART interface
 *
 * @param[in]   uart         the UART interface
 * @param[out]  rxbuf        pointer to the buffer which will store incoming data
 * @param[in]   expect_size  expect number of bytes to receive
 *
 * @return  
 *	- > 0  number of bytes to receive
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_receive(hosal_uart_dev_t *uart, void *data, uint32_t expect_size);

/**
 * @brief hal uart ioctl
 *
 * @param[in] uart   the UART interface
 * @param[in] ctl  Control request
 *   - HOSAL_UART_BAUD_SET : baud set, p_arg is baud
 *   - HOSAL_UART_BAUD_GET : baud get, p_arg is baud's pointer
 *   - HOSAL_UART_DATA_WIDTH_SET : set data width，p_arg is hosal_uart_data_width_t
 *   - HOSAL_UART_DATA_WIDTH_GET : get data width，p_arg is hosal_uart_data_width_t's pointer
 *   - HOSAL_UART_STOP_BITS_SET : set stop bits, p_arg is hosal_uart_stop_bits_t
 *   - HOSAL_UART_STOP_BITS_GET : get stop bits, p_arg is hosal_uart_stop_bits_t's pointer
 *   - HOSAL_UART_PARITY_SET : set parity, p_arg is hosal_uart_parity_t
 *   - HOSAL_UART_PARITY_GET : get parity, p_arg is hosal_uart_parity_t's pointer
 *   - HOSAL_UART_MODE_SET : UART mode set, p_arg is hosal_uart_mode_t
 *   - HOSAL_UART_MODE_GET : UART mode get, p_arg is hosal_uart_mode_t's pointer
 *   - HOSAL_UART_FLOWMODE_SET : UART flow mode set, p_arg is hosal_uart_flow_control_t
 *   - HOSAL_UART_FLOWSTAT_GET : UART flow state get, p_arg is hosal_uart_flow_control_t's pointer
 *   - HOSAL_UART_FREE_TXFIFO_GET : get uart free tx fifo size (bytes)
 *   - HOSAL_UART_FREE_RXFIFO_GET : get uart free rx fifo size (bytes)
 *   - HOSAL_UART_FLUSH : Wait for the send to complete
 *   - HOSAL_UART_TX_TRIGGER_ON : UART TX trigger on
 *   - HOSAL_UART_TX_TRIGGER_OFF : UART TX trigger off
 *   - HOSAL_UART_DMA_CONFIG : p_arg is hosal_uart_dma_cfg_t's pointer
 *   - HOSAL_UART_DMA_TX_START : UART DMA TX start trans p_arg is hosal_uart_dma_cfg_t's pointer
 *   - HOSAL_UART_DMA_RX_START : UART DMA RX start trans p_arg is hosal_uart_dma_cfg_t's pointer
 *
 * @param[in,out] p_arg  parameter
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_ioctl (hosal_uart_dev_t *uart, int ctl, void *p_arg);

/**
 * @brief hal uart callback set
 *
 * @param[in]  uart     the UART interface
 * @param[in] callback_type   callback type
 *            - HOSAL_UART_TX_CALLBACK
 *            - HOSAL_UART_RX_CALLBACK
 *            - HOSAL_UART_TX_DMA_CALLBACK
 *            - HOSAL_UART_RX_DMA_CALLBACK
 * @param[in] pfn_callback  callback function
 * @param[in] arg  callback function parameter
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_callback_set (hosal_uart_dev_t *uart,
                           int callback_type,
                           hosal_uart_callback_t pfn_callback,
                           void *arg);

/**
 * @brief Deinitialises a UART interface
 *
 * @param[in]  uart  the interface which should be deinitialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_uart_finalize(hosal_uart_dev_t *uart);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_UART_H__ */

/* end of file */
