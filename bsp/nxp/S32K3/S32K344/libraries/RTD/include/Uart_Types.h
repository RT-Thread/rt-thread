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

#ifndef UART_TYPES_H
#define UART_TYPES_H

/**
*   @file
*   @defgroup uart_driver UART Driver
*   @addtogroup  uart_driver UART Driver
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
#include "CDD_Uart_Defines.h"
#include "Uart_Ipw_Types.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define UART_TYPES_VENDOR_ID                    43
#define UART_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define UART_TYPES_AR_RELEASE_MINOR_VERSION     7
#define UART_TYPES_AR_RELEASE_REVISION_VERSION  0
#define UART_TYPES_SW_MAJOR_VERSION             5
#define UART_TYPES_SW_MINOR_VERSION             0
#define UART_TYPES_SW_PATCH_VERSION             0
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/*Checks against CDD_Uart_Defines.h */
#if (UART_TYPES_VENDOR_ID != UART_DEFINES_VENDOR_ID_CFG)
    #error "Uart_Types.h and CDD_Uart_Defines.h have different vendor ids"
#endif
#if ((UART_TYPES_AR_RELEASE_MAJOR_VERSION    != UART_DEFINES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (UART_TYPES_AR_RELEASE_MINOR_VERSION   != UART_DEFINES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (UART_TYPES_AR_RELEASE_REVISION_VERSION!= UART_DEFINES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AUTOSAR Version Numbers of Uart_Types.h and CDD_Uart_Defines.h are different"
#endif
#if ((UART_TYPES_SW_MAJOR_VERSION!= UART_DEFINES_SW_MAJOR_VERSION_CFG) || \
     (UART_TYPES_SW_MINOR_VERSION!= UART_DEFINES_SW_MINOR_VERSION_CFG) || \
     (UART_TYPES_SW_PATCH_VERSION!= UART_DEFINES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Uart_Types.h and CDD_Uart_Defines.h are different"
#endif

/*Checks against Uart_Ipw_Types.h */
#if (UART_TYPES_VENDOR_ID != UART_IPW_TYPES_VENDOR_ID)
    #error "Uart_Types.h and Uart_Ipw_Types.h have different vendor ids"
#endif
#if ((UART_TYPES_AR_RELEASE_MAJOR_VERSION    != UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (UART_TYPES_AR_RELEASE_MINOR_VERSION   != UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (UART_TYPES_AR_RELEASE_REVISION_VERSION!= UART_IPW_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Types.h and Uart_Ipw_Types.h are different"
#endif
#if ((UART_TYPES_SW_MAJOR_VERSION!= UART_IPW_TYPES_SW_MAJOR_VERSION) || \
     (UART_TYPES_SW_MINOR_VERSION!= UART_IPW_TYPES_SW_MINOR_VERSION) || \
     (UART_TYPES_SW_PATCH_VERSION!= UART_IPW_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Types.h and Uart_Ipw_Types.h are different"
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_RUNTIME_ERROR_DETECT == STD_ON))

/**
* @brief            Driver not initialized
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_UNINIT               ((uint8)0x01U)

/**
* @brief Invalid channel given as parameter
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_INVALID_CHANNEL      ((uint8)0x02U)

/**
* @brief Invalid channel given as parameter
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_INVALID_POINTER      ((uint8)0x03U)

/**
* @brief Driver already initialized
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_ALREADY_INITIALIZED  ((uint8)0x04U)

/**
* @brief Invalid partitionid
*
*/
#define UART_E_PARAM_CONFIG         ((uint8)0x05U)

/**
* @brief Channel is busy, therefore the service can not be executed
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_CHANNEL_BUSY         ((uint8)0x06U)

/**
* @brief Parameter has a wrong value
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_INVALID_PARAMETER    ((uint8)0x07U)

/**
* @brief Timeout occured
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_TIMEOUT              ((uint8)0x08U)

/**
* @brief Invalid pointer for init function parameter
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_INIT_FAILED          ((uint8)0x09U)

/**
* @brief De-Init function for specific HW channel finish unsuccessfully
* @details Errors reported by Det_ReportError() and Det_ReportRuntimeError().
*
*/
#define UART_E_DEINIT_FAILED         ((uint8)0x10U)



/**< @brief API service ID for UART_Init() function
* @details          Parameters used when raising an error or exception.
*
*/
#define UART_INIT_ID                 ((uint8)0x00U)

/**
* @brief API service ID for UART_DeInit() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_DEINIT_ID               ((uint8)0x01U)

/**
* @brief API service ID for UART_SetBaudrate() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_SETBAUDRATE_ID          ((uint8)0x02U)

/**
* @brief API service ID for UART_GetBaudrate() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_GETBAUDRATE_ID          ((uint8)0x03U)

/**
* @brief API service ID for UART_SyncSend() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_SYNCSEND_ID             ((uint8)0x04U)

/**
* @brief API service ID for UART_AsyncReceive() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_ASYNCSEND_ID            ((uint8)0x05U)

/**
* @brief API service ID for UART_SyncReceive() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_SYNCRECEIVE_ID          ((uint8)0x06U)

/**
* @brief API service ID for UART_AsyncSend() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_ASYNCRECEIVE_ID         ((uint8)0x07U)

/**
* @brief API service ID for UART_Abort() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_ABORT_ID                ((uint8)0x08U)

/**
* @brief API service ID for UART_GetStatus() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_GETSTATUS_ID            ((uint8)0x09U)

/**
* @brief API service ID for Uart_GetVersionInfo() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_VERSIONINFO_ID          ((uint8)0x0AU)

/**
* @brief API service ID for UART_SetBuffer() function
* @details Parameters used when raising an error or exception.
*
*/
#define UART_SETBUFFER_ID            ((uint8)0x0BU)
#endif /*EV_ERROR_DETECT == STD_ON) || (UART_RUNTIME_ERROR_DETECT == STD_ON)) */

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/**
* @brief            Driver initialization status.
* @details          This enum contains the values for the driver initialization status.
*/
typedef enum
{
    UART_DRV_UNINIT = 0U,    /**< @brief Driver not initialized */
    UART_DRV_INIT ,          /**< @brief Driver ready */
}
Uart_DrvStatusType;


/**
* @brief          The type operation of an Uart channel.
*/
/* implements     Uart_DataDirectionType_enum */
typedef enum
{
    UART_SEND    = (uint8)0x00U, /**< @brief The sending operation */
    UART_RECEIVE = (uint8)0x01U  /**< @brief The receiving operation */
} Uart_DataDirectionType;

/**
* @brief          Uart operation status type
*/
typedef enum
{
    UART_STATUS_NO_ERROR            =  0x00, /**< @brief Uart operation is successfull  */
    UART_STATUS_OPERATION_ONGOING   =  0x01, /**< @brief Uart operation on going  */
    UART_STATUS_ABORTED             =  0x02, /**< @brief Uart operation aborted  */
    UART_STATUS_FRAMING_ERROR       =  0x03, /**< @brief Uart framing error  */
    UART_STATUS_RX_OVERRUN_ERROR    =  0x04, /**< @brief Uart overrun error  */
    UART_STATUS_PARITY_ERROR        =  0x05, /**< @brief Uart parity error  */
    UART_STATUS_TIMEOUT             =  0x06, /**< @brief Uart operation has timeout  */
    UART_STATUS_NOISE_ERROR         =  0x07, /**< @brief Uart noise error  */
    UART_STATUS_DMA_ERROR           =  0x08, /**< @brief Uart Dma error  */
    UART_STATUS_BREAK_ERROR         =  0x09, /**< @brief Uart break error  */
#if (UART_HAS_TIMEOUT_INTERRUPT_ENABLED == STD_ON)
    UART_STATUS_RX_IDLE_STATE       =  0x0A, /**< @brief Uart receive timeout error  */
#endif
} Uart_StatusType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          Uart channel configuration type structure.
* @details        This is the type of the external data structure containing
*                 the overall initialization data for one Uart Channel.
*                 A pointer to such a structure is provided to the Uart channel
*                 initialization routine for configuration of the Uart hardware
*                 channel.
*
*
*/
/* implements     Uart_ChannelConfigType_structure */
typedef struct
{
    uint8 UartChannelId;                           /**< @brief Uart channel configured  */
#if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    uint32 ChannelPartitionId;                         /**< @brief Partition id on which the Uart channel has been assigned  */
#endif
    uint32 ChannelClockFrequency;                 /**< @brief The clock frequency configured on the given channel  */
    const Uart_Ipw_HwConfigType* UartChannelConfig; /**< @brief Pointer to a lower level channel configuration  */
} Uart_ChannelConfigType;

/**
* @brief          Uart driver configuration type structure.
* @details        This is the type of the pointer to the external data
*                 Uart Channels.
*                 A pointer of such a structure is provided to the Uart driver
*                 initialization routine for configuration of the Uart hardware
*                 channel.
*
*
*
*/
/* implements     Uart_ConfigType_structure */
typedef struct
{
#if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    uint32 PartitionId;                                 /**< @brief Configured of the partition ID  */
#endif
    /**
     * @brief     Hardware channel.
     * @details   Constant pointer of the constant external data
     *            structure containing the overall initialization data
     *            for all the configured Uart Channels.
     */
    const Uart_ChannelConfigType *Configs[UART_CH_MAX_CONFIG];
} Uart_ConfigType;

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

#endif /* UART_Types_H */
