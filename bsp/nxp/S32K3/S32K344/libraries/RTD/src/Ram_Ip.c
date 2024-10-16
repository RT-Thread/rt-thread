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
*   @file       Ram_Ip.c
*   @version    5.0.0
*
*   @brief   RAM driver implementations.
*   @details RAM driver implementations.
*
*   @addtogroup RAM_DRIVER Ram Ip Driver
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
#include "Ram_Ip.h"
#include "OsIf.h"

    #if (defined(RAM_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT))
        #if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
            #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)
                #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
                #include "RegLockMacros.h"
            #endif /* (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE) */
        #endif
    #endif /* (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT) */
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RAM_IP_VENDOR_ID_C                      43
#define RAM_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define RAM_IP_AR_RELEASE_MINOR_VERSION_C       7
#define RAM_IP_AR_RELEASE_REVISION_VERSION_C    0
#define RAM_IP_SW_MAJOR_VERSION_C               5
#define RAM_IP_SW_MINOR_VERSION_C               0
#define RAM_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Ram_Ip.c file and Ram_Ip.h file are of the same vendor */
#if (RAM_IP_VENDOR_ID_C != RAM_IP_VENDOR_ID)
    #error "Ram_Ip.c and Ram_Ip.h have different vendor ids"
#endif

/* Check if Ram_Ip.c file and Ram_Ip.h file are of the same Autosar version */
#if ((RAM_IP_AR_RELEASE_MAJOR_VERSION_C != RAM_IP_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_AR_RELEASE_MINOR_VERSION_C != RAM_IP_AR_RELEASE_MINOR_VERSION) || \
     (RAM_IP_AR_RELEASE_REVISION_VERSION_C != RAM_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Ram_Ip.c and Ram_Ip.h are different"
#endif

/* Check if Ram_Ip.c file and Ram_Ip.h file are of the same Software version */
#if ((RAM_IP_SW_MAJOR_VERSION_C != RAM_IP_SW_MAJOR_VERSION) || \
     (RAM_IP_SW_MINOR_VERSION_C != RAM_IP_SW_MINOR_VERSION) || \
     (RAM_IP_SW_PATCH_VERSION_C != RAM_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Ram_Ip.c and Ram_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Ram_Ip.c file and OsIf.h file are of the same Autosar version */
#if ((RAM_IP_AR_RELEASE_MAJOR_VERSION_C    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_AR_RELEASE_MINOR_VERSION_C    != OSIF_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Ram_Ip.c and OsIf.h are different"
#endif
#endif

    #if (defined(RAM_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT))
        #if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
            #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)
                #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
                /* Check if Ram_Ip.c file and RegLockMacros.h file are of the same Autosar version */
                    #if ((RAM_IP_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
                        (RAM_IP_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
                        #error "AutoSar Version Numbers of Ram_Ip.c and RegLockMacros.h are different"
                    #endif
                #endif
            #endif /* (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE) */
        #endif
    #endif /* RAM_IP_ENABLE_USER_MODE_SUPPORT */
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
static void Ram_Ip_StartTimeout(uint32 *StartTimeOut,
                                uint32 *ElapsedTimeOut,
                                uint32 *TimeoutTicksOut,
                                uint32 TimeoutUs
                                );
static boolean Ram_Ip_TimeoutExpired(   uint32 *StartTimeInOut,
                                        uint32 *ElapsedTimeInOut,
                                        uint32 TimeoutTicks
                                    );

static void Ram_Ip_ReportRamErrorsEmptyCallback(Ram_Ip_RamReportErrorType Error,
                                                uint8 ErrorCode
                                                );
static void Ram_Ip_ReportRamErrors( Ram_Ip_RamReportErrorType Error,
                                    uint8 ErrorCode
                                   );
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#if (RAM_IP_GET_RAM_STATE_API == STD_ON)

#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Ram Report Error Callback */
static Ram_Ip_ReportErrorsCallbackType Ram_Ip_pfReportErrorsCallback = &Ram_Ip_ReportRamErrorsEmptyCallback;

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#endif /* (RAM_IP_GET_RAM_STATE_API == STD_ON) */
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Ram_Ip_StartTimeout
 * Description   : Checks for timeout condition
 *
 *END**************************************************************************/
static void Ram_Ip_StartTimeout(uint32 *StartTimeOut,
                                uint32 *ElapsedTimeOut,
                                uint32 *TimeoutTicksOut,
                                uint32 TimeoutUs
                                )
{
    *StartTimeOut    = OsIf_GetCounter(RAM_IP_TIMEOUT_TYPE);
    *ElapsedTimeOut  = 0U;
    *TimeoutTicksOut = OsIf_MicrosToTicks(TimeoutUs, RAM_IP_TIMEOUT_TYPE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Ram_Ip_TimeoutExpired
 * Description   : Checks for timeout expiration condition
 *
 *END**************************************************************************/
static boolean Ram_Ip_TimeoutExpired   (uint32 *StartTimeInOut,
                                        uint32 *ElapsedTimeInOut,
                                        uint32 TimeoutTicks
                                        )
{
    boolean RetVal = FALSE;
    *ElapsedTimeInOut += OsIf_GetElapsed(StartTimeInOut, RAM_IP_TIMEOUT_TYPE);

    if (*ElapsedTimeInOut >= TimeoutTicks)
    {
        RetVal = TRUE;
    }
    return RetVal;
}
#endif

#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
static void Ram_Ip_ReportRamErrorsEmptyCallback(Ram_Ip_RamReportErrorType Error,
                                                uint8 ErrorCode
                                                )
{
    /* No implementation */
    (void)Error;
    (void)ErrorCode;
}

/* Report Ram errors */
static void Ram_Ip_ReportRamErrors( Ram_Ip_RamReportErrorType Error,
                                    uint8 ErrorCode
                                   )
{
    Ram_Ip_pfReportErrorsCallback(Error, ErrorCode);
}
#endif

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

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
* @retval           RAM_IP_STATUS_OK        The RAM section check was successful.
* @retval           RAM_IP_STATUS_NOT_OK    The RAM section check was not successful.
*
* @implements Ram_Ip_InitRamSection_Activity
*
*/
Ram_Ip_StatusType Ram_Ip_InitRamSection(const Ram_Ip_RamConfigType * RamConfigPtr)
{
    /* Result of the operation. */
    Ram_Ip_StatusType RamStatus = RAM_IP_STATUS_OK;
    /* Variable for indexing RAM sections. */
    Ram_Ip_RamIndexType RamCounter;
    /* Limit of RamCounter. */
    Ram_Ip_RamSizeType RamCounterLimit;

    RAM_IP_DEV_ASSERT(NULL_PTR != RamConfigPtr);

    RamCounterLimit = (Ram_Ip_RamSizeType)( ((Ram_Ip_RamSizeType)(RamConfigPtr->RamSize)) / (RamConfigPtr->RamWriteSize) );

    RamStatus = RAM_IP_STATUS_OK;
    RamCounter = (Ram_Ip_RamIndexType)0UL;
    while ((RamCounter < RamCounterLimit) && (RAM_IP_STATUS_OK == RamStatus))
    {
        switch (RamConfigPtr->RamWriteSize)
        {
            case (Ram_Ip_RamWriteSizeType)1U:

                ( *((uint8 (*)[1U]) ((Ram_Ip_uintPtrType) RamConfigPtr->RamBaseAddrPtr)) )[RamCounter]  = (uint8) (RamConfigPtr->RamDefaultValue);
                break;

            case (Ram_Ip_RamWriteSizeType)2U:

                ( *((uint16 (*)[1U]) ((Ram_Ip_uintPtrType) RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] = (uint16) ( ((uint16)(RamConfigPtr->RamDefaultValue) << 0U) | ((uint16)(RamConfigPtr->RamDefaultValue) << 8U) );
                break;

            case (Ram_Ip_RamWriteSizeType)4U:

                ( *((uint32 (*)[1U]) ((Ram_Ip_uintPtrType) RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] = \
                (uint32) ( ((uint32)(RamConfigPtr->RamDefaultValue) << 0U) | ((uint32)(RamConfigPtr->RamDefaultValue) << 8U)  |\
                          ((uint32)(RamConfigPtr->RamDefaultValue) << 16U) | ((uint32)(RamConfigPtr->RamDefaultValue) << 24U) );
                break;

            case (Ram_Ip_RamWriteSizeType)8U:

                ( *((uint64 (*)[1U]) ((Ram_Ip_uintPtrType) RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] = \
                  (uint64) ( ((uint64)(RamConfigPtr->RamDefaultValue) << 0U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 8U)  |\
                            ((uint64)(RamConfigPtr->RamDefaultValue) << 16U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 24U) |\
                            ((uint64)(RamConfigPtr->RamDefaultValue) << 32U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 40U) |\
                            ((uint64)(RamConfigPtr->RamDefaultValue) << 48U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 56U) );

                break;
            default:
                RamStatus = RAM_IP_STATUS_NOT_OK;
                break;
        }
        RamCounter++;
    }

    if ( RAM_IP_STATUS_OK == RamStatus )
    {
        RamCounter = (Ram_Ip_RamIndexType)0UL;
        /* Check if RAM was initialized correctly. */
        while ((RamCounter < RamCounterLimit) && (RAM_IP_STATUS_OK == RamStatus))
        {
            switch (RamConfigPtr->RamWriteSize)
            {
                case (Ram_Ip_RamWriteSizeType)1U:

                    if ( (uint8) (RamConfigPtr->RamDefaultValue)  != ( *((uint8 (*)[1U]) ((Ram_Ip_uintPtrType)RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] )
                    {
                        RamStatus = RAM_IP_STATUS_NOT_OK;
                    }
                    break;

                case (Ram_Ip_RamWriteSizeType)2U:

                    if ( (uint16) ( ((uint16)(RamConfigPtr->RamDefaultValue) << 0U) | ((uint16)(RamConfigPtr->RamDefaultValue) << 8U) ) != ( *((uint16 (*)[1U]) ((Ram_Ip_uintPtrType)RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] )
                    {
                        RamStatus = RAM_IP_STATUS_NOT_OK;
                    }
                    break;

                case (Ram_Ip_RamWriteSizeType)4U:

                    if ( (uint32)  ( ((uint32)(RamConfigPtr->RamDefaultValue) << 0U) | ((uint32)(RamConfigPtr->RamDefaultValue) << 8U)  |\
                                    ((uint32)(RamConfigPtr->RamDefaultValue) << 16U) | ((uint32)(RamConfigPtr->RamDefaultValue) << 24U) ) != \
                        ( *((uint32 (*)[1U]) ((Ram_Ip_uintPtrType)RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] )
                    {
                        RamStatus = RAM_IP_STATUS_NOT_OK;
                    }
                    break;

                case (Ram_Ip_RamWriteSizeType)8U:

                    if ( (uint64) ( ((uint64)(RamConfigPtr->RamDefaultValue) << 0U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 8U)  |\
                                   ((uint64)(RamConfigPtr->RamDefaultValue) << 16U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 24U) |\
                                   ((uint64)(RamConfigPtr->RamDefaultValue) << 32U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 40U) |\
                                   ((uint64)(RamConfigPtr->RamDefaultValue) << 48U) | ((uint64)(RamConfigPtr->RamDefaultValue) << 56U) ) != \
                        ( *((uint64 (*)[1U]) ((Ram_Ip_uintPtrType)RamConfigPtr->RamBaseAddrPtr)) )[RamCounter] )
                    {
                        RamStatus = RAM_IP_STATUS_NOT_OK;
                    }
                    break;

                default:
                    RamStatus = RAM_IP_STATUS_NOT_OK;
                    break;
            }
            RamCounter++;
        }
    }

    return RamStatus;
}
#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
/**
* @brief            This service provides the actual status of the microcontroller Ram. (if supported)
* @details
*
* @param[in]        void
*
* @return           State of RAM
*
* @implements Ram_Ip_GetRamState_Activity
*
*/
Ram_Ip_RamStateType Ram_Ip_GetRamState(void)
{
    Ram_Ip_RamStateType RamState = RAM_IP_RAMSTATE_INVALID;
    uint32 TempReg;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;

    /* MC_ME SetUserAccessAllowed */
    #if (defined(RAM_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT))
        #if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE ))
            #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE )
                #if (defined(IP_MC_ME_BASE))
    OsIf_Trusted_Call2params(SET_USER_ACCESS_ALLOWED,IP_MC_ME_BASE,MC_ME_PROT_MEM_U32);
                #endif
            #endif
        #endif /* MCAL_MC_ME_REG_PROT_AVAILABLE  */
    #endif /* (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT) */

    /* Check clock status for STCU2 */
    if (((IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK104_MASK) == 0U))
    {
        /* Enable clock for STCU2 device */
        IP_MC_ME->PRTN1_COFB3_CLKEN |= MC_ME_PRTN1_COFB3_CLKEN_REQ104(1U);   /* REQ104: the clock enable control for STCU2 */
        IP_MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        IP_MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        IP_MC_ME->CTL_KEY = 0x5AF0U;                                         /* Enter key */
        IP_MC_ME->CTL_KEY = 0xA50FU;
        
        /* 
            Check whether hardware update process finished (PCUD is zero in this case)
            and peripheral clock gate state (Gate State is 1U in this case).
            Otherwise wait for hardware status to update.
         */
        if ((0U != (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) ||
            (0U == (IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK104_MASK)))

        {
            /* Wait for hardware to update */
            Ram_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, RAM_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Ram_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                /*
                    Check whether hardware update process finished (PCUD is zero in this case)
                    and peripheral clock gate state (Gate State is 1U in this case).
                 */
                if ((0U == (IP_MC_ME->PRTN1_PUPD & MC_ME_PRTN1_PUPD_PCUD_MASK)) &&
                    (0U != (IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK104_MASK)))
                {
                    break;
                }
            }while (FALSE == TimeoutOccurred);

            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                Ram_Ip_ReportRamErrors(RAM_IP_REPORT_TIMEOUT_ERROR,RAM_IP_ERR_CODE_RESERVED);
            }
        }
    }
    /* Stay in this loop until these registers are automatically updated following the
     * completion of the MBIST run. */
    Ram_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, RAM_IP_TIMEOUT_VALUE_US);
    do
    {
        TimeoutOccurred = Ram_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        /* Execute WFI */
    #ifdef STCU_MBESW_COUNT
        TempReg = IP_STCU->MBESW[0];
    #else
        TempReg = IP_STCU->MBESW0;
    #endif

    } while ( (STCU2_MBESW0_RAM_TEST_MASK32 != (TempReg & STCU2_MBESW0_RAM_TEST_MASK32)) && (!TimeoutOccurred) );

    if (!TimeoutOccurred)
    {
    #ifdef STCU_MBSSW_COUNT
        TempReg = IP_STCU->MBSSW[0];
    #else
        TempReg = IP_STCU->MBSSW0;
    #endif

        if (STCU2_MBSSW0_RAM_TEST_MASK32 == (TempReg & STCU2_MBSSW0_RAM_TEST_MASK32))
        {
            RamState = RAM_IP_RAMSTATE_VALID;
        }
    }
    else
    {
        /* report callback here */
        Ram_Ip_ReportRamErrors(RAM_IP_REPORT_TIMEOUT_ERROR,RAM_IP_ERR_CODE_RESERVED);
    }

    return RamState;
}
#endif

#if (RAM_IP_GET_RAM_STATE_API == STD_ON)
/**
* @brief            This function installs a callback for reporting errors from Ram driver.
* @details
*
* @param[in]        ReportErrorsCallback    Callback to be installed.
*
* @return           void
*
* @implements Ram_Ip_InstallNotificationsCallback_Activity
*/
void Ram_Ip_InstallNotificationsCallback(Ram_Ip_ReportErrorsCallbackType ReportErrorsCallback)
{
    RAM_IP_DEV_ASSERT(NULL_PTR != ReportErrorsCallback);
    Ram_Ip_pfReportErrorsCallback = ReportErrorsCallback;
}
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

