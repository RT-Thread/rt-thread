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

#ifndef POWER_IP_AEC_TYPES_H
#define POWER_IP_AEC_TYPES_H

/**
*   @file       Power_Ip_AEC_Types.h
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
#include "Power_Ip_Cfg_Defines.h"
#include "Mcal.h"
#if (defined(POWER_IP_S32M244) || defined(POWER_IP_S32M242) || defined(POWER_IP_S32M241) || defined(POWER_IP_S32M243))
  #include "S32M24x_AEC_AE.h"
#endif
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_AEC_TYPES_VENDOR_ID                       43
#define POWER_IP_AEC_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_AEC_TYPES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_AEC_TYPES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_AEC_TYPES_SW_MAJOR_VERSION                5
#define POWER_IP_AEC_TYPES_SW_MINOR_VERSION                0
#define POWER_IP_AEC_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Power_Ip_AEC_Types.h file and Mcal.h file are of the same Autosar version */
#if ((POWER_IP_AEC_TYPES_AR_RELEASE_MAJOR_VERSION    != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AEC_TYPES_AR_RELEASE_MINOR_VERSION    != MCAL_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_AEC_Types.h and Mcal.h are different"
#endif
#endif

/* Check if Power_Ip_AEC_Types.h file and Power_Ip_Cfg_Defines.h file have same versions */
#if (POWER_IP_AEC_TYPES_VENDOR_ID  != POWER_IP_CFG_DEFINES_VENDOR_ID)
    #error "Power_Ip_AEC_Types.h and Power_Ip_Cfg_Defines.h have different vendor IDs"
#endif

/* Check if Power_Ip_AEC_Types.h file and Power_Ip_Cfg_Defines.h file are of the same Autosar version */
#if ((POWER_IP_AEC_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AEC_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AEC_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_AEC_Types.h and Power_Ip_Cfg_Defines.h are different"
#endif

/* Check if Power_Ip_AEC_Types.h file and Power_Ip_Cfg_Defines.h file are of the same Software version */
#if ((POWER_IP_AEC_TYPES_SW_MAJOR_VERSION != POWER_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (POWER_IP_AEC_TYPES_SW_MINOR_VERSION != POWER_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (POWER_IP_AEC_TYPES_SW_PATCH_VERSION != POWER_IP_CFG_DEFINES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_AEC_Types.h and Power_Ip_Cfg_Defines.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

#define AEC_AE_RSTGEN_CFG_REGS_OTP_ENABLE_U16          ((uint16)(0x0001))
#define AEC_AE_RSTGEN_CFG_REGS_OTP_DISABLE_U16         ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_CANPHY_ENABLE_U16            ((uint16)(0x0002))
#define AEC_AE_RSTGEN_CFG_CANPHY_DISABLE_U16           ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_LINPHY_HP_ENABLE_U16         ((uint16)(0x0004))
#define AEC_AE_RSTGEN_CFG_LINPHY_HP_DISABLE_U16        ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_LINPHY_LP_ENABLE_U16         ((uint16)(0x0008))
#define AEC_AE_RSTGEN_CFG_LINPHY_LP_DISABLE_U16        ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_GDU_ENABLE_U16               ((uint16)(0x0010))
#define AEC_AE_RSTGEN_CFG_GDU_DISABLE_U16              ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_HVI_ENABLE_U16               ((uint16)(0x0020))
#define AEC_AE_RSTGEN_CFG_HVI_DISABLE_U16              ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_DPGA_ENABLE_U16              ((uint16)(0x0040))
#define AEC_AE_RSTGEN_CFG_DPGA_DISABLE_U16             ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_TEMPSENSOR_ENABLE_U16        ((uint16)(0x0080))
#define AEC_AE_RSTGEN_CFG_TEMPSENSOR_DISABLE_U16       ((uint16)(0x0000))
#define AEC_AE_RSTGEN_CFG_CXPI_ENABLE_U16              ((uint16)(0x0100))
#define AEC_AE_RSTGEN_CFG_CXPI_DISABLE_U16             ((uint16)(0x0000))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief            Configuration for AEC.
* @details          The Reset generator configuration (AEC_RSTGEN_CFG)
*/
typedef struct
{
    uint16 Rstgencfg;                   /**< @brief Reset generator configuration (AEC_RSTGEN_CFG). */
} Power_Ip_AEC_ConfigType;

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
#endif /* POWER_IP_AEC_TYPES_H */

