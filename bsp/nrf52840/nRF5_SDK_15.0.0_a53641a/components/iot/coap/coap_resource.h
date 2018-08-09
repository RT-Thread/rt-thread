/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
/** @file coap_resource.h
 *
 * @defgroup iot_sdk_coap_resource CoAP Resource
 * @ingroup iot_sdk_coap
 * @{
 * @brief Private API of Nordic's CoAP Resource implementation.
 */

#ifndef COAP_RESOURCE_H__
#define COAP_RESOURCE_H__

#include <stdint.h>
#include "coap_api.h"
#include "sdk_config.h"
#include "coap_message.h"
#include "nrf_error.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Initialize the CoAP resource module.
 *
 * @details This function will initialize the root element pointer to NULL.
 *          This way, a new root can be assigned registered. The first
 *          resource added will be set as the new root.
 *
 * @retval NRF_SUCCESS         This function will always return success.
 */
uint32_t coap_resource_init(void);

/**@brief Find a resource by traversing the resource names.
 *
 * @param[out] p_resource      Located resource.
 * @param[in]  pp_uri_pointers Array of strings which forms the hierarchical path to the resource.
 * @param[in]  num_of_uris     Number of URIs supplied through the path pointer list.
 *
 * @retval NRF_SUCCESS             The resource was instance located.
 * @retval NRF_ERROR_NOT_FOUND     The resource was not located.
 * @retval NRF_ERROR_INVALID_STATE If no resource has been registered.
 */
uint32_t coap_resource_get(coap_resource_t ** p_resource,
                           uint8_t **         pp_uri_pointers,
                           uint8_t            num_of_uris);


/**@brief Process the request related to the resource.
 *
 * @details When a request is received and the resource has successfully been located it
 *          will pass on to this function. The method in the request will be matched against
 *          what the service provides of method handling callbacks. If the request expects a
 *          response this will be provided as output from this function. The memory provided
 *          for the response must be provided from outside.
 *
 * @param[in]    p_resource Resource that will handle the request.
 * @param[in]    p_request  The request to be handled.
 * @param[inout] p_response Response message which can be used by the resource populate
 *                          the response message.
 */
uint32_t coap_resource_process_request(coap_resource_t * p_resource,
                                       coap_message_t *  p_request,
                                       coap_message_t *  p_response);

#ifdef __cplusplus
}
#endif

#endif // COAP_MESSAGE_H__

/** @} */
