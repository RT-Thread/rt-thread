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

#ifndef RAM_IP_CFG_H
#define RAM_IP_CFG_H

/**
*   @file       Ram_Ip_Cfg.h
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup RAM_DRIVER_CONFIGURATION Ram Ip Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Ram_Ip_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RAM_IP_CFG_VENDOR_ID                      43
#define RAM_IP_CFG_AR_RELEASE_MAJOR_VERSION       4
#define RAM_IP_CFG_AR_RELEASE_MINOR_VERSION       7
#define RAM_IP_CFG_AR_RELEASE_REVISION_VERSION    0
#define RAM_IP_CFG_SW_MAJOR_VERSION               5
#define RAM_IP_CFG_SW_MINOR_VERSION               0
#define RAM_IP_CFG_SW_PATCH_VERSION               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Ram_Ip_Cfg.h file and Ram_Ip_PBcfg.h file are of the same vendor */
#if (RAM_IP_CFG_VENDOR_ID != RAM_IP_PBCFG_VENDOR_ID)
    #error "Ram_Ip_Cfg.h and Ram_Ip_PBcfg.h have different vendor ids"
#endif

/* Check if Ram_Ip_Cfg.h file and Ram_Ip_PBcfg.h file are of the same Autosar version */
#if ((RAM_IP_CFG_AR_RELEASE_MAJOR_VERSION != RAM_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_CFG_AR_RELEASE_MINOR_VERSION != RAM_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (RAM_IP_CFG_AR_RELEASE_REVISION_VERSION != RAM_IP_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Ram_Ip_Cfg.h and Ram_Ip_PBcfg.h are different"
#endif

/* Check if Ram_Ip_Cfg.h file and Ram_Ip_PBcfg.h file are of the same Software version */
#if ((RAM_IP_CFG_SW_MAJOR_VERSION != RAM_IP_PBCFG_SW_MAJOR_VERSION) || \
     (RAM_IP_CFG_SW_MINOR_VERSION != RAM_IP_PBCFG_SW_MINOR_VERSION) || \
     (RAM_IP_CFG_SW_PATCH_VERSION != RAM_IP_PBCFG_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of Ram_Ip_Cfg.h and Ram_Ip_PBcfg.h are different"
#endif


/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Detection and reporting of development errors(API parameter checking) at IP level shall be pre compile time configurable.
* @implements RAM_IP_DEV_ERROR_DETECT_Define
*/
#define RAM_IP_DEV_ERROR_DETECT         (STD_OFF)

#define RAM_IP_TIMEOUT_TYPE                (OSIF_COUNTER_DUMMY)

#define RAM_IP_TIMEOUT_VALUE_US            (50000U)

/**
* @brief        Support for User mode.
*               If this parameter has been configured to 'TRUE' the Ram can be executed from both supervisor and user mode.
*/
#define RAM_IP_ENABLE_USER_MODE_SUPPORT  (STD_OFF)

/** Check the driver user mode is enabled only when the MCAL_ENABLE_USER_MODE_SUPPORT is enabled */
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT)
    #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Ram in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
  #endif /* (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT) */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* RAM_IP_CFG_H */


