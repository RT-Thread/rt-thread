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
*   @file       Clock_Ip_Gate.c
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
#define CLOCK_IP_GATE_VENDOR_ID_C                      43
#define CLOCK_IP_GATE_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_GATE_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_GATE_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_GATE_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_GATE_SW_MINOR_VERSION_C               0
#define CLOCK_IP_GATE_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Gate.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_GATE_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Gate.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Gate.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_GATE_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_GATE_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_GATE_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Gate.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Gate.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_GATE_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_GATE_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_GATE_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Gate.c and Clock_Ip_Private.h are different"
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

static void Clock_Ip_ClockSetGateEmpty(Clock_Ip_GateConfigType const* Config);
static void Clock_Ip_ClockUpdateGateEmpty(Clock_Ip_NameType ClockName, boolean Gate);
#ifdef CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST
static void Clock_Ip_ClockSetGateMcMePartitionCollectionClockRequest(Clock_Ip_GateConfigType const* Config);
static void Clock_Ip_ClockUpdateGateMcMePartitionCollectionClockRequest(Clock_Ip_NameType ClockName, boolean Gate);
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

static void Clock_Ip_ClockSetGateEmpty(Clock_Ip_GateConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}
static void Clock_Ip_ClockUpdateGateEmpty(Clock_Ip_NameType ClockName, boolean Gate)
{
    (void)ClockName;
    (void)Gate;
    /* No implementation */
}

#ifdef CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST
static void Clock_Ip_ClockSetGateMcMePartitionCollectionClockRequest(Clock_Ip_GateConfigType const* Config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    const Clock_Ip_GateInfoType * GateInformation;
    uint32 Partition;
    uint32 Collection;
    uint32 EnableRequest;
    uint32 HwProcessUpdateFinished;
    uint32 PeripheralGateStatusValue;

    if (NULL_PTR != Config)
    {
        GateInformation = &Clock_Ip_axGateInfo[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_GATE_INDEX]];
        Partition      = GateInformation->PartitionValue;
        Collection     = GateInformation->ColectionValue;
        EnableRequest  = GateInformation->RequestValueMask;

        if (Config->Enable != 0U)
        {
            /* Partition PRTN_COFB_STAT is reserved in S32G2XX and S32G3XX */
            #ifdef CLOCK_IP_PLATFORM_SPECIFIC1
            if (0U == (Clock_Ip_apxMcMeGetPartitions[Partition]->PRTN_COFB_STAT[Collection] & EnableRequest))
            #else
            if (0U == (Clock_Ip_apxMcMeSetPartitions[Partition]->PRTN_COFB_CLKEN[Collection] & EnableRequest))
            #endif
            {

                Clock_Ip_apxMcMeSetPartitions[Partition]->PRTN_COFB_CLKEN[Collection] |= EnableRequest;
                Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PCONF  |= MC_ME_PRTN1_PCONF_PCE_MASK;
                Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PUPD   |= MC_ME_PRTN1_PUPD_PCUD_MASK;
                Clock_Ip_McMeEnterKey();

                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                    Otherwise wait for hardware status to update.
                 */
                HwProcessUpdateFinished = (Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK);
                PeripheralGateStatusValue = (Clock_Ip_apxMcMeGetPartitions[Partition]->PRTN_COFB_STAT[Collection] & EnableRequest);
                if ((0U != HwProcessUpdateFinished) || (0U == PeripheralGateStatusValue))

                {
                    /* Wait for hardware to update */
                    Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
                    do
                    {
                        TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                        /*
                            Check whether hardware update process finished (PCUD is zero in this case)
                            and peripheral clock gate state (Gate State is 0U in this case).
                         */
                        HwProcessUpdateFinished = (Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK);
                        PeripheralGateStatusValue = (Clock_Ip_apxMcMeGetPartitions[Partition]->PRTN_COFB_STAT[Collection] & EnableRequest);
                        if ((0U == HwProcessUpdateFinished) && (0U != PeripheralGateStatusValue))
                        {
                            break;
                        }
                    }while (FALSE == TimeoutOccurred);

                    if (TRUE == TimeoutOccurred)
                    {
                        /* Report timeout error */
                        Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
                    }
                }
            }
        }
        else
        {
            /* Partition PRTN_COFB_STAT is reserved in S32G2XX and S32G3XX */
            #ifdef CLOCK_IP_PLATFORM_SPECIFIC1
            if (0U != (Clock_Ip_apxMcMeGetPartitions[Partition]->PRTN_COFB_STAT[Collection] & EnableRequest))
            #else
            if (0U != (Clock_Ip_apxMcMeSetPartitions[Partition]->PRTN_COFB_CLKEN[Collection] & EnableRequest))
            #endif
            {

                Clock_Ip_apxMcMeSetPartitions[Partition]->PRTN_COFB_CLKEN[Collection] &= (~EnableRequest);
                Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PCONF  |= MC_ME_PRTN1_PCONF_PCE_MASK;
                Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PUPD   |= MC_ME_PRTN1_PUPD_PCUD_MASK;
                Clock_Ip_McMeEnterKey();

                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                    Otherwise wait for hardware status to update.
                 */
                HwProcessUpdateFinished = (Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK);
                PeripheralGateStatusValue = (Clock_Ip_apxMcMeGetPartitions[Partition]->PRTN_COFB_STAT[Collection] & EnableRequest);
                if ((0U != HwProcessUpdateFinished) || (0U != PeripheralGateStatusValue))

                {
                    /* Wait for hardware to update */
                    Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
                    do
                    {
                        TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                        /*
                            Check whether hardware update process finished (PCUD is zero in this case)
                            and peripheral clock gate state (Gate State is 0U in this case).
                         */
                        HwProcessUpdateFinished = (Clock_Ip_apxMcMeTriggerPartitions[Partition]->PRTN_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK);
                        PeripheralGateStatusValue = (Clock_Ip_apxMcMeGetPartitions[Partition]->PRTN_COFB_STAT[Collection] & EnableRequest);
                        if ((0U == HwProcessUpdateFinished) && (0U == PeripheralGateStatusValue))
                        {
                            break;
                        }
                    }while (FALSE == TimeoutOccurred);

                    /* timeout notification */
                    if (TRUE == TimeoutOccurred)
                    {
                        /* Report timeout error */
                        Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
                    }
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
        (void)GateInformation;
        (void)Partition;
        (void)Collection;
        (void)EnableRequest;
    }
}

static void Clock_Ip_ClockUpdateGateMcMePartitionCollectionClockRequest(Clock_Ip_NameType ClockName, boolean Gate)
{
    Clock_Ip_GateConfigType Config;

    Config.Name = ClockName;
    if (TRUE == Gate)
    {
        Config.Enable = 0U;
    }
    else
    {
        Config.Enable = 1U;
    }
    /* Write configuration to register */
    Clock_Ip_ClockSetGateMcMePartitionCollectionClockRequest(&Config);
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

const Clock_Ip_GateCallbackType Clock_Ip_axGateCallbacks[CLOCK_IP_GATE_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_ClockSetGateEmpty,     /* Set */
        &Clock_Ip_ClockUpdateGateEmpty,  /* Update */
    },
#ifdef CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST
    {
        &Clock_Ip_ClockSetGateMcMePartitionCollectionClockRequest,      /* Set */
        &Clock_Ip_ClockUpdateGateMcMePartitionCollectionClockRequest,   /* Update */
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
