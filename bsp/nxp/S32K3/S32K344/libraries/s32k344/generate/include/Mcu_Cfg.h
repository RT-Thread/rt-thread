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

#ifndef MCU_CFG_H
#define MCU_CFG_H

/**
*   @file       Mcu_Cfg.h
*   @implements Mcu_Cfg.h_Artifact
*   @version    5.0.0
*
*   @brief      AUTOSAR Mcu - Configuration file for the driver.
*   @details    Precompile parameters and extern configuration.
*
*   @addtogroup MCU
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

#include "Mcal.h"
#include "Clock_Ip_Cfg.h"
#include "Power_Ip_Cfg.h"
#include "Ram_Ip_Cfg.h"
#include "Mcu_PBcfg.h"

/*==================================================================================================
*                                  SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_CFG_VENDOR_ID                        43
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION         4
#define MCU_CFG_AR_RELEASE_MINOR_VERSION         7
#define MCU_CFG_AR_RELEASE_REVISION_VERSION      0
#define MCU_CFG_SW_MAJOR_VERSION                 5
#define MCU_CFG_SW_MINOR_VERSION                 0
#define MCU_CFG_SW_PATCH_VERSION                 0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if header file and Mcal.h header file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu_Cfg.h and Mcal.h are different"
#endif
#endif

/* Check if header file and Clock_Ip_Cfg.h file are of the same vendor */
#if (MCU_CFG_VENDOR_ID != CLOCK_IP_CFG_VENDOR_ID)
    #error "Mcu_Cfg.h and Clock_Ip_Cfg.h have different vendor ids"
#endif

/* Check if header file and Clock_Ip_Cfg.h file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION != CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION != CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION != CLOCK_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.h and Clock_Ip_Cfg.h are different"
#endif

/* Check if header file and Clock_Ip_Cfg.h file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION != CLOCK_IP_CFG_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION != CLOCK_IP_CFG_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION != CLOCK_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.h and Clock_Ip_Cfg.h are different"
#endif

/* Check if header file and Power_Ip_Cfg.h file are of the same vendor */
#if (MCU_CFG_VENDOR_ID != POWER_IP_CFG_VENDOR_ID)
    #error "Mcu_Cfg.h and Power_Ip_Cfg.h have different vendor ids"
#endif

/* Check if header file and Power_Ip_Cfg.h file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION != POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION != POWER_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION != POWER_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.h and Power_Ip_Cfg.h are different"
#endif

/* Check if header file and Power_Ip_Cfg.h file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION != POWER_IP_CFG_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION != POWER_IP_CFG_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION != POWER_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.h and Power_Ip_Cfg.h are different"
#endif

/* Check if header file and Ram_Ip_Cfg.h file are of the same vendor */
#if (MCU_CFG_VENDOR_ID != RAM_IP_CFG_VENDOR_ID)
    #error "Mcu_Cfg.h and Ram_Ip_Cfg.h have different vendor ids"
#endif

/* Check if header file and Ram_Ip_Cfg.h file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION != RAM_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION != RAM_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION != RAM_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.h and Ram_Ip_Cfg.h are different"
#endif

/* Check if header file and Ram_Ip_Cfg.h file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION != RAM_IP_CFG_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION != RAM_IP_CFG_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION != RAM_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.h and Ram_Ip_Cfg.h are different"
#endif

/* Check if header file and Mcu_PBcfg.h file are of the same vendor */
#if (MCU_CFG_VENDOR_ID != MCU_PBCFG_VENDOR_ID)
    #error "Mcu_Cfg.h and Mcu_PBcfg.h have different vendor ids"
#endif
/* Check if header file and Mcu_PBcfg.h file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION != MCU_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION != MCU_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION != MCU_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.h and Mcu_PBcfg.h are different"
#endif
/* Check if header file and Mcu_PBcfg.h file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION != MCU_PBCFG_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION != MCU_PBCFG_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION != MCU_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.h and Mcu_PBcfg.h are different"
#endif


/*==================================================================================================
*                                              CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                           DEFINES AND MACROS
==================================================================================================*/


/**
* @brief      Specifies the InstanceId of this module instance.
*/

#define MCU_INSTANCE_ID                 ((uint8)0x0U)

/**
@{
* @brief            Service Ids for MCU APIs.
*/


#define MCU_INIT_ID                     ((uint8)0x00U)

#define MCU_INITRAMSECTION_ID           ((uint8)0x01U)

#define MCU_INITCLOCK_ID                ((uint8)0x02U)

#define MCU_DISTRIBUTEPLLCLOCK_ID       ((uint8)0x03U)

#define MCU_GETPLLSTATUS_ID             ((uint8)0x04U)

#define MCU_GETRESETREASON_ID           ((uint8)0x05U)

#define MCU_GETRESETRAWVALUE_ID         ((uint8)0x06U)

#define MCU_PERFORMRESET_ID             ((uint8)0x07U)

#define MCU_SETMODE_ID                  ((uint8)0x08U)

#define MCU_GETVERSIONINFO_ID           ((uint8)0x09U)

#define MCU_GETRAMSTATE_ID              ((uint8)0x0AU)

/**@}*/


/**
@{
* @brief            Service Ids for NonASR MCU APIs.
*/


#define MCU_GETPOWERDOMAIN_ID           ((uint8)0x0BU)

#define MCU_GETPERIPHERALSTATE_ID       ((uint8)0x0CU)

#define MCU_GETSYSTEMSTATE_ID           ((uint8)0x0DU)

#define MCU_GETPOWERMODESTATE_ID        ((uint8)0x0EU)

#define MCU_GETMEMCONFIG_ID             ((uint8)0x13U)

#define MCU_GETMIDRSTRUCTURE_ID         ((uint8)0x14U)

#define MCU_SSCMGETSTATUS_ID            ((uint8)0x15U)

#define MCU_SSCMGETUOPT_ID              ((uint8)0x16U)

#define MCU_DISABLECMU_ID               ((uint8)0x17U)

#define MCU_EMIOSCONFIGUREGPREN_ID      ((uint8)0x18U)

#define MCU_GETCLOCKFREQUENCY_ID        ((uint8)0x19U)

#define MCU_SLEEPONEXIT_ID              ((uint8)0x1AU)

#define MCU_SRAMRETENCONFIG_ID          ((uint8)0x1BU)

#define MCU_PMCAECONFIG_ID              ((uint8)0x1CU)

#define MCU_AECRESETCONFIG_ID           ((uint8)0x1DU)

#define MCU_LASTMILEENABLE_ID           ((uint8)0x1EU)

#define MCU_LASTMILEDISABLE_ID          ((uint8)0x1FU)

/**@}*/


/**
* @brief            Pre-processor switch for enabling the default error detection and reporting to the DET.
*                   The detection of default errors is configurable (ON / OFF) at pre-compile time.
*/
#define MCU_DEV_ERROR_DETECT   (STD_OFF)
/**
* @brief            Pre-processor switch to enable/disable the API to read out the modules version information.
*/
#define MCU_VERSION_INFO_API   (STD_OFF)

/**
* @brief            Pre-processor switch to enable/disable the API Mcu_GetRamState.
*/
#define MCU_GET_RAM_STATE_API           (STD_OFF)

/**
* @brief            If this parameter is set to FALSE, the clock initialization has to be disabled from the MCU driver.
*/
#define MCU_INIT_CLOCK   (STD_ON)

/**
* @brief            This parameter shall be set True, if the H/W does not have a PLL or the PLL circuitry is enabled after the power on without S/W intervention.
*/
#define MCU_NO_PLL   (STD_ON)
/**
* @brief            Support for Low Power mode.
*/
#define MCU_ENTER_LOW_POWER_MODE           POWER_IP_ENTER_LOW_POWER_MODE

/**
* @brief            Pre-processor switch to enable/disable the API Mcu_PerformReset.
*/
#define MCU_PERFORM_RESET_API               POWER_IP_PERFORM_RESET_API

#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            The user callout reset is/is not available (STD_ON/STD_OFF) - called by MCU right before Mcu_PerformReset().
*/
#define MCU_RESET_CALLOUT_USED   (STD_OFF)
#endif



/**
* @brief            ISR Mcu_CmuClockFail_ISR is/is not available
*/
#define MCU_CMU_ERROR_ISR_USED            (STD_OFF)

/**
* @brief            ISR Mcu_CguClockDetect_ISR is/is not available
*/
#define MCU_CGU_DETECT_ISR_USED            (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetPeripheral_State() for getting infos about peripheral state from MC_ME module.
*/
#define MCU_GET_PERIPH_STATE_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetPowerMode_State() for getting infos system platform configuration.
*/
#define MCU_POWERMODE_STATE_API          (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetPowerDomain_Status. Get PMU state: operable or not.
*/
#define MCU_GET_POWER_DOMAIN_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetSystem_State() for getting system platform configuration information. Get (SSCM_STATUS | SSCM_MEMCONFIG).
*/
#define MCU_GET_SYSTEM_STATE_API  (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_SscmGetMemConfig(). Get SSCM_MEMCONFIG.
*/
#define MCU_GET_MEM_CONFIG_API  (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_SscmGetStatus(). Get SSCM_STATUS.
*/
#define MCU_SSCM_GET_STATUS_API  (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_SscmGetUopt(). Get SSCM_UOPT.
*/
#define MCU_SSCM_GET_UOPT_API     (STD_OFF)

/**
* @brief            Enable the call to "Mcu_Ipw_Sscm_Init()" inside "Mcu_Ipw_Init".
*/
#define MCU_SSCM_CHECK_SYSTEM_STATE (STD_OFF)
/**
* @brief            Enable the usage of Non-Autosar API  Mcu_GetMidrStructure(). Returns .
*/
#define MCU_GET_MIDR_API          (STD_OFF)
/**
* @brief            Enable the usage of Non-Autosar API  Mcu_EmiosConfigureGpren().
*/
#define MCU_EMIOS_CONFIGURE_GPREN_API        (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API  Mcu_Disable_CMU().
*/
#define MCU_DISABLE_CMU_API     (STD_ON)
/**
* @brief            Enable the usage of Non-Autosar API  Mcu_GetClockFrequency().
*/
#define MCU_GET_CLOCK_FREQUENCY_API     (STD_OFF)



/**
* @brief            Enable the usage of Non-Autosar API  Mcu_PmcAeConfig().
*/
#define MCU_PMCAECONFIG_API               POWER_IP_PMCAECONFIG_API

/**
* @brief            Enable the usage of Non-Autosar API  Mcu_AecResetConfig().
*/
#define MCU_AECRESETCONFIG_API               POWER_IP_AECRESETCONFIG_API

/**
* @brief            Enable/Disable the API for reporting the Dem Error.
*/

#define MCU_DISABLE_DEM_REPORT_ERROR_STATUS     (STD_ON)

/**
* @brief           Enable/Disable the Ram Notification.
*/
#define MCU_DISABLE_RAM_CONFIG         (STD_OFF)

/**
* @brief           Enable/Disable the Flash Notification.
*/
#define MCU_DISABLE_FLASH_CONFIG         (STD_OFF)


/**
* @brief           This define controls whether the MCU driver will configure and supervise the Application Extension Subsystem.
*/
#ifdef POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT
#define MCU_FUNCTIONAL_RESET_DISABLE_SUPPORT   (POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT)
#endif /* POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT */

/**
* @brief            Maximum number of MCU Clock configurations.
*/
#define MCU_MAX_CLKCONFIGS   ((uint32)1U)

/**
* @brief            Maximum number of MCU Mode configurations.
*/
#define MCU_MAX_MODECONFIGS   ((uint32)1U)

/**
* @brief            Maximum number of MCU Ram configurations.
*/
#define MCU_MAX_RAMCONFIGS   ((uint32)0U)
#define MCU_MAX_NORAMCONFIGS
/**
* @brief            Pre-compile Support.
*/
#define MCU_PRECOMPILE_SUPPORT (STD_ON)

#ifdef MCU_GET_MIDR_API
  #if (MCU_GET_MIDR_API == STD_ON)
/**
* @brief            Number of total available SIUL2 (SIUL2 + SIUL2_AE) units.
*/

#define MCU_SIUL2_TOTAL_UNITS                    ((uint8)1U)
  #endif
#endif


#ifdef MCU_ERROR_ISR_NOTIFICATION
/* This is used to clear CMU flags from the RGM interrupt */
#define MCU_CMU_CLEAR_CLOCK_IRQ_FLAG            (MCU_CMU_ERROR_ISR_USED)
#endif

#ifndef CLOCK_IP_DERIVATIVE_NOT_SUPPORT_USER_MODE
/**
* @brief        Support for User mode.
*               If this parameter has been configured to 'TRUE' the Mcu driver can be executed from both supervisor and user mode.
*/
#define MCU_ENABLE_USER_MODE_SUPPORT   (STD_OFF)

/** Check the driver user mode is enabled only when the MCAL_ENABLE_USER_MODE_SUPPORT is enabled */
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
  #if (MCU_ENABLE_USER_MODE_SUPPORT == STD_ON)
    #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Mcu in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
  #endif /* (MCU_ENABLE_USER_MODE_SUPPORT == STD_ON) */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

#endif /* CLOCK_IP_DERIVATIVE_NOT_SUPPORT_USER_MODE */

/**
* @brief           This define controls the availability of function Mcu_SleepOnExit
*/
#define MCU_SLEEPONEXIT_SUPPORT         (STD_ON)

/**
* @brief           This define controls the availability of function Mcu_LastMileEnable/Mcu_LastMileDisable
*/
#define MCU_LASTMILE_SUPPORT        (STD_ON)

/**
* @brief            This macro is used to define the position of the first reset reason.
*
*/
#define MCU_FIRST_RESET_REASON_POS_U32      ((uint32)MCU_POWER_ON_RESET)

#if (MCU_DEV_ERROR_DETECT == STD_ON)
/**
@{
* @brief            Default error values are of type uint8.
*                   The following errors and exceptions shall be detectable by the MCU module depending on its
*                   build version (Default/production mode).
*
*/

#define MCU_E_PARAM_CONFIG              ((uint8)0x0AU)

#if (MCU_INIT_CLOCK == STD_ON)
    #define MCU_E_PARAM_CLOCK               ((uint8)0x0BU)
#endif

#define MCU_E_PARAM_MODE                ((uint8)0x0CU)

#ifndef MCU_MAX_NORAMCONFIGS
    #define MCU_E_PARAM_RAMSECTION          ((uint8)0x0DU)
#endif

#if (MCU_INIT_CLOCK == STD_ON) && (MCU_NO_PLL == STD_OFF)
    #define MCU_E_PLL_NOT_LOCKED            ((uint8)0x0EU)
#endif

#define MCU_E_UNINIT                    ((uint8)0x0FU)

#if (MCU_VERSION_INFO_API == STD_ON) || (MCU_GET_MIDR_API == STD_ON)
    #define MCU_E_PARAM_POINTER             ((uint8)0x10U)
#endif

#define MCU_E_INIT_FAILED               ((uint8)0x11U)
#define MCU_E_ALREADY_INITIALIZED       ((uint8)0x13U)

#if (MCU_DISABLE_CMU_API == STD_ON)
    #define MCU_E_CMU_INDEX_OUT_OF_RANGE    ((uint8)0x22U)
#endif

/**@}*/
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

/**
* @brief  The function Mcu_GetResetRawValue shall return an implementation specific value which does
*         not correspond to a valid value of the reset status register and is not equal to 0 if this
*         function is called prior to calling of the function Mcu_Init, and if supported by the
*         hardware.
*
*/
#define MCU_RAW_RESET_DEFAULT      ((uint32)0xFFFFFFFFUL)

#ifdef MCU_ERROR_ISR_NOTIFICATION
/**
@{
* @brief            Error ISR values are of type uint8.
*                   The following error codes are reported by the error ISR.
*/
#if (MCU_CMU_ERROR_ISR_USED == STD_ON)
    #define MCU_E_ISR_CLOCK_FAILURE                 ((uint8)0x01U)
#endif

#endif /* MCU_ERROR_ISR_NOTIFICATION */
/**
@{
* @brief            Macro parameter input of function mcu_emiosconfiguregpren().
*/
#ifdef MCU_EMIOS_CONFIGURE_GPREN_API
#if (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON)

#ifdef IP_EMIOS_0_BASE
#define MCU_EMIOS_MODULE_0 (0x00U)
#endif
#ifdef IP_EMIOS_1_BASE
#define MCU_EMIOS_MODULE_1 (0x01U)
#endif
#ifdef IP_EMIOS_2_BASE
#define MCU_EMIOS_MODULE_2 (0x02U)
#endif

#define MCU_EMIOS_GPREN_BIT_ENABLE (0x01U)
#define MCU_EMIOS_GPREN_BIT_DISABLE (0x00U)
#define MCU_EMIOS_MCR_GPREN_MASK32 eMIOS_MCR_GPREN_MASK
#endif
#endif




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            Create defines with the IDs assigned to Mcu Clock configurations.
*                   These IDs will be transmitted as input parameters for Mcu_InitClock() API.
*/


#define McuClockSettingConfig_0      ((Mcu_ClockType)0U)

#define McuConf_McuClockSettingConfig_McuClockSettingConfig_0      ((Mcu_ClockType)0U)

#endif

/**
* @brief            Create defines with the IDs assigned to Mcu Mode configurations.
*                   These IDs will be transmitted as input parameters for Mcu_SetMode() API.
*/

#define McuModeSettingConf_0      ((Mcu_ModeType)0U)

#define McuConf_McuModeSettingConf_McuModeSettingConf_0      ((Mcu_ModeType)0U)


/**
* @brief            Create defines with the IDs assigned to Mcu RAM Section configurations.
*                   These IDs will be transmitted as input parameters for Mcu_InitRamSection() API.
*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/**
* @brief            Type of the return value of the function Mcu_GetPllStatus.
* @details          The type of Mcu_PllStatusType is an enumeration with the following values:
*                       MCU_PLL_LOCKED, MCU_PLL_UNLOCKED, MCU_PLL_STATUS_UNDEFINED.
*
* @implements     Mcu_PllStatusType_Enumeration
*
*/
typedef enum
{
    MCU_PLL_LOCKED = 0x00U,            /**< @brief PLL is locked.         */
    MCU_PLL_UNLOCKED = 0x01U,          /**< @brief PLL is unlocked.       */
    MCU_PLL_STATUS_UNDEFINED = 0x02U   /**< @brief PLL Status is unknown. */

} Mcu_PllStatusType;


/**
* @brief            The type Mcu_ResetType, represents the different reset that a specified MCU can have.
* @details          The MCU module shall provide at least the values MCU_POWER_ON_RESET and MCU_RESET_UNDEFINED for the enumeration Mcu_ResetType.
*
* @implements Mcu_ResetType_Enumeration
*/
typedef Power_Ip_ResetType Mcu_ResetType;



#if (MCU_GET_RAM_STATE_API == STD_ON)
/**
* @brief            Ram State of the microcontroller.
* @details          This is the Ram State data type returned by the function Mcu_GetRamState() of the Mcu module.
* @implements Mcu_RamStateType_Enumeration
*/
typedef enum
{
    MCU_RAMSTATE_INVALID = 0x00U,   /**< @brief RAM content is not valid or unknown (default). */
    MCU_RAMSTATE_VALID   = 0x01U    /**< @brief RAM content is valid. */

} Mcu_RamStateType;
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

#ifdef MCU_PREPARE_MEMORY_CONFIG
/**
* @brief            The stage of the flash and ram controllers configuration.
* @details          This is used to specify the entry and exit point of the flash and ram controllers configuration.
*/
typedef enum
{
    MCU_RAM_MEMORY_CONFIG_ENTRY_POINT      = 0x77U,
    MCU_RAM_MEMORY_CONFIG_EXIT_POINT       = 0x88U,
    MCU_FLASH_MEMORY_CONFIG_ENTRY_POINT    = 0x89U,
    MCU_FLASH_MEMORY_CONFIG_EXIT_POINT     = 0x90U

} Mcu_MemoryConfigStageType;
#endif

#if (defined(MCU_PMC_NOTIFICATION) && (MCU_ENTER_LOW_POWER_MODE == STD_ON))
/**
* @brief            Power management controller events.
* @details          The various events triggered by the power management controller.
*/
typedef enum
{
    MCU_LAST_MILE_REGULATOR_DISABLED = 0x55U

} Mcu_PowerManagementEventType;
#endif

#ifdef MCU_SLEEPONEXIT_SUPPORT
  #if (MCU_SLEEPONEXIT_SUPPORT == STD_ON)
typedef enum
{
    MCU_SLEEP_ON_EXIT_DISABLED = 0U,   /**< @brief Disable SLEEPONEXIT bit (default). */
    MCU_SLEEP_ON_EXIT_ENABLED   /**< @brief Enable SLEEPONEXIT bit. */

} Mcu_SleepOnExitType;
  #endif
#endif

#ifdef MCU_SRAM_RETEN_CONFIG_API
#if (MCU_SRAM_RETEN_CONFIG_API == STD_ON)
/**
* @brief            Type of parameter value of the function Mcu_SRAMRetentionConfig.
* @details          The type of Mcu_SRAMRetenConfigType is an enumeration with the following values:
*                       MCU_SRAML_RETEN, MCU_SRAMU_RETEN, MCU_SRAMLU_RETEN, MCU_NO_SRAMLU_RETEN.
*/
typedef Power_Ip_SRAMRetenConfigType Mcu_SRAMRetenConfigType;
#endif
#endif

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            The Mcu_ModeType specifies the identification (ID) for a MCU mode, configured via configuration structure.
* @details          The type shall be uint8, uint16 or uint32.
*
* @implements     Mcu_ModeType_typedef
*
*/
typedef uint32 Mcu_ModeType;

/**
* @brief            The Mcu_RamSectionType specifies the identification (ID) for a RAM section, configured via the configuration structure.
*                   The type shall be uint8, uint16 or uint32, based on best performance.
* @implements Mcu_RamSectionType_typedef
*/
typedef uint32 Mcu_RamSectionType;

#ifndef MCU_MAX_NORAMCONFIGS
#if (MCU_DEV_ERROR_DETECT == STD_ON)
/**
* @brief            The Mcu_RamWriteSizeType specifies the RAM section write size.
*                   The type shall be uint8, uint16 or uint32, based on best performance.
*
*/
typedef uint32 Mcu_RamWriteSizeType;
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
#endif /* ifndef MCU_MAX_NORAMCONFIGS */


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief          Defines the identification (ID) for clock setting configured via the configuration structure.
* @details        The type shall be uint8, uint16 or uint32, depending on uC platform.
*
* @implements Mcu_ClockType_typedef
*/
typedef uint32 Mcu_ClockType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/**
* @brief            The type Mcu_RawResetType specifies the reset reason in raw register format, read from a reset status register.
* @details          The type shall be uint8, uint16 or uint32 based on best performance.
*
* @implements Mcu_RawResetType_typedef
*
*/
typedef uint32 Mcu_RawResetType;   /**< @brief Destructive and Functional Reset Events Log. */


#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief            DEM error reporting configuration.
* @details          This structure contains information DEM error reporting
*/
typedef struct
{
    Mcal_DemErrorType ErrorTimeoutFailureCfg;
    Mcal_DemErrorType ErrorInvalidFxoscConfigCfg;
    Mcal_DemErrorType ErrorClockMuxSwitchFailureCfg;
    Mcal_DemErrorType ErrorClockFailureCfg;
    Mcal_DemErrorType ErrorSwitchModeFailureCfg;
#ifdef MCU_SSCM_CHECK_SYSTEM_STATE
  #if (MCU_SSCM_CHECK_SYSTEM_STATE == STD_ON)
    Mcal_DemErrorType ErrorSscmCerFailureCfg;
  #endif /* (MCU_SSCM_CHECK_SYSTEM_STATE == STD_ON) */
#endif /* MCU_SSCM_CHECK_SYSTEM_STATE */
} Mcu_DemConfigType;
#endif

#if (MCU_POWERMODE_STATE_API == STD_ON)
/**
* @brief            State of the current power mode.
* @details          Used to store the value of register value.
*/
typedef uint32 Mcu_PowerModeStateType;
#endif /* (MCU_POWERMODE_STATE_API == STD_ON) */


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"

/**
* @brief            Local copy of the pointer to the configuration data
*/
extern const Mcu_DemConfigType * Mcu_pDemCfgPtr;

#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"


#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Mcu_MemMap.h"

extern const Mcu_DemConfigType Mcu_DemConfig;

#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "Mcu_MemMap.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"




#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* #ifndef MCU_CFG_H */



