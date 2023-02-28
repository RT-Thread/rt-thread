/**
 ****************************************************************************************
 *
 * @file gapm_task.h
 *
 * @brief Generic Access Profile Manager Task Header.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */


#ifndef _GAPM_TASK_H_
#define _GAPM_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup GAPM_TASK Generic Access Profile Manager Task
 * @ingroup GAPM
 * @brief  Handles ALL messages to/from GAP Manager block.
 *
 * It handles messages from lower and higher layers not related to an ongoing connection.
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


/*
 * DEFINES
 ****************************************************************************************
 */

/// GAP Manager Message Interface
enum gapm_msg_id
{
    /* Default event */
    /// Command Complete event
    GAPM_CMP_EVT = TASK_FIRST_MSG(TASK_ID_GAPM),
    /// Event triggered to inform that lower layers are ready
    GAPM_DEVICE_READY_IND,

    /* Default commands */
    /// Reset link layer and the host command
    GAPM_RESET_CMD,
    /// Cancel ongoing operation
    GAPM_CANCEL_CMD,
    /* Device Configuration */
    /// Set device configuration command
    GAPM_SET_DEV_CONFIG_CMD,
    /// Set device channel map
    GAPM_SET_CHANNEL_MAP_CMD,
    /* Local device information */
    /// Get local device info command
    GAPM_GET_DEV_INFO_CMD,
    /// Local device version indication event
    GAPM_DEV_VERSION_IND,
    /// Local device BD Address indication event
    GAPM_DEV_BDADDR_IND,
    /// Advertising channel Tx power level
    GAPM_DEV_ADV_TX_POWER_IND,
    /// Indication containing information about memory usage.
    GAPM_DBG_MEM_INFO_IND,

    /* White List */
    /// White List Management Command
    GAPM_WHITE_LIST_MGT_CMD,
    /// White List Size indication event
    GAPM_WHITE_LIST_SIZE_IND,

    /* Air Operations */
    /// Set advertising mode Command
    GAPM_START_ADVERTISE_CMD,
    /// Update Advertising Data Command - On fly update when device is advertising
    GAPM_UPDATE_ADVERTISE_DATA_CMD,

    /// Set Scan mode Command
    GAPM_START_SCAN_CMD,
    /// Advertising or scanning report information event
    GAPM_ADV_REPORT_IND,

    /// Set connection initialization Command
    GAPM_START_CONNECTION_CMD,
    /// Name of peer device indication
    GAPM_PEER_NAME_IND,
    /// Confirm connection to a specific device (Connection Operation in Selective mode)
    GAPM_CONNECTION_CFM,

    /* Security / Encryption Toolbox */
    /// Resolve address command
    GAPM_RESOLV_ADDR_CMD,
    /// Indicate that resolvable random address has been solved
    GAPM_ADDR_SOLVED_IND,
    /// Generate a random address.
    GAPM_GEN_RAND_ADDR_CMD,
    /// Use the AES-128 block in the controller
    GAPM_USE_ENC_BLOCK_CMD,
    ///  AES-128 block result indication
    GAPM_USE_ENC_BLOCK_IND,
    /// Generate a 8-byte random number
    GAPM_GEN_RAND_NB_CMD,
    /// Random Number Indication
    GAPM_GEN_RAND_NB_IND,

    /* Profile Management */
    /// Create new task for specific profile
    GAPM_PROFILE_TASK_ADD_CMD,
    /// Inform that profile task has been added.
    GAPM_PROFILE_ADDED_IND,

    /// Indicate that a message has been received on an unknown task
    GAPM_UNKNOWN_TASK_IND,

    /* Data Length Extension */
    /// Suggested Default Data Length indication
    GAPM_SUGG_DFLT_DATA_LEN_IND,
    /// Maximum Data Length indication
    GAPM_MAX_DATA_LEN_IND,

    /* Resolving list for controller-based privacy*/
    /// Resolving address list management
    GAPM_RAL_MGT_CMD,
    /// Resolving address list size indication
    GAPM_RAL_SIZE_IND,
    /// Resolving address list address indication
    GAPM_RAL_ADDR_IND,

    /* Set new IRK */
    /// Modify current IRK
    GAPM_SET_IRK_CMD,

    /* LE Protocol/Service Multiplexer Management */
    /// Register a LE Protocol/Service Multiplexer command
    GAPM_LEPSM_REGISTER_CMD,
    /// Unregister a LE Protocol/Service Multiplexer command
    GAPM_LEPSM_UNREGISTER_CMD,

    /* ************************************************ */
    /* -------------- Internal usage only ------------- */
    /* ************************************************ */
    /// Message received to unknown task received
    GAPM_UNKNOWN_TASK_MSG,

    /* Secure Connections */
    /// Request to provide DH Key
    GAPM_GEN_DH_KEY_CMD,
    /// Indicates the DH Key computation is complete and available
    GAPM_GEN_DH_KEY_IND,

    /* Internal messages for timer events, not part of API*/
    /// Limited discoverable timeout indication
    GAPM_LIM_DISC_TO_IND,
    /// Scan timeout indication
    GAPM_SCAN_TO_IND,
    /// Address renewal timeout indication
    GAPM_ADDR_RENEW_TO_IND,
};


/// GAP Manager operation type - application interface
enum gapm_operation
{
    /* No Operation (if nothing has been requested)     */
    /* ************************************************ */
    /// No operation.
    GAPM_NO_OP                                     = 0x00,

    /* Default operations                               */
    /* ************************************************ */
    /// Reset BLE subsystem: LL and HL.
    GAPM_RESET,
    /// Cancel currently executed operation.
    GAPM_CANCEL,

    /* Configuration operations                         */
    /* ************************************************ */
    /// Set device configuration
    GAPM_SET_DEV_CONFIG,
    /// Set device channel map
    GAPM_SET_CHANNEL_MAP, //0x04

    /* Retrieve device information                      */
    /* ************************************************ */
    /// Get Local device version
    GAPM_GET_DEV_VERSION,
    /// Get Local device BD Address
    GAPM_GET_DEV_BDADDR,
    /// Get device advertising power level
    GAPM_GET_DEV_ADV_TX_POWER,

    /* Operation on White list                          */
    /* ************************************************ */
    /// Get White List Size.
    GAPM_GET_WLIST_SIZE,   //0x08
    /// Add devices in white list.
    GAPM_ADD_DEV_IN_WLIST,
    /// Remove devices form white list.
    GAPM_RMV_DEV_FRM_WLIST,  //0x0a
    /// Clear all devices from white list.
    GAPM_CLEAR_WLIST,

    /* Advertise mode operations                        */
    /* ************************************************ */
    /// Start non connectable advertising
    GAPM_ADV_NON_CONN,      //0x0c
    /// Start undirected connectable advertising
    GAPM_ADV_UNDIRECT,
    /// Start directed connectable advertising
    GAPM_ADV_DIRECT,
    /// Start directed connectable advertising using Low Duty Cycle
    GAPM_ADV_DIRECT_LDC,
    /// Update on the fly advertising data
    GAPM_UPDATE_ADVERTISE_DATA, //0x10

    /* Scan mode operations                             */
    /* ************************************************ */
    /// Start active scan operation
    GAPM_SCAN_ACTIVE,
    /// Start passive scan operation
    GAPM_SCAN_PASSIVE,

    /* Connection mode operations                       */
    /* ************************************************ */
    /// Direct connection operation
    GAPM_CONNECTION_DIRECT,
    /// Automatic connection operation
    GAPM_CONNECTION_AUTO, //0x014
    /// Selective connection operation
    GAPM_CONNECTION_SELECTIVE,
    /// Name Request operation (requires to start a direct connection)
    GAPM_CONNECTION_NAME_REQUEST,

    /* Security / Encryption Toolbox                    */
    /* ************************************************ */
    /// Resolve device address
    GAPM_RESOLV_ADDR,
    /// Generate a random address
    GAPM_GEN_RAND_ADDR,  //0x18
    /// Use the controller's AES-128 block
    GAPM_USE_ENC_BLOCK,
    /// Generate a 8-byte random number
    GAPM_GEN_RAND_NB,

    /* Profile Management                               */
    /* ************************************************ */
    /// Create new task for specific profile
    GAPM_PROFILE_TASK_ADD,


    /* DEBUG                                            */
    /* ************************************************ */
    /// Get memory usage
    GAPM_DBG_GET_MEM_INFO,  //0x1c
    /// Perform a platform reset
    GAPM_PLF_RESET,

    /* Data Length Extension                            */
    /* ************************************************ */
    /// Set Suggested Default LE Data Length
    GAPM_SET_SUGGESTED_DFLT_LE_DATA_LEN,
    /// Get Suggested Default LE Data Length
    GAPM_GET_SUGGESTED_DFLT_LE_DATA_LEN,
    /// Get Maximum LE Data Length
    GAPM_GET_MAX_LE_DATA_LEN, // 0x20

    /* Operation on Resolving List                      */
    /* ************************************************ */
    /// Get resolving address list size
    GAPM_GET_RAL_SIZE,
    /// Get resolving local address
    GAPM_GET_RAL_LOC_ADDR,
    /// Get resolving peer address
    GAPM_GET_RAL_PEER_ADDR,
    /// Add device in resolving address list
    GAPM_ADD_DEV_IN_RAL, // 0x024
    /// Remove device from resolving address list
    GAPM_RMV_DEV_FRM_RAL,
    /// Clear resolving address list
    GAPM_CLEAR_RAL,

    /* Connection mode operations - cont                */
    /* ************************************************ */
    /// General connection operation
    GAPM_CONNECTION_GENERAL,

    /* Change current IRK                               */
    /* ************************************************ */
    /// Set IRK
    GAPM_SET_IRK,   //0x028

    /* LE Protocol/Service Multiplexer management       */
    /* ************************************************ */
    /// Register a LE Protocol/Service Multiplexer
    GAPM_LEPSM_REG,
    /// Unregister a LE Protocol/Service Multiplexer
    GAPM_LEPSM_UNREG,

    /* Secure Connection - Internal API                 */
    /* ************************************************ */
    /// Generate DH_Key
    GAPM_GEN_DH_KEY,  //0x2b
};


/// Device Address type Configuration
enum gapm_addr_type
{
    /// Device Address is a Public Static address
    GAPM_CFG_ADDR_PUBLIC        = 0,
    /// Device Address is a Private Static address
    GAPM_CFG_ADDR_PRIVATE       = 1,
    /// Device Address generated using host-based Privacy feature
    GAPM_CFG_ADDR_HOST_PRIVACY  = 2,
    /// Device Address generated using controller-based Privacy feature
    GAPM_CFG_ADDR_CTNL_PRIVACY  = 4,
};


/// Own BD address source of the device
enum gapm_own_addr
{
   /// Public or Private Static Address according to device address configuration
   GAPM_STATIC_ADDR,
   /// Generated resolvable private random address
   GAPM_GEN_RSLV_ADDR,
   /// Generated non-resolvable private random address
   GAPM_GEN_NON_RSLV_ADDR,
};

/// Device Attribute write permission requirement
enum gapm_write_att_perm
{
    /// Disable write access
    GAPM_WRITE_DISABLE     = 0,
    /// Enable write access - no authentication required
    GAPM_WRITE_NO_AUTH     = 1,
    /// Write access requires unauthenticated link
    GAPM_WRITE_UNAUTH      = 2,
    /// Write access requires authenticated link
    GAPM_WRITE_AUTH        = 3,
    /// Write access requires secure connected link
    GAPM_WRITE_SEC_CON     = 4
};


/// Attribute database configuration
///   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
/// +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
/// | DBG |              RFU                | SC |PCP |   APP_PERM   |   NAME_PERM  |
/// +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
/// - Bit [0-2] : Device Name write permission requirements for peer device (@see gapm_write_att_perm)
/// - Bit [3-5] : Device Appearance write permission requirements for peer device (@see gapm_write_att_perm)
/// - Bit [6]   : Slave Preferred Connection Parameters present
/// - Bit [7]   : Service change feature present in GATT attribute database.
/// - Bit [8-14]: Reserved
/// - Bit [15]  : Enable Debug Mode
enum gapm_att_cfg_flag
{
    /// Device Name write permission requirements for peer device (@see gapm_write_att_perm)
    GAPM_MASK_ATT_NAME_PERM           = 0x0007,
    GAPM_POS_ATT_NAME_PERM            = 0x00,
    /// Device Appearance write permission requirements for peer device (@see gapm_write_att_perm)
    GAPM_MASK_ATT_APPEARENCE_PERM     = 0x0038,
    GAPM_POS_ATT_APPEARENCE_PERM      = 0x03,
    /// Slave Preferred Connection Parameters present in GAP attribute database.
    GAPM_MASK_ATT_SLV_PREF_CON_PAR_EN = 0x0040,
    GAPM_POS_ATT_SLV_PREF_CON_PAR_EN  = 0x06,
    /// Service change feature present in GATT attribute database.
    GAPM_MASK_ATT_SVC_CHG_EN          = 0x0080,
    GAPM_POS_ATT_SVC_CHG_EN           = 0x07,
    /// Service change feature present in GATT attribute database.
    GAPM_MASK_ATT_DBG_MODE_EN         = 0x8000,
    GAPM_POS_ATT_DBG_MODE_EN          = 0x0F,
};

/// Pairing mode authorized on the device
///    7    6    5    4    3    2    1    0
/// +----+----+----+----+----+----+----+----+
/// |KGEN|          RFU           | SCP| LP |
/// +----+----+----+----+----+----+----+----+
enum gapm_pairing_mode
{
    /// No pairing authorized
    GAPM_PAIRING_DISABLE  = 0,
    /// Legacy pairing Authorized
    GAPM_PAIRING_LEGACY   = (1 << 0),
    /// Secure Connection pairing Authorized
    GAPM_PAIRING_SEC_CON  = (1 << 1),
    /// Force re-generation of P256 private and public keys
    GAPM_PAIRING_FORCE_P256_KEY_GEN = (1<<7),
};

/// LE Audio Mode Configuration
///   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
/// +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
/// |                                 RFU                                      | AM0|
/// +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
enum gapm_audio_cfg_flag
{
    /// LE Audio Mode 0 Supported
    GAPM_MASK_AUDIO_AM0_SUP           = 0x0001,
    GAPM_POS_AUDIO_AM0_SUP            = 0x00,
};

/// Security level
///   7   6   5   4   3   2   1   0
/// +---+---+---+---+---+---+---+---+
/// |MI |      RFU      |EKS|SEC_LVL|
/// +---+---+---+---+---+---+---+---+
/// bit[0-1]: Security level requirement (0=NO_AUTH, 1=UNAUTH, 2=AUTH, 3=SEC_CON)
/// bit[2]  : Encryption Key Size length must have 16 bytes
/// bit[7]  : Multi-instantiated task
enum gapm_le_psm_sec_mask
{
    /// bit[0-1]: Security level requirement (0=NO_AUTH, 1=UNAUTH, 2=AUTH, 3=SEC_CON)
    /// bit[2]  : Encryption Key Size length must have 16 bytes
    GAPM_LE_PSM_SEC_LVL_MASK  = 0x07,
    /// bit[7]  : Multi-instantiated task
    GAPM_LE_PSM_MI_TASK_MASK  = 0x80,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Operation command structure in order to keep requested operation.
struct gapm_operation_cmd
{
    /// GAP request type
    uint8_t operation;
};

/// Command complete event data structure
struct gapm_cmp_evt
{
    /// GAP requested operation
    uint8_t operation;
    /// Status of the request
    uint8_t status;
};

///  Reset link layer and the host command
struct gapm_reset_cmd
{
    /// GAPM requested operation:
    /// - GAPM_RESET: Reset BLE subsystem: LL and HL.
    uint8_t operation;
};

/// Set device configuration command
struct gapm_set_dev_config_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_SET_DEV_CONFIG: Set device configuration
    uint8_t operation;
    /// Device Role: Central, Peripheral, Observer, Broadcaster or All roles.
    uint8_t role;

    /// -------------- Privacy Config -----------------------
    /// Duration before regenerate device address when privacy is enabled.
    uint16_t renew_dur;
    /// Provided own static private random address (addr_type = GAPM_CFG_ADDR_PRIVATE)
    bd_addr_t addr;
    /// Device IRK used for resolvable random BD address generation (LSB first)
    struct gap_sec_key irk;
    /// Device Address Type
    /// - GAPM_CFG_ADDR_PUBLIC: Device Address is a Public Static address
    /// - GAPM_CFG_ADDR_PRIVATE: Device Address is a Private Static address
    /// - GAPM_CFG_ADDR_HOST_PRIVACY: Device Address generated using Host Privacy feature
    /// - GAPM_CFG_ADDR_CTNL_PRIVACY: Device Address generated using Controller Privacy feature
    uint8_t addr_type;

    /// -------------- Security Config -----------------------

    /// Pairing mode authorized (see enum gapm_pairing_mode)
    uint8_t pairing_mode;

    /// -------------- ATT Database Config -----------------------

    /// GAP service start handle
    uint16_t gap_start_hdl;
    /// GATT service start handle
    uint16_t gatt_start_hdl;

    /// Attribute database configuration
    ///   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
    /// +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
    /// | DBG |              RFU                | SC |PCP |   APP_PERM   |   NAME_PERM  |
    /// +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
    /// - Bit [0-2] : Device Name write permission requirements for peer device (@see gapm_write_att_perm)
    /// - Bit [3-5] : Device Appearance write permission requirements for peer device (@see gapm_write_att_perm)
    /// - Bit [6]   : Slave Preferred Connection Parameters present
    /// - Bit [7]   : Service change feature present in GATT attribute database.
    /// - Bit [8-14]: Reserved
    /// - Bit [15]  : Enable Debug Mode
    uint16_t  att_cfg;

    /// -------------- LE Data Length Extension -----------------------
    ///Suggested value for the Controller's maximum transmitted number of payload octets to be used
    uint16_t sugg_max_tx_octets;
    ///Suggested value for the Controller's maximum packet transmission time to be used
    uint16_t sugg_max_tx_time;

    /// --------------- L2CAP Configuration ---------------------------
    /// Maximal MTU acceptable for device
    uint16_t max_mtu;
    /// Maximal MPS Packet size acceptable for device
    uint16_t max_mps;
    /// Maximum number of LE Credit based connection that can be established
    uint8_t  max_nb_lecb;

    /// --------------- LE Audio Mode Supported -----------------------
    ///
    /// LE Audio Mode Configuration (@see gapm_audio_cfg_flag)
    uint16_t  audio_cfg;

};

/// Set new IRK
struct gapm_set_irk_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_SET_IRK: Set device configuration
    uint8_t operation;
    /// Device IRK used for resolvable random BD address generation (LSB first)
    struct gap_sec_key irk;
};

/// Set device channel map
struct gapm_set_channel_map_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_SET_CHANNEL_MAP: Set device channel map.
    uint8_t operation;
    /// Channel map
    le_chnl_map_t chmap;
};


/// Get local device info command
struct gapm_get_dev_info_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_GET_DEV_VERSION: Get Local device version
    ///  - GAPM_GET_DEV_BDADDR: Get Local device BD Address
    ///  - GAPM_GET_DEV_ADV_TX_POWER: Get device advertising power level
    ///  - GAPM_DBG_GET_MEM_INFO: Get memory usage (debug only)
    uint8_t operation;
};

/// Local device version indication event
struct gapm_dev_version_ind
{
    /// HCI version
    uint8_t hci_ver;
    /// LMP version
    uint8_t lmp_ver;
    /// Host version
    uint8_t host_ver;
    /// HCI revision
    uint16_t hci_subver;
    /// LMP subversion
    uint16_t lmp_subver;
    /// Host revision
    uint16_t host_subver;
    /// Manufacturer name
    uint16_t manuf_name;
};

/// Local device BD Address indication event
struct gapm_dev_bdaddr_ind
{
    /// Local device address information
    struct gap_bdaddr addr;
};

/// Advertising channel Tx power level indication event
struct gapm_dev_adv_tx_power_ind
{
    /// Advertising channel Tx power level
    int8_t     power_lvl;
};

/// Cancel ongoing operation
struct gapm_cancel_cmd
{
    /// GAPM requested operation
    /// - GAPM_CANCEL: Cancel running operation
    uint8_t operation;
};


/// White List Management Command
struct gapm_white_list_mgt_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_GET_WLIST_SIZE: Get White List Size.
    ///  - GAPM_ADD_DEV_IN_WLIST: Add devices in white list.
    ///  - GAPM_RMV_DEV_FRM_WLIST: Remove devices form white list.
    ///  - GAPM_CLEAR_WLIST: Clear all devices from white list.
    uint8_t operation;
    /// Number of device information present in command
    uint8_t nb;
    /// Device address information that can be used to add or remove element in device list.
    struct gap_bdaddr devices[__ARRAY_EMPTY];
};

/// White List Size indication event
struct gapm_white_list_size_ind
{
    /// White List size
    uint8_t size;
};

/// Resolving List Management Command
struct gapm_ral_mgt_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_GET_RAL_SIZE: Get Resolving List Size.
    ///  - GAPM_GET_RAL_LOC_ADDR: Get Resolving Local Address.
    ///  - GAPM_GET_RAL_PEER_ADDR: Get Resolving Peer Address.
    ///  - GAPM_ADD_DEV_IN_RAL: Add devices in resolving list.
    ///  - GAPM_RMV_DEV_FRM_RAL: Remove devices form resolving list.
    ///  - GAPM_CLEAR_RAL: Clear all devices from resolving list.
    uint8_t operation;
    /// Number of device information present in command
    uint8_t nb;
    /// Device address information that can be used to add or remove element in device list.
    struct gap_ral_dev_info devices[__ARRAY_EMPTY];
};

/// Resolving List Size indication event
struct gapm_ral_size_ind
{
    /// Resolving List size
    uint8_t size;
};

/// Resolving Address indication event
struct gapm_ral_addr_ind
{
    /// Peer or local read operation
    uint8_t operation;
    /// Resolving List address
    struct gap_bdaddr addr;
};

/// Resolve Address command
struct gapm_resolv_addr_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_RESOLV_ADDR: Resolve device address
    uint8_t operation;
    /// Number of provided IRK (sahlle be > 0)
    uint8_t nb_key;
    /// Resolvable random address to solve
    bd_addr_t addr;
    /// Array of IRK used for address resolution (MSB -> LSB)
    struct gap_sec_key irk[__ARRAY_EMPTY];
};


/// Indicate that resolvable random address has been solved
struct gapm_addr_solved_ind
{
    /// Resolvable random address solved
    bd_addr_t addr;
    /// IRK that correctly solved the random address
    struct gap_sec_key irk;
};


/// Advertising data that contains information set by host.
struct gapm_adv_host
{
    /// Advertising mode :
    /// - GAP_NON_DISCOVERABLE: Non discoverable mode
    /// - GAP_GEN_DISCOVERABLE: General discoverable mode
    /// - GAP_LIM_DISCOVERABLE: Limited discoverable mode
    /// - GAP_BROADCASTER_MODE: Broadcaster mode
    uint8_t              mode;

    /// Advertising filter policy:
    /// - ADV_ALLOW_SCAN_ANY_CON_ANY: Allow both scan and connection requests from anyone
    /// - ADV_ALLOW_SCAN_WLST_CON_ANY: Allow both scan req from White List devices only and
    ///   connection req from anyone
    /// - ADV_ALLOW_SCAN_ANY_CON_WLST: Allow both scan req from anyone and connection req
    ///   from White List devices only
    /// - ADV_ALLOW_SCAN_WLST_CON_WLST: Allow scan and connection requests from White List
    ///   devices only
    uint8_t              adv_filt_policy;

    /// Advertising data length - maximum 28 bytes, 3 bytes are reserved to set
    /// Advertising AD type flags, shall not be set in advertising data
    uint8_t              adv_data_len;
    /// Advertising data
    uint8_t              adv_data[GAP_ADV_DATA_LEN-3];
    /// Scan response data length- maximum 31 bytes
    uint8_t              scan_rsp_data_len;
    /// Scan response data
    uint8_t              scan_rsp_data[GAP_SCAN_RSP_DATA_LEN];
    /// Peer address
    struct gap_bdaddr peer_addr;
};

/// Air operation default parameters
struct gapm_air_operation
{
    /// Operation code.
    uint8_t  code;

    /**
     * Own BD address source of the device:
     * - GAPM_STATIC_ADDR: Public or Private Static Address according to device address configuration
     * - GAPM_GEN_RSLV_ADDR: Generated resolvable private random address
     * - GAPM_GEN_NON_RSLV_ADDR: Generated non-resolvable private random address
     */
    uint8_t addr_src;

    /// Dummy data use to retrieve internal operation state (should be set to 0).
    uint16_t state;
};


/// Set advertising mode Command
struct gapm_start_advertise_cmd
{
    /// GAPM requested operation:
    /// - GAPM_ADV_NON_CONN: Start non connectable advertising
    /// - GAPM_ADV_UNDIRECT: Start undirected connectable advertising
    /// - GAPM_ADV_DIRECT: Start directed connectable advertising
    /// - GAPM_ADV_DIRECT_LDC: Start directed connectable advertising using Low Duty Cycle
    struct gapm_air_operation op;

    /// Minimum interval for advertising
    uint16_t             intv_min;
    /// Maximum interval for advertising
    uint16_t             intv_max;

    ///Advertising channel map
    uint8_t              channel_map;

    /// Advertising information
    union gapm_adv_info
    {
        /// Host information advertising data (GAPM_ADV_NON_CONN and GAPM_ADV_UNDIRECT)
        struct gapm_adv_host host;
        ///  Direct address information (GAPM_ADV_DIRECT)
        /// (used only if reconnection address isn't set or privacy disabled)
        struct gap_bdaddr direct;
    } info;
};


/// Update Advertising Data Command - On fly update when device is advertising
struct gapm_update_advertise_data_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_UPDATE_ADVERTISE_DATA: Update on the fly advertising data
    uint8_t  operation;
    /// Advertising data length - maximum 28 bytes, 3 bytes are reserved to set
    /// Advertising AD type flags, shall not be set in advertising data
    uint8_t              adv_data_len;
    /// Advertising data
    uint8_t              adv_data[GAP_ADV_DATA_LEN-3];
    /// Scan response data length- maximum 31 bytes
    uint8_t              scan_rsp_data_len;
    /// Scan response data
    uint8_t              scan_rsp_data[GAP_SCAN_RSP_DATA_LEN];
};

/// Set scan mode Command
struct gapm_start_scan_cmd
{
    /// GAPM requested operation:
    /// - GAPM_SCAN_ACTIVE: Start active scan operation
    /// - GAPM_SCAN_PASSIVE: Start passive scan operation
    struct gapm_air_operation op;

    /// Scan interval
    uint16_t             interval;
    /// Scan window size
    uint16_t             window;

    /// Scanning mode :
    /// - GAP_GEN_DISCOVERY: General discovery mode
    /// - GAP_LIM_DISCOVERY: Limited discovery mode
    /// - GAP_OBSERVER_MODE: Observer mode
    uint8_t              mode;

    /// Scan filter policy:
    /// - SCAN_ALLOW_ADV_ALL: Allow advertising packets from anyone
    /// - SCAN_ALLOW_ADV_WLST: Allow advertising packets from White List devices only
    uint8_t              filt_policy;
    /// Scan duplicate filtering policy:
    /// - SCAN_FILT_DUPLIC_DIS: Disable filtering of duplicate packets
    /// - SCAN_FILT_DUPLIC_EN: Enable filtering of duplicate packets
    uint8_t              filter_duplic;
};


/// Advertising or scanning report information event
struct gapm_adv_report_ind
{
    /// Advertising report structure
    adv_report_t report;
};


/// Set connection initialization Command
struct gapm_start_connection_cmd
{
    /// GAPM requested operation:
    /// - GAPM_CONNECTION_DIRECT: Direct connection operation
    /// - GAPM_CONNECTION_AUTO: Automatic connection operation
    /// - GAPM_CONNECTION_SELECTIVE: Selective connection operation
    /// - GAPM_CONNECTION_NAME_REQUEST: Name Request operation (requires to start a direct
    ///   connection)
    /// - GAPM_CONNECTION_GENERAL: General connection operation
    struct gapm_air_operation op;

    /// Scan interval
    uint16_t             scan_interval;
    /// Scan window size
    uint16_t             scan_window;

    /// Minimum of connection interval
    uint16_t             con_intv_min;
    /// Maximum of connection interval
    uint16_t             con_intv_max;
    /// Connection latency
    uint16_t             con_latency;
    /// Link supervision timeout
    uint16_t             superv_to;
    /// Minimum CE length
    uint16_t             ce_len_min;
    /// Maximum CE length
    uint16_t             ce_len_max;

    /// Number of peer device information present in message.
    ///  Shall be 1 for GAPM_CONNECTION_DIRECT or GAPM_CONNECTION_NAME_REQUEST operations
    ///  Shall be greater than 0 for other operations
    uint8_t              nb_peers;

    /// Peer device information
    struct gap_bdaddr   peers[__ARRAY_EMPTY];
};


/// Name of peer device indication
struct gapm_peer_name_ind
{
    /// peer device bd address
    bd_addr_t addr;
    /// peer device address type
    uint8_t addr_type;
    /// peer device name length
    uint8_t name_len;
    /// peer device name
    uint8_t name[__ARRAY_EMPTY];
};

/// Confirm connection to a specific device (Connection Operation in Selective mode)
struct gapm_connection_cfm
{
    /// peer device bd address
    bd_addr_t addr;
    /// peer device address type
    uint8_t addr_type;

    /// Minimum of connection interval
    uint16_t             con_intv_min;
    /// Maximum of connection interval
    uint16_t             con_intv_max;
    /// Connection latency
    uint16_t             con_latency;
    /// Link supervision timeout
    uint16_t             superv_to;
    /// Minimum CE length
    uint16_t             ce_len_min;
    /// Maximum CE length
    uint16_t             ce_len_max;
};

/// Generate a random address.
struct gapm_gen_rand_addr_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_GEN_RAND_ADDR: Generate a random address
    uint8_t  operation;
    /// Dummy parameter used to store the prand part of the address
    uint8_t  prand[GAP_ADDR_PRAND_LEN];
    /// Random address type @see gap_rnd_addr_type
    ///  - GAP_STATIC_ADDR: Static random address
    ///  - GAP_NON_RSLV_ADDR: Private non resolvable address
    ///  - GAP_RSLV_ADDR: Private resolvable address
    uint8_t rnd_type;
};

/// Parameters of the @ref GAPM_USE_ENC_BLOCK_CMD message
struct gapm_use_enc_block_cmd
{
    /// Command Operation Code (shall be GAPM_USE_ENC_BLOCK)
    uint8_t operation;
    /// Operand 1
    uint8_t operand_1[GAP_KEY_LEN];
    /// Operand 2
    uint8_t operand_2[GAP_KEY_LEN];
};

/// Parameters of the @ref GAPM_USE_ENC_BLOCK_IND message
struct gapm_use_enc_block_ind
{
    /// Result (16 bytes)
    uint8_t result[GAP_KEY_LEN];
};

/// Parameters of the @ref GAPM_GEN_DH_KEY_CMD message
struct gapm_gen_dh_key_cmd
{
    /// Command Operation Code (shall be GAPM_GEN_DH_KEY)
    uint8_t operation;
    /// X coordinate
    uint8_t operand_1[GAP_P256_KEY_LEN];
    /// Y coordinate
    uint8_t operand_2[GAP_P256_KEY_LEN];
};

/// Parameters of the @ref GAPM_GEN_DH_KEY_IND message
struct gapm_gen_dh_key_ind
{
    /// Result (32 bytes)
    uint8_t result[GAP_P256_KEY_LEN];
};

/// Parameters of the @ref GAPM_GEN_RAND_NB_CMD message
struct gapm_gen_rand_nb_cmd
{
    /// Command Operation Code (shall be GAPM_GEN_RAND_NB)
    uint8_t operation;
};

/// Parameters of the @ref GAPM_GEN_RAND_NB_IND message
struct gapm_gen_rand_nb_ind
{
    /// Generation Random Number (8 bytes)
    rand_nb_t randnb;
};



/// Create new task for specific profile
struct gapm_profile_task_add_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_PROFILE_TASK_ADD: Add new profile task
    uint8_t  operation;
    /// Security Level :
    ///  7    6    5    4    3    2    1    0
    /// +----+----+----+----+----+----+----+----+
    /// |   Reserved   |DIS |  AUTH   |EKS | MI |
    /// +----+----+----+----+----+----+----+----+
    ///
    /// - MI: 1 - Application task is a Multi-Instantiated task, 0 - Mono-Instantiated
    /// Only applies for service - Ignored by collectors:
    /// - EKS: Service needs a 16 bytes encryption key
    /// - AUTH: 0 - Disable, 1 - Enable, 2 - Unauth, 3 - Auth
    /// - DIS: Disable the service
    uint8_t  sec_lvl;
    /// Profile task identifier
    uint16_t prf_task_id;
    /// Application task number
    uint16_t app_task;
    /// Service start handle
    /// Only applies for services - Ignored by collectors
    /// 0: dynamically allocated in Attribute database
    uint16_t start_hdl;
    /// 32 bits value that contains value to initialize profile (database parameters, etc...)
    uint32_t param[__ARRAY_EMPTY];
};


/// Inform that profile task has been added.
struct gapm_profile_added_ind
{
    /// Profile task identifier
    uint16_t prf_task_id;
    /// Profile task number allocated
    uint16_t prf_task_nb;
    /// Service start handle
    /// Only applies for services - Ignored by collectors
    uint16_t start_hdl;
};

/// Indicate that a message has been received on an unknown task
struct gapm_unknown_task_ind
{
    /// Message identifier
    uint16_t msg_id;
    /// Task identifier
    uint16_t task_id;
};

/// Indicates suggested default data length
struct gapm_sugg_dflt_data_len_ind
{
    ///Host's suggested value for the Controller's maximum transmitted number of payload octets
    uint16_t suggted_max_tx_octets;
    ///Host's suggested value for the Controller's maximum packet transmission time
    uint16_t suggted_max_tx_time;
};

/// Indicates maximum data length
struct gapm_max_data_len_ind
{
    ///Maximum number of payload octets that the local Controller supports for transmission
    uint16_t suppted_max_tx_octets;
    ///Maximum time, in microseconds, that the local Controller supports for transmission
    uint16_t suppted_max_tx_time;
    ///Maximum number of payload octets that the local Controller supports for reception
    uint16_t suppted_max_rx_octets;
    ///Maximum time, in microseconds, that the local Controller supports for reception
    uint16_t suppted_max_rx_time;
};


/// Register a LE Protocol/Service Multiplexer command
struct gapm_lepsm_register_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_LEPSM_REG: Register a LE Protocol/Service Multiplexer
    uint8_t  operation;
    /// LE Protocol/Service Multiplexer
    uint16_t le_psm;
    /// Application task number
    uint16_t app_task;
    /// Security level
    ///   7   6   5   4   3   2   1   0
    /// +---+---+---+---+---+---+---+---+
    /// |MI |      RFU      |EKS|SEC_LVL|
    /// +---+---+---+---+---+---+---+---+
    /// bit[0-1]: Security level requirement (0=NO_AUTH, 1=UNAUTH, 2=AUTH, 3=SEC_CON)
    /// bit[2]  : Encryption Key Size length must have 16 bytes
    /// bit[7]  : Does the application task is multi-instantiated or not
    uint8_t sec_lvl;
};


/// Unregister a LE Protocol/Service Multiplexer command
struct gapm_lepsm_unregister_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_LEPSM_UNREG: Unregister a LE Protocol/Service Multiplexer
    uint8_t  operation;
    /// LE Protocol/Service Multiplexer
    uint16_t le_psm;
};

/*
 * MACROS
 ****************************************************************************************
 */


/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/// @} GAPM_TASK

#endif /* _GAPM_TASK_H_ */
