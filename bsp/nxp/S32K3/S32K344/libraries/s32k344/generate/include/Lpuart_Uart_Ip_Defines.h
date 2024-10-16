/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXIO
*   Dependencies         : 
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

#ifndef LPUART_UART_IP_DEFINES_H
#define LPUART_UART_IP_DEFINES_H

/**
*   @file
*   @defgroup lpuart_uart_ip Lpuart UART IPL
*   @addtogroup  lpuart_uart_ip Lpuart UART IPL
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
* 4) user callback header files
==================================================================================================*/
#include "Mcal.h"
#include "S32K344_LPUART.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_UART_IP_DEFINES_VENDOR_ID                     43
#define LPUART_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION      4
#define LPUART_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION      7
#define LPUART_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION   0
#define LPUART_UART_IP_DEFINES_SW_MAJOR_VERSION              5
#define LPUART_UART_IP_DEFINES_SW_MINOR_VERSION              0
#define LPUART_UART_IP_DEFINES_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((LPUART_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip_Defines.h and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                     DEFINES AND MACROS
==================================================================================================*/

/** Array initializer of LINFLEXD peripheral base pointers */
#define LPUART_IP_BASE_PTRS                    IP_LPUART_BASE_PTRS
/* @brief Development error detection */
#define LPUART_UART_IP_DEV_ERROR_DETECT         (STD_ON)

/* @brief Total number of channels configured for Lpuart, the define should be set to 1 when Lpuart is not configured*/
#define LPUART_UART_IP_NUMBER_OF_INSTANCES      (1U)

/* @brief Uart Osif source counter. This parameter is used to select between different OsIf counter implementation */
#define LPUART_UART_IP_TIMEOUT_TYPE             (OSIF_COUNTER_DUMMY)

/* @brief Number of loops before returning STATUS_TIMEOUT.*/
#define LPUART_UART_IP_TIMEOUT_VALUE_US         (10000000U)

/* @brief Lpuart DMA support */
#define LPUART_UART_IP_HAS_DMA_ENABLED          (STD_OFF)

/* @brief Lpuart Usermode support */
#define LPUART_UART_IP_ENABLE_USER_MODE_SUPPORT (STD_OFF) /* Disable User Mode */

/* @brief Support for Uart Timeout Interrupt. If this parameter has been configured to TRUE, the Uart driver will enable Timeout Interrupt. */
#define LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT  (STD_OFF)

#if (STD_ON == LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT)
    /* @brief Array of instances that have loopback mode enabled. */
    #define LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT_PER_INSTANCE  {(boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE}
#endif

/* @brief Support for Internal Loopback. If this parameter has been configured to TRUE, the Uart driver will be executed in Loopback mode. */
#define LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK  (STD_OFF)

#if (STD_ON == LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK)
    /* @brief Array of instances that have loopback mode enabled. */
    #define LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK_PER_INSTANCE  {(boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE, (boolean) FALSE}
#endif

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
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

#endif /* LPUART_UART_IP_DEFINES_H */

