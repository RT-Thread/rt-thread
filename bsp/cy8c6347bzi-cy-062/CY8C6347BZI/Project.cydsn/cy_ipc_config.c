/***************************************************************************//**
* \file cy_ipc_config.c
* \version 1.10.1
*
*  Description:
*  This C file is not intended to be part of the IPC driver. It is the code
*  required to configure the device specific IPC channels for semaphores
*  and pipes.
*
********************************************************************************
* Copyright 2016-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ipc/cy_ipc_drv.h"
#include "ipc/cy_ipc_pipe.h"
#include "ipc/cy_ipc_sema.h"

#include "cy_ipc_config.h"

/* Create an array of endpoint structures */
static cy_stc_ipc_pipe_ep_t        cy_ipc_pipe_sysEpArray[CY_IPC_MAX_ENDPOINTS];

#define CY_CYPIPE_DEFAULT_CONFIG    \
{\
    /* .ep0ConfigData */ {\
        /* .ipcNotifierNumber    */  CY_IPC_INTR_CYPIPE_EP0,\
        /* .ipcNotifierPriority  */  CY_IPC_INTR_CYPIPE_PRIOR_EP0,\
        /* .ipcNotifierMuxNumber */  CY_IPC_INTR_CYPIPE_MUX_EP0,\
        /* .epAddress            */  CY_IPC_EP_CYPIPE_CM0_ADDR,\
        /* .epConfig             */  CY_IPC_CYPIPE_CONFIG_EP0\
    },\
    /* .ep1ConfigData */ {\
        /* .ipcNotifierNumber    */  CY_IPC_INTR_CYPIPE_EP1,\
        /* .ipcNotifierPriority  */  CY_IPC_INTR_CYPIPE_PRIOR_EP1,\
        /* .ipcNotifierMuxNumber */  0u,\
        /* .epAddress            */  CY_IPC_EP_CYPIPE_CM4_ADDR,\
        /* .epConfig             */  CY_IPC_CYPIPE_CONFIG_EP1\
    },\
    /* .endpointClientsCount     */  CY_IPC_CYPIPE_CLIENT_CNT,\
    /* .endpointsCallbacksArray  */  cy_ipc_pipe_sysCbArray,\
    /* .userPipeIsrHandler       */  &Cy_IPC_SystemPipeIsr\
}

/*******************************************************************************
* Function Name: Cy_IPC_SystemSemaInit
****************************************************************************//**
*
* Initializes the system semaphores. The system semaphores are used by Flash.
*
* This function is called in the SystemInit() function. If the default startup
* file is not used, or SystemInit() is not called in your project,
* call the following three functions prior to executing any flash or EmEEPROM
* write or erase operation:
*  -# Cy_IPC_SystemSemaInit()
*  -# Cy_IPC_SystemPipeInit()
*  -# Cy_Flash_Init()
*
*******************************************************************************/
void Cy_IPC_SystemSemaInit(void)
{
/* Create array used for semaphores */
#if !(CY_CPU_CORTEX_M0P)
    (void) Cy_IPC_Sema_Init(CY_IPC_CHAN_SEMA, 0ul, NULL);
#else
    static uint32_t ipcSemaArray[CY_IPC_SEMA_COUNT / CY_IPC_SEMA_PER_WORD];
    (void) Cy_IPC_Sema_Init(CY_IPC_CHAN_SEMA, CY_IPC_SEMA_COUNT, ipcSemaArray);
#endif
}

/*******************************************************************************
* Function Name: Cy_IPC_SystemPipeInit
****************************************************************************//**
*
* Initializes the system pipes. The system pipes are used by BLE and Flash.
* \note The function should be called on all CPUs.
*
* This function is called in the SystemInit() function. If the default startup
* file is not used, or SystemInit() is not called in your project,
* call the following three functions prior to executing any flash or EmEEPROM
* write or erase operation:
*  -# Cy_IPC_SystemSemaInit()
*  -# Cy_IPC_SystemPipeInit()
*  -# Cy_Flash_Init()
*
* Also this function is called to support BLE host/controller communication.
*
*******************************************************************************/
void Cy_IPC_SystemPipeInit(void)
{
    uint32_t intr;

    intr = Cy_SysLib_EnterCriticalSection();

    static cy_ipc_pipe_callback_ptr_t cy_ipc_pipe_sysCbArray[CY_IPC_CYPIPE_CLIENT_CNT];

    static const cy_stc_ipc_pipe_config_t systemPipeConfig = CY_CYPIPE_DEFAULT_CONFIG;

    Cy_IPC_Pipe_Config(cy_ipc_pipe_sysEpArray);

    Cy_IPC_Pipe_Init(&systemPipeConfig);

    Cy_SysLib_ExitCriticalSection(intr);
}

/*******************************************************************************
* Function Name: Cy_IPC_SystemPipeIsr
****************************************************************************//**
*
* This is the interrupt service routine for the system pipe.
*
*******************************************************************************/
void Cy_IPC_SystemPipeIsr(void)
{
    Cy_IPC_Pipe_ExecCallback(&cy_ipc_pipe_sysEpArray[CY_IPC_EP_CYPIPE_ADDR]);
}


/* [] END OF FILE */

