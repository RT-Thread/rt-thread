/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
#ifndef OSIF_INTERNAL_H
#define OSIF_INTERNAL_H

/**
*   @file
*   @implements OsIf_Internal.h_Artifact
*   @addtogroup osif_drv
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Soc_Ips.h"
#include "OsIf_Cfg.h"

#if defined(USING_OS_AUTOSAROS)
#include "Os.h"
#endif /* defined(USING_OS_AUTOSAROS) */

#if defined(USING_OS_ZEPHYR)
#include "OsIf_Interrupts.h"
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
/* System calls for RTD */
#include "rtd.h"
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
#endif /* defined(USING_OS_ZEPHYR) */

#if defined(USING_OS_FREERTOS)
#include "OsIf_Interrupts.h"
#include "FreeRTOS.h"
#include "task.h"
#endif /* defined(USING_OS_FREERTOS) */

#if !defined(USING_OS_AUTOSAROS)
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
#if (MCAL_PLATFORM_ARM  == MCAL_ARM_MARCH)
/* prototypes defined in system.h*/
uint32 Sys_GoToUser_Return(uint32 u32SwitchToSupervisor, uint32 u32returnValue);
uint32 Sys_GoToSupervisor(void);
uint32 Sys_GoToUser(void);
#else
/* import inline function for switch context from system.h */
#include "system.h"
#endif /*  (MCAL_PLATFORM_ARM  == MCAL_ARM_MARCH) */
void Sys_SuspendInterrupts(void);
void Sys_ResumeInterrupts(void);
#endif /* def MCAL_ENABLE_USER_MODE_SUPPORT */
uint8 Sys_GetCoreID(void);
#endif /* !defined(USING_OS_AUTOSAROS) */

#if defined(USING_COHORT_DOMAIN_ID)
#if (USING_COHORT_DOMAIN_ID == STD_ON)
uint8 Sys_GetCohortID(void);
uint8 Sys_GetDomainID(void);
uint8 Sys_GetAID(void);
#endif
#endif /* defined(USING_COHORT_DOMAIN_ID) */

#if (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH32) || (MCAL_PLATFORM_ARM  == MCAL_ARM_RARCH) 
void Sys_EL1SuspendInterrupts(void);
void Sys_EL1ResumeInterrupts(void);
#endif

#ifdef USING_GET_CUSTOM_ID
uint8 OsIf_GetCustomID(void);
#endif
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_INTERNAL_VENDOR_ID                    43
#define OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION     7
#define OSIF_INTERNAL_AR_RELEASE_REVISION_VERSION  0
#define OSIF_INTERNAL_SW_MAJOR_VERSION             5
#define OSIF_INTERNAL_SW_MINOR_VERSION             0
#define OSIF_INTERNAL_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Internal.h file and OsIf_Cfg.h file are of the same vendor */
#if (OSIF_INTERNAL_VENDOR_ID != OSIF_CFG_VENDOR_ID)
    #error "OsIf_Internal.h and OsIf_Cfg.h have different vendor ids"
#endif
/* Check if OsIf_Internal.h file and OsIf_Cfg.h file are of the same Autosar version */
#if ((OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION    != OSIF_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION    != OSIF_CFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_INTERNAL_AR_RELEASE_REVISION_VERSION != OSIF_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Internal.h and OsIf_Cfg.h are different"
#endif
/* Check if OsIf_Internal.h file and OsIf_Cfg.h file are of the same Software version */
#if ((OSIF_INTERNAL_SW_MAJOR_VERSION != OSIF_CFG_SW_MAJOR_VERSION) || \
     (OSIF_INTERNAL_SW_MINOR_VERSION != OSIF_CFG_SW_MINOR_VERSION) || \
     (OSIF_INTERNAL_SW_PATCH_VERSION != OSIF_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Internal.h and OsIf_Cfg.h are different"
#endif

/* Check if OsIf_Internal.h file and Std_Types.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Internal.h and Std_Types.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/* Check if OsIf_Internal.h file and Soc_Ips.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Internal.h and Soc_Ips.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

#if defined(USING_OS_AUTOSAROS)
/* Check if OsIf_Internal.h file and Os.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION != OS_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION != OS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Internal.h and Os.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* defined(USING_OS_AUTOSAROS) */

#if defined(USING_OS_ZEPHYR)
/* Check if OsIf_Internal.h file and OsIf_Interrupts.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION != OSIF_INTERRUPTS_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION != OSIF_INTERRUPTS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Internal.h and OsIf_Interrupts.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* defined(USING_OS_AUTOSAROS) */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*
 * OsIf_Trusted_Call*
 */
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
#if (defined(USING_OS_AUTOSAROS) || defined(USING_OS_ZEPHYR))
#define OsIf_Trusted_Call(name)                                                  Call_##name##_TRUSTED()
#define OsIf_Trusted_Call1param(name,param)                                      Call_##name##_TRUSTED(param)
#define OsIf_Trusted_Call2params(name,param1,param2)                             Call_##name##_TRUSTED(param1,param2)
#define OsIf_Trusted_Call3params(name,param1,param2,param3)                      Call_##name##_TRUSTED(param1,param2,param3)
#define OsIf_Trusted_Call4params(name,param1,param2,param3,param4)               Call_##name##_TRUSTED(param1,param2,param3,param4)
#define OsIf_Trusted_Call5params(name,param1,param2,param3,param4,param5)        Call_##name##_TRUSTED(param1,param2,param3,param4,param5)
#define OsIf_Trusted_Call6params(name,param1,param2,param3,param4,param5,param6) Call_##name##_TRUSTED(param1,param2,param3,param4,param5,param6)

#define OsIf_Trusted_Call_Return(name)                                                 Call_##name##_TRUSTED()
#define OsIf_Trusted_Call_Return1param(name,param1)                                    Call_##name##_TRUSTED(param1)
#define OsIf_Trusted_Call_Return2param(name,param1,param2)                             Call_##name##_TRUSTED(param1,param2)
#define OsIf_Trusted_Call_Return3param(name,param1,param2,param3)                      Call_##name##_TRUSTED(param1,param2,param3)
#define OsIf_Trusted_Call_Return4param(name,param1,param2,param3,param4)               Call_##name##_TRUSTED(param1,param2,param3,param4)
#define OsIf_Trusted_Call_Return5param(name,param1,param2,param3,param4,param5)        Call_##name##_TRUSTED(param1,param2,param3,param4,param5)
#define OsIf_Trusted_Call_Return6param(name,param1,param2,param3,param4,param5,param6) Call_##name##_TRUSTED(param1,param2,param3,param4,param5,param6)

#else /* USING_OS_AUTOSAROS */
/* Baremetal and FreeRTOS */
#define OsIf_Trusted_Call(name)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(), (void)Sys_GoToUser()) : (name(),(void)0U))
#define OsIf_Trusted_Call1param(name,param)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(param), (void)Sys_GoToUser()) : (name(param),(void)0U))
#define OsIf_Trusted_Call2params(name,param1,param2)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(param1,param2), (void)Sys_GoToUser()) : (name(param1,param2),(void)0U))
#define OsIf_Trusted_Call3params(name,param1,param2,param3)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(param1,param2,param3), (void)Sys_GoToUser()) : (name(param1,param2,param3),(void)0U))
#define OsIf_Trusted_Call4params(name,param1,param2,param3,param4)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(param1,param2,param3,param4), (void)Sys_GoToUser()) : (name(param1,param2,param3,param4),(void)0U))
#define OsIf_Trusted_Call5params(name,param1,param2,param3,param4,param5)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(param1,param2,param3,param4,param5), (void)Sys_GoToUser()) : (name(param1,param2,param3,param4,param5),(void)0U))
#define OsIf_Trusted_Call6params(name,param1,param2,param3,param4,param5,param6)  \
    ((1UL == Sys_GoToSupervisor()) ? (name(param1,param2,param3,param4,param5,param6), (void)Sys_GoToUser()) : (name(param1,param2,param3,param4,param5,param6),(void)0U))

#define OsIf_Trusted_Call_Return(name)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name()) :  Sys_GoToUser_Return(0U, name()))
#define OsIf_Trusted_Call_Return1param(name,param)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name(param)) :  Sys_GoToUser_Return(0U, name(param)))
#define OsIf_Trusted_Call_Return2param(name,param1,param2)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name(param1,param2)) : Sys_GoToUser_Return(0U, name(param1,param2)))
#define OsIf_Trusted_Call_Return3param(name,param1,param2,param3)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name(param1,param2,param3)) :  Sys_GoToUser_Return(0U, name(param1,param2,param3)))
#define OsIf_Trusted_Call_Return4param(name,param1,param2,param3,param4)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name(param1,param2,param3,param4)) :  Sys_GoToUser_Return(0U, name(param1,param2,param3,param4)))
#define OsIf_Trusted_Call_Return5param(name,param1,param2,param3,param4,param5)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name(param1,param2,param3,param4,param5)) :  Sys_GoToUser_Return(0U, name(param1,param2,param3,param4,param5)))
#define OsIf_Trusted_Call_Return6param(name,param1,param2,param3,param4,param5,param6)  \
    ((1UL == Sys_GoToSupervisor()) ?  Sys_GoToUser_Return(1U, name(param1,param2,param3,param4,param5,param6)) :  Sys_GoToUser_Return(0U, name(param1,param2,param3,param4,param5,param6)))
#endif /* USING_OS_AUTOSAROS */
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */

/*
 * OsIf_GetCoreID
 */
#ifdef USING_OS_AUTOSAROS
        #define OsIf_GetCoreID()    GetCoreID()
#else /* USING_OS_AUTOSAROS */
    /* Baremetal and FreeRTOS and ZephyrOS */
    #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        #define OsIf_GetCoreID()    OsIf_Trusted_Call_Return(Sys_GetCoreID)
    #else
        /* @implements OsIf_GetCoreID_define */
        #define OsIf_GetCoreID()    Sys_GetCoreID()
    #endif
#endif

#ifdef USING_GET_PARTITION_ID
/*
 * OsIf_GetOsAppId
 */
/* USING_OS_AUTOSAROS */
    #ifdef USING_OS_AUTOSAROS
        #define OsIf_GetUserId()       (OsIf_apxMultiPartitionPredefinedConfig[GetApplicationID()])
    #else
        #define OsIf_GetUserId()       OsIf_GetCoreID()
    #endif
#else
    #ifdef USING_GET_CORE_ID
        #define OsIf_GetUserId()   OsIf_GetCoreID()
    #else
        #define OsIf_GetUserId()   OsIf_GetCustomID()
    #endif
#endif

/*
 * OsIf_SuspendAllInterrupts
 * OsIf_ResumeAllInterrupts
 */
#if (!defined(USING_OS_AUTOSAROS) && !defined(USING_OS_ZEPHYR))
    #ifndef MCAL_ENABLE_USER_MODE_SUPPORT   /*Bare metal not enable user mode*/
        /* Baremetal or FreeRTOS case */
        #if (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH64)
            #define ResumeAllInterrupts()   ASM_KEYWORD(" msr DAIFClr,#0x3")
            #define SuspendAllInterrupts()  ASM_KEYWORD(" msr DAIFSet,#0x3")
        #elif (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH32) || (MCAL_PLATFORM_ARM  == MCAL_ARM_RARCH) 
            #define ResumeAllInterrupts()   Sys_EL1ResumeInterrupts()
            #define SuspendAllInterrupts()  Sys_EL1SuspendInterrupts()
        #elif (MCAL_PLATFORM_ARM  == MCAL_ARM_MARCH)
            #if defined(USING_OS_FREERTOS)
                #define ResumeAllInterrupts()   OsIf_Interrupts_ResumeAllInterrupts()
                #define SuspendAllInterrupts()  OsIf_Interrupts_SuspendAllInterrupts()
            #else
                #define ResumeAllInterrupts()   ASM_KEYWORD(" cpsie i")
                #define SuspendAllInterrupts()  ASM_KEYWORD(" cpsid i")
            #endif /* defined(USING_OS_FREERTOS) */

         #endif /* MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH64 */
    #else  
        #if (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH32) || (MCAL_PLATFORM_ARM  == MCAL_ARM_RARCH) 
            #define ResumeAllInterrupts()  OsIf_Trusted_Call(Sys_EL1ResumeInterrupts)
            #define SuspendAllInterrupts() OsIf_Trusted_Call(Sys_EL1SuspendInterrupts)
        #else
            #define ResumeAllInterrupts()   Sys_ResumeInterrupts()
            #define SuspendAllInterrupts()  Sys_SuspendInterrupts()
        #endif  
    #endif /*MCAL_ENABLE_USER_MODE_SUPPORT */
#elif defined(USING_OS_ZEPHYR)
    #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        #define ResumeAllInterrupts()   OsIf_Trusted_Call(OsIf_Interrupts_ResumeAllInterrupts)
        #define SuspendAllInterrupts()  OsIf_Trusted_Call(OsIf_Interrupts_SuspendAllInterrupts)
    #else
        #define ResumeAllInterrupts()   OsIf_Interrupts_ResumeAllInterrupts()
        #define SuspendAllInterrupts()  OsIf_Interrupts_SuspendAllInterrupts()
    #endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
#endif /* !defined(USING_OS_AUTOSAROS) && !defined(USING_OS_ZEPHYR) */

/* @implements OsIf_SuspendAllInterrupts_define */
#define OsIf_SuspendAllInterrupts()     SuspendAllInterrupts()
/* @implements OsIf_ResumeAllInterrupts_define */
#define OsIf_ResumeAllInterrupts()      ResumeAllInterrupts()

/*
 * ISR macro definition
 */
#ifdef USING_OS_AUTOSAROS
/* ISR() macro defined by Autosar OS*/
#else
/* Baremetal or FreeRTOS case */
#if defined (USE_SW_VECTOR_MODE)
    #define ISR(IsrName)       void IsrName(void)
#else
    #define ISR(IsrName)       INTERRUPT_FUNC void IsrName(void)
#endif /* defined (USE_SW_VECTOR_MODE) */
#endif /* USING_OS_AUTOSAROS */

#if defined(USING_COHORT_DOMAIN_ID)
#if (USING_COHORT_DOMAIN_ID == STD_ON)
    #define OsIf_GetCohortID()  Sys_GetCohortID()
    #define OsIf_GetDomainID()  Sys_GetDomainID()
    #define OsIf_GetAID()       Sys_GetAID()
#endif
#endif /* defined(USING_COHORT_DOMAIN_ID) */

/*
 * OsIf_EnableInterruptSource
 */
#ifdef USING_OS_AUTOSAROS
    #define OsIf_EnableInterruptSource(ISRID, ClearPending)    EnableInterruptSource(ISRID, ClearPending)
#elif defined(USING_OS_ZEPHYR)
    /* specific Zephyr API for enabling interrupts */
#elif defined(USING_OS_FREERTOS)
    /* specific FreeRTOS API for enabling interrupts */
#endif

/*
 * OsIf_SetEvent
 */
#ifdef USING_OS_AUTOSAROS
    #define OsIf_SetEvent(taskId, mask)    SetEvent(taskId, mask)
#elif defined(USING_OS_ZEPHYR)
    /* specific Zephyr API for setting events */
#elif defined(USING_OS_FREERTOS)
    /* specific FreeRTOS API for setting events */
#endif

/*
 * OsIf_ClearEvent
 */
#ifdef USING_OS_AUTOSAROS
    #define OsIf_ClearEvent(mask)    ClearEvent(mask)
#elif defined(USING_OS_ZEPHYR)
    /* specific Zephyr API for clearing events */
#elif defined(USING_OS_FREERTOS)
    /* specific FreeRTOS API for clearing events */
#endif


/*
 * OsIf_WaitEvent
 */
#ifdef USING_OS_AUTOSAROS
    #define OsIf_WaitEvent(mask)    WaitEvent(mask)
#elif defined(USING_OS_ZEPHYR)
    /* specific Zephyr API for waiting for events */
#elif defined(USING_OS_FREERTOS)
    /* specific FreeRTOS API for waiting for events */
#endif

/*
 * OsIf_Schedule
 */
#ifdef USING_OS_AUTOSAROS
    #define OsIf_Schedule()    Schedule()
#elif defined(USING_OS_ZEPHYR)
    /* specific Zephyr API for scheduling */
#elif defined(USING_OS_FREERTOS)
    /* specific FreeRTOS API for scheduling */
#endif
/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* OSIF_INTERNAL_H */
