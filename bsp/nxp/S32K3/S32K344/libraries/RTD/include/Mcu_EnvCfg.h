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

#ifndef MCU_ENVCFG_H
#define MCU_ENVCFG_H

/**
*   @file    Mcu_EnvCfg.h
*   @version    5.0.0
*
*   @brief      AUTOSAR Mcu - Driver external interface.
*   @details    Contains all the public functions and data types that are used by the higher layer.

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

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_ENVCFG_VENDOR_ID                       43
#define MCU_ENVCFG_AR_RELEASE_MAJOR_VERSION        4
#define MCU_ENVCFG_AR_RELEASE_MINOR_VERSION        7
#define MCU_ENVCFG_AR_RELEASE_REVISION_VERSION     0
#define MCU_ENVCFG_SW_MAJOR_VERSION                5
#define MCU_ENVCFG_SW_MINOR_VERSION                0
#define MCU_ENVCFG_SW_PATCH_VERSION                0

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/


/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define MCU_PARAM_CHECK                 (MCU_DEV_ERROR_DETECT)

#if (MCU_PARAM_CHECK != MCU_DEV_ERROR_DETECT)
    #error "Cannot disable parameter check (MCU_PARAM_CHECK) when development error detection is enabled (MCU_DEV_ERROR_DETECT) as per [SWS_BSW_00042]"
#endif

/* high level defines */
#define MCU_VALIDATE_GLOBAL_CALL        (MCU_DEV_ERROR_DETECT)

#if (MCU_VALIDATE_GLOBAL_CALL != MCU_DEV_ERROR_DETECT)
    #error "Cannot disable API validation (MCU_VALIDATE_GLOBAL_CALL) when development error detection is enabled (MCU_DEV_ERROR_DETECT) as per [SWS_BSW_00042]"
#endif


#define MCU_PARAM_UNUSED(param)         ((void)((param)))

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

/** @} */
#endif /* MCU_ENVCFG_H */

