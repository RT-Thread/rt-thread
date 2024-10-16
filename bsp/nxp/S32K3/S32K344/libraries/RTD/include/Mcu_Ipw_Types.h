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

#ifndef MCU_IPW_TYPES_H
#define MCU_IPW_TYPES_H

/**
*   @file    Mcu_Ipw_Types.h
*   @version    5.0.0
*
*   @brief   AUTOSAR Mcu - Mcu driver header file.
*   @details AUTOSAR specific Mcu driver header file.

*   @addtogroup MCU_DRIVER Mcu Driver
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
/* Header files that are specific to the common (main) platform */
#include "Mcu_Cfg.h"
#include "Clock_Ip_Types.h"
#include "Power_Ip_Types.h"
#include "Ram_Ip_Types.h"

/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_IPW_TYPES_VENDOR_ID                     43
#define MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION      4
#define MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION      7
#define MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION   0
#define MCU_IPW_TYPES_SW_MAJOR_VERSION              5
#define MCU_IPW_TYPES_SW_MINOR_VERSION              0
#define MCU_IPW_TYPES_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Mcu_Ipw_Types.h file and Mcu_Cfg.h file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_CFG_VENDOR_ID)
    #error "Mcu_Ipw_Types.h and Mcu_Cfg.h have different vendor ids"
#endif

/* Check if Mcu_Ipw_Types.h file and Mcu_Cfg.h file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw_Types.h and Mcu_Cfg.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Mcu_Cfg.h file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw_Types.h and Mcu_Cfg.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Clock_Ip_Types.h file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != CLOCK_IP_TYPES_VENDOR_ID)
    #error "Mcu_Ipw_Types.h and Clock_Ip_Types.h have different vendor ids"
#endif

/* Check if Mcu_Ipw_Types.h file and Clock_Ip_Types.h file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != CLOCK_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION != CLOCK_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != CLOCK_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw_Types.h and Clock_Ip_Types.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Clock_Ip_Types.h file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != CLOCK_IP_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != CLOCK_IP_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != CLOCK_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw_Types.h and Clock_Ip_Types.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Power_Ip_Types.h file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != POWER_IP_TYPES_VENDOR_ID)
    #error "Mcu_Ipw_Types.h and Power_Ip_Types.h have different vendor ids"
#endif

/* Check if Mcu_Ipw_Types.h file and Power_Ip_Types.h file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != POWER_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION != POWER_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw_Types.h and Power_Ip_Types.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Power_Ip_Types.h file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != POWER_IP_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != POWER_IP_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != POWER_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw_Types.h and Power_Ip_Types.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Ram_Ip_Types.h file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != RAM_IP_TYPES_VENDOR_ID)
    #error "Mcu_Ipw_Types.h and Ram_Ip_Types.h have different vendor ids"
#endif

/* Check if Mcu_Ipw_Types.h file and Ram_Ip_Types.h file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != RAM_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION != RAM_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != RAM_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Ipw_Types.h and Ram_Ip_Types.h are different"
#endif

/* Check if Mcu_Ipw_Types.h file and Ram_Ip_Types.h file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != RAM_IP_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != RAM_IP_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != RAM_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Ipw_Types.h and Ram_Ip_Types.h are different"
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Mcu_ClockNotificationType
* @details      Clock failure notification.
*               Enable/disable clock failure interrupt generated by the MCU.
*/
typedef enum
{
    MCU_CLK_NOTIF_DIS = 0x5AU,   /**< @brief Disable clock notification. */
    MCU_CLK_NOTIF_EN = 0xA5U     /**< @brief Enable clock notification.  */

} Mcu_ClockNotificationType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            Mcu driver configuration structure.
* @details          Configuration for SIU reset configuration module.
*                   Configuration for power management and SSCM.
*                   Configuration for FLASH controller.
*                   Used by "Mcu_ConfigType" structure.
*
*/
typedef Power_Ip_HwIPsConfigType Mcu_HwIPsConfigType;


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            Definition of a Clock configuration.
* @details          This configuration is transmitted as parameter to Mcu_Ipw_InitClock() API.
*                   Used by "Mcu_ConfigType" structure.
*
* @note             The structure Mcu_ConfigType shall provide a configurable (enable/ disable)
*                   clock failure notification if the MCU provides an interrupt for such detection.
*
*/
typedef Clock_Ip_ClockConfigType Mcu_ClockConfigType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#ifndef MCU_MAX_NORAMCONFIGS
/**
* @brief            Definition of a Clock configuration.
* @details          This configuration is transmitted as parameter to Mcu_Ipw_InitClock() API.
*                   Used by "Mcu_ConfigType" structure.
*
* @note             The structure Mcu_ConfigType shall provide a configurable (enable/ disable)
*                   clock failure notification if the MCU provides an interrupt for such detection.
*
*/
typedef Ram_Ip_RamConfigType Mcu_RamConfigType;
#endif /* ifndef MCU_MAX_NORAMCONFIGS */

/**
* @brief            Definition of a Mode configuration.
* @details          This configuration is transmitted as parameter to Mcu_Ipw_SetMode() API.
*                   Used by "Mcu_ConfigType" structure.
*
*/
typedef Power_Ip_ModeConfigType Mcu_ModeConfigType;

#ifdef MCU_GET_MIDR_API
  #if (MCU_GET_MIDR_API == STD_ON)
/**
* @brief            MIDR configuration
*
*/
typedef struct
{
    uint32 Midr1;   /**< @brief SIUL2_MIDR1 Configuration register. */
    uint32 Midr2;   /**< @brief SIUL2_MIDR2 Configuration register. */
    uint32 Midr3;   /**< @brief SIUL2_MIDR3 Configuration register. */
    uint32 Midr4;   /**< @brief SIUL2_MIDR4 Configuration register. */

} Mcu_MidrReturnType;
#endif /* (MCU_GET_MIDR_API == STD_ON) */
#endif /* MCU_GET_MIDR_API */


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
#endif /* MCU_IPW_TYPES_H */



