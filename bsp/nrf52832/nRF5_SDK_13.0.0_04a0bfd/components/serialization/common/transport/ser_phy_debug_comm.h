/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#ifndef SER_PHY_DEBUG_COMM_H__
#define SER_PHY_DEBUG_COMM_H__

#ifndef SER_PHY_HCI_DEBUG_ENABLE

// empty definitions here
#define DEBUG_EVT_HCI_PHY_EVT_TX_PKT_SENT(data)
#define DEBUG_EVT_HCI_PHY_EVT_BUF_REQUEST(data)
#define DEBUG_EVT_HCI_PHY_EVT_RX_PKT_RECEIVED(data)
#define DEBUG_EVT_HCI_PHY_EVT_RX_PKT_DROPPED(data)
#define DEBUG_EVT_HCI_PHY_EVT_TX_ERROR(data)
#define DEBUG_EVT_SLIP_PACKET_TX(data)
#define DEBUG_EVT_SLIP_ACK_TX(data)
#define DEBUG_EVT_SLIP_PACKET_TXED(data)
#define DEBUG_EVT_SLIP_ACK_TXED(data)
#define DEBUG_EVT_SLIP_PACKET_RXED(data)
#define DEBUG_EVT_SLIP_ACK_RXED(data)
#define DEBUG_EVT_SLIP_ERR_RXED(data)
#define DEBUG_EVT_TIMEOUT(data)
#define DEBUG_HCI_RETX(data)
#define DEBUG_EVT_MAIN_BUSY(data)
#define DEBUG_EVT_TX_REQ(data)

#else
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//Low level hardware events
typedef enum
{
    HCI_PHY_EVT_TX_PKT_SENT,
    HCI_PHY_EVT_BUF_REQUEST,
    HCI_PHY_EVT_RX_PKT_RECEIVED,
    HCI_PHY_EVT_RX_PKT_DROPPED,
    HCI_PHY_EVT_TX_ERROR,
    HCI_SLIP_EVT_PACKET_TX,
    HCI_SLIP_EVT_ACK_TX,
    HCI_SLIP_EVT_PACKET_TXED,
    HCI_SLIP_EVT_ACK_TXED,
    HCI_SLIP_EVT_PACKET_RXED,
    HCI_SLIP_EVT_ACK_RXED,
    HCI_SLIP_EVT_ERR_RXED,
    HCI_TIMER_EVT_TIMEOUT,
    HCI_RETX,
    HCI_MAIN_BUSY,
    HCI_TX_REQ,
    HCI_PHY_EVT_MAX
} hci_dbg_evt_type_t;


//Low level hardware event definition
typedef struct
{
    hci_dbg_evt_type_t   evt;
    uint32_t              data;
} hci_dbg_evt_t;

typedef void (*hci_dbg_event_handler_t)(hci_dbg_evt_t event);

void debug_init(hci_dbg_event_handler_t evt_callback);

void debug_evt(hci_dbg_evt_type_t evt, uint32_t data);


#define DEBUG_EVT(event_type, data)    \
do {                            \
    debug_evt(event_type, data);       \
} while (0);


#define DEBUG_EVT_HCI_PHY_EVT_TX_PKT_SENT(data)      \
do {                                                 \
    DEBUG_EVT(HCI_PHY_EVT_TX_PKT_SENT, data);        \
} while (0);


#define DEBUG_EVT_HCI_PHY_EVT_BUF_REQUEST(data)       \
do {                                                  \
    DEBUG_EVT(HCI_PHY_EVT_BUF_REQUEST, data);         \
} while (0);


#define DEBUG_EVT_HCI_PHY_EVT_RX_PKT_RECEIVED(data)   \
do {                                                  \
    DEBUG_EVT(HCI_PHY_EVT_RX_PKT_RECEIVED, data);     \
} while (0);


#define DEBUG_EVT_HCI_PHY_EVT_RX_PKT_DROPPED(data)    \
do {                                                  \
    DEBUG_EVT(HCI_PHY_EVT_RX_PKT_DROPPED, data);      \
} while (0);

#define DEBUG_EVT_HCI_PHY_EVT_TX_ERROR(data)          \
do {                                                  \
    DEBUG_EVT(HCI_PHY_EVT_TX_ERROR, data);            \
} while (0);

#define DEBUG_EVT_SLIP_PACKET_TX(data)                \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_PACKET_TX, data);          \
} while (0);

#define DEBUG_EVT_SLIP_ACK_TX(data)                   \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_ACK_TX, data);             \
} while (0);

#define DEBUG_EVT_SLIP_PACKET_TXED(data)              \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_PACKET_TXED, data);        \
} while (0);

#define DEBUG_EVT_SLIP_ACK_TXED(data)                 \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_ACK_TXED, data);           \
} while (0);

#define DEBUG_EVT_SLIP_PACKET_RXED(data)              \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_PACKET_RXED, data);        \
} while (0);

#define DEBUG_EVT_SLIP_ACK_RXED(data)                 \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_ACK_RXED, data);           \
} while (0);

#define DEBUG_EVT_SLIP_ERR_RXED(data)                 \
do {                                                  \
    DEBUG_EVT(HCI_SLIP_EVT_ERR_RXED, data);           \
} while (0);

#define DEBUG_EVT_TIMEOUT(data)                       \
do {                                                  \
    DEBUG_EVT(HCI_TIMER_EVT_TIMEOUT, data);           \
} while (0);

#define DEBUG_HCI_RETX(data)                          \
do {                                                  \
    DEBUG_EVT(HCI_RETX, data);                        \
} while (0);

#define DEBUG_EVT_MAIN_BUSY(data)                     \
do {                                                  \
    DEBUG_EVT(HCI_MAIN_BUSY, data);                   \
} while (0);

#define DEBUG_EVT_TX_REQ(data)                        \
do {                                                  \
    DEBUG_EVT(HCI_TX_REQ, data);                      \
} while (0);

#endif  // SER_PHY_HCI_DEBUG_ENABLE


#ifdef __cplusplus
}
#endif

#endif  // SER_PHY_DEBUG_COMM_H__
