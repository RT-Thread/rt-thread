/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
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
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef SIUL2_PORT_IP_DEFINES
#define SIUL2_PORT_IP_DEFINES

/**
*   @file    Siul2_Port_Ip_Defines.h
*
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "S32K344_SIUL2.h"
#include "S32K344_DCM_GPR.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SIUL2_PORT_IP_DEFINES_VENDOR_ID_H                       43
#define SIUL2_PORT_IP_DEFINES_AR_RELEASE_MAJOR_VERSION_H        4
#define SIUL2_PORT_IP_DEFINES_AR_RELEASE_MINOR_VERSION_H        7
#define SIUL2_PORT_IP_DEFINES_AR_RELEASE_REVISION_VERSION_H     0
#define SIUL2_PORT_IP_DEFINES_SW_MAJOR_VERSION_H                5
#define SIUL2_PORT_IP_DEFINES_SW_MINOR_VERSION_H                0
#define SIUL2_PORT_IP_DEFINES_SW_PATCH_VERSION_H                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Number of SIUL2 instances present on the subderivative
*/
#define SIUL2_NUM_SIUL2_INSTANCES_U8 (1)

/* S32K3XX */
#define SIUL2_PORT_IP_HAS_ONEBIT_SLEWRATE           (STD_ON)
#define SIUL2_PORT_IP_HAS_ADC_INTERLEAVE            (STD_ON)
#define FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT   (STD_OFF)

/*! @brief SIUL2 module has DSE bit */
#define FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH    (STD_ON)

/*! @brief SIUL2 module has IFE bit */
#define FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER      (STD_ON)

/*! @brief SIUL2 module has PKE bit */
#define FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER       (STD_ON)

/*! @brief SIUL2 module has INV bit */
#define FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA       (STD_ON)

#define FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING         (STD_ON)
/**
* @brief Macros defined for the SIUL2 IPV that are protected.
*/
#define MCAL_SIUL2_REG_PROT_AVAILABLE   (STD_ON)

/**
* @brief Macros defined for the protection size
*/
#define SIUL2_PROT_MEM_U32    ((uint32)0x00000008UL)

/**
* @brief Support for User mode.
* If this parameter has been configured to STD_ON, the PORT driver code can be executed from both supervisor and user mode.
*/
#define PORT_ENABLE_USER_MODE_SUPPORT   (STD_OFF)

#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
    #ifdef PORT_ENABLE_USER_MODE_SUPPORT
        #if (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT)
            #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Port in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined
        #endif /* (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT) */
    #endif /* ifdef PORT_ENABLE_USER_MODE_SUPPORT*/
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

/* Pre-processor switch to enable/disable development error detection for Siul2 Ip API */
#define SIUL2_PORT_IP_DEV_ERROR_DETECT                         (STD_OFF)

#define PORT_SIUL2_0_IMCRS_IDX_END_U16     ((uint16)378)

/* Pre-processor switch to enable/disable VirtWrapper support */
#define PORT_VIRTWRAPPER_SUPPORT                      (STD_OFF)


#define SIUL2_MSCR_BASE                (IP_SIUL2->MSCR)

/** SIUL2 */
/** Peripheral PORTA_L_HALF base pointer */
#define PORTA_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x00))
/** Peripheral PORTA_H_HALF base pointer */
#define PORTA_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x10))
/** Peripheral PORTB_L_HALF base pointer */
#define PORTB_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x20))
/** Peripheral PORTB_H_HALF base pointer */
#define PORTB_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x30))
/** Peripheral PORTC_L_HALF base pointer */
#define PORTC_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x40))
/** Peripheral PORTC_H_HALF base pointer */
#define PORTC_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x50))
/** Peripheral PORTD_L_HALF base pointer */
#define PORTD_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x60))
/** Peripheral PORTD_H_HALF base pointer */
#define PORTD_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x70))
/** Peripheral PORTE_L_HALF base pointer */
#define PORTE_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x80))
/** Peripheral PORTE_H_HALF base pointer */
#define PORTE_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0x90))
/** Peripheral PORTF_L_HALF base pointer */
#define PORTF_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0xA0))
/** Peripheral PORTF_H_HALF base pointer */
#define PORTF_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0xB0))
/** Peripheral PORTG_L_HALF base pointer */
#define PORTG_L_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0xC0))
/** Peripheral PORTG_H_HALF base pointer */
#define PORTG_H_HALF                            ((Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + 0xD0))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


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

#endif /* SIUL2_PORT_IP_DEFINES */

