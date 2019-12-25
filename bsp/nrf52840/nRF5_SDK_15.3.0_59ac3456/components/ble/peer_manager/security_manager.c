/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(PEER_MANAGER)
#include "security_manager.h"

#include <string.h>
#include "ble_err.h"
#include "security_dispatcher.h"
#include "peer_database.h"
#include "ble_conn_state.h"
#include "id_manager.h"
#include "sdk_common.h"

#if PM_LESC_ENABLED
#include "nrf_ble_lesc.h"
#endif
#define NRF_LOG_MODULE_NAME peer_manager_sm
#if PM_LOG_ENABLED
    #define NRF_LOG_LEVEL       PM_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  PM_LOG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR PM_LOG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // PM_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_strerror.h"


// The number of registered event handlers.
#define SM_EVENT_HANDLERS_CNT       (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))


// Security Manager event handler in Peer Manager.
extern void pm_sm_evt_handler(pm_evt_t * p_sm_evt);

// Security Manager events' handlers.
// The number of elements in this array is SM_EVENT_HANDLERS_CNT.
static pm_evt_handler_internal_t const m_evt_handlers[] =
{
    pm_sm_evt_handler
};


// The context type that is used in PM_EVT_CONN_SEC_PARAMS_REQ events and in calls to sm_sec_params_reply().
typedef struct
{
    ble_gap_sec_params_t * p_sec_params;         //!< The security parameters to use in the call to the security_dispatcher
    ble_gap_sec_params_t   sec_params_mem;       //!< The buffer for holding the security parameters.
    bool                   params_reply_called;  //!< Whether @ref sm_sec_params_reply has been called for this context instance.
} sec_params_reply_context_t;

static bool                            m_module_initialized;      //!< Whether the Security Manager module has been initialized.

static ble_gap_sec_params_t            m_sec_params;              //!< The buffer for the default security parameters set by @ref sm_sec_params_set.
static ble_gap_sec_params_t          * mp_sec_params = NULL;      //!< The default security parameters set by @ref sm_sec_params_set.
static bool                            m_sec_params_set = false;  //!< Whether @ref sm_sec_params_set has been called.

#if PM_LESC_ENABLED == 0
static ble_gap_lesc_p256_pk_t        * m_p_public_key;            //!< Pointer, provided by the user, to the public key to use for LESC procedures.
#endif

static ble_conn_state_user_flag_id_t   m_flag_link_secure_pending_busy        = BLE_CONN_STATE_USER_FLAG_INVALID;  //!< User flag indicating whether a connection has a pending call to @ref sm_link_secure because it returned @ref NRF_ERROR_BUSY.
static ble_conn_state_user_flag_id_t   m_flag_link_secure_force_repairing     = BLE_CONN_STATE_USER_FLAG_INVALID;  //!< User flag indicating whether a pending call to @ref sm_link_secure should be called with true for the force_repairing parameter.
static ble_conn_state_user_flag_id_t   m_flag_link_secure_null_params         = BLE_CONN_STATE_USER_FLAG_INVALID;  //!< User flag indicating whether a pending call to @ref sm_link_secure should be called with NULL security parameters.
static ble_conn_state_user_flag_id_t   m_flag_params_reply_pending_busy       = BLE_CONN_STATE_USER_FLAG_INVALID;  //!< User flag indicating whether a connection has a pending call to @ref sm_sec_params_reply because it returned @ref NRF_ERROR_BUSY.


/**@brief Function for sending an SM event to all registered event handlers.
 *
 * @param[in]  p_event  The event to send.
 */
static void evt_send(pm_evt_t * p_event)
{
    for (uint32_t i = 0; i < SM_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}


/**@brief Function for setting or clearing user flags based on error codes returned from @ref
 *        smd_link_secure or @ref smd_params_reply.
 *
 * @param[in]  conn_handle   The connection the call pertained to.
 * @param[in]  err_code      The error code returned from @ref smd_link_secure or
 *                           @ref smd_params_reply.
 * @param[in]  params_reply  Whether the call was to @ref smd_params_reply.
 */
static void flags_set_from_err_code(uint16_t conn_handle, ret_code_t err_code, bool params_reply)
{
    bool flag_value_busy       = false;

    if (err_code == NRF_ERROR_BUSY)
    {
        flag_value_busy       = true;
    }
    else
    {
        flag_value_busy       = false;
    }

    if (params_reply)
    {
        ble_conn_state_user_flag_set(conn_handle,
                                     m_flag_params_reply_pending_busy,
                                     flag_value_busy);
        ble_conn_state_user_flag_set(conn_handle,
                                     m_flag_link_secure_pending_busy,
                                     false);
    }
    else
    {
        ble_conn_state_user_flag_set(conn_handle,
                                     m_flag_link_secure_pending_busy,
                                     flag_value_busy);
    }
}


/**@brief Function for sending an event based on error codes returned from @ref smd_link_secure or
 *        @ref smd_params_reply.
 *
 * @param[in]  conn_handle   The connection the event pertains to.
 * @param[in]  err_code      The error code returned from @ref smd_link_secure or
 *                           @ref smd_params_reply.
 * @param[in]  p_sec_params  The security parameters attempted to pass in the call to
 *                           @ref smd_link_secure or @ref smd_params_reply.
 */
static void events_send_from_err_code(uint16_t               conn_handle,
                                      ret_code_t             err_code,
                                      ble_gap_sec_params_t * p_sec_params)
{
    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY) && (err_code != NRF_ERROR_INVALID_STATE))
    {
        pm_evt_t evt =
        {
            .conn_handle = conn_handle,
            .peer_id = im_peer_id_get_by_conn_handle(conn_handle),
        };
        if (err_code == NRF_ERROR_TIMEOUT)
        {
            NRF_LOG_WARNING("Cannot secure link because a previous security procedure ended in timeout. "\
                            "Disconnect and retry. smd_params_reply() or smd_link_secure() returned "\
                            "NRF_ERROR_TIMEOUT. conn_handle: %d",
                            conn_handle);
            evt.evt_id = PM_EVT_CONN_SEC_FAILED;
            evt.params.conn_sec_failed.procedure = ((p_sec_params != NULL) && p_sec_params->bond)
                                                 ? PM_CONN_SEC_PROCEDURE_BONDING
                                                 : PM_CONN_SEC_PROCEDURE_PAIRING;
            evt.params.conn_sec_failed.error_src = BLE_GAP_SEC_STATUS_SOURCE_LOCAL;
            evt.params.conn_sec_failed.error     = PM_CONN_SEC_ERROR_SMP_TIMEOUT;
        }
        else
        {
            NRF_LOG_ERROR("Could not perform security procedure. smd_params_reply() or "\
                          "smd_link_secure() returned %s. conn_handle: %d",
                          nrf_strerror_get(err_code),
                          conn_handle);
            evt.evt_id = PM_EVT_ERROR_UNEXPECTED;
            evt.params.error_unexpected.error     = err_code;
            evt.params.error_unexpected.fds_error = false;
        }
        evt_send(&evt);
    }
}


/**@brief Function for sending an PM_EVT_CONN_SEC_PARAMS_REQ event.
 *
 * @param[in]  conn_handle    The connection the event pertains to.
 * @param[in]  p_peer_params  The peer's security parameters to include in the event. Can be NULL.
 * @param[in]  p_context      Pointer to a context that the user must include in the call to @ref
 *                            sm_sec_params_reply().
 */
static void params_req_send(uint16_t                     conn_handle,
                            ble_gap_sec_params_t const * p_peer_params,
                            sec_params_reply_context_t * p_context)
{
    pm_evt_t evt;
    evt.evt_id                                   = PM_EVT_CONN_SEC_PARAMS_REQ;
    evt.conn_handle                              = conn_handle;
    evt.peer_id                                  = im_peer_id_get_by_conn_handle(conn_handle);
    evt.params.conn_sec_params_req.p_peer_params = p_peer_params;
    evt.params.conn_sec_params_req.p_context     = p_context;

    evt_send(&evt);
}


/**@brief Function for creating a new @ref sec_params_reply_context_t with the correct initial values.
 *
 * @return  The new context.
 */
static sec_params_reply_context_t new_context_get(void)
{
    sec_params_reply_context_t new_context =
    {
        .p_sec_params = mp_sec_params,
        .params_reply_called = false
    };
    return new_context;
}


/**@brief Internal function corresponding to @ref sm_link_secure.
 *
 * @param[in]  conn_handle      The connection to secure.
 * @param[in]  null_params      Whether to pass NULL security parameters to the security_dispatcher.
 * @param[in]  force_repairing  Whether to force rebonding if peer exists.
 * @param[in]  send_events      Whether to send events based on the result of @ref smd_link_secure.
 *
 * @return  Same return codes as @ref sm_link_secure.
 */
static ret_code_t link_secure(uint16_t conn_handle,
                              bool     null_params,
                              bool     force_repairing,
                              bool     send_events)
{
    ret_code_t             err_code;
    ret_code_t             return_err_code;
    ble_gap_sec_params_t * p_sec_params;

    if (null_params)
    {
        p_sec_params = NULL;
    }
    else
    {
        sec_params_reply_context_t context = new_context_get();
        params_req_send(conn_handle, NULL, &context);
        p_sec_params = context.p_sec_params;

        if (!m_sec_params_set && !context.params_reply_called)
        {
            // Security parameters have not been set.
            return NRF_ERROR_NOT_FOUND;
        }
    }


    err_code = smd_link_secure(conn_handle, p_sec_params, force_repairing);

    flags_set_from_err_code(conn_handle, err_code, false);

    switch (err_code)
    {
        case NRF_ERROR_BUSY:
            ble_conn_state_user_flag_set(conn_handle, m_flag_link_secure_null_params, null_params);
            ble_conn_state_user_flag_set(conn_handle, m_flag_link_secure_force_repairing, force_repairing);
            return_err_code = NRF_SUCCESS;
            break;
        case NRF_SUCCESS:
        case NRF_ERROR_TIMEOUT:
        case BLE_ERROR_INVALID_CONN_HANDLE:
        case NRF_ERROR_INVALID_STATE:
        case NRF_ERROR_INVALID_DATA:
            return_err_code = err_code;
            break;
        default:
            NRF_LOG_ERROR("Could not perform security procedure. smd_link_secure() returned %s. "\
                          "conn_handle: %d",
                          nrf_strerror_get(err_code),
                          conn_handle);
            return_err_code = NRF_ERROR_INTERNAL;
            break;
    }

    if (send_events)
    {
        events_send_from_err_code(conn_handle, err_code, p_sec_params);
    }

    return return_err_code;
}


/**@brief Function for requesting security parameters from the user and passing them to the security_dispatcher.
 *
 * @param[in]  conn_handle    The connection that needs security parameters.
 * @param[in]  p_peer_params  The peer's security parameters if present. Otherwise NULL.
 */
static void smd_params_reply_perform(uint16_t conn_handle, ble_gap_sec_params_t const * p_peer_params)
{
    ret_code_t                 err_code;
    ble_gap_lesc_p256_pk_t   * p_public_key;
    sec_params_reply_context_t context = new_context_get();

    params_req_send(conn_handle, p_peer_params, &context);

#if PM_LESC_ENABLED
    p_public_key = nrf_ble_lesc_public_key_get();
#else
    p_public_key = m_p_public_key;
#endif // PM_LESC_ENABLED
    err_code = smd_params_reply(conn_handle, context.p_sec_params, p_public_key);

    flags_set_from_err_code(conn_handle, err_code, true);
    events_send_from_err_code(conn_handle, err_code, context.p_sec_params);
}


/**@brief Function for handling @ref PM_EVT_CONN_SEC_PARAMS_REQ events.
 *
 * @param[in]  p_event  The @ref PM_EVT_CONN_SEC_PARAMS_REQ event.
 */
static __INLINE void params_req_process(pm_evt_t const * p_event)
{
    smd_params_reply_perform(p_event->conn_handle, p_event->params.conn_sec_params_req.p_peer_params);
}


/**@brief Function for handling @ref PM_EVT_SLAVE_SECURITY_REQ events.
 *
 * @param[in]  p_event  The @ref PM_EVT_SLAVE_SECURITY_REQ event.
 */
static void sec_req_process(pm_evt_t const * p_event)
{
    bool null_params = false;
    if (mp_sec_params == NULL)
    {
        null_params = true;
    }
    else if ((bool)m_sec_params.bond < (bool)p_event->params.slave_security_req.bond)
    {
        null_params = true;
    }
    else if ((bool)m_sec_params.mitm < (bool)p_event->params.slave_security_req.mitm)
    {
        null_params = true;
    }
    else
    {
        // No action.
    }
    ret_code_t err_code = link_secure(p_event->conn_handle, null_params, false, true);
    UNUSED_VARIABLE(err_code); // It is acceptable to ignore the return code because it is
                               // acceptable to ignore a security request.
}


/**@brief Function for translating an SMD event to an SM event and passing it on to SM event handlers.
 *
 * @param[in]  p_event  The event to forward.
 */
static void evt_forward(pm_evt_t * p_event)
{
    evt_send(p_event);
}


/**@brief Event handler for events from the Security Dispatcher module.
 *        This handler is extern in Security Dispatcher.
 *
 * @param[in]  p_event   The event that has happened.
 */
void sm_smd_evt_handler(pm_evt_t * p_event)
{
    switch (p_event->evt_id)
    {
        case PM_EVT_CONN_SEC_PARAMS_REQ:
            params_req_process(p_event);
            break;
        case PM_EVT_SLAVE_SECURITY_REQ:
            sec_req_process(p_event);
            /* fallthrough */
        default:
            // Forward the event to all registered Security Manager event handlers.
            evt_forward(p_event);
            break;
    }
}


/**@brief Function handling a pending params_reply. See @ref ble_conn_state_user_function_t.
 */
static void params_reply_pending_handle(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);
    smd_params_reply_perform(conn_handle, NULL);
}


/**@brief Function handling a pending link_secure. See @ref ble_conn_state_user_function_t.
 */
static void link_secure_pending_handle(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    bool force_repairing = ble_conn_state_user_flag_get(conn_handle, m_flag_link_secure_force_repairing);
    bool null_params     = ble_conn_state_user_flag_get(conn_handle, m_flag_link_secure_null_params);

    // If this fails, it will be automatically retried.
    ret_code_t err_code = link_secure(conn_handle, null_params, force_repairing, true);
    UNUSED_VARIABLE(err_code);
}


/**@brief Event handler for events from the Peer Database module.
 *        This handler is extern in Peer Database.
 *
 * @param[in]  p_event   The event that has happened.
 */
void sm_pdb_evt_handler(pm_evt_t * p_event)
{
    switch (p_event->evt_id)
    {
        case PM_EVT_FLASH_GARBAGE_COLLECTED:
        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
        case PM_EVT_PEER_DATA_UPDATE_FAILED:
        case PM_EVT_PEER_DELETE_SUCCEEDED:
        case PM_EVT_PEER_DELETE_FAILED:
            (void) ble_conn_state_for_each_set_user_flag(m_flag_params_reply_pending_busy,
                                                         params_reply_pending_handle,
                                                         NULL);
            (void) ble_conn_state_for_each_set_user_flag(m_flag_link_secure_pending_busy,
                                                         link_secure_pending_handle,
                                                         NULL);
            break;
        default:
            // Do nothing.
            break;
    }
}


/**@brief Funtion for initializing a BLE Connection State user flag.
 *
 * @param[out] flag_id  The flag to initialize.
 */
static void flag_id_init(ble_conn_state_user_flag_id_t * p_flag_id)
{
    if (*p_flag_id == BLE_CONN_STATE_USER_FLAG_INVALID)
    {
        *p_flag_id = ble_conn_state_user_flag_acquire();
    }
}


ret_code_t sm_init(void)
{
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

#if PM_LESC_ENABLED
    ret_code_t err_code = nrf_ble_lesc_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
#endif

    flag_id_init(&m_flag_link_secure_pending_busy);
    flag_id_init(&m_flag_link_secure_force_repairing);
    flag_id_init(&m_flag_link_secure_null_params);
    flag_id_init(&m_flag_params_reply_pending_busy);

    if (m_flag_params_reply_pending_busy == BLE_CONN_STATE_USER_FLAG_INVALID)
    {
        NRF_LOG_ERROR("Could not acquire conn_state user flags. Increase "\
                      "BLE_CONN_STATE_USER_FLAG_COUNT in the ble_conn_state module.");
        return NRF_ERROR_INTERNAL;
    }

    m_module_initialized = true;

    return NRF_SUCCESS;
}


void sm_ble_evt_handler(ble_evt_t const * p_ble_evt)
{
    NRF_PM_DEBUG_CHECK(p_ble_evt != NULL);

    smd_ble_evt_handler(p_ble_evt);
#if PM_LESC_ENABLED
    nrf_ble_lesc_on_ble_evt(p_ble_evt);
#endif
    (void) ble_conn_state_for_each_set_user_flag(m_flag_params_reply_pending_busy,
                                                 params_reply_pending_handle,
                                                 NULL);
    (void) ble_conn_state_for_each_set_user_flag(m_flag_link_secure_pending_busy,
                                                 link_secure_pending_handle,
                                                 NULL);
}


/**@brief Funtion for checking whether security parameters are valid.
 *
 * @param[out] p_sec_params  The security parameters to verify.
 *
 * @return  Whether the security parameters are valid.
 */
static bool sec_params_verify(ble_gap_sec_params_t * p_sec_params)
{
    // NULL check.
    if (p_sec_params == NULL)
    {
        return false;
    }

    // OOB not allowed unless MITM.
    if (!p_sec_params->mitm && p_sec_params->oob)
    {
        return false;
    }

    // IO Capabilities must be one of the valid values from @ref BLE_GAP_IO_CAPS.
    if (p_sec_params->io_caps > BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY)
    {
        return false;
    }

    // Must have either IO capabilities or OOB if MITM.
    if (p_sec_params->mitm && (p_sec_params->io_caps == BLE_GAP_IO_CAPS_NONE) && !p_sec_params->oob)
    {
        return false;
    }

    // Minimum key size cannot be larger than maximum key size.
    if (p_sec_params->min_key_size > p_sec_params->max_key_size)
    {
        return false;
    }

    // Key size cannot be below 7 bytes.
    if (p_sec_params->min_key_size < 7)
    {
        return false;
    }

    // Key size cannot be above 16 bytes.
    if (p_sec_params->max_key_size > 16)
    {
        return false;
    }

    // Signing is not supported.
    if (p_sec_params->kdist_own.sign || p_sec_params->kdist_peer.sign)
    {
        return false;
    }

    // link bit must be 0.
    if (p_sec_params->kdist_own.link || p_sec_params->kdist_peer.link)
    {
        return false;
    }

    // If bonding is not enabled, no keys can be distributed.
    if (!p_sec_params->bond && (   p_sec_params->kdist_own.enc
                                || p_sec_params->kdist_own.id
                                || p_sec_params->kdist_peer.enc
                                || p_sec_params->kdist_peer.id))
    {
        return false;
    }

    // If bonding is enabled, one or more keys must be distributed.
    if (    p_sec_params->bond
        && !p_sec_params->kdist_own.enc
        && !p_sec_params->kdist_own.id
        && !p_sec_params->kdist_peer.enc
        && !p_sec_params->kdist_peer.id)
    {
        return false;
    }

    return true;
}


ret_code_t sm_sec_params_set(ble_gap_sec_params_t * p_sec_params)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    if (p_sec_params == NULL)
    {
        mp_sec_params    = NULL;
        m_sec_params_set = true;
        return NRF_SUCCESS;
    }
    else if (sec_params_verify(p_sec_params))
    {
        m_sec_params     = *p_sec_params;
        mp_sec_params    = &m_sec_params;
        m_sec_params_set = true;
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }
}


void sm_conn_sec_config_reply(uint16_t conn_handle, pm_conn_sec_config_t * p_conn_sec_config)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_conn_sec_config != NULL);

    smd_conn_sec_config_reply(conn_handle, p_conn_sec_config);
}


ret_code_t sm_sec_params_reply(uint16_t               conn_handle,
                               ble_gap_sec_params_t * p_sec_params,
                               void           const * p_context)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    VERIFY_PARAM_NOT_NULL(p_context);

    sec_params_reply_context_t * p_sec_params_reply_context = (sec_params_reply_context_t *)p_context;
    if (p_sec_params == NULL)
    {
        // Set the store pointer to NULL, so that NULL is passed to the SoftDevice.
        p_sec_params_reply_context->p_sec_params = NULL;
    }
    else if (sec_params_verify(p_sec_params))
    {
        // Copy the provided sec_params into the store.
        p_sec_params_reply_context->sec_params_mem = *p_sec_params;
        p_sec_params_reply_context->p_sec_params   = &p_sec_params_reply_context->sec_params_mem;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    p_sec_params_reply_context->params_reply_called = true;

    return NRF_SUCCESS;
}


ret_code_t sm_lesc_public_key_set(ble_gap_lesc_p256_pk_t * p_public_key)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

#if PM_LESC_ENABLED
    return NRF_ERROR_FORBIDDEN;
#else
    m_p_public_key = p_public_key;

    return NRF_SUCCESS;
#endif // PM_LESC_ENABLED
}


ret_code_t sm_link_secure(uint16_t conn_handle, bool force_repairing)
{
    ret_code_t ret;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    ret = link_secure(conn_handle, false, force_repairing, false);
    return ret;
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
