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
*   @file       Clock_Ip.c
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
#include "OsIf.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_VENDOR_ID_C                      43
#define CLOCK_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_SW_MINOR_VERSION_C               0
#define CLOCK_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip.c and Clock_Ip_Private.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Clock_Ip.c file and OsIf.h file are of the same Autosar version */
#if ((CLOCK_IP_AR_RELEASE_MAJOR_VERSION_C    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_MINOR_VERSION_C    != OSIF_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip.c and OsIf.h are different"
#endif
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*!
 * @brief Clock ip driver context
 */
typedef struct
{
    boolean ClockTreeIsConsumingPll;                /**< Clock tree is using a PLL output. */
    boolean WaitStatesAreSupported;                 /**< Wait states are supported. */
    uint8 HwPllsNo;                                 /**< Number of plls . */
    uint8 HwDfsNo;                                  /**< Number of fractional dividers . */

} Clock_Ip_DriverContextType;

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/
/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

#if !((CLOCK_IP_CMU_INFO_SIZE > 0U) || defined(CLOCK_IP_CGU_INTERRUPT))
static const Clock_Ip_ClockConfigType *Clock_Ip_pxConfig;                                           /* Reference to the current clock configuration */
#endif

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"
/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/
/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_BOOLEAN
#include "Mcu_MemMap.h"

static boolean FunctionWasCalled;

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

static Clock_Ip_DriverContextType DriverContext;

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"
/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/
/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

#if (CLOCK_IP_CMU_INFO_SIZE > 0U) || defined(CLOCK_IP_CGU_INTERRUPT)
const Clock_Ip_ClockConfigType *Clock_Ip_pxConfig;                                           /* Reference to the current clock configuration */
#endif

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_BOOLEAN
#include "Mcu_MemMap.h"


/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_BOOLEAN
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_8
#include "Mcu_MemMap.h"

uint8 Clock_Ip_FreqIds[CLOCK_IP_FEATURE_NAMES_NO];

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_8
#include "Mcu_MemMap.h"


/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

static void Clock_Ip_NotificatonsEmptyCallback(Clock_Ip_NotificationType Notification, Clock_Ip_NameType ClockName);
static void Clock_Ip_ResetClockConfiguration(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_UpdateDriverContext(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CallEmptyCallbacks(void);

#if ( defined(CLOCK_IP_HAS_RAM_WAIT_STATES) || defined(CLOCK_IP_HAS_FLASH_WAIT_STATES) )
static void Clock_Ip_SetWaitStates(void);
#endif

#if (defined(CLOCK_IP_DEV_ERROR_DETECT) && (CLOCK_IP_DEV_ERROR_DETECT == STD_ON))
static void Clock_Ip_CheckClockConfiguration(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckIrcoscClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckXoscClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckPllClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckExtSigClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckSelectorClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckDividerClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckDividerTriggerClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckFracDividerClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckGateClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckPcfsClocks(Clock_Ip_ClockConfigType const * Config);
static void Clock_Ip_CheckCmuClocks(Clock_Ip_ClockConfigType const * Config);
#endif

/* Clock Report Error Callback */
static Clock_Ip_NotificationsCallbackType Clock_Ip_pfkNotificationsCallback = &Clock_Ip_NotificatonsEmptyCallback;

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_NotificatonsEmptyCallback.
 * Description   : Notification clock call back.
 *
 *END**************************************************************************/
static void Clock_Ip_NotificatonsEmptyCallback( Clock_Ip_NotificationType Notification,
                                                Clock_Ip_NameType ClockName
                                               )
{
    /* No implementation */
    (void)Notification;
    (void)ClockName;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_UpdateDriverContext.
 * Description   : Updates context of the driver, internal memory, clock objects.
 *
 *END**************************************************************************/
static void Clock_Ip_UpdateDriverContext(Clock_Ip_ClockConfigType const * Config)
{
    uint8 Index;
    (void)Config;
    /* Initialize clock objects */
    Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND);

    for (Index = 0U; Index < Config->ExtClksCount; Index++)    /* Set external signal frequency. */
    {
        Clock_Ip_SetExternalSignalFrequency((*(Config->ExtClks))[Index].Name, (*(Config->ExtClks))[Index].Value);
    }

    /* Call empty callbacks */
    Clock_Ip_CallEmptyCallbacks();

    for (Index = 1U; Index < Config->ConfigureFrequenciesCount; Index++)
    {
        Clock_Ip_FreqIds[(*(Config->ConfiguredFrequencies))[Index].Name] = Index;
    }
}

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
    #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckIrcoscClocks
 * Description   : Checks clock names from ircoscs array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckIrcoscClocks(Clock_Ip_ClockConfigType const * Config)
{
#if CLOCK_IP_IRCOSCS_COUNT > 1U
    uint32 Index;
#endif
    if (Config->IrcoscsCount != 0U)
    {
#if CLOCK_IP_IRCOSCS_COUNT > 1U
        if (Config->IrcoscsCount > 1U)
        {
            for (Index = 0U; Index < (Config->IrcoscsCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->Ircoscs))[Index].Name) < ((uint32)(*(Config->Ircoscs))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Ircoscs))[Index].Name] & CLOCK_IP_IRCOSC_OBJECT) != 0U);
            }
        }
#endif
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Ircoscs))[Config->IrcoscsCount - 1U].Name] & CLOCK_IP_IRCOSC_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckXoscClocks
 * Description   : Checks clock names from xoscs array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckXoscClocks(Clock_Ip_ClockConfigType const * Config)
{
#if CLOCK_IP_XOSCS_COUNT > 1U
    uint32 Index;
#endif

    if (Config->XoscsCount != 0U)
    {
#if CLOCK_IP_XOSCS_COUNT > 1U
        if (Config->XoscsCount > 1U)
        {
            for (Index = 0U; Index < (Config->XoscsCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->Xoscs))[Index].Name) < ((uint32)(*(Config->Xoscs))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Xoscs))[Index].Name] & CLOCK_IP_XOSC_OBJECT) != 0U);
            }
        }
#endif
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Xoscs))[Config->XoscsCount - 1U].Name] & CLOCK_IP_XOSC_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckPllClocks
 * Description   : Checks clock names from plls array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckPllClocks(Clock_Ip_ClockConfigType const * Config)
{
#if CLOCK_IP_PLLS_COUNT > 1U
    uint32 Index;
#endif
    if (Config->PllsCount != 0U)
    {
#if CLOCK_IP_PLLS_COUNT > 1U
        if (Config->PllsCount > 1U)
        {
            for (Index = 0U; Index < (Config->PllsCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->Plls))[Index].Name) < ((uint32)(*(Config->Plls))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Plls))[Index].Name] & CLOCK_IP_PLL_OBJECT) != 0U);
            }
        }
#endif
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Plls))[Config->PllsCount - 1U].Name] & CLOCK_IP_PLL_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckExtSigClocks
 * Description   : Checks clock names from ext signal clocks array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckExtSigClocks(Clock_Ip_ClockConfigType const * Config)
{
#if CLOCK_IP_EXT_CLKS_COUNT > 1U
    uint32 Index;
#endif
    if (Config->ExtClksCount != 0U)
    {
#if CLOCK_IP_EXT_CLKS_COUNT > 1U
        if (Config->ExtClksCount > 1U)
        {
            for (Index = 0U; Index < (Config->ExtClksCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->ExtClks))[Index].Name) < ((uint32)(*(Config->ExtClks))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->ExtClks))[Index].Name] & CLOCK_IP_EXT_SIG_OBJECT) != 0U);
            }
        }
#endif
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->ExtClks))[Config->ExtClksCount - 1U].Name] & CLOCK_IP_EXT_SIG_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckSelectorClocks
 * Description   : Checks clock names from selectors array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckSelectorClocks(Clock_Ip_ClockConfigType const * Config)
{
    uint32 Index;

    if (Config->SelectorsCount != 0U)
    {
        if (Config->SelectorsCount > 1U)
        {
            for (Index = 0U; Index < (Config->SelectorsCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Selectors))[Index].Name] & CLOCK_IP_SELECTOR_OBJECT) != 0U);
            }
        }
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Selectors))[Config->SelectorsCount - 1U].Name] & CLOCK_IP_SELECTOR_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckDividerClocks
 * Description   : Checks clock names from dividers array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckDividerClocks(Clock_Ip_ClockConfigType const * Config)
{
    uint32 Index;

    if (Config->DividersCount != 0U)
    {
        if (Config->DividersCount > 1U)
        {
            for (Index = 0U; Index < (Config->DividersCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Dividers))[Index].Name] & CLOCK_IP_DIVIDER_OBJECT) != 0U);
            }
        }
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Dividers))[Config->DividersCount - 1U].Name] & CLOCK_IP_DIVIDER_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_DividerTrigger_Clocks
 * Description   : Checks clock names from divider triggers array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckDividerTriggerClocks(Clock_Ip_ClockConfigType const * Config)
{
#if CLOCK_IP_DIVIDER_TRIGGERS_COUNT > 1U
    uint32 Index;
#endif

    if (Config->DividerTriggersCount != 0U)
    {
#if CLOCK_IP_DIVIDER_TRIGGERS_COUNT > 1U
        if (Config->DividerTriggersCount > 1U)
        {
            for (Index = 0U; Index < (Config->DividerTriggersCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->DividerTriggers))[Index].Name) < ((uint32)(*(Config->DividerTriggers))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->DividerTriggers))[Index].Name] & CLOCK_IP_DIVIDER_TRIGGER_OBJECT) != 0U);
            }
        }
#endif
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->DividerTriggers))[Config->DividerTriggersCount - 1U].Name] & CLOCK_IP_DIVIDER_TRIGGER_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_FracDivider_Clocks
 * Description   : Checks clock names from fractional divider array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckFracDividerClocks(Clock_Ip_ClockConfigType const * Config)
{
#if CLOCK_IP_FRACTIONAL_DIVIDERS_COUNT > 1U
    uint32 Index;
#endif

    if (Config->FracDivsCount != 0U)
    {
#if CLOCK_IP_FRACTIONAL_DIVIDERS_COUNT > 1U
        if (Config->FracDivsCount > 1U)
        {
            for (Index = 0U; Index < (Config->FracDivsCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->FracDivs))[Index].Name) < ((uint32)(*(Config->FracDivs))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->FracDivs))[Index].Name] & CLOCK_IP_FRAC_DIV_OBJECT) != 0U);
            }
        }
#endif
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->FracDivs))[Config->FracDivsCount - 1U].Name] & CLOCK_IP_FRAC_DIV_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckGateClocks
 * Description   : Checks clock names from gates array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckGateClocks(Clock_Ip_ClockConfigType const * Config)
{
    uint32 Index;

    if (Config->GatesCount != 0U)
    {
        if (Config->GatesCount > 1U)
        {
            for (Index = 0U; Index < (Config->GatesCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT(((uint32)(*(Config->Gates))[Index].Name) < ((uint32)(*(Config->Gates))[Index+1U].Name));
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Gates))[Index].Name] & CLOCK_IP_GATE_OBJECT) != 0U);
            }
        }
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Gates))[Config->GatesCount - 1U].Name] & CLOCK_IP_GATE_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckPcfsClocks
 * Description   : Checks clock names from pcfs array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckPcfsClocks(Clock_Ip_ClockConfigType const * Config)
{
    uint32 Index;

    if (Config->PcfsCount != 0U)
    {
        if (Config->PcfsCount > 1U)
        {
            for (Index = 0U; Index < (Config->PcfsCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Pcfs))[Index].Name] & CLOCK_IP_PCFS_OBJECT) != 0U);
            }
        }
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Pcfs))[Config->PcfsCount - 1U].Name] & CLOCK_IP_PCFS_OBJECT) != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_CheckCmuClocks
 * Description   : Checks clock names from cmu array
 *
 *END**************************************************************************/
static void Clock_Ip_CheckCmuClocks(Clock_Ip_ClockConfigType const * Config)
{
    uint32 Index;

    if (Config->CmusCount != 0U)
    {
        if (Config->CmusCount > 1U)
        {
            for (Index = 0U; Index < (Config->CmusCount - 1U); Index++)
            {
                CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Cmus))[Index].Name] & CLOCK_IP_CMU_OBJECT) != 0U);
            }
        }
        CLOCK_IP_DEV_ASSERT((Clock_Ip_au8ClockNameTypes[(*(Config->Cmus))[Config->CmusCount - 1U].Name] & CLOCK_IP_CMU_OBJECT) != 0U);
    }
}
    #endif
#endif

#define CLOCK_IP_NO_CALLBACK 0U

/* Call empty callbacks to improve CCOV*/
static void Clock_Ip_CallEmptyCallbacks(void)
{

    if (FALSE == FunctionWasCalled)
    {
        FunctionWasCalled = TRUE;

        Clock_Ip_axCmuCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR, 0U);
        Clock_Ip_axCmuCallbacks[CLOCK_IP_NO_CALLBACK].Disable(RESERVED_CLK);

        Clock_Ip_axDividerCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR);

        Clock_Ip_axDividerTriggerCallbacks[CLOCK_IP_NO_CALLBACK].Configure(NULL_PTR);

        Clock_Ip_axExtOscCallbacks[CLOCK_IP_NO_CALLBACK].Reset(NULL_PTR);

        Clock_Ip_axFracDivCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR);
        (void)Clock_Ip_axFracDivCallbacks[CLOCK_IP_NO_CALLBACK].Complete(CLOCK_IS_OFF);

        Clock_Ip_axGateCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR);
        Clock_Ip_axGateCallbacks[CLOCK_IP_NO_CALLBACK].Update(CLOCK_IS_OFF,FALSE);

        Clock_Ip_axIntOscCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR);

        Clock_Ip_axPllCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR);
        (void)Clock_Ip_axPllCallbacks[CLOCK_IP_NO_CALLBACK].Complete(CLOCK_IS_OFF);

        Clock_Ip_axSelectorCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR);

        Clock_Ip_axPcfsCallbacks[CLOCK_IP_NO_CALLBACK].Set(NULL_PTR, 0U);
    }
}

static void Clock_Ip_ResetClockConfiguration(Clock_Ip_ClockConfigType const * Config)
{
    uint32 CallbackIndex;
    uint32 Index;

    for (Index = Config->SelectorsCount ; Index > 0U; Index--)    /* Ramp down all selectors from configuration to SAFE_CLOCK */
    {
        CallbackIndex = Clock_Ip_au8SelectorCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Selectors))[Index - 1U].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axSelectorCallbacks[CallbackIndex].Reset(&(*Config->Selectors)[Index - 1U]);
    }

    for (Index = Config->FracDivsCount; Index > 0U; Index--)    /* Put in reset state all fractional dividers from configuration */
    {
        CallbackIndex = Clock_Ip_au8FractionalDividerCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->FracDivs))[Index - 1U].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axFracDivCallbacks[CallbackIndex].Reset(&(*Config->FracDivs)[Index - 1U]);
    }

    for (Index = Config->PllsCount; Index > 0U; Index--)       /* Power down all plls from configuration */
    {
        CallbackIndex = Clock_Ip_au8PllCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Plls))[Index - 1U].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axPllCallbacks[CallbackIndex].Reset(&(*Config->Plls)[Index - 1U]);
    }

    for (Index = Config->XoscsCount; Index > 0U; Index--)     /* Power down all xoscs from configuration */
    {
        CallbackIndex = Clock_Ip_au8XoscCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Xoscs))[Index - 1U].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axExtOscCallbacks[CallbackIndex].Reset(&(*Config->Xoscs)[Index - 1U]);
    }
}

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
    #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
static void Clock_Ip_CheckClockConfiguration(Clock_Ip_ClockConfigType const * Config)
{
    Clock_Ip_CheckIrcoscClocks(Config);
    Clock_Ip_CheckXoscClocks(Config);
    Clock_Ip_CheckPllClocks(Config);
    Clock_Ip_CheckExtSigClocks(Config);
    Clock_Ip_CheckSelectorClocks(Config);
    Clock_Ip_CheckDividerClocks(Config);
    Clock_Ip_CheckDividerTriggerClocks(Config);
    Clock_Ip_CheckFracDividerClocks(Config);
    Clock_Ip_CheckGateClocks(Config);
    Clock_Ip_CheckPcfsClocks(Config);
    Clock_Ip_CheckCmuClocks(Config);
}
    #endif
#endif
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_Init
 *
 * Description   : Set clock configuration according to pre-defined structure.
 *                 This function sets system to target clock configuration; It sets the
 *                 clock modules registers for clock mode change.
 *
 *                 If external clock is used in the target mode, please make sure it is
 *                 enabled, for example, if the external oscillator is used, please setup correctly.
 *
 * @implements Clock_Ip_Init_Activity
 * END**********************************************************************************/
Clock_Ip_StatusType Clock_Ip_Init(Clock_Ip_ClockConfigType const * Config)
{
    Clock_Ip_StatusType ClockStatus = CLOCK_IP_ERROR;

    Clock_Ip_PllStatusType PllStatus;

    (void)Clock_Ip_au8XoscCallbackIndex;
    (void)Clock_Ip_axExtOscCallbacks;
    (void)Clock_Ip_au8IrcoscCallbackIndex;
    (void)Clock_Ip_axIntOscCallbacks;
    (void)Clock_Ip_au8PcfsCallbackIndex;
    (void)Clock_Ip_axPcfsCallbacks;
    (void)Clock_Ip_au8DividerCallbackIndex;
    (void)Clock_Ip_axDividerCallbacks;

    (void)CLOCK_IP_MODULE_INSTANCE;
    (void)CLOCK_IP_CALLBACK;
    (void)CLOCK_IP_EXTENSION_INDEX;
    (void)CLOCK_IP_POWER_MODE_INDEX;
    (void)CLOCK_IP_SELECTOR_INDEX;
    (void)CLOCK_IP_DIVIDER_INDEX;
    (void)CLOCK_IP_GATE_INDEX;
    (void)CLOCK_IP_PCFS_INDEX;
    (void)CLOCK_IP_CMU_INDEX;

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    /* Set user access allowed for Clock */
    Clock_Ip_Command(Config, CLOCK_IP_SET_USER_ACCESS_ALLOWED_COMMAND);
  #endif
#endif
    CLOCK_IP_DEV_ASSERT(NULL_PTR != Config);

    Clock_Ip_InitClock(Config);

    if (DriverContext.ClockTreeIsConsumingPll)
    {
        PllStatus = Clock_Ip_GetPllStatus();
        if (CLOCK_IP_PLL_LOCKED == PllStatus)
        {
            Clock_Ip_DistributePll();
            ClockStatus = CLOCK_IP_SUCCESS;
        }
    }
    else
    {
        ClockStatus = CLOCK_IP_SUCCESS;
    }

    return ClockStatus;
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_InitClock
 *
 * Description   : Set the PLL and other MCU specific clock options.
 *                 This function initializes the PLL and other MCU specific clock options.
 *                 The clock configuration parameters are provided via the configuration structure.
 *
 *                 This function shall start the PLL lock procedure (if PLL
 *                 shall be initialized) and shall return without waiting until the PLL is locked.
 *
 * @implements Clock_Ip_InitClock_Activity
 * END**********************************************************************************/
void Clock_Ip_InitClock(Clock_Ip_ClockConfigType const * Config)
{
    uint32 CallbackIndex;
    uint32 Index;

#if (defined(CLOCK_IP_DEV_ERROR_DETECT) && (CLOCK_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check clock elements from clock configuration */
    Clock_Ip_CheckClockConfiguration(Config);
#endif

    CLOCK_IP_DEV_ASSERT(NULL_PTR != Config);

    /* Save the current clock configuration to be used by "Clock_Ip_DistributePllClock". */
    Clock_Ip_pxConfig = Config;

    /* Platform specific initialization:
     * DFS reset, FIRC_CLK configuration etc. */
    Clock_Ip_Command(Config, CLOCK_IP_INITIALIZE_PLATFORM_COMMAND);

    /* Clear all the settings for CMU0/1/2... */
    /* In case one clock configuration has the CMU disabled, then need to make the transition to
    reset state of CMU modules. */
    if (NULL_PTR != Clock_Ip_pxConfig)
    {
        for (Index = 0U; Index < Config->CmusCount; Index++)    /* Reset all clock monitor units from previous configuration. */
        {
            CallbackIndex = Clock_Ip_au8CmuCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Cmus))[Index].Name][CLOCK_IP_CALLBACK]];
            Clock_Ip_axCmuCallbacks[CallbackIndex].Reset(&(*Config->Cmus)[Index]);
        }
    }

    /*********************************************************************
     ***  Ramp down to safe configuration. Reset elements from clock tree:
     ***  selectors, fractional dividers, plls and xoscs
     ***********************************************************************/
    Clock_Ip_ResetClockConfiguration(Config);

    /*******************************************************
     *** Load the new configuration. Selectors that might
     *** be clocked from PLLs shouldn't be configured.
     *******************************************************/

    for (Index = 0U; Index < Config->IrcoscsCount; Index++)   /* Set internal oscillators from configuration */
    {
        CallbackIndex = Clock_Ip_au8IrcoscCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Ircoscs))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axIntOscCallbacks[CallbackIndex].Set(&(*Config->Ircoscs)[Index]);
    }

    /* Initialize clock objects, internal driver data */
    Clock_Ip_UpdateDriverContext(Config);

    for (Index = 0U; Index < Config->XoscsCount; Index++)     /* Configure all xoscs from configuration */
    {
        CallbackIndex = Clock_Ip_au8XoscCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Xoscs))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axExtOscCallbacks[CallbackIndex].Set(&(*Config->Xoscs)[Index]);
    }

    /* Configure the PCFS  */
    for (Index = 0U; Index < Config->PcfsCount; Index++)       /* Configure all progressive frequency switching clocks from configuration */
    {
        CallbackIndex = Clock_Ip_au8PcfsCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Pcfs))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axPcfsCallbacks[CallbackIndex].Set(&(*Config->Pcfs)[Index], Index);
    }

    /* Configure the clock divider triggers that are under MCU control */
    for (Index = 0U; Index < Config->DividerTriggersCount; Index++)    /* Set divider triggers from configuration. */
    {
        CallbackIndex = Clock_Ip_au8DividerTriggerCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->DividerTriggers))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axDividerTriggerCallbacks[CallbackIndex].Configure(&(*Config->DividerTriggers)[Index]);
    }

    /* Configure the clock dividers that are under MCU control */
    for (Index = 0U; Index < Config->DividersCount; Index++)    /* Set dividers from configuration. */
    {
        CallbackIndex = Clock_Ip_au8DividerCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Dividers))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axDividerCallbacks[CallbackIndex].Set(&(*Config->Dividers)[Index]);
    }

    /* Trigger update for all divider trigger that are under MCU control */
    for (Index = 0U; Index < Config->DividerTriggersCount; Index++)    /* Set divider triggers from configuration. */
    {
        CallbackIndex = Clock_Ip_au8DividerTriggerCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->DividerTriggers))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axDividerTriggerCallbacks[CallbackIndex].TriggerUpdate(&(*Config->DividerTriggers)[Index]);
    }

    /* Configure PLL clock generators */
    for (Index = 0U; Index < Config->PllsCount; Index++)       /* Configure all plls from configuration asynchronously. Do not enable. */
    {
        CallbackIndex = Clock_Ip_au8PllCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Plls))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axPllCallbacks[CallbackIndex].Set(&(*Config->Plls)[Index]);
    }

    for (Index = 0U; Index < Config->CmusCount; Index++)     /* Set the Clock Monitoring Units that are under mcu control. Cmus are not enabled. */
    {
        CallbackIndex = Clock_Ip_au8CmuCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Cmus))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axCmuCallbacks[CallbackIndex].Set(&(*Config->Cmus)[Index], Index);
    }

    for (Index = 0U; Index < Config->XoscsCount; Index++)     /* Wait for all xoscs from configuration to lock */
    {
        CallbackIndex = Clock_Ip_au8XoscCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Xoscs))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axExtOscCallbacks[CallbackIndex].Complete(&(*Config->Xoscs)[Index]);
    }

    /* Configure PLL clock generators */
    for (Index = 0U; Index < Config->PllsCount; Index++)       /* Enable plls according to configuration asynchronously. Do not wait. */
    {
        CallbackIndex = Clock_Ip_au8PllCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Plls))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axPllCallbacks[CallbackIndex].Enable(&(*Config->Plls)[Index]);
    }

    /* Configure fractional dividers */
    /* Note: The DFS configuration might actually need to be done after we
     * know that the PLLs are all locked in "Clock_Ip_GetPllStatus". */
    for (Index = 0U; Index < Config->FracDivsCount; Index++)    /* Configure all fractional dividers from configuration asynchronously. Do not wait. */
    {
        CallbackIndex = Clock_Ip_au8FractionalDividerCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->FracDivs))[Index].Name][CLOCK_IP_CALLBACK]];
        Clock_Ip_axFracDivCallbacks[CallbackIndex].Set(&(*Config->FracDivs)[Index]);
    }

    DriverContext.ClockTreeIsConsumingPll = FALSE;                                  /* Check if clock tree is using a PLL output */
#if (defined(CLOCK_IP_SUPPORTS_WAIT_STATES))
#if(CLOCK_IP_SUPPORTS_WAIT_STATES == STD_ON)
    DriverContext.WaitStatesAreSupported = TRUE;                                    /* Wait states are supported */
#else
    DriverContext.WaitStatesAreSupported = FALSE;                                   /* Wait states are not supported */
#endif /*CLOCK_IP_SUPPORTS_WAIT_STATES == STD_ON */
#else
    DriverContext.WaitStatesAreSupported = FALSE;                                   /* Wait states are not supported */
#endif /* #if (defined(CLOCK_IP_SUPPORTS_WAIT_STATES)) */
    DriverContext.HwPllsNo = CLOCK_IP_NUMBER_OF_HARDWARE_PLL;                       /* Number of plls */
    DriverContext.HwDfsNo = CLOCK_IP_NUMBER_OF_HARDWARE_DFS;                        /* Number of fractional dividers */

#if ( defined(CLOCK_IP_HAS_RAM_WAIT_STATES) || defined(CLOCK_IP_HAS_FLASH_WAIT_STATES) )
    /* Configure wait states */
    Clock_Ip_SetWaitStates();
#endif

    /* Switch the clock multiplexers under MCU control to the configured source clocks */
    /* Note: if the configured source clock of a ClockMux is the output clock of a PLL/DFS,
     * the configuration will be skipped and the respective ClockMux will be switched in
     * the "Clock_Ip_DistributePllClock" function instead, when the source clock will have
     * stabilized already. */
    for (Index = 0U; Index < Config->SelectorsCount; Index++)    /* Set only if selected inputs are not clocked from PLLs */
    {
        if ((PLL_TYPE != Clock_Ip_aeSourceTypeClockName[(*(Config->Selectors))[Index].Value]))
        {

            CallbackIndex = Clock_Ip_au8SelectorCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Selectors))[Index].Name][CLOCK_IP_CALLBACK]];
            Clock_Ip_axSelectorCallbacks[CallbackIndex].Set(&(*Config->Selectors)[Index]);
        }
        else
        {
            /* At least one mux is consuming pll */
            DriverContext.ClockTreeIsConsumingPll = TRUE;
        }
    }

    /* Check if the clock tree is using a PLL output */
    if ( FALSE == DriverContext.ClockTreeIsConsumingPll )
    {
        for (Index = 0U; Index < Config->GatesCount; Index++)    /* Set clock gates that are under clock control. */
        {
            CallbackIndex = Clock_Ip_au8GateCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Gates))[Index].Name][CLOCK_IP_CALLBACK]];
            Clock_Ip_axGateCallbacks[CallbackIndex].Set(&(*Config->Gates)[Index]);
        }

        /* Enable the Clock Monitoring Units ( CMU0 .. n ) according to configuration. */
        for (Index = 0U; Index < Config->CmusCount; Index++)
        {
            CallbackIndex = Clock_Ip_au8CmuCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Config->Cmus))[Index].Name][CLOCK_IP_CALLBACK]];
            Clock_Ip_axCmuCallbacks[CallbackIndex].Enable(&(*Config->Cmus)[Index]);
        }
        /* Disable safe clock if it is supported by platform and it is configured/required. */
        /* Note: Safe clock is the fast internal oscillator clock. It is clocking the clock tree until pll is distributed.
         * At the end of configuration it can be disabled if it is supported on this platform and required/configured. */
        Clock_Ip_Command(Config, CLOCK_IP_DISABLE_SAFE_CLOCK_COMMAND);
    }
    else
    {
        /* The clock tree is using at least one PLL/DFS output clock as source. */
        /* The user must wait until the PLLs and DFSs are locked by polling Clock_Ip_GetPllStatus */
        /* and then call "Clock_Ip_DistributePllClock" */
    }
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_GetPllStatus
 * Description   : This function configures all clocks according to a clock configuration.
 * If no configuration is received, no change will be processed in HW and clock driver
 * will calculate frequencies only.
 *
 * @implements Clock_Ip_GetPllStatus_Activity
 * END**********************************************************************************/
Clock_Ip_PllStatusType Clock_Ip_GetPllStatus(void)
{
    Clock_Ip_PllStatusType RetValue = CLOCK_IP_PLL_STATUS_UNDEFINED;
    Clock_Ip_PllStatusReturnType PllStatus;
    Clock_Ip_DfsStatusType DfsStatus;

    uint32 Index;
    uint32 CallbackIndex;

    for (Index = 0U; Index < DriverContext.HwPllsNo; Index++)
    {
        CallbackIndex = Clock_Ip_au8PllCallbackIndex[Clock_Ip_au8ClockFeatures[Clock_Ip_aeHwPllName[Index]][CLOCK_IP_CALLBACK]];
        PllStatus = Clock_Ip_axPllCallbacks[CallbackIndex].Complete(Clock_Ip_aeHwPllName[Index]);
        if (STATUS_PLL_UNLOCKED == PllStatus)
        {
            RetValue = CLOCK_IP_PLL_UNLOCKED;
            break;
        }
        else
        {
            if (STATUS_PLL_LOCKED == PllStatus)
            {
                RetValue = CLOCK_IP_PLL_LOCKED;
            }
        }
    }

    if (CLOCK_IP_PLL_LOCKED == RetValue)
    {
        for (Index = 0U; Index < DriverContext.HwDfsNo; Index++)
        {
            CallbackIndex = Clock_Ip_au8FractionalDividerCallbackIndex[Clock_Ip_au8ClockFeatures[Clock_Ip_aeHwDfsName[Index]][CLOCK_IP_CALLBACK]];
            DfsStatus = Clock_Ip_axFracDivCallbacks[CallbackIndex].Complete(Clock_Ip_aeHwDfsName[Index]);
            if (STATUS_DFS_UNLOCKED == DfsStatus)
            {
                RetValue = CLOCK_IP_PLL_UNLOCKED;
                break;
            }
        }
    }

    return RetValue;
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DistributePll
 * Description   : Function completes the PLL configuration and then activates the PLL clock to Mcu
 * The function will not distribute the PLL clock if the driver state does not allow it, or the PLL is not stable.
 *
 * @implements Clock_Ip_DistributePll_Activity
 * END**********************************************************************************/
void Clock_Ip_DistributePll(void)
{

    uint32 Index;
    uint32 CallbackIndex;

    CLOCK_IP_DEV_ASSERT(NULL_PTR != Clock_Ip_pxConfig);
    /* 'Clock_Ip_pxConfig' is set by Clock_Ip_InitClock().
     *  It doesn't make sense to call PLL distribution without clock initialization. */
    if (NULL_PTR != Clock_Ip_pxConfig)
    {
        for (Index = 0U; Index < Clock_Ip_pxConfig->SelectorsCount; Index++)    /* Set only if selected inputs are clocked from PLLs */
        {
            if (PLL_TYPE == Clock_Ip_aeSourceTypeClockName[(*(Clock_Ip_pxConfig->Selectors))[Index].Value])
            {

                CallbackIndex = Clock_Ip_au8SelectorCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Clock_Ip_pxConfig->Selectors))[Index].Name][CLOCK_IP_CALLBACK]];
                Clock_Ip_axSelectorCallbacks[CallbackIndex].Set(&(*Clock_Ip_pxConfig->Selectors)[Index]);
            }
        }

        /* In the case of PLL is enabled but PLL clock source is not used by any clock Mux.
           So, no need to re-configure for CMUs, because they are configured by Clock_Ip_InitClock */
        /* Check if the clock tree is using a PLL output */
        if ( DriverContext.ClockTreeIsConsumingPll )
        {
            for (Index = 0U; Index < Clock_Ip_pxConfig->GatesCount; Index++)    /* Set clock gates that are under clock control. */
            {
                CallbackIndex = Clock_Ip_au8GateCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Clock_Ip_pxConfig->Gates))[Index].Name][CLOCK_IP_CALLBACK]];
                Clock_Ip_axGateCallbacks[CallbackIndex].Set(&(*Clock_Ip_pxConfig->Gates)[Index]);
            }

            /* Enable the Clock Monitoring Units ( CMU0 .. n ) according to configuration. */
            for (Index = 0U; Index < Clock_Ip_pxConfig->CmusCount; Index++)
            {
                CallbackIndex = Clock_Ip_au8CmuCallbackIndex[Clock_Ip_au8ClockFeatures[(*(Clock_Ip_pxConfig->Cmus))[Index].Name][CLOCK_IP_CALLBACK]];
                Clock_Ip_axCmuCallbacks[CallbackIndex].Enable(&(*Clock_Ip_pxConfig->Cmus)[Index]);
            }

            /* Disable safe clock if it is supported by platform and it is configured/required. */
            /* Note: Safe clock is the fast internal oscillator clock. It is clocking the clock tree until pll is distributed.
             * At the end of configuration it can be disabled if it is supported on this platform and required/configured. */
            Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_DISABLE_SAFE_CLOCK_COMMAND);
        }
    }
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DisableClockMonitor
 * Description   : Disables a clock monitor.
 *
 * @implements Clock_Ip_DisableClockMonitor_Activity
 * END**********************************************************************************/
void Clock_Ip_DisableClockMonitor(Clock_Ip_NameType ClockName)
{

    uint32 CallbackIndex;

    CallbackIndex = Clock_Ip_au8CmuCallbackIndex[Clock_Ip_au8ClockFeatures[ClockName][CLOCK_IP_CALLBACK]];
    Clock_Ip_axCmuCallbacks[CallbackIndex].Disable(ClockName);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_InstallNotificationsCallback
 * Description   : This function installs a callback for clock notifications.
 *
 * @implements Clock_Ip_InstallNotificationsCallback_Activity
 * END**********************************************************************************/
void Clock_Ip_InstallNotificationsCallback(Clock_Ip_NotificationsCallbackType Callback)
{
    CLOCK_IP_DEV_ASSERT(NULL_PTR != Callback);

    Clock_Ip_pfkNotificationsCallback = Callback;
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DisableModuleClock
 * Description   : Disables clock for a peripheral.
 *
 * @implements Clock_Ip_DisableModuleClock_Activity
 * END**********************************************************************************/
void Clock_Ip_DisableModuleClock(Clock_Ip_NameType ClockName)
{

    uint32 CallbackIndex;

    CallbackIndex = Clock_Ip_au8GateCallbackIndex[Clock_Ip_au8ClockFeatures[ClockName][CLOCK_IP_CALLBACK]];
    Clock_Ip_axGateCallbacks[CallbackIndex].Update(ClockName,TRUE);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_EnableModuleClock
 * Description   : Enable clock for a peripheral.
 *
 * @implements Clock_Ip_EnableModuleClock_Activity
 * END**********************************************************************************/
void Clock_Ip_EnableModuleClock(Clock_Ip_NameType ClockName)
{

    uint32 CallbackIndex;

    CallbackIndex = Clock_Ip_au8GateCallbackIndex[Clock_Ip_au8ClockFeatures[ClockName][CLOCK_IP_CALLBACK]];
    Clock_Ip_axGateCallbacks[CallbackIndex].Update(ClockName,FALSE);
}


#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_SetUserAccessAllowed.
 * Description   : Set user access allowed.
 *
 *END**************************************************************************/
void Clock_Ip_SetUserAccessAllowed(void)
{
    Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_SET_USER_ACCESS_ALLOWED_COMMAND);
}
  #endif
#endif


#if (defined(CLOCK_IP_GET_FREQUENCY_API))
  #if (CLOCK_IP_GET_FREQUENCY_API == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_GetClockFrequency
 * Description   : This function returns the frequency of a given clock
 *
 * @implements Clock_Ip_GetClockFrequency_Activity
 * END**************************************************************************/
uint64 Clock_Ip_GetClockFrequency(Clock_Ip_NameType ClockName)
{
#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
  #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
    CLOCK_IP_DEV_ASSERT((((uint32)ClockName) < ((uint32)CLOCK_IP_NAMES_NO)) && (THE_LAST_PRODUCER_CLK != ClockName));
  #endif
#endif
    return Clock_Ip_GetFreq(ClockName);
}
    #endif
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_SetWaitStates
 * Description   : Configure wait states
 *
 *END**************************************************************************/
#if ( defined(CLOCK_IP_HAS_RAM_WAIT_STATES) || defined(CLOCK_IP_HAS_FLASH_WAIT_STATES) )
static void Clock_Ip_SetWaitStates(void)
{
#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES
    /* The entry point of the flash and RAM controllers configuration. */
#ifdef CLOCK_IP_PREPARE_MEMORY_CONFIG
    CLOCK_IP_PREPARE_MEMORY_CONFIG(CLOCK_IP_RAM_MEMORY_CONFIG_ENTRY_POINT);
#else
    Clock_Ip_pfkNotificationsCallback(CLOCK_IP_RAM_MEMORY_CONFIG_ENTRY, RESERVED_CLK);
#endif

    Clock_Ip_SetRamWaitStates();

    /* The exit point of the flash and RAM controllers configuration. */
#ifdef CLOCK_IP_PREPARE_MEMORY_CONFIG
    CLOCK_IP_PREPARE_MEMORY_CONFIG(CLOCK_IP_RAM_MEMORY_CONFIG_EXIT_POINT);
#else
    Clock_Ip_pfkNotificationsCallback(CLOCK_IP_RAM_MEMORY_CONFIG_EXIT, RESERVED_CLK);
#endif
#endif

#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES
    /* The entry point of the flash and RAM controllers configuration. */
#ifdef CLOCK_IP_PREPARE_MEMORY_CONFIG
    CLOCK_IP_PREPARE_MEMORY_CONFIG(CLOCK_IP_FLASH_MEMORY_CONFIG_ENTRY_POINT);
#else
    Clock_Ip_pfkNotificationsCallback(CLOCK_IP_FLASH_MEMORY_CONFIG_ENTRY, RESERVED_CLK);
#endif

    Clock_Ip_SetFlashWaitStates();

    /* The exit point of the flash and RAM controllers configuration. */
#ifdef CLOCK_IP_PREPARE_MEMORY_CONFIG
    CLOCK_IP_PREPARE_MEMORY_CONFIG(CLOCK_IP_FLASH_MEMORY_CONFIG_EXIT_POINT);
#else
    Clock_Ip_pfkNotificationsCallback(CLOCK_IP_FLASH_MEMORY_CONFIG_EXIT, RESERVED_CLK);
#endif
#endif
}
#endif /* ( defined(CLOCK_IP_HAS_RAM_WAIT_STATES) || defined(CLOCK_IP_HAS_FLASH_WAIT_STATES) ) */

#ifdef CLOCK_IP_HAS_FIRC_STDBY_CLOCK_DISABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_DisableFircInStandby
 * Description   : This function disables FIRC in standby mode
 *
 * @implements Clock_Ip_DisableFircInStandby_Activity
 * END**************************************************************************/
void Clock_Ip_DisableFircInStandby(void)
{
    /* Initialize clock objects */
    Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND);

    DisableFircInStandbyMode();
}
#endif


#ifdef CLOCK_IP_HAS_FIRC_STDBY_CLOCK_ENABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_EnableFircInStandby
 * Description   : This function enables FIRC in standby mode
 *
 * @implements Clock_Ip_EnableFircInStandby_Activity
 * END**************************************************************************/
void Clock_Ip_EnableFircInStandby(void)
{
    /* Initialize clock objects */
    Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND);

    EnableFircInStandbyMode();
}
#endif


#ifdef CLOCK_IP_HAS_SIRC_STDBY_CLOCK_DISABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_DisableSircInStandby
 * Description   : This function disables SIRC in standby mode
 *
 * @implements Clock_Ip_DisableSircInStandby_Activity
 * END**************************************************************************/
void Clock_Ip_DisableSircInStandby(void)
{
    /* Initialize clock objects */
    Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND);

    DisableSircInStandbyMode();
}
#endif


#ifdef CLOCK_IP_HAS_SIRC_STDBY_CLOCK_ENABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_EnableSircInStandby
 * Description   : This function enables SIRC in standby mode
 *
 * @implements Clock_Ip_EnableSircInStandby_Activity
 * END**************************************************************************/
void Clock_Ip_EnableSircInStandby(void)
{
    /* Initialize clock objects */
    Clock_Ip_Command(Clock_Ip_pxConfig, CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND);

    EnableSircInStandbyMode();
}
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_ReportClockErrors
 * Description   : Report clock error
 *
 *END**************************************************************************/
void Clock_Ip_ReportClockErrors(Clock_Ip_NotificationType Error, Clock_Ip_NameType ClockName)
{
    Clock_Ip_pfkNotificationsCallback(Error,ClockName);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_StartTimeout
 * Description   : Checks for timeout condition
 *
 *END**************************************************************************/
void Clock_Ip_StartTimeout(uint32 *StartTimeOut,
                       uint32 *ElapsedTimeOut,
                       uint32 *TimeoutTicksOut,
                       uint32 TimeoutUs)
{
    *StartTimeOut    = OsIf_GetCounter(CLOCK_IP_TIMEOUT_TYPE);
    *ElapsedTimeOut  = 0U;
    *TimeoutTicksOut = OsIf_MicrosToTicks(TimeoutUs, CLOCK_IP_TIMEOUT_TYPE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_TimeoutExpired
 * Description   : Checks for timeout expiration condition
 *
 *END**************************************************************************/
boolean Clock_Ip_TimeoutExpired(uint32 *StartTimeInOut,
                            uint32 *ElapsedTimeInOut,
                            uint32 TimeoutTicks)
{
    boolean RetVal = FALSE;
    *ElapsedTimeInOut += OsIf_GetElapsed(StartTimeInOut, CLOCK_IP_TIMEOUT_TYPE);

    if (*ElapsedTimeInOut >= TimeoutTicks)
    {
        RetVal = TRUE;
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_WriteRegisterValues
 * Description   : Write register values
 *
 *END**************************************************************************/
#if (defined(CLOCK_IP_REGISTER_VALUES_OPTIMIZATION) && (CLOCK_IP_REGISTER_VALUES_OPTIMIZATION == STD_ON))
void Clock_Ip_WriteRegisterValues(const Clock_Ip_RegisterIndexType *Indexes)
{
    uint32 *RegAddr;
    uint32 RegData;
    uint32 Index;

    CLOCK_IP_DEV_ASSERT(NULL_PTR != Clock_Ip_pxConfig);
    /* 'Clock_Ip_pxConfig' is set by Clock_Ip_InitClock().
     *  It doesn't make sense to call this function without clock initialization. */
    if (NULL_PTR != Clock_Ip_pxConfig)
    {
        /* Register values array must be valid */
        CLOCK_IP_DEV_ASSERT(NULL_PTR != Clock_Ip_pxConfig->RegValues);

        /* Valus of indexes must be valid */
        CLOCK_IP_DEV_ASSERT(Indexes->StartIndex < Indexes->EndIndex);

        for (Index = Indexes->StartIndex; Index < Indexes->EndIndex; Index++)
        {
            RegAddr = (*Clock_Ip_pxConfig->RegValues)[Index].RegisterAddr;
            RegData = (*Clock_Ip_pxConfig->RegValues)[Index].RegisterData;
            *RegAddr = RegData;
        }
    }
}
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
