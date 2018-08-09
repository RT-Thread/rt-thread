/**
 * Copyright (c) 2013 - 2018, Nordic Semiconductor ASA
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

#if NRF_MODULE_ENABLED(BLE_DB_DISCOVERY)
#include "ble_db_discovery.h"
#include <stdlib.h>
#include "ble_srv_common.h"
#define NRF_LOG_MODULE_NAME ble_db_disc
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define SRV_DISC_START_HANDLE  0x0001                    /**< The start handle value used during service discovery. */
#define DB_DISCOVERY_MAX_USERS BLE_DB_DISCOVERY_MAX_SRV  /**< The maximum number of users/registrations allowed by this module. */
#define MODULE_INITIALIZED (m_initialized == true)       /**< Macro designating whether the module has been initialized properly. */


/**@brief Array of structures containing information about the registered application modules. */
static ble_uuid_t m_registered_handlers[DB_DISCOVERY_MAX_USERS];


/**@brief   Array of structures containing pending events to be sent to the application modules.
 *
 * @details Whenever a discovery related event is to be raised to a user module, it will be stored
 *          in this array first. When all services needed to be discovered have been
 *          discovered, all pending events will be sent to the corresponding user modules.
 **/
static struct
{
    ble_db_discovery_evt_t         evt;          /**< The pending event. */
    ble_db_discovery_evt_handler_t evt_handler;  /**< The event handler which should be called to raise this event. */
} m_pending_user_evts[DB_DISCOVERY_MAX_USERS];

static ble_db_discovery_evt_handler_t m_evt_handler;
static uint32_t m_pending_usr_evt_index;    /**< The index to the pending user event array, pointing to the last added pending user event. */
static uint32_t m_num_of_handlers_reg;      /**< The number of handlers registered with the DB Discovery module. */
static bool     m_initialized = false;      /**< This variable Indicates if the module is initialized or not. */

/**@brief     Function for fetching the event handler provided by a registered application module.
 *
 * @param[in] srv_uuid UUID of the service.
 *
 * @retval    evt_handler Event handler of the module, registered for the given service UUID.
 * @retval    NULL If no event handler is found.
 */
static ble_db_discovery_evt_handler_t registered_handler_get(ble_uuid_t const * p_srv_uuid)
{
    for (uint32_t i = 0; i < m_num_of_handlers_reg; i++)
    {
        if (BLE_UUID_EQ(&(m_registered_handlers[i]), p_srv_uuid))
        {
            return (m_evt_handler);
        }
    }

    return NULL;
}


/**@brief     Function for storing the event handler provided by a registered application module.
 *
 * @param[in] p_srv_uuid    The UUID of the service.
 * @param[in] p_evt_handler The event handler provided by the application.
 *
 * @retval    NRF_SUCCESS If the handler was stored or already present in the list.
 * @retval    NRF_ERROR_NO_MEM If there is no space left to store the handler.
 */
static uint32_t registered_handler_set(ble_uuid_t                     const * p_srv_uuid,
                                       ble_db_discovery_evt_handler_t         p_evt_handler)
{
    if (registered_handler_get(p_srv_uuid) != NULL)
    {
        return NRF_SUCCESS;
    }

    if (m_num_of_handlers_reg < DB_DISCOVERY_MAX_USERS)
    {
        m_registered_handlers[m_num_of_handlers_reg] = *p_srv_uuid;
        m_num_of_handlers_reg++;

        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_NO_MEM;
    }
}


/**@brief Function for sending all pending discovery events to the corresponding user modules.
 */
static void pending_user_evts_send(void)
{
    for (uint32_t i = 0; i < m_num_of_handlers_reg; i++)
    {
        // Pass the event to the corresponding event handler.
        m_pending_user_evts[i].evt_handler(&(m_pending_user_evts[i].evt));
    }

    m_pending_usr_evt_index = 0;
}


/**@brief     Function for indicating error to the application.
 *
 * @details   This function will fetch the event handler based on the UUID of the service being
 *            discovered. (The event handler is registered by the application beforehand).
 *            The error code is added to the pending events together with the event handler.
 *            If no event handler was found, then this function will do nothing.
 *
 * @param[in] p_db_discovery Pointer to the DB discovery structure.
 * @param[in] err_code       Error code that should be provided to the application.
 * @param[in] conn_handle    Connection Handle.
 *
 */
static void discovery_error_evt_trigger(ble_db_discovery_t * p_db_discovery,
                                        uint32_t             err_code,
                                        uint16_t             conn_handle)
{
    ble_db_discovery_evt_handler_t   p_evt_handler;
    ble_gatt_db_srv_t              * p_srv_being_discovered;

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    p_evt_handler = registered_handler_get(&(p_srv_being_discovered->srv_uuid));

    if (p_evt_handler != NULL)
    {
        ble_db_discovery_evt_t evt =
        {
            .conn_handle     = conn_handle,
            .evt_type        = BLE_DB_DISCOVERY_ERROR,
            .params.err_code = err_code,
        };

        p_evt_handler(&evt);
    }
}


/**@brief     Function for triggering a Discovery Complete or Service Not Found event to the
 *            application.
 *
 * @details   This function will fetch the event handler based on the UUID of the service being
 *            discovered. (The event handler is registered by the application beforehand).
 *            It then triggers an event indicating the completion of the service discovery.
 *            If no event handler was found, then this function will do nothing.
 *
 * @param[in] p_db_discovery Pointer to the DB discovery structure.
 * @param[in] is_srv_found   Variable to indicate if the service was found at the peer.
 * @param[in] conn_handle    Connection Handle.
 */
static void discovery_complete_evt_trigger(ble_db_discovery_t * p_db_discovery,
                                           bool                 is_srv_found,
                                           uint16_t             conn_handle)
{
    ble_db_discovery_evt_handler_t   p_evt_handler;
    ble_gatt_db_srv_t              * p_srv_being_discovered;

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    p_evt_handler = registered_handler_get(&(p_srv_being_discovered->srv_uuid));

    if (p_evt_handler != NULL)
    {
        if (m_pending_usr_evt_index < DB_DISCOVERY_MAX_USERS)
        {
            // Insert an event into the pending event list.
            m_pending_user_evts[m_pending_usr_evt_index].evt.conn_handle = conn_handle;
            m_pending_user_evts[m_pending_usr_evt_index].evt.params.discovered_db =
                *p_srv_being_discovered;

            if (is_srv_found)
            {
                m_pending_user_evts[m_pending_usr_evt_index].evt.evt_type =
                    BLE_DB_DISCOVERY_COMPLETE;
            }
            else
            {
                m_pending_user_evts[m_pending_usr_evt_index].evt.evt_type =
                    BLE_DB_DISCOVERY_SRV_NOT_FOUND;
            }

            m_pending_user_evts[m_pending_usr_evt_index].evt_handler = p_evt_handler;
            m_pending_usr_evt_index++;

            if (m_pending_usr_evt_index == m_num_of_handlers_reg)
            {
                // All registered modules have pending events. Send all pending events to the user
                // modules.
                pending_user_evts_send();
            }
            else
            {
                // Too many events pending. Do nothing. (Ideally this should not happen.)
            }
        }
    }
}


/**@brief     Function for handling service discovery completion.
 *
 * @details   This function will be used to determine if there are more services to be discovered,
 *            and if so, initiate the discovery of the next service.
 *
 * @param[in] p_db_discovery Pointer to the DB Discovery Structure.
 * @param[in] conn_handle    Connection Handle.
 */
static void on_srv_disc_completion(ble_db_discovery_t * p_db_discovery,
                                   uint16_t             conn_handle)
{
    p_db_discovery->discoveries_count++;

    // Check if more services need to be discovered.
    if (p_db_discovery->discoveries_count < m_num_of_handlers_reg)
    {
        // Reset the current characteristic index since a new service discovery is about to start.
        p_db_discovery->curr_char_ind = 0;

        // Initiate discovery of the next service.
        p_db_discovery->curr_srv_ind++;

        ble_gatt_db_srv_t * p_srv_being_discovered;

        p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

        p_srv_being_discovered->srv_uuid = m_registered_handlers[p_db_discovery->curr_srv_ind];

        // Reset the characteristic count in the current service to zero since a new service
        // discovery is about to start.
        p_srv_being_discovered->char_count = 0;

        NRF_LOG_DEBUG("Starting discovery of service with UUID 0x%x on connection handle 0x%x.",
                      p_srv_being_discovered->srv_uuid.uuid, conn_handle);

        uint32_t err_code;

        err_code = sd_ble_gattc_primary_services_discover(conn_handle,
                                                          SRV_DISC_START_HANDLE,
                                                          &(p_srv_being_discovered->srv_uuid));

        if (err_code != NRF_SUCCESS)
        {
            p_db_discovery->discovery_in_progress = false;

            // Error with discovering the service.
            // Indicate the error to the registered user application.
            discovery_error_evt_trigger(p_db_discovery, err_code, conn_handle);

            m_pending_user_evts[0].evt.evt_type    = BLE_DB_DISCOVERY_AVAILABLE;
            m_pending_user_evts[0].evt.conn_handle = conn_handle;

            return;
        }
    }
    else
    {
        // No more service discovery is needed.
        p_db_discovery->discovery_in_progress  = false;
        m_pending_user_evts[0].evt.evt_type    = BLE_DB_DISCOVERY_AVAILABLE;
        m_pending_user_evts[0].evt.conn_handle = conn_handle;
    }
}


/**@brief     Function for finding out if a characteristic discovery should be performed after the
 *            last discovered characteristic.
 *
 * @details   This function is used during the time of database discovery to find out if there is
 *            a need to do more characteristic discoveries. The value handles of the
 *            last discovered characteristic is compared with the end handle of the service.
 *            If the service handle is greater than one of the former characteristic handles,
 *            it means that a characteristic discovery is required.
 *
 * @param[in] p_db_discovery The pointer to the DB Discovery structure.
 * @param[in] p_after_char   The pointer to the last discovered characteristic.
 *
 * @retval    True if a characteristic discovery is required.
 * @retval    False if a characteristic discovery is NOT required.
 */
static bool is_char_discovery_reqd(ble_db_discovery_t * p_db_discovery,
                                   ble_gattc_char_t   * p_after_char)
{
    if (p_after_char->handle_value <
        p_db_discovery->services[p_db_discovery->curr_srv_ind].handle_range.end_handle)
    {
        // Handle value of the characteristic being discovered is less than the end handle of
        // the service being discovered. There is a possibility of more characteristics being
        // present. Hence a characteristic discovery is required.
        return true;
    }

    return false;
}


/**@brief      Function to find out if a descriptor discovery is required.
 *
 * @details    This function finds out if there is a possibility of existence of descriptors between
 *             current characteristic and the next characteristic. If so, this function will compute
 *             the handle range on which the descriptors may be present and will return it.
 *             If the current characteristic is the last known characteristic, then this function
 *             will use the service end handle to find out if the current characteristic can have
 *             descriptors.
 *
 * @param[in]  p_db_discovery Pointer to the DB Discovery structure.
 * @param[in]  p_curr_char    Pointer to the current characteristic.
 * @param[in]  p_next_char    Pointer to the next characteristic. This should be NULL if the
 *                            caller knows that there is no characteristic after the current
 *                            characteristic at the peer.
 * @param[out] p_handle_range Pointer to the handle range in which descriptors may exist at the
 *                            the peer.
 *
 * @retval     True If a descriptor discovery is required.
 * @retval     False If a descriptor discovery is NOT required.
 */
static bool is_desc_discovery_reqd(ble_db_discovery_t       * p_db_discovery,
                                   ble_gatt_db_char_t       * p_curr_char,
                                   ble_gatt_db_char_t       * p_next_char,
                                   ble_gattc_handle_range_t * p_handle_range)
{
    if (p_next_char == NULL)
    {
        // Current characteristic is the last characteristic in the service. Check if the value
        // handle of the current characteristic is equal to the service end handle.
        if (
            p_curr_char->characteristic.handle_value ==
            p_db_discovery->services[p_db_discovery->curr_srv_ind].handle_range.end_handle
           )
        {
            // No descriptors can be present for the current characteristic. p_curr_char is the last
            // characteristic with no descriptors.
            return false;
        }

        p_handle_range->start_handle = p_curr_char->characteristic.handle_value + 1;

        // Since the current characteristic is the last characteristic in the service, the end
        // handle should be the end handle of the service.
        p_handle_range->end_handle =
            p_db_discovery->services[p_db_discovery->curr_srv_ind].handle_range.end_handle;

        return true;
    }

    // p_next_char != NULL. Check for existence of descriptors between the current and the next
    // characteristic.
    if ((p_curr_char->characteristic.handle_value + 1) == p_next_char->characteristic.handle_decl)
    {
        // No descriptors can exist between the two characteristic.
        return false;
    }

    p_handle_range->start_handle = p_curr_char->characteristic.handle_value + 1;
    p_handle_range->end_handle   = p_next_char->characteristic.handle_decl - 1;

    return true;
}


/**@brief     Function for performing characteristic discovery.
 *
 * @param[in] p_db_discovery Pointer to the DB Discovery structure.
 * @param[in] conn_handle    Connection Handle.
 *
 * @return    NRF_SUCCESS if the SoftDevice was successfully requested to perform the characteristic
 *            discovery. Otherwise an error code. This function returns the error code returned
 *            by the SoftDevice API @ref sd_ble_gattc_characteristics_discover.
 */
static uint32_t characteristics_discover(ble_db_discovery_t * p_db_discovery,
                                         uint16_t             conn_handle)
{
    ble_gatt_db_srv_t      * p_srv_being_discovered;
    ble_gattc_handle_range_t handle_range;

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    if (p_db_discovery->curr_char_ind != 0)
    {
        // This is not the first characteristic being discovered. Hence the 'start handle' to be
        // used must be computed using the handle_value of the previous characteristic.
        ble_gattc_char_t * p_prev_char;
        uint8_t            prev_char_ind = p_db_discovery->curr_char_ind - 1;

        p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

        p_prev_char = &(p_srv_being_discovered->charateristics[prev_char_ind].characteristic);

        handle_range.start_handle = p_prev_char->handle_value + 1;
    }
    else
    {
        // This is the first characteristic of this service being discovered.
        handle_range.start_handle = p_srv_being_discovered->handle_range.start_handle;
    }

    handle_range.end_handle = p_srv_being_discovered->handle_range.end_handle;

    return sd_ble_gattc_characteristics_discover(conn_handle, &handle_range);
}


/**@brief      Function for performing descriptor discovery, if required.
 *
 * @details    This function will check if descriptor discovery is required and then perform it if
 *             needed. If no more descriptor discovery is required for the service, then the output
 *             parameter p_raise_discov_complete is set to true, indicating to the caller that a
 *             discovery complete event can be triggered to the application.
 *
 * @param[in]  p_db_discovery           Pointer to the DB Discovery structure.
 * @param[out] p_raise_discov_complete  The value pointed to by this pointer will be set to true if
 *                                      the Discovery Complete event can be triggered to the
 *                                      application.
 * @param[in] conn_handle               Connection Handle.
 *
 * @return     NRF_SUCCESS if the SoftDevice was successfully requested to perform the descriptor
 *             discovery, or if no more descriptor discovery is required. Otherwise an error code.
 *             This function returns the error code returned by the SoftDevice API @ref
 *             sd_ble_gattc_descriptors_discover.
 */
static uint32_t descriptors_discover(ble_db_discovery_t * p_db_discovery,
                                     bool               * p_raise_discov_complete,
                                     uint16_t             conn_handle)
{
    ble_gattc_handle_range_t   handle_range;
    ble_gatt_db_char_t       * p_curr_char_being_discovered;
    ble_gatt_db_srv_t        * p_srv_being_discovered;
    bool                       is_discovery_reqd = false;

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    p_curr_char_being_discovered =
        &(p_srv_being_discovered->charateristics[p_db_discovery->curr_char_ind]);

    if ((p_db_discovery->curr_char_ind + 1) == p_srv_being_discovered->char_count)
    {
        // This is the last characteristic of this service.
        is_discovery_reqd = is_desc_discovery_reqd(p_db_discovery,
                                                   p_curr_char_being_discovered,
                                                   NULL,
                                                   &handle_range);
    }
    else
    {
        uint8_t                   i;
        ble_gatt_db_char_t * p_next_char;

        for (i = p_db_discovery->curr_char_ind; i < p_srv_being_discovered->char_count; i++)
        {
            if (i == (p_srv_being_discovered->char_count - 1))
            {
                // The current characteristic is the last characteristic in the service.
                p_next_char = NULL;
            }
            else
            {
                p_next_char = &(p_srv_being_discovered->charateristics[i + 1]);
            }

            // Check if it is possible for the current characteristic to have a descriptor.
            if (is_desc_discovery_reqd(p_db_discovery,
                                       p_curr_char_being_discovered,
                                       p_next_char,
                                       &handle_range))
            {
                is_discovery_reqd = true;
                break;
            }
            else
            {
                // No descriptors can exist.
                p_curr_char_being_discovered = p_next_char;
                p_db_discovery->curr_char_ind++;
            }
        }
    }

    if (!is_discovery_reqd)
    {
        // No more descriptor discovery required. Discovery is complete.
        // This informs the caller that a discovery complete event can be triggered.
        *p_raise_discov_complete = true;

        return NRF_SUCCESS;
    }

    *p_raise_discov_complete = false;

    return sd_ble_gattc_descriptors_discover(conn_handle, &handle_range);
}


/**@brief     Function for handling primary service discovery response.
 *
 * @details   This function will handle the primary service discovery response and start the
 *            discovery of characteristics within that service.
 *
 * @param[in] p_db_discovery    Pointer to the DB Discovery structure.
 * @param[in] p_ble_gattc_evt   Pointer to the GATT Client event.
 */
static void on_primary_srv_discovery_rsp(ble_db_discovery_t       * p_db_discovery,
                                         ble_gattc_evt_t    const * p_ble_gattc_evt)
{
    ble_gatt_db_srv_t * p_srv_being_discovered;

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    if (p_ble_gattc_evt->conn_handle != p_db_discovery->conn_handle)
    {
        return;
    }

    if (p_ble_gattc_evt->gatt_status == BLE_GATT_STATUS_SUCCESS)
    {
        uint32_t err_code;
        ble_gattc_evt_prim_srvc_disc_rsp_t const * p_prim_srvc_disc_rsp_evt;

        NRF_LOG_DEBUG("Found service UUID 0x%x.", p_srv_being_discovered->srv_uuid.uuid);

        p_prim_srvc_disc_rsp_evt = &(p_ble_gattc_evt->params.prim_srvc_disc_rsp);

        p_srv_being_discovered->srv_uuid     = p_prim_srvc_disc_rsp_evt->services[0].uuid;
        p_srv_being_discovered->handle_range = p_prim_srvc_disc_rsp_evt->services[0].handle_range;

        err_code = characteristics_discover(p_db_discovery, p_ble_gattc_evt->conn_handle);

        if (err_code != NRF_SUCCESS)
        {
            p_db_discovery->discovery_in_progress = false;

            // Error with discovering the service.
            // Indicate the error to the registered user application.
            discovery_error_evt_trigger(p_db_discovery, err_code, p_ble_gattc_evt->conn_handle);

            m_pending_user_evts[0].evt.evt_type    = BLE_DB_DISCOVERY_AVAILABLE;
            m_pending_user_evts[0].evt.conn_handle = p_ble_gattc_evt->conn_handle;
        }
    }
    else
    {
        NRF_LOG_DEBUG("Service UUID 0x%x not found.", p_srv_being_discovered->srv_uuid.uuid);
        // Trigger Service Not Found event to the application.
        discovery_complete_evt_trigger(p_db_discovery, false, p_ble_gattc_evt->conn_handle);
        on_srv_disc_completion(p_db_discovery, p_ble_gattc_evt->conn_handle);
    }
}


/**@brief     Function for handling characteristic discovery response.
 *
 * @param[in] p_db_discovery    Pointer to the DB Discovery structure.
 * @param[in] p_ble_gattc_evt   Pointer to the GATT Client event.
 */
static void on_characteristic_discovery_rsp(ble_db_discovery_t       * p_db_discovery,
                                            ble_gattc_evt_t    const * p_ble_gattc_evt)
{
    uint32_t            err_code;
    ble_gatt_db_srv_t * p_srv_being_discovered;
    bool                perform_desc_discov = false;

    if (p_ble_gattc_evt->conn_handle != p_db_discovery->conn_handle)
    {
        return;
    }

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    if (p_ble_gattc_evt->gatt_status == BLE_GATT_STATUS_SUCCESS)
    {
        ble_gattc_evt_char_disc_rsp_t const * p_char_disc_rsp_evt;

        p_char_disc_rsp_evt = &(p_ble_gattc_evt->params.char_disc_rsp);

        // Find out the number of characteristics that were previously discovered (in earlier
        // characteristic discovery responses, if any).
        uint8_t num_chars_prev_disc = p_srv_being_discovered->char_count;

        // Find out the number of characteristics that are currently discovered (in the
        // characteristic discovery response being handled).
        uint8_t num_chars_curr_disc = p_char_disc_rsp_evt->count;

        // Check if the total number of discovered characteristics are supported by this module.
        if ((num_chars_prev_disc + num_chars_curr_disc) <= BLE_GATT_DB_MAX_CHARS)
        {
            // Update the characteristics count.
            p_srv_being_discovered->char_count += num_chars_curr_disc;
        }
        else
        {
            // The number of characteristics discovered at the peer is more than the supported
            // maximum. This module will store only the characteristics found up to this point.
            p_srv_being_discovered->char_count = BLE_GATT_DB_MAX_CHARS;
        }

        uint32_t i;
        uint32_t j;

        for (i = num_chars_prev_disc, j = 0; i < p_srv_being_discovered->char_count; i++, j++)
        {
            p_srv_being_discovered->charateristics[i].characteristic =
                p_char_disc_rsp_evt->chars[j];

            p_srv_being_discovered->charateristics[i].cccd_handle       = BLE_GATT_HANDLE_INVALID;
            p_srv_being_discovered->charateristics[i].ext_prop_handle   = BLE_GATT_HANDLE_INVALID;
            p_srv_being_discovered->charateristics[i].user_desc_handle  = BLE_GATT_HANDLE_INVALID;
            p_srv_being_discovered->charateristics[i].report_ref_handle = BLE_GATT_HANDLE_INVALID;
        }

        ble_gattc_char_t * p_last_known_char;

        p_last_known_char = &(p_srv_being_discovered->charateristics[i - 1].characteristic);

        // If no more characteristic discovery is required, or if the maximum number of supported
        // characteristic per service has been reached, descriptor discovery will be performed.
        if (   !is_char_discovery_reqd(p_db_discovery, p_last_known_char)
            || (p_srv_being_discovered->char_count == BLE_GATT_DB_MAX_CHARS))
        {
            perform_desc_discov = true;
        }
        else
        {
            // Update the current characteristic index.
            p_db_discovery->curr_char_ind = p_srv_being_discovered->char_count;

            // Perform another round of characteristic discovery.
            err_code = characteristics_discover(p_db_discovery, p_ble_gattc_evt->conn_handle);

            if (err_code != NRF_SUCCESS)
            {
                p_db_discovery->discovery_in_progress = false;

                discovery_error_evt_trigger(p_db_discovery, err_code, p_ble_gattc_evt->conn_handle);

                m_pending_user_evts[0].evt.evt_type    = BLE_DB_DISCOVERY_AVAILABLE;
                m_pending_user_evts[0].evt.conn_handle = p_ble_gattc_evt->conn_handle;

                return;
            }
        }
    }
    else
    {
        // The previous characteristic discovery resulted in no characteristics.
        // descriptor discovery should be performed.
        perform_desc_discov = true;
    }

    if (perform_desc_discov)
    {
        bool raise_discov_complete;

        p_db_discovery->curr_char_ind = 0;

        err_code = descriptors_discover(p_db_discovery,
                                        &raise_discov_complete,
                                        p_ble_gattc_evt->conn_handle);

        if (err_code != NRF_SUCCESS)
        {
            p_db_discovery->discovery_in_progress = false;

            discovery_error_evt_trigger(p_db_discovery, err_code, p_ble_gattc_evt->conn_handle);

            m_pending_user_evts[0].evt.evt_type    = BLE_DB_DISCOVERY_AVAILABLE;
            m_pending_user_evts[0].evt.conn_handle = p_ble_gattc_evt->conn_handle;

            return;
        }
        if (raise_discov_complete)
        {
            // No more characteristics and descriptors need to be discovered. Discovery is complete.
            // Send a discovery complete event to the user application.
            NRF_LOG_DEBUG("Discovery of service with UUID 0x%x completed with success"
                          " on connection handle 0x%x.",
                          p_srv_being_discovered->srv_uuid.uuid,
                          p_ble_gattc_evt->conn_handle);

            discovery_complete_evt_trigger(p_db_discovery, true, p_ble_gattc_evt->conn_handle);
            on_srv_disc_completion(p_db_discovery, p_ble_gattc_evt->conn_handle);
        }
    }
}


/**@brief     Function for handling descriptor discovery response.
 *
 * @param[in] p_db_discovery    Pointer to the DB Discovery structure.
 * @param[in] p_ble_gattc_evt   Pointer to the GATT Client event.
 */
static void on_descriptor_discovery_rsp(ble_db_discovery_t * const    p_db_discovery,
                                        const ble_gattc_evt_t * const p_ble_gattc_evt)
{
    const ble_gattc_evt_desc_disc_rsp_t * p_desc_disc_rsp_evt;
    ble_gatt_db_srv_t                   * p_srv_being_discovered;

    if (p_ble_gattc_evt->conn_handle != p_db_discovery->conn_handle)
    {
        return;
    }

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);

    p_desc_disc_rsp_evt = &(p_ble_gattc_evt->params.desc_disc_rsp);

    ble_gatt_db_char_t * p_char_being_discovered =
        &(p_srv_being_discovered->charateristics[p_db_discovery->curr_char_ind]);

    if (p_ble_gattc_evt->gatt_status == BLE_GATT_STATUS_SUCCESS)
    {
        // The descriptor was found at the peer.
        // Iterate through and collect CCCD, Extended Properties,
        // User Description & Report Reference descriptor handles.
        for (uint32_t i = 0; i < p_desc_disc_rsp_evt->count; i++)
        {
            switch (p_desc_disc_rsp_evt->descs[i].uuid.uuid)
            {
                case BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG:
                    p_char_being_discovered->cccd_handle =
                        p_desc_disc_rsp_evt->descs[i].handle;
                    break;

                case BLE_UUID_DESCRIPTOR_CHAR_EXT_PROP:
                    p_char_being_discovered->ext_prop_handle =
                        p_desc_disc_rsp_evt->descs[i].handle;
                    break;

                case BLE_UUID_DESCRIPTOR_CHAR_USER_DESC:
                    p_char_being_discovered->user_desc_handle =
                        p_desc_disc_rsp_evt->descs[i].handle;
                    break;

                case BLE_UUID_REPORT_REF_DESCR:
                    p_char_being_discovered->report_ref_handle =
                        p_desc_disc_rsp_evt->descs[i].handle;
                    break;
            }

            /* Break if we've found all the descriptors we are looking for. */
            if (p_char_being_discovered->cccd_handle       != BLE_GATT_HANDLE_INVALID &&
                p_char_being_discovered->ext_prop_handle   != BLE_GATT_HANDLE_INVALID &&
                p_char_being_discovered->user_desc_handle  != BLE_GATT_HANDLE_INVALID &&
                p_char_being_discovered->report_ref_handle != BLE_GATT_HANDLE_INVALID)
            {
                break;
            }
        }
    }

    bool raise_discov_complete = false;

    if ((p_db_discovery->curr_char_ind + 1) == p_srv_being_discovered->char_count)
    {
        // No more characteristics and descriptors need to be discovered. Discovery is complete.
        // Send a discovery complete event to the user application.

        raise_discov_complete = true;
    }
    else
    {
        // Begin discovery of descriptors for the next characteristic.
        uint32_t err_code;

        p_db_discovery->curr_char_ind++;

        err_code = descriptors_discover(p_db_discovery,
                                        &raise_discov_complete,
                                        p_ble_gattc_evt->conn_handle);

        if (err_code != NRF_SUCCESS)
        {
            p_db_discovery->discovery_in_progress = false;

            // Error with discovering the service.
            // Indicate the error to the registered user application.
            discovery_error_evt_trigger(p_db_discovery, err_code, p_ble_gattc_evt->conn_handle);

            m_pending_user_evts[0].evt.evt_type    = BLE_DB_DISCOVERY_AVAILABLE;
            m_pending_user_evts[0].evt.conn_handle = p_ble_gattc_evt->conn_handle;

            return;
        }
    }

    if (raise_discov_complete)
    {
        NRF_LOG_DEBUG("Discovery of service with UUID 0x%x completed with success"
                      " on connection handle 0x%x.",
                      p_srv_being_discovered->srv_uuid.uuid,
                      p_ble_gattc_evt->conn_handle);

        discovery_complete_evt_trigger(p_db_discovery, true, p_ble_gattc_evt->conn_handle);
        on_srv_disc_completion(p_db_discovery, p_ble_gattc_evt->conn_handle);
    }
}


uint32_t ble_db_discovery_init(const ble_db_discovery_evt_handler_t evt_handler)
{
    uint32_t err_code = NRF_SUCCESS;
    VERIFY_PARAM_NOT_NULL(evt_handler);

    m_num_of_handlers_reg   = 0;
    m_initialized           = true;
    m_pending_usr_evt_index = 0;
    m_evt_handler           = evt_handler;

    return err_code;

}


uint32_t ble_db_discovery_close()
{
    m_num_of_handlers_reg   = 0;
    m_initialized           = false;
    m_pending_usr_evt_index = 0;

    return NRF_SUCCESS;
}


uint32_t ble_db_discovery_evt_register(ble_uuid_t const * p_uuid)
{
    VERIFY_PARAM_NOT_NULL(p_uuid);
    VERIFY_MODULE_INITIALIZED();

    return registered_handler_set(p_uuid, m_evt_handler);
}


static uint32_t discovery_start(ble_db_discovery_t * const p_db_discovery, uint16_t conn_handle)
{
    uint32_t err_code;
    ble_gatt_db_srv_t * p_srv_being_discovered;

    memset(p_db_discovery, 0x00, sizeof(ble_db_discovery_t));

    p_db_discovery->conn_handle = conn_handle;

    m_pending_usr_evt_index   = 0;

    p_db_discovery->discoveries_count = 0;
    p_db_discovery->curr_srv_ind      = 0;
    p_db_discovery->curr_char_ind     = 0;

    p_srv_being_discovered = &(p_db_discovery->services[p_db_discovery->curr_srv_ind]);
    p_srv_being_discovered->srv_uuid = m_registered_handlers[p_db_discovery->curr_srv_ind];

    NRF_LOG_DEBUG("Starting discovery of service with UUID 0x%x on connection handle 0x%x.",
                  p_srv_being_discovered->srv_uuid.uuid, conn_handle);

    err_code = sd_ble_gattc_primary_services_discover(conn_handle,
                                                      SRV_DISC_START_HANDLE,
                                                      &(p_srv_being_discovered->srv_uuid));
    if (err_code != NRF_ERROR_BUSY)
    {
        VERIFY_SUCCESS(err_code);
        p_db_discovery->discovery_in_progress = true;
        p_db_discovery->discovery_pending     = false;
    }
    else
    {
        p_db_discovery->discovery_in_progress = true;
        p_db_discovery->discovery_pending     = true;
    }

    return NRF_SUCCESS;
}


uint32_t ble_db_discovery_start(ble_db_discovery_t * const p_db_discovery, uint16_t conn_handle)
{
    VERIFY_PARAM_NOT_NULL(p_db_discovery);
    VERIFY_MODULE_INITIALIZED();

    if (m_num_of_handlers_reg == 0)
    {
        // No user modules were registered. There are no services to discover.
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_db_discovery->discovery_in_progress)
    {
        return NRF_ERROR_BUSY;
    }

    return discovery_start(p_db_discovery, conn_handle);
}


/**@brief     Function for handling disconnected event.
 *
 * @param[in] p_db_discovery    Pointer to the DB Discovery structure.
 * @param[in] p_ble_gattc_evt   Pointer to the GAP event.
 */
static void on_disconnected(ble_db_discovery_t       * p_db_discovery,
                            ble_gap_evt_t      const * p_evt)
{
    if (p_evt->conn_handle == p_db_discovery->conn_handle)
    {
        p_db_discovery->discovery_in_progress = false;
        p_db_discovery->discovery_pending     = false;
        p_db_discovery->conn_handle           = BLE_CONN_HANDLE_INVALID;
    }
}


void ble_db_discovery_on_ble_evt(ble_evt_t const * p_ble_evt,
                                 void            * p_context)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);
    VERIFY_PARAM_NOT_NULL_VOID(p_context);
    VERIFY_MODULE_INITIALIZED_VOID();

    ble_db_discovery_t * p_db_discovery = (ble_db_discovery_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP:
            on_primary_srv_discovery_rsp(p_db_discovery, &(p_ble_evt->evt.gattc_evt));
            break;

        case BLE_GATTC_EVT_CHAR_DISC_RSP:
            on_characteristic_discovery_rsp(p_db_discovery, &(p_ble_evt->evt.gattc_evt));
            break;

        case BLE_GATTC_EVT_DESC_DISC_RSP:
            on_descriptor_discovery_rsp(p_db_discovery, &(p_ble_evt->evt.gattc_evt));
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_db_discovery, &(p_ble_evt->evt.gap_evt));
            break;

        default:
            break;
    }

    if (   (p_db_discovery->discovery_pending)
        && (p_ble_evt->header.evt_id >= BLE_GATTC_EVT_BASE)
        && (p_ble_evt->header.evt_id <= BLE_GATTC_EVT_LAST)
        && (p_ble_evt->evt.gattc_evt.conn_handle == p_db_discovery->conn_handle))
    {
        (void)discovery_start(p_db_discovery, p_db_discovery->conn_handle);
    }
}
#endif // NRF_MODULE_ENABLED(BLE_DB_DISCOVERY)
