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
*   @file       Power_Ip_MC_RGM.c
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
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_Private.h"
#include "Power_Ip_MC_RGM.h"
#include "Power_Ip_MC_ME.h"

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_MC_RGM_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE)
      #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
      #include "RegLockMacros.h"
    #endif /* (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_MC_RGM_VENDOR_ID_C                      43
#define POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_MC_RGM_SW_MAJOR_VERSION_C               5
#define POWER_IP_MC_RGM_SW_MINOR_VERSION_C               0
#define POWER_IP_MC_RGM_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_MC_RGM.c file and Power_Ip_Private.h file are of the same vendor */
#if (POWER_IP_MC_RGM_VENDOR_ID_C != POWER_IP_PRIVATE_VENDOR_ID)
    #error "Power_Ip_MC_RGM.c and Power_Ip_Private.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_Private.h file are of the same Autosar version */
#if ((POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_RGM.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_Private.h file are of the same Software version */
#if ((POWER_IP_MC_RGM_SW_MAJOR_VERSION_C != POWER_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_SW_MINOR_VERSION_C != POWER_IP_PRIVATE_SW_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_SW_PATCH_VERSION_C != POWER_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_RGM.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_MC_RGM.h file are of the same vendor */
#if (POWER_IP_MC_RGM_VENDOR_ID_C != POWER_IP_MC_RGM_VENDOR_ID)
    #error "Power_Ip_MC_RGM.c and Power_Ip_MC_RGM.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_MC_RGM.h file are of the same Autosar version */
#if ((POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_RGM.c and Power_Ip_MC_RGM.h are different"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_MC_RGM.h file are of the same Software version */
#if ((POWER_IP_MC_RGM_SW_MAJOR_VERSION_C != POWER_IP_MC_RGM_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_SW_MINOR_VERSION_C != POWER_IP_MC_RGM_SW_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_SW_PATCH_VERSION_C != POWER_IP_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_RGM.c and Power_Ip_MC_RGM.h are different"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_MC_ME.h file are of the same vendor */
#if (POWER_IP_MC_RGM_VENDOR_ID_C != POWER_IP_MC_ME_VENDOR_ID)
    #error "Power_Ip_MC_RGM.c and Power_Ip_MC_ME.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_MC_ME.h file are of the same Autosar version */
#if ((POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_RGM.c and Power_Ip_MC_ME.h are different"
#endif

/* Check if Power_Ip_MC_RGM.c file and Power_Ip_MC_ME.h file are of the same Software version */
#if ((POWER_IP_MC_RGM_SW_MAJOR_VERSION_C != POWER_IP_MC_ME_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_SW_MINOR_VERSION_C != POWER_IP_MC_ME_SW_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_SW_PATCH_VERSION_C != POWER_IP_MC_ME_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_RGM.c and Power_Ip_MC_ME.h are different"
#endif

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_MC_RGM_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE)
        #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if Power_Ip_MC_RGM.c file and RegLockMacros.h file are of the same Autosar version */
            #if ((POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
                (POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
                #error "AutoSar Version Numbers of Power_Ip_MC_RGM.c and RegLockMacros.h are different"
            #endif
        #endif
    #endif /* (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */
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
#define MCU_START_SEC_VAR_CLEARED_32

#include "Mcu_MemMap.h"

static uint32 DesResetStatus;
static uint32 FesResetStatus;

#if (defined(POWER_IP_RESET_DURING_STANDBY_SUPPORTED) && (POWER_IP_RESET_DURING_STANDBY_SUPPORTED == STD_ON))
    #if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
static uint32 StandbyResetStatus =0U;
#endif
#endif

#define MCU_STOP_SEC_VAR_CLEARED_32

#include "Mcu_MemMap.h"


#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

static Power_Ip_MC_RGM_Type * Power_Ip_pxMC_RGM = (Power_Ip_MC_RGM_Type *)IP_MC_RGM_BASE;
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mcu_MemMap.h"

#if (defined(POWER_IP_RESET_ALTERNATE_ISR_USED) && (POWER_IP_RESET_ALTERNATE_ISR_USED == STD_ON))
static volatile Power_MC_RGM_StatusType Power_Ip_eMcRgmStatus = POWER_MC_RGM_UNINIT;
#endif

#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
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


static void Power_Ip_MC_RGM_ClearFesResetFlags(uint32 RegValue);
static void Power_Ip_MC_RGM_ClearDesResetFlags(uint32 RegValue);
static Power_Ip_ResetType Power_Ip_MC_RGM_CheckResetReason( uint32 ActiveValue,
                                                            uint8 ResetMode,
                                                            uint32 * PositionPtr
                                                            );

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief            This function clears all the reset flags from MC_RGM_FES.
* @details          This function clears all the reset flags from MC_RGM_FES.
*
* @param[in]        RegValue     The value of the MC_RGM_FES register.
*
* @return           void
*
*/
static void Power_Ip_MC_RGM_ClearFesResetFlags(uint32 RegValue)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 RegValueTemp = RegValue;

    /* Clear all the reset flags of MC_RGM_FES */
    if ((uint32)0U != RegValueTemp)
    {
        /* Wait until the update has finished. */
        Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            Power_Ip_pxMC_RGM->FES = RegValueTemp;

            RegValueTemp = Power_Ip_pxMC_RGM->FES & MC_RGM_FES_RWBITS_MASK32;
        }
        while ( ((uint32)0U != RegValueTemp) && (!TimeoutOccurred) );
        /* timeout notification */
        if(TimeoutOccurred)
        {
            Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
        }
    }
}

/**
* @brief            This function clears all the reset flags from MC_RGM_DES.
* @details          This function clears all the reset flags from MC_RGM_DES.
*                   Called by:
*                       - Power_Ip_MC_RGM_GetResetReason().
*                       - Power_Ip_MC_RGM_GetResetRawValue().
*
* @param[in]        RegValue     The value of the MC_RGM_DES register.
*
* @return           void
*
*/
static void Power_Ip_MC_RGM_ClearDesResetFlags(uint32 RegValue)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 RegValueTemp = RegValue;

    /* Clear all the reset flags from MC_RGM_DES */
    if ((uint32)0U != RegValueTemp)
    {
        /* Wait until the update has finished. */
        Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            Power_Ip_pxMC_RGM->DES = RegValueTemp;

            RegValueTemp = Power_Ip_pxMC_RGM->DES & MC_RGM_DES_RWBITS_MASK32;
        }
        while ( ((uint32)0x00U != RegValueTemp) && (!TimeoutOccurred) );
        /* Report error when timeout occurred */
        if (TimeoutOccurred)
        {
            Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
        }
    }
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_MC_RGM_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE)
/**
* @brief            This function will enable writing in User mode by configuring REG_PROT
*/
void Power_Ip_MC_RGM_SetUserAccessAllowed(void)
{
#if (defined(IP_MC_RGM_BASE))
    SET_USER_ACCESS_ALLOWED(IP_MC_RGM_BASE, MC_RGM_PROT_MEM_U32);
#endif
}
    #endif /* (STD_ON == MCAL_MC_RGM_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */



/**
* @brief            This function initializes the Reset parameters.
* @details          This function configures disabling the functional event reset, disabling the
*                   destructive event reset, the functional event alternate request, the
*                   destructive event alternate request, the functional event short sequence, the
*                   standby reset sequence and enabling the functional bidirectional reset.
*
* @param[in]        ConfigPtr   Pointer to the MC_RGM configuration structure.
*
* @return           void
*
*/
void Power_Ip_MC_RGM_ResetInit(const Power_Ip_MC_RGM_ConfigType * ConfigPtr)
{
    /* Temporary variables for FES and DES register values. */
    uint32 FesResetReason = 0U;
    uint32 DesResetReason = 0U;


    /* Warning: It is important to clear the RGM_FES register before setting any of the bits
     * in the RGM_FERD register to '1'. Otherwise, a redundant interrupt request may occur.
     * Also, each byte in RGM_FERD can be written only once after a power-on reset. */

    /* Check "Functional Reset Reason" from FES Status Register. */
    FesResetReason = Power_Ip_pxMC_RGM->FES;

    /* Store the contents of FES. */
    if ((uint32)0U != FesResetReason)
    {
        FesResetStatus = FesResetReason;
        Power_Ip_MC_RGM_ClearFesResetFlags(FesResetReason);
    }

#if (defined(POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT) && (POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT == STD_ON))
    /* 'Functional' Event Reset Disable Register (RGM_FERD) */
    Power_Ip_pxMC_RGM->FERD = ConfigPtr->FuncResetOpt;
#endif /* POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT */

    /* Check "Destructive Reset Reason" from DES Status Register. */
    DesResetReason = Power_Ip_pxMC_RGM->DES;

    /* Enable (reconfigure) FRET only on "Power On Reset" or "Destructive Reset" event.   */
    /* Otherwise, the "Functional Reset Escalation" will not work, because the "internal  */
    /* functional reset counter" will be reset to 0 each time "Mcu_Init" is called.       */
    /* Therefore, it will never reach the functional threshold value.                     */
    if(MC_RGM_FRET_FRET((uint32)0U) != ConfigPtr->FesThresholdReset)
    {
        if ((uint32)0U != DesResetReason)
        {
            /* 'Functional' Reset Escalation Threshold Register (MC_RGM_FRET) */
            Power_Ip_pxMC_RGM->FRET = ConfigPtr->FesThresholdReset;
        }
    }
    else
    {
        Power_Ip_pxMC_RGM->FRET = (uint32)0U;
    }
    /* Enable (reconfigure) DRET only on "Power On Reset" event.                          */
    /* Otherwise, the "Destructive Reset Escalation" will not work, because the "internal */
    /* destructive reset counter" will be reset to 0 each time "Mcu_Init" is called.      */
    /* Therefore, it will never reach the destructive threshold value.                    */
    if(MC_RGM_DRET_DRET((uint32)0U) != ConfigPtr->DesThresholdReset)
    {
        if (MC_RGM_DES_F_POR_MASK == (DesResetReason & MC_RGM_DES_F_POR_MASK))
        {
            /* 'Destructive' Reset Escalation Threshold Register (MC_RGM_DRET) */
            Power_Ip_pxMC_RGM->DRET = ConfigPtr->DesThresholdReset;
        }
    }
    else
    {
        Power_Ip_pxMC_RGM->DRET = (uint32)0U;
    }

    /* Configure the timeout duration of the functional reset entry timer */
#if defined(POWER_IP_FUNCTIONAL_RESET_ENTRY_TIMEOUT_SUPPORT)
  #if (POWER_IP_FUNCTIONAL_RESET_ENTRY_TIMEOUT_SUPPORT == STD_ON)
    Power_Ip_pxMC_RGM->FRENTC = ConfigPtr->ResetEntryTimeout;
  #endif
#endif

#if (defined(POWER_IP_RESET_ALTERNATE_ISR_USED) && (POWER_IP_RESET_ALTERNATE_ISR_USED == STD_ON))
    Power_Ip_eMcRgmStatus = POWER_MC_RGM_INIT;
#endif
}


/**
* @brief            This function check reset reason RGM.
* @details          This function check reset reason RGM.
*
* @param[in]        uint32 ActiveValue, uint8 ResetMode, uint32 * PositionPt
*
* @return           ResetReason
*
*/
static Power_Ip_ResetType Power_Ip_MC_RGM_CheckResetReason(uint32 ActiveValue, uint8 ResetMode, uint32 * PositionPtr)
{
    /* Temporary variables for DES and FES registers value. */
    Power_Ip_ResetType ResetReason = MCU_NO_RESET_REASON;
    uint32 ResetMask;
    uint32 NumberOfFlags = 0U;
    uint32 Index;
    uint32 DynamicMask;
    uint32 Position = *PositionPtr;

    /* Type 0 : destructive reset
       Type 1 : functional reset */
    if (0U == ResetMode)
    {
#if ( (defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || \
    defined(POWER_IP_DERIVATIVE_003) || defined(POWER_IP_DERIVATIVE_004) || \
    defined(POWER_IP_DERIVATIVE_005) || defined(POWER_IP_DERIVATIVE_007) || \
    defined(POWER_IP_DERIVATIVE_009)) && defined(POWER_IP_RESET_REASON_FILTER))
        /* Combination with CM7_CORE_CLK_FAIL bit mask on the derivatives doesn't have to skip CM7_CORE_CLK_FAIL_RESET reason */
        /* The ResetMask variable isn't used to filter the value read from register */
        ResetMask = MC_RGM_DES_RWBITS_MASK32 | MC_RGM_DES_CM7_CORE_CLK_FAIL_MASK32;
#else
        ResetMask = MC_RGM_DES_RWBITS_MASK32;
#endif
    }
    else
    {
#if ( (defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || \
     defined(POWER_IP_DERIVATIVE_004) || defined(POWER_IP_DERIVATIVE_005)) && defined(POWER_IP_RESET_REASON_FILTER) )
        /* Combination with SWT1/SWT2/SWT3 bit mask on the derivatives doesn't have to skip MCU_SWT1_RST_RESET/MCU_SWT2_RST_RESET/MCU_SWT3_RST_RESET reason */
        /* The ResetMask variable isn't used to filter the value read from register */
        ResetMask = (MC_RGM_FES_RWBITS_MASK32 | MC_RGM_FES_SWT1_RST_MASK32 | MC_RGM_FES_SWT2_RST_MASK32 | MC_RGM_FES_SWT3_RST_MASK32);
#elif ( (defined(POWER_IP_DERIVATIVE_003) || defined(POWER_IP_DERIVATIVE_007)) && defined(POWER_IP_RESET_REASON_FILTER))
        ResetMask = MC_RGM_FES_RWBITS_MASK32 | MC_RGM_FES_SWT2_RST_MASK32 | MC_RGM_FES_SWT3_RST_MASK32;
#elif ( (defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_009)) && defined(POWER_IP_RESET_REASON_FILTER))
        ResetMask = MC_RGM_FES_RWBITS_MASK32 | MC_RGM_FES_SWT3_RST_MASK32;
#else
        ResetMask = MC_RGM_FES_RWBITS_MASK32;
#endif

#if (!(defined(POWER_IP_DERIVATIVE_008) || defined(POWER_IP_DERIVATIVE_009)))
    #if (defined(MC_RGM_FES_PLL_AUX_MASK32))
        /* Combination with PLL_AUX bit mask on the derivatives doesn't have to skip MCU_PLL_AUX_RESET reason */
        /* The ResetMask variable isn't used to filter the value read from register */
        ResetMask |= MC_RGM_FES_PLL_AUX_MASK32;
    #endif
#endif
    }

    for (Index = 0U; Index < (uint32)32U; Index++)
    {
        DynamicMask = ((uint32)0x01U << Index);
        if ( (uint32)0U != (DynamicMask & ResetMask) )
        {
            if ( (uint32)0U != (DynamicMask & ActiveValue) )
            {
                ResetReason = (Power_Ip_ResetType)Position;
                NumberOfFlags++;

                /*
                   MCU_MULTIPLE_RESET_REASON returned if more than one reset reason.
                   In this case, use function Mcu_GetRawValue to determine.
                */
                if (2U <= NumberOfFlags)
                {
                    ResetReason = MCU_MULTIPLE_RESET_REASON;
                    break;
                }
            }

            Position++;
        }
    }
    /* update value for PositionPtr. It used to calculate in both Des and Fes */
    *PositionPtr = Position;
    (void)NumberOfFlags;
    (void)ActiveValue;

    return ResetReason;
}
/**
* @brief            This function returns the Reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_Ipw_GetResetReason() from IPW.
*
* @return           Reason of the Reset event.
* @retval           Power_Ip_ResetType   Platform-specific enumeration defined in "".
*
* @note             The User should ensure that the reset reason is cleared once it has been read
*                   out to avoid multiple reset reasons. The function Mcu_GetResetReason shall
*                   return MCU_RESET_UNDEFINED if this function is called prior to calling of the
*                   function Mcu_Init, and if supported by the hardware.
*/
Power_Ip_ResetType Power_Ip_MC_RGM_GetResetReason(void)
{
    Power_Ip_ResetType ResetReason;

    /* Temporary variables for DES and FES registers value. */
    uint32 RegValue = 0U;
    uint32 ActiveValue;
    uint32 Position = POWER_IP_FIRST_RESET_REASON_POS;

    /* Check "Destructive Reset Reason" from DES Status Register. */
    RegValue = Power_Ip_pxMC_RGM->DES & MC_RGM_DES_RWBITS_MASK32;

    /* Store the contents of DES. */
    if ((uint32)0U != RegValue)
    {
        DesResetStatus = RegValue;
    }

    ActiveValue = DesResetStatus;
    /* If at least one bit is set in the RGM_DES register, then it means that some destructive reset event has been logged. */
    ResetReason = Power_Ip_MC_RGM_CheckResetReason(ActiveValue, 0U, &Position);

    /* Clear all the reset flags from MC_RGM_DES. */
    Power_Ip_MC_RGM_ClearDesResetFlags(RegValue);

    /* If the fields of Destructive Event Status Register (DES) are set then the status of FES register must be ignored */
    if (((uint32)0U == ActiveValue) || (MCU_POWER_ON_RESET == ResetReason))
    {
        /* Check "Functional Reset Reason" from FES Status Register. */
        RegValue = Power_Ip_pxMC_RGM->FES & MC_RGM_FES_RWBITS_MASK32;

        /* Store the contents of FES. */
        if ((uint32)0U != RegValue)
        {
            FesResetStatus = RegValue;
        }

        ActiveValue = FesResetStatus;
        if ((uint32)0U != ActiveValue)
        {
            /* DES[F_POR] is set and at least one bit is set in the RGM_FES register */
            if(MCU_POWER_ON_RESET == ResetReason)
            {
                ResetReason = MCU_MULTIPLE_RESET_REASON;
            }
            else
            {
                /* If at least one bit is set in the RGM_FES register, then it means that some functional reset event has been logged. */
                ResetReason = Power_Ip_MC_RGM_CheckResetReason(ActiveValue, 1U, &Position);
            }
        }

        /* Clear all the reset flags from MC_RGM_FES */
        Power_Ip_MC_RGM_ClearFesResetFlags(RegValue);
    }

    return ResetReason;
}

/**
* @brief            This function is a wrapper around Power_Ip_MC_RGM_GetResetReason.
* @details          This routine returns the Reset reason that is read from the hardware in uint32 format.
*                   Called by:
*                       - Mcu_Ipw_GetResetReason() from IPW when user mode is enabled.
*
* @return           Reason of the Reset event.
* @retval           uint32.
*/
uint32 Power_Ip_MC_RGM_GetResetReason_Uint(void)
{
    return (uint32)Power_Ip_MC_RGM_GetResetReason();
}

/**
* @brief            This function returns the Raw Reset value.
* @details          This routine returns the Raw Reset value that is read from the hardware.
*
* @return           Implementation-specific value with the Reset status.
* @retval           Power_Ip_RawResetType   Code of the Raw reset value.
*
* @note             The User should ensure that the reset reason is cleared once it has been read
*                   out to avoid multiple reset reasons.
*
*/
Power_Ip_RawResetType Power_Ip_MC_RGM_GetResetRawValue(void)
{
    /* Temporary variables for DES and FES registers value. */
    uint32 RawReset = 0U;
    uint32 RegValue;
    uint32 ActiveValue;
    uint32 Index;
    uint32 DynamicMask;
    uint32 Position;
    uint32 ResetMask;
#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
    Power_Ip_PowerModeType PreviousMode;
#endif

    /* Compact the 2x32 registers to 1x32 register. */
    /* Lower 16 bits will be FES, higher 16 bits will be DES. */
    RegValue = Power_Ip_pxMC_RGM->FES & MC_RGM_FES_RWBITS_MASK32;

    /* Store the contents of FES. */
    if ((uint32)0U != RegValue)
    {
        FesResetStatus = RegValue;
    }
#if ( (defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || \
     defined(POWER_IP_DERIVATIVE_004) || defined(POWER_IP_DERIVATIVE_005)) && defined(POWER_IP_RESET_REASON_FILTER))
    /* Combination with SWT1/SWT2/SWT3 bit mask on the derivatives doesn't have to skip MCU_SWT1_RST_RESET/MCU_SWT2_RST_RESET/MCU_SWT3_RST_RESET reason */
    /* The ResetMask variable isn't used to filter the value read from register */
    ResetMask = (MC_RGM_FES_RWBITS_MASK32 | MC_RGM_FES_SWT1_RST_MASK32 | MC_RGM_FES_SWT2_RST_MASK32 | MC_RGM_FES_SWT3_RST_MASK32);
#elif ( (defined(POWER_IP_DERIVATIVE_003) || defined(POWER_IP_DERIVATIVE_007)) && defined(POWER_IP_RESET_REASON_FILTER))
    ResetMask = MC_RGM_FES_RWBITS_MASK32 | MC_RGM_FES_SWT2_RST_MASK32 | MC_RGM_FES_SWT3_RST_MASK32;
#elif ( (defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_009)) && defined(POWER_IP_RESET_REASON_FILTER))
    ResetMask = MC_RGM_FES_RWBITS_MASK32 | MC_RGM_FES_SWT3_RST_MASK32;
#else
    ResetMask = MC_RGM_FES_RWBITS_MASK32;
#endif

#if (!(defined(POWER_IP_DERIVATIVE_008) || defined(POWER_IP_DERIVATIVE_009)))
#if (defined(MC_RGM_FES_PLL_AUX_MASK32))
    /* Combination with PLL_AUX bit mask on the derivatives doesn't have to skip MCU_PLL_AUX_RESET reason */
    /* The ResetMask variable isn't used to filter the value read from register */
    ResetMask |= MC_RGM_FES_PLL_AUX_MASK32;
#endif
#endif

    ActiveValue = FesResetStatus;
    if ((uint32)0U != ActiveValue)
    {
        Position = MC_RGM_RAWRESET_FES_BASE_SHIFT_U32;

        for (Index = 0U; Index < (uint32)32U; Index++)
        {
            DynamicMask = ((uint32)0x01U << Index);
            if ( (uint32)0U != (DynamicMask & ResetMask) )
            {
                if ( (uint32)0U != (DynamicMask & ActiveValue) )
                {
                    RawReset |= ((uint32)0x01U << Position);
                }

                Position++;
            }
        }

        /* Clear all the reset flags of MC_RGM_FES. */
        Power_Ip_MC_RGM_ClearFesResetFlags(RegValue);
    }

#if ( (defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || \
    defined(POWER_IP_DERIVATIVE_003) || defined(POWER_IP_DERIVATIVE_004) || \
    defined(POWER_IP_DERIVATIVE_005) || defined(POWER_IP_DERIVATIVE_007) || \
    defined(POWER_IP_DERIVATIVE_009)) && defined(POWER_IP_RESET_REASON_FILTER))
    ResetMask = MC_RGM_DES_RWBITS_MASK32 | MC_RGM_DES_CM7_CORE_CLK_FAIL_MASK32;
#else
    ResetMask = MC_RGM_DES_RWBITS_MASK32;
#endif
    RegValue = Power_Ip_pxMC_RGM->DES & MC_RGM_DES_RWBITS_MASK32;

    /* Store the contents of DES. */
    if ((uint32)0U != RegValue)
    {
        DesResetStatus = RegValue;
    }

    ActiveValue = DesResetStatus;
    if ((uint32)0U != ActiveValue)
    {
        Position = MC_RGM_RAWRESET_DES_BASE_SHIFT_U32;

        for (Index = 0x00U; Index < (uint32)32U; Index++)
        {
            DynamicMask = ((uint32)0x01U << Index);
            if ((uint32)0x00U != (DynamicMask & ResetMask))
            {
                if ((uint32)0x00U != (DynamicMask & ActiveValue))
                {
                    RawReset |= ((uint32)0x01U << Position);
                }

                Position++;
            }
        }

        /* Clear all the reset flags from MC_RGM_DES. */
        Power_Ip_MC_RGM_ClearDesResetFlags(RegValue);
    }
#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
    /* If there is no reset reason on the main platform */
    if ((uint32)0U == RawReset)
    {
        PreviousMode = Power_Ip_MC_ME_GetPreviousMode();
        if ( POWER_IP_SOC_STANDBY_MODE == PreviousMode )
        {
            RawReset |= MC_RGM_RAWRESET_WAKEUP_MASK32;
        }
    }
#endif /*(POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
    return (Power_Ip_RawResetType)RawReset;
}

#if (defined(POWER_IP_RESET_DURING_STANDBY_SUPPORTED) && (POWER_IP_RESET_DURING_STANDBY_SUPPORTED == STD_ON))
    #if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
/**
* @brief            This function returns whether a reset occurred during standby.
* @details          This function returns whether a reset occurred during standby.
*
* @return           uint8
* @retval           1U        Reset occurred during standby.
* @retval           0U       Reset did not occurred during standby.
*
*/
uint8 Power_Ip_MC_RGM_ResetDuringStandby(void)
{
    uint32 RegValue;
    uint8 ResetDuringStdby = 0U;

    RegValue = (uint32)(Power_Ip_pxMC_RGM->RDSS & MC_RGM_RDSS_RWBITS_MASK_U32);

    /* Store the contents of RDSS. */
    if ((uint32)0U != RegValue)
    {
        StandbyResetStatus = RegValue;

        /* Clear all the flags from MC_RGM_RDSS */
        Power_Ip_pxMC_RGM->RDSS = RegValue;
    }

#ifdef MC_RGM_FES_RES_OCCURED_DURING_STANDBY_U32
    if (
           (MC_RGM_FES_RES_OCCURED_DURING_STANDBY_U32 == (StandbyResetStatus & MC_RGM_RDSS_FES_RES_MASK_U32)) ||
           (MC_RGM_DES_RES_OCCURED_DURING_STANDBY_U32 == (StandbyResetStatus & MC_RGM_RDSS_DES_RES_MASK_U32))
       )
#else
    if (
           (MC_RGM_DES_RES_OCCURED_DURING_STANDBY_U32 == (StandbyResetStatus & MC_RGM_RDSS_DES_RES_MASK_U32))
       )
#endif
    {
        ResetDuringStdby = 1U;
    }

    return ResetDuringStdby;
}
    #endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
#endif /* (POWER_IP_RESET_DURING_STANDBY_SUPPORTED == STD_ON) */

#if (POWER_IP_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*                   This is a chip-wide virtual mode during which the application is not active.
*                   The system remains in this mode until all resources are available for the
*                   embedded software to take control of the device.
*
* @param[in]        ConfigPtr   Pointer to the MC_RGM configuration structure.
*
* @return           void
*
*/
void Power_Ip_MC_RGM_PerformReset(const Power_Ip_MC_RGM_ConfigType * ConfigPtr)
{
    switch (ConfigPtr->ResetType)
    {
        case (MCU_FUNC_RESET):
        {
            /* Initiate "Functional Reset" Mode. */
            Power_Ip_MC_ME_SocTriggerResetEvent(POWER_IP_FUNC_RESET_MODE);
            break;
        }
        case (MCU_DEST_RESET):
        {
            /* Initiate "Destructive Reset" Mode. */
            Power_Ip_MC_ME_SocTriggerResetEvent(POWER_IP_DEST_RESET_MODE);
            break;
        }
        default:
        {
            /* Default case - should never enter here. */
            break;
        }
    }
}
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */

#if (defined(POWER_IP_RESET_ALTERNATE_ISR_USED) && (POWER_IP_RESET_ALTERNATE_ISR_USED == STD_ON))
/**
* @brief            This function handles both the 'Functional' and 'Destructive' Reset
*                   Alternate Event Interrupts.
* @details          Only the following reset events support interrupt reaction:
*                       - DEBUG_FUNC (Functional Debug Reset)
*                       - EXR (External Reset)
*
* @return           void
*
*/

void Power_Ip_MC_RGM_ResetAltInt(void)
{
    /* Functional event IRQs */
    uint32 FesIntResetReason       = 0U;
    uint32 MaskedFesIntResetReason = 0U;

    if (POWER_MC_RGM_UNINIT != Power_Ip_eMcRgmStatus)
    {
        /* Get only the bits that can generate a functional reset IRQ. */
        FesIntResetReason = ((uint32)(Power_Ip_pxMC_RGM->FES & MC_RGM_FES_IRQ_BITS_MASK));
        /* Check for spurious interrupt. */
        MaskedFesIntResetReason = FesIntResetReason & ( (uint32)(Power_Ip_pxMC_RGM->FERD & MC_RGM_FERD_RWBITS_MASK) );

        /* Signal the functional alternate reset event (IRQ) to upper layers. */
        if ((uint32)0U != MaskedFesIntResetReason)
        {
            /* Clear active functional IRQs */
            Power_Ip_pxMC_RGM->FES = ((uint32)(FesIntResetReason & MC_RGM_FES_RWBITS_MASK32));
#ifdef POWER_IP_ERROR_ISR_NOTIFICATION
            POWER_IP_ERROR_ISR_NOTIFICATION(POWER_IP_E_ISR_FUNC_RESET_ALT_FAILURE);
#else
            Power_Ip_ReportPowerErrors(POWER_IP_ISR_ERROR, POWER_IP_E_ISR_FUNC_RESET_ALT_FAILURE);
#endif
        }
    }
    else
    {
        /* Clear active functional IRQs */
        Power_Ip_pxMC_RGM->FES = ((uint32)(FesIntResetReason & MC_RGM_FES_RWBITS_MASK32));
    }
}
#endif /* ( POWER_IP_RESET_ALTERNATE_ISR_USED == STD_ON ) */


#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

