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

#include "sdk_config.h"
#if APP_USBD_ENABLED
#include "sdk_common.h"
#include "app_usbd.h"
#include "app_usbd_core.h"

/* Base variables tests */

/* Check event of app_usbd_event_type_t enumerator */
STATIC_ASSERT((int32_t)APP_USBD_EVT_FIRST_APP == (int32_t)NRF_DRV_USBD_EVT_CNT);
STATIC_ASSERT(sizeof(app_usbd_event_type_t) == sizeof(nrf_drv_usbd_event_type_t));

STATIC_ASSERT(sizeof(app_usbd_descriptor_header_t) == 2);
STATIC_ASSERT(sizeof(app_usbd_descriptor_device_t) == 18);
STATIC_ASSERT(sizeof(app_usbd_descriptor_configuration_t) == 9);
STATIC_ASSERT(sizeof(app_usbd_descriptor_iface_t) == 9);
STATIC_ASSERT(sizeof(app_usbd_descriptor_ep_t) == 7);
STATIC_ASSERT(sizeof(app_usbd_descriptor_iad_t) == 8);

STATIC_ASSERT(sizeof(app_usbd_setup_t) == sizeof(nrf_drv_usbd_setup_t));

/**
 * @internal
 * @defgroup app_usbd_internals USBD library internals
 * @ingroup app_usbd
 *
 * Internal variables, auxiliary macros and functions of USBD library.
 * @{
 */

/**
 * @brief Variable type for endpoint configuration
 *
 * Each endpoint would have assigned this type of configuration structure.
 */
typedef struct
{
    /**
     * @brief The class instance
     *
     * The pointer to the class instance that is connected to the endpoint.
     */
    app_usbd_class_inst_t const * p_cinst;

    /**
     * @brief Endpoint event handler.
     *
     * Event handler for the endpoint.
     * It is set to event handler for the class instance during connection by default,
     * but it can be then updated for as a reaction for @ref APP_USBD_EVT_ATTACHED event.
     * This way we can speed up the interpretation of endpoint related events.
     */
    app_usbd_ep_event_handler_t event_handler;
}app_usbd_ep_conf_t;

/**
 * @brief Instances connected with IN endpoints
 *
 * Array of instance pointers connected with every IN endpoint.
 * @sa m_epout_instances
 */
static app_usbd_ep_conf_t m_epin_conf[NRF_USBD_EPIN_CNT];

/**
 * @brief Instances connected with OUT endpoints
 *
 * Array of instance pointers connected with every OUT endpoint.
 * @sa m_epin_instances
 */
static app_usbd_ep_conf_t m_epout_conf[NRF_USBD_EPIN_CNT];

/**
 * @brief Beginning of classes list
 *
 * All enabled in current configuration instances are connected into
 * a single linked list chain.
 * This variable points to first element.
 * Core class instance (connected to endpoint 0) is not listed here.
 */
static app_usbd_class_inst_t const * m_p_first_cinst;

/**
 * @brief Classes list that requires SOF events
 *
 * @todo RK Implement and documentation
 */
static app_usbd_class_inst_t const * m_p_first_sof_cinst;

/**
 * @brief Default configuration (when NULL is passed to @ref app_usbd_init).
 */
static const app_usbd_config_t m_default_conf = {
        .ev_handler = NULL
};

/**
 * @brief Current configuration.
 */
static app_usbd_config_t m_current_conf;

/**
 * @brief Class interface call: event handler
 *
 * @ref app_usbd_class_interface_t::event_handler
 *
 * @param[in] p_cinst Class instance
 * @param[in] p_event Event passed to class instance
 *
 * @return Standard error code @ref ret_code_t
 * @retval NRF_SUCCESS event handled successfully
 * @retval NRF_ERROR_NOT_SUPPORTED unsupported event
 * */
static inline ret_code_t class_event_handler(app_usbd_class_inst_t  const * const p_cinst,
                                             app_usbd_complex_evt_t const * const p_event)
{
    ASSERT(p_cinst != NULL);
    ASSERT(p_cinst->p_class_methods != NULL);
    ASSERT(p_cinst->p_class_methods->event_handler != NULL);
    return p_cinst->p_class_methods->event_handler(p_cinst, p_event);
}

/**
 * @brief User event handler call (passed via configuration).
 *
 * @param event Event type.
 */
static inline void user_event_handler(app_usbd_event_type_t event)
{
    if ((m_current_conf.ev_handler) != NULL)
    {
        m_current_conf.ev_handler(event);
    }
}

/**
 * @brief Class interface call: get descriptors
 *
 * @ref app_usbd_class_interface_t::get_descriptors
 *
 * @param[in]  p_inst Class instance
 * @param[out] p_size Descriptors size
 *
 * @return Class descriptors start address
 * */
static inline const void * class_get_descriptors(app_usbd_class_inst_t const * const p_cinst,
                                                 size_t * p_size)
{
    ASSERT(p_cinst != NULL);
    ASSERT(p_cinst->p_class_methods != NULL);
    ASSERT(p_cinst->p_class_methods->get_descriptors != NULL);
    return p_cinst->p_class_methods->get_descriptors(p_cinst, p_size);
}

const void * app_usbd_class_descriptor_find(app_usbd_class_inst_t const * const p_cinst,
                                            uint8_t  desc_type,
                                            uint8_t  desc_index,
                                            size_t * p_desc_len)
{
    app_usbd_descriptor_header_t const * p_header;
    uint8_t const * p_raw = class_get_descriptors(p_cinst, p_desc_len);
    if (p_raw == NULL)
    {
        return NULL;
    }

    size_t pos = 0;
    uint8_t index = 0;
    while (pos < *p_desc_len)
    {
        p_header = (app_usbd_descriptor_header_t const *)(p_raw + pos);
        if (p_header->bDescriptorType == desc_type)
        {
            if (desc_index == index)
            {
                *p_desc_len = p_header->bLength;
                return p_header;
            }

            index++;
        }

        pos += p_header->bLength;
    }

    return NULL;
}

/**
 * @brief Access into selected endpoint configuration structure
 *
 * @param ep Endpoint address
 * @return A pointer to the endpoint configuration structure
 *
 * @note This function would assert when endpoint number is not correct and debugging is enabled.
 */
static app_usbd_ep_conf_t * app_usbd_ep_conf_access(nrf_drv_usbd_ep_t ep)
{
    if (NRF_USBD_EPIN_CHECK(ep))
    {
        uint8_t nr = NRF_USBD_EP_NR_GET(ep);
        ASSERT(nr < NRF_USBD_EPIN_CNT);
        return &m_epin_conf[nr];
    }
    else
    {
        uint8_t nr = NRF_USBD_EP_NR_GET(ep);
        ASSERT(nr < NRF_USBD_EPOUT_CNT);
        return &m_epout_conf[nr];
    }
}

/**
 * @brief Accessing instance connected with selected endpoint
 *
 * @param ep Endpoint number
 *
 * @return The pointer to the instance connected with endpoint
 */
static inline app_usbd_class_inst_t const * app_usbd_ep_instance_get(nrf_drv_usbd_ep_t ep)
{
    return app_usbd_ep_conf_access(ep)->p_cinst;
}

/**
 * @brief Connect instance with selected endpoint
 *
 * This function configures instance connected to endpoint but also sets
 * default event handler function pointer.
 *
 * @param ep      Endpoint number
 * @param p_cinst The instance to connect into the selected endpoint.
 *                NULL if endpoint is going to be disconnected.
 *
 * @note Disconnecting EP0 is not allowed and protected by assertion.
 */
static void app_usbd_ep_instance_set(nrf_drv_usbd_ep_t ep, app_usbd_class_inst_t const * p_cinst)
{
    app_usbd_ep_conf_t * p_ep_conf = app_usbd_ep_conf_access(ep);
    /* Set instance and default event handler */
    p_ep_conf->p_cinst = p_cinst;
    if (p_cinst == NULL)
    {
        ASSERT((ep != NRF_DRV_USBD_EPOUT0) && (ep != NRF_DRV_USBD_EPIN0)); /* EP0 should never be disconnected */
        p_ep_conf->event_handler = NULL;
    }
    else
    {
        p_ep_conf->event_handler = p_cinst->p_class_methods->event_handler;
    }
}

/**
 * @brief Call the core handler
 *
 * Core instance is special kind of instance that is connected only to endpoint 0.
 * It is not present in instance list.
 * This auxiliary function makes future changes easier.
 * Just call the event instance for core module here.
 */
static inline ret_code_t app_usbd_core_handler_call(nrf_drv_usbd_evt_t const * const p_event)
{
    return m_epout_conf[0].event_handler(
        m_epout_conf[0].p_cinst,
        (app_usbd_complex_evt_t const *)p_event);
}

/**
 * @brief USBD event handler
 *
 *
 */
static void app_usbd_event_handler(nrf_drv_usbd_evt_t const * const p_event)
{
    ASSERT(NULL != m_p_first_cinst);

    /* Note - there should never be situation that event is generated on disconnected endpoint */
    switch(p_event->type)
    {
        case NRF_DRV_USBD_EVT_SOF:
        {
            app_usbd_class_inst_t const * p_inst = app_usbd_class_sof_first_get();
            ASSERT(NULL != p_inst); /* This should not happen - when no SOF instances are in the list, SOF event is disabled */

            while (NULL != p_inst)
            {
                ret_code_t r = class_event_handler(p_inst, (app_usbd_complex_evt_t const *)p_event);
                UNUSED_VARIABLE(r);
                p_inst = app_usbd_class_sof_next_get(p_inst);
            }
            break;
        }

        /* Reset and */
        case NRF_DRV_USBD_EVT_RESET:
        case NRF_DRV_USBD_EVT_RESUME:
        {
            /* Processing core interface (connected only to EP0) and then all instances from the list */
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }
        case NRF_DRV_USBD_EVT_SUSPEND:
        {
            /* Processing all instances from the list and then core interface (connected only to EP0) */
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            break;
        }

        case NRF_DRV_USBD_EVT_SETUP:
        {
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            break;
        }

        case NRF_DRV_USBD_EVT_EPTRANSFER:
        {
            app_usbd_ep_conf_t const * p_ep_conf =
                    app_usbd_ep_conf_access(p_event->data.eptransfer.ep);
            ASSERT(NULL != p_ep_conf->p_cinst);
            ASSERT(NULL != p_ep_conf->event_handler);

            if (NRF_SUCCESS != p_ep_conf->event_handler(p_ep_conf->p_cinst,
                                                       (app_usbd_complex_evt_t const *)p_event))
            {
                /* If error returned, every bulk/interrupt endpoint would be stalled */
                if (!(0 == NRF_USBD_EP_NR_GET(p_event->data.eptransfer.ep) ||
                   NRF_USBD_EPISO_CHECK(p_event->data.eptransfer.ep)))
                {
                    nrf_drv_usbd_ep_stall(p_event->data.eptransfer.ep);
                }
            }
            break;
        }

        default:
            ASSERT(0);
            break;
    }

    user_event_handler((app_usbd_event_type_t)p_event->type);
}

/** @} */


ret_code_t app_usbd_init(app_usbd_config_t const * p_config)
{
    ret_code_t ret;

    ret = nrf_drv_usbd_init(app_usbd_event_handler);
    if (NRF_SUCCESS != ret)
    {
        return ret;
    }

    if (p_config == NULL)
    {
        m_current_conf = m_default_conf;
    }
    else
    {
        m_current_conf = *p_config;
    }

    /* Clear variables */
    m_p_first_cinst = NULL;
    m_p_first_sof_cinst = NULL;
    memset(m_epin_conf , 0, sizeof(m_epin_conf ));
    memset(m_epout_conf, 0, sizeof(m_epout_conf));

    /*Pin core class to required endpoints*/
    uint8_t iface_idx;
    app_usbd_class_iface_conf_t const * p_iface;
    app_usbd_class_inst_t const * const p_inst = app_usbd_core_instance_access();
    iface_idx = 0;
    while ((p_iface = app_usbd_class_iface_get(p_inst, iface_idx++)) != NULL)
    {
        uint8_t ep_idx = 0;
        app_usbd_class_ep_conf_t const * p_ep;
        while ((p_ep = app_usbd_class_iface_ep_get(p_iface, ep_idx++)) != NULL)
        {
            app_usbd_ep_instance_set(app_usbd_class_ep_address_get(p_ep), p_inst);
        }
    }

    /* Successfully attached */
    const app_usbd_evt_t evt_data = {
            .type = APP_USBD_EVT_INST_APPEND
    };

    return class_event_handler(p_inst, (app_usbd_complex_evt_t const *)(&evt_data));
}


ret_code_t app_usbd_uninit(void)
{
    ret_code_t ret;

    ret = nrf_drv_usbd_uninit();
    if(NRF_SUCCESS != ret)
        return ret;

    /* Unchain instance list */
    app_usbd_class_inst_t const * * pp_inst;
    pp_inst = &m_p_first_cinst;
    while (NULL != (*pp_inst))
    {
        app_usbd_class_inst_t const * * pp_next = &app_usbd_class_data_access(*pp_inst)->p_next;
        (*pp_inst) = NULL;
        pp_inst = pp_next;
    }

    /* Unchain SOF list */
    pp_inst = &m_p_first_sof_cinst;
    while (NULL != (*pp_inst))
    {
        app_usbd_class_inst_t const * * pp_next = &app_usbd_class_data_access(*pp_inst)->p_sof_next;
        (*pp_inst) = NULL;
        pp_inst = pp_next;
    }

    /* Clear all endpoints configurations */
    memset(m_epin_conf , 0, sizeof(m_epin_conf ));
    memset(m_epout_conf, 0, sizeof(m_epout_conf));
    /* Clear current configuration */
    memset(&m_current_conf, 0, sizeof(m_current_conf));

    return ret;
}


void app_usbd_enable(void)
{
    nrf_drv_usbd_enable();
    while (!app_usbd_core_power_regulator_is_ready())
    {
        /* Just waiting */
    }
}


void app_usbd_disable(void)
{
    if (nrf_drv_usbd_is_started())
    {
        app_usbd_stop();
    }
    nrf_drv_usbd_disable();
}


void app_usbd_start(void)
{
    const app_usbd_evt_t evt_data = {
            .type = APP_USBD_EVT_START
    };

    /* Enable all connected endpoints */
    uint8_t n;
    for (n = 1; n < ARRAY_SIZE(m_epin_conf); ++n)
    {
        if (NULL != m_epin_conf[n].p_cinst)
        {
            nrf_drv_usbd_ep_enable(NRF_DRV_USBD_EPIN(n));
        }
    }
    for (n = 1; n < ARRAY_SIZE(m_epout_conf); ++n)
    {
        if (NULL != m_epout_conf[n].p_cinst)
        {
            nrf_drv_usbd_ep_enable(NRF_DRV_USBD_EPOUT(n));
        }
    }

    /* Send event to all classes */
    UNUSED_RETURN_VALUE(app_usbd_core_handler_call((nrf_drv_usbd_evt_t const * )&evt_data));
    app_usbd_all_call((app_usbd_complex_evt_t const *)&evt_data);
    user_event_handler(APP_USBD_EVT_START);

    nrf_drv_usbd_start(NULL != m_p_first_sof_cinst);
}


void app_usbd_stop(void)
{
    const app_usbd_evt_t evt_data = {
            .type = APP_USBD_EVT_STOP
    };

    nrf_drv_usbd_stop();

    /* Send event to all classes */
    app_usbd_all_call((app_usbd_complex_evt_t const * )&evt_data);
    UNUSED_RETURN_VALUE(app_usbd_core_handler_call((nrf_drv_usbd_evt_t const *)&evt_data));
    user_event_handler(APP_USBD_EVT_STOP);
}


ret_code_t app_usbd_class_append(app_usbd_class_inst_t const * p_cinst)
{
    ASSERT(NULL != p_cinst);
    ASSERT(NULL != p_cinst->p_class_methods);
    ASSERT(NULL != p_cinst->p_class_methods->event_handler);
    ASSERT(NULL == app_usbd_class_data_access(p_cinst)->p_next);

    /* This should be only called if USBD is disabled
     * We simply assume that USBD is enabled if its interrupts are */
    ASSERT(!nrf_drv_usbd_is_enabled() && nrf_drv_usbd_is_initialized());

    /* Check if all required endpoints are available
     * Checking is splitted from setting to avoid situation that anything
     * is modified and then operation finishes with error */
    uint8_t iface_idx;
    app_usbd_class_iface_conf_t const * p_iface;

    iface_idx = 0;
    while (NULL != (p_iface = app_usbd_class_iface_get(p_cinst, iface_idx++)))
    {
        uint8_t ep_idx = 0;
        app_usbd_class_ep_conf_t const * p_ep;
        while (NULL != (p_ep = app_usbd_class_iface_ep_get(p_iface, ep_idx++)))
        {
            if (NULL != app_usbd_ep_instance_get(app_usbd_class_ep_address_get(p_ep)))
            {
                return NRF_ERROR_BUSY;
            }
        }
    }

    /* Connecting all required endpoints */
    iface_idx = 0;
    while (NULL != (p_iface = app_usbd_class_iface_get(p_cinst, iface_idx++)))
    {
        uint8_t ep_idx = 0;
        app_usbd_class_ep_conf_t const * p_ep;
        while (NULL != (p_ep = app_usbd_class_iface_ep_get(p_iface, ep_idx++)))
        {
            app_usbd_ep_instance_set(app_usbd_class_ep_address_get(p_ep), p_cinst);
        }
    }

    /* Adding pointer to this instance to the end of the chain */
    app_usbd_class_inst_t const * * pp_last = &m_p_first_cinst;
    while (NULL != (*pp_last))
    {
        ASSERT((*pp_last) != p_cinst);
        pp_last = &(app_usbd_class_data_access(*pp_last)->p_next);
    }
    (*pp_last) = p_cinst;

    /* Successfully attached */
    const app_usbd_evt_t evt_data = {.type = APP_USBD_EVT_INST_APPEND };
    return class_event_handler(p_cinst, (app_usbd_complex_evt_t const *)(&evt_data));
}


ret_code_t app_usbd_class_remove(app_usbd_class_inst_t const * p_cinst)
{
    ASSERT(NULL != p_cinst);
    ASSERT(NULL != p_cinst->p_class_methods);
    ASSERT(NULL != p_cinst->p_class_methods->event_handler);
    /** This function should be only called if USBD is disabled */
    ASSERT(!nrf_drv_usbd_is_enabled() && nrf_drv_usbd_is_initialized());
    ret_code_t ret;
    /* Remove this class from the chain */
    app_usbd_class_inst_t const * * pp_last = &m_p_first_cinst;
    while (NULL != (*pp_last))
    {
        if ((*pp_last) == p_cinst)
        {
            /* Inform class instance that removing process is going to be started */
            const app_usbd_evt_t evt_data = {
                    .type = APP_USBD_EVT_INST_REMOVE
            };
            ret = class_event_handler(p_cinst, (app_usbd_complex_evt_t const *)(&evt_data));
            if (ret != NRF_SUCCESS)
            {
                return ret;
            }

            /* Breaking chain */
            (*pp_last) = (app_usbd_class_data_access(p_cinst)->p_next);
            app_usbd_class_data_access(p_cinst)->p_next = NULL;

            /* Disconnecting endpoints */
            uint8_t ep_idx;
            for (ep_idx = 0; ep_idx < NRF_USBD_EPIN_CNT; ++ep_idx)
            {
                nrf_drv_usbd_ep_t ep = NRF_DRV_USBD_EPIN(ep_idx);
                if (app_usbd_ep_instance_get(ep) == p_cinst)
                {
                    app_usbd_ep_instance_set(ep, NULL);
                }
            }
            for (ep_idx = 0; ep_idx < NRF_USBD_EPOUT_CNT; ++ep_idx)
            {
                nrf_drv_usbd_ep_t ep = NRF_DRV_USBD_EPOUT(ep_idx);
                if (app_usbd_ep_instance_get(ep) == p_cinst)
                {
                    app_usbd_ep_instance_set(ep, NULL);
                }
            }

            return NRF_SUCCESS;
        }
        pp_last = &(app_usbd_class_data_access(*pp_last)->p_next);
    }

    return NRF_ERROR_NOT_FOUND;
}


ret_code_t app_usbd_class_remove_all(void)
{
    ret_code_t ret = NRF_SUCCESS;
    while (NULL != m_p_first_cinst)
    {
        ret = app_usbd_class_remove(m_p_first_cinst);
        if (ret != NRF_SUCCESS)
        {
            break;
        }
    }

    return ret;
}


ret_code_t app_usbd_ep_handler_set(app_usbd_class_inst_t const * const p_cinst,
                                   nrf_drv_usbd_ep_t ep,
                                   app_usbd_ep_event_handler_t handler)
{
    ASSERT(NULL != p_cinst);
    ASSERT(NULL != handler);
    /** This function should be only called if USBD is disabled */
    ASSERT(!nrf_drv_usbd_is_enabled() && nrf_drv_usbd_is_initialized());

    if (p_cinst != app_usbd_ep_instance_get(ep))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    (app_usbd_ep_conf_access(ep))->event_handler = handler;
    return NRF_SUCCESS;
}


ret_code_t app_usbd_class_sof_register(app_usbd_class_inst_t const * p_cinst)
{
    ASSERT(NULL != p_cinst);
    ASSERT(NULL != p_cinst->p_class_methods);
    ASSERT(NULL != p_cinst->p_class_methods->event_handler);
    /** This function should be only called if USBD is disabled */
    ASSERT(!nrf_drv_usbd_is_enabled() && nrf_drv_usbd_is_initialized());

    /* Next SOF event requiring instance have to be null now  */
    ASSERT(NULL == (app_usbd_class_data_access(p_cinst)->p_sof_next));

    /* Adding pointer to this instance to the end of the chain */
    app_usbd_class_inst_t const * * pp_last = &m_p_first_sof_cinst;
    while (NULL != (*pp_last))
    {

       ASSERT((*pp_last) != p_cinst);
       pp_last = &(app_usbd_class_data_access(*pp_last)->p_sof_next);
    }
    (*pp_last) = p_cinst;

    return NRF_SUCCESS;
}


ret_code_t app_usbd_class_sof_unregister(app_usbd_class_inst_t const * p_cinst)
{
    ASSERT(NULL != p_cinst);
    /** This function should be only called if USBD is disabled */
    ASSERT(!nrf_drv_usbd_is_enabled() && nrf_drv_usbd_is_initialized());

    app_usbd_class_inst_t const * * pp_last = &m_p_first_sof_cinst;
    while (NULL != (*pp_last))
    {
        if ((*pp_last) == p_cinst)
        {
            /* Breaking chain */
            (*pp_last) = (app_usbd_class_data_access(p_cinst)->p_sof_next);
            app_usbd_class_data_access(p_cinst)->p_sof_next = NULL;

            return NRF_SUCCESS;
        }
        pp_last = &(app_usbd_class_data_access(*pp_last)->p_sof_next);
    }
    return NRF_ERROR_NOT_FOUND;
}

ret_code_t app_usbd_interface_std_req_handle(app_usbd_setup_evt_t  const * p_setup_ev)
{
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_SETUP_STDREQ_GET_STATUS:
        {
            size_t tx_size;
            uint16_t * p_tx_buff = app_usbd_core_setup_transfer_buff_get(&tx_size);

            p_tx_buff[0] = 0;
            return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_tx_buff, sizeof(uint16_t));
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

ret_code_t app_usbd_endpoint_std_req_handle(app_usbd_setup_evt_t const * p_setup_ev)
{
    nrf_drv_usbd_ep_t ep_addr = (nrf_drv_usbd_ep_t)(p_setup_ev->setup.wIndex.lb);
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_SETUP_STDREQ_GET_STATUS:
        {
            size_t tx_size;
            uint16_t * p_tx_buff = app_usbd_core_setup_transfer_buff_get(&tx_size);

            p_tx_buff[0] = nrf_drv_usbd_ep_stall_check(ep_addr) ? 1 : 0;
            return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_tx_buff, sizeof(uint16_t));
        }
        case APP_USBD_SETUP_STDREQ_SET_FEATURE:
        {
            if (p_setup_ev->setup.wValue.w != APP_USBD_SETUP_STDFEATURE_ENDPOINT_HALT)
             {
                 return NRF_ERROR_NOT_SUPPORTED;
             }

            nrf_drv_usbd_ep_stall(ep_addr);
            return NRF_SUCCESS;
        }
        case APP_USBD_SETUP_STDREQ_CLEAR_FEATURE:
        {
            if (p_setup_ev->setup.wValue.w != APP_USBD_SETUP_STDFEATURE_ENDPOINT_HALT)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            if (nrf_usbd_dtoggle_get(ep_addr) != NRF_USBD_DTOGGLE_DATA0)
            {
                nrf_usbd_dtoggle_set(ep_addr, NRF_USBD_DTOGGLE_DATA0);
            }

            if (NRF_USBD_EPISO_CHECK(ep_addr) == 0)
            {
                nrf_drv_usbd_ep_stall_clear(ep_addr);
            }

            return NRF_SUCCESS;
        }
        default:
            return NRF_ERROR_NOT_SUPPORTED;
    }
}

ret_code_t app_usbd_req_std_set_interface(app_usbd_class_inst_t const * const p_cinst,
                                          app_usbd_setup_evt_t  const * const p_setup_ev)
{
    uint8_t iface_count = app_usbd_class_iface_count_get(p_cinst);

    app_usbd_class_iface_conf_t const * p_iface = NULL;
    for (uint8_t j = 0; j < iface_count; ++j)
    {
        p_iface = app_usbd_class_iface_get(p_cinst, j);
        if (p_iface->number == p_setup_ev->setup.wIndex.lb)
        {
            break;
        }
    }

    if (p_iface == NULL)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    uint8_t ep_count = app_usbd_class_iface_ep_count_get(p_iface);

    for (uint8_t j = 0; j < ep_count; ++j)
    {
        /*Clear stall for every endpoint*/
        app_usbd_class_ep_conf_t const * p_ep = app_usbd_class_iface_ep_get(p_iface, j);

        if (nrf_usbd_dtoggle_get(p_ep->address) != NRF_USBD_DTOGGLE_DATA0)
        {
            nrf_usbd_dtoggle_set(p_ep->address, NRF_USBD_DTOGGLE_DATA0);
        }

        if (NRF_USBD_EPISO_CHECK(p_ep->address) == 0)
        {
            nrf_drv_usbd_ep_stall_clear(p_ep->address);
        }

    }

    return NRF_SUCCESS;
}

app_usbd_class_inst_t const * app_usbd_class_first_get(void)
{
    return m_p_first_cinst;
}

app_usbd_class_inst_t const * app_usbd_class_sof_first_get(void)
{
    return m_p_first_sof_cinst;
}

ret_code_t app_usbd_iface_call(uint8_t iface, app_usbd_complex_evt_t const * const p_event)
{
    ASSERT(NULL != m_p_first_cinst);
    /*Iterate over classes*/
    app_usbd_class_inst_t const * p_inst = app_usbd_class_first_get();
    while (p_inst != NULL)
    {
        uint8_t iface_count = app_usbd_class_iface_count_get(p_inst);
        /*Iterate over interfaces*/
        for (uint8_t i = 0; i < iface_count; ++i)
        {
            app_usbd_class_iface_conf_t const * p_iface;
            p_iface = app_usbd_class_iface_get(p_inst, i);
            if (app_usbd_class_iface_number_get(p_iface) == iface)
            {
                return class_event_handler(p_inst, p_event);
            }
        }
        p_inst = app_usbd_class_next_get(p_inst);
    }

    return NRF_ERROR_INVALID_ADDR;
}

ret_code_t app_usbd_ep_call(nrf_drv_usbd_ep_t ep, app_usbd_complex_evt_t const * const p_event)
{
    app_usbd_class_inst_t const * p_inst = app_usbd_ep_conf_access(ep)->p_cinst;
    if (p_inst != NULL)
    {
       return class_event_handler(p_inst, p_event);
    }

    return NRF_ERROR_INVALID_ADDR;
}

void app_usbd_all_call(app_usbd_complex_evt_t const * const p_event)
{
    app_usbd_class_inst_t const * p_inst;
    for (p_inst = app_usbd_class_first_get(); NULL != p_inst;
         p_inst = app_usbd_class_next_get(p_inst))
    {
        UNUSED_RETURN_VALUE(class_event_handler(p_inst, p_event));
    }
}

ret_code_t app_usbd_all_until_served_call(app_usbd_complex_evt_t const * const p_event)
{
    app_usbd_class_inst_t const * p_inst;
    ret_code_t ret = NRF_ERROR_NOT_SUPPORTED;
    /* Try to process via every instance */
    for (p_inst = app_usbd_class_first_get(); NULL != p_inst;
         p_inst = app_usbd_class_next_get(p_inst))
    {

        ret = class_event_handler(p_inst, p_event);
        if (NRF_ERROR_NOT_SUPPORTED != ret)
        {
            /* Processing finished */
            break;
        }
    }

    return ret;
}

#endif // APP_USBD_ENABLED
