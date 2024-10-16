/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
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
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef TSPC_PORT_IP_CFG_H
#define TSPC_PORT_IP_CFG_H

/**
*   @file    Tspc_Port_Ip_Cfg.h
*
*   @addtogroup Port_CFG
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
#include "Tspc_Port_Ip_Types.h"
#include "S32K344_TSPC.h"
#include "Tspc_Port_Ip_PBcfg.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define TSPC_PORT_IP_VENDOR_ID_CFG_H                       43
#define TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H        4
#define TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H        7
#define TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H     0
#define TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_H                5
#define TSPC_PORT_IP_SW_MINOR_VERSION_CFG_H                0
#define TSPC_PORT_IP_SW_PATCH_VERSION_CFG_H                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_Types.h are of the same version */
#if (TSPC_PORT_IP_VENDOR_ID_CFG_H != TSPC_PORT_IP_TYPES_VENDOR_ID_H)
    #error "Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_Types.h have different vendor ids"
#endif

/* Check if Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_Types.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H    != TSPC_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H    != TSPC_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H != TSPC_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_Types.h are different"
#endif

/* Check if Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_Types.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_H != TSPC_PORT_IP_TYPES_SW_MAJOR_VERSION_H) || \
     (TSPC_PORT_IP_SW_MINOR_VERSION_CFG_H != TSPC_PORT_IP_TYPES_SW_MINOR_VERSION_H) || \
     (TSPC_PORT_IP_SW_PATCH_VERSION_CFG_H != TSPC_PORT_IP_TYPES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_Types.h are different"
#endif

/* Check if the files Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_PBcfg.h are of the same version */
#if (TSPC_PORT_IP_VENDOR_ID_CFG_H != TSPC_PORT_IP_VENDOR_ID_PBCFG_H)
    #error "Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_PBcfg.h have different vendor IDs"
#endif
/* Check if the files Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_PBcfg.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H != TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_H) ||   \
     (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H != TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_PBCFG_H) ||   \
     (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H != TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_PBcfg.h are different"
#endif
/* Check if the files Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_PBcfg.h are of the same software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_H != TSPC_PORT_IP_SW_MAJOR_VERSION_PBCFG_H) || \
     (TSPC_PORT_IP_SW_MINOR_VERSION_CFG_H != TSPC_PORT_IP_SW_MINOR_VERSION_PBCFG_H) || \
     (TSPC_PORT_IP_SW_PATCH_VERSION_CFG_H != TSPC_PORT_IP_SW_PATCH_VERSION_PBCFG_H)     \
    )
    #error "Software Version Numbers of Tspc_Port_Ip_Cfg.h and Tspc_Port_Ip_PBcfg.h are different"
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/* Pre-processor switch to enable/disable Touch Sense support */
#define FEATURE_TSPC_PORT_IP_SUPPORT      (STD_OFF)

/*! @brief User number of configured pins */
#define NUM_OF_OBE_GROUP_CONFIG 3

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

TSPC_PORT_CONFIG_PB

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* TSPC_PORT_IP_CFG_H */
