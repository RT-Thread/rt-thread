/**
 ****************************************************************************************
 *
 * @file l2cc_int.h
 *
 * @brief Header file - L2CCTASK that contains internal API.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef L2CC_INT_H_
#define L2CC_INT_H_

/**
 ****************************************************************************************
 * @addtogroup L2CCINT Internals
 * @ingroup L2CC
 * @brief Internal API for L2CC module
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_L2CC)

#include "l2cc_task.h"
#include "l2cc.h"

/*
 * MACRO DEFINITIONS
 ****************************************************************************************
 */


/// Maximum number of instances of the L2CC task
#define L2CC_IDX_MAX            (BLE_CONNECTION_MAX)

/*
 * STATES
 ****************************************************************************************
 */



/// states of L2CAP Controller task
enum l2cc_state_id
{
    /// Connection ready state
    L2CC_READY,
    /// LE signaling protocol busy
    L2CC_SIG_BUSY           = (1 << L2CC_OP_SIG),
    /// Free state
    L2CC_FREE               = 0X3F,

    /// Number of defined states.
    L2CC_STATE_MAX
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/// L2CAP environment pool
extern struct l2cc_env_tag *l2cc_env[L2CC_IDX_MAX];

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Create and Initialize the L2CAP controller task.
 *
 * @param[in] reset   true if it's requested by a reset; false if it's boot initialization
 *
 ****************************************************************************************
 */
void l2cc_init(bool reset);

/**
struct l2cc_pdu_recv_ind;
 *
 ****************************************************************************************
 * @brief Initialize the link layer controller task.
 *
 * @param[in] conidx            Connection index
 *
 ****************************************************************************************
 */
void l2cc_create(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief De-initialize the task.
 *
 * @param[in] conidx            Connection index
 * @param[in] reset   true if it's requested by a reset; false if it's boot initialization
 ****************************************************************************************
 */
void l2cc_cleanup(uint8_t conidx, bool reset);

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
void l2cc_update_state(uint8_t conidx, ke_state_t state, bool busy);


/**
 * @brief Send a complete event of ongoing executed operation to requester.
 * It also clean-up variable used for ongoing operation.
 *
 * @param[in] conidx        Connection index
 * @param[in] op_type       Operation type.
 * @param[in] status        Status of completed operation
 */
void l2cc_send_complete_evt(uint8_t conidx, uint8_t op_type, uint8_t status);

/**
 ****************************************************************************************
 * @brief Send operation completed message with status error code not related to a
 * running operation.
 *
 * @param[in] conidx    Connection index
 * @param[in] operation Operation code
 * @param[in] requester requester of operation
 * @param[in] status    Error status code
 * @param[in] cid           Channel Identifier
 ****************************************************************************************
 */
void l2cc_send_error_evt(uint8_t conidx, uint8_t operation, const ke_task_id_t requester, uint8_t status, uint16_t cid);


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
uint8_t l2cc_get_operation(uint8_t conidx, uint8_t op_type);

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
void* l2cc_get_operation_ptr(uint8_t conidx, uint8_t op_type);


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
void l2cc_set_operation_ptr(uint8_t conidx, uint8_t op_type, void* op);




/**
 ****************************************************************************************
 * @brief Perform data packet TX over HCI (call of this function is handled by L2CM
 *
 * @param[in] conidx        Connection Index
 * @param[in] nb_buffer     Number of available TX buffers
 ****************************************************************************************
 */
void l2cc_data_send(uint8_t conidx, uint8_t nb_buffer);






#endif //(BLE_L2CC)

/// @} L2CCINT

#endif // L2CC_INT_H_
