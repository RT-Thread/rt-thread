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

#ifndef POWER_IP_CFG_DEFINES_H
#define POWER_IP_CFG_DEFINES_H

/**
*   @file       Power_Ip_Cfg_Defines.h
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup POWER_DRIVER_CONFIGURATION Power Ip Driver
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
#include "Std_Types.h"
#include "S32K344_MC_ME.h"
#include "S32K344_MC_RGM.h"
#include "S32K344_PMC.h"
#include "S32K344_DCM_GPR.h"
#include "S32K344_FLASH.h"
#include "S32K344_SCB.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_CFG_DEFINES_VENDOR_ID                       43
#define POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_CFG_DEFINES_SW_MAJOR_VERSION                5
#define POWER_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define POWER_IP_CFG_DEFINES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_Cfg_Defines.h  and Std_Types.h are different"
#endif
#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/

/**
* @brief            Derivative used.
*/
#define POWER_IP_DERIVATIVE_005


#define PMC_CONFIG_RWBITS_MASK                      ( \
                                                    ((uint32)PMC_CONFIG_LMEN_MASK) |\
                                                    ((uint32)PMC_CONFIG_LMBCTLEN_MASK) |\
                                                    ((uint32)PMC_CONFIG_FASTREC_MASK) |\
                                                    ((uint32)PMC_CONFIG_LPM25EN_MASK) |\
                                                    ((uint32)PMC_CONFIG_LVRBLPEN_MASK) |\
                                                    ((uint32)PMC_CONFIG_HVDIE_MASK) |\
                                                    ((uint32)PMC_CONFIG_LVDIE_MASK) |\
                                                    ((uint32)PMC_CONFIG_LMAUTOEN_MASK) )


/**
* @brief            If this parameter is set to TRUE, the Reset Generation Module (RGM) initialization has to be disabled from the MCU driver.
*/

#define POWER_IP_DISABLE_RGM_INIT                   (STD_OFF)

/**
* @brief            If this parameter is set to TRUE, the Power Management Controller (PMC) initialization has to be disabled from the MCU driver.
*/
#define POWER_IP_DISABLE_PMC_INIT                   (STD_OFF)

/**
* @brief            If this parameter is set to TRUE, the Switched Mode Power Supply (SMPS) initialization has to be disabled from the MCU driver.
*/
#define POWER_IP_ENABLE_SMPS_INIT                   (STD_OFF)

/**
* @brief            Support for Low Power mode.
*/
#define POWER_IP_ENTER_LOW_POWER_MODE                    (STD_ON)

/**
* @brief
*/
#define POWER_IP_PERFORM_RESET_API                       (STD_OFF)

/**
* @brief            Configure PRTNm_COREn_ADDR registers
*/
#define POWER_IP_CONFIGURE_CADDRN                        (STD_OFF)

/**
* @brief            Support for Functional Reset Disable (FERD regiter present).
*/
#define POWER_IP_FUNCTIONAL_RESET_DISABLE_SUPPORT   (STD_ON)

/**
* @brief            Max number of MC_ME partitions.
*/
#define POWER_IP_MAX_NUMBER_OF_PARTITIONS           ((uint8)3U)


/**
* @brief            Support for lockstep configuration (PTRNx_CORE_LOCKSTEP) registers.
*/
#define POWER_IP_LOCKSTEP_CTRL_SUPPORT                  (STD_OFF)

/**
* @brief            ISR Mcu_ResetAlternate_ISR is/is not available (STD_ON/STD_OFF)
*/
#define POWER_IP_RESET_ALTERNATE_ISR_USED                (STD_OFF)

/**
* @brief
*/
#define POWER_IP_HAS_OUTPUT_SAFE_STATE         (STD_OFF)

/**
* @brief
*/
#define POWER_IP_RESET_DURING_STANDBY_SUPPORTED      (STD_ON)


#define POWER_IP_RESET_DOMAINS_SUPPORTED                 (STD_OFF)

/**
* @brief            PMC_AE Configuration Register (CONFIG) and PMC_AE Monitor Register (MONITOR).
*/
#define POWER_IP_PMC_AE_SUPPORT         (STD_OFF)

/**
* @brief            AEC Configuration Register (RSTGEN_CFG).
*/
#define POWER_IP_AEC_SUPPORT            (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API  Power_Ip_PmcAeConfig().
*/
#define POWER_IP_PMCAECONFIG_API     (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API  Power_Ip_AecResetConfig().
*/
#define POWER_IP_AECRESETCONFIG_API     (STD_OFF)

/**
* @brief            ISR Mcu_PMC_UnderOverVoltage_ISR is/is not available (STD_ON/STD_OFF)
*/
#define POWER_IP_VOLTAGE_ERROR_ISR_USED                  (STD_OFF)

/**
* @brief           This define controls the availability of function Power_Ip_DCM_GPR_PMICBypasses
*/
#define POWER_IP_PMIC_PGOOD_SUPPORT    (STD_OFF)

/**
* @brief            Support for Functional Reset Entry Timeout (FRENTC regiter present).
*/
#define POWER_IP_FUNCTIONAL_RESET_ENTRY_TIMEOUT_SUPPORT    (STD_OFF)

/**
* @brief           This define controls the availability of function Power_Ip_EnableLastMile/Power_Ip_DisableLastMile
*/
#define POWER_IP_LASTMILE_SUPPORT                   (STD_ON)

/**
* @brief            Create defines with the values assigned to Mcu Reset Reason configurations.
*                   These values can be  retrieved from Mcu_GetResetReason Api.
*/

#define McuConf_McuResetReasonConf_MCU_POWER_ON_RESET   ((uint8)0U)

#define McuConf_McuResetReasonConf_MCU_FCCU_FTR_RESET   ((uint8)1U)

#define McuConf_McuResetReasonConf_MCU_STCU_URF_RESET   ((uint8)2U)

#define McuConf_McuResetReasonConf_MCU_MC_RGM_FRE_RESET   ((uint8)3U)

#define McuConf_McuResetReasonConf_MCU_FXOSC_FAIL_RESET   ((uint8)4U)

#define McuConf_McuResetReasonConf_MCU_PLL_LOL_RESET   ((uint8)5U)

#define McuConf_McuResetReasonConf_MCU_CORE_CLK_FAIL_RESET   ((uint8)6U)

#define McuConf_McuResetReasonConf_MCU_AIPS_PLAT_CLK_FAIL_RESET   ((uint8)7U)

#define McuConf_McuResetReasonConf_MCU_HSE_CLK_FAIL_RESET   ((uint8)8U)

#define McuConf_McuResetReasonConf_MCU_SYS_DIV_FAIL_RESET   ((uint8)9U)

#define McuConf_McuResetReasonConf_MCU_CM7_CORE_CLK_FAIL_RESET   ((uint8)10U)

#define McuConf_McuResetReasonConf_MCU_HSE_TMPR_RST_RESET   ((uint8)11U)

#define McuConf_McuResetReasonConf_MCU_HSE_SNVS_RST_RESET   ((uint8)12U)

#define McuConf_McuResetReasonConf_MCU_SW_DEST_RESET   ((uint8)13U)

#define McuConf_McuResetReasonConf_MCU_DEBUG_DEST_RESET   ((uint8)14U)

#define McuConf_McuResetReasonConf_MCU_F_EXR_RESET   ((uint8)15U)

#define McuConf_McuResetReasonConf_MCU_FCCU_RST_RESET   ((uint8)16U)

#define McuConf_McuResetReasonConf_MCU_ST_DONE_RESET   ((uint8)17U)

#define McuConf_McuResetReasonConf_MCU_SWT0_RST_RESET   ((uint8)18U)

#define McuConf_McuResetReasonConf_MCU_SWT1_RST_RESET   ((uint8)19U)

#define McuConf_McuResetReasonConf_MCU_SWT2_RST_RESET   ((uint8)20U)

#define McuConf_McuResetReasonConf_MCU_JTAG_RST_RESET   ((uint8)21U)

#define McuConf_McuResetReasonConf_MCU_SWT3_RST_RESET   ((uint8)22U)

#define McuConf_McuResetReasonConf_MCU_PLL_AUX_RESET   ((uint8)23U)

#define McuConf_McuResetReasonConf_MCU_HSE_SWT_RST_RESET   ((uint8)24U)

#define McuConf_McuResetReasonConf_MCU_HSE_BOOT_RST_RESET   ((uint8)25U)

#define McuConf_McuResetReasonConf_MCU_SW_FUNC_RESET   ((uint8)26U)

#define McuConf_McuResetReasonConf_MCU_DEBUG_FUNC_RESET   ((uint8)27U)

#define McuConf_McuResetReasonConf_MCU_WAKEUP_REASON   ((uint8)28U)

#define McuConf_McuResetReasonConf_MCU_NO_RESET_REASON   ((uint8)29U)

#define McuConf_McuResetReasonConf_MCU_MULTIPLE_RESET_REASON   ((uint8)30U)

#define McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED   ((uint8)31U)
/**
* @brief           This define controls the availability of function Mcu_SleepOnExit
*/
#define POWER_IP_SLEEPONEXIT_SUPPORT         (STD_ON)
/**
* @brief            Support Mc_Me COFB (COFB regiter present).
*/
#define POWER_IP_MC_ME_COFB_SUPPORT                 (STD_ON)
/***********************************************************/
/*                 MC_ME_PRTN0_COFB1_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN0_COFB1_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ35_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ36_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK | \
                    MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK | \
                    0x00000000))
#define MC_ME_PRTN0_COFB1_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN0_COFB1_CLKEN_RWBITS_MASK))
/***********************************************************/
/*                 MC_ME_PRTN1_COFB0_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN1_COFB0_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ3_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ4_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ5_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ6_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ7_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ8_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ9_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ10_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ11_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ12_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ13_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ14_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ15_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ21_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ22_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ23_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ24_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ28_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ29_MASK | \
                    MC_ME_PRTN1_COFB0_CLKEN_REQ31_MASK | \
                    0x00000000))
#define MC_ME_PRTN1_COFB0_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN1_COFB0_CLKEN_RWBITS_MASK))
/***********************************************************/
/*                 MC_ME_PRTN1_COFB1_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN1_COFB1_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ32_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ33_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ34_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ42_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ45_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ47_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ49_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ51_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ53_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ56_MASK | \
                    MC_ME_PRTN1_COFB1_CLKEN_REQ63_MASK | \
                    0x00000000))
#define MC_ME_PRTN1_COFB1_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN1_COFB1_CLKEN_RWBITS_MASK))
/***********************************************************/
/*                 MC_ME_PRTN1_COFB2_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN1_COFB2_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ65_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ66_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ67_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ68_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ69_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ70_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ73_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ74_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ75_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ76_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ77_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ78_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ79_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ80_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ81_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ84_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ85_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ86_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ87_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ88_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ89_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ91_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ92_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ93_MASK | \
                    MC_ME_PRTN1_COFB2_CLKEN_REQ95_MASK | \
                    0x00000000))
#define MC_ME_PRTN1_COFB2_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN1_COFB2_CLKEN_RWBITS_MASK))
/***********************************************************/
/*                 MC_ME_PRTN1_COFB3_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN1_COFB3_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN1_COFB3_CLKEN_REQ96_MASK | \
                    MC_ME_PRTN1_COFB3_CLKEN_REQ104_MASK | \
                    0x00000000))
#define MC_ME_PRTN1_COFB3_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN1_COFB3_CLKEN_RWBITS_MASK))
/***********************************************************/
/*                 MC_ME_PRTN2_COFB0_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN2_COFB0_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ4_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ5_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ6_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ7_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ8_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ9_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ10_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ11_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ12_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ13_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ14_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ15_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ16_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ17_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ18_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ19_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ20_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ21_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ22_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ23_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ24_MASK | \
                    MC_ME_PRTN2_COFB0_CLKEN_REQ29_MASK | \
                    0x00000000))
#define MC_ME_PRTN2_COFB0_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN2_COFB0_CLKEN_RWBITS_MASK))
/***********************************************************/
/*                 MC_ME_PRTN2_COFB1_CLKEN                 */
/***********************************************************/
#define MC_ME_PRTN2_COFB1_CLKEN_RWBITS_MASK  ((uint32)( \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ32_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ35_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ36_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ37_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ38_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ39_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ40_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ41_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ42_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ47_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ48_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ51_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ55_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ58_MASK | \
                    MC_ME_PRTN2_COFB1_CLKEN_REQ62_MASK | \
                    0x00000000))
#define MC_ME_PRTN2_COFB1_CLKEN(value)       ((uint32)(((uint32)(value)) & MC_ME_PRTN2_COFB1_CLKEN_RWBITS_MASK))

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

/** @} */
#endif /* #ifndef POWER_IP_CFG_DEFINES_H */


