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

#include "nrf_error.h"
#include "nrf_esb.h"
#include "nrf_esb_error_codes.h"
#include "nrf_gpio.h"
#include <string.h>
#include <stddef.h>
#include "sdk_common.h"
#include "sdk_macros.h"
#include "app_util.h"
#include "nrf_log.h"

#define BIT_MASK_UINT_8(x) (0xFF >> (8 - (x)))
#define NRF_ESB_PIPE_COUNT 9

// Constant parameters
#define RX_WAIT_FOR_ACK_TIMEOUT_US_2MBPS        (48)        /**< 2 Mb RX wait for acknowledgment time-out value. Smallest reliable value - 43. */
#define RX_WAIT_FOR_ACK_TIMEOUT_US_1MBPS        (64)        /**< 1 Mb RX wait for acknowledgment time-out value. Smallest reliable value - 59. */
#define RX_WAIT_FOR_ACK_TIMEOUT_US_250KBPS      (250)       /**< 250 Kb RX wait for acknowledgment time-out value. */
#define RX_WAIT_FOR_ACK_TIMEOUT_US_1MBPS_BLE    (64)        /**< 1 Mb RX wait for acknowledgment time-out (combined with BLE). */

// Interrupt flags
#define     NRF_ESB_INT_TX_SUCCESS_MSK          0x01        /**< Interrupt mask value for TX success. */
#define     NRF_ESB_INT_TX_FAILED_MSK           0x02        /**< Interrupt mask value for TX failure. */
#define     NRF_ESB_INT_RX_DATA_RECEIVED_MSK    0x04        /**< Interrupt mask value for RX_DR. */

#define     NRF_ESB_PID_RESET_VALUE             0xFF        /**< Invalid PID value which is guaranteed to not collide with any valid PID value. */
#define     NRF_ESB_PID_MAX                     3           /**< Maximum value for PID. */
#define     NRF_ESB_CRC_RESET_VALUE             0xFFFF      /**< CRC reset value. */

// Internal Enhanced ShockBurst module state.
typedef enum {
    NRF_ESB_STATE_IDLE,                                     /**< Module idle. */
    NRF_ESB_STATE_PTX_TX,                                   /**< Module transmitting without acknowledgment. */
    NRF_ESB_STATE_PTX_TX_ACK,                               /**< Module transmitting with acknowledgment. */
    NRF_ESB_STATE_PTX_RX_ACK,                               /**< Module transmitting with acknowledgment and reception of payload with the acknowledgment response. */
    NRF_ESB_STATE_PRX,                                      /**< Module receiving packets without acknowledgment. */
    NRF_ESB_STATE_PRX_SEND_ACK,                             /**< Module transmitting acknowledgment in RX mode. */
} nrf_esb_mainstate_t;


#define DISABLE_RF_IRQ()      NVIC_DisableIRQ(RADIO_IRQn)
#define ENABLE_RF_IRQ()       NVIC_EnableIRQ(RADIO_IRQn)

#define RADIO_SHORTS_COMMON ( RADIO_SHORTS_READY_START_Msk | RADIO_SHORTS_END_DISABLE_Msk | \
            RADIO_SHORTS_ADDRESS_RSSISTART_Msk | RADIO_SHORTS_DISABLED_RSSISTOP_Msk )

#define VERIFY_PAYLOAD_LENGTH(p)                            \
do                                                          \
{                                                           \
    if (p->length == 0 ||                                    \
       p->length > NRF_ESB_MAX_PAYLOAD_LENGTH ||            \
       (m_config_local.protocol == NRF_ESB_PROTOCOL_ESB &&  \
        p->length > m_config_local.payload_length))         \
    {                                                       \
        return NRF_ERROR_INVALID_LENGTH;                    \
    }                                                       \
}while (0)


/* @brief Structure holding pipe info PID and CRC and acknowledgment payload. */
typedef struct
{
    uint16_t    crc;                                      /**< CRC value of the last received packet (Used to detect retransmits). */
    uint8_t     pid;                                      /**< Packet ID of the last received packet (Used to detect retransmits). */
    bool        ack_payload;                              /**< Flag indicating the state of the transmission of acknowledgment payloads. */
} pipe_info_t;


/* @brief  First-in, first-out queue of payloads to be transmitted. */
typedef struct
{
    nrf_esb_payload_t * p_payload[NRF_ESB_TX_FIFO_SIZE];  /**< Pointer to the actual queue. */
    uint32_t            entry_point;                      /**< Current start of queue. */
    uint32_t            exit_point;                       /**< Current end of queue. */
    uint32_t            count;                            /**< Current number of elements in the queue. */
} nrf_esb_payload_tx_fifo_t;


/* @brief First-in, first-out queue of received payloads. */
typedef struct
{
    nrf_esb_payload_t * p_payload[NRF_ESB_RX_FIFO_SIZE];  /**< Pointer to the actual queue. */
    uint32_t            entry_point;                      /**< Current start of queue. */
    uint32_t            exit_point;                       /**< Current end of queue. */
    uint32_t            count;                            /**< Current number of elements in the queue. */
} nrf_esb_payload_rx_fifo_t;


/**@brief Enhanced ShockBurst address.
 *
 * Enhanced ShockBurst addresses consist of a base address and a prefix
 *          that is unique for each pipe. See @ref esb_addressing in the ESB user
 *          guide for more information.
*/
typedef struct
{
    uint8_t base_addr_p0[4];        /**< Base address for pipe 0 encoded in big endian. */
    uint8_t base_addr_p1[4];        /**< Base address for pipe 1-7 encoded in big endian. */
    uint8_t pipe_prefixes[8];       /**< Address prefix for pipe 0 to 7. */
    uint8_t num_pipes;              /**< Number of pipes available. */
    uint8_t addr_length;            /**< Length of the address including the prefix. */
    uint8_t rx_pipes_enabled;       /**< Bitfield for enabled pipes. */
    uint8_t rf_channel;             /**< Channel to use (must be between 0 and 100). */
} nrf_esb_address_t;


// Module state
static bool                         m_esb_initialized           = false;
static nrf_esb_mainstate_t          m_nrf_esb_mainstate         = NRF_ESB_STATE_IDLE;
static nrf_esb_payload_t          * mp_current_payload;

static nrf_esb_event_handler_t      m_event_handler;

// Address parameters
static nrf_esb_address_t            m_esb_addr = NRF_ESB_ADDR_DEFAULT;

// RF parameters
static nrf_esb_config_t             m_config_local;

// TX FIFO
static nrf_esb_payload_t            m_tx_fifo_payload[NRF_ESB_TX_FIFO_SIZE];
static nrf_esb_payload_tx_fifo_t    m_tx_fifo;

// RX FIFO
static nrf_esb_payload_t            m_rx_fifo_payload[NRF_ESB_RX_FIFO_SIZE];
static nrf_esb_payload_rx_fifo_t    m_rx_fifo;

// Payload buffers
static  uint8_t                     m_tx_payload_buffer[NRF_ESB_MAX_PAYLOAD_LENGTH + 2];
static  uint8_t                     m_rx_payload_buffer[NRF_ESB_MAX_PAYLOAD_LENGTH + 2];

// Run time variables
static volatile uint32_t            m_interrupt_flags = 0;
static uint8_t                      m_pids[NRF_ESB_PIPE_COUNT];
static pipe_info_t                  m_rx_pipe_info[NRF_ESB_PIPE_COUNT];
static volatile uint32_t            m_retransmits_remaining;
static volatile uint32_t            m_last_tx_attempts;
static volatile uint32_t            m_wait_for_ack_timeout_us;

// These function pointers are changed dynamically, depending on protocol configuration and state.
static void (*on_radio_disabled)(void) = 0;
static void (*on_radio_end)(void) = 0;
static void (*update_rf_payload_format)(uint32_t payload_length) = 0;


// The following functions are assigned to the function pointers above.
static void on_radio_disabled_tx_noack(void);
static void on_radio_disabled_tx(void);
static void on_radio_disabled_tx_wait_for_ack(void);
static void on_radio_disabled_rx(void);
static void on_radio_disabled_rx_ack(void);


#define NRF_ESB_ADDR_UPDATE_MASK_BASE0          (1 << 0)    /*< Mask value to signal updating BASE0 radio address. */
#define NRF_ESB_ADDR_UPDATE_MASK_BASE1          (1 << 1)    /*< Mask value to signal updating BASE1 radio address. */
#define NRF_ESB_ADDR_UPDATE_MASK_PREFIX         (1 << 2)    /*< Mask value to signal updating radio prefixes. */


// Function to do bytewise bit-swap on an unsigned 32-bit value
static uint32_t bytewise_bit_swap(uint8_t const * p_inp)
{
    uint32_t inp = (*(uint32_t*)p_inp);
#if __CORTEX_M == (0x04U)
    return __REV((uint32_t)__RBIT(inp)); //lint -esym(628, __rev) -esym(526, __rev) -esym(628, __rbit) -esym(526, __rbit) */
#else
    inp = (inp & 0xF0F0F0F0) >> 4 | (inp & 0x0F0F0F0F) << 4;
    inp = (inp & 0xCCCCCCCC) >> 2 | (inp & 0x33333333) << 2;
    inp = (inp & 0xAAAAAAAA) >> 1 | (inp & 0x55555555) << 1;
    return inp;
#endif
}


// Internal function to convert base addresses from nRF24L type addressing to nRF51 type addressing
static uint32_t addr_conv(uint8_t const* p_addr)
{
    return __REV(bytewise_bit_swap(p_addr)); //lint -esym(628, __rev) -esym(526, __rev) */
}


static void update_rf_payload_format_esb_dpl(uint32_t payload_length)
{
#if (NRF_ESB_MAX_PAYLOAD_LENGTH <= 32)
    // Using 6 bits for length
    NRF_RADIO->PCNF0 = (0 << RADIO_PCNF0_S0LEN_Pos) |
                       (6 << RADIO_PCNF0_LFLEN_Pos) |
                       (3 << RADIO_PCNF0_S1LEN_Pos) ;
#else
    // Using 8 bits for length
    NRF_RADIO->PCNF0 = (0 << RADIO_PCNF0_S0LEN_Pos) |
                       (8 << RADIO_PCNF0_LFLEN_Pos) |
                       (3 << RADIO_PCNF0_S1LEN_Pos) ;
#endif
    NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Disabled    << RADIO_PCNF1_WHITEEN_Pos) |
                       (RADIO_PCNF1_ENDIAN_Big          << RADIO_PCNF1_ENDIAN_Pos)  |
                       ((m_esb_addr.addr_length - 1)    << RADIO_PCNF1_BALEN_Pos)   |
                       (0                               << RADIO_PCNF1_STATLEN_Pos) |
                       (NRF_ESB_MAX_PAYLOAD_LENGTH      << RADIO_PCNF1_MAXLEN_Pos);
}


static void update_rf_payload_format_esb(uint32_t payload_length)
{
    NRF_RADIO->PCNF0 = (1 << RADIO_PCNF0_S0LEN_Pos) |
                       (0 << RADIO_PCNF0_LFLEN_Pos) |
                       (1 << RADIO_PCNF0_S1LEN_Pos);

    NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Disabled    << RADIO_PCNF1_WHITEEN_Pos) |
                       (RADIO_PCNF1_ENDIAN_Big          << RADIO_PCNF1_ENDIAN_Pos)  |
                       ((m_esb_addr.addr_length - 1)    << RADIO_PCNF1_BALEN_Pos)   |
                       (payload_length                  << RADIO_PCNF1_STATLEN_Pos) |
                       (payload_length                  << RADIO_PCNF1_MAXLEN_Pos);
}


static void update_radio_addresses(uint8_t update_mask)
{
    if ((update_mask & NRF_ESB_ADDR_UPDATE_MASK_BASE0) != 0)
    {
        NRF_RADIO->BASE0 = addr_conv(m_esb_addr.base_addr_p0);
    }

    if ((update_mask & NRF_ESB_ADDR_UPDATE_MASK_BASE1) != 0)
    {
        NRF_RADIO->BASE1 = addr_conv(m_esb_addr.base_addr_p1);
    }

    if ((update_mask & NRF_ESB_ADDR_UPDATE_MASK_PREFIX) != 0)
    {
        NRF_RADIO->PREFIX0 = bytewise_bit_swap(&m_esb_addr.pipe_prefixes[0]);
        NRF_RADIO->PREFIX1 = bytewise_bit_swap(&m_esb_addr.pipe_prefixes[4]);
    }
}


static void update_radio_tx_power()
{
    NRF_RADIO->TXPOWER = m_config_local.tx_output_power << RADIO_TXPOWER_TXPOWER_Pos;
}


static void update_radio_bitrate()
{
    NRF_RADIO->MODE = m_config_local.bitrate << RADIO_MODE_MODE_Pos;

    switch (m_config_local.bitrate)
    {
        case NRF_ESB_BITRATE_2MBPS:
            m_wait_for_ack_timeout_us = RX_WAIT_FOR_ACK_TIMEOUT_US_2MBPS;
            break;

        case NRF_ESB_BITRATE_1MBPS:
            m_wait_for_ack_timeout_us = RX_WAIT_FOR_ACK_TIMEOUT_US_1MBPS;
            break;

        case NRF_ESB_BITRATE_250KBPS:
            m_wait_for_ack_timeout_us = RX_WAIT_FOR_ACK_TIMEOUT_US_250KBPS;
            break;

        case NRF_ESB_BITRATE_1MBPS_BLE:
            m_wait_for_ack_timeout_us = RX_WAIT_FOR_ACK_TIMEOUT_US_1MBPS_BLE;
            break;

        default:
            // Should not be reached
            break;
    }
}


static void update_radio_protocol()
{
    switch (m_config_local.protocol)
    {
        case NRF_ESB_PROTOCOL_ESB_DPL:
            update_rf_payload_format = update_rf_payload_format_esb_dpl;
            break;

        case NRF_ESB_PROTOCOL_ESB:
            update_rf_payload_format = update_rf_payload_format_esb;
            break;

        default:
            // Should not be reached
            break;
    }
}


static void update_radio_crc()
{
    NRF_RADIO->CRCCNF = m_config_local.crc << RADIO_CRCCNF_LEN_Pos;

    if (m_config_local.crc == RADIO_CRCCNF_LEN_Two)
    {
        NRF_RADIO->CRCINIT = 0xFFFFUL;      // Initial value
        NRF_RADIO->CRCPOLY = 0x11021UL;     // CRC poly: x^16+x^12^x^5+1
    }
    else if (m_config_local.crc == RADIO_CRCCNF_LEN_One)
    {
        NRF_RADIO->CRCINIT = 0xFFUL;        // Initial value
        NRF_RADIO->CRCPOLY = 0x107UL;       // CRC poly: x^8+x^2^x^1+1
    }
}


static void update_radio_parameters()
{
    update_radio_tx_power();
    update_radio_bitrate();
    update_radio_protocol();
    update_radio_crc();
    update_rf_payload_format(m_config_local.payload_length);
}


static void reset_fifos()
{
    m_tx_fifo.entry_point = 0;
    m_tx_fifo.exit_point  = 0;
    m_tx_fifo.count       = 0;

    m_rx_fifo.entry_point = 0;
    m_rx_fifo.exit_point  = 0;
    m_rx_fifo.count       = 0;
}


static void initialize_fifos()
{
    reset_fifos();

    for (int i = 0; i < NRF_ESB_TX_FIFO_SIZE; i++)
    {
        m_tx_fifo.p_payload[i] = &m_tx_fifo_payload[i];
    }

    for (int i = 0; i < NRF_ESB_RX_FIFO_SIZE; i++)
    {
        m_rx_fifo.p_payload[i] = &m_rx_fifo_payload[i];
    }
}


static void tx_fifo_remove_last()
{
    if (m_tx_fifo.count > 0)
    {
        DISABLE_RF_IRQ();

        m_tx_fifo.count--;
        if (++m_tx_fifo.exit_point >= NRF_ESB_TX_FIFO_SIZE)
        {
            m_tx_fifo.exit_point = 0;
        }

        ENABLE_RF_IRQ();
    }
}

/** @brief  Function to push the content of the rx_buffer to the RX FIFO.
 *
 *  The module will point the register NRF_RADIO->PACKETPTR to a buffer for receiving packets.
 *  After receiving a packet the module will call this function to copy the received data to
 *  the RX FIFO.
 *
 *  @param  pipe Pipe number to set for the packet.
 *  @param  pid  Packet ID.
 *
 *  @retval true   Operation successful.
 *  @retval false  Operation failed.
 */
static bool rx_fifo_push_rfbuf(uint8_t pipe, uint8_t pid)
{
    if (m_rx_fifo.count < NRF_ESB_RX_FIFO_SIZE)
    {
        if (m_config_local.protocol == NRF_ESB_PROTOCOL_ESB_DPL)
        {
            if (m_rx_payload_buffer[0] > NRF_ESB_MAX_PAYLOAD_LENGTH)
            {
                return false;
            }

            m_rx_fifo.p_payload[m_rx_fifo.entry_point]->length = m_rx_payload_buffer[0];
        }
        else if (m_config_local.mode == NRF_ESB_MODE_PTX)
        {
            // Received packet is an acknowledgment
            m_rx_fifo.p_payload[m_rx_fifo.entry_point]->length = 0;
        }
        else
        {
            m_rx_fifo.p_payload[m_rx_fifo.entry_point]->length = m_config_local.payload_length;
        }

        memcpy(m_rx_fifo.p_payload[m_rx_fifo.entry_point]->data, &m_rx_payload_buffer[2],
               m_rx_fifo.p_payload[m_rx_fifo.entry_point]->length);

        m_rx_fifo.p_payload[m_rx_fifo.entry_point]->pipe = pipe;
        m_rx_fifo.p_payload[m_rx_fifo.entry_point]->rssi = NRF_RADIO->RSSISAMPLE;
        m_rx_fifo.p_payload[m_rx_fifo.entry_point]->pid = pid;
        if (++m_rx_fifo.entry_point >= NRF_ESB_RX_FIFO_SIZE)
        {
            m_rx_fifo.entry_point = 0;
        }
        m_rx_fifo.count++;

        return true;
    }

    return false;
}


static void sys_timer_init()
{
    // Configure the system timer with a 1 MHz base frequency
    NRF_ESB_SYS_TIMER->PRESCALER = 4;
    NRF_ESB_SYS_TIMER->BITMODE   = TIMER_BITMODE_BITMODE_16Bit;
    NRF_ESB_SYS_TIMER->SHORTS    = TIMER_SHORTS_COMPARE1_CLEAR_Msk | TIMER_SHORTS_COMPARE1_STOP_Msk;
}


static void ppi_init()
{
    NRF_PPI->CH[NRF_ESB_PPI_TIMER_START].EEP = (uint32_t)&NRF_RADIO->EVENTS_READY;
    NRF_PPI->CH[NRF_ESB_PPI_TIMER_START].TEP = (uint32_t)&NRF_ESB_SYS_TIMER->TASKS_START;

    NRF_PPI->CH[NRF_ESB_PPI_TIMER_STOP].EEP  = (uint32_t)&NRF_RADIO->EVENTS_ADDRESS;
    NRF_PPI->CH[NRF_ESB_PPI_TIMER_STOP].TEP  = (uint32_t)&NRF_ESB_SYS_TIMER->TASKS_STOP;

    NRF_PPI->CH[NRF_ESB_PPI_RX_TIMEOUT].EEP  = (uint32_t)&NRF_ESB_SYS_TIMER->EVENTS_COMPARE[0];
    NRF_PPI->CH[NRF_ESB_PPI_RX_TIMEOUT].TEP  = (uint32_t)&NRF_RADIO->TASKS_DISABLE;

    NRF_PPI->CH[NRF_ESB_PPI_TX_START].EEP    = (uint32_t)&NRF_ESB_SYS_TIMER->EVENTS_COMPARE[1];
    NRF_PPI->CH[NRF_ESB_PPI_TX_START].TEP    = (uint32_t)&NRF_RADIO->TASKS_TXEN;
}


static void start_tx_transaction()
{
    bool ack;

    m_last_tx_attempts = 1;
    // Prepare the payload
    mp_current_payload = m_tx_fifo.p_payload[m_tx_fifo.exit_point];


    switch (m_config_local.protocol)
    {
        case NRF_ESB_PROTOCOL_ESB:
            update_rf_payload_format(mp_current_payload->length);
            m_tx_payload_buffer[0] = mp_current_payload->pid;
            m_tx_payload_buffer[1] = 0;
            memcpy(&m_tx_payload_buffer[2], mp_current_payload->data, mp_current_payload->length);

            NRF_RADIO->SHORTS   = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_RXEN_Msk;
            NRF_RADIO->INTENSET = RADIO_INTENSET_DISABLED_Msk | RADIO_INTENSET_READY_Msk;

            // Configure the retransmit counter
            m_retransmits_remaining = m_config_local.retransmit_count;
            on_radio_disabled = on_radio_disabled_tx;
            m_nrf_esb_mainstate = NRF_ESB_STATE_PTX_TX_ACK;
            break;

        case NRF_ESB_PROTOCOL_ESB_DPL:
            ack = !mp_current_payload->noack || !m_config_local.selective_auto_ack;
            m_tx_payload_buffer[0] = mp_current_payload->length;
            m_tx_payload_buffer[1] = mp_current_payload->pid << 1;
            m_tx_payload_buffer[1] |= ack ? 0x00 : 0x01;
            memcpy(&m_tx_payload_buffer[2], mp_current_payload->data, mp_current_payload->length);

            // Handling ack if noack is set to false or if selective auto ack is turned off
            if (ack)
            {
                NRF_RADIO->SHORTS   = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_RXEN_Msk;
                NRF_RADIO->INTENSET = RADIO_INTENSET_DISABLED_Msk | RADIO_INTENSET_READY_Msk;

                // Configure the retransmit counter
                m_retransmits_remaining = m_config_local.retransmit_count;
                on_radio_disabled = on_radio_disabled_tx;
                m_nrf_esb_mainstate = NRF_ESB_STATE_PTX_TX_ACK;
            }
            else
            {
                NRF_RADIO->SHORTS   = RADIO_SHORTS_COMMON;
                NRF_RADIO->INTENSET = RADIO_INTENSET_DISABLED_Msk;
                on_radio_disabled   = on_radio_disabled_tx_noack;
                m_nrf_esb_mainstate = NRF_ESB_STATE_PTX_TX;
            }
            break;

        default:
            // Should not be reached
            break;
    }

    NRF_RADIO->TXADDRESS    = mp_current_payload->pipe;
    NRF_RADIO->RXADDRESSES  = 1 << mp_current_payload->pipe;

    NRF_RADIO->FREQUENCY    = m_esb_addr.rf_channel;
    NRF_RADIO->PACKETPTR    = (uint32_t)m_tx_payload_buffer;

    NVIC_ClearPendingIRQ(RADIO_IRQn);
    NVIC_EnableIRQ(RADIO_IRQn);

    NRF_RADIO->EVENTS_ADDRESS = 0;
    NRF_RADIO->EVENTS_PAYLOAD = 0;
    NRF_RADIO->EVENTS_DISABLED = 0;

    DEBUG_PIN_SET(DEBUGPIN4);
    NRF_RADIO->TASKS_TXEN  = 1;
}


static void on_radio_disabled_tx_noack()
{
    m_interrupt_flags |= NRF_ESB_INT_TX_SUCCESS_MSK;
    tx_fifo_remove_last();

    if (m_tx_fifo.count == 0)
    {
        m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;
        NVIC_SetPendingIRQ(ESB_EVT_IRQ);
    }
    else
    {
        NVIC_SetPendingIRQ(ESB_EVT_IRQ);
        start_tx_transaction();
    }
}


static void on_radio_disabled_tx()
{
    // Remove the DISABLED -> RXEN shortcut, to make sure the radio stays
    // disabled after the RX window
    NRF_RADIO->SHORTS           = RADIO_SHORTS_COMMON;

    // Make sure the timer is started the next time the radio is ready,
    // and that it will disable the radio automatically if no packet is
    // received by the time defined in m_wait_for_ack_timeout_us
    NRF_ESB_SYS_TIMER->CC[0]    = m_wait_for_ack_timeout_us;
    NRF_ESB_SYS_TIMER->CC[1]    = m_config_local.retransmit_delay - 130;
    NRF_ESB_SYS_TIMER->TASKS_CLEAR = 1;
    NRF_ESB_SYS_TIMER->EVENTS_COMPARE[0] = 0;
    NRF_ESB_SYS_TIMER->EVENTS_COMPARE[1] = 0;

    NRF_PPI->CHENSET            = (1 << NRF_ESB_PPI_TIMER_START) |
                                  (1 << NRF_ESB_PPI_RX_TIMEOUT) |
                                  (1 << NRF_ESB_PPI_TIMER_STOP);
    NRF_PPI->CHENCLR            = (1 << NRF_ESB_PPI_TX_START);
    NRF_RADIO->EVENTS_END       = 0;

    if (m_config_local.protocol == NRF_ESB_PROTOCOL_ESB)
    {
        update_rf_payload_format(0);
    }

    NRF_RADIO->PACKETPTR        = (uint32_t)m_rx_payload_buffer;
    on_radio_disabled           = on_radio_disabled_tx_wait_for_ack;
    m_nrf_esb_mainstate         = NRF_ESB_STATE_PTX_RX_ACK;
}


static void on_radio_disabled_tx_wait_for_ack()
{
    // This marks the completion of a TX_RX sequence (TX with ACK)

    // Make sure the timer will not deactivate the radio if a packet is received
    NRF_PPI->CHENCLR = (1 << NRF_ESB_PPI_TIMER_START) |
                       (1 << NRF_ESB_PPI_RX_TIMEOUT)  |
                       (1 << NRF_ESB_PPI_TIMER_STOP);

    // If the radio has received a packet and the CRC status is OK
    if (NRF_RADIO->EVENTS_END && NRF_RADIO->CRCSTATUS != 0)
    {
        NRF_ESB_SYS_TIMER->TASKS_STOP = 1;
        NRF_PPI->CHENCLR = (1 << NRF_ESB_PPI_TX_START);
        m_interrupt_flags |= NRF_ESB_INT_TX_SUCCESS_MSK;
        m_last_tx_attempts = m_config_local.retransmit_count - m_retransmits_remaining + 1;

        tx_fifo_remove_last();

        if (m_config_local.protocol != NRF_ESB_PROTOCOL_ESB && m_rx_payload_buffer[0] > 0)
        {
            if (rx_fifo_push_rfbuf((uint8_t)NRF_RADIO->TXADDRESS, 0))
            {
                m_interrupt_flags |= NRF_ESB_INT_RX_DATA_RECEIVED_MSK;
            }
        }

        if ((m_tx_fifo.count == 0) || (m_config_local.tx_mode == NRF_ESB_TXMODE_MANUAL))
        {
            m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;
            NVIC_SetPendingIRQ(ESB_EVT_IRQ);
        }
        else
        {
            NVIC_SetPendingIRQ(ESB_EVT_IRQ);
            start_tx_transaction();
        }
    }
    else
    {
        if (m_retransmits_remaining-- == 0)
        {
            NRF_ESB_SYS_TIMER->TASKS_STOP = 1;
            NRF_PPI->CHENCLR = (1 << NRF_ESB_PPI_TX_START);
            // All retransmits are expended, and the TX operation is suspended
            m_last_tx_attempts = m_config_local.retransmit_count + 1;
            m_interrupt_flags |= NRF_ESB_INT_TX_FAILED_MSK;

            m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;
            NVIC_SetPendingIRQ(ESB_EVT_IRQ);
        }
        else
        {
            // There are still more retransmits left, TX mode should be
            // entered again as soon as the system timer reaches CC[1].
            NRF_RADIO->SHORTS = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_RXEN_Msk;
            update_rf_payload_format(mp_current_payload->length);
            NRF_RADIO->PACKETPTR = (uint32_t)m_tx_payload_buffer;
            on_radio_disabled = on_radio_disabled_tx;
            m_nrf_esb_mainstate = NRF_ESB_STATE_PTX_TX_ACK;
            NRF_ESB_SYS_TIMER->TASKS_START = 1;
            NRF_PPI->CHENSET = (1 << NRF_ESB_PPI_TX_START);
            if (NRF_ESB_SYS_TIMER->EVENTS_COMPARE[1])
            {
                NRF_RADIO->TASKS_TXEN = 1;
            }
        }
    }
}

static void clear_events_restart_rx(void)
{
    NRF_RADIO->SHORTS = RADIO_SHORTS_COMMON;
    update_rf_payload_format(m_config_local.payload_length);
    NRF_RADIO->PACKETPTR = (uint32_t)m_rx_payload_buffer;
    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_DISABLE = 1;

    while (NRF_RADIO->EVENTS_DISABLED == 0);

    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->SHORTS = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_TXEN_Msk;
    NRF_RADIO->TASKS_RXEN = 1;
}

static void on_radio_disabled_rx(void)
{
    bool            ack                = false;
    bool            retransmit_payload = false;
    bool            send_rx_event      = true;
    pipe_info_t *   p_pipe_info;

    if (NRF_RADIO->CRCSTATUS == 0)
    {
        clear_events_restart_rx();
        return;
    }

    if (m_rx_fifo.count >= NRF_ESB_RX_FIFO_SIZE)
    {
        clear_events_restart_rx();
        return;
    }

    p_pipe_info = &m_rx_pipe_info[NRF_RADIO->RXMATCH];
    if (NRF_RADIO->RXCRC             == p_pipe_info->crc &&
        (m_rx_payload_buffer[1] >> 1) == p_pipe_info->pid
       )
    {
        retransmit_payload = true;
        send_rx_event = false;
    }

    p_pipe_info->pid = m_rx_payload_buffer[1] >> 1;
    p_pipe_info->crc = NRF_RADIO->RXCRC;

    if (m_config_local.selective_auto_ack == false || ((m_rx_payload_buffer[1] & 0x01) == 0))
    {
        ack = true;
    }

    if (ack)
    {
        NRF_RADIO->SHORTS = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_RXEN_Msk;

        switch (m_config_local.protocol)
        {
            case NRF_ESB_PROTOCOL_ESB_DPL:
                {
                    if (m_tx_fifo.count > 0 &&
                        (m_tx_fifo.p_payload[m_tx_fifo.exit_point]->pipe == NRF_RADIO->RXMATCH)
                       )
                    {
                        // Pipe stays in ACK with payload until TX FIFO is empty
                        // Do not report TX success on first ack payload or retransmit
                        if (p_pipe_info->ack_payload == true && !retransmit_payload)
                        {
                            if (++m_tx_fifo.exit_point >= NRF_ESB_TX_FIFO_SIZE)
                            {
                                m_tx_fifo.exit_point = 0;
                            }

                            m_tx_fifo.count--;

                            // ACK payloads also require TX_DS
                            // (page 40 of the 'nRF24LE1_Product_Specification_rev1_6.pdf').
                            m_interrupt_flags |= NRF_ESB_INT_TX_SUCCESS_MSK;
                        }

                        p_pipe_info->ack_payload = true;

                        mp_current_payload = m_tx_fifo.p_payload[m_tx_fifo.exit_point];

                        update_rf_payload_format(mp_current_payload->length);
                        m_tx_payload_buffer[0] = mp_current_payload->length;
                        memcpy(&m_tx_payload_buffer[2],
                               mp_current_payload->data,
                               mp_current_payload->length);
                    }
                    else
                    {
                        p_pipe_info->ack_payload = false;
                        update_rf_payload_format(0);
                        m_tx_payload_buffer[0] = 0;
                    }

                    m_tx_payload_buffer[1] = m_rx_payload_buffer[1];
                }
                break;

            case NRF_ESB_PROTOCOL_ESB:
                {
                    update_rf_payload_format(0);
                    m_tx_payload_buffer[0] = m_rx_payload_buffer[0];
                    m_tx_payload_buffer[1] = 0;
                }
                break;
        }

        m_nrf_esb_mainstate = NRF_ESB_STATE_PRX_SEND_ACK;
        NRF_RADIO->TXADDRESS = NRF_RADIO->RXMATCH;
        NRF_RADIO->PACKETPTR = (uint32_t)m_tx_payload_buffer;
        on_radio_disabled = on_radio_disabled_rx_ack;
    }
    else
    {
        clear_events_restart_rx();
    }

    if (send_rx_event)
    {
        // Push the new packet to the RX buffer and trigger a received event if the operation was
        // successful.
        if (rx_fifo_push_rfbuf(NRF_RADIO->RXMATCH, p_pipe_info->pid))
        {
            m_interrupt_flags |= NRF_ESB_INT_RX_DATA_RECEIVED_MSK;
            NVIC_SetPendingIRQ(ESB_EVT_IRQ);
        }
    }
}


static void on_radio_disabled_rx_ack(void)
{
    NRF_RADIO->SHORTS = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_TXEN_Msk;
    update_rf_payload_format(m_config_local.payload_length);

    NRF_RADIO->PACKETPTR = (uint32_t)m_rx_payload_buffer;
    on_radio_disabled = on_radio_disabled_rx;

    m_nrf_esb_mainstate = NRF_ESB_STATE_PRX;
}


/**@brief Function for clearing pending interrupts.
 *
 * @param[in,out]   p_interrupts        Pointer to the value that holds the current interrupts.
 *
 * @retval  NRF_SUCCESS                     If the interrupts were cleared successfully.
 * @retval  NRF_ERROR_NULL                  If the required parameter was NULL.
 * @retval  NRF_INVALID_STATE               If the module is not initialized.
 */
static uint32_t nrf_esb_get_clear_interrupts(uint32_t * p_interrupts)
{
    VERIFY_TRUE(m_esb_initialized, NRF_ERROR_INVALID_STATE);
    VERIFY_PARAM_NOT_NULL(p_interrupts);

    DISABLE_RF_IRQ();

    *p_interrupts = m_interrupt_flags;
    m_interrupt_flags = 0;

    ENABLE_RF_IRQ();

    return NRF_SUCCESS;
}


void RADIO_IRQHandler()
{
    if (NRF_RADIO->EVENTS_READY && (NRF_RADIO->INTENSET & RADIO_INTENSET_READY_Msk))
    {
        NRF_RADIO->EVENTS_READY = 0;
        DEBUG_PIN_SET(DEBUGPIN1);
    }

    if (NRF_RADIO->EVENTS_END && (NRF_RADIO->INTENSET & RADIO_INTENSET_END_Msk))
    {
        NRF_RADIO->EVENTS_END = 0;
        DEBUG_PIN_SET(DEBUGPIN2);

        // Call the correct on_radio_end function, depending on the current protocol state
        if (on_radio_end)
        {
            on_radio_end();
        }
    }

    if (NRF_RADIO->EVENTS_DISABLED && (NRF_RADIO->INTENSET & RADIO_INTENSET_DISABLED_Msk))
    {
        NRF_RADIO->EVENTS_DISABLED = 0;
        DEBUG_PIN_SET(DEBUGPIN3);

        // Call the correct on_radio_disable function, depending on the current protocol state
        if (on_radio_disabled)
        {
            on_radio_disabled();
        }
    }

    DEBUG_PIN_CLR(DEBUGPIN1);
    DEBUG_PIN_CLR(DEBUGPIN2);
    DEBUG_PIN_CLR(DEBUGPIN3);
    DEBUG_PIN_CLR(DEBUGPIN4);
}


uint32_t nrf_esb_init(nrf_esb_config_t const * p_config)
{
    uint32_t err_code;

    VERIFY_PARAM_NOT_NULL(p_config);

    if (m_esb_initialized)
    {
        err_code = nrf_esb_disable();
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    m_event_handler = p_config->event_handler;

    memcpy(&m_config_local, p_config, sizeof(nrf_esb_config_t));

    m_interrupt_flags    = 0;

    memset(m_rx_pipe_info, 0, sizeof(m_rx_pipe_info));
    memset(m_pids, 0, sizeof(m_pids));

    update_radio_parameters();

    initialize_fifos();

    sys_timer_init();

    ppi_init();

    NVIC_SetPriority(RADIO_IRQn, m_config_local.radio_irq_priority & 0x03);
    NVIC_SetPriority(ESB_EVT_IRQ, m_config_local.event_irq_priority & 0x03);
    NVIC_EnableIRQ(ESB_EVT_IRQ);

    m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;
    m_esb_initialized = true;

    return NRF_SUCCESS;
}


uint32_t nrf_esb_suspend(void)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);

    // Clear PPI
    NRF_PPI->CHENCLR = (1 << NRF_ESB_PPI_TIMER_START) |
                       (1 << NRF_ESB_PPI_TIMER_STOP)  |
                       (1 << NRF_ESB_PPI_RX_TIMEOUT)  |
                       (1 << NRF_ESB_PPI_TX_START);

    m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;

    return NRF_SUCCESS;
}


uint32_t nrf_esb_disable(void)
{
    // Clear PPI
    NRF_PPI->CHENCLR = (1 << NRF_ESB_PPI_TIMER_START) |
                       (1 << NRF_ESB_PPI_TIMER_STOP)  |
                       (1 << NRF_ESB_PPI_RX_TIMEOUT)  |
                       (1 << NRF_ESB_PPI_TX_START);

    m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;

    reset_fifos();

    memset(m_rx_pipe_info, 0, sizeof(m_rx_pipe_info));
    memset(m_pids, 0, sizeof(m_pids));

    // Disable the radio
    NVIC_DisableIRQ(ESB_EVT_IRQ);
    NRF_RADIO->SHORTS = RADIO_SHORTS_READY_START_Enabled << RADIO_SHORTS_READY_START_Pos |
                        RADIO_SHORTS_END_DISABLE_Enabled << RADIO_SHORTS_END_DISABLE_Pos;

    return NRF_SUCCESS;
}


bool nrf_esb_is_idle(void)
{
    return m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE;
}


void ESB_EVT_IRQHandler(void)
{
    ret_code_t      err_code;
    uint32_t        interrupts;
    nrf_esb_evt_t   event;

    event.tx_attempts = m_last_tx_attempts;

    err_code = nrf_esb_get_clear_interrupts(&interrupts);
    if (err_code == NRF_SUCCESS && m_event_handler != 0)
    {
        if (interrupts & NRF_ESB_INT_TX_SUCCESS_MSK)
        {
            event.evt_id = NRF_ESB_EVENT_TX_SUCCESS;
            m_event_handler(&event);
        }
        if (interrupts & NRF_ESB_INT_TX_FAILED_MSK)
        {
            event.evt_id = NRF_ESB_EVENT_TX_FAILED;
            m_event_handler(&event);
        }
        if (interrupts & NRF_ESB_INT_RX_DATA_RECEIVED_MSK)
        {
            event.evt_id = NRF_ESB_EVENT_RX_RECEIVED;
            m_event_handler(&event);
        }
    }
}

uint32_t nrf_esb_write_payload(nrf_esb_payload_t const * p_payload)
{
    VERIFY_TRUE(m_esb_initialized, NRF_ERROR_INVALID_STATE);
    VERIFY_PARAM_NOT_NULL(p_payload);
    VERIFY_PAYLOAD_LENGTH(p_payload);
    VERIFY_FALSE(m_tx_fifo.count >= NRF_ESB_TX_FIFO_SIZE, NRF_ERROR_NO_MEM);

    if (m_config_local.mode == NRF_ESB_MODE_PTX &&
        p_payload->noack && !m_config_local.selective_auto_ack )
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    DISABLE_RF_IRQ();

    memcpy(m_tx_fifo.p_payload[m_tx_fifo.entry_point], p_payload, sizeof(nrf_esb_payload_t));

    m_pids[p_payload->pipe] = (m_pids[p_payload->pipe] + 1) % (NRF_ESB_PID_MAX + 1);
    m_tx_fifo.p_payload[m_tx_fifo.entry_point]->pid = m_pids[p_payload->pipe];

    if (++m_tx_fifo.entry_point >= NRF_ESB_TX_FIFO_SIZE)
    {
        m_tx_fifo.entry_point = 0;
    }

    m_tx_fifo.count++;

    ENABLE_RF_IRQ();


    if (m_config_local.mode == NRF_ESB_MODE_PTX &&
        m_config_local.tx_mode == NRF_ESB_TXMODE_AUTO &&
        m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE)
    {
        start_tx_transaction();
    }

    return NRF_SUCCESS;
}


uint32_t nrf_esb_read_rx_payload(nrf_esb_payload_t * p_payload)
{
    VERIFY_TRUE(m_esb_initialized, NRF_ERROR_INVALID_STATE);
    VERIFY_PARAM_NOT_NULL(p_payload);

    if (m_rx_fifo.count == 0)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    DISABLE_RF_IRQ();

    p_payload->length = m_rx_fifo.p_payload[m_rx_fifo.exit_point]->length;
    p_payload->pipe   = m_rx_fifo.p_payload[m_rx_fifo.exit_point]->pipe;
    p_payload->rssi   = m_rx_fifo.p_payload[m_rx_fifo.exit_point]->rssi;
    p_payload->pid    = m_rx_fifo.p_payload[m_rx_fifo.exit_point]->pid;
    memcpy(p_payload->data, m_rx_fifo.p_payload[m_rx_fifo.exit_point]->data, p_payload->length);

    if (++m_rx_fifo.exit_point >= NRF_ESB_RX_FIFO_SIZE)
    {
        m_rx_fifo.exit_point = 0;
    }

    m_rx_fifo.count--;

    ENABLE_RF_IRQ();

    return NRF_SUCCESS;
}


uint32_t nrf_esb_start_tx(void)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);

    if (m_tx_fifo.count == 0)
    {
        return NRF_ERROR_BUFFER_EMPTY;
    }

    start_tx_transaction();

    return NRF_SUCCESS;
}


uint32_t nrf_esb_start_rx(void)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);

    NRF_RADIO->INTENCLR = 0xFFFFFFFF;
    NRF_RADIO->EVENTS_DISABLED = 0;
    on_radio_disabled = on_radio_disabled_rx;

    NRF_RADIO->SHORTS      = RADIO_SHORTS_COMMON | RADIO_SHORTS_DISABLED_TXEN_Msk;
    NRF_RADIO->INTENSET    = RADIO_INTENSET_DISABLED_Msk;
    m_nrf_esb_mainstate    = NRF_ESB_STATE_PRX;

    NRF_RADIO->RXADDRESSES  = m_esb_addr.rx_pipes_enabled;
    NRF_RADIO->FREQUENCY    = m_esb_addr.rf_channel;
    NRF_RADIO->PACKETPTR    = (uint32_t)m_rx_payload_buffer;

    NVIC_ClearPendingIRQ(RADIO_IRQn);
    NVIC_EnableIRQ(RADIO_IRQn);

    NRF_RADIO->EVENTS_ADDRESS = 0;
    NRF_RADIO->EVENTS_PAYLOAD = 0;
    NRF_RADIO->EVENTS_DISABLED = 0;

    NRF_RADIO->TASKS_RXEN  = 1;

    return NRF_SUCCESS;
}


uint32_t nrf_esb_stop_rx(void)
{
    if (m_nrf_esb_mainstate == NRF_ESB_STATE_PRX)
    {
        NRF_RADIO->SHORTS = 0;
        NRF_RADIO->INTENCLR = 0xFFFFFFFF;
        on_radio_disabled = NULL;
        NRF_RADIO->EVENTS_DISABLED = 0;
        NRF_RADIO->TASKS_DISABLE = 1;
        while (NRF_RADIO->EVENTS_DISABLED == 0);
        m_nrf_esb_mainstate = NRF_ESB_STATE_IDLE;

        return NRF_SUCCESS;
    }

    return NRF_ESB_ERROR_NOT_IN_RX_MODE;
}


uint32_t nrf_esb_flush_tx(void)
{
    VERIFY_TRUE(m_esb_initialized, NRF_ERROR_INVALID_STATE);

    DISABLE_RF_IRQ();

    m_tx_fifo.count = 0;
    m_tx_fifo.entry_point = 0;
    m_tx_fifo.exit_point = 0;

    ENABLE_RF_IRQ();

    return NRF_SUCCESS;
}


uint32_t nrf_esb_pop_tx(void)
{
    VERIFY_TRUE(m_esb_initialized, NRF_ERROR_INVALID_STATE);
    VERIFY_TRUE(m_tx_fifo.count > 0, NRF_ERROR_BUFFER_EMPTY);

    DISABLE_RF_IRQ();

    if (++m_tx_fifo.entry_point >= NRF_ESB_TX_FIFO_SIZE)
    {
        m_tx_fifo.entry_point = 0;
    }
    m_tx_fifo.count--;

    ENABLE_RF_IRQ();

    return NRF_SUCCESS;
}


uint32_t nrf_esb_flush_rx(void)
{
    VERIFY_TRUE(m_esb_initialized, NRF_ERROR_INVALID_STATE);

    DISABLE_RF_IRQ();

    m_rx_fifo.count = 0;
    m_rx_fifo.entry_point = 0;
    m_rx_fifo.exit_point = 0;

    memset(m_rx_pipe_info, 0, sizeof(m_rx_pipe_info));

    ENABLE_RF_IRQ();

    return NRF_SUCCESS;
}


uint32_t nrf_esb_set_address_length(uint8_t length)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);
    VERIFY_TRUE(length > 2 && length < 6, NRF_ERROR_INVALID_PARAM);

    m_esb_addr.addr_length = length;

    update_rf_payload_format(m_config_local.payload_length);

    return NRF_SUCCESS;
}


uint32_t nrf_esb_set_base_address_0(uint8_t const * p_addr)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);
    VERIFY_PARAM_NOT_NULL(p_addr);

    memcpy(m_esb_addr.base_addr_p0, p_addr, 4);

    update_radio_addresses(NRF_ESB_ADDR_UPDATE_MASK_BASE0);

    return NRF_SUCCESS;
}


uint32_t nrf_esb_set_base_address_1(uint8_t const * p_addr)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);
    VERIFY_PARAM_NOT_NULL(p_addr);

    memcpy(m_esb_addr.base_addr_p1, p_addr, 4);

    update_radio_addresses(NRF_ESB_ADDR_UPDATE_MASK_BASE1);

    return NRF_SUCCESS;
}


uint32_t nrf_esb_set_prefixes(uint8_t const * p_prefixes, uint8_t num_pipes)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);
    VERIFY_PARAM_NOT_NULL(p_prefixes);
    VERIFY_TRUE(num_pipes < 9, NRF_ERROR_INVALID_PARAM);

    memcpy(m_esb_addr.pipe_prefixes, p_prefixes, num_pipes);
    m_esb_addr.num_pipes = num_pipes;
    m_esb_addr.rx_pipes_enabled = BIT_MASK_UINT_8(num_pipes);

    update_radio_addresses(NRF_ESB_ADDR_UPDATE_MASK_PREFIX);

    return NRF_SUCCESS;
}


uint32_t nrf_esb_update_prefix(uint8_t pipe, uint8_t prefix)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);
    VERIFY_TRUE(pipe < 8, NRF_ERROR_INVALID_PARAM);

    m_esb_addr.pipe_prefixes[pipe] = prefix;

    update_radio_addresses(NRF_ESB_ADDR_UPDATE_MASK_PREFIX);

    return NRF_SUCCESS;
}


uint32_t nrf_esb_enable_pipes(uint8_t enable_mask)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);

    m_esb_addr.rx_pipes_enabled = enable_mask;

    return NRF_SUCCESS;
}


uint32_t nrf_esb_set_rf_channel(uint32_t channel)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);
    VERIFY_TRUE(channel <= 100, NRF_ERROR_INVALID_PARAM);

    m_esb_addr.rf_channel = channel;

    return NRF_SUCCESS;
}


uint32_t nrf_esb_get_rf_channel(uint32_t * p_channel)
{
    VERIFY_PARAM_NOT_NULL(p_channel);

    *p_channel = m_esb_addr.rf_channel;

    return NRF_SUCCESS;
}


uint32_t nrf_esb_set_tx_power(nrf_esb_tx_power_t tx_output_power)
{
    VERIFY_TRUE(m_nrf_esb_mainstate == NRF_ESB_STATE_IDLE, NRF_ERROR_BUSY);

    if ( m_config_local.tx_output_power != tx_output_power )
    {
        m_config_local.tx_output_power = tx_output_power;
        update_radio_tx_power();
    }

    return NRF_SUCCESS;
}
