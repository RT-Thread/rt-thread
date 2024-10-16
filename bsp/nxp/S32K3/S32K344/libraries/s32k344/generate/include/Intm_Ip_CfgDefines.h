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

#ifndef INTM_IP_CFG_DEFINES_H_
#define INTM_IP_CFG_DEFINES_H_

/**
*   @file
*
*   @addtogroup Intm_Ip
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

        #include "S32K344_INTM.h"
        


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_VENDOR_ID                          43
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTM_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
    
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/**
* @brief          Enumeration exposing the available interrupt monitors.
* @implements     Intm_Ip_MonitorType_Class
*/
typedef enum
{
    /** @brief Interrupt monitor 0 */
    INTM_IP_MONITOR0,
    /** @brief Interrupt monitor 1 */
    INTM_IP_MONITOR1,
    /** @brief Interrupt monitor 2 */
    INTM_IP_MONITOR2,
    /** @brief Interrupt monitor 3 */
    INTM_IP_MONITOR3
}Intm_Ip_MonitorType;

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define INTM_IP_IRQ_MIN                       (INT0_IRQn)
#define INTM_IP_IRQ_MAX                       (SoC_PLL_IRQn)

#endif /* INTM_IP_CFG_DEFINES_H_ */

/** @} */

