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
 * @defgroup ser_phy_spi_phy_driver_slave ser_phy_nrf51_spi_slave.c
 * @{
 * @ingroup ser_phy_spi_phy_driver_slave
 *
 * @brief SPI_RAW PHY slave driver.
 */

#include <stddef.h>
#include <string.h>

#include "app_error.h"
#include "app_util.h"
#include "boards.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "nrf_soc.h"
#include "nrf_drv_spis.h"
#include "ser_config.h"
#include "ser_phy.h"
#include "ser_phy_config_conn.h"
#include "ser_phy_debug_conn.h"

#define SER_PHY_SPI_DEF_CHARACTER 0xFF //SPI default character. Character clocked out in case of an ignored transaction
#define SER_PHY_SPI_ORC_CHARACTER 0xFF //SPI over-read character. Character clocked out after an over-read of the transmit buffer

static nrf_drv_spis_t m_spis = NRF_DRV_SPIS_INSTANCE(SER_PHY_SPI_SLAVE_INSTANCE);

#ifdef NRF_SPIS0
#define SPI_SLAVE_REG              NRF_SPIS0
#else
#define SPI_SLAVE_REG              NRF_SPIS1
#endif

//SPI raw peripheral device configuration data
typedef struct
{
    int32_t pin_req;       //SPI /REQ pin. -1 for not using
    int32_t pin_rdy;       //SPI /RDY pin. -1 for not using
    int32_t ppi_rdy_ch;    //SPI /RDY ppi ready channel
    int32_t gpiote_rdy_ch; //SPI /RDY pin ready channel
} spi_slave_raw_trasp_cfg_t;

/**@brief States of the SPI transaction state machine. */
typedef enum
{
    SPI_RAW_STATE_UNKNOWN,
    SPI_RAW_STATE_SETUP_HEADER,
    SPI_RAW_STATE_RX_HEADER,
    SPI_RAW_STATE_MEM_REQUESTED,
    SPI_RAW_STATE_RX_PAYLOAD,
    SPI_RAW_STATE_TX_HEADER,
    SPI_RAW_STATE_TX_PAYLOAD,
} trans_state_t;

#define _static static

static spi_slave_raw_trasp_cfg_t m_spi_slave_raw_config;

_static uint16_t m_accumulated_rx_packet_length;
_static uint16_t m_rx_packet_length;
_static uint16_t m_current_rx_frame_length;

_static uint16_t m_accumulated_tx_packet_length;
_static uint16_t m_tx_packet_length;
_static uint16_t m_current_tx_frame_length;

_static uint8_t m_header_rx_buffer[SER_PHY_HEADER_SIZE];
_static uint8_t m_header_tx_buffer[SER_PHY_HEADER_SIZE];

_static uint8_t m_frame_buffer[SER_PHY_SPI_MTU_SIZE];          //trash storage
_static uint8_t m_zero_buffer[SER_PHY_SPI_MTU_SIZE] = {  0  }; //ROM'able declaration

_static uint8_t * volatile       m_p_rx_buffer = NULL;
_static const uint8_t * volatile m_p_tx_buffer = NULL;

_static bool m_trash_payload_flag;
_static bool m_buffer_reqested_flag;

_static trans_state_t            m_trans_state      = SPI_RAW_STATE_UNKNOWN;
_static ser_phy_events_handler_t m_ser_phy_callback = NULL;

static void spi_slave_raw_assert(bool cond)
{
    APP_ERROR_CHECK_BOOL(cond);
}

static void callback_ser_phy_event(ser_phy_evt_t event)
{
    if (m_ser_phy_callback)
    {
        m_ser_phy_callback(event);
    }
}

static void callback_memory_request(uint16_t size)
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_SLAVE_PHY_BUF_REQUEST(0);

    event.evt_type                               = SER_PHY_EVT_RX_BUF_REQUEST;
    event.evt_params.rx_buf_request.num_of_bytes = size;
    callback_ser_phy_event(event);
}

static void callback_packet_received(uint8_t * pBuffer, uint16_t size)
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_SLAVE_PHY_PKT_RECEIVED(0);

    event.evt_type = SER_PHY_EVT_RX_PKT_RECEIVED;
    event.evt_params.rx_pkt_received.num_of_bytes = size;
    event.evt_params.rx_pkt_received.p_buffer     = pBuffer;
    callback_ser_phy_event(event);
}

static void callback_packet_dropped()
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_SLAVE_PHY_PKT_DROPPED(0);

    event.evt_type = SER_PHY_EVT_RX_PKT_DROPPED;
    callback_ser_phy_event(event);
}

static void callback_packet_transmitted(void)
{
    ser_phy_evt_t event;

    DEBUG_EVT_SPI_SLAVE_PHY_PKT_SENT(0);

    event.evt_type = SER_PHY_EVT_TX_PKT_SENT;
    callback_ser_phy_event(event);
}

/* Function computes current packet length */
static uint16_t compute_current_frame_length(const uint16_t packet_length,
                                             const uint16_t accumulated_packet_length)
{
    uint16_t current_packet_length = packet_length - accumulated_packet_length;

    if (current_packet_length > SER_PHY_SPI_MTU_SIZE)
    {
        current_packet_length = SER_PHY_SPI_MTU_SIZE;
    }

    return current_packet_length;
}

static uint32_t header_get()
{
    uint32_t err_code;

    err_code = nrf_drv_spis_buffers_set(&m_spis,
                                        (uint8_t *) m_zero_buffer,
                                        SER_PHY_HEADER_SIZE,
                                        m_header_rx_buffer,
                                        SER_PHY_HEADER_SIZE);
    return err_code;
}

static uint32_t frame_get()
{
    uint32_t err_code;

    m_current_rx_frame_length = compute_current_frame_length(m_rx_packet_length,
                                                             m_accumulated_rx_packet_length);

    if (!m_trash_payload_flag)
    {
        err_code =
            nrf_drv_spis_buffers_set(&m_spis,
                                     (uint8_t *) m_zero_buffer,
                                     m_current_rx_frame_length,
                                     &(m_p_rx_buffer[m_accumulated_rx_packet_length]),
                                     m_current_rx_frame_length);
    }
    else
    {
        err_code = nrf_drv_spis_buffers_set(&m_spis,
                                            (uint8_t *) m_zero_buffer,
                                            m_current_rx_frame_length,
                                            m_frame_buffer,
                                            m_current_rx_frame_length);
    }
    return err_code;
}

static uint32_t header_send(uint16_t len)
{
    uint32_t err_code;

    (void) uint16_encode(len, m_header_tx_buffer);
    err_code =
        nrf_drv_spis_buffers_set(&m_spis,
                                 m_header_tx_buffer,
                                 sizeof (m_header_tx_buffer),
                                 m_header_rx_buffer,
                                 sizeof (m_header_tx_buffer));
    return err_code;
}

static uint32_t frame_send()
{
    uint32_t err_code;

    m_current_tx_frame_length = compute_current_frame_length(m_tx_packet_length,
                                                             m_accumulated_tx_packet_length);
    err_code                     =
        nrf_drv_spis_buffers_set(&m_spis,
                                 (uint8_t *) &(m_p_tx_buffer[m_accumulated_tx_packet_length]),
                                 m_current_tx_frame_length,
                                 m_frame_buffer,
                                 m_current_tx_frame_length);
    return err_code;
}

static void set_ready_line(void)
{
    //toggle - this should go high - but toggle is unsafe
    uint32_t rdy_task = nrf_drv_gpiote_out_task_addr_get(m_spi_slave_raw_config.pin_rdy);
    *(uint32_t *)rdy_task = 1;
    return;
}

static void set_request_line(void)
{
    //active low logic - set is 0
    nrf_gpio_pin_clear(m_spi_slave_raw_config.pin_req);
    DEBUG_EVT_SPI_SLAVE_RAW_REQ_SET(0);
}

static void clear_request_line(void)
{
    //active low logic - clear is 1
    nrf_gpio_pin_set(m_spi_slave_raw_config.pin_req);
    DEBUG_EVT_SPI_SLAVE_RAW_REQ_SET(0);
}

/**
 * \brief Slave driver main state machine
 * For UML graph, please refer to SDK documentation
*/
static void spi_slave_event_handle(nrf_drv_spis_event_t event)
{
    uint32_t        err_code = NRF_SUCCESS;
    static uint16_t packetLength;

    switch (m_trans_state)
    {
        case SPI_RAW_STATE_SETUP_HEADER:
            m_trans_state = SPI_RAW_STATE_RX_HEADER;
            err_code      = header_get();
            break;

        case SPI_RAW_STATE_RX_HEADER:

            if (event.evt_type == NRF_DRV_SPIS_BUFFERS_SET_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_BUFFERS_SET(0);
                set_ready_line();
            }

            if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_RX_XFER_DONE(event.rx_amount);
                spi_slave_raw_assert(event.rx_amount == SER_PHY_HEADER_SIZE);
                packetLength = uint16_decode(m_header_rx_buffer);

                if (packetLength != 0 )
                {
                    m_trans_state          = SPI_RAW_STATE_MEM_REQUESTED;
                    m_buffer_reqested_flag = true;
                    m_rx_packet_length     = packetLength;
                    callback_memory_request(packetLength);
                }
                else
                {
                    if (m_p_tx_buffer)
                    {
                        clear_request_line();
                        m_trans_state = SPI_RAW_STATE_TX_HEADER;
                        err_code      = header_send(m_tx_packet_length);
                    }
                    else
                    {
                        //there is nothing to send - zero response facilitates pooling - but perhaps, it should be assert
                        err_code = header_send(0);
                    }
                }
            }

            break;

        case SPI_RAW_STATE_MEM_REQUESTED:

            if (event.evt_type == NRF_DRV_SPIS_EVT_TYPE_MAX) //This is API dummy event
            {
                m_buffer_reqested_flag         = false;
                m_trans_state                  = SPI_RAW_STATE_RX_PAYLOAD;
                m_accumulated_rx_packet_length = 0;
                err_code                       = frame_get();
            }
            break;

        case SPI_RAW_STATE_RX_PAYLOAD:

            if (event.evt_type == NRF_DRV_SPIS_BUFFERS_SET_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_BUFFERS_SET(0);
                set_ready_line();
            }

            if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_RX_XFER_DONE(event.rx_amount);
                spi_slave_raw_assert(event.rx_amount == m_current_rx_frame_length);
                m_accumulated_rx_packet_length += m_current_rx_frame_length;

                if (m_accumulated_rx_packet_length < m_rx_packet_length )
                {
                    err_code = frame_get();
                }
                else
                {
                    spi_slave_raw_assert(m_accumulated_rx_packet_length == m_rx_packet_length);
                    m_trans_state = SPI_RAW_STATE_RX_HEADER;
                    err_code      = header_get();

                    if (!m_trash_payload_flag)
                    {
                        callback_packet_received(m_p_rx_buffer, m_accumulated_rx_packet_length);
                    }
                    else
                    {
                        callback_packet_dropped();
                    }
                }
            }
            break;

        case SPI_RAW_STATE_TX_HEADER:

            if (event.evt_type == NRF_DRV_SPIS_BUFFERS_SET_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_BUFFERS_SET(0);
                set_ready_line();
            }

            if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_TX_XFER_DONE(event.tx_amount);
                spi_slave_raw_assert(event.tx_amount == SER_PHY_HEADER_SIZE);
                m_trans_state                  = SPI_RAW_STATE_TX_PAYLOAD;
                m_accumulated_tx_packet_length = 0;
                err_code                       = frame_send();
            }

            break;

        case SPI_RAW_STATE_TX_PAYLOAD:

            if (event.evt_type == NRF_DRV_SPIS_BUFFERS_SET_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_BUFFERS_SET(0);
                set_ready_line();
            }

            if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
            {
                DEBUG_EVT_SPI_SLAVE_RAW_TX_XFER_DONE(event.tx_amount);
                spi_slave_raw_assert(event.tx_amount == m_current_tx_frame_length);
                m_accumulated_tx_packet_length += m_current_tx_frame_length;

                if ( m_accumulated_tx_packet_length < m_tx_packet_length )
                {
                    err_code = frame_send();
                }
                else
                {
                    spi_slave_raw_assert(m_accumulated_tx_packet_length == m_tx_packet_length);
                    //clear pointer before callback
                    m_p_tx_buffer = NULL;
                    callback_packet_transmitted();
                    //spi slave TX transfer is possible only when RX is ready, so return to waiting for a header
                    m_trans_state = SPI_RAW_STATE_RX_HEADER;
                    err_code      = header_get();
                }
            }
            break;

        default:
            err_code = NRF_ERROR_INVALID_STATE;
            break;
    }
    APP_ERROR_CHECK(err_code);
}

static void spi_slave_gpiote_init(void)
{
    if (!nrf_drv_gpiote_is_init())
    {
        (void)nrf_drv_gpiote_init();
    }
    nrf_drv_gpiote_out_config_t config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
    (void) nrf_drv_gpiote_out_init(m_spi_slave_raw_config.pin_rdy, &config);
    (void) nrf_drv_gpiote_out_task_enable(m_spi_slave_raw_config.pin_rdy);
    return;
}

static void spi_slave_ppi_init(void)
{
    uint32_t rdy_task = nrf_drv_gpiote_out_task_addr_get(m_spi_slave_raw_config.pin_rdy);
    //Configure PPI channel  to clear /RDY line
    NRF_PPI->CH[m_spi_slave_raw_config.ppi_rdy_ch].EEP = (uint32_t)(&SPI_SLAVE_REG->EVENTS_END);
    NRF_PPI->CH[m_spi_slave_raw_config.ppi_rdy_ch].TEP = rdy_task;

    //this works only for channels 0..15 - but soft device is using 8-15 anyway
    NRF_PPI->CHEN |= (1 << m_spi_slave_raw_config.ppi_rdy_ch);
    return;
}

static void spi_slave_gpio_init(void)
{
    nrf_gpio_pin_set(m_spi_slave_raw_config.pin_req);
    nrf_gpio_cfg_output(m_spi_slave_raw_config.pin_req);
    nrf_gpio_pin_set(m_spi_slave_raw_config.pin_rdy);
    nrf_gpio_cfg_output(m_spi_slave_raw_config.pin_rdy);
}

/* ser_phy API function */
void ser_phy_interrupts_enable(void)
{
    (void)sd_nvic_EnableIRQ(nrfx_get_irq_number(m_spis.p_reg));
}

/* ser_phy API function */
void ser_phy_interrupts_disable(void)
{
    (void)sd_nvic_DisableIRQ(nrfx_get_irq_number(m_spis.p_reg));
}

/* ser_phy API function */
uint32_t ser_phy_rx_buf_set(uint8_t * p_buffer)
{
    uint32_t             status = NRF_SUCCESS;
    nrf_drv_spis_event_t event;

    ser_phy_interrupts_disable();

    if (m_buffer_reqested_flag && (m_trans_state == SPI_RAW_STATE_MEM_REQUESTED))
    {
        m_p_rx_buffer = p_buffer;

        if (m_p_rx_buffer)
        {
            m_trash_payload_flag = false;
        }
        else
        {
            m_trash_payload_flag = true;
        }
        event.evt_type  = NRF_DRV_SPIS_EVT_TYPE_MAX; //force transition with dummy event
        event.rx_amount = 0;
        event.tx_amount = 0;
        spi_slave_event_handle(event);
    }
    else
    {
        status = NRF_ERROR_BUSY;
    }
    ser_phy_interrupts_enable();

    return status;
}

/* ser_phy API function */
uint32_t ser_phy_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes)
{
    uint32_t status = NRF_SUCCESS;

    if ( p_buffer == NULL || num_of_bytes == 0)
    {
        return NRF_ERROR_NULL;
    }

    ser_phy_interrupts_disable();

    if ( m_p_tx_buffer == NULL)
    {
        m_tx_packet_length = num_of_bytes;
        m_p_tx_buffer      = p_buffer;
        set_request_line();
    }
    else
    {
        status = NRF_ERROR_BUSY;
    }
    ser_phy_interrupts_enable();

    return status;
}

/* ser_phy API function */
uint32_t ser_phy_open(ser_phy_events_handler_t events_handler)
{
    uint32_t              err_code;
    nrf_drv_spis_config_t spi_slave_config;
    nrf_drv_spis_event_t  event;

    if (m_trans_state != SPI_RAW_STATE_UNKNOWN)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (events_handler == NULL)
    {
        return NRF_ERROR_NULL;
    }

    //one ppi channel and one gpiote channel are used to drive RDY line
    m_spi_slave_raw_config.pin_req       = SER_PHY_SPI_SLAVE_REQ_PIN;
    m_spi_slave_raw_config.pin_rdy       = SER_PHY_SPI_SLAVE_RDY_PIN;
    m_spi_slave_raw_config.ppi_rdy_ch    = SER_PHY_SPI_PPI_RDY_CH;
    m_spi_slave_raw_config.gpiote_rdy_ch = SER_PHY_SPI_GPIOTE_RDY_CH;

    spi_slave_gpio_init();
    spi_slave_gpiote_init();
    spi_slave_ppi_init();

    spi_slave_config.miso_pin         = SER_PHY_SPI_SLAVE_MISO_PIN;
    spi_slave_config.mosi_pin         = SER_PHY_SPI_SLAVE_MOSI_PIN;
    spi_slave_config.sck_pin          = SER_PHY_SPI_SLAVE_SCK_PIN;
    spi_slave_config.csn_pin          = SER_PHY_SPI_SLAVE_SS_PIN;
    spi_slave_config.mode             = NRF_DRV_SPIS_MODE_0;
    spi_slave_config.bit_order        = NRF_DRV_SPIS_BIT_ORDER_LSB_FIRST;
    spi_slave_config.def              = SER_PHY_SPI_DEF_CHARACTER;
    spi_slave_config.orc              = SER_PHY_SPI_ORC_CHARACTER;
    spi_slave_config.irq_priority     = APP_IRQ_PRIORITY_LOWEST;
    spi_slave_config.miso_drive       = NRF_DRV_SPIS_DEFAULT_MISO_DRIVE;
    //use /CS pullup because state of the line might be undefined when master redefines PIO lines
    spi_slave_config.csn_pullup       = NRF_GPIO_PIN_PULLUP;

    //keep /CS high when init
    nrf_gpio_cfg_input(spi_slave_config.csn_pin, NRF_GPIO_PIN_PULLUP);

    err_code = nrf_drv_spis_init(&m_spis, &spi_slave_config, spi_slave_event_handle);
    APP_ERROR_CHECK(err_code);

    if (err_code == NRF_SUCCESS)
    {
        m_ser_phy_callback = events_handler;

        m_trans_state   = SPI_RAW_STATE_SETUP_HEADER;
        event.evt_type  = NRF_DRV_SPIS_EVT_TYPE_MAX; //force transition for dummy event
        event.rx_amount = 0;
        event.tx_amount = 0;
        spi_slave_event_handle(event);

    }
    return err_code;
}

/* ser_phy API function */
void ser_phy_close(void)
{
    nrf_drv_spis_uninit(&m_spis);
    m_ser_phy_callback = NULL;
    m_trans_state      = SPI_RAW_STATE_UNKNOWN;
}
