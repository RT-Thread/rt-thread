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

#ifndef POWER_IP_MC_ME_TYPES_H
#define POWER_IP_MC_ME_TYPES_H

/**
*   @file       Power_Ip_MC_ME_Types.h
*   @version    5.0.0
*
*   @brief   POWER IP driver header file.
*   @details POWER IP driver header file.
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
#include "Power_Ip_Specific.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_MC_ME_TYPES_VENDOR_ID                       43
#define POWER_IP_MC_ME_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_MC_ME_TYPES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_MC_ME_TYPES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_MC_ME_TYPES_SW_MAJOR_VERSION                5
#define POWER_IP_MC_ME_TYPES_SW_MINOR_VERSION                0
#define POWER_IP_MC_ME_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if Power_Ip_MC_ME_Types.h file and Power_Ip_Specific.h file have same versions */
#if (POWER_IP_MC_ME_TYPES_VENDOR_ID  != POWER_IP_SPECIFIC_VENDOR_ID)
    #error "Power_Ip_MC_ME_Types.h and Power_Ip_Specific.h have different vendor IDs"
#endif

/* Check if Power_Ip_MC_ME_Types.h file and Power_Ip_Specific.h file are of the same Autosar version */
#if ((POWER_IP_MC_ME_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_ME_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_MC_ME_Types.h and Power_Ip_Specific.h are different"
#endif

/* Check if Power_Ip_MC_ME_Types.h file and Power_Ip_Specific.h file are of the same Software version */
#if ((POWER_IP_MC_ME_TYPES_SW_MAJOR_VERSION != POWER_IP_SPECIFIC_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_ME_TYPES_SW_MINOR_VERSION != POWER_IP_SPECIFIC_SW_MINOR_VERSION) || \
     (POWER_IP_MC_ME_TYPES_SW_PATCH_VERSION != POWER_IP_SPECIFIC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_MC_ME_Types.h and Power_Ip_Specific.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/***********************************************************/
/*                      MC_ME_CTL_KEY                      */
/***********************************************************/
#define MC_ME_CTL_KEY_DIRECT_KEY_U32                    ((uint32)0x00005AF0U)
#define MC_ME_CTL_KEY_INVERTED_KEY_U32                  ((uint32)0x0000A50FU)

/***********************************************************/
/*                     MC_ME_MODE_STAT                     */
/***********************************************************/
#define MC_ME_MODE_STAT_PREV_MODE_RESET_U32             ((uint32)0x00000000U)
#define MC_ME_MODE_STAT_PREV_MODE_STANDBY_U32           (MC_ME_MODE_STAT_PREV_MODE_MASK)

/***********************************************************/
/*                    MC_ME_PRTNx_PCONF                    */
/***********************************************************/
#define MC_ME_PRTNX_PCONF_PCE_EN_U32                    (MC_ME_PRTN0_PCONF_PCE_MASK)
#define MC_ME_PRTNX_PCONF_PCE_DIS_U32                   ((uint32)0x00000000U)

/***********************************************************/
/*                    MC_ME_PRTNx_PUPD                     */
/***********************************************************/
#define MC_ME_PRTNX_PUPD_PCUD_TRIG_U32                  (MC_ME_PRTNx_PUPD_PCUD_MASK)
#define MC_ME_PRTNX_PUPD_PCUD_NOT_TRIG_U32              ((uint32)0x00000000U)

/***********************************************************/
/*                    MC_ME_PRTNx_STAT                     */
/***********************************************************/
#define MC_ME_PRTNX_STAT_PCS_ACTIVE_U32                 (MC_ME_PRTN0_STAT_PCS_MASK)
#define MC_ME_PRTNX_STAT_PCS_INACTIVE_U32               ((uint32)0x00000000U)

/***********************************************************/
/*                 MC_ME_PRTNn_COREm_PCONF                 */
/***********************************************************/
#define MC_ME_PRTNX_COREX_PCONF_CCE_EN_U32              (MC_ME_PRTN0_CORE0_PCONF_CCE_MASK)
#define MC_ME_PRTNX_COREX_PCONF_CCE_DIS_U32             ((uint32)0x00000000U)

/***********************************************************/
/*                 MC_ME_PRTNn_COREm_PUPD                  */
/***********************************************************/
#define MC_ME_PRTNX_COREX_PUPD_CCUPD_TRIG_U32           (MC_ME_PRTN0_CORE0_PUPD_CCUPD_MASK)
#define MC_ME_PRTNX_COREX_PUPD_CCUPD_NOT_TRIG_U32       ((uint32)0x00000000U)

/***********************************************************/
/*                 MC_ME_PRTNn_COREm_STAT                  */
/***********************************************************/
#define MC_ME_PRTNX_COREX_STAT_WFI_EXECUTED_U32         (MC_ME_PRTN0_CORE0_STAT_WFI_MASK)
#define MC_ME_PRTNX_COREX_STAT_WFI_NOT_EXECUTED_U32     ((uint32)0x00000000U)

#define MC_ME_PRTNX_COREX_STAT_CCS_ACTIVE_U32           (MC_ME_PRTN0_CORE0_STAT_CCS_MASK)
#define MC_ME_PRTNX_COREX_STAT_CCS_INACTIVE_U32         ((uint32)0x00000000U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/**
* @brief   MC_ME Core Configuration.
* @details This structure contains information for configuring the cores.
*          The definitions for each Core setting within the structure Power_Ip_MC_ME_CoreConfigType shall contain:
*          - The index of the Core (within its partition).
*          - The boot address of the Core.
*          - Power management information (i.e. start or shutdown the Core).
*/
typedef struct
{
    /** @brief Specifies whether the given core is under MCU control. */
    boolean CoreUnderMcuControl;

    /** @brief The index of the core within the partition. */
    uint8 CoreIndex;

    /** @brief The boot address of the core. */
    uint32 * CoreBootAddress;

    /** @brief The process configuration register value of the core. */
    uint32 CorePconfRegValue;
    
} Power_Ip_MC_ME_CoreConfigType;

/**
* @brief   MC_ME COFB Configuration.
* @details This structure contains information for configuring the COFBs (Collection of Functional Blocks).
*          The definitions for each COFB setting within the structure Power_Ip_MC_ME_CofbConfigType shall contain:
*          - The index of the COFB (within its partition).
*          - The list of peripherals enable/disable (i.e. the value of the PRTNx_COFBx_CLKEN register).
*/
typedef struct
{
    /** @brief Specifies whether the given COFB set is under MCU control. */
    boolean CofbUnderMcuControl;

    /** @brief The index of the COFB set within the partition. */
    uint8 CofbIndex;

    /** @brief The clock enable register value of the COFB set. */
    uint32 CofbClkenRegValue;

    /** @brief Mask containing the COFB blocks to be updated. */
    uint32 CofbBlocksToUpdateMask;

} Power_Ip_MC_ME_CofbConfigType;

/**
* @brief   MC_ME Partition Configuration.
* @details This structure contains information for configuring the Partitions.
*          The definitions for each Partition setting within the structure Power_Ip_MC_ME_PartitionConfigType shall contain:
*          - The index of the Partition.
*          - The configuration settings for the COFBs contained within the Partition.
*          - The configuration settings for the Cores contained within the Partition.
*/
typedef struct
{
    /** @brief Specifies whether the given partition is under MCU control. */
    boolean PartitionUnderMcuControl;

    /** @brief Specifies whether the given partition's power management is under MCU control */
    boolean PartitionPowerUnderMcuControl;

#if (defined(POWER_IP_RTU_LOCKSTEP_SUPPORTED))
  #if (POWER_IP_RTU_LOCKSTEP_SUPPORTED == STD_ON)     
    /** @brief Specifies whether core operations(lockstep, split) is under MCU control */
    boolean CoreOperationUnderMcuControl;
  #endif
#endif

    /** @brief The index of the partition. */
    uint8 PartitionIndex;

#if (defined(POWER_IP_RTU_LOCKSTEP_SUPPORTED))
  #if (POWER_IP_RTU_LOCKSTEP_SUPPORTED == STD_ON)    
    /** @brief Configure cores in partition is lockstep or split operation. */
    boolean LockStepEn;
  #endif
#endif

    /** @brief The process configuration register value of the partition. */
    uint32 PartitionPconfRegValue;

    /** @brief Mask containing the Partition triggers (PCE/OSSE/etc) to be updated. */
    uint32 PartitionTriggerMask;

    /** @brief Number of COFBs within the partition. */
    uint8 NumberOfCofbs;
    /** @brief The configuration of the COFBs. */
    const Power_Ip_MC_ME_CofbConfigType (*ArrayPartitionCofbConfigPtr)[];

    /** @brief Number of cores within the partition. */
    uint8 NumberOfCores;
    /** @brief The configuration of the cores. */
    const Power_Ip_MC_ME_CoreConfigType (*ArrayPartitionCoreConfigPtr)[];

} Power_Ip_MC_ME_PartitionConfigType;

/**
* @brief   MC_ME IP Configuration.
* @details This structure contains information for configuring the entire MC_ME IP.
*/
typedef struct
{
#if (defined(POWER_IP_ENTER_LOW_POWER_MODE))
  #if (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON)
    /** @brief MC_ME Main Core ID register */
    uint32 MainCoreIdRegValue;
  #endif
#endif
#if (defined(POWER_IP_LOCKSTEP_CTRL_SUPPORT))
  #if (POWER_IP_LOCKSTEP_CTRL_SUPPORT == STD_ON)
    /** @brief The control for indicating a set of cores for lockstep execution. */
    boolean CoreLockStepCtrl;
  #endif
#endif
    /** @brief MC_ME Mode Partition Settings. */
    const Power_Ip_MC_ME_PartitionConfigType (*ArrayPartitionConfigPtr)[POWER_IP_MAX_NUMBER_OF_PARTITIONS];

} Power_Ip_MC_ME_ModeConfigType;


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* POWER_IP_MC_ME_TYPES_H */

