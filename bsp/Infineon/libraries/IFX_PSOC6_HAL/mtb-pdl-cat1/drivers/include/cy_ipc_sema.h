/***************************************************************************//**
* \file cy_ipc_sema.h
* \version 1.80
*
* \brief
* Header file for IPC SEM functions
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CY_IPC_SEMA_H
#define CY_IPC_SEMA_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS)

#include "cy_ipc_drv.h"
#include <stdbool.h>

/**
* \addtogroup group_ipc_sema IPC semaphores layer (IPC_SEMA)
* \{
* The semaphores layer functions made use of a single IPC channel to allow
* multiple semaphores that can be used by system or user function calls.
*
* Include cy_ipc_sema.h. Alternatively include cy_pdl.h
* to get access to all functions and declarations in the PDL.
*
* By default, there are 128 semaphores provided, although the user may modify
* the default value to any number, limited only by SRAM.
*
*     \defgroup group_ipc_sema_macros Macros
*       Macro definitions are used in the driver
*
*     \defgroup group_ipc_sema_functions Functions
*       Functions are used in the driver
*
*     \defgroup group_ipc_sema_enums Enumerated Types
*       Enumerations are used in the driver
* \}
*
* \addtogroup group_ipc_sema_macros
* \{
*/

/** Software PDL driver ID for IPC semaphore functions */
#define CY_IPC_SEMA_RTN        (0x0100UL)
/** Return prefix for IPC semaphore function status codes */
#define CY_IPC_SEMA_ID_INFO    (uint32_t)( CY_IPC_ID_INFO    | CY_IPC_SEMA_RTN)
/** Return prefix for IPC semaphore function warning return values */
#define CY_IPC_SEMA_ID_WARNING (uint32_t)( CY_IPC_ID_WARNING | CY_IPC_SEMA_RTN)
/** Return prefix for IPC semaphore function error return values */
#define CY_IPC_SEMA_ID_ERROR   (uint32_t)( CY_IPC_ID_ERROR   | CY_IPC_SEMA_RTN)

#define CY_IPC_SEMA_PER_WORD    (uint32_t)32u   /**< 32 semaphores per word */

/** \} group_ipc_sema_macros */

/**
* \addtogroup group_ipc_sema_enums
* \{
*/

/** Return constants for IPC semaphores functions. */
typedef enum
{
    /** No error has occurred */
    CY_IPC_SEMA_SUCCESS            = (uint32_t)(0UL),
    /** Semaphores IPC channel has already been locked */
    CY_IPC_SEMA_ERROR_LOCKED       = (uint32_t)(CY_IPC_SEMA_ID_ERROR | 1UL),
    /** Semaphores IPC channel is unlocked */
    CY_IPC_SEMA_ERROR_UNLOCKED     = (uint32_t)(CY_IPC_SEMA_ID_ERROR | 2UL),
    /** Semaphore API bad parameter */
    CY_IPC_SEMA_BAD_PARAM          = (uint32_t)(CY_IPC_SEMA_ID_ERROR | 3UL),
    /** Semaphore API return when semaphore number is out of the range */
    CY_IPC_SEMA_OUT_OF_RANGE       = (uint32_t)(CY_IPC_SEMA_ID_ERROR | 4UL),

    /** Semaphore API return when IPC channel was not acquired */
    CY_IPC_SEMA_NOT_ACQUIRED       = (uint32_t)(CY_IPC_SEMA_ID_INFO  | 2UL),
    /** Semaphore API return status when semaphore channel is busy or locked
*                              by another process */
    CY_IPC_SEMA_LOCKED             = (uint32_t)(CY_IPC_SEMA_ID_INFO  | 3UL),
    /** Semaphore status return that the semaphore is set */
    CY_IPC_SEMA_STATUS_LOCKED      = (uint32_t)(CY_IPC_SEMA_ID_INFO  | 1UL),
    /** Semaphore status return that the semaphore is cleared */
    CY_IPC_SEMA_STATUS_UNLOCKED    = (uint32_t)(CY_IPC_SEMA_ID_INFO  | 0UL)
} cy_en_ipcsema_status_t;


/** IPC semaphore control data structure. */
typedef struct
{
    /** Maximum semaphores in system */
    uint32_t maxSema;
    /** Pointer to semaphores array  */
    uint32_t *arrayPtr;
} cy_stc_ipc_sema_t;

/** \} group_ipc_sema_enums */

/**
* \addtogroup group_ipc_sema_functions
* \{
*/

#ifdef __cplusplus
extern "C" {
#endif

cy_en_ipcsema_status_t   Cy_IPC_Sema_Init (uint32_t ipcChannel, uint32_t count, uint32_t memPtr[]);
cy_en_ipcsema_status_t   Cy_IPC_Sema_InitExt(uint32_t ipcChannel, cy_stc_ipc_sema_t *ipcSema);
cy_en_ipcsema_status_t   Cy_IPC_Sema_Set (uint32_t semaNumber, bool preemptable);
cy_en_ipcsema_status_t   Cy_IPC_Sema_Clear (uint32_t semaNumber, bool preemptable);
cy_en_ipcsema_status_t   Cy_IPC_Sema_Status (uint32_t semaNumber);
uint32_t Cy_IPC_Sema_GetMaxSems(void);

#ifdef __cplusplus
}
#endif

/** \} group_ipc_sema_functions */

#endif /* CY_IP_M4CPUSS  || CY_IP_M7CPUSS*/

#endif /* CY_IPC_SEMA_H  */

/* [] END OF FILE */
