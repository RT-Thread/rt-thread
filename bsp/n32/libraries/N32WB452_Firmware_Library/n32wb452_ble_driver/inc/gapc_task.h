/**
 ****************************************************************************************
 *
 * @file gapc_task.h
 *
 * @brief Generic Access Profile Controller Task Header.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */
#ifndef _GAPC_TASK_H_
#define _GAPC_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup GAPC_TASK Generic Access Profile Controller Task
 * @ingroup GAPC
 * @brief Handles ALL messages to/from GAP Controller block.
 *
 * It handles messages from lower and higher layers related to an ongoing connection.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_task.h" // Task definitions
#include "gap.h"
#include <stdbool.h>


/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */


/// GAP Controller Task messages
enum gapc_msg_id
{
    /* Default event */
    /// Command Complete event
    GAPC_CMP_EVT = TASK_FIRST_MSG(TASK_ID_GAPC),

    /* Connection state information */
    /// Indicate that a connection has been established
    GAPC_CONNECTION_REQ_IND,
    /// Set specific link data configuration.
    GAPC_CONNECTION_CFM,

    /// Indicate that a link has been disconnected
    GAPC_DISCONNECT_IND,

    /* Link management command */
    /// Request disconnection of current link command.
    GAPC_DISCONNECT_CMD,

    /* Peer device info */
    /// Retrieve information command
    GAPC_GET_INFO_CMD,
    /// Peer device attribute DB info such as Device Name, Appearance or Slave Preferred Parameters
    GAPC_PEER_ATT_INFO_IND,
    /// Indication of peer version info
    GAPC_PEER_VERSION_IND,
    /// Indication of peer features info
    GAPC_PEER_FEATURES_IND,
    /// Indication of ongoing connection RSSI
    GAPC_CON_RSSI_IND,

    /* Device Name Management */
    /// Peer device request local device info such as name, appearance or slave preferred parameters
    GAPC_GET_DEV_INFO_REQ_IND,
    /// Send requested info to peer device
    GAPC_GET_DEV_INFO_CFM,
    /// Peer device request to modify local device info such as name or appearance
    GAPC_SET_DEV_INFO_REQ_IND,
    /// Local device accept or reject device info modification
    GAPC_SET_DEV_INFO_CFM,

    /* Connection parameters update */
    /// Perform update of connection parameters command
    GAPC_PARAM_UPDATE_CMD,
    /// Request of updating connection parameters indication
    GAPC_PARAM_UPDATE_REQ_IND,
    /// Master confirm or not that parameters proposed by slave are accepted or not
    GAPC_PARAM_UPDATE_CFM,
    /// Connection parameters updated indication
    GAPC_PARAM_UPDATED_IND,

    /* Bonding procedure */
    /// Start Bonding command procedure
    GAPC_BOND_CMD,
    /// Bonding requested by peer device indication message.
    GAPC_BOND_REQ_IND,
    /// Confirm requested bond information.
    GAPC_BOND_CFM,
    /// Bonding information indication message
    GAPC_BOND_IND,

    /* Encryption procedure */
    /// Start Encryption command procedure
    GAPC_ENCRYPT_CMD,
    /// Encryption requested by peer device indication message.
    GAPC_ENCRYPT_REQ_IND,
    /// Confirm requested Encryption information.
    GAPC_ENCRYPT_CFM,
    /// Encryption information indication message
    GAPC_ENCRYPT_IND,

    /* Security request procedure */
    /// Start Security Request command procedure
    GAPC_SECURITY_CMD,
    /// Security requested by peer device indication message
    GAPC_SECURITY_IND,

    /* Signature procedure */
    /// Indicate the current sign counters to the application
    GAPC_SIGN_COUNTER_IND,

    /* Device information */
    /// Indication of ongoing connection Channel Map
    GAPC_CON_CHANNEL_MAP_IND,


    /* Deprecated */
    /// Deprecated messages
    GAPC_DEPRECATED_0,
    GAPC_DEPRECATED_1,
    GAPC_DEPRECATED_2,
    GAPC_DEPRECATED_3,
    GAPC_DEPRECATED_4,
    GAPC_DEPRECATED_5,
    GAPC_DEPRECATED_6,
    GAPC_DEPRECATED_7,
    GAPC_DEPRECATED_8,
    GAPC_DEPRECATED_9,

    /* LE Ping */
    /// Update LE Ping timeout value
    GAPC_SET_LE_PING_TO_CMD,
    /// LE Ping timeout indication
    GAPC_LE_PING_TO_VAL_IND,
    /// LE Ping timeout expires indication
    GAPC_LE_PING_TO_IND,

    /* LE Data Length extension*/
    /// LE Set Data Length Command
    GAPC_SET_LE_PKT_SIZE_CMD,
    /// LE Set Data Length Indication
    GAPC_LE_PKT_SIZE_IND,

    /* Secure Connections */
    /// Request to inform the remote device when keys have been entered or erased
    GAPC_KEY_PRESS_NOTIFICATION_CMD,
    /// Indication that a KeyPress has been performed on the peer device.
    GAPC_KEY_PRESS_NOTIFICATION_IND,

    // ---------------------- INTERNAL API ------------------------
    /* Internal messages for timer events, not part of API*/
    /// Signature procedure
    GAPC_SIGN_CMD,
    /// Signature result
    GAPC_SIGN_IND,

    /// Parameter update procedure timeout indication
    GAPC_PARAM_UPDATE_TO_IND,
    /// Pairing procedure timeout indication
    GAPC_SMP_TIMEOUT_TIMER_IND,
    /// Pairing repeated attempts procedure timeout indication
    GAPC_SMP_REP_ATTEMPTS_TIMER_IND,
};




/// request operation type - application interface
enum gapc_operation
{
    /*                 Operation Flags                  */
    /* No Operation (if nothing has been requested)     */
    /* ************************************************ */
    /// No operation
    GAPC_NO_OP                                    = 0x00,

    /* Connection management */
    /// Disconnect link
    GAPC_DISCONNECT,

    /* Connection information */
    /// Retrieve name of peer device.
    GAPC_GET_PEER_NAME,
    /// Retrieve peer device version info.
    GAPC_GET_PEER_VERSION,
    /// Retrieve peer device features.
    GAPC_GET_PEER_FEATURES,
    /// Get Peer device appearance
    GAPC_GET_PEER_APPEARANCE,
    /// Get Peer device Slaved Preferred Parameters
    GAPC_GET_PEER_SLV_PREF_PARAMS,
    /// Retrieve connection RSSI.
    GAPC_GET_CON_RSSI,
    /// Retrieve Connection Channel MAP.
    GAPC_GET_CON_CHANNEL_MAP,

    /* Connection parameters update */
    /// Perform update of connection parameters.
    GAPC_UPDATE_PARAMS,

    /* Security procedures */
    /// Start bonding procedure.
    GAPC_BOND,
    /// Start encryption procedure.
    GAPC_ENCRYPT,
    /// Start security request procedure
    GAPC_SECURITY_REQ,

    /* Deprecated */
    /// Deprecated operation
    GAPC_OP_DEPRECATED_0,
    GAPC_OP_DEPRECATED_1,
    GAPC_OP_DEPRECATED_2,
    GAPC_OP_DEPRECATED_3,
    GAPC_OP_DEPRECATED_4,

    /* LE Ping*/
    /// get timer timeout value
    GAPC_GET_LE_PING_TO,
    /// set timer timeout value
    GAPC_SET_LE_PING_TO,

    /* LE Data Length extension*/
    /// LE Set Data Length
    GAPC_SET_LE_PKT_SIZE,

    /* Central Address resolution supported*/
    GAPC_GET_ADDR_RESOL_SUPP,

    /* Secure Connections */
    /// Request to inform the remote device when keys have been entered or erased
    GAPC_KEY_PRESS_NOTIFICATION,

    // ---------------------- INTERNAL API ------------------------
    /* Packet signature */
    /// sign an attribute packet
    GAPC_SIGN_PACKET,
    /// Verify signature or an attribute packet
    GAPC_SIGN_CHECK,
};

/// Bond event type.
enum gapc_bond
{
    /// Bond Pairing request
    GAPC_PAIRING_REQ,
    /// Respond to Pairing request
    GAPC_PAIRING_RSP,

    /// Pairing Finished information
    GAPC_PAIRING_SUCCEED,
    /// Pairing Failed information
    GAPC_PAIRING_FAILED,

    /// Used to retrieve pairing Temporary Key
    GAPC_TK_EXCH,
    /// Used for Identity Resolving Key exchange
    GAPC_IRK_EXCH,
    /// Used for Connection Signature Resolving Key exchange
    GAPC_CSRK_EXCH,
    /// Used for Long Term Key exchange
    GAPC_LTK_EXCH,

    /// Bond Pairing request issue, Repeated attempt
    GAPC_REPEATED_ATTEMPT,

    /// Out of Band - exchange of confirm and rand.
    GAPC_OOB_EXCH,

    /// Numeric Comparison - Exchange of Numeric Value -
    GAPC_NC_EXCH
};

/// List of device info that should be provided by application
enum gapc_dev_info
{
    /// Device Name
    GAPC_DEV_NAME,
    /// Device Appearance Icon
    GAPC_DEV_APPEARANCE,
    /// Device Slave preferred parameters
    GAPC_DEV_SLV_PREF_PARAMS,
    /// Device Central address resolution
    GAPC_DEV_CTL_ADDR_RESOL,
    /// maximum device info parameter
    GAPC_DEV_INFO_MAX,
};

/// List of features available on a device
enum gapc_features_list
{
    /// LE encryption
    GAPC_ENCRYPT_FEAT_MASK              = (1 << 0),
    /// Connection Parameters Request Procedure
    GAPC_CONN_PARAM_REQ_FEAT_MASK       = (1 << 1),
    /// Extended Reject Indication
    GAPC_EXT_REJECT_IND_FEAT_MASK       = (1 << 2),
    /// Slave-initiated Features Exchange
    GAPC_SLAVE_FEAT_EXCH_FEAT_MASK      = (1 << 3),
    /// LE ping
    GAPC_LE_PING_FEAT_MASK              = (1 << 4)
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Operation command structure in order to keep requested operation.
struct gapc_operation_cmd
{
    /// GAP request type
    uint8_t operation;
};


/// Command complete event data structure
struct gapc_cmp_evt
{
    /// GAP request type
    uint8_t operation;
    /// Status of the request
    uint8_t status;
};

/// Indicate that a connection has been established
struct gapc_connection_req_ind
{
    /// Connection handle
    uint16_t conhdl;
    /// Connection interval
    uint16_t con_interval;
    /// Connection latency
    uint16_t con_latency;
    /// Link supervision timeout
    uint16_t sup_to;
    /// Clock accuracy
    uint8_t clk_accuracy;
    /// Peer address type
    uint8_t peer_addr_type;
    /// Peer BT address
    bd_addr_t peer_addr;
};


/// Set specific link data configuration.
struct gapc_connection_cfm
{
    /// Local CSRK value
    struct gap_sec_key lcsrk;
    /// Local signature counter value
    uint32_t lsign_counter;

    /// Remote CSRK value
    struct gap_sec_key rcsrk;
    /// Remote signature counter value
    uint32_t rsign_counter;

    /// Authentication (@see gap_auth)
    uint8_t auth;
    /// Service Changed Indication enabled
    uint8_t svc_changed_ind_enable;
    /// LTK exchanged during pairing.
    bool ltk_present;
};


/// Request disconnection of current link command.
struct gapc_disconnect_cmd
{
    /// GAP request type:
    /// - GAPC_DISCONNECT: Disconnect link.
    uint8_t operation;

    /// Reason of disconnection
    uint8_t reason;
};


/// Indicate that a link has been disconnected
struct gapc_disconnect_ind
{
    /// Connection handle
    uint16_t conhdl;
    /// Reason of disconnection
    uint8_t reason;
};


/// Retrieve information command
struct gapc_get_info_cmd
{
    /// GAP request type:
    /// - GAPC_GET_PEER_NAME: Retrieve name of peer device.
    /// - GAPC_GET_PEER_VERSION: Retrieve peer device version info.
    /// - GAPC_GET_PEER_FEATURES: Retrieve peer device features.
    /// - GAPC_GET_CON_RSSI: Retrieve connection RSSI.
    /// - GAPC_GET_CON_CHANNEL_MAP: Retrieve Connection Channel MAP.
    /// - GAPC_GET_PEER_APPEARANCE: Get Peer device appearance
    /// - GAPC_GET_PEER_SLV_PREF_PARAMS: Get Peer device Slaved Preferred Parameters
    /// - GAPC_GET_ADDR_RESOL_SUPP: Address Resolution Supported
    /// - GAPC_GET_LE_PING_TIMEOUT: Retrieve LE Ping Timeout Value
    uint8_t operation;
};

/// device information data
union gapc_dev_info_val
{
    /// Device name
    struct gap_dev_name name;
    /// Appearance Icon
    uint16_t appearance;
    /// Slave preferred parameters
    struct gap_slv_pref slv_params;
    /// Central address resolution
    uint8_t cnt_addr_resol;
};

/// Peer device attribute DB info such as Device Name, Appearance or Slave Preferred Parameters
struct gapc_peer_att_info_ind
{
    /// Requested information
    /// - GAPC_DEV_NAME: Device Name
    /// - GAPC_DEV_APPEARANCE: Device Appearance Icon
    /// - GAPC_DEV_SLV_PREF_PARAMS: Device Slave preferred parameters
    /// - GAPC_GET_ADDR_RESOL_SUPP: Address resolution supported
    uint8_t  req;
    /// Attribute handle
    uint16_t handle;

    /// device information data
    union gapc_dev_info_val info;
};

/// Indication of peer version info
struct gapc_peer_version_ind
{
    /// Manufacturer name
    uint16_t compid;
    /// LMP subversion
    uint16_t lmp_subvers;
    /// LMP version
    uint8_t  lmp_vers;
};

/// Indication of peer features info
struct gapc_peer_features_ind
{
    /// 8-byte array for LE features
    uint8_t features[GAP_LE_FEATS_LEN];
};

/// Indication of ongoing connection RSSI
struct gapc_con_rssi_ind
{
    /// RSSI value
    int8_t rssi;
};
/// Indication of ongoing connection Channel Map
struct gapc_con_channel_map_ind
{
    /// channel map value
    le_chnl_map_t ch_map;
};

/// Sign counter value changed due to packet signing or signature verification.
struct gapc_sign_counter_updated_ind
{
    /// New Local signature counter value
    uint32_t lsign_counter;
    /// New Remote signature counter value
    uint32_t rsign_counter;
};

/// Indication of LE Ping
struct gapc_le_ping_to_val_ind
{
    ///Authenticated payload timeout
    uint16_t timeout;
};


/// Peer device request local device info such as name, appearance or slave preferred parameters
struct gapc_get_dev_info_req_ind
{
    /// Requested information
    /// - GAPC_DEV_NAME: Device Name
    /// - GAPC_DEV_APPEARANCE: Device Appearance Icon
    /// - GAPC_DEV_SLV_PREF_PARAMS: Device Slave preferred parameters
    uint8_t req;
};



/// Send requested info to peer device
struct gapc_get_dev_info_cfm
{
    /// Requested information
    /// - GAPC_DEV_NAME: Device Name
    /// - GAPC_DEV_APPEARANCE: Device Appearance Icon
    /// - GAPC_DEV_SLV_PREF_PARAMS: Device Slave preferred parameters
    uint8_t req;

    /// Peer device information data
    union gapc_dev_info_val info;
};

/// Peer device request to modify local device info such as name or appearance
struct gapc_set_dev_info_req_ind
{
    /// Requested information
    /// - GAPC_DEV_NAME: Device Name
    /// - GAPC_DEV_APPEARANCE: Device Appearance Icon
    uint8_t req;

    /// device information data
    union gapc_set_dev_info
    {
        /// Device name
        struct gap_dev_name name;
        /// Appearance Icon
        uint16_t appearance;
    } info;
};

/// Local device accept or reject device info modification
struct gapc_set_dev_info_cfm
{
    /// Requested information
    /// - GAPC_DEV_NAME: Device Name
    /// - GAPC_DEV_APPEARANCE: Device Appearance Icon
    uint8_t req;

    /// Status code used to know if requested has been accepted or not
    uint8_t status;
};

/// Connection Parameter used to update connection parameters
struct gapc_conn_param
{
    /// Connection interval minimum
    uint16_t intv_min;
    /// Connection interval maximum
    uint16_t intv_max;
    /// Latency
    uint16_t latency;
    /// Supervision timeout
    uint16_t time_out;
};

/// Perform update of connection parameters command
struct gapc_param_update_cmd
{
    /// GAP request type:
    /// - GAPC_UPDATE_PARAMS: Perform update of connection parameters.
    uint8_t operation;
    /// Internal parameter used to manage internally l2cap packet identifier for signaling
    uint8_t pkt_id;
    /// Connection interval minimum
    uint16_t intv_min;
    /// Connection interval maximum
    uint16_t intv_max;
    /// Latency
    uint16_t latency;
    /// Supervision timeout
    uint16_t time_out;
    /// Minimum Connection Event Duration
    uint16_t ce_len_min;
    /// Maximum Connection Event Duration
    uint16_t ce_len_max;
};

/// Request of updating connection parameters indication
struct gapc_param_update_req_ind
{
    /// Connection interval minimum
    uint16_t intv_min;
    /// Connection interval maximum
    uint16_t intv_max;
    /// Latency
    uint16_t latency;
    /// Supervision timeout
    uint16_t time_out;
};

/// Connection parameters updated indication
struct gapc_param_updated_ind
{
    ///Connection interval value
    uint16_t            con_interval;
    ///Connection latency value
    uint16_t            con_latency;
    ///Supervision timeout
    uint16_t            sup_to;
};

/// Master confirm or not that parameters proposed by slave are accepted or not
struct gapc_param_update_cfm
{
    /// True to accept slave connection parameters, False else.
    bool accept;
    /// Minimum Connection Event Duration
    uint16_t ce_len_min;
    /// Maximum Connection Event Duration
    uint16_t ce_len_max;
};

/// Pairing parameters
struct gapc_pairing
{
    /// IO capabilities (@see gap_io_cap)
    uint8_t iocap;
    /// OOB information (@see gap_oob)
    uint8_t oob;
    /// Authentication (@see gap_auth)
    /// Note in BT 4.1 the Auth Field is extended to include 'Key Notification' and
    /// and 'Secure Connections'.
    uint8_t auth;
    /// Encryption key size (7 to 16)
    uint8_t key_size;
    ///Initiator key distribution (@see gap_kdist)
    uint8_t ikey_dist;
    ///Responder key distribution (@see gap_kdist)
    uint8_t rkey_dist;

    /// Device security requirements (minimum security level). (@see gap_sec_req)
    uint8_t sec_req;
};

/// Long Term Key information
struct gapc_ltk
{
    /// Long Term Key
    struct gap_sec_key ltk;
    /// Encryption Diversifier
    uint16_t ediv;
    /// Random Number
    rand_nb_t randnb;
    /// Encryption key size (7 to 16)
    uint8_t key_size;

    uint8_t key_num;
};
/// Out of Band Information
struct gapc_oob
{
    /// Confirm Value
    uint8_t conf[GAP_KEY_LEN];
    /// Random Number
    uint8_t rand[GAP_KEY_LEN];
};

struct gapc_nc
{
    uint8_t value[4];
};

/// Identity Resolving Key information
struct gapc_irk
{
    /// Identity Resolving Key
    struct gap_sec_key irk;
    /// Device BD Identity Address
    struct gap_bdaddr addr;
};


/// Start Bonding command procedure
struct gapc_bond_cmd
{
    /// GAP request type:
    /// - GAPC_BOND:  Start bonding procedure.
    uint8_t operation;
    /// Pairing information
    struct gapc_pairing pairing;
};

/// Bonding requested by peer device indication message.
struct gapc_bond_req_ind
{
    /// Bond request type (@see gapc_bond)
    uint8_t request;

    /// Bond procedure requested information data
    union gapc_bond_req_data
    {
        /// Authentication level (@see gap_auth) (if request = GAPC_PAIRING_REQ)
        uint8_t auth_req;
        /// LTK Key Size (if request = GAPC_LTK_EXCH)
        uint8_t key_size;
        /// Device IO used to get TK: (if request = GAPC_TK_EXCH)
        ///  - GAP_TK_OOB:       TK get from out of band method
        ///  - GAP_TK_DISPLAY:   TK generated and shall be displayed by local device
        ///  - GAP_TK_KEY_ENTRY: TK shall be entered by user using device keyboard
        uint8_t tk_type;

        /// Addition OOB Data for the OOB Conf and Rand values
        struct gapc_oob  oob_data;
        /// Numeric Comparison Data
        struct gapc_nc   nc_data;
    } data;
};

/// Confirm requested bond information.
struct gapc_bond_cfm
{
    /// Bond request type (@see gapc_bond)
    uint8_t request;
    /// Request accepted
    uint8_t accept;

    /// Bond procedure information data
    union gapc_bond_cfm_data
    {
        /// Pairing Features (request = GAPC_PAIRING_RSP)
        struct gapc_pairing pairing_feat;
        /// LTK (request = GAPC_LTK_EXCH)
        struct gapc_ltk ltk;
        /// CSRK (request = GAPC_CSRK_EXCH)
        struct gap_sec_key csrk;
        /// TK (request = GAPC_TK_EXCH)
        struct gap_sec_key tk;
        /// IRK (request = GAPC_IRK_EXCH)
        struct gapc_irk irk;
        /// OOB Confirm and Random from the peer (request = GAPC_OOB_EXCH)
        struct gapc_oob oob;
    } data;
};

/**
 *  Authentication information
 */
struct gapc_bond_auth
{
    /// Authentication information (@see gap_auth)
    uint8_t info;

    /// LTK exchanged during pairing.
    bool ltk_present;
};



/// Bonding information indication message
struct gapc_bond_ind
{
    /// Bond information type (@see gapc_bond)
    uint8_t info;

    /// Bond procedure information data
    union gapc_bond_data
    {
        /// Authentication information (@see gap_auth)
        /// (if info = GAPC_PAIRING_SUCCEED)
        struct gapc_bond_auth auth;
        /// Pairing failed reason  (if info = GAPC_PAIRING_FAILED)
        uint8_t reason;
        /// Long Term Key information (if info = GAPC_LTK_EXCH)
        struct gapc_ltk ltk;
        /// Identity Resolving Key information (if info = GAPC_IRK_EXCH)
        struct gapc_irk irk;
        /// Connection Signature Resolving Key information (if info = GAPC_CSRK_EXCH)
        struct gap_sec_key csrk;
    } data;
};

/// Start Encryption command procedure
struct gapc_encrypt_cmd
{
    /// GAP request type:
    /// - GAPC_ENCRYPT:  Start encryption procedure.
    uint8_t operation;
    /// Long Term Key information
    struct gapc_ltk ltk;
};

/// Encryption requested by peer device indication message.
struct gapc_encrypt_req_ind
{
    /// Encryption Diversifier
    uint16_t ediv;
    /// Random Number
    rand_nb_t rand_nb;
};

/// Confirm requested Encryption information.
struct gapc_encrypt_cfm
{
    /// Indicate if a LTK has been found for the peer device
    uint8_t found;
    /// Long Term Key
    struct gap_sec_key ltk;
    /// LTK Key Size
    uint8_t key_size;
};

/// Encryption information indication message
struct gapc_encrypt_ind
{
    /// Authentication  level (@see gap_auth)
    uint8_t auth;
};

/// Start Security Request command procedure
struct gapc_security_cmd
{
    /// GAP request type:
    /// - GAPC_SECURITY_REQ: Start security request procedure
    uint8_t operation;
    /// Authentication level (@see gap_auth)
    uint8_t auth;
};
/// Security requested by peer device indication message
struct gapc_security_ind
{
    /// Authentication level (@see gap_auth)
    uint8_t auth;
};

/// Parameters of the @ref GAPC_SIGN_COUNTER_IND message
struct gapc_sign_counter_ind
{
    /// Local SignCounter value
    uint32_t local_sign_counter;
    /// Peer SignCounter value
    uint32_t peer_sign_counter;
};


/// Parameters of the @ref GAPC_SET_LE_PING_TO_CMD message
struct gapc_set_le_ping_to_cmd
{
    /// GAP request type:
    /// - GAPC_SET_LE_PING_TO : Set the LE Ping timeout value
    uint8_t operation;
    /// Authenticated payload timeout
    uint16_t timeout;
};

/// Parameters of the @ref GAPC_SET_LE_PKT_SIZE_CMD message
struct gapc_set_le_pkt_size_cmd
{
    /// GAP request type:
    /// - GAPC_SET_LE_PKT_SIZE : Set the LE Data length value
    uint8_t operation;
    ///Preferred maximum number of payload octets that the local Controller should include
    ///in a single Link Layer Data Channel PDU.
    uint16_t tx_octets;
    ///Preferred maximum number of microseconds that the local Controller should use to transmit
    ///a single Link Layer Data Channel PDU
    uint16_t tx_time;
};

/// Parameters of the @ref GAPC_LE_PKT_SIZE_IND message
struct gapc_le_pkt_size_ind
{
    ///The maximum number of payload octets in TX
    uint16_t max_tx_octets;
    ///The maximum time that the local Controller will take to TX
    uint16_t max_tx_time;
    ///The maximum number of payload octets in RX
    uint16_t max_rx_octets;
    ///The maximum time that the local Controller will take to RX
    uint16_t max_rx_time;
};

/// Parameters of the @ref GAPC_KEY_PRESS_NOTIFICATION_CMD message
struct gapc_key_press_notif_cmd
{
    /// GAP request type:
    /// - GAPC_KEY_PRESS_NOTIFICATION_CMD : Inform the remote device when keys have been entered or erased
    uint8_t operation;
    /// notification type
    uint8_t notification_type;
};

/// Parameters of the @ref GAPC_KEY_PRESS_NOTIFICATION_IND message
struct gapc_key_press_notif_ind
{
    /// notification type
    uint8_t notification_type;
};


/// Parameters of the @ref GAPC_SIGN_CMD message
struct gapc_sign_cmd
{
    /// GAP request type:
    /// - GAPC_SIGN_PACKET: Sign an attribute packet
    /// - GAPC_SIGN_CHECK:  Verify signature or an attribute packet
    uint8_t operation;
    /// Data PDU length (Bytes)
    uint16_t byte_len;
    /// Data PDU + SignCounter if generation, Data PDU + SignCounter + MAC if verification
    uint8_t msg[__ARRAY_EMPTY];
};

/// Parameters of the @ref GAPC_SIGN_IND message
struct gapc_sign_ind
{
    /// GAP request type:
    /// - GAPC_SIGN_PACKET: Sign an attribute packet
    /// - GAPC_SIGN_CHECK:  Verify signature or an attribute packet
    uint8_t operation;
    /// Data PDU length (Bytes)
    uint16_t byte_len;
    /// Data PDU + SignCounter + MAC
    uint8_t signed_msg[__ARRAY_EMPTY];
};


/// @} GAPC_TASK

#endif /* _GAPC_TASK_H_ */
