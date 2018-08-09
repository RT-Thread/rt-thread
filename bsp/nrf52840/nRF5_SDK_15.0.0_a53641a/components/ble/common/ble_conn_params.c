/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_BLE_CONN_PARAMS)
#include <stdlib.h>
#include "nrf.h"
#include "sdk_errors.h"
#include "ble_hci.h"
#include "ble_err.h"
#include "ble_conn_params.h"
#include "ble_srv_common.h"
#include "ble_conn_state.h"
#include "nrf_sdh_ble.h"
#include "app_timer.h"
#include "app_util.h"


#define NRF_BLE_CONN_PARAMS_INSTANCE_COUNT  NRF_SDH_BLE_PERIPHERAL_LINK_COUNT   //!< The number of @ref ble_conn_params_instance_t instances kept by the conn_params module.

#if (NRF_BLE_CONN_PARAMS_INSTANCE_COUNT < 1)
#error Invalid NRF_SDH_BLE_PERIPHERAL_LINK_COUNT value. Set it in SDK config (nrf_sdh_ble).
#endif

/** @brief Each peripheral link has such an instance associated with it.
 */
typedef struct
{
    uint16_t              conn_handle;           //!< The connection handle of this link. If this is @ref BLE_CONN_HANDLE_INVALID, the instance is free.
    app_timer_id_t        timer_id;              //!< The ID of the timer associated with this link.
    uint8_t               update_count;          //!< The number of times the connection parameters have been attempted negotiated on this link.
    uint8_t               params_ok;             //!< Whether the current connection parameters on this link are acceptable according to the @p preferred_conn_params, and configured maximum deviations.
    ble_gap_conn_params_t preferred_conn_params; //!< The desired connection parameters for this link.
} ble_conn_params_instance_t;

static app_timer_t                m_timer_data[NRF_BLE_CONN_PARAMS_INSTANCE_COUNT] = {{{0}}};          //!< Data needed for timers.
static ble_conn_params_instance_t m_conn_params_instances[NRF_BLE_CONN_PARAMS_INSTANCE_COUNT] = {{0}}; //!< Configuration data for each connection.
static ble_conn_params_init_t     m_conn_params_config;                                                //!< Configuration as provided by the application during intialization.
static ble_gap_conn_params_t      m_preferred_conn_params;                                             //!< The preferred connection parameters as specified during initialization.
//lint -esym(551, m_preferred_conn_params) "Not accessed"


/**@brief Function for retrieving the conn_params instance belonging to a conn_handle
 *
 * @params[in]  conn_handle  The connection handle to retrieve the instance of.
 *
 * @return  A pointer to the instance, or NULL if no instance was found with that conn_handle.
 */
static ble_conn_params_instance_t * instance_get(uint16_t conn_handle)
{
    //lint -save -e681 "Loop not entered" when NRF_BLE_CONN_PARAMS_INSTANCE_COUNT is 0
    for (uint32_t i = 0; i < NRF_BLE_CONN_PARAMS_INSTANCE_COUNT; i++)
    {
        if (m_conn_params_instances[i].conn_handle == conn_handle)
        {
            return &m_conn_params_instances[i];
        }
    }
    //lint -restore
    return NULL;
}


/**@brief Function for initializing an instance, and associating it with a conn_handle.
 *
 * @params[in]  p_instance   The instance to initialize and associate.
 * @params[in]  conn_handle  The connection handle to associate with.
 */
static __INLINE void instance_claim(ble_conn_params_instance_t * p_instance, uint16_t conn_handle)
{
    p_instance->conn_handle           = conn_handle;
    p_instance->update_count          = 0;
    p_instance->preferred_conn_params = m_preferred_conn_params;
}


/**@brief Function for freeing an instance.
 *
 * @params[in]  p_instance   The instance to free.
 */
static __INLINE void instance_free(ble_conn_params_instance_t * p_instance)
{
    p_instance->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for validating a set of connection parameters against the preferred parameters.
 *
 * @param[in]  p_preferred_conn_params  The desired parameters.
 * @param[in]  p_actual_conn_params     The parameters to validate.
 * @param[in]  max_slave_latency_err    The amount of discrepancy in slave latency, in number of
 *                                      connection intervals, that will be accepted.
 * @param[in]  max_sup_timeout_err      The amount of discrepancy in supervision timeout, in tens of
 *                                      milliseconds, that will be accepted.
 *
 * @return  Whether the params in @p p_actual_conn_params are acceptable given the other parameters.
 */
static bool is_conn_params_ok(ble_gap_conn_params_t const * p_preferred_conn_params,
                              ble_gap_conn_params_t const * p_actual_conn_params,
                              uint16_t                      max_slave_latency_err,
                              uint16_t                      max_sup_timeout_err)
{
    uint32_t max_allowed_sl = p_preferred_conn_params->slave_latency + max_slave_latency_err;
    uint32_t min_allowed_sl = p_preferred_conn_params->slave_latency
                              - MIN(max_slave_latency_err, p_preferred_conn_params->slave_latency);
    uint32_t max_allowed_to = p_preferred_conn_params->conn_sup_timeout + max_sup_timeout_err;
    uint32_t min_allowed_to = p_preferred_conn_params->conn_sup_timeout
                              - MIN(max_sup_timeout_err, p_preferred_conn_params->conn_sup_timeout);

    // Check if interval is within the acceptable range.
    // NOTE: Using max_conn_interval in the received event data because this contains
    //       the client's connection interval.
    if   ((p_actual_conn_params->max_conn_interval < p_preferred_conn_params->min_conn_interval)
       || (p_actual_conn_params->max_conn_interval > p_preferred_conn_params->max_conn_interval))
    {
        return false;
    }

    // Check if slave latency is within the acceptable deviation.
    if   ((p_actual_conn_params->slave_latency < min_allowed_sl)
       || (p_actual_conn_params->slave_latency > max_allowed_sl))
    {
        return false;
    }

    // Check if supervision timeout is within the acceptable deviation.
    if   ((p_actual_conn_params->conn_sup_timeout < min_allowed_to)
       || (p_actual_conn_params->conn_sup_timeout > max_allowed_to))
    {
        return false;
    }

    return true;
}


static void send_error_evt(ret_code_t err_code)
{
    if (m_conn_params_config.error_handler != NULL)
    {
        m_conn_params_config.error_handler(err_code);
    }
}


/**@brief Function for sending a conn_param_update request on-air, and handling errors.
 *
 * @param[in]  conn_handle        Connection to send request on.
 * @param[in]  p_new_conn_params  Connection parameters to request.
 *
 * @return  Whether the request was successfully sent.
 */
static bool send_update_request(uint16_t conn_handle, ble_gap_conn_params_t * p_new_conn_params)
{
    ret_code_t err_code;

    err_code = sd_ble_gap_conn_param_update(conn_handle, p_new_conn_params);
    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY)) // NRF_ERROR_BUSY means another conn_param_update request is pending.
    {
        send_error_evt(err_code);
    }

    return (err_code == NRF_SUCCESS);
}


/**@brief Function called after conn_params_update_delay has happened. This is triggered by app_timer.
 *
 * @param[in]  p_context  Context identifying which connection this is for.
 */
static void update_timeout_handler(void * p_context)
{
    uint32_t                     conn_handle = (uint32_t)p_context;
    ble_conn_params_instance_t * p_instance  = instance_get(conn_handle);

    if (p_instance != NULL)
    {
        // Check if we have reached the maximum number of attempts
        if (p_instance->update_count < m_conn_params_config.max_conn_params_update_count)
        {
            bool update_sent = send_update_request(conn_handle, &p_instance->preferred_conn_params);
            if (update_sent)
            {
                p_instance->update_count++;
            }
        }
        else
        {
            p_instance->update_count = 0;

            // Negotiation failed, disconnect automatically if this has been configured
            if (m_conn_params_config.disconnect_on_fail)
            {
                ret_code_t err_code;

                err_code = sd_ble_gap_disconnect(conn_handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
                if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_INVALID_STATE)) // NRF_ERROR_INVALID_STATE means disconnect is already in progress.
                {
                    send_error_evt(err_code);
                }
            }

            // Notify the application that the procedure has failed
            if (m_conn_params_config.evt_handler != NULL)
            {
                ble_conn_params_evt_t evt;

                evt.evt_type = BLE_CONN_PARAMS_EVT_FAILED;
                evt.conn_handle = conn_handle;
                m_conn_params_config.evt_handler(&evt);
            }
        }
    }
}


ret_code_t ble_conn_params_init(const ble_conn_params_init_t * p_init)
{
    ret_code_t err_code;

    VERIFY_PARAM_NOT_NULL(p_init);

    m_conn_params_config = *p_init;
    m_conn_params_config.p_conn_params = &m_preferred_conn_params;

    if (p_init->p_conn_params != NULL)
    {
        // Set the connection params in stack.
        err_code = sd_ble_gap_ppcp_set(p_init->p_conn_params);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        m_preferred_conn_params = *p_init->p_conn_params;
    }
    else
    {
        // Get the (default) connection params from stack.
        err_code = sd_ble_gap_ppcp_get(&m_preferred_conn_params);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    //lint -save -e681 "Loop not entered" when NRF_BLE_CONN_PARAMS_INSTANCE_COUNT is 0
    for (uint32_t i = 0; i < NRF_BLE_CONN_PARAMS_INSTANCE_COUNT; i++)
    {
        ble_conn_params_instance_t * p_instance = &m_conn_params_instances[i];

        instance_free(p_instance);
        p_instance->timer_id = &m_timer_data[i];

        err_code = app_timer_create(&p_instance->timer_id,
                            APP_TIMER_MODE_SINGLE_SHOT,
                            update_timeout_handler);
        if (err_code != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }
    }
    //lint -restore

    return NRF_SUCCESS;
}


ret_code_t ble_conn_params_stop(void)
{
    ret_code_t err_code;

    //lint -save -e681 "Loop not entered" when NRF_BLE_CONN_PARAMS_INSTANCE_COUNT is 0
    for (uint32_t i = 0; i < NRF_BLE_CONN_PARAMS_INSTANCE_COUNT; i++)
        {
        err_code = app_timer_stop(m_conn_params_instances[i].timer_id);
        switch (err_code)
            {
            case NRF_SUCCESS:
                /* do nothing */
                break;

            case NRF_ERROR_INVALID_STATE:
                /* do nothing */
                break;

            case NRF_ERROR_NO_MEM:
                return NRF_ERROR_BUSY;

            case NRF_ERROR_INVALID_PARAM:
                /* fallthrough */
            default:
                return NRF_ERROR_INTERNAL;
            }
        }
    //lint -restore
    return NRF_SUCCESS;
}


/**@brief Function for taking appropriate action based on the current state of connection parameters.
 *
 * @param[in]  conn_handle  Connection to handle.
 * @param[in]  p_instance   Configuration for the connection.
 */
static void conn_params_negotiation(uint16_t conn_handle, ble_conn_params_instance_t * p_instance)
        {
    // Start negotiation if the received connection parameters are not acceptable
    if (!p_instance->params_ok)
            {
        ret_code_t err_code;
        uint32_t   timeout_ticks;

        if (p_instance->update_count == 0)
        {
                // First connection parameter update
                timeout_ticks = m_conn_params_config.first_conn_params_update_delay;
            }
            else
            {
                timeout_ticks = m_conn_params_config.next_conn_params_update_delay;
            }

        err_code = app_timer_start(p_instance->timer_id, timeout_ticks, (void *)(uint32_t)conn_handle);
        if (err_code != NRF_SUCCESS)
            {
            send_error_evt(err_code);
            }
        }
    else
    {
        p_instance->update_count = 0;

        // Notify the application that the procedure has succeeded
        if (m_conn_params_config.evt_handler != NULL)
        {
            ble_conn_params_evt_t evt;

            evt.evt_type = BLE_CONN_PARAMS_EVT_SUCCEEDED;
            evt.conn_handle = conn_handle;
            m_conn_params_config.evt_handler(&evt);
        }
    }
}


/**@brief Function for handling a connection event from the SoftDevice.
 *
 * @param[in]  p_ble_evt  Event from the SoftDevice.
 */
static void on_connect(ble_evt_t const * p_ble_evt)
{
    uint8_t  role        = p_ble_evt->evt.gap_evt.params.connected.role;
    uint16_t conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

    if (role != BLE_GAP_ROLE_PERIPH)
    {
        return;
    }

    ble_conn_params_instance_t * p_instance  = instance_get(BLE_CONN_HANDLE_INVALID);

    if (p_instance == NULL)
    {
        send_error_evt(NRF_ERROR_NO_MEM);
        return;
    }

    instance_claim(p_instance, conn_handle);
    p_instance->params_ok = is_conn_params_ok(&p_instance->preferred_conn_params,
                                              &p_ble_evt->evt.gap_evt.params.connected.conn_params,
                                              NRF_BLE_CONN_PARAMS_MAX_SLAVE_LATENCY_DEVIATION,
                                              NRF_BLE_CONN_PARAMS_MAX_SUPERVISION_TIMEOUT_DEVIATION);

    // Check if we shall handle negotiation on connect
    if (m_conn_params_config.start_on_notify_cccd_handle == BLE_GATT_HANDLE_INVALID)
    {
        conn_params_negotiation(conn_handle, p_instance);
    }
}


/**@brief Function for handling a disconnection event from the SoftDevice.
 *
 * @param[in]  p_ble_evt  Event from the SoftDevice.
 */
static void on_disconnect(ble_evt_t const * p_ble_evt)
{
    ret_code_t                   err_code;
    uint16_t                     conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
    ble_conn_params_instance_t * p_instance  = instance_get(conn_handle);

    if (p_instance != NULL)
    {
    // Stop timer if running
        err_code = app_timer_stop(p_instance->timer_id);
        if (err_code != NRF_SUCCESS)
        {
            send_error_evt(err_code);
        }

        instance_free(p_instance);
    }
}


/**@brief Function for handling a GATT write event from the SoftDevice.
 *
 * @details To provide the start_on_notify_cccd_handle functionality.
 *
 * @param[in]  p_ble_evt  Event from the SoftDevice.
 */
static void on_write(ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    // Check if this is the correct CCCD
    if (
        (p_evt_write->handle == m_conn_params_config.start_on_notify_cccd_handle)
        &&
        (p_evt_write->len == 2)
       )
    {
        uint16_t                     conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
        ble_conn_params_instance_t * p_instance  = instance_get(conn_handle);

        if (p_instance != NULL)
        {
            // Check if this is a 'start notification'
            if (ble_srv_is_notification_enabled(p_evt_write->data))
            {
                // Do connection parameter negotiation if necessary
                    conn_params_negotiation(conn_handle, p_instance);
            }
            else
            {
                ret_code_t err_code;

                // Stop timer if running
                err_code = app_timer_stop(p_instance->timer_id);
                if (err_code != NRF_SUCCESS)
                {
                    send_error_evt(err_code);
                }
            }
        }
    }
}


/**@brief Function for handling a connection parameter update event from the SoftDevice.
 *
 * @details This event means the peer central has changed the connection parameters or declined our
 *          request.
 *
 * @param[in]  p_ble_evt  Event from the SoftDevice.
 */
static void on_conn_params_update(ble_evt_t const * p_ble_evt)
{
    uint16_t                     conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
    ble_conn_params_instance_t * p_instance  = instance_get(conn_handle);

    if (p_instance != NULL)
    {
        p_instance->params_ok = is_conn_params_ok(
                                     &p_instance->preferred_conn_params,
                                     &p_ble_evt->evt.gap_evt.params.conn_param_update.conn_params,
                                     NRF_BLE_CONN_PARAMS_MAX_SLAVE_LATENCY_DEVIATION,
                                     NRF_BLE_CONN_PARAMS_MAX_SUPERVISION_TIMEOUT_DEVIATION);

        conn_params_negotiation(conn_handle, p_instance);
    }
}


/**
 * @brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt       Event received from the BLE stack.
 * @param[in]   p_context       Context.
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_ble_evt);
            break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
            on_conn_params_update(p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


ret_code_t ble_conn_params_change_conn_params(uint16_t                conn_handle,
                                              ble_gap_conn_params_t * p_new_params)
{
    ret_code_t                   err_code   = BLE_ERROR_INVALID_CONN_HANDLE;
    ble_conn_params_instance_t * p_instance = instance_get(conn_handle);

    if (p_new_params == NULL)
    {
        p_new_params = &m_preferred_conn_params;
    }

    if (p_instance != NULL)
    {
        // Send request to central.
        err_code = sd_ble_gap_conn_param_update(conn_handle, p_new_params);
        if (err_code == NRF_SUCCESS)
        {
            p_instance->params_ok             = false;
            p_instance->update_count          = 1;
            p_instance->preferred_conn_params = *p_new_params;
        }
    }

    return err_code;
}

NRF_SDH_BLE_OBSERVER(m_ble_observer, BLE_CONN_PARAMS_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);

#endif //ENABLED
