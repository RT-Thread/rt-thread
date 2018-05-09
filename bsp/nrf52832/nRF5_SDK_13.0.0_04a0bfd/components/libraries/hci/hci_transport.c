/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(HCI_TRANSPORT)
#include "hci_transport.h"
#include "hci_slip.h"
#include "crc16.h"
#include "hci_mem_pool.h"
#include "app_timer.h"
#include "app_error.h"
#include <stdio.h>

#define PKT_HDR_SIZE                    4u                                                                 /**< Packet header size in number of bytes. */
#define PKT_CRC_SIZE                    2u                                                                 /**< Packet CRC size in number of bytes. */
#define PKT_TYPE_VENDOR_SPECIFIC        14u                                                                /**< Packet type vendor specific. */
#define PKT_TYPE_ACK                    0                                                                  /**< Packet type acknowledgement. */
#define DATA_INTEGRITY_MASK             (1u << 6u)                                                         /**< Mask for data integrity bit in the packet header. */
#define RELIABLE_PKT_MASK               (1u << 7u)                                                         /**< Mask for reliable packet bit in the packet header. */
#define INITIAL_ACK_NUMBER_EXPECTED     1u                                                                 /**< Initial acknowledge number expected. */
#define INITIAL_ACK_NUMBER_TX           INITIAL_ACK_NUMBER_EXPECTED                                        /**< Initial acknowledge number transmitted. */
#define INVALID_PKT_TYPE                0xFFFFFFFFu                                                        /**< Internal invalid packet type value. */
#define HCI_UART_REG_VALUE_TO_BAUDRATE(BAUDRATE) ((BAUDRATE)/268)                                          /**< Estimated relation between UART baudrate register value and actual baudrate */
#define MAX_TRANSMISSION_TIME                                                  \
                   (ROUNDED_DIV((HCI_MAX_PACKET_SIZE_IN_BITS * 1000u),         \
                    HCI_UART_REG_VALUE_TO_BAUDRATE(HCI_UART_BAUDRATE)))                                    /**< Max transmission time of a single application packet over UART in units of mseconds. */
#define RETRANSMISSION_TIMEOUT_IN_MS    (3u * MAX_TRANSMISSION_TIME)                                       /**< Retransmission timeout for application packet in units of mseconds. */
#define RETRANSMISSION_TIMEOUT_IN_TICKS APP_TIMER_TICKS(RETRANSMISSION_TIMEOUT_IN_MS) /**< Retransmission timeout for application packet in units of timer ticks. */
#define MAX_RETRY_COUNT                 5u                                                                 /**< Max retransmission retry count for application packets. */
#define ACK_BUF_SIZE                    5u                                                                 /**< Length of module internal RX buffer which is big enough to hold an acknowledgement packet. */

/**@brief States of the TX state machine. */
typedef enum
{
    TX_STATE_IDLE,                                                   /**< State for: no application transmission packet processing in progress. */
    TX_STATE_PENDING,                                                /**< State for: TX in progress in slip layer and TX-done event is waited for to signal the end of transmission. */
    TX_STATE_ACTIVE                                                  /**< State for: application packet has been delivered to slip for transmission and peer transport entity acknowledgement packet is waited for. */
} tx_state_t;

/**@brief TX state machine events. */
typedef enum
{
    TX_EVENT_STATE_ENTRY,                                            /**< Event for: state entry use case. */
    TX_EVENT_SLIP_TX_DONE,                                           /**< Event for: HCI_SLIP_TX_DONE event use case. */
    TX_EVENT_TIMEOUT,                                                /**< Event for: retransmission timeout use case. */
    TX_EVENT_VALID_RX_ACK                                            /**< Event for: valid acknowledgement received for TX packet use case. */
} tx_event_t;

static void tx_sm_state_change(tx_state_t new_state);

static tx_state_t                      m_tx_state;                   /**< Current TX state. */
static hci_transport_tx_done_handler_t m_transport_tx_done_handle;   /**< TX done event callback function. */
static hci_transport_event_handler_t   m_transport_event_handle;     /**< Event handler callback function. */
static uint8_t *                       mp_slip_used_rx_buffer;       /**< Reference to RX buffer used by the slip layer. */
static uint32_t                        m_packet_expected_seq_number; /**< Sequence number counter of the packet expected to be received . */
static uint32_t                        m_packet_transmit_seq_number; /**< Sequence number counter of the transmitted packet for which acknowledgement packet is waited for. */
static uint8_t *                       mp_tx_buffer;                 /**< Pointer to TX application buffer to be transmitted. */
static uint32_t                        m_tx_buffer_length;           /**< Length of application TX packet data to be transmitted in bytes. */
static bool                            m_is_slip_decode_ready;       /**< Boolean to determine has slip decode been completed or not. */
APP_TIMER_DEF(m_app_timer_id);                                       /**< Application timer id. */
static uint32_t                        m_tx_retry_counter;           /**< Application packet retransmission counter. */
static hci_transport_tx_done_result_t  m_tx_done_result_code;        /**< TX done event callback function result code. */
static uint8_t                         m_rx_ack_buffer[ACK_BUF_SIZE];/**< RX buffer big enough to hold an acknowledgement packet and which is taken in use upon receiving  HCI_SLIP_RX_OVERFLOW event. */


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
static __INLINE uint8_t packet_number_expected_get(void)
{
    return (uint8_t) m_packet_expected_seq_number;
}


/**@brief Function for calculating a packet header checksum.
 *
 * @param[in] p_hdr Pointer to the packet header.
 *
 * @return          Calculated checksum.
 */
static uint8_t header_checksum_calculate(const uint8_t * p_hdr)
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


/**@brief Function for writing an acknowledgment packet for transmission.
 */
static void ack_transmit(void)
{
    static uint8_t ack_packet[PKT_HDR_SIZE];

    // TX ACK packet format:
    // - Unreliable Packet type
    // - Payload Length set to 0
    // - Sequence Number set to 0
    // - Header checksum calculated
    // - Acknowledge Number set correctly
    ack_packet[0] = (packet_number_expected_get() << 3u);
    ack_packet[1] = 0;
    ack_packet[2] = 0;
    ack_packet[3] = header_checksum_calculate(ack_packet);

    // @note: no return value check needed for hci_slip_write(...) call as acknowledgement packets
    // are considered to be from system design point of view unreliable packets.Use case where
    // underlying slip layer does not accept a packet for transmission is managed either by:
    // - acknowledged by possible future application packet as acknowledgement number header field
    // is included
    // - protocol peer entity will retransmit the packet
    UNUSED_VARIABLE(hci_slip_write(ack_packet, sizeof(ack_packet)));
}


/**@brief Function for validating a received packet.
 *
 * @param[in] p_buffer Pointer to the packet data.
 *
 * @return sequence number field of the packet header with unrelated data masked out.
 */
static __INLINE uint8_t packet_seq_nmbr_extract(const uint8_t * p_buffer)
{
    return (p_buffer[0] & 0x07u);
}


/**@brief Function for incrementing the sequence number counter for next reliable packet expected.
 */
static __INLINE void packet_number_expected_inc(void)
{
    ++m_packet_expected_seq_number;
    m_packet_expected_seq_number &= 0x07u;
}


/**@brief Function for decoding a packet type field.
 *
 * @param[in] p_buffer Pointer to the packet data.
 * @param[in] length   Length of packet data in bytes.
 *
 * @return Packet type field or INVALID_PKT_TYPE in case of decode error.
 */
static __INLINE uint32_t packet_type_decode(const uint8_t * p_buffer, uint32_t length)
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


/**@brief Function for processing a received vendor specific packet.
 *
 * @param[in] p_buffer Pointer to the packet data.
 * @param[in] length   Length of packet data in bytes.
 */
static void rx_vendor_specific_pkt_type_handle(const uint8_t * p_buffer, uint32_t length)
{
    // @note: no pointer validation check needed as allready checked by calling function.
    uint32_t err_code;

    if (is_rx_pkt_valid(p_buffer, length))
    {
        // RX packet is valid: validate sequence number.
        const uint8_t rx_seq_number = packet_seq_nmbr_extract(p_buffer);
        if (packet_number_expected_get() == rx_seq_number)
        {
            // Sequence number is valid: transmit acknowledgement.
            packet_number_expected_inc();
            ack_transmit();

            m_is_slip_decode_ready = true;

            err_code = hci_mem_pool_rx_data_size_set(length);
            APP_ERROR_CHECK(err_code);

            err_code = hci_mem_pool_rx_produce(HCI_RX_BUF_SIZE, (void **)&mp_slip_used_rx_buffer);
            APP_ERROR_CHECK_BOOL((err_code == NRF_SUCCESS) || (err_code == NRF_ERROR_NO_MEM));

            // If memory pool RX buffer produce succeeded we register that buffer to slip layer
            // otherwise we register the internal acknowledgement buffer.
            err_code = hci_slip_rx_buffer_register(
                (err_code == NRF_SUCCESS) ? mp_slip_used_rx_buffer : m_rx_ack_buffer,
                (err_code == NRF_SUCCESS) ? HCI_RX_BUF_SIZE : ACK_BUF_SIZE);

            APP_ERROR_CHECK(err_code);

            if (m_transport_event_handle != NULL)
            {
                // Send application event of RX packet reception.
                const hci_transport_evt_t evt = {HCI_TRANSPORT_RX_RDY};
                m_transport_event_handle(evt);
            }
        }
        else
        {
            // RX packet discarded: sequence number not valid, set the same buffer to slip layer in
            // order to avoid buffer overrun.
            err_code = hci_slip_rx_buffer_register(mp_slip_used_rx_buffer, HCI_RX_BUF_SIZE);
            APP_ERROR_CHECK(err_code);

            // As packet did not have expected sequence number: send acknowledgement with the
            // current expected sequence number.
            ack_transmit();
        }
    }
    else
    {
        // RX packet discarded: reset the same buffer to slip layer in order to avoid buffer
        // overrun.
        err_code = hci_slip_rx_buffer_register(mp_slip_used_rx_buffer, HCI_RX_BUF_SIZE);
        APP_ERROR_CHECK(err_code);
    }
}


/**@brief Function for getting the sequence number of a reliable TX packet for which peer protocol
 * entity acknowledgment is pending.
 *
 * @return sequence number of a reliable TX packet for which peer protocol entity acknowledgement
 * is pending.
 */
static __INLINE uint8_t packet_number_to_transmit_get(void)
{
    return m_packet_transmit_seq_number;
}


/**@brief Function for getting the expected acknowledgement number.
 *
 * @return expected acknowledgement number.
 */
static __INLINE uint8_t expected_ack_number_get(void)
{
    uint8_t seq_nmbr = packet_number_to_transmit_get();
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
static __INLINE bool rx_ack_pkt_type_handle(const uint8_t * p_buffer)
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
    return (ack_number == expected_ack_number_get());
}


/**@brief Function for incrementing the sequence number counter of the TX packet.
 */
static __INLINE void packet_number_tx_inc(void)
{
    ++m_packet_transmit_seq_number;
    m_packet_transmit_seq_number &= 0x07u;
}


/**@brief Function for TX state machine event processing in a state centric manner.
 *
 * @param[in] event Type of event occurred.
 */
static void tx_sm_event_handle(tx_event_t event)
{
    uint32_t err_code;

    switch (m_tx_state)
    {
        case TX_STATE_IDLE:
            if (event == TX_EVENT_STATE_ENTRY)
            {
                err_code = app_timer_stop(m_app_timer_id);
                APP_ERROR_CHECK(err_code);

                // Send TX-done event if registered handler exists.
                if (m_transport_tx_done_handle != NULL)
                {
                    m_transport_tx_done_handle(m_tx_done_result_code);
                }
            }
            break;

        case TX_STATE_PENDING:
            if (event == TX_EVENT_SLIP_TX_DONE)
            {
                // @note: this call should always succeed as called from HCI_SLIP_TX_DONE context
                // and error cases are managed by dedicated error event from the slip layer.
                err_code = hci_slip_write(mp_tx_buffer,
                                         (m_tx_buffer_length + PKT_HDR_SIZE + PKT_CRC_SIZE));
                APP_ERROR_CHECK(err_code);
                tx_sm_state_change(TX_STATE_ACTIVE);
            }
            break;

        case TX_STATE_ACTIVE:
            switch (event)
            {
                case TX_EVENT_VALID_RX_ACK:
                    // Tx sequence number counter incremented as packet transmission
                    // acknowledged by peer transport entity.
                    packet_number_tx_inc();
                    tx_sm_state_change(TX_STATE_IDLE);
                    break;

                case TX_EVENT_STATE_ENTRY:
                    m_tx_retry_counter = 0;
                    err_code = app_timer_start(m_app_timer_id,
                                               RETRANSMISSION_TIMEOUT_IN_TICKS,
                                               NULL);
                    APP_ERROR_CHECK(err_code);
                    break;

                case TX_EVENT_TIMEOUT:
                    if (m_tx_retry_counter != MAX_RETRY_COUNT)
                    {
                        ++m_tx_retry_counter;
                        // @note: no return value check done for hci_slip_write(...) call as current
                        // system design allows use case where retransmission is not accepted by the
                        // slip layer due to existing acknowledgement packet transmission in the
                        // slip layer.
                        UNUSED_VARIABLE(hci_slip_write(mp_tx_buffer,
                                                      (m_tx_buffer_length +
                                                      PKT_HDR_SIZE        +
                                                      PKT_CRC_SIZE)));
                    }
                    else
                    {
                        // Application packet retransmission count reached:
                        // - set correct TX done event callback function result code
                        // - execute state change
                        // @note: m_tx_retry_counter is reset in TX_STATE_ACTIVE state entry.
                        m_tx_done_result_code = HCI_TRANSPORT_TX_DONE_FAILURE;
                        tx_sm_state_change(TX_STATE_IDLE);
                    }
                    break;

                default:
                    // No implementation needed.
                    break;
            }
            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for changing the state of the TX state machine.
 *
 * @param[in] new_state State TX state machine transits to.
 */
static void tx_sm_state_change(tx_state_t new_state)
{
    m_tx_state = new_state;
    tx_sm_event_handle(TX_EVENT_STATE_ENTRY);
}


/**@brief Function for handling slip events.
 *
 * @param[in] event The event structure.
 */
void slip_event_handle(hci_slip_evt_t event)
{
    uint32_t return_code;
    uint32_t err_code;

    switch (event.evt_type)
    {
        case HCI_SLIP_TX_DONE:
            tx_sm_event_handle(TX_EVENT_SLIP_TX_DONE);
            break;

        case HCI_SLIP_RX_RDY:
            return_code = packet_type_decode(event.packet, event.packet_length);

            switch (return_code)
            {
                case PKT_TYPE_VENDOR_SPECIFIC:
                    rx_vendor_specific_pkt_type_handle(event.packet, event.packet_length);
                    break;

                case PKT_TYPE_ACK:
                    if (rx_ack_pkt_type_handle(event.packet))
                    {
                        // Valid expected acknowledgement packet received: set correct TX done event
                        // callback function result code and execute state change.
                        m_tx_done_result_code = HCI_TRANSPORT_TX_DONE_SUCCESS;
                        tx_sm_event_handle(TX_EVENT_VALID_RX_ACK);
                    }

                /* fall-through */
                default:
                    // RX packet dropped: reset memory buffer to slip in order to avoid RX buffer
                    // overflow.
                    // If existing mem pool produced RX buffer exists reuse that one. If existing
                    // mem pool produced RX buffer does not exist try to produce new one. If
                    // producing fails use the internal acknowledgement buffer.
                    if (mp_slip_used_rx_buffer != NULL)
                    {
                        err_code = hci_slip_rx_buffer_register(mp_slip_used_rx_buffer, HCI_RX_BUF_SIZE);
                        APP_ERROR_CHECK(err_code);
                    }
                    else
                    {
                        err_code = hci_mem_pool_rx_produce(HCI_RX_BUF_SIZE,
                                                           (void **)&mp_slip_used_rx_buffer);
                        APP_ERROR_CHECK_BOOL((err_code == NRF_SUCCESS) ||
                                            (err_code == NRF_ERROR_NO_MEM));

                        err_code = hci_slip_rx_buffer_register(
                            (err_code == NRF_SUCCESS) ? mp_slip_used_rx_buffer : m_rx_ack_buffer,
                            (err_code == NRF_SUCCESS) ? HCI_RX_BUF_SIZE : ACK_BUF_SIZE);
                        APP_ERROR_CHECK(err_code);
                    }
                    break;
            }
            break;

        case HCI_SLIP_RX_OVERFLOW:
            err_code = hci_slip_rx_buffer_register(m_rx_ack_buffer, ACK_BUF_SIZE);
            APP_ERROR_CHECK(err_code);
            break;

        case HCI_SLIP_ERROR:
            APP_ERROR_HANDLER(event.evt_type);
            break;

        default:
            APP_ERROR_HANDLER(event.evt_type);
            break;
    }
}


uint32_t hci_transport_evt_handler_reg(hci_transport_event_handler_t event_handler)
{
    uint32_t err_code;

    m_transport_event_handle = event_handler;
    err_code                 = hci_slip_evt_handler_register(slip_event_handle);
    APP_ERROR_CHECK(err_code);

    return (event_handler != NULL) ? NRF_SUCCESS : NRF_ERROR_NULL;
}


uint32_t hci_transport_tx_done_register(hci_transport_tx_done_handler_t event_handler)
{
    uint32_t err_code;

    m_transport_tx_done_handle = event_handler;
    err_code                   = hci_slip_evt_handler_register(slip_event_handle);
    APP_ERROR_CHECK(err_code);

    return (event_handler != NULL) ? NRF_SUCCESS : NRF_ERROR_NULL;
}


/**@brief Function for handling the application packet retransmission timeout.
 *
 * This function is registered in the @ref app_timer module when a timer is created on
 * @ref hci_transport_open.
 *
 * @note This function must be executed in APP-LO context otherwise retransmission behaviour is
 *       undefined, see @ref nrf51_system_integration_serialization.
 *
 * @param[in] p_context The timeout context.
 */
void hci_transport_timeout_handle(void * p_context)
{
    tx_sm_event_handle(TX_EVENT_TIMEOUT);
}


uint32_t hci_transport_open(void)
{
    mp_tx_buffer                 = NULL;
    m_tx_buffer_length           = 0;
    m_tx_retry_counter           = 0;
    m_is_slip_decode_ready       = false;
    m_tx_state                   = TX_STATE_IDLE;
    m_packet_expected_seq_number = INITIAL_ACK_NUMBER_EXPECTED;
    m_packet_transmit_seq_number = INITIAL_ACK_NUMBER_TX;
    m_tx_done_result_code        = HCI_TRANSPORT_TX_DONE_FAILURE;

    uint32_t err_code = app_timer_create(&m_app_timer_id,
                                         APP_TIMER_MODE_REPEATED,
                                         hci_transport_timeout_handle);
    if (err_code != NRF_SUCCESS)
    {
        // @note: conduct required interface adjustment.
        return NRF_ERROR_INTERNAL;
    }

    err_code = hci_mem_pool_open();
    VERIFY_SUCCESS(err_code);

    err_code = hci_slip_open();
    VERIFY_SUCCESS(err_code);

    err_code = hci_mem_pool_rx_produce(HCI_RX_BUF_SIZE, (void **)&mp_slip_used_rx_buffer);
    if (err_code != NRF_SUCCESS)
    {
        // @note: conduct required interface adjustment.
        return NRF_ERROR_INTERNAL;
    }

    err_code = hci_slip_rx_buffer_register(mp_slip_used_rx_buffer, HCI_RX_BUF_SIZE);

    return err_code;
}


uint32_t hci_transport_close(void)
{
    uint32_t err_code;

    m_transport_tx_done_handle = NULL;
    m_transport_event_handle   = NULL;

    err_code = hci_mem_pool_close();
    APP_ERROR_CHECK(err_code);
    err_code = hci_slip_close();
    APP_ERROR_CHECK(err_code);

    // @note: NRF_ERROR_NO_MEM is the only return value which should never be returned.
    err_code = app_timer_stop(m_app_timer_id);
    APP_ERROR_CHECK_BOOL(err_code != NRF_ERROR_NO_MEM);

    return NRF_SUCCESS;
}


uint32_t hci_transport_tx_alloc(uint8_t ** pp_memory)
{
    const uint32_t err_code = hci_mem_pool_tx_alloc((void **)pp_memory);
    if (err_code == NRF_SUCCESS)
    {
        // @note: no need to validate pp_memory against null as validation has already been done
        // by hci_mem_pool_tx_alloc(...) and visible to us from the method return code.
        //lint -e(413) "Likely use of null pointer"
        *pp_memory += PKT_HDR_SIZE;
    }

    return err_code;
}


uint32_t hci_transport_tx_free(void)
{
    return hci_mem_pool_tx_free();
}


/**@brief Function for constructing 1st byte of the packet header of the packet to be transmitted.
 *
 * @return 1st byte of the packet header of the packet to be transmitted
 */
static __INLINE uint8_t tx_packet_byte_zero_construct(void)
{
    const uint32_t value = DATA_INTEGRITY_MASK                  |
                           RELIABLE_PKT_MASK                    |
                           (packet_number_expected_get() << 3u) |
                           packet_number_to_transmit_get();

    return (uint8_t) value;
}


/**@brief Function for handling the application packet write request in tx-idle state.
 */
static uint32_t pkt_write_handle(void)
{
    uint32_t err_code;

    // Set packet header fields.

    mp_tx_buffer   -= PKT_HDR_SIZE;
    mp_tx_buffer[0] = tx_packet_byte_zero_construct();

    const uint16_t type_and_length_fields = ((m_tx_buffer_length << 4u) | PKT_TYPE_VENDOR_SPECIFIC);
    // @note: no use case for uint16_encode(...) return value.
    UNUSED_VARIABLE(uint16_encode(type_and_length_fields, &(mp_tx_buffer[1])));
    mp_tx_buffer[3] = header_checksum_calculate(mp_tx_buffer);

    // Calculate, append CRC to the packet and write it.

    const uint16_t crc = crc16_compute(mp_tx_buffer, (PKT_HDR_SIZE + m_tx_buffer_length), NULL);
    // @note: no use case for uint16_encode(...) return value.
    UNUSED_VARIABLE(uint16_encode(crc, &(mp_tx_buffer[PKT_HDR_SIZE + m_tx_buffer_length])));
    err_code = hci_slip_write(mp_tx_buffer, (m_tx_buffer_length + PKT_HDR_SIZE + PKT_CRC_SIZE));
    switch (err_code)
    {
        case NRF_SUCCESS:
            tx_sm_state_change(TX_STATE_ACTIVE);
            break;

        case NRF_ERROR_NO_MEM:
            tx_sm_state_change(TX_STATE_PENDING);
            err_code = NRF_SUCCESS;
            break;

        default:
            // No implementation needed.
            break;
    }

    return err_code;
}


uint32_t hci_transport_pkt_write(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t err_code;

    if (p_buffer)
    {
        switch (m_tx_state)
        {
            case TX_STATE_IDLE:
                mp_tx_buffer       = (uint8_t *)p_buffer;
                m_tx_buffer_length = length;
                err_code = pkt_write_handle();
                break;

            default:
                err_code = NRF_ERROR_NO_MEM;
                break;
        }
    }
    else
    {
        err_code = NRF_ERROR_NULL;
    }

    return err_code;
}


uint32_t hci_transport_rx_pkt_extract(uint8_t ** pp_buffer, uint16_t * p_length)
{
    uint32_t err_code;

    if (pp_buffer != NULL && p_length != NULL)
    {
        uint32_t length = 0;

        if (m_is_slip_decode_ready)
        {
            m_is_slip_decode_ready = false;
            err_code               = hci_mem_pool_rx_extract(pp_buffer, &length);
            length                -= (PKT_HDR_SIZE + PKT_CRC_SIZE);

            *p_length              = (uint16_t)length;
            *pp_buffer            += PKT_HDR_SIZE;
        }
        else
        {
            err_code = NRF_ERROR_NO_MEM;
        }
    }
    else
    {
        err_code = NRF_ERROR_NULL;
    }

    return err_code;
}


uint32_t hci_transport_rx_pkt_consume(uint8_t * p_buffer)
{
    return (hci_mem_pool_rx_consume(p_buffer - PKT_HDR_SIZE));
}
#endif //NRF_MODULE_ENABLED(HCI_TRANSPORT)
