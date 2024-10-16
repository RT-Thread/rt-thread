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

#ifndef MCU_DEM_WRAPPER_H
#define MCU_DEM_WRAPPER_H

/**
*   @file    Mcu_Mcu_Dem_Wrapper.h
*   @version    5.0.0
*
*   @brief      AUTOSAR Mcu - Convenience macros for DEM.
*   @details    Contains convenience macros for DEM calls to reduce code clutter in IPs.

*   @addtogroup MCU_DRIVER Mcu Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif



/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu_Cfg.h"

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
  #include "Dem.h"
#endif

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_DEM_WRAPPER_VENDOR_ID                       43
#define MCU_DEM_WRAPPER_AR_RELEASE_MAJOR_VERSION        4
#define MCU_DEM_WRAPPER_AR_RELEASE_MINOR_VERSION        7
#define MCU_DEM_WRAPPER_AR_RELEASE_REVISION_VERSION     0
#define MCU_DEM_WRAPPER_SW_MAJOR_VERSION                5
#define MCU_DEM_WRAPPER_SW_MINOR_VERSION                0
#define MCU_DEM_WRAPPER_SW_PATCH_VERSION                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Mcu_Cfg.h file are of the same vendor */
#if (MCU_DEM_WRAPPER_VENDOR_ID != MCU_CFG_VENDOR_ID)
    #error "Mcu_Dem_Wrapper.h and Mcu_Cfg.h have different vendor ids"
#endif

/* Check if header file and Mcu_Cfg.h file are of the same Autosar version */
#if ((MCU_DEM_WRAPPER_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_DEM_WRAPPER_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_DEM_WRAPPER_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Dem_Wrapper.h and Mcu_Cfg.h are different"
#endif

/* Check if header file and Mcu_Cfg.h file are of the same Software version */
#if ((MCU_DEM_WRAPPER_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION) || \
     (MCU_DEM_WRAPPER_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION) || \
     (MCU_DEM_WRAPPER_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Dem_Wrapper.h and Mcu_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/* Check if header file and Dem.h file are of the same Autosar version */
#if ((MCU_DEM_WRAPPER_AR_RELEASE_MAJOR_VERSION != DEM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_DEM_WRAPPER_AR_RELEASE_MINOR_VERSION != DEM_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu_Dem_Wrapper.h and Dem.h are different"
#endif
#endif
#endif
/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    #define Mcu_Macro_ReportDemTimeoutError()  (Mcu_ReportDemTimeoutError())
    #define Mcu_Macro_ReportDemFxoscConfigurationError() (Mcu_ReportDemFxoscError())
    #define Mcu_Macro_ReportDemClockMuxSwitchError()     (Mcu_ReportDemClockMuxSwitchError())
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

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
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
 /*!
 * @brief    Reports timeout error to DEM.
 *
 * Checks if the timeout expired and reports the timeout error to DEM if that is the case.
 *
 * @param[in]  u32Timeout  Maximum timeout to be waited.
 *
 * @return     void.
 */
void Mcu_ReportDemTimeoutError(void);

 /*!
 * @brief    Reports incorrect FXOSC configuration to DEM.
 *
 * Directly reports the FXOSC configuration error to DEM.
 *
 * @param[in]  void.
 *
 * @return     void.
 */
void Mcu_ReportDemFxoscError(void);

 /*!
 * @brief    Reports failed clock multiplexer switch to DEM.
 *
 * Directly reports the clock multiplexer switch error to DEM.
 *
 * @param[in]  void.
 *
 * @return     void.
 */
void Mcu_ReportDemClockMuxSwitchError(void);

#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* MCU_DEM_WRAPPER_H */

