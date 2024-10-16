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

#ifndef TSPC_PORT_IP_H
#define TSPC_PORT_IP_H

/**
*   @file    Tspc_Port_Ip.h
*
*   @addtogroup Tspc_IPL
*   @{
*/

#if defined(__cplusplus)
extern "C" {
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Tspc_Port_Ip_Cfg.h"
#include "Tspc_Port_Ip_Types.h"
#include "Siul2_Port_Ip_Cfg.h"
#include "Devassert.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file and also in the
 *        module's description file
 */
#define TSPC_PORT_IP_VENDOR_ID_H                     43
#define TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H      4
#define TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H      7
#define TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_H   0
#define TSPC_PORT_IP_SW_MAJOR_VERSION_H              5
#define TSPC_PORT_IP_SW_MINOR_VERSION_H              0
#define TSPC_PORT_IP_SW_PATCH_VERSION_H              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Tspc_Port_Ip.h and Tspc_Port_Ip_Cfg.h are of the same version */
#if (TSPC_PORT_IP_VENDOR_ID_H != TSPC_PORT_IP_VENDOR_ID_CFG_H)
    #error "Tspc_Port_Ip.h and Tspc_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Tspc_Port_Ip.h and Tspc_Port_Ip_Cfg.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_H != TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip.h and Tspc_Port_Ip_Cfg.h are different"
#endif
/* Check if Tspc_Port_Ip.h and Tspc_Port_Ip_Cfg.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_H != TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_SW_MINOR_VERSION_H != TSPC_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_SW_PATCH_VERSION_H != TSPC_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip.h and Tspc_Port_Ip_Cfg.h are different"
#endif

/* Check if the files Tspc_Port_Ip.h and Tspc_Port_Ip_Types.h are of the same version */
#if (TSPC_PORT_IP_VENDOR_ID_H != TSPC_PORT_IP_TYPES_VENDOR_ID_H)
    #error "Tspc_Port_Ip.h and Tspc_Port_Ip_Types.h have different vendor ids"
#endif
/* Check if Tspc_Port_Ip.h and Tspc_Port_Ip_Types.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != TSPC_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != TSPC_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_H != TSPC_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip.h and Tspc_Port_Ip_Types.h are different"
#endif
/* Check if Tspc_Port_Ip.h and Tspc_Port_Ip_Types.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_H != TSPC_PORT_IP_TYPES_SW_MAJOR_VERSION_H) || \
     (TSPC_PORT_IP_SW_MINOR_VERSION_H != TSPC_PORT_IP_TYPES_SW_MINOR_VERSION_H) || \
     (TSPC_PORT_IP_SW_PATCH_VERSION_H != TSPC_PORT_IP_TYPES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip.h and Tspc_Port_Ip_Types.h are different"
#endif

/* Check if the files Tspc_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same version */
#if (TSPC_PORT_IP_VENDOR_ID_H != SIUL2_PORT_IP_VENDOR_ID_CFG_H)
    #error "Tspc_Port_Ip.h and Siul2_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Tspc_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_H != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip.h and Siul2_Port_Ip_Cfg.h are different"
#endif
/* Check if Tspc_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_H != SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_SW_MINOR_VERSION_H != SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
     (TSPC_PORT_IP_SW_PATCH_VERSION_H != SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip.h and Siul2_Port_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Tspc_Port_Ip.h and Devassert.h are of the same version */
    #if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
         (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H != DEVASSERT_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Tspc_Port_Ip.h and Devassert.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#if (SIUL2_PORT_IP_DEV_ERROR_DETECT == STD_ON)
#define TSPC_PORT_DEV_ASSERT(par) DevAssert(par)
#else
#define TSPC_PORT_DEV_ASSERT(par)
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
#ifdef FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING

/* @brief Allocate defined section for PORT code. */
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function shall enable the specified group whose pads
 * are participating in simultaneous transition.
 *
 * @param[in] group Specified group whose pads are participating in simultaneous transition.
*/
void Tspc_Port_Ip_EnableObeGroup(uint8 group);

/*!
 * @brief Disables the OBE group according to parameter
 *
 * This function shall disable the specified group whose pads
 * are participating in simultaneous transition.
 *
 * @param[in] group Specified group whose pads are participating in simultaneous transition.
*/
void Tspc_Port_Ip_DisableObeGroup(uint8 group);

/*!
 * @brief Masks pins the group according to parameter
 *
 * This function shall mask the specified pins inside a group 
 * across OBE1 and OBE2.
 *
 * @param[in] group Specified group whose pads are participating in simultaneous transition.
 * @param[in] mask Mask the specified pins inside a group.
*/
void Tspc_Port_Ip_MaskObeGroup(uint8 group, 
                               uint64 mask
                              );

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function shall configure which channels participate in the OBE group.
 * This function enables the specified group whose pads are participating in simultaneous transition.
 *
 * @param[in] cfgCount The number of configured pins in structure
 * @param[in] config The configuration structure
*/
void Tspc_Port_Ip_ConfigureObeGroup(uint32 cfgCount,
                                    const Tspc_Port_Ip_ObeGroupConfig config[]
                                   );

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#endif /* FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING */

#if defined(__cplusplus)
}
#endif

/** @} */

#endif /* TSPC_PORT_IP_H */
