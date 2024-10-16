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

#ifndef UART_IPW_TYPES_H
#define UART_IPW_TYPES_H

/**
*   @file
*   @internal
*   @addtogroup UART_IPW_DRIVER
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
#include "Std_Types.h"
#include "CDD_Uart_Defines.h"
#include "Lpuart_Uart_Ip_Types.h"
#include "Flexio_Uart_Ip_Types.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define UART_IPW_TYPES_VENDOR_ID                    43
#define UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION     7
#define UART_IPW_TYPES_AR_RELEASE_REVISION_VERSION  0
#define UART_IPW_TYPES_SW_MAJOR_VERSION             5
#define UART_IPW_TYPES_SW_MINOR_VERSION             0
#define UART_IPW_TYPES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/*Checks against Lpuart_Uart_Ip_Types.h */
#if (UART_IPW_TYPES_VENDOR_ID!= LPUART_UART_IP_TYPES_VENDOR_ID)
    #error "Uart_Ipw_Types.h and Lpuart_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION   != LPUART_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION   != LPUART_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_TYPES_AR_RELEASE_REVISION_VERSION!= LPUART_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Uart_Ipw_Types.h and Lpuart_Uart_Ip_Types.h are different"
#endif
#if ((UART_IPW_TYPES_SW_MAJOR_VERSION!= LPUART_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (UART_IPW_TYPES_SW_MINOR_VERSION!= LPUART_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (UART_IPW_TYPES_SW_PATCH_VERSION!= LPUART_UART_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw_Types.h and Lpuart_Uart_Ip_Types.h are different"
#endif

/*Checks against Flexio_Uart_Ip_Types.h */
#if (UART_IPW_TYPES_VENDOR_ID!= FLEXIO_UART_IP_TYPES_VENDOR_ID)
    #error "Uart_Ipw_Types.h and Flexio_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION   != FLEXIO_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION   != FLEXIO_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_TYPES_AR_RELEASE_REVISION_VERSION!= FLEXIO_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw_Types.h and Flexio_Uart_Ip_Types.h are different"
#endif
#if ((UART_IPW_TYPES_SW_MAJOR_VERSION!= FLEXIO_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (UART_IPW_TYPES_SW_MINOR_VERSION!= FLEXIO_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (UART_IPW_TYPES_SW_PATCH_VERSION!= FLEXIO_UART_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw_Types.h and Flexio_Uart_Ip_Types.h are different"
#endif

/* Checks against CDD_Uart_Defines.h */
#if (UART_IPW_TYPES_VENDOR_ID != UART_DEFINES_VENDOR_ID_CFG)
    #error "Uart_Ipw_Types.h and CDD_Uart_Defines.h have different vendor ids"
#endif
#if ((UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != UART_DEFINES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != UART_DEFINES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (UART_IPW_TYPES_AR_RELEASE_REVISION_VERSION != UART_DEFINES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Uart_Ipw_Types.h and CDD_Uart_Defines.h are different"
#endif
/* Check if current file and CDD_Uart_Defines.h header file are of the same Software version */
#if ((UART_IPW_TYPES_SW_MAJOR_VERSION != UART_DEFINES_SW_MAJOR_VERSION_CFG) || \
     (UART_IPW_TYPES_SW_MINOR_VERSION != UART_DEFINES_SW_MINOR_VERSION_CFG) || \
     (UART_IPW_TYPES_SW_PATCH_VERSION != UART_DEFINES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Uart_Ipw_Types.h and CDD_Uart_Defines.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Std_Types.h header file are of the same Autosar version */
    #if ((UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Uart_Ipw_Types.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/**
* @internal
* @brief The hardware ip supported by the Uart driver
*/
typedef enum
{

    LPUART_IP   = 0,          /**< @brief Lpuart Ip  */
    FLEXIO_IP   = 1           /**< @brief Flexio Ip  */
}
Uart_Ipw_HwChannelType;

/**
 * @brief Define the enum of the Events which can trigger UART callback
 *
 * @details This enum should include the Events for all platforms
 *
 *
 */
/* implements   Uart_EventType_enum */
typedef enum
{
    UART_EVENT_RX_FULL      = 0x00U,    /**< @brief Rx buffer is full */
    UART_EVENT_TX_EMPTY     = 0x01U,    /**< @brief Tx buffer is empty */
    UART_EVENT_END_TRANSFER = 0x02U,    /**< @brief The current transfer is ending */
    UART_EVENT_ERROR        = 0x03U,    /**< @brief An error occured during transfer */
#if (UART_HAS_TIMEOUT_INTERRUPT_ENABLED == STD_ON)
    UART_EVENT_IDLE_STATE   = 0x04U     /**< @brief The idle state of the reception line is generated*/
#endif
} Uart_EventType;

/**
 * @brief Baudrate values supported by Uart driver.
 *
 *
 *
 */
/* implements   Uart_BaudrateType_enum */
typedef enum
{
  UART_BAUDRATE_1200   = 1200U,
  UART_BAUDRATE_2400   = 2400U,
  UART_BAUDRATE_4800   = 4800U,
  UART_BAUDRATE_7200   = 7200U,
  UART_BAUDRATE_9600   = 9600U,
  UART_BAUDRATE_14400  = 14400U,
  UART_BAUDRATE_19200  = 19200U,
  UART_BAUDRATE_28800  = 28800U,
  UART_BAUDRATE_38400  = 38400U,
  UART_BAUDRATE_57600  = 57600U,
  UART_BAUDRATE_115200 = 115200U,
  UART_BAUDRATE_230400 = 230400U,
  UART_BAUDRATE_460800 = 460800U,
  UART_BAUDRATE_921600 = 921600U,
  UART_BAUDRATE_1843200 = 1843200U
}Uart_BaudrateType;
/**
 * @brief Uart callback notification signature.
 *
 *
 *
 */
/* implements     Uart_CallbackType_Type */
typedef void (*Uart_CallbackType)(uint8 Channel,
                                  Uart_EventType Event);
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @internal
* @brief The Ip configuration structure pointer
*/
typedef struct
{
    const Lpuart_Uart_Ip_UserConfigType *LpuartUserConfig;     /**< @brief Lpuart Ip configuration structure  */
    const Flexio_Uart_Ip_UserConfigType *FlexioUartUserConfig; /**< @brief Flexio Uart Ip configuration structure  */
}
Uart_Ipw_IpConfigType;

/**
* @internal
* @brief   Structure which brings together all the hardware
*          specific information regarding a channel
* @details This structure contains a pointer to the
*          Ip configuration structure, the type of hardware instance and
*          the number of it.
*/
typedef struct
{
    uint32 UartHwChannel;              /**< @brief Uart Hardware Channel.*/
    Uart_Ipw_HwChannelType UartIpType; /**< @brief Type of Hardware interface configured.*/
    Uart_CallbackType Callback;     /**< @brief User Callback to invoke for Uart Events */
    const Uart_Ipw_IpConfigType * UserConfig; /**< @brief Pointer to the Ip configuration structure.*/
}
Uart_Ipw_HwConfigType;
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

#endif /*UART_IPW_TYPES_H*/
