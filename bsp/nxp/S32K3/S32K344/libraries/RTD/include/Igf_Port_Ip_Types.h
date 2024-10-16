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

#ifndef IGF_PORT_IP_TYPES_H
#define IGF_PORT_IP_TYPES_H

/**
*   @file    Igf_Port_Ip_Types.h
*
*   @defgroup Igf_IPL IGF IPL
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
#include "Std_Types.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file and also in the
 *        module's description file
 */
#define IGF_PORT_IP_TYPES_VENDOR_ID_H                     43
#define IGF_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H      4
#define IGF_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H      7
#define IGF_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H   0
#define IGF_PORT_IP_TYPES_SW_MAJOR_VERSION_H              5
#define IGF_PORT_IP_TYPES_SW_MINOR_VERSION_H              0
#define IGF_PORT_IP_TYPES_SW_PATCH_VERSION_H              0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Igf_Port_Ip_Types.h and Std_Types.h are of the same version */
    #if ((IGF_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H != STD_AR_RELEASE_MAJOR_VERSION) || \
         (IGF_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Igf_Port_Ip_Types.h and Std_Types.h are different"
    #endif
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/* Define used to signal that a register should not be configured with any value */
#define IGF_PORT_IP_REG_NOT_CONFIGURED_U32     ((uint32)0xFFFFFFFFU)

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/
/**
* @brief   Single Igf channel configuration.
* @details This structure contains all configuration parameters of a single IGF channel
*          identified by u8IgfInstance and u8IgfChannel.
*
* @api
*/
typedef struct
{
    uint8   u8IgfInstance;
    uint8   u8IgfChannel;
    uint32  u32IgfMCR;
    uint32  u32IgfPRESR;
    uint32  u32IgfRTH;
    uint32  u32IgfFTH;
} Igf_Port_Ip_ChannelConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/


#if defined(__cplusplus)
}
#endif

/** @} */

#endif /* IGF_PORT_IP_TYPES_H */
