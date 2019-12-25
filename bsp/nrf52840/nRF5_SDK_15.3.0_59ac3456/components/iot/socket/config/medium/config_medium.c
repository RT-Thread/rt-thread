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
#include "sdk_config.h"
#include "socket_api.h"
#include "config_medium.h"
#include "ipv6_medium.h"
#include "iot_errors.h"
#include "app_error.h"
#include "socket_config.h"

static ipv6_medium_instance_t m_ipv6_medium;                                                        /**< IPv6 medium instance. */
eui64_t                       eui64_local_iid;                                                      /**< Local EUI64 value that is used as the IID for*/

eui64_t * config_medium_local_iid(void)
{
    return &eui64_local_iid;
}

void config_medium_start(void)
{
    uint32_t err_code = ipv6_medium_connectable_mode_enter(m_ipv6_medium.ipv6_medium_instance_id);
    APP_ERROR_CHECK(err_code);
}

static void on_ipv6_medium_evt(ipv6_medium_evt_t * p_ipv6_medium_evt)
{
    switch (p_ipv6_medium_evt->ipv6_medium_evt_id)
    {
        case IPV6_MEDIUM_EVT_CONN_UP:
        {
            // TODO: Signal
            break;
        }
        case IPV6_MEDIUM_EVT_CONN_DOWN:
        {
            config_medium_start();
            break;
        }
        default:
        {
            break;
        }
    }
}


static void on_ipv6_medium_error(ipv6_medium_error_t * p_ipv6_medium_error)
{
    // Do something.
}

static uint32_t config_medium_init(ipv6_medium_init_params_t * p_medium_params,
                                   ipv6_medium_type_t          medium_type)
{
    uint32_t err_code = ipv6_medium_init(p_medium_params, medium_type, &m_ipv6_medium);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    eui48_t ipv6_medium_eui48;
    err_code = ipv6_medium_eui48_get(m_ipv6_medium.ipv6_medium_instance_id, &ipv6_medium_eui48);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    ipv6_medium_eui48.identifier[EUI_48_SIZE - 1] = 0x00;

    err_code = ipv6_medium_eui48_set(m_ipv6_medium.ipv6_medium_instance_id, &ipv6_medium_eui48);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = ipv6_medium_eui64_get(m_ipv6_medium.ipv6_medium_instance_id, &eui64_local_iid);
    return err_code;
}

uint32_t config_medium_init_default(void)
{
    static ipv6_medium_init_params_t ipv6_medium_init_params;
    memset(&ipv6_medium_init_params, 0x00, sizeof(ipv6_medium_init_params));
    ipv6_medium_init_params.ipv6_medium_evt_handler    = on_ipv6_medium_evt;
    ipv6_medium_init_params.ipv6_medium_error_handler  = on_ipv6_medium_error;
    return config_medium_init(&ipv6_medium_init_params, IPV6_MEDIUM_ID_BLE);
}

uint32_t config_medium_setopt(int optname, const void * p_optarg, socklen_t optlen)
{
    uint32_t err_code = SOCKET_INVALID_PARAM;
    if (optname == MEDIUM_INIT_PARAMS)
    {
        if (optlen == sizeof(config_medium_params_t))
        {
            const config_medium_params_t * p_cfg = (const config_medium_params_t *)p_optarg;
            ipv6_medium_init_params_t ipv6_medium_init_params;
            memset(&ipv6_medium_init_params, 0x00, sizeof(ipv6_medium_init_params));
            ipv6_medium_init_params.ipv6_medium_evt_handler    = p_cfg->evt_handler;
            ipv6_medium_init_params.ipv6_medium_error_handler  = p_cfg->error_handler;
            err_code = config_medium_init(&ipv6_medium_init_params, p_cfg->medium_type);
        }
    }
    return err_code;
}

uint32_t config_medium_getopt(int optname, void * p_optarg, socklen_t * p_optlen)
{
    (void) optname;
    (void) p_optarg;
    (void) p_optlen;
    return SOCKET_INVALID_PARAM;
}

uint32_t config_socket_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
#if SOCKET_AUTOINIT_ENABLE == 1
    err_code = config_medium_init_default();
#endif
    return err_code;
}

void config_socket_start(void)
{
#if SOCKET_AUTOINIT_ENABLE == 1
    config_medium_start();
#endif
}

static uint32_t config_socket_open(socket_t * p_socket)
{
    (void) p_socket;
    return NRF_ERROR_NULL;
}

static uint32_t config_socket_close(socket_t * p_socket)
{
    (void) p_socket;
    return NRF_ERROR_NULL;
}

uint32_t config_socket_setopt(socket_t   * p_socket,
                              int          level,
                              int          optname,
                              const void * p_optarg,
                              socklen_t    optlen)
{
    uint32_t err_code = NRF_SUCCESS;
    switch (level)
    {
        case SOL_NRF_MEDIUM:
            err_code = config_medium_setopt(optname, p_optarg, optlen);
            break;
        default:
            err_code = SOCKET_INVALID_PARAM;
            break;
    }
    return err_code;
}

uint32_t config_socket_getopt(socket_t  * p_socket,
                              int         level,
                              int         optname,
                              void      * p_optarg,
                              socklen_t * p_optlen)
{
    uint32_t err_code = NRF_SUCCESS;
    switch (level)
    {
        case SOL_NRF_MEDIUM:
            err_code = config_medium_getopt(optname, p_optarg, p_optlen);
            break;
        default:
            err_code = SOCKET_INVALID_PARAM;
            break;
    }
    return err_code;
}

/**
 * @brief Transport for configuration socket.
 */
socket_transport_t config_socket_transport =
{
    .open       = config_socket_open,
    .setsockopt = config_socket_setopt,
    .getsockopt = config_socket_getopt,
    .close      = config_socket_close
};
