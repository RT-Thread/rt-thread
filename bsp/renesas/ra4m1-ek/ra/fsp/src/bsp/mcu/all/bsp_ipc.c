/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#ifdef R_IPC

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* IPC0NMI is Core1 -> Core0, IPC1NMI is Core0 -> Core1 */
 #if (BSP_CFG_CPU_CORE == 0)
  #define BSP_IPC_PRV_NMI_REG_SET            IPC1NMI
  #define BSP_IPC_PRV_NMI_REG_CLEAR          IPC0NMI
 #else
  #define BSP_IPC_PRV_NMI_REG_SET            IPC0NMI
  #define BSP_IPC_PRV_NMI_REG_CLEAR          IPC1NMI
 #endif

 #define BSP_IPC_PRV_SEMAPHORE_CLEAR         1
 #define BSP_IPC_PRV_VALID_SEMAPHORE_MASK    (0xFFFFU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

static void ipc_nmi_internal_callback(bsp_grp_irq_t irq);

static bsp_ipc_nmi_cb_t gp_nmi_callback = NULL;

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Attempt to take IPC semaphore
 *
 * @param[in]  p_semaphore_handle Semaphore handle corresponding to IPCSEMn to use.
 *
 * @retval     FSP_SUCCESS                     Semaphore successfully taken
 * @retval     FSP_ERR_IN_USE                  Semaphore already taken
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  Specified semaphore doesn't exist on device
 **********************************************************************************************************************/
fsp_err_t R_BSP_IpcSemaphoreTake (bsp_ipc_semaphore_handle_t const * const p_semaphore_handle)
{
 #if BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_semaphore_handle);
    FSP_ERROR_RETURN(BSP_IPC_PRV_VALID_SEMAPHORE_MASK & (1 << p_semaphore_handle->semaphore_num),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #endif

    FSP_ERROR_RETURN(!R_IPC->IPCSEM[p_semaphore_handle->semaphore_num], FSP_ERR_IN_USE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Give/clear the IPC semaphore
 *
 * @param[in]  p_semaphore_handle Semaphore handle corresponding to IPCSEMn to use.
 *
 * @retval     FSP_SUCCESS                     Semaphore successfully given
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  Specified semaphore doesn't exist on device
 **********************************************************************************************************************/
fsp_err_t R_BSP_IpcSemaphoreGive (bsp_ipc_semaphore_handle_t const * const p_semaphore_handle)
{
 #if BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_semaphore_handle);
    FSP_ERROR_RETURN(BSP_IPC_PRV_VALID_SEMAPHORE_MASK & (1 << p_semaphore_handle->semaphore_num),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #endif

    R_IPC->IPCSEM[p_semaphore_handle->semaphore_num] = BSP_IPC_PRV_SEMAPHORE_CLEAR;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable NMI for current core
 *
 *  @param[in]  p_callback Pointer to callback to use for NMI.
 *
 * @retval     FSP_SUCCESS                  NMI request set
 **********************************************************************************************************************/
fsp_err_t R_BSP_IpcNmiEnable (bsp_ipc_nmi_cb_t p_callback)
{
 #if BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_callback);
 #endif

    gp_nmi_callback = p_callback;

    /* Setup NMI callback */
    R_BSP_GroupIrqWrite(BSP_GRP_IRQ_IPC, ipc_nmi_internal_callback);

    /* Set IPCEN bit to enable NMI. NMIER bits cannot be cleared after reset, so no need to read-modify-write. */
    R_ICU->NMIER = R_ICU_NMIER_IPCEN_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set NMI request for the opposing core
 *
 * @retval     FSP_SUCCESS                  NMI request set
 **********************************************************************************************************************/
fsp_err_t R_BSP_IpcNmiRequestSet (void)
{
    R_IPC->BSP_IPC_PRV_NMI_REG_SET.SET = 1;

    return FSP_SUCCESS;
}

/** @} (end addtogroup BSP_MCU) */

static void ipc_nmi_internal_callback (bsp_grp_irq_t irq)
{
    if (BSP_GRP_IRQ_IPC == irq)
    {
        /* Clear NMI request */
        R_IPC->BSP_IPC_PRV_NMI_REG_CLEAR.CLR = 1;

        if (NULL != gp_nmi_callback)
        {
            /* Call user callback */
            gp_nmi_callback();
        }
    }
}

#endif
