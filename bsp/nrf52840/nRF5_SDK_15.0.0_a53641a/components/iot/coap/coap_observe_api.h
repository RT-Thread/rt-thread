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
/** @file coap_observe_api.h
 *
 * @defgroup iot_sdk_coap_observe CoAP Observe
 * @ingroup iot_sdk_coap
 * @{
 * @brief Public API of Nordic's CoAP Observe implementation.
 */
#ifndef COAP_OBSERVE_API_H__
#define COAP_OBSERVE_API_H__

#include <stdint.h>
#include "coap_api.h"
#include "coap_transport.h"
#include "coap_queue.h"
#include "compiler_abstraction.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COAP_OPT_OBSERVE     6                       /**< Observe option number. */

/**@brief Struct for CoAP Server for holding an instance of a remote observer. */
typedef struct
{
    coap_remote_t            remote;                 /**< Remote address and port number. */
    uint8_t                  token[8];               /**< Message Token ID. */
    uint8_t                  token_len;              /**< Length of the token. */
    coap_content_type_t      ct;                     /**< Content type to use when sending notifications. */
    coap_resource_t *        p_resource_of_interest; /**< Pointer to the resource of interest. */
} coap_observer_t;

/**@brief Struct for CoAP Client for holding an instance of a remote observable resource. */
typedef struct
{
    coap_remote_t            remote;                 /**< Remote address and port number. */
    uint8_t                  token[8];               /**< Message Token ID. */
    uint8_t                  token_len;              /**< Length of the token. */
    coap_response_callback_t response_callback;      /**< Function callback set by the application to be called when a notifications has been received. Should be set by the application. */
    uint32_t                 max_age;                /**< Max-Age of the observable resources value. If timed out, the value is no longer valid as a representation of the observable resource. */
} coap_observable_t;


/**@brief Register a new observer.
 *
 * @param[out]   p_handle    Handle to the observer instance registered. Returned by reference.
 *                           Should not be NULL.
 * @param[in]    p_observer  Pointer to the observer structure to register. The data will be
 *                           copied. Should not be NULL.
 *
 * @retval NRF_SUCCESS                   If the observer was registered successfully.
 * @retval NRF_ERROR_NO_MEM              If the observer could not be added to the list.
 * @retval NRF_ERROR_NULL                If one of the parameters is a NULL pointer.
 */
uint32_t coap_observe_server_register(uint32_t * p_handle, coap_observer_t * p_observer);

/**@brief Unregister an observer.
 *
 * @details Unregister the observer and clear the memory used by this instance.
 *
 * @param[in] handle Handle to the observer instance registered.
 *
 * @retval NRF_SUCCESS                   If the observer was successfully unregistered.
 * @retval NRF_ERROR_NOT_FOUND           If the given handle was not found in the observer list.
 */
uint32_t coap_observe_server_unregister(uint32_t handle);

/**@brief Search the observer list for an observer matching remote address and subject given.
 *
 * @param[out]   p_handle        Handle to the observer instance registered. Returned by reference.
 *                               Should not be NULL.
 * @param[in]    p_observer_addr Pointer to an address structure giving remote address of the observer and port number.
 *                               Should not be NULL.
 * @param[in]    p_resource      Pointer to the resource the observer is registered to. Should not be NULL.
 *
 * @retval NRF_SUCCESS                   If observer was found in the observer list.
 * @retval NRF_ERROR_NULL                If one of the pointers are NULL.
 * @retval NRF_ERROR_NOT_FOUND           If observer was not found.
 */
uint32_t coap_observe_server_search(uint32_t * p_handle, coap_remote_t * p_observer_addr, coap_resource_t * p_resource);

/**@brief Iterate through observers subscribing to a specific resource.
 *
 * @param[out] pp_observer Pointer to be filled by the search function upon finding the next observer starting from
 *                         from the p_observer pointer provided. Should not be NULL.
 * @param[in]  p_observer  Pointer to the observer where to start the search.
 * @param[in]  p_resource  Pointer to the resource of interest. Should not be NULL.
 *
 * @retval NRF_SUCCESS                   If observer was found.
 * @retval NRF_ERROR_NULL                If pp_observer or p_resource pointer is NULL.
 * @retval NRF_ERROR_NOT_FOUND           If next observer was not found.
 */
uint32_t coap_observe_server_next_get(coap_observer_t ** pp_observer, coap_observer_t * p_observer, coap_resource_t * p_resource);

/**@brief Retrieve the observer based on handle.
 *
 * @param[in]  handle          Handle to the coap_observer_t instance.
 * @param[out] pp_observer     Pointer to an observer return by reference.
 *                             Should not be NULL.
 *
 * @retval NRF_SUCCESS                   If observer was found in the observer list.
 * @retval NRF_ERROR_NULL                If pp_observer pointer is NULL.
 * @retval NRF_ERROR_NOT_FOUND           If observer associated with the handle was not found.
 */
uint32_t coap_observe_server_get(uint32_t handle, coap_observer_t ** pp_observer);

/**@brief Register a new observable resource.
 *
 * @param[out]   p_handle     Handle to the observable resource instance registered. Returned by
 *                            reference. Should not be NULL.
 * @param[in]    p_observable Pointer to a observable resource structure to register. The structure
 *                            will be copied. Should not be NULL.
 *
 * @retval NRF_SUCCESS                   If the observable resource was registered successfully.
 * @retval NRF_ERROR_NO_MEM              If the observable resource could not be added to the list.
 * @retval NRF_ERROR_NULL                If one of the parameters is a NULL pointer.
 */
uint32_t coap_observe_client_register(uint32_t * p_handle, coap_observable_t * p_observable);

/**@brief Unregister an observable resource.
 *
 * @details Unregister the observable resource and clear the memory used by this instance.
 *
 * @param[in] handle Handle to the observable resource instance registered.
 *
 * @retval NRF_SUCCESS                   If the observable resource was successfully unregistered.
 * @retval NRF_ERROR_NOT_FOUND           If the given handle was not found in the observable
 *                                       resource list.
 */
uint32_t coap_observe_client_unregister(uint32_t handle);

/**@brief Search for a observable resource instance by token.
 *
 * @param[out] p_handle  Handle to the observable resource instance registered. Returned by
 *                       reference. Should not be NULL.
 * @param[in]  p_token   Pointer to the byte array holding the token id. Should not be NULL.
 * @param[in]  token_len Length of the token.
 *
 * @retval NRF_SUCCESS                   If observable resource was found in the observable
 *                                       resource list.
 * @retval NRF_ERROR_NULL                If one of the pointers are NULL.
 * @retval NRF_ERROR_NOT_FOUND           If observable resource was not found in the observable
 *                                       resource list.
 */
uint32_t coap_observe_client_search(uint32_t * p_handle, uint8_t * p_token, uint16_t token_len);

/**@brief Retrieve the observable resource based on handle.
 *
 * @param[in]  handle          Handle to the coap_observable_t instance.
 * @param[out] pp_observable   Pointer to an observable resource return by reference.
 *                             Should not be NULL.
 *
 * @retval NRF_SUCCESS                   If observable resource was found in the observable
 *                                       resource list.
 * @retval NRF_ERROR_NULL                If pp_observable pointer is NULL.
 * @retval NRF_ERROR_NOT_FOUND           If observable resource associated with the handle
 *                                       was not found.
 */
uint32_t coap_observe_client_get(uint32_t handle, coap_observable_t ** pp_observable);

/**@brief Iterate through observable resources.
 *
 * @param[out] pp_observable Pointer to be filled by the search function upon finding the next
 *                           observable resource starting from from the pointer provided.
 *                           Should not be NULL.
 * @param[out] p_handle      Handler to the observable resource found returned by reference. Should
 *                           not be NULL.
 * @param[in]  p_observable  Pointer to the observable resource where to start the search.
 *
 * @retval NRF_SUCCESS                   If observer was found.
 * @retval NRF_ERROR_NULL                If pp_observer or p_observer pointer is NULL.
 * @retval NRF_ERROR_NOT_FOUND           If next observer was not found.
 */
uint32_t coap_observe_client_next_get(coap_observable_t ** pp_observable, uint32_t * p_handle, coap_observable_t * p_observable);

#ifdef __cplusplus
}
#endif

#endif // COAP_OBSERVE_API_H__

/** @} */
