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
*   @file       Clock_Ip_IntOsc.c
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
#define CLOCK_IP_INTOSC_VENDOR_ID_C                      43
#define CLOCK_IP_INTOSC_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_INTOSC_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_INTOSC_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_INTOSC_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_INTOSC_SW_MINOR_VERSION_C               0
#define CLOCK_IP_INTOSC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_IntOsc.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_INTOSC_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_IntOsc.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_IntOsc.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_INTOSC_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_INTOSC_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_INTOSC_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_IntOsc.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_IntOsc.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_INTOSC_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_INTOSC_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_INTOSC_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_IntOsc.c and Clock_Ip_Private.h are different"
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

static void Clock_Ip_InternalOscillatorEmpty(Clock_Ip_IrcoscConfigType const* Config);
static void Clock_Ip_InternalOscillatorEmpty_Disable(Clock_Ip_NameType Name);
#ifdef CLOCK_IP_FIRC_STDBY_ENABLE
static void Clock_Ip_SetFircStdby(Clock_Ip_IrcoscConfigType const* Config);
static void Clock_Ip_EnableFircStdby(Clock_Ip_IrcoscConfigType const* Config);
static void Clock_Ip_DisableFircStdby(Clock_Ip_NameType Name);
#endif


#ifdef CLOCK_IP_SIRC_STDBY_ENABLE
static void Clock_Ip_SetSircStdby(Clock_Ip_IrcoscConfigType const* Config);
static void Clock_Ip_EnableSircStdby(Clock_Ip_IrcoscConfigType const* Config);
static void Clock_Ip_DisableSircStdby(Clock_Ip_NameType Name);
#endif


#ifdef CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR
static void Clock_Ip_SetFircDivSelHSEb(Clock_Ip_IrcoscConfigType const* Config);
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

static void Clock_Ip_InternalOscillatorEmpty(Clock_Ip_IrcoscConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}
static void Clock_Ip_InternalOscillatorEmpty_Disable(Clock_Ip_NameType Name)
{
    (void)Name;
    /* No implementation */
}

#ifdef CLOCK_IP_FIRC_STDBY_ENABLE
/* Set Firc in Standby mode */
static void Clock_Ip_SetFircStdby(Clock_Ip_IrcoscConfigType const* Config)
{
    if (NULL_PTR != Config)
    {
        if (Config->Enable != 0U)
        {
            IP_FIRC->STDBY_ENABLE |= FIRC_STDBY_ENABLE_STDBY_EN_MASK;
        }
        else
        {
            IP_FIRC->STDBY_ENABLE &= ~FIRC_STDBY_ENABLE_STDBY_EN_MASK;
        }
    }
}
/* Enable Firc in Standby mode */
static void Clock_Ip_EnableFircStdby(Clock_Ip_IrcoscConfigType const* Config)
{
    (void)Config;
    IP_FIRC->STDBY_ENABLE |= FIRC_STDBY_ENABLE_STDBY_EN_MASK;
}
/* Disable Firc in Standby mode */
static void Clock_Ip_DisableFircStdby(Clock_Ip_NameType Name)
{
    (void)Name;
    IP_FIRC->STDBY_ENABLE &= ~FIRC_STDBY_ENABLE_STDBY_EN_MASK;
}
#endif


#ifdef CLOCK_IP_SIRC_STDBY_ENABLE
/* Set Sirc in Standby mode  */
static void Clock_Ip_SetSircStdby(Clock_Ip_IrcoscConfigType const* Config)
{
    if (NULL_PTR != Config)
    {
        if (Config->Enable != 0U)
        {
            IP_SIRC->MISCELLANEOUS_IN |= SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK;
        }
        else
        {
            IP_SIRC->MISCELLANEOUS_IN &= ~SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK;
        }
    }
}
/* Enable Sirc in Standby mode */
static void Clock_Ip_EnableSircStdby(Clock_Ip_IrcoscConfigType const* Config)
{
    (void)Config;
    IP_SIRC->MISCELLANEOUS_IN |= SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK;
}
/* Disable Sirc in Standby mode */
static void Clock_Ip_DisableSircStdby(Clock_Ip_NameType Name)
{
    (void)Name;
    IP_SIRC->MISCELLANEOUS_IN &= ~SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK;
}
#endif


#ifdef CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR
#define CLOCK_IP_APP_CAN_WRITE 5U
/* Set Firc Div Sel */
static void Clock_Ip_SetFircDivSelHSEb(Clock_Ip_IrcoscConfigType const* Config)
{
    uint32 RegValue;
    uint32 DividerValue = 0U;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 WfiStatus;

    if (NULL_PTR != Config)
    {
        switch(Config->Range)
        {
            case CLOCK_IP_SUPPORTS_48MHZ_FREQUENCY:
                DividerValue = 3U;
                break;
            case CLOCK_IP_SUPPORTS_24MHZ_FREQUENCY:
                DividerValue = 1U;
                break;
            case CLOCK_IP_SUPPORTS_3MHZ_FREQUENCY:
                DividerValue = 2U;
                break;
            default:
                /* No option in hardware for this value */
                break;
        }

        /* If divider value option from configuration is valid */
        if (DividerValue != 0U)
        {
            /* Application can write this divider */
            if ( ((IP_CONFIGURATION_GPR->CONFIG_REG_GPR & CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_MASK)>>CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_SHIFT) == CLOCK_IP_APP_CAN_WRITE)
            {
                /* Before access to CONFIG_REG_GPR register, driver should wait for Secure BAF to go in WFI
                   by reading register PRTN0_CORE2_STAT. Wfi status will be checked. */
                Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
                /* Wait for acknowledge to be cleared. */
                do
                {
                    WfiStatus = (IP_MC_ME->PRTN0_CORE2_STAT & MC_ME_PRTN0_CORE2_STAT_WFI_MASK);
                    TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                }
                while ((CLOCK_IP_WFI_EXECUTED != WfiStatus) && (FALSE == TimeoutOccurred));

                if (FALSE == TimeoutOccurred)
                {
                    RegValue = IP_CONFIGURATION_GPR->CONFIG_REG_GPR;
                    RegValue &= ~CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_MASK;
                    RegValue |= CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL(DividerValue);
                    IP_CONFIGURATION_GPR->CONFIG_REG_GPR = RegValue;
                }
                else
                {
                    Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
                }
            }
            else
            {
                /* HSE firmware doesn't allow to write FIRC post divider. Firc range cannot be set as it's configured. */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_WRITE_PROTECTION_ERROR, Config->Name);
            }
        }
    }
    else
    {
        (void)RegValue;
        (void)DividerValue;
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)WfiStatus;
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

const Clock_Ip_IntOscCallbackType Clock_Ip_axIntOscCallbacks[CLOCK_IP_IRCOSC_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_InternalOscillatorEmpty,          /* Set */
        &Clock_Ip_InternalOscillatorEmpty,          /* Enable */
        &Clock_Ip_InternalOscillatorEmpty_Disable,  /* Disable */
    },
#ifdef CLOCK_IP_FIRC_STDBY_ENABLE
    {
        &Clock_Ip_SetFircStdby,                     /* Set */
        &Clock_Ip_EnableFircStdby,                  /* Enable */
        &Clock_Ip_DisableFircStdby,                 /* Disable */
    },
#endif


#ifdef CLOCK_IP_SIRC_STDBY_ENABLE
    {
        &Clock_Ip_SetSircStdby,                     /* Set */
        &Clock_Ip_EnableSircStdby,                  /* Enable */
        &Clock_Ip_DisableSircStdby,                 /* Disable */
    },
#endif


#ifdef CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR
    {
        &Clock_Ip_SetFircDivSelHSEb,                     /* Set */
        &Clock_Ip_InternalOscillatorEmpty,               /* Enable */
        &Clock_Ip_InternalOscillatorEmpty_Disable,       /* Disable */
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
