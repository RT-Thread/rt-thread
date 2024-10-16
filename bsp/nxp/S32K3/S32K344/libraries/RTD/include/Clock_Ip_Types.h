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

#ifndef CLOCK_IP_TYPES_H
#define CLOCK_IP_TYPES_H

/**
*   @file    Clock_Ip_Types.h
*   @version    5.0.0
*
*   @brief   CLOCK IP type header file.
*   @details CLOCK IP type header file.

*   @addtogroup CLOCK_DRIVER Clock Ip Driver
*   @{
*/

#if defined(__cplusplus)
extern "C"{
#endif
/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Clock_Ip_Cfg_Defines.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_TYPES_VENDOR_ID                       43
#define CLOCK_IP_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_TYPES_AR_RELEASE_MINOR_VERSION        7
#define CLOCK_IP_TYPES_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_TYPES_SW_MAJOR_VERSION                5
#define CLOCK_IP_TYPES_SW_MINOR_VERSION                0
#define CLOCK_IP_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((CLOCK_IP_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Types.h  and Std_Types.h are different"
#endif
#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/* Check if Clock_Ip_Types.h file and Clock_Ip_Cfg_Defines.h file have same versions */
#if (CLOCK_IP_TYPES_VENDOR_ID  != CLOCK_IP_CFG_DEFINES_VENDOR_ID)
    #error "Clock_Ip_Types.h and Clock_Ip_Cfg_Defines.h have different vendor IDs"
#endif

/* Check if Clock_Ip_Types.h file and Clock_Ip_Cfg_Defines.h file are of the same Autosar version */
#if ((CLOCK_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_TYPES_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_TYPES_AR_RELEASE_REVISION_VERSION != CLOCK_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip_Types.h and Clock_Ip_Cfg_Defines.h are different"
#endif

/* Check if Clock_Ip_Types.h file and Clock_Ip_Cfg_Defines.h file are of the same Software version */
#if ((CLOCK_IP_TYPES_SW_MAJOR_VERSION != CLOCK_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CLOCK_IP_TYPES_SW_MINOR_VERSION != CLOCK_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CLOCK_IP_TYPES_SW_PATCH_VERSION != CLOCK_IP_CFG_DEFINES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip_Types.h and Clock_Ip_Cfg_Defines.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
#if (defined(CLOCK_IP_POWER_NOTIFICATIONS))
/** @brief Power modes. */
typedef enum {

#if defined(CLOCK_IP_HAS_RUN_MODE)
    RUN_MODE                              = CLOCK_IP_HAS_RUN_MODE,
    VLPR_MODE                             = 1U,
    VLPS_MODE                             = 2U,
    HSRUN_MODE                            = 3U,
#endif
} Clock_Ip_PowerModesType;

/** @brief Power mode notification. */
typedef enum {

    BEFORE_POWER_MODE_CHANGE,                /* Before power mode change command is sent */
    POWER_MODE_CHANGE_IN_PROGRESS,         /* Power mode transition is in progress */
    POWER_MODE_CHANGED,                    /* Power mode transition completed */

} Clock_Ip_PowerNotificationType;
#endif

/** @brief Clock names. */
typedef enum {

    CLOCK_IS_OFF              = 0U,

#if defined(CLOCK_IP_HAS_FIRC_CLK)
    FIRC_CLK                  = CLOCK_IP_HAS_FIRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    FIRC_AE_CLK                  = CLOCK_IP_HAS_FIRC_AE_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_MUXED_CLK)
    FIRC_MUXED_CLK                  = CLOCK_IP_HAS_FIRC_MUXED_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_VLP_CLK)
    FIRC_VLP_CLK              = CLOCK_IP_HAS_FIRC_VLP_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_STOP_CLK)
    FIRC_STOP_CLK             = CLOCK_IP_HAS_FIRC_STOP_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_STANDBY_CLK)
    FIRC_STANDBY_CLK          = CLOCK_IP_HAS_FIRC_STANDBY_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_POSTDIV_CLK)
    FIRC_POSTDIV_CLK          = CLOCK_IP_HAS_FIRC_POSTDIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_FRO_CLK)
    FRO_CLK          = CLOCK_IP_HAS_FRO_CLK,
#endif
#if defined(CLOCK_IP_HAS_SAFE_CLK)
    SAFE_CLK                  = CLOCK_IP_HAS_SAFE_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIRC_CLK)
    SIRC_CLK                  = CLOCK_IP_HAS_SIRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIRC_VLP_CLK)
    SIRC_VLP_CLK              = CLOCK_IP_HAS_SIRC_VLP_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIRC_STOP_CLK)
    SIRC_STOP_CLK             = CLOCK_IP_HAS_SIRC_STOP_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIRC_STANDBY_CLK)
    SIRC_STANDBY_CLK          = CLOCK_IP_HAS_SIRC_STANDBY_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    SYSTEM_CLK          = CLOCK_IP_HAS_SYSTEM_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPO_128K_CLK)
    LPO_128K_CLK              = CLOCK_IP_HAS_LPO_128K_CLK,
#endif
#if defined(CLOCK_IP_HAS_FXOSC_CLK)
    FXOSC_CLK                 = CLOCK_IP_HAS_FXOSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    SXOSC_CLK                 = CLOCK_IP_HAS_SXOSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_SOSC_CLK)
    SOSC_CLK                  = CLOCK_IP_HAS_SOSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCELPLL_CLK)
    ACCELPLL_CLK              = CLOCK_IP_HAS_ACCELPLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_CLK)
    COREPLL_CLK               = CLOCK_IP_HAS_COREPLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_DDRPLL_CLK)
    DDRPLL_CLK                = CLOCK_IP_HAS_DDRPLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_CLK)
    PERIPHPLL_CLK             = CLOCK_IP_HAS_PERIPHPLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST0_PLL_CLK)
    LFAST0_PLL_CLK             = CLOCK_IP_HAS_LFAST0_PLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST1_PLL_CLK)
    LFAST1_PLL_CLK             = CLOCK_IP_HAS_LFAST1_PLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLL_CLK)
    PLL_CLK                   = CLOCK_IP_HAS_PLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLL0_CLK)
    PLL0_CLK                   = CLOCK_IP_HAS_PLL0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLL1_CLK)
    PLL1_CLK                   = CLOCK_IP_HAS_PLL1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    PLLAUX_CLK                   = CLOCK_IP_HAS_PLLAUX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
    PLLAUX_PHI0_CLK                   = CLOCK_IP_HAS_PLLAUX_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
    PLLAUX_PHI1_CLK                   = CLOCK_IP_HAS_PLLAUX_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
    PLLAUX_PHI2_CLK                   = CLOCK_IP_HAS_PLLAUX_PHI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPLL_CLK)
    SPLL_CLK                  = CLOCK_IP_HAS_SPLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_AURORAPLL_CLK)
    AURORAPLL_CLK             = CLOCK_IP_HAS_AURORAPLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_PLL_PHI0_CLK)
    ACCEL_PLL_PHI0_CLK        = CLOCK_IP_HAS_ACCEL_PLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_PLL_PHI1_CLK)
    ACCEL_PLL_PHI1_CLK        = CLOCK_IP_HAS_ACCEL_PLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_PHI0_CLK)
    CORE_PLL_PHI0_CLK         = CLOCK_IP_HAS_CORE_PLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_PHI1_CLK)
    CORE_PLL_PHI1_CLK         = CLOCK_IP_HAS_CORE_PLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS0_CLK)
    CORE_PLL_DFS0_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS1_CLK)
    CORE_PLL_DFS1_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS2_CLK)
    CORE_PLL_DFS2_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS2_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS3_CLK)
    CORE_PLL_DFS3_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS3_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS4_CLK)
    CORE_PLL_DFS4_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS4_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS5_CLK)
    CORE_PLL_DFS5_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS5_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_DFS6_CLK)
    CORE_PLL_DFS6_CLK         = CLOCK_IP_HAS_CORE_PLL_DFS6_CLK,
#endif
#if defined(CLOCK_IP_HAS_DDR_PLL_PHI0_CLK)
    DDR_PLL_PHI0_CLK          = CLOCK_IP_HAS_DDR_PLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI0_CLK)
    PERIPH_PLL_PHI0_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI1_CLK)
    PERIPH_PLL_PHI1_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI2_CLK)
    PERIPH_PLL_PHI2_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI3_CLK)
    PERIPH_PLL_PHI3_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI3_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI4_CLK)
    PERIPH_PLL_PHI4_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI4_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI5_CLK)
    PERIPH_PLL_PHI5_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI5_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI6_CLK)
    PERIPH_PLL_PHI6_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI6_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_PHI7_CLK)
    PERIPH_PLL_PHI7_CLK       = CLOCK_IP_HAS_PERIPH_PLL_PHI7_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS0_CLK)
    PERIPH_PLL_DFS0_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS1_CLK)
    PERIPH_PLL_DFS1_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS2_CLK)
    PERIPH_PLL_DFS2_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS2_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS3_CLK)
    PERIPH_PLL_DFS3_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS3_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS4_CLK)
    PERIPH_PLL_DFS4_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS4_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS5_CLK)
    PERIPH_PLL_DFS5_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS5_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_DFS6_CLK)
    PERIPH_PLL_DFS6_CLK       = CLOCK_IP_HAS_PERIPH_PLL_DFS6_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI0_CLK)
    COREPLL_PHI0_CLK          = CLOCK_IP_HAS_COREPLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI1_CLK)
    COREPLL_PHI1_CLK          = CLOCK_IP_HAS_COREPLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI2_CLK)
    COREPLL_PHI2_CLK          = CLOCK_IP_HAS_COREPLL_PHI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI3_CLK)
    COREPLL_PHI3_CLK          = CLOCK_IP_HAS_COREPLL_PHI3_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI4_CLK)
    COREPLL_PHI4_CLK          = CLOCK_IP_HAS_COREPLL_PHI4_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI5_CLK)
    COREPLL_PHI5_CLK          = CLOCK_IP_HAS_COREPLL_PHI5_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI6_CLK)
    COREPLL_PHI6_CLK          = CLOCK_IP_HAS_COREPLL_PHI6_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI7_CLK)
    COREPLL_PHI7_CLK          = CLOCK_IP_HAS_COREPLL_PHI7_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI8_CLK)
    COREPLL_PHI8_CLK          = CLOCK_IP_HAS_COREPLL_PHI8_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_PHI9_CLK)
    COREPLL_PHI9_CLK          = CLOCK_IP_HAS_COREPLL_PHI9_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS0_CLK)
    COREPLL_DFS0_CLK          = CLOCK_IP_HAS_COREPLL_DFS0_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS1_CLK)
    COREPLL_DFS1_CLK          = CLOCK_IP_HAS_COREPLL_DFS1_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS2_CLK)
    COREPLL_DFS2_CLK          = CLOCK_IP_HAS_COREPLL_DFS2_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS3_CLK)
    COREPLL_DFS3_CLK          = CLOCK_IP_HAS_COREPLL_DFS3_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS4_CLK)
    COREPLL_DFS4_CLK          = CLOCK_IP_HAS_COREPLL_DFS4_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS5_CLK)
    COREPLL_DFS5_CLK          = CLOCK_IP_HAS_COREPLL_DFS5_CLK,
#endif
#if defined(CLOCK_IP_HAS_COREPLL_DFS6_CLK)
    COREPLL_DFS6_CLK          = CLOCK_IP_HAS_COREPLL_DFS6_CLK,
#endif
#if defined(CLOCK_IP_HAS_DDRPLL_PHI0_CLK)
    DDRPLL_PHI0_CLK           = CLOCK_IP_HAS_DDRPLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI0_CLK)
    PERIPHPLL_PHI0_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI1_CLK)
    PERIPHPLL_PHI1_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI2_CLK)
    PERIPHPLL_PHI2_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI3_CLK)
    PERIPHPLL_PHI3_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI3_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI4_CLK)
    PERIPHPLL_PHI4_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI4_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI5_CLK)
    PERIPHPLL_PHI5_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI5_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI6_CLK)
    PERIPHPLL_PHI6_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI6_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI7_CLK)
    PERIPHPLL_PHI7_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI7_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI8_CLK)
    PERIPHPLL_PHI8_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI8_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_PHI9_CLK)
    PERIPHPLL_PHI9_CLK        = CLOCK_IP_HAS_PERIPHPLL_PHI9_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS0_CLK)
    PERIPHPLL_DFS0_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS1_CLK)
    PERIPHPLL_DFS1_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS2_CLK)
    PERIPHPLL_DFS2_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS2_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS3_CLK)
    PERIPHPLL_DFS3_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS3_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS4_CLK)
    PERIPHPLL_DFS4_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS4_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS5_CLK)
    PERIPHPLL_DFS5_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS5_CLK,
#endif
#if defined(CLOCK_IP_HAS_PERIPHPLL_DFS6_CLK)
    PERIPHPLL_DFS6_CLK        = CLOCK_IP_HAS_PERIPHPLL_DFS6_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLL_PHI0_CLK)
    PLL_PHI0_CLK              = CLOCK_IP_HAS_PLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLL_PHI1_CLK)
    PLL_PHI1_CLK              = CLOCK_IP_HAS_PLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_AURORAPLL_PHI0_CLK)
    AURORAPLL_PHI0_CLK       = CLOCK_IP_HAS_AURORAPLL_PHI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_AURORAPLL_PHI1_CLK)
    AURORAPLL_PHI1_CLK       = CLOCK_IP_HAS_AURORAPLL_PHI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_AURORAPLL_PHI2_CLK)
    AURORAPLL_PHI2_CLK       = CLOCK_IP_HAS_AURORAPLL_PHI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST0_PLL_PH0_CLK)
    LFAST0_PLL_PH0_CLK       = CLOCK_IP_HAS_LFAST0_PLL_PH0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST1_PLL_PH0_CLK)
    LFAST1_PLL_PH0_CLK       = CLOCK_IP_HAS_LFAST1_PLL_PH0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLL_POSTDIV_CLK)
    PLL_POSTDIV_CLK           = CLOCK_IP_HAS_PLL_POSTDIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
    PLLAUX_POSTDIV_CLK           = CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIRCDIV1_CLK)
    SIRCDIV1_CLK              = CLOCK_IP_HAS_SIRCDIV1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIRCDIV2_CLK)
    SIRCDIV2_CLK              = CLOCK_IP_HAS_SIRCDIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_FDIV0_CLK)
    FDIV0_CLK              = CLOCK_IP_HAS_FDIV0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRCDIV1_CLK)
    FIRCDIV1_CLK              = CLOCK_IP_HAS_FIRCDIV1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRCDIV2_CLK)
    FIRCDIV2_CLK              = CLOCK_IP_HAS_FIRCDIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SOSCDIV1_CLK)
    SOSCDIV1_CLK              = CLOCK_IP_HAS_SOSCDIV1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SOSCDIV2_CLK)
    SOSCDIV2_CLK              = CLOCK_IP_HAS_SOSCDIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPLLDIV1_CLK)
    SPLLDIV1_CLK              = CLOCK_IP_HAS_SPLLDIV1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPLLDIV2_CLK)
    SPLLDIV2_CLK              = CLOCK_IP_HAS_SPLLDIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPO_32K_CLK)
    LPO_32K_CLK               = CLOCK_IP_HAS_LPO_32K_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPO_1K_CLK)
    LPO_1K_CLK                = CLOCK_IP_HAS_LPO_1K_CLK,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_LANE_0_TX)
    SERDES_0_LANE_0_TX        = CLOCK_IP_HAS_SERDES_0_LANE_0_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_LANE_0_CDR)
    SERDES_0_LANE_0_CDR       = CLOCK_IP_HAS_SERDES_0_LANE_0_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_LANE_1_TX)
    SERDES_0_LANE_1_TX        = CLOCK_IP_HAS_SERDES_0_LANE_1_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_LANE_1_CDR)
    SERDES_0_LANE_1_CDR       = CLOCK_IP_HAS_SERDES_0_LANE_1_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_LANE_0_TX)
    SERDES_1_LANE_0_TX        = CLOCK_IP_HAS_SERDES_1_LANE_0_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_LANE_0_CDR)
    SERDES_1_LANE_0_CDR       = CLOCK_IP_HAS_SERDES_1_LANE_0_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_LANE_1_TX)
    SERDES_1_LANE_1_TX        = CLOCK_IP_HAS_SERDES_1_LANE_1_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_LANE_1_CDR)
    SERDES_1_LANE_1_CDR       = CLOCK_IP_HAS_SERDES_1_LANE_1_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_XPCS_0_TX)
    SERDES_0_XPCS_0_TX        = CLOCK_IP_HAS_SERDES_0_XPCS_0_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_XPCS_0_CDR)
    SERDES_0_XPCS_0_CDR       = CLOCK_IP_HAS_SERDES_0_XPCS_0_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_XPCS_1_TX)
    SERDES_0_XPCS_1_TX        = CLOCK_IP_HAS_SERDES_0_XPCS_1_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_0_XPCS_1_CDR)
    SERDES_0_XPCS_1_CDR       = CLOCK_IP_HAS_SERDES_0_XPCS_1_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_XPCS_0_TX)
    SERDES_1_XPCS_0_TX        = CLOCK_IP_HAS_SERDES_1_XPCS_0_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_XPCS_0_CDR)
    SERDES_1_XPCS_0_CDR       = CLOCK_IP_HAS_SERDES_1_XPCS_0_CDR,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_XPCS_1_TX)
    SERDES_1_XPCS_1_TX        = CLOCK_IP_HAS_SERDES_1_XPCS_1_TX,
#endif
#if defined(CLOCK_IP_HAS_SERDES_1_XPCS_1_CDR)
    SERDES_1_XPCS_1_CDR       = CLOCK_IP_HAS_SERDES_1_XPCS_1_CDR,
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
    EMAC_MII_RX_CLK           = CLOCK_IP_HAS_EMAC_MII_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
    EMAC_MII_RMII_TX_CLK      = CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH_RGMII_REF_CLK)
    ETH_RGMII_REF_CLK         = CLOCK_IP_HAS_ETH_RGMII_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_TMR_1588_CLK)
    TMR_1588_CLK            = CLOCK_IP_HAS_TMR_1588_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH_EXT_TS_CLK)
    ETH_EXT_TS_CLK            = CLOCK_IP_HAS_ETH_EXT_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_EXT_RX_CLK)
    ETH0_EXT_RX_CLK           = CLOCK_IP_HAS_ETH0_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_EXT_TX_CLK)
    ETH0_EXT_TX_CLK           = CLOCK_IP_HAS_ETH0_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_EXT_RX_CLK)
    ETH1_EXT_RX_CLK           = CLOCK_IP_HAS_ETH1_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_EXT_TX_CLK)
    ETH1_EXT_TX_CLK           = CLOCK_IP_HAS_ETH1_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST0_EXT_REF_CLK)
    LFAST0_EXT_REF_CLK        = CLOCK_IP_HAS_LFAST0_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST1_EXT_REF_CLK)
    LFAST1_EXT_REF_CLK        = CLOCK_IP_HAS_LFAST1_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM_0_EXT_REF_CLK)
    FTM_0_EXT_REF_CLK         = CLOCK_IP_HAS_FTM_0_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM_1_EXT_REF_CLK)
    FTM_1_EXT_REF_CLK         = CLOCK_IP_HAS_FTM_1_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
    GMAC_MII_RGMII_RX_CLK           = CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
    GMAC_MII_RMII_RGMII_TX_CLK      = CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_EXT_REF_CLK)
    GMAC_0_EXT_REF_CLK        = CLOCK_IP_HAS_GMAC_0_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_EXT_RX_CLK)
    GMAC_0_EXT_RX_CLK         = CLOCK_IP_HAS_GMAC_0_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_EXT_TX_CLK)
    GMAC_0_EXT_TX_CLK         = CLOCK_IP_HAS_GMAC_0_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_SGMII_REF_CLK)
    GMAC_0_SGMII_REF_CLK      = CLOCK_IP_HAS_GMAC_0_SGMII_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_SGMII_RX_CLK)
    GMAC_0_SGMII_RX_CLK       = CLOCK_IP_HAS_GMAC_0_SGMII_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_SGMII_TX_CLK)
    GMAC_0_SGMII_TX_CLK       = CLOCK_IP_HAS_GMAC_0_SGMII_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_1_EXT_REF_CLK)
    GMAC_1_EXT_REF_CLK        = CLOCK_IP_HAS_GMAC_1_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_1_EXT_RX_CLK)
    GMAC_1_EXT_RX_CLK         = CLOCK_IP_HAS_GMAC_1_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_1_EXT_TX_CLK)
    GMAC_1_EXT_TX_CLK         = CLOCK_IP_HAS_GMAC_1_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_EXT_TS_CLK)
    GMAC_EXT_TS_CLK           = CLOCK_IP_HAS_GMAC_EXT_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_0_EXT_TS_CLK)
    GMAC_0_EXT_TS_CLK         = CLOCK_IP_HAS_GMAC_0_EXT_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_1_EXT_TS_CLK)
    GMAC_1_EXT_TS_CLK         = CLOCK_IP_HAS_GMAC_1_EXT_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_1_INT_REF_CLK)
    GMAC_1_INT_REF_CLK         = CLOCK_IP_HAS_GMAC_1_INT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_0_EXT_REF_CLK)
    PFE_MAC_0_EXT_REF_CLK     = CLOCK_IP_HAS_PFE_MAC_0_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_0_EXT_RX_CLK)
    PFE_MAC_0_EXT_RX_CLK      = CLOCK_IP_HAS_PFE_MAC_0_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_0_EXT_TX_CLK)
    PFE_MAC_0_EXT_TX_CLK      = CLOCK_IP_HAS_PFE_MAC_0_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_1_EXT_REF_CLK)
    PFE_MAC_1_EXT_REF_CLK     = CLOCK_IP_HAS_PFE_MAC_1_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_1_EXT_RX_CLK)
    PFE_MAC_1_EXT_RX_CLK      = CLOCK_IP_HAS_PFE_MAC_1_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_1_EXT_TX_CLK)
    PFE_MAC_1_EXT_TX_CLK      = CLOCK_IP_HAS_PFE_MAC_1_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_2_EXT_REF_CLK)
    PFE_MAC_2_EXT_REF_CLK     = CLOCK_IP_HAS_PFE_MAC_2_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_2_EXT_RX_CLK)
    PFE_MAC_2_EXT_RX_CLK      = CLOCK_IP_HAS_PFE_MAC_2_EXT_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_MAC_2_EXT_TX_CLK)
    PFE_MAC_2_EXT_TX_CLK      = CLOCK_IP_HAS_PFE_MAC_2_EXT_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_TCLK0_REF_CLK)
    TCLK0_REF_CLK             = CLOCK_IP_HAS_TCLK0_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_TCLK1_REF_CLK)
    TCLK1_REF_CLK             = CLOCK_IP_HAS_TCLK1_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_TCLK2_REF_CLK)
    TCLK2_REF_CLK             = CLOCK_IP_HAS_TCLK2_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_TEST_CLK)
    TEST_CLK             = CLOCK_IP_HAS_TEST_CLK,
#endif
#if defined(CLOCK_IP_HAS_TPR_CLK)
    TPR_CLK             = CLOCK_IP_HAS_TPR_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTC_CLKIN)
    RTC_CLKIN                 = CLOCK_IP_HAS_RTC_CLKIN,
#endif
#if defined(CLOCK_IP_HAS_A53_CORE_CLK)
    A53_CORE_CLK              = CLOCK_IP_HAS_A53_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_A53_CORE_DIV2_CLK)
    A53_CORE_DIV2_CLK         = CLOCK_IP_HAS_A53_CORE_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_A53_CORE_DIV4_CLK)
    A53_CORE_DIV4_CLK         = CLOCK_IP_HAS_A53_CORE_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_A53_CORE_DIV10_CLK)
    A53_CORE_DIV10_CLK        = CLOCK_IP_HAS_A53_CORE_DIV10_CLK,
#endif
#if defined(CLOCK_IP_HAS_AIPS_PLAT_CLK)
    AIPS_PLAT_CLK             = CLOCK_IP_HAS_AIPS_PLAT_CLK,
#endif
#if defined(CLOCK_IP_HAS_AIPS_SLOW_CLK)
    AIPS_SLOW_CLK             = CLOCK_IP_HAS_AIPS_SLOW_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL3_CLK)
    ACCEL3_CLK                = CLOCK_IP_HAS_ACCEL3_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL3_DIV3_CLK)
    ACCEL3_DIV3_CLK           = CLOCK_IP_HAS_ACCEL3_DIV3_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL4_CLK)
    ACCEL4_CLK                = CLOCK_IP_HAS_ACCEL4_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT_RUN_CLK)
    CLKOUT_RUN_CLK            = CLOCK_IP_HAS_CLKOUT_RUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_DCM_CLK)
    DCM_CLK                   = CLOCK_IP_HAS_DCM_CLK,
#endif
#if defined(CLOCK_IP_HAS_DDR_CLK)
    DDR_CLK                   = CLOCK_IP_HAS_DDR_CLK,
#endif
#if defined(CLOCK_IP_HAS_DDR0_CLK)
    DDR0_CLK                   = CLOCK_IP_HAS_DDR0_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMACRC0_CLK)
    DMACRC0_CLK                   = CLOCK_IP_HAS_DMACRC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMACRC1_CLK)
    DMACRC1_CLK                   = CLOCK_IP_HAS_DMACRC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMACRC4_CLK)
    DMACRC4_CLK                   = CLOCK_IP_HAS_DMACRC4_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMACRC5_CLK)
    DMACRC5_CLK                   = CLOCK_IP_HAS_DMACRC5_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_REF_DIV_CLK)
    GMAC_REF_DIV_CLK          = CLOCK_IP_HAS_GMAC_REF_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_REF_DIV_CLK)
    GMAC0_REF_DIV_CLK         = CLOCK_IP_HAS_GMAC0_REF_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_REF_CLK)
    GMAC0_REF_CLK             = CLOCK_IP_HAS_GMAC0_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_REF_DIV_CLK)
    GMAC1_REF_DIV_CLK         = CLOCK_IP_HAS_GMAC1_REF_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_REF_CLK)
    GMAC1_REF_CLK             = CLOCK_IP_HAS_GMAC1_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_INT_CLK)
    GMAC1_INT_CLK             = CLOCK_IP_HAS_GMAC1_INT_CLK,
#endif
#if defined(CLOCK_IP_HAS_AURORA_TRACE_TEST_CLK)
    AURORA_TRACE_TEST_CLK             = CLOCK_IP_HAS_AURORA_TRACE_TEST_CLK,
#endif
#if defined(CLOCK_IP_HAS_HSE_CLK)
    HSE_CLK                   = CLOCK_IP_HAS_HSE_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    LBIST_CLK                 = CLOCK_IP_HAS_LBIST_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_PE_CLK)
    PFE_PE_CLK                = CLOCK_IP_HAS_PFE_PE_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFE_SYS_CLK)
    PFE_SYS_CLK                = CLOCK_IP_HAS_PFE_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_PER_CLK)
    PER_CLK                   = CLOCK_IP_HAS_PER_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC0_REF_DIV_CLK)
    PFEMAC0_REF_DIV_CLK       = CLOCK_IP_HAS_PFEMAC0_REF_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC1_REF_DIV_CLK)
    PFEMAC1_REF_DIV_CLK       = CLOCK_IP_HAS_PFEMAC1_REF_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC2_REF_DIV_CLK)
    PFEMAC2_REF_DIV_CLK       = CLOCK_IP_HAS_PFEMAC2_REF_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    QSPI_MEM_CLK              = CLOCK_IP_HAS_QSPI_MEM_CLK,
#endif
#if defined(CLOCK_IP_HAS_SCS_CLK)
    SCS_CLK                   = CLOCK_IP_HAS_SCS_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_2X_CLK)
    XBAR_2X_CLK               = CLOCK_IP_HAS_XBAR_2X_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_CLK)
    XBAR_CLK                  = CLOCK_IP_HAS_XBAR_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_DIV2_CLK)
    XBAR_DIV2_CLK             = CLOCK_IP_HAS_XBAR_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_DIV3_CLK)
    XBAR_DIV3_CLK             = CLOCK_IP_HAS_XBAR_DIV3_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_DIV4_CLK)
    XBAR_DIV4_CLK             = CLOCK_IP_HAS_XBAR_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_DIV6_CLK)
    XBAR_DIV6_CLK             = CLOCK_IP_HAS_XBAR_DIV6_CLK,
#endif
#if defined(CLOCK_IP_HAS_XMII_CLK_125MHZ)
    XMII_CLK_125MHZ             = CLOCK_IP_HAS_XMII_CLK_125MHZ,
#endif
#if defined(CLOCK_IP_HAS_XMII_CLK_2M5HZ)
    XMII_CLK_2M5HZ             = CLOCK_IP_HAS_XMII_CLK_2M5HZ,
#endif
#if defined(CLOCK_IP_HAS_XMII_CLK_25MHZ)
    XMII_CLK_25MHZ             = CLOCK_IP_HAS_XMII_CLK_25MHZ,
#endif
#if defined(CLOCK_IP_HAS_XMII_CLK_50MHZ)
    XMII_CLK_50MHZ             = CLOCK_IP_HAS_XMII_CLK_50MHZ,
#endif
#if defined(CLOCK_IP_HAS_XOSC_CLK)
    XOSC_CLK             = CLOCK_IP_HAS_XOSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_SERDES_REF_CLK)
    SERDES_REF_CLK            = CLOCK_IP_HAS_SERDES_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_SERDES0_REF_CLK)
    SERDES0_REF_CLK            = CLOCK_IP_HAS_SERDES0_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_SERDES1_REF_CLK)
    SERDES1_REF_CLK            = CLOCK_IP_HAS_SERDES1_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_SCS_RUN_CLK)
    SCS_RUN_CLK               = CLOCK_IP_HAS_SCS_RUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_SCS_VLPR_CLK)
    SCS_VLPR_CLK              = CLOCK_IP_HAS_SCS_VLPR_CLK,
#endif
#if defined(CLOCK_IP_HAS_SCS_HSRUN_CLK)
    SCS_HSRUN_CLK             = CLOCK_IP_HAS_SCS_HSRUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_CLK)
    CORE_CLK                  = CLOCK_IP_HAS_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    CM7_CORE_CLK              = CLOCK_IP_HAS_CM7_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_RUN_CLK)
    CORE_RUN_CLK              = CLOCK_IP_HAS_CORE_RUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_VLPR_CLK)
    CORE_VLPR_CLK             = CLOCK_IP_HAS_CORE_VLPR_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_HSRUN_CLK)
    CORE_HSRUN_CLK             = CLOCK_IP_HAS_CORE_HSRUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_BUS_CLK)
    BUS_CLK                   = CLOCK_IP_HAS_BUS_CLK,
#endif
#if defined(CLOCK_IP_HAS_BUS_RUN_CLK)
    BUS_RUN_CLK               = CLOCK_IP_HAS_BUS_RUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_BUS_VLPR_CLK)
    BUS_VLPR_CLK              = CLOCK_IP_HAS_BUS_VLPR_CLK,
#endif
#if defined(CLOCK_IP_HAS_BUS_HSRUN_CLK)
    BUS_HSRUN_CLK              = CLOCK_IP_HAS_BUS_HSRUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_SLOW_CLK)
    SLOW_CLK                  = CLOCK_IP_HAS_SLOW_CLK,
#endif
#if defined(CLOCK_IP_HAS_SLOW_RUN_CLK)
    SLOW_RUN_CLK              = CLOCK_IP_HAS_SLOW_RUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_SLOW_VLPR_CLK)
    SLOW_VLPR_CLK             = CLOCK_IP_HAS_SLOW_VLPR_CLK,
#endif
#if defined(CLOCK_IP_HAS_SLOW_HSRUN_CLK)
    SLOW_HSRUN_CLK             = CLOCK_IP_HAS_SLOW_HSRUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPO_CLK)
    LPO_CLK                   = CLOCK_IP_HAS_LPO_CLK,
#endif
#if defined(CLOCK_IP_HAS_SCG_CLKOUT_CLK)
    SCG_CLKOUT_CLK            = CLOCK_IP_HAS_SCG_CLKOUT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM0_EXT_CLK)
    FTM0_EXT_CLK              = CLOCK_IP_HAS_FTM0_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM1_EXT_CLK)
    FTM1_EXT_CLK              = CLOCK_IP_HAS_FTM1_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM2_EXT_CLK)
    FTM2_EXT_CLK              = CLOCK_IP_HAS_FTM2_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM3_EXT_CLK)
    FTM3_EXT_CLK              = CLOCK_IP_HAS_FTM3_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM4_EXT_CLK)
    FTM4_EXT_CLK              = CLOCK_IP_HAS_FTM4_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM5_EXT_CLK)
    FTM5_EXT_CLK              = CLOCK_IP_HAS_FTM5_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM6_EXT_CLK)
    FTM6_EXT_CLK              = CLOCK_IP_HAS_FTM6_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM7_EXT_CLK)
    FTM7_EXT_CLK              = CLOCK_IP_HAS_FTM7_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_Px_CLKOUT_SRC_CLK)
    Px_CLKOUT_SRC_CLK         = CLOCK_IP_HAS_Px_CLKOUT_SRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_Px_PSI5_S_UTIL_CLK)
    Px_PSI5_S_UTIL_CLK        = CLOCK_IP_HAS_Px_PSI5_S_UTIL_CLK,
#endif
#if defined(CLOCK_IP_HAS_SHIFT_LBIST_CLK)
    SHIFT_LBIST_CLK           = CLOCK_IP_HAS_SHIFT_LBIST_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_SYS_CLK)
    P0_SYS_CLK                = CLOCK_IP_HAS_P0_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_SYS_CLK)
    P1_SYS_CLK                = CLOCK_IP_HAS_P1_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_SYS_DIV2_CLK)
    P1_SYS_DIV2_CLK           = CLOCK_IP_HAS_P1_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_SYS_DIV4_CLK)
    P1_SYS_DIV4_CLK           = CLOCK_IP_HAS_P1_SYS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_SYS_CLK)
    P2_SYS_CLK                = CLOCK_IP_HAS_P2_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_M33_CLK)
    CORE_M33_CLK              = CLOCK_IP_HAS_CORE_M33_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_SYS_DIV2_CLK)
    P2_SYS_DIV2_CLK           = CLOCK_IP_HAS_P2_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_SYS_DIV4_CLK)
    P2_SYS_DIV4_CLK           = CLOCK_IP_HAS_P2_SYS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_SYS_CLK)
    P3_SYS_CLK                = CLOCK_IP_HAS_P3_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_SYS_DIV2_CLK)
    CE_SYS_DIV2_CLK           = CLOCK_IP_HAS_CE_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_SYS_DIV4_CLK)
    CE_SYS_DIV4_CLK           = CLOCK_IP_HAS_CE_SYS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_SYS_DIV2_NOC_CLK)
    P3_SYS_DIV2_NOC_CLK       = CLOCK_IP_HAS_P3_SYS_DIV2_NOC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_SYS_DIV4_CLK)
    P3_SYS_DIV4_CLK           = CLOCK_IP_HAS_P3_SYS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_SYS_CLK)
    P4_SYS_CLK                = CLOCK_IP_HAS_P4_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_SYS_DIV2_CLK)
    P4_SYS_DIV2_CLK           = CLOCK_IP_HAS_P4_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_HSE_SYS_DIV2_CLK)
    HSE_SYS_DIV2_CLK          = CLOCK_IP_HAS_HSE_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_SYS_CLK)
    P5_SYS_CLK                = CLOCK_IP_HAS_P5_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_SYS_DIV2_CLK)
    P5_SYS_DIV2_CLK           = CLOCK_IP_HAS_P5_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_SYS_DIV4_CLK)
    P5_SYS_DIV4_CLK           = CLOCK_IP_HAS_P5_SYS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_MATH_CLK)
    P2_MATH_CLK               = CLOCK_IP_HAS_P2_MATH_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_MATH_DIV3_CLK)
    P2_MATH_DIV3_CLK          = CLOCK_IP_HAS_P2_MATH_DIV3_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_CLK)
    RTU0_CORE_CLK             = CLOCK_IP_HAS_RTU0_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_DIV2_CLK)
    RTU0_CORE_DIV2_CLK        = CLOCK_IP_HAS_RTU0_CORE_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_CLK)
    RTU1_CORE_CLK             = CLOCK_IP_HAS_RTU1_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_DIV2_CLK)
    RTU1_CORE_DIV2_CLK        = CLOCK_IP_HAS_RTU1_CORE_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_UTIL_CLK)
    P0_PSI5_S_UTIL_CLK        = CLOCK_IP_HAS_P0_PSI5_S_UTIL_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_UTIL_CLK)
    P4_PSI5_S_UTIL_CLK        = CLOCK_IP_HAS_P4_PSI5_S_UTIL_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    SYSTEM_DRUN_CLK           = CLOCK_IP_HAS_SYSTEM_DRUN_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    SYSTEM_DIV2_CLK           = CLOCK_IP_HAS_SYSTEM_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    SYSTEM_DIV4_MON1_CLK      = CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    SYSTEM_DIV4_MON2_CLK      = CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_CLK)
    SYS_CLK                   = CLOCK_IP_HAS_SYS_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_DIV2_CLK)
    SYS_DIV2_CLK              = CLOCK_IP_HAS_SYS_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_DIV4_CLK)
    SYS_DIV4_CLK              = CLOCK_IP_HAS_SYS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_DIV8_CLK)
    SYS_DIV8_CLK              = CLOCK_IP_HAS_SYS_DIV8_CLK,
#endif
#if defined(CLOCK_IP_HAS_RT_DAPB_CLK)
    RT_DAPB_CLK               = CLOCK_IP_HAS_RT_DAPB_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_CLK)
    ACCEL_CLK                 = CLOCK_IP_HAS_ACCEL_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_DIV3_CLK)
    ACCEL_DIV3_CLK            = CLOCK_IP_HAS_ACCEL_DIV3_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_DIV4_CLK)
    ACCEL_DIV4_CLK            = CLOCK_IP_HAS_ACCEL_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_XBAR_CLK)
    ACCEL_XBAR_CLK            = CLOCK_IP_HAS_ACCEL_XBAR_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_XBAR_DIV2_CLK)
    ACCEL_XBAR_DIV2_CLK       = CLOCK_IP_HAS_ACCEL_XBAR_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_XBAR_DIV4_CLK)
    ACCEL_XBAR_DIV4_CLK       = CLOCK_IP_HAS_ACCEL_XBAR_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL_XBAR_DIV8_CLK)
    ACCEL_XBAR_DIV8_CLK       = CLOCK_IP_HAS_ACCEL_XBAR_DIV8_CLK,
#endif
#if defined(CLOCK_IP_HAS_AP_DAPB_CLK)
    AP_DAPB_CLK               = CLOCK_IP_HAS_AP_DAPB_CLK,
#endif
THE_LAST_PRODUCER_CLK         = CLOCK_IP_FEATURE_PRODUCERS_NO,     /* Number of producers clocks */
#if defined(CLOCK_IP_HAS_ACCEL4_LAX0_CLK)
    ACCEL4_LAX0_CLK           = CLOCK_IP_HAS_ACCEL4_LAX0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ACCEL4_LAX1_CLK)
    ACCEL4_LAX1_CLK           = CLOCK_IP_HAS_ACCEL4_LAX1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC0_CLK)
    ADC0_CLK                  = CLOCK_IP_HAS_ADC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC1_CLK)
    ADC1_CLK                  = CLOCK_IP_HAS_ADC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC2_CLK)
    ADC2_CLK                  = CLOCK_IP_HAS_ADC2_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
    ADC3_CLK                  = CLOCK_IP_HAS_ADC3_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
    ADC4_CLK                  = CLOCK_IP_HAS_ADC4_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
    ADC5_CLK                  = CLOCK_IP_HAS_ADC5_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
    ADC6_CLK                  = CLOCK_IP_HAS_ADC6_CLK,
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
    ADCBIST_CLK               = CLOCK_IP_HAS_ADCBIST_CLK,
#endif
#if defined(CLOCK_IP_HAS_AURORAPLL_DIFF_CLK)
    AURORAPLL_DIFF_CLK        = CLOCK_IP_HAS_AURORAPLL_DIFF_CLK,
#endif
#if defined(CLOCK_IP_HAS_BCTU0_CLK)
    BCTU0_CLK                 = CLOCK_IP_HAS_BCTU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
    BCTU1_CLK                 = CLOCK_IP_HAS_BCTU1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_SYS_DIV2_MON_CLK)
    CE_SYS_DIV2_MON_CLK       = CLOCK_IP_HAS_CE_SYS_DIV2_MON_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_EDMA_CLK)
    CE_EDMA_CLK       = CLOCK_IP_HAS_CE_EDMA_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_PIT0_CLK)
    CE_PIT0_CLK       = CLOCK_IP_HAS_CE_PIT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_PIT1_CLK)
    CE_PIT1_CLK       = CLOCK_IP_HAS_CE_PIT1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_PIT2_CLK)
    CE_PIT2_CLK       = CLOCK_IP_HAS_CE_PIT2_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_PIT3_CLK)
    CE_PIT3_CLK       = CLOCK_IP_HAS_CE_PIT3_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_PIT4_CLK)
    CE_PIT4_CLK       = CLOCK_IP_HAS_CE_PIT4_CLK,
#endif
#if defined(CLOCK_IP_HAS_CE_PIT5_CLK)
    CE_PIT5_CLK       = CLOCK_IP_HAS_CE_PIT5_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT_STANDBY_CLK)
    CLKOUT_STANDBY_CLK        = CLOCK_IP_HAS_CLKOUT_STANDBY_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT0_CLK)
    CLKOUT0_CLK               = CLOCK_IP_HAS_CLKOUT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT1_CLK)
    CLKOUT1_CLK               = CLOCK_IP_HAS_CLKOUT1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT2_CLK)
    CLKOUT2_CLK               = CLOCK_IP_HAS_CLKOUT2_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT3_CLK)
    CLKOUT3_CLK               = CLOCK_IP_HAS_CLKOUT3_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT4_CLK)
    CLKOUT4_CLK               = CLOCK_IP_HAS_CLKOUT4_CLK,
#endif
#if defined(CLOCK_IP_HAS_CLKOUT5_CLK)
    CLKOUT5_CLK               = CLOCK_IP_HAS_CLKOUT5_CLK,
#endif
#if defined(CLOCK_IP_HAS_CMP0_CLK)
    CMP0_CLK                  = CLOCK_IP_HAS_CMP0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CMP1_CLK)
    CMP1_CLK                  = CLOCK_IP_HAS_CMP1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
    CMP2_CLK                  = CLOCK_IP_HAS_CMP2_CLK,
#endif
#if defined(CLOCK_IP_HAS_CMU0_CLK)
    CMU0_CLK                  = CLOCK_IP_HAS_CMU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CMU1_CLK)
    CMU1_CLK                  = CLOCK_IP_HAS_CMU1_CLK,
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
    COOLFLUX_D_RAM0_CLK                  = CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
    COOLFLUX_D_RAM1_CLK                  = CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
    COOLFLUX_DSP16L_CLK                  = CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK,
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
    COOLFLUX_I_RAM0_CLK                  = CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
    COOLFLUX_I_RAM1_CLK                  = CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_A53_CLUSTER_0_CLK)
    CORE_A53_CLUSTER_0_CLK    = CLOCK_IP_HAS_CORE_A53_CLUSTER_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_A53_CLUSTER_1_CLK)
    CORE_A53_CLUSTER_1_CLK    = CLOCK_IP_HAS_CORE_A53_CLUSTER_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_M7_0_CLK)
    CORE_M7_0_CLK             = CLOCK_IP_HAS_CORE_M7_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_M7_1_CLK)
    CORE_M7_1_CLK             = CLOCK_IP_HAS_CORE_M7_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_M7_2_CLK)
    CORE_M7_2_CLK             = CLOCK_IP_HAS_CORE_M7_2_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_M7_3_CLK)
    CORE_M7_3_CLK             = CLOCK_IP_HAS_CORE_M7_3_CLK,
#endif
#if defined(CLOCK_IP_HAS_CRC0_CLK)
    CRC0_CLK                  = CLOCK_IP_HAS_CRC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CTU0_CLK)
    CTU0_CLK                  = CLOCK_IP_HAS_CTU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CTU1_CLK)
    CTU1_CLK                  = CLOCK_IP_HAS_CTU1_CLK,
#endif
#if defined(CLOCK_IP_HAS_DAPB_CLK)
    DAPB_CLK                  = CLOCK_IP_HAS_DAPB_CLK,
#endif
#if defined(CLOCK_IP_HAS_DCM0_CLK)
    DCM0_CLK                  = CLOCK_IP_HAS_DCM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA_CRC0_CLK)
    DMA_CRC0_CLK              = CLOCK_IP_HAS_DMA_CRC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA_CRC1_CLK)
    DMA_CRC1_CLK              = CLOCK_IP_HAS_DMA_CRC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA0_CLK)
    DMA0_CLK                  = CLOCK_IP_HAS_DMA0_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA1_CLK)
    DMA1_CLK                  = CLOCK_IP_HAS_DMA1_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMAMUX0_CLK)
    DMAMUX0_CLK               = CLOCK_IP_HAS_DMAMUX0_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMAMUX1_CLK)
    DMAMUX1_CLK               = CLOCK_IP_HAS_DMAMUX1_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
    DMAMUX2_CLK               = CLOCK_IP_HAS_DMAMUX2_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
    DMAMUX3_CLK               = CLOCK_IP_HAS_DMAMUX3_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMAMUX4_CLK)
    DMAMUX4_CLK               = CLOCK_IP_HAS_DMAMUX4_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMAMUX5_CLK)
    DMAMUX5_CLK               = CLOCK_IP_HAS_DMAMUX5_CLK,
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
    DSPI_MSC_CLK               = CLOCK_IP_HAS_DSPI_MSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA_CLK)
    EDMA_CLK                  = CLOCK_IP_HAS_EDMA_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_CLK)
    EDMA0_CLK                 = CLOCK_IP_HAS_EDMA0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD0_CLK)
    EDMA0_TCD0_CLK            = CLOCK_IP_HAS_EDMA0_TCD0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD1_CLK)
    EDMA0_TCD1_CLK            = CLOCK_IP_HAS_EDMA0_TCD1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD2_CLK)
    EDMA0_TCD2_CLK            = CLOCK_IP_HAS_EDMA0_TCD2_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD3_CLK)
    EDMA0_TCD3_CLK            = CLOCK_IP_HAS_EDMA0_TCD3_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD4_CLK)
    EDMA0_TCD4_CLK            = CLOCK_IP_HAS_EDMA0_TCD4_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD5_CLK)
    EDMA0_TCD5_CLK            = CLOCK_IP_HAS_EDMA0_TCD5_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD6_CLK)
    EDMA0_TCD6_CLK            = CLOCK_IP_HAS_EDMA0_TCD6_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD7_CLK)
    EDMA0_TCD7_CLK            = CLOCK_IP_HAS_EDMA0_TCD7_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD8_CLK)
    EDMA0_TCD8_CLK            = CLOCK_IP_HAS_EDMA0_TCD8_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD9_CLK)
    EDMA0_TCD9_CLK            = CLOCK_IP_HAS_EDMA0_TCD9_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD10_CLK)
    EDMA0_TCD10_CLK           = CLOCK_IP_HAS_EDMA0_TCD10_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD11_CLK)
    EDMA0_TCD11_CLK           = CLOCK_IP_HAS_EDMA0_TCD11_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
    EDMA0_TCD12_CLK           = CLOCK_IP_HAS_EDMA0_TCD12_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
    EDMA0_TCD13_CLK           = CLOCK_IP_HAS_EDMA0_TCD13_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
    EDMA0_TCD14_CLK           = CLOCK_IP_HAS_EDMA0_TCD14_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
    EDMA0_TCD15_CLK           = CLOCK_IP_HAS_EDMA0_TCD15_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
    EDMA0_TCD16_CLK           = CLOCK_IP_HAS_EDMA0_TCD16_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
    EDMA0_TCD17_CLK           = CLOCK_IP_HAS_EDMA0_TCD17_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
    EDMA0_TCD18_CLK           = CLOCK_IP_HAS_EDMA0_TCD18_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
    EDMA0_TCD19_CLK           = CLOCK_IP_HAS_EDMA0_TCD19_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
    EDMA0_TCD20_CLK           = CLOCK_IP_HAS_EDMA0_TCD20_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
    EDMA0_TCD21_CLK           = CLOCK_IP_HAS_EDMA0_TCD21_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
    EDMA0_TCD22_CLK           = CLOCK_IP_HAS_EDMA0_TCD22_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
    EDMA0_TCD23_CLK           = CLOCK_IP_HAS_EDMA0_TCD23_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
    EDMA0_TCD24_CLK           = CLOCK_IP_HAS_EDMA0_TCD24_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
    EDMA0_TCD25_CLK           = CLOCK_IP_HAS_EDMA0_TCD25_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
    EDMA0_TCD26_CLK           = CLOCK_IP_HAS_EDMA0_TCD26_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
    EDMA0_TCD27_CLK           = CLOCK_IP_HAS_EDMA0_TCD27_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
    EDMA0_TCD28_CLK           = CLOCK_IP_HAS_EDMA0_TCD28_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
    EDMA0_TCD29_CLK           = CLOCK_IP_HAS_EDMA0_TCD29_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
    EDMA0_TCD30_CLK           = CLOCK_IP_HAS_EDMA0_TCD30_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
    EDMA0_TCD31_CLK           = CLOCK_IP_HAS_EDMA0_TCD31_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
    EDMA1_CLK                 = CLOCK_IP_HAS_EDMA1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
    EDMA1_TCD0_CLK            = CLOCK_IP_HAS_EDMA1_TCD0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
    EDMA1_TCD1_CLK            = CLOCK_IP_HAS_EDMA1_TCD1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
    EDMA1_TCD2_CLK            = CLOCK_IP_HAS_EDMA1_TCD2_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
    EDMA1_TCD3_CLK            = CLOCK_IP_HAS_EDMA1_TCD3_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
    EDMA1_TCD4_CLK            = CLOCK_IP_HAS_EDMA1_TCD4_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
    EDMA1_TCD5_CLK            = CLOCK_IP_HAS_EDMA1_TCD5_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
    EDMA1_TCD6_CLK            = CLOCK_IP_HAS_EDMA1_TCD6_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
    EDMA1_TCD7_CLK            = CLOCK_IP_HAS_EDMA1_TCD7_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
    EDMA1_TCD8_CLK            = CLOCK_IP_HAS_EDMA1_TCD8_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
    EDMA1_TCD9_CLK            = CLOCK_IP_HAS_EDMA1_TCD9_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
    EDMA1_TCD10_CLK           = CLOCK_IP_HAS_EDMA1_TCD10_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
    EDMA1_TCD11_CLK           = CLOCK_IP_HAS_EDMA1_TCD11_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
    EDMA1_TCD12_CLK           = CLOCK_IP_HAS_EDMA1_TCD12_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
    EDMA1_TCD13_CLK           = CLOCK_IP_HAS_EDMA1_TCD13_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
    EDMA1_TCD14_CLK           = CLOCK_IP_HAS_EDMA1_TCD14_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
    EDMA1_TCD15_CLK           = CLOCK_IP_HAS_EDMA1_TCD15_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
    EDMA1_TCD16_CLK           = CLOCK_IP_HAS_EDMA1_TCD16_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
    EDMA1_TCD17_CLK           = CLOCK_IP_HAS_EDMA1_TCD17_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
    EDMA1_TCD18_CLK           = CLOCK_IP_HAS_EDMA1_TCD18_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
    EDMA1_TCD19_CLK           = CLOCK_IP_HAS_EDMA1_TCD19_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
    EDMA1_TCD20_CLK           = CLOCK_IP_HAS_EDMA1_TCD20_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
    EDMA1_TCD21_CLK           = CLOCK_IP_HAS_EDMA1_TCD21_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
    EDMA1_TCD22_CLK           = CLOCK_IP_HAS_EDMA1_TCD22_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
    EDMA1_TCD23_CLK           = CLOCK_IP_HAS_EDMA1_TCD23_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
    EDMA1_TCD24_CLK           = CLOCK_IP_HAS_EDMA1_TCD24_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
    EDMA1_TCD25_CLK           = CLOCK_IP_HAS_EDMA1_TCD25_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
    EDMA1_TCD26_CLK           = CLOCK_IP_HAS_EDMA1_TCD26_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
    EDMA1_TCD27_CLK           = CLOCK_IP_HAS_EDMA1_TCD27_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
    EDMA1_TCD28_CLK           = CLOCK_IP_HAS_EDMA1_TCD28_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
    EDMA1_TCD29_CLK           = CLOCK_IP_HAS_EDMA1_TCD29_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
    EDMA1_TCD30_CLK           = CLOCK_IP_HAS_EDMA1_TCD30_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
    EDMA1_TCD31_CLK           = CLOCK_IP_HAS_EDMA1_TCD31_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA3_CLK)
    EDMA3_CLK                 = CLOCK_IP_HAS_EDMA3_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA4_CLK)
    EDMA4_CLK                 = CLOCK_IP_HAS_EDMA4_CLK,
#endif
#if defined(CLOCK_IP_HAS_EDMA5_CLK)
    EDMA5_CLK                 = CLOCK_IP_HAS_EDMA5_CLK,
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
    EFLEX_PWM0_CLK                 = CLOCK_IP_HAS_EFLEX_PWM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
    EFLEX_PWM1_CLK                 = CLOCK_IP_HAS_EFLEX_PWM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FDMA0_CLK)
    FDMA0_CLK                 = CLOCK_IP_HAS_FDMA0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ENET_CLK)
    ENET_CLK                  = CLOCK_IP_HAS_ENET_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
    EIM_CLK                   = CLOCK_IP_HAS_EIM_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
    EIM0_CLK                  = CLOCK_IP_HAS_EIM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
    EIM1_CLK                  = CLOCK_IP_HAS_EIM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
    EIM2_CLK                  = CLOCK_IP_HAS_EIM2_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
    EIM3_CLK                  = CLOCK_IP_HAS_EIM3_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_BBE32DSP_CLK)
    EIM_BBE32DSP_CLK          = CLOCK_IP_HAS_EIM_BBE32DSP_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_LAX0_CLK)
    EIM_LAX0_CLK              = CLOCK_IP_HAS_EIM_LAX0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_LAX1_CLK)
    EIM_LAX1_CLK              = CLOCK_IP_HAS_EIM_LAX1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_PER1_CLK)
    EIM_PER1_CLK              = CLOCK_IP_HAS_EIM_PER1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ENET0_CLK)
    ENET0_CLK                 = CLOCK_IP_HAS_ENET0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ENET1_CLK)
    ENET1_CLK                 = CLOCK_IP_HAS_ENET1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
    EMAC_RX_CLK               = CLOCK_IP_HAS_EMAC_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
    EMAC_TS_CLK               = CLOCK_IP_HAS_EMAC_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
    EMAC_TX_CLK               = CLOCK_IP_HAS_EMAC_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
    EMAC_TX_RMII_CLK               = CLOCK_IP_HAS_EMAC_TX_RMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
    EMAC0_RX_CLK              = CLOCK_IP_HAS_EMAC0_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
    EMAC0_TS_CLK              = CLOCK_IP_HAS_EMAC0_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
    EMAC0_TX_CLK              = CLOCK_IP_HAS_EMAC0_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMIOS0_CLK)
    EMIOS0_CLK                = CLOCK_IP_HAS_EMIOS0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
    EMIOS1_CLK                = CLOCK_IP_HAS_EMIOS1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
    EMIOS2_CLK                = CLOCK_IP_HAS_EMIOS2_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM0_CLK)
    ERM0_CLK                  = CLOCK_IP_HAS_ERM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM1_CLK)
    ERM1_CLK                  = CLOCK_IP_HAS_ERM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_CPU0_CLK)
    ERM_CPU0_CLK              = CLOCK_IP_HAS_ERM_CPU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_CPU1_CLK)
    ERM_CPU1_CLK              = CLOCK_IP_HAS_ERM_CPU1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_CPU2_CLK)
    ERM_CPU2_CLK              = CLOCK_IP_HAS_ERM_CPU2_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_EDMA0_CLK)
    ERM_EDMA0_CLK             = CLOCK_IP_HAS_ERM_EDMA0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_EDMA1_CLK)
    ERM_EDMA1_CLK             = CLOCK_IP_HAS_ERM_EDMA1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_LAX0_CLK)
    ERM_LAX0_CLK              = CLOCK_IP_HAS_ERM_LAX0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_LAX1_CLK)
    ERM_LAX1_CLK              = CLOCK_IP_HAS_ERM_LAX1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_PER_CLK)
    ERM_PER_CLK               = CLOCK_IP_HAS_ERM_PER_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_PER1_CLK)
    ERM_PER1_CLK              = CLOCK_IP_HAS_ERM_PER1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_CLK)
    ERM_CLK                   = CLOCK_IP_HAS_ERM_CLK,
#endif
#if defined(CLOCK_IP_HAS_EWM0_CLK)
    EWM0_CLK                  = CLOCK_IP_HAS_EWM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_MON1_CLK)
    FIRC_MON1_CLK             = CLOCK_IP_HAS_FIRC_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FIRC_MON2_CLK)
    FIRC_MON2_CLK             = CLOCK_IP_HAS_FIRC_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
    FLASH0_CLK                = CLOCK_IP_HAS_FLASH0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CAN_PE_CLK)
    CAN_PE_CLK                = CLOCK_IP_HAS_CAN_PE_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN_CLK)
    FLEXCAN_CLK               = CLOCK_IP_HAS_FLEXCAN_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN0_CLK)
    FLEXCAN0_CLK              = CLOCK_IP_HAS_FLEXCAN0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN1_CLK)
    FLEXCAN1_CLK              = CLOCK_IP_HAS_FLEXCAN1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN2_CLK)
    FLEXCAN2_CLK              = CLOCK_IP_HAS_FLEXCAN2_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
    FLEXCAN3_CLK              = CLOCK_IP_HAS_FLEXCAN3_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
    FLEXCAN4_CLK              = CLOCK_IP_HAS_FLEXCAN4_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
    FLEXCAN5_CLK              = CLOCK_IP_HAS_FLEXCAN5_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
    FLEXCAN6_CLK              = CLOCK_IP_HAS_FLEXCAN6_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
    FLEXCAN7_CLK              = CLOCK_IP_HAS_FLEXCAN7_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN8_CLK)
    FLEXCAN8_CLK              = CLOCK_IP_HAS_FLEXCAN8_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN9_CLK)
    FLEXCAN9_CLK              = CLOCK_IP_HAS_FLEXCAN9_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN10_CLK)
    FLEXCAN10_CLK             = CLOCK_IP_HAS_FLEXCAN10_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN11_CLK)
    FLEXCAN11_CLK             = CLOCK_IP_HAS_FLEXCAN11_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN12_CLK)
    FLEXCAN12_CLK             = CLOCK_IP_HAS_FLEXCAN12_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN13_CLK)
    FLEXCAN13_CLK             = CLOCK_IP_HAS_FLEXCAN13_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN14_CLK)
    FLEXCAN14_CLK             = CLOCK_IP_HAS_FLEXCAN14_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN15_CLK)
    FLEXCAN15_CLK             = CLOCK_IP_HAS_FLEXCAN15_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN16_CLK)
    FLEXCAN16_CLK             = CLOCK_IP_HAS_FLEXCAN16_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN17_CLK)
    FLEXCAN17_CLK             = CLOCK_IP_HAS_FLEXCAN17_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN18_CLK)
    FLEXCAN18_CLK             = CLOCK_IP_HAS_FLEXCAN18_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN19_CLK)
    FLEXCAN19_CLK             = CLOCK_IP_HAS_FLEXCAN19_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN20_CLK)
    FLEXCAN20_CLK             = CLOCK_IP_HAS_FLEXCAN20_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN21_CLK)
    FLEXCAN21_CLK             = CLOCK_IP_HAS_FLEXCAN21_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN22_CLK)
    FLEXCAN22_CLK             = CLOCK_IP_HAS_FLEXCAN22_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN23_CLK)
    FLEXCAN23_CLK             = CLOCK_IP_HAS_FLEXCAN23_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCANA_CLK)
    FLEXCANA_CLK              = CLOCK_IP_HAS_FLEXCANA_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
    FLEXCANB_CLK              = CLOCK_IP_HAS_FLEXCANB_CLK,
#endif
#if defined(CLOCK_IP_HAS_FlexIO_CLK)
    FlexIO_CLK                = CLOCK_IP_HAS_FlexIO_CLK,
#endif
#if defined(CLOCK_IP_HAS_FlexIO0_CLK)
    FlexIO0_CLK               = CLOCK_IP_HAS_FlexIO0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXIO0_CLK)
    FLEXIO0_CLK               = CLOCK_IP_HAS_FLEXIO0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXRAY_CLK)
    FLEXRAY_CLK               = CLOCK_IP_HAS_FLEXRAY_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXTIMERA_CLK)
    FLEXTIMERA_CLK            = CLOCK_IP_HAS_FLEXTIMERA_CLK,
#endif
#if defined(CLOCK_IP_HAS_FLEXTIMERB_CLK)
    FLEXTIMERB_CLK            = CLOCK_IP_HAS_FLEXTIMERB_CLK,
#endif
#if defined(CLOCK_IP_HAS_FRAY0_CLK)
    FRAY0_CLK                 = CLOCK_IP_HAS_FRAY0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FRAY1_CLK)
    FRAY1_CLK                 = CLOCK_IP_HAS_FRAY1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTFC_CLK)
    FTFC_CLK                  = CLOCK_IP_HAS_FTFC_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTFM_CLK)
    FTFM_CLK                  = CLOCK_IP_HAS_FTFM_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTIMER0_CLK)
    FTIMER0_CLK               = CLOCK_IP_HAS_FTIMER0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTIMER1_CLK)
    FTIMER1_CLK               = CLOCK_IP_HAS_FTIMER1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM0_CLK)
    FTM0_CLK                  = CLOCK_IP_HAS_FTM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM1_CLK)
    FTM1_CLK                  = CLOCK_IP_HAS_FTM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM2_CLK)
    FTM2_CLK                  = CLOCK_IP_HAS_FTM2_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM3_CLK)
    FTM3_CLK                  = CLOCK_IP_HAS_FTM3_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM4_CLK)
    FTM4_CLK                  = CLOCK_IP_HAS_FTM4_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM5_CLK)
    FTM5_CLK                  = CLOCK_IP_HAS_FTM5_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM6_CLK)
    FTM6_CLK                  = CLOCK_IP_HAS_FTM6_CLK,
#endif
#if defined(CLOCK_IP_HAS_FTM7_CLK)
    FTM7_CLK                  = CLOCK_IP_HAS_FTM7_CLK,
#endif
#if defined(CLOCK_IP_HAS_GLB_LBIST_CLK)
    GLB_LBIST_CLK             = CLOCK_IP_HAS_GLB_LBIST_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
    GMAC0_CLK               = CLOCK_IP_HAS_GMAC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
    GMAC_TS_CLK               = CLOCK_IP_HAS_GMAC_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
    GMAC_RX_CLK               = CLOCK_IP_HAS_GMAC_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
    GMAC_TX_CLK               = CLOCK_IP_HAS_GMAC_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
    GMAC0_RX_CLK              = CLOCK_IP_HAS_GMAC0_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
    GMAC0_TX_CLK              = CLOCK_IP_HAS_GMAC0_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TS_CLK)
    GMAC0_TS_CLK              = CLOCK_IP_HAS_GMAC0_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
    GMAC0_TX_RMII_CLK         = CLOCK_IP_HAS_GMAC0_TX_RMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
    GMAC0_MII_RGMII_RX_CLK          = CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
    GMAC0_MII_RMII_RGMII_TX_CLK     = CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
    GMAC1_MII_RGMII_RX_CLK          = CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
    GMAC1_RX_CLK              = CLOCK_IP_HAS_GMAC1_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
    GMAC1_TX_CLK              = CLOCK_IP_HAS_GMAC1_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TS_CLK)
    GMAC1_TS_CLK              = CLOCK_IP_HAS_GMAC1_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
    GMAC1_RMII_CLK            = CLOCK_IP_HAS_GMAC1_RMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
    GMAC1_MII_RMII_RGMII_TX_CLK        = CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_GPIO0_CLK)
    GPIO0_CLK                 = CLOCK_IP_HAS_GPIO0_CLK,
#endif
#if defined(CLOCK_IP_HAS_GTM_CLK)
    GTM_CLK                = CLOCK_IP_HAS_GTM_CLK,
#endif
#if defined(CLOCK_IP_HAS_IDIV0_CLK)
    IDIV0_CLK                   = CLOCK_IP_HAS_IDIV0_CLK,
#endif
#if defined(CLOCK_IP_HAS_IDIV1_CLK)
    IDIV1_CLK                   = CLOCK_IP_HAS_IDIV1_CLK,
#endif
#if defined(CLOCK_IP_HAS_IDIV2_CLK)
    IDIV2_CLK                   = CLOCK_IP_HAS_IDIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_IDIV3_CLK)
    IDIV3_CLK                   = CLOCK_IP_HAS_IDIV3_CLK,
#endif
#if defined(CLOCK_IP_HAS_IDIV4_CLK)
    IDIV4_CLK                   = CLOCK_IP_HAS_IDIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
    IGF0_CLK                   = CLOCK_IP_HAS_IGF0_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIIC0_CLK)
    IIIC0_CLK                 = CLOCK_IP_HAS_IIIC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIIC1_CLK)
    IIIC1_CLK                 = CLOCK_IP_HAS_IIIC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIIC2_CLK)
    IIIC2_CLK                 = CLOCK_IP_HAS_IIIC2_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIC0_CLK)
    IIC0_CLK                  = CLOCK_IP_HAS_IIC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIC1_CLK)
    IIC1_CLK                  = CLOCK_IP_HAS_IIC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIC2_CLK)
    IIC2_CLK                  = CLOCK_IP_HAS_IIC2_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIC3_CLK)
    IIC3_CLK                  = CLOCK_IP_HAS_IIC3_CLK,
#endif
#if defined(CLOCK_IP_HAS_IIC4_CLK)
    IIC4_CLK                  = CLOCK_IP_HAS_IIC4_CLK,
#endif
#if defined(CLOCK_IP_HAS_INTM_CLK)
    INTM_CLK                  = CLOCK_IP_HAS_INTM_CLK,
#endif
#if defined(CLOCK_IP_HAS_ISO_CLK)
    ISO_CLK                  = CLOCK_IP_HAS_ISO_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST0_CLK)
    LBIST0_CLK                = CLOCK_IP_HAS_LBIST0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST1_CLK)
    LBIST1_CLK                = CLOCK_IP_HAS_LBIST1_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST2_CLK)
    LBIST2_CLK                = CLOCK_IP_HAS_LBIST2_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST3_CLK)
    LBIST3_CLK                = CLOCK_IP_HAS_LBIST3_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST4_CLK)
    LBIST4_CLK                = CLOCK_IP_HAS_LBIST4_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST5_CLK)
    LBIST5_CLK                = CLOCK_IP_HAS_LBIST5_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST6_CLK)
    LBIST6_CLK                = CLOCK_IP_HAS_LBIST6_CLK,
#endif
#if defined(CLOCK_IP_HAS_LBIST7_CLK)
    LBIST7_CLK                = CLOCK_IP_HAS_LBIST7_CLK,
#endif
#if defined(CLOCK_IP_HAS_LCU0_CLK)
    LCU0_CLK                  = CLOCK_IP_HAS_LCU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LCU1_CLK)
    LCU1_CLK                  = CLOCK_IP_HAS_LCU1_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN_BAUD_CLK)
    LIN_BAUD_CLK                   = CLOCK_IP_HAS_LIN_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_LINFLEXD_CLK)
    LINFLEXD_CLK                   = CLOCK_IP_HAS_LINFLEXD_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN0_CLK)
    LIN0_CLK                  = CLOCK_IP_HAS_LIN0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN1_CLK)
    LIN1_CLK                  = CLOCK_IP_HAS_LIN1_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN2_CLK)
    LIN2_CLK                  = CLOCK_IP_HAS_LIN2_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN3_CLK)
    LIN3_CLK                  = CLOCK_IP_HAS_LIN3_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN4_CLK)
    LIN4_CLK                  = CLOCK_IP_HAS_LIN4_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN5_CLK)
    LIN5_CLK                  = CLOCK_IP_HAS_LIN5_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN6_CLK)
    LIN6_CLK                  = CLOCK_IP_HAS_LIN6_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN7_CLK)
    LIN7_CLK                  = CLOCK_IP_HAS_LIN7_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN8_CLK)
    LIN8_CLK                  = CLOCK_IP_HAS_LIN8_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN9_CLK)
    LIN9_CLK                  = CLOCK_IP_HAS_LIN9_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN10_CLK)
    LIN10_CLK                 = CLOCK_IP_HAS_LIN10_CLK,
#endif
#if defined(CLOCK_IP_HAS_LIN11_CLK)
    LIN11_CLK                 = CLOCK_IP_HAS_LIN11_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
    LFAST_REF_CLK             = CLOCK_IP_HAS_LFAST_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
    LFAST_REF_EXT_CLK         = CLOCK_IP_HAS_LFAST_REF_EXT_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
    LPI2C0_CLK                = CLOCK_IP_HAS_LPI2C0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPI2C1_CLK)
    LPI2C1_CLK                = CLOCK_IP_HAS_LPI2C1_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPIT0_CLK)
    LPIT0_CLK                 = CLOCK_IP_HAS_LPIT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI_CLK)
    LPSPI_CLK                = CLOCK_IP_HAS_LPSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI0_CLK)
    LPSPI0_CLK                = CLOCK_IP_HAS_LPSPI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI1_CLK)
    LPSPI1_CLK                = CLOCK_IP_HAS_LPSPI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI2_CLK)
    LPSPI2_CLK                = CLOCK_IP_HAS_LPSPI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI3_CLK)
    LPSPI3_CLK                = CLOCK_IP_HAS_LPSPI3_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
    LPSPI4_CLK                = CLOCK_IP_HAS_LPSPI4_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
    LPSPI5_CLK                = CLOCK_IP_HAS_LPSPI5_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPTMR0_CLK)
    LPTMR0_CLK                = CLOCK_IP_HAS_LPTMR0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART0_CLK)
    LPUART0_CLK               = CLOCK_IP_HAS_LPUART0_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART1_CLK)
    LPUART1_CLK               = CLOCK_IP_HAS_LPUART1_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART2_CLK)
    LPUART2_CLK               = CLOCK_IP_HAS_LPUART2_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART3_CLK)
    LPUART3_CLK               = CLOCK_IP_HAS_LPUART3_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
    LPUART4_CLK               = CLOCK_IP_HAS_LPUART4_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
    LPUART5_CLK               = CLOCK_IP_HAS_LPUART5_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
    LPUART6_CLK               = CLOCK_IP_HAS_LPUART6_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
    LPUART7_CLK               = CLOCK_IP_HAS_LPUART7_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
    LPUART8_CLK               = CLOCK_IP_HAS_LPUART8_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
    LPUART9_CLK               = CLOCK_IP_HAS_LPUART9_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
    LPUART10_CLK              = CLOCK_IP_HAS_LPUART10_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
    LPUART11_CLK              = CLOCK_IP_HAS_LPUART11_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
    LPUART12_CLK              = CLOCK_IP_HAS_LPUART12_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
    LPUART13_CLK              = CLOCK_IP_HAS_LPUART13_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
    LPUART14_CLK              = CLOCK_IP_HAS_LPUART14_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
    LPUART15_CLK              = CLOCK_IP_HAS_LPUART15_CLK,
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
    LPUART_MSC_CLK              = CLOCK_IP_HAS_LPUART_MSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_LVDS_CLK)
    LVDS_CLK              = CLOCK_IP_HAS_LVDS_CLK,
#endif
#if defined(CLOCK_IP_HAS_MCSS_CLK)
    MCSS_CLK                  = CLOCK_IP_HAS_MCSS_CLK,
#endif
#if defined(CLOCK_IP_HAS_MPU0_CLK)
    MPU0_CLK                  = CLOCK_IP_HAS_MPU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_MSCM_CLK)
    MSCM_CLK                  = CLOCK_IP_HAS_MSCM_CLK,
#endif
#if defined(CLOCK_IP_HAS_MSCM0_CLK)
    MSCM0_CLK                 = CLOCK_IP_HAS_MSCM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_MUA_CLK)
    MUA_CLK                   = CLOCK_IP_HAS_MUA_CLK,
#endif
#if defined(CLOCK_IP_HAS_MUB_CLK)
    MUB_CLK                   = CLOCK_IP_HAS_MUB_CLK,
#endif
#if defined(CLOCK_IP_HAS_MU2A_CLK)
    MU2A_CLK                   = CLOCK_IP_HAS_MU2A_CLK,
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
    MU2B_CLK                   = CLOCK_IP_HAS_MU2B_CLK,
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
    MU3A_CLK                   = CLOCK_IP_HAS_MU3A_CLK,
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
    MU3B_CLK                   = CLOCK_IP_HAS_MU3B_CLK,
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
    MU4A_CLK                   = CLOCK_IP_HAS_MU4A_CLK,
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
    MU4B_CLK                   = CLOCK_IP_HAS_MU4B_CLK,
#endif
#if defined(CLOCK_IP_HAS_OCOTP_CLK)
    OCOTP_CLK                = CLOCK_IP_HAS_OCOTP_CLK,
#endif
#if defined(CLOCK_IP_HAS_PDB0_CLK)
    PDB0_CLK                  = CLOCK_IP_HAS_PDB0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PDB1_CLK)
    PDB1_CLK                  = CLOCK_IP_HAS_PDB1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC0_RX_CLK)
    PFEMAC0_RX_CLK            = CLOCK_IP_HAS_PFEMAC0_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC0_TX_DIV_CLK)
    PFEMAC0_TX_DIV_CLK            = CLOCK_IP_HAS_PFEMAC0_TX_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC1_TX_DIV_CLK)
    PFEMAC1_TX_DIV_CLK            = CLOCK_IP_HAS_PFEMAC1_TX_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC2_TX_DIV_CLK)
    PFEMAC2_TX_DIV_CLK            = CLOCK_IP_HAS_PFEMAC2_TX_DIV_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC0_TX_CLK)
    PFEMAC0_TX_CLK            = CLOCK_IP_HAS_PFEMAC0_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC1_RX_CLK)
    PFEMAC1_RX_CLK            = CLOCK_IP_HAS_PFEMAC1_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC1_TX_CLK)
    PFEMAC1_TX_CLK            = CLOCK_IP_HAS_PFEMAC1_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC2_RX_CLK)
    PFEMAC2_RX_CLK            = CLOCK_IP_HAS_PFEMAC2_RX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PFEMAC2_TX_CLK)
    PFEMAC2_TX_CLK            = CLOCK_IP_HAS_PFEMAC2_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_PIT0_CLK)
    PIT0_CLK                  = CLOCK_IP_HAS_PIT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PIT1_CLK)
    PIT1_CLK                  = CLOCK_IP_HAS_PIT1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PIT2_CLK)
    PIT2_CLK                  = CLOCK_IP_HAS_PIT2_CLK,
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
    PIT3_CLK                  = CLOCK_IP_HAS_PIT3_CLK,
#endif
#if defined(CLOCK_IP_HAS_PIT4_CLK)
    PIT4_CLK                  = CLOCK_IP_HAS_PIT4_CLK,
#endif
#if defined(CLOCK_IP_HAS_PIT5_CLK)
    PIT5_CLK                  = CLOCK_IP_HAS_PIT5_CLK,
#endif
#if defined(CLOCK_IP_HAS_PORTA_CLK)
    PORTA_CLK                 = CLOCK_IP_HAS_PORTA_CLK,
#endif
#if defined(CLOCK_IP_HAS_PORTB_CLK)
    PORTB_CLK                 = CLOCK_IP_HAS_PORTB_CLK,
#endif
#if defined(CLOCK_IP_HAS_PORTC_CLK)
    PORTC_CLK                 = CLOCK_IP_HAS_PORTC_CLK,
#endif
#if defined(CLOCK_IP_HAS_PORTD_CLK)
    PORTD_CLK                 = CLOCK_IP_HAS_PORTD_CLK,
#endif
#if defined(CLOCK_IP_HAS_PORTE_CLK)
    PORTE_CLK                 = CLOCK_IP_HAS_PORTE_CLK,
#endif
#if defined(CLOCK_IP_HAS_PSI5_0_CLK)
    PSI5_0_CLK                = CLOCK_IP_HAS_PSI5_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PSI5_1_CLK)
    PSI5_1_CLK                = CLOCK_IP_HAS_PSI5_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_PSI5S_0_CLK)
    PSI5S_0_CLK               = CLOCK_IP_HAS_PSI5S_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_PSI5S_1_CLK)
    PSI5S_1_CLK               = CLOCK_IP_HAS_PSI5S_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_CLK)
    QSPI_CLK             = CLOCK_IP_HAS_QSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFIF_CLK_HYP_PREMUX_CLK)
    QSPI_SFIF_CLK_HYP_PREMUX_CLK = CLOCK_IP_HAS_QSPI_SFIF_CLK_HYP_PREMUX_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFIF_CLK)
    QSPI_SFIF_CLK             = CLOCK_IP_HAS_QSPI_SFIF_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_2xSFIF_CLK)
    QSPI_2xSFIF_CLK           = CLOCK_IP_HAS_QSPI_2xSFIF_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
    QSPI_2XSFIF_CLK           = CLOCK_IP_HAS_QSPI_2XSFIF_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_2X_CLK)
    QSPI_2X_CLK                  = CLOCK_IP_HAS_QSPI_2X_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_1X_CLK)
    QSPI_1X_CLK                  = CLOCK_IP_HAS_QSPI_1X_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
    QSPI_SFCK_CLK             = CLOCK_IP_HAS_QSPI_SFCK_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
    QSPI0_CLK                 = CLOCK_IP_HAS_QSPI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
    QSPI0_RAM_CLK             = CLOCK_IP_HAS_QSPI0_RAM_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)
    QSPI0_SFCK_CLK            = CLOCK_IP_HAS_QSPI0_SFCK_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
    QSPI0_TX_MEM_CLK          = CLOCK_IP_HAS_QSPI0_TX_MEM_CLK,
#endif
#if defined(CLOCK_IP_HAS_QSPI1_CLK)
    QSPI1_CLK                 = CLOCK_IP_HAS_QSPI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_CLKOUT_SRC_CLK)
    P0_CLKOUT_SRC_CLK         = CLOCK_IP_HAS_P0_CLKOUT_SRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_CTU_PER_CLK)
    P0_CTU_PER_CLK            = CLOCK_IP_HAS_P0_CTU_PER_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_DSPI_CLK)
    P0_DSPI_CLK               = CLOCK_IP_HAS_P0_DSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_DSPI_MSC_CLK)
    P0_DSPI_MSC_CLK           = CLOCK_IP_HAS_P0_DSPI_MSC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_EMIOS_LCU_CLK)
    P0_EMIOS_LCU_CLK          = CLOCK_IP_HAS_P0_EMIOS_LCU_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_FR_PE_CLK)
    P0_FR_PE_CLK              = CLOCK_IP_HAS_P0_FR_PE_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_GTM_CLK)
    P0_GTM_CLK                = CLOCK_IP_HAS_P0_GTM_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_GTM_NOC_CLK)
    P0_GTM_NOC_CLK            = CLOCK_IP_HAS_P0_GTM_NOC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_GTM_TS_CLK)
    P0_GTM_TS_CLK             = CLOCK_IP_HAS_P0_GTM_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_LIN_BAUD_CLK)
    P0_LIN_BAUD_CLK           = CLOCK_IP_HAS_P0_LIN_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_LIN_CLK)
    P0_LIN_CLK                = CLOCK_IP_HAS_P0_LIN_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_NANO_CLK)
    P0_NANO_CLK               = CLOCK_IP_HAS_P0_NANO_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_125K_CLK)
    P0_PSI5_125K_CLK          = CLOCK_IP_HAS_P0_PSI5_125K_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_189K_CLK)
    P0_PSI5_189K_CLK          = CLOCK_IP_HAS_P0_PSI5_189K_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_1US_CLK)
    P0_PSI5_1US_CLK           = CLOCK_IP_HAS_P0_PSI5_1US_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_BAUD_CLK)
    P0_PSI5_S_BAUD_CLK        = CLOCK_IP_HAS_P0_PSI5_S_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_CORE_CLK)
    P0_PSI5_S_CORE_CLK        = CLOCK_IP_HAS_P0_PSI5_S_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_TRIG0_CLK)
    P0_PSI5_S_TRIG0_CLK       = CLOCK_IP_HAS_P0_PSI5_S_TRIG0_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_TRIG1_CLK)
    P0_PSI5_S_TRIG1_CLK       = CLOCK_IP_HAS_P0_PSI5_S_TRIG1_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_TRIG2_CLK)
    P0_PSI5_S_TRIG2_CLK       = CLOCK_IP_HAS_P0_PSI5_S_TRIG2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_TRIG3_CLK)
    P0_PSI5_S_TRIG3_CLK       = CLOCK_IP_HAS_P0_PSI5_S_TRIG3_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_UART_CLK)
    P0_PSI5_S_UART_CLK        = CLOCK_IP_HAS_P0_PSI5_S_UART_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_WDOG0_CLK)
    P0_PSI5_S_WDOG0_CLK       = CLOCK_IP_HAS_P0_PSI5_S_WDOG0_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_WDOG1_CLK)
    P0_PSI5_S_WDOG1_CLK       = CLOCK_IP_HAS_P0_PSI5_S_WDOG1_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_WDOG2_CLK)
    P0_PSI5_S_WDOG2_CLK       = CLOCK_IP_HAS_P0_PSI5_S_WDOG2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_PSI5_S_WDOG3_CLK)
    P0_PSI5_S_WDOG3_CLK       = CLOCK_IP_HAS_P0_PSI5_S_WDOG3_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_REG_INTF_2X_CLK)
    P0_REG_INTF_2X_CLK        = CLOCK_IP_HAS_P0_REG_INTF_2X_CLK,
#endif
#if defined(CLOCK_IP_HAS_P0_REG_INTF_CLK)
    P0_REG_INTF_CLK           = CLOCK_IP_HAS_P0_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_CLKOUT_SRC_CLK)
    P1_CLKOUT_SRC_CLK         = CLOCK_IP_HAS_P1_CLKOUT_SRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_DSPI_CLK)
    P1_DSPI_CLK               = CLOCK_IP_HAS_P1_DSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_DSPI60_CLK)
    P1_DSPI60_CLK             = CLOCK_IP_HAS_P1_DSPI60_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_LFAST0_REF_CLK)
    P1_LFAST0_REF_CLK         = CLOCK_IP_HAS_P1_LFAST0_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_LFAST1_REF_CLK)
    P1_LFAST1_REF_CLK         = CLOCK_IP_HAS_P1_LFAST1_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_LFAST_DFT_CLK)
    P1_LFAST_DFT_CLK          = CLOCK_IP_HAS_P1_LFAST_DFT_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_NETC_AXI_CLK)
    P1_NETC_AXI_CLK           = CLOCK_IP_HAS_P1_NETC_AXI_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_LIN_BAUD_CLK)
    P1_LIN_BAUD_CLK           = CLOCK_IP_HAS_P1_LIN_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_LIN_CLK)
    P1_LIN_CLK                = CLOCK_IP_HAS_P1_LIN_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH_TS_CLK)
    ETH_TS_CLK                = CLOCK_IP_HAS_ETH_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH_TS_DIV4_CLK)
    ETH_TS_DIV4_CLK           = CLOCK_IP_HAS_ETH_TS_DIV4_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_REF_RMII_CLK)
    ETH0_REF_RMII_CLK         = CLOCK_IP_HAS_ETH0_REF_RMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_RX_MII_CLK)
    ETH0_RX_MII_CLK           = CLOCK_IP_HAS_ETH0_RX_MII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_RX_RGMII_CLK)
    ETH0_RX_RGMII_CLK         = CLOCK_IP_HAS_ETH0_RX_RGMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_TX_MII_CLK)
    ETH0_TX_MII_CLK           = CLOCK_IP_HAS_ETH0_TX_MII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_TX_RGMII_CLK)
    ETH0_TX_RGMII_CLK         = CLOCK_IP_HAS_ETH0_TX_RGMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_TX_RGMII_LPBK_CLK)
    ETH0_TX_RGMII_LPBK_CLK    = CLOCK_IP_HAS_ETH0_TX_RGMII_LPBK_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH0_PS_TX_CLK)
    ETH0_PS_TX_CLK            = CLOCK_IP_HAS_ETH0_PS_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_REF_RMII_CLK)
    ETH1_REF_RMII_CLK         = CLOCK_IP_HAS_ETH1_REF_RMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_RX_MII_CLK)
    ETH1_RX_MII_CLK           = CLOCK_IP_HAS_ETH1_RX_MII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_RX_RGMII_CLK)
    ETH1_RX_RGMII_CLK         = CLOCK_IP_HAS_ETH1_RX_RGMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_TX_MII_CLK)
    ETH1_TX_MII_CLK           = CLOCK_IP_HAS_ETH1_TX_MII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_TX_RGMII_CLK)
    ETH1_TX_RGMII_CLK         = CLOCK_IP_HAS_ETH1_TX_RGMII_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_TX_RGMII_LPBK_CLK)
    ETH1_TX_RGMII_LPBK_CLK    = CLOCK_IP_HAS_ETH1_TX_RGMII_LPBK_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETH1_PS_TX_CLK)
    ETH1_PS_TX_CLK            = CLOCK_IP_HAS_ETH1_PS_TX_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
    ETPU_AB_REGISTERS_CLK    = CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
    ETPU_CODE_RAM1_CLK    = CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
    ETPU_CODE_RAM2_CLK    = CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
    ETPU_RAM_MIRROR_CLK    = CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK,
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
    ETPU_RAM_SDM_CLK    = CLOCK_IP_HAS_ETPU_RAM_SDM_CLK,
#endif
#if defined(CLOCK_IP_HAS_P1_REG_INTF_CLK)
    P1_REG_INTF_CLK           = CLOCK_IP_HAS_P1_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_DBG_ATB_CLK)
    P2_DBG_ATB_CLK            = CLOCK_IP_HAS_P2_DBG_ATB_CLK,
#endif
#if defined(CLOCK_IP_HAS_P2_REG_INTF_CLK)
    P2_REG_INTF_CLK           = CLOCK_IP_HAS_P2_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_AES_CLK)
    P3_AES_CLK                = CLOCK_IP_HAS_P3_AES_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_CAN_PE_CLK)
    P3_CAN_PE_CLK             = CLOCK_IP_HAS_P3_CAN_PE_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_CLKOUT_SRC_CLK)
    P3_CLKOUT_SRC_CLK         = CLOCK_IP_HAS_P3_CLKOUT_SRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_DBG_TS_CLK)
    P3_DBG_TS_CLK             = CLOCK_IP_HAS_P3_DBG_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_REG_INTF_CLK)
    P3_REG_INTF_CLK           = CLOCK_IP_HAS_P3_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_SYS_MON1_CLK)
    P3_SYS_MON1_CLK           = CLOCK_IP_HAS_P3_SYS_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_SYS_MON2_CLK)
    P3_SYS_MON2_CLK           = CLOCK_IP_HAS_P3_SYS_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P3_SYS_MON3_CLK)
    P3_SYS_MON3_CLK           = CLOCK_IP_HAS_P3_SYS_MON3_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_CLKOUT_SRC_CLK)
    P4_CLKOUT_SRC_CLK         = CLOCK_IP_HAS_P4_CLKOUT_SRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_DSPI_CLK)
    P4_DSPI_CLK               = CLOCK_IP_HAS_P4_DSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_DSPI60_CLK)
    P4_DSPI60_CLK             = CLOCK_IP_HAS_P4_DSPI60_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_EMIOS_LCU_CLK)
    P4_EMIOS_LCU_CLK          = CLOCK_IP_HAS_P4_EMIOS_LCU_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_LIN_BAUD_CLK)
    P4_LIN_BAUD_CLK           = CLOCK_IP_HAS_P4_LIN_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_LIN_CLK)
    P4_LIN_CLK                = CLOCK_IP_HAS_P4_LIN_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_125K_CLK)
    P4_PSI5_125K_CLK          = CLOCK_IP_HAS_P4_PSI5_125K_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_189K_CLK)
    P4_PSI5_189K_CLK          = CLOCK_IP_HAS_P4_PSI5_189K_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_1US_CLK)
    P4_PSI5_1US_CLK           = CLOCK_IP_HAS_P4_PSI5_1US_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_BAUD_CLK)
    P4_PSI5_S_BAUD_CLK        = CLOCK_IP_HAS_P4_PSI5_S_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_CORE_CLK)
    P4_PSI5_S_CORE_CLK        = CLOCK_IP_HAS_P4_PSI5_S_CORE_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_TRIG0_CLK)
    P4_PSI5_S_TRIG0_CLK       = CLOCK_IP_HAS_P4_PSI5_S_TRIG0_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_TRIG1_CLK)
    P4_PSI5_S_TRIG1_CLK       = CLOCK_IP_HAS_P4_PSI5_S_TRIG1_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_TRIG2_CLK)
    P4_PSI5_S_TRIG2_CLK       = CLOCK_IP_HAS_P4_PSI5_S_TRIG2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_TRIG3_CLK)
    P4_PSI5_S_TRIG3_CLK       = CLOCK_IP_HAS_P4_PSI5_S_TRIG3_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_UART_CLK)
    P4_PSI5_S_UART_CLK        = CLOCK_IP_HAS_P4_PSI5_S_UART_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_WDOG0_CLK)
    P4_PSI5_S_WDOG0_CLK       = CLOCK_IP_HAS_P4_PSI5_S_WDOG0_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_WDOG1_CLK)
    P4_PSI5_S_WDOG1_CLK       = CLOCK_IP_HAS_P4_PSI5_S_WDOG1_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_WDOG2_CLK)
    P4_PSI5_S_WDOG2_CLK       = CLOCK_IP_HAS_P4_PSI5_S_WDOG2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_PSI5_S_WDOG3_CLK)
    P4_PSI5_S_WDOG3_CLK       = CLOCK_IP_HAS_P4_PSI5_S_WDOG3_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_QSPI0_2X_CLK)
    P4_QSPI0_2X_CLK           = CLOCK_IP_HAS_P4_QSPI0_2X_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_QSPI0_1X_CLK)
    P4_QSPI0_1X_CLK           = CLOCK_IP_HAS_P4_QSPI0_1X_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_QSPI1_2X_CLK)
    P4_QSPI1_2X_CLK           = CLOCK_IP_HAS_P4_QSPI1_2X_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_QSPI1_1X_CLK)
    P4_QSPI1_1X_CLK           = CLOCK_IP_HAS_P4_QSPI1_1X_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_REG_INTF_2X_CLK)
    P4_REG_INTF_2X_CLK        = CLOCK_IP_HAS_P4_REG_INTF_2X_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_REG_INTF_CLK)
    P4_REG_INTF_CLK           = CLOCK_IP_HAS_P4_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_SDHC_CLK)
    P4_SDHC_CLK               = CLOCK_IP_HAS_P4_SDHC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_SDHC_IP_CLK)
    P4_SDHC_IP_CLK            = CLOCK_IP_HAS_P4_SDHC_IP_CLK,
#endif
#if defined(CLOCK_IP_HAS_P4_SDHC_IP_DIV2_CLK)
    P4_SDHC_IP_DIV2_CLK       = CLOCK_IP_HAS_P4_SDHC_IP_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_AE_CLK)
    P5_AE_CLK           = CLOCK_IP_HAS_P5_AE_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_CANXL_PE_CLK)
    P5_CANXL_PE_CLK           = CLOCK_IP_HAS_P5_CANXL_PE_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_CANXL_CHI_CLK)
    P5_CANXL_CHI_CLK           = CLOCK_IP_HAS_P5_CANXL_CHI_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_CLKOUT_SRC_CLK)
    P5_CLKOUT_SRC_CLK         = CLOCK_IP_HAS_P5_CLKOUT_SRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_DSPI_CLK)
    P5_DSPI_CLK               = CLOCK_IP_HAS_P5_DSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_DIPORT_CLK)
    P5_DIPORT_CLK               = CLOCK_IP_HAS_P5_DIPORT_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_LIN_BAUD_CLK)
    P5_LIN_BAUD_CLK           = CLOCK_IP_HAS_P5_LIN_BAUD_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_LIN_CLK)
    P5_LIN_CLK                = CLOCK_IP_HAS_P5_LIN_CLK,
#endif
#if defined(CLOCK_IP_HAS_P5_REG_INTF_CLK)
    P5_REG_INTF_CLK           = CLOCK_IP_HAS_P5_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_P6_REG_INTF_CLK)
    P6_REG_INTF_CLK           = CLOCK_IP_HAS_P6_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_REG_INTF_CLK)
    RTU0_REG_INTF_CLK         = CLOCK_IP_HAS_RTU0_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_MON1_CLK)
    RTU0_CORE_MON1_CLK        = CLOCK_IP_HAS_RTU0_CORE_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_MON2_CLK)
    RTU0_CORE_MON2_CLK        = CLOCK_IP_HAS_RTU0_CORE_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_DIV2_MON1_CLK)
    RTU0_CORE_DIV2_MON1_CLK   = CLOCK_IP_HAS_RTU0_CORE_DIV2_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_DIV2_MON2_CLK)
    RTU0_CORE_DIV2_MON2_CLK   = CLOCK_IP_HAS_RTU0_CORE_DIV2_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU0_CORE_DIV2_MON3_CLK)
    RTU0_CORE_DIV2_MON3_CLK   = CLOCK_IP_HAS_RTU0_CORE_DIV2_MON3_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_REG_INTF_CLK)
    RTU1_REG_INTF_CLK         = CLOCK_IP_HAS_RTU1_REG_INTF_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_MON1_CLK)
    RTU1_CORE_MON1_CLK        = CLOCK_IP_HAS_RTU1_CORE_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_MON2_CLK)
    RTU1_CORE_MON2_CLK        = CLOCK_IP_HAS_RTU1_CORE_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_DIV2_MON1_CLK)
    RTU1_CORE_DIV2_MON1_CLK   = CLOCK_IP_HAS_RTU1_CORE_DIV2_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_DIV2_MON2_CLK)
    RTU1_CORE_DIV2_MON2_CLK   = CLOCK_IP_HAS_RTU1_CORE_DIV2_MON2_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_DIV2_MON3_CLK)
    RTU1_CORE_DIV2_MON3_CLK   = CLOCK_IP_HAS_RTU1_CORE_DIV2_MON3_CLK,
#endif
#if defined(CLOCK_IP_HAS_RFE_PLL_CLK)
    RFE_PLL_CLK                   = CLOCK_IP_HAS_RFE_PLL_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTC_CLK)
    RTC_CLK                   = CLOCK_IP_HAS_RTC_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTC0_CLK)
    RTC0_CLK                  = CLOCK_IP_HAS_RTC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_RTC_EXT_REF_CLK)
    RTC_EXT_REF_CLK                  = CLOCK_IP_HAS_RTC_EXT_REF_CLK,
#endif
#if defined(CLOCK_IP_HAS_RXLUT_CLK)
    RXLUT_CLK                  = CLOCK_IP_HAS_RXLUT_CLK,
#endif
#if defined(CLOCK_IP_HAS_SAI0_CLK)
    SAI0_CLK                  = CLOCK_IP_HAS_SAI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
    SAI1_CLK                  = CLOCK_IP_HAS_SAI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDHC0_CLK)
    SDHC0_CLK                 = CLOCK_IP_HAS_SDHC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
    SEMA42_CLK                = CLOCK_IP_HAS_SEMA42_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
    SIPI0_CLK                 = CLOCK_IP_HAS_SIPI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIPI1_CLK)
    SIPI1_CLK                 = CLOCK_IP_HAS_SIPI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SINC_CLK)
    SINC_CLK                 = CLOCK_IP_HAS_SINC_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL0_CLK)
    SIUL0_CLK                 = CLOCK_IP_HAS_SIUL0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL1_CLK)
    SIUL1_CLK                 = CLOCK_IP_HAS_SIUL1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL2_0_CLK)
    SIUL2_0_CLK               = CLOCK_IP_HAS_SIUL2_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL2_1_CLK)
    SIUL2_1_CLK               = CLOCK_IP_HAS_SIUL2_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL2_4_CLK)
    SIUL2_4_CLK               = CLOCK_IP_HAS_SIUL2_4_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL2_5_CLK)
    SIUL2_5_CLK               = CLOCK_IP_HAS_SIUL2_5_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI_CLK)
    SPI_CLK                   = CLOCK_IP_HAS_SPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI0_CLK)
    SPI0_CLK                  = CLOCK_IP_HAS_SPI0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI1_CLK)
    SPI1_CLK                  = CLOCK_IP_HAS_SPI1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI2_CLK)
    SPI2_CLK                  = CLOCK_IP_HAS_SPI2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI3_CLK)
    SPI3_CLK                  = CLOCK_IP_HAS_SPI3_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI4_CLK)
    SPI4_CLK                  = CLOCK_IP_HAS_SPI4_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI5_CLK)
    SPI5_CLK                  = CLOCK_IP_HAS_SPI5_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI6_CLK)
    SPI6_CLK                  = CLOCK_IP_HAS_SPI6_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI7_CLK)
    SPI7_CLK                  = CLOCK_IP_HAS_SPI7_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI8_CLK)
    SPI8_CLK                  = CLOCK_IP_HAS_SPI8_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPI9_CLK)
    SPI9_CLK                  = CLOCK_IP_HAS_SPI9_CLK,
#endif
#if defined(CLOCK_IP_HAS_SRX0_CLK)
    SRX0_CLK                  = CLOCK_IP_HAS_SRX0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SRX1_CLK)
    SRX1_CLK                  = CLOCK_IP_HAS_SRX1_CLK,
#endif
#if defined(CLOCK_IP_HAS_STCU0_CLK)
    STCU0_CLK                 = CLOCK_IP_HAS_STCU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM0_CLK)
    STM0_CLK                  = CLOCK_IP_HAS_STM0_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
    STM1_CLK                  = CLOCK_IP_HAS_STM1_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
    STM2_CLK                  = CLOCK_IP_HAS_STM2_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
    STM3_CLK                  = CLOCK_IP_HAS_STM3_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM4_CLK)
    STM4_CLK                  = CLOCK_IP_HAS_STM4_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM5_CLK)
    STM5_CLK                  = CLOCK_IP_HAS_STM5_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM6_CLK)
    STM6_CLK                  = CLOCK_IP_HAS_STM6_CLK,
#endif
#if defined(CLOCK_IP_HAS_STM7_CLK)
    STM7_CLK                  = CLOCK_IP_HAS_STM7_CLK,
#endif
#if defined(CLOCK_IP_HAS_STMA_CLK)
    STMA_CLK                  = CLOCK_IP_HAS_STMA_CLK,
#endif
#if defined(CLOCK_IP_HAS_STMB_CLK)
    STMB_CLK                  = CLOCK_IP_HAS_STMB_CLK,
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
    STMC_CLK                  = CLOCK_IP_HAS_STMC_CLK,
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
    STMD_CLK                  = CLOCK_IP_HAS_STMD_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
    SWG_CLK                  = CLOCK_IP_HAS_SWG_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
    SWG0_CLK                  = CLOCK_IP_HAS_SWG0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
    SWG1_CLK                  = CLOCK_IP_HAS_SWG1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
    SWG_PAD_CLK                  = CLOCK_IP_HAS_SWG_PAD_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT0_CLK)
    SWT0_CLK                  = CLOCK_IP_HAS_SWT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT1_CLK)
    SWT1_CLK                  = CLOCK_IP_HAS_SWT1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
    SWT2_CLK                  = CLOCK_IP_HAS_SWT2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
    SWT3_CLK                  = CLOCK_IP_HAS_SWT3_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT4_CLK)
    SWT4_CLK                  = CLOCK_IP_HAS_SWT4_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT5_CLK)
    SWT5_CLK                  = CLOCK_IP_HAS_SWT5_CLK,
#endif
#if defined(CLOCK_IP_HAS_SWT6_CLK)
    SWT6_CLK                  = CLOCK_IP_HAS_SWT6_CLK,
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
    TCM_CM7_0_CLK             = CLOCK_IP_HAS_TCM_CM7_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
    TCM_CM7_1_CLK             = CLOCK_IP_HAS_TCM_CM7_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_TEMPSENSE_CLK)
    TEMPSENSE_CLK             = CLOCK_IP_HAS_TEMPSENSE_CLK,
#endif
#if defined(CLOCK_IP_HAS_TIMER_CLK)
    TIMER_CLK             = CLOCK_IP_HAS_TIMER_CLK,
#endif
#if defined(CLOCK_IP_HAS_ENET0_TIME_CLK)
    ENET0_TIME_CLK            = CLOCK_IP_HAS_ENET0_TIME_CLK,
#endif
#if defined(CLOCK_IP_HAS_TRACE_CLK)
    TRACE_CLK                 = CLOCK_IP_HAS_TRACE_CLK,
#endif
#if defined(CLOCK_IP_HAS_TRGMUX0_CLK)
    TRGMUX0_CLK               = CLOCK_IP_HAS_TRGMUX0_CLK,
#endif
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
    TRGMUX1_CLK               = CLOCK_IP_HAS_TRGMUX1_CLK,
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
    TSENSE0_CLK               = CLOCK_IP_HAS_TSENSE0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDHC_CLK)
    SDHC_CLK                  = CLOCK_IP_HAS_SDHC_CLK,
#endif
#if defined(CLOCK_IP_HAS_USDHC_CLK)
    USDHC_CLK                 = CLOCK_IP_HAS_USDHC_CLK,
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
    USDHC_PER_CLK             = CLOCK_IP_HAS_USDHC_PER_CLK,
#endif
#if defined(CLOCK_IP_HAS_USDHC0_CLK)
    USDHC0_CLK                = CLOCK_IP_HAS_USDHC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_WKPU0_CLK)
    WKPU0_CLK                 = CLOCK_IP_HAS_WKPU0_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_DIV3_FAIL_CLK)
    XBAR_DIV3_FAIL_CLK        = CLOCK_IP_HAS_XBAR_DIV3_FAIL_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_MIPICSI201_CLK)
    XBAR_MIPICSI201_CLK       = CLOCK_IP_HAS_XBAR_MIPICSI201_CLK,
#endif
#if defined(CLOCK_IP_HAS_XBAR_MIPICSI223_CLK)
    XBAR_MIPICSI223_CLK       = CLOCK_IP_HAS_XBAR_MIPICSI223_CLK,
#endif
#if defined(CLOCK_IP_HAS_BBE32EP_DSP_CLK)
    BBE32EP_DSP_CLK           = CLOCK_IP_HAS_BBE32EP_DSP_CLK,
#endif
#if defined(CLOCK_IP_HAS_CAN_CHI_CLK)
    CAN_CHI_CLK               = CLOCK_IP_HAS_CAN_CHI_CLK,
#endif
#if defined(CLOCK_IP_HAS_CAN_TS_CLK)
    CAN_TS_CLK                = CLOCK_IP_HAS_CAN_TS_CLK,
#endif
#if defined(CLOCK_IP_HAS_CAN0_CLK)
    CAN0_CLK                  = CLOCK_IP_HAS_CAN0_CLK,
#endif
#if defined(CLOCK_IP_HAS_CAN1_CLK)
    CAN1_CLK                  = CLOCK_IP_HAS_CAN1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CRC_CLK)
    CRC_CLK                   = CLOCK_IP_HAS_CRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_CSI_CFG_CLK)
    CSI_CLK                   = CLOCK_IP_HAS_CSI_CLK,
#endif
#if defined(CLOCK_IP_HAS_CSI_CFG_CLK)
    CSI_CFG_CLK               = CLOCK_IP_HAS_CSI_CFG_CLK,
#endif
#if defined(CLOCK_IP_HAS_CSI_IPS_CLK)
    CSI_IPS_CLK               = CLOCK_IP_HAS_CSI_IPS_CLK,
#endif
#if defined(CLOCK_IP_HAS_CSI_TXCLK_CLK)
    CSI_TXCLK_CLK             = CLOCK_IP_HAS_CSI_TXCLK_CLK,
#endif
#if defined(CLOCK_IP_HAS_CTE_CLK)
    CTE_CLK                   = CLOCK_IP_HAS_CTE_CLK,
#endif
#if defined(CLOCK_IP_HAS_CTU_CLK)
    CTU_CLK                   = CLOCK_IP_HAS_CTU_CLK,
#endif
#if defined(CLOCK_IP_HAS_CTU_IPS_CLK)
    CTU_IPS_CLK               = CLOCK_IP_HAS_CTU_IPS_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA_CLK)
    DMA_CLK                   = CLOCK_IP_HAS_DMA_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA_CRC_CLK)
    DMA_CRC_CLK               = CLOCK_IP_HAS_DMA_CRC_CLK,
#endif
#if defined(CLOCK_IP_HAS_DMA_TCD_CLK)
    DMA_TCD_CLK               = CLOCK_IP_HAS_DMA_TCD_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_AP1_CLK)
    EIM_AP1_CLK               = CLOCK_IP_HAS_EIM_AP1_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_CM70_CLK)
    EIM_CM70_CLK              = CLOCK_IP_HAS_EIM_CM70_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_CM71_CLK)
    EIM_CM71_CLK              = CLOCK_IP_HAS_EIM_CM71_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_DSP_CLK)
    EIM_DSP_CLK               = CLOCK_IP_HAS_EIM_DSP_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_RT0_CLK)
    EIM_RT0_CLK               = CLOCK_IP_HAS_EIM_RT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_EIM_RT2_CLK)
    EIM_RT2_CLK               = CLOCK_IP_HAS_EIM_RT2_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_AP1_CLK)
    ERM_AP1_CLK               = CLOCK_IP_HAS_ERM_AP1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_RT0_CLK)
    ERM_RT0_CLK               = CLOCK_IP_HAS_ERM_RT0_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_RT1_CLK)
    ERM_RT1_CLK               = CLOCK_IP_HAS_ERM_RT1_CLK,
#endif
#if defined(CLOCK_IP_HAS_ERM_RT2_CLK)
    ERM_RT2_CLK               = CLOCK_IP_HAS_ERM_RT2_CLK,
#endif
#if defined(CLOCK_IP_HAS_FCCU_IPS_CLK)
    FCCU_IPS_CLK              = CLOCK_IP_HAS_FCCU_IPS_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_M7_0_CLK)
    SYS_M7_0_CLK              = CLOCK_IP_HAS_SYS_M7_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_M7_1_CLK)
    SYS_M7_1_CLK              = CLOCK_IP_HAS_SYS_M7_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYS_HSE_CLK)
    SYS_HSE_CLK           = CLOCK_IP_HAS_SYS_HSE_CLK,
#endif
#if defined(CLOCK_IP_HAS_MC_CLK)
    MC_CLK                    = CLOCK_IP_HAS_MC_CLK,
#endif
#if defined(CLOCK_IP_HAS_MIPICSI2_0_CLK)
    MIPICSI2_0_CLK            = CLOCK_IP_HAS_MIPICSI2_0_CLK,
#endif
#if defined(CLOCK_IP_HAS_MIPICSI2_1_CLK)
    MIPICSI2_1_CLK            = CLOCK_IP_HAS_MIPICSI2_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_MSCDSPI_CLK)
    MSCDSPI_CLK            = CLOCK_IP_HAS_MSCDSPI_CLK,
#endif
#if defined(CLOCK_IP_HAS_MSCLIN_CLK)
    MSCLIN_CLK            = CLOCK_IP_HAS_MSCLIN_CLK,
#endif
#if defined(CLOCK_IP_HAS_NOC_TRACE_CLK)
    NOC_TRACE_CLK             = CLOCK_IP_HAS_NOC_TRACE_CLK,
#endif
#if defined(CLOCK_IP_HAS_NANO_CLK)
    NANO_CLK             = CLOCK_IP_HAS_NANO_CLK,
#endif
#if defined(CLOCK_IP_HAS_SAR_ADC_CLK)
    SAR_ADC_CLK               = CLOCK_IP_HAS_SAR_ADC_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
    SDA_AP_CLK               = CLOCK_IP_HAS_SDA_AP_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
    SDADC0_CLK               = CLOCK_IP_HAS_SDADC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
    SDADC1_CLK               = CLOCK_IP_HAS_SDADC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
    SDADC2_CLK               = CLOCK_IP_HAS_SDADC2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
    SDADC3_CLK               = CLOCK_IP_HAS_SDADC3_CLK,
#endif
#if defined(CLOCK_IP_HAS_SEMA42_1_CLK)
    SEMA42_1_CLK              = CLOCK_IP_HAS_SEMA42_1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SIUL2_CLK)
    SIUL2_CLK                 = CLOCK_IP_HAS_SIUL2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SPT_CLK)
    SPT_CLK                   = CLOCK_IP_HAS_SPT_CLK,
#endif
#if defined(CLOCK_IP_HAS_SRAM_CLK)
    SRAM_CLK                  = CLOCK_IP_HAS_SRAM_CLK,
#endif
#if defined(CLOCK_IP_HAS_STCU_CLK)
    STCU_CLK                  = CLOCK_IP_HAS_STCU_CLK,
#endif
#if defined(CLOCK_IP_HAS_TMU_CLK)
    TMU_CLK                   = CLOCK_IP_HAS_TMU_CLK,
#endif
#if defined(CLOCK_IP_HAS_WKPU_CLK)
    WKPU_CLK                  = CLOCK_IP_HAS_WKPU_CLK,
#endif
#if defined(CLOCK_IP_HAS_XRDC0_CLK)
    XRDC0_CLK                 = CLOCK_IP_HAS_XRDC0_CLK,
#endif
#if defined(CLOCK_IP_HAS_XRDC1_CLK)
    XRDC1_CLK                 = CLOCK_IP_HAS_XRDC1_CLK,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_REFCLKOUT)
    CORE_PLL_REFCLKOUT                 = CLOCK_IP_HAS_CORE_PLL_REFCLKOUT,
#endif
#if defined(CLOCK_IP_HAS_CORE_PLL_FBCLKOUT)
    CORE_PLL_FBCLKOUT                 = CLOCK_IP_HAS_CORE_PLL_FBCLKOUT,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_REFCLKOUT)
    PERIPH_PLL_REFCLKOUT                 = CLOCK_IP_HAS_PERIPH_PLL_REFCLKOUT,
#endif
#if defined(CLOCK_IP_HAS_PERIPH_PLL_FBCLKOUT)
    PERIPH_PLL_FBCLKOUT                 = CLOCK_IP_HAS_PERIPH_PLL_FBCLKOUT,
#endif
#if defined(CLOCK_IP_HAS_TCLK_CLK)
    TCLK_CLK                  = CLOCK_IP_HAS_TCLK_CLK,
#endif
#if defined(CLOCK_IP_HAS_TCK_CLK)
    TCK_CLK                  = CLOCK_IP_HAS_TCK_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
    AES_CLK                  = CLOCK_IP_HAS_AES_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
    AES_ACCEL_CLK                  = CLOCK_IP_HAS_AES_ACCEL_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
    AES_APP0_CLK                  = CLOCK_IP_HAS_AES_APP0_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
    AES_APP1_CLK                  = CLOCK_IP_HAS_AES_APP1_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
    AES_APP2_CLK                  = CLOCK_IP_HAS_AES_APP2_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
    AES_APP3_CLK                  = CLOCK_IP_HAS_AES_APP3_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
    AES_APP4_CLK                  = CLOCK_IP_HAS_AES_APP4_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
    AES_APP5_CLK                  = CLOCK_IP_HAS_AES_APP5_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
    AES_APP6_CLK                  = CLOCK_IP_HAS_AES_APP6_CLK,
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
    AES_APP7_CLK                  = CLOCK_IP_HAS_AES_APP7_CLK,
#endif
#if defined(CLOCK_IP_HAS_DSPI_SCK_TST_CLK)
    DSPI_SCK_TST_CLK          = CLOCK_IP_HAS_DSPI_SCK_TST_CLK,
#endif
RESERVED_CLK                  = CLOCK_IP_FEATURE_NAMES_NO,  /* Invalid clock name */
} Clock_Ip_NameType;

/** @brief Clock ip status return codes. */
typedef enum
{
    CLOCK_IP_SUCCESS                            = 0x00U,    /**< Clock tree was initialized successfully. */
    CLOCK_IP_ERROR                              = 0x01U,    /**< One of the elements timeout, clock tree couldn't be initialized. */

} Clock_Ip_StatusType;

/** @brief Clock ip pll status return codes. */
typedef enum
{
    CLOCK_IP_PLL_LOCKED                         = 0x00U,    /**< PLL is locked */
    CLOCK_IP_PLL_UNLOCKED                       = 0x01U,    /**< PLL is unlocked */
    CLOCK_IP_PLL_STATUS_UNDEFINED               = 0x02U,    /**< PLL Status is unknown */

} Clock_Ip_PllStatusType;

/** @brief Clock ip report error types. */
typedef enum
{
    CLOCK_IP_CMU_ERROR                          = 0U,   /**< @brief Cmu Fccu notification. */
    CLOCK_IP_REPORT_TIMEOUT_ERROR               = 1U,   /**< @brief Report Timeout Error. */
    CLOCK_IP_REPORT_FXOSC_CONFIGURATION_ERROR   = 2U,   /**< @brief Report Fxosc Configuration Error. */
    CLOCK_IP_REPORT_CLOCK_MUX_SWITCH_ERROR      = 3U,   /**< @brief Report Clock Mux Switch Error. */
    CLOCK_IP_RAM_MEMORY_CONFIG_ENTRY            = 4U,   /**< @brief Ram config entry point. */
    CLOCK_IP_RAM_MEMORY_CONFIG_EXIT             = 5U,   /**< @brief Ram config exit point. */
    CLOCK_IP_FLASH_MEMORY_CONFIG_ENTRY          = 6U,   /**< @brief Flash config entry point. */
    CLOCK_IP_FLASH_MEMORY_CONFIG_EXIT           = 7U,   /**< @brief Flash config exit point. */
    CLOCK_IP_ACTIVE                             = 8U,   /**< @brief Report Clock Active. */
    CLOCK_IP_INACTIVE                           = 9U,   /**< @brief Report Clock Inactive. */
    CLOCK_IP_REPORT_WRITE_PROTECTION_ERROR      = 10U,  /**< @brief Report Write Protection Error. */
    CLOCK_IP_SET_RAM_WAIT_STATES_ERROR          = 11U,  /**< @brief Set Ram Wait States Error. */
} Clock_Ip_NotificationType;

/** @brief Clock ip trigger divider type. */
typedef enum
{
    IMMEDIATE_DIVIDER_UPDATE,          /**< @brief Immediate divider update. */
    COMMON_TRIGGER_DIVIDER_UPDATE,     /**< @brief Common trigger divider update.  */

} Clock_Ip_TriggerDividerType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/*!
 * @brief Clock notifications callback type.
 * Implements ClockNotificationsCallbackType_Class
 */
typedef void (*Clock_Ip_NotificationsCallbackType)(Clock_Ip_NotificationType Error, Clock_Ip_NameType ClockName);

/*!
 * @brief Register value structure.
 * Implements Clock_Ip_RegisterValueType_Class
 */
typedef struct
{
    uint32*                       RegisterAddr;    /**< Register address. */
    uint32                        RegisterData;    /**< Register value. */

} Clock_Ip_RegisterValueType;

/*!
 * @brief Register index structure.
 * Implements Clock_Ip_RegisterIndexType_Class
 */
typedef struct
{
    uint16                        StartIndex;            /**< Start index in register array. */
    uint16                        EndIndex;              /**< End index in register array. */

} Clock_Ip_RegisterIndexType;



/*!
 * @brief Clock Source IRCOSC configuration structure.
 * Implements Clock_Ip_IrcoscConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType             Name;               /**< Clock name associated to ircosc */
    uint16                        Enable;             /**< Enable ircosc. */

    uint8                         Regulator;          /**< Enable regulator. */
    uint8                         Range;              /**< Ircosc range. */
    uint8                         LowPowerModeEnable; /**< Ircosc enable in VLP mode */
    uint8                         StopModeEnable;     /**< Ircosc enable in STOP mode */

} Clock_Ip_IrcoscConfigType;

/*!
 * @brief CGM Clock Source XOSC configuration structure.
 * Implements Clock_Ip_XoscConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType       Name;                   /**< Clock name associated to xosc */

    uint32                  Freq;                   /**< External oscillator frequency. */

    uint16                  Enable;                 /**< Enable xosc. */

    uint16                  StartupDelay;           /**< Startup stabilization time. */
    uint8                   BypassOption;           /**< XOSC bypass option */
    uint8                   CompEn;                 /**< Comparator enable */
    uint8                   TransConductance;       /**< Crystal overdrive protection */

    uint8                   Gain;                   /**< Gain value */
    uint8                   Monitor;                /**< Monitor type */
    uint8                   AutoLevelController;    /**< Automatic level controller */
    uint8                   LevelShifterCurrent;    /**< Level Shifter Current */
    uint8                   ComparatorCurrent;      /**< Comparator Current */

} Clock_Ip_XoscConfigType;

/*!
 * @brief CGM Clock Source PLLDIG configuration structure.
 * Implements Clock_Ip_PllConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType        Name;                           /**< Clock name associated to pll */

    uint16                   Enable;                         /**< Enable pll. */

    Clock_Ip_NameType        InputReference;                 /**< Input reference. */

    uint8                    Bypass;                         /**< Bypass pll. */

    uint8                    Predivider;                     /**< Input clock predivider. */
    uint16                   Multiplier;                     /**< Clock multiplier.  */
    uint8                    Postdivider;                    /**< Clock postidivder.*/

    uint16                   NumeratorFracLoopDiv;           /**< Numerator of fractional loop division factor (MFN) */
    uint8                    MulFactorDiv;                   /**< Multiplication factor divider (MFD) */

    uint8                    FrequencyModulationBypass;      /**< Enable/disable modulation */
    uint8                    ModulationType;                 /**< Modulation type */
    uint16                   ModulationPeriod;               /**< Stepsize - modulation period */
    uint16                   IncrementStep;                  /**< Stepno  - step no */

    uint8                    SigmaDelta;                     /**< Sigma Delta Modulation Enable */

    uint8                    DitherControl;                  /**< Dither control enable */
    uint8                    DitherControlValue;             /**< Dither control value */

    uint8                    Monitor;                        /**< Monitor type */

    uint16                   Dividers[3U];                   /**< Dividers values */

    uint8                    SoftwareDisable;                /**< Software Disable */
} Clock_Ip_PllConfigType;

/*!
 * @brief Clock selector configuration structure.
 * Implements Clock_Ip_SelectorConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType               Name;                           /**< Clock name associated to selector */
    Clock_Ip_NameType               Value;                          /**< Name of the selected input source */

} Clock_Ip_SelectorConfigType;

/*!
 * @brief Clock divider configuration structure.
 * Implements Clock_Ip_DividerConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType         Name;                           /**< Clock name associated to divider. */
    uint32                    Value;                          /**< Divider value - if value is zero then divider is disabled. */
    uint8                     Options[1U];                    /**< Option divider value - this value depend hardware information. */
} Clock_Ip_DividerConfigType;

/*!
 * @brief Clock divider trigger configuration structure.
 * Implements Clock_Ip_DividerTriggerConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType             Name;                           /**< Clock name associated to divider for which trigger is configured. */
    Clock_Ip_TriggerDividerType   TriggerType;                    /**< Trigger value - if value is zero then divider is updated immediately, divider is not triggered. */
    Clock_Ip_NameType             Source;                         /**< Clock name of the common input source of all dividers from the same group that support a common update */

} Clock_Ip_DividerTriggerConfigType;



/*!
 * @brief Clock fractional divider configuration structure.
 * Implements Clock_Ip_FracDivConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType         Name;                           /**< Clock name associated to fractional divider. */
    uint8                     Enable;                         /**< Enable control for port n */
    uint32                    Value[2U];                      /**< Fractional dividers */

} Clock_Ip_FracDivConfigType;

/*!
 * @brief Clock external clock configuration structure.
 * Implements Clock_Ip_ExtClkConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType         Name;                           /**< Clock name of the external clock. */
    uint64                    Value;                          /**< Enable value - if value is zero then clock is gated, otherwise is enabled in different modes. */

} Clock_Ip_ExtClkConfigType;

/*!
 * @brief Clock Source PCFS configuration structure.
 * Implements Clock_Ip_PcfsConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType             Name;                        /**<  Clock source from which ramp-down and to which ramp-up are processed. */
    uint32                        MaxAllowableIDDchange;       /**<  Maximum variation of current per time (mA/microsec) -  max allowable IDD change is determined by the user's power supply design. */
    uint32                        StepDuration;                /**<  Step duration of each PCFS step */
    Clock_Ip_NameType             SelectorName;                /**<  Name of the selector that supports PCFS and name is one the inputs that can be selected */
    uint32                        ClockSourceFrequency;        /**<  Frequency of the clock source from which ramp-down and to which ramp-up are processed. */

} Clock_Ip_PcfsConfigType;

/*!
 * @brief Clock gate clock configuration structure.
 * Implements Clock_Ip_GateConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType         Name;                           /**< Clock name associated to clock gate. */
    uint16                    Enable;                         /**< Enable or disable clock */

} Clock_Ip_GateConfigType;

/*!
 * @brief Clock cmu configuration structure.
 * Implements Clock_Ip_CmuConfigType_Class
 */
typedef struct
{
    Clock_Ip_NameType               Name;                           /**< Clock name associated to clock monitor. */
    uint8                           Enable;                         /**< Enable/disable clock monitor */
    uint32                          Interrupt;                      /**< Enable/disable interrupt */
    uint32                          MonitoredClockFrequency;        /**< Frequency of the clock source from which ramp-down and to which ramp-up are processed. */
    Clock_Ip_RegisterIndexType      Indexes;                        /**< Register index if register value optimization is enabled. */
} Clock_Ip_CmuConfigType;

/*!
 * @brief Configured frequency structure.
 * Implements Clock_Ip_ConfiguredFrequencyType_Class
 */
typedef struct
{
    Clock_Ip_NameType               Name;                           /**< Clock name of the configured frequency value */
    uint32                          ConfiguredFrequencyValue;       /**< Configured frequency value */
} Clock_Ip_ConfiguredFrequencyType;

/*!
 * @brief Clock configuration structure.
 * Implements Clock_Ip_ClockConfigType_Class
 */
typedef struct
{
    uint32                             ClkConfigId;                                     /**< The ID for Clock configuration */

    const Clock_Ip_RegisterValueType         (*RegValues)[];                                  /**< Pointer to register values array */

    uint8   IrcoscsCount;                                                               /**< IRCOSCs count */
    uint8   XoscsCount;                                                                 /**< XOSCs count */
    uint8   PllsCount;                                                                  /**< PLLs count */
    uint8   SelectorsCount;                                                             /**< Selectors count */
    uint8   DividersCount;                                                              /**< Dividers count */
    uint8   DividerTriggersCount;                                                       /**< Divider triggers count */
    uint8   FracDivsCount;                                                              /**< Fractional dividers count */
    uint8   ExtClksCount;                                                               /**< External clocks count */
    uint8   GatesCount;                                                                 /**< Clock gates count */
    uint8   PcfsCount;                                                                  /**< Clock pcfs count */
    uint8   CmusCount;                                                                  /**< Clock cmus count */
    uint8   ConfigureFrequenciesCount;                                                  /**< Configured frequencies count */

    const Clock_Ip_IrcoscConfigType          (*Ircoscs)[];                              /**< IRCOSCs */
    const Clock_Ip_XoscConfigType            (*Xoscs)[];                                /**< XOSCs */
    const Clock_Ip_PllConfigType             (*Plls)[];                                 /**< PLLs */
    const Clock_Ip_SelectorConfigType        (*Selectors)[];                            /**< Selectors */
    const Clock_Ip_DividerConfigType         (*Dividers)[];                             /**< Dividers */
    const Clock_Ip_DividerTriggerConfigType  (*DividerTriggers)[];                      /**< Divider triggers */
    const Clock_Ip_FracDivConfigType         (*FracDivs)[];                             /**< Fractional dividers */
    const Clock_Ip_ExtClkConfigType          (*ExtClks)[];                              /**< External clocks */
    const Clock_Ip_GateConfigType            (*Gates)[];                                /**< Clock gates */
    const Clock_Ip_PcfsConfigType            (*Pcfs)[];                                 /**< Progressive clock switching */
    const Clock_Ip_CmuConfigType             (*Cmus)[];                                 /**< Clock cmus */
    const Clock_Ip_ConfiguredFrequencyType   (*ConfiguredFrequencies)[];                /**< Configured frequency values */

} Clock_Ip_ClockConfigType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                     CONFIGURATION STRUCTURE
==================================================================================================*/


#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_IP_TYPES_H */


