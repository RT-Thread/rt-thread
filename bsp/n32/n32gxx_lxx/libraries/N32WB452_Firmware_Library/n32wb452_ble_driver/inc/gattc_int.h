/**
 ****************************************************************************************
 *
 * @file gattc_int.h
 *
 * @brief Header file - GATTC_INT.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef GATTC_TASK_INT_H_
#define GATTC_TASK_INT_H_

/**
 ****************************************************************************************
 * @addtogroup GATTC_INT Internals
 * @ingroup GATTC
 * @brief Internal features of the GATTC module
 *
 * @{
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_GATTC)
#include "gattc.h"
#include "gattc_task.h"
#include "ke_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/// retrieve on-going operation command
#define GATT_OPERATION_CMD(conidx, op_type, cmd) \
    ((struct cmd*) gattc_get_operation_ptr(conidx, op_type))

#define GATT_WRITE_ERROR_CODE (0xFFFF)


/// number of GATT Controller Process
#define GATTC_IDX_MAX                                 BLE_CONNECTION_MAX



/// states of GATT Controller task
enum gattc_state_id
{
    /// Connection ready state
    GATTC_READY = 0,
    #if (BLE_ATTC)
    /// Client operation on-going
    GATTC_CLIENT_BUSY       = (1 << GATTC_OP_CLIENT),
    /// Service Discovery Procedure operation on-going
    GATTC_SDP_BUSY          = (1 << GATTC_OP_SDP),
    #endif // (BLE_ATTC)
    #if (BLE_ATTS)
    /// Server operation on-going
    GATTC_SERVER_BUSY       = (1 << GATTC_OP_SERVER),
    #endif // (BLE_ATTS)
    /// Connection started but ATTS not ready
    GATTC_CONNECTED         = (1 << (GATTC_OP_MAX + 1)),

    /// Free state
    GATTC_FREE              = (1 << (GATTC_OP_MAX + 2)),
    /// Number of defined states.
    GATTC_STATE_MAX
};



/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */



/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */
extern struct gattc_env_tag* gattc_env[GATTC_IDX_MAX];

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Initialization of the GATT controller module.
 * This function performs all the initialization steps of the GATT module.
 *
 * @param[in] reset  true if it's requested by a reset; false if it's boot initialization
 *
 ****************************************************************************************
 */
void gattc_init(bool reset);


/**
 ****************************************************************************************
 * @brief Initialize GATT controller for connection.
 *
 * @param[in] conidx    connection record index
 * @param[in] role   device role after connection establishment
 *
 ****************************************************************************************
 */
void gattc_create(uint8_t conidx);



/**
 ****************************************************************************************
 * @brief Cleanup GATT controller resources for connection
 *
 * @param[in] conidx     connection record index
 * @param[in] disconnect True if disconnection occurs else request due to init or reset
 *
 ****************************************************************************************
 */
void gattc_cleanup(uint8_t conidx, bool disconnect);

/**
 * @brief Send a complete event of ongoing executed operation to requester.
 * It also clean-up variable used for ongoing operation.
 *
 * @param[in] conidx Connection index
 * @param[in] op_type       Operation type.
 * @param[in] status Status of completed operation
 */
void gattc_send_complete_evt(uint8_t conidx, uint8_t op_type, uint8_t status);

/**
 ****************************************************************************************
 * @brief Send operation completed message with status error code not related to a
 * running operation.
 *
 * @param[in] conidx    Connection index
 * @param[in] operation Operation code
 * @param[in] seq_num   Operation sequence number
 * @param[in] requester requester of operation
 * @param[in] status    Error status code
 ****************************************************************************************
 */
void gattc_send_error_evt(uint8_t conidx, uint8_t operation, uint16_t seq_num, const ke_task_id_t requester, uint8_t status);


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
uint8_t gattc_get_operation(uint8_t conidx, uint8_t op_type);

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
void* gattc_get_operation_ptr(uint8_t conidx, uint8_t op_type);


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
void gattc_set_operation_ptr(uint8_t conidx, uint8_t op_type, void* op);

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
bool gattc_reschedule_operation(uint8_t conidx, uint8_t op_type);

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
ke_task_id_t gattc_get_requester(uint8_t conidx, uint8_t op_type);



/**
 ****************************************************************************************
 * @brief Get Operation Sequence Number
 *
 * @param[in] conidx        Connection Index
 * @param[in] op_type       Operation type.
 *
 * @return Sequence number provided for operation execution
 ****************************************************************************************
 */
uint16_t gattc_get_op_seq_num(uint8_t conidx, uint8_t op_type);


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
void gattc_update_state(uint8_t conidx, ke_state_t state, bool busy);


/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler gattc_default_handler;
extern ke_state_t gattc_state[GATTC_IDX_MAX];


#endif // (BLE_GATTC)

/// @} GATTCTASK
#endif // GATTC_INT
