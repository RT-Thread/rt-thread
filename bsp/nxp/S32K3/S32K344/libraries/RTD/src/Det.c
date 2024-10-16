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
*   @file Det.c
*   @details This sample code shows how to implement det logging mechanism.
*            This file contains sample code only. It is not part of the production code deliverables.
*            Structure of buffers are created using static linked list technique to keep buffer size minimal and easy to trace and debug error event logs.
*            In production mode, users can implement a simpler mechanism for better performance or more complex solution to be compatible with debug equipment system.
*            Please follow Specification of Default Error Tracer for detail.
*
*   @addtogroup DET_MODULE
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
#include "OsIf.h"
#include "Det.h"
#include "Det_LinkedList.h"
/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/
#define DET_VENDOR_ID_C                     43
#define DET_AR_RELEASE_MAJOR_VERSION_C      4
#define DET_AR_RELEASE_MINOR_VERSION_C      7
#define DET_AR_RELEASE_REVISION_VERSION_C   0
#define DET_SW_MAJOR_VERSION_C              5
#define DET_SW_MINOR_VERSION_C              0
#define DET_SW_PATCH_VERSION_C              0
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and DET header file are of the same vendor */
#if (DET_VENDOR_ID_C != DET_VENDOR_ID)
    #error "Det.c and Det.h have different vendor ids"
#endif

/* Check if source file and DET header file are of the same Autosar version */
#if ((DET_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) || \
     (DET_AR_RELEASE_REVISION_VERSION_C != DET_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Det.c and Det.h are different"
#endif

/* Check if source file and DET header file are of the same Software version */
#if ((DET_SW_MAJOR_VERSION_C != DET_SW_MAJOR_VERSION) || \
     (DET_SW_MINOR_VERSION_C != DET_SW_MINOR_VERSION) || \
     (DET_SW_PATCH_VERSION_C != DET_SW_PATCH_VERSION))
    #error "Software Version Numbers of Det.c and Det.h are different"
#endif

/* Check if source file and DET header file are of the same vendor */
#if (DET_VENDOR_ID_C != DET_LINKEDLIST_VENDOR_ID)
    #error "Det.c and Det_LinkedList.h have different vendor ids"
#endif

/* Check if source file and DET header file are of the same Autosar version */
#if ((DET_AR_RELEASE_MAJOR_VERSION_C != DET_LINKEDLIST_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION_C != DET_LINKEDLIST_AR_RELEASE_MINOR_VERSION) || \
     (DET_AR_RELEASE_REVISION_VERSION_C != DET_LINKEDLIST_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Det.c and Det_LinkedList.h are different"
#endif

/* Check if source file and DET header file are of the same Software version */
#if ((DET_SW_MAJOR_VERSION_C != DET_LINKEDLIST_SW_MAJOR_VERSION) || \
     (DET_SW_MINOR_VERSION_C != DET_LINKEDLIST_SW_MINOR_VERSION) || \
     (DET_SW_PATCH_VERSION_C != DET_LINKEDLIST_SW_PATCH_VERSION))
    #error "Software Version Numbers of Det.c and Det_LinkedList.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Mcal.h are of the same version */
   #if ((DET_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
        (DET_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION)    \
       )
       #error "AutoSar Version Numbers of Det.c and Mcal.h are different"
   #endif
    /* Checks against OsIf.h */
    #if ((DET_AR_RELEASE_MAJOR_VERSION_C != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         (DET_AR_RELEASE_MINOR_VERSION_C != OSIF_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Det.c and OsIf.h are different"
    #endif
#endif
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define DET_START_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Det_MemMap.h"
/* Variables to store last DET error */
uint8 Det_InstanceId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];               /**< @brief DET instance ID*/
uint8 Det_ApiId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];                    /**< @brief DET API ID*/
uint8 Det_ErrorId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];                  /**< @brief DET Error ID*/
/* Variables to store last DET runtime error */
uint8 Det_RuntimeInstanceId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];        /**< @brief DET Runtime instance ID*/
uint8 Det_RuntimeApiId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];             /**< @brief DET Runtime API ID*/
uint8 Det_RuntimeErrorId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];           /**< @brief DET Runtime Error ID*/
/* Variables to store last DET transient error */
uint8 Det_TransientInstanceId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];      /**< @brief DET Transient instance ID*/
uint8 Det_TransientApiId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];           /**< @brief DET Transient API ID*/
uint8 Det_TransientFaultId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];         /**< @brief DET Transient Error ID*/
#define DET_STOP_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_CLEARED_16_NO_CACHEABLE
#include "Det_MemMap.h"
uint16 Det_TransientModuleId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];       /**< @brief DET Transient module ID*/
uint16 Det_ModuleId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];                /**< @brief DET module ID*/
uint16 Det_RuntimeModuleId[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];         /**< @brief DET Runtime module ID*/
#define DET_STOP_SEC_VAR_CLEARED_16_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_CLEARED_32_NO_CACHEABLE
#include "Det_MemMap.h"
uint32 Det_numEventErrors[DET_NO_ECU_CORES];               /**< @brief number of DET error ID*/
uint32 Det_numRuntimeEventErrors[DET_NO_ECU_CORES];        /**< @brief number of runtime DET error ID*/
uint32 Det_numTransientEventErrors[DET_NO_ECU_CORES];      /**< @brief number of transient DET error ID*/
#define DET_STOP_SEC_VAR_CLEARED_32_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_CLEARED_16_NO_CACHEABLE
#include "Det_MemMap.h"
/**< @brief Next Index List of Det Error */
uint16 Det_NextIdxList[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];
/**< @brief Head Index of Static Linked List */
uint16 Det_Head[DET_NO_ECU_CORES];
/**< @brief Tail Index of Statuc Linked List */
uint16 Det_Tail[DET_NO_ECU_CORES];

/**< @brief Next Index List of Det Trasient Error */
uint16 Det_Transient_NextIdxList[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];
/**< @brief Head Index of Static Linked List (Det Trasient Error) */
uint16 Det_Transient_Head[DET_NO_ECU_CORES];
/**< @brief Tail Index of Static Linked List (Det Trasient Error) */
uint16 Det_Transient_Tail[DET_NO_ECU_CORES];

/**< @brief Next Index of Det Runtime Error */
uint16 Det_Runtime_NextIdxList[DET_NO_ECU_CORES][DET_MAX_NUMBER_OF_EVENTS];
/**< @brief Head Index of Static Linked (List Det Runtime Error) */
uint16 Det_Runtime_Head[DET_NO_ECU_CORES];
/**< @brief Tail pointer of Static Linked List (Det Runtime Error) */
uint16 Det_Runtime_Tail[DET_NO_ECU_CORES];
#define DET_STOP_SEC_VAR_CLEARED_16_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"
/**< @brief state of linked list Det error */
Det_LinkedListStateType Det_aErrorState[DET_NO_ECU_CORES];
/**< @brief state of linked list Runtime Det error */
Det_LinkedListStateType Det_aRuntimeErrorState[DET_NO_ECU_CORES];
/**< @brief state of linked list Transient Det error */
Det_LinkedListStateType Det_aTransientErrorState[DET_NO_ECU_CORES];
#define DET_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"
/**< @brief Information about initialization of module */
Det_ModuleStateType Det_ModuleState[DET_NO_ECU_CORES] = {DET_UNINIT};
#define DET_STOP_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_INIT_BOOLEAN_NO_CACHEABLE
#include "Det_MemMap.h"
/**< @brief Overflow flag of DET error */
boolean Det_OverflowErrorFlag[DET_NO_ECU_CORES] = {FALSE};
/**< @brief Overflow flag of Runtime DET error */
boolean Det_OverflowRuntimeErrorFlag[DET_NO_ECU_CORES] = {FALSE};
/**< @brief Overflow flag of Transient DET error */
boolean Det_OverflowTransientErrorFlag[DET_NO_ECU_CORES] = {FALSE};
#define DET_STOP_SEC_VAR_INIT_BOOLEAN_NO_CACHEABLE
#include "Det_MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define DET_START_SEC_CODE
#include "Det_MemMap.h"
/* @brief   Delete node after seach in Normal Linked List */
LOCAL_INLINE void Det_UnlinkNode(uint16 u16NodeToDel,
                                 Det_LinkedListStateType *pDetErrorState);
/* @brief   Initialize the linked list */
LOCAL_INLINE void Det_InitLinkedList(void);
#define DET_STOP_SEC_CODE
#include "Det_MemMap.h"
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
* @brief          This function initializes the DET module.
* @details        This is a function stub only. Functionality is void in this implementation.
*/
void Det_Init(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    Det_InitLinkedList();

    Det_FreeNodesInLinkedList(&Det_aErrorState[u32CoreId]);
    Det_FreeNodesInLinkedList(&Det_aRuntimeErrorState[u32CoreId]);
    Det_FreeNodesInLinkedList(&Det_aTransientErrorState[u32CoreId]);
}

/*================================================================================================*/
/**
* @brief   This function provides the service for reporting of development errors.
* @details This is a function stub only. It only loads the global IDs with the IDs of the latest error that occured
*
* @param[in]     ModuleId    Module ID of Calling Module
* @param[in]     InstanceId  Index of Module starting at 0
* @param[in]     ApiId       ID of API with Error
* @param[in]     ErrorId     ID of Error
*
* @return        Std_ReturnType - E_OK: Reporting error success - E_NOT_OK: Reporting error fail
*/
Std_ReturnType Det_ReportError(uint16 ModuleId,
                               uint8 InstanceId,
                               uint8 ApiId,
                               uint8 ErrorId)
{
    uint16 u16NodeToAdd;
    Std_ReturnType RetVal;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        Det_Init();
    }
    u16NodeToAdd = Det_InitDataNode(ModuleId,
                                    InstanceId,
                                    ApiId,
                                    ErrorId,
                                    &Det_aErrorState[u32CoreId]);

    if (u16NodeToAdd != DET_NULL)
    {
        RetVal = Det_LinkNodeToHead(u16NodeToAdd, &Det_aErrorState[u32CoreId]);
    }
    else
    {
        /* Can not add more node because of full linked list */
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    OsIf_ResumeAllInterrupts();

    return RetVal;
}

/*================================================================================================*/
/**
* @brief   This function provides the service for reporting of runtime errors.
* @details This is a function stub only. It only loads the global IDs with the IDs of the latest error that occured
*
* @param[in]     ModuleId    Module ID of Calling Module
* @param[in]     InstanceId  Index of Module starting at 0
* @param[in]     ApiId       ID of API with Error
* @param[in]     ErrorId     ID of Error
*
* @return        Std_ReturnType - E_OK: Reporting error success - E_NOT_OK: Reporting error fail
*/
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId,
                                      uint8 InstanceId,
                                      uint8 ApiId,
                                      uint8 ErrorId)
{
    uint16 u16NodeToAdd;
    Std_ReturnType RetVal;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        Det_Init();
    }
    u16NodeToAdd = Det_InitDataNode(ModuleId,
                                    InstanceId,
                                    ApiId,
                                    ErrorId,
                                    &Det_aRuntimeErrorState[u32CoreId]);

    if (u16NodeToAdd != DET_NULL)
    {
        RetVal = Det_LinkNodeToHead(u16NodeToAdd, &Det_aRuntimeErrorState[u32CoreId]);
    }
    else
    {
        /* Can not add more node because of full linked list */
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    OsIf_ResumeAllInterrupts();

    return RetVal;
}

/*================================================================================================*/
/**
* @brief   This function provides the service for reporting of transient errors.
* @details This is a function stub only. It only loads the global IDs with the IDs of the latest error that occured
*
* @param[in]     ModuleId    Module ID of Calling Module
* @param[in]     InstanceId  Index of Module starting at 0
* @param[in]     ApiId       ID of API with Error
* @param[in]     FaultId     ID of Fault
*
* @return        Std_ReturnType - E_OK: Reporting error success - E_NOT_OK: Reporting error fail
*/
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId,
                                        uint8 InstanceId,
                                        uint8 ApiId,
                                        uint8 FaultId)
{
    uint16 u16NodeToAdd;
    Std_ReturnType RetVal;
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    OsIf_SuspendAllInterrupts();
    if (DET_UNINIT == Det_ModuleState[u32CoreId])
    {
        Det_Init();
    }
    u16NodeToAdd = Det_InitDataNode(ModuleId,
                                    InstanceId,
                                    ApiId,
                                    FaultId,
                                    &Det_aTransientErrorState[u32CoreId]);

    if (u16NodeToAdd != DET_NULL)
    {
        RetVal = Det_LinkNodeToHead(u16NodeToAdd, &Det_aTransientErrorState[u32CoreId]);
    }
    else
    {
        /* Can not add more node because of full linked list */
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    OsIf_ResumeAllInterrupts();

    return RetVal;
}

/*================================================================================================*/
/**
* @brief   This function provides the starting after the Det_Init has been called.
* @details This is a function stub only.  Det_Init and Det_Start shall always be available.
*          Functionality is void in this implementation
*
*/
void Det_Start(void)
{
    /* Do nothing */
}

/**
* @brief   Initialize data of node in Det Array.
* @details Initialize data of node in Det Array.
*
* @param[in]     ModuleId    Module ID of Calling Module
* @param[in]     InstanceId  Index of Module starting at 0
* @param[in]     ApiId       ID of API with Error
* @param[in]     FaultId     ID of Fault
*
* @return        uint16      Index of the return node in Det Array
*/
uint16 Det_InitDataNode(uint16 ModuleId,
                        uint8 InstanceId,
                        uint8 ApiId,
                        uint8 ErrorId,
                        Det_LinkedListStateType *pDetErrorState)
{
    uint16 u16Count;
    uint16 u16RetNode  = DET_NULL;
    uint32 *pNumError  = pDetErrorState->pNumErrors;
    uint16 *pModuleId  = pDetErrorState->pModuleId;
    uint8 *pInstanceId = pDetErrorState->pInstanceId;
    uint8 *pApiId      = pDetErrorState->pApiId;
    uint8 *pErrorId    = pDetErrorState->pErrorId;

    if (*pNumError < DET_MAX_NUMBER_OF_EVENTS)
    {
        for (u16Count = (uint16)0; u16Count < DET_MAX_NUMBER_OF_EVENTS; u16Count++)
        {
            if (
                (DET_NO_MODULE   == pModuleId[u16Count]) &&
                (DET_NO_INIT_VAL == pInstanceId[u16Count]) &&
                (DET_NO_INIT_VAL == pApiId[u16Count]) &&
                (DET_NO_INIT_VAL == pErrorId[u16Count])
               )
            {
                pModuleId[u16Count]   = ModuleId;
                pInstanceId[u16Count] = InstanceId;
                pApiId[u16Count]      = ApiId;
                pErrorId[u16Count]    = ErrorId;
                u16RetNode = u16Count;
                break;
            }
        }
    }
    else
    {
        /* the DET error array is full, need to return invalid value */
        *(pDetErrorState->pOverflow) = TRUE;
    }

    return u16RetNode;
}

/**
* @brief   Add node into head of Normal Linked List.
* @details Add node into head of Normal Linked List.
*
* @param[in]     u16NodeToAdd    index of node need to be added in the linked list
* @param[in]     pDetErrorState  pointer of linked list state
*
* @return        Std_ReturnType - E_OK: Linking node success - E_NOT_OK: Linking node fail
*/
Std_ReturnType Det_LinkNodeToHead(uint16 u16NodeToAdd, Det_LinkedListStateType *pDetErrorState)
{
    Std_ReturnType RetVal = (Std_ReturnType)E_OK;
    uint16 *pNextIdxAtNodeToAdd = &((pDetErrorState->pNextIdxList)[u16NodeToAdd]);
    uint16 *pHead = pDetErrorState->pHead;
    uint16 *pTail = pDetErrorState->pTail;
    uint32 *pNumError = pDetErrorState->pNumErrors;

    if (*pNextIdxAtNodeToAdd == DET_NULL)
    {
        /* if the node to add is the first node of linked list, 
           next index of the node will be NULL value */
        *pNextIdxAtNodeToAdd = *pHead;
        /* The tail is always assigned to the first node of the linked list */
        /* The head is always change when pushing node into the linked list */
        /* It's convenient for finding the lastest node in the linked list */
        *pHead = u16NodeToAdd;
        if (0U == *pNumError)
        {
            *pTail = u16NodeToAdd;
        }
        (*pNumError)++;
    }
    else
    {
        RetVal = (Std_ReturnType)E_NOT_OK;
    }

    return RetVal;
}

/**
* @brief   Delete all node in the linked list that have same ModuleId, InstanceId, ApiId, ErrorId
* @details Delete all node in the linked list that have same ModuleId, InstanceId, ApiId, ErrorId
*
* @param[in]     ModuleId    Module ID of Calling Module
* @param[in]     InstanceId  Index of Module starting at 0
* @param[in]     ApiId       ID of API with Error
* @param[in]     FaultId     ID of Fault
* @param[in]     pDetErrorState  pointer of linked list state
*
* @return        boolean - TRUE: Deleting node success - FALSE: not found node to delete
*/
boolean Det_DelAllNodesSameId(uint16 ModuleId,
                              uint8 InstanceId,
                              uint8 ApiId,
                              uint8 ErrorId,
                              Det_LinkedListStateType *pDetErrorState)
{
    uint16 u16Count;
    uint16 u16TempNodeIdx;
    boolean RetVal = FALSE;
    uint32 *pNumError  = pDetErrorState->pNumErrors;
    uint16 *pModuleId  = pDetErrorState->pModuleId;
    uint8 *pInstanceId = pDetErrorState->pInstanceId;
    uint8 *pApiId      = pDetErrorState->pApiId;
    uint8 *pErrorId    = pDetErrorState->pErrorId;
    if (*pNumError != 0U)
    {
        u16Count = *(pDetErrorState->pHead);
        do
        {
            if (
                (ModuleId   == pModuleId[u16Count]) &&
                (InstanceId == pInstanceId[u16Count]) &&
                (ApiId      == pApiId[u16Count]) &&
                (ErrorId    == pErrorId[u16Count])
               )
            {
                /* Store next of the node to delete */
                /* The purpose is to continue scanning the linked list after deleting the node*/
                u16TempNodeIdx = pDetErrorState->pNextIdxList[u16Count];
                Det_UnlinkNode(u16Count, pDetErrorState);
                u16Count = u16TempNodeIdx;
                RetVal = TRUE;
            }
            else
            {
                u16Count = pDetErrorState->pNextIdxList[u16Count];
            }

        }
        while (u16Count != DET_NULL);
    }
    else
    {
        /* Not found the node because of empty linked list. Need to return invalid index */
        /* Do Nothing because RetVal is default asigned to FALSE */
    }

    return RetVal;
}
/*
 * @brief   Delete node after seach in Normal Linked List
*/
LOCAL_INLINE void Det_UnlinkNode(uint16 u16NodeToDel,
                                 Det_LinkedListStateType *pDetErrorState)
{
    uint32 *pNumError  = pDetErrorState->pNumErrors;
    uint16 *pModuleId  = pDetErrorState->pModuleId;
    uint8 *pInstanceId = pDetErrorState->pInstanceId;
    uint8 *pApiId      = pDetErrorState->pApiId;
    uint8 *pErrorId    = pDetErrorState->pErrorId;
    uint16 *pHead      = pDetErrorState->pHead;
    uint16 *pTail      = pDetErrorState->pTail;
    uint16 u16Count    = *pHead;
    uint16 *pNextIdx   = pDetErrorState->pNextIdxList;

    /* Delete the link of the node to delete */
    if (u16NodeToDel == *pHead)
    {
        *pHead = pNextIdx[u16NodeToDel];
        pNextIdx[u16NodeToDel] = DET_NULL;
    }
    else if (u16NodeToDel == *pTail)
    {
        while(pNextIdx[u16Count] != *pTail)
        {
            u16Count = pNextIdx[u16Count];
        };
        pNextIdx[u16Count] = DET_NULL;
        *pTail = u16Count;
    }
    else
    {
        while (pNextIdx[u16Count] != u16NodeToDel)
        {
            u16Count = pNextIdx[u16Count];
        }
        pNextIdx[u16Count] = pNextIdx[u16NodeToDel];
        pNextIdx[u16NodeToDel] = DET_NULL;
    }
    (*pNumError)--;
    /* Reset Head, Tail if the linked list is empty */
    if (0U == *pNumError)
    {
        *pHead = DET_NULL;
        *pTail = DET_NULL;
    }
    /* Delete data of the note to delete */
    pModuleId[u16NodeToDel]   = DET_NO_MODULE;
    pInstanceId[u16NodeToDel] = DET_NO_INIT_VAL;
    pApiId[u16NodeToDel]      = DET_NO_INIT_VAL;
    pErrorId[u16NodeToDel]    = DET_NO_INIT_VAL;
}

/**
* @brief   Free all nodes in the linked list
* @details Free all nodes in the linked list
*
* @param[in]     pDetErrorState  pointer of linked list state
*
*/
void Det_FreeNodesInLinkedList(Det_LinkedListStateType *pDetErrorState)
{
    uint16 u16Count;
    uint16 *pModuleId  = pDetErrorState->pModuleId;
    uint8 *pInstanceId = pDetErrorState->pInstanceId;
    uint8 *pApiId      = pDetErrorState->pApiId;
    uint8 *pErrorId    = pDetErrorState->pErrorId;
    uint16 *pNextIdx   = pDetErrorState->pNextIdxList;
    uint16 *pHead      = pDetErrorState->pHead;
    uint16 *pTail      = pDetErrorState->pTail;

    for (u16Count = 0; u16Count < DET_MAX_NUMBER_OF_EVENTS; u16Count++)
    {
        pNextIdx[u16Count]    = DET_NULL;
        pModuleId[u16Count]   = DET_NO_MODULE;
        pInstanceId[u16Count] = DET_NO_INIT_VAL;
        pApiId[u16Count]      = DET_NO_INIT_VAL;
        pErrorId[u16Count]    = DET_NO_INIT_VAL;
    }
    *pHead = DET_NO_MODULE;
    *pTail = DET_NO_MODULE;
    *(pDetErrorState->pOverflow) = FALSE;
}

/*
* @brief   Initialize the linked list
*/ 
LOCAL_INLINE void Det_InitLinkedList(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    Det_numEventErrors[u32CoreId]          = 0U;
    Det_numRuntimeEventErrors[u32CoreId]   = 0U;
    Det_numTransientEventErrors[u32CoreId] = 0U;

    Det_OverflowErrorFlag[u32CoreId]          = FALSE;
    Det_OverflowRuntimeErrorFlag[u32CoreId]   = FALSE;
    Det_OverflowTransientErrorFlag[u32CoreId] = FALSE;

    Det_aErrorState[u32CoreId].pModuleId    = Det_ModuleId[u32CoreId];
    Det_aErrorState[u32CoreId].pInstanceId  = Det_InstanceId[u32CoreId];
    Det_aErrorState[u32CoreId].pApiId       = Det_ApiId[u32CoreId];
    Det_aErrorState[u32CoreId].pErrorId     = Det_ErrorId[u32CoreId];
    Det_aErrorState[u32CoreId].pNumErrors   = &Det_numEventErrors[u32CoreId];
    Det_aErrorState[u32CoreId].pNextIdxList = Det_NextIdxList[u32CoreId];
    Det_aErrorState[u32CoreId].pHead        = &Det_Head[u32CoreId];
    Det_aErrorState[u32CoreId].pTail        = &Det_Tail[u32CoreId];
    Det_aErrorState[u32CoreId].pOverflow    = &Det_OverflowErrorFlag[u32CoreId];

    Det_aRuntimeErrorState[u32CoreId].pModuleId    = Det_RuntimeModuleId[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pInstanceId  = Det_RuntimeInstanceId[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pApiId       = Det_RuntimeApiId[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pErrorId     = Det_RuntimeErrorId[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pNumErrors   = &Det_numRuntimeEventErrors[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pNextIdxList = Det_Runtime_NextIdxList[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pHead        = &Det_Runtime_Head[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pTail        = &Det_Runtime_Tail[u32CoreId];
    Det_aRuntimeErrorState[u32CoreId].pOverflow    = &Det_OverflowRuntimeErrorFlag[u32CoreId];

    Det_aTransientErrorState[u32CoreId].pModuleId    = Det_TransientModuleId[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pInstanceId  = Det_TransientInstanceId[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pApiId       = Det_TransientApiId[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pErrorId     = Det_TransientFaultId[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pNumErrors   = &Det_numTransientEventErrors[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pNextIdxList = Det_Transient_NextIdxList[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pHead        = &Det_Transient_Head[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pTail        = &Det_Transient_Tail[u32CoreId];
    Det_aTransientErrorState[u32CoreId].pOverflow    = &Det_OverflowTransientErrorFlag[u32CoreId];

    Det_ModuleState[u32CoreId] = DET_INIT;
}
#define DET_STOP_SEC_CODE
#include "Det_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
