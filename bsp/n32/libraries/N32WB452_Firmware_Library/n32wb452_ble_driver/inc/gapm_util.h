/**
 ****************************************************************************************
 *
 * @file gapm_util.h
 *
 * @brief Generic Access Profile Manager Tool Box Header.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */


#ifndef _GAPM_UTIL_H_
#define _GAPM_UTIL_H_

/**
 ****************************************************************************************
 * @addtogroup GAPM_UTIL Generic Access Profile Manager Tool Box
 * @ingroup GAPM
 * @brief Generic Access Profile Manager Tool Box
 *
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include "ke_task.h"
#include "gapm.h"


/*
 * DEFINES
 ****************************************************************************************
 */
/// GAP Manager operation state - air commands
enum gapm_op_state
{
    /* state in non connected mode */
    /// Initial state of the operation
    GAPM_OP_INIT,
    /// Set operation parameters
    GAPM_OP_SET_PARAMS,
    /// Clear White List operation
    GAPM_OP_CLEAR_WL,
    /// Set White List operation
    GAPM_OP_SET_WL,
    /// Set operation advertise data
    GAPM_OP_SET_ADV_DATA,
    /// Set operation scan response data
    GAPM_OP_SET_SCAN_RSP_DATA,
    /// Generation of address
    GAPM_OP_ADDR_GEN,
    /// Set private address
    GAPM_OP_ADDR_SET,
    /// Start operation (advertising, scanning or connecting)
    GAPM_OP_START,
    /// Operation is in wait (advertising, scanning or connecting) state
    GAPM_OP_WAIT,
    /// Stop operation (advertising, scanning or connecting)
    GAPM_OP_STOP,
    /// Operation is finished
    GAPM_OP_FINISH,

    /// Error state
    GAPM_OP_ERROR,


    /* state in connected mode */
    /// Connection established
    GAPM_OP_CONNECT,
    /// Perform peer device name request
    GAPM_OP_NAME_REQ,
    /// Perform peer device disconnection
    GAPM_OP_DISCONNECT,

    /// Operation is in canceled state and shall be terminated.
    GAPM_OP_CANCEL,
    /// Operation is in timeout state and shall be terminated.
    GAPM_OP_TIMEOUT,
    /// Operation is terminated due to a timeout.
    GAPM_OP_TERM_TIMEOUT,
    /// Renew address generation
    GAPM_OP_ADDR_RENEW,
    /// initiate a connection request
    GAPM_OP_CONNECT_REQ,


    /// Mask used to retrieve operation state in state parameter
    GAPM_OP_MASK                 = 0x00FF,

    /* Specific bit fields into operation state machine */
    /// Mask used to know in state parameter if message is in kernel queue
    GAPM_OP_QUEUED_MASK          = 0x0100,

    /// Operation is in canceled state and shall be terminated.
    GAPM_OP_CANCELED_MASK        = 0x0200,

    /// Operation is in timeout state and shall be terminated.
    GAPM_OP_TIMEOUT_MASK         = 0x0400,

    /// Renew address generation
    GAPM_OP_ADDR_RENEW_MASK      = 0x0800,

    /// Mask used to know in state parameter if a connection has been initiated
    GAPM_OP_CONNECTING_MASK      = 0x1000,

    /// Mask used to know if device is currently in scanning state
    GAPM_OP_SCANNING_MASK        = 0x2000
};

/// state machine of reset operation
enum gapm_op_reset_state
{
    /// initialization of reset operation state machine
    GAPM_OP_RESET_INIT,
    /// HCI_RESET_CMD command execution completed
    GAPM_OP_RESET_HCI,
     /// SET_ADDR_CMD command execution completed add by wq
    GAPM_OP_SET_ADDR,
    /// HCI_SET_EVT_MASK_CMD command execution completed
    GAPM_OP_RESET_SET_EVT_MASK,
    /// HCI_LE_SET_EVT_MASK_CMD command execution completed
    GAPM_OP_RESET_LE_SET_EVT_MASK,
    /// HCI_RD_BD_ADDR_CMD command execution completed
    GAPM_OP_RESET_RD_BD_ADDR,
    #if (BLE_CENTRAL || BLE_PERIPHERAL)
    /// HCI_LE_RD_BUFF_SIZE_CMD command execution completed
    GAPM_OP_RESET_LE_RD_BUFF_SIZE,
    /// HCI_RD_BUFF_SIZE_CMD command execution completed
    GAPM_OP_RESET_RD_BUFF_SIZE,
    #endif // (BLE_CENTRAL || BLE_PERIPHERAL)
};

/// state machine of setup operation
enum gapm_op_setup_state
{
    /// initialization of device setup operation state machine
    GAPM_OP_SETUP_INIT,
    #if BLE_DEBUG
    GAPM_OP_SETUP_SET_4_0_LE_EVT_MASK,
    #endif // BLE_DEBUG
    /// HCI_LE_WR_SUGGTED_DFT_DATA_LEN_CMD command execution completed
    GAPM_OP_SETUP_WR_LE_DFT_DATA_LEN_CMD,
    /// HCI_LE_SET_RSLV_PRIV_ADDR_TO_CMD command execution completed
    GAPM_OP_SETUP_SET_RENEW_TO,
    /// HCI_LE_SET_ADDR_RESOL_EN_CMD command execution completed
    GAPM_OP_SETUP_EN_CTRL_PRIV,
    /// Device address management is over:
    /// HCI_RD_BD_ADDR_CMD command execution completed
    /// or HCI_LE_SET_RAND_ADDR_CMD command execution completed
    GAPM_OP_SETUP_ADDR_MGT,
    #if (SECURE_CONNECTIONS)
    /// HCI_LE_RD_LOC_P256_PUB_KEY_CMD command execution completed
    GAPM_OP_SETUP_RD_PRIV_KEY,
    #endif // (SECURE_CONNECTIONS)
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/*
 * MACROS
 ****************************************************************************************
 */
/// check if current role is supported by configuration
#define GAPM_IS_ROLE_SUPPORTED(role_type)\
    ((gapm_env.role & (role_type)) == (role_type))

/// Get current operation state
#define GAPM_GET_OP_STATE(operation) \
    ((operation).state & (GAPM_OP_MASK))

/// Set current operation state
#define GAPM_SET_OP_STATE(operation, new_state) \
    (operation).state = (((operation).state & ~(GAPM_OP_MASK)) | (new_state))


/// Get if operation is in kernel queue
#define GAPM_IS_OP_FIELD_SET(operation, field) \
        ((((operation).state) & (GAPM_OP_##field##_MASK)) != 0)

/// Set operation in kernel queue
#define GAPM_SET_OP_FIELD(operation, field) \
        ((operation).state) |= (GAPM_OP_##field##_MASK)

/// Clear operation in kernel queue
#define GAPM_CLEAR_OP_FIELD(operation, field) \
        ((operation).state)  &= ~(GAPM_OP_##field##_MASK)




/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Interface to get the device role.
 *
 * @return uint8_t device role
 *
 ****************************************************************************************
 */
uint8_t  gapm_get_role(void);


#if (BLE_BROADCASTER || BLE_PERIPHERAL)
/**
 ****************************************************************************************
 * @brief Enable or disable advertising mode.
 *
 * @param[in] en_flag       enabling flag for advertising mode
 *
 ****************************************************************************************
 */
void gapm_set_adv_mode(uint8_t en_flag);
/**
 ****************************************************************************************
 * Execute Advertising operation according to current operation state.
 ****************************************************************************************
 */
void gapm_execute_adv_op(void);


/**
 ****************************************************************************************
 * Perform a sanity check on advertising operation
 *
 * @return sanity check status: GAP_ERR_NO_ERROR if succeed, error code else.
 ****************************************************************************************
 */
uint8_t gapm_adv_op_sanity(void);

/**
 ****************************************************************************************
 * Set the advertising data
 *
 * @return length Size of the
 ****************************************************************************************
 */
void gapm_set_adv_data(uint8_t length,  uint8_t* data);

#endif // (BLE_BROADCASTER || BLE_PERIPHERAL)


#if (BLE_OBSERVER || BLE_CENTRAL)
/**
 ****************************************************************************************
 * @brief Enable or disable scanning mode.
 *
 * @param[in] en_flag           enabling flag for scanning mode
 * @param[in] filter_duplic_en  enabling duplicate filtering mode
 *
 ****************************************************************************************
 */
void gapm_set_scan_mode(uint8_t en_flag, uint8_t filter_duplic_en);


/**
 ****************************************************************************************
 * @brief retrieve AD Type Flag information in advertising data.
 *
 * @param[in] data   Advertising data
 * @param[in] length Advertising data length
 *
 * @return Advertising AD Type flag value if found, 0x00 else.
 ****************************************************************************************
 */
uint8_t gapm_get_ad_type_flag(uint8_t *data, uint8_t length);


/**
 ****************************************************************************************
 * @brief Add device to unfiltered device
 *
 * @param[in] addr       Device address
 * @param[in] addr_type  Device address type
 ****************************************************************************************
 */
void gapm_add_to_filter(bd_addr_t * addr, uint8_t addr_type);

/**
 ****************************************************************************************
 * @brief Check if device is filtered or not when a scan response data is received
 *
 * If device is not filtered (present in filter list), in that case function returns false
 * and device is removed from filtered devices.
 *
 * @param[in] addr       Device address
 * @param[in] addr_type  Device address type
 *
 * @return true if device filtered, false else.
 ****************************************************************************************
 */
bool gapm_is_filtered(bd_addr_t * addr, uint8_t addr_type);

/**
 ****************************************************************************************
 * @brief Execute Scan operation according to current operation state.
 *
 ****************************************************************************************
 */
void gapm_execute_scan_op(void);

/**
 ****************************************************************************************
 * Perform a sanity check on Scanning operation
 *
 * @return sanity check status: GAP_ERR_NO_ERROR if succeed, error code else.
 ****************************************************************************************
 */
uint8_t gapm_scan_op_sanity(void);

#endif // (BLE_OBSERVER || BLE_CENTRAL)


#if (BLE_CENTRAL)
/**
 ****************************************************************************************
 * @brief Execute Connection operation according to current operation state.
 *
 ****************************************************************************************
 */
void gapm_execute_connect_op(void);


/**
 ****************************************************************************************
 * Perform a sanity check on connection operation
 *
 * @return sanity check status: GAP_ERR_NO_ERROR if succeed, error code else.
 ****************************************************************************************
 */
uint8_t gapm_connect_op_sanity(void);

#endif // (BLE_CENTRAL)

/**
 ****************************************************************************************
 * @brief Requests current operation state to change.
 *
 *  1. Check if new state can be applied to ongoing operation.
 *  2. Verify that message is not in kernel message queue.
 *  3. If not push it into @ref TASK_GAPM message queue
 *
 * @param[in] op_type    Ongoing Air operation type (GAPM_OP_AIR)
 * @param[in] state      New state to set
 * @param[in] status     Status code of the transition
 *
 ****************************************************************************************
 */
void gapm_update_air_op_state(uint8_t op_type, uint8_t state, uint8_t status);


/**
 ****************************************************************************************
 * @brief Sends a basic HCI command (with no parameter)
 *
 * @param[in] opcode       Command opcode
 ****************************************************************************************
 */
void gapm_basic_hci_cmd_send(uint16_t opcode);

/**
 ****************************************************************************************
 * @brief General configuration for new connections (including privacy 1.2)
 *
 * @param[in] msgid       message id
 * @param[in] event       Parameters
 ****************************************************************************************
 */
void gapm_setup_conn(ke_msg_id_t const msgid, struct hci_le_enh_con_cmp_evt const *event);

/**
 ****************************************************************************************
 * @brief Get proper advertising mode
 *
 * @param[in] operation    Operation
 * @param[in] air_op       Air operation
 *
 * @return mode
 ****************************************************************************************
 */
uint8_t gapm_get_adv_mode (uint8_t operation, struct gapm_air_operation* air_op);

/**
 ****************************************************************************************
 * @brief Get local address type
 *
 * @return addres type
 ****************************************************************************************
 */
uint8_t gapm_get_local_addrtype (void);


/**
 ****************************************************************************************
 * Handles the Reset state machine
 *
 *
 * @param[in] current_state  Current operation state (@see enum gapm_reset_state)
 * @param[in] status         Current operation status
 ****************************************************************************************
 */
void gapm_op_reset_continue(uint8_t current_state, uint8_t status);

/**
 ****************************************************************************************
 * Handles the Device Setup state machine
 *
 *
 * @param[in] current_state  Current operation state (@see enum gapm_reset_state)
 * @param[in] status         Current operation status
 ****************************************************************************************
 */
void gapm_op_setup_continue(uint8_t current_state, uint8_t status);

/// @} GAPM_UTIL

#endif /* _GAPM_UTIL_H_ */
