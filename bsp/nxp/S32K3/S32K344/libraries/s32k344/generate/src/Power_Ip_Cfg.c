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
/**
*   @file       Power_Ip_Cfg.c
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup POWER_DRIVER_CONFIGURATION Power Ip Driver
*   @{
*/


#ifdef __cplusplus
extern "C"
{
#endif




/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_Cfg.h"
#include "Power_Ip_Types.h"
#include "Std_Types.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_CFG_VENDOR_ID_C                      43
#define POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_CFG_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_CFG_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_CFG_SW_MAJOR_VERSION_C               5
#define POWER_IP_CFG_SW_MINOR_VERSION_C               0
#define POWER_IP_CFG_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Power_Ip_Cfg.h file are of the same vendor */
#if (POWER_IP_CFG_VENDOR_ID_C != POWER_IP_CFG_VENDOR_ID)
    #error "Power_Ip_Cfg.c and Power_Ip_Cfg.h have different vendor ids"
#endif
/* Check if source file and Power_Ip_Cfg.h file are of the same Autosar version */
#if ((POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
        (POWER_IP_CFG_AR_RELEASE_MINOR_VERSION_C != POWER_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
        (POWER_IP_CFG_AR_RELEASE_REVISION_VERSION_C != POWER_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_Cfg.c and Power_Ip_Cfg.h are different"
#endif
/* Check if source file and Power_Ip_Cfg.h file are of the same Software version */
#if ((POWER_IP_CFG_SW_MAJOR_VERSION_C != POWER_IP_CFG_SW_MAJOR_VERSION) || \
        (POWER_IP_CFG_SW_MINOR_VERSION_C != POWER_IP_CFG_SW_MINOR_VERSION) || \
        (POWER_IP_CFG_SW_PATCH_VERSION_C != POWER_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_Cfg.c and Power_Ip_Cfg.h are different"
#endif

/* Check if header file and Power_Ip_Types.h file are of the same vendor */
#if (POWER_IP_CFG_VENDOR_ID_C != POWER_IP_TYPES_VENDOR_ID)
    #error "Power_Ip_Cfg.c and Power_Ip_Types.h have different vendor ids"
#endif
/* Check if header file and Power_Ip_Types.h file are of the same Autosar version */
#if ((POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_CFG_AR_RELEASE_MINOR_VERSION_C != POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_CFG_AR_RELEASE_REVISION_VERSION_C != POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_Cfg.c and Power_Ip_Types.h are different"
#endif
/* Check if header file and Power_Ip_Types.h file are of the same Software version */
#if ((POWER_IP_CFG_SW_MAJOR_VERSION_C != POWER_IP_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_CFG_SW_MINOR_VERSION_C != POWER_IP_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_CFG_SW_PATCH_VERSION_C != POWER_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_Cfg.c and Power_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_CFG_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_Cfg.c  and Std_Types.h are different"
#endif
#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */


