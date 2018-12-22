/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef SECURITY_DISPATCHER_H__
#define SECURITY_DISPATCHER_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "ble.h"
#include "ble_gap.h"
#include "peer_manager_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @defgroup security_dispatcher Security Dispatcher
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for streamlining pairing, bonding, and
 *        encryption, including flash storage of shared data.
 *
 */


/**@brief Events that can come from the Security Dispatcher module.
 */
typedef enum
{
    SMD_EVT_PARAMS_REQ,             /**< Parameters are required for a pairing procedure on the specified connection. The user must provide them using @ref smd_params_reply. */
    SMD_EVT_SLAVE_SECURITY_REQ,     /**< The peer (slave) has requested link encryption. Call @ref smd_link_secure to honor the request. The data in the event structure must be used in the parameters. */
    SMD_EVT_SEC_PROCEDURE_START,    /**< A security procedure has started. */
    SMD_EVT_PAIRING_SUCCESS,        /**< A pairing procedure (and bonding if applicable) has completed with success. */
    SMD_EVT_PAIRING_FAIL,           /**< A pairing procedure has failed which means no encryption and no bond could be established. */
    SMD_EVT_LINK_ENCRYPTION_UPDATE, /**< The security level of the link has been updated. The link is encrypted. */
    SMD_EVT_LINK_ENCRYPTION_FAILED, /**< An attempt to start encryption on an unencrypted link failed because the peripheral did not have the correct keys. If the peer is the peripheral, the force_repairing flag should be set when reattempting @ref smd_link_secure. */
    SMD_EVT_BONDING_INFO_STORED,    /**< Information exchanged during bonding with a peer has been stored persistently. */
    SMD_EVT_ERROR_BONDING_INFO,     /**< Information exchanged during bonding with a peer could not be stored persistently, because of an unexpected error. */
    // SMD_EVT_ERROR_NO_MEM,           /**< An operation failed because there was no available storage room in persistent storage. Please free up room, and the operation will automatically continue. */
    SMD_EVT_ERROR_UNEXPECTED,       /**< An operation failed with an unexpected error. The error is provided. This is possibly a fatal error. */
} smd_evt_id_t;


/**@brief Events parameters specific to the @ref SMD_EVT_SLAVE_SECURITY_REQ event.
 */
typedef struct
{
    bool bond;
    bool mitm;
} smd_evt_slave_security_req_t;


/**@brief Events parameters specific to the @ref SMD_EVT_SEC_PROCEDURE_START event.
 */
typedef struct
{
    pm_conn_sec_procedure_t procedure; /**< The procedure that has started. */
} smd_evt_sec_procedure_start_t;


/**@brief Events parameters specific to the @ref SMD_EVT_PAIRING_SUCCESS event.
 */
typedef struct
{
    bool                bonded;     /**< Whether bonding was performed. */
    bool                mitm;       /**< Whether MITM protection was used during pairing. */
    ble_gap_sec_kdist_t kdist_own;  /**< Which keys were distributed to the peer. Only relevant if bonding was performed. */
    ble_gap_sec_kdist_t kdist_peer; /**< Which keys were distributed by the peer. Only relevant if bonding was performed. */
} smd_evt_pairing_success_t;


/**@brief Events parameters specific to the @ref SMD_EVT_PAIRING_FAIL event.
 */
typedef struct
{
    pm_sec_error_code_t error;     /**< What went wrong. */
    uint8_t             error_src; /**< The party that raised the error, see @ref BLE_GAP_SEC_STATUS_SOURCES. */
} smd_evt_pairing_failed_t;


/**@brief Events parameters specific to the @ref SMD_EVT_LINK_ENCRYPTION_UPDATE event.
 */
typedef struct
{
    bool mitm_protected;  /**< Whether the link is now MITM protected. */
} smd_evt_link_encryption_update_t;


/**@brief Events parameters specific to the @ref SMD_EVT_LINK_ENCRYPTION_FAILED event.
 */
typedef struct
{
    pm_sec_error_code_t error;     /**< What went wrong. */
    uint8_t             error_src; /**< The party that raised the error, see @ref BLE_GAP_SEC_STATUS_SOURCES. */
} smd_evt_link_encryption_failed_t;


/**@brief Events parameters specific to the @ref SMD_EVT_BONDING_INFO_STORED event.
 */
typedef struct
{
    pm_peer_id_t peer_id; /**< The peer this event pertains to. */
} smd_evt_bonding_info_stored_t;


/**@brief Events parameters specific to the @ref SMD_EVT_ERROR_BONDING_INFO event.
 */
typedef struct
{
    pm_peer_id_t peer_id; /**< The peer this event pertains to, if previously bonded. @ref PM_PEER_ID_INVALID if no successful bonding has happened with the peer before. */
    ret_code_t   error;   /**< The unexpected error that occurred. */
} smd_evt_error_bonding_info_t;


// typedef struct
// {
    // pm_peer_id_t peer_id; /**< The peer this event pertains to. */
// } smd_evt_error_no_mem_t;


/**@brief Events parameters specific to the @ref SMD_EVT_ERROR_UNEXPECTED event.
 */
typedef struct
{
    ret_code_t error; /**< The unexpected error that occurred. */
} smd_evt_error_unexpected_t;


typedef union
{
    smd_evt_slave_security_req_t     slave_security_req;
    smd_evt_sec_procedure_start_t    sec_procedure_start;
    smd_evt_pairing_success_t        pairing_success;
    smd_evt_pairing_failed_t         pairing_failed;
    smd_evt_link_encryption_update_t link_encryption_update;
    smd_evt_link_encryption_failed_t link_encryption_failed;
    smd_evt_bonding_info_stored_t    bonding_info_stored;
    smd_evt_error_bonding_info_t     error_bonding_info;
    //  smd_evt_error_no_mem_t          error_no_mem;
    smd_evt_error_unexpected_t       error_unexpected;
} smd_evt_params_t; /**< Event specific parameters. Chosen based on evt_id. */


/**@brief Structure describing events from the Security Dispatcher module.
 */
typedef struct
{
    smd_evt_id_t evt_id;     /**< The type of event. */
    uint16_t conn_handle;    /**< The connection this event pertains to. */
    smd_evt_params_t params; /**< Event specific parameters. Chosen based on evt_id. */
} smd_evt_t;



/**@brief Event handler for events from the Security Dispatcher module.
 *
 * @param[in]  p_event  The event that has happened.
 */
typedef void (*smd_evt_handler_t)(smd_evt_t const * p_event);


#if 0
/**@brief Function for registering with the Security Dispatcher module. This function also
 *        initializes the module if uninitialized.
 *
 * @param[in]  evt_handler  Callback for events from the Security Dispatcher module.
 *
 * @retval NRF_SUCCESS       Registration was successful.
 * @retval NRF_ERROR_NO_MEM  No more registrations possible.
 * @retval NRF_ERROR_NULL    evt_handler was NULL.
 */
ret_code_t smd_register(smd_evt_handler_t evt_handler);
#endif


ret_code_t smd_init(void);


/**@brief Function for dispatching SoftDevice events to the Security Dispatcher module.
 *
 * @param[in]  ble_evt    The SoftDevice event.
 */
void smd_ble_evt_handler(ble_evt_t * ble_evt);


/**@brief Function for providing pairing and bonding parameters to use for the current pairing
 *        procedure on a connection.
 *
 * @note If this function returns an @ref NRF_ERROR_NULL, @ref NRF_ERROR_INVALID_PARAM, @ref
 *       BLE_ERROR_INVALID_CONN_HANDLE, or @ref NRF_ERROR_STORAGE_FULL, this function can be called
 *       again after corrective action.
 *
 * @note To reject a request, call this function with NULL p_sec_params.
 *
 * @param[in]  conn_handle   The connection handle of the connection the pairing is happening on.
 * @param[in]  p_sec_params  The security parameters to use for this link.
 * @param[in]  p_public_key  A pointer to the public key to use if using LESC, or NULL.
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_INVALID_STATE        Module is not initialized, or no parameters have been
 *                                        requested on that conn_handle, or this error originates
 *                                        from the SoftDevice.
 * @retval NRF_ERROR_INVALID_PARAM        Invalid combination of parameters (not including conn_handle).
 * @retval NRF_ERROR_TIMEOUT              There has been an SMP timeout, so no more SMP operations
 *                                        can be performed on this link.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @retval NRF_ERROR_STORAGE_FULL         No more room in flash. Fix and reattempt after the next
 *                                        FDS garbage collection procedure.
 * @retval NRF_ERROR_BUSY                 No write buffer. Reattempt later.
 */
ret_code_t smd_params_reply(uint16_t                 conn_handle,
                            ble_gap_sec_params_t   * p_sec_params,
                            ble_gap_lesc_p256_pk_t * p_public_key);


/**@brief Function for initiating security on the link, with the specified parameters.
 *
 * @note If the connection is a peripheral connection, this will send a security request to the
 *       master, but the master is not obligated to initiate pairing or encryption in response.
 * @note If the connection is a central connection and a key is available, the parameters will be
 *       used to determine whether to re-pair or to encrypt using the existing key. If no key is
 *       available, pairing will be started.
 *
 * @param[in]  conn_handle      Handle of the connection to initiate pairing on.
 * @param[in]  p_sec_params     The security parameters to use for this link. As a central, this can
 *                              be NULL to reject a slave security request.
 * @param[in]  force_repairing  Whether to force a pairing procedure to happen regardless of whether
 *                              an encryption key already exists. This argument is only relevant for
 *                              the central role. Recommended value: false
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_NULL                 p_sec_params was NULL (peripheral only).
 * @retval NRF_ERROR_INVALID_STATE        Module is not initialized, or this error originates from
 *                                        the SoftDevice.
 * @retval NRF_ERROR_INVALID_PARAM        Invalid combination of parameters (not including conn_handle).
 * @retval NRF_ERROR_BUSY                 Unable to initiate procedure at this time.
 * @retval NRF_ERROR_TIMEOUT              There has been an SMP timeout, so no more SMP operations
 *                                        can be performed on this link.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @retval NRF_ERROR_STORAGE_FULL         No more room in flash. Fix and reattempt after the next
 *                                        FDS garbage collection procedure.
 * @retval NRF_ERROR_INTERNAL             No more available peer IDs.
 */
ret_code_t smd_link_secure(uint16_t               conn_handle,
                           ble_gap_sec_params_t * p_sec_params,
                           bool                   force_repairing);

/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* SECURITY_DISPATCHER_H__ */
