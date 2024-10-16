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

#ifndef POWER_IP_MC_RGM_TYPES_H
#define POWER_IP_MC_RGM_TYPES_H

/**
*   @file       Power_Ip_MC_RGM_Types.h
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
#define POWER_IP_MC_RGM_TYPES_VENDOR_ID                       43
#define POWER_IP_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_MC_RGM_TYPES_SW_MAJOR_VERSION                5
#define POWER_IP_MC_RGM_TYPES_SW_MINOR_VERSION                0
#define POWER_IP_MC_RGM_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_MC_RGM_Types.h file and Power_Ip_Specific.h file have same versions */
#if (POWER_IP_MC_RGM_TYPES_VENDOR_ID  != POWER_IP_SPECIFIC_VENDOR_ID)
    #error "Power_Ip_MC_RGM_Types.h and Power_Ip_Specific.h have different vendor IDs"
#endif

/* Check if Power_Ip_MC_RGM_Types.h file and Power_Ip_Specific.h file are of the same Autosar version */
#if ((POWER_IP_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_MC_RGM_Types.h and Power_Ip_Specific.h are different"
#endif

/* Check if Power_Ip_MC_RGM_Types.h file and Power_Ip_Specific.h file are of the same Software version */
#if ((POWER_IP_MC_RGM_TYPES_SW_MAJOR_VERSION != POWER_IP_SPECIFIC_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_TYPES_SW_MINOR_VERSION != POWER_IP_SPECIFIC_SW_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_TYPES_SW_PATCH_VERSION != POWER_IP_SPECIFIC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_MC_RGM_Types.h and Power_Ip_Specific.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

#if (POWER_IP_PERFORM_RESET_API == STD_ON)
/**
* @brief            Reset type to be performed through the Mcu_PerformReset() API.
* @details          Destructive Reset:
*                       - Flash is always reset, so an updated value of the option bits is reloaded
*                         in volatile registers outside of the Flash array.
*                       - Trimming is lost.
*                       - STCU is reset and configured BISTs are executed
*                   Functional Reset:
*                       - Starts the reset sequence from PHASE1 or from PHASE3.
*                       - The volatile registers are not reset; in case of a reset event, the
*                         trimming is maintained.
*                       - No BISTs shall be executed after functional resets.
*/
typedef enum
{
    MCU_FUNC_RESET = 0x5AU,     /**< @brief Functional Reset type. */
    MCU_DEST_RESET = 0x3CU      /**< @brief Destructive Reset type. */

} Power_Ip_MC_RGM_ResetType;
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            Configuration of MC_RGM hardware IP.
* @details          This data configuration is set at module initialization phase.
*/
typedef struct
{
#if (POWER_IP_PERFORM_RESET_API == STD_ON)
    /** @brief RESET type: Functional vs Destructive. */
    Power_Ip_MC_RGM_ResetType ResetType;
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */

#if (defined(POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT))
  #if (POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT == STD_ON)
    /** @brief Enable/Disable functional reset sources (RGM_FERD register). */
    uint32 FuncResetOpt;
  #endif
#endif /* POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT */

#if defined(POWER_IP_FUNCTIONAL_RESET_ENTRY_TIMEOUT_SUPPORT)
  #if (POWER_IP_FUNCTIONAL_RESET_ENTRY_TIMEOUT_SUPPORT == STD_ON)
    uint32 ResetEntryTimeout;
  #endif
#endif

    /** @brief Functional Reset Escalation Threshold (RGM_FRET register). */
    uint32 FesThresholdReset;

    /** @brief Destructive Reset Escalation Threshold (RGM_DRET register). */
    uint32 DesThresholdReset;
  
} Power_Ip_MC_RGM_ConfigType;


#if (defined(POWER_IP_RESET_ALTERNATE_ISR_USED))
  #if (POWER_IP_RESET_ALTERNATE_ISR_USED == STD_ON)
typedef enum
{
    POWER_MC_RGM_UNINIT = 0,  /**< @brief The MC_RGM driver is uninitialized. */
    POWER_MC_RGM_INIT = 1     /**< @brief The MC_RGM driver is initialized. */
} Power_MC_RGM_StatusType;
  #endif
#endif
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
#endif /* POWER_IP_MC_RGM_TYPES_H */

