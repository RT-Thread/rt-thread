/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_transport.h"
#include "slip.h"
#include "nrf_balloc.h"
#include "nrf_drv_power.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_usbd.h"
#include "nrf_dfu_serial.h"
#include "app_scheduler.h"
#include "app_usbd.h"
#include "app_usbd_cdc_acm.h"
#include "app_usbd_core.h"
#include "app_usbd_string_desc.h"
#include "app_util_platform.h"
#include "app_usbd_serial_num.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_serial_usb
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@file
 *
 * @defgroup nrf_dfu_serial_usb DFU Serial USB CDC ACM transport
 * @ingroup  nrf_dfu
 * @brief    Device Firmware Update (DFU) transport layer using USB CDC ACM.
 */
 
#define NRF_SERIAL_OPCODE_SIZE          (sizeof(uint8_t))

#define NRF_USB_MAX_RESPONSE_SIZE_SLIP  (2 * NRF_SERIAL_MAX_RESPONSE_SIZE + 1)

#define RX_BUF_SIZE                     (1024)
#define SLIP_MTU                        (2 * (RX_BUF_SIZE + 1) + 1)
#define OPCODE_OFFSET                   (sizeof(uint32_t) - NRF_SERIAL_OPCODE_SIZE)
#define DATA_OFFSET                     (OPCODE_OFFSET + NRF_SERIAL_OPCODE_SIZE)

#define CDC_ACM_COMM_INTERFACE          0
#define CDC_ACM_COMM_EPIN               NRF_DRV_USBD_EPIN2
#define CDC_ACM_DATA_INTERFACE          1
#define CDC_ACM_DATA_EPIN               NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT              NRF_DRV_USBD_EPOUT1

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

/**
 * @brief Interfaces list passed to @ref APP_USBD_CDC_ACM_GLOBAL_DEF
 * */
#define CDC_ACM_INTERFACES_CONFIG()                                                                \
    APP_USBD_CDC_ACM_CONFIG(CDC_ACM_COMM_INTERFACE,                                                \
                            CDC_ACM_COMM_EPIN,                                                     \
                            CDC_ACM_DATA_INTERFACE,                                                \
                            CDC_ACM_DATA_EPIN,                                                     \
                            CDC_ACM_DATA_EPOUT)

/*lint -save -e26 -e64 -e505 -e651 */
static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event);

/**@brief CDC_ACM class instance. */
APP_USBD_CDC_ACM_GLOBAL_DEF(m_app_cdc_acm,
                            cdc_acm_user_ev_handler,
                            CDC_ACM_COMM_INTERFACE,
                            CDC_ACM_DATA_INTERFACE,
                            CDC_ACM_COMM_EPIN,
                            CDC_ACM_DATA_EPIN,
                            CDC_ACM_DATA_EPOUT,
                            APP_USBD_CDC_COMM_PROTOCOL_NONE);
/*lint -restore */

NRF_BALLOC_DEF(m_payload_pool, (SLIP_MTU+1), NRF_DFU_SERIAL_USB_RX_BUFFERS);

static nrf_dfu_serial_t m_serial;
static slip_t m_slip;
static uint8_t m_rsp_buf[NRF_USB_MAX_RESPONSE_SIZE_SLIP];
static uint8_t m_rx_buf[NRF_DRV_USBD_EPSIZE];

static nrf_dfu_observer_t m_observer;

static uint32_t usb_dfu_transport_init(nrf_dfu_observer_t observer);
static uint32_t usb_dfu_transport_close(nrf_dfu_transport_t const * p_exception);


DFU_TRANSPORT_REGISTER(nrf_dfu_transport_t const usb_dfu_transport) =
{
    .init_func  = usb_dfu_transport_init,
    .close_func = usb_dfu_transport_close,
};


static void payload_free(void * p_buf)
{
    uint8_t * p_buf_root = ((uint8_t *)(p_buf)) - DATA_OFFSET; //pointer is shifted to point to data
    nrf_balloc_free(&m_payload_pool, p_buf_root);
}


static ret_code_t rsp_send(uint8_t const * p_data, uint32_t length)
{
    ASSERT(p_data);
    ASSERT(length != 0);

    uint32_t slip_len;

    // Cannot fail if inputs are non-NULL.
    (void) slip_encode(m_rsp_buf, (uint8_t *)(p_data), length, &slip_len);

    return app_usbd_cdc_acm_write(&m_app_cdc_acm, m_rsp_buf, slip_len);
}


static void on_rx_complete(nrf_dfu_serial_t * p_transport, uint8_t * p_data, uint8_t len)
{
    ret_code_t ret_code;

    for (uint32_t i = 0; i < len; i++)
    {
        ret_code = slip_decode_add_byte(&m_slip, p_data[i]);
        if (ret_code != NRF_SUCCESS)
        {
            continue;
        }

        nrf_dfu_serial_on_packet_received(p_transport,
                                          (uint8_t const *)(m_slip.p_buffer),
                                          m_slip.current_index);

        uint8_t * p_rx_buf = nrf_balloc_alloc(&m_payload_pool);
        if (p_rx_buf == NULL)
        {
            NRF_LOG_ERROR("Failed to allocate buffer!");
            return;
        }

        NRF_LOG_DEBUG("Allocated buffer %x", p_rx_buf);
        // reset the slip decoding
        m_slip.p_buffer      = &p_rx_buf[OPCODE_OFFSET];
        m_slip.current_index = 0;
        m_slip.state         = SLIP_STATE_DECODING;
    }
}

/**
 * @brief User event handler @ref app_usbd_cdc_acm_user_ev_handler_t (headphones)
 * */
static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event)
{
    ret_code_t ret_code;

    switch (event)
    {
        case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
        {
            ret_code = app_usbd_cdc_acm_read(&m_app_cdc_acm, m_rx_buf, 1);
            NRF_LOG_WARNING("Could not read from CDC. Error: 0x%x.", ret_code);
        } break;

        case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
        {
            do
            {
                on_rx_complete(&m_serial, m_rx_buf, 1);
                ret_code = app_usbd_cdc_acm_read(&m_app_cdc_acm, m_rx_buf, 1);
            } while (ret_code == NRF_SUCCESS);
        } break;

        default:
            break;
    }
}


static void usbd_dfu_transport_ev_handler(app_usbd_event_type_t event)
{
    switch (event)
    {
        case APP_USBD_EVT_STOPPED:
            app_usbd_disable();
            break;

        case APP_USBD_EVT_POWER_DETECTED:
            NRF_LOG_INFO("USB power detected");
            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }

            if (m_observer)
            {
                m_observer(NRF_DFU_EVT_TRANSPORT_ACTIVATED);
            }
            break;

        case APP_USBD_EVT_POWER_REMOVED:
            NRF_LOG_INFO("USB power removed");
            app_usbd_stop();
            if (m_observer)
            {
                m_observer(NRF_DFU_EVT_TRANSPORT_DEACTIVATED);
            }
            break;

        case APP_USBD_EVT_POWER_READY:
            NRF_LOG_INFO("USB ready");
            app_usbd_start();
            break;

        default:
            break;
    }
}


static void usbd_sched_event_handler(void * p_event_data, uint16_t event_size)
{
    app_usbd_event_execute(p_event_data);
}


static void usbd_event_handler(app_usbd_internal_evt_t const * const p_event)
{
    ret_code_t ret_code;
    if (p_event->type == APP_USBD_EVT_DRV_SOF)
    {
        app_usbd_event_execute(p_event);
    }
    else
    {
        ret_code = app_sched_event_put(p_event,
                                       sizeof(app_usbd_internal_evt_t),
                                       usbd_sched_event_handler);

        if (ret_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Could not schedule USB event!");
        }
    }
}


static uint32_t usb_dfu_transport_init(nrf_dfu_observer_t observer)
{
    uint32_t err_code;

    /* Execute event directly in interrupt handler */
    static const app_usbd_config_t usbd_config =
    {
        .ev_handler    = usbd_event_handler,
        .ev_state_proc = usbd_dfu_transport_ev_handler
    };

    (void) nrf_balloc_init(&m_payload_pool); //Result is checked by checking result of _alloc().

    m_observer = observer;

    uint8_t * p_rx_buf = nrf_balloc_alloc(&m_payload_pool);
    if (p_rx_buf == NULL)
    {
        NRF_LOG_ERROR("Could not allocate payload pool.");
        return NRF_ERROR_INTERNAL;
    }

    m_slip.p_buffer      = &p_rx_buf[OPCODE_OFFSET];
    m_slip.current_index = 0;
    m_slip.buffer_len    = SLIP_MTU;
    m_slip.state         = SLIP_STATE_DECODING;

    m_serial.rsp_func          = rsp_send;
    m_serial.payload_free_func = payload_free;
    m_serial.mtu               = SLIP_MTU;
    m_serial.p_rsp_buf         = &m_rsp_buf[NRF_USB_MAX_RESPONSE_SIZE_SLIP -
                                            NRF_SERIAL_MAX_RESPONSE_SIZE];
    m_serial.p_low_level_transport = &usb_dfu_transport;


    NRF_LOG_DEBUG("Initializing drivers.");

    err_code = nrf_drv_clock_init();
    if (err_code != NRF_ERROR_MODULE_ALREADY_INITIALIZED)
    {
        VERIFY_SUCCESS(err_code);
    }

    err_code = nrf_drv_power_init(NULL);
    VERIFY_SUCCESS(err_code);

    app_usbd_serial_num_generate();

    err_code = app_usbd_init(&usbd_config);
    VERIFY_SUCCESS(err_code);

    app_usbd_class_inst_t const * class_cdc_acm = app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm);
    err_code                                    = app_usbd_class_append(class_cdc_acm);
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("Starting USB");

    if (USBD_POWER_DETECTION)
    {
        err_code = app_usbd_power_events_enable();
        VERIFY_SUCCESS(err_code);
    }
    else
    {
        NRF_LOG_DEBUG("No USB power detection enabled, starting USB now");

        app_usbd_enable();
        app_usbd_start();
    }

    NRF_LOG_DEBUG("USB Transport initialized");

    return err_code;
}


static uint32_t usb_dfu_transport_close(nrf_dfu_transport_t const * p_exception)
{
    return NRF_SUCCESS;
}
