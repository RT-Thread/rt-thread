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

#ifndef PLATFORM_CFG_DEFINES_H_
#define PLATFORM_CFG_DEFINES_H_

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_CFGDEFINES_VENDOR_ID                     43
#define CDD_PLATFORM_CFGDEFINES_AR_RELEASE_MAJOR_VERSION      4
#define CDD_PLATFORM_CFGDEFINES_AR_RELEASE_MINOR_VERSION      7
#define CDD_PLATFORM_CFGDEFINES_AR_RELEASE_REVISION_VERSION   0
#define CDD_PLATFORM_CFGDEFINES_SW_MAJOR_VERSION              5
#define CDD_PLATFORM_CFGDEFINES_SW_MINOR_VERSION              0
#define CDD_PLATFORM_CFGDEFINES_SW_PATCH_VERSION              0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Std_Types.h */
    #if ((CDD_PLATFORM_CFGDEFINES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_PLATFORM_CFGDEFINES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Platform_CfgDefines.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* Development error checking */
#define PLATFORM_DEV_ERROR_DETECT        (STD_ON)

/* Interrupt monitoring feature enablement */
#define PLATFORM_INT_MONITOR             (STD_OFF)

/* Number of available interrupt monitors */
#define PLATFORM_INT_MONITOR_CNT         (0U)

/* Interrupt monitors maximum latency */
#define PLATFORM_INT_MONITOR_MAX_LATENCY (16777213U)
/* System settings configurable */
#define PLATFORM_SYS_CFG                 (STD_OFF)
/* PlatformMpuM7 configurable */
#define PLATFORM_ENABLE_MPU_M7                 (STD_OFF)
/* IntCtrl configurable */
#define PLATFORM_ENABLE_INT_CTRL                (STD_ON)
/* multi-partition support */
#define PLATFORM_MULTICORE_SUPPORT                   (STD_OFF)
#if (STD_ON == PLATFORM_MULTICORE_SUPPORT)
    #define Platform_GetCoreID()     OsIf_GetUserId()
#else
    #define Platform_GetCoreID()     ((uint8)0UL)
#endif

#define PLATFORM_MAX_PARTITIONS                   (1U) 
/**
* @brief Support for User mode.
*        If this parameter has been configured to STD_ON, the PLATFORM driver code can be executed from both supervisor and user mode.
*/

#define PLATFORM_ENABLE_USER_MODE_SUPPORT   (STD_OFF)


#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
 #ifdef PLATFORM_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == PLATFORM_ENABLE_USER_MODE_SUPPORT)
   #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Platform in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined
  #endif /* (STD_ON == PLATFORM_ENABLE_USER_MODE_SUPPORT) */
 #endif /* ifdef PLATFORM_ENABLE_USER_MODE_SUPPORT*/
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

#endif /* PLATFORM_CFG_DEFINES_H_ */

