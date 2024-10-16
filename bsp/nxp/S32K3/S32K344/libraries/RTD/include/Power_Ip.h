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

#ifndef POWER_IP_H
#define POWER_IP_H

/**
*   @file       Power_Ip.h
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
#include "Std_Types.h"
#include "Power_Ip_Cfg.h"
#include "Power_Ip_CortexM7.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_VENDOR_ID                       43
#define POWER_IP_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_SW_MAJOR_VERSION                5
#define POWER_IP_SW_MINOR_VERSION                0
#define POWER_IP_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.h  and Std_Types.h are different"
#endif
#endif

/* Check if Power_Ip.h file and Power_Ip_Cfg.h file have same versions */
#if (POWER_IP_VENDOR_ID  != POWER_IP_CFG_VENDOR_ID)
    #error "Power_Ip.h and Power_Ip_Cfg.h have different vendor IDs"
#endif

/* Check if Power_Ip.h file and Power_Ip_Cfg.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION    != POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION    != POWER_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION != POWER_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip.h and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip.h file and Power_Ip_Cfg.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION != POWER_IP_CFG_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION != POWER_IP_CFG_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION != POWER_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip.h and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip.h file and Power_Ip_CortexM7.h file have same versions */
#if (POWER_IP_VENDOR_ID  != POWER_IP_CORTEXM7_VENDOR_ID)
    #error "Power_Ip.h and Power_Ip_CortexM7.h have different vendor IDs"
#endif

/* Check if Power_Ip.h file and Power_Ip_CortexM7.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION    != POWER_IP_CORTEXM7_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION    != POWER_IP_CORTEXM7_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION != POWER_IP_CORTEXM7_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip.h and Power_Ip_CortexM7.h are different"
#endif

/* Check if Power_Ip.h file and Power_Ip_CortexM7.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION != POWER_IP_CORTEXM7_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION != POWER_IP_CORTEXM7_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION != POWER_IP_CORTEXM7_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip.h and Power_Ip_CortexM7.h are different"
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


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Power initialization
 *
 * This function power initialization
 *
 * @param[in] HwIPsConfigPtr  power initialization configuration.
 *
 * @return void
 */
void Power_Ip_Init(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr);


/*!
 * @brief Sets mode
 *
 * This function sets mode.
 *
 * @param[in] ModeConfigPtr  power set mote configuration.
 *
 * @return void
 */
void Power_Ip_SetMode (const Power_Ip_ModeConfigType * ModeConfigPtr);

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE))
  #if (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)
/**
* @brief            This function returns the previous mode.
* @details          This function returns the previous mode.
*
* @return           Status of the previous mode.
*
* @implements Power_Ip_GetPreviousMode_Activity
*
*/
Power_Ip_PowerModeType Power_Ip_GetPreviousMode(void);
  #endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
#endif

#if (POWER_IP_PERFORM_RESET_API == STD_ON)
/*!
 * @brief Performs reset
 *
 * This function performs reset.
 *
 * @param[in] HwIPsConfigPtr  reset initialization configuration.
 *
 * @return void
 */
void Power_Ip_PerformReset(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr);
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */

/*!
 * @brief Returns reset type
 *
 * This function returns reset type.
 *
 * @return Power_Ip_ResetType   Reset type
 */
Power_Ip_ResetType Power_Ip_GetResetReason(void);

/*!
 * @brief Returns raw reset type
 *
 * This function returns raw reset type.
 *
 * @return Power_Ip_RawResetType   Raw reset type
 */
Power_Ip_RawResetType Power_Ip_GetResetRawValue(void);

/*!
 * @brief Install report error callback
 *
 * This function installs a callback for reporting errors from power driver
 *
 *
 * @param[in] ReportErrorsCallback      Callback to be installed.
 *
 * @return void
 */
void Power_Ip_InstallNotificationsCallback(Power_Ip_ReportErrorsCallbackType ReportErrorsCallback);

#ifdef POWER_IP_SLEEPONEXIT_SUPPORT
  #if (POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON)

/**
* @brief        The function enable SLEEPONEXIT bit.
* @details      The function enable SLEEPONEXIT bit.
*
* @return void
*
* @implements Power_Ip_EnableSleepOnExit_Activity
*/
void Power_Ip_EnableSleepOnExit(void);

/**
* @brief        The function disable SLEEPONEXIT bit.
* @details      The function disable SLEEPONEXIT bit.
*
* @return void
*
* @implements Power_Ip_DisableSleepOnExit_Activity
*/
void Power_Ip_DisableSleepOnExit(void);

  #endif
#endif


#ifdef POWER_IP_PMCAECONFIG_API
#if (POWER_IP_PMCAECONFIG_API == STD_ON)
void Power_Ip_PmcAeConfig(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr);
#endif /* (POWER_IP_PMCAECONFIG_API == STD_ON) */
#endif

#ifdef POWER_IP_AECRESETCONFIG_API
#if (POWER_IP_AECRESETCONFIG_API == STD_ON)
void Power_Ip_AecResetConfig(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr);
#endif /* (POWER_IP_AECRESETCONFIG_API == STD_ON) */
#endif

#ifdef POWER_IP_LASTMILE_SUPPORT
  #if (STD_ON == POWER_IP_LASTMILE_SUPPORT)
/**
* @brief        The function enable LMEN bit.
* @details      The function enable LMEN bit.
*
* @return void
*
*
*/
void Power_Ip_EnableLastMile(boolean BJTused);

/**
* @brief        The function disable LMEN bit.
* @details      The function disable LMEN bit.
*
* @return void
*
*
*/
void Power_Ip_DisableLastMile(void);
  #endif
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif


/** @} */
#endif /* POWER_IP_H */

