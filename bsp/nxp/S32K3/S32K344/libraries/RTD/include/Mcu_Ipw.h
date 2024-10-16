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

#ifndef MCU_IPW_H
#define MCU_IPW_H

/**
*   @file    Mcu_Ipw.h
*   @implements Mcu_Ipw.h_Artifact
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Mcu driver header file.
*   @details AUTOSAR specific Mcu driver header file.

*   @addtogroup MCU_DRIVER Mcu Driver
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
#include "Mcu_Ipw_Types.h"
#include "Mcu_EnvCfg.h"
#include "Mcal.h"

/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_IPW_VENDOR_ID                     43
#define MCU_IPW_AR_RELEASE_MAJOR_VERSION      4
#define MCU_IPW_AR_RELEASE_MINOR_VERSION      7
#define MCU_IPW_AR_RELEASE_REVISION_VERSION   0
#define MCU_IPW_SW_MAJOR_VERSION              5
#define MCU_IPW_SW_MINOR_VERSION              0
#define MCU_IPW_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Mcu_Ipw.h file and Mcu_Ipw_Types.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID != MCU_IPW_TYPES_VENDOR_ID)
    #error "Mcu_Ipw.h and Mcu_Ipw_Types.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.h file and Mcu_Ipw_Types.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION != MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION != MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION != MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.h and Mcu_Ipw_Types.h are different"
#endif

/* Check if Mcu_Ipw.h file and Mcu_Ipw_Types.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION != MCU_IPW_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION != MCU_IPW_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION != MCU_IPW_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.h and Mcu_Ipw_Types.h are different"
#endif

/* Check if Mcu_Ipw.h file and Mcu_EnvCfg.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID != MCU_ENVCFG_VENDOR_ID)
    #error "Mcu_Ipw.h and Mcu_EnvCfg.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.h file and Mcu_EnvCfg.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION != MCU_ENVCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION != MCU_ENVCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION != MCU_ENVCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.h and Mcu_EnvCfg.h are different"
#endif

/* Check if Mcu_Ipw.h file and Mcu_EnvCfg.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION != MCU_ENVCFG_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION != MCU_ENVCFG_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION != MCU_ENVCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.h and Mcu_EnvCfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Mcu_Ipw.h file and Mcal.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu_Ipw.h and Mcal.h are different"
#endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#if (MCU_INIT_CLOCK == STD_ON)
void Mcu_ClkSrcFailureNotification(Clock_Ip_NameType ClockName);
#endif /* (MCU_INIT_CLOCK == STD_ON) */

void Mcu_Ipw_Init(const Mcu_HwIPsConfigType * HwIPsConfigPtr);

void Mcu_Ipw_SetMode(const Mcu_ModeConfigType * ModeConfigPtr);

#ifndef MCU_MAX_NORAMCONFIGS
Std_ReturnType Mcu_Ipw_InitRamSection(const Mcu_RamConfigType * RamConfigPtr);
#endif /* ifndef MCU_MAX_NORAMCONFIGS */

#if (MCU_INIT_CLOCK == STD_ON)
void Mcu_Ipw_InitClock(const Mcu_ClockConfigType * ClockConfigPtr);
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#if (MCU_INIT_CLOCK == STD_ON)
    #if (MCU_NO_PLL == STD_OFF)
void Mcu_Ipw_DistributePllClock(void);
    #endif /* (MCU_NO_PLL == STD_OFF) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#if (MCU_NO_PLL == STD_OFF)
Mcu_PllStatusType Mcu_Ipw_GetPllStatus(void);
#endif /* (MCU_NO_PLL == STD_OFF) */

#if MCU_PERFORM_RESET_API == STD_ON
void Mcu_Ipw_PerformReset(const Mcu_HwIPsConfigType * HwIPsConfigPtr);
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

Mcu_ResetType Mcu_Ipw_GetResetReason(void);

Mcu_RawResetType Mcu_Ipw_GetResetRawValue(void);

#if (MCU_GET_RAM_STATE_API == STD_ON)
Mcu_RamStateType Mcu_Ipw_GetRamState(void);
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

#if (MCU_GET_MIDR_API == STD_ON)
void Mcu_Ipw_GetMidrStructure(Mcu_MidrReturnType * MidrPtr);
#endif /*(MCU_GET_MIDR_API == STD_ON)*/

#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
void Mcu_Ipw_DisableCmu(Clock_Ip_NameType ClockName);
#endif
#endif

#ifdef MCU_EMIOS_CONFIGURE_GPREN_API
#if (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON)
void Mcu_Ipw_EmiosConfigureGpren(uint8 Module, uint8 Value);
#endif
#endif

#ifdef MCU_GET_CLOCK_FREQUENCY_API
#if (MCU_GET_CLOCK_FREQUENCY_API == STD_ON)
uint64 MCU_Ipw_GetClockFrequency(Clock_Ip_NameType ClockName);
#endif /* (MCU_GET_CLOCK_FREQUENCY_API == STD_ON) */
#endif /* MCU_GET_CLOCK_FREQUENCY_API */


#ifdef MCU_SLEEPONEXIT_SUPPORT
  #if (MCU_SLEEPONEXIT_SUPPORT == STD_ON)
void Mcu_Ipw_SleepOnExit(Mcu_SleepOnExitType SleepOnExit);
  #endif
#endif

#ifdef MCU_PMCAECONFIG_API
#if (MCU_PMCAECONFIG_API == STD_ON)
void Mcu_Ipw_PmcAeConfig(const Mcu_HwIPsConfigType * HwIPsConfigPtr);
#endif /* (MCU_PMCAECONFIG_API == STD_ON) */
#endif

#ifdef MCU_AECRESETCONFIG_API
#if (MCU_AECRESETCONFIG_API == STD_ON)
void Mcu_Ipw_AecResetConfig(const Mcu_HwIPsConfigType * HwIPsConfigPtr);
#endif /* (MCU_AECRESETCONFIG_API == STD_ON) */
#endif

#ifdef MCU_LASTMILE_SUPPORT
  #if (STD_ON == MCU_LASTMILE_SUPPORT)
void Mcu_Ipw_LastMileDisable(void);
void Mcu_Ipw_LastMileEnable(boolean BJTused);
  #endif
#endif

#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* MCU_IPW_H */

