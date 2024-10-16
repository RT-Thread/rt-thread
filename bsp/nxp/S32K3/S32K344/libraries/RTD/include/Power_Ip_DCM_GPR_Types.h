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

#ifndef POWER_IP_DCM_GPR_TYPES_H
#define POWER_IP_DCM_GPR_TYPES_H

/**
*   @file       Power_Ip_DCM_GPR_Types.h
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
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_Specific.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_DCM_GPR_TYPES_VENDOR_ID                       43
#define POWER_IP_DCM_GPR_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_DCM_GPR_TYPES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_DCM_GPR_TYPES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_DCM_GPR_TYPES_SW_MAJOR_VERSION                5
#define POWER_IP_DCM_GPR_TYPES_SW_MINOR_VERSION                0
#define POWER_IP_DCM_GPR_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_DCM_GPR_Types.h file and Power_Ip_Specific.h file have same versions */
#if (POWER_IP_DCM_GPR_TYPES_VENDOR_ID  != POWER_IP_SPECIFIC_VENDOR_ID)
    #error "Power_Ip_DCM_GPR_Types.h and Power_Ip_Specific.h have different vendor IDs"
#endif

/* Check if Power_Ip_DCM_GPR_Types.h file and Power_Ip_Specific.h file are of the same Autosar version */
#if ((POWER_IP_DCM_GPR_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_DCM_GPR_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_DCM_GPR_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_DCM_GPR_Types.h and Power_Ip_Specific.h are different"
#endif

/* Check if Power_Ip_DCM_GPR_Types.h file and Power_Ip_Specific.h file are of the same Software version */
#if ((POWER_IP_DCM_GPR_TYPES_SW_MAJOR_VERSION != POWER_IP_SPECIFIC_SW_MAJOR_VERSION) || \
     (POWER_IP_DCM_GPR_TYPES_SW_MINOR_VERSION != POWER_IP_SPECIFIC_SW_MINOR_VERSION) || \
     (POWER_IP_DCM_GPR_TYPES_SW_PATCH_VERSION != POWER_IP_SPECIFIC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_DCM_GPR_Types.h and Power_Ip_Specific.h are different"
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define POWER_IP_GLOBAL_PADKEEPING_ENABLED      (0U)
#define POWER_IP_GLOBAL_PADKEEPING_DISABLED     (1U)

#define POWER_IP_PMIC_PGOOD_BYPASSES_ENABLED      (1U)
#define POWER_IP_PMIC_PGOOD_BYPASSES_DISABLED     (0U)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief            Configuration for DCM_GPR.
* @details          The power control unit (DCM_GPR) acts as a bridge for mapping the DCM_GPR peripheral
 *                  to the DCM_GPR address space.
*/
typedef struct
{
    boolean DcmGprUnderMcuControl;   /**< @brief Specifies whether the the DCM_GPR registers is under MCU control. */
    uint8  BootMode;               /**< @brief The boot mode after exiting Standby mode. */
    uint32 BootAddress;            /**< @brief Cortex-M7_0 base address of vector table. */
#if(defined(POWER_IP_PMIC_PGOOD_SUPPORT) && (STD_ON == POWER_IP_PMIC_PGOOD_SUPPORT))
    uint8 PGOODBypasses;           /**< @brief PMIC_PGOOD handshake (DCMRWF1[PMIC_PGOOD_HNDSHK_BYP]) */
#endif
    uint32 ConfigRegister;         /**< @brief DCM_GPR configuration register (DCMRWF2) */
    boolean GlobalPadkeeping;      /**< @brief Global Padkeeping enablement (DCMRWF1[STANBY_IO_CONFIG]) */
} Power_Ip_DCM_GPR_ConfigType;

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
#endif /* POWER_IP_DCM_GPR_TYPES_H */

