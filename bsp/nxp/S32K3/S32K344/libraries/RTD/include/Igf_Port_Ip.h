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

#ifndef IGF_PORT_IP_H
#define IGF_PORT_IP_H

/**
*   @file    Igf_Port_Ip.h
*
*   @addtogroup Igf_IPL
*   @{
*/

#if defined(__cplusplus)
extern "C" {
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Igf_Port_Ip_Cfg.h"
#include "Igf_Port_Ip_Types.h"
#include "Siul2_Port_Ip_Cfg.h"
#include "Devassert.h"

/*=================================================================================================
*                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file and also in the
 *        module's description file
 */
#define IGF_PORT_IP_VENDOR_ID_H                     43
#define IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H      4
#define IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H      7
#define IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_H   0
#define IGF_PORT_IP_SW_MAJOR_VERSION_H              5
#define IGF_PORT_IP_SW_MINOR_VERSION_H              0
#define IGF_PORT_IP_SW_PATCH_VERSION_H              0


/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if the files Igf_Port_Ip.h and Igf_Port_Ip_Cfg.h are of the same version */
#if (IGF_PORT_IP_VENDOR_ID_H != IGF_PORT_IP_VENDOR_ID_CFG_H)
    #error "Igf_Port_Ip.h and Igf_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Igf_Port_Ip.h and Igf_Port_Ip_Cfg.h are of the same Autosar version */
#if ((IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_H != IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Igf_Port_Ip.h and Igf_Port_Ip_Cfg.h are different"
#endif
/* Check if Igf_Port_Ip.h and Igf_Port_Ip_Cfg.h are of the same Software version */
#if ((IGF_PORT_IP_SW_MAJOR_VERSION_H != IGF_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
     (IGF_PORT_IP_SW_MINOR_VERSION_H != IGF_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
     (IGF_PORT_IP_SW_PATCH_VERSION_H != IGF_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Igf_Port_Ip.h and Igf_Port_Ip_Cfg.h are different"
#endif

/* Check if the files Igf_Port_Ip.h and Igf_Port_Ip_Types.h are of the same version */
#if (IGF_PORT_IP_VENDOR_ID_H != IGF_PORT_IP_TYPES_VENDOR_ID_H)
    #error "Igf_Port_Ip.h and Igf_Port_Ip_Types.h have different vendor ids"
#endif
/* Check if Igf_Port_Ip.h and Igf_Port_Ip_Types.h are of the same Autosar version */
#if ((IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != IGF_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != IGF_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_H != IGF_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Igf_Port_Ip.h and Igf_Port_Ip_Types.h are different"
#endif
/* Check if Igf_Port_Ip.h and Igf_Port_Ip_Types.h are of the same Software version */
#if ((IGF_PORT_IP_SW_MAJOR_VERSION_H != IGF_PORT_IP_TYPES_SW_MAJOR_VERSION_H) || \
     (IGF_PORT_IP_SW_MINOR_VERSION_H != IGF_PORT_IP_TYPES_SW_MINOR_VERSION_H) || \
     (IGF_PORT_IP_SW_PATCH_VERSION_H != IGF_PORT_IP_TYPES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Igf_Port_Ip.h and Igf_Port_Ip_Types.h are different"
#endif

/* Check if the files Igf_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same version */
#if (IGF_PORT_IP_VENDOR_ID_H != SIUL2_PORT_IP_VENDOR_ID_CFG_H)
    #error "Igf_Port_Ip.h and Siul2_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Igf_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same Autosar version */
#if ((IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H)  || \
     (IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H)  || \
     (IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_H != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H)  \
    )
    #error "AutoSar Version Numbers of Igf_Port_Ip.h and Siul2_Port_Ip_Cfg.h are different"
#endif
/* Check if Igf_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same Software version */
#if ((IGF_PORT_IP_SW_MAJOR_VERSION_H != SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
     (IGF_PORT_IP_SW_MINOR_VERSION_H != SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
     (IGF_PORT_IP_SW_PATCH_VERSION_H != SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Igf_Port_Ip.h and Siul2_Port_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Igf_Port_Ip.h and Devassert.h are of the same AutoSar version */
    #if ((IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
         (IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H != DEVASSERT_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Igf_Port_Ip.h and Devassert.h are different"
    #endif
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                               DEFINES AND MACROS
=================================================================================================*/

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/


/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                     FUNCTION PROTOTYPES
=================================================================================================*/
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER
/* @brief Allocate defined section for PORT code. */
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/* @brief    Initializes the IGF IP Driver. */
void Igf_Port_Ip_Init(uint8 u8NumChannels, const Igf_Port_Ip_ChannelConfigType *pIgfConfigPtr);

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER */

#if defined(__cplusplus)
}
#endif
/** @} */

#endif /* IGF_PORT_IP_H */
