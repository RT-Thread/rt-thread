/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_IPC_EVENT_MGR_H
#define HPM_IPC_EVENT_MGR_H

#ifdef __cplusplus

extern "C" {
#endif

/**
 * @brief Type definition of event callback function pointer.
 *
 * @param [in] event data
 * @param [in] callback context data
 */
typedef void (*ipc_event_callback_t)(uint16_t event_data, void *context);

/**
 * @brief Type definition of structure with event handler and data.
 */
typedef struct {
    ipc_event_callback_t callback; /**< Pointer to callback function.*/
    void *callback_data; /**< Context data for callback.*/
} ipc_event_t;

/**
 * @brief Type definition of event types.
 */
typedef enum {
    ipc_remote_start_event = 1,
    ipc_remote_rpmsg_event,
    ipc_event_table_len
} ipc_event_type_t;

/**
 * @brief IPC Init.
 */
void ipc_init(void);

/**
 * @brief Enbale IPC event interrupt.
 *
 * @param [in] interrupt priority
 */
void ipc_enable_event_interrupt(uint32_t priority);

/**
 * @brief Disbale IPC event interrupt.
 */
void ipc_disable_event_interrupt(void);

/**
 * @brief Register IPC event
 *
 * @param [in] event type
 * @param [in] event callback function
 * @param [in] event callback data
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if the parameter is invalid
 */
hpm_stat_t ipc_register_event(ipc_event_type_t type, ipc_event_callback_t callback, void *callback_data);

/**
 * @brief Trigger IPC event
 *
 * @param [in] event type
 * @param [in] event data
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t ipc_tigger_event(ipc_event_type_t type, uint16_t event_data);

/*!
 * @brief event handler
 *
 * This function is called when event received
 *
 * @param [in] event type and data.
 */
void ipc_event_handler(uint32_t data);

#ifdef __cplusplus
}
#endif

#endif /* HPM_IPC_EVENT_MGR_H */
