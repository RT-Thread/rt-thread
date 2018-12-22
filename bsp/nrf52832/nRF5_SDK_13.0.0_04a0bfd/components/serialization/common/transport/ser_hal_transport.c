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
#include <stdbool.h>
#include <string.h>
#include "app_error.h"
#include "ser_config.h"
#include "ser_phy.h"
#include "ser_hal_transport.h"

/**
 * @brief States of the RX state machine.
 */
typedef enum
{
    HAL_TRANSP_RX_STATE_CLOSED = 0,
    HAL_TRANSP_RX_STATE_IDLE,
    HAL_TRANSP_RX_STATE_RECEIVING,
    HAL_TRANSP_RX_STATE_DROPPING,
    HAL_TRANSP_RX_STATE_RECEIVED,
    HAL_TRANSP_RX_STATE_RECEIVED_PENDING_BUF_REQ,
    HAL_TRANSP_RX_STATE_RECEIVED_DROPPING,
    HAL_TRANSP_RX_STATE_MAX
}ser_hal_transp_rx_states_t;

/**
 * @brief States of the TX state machine.
 */
typedef enum
{
    HAL_TRANSP_TX_STATE_CLOSED = 0,
    HAL_TRANSP_TX_STATE_IDLE,
    HAL_TRANSP_TX_STATE_TX_ALLOCATED,
    HAL_TRANSP_TX_STATE_TRANSMITTING,
    HAL_TRANSP_TX_STATE_TRANSMITTED,
    HAL_TRANSP_TX_STATE_MAX
}ser_hal_transp_tx_states_t;

/**
 * @brief RX state.
 */
static ser_hal_transp_rx_states_t m_rx_state = HAL_TRANSP_RX_STATE_CLOSED;
/**
 * @brief TX state.
 */
static ser_hal_transp_tx_states_t m_tx_state = HAL_TRANSP_TX_STATE_CLOSED;

/**
 * @brief Transmission buffer.
 */
static uint8_t m_tx_buffer[SER_HAL_TRANSPORT_TX_MAX_PKT_SIZE];
/**
 * @brief Reception buffer.
 */
static uint8_t m_rx_buffer[SER_HAL_TRANSPORT_RX_MAX_PKT_SIZE];

/**
 * @brief Callback function handler for Serialization HAL Transport layer events.
 */
static ser_hal_transport_events_handler_t m_events_handler = NULL;


/**
 * @brief A callback function to be used to handle a PHY module events. This function is called in
 *        an interrupt context.
 */
static void phy_events_handler(ser_phy_evt_t phy_event)
{
    uint32_t                err_code = 0;
    ser_hal_transport_evt_t hal_transp_event;

    memset(&hal_transp_event, 0, sizeof (ser_hal_transport_evt_t));
    hal_transp_event.evt_type = SER_HAL_TRANSP_EVT_TYPE_MAX;

    switch (phy_event.evt_type)
    {
        case SER_PHY_EVT_TX_PKT_SENT:
        {
            if (HAL_TRANSP_TX_STATE_TRANSMITTING == m_tx_state)
            {
                m_tx_state = HAL_TRANSP_TX_STATE_TRANSMITTED;
                err_code   = ser_hal_transport_tx_pkt_free(m_tx_buffer);
                APP_ERROR_CHECK(err_code);
                /* An event to an upper layer that a packet has been transmitted. */
                hal_transp_event.evt_type = SER_HAL_TRANSP_EVT_TX_PKT_SENT;
                m_events_handler(hal_transp_event);
            }
            else
            {
                /* Lower layer should not generate this event in current state. */
                APP_ERROR_CHECK_BOOL(false);
            }
            break;
        }

        case SER_PHY_EVT_RX_BUF_REQUEST:
        {
            /* An event to an upper layer that a packet is being scheduled to receive or to drop. */
            hal_transp_event.evt_type = SER_HAL_TRANSP_EVT_RX_PKT_RECEIVING;

            /* Receive or drop a packet. */
            if (phy_event.evt_params.rx_buf_request.num_of_bytes <= sizeof (m_rx_buffer))
            {
                if (HAL_TRANSP_RX_STATE_IDLE == m_rx_state)
                {
                    m_events_handler(hal_transp_event);
                    err_code = ser_phy_rx_buf_set(m_rx_buffer);
                    APP_ERROR_CHECK(err_code);
                    m_rx_state = HAL_TRANSP_RX_STATE_RECEIVING;
                }
                else if (HAL_TRANSP_RX_STATE_RECEIVED == m_rx_state)
                {
                    /* It is OK to get know higher layer at this point that we are going to receive
                     * a new packet even though we will start receiving when rx buffer is freed. */
                    m_events_handler(hal_transp_event);
                    m_rx_state = HAL_TRANSP_RX_STATE_RECEIVED_PENDING_BUF_REQ;
                }
                else
                {
                    /* Lower layer should not generate this event in current state. */
                    APP_ERROR_CHECK_BOOL(false);
                }
            }
            else
            {
                /* There is not enough memory but packet has to be received to dummy location. */
                if (HAL_TRANSP_RX_STATE_IDLE == m_rx_state)
                {
                    m_events_handler(hal_transp_event);
                    err_code = ser_phy_rx_buf_set(NULL);
                    APP_ERROR_CHECK(err_code);
                    m_rx_state = HAL_TRANSP_RX_STATE_DROPPING;
                }
                else if (HAL_TRANSP_RX_STATE_RECEIVED == m_rx_state)
                {
                    m_events_handler(hal_transp_event);
                    err_code = ser_phy_rx_buf_set(NULL);
                    APP_ERROR_CHECK(err_code);
                    m_rx_state = HAL_TRANSP_RX_STATE_RECEIVED_DROPPING;
                }
                else
                {
                    /* Lower layer should not generate this event in current state. */
                    APP_ERROR_CHECK_BOOL(false);
                }
            }
            break;
        }

        case SER_PHY_EVT_RX_PKT_RECEIVED:
        {
            if (HAL_TRANSP_RX_STATE_RECEIVING == m_rx_state)
            {
                m_rx_state = HAL_TRANSP_RX_STATE_RECEIVED;
                /* Generate the event to an upper layer. */
                hal_transp_event.evt_type =
                    SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED;
                hal_transp_event.evt_params.rx_pkt_received.p_buffer =
                    phy_event.evt_params.rx_pkt_received.p_buffer;
                hal_transp_event.evt_params.rx_pkt_received.num_of_bytes =
                    phy_event.evt_params.rx_pkt_received.num_of_bytes;
                m_events_handler(hal_transp_event);
            }
            else
            {
                /* Lower layer should not generate this event in current state. */
                APP_ERROR_CHECK_BOOL(false);
            }
            break;
        }

        case SER_PHY_EVT_RX_PKT_DROPPED:
        {
            if (HAL_TRANSP_RX_STATE_DROPPING == m_rx_state)
            {
                /* Generate the event to an upper layer. */
                hal_transp_event.evt_type = SER_HAL_TRANSP_EVT_RX_PKT_DROPPED;
                m_events_handler(hal_transp_event);
                m_rx_state = HAL_TRANSP_RX_STATE_IDLE;
            }
            else if (HAL_TRANSP_RX_STATE_RECEIVED_DROPPING == m_rx_state)
            {
                /* Generate the event to an upper layer. */
                hal_transp_event.evt_type = SER_HAL_TRANSP_EVT_RX_PKT_DROPPED;
                m_events_handler(hal_transp_event);
                m_rx_state = HAL_TRANSP_RX_STATE_RECEIVED;
            }
            else
            {
                /* Lower layer should not generate this event in current state. */
                APP_ERROR_CHECK_BOOL(false);
            }
            break;
        }

        case SER_PHY_EVT_RX_OVERFLOW_ERROR:
        {
            /* Generate the event to an upper layer. */
            hal_transp_event.evt_type                        = SER_HAL_TRANSP_EVT_PHY_ERROR;
            hal_transp_event.evt_params.phy_error.error_type =
                SER_HAL_TRANSP_PHY_ERROR_RX_OVERFLOW;
            m_events_handler(hal_transp_event);
            break;
        }

        case SER_PHY_EVT_TX_OVERREAD_ERROR:
        {
            /* Generate the event to an upper layer. */
            hal_transp_event.evt_type                        = SER_HAL_TRANSP_EVT_PHY_ERROR;
            hal_transp_event.evt_params.phy_error.error_type =
                SER_HAL_TRANSP_PHY_ERROR_TX_OVERREAD;
            m_events_handler(hal_transp_event);
            break;
        }

        case SER_PHY_EVT_HW_ERROR:
        {
            /* Generate the event to an upper layer. */
            hal_transp_event.evt_type                        = SER_HAL_TRANSP_EVT_PHY_ERROR;
            hal_transp_event.evt_params.phy_error.error_type =
                SER_HAL_TRANSP_PHY_ERROR_HW_ERROR;
            hal_transp_event.evt_params.phy_error.hw_error_code =
                phy_event.evt_params.hw_error.error_code;
            if (HAL_TRANSP_TX_STATE_TRANSMITTING == m_tx_state)
            {
                m_tx_state = HAL_TRANSP_TX_STATE_TRANSMITTED;
                err_code   = ser_hal_transport_tx_pkt_free(phy_event.evt_params.hw_error.p_buffer);
                APP_ERROR_CHECK(err_code);
                /* An event to an upper layer that a packet has been transmitted. */
            }
            else if (HAL_TRANSP_RX_STATE_RECEIVING == m_rx_state)
            {
                m_rx_state = HAL_TRANSP_RX_STATE_RECEIVED;
                err_code   = ser_hal_transport_rx_pkt_free(phy_event.evt_params.hw_error.p_buffer);
                APP_ERROR_CHECK(err_code);
            }
            m_events_handler(hal_transp_event);

            break;
        }

        default:
        {
            APP_ERROR_CHECK_BOOL(false);
            break;
        }
    }
}

uint32_t ser_hal_transport_open(ser_hal_transport_events_handler_t events_handler)
{
    uint32_t err_code = NRF_SUCCESS;

    if ((HAL_TRANSP_RX_STATE_CLOSED != m_rx_state) || (HAL_TRANSP_TX_STATE_CLOSED != m_tx_state))
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }
    else if (NULL == events_handler)
    {
        err_code = NRF_ERROR_NULL;
    }
    else
    {
        /* We have to change states before calling lower layer because ser_phy_open() function is
         * going to enable interrupts. On success an event from PHY layer can be emitted immediately
         * after return from ser_phy_open(). */
        m_rx_state = HAL_TRANSP_RX_STATE_IDLE;
        m_tx_state = HAL_TRANSP_TX_STATE_IDLE;

        m_events_handler = events_handler;

        /* Initialize a PHY module. */
        err_code = ser_phy_open(phy_events_handler);

        if (NRF_SUCCESS != err_code)
        {
            m_rx_state       = HAL_TRANSP_RX_STATE_CLOSED;
            m_tx_state       = HAL_TRANSP_TX_STATE_CLOSED;
            m_events_handler = NULL;

            if (NRF_ERROR_INVALID_PARAM != err_code)
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }
    }

    return err_code;
}


void ser_hal_transport_close(void)
{
    /* Reset generic handler for all events, reset internal states and close PHY module. */
    ser_phy_interrupts_disable();
    m_rx_state = HAL_TRANSP_RX_STATE_CLOSED;
    m_tx_state = HAL_TRANSP_TX_STATE_CLOSED;

    m_events_handler = NULL;

    ser_phy_close();
}


uint32_t ser_hal_transport_rx_pkt_free(uint8_t * p_buffer)
{
    uint32_t err_code = NRF_SUCCESS;

    ser_phy_interrupts_disable();

    if (NULL == p_buffer)
    {
        err_code = NRF_ERROR_NULL;
    }
    else if (p_buffer != m_rx_buffer)
    {
        err_code = NRF_ERROR_INVALID_ADDR;
    }
    else if (HAL_TRANSP_RX_STATE_RECEIVED == m_rx_state)
    {
        m_rx_state = HAL_TRANSP_RX_STATE_IDLE;
    }
    else if (HAL_TRANSP_RX_STATE_RECEIVED_DROPPING == m_rx_state)
    {
        m_rx_state = HAL_TRANSP_RX_STATE_DROPPING;
    }
    else if (HAL_TRANSP_RX_STATE_RECEIVED_PENDING_BUF_REQ == m_rx_state)
    {
        err_code = ser_phy_rx_buf_set(m_rx_buffer);

        if (NRF_SUCCESS == err_code)
        {
            m_rx_state = HAL_TRANSP_RX_STATE_RECEIVING;
        }
        else
        {
            err_code = NRF_ERROR_INTERNAL;
        }
    }
    else
    {
        /* Upper layer should not call this function in current state. */
        err_code = NRF_ERROR_INVALID_STATE;
    }
    ser_phy_interrupts_enable();

    return err_code;
}


uint32_t ser_hal_transport_tx_pkt_alloc(uint8_t * * pp_memory, uint16_t * p_num_of_bytes)
{
    uint32_t err_code = NRF_SUCCESS;

    if ((NULL == pp_memory) || (NULL == p_num_of_bytes))
    {
        err_code = NRF_ERROR_NULL;
    }
    else if (HAL_TRANSP_TX_STATE_CLOSED == m_tx_state)
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }
    else if (HAL_TRANSP_TX_STATE_IDLE == m_tx_state)
    {
        m_tx_state      = HAL_TRANSP_TX_STATE_TX_ALLOCATED;
        *pp_memory      = &m_tx_buffer[0];
        *p_num_of_bytes = (uint16_t)sizeof (m_tx_buffer);
    }
    else
    {
        err_code = NRF_ERROR_NO_MEM;
    }

    return err_code;
}


uint32_t ser_hal_transport_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes)
{
    uint32_t err_code = NRF_SUCCESS;

    /* The buffer provided to this function must be allocated through ser_hal_transport_tx_alloc()
     * function - this assures correct state and that correct memory buffer is used. */
    if (NULL == p_buffer)
    {
        err_code = NRF_ERROR_NULL;
    }
    else if (0 == num_of_bytes)
    {
        err_code = NRF_ERROR_INVALID_PARAM;
    }
    else if (p_buffer != m_tx_buffer)
    {
        err_code = NRF_ERROR_INVALID_ADDR;
    }
    else if (num_of_bytes > sizeof (m_tx_buffer))
    {
        err_code = NRF_ERROR_DATA_SIZE;
    }
    else if (HAL_TRANSP_TX_STATE_TX_ALLOCATED == m_tx_state)
    {
        ser_phy_interrupts_disable();
        err_code = ser_phy_tx_pkt_send(p_buffer, num_of_bytes);

        if (NRF_SUCCESS == err_code)
        {
            m_tx_state = HAL_TRANSP_TX_STATE_TRANSMITTING;
        }
        else
        {
            if (NRF_ERROR_BUSY != err_code)
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }
        ser_phy_interrupts_enable();
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}


uint32_t ser_hal_transport_tx_pkt_free(uint8_t * p_buffer)
{
    uint32_t err_code = NRF_SUCCESS;

    if (NULL == p_buffer)
    {
        err_code = NRF_ERROR_NULL;
    }
    else if (p_buffer != m_tx_buffer)
    {
        err_code = NRF_ERROR_INVALID_ADDR;
    }
    else if ((HAL_TRANSP_TX_STATE_TX_ALLOCATED == m_tx_state) ||
             (HAL_TRANSP_TX_STATE_TRANSMITTED == m_tx_state))
    {
        /* Release TX buffer for use. */
        m_tx_state = HAL_TRANSP_TX_STATE_IDLE;
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}
