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

#ifndef APP_USBD_H__
#define APP_USBD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_drv_usbd.h"
#include "app_usbd_types.h"
#include "app_usbd_class_base.h"

/**
 * @defgroup app_usbd USB Device high level library
 * @ingroup app_common
 *
 * @brief @tagAPI52840 Module for easy support for any USB device configuration.
 *
 * This module manages class instances that would create the USB device,
 * manages endpoints and interfaces transactions.
 * @{
 */

/**
 * @brief Configuration passed to @ref app_usbd_init.
 */
typedef struct {
    /**
     * @brief User defined event handler.
     *
     * @param event Event type.
     */
    void (*ev_handler)(app_usbd_event_type_t event);
} app_usbd_config_t;

/**
 * @brief USB library initialization.
 *
 * Call this function before any configuration or class attachment.
 * USBD peripheral would be ready to accept commands, and library would be ready,
 * but it would not be connected to the bus.
 * Call @ref app_usbd_enable to enable USBD communication with the host.
 *
 * @param p_config  Configuration. NULL pointer might be passed here and default
 *                  configuration will be applied then.
 */
ret_code_t app_usbd_init(app_usbd_config_t const * p_config);

/**
 * @brief USB library un-initialization
 *
 * @note Currently not supported
 */
ret_code_t app_usbd_uninit(void);

/**
 * @brief Enable USBD
 *
 * USBD is enabled and starts requiring High Frequency Clock and power regulator.
 */
void app_usbd_enable(void);

/**
 * @brief Disable USBD
 *
 * Disabled USDB peripheral cannot be accessed but also stops requesting
 * High Frequency clock and releases power regulator.
 */
void app_usbd_disable(void);

/**
 * @brief Start USB to work
 *
 * Start library to work.
 * Enable interrupts.
 * Enable USB pull-ups.
 * After calling this function USB device is visible to a HOST.
 */
void app_usbd_start(void);

/**
 * @brief Stop USB to work
 *
 * This function disables interrupts and USB pull-ups.
 * The peripheral itself is left enabled so it can be programmed,
 * but it a HOST sees it as a peripheral disconnection.
 */
void app_usbd_stop(void);

/**
 * @brief Add class instance
 *
 * This function connects given instance into internal class instance chain and
 * into all required endpoints.
 * The instance event handler would be connected into endpoint by default,
 * but this can be overwritten by @ref app_usbd_ep_handler_set.
 *
 * After successful attachment @ref APP_USBD_EVT_INST_APPEND would be passed to class instance.
 *
 * @note This function can only be called after USBD library is initialized but still disabled.
 *       Assertion would be generated otherwise.
 *
 * @param[in,out] p_cinst Instance to connect. Chain data would be written into writable instance data.
 */
ret_code_t app_usbd_class_append(app_usbd_class_inst_t const * p_cinst);

/**
 * @brief Remove class instance
 *
 * Instance is removed from instance chain.
 * Instance and event handlers are removed also from endpoints.
 * Endpoints used by by the class instance are left disabled.
 *
 * @note This function can only be called after USBD library is initialized but still disabled.
 *       Assertion would be generated otherwise.
 *
 * @param p_cinst Instance pointer to remove.
 *
 * @retval NRF_SUCCESS         Instance successfully removed.
 * @retval NRF_ERROR_NOT_FOUND Instance not found in the instance chain.
 */
ret_code_t app_usbd_class_remove(app_usbd_class_inst_t const * p_cinst);

/**
 * @brief Remove all class instances
 *
 * This function basically calls @ref app_usbd_class_remove
 * on instances chain as long as there is any element left.
 *
 * @note This function can only be called after USBD library is initialized but still disabled.
 *       Assertion would be generated otherwise.
 *
 * @sa app_usbd_class_remove
 *
 * @return Is should always return @ref NRF_SUCCESS.
 *         Any error value returned would mean there is an error inside the library.
 */
ret_code_t app_usbd_class_remove_all(void);

/**
 * @brief Change endpoint handler
 *
 * This function may be called for the endpoint only if the class instance is
 * already properly attached by the @ref app_usbd_class_append function.
 *
 * The endpoint event handler function can be only overwritten by the class instance
 * that was connected into the endpoint.
 *
 * @note This function can only be called after USBD library is initialized but still disabled.
 *       Assertion would be generated otherwise.
 *
 * @param[in] p_cinst Instance of a class that wish to set new event handler.
 *                    It has to match currently configured instance for the selected endpoint.
 *                    In other situation error would be returned.
 * @param[in] ep      Endpoint address to configure.
 * @param[in] handler Event handler function to set.
 *
 * @retval NRF_SUCCESS             New handler successfully set
 * @retval NRF_ERROR_INVALID_PARAM p_cinst is not the same as currently set for the endpoint
 */
ret_code_t app_usbd_ep_handler_set(app_usbd_class_inst_t const * p_cinst,
                                   nrf_drv_usbd_ep_t             ep,
                                   app_usbd_ep_event_handler_t   handler);

/**
 * @brief Register class instance as the one that requires SOF events
 *
 * This function should be called in reaction on APP_USBD_EVT_INST_APPEND event.
 * Connect the class instance to the list of instances that requires SOF processing.
 * If none of the appended instances requires SOF event - it is disabled.
 *
 * @param p_cinst Instance that requires SOF event.
 *
 * @retval NRF_SUCCESS Instance linked into SOF processing list.
 *
 * @sa app_usbd_class_sof_unregister
 */
ret_code_t app_usbd_class_sof_register(app_usbd_class_inst_t const * p_cinst);

/**
 * @brief Unregister class instance from SOF processing instances list
 *
 * Every class that calls @ref app_usbd_class_sof_register have to call also unregistering function
 * in reaction to @ref APP_USBD_EVT_INST_REMOVE event.
 *
 * @param p_cinst Instance to be unregistered from SOF event processing list.
 *
 * @retval NRF_SUCCESS         Instance linked into SOF processing list.
 * @retval NRF_ERROR_NOT_FOUND Instance not found in the SOF processing list.
 *
 * @sa app_usbd_class_sof_register
 */
ret_code_t app_usbd_class_sof_unregister(app_usbd_class_inst_t const * p_cinst);

/**
 * @brief Function finds a given descriptor type in class descriptors payload
 *
 * @param[in] p_cinst     Instance of a class
 * @param[in] desc_type   Descriptor type (@ref APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR)
 * @param[in] desc_index  Descriptor index (@ref APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR)
 * @param[out] p_desc_len Descriptor length
 *
 * @return Address of the descriptor (NULL if not found)
 * */
const void * app_usbd_class_descriptor_find(app_usbd_class_inst_t const * const p_cinst,
                                            uint8_t  desc_type,
                                            uint8_t  desc_index,
                                            size_t * p_desc_len);

/**
 * @brief Standard interface request handle
 *
 * @param[in] p_setup_ev Setup event
 *
 * @return Standard error code
 * */
ret_code_t app_usbd_interface_std_req_handle(app_usbd_setup_evt_t  const * p_setup_ev);

/**
 * @brief Standard endpoint request handle
 *
 * @param[in] p_setup_ev Setup event
 *
 * @return Standard error code
 * */
ret_code_t app_usbd_endpoint_std_req_handle(app_usbd_setup_evt_t const * p_setup_ev);


/**
 * @brief Standard interface set request handle
 *
 * @param[in] p_cinst    Instance of a class
 * @param[in] p_setup_ev Setup event
 *
 * @return Standard error code
 * */
ret_code_t app_usbd_req_std_set_interface(app_usbd_class_inst_t const * const p_cinst,
                                          app_usbd_setup_evt_t  const * const p_setup_ev);

/**
 * @name Iterate through classes lists
 *
 * Functions that helps to iterate through internally chained classes.
 * @{
 */
    /**
     * @brief Get first class instance in the list
     *
     * Get first instance from the list of active class instances.
     * That instance may be used then in @ref app_usbd_class_next_get function.
     *
     * @return First instance in the list or NULL if there are no instances available.
     */
    app_usbd_class_inst_t const * app_usbd_class_first_get(void);

    /**
     * @brief Get next instance in the list
     *
     * Get the next instance from the list of active instances.
     * Used to iterate through all instances.
     *
     * @param[in] p_cinst The current instance from with next one is required.
     *
     * @return Next instance to the given one or NULL if there is no more instances in the list.
     */
    static inline app_usbd_class_inst_t const * app_usbd_class_next_get(
            app_usbd_class_inst_t const * const p_cinst)
    {
        ASSERT(NULL != p_cinst);
        return app_usbd_class_data_access(p_cinst)->p_next;
    }

    /**
     * @brief Get first instance in SOF list
     *
     * Start iteration through the list of instances that requires SOF event processing.
     *
     * @return First instance in the list or NULL if the list is empty
     *
     * @sa app_usbd_class_first_get
     */
    app_usbd_class_inst_t const * app_usbd_class_sof_first_get(void);

    /**
     * @brief Get next instance in the SOF list
     *
     * Get the next instance from the list of instances requiring SOF event processing.
     * Used to iterate through all SOF instances.
     *
     * @param p_cinst The current instance from with next one is required.
     *
     * @return Next instance to the given one or NULL if there is no more instances in the list.
     */
    static inline app_usbd_class_inst_t const * app_usbd_class_sof_next_get(
            app_usbd_class_inst_t const * const p_cinst)
    {
        ASSERT(NULL != p_cinst);
        return app_usbd_class_data_access(p_cinst)->p_sof_next;
    }
/** @} */

/**
 * @name Communicate with interfaces, endpoints and instances inside usbd library
 *
 * @{
 */

    /**
     * @brief Call interface event handler
     *
     * Call event handler for selected interface.
     * @param[in] iface   Target interface number
     * @param[in] p_event Event structure to send
     *
     * @return Operation status
     */
    ret_code_t app_usbd_iface_call(uint8_t iface, app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Call endpoint event handler
     *
     * Call event handler for the selected endpoint.
     * @param[in] ep      Endpoint number
     * @param[in] p_event Event structure to send
     *
     * @return Operation status
     */
    ret_code_t app_usbd_ep_call(nrf_drv_usbd_ep_t ep, app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Auxiliary function that process event by every instance in the list
     *
     * This function ignores the result of called handler.
     *
     * @param p_event Event to pass to every instance
     */
    void app_usbd_all_call(app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Call interface event handlers and stop when served
     *
     * Call event handlers from instances as long as we get result different than @ref NRF_ERROR_NOT_SUPPORTED
     * @param[in] p_event Event structure to send
     *
     * @return Operation status or @ref NRF_ERROR_NOT_SUPPORTED if none of instances in the list can support given event.
     */
    ret_code_t app_usbd_all_until_served_call(app_usbd_complex_evt_t const * const p_event);
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_H__ */
