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
#ifndef DET_LINKEDLIST_H
#define DET_LINKEDLIST_H

/**
*   @file Det_LinkedList.h
*
*   @addtogroup DET_MODULE
*   @{
*/
#ifdef __cplusplus
extern "C" {
#endif
/*===============================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
===============================================================================================*/
#include "Det.h"
/*===============================================================================================
*                               SOURCE FILE VERSION INFORMATION
===============================================================================================*/
#define DET_LINKEDLIST_VENDOR_ID                     43
#define DET_LINKEDLIST_AR_RELEASE_MAJOR_VERSION      4
#define DET_LINKEDLIST_AR_RELEASE_MINOR_VERSION      7
#define DET_LINKEDLIST_AR_RELEASE_REVISION_VERSION   0
#define DET_LINKEDLIST_SW_MAJOR_VERSION              5
#define DET_LINKEDLIST_SW_MINOR_VERSION              0
#define DET_LINKEDLIST_SW_PATCH_VERSION              0
/*===============================================================================================
*                                      FILE VERSION CHECKS
===============================================================================================*/
/* Check if Det_LinkedList.h and DET header file are of the same vendor */
#if (DET_LINKEDLIST_VENDOR_ID != DET_VENDOR_ID)
    #error "Det_LinkedList.h and Det.h have different vendor ids"
#endif

/* Check if Det_LinkedList.h and DET header file are of the same Autosar version */
#if ((DET_LINKEDLIST_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION) || \
     (DET_LINKEDLIST_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION) || \
     (DET_LINKEDLIST_AR_RELEASE_REVISION_VERSION != DET_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Det_LinkedList.h and Det.h are different"
#endif

/* Check if Det_LinkedList.h and DET header file are of the same Software version */
#if ((DET_LINKEDLIST_SW_MAJOR_VERSION != DET_SW_MAJOR_VERSION) || \
     (DET_LINKEDLIST_SW_MINOR_VERSION != DET_SW_MINOR_VERSION) || \
     (DET_LINKEDLIST_SW_PATCH_VERSION != DET_SW_PATCH_VERSION))
    #error "Software Version Numbers of Det_LinkedList.h and Det.h are different"
#endif
/*===============================================================================================
*                                           CONSTANTS
===============================================================================================*/

/*===============================================================================================
*                                       DEFINES AND MACROS
===============================================================================================*/
#define DET_NO_INIT_VAL     (uint8)0xFF
#define DET_NO_MODULE       (uint16)0xFFFF
#define DET_NULL            (uint16)0xFFFF
/*===============================================================================================
*                                             ENUMS
===============================================================================================*/

/*===============================================================================================
*                            STRUCTURES AND OTHER TYPEDEFS
===============================================================================================*/
/**< @brief information of linked list, point to DET buffers. */
typedef struct {
    uint16 *pModuleId;
    uint8 *pInstanceId;
    uint8 *pApiId;
    uint8 *pErrorId;
    uint32 *pNumErrors;
    uint16 *pNextIdxList;
    uint16 *pHead;
    uint16 *pTail;
    boolean *pOverflow;
}Det_LinkedListStateType;

/**< @brief Module Initialization State */
typedef enum {
    DET_UNINIT = 0U,
    DET_INIT   = 1U
}Det_ModuleStateType;
/*===============================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
===============================================================================================*/
#define DET_START_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"
/**< @brief Information about initialization of module */
extern Det_ModuleStateType Det_ModuleState[DET_NO_ECU_CORES];
#define DET_STOP_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"

#define DET_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"
/**< @brief state of linked list Det error */
extern Det_LinkedListStateType Det_aErrorState[DET_NO_ECU_CORES];
/**< @brief state of linked list Runtime Det error */
extern Det_LinkedListStateType Det_aRuntimeErrorState[DET_NO_ECU_CORES];
/**< @brief state of linked list Transient Det error */
extern Det_LinkedListStateType Det_aTransientErrorState[DET_NO_ECU_CORES];
#define DET_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Det_MemMap.h"
/*===============================================================================================
                                     FUNCTION PROTOTYPES
===============================================================================================*/
#define DET_START_SEC_CODE
#include "Det_MemMap.h"
/* @brief This function provides the service for reporting of runtime errors. */
uint16 Det_InitDataNode(uint16 ModuleId,
                        uint8 InstanceId,
                        uint8 ApiId,
                        uint8 ErrorId,
                        Det_LinkedListStateType *pDetErrorState);

/* @brief  Delete all node in the linked list that have same ModuleId, InstanceId, ApiId, ErrorId */
boolean Det_DelAllNodesSameId(uint16 ModuleId,
                          uint8 InstanceId,
                          uint8 ApiId,
                          uint8 ErrorId,
                          Det_LinkedListStateType *pDetErrorState);

/* @brief  Add node into head of Linked List */
Std_ReturnType Det_LinkNodeToHead(uint16 u16NodeToAdd, 
                                  Det_LinkedListStateType *pDetErrorState);

/* @brief   Removes data of nodes in the linked list */
void Det_FreeNodesInLinkedList(Det_LinkedListStateType *pDetErrorState);
#define DET_STOP_SEC_CODE
#include "Det_MemMap.h"
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* DET_LINKEDLIST_H */
