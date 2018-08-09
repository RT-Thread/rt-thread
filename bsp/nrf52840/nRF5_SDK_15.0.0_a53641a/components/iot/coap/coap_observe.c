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
#include <string.h>

#include "coap_observe_api.h"
#include "coap_observe.h"
#include "nrf_error.h"
#include "iot_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "coap.h"

#if IOT_COAP_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME coapobs

#define NRF_LOG_LEVEL       IOT_COAP_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_COAP_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_COAP_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define COAP_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define COAP_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define COAP_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define COAP_ENTRY() COAP_TRC(">> %s", __func__)
#define COAP_EXIT()  COAP_TRC("<< %s", __func__)

#else // IOT_COAP_CONFIG_LOG_ENABLED

#define COAP_TRC(...)                                                                           /**< Disables traces. */
#define COAP_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define COAP_ERR(...)                                                                           /**< Disables error logs. */

#define COAP_ENTRY(...)
#define COAP_EXIT(...)

#endif // IOT_COAP_CONFIG_LOG_ENABLED

#if (COAP_ENABLE_OBSERVE_SERVER == 1)
static coap_observer_t   m_observers[COAP_OBSERVE_MAX_NUM_OBSERVERS];

static void observe_server_init(void)
{
    COAP_ENTRY();

    // Loop through the observer array and clear the memory.
    for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVERS; i++)
    {
        memset(&m_observers[i], 0, sizeof(coap_observer_t));
    }

    COAP_EXIT();
}

uint32_t internal_coap_observe_server_register(uint32_t * p_handle, coap_observer_t * p_observer)
{
    COAP_ENTRY();

    NULL_PARAM_CHECK(p_handle);
    NULL_PARAM_CHECK(p_observer);

    NULL_PARAM_MEMBER_CHECK(p_observer->p_resource_of_interest);

    // Check if there is already a registered observer in the list to be reused.
    uint32_t handle;
    uint32_t err_code = coap_observe_server_search(&handle,
                                                   &p_observer->remote,
                                                   p_observer->p_resource_of_interest);
    if (err_code == NRF_SUCCESS)
    {
        memcpy(&m_observers[handle], p_observer, sizeof(coap_observer_t));
        *p_handle = handle;
        return NRF_SUCCESS;
    }

    // Check if there is an available spot in the observer list.
    for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVERS; i++)
    {
        if (m_observers[i].p_resource_of_interest == NULL)
        {
            memcpy(&m_observers[i], p_observer, sizeof(coap_observer_t));

            *p_handle = i;
            return NRF_SUCCESS;
        }
    }


    COAP_EXIT();

    return (NRF_ERROR_NO_MEM | IOT_COAP_ERR_BASE);
}


uint32_t internal_coap_observe_server_unregister(uint32_t handle)
{
    COAP_ENTRY();

    if (handle >= COAP_OBSERVE_MAX_NUM_OBSERVERS)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    if (m_observers[handle].p_resource_of_interest == NULL)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    m_observers[handle].p_resource_of_interest = NULL;

    COAP_EXIT();

    return NRF_SUCCESS;
}


uint32_t internal_coap_observe_server_search(uint32_t *        p_handle,
                                             coap_remote_t *   p_observer_addr,
                                             coap_resource_t * p_resource)
{
    NULL_PARAM_CHECK(p_handle);
    NULL_PARAM_CHECK(p_observer_addr);
    NULL_PARAM_CHECK(p_resource);

    for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVERS; i++)
    {
        if (m_observers[i].p_resource_of_interest == p_resource)
        {
            if (m_observers[i].remote.port_number == p_observer_addr->port_number)
            {
                if (memcmp(p_observer_addr->addr, m_observers[i].remote.addr, sizeof(p_observer_addr->addr)) == 0)
                {
                    *p_handle = i;
                    return NRF_SUCCESS;
                }
            }
        }
    }

    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}


uint32_t internal_coap_observe_server_next_get(coap_observer_t ** pp_observer,
                                               coap_observer_t *  p_observer,
                                               coap_resource_t *  p_resource)
{
    NULL_PARAM_CHECK(p_resource);
    NULL_PARAM_CHECK(pp_observer);

    if (p_observer == NULL)
    {
        for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVERS; i++)
        {
            if (m_observers[i].p_resource_of_interest == p_resource)
            {
                (*pp_observer) = &m_observers[i];
                return NRF_SUCCESS;
            }
        }
    }
    else
    {
        uint32_t index_to_previous = (uint8_t)(((uint32_t)p_observer - (uint32_t)m_observers) / (uint32_t)sizeof(coap_observer_t));

        for (uint32_t i = index_to_previous + 1; i < COAP_OBSERVE_MAX_NUM_OBSERVERS; i++)
        {
            if (m_observers[i].p_resource_of_interest == p_resource)
            {
                (*pp_observer) = &m_observers[i];
                return NRF_SUCCESS;
            }
        }
    }
    (*pp_observer) = NULL;

    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}

uint32_t internal_coap_observe_server_get(uint32_t handle, coap_observer_t ** pp_observer)
{
    NULL_PARAM_CHECK(pp_observer);

    if (handle >= COAP_OBSERVE_MAX_NUM_OBSERVERS)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    if (m_observers[handle].p_resource_of_interest == NULL)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    *pp_observer = &m_observers[handle];
    return NRF_SUCCESS;
}
#else
#define observe_server_init(...)
#endif

#if (COAP_ENABLE_OBSERVE_CLIENT == 1)
static coap_observable_t m_observables[COAP_OBSERVE_MAX_NUM_OBSERVABLES];

static void observe_client_init(void)
{
    // Loop through the observable array and clear the memory.
    for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVABLES; i++)
    {
        memset(&m_observables[i], 0, sizeof(coap_observable_t));
    }
}


uint32_t internal_coap_observe_client_register(uint32_t *          p_handle,
                                               coap_observable_t * p_observable)
{
    COAP_ENTRY();

    NULL_PARAM_CHECK(p_handle);
    NULL_PARAM_CHECK(p_observable);

    NULL_PARAM_MEMBER_CHECK(p_observable->response_callback);

    // Check if there is an available spot in the observer list.
    for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVABLES; i++)
    {
        if (m_observables[i].response_callback == NULL)
        {
            memcpy(&m_observables[i], p_observable, sizeof(coap_observable_t));
            *p_handle = i;
            return NRF_SUCCESS;
        }
    }

    COAP_EXIT();

    return (NRF_ERROR_NO_MEM | IOT_COAP_ERR_BASE);
}


uint32_t internal_coap_observe_client_unregister(uint32_t handle)
{
    COAP_ENTRY();

    if (handle >= COAP_OBSERVE_MAX_NUM_OBSERVABLES)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    if (m_observables[handle].response_callback == NULL)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    m_observables[handle].response_callback = NULL;

    COAP_EXIT();

    return NRF_SUCCESS;
}


uint32_t internal_coap_observe_client_search(uint32_t * p_handle, uint8_t * p_token, uint16_t token_len)
{
    NULL_PARAM_CHECK(p_handle);
    NULL_PARAM_CHECK(p_token);

    for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVABLES; i++)
    {
        if ((m_observables[i].response_callback != NULL)                           &&
            (0 != m_observables[i].token_len)                                           &&
            (memcmp(m_observables[i].token, p_token, m_observables[i].token_len) == 0))
        {
            *p_handle = i;
            return NRF_SUCCESS;
        }
    }

    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}


uint32_t internal_coap_observe_client_get(uint32_t handle, coap_observable_t ** pp_observable)
{
    NULL_PARAM_CHECK(pp_observable);

    if (handle >= COAP_OBSERVE_MAX_NUM_OBSERVABLES)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    if (m_observables[handle].response_callback == NULL)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    *pp_observable = &m_observables[handle];

    return NRF_SUCCESS;
}

uint32_t internal_coap_observe_client_next_get(coap_observable_t ** pp_observable,
                                               uint32_t *           p_handle,
                                               coap_observable_t *  p_observable)
{
    NULL_PARAM_CHECK(pp_observable);

    if (p_observable == NULL)
    {
        for (uint32_t i = 0; i < COAP_OBSERVE_MAX_NUM_OBSERVABLES; i++)
        {
            if (m_observables[i].response_callback != NULL)
            {
                (*pp_observable) = &m_observables[i];
                (*p_handle)      = i;
                return NRF_SUCCESS;
            }
        }
    }
    else
    {
        uint32_t index_to_previous = (uint8_t)(((uint32_t)p_observable - (uint32_t)m_observables) / (uint32_t)sizeof(coap_observable_t));

        for (uint32_t i = index_to_previous + 1; i < COAP_OBSERVE_MAX_NUM_OBSERVABLES; i++)
        {
            if (m_observables[i].response_callback != NULL)
            {
                (*pp_observable) = &m_observables[i];
                (*p_handle)      = i;
                return NRF_SUCCESS;
            }
        }
    }
    (*pp_observable) = NULL;

    COAP_MUTEX_UNLOCK();

    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}

static uint32_t observe_opt_present(coap_message_t * p_message)
{
    uint8_t index;
    for (index = 0; index < p_message->options_count; index++)
    {
        if (p_message->options[index].number == COAP_OPT_OBSERVE)
        {
            return NRF_SUCCESS;
        }
    }
    return NRF_ERROR_NOT_FOUND;
}

static void set_max_age(coap_observable_t * observable, coap_message_t * p_response)
{
    uint8_t index;
    for (index = 0; index < p_response->options_count; index++)
    {
        if (p_response->options[index].number == COAP_OPT_MAX_AGE)
        {
            uint32_t max_age;
            observable->max_age = coap_opt_uint_decode(&max_age,
                                                       p_response->options[index].length,
                                                       p_response->options[index].p_data);
            observable->max_age = max_age;
            return;
        }
    }

    // Max-Age option is not present, set default value to 60.
    observable->max_age = 60;
}

void coap_observe_client_send_handle(coap_message_t * p_request)
{
    COAP_ENTRY();

    if (p_request->header.code == COAP_CODE_GET)
    {
        uint32_t observe_option = 0;
        if (observe_opt_present(p_request) == NRF_SUCCESS)
        {
            // Locate option and check value.
            uint8_t index;
            for (index = 0; index < p_request->options_count; index++)
            {
                if (p_request->options[index].number == COAP_OPT_OBSERVE)
                {
                    uint32_t err_code = coap_opt_uint_decode(&observe_option,
                                                             p_request->options[index].length,
                                                             p_request->options[index].p_data);
                    if (err_code != NRF_SUCCESS)
                    {
                       return;
                    }
                    break;
                }
            }
        }

        if (observe_option == 1)
        {
            // Un-register observable instance.
            uint32_t handle;
            uint32_t err_code = internal_coap_observe_client_search(&handle,
                                                           p_request->token,
                                                           p_request->header.token_len);
            if (err_code == NRF_SUCCESS)
            {
                (void)internal_coap_observe_client_unregister(handle);
                COAP_TRC("OBSERVE=1 in request, client_unregister handle: %i", handle);

            }
        }
    }

    COAP_EXIT();
}

void coap_observe_client_response_handle(coap_message_t * p_response, coap_queue_item_t * p_item)
{
    COAP_ENTRY();

    if (observe_opt_present(p_response) == NRF_SUCCESS)
    {
        if (p_item == NULL)
        {
            // Search for the token in the observable list.
            uint32_t handle;
            uint32_t err_code = internal_coap_observe_client_search(&handle, p_response->token, p_response->header.token_len);
            if (err_code == NRF_SUCCESS)
            {
                // Fetch the observable.
                coap_observable_t * p_observable;
                err_code = internal_coap_observe_client_get(handle, &p_observable);
                if (err_code == NRF_SUCCESS)
                {
                    // Update max-age to the newly recieved message.
                    set_max_age(p_observable, p_response);

                    COAP_MUTEX_UNLOCK();

                    // Callback to the application.
                    p_observable->response_callback(NRF_SUCCESS, NULL, p_response);

                    COAP_MUTEX_LOCK();

                    COAP_TRC("Notification received on handle: %i", handle);

        #ifdef COAP_AUTOMODE
                    if (p_response->header.type == COAP_TYPE_CON)
                    {
                        // Reply an ACK upon CON message.
                    }
                    else if (p_response->header.type == COAP_TYPE_RST)
                    {
                        // Remove observable from list.
                    }
        #endif
                }
                else
                {
        #ifdef COAP_AUTOMODE
                    if (p_response->header.type == COAP_TYPE_CON)
                    {
                        // Reply reset upon CON message when observer is not located.
                    }
        #endif
                }
            }
            else
            {
                // Send RST message back to server to indicate there is no one listening.
            }
        }
        else // p_item set.
        {
            // If there is no observable instance created yet for thit token, add it.
            uint32_t handle;
            uint32_t err_code = internal_coap_observe_client_search(&handle, p_response->token, p_response->header.token_len);
            if (err_code == (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE))
            {
                // If the response is a valid response, add the observable resource.
                if (p_response->header.code == COAP_CODE_205_CONTENT)
                {
                    coap_observable_t observable;
                    // Token Length.
                    observable.token_len = p_response->header.token_len;
                    // Remote.
                    memcpy(&observable.remote, &p_response->remote, sizeof(coap_remote_t));
                    // Token.
                    memcpy(observable.token, p_response->token, observable.token_len);
                    // Callback to be called upon notification.
                    observable.response_callback = p_item->callback;

                    // Update max-age to the newly recieved message.
                    set_max_age(&observable, p_response);

                    // Register the observable.
                    uint32_t observable_resource_handle;
                    (void)internal_coap_observe_client_register(&observable_resource_handle, &observable);
                    // TODO: error check

                    COAP_TRC("Subscription response received, client_register handle: %i", observable_resource_handle);
                }
            }
        }
    }
    else // COAP_OPT_OBSERVE not present
    {
        uint32_t handle;
        uint32_t err_code = internal_coap_observe_client_search(&handle, p_response->token, p_response->header.token_len);
        if (err_code == NRF_SUCCESS)
        {
            (void)internal_coap_observe_client_unregister(handle);
            COAP_TRC("OBSERVE not present in notification, client_unregister handle: %i", handle);
        }
    }

    COAP_EXIT();
}
#else
#define observe_client_init(...)
#endif

void internal_coap_observe_init(void)
{
    observe_server_init();
    observe_client_init();
}

#if (COAP_ENABLE_OBSERVE_SERVER == 1)

uint32_t coap_observe_server_register(uint32_t * p_handle, coap_observer_t * p_observer)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_server_register(p_handle, p_observer);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_server_unregister(uint32_t handle)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_server_unregister(handle);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_server_search(uint32_t * p_handle, coap_remote_t * p_observer_addr, coap_resource_t * p_resource)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_server_search(p_handle, p_observer_addr, p_resource);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_server_next_get(coap_observer_t ** pp_observer, coap_observer_t * p_observer, coap_resource_t * p_resource)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_server_next_get(pp_observer, p_observer, p_resource);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_server_get(uint32_t handle, coap_observer_t ** pp_observer)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_server_get(handle, pp_observer);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

#endif // COAP_ENABLE_OBSERVE_SERVER = 1

#if (COAP_ENABLE_OBSERVE_CLIENT == 1)

uint32_t coap_observe_client_register(uint32_t * p_handle, coap_observable_t * p_observable)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_client_register(p_handle, p_observable);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_client_unregister(uint32_t handle)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_client_unregister(handle);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_client_search(uint32_t * p_handle, uint8_t * p_token, uint16_t token_len)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_client_search(p_handle, p_token, token_len);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_client_get(uint32_t handle, coap_observable_t ** pp_observable)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_client_get(handle, pp_observable);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

uint32_t coap_observe_client_next_get(coap_observable_t ** pp_observable, uint32_t * p_handle, coap_observable_t * p_observable)
{
    COAP_MUTEX_UNLOCK();

    uint32_t err_code = internal_coap_observe_client_next_get(pp_observable, p_handle, p_observable);

    COAP_MUTEX_UNLOCK();

    return err_code;
}

#endif // COAP_ENABLE_OBSERVE_CLIENT == 1
