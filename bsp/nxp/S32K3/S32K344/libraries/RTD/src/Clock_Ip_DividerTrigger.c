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
*   @file       Clock_Ip_DividerTrigger.c
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
#define CLOCK_IP_DIVIDERTRIGGER_VENDOR_ID_C                      43
#define CLOCK_IP_DIVIDERTRIGGER_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_DIVIDERTRIGGER_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_DIVIDERTRIGGER_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_DIVIDERTRIGGER_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_DIVIDERTRIGGER_SW_MINOR_VERSION_C               0
#define CLOCK_IP_DIVIDERTRIGGER_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_DividerTrigger.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_DIVIDERTRIGGER_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_DividerTrigger.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_DividerTrigger.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_DIVIDERTRIGGER_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_DIVIDERTRIGGER_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_DIVIDERTRIGGER_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_DividerTrigger.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_DividerTrigger.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_DIVIDERTRIGGER_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_DIVIDERTRIGGER_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_DIVIDERTRIGGER_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_DividerTrigger.c and Clock_Ip_Private.h are different"
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


/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_Callback_DividerTriggerEmpty(Clock_Ip_DividerTriggerConfigType const* Config);

#ifdef CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT
static void Clock_Ip_ConfigureCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* Config);
static void Clock_Ip_TriggerUpdateCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* Config);
#endif


/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_Callback_DividerTriggerEmpty(Clock_Ip_DividerTriggerConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}

#ifdef CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT
static void Clock_Ip_ConfigureCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* Config)
{
    uint32 Instance;
    uint32 SelectorIndex;

    if (NULL_PTR != Config)
    {
        Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        SelectorIndex = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_SELECTOR_INDEX];

        /* Check whether trigger is enabled */
        if (Config->TriggerType != IMMEDIATE_DIVIDER_UPDATE)
        {
            Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_TRIG_CTRL = (MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK);
        }
        else
        {
            Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_TRIG_CTRL &= ~(MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK);
        }
    }
    else
    {
        (void)Config;
        (void)Instance;
        (void)SelectorIndex;
    }
}

static void Clock_Ip_TriggerUpdateCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* Config)
{
    uint32 Instance;
    uint32 SelectorIndex;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    if (NULL_PTR != Config)
    {
        Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        SelectorIndex = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_SELECTOR_INDEX];

        /* Check whether trigger is enabled */
        if (Config->TriggerType != IMMEDIATE_DIVIDER_UPDATE)
        {
            Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_TRIG = MC_CGM_MUX_DIV_TRIG_TRIGGER(CLOCK_IP_TRIGGER_VALUE);

            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            /* Wait for acknowledge to be cleared. */
            do
            {
                DividerStatus = (Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while ((MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING == DividerStatus) && (FALSE == TimeoutOccurred));

            /* timeout notification */
            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
            }
        }
    }
    else
    {
        (void)Instance;
        (void)SelectorIndex;
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)DividerStatus;
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

const Clock_Ip_DividerTriggerCallbackType Clock_Ip_axDividerTriggerCallbacks[CLOCK_IP_DIVIDERTRIGGER_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_Callback_DividerTriggerEmpty,                  /* Configure */
        &Clock_Ip_Callback_DividerTriggerEmpty,                  /* Trigger Update */
    },
#ifdef CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT
    {
        &Clock_Ip_ConfigureCgmXDivTrigCtrlTctlHhenUpdStat,           /* Configure */
        &Clock_Ip_TriggerUpdateCgmXDivTrigCtrlTctlHhenUpdStat,       /* Trigger Update */
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
