
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
*   @file       Clock_Ip_Specific.c
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

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_SPECIFIC_VENDOR_ID_C                      43
#define CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_SPECIFIC_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_SPECIFIC_SW_MINOR_VERSION_C               0
#define CLOCK_IP_SPECIFIC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Specific.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_SPECIFIC_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Specific.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Specific.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Specific.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Specific.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_SPECIFIC_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Specific.c and Clock_Ip_Private.h are different"
#endif

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Clock_Ip_Specific.c file and RegLockMacros.h file are of the same Autosar version */
    #if ((CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
        (CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Clock_Ip_Specific.c and RegLockMacros.h are different"
    #endif
    #endif
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES
typedef void (*SetFlashWaitStatesCallbackType)(void);
#endif

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define CLOCK_IP_FIRCOSC_STDBY                 2U
#define CLOCK_IP_SIRCOSC_STDBY                 3U
/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start ram section code */
#define MCU_START_SEC_RAMCODE
#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES
static void Clock_Ip_CodeInRamSetFlashWaitStates(void);
#endif

/* Clock stop ram section code */
#define MCU_STOP_SEC_RAMCODE
#include "Mcu_MemMap.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

static void Clock_Ip_ClockInitializeObjects(void);

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

static const Clock_Ip_IntOscCallbackType *Clock_Ip_pxSircStdbyClock;
static const Clock_Ip_IntOscCallbackType *Clock_Ip_pxFircStdbyClock;


/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES
static SetFlashWaitStatesCallbackType Clock_Ip_SetFlashWaitStatesCallback = &Clock_Ip_CodeInRamSetFlashWaitStates;   /* Set Flash Wait States callback */
#endif

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_BOOLEAN
#include "Mcu_MemMap.h"

static boolean Clock_Ip_bObjectsAreInitialized;   /* Clock objects are initialized. */

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Mcu_MemMap.h"
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
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
static void Clock_Ip_PllPowerClockIp(void);
static void Clock_Ip_FxoscPowerClockIp(void);
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
static void Clock_Ip_SxoscPowerClockIp(void);
#endif
static void Clock_Ip_CmusPowerClockIp(void);
static void Clock_Ip_MscmPowerClockIp(void);
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

static void Clock_Ip_PllPowerClockIp(void)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;

    /* PLL is not powered */
    if (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK))
    {
        /* Power PLL device */
        IP_MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ56(1U);   /* REQ56: Frequency Modulated Phase-Locked Loop */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        Clock_Ip_McMeEnterKey();

        /* 
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK)))

        {
            /* Wait for hardware to update */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PLL_CLK);
            }
        }
    }

    /* PLLAUX is not powered */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    if (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK57_MASK))
    {
        /* Power PLL device */
        IP_MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ57(1U);   /* REQ57: Frequency Modulated Phase-Locked Loop */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        Clock_Ip_McMeEnterKey();

        /* 
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK57_MASK)))

        {
            /* Wait for hardware to update */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK57_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PLLAUX_CLK);
            }
        }
    }
#endif
}
static void Clock_Ip_FxoscPowerClockIp(void)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;

    /* FXOSC is not powered */
    if (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK53_MASK))
    {
        /* Power FXOSC device */
        IP_MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ53(1U);   /* REQ53: Fast External Oscillator */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        Clock_Ip_McMeEnterKey();

        /* 
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK53_MASK)))

        {
            /* Wait for hardware to update */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK53_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, FXOSC_CLK);
            }
        }
    }
}

#if defined(CLOCK_IP_HAS_SXOSC_CLK)
static void Clock_Ip_SxoscPowerClockIp(void)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;

    /* SXOSC is not powered */
    if (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK51_MASK))
    {
        /* Power SXOSC device */
        IP_MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ51(1U);   /* REQ51: Slow External Oscillator */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        Clock_Ip_McMeEnterKey();

        /*
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK51_MASK)))

        {
            /* Wait for hardware to update */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK51_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, SXOSC_CLK);
            }
        }
    }
}
#endif

static void Clock_Ip_CmusPowerClockIp(void)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;

    /* CMUs are not powered */
    if (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK47_MASK))
    {
        /* Power CMU devices */
        IP_MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ47(1U);   /* REQ47: Clock monitor unit */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        Clock_Ip_McMeEnterKey();

        /*
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK47_MASK)))

        {
            /* Wait for hardware to update */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK47_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, RESERVED_CLK);
            }
        }
    }
}
static void Clock_Ip_MscmPowerClockIp(void)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;

    /* MSCM is not powered */
    if (0U == (IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK24_MASK))
    {
        /* Power MSCM devices */
        IP_MC_ME->PRTN1_COFB0_CLKEN |= MC_ME_PRTN1_COFB0_CLKEN_REQ24(1U);   /* REQ24: MSCM */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        Clock_Ip_McMeEnterKey();

        /*
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK24_MASK)))

        {
            /* Wait for hardware to update */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK24_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, RESERVED_CLK);
            }
        }
    }
}

/* Power clock ip modules */
void Clock_Ip_PowerClockIpModules(void)
{
    Clock_Ip_PllPowerClockIp();
    Clock_Ip_FxoscPowerClockIp();
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    Clock_Ip_SxoscPowerClockIp();
#endif
    Clock_Ip_CmusPowerClockIp();
    Clock_Ip_MscmPowerClockIp();
}
/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES


/* Clock start ram section code */
#define MCU_START_SEC_RAMCODE

#include "Mcu_MemMap.h"

/* Configuration Flash wait state value base on ControllerRamFrequency  */
static void Clock_Ip_CodeInRamSetFlashWaitStates(void)
{
    uint32 RegValue;
    uint32 RwscSetting = 0U;
    uint32 ConfiguredCoreClock = 0U;

    ConfiguredCoreClock = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[CORE_CLK]].ConfiguredFrequencyValue;

    if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD4)
    {
#ifndef ERR_IPV_MCU_E051739
        if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD1)
        {
            RwscSetting = 1U;
        }
        else if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD2)
        {
            RwscSetting = 2U;
        }
        else if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD3)
        {
            RwscSetting = 3U;
        }
#else
        if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD3)
        {
            RwscSetting = 3U;
        }
#endif
        else
        {
            RwscSetting = 4U;
        }
    }
    else
    {
        if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD5)
        {
            RwscSetting = 5U;
        }
        else if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD6)
        {
            RwscSetting = 6U;
        }
        else if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD7)
        {
            RwscSetting = 7U;
        }
#ifdef CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD8
        else if (ConfiguredCoreClock <= CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD8)
        {
            RwscSetting = 8U;
        }
        else
        {
            RwscSetting = 8U;
        }
#else
        else
        {
            RwscSetting = 7U;
        }
#endif
    }

    /* Update register value with the new WS value. */
    RegValue = IP_FLASH->CTL;
    RegValue &= ~FLASH_CTL_RWSC_MASK;
    RegValue |= FLASH_CTL_RWSC(RwscSetting);

    /* Complete all data memory accesses and instructions. */
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    /* Unlock register to set flash wait states */
    IP_FLASH->CTL &= ~FLASH_CTL_RWSL_MASK;

    /* Configure wait states */
    IP_FLASH->CTL = RegValue;

    /* Complete all data memory accesses and instructions. */
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();
}

/* Clock stop ram section code */
#define MCU_STOP_SEC_RAMCODE
#include "Mcu_MemMap.h"

#endif

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES

/* Set Ram wait state */
void Clock_Ip_SetRamWaitStates(void)
{
#ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    OsIf_Trusted_Call(Clock_Ip_PRAMCSetRamIWS);
  #else
    Clock_Ip_PRAMCSetRamIWS();
  #endif
#else
  Clock_Ip_PRAMCSetRamIWS();
#endif
}
#endif

#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES
void Clock_Ip_FLASH_SetFlashIWS(void);

/* Set Flash wait state */
void Clock_Ip_SetFlashWaitStates(void)
{
    Clock_Ip_FLASH_SetFlashIWS();
}
#endif

void Clock_Ip_McMeEnterKey(void)
{
    IP_MC_ME->CTL_KEY = 0x5AF0U;                                         /* Enter key */

    IP_MC_ME->CTL_KEY = 0xA50FU;
}



static void Clock_Ip_SpecificPlatformInitClock(Clock_Ip_ClockConfigType const * Config)
{
    (void)Config;

    /* Power clock ip modules.
     * On some platforms clock ip modules cannot be configured,
     * registers cannot be access until device is powered.
     * Check and power if it is required clock ip modules.
     */
    Clock_Ip_PowerClockIpModules();
}

/* Disable FIRC in Standby mode */
void DisableFircInStandbyMode(void)
{
    Clock_Ip_pxFircStdbyClock->Disable(FIRC_CLK);
}

/* Enable Firc in Standby mode  */
void EnableFircInStandbyMode(void)
{
    Clock_Ip_IrcoscConfigType FircConfig;
    FircConfig.Enable = 1U;                                             /* TRUE */
    Clock_Ip_pxFircStdbyClock->Enable(&FircConfig);
}

/* Disable Sirc in Standby mode  */
void DisableSircInStandbyMode(void)
{
    Clock_Ip_pxSircStdbyClock->Disable(SIRC_CLK);
}

/* Enable Sirc in Standby mode  */
void EnableSircInStandbyMode(void)
{
    Clock_Ip_IrcoscConfigType SircConfig;
    SircConfig.Enable = 1U;                                             /* TRUE */
    Clock_Ip_pxSircStdbyClock->Enable(&SircConfig);
}

/* Initialize objects for clock */
static void Clock_Ip_ClockInitializeObjects(void)
{
    if (FALSE == Clock_Ip_bObjectsAreInitialized)
    {
        Clock_Ip_bObjectsAreInitialized = TRUE;

        Clock_Ip_pxSircStdbyClock = &Clock_Ip_axIntOscCallbacks[Clock_Ip_au8IrcoscCallbackIndex[CLOCK_IP_SIRCOSC_STDBY]];

        Clock_Ip_pxFircStdbyClock = &Clock_Ip_axIntOscCallbacks[Clock_Ip_au8IrcoscCallbackIndex[CLOCK_IP_FIRCOSC_STDBY]];
    }
}

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
void Clock_Ip_SpecificSetUserAccessAllowed(void)
{
    #ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
#if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    OsIf_Trusted_Call(Clock_Ip_PowerClockIpModules);
#else
    Clock_Ip_PowerClockIpModules();
#endif
#else
    Clock_Ip_PowerClockIpModules();
#endif
    /* PLLDIG SetUserAccessAllowed */
#if ( defined(MCAL_PLLDIG_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_PLLDIG_REG_PROT_AVAILABLE)
    #if (defined(IP_PLL_BASE))
    SET_USER_ACCESS_ALLOWED(IP_PLL_BASE, PLLDIG_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_PLLDIG_REG_PROT_AVAILABLE */

    /* PLLDIG SetUserAccessAllowed */
#if ( defined(MCAL_PLLDIG_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_PLLDIG_REG_PROT_AVAILABLE)
    #if (defined(IP_PLL_AUX_BASE))
    SET_USER_ACCESS_ALLOWED(IP_PLL_AUX_BASE, PLLDIG_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_PLLDIG_REG_PROT_AVAILABLE */
    /* FXOSC SetUserAccessAllowed */
#if (defined(MCAL_FXOSC_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_FXOSC_REG_PROT_AVAILABLE)
    #if (defined(IP_FXOSC_BASE))
    SET_USER_ACCESS_ALLOWED(IP_FXOSC_BASE, FXOSC_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_FXOSC_REG_PROT_AVAILABLE */

    /* MC_CGM SetUserAccessAllowed */
#if ( defined(MCAL_MC_CGM_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_MC_CGM_REG_PROT_AVAILABLE)
    #if (defined(IP_MC_CGM_BASE))
    SET_USER_ACCESS_ALLOWED(IP_MC_CGM_BASE, MC_CGM_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_MC_CGM_REG_PROT_AVAILABLE */

    /* CMU SetUserAccessAllowed */
#if (defined(MCAL_CMU_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_CMU_REG_PROT_AVAILABLE)
    #if (defined(IP_CMU_0_BASE))
    /* Check clock status for CMU0 */
    SET_USER_ACCESS_ALLOWED(IP_CMU_0_BASE, CMU_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_CMU_REG_PROT_AVAILABLE */

/* SRAM SetUserAccessAllowed */
#if (defined(MCAL_PRAMC_REG_PROT_AVAILABLE))
  #if (STD_ON == MCAL_PRAMC_REG_PROT_AVAILABLE)
    #if (defined(IP_PRAMC_0_BASE))
    SET_USER_ACCESS_ALLOWED(IP_PRAMC_0_BASE, PRAMC_PROT_MEM_U32);
    #endif
    #if (defined(IP_PRAMC_1_BASE))
    SET_USER_ACCESS_ALLOWED(IP_PRAMC_1_BASE, PRAMC_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_PRAMC_REG_PROT_AVAILABLE */

/* MC_ME SetUserAccessAllowed */
#if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE ))
  #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE )
    #if (defined(IP_MC_ME_BASE))
        SET_USER_ACCESS_ALLOWED(IP_MC_ME_BASE, MC_ME_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_MC_ME_REG_PROT_AVAILABLE  */

/* FLASH_C40ASF SetUserAccessAllowed */
#if (defined(MCAL_C40ASF_REG_PROT_AVAILABLE ))
  #if (STD_ON == MCAL_C40ASF_REG_PROT_AVAILABLE )
    #if (defined(IP_FLASH_BASE))
        SET_USER_ACCESS_ALLOWED(IP_FLASH_BASE, C40ASF_PROT_MEM_U32);
    #endif
  #endif
#endif /* MCAL_C40ASF_REG_PROT_AVAILABLE  */
}
#endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

void Clock_Ip_Command(Clock_Ip_ClockConfigType const * Config, Clock_Ip_CommandType Command)
{
    switch(Command)
    {
        case CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND:
            Clock_Ip_ClockInitializeObjects();
            break;
        case CLOCK_IP_INITIALIZE_PLATFORM_COMMAND:
            Clock_Ip_SpecificPlatformInitClock(Config);
            break;
#ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
        case CLOCK_IP_SET_USER_ACCESS_ALLOWED_COMMAND:
            OsIf_Trusted_Call(Clock_Ip_SpecificSetUserAccessAllowed);
            break;
    #endif
#endif
        default:
            /* Command is not implemented on this platform */
            break;
    }
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES

/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
/* Set Flash wait state */
void Clock_Ip_FLASH_SetFlashIWS(void)
{
    Clock_Ip_SetFlashWaitStatesCallback();
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#endif

#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES


/* Clock start rom section code */
#define MCU_START_SEC_CODE_AC

#include "Mcu_MemMap.h"

void Clock_Ip_PRAMCSetRamIWS(void)
{
    uint32 ControllerRamFrequency = 0U;   /* Frequency at which PRAM controller is working */
    uint32 ArrayRamFrequency = 0U;        /* Frequency at which system ram is working */

    uint32 Pram0RegVal = IP_PRAMC_0->PRCR1;
#ifdef IP_PRAMC_1
    uint32 Pram1RegVal = IP_PRAMC_1->PRCR1;
#endif

#if defined(CLOCK_IP_HAS_CORE_CLK)
    ControllerRamFrequency = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[CORE_CLK]].ConfiguredFrequencyValue;
#endif

#if defined(CLOCK_IP_HAS_AIPS_PLAT_CLK)
    ArrayRamFrequency = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[AIPS_PLAT_CLK]].ConfiguredFrequencyValue;
#endif

    /* if controller is working at a higher frequency than array ram (system/physical ram) */
    if (ControllerRamFrequency > ArrayRamFrequency)
    {
        /* Enable RAM WS */
        Pram0RegVal |= PRAMC_PRCR1_FT_DIS_MASK;
#ifdef IP_PRAMC_1
        Pram1RegVal |= PRAMC_PRCR1_FT_DIS_MASK;
#endif

        /* Read bursts are optimized when flow-through is disabled */
        Pram0RegVal &= ~PRAMC_PRCR1_P0_BO_DIS_MASK;
#ifdef IP_PRAMC_1
        Pram1RegVal &= ~PRAMC_PRCR1_P0_BO_DIS_MASK;
#endif
    }
    else
    {
        /* Disable RAM WS */
        Pram0RegVal &= ~PRAMC_PRCR1_FT_DIS_MASK;
#ifdef IP_PRAMC_1
        Pram1RegVal &= ~PRAMC_PRCR1_FT_DIS_MASK;
#endif
    }

    IP_PRAMC_0->PRCR1 = Pram0RegVal;
#ifdef IP_PRAMC_1
    IP_PRAMC_1->PRCR1 = Pram1RegVal;
#endif
}

/* Clock stop rom section code */
#define MCU_STOP_SEC_CODE_AC
#include "Mcu_MemMap.h"

#endif


#ifdef __cplusplus
}
#endif

/** @} */

