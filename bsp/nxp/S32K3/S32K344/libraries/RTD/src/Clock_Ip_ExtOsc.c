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
*   @file       Clock_Ip_ExtOsc.c
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
#define CLOCK_IP_EXTOSC_VENDOR_ID_C                      43
#define CLOCK_IP_EXTOSC_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_EXTOSC_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_EXTOSC_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_EXTOSC_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_EXTOSC_SW_MINOR_VERSION_C               0
#define CLOCK_IP_EXTOSC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_ExtOsc.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_EXTOSC_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_ExtOsc.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_ExtOsc.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_EXTOSC_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_EXTOSC_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_EXTOSC_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_ExtOsc.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_ExtOsc.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_EXTOSC_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_EXTOSC_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_EXTOSC_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_ExtOsc.c and Clock_Ip_Private.h are different"
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

static void Clock_Ip_ExternalOscillatorEmpty(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_ExternalOscillatorEmpty(Clock_Ip_XoscConfigType const* Config);

#ifdef CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL
static void Clock_Ip_ResetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_SetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_CompleteFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_EnableFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config);
#endif


#ifdef CLOCK_IP_SXOSC_OSCON_EOCV
static void Clock_Ip_ResetSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_SetSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_CompleteSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_EnableSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config);
#endif




#ifdef CLOCK_IP_SXOSC_OSCON_EOCV_CURR_PRG_SF_CURR_PRG_COMP_GM_SEL
static void Clock_Ip_ResetSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_SetSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_CompleteSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config);
static void Clock_Ip_EnableSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config);
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

static void Clock_Ip_ExternalOscillatorEmpty(Clock_Ip_XoscConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}


#ifdef CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL
static void Clock_Ip_ResetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 FxoscStatus;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable FXOSC */
        Clock_Ip_apxXosc[Instance]->CTRL &= ~FXOSC_CTRL_OSCON_MASK;
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until xosc is locked */
        do
        {
            FxoscStatus = ((Clock_Ip_apxXosc[Instance]->STAT & FXOSC_STAT_OSC_STAT_MASK) >> FXOSC_STAT_OSC_STAT_SHIFT);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((1U == FxoscStatus) && (FALSE == TimeoutOccurred));

        if (TimeoutOccurred)
        {
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
        }
    }
    else
    {
        (void)Instance;
    }
}

/* Set Fxosc configuration to register */
static void Clock_Ip_SetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            Clock_Ip_apxXosc[Instance]->CTRL =
               (
                FXOSC_CTRL_OSCON(1U)                                                |
                FXOSC_CTRL_OSC_BYP(Config->BypassOption)                            |
                FXOSC_CTRL_EOCV(Config->StartupDelay)                               |
                FXOSC_CTRL_GM_SEL(Config->TransConductance)                         |
                FXOSC_CTRL_COMP_EN(Config->CompEn)                                  |
        #ifdef CLOCK_IP_FXOSC_ALC_SUPPORTED
            #if (CLOCK_IP_FXOSC_ALC_SUPPORTED == STD_ON)
                FXOSC_CTRL_ALC_D(Config->AutoLevelController)
            #else
                (0U)
            #endif
        #else
                (0U)
        #endif
               );
        }
    #ifdef CLOCK_IP_GET_FREQUENCY_API
    #if (CLOCK_IP_GET_FREQUENCY_API == STD_ON)
        Clock_Ip_SetExternalOscillatorFrequency(Config->Name,Config->Freq);
    #endif
    #endif
    }
    else
    {
        (void)Instance;
    }
}
static void Clock_Ip_CompleteFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 FxoscStatus;
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            /* This assumes that FXOSC_CTRL[COMP_EN] = 1 and FXOSC_CTRL[OSC_BYP] = 0 (i.e. crystal clock/oscillator output). */
            /* In bypass mode (i.e. EXTAL output), FXOSC_CTRL[COMP_EN] = 0 and FXOSC_CTRL[OSC_BYP] = 1, which means that
               we cannot check for stabilization. This shifts the responsibility of waiting for a stable clock to the
               upper layers. */
            if (Config->CompEn != 0U)
            {
                if(0U == Config->BypassOption)
                {
                    Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
                    /* Wait until xosc is locked */
                    do
                    {
                        FxoscStatus = ((Clock_Ip_apxXosc[Instance]->STAT & FXOSC_STAT_OSC_STAT_MASK) >> FXOSC_STAT_OSC_STAT_SHIFT);
                        TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                    }
                    while ((0U == FxoscStatus) && (FALSE == TimeoutOccurred));

                    if (TimeoutOccurred)
                    {
                        /* Report timeout error */
                        Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
                    }
                }
                else
                {
                    /* Invalid FXOSC configuration: FXOSC_CTRL[COMP_EN] = 1 enforces FXOSC_CTRL[OSC_BYP] = 0. */
                    /* Report timeout error */
                    Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_FXOSC_CONFIGURATION_ERROR, Config->Name);
                }
            }
        }
    }
    else
    {
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)FxoscStatus;
        (void)Instance;
    }
}
static void Clock_Ip_EnableFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (1U == Config->Enable)
        {
            /* Enable SOSC. */
            Clock_Ip_apxXosc[Instance]->CTRL |= FXOSC_CTRL_OSCON_MASK;
        }
    }
    else
    {
        (void)Instance;
    }
}
#endif


#ifdef CLOCK_IP_SXOSC_OSCON_EOCV
static void Clock_Ip_ResetSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable SXOSC */
        Clock_Ip_apxXosc[Instance]->CTRL &= ~SXOSC_SXOSC_CTRL_OSCON_MASK;
    }
    else
    {
        (void)Instance;
    }
}

/* Set Sxosc configuration to register */
static void Clock_Ip_SetSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;
    uint32 RegValue;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            RegValue = Clock_Ip_apxXosc[Instance]->CTRL;
            RegValue &= ~(SXOSC_SXOSC_CTRL_OSCON_MASK | SXOSC_SXOSC_CTRL_EOCV_MASK );
            RegValue|= (SXOSC_SXOSC_CTRL_OSCON(1U)                                  |
                        SXOSC_SXOSC_CTRL_EOCV(Config->StartupDelay)
                        );
            Clock_Ip_apxXosc[Instance]->CTRL = RegValue;
        }
    #ifdef CLOCK_IP_GET_FREQUENCY_API
    #if (CLOCK_IP_GET_FREQUENCY_API == STD_ON)
        Clock_Ip_SetExternalOscillatorFrequency(Config->Name,Config->Freq);
    #endif
    #endif
    }
    else
    {
        (void)Instance;
        (void)RegValue;
    }
}
static void Clock_Ip_CompleteSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 SxoscStatus;
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            if(0U == Config->BypassOption)
            {
                Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
                /* Wait until xosc is locked */
                do
                {
                    SxoscStatus = ((Clock_Ip_apxXosc[Instance]->STAT & SXOSC_SXOSC_STAT_OSC_STAT_MASK) >> SXOSC_SXOSC_STAT_OSC_STAT_SHIFT);
                    TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                }
                while ((0U == SxoscStatus) && (FALSE == TimeoutOccurred));

                if (TimeoutOccurred)
                {
                    /* Report timeout error */
                    Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
                }
            }
            else
            {
                /* Invalid FXOSC configuration: FXOSC_CTRL[COMP_EN] = 1 enforces FXOSC_CTRL[OSC_BYP] = 0. */
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_FXOSC_CONFIGURATION_ERROR, Config->Name);
            }
        }
    }
    else
    {
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)SxoscStatus;
        (void)Instance;
    }
}

/* Enable Sxosc */
static void Clock_Ip_EnableSxoscOsconEocv(Clock_Ip_XoscConfigType const* Config)
{
    (void)Config;
}
#endif




#ifdef CLOCK_IP_SXOSC_OSCON_EOCV_CURR_PRG_SF_CURR_PRG_COMP_GM_SEL
static void Clock_Ip_ResetSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable SXOSC */
        Clock_Ip_apxXosc[Instance]->CTRL &= ~(  SXOSC_SXOSC_CTRL_OSCON_MASK |
                                                SXOSC_SXOSC_CTRL_GM_SEL_MASK |
                                                SXOSC_SXOSC_CTRL_EOCV_MASK |
                                                SXOSC_SXOSC_CTRL_CURR_PRG_COMP_MASK |
                                                SXOSC_SXOSC_CTRL_CURR_PRG_SF_MASK );
    }
    else
    {
        (void)Instance;
    }
}

/* Set Sxosc configuration to register */
static void Clock_Ip_SetSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config)
{
    uint32 Instance;
    uint32 RegValue;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            RegValue = Clock_Ip_apxXosc[Instance]->CTRL;
            RegValue &= ~(  SXOSC_SXOSC_CTRL_OSCON_MASK |
                            SXOSC_SXOSC_CTRL_GM_SEL_MASK |
                            SXOSC_SXOSC_CTRL_EOCV_MASK |
                            SXOSC_SXOSC_CTRL_CURR_PRG_COMP_MASK |
                            SXOSC_SXOSC_CTRL_CURR_PRG_SF_MASK );
            RegValue|= (SXOSC_SXOSC_CTRL_OSCON(1U)                      |
                        SXOSC_SXOSC_CTRL_EOCV(Config->StartupDelay)     |
                        SXOSC_SXOSC_CTRL_GM_SEL(Config->TransConductance)     |
                        SXOSC_SXOSC_CTRL_CURR_PRG_SF(Config->LevelShifterCurrent)     |
                        SXOSC_SXOSC_CTRL_CURR_PRG_COMP(Config->ComparatorCurrent)
                        );
            Clock_Ip_apxXosc[Instance]->CTRL = RegValue;
        }
    #ifdef CLOCK_IP_GET_FREQUENCY_API
    #if (CLOCK_IP_GET_FREQUENCY_API == STD_ON)
        Clock_Ip_SetExternalOscillatorFrequency(Config->Name,Config->Freq);
    #endif
    #endif
    }
    else
    {
        (void)Instance;
        (void)RegValue;
    }
}
static void Clock_Ip_CompleteSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 SxoscStatus;
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            if(0U == Config->BypassOption)
            {
                Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
                /* Wait until xosc is locked */
                do
                {
                    SxoscStatus = ((Clock_Ip_apxXosc[Instance]->STAT & SXOSC_SXOSC_STAT_OSC_STAT_MASK) >> SXOSC_SXOSC_STAT_OSC_STAT_SHIFT);
                    TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                }
                while ((0U == SxoscStatus) && (FALSE == TimeoutOccurred));

                if (TimeoutOccurred)
                {
                    /* Report timeout error */
                    Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
                }
            }
            else
            {
                /* Invalid FXOSC configuration: FXOSC_CTRL[COMP_EN] = 1 enforces FXOSC_CTRL[OSC_BYP] = 0. */
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_FXOSC_CONFIGURATION_ERROR, Config->Name);
            }
        }
    }
    else
    {
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)SxoscStatus;
        (void)Instance;
    }
}


/* Enable Sxosc */
static void Clock_Ip_EnableSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel(Clock_Ip_XoscConfigType const* Config)
{
    (void)Config;
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

const Clock_Ip_ExtOscCallbackType Clock_Ip_axExtOscCallbacks[CLOCK_IP_XOSC_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_ExternalOscillatorEmpty,        /* Reset */
        &Clock_Ip_ExternalOscillatorEmpty,        /* Set */
        &Clock_Ip_ExternalOscillatorEmpty,        /* Complete */
        &Clock_Ip_ExternalOscillatorEmpty,        /* Enable */
    },

#ifdef CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL
    {
        &Clock_Ip_ResetFxoscOsconBypEocvGmSel,        /* Reset */
        &Clock_Ip_SetFxoscOsconBypEocvGmSel,          /* Set */
        &Clock_Ip_CompleteFxoscOsconBypEocvGmSel,     /* Complete */
        &Clock_Ip_EnableFxoscOsconBypEocvGmSel,       /* Enable */
    },
#endif


#ifdef CLOCK_IP_SXOSC_OSCON_EOCV
    {
        &Clock_Ip_ResetSxoscOsconEocv,                /* Reset */
        &Clock_Ip_SetSxoscOsconEocv,                  /* Set */
        &Clock_Ip_CompleteSxoscOsconEocv,             /* Complete */
        &Clock_Ip_EnableSxoscOsconEocv,               /* Enable */
    },
#endif




#ifdef CLOCK_IP_SXOSC_OSCON_EOCV_CURR_PRG_SF_CURR_PRG_COMP_GM_SEL
    {
        &Clock_Ip_ResetSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel,                /* Reset */
        &Clock_Ip_SetSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel,                  /* Set */
        &Clock_Ip_CompleteSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel,             /* Complete */
        &Clock_Ip_EnableSxoscOsconEocvCurrPrgSfCurrPrgCompGmSel,               /* Enable */
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
