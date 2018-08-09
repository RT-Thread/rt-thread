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
/**@file config_medium.h
 *
 * @defgroup iot_socket_config_medium Configuration socket based on ipv6_medium
 * @ingroup iot_sdk_socket
 * @{
 * @brief Configuration socket based on the ipv6_medium module.
 *
 * This module wraps the medium module in a configuration socket API.
 */
#ifndef CONFIG_MEDIUM_H__
#define CONFIG_MEDIUM_H__

#include <stdint.h>
#include "iot_defines.h"
#include "ipv6_medium.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function for initializing a configuration socket with default settings.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t config_medium_init_default(void);

/**
 * @brief Function for starting the medium layer.
 *
 * For BLE, this means to start advertising.
 */
void config_medium_start(void);

/**
 * @brief Function for retrieving local interface ID assigned.
 *
 * @return Pointer to location of interface ID.
 */
eui64_t * config_medium_local_iid(void);

/**
 * @brief Function for setting configuration parameters for the medium layers using the socket option.
 *
 * @param optname   Option name/type.
 * @param p_optarg  Pointer to option value.
 * @param optlen  Length of option value.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t config_medium_setopt(int optname, const void * p_optarg, socklen_t optlen);

/**
 * @brief Function for getting configuration parameters for the medium layers using the socket option.
 *
 * @param optname   Option name/type.
 * @param p_optarg  Pointer to the option value structure where the value should be stored.
 * @param p_optlen  Length of option value.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t config_medium_getopt(int optname, void * p_optarg, socklen_t * p_optlen);

/**
 * @brief Parameters passed for the MEDIUM_INIT_PARAMS option.
 *
 * These are currently the same as for ipv6_medium initialization.
 */
typedef struct {
    ipv6_medium_evt_handler_t       evt_handler;    /**< The medium event handler callback.    */
    ipv6_medium_error_handler_t     error_handler;  /**< The medium error handler callback.    */
    ipv6_medium_type_t              medium_type;    /**< The medium type.                      */
} config_medium_params_t;

#ifdef __cplusplus
}
#endif

#endif // CONFIG_MEDIUM_H__

/**@} */
