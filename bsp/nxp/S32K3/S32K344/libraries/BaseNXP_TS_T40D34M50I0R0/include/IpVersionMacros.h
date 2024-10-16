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
/**
*   @file    IpVersionMacros.h
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - IP module versions.
*   @details Implements macros for soft and hard lock on CORTEXM hardware platform
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/


#ifndef IPVERSIONMACROS_H
#define IPVERSIONMACROS_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define IPVERSIONMACROS_VENDOR_ID                    43
#define IPVERSIONMACROS_MODULE_ID                    0
#define IPVERSIONMACROS_AR_RELEASE_MAJOR_VERSION     4
#define IPVERSIONMACROS_AR_RELEASE_MINOR_VERSION     7
#define IPVERSIONMACROS_AR_RELEASE_REVISION_VERSION  0
#define IPVERSIONMACROS_SW_MAJOR_VERSION             5
#define IPVERSIONMACROS_SW_MINOR_VERSION             0
#define IPVERSIONMACROS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/* Architectures */
#define IPV_ARMV8_ARCHITECTURE_U32          (0x2B000000UL)
#define IPV_ARM_ARCHITECTURE_U32            (0x1F000000UL)
#define IPV_CORTEXM_ARCHITECTURE_U32        (0x28000000UL)
#define IPV_POWER_ARCHITECTURE_U32          (0x02000000UL)

/* Platforms */
#define IPV_S32S2XX_PLATFORM_U32            (0x001D0000UL)
#define IPV_S32K1XX_PLATFORM_U32            (0x00020000UL)
#define IPV_S32K2XX_PLATFORM_U32            (0x00110000UL)
#define IPV_S32K3XX_PLATFORM_U32            (0x00220000UL)
#define IPV_S32XX_PLATFORM_U32              (0x000B0000UL)
#define IPV_MPC5777C_PLATFORM_U32           (0x00290000UL)
#define IPV_S32R294_PLATFORM_U32            (0x00380000UL)
#define IPV_S32R41_PLATFORM_U32             (0x002F0000UL)
#define IPV_S32ZSE_PLATFORM_U32             (0x00350000UL)

/* Utility IPV Macros */
#define IPV_GET_ARCHITECTURE_U32(IP_VER)    ((IP_VER) & (0xFF000000UL))
#define IPV_GET_PLATFORM_U32(IP_VER)        ((IP_VER) & (0x00FF0000UL))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef IPVERSIONMACROS_H */

/** @} */
