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
#include <stddef.h>
#include <string.h>

#include "app_error.h"
#include "app_util.h"
#include "app_util_platform.h"
#include "app_timer.h"
#include "nrf_queue.h"
#include "ser_phy.h"
#include "ser_phy_hci.h"
#include "crc16.h"
#include "nrf_soc.h"
#include "ser_config.h"
#include "ser_phy_debug_comm.h"

#include "nrf_sdh.h"
#include "ser_hal_transport.h"
#include "app_scheduler.h"

#ifdef SER_CONNECTIVITY
#include "ser_conn_handlers.h"
#include "ser_conn_reset_cmd_decoder.h"
#endif /* SER_CONNECTIVITY */

#ifdef BLE_STACK_SUPPORT_REQD
#include "nrf_sdm.h"
#endif /* BLE_STACK_SUPPORT_REQD */

#define NRF_LOG_MODULE_NAME sphy_hci
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
// hide globals for release version, expose for debug version
#if defined(SER_PHY_HCI_DEBUG_ENABLE)
#define _static
#else
#define _static static
#endif

#define PKT_HDR_SIZE            4 /**< Packet header size in number of bytes. */
#define PKT_CRC_SIZE            2 /**< Packet CRC size in number of bytes. */
#define MAX_PACKET_SIZE_IN_BITS (11uL * \
                                 (SER_HAL_TRANSPORT_MAX_PKT_SIZE + PKT_HDR_SIZE + PKT_CRC_SIZE))
#define BAUD_TIME_us            (1000000uL / SER_PHY_UART_BAUDRATE_VAL)

#define TX_EVT_QUEUE_SIZE            16
#define RX_EVT_QUEUE_SIZE            16
#define PKT_TYPE_VENDOR_SPECIFIC     14                                                /**< Packet type vendor specific. */
#define PKT_TYPE_ACK                 0                                                 /**< Packet type acknowledgement. */
#define PKT_TYPE_LINK_CONTROL        15                                                /**< Packet type link control. */
#define PKT_TYPE_RESET               5                                                 /**< Packet type reset. */
#define DATA_INTEGRITY_MASK          (1 << 6)                                          /**< Mask for data integrity bit in the packet header. */
#define RELIABLE_PKT_MASK            (1 << 7)                                          /**< Mask for reliable packet bit in the packet header. */
#define INITIAL_ACK_NUMBER_EXPECTED  0                                                 /**< Initial acknowledge number expected. */
#define INITIAL_SEQ_NUMBER           INITIAL_ACK_NUMBER_EXPECTED                       /**< Initial acknowledge number transmitted. */
#define INVALID_PKT_TYPE             0xFFFFFFFFu                                       /**< Internal invalid packet type value. */
#define MAX_TRANSMISSION_TIME_ms     (MAX_PACKET_SIZE_IN_BITS * BAUD_TIME_us / 1000uL) /**< Max transmission time of a single application packet over UART in units of mseconds. */
#define RETRANSMISSION_TIMEOUT_IN_ms (50uL * MAX_TRANSMISSION_TIME_ms)                 /**< Retransmission timeout for application packet in units of mseconds. */

#ifdef  HCI_LINK_CONTROL
#define HCI_PKT_SYNC        0x7E01u                                                    /**< Link Control Packet: type SYNC */
#define HCI_PKT_SYNC_RSP    0x7D02u                                                    /**< Link Control Packet: type SYNC RESPONSE */
#define HCI_PKT_CONFIG      0xFC03u                                                    /**< Link Control Packet: type CONFIG */
#define HCI_PKT_CONFIG_RSP  0x7B04u                                                    /**< Link Control Packet: type CONFIG RESPONSE */
#define HCI_CONFIG_FIELD    0x11u                                                      /**< Configuration field of CONFIG and CONFIG_RSP packet */
#define HCI_PKT_SYNC_SIZE   6u                                                         /**< Size of SYNC and SYNC_RSP packet */
#define HCI_PKT_CONFIG_SIZE 7u                                                         /**< Size of CONFIG and CONFIG_RSP packet */
#define HCI_LINK_CONTROL_PKT_INVALID 0xFFFFu                                           /**< Size of CONFIG and CONFIG_RSP packet */
#define HCI_LINK_CONTROL_TIMEOUT     1u                                                /**< Default link control timeout. */
#endif  /* HCI_LINK_CONTROL */

#define PACKET_TYPE_STR(type)\
    ((type == PKT_TYPE_ACK) ? "ACK" :\
    ((type ==PKT_TYPE_LINK_CONTROL) ? "Link Control" : \
    ((type ==PKT_TYPE_VENDOR_SPECIFIC) ? "Vendor Specific" : "Reset")))

#define RETRANSMISSION_TIMEOUT_IN_TICKS (APP_TIMER_TICKS(RETRANSMISSION_TIMEOUT_IN_ms)) /**< Retransmission timeout for application packet in units of timer ticks. */
#define MAX_RETRY_COUNT                 5                                      /**< Max retransmission retry count for application packets. */

#if   (defined(HCI_TIMER0))
#define HCI_TIMER            NRF_TIMER0
#define HCI_TIMER_IRQn       TIMER0_IRQn
#define HCI_TIMER_IRQHandler TIMER0_IRQHandler
#elif (defined(HCI_TIMER1))
#define HCI_TIMER            NRF_TIMER1
#define HCI_TIMER_IRQn       TIMER1_IRQn
#define HCI_TIMER_IRQHandler TIMER1_IRQHandler
#elif (defined(HCI_TIMER2))
#define HCI_TIMER            NRF_TIMER2
#define HCI_TIMER_IRQn       TIMER2_IRQn
#define HCI_TIMER_IRQHandler TIMER2_IRQHandler
#else
#define HCI_APP_TIMER
#endif


/**@brief States of the hci event driven state machine. */
typedef enum
{
    HCI_TX_STATE_DISABLE,
    HCI_TX_STATE_SEND,
    HCI_TX_STATE_WAIT_FOR_FIRST_TX_END,
    HCI_TX_STATE_WAIT_FOR_ACK_OR_TX_END,
    HCI_TX_STATE_WAIT_FOR_ACK,
    HCI_TX_STATE_WAIT_FOR_TX_END
} hci_tx_fsm_state_t;

typedef enum
{
    HCI_RX_STATE_DISABLE,
    HCI_RX_STATE_RECEIVE,
    HCI_RX_STATE_WAIT_FOR_MEM,
    HCI_RX_STATE_WAIT_FOR_SLIP_ACK_END,
    HCI_RX_STATE_WAIT_FOR_SLIP_NACK_END,
} hci_rx_fsm_state_t;

typedef enum
{
    HCI_EVT_TIMEOUT,
} hci_timer_evt_type_t;

typedef enum
{
    HCI_SER_PHY_TX_REQUEST,
    HCI_SER_PHY_RX_BUF_GRANTED,
    HCI_SER_PHY_EVT_GEN_ENABLE,
    HCI_SER_PHY_EVT_GEN_DISABLE
} ser_phy_int_evt_type_t;

typedef enum
{
    HCI_SER_PHY_EVT,
    HCI_SLIP_EVT,
    HCI_TIMER_EVT,
} hci_evt_source_t;

#ifdef HCI_LINK_CONTROL
typedef enum
{
    HCI_MODE_DISABLE,
    HCI_MODE_UNINITIALIZED,
    HCI_MODE_INITIALIZED,
    HCI_MODE_ACTIVE,
} hci_mode_t;
#endif /*HCI_LINK_CONTROL */

typedef struct
{
    hci_timer_evt_type_t evt_type; /**< Type of an event. */
} hci_timer_evt_t;

typedef struct
{
    ser_phy_int_evt_type_t evt_type; /**< Type of an event. */
} ser_phy_int_evt_t;

typedef struct
{
    hci_evt_source_t evt_source; /**< source of an event. */
    union
    {
        ser_phy_int_evt_t      ser_phy_evt;      /**< ser_phy event. */
        ser_phy_hci_slip_evt_t ser_phy_slip_evt; /**< ser_phy_hci event. */
        hci_timer_evt_t        timer_evt;        /**< timer event. */
    } evt;
} hci_evt_t;

_static uint8_t m_tx_packet_header[PKT_HDR_SIZE];
_static uint8_t m_tx_packet_crc[PKT_CRC_SIZE];
_static uint8_t m_tx_ack_packet[PKT_HDR_SIZE];
#ifdef HCI_LINK_CONTROL
_static uint8_t m_tx_link_control_header[PKT_HDR_SIZE];
_static uint8_t m_tx_link_control_payload[HCI_PKT_CONFIG_SIZE - PKT_HDR_SIZE];
static bool m_cfg_sent;
#endif /* HCI_LINK_CONTROL */

_static uint32_t m_packet_ack_number; // Sequence number counter of the packet expected to be received
_static uint32_t m_packet_seq_number; // Sequence number counter of the transmitted packet for which acknowledgement packet is waited for


_static uint32_t m_tx_retry_count;


// _static uint32_t m_tx_retx_counter = 0;
// _static uint32_t m_rx_drop_counter = 0;

NRF_QUEUE_DEF(hci_evt_t,
              m_tx_evt_queue,
              TX_EVT_QUEUE_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);

NRF_QUEUE_DEF(hci_evt_t,
              m_rx_evt_queue,
              RX_EVT_QUEUE_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);

_static hci_tx_fsm_state_t m_hci_tx_fsm_state = HCI_TX_STATE_DISABLE;
_static hci_rx_fsm_state_t m_hci_rx_fsm_state = HCI_RX_STATE_DISABLE;

#ifdef HCI_LINK_CONTROL
_static hci_mode_t m_hci_mode                  = HCI_MODE_DISABLE;
_static uint16_t   m_hci_link_control_next_pkt = HCI_PKT_SYNC;
_static bool       m_hci_other_side_active     = false;
#endif /* HCI_LINK_CONTROL */

#ifdef HCI_APP_TIMER
APP_TIMER_DEF(m_app_timer_id);
#endif

_static bool m_tx_fsm_idle_flag = true;
_static bool m_rx_fsm_idle_flag = true;

_static bool m_buffer_reqested_flag = false;

_static uint8_t * m_p_rx_buffer = NULL;
_static uint16_t  m_rx_packet_length;
_static uint8_t * m_p_rx_packet;
_static uint8_t * m_p_tx_payload = NULL;
_static uint16_t  m_tx_payload_length;

_static ser_phy_events_handler_t m_ser_phy_callback = NULL;

static void hci_tx_event_handler(hci_evt_t * p_event);
static void hci_rx_event_handler(hci_evt_t * p_event);
#ifdef HCI_LINK_CONTROL
static void hci_link_control_event_handler(hci_evt_t * p_event);
#endif /* HCI_LINK_CONTROL */

_static bool m_hci_timer_enabled_flag  = true;
_static bool m_hci_timout_pending_flag = false;
_static bool m_hci_global_enable_flag  = true;

#define ser_phy_hci_assert(cond) APP_ERROR_CHECK_BOOL(cond)

static void hci_signal_timeout_event(void)
{
    hci_evt_t event;

    event.evt_source             = HCI_TIMER_EVT;
    event.evt.timer_evt.evt_type = HCI_EVT_TIMEOUT;
    DEBUG_EVT_TIMEOUT(0);

#ifndef HCI_LINK_CONTROL
    hci_tx_event_handler(&event);
#else
    hci_link_control_event_handler(&event);
    if ((m_hci_mode == HCI_MODE_ACTIVE) && m_hci_other_side_active)
    {
        hci_tx_event_handler(&event);
    }
#endif /* HCI_LINK_CONTROL */
}


#ifndef HCI_APP_TIMER

void HCI_TIMER_IRQHandler(void)
{

    if ((HCI_TIMER->EVENTS_COMPARE[1] == 1) && (HCI_TIMER->INTENSET & TIMER_INTENSET_COMPARE1_Msk))
    {
        HCI_TIMER->EVENTS_COMPARE[1] = 0;
        HCI_TIMER->TASKS_CLEAR       = 1;

        if (m_hci_timer_enabled_flag)
        {
            hci_signal_timeout_event();
        }
        else
        {
            m_hci_timout_pending_flag = true;
        }
    }
}


static void hci_timeout_setup(uint32_t count)
{

    uint32_t time_msec;

    if (count)
    {
        HCI_TIMER->INTENCLR          = TIMER_INTENCLR_COMPARE1_Msk;
        time_msec                    = count * RETRANSMISSION_TIMEOUT_IN_ms;
        HCI_TIMER->CC[1]             = time_msec * 31;
        HCI_TIMER->CC[1]            += time_msec / 4;
        HCI_TIMER->TASKS_CLEAR       = 1; // < Clear TIMER
        HCI_TIMER->EVENTS_COMPARE[1] = 0;
        HCI_TIMER->TASKS_START       = 1; // < Start TIMER
        HCI_TIMER->INTENSET          = TIMER_INTENSET_COMPARE1_Msk;
    }
    else
    {
        HCI_TIMER->INTENCLR   = TIMER_INTENCLR_COMPARE1_Msk;
        HCI_TIMER->TASKS_STOP = 1; // < Start TIMER
    }
}


#else

_static bool     m_hci_timer_setup_flag = false;
_static uint32_t m_hci_timer_counter    = 0;
_static uint32_t m_hci_timer_setup;

static void hci_timeout_setup(uint32_t count)
{
    m_hci_timer_setup      = count;
    m_hci_timer_setup_flag = true;
}


static void hci_timeout_handler(void * p_context)
{

    if (m_hci_timer_setup_flag)
    {
        m_hci_timer_setup_flag = false;
        m_hci_timer_counter    = m_hci_timer_setup; /* for 1 it will be always more than 1 tick - jitter is up to 1 tick */
    }
    else if ( m_hci_timer_counter )
    {
        m_hci_timer_counter--;

        if (m_hci_timer_counter == 0)
        {
            if (m_hci_timer_enabled_flag)
            {
                hci_signal_timeout_event();
            }
            else
            {
                m_hci_timout_pending_flag = true;
            }
        }
    }
    return;
}


#endif


/**@brief Function for validating a received packet.
 *
 * @param[in] p_buffer Pointer to the packet data.
 * @param[in] length   Length of packet data in bytes.
 *
 * @return true if received packet is valid, false in other case.
 */
static bool is_rx_pkt_valid(const uint8_t * p_buffer, uint32_t length)
{
    // Executed packet filtering algorithm order:
    // - verify packet overall length
    // - verify data integrity bit set
    // - verify reliable packet bit set
    // - verify supported packet type
    // - verify header checksum
    // - verify payload length field
    // - verify CRC
    if (length <= PKT_HDR_SIZE)
    {
        return false;
    }

    if (!(p_buffer[0] & DATA_INTEGRITY_MASK))
    {
        return false;
    }

    if (!(p_buffer[0] & RELIABLE_PKT_MASK))
    {
        return false;
    }

    if ((p_buffer[1] & 0x0Fu) != PKT_TYPE_VENDOR_SPECIFIC)
    {
        return false;
    }

    const uint32_t expected_checksum =
        ((p_buffer[0] + p_buffer[1] + p_buffer[2] + p_buffer[3])) & 0xFFu;

    if (expected_checksum != 0)
    {
        return false;
    }

    const uint16_t crc_calculated = crc16_compute(p_buffer, (length - PKT_CRC_SIZE), NULL);
    const uint16_t crc_received   = uint16_decode(&p_buffer[length - PKT_CRC_SIZE]);

    if (crc_calculated != crc_received)
    {
        return false;
    }

    return true;
}


/**@brief Function for getting the sequence number of the next reliable packet expected.
 *
 * @return sequence number of the next reliable packet expected.
 */
static __INLINE uint8_t packet_ack_get(void)
{
    return (uint8_t) m_packet_ack_number;
}


/**@brief Function for getting the sequence number of a reliable TX packet for which peer protocol
 * entity acknowledgment is pending.
 *
 * @return sequence number of a reliable TX packet for which peer protocol entity acknowledgement
 * is pending.
 */
static __INLINE uint8_t packet_seq_get(void)
{
    return m_packet_seq_number;
}


static __INLINE uint8_t packet_seq_nmbr_extract(const uint8_t * p_buffer)
{
    return (p_buffer[0] & 0x07u);
}


/**@brief Function for constructing 1st byte of the packet header of the packet to be transmitted.
 *
 * @return 1st byte of the packet header of the packet to be transmitted
 */
static __INLINE uint8_t tx_packet_byte_zero_construct(void)
{
    const uint32_t value = DATA_INTEGRITY_MASK | RELIABLE_PKT_MASK |
                           (packet_ack_get() << 3u) | packet_seq_get();

    return (uint8_t) value;
}


/**@brief Function for calculating a packet header checksum.
 *
 * @param[in] p_hdr Pointer to the packet header.
 *
 * @return          Calculated checksum.
 */
static __INLINE uint8_t header_checksum_calculate(const uint8_t * p_hdr)
{
    // @note: no pointer validation check needed as already checked by calling function.
    uint32_t checksum;

    checksum  = p_hdr[0];
    checksum += p_hdr[1];
    checksum += p_hdr[2];
    checksum &= 0xFFu;
    checksum  = (~checksum + 1u);

    return (uint8_t)checksum;
}


/**@brief Function for getting the expected ACK number.
 *
 * @return expected ACK number.
 */
static __INLINE uint8_t expected_ack_number_get(void)
{
    uint8_t seq_nmbr = packet_seq_get();

    ++seq_nmbr;
    seq_nmbr &= 0x07u;

    return seq_nmbr;
}


/**@brief Function for getting the expected ACK number.
 *
 * @return next expected ACK number.
 */

static __INLINE uint8_t next_expected_ack_number_get(void)
{
    uint8_t seq_nmbr = expected_ack_number_get();

    ++seq_nmbr;
    seq_nmbr &= 0x07u;

    return seq_nmbr;
}


/**@brief Function for processing a received acknowledgement packet.
 *
 * Verifies does the received acknowledgement packet has the expected acknowledgement number and
 * that the header checksum is correct.
 *
 * @param[in] p_buffer Pointer to the packet data.
 *
 * @return true if valid acknowledgement packet received.
 */

static bool rx_ack_pkt_valid(const uint8_t * p_buffer)
{
    // @note: no pointer validation check needed as allready checked by calling function.

    // Verify header checksum.
    const uint32_t expected_checksum =
        ((p_buffer[0] + p_buffer[1] + p_buffer[2] + p_buffer[3])) & 0xFFu;

    if (expected_checksum != 0)
    {
        return false;
    }

    const uint8_t ack_number = (p_buffer[0] >> 3u) & 0x07u;

    // Verify expected acknowledgment number.
    return ( (ack_number == expected_ack_number_get()) ||
             (ack_number == next_expected_ack_number_get()) );
}


/**@brief Function for decoding a packet type field.
 *
 * @param[in] p_buffer Pointer to the packet data.
 * @param[in] length   Length of packet data in bytes.
 *
 * @return Packet type field or INVALID_PKT_TYPE in case of decode error.
 */

static uint32_t packet_type_decode(const uint8_t * p_buffer, uint32_t length)
{
    // @note: no pointer validation check needed as allready checked by calling function.
    uint32_t return_value;

    if (length >= PKT_HDR_SIZE)
    {
        return_value = (p_buffer[1] & 0x0Fu);
    }
    else
    {
        return_value = INVALID_PKT_TYPE;
    }

    return return_value;
}

#ifdef HCI_LINK_CONTROL
/**@brief Function for decoding a link control packet.
 *
 * @param[in] p_buffer    Pointer to the packet data.
 * @param[in] length      Length of packet data in bytes.
 *
 * @return Link Control Packet Type if decoding successful, HCI_LINK_CONTROL_PKT_INVALID otherwise.
 */
static uint16_t link_control_packet_decode(const uint8_t * p_buffer, uint32_t length)
{
    // @note: no pointer validation check needed as allready checked by calling function.
    uint16_t packet_type = HCI_LINK_CONTROL_PKT_INVALID;

 // Executed link control packet filtering algorithm order:
    // - verify packet overall length
    // - verify data integrity bit cleared
    // - verify reliable packet bit cleared
    // - verify header checksum
    // - verify payload: length and value

    if (length < HCI_PKT_SYNC_SIZE)
    {
        packet_type = HCI_LINK_CONTROL_PKT_INVALID;
    }

    packet_type = p_buffer[PKT_HDR_SIZE] | (p_buffer[PKT_HDR_SIZE + 1] << 8u);

    if ((p_buffer[0] & DATA_INTEGRITY_MASK) || (p_buffer[0] & RELIABLE_PKT_MASK))
    {
        packet_type = HCI_LINK_CONTROL_PKT_INVALID;
    }

    const uint32_t expected_checksum =
        ((p_buffer[0] + p_buffer[1] + p_buffer[2] + p_buffer[3])) & 0xFFu;

    if (expected_checksum != 0)
    {
        packet_type = HCI_LINK_CONTROL_PKT_INVALID;
    }

    // This is a CONFIG or CONFIG_RSP packet
    if ((packet_type == HCI_PKT_CONFIG) || (packet_type == HCI_PKT_CONFIG_RSP))
    {
        if (length != HCI_PKT_CONFIG_SIZE)
        {
            packet_type = HCI_LINK_CONTROL_PKT_INVALID;
        }
        // Verify configuration field (0x11):
        // - Sliding Window Size       == 1,
        // - OOF Flow Control          == 0,
        // - Data Integrity Check Type == 1,
        // - Version Number            == 0
        if (p_buffer[HCI_PKT_CONFIG_SIZE - 1] != HCI_CONFIG_FIELD)
        {
            packet_type = HCI_LINK_CONTROL_PKT_INVALID;
        }
    }
    // This is a SYNC or SYNC_RSP packet
    else if ((packet_type == HCI_PKT_SYNC) || (packet_type == HCI_PKT_SYNC_RSP))
    {
        if (length != HCI_PKT_SYNC_SIZE)
        {
            packet_type = HCI_LINK_CONTROL_PKT_INVALID;
        }
    }
    else
    {
        packet_type = HCI_LINK_CONTROL_PKT_INVALID;
    }

    return packet_type;
}
#endif /* HCI_LINK_CONTROL */

/**@brief Function for writing an acknowledgment packet for transmission.
 */

static void ack_transmit(void)
{
    uint32_t err_code;
    // TX ACK packet format:
    // - Unreliable Packet type
    // - Payload Length set to 0
    // - Sequence Number set to 0
    // - Header checksum calculated
    // - Acknowledge Number set correctly
    m_tx_ack_packet[0] = (packet_ack_get() << 3u);
    m_tx_ack_packet[1] = 0;
    m_tx_ack_packet[2] = 0;
    m_tx_ack_packet[3] = header_checksum_calculate(m_tx_ack_packet);

    ser_phy_hci_pkt_params_t pkt_header;

    pkt_header.p_buffer     = m_tx_ack_packet;
    pkt_header.num_of_bytes = PKT_HDR_SIZE;
    DEBUG_EVT_SLIP_ACK_TX(0);
    err_code = ser_phy_hci_slip_tx_pkt_send(&pkt_header, NULL, NULL);
    NRF_LOG_DEBUG("Start sending ACK.");
    ser_phy_hci_assert(err_code == NRF_SUCCESS);

    return;
}


static void ser_phy_event_callback(ser_phy_evt_t event)
{
    if (m_ser_phy_callback)
    {
        m_ser_phy_callback(event);
    }

    return;
}


static void memory_request_callback(uint16_t size)
{
    ser_phy_evt_t event;

    DEBUG_EVT_HCI_PHY_EVT_BUF_REQUEST(0);

    event.evt_type                               = SER_PHY_EVT_RX_BUF_REQUEST;
    event.evt_params.rx_buf_request.num_of_bytes = size;
    ser_phy_event_callback(event);
}


static void packet_received_callback(uint8_t * pBuffer, uint16_t size)
{
    ser_phy_evt_t event;

    DEBUG_EVT_HCI_PHY_EVT_RX_PKT_RECEIVED(0);

    event.evt_type = SER_PHY_EVT_RX_PKT_RECEIVED;
    event.evt_params.rx_pkt_received.num_of_bytes = size;
    event.evt_params.rx_pkt_received.p_buffer     = pBuffer;
    ser_phy_event_callback(event);
}


static void packet_dropped_callback(void)
{
    ser_phy_evt_t event;

    DEBUG_EVT_HCI_PHY_EVT_RX_PKT_DROPPED(0);

    event.evt_type = SER_PHY_EVT_RX_PKT_DROPPED;
    ser_phy_event_callback(event);
}


static void packet_transmitted_callback(void)
{
    ser_phy_evt_t event;

    DEBUG_EVT_HCI_PHY_EVT_TX_PKT_SENT(0);

    event.evt_type = SER_PHY_EVT_TX_PKT_SENT;
    ser_phy_event_callback(event);
}


static void error_callback(void)
{
    ser_phy_evt_t event;

    DEBUG_EVT_HCI_PHY_EVT_TX_ERROR(0);

    NRF_LOG_DEBUG("no ack");
    event.evt_type = SER_PHY_EVT_HW_ERROR;
    event.evt_params.hw_error.p_buffer = m_p_tx_payload;
    ser_phy_event_callback(event);
}

static void hci_slip_event_handler(ser_phy_hci_slip_evt_t * p_event)
{
    hci_evt_t event;
    uint32_t  packet_type;
    uint32_t  err_code;

    if ( p_event->evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT )
    {
        NRF_LOG_DEBUG("EVT:Tx packet sent.");

        DEBUG_EVT_SLIP_PACKET_TXED(0);
        event.evt_source                    = HCI_SLIP_EVT;
        event.evt.ser_phy_slip_evt.evt_type = p_event->evt_type;
#ifndef HCI_LINK_CONTROL
        hci_tx_event_handler(&event);
#else
        if ((m_hci_mode == HCI_MODE_ACTIVE) && m_hci_other_side_active)
        {
            hci_tx_event_handler(&event);
        }
#endif /*HCI_LINK_CONTROL*/
    }
    else if ( p_event->evt_type == SER_PHY_HCI_SLIP_EVT_ACK_SENT )
    {
        NRF_LOG_DEBUG("EVT:ACK sent.");

        DEBUG_EVT_SLIP_ACK_TXED(0);
        event.evt_source                    = HCI_SLIP_EVT;
        event.evt.ser_phy_slip_evt.evt_type = p_event->evt_type;
#ifndef HCI_LINK_CONTROL
        hci_rx_event_handler(&event);
#else
        if ((m_hci_mode == HCI_MODE_ACTIVE) && m_hci_other_side_active)
        {
            hci_rx_event_handler(&event);
        }
#endif /* HCI_LINK_CONTROL */
    }

    else if ( p_event->evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED )
    {
        event.evt_source = HCI_SLIP_EVT;
        event.evt.ser_phy_slip_evt.evt_type                         = p_event->evt_type;
        event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer =
            p_event->evt_params.received_pkt.p_buffer;
        event.evt.ser_phy_slip_evt.evt_params.received_pkt.num_of_bytes =
            p_event->evt_params.received_pkt.num_of_bytes;
        ser_phy_hci_assert(event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer != NULL);
        ser_phy_hci_assert(event.evt.ser_phy_slip_evt.evt_params.received_pkt.num_of_bytes != 0);
        packet_type = packet_type_decode(
            event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer,
            event.evt.ser_phy_slip_evt.evt_params.received_pkt.num_of_bytes);

        NRF_LOG_DEBUG("EVT:RX %s packet (length:%u)", PACKET_TYPE_STR(packet_type),
            p_event->evt_params.received_pkt.num_of_bytes);

        if (packet_type == PKT_TYPE_RESET)
        {
#if defined(SER_CONNECTIVITY) && defined(SER_PHY_HCI_USB_CDC)
            (void)soft_reset_trigger();
#else
            NVIC_SystemReset();
#endif
        }
        else if (packet_type == PKT_TYPE_ACK )
        {
            DEBUG_EVT_SLIP_ACK_RXED(0);
#ifndef HCI_LINK_CONTROL
            hci_tx_event_handler(&event);
#else
            if ((m_hci_mode == HCI_MODE_ACTIVE) && m_hci_other_side_active)
            {
                hci_tx_event_handler(&event);
            }
            else
            {
                err_code = ser_phy_hci_slip_rx_buf_free(
                      event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            }
#endif /* HCI_LINK_CONTROL */
        }
        else if ( packet_type == PKT_TYPE_VENDOR_SPECIFIC )
        {
            if (is_rx_pkt_valid(event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer,
                                event.evt.ser_phy_slip_evt.evt_params.received_pkt.num_of_bytes))
            {
                DEBUG_EVT_SLIP_PACKET_RXED(0);
#ifndef HCI_LINK_CONTROL
                hci_rx_event_handler(&event);
#else
                if ((m_hci_mode == HCI_MODE_ACTIVE) && m_hci_other_side_active)
                {
                    hci_rx_event_handler(&event);
                }
                else
                {
                    err_code = ser_phy_hci_slip_rx_buf_free(
                                    event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
                }
#endif /* HCI_LINK_CONTROL */
            }
            else
            {
                err_code = ser_phy_hci_slip_rx_buf_free(
                    event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
                ser_phy_hci_assert(err_code == NRF_SUCCESS);
                /* throw assert when in debug mode*/
                DEBUG_EVT_SLIP_ERR_RXED(0);
            }
        }
#ifdef HCI_LINK_CONTROL
        else if (packet_type == PKT_TYPE_LINK_CONTROL)
        {
            hci_link_control_event_handler(&event);
        }
#endif /* HCI_LINK_CONTROL */
        else
        {
            err_code = ser_phy_hci_slip_rx_buf_free(
                event.evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            ser_phy_hci_assert(err_code == NRF_SUCCESS);
            /* throw assert when in debug mode*/
            DEBUG_EVT_SLIP_ERR_RXED(0);
        }
    }
    else
    {
        NRF_LOG_DEBUG("EVT_HW_ERROR");
    }
}


static void hci_pkt_send(void)
{
    uint32_t err_code;

    m_tx_packet_header[0] = tx_packet_byte_zero_construct();
    uint16_t type_and_length_fields = ((m_tx_payload_length << 4u) | PKT_TYPE_VENDOR_SPECIFIC);
    (void)uint16_encode(type_and_length_fields, &(m_tx_packet_header[1]));
    m_tx_packet_header[3] = header_checksum_calculate(m_tx_packet_header);
    uint16_t crc = crc16_compute(m_tx_packet_header, PKT_HDR_SIZE, NULL);
    crc = crc16_compute(m_p_tx_payload, m_tx_payload_length, &crc);
    (void)uint16_encode(crc, m_tx_packet_crc);

    ser_phy_hci_pkt_params_t pkt_header;
    ser_phy_hci_pkt_params_t pkt_payload;
    ser_phy_hci_pkt_params_t pkt_crc;

    pkt_header.p_buffer      = m_tx_packet_header;
    pkt_header.num_of_bytes  = PKT_HDR_SIZE;
    pkt_payload.p_buffer     = m_p_tx_payload;
    pkt_payload.num_of_bytes = m_tx_payload_length;
    pkt_crc.p_buffer         = m_tx_packet_crc;
    pkt_crc.num_of_bytes     = PKT_CRC_SIZE;
    DEBUG_EVT_SLIP_PACKET_TX(0);
    err_code = ser_phy_hci_slip_tx_pkt_send(&pkt_header, &pkt_payload, &pkt_crc);
    NRF_LOG_DEBUG("Started TX packet (payload %d).", m_tx_payload_length);
    ser_phy_hci_assert(err_code == NRF_SUCCESS);

    return;
}

#ifdef HCI_LINK_CONTROL
static void hci_link_control_pkt_send(void)
{
    uint32_t err_code;
    uint16_t link_control_payload_len = 0;

    m_tx_link_control_header[0] = 0x00u;       // SEQ, ACK, DI and RP are set to 0 for link control
    if (m_hci_link_control_next_pkt == HCI_PKT_SYNC)
    {
        link_control_payload_len = HCI_PKT_SYNC_SIZE - PKT_HDR_SIZE;
        (void)uint16_encode(HCI_PKT_SYNC, m_tx_link_control_payload);
    }
    else if (m_hci_link_control_next_pkt == HCI_PKT_SYNC_RSP)
    {
        link_control_payload_len = HCI_PKT_SYNC_SIZE - PKT_HDR_SIZE;
        (void)uint16_encode(HCI_PKT_SYNC_RSP, m_tx_link_control_payload);
    }
    else if (m_hci_link_control_next_pkt == HCI_PKT_CONFIG)
    {
        link_control_payload_len = HCI_PKT_CONFIG_SIZE - PKT_HDR_SIZE;
        (void)uint16_encode(HCI_PKT_CONFIG, m_tx_link_control_payload);
        m_tx_link_control_payload[2] = HCI_CONFIG_FIELD;
    }
    else if (m_hci_link_control_next_pkt == HCI_PKT_CONFIG_RSP)
    {
        link_control_payload_len = HCI_PKT_CONFIG_SIZE - PKT_HDR_SIZE;
        (void)uint16_encode(HCI_PKT_CONFIG_RSP, m_tx_link_control_payload);
        m_tx_link_control_payload[2] = HCI_CONFIG_FIELD;
    }
    uint16_t type_and_length_fields = ((link_control_payload_len << 4u) | PKT_TYPE_LINK_CONTROL);
    (void)uint16_encode(type_and_length_fields, &(m_tx_link_control_header[1]));
    m_tx_link_control_header[3] = header_checksum_calculate(m_tx_link_control_header);

    ser_phy_hci_pkt_params_t pkt_header;
    ser_phy_hci_pkt_params_t pkt_payload;
    ser_phy_hci_pkt_params_t pkt_crc;

    pkt_header.p_buffer      = m_tx_link_control_header;
    pkt_header.num_of_bytes  = PKT_HDR_SIZE;
    pkt_payload.p_buffer     = m_tx_link_control_payload;
    pkt_payload.num_of_bytes = link_control_payload_len;
    pkt_crc.p_buffer         = NULL;
    pkt_crc.num_of_bytes     = 0;
    DEBUG_EVT_SLIP_PACKET_TX(0);
    err_code = ser_phy_hci_slip_tx_pkt_send(&pkt_header, &pkt_payload, &pkt_crc);
    ser_phy_hci_assert(err_code == NRF_SUCCESS);

    return;
}
#endif /* HCI_LINK_CONTROL */

static void hci_pkt_sent_upcall(void)
{
    m_packet_seq_number++; // incoming ACK is valid, increment SEQ
    m_packet_seq_number &= 0x07u;
    m_p_tx_payload       = NULL;
    packet_transmitted_callback();

    return;
}


static void hci_release_ack_buffer(hci_evt_t * p_event)
{
    uint32_t err_code;

    err_code = ser_phy_hci_slip_rx_buf_free(
        p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
    ser_phy_hci_assert(err_code == NRF_SUCCESS);

    return;
}


static void hci_process_orphaned_ack(hci_evt_t * p_event)
{
    hci_release_ack_buffer(p_event);
    return;
}

/* main tx fsm   */
static void hci_tx_fsm_event_process(hci_evt_t * p_event)
{

    switch (m_hci_tx_fsm_state)
    {
        case HCI_TX_STATE_SEND:

            if ((p_event->evt_source == HCI_SER_PHY_EVT) &&
                (p_event->evt.ser_phy_evt.evt_type == HCI_SER_PHY_TX_REQUEST))
            {
                hci_pkt_send();
                hci_timeout_setup(0);
                m_tx_retry_count   = MAX_RETRY_COUNT;
                m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_FIRST_TX_END;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                hci_process_orphaned_ack(p_event);
            }

            break;

        case HCI_TX_STATE_WAIT_FOR_FIRST_TX_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT))
            {
                hci_timeout_setup(1);
                m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_ACK;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                hci_process_orphaned_ack(p_event);
            }
            break;

        case HCI_TX_STATE_WAIT_FOR_ACK_OR_TX_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT))
            {
                hci_timeout_setup(1);
                m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_ACK;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                if (rx_ack_pkt_valid(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer))
                {
                    hci_timeout_setup(0);
                    m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_TX_END;
                }
                hci_release_ack_buffer(p_event);
            }
            break;

        case HCI_TX_STATE_WAIT_FOR_ACK:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                if (rx_ack_pkt_valid(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer))
                {
                    hci_timeout_setup(0);
                    hci_pkt_sent_upcall();
                    m_hci_tx_fsm_state = HCI_TX_STATE_SEND;
                }
                hci_release_ack_buffer(p_event);
            }
            else if (p_event->evt_source == HCI_TIMER_EVT)
            {
                m_tx_retry_count--;
                // m_tx_retx_counter++; // global retransmissions counter
                if (m_tx_retry_count)
                {
                    NRF_LOG_DEBUG("Timeout, no ACK. Retrying tx packet.");
                    hci_pkt_send();
                    DEBUG_HCI_RETX(0);
                    m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_ACK_OR_TX_END;
                }
                else
                {
                    error_callback();
                    m_hci_tx_fsm_state = HCI_TX_STATE_SEND;
                    NRF_LOG_WARNING("Timeout, no ACK. Dropping.");
                }
            }
            break;

        case HCI_TX_STATE_WAIT_FOR_TX_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT))
            {
                hci_pkt_sent_upcall();
                m_hci_tx_fsm_state = HCI_TX_STATE_SEND;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                hci_process_orphaned_ack(p_event);
            }

            break;

#ifdef HCI_LINK_CONTROL
        case HCI_TX_STATE_DISABLE:
            /* This case should not happen if HCI is in ACTIVE mode */
            if (m_hci_mode == HCI_MODE_ACTIVE)
            {
                ser_phy_hci_assert(false);
            }
            break;
#endif /* HCI_LINK_CONTROL */

        default:
            ser_phy_hci_assert(false);
            break;
    }
}


static void hci_mem_request(hci_evt_t * p_event)
{
    m_buffer_reqested_flag = true;
    m_p_rx_packet          = p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer;
    m_rx_packet_length     = p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.num_of_bytes;
    ser_phy_hci_assert(m_rx_packet_length > PKT_HDR_SIZE + PKT_CRC_SIZE);
    memory_request_callback(m_rx_packet_length - PKT_HDR_SIZE - PKT_CRC_SIZE);
    return;
}


static void hci_inc_ack()
{
    m_packet_ack_number++;
    m_packet_ack_number &= 0x07u;
}


static void hci_rx_fsm_event_process(hci_evt_t * p_event)
{
    switch (m_hci_rx_fsm_state)
    {
        case HCI_RX_STATE_RECEIVE:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                /* type and crc and check sum are validated by slip handler */
                uint8_t rx_seq_number = packet_seq_nmbr_extract(
                    p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);

                if (packet_ack_get() == rx_seq_number)
                {
                    hci_mem_request(p_event);
                    m_hci_rx_fsm_state = HCI_RX_STATE_WAIT_FOR_MEM;
                }
                else
                {
                    // m_rx_drop_counter++;
                    m_hci_rx_fsm_state = HCI_RX_STATE_WAIT_FOR_SLIP_NACK_END;
                    (void) ser_phy_hci_slip_rx_buf_free(m_p_rx_packet); // and drop a packet
                    ack_transmit();                                     // send NACK with valid ACK
                }
            }
            break;

        case HCI_RX_STATE_WAIT_FOR_MEM:

            if ((p_event->evt_source == HCI_SER_PHY_EVT) &&
                (p_event->evt.ser_phy_evt.evt_type == HCI_SER_PHY_RX_BUF_GRANTED))
            {
                if (m_p_rx_buffer)
                {
                    memcpy(m_p_rx_buffer,
                           m_p_rx_packet + PKT_HDR_SIZE,
                           m_rx_packet_length - PKT_HDR_SIZE - PKT_CRC_SIZE);
                    (void) ser_phy_hci_slip_rx_buf_free(m_p_rx_packet);
                }
                m_hci_rx_fsm_state = HCI_RX_STATE_WAIT_FOR_SLIP_ACK_END;
                hci_inc_ack(); // SEQ was valid for good packet, we will send incremented SEQ as ACK
                ack_transmit();
            }

            break;

        case HCI_RX_STATE_WAIT_FOR_SLIP_ACK_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_ACK_SENT))
            {

                if (m_p_rx_buffer)
                {
                    packet_received_callback(m_p_rx_buffer,
                                             m_rx_packet_length - PKT_HDR_SIZE - PKT_CRC_SIZE);
                }
                else
                {
                    packet_dropped_callback();
                }
                m_hci_rx_fsm_state = HCI_RX_STATE_RECEIVE;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                    (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                (void) ser_phy_hci_slip_rx_buf_free(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            }
            break;

        case HCI_RX_STATE_WAIT_FOR_SLIP_NACK_END:
            if ((p_event->evt_source == HCI_SLIP_EVT) &&
               (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_ACK_SENT))
            {
               m_hci_rx_fsm_state = HCI_RX_STATE_RECEIVE;
            }
            else
            {
               (void) ser_phy_hci_slip_rx_buf_free(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            }
            break;


#ifdef HCI_LINK_CONTROL
        case HCI_RX_STATE_DISABLE:
            if (m_hci_mode == HCI_MODE_ACTIVE)
            {
                ser_phy_hci_assert(false);
            }
            break;
#endif /* HCI_LINK_CONTROL */

        default:
            ser_phy_hci_assert(false);
            break;
    }
}


/* this function might be entered only via hci_tx_event_handler */
static void hci_tx_fsm(void)
{
    hci_evt_t event;
    uint32_t  err_code = NRF_SUCCESS;

    while (err_code == NRF_SUCCESS)
    {

        CRITICAL_REGION_ENTER();
        err_code = nrf_queue_pop(&m_tx_evt_queue, &event);

        if (err_code != NRF_SUCCESS)
        {
            m_tx_fsm_idle_flag = true;
        }
        CRITICAL_REGION_EXIT();

        if (err_code == NRF_SUCCESS)
        {
            hci_tx_fsm_event_process(&event); /* this is the only entry to the TX_FSM */
        }
    }
    return;
}


/* this function might be entered only via hci_rx_event_handler */
static void hci_rx_fsm(void)
{
    hci_evt_t event;
    uint32_t  err_code = NRF_SUCCESS;

    while (err_code == NRF_SUCCESS)
    {
        CRITICAL_REGION_ENTER();
        err_code = nrf_queue_pop(&m_rx_evt_queue, &event);

        if (err_code != NRF_SUCCESS)
        {
            m_rx_fsm_idle_flag = true;
        }
        CRITICAL_REGION_EXIT();

        if (err_code == NRF_SUCCESS)
        {
            hci_rx_fsm_event_process(&event); /* this is the only entry to the RX_FSM */
        }
    }
    return;
}


/* something might have been queued by API with disabled 'PHY-interrupts' */
static void hci_tx_reschedule()
{
    bool     tx_exec_flag = false;
    uint32_t tx_queue_length;

    CRITICAL_REGION_ENTER();
    tx_queue_length = nrf_queue_utilization_get(&m_tx_evt_queue);

#ifndef HCI_LINK_CONTROL
    if (m_tx_fsm_idle_flag && m_hci_global_enable_flag && tx_queue_length)
#else
    if (m_tx_fsm_idle_flag && m_hci_global_enable_flag && tx_queue_length && (m_hci_mode == HCI_MODE_ACTIVE))
#endif /* HCI_LINK_CONTROL */
    {
        tx_exec_flag       = true;  // FSM should be activated
        m_tx_fsm_idle_flag = false; // FSM will be busy from now on till the queue is exhausted
    }
    CRITICAL_REGION_EXIT();

    if (tx_exec_flag)
    {
        hci_tx_fsm();
    }
    return;
}


/* entry to TX state machine, might be called asynchronously from different contexts */
/* Puts event into the TX event queue and execute if FSM was idle */
static void hci_tx_event_handler(hci_evt_t * p_event)
{
    bool     tx_exec_flag = false;
    uint32_t err_code;

    CRITICAL_REGION_ENTER();
    err_code = nrf_queue_push(&m_tx_evt_queue, p_event);
    ser_phy_hci_assert(err_code == NRF_SUCCESS);

    // CRITICAL_REGION_ENTER();
    /* only one process can acquire tx_exec_flag */
    if (m_tx_fsm_idle_flag && m_hci_global_enable_flag)
    {
        tx_exec_flag       = true;  // FSM should be activated
        m_tx_fsm_idle_flag = false; // FSM will be busy from now on till the queue is exhausted
    }
    CRITICAL_REGION_EXIT();

    if (tx_exec_flag)
    {
        hci_tx_fsm();
    }
    return;
}


/* Something might have been queued by API with disabled 'PHY-interrupts' */
static void hci_rx_reschedule()
{
    bool     rx_exec_flag = false;
    uint32_t rx_queue_length;

    CRITICAL_REGION_ENTER();
    rx_queue_length = nrf_queue_utilization_get(&m_rx_evt_queue);

#ifndef HCI_LINK_CONTROL
    if (m_rx_fsm_idle_flag && m_hci_global_enable_flag && rx_queue_length)
#else
    if (m_rx_fsm_idle_flag && m_hci_global_enable_flag && rx_queue_length && (m_hci_mode == HCI_MODE_ACTIVE))
#endif /* HCI_LINK_CONTROL */
    {
        rx_exec_flag       = true;  // FSM should be activated
        m_rx_fsm_idle_flag = false; // FSM will be busy from now on till the queue is exhausted
    }
    CRITICAL_REGION_EXIT();

    if (rx_exec_flag)
    {
        hci_rx_fsm();
    }

}


/* Entry to RX state machine, might be called asynchronously from different contexts */
/* Puts event into the RX event queue and execute if FSM was idle */
static void hci_rx_event_handler(hci_evt_t * p_event)
{
    bool     rx_exec_flag = false;
    uint32_t err_code;

    CRITICAL_REGION_ENTER();
    err_code = nrf_queue_push(&m_rx_evt_queue, p_event);
    ser_phy_hci_assert(err_code == NRF_SUCCESS);

    /* only one process can acquire rx_exec_flag */
    // CRITICAL_REGION_ENTER();
    if (m_rx_fsm_idle_flag && m_hci_global_enable_flag)
    {
        rx_exec_flag       = true;  // FSM should be activated
        m_rx_fsm_idle_flag = false; // FSM will be busy from now on till the queue is exhausted
    }
    CRITICAL_REGION_EXIT();

    if (rx_exec_flag)
    {
        hci_rx_fsm();
    }

    return;
}

#ifdef HCI_LINK_CONTROL
/* Link control event handler - used only for Link Control packets */
/* This handler will be called only in 2 cases:
   - when SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED event is received
   - when HCI_TIMER_EVT event is reveived */
static void hci_link_control_event_handler(hci_evt_t * p_event)
{
    uint16_t pkt_type = HCI_LINK_CONTROL_PKT_INVALID;

    switch (p_event->evt_source)
    {
        case HCI_SLIP_EVT:
            pkt_type = link_control_packet_decode(
                            p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer,
                            p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.num_of_bytes);
            /* Perform HCI mode transition if needed */
            CRITICAL_REGION_ENTER();
            switch (pkt_type)
            {
                case HCI_PKT_SYNC:
                    m_hci_link_control_next_pkt = HCI_PKT_SYNC_RSP;
                    /* Restart HCI communication if it was in ACTIVE mode */
                    if (m_hci_mode == HCI_MODE_ACTIVE)
                    {
                        m_hci_mode          = HCI_MODE_UNINITIALIZED;
                        m_packet_ack_number = INITIAL_ACK_NUMBER_EXPECTED;
                        m_packet_seq_number = INITIAL_SEQ_NUMBER;
                        m_hci_tx_fsm_state  = HCI_TX_STATE_DISABLE;
                        m_hci_rx_fsm_state  = HCI_RX_STATE_DISABLE;
                        m_hci_other_side_active = false;
                    }
                    NRF_LOG_DEBUG("Link control. Sync received, sending Sync Response.");
                    hci_link_control_pkt_send();
                    hci_timeout_setup(HCI_LINK_CONTROL_TIMEOUT); // Need to trigger transmitting SYNC messages
                    break;
                case HCI_PKT_SYNC_RSP:
                    if (m_hci_mode == HCI_MODE_UNINITIALIZED)
                    {
                        m_hci_mode                  = HCI_MODE_INITIALIZED;
                        m_hci_link_control_next_pkt = HCI_PKT_CONFIG;
                        m_cfg_sent = false;
                    }
                    NRF_LOG_DEBUG("Link control. Sync Resposnse recieved.");
                    break;
                case HCI_PKT_CONFIG:
                    if (m_hci_mode != HCI_MODE_UNINITIALIZED)
                    {
                        if (m_cfg_sent)
                        {
                            m_hci_link_control_next_pkt = HCI_PKT_CONFIG_RSP;
                            m_hci_other_side_active = true;
                        }
                        else
                        {
                            m_hci_link_control_next_pkt = HCI_PKT_CONFIG;
                        }
                        hci_link_control_pkt_send();
                        m_cfg_sent = true;
                    }
                    break;
                case HCI_PKT_CONFIG_RSP:
                    if (m_hci_mode == HCI_MODE_INITIALIZED)
                    {
                        m_hci_mode          = HCI_MODE_ACTIVE;
                        m_hci_tx_fsm_state  = HCI_TX_STATE_SEND;
                        m_hci_rx_fsm_state  = HCI_RX_STATE_RECEIVE;
                    }
                    break;
            }
            CRITICAL_REGION_EXIT();
            (void) ser_phy_hci_slip_rx_buf_free(
                p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            /* Kick the state machine so it can start process BLE packets */
            if ((m_hci_mode == HCI_MODE_ACTIVE) && m_hci_other_side_active)
            {
                hci_tx_reschedule();
                hci_rx_reschedule();
            }
            break;

        case HCI_TIMER_EVT:
            /* Send one of the Link Control packets if in Unintialized or Initialized state */
            CRITICAL_REGION_ENTER();
            switch (m_hci_mode)
            {
                case HCI_MODE_UNINITIALIZED:
                    //send packet
                    m_hci_link_control_next_pkt = HCI_PKT_SYNC;
                    hci_link_control_pkt_send();
                    hci_timeout_setup(HCI_LINK_CONTROL_TIMEOUT);
                    break;
                case HCI_MODE_INITIALIZED:
                    m_hci_link_control_next_pkt = HCI_PKT_CONFIG;
                    hci_link_control_pkt_send();
                    m_cfg_sent = true;
                    hci_timeout_setup(HCI_LINK_CONTROL_TIMEOUT);
                    break;
                case HCI_MODE_ACTIVE:
                case HCI_MODE_DISABLE:
                default:
                    // No implementation needed
                    break;
            }
            CRITICAL_REGION_EXIT();
            break;
        case HCI_SER_PHY_EVT:
        default:
            // No implementation needed
            break;
    }
}
#endif /* HCI_LINK_CONTROL */

/* ser_phy API function */
void ser_phy_interrupts_enable(void)
{
    bool pending_timer_callback_flag = false;

    CRITICAL_REGION_ENTER();
    m_hci_timer_enabled_flag = true;

    if (m_hci_timout_pending_flag)
    {
        m_hci_timout_pending_flag   = false;
        pending_timer_callback_flag = true;
    }
    CRITICAL_REGION_EXIT();
    // this is a workaround - scheduled SER_PHY EVENTS
    m_hci_global_enable_flag = true;
    hci_tx_reschedule();
    hci_rx_reschedule();

    if (pending_timer_callback_flag)
    {
        hci_signal_timeout_event();
    }

    return;
}


/* ser_phy API function */
void ser_phy_interrupts_disable(void)
{
    CRITICAL_REGION_ENTER();
    m_hci_timer_enabled_flag = false;
    // transport calls PHY API with ser_phy_interrupts_disabled
    m_hci_global_enable_flag = false;
    CRITICAL_REGION_EXIT();
}


/* ser_phy API function */
uint32_t ser_phy_rx_buf_set(uint8_t * p_buffer)
{
    uint32_t  status = NRF_SUCCESS;
    hci_evt_t event;

    if (m_buffer_reqested_flag)
    {
        m_buffer_reqested_flag         = false;
        m_p_rx_buffer                  = p_buffer;
        event.evt_source               = HCI_SER_PHY_EVT;
        event.evt.ser_phy_evt.evt_type = HCI_SER_PHY_RX_BUF_GRANTED;
        hci_rx_event_handler(&event);
    }
    else
    {
        status = NRF_ERROR_BUSY;
    }
    return status;
}


/* ser_phy API function */
uint32_t ser_phy_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes)
{
    NRF_LOG_DEBUG("TX request (%d bytes)", num_of_bytes);
    uint32_t  status = NRF_SUCCESS;
    hci_evt_t event;

    if ( p_buffer == NULL || num_of_bytes == 0)
    {
        return NRF_ERROR_NULL;
    }

    if ( m_p_tx_payload == NULL)
    {
        m_tx_payload_length = num_of_bytes;
        m_p_tx_payload      = (uint8_t *)p_buffer;
        DEBUG_EVT_TX_REQ(0);
        event.evt_source               = HCI_SER_PHY_EVT;
        event.evt.ser_phy_evt.evt_type = HCI_SER_PHY_TX_REQUEST;
        hci_tx_event_handler(&event);
    }
    else
    {
        status = NRF_ERROR_BUSY;
    }

    return status;
}

static uint32_t hci_timer_reset(void)
{
#ifdef HCI_APP_TIMER
    ret_code_t err_code = app_timer_stop(m_app_timer_id);

    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    err_code = app_timer_start(m_app_timer_id, RETRANSMISSION_TIMEOUT_IN_TICKS, NULL);

    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
#else

    // Configure TIMER for compare[1] event
    HCI_TIMER->PRESCALER = 9;
    HCI_TIMER->MODE      = TIMER_MODE_MODE_Timer;
    HCI_TIMER->BITMODE   = TIMER_BITMODE_BITMODE_16Bit;

    // Clear TIMER
    HCI_TIMER->TASKS_CLEAR = 1;
    HCI_TIMER->TASKS_STOP = 1;

    // Enable interrupt
    HCI_TIMER->INTENCLR = 0xFFFFFFFF;
    HCI_TIMER->INTENSET = TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos;

    NVIC_ClearPendingIRQ(HCI_TIMER_IRQn);
    NVIC_SetPriority(HCI_TIMER_IRQn, APP_IRQ_PRIORITY_HIGH);
    NVIC_EnableIRQ(HCI_TIMER_IRQn);

#endif
    return NRF_SUCCESS;
}

static uint32_t  hci_timer_init(void)
{

#ifdef HCI_APP_TIMER
    uint32_t err_code = NRF_SUCCESS;

    err_code = app_timer_create(&m_app_timer_id, APP_TIMER_MODE_REPEATED, hci_timeout_handler);

    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
#endif
    return hci_timer_reset();
}

void ser_phy_hci_reset(void)
{
    m_p_tx_payload = NULL;
    m_p_rx_buffer = NULL;
    
    nrf_queue_reset(&m_tx_evt_queue);
    nrf_queue_reset(&m_rx_evt_queue);

    (void)hci_timer_reset();
    m_packet_ack_number = INITIAL_ACK_NUMBER_EXPECTED;
    m_packet_seq_number = INITIAL_SEQ_NUMBER;

#ifndef HCI_LINK_CONTROL
    m_hci_tx_fsm_state  = HCI_TX_STATE_SEND;
    m_hci_rx_fsm_state  = HCI_RX_STATE_RECEIVE;
#else
    m_hci_tx_fsm_state  = HCI_TX_STATE_DISABLE;
    m_hci_rx_fsm_state  = HCI_RX_STATE_DISABLE;
    hci_timeout_setup(HCI_LINK_CONTROL_TIMEOUT);// Trigger sending SYNC messages
    m_hci_link_control_next_pkt = HCI_PKT_SYNC;
    m_hci_mode              = HCI_MODE_UNINITIALIZED;
    m_hci_other_side_active = false;
    m_rx_fsm_idle_flag = true;
    m_hci_global_enable_flag = true;
#endif /*HCI_LINK_CONTROL*/
}

/* ser_phy API function */
uint32_t ser_phy_open(ser_phy_events_handler_t events_handler)
{
    uint32_t err_code;

    if ((m_hci_tx_fsm_state != HCI_TX_STATE_DISABLE) || (m_hci_rx_fsm_state != HCI_RX_STATE_DISABLE))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (events_handler == NULL)
    {
        return NRF_ERROR_NULL;
    }

    m_ser_phy_callback  = events_handler;

    err_code = hci_timer_init();

    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    err_code = ser_phy_hci_slip_open(hci_slip_event_handler);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (err_code == NRF_SUCCESS)
    {
        ser_phy_hci_reset();
    }
    return err_code;
}

static uint32_t hci_timer_close(void)
{
    uint32_t err_code = NRF_SUCCESS;

#ifdef HCI_APP_TIMER
    err_code = app_timer_stop(m_app_timer_id);

    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
#endif

    return err_code;
}

/* ser_phy API function */
void ser_phy_close(void)
{
    m_ser_phy_callback = NULL;
    ser_phy_hci_slip_close();
    m_hci_tx_fsm_state = HCI_TX_STATE_DISABLE;
    m_hci_rx_fsm_state = HCI_RX_STATE_DISABLE;

#ifdef HCI_LINK_CONTROL
    m_hci_mode         = HCI_MODE_DISABLE;
#endif /* HCI_LINK_CONTROL */

    uint32_t err_code = hci_timer_close();
    ser_phy_hci_assert(err_code == NRF_SUCCESS);
}


