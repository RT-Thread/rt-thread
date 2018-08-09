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
/**
 * @file peer_manager_types.h
 *
 * @addtogroup peer_manager
 * @{
 */

#ifndef PEER_MANAGER_TYPES_H__
#define PEER_MANAGER_TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "nrf.h"
#include "ble_gap.h"
#include "ble_hci.h"
#include "ble_gatt_db.h"
#include "app_util.h"
#include "app_util_platform.h"


#ifdef __cplusplus
extern "C" {
#endif


/**@brief Handle to uniquely identify a peer for which we have persistently stored data.
 */
typedef uint16_t pm_peer_id_t;

/**@brief Type that is used for write prepares (used to reserve space in flash).
 */
typedef uint32_t pm_prepare_token_t;

/**@brief Type that is used to hold a reference to a stored item in flash.
 */
typedef uint32_t pm_store_token_t;

/**@brief Errors from security procedures in Peer Manager.
 *
 * @details Possible values are defined in @ref PM_SEC_ERRORS and @ref BLE_GAP_SEC_STATUS.
 */
typedef uint16_t pm_sec_error_code_t;


//lint -emacro(516,PM_LOCAL_DB_LEN_OVERHEAD_BYTES)

#define PM_PEER_ID_INVALID              0xFFFF                                         /**< @brief Invalid value for @ref pm_peer_id_t. */
#define PM_STORE_TOKEN_INVALID          0                                              /**< @brief Invalid value for store token. */
#define PM_PEER_ID_N_AVAILABLE_IDS      256                                            /**< @brief The number of available peer IDs. */
#define PM_LOCAL_DB_LEN_OVERHEAD_BYTES  offsetof(pm_peer_data_local_gatt_db_t, data)   /**< @brief The static-length part of the local GATT data struct. */


#define PM_CONN_SEC_ERROR_BASE 0x1000  /**< @brief The base for Peer Manager defined errors. See @ref PM_SEC_ERRORS and @ref pm_sec_error_code_t. */


/**@defgroup PM_SEC_ERRORS Peer Manager defined security errors
 *
 * @details The first 256 numbers in this range correspond to the status codes in
 *          @ref BLE_HCI_STATUS_CODES.
 * @{ */
#define PM_CONN_SEC_ERROR_PIN_OR_KEY_MISSING (PM_CONN_SEC_ERROR_BASE + 0x06)  /**< @brief Encryption failed because the peripheral has lost the LTK for this bond. See also @ref BLE_HCI_STATUS_CODE_PIN_OR_KEY_MISSING and Table 3.7 ("Pairing Failed Reason Codes") in the Bluetooth Core Specification 4.2, section 3.H.3.5.5 (@linkBLEcore).  */
#define PM_CONN_SEC_ERROR_MIC_FAILURE        (PM_CONN_SEC_ERROR_BASE + 0x3D)  /**< @brief Encryption ended with disconnection because of mismatching keys or a stray packet during a procedure. See the SoftDevice GAP Message Sequence Charts on encryption (@linkBLEMSCgap), the Bluetooth Core Specification 4.2, sections 6.B.5.1.3.1 and 3.H.3.5.5 (@linkBLEcore), and @ref BLE_HCI_CONN_TERMINATED_DUE_TO_MIC_FAILURE. */
#define PM_CONN_SEC_ERROR_DISCONNECT         (PM_CONN_SEC_ERROR_BASE + 0x100) /**< @brief Pairing or encryption did not finish before the link disconnected for an unrelated reason. */
#define PM_CONN_SEC_ERROR_SMP_TIMEOUT        (PM_CONN_SEC_ERROR_BASE + 0x101) /**< @brief Pairing/bonding could not start because an SMP time-out has already happened on this link. This means that no more pairing or bonding can happen on this link. To be able to pair or bond, the link must be disconnected and then reconnected. See Bluetooth Core Specification 4.2 section 3.H.3.4 (@linkBLEcore). */
 /** @} */



/**@defgroup PM_PEER_ID_VERSIONS All versions of Peer IDs.
 * @brief The data ID for each iteration of the data formats in flash.
 * @details Each time the format (in flash) of a piece of peer data changes, the data ID will also
 *          be updated. This list of defines is a record of each data ID that has ever existed, and
 *          code that caters to legacy formats can find the relevant IDs here.
 * @{ */
#define PM_PEER_DATA_ID_FIRST_VX                   0     /**< @brief The smallest data ID. */
#define PM_PEER_DATA_ID_BONDING_V1                 0     /**< @brief The data ID of the first version of bonding data. */
#define PM_PEER_DATA_ID_BONDING_V2                 7     /**< @brief The data ID of the second version of bonding data. */
#define PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING_V1 1     /**< @brief The data ID of the first version of the service changed pending flag. */
#define PM_PEER_DATA_ID_GATT_LOCAL_V1              2     /**< @brief The data ID of the first version of local GATT data. */
#define PM_PEER_DATA_ID_GATT_LOCAL_V2              8     /**< @brief The data ID of the second version of local GATT data. */
#define PM_PEER_DATA_ID_GATT_REMOTE_V1             3     /**< @brief The data ID of the first version of remote GATT data. */
#define PM_PEER_DATA_ID_APPLICATION_V1             4     /**< @brief The data ID of the first version of application data. */
#define PM_PEER_DATA_ID_GATT_REMOTE_V2             5     /**< @brief The data ID of the second version of remote GATT data. */
#define PM_PEER_DATA_ID_PEER_RANK_V1               6     /**< @brief The data ID of the first version of the rank. */
#define PM_PEER_DATA_ID_LAST_VX                    9     /**< @brief The data ID after the last valid one. */
#define PM_PEER_DATA_ID_INVALID_VX                 0xFF  /**< @brief A data ID guaranteed to be invalid. */
/**@}*/


/**@brief The different types of data associated with a peer.
 */
typedef enum
{
    PM_PEER_DATA_ID_FIRST                   = PM_PEER_DATA_ID_FIRST_VX,                   /**< @brief The smallest data ID. */
    PM_PEER_DATA_ID_BONDING                 = PM_PEER_DATA_ID_BONDING_V2,                 /**< @brief The data ID for bonding data. Type: @ref pm_peer_data_bonding_t. */
    PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING = PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING_V1, /**< @brief The data ID for service changed state. Type: bool. */
    PM_PEER_DATA_ID_GATT_LOCAL              = PM_PEER_DATA_ID_GATT_LOCAL_V2,              /**< @brief The data ID for local GATT data (sys attributes). Type: @ref pm_peer_data_local_gatt_db_t. */
    PM_PEER_DATA_ID_GATT_REMOTE             = PM_PEER_DATA_ID_GATT_REMOTE_V2,             /**< @brief The data ID for remote GATT data. Type: uint8_t array. */
    PM_PEER_DATA_ID_PEER_RANK               = PM_PEER_DATA_ID_PEER_RANK_V1,               /**< @brief The data ID for peer rank. See @ref pm_peer_rank_highest. Type: uint32_t. */
    PM_PEER_DATA_ID_APPLICATION             = PM_PEER_DATA_ID_APPLICATION_V1,             /**< @brief The data ID for application data. Type: uint8_t array. */
    PM_PEER_DATA_ID_LAST                    = PM_PEER_DATA_ID_LAST_VX,                    /**< @brief One more than the highest data ID. */
    PM_PEER_DATA_ID_INVALID                 = PM_PEER_DATA_ID_INVALID_VX,                 /**< @brief A data ID guaranteed to be invalid. */
} pm_peer_data_id_t;


/**@brief Different procedures that can lead to an encrypted link.
 */
typedef enum
{
    PM_CONN_SEC_PROCEDURE_ENCRYPTION, /**< @brief Using an LTK that was shared during a previous bonding procedure to encrypt the link. */
    PM_CONN_SEC_PROCEDURE_BONDING,    /**< @brief A pairing procedure, followed by a bonding procedure. */
    PM_CONN_SEC_PROCEDURE_PAIRING,    /**< @brief A pairing procedure with no bonding. */
} pm_conn_sec_procedure_t;


/**@brief Configuration of a security procedure.
 */
typedef struct
{
    bool allow_repairing; /** @brief Whether to allow the peer to pair if it wants to, but is already bonded. If this is false, the procedure is rejected, and no more events are sent. Default: false. */
} pm_conn_sec_config_t;


/**@brief Data associated with a bond to a peer.
 */
typedef struct
{
    uint8_t           own_role;    /**< @brief The BLE role of the local device during bonding. See @ref BLE_GAP_ROLES. */
    ble_gap_id_key_t  peer_ble_id; /**< @brief The peer's Bluetooth address and identity resolution key (IRK). */
    ble_gap_enc_key_t peer_ltk;    /**< @brief The peer's long-term encryption key (LTK) and master ID. */
    ble_gap_enc_key_t own_ltk;     /**< @brief Locally generated long-term encryption key (LTK) and master ID, distributed to the peer. */
} pm_peer_data_bonding_t;


/**@brief Data on a local GATT database.
 */
typedef struct
{
    uint32_t flags;       /**< @brief Flags that describe the database attributes. */
    uint16_t len;         /**< @brief Size of the attribute array. */
    uint8_t  data[1];     /**< @brief Array to hold the database attributes. */
} pm_peer_data_local_gatt_db_t;


/**@brief Device Privacy.
 *
 *        The privacy feature provides a way for the device to avoid being tracked over a period of
 *        time. The privacy feature, when enabled, hides the local device identity and replaces it
 *        with a private address that is automatically refreshed at a specified interval.
 *
 *        If a device still wants to be recognized by other peers, it needs to share it's Identity
 *        Resolving Key (IRK). With this key, a device can generate a random private address that
 *        can only be recognized by peers in possession of that key, and devices can establish
 *        connections without revealing their real identities.
 *
 * @note  If the device IRK is updated, the new IRK becomes the one to be distributed in all
 *        bonding procedures performed after @ref sd_ble_gap_privacy_set returns.
 *        The IRK distributed during bonding procedure is the device IRK that is active when @ref
 *        sd_ble_gap_sec_params_reply is called.
 */
typedef ble_gap_privacy_params_t pm_privacy_params_t;


/**@brief Types of events that can come from the @ref peer_manager module.
 */
typedef enum
{
    PM_EVT_BONDED_PEER_CONNECTED,           /**< @brief A connected peer has been identified as one with which we have a bond. When performing bonding with a peer for the first time, this event will not be sent until a new connection is established with the peer. When we are central, this event is always sent when the Peer Manager receives the @ref BLE_GAP_EVT_CONNECTED event. When we are peripheral, this event might in rare cases arrive later. */
    PM_EVT_CONN_SEC_START,                  /**< @brief A security procedure has started on a link, initiated either locally or remotely. The security procedure is using the last parameters provided via @ref pm_sec_params_set. This event is always followed by either a @ref PM_EVT_CONN_SEC_SUCCEEDED or a @ref PM_EVT_CONN_SEC_FAILED event. This is an informational event; no action is needed for the procedure to proceed. */
    PM_EVT_CONN_SEC_SUCCEEDED,              /**< @brief A link has been encrypted, either as a result of a call to @ref pm_conn_secure or a result of an action by the peer. The event structure contains more information about the circumstances. This event might contain a peer ID with the value @ref PM_PEER_ID_INVALID, which means that the peer (central) used an address that could not be identified, but it used an encryption key (LTK) that is present in the database. */
    PM_EVT_CONN_SEC_FAILED,                 /**< @brief A pairing or encryption procedure has failed. In some cases, this means that security is not possible on this link (temporarily or permanently). How to handle this error depends on the application. */
    PM_EVT_CONN_SEC_CONFIG_REQ,             /**< @brief The peer (central) has requested pairing, but a bond already exists with that peer. Reply by calling @ref pm_conn_sec_config_reply before the event handler returns. If no reply is sent, a default is used. */
    PM_EVT_CONN_SEC_PARAMS_REQ,             /**< @brief Security parameters (@ref ble_gap_sec_params_t) are needed for an ongoing security procedure. Reply with @ref pm_conn_sec_params_reply before the event handler returns. If no reply is sent, the parameters given in @ref pm_sec_params_set are used. If a peripheral connection, the central's sec_params will be available in the event. */
    PM_EVT_STORAGE_FULL,                    /**< @brief There is no more room for peer data in flash storage. To solve this problem, delete data that is not needed anymore and run a garbage collection procedure in FDS. */
    PM_EVT_ERROR_UNEXPECTED,                /**< @brief An unrecoverable error happened inside Peer Manager. An operation failed with the provided error. */
    PM_EVT_PEER_DATA_UPDATE_SUCCEEDED,      /**< @brief A piece of peer data was stored, updated, or cleared in flash storage. This event is sent for all successful changes to peer data, also those initiated internally in Peer Manager. To identify an operation, compare the store token in the event with the store token received during the initiating function call. Events from internally initiated changes might have invalid store tokens. */
    PM_EVT_PEER_DATA_UPDATE_FAILED,         /**< @brief A piece of peer data could not be stored, updated, or cleared in flash storage. This event is sent instead of @ref PM_EVT_PEER_DATA_UPDATE_SUCCEEDED for the failed operation. */
    PM_EVT_PEER_DELETE_SUCCEEDED,           /**< @brief A peer was cleared from flash storage, for example because a call to @ref pm_peer_delete succeeded. This event can also be sent as part of a call to @ref pm_peers_delete or internal cleanup. */
    PM_EVT_PEER_DELETE_FAILED,              /**< @brief A peer could not be cleared from flash storage. This event is sent instead of @ref PM_EVT_PEER_DELETE_SUCCEEDED for the failed operation. */
    PM_EVT_PEERS_DELETE_SUCCEEDED,          /**< @brief A call to @ref pm_peers_delete has completed successfully. Flash storage now contains no peer data. */
    PM_EVT_PEERS_DELETE_FAILED,             /**< @brief A call to @ref pm_peers_delete has failed, which means that at least one of the peers could not be deleted. Other peers might have been deleted, or might still be queued to be deleted. No more @ref PM_EVT_PEERS_DELETE_SUCCEEDED or @ref PM_EVT_PEERS_DELETE_FAILED events are sent until the next time @ref pm_peers_delete is called. */
    PM_EVT_LOCAL_DB_CACHE_APPLIED,          /**< @brief Local database values for a peer (taken from flash storage) have been provided to the SoftDevice. */
    PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED,     /**< @brief Local database values for a peer (taken from flash storage) were rejected by the SoftDevice, which means that either the database has changed or the user has manually set the local database to an invalid value (using @ref pm_peer_data_store). */
    PM_EVT_SERVICE_CHANGED_IND_SENT,        /**< @brief A service changed indication has been sent to a peer, as a result of a call to @ref pm_local_database_has_changed. This event will be followed by a @ref PM_EVT_SERVICE_CHANGED_IND_CONFIRMED event if the peer acknowledges the indication. */
    PM_EVT_SERVICE_CHANGED_IND_CONFIRMED,   /**< @brief A service changed indication that was sent has been confirmed by a peer. The peer can now be considered aware that the local database has changed. */
    PM_EVT_SLAVE_SECURITY_REQ,              /**< @brief The peer (peripheral) has requested link encryption, which has been enabled. */
    PM_EVT_FLASH_GARBAGE_COLLECTED,         /**< @brief The flash has been garbage collected (By FDS), possibly freeing up space. */
} pm_evt_id_t;


/**@brief Events parameters specific to the @ref PM_EVT_CONN_SEC_START event.
 */
typedef struct
{
    pm_conn_sec_procedure_t procedure; /**< @brief The procedure that has started. */
} pm_conn_sec_start_evt_t;


/**@brief Parameters specific to the @ref PM_EVT_CONN_SEC_SUCCEEDED event.
 */
typedef struct
{
    pm_conn_sec_procedure_t procedure;   /**< @brief The procedure that led to securing the link. */
    bool                    data_stored; /**< @brief Whether bonding data was successfully requested to be stored. This is false if: No bonding happened, or an internal error occurred when trying to store the data, or if the data was rejected via @ref pm_conn_sec_config_reply. */
} pm_conn_secured_evt_t;


/**@brief Parameters specific to the @ref PM_EVT_CONN_SEC_FAILED event.
 */
typedef struct
{
    pm_conn_sec_procedure_t procedure; /**< @brief The procedure that failed. */
    pm_sec_error_code_t     error;     /**< @brief An error code that describes the failure. */
    uint8_t                 error_src; /**< @brief The party that raised the error, see @ref BLE_GAP_SEC_STATUS_SOURCES. */
} pm_conn_secure_failed_evt_t;


/**@brief Parameters specific to the @ref PM_EVT_CONN_SEC_PARAMS_REQ event.
 */
typedef struct
{
    ble_gap_sec_params_t const * p_peer_params; /**< @brief Peer security parameters, if role is peripheral. Otherwise, this is NULL. */
    void                 const * p_context;     /**< @brief This pointer must be provided in the reply if the reply function takes a p_context argument. */
} pm_conn_sec_params_req_evt_t;


/**@brief Actions that can be performed to peer data in persistent storage.
 */
typedef enum
{
    PM_PEER_DATA_OP_UPDATE, /**< @brief Writing or overwriting the data. */
    PM_PEER_DATA_OP_DELETE, /**< @brief Removing the data. */
} pm_peer_data_op_t;


/**@brief Parameters specific to the @ref PM_EVT_PEER_DATA_UPDATE_SUCCEEDED event.
 */
typedef struct
{
    pm_peer_data_id_t data_id;           /**< @brief The type of the data that was changed. */
    pm_peer_data_op_t action;            /**< @brief What happened to the data. */
    pm_store_token_t  token;             /**< @brief Token that identifies the operation. For @ref PM_PEER_DATA_OP_DELETE actions, this token can be disregarded. For @ref PM_PEER_DATA_OP_UPDATE actions, compare this token with the token that is received from a call to a @ref PM_PEER_DATA_FUNCTIONS function. */
    uint8_t           flash_changed : 1; /**< @brief If this is false, no operation was done in flash, because the value was already what it should be. Please note that in certain scenarios, this flag will be true even if the new value is the same as the old. */
} pm_peer_data_update_succeeded_evt_t;


/**@brief Parameters specific to the @ref PM_EVT_PEER_DATA_UPDATE_FAILED event.
 */
typedef struct
{
    pm_peer_data_id_t data_id; /**< @brief The type of the data that was supposed to be changed. */
    pm_peer_data_op_t action;  /**< @brief The action that failed. */
    pm_store_token_t  token;   /**< @brief Token that identifies the operation. For @ref PM_PEER_DATA_OP_DELETE actions, this token can be disregarded. For @ref PM_PEER_DATA_OP_UPDATE actions, compare this token with the token that is received from a call to a @ref PM_PEER_DATA_FUNCTIONS function. */
    ret_code_t        error;   /**< @brief An error code that describes the failure. */
} pm_peer_data_update_failed_t;


/**@brief Standard parameters for failure events.
 */
typedef struct
{
    ret_code_t error; /**< @brief The error that occurred. */
} pm_failure_evt_t;


/**@brief Events parameters specific to the @ref PM_EVT_SLAVE_SECURITY_REQ event.
 */
typedef struct
{
    bool bond; /**< @brief Whether the peripheral requested bonding. */
    bool mitm; /**< @brief Whether the peripheral requested man-in-the-middle protection. */
} pm_evt_slave_security_req_t;


/**@brief An event from the @ref peer_manager module.
 *
 * @details The structure contains both standard parameters and parameters that are specific to some events.
 */
typedef struct
{
    pm_evt_id_t  evt_id;      /**< @brief The type of the event. */
    uint16_t     conn_handle; /**< @brief The connection that this event pertains to, or @ref BLE_CONN_HANDLE_INVALID. */
    pm_peer_id_t peer_id;     /**< @brief The bonded peer that this event pertains to, or @ref PM_PEER_ID_INVALID. */
    union
    {
        pm_conn_sec_start_evt_t             conn_sec_start;             /**< @brief Parameters specific to the @ref PM_EVT_CONN_SEC_START event. */
        pm_conn_secured_evt_t               conn_sec_succeeded;         /**< @brief Parameters specific to the @ref PM_EVT_CONN_SEC_SUCCEEDED event. */
        pm_conn_secure_failed_evt_t         conn_sec_failed;            /**< @brief Parameters specific to the @ref PM_EVT_CONN_SEC_FAILED event. */
        pm_conn_sec_params_req_evt_t        conn_sec_params_req;        /**< @brief Parameters specific to the @ref PM_EVT_CONN_SEC_PARAMS_REQ event. */
        pm_peer_data_update_succeeded_evt_t peer_data_update_succeeded; /**< @brief Parameters specific to the @ref PM_EVT_PEER_DATA_UPDATE_SUCCEEDED event. */
        pm_peer_data_update_failed_t        peer_data_update_failed;    /**< @brief Parameters specific to the @ref PM_EVT_PEER_DATA_UPDATE_FAILED event. */
        pm_failure_evt_t                    peer_delete_failed;         /**< @brief Parameters specific to the @ref PM_EVT_PEER_DELETE_FAILED event. */
        pm_failure_evt_t                    peers_delete_failed_evt;    /**< @brief Parameters specific to the @ref PM_EVT_PEERS_DELETE_FAILED event. */
        pm_failure_evt_t                    error_unexpected;           /**< @brief Parameters specific to the @ref PM_EVT_ERROR_UNEXPECTED event. */
        pm_evt_slave_security_req_t         slave_security_req;         /**< @brief Parameters specific to the @ref PM_EVT_SLAVE_SECURITY_REQ event. */
    } params;
} pm_evt_t;


/**@brief Event handler for events from the @ref peer_manager module.
 *
 * @sa pm_register
 *
 * @param[in]  p_event  The event that has occurred.
 */
typedef void (*pm_evt_handler_t)(pm_evt_t const * p_event);

#ifdef __cplusplus
}
#endif

#endif /* PEER_MANAGER_TYPES_H__ */

/** @} */
