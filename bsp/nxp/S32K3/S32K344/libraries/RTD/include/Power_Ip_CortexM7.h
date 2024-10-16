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
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef POWER_IP_CORTEXM7_H
#define POWER_IP_CORTEXM7_H

/**
*   @file       Power_Ip_CortexM7.h
*   @version    5.0.0
*
*   @brief   POWER IP driver header file.
*   @details POWER IP driver header file.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
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
#include "Power_Ip_Types.h"
#include "Mcal.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_CORTEXM7_VENDOR_ID                    43
#define POWER_IP_CORTEXM7_AR_RELEASE_MAJOR_VERSION     4
#define POWER_IP_CORTEXM7_AR_RELEASE_MINOR_VERSION     7
#define POWER_IP_CORTEXM7_AR_RELEASE_REVISION_VERSION  0
#define POWER_IP_CORTEXM7_SW_MAJOR_VERSION             5
#define POWER_IP_CORTEXM7_SW_MINOR_VERSION             0
#define POWER_IP_CORTEXM7_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_CortexM7.h file and Power_Ip_Types.h file have same versions */
#if (POWER_IP_CORTEXM7_VENDOR_ID  != POWER_IP_TYPES_VENDOR_ID)
    #error "Power_Ip_CortexM7.h and Power_Ip_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_CortexM7.h file and Power_Ip_Types.h file are of the same Autosar version */
#if ((POWER_IP_CORTEXM7_AR_RELEASE_MAJOR_VERSION    != POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_CORTEXM7_AR_RELEASE_MINOR_VERSION    != POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_CORTEXM7_AR_RELEASE_REVISION_VERSION != POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_CortexM7.h and Power_Ip_Types.h are different"
#endif

/* Check if Power_Ip_CortexM7.h file and Power_Ip_Types.h file are of the same Software version */
#if ((POWER_IP_CORTEXM7_SW_MAJOR_VERSION != POWER_IP_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_CORTEXM7_SW_MINOR_VERSION != POWER_IP_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_CORTEXM7_SW_PATCH_VERSION != POWER_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_CortexM7.h and Power_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Power_Ip_CortexM7.h file and Mcal.h file are of the same Autosar version */
#if ((POWER_IP_CORTEXM7_AR_RELEASE_MAJOR_VERSION    != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_CORTEXM7_AR_RELEASE_MINOR_VERSION    != MCAL_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_CortexM7.h and Mcal.h are different"
#endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/***********************************************************/
/*          CortexM7 System Control Register               */
/***********************************************************/
#define CM7_SCR_BASEADDR    ((uint32)0xE000ED10U)

#define CM7_SCR_SLEEPONEXIT_MASK32  ((uint32)0x00000002U)
#define CM7_SCR_SLEEPDEEP_MASK32    ((uint32)0x00000004U)


/* Memory mapping of Cortex-M Hardware */
/* Application Interrupt and Reset Control Register */

#define CM_AIRCR_ADDR32                     ((uint32)0xE000ED0CU)               /* System Control Block Base Address  */

/** CM7 AIRCR base pointer */
#define IP_CM_AIRCR                         (*(volatile uint32*)(CM_AIRCR_ADDR32))

#define CM_AIRCR_SYSRESETREQ_MASK32         ((uint32)0x4U)
#define CM_AIRCR_VECTKEY_MASK32             ((uint32)0xFFFF0000U)
#define CM_AIRCR_VECTKEY_SHIFT32            ((uint32)16U)

/**
* @violates @ref Reg_eSys_CortexM_H_REF_1 A function should be used in preference to a function-like macro
* where they are interchangeable.
*/
#define CM_AIRCR_VECTKEY(x)                 ((uint32)( (uint32)( (x) << CM_AIRCR_VECTKEY_SHIFT32 ) & CM_AIRCR_VECTKEY_MASK32 ))

#define CM_AIRCR_VECTKEY_KEY_U32            ((uint32)0x000005FAU)

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef POWER_IP_SLEEPONEXIT_SUPPORT
#if (POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON)

#ifdef POWER_IP_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT)
        #define  Call_Power_Ip_CM7_EnableSleepOnExit()  OsIf_Trusted_Call(Power_Ip_CM7_EnableSleepOnExit)
        #define  Call_Power_Ip_CM7_DisableSleepOnExit() OsIf_Trusted_Call(Power_Ip_CM7_DisableSleepOnExit)
    #else
        #define  Call_Power_Ip_CM7_EnableSleepOnExit()  Power_Ip_CM7_EnableSleepOnExit()
        #define  Call_Power_Ip_CM7_DisableSleepOnExit() Power_Ip_CM7_DisableSleepOnExit()
    #endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */
#else /* POWER_IP_ENABLE_USER_MODE_SUPPORT */
    #define  Call_Power_Ip_CM7_EnableSleepOnExit()  Power_Ip_CM7_EnableSleepOnExit()
    #define  Call_Power_Ip_CM7_DisableSleepOnExit() Power_Ip_CM7_DisableSleepOnExit()
#endif /* POWER_IP_ENABLE_USER_MODE_SUPPORT */

#endif /* POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON */
#endif /* POWER_IP_SLEEPONEXIT_SUPPORT */

#ifdef POWER_IP_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT)
        #define  Call_Power_Ip_CM7_EnableDeepSleep()  OsIf_Trusted_Call(Power_Ip_CM7_EnableDeepSleep)
        #define  Call_Power_Ip_CM7_DisableDeepSleep() OsIf_Trusted_Call(Power_Ip_CM7_DisableDeepSleep)
    #else
        #define  Call_Power_Ip_CM7_EnableDeepSleep()  Power_Ip_CM7_EnableDeepSleep()
        #define  Call_Power_Ip_CM7_DisableDeepSleep() Power_Ip_CM7_DisableDeepSleep()
    #endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */
#else /* POWER_IP_ENABLE_USER_MODE_SUPPORT */
    #define  Call_Power_Ip_CM7_EnableDeepSleep()  Power_Ip_CM7_EnableDeepSleep()
    #define  Call_Power_Ip_CM7_DisableDeepSleep() Power_Ip_CM7_DisableDeepSleep()
#endif /* POWER_IP_ENABLE_USER_MODE_SUPPORT */

#ifdef POWER_IP_SLEEPONEXIT_SUPPORT
  #if (POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON)

void Power_Ip_CM7_EnableSleepOnExit(void);
void Power_Ip_CM7_DisableSleepOnExit(void);
  #endif
#endif

void Power_Ip_CM7_DisableDeepSleep(void);
void Power_Ip_CM7_EnableDeepSleep(void);
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* POWER_IP_CORTEXM7_H */


