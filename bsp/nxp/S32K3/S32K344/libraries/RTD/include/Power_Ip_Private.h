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

#ifndef POWER_IP_PRIVATE_H
#define POWER_IP_PRIVATE_H

/**
*   @file       Power_Ip_Private.h
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
#include "Power_Ip_Types.h"
#include "Power_Ip_Cfg.h"
#ifdef POWER_IP_DEV_ERROR_DETECT
#if (STD_ON == POWER_IP_DEV_ERROR_DETECT)
    #include "Devassert.h"
#endif /* (STD_ON == POWER_IP_DEV_ERROR_DETECT) */
#endif /* #ifdef POWER_IP_DEV_ERROR_DETECT */
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_PRIVATE_VENDOR_ID                    43
#define POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION     4
#define POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION     7
#define POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION  0
#define POWER_IP_PRIVATE_SW_MAJOR_VERSION             5
#define POWER_IP_PRIVATE_SW_MINOR_VERSION             0
#define POWER_IP_PRIVATE_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_Private.h file and Power_Ip_Types.h file have same versions */
#if (POWER_IP_PRIVATE_VENDOR_ID  != POWER_IP_TYPES_VENDOR_ID)
    #error "Power_Ip_Private.h and Power_Ip_Types.h have different vendor IDs"
#endif

/* Check if Power_Ip_Private.h file and Power_Ip_Types.h file are of the same Autosar version */
#if ((POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION != POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Private.h and Power_Ip_Types.h are different"
#endif

/* Check if Power_Ip_Private.h file and Power_Ip_Types.h file are of the same Software version */
#if ((POWER_IP_PRIVATE_SW_MAJOR_VERSION != POWER_IP_TYPES_SW_MAJOR_VERSION) || \
     (POWER_IP_PRIVATE_SW_MINOR_VERSION != POWER_IP_TYPES_SW_MINOR_VERSION) || \
     (POWER_IP_PRIVATE_SW_PATCH_VERSION != POWER_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Private.h and Power_Ip_Types.h are different"
#endif

/* Check if Power_Ip_Private.h file and Power_Ip_Cfg.h file have same versions */
#if (POWER_IP_PRIVATE_VENDOR_ID  != POWER_IP_CFG_VENDOR_ID)
    #error "Power_Ip_Private.h and Power_Ip_Cfg.h have different vendor IDs"
#endif

/* Check if Power_Ip_Private.h file and Power_Ip_Cfg.h file are of the same Autosar version */
#if ((POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != POWER_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION != POWER_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Private.h and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip_Private.h file and Power_Ip_Cfg.h file are of the same Software version */
#if ((POWER_IP_PRIVATE_SW_MAJOR_VERSION != POWER_IP_CFG_SW_MAJOR_VERSION) || \
     (POWER_IP_PRIVATE_SW_MINOR_VERSION != POWER_IP_CFG_SW_MINOR_VERSION) || \
     (POWER_IP_PRIVATE_SW_PATCH_VERSION != POWER_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Private.h and Power_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#ifdef POWER_IP_DEV_ERROR_DETECT
#if (STD_ON == POWER_IP_DEV_ERROR_DETECT)
/* Check if Power_Ip_Private.h file and Devassert.h file are of the same Autosar version */
#if ((POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != DEVASSERT_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Private.h and Devassert.h are different"
#endif
#endif /* (STD_ON == POWER_IP_DEV_ERROR_DETECT) */
#endif /* #ifdef POWER_IP_DEV_ERROR_DETECT */
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#ifdef POWER_IP_DEV_ERROR_DETECT
  #if (POWER_IP_DEV_ERROR_DETECT == STD_ON)
    #define POWER_IP_DEV_ASSERT(x)      DevAssert(x)
  #else
    #define POWER_IP_DEV_ASSERT(x)
  #endif
#else
    #define POWER_IP_DEV_ASSERT(x)
#endif
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Power Report Error Callback */
extern Power_Ip_ReportErrorsCallbackType Power_Ip_pfReportErrorsCallback;

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

void Power_Ip_ReportPowerErrors(Power_Ip_ReportErrorType Error, uint8 ErrorCode);
void Power_Ip_ReportPowerErrorsEmptyCallback(Power_Ip_ReportErrorType Error, uint8 ErrorCode);

/*!
 * @brief Initializes a starting reference point for timeout
 *
 * @param[out] StartTimeOut    The starting time from which elapsed time is measured
 * @param[out] ElapsedTimeOut  The elapsed time to be passed to Power_Ip_TimeoutExpired
 * @param[out] TimeoutTicksOut The timeout value (in ticks) to be passed to Power_Ip_TimeoutExpired
 * @param[in]  TimeoutUs       The timeout value (in microseconds)
 */
void Power_Ip_StartTimeout(uint32 *StartTimeOut,
                       uint32 *ElapsedTimeOut,
                       uint32 *TimeoutTicksOut,
                       uint32 TimeoutUs);

/*!
 * @brief Checks for timeout condition.
 *
 * @param[in,out] StartTimeInOut    The starting time from which elapsed time is measured
 * @param[in,out] ElapsedTimeInOut  The accumulated elapsed time from the starting time reference
 * @param[in]     TimeoutTicks      The timeout limit (in ticks)
 */
boolean Power_Ip_TimeoutExpired(uint32 *StartTimeInOut,
                            uint32 *ElapsedTimeInOut,
                            uint32 TimeoutTicks);

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* POWER_IP_PRIVATE_H */

