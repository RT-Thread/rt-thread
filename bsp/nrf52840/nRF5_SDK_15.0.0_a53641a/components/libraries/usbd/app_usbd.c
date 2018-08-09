/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(APP_USBD)

#include "app_usbd.h"
#include "app_usbd_core.h"
#include "nrf_power.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_power.h"
#if APP_USBD_CONFIG_EVENT_QUEUE_ENABLE
#include "nrf_atfifo.h"
#include "nrf_atomic.h"
#endif

#define NRF_LOG_MODULE_NAME app_usbd

#if APP_USBD_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       APP_USBD_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  APP_USBD_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR APP_USBD_CONFIG_DEBUG_COLOR
#else //APP_USBD_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //APP_USBD_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


/* Base variables tests */

/* Check event of app_usbd_event_type_t enumerator */
STATIC_ASSERT((int32_t)APP_USBD_EVT_FIRST_POWER == (int32_t)NRF_DRV_USBD_EVT_CNT);
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

#if (APP_USBD_PROVIDE_SOF_TIMESTAMP) || defined(__SDK_DOXYGEN__)
/**
 * @brief The last received frame number.
 */
static uint16_t m_last_frame;
#endif

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
 * @brief Internal event with SOF counter.
 */
typedef struct
{
    app_usbd_internal_evt_t evt;     //!< Internal event type

#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE) \
     || defined(__SDK_DOXYGEN__)
    uint16_t                sof_cnt;        //!< Number of the SOF events that appears before current event
    uint16_t                start_frame;    //!< Number of the SOF frame that starts this event
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)

} app_usbd_internal_queue_evt_t;

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
/**
 * @brief Event queue
 *
 * The queue with events to be processed
 */
NRF_ATFIFO_DEF(m_event_queue, app_usbd_internal_queue_evt_t, APP_USBD_CONFIG_EVENT_QUEUE_SIZE);

#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE) \
     || defined(__SDK_DOXYGEN__)

/** @brief SOF events counter */
static nrf_atomic_u32_t m_sof_events_cnt;

/** @brief SOF Frame counter */
static uint16_t m_event_frame;

// Limit of SOF events stacked until warning message.
#define APP_USBD_SOF_WARNING_LIMIT 500
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
       //  || defined(__SDK_DOXYGEN__)

#endif

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
#if (!(APP_USBD_CONFIG_EVENT_QUEUE_ENABLE)) || defined(__SDK_DOXYGEN__)
    .ev_handler = app_usbd_event_execute,
#endif
#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
    .ev_isr_handler = NULL,
#endif
    .ev_state_proc = NULL,
    .enable_sof = false
};

/**
 * @brief SUSPEND state machine states
 *
 * The enumeration of internal SUSPEND state machine states.
 */
typedef enum
{
    SUSTATE_STOPPED,                     /**< The USB driver was not started */
    SUSTATE_STARTED,                     /**< The USB driver was started - waiting for USB RESET */
    SUSTATE_ACTIVE,                      /**< Active state */
    SUSTATE_SUSPENDING,                  /**< Suspending - waiting for the user to acknowledge */
    SUSTATE_SUSPEND,                     /**< Suspended */
    SUSTATE_RESUMING,                    /**< Resuming - waiting for clock */
    SUSTATE_WAKINGUP_WAITING_HFCLK_WREQ, /**< Waking up - waiting for clock and WUREQ from driver */
    SUSTATE_WAKINGUP_WAITING_HFCLK,      /**< Waking up - waiting for HFCLK (WUREQ detected) */
    SUSTATE_WAKINGUP_WAITING_WREQ,       /**< Waking up - waiting for WREQ (HFCLK active) */
}app_usbd_sustate_t;

/**
 * @brief Current suspend state
 *
 * The state of the suspend state machine
 */
static app_usbd_sustate_t m_sustate;

/**
 * @brief Remote wake-up register/unregister
 *
 * Counter incremented when appended instance required remote wake-up functionality.
 * It should be decremented when the class is removed.
 * When this counter is not zero, remote wake-up functionality is activated inside core.
 */
static uint8_t m_rwu_registered_counter;

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

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
/**
 * @brief User event handler call (passed via configuration).
 *
 * @param p_event Handler of an event that is going to be added into queue.
 * @param queued  The event is visible in the queue.
 */
static inline void user_event_handler(app_usbd_internal_evt_t const * const p_event, bool queued)
{
    if ((m_current_conf.ev_isr_handler) != NULL)
    {
        m_current_conf.ev_isr_handler(p_event, queued);
    }
}
#endif

/**
 * @brief User event processor call (passed via configuration)
 *
 * @param event Event type.
 */
static inline void user_event_state_proc(app_usbd_event_type_t event)
{
    if ((m_current_conf.ev_state_proc) != NULL)
    {
        m_current_conf.ev_state_proc(event);
    }
}

/**
 * @brief Find a specified descriptor
 *
 * @param[in] p_cinst Class instance
 * @param[in] desc_type Descriptor type @ref app_usbd_descriptor_t
 * @param[in] desc_index Descriptor index
 * @param[out] p_desc Pointer to escriptor
 * @param[out] p_desc_len Length of descriptor
 *
 * @return Standard error code @ref ret_code_t
 * @retval NRF_SUCCESS descriptor successfully found
 * @retval NRF_ERROR_NOT_FOUND descriptor not found
 * */
ret_code_t app_usbd_class_descriptor_find(app_usbd_class_inst_t const * const p_cinst,
                                          uint8_t                             desc_type,
                                          uint8_t                             desc_index,
                                          uint8_t                           * p_desc,
                                          size_t                            * p_desc_len)
{
    app_usbd_class_descriptor_ctx_t siz;
    APP_USBD_CLASS_DESCRIPTOR_INIT(&siz);
    uint32_t total_size = 0;
    while(p_cinst->p_class_methods->feed_descriptors(&siz, p_cinst, NULL, sizeof(uint8_t)))
    {
        total_size++;
    }

    uint8_t cur_len = 0;
    uint32_t cur_size = 0;

    uint8_t index = 0;
    app_usbd_class_descriptor_ctx_t descr;
    APP_USBD_CLASS_DESCRIPTOR_INIT(&descr);

    while(cur_size < total_size)
    {
        /* First byte of a descriptor is its size */
        UNUSED_RETURN_VALUE(p_cinst->p_class_methods->feed_descriptors(&descr,
                                                                       p_cinst,
                                                                       &cur_len,
                                                                       sizeof(uint8_t)));

        /* Second byte is type of the descriptor */
        uint8_t type;
        UNUSED_RETURN_VALUE(p_cinst->p_class_methods->feed_descriptors(&descr,
                                                                       p_cinst,
                                                                       &type,
                                                                       sizeof(uint8_t)));

        if(type == desc_type)
        {
            if(index == desc_index)
            {
                /* Copy the length of descriptor to *p_desc_len */
                *p_desc_len = cur_len;
                /* Two first bytes of descriptor have already been fed - copy them to *p_desc */
                *p_desc++ = cur_len;
                *p_desc++ = desc_type;
                /* Copy the rest of descriptor to *p_desc */
                UNUSED_RETURN_VALUE(p_cinst->p_class_methods->feed_descriptors(&descr,
                                                                               p_cinst,
                                                                               p_desc,
                                                                               cur_len-2));
                return NRF_SUCCESS;
            }
            else
            {
                index++;
            }
        }
        /* Fast-forward through unmatched descriptor */
        UNUSED_RETURN_VALUE(p_cinst->p_class_methods->feed_descriptors(&descr,
                                                                       p_cinst,
                                                                       NULL,
                                                                       cur_len-2));
        cur_size += cur_len;
    }
    return NRF_ERROR_NOT_FOUND;
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
static inline ret_code_t app_usbd_core_handler_call(app_usbd_internal_evt_t const * const p_event)
{
    return m_epout_conf[0].event_handler(
        m_epout_conf[0].p_cinst,
        (app_usbd_complex_evt_t const *)p_event);
}



/**
 * @brief Add event for execution
 *
 * Dependent on configuration event would be executed in place or would be added into queue
 * to be executed later.
 *
 * @param p_event Event to be executed
 */
static inline void app_usbd_event_add(app_usbd_internal_evt_t const * const p_event)
{
#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE)

#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
    if (p_event->app_evt.type == APP_USBD_EVT_DRV_SOF)
    {
        CRITICAL_REGION_ENTER();
        if (m_sof_events_cnt == 0)
        {
            m_event_frame = p_event->drv_evt.data.sof.framecnt;
        }
        UNUSED_RETURN_VALUE(nrf_atomic_u32_add(&m_sof_events_cnt, 1));
        CRITICAL_REGION_EXIT();
        
        user_event_handler(p_event, true);
        if (m_sof_events_cnt == APP_USBD_SOF_WARNING_LIMIT)
        {
            NRF_LOG_WARNING("Stacked over %d SOF events.", APP_USBD_SOF_WARNING_LIMIT);
        }
        return;
    }
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)

    if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_INTERRUPT)
    {
        if (p_event->app_evt.type == APP_USBD_EVT_DRV_SOF)
        {
            user_event_handler(p_event, false);
            app_usbd_event_execute(p_event);
            return;
        }
    }

    nrf_atfifo_item_put_t cx;
    app_usbd_internal_queue_evt_t * p_event_item = nrf_atfifo_item_alloc(m_event_queue, &cx);

    if (NULL != p_event_item)
    {
        bool visible;
        p_event_item->evt = *p_event;

#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
        CRITICAL_REGION_ENTER();
        p_event_item->start_frame = m_event_frame - m_sof_events_cnt + 1;
        p_event_item->sof_cnt = nrf_atomic_u32_fetch_store(&m_sof_events_cnt, 0);
        CRITICAL_REGION_EXIT();
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)

        visible = nrf_atfifo_item_put(m_event_queue, &cx);
        user_event_handler(p_event, visible);
    }
    else
    {
        NRF_LOG_ERROR("Event queue full.");
    }
#else
    m_current_conf.ev_handler(p_event);
#endif
}

/**
 * @brief Power event handler
 *
 * The function that pushes power events into the queue
 * @param p_event
 */
#if APP_USBD_CONFIG_POWER_EVENTS_PROCESS
static void app_usbd_power_event_handler(nrf_drv_power_usb_evt_t event)
{
    switch(event)
    {
        case NRF_DRV_POWER_USB_EVT_DETECTED:
        {
            static const app_usbd_internal_evt_t ev = {
                .type = APP_USBD_EVT_POWER_DETECTED
            };
            app_usbd_event_add(&ev);
            break;
        }
        case NRF_DRV_POWER_USB_EVT_REMOVED:
        {
            static const app_usbd_internal_evt_t ev = {
                .type = APP_USBD_EVT_POWER_REMOVED
            };
            app_usbd_event_add(&ev);
            break;
        }
        case NRF_DRV_POWER_USB_EVT_READY:
        {
            static const app_usbd_internal_evt_t ev = {
                .type = APP_USBD_EVT_POWER_READY
            };
            app_usbd_event_add(&ev);
            break;
        }
        default:
            ASSERT(false);
    }
}
#endif

/**
 * @brief Event handler
 *
 * The function that pushes the event into the queue
 * @param p_event
 */
static void app_usbd_event_handler(nrf_drv_usbd_evt_t const * const p_event)
{
    app_usbd_event_add((app_usbd_internal_evt_t const *)p_event);
}

/**
 * @brief HF clock ready event handler
 *
 * Function that is called when high frequency clock is started
 *
 * @param event Event type that comes from clock driver
 */
static void app_usbd_hfclk_ready(nrf_drv_clock_evt_type_t event)
{
    ASSERT(NRF_DRV_CLOCK_EVT_HFCLK_STARTED == event);
    static const app_usbd_evt_t evt_data = {
        .type = APP_USBD_EVT_HFCLK_READY
    };
    app_usbd_event_add((app_usbd_internal_evt_t const * )&evt_data);
}

/**
 * @brief Check if the HFCLK was requested in selected suspend state machine state
 *
 *
 * @param sustate State to be checked
 *
 * @retval true  High frequency clock was requested in selected state
 * @retval false High frequency clock was released in selected state
 */
static inline bool app_usbd_sustate_with_requested_hfclk(app_usbd_sustate_t sustate)
{
    switch(sustate)
    {
        case SUSTATE_STOPPED:                    return false;
        case SUSTATE_STARTED:                    return false;
        case SUSTATE_ACTIVE:                     return true;
        case SUSTATE_SUSPENDING:                 return false;
        case SUSTATE_SUSPEND:                    return false;
        case SUSTATE_RESUMING:                   return true;
        case SUSTATE_WAKINGUP_WAITING_HFCLK_WREQ: return true;
        case SUSTATE_WAKINGUP_WAITING_HFCLK:      return true;
        case SUSTATE_WAKINGUP_WAITING_WREQ:      return true;
        default:
            return false;
    }
}

/**
 * @brief Check it the HFCLK is running in selected suspend state machine state
 *
 * @param sustate State to be checked
 *
 * @retval true  High frequency clock is running in selected state
 * @retval false High frequency clock is released in selected state
 */
static inline bool app_usbd_sustate_with_running_hfclk(app_usbd_sustate_t sustate)
{
    switch(sustate)
    {
        case SUSTATE_STOPPED:                    return false;
        case SUSTATE_STARTED:                    return false;
        case SUSTATE_ACTIVE:                     return true;
        case SUSTATE_SUSPENDING:                 return false;
        case SUSTATE_SUSPEND:                    return false;
        case SUSTATE_RESUMING:                   return false;
        case SUSTATE_WAKINGUP_WAITING_HFCLK_WREQ: return false;
        case SUSTATE_WAKINGUP_WAITING_HFCLK:      return false;
        case SUSTATE_WAKINGUP_WAITING_WREQ:      return true;
        default:
            return false;
    }
}

/**
 * @brief Get current suspend state machine state
 *
 * @return The state of the suspend state machine
 */
static inline app_usbd_sustate_t sustate_get(void)
{
    return m_sustate;
}

/**
 * @brief Set current suspend state machine state
 *
 * @param sustate The requested state of the state machine
 */
static inline void sustate_set(app_usbd_sustate_t sustate)
{
    if (app_usbd_sustate_with_requested_hfclk(sustate) != app_usbd_sustate_with_requested_hfclk(m_sustate))
    {
        if (app_usbd_sustate_with_requested_hfclk(sustate))
        {
            static nrf_drv_clock_handler_item_t clock_handler_item =
            {
                .event_handler = app_usbd_hfclk_ready
            };
            nrf_drv_clock_hfclk_request(&clock_handler_item);
        }
        else
        {
            nrf_drv_clock_hfclk_release();
        }
    }
    if (app_usbd_sustate_with_running_hfclk(sustate) != app_usbd_sustate_with_running_hfclk(m_sustate))
    {
        if (app_usbd_sustate_with_running_hfclk(sustate))
        {
            nrf_drv_usbd_active_irq_config();
        }
        else
        {
            nrf_drv_usbd_suspend_irq_config();
        }
    }
    m_sustate = sustate;
}

/**
 * @brief Default selection function for interface
 *
 * This function just enables and clears interface endpoints
 *
 * @param p_inst    See the documentation for @ref app_usbd_iface_select
 * @param iface_idx See the documentation for @ref app_usbd_iface_select
 * @param alternate See the documentation for @ref app_usbd_iface_select
 * @return
 */
static inline ret_code_t default_iface_select(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx,
    uint8_t                             alternate)
{
    ASSERT(iface_idx <= app_usbd_class_iface_count_get(p_inst));

    if (alternate != 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    app_usbd_class_iface_conf_t const * p_iface  = app_usbd_class_iface_get(p_inst, iface_idx);
    uint8_t ep_count = app_usbd_class_iface_ep_count_get(p_iface);

    for (uint8_t i = 0; i < ep_count; ++i)
    {
        /* Enable every endpoint */
        app_usbd_class_ep_conf_t const * p_ep = app_usbd_class_iface_ep_get(p_iface, i);
        app_usbd_ep_enable(p_ep->address);
    }
    return NRF_SUCCESS;
}

/**
 * @brief Default deselection function for interface
 *
 * This function just disables all interface endpoints.
 *
 * @param p_inst    See the documentation for @ref app_usbd_iface_deselect
 * @param iface_idx See the documentation for @ref app_usbd_iface_deselect
 */
static inline void default_iface_deselect(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx)
{
    ASSERT(iface_idx <= app_usbd_class_iface_count_get(p_inst));

    app_usbd_class_iface_conf_t const * p_iface  = app_usbd_class_iface_get(p_inst, iface_idx);
    uint8_t ep_count = app_usbd_class_iface_ep_count_get(p_iface);

    for (uint8_t i = 0; i < ep_count; ++i)
    {
        /* Disable every endpoint */
        app_usbd_class_ep_conf_t const * p_ep = app_usbd_class_iface_ep_get(p_iface, i);
        app_usbd_ep_disable(p_ep->address);
    }
}


/** @} */

#if (APP_USBD_PROVIDE_SOF_TIMESTAMP) || defined(__SDK_DOXYGEN__)
uint32_t app_usbd_sof_timestamp_get(void)
{
    return m_last_frame;
}
#endif

ret_code_t app_usbd_init(app_usbd_config_t const * p_config)
{
    ASSERT(nrf_drv_clock_init_check());
    ret_code_t ret;

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
    ret = NRF_ATFIFO_INIT(m_event_queue);
    if (NRF_SUCCESS != ret)
    {
        return NRF_ERROR_INTERNAL;
    }
#endif

    /* This is called at the beginning to secure multiple calls to init function */
    ret = nrf_drv_usbd_init(app_usbd_event_handler);
    if (NRF_SUCCESS != ret)
    {
        return ret;
    }

    /* Clear the variables */
    m_sustate = SUSTATE_STOPPED;
    m_p_first_cinst = NULL;
    m_p_first_sof_cinst = NULL;
    memset(m_epin_conf , 0, sizeof(m_epin_conf ));
    memset(m_epout_conf, 0, sizeof(m_epout_conf));
    /* Save the new configuration */
    if (p_config == NULL)
    {
        m_current_conf = m_default_conf;
    }
    else
    {
        m_current_conf = *p_config;
    }

#if (!(APP_USBD_CONFIG_EVENT_QUEUE_ENABLE))
    if(m_current_conf.ev_handler == NULL)
    {
        m_current_conf.ev_handler = m_default_conf.ev_handler;
    }
#endif

#if APP_USBD_CONFIG_POWER_EVENTS_PROCESS
    ret = nrf_drv_power_init(NULL);
    if ((ret != NRF_SUCCESS) && (ret != NRF_ERROR_MODULE_ALREADY_INITIALIZED))
    {
        /* This should never happen */
        APP_ERROR_HANDLER(ret);
    }
#endif

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

    ret = class_event_handler(p_inst, (app_usbd_complex_evt_t const *)(&evt_data));
    if (NRF_SUCCESS != ret)
    {
        UNUSED_RETURN_VALUE(nrf_drv_usbd_uninit());
        return ret;
    }

    return NRF_SUCCESS;
}


ret_code_t app_usbd_uninit(void)
{
#if APP_USBD_CONFIG_POWER_EVENTS_PROCESS
    nrf_drv_power_usbevt_uninit();
#endif

    /* We get this error at very beginning but it would be used at the end of the function */
    const ret_code_t ret = nrf_drv_usbd_uninit();

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


#if APP_USBD_CONFIG_POWER_EVENTS_PROCESS
ret_code_t app_usbd_power_events_enable(void)
{
    if (!nrf_drv_usbd_is_initialized() || nrf_drv_usbd_is_enabled())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    ASSERT((!APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || (USBD_CONFIG_IRQ_PRIORITY == POWER_CONFIG_IRQ_PRIORITY));

    ret_code_t ret;
    static const nrf_drv_power_usbevt_config_t config =
    {
        .handler = app_usbd_power_event_handler
    };

    ret = nrf_drv_power_usbevt_init(&config);
    APP_ERROR_CHECK(ret);

    return NRF_SUCCESS;
}
#endif /* APP_USBD_CONFIG_POWER_EVENTS_PROCESS */


void app_usbd_enable(void)
{
    nrf_drv_usbd_enable();
}


void app_usbd_disable(void)
{
    ASSERT(!nrf_drv_usbd_is_started());
    nrf_drv_usbd_disable();
}


void app_usbd_start(void)
{
    ASSERT(nrf_drv_usbd_is_enabled());

    /* Check if interface numbers are in correct order */
    if (APP_USBD_CONFIG_LOG_ENABLED)
    {
        uint8_t next_iface = 0;
        for (app_usbd_class_inst_t const * * pp_inst = &m_p_first_cinst;
             (*pp_inst) != NULL;
             pp_inst = &(app_usbd_class_data_access(*pp_inst)->p_next))
        {
            uint8_t iface_idx = 0;
            app_usbd_class_iface_conf_t const * p_iface;
            while (NULL != (p_iface = app_usbd_class_iface_get(*pp_inst, iface_idx++)))
            {
                if (p_iface->number != next_iface)
                {
                    NRF_LOG_WARNING("Unexpected interface number, expected %d, got %d",
                                    next_iface,
                                    p_iface->number);
                }
                ++next_iface;
            }
        }
    }

    /* Power should be already enabled - wait just in case if user calls
     * app_usbd_start just after app_usbd_enable without waiting for the event. */
    while (!nrf_power_usbregstatus_outrdy_get())
    {
        /* Wait for the power but terminate the function if USBD power disappears */
        if (!nrf_power_usbregstatus_vbusdet_get())
            return;
    }

    static const app_usbd_evt_t evt_data = {
        .type = APP_USBD_EVT_START_REQ
    };
    app_usbd_event_add((app_usbd_internal_evt_t const * )&evt_data);
}


void app_usbd_stop(void)
{
    const app_usbd_evt_t evt_data = {
        .type = APP_USBD_EVT_STOP_REQ
    };
    app_usbd_event_add((app_usbd_internal_evt_t const * )&evt_data);
}

void app_usbd_suspend_req(void)
{
    const app_usbd_evt_t evt_data = {
       .type = APP_USBD_EVT_SUSPEND_REQ
   };
   app_usbd_event_add((app_usbd_internal_evt_t const * )&evt_data);
}

bool app_usbd_wakeup_req(void)
{
    ASSERT(app_usbd_class_rwu_enabled_check());
    if (!app_usbd_core_feature_state_get(APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP))
        return false;

    const app_usbd_evt_t evt_data = {
        .type = APP_USBD_EVT_WAKEUP_REQ
    };
    app_usbd_event_add((app_usbd_internal_evt_t const * )&evt_data);
    return true;
}

bool app_usbd_active_check(void)
{
    return (sustate_get() == SUSTATE_ACTIVE);
}

void app_usbd_event_execute(app_usbd_internal_evt_t const * const p_event)
{
    ASSERT(NULL != m_p_first_cinst);
    /* If no event queue is implemented, it has to be ensured that this function is never called
     * from the context higher than USB interrupt level
     * If queue is implemented it would be called always from Thread level
     * if the library is used correctly.
     * NOTE: Higher interrupt level -> lower priority value.
     */
    ASSERT(USBD_CONFIG_IRQ_PRIORITY <= current_int_priority_get());

    /* Note - there should never be situation that event is generated on disconnected endpoint */
    switch (p_event->type)
    {
        case APP_USBD_EVT_START_REQ:
        {
            static const app_usbd_evt_t evt_data = {
                .type = APP_USBD_EVT_STARTED
            };

            /* Send event to all classes */
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call((app_usbd_internal_evt_t const * )&evt_data));
            app_usbd_all_call((app_usbd_complex_evt_t const *)&evt_data);
            user_event_state_proc(APP_USBD_EVT_STARTED);

            nrf_drv_usbd_start((NULL != m_p_first_sof_cinst) || (m_current_conf.enable_sof) || (APP_USBD_PROVIDE_SOF_TIMESTAMP));
            app_usbd_all_iface_deselect();
            sustate_set(SUSTATE_STARTED);
            break;
        }
        case APP_USBD_EVT_STOP_REQ:
        {
            static const app_usbd_evt_t evt_data = {
                .type = APP_USBD_EVT_STOPPED
            };

            app_usbd_all_iface_deselect();
            nrf_drv_usbd_stop();
            sustate_set(SUSTATE_STOPPED);

            /* Send event to all classes */
            app_usbd_all_call((app_usbd_complex_evt_t const * )&evt_data);
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call((app_usbd_internal_evt_t const *)&evt_data));
            user_event_state_proc(APP_USBD_EVT_STOPPED);
            if (app_usbd_sustate_with_requested_hfclk(sustate_get()))
            {
                nrf_drv_clock_hfclk_release();
            }

            break;
        }
        case APP_USBD_EVT_HFCLK_READY:
        {
            switch(sustate_get())
            {
                case SUSTATE_RESUMING:
                {
                    sustate_set(SUSTATE_ACTIVE);
                    break;
                }
                case SUSTATE_WAKINGUP_WAITING_HFCLK_WREQ:
                {
                    sustate_set(SUSTATE_WAKINGUP_WAITING_WREQ);
                    break;
                }
                case SUSTATE_WAKINGUP_WAITING_HFCLK:
                {
                    sustate_set(SUSTATE_ACTIVE);
                    break;
                }
                default:
                    break; // Just ignore - it can happen in specyfic situation
            }
            break;
        }
        case APP_USBD_EVT_SUSPEND_REQ:
        {
            /* Suspend request can be only processed when we are in suspending state */
            if (SUSTATE_SUSPENDING == sustate_get())
            {
                if (nrf_drv_usbd_suspend())
                {
                    sustate_set(SUSTATE_SUSPEND);
                }
            }
            break;
        }
        case APP_USBD_EVT_WAKEUP_REQ:
        {
            /* Suspend temporary if no suspend function was called from the application.
             * This makes it possible to generate APP_USBD_EVT_DRV_WUREQ event from the driver */
            if (sustate_get() == SUSTATE_SUSPENDING)
            {
                if (nrf_drv_usbd_suspend())
                {
                    sustate_set(SUSTATE_SUSPEND);
                }
            }
            if (nrf_drv_usbd_wakeup_req())
            {
                sustate_set(SUSTATE_WAKINGUP_WAITING_HFCLK_WREQ);
            }
            break;
        }

        case APP_USBD_EVT_DRV_SOF:
        {
#if (APP_USBD_PROVIDE_SOF_TIMESTAMP) || defined(__SDK_DOXYGEN__)
            m_last_frame = p_event->drv_evt.data.sof.framecnt;
#endif
            user_event_state_proc(APP_USBD_EVT_DRV_SOF);

            app_usbd_class_inst_t const * p_inst = app_usbd_class_sof_first_get();
            while (NULL != p_inst)
            {
                ret_code_t r = class_event_handler(p_inst, (app_usbd_complex_evt_t const *)p_event);
                UNUSED_VARIABLE(r);
                p_inst = app_usbd_class_sof_next_get(p_inst);
            }
            break;
        }

        case APP_USBD_EVT_DRV_RESET:
        {
            app_usbd_all_iface_deselect();
            sustate_set(SUSTATE_ACTIVE);
            user_event_state_proc(APP_USBD_EVT_DRV_RESET);
            /* Processing core interface (connected only to EP0) and then all instances from the list */
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }
        case APP_USBD_EVT_DRV_RESUME:
        {
            sustate_set(SUSTATE_RESUMING);
            user_event_state_proc(APP_USBD_EVT_DRV_RESUME);
            /* Processing core interface (connected only to EP0) and then all instances from the list */
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }
        case APP_USBD_EVT_DRV_WUREQ:
        {
            static const app_usbd_evt_t evt_data = {
                .type = APP_USBD_EVT_DRV_RESUME
            };
            user_event_state_proc(APP_USBD_EVT_DRV_RESUME);
            /* Processing core interface (connected only to EP0) and then all instances from the list */
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call((app_usbd_internal_evt_t const *)&evt_data));
            app_usbd_all_call((app_usbd_complex_evt_t const *)&evt_data);

            switch(sustate_get())
            {
                case SUSTATE_WAKINGUP_WAITING_HFCLK_WREQ:
                    sustate_set(SUSTATE_WAKINGUP_WAITING_HFCLK);
                    break;
                case SUSTATE_WAKINGUP_WAITING_WREQ:
                    sustate_set(SUSTATE_ACTIVE);
                    break;
                default:
                {
                    // This should not happen - but try to recover by setting directly active state
                    NRF_LOG_WARNING("Unexpected state on WUREQ event (%u)", sustate_get());
                    sustate_set(SUSTATE_ACTIVE);
                }
            }
            break;
        }
        case APP_USBD_EVT_DRV_SUSPEND:
        {
            sustate_set(SUSTATE_SUSPENDING);

            user_event_state_proc(APP_USBD_EVT_DRV_SUSPEND);

            /* Processing all instances from the list and then core interface (connected only to EP0) */
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            break;
        }

        case APP_USBD_EVT_STATE_CHANGED:
        {
            user_event_state_proc(APP_USBD_EVT_STATE_CHANGED);
            /* Processing all instances from the list and then core interface (connected only to EP0) */
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }

        case APP_USBD_EVT_DRV_SETUP:
        {
            UNUSED_RETURN_VALUE(app_usbd_core_handler_call(p_event));
            break;
        }

        case APP_USBD_EVT_DRV_EPTRANSFER:
        {
            app_usbd_ep_conf_t const * p_ep_conf =
                    app_usbd_ep_conf_access(p_event->drv_evt.data.eptransfer.ep);
            ASSERT(NULL != p_ep_conf->p_cinst);
            ASSERT(NULL != p_ep_conf->event_handler);

            if (NRF_SUCCESS != p_ep_conf->event_handler(p_ep_conf->p_cinst,
                                                       (app_usbd_complex_evt_t const *)p_event))
            {
                /* If error returned, every bulk/interrupt endpoint would be stalled */
                if (!(0 == NRF_USBD_EP_NR_GET(p_event->drv_evt.data.eptransfer.ep) ||
                   NRF_USBD_EPISO_CHECK(p_event->drv_evt.data.eptransfer.ep)))
                {
                    nrf_drv_usbd_ep_stall(p_event->drv_evt.data.eptransfer.ep);
                }
            }
            break;
        }
#if APP_USBD_CONFIG_POWER_EVENTS_PROCESS
        case APP_USBD_EVT_POWER_DETECTED:
        {
            user_event_state_proc(APP_USBD_EVT_POWER_DETECTED);
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }
        case APP_USBD_EVT_POWER_REMOVED:
        {
            user_event_state_proc(APP_USBD_EVT_POWER_REMOVED);
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }
        case APP_USBD_EVT_POWER_READY:
        {
            user_event_state_proc(APP_USBD_EVT_POWER_READY);
            app_usbd_all_call((app_usbd_complex_evt_t const *)p_event);
            break;
        }
#endif
        default:
            ASSERT(0);
            break;
    }
}


#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
bool app_usbd_event_queue_process(void)
{
#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
    app_usbd_internal_evt_t sof_event = {
        .app_evt.type = APP_USBD_EVT_DRV_SOF
    };
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
    static nrf_atfifo_item_get_t cx;
    static app_usbd_internal_queue_evt_t * p_event_item = NULL;
    if (NULL == p_event_item)
    {
        p_event_item = nrf_atfifo_item_get(m_event_queue, &cx);
    }

    if (NULL != p_event_item)
    {

#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
        if (p_event_item->sof_cnt > 0)
        {
            if (p_event_item->start_frame > USBD_FRAMECNTR_FRAMECNTR_Msk)
            {
                p_event_item->start_frame = 0;
            }
            sof_event.drv_evt.data.sof.framecnt = (p_event_item->start_frame)++;
            --(p_event_item->sof_cnt);
            app_usbd_event_execute(&sof_event);
            return true;
        }
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)

        app_usbd_event_execute(&(p_event_item->evt));
        UNUSED_RETURN_VALUE(nrf_atfifo_item_free(m_event_queue, &cx));
        p_event_item = NULL;
        return true;
    }
#if (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
    else if (m_sof_events_cnt > 0)
    {
        CRITICAL_REGION_ENTER();
        if (m_event_frame > USBD_FRAMECNTR_FRAMECNTR_Msk)
        {
            m_event_frame = 0;
        }
        sof_event.drv_evt.data.sof.framecnt = m_event_frame++;
        UNUSED_RETURN_VALUE(nrf_atomic_u32_sub_hs(&m_sof_events_cnt, 1));
        CRITICAL_REGION_EXIT();
        app_usbd_event_execute(&sof_event);
        return true;
    }
#endif // (APP_USBD_CONFIG_SOF_HANDLING_MODE == APP_USBD_SOF_HANDLING_COMPRESS_QUEUE)
    else
    {
        return false;
    }
}
#endif


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


ret_code_t app_usbd_class_rwu_register(app_usbd_class_inst_t const * const p_inst)
{
    ASSERT(p_inst != NULL);
    ++m_rwu_registered_counter;
    /*Overflow check*/
    ASSERT(m_rwu_registered_counter != 0);

    return NRF_SUCCESS;
}


ret_code_t app_usbd_class_rwu_unregister(app_usbd_class_inst_t const * const p_inst)
{
    ASSERT(p_inst != NULL);
    /* Usage validation. If counter is 0 unregister is not possible.*/
    ASSERT(m_rwu_registered_counter != 0);
    --m_rwu_registered_counter;

    return NRF_SUCCESS;
}

bool app_usbd_class_rwu_enabled_check(void)
{
    return (m_rwu_registered_counter != 0);
}

ret_code_t app_usbd_interface_ep_reset(app_usbd_class_inst_t const * const p_cinst,
                                       uint8_t iface)
{
    uint8_t iface_count = app_usbd_class_iface_count_get(p_cinst);

    app_usbd_class_iface_conf_t const * p_iface = NULL;
    for (uint8_t j = 0; j < iface_count; ++j)
    {
        p_iface = app_usbd_class_iface_get(p_cinst, j);
        if (app_usbd_class_iface_number_get(p_iface) == iface)
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

        if (!NRF_USBD_EPISO_CHECK(p_ep->address))
        {
            nrf_drv_usbd_ep_dtoggle_clear(p_ep->address);
            nrf_drv_usbd_ep_stall_clear(p_ep->address);
        }

    }

    return NRF_SUCCESS;
}

void app_usbd_ep_enable(nrf_drv_usbd_ep_t ep)
{
    if (!NRF_USBD_EPISO_CHECK(ep))
    {
        nrf_drv_usbd_ep_dtoggle_clear(ep);
        nrf_drv_usbd_ep_stall_clear(ep);
    }
    nrf_drv_usbd_ep_enable(ep);
}

void app_usbd_ep_disable(nrf_drv_usbd_ep_t ep)
{
    nrf_drv_usbd_ep_disable(ep);
}


app_usbd_class_inst_t const * app_usbd_class_first_get(void)
{
    return m_p_first_cinst;
}

app_usbd_class_inst_t const * app_usbd_class_sof_first_get(void)
{
    return m_p_first_sof_cinst;
}

app_usbd_class_inst_t const * app_usbd_iface_find(uint8_t iface, uint8_t * p_iface_idx)
{
    app_usbd_class_inst_t const * p_inst = app_usbd_class_first_get();
    while (p_inst != NULL)
    {
        uint8_t iface_count = app_usbd_class_iface_count_get(p_inst);
        /* Iterate over interfaces */
        for (uint8_t i = 0; i < iface_count; ++i)
        {
            app_usbd_class_iface_conf_t const * p_iface;
            p_iface = app_usbd_class_iface_get(p_inst, i);
            if (app_usbd_class_iface_number_get(p_iface) == iface)
            {
                if (p_iface_idx != NULL)
                {
                    (*p_iface_idx) = i;
                }
                return p_inst;
            }
        }
        p_inst = app_usbd_class_next_get(p_inst);
    }
    return NULL;
}

ret_code_t app_usbd_iface_call(
    app_usbd_class_inst_t const * const p_class_inst,
    uint8_t iface_idx,
    app_usbd_complex_evt_t const * const p_event)
{
    UNUSED_PARAMETER(iface_idx);
    return class_event_handler(p_class_inst, p_event);
}

ret_code_t app_usbd_ep_call(nrf_drv_usbd_ep_t ep, app_usbd_complex_evt_t const * const p_event)
{
    if (NRF_USBD_EP_VALIDATE(ep))
    {
        app_usbd_class_inst_t const * p_inst = app_usbd_ep_conf_access(ep)->p_cinst;
        if (p_inst != NULL)
        {
           return class_event_handler(p_inst, p_event);
        }
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

ret_code_t app_usbd_ep_transfer(
    nrf_drv_usbd_ep_t                     ep,
    nrf_drv_usbd_transfer_t const * const p_transfer)
{
    if (!nrf_drv_usbd_ep_enable_check(ep))
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (m_sustate != SUSTATE_ACTIVE)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return nrf_drv_usbd_ep_transfer(ep, p_transfer);
}

ret_code_t app_usbd_ep_handled_transfer(
    nrf_drv_usbd_ep_t                         ep,
    nrf_drv_usbd_handler_desc_t const * const p_handler)
{
    if (!nrf_drv_usbd_ep_enable_check(ep))
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (m_sustate != SUSTATE_ACTIVE)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return nrf_drv_usbd_ep_handled_transfer(ep, p_handler);
}

ret_code_t app_usbd_iface_select(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx,
    uint8_t                             alternate)
{
    ret_code_t ret = NRF_ERROR_NOT_SUPPORTED;

    if (p_inst->p_class_methods->iface_select != NULL)
    {
        ret = p_inst->p_class_methods->iface_select(p_inst, iface_idx, alternate);
    }

    if(ret == NRF_ERROR_NOT_SUPPORTED)
    {
        ret = default_iface_select(p_inst, iface_idx, alternate);
    }
    return ret;
}

void app_usbd_iface_deselect(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx)
{
    if (p_inst->p_class_methods->iface_deselect != NULL)
    {
        p_inst->p_class_methods->iface_deselect(p_inst, iface_idx);
    }
    default_iface_deselect(p_inst, iface_idx);
}

uint8_t app_usbd_iface_selection_get(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx)
{
    uint8_t alt = 0;
    if (p_inst->p_class_methods->iface_selection_get != NULL)
    {
        alt = p_inst->p_class_methods->iface_selection_get(p_inst, iface_idx);
    }
    return alt;
}

void app_usbd_all_iface_select_0(void)
{
    app_usbd_class_inst_t const * p_inst = app_usbd_class_first_get();
    while (p_inst != NULL)
    {
        uint8_t iface_count = app_usbd_class_iface_count_get(p_inst);
        for (uint8_t i = 0; i < iface_count; ++i)
        {
            ret_code_t ret;
            ret = app_usbd_iface_select(p_inst, i, 0);
            ASSERT(ret == NRF_SUCCESS);
            UNUSED_VARIABLE(ret);
        }
        p_inst = app_usbd_class_next_get(p_inst);
    }
}

void app_usbd_all_iface_deselect(void)
{
    app_usbd_class_inst_t const * p_inst = app_usbd_class_first_get();
    while (p_inst != NULL)
    {
        uint8_t iface_count = app_usbd_class_iface_count_get(p_inst);
        for (uint8_t i = 0; i < iface_count; ++i)
        {
            app_usbd_iface_deselect(p_inst, i);
        }
        p_inst = app_usbd_class_next_get(p_inst);
    }
}

#endif //NRF_MODULE_ENABLED(APP_USBD)
