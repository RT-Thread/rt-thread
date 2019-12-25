/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

#include "nrf_drv_usbd.h"
#include "app_usbd_types.h"
#include "app_usbd_class_base.h"

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Highest value of Frame Number in SOF packets.
 */
#define APP_USBD_SOF_MAX 2047

/**
 * @brief True if SOF timestamping is really provided.
 *
 * SOF timestamping is really provided if it was requested and if the logger is enabled.
 */
#if ((APP_USBD_CONFIG_SOF_TIMESTAMP_PROVIDE) && (NRF_LOG_ENABLED))
#define APP_USBD_PROVIDE_SOF_TIMESTAMP 1
#else
#define APP_USBD_PROVIDE_SOF_TIMESTAMP 0
#endif

/**
 * @brief SOF event handling modes.
 */
#define APP_USBD_SOF_HANDLING_NORMAL_QUEUE    0 //!< Push SOF events into event queue.
#define APP_USBD_SOF_HANDLING_COMPRESS_QUEUE  1 //!< Compress SOF events.
#define APP_USBD_SOF_HANDLING_INTERRUPT       2 //!< Handle SOF events in interrupt.

/**
 * @brief Configuration passed to @ref app_usbd_init.
 */
typedef struct {
#if (!(APP_USBD_CONFIG_EVENT_QUEUE_ENABLE)) || defined(__SDK_DOXYGEN__)
    /**
     * @brief User defined event handler.
     *
     * This function is called on every event from the interrupt.
     * It is prepared for external user function that would queue events to be processed
     * from the main context.
     * It should be used with operating systems with its own implementation of the queue.
     *
     * @param p_event The event structure pointer.
     *
     * @note This field is available only when USB internal queue is disabled
     *       (see @ref APP_USBD_CONFIG_EVENT_QUEUE_ENABLE).
     */
    void (*ev_handler)(app_usbd_internal_evt_t const * const p_event);
#endif

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
    /**
     * @brief User defined event handler.
     *
     * This function is called on every event from the interrupt.
     *
     * @param p_event The event structure pointer.
     * @param queued  The event is visible in the queue.
     *                If queue conflict is detected the event might not be accessible inside queue
     *                until all write operations finish.
     *                See @ref nrf_atfifo for more details.
     *
     * @note This field is available only when USBD internal queue is configured
     *       (see @ref APP_USBD_CONFIG_EVENT_QUEUE_ENABLE).
     *
     * @note If is set to NULL no event would be called from interrupt.
     * @note This function is called before event is processed.
     *       It means that if the event type is @ref APP_USBD_EVT_DRV_SETUP,
     *       there would not be setup field present in the event structure.
     */
    void (*ev_isr_handler)(app_usbd_internal_evt_t const * const p_event, bool queued);
#endif

    /**
     * @brief User defined event processor
     *
     * This function is called while state event is processed.
     *
     * * @note This field is available only when USBD internal queue is configured
     *       (see @ref APP_USBD_CONFIG_EVENT_QUEUE_ENABLE).
     *
     * @param event Event type.
     *              Only following events are sent into this function:
     *              - APP_USBD_EVT_DRV_SOF
     *              - APP_USBD_EVT_DRV_RESET  - Note that it also exits suspend
     *              - APP_USBD_EVT_DRV_SUSPEND
     *              - APP_USBD_EVT_DRV_RESUME - It is also generated when remote wakeup is generated
     *              - APP_USBD_EVT_START
     *              - APP_USBD_EVT_STOP
     *              - APP_USBD_EVT_STATE_CHANGED
     *              - APP_USBD_EVT_POWER_DETECTED
     *              - APP_USBD_EVT_POWER_REMOVED
     *              - APP_USBD_EVT_POWER_READY
     */
    void (*ev_state_proc)(app_usbd_event_type_t event);

    /**
     * @brief SOF processing required by the user event processing.
     *
     * This flag would enable SOF processing for the user events regardless of the fact if any
     * of the implemented class requires SOF event.
     *
     * @note SOF event would be enabled anyway if any of the appended class requires SOF processing.
     */
    bool enable_sof;
} app_usbd_config_t;


#if (APP_USBD_PROVIDE_SOF_TIMESTAMP) || defined(__SDK_DOXYGEN__)
/**
 * @brief Timestamp function for the logger.
 *
 * @return Current frame number taken directly from the last processed SOF.
 */
uint32_t app_usbd_sof_timestamp_get(void);
#endif

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
 * @brief USB library un-initialization.
 *
 * @note Currently not supported.
 */
ret_code_t app_usbd_uninit(void);

#if (APP_USBD_CONFIG_POWER_EVENTS_PROCESS) || defined(__SDK_DOXYGEN__)
/**
 * @brief Function to start USB related power events processing.
 *
 * This function should be called after @ref app_usbd_init and after all the
 * required classes were appended (@ref app_usbd_class_append).
 *
 * @retval NRF_SUCCESS             Power events successfully initialized.
 * @retval NRF_ERROR_INVALID_STATE The state of the driver does not allow to enable
 *                                 the power events processing.
 */
ret_code_t app_usbd_power_events_enable(void);
#endif

/**
 * @brief Enable USBD.
 *
 * USBD is enabled.
 * Since now the high frequency clock may be requested when USB RESET would be detected.
 */
void app_usbd_enable(void);

/**
 * @brief Disable USBD.
 *
 * Disabled USDB peripheral cannot be accessed but also stops requesting
 * High Frequency clock and releases power regulator.
 *
 * @note This function cannot be called when USB is started. Stop it first.
 */
void app_usbd_disable(void);

/**
 * @brief Request USBD to start.
 *
 * The function sends start request to the event queue.
 * If the queue is enabled (@ref APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) it would be processed
 * when the queue is processed.
 * If queue is disabled it would be processed immediately inside this function.
 * It means that if queue is disabled this function cannot be called from interrupt with priority
 * higher than USB interrupt.
 *
 * When start is processed it would:
 * 1. Start library.
 * 2. Enable interrupts.
 * 3. Enable USB pull-ups.
 *
 * @note
 * In some specific circumstances the library can be left not started and this function would
 * silently exit.
 * This may happen if some glitches appears on USB power line or if the plug was disconnected before
 * whole starting process finishes.
 * User would get the event from POWER peripheral then.
 * Also no @ref APP_USBD_EVT_STARTED event would be generated to the classes and user event handler.
 * For the safe code it is recommended to wait for @ref APP_USBD_EVT_STARTED event if anything
 * has to be initialized after USB driver is started (just before enabling the interrupts).
 * If library is properly started the @ref APP_USBD_EVT_STARTED event passed to the user handler
 * from this function body.
 */
void app_usbd_start(void);

/**
 * @brief Stop USB.
 *
 * The function sends stop request to the event queue.
 * If the queue is enabled (@ref APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) it would be processed
 * when the queue is processed.
 * If queue is disabled it would be processed immediately inside this function.
 * It means that if queue is disabled this function cannot be called from interrupt with priority
 * higher than USB interrupt.
 *
 * When the event is processed interrupts and USB pull-ups are disabled.
 * The peripheral itself is left enabled so it can be programmed,
 * but a HOST sees it as a peripheral disconnection.
 *
 * @note
 * If the library is not started when this function is called it exits silently - also
 * no @ref APP_USBD_EVT_STOPPED is generated.
 */
void app_usbd_stop(void);

/**
 * @brief Request library to suspend.
 *
 * This function send suspend request to the event queue.
 *
 * @note This function should only be called after @ref APP_USBD_EVT_DRV_SUSPEND os received.
 *       Internal suspend request processing would give no effect if the bus is not in suspend state.
 */
void app_usbd_suspend_req(void);

/**
 * @brief Request library to wake-up.
 *
 * This function send wakeup request to the event queue.
 *
 * @note Calling this function does not mean that peripheral is active - the wakeup request is sent
 *       into message queue and needs to be processed.
 *
 * @retval true  Wakeup generation has been started.
 * @retval false No wakeup would be generated becouse it is disabled by the host.
 */
bool app_usbd_wakeup_req(void);

/**
 * @brief Get information whether there is an active connection.
 *
 * Function to check if the communication with the bus is possible.
 *
 * @retval true  The bus is active.
 * @retval false There is no connection or bus is suspended.
 */
bool app_usbd_active_check(void);

/**
 * @brief USBD event processor.
 *
 * Function to be called on each event to be processed by the library.
 */
void app_usbd_event_execute(app_usbd_internal_evt_t const * const p_event);


#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE) || defined(__SDK_DOXYGEN__)
/**
 * @brief Function that process events from the queue.
 *
 * @note This function calls @ref app_usbd_event_execute internally.
 *
 * @retval true  Event was processed.
 * @retval false The event queue is empty.
 */
bool app_usbd_event_queue_process(void);
#endif

/**
 * @brief Add class instance.
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
 *
 * @retval NRF_SUCCESS         Instance successfully added.
 * @retval NRF_ERROR_BUSY      Endpoint(s) not available.
 */
ret_code_t app_usbd_class_append(app_usbd_class_inst_t const * p_cinst);

/**
 * @brief Remove class instance.
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
 * @brief Remove all class instances.
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
 * @brief Change endpoint handler.
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
 * @brief Register class instance as the one that requires SOF events.
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
 * @brief Unregister class instance from SOF processing instances list.
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
 * @brief Register class instance as the one that requires SOF events in interrupt.
 *
 * This function should be called in reaction on APP_USBD_EVT_INST_APPEND event.
 * Connect the class instance to the list of instances that requires SOF processing.
 * If none of the appended instances requires SOF event - it is disabled.
 *
 * @param p_cinst Instance that requires SOF event.
 * @param handler Handler to SOF event
 *
 * @retval NRF_SUCCESS Instance linked into SOF processing list.
 *
 * @sa app_usbd_class_sof_interrupt_unregister
 */
ret_code_t app_usbd_class_sof_interrupt_register(app_usbd_class_inst_t const * p_cinst,
                                                 app_usbd_sof_interrupt_handler_t handler);

/**
 * @brief Unregister class instance from SOF processing in interrupt instances list.
 *
 * Every class that calls @ref app_usbd_class_sof_interrupt_register have to call 
 * also unregistering function in reaction to @ref APP_USBD_EVT_INST_REMOVE event.
 *
 * @param p_cinst Instance to be unregistered from SOF processing in interrupt list.
 *
 * @retval NRF_SUCCESS         Instance linked into SOF processing in interrupt list.
 * @retval NRF_ERROR_NOT_FOUND Instance not found in the SOF processing in interrupt list.
 *
 * @sa app_usbd_class_sof_interrupt_register
 */
ret_code_t app_usbd_class_sof_interrupt_unregister(app_usbd_class_inst_t const * p_cinst);


/**
 * @brief Register class on remote wake-up feature.
 *
 * @param[in] p_inst Instance of the class.
 *
 * @retval NRF_SUCCESS Instance that requires remote wake-up registered.
 */
ret_code_t app_usbd_class_rwu_register(app_usbd_class_inst_t const * const p_inst);

/**
 * @brief Unregister class from remote wake-up feature.
 *
 * @param[in] p_inst Instance of the class.
 *
 * @retval NRF_SUCCESS Instance that requires remote wake-up removed.
 */
ret_code_t app_usbd_class_rwu_unregister(app_usbd_class_inst_t const * const p_inst);

/**
 * @brief Check if there is any class with remote wakeup.
 *
 * The function checks internal registered class with remote wakeup counter.
 *
 * @sa app_usbd_class_rwu_register, app_usbd_class_rwu_unregister
 *
 * @retval true  The remote wakeup functionality is required by some class instance.
 * @retval false There is no class instance that requires wakeup functionality.
 */
bool app_usbd_class_rwu_enabled_check(void);

/**
 * @brief Find a specified descriptor.
 *
 * @param[in] p_cinst       Class instance.
 * @param[in] desc_type     Descriptor type @ref app_usbd_descriptor_t
 * @param[in] desc_index    Descriptor index.
 * @param[out] p_desc       Pointer to escriptor.
 * @param[out] p_desc_len   Length of descriptor.
 *
 * @return Standard error code @ref ret_code_t
 * @retval NRF_SUCCESS          Descriptor successfully found.
 * @retval NRF_ERROR_NOT_FOUND  Descriptor not found.
 * */
ret_code_t app_usbd_class_descriptor_find(app_usbd_class_inst_t const * const p_cinst,
                                          uint8_t                             desc_type,
                                          uint8_t                             desc_index,
                                          uint8_t                           * p_desc,
                                          size_t                            * p_desc_len);

/**
 * @brief Standard set interface request handle.
 *
 * This function should be called when processing SET_INTERFACE request.
 *
 * @param[in] p_cinst  Instance of a class.
 * @param[in] iface    Interface number.
 *
 * @return Standard error code.
 *
 * @note Selected interface to reset has to be part of given class.
 * */
ret_code_t app_usbd_interface_ep_reset(app_usbd_class_inst_t const * const p_cinst,
                                       uint8_t iface);


/**
 * @brief Enable selected endpoint.
 *
 * Selected endpoint is enabled and cleared.
 *
 * @param ep Endpoint number.
 */
void app_usbd_ep_enable(nrf_drv_usbd_ep_t ep);

/**
 * @brief Disable selected endpoint.
 *
 * @param ep Endpoint number.
 */
void app_usbd_ep_disable(nrf_drv_usbd_ep_t ep);

/**
 * @name Iterate through classes lists
 *
 * Functions that helps to iterate through internally chained classes.
 * @{
 */
    /**
     * @brief Get first class instance in the list.
     *
     * Get first instance from the list of active class instances.
     * That instance may be used then in @ref app_usbd_class_next_get function.
     *
     * @return First instance in the list or NULL if there are no instances available.
     */
    app_usbd_class_inst_t const * app_usbd_class_first_get(void);

    /**
     * @brief Get next instance in the list.
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
     * @brief Get first instance in SOF list.
     *
     * Start iteration through the list of instances that require SOF event processing.
     *
     * @return First instance in the list or NULL if the list is empty.
     *
     * @sa app_usbd_class_first_get
     */
    app_usbd_class_inst_t const * app_usbd_class_sof_first_get(void);

    /**
     * @brief Get next instance in the SOF list.
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

    /**
     * @brief Get first instance in SOF interrupt list.
     *
     * Start iteration through the list of instances that require SOF processing in interrupt.
     *
     * @return First instance in the list or NULL if the list is empty.
     *
     * @sa app_usbd_class_first_get
     */
    app_usbd_class_inst_t const * app_usbd_class_sof_interrupt_first_get(void);

    /**
     * @brief Get next instance in the SOF interrupt list.
     *
     * Get the next instance from the list of instances requiring SOF processing in interrupt.
     * Used to iterate through all SOF instances that have SOF handlers.
     *
     * @param p_cinst The current instance from with next one is required.
     *
     * @return Next instance to the given one or NULL if there is no more instances in the list.
     */
    static inline app_usbd_class_inst_t const * app_usbd_class_sof_interrupt_next_get(
            app_usbd_class_inst_t const * const p_cinst)
    {
        ASSERT(NULL != p_cinst);
        return app_usbd_class_data_access(p_cinst)->p_sof_next;
    }
/** @} */

/**
 * @brief Search for selected interface.
 *
 * Function searches for the given interface number and returns the class that contains it.
 * Optionally it can return interface index inside class instance.
 *
 * @param[in]  iface       Interface number.
 * @param[out] p_iface_idx Pointer to a variable that would hold interface index inside returned
 *                         class instance.
 *
 * @return Pointer to the class structure that cointain given interface or NULL if not found.
 */
app_usbd_class_inst_t const * app_usbd_iface_find(uint8_t iface, uint8_t * p_iface_idx);


/**
 * @name Communicate with interfaces, endpoints and instances inside usbd library
 *
 * @{
 */

    /**
     * @brief Call interface event handler.
     *
     * Call event handler for selected interface.
     * @param[in,out] p_class_inst Class instance that holds selected interface.
     * @param[in]     iface_idx    Index of the interface in class structure.
     * @param[in]     p_event      Event structure to be processed.
     *
     * @return Operation status.
     */
    ret_code_t app_usbd_iface_call(
        app_usbd_class_inst_t const * const p_class_inst,
        uint8_t iface_idx,
        app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Call endpoint event handler.
     *
     * Call event handler for the selected endpoint.
     * @param[in] ep      Endpoint number.
     * @param[in] p_event Event structure to send.
     *
     * @return Operation status.
     */
    ret_code_t app_usbd_ep_call(nrf_drv_usbd_ep_t ep, app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Auxiliary function that process event by every instance in the list.
     *
     * This function ignores the result of called handler.
     *
     * @param p_event Event to pass to every instance.
     */
    void app_usbd_all_call(app_usbd_complex_evt_t const * const p_event);

    /**
     * @brief Call interface event handlers and stop when served.
     *
     * Call event handlers from instances as long as we get result different than @ref NRF_ERROR_NOT_SUPPORTED
     * @param[in] p_event Event structure to send.
     *
     * @return Operation status or @ref NRF_ERROR_NOT_SUPPORTED if none of instances in the list can support given event.
     */
    ret_code_t app_usbd_all_until_served_call(app_usbd_complex_evt_t const * const p_event);
/** @} */

/**
 * @brief Endpoint transfer.
 *
 * @param ep         Endpoint number.
 * @param p_transfer Description of the transfer to be performed.
 *                   The direction of the transfer is determined by the
 *                   endpoint number.
 *
 * @retval NRF_ERROR_INVALID_STATE The state of the USB device does not allow
 *                                 data transfer on the endpoint.
 * @return Values returned by @ref nrf_drv_usbd_ep_transfer.
 *
 * @sa app_usbd_ep_handled_transfer
 */
ret_code_t app_usbd_ep_transfer(
    nrf_drv_usbd_ep_t                     ep,
    nrf_drv_usbd_transfer_t const * const p_transfer);

/**
 * @brief Set up an endpoint handled transfer.
 *
 * Configures a transfer handled by the feedback function.
 *
 * @param ep        Endpoint number.
 * @param p_handler Function called when the next chunk of data is requested.
 *
 * @retval NRF_ERROR_INVALID_STATE The state of the USB device does not allow
 *                                 data transfer on the endpoint.
 * @return Values returned by @ref nrf_drv_usbd_ep_handled_transfer.
 */
ret_code_t app_usbd_ep_handled_transfer(
    nrf_drv_usbd_ep_t                         ep,
    nrf_drv_usbd_handler_desc_t const * const p_handler);


/**
 * @brief Select interface
 *
 * Select the given interface.
 * This function calls class interface selection function or default
 * interface selection function.
 *
 * After calling this function interface should be functional.
 *
 * @param[in,out] p_inst    Instance of the class.
 * @param[in]     iface_idx Index of the interface inside class structure.
 * @param[in]     alternate Alternate setting that should be selected.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_iface_select(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx,
    uint8_t                             alternate);


/**
 * @brief Deselect interface.
 *
 * Disable the given interface.
 * This function calls class interface deselection function or
 * default interface selection function.
 *
 * After calling this function all the endpoints from the interface
 * have to be disabled.
 *
 * @param[in,out] p_inst    Instance of the class.
 * @param[in]     iface_idx Index of the interface inside class structure.
 */
void app_usbd_iface_deselect(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx);

/**
 * @brief Get selected interface.
 *
 * Function retieves currently selected interface.
 * If the class contains @ref app_usbd_class_methods_t::iface_selection_get it is called.
 * It it does not contain this function this function would return default, 0 value.
 *
 * @param[in] p_inst    Instance of the class.
 * @param[in] iface_idx Index of the interface inside class structure.
 *
 * @return Selected alternate interface setting.
 */
uint8_t app_usbd_iface_selection_get(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx);

/**
 * @brief Select alternate configuration 0 for all interfaces.
 *
 * Auxiliary function that clears settings for all interfaces leaving them enabled.
 */
void app_usbd_all_iface_select_0(void);

/**
 * @brief Deselect all interfaces.
 *
 * Auxiliary function to disable all interfaces.
 */
void app_usbd_all_iface_deselect(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_H__ */
