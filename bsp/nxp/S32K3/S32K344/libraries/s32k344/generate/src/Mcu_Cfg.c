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
*   @file       Mcu_Cfg.c
*   @implements Mcu_Cfg.c_Artifact
*   @version    5.0.0
*
*   @brief      AUTOSAR Mcu - Data structures for the Mcu driver.
*   @details    Precompile structure configuration for the driver initialization.
*
*   @addtogroup MCU
*   @{
*/


#ifdef __cplusplus
extern "C"
{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu.h"

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_CFG_VENDOR_ID_C                       43
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION_C        4
#define MCU_CFG_AR_RELEASE_MINOR_VERSION_C        7
#define MCU_CFG_AR_RELEASE_REVISION_VERSION_C     0
#define MCU_CFG_SW_MAJOR_VERSION_C                5
#define MCU_CFG_SW_MINOR_VERSION_C                0
#define MCU_CFG_SW_PATCH_VERSION_C                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Mcu.h file are of the same vendor */
#if (MCU_CFG_VENDOR_ID_C != MCU_VENDOR_ID)
    #error "Mcu_Cfg.c and Mcu.h have different vendor ids"
#endif
/* Check if source file and Mcu.h file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION_C != MCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION_C != MCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION_C != MCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.c and Mcu.h are different"
#endif
/* Check if source file and Mcu.h file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.c and Mcu.h are different"
#endif

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Dem.h file are of the same Autosar version */
    #if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
        (MCU_CFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_Cfg.c and Dem.h are different"
    #endif

    #endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Mcu_MemMap.h"

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
const Mcu_DemConfigType Mcu_DemConfig =
{
    /* DEM error reporting MCU_E_TIMEOUT_FAILURE */
    {(uint32)STD_OFF, 0U},
    /* DEM error reporting MCU_E_INVALIDFXOSC_CONFIG */
    {(uint32)STD_OFF, 0U},
    /* DEM error reporting MCU_E_CLOCKMUXSWITCH_FAILURE */
    {(uint32)STD_OFF, 0U},
    /* DEM error reporting MCU_E_CLOCK_FAILURE */
    {(uint32)STD_OFF, 0U},
    /* DEM error reporting MCU_E_SWITCHMODE_FAILURE */
    {(uint32)STD_OFF, 0U}
};
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */


#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "Mcu_MemMap.h"


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


