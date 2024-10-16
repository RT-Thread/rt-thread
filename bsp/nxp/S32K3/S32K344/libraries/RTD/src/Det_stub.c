/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   (c) Copyright 2020 - 2024 NXP
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file Det_stub.c
*
*   @addtogroup DET_MODULE
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
#include "OsIf.h"
#include "Det_stub.h"
#include "Det_LinkedList.h"
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define DET_STUB_VENDOR_ID_C                     43
#define DET_STUB_AR_RELEASE_MAJOR_VERSION_C      4
#define DET_STUB_AR_RELEASE_MINOR_VERSION_C      7
#define DET_STUB_AR_RELEASE_REVISION_VERSION_C   0
#define DET_STUB_SW_MAJOR_VERSION_C              5
#define DET_STUB_SW_MINOR_VERSION_C              0
#define DET_STUB_SW_PATCH_VERSION_C              0
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Det_stub.c and DET header file are of the same vendor */
#if (DET_STUB_VENDOR_ID_C != DET_LINKEDLIST_VENDOR_ID)
    #error "Det_stub.c and Det_LinkedList.h have different vendor ids"
#endif

/* Check if Det_stub.c and DET header file are of the same Autosar version */
#if ((DET_STUB_AR_RELEASE_MAJOR_VERSION_C != DET_LINKEDLIST_AR_RELEASE_MAJOR_VERSION) || \
     (DET_STUB_AR_RELEASE_MINOR_VERSION_C != DET_LINKEDLIST_AR_RELEASE_MINOR_VERSION) || \
     (DET_STUB_AR_RELEASE_REVISION_VERSION_C != DET_LINKEDLIST_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Det_stub.c and Det_LinkedList.h are different"
#endif

/* Check if Det_stub.c and DET header file are of the same Software version */
#if ((DET_STUB_SW_MAJOR_VERSION_C != DET_LINKEDLIST_SW_MAJOR_VERSION) || \
     (DET_STUB_SW_MINOR_VERSION_C != DET_LINKEDLIST_SW_MINOR_VERSION) || \
     (DET_STUB_SW_PATCH_VERSION_C != DET_LINKEDLIST_SW_PATCH_VERSION))
    #error "Software Version Numbers of Det_stub.c and Det_LinkedList.h are different"
#endif

/* Check if Det_stub.c and Det_stub header file are of the same vendor */
#if (DET_STUB_VENDOR_ID_C != DET_STUB_VENDOR_ID)
    #error "Det_stub.c and Det_stub.h have different vendor ids"
#endif

/* Check if Det_stub.c and Det_stub header file are of the same Autosar version */
#if ((DET_STUB_AR_RELEASE_MAJOR_VERSION_C != DET_STUB_AR_RELEASE_MAJOR_VERSION) || \
     (DET_STUB_AR_RELEASE_MINOR_VERSION_C != DET_STUB_AR_RELEASE_MINOR_VERSION) || \
     (DET_STUB_AR_RELEASE_REVISION_VERSION_C != DET_STUB_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Det_stub.c and Det_stub.h are different"
#endif

/* Check if Det_stub.c and Det_stub header file are of the same Software version */
#if ((DET_STUB_SW_MAJOR_VERSION_C != DET_STUB_SW_MAJOR_VERSION) || \
     (DET_STUB_SW_MINOR_VERSION_C != DET_STUB_SW_MINOR_VERSION) || \
     (DET_STUB_SW_PATCH_VERSION_C != DET_STUB_SW_PATCH_VERSION))
    #error "Software Version Numbers of Det_stub.c and Det_stub.h are different"
#endif


#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Det_stub.c and Mcal.h are of the same version */
    #if ((DET_STUB_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (DET_STUB_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Det_stub.c and Mcal.h are different"
    #endif
    /* Checks against OsIf.h */
    #if ((DET_STUB_AR_RELEASE_MAJOR_VERSION_C != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         (DET_STUB_AR_RELEASE_MINOR_VERSION_C != OSIF_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Det_stub.c and OsIf.h are different"
    #endif
#endif
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define DET_START_SEC_CODE
#include "Det_MemMap.h"

/*================================================================================================*/
/**
* @brief            Tests if an expected error has been reported to DET
* @details          Tests if an expected error has been reported to DET
*
* @param[in]        ModuleId - ID of the module reporting the error
* @param[in]        InstanceId - ID of the Instance reporting the error
* @param[in]        APIId - ID of the API where the error has been generated from
* @param[in]        ErrorId - Error Code

* @return           boolean - true in case expected error has been found
*
*/
boolean Det_TestLastReportError(uint16 ModuleId,
                                uint8 InstanceId,
                                uint8 ApiId,
                                uint8 ErrorId)
{
    boolean RetVal;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        /* Not found the node in linked list. because module is uninit state */
        Det_Init();
        RetVal = FALSE;
    }
    else
    {
        RetVal = Det_DelAllNodesSameId(ModuleId,
                                       InstanceId,
                                       ApiId,
                                       ErrorId,
                                       &Det_aErrorState[u32CoreId]);
    }
    OsIf_ResumeAllInterrupts();

    return RetVal;
}

/*================================================================================================*/
/**
* @brief            Tests if an expected error has been reported to DET
* @details          Tests if an expected error has been reported to DET
*
* @param[in]        ModuleId - ID of the module reporting the error
* @param[in]        InstanceId - ID of the Instance reporting the error
* @param[in]        APIId - ID of the API where the error has been generated from
* @param[in]        ErrorId - Error Code

* @return           boolean - true in case expected error has been found
*
*/
boolean Det_TestLastReportRuntimeError(uint16 ModuleId,
                                       uint8 InstanceId,
                                       uint8 ApiId,
                                       uint8 ErrorId)
{
    boolean RetVal;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        /* Not found the node in linked list. because module is uninit state */
        Det_Init();
        RetVal = FALSE;
    }
    else
    {
        RetVal = Det_DelAllNodesSameId(ModuleId,
                                       InstanceId,
                                       ApiId,
                                       ErrorId,
                                       &Det_aRuntimeErrorState[u32CoreId]);
    }
    OsIf_ResumeAllInterrupts();

    return RetVal;
}

/*================================================================================================*/
/**
* @brief            Tests if an expected error has been reported to DET
* @details          Tests if an expected error has been reported to DET,
*                   then Initialzie Det Module
*
*
* @param[in]        ModuleId - ID of the module reporting the error
* @param[in]        InstanceId - ID of the Instance reporting the error
* @param[in]        APIId - ID of the API where the error has been generated from
* @param[in]        ErrorId - Error Code

* @return           boolean - true in case expected error has been found
*
*/
boolean Det_TestLastReportTransientFault(uint16 ModuleId,
                                         uint8 InstanceId,
                                         uint8 ApiId,
                                         uint8 FaultId)
{
    boolean RetVal;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        /* Not found the node in linked list. because module is uninit state */
        Det_Init();
        RetVal = FALSE;
    }
    else
    {
        RetVal = Det_DelAllNodesSameId(ModuleId,
                                       InstanceId,
                                       ApiId,
                                       FaultId,
                                       &Det_aTransientErrorState[u32CoreId]);
    }
    OsIf_ResumeAllInterrupts();

    return RetVal;
}

/*================================================================================================*/
/**
* @brief            Tests if an error has been reported to DET
* @details          Tests if an error has been reported to DET, then Initialzie Det Module
*
* @return           boolean - true in case of NO error has been reported to DET
*
*/
boolean Det_TestNoError(void)
{
    boolean result = TRUE;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        Det_Init();
    }
    else
    {
        if (Det_numEventErrors[u32CoreId] != 0)
        {
            result = FALSE;
        }
        Det_numEventErrors[u32CoreId] = 0U;
        Det_FreeNodesInLinkedList(&Det_aErrorState[u32CoreId]);
    }
    OsIf_ResumeAllInterrupts();

    return result;
}

/*================================================================================================*/
/**
* @brief            Tests if an runtime error has been reported to DET
* @details          Tests if an runtime error has been reported to DET,
*                   then Initialzie Runtime Det Module
*
* @return           boolean - true in case of NO error has been reported to DET
*
*/
boolean Det_TestNoRuntimeError(void)
{
    boolean result = TRUE;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        Det_Init();
    }
    else
    {
        if (Det_numRuntimeEventErrors[u32CoreId] != 0)
        {
            result = FALSE;
        }
        Det_numRuntimeEventErrors[u32CoreId] = 0U;
        Det_FreeNodesInLinkedList(&Det_aRuntimeErrorState[u32CoreId]);
    }
    OsIf_ResumeAllInterrupts();

    return result;
}

/*================================================================================================*/
/**
* @brief            Tests if an transient error has been reported to DET
* @details          Tests if an transient error has been reported to DET,
*                   then Initialzie transient Det Module
*
* @return           boolean - true in case of NO error has been reported to DET
*
*/
boolean Det_TestNoTransientFault(void)
{
    boolean result = TRUE;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        Det_Init();
    }
    else
    {
        if (Det_numTransientEventErrors[u32CoreId] != 0)
        {
            result = FALSE;
        }
        Det_numTransientEventErrors[u32CoreId] = 0U;
        Det_FreeNodesInLinkedList(&Det_aTransientErrorState[u32CoreId]);
    }
    OsIf_ResumeAllInterrupts();

    return result;
}

#define DET_STOP_SEC_CODE
#include "Det_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
