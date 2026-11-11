/**
 ****************************************************************************************
 *
 * @file gapc_int.h
 *
 * @brief Generic Access Profile Controller Internal Header.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */
#ifndef _GAPC_INT_H_
#define _GAPC_INT_H_

/**
 ****************************************************************************************
 * @addtogroup GAPC_INT Generic Access Profile Controller Internals
 * @ingroup GAPC
 * @brief Handles ALL Internal GAPC API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "gapc.h"
#include "gapc_task.h"

#if (BLE_GAPC)

/*
 * MACROS
 ****************************************************************************************
 */

/// Set link configuration field
#define GAPC_SET_FIELD(conidx, field, value)\
    (gapc_env[conidx]->fields) = ((gapc_env[conidx]->fields) & (~GAPC_##field##_MASK)) \
                                     | (((value) << GAPC_##field) & (GAPC_##field##_MASK))


/// Get link configuration field
#define GAPC_GET_FIELD(conidx, field)\
    (((gapc_env[conidx]->fields) & (GAPC_##field##_MASK)) >> GAPC_##field)


/*
 * DEFINES
 ****************************************************************************************
 */

/// number of GAP Controller Process
#define GAPC_IDX_MAX                                 BLE_CONNECTION_MAX




/// states of GAP Controller task
enum gapc_state_id
{
    /// Connection ready state
    GAPC_READY,

    /// Link Operation on-going
    GAPC_LINK_INFO_BUSY     = (1 << GAPC_OP_LINK_INFO),
    /// SMP Operation  on-going
    GAPC_SMP_BUSY           = (1 << GAPC_OP_SMP),
    /// Update Operation  on-going
    GAPC_LINK_UPD_BUSY      = (1 << GAPC_OP_LINK_UPD),
    /// SMP start encryption on-going
    GAPC_ENCRYPT_BUSY       = (1 << GAPC_OP_MAX),

    /// Disconnection  on-going
    GAPC_DISC_BUSY          = 0x1F,
    /// Free state
    GAPC_FREE               = 0X3F,

    /// Number of defined states.
    GAPC_STATE_MAX
};



/// fields definitions.
/// Configuration fields:
///    7    6    5    4    3    2    1    0
/// +----+----+----+----+----+----+----+----+
/// |RFU |SVCH|ROLE|LTK |ENC |BOND| SEC_LVL |
/// +----+----+----+----+----+----+----+----+
enum gapc_fields
{
    /// Link Security Level
    GAPC_SEC_LVL          = 0,
    GAPC_SEC_LVL_MASK     = 0x03,
    /// Link Bonded or not
    GAPC_BONDED           = 2,
    GAPC_BONDED_MASK      = 0x04,
    /// Encrypted connection or not
    GAPC_ENCRYPTED        = 3,
    GAPC_ENCRYPTED_MASK   = 0x08,
    /// Ltk present and exchanged during pairing
    GAPC_LTK_PRESENT       = 4,
    GAPC_LTK_PRESENT_MASK  = 0x10,
    /// Local connection role
    GAPC_ROLE             = 5,
    GAPC_ROLE_MASK        = 0x20,
    /// Service Changed CCC configuration
    GAPC_SVC_CHG_CCC      = 6,
    GAPC_SVC_CHG_CCC_MASK = 0x40,
};


/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */
extern struct gapc_env_tag* gapc_env[GAPC_IDX_MAX];


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize Generic Access Profile Controller Module.
 *
 * @param[in] reset  true if it's requested by a reset; false if it's boot initialization
 *
 ****************************************************************************************
 */
void gapc_init(bool reset);


/**
 ****************************************************************************************
 * @brief A connection has been created, initialize Controller task.
 *
 * This function find first available task index available for new connection.
 * It triggers also connection event to task that has requested the connection.
 *
 * @param[in] msgid      Message id for normal or enhanced privacy
 * @param[in] con_params Connection parameters from lower layers
 * @param[in] requester  Task that request the connection to send indication(s)
 * @param[in] laddr      Local BD Address
 * @param[in] laddr_type Local BD Address Type (PUBLIC or RAND)
 *
 * @return Connection index allocated to the new connection.
 ****************************************************************************************
 */
uint8_t gapc_con_create(ke_msg_id_t const msgid, struct hci_le_enh_con_cmp_evt const *con_params,
                        ke_task_id_t requester, bd_addr_t* laddr, uint8_t laddr_type);

/**
 ****************************************************************************************
 * @brief A connection has been disconnected, uninitialized Controller task.
 *
 * unregister connection, and destroy environment variable allocated for current connection.
 *
 * @param[in] conidx  Connection index
 *
 * @return Connection index of the connection.
 ****************************************************************************************
 */
uint8_t gapc_con_cleanup(uint8_t conidx);


/**
 ****************************************************************************************
 * @brief Send Disconnection indication to specific task
 *
 * @param[in] conidx  Connection index
 * @param[in] reason  Disconnection reason
 * @param[in] conhdl  Connection handle
 * @param[in] dest_id Message destination ID
 *
 ****************************************************************************************
 */
void gapc_send_disconect_ind(uint8_t conidx,  uint8_t reason, uint8_t conhdl,
                              ke_task_id_t dest_id);



/**
 ****************************************************************************************
 * @brief Retrieve connection CSRK information on current link.
 *
 * @param[in] conidx Connection index
 * @param[in] src    Connection information source
 *
 * @return Return found connection CSRK
 ****************************************************************************************
 */
struct gap_sec_key* gapc_get_csrk(uint8_t conidx, uint8_t src);

/**
 ****************************************************************************************
 * @brief Return the sign counter value for the specified connection index.
 *
 * @param[in] conidx Connection index
 * @param[in] src    Connection information source
 *
 * @return the requested signCounter value
 ****************************************************************************************
 */
uint32_t gapc_get_sign_counter(uint8_t conidx, uint8_t src);

/**
 * @brief Send a complete event of ongoing executed operation to requester.
 * It also clean-up variable used for ongoing operation.
 *
 * @param[in] conidx Connection index
 * @param[in] op_type       Operation type.
 * @param[in] status Status of completed operation
 */
void gapc_send_complete_evt(uint8_t conidx, uint8_t op_type, uint8_t status);

/**
 ****************************************************************************************
 * @brief Send operation completed message with status error code not related to a
 * running operation.
 *
 * @param[in] conidx    Connection index
 * @param[in] operation Operation code
 * @param[in] requester requester of operation
 * @param[in] status    Error status code
 ****************************************************************************************
 */
void gapc_send_error_evt(uint8_t conidx, uint8_t operation, const ke_task_id_t requester, uint8_t status);


/**
 ****************************************************************************************
 * @brief Get operation on going
 *
 * @param[in] conidx        Connection Index
 * @param[in] op_type       Operation type.
 *
 * @return operation code on going
 ****************************************************************************************
 */
uint8_t gapc_get_operation(uint8_t conidx, uint8_t op_type);

/**
 ****************************************************************************************
 * @brief Get operation pointer
 *
 * @param[in] conidx        Connection Index
 * @param[in] op_type       Operation type.
 *
 * @return operation pointer on going
 ****************************************************************************************
 */
void* gapc_get_operation_ptr(uint8_t conidx, uint8_t op_type);


/**
 ****************************************************************************************
 * @brief Set operation pointer
 *
 * @param[in] conidx        Connection Index
 * @param[in] op_type       Operation type.
 * @param[in] op            Operation pointer.
 *
 ****************************************************************************************
 */
void gapc_set_operation_ptr(uint8_t conidx, uint8_t op_type, void* op);

/**
 ****************************************************************************************
 * @brief Operation execution not finish, request kernel to reschedule it in order to
 * continue its execution
 *
 * @param[in] conidx        Connection Index
 * @param[in] op_type       Operation type.
 *
 * @return if operation has been rescheduled (not done if operation pointer is null)
 ****************************************************************************************
 */
bool gapc_reschedule_operation(uint8_t conidx, uint8_t op_type);

/**
 ****************************************************************************************
 * @brief Get requester of on going operation
 *
 * @param[in] conidx        Connection Index
 * @param[in] op_type       Operation type.
 *
 * @return task that requests to execute the operation
 ****************************************************************************************
 */
ke_task_id_t gapc_get_requester(uint8_t conidx, uint8_t op_type);




/**
 ****************************************************************************************
 * @brief Set the encryption key size of the connection
 *
 * @param[in] conidx Connection index
 * @param[in] key_size encryption key size (size is 7 - 16 byte range)
 *
 ****************************************************************************************
 */
void gapc_enc_keysize_set(uint8_t conidx, uint8_t key_size);


/**
 ****************************************************************************************
 * @brief Update link status, current link is now encrypted
 *
 * @param[in] conidx Connection index
 *
 ****************************************************************************************
 */
void gapc_link_encrypted(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Update link authentication level
 *
 * @param[in] conidx      Connection index
 * @param[in] auth        Link authentication level
 * @param[in] ltk_present Link paired and an LTK has been exchanged
 *
 ****************************************************************************************
 */
void gapc_auth_set(uint8_t conidx, uint8_t auth, bool ltk_present);

/**
 ****************************************************************************************
 * @brief Retrieve link authentication level
 *
 * @param[in] conidx Connection index
 * @return Link authentication level
 ****************************************************************************************
 */
uint8_t gapc_auth_get(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Update task state
 *
 * @param[in] conidx Connection index
 * @param[in] state to update
 * @param[in] set state to busy (true) or idle (false)
 *
 ****************************************************************************************
 */
void gapc_update_state(uint8_t conidx, ke_state_t state, bool busy);


/**
 ****************************************************************************************
 * @brief Checks connection parameters values
 *
 * @param[in] intv_max          maximum interval
 * @param[in] intv_min          minimum interval
 * @param[in] latency           latency
 * @param[in] timeout           timeout value
 *
 * @return true if OK, false if not OK
 ****************************************************************************************
 */
bool gapc_param_update_sanity(uint16_t intv_max, uint16_t intv_min, uint16_t latency, uint16_t timeout);

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
int gapc_process_op(uint8_t conidx, uint8_t op_type, void* op_msg, enum gapc_operation* supp_ops);




/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler gapc_default_handler;
extern ke_state_t gapc_state[GAPC_IDX_MAX];

#endif // (BLE_GAPC)
/// @} GAPC_INT

#endif /* _GAPC_INT_H_ */
