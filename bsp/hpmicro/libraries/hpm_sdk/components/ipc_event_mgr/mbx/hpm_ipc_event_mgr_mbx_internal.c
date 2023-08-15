/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc.h"
#include "hpm_mbx_drv.h"
#include "hpm_ipc_event_mgr.h"
#include "hpm_ipc_event_mgr_mbx_config.h"
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
static void mbx_isr(void);
SDK_DECLARE_EXT_ISR_M(IRQn_MBX, mbx_isr)

/*****************************************************************************************************************
 *
 *  Variables
 *
 *****************************************************************************************************************/

/*****************************************************************************************************************
 *
 *  Codes
 *
 *****************************************************************************************************************/
void ipc_init_internal(void)
{
    mbx_init(HPM_MBX);
}

void ipc_enable_event_interrupt_internal(uint32_t priority)
{
    mbx_enable_intr(HPM_MBX, MBX_CR_RWMVIE_MASK);
    intc_m_enable_irq_with_priority(IRQn_MBX, priority);
}

void ipc_disable_event_interrupt_internal(void)
{
    mbx_disable_intr(HPM_MBX, MBX_CR_RWMVIE_MASK);
    intc_m_disable_irq(IRQn_MBX);
}

hpm_stat_t ipc_tigger_event_internal(uint32_t remote_data)
{
    return mbx_send_message(HPM_MBX, remote_data);
}

/*!
 * @brief ISR handler
 *
 * This function is called when data from MBX is received
 */
static void mbx_isr(void)
{
    uint32_t data;
    hpm_stat_t state;

    state = mbx_retrieve_message(HPM_MBX, &data);

    if (state == status_success) {
        ipc_event_handler(data);
    }
}
