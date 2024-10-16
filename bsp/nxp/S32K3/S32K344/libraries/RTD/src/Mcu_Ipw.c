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
*   @file    Mcu_Ipw.c
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
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/* Header file with prototype functions defines in this layer. */
#include "Mcu_Ipw.h"
#include "Mcu_Ipw_Cfg_Defines.h"
#include "SchM_Mcu.h"

/* Header files that are called from IPW layer. */
#include "Power_Ip.h"
#include "Ram_Ip.h"
#include "Clock_Ip.h"


/**
* @brief    Detected development errors shall be reported to the Det_ReportError service of the
*           Development Error Tracer (DET) if the pre-processor switch McuDevErrorDetect is set
*           The detection of development errors is configurable (ON / OFF) at precompile time.
*           The switch McuDevErrorDetect (see chapter 10) shall activate or deactivate the detection
*           of all development errors.
*           Det_ReportError - Service to report development errors.
*
*/
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Mcu_Dem_Wrapper.h"
#endif

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_IPW_VENDOR_ID_C                      43
#define MCU_IPW_AR_RELEASE_MAJOR_VERSION_C       4
#define MCU_IPW_AR_RELEASE_MINOR_VERSION_C       7
#define MCU_IPW_AR_RELEASE_REVISION_VERSION_C    0
#define MCU_IPW_SW_MAJOR_VERSION_C               5
#define MCU_IPW_SW_MINOR_VERSION_C               0
#define MCU_IPW_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Mcu_Ipw.c file and Mcu_Ipw.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_IPW_VENDOR_ID)
    #error "Mcu_Ipw.c and Mcu_Ipw.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Ipw.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != MCU_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != MCU_IPW_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Mcu_Ipw.h are different"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Ipw.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_IPW_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_IPW_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.c and Mcu_Ipw.h are different"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Ipw_Cfg_Defines.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_IPW_CFG_DEFINES_VENDOR_ID)
    #error "Mcu_Ipw.c and Mcu_Ipw_Cfg_Defines.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Ipw_Cfg_Defines.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != MCU_IPW_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != MCU_IPW_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Mcu_Ipw_Cfg_Defines.h are different"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Ipw_Cfg_Defines.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_IPW_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_IPW_CFG_DEFINES_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_IPW_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.c and Mcu_Ipw_Cfg_Defines.h are different"
#endif

/* Check if Mcu_Ipw.c file and Power_Ip.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != POWER_IP_VENDOR_ID)
    #error "Mcu_Ipw.c and Power_Ip.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.c file and Power_Ip.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != POWER_IP_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != POWER_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Power_Ip.h are different"
#endif

/* Check if Mcu_Ipw.c file and Power_Ip.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != POWER_IP_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != POWER_IP_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != POWER_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.c and Power_Ip.h are different"
#endif

/* Check if Mcu_Ipw.c file and Ram_Ip.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != RAM_IP_VENDOR_ID)
    #error "Mcu_Ipw.c and Ram_Ip.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.c file and Ram_Ip.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != RAM_IP_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != RAM_IP_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != RAM_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Ram_Ip.h are different"
#endif

/* Check if Mcu_Ipw.c file and Ram_Ip.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != RAM_IP_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != RAM_IP_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != RAM_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.c and Ram_Ip.h are different"
#endif

/* Check if Mcu_Ipw.c file and Clock_Ip.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != CLOCK_IP_VENDOR_ID)
    #error "Mcu_Ipw.c and Clock_Ip.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.c file and Clock_Ip.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Clock_Ip.h are different"
#endif

/* Check if Mcu_Ipw.c file and Clock_Ip.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != CLOCK_IP_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != CLOCK_IP_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != CLOCK_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.c and Clock_Ip.h are different"
#endif


#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Mcu_Ipw.c file and Det.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != DET_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != DET_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Det.h are different"
#endif
#endif
#endif

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/* Check if Mcu_Ipw.c file and Mcu_Dem_Wrapper.h file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_DEM_WRAPPER_VENDOR_ID)
    #error "Mcu_Ipw.c and Mcu_Dem_Wrapper.h have different vendor ids"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Dem_Wrapper.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != MCU_DEM_WRAPPER_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != MCU_DEM_WRAPPER_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_DEM_WRAPPER_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw.c and Mcu_Dem_Wrapper.h are different"
#endif

/* Check if Mcu_Ipw.c file and Mcu_Dem_Wrapper.h file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_DEM_WRAPPER_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_DEM_WRAPPER_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_DEM_WRAPPER_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw.c and Mcu_Dem_Wrapper.h are different"
#endif
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Mcu_Ipw.c file and SchM_Mcu.h file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != SCHM_MCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != SCHM_MCU_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu_Ipw.c and SchM_Mcu.h are different"
#endif
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/
#if (MCU_INIT_CLOCK == STD_ON)
/* When clock_ip notifications are enabled, then callback is install to receive notifications.
*/
#if (\
(defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)) ||   \
(defined(MCU_DISABLE_RAM_CONFIG) && (MCU_DISABLE_RAM_CONFIG == STD_OFF))                           ||   \
(defined(MCU_DISABLE_FLASH_CONFIG) && (MCU_DISABLE_FLASH_CONFIG == STD_OFF))                       ||   \
(defined(MCU_CMU_ERROR_ISR_USED) && (MCU_CMU_ERROR_ISR_USED == STD_ON))                            ||   \
defined(MCU_ERROR_ISR_NOTIFICATION)                                                                     \
)
#define MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS STD_ON
#else
#define MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS STD_OFF
#endif
#else
#define MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS STD_OFF
#endif /* (MCU_INIT_CLOCK == STD_ON) */
/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#if (MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS == STD_ON)
void Mcu_Ipw_ClockNotificationsCallback(Clock_Ip_NotificationType Notification, Clock_Ip_NameType ClockName);
#endif

#if ((defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)) || (defined(MCU_ERROR_ISR_NOTIFICATION)) || (defined(MCU_PMC_NOTIFICATION)) || (defined(MCU_PMC_AE_NOTIFICATION)))
void Mcu_Ipw_ReportPowerErrorsCallback(Power_Ip_ReportErrorType Error, uint8 ErrorCode);
#endif

#if (defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF))
void Mcu_Ipw_ReportRamErrorsCallback(Ram_Ip_RamReportErrorType Error, uint8 ErrorCode);
#endif

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief            This function initializes the MCU module on the common (main) platform.
* @details          The function initializes the CGM, ME, RGM, and PMC modules.
*                   Called by:
*                       - Mcu_Init() from HLD.
*
* @param[in]        HwIPsConfigPtr   Pointer to IPW configuration structure.
*
* @return           void
*
*/
void Mcu_Ipw_Init(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr)
{

#if ((defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)) || (defined(MCU_ERROR_ISR_NOTIFICATION)) || (defined(MCU_PMC_NOTIFICATION)) || (defined(MCU_PMC_AE_NOTIFICATION)))
    Power_Ip_InstallNotificationsCallback(&Mcu_Ipw_ReportPowerErrorsCallback);
#endif

#if (MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS == STD_ON)
    Clock_Ip_InstallNotificationsCallback(&Mcu_Ipw_ClockNotificationsCallback);
#endif

#if ((MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) && (MCU_GET_RAM_STATE_API == STD_ON))
    Ram_Ip_InstallNotificationsCallback(&Mcu_Ipw_ReportRamErrorsCallback);
#endif

#if (defined(MCU_ENABLE_USER_MODE_SUPPORT) && (STD_ON == MCU_ENABLE_USER_MODE_SUPPORT))
#if (MCU_INIT_CLOCK == STD_ON)
    /* Set user access allowed for Clock */
    Clock_Ip_SetUserAccessAllowed();
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#endif /* (STD_ON == MCU_ENABLE_USER_MODE_SUPPORT) */

    /* Init Power and Reset */
    Power_Ip_Init(HwIPsConfigPtr);
}

#ifndef MCU_MAX_NORAMCONFIGS
/**
* @brief            This function initializes a given RAM section of the MCU on the common (main) platform.
* @details          Function initializes the RAM section specified by the pointer to the "Mcu_RamConfigType" parameter.
*                   The section's base address, size, value to be written, and write-at-once-size are provided by
*                   the configuration structure.
*                   The function will write the value specified in the configuration structure.
*                   After the write it will read back the RAM to verify that the requested value was
*                   written.
*                   Called by:
*                       - Mcu_InitRamSection() from HLD.
*
* @param[in]        RamConfigPtr   Pointer to RAM section configuration structure
*                   (member of 'Mcu_ConfigType' struct).
*
* @return           Status signaling if the given RAM section has or has not been successfully initialized.
* @retval           E_OK        The RAM section check was successful.
* @retval           E_NOT_OK    The RAM section check was not successful.
*
*/
Std_ReturnType Mcu_Ipw_InitRamSection(const Mcu_RamConfigType * RamConfigPtr)
{
    /* Ram status variable. */
    Std_ReturnType RamStatus;

    switch(Ram_Ip_InitRamSection(RamConfigPtr))
    {
        case RAM_IP_STATUS_OK:
        {
            RamStatus = E_OK;
        }
        break;
        case RAM_IP_STATUS_NOT_OK:
        /* pass-through */
        default:
        {
            RamStatus = E_NOT_OK;
        }
        break;
    }

    /* Return the RAM state. */
    return RamStatus;

}
#endif /* ifndef MCU_MAX_NORAMCONFIGS */


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            This function initializes the clock structure on the common (main) platform.
* @details          This function initializes the clock structure by configuring the CGM module.
*                   Called by:
*                       - Mcu_InitClock() from HLD.
*
* @param[in]        ClockConfigPtr   Pointer to clock configuration structure
*                   (member of 'Mcu_ConfigType' struct).
*
* @return           void
*
*/
void Mcu_Ipw_InitClock(const Mcu_ClockConfigType * ClockConfigPtr)
{
    Clock_Ip_InitClock(ClockConfigPtr);
}
#endif /* (MCU_INIT_CLOCK == STD_ON) */


#if (MCU_INIT_CLOCK == STD_ON)
  #if (MCU_NO_PLL == STD_OFF)
/**
* @brief              This function activates the main PLL as the system clock source.
* @details            This function sets the PLL as the system clock and also enables monitoring.
*                     Called by:
*                       - Mcu_DistributePllClock() from HLD.
*
* @return           void
*
*/
void Mcu_Ipw_DistributePllClock(void)
{
    Clock_Ip_DistributePll();
}
  #endif /* (MCU_NO_PLL == STD_OFF) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#if (MCU_NO_PLL == STD_OFF)
/**
* @brief            This function returns the lock status of the PLL.
* @details          The user takes care that the PLL is locked by executing Mcu_GetPllStatus.
*                   If the MCU_NO_PLL is TRUE the MCU_GetPllStatus has to return
*                   MCU_PLL_STATUS_UNDEFINED.
*                   Called by:
*                       - Mcu_GetPllStatus() from HLD.
*
* @return           Provides the lock status of the PLL.
* @retval           MCU_PLL_STATUS_UNDEFINED   PLL Status is unknown.
* @retval           MCU_PLL_LOCKED             PLL is locked.
* @retval           MCU_PLL_UNLOCKED           PLL is unlocked.
*
*/
Mcu_PllStatusType Mcu_Ipw_GetPllStatus(void)
{
    /* PLL status variable. */
    Mcu_PllStatusType PllStatus;

    switch(Clock_Ip_GetPllStatus())
    {
        case CLOCK_IP_PLL_LOCKED:
        {
            PllStatus = MCU_PLL_LOCKED;
        }
        break;
        case CLOCK_IP_PLL_UNLOCKED:
        {
            PllStatus = MCU_PLL_UNLOCKED;
        }
        break;
        case CLOCK_IP_PLL_STATUS_UNDEFINED:
        default:
        {
            PllStatus = MCU_PLL_STATUS_UNDEFINED;
        }
        break;
    }

    /* Return the PLL status. */
    return PllStatus;
}
#endif /* (MCU_NO_PLL == STD_OFF) */

#ifdef MCU_GET_CLOCK_FREQUENCY_API
#if (MCU_GET_CLOCK_FREQUENCY_API == STD_ON)
/**
* @brief            This function returns the frequency of a given clock.
* @details          The function returns the frequency of a given clock which is request by user.
*                   Called by:
*                       - Mcu_GetClockFrequency() from HLD.
*
* @param[in]        ClockName   Name of the clock source for which need to get frequency.
*
* @return           Provides the frequency value of a source clock.
*
*/
uint64 MCU_Ipw_GetClockFrequency(Clock_Ip_NameType ClockName)
{
    return Clock_Ip_GetClockFrequency(ClockName);
}
#endif /* (MCU_GET_CLOCK_FREQUENCY_API == STD_ON) */
#endif /* MCU_GET_CLOCK_FREQUENCY_API */

/**
* @brief            This function initializes the mode structure.
* @details          This function initializes the mode structure by configuring the MC_ME module.
*                   Called by:
*                       - Mcu_SetMode() from HLD.
*
* @param[in]        ModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
*/
void Mcu_Ipw_SetMode(const Mcu_ModeConfigType * ModeConfigPtr)
{
    /* ASR 4.3.1: "Mcu_SetMode" has to be "concurrency-safe" */
    SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_00();

    Power_Ip_SetMode(ModeConfigPtr);
    
    SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_00();
}


#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*                   Called by:
*                       - Mcu_PerformReset() from HLD.
*
* @param[in]        HwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
*/
void Mcu_Ipw_PerformReset(const Mcu_HwIPsConfigType * HwIPsConfigPtr)
{
    /*
     *  Performs a microcontroller reset.
     *  A RESET mode requested via the ME_MCTL register is passed to the MC_RGM, which generates a
     *  global system reset and initiates the reset sequence.
     */

    Power_Ip_PerformReset(HwIPsConfigPtr);
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_GetResetReason() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
Mcu_ResetType Mcu_Ipw_GetResetReason(void)
{
    return (Mcu_ResetType)Power_Ip_GetResetReason();

}

/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_GetResetReason() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
Mcu_RawResetType Mcu_Ipw_GetResetRawValue(void)
{
    Power_Ip_RawResetType ResetReason;

    ResetReason = Power_Ip_GetResetRawValue();
    return (Mcu_RawResetType)ResetReason;
}

#if (MCU_GET_RAM_STATE_API == STD_ON)
Mcu_RamStateType Mcu_Ipw_GetRamState(void)
{
    /* Ram state variable. */
    Mcu_RamStateType RamState;

    switch(Ram_Ip_GetRamState())
    {
        case RAM_IP_RAMSTATE_VALID:
        {
            RamState = MCU_RAMSTATE_VALID;
        }
        break;
        case RAM_IP_RAMSTATE_INVALID:
        /* pass-through */
        default:
        {
            RamState = MCU_RAMSTATE_INVALID;
        }
        break;
    }

    /* Return the RAM state. */
    return RamState;
}
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

#ifdef MCU_GET_MIDR_API
  #if (MCU_GET_MIDR_API == STD_ON)
/* Return value of MIDR register */
void Mcu_Ipw_GetMidrStructure(Mcu_MidrReturnType * MidrPtr)
{
    uint8 Index;
    const SIUL2_Type * const Siul2BasePtrs[SIUL2_INSTANCE_COUNT] = IP_SIUL2_BASE_PTRS;

    for (Index = 0U; Index < SIUL2_INSTANCE_COUNT; ++Index)
    {
        MidrPtr[Index].Midr1 = Siul2BasePtrs[Index]->MIDR1;
        MidrPtr[Index].Midr2 = Siul2BasePtrs[Index]->MIDR2;
        MidrPtr[Index].Midr3 = Siul2BasePtrs[Index]->MIDR3;
        MidrPtr[Index].Midr4 = Siul2BasePtrs[Index]->MIDR4;
    }
}
#endif /* (MCU_GET_MIDR_API == STD_ON) */
#endif /* MCU_GET_MIDR_API */


#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
/* Function disable clock monitor */
void Mcu_Ipw_DisableCmu(Clock_Ip_NameType ClockName)
{
    Clock_Ip_DisableClockMonitor(ClockName);
}
#endif /* (MCU_DISABLE_CMU_API == STD_ON) */
#endif /* MCU_DISABLE_CMU_API */

#if (MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS == STD_ON)
void Mcu_Ipw_ClockNotificationsCallback(Clock_Ip_NotificationType Notification, Clock_Ip_NameType ClockName)
{
    (void)ClockName;

    switch(Notification)
    {
        case CLOCK_IP_CMU_ERROR:
        {
            Mcu_ClkSrcFailureNotification(ClockName);
        }
        break;

        case CLOCK_IP_REPORT_TIMEOUT_ERROR:
        {
#if (defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF))
            Mcu_Macro_ReportDemTimeoutError();
        }
        break;
        case CLOCK_IP_REPORT_FXOSC_CONFIGURATION_ERROR:
        {
            Mcu_Macro_ReportDemFxoscConfigurationError();
        }
        break;
        case CLOCK_IP_REPORT_CLOCK_MUX_SWITCH_ERROR:
        {
            Mcu_Macro_ReportDemClockMuxSwitchError();
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
        }
        break;

        case CLOCK_IP_RAM_MEMORY_CONFIG_ENTRY:
        {
#if (defined(MCU_DISABLE_RAM_CONFIG) && (MCU_DISABLE_RAM_CONFIG == STD_OFF))
        #ifdef MCU_PREPARE_MEMORY_CONFIG
            /* The exit point of the FLASH and RAM controllers configuration. */
            MCU_PREPARE_MEMORY_CONFIG(MCU_RAM_MEMORY_CONFIG_ENTRY_POINT);
        #endif
        }
        break;
        case CLOCK_IP_RAM_MEMORY_CONFIG_EXIT:
        {
        #ifdef MCU_PREPARE_MEMORY_CONFIG
            /* The exit point of the FLASH and RAM controllers configuration. */
            MCU_PREPARE_MEMORY_CONFIG(MCU_RAM_MEMORY_CONFIG_EXIT_POINT);
        #endif
#endif /* (MCU_DISABLE_RAM_CONFIG == STD_OFF) */
        }
        break;

        case CLOCK_IP_FLASH_MEMORY_CONFIG_ENTRY:
        {
#if (defined(MCU_DISABLE_FLASH_CONFIG) && (MCU_DISABLE_FLASH_CONFIG == STD_OFF))
        #ifdef MCU_PREPARE_MEMORY_CONFIG
            /* The entry point of the FLASH and RAM controllers configuration. */
            MCU_PREPARE_MEMORY_CONFIG(MCU_FLASH_MEMORY_CONFIG_ENTRY_POINT);
        #endif
        }
        break;
        case CLOCK_IP_FLASH_MEMORY_CONFIG_EXIT:
        {
        #ifdef MCU_PREPARE_MEMORY_CONFIG
            /* The exit point of the FLASH and RAM controllers configuration. */
            MCU_PREPARE_MEMORY_CONFIG(MCU_FLASH_MEMORY_CONFIG_EXIT_POINT);
        #endif
#endif /* (MCU_DISABLE_FLASH_CONFIG == STD_OFF) */
        }
        break;

        default:
        {
            /* Notification is not consumed HLD layer (it's not enabled from MCU component) */
        }
        break;
    }
}
#endif /* (MCU_IPW_ENABLE_CLOCK_NOTIFICATIONS == STD_ON) */

#if ((defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)) || (defined(MCU_ERROR_ISR_NOTIFICATION)) || (defined(MCU_PMC_NOTIFICATION)) || (defined(MCU_PMC_AE_NOTIFICATION)))
void Mcu_Ipw_ReportPowerErrorsCallback(Power_Ip_ReportErrorType Error, uint8 ErrorCode)
{
    switch(Error)
    {
        case POWER_IP_REPORT_TIMEOUT_ERROR:
        {
            (void)ErrorCode;
        #if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            Mcu_Macro_ReportDemTimeoutError();
        #endif
        }
        break;
        case POWER_IP_ISR_ERROR:
        {
        #ifdef MCU_ERROR_ISR_NOTIFICATION
            MCU_ERROR_ISR_NOTIFICATION(ErrorCode);
        #endif
        }
        break;
        case POWER_IP_PMC_ERROR:
        {
        #ifdef MCU_PMC_NOTIFICATION
            MCU_PMC_NOTIFICATION((Mcu_PowerManagementEventType)ErrorCode);
        #endif
        }
        break;
        case POWER_IP_ISR_VOLTAGE_HVD_VDDINT_DETECT:
        case POWER_IP_ISR_VOLTAGE_HVD_15_DETECT:
        case POWER_IP_ISR_VOLTAGE_HVD_VDD_DETECT:
        case POWER_IP_ISR_VOLTAGE_LVD_VDDC_DETECT:
        case POWER_IP_ISR_VOLTAGE_LVD_VLS_DETECT:
        {
        #ifdef MCU_PMC_AE_NOTIFICATION
            MCU_PMC_AE_NOTIFICATION(Error,ErrorCode);
        #endif
        }
        break;
        default:
        {
            /* Reporting errors mechanism */
        }
        break;
    }
}
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#if (defined(MCU_DISABLE_DEM_REPORT_ERROR_STATUS) && (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF))
void Mcu_Ipw_ReportRamErrorsCallback(Ram_Ip_RamReportErrorType Error, uint8 ErrorCode)
{
    switch(Error)
    {
        case RAM_IP_REPORT_TIMEOUT_ERROR:
        {
            (void)ErrorCode;
        #if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            Mcu_Macro_ReportDemTimeoutError();
        #endif
        }
        break;
        default:
        {
            /* Reporting errors mechanism */
        }
        break;
    }
}
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#ifdef MCU_EMIOS_CONFIGURE_GPREN_API
#if (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON)
void Mcu_Ipw_EmiosConfigureGpren(uint8 Module, uint8 Value)
{
    eMIOS_Type *const EmiosBasePtrs[eMIOS_INSTANCE_COUNT] = IP_eMIOS_BASE_PTRS;
    
    /* Enter critical region*/
    SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_02();

    if (Value == MCU_EMIOS_GPREN_BIT_ENABLE)
    {
        EmiosBasePtrs[Module]->MCR |= MCU_EMIOS_MCR_GPREN_MASK32;
    }
    else
    {
        EmiosBasePtrs[Module]->MCR &= (~MCU_EMIOS_MCR_GPREN_MASK32);
    }

    /* Exit critical region. */
    SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_02();
}
#endif /* (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) */
#endif /* MCU_EMIOS_CONFIGURE_GPREN_API */

#ifdef MCU_SLEEPONEXIT_SUPPORT
  #if (MCU_SLEEPONEXIT_SUPPORT == STD_ON)
/**
* @brief            This function disable/enable SleepOnExit.
* @details          Disable/enable Sleep on exit when returning from Handler mode to Thread mode.
*                   Called by:
*                       - Mcu_CM4_SleepOnExit() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
void Mcu_Ipw_SleepOnExit(Mcu_SleepOnExitType SleepOnExit)
{
    if(MCU_SLEEP_ON_EXIT_DISABLED == (Mcu_SleepOnExitType)SleepOnExit)
    {
        Power_Ip_DisableSleepOnExit();
    }
    else
    {
        Power_Ip_EnableSleepOnExit();
    }
}
  #endif
#endif

#ifdef MCU_PMCAECONFIG_API
#if (MCU_PMCAECONFIG_API == STD_ON)
/**
* @brief            This function configure the Power Management Controller AE.
* @details          This function configure the Power Management Controller AE of
*                   the microcontroller.
*                   Called by:
*                       - Mcu_PmcAeConfig() from HLD.
*
* @param[in]        HwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
*/
void Mcu_Ipw_PmcAeConfig(const Mcu_HwIPsConfigType * HwIPsConfigPtr)
{
    Power_Ip_PmcAeConfig(HwIPsConfigPtr);
}
#endif /* (MCU_PMCAECONFIG_API == STD_ON) */
#endif

#ifdef MCU_AECRESETCONFIG_API
#if (MCU_AECRESETCONFIG_API == STD_ON)
/**
* @brief            This function configure the reset generator AE.
* @details          This function configure the reset generator AE of
*                   the microcontroller.
*                   Called by:
*                       - Mcu_AecResetConfig() from HLD.
*
* @param[in]        HwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
*/
void Mcu_Ipw_AecResetConfig(const Mcu_HwIPsConfigType * HwIPsConfigPtr)
{
    Power_Ip_AecResetConfig(HwIPsConfigPtr);
}
#endif /* (MCU_AECRESETCONFIG_API == STD_ON) */
#endif

#ifdef MCU_LASTMILE_SUPPORT
  #if (STD_ON == MCU_LASTMILE_SUPPORT)
/**
* @brief            This function enable Last Mile regulator.
* @details          Enable Last Mile to provide voltage to core and flash.
*
* @param[in]        None
*
* @return           void
*
*/
void Mcu_Ipw_LastMileEnable(boolean BJTused)
{
    Power_Ip_EnableLastMile(BJTused);
}

/**
* @brief            This function disable Last Mile regulator.
* @details          Disable Last Mile to provide voltage to core and flash from Boot regulator.
*
* @param[in]        None
*
* @return           void
*
*/
void Mcu_Ipw_LastMileDisable(void)
{
    Power_Ip_DisableLastMile();
}
  #endif
#endif

#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

