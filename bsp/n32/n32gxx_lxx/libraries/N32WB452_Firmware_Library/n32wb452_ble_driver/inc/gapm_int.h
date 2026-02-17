/**
 ****************************************************************************************
 *
 * @file gapm_int.h
 *
 * @brief Generic Access Profile Manager Internal Header.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */


#ifndef _GAPM_INT_H_
#define _GAPM_INT_H_

/**
 ****************************************************************************************
 * @addtogroup GAPM_INT Generic Access Profile Manager Internal
 * @ingroup GAPM
 * @brief defines for internal GAPM usage
 *
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "gapm.h"
#include "gapm_task.h"
#include "co_bt.h"


/*
 * DEFINES
 ****************************************************************************************
 */

/// Maximum number of GAP Manager process
#define GAPM_IDX_MAX                                 0x01


/// Scan filter size
#define GAPM_SCAN_FILTER_SIZE   10



/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */


/// Retrieve information about memory usage
struct gapm_dbg_get_mem_info_cmd
{
    /// GAPM requested operation:
    ///  - GAPM_DBG_GET_MEM_INFO: Get memory usage
    uint8_t operation;
};

/// Indication containing information about memory usage.
struct gapm_dbg_mem_info_ind
{
    /// peak of memory usage measured
    uint32_t max_mem_used;
    /// memory size currently used into each heaps.
    uint16_t mem_used[KE_MEM_BLOCK_MAX];
};


/// Operation type
enum gapm_op_type
{
    /// Configuration operation
    GAPM_OP_CFG         = 0x00,

    /// Air mode operation (scanning, advertising, connection establishment)
    /// Note: Restriction, only one air operation supported.
    GAPM_OP_AIR         = 0x01,
#if (SECURE_CONNECTIONS)
    /// GAP State for DH Key Generation
    GAPM_OP_DHKEY       = 0x02,
#endif // (SECURE_CONNECTIONS)
    /// Max number of operations
    GAPM_OP_MAX
};


/// GAPM states
enum gapm_state_id
{
    /// Idle state - no on going operation
    GAPM_IDLE,

    /// Busy state - Configuration operation on going
    GAPM_CFG_BUSY       = 1 << GAPM_OP_CFG,
    /// Busy state - Air operation on going
    GAPM_AIR_BUSY       = 1 << GAPM_OP_AIR,
    #if (SECURE_CONNECTIONS)
    /// Busy state - DH Key Calculation operation on going
    GAPM_DHKEY_BUSY     = 1 << GAPM_OP_DHKEY,
    #endif //  (SECURE_CONNECTIONS)

    /// Reset state - Reset operation on going
    GAPM_DEVICE_SETUP   = 1 << GAPM_OP_MAX,

    GAPM_STATE_MAX
};
/// Device configuration flags
///    7    6    5    4    3    2    1    0
/// +-----+----+----+----+----+----+----+----+
/// | DBG | SC | CP | GA | RE |CTLP|HSTP|ADDR|
/// +-----+----+----+----+----+----+----+----+
/// - Bit [0-2]: Address Type @see enum gapm_cfg_flag
///             Bit 0: 0 = Public address, 1 = Private address
///             Bit 1: 0 = Host-based Privacy disabled, 1 = enabled
///             Bit 2: 0 = Controller-based Privacy disabled, 1 = enabled
///
/// - Bit [3]  : Address to renew (only if privacy is enabled, 1 address to renew else 0)
/// - Bit [4]  : Generated Address type (1 = Resolvable, 0 = Non Resolvable)
/// - Bit [5]  : Preferred Connection parameters present in GAP DB
/// - Bit [6]  : Service Change feature present
/// - Bit [7]  : Enable Debug mode

/// Configuration flag bit description
enum gapm_cfg_flag_def
{
    /// Address Type
    GAPM_MASK_ADDR_TYPE           = 0x07,
    GAPM_POS_ADDR_TYPE            = 0x00,
    /// Address to renew
    GAPM_MASK_ADDR_RENEW          = 0x08,
    GAPM_POS_ADDR_RENEW           = 0x03,
    /// Generated Address type
    GAPM_MASK_RESOLV_ADDR         = 0x10,
    GAPM_POS_RESOLV_ADDR          = 0x04,
    /// Preferred Connection parameters present in GAP DB
    GAPM_MASK_PREF_CON_PAR_PRES   = 0x20,
    GAPM_POS_PREF_CON_PAR_PRES    = 0x05,
    /// Service Change feature present
    GAPM_MASK_SVC_CHG_EN          = 0x40,
    GAPM_POS_SVC_CHG_EN           = 0x06,

#if (BLE_DEBUG)
    /// L2CAP Debug Mode used to force LE-frames
    GAPM_MASK_DBG_MODE_EN         = 0x80,
    GAPM_POS_DBG_MODE_EN          = 0x07,
#endif // (BLE_DEBUG)

};


/*
 * MACROS
 ****************************************************************************************
 */
/// Macro used to retrieve field
#define GAPM_F_GET(data, field)\
        (((data) & (GAPM_MASK_ ## field)) >> (GAPM_POS_ ## field))

/// Macro used to set field
#define GAPM_F_SET(data, field, val)\
    (data) = (((data) & ~(GAPM_MASK_ ## field)) \
           | ((val << (GAPM_POS_ ## field)) & (GAPM_MASK_ ## field)))

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Information about registered LE_PSM
struct gapm_le_psm_info
{
    /// List header structure to put information within a list
    struct co_list_hdr hdr;

    /// LE Protocol/Service Multiplexer
    uint16_t le_psm;

    /// Registered task identifier
    ke_task_id_t task_id;

    /// Security level
    ///   7   6   5   4   3   2   1   0
    /// +---+---+---+---+---+---+---+---+
    /// |MI |      RFU      |EKS|SEC_LVL|
    /// +---+---+---+---+---+---+---+---+
    /// bit[0-1]: Security level requirement (0=NO_AUTH, 1=UNAUTH, 2=AUTH, 3=SEC_CON)
    /// bit[2]  : Encryption Key Size length must have 16 bytes
    /// bit[7]  : Multi-instantiated task
    uint8_t sec_lvl;

    /// Number of established link
    uint8_t nb_est_lk;
};

/// GAP Manager environment structure
struct gapm_env_tag
{
    /// Request operation Kernel message
    void* operation[GAPM_OP_MAX];

    #if (BLE_CENTRAL || BLE_OBSERVER)
    /// Scan filtering Array
    struct gap_bdaddr* scan_filter;
    #endif // (BLE_CENTRAL || BLE_OBSERVER)

    #if (BLE_LECB)
    /// Registered list of LE Protocol/Service Multiplexer for LE Credit Based Connection
    struct co_list reg_le_psm;
    #endif // (BLE_LECB)

    #if (BLE_ATTS)
    /// GAP service start handle
    uint16_t svc_start_hdl;
    #endif // (BLE_ATTS)

    /// Duration before regenerate device address when privacy is enabled.
    uint16_t renew_dur;
    /// Device IRK used for resolvable random BD address generation (MSB -> LSB)
    struct gap_sec_key irk;

    /// Current device Address
    bd_addr_t addr;
    /// Device Role
    uint8_t role;
    /// Number of BLE connection
    uint8_t connections;
    /// Device configuration flags - (@see enum gapm_cfg_flag_def)
    uint8_t cfg_flags;
    /// Pairing mode authorized (see enum gapm_pairing_mode)
    uint8_t pairing_mode;
    /// Maximum device MTU size
    uint16_t max_mtu;
    /// Maximum device MPS size
    uint16_t max_mps;
    #if (SECURE_CONNECTIONS)
    /// Local device Public Key
    public_key_t public_key;
    #endif // (SECURE_CONNECTIONS)

    #if (BLE_AUDIO)
    /// Audio configuration flag (see gapm_audio_cfg_flag)
    uint16_t audio_cfg;
    #endif // (BLE_AUDIO)

    #if (BLE_EMB_PRESENT && HCI_TL_SUPPORT)
    /// In Full mode, by default the AHI API is used, but if an HCI Reset is received,
    /// TL is switched to HCI and embedded host is disabled
    bool embedded_host;
    #endif // (BLE_EMB_PRESENT && HCI_TL_SUPPORT)

    #if (BLE_LECB)
    /// Maximum number of allowed LE Credit Based channels
    uint8_t max_nb_lecb;
    /// Current number of LE Credit Based channel connections established
    uint8_t nb_lecb;
    #endif // (BLE_LECB)
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */
/// GAP Manager environment variable.
extern struct gapm_env_tag gapm_env;


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize GAP attribute database
 *
 * @param[in] start_hdl Service Start Handle
 * @param[in] feat      Attribute database features
 *
 * @return status code of attribute database initialization
 *  - @ref ATT_ERR_NO_ERROR: If database creation succeeds.
 *  - @ref ATT_ERR_INVALID_HANDLE: If start_hdl given in parameter + nb of attribute override
 *                            some existing services handles.
 *  - @ref ATT_ERR_INSUFF_RESOURCE: There is not enough memory to allocate service buffer.
 *                           or of new attribute cannot be added because all expected
 *                           attributes already add
 ****************************************************************************************
 */
uint8_t gapm_init_attr(uint16_t start_hdl, uint32_t feat);

/**
 ****************************************************************************************
 * @brief Send operation completed message according to operation type.
 * Perform also am operation clean-up
 *
 * @param[in] op_type Operation type
 * @param[in] status  Command status
 *****************************************************************************************
 */
void gapm_send_complete_evt(uint8_t op_type, uint8_t status);

/**
 ****************************************************************************************
 * @brief Send operation completed message with status error code not related to a
 * running operation.
 *
 * @param[in] operation Operation code
 * @param[in] requester requester of operation
 * @param[in] status    Error status code
 ****************************************************************************************
 */
void gapm_send_error_evt(uint8_t operation, const ke_task_id_t requester, uint8_t status);


/**
 ****************************************************************************************
 * @brief Get operation pointer
 *
 * @param[in] op_type       Operation type.
 *
 * @return operation pointer on going
 ****************************************************************************************
 */
__INLINE void* gapm_get_operation_ptr(uint8_t op_type)
{
    ASSERT_ERR(op_type < GAPM_OP_MAX);
    // return operation pointer
    return gapm_env.operation[op_type];
}


/**
 ****************************************************************************************
 * @brief Set operation pointer
 *
 * @param[in] op_type       Operation type.
 * @param[in] op            Operation pointer.
 *
 ****************************************************************************************
 */
__INLINE void gapm_set_operation_ptr(uint8_t op_type, void* op)
{
    ASSERT_ERR(op_type < GAPM_OP_MAX);
    // update operation pointer
    gapm_env.operation[op_type] = op;
}


/**
 ****************************************************************************************
 * @brief Get operation on going
 *
 * @param[in] op_type       Operation type.
 *
 * @return operation code on going
 ****************************************************************************************
 */
uint8_t gapm_get_operation(uint8_t op_type);


/**
 ****************************************************************************************
 * @brief Operation execution not finish, request kernel to reschedule it in order to
 * continue its execution
 *
 * @param[in] op_type       Operation type.
 *
 * @return if operation has been rescheduled (not done if operation pointer is null)
 ****************************************************************************************
 */
bool gapm_reschedule_operation(uint8_t op_type);

/**
 ****************************************************************************************
 * @brief Get requester of on going operation
 *
 * @param[in] op_type       Operation type.
 *
 * @return task that requests to execute the operation
 ****************************************************************************************
 */
ke_task_id_t gapm_get_requester(uint8_t op_type);




#if (BLE_GAPC)
/**
 ****************************************************************************************
 * @brief A connection has been created, initialize host stack to be ready for connection.
 *
 * @param[in] msgid      Message id
 * @param[in] operation  Air operation type
 * @param[in] con_params Connection parameters from lower layers
 *
 * @return Connection index allocated to the new connection.
 ****************************************************************************************
 */
uint8_t gapm_con_create(ke_msg_id_t const msgid, uint8_t operation, struct hci_le_enh_con_cmp_evt const *con_params);

#endif // (BLE_GAPC)

/**
 ****************************************************************************************
 * Retrieve if current connection index is used for a discovery purpose such as
 * Name discovery
 *
 * @param conidx Index of the specific connection
 *
 * @return true if connection has a discovery purpose, False else
 ****************************************************************************************
 */
bool gapm_is_disc_connection(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Set the maximal MTU value
 *
 * @param[in] mtu   Max MTU value (Minimum is 23)
 ****************************************************************************************
 */
void gapm_set_max_mtu(uint16_t mtu);

/**
 ****************************************************************************************
 * @brief Set the maximal MPS value
 *
 * @param[in] mps   Max MPS value (Minimum is 23)
 ****************************************************************************************
 */
void gapm_set_max_mps(uint16_t mps);

/**
 ****************************************************************************************
 * @brief Checks validity of the address type
 *
 * @param[in] addr_type   Address type
 ****************************************************************************************
 */
uint8_t gapm_addr_check( uint8_t addr_type);

/**
 ****************************************************************************************
 * @brief Checks validity of the Data Length Suggested values
 *
 * @param[in] sugg_oct   Suggested octets
 * @param[in] sugg_time  Suggested time
 ****************************************************************************************
 */
uint8_t gapm_dle_val_check(uint16_t sugg_oct, uint16_t sugg_time);



/**
 ****************************************************************************************
 * @brief Update task state
 *
 * @param[in] operation that modify the state
 * @param[in] set state to busy (true) or idle (false)
 *
 ****************************************************************************************
 */
void gapm_update_state(uint8_t operation, bool busy);



#if (BLE_LECB)


/**
 ****************************************************************************************
 * @brief Find Information about LE_PSM registered in GAPM
 *
 * @param[in] le_psm    LE Protocol/Service Multiplexer
 *
 * @return Null if not found or LE_PSM info structure
 ****************************************************************************************
 */
struct gapm_le_psm_info* gapm_le_psm_find(uint16_t le_psm);


/**
 ****************************************************************************************
 * @brief Remove all registered LE_PSM
 ****************************************************************************************
 */
void gapm_le_psm_cleanup(void);
#endif // (BLE_LECB)

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler gapm_default_handler;
extern ke_state_t gapm_state[GAPM_IDX_MAX];

/// @} GAPM_INT

#endif /* _GAPM_INT_H_ */
