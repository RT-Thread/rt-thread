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

#ifndef POWER_IP_TYPES_H
#define POWER_IP_TYPES_H

/**
*   @file       Power_Ip_Types.h
*   @version    5.0.0
*
*   @brief   POWER IP type header file.
*   @details POWER IP type header file.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2012 violations
*
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_MC_ME_Types.h"
#include "Power_Ip_MC_RGM_Types.h"
#include "Power_Ip_PMC_Types.h"
#include "Power_Ip_DCM_GPR_Types.h"

#if(STD_ON == POWER_IP_AEC_SUPPORT)
#include "Power_Ip_AEC_Types.h"
#endif
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_TYPES_VENDOR_ID                       43
#define POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_TYPES_SW_MAJOR_VERSION                5
#define POWER_IP_TYPES_SW_MINOR_VERSION                0
#define POWER_IP_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_Types.h file and Power_Ip_MC_ME_Types.h file have same versions */
#if (POWER_IP_TYPES_VENDOR_ID  != POWER_IP_MC_ME_TYPES_VENDOR_ID)
    #error "Power_Ip_Types.h and Power_Ip_MC_ME_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_MC_ME_Types.h file are of the same Autosar version */
#if ((POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_MC_ME_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_MC_ME_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_MC_ME_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Types.h and Power_Ip_MC_ME_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_MC_ME_Types.h file are of the same Software version */
#if ((POWER_IP_TYPES_SW_MAJOR_VERSION != POWER_IP_MC_ME_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_TYPES_SW_MINOR_VERSION != POWER_IP_MC_ME_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_TYPES_SW_PATCH_VERSION != POWER_IP_MC_ME_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Types.h and Power_Ip_MC_ME_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_MC_RGM_Types.h file have same versions */
#if (POWER_IP_TYPES_VENDOR_ID  != POWER_IP_MC_RGM_TYPES_VENDOR_ID)
    #error "Power_Ip_Types.h and Power_Ip_MC_RGM_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_MC_RGM_Types.h file are of the same Autosar version */
#if ((POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Types.h and Power_Ip_MC_RGM_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_MC_RGM_Types.h file are of the same Software version */
#if ((POWER_IP_TYPES_SW_MAJOR_VERSION != POWER_IP_MC_RGM_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_TYPES_SW_MINOR_VERSION != POWER_IP_MC_RGM_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_TYPES_SW_PATCH_VERSION != POWER_IP_MC_RGM_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Types.h and Power_Ip_MC_RGM_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_PMC_Types.h file have same versions */
#if (POWER_IP_TYPES_VENDOR_ID  != POWER_IP_PMC_TYPES_VENDOR_ID)
    #error "Power_Ip_Types.h and Power_Ip_PMC_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_PMC_Types.h file are of the same Autosar version */
#if ((POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_PMC_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_PMC_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_PMC_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Types.h and Power_Ip_PMC_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_PMC_Types.h file are of the same Software version */
#if ((POWER_IP_TYPES_SW_MAJOR_VERSION != POWER_IP_PMC_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_TYPES_SW_MINOR_VERSION != POWER_IP_PMC_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_TYPES_SW_PATCH_VERSION != POWER_IP_PMC_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Types.h and Power_Ip_PMC_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_DCM_GPR_Types.h file have same versions */
#if (POWER_IP_TYPES_VENDOR_ID  != POWER_IP_DCM_GPR_TYPES_VENDOR_ID)
    #error "Power_Ip_Types.h and Power_Ip_DCM_GPR_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_DCM_GPR_Types.h file are of the same Autosar version */
#if ((POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_DCM_GPR_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_DCM_GPR_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_DCM_GPR_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Types.h and Power_Ip_DCM_GPR_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_DCM_GPR_Types.h file are of the same Software version */
#if ((POWER_IP_TYPES_SW_MAJOR_VERSION != POWER_IP_DCM_GPR_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_TYPES_SW_MINOR_VERSION != POWER_IP_DCM_GPR_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_TYPES_SW_PATCH_VERSION != POWER_IP_DCM_GPR_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Types.h and Power_Ip_DCM_GPR_Types.h are different"
#endif

#if(STD_ON == POWER_IP_AEC_SUPPORT)
/* Check if Power_Ip_Types.h file and Power_Ip_AEC_Types.h file have same versions */
#if (POWER_IP_TYPES_VENDOR_ID  != POWER_IP_AEC_TYPES_VENDOR_ID)
    #error "Power_Ip_Types.h and Power_Ip_AEC_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_AEC_Types.h file are of the same Autosar version */
#if ((POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_AEC_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_AEC_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_AEC_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Types.h and Power_Ip_AEC_Types.h are different"
#endif

/* Check if Power_Ip_Types.h file and Power_Ip_AEC_Types.h file are of the same Software version */
#if ((POWER_IP_TYPES_SW_MAJOR_VERSION != POWER_IP_AEC_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_TYPES_SW_MINOR_VERSION != POWER_IP_AEC_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_TYPES_SW_PATCH_VERSION != POWER_IP_AEC_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Types.h and Power_Ip_AEC_Types.h are different"
#endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define POWER_IP_ERR_CODE_RESERVED   0xFF

#define POWER_IP_E_ISR_FUNC_RESET_ALT_FAILURE        ((uint8)0x03U)
#define POWER_IP_E_ISR_DEST_RESET_ALT_FAILURE        ((uint8)0x04U)
#define POWER_IP_E_ISR_VOLTAGE_ERROR                 ((uint8)0x08U)
#define POWER_IP_E_ISR_LOW_VOLTAGE                   ((uint8)0x09U)
#define POWER_IP_E_ISR_HIGH_VOLTAGE                  ((uint8)0x0AU)
#define POWER_IP_LAST_MILE_REGULATOR_DISABLED        ((uint8)0x55U)
#define POWER_IP_E_FLASH_HV_OPERATION_ONGOING        ((uint8)0x07U)

#define POWER_IP_DATAWIDTH_8                     (8U)
#define POWER_IP_DATAWIDTH_16                    (16U)
#define POWER_IP_DATAWIDTH_32                    (32U)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief
* @details
*/
typedef struct
{
    /**< @brief Configuration for MC_RGM (Reset Generation Module) hardware IP. */
    const Power_Ip_MC_RGM_ConfigType * McRgmConfigPtr;
    /**< @brief Configuration for PMC (Power Management Unit) hardware IP, part of PMC. */
    const Power_Ip_PMC_ConfigType * PMCConfigPtr;
#if(STD_ON == POWER_IP_AEC_SUPPORT)
    /**< @brief Configuration for AEC hardware IP. */
    const Power_Ip_AEC_ConfigType * AECConfigPtr;
#endif
} Power_Ip_HwIPsConfigType;


/**
* @brief            Power Modes encoding.
* @details          Supported power modes for the MCU.
*/
typedef enum
{
    POWER_IP_DEST_RESET_MODE = 0U,           /**< @brief Destructive Reset Mode. */
    POWER_IP_FUNC_RESET_MODE = 1U,           /**< @brief Functional Reset Mode. */
    POWER_IP_RESET_MODE = 2U,                /**< @brief Any reset mode. Used when the particular type of reset doesn't matter. */
    POWER_IP_CORE_WARM_RESET_MODE = 3U,      /**< @brief Core Warm Reset Mode. */
#if (defined(POWER_IP_ENTER_LOW_POWER_MODE))
  #if (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)
    POWER_IP_CORE_STANDBY_MODE = 13U,        /**< @brief Core Standby Mode */
    POWER_IP_SOC_PREPARE_STANDBY_MODE = 14U, /**< @brief Prepare Standby Mode */
    POWER_IP_SOC_STANDBY_MODE  = 15U,        /**< @brief StandBy Mode. */
    POWER_IP_STANDBY_MODE  = 16U,            /**< @brief Prepare Standby and StandBy Mode. */
    POWER_IP_SOC_PREPARE_FAST_STANDBY_MODE = 17U, /**< @brief Prepare Fast Standby Mode */
    POWER_IP_SOC_FAST_STANDBY_MODE  = 18U,        /**< @brief Fast StandBy Mode. */
    POWER_IP_FAST_STANDBY_MODE  = 19U,            /**< @brief Prepare Fast Standby and Fast StandBy Mode. */
  #endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
#endif
    POWER_IP_RUN_MODE   = 32U,               /**< @brief Run Mode. */

} Power_Ip_PowerModeType;

/**
* @brief            The type Mcu_RawResetType specifies the reset reason in raw register format, read from a reset status register.
* @details          The type shall be uint8, uint16 or uint32 based on best performance.
*
* @implements Mcu_RawResetType_typedef
*
*/
typedef uint32 Power_Ip_RawResetType;   /**< @brief Destructive and Functional Reset Events Log. */

/**
* @brief            The Mcu_ModeType specifies the identification (ID) for a MCU mode, configured via configuration structure.
* @details          The type shall be uint8, uint16 or uint32.
*
* @implements     Mcu_ModeType_typedef
*
*/
typedef uint32 Power_Ip_ModeType;

/**
* @brief
* @details
*/
typedef struct
{
    /**< @brief The ID for Power Mode configuration. */
    Power_Ip_ModeType ModeConfigId;

    /**< @brief The Power Mode name (code). */
    Power_Ip_PowerModeType PowerMode;

    /**< @brief Indicates sleep-on-exit configuration */
    boolean SleepOnExit;

    /**< @brief MC_ME IP Mode settings. */
    const Power_Ip_MC_ME_ModeConfigType * McMeModeConfigPtr;

#if (defined(POWER_IP_RESET_DOMAINS_SUPPORTED))
  #if (POWER_IP_RESET_DOMAINS_SUPPORTED == STD_ON)
    /**< @brief MC_RGM IP Mode settings. */
    const Power_Ip_MC_RGM_ModeConfigType * McRgmModeConfigPtr;
  #endif /* (POWER_IP_RESET_DOMAINS_SUPPORTED == STD_ON) */
#endif
    /**< @brief Configuration for DCM_GPR (Device Configuration Module General-Purpose Registers) hardware IP. */
    const Power_Ip_DCM_GPR_ConfigType * DcmGprConfigPtr;

} Power_Ip_ModeConfigType;


/** @brief Power ip report error types. */
typedef enum
{
    POWER_IP_REPORT_TIMEOUT_ERROR               = 0U,   /**< @brief Report Timeout Error. */
    POWER_IP_ISR_ERROR                          = 1U,   /**< @brief Notification Error. */
    POWER_IP_PMC_ERROR                          = 2U,   /**< @brief Notification PMC. */
    POWER_IP_ISR_VOLTAGE_HVD_VDDINT_DETECT      = 3U,   /**< @brief Report the Voltage on VDDINT is high-voltage detected. */
    POWER_IP_ISR_VOLTAGE_HVD_15_DETECT          = 4U,   /**< @brief Report the Voltage on VDD15 is high-voltage detected. */
    POWER_IP_ISR_VOLTAGE_HVD_VDD_DETECT         = 5U,   /**< @brief Report the Voltage on VDD is high-voltage detected. */
    POWER_IP_ISR_VOLTAGE_LVD_VDDC_DETECT        = 6U,   /**< @brief Report the Voltage on VDDC is low-voltage detected. */
    POWER_IP_ISR_VOLTAGE_LVD_VLS_DETECT         = 7U,   /**< @brief Report the Voltage on VLS is low-voltage detected. */
} Power_Ip_ReportErrorType;

/*!
 * @brief Power report error callback structure.
 * Implements PowerReportErrorCallbackType_Class
 */
typedef void (*Power_Ip_ReportErrorsCallbackType)(Power_Ip_ReportErrorType Error, uint8 ErrorCode);

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
#endif /* POWER_IP_TYPES_H */


