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
*   @file       Power_Ip.c
*   @version    5.0.0
*
*   @brief
*   @brief   POWER driver implementations.
*   @details POWER driver implementations.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
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
#include "Power_Ip_Private.h"
#include "Power_Ip.h"
#include "Power_Ip_MC_ME.h"
#include "Power_Ip_MC_RGM.h"
#include "Power_Ip_PMC.h"
#include "Power_Ip_FLASH.h"
#include "Power_Ip_CortexM7.h"
#include "Power_Ip_DCM_GPR.h"

#ifdef POWER_IP_AECRESETCONFIG_API
#if (POWER_IP_AECRESETCONFIG_API == STD_ON)
#include "Power_Ip_AEC.h"
#endif
#endif
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_VENDOR_ID_C                      43
#define POWER_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_SW_MAJOR_VERSION_C               5
#define POWER_IP_SW_MINOR_VERSION_C               0
#define POWER_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip.c file and Power_Ip_Private.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_PRIVATE_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip_Private.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip_Private.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_Private.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_PRIVATE_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_MC_ME.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_MC_ME_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip_MC_ME.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip_MC_ME.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip_MC_ME.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_MC_ME.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_MC_ME_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_MC_ME_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_MC_ME_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip_MC_ME.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_MC_RGM.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_MC_RGM_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip_MC_RGM.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip_MC_RGM.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip_MC_RGM.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_MC_RGM.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_MC_RGM_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_MC_RGM_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip_MC_RGM.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_PMC.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_PMC_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip_PMC.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip_PMC.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PMC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PMC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip_PMC.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_PMC.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_PMC_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_PMC_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_PMC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip_PMC.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_FLASH.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_FLASH_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip_FLASH.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip_FLASH.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_FLASH_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_FLASH_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_FLASH_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip_FLASH.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_FLASH.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_FLASH_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_FLASH_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_FLASH_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip_FLASH.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_CortexM7.h file are of the same vendor */
#if (POWER_IP_VENDOR_ID_C != POWER_IP_CORTEXM7_VENDOR_ID)
    #error "Power_Ip.c and Power_Ip_CortexM7.h have different vendor ids"
#endif

/* Check if Power_Ip.c file and Power_Ip_CortexM7.h file are of the same Autosar version */
#if ((POWER_IP_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_CORTEXM7_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AR_RELEASE_MINOR_VERSION_C != POWER_IP_CORTEXM7_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AR_RELEASE_REVISION_VERSION_C != POWER_IP_CORTEXM7_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip.c and Power_Ip_CortexM7.h are different"
#endif

/* Check if Power_Ip.c file and Power_Ip_CortexM7.h file are of the same Software version */
#if ((POWER_IP_SW_MAJOR_VERSION_C != POWER_IP_CORTEXM7_SW_MAJOR_VERSION) || \
     (POWER_IP_SW_MINOR_VERSION_C != POWER_IP_CORTEXM7_SW_MINOR_VERSION) || \
     (POWER_IP_SW_PATCH_VERSION_C != POWER_IP_CORTEXM7_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip.c and Power_Ip_CortexM7.h are different"
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Power Report Error Callback */
Power_Ip_ReportErrorsCallbackType Power_Ip_pfReportErrorsCallback = &Power_Ip_ReportPowerErrorsEmptyCallback;

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
static void Power_Ip_SetUserAccessAllowed(void);
#endif


#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))

#ifdef POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT
  #if (POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT == STD_ON)
static void Power_Ip_PrepareSocStandby(const Power_Ip_ModeConfigType * ModeConfigPtr);
  #endif
#endif

#endif

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
/* Set user access to power register allowed when run in Usermode */
static void Power_Ip_SetUserAccessAllowed(void)
{
#if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)
    OsIf_Trusted_Call(Power_Ip_MC_ME_SetUserAccessAllowed);
  #endif
#endif

#if (defined(MCAL_PMC_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE)
    OsIf_Trusted_Call(Power_Ip_PMC_SetUserAccessAllowed);
  #endif
#endif

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
  #if (defined(MCAL_C40ASF_REG_PROT_AVAILABLE))
    #if(STD_ON == MCAL_C40ASF_REG_PROT_AVAILABLE)
    OsIf_Trusted_Call(Power_Ip_FLASH_C40ASF_SetUserAccessAllowed);
    #endif
  #endif
#endif

#if (defined(MCAL_MC_RGM_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE)
    OsIf_Trusted_Call(Power_Ip_MC_RGM_SetUserAccessAllowed);
  #endif
#endif

#if (defined(MCAL_DCM_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_DCM_REG_PROT_AVAILABLE)
    OsIf_Trusted_Call(Power_Ip_DCM_GPR_SetUserAccessAllowed);
  #endif
#endif
}
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))

#ifdef POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT
  #if (POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT == STD_ON)
/* Prepare soc standby */
static void Power_Ip_PrepareSocStandby(const Power_Ip_ModeConfigType * ModeConfigPtr)
{
    #if (defined(POWER_IP_PMIC_PGOOD_SUPPORT) && (STD_ON == POWER_IP_PMIC_PGOOD_SUPPORT))
    if((boolean)TRUE == ModeConfigPtr->DcmGprConfigPtr->DcmGprUnderMcuControl)
    {
        Power_Ip_DCM_GPR_PMICBypasses(ModeConfigPtr->DcmGprConfigPtr->PGOODBypasses);
    }
    #endif
    
    /* Init Device Configuration Module General-Purpose Registers */
    Power_Ip_DCM_GPR_Config(ModeConfigPtr->DcmGprConfigPtr);

    if(((boolean)TRUE == ModeConfigPtr->DcmGprConfigPtr->GlobalPadkeeping) && \
       ((boolean)TRUE == ModeConfigPtr->DcmGprConfigPtr->DcmGprUnderMcuControl))
    {
        Power_Ip_DCM_GPR_GlobalPadkeepingConfig(POWER_IP_GLOBAL_PADKEEPING_ENABLED);
    }

    if (FALSE == Power_Ip_FLASH_HighVoltageOperationOngoing())
    {
        Call_Power_Ip_PMC_PrepareLowPowerEntry();
    }
    else
    {
#ifdef POWER_IP_ERROR_ISR_NOTIFICATION
        POWER_IP_ERROR_ISR_NOTIFICATION(POWER_IP_E_FLASH_HV_OPERATION_ONGOING);
#else
        Power_Ip_ReportPowerErrors(POWER_IP_ISR_ERROR, POWER_IP_E_FLASH_HV_OPERATION_ONGOING);
#endif
    }
}
  #endif
#endif /* POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT */

#endif /* ((POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)) */


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/



/**
* @brief            This function initializes the mode structure.
* @details          This function initializes the mode structure by configuring the MC_ME module.
*
* @param[in]        ModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
* @implements Power_Ip_SetMode_Activity
*
*/
void Power_Ip_SetMode(const Power_Ip_ModeConfigType * ModeConfigPtr)
{
    Power_Ip_PowerModeType PowerMode;

    POWER_IP_DEV_ASSERT(NULL_PTR != ModeConfigPtr);

    PowerMode = ModeConfigPtr->PowerMode;

    /* Step 1: Enable Partitions clock base on configuration of McuPartitionClockEnable.  */
    Power_Ip_MC_ME_EnablePartitionClock(ModeConfigPtr->McMeModeConfigPtr);

#if (defined(POWER_IP_RESET_DOMAINS_SUPPORTED) && (POWER_IP_RESET_DOMAINS_SUPPORTED == STD_ON))
    /* Step 2: Enable interconnect interface of Software Reset Domain base on configuration of McuPartitionResetEnable. */
    Call_Power_Ip_MC_RGM_EnableResetDomain(ModeConfigPtr->McRgmModeConfigPtr);
#endif

#if (defined(POWER_IP_HAS_OUTPUT_SAFE_STATE))
  #if (POWER_IP_HAS_OUTPUT_SAFE_STATE == STD_ON)
    /* Step 3: Disable Output safe stating base on configuration of McuPartitionClockEnable. */
    Power_Ip_MC_ME_DisablePartitionOutputSafe(ModeConfigPtr->McMeModeConfigPtr);
  #endif
#endif

    /* Step 4: Configure Cores address, Cores clock and COFB clock */
    Power_Ip_MC_ME_ConfigCoreCOFBClock(ModeConfigPtr->McMeModeConfigPtr);

#if (defined(POWER_IP_RESET_DOMAINS_SUPPORTED) && (POWER_IP_RESET_DOMAINS_SUPPORTED == STD_ON))
    /* Step 5: Configure and check configure Core and COFB reset */
    /* Request new mode configuration from MC_RGM. */
    Call_Power_Ip_MC_RGM_ModeConfig(ModeConfigPtr->McRgmModeConfigPtr);
    /* Check new mode configuration from MC_RGM. */
    Call_Power_Ip_MC_RGM_CheckModeConfig(ModeConfigPtr->McRgmModeConfigPtr);

    /* Step 6: Disable interconnect interface of Software Reset Domain base on configuration of McuPartitionResetEnable. */
    Call_Power_Ip_MC_RGM_DisableResetDomain(ModeConfigPtr->McRgmModeConfigPtr);
#endif /* (POWER_IP_RESET_DOMAINS_SUPPORTED == STD_ON) */

    /* Step 7: Disable Partitions clock base on configuration of McuPartitionClockEnable.  */
    Power_Ip_MC_ME_DisablePartitionClock(ModeConfigPtr->McMeModeConfigPtr);

#if (defined(POWER_IP_HAS_OUTPUT_SAFE_STATE))
  #if (POWER_IP_HAS_OUTPUT_SAFE_STATE == STD_ON)
    /* Step 8: Enable Output safe stating base on configuration of McuPartitionClockEnable. */
    Power_Ip_MC_ME_EnablePartitionOutputSafe(ModeConfigPtr->McMeModeConfigPtr);
  #endif
#endif

    if ( (POWER_IP_DEST_RESET_MODE == PowerMode) || (POWER_IP_FUNC_RESET_MODE == PowerMode) )
    {
        Power_Ip_MC_ME_SocTriggerResetEvent(PowerMode);
    }
#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
    else if (POWER_IP_CORE_STANDBY_MODE == PowerMode)
    {
        /* External assumption: The application will make sure that the core is prepared for standby entry. */
        Power_Ip_MC_ME_CoreStandbyEntry(ModeConfigPtr);
    }
#ifdef POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT
  #if (POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT == STD_ON)
    else if ( (POWER_IP_SOC_PREPARE_STANDBY_MODE == PowerMode) || (POWER_IP_SOC_PREPARE_FAST_STANDBY_MODE == PowerMode) )
    {
        /* External assumption: The application will disable the PLL (and optionally disable FIRC/SIRC/SXOSC/FXOSC
         * as per power-consumption requirements in order to reduce power consumption in STANDBY mode) and ensure
         * that no flash high-voltage operations are ongoing. */

        Power_Ip_PrepareSocStandby(ModeConfigPtr);
    }
  #endif
#endif
    else if ( (POWER_IP_SOC_STANDBY_MODE == PowerMode) || (POWER_IP_SOC_FAST_STANDBY_MODE == PowerMode) )
    {
        /* External assumption: The application will program the necessary wakeup IP(s). */
        Power_Ip_MC_ME_SocStandbyEntry(ModeConfigPtr);
    }
#ifdef POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT
  #if (POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT == STD_ON)
    else if ( (POWER_IP_STANDBY_MODE == PowerMode) || (POWER_IP_FAST_STANDBY_MODE == PowerMode) )
    {
        /* Step 1: prepare soc standby */
        Power_Ip_PrepareSocStandby(ModeConfigPtr);
        /* External assumption: The application will program the necessary wakeup IP(s). */
        /* Step 2: set soc standby */
        Power_Ip_MC_ME_SocStandbyEntry(ModeConfigPtr);
    }
  #endif
#endif /* POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT */
#endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
    else
    {
        /* Nothing else to be done. Ignore the power mode. */
    }
}

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
/**
* @brief            This function returns the previous mode.
* @details          This function returns the previous mode.
*
* @return           Status of the previous mode.
*
* @implements Power_Ip_GetPreviousMode_Activity
*
*/
Power_Ip_PowerModeType Power_Ip_GetPreviousMode(void)
{
    Power_Ip_PowerModeType PowerPrevMode;

    PowerPrevMode = Power_Ip_MC_ME_GetPreviousMode();

    return PowerPrevMode;
}
#endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */

#if (POWER_IP_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*
* @param[in]        HwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
* @implements Power_Ip_PerformReset_Activity
*
*/
void Power_Ip_PerformReset(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr)
{

    POWER_IP_DEV_ASSERT(NULL_PTR != HwIPsConfigPtr);
    /*
     *  Performs a microcontroller reset.
     *  A RESET mode requested via the ME_MCTL register is passed to the MC_RGM, which generates a
     *  global system reset and initiates the reset sequence.
     */

    Call_Power_Ip_MC_RGM_PerformReset(HwIPsConfigPtr->McRgmConfigPtr);
}
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */

/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*
* @param[in]        None
*
* @return           void
*
* @implements Power_Ip_GetResetReason_Activity
*
*/
Power_Ip_ResetType Power_Ip_GetResetReason(void)
{
    Power_Ip_ResetType ResetReason = MCU_RESET_UNDEFINED;
#if (defined(POWER_IP_RESET_DURING_STANDBY_SUPPORTED))
  #if (POWER_IP_RESET_DURING_STANDBY_SUPPORTED == STD_ON)
    #if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
    Power_Ip_PowerModeType PreviousMode;
    #endif /*(POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
  #endif
#endif

#if (defined(POWER_IP_RESET_DURING_STANDBY_SUPPORTED))
  #if (POWER_IP_RESET_DURING_STANDBY_SUPPORTED == STD_ON)
    #if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
    if ( 0U != Call_Power_Ip_MC_RGM_ResetDuringStandby() )
    {
        ResetReason = MCU_WAKEUP_REASON;
    }
    else
    {
        PreviousMode = Power_Ip_MC_ME_GetPreviousMode();
        if ( POWER_IP_SOC_STANDBY_MODE == PreviousMode )
        {
            ResetReason = MCU_WAKEUP_REASON;
        }
        else
        {
    #endif
  #endif
#endif
            ResetReason = (Power_Ip_ResetType)Call_Power_Ip_MC_RGM_GetResetReason();
#if (defined(POWER_IP_RESET_DURING_STANDBY_SUPPORTED))
  #if (POWER_IP_RESET_DURING_STANDBY_SUPPORTED == STD_ON)
    #if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
        }
    }
    #endif
  #endif
#endif

    return ResetReason;
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
* @implements Power_Ip_GetResetRawValue_Activity
*
*/
Power_Ip_RawResetType Power_Ip_GetResetRawValue(void)
{
    Power_Ip_RawResetType ResetReason;

    /**  @violates @ref Mcu_IPW_c_REF_12 The comma operator shall not be used. */
    ResetReason = Call_Power_Ip_MC_RGM_GetResetRawValue();
    return ResetReason;
}

/**
* @brief            This function initializes the power module.
* @details
*
* @param[in]        HwIPsConfigPtr  Pointer to LLD configuration structure.
*
* @return           void
*
* @implements Power_Ip_Init_Activity
*
*/
void Power_Ip_Init(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr)
{
    POWER_IP_DEV_ASSERT(NULL_PTR != HwIPsConfigPtr);

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
    /* Set user access allowed for Power */
    Power_Ip_SetUserAccessAllowed();
#endif

#if (defined(POWER_IP_DISABLE_RGM_INIT) && (STD_OFF == POWER_IP_DISABLE_RGM_INIT))
    /* Init MCU MC_RGM part of the registers: MC_RGM_FERD, MC_RGM_FEAR, MC_RGM_FESS, MC_RGM_FBRE, clear FES & DES status registers. */
    Call_Power_Ip_MC_RGM_ResetInit(HwIPsConfigPtr->McRgmConfigPtr);
#endif

#if (defined(POWER_IP_DISABLE_PMC_INIT) && (STD_OFF == POWER_IP_DISABLE_PMC_INIT))
    /* Init Power Management Controller digital interface */
    Power_Ip_PMC_PowerInit(HwIPsConfigPtr->PMCConfigPtr);
#endif

    /* Disable the padkeeping for every Power Init */
    Power_Ip_DCM_GPR_GlobalPadkeepingConfig(POWER_IP_GLOBAL_PADKEEPING_DISABLED);

    /* Avoid compiler warning */
    (void)HwIPsConfigPtr;
}

#ifdef POWER_IP_PMCAECONFIG_API
#if (POWER_IP_PMCAECONFIG_API == STD_ON)
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
*
*
*/
void Power_Ip_PmcAeConfig(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr)
{
    Power_Ip_PMC_AE_PowerInit(HwIPsConfigPtr->PMCConfigPtr);
}
#endif /* (POWER_IP_PMCAECONFIG_API == STD_ON) */
#endif

#ifdef POWER_IP_AECRESETCONFIG_API
#if (POWER_IP_AECRESETCONFIG_API == STD_ON)
/**
* @brief            This function configure reset generator (AEC_AE)
* @details          This function configure reset generator (AEC_AE)
*                   Called by:
*                       - Mcu_AecResetConfig() from HLD.
*
* @param[in]        HwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
*
*
*/
void Power_Ip_AecResetConfig(const Power_Ip_HwIPsConfigType * HwIPsConfigPtr)
{
    Power_Ip_AEC_Reset_Config(HwIPsConfigPtr->AECConfigPtr);
}
#endif /* (POWER_IP_AECRESETCONFIG_API == STD_ON) */
#endif

/**
* @brief            This function installs a callback for reporting errors from power driver.
* @details
*
* @param[in]        ReportErrorsCallback    Callback to be installed.
*
* @return           void
*
* @implements Power_Ip_InstallNotificationsCallback_Activity
*/
void Power_Ip_InstallNotificationsCallback(Power_Ip_ReportErrorsCallbackType ReportErrorsCallback)
{
    POWER_IP_DEV_ASSERT(NULL_PTR != ReportErrorsCallback);

    Power_Ip_pfReportErrorsCallback = ReportErrorsCallback;
}

#ifdef POWER_IP_SLEEPONEXIT_SUPPORT
  #if (POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON)
/**
* @brief        The function enable SLEEPONEXIT bit.
* @details      The function enable SLEEPONEXIT bit.
*
* @return void
*
* @implements Power_Ip_EnableSleepOnExit_Activity
*/
void Power_Ip_EnableSleepOnExit(void)
{
    Call_Power_Ip_CM7_EnableSleepOnExit();
}

/**
* @brief        The function disable SLEEPONEXIT bit.
* @details      The function disable SLEEPONEXIT bit.
*
* @return void
*
* @implements Power_Ip_DisableSleepOnExit_Activity
*/
void Power_Ip_DisableSleepOnExit(void)
{
    Call_Power_Ip_CM7_DisableSleepOnExit();
}
  #endif
#endif

#ifdef POWER_IP_LASTMILE_SUPPORT
  #if (STD_ON == POWER_IP_LASTMILE_SUPPORT)
/**
* @brief        The function enable LMEN bit.
* @details      The function enable LMEN bit.
*
* @return void
*
*
*/
void Power_Ip_EnableLastMile(boolean BJTused)
{
  Power_Ip_PMC_EnableLastMile(BJTused);
}

/**
* @brief        The function disable LMEN bit.
* @details      The function disable LMEN bit.
*
* @return void
*
*
*/
void Power_Ip_DisableLastMile(void)
{
  Power_Ip_PMC_DisableLastMile();
}

  #endif
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
