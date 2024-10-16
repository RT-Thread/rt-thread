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
*   @file       Mcu_PBcfg.c
*   @implements Mcu_PBcfg.c_Artifact
*   @version    5.0.0
*
*   @brief      AUTOSAR Mcu - Data structures for the Mcu driver.
*   @details    Postbuild structure configurations for the driver initalization.
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
#define MCU_PBCFG_VENDOR_ID_C                     43
#define MCU_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define MCU_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define MCU_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define MCU_PBCFG_SW_MAJOR_VERSION_C              5
#define MCU_PBCFG_SW_MINOR_VERSION_C              0
#define MCU_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Mcu.h file are of the same vendor */
#if (MCU_PBCFG_VENDOR_ID_C != MCU_VENDOR_ID)
    #error "Mcu_PBcfg.c and Mcu.h have different vendor ids"
#endif
/* Check if source file and Mcu.h file are of the same Autosar version */
#if ((MCU_PBCFG_AR_RELEASE_MAJOR_VERSION_C != MCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_PBCFG_AR_RELEASE_MINOR_VERSION_C != MCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_PBCFG_AR_RELEASE_REVISION_VERSION_C != MCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_PBcfg.c and Mcu.h are different"
#endif
/* Check if source file and Mcu.h file are of the same Software version */
#if ((MCU_PBCFG_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
     (MCU_PBCFG_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
     (MCU_PBCFG_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_PBcfg.c and Mcu.h are different"
#endif

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Dem.h file are of the same Autosar version */
    #if ((MCU_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
        (MCU_PBCFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_PBcfg.c and Dem.h are different"
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

/**
* @brief          Initialization data for the MCU driver.
* @details        A pointer to such a structure is provided to the MCU initialization routines for configuration.
*
*/
const Mcu_ConfigType Mcu_PreCompileConfig=
{
#if (MCU_INIT_CLOCK == STD_ON)
    /* Globally enable/disable SCM, loss of clock and loss of lock notification. */
    MCU_CLK_NOTIF_DIS,
#endif
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Pointer to DEM error reporting configurations. */
    &Mcu_DemConfig,
#endif
    /* Number of RAM Sections configurations. */
    (Mcu_RamSectionType)0U,

    /* Number of Power Modes configurations. */
    (Mcu_ModeType)1U,

#if (MCU_INIT_CLOCK == STD_ON)
    /* Number of Clock Setting configurations. */
    (Mcu_ClockType)1U,
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#ifndef MCU_MAX_NORAMCONFIGS
    /* Pointer to RAM Section configurations. */
    (NULL_PTR),
#endif

    /* Pointer to Power Mode configurations. */
    &Power_Ip_aModeConfigPB,

#if (MCU_INIT_CLOCK == STD_ON)
    /* Pointer to Clock configurations. */
    &Mcu_aClockConfigPB,

#endif /* (MCU_INIT_CLOCK == STD_ON) */
    /* Pointer to Low Level Mcu driver configuration. */
    &Power_Ip_HwIPsConfigPB
};


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


