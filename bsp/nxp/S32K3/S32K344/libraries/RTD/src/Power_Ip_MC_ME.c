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
*   @file       Power_Ip_MC_ME.c
*   @version    5.0.0
*
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
#include "Power_Ip_MC_ME.h"
#include "Power_Ip_CortexM7.h"

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)
      #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
      #include "RegLockMacros.h"
    #endif /* (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_MC_ME_VENDOR_ID_C                      43
#define POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_MC_ME_SW_MAJOR_VERSION_C               5
#define POWER_IP_MC_ME_SW_MINOR_VERSION_C               0
#define POWER_IP_MC_ME_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_MC_ME.c file and Power_Ip_Private.h file are of the same vendor */
#if (POWER_IP_MC_ME_VENDOR_ID_C != POWER_IP_PRIVATE_VENDOR_ID)
    #error "Power_Ip_MC_ME.c and Power_Ip_Private.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_Private.h file are of the same Autosar version */
#if ((POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_ME.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_Private.h file are of the same Software version */
#if ((POWER_IP_MC_ME_SW_MAJOR_VERSION_C != POWER_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_SW_MINOR_VERSION_C != POWER_IP_PRIVATE_SW_MINOR_VERSION) || \
     (POWER_IP_MC_ME_SW_PATCH_VERSION_C != POWER_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_ME.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_CortexM7.h file are of the same vendor */
#if (POWER_IP_MC_ME_VENDOR_ID_C != POWER_IP_CORTEXM7_VENDOR_ID)
    #error "Power_Ip_MC_ME.c and Power_Ip_CortexM7.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_CortexM7.h file are of the same Autosar version */
#if ((POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_CORTEXM7_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION_C != POWER_IP_CORTEXM7_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION_C != POWER_IP_CORTEXM7_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_ME.c and Power_Ip_CortexM7.h are different"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_CortexM7.h file are of the same Software version */
#if ((POWER_IP_MC_ME_SW_MAJOR_VERSION_C != POWER_IP_CORTEXM7_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_SW_MINOR_VERSION_C != POWER_IP_CORTEXM7_SW_MINOR_VERSION) || \
     (POWER_IP_MC_ME_SW_PATCH_VERSION_C != POWER_IP_CORTEXM7_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_ME.c and Power_Ip_CortexM7.h are different"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_MC_ME.h file are of the same vendor */
#if (POWER_IP_MC_ME_VENDOR_ID_C != POWER_IP_MC_ME_VENDOR_ID)
    #error "Power_Ip_MC_ME.c and Power_Ip_MC_ME.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_MC_ME.h file are of the same Autosar version */
#if ((POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION_C != POWER_IP_MC_ME_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_ME.c and Power_Ip_MC_ME.h are different"
#endif

/* Check if Power_Ip_MC_ME.c file and Power_Ip_MC_ME.h file are of the same Software version */
#if ((POWER_IP_MC_ME_SW_MAJOR_VERSION_C != POWER_IP_MC_ME_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_SW_MINOR_VERSION_C != POWER_IP_MC_ME_SW_MINOR_VERSION) || \
     (POWER_IP_MC_ME_SW_PATCH_VERSION_C != POWER_IP_MC_ME_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_ME.c and Power_Ip_MC_ME.h are different"
#endif

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)
        #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
            /* Check if Power_Ip_MC_ME.c file and RegLockMacros.h file are of the same Autosar version */
            #if ((POWER_IP_MC_ME_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
                (POWER_IP_MC_ME_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
                #error "AutoSar Version Numbers of Power_Ip_MC_ME.c and RegLockMacros.h are different"
            #endif
        #endif
    #endif /* (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE) */
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
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED

#include "Mcu_MemMap.h"

static Power_Ip_MC_ME_Type * Power_Ip_pxMC_ME = (Power_Ip_MC_ME_Type *)IP_MC_ME_BASE;

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


static inline void Power_Ip_MC_ME_WriteControlKeys(void);
static inline void Power_Ip_MC_ME_TriggerModeUpdate(void);

static inline void Power_Ip_MC_ME_TriggerPartitionUpdate(uint32 TriggerMask, uint8 PartitionIndex);
#ifdef POWER_IP_MC_ME_COFB_SUPPORT
#if (POWER_IP_MC_ME_COFB_SUPPORT == STD_ON)
static inline void Power_Ip_MC_ME_TriggerCofbUpdate(uint8 PartitionIndex);
#endif
#endif
static inline void Power_Ip_MC_ME_TriggerCoreUpdate(uint8 PartitionIndex, uint8 CoreIndex);

static void Power_Ip_MC_ME_ConfigurePartitionClock(const Power_Ip_MC_ME_PartitionConfigType * PartitionConfigPtr);
#ifdef POWER_IP_MC_ME_COFB_SUPPORT
#if (POWER_IP_MC_ME_COFB_SUPPORT == STD_ON)
static void Power_Ip_MC_ME_ConfigureCOFB   ( const Power_Ip_MC_ME_CofbConfigType * CofbConfigPtr,
                                             uint8 PartitionIndex
                                            );
#endif
#endif
static void Power_Ip_MC_ME_ConfigureCore(const Power_Ip_MC_ME_CoreConfigType * CoreConfigPtr,
                                         uint8 PartitionIndex
                                         );

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief            This function triggers the hardware processes of MC_ME.
* @details          This function writes the key 0x5AF0 and the inverted key
*                   0xA50F to the Control Key Register (MC_ME_CTL_KEY).
*
* @param[in]        void
*
* @return           void
*
*/
static inline void Power_Ip_MC_ME_WriteControlKeys(void)
{
    /* Starting the hardware processes */

    /* Write key to MC_ME_CTL_KEY */
    Power_Ip_pxMC_ME->CTL_KEY = MC_ME_CTL_KEY_KEY(MC_ME_CTL_KEY_DIRECT_KEY_U32);

    /* Write inverted key to MC_ME_CTL_KEY */
    Power_Ip_pxMC_ME->CTL_KEY = MC_ME_CTL_KEY_KEY(MC_ME_CTL_KEY_INVERTED_KEY_U32);
}

/**
* @brief            This function triggers a mode update.
* @details          This function triggers a mode update by writing to the
*                   corresponding MC_ME_MODE_UPD register.
*
* @param[in]        void
*
* @return           void
*
*/
static inline void Power_Ip_MC_ME_TriggerModeUpdate(void)
{
    Power_Ip_pxMC_ME->MODE_UPD = MC_ME_MODE_UPD_MODE_UPD(MC_ME_MODE_UPD_MODE_UPD_MASK);

    Power_Ip_MC_ME_WriteControlKeys();
}

/**
* @brief            This function triggers a partition update.
* @details          This function triggers a partition update based on the value of TriggerMask
*                   by writing to the corresponding MC_ME_PRTNx_PUPD register.
*
* @param[in]        TriggerMask      Mask containing the process updates to be triggered.
* @param[in]        PartitionIndex    Index of the partition to be updated.
*
* @return           void
*
*/
static inline void Power_Ip_MC_ME_TriggerPartitionUpdate(   uint32 TriggerMask,
                                                            uint8 PartitionIndex
                                                        )
{
    uint32 TempValue = 0U;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 HwprocessesStatus;
    
    TempValue = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PUPD;
    TempValue &= ~TriggerMask;
    TempValue |= TriggerMask;
    Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PUPD = TempValue;

    Power_Ip_MC_ME_WriteControlKeys();

    /* Wait until the update has finished. */
    Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
    do
    {
        TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

        HwprocessesStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PUPD;
    } while ((0U != (HwprocessesStatus & MC_ME_PRTNx_PUPD_PCUD_MASK)) && (!TimeoutOccurred));
    /* timeout notification */
    if(TimeoutOccurred)
    {
        Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
    }
}

#ifdef POWER_IP_MC_ME_COFB_SUPPORT
#if (POWER_IP_MC_ME_COFB_SUPPORT == STD_ON)
/**
* @brief            This function triggers a COFB update.
* @details          This function triggers a COFB update by writing to
*                   the corresponding MC_ME_PRTNx_PUPD register.
*
* @param[in]        PartitionIndex    Index of the partition (in which the COFB set resides) to be updated.
*
* @return           void
*
*/
static inline void Power_Ip_MC_ME_TriggerCofbUpdate(uint8 PartitionIndex)
{
    uint32 TempValue = 0U;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 HwprocessesStatus;
    
    TempValue = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PUPD;
    TempValue &= (~MC_ME_PRTNx_PUPD_PCUD_MASK);
    TempValue |= (MC_ME_PRTNX_PUPD_PCUD_TRIG_U32 & MC_ME_PRTNx_PUPD_PCUD_MASK);
    Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PUPD = TempValue;

    Power_Ip_MC_ME_WriteControlKeys();
    
    /* Wait until the update has finished. */
    Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
    do
    {
        TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

        HwprocessesStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PUPD;
    } while ((0U != (HwprocessesStatus & MC_ME_PRTNx_PUPD_PCUD_MASK)) && (!TimeoutOccurred));
    /* timeout notification */
    if(TimeoutOccurred)
    {
        Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
    }
}
#endif
#endif

/**
* @brief            This function triggers a core update.
* @details          This function triggers a core update by writing to the corresponding MC_ME_PRTNx_COREx_PUPD register.
*
* @param[in]        PartitionIndex    Index of the partition to be updated.
* @param[in]        CoreIndex         Index of the core (within the partition) to be updated.
*
* @return           void
*
*/
static inline void Power_Ip_MC_ME_TriggerCoreUpdate(uint8 PartitionIndex, uint8 CoreIndex)
{
    uint32 TempValue = 0U;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 HwprocessesStatus;
    
    TempValue = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_PUPD;
    TempValue &= ~MC_ME_PRTN0_CORE0_PUPD_CCUPD_MASK;
    TempValue |= (MC_ME_PRTNX_COREX_PUPD_CCUPD_TRIG_U32 & MC_ME_PRTN0_CORE0_PUPD_CCUPD_MASK);
    Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_PUPD = TempValue;

    Power_Ip_MC_ME_WriteControlKeys();
    
    /* Wait until the update has finished. */
    Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
    do
    {
        TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

        HwprocessesStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_PUPD;
    } while ((0U != (HwprocessesStatus & MC_ME_PRTN0_CORE0_PUPD_CCUPD_MASK)) && (!TimeoutOccurred));
    /* timeout notification */
    if(TimeoutOccurred)
    {
        Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
    }
}

/**
* @brief            This function configures Partition clock enable.
* @details          Configures the processes and waits until the updates have finished.
*
* @param[in]        PartitionConfigPtr   Pointer to a Partition configuration structure
*                   (member of 'Power_Ip_MC_ME_ModeConfigType' struct).
*
* @return           void
*
*/
static void Power_Ip_MC_ME_ConfigurePartitionClock(const Power_Ip_MC_ME_PartitionConfigType * PartitionConfigPtr)
{
    uint32 TempValue = 0U;
    uint32 PartitionConfig      = PartitionConfigPtr->PartitionPconfRegValue;
    uint32 PartitionTriggerMask = PartitionConfigPtr->PartitionTriggerMask;
    uint32 PartitionStatus;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint8 PartitionIndex = PartitionConfigPtr->PartitionIndex;

    if (MC_ME_PRTNX_PUPD_PCUD_TRIG_U32 == (PartitionTriggerMask & MC_ME_PRTNx_PUPD_PCUD_MASK))
    {
        /* Write the new configuration for PRTNx_PCONF[PCE]. */
        TempValue = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PCONF;
        TempValue &= ~MC_ME_PRTN0_PCONF_PCE_MASK;
        TempValue |= (PartitionConfig & MC_ME_PRTN0_PCONF_PCE_MASK);
        Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_PCONF = TempValue;

        /* Trigger the update in hardware. */
        Power_Ip_MC_ME_TriggerPartitionUpdate(MC_ME_PRTNx_PUPD_PCUD_MASK, PartitionIndex);

        /* Wait until the update has finished. */
        Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

            PartitionStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_STAT;
        } while ( ((PartitionStatus & MC_ME_PRTN0_STAT_PCS_MASK) != (PartitionConfig & MC_ME_PRTN0_PCONF_PCE_MASK)) && (!TimeoutOccurred) );
        /* timeout notification */
        if (TimeoutOccurred)
        {
            Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
        }
    }
}


#ifdef POWER_IP_MC_ME_COFB_SUPPORT
#if (POWER_IP_MC_ME_COFB_SUPPORT == STD_ON)
/**
* @brief            This function configures a given COFB set.
* @details          Configures the blocks within the given COFB set and wait until the updates have finished.
*
* @param[in]        CofbConfigPtr    Pointer to a COFB set configuration structure
*                   (member of 'Power_Ip_MC_ME_PartitionConfigType' struct).
* @param[in]        PartitionIndex        Index of the partition in which the COFB set resides.
*
* @return           void
*
*/
static void Power_Ip_MC_ME_ConfigureCOFB(const Power_Ip_MC_ME_CofbConfigType * CofbConfigPtr, uint8 PartitionIndex)
{
    uint32 PeripheralsConfig   = CofbConfigPtr->CofbClkenRegValue;
    uint32 PeripheralsToUpdate = CofbConfigPtr->CofbBlocksToUpdateMask;
    uint32 PeripheralsStatus;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint8 CofbIndex = CofbConfigPtr->CofbIndex;
    uint32 Regvalue;

    Regvalue = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_COFB_CLKEN[CofbIndex];
    Regvalue = (Regvalue & (~ PeripheralsToUpdate)) | PeripheralsConfig;
    /* Write the new configuration for the COFB set. */
    Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_COFB_CLKEN[CofbIndex] = Regvalue;

    /* Trigger the update in hardware. */
    Power_Ip_MC_ME_TriggerCofbUpdate(PartitionIndex);

#ifdef POWER_IP_MC_ME_PRTN2_COFB0_STAT_RESERVED
#if (POWER_IP_MC_ME_PRTN2_COFB0_STAT_RESERVED == STD_ON)
    if ((uint8)2U != PartitionIndex)
    {
#endif
#endif
        /* Wait until the update has finished. */
        Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

            PeripheralsStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].PRTN_COFB_STAT[CofbIndex];
        } while ( (PeripheralsConfig != (PeripheralsStatus & PeripheralsToUpdate)) && (!TimeoutOccurred) );
        /* timeout notification */
        if (TimeoutOccurred)
        {
            Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
        }
#ifdef POWER_IP_MC_ME_PRTN2_COFB0_STAT_RESERVED
#if (POWER_IP_MC_ME_PRTN2_COFB0_STAT_RESERVED == STD_ON)
    }
#endif
#endif
}
#endif
#endif

/**
* @brief            This function configures a given core.
* @details          Configures the core within the given partition and waits until the updates have finished.
*
* @param[in]        CoreConfigPtr    Pointer to a core configuration structure
*                   (member of 'Power_Ip_MC_ME_PartitionConfigType' struct).
* @param[in]        PartitionIndex        Index of the partition in which the core resides.
*
* @return           void
*
*/
static void Power_Ip_MC_ME_ConfigureCore(const Power_Ip_MC_ME_CoreConfigType * CoreConfigPtr,
                                         uint8 PartitionIndex
                                         )
{
    uint32 CoreConfig = CoreConfigPtr->CorePconfRegValue;
    uint32 CoreStatus;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint8 CoreIndex = CoreConfigPtr->CoreIndex;

    if (MC_ME_PRTNX_COREX_PCONF_CCE_DIS_U32 == (CoreConfigPtr->CorePconfRegValue & MC_ME_PRTN0_CORE0_PCONF_CCE_MASK))
    {
        /* Wait until WFI is set */
        Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

            CoreStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_STAT;
        } while ( (MC_ME_PRTNX_COREX_STAT_WFI_EXECUTED_U32 != (CoreStatus & MC_ME_PRTN0_CORE0_STAT_WFI_MASK)) && (!TimeoutOccurred) );
        /* timeout notification */
        if (TimeoutOccurred)
        {
            Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
        }
    }
#if (defined(POWER_IP_CONFIGURE_CADDRN))
  #if (POWER_IP_CONFIGURE_CADDRN == STD_ON)
    else
    {
        /* Set the boot address for the core */
        Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_ADDR = (uint32) CoreConfigPtr->CoreBootAddress;
    }
  #endif
#endif

    if (!TimeoutOccurred)
    {
        /* Write the new configuration for the core. */
        Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_PCONF = CoreConfig;

        /* Trigger the update in hardware */
        Power_Ip_MC_ME_TriggerCoreUpdate(PartitionIndex, CoreIndex);

        /* Wait until the update has finished. */
        Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

            CoreStatus = Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].McMePrtnCoreArray[CoreIndex].PRTN_CORE_STAT;
        } while ( ((CoreStatus & MC_ME_PRTN0_CORE0_STAT_CCS_MASK) != (CoreConfig & MC_ME_PRTN0_CORE0_PCONF_CCE_MASK)) && (!TimeoutOccurred) );
        /* timeout notification */
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
  #if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)
/**
* @brief            This function will enable writing in User mode by configuring REG_PROT
*/
void Power_Ip_MC_ME_SetUserAccessAllowed(void)
{
#if (defined(IP_MC_ME_BASE))
    SET_USER_ACCESS_ALLOWED(IP_MC_ME_BASE, MC_ME_PROT_MEM_U32);
#endif
}
    #endif /* (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */

/**
* @brief            This function initializes the mode structure.
* @details          This function initializes the mode structure by configuring the MC_ME module.
*                   The target mode is requested by accessing the ME_MCTL register with the required
*                   keys. This mode transition request by software must be a valid request
*                   satisfying a set of pre-defined rules to initiate the process. In the case of
*                   mode transitions occurring because of hardware events such as a reset, a SAFE
*                   mode request, or interrupt requests and wakeup events to exit from low-power
*                   modes, the TARGET_MODE bit field of the ME_MCTL register is automatically
*                   updated with the appropriate target mode.
*
* @param[in]        ModeConfigPtr   Pointer to MC_ME configuration structure
*                   (member of 'ModeConfigType' struct).
*
* @return           void
*
*/
void Power_Ip_MC_ME_ConfigCoreCOFBClock(const Power_Ip_MC_ME_ModeConfigType * ModeConfigPtr)
{
    const Power_Ip_MC_ME_PartitionConfigType *TempPartitionConfig = NULL_PTR;
    uint8 PartitionIndex;
#ifdef POWER_IP_MC_ME_COFB_SUPPORT
#if (POWER_IP_MC_ME_COFB_SUPPORT == STD_ON)
    uint8 CofbIndex;
#endif
#endif
    uint8 CoreIndex;

    for (PartitionIndex = 0U; PartitionIndex < POWER_IP_MAX_NUMBER_OF_PARTITIONS; ++PartitionIndex)
    {
        TempPartitionConfig = &(*ModeConfigPtr->ArrayPartitionConfigPtr)[PartitionIndex];

        if ( TRUE == TempPartitionConfig->PartitionUnderMcuControl )
        {
#ifdef POWER_IP_MC_ME_COFB_SUPPORT
#if (POWER_IP_MC_ME_COFB_SUPPORT == STD_ON)
            for (CofbIndex = 0U; CofbIndex < TempPartitionConfig->NumberOfCofbs; ++CofbIndex)
            {
                if ( TRUE == (*TempPartitionConfig->ArrayPartitionCofbConfigPtr)[CofbIndex].CofbUnderMcuControl )
                {
                    Power_Ip_MC_ME_ConfigureCOFB(&(*TempPartitionConfig->ArrayPartitionCofbConfigPtr)[CofbIndex], TempPartitionConfig->PartitionIndex);
                }
            }
#endif
#endif
            for (CoreIndex = 0U; CoreIndex < TempPartitionConfig->NumberOfCores; ++CoreIndex)
            {
                if ( TRUE == (*TempPartitionConfig->ArrayPartitionCoreConfigPtr)[CoreIndex].CoreUnderMcuControl )
                {
                    Power_Ip_MC_ME_ConfigureCore(&(*TempPartitionConfig->ArrayPartitionCoreConfigPtr)[CoreIndex], TempPartitionConfig->PartitionIndex);
                }
            }
        }
    }
}

/**
* @brief            This function Enable Partition Clock.
* @details          This function enable partition clock by configuring the MC_ME_PRTNx_PCONF[PCE] module.
*
* @param[in]        ModeConfigPtr   Pointer to MC_ME configuration structure
*                   (member of 'ModeConfigType' struct).
*
* @return           void
*
*/
void Power_Ip_MC_ME_EnablePartitionClock(const Power_Ip_MC_ME_ModeConfigType * ModeConfigPtr)
{
    const Power_Ip_MC_ME_PartitionConfigType *TempPartitionConfig = NULL_PTR;
    uint8 PartitionIndex;

    for (PartitionIndex = 0U; PartitionIndex < POWER_IP_MAX_NUMBER_OF_PARTITIONS; ++PartitionIndex)
    {
        TempPartitionConfig = &(*ModeConfigPtr->ArrayPartitionConfigPtr)[PartitionIndex];

        if ( TRUE == TempPartitionConfig->PartitionUnderMcuControl )
        {
            if ( TRUE == TempPartitionConfig->PartitionPowerUnderMcuControl )
            {
                /* The partition must be enabled before configuring its COFBs and Cores */
                if (MC_ME_PRTNX_PCONF_PCE_EN_U32 == (TempPartitionConfig->PartitionPconfRegValue & MC_ME_PRTN0_PCONF_PCE_MASK))
                {
                    Power_Ip_MC_ME_ConfigurePartitionClock(TempPartitionConfig);
#ifdef POWER_IP_LOCKSTEP_CTRL_SUPPORT
  #if (POWER_IP_LOCKSTEP_CTRL_SUPPORT == STD_ON)
                    if (0U == PartitionIndex)
                    {
                        Power_Ip_pxMC_ME->McMePrtnArray[PartitionIndex].CORE_LOCKSTEP = MC_ME_PRTN0_CORE_LOCKSTEP_LS2(ModeConfigPtr->CoreLockStepCtrl);
                    }
  #endif
#endif  
                }
            }
        }
    }
}

/**
* @brief            This function Disable Partition Clock.
* @details          This function disable partition clock by configuring the MC_ME_PRTNx_PCONF[PCE] module.
*
* @param[in]        ModeConfigPtr   Pointer to MC_ME configuration structure
*                   (member of 'ModeConfigType' struct).
*
* @return           void
*
*/
void Power_Ip_MC_ME_DisablePartitionClock(const Power_Ip_MC_ME_ModeConfigType * ModeConfigPtr)
{
    const Power_Ip_MC_ME_PartitionConfigType *TempPartitionConfig = NULL_PTR;
    uint8 PartitionIndex;

    for (PartitionIndex = 0U; PartitionIndex < POWER_IP_MAX_NUMBER_OF_PARTITIONS; ++PartitionIndex)
    {
        TempPartitionConfig = &(*ModeConfigPtr->ArrayPartitionConfigPtr)[PartitionIndex];

        if ( TRUE == TempPartitionConfig->PartitionUnderMcuControl )
        {
            if ( TRUE == TempPartitionConfig->PartitionPowerUnderMcuControl )
            {
                /* The partition must be disabled after configuring its COFBs and Cores */
                if (MC_ME_PRTNX_PCONF_PCE_DIS_U32 == (TempPartitionConfig->PartitionPconfRegValue & MC_ME_PRTN0_PCONF_PCE_MASK))
                {
                    Power_Ip_MC_ME_ConfigurePartitionClock(TempPartitionConfig);
                }
            }
        }
    }
}


/**
* @brief            This function triggers a reset event (destructive or functional) for the SoC.
* @details          This function triggers a reset event (destructive or functional) for the SoC.
*
* @return           Status of the previous mode.
*
*/
void Power_Ip_MC_ME_SocTriggerResetEvent(Power_Ip_PowerModeType PowerMode)
{
     /* Software must not enable mode entry if the value of multiple fields is 1 in the MODE_CONF register. */
    if (MC_ME_MODE_CONF_MASK != Power_Ip_pxMC_ME->MODE_CONF)
    {
        if (POWER_IP_DEST_RESET_MODE == PowerMode)
        {
            /* Makes a request to trigger a Destructive Reset Event */
            Power_Ip_pxMC_ME->MODE_CONF=MC_ME_MODE_CONF(MC_ME_MODE_CONF_DEST_RST_MASK);
        }
        else if (POWER_IP_FUNC_RESET_MODE == PowerMode)
        {
            /* Makes a request to trigger a Functional Reset Event */
            Power_Ip_pxMC_ME->MODE_CONF=MC_ME_MODE_CONF(MC_ME_MODE_CONF_FUNC_RST_MASK);
        }
        else
        {
            /* Should never happen. Throw an error. */
        }
        /* Trigger the update in hardware */
        Power_Ip_MC_ME_TriggerModeUpdate();
    }
}

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE))
  #if (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)
/**
* @brief            This function will transition a core to Standby mode.
* @details          This function will transition a core to Standby mode.
*
* @param[in]        ModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
*/
void Power_Ip_MC_ME_CoreStandbyEntry(const Power_Ip_ModeConfigType * ModeConfigPtr)
{
#ifdef MCAL_PLATFORM_ARM
    /* Finish/Retire outstanding instructions */
    MCAL_DATA_SYNC_BARRIER();
#endif

#ifdef POWER_IP_SLEEPONEXIT_SUPPORT
#if (POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON)
    if (FALSE != ModeConfigPtr->SleepOnExit)
    {
        /* Enable Sleep On Exit */
        Call_Power_Ip_CM7_EnableSleepOnExit();
    }
#endif
#endif
    /* Execute WFI */
    EXECUTE_WAIT();

#ifdef MCAL_PLATFORM_ARM
    /* Finish/Retire outstanding instructions */
    MCAL_DATA_SYNC_BARRIER();
#endif

}
  #endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
#endif

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE))
  #if (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)
/**
* @brief            This function will transition the SoC to Standby mode.
* @details          This function will transition the SoC to Standby mode.
*
* @param[in]        ModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
*/
void Power_Ip_MC_ME_SocStandbyEntry(const Power_Ip_ModeConfigType * ModeConfigPtr)
{
    /* Program MC_ME for valid main core id */
    Power_Ip_pxMC_ME->MAIN_COREID = ModeConfigPtr->McMeModeConfigPtr->MainCoreIdRegValue;

#ifdef MCAL_PLATFORM_ARM
    /* Finish/Retire outstanding instructions */
    MCAL_DATA_SYNC_BARRIER();
#endif

    /* Makes a request to go to Standby mode */
    Power_Ip_pxMC_ME->MODE_CONF = MC_ME_MODE_CONF(MC_ME_MODE_CONF_STANDBY_MASK);

    /* Trigger the update in hardware */
    Power_Ip_MC_ME_TriggerModeUpdate();

#ifdef MCAL_PLATFORM_ARM
    /* Finish/Retire outstanding instructions */
    MCAL_DATA_SYNC_BARRIER();
#endif

#ifdef POWER_IP_SLEEPONEXIT_SUPPORT
#if (POWER_IP_SLEEPONEXIT_SUPPORT == STD_ON)
    if (FALSE != ModeConfigPtr->SleepOnExit)
    {
        /* Enable Sleep On Exit */
        Call_Power_Ip_CM7_EnableSleepOnExit();
    }
#endif
#endif
    /* Execute WFI */
    EXECUTE_WAIT();

}
  #endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
#endif

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE))
  #if (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)
/**
* @brief            This function returns the previous mode.
* @details          This function returns the previous mode.
*
* @return           Status of the previous mode.
*
*/
Power_Ip_PowerModeType Power_Ip_MC_ME_GetPreviousMode(void)
{
    Power_Ip_PowerModeType PrevMode;

    if (MC_ME_MODE_STAT_PREV_MODE_STANDBY_U32 == (Power_Ip_pxMC_ME->MODE_STAT & MC_ME_MODE_STAT_PREV_MODE_MASK))
    {
        PrevMode = POWER_IP_SOC_STANDBY_MODE;
    }
    else
    {
        PrevMode = POWER_IP_RESET_MODE;
    }

    return PrevMode;
}
  #endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

