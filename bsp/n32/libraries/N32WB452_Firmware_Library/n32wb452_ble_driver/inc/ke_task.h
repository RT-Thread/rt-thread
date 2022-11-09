/**
 ****************************************************************************************
 *
 * @file ke_task.h
 *
 * @brief This file contains the definition related to kernel task management.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _KE_TASK_H_
#define _KE_TASK_H_

/**
 ****************************************************************************************
 * @defgroup TASK Task and Process
 * @ingroup KERNEL
 * @brief Task management module.
 *
 * This module implements the functions used for managing tasks.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>          // standard integer
#include <stdbool.h>         // standard boolean

#include "rwip_config.h"     // stack configuration
#include "ble_arch.h"        // compiler defines, INLINE
#include "ke_msg.h"          // kernel message defines

/* Default Message handler code to handle several message type in same handler. */
#define KE_MSG_DEFAULT_HANDLER  (0xFFFF)
/* Invalid task */
#define KE_TASK_INVALID         (0xFFFF)
/* Used to know if a message is not present in kernel queue */
#define KE_MSG_NOT_IN_QUEUE     ((struct co_list_hdr *) 0xFFFFFFFF)

/// Status of ke_task API functions
enum KE_TASK_STATUS
{
    KE_TASK_OK = 0,
    KE_TASK_FAIL,
    KE_TASK_UNKNOWN,
    KE_TASK_CAPA_EXCEEDED,
    KE_TASK_ALREADY_EXISTS,
};


#define MSG_T(msg)         ((ke_task_id_t)((msg) >> 8))
#define MSG_I(msg)         ((msg) & ((1<<8)-1))

/// Format of a task message handler function
typedef int (*ke_msg_func_t)(ke_msg_id_t const msgid, void const *param,
                             ke_task_id_t const dest_id, ke_task_id_t const src_id);

/// Macro for message handler function declaration or definition
#define KE_MSG_HANDLER(msg_name, param_struct)   __STATIC int msg_name##_handler(ke_msg_id_t const msgid,     \
                                                                                param_struct const *param,  \
                                                                                ke_task_id_t const dest_id, \
                                                                                ke_task_id_t const src_id)

/// Macro for message handlers table declaration or definition
#define KE_MSG_HANDLER_TAB(task)   __STATIC const struct ke_msg_handler task##_default_state[] =

/// Macro for state handler declaration or definition
#define KE_MSG_STATE(task) const struct ke_state_handler task##_default_handler = KE_STATE_HANDLER(task##_default_state);

/// Element of a message handler table.
struct ke_msg_handler
{
    /// Id of the handled message.
    ke_msg_id_t id;
    /// Pointer to the handler function for the msgid above.
    ke_msg_func_t func;
};

/// Element of a state handler table.
struct ke_state_handler
{
    /// Pointer to the message handler table of this state.
    const struct ke_msg_handler *msg_table;
    /// Number of messages handled in this state.
    uint16_t msg_cnt;
};

/// Helps writing the initialization of the state handlers without errors.
#define KE_STATE_HANDLER(hdl) {hdl, sizeof(hdl)/sizeof(struct ke_msg_handler)}

/// Helps writing empty states.
#define KE_STATE_HANDLER_NONE {NULL, 0}

/// Task descriptor grouping all information required by the kernel for the scheduling.
struct ke_task_desc
{
    /// Pointer to the state handler table (one element for each state).
    const struct ke_state_handler* state_handler;
    /// Pointer to the default state handler (element parsed after the current state).
    const struct ke_state_handler* default_handler;
    /// Pointer to the state table (one element for each instance).
    ke_state_t* state;
    /// Maximum number of states in the task.
    uint16_t state_max;
    /// Maximum index of supported instances of the task.
    uint16_t idx_max;
};

/*
 * FUNCTION PROTOTYPES
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Initialize Kernel task module.
 ****************************************************************************************
 */
void ke_task_init(void);

/**
 ****************************************************************************************
 * @brief Create a task.
 *
 * @param[in]  task_type       Task type.
 * @param[in]  p_task_desc     Pointer to task descriptor.
 *
 * @return                     Status
 ****************************************************************************************
 */
uint8_t ke_task_create(uint8_t task_type, struct ke_task_desc const * p_task_desc);

/**
 ****************************************************************************************
 * @brief Delete a task.
 *
 * @param[in]  task_type       Task type.
 *
 * @return                     Status
 ****************************************************************************************
 */
uint8_t ke_task_delete(uint8_t task_type);

/**
 ****************************************************************************************
 * @brief Retrieve the state of a task.
 *
 * @param[in]  id   Task id.
 *
 * @return          Current state of the task
 ****************************************************************************************
 */
ke_state_t ke_state_get(ke_task_id_t const id);

/**
 ****************************************************************************************
 * @brief Set the state of the task identified by its Task Id.
 *
 * In this function we also handle the SAVE service: when a task state changes we
 * try to activate all the messages currently saved in the save queue for the given
 * task identifier.
 *
 * @param[in]  id          Identifier of the task instance whose state is going to be modified
 * @param[in]  state_id    New State
 *
 ****************************************************************************************
 */
void ke_state_set(ke_task_id_t const id, ke_state_t const state_id);

/**
 ****************************************************************************************
 * @brief Generic message handler to consume message without handling it in the task.
 *
 * @param[in] msgid Id of the message received (probably unused)
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id TaskId of the receiving task.
 * @param[in] src_id TaskId of the sending task.
 *
 * @return KE_MSG_CONSUMED
 ****************************************************************************************
 */
int ke_msg_discard(ke_msg_id_t const msgid, void const *param,
                   ke_task_id_t const dest_id, ke_task_id_t const src_id);

/**
 ****************************************************************************************
 * @brief Generic message handler to consume message without handling it in the task.
 *
 * @param[in] msgid Id of the message received (probably unused)
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id TaskId of the receiving task.
 * @param[in] src_id TaskId of the sending task.
 *
 * @return KE_MSG_CONSUMED
 ****************************************************************************************
 */
int ke_msg_save(ke_msg_id_t const msgid, void const *param,
                ke_task_id_t const dest_id, ke_task_id_t const src_id);



/**
 ****************************************************************************************
 * @brief This function flushes all messages, currently pending in the kernel for a
 * specific task.
 *
 * @param[in] task The Task Identifier that shall be flushed.
 ****************************************************************************************
 */
void ke_task_msg_flush(ke_task_id_t task);


/**
 ****************************************************************************************
 * @brief Check validity of a task. If task type or task instance does not exist,
 * return invalid task
 *
 * @param[in] task Task Identifier to check.
 *
 * @return Task identifier if valid, invalid identifier else.
 ****************************************************************************************
 */
ke_task_id_t ke_task_check(ke_task_id_t task);

/// @} TASK

#endif // _KE_TASK_H_

