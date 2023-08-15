/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_IPC_EVENT_MGR_MBX_INTERNAL_H
#define HPM_IPC_EVENT_MGR_MBX_INTERNAL_H

#ifdef __cplusplus

extern "C" {
#endif

/**
 * @brief Initial MBX.
 */
void ipc_init_internal(void);

/**
 * @brief Enbale MBX event interrupt
 *
 * @param [in] interrupt priority
 */
void ipc_enable_event_interrupt_internal(uint32_t priority);

/**
 * @brief Disbale MBX event interrupt
 */
void ipc_disable_event_interrupt_internal(void);

/**
 * @brief Trigger MBX event
 *
 * @param [in] remote data
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t ipc_tigger_event_internal(uint32_t remote_data);

#ifdef __cplusplus
}
#endif

#endif /* HPM_IPC_EVENT_MGR_MBX_INTERNAL_H */
