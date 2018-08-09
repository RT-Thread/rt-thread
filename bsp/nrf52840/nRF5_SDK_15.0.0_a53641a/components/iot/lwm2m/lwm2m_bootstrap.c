/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#include <stdio.h>
#include <stdint.h>
#include "lwm2m_api.h"
#include "lwm2m_bootstrap.h"
#include "lwm2m.h"
#include "coap_api.h"
#include "coap_message.h"
#include "coap_codes.h"
#include "sdk_config.h"
#include "app_util.h"

#if LWM2M_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME lwm2m

#define NRF_LOG_LEVEL       LWM2M_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  LWM2M_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR LWM2M_CONFIG_DEBUG_COLOR

#include "nrf_log.h"

#define LWM2M_TRC     NRF_LOG_DEBUG                                                                 /**< Used for getting trace of execution in the module. */
#define LWM2M_ERR     NRF_LOG_ERROR                                                                 /**< Used for logging errors in the module. */
#define LWM2M_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                         /**< Used for dumping octet information to get details of bond information etc. */

#define LWM2M_ENTRY() LWM2M_TRC(">> %s", __func__)
#define LWM2M_EXIT()  LWM2M_TRC("<< %s", __func__)

#else // LWM2M_CONFIG_LOG_ENABLED

#define LWM2M_TRC(...)                                                                              /**< Disables traces. */
#define LWM2M_DUMP(...)                                                                             /**< Disables dumping of octet streams. */
#define LWM2M_ERR(...)                                                                              /**< Disables error logs. */

#define LWM2M_ENTRY(...)
#define LWM2M_EXIT(...)

#endif // LWM2M_CONFIG_LOG_ENABLED

#define LWM2M_BOOTSTRAP_URI_PATH            "bs"

#define TOKEN_START                         0x012A

static uint16_t m_token = TOKEN_START;

static uint32_t internal_message_new(coap_message_t **        pp_msg,
                                     coap_msg_code_t          code,
                                     coap_response_callback_t callback,
                                     uint16_t                 local_port)
{
    uint32_t err_code;
    coap_message_conf_t conf;
    memset (&conf, 0, sizeof(coap_message_conf_t));

    conf.type              = COAP_TYPE_CON;
    conf.code              = code;
    conf.response_callback = callback;
    conf.port.port_number  = local_port;

    conf.token_len = uint16_encode(m_token, conf.token);

    m_token++;

    err_code = coap_message_new(pp_msg, &conf);

    return err_code;
}


/**@brief Function to be used as callback function upon a bootstrap request. */
static void lwm2m_bootstrap_cb(uint32_t status, void * p_arg, coap_message_t * p_message)
{
    LWM2M_TRC("[Bootstrap]: lwm2m_bootstrap_cb, status: %ul, coap code: %u",
              status,
              p_message->header.code);

    (void)lwm2m_notification(LWM2M_NOTIFCATION_TYPE_BOOTSTRAP,
                             &p_message->remote,
                             p_message->header.code);
}


uint32_t internal_lwm2m_bootstrap_init(void)
{
    m_token = TOKEN_START;
    return NRF_SUCCESS;
}


uint32_t lwm2m_bootstrap(lwm2m_remote_t * p_remote, lwm2m_client_identity_t * p_id, uint16_t local_port)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_remote);
    NULL_PARAM_CHECK(p_id);

    LWM2M_MUTEX_LOCK();

    uint32_t         err_code;
    coap_message_t * p_msg;

    lwm2m_string_t endpoint;

    endpoint.p_val = LWM2M_BOOTSTRAP_URI_PATH;
    endpoint.len   = 2;

    err_code = internal_message_new(&p_msg, COAP_CODE_POST, lwm2m_bootstrap_cb, local_port);
    if (err_code != NRF_SUCCESS)
    {
        LWM2M_MUTEX_UNLOCK();
        return err_code;
    }

    if (err_code == NRF_SUCCESS)
    {
        err_code = coap_message_remote_addr_set(p_msg, p_remote);
    }

    if (err_code == NRF_SUCCESS)
    {
        err_code = coap_message_opt_str_add(p_msg,
                                            COAP_OPT_URI_PATH,
                                            (uint8_t *)endpoint.p_val,
                                            endpoint.len); // end_point length is always 2
    }

    if (err_code == NRF_SUCCESS)
    {
        char buffer[40];
        buffer[0] = 'e';
        buffer[1] = 'p';
        buffer[2] = '=';
        memcpy(buffer + 3, &p_id->value, p_id->type);

        err_code = coap_message_opt_str_add(p_msg,
                                            COAP_OPT_URI_QUERY,
                                            (uint8_t *)buffer,
                                            p_id->type + 3);
    }

    if (err_code == NRF_SUCCESS)
    {
        uint32_t msg_handle;
        err_code = coap_message_send(&msg_handle, p_msg);
    }

    if (err_code == NRF_SUCCESS)
    {
        err_code = coap_message_delete(p_msg);
    }
    else
    {
        // If we have hit an error try to clean up.
        // Return the original error code.
        (void)coap_message_delete(p_msg);
    }

    LWM2M_EXIT();

    LWM2M_MUTEX_UNLOCK();

    return err_code;
}
