/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include "ser_phy.h"
#include "ser_config.h"
#ifdef SER_CONNECTIVITY
    #include "ser_phy_config_conn.h"
#else
    #include "ser_phy_config_app.h"
#endif
#include "nrf_drv_uart.h"
#include "app_error.h"
#include "app_util.h"
#include "app_util_platform.h"

#define UART_TRANSFER_MAX 255

#if defined(UARTE_PRESENT) && !defined(UART_PRESENT)
#define SER_UART_IRQ UARTE0_IRQn
#else
#define SER_UART_IRQ UART0_IRQn
#endif

static const nrf_drv_uart_t m_uart = NRF_DRV_UART_INSTANCE(0);
static const nrf_drv_uart_config_t m_uart_config = {
    .pseltxd            = SER_PHY_UART_TX,
    .pselrxd            = SER_PHY_UART_RX,
    .pselrts            = SER_PHY_UART_RTS,
    .pselcts            = SER_PHY_UART_CTS,
    .p_context          = NULL,
    .interrupt_priority = UART_IRQ_PRIORITY,
#if defined(UARTE_PRESENT) && defined(UART_PRESENT)
    .use_easy_dma       = true,
#endif
    // These values are common for application and connectivity, they are
    // defined in "ser_config.h".
    .hwfc      = SER_PHY_UART_FLOW_CTRL,
    .parity    = SER_PHY_UART_PARITY,
    .baudrate  = (nrf_uart_baudrate_t)SER_PHY_UART_BAUDRATE
};

static bool volatile   m_tx_in_progress;
static uint8_t         m_tx_header_buf[SER_PHY_HEADER_SIZE];
static uint16_t        m_bytes_to_transmit;
static uint8_t const * mp_tx_buffer;

static uint8_t         m_rx_header_buf[SER_PHY_HEADER_SIZE];
static uint16_t        m_bytes_to_receive;
static uint8_t         m_rx_drop_buf[1];

static ser_phy_events_handler_t m_ser_phy_event_handler;
static ser_phy_evt_t m_ser_phy_rx_event;


static void packet_sent_callback(void)
{
    static ser_phy_evt_t const event = {
        .evt_type = SER_PHY_EVT_TX_PKT_SENT,
    };
    m_ser_phy_event_handler(event);
}

static void buffer_request_callback(uint16_t num_of_bytes)
{
    m_ser_phy_rx_event.evt_type = SER_PHY_EVT_RX_BUF_REQUEST;
    m_ser_phy_rx_event.evt_params.rx_buf_request.num_of_bytes = num_of_bytes;
    m_ser_phy_event_handler(m_ser_phy_rx_event);
}

static void packet_received_callback(void)
{
    m_ser_phy_event_handler(m_ser_phy_rx_event);
}

static void packet_dropped_callback(void)
{
    static ser_phy_evt_t const event = {
        .evt_type = SER_PHY_EVT_RX_PKT_DROPPED,
    };
    m_ser_phy_event_handler(event);
}

static void hardware_error_callback(uint32_t hw_error)
{
    ser_phy_evt_t event = {
        .evt_type = SER_PHY_EVT_HW_ERROR,
        .evt_params.hw_error.error_code = hw_error,
    };
    m_ser_phy_event_handler(event);
}

static void packet_rx_start(void)
{
    APP_ERROR_CHECK(nrf_drv_uart_rx(&m_uart, m_rx_header_buf,
        SER_PHY_HEADER_SIZE));
}

static void packet_byte_drop(void)
{
    APP_ERROR_CHECK(nrf_drv_uart_rx(&m_uart, m_rx_drop_buf, 1));
}

static void uart_event_handler(nrf_drv_uart_event_t * p_event,
                               void * p_context)
{
    (void)p_context;

    switch (p_event->type)
    {
        case NRF_DRV_UART_EVT_ERROR:
            // Process the error only if this is a parity or overrun error.
            // Break and framing errors will always occur before the other
            // side becomes active.
            if (p_event->data.error.error_mask &
                (NRF_UART_ERROR_PARITY_MASK | NRF_UART_ERROR_OVERRUN_MASK))
            {
                // Pass error source to upper layer.
                hardware_error_callback(p_event->data.error.error_mask);
            }

            packet_rx_start();
            break;

        case NRF_DRV_UART_EVT_TX_DONE:
            if (p_event->data.rxtx.p_data == m_tx_header_buf)
            {
#if (SER_HAL_TRANSPORT_TX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
                if (m_bytes_to_transmit > UART_TRANSFER_MAX)
                {
                    APP_ERROR_CHECK(nrf_drv_uart_tx(&m_uart, mp_tx_buffer,
                        UART_TRANSFER_MAX));
                }
                else
#endif // (SER_HAL_TRANSPORT_TX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
                {
                    APP_ERROR_CHECK(nrf_drv_uart_tx(&m_uart, mp_tx_buffer,
                        m_bytes_to_transmit));
                }
            }
            else
            {
#if (SER_HAL_TRANSPORT_TX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
                ASSERT(p_event->data.rxtx.bytes <= m_bytes_to_transmit);
                m_bytes_to_transmit -= p_event->data.rxtx.bytes;
                if (m_bytes_to_transmit != 0)
                {
                    APP_ERROR_CHECK(nrf_drv_uart_tx(&m_uart,
                        p_event->data.rxtx.p_data + p_event->data.rxtx.bytes,
                        m_bytes_to_transmit < UART_TRANSFER_MAX ?
                            m_bytes_to_transmit : UART_TRANSFER_MAX));
                }
                else
#endif // (SER_HAL_TRANSPORT_TX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
                {
                    m_tx_in_progress = false;
                    packet_sent_callback();
                }
            }
            break;

        case NRF_DRV_UART_EVT_RX_DONE:
            if (p_event->data.rxtx.p_data == m_rx_header_buf)
            {
                m_bytes_to_receive = uint16_decode(m_rx_header_buf);
                buffer_request_callback(m_bytes_to_receive);
            }
            else if (p_event->data.rxtx.p_data == m_rx_drop_buf)
            {
                --m_bytes_to_receive;
                if (m_bytes_to_receive != 0)
                {
                    packet_byte_drop();
                }
                else
                {
                    packet_dropped_callback();

                    packet_rx_start();
                }
            }
            else
            {
#if (SER_HAL_TRANSPORT_RX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
                ASSERT(p_event->data.rxtx.bytes <= m_bytes_to_receive);
                m_bytes_to_receive -= p_event->data.rxtx.bytes;
                if (m_bytes_to_receive != 0)
                {
                    APP_ERROR_CHECK(nrf_drv_uart_rx(&m_uart,
                        p_event->data.rxtx.p_data + p_event->data.rxtx.bytes,
                        m_bytes_to_receive < UART_TRANSFER_MAX ?
                            m_bytes_to_receive : UART_TRANSFER_MAX));
                }
                else
#endif // (SER_HAL_TRANSPORT_RX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
                {
                    packet_received_callback();

                    packet_rx_start();
                }
            }
            break;

        default:
            APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
    }
}

/** API FUNCTIONS */

uint32_t ser_phy_open(ser_phy_events_handler_t events_handler)
{
    uint32_t err_code;

    if (events_handler == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Check if function was not called before.
    if (m_ser_phy_event_handler != NULL)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    err_code = nrf_drv_uart_init(&m_uart, &m_uart_config, uart_event_handler);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_ser_phy_event_handler = events_handler;

    packet_rx_start();

    return err_code;
}

uint32_t ser_phy_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes)
{
    if (p_buffer == NULL)
    {
        return NRF_ERROR_NULL;
    }
    else if (num_of_bytes == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    bool busy;

    CRITICAL_REGION_ENTER();
    busy = m_tx_in_progress;
    m_tx_in_progress = true;
    CRITICAL_REGION_EXIT();

    if (busy)
    {
        return NRF_ERROR_BUSY;
    }

    (void)uint16_encode(num_of_bytes, m_tx_header_buf);
    mp_tx_buffer = p_buffer;
    m_bytes_to_transmit = num_of_bytes;
    APP_ERROR_CHECK(nrf_drv_uart_tx(&m_uart, m_tx_header_buf,
        SER_PHY_HEADER_SIZE));

    return NRF_SUCCESS;
}


uint32_t ser_phy_rx_buf_set(uint8_t * p_buffer)
{

    if (m_ser_phy_rx_event.evt_type != SER_PHY_EVT_RX_BUF_REQUEST)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_ser_phy_rx_event.evt_type = SER_PHY_EVT_RX_PKT_RECEIVED;
    m_ser_phy_rx_event.evt_params.rx_pkt_received.p_buffer = p_buffer;
    m_ser_phy_rx_event.evt_params.rx_pkt_received.num_of_bytes =
        m_bytes_to_receive;

    // If there is not enough memory to receive the packet (no buffer was
    // provided), drop its data byte by byte (using an internal 1-byte buffer).
    if (p_buffer == NULL)
    {
        packet_byte_drop();
    }
#if (SER_HAL_TRANSPORT_RX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
    else if (m_bytes_to_receive > UART_TRANSFER_MAX)
    {
        APP_ERROR_CHECK(nrf_drv_uart_rx(&m_uart, p_buffer, UART_TRANSFER_MAX));
    }
#endif // (SER_HAL_TRANSPORT_RX_MAX_PKT_SIZE > UART_TRANSFER_MAX)
    else
    {
        APP_ERROR_CHECK(nrf_drv_uart_rx(&m_uart, p_buffer, m_bytes_to_receive));
    }

    return NRF_SUCCESS;
}


void ser_phy_close(void)
{
    nrf_drv_uart_uninit(&m_uart);
    m_ser_phy_event_handler = NULL;
}


void ser_phy_interrupts_enable(void)
{
    NVIC_EnableIRQ(SER_UART_IRQ);
}


void ser_phy_interrupts_disable(void)
{
    NVIC_DisableIRQ(SER_UART_IRQ);
}
