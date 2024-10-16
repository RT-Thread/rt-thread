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

#ifndef FLEXIO_UART_IP_DEFINES_H
#define FLEXIO_UART_IP_DEFINES_H

/**
*   @file
*   @defgroup flexio_uart_ip Flexio UART IPL
*   @addtogroup  flexio_uart_ip Flexio UART IPL
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
#include "S32K344_FLEXIO.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_UART_IP_DEFINES_VENDOR_ID                     43
#define FLEXIO_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION      4
#define FLEXIO_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION      7
#define FLEXIO_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION   0
#define FLEXIO_UART_IP_DEFINES_SW_MAJOR_VERSION              5
#define FLEXIO_UART_IP_DEFINES_SW_MINOR_VERSION              0
#define FLEXIO_UART_IP_DEFINES_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((FLEXIO_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_Defines.h and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                     DEFINES AND MACROS
==================================================================================================*/
/* @brief Using FLEXIO */
#define FLEXIO_UART_IP_IS_USING                         (STD_OFF)

/* @brief Development error detection */
#define FLEXIO_UART_IP_DEV_ERROR_DETECT                 (STD_ON)

/* @brief Flexio DMA support */
#define FLEXIO_UART_IP_HAS_DMA_ENABLED                  (STD_OFF)

/* @brief Number of available shifter and timer */
#define FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER      (8U)

/* @brief Total number of channels configured for FLEXIO, the define should be set to 1 when FLEXIO is not configured*/
#define FLEXIO_UART_IP_NUMBER_OF_INSTANCES              (1U)

/* @brief Uart Osif source counter. This parameter is used to select between different OsIf counter implementation */
#define FLEXIO_UART_IP_TIMEOUT_TYPE                     (OSIF_COUNTER_DUMMY)

/* @brief Number of loops before returning STATUS_TIMEOUT.*/
#define FLEXIO_UART_IP_TIMEOUT_VALUE_US                 (10000000U)

/* @brief Flexio Usermode support */
#define FLEXIO_UART_IP_ENABLE_USER_MODE_SUPPORT         (STD_OFF)


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

#endif /* FLEXIO_UART_IP_DEFINES_H */

