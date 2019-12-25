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
/**@file
 *
 * @defgroup ser_phy_spi_phy_driver_master ser_phy_nrf51_spi_master.c
 * @{
 * @ingroup ser_phy_spi_phy_driver_master
 *
 * @brief SPI_RAW PHY master driver.
 */

#include <stdio.h>
#include "nrf_drv_gpiote.h"
#include "nrf_drv_spi.h"
#include "ser_phy.h"
#include "ser_config.h"
#include "app_util.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_error.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"
#include "boards.h"
#include "app_error.h"
#include "ser_phy_config_app.h"
#include "ser_phy_debug_app.h"

#define notUSE_PendSV

#ifdef USE_PendSV

#define SW_IRQn              PendSV_IRQn
#define SW_IRQ_Handler()     PendSV_Handler()
#define SET_Pend_SW_IRQ()    SCB->ICSR = SCB->ICSR | SCB_ICSR_PENDSVSET_Msk //NVIC_SetPendingIRQ(PendSV_IRQn) -  PendSV_IRQn is a negative - does not work with CMSIS

#else

#define SW_IRQn              SWI3_IRQn
#define SW_IRQ_Handler()     SWI3_IRQHandler()
#define SET_Pend_SW_IRQ()    NVIC_SetPendingIRQ(SWI3_IRQn)
#endif /* USE_PendSV */

typedef enum
{
    SER_PHY_STATE_IDLE = 0,
    SER_PHY_STATE_TX_HEADER,
    SER_PHY_STATE_TX_WAIT_FOR_RDY,
    SER_PHY_STATE_TX_PAYLOAD,
    SER_PHY_STATE_RX_WAIT_FOR_RDY,
    SER_PHY_STATE_TX_ZERO_HEADER,
    SER_PHY_STATE_RX_HEADER,
    SER_PHY_STATE_MEMORY_REQUEST,
    SER_PHY_STATE_RX_PAYLOAD,
    SER_PHY_STATE_DISABLED
} ser_phy_spi_master_state_t;

typedef enum
{
    SER_PHY_EVT_GPIO_RDY = 0,
    SER_PHY_EVT_GPIO_REQ,
    SER_PHY_EVT_SPI_TRANSFER_DONE,
    SER_PHY_EVT_TX_API_CALL,
    SER_PHY_EVT_RX_API_CALL
} ser_phy_event_source_t;

#define _static static

_static uint8_t * mp_tx_buffer = NULL;
_static uint16_t  m_tx_buf_len = 0;

_static uint8_t * mp_rx_buffer = NULL;
_static uint16_t  m_rx_buf_len = 0;
_static uint8_t   m_frame_buffer[SER_PHY_SPI_MTU_SIZE];
_static uint8_t   m_header_buffer[SER_PHY_HEADER_SIZE] = { 0 };

_static uint16_t m_tx_packet_length             = 0;
_static uint16_t m_accumulated_tx_packet_length = 0;
_static uint16_t m_current_tx_packet_length     = 0;

_static uint16_t m_rx_packet_length             = 0;
_static uint16_t m_accumulated_rx_packet_length = 0;
_static uint16_t m_current_rx_packet_length     = 0;

_static volatile bool m_pend_req_flag    = 0;
_static volatile bool m_pend_rdy_flag    = 0;
_static volatile bool m_pend_xfer_flag   = 0;
_static volatile bool m_pend_rx_api_flag = 0;
_static volatile bool m_pend_tx_api_flag = 0;

_static volatile bool m_slave_ready_flag   = false;
_static volatile bool m_slave_request_flag = false;

_static ser_phy_events_handler_t   m_callback_events_handler = NULL;
_static ser_phy_spi_master_state_t m_spi_master_state        = SER_PHY_STATE_DISABLED;

_static const nrf_drv_spi_t m_spi_master = SER_PHY_SPI_MASTER_INSTANCE;

static void ser_phy_switch_state(ser_phy_event_source_t evt_src);

static void spi_master_raw_assert(bool cond)
{
    APP_ERROR_CHECK_BOOL(cond);
}

void SW_IRQ_Handler()
{
    if (m_pend_req_flag)
    {
        m_pend_req_flag = false;
        DEBUG_EVT_SPI_MASTER_RAW_REQUEST(0);
        ser_phy_switch_state(SER_PHY_EVT_GPIO_REQ);
    }

    if (m_pend_rdy_flag)
    {
        m_pend_rdy_flag = false;
        DEBUG_EVT_SPI_MASTER_RAW_READY(0);
        ser_phy_switch_state(SER_PHY_EVT_GPIO_RDY);
    }

    if (m_pend_xfer_flag)
    {
        m_pend_xfer_flag = false;
        DEBUG_EVT_SPI_MASTER_RAW_XFER_DONE(0);
        ser_phy_switch_state(SER_PHY_EVT_SPI_TRANSFER_DONE);
    }

    if (m_pend_rx_api_flag)
    {
        m_pend_rx_api_flag = false;
        DEBUG_EVT_SPI_MASTER_RAW_API_CALL(0);
        ser_phy_switch_state(SER_PHY_EVT_RX_API_CALL);
    }

    if (m_pend_tx_api_flag)
    {
        m_pend_tx_api_flag = false;
        DEBUG_EVT_SPI_MASTER_RAW_API_CALL(0);
        ser_phy_switch_state(SER_PHY_EVT_TX_API_CALL);
    }
}

static void ser_phy_spi_master_ready(nrf_drv_gpiote_pin_t pin,
                                     nrf_gpiote_polarity_t action)
{
    if (nrf_gpio_pin_read(pin) == 0)
    {
        m_slave_ready_flag = true;
        m_pend_rdy_flag    = true;
    }
    else
    {
        m_slave_ready_flag = false;
    }

    DEBUG_EVT_SPI_MASTER_RAW_READY_EDGE((uint32_t) !m_slave_ready_flag);
    SET_Pend_SW_IRQ();
}

static void ser_phy_spi_master_request(nrf_drv_gpiote_pin_t pin,
                                       nrf_gpiote_polarity_t action)
{
    if (nrf_gpio_pin_read(pin) == 0)
    {
        m_slave_request_flag = true;
        m_pend_req_flag      = true;
    }
    else
    {
        m_slave_request_flag = false;
    }

    DEBUG_EVT_SPI_MASTER_RAW_REQUEST_EDGE((uint32_t) !m_slave_request_flag);
    SET_Pend_SW_IRQ();
}

/* Send event SER_PHY_EVT_TX_PKT_SENT */
static __INLINE void callback_packet_sent()
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_MASTER_PHY_TX_PKT_SENT(0);

    event.evt_type = SER_PHY_EVT_TX_PKT_SENT;
    m_callback_events_handler(event);
}

/* Send event SER_PHY_EVT_RX_PKT_DROPPED */
static __INLINE void callback_packet_dropped()
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_MASTER_PHY_RX_PKT_DROPPED(0);

    event.evt_type = SER_PHY_EVT_RX_PKT_DROPPED;
    m_callback_events_handler(event);
}

/* Send event SER_PHY_EVT_RX_PKT_RECEIVED */
static __INLINE void callback_packet_received()
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_MASTER_PHY_RX_PKT_RECEIVED(0);

    event.evt_type = SER_PHY_EVT_RX_PKT_RECEIVED;
    event.evt_params.rx_pkt_received.p_buffer     = mp_rx_buffer;
    event.evt_params.rx_pkt_received.num_of_bytes = m_rx_buf_len;
    m_callback_events_handler(event);
}

/* Send event SER_PHY_EVT_RX_BUF_REQUEST */
static __INLINE void callback_mem_request()
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_MASTER_PHY_BUF_REQUEST(0);

    event.evt_type                               = SER_PHY_EVT_RX_BUF_REQUEST;
    event.evt_params.rx_buf_request.num_of_bytes = m_rx_buf_len;
    m_callback_events_handler(event);
}

/* Release buffer */
static __INLINE void buffer_release(uint8_t * * const pp_buffer,
                                    uint16_t * const  p_buf_len)
{
    *pp_buffer = NULL;
    *p_buf_len = 0;
}

/* Function computes current packet length */
static uint16_t compute_current_packet_length(const uint16_t packet_length,
                                              const uint16_t accumulated_packet_length)
{
    uint16_t current_packet_length = packet_length - accumulated_packet_length;

    if (current_packet_length > SER_PHY_SPI_MTU_SIZE)
    {
        current_packet_length = SER_PHY_SPI_MTU_SIZE;
    }

    return current_packet_length;
}

static __INLINE uint32_t header_send(const uint16_t length)
{
    uint8_t buf_len_size = uint16_encode(length, m_header_buffer);

    return nrf_drv_spi_transfer(&m_spi_master, m_header_buffer, buf_len_size, NULL, 0);
}


static __INLINE uint32_t frame_send()
{
    uint32_t err_code;

    m_current_tx_packet_length = compute_current_packet_length(m_tx_packet_length,
                                                               m_accumulated_tx_packet_length);
    err_code                   =
        nrf_drv_spi_transfer(&m_spi_master,
                             &mp_tx_buffer[m_accumulated_tx_packet_length],
                             m_current_tx_packet_length,
                             NULL,
                             0);
    m_accumulated_tx_packet_length += m_current_tx_packet_length;
    return err_code;
}

static __INLINE uint32_t header_get()
{
    return nrf_drv_spi_transfer(&m_spi_master, NULL, 0, m_header_buffer, SER_PHY_HEADER_SIZE);
}

static __INLINE uint32_t frame_get()
{
    uint32_t err_code;

    m_current_rx_packet_length = compute_current_packet_length(m_rx_packet_length,
                                                               m_accumulated_rx_packet_length);

    if (mp_rx_buffer)
    {
        err_code = nrf_drv_spi_transfer(&m_spi_master,
                                        NULL,
                                        0,
                                        &(mp_rx_buffer[m_accumulated_rx_packet_length]),
                                        m_current_rx_packet_length);
    }
    else
    {
        err_code = nrf_drv_spi_transfer(&m_spi_master,
                                        NULL,
                                        0,
                                        m_frame_buffer,
                                        m_current_rx_packet_length);
    }
    return err_code;
}


/**
 * \brief Master driver main state machine
 * Executed only in the context of PendSV_Handler()
 * For UML graph, please refer to SDK documentation
*/
static void ser_phy_switch_state(ser_phy_event_source_t evt_src)
{
    uint32_t    err_code           = NRF_SUCCESS;
    static bool m_wait_for_ready_flag = false; //local scheduling flag to defer RDY events

    switch (m_spi_master_state)
    {

        case SER_PHY_STATE_IDLE:

            if (evt_src == SER_PHY_EVT_GPIO_REQ)
            {
                m_wait_for_ready_flag = false;

                if (m_slave_ready_flag)
                {
                    m_spi_master_state = SER_PHY_STATE_TX_ZERO_HEADER;
                    err_code           = header_send(0);
                }
                else
                {
                    m_spi_master_state = SER_PHY_STATE_RX_WAIT_FOR_RDY;
                }
            }
            else if (evt_src == SER_PHY_EVT_TX_API_CALL)
            {
                spi_master_raw_assert(mp_tx_buffer != NULL); //api event with tx_buffer == NULL has no sense
                m_wait_for_ready_flag = false;

                if (m_slave_ready_flag)
                {
                    m_spi_master_state = SER_PHY_STATE_TX_HEADER;
                    err_code           = header_send(m_tx_buf_len);
                }
                else
                {
                    m_spi_master_state = SER_PHY_STATE_TX_WAIT_FOR_RDY;
                }
            }
            break;

        case SER_PHY_STATE_TX_WAIT_FOR_RDY:

            if (evt_src == SER_PHY_EVT_GPIO_RDY)
            {
                m_spi_master_state = SER_PHY_STATE_TX_HEADER;
                err_code           = header_send(m_tx_buf_len);
            }
            break;

        case SER_PHY_STATE_RX_WAIT_FOR_RDY:

            if (evt_src == SER_PHY_EVT_GPIO_RDY)
            {
                m_spi_master_state = SER_PHY_STATE_TX_ZERO_HEADER;
                err_code           = header_send(0);

            }
            break;

        case SER_PHY_STATE_TX_HEADER:

            if (evt_src == SER_PHY_EVT_SPI_TRANSFER_DONE)
            {
                m_tx_packet_length             = m_tx_buf_len;
                m_accumulated_tx_packet_length = 0;

                if (m_slave_ready_flag)
                {
                    m_spi_master_state = SER_PHY_STATE_TX_PAYLOAD;
                    err_code           = frame_send();

                }
                else
                {
                    m_wait_for_ready_flag = true;
                }
            }
            else if ((evt_src == SER_PHY_EVT_GPIO_RDY) && m_wait_for_ready_flag)
            {
                m_wait_for_ready_flag = false;
                m_spi_master_state = SER_PHY_STATE_TX_PAYLOAD;
                err_code           = frame_send();
            }

            break;

        case SER_PHY_STATE_TX_PAYLOAD:

            if (evt_src == SER_PHY_EVT_SPI_TRANSFER_DONE)
            {
                if (m_accumulated_tx_packet_length < m_tx_packet_length)
                {
                    if (m_slave_ready_flag)
                    {
                        err_code = frame_send();
                    }
                    else
                    {
                        m_wait_for_ready_flag = true;
                    }
                }
                else
                {
                    spi_master_raw_assert(m_accumulated_tx_packet_length == m_tx_packet_length);
                    buffer_release(&mp_tx_buffer, &m_tx_buf_len);
                    callback_packet_sent();
                    if ( m_slave_request_flag)
                    {
                        if (m_slave_ready_flag)
                        {
                            m_spi_master_state = SER_PHY_STATE_TX_ZERO_HEADER;
                            err_code           = header_send(0);
                        }
                        else
                        {
                            m_spi_master_state = SER_PHY_STATE_RX_WAIT_FOR_RDY;
                        }
                    }
                    else
                    {
                        m_spi_master_state = SER_PHY_STATE_IDLE; //m_Tx_buffer is NULL - have to wait for API event
                    }
                }
            }
            else if ((evt_src == SER_PHY_EVT_GPIO_RDY) && m_wait_for_ready_flag )
            {
                m_wait_for_ready_flag = false;
                err_code           = frame_send();
            }

            break;

        case SER_PHY_STATE_TX_ZERO_HEADER:

            if (evt_src == SER_PHY_EVT_SPI_TRANSFER_DONE)
            {
                if (m_slave_ready_flag)
                {
                    m_spi_master_state = SER_PHY_STATE_RX_HEADER;
                    err_code           = header_get();
                }
                else
                {
                    m_wait_for_ready_flag = true;
                }
            }
            else if ( (evt_src == SER_PHY_EVT_GPIO_RDY) && m_wait_for_ready_flag)
            {
                m_wait_for_ready_flag = false;
                m_spi_master_state = SER_PHY_STATE_RX_HEADER;
                err_code           = header_get();
            }
            break;

        case SER_PHY_STATE_RX_HEADER:

            if (evt_src == SER_PHY_EVT_SPI_TRANSFER_DONE)
            {
                m_spi_master_state = SER_PHY_STATE_MEMORY_REQUEST;
                m_rx_buf_len       = uint16_decode(m_header_buffer);
                m_rx_packet_length = m_rx_buf_len;
                callback_mem_request();

            }
            break;

        case SER_PHY_STATE_MEMORY_REQUEST:

            if (evt_src == SER_PHY_EVT_RX_API_CALL)
            {
                m_accumulated_rx_packet_length = 0;

                if (m_slave_ready_flag)
                {
                    m_spi_master_state = SER_PHY_STATE_RX_PAYLOAD;
                    err_code           = frame_get();
                }
                else
                {
                    m_wait_for_ready_flag = true;
                }
            }
            else if ((evt_src == SER_PHY_EVT_GPIO_RDY) && m_wait_for_ready_flag)
            {
                m_wait_for_ready_flag = false;
                m_spi_master_state = SER_PHY_STATE_RX_PAYLOAD;
                err_code           = frame_get();
            }
            break;

        case SER_PHY_STATE_RX_PAYLOAD:

            if (evt_src == SER_PHY_EVT_SPI_TRANSFER_DONE)
            {
                m_accumulated_rx_packet_length += m_current_rx_packet_length;

                if (m_accumulated_rx_packet_length < m_rx_packet_length)
                {
                    if (m_slave_ready_flag)
                    {
                        err_code = frame_get();
                    }
                    else
                    {
                        m_wait_for_ready_flag = true;
                    }
                }
                else
                {
                    spi_master_raw_assert(m_accumulated_rx_packet_length == m_rx_packet_length);

                    if (mp_rx_buffer == NULL)
                    {
                        callback_packet_dropped();
                    }
                    else
                    {
                        callback_packet_received();
                    }
                    buffer_release(&mp_rx_buffer, &m_rx_buf_len);
                    if (mp_tx_buffer != NULL) //mp_tx_buffer !=NULL, this means that API_EVT was scheduled
                    {
                        if (m_slave_ready_flag )
                        {
                            err_code           = header_send(m_tx_buf_len);
                            m_spi_master_state = SER_PHY_STATE_TX_HEADER;
                        }
                        else
                        {
                            m_spi_master_state = SER_PHY_STATE_TX_WAIT_FOR_RDY;
                        }
                    }
                    else if (m_slave_request_flag)
                    {
                        if (m_slave_ready_flag)
                        {
                            m_spi_master_state = SER_PHY_STATE_TX_ZERO_HEADER;
                            err_code           = header_send(0);
                        }
                        else
                        {
                            m_spi_master_state = SER_PHY_STATE_RX_WAIT_FOR_RDY;
                        }
                    }
                    else
                    {
                        m_spi_master_state = SER_PHY_STATE_IDLE;

                    }
                }

            }
            else if ( evt_src == SER_PHY_EVT_GPIO_RDY && m_wait_for_ready_flag)
            {
                m_wait_for_ready_flag = false;
                err_code           = frame_get();
            }
            break;

        default:
            break;
    }

    if (err_code != NRF_SUCCESS)
    {
        (void)err_code;
    }
}

static void ser_phy_spi_master_event_handler(nrf_drv_spi_evt_t const * p_event,
                                             void *                    p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_SPI_EVENT_DONE:

            /* Switch state */
            m_pend_xfer_flag = true;
            SET_Pend_SW_IRQ();

            break;

        default:
            break;
    }
}

static void ser_phy_init_PendSV(void)
{
    NVIC_SetPriority(SW_IRQn, APP_IRQ_PRIORITY_MID);
    NVIC_EnableIRQ(SW_IRQn);
}

static ret_code_t ser_phy_init_gpiote(void)
{
    if (!nrf_drv_gpiote_is_init())
    {
        (void)nrf_drv_gpiote_init();
    }
    NVIC_SetPriority(GPIOTE_IRQn, APP_IRQ_PRIORITY_HIGH);

    nrf_drv_gpiote_in_config_t config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    /* Enable pullup to ensure high state while connectivity device is reset */
    config.pull = NRF_GPIO_PIN_PULLUP;
    ret_code_t err_code = nrf_drv_gpiote_in_init(SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST,
        &config, ser_phy_spi_master_request);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    nrf_drv_gpiote_in_event_enable(SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST,true);

    err_code = nrf_drv_gpiote_in_init(SER_PHY_SPI_MASTER_PIN_SLAVE_READY,
        &config, ser_phy_spi_master_ready);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    nrf_drv_gpiote_in_event_enable(SER_PHY_SPI_MASTER_PIN_SLAVE_READY,true);

    m_slave_request_flag = !(nrf_gpio_pin_read(SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST));
    m_slave_ready_flag   = !(nrf_gpio_pin_read(SER_PHY_SPI_MASTER_PIN_SLAVE_READY));

    NVIC_ClearPendingIRQ(SW_IRQn);

    return NRF_SUCCESS;
}

static void ser_phy_deinit_gpiote(void)
{
    nrf_drv_gpiote_in_uninit(SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST);
    nrf_drv_gpiote_in_uninit(SER_PHY_SPI_MASTER_PIN_SLAVE_READY);
}

/* ser_phy API function */
uint32_t ser_phy_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes)
{
    if (p_buffer == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (num_of_bytes == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (mp_tx_buffer != NULL)
    {
        return NRF_ERROR_BUSY;
    }

    //ser_phy_interrupts_disable();
    CRITICAL_REGION_ENTER();
    mp_tx_buffer       = (uint8_t *)p_buffer;
    m_tx_buf_len       = num_of_bytes;
    m_pend_tx_api_flag = true;
    SET_Pend_SW_IRQ();
    //ser_phy_interrupts_enable();
    CRITICAL_REGION_EXIT();

    return NRF_SUCCESS;
}
/* ser_phy API function */
uint32_t ser_phy_rx_buf_set(uint8_t * p_buffer)
{
    if (m_spi_master_state != SER_PHY_STATE_MEMORY_REQUEST)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    //ser_phy_interrupts_disable();
    CRITICAL_REGION_ENTER();
    mp_rx_buffer       = p_buffer;
    m_pend_rx_api_flag = true;
    SET_Pend_SW_IRQ();
    //ser_phy_interrupts_enable();
    CRITICAL_REGION_EXIT();

    return NRF_SUCCESS;
}

/* ser_phy API function */
uint32_t ser_phy_open(ser_phy_events_handler_t events_handler)
{
    if (m_spi_master_state != SER_PHY_STATE_DISABLED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (events_handler == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t err_code = NRF_SUCCESS;

    m_spi_master_state        = SER_PHY_STATE_IDLE;
    m_callback_events_handler = events_handler;
    nrf_drv_spi_config_t spi_master_config = {
        .sck_pin      = SER_PHY_SPI_MASTER_PIN_SCK,
        .mosi_pin     = SER_PHY_SPI_MASTER_PIN_MOSI,
        .miso_pin     = SER_PHY_SPI_MASTER_PIN_MISO,
        .ss_pin       = SER_PHY_SPI_MASTER_PIN_SLAVE_SELECT,
        .irq_priority = APP_IRQ_PRIORITY_MID,
        .orc          = 0,
        .frequency    = SER_PHY_SPI_FREQUENCY,
        .mode         = NRF_DRV_SPI_MODE_0,
        .bit_order    = NRF_DRV_SPI_BIT_ORDER_LSB_FIRST,
    };
    err_code = nrf_drv_spi_init(&m_spi_master,
                                &spi_master_config,
                                ser_phy_spi_master_event_handler,
                                NULL);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = ser_phy_init_gpiote();
    ser_phy_init_PendSV();
    return err_code;
}

/* ser_phy API function */
void ser_phy_close(void)
{
    m_spi_master_state = SER_PHY_STATE_DISABLED;

    m_callback_events_handler = NULL;

    buffer_release(&mp_tx_buffer, &m_tx_buf_len);
    buffer_release(&mp_rx_buffer, &m_rx_buf_len);

    m_tx_packet_length             = 0;
    m_accumulated_tx_packet_length = 0;
    m_current_tx_packet_length     = 0;

    m_rx_packet_length             = 0;
    m_accumulated_rx_packet_length = 0;
    m_current_rx_packet_length     = 0;

    ser_phy_deinit_gpiote();
    nrf_drv_spi_uninit(&m_spi_master);
}

/* ser_phy API function */
/* only PendSV may interact with ser_phy layer, other interrupts are internal */
void ser_phy_interrupts_enable(void)
{
    NVIC_EnableIRQ(SW_IRQn);
}

/* ser_phy API function */
void ser_phy_interrupts_disable(void)
{
    NVIC_DisableIRQ(SW_IRQn);
}

/** @} */
