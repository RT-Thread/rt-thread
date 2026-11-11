/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/** @} (end addtogroup BSP_MCU) */

#ifndef BSP_IPC_H
#define BSP_IPC_H

#ifdef R_IPC

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Semaphore handle for IPC semaphores. */
typedef struct st_bsp_ipc_semaphore_handle
{
    uint8_t semaphore_num;             ///< Semaphore number, controls which IPCSEMn register is used.
} bsp_ipc_semaphore_handle_t;

/** IPC NMI callback type. */
typedef void (* bsp_ipc_nmi_cb_t)(void);

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

fsp_err_t R_BSP_IpcSemaphoreTake(bsp_ipc_semaphore_handle_t const * const p_semaphore_handle);
fsp_err_t R_BSP_IpcSemaphoreGive(bsp_ipc_semaphore_handle_t const * const p_semaphore_handle);
fsp_err_t R_BSP_IpcNmiRequestSet(void);
fsp_err_t R_BSP_IpcNmiEnable(bsp_ipc_nmi_cb_t p_callback);

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

#endif
