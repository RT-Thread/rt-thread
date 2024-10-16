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

#ifndef CLOCK_IP_DERIVATIVE_002_H
#define CLOCK_IP_DERIVATIVE_002_H

/**
*   @file       Clock_Ip_Derivative_002.h
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
#define CLOCK_IP_DERIVATIVE_002_VENDOR_ID                       43
#define CLOCK_IP_DERIVATIVE_002_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_DERIVATIVE_002_AR_RELEASE_MINOR_VERSION        7
#define CLOCK_IP_DERIVATIVE_002_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_DERIVATIVE_002_SW_MAJOR_VERSION                5
#define CLOCK_IP_DERIVATIVE_002_SW_MINOR_VERSION                0
#define CLOCK_IP_DERIVATIVE_002_SW_PATCH_VERSION                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/


#define CLOCK_IP_DIVIDER_CALLBACKS_COUNT                                               4U
#define CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE                                       1U
#define CLOCK_IP_PLL_PLL0DIV_DE_DIV_OUTPUT                                             2U
#define CLOCK_IP_PLL_PLLDV_ODIV2_OUTPUT                                                3U

#define CLOCK_IP_DIVIDERTRIGGER_CALLBACKS_COUNT                                        2U
#define CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT                                1U

#define CLOCK_IP_XOSC_CALLBACKS_COUNT                                                  2U
#define CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL                                           1U

#define CLOCK_IP_IRCOSC_CALLBACKS_COUNT                                                3U
#define CLOCK_IP_FIRC_STDBY_ENABLE                                                     1U
#define CLOCK_IP_SIRC_STDBY_ENABLE                                                     2U

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

#define CLOCK_IP_CMU_INSTANCES_NO                                                      4U

#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD1 66000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD2 100000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD3 133000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD4 167000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD5 200000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD6 233000000U
#define CLOCK_IP_FLASH_WAIT_STATES_THRESHOLD7 250000000U

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
#endif /* #ifndef CLOCK_IP_DERIVATIVE_002_H */

