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
    PM_PEER_DATA_ID_BONDING                 = PM_PEER_DATA_ID_BONDING_V2,                 /**< @brief The data ID for bonding data. See @ref pm_peer_data_bonding_t. */
    PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING = PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING_V1, /**< @brief The data ID for service changed state. */
    PM_PEER_DATA_ID_GATT_LOCAL              = PM_PEER_DATA_ID_GATT_LOCAL_V2,              /**< @brief The data ID for local GATT data (sys attributes). See @ref pm_peer_data_local_gatt_db_t. */
    PM_PEER_DATA_ID_GATT_REMOTE             = PM_PEER_DATA_ID_GATT_REMOTE_V2,             /**< @brief The data ID for remote GATT data. */
    PM_PEER_DATA_ID_PEER_RANK               = PM_PEER_DATA_ID_PEER_RANK_V1,               /**< @brief The data ID for peer rank. See @ref pm_peer_rank_highest. */
    PM_PEER_DATA_ID_APPLICATION             = PM_PEER_DATA_ID_APPLICATION_V1,             /**< @brief The data ID for application data. */
    PM_PEER_DATA_ID_LAST                    = PM_PEER_DATA_ID_LAST_VX,                    /**< @brief One more than the highest data ID. */
    PM_PEER_DATA_ID_INVALID                 = PM_PEER_DATA_ID_INVALID_VX,                 /**< @brief A data ID guaranteed to be invalid. */
} pm_peer_data_id_t;


/**@brief Different procedures that can lead to an encrypted link.
 */
typedef enum
{
    PM_LINK_SECURED_PROCEDURE_ENCRYPTION, /**< @brief Using an LTK that was shared during a previous bonding procedure to encrypt the link. */
    PM_LINK_SECURED_PROCEDURE_BONDING,    /**< @brief A pairing procedure, followed by a bonding procedure. */
    PM_LINK_SECURED_PROCEDURE_PAIRING,    /**< @brief A pairing procedure with no bonding. */
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
#if (NRF_SD_BLE_API_VERSION < 3)

typedef struct
{
    uint8_t         privacy_mode;           /**< Privacy mode, see @ref BLE_GAP_PRIVACY_MODES. Default is @ref BLE_GAP_PRIVACY_MODE_OFF. */
    uint8_t         private_addr_type;      /**< The private address type must be either @ref BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE or @ref BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE. */
    uint16_t        private_addr_cycle_s;   /**< Private address cycle interval in seconds. Providing an address cycle value of 0 will use the default value defined by @ref BLE_GAP_DEFAULT_PRIVATE_ADDR_CYCLE_INTERVAL_S. */
    ble_gap_irk_t * p_device_irk;           /**< When used as input, pointer to IRK structure that will be used as the default IRK. If NULL, the device default IRK will be used.
                                                 When used as output, pointer to IRK structure where the current default IRK will be written to. If NULL, this argument is ignored.
                                                 By default, the default IRK is used to generate random private resolvable addresses for the local device unless instructed otherwise. */
} pm_privacy_params_t;


/**@defgroup BLE_GAP_PRIVACY_MODES Privacy modes
 * @{ */
#define BLE_GAP_PRIVACY_MODE_OFF                0x00 /**< Device will send and accept its identity address for its own address. */
#define BLE_GAP_PRIVACY_MODE_DEVICE_PRIVACY     0x01 /**< Device will send and accept only private addresses for its own address. */
/**@} */

#else

typedef ble_gap_privacy_params_t pm_privacy_params_t;

#endif


#ifdef __cplusplus
}
#endif

#endif /* PEER_MANAGER_TYPES_H__ */

/** @} */
