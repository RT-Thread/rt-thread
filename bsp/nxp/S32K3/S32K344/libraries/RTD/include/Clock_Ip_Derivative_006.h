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

#ifndef CLOCK_IP_DERIVATIVE_006_H
#define CLOCK_IP_DERIVATIVE_006_H

/**
*   @file       Clock_Ip_Derivative_006.h
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
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

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_DERIVATIVE_006_VENDOR_ID                       43
#define CLOCK_IP_DERIVATIVE_006_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_DERIVATIVE_006_AR_RELEASE_MINOR_VERSION        7
#define CLOCK_IP_DERIVATIVE_006_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_DERIVATIVE_006_SW_MAJOR_VERSION                5
#define CLOCK_IP_DERIVATIVE_006_SW_MINOR_VERSION                0
#define CLOCK_IP_DERIVATIVE_006_SW_PATCH_VERSION                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/


#define CLOCK_IP_DIVIDER_CALLBACKS_COUNT                                               5U
#define CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE                                       1U
#define CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WAIT_FOR_HSE_CORE                     2U
#define CLOCK_IP_PLL_PLL0DIV_DE_DIV_OUTPUT                                             3U
#define CLOCK_IP_PLL_PLLDV_ODIV2_OUTPUT                                                4U

#define CLOCK_IP_DIVIDERTRIGGER_CALLBACKS_COUNT                                        2U
#define CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT                                1U

#define CLOCK_IP_XOSC_CALLBACKS_COUNT                                                  2U
#define CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL                                           1U

#define CLOCK_IP_IRCOSC_CALLBACKS_COUNT                                                4U
#define CLOCK_IP_FIRC_STDBY_ENABLE                                                     1U
#define CLOCK_IP_SIRC_STDBY_ENABLE                                                     2U
#define CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR                                      3U

#define CLOCK_IP_GATE_CALLBACKS_COUNT                                                  2U
#define CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST                                   1U

#define CLOCK_IP_FRACTIONAL_DIVIDER_CALLBACKS_COUNT                                    1U

#define CLOCK_IP_PLL_CALLBACKS_COUNT                                                   2U
#define CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE        1U

#define CLOCK_IP_SELECTOR_CALLBACKS_COUNT                                              5U
#define CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP                                             1U
#define CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP                             2U
#define CLOCK_IP_CGM_X_CSC_CSS_CS_GRIP                                                 3U
#define CLOCK_IP_RTC_RTCC_CLKSELECT                                                    4U

#define CLOCK_IP_PCFS_CALLBACKS_COUNT                                                  2U
#define CLOCK_IP_CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS                                        1U

#define CLOCK_IP_CMU_CALLBACKS_COUNT                                                   2U
#define CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF                                        1U

#define CLOCK_IP_CMU_INSTANCES_NO                                                      5U

#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD1 60000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD2 90000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD3 120000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD4 150000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD5 180000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD6 210000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD7 240000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD8 250000000U

/*! @name PRTN0_COFB0_CLKEN - Partition 0 COFB Set 0 Clock Enable Register */
/*! @{ */

#define MC_ME_PRTN0_COFB0_CLKEN_REQ3_MASK        (0x8U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ3_SHIFT       (3U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ3_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ3(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ3_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ3_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ4_MASK        (0x10U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ4_SHIFT       (4U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ4_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ4(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ4_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ4_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ5_MASK        (0x20U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ5_SHIFT       (5U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ5_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ5(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ5_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ5_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ6_MASK        (0x40U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ6_SHIFT       (6U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ6_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ6(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ6_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ6_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ7_MASK        (0x80U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ7_SHIFT       (7U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ7_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ7(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ7_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ7_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ8_MASK        (0x100U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ8_SHIFT       (8U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ8_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ8(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ8_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ8_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ9_MASK        (0x200U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ9_SHIFT       (9U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ9_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ9(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ9_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ9_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ10_MASK       (0x400U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ10_SHIFT      (10U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ10_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ10(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ10_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ10_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ11_MASK       (0x800U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ11_SHIFT      (11U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ11_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ11(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ11_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ11_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ12_MASK       (0x1000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ12_SHIFT      (12U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ12_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ12(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ12_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ12_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ13_MASK       (0x2000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ13_SHIFT      (13U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ13_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ13(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ13_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ13_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ14_MASK       (0x4000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ14_SHIFT      (14U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ14_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ14(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ14_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ14_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ15_MASK       (0x8000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ15_SHIFT      (15U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ15_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ15(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ15_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ15_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ16_MASK       (0x10000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ16_SHIFT      (16U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ16_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ16(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ16_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ16_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ17_MASK       (0x20000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ17_SHIFT      (17U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ17_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ17(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ17_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ17_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ18_MASK       (0x40000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ18_SHIFT      (18U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ18_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ18(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ18_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ18_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ19_MASK       (0x80000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ19_SHIFT      (19U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ19_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ19(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ19_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ19_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ20_MASK       (0x100000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ20_SHIFT      (20U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ20_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ20(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ20_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ20_MASK)
/*! @} */

/*! @name PRTN0_COFB1_CLKEN - Partition 0 COFB Set 1 Clock Enable Register */
/*! @{ */

#define MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK       (0x1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ32_SHIFT      (0U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ32_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ32(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ32_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK       (0x2U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ33_SHIFT      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ33_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ33(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ33_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK       (0x4U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ34_SHIFT      (2U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ34_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ34(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ34_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK       (0x40U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ38_SHIFT      (6U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ38_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ38(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ38_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK       (0x80U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ39_SHIFT      (7U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ39_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ39(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ39_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK       (0x100U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ40_SHIFT      (8U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ40_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ40(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ40_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK       (0x200U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ41_SHIFT      (9U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ41_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ41(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ41_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK       (0x400U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ42_SHIFT      (10U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ42_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ42(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ42_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ43_MASK       (0x800U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ43_SHIFT      (11U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ43_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ43(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ43_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ43_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK       (0x1000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ44_SHIFT      (12U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ44_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ44(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ44_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK       (0x2000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ45_SHIFT      (13U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ45_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ45(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ45_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ46_MASK       (0x4000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ46_SHIFT      (14U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ46_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ46(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ46_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ46_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ47_MASK       (0x8000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ47_SHIFT      (15U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ47_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ47(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ47_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ47_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ48_MASK       (0x10000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ48_SHIFT      (16U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ48_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ48(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ48_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ48_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ49_MASK       (0x20000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ49_SHIFT      (17U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ49_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ49(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ49_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ49_MASK)
/*! @} */

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/



#ifdef __cplusplus
}
#endif

/** @} */
#endif /* #ifndef CLOCK_IP_DERIVATIVE_006_H */

