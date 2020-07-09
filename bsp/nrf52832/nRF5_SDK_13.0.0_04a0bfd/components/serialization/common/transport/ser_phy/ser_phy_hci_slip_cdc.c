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

#include <string.h>
#include "ser_phy_hci.h"
#include "ser_config.h"
#ifdef SER_CONNECTIVITY
#include "ser_phy_config_conn.h"
#else
#include "ser_phy_config_app.h"
#endif
#include "app_usbd_cdc_acm.h"
#include "nrf_drv_clock.h"
#include "app_error.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "CONN"
#include "nrf_log.h"

#define APP_SLIP_END     0xC0 /**< SLIP code for identifying the beginning and end of a packet frame.. */
#define APP_SLIP_ESC     0xDB /**< SLIP escape code. This code is used to specify that the following character is specially encoded. */
#define APP_SLIP_ESC_END 0xDC /**< SLIP special code. When this code follows 0xDB, this character is interpreted as payload data 0xC0.. */
#define APP_SLIP_ESC_ESC 0xDD /**< SLIP special code. When this code follows 0xDB, this character is interpreted as payload data 0xDB. */

#define HDR_SIZE 4
#define CRC_SIZE 2
#define PKT_SIZE (SER_HAL_TRANSPORT_MAX_PKT_SIZE + HDR_SIZE + CRC_SIZE)

static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event);

#define CDC_ACM_COMM_INTERFACE  0
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE  1
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT1

#define CDC_ACM_INTERFACES_CONFIG()                 \
    APP_USBD_CDC_ACM_CONFIG(CDC_ACM_COMM_INTERFACE, \
                            CDC_ACM_COMM_EPIN,      \
                            CDC_ACM_DATA_INTERFACE, \
                            CDC_ACM_DATA_EPIN,      \
                            CDC_ACM_DATA_EPOUT)

static const uint8_t m_cdc_acm_class_descriptors[] = {
        APP_USBD_CDC_ACM_DEFAULT_DESC(CDC_ACM_COMM_INTERFACE,
                                      CDC_ACM_COMM_EPIN,
                                      CDC_ACM_DATA_INTERFACE,
                                      CDC_ACM_DATA_EPIN,
                                      CDC_ACM_DATA_EPOUT)
};

/*lint -save -e40 -e26 -e64 -e123 -e505 -e651*/
APP_USBD_CDC_ACM_GLOBAL_DEF(m_app_cdc_acm,
                            CDC_ACM_INTERFACES_CONFIG(),
                            cdc_acm_user_ev_handler,
                            m_cdc_acm_class_descriptors
);
/*lint -restore*/

static bool volatile m_port_open;

typedef struct {
    ser_phy_hci_pkt_params_t header;
    ser_phy_hci_pkt_params_t payload;
    ser_phy_hci_pkt_params_t crc;
} ser_phy_hci_slip_pkt_t;
static ser_phy_hci_slip_pkt_t m_tx_curr_packet;
static ser_phy_hci_slip_pkt_t m_tx_next_packet;

static ser_phy_hci_slip_evt_t           m_ser_phy_hci_slip_event;
static ser_phy_hci_slip_event_handler_t m_ser_phy_hci_slip_event_handler; /**< Event handler for upper layer */

static uint8_t   m_tx_buf0[NRF_DRV_USBD_EPSIZE];
static uint8_t   m_tx_buf1[NRF_DRV_USBD_EPSIZE];
static uint8_t * mp_tx_buf;
static uint8_t   m_tx_bytes;
static enum {
    PHASE_BEGIN,
    PHASE_HEADER,
    PHASE_PAYLOAD,
    PHASE_CRC,
    PHASE_ACK_END,
    // The following three elements have to have consecutive values,
    // 'tx_buf_fill()' relies on this.
    PHASE_PACKET_END,
    PHASE_PRE_IDLE = PHASE_PACKET_END + 1,
    PHASE_IDLE     = PHASE_PRE_IDLE + 1
} volatile m_tx_phase;
static bool volatile m_tx_in_progress;
static bool volatile m_tx_pending;

#define NO_EVENT  SER_PHY_HCI_SLIP_EVT_TYPE_MAX
static ser_phy_hci_slip_evt_type_t m_tx_evt_type;
static ser_phy_hci_slip_evt_type_t m_tx_pending_evt_type;

static ser_phy_hci_pkt_params_t * mp_tx_data = NULL;
static uint32_t                   m_tx_index;

static uint8_t m_small_buffer[HDR_SIZE];
static uint8_t m_big_buffer[PKT_SIZE];

static uint8_t * mp_small_buffer = NULL;
static uint8_t * mp_big_buffer   = NULL;
static uint8_t * mp_buffer       = NULL;
static uint32_t  m_rx_index;

static uint8_t m_rx_buf[NRF_DRV_USBD_EPSIZE];
static bool m_rx_escape;

#define SERIAL_NUMBER_STRING_SIZE (16)
uint16_t g_extern_serial_number[SERIAL_NUMBER_STRING_SIZE + 1];

static void serial_number_string_create(void)
{
    g_extern_serial_number[0] = (uint16_t)APP_USBD_DESCRIPTOR_STRING << 8 |
                                          sizeof(g_extern_serial_number);

    uint32_t dev_id_hi = NRF_FICR->DEVICEID[1];
    uint32_t dev_id_lo = NRF_FICR->DEVICEID[0];
    uint64_t device_id = (((uint64_t)dev_id_hi) << 32) | dev_id_lo;

    for (size_t i = SERIAL_NUMBER_STRING_SIZE; i > 0; --i)
    {
        uint8_t nibble = (uint8_t)(device_id & 0xF);
        device_id >>= 4;

        uint8_t hex_digit;
        if (nibble >= 10)
        {
            hex_digit = 'A' + (nibble - 10);
        }
        else
        {
            hex_digit = '0' + nibble;
        }
        g_extern_serial_number[i] = hex_digit;
    }
}

// The function returns false to signal that no more bytes can be passed to be
// sent (put into the TX buffer) until UART transmission is done.
static bool tx_buf_put(uint8_t data_byte)
{
    ASSERT(m_tx_bytes < SER_PHY_HCI_SLIP_TX_BUF_SIZE);
    mp_tx_buf[m_tx_bytes] = data_byte;
    ++m_tx_bytes;

    bool flush = false;
    ser_phy_hci_slip_evt_type_t slip_evt_type = NO_EVENT;
    if (m_tx_phase == PHASE_ACK_END)
    {
        // Send buffer, then signal that an acknowledge packet has been sent.
        flush = true;
        slip_evt_type = SER_PHY_HCI_SLIP_EVT_ACK_SENT;
    }
    else if (m_tx_phase == PHASE_PACKET_END)
    {
        // Send buffer, then signal that a packet with payload has been sent.
        flush = true;
        slip_evt_type = SER_PHY_HCI_SLIP_EVT_PKT_SENT;
    }
    else if (m_tx_bytes >= SER_PHY_HCI_SLIP_TX_BUF_SIZE)
    {
        // Send buffer (because it is filled up), but don't signal anything,
        // since the packet sending is not complete yet.
        flush = true;
    }

    if (flush)
    {
        // If some TX transfer is being done at the moment, a new one cannot be
        // started, it must be scheduled to be performed later.
        if (m_tx_in_progress)
        {
            m_tx_pending_evt_type = slip_evt_type;
            m_tx_pending = true;
            // No more buffers available, can't continue filling.
            return false;
        }

        if (m_port_open)
        {
            m_tx_in_progress = true;
            m_tx_evt_type = slip_evt_type;
            APP_ERROR_CHECK(app_usbd_cdc_acm_write(&m_app_cdc_acm,
                mp_tx_buf, m_tx_bytes));
        }

        // Switch to the second buffer.
        mp_tx_buf = (mp_tx_buf == m_tx_buf0) ? m_tx_buf1 : m_tx_buf0;
        m_tx_bytes = 0;
    }

    return true;
}

static void tx_buf_fill(void)
{
    bool can_continue = true;
    do {
        static uint8_t tx_escaped_data = 0;

        if (tx_escaped_data != 0)
        {
            can_continue = tx_buf_put(tx_escaped_data);
            tx_escaped_data = 0;
        }
        else switch (m_tx_phase)
        {
        case PHASE_BEGIN:
            can_continue = tx_buf_put(APP_SLIP_END);
            mp_tx_data = &m_tx_curr_packet.header;
            m_tx_index = 0;
            m_tx_phase = PHASE_HEADER;
            tx_escaped_data = 0;
            break;

        case PHASE_ACK_END:
        case PHASE_PACKET_END:
            can_continue = tx_buf_put(APP_SLIP_END);

            // [this is needed for the '++m_tx_phase;' below]
            m_tx_phase = PHASE_PACKET_END;
            // no break, intentional fall-through

        case PHASE_PRE_IDLE:
            // In PHASE_PRE_IDLE the sending process is almost finished, only
            // the NRF_DRV_UART_EVT_TX_DONE event is needed before it can switch
            // to PHASE_IDLE. But during this waiting a new packet may appear
            // (i.e. 'ser_phy_hci_slip_tx_pkt_send()' may be called), hence
            // the following pointer must be checked before switching the phase,
            // just like right after writing whole packet to buffer (i.e. in
            // PHASE_PACKET_END). Therefore, the following code is common for
            // these two cases.
            if (m_tx_next_packet.header.p_buffer != NULL)
            {
                m_tx_curr_packet = m_tx_next_packet;
                m_tx_next_packet.header.p_buffer = NULL;

                m_tx_phase = PHASE_BEGIN;
                break;
            }
            // Go to the next phase:
            //   PHASE_PACKET_END -> PHASE_PRE_IDLE
            //   PHASE_PRE_IDLE   -> PHASE_IDLE
            ++m_tx_phase;
            return;

        default:
            ASSERT(mp_tx_data->p_buffer != NULL);
            uint8_t data = mp_tx_data->p_buffer[m_tx_index];
            ++m_tx_index;

            if (data == APP_SLIP_END)
            {
                data = APP_SLIP_ESC;
                tx_escaped_data = APP_SLIP_ESC_END;
            }
            else if (data == APP_SLIP_ESC)
            {
                tx_escaped_data = APP_SLIP_ESC_ESC;
            }
            can_continue = tx_buf_put(data);

            if (m_tx_index >= mp_tx_data->num_of_bytes)
            {
                mp_tx_data->p_buffer = NULL;

                if (m_tx_phase == PHASE_HEADER)
                {
                    if (m_tx_curr_packet.payload.p_buffer == NULL)
                    {
                        // No payload -> ACK packet.
                        m_tx_phase = PHASE_ACK_END;
                    }
                    else
                    {
                        mp_tx_data = &m_tx_curr_packet.payload;
                        m_tx_index = 0;
                        m_tx_phase = PHASE_PAYLOAD;
                    }
                }
                else if (m_tx_phase == PHASE_PAYLOAD)
                {
                    if (m_tx_curr_packet.crc.p_buffer == NULL)
                    {
                        // Packet without CRC.
                        m_tx_phase = PHASE_PACKET_END;
                    }
                    else
                    {
                        mp_tx_data = &m_tx_curr_packet.crc;
                        m_tx_index = 0;
                        m_tx_phase = PHASE_CRC;
                    }
                }
                else
                {
                    ASSERT(m_tx_phase == PHASE_CRC);
                    m_tx_phase = PHASE_PACKET_END;
                }
            }
            break;
        }
    } while (can_continue);
}

uint32_t ser_phy_hci_slip_tx_pkt_send(const ser_phy_hci_pkt_params_t * p_header,
                                      const ser_phy_hci_pkt_params_t * p_payload,
                                      const ser_phy_hci_pkt_params_t * p_crc)
{
    if (p_header == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (!m_port_open)
    {
        return NRF_SUCCESS;
    }

    CRITICAL_REGION_ENTER();

    // If some packet is already transmitted, schedule this new one to be sent
    // as next. A critical region is needed here to ensure that the transmission
    // won't finish before the following assignments are done.
    if (m_tx_phase != PHASE_IDLE)
    {
        m_tx_next_packet.header = *p_header;

        if (p_payload == NULL)
        {
            m_tx_next_packet.payload.p_buffer = NULL;
        }
        else
        {
            m_tx_next_packet.payload = *p_payload;
        }

        if (p_crc == NULL)
        {
            m_tx_next_packet.crc.p_buffer = NULL;
        }
        else
        {
            m_tx_next_packet.crc = *p_crc;
        }
    }
    else
    {
        m_tx_curr_packet.header = *p_header;

        if (p_payload == NULL)
        {
            m_tx_curr_packet.payload.p_buffer = NULL;
        }
        else
        {
            m_tx_curr_packet.payload = *p_payload;
        }

        if (p_crc == NULL)
        {
            m_tx_curr_packet.crc.p_buffer = NULL;
        }
        else
        {
            m_tx_curr_packet.crc = *p_crc;
        }

        m_tx_phase = PHASE_BEGIN;
        tx_buf_fill();
    }

    CRITICAL_REGION_EXIT();

    return NRF_SUCCESS;
}

/* Function returns false when last byte in packet is detected.*/
static bool slip_decode(uint8_t * p_received_byte)
{
    switch (*p_received_byte)
    {
        case APP_SLIP_END:
            return false;

        case APP_SLIP_ESC:
            m_rx_escape = true;
            break;

        case APP_SLIP_ESC_END:

            if (m_rx_escape == true)
            {
                m_rx_escape      = false;
                *p_received_byte = APP_SLIP_END;
            }
            break;

        case APP_SLIP_ESC_ESC:

            if (m_rx_escape == true)
            {
                m_rx_escape      = false;
                *p_received_byte = APP_SLIP_ESC;
            }
            break;

        /* Normal character - decoding not needed*/
        default:
            break;
    }

    return true;
}


static void ser_phi_hci_rx_byte(uint8_t rx_byte)
{
    static bool rx_sync         = false;
    uint8_t     received_byte   = rx_byte;
    static bool big_buff_in_use = false;

    /* Test received byte for SLIP packet start: 0xC0*/
    if (!rx_sync)
    {
        if (received_byte == APP_SLIP_END)
        {
            m_rx_index = 0;
            rx_sync    = true;
        }
        return;
    }

    /* Additional check needed in case rx_sync flag was set by end of previous packet*/
    if ((m_rx_index) == 0 && (received_byte == APP_SLIP_END))
    {
        return;
    }

    /* Check if small (ACK) buffer is available*/
    if ((mp_small_buffer != NULL) && (big_buff_in_use == false))
    {
        if (m_rx_index == 0)
        {
            mp_buffer = mp_small_buffer;
        }

        /* Check if switch between small and big buffer is needed*/
        if (m_rx_index == sizeof (m_small_buffer) /*NEW!!!*/ && received_byte != APP_SLIP_END)
        {
            /* Check if big (PKT) buffer is available*/
            if (mp_big_buffer != NULL)
            {
                /* Switch to big buffer*/
                memcpy(m_big_buffer, m_small_buffer, sizeof (m_small_buffer));
                mp_buffer = m_big_buffer;
            }
            else
            {
                /* Small buffer is too small and big buffer not available - cannot continue reception*/
                rx_sync = false;
                return;
            }
        }

        /* Check if big buffer is full */
        if ((m_rx_index >= PKT_SIZE) && (received_byte != APP_SLIP_END))
        {
            /* Do not notify upper layer - the packet is too big and cannot be handled by slip */
            rx_sync = false;
            return;
        }

        /* Decode byte. Will return false when it is 0xC0 - end of packet*/
        if (slip_decode(&received_byte))
        {
            /* Write Rx byte only if it is not escape char */
            if (!m_rx_escape)
            {
                mp_buffer[m_rx_index++] = received_byte;
            }
        }
        else
        {
            /* Reset pointers to signalise buffers are locked waiting for upper layer */
            if (mp_buffer == mp_small_buffer)
            {
                mp_small_buffer = NULL;
            }
            else
            {
                mp_big_buffer = NULL;
            }
            /* Report packet reception end*/
            m_ser_phy_hci_slip_event.evt_type =
                SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED;
            m_ser_phy_hci_slip_event.evt_params.received_pkt.p_buffer     = mp_buffer;
            m_ser_phy_hci_slip_event.evt_params.received_pkt.num_of_bytes = m_rx_index;
            m_ser_phy_hci_slip_event_handler(&m_ser_phy_hci_slip_event);

            rx_sync = false;
        }
    }
    else if (mp_big_buffer != NULL)
    {
        big_buff_in_use = true;
        mp_buffer       = mp_big_buffer;

        /* Check if big buffer is full */
        if ((m_rx_index >= PKT_SIZE) && (received_byte != APP_SLIP_END))
        {
            /* Do not notify upper layer - the packet is too big and cannot be handled by slip */
            rx_sync = false;
            return;
        }

        /* Decode byte*/
        if (slip_decode(&received_byte))
        {
            /* Write Rx byte only if it is not escape char */
            if (!m_rx_escape)
            {
                mp_buffer[m_rx_index++] = received_byte;
            }
        }
        else
        {
            // Mark the big buffer as locked (it should be freed by the upper
            // layer).
            mp_big_buffer   = NULL;
            big_buff_in_use = false;

            /* Report packet reception end*/
            m_ser_phy_hci_slip_event.evt_type =
                SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED;
            m_ser_phy_hci_slip_event.evt_params.received_pkt.p_buffer     = mp_buffer;
            m_ser_phy_hci_slip_event.evt_params.received_pkt.num_of_bytes = m_rx_index;
            m_ser_phy_hci_slip_event_handler(&m_ser_phy_hci_slip_event);

            rx_sync = false;
        }
    }
    else
    {
        /* Both buffers are not available - cannot continue reception*/
        rx_sync = false;
        return;
    }
}


uint32_t ser_phy_hci_slip_rx_buf_free(uint8_t * p_buffer)
{
    uint32_t err_code = NRF_SUCCESS;

    if (p_buffer == NULL)
    {
        return NRF_ERROR_NULL;
    }
    else if (p_buffer == m_small_buffer)
    {
        /* Free small buffer*/
        if (mp_small_buffer == NULL)
        {
            mp_small_buffer = m_small_buffer;
        }
        else
        {
            err_code = NRF_ERROR_INVALID_STATE;
        }
    }
    else if (p_buffer == m_big_buffer)
    {
        /* Free big buffer*/
        if (mp_big_buffer == NULL)
        {
            mp_big_buffer = m_big_buffer;
        }
        else
        {
            err_code = NRF_ERROR_INVALID_STATE;
        }
    }

    return err_code;
}


static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = app_usbd_cdc_acm_class_get(p_inst);

    switch (event)
    {
    case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
        NRF_LOG_DEBUG("EVT_PORT_OPEN\r\n");
        if (!m_port_open)
        {
            m_port_open = true;
            APP_ERROR_CHECK(app_usbd_cdc_acm_read(p_cdc_acm,
                m_rx_buf, sizeof(m_rx_buf)));
        }
        break;

    case APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE:
        NRF_LOG_DEBUG("EVT_PORT_CLOSE\r\n");
        m_port_open = false;
        break;

    case APP_USBD_CDC_ACM_USER_EVT_TX_DONE:
        // If there is a pending transfer (the second buffer is ready to
        // be sent), start it immediately.
        if (m_tx_pending)
        {
            APP_ERROR_CHECK(app_usbd_cdc_acm_write(p_cdc_acm,
                mp_tx_buf, m_tx_bytes));

            // Switch to the buffer that has just been sent completely
            // and now can be filled again.
            mp_tx_buf = (mp_tx_buf == m_tx_buf0) ? m_tx_buf1 : m_tx_buf0;
            m_tx_bytes = 0;

            m_ser_phy_hci_slip_event.evt_type = m_tx_evt_type;
            m_tx_evt_type = m_tx_pending_evt_type;

            m_tx_pending = false;
        }
        else
        {
            m_tx_in_progress = false;
            m_ser_phy_hci_slip_event.evt_type = m_tx_evt_type;
        }
        // If needed, notify the upper layer that the packet transfer is
        // complete (note that this notification may result in another
        // packet send request, so everything must be cleaned up above).
        if (m_ser_phy_hci_slip_event.evt_type != NO_EVENT)
        {
            m_ser_phy_hci_slip_event_handler(&m_ser_phy_hci_slip_event);
        }
        // And if the sending process is not yet finished, look what is
        // to be done next.
        if (m_tx_phase != PHASE_IDLE)
        {
            tx_buf_fill();
        }
        break;

    case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
        {
            size_t size = app_usbd_cdc_acm_rx_size(p_cdc_acm);
            for (size_t i = 0; i < size; ++i)
            {
                ser_phi_hci_rx_byte(m_rx_buf[i]);
            }
            APP_ERROR_CHECK(app_usbd_cdc_acm_read(p_cdc_acm,
                m_rx_buf, sizeof(m_rx_buf)));
        }
        break;

    default:
        break;
    }
}

static void clock_event_handler(nrf_drv_clock_evt_type_t event)
{
    ASSERT(event == NRF_DRV_CLOCK_EVT_HFCLK_STARTED);
    (void)event;

    NRF_LOG_DEBUG("Clock started\r\n");

    APP_ERROR_CHECK(app_usbd_init(NULL));
    APP_ERROR_CHECK(app_usbd_class_append(
        app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm)));

    app_usbd_enable();
    app_usbd_start();

    NRF_LOG_DEBUG("USB started\r\n");
}
static nrf_drv_clock_handler_item_t m_clock_handler_item = {
    NULL,
    clock_event_handler
};

uint32_t ser_phy_hci_slip_open(ser_phy_hci_slip_event_handler_t events_handler)
{
    if (events_handler == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Check if function was not called before.
    if (m_ser_phy_hci_slip_event_handler != NULL)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    serial_number_string_create();

    (void)nrf_drv_clock_init();
    nrf_drv_clock_hfclk_request(&m_clock_handler_item);

    m_ser_phy_hci_slip_event_handler = events_handler;

    mp_tx_buf        = m_tx_buf0;
    m_tx_bytes       = 0;
    m_tx_phase       = PHASE_IDLE;
    m_tx_in_progress = false;
    m_tx_pending     = false;

    m_rx_escape      = false;
    mp_small_buffer  = m_small_buffer;
    mp_big_buffer    = m_big_buffer;

    return NRF_SUCCESS;
}


void ser_phy_hci_slip_close(void)
{
    app_usbd_stop();
    app_usbd_disable();
    (void)app_usbd_uninit();
    nrf_drv_clock_hfclk_release();

    m_ser_phy_hci_slip_event_handler = NULL;
}
