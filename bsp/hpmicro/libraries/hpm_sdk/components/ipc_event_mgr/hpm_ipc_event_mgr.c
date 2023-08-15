/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_common.h"
#include "hpm_ipc_event_mgr.h"
#include "hpm_ipc_event_mgr_mbx_internal.h"

/*****************************************************************************************************************
 *
 *  Definitions
 *
 *****************************************************************************************************************/

/*****************************************************************************************************************
 *
 *  Prototypes
 *
 *****************************************************************************************************************/

/*****************************************************************************************************************
 *
 *  Variables
 *
 *****************************************************************************************************************/
static ipc_event_t s_ipc_event_table[ipc_event_table_len];

/*****************************************************************************************************************
 *
 *  Codes
 *
 *****************************************************************************************************************/
void ipc_init(void)
{
    ipc_init_internal();
}

void ipc_enable_event_interrupt(uint32_t priority)
{
    ipc_enable_event_interrupt_internal(priority);
}

void ipc_disable_event_interrupt(void)
{
    ipc_disable_event_interrupt_internal();
}

hpm_stat_t ipc_register_event(ipc_event_type_t type, ipc_event_callback_t callback, void *callback_data)
{
    hpm_stat_t status;

    if ((type >= ipc_event_table_len) || (callback == NULL)) {
        status = status_invalid_argument;
    } else {
        s_ipc_event_table[type].callback = callback;
        s_ipc_event_table[type].callback_data = callback_data;
        status = status_success;
    }

    return status;
}

hpm_stat_t ipc_tigger_event(ipc_event_type_t type, uint16_t event_data)
{
    hpm_stat_t status;
    uint32_t remote_data;

    if (type >= ipc_event_table_len) {
        status = status_invalid_argument;
    } else {
        remote_data = (((uint32_t)type) << 16) | event_data;
        ipc_tigger_event_internal(remote_data);
        status = status_success;
    }

    return status;
}

void ipc_event_handler(uint32_t data)
{
    uint16_t event_type;
    uint16_t event_data;

    if (0U != data) {
        event_type = (uint16_t)(data >> 16u);
        event_data = (uint16_t)(data & 0x0000FFFFu);

        if (((ipc_event_type_t)event_type >= ipc_remote_start_event) && ((ipc_event_type_t)event_type < ipc_event_table_len)) {
            if (s_ipc_event_table[(ipc_event_type_t)event_type].callback != NULL) {
                s_ipc_event_table[(ipc_event_type_t)event_type].callback(
                    event_data, s_ipc_event_table[(ipc_event_type_t)event_type].callback_data);
            }
        }
    }
}
