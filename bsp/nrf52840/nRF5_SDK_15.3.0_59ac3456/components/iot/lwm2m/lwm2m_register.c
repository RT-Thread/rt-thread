/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#include "lwm2m_register.h"
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

#define LWM2M_REGISTER_URI_PATH             "rd"

#define TOKEN_START                         0xAE1C

typedef struct
{
    lwm2m_remote_t      remote;
    char                location[LWM2M_REGISTER_MAX_LOCATION_LEN];
    uint16_t            location_len;
} internal_lwm2m_remote_location_t;


static internal_lwm2m_remote_location_t m_remote_to_location[LWM2M_MAX_SERVERS];

static uint16_t num_servers = 0;
static uint16_t m_token     = TOKEN_START;

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


static uint32_t internal_location_find(lwm2m_string_t * p_location, lwm2m_remote_t * p_remote)
{
    for (uint16_t i = 0; i < num_servers; ++i)
    {
        if (memcmp(&m_remote_to_location[i].remote, p_remote, sizeof(lwm2m_remote_t)) == 0)
        {
            p_location->p_val = m_remote_to_location[i].location;
            p_location->len   = m_remote_to_location[i].location_len;
            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NOT_FOUND;
}


static uint32_t internal_remote_location_save(lwm2m_string_t * location, lwm2m_remote_t * remote)
{
    for (uint16_t i = 0; i < num_servers; ++i)
    {
        if (memcmp(&m_remote_to_location[i].remote, remote, sizeof(lwm2m_remote_t)) == 0)
        {
            memcpy(m_remote_to_location[i].location, location->p_val, location->len);
            m_remote_to_location[i].location_len = location->len;
            return NRF_SUCCESS;
        }
    }

    if (num_servers == LWM2M_MAX_SERVERS)
        return NRF_ERROR_NO_MEM;

    memcpy(&m_remote_to_location[num_servers].remote, remote, sizeof(lwm2m_remote_t));

    memcpy(m_remote_to_location[num_servers].location, location->p_val, location->len);

    m_remote_to_location[num_servers].location_len = location->len;

    ++num_servers;

    return NRF_SUCCESS;
}


static uint32_t internal_server_config_set(coap_message_t * msg, lwm2m_server_config_t * p_config)
{
    char buffer[32];
    uint32_t err_code = NRF_SUCCESS;

    if (p_config->lifetime > 0)
    {
        int retval = snprintf(buffer, sizeof(buffer), "lt=%lu", p_config->lifetime);
        if (retval < 0)
        {
            err_code = NRF_ERROR_INVALID_PARAM;
        }
        else
        {
            err_code = coap_message_opt_str_add(msg,
                                                COAP_OPT_URI_QUERY,
                                                (uint8_t *)buffer,
                                                strlen(buffer));
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        if ((p_config->lwm2m_version_major > 0) || (p_config->lwm2m_version_minor > 0))
        {
            int retval = snprintf(buffer,
                                  sizeof(buffer),
                                  "lwm2m=%d.%d",
                                  p_config->lwm2m_version_major,
                                  p_config->lwm2m_version_minor);
            if (retval < 0)
            {
                err_code = NRF_ERROR_INVALID_PARAM;
            }
            else
            {
                err_code = coap_message_opt_str_add(msg,
                                                    COAP_OPT_URI_QUERY,
                                                    (uint8_t *)buffer,
                                                    strlen(buffer));
            }
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        if (p_config->msisdn > 0)
        {
            int retval = snprintf(buffer, sizeof(buffer), "sms=%llu" , p_config->msisdn);
            if (retval < 0)
            {
                err_code = NRF_ERROR_INVALID_PARAM;
            }
            else
            {
                err_code = coap_message_opt_str_add(msg,
                                                    COAP_OPT_URI_QUERY,
                                                    (uint8_t *)buffer,
                                                    strlen(buffer));
            }
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        if (p_config->binding.len > 0)
        {
            if (p_config->binding.len < sizeof(buffer) - 2)
            {
                buffer[0] = 'b';
                buffer[1] = '=';
                memcpy(buffer + 2, p_config->binding.p_val, p_config->binding.len);

                err_code = coap_message_opt_str_add(msg,
                                                    COAP_OPT_URI_QUERY,
                                                    (uint8_t *)buffer,
                                                    p_config->binding.len + 2);
            }
            else
            {
                err_code = NRF_ERROR_NO_MEM;
            }
        }
    }

    return err_code;
}


uint32_t internal_lwm2m_register_init(void)
{
    m_token     = TOKEN_START;
    num_servers = 0;
    return NRF_SUCCESS;
}


static void lwm2m_register_cb(uint32_t status, void * p_arg, coap_message_t * p_message)
{
    LWM2M_TRC("[Register]: lwm2m_register_cb, status: %ul, coap code: %u",
              status,
              p_message->header.code);

    LWM2M_MUTEX_LOCK();

    for (uint16_t i = 0; i < p_message->options_count; ++i)
    {
        coap_option_t option = p_message->options[i];

        if (option.number == COAP_OPT_LOCATION_PATH)
        {
            lwm2m_string_t location;
            location.p_val = (char *) option.p_data;
            location.len   = option.length;
            (void)internal_remote_location_save(&location, &p_message->remote);
        }
    }

    LWM2M_MUTEX_UNLOCK();

    (void)lwm2m_notification(LWM2M_NOTIFCATION_TYPE_REGISTER,
                             &p_message->remote,
                             p_message->header.code);
}


uint32_t lwm2m_register(lwm2m_remote_t *          p_remote,
                        lwm2m_client_identity_t * p_id,
                        lwm2m_server_config_t *   p_config,
                        uint16_t                  local_port,
                        uint8_t *                 p_link_format_string,
                        uint16_t                  link_format_len)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_remote);
    NULL_PARAM_CHECK(p_id);
    NULL_PARAM_CHECK(p_config);
    NULL_PARAM_CHECK(p_link_format_string);

    LWM2M_MUTEX_LOCK();

    uint32_t  err_code;
    char      buffer[40];

    lwm2m_string_t endpoint;

    endpoint.p_val = LWM2M_REGISTER_URI_PATH;
    endpoint.len   = 2;

    coap_message_t * p_msg;

    err_code = internal_message_new(&p_msg, COAP_CODE_POST, lwm2m_register_cb, local_port);
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
        // Set uri-path option
        err_code = coap_message_opt_str_add(p_msg,
                                            COAP_OPT_URI_PATH,
                                            (uint8_t *)endpoint.p_val,
                                            endpoint.len); // end_point length is always 2
    }

    if (err_code == NRF_SUCCESS)
    {
        // Set content format.
        err_code = coap_message_opt_uint_add(p_msg, COAP_OPT_CONTENT_FORMAT, COAP_CT_APP_LINK_FORMAT);
    }

    if (err_code == NRF_SUCCESS)
    {
        // Set queries.
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
        err_code = internal_server_config_set(p_msg, p_config);
    }

    if (err_code == NRF_SUCCESS)
    {
        err_code = coap_message_payload_set(p_msg, p_link_format_string, link_format_len);
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

    LWM2M_MUTEX_UNLOCK();

    LWM2M_EXIT();

    return err_code;
}

void lwm2m_update_cb(uint32_t status, void * p_arg, coap_message_t * p_message)
{
    LWM2M_TRC("[Update]: lwm2m_update_cb, status: %ul, coap code: %u",
              status,
              p_message->header.code);

    (void)lwm2m_notification(LWM2M_NOTIFCATION_TYPE_UPDATE,
                             &p_message->remote,
                             p_message->header.code);
}


uint32_t lwm2m_update(lwm2m_remote_t * p_remote, lwm2m_server_config_t * p_config, uint16_t local_port)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_remote);
    NULL_PARAM_CHECK(p_config);

    LWM2M_MUTEX_LOCK();

    uint32_t         err_code;
    coap_message_t * p_msg;

    err_code = internal_message_new(&p_msg, COAP_CODE_POST, lwm2m_update_cb, local_port);
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
        lwm2m_string_t location;
        err_code = internal_location_find(&location, p_remote);

        if (err_code == NRF_SUCCESS)
        {
            // Sets URI PATH
            err_code = coap_message_opt_str_add(p_msg,
                                                COAP_OPT_URI_PATH,
                                                (uint8_t *)location.p_val,
                                                location.len);
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        // Sets CoAP queries
        err_code = internal_server_config_set(p_msg, p_config);
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

void lwm2m_deregister_cb(uint32_t status, void * p_arg, coap_message_t * p_message)
{
    LWM2M_TRC("[DeRegister]: lwm2m_deregister_cb, status: %ul, coap code: %u",
              status,
              p_message->header.code);

    (void)lwm2m_notification(LWM2M_NOTIFCATION_TYPE_DEREGISTER,
                             &p_message->remote,
                             p_message->header.code);
}

uint32_t lwm2m_deregister(lwm2m_remote_t * p_remote, uint16_t local_port)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_remote);

    LWM2M_MUTEX_LOCK();

    uint32_t         err_code;
    coap_message_t * p_msg;

    err_code = internal_message_new(&p_msg, COAP_CODE_DELETE, lwm2m_deregister_cb, local_port);
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
        lwm2m_string_t location;
        err_code = internal_location_find(&location, p_remote);

        if (err_code == NRF_SUCCESS)
        {
            err_code = coap_message_opt_str_add(p_msg,
                                                COAP_OPT_URI_PATH,
                                                (uint8_t *)location.p_val,
                                                location.len);
        }
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
