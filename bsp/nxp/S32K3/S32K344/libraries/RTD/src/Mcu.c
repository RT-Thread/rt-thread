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
*   @file       Mcu.c
*   @implements Mcu.c_Artifact
*   @version    5.0.0
*
*   @brief      AUTOSAR Mcu - Implements the AUTOSAR MCU driver functionality.
*   @details    Implements the AUTOSAR MCU driver. All the API functions are described by AUTOSAR
*
*   @addtogroup MCU_DRIVER Mcu Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"

/**
* @brief Mcu.c shall include Mcu.h
*/
#include "Mcu.h"

/* Get the prototypes of IPW functions. */
#include "Mcu_Ipw.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_VENDOR_ID_C                      43
#define MCU_AR_RELEASE_MAJOR_VERSION_C       4
#define MCU_AR_RELEASE_MINOR_VERSION_C       7
#define MCU_AR_RELEASE_REVISION_VERSION_C    0
#define MCU_SW_MAJOR_VERSION_C               5
#define MCU_SW_MINOR_VERSION_C               0
#define MCU_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Mcu.c file and Det.h file are of the same Autosar version */
#if ((MCU_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu.c and Det.h are different"
#endif
#endif
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Mcu.c file and Mcal.h file are of the same Autosar version */
#if ((MCU_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu.c and Mcal.h are different"
#endif
#endif

/* Check if Mcu.c file and Mcu.h file are of the same vendor */
#if (MCU_VENDOR_ID_C != MCU_VENDOR_ID)
    #error "Mcu.c and Mcu.h have different vendor ids"
#endif

/* Check if Mcu.c file and Mcu.h file are of the same Autosar version */
#if ((MCU_AR_RELEASE_MAJOR_VERSION_C != MCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_AR_RELEASE_MINOR_VERSION_C != MCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_AR_RELEASE_REVISION_VERSION_C != MCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu.c and Mcu.h are different"
#endif

/* Check if Mcu.c file and Mcu.h file are of the same Software version */
#if ((MCU_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu.c and Mcu.h are different"
#endif

/* Check if Mcu.c file and Mcu_Ipw.h file are of the same vendor */
#if (MCU_VENDOR_ID_C != MCU_IPW_VENDOR_ID)
    #error "Mcu.c and Mcu_Ipw.h have different vendor ids"
#endif

/* Check if Mcu.c file and Mcu_Ipw.h file are of the same Autosar version */
#if ((MCU_AR_RELEASE_MAJOR_VERSION_C != MCU_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_AR_RELEASE_MINOR_VERSION_C != MCU_IPW_AR_RELEASE_MINOR_VERSION) || \
     (MCU_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu.c and Mcu_Ipw.h are different"
#endif

/* Check if Mcu.c file and Mcu_Ipw.h file are of the same Software version */
#if ((MCU_SW_MAJOR_VERSION_C != MCU_IPW_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_C != MCU_IPW_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_C != MCU_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu.c and Mcu_Ipw.h are different"
#endif
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
* @brief  This enumerated type contains the Mcu driver's possible states.
*/
typedef enum
{
    MCU_UNINIT = 0x3U,  /**< @brief The Mcu driver is uninitialized.         */
    MCU_IDLE   = 0xCU,  /**< @brief = 0xE1 The Mcu driver is currently idle. */
    MCU_BUSY   = 0xAU   /**< @brief = 0xD2 The Mcu driver is currently busy. */

} Mcu_StatusType;


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_CLEARED_8

#include "Mcu_MemMap.h"

#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            Array for saving the Clock configuration Ids.
*/
static uint8 Mcu_au8ClockConfigIds[MCU_MAX_CLKCONFIGS];
#endif /* (MCU_INIT_CLOCK == STD_ON) */

/**
* @brief            Array for saving the Mode configuration Ids.
*/
static uint8 Mcu_au8ModeConfigIds[MCU_MAX_MODECONFIGS];

#ifndef MCU_MAX_NORAMCONFIGS
/**
* @brief            Array for saving the Ram sectors configuration Ids.
*                   If no RamConfig is defined, remove all usages of this array.
*/
static uint8 Mcu_au8RamConfigIds[MCU_MAX_RAMCONFIGS];
#endif /* ( 0 != MCU_MAX_RAMCONFIGS ) */

#define MCU_STOP_SEC_VAR_CLEARED_8

#include "Mcu_MemMap.h"


#define MCU_START_SEC_VAR_INIT_UNSPECIFIED

#include "Mcu_MemMap.h"


/**
*  @brief Variable that indicates the state of the driver.
*/
static Mcu_StatusType Mcu_eStatus = MCU_UNINIT;


#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED

#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"

/**
* @brief            Local copy of the pointer to the configuration data.
*/
#if ((defined(MCU_CMU_ERROR_ISR_USED) && (MCU_CMU_ERROR_ISR_USED == STD_ON)) || (defined(MCU_CGU_DETECT_ISR_USED) && (MCU_CGU_DETECT_ISR_USED == STD_ON)))
const Mcu_ConfigType * Mcu_pConfigPtr;
#else
static const Mcu_ConfigType * Mcu_pConfigPtr;
#endif


#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"
/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"


#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
const Mcu_DemConfigType * Mcu_pDemCfgPtr;
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */


#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"


#if (MCU_PARAM_CHECK == STD_ON)
static Std_ReturnType Mcu_CheckInit(const Mcu_ConfigType * ConfigPtr);
#endif /* (MCU_PARAM_CHECK == STD_ON) */


#ifndef MCU_MAX_NORAMCONFIGS
#if (MCU_PARAM_CHECK == STD_ON)
static Std_ReturnType Mcu_CheckInitRamSection(Mcu_RamSectionType RamSection);
#endif /* (MCU_PARAM_CHECK == STD_ON) */
#endif /* ifndef MCU_MAX_NORAMCONFIGS */


#if (MCU_INIT_CLOCK  == STD_ON)
#if (MCU_PARAM_CHECK == STD_ON)
static Std_ReturnType Mcu_CheckInitClock(Mcu_ClockType ClockSetting);
#endif /* (MCU_PARAM_CHECK == STD_ON) */
#endif /* (MCU_INIT_CLOCK  == STD_ON) */


#if (MCU_PARAM_CHECK == STD_ON)
static Std_ReturnType Mcu_CheckSetMode(Power_Ip_ModeType McuMode);
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#ifdef MCU_GET_MIDR_API
#if ( (MCU_GET_MIDR_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
static Std_ReturnType Mcu_CheckGetMidrStructure(const Mcu_MidrReturnType MidrPtr[MCU_SIUL2_TOTAL_UNITS]);
#endif /* ( (MCU_GET_MIDR_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */
#endif /* (MCU_GET_MIDR_API == STD_ON) */

#if (MCU_INIT_CLOCK   == STD_ON)
#if (MCU_NO_PLL       == STD_OFF)
#if ( MCU_PARAM_CHECK == STD_ON )
static Std_ReturnType Mcu_CheckDistributePllClock(void);
#endif /* (MCU_PARAM_CHECK == STD_ON)  */
#endif /* (MCU_NO_PLL      == STD_OFF) */
#endif /* (MCU_INIT_CLOCK  == STD_ON)  */

#if ( \
      (MCU_PERFORM_RESET_API   == STD_ON) && \
      (MCU_PARAM_CHECK         == STD_ON)    \
    )
static Std_ReturnType Mcu_CheckPerformReset(void);
#endif


#if (MCU_VERSION_INFO_API == STD_ON)
#if (MCU_PARAM_CHECK      == STD_ON)
static Std_ReturnType Mcu_CheckGetVersionInfo(const Std_VersionInfoType * VersionInfo);
#endif /* (MCU_PARAM_CHECK == STD_ON) */
#endif /* (MCU_VERSION_INFO_API == STD_ON) */

#ifdef MCU_EMIOS_CONFIGURE_GPREN_API
#if ( (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
static Std_ReturnType Mcu_CheckConfigureGpren(uint8 Module);
#endif /* ( (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */
#endif /* MCU_EMIOS_CONFIGURE_GPREN_API */

#ifdef MCU_DISABLE_CMU_API
#if ( (MCU_DISABLE_CMU_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
static Std_ReturnType Mcu_CheckDisableCMU(Clock_Ip_NameType ClockName);

#endif /* ( (MCU_DISABLE_CMU_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */
#endif /* MCU_DISABLE_CMU_API */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
/* MCU state check, entry point. */
static Std_ReturnType Mcu_HLDChecksEntry(uint8 McuServiceID);
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */


#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
/* MCU state check, exit point. */
static void Mcu_HLDChecksExit(  Std_ReturnType RetStatus,
                                uint8 McuServiceID
                              );
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#if (MCU_PARAM_CHECK == STD_ON)
/**
* @brief Mcu_CheckInit - checks for Mcu_Init
* @implements Mcu_CheckInit_Activity
*/
static Std_ReturnType Mcu_CheckInit(const Mcu_ConfigType * ConfigPtr)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

#if (MCU_PRECOMPILE_SUPPORT == STD_OFF)
    if (NULL_PTR == ConfigPtr)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_ID, MCU_E_INIT_FAILED);
    }
#else /* MCU_PRECOMPILE_SUPPORT == STD_ON */
    if (NULL_PTR != ConfigPtr)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_ID, MCU_E_INIT_FAILED);
    }
#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */

    return CheckStatus;
}
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#ifndef MCU_MAX_NORAMCONFIGS
#if (MCU_PARAM_CHECK == STD_ON)
/**
* @brief Mcu_CheckInitRamSection - checks for Mcu_InitRamSection
* @implements Mcu_CheckInitRamSection_Activity
*/
static Std_ReturnType Mcu_CheckInitRamSection(Mcu_RamSectionType RamSection)
{
    const uint8 RamConfigId = Mcu_au8RamConfigIds[RamSection];
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    /* Check if the Ram section's ID is in range. */
    if (RamSection >= Mcu_pConfigPtr->NoRamConfigs)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_ID, MCU_E_PARAM_RAMSECTION);
    }
    else
    {
        /* Check if Ram memory configuration is valid. */
        if (NULL_PTR == Mcu_pConfigPtr->RamConfigArrayPtr)
        {
            CheckStatus = (Std_ReturnType)E_NOT_OK;

            (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_ID, MCU_E_PARAM_RAMSECTION);
        }
        /* Check if Ram write size is valid. */
        else
        {
            if (
                    ( (Mcu_RamWriteSizeType)1U != ((*Mcu_pConfigPtr->RamConfigArrayPtr)[RamConfigId]).RamWriteSize ) &&
                    ( (Mcu_RamWriteSizeType)2U != ((*Mcu_pConfigPtr->RamConfigArrayPtr)[RamConfigId]).RamWriteSize ) &&
                    ( (Mcu_RamWriteSizeType)4U != ((*Mcu_pConfigPtr->RamConfigArrayPtr)[RamConfigId]).RamWriteSize ) &&
                    ( (Mcu_RamWriteSizeType)8U != ((*Mcu_pConfigPtr->RamConfigArrayPtr)[RamConfigId]).RamWriteSize )
               )
            {
                CheckStatus = (Std_ReturnType)E_NOT_OK;

                (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_ID, MCU_E_PARAM_RAMSECTION);
            }
        }
    }

    return CheckStatus;
}
#endif /* (MCU_PARAM_CHECK == STD_ON) */
#endif /* ifndef MCU_MAX_NORAMCONFIGS */


#if (MCU_INIT_CLOCK  == STD_ON)
#if (MCU_PARAM_CHECK == STD_ON)
/**
* @brief Mcu_CheckInitClock - checks for Mcu_InitClock
* @implements Mcu_CheckInitClock_Activity
*/
static Std_ReturnType Mcu_CheckInitClock(Mcu_ClockType ClockSetting)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if (ClockSetting >= Mcu_pConfigPtr->NoClkConfigs)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_ID, MCU_E_PARAM_CLOCK);
    }

    return CheckStatus;
}
#endif /* (MCU_PARAM_CHECK == STD_ON) */
#endif /* (MCU_INIT_CLOCK  == STD_ON) */


#if (MCU_PARAM_CHECK == STD_ON)
/**
* @brief Mcu_CheckSetMode - checks for Mcu_SetMode
* @implements Mcu_CheckSetMode_Activity
*/
static Std_ReturnType Mcu_CheckSetMode(Power_Ip_ModeType McuMode)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if (McuMode >= Mcu_pConfigPtr->NoModeConfigs)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_ID, MCU_E_PARAM_MODE);
    }

    return CheckStatus;
}
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#ifdef MCU_GET_MIDR_API
#if ( (MCU_GET_MIDR_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
/**
* @brief Mcu_CheckGetMidrStructure - checks for Mcu_GetMidrStructure
* @implements Mcu_CheckGetMidrStructure_Activity
*/
static Std_ReturnType Mcu_CheckGetMidrStructure(const Mcu_MidrReturnType MidrPtr[MCU_SIUL2_TOTAL_UNITS])
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if (NULL_PTR == MidrPtr)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETMIDRSTRUCTURE_ID, MCU_E_PARAM_POINTER);
    }

    return CheckStatus;
}
#endif /* ( (MCU_GET_MIDR_API == STD_ON) && (MCU_GET_MIDR_API == STD_ON) ) */
#endif /* MCU_GET_MIDR_API */

#if (MCU_INIT_CLOCK  == STD_ON)
#if (MCU_NO_PLL      == STD_OFF)
#if (MCU_PARAM_CHECK == STD_ON)
/**
* @brief Mcu_CheckDistributePllClock - checks for Mcu_DistributePllClock
* @implements Mcu_CheckDistributePllClock_Activity
*/
static Std_ReturnType Mcu_CheckDistributePllClock(void)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if ( MCU_PLL_LOCKED != Mcu_Ipw_GetPllStatus() )
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_ID, MCU_E_PLL_NOT_LOCKED);
    }

    return CheckStatus;
}
#endif /* (MCU_PARAM_CHECK == STD_ON)  */
#endif /* (MCU_NO_PLL      == STD_OFF) */
#endif /* (MCU_INIT_CLOCK  == STD_ON)  */


#if ( \
     (MCU_PERFORM_RESET_API   == STD_ON) && \
     (MCU_PARAM_CHECK         == STD_ON)    \
    )
/**
* @brief Mcu_CheckPerformReset - checks for Mcu_PerformReset
* @implements Mcu_CheckPerformReset_Activity
*/
static Std_ReturnType Mcu_CheckPerformReset(void)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    return CheckStatus;
}
#endif /* ( (MCU_PERFORM_RESET_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */


#if (MCU_VERSION_INFO_API == STD_ON)
#if (MCU_PARAM_CHECK      == STD_ON)
/**
* @brief Mcu_CheckGetVersionInfo - checks for Mcu_GetVersionInfo
* @implements Mcu_CheckGetVersionInfo_Activity
*/
static Std_ReturnType Mcu_CheckGetVersionInfo(const Std_VersionInfoType * VersionInfo)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if (NULL_PTR == VersionInfo)
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void)Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETVERSIONINFO_ID, MCU_E_PARAM_POINTER);
    }

    return CheckStatus;
}
#endif /* (MCU_PARAM_CHECK == STD_ON) */
#endif /* (MCU_VERSION_INFO_API == STD_ON) */

#ifdef MCU_EMIOS_CONFIGURE_GPREN_API
#if ( (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
/**
* @brief Mcu_CheckConfigureGpren - checks for Mcu_EmiosConfigureGpren
* @implements Mcu_CheckConfigureGpren_Activity
*/
static Std_ReturnType Mcu_CheckConfigureGpren(uint8 Module)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

#ifdef MCU_CHECK_EMIOS_STATUS
  #if (MCU_CHECK_EMIOS_STATUS == STD_ON)
    if ( (Std_ReturnType)E_NOT_OK == Mcu_IPW_CheckEmiosStatus(Module) )
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_EMIOSCONFIGUREGPREN_ID, MCU_E_EMIOS_DEACTIVATED);
    }
  #endif /* (MCU_CHECK_EMIOS_STATUS == STD_ON) */
#endif /* MCU_CHECK_EMIOS_STATUS */

    MCU_PARAM_UNUSED(Module);

    return CheckStatus;
}
#endif /* ( (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */
#endif /* MCU_EMIOS_CONFIGURE_GPREN_API */

#ifdef MCU_DISABLE_CMU_API
#if ( (MCU_DISABLE_CMU_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
/**
* @brief Mcu_CheckDisableCMU - checks for Mcu_Disable_CMU
*/
static Std_ReturnType Mcu_CheckDisableCMU(Clock_Ip_NameType ClockName)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if (((uint8)ClockName) >= ((uint8)RESERVED_CLK))
    {
        CheckStatus = (Std_ReturnType)E_NOT_OK;

        (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISABLECMU_ID, MCU_E_CMU_INDEX_OUT_OF_RANGE);
    }

    return CheckStatus;
}
#endif /* ( (MCU_DISABLE_CMU_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */
#endif /* MCU_DISABLE_CMU_API */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
/* MCU state check, entry point. */
/**
* @brief Mcu_HLDChecksEntry - checks for invalid mode transitions.
* @implements Mcu_HLDChecksEntry_Activity
*/
static Std_ReturnType Mcu_HLDChecksEntry(uint8 McuServiceID)
{
    Std_ReturnType CheckStatus = (Std_ReturnType)E_OK;

    if (MCU_INIT_ID == McuServiceID)
    {
        if (MCU_UNINIT != Mcu_eStatus) /* If "Mcu_Init" was already called (i.e. driver is initialized). */
        {
            CheckStatus = (Std_ReturnType)E_NOT_OK;
            (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, McuServiceID, MCU_E_ALREADY_INITIALIZED);
        }
    }
    else
    {
        if (MCU_UNINIT == Mcu_eStatus) /* If "Mcu_Init" was not called (i.e driver is uninitialized). */
        {
            CheckStatus = (Std_ReturnType)E_NOT_OK;
            (void) Det_ReportError((uint16)MCU_MODULE_ID, MCU_INSTANCE_ID, McuServiceID, MCU_E_UNINIT);
        }
        else
        {
            Mcu_eStatus = MCU_BUSY;
        }
    }

    return CheckStatus;
}

#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */


#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
/* MCU state check, exit point. */
/**
* @brief Mcu_HLDChecksExit - checks for invalid mode transitions.
* @implements Mcu_HLDChecksExit_Activity
*/
static void Mcu_HLDChecksExit(  Std_ReturnType RetStatus,
                                uint8 McuServiceID
                              )
{
    if (MCU_INIT_ID == McuServiceID)
    {
        if ((Std_ReturnType)E_OK == (Std_ReturnType)RetStatus)
        {
            Mcu_eStatus = MCU_IDLE;
        }
        else
        {
            Mcu_eStatus = MCU_UNINIT;
        }
    }
    else
    {
        Mcu_eStatus = MCU_IDLE;
    }
}
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief            MCU driver initialization function.
* @details          This routine initializes the MCU Driver.
*                   The intention of this function is to make the configuration setting for power
*                   down, clock and Ram sections visible within the MCU Driver.
*
* @param[in]        ConfigPtr   Pointer to configuration structure.
*
* @return           void
*
* @api
*
* @implements Mcu_Init_Activity
*/
void Mcu_Init(const Mcu_ConfigType * ConfigPtr)
{
    /* Temporary variable for looping through all the configurations. */
    uint32 NoConfigs;

#if ( (MCU_VALIDATE_GLOBAL_CALL == STD_ON) || (MCU_PARAM_CHECK == STD_ON) )
    Std_ReturnType CheckStatus;
#endif /* ( (MCU_VALIDATE_GLOBAL_CALL == STD_ON) || (MCU_PARAM_CHECK == STD_ON) ) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    CheckStatus = (Std_ReturnType) Mcu_HLDChecksEntry(MCU_INIT_ID);

    if ( (Std_ReturnType)E_OK == CheckStatus )
    {
#else
    Mcu_eStatus = MCU_IDLE;
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
        /* Get a local copy of the driver initalization structure. */

#if (MCU_PARAM_CHECK == STD_ON)
        /* When PostBuild is used and #(Variants) > 1, the input parameter 'ConfigPtr' is mandatory
         * to be different than NULL_PTR. */
        /* Check the config. In case of error, return immediately. The "Mcu_CheckInit" function will report DET errors. */
        CheckStatus = Mcu_CheckInit(ConfigPtr);

        if ((Std_ReturnType)E_OK == CheckStatus)
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#if (MCU_PRECOMPILE_SUPPORT == STD_ON)
            Mcu_pConfigPtr = &Mcu_PreCompileConfig;
            MCU_PARAM_UNUSED(ConfigPtr);
#else
            Mcu_pConfigPtr = ConfigPtr;
#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            /* Get a local copy of the DEM error reporting structure. */
            Mcu_pDemCfgPtr = Mcu_pConfigPtr->DemConfigPtr;
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

            /* Save the Mcu Mode IDs configurations. */
            for (NoConfigs = (uint32)0U; NoConfigs < Mcu_pConfigPtr->NoModeConfigs; NoConfigs++)
            {
                Mcu_au8ModeConfigIds[(*Mcu_pConfigPtr->ModeConfigArrayPtr)[NoConfigs].ModeConfigId] = (uint8)NoConfigs;
            }

#if (MCU_INIT_CLOCK == STD_ON)
            /* Save the Mcu Clock IDs configurations. */
            for (NoConfigs = (uint32)0U; NoConfigs < Mcu_pConfigPtr->NoClkConfigs; NoConfigs++)
            {
                Mcu_au8ClockConfigIds[(*Mcu_pConfigPtr->ClockConfigArrayPtr)[NoConfigs].ClkConfigId] = (uint8)NoConfigs;
            }
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#ifndef MCU_MAX_NORAMCONFIGS
            /* Save the Mcu Ram Sector IDs configurations. */
            for (NoConfigs = (uint32)0U; NoConfigs < Mcu_pConfigPtr->NoRamConfigs; NoConfigs++)
            {
                Mcu_au8RamConfigIds[(*Mcu_pConfigPtr->RamConfigArrayPtr)[NoConfigs].RamSectorId] = (uint8)NoConfigs;
            }
#endif /* (0 != MCU_MAX_RAMCONFIGS) */

            Mcu_Ipw_Init(Mcu_pConfigPtr->HwIPsConfigPtr);

#if (MCU_PARAM_CHECK == STD_ON)
        }
        else
        {
            /* Clean the init pointer in case of an error. */
            Mcu_pConfigPtr = NULL_PTR;
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */


#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        /* The driver is now initialized. Set the proper status. */
        Mcu_HLDChecksExit(CheckStatus, MCU_INIT_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}


/**
* @brief            MCU driver initialization of Ram sections.
* @details          Function initializes the ram section selected by RamSection parameter.
*                   The section base address, size and value to be written are provided from
*                   the configuration structure.
*                   The function will write the value specified in the configuration structure
*                   indexed by RamSection.
*                   After the write it will read back the RAM to verify that the requested value was
*                   written.
*
* @param[in]        RamSection   Index of ram section from configuration structure to be initialized.
*
* @return           Command has or has not been accepted.
* @retval           E_OK        Valid parameter, the driver state allowed execution and the RAM
*                               check was successful
* @retval           E_NOT_OK    Invalid parameter, the driver state did not allowed execution or
*                               the RAM check was not successful
*
* @api
*
* @implements Mcu_InitRamSection_Activity
*
*/
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
#ifndef MCU_MAX_NORAMCONFIGS
    const uint8 RamConfigId = Mcu_au8RamConfigIds[RamSection];
#endif /* #ifndef MCU_MAX_NORAMCONFIGS */
    /* Result of the operation. */
    Std_ReturnType RamStatus = (Std_ReturnType)E_NOT_OK;

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    /* Check if the driver is initialized. */
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_INITRAMSECTION_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#ifndef MCU_MAX_NORAMCONFIGS
    #if (MCU_PARAM_CHECK == STD_ON)
        /* Check if Ram memory configuration is valid. */
        /* If no ramConfig is defined, the function will return immediately. */
        if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckInitRamSection(RamSection) )
        {
    #endif /* (MCU_PARAM_CHECK == STD_ON) */
            /* Get Ram settings from the configuration structure. */
            RamStatus = Mcu_Ipw_InitRamSection(&(*Mcu_pConfigPtr->RamConfigArrayPtr)[RamConfigId]);
    #if (MCU_PARAM_CHECK == STD_ON)
        }
    #endif /* (MCU_PARAM_CHECK == STD_ON) */
#else
        /* To avoid compiler warning. */
        MCU_PARAM_UNUSED(RamSection);
#endif /* #ifndef MCU_MAX_NORAMCONFIGS */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_INITRAMSECTION_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return RamStatus;
}


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            MCU driver clock initialization function.
* @details          This function intializes the PLL and MCU specific clock options. The clock
*                       setting is provided from the configuration structure.
*
* @param[in]        ClockSetting   Clock setting ID from config structure to be used.
*
* @return           Command has or has not been accepted.
* @retval           E_OK        The driver state allowed the execution of the function and the
*                                   provided parameter was in range
* @retval           E_NOT_OK    The driver state did not allowed execution or the parameter was
*                                   invalid
*
* @api
*
* @implements Mcu_InitClock_Activity
*/
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    const uint8 ClockConfigId =  Mcu_au8ClockConfigIds[ClockSetting];
    /* Return the success of the clock initalization operation. */
#if ( (MCU_VALIDATE_GLOBAL_CALL == STD_ON) || (MCU_PARAM_CHECK == STD_ON) )
    Std_ReturnType ClockStatus = (Std_ReturnType)E_NOT_OK;
#else
    Std_ReturnType ClockStatus;
#endif

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_INITCLOCK_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

        /* Check if Clock configuration is valid. */
#if (MCU_PARAM_CHECK == STD_ON)
        if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckInitClock(ClockSetting) )
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */
            Mcu_Ipw_InitClock(&(*Mcu_pConfigPtr->ClockConfigArrayPtr)[ClockConfigId]);

            /* Command has been accepted. */
            ClockStatus = (Std_ReturnType)E_OK;
#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_INITCLOCK_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return ClockStatus;
}
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/**
* @brief            This function sets the MCU power mode.
* @details          This function activates MCU power mode from config structure selected by McuMode
*                       parameter.
*                   If the driver state is invalid or McuMode is not in range the function will skip
*                       changing the mcu mode.
*
* @param[in]        McuMode   MCU mode setting ID from config structure to be set.
*
* @return           void
*
* @api
*
* @implements Mcu_SetMode_Activity
*/
void Mcu_SetMode(Mcu_ModeType McuMode)
{
    const uint8 McuModeId = Mcu_au8ModeConfigIds[McuMode];

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_SETMODE_ID) )
    {
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/

#if (MCU_PARAM_CHECK == STD_ON)
        /* Check if Mode configuration is valid. */
        if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckSetMode(McuMode) )
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */

            Mcu_Ipw_SetMode( &(*Mcu_pConfigPtr->ModeConfigArrayPtr)[McuModeId] );

#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */


#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_SETMODE_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}

#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_NO_PLL == STD_OFF)
/**
* @brief            This function activates the PLL clock to the MCU clock distribution.
* @details          Function completes the PLL configuration and then activates the PLL clock to
*                       MCU. If the MCU_NO_PLL is TRUE the Mcu_DistributePllClock has to be
*                       disabled.
*                   The function will not distribute the PLL clock if the driver state does not
*                       allow it, or the PLL is not stable.
*
* @return           Std_ReturnType
* @retval           E_OK        Command has been accepted.
* @retval           E_NOT_OK    Command has not been accepted.
*
* @api
*
* @implements Mcu_DistributePllClock_Activity
*
*/
Std_ReturnType Mcu_DistributePllClock(void)
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    /* Return variable */
    Std_ReturnType PllStatus = (Std_ReturnType)E_NOT_OK;
#else
    Std_ReturnType PllStatus;
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_DISTRIBUTEPLLCLOCK_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#if (MCU_PARAM_CHECK == STD_ON)
        /* Check if the PLL is locked. */
        if ( (Std_ReturnType)E_OK == (Std_ReturnType)Mcu_CheckDistributePllClock() )
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */

            /* Set the PLL as System Clock if it is locked and enabled by the current mode.
            If the PLL0 is already selected as system clock, then this function will return without
            doing anything. */
            Mcu_Ipw_DistributePllClock();

            PllStatus = (Std_ReturnType)E_OK;
#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */


#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_DISTRIBUTEPLLCLOCK_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return PllStatus;
}
#endif /* (MCU_NO_PLL == STD_OFF) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/**
* @brief            This function returns the lock status of the PLL.
* @details          The user takes care that the PLL is locked by executing Mcu_GetPllStatus.
*                       If the MCU_NO_PLL is TRUE the MCU_GetPllStatus has to return
*                       MCU_PLL_STATUS_UNDEFINED.
*                   It will also return MCU_PLL_STATUS_UNDEFINED if the driver state was invalid
*
* @return           Provides the lock status of the PLL.
* @retval           MCU_PLL_STATUS_UNDEFINED    PLL Status is unknown.
* @retval           MCU_PLL_LOCKED              PLL is locked.
* @retval           MCU_PLL_UNLOCKED            PLL is unlocked.
*
* @api
*
* @implements Mcu_GetPllStatus_Activity
*
*
*/
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
    /* Return variable. */
#if ( (MCU_VALIDATE_GLOBAL_CALL == STD_ON) || (MCU_NO_PLL == STD_ON) )
    Mcu_PllStatusType PllStatus = MCU_PLL_STATUS_UNDEFINED;
#else
    Mcu_PllStatusType PllStatus;
#endif

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_GETPLLSTATUS_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    /* If the PLL is not used in the configuration, return MCU_PLL_STATUS_UNDEFINED. */
#if (MCU_NO_PLL == STD_OFF)
        /* Get status of the PLL (if enabled in current mode).
           At this point, the return value can be only MCU_PLL_LOCKED or MCU_PLL_UNLOCKED. */
        PllStatus = Mcu_Ipw_GetPllStatus();
#endif /* (MCU_NO_PLL == STD_OFF) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_GETPLLSTATUS_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return PllStatus;
}

/**
* @brief            This function returns the Reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*
*
* @return           Reason of the Reset event.
*
* @api
*
* @implements Mcu_GetResetReason_Activity
*/
Mcu_ResetType Mcu_GetResetReason(void)
{
    /* Return value of the function. */
    Mcu_ResetType ResetReason = MCU_RESET_UNDEFINED;

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_GETRESETREASON_ID) )
    {
#else
    if (MCU_UNINIT != Mcu_eStatus)
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
        /* Get the reset reason. */
        ResetReason = Mcu_Ipw_GetResetReason();

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit( (Std_ReturnType)E_OK, MCU_GETRESETREASON_ID);
    }
#else
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return ResetReason;
}


/**
* @brief            This function returns the Raw Reset value.
* @details          This routine returns the Raw Reset value that is read from the hardware.
*
* @return           Description of the returned value.
* @retval           uint32   Code of the Raw reset value.
*
* @api
*
* @implements Mcu_GetResetRawValue_Activity
*
*/
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
    /* Return value of the function. */
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    Mcu_RawResetType RawResetValue = MCU_RAW_RESET_DEFAULT;
#else
    Mcu_RawResetType RawResetValue;
#endif

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_GETRESETRAWVALUE_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
        RawResetValue = (Mcu_RawResetType) Mcu_Ipw_GetResetRawValue();

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_GETRESETRAWVALUE_ID);
    }
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/

    return RawResetValue;
}

#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller. In case the function returns, the user must reset the
*                   platform using an alternate reset mechanism
*
* @return           void
*
* @api
*
* @implements Mcu_PerformReset_Activity
*/
void Mcu_PerformReset(void)
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_PERFORMRESET_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#if (MCU_PARAM_CHECK == STD_ON)
        if ( (Std_ReturnType)E_OK == (Std_ReturnType)Mcu_CheckPerformReset() )
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#if (MCU_RESET_CALLOUT_USED == STD_ON)
            /* User callout. */
            MCU_RESET_CALLOUT();
#endif /* (MCU_RESET_CALLOUT_USED == STD_ON) */

            Mcu_Ipw_PerformReset(Mcu_pConfigPtr->HwIPsConfigPtr);
            /* we should not get here */
            /* it's the app. responsability to detect if the reset failled */
#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_PERFORMRESET_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */


#if (MCU_VERSION_INFO_API == STD_ON)
/**
* @brief            This function returns the Version Information for the MCU module.
* @details          This function returns the vendor id, module id, major, minor and patch version.
*
* @param[in,out]    versioninfo   A pointer to a variable to store version info.
*
* @return           void
*
* @api
*
* @implements Mcu_GetVersionInfo_Activity
*/
void Mcu_GetVersionInfo(Std_VersionInfoType * versioninfo)
{
#if (MCU_PARAM_CHECK == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckGetVersionInfo(versioninfo) )
    {
#endif /* (MCU_PARAM_CHECK == STD_ON) */
        (versioninfo)->vendorID = (uint16)MCU_VENDOR_ID;
        (versioninfo)->moduleID = (uint8)MCU_MODULE_ID;
        (versioninfo)->sw_major_version = (uint8)MCU_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8)MCU_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8)MCU_SW_PATCH_VERSION;
#if (MCU_PARAM_CHECK == STD_ON)
    }
#endif /* (MCU_PARAM_CHECK == STD_ON) */
}
#endif /* (MCU_VERSION_INFO_API == STD_ON) */

#ifdef MCU_GET_MIDR_API
  #if (MCU_GET_MIDR_API == STD_ON)
/**
* @brief            This function returns the value of the MIDR registers.
* @details          This function returns the platform dependent Mcu_MidrReturnType structure witch
*                   contains the MIDRn registers.
*
* @param[in,out]    MidrPtr   A pointer to a variable to store the Mcu_MidrReturnType structure.
*
* @return           void
*
* @api
*
* @implements Mcu_GetMidrStructure_Activity
*
*/
void Mcu_GetMidrStructure(Mcu_MidrReturnType MidrPtr[MCU_SIUL2_TOTAL_UNITS])
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_GETMIDRSTRUCTURE_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#ifdef MCU_GET_MIDR_API
  #if ( (MCU_GET_MIDR_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) )
        /* Check if Mode configuration is valid. */
        if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckGetMidrStructure(MidrPtr) )
        {
  #endif /* ( (MCU_GET_MIDR_API == STD_ON) && (MCU_PARAM_CHECK == STD_ON) ) */
#endif /* MCU_GET_MIDR_API */
            Mcu_Ipw_GetMidrStructure( MidrPtr );
#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* ( MCU_PARAM_CHECK == STD_ON) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_GETMIDRSTRUCTURE_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}
  #endif /* (MCU_GET_MIDR_API == STD_ON) */
#endif /* MCU_GET_MIDR_API */

#if (MCU_GET_RAM_STATE_API == STD_ON)
/**
* @brief            This function returns the actual state of the RAM.
* @details          This function returns if the Ram Status is valid after a reset.
*                   The report is get from STCU as a result of MBIST (Memory Built-In Self Tests).
*
* @return           Status of the Ram Content.
*
* @retval           MCU_RAMSTATE_INVALID    Ram state is not valid or unknown (default),
*                                               or the driver state does not allow this call.
* @retval           MCU_RAMSTATE_VALID      Ram state is valid.
*
* @api
*
* @implements Mcu_GetRamState_Activity
*
*/
Mcu_RamStateType Mcu_GetRamState(void)
{
    /* Return value of this function. */
    Mcu_RamStateType RamState = MCU_RAMSTATE_INVALID;

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_GETRAMSTATE_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
        RamState = Mcu_Ipw_GetRamState();

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_GETRAMSTATE_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return RamState;
}

#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

#ifdef MCU_EMIOS_CONFIGURE_GPREN_API
#if (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON)
/**
 * @brief   eMios Global Prescaler Enable.
 * @details This function enables or disables the GPREN bit of the EMIOSMCR register of an
 *          addressed eMIOS instance.
 * @pre     Function requires an execution of Mcu_Init() before it can be used,
 *otherwise it reports error to DET.
 *
 * @param[in] Module         MCU_EMIOS_MODULE_0 --> Select eMios 0
 *                           MCU_EMIOS_MODULE_1 --> Select eMios 1
 *                           MCU_EMIOS_MODULE_2 --> Select eMios 2
 *
 * @param[in] Value          MCU_EMIOS_GPREN_BIT_ENABLE   --> Global Prescaler Enabled
 *                           MCU_EMIOS_GPREN_BIT_DISABLE  --> Global Prescaler Disabled
 *
 * @return                   void
 *
 * @api
 * @implements Mcu_EmiosConfigureGpren_Activity
 */
void Mcu_EmiosConfigureGpren(uint8 Module,
                             uint8 Value
                             )
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_EMIOSCONFIGUREGPREN_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#if (MCU_PARAM_CHECK == STD_ON)
        if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckConfigureGpren(Module) )
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */
            Mcu_Ipw_EmiosConfigureGpren(Module, Value);
#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_EMIOSCONFIGUREGPREN_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}
#endif /* (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) */
#endif /* MCU_EMIOS_CONFIGURE_GPREN_API */

#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
/**
 * @brief   Disable clock monitoring unit.
 * @details This function disables the selected clock monitoring unit.
 * @pre     Function requires an execution of Mcu_Init() before it can be used.
 *
 * @param[in] ClockName    Name of the monitor clock for which CMU must be disabled.
 *
 * @return                   void
 *
 * @api
 * @implements Mcu_DisableCmu_Activity
 */
void Mcu_DisableCmu(Clock_Ip_NameType ClockName)
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_DISABLECMU_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

#if (MCU_PARAM_CHECK == STD_ON)
        if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_CheckDisableCMU(ClockName) )
        {
#endif /* (MCU_PARAM_CHECK == STD_ON) */
            Mcu_Ipw_DisableCmu(ClockName);
#if (MCU_PARAM_CHECK == STD_ON)
        }
#endif /* (MCU_PARAM_CHECK == STD_ON) */

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_DISABLECMU_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}
#endif /* (MCU_DISABLE_CMU_API == STD_ON) */
#endif /* MCU_DISABLE_CMU_API */

#ifdef MCU_GET_CLOCK_FREQUENCY_API
#if (MCU_GET_CLOCK_FREQUENCY_API == STD_ON)
/**
 * @brief   Return the frequency of a given clock.
 * @details This function returns the frequency of a given clock which is request by user.
 * @pre     Function requires an execution of Mcu_Init() before it can be used,
 *
 * @param[in] ClockName    Name of the monitor clock for which CMU must be disabled.
 *
 * @return                 uint32
 *
 * @api
 *
 */
uint64 Mcu_GetClockFrequency(Clock_Ip_NameType ClockName)
{
    uint64 Frequency = 0U;

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_GETCLOCKFREQUENCY_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

        Frequency = MCU_Ipw_GetClockFrequency(ClockName);

#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_GETCLOCKFREQUENCY_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */

    return Frequency;
}

#endif /* (MCU_GET_CLOCK_FREQUENCY_API == STD_ON) */
#endif /* MCU_GET_CLOCK_FREQUENCY_API */

#ifdef MCU_SLEEPONEXIT_SUPPORT
  #if (MCU_SLEEPONEXIT_SUPPORT == STD_ON)
/**
* @brief            This function disable/enable SleepOnExit.
* @details          Disable/enable Sleep on exit when returning from Handler mode to Thread mode.
*
* @param[in]        Mcu_SleepOnExitType   The value will be configured to SLEEPONEXIT bits.
*                                         MCU_SLEEP_ON_EXIT_DISABLED - Disable SLEEPONEXIT bit.
*                                         MCU_SLEEP_ON_EXIT_ENABLED - Enable SLEEPONEXIT bit.
* @return           void
*
* @api
*
* @implements Mcu_SleepOnExit_Activity
*
*/
void Mcu_SleepOnExit(Mcu_SleepOnExitType SleepOnExit)
{
#if ( MCU_VALIDATE_GLOBAL_CALL == STD_ON )
    if ((Std_ReturnType)E_OK == (Std_ReturnType)Mcu_HLDChecksEntry(MCU_SLEEPONEXIT_ID))
    {
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/

            Mcu_Ipw_SleepOnExit(SleepOnExit);

#if ( MCU_VALIDATE_GLOBAL_CALL == STD_ON )
        Mcu_HLDChecksExit( (Std_ReturnType)E_OK ,MCU_SLEEPONEXIT_ID);
    }
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/
}
  #endif
#endif



#if (MCU_INIT_CLOCK == STD_ON)
/**
 * @brief   Clock source failure notification
 * @details This function is called when frequency of clock source is not in the expected range.
 * @pre     McuClockSourceFailureNotification must be enabled.
 *
 * @param[in] ClockName    Name of the clock that triggered a failure.
 *
 * @return                 void
 *
 * @api
 */
void Mcu_ClkSrcFailureNotification(Clock_Ip_NameType ClockName)
{
    (void)ClockName;

    if ( (NULL_PTR != Mcu_pConfigPtr) && (Mcu_pConfigPtr->ClkSrcFailureNotification == MCU_CLK_NOTIF_EN))
    {
#if (defined(MCU_CMU_ERROR_ISR_USED) && (MCU_CMU_ERROR_ISR_USED == STD_ON))
    #if defined(MCU_CMU_FCCU_NOTIFICATION)
        /* CMU clock out of bounds notification. */
        MCU_CMU_FCCU_NOTIFICATION(ClockName);
    #endif
    #ifdef MCU_ERROR_ISR_NOTIFICATION
        MCU_ERROR_ISR_NOTIFICATION(MCU_E_ISR_CLOCK_FAILURE);
    #endif
#elif (defined(MCU_CGU_DETECT_ISR_USED) && (MCU_CGU_DETECT_ISR_USED == STD_ON))
        #if defined(MCU_CGU_NOTIFICATION)
        MCU_CGU_NOTIFICATION(ClockName, MCU_ISR_CLOCK_INACTIVE);
        #endif
#else
        /* Nothing else to be done. */
#endif /* (MCU_CMU_ERROR_ISR_USED == STD_OFF && MCU_CGU_DETECT_ISR_USED == STD_OFF) */
    }
}

#endif /* (MCU_INIT_CLOCK == STD_ON) */

#ifdef MCU_PMCAECONFIG_API
#if (MCU_PMCAECONFIG_API == STD_ON)
/**
* @brief            This function configure the Power Management Controller AE.
* @details          This function configure the Power Management Controller AE of
*                   the microcontroller.
*
* @return           void
*
* @api
*
*
*/
void Mcu_PmcAeConfig(void)
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_PMCAECONFIG_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
        Mcu_Ipw_PmcAeConfig(Mcu_pConfigPtr->HwIPsConfigPtr);
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_PMCAECONFIG_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}
#endif /* (MCU_PMCAECONFIG_API == STD_ON) */
#endif

#ifdef MCU_AECRESETCONFIG_API
#if (MCU_AECRESETCONFIG_API == STD_ON)
/**
* @brief            This function configure the Reset config AEC.
* @details          This function configure the Reset config AEC of
*                   the microcontroller.
*
* @return           void
*
* @api
*
*
*/
void Mcu_AecResetConfig(void)
{
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
    if ( (Std_ReturnType)E_OK == (Std_ReturnType) Mcu_HLDChecksEntry(MCU_AECRESETCONFIG_ID) )
    {
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
        Mcu_Ipw_AecResetConfig(Mcu_pConfigPtr->HwIPsConfigPtr);
#if (MCU_VALIDATE_GLOBAL_CALL == STD_ON)
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_AECRESETCONFIG_ID);
    }
#endif /* (MCU_VALIDATE_GLOBAL_CALL == STD_ON) */
}
#endif /* (MCU_AECRESETCONFIG_API == STD_ON) */
#endif


#ifdef MCU_LASTMILE_SUPPORT
  #if (STD_ON == MCU_LASTMILE_SUPPORT)
/**
* @brief            This function enable Last Mile.
* @details          Enable Last Mile regulator to provide V15 to core and Flash.
*
* @param[in]        BJTused   BJT used on board or not.
*
* @return           void
*
*/
void Mcu_LastMileEnable(boolean BJTused)
{
#if ( MCU_VALIDATE_GLOBAL_CALL == STD_ON )
    if((Std_ReturnType)E_OK == (Std_ReturnType)Mcu_HLDChecksEntry(MCU_LASTMILEENABLE_ID))
    {
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/ 
 
        Mcu_Ipw_LastMileEnable(BJTused);
        
#if ( MCU_VALIDATE_GLOBAL_CALL == STD_ON )
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_LASTMILEENABLE_ID);
    }
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/  
}

/**
* @brief            This function disable Last Mile.
* @details          Disable Last Mile to switch to Boot regulator to provide a lower voltage to core and flash.
*
* @return           void
*
*/
void Mcu_LastMileDisable(void)
{
#if ( MCU_VALIDATE_GLOBAL_CALL == STD_ON )
    if((Std_ReturnType)E_OK == (Std_ReturnType)Mcu_HLDChecksEntry(MCU_LASTMILEDISABLE_ID))
    {
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/ 
 
        Mcu_Ipw_LastMileDisable();
        
#if ( MCU_VALIDATE_GLOBAL_CALL == STD_ON )
        Mcu_HLDChecksExit((Std_ReturnType)E_OK, MCU_LASTMILEDISABLE_ID);
    }
#endif /*( MCU_VALIDATE_GLOBAL_CALL == STD_ON )*/  
}
  #endif
#endif

#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
