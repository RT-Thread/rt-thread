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

#ifndef MCU_TRUSTEDFUNCTIONS_H
#define MCU_TRUSTEDFUNCTIONS_H

/**
*   @file    Mcu_TrustedFunctions.h
*
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Mcu driver header file.
*   @details AUTOSAR specific Mcu driver header file.

*   @addtogroup MCU_DRIVER Mcu Driver
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
#include "Clock_Ip_TrustedFunctions.h"
#include "Power_Ip_TrustedFunctions.h"

/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_TRUSTEDFUNCTIONS_VENDOR_ID                     43
#define MCU_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION      4
#define MCU_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION      7
#define MCU_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION   0
#define MCU_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION              5
#define MCU_TRUSTEDFUNCTIONS_SW_MINOR_VERSION              0
#define MCU_TRUSTEDFUNCTIONS_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Mcu_TrustedFunctions.h file and Clock_Ip_TrustedFunctions.h file are of the same vendor */
#if (MCU_TRUSTEDFUNCTIONS_VENDOR_ID != CLOCK_IP_TRUSTEDFUNCTIONS_VENDOR_ID)
    #error "Mcu_TrustedFunctions.h and Clock_Ip_TrustedFunctions.h have different vendor ids"
#endif

/* Check if Mcu_TrustedFunctions.h file and Clock_Ip_TrustedFunctions.h file are of the same Autosar version */
#if ((MCU_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION != CLOCK_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION != CLOCK_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION != CLOCK_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_TrustedFunctions.h and Clock_Ip_TrustedFunctions.h are different"
#endif

/* Check if Mcu_TrustedFunctions.h file and Clock_Ip_TrustedFunctions.h file are of the same Software version */
#if ((MCU_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION != CLOCK_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_SW_MINOR_VERSION != CLOCK_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_SW_PATCH_VERSION != CLOCK_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_TrustedFunctions.h and Clock_Ip_TrustedFunctions.h are different"
#endif

/* Check if Mcu_TrustedFunctions.h file and Power_Ip_TrustedFunctions.h file are of the same vendor */
#if (MCU_TRUSTEDFUNCTIONS_VENDOR_ID != POWER_IP_TRUSTEDFUNCTIONS_VENDOR_ID)
    #error "Mcu_TrustedFunctions.h and Power_Ip_TrustedFunctions.h have different vendor ids"
#endif

/* Check if Mcu_TrustedFunctions.h file and Power_Ip_TrustedFunctions.h file are of the same Autosar version */
#if ((MCU_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION != POWER_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION != POWER_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION != POWER_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_TrustedFunctions.h and Power_Ip_TrustedFunctions.h are different"
#endif

/* Check if Mcu_TrustedFunctions.h file and Power_Ip_TrustedFunctions.h file are of the same Software version */
#if ((MCU_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION != POWER_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_SW_MINOR_VERSION != POWER_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION) || \
     (MCU_TRUSTEDFUNCTIONS_SW_PATCH_VERSION != POWER_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_TrustedFunctions.h and Power_Ip_TrustedFunctions.h are different"
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* MCU_TRUSTEDFUNCTIONS_H */

