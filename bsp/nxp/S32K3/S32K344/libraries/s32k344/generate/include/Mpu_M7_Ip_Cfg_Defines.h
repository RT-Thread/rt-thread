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

#ifndef MPU_M7_IP_CFG_DEFINES_H_
#define MPU_M7_IP_CFG_DEFINES_H_

/**
*   @file Mpu_M7_Ip_CfgDefines.h
*
*   @addtogroup Mpu_M7_Ip Mpu M7 IPV Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

#include "S32K344_MPU.h"
#include "S32K344_SCB.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_VENDOR_ID                    43
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     7
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_SW_MAJOR_VERSION             5
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_SW_MINOR_VERSION             0
#define CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Std_Types.h */
    #if ((CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Mpu_M7_Ip_Cfg_Defines.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** @brief    IP enablement checking */
#define PLATFORM_IP_ENABLE_MPU_M7 (STD_OFF)



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

#endif /* MPU_M7_IP_CFG_DEFINES_H_ */

