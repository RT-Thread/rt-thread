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
*   @file       Clock_Ip_Pll.c
*   @version    5.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
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

#include "Clock_Ip_Private.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_PLL_VENDOR_ID_C                      43
#define CLOCK_IP_PLL_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_PLL_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_PLL_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_PLL_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_PLL_SW_MINOR_VERSION_C               0
#define CLOCK_IP_PLL_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Pll.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_PLL_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Pll.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Pll.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_PLL_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PLL_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_PLL_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Pll.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Pll.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_PLL_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_PLL_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_PLL_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Pll.c and Clock_Ip_Private.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

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
*                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"













/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void Clock_Ip_CallbackPllEmpty(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CallbackPllEmptyComplete(Clock_Ip_NameType PllName);
static void Clock_Ip_CallbackPllEmptyDisable(Clock_Ip_NameType PllName);





#ifdef CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
static void Clock_Ip_ResetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config);
static void Clock_Ip_SetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_NameType PllName);
static void Clock_Ip_EnablePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config);
#endif







#ifdef CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN
static void Clock_Ip_ResetPllRdivMfiMfnOdiv2Sdmen(Clock_Ip_PllConfigType const* Config);
static void Clock_Ip_SetPllRdivMfiMfnOdiv2Sdmen(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePllRdivMfiMfnOdiv2Sdmen(Clock_Ip_NameType PllName);
static void Clock_Ip_EnablePllRdivMfiMfnOdiv2Sdmen(Clock_Ip_PllConfigType const* Config);
#endif



/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

#define MCU_START_SEC_CODE
/* Clock start section code */

#include "Mcu_MemMap.h"


static void Clock_Ip_CallbackPllEmpty(Clock_Ip_PllConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}
static Clock_Ip_PllStatusReturnType Clock_Ip_CallbackPllEmptyComplete(Clock_Ip_NameType PllName)
{
    (void)PllName;
    /* No implementation */
    return STATUS_PLL_LOCKED;
}
static void Clock_Ip_CallbackPllEmptyDisable(Clock_Ip_NameType PllName)
{
    (void)PllName;
    /* No implementation */
}





#ifdef CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
/* Recommended unlock control accuracy when frequency modulation is bypassed */
#define CLOCK_IP_RECOMMENTED_ULKCTL_BYPASSED_FM     0U
/* Recommended unlock control accuracy when frequency modulation is not bypassed */
#define CLOCK_IP_RECOMMENTED_ULKCTL_NOT_BYPASSED_FM 1U
static void Clock_Ip_ResetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint8 DividerIndex;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable output dividers */
        for (DividerIndex = 0U; DividerIndex < Clock_Ip_apxPll[Instance].DivsNo; DividerIndex++)
        {
            Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex] &= ~PLL_PLLODIV_DE_MASK;
        }
        /* Power down PLL */
        Clock_Ip_apxPll[Instance].PllInstance->PLLCR |= PLL_PLLCR_PLLPD_MASK;
    }
    else
    {
        (void)Instance;
        (void)DividerIndex;
    }
}
static void Clock_Ip_SetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint32 Value;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
#ifdef CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX
    #if (CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX == STD_ON)
            /* Name of the input reference clock */
            switch (Config->InputReference)
            {
                case FIRC_CLK:
                    /* Select input reference. */
                    Clock_Ip_apxPll[Instance].PllInstance->PLLCLKMUX = PLL_PLLCLKMUX_REFCLKSEL(CLOCK_IP_FIRC_PLL_REFERENCE);
                    break;
                case FXOSC_CLK:
                    /* Select input reference. */
                    Clock_Ip_apxPll[Instance].PllInstance->PLLCLKMUX = PLL_PLLCLKMUX_REFCLKSEL(CLOCK_IP_FXOSC_PLL_REFERENCE);
                    break;
                default:
                    /* Command is not implemented on this platform */
                    break;
            }
    #endif /*(CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX == STD_ON)*/
#endif /*CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX*/

            /* Configure PLL: predivider and multiplier */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLDV;
            Value &= ~(PLL_PLLDV_RDIV_MASK | PLL_PLLDV_MFI_MASK);
            Value |= (uint32) (PLL_PLLDV_RDIV(Config->Predivider) |
                              PLL_PLLDV_MFI(Config->MulFactorDiv));
            Clock_Ip_apxPll[Instance].PllInstance->PLLDV = Value;

            /* Set numerator fractional loop divider and sigma delta modulation */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLFD;
            Value &= ~(PLL_PLLFD_MFN_MASK | PLL_PLLFD_SDMEN_MASK);
            Value |=  PLL_PLLFD_MFN(Config->NumeratorFracLoopDiv);
            Value |= PLL_PLLFD_SDMEN(Config->SigmaDelta);
            Clock_Ip_apxPll[Instance].PllInstance->PLLFD = Value;

            /* Configure modulation */
            Value = (uint32) (PLL_PLLFM_SSCGBYP(Config->FrequencyModulationBypass)         |
                                PLL_PLLFM_SPREADCTL(Config->ModulationType)                |
                                PLL_PLLFM_STEPNO(Config->IncrementStep)                    |
                                PLL_PLLFM_STEPSIZE(Config->ModulationPeriod));
            Clock_Ip_apxPll[Instance].PllInstance->PLLFM = Value;

            /* Unlock Control Accuracy - accuracy necessary to achieve unlock. */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLCAL2;
            Value &= ~PLL_PLLCAL2_ULKCTL_MASK;
            Value |= PLL_PLLCAL2_ULKCTL((Config->FrequencyModulationBypass != 0U) ?  CLOCK_IP_RECOMMENTED_ULKCTL_BYPASSED_FM : CLOCK_IP_RECOMMENTED_ULKCTL_NOT_BYPASSED_FM);
            Clock_Ip_apxPll[Instance].PllInstance->PLLCAL2 = Value;

            /* Send command to enable PLL device. */
            Clock_Ip_apxPll[Instance].PllInstance->PLLCR &= ~PLL_PLLCR_PLLPD_MASK;
        }
    }
    else
    {
        (void)Instance;
        (void)Value;
    }
}

static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_NameType PllName)
{
    Clock_Ip_PllStatusReturnType PllStatus = STATUS_PLL_LOCKED;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 Instance = Clock_Ip_au8ClockFeatures[PllName][CLOCK_IP_MODULE_INSTANCE];

    if (0U == (Clock_Ip_apxPll[Instance].PllInstance->PLLCR & PLL_PLLCR_PLLPD_MASK))
    {
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            PllLockStatus = ((Clock_Ip_apxPll[Instance].PllInstance->PLLSR & PLL_PLLSR_LOCK_MASK) >> PLL_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((0U == PllLockStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            PllStatus = STATUS_PLL_UNLOCKED;
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PllName);
        }
    }
    else
    {
        PllStatus = STATUS_PLL_NOT_ENABLED;
    }

    return PllStatus;
}
static void Clock_Ip_EnablePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Configure PLL. */
        if (1U == Config->Enable)
        {
            /* Send command to enable PLL device. */
            Clock_Ip_apxPll[Instance].PllInstance->PLLCR &= ~PLL_PLLCR_PLLPD_MASK;
        }
    }
    else
    {
        (void)Instance;
    }
}
#endif







#ifdef CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN
static void Clock_Ip_ResetPllRdivMfiMfnOdiv2Sdmen(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint8 DividerIndex;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable output dividers */
        for (DividerIndex = 0U; DividerIndex < Clock_Ip_apxPll[Instance].DivsNo; DividerIndex++)
        {
            Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex] &= ~PLL_PLLODIV_DE_MASK;
        }
        /* Power down PLL */
        Clock_Ip_apxPll[Instance].PllInstance->PLLCR |= PLL_PLLCR_PLLPD_MASK;
    }
    else
    {
        (void)Instance;
        (void)DividerIndex;
    }

}

static void Clock_Ip_SetPllRdivMfiMfnOdiv2Sdmen(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint32 Value;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            /* Configure PLL: predivider and multiplier */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLDV;
            Value &= ~(PLL_PLLDV_RDIV_MASK | PLL_PLLDV_MFI_MASK);
            Value |= (uint32) (PLL_PLLDV_RDIV(Config->Predivider) |
                              PLL_PLLDV_MFI(Config->MulFactorDiv));
            Clock_Ip_apxPll[Instance].PllInstance->PLLDV = Value;
            Clock_Ip_apxPll[Instance].PllInstance->PLLCR &= ~PLL_PLLCR_PLLPD_MASK;
        }
    }
    else
    {
        (void)Instance;
        (void)Value;
    }
}

static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePllRdivMfiMfnOdiv2Sdmen(Clock_Ip_NameType PllName)
{
    Clock_Ip_PllStatusReturnType PllStatus = STATUS_PLL_LOCKED;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 Instance = Clock_Ip_au8ClockFeatures[PllName][CLOCK_IP_MODULE_INSTANCE];

    if (0U == (Clock_Ip_apxPll[Instance].PllInstance->PLLCR & PLL_PLLCR_PLLPD_MASK))
    {
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            PllLockStatus = ((Clock_Ip_apxPll[Instance].PllInstance->PLLSR & PLL_PLLSR_LOCK_MASK) >> PLL_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((0U == PllLockStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            PllStatus = STATUS_PLL_UNLOCKED;
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PllName);
        }
    }
    else
    {
        PllStatus = STATUS_PLL_NOT_ENABLED;
    }
    return PllStatus;
}
static void Clock_Ip_EnablePllRdivMfiMfnOdiv2Sdmen(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Configure PLL. */
        if (1U == Config->Enable)
        {
            /* Send command to enable PLL device. */
            Clock_Ip_apxPll[Instance].PllInstance->PLLCR &= ~PLL_PLLCR_PLLPD_MASK;
        }
    }
    else
    {
        (void)Instance;
    }
}
#endif




/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
















/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/
/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"
const Clock_Ip_PllCallbackType Clock_Ip_axPllCallbacks[CLOCK_IP_PLL_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_CallbackPllEmpty,            /* Reset */
        &Clock_Ip_CallbackPllEmpty,            /* Set */
        &Clock_Ip_CallbackPllEmptyComplete,    /* Complete */
        &Clock_Ip_CallbackPllEmpty,            /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,     /* Disable */
    },




#ifdef CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
    {
        &Clock_Ip_ResetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,              /* Reset */
        &Clock_Ip_SetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,                /* Set */
        &Clock_Ip_CompletePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,           /* Complete */
        &Clock_Ip_EnablePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,             /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,                                                 /* Disable */
    },
#endif







#ifdef CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN
    {
        &Clock_Ip_ResetPllRdivMfiMfnOdiv2Sdmen,              /* Reset */
        &Clock_Ip_SetPllRdivMfiMfnOdiv2Sdmen,                /* Set */
        &Clock_Ip_CompletePllRdivMfiMfnOdiv2Sdmen,           /* Complete */
        &Clock_Ip_EnablePllRdivMfiMfnOdiv2Sdmen,             /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,                   /* Disable */
    },
#endif



};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
