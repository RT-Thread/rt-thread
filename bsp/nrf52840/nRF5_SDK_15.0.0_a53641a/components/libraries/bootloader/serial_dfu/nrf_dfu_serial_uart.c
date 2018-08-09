/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#include "nrf_dfu_serial.h"

#include <string.h>
#include "boards.h"
#include "app_util_platform.h"
#include "nrf_dfu_transport.h"
#include "nrf_dfu_req_handler.h"
#include "slip.h"
#include "nrf_balloc.h"
#include "nrf_drv_uart.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_serial_uart
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@file
 *
 * @defgroup nrf_dfu_serial_uart DFU Serial UART transport
 * @ingroup  nrf_dfu
 * @brief    Device Firmware Update (DFU) transport layer using UART.
 */
 
#define NRF_SERIAL_OPCODE_SIZE          (sizeof(uint8_t))
#define NRF_UART_MAX_RESPONSE_SIZE_SLIP (2 * NRF_SERIAL_MAX_RESPONSE_SIZE + 1)
#define RX_BUF_SIZE                     (64) //to get 64bytes payload
#define OPCODE_OFFSET                   (sizeof(uint32_t) - NRF_SERIAL_OPCODE_SIZE)
#define DATA_OFFSET                     (OPCODE_OFFSET + NRF_SERIAL_OPCODE_SIZE)
#define UART_SLIP_MTU                   (2 * (RX_BUF_SIZE + 1) + 1)
#define BALLOC_BUF_SIZE                 ((CEIL_DIV((RX_BUF_SIZE+OPCODE_SIZE),sizeof(uint32_t))*sizeof(uint32_t)))

NRF_BALLOC_DEF(m_payload_pool, (UART_SLIP_MTU + 1), NRF_DFU_SERIAL_UART_RX_BUFFERS);

static nrf_drv_uart_t m_uart =  NRF_DRV_UART_INSTANCE(0);
static uint8_t m_rx_byte;

static nrf_dfu_serial_t m_serial;
static slip_t m_slip;
static uint8_t m_rsp_buf[NRF_UART_MAX_RESPONSE_SIZE_SLIP];
static bool m_active;

static nrf_dfu_observer_t m_observer;

static uint32_t uart_dfu_transport_init(nrf_dfu_observer_t observer);
static uint32_t uart_dfu_transport_close(nrf_dfu_transport_t const * p_exception);

DFU_TRANSPORT_REGISTER(nrf_dfu_transport_t const uart_dfu_transport) =
{
    .init_func  = uart_dfu_transport_init,
    .close_func = uart_dfu_transport_close,
};

static void payload_free(void * p_buf)
{
    uint8_t * p_buf_root = (uint8_t *)p_buf - DATA_OFFSET; //pointer is shifted to point to data
    nrf_balloc_free(&m_payload_pool, p_buf_root);
}

static ret_code_t rsp_send(uint8_t const * p_data, uint32_t length)
{
    uint32_t slip_len;
    (void) slip_encode(m_rsp_buf, (uint8_t *)p_data, length, &slip_len);

    return nrf_drv_uart_tx(&m_uart, m_rsp_buf, slip_len);
}

static __INLINE void on_rx_complete(nrf_dfu_serial_t * p_transport, uint8_t * p_data, uint8_t len)
{
    ret_code_t ret_code;

    ret_code = slip_decode_add_byte(&m_slip, p_data[0]);
    (void) nrf_drv_uart_rx(&m_uart, &m_rx_byte, 1);

    if (ret_code == NRF_SUCCESS)
    {
        // Activity detected on current transport, close all except active one.
        UNUSED_RETURN_VALUE(nrf_dfu_transports_close(&uart_dfu_transport));

        nrf_dfu_serial_on_packet_received(p_transport,
                                         (uint8_t const *)m_slip.p_buffer,
                                         m_slip.current_index);

        uint8_t * p_rx_buf = nrf_balloc_alloc(&m_payload_pool);
        if (p_rx_buf == NULL)
        {
            NRF_LOG_ERROR("Failed to allocate buffer");
            return;
        }
        NRF_LOG_INFO("Allocated buffer %x", p_rx_buf);
        // reset the slip decoding
        m_slip.p_buffer      = &p_rx_buf[OPCODE_OFFSET];
        m_slip.current_index = 0;
        m_slip.state         = SLIP_STATE_DECODING;
    }

}

static void uart_event_handler(nrf_drv_uart_event_t * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_UART_EVT_RX_DONE:
            on_rx_complete((nrf_dfu_serial_t*)p_context,
                           p_event->data.rxtx.p_data,
                           p_event->data.rxtx.bytes);
            break;

        case NRF_DRV_UART_EVT_ERROR:
            APP_ERROR_HANDLER(p_event->data.error.error_mask);
            break;

        default:
            // No action.
            break;
    }
}

static uint32_t uart_dfu_transport_init(nrf_dfu_observer_t observer)
{
    uint32_t err_code = NRF_SUCCESS;

    if (m_active)
    {
        return err_code;
    }

    NRF_LOG_DEBUG("serial_dfu_transport_init()");

    m_observer = observer;

    err_code = nrf_balloc_init(&m_payload_pool);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    uint8_t * p_rx_buf = nrf_balloc_alloc(&m_payload_pool);

    m_slip.p_buffer      =  &p_rx_buf[OPCODE_OFFSET];
    m_slip.current_index = 0;
    m_slip.buffer_len    = UART_SLIP_MTU;
    m_slip.state         = SLIP_STATE_DECODING;

    m_serial.rsp_func           = rsp_send;
    m_serial.payload_free_func  = payload_free;
    m_serial.mtu                = UART_SLIP_MTU;
    m_serial.p_rsp_buf          = &m_rsp_buf[NRF_UART_MAX_RESPONSE_SIZE_SLIP -
                                            NRF_SERIAL_MAX_RESPONSE_SIZE];

    nrf_drv_uart_config_t uart_config = NRF_DRV_UART_DEFAULT_CONFIG;

    uart_config.pseltxd   = TX_PIN_NUMBER;
    uart_config.pselrxd   = RX_PIN_NUMBER;
    uart_config.pselcts   = CTS_PIN_NUMBER;
    uart_config.pselrts   = RTS_PIN_NUMBER;
    uart_config.hwfc      = NRF_DFU_SERIAL_UART_USES_HWFC ?
                                NRF_UART_HWFC_ENABLED : NRF_UART_HWFC_DISABLED;
    uart_config.p_context = &m_serial;

    err_code =  nrf_drv_uart_init(&m_uart, &uart_config, uart_event_handler);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed initializing uart");
        return err_code;
    }

    err_code = nrf_drv_uart_rx(&m_uart, &m_rx_byte, 1);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed initializing rx");
    }

    NRF_LOG_DEBUG("serial_dfu_transport_init() completed");

    m_active = true;

    if (m_observer)
    {
        m_observer(NRF_DFU_EVT_TRANSPORT_ACTIVATED);
    }

    return err_code;
}


static uint32_t uart_dfu_transport_close(nrf_dfu_transport_t const * p_exception)
{
    if ((m_active == true) && (p_exception != &uart_dfu_transport))
    {
        nrf_drv_uart_uninit(&m_uart);
        m_active = false;
    }

    return NRF_SUCCESS;
}

