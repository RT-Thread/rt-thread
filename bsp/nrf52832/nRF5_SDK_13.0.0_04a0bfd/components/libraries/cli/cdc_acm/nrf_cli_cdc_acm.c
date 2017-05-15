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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CLI_CDC_ACM)
#include "nrf_cli_cdc_acm.h"
#include "nrf_queue.h"

static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event);


/**
 * @brief Interfaces list passed to @ref APP_USBD_CDC_ACM_GLOBAL_DEF
 * */
#define NRF_CLI_CDC_ACM_INTERFACES_CONFIG()                 \
    APP_USBD_CDC_ACM_CONFIG(NRF_CLI_CDC_ACM_COMM_INTERFACE, \
                            NRF_CLI_CDC_ACM_COMM_EPIN,      \
                            NRF_CLI_CDC_ACM_DATA_INTERFACE, \
                            NRF_CLI_CDC_ACM_DATA_EPIN,      \
                            NRF_CLI_CDC_ACM_DATA_EPOUT)

static const uint8_t m_cdc_acm_class_descriptors[] = {
        APP_USBD_CDC_ACM_DEFAULT_DESC(NRF_CLI_CDC_ACM_COMM_INTERFACE,
                                      NRF_CLI_CDC_ACM_COMM_EPIN,
                                      NRF_CLI_CDC_ACM_DATA_INTERFACE,
                                      NRF_CLI_CDC_ACM_DATA_EPIN,
                                      NRF_CLI_CDC_ACM_DATA_EPOUT)
};

/*lint -save -e26 -e40 -e64 -e123 -e505 -e651*/

/**
 * @brief CDC_ACM class instance.
 * */
APP_USBD_CDC_ACM_GLOBAL_DEF(nrf_cli_cdc_acm,
                            NRF_CLI_CDC_ACM_INTERFACES_CONFIG(),
                            cdc_acm_user_ev_handler,
                            m_cdc_acm_class_descriptors
);

/*lint -restore*/

NRF_QUEUE_DEF(uint8_t,
              m_rx_queue,
              NRF_DRV_USBD_EPSIZE,
              NRF_QUEUE_MODE_OVERFLOW);

static bool m_port_is_open;
static char m_rx_buffer[NRF_DRV_USBD_EPSIZE];

/**
 * @brief User event handler.
 * */
static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = app_usbd_cdc_acm_class_get(p_inst);



    switch (event)
    {
        case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
        {
            m_port_is_open = true;
            /*Setup first transfer*/
            ret_code_t ret = app_usbd_cdc_acm_read(&nrf_cli_cdc_acm,
                                                   m_rx_buffer,
                                                   sizeof(m_rx_buffer));
            APP_ERROR_CHECK(ret);
            break;
        }
        case APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE:
            m_port_is_open = false;
            break;
        case APP_USBD_CDC_ACM_USER_EVT_TX_DONE:
            break;
        case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
        {
            /*Get amount of data transfered*/
            size_t size = app_usbd_cdc_acm_rx_size(p_cdc_acm);
            size_t qsize = nrf_queue_in(&m_rx_queue, m_rx_buffer, size);
            ASSERT(size == qsize);

            /*Setup next transfer*/
            ret_code_t ret = app_usbd_cdc_acm_read(&nrf_cli_cdc_acm,
                                                   m_rx_buffer,
                                                   sizeof(m_rx_buffer));

            ASSERT(ret == NRF_SUCCESS); /*Should not happen*/
            break;
        }
        default:
            break;
    }
}

static ret_code_t cli_cdc_acm_init(void)
{
    return NRF_SUCCESS;
}

static ret_code_t cli_cdc_acm_uninit(void)
{
    return NRF_SUCCESS;
}

static ret_code_t cli_cdc_acm_read(void * p_data,
                                   size_t length,
                                   size_t * p_cnt)
{
    size_t size = nrf_queue_out(&m_rx_queue, p_data, length);
    if (p_cnt)
    {
        *p_cnt = size;
    }

    return NRF_SUCCESS;
}

static ret_code_t cli_cdc_acm_write(const void * p_data,
                                    size_t length,
                                    size_t * p_cnt)
{
    ret_code_t ret;
    do {

        ret = app_usbd_cdc_acm_write(&nrf_cli_cdc_acm, p_data, length);
        if (ret == NRF_SUCCESS && p_cnt)
        {
            *p_cnt = length;
        }

    } while(ret == NRF_ERROR_BUSY);

    return ret;
}

const nrf_cli_transport_t nrf_cli_cdc_acm_transport = {
        .init = cli_cdc_acm_init,
        .uninit = cli_cdc_acm_uninit,
        .read = cli_cdc_acm_read,
        .write = cli_cdc_acm_write,
};

bool nrf_cli_cdc_acm_port_is_open(void)
{
    return m_port_is_open;
}

#endif // NRF_MODULE_ENABLED(NRF_CLI_CDC_ACM)
