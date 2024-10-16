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

#ifndef RAM_IP_H
#define RAM_IP_H

/**
*   @file       Ram_Ip.h
*   @version    5.0.0
*
*   @brief   RAM IP driver header file.
*   @details RAM IP driver header file.
*
*   @addtogroup RAM_DRIVER Ram Ip Driver
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
#include "Ram_Ip_Types.h"
#include "Ram_Ip_Cfg.h"

#ifdef RAM_IP_DEV_ERROR_DETECT
#if (STD_ON == RAM_IP_DEV_ERROR_DETECT)
    #include "Devassert.h"
#endif /* (STD_ON == RAM_IP_DEV_ERROR_DETECT) */
#endif /* #ifdef RAM_IP_DEV_ERROR_DETECT */
/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RAM_IP_VENDOR_ID                     43
#define RAM_IP_AR_RELEASE_MAJOR_VERSION      4
#define RAM_IP_AR_RELEASE_MINOR_VERSION      7
#define RAM_IP_AR_RELEASE_REVISION_VERSION   0
#define RAM_IP_SW_MAJOR_VERSION              5
#define RAM_IP_SW_MINOR_VERSION              0
#define RAM_IP_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((RAM_IP_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Ram_Ip.h  and Std_Types.h are different"
#endif
#endif

/* Check if Ram_Ip.h file and Ram_Ip_Types.h file are of the same vendor */
#if (RAM_IP_VENDOR_ID != RAM_IP_TYPES_VENDOR_ID)
    #error "Ram_Ip.h and Ram_Ip_Types.h have different vendor ids"
#endif

/* Check if Ram_Ip.h file and Ram_Ip_Types.h file are of the same Autosar version */
#if ((RAM_IP_AR_RELEASE_MAJOR_VERSION != RAM_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_AR_RELEASE_MINOR_VERSION != RAM_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (RAM_IP_AR_RELEASE_REVISION_VERSION != RAM_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Ram_Ip.h and Ram_Ip_Types.h are different"
#endif

/* Check if Ram_Ip.h file and Ram_Ip_Types.h file are of the same Software version */
#if ((RAM_IP_SW_MAJOR_VERSION != RAM_IP_TYPES_SW_MAJOR_VERSION) || \
     (RAM_IP_SW_MINOR_VERSION != RAM_IP_TYPES_SW_MINOR_VERSION) || \
     (RAM_IP_SW_PATCH_VERSION != RAM_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Ram_Ip.h and Ram_Ip_Types.h are different"
#endif

/* Check if Ram_Ip.h file and Ram_Ip_Cfg.h file are of the same vendor */
#if (RAM_IP_VENDOR_ID != RAM_IP_CFG_VENDOR_ID)
    #error "Ram_Ip.h and Ram_Ip_Cfg.h have different vendor ids"
#endif

/* Check if Ram_Ip.h file and Ram_Ip_Cfg.h file are of the same Autosar version */
#if ((RAM_IP_AR_RELEASE_MAJOR_VERSION != RAM_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_AR_RELEASE_MINOR_VERSION != RAM_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (RAM_IP_AR_RELEASE_REVISION_VERSION != RAM_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Ram_Ip.h and Ram_Ip_Cfg.h are different"
#endif

/* Check if Ram_Ip.h file and Ram_Ip_Cfg.h file are of the same Software version */
#if ((RAM_IP_SW_MAJOR_VERSION != RAM_IP_CFG_SW_MAJOR_VERSION) || \
     (RAM_IP_SW_MINOR_VERSION != RAM_IP_CFG_SW_MINOR_VERSION) || \
     (RAM_IP_SW_PATCH_VERSION != RAM_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Ram_Ip.h and Ram_Ip_Cfg.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#ifdef RAM_IP_DEV_ERROR_DETECT
#if (STD_ON == RAM_IP_DEV_ERROR_DETECT)
/* Check if Ram_Ip.h file and Devassert.h file are of the same Autosar version */
#if ((RAM_IP_AR_RELEASE_MAJOR_VERSION    != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_AR_RELEASE_MINOR_VERSION    != DEVASSERT_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Ram_Ip.h and Devassert.h are different"
#endif
#endif /* (STD_ON == RAM_IP_DEV_ERROR_DETECT) */
#endif /* (RAM_IP_DEV_ERROR_DETECT) */
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#ifdef RAM_IP_DEV_ERROR_DETECT
  #if (STD_ON == RAM_IP_DEV_ERROR_DETECT)
    #define RAM_IP_DEV_ASSERT(x)      DevAssert(x)
  #else
    #define RAM_IP_DEV_ASSERT(x)
  #endif
#else
    #define RAM_IP_DEV_ASSERT(x)
#endif
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
 * @brief Initializes RAM section
 *
 * This function initializes RAM section.
 *
 * @param[in] RamConfigPtr  Ram section configuration.
 *
 * @return Ram_Ip_StatusType  Ram status
 */
Ram_Ip_StatusType Ram_Ip_InitRamSection(const Ram_Ip_RamConfigType * RamConfigPtr);

#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
/*!
 * @brief Returns RAM state
 *
 * This function returns RAM section.
 *
 * @return Ram_Ip_RamStateType  Ram state
 */
Ram_Ip_RamStateType Ram_Ip_GetRamState(void);
#endif

#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
 /*!
 * @brief           Install report error callback.
 * This function installs a callback for reporting errors from Ram driver.
 *
 * @param[in]        ReportErrorsCallback    Callback to be installed.
 *
 * @return           void
 */
void Ram_Ip_InstallNotificationsCallback(Ram_Ip_ReportErrorsCallbackType ReportErrorsCallback);
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* RAM_IP_H */


