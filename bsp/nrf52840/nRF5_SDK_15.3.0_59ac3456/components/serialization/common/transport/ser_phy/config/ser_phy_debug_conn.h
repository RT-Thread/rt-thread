/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#ifndef SER_PHY_DEBUG_CONN_H__
#define SER_PHY_DEBUG_CONN_H__

#ifndef SER_PHY_DEBUG_CONN_ENABLE

#define DEBUG_EVT_SPI_SLAVE_RAW_RX_XFER_DONE(data);

#define DEBUG_EVT_SPI_SLAVE_RAW_TX_XFER_DONE(data);

#define DEBUG_EVT_SPI_SLAVE_RAW_BUFFERS_SET(data);

#define DEBUG_EVT_SPI_SLAVE_RAW_REQ_SET(data);

#define DEBUG_EVT_SPI_SLAVE_RAW_REQ_CLEARED(data);

#define DEBUG_EVT_SPI_SLAVE_PHY_BUF_REQUEST(data);

#define DEBUG_EVT_SPI_SLAVE_PHY_PKT_RECEIVED(data);

#define DEBUG_EVT_SPI_SLAVE_PHY_PKT_DROPPED(data);

#define DEBUG_EVT_SPI_SLAVE_PHY_PKT_SENT(data);

#else

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// low level hardware event types
typedef enum
{
    SPI_SLAVE_RAW_BUFFERS_SET,
    SPI_SLAVE_RAW_RX_XFER_DONE,
    SPI_SLAVE_RAW_TX_XFER_DONE,
    SPI_SLAVE_RAW_REQ_SET,
    SPI_SLAVE_RAW_REQ_CLEARED,
    SPI_SLAVE_PHY_BUF_REQUEST,
    SPI_SLAVE_PHY_PKT_SENT,
    SPI_SLAVE_PHY_PKT_RECEIVED,
    SPI_SLAVE_PHY_PKT_DROPPED,
    SPI_SLAVE_RAW_EVT_TYPE_MAX
} spi_slave_raw_evt_type_t;

// low level hardware event definition
typedef struct
{
    spi_slave_raw_evt_type_t  evt_type;
    uint32_t                  data;
} spi_slave_raw_evt_t;

typedef void (*spi_slave_raw_callback_t)(spi_slave_raw_evt_t event);

void debug_init(spi_slave_raw_callback_t spi_slave_raw_evt_callback);

void debug_evt(spi_slave_raw_evt_type_t evt_type, uint32_t data);

#define DEBUG_EVT(evt, data)    \
do {                            \
    debug_evt(evt, data);       \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_RAW_RX_XFER_DONE(data)  \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_RAW_RX_XFER_DONE, data);    \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_RAW_TX_XFER_DONE(data)  \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_RAW_TX_XFER_DONE, data);    \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_RAW_BUFFERS_SET(data)   \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_RAW_BUFFERS_SET, data);     \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_RAW_REQ_SET(data)       \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_RAW_REQ_SET, data);         \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_RAW_REQ_CLEARED(data)   \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_RAW_REQ_CLEARED, data);     \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_PHY_BUF_REQUEST(data)   \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_PHY_BUF_REQUEST, data);     \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_PHY_PKT_RECEIVED(data)  \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_PHY_PKT_RECEIVED, data);    \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_PHY_PKT_DROPPED(data)   \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_PHY_PKT_DROPPED, data);     \
} while (0);


#define DEBUG_EVT_SPI_SLAVE_PHY_PKT_SENT(data)      \
do {                                                \
    DEBUG_EVT(SPI_SLAVE_PHY_PKT_SENT, data);        \
} while (0);


#endif


#ifdef __cplusplus
}
#endif

#endif //SER_PHY_DEBUG_CONN_H__
