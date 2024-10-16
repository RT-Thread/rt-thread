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

#ifndef FLEXIO_UART_IP_TYPES_H
#define FLEXIO_UART_IP_TYPES_H

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
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Flexio_Uart_Ip_Defines.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_UART_IP_TYPES_VENDOR_ID                    43
#define FLEXIO_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define FLEXIO_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION     7
#define FLEXIO_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION  0
#define FLEXIO_UART_IP_TYPES_SW_MAJOR_VERSION             5
#define FLEXIO_UART_IP_TYPES_SW_MINOR_VERSION             0
#define FLEXIO_UART_IP_TYPES_SW_PATCH_VERSION             0


/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Flexio_Uart_Ip_Defines.h */
#if (FLEXIO_UART_IP_DEFINES_VENDOR_ID != FLEXIO_UART_IP_TYPES_VENDOR_ID)
    #error "Flexio_Uart_Ip_Defines.h and Flexio_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION    != FLEXIO_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION    != FLEXIO_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION != FLEXIO_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_Defines.h and Flexio_Uart_Ip_Types.h are different"
#endif
#if ((FLEXIO_UART_IP_DEFINES_SW_MAJOR_VERSION != FLEXIO_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_DEFINES_SW_MINOR_VERSION != FLEXIO_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_DEFINES_SW_PATCH_VERSION != FLEXIO_UART_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip_Defines.h and Flexio_Uart_Ip_Types.h are different"
#endif
/* Check if current file and Std_Types.h header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((FLEXIO_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Flexio_Uart_Ip_Types.h and Std_Types.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       TYPES AND MACROS
==================================================================================================*/

/** FLEXIO Instance support . */
#define FLEXIO_HW_INSTANCE                       (0u)
/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*! @brief Driver type: Interrupts/DMA
 * Implements : Flexio_Uart_IP_DriverType_Class
 */
typedef enum
{
    FLEXIO_UART_IP_DRIVER_TYPE_INTERRUPTS    = 0U,  /*!< Driver uses interrupts for data transfers */
    FLEXIO_UART_IP_DRIVER_TYPE_DMA           = 1U,  /*!< Driver uses DMA for data transfers */
} Flexio_Uart_IP_DriverType;

 /*!
 * @brief flexio_uart driver direction (tx or rx)
 *
 * This structure describes the direction configuration options for the flexio_uart driver.
 * Implements : flexio_uart_driver_direction_t_Class
 */
typedef enum
{
    FLEXIO_UART_IP_DIRECTION_TX       = 0x01U,    /*!< Tx UART driver */
    FLEXIO_UART_IP_DIRECTION_RX       = 0x00U,    /*!< Rx UART driver */
} Flexio_Uart_Ip_DirectionType;

/**
 * @brief Define the enum of the Events which can trigger UART callback
 *
 * This enum should include the Events for all platforms
 *
 *
 */
typedef enum
{
    FLEXIO_UART_IP_EVENT_RX_FULL      = 0x00U,    /**< @brief Rx buffer is full */
    FLEXIO_UART_IP_EVENT_TX_EMPTY     = 0x01U,    /**< @brief Tx buffer is empty */
    FLEXIO_UART_IP_EVENT_END_TRANSFER = 0x02U,    /**< @brief The current transfer is ending */
    FLEXIO_UART_IP_EVENT_ERROR        = 0x03U,    /**< @brief An error occured during transfer */
} Flexio_Uart_Ip_EventType;

 /*!
 * Implements : Driver status type.
 */
typedef enum
{
    /* UART specific error codes */
    FLEXIO_UART_IP_STATUS_SUCCESS                     = 0x000U,  /*!< Operation has been successfully  */
    FLEXIO_UART_IP_STATUS_ERROR                       = 0x001U,  /*!< Operation has had error  */
    FLEXIO_UART_IP_STATUS_BUSY                        = 0x002U,  /*!< Function is called during an on-going transfer  */
    FLEXIO_UART_IP_STATUS_DMA_ERROR                   = 0x003U,  /*!< Operation has had DMA error  */
    FLEXIO_UART_IP_STATUS_TX_UNDERRUN                 = 0x201U,  /*!< TX underrun error */
    FLEXIO_UART_IP_STATUS_RX_OVERRUN                  = 0x202U,  /*!< RX overrun error */
    FLEXIO_UART_IP_STATUS_ABORTED                     = 0x204U,  /*!< A transfer was aborted */
    FLEXIO_UART_IP_STATUS_TIMEOUT                     = 0x206U
}Flexio_Uart_Ip_StatusType;

/**
 * @brief Define the enum of the baudrate values that should be set for Uart
 *
 */

typedef enum
{
    FLEXIO_UART_BAUDRATE_1200   = 1200U,
    FLEXIO_UART_BAUDRATE_2400   = 2400U,
    FLEXIO_UART_BAUDRATE_4800   = 4800U,
    FLEXIO_UART_BAUDRATE_7200   = 7200U,
    FLEXIO_UART_BAUDRATE_9600   = 9600U,
    FLEXIO_UART_BAUDRATE_14400  = 14400U,
    FLEXIO_UART_BAUDRATE_19200  = 19200U,
    FLEXIO_UART_BAUDRATE_28800  = 28800U,
    FLEXIO_UART_BAUDRATE_38400  = 38400U,
    FLEXIO_UART_BAUDRATE_57600  = 57600U,
    FLEXIO_UART_BAUDRATE_115200 = 115200U,
    FLEXIO_UART_BAUDRATE_230400 = 230400U,
    FLEXIO_UART_BAUDRATE_460800 = 460800U,
    FLEXIO_UART_BAUDRATE_921600 = 921600U,
    FLEXIO_UART_BAUDRATE_1843200 = 1843200U
}Flexio_Uart_Ip_BaudrateType;


/*! @brief FLEXIO Timer decrement options
 *
 *
 */
typedef enum
{
    FLEXIO_TIMER_DECREMENT_FXIO_CLK_SHIFT_TMR = 0x00U,  /*!< Decrement counter on FlexIO clock, Shift clock equals Timer output. */
    FLEXIO_TIMER_DECREMENT_FXIO_CLK_DIV_16    = 0x04U,  /*!< Decrement counter on FlexIO clock divided by 16, Shift clock equals Timer output. */
    FLEXIO_TIMER_DECREMENT_FXIO_CLK_DIV_256   = 0x05U,  /*!< Decrement counter on FlexIO clock divided by 256, Shift clock equals Timer output. */
} Flexio_Uart_Ip_TimerDecrementType;

/*! @brief FLEXIO number of bits in a character
 *
 *
 */
typedef enum
{
    FLEXIO_UART_IP_8_BITS_PER_CHAR  = 0x8U /*!< 8-bit data characters */
} Flexio_Uart_Ip_BitCountPerCharType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*!
 * @brief Driver internal context structure
 *
 * This structure is used by the flexio_uart driver for its internal logic. It must
 * be provided by the application through the Flexio_Uart_Ip_Init() function, then
 * it cannot be freed until the driver is de-initialized using Flexio_Uart_Ip_Deinit().
 * The application should make no assumptions about the content of this structure.
 */
/*! @cond DRIVER_INTERNAL_USE_ONLY */

/**
 * @brief Callback for all peripherals which support UART features
 *
 *
 */
typedef void (*Flexio_Uart_Ip_CallbackType)(const uint8 HwChannel,
                                            const Flexio_Uart_Ip_EventType Event,
                                            const void *UserData);
/*!
 * @brief Runtime  of the FLEXIO driver.
 *
 * Note that the caller provides memory for the driver  structures during
 * initialization because the driver does not statically allocate memory.
 *
 * Implements : Flexio_Uart_Ip_StateStructureType
 */
typedef struct
{
/*! @cond DRIVER_INTERNAL_USE_ONLY */
    volatile uint8 * RxData;                                /**< @brief Receive buffer. */
    volatile const uint8 * TxData;                          /**< @brief Transmit buffer. */
    volatile uint32 RemainingBytes;                       /**< @brief Number of remaining bytes to be transferred. */
    uint32 BaudRate;                                      /**< @brief Baud rate in hertz */
    volatile Flexio_Uart_Ip_StatusType Status;              /**< @brief Current status of the driver */
    volatile boolean DriverIdle;                            /**< @brief Idle/busy state of the receiver */
    uint8 TxFlush;                                         /**< @brief Used for flushing Tx buffer before ending a transmission */
/*! @endcond */
} Flexio_Uart_Ip_StateStructureType;

 /*!
 * @brief Driver configuration structure
 *
 * This structure is used to provide configuration parameters for the flexio_uart driver at initialization time.
 * Implements : Flexio_Uart_Ip_UserConfigType_Class
 */
typedef struct
{
    uint32 Channel;                                /**< @brief Flexio Uart Channel has been configured. Note that Make sure
                                                                  the Channel is used in all API corresponds to this parameter */
    Flexio_Uart_IP_DriverType DriverType;            /**< @brief Driver type: Interrupts/DMA */
    uint16 Divider;                                  /**< @brief Baudrate divider */
    Flexio_Uart_Ip_TimerDecrementType TimerDec;      /**< @brief The source of the Timer decrement and the source of the Shift clock */
    uint32 BaudRate;                               /**< @brief Baud rate in hertz */
    Flexio_Uart_Ip_BitCountPerCharType BitCount;     /**< @brief Number of bits per word */
    Flexio_Uart_Ip_DirectionType Direction;          /**< @brief Driver direction: Tx or Rx */
    uint8 DataPin;                                  /**< @brief Flexio pin to use as Tx or Rx pin */
    Flexio_Uart_Ip_CallbackType Callback;           /**< @brief User callback function. Note that this function will be
                                                                 called from the interrupt service routine, so its
                                                                 execution time should be as small as possible. It can be
                                                                 NULL_PTR if it is not needed */
    void *CallbackParam;                             /**< @brief Parameter for the callback function */
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    uint8 DmaChannel;                               /**< @brief DMA channel number. Only used in DMA mode */
#endif
    Flexio_Uart_Ip_StateStructureType *StateStruct;
} Flexio_Uart_Ip_UserConfigType;

#ifdef __cplusplus
}
#endif

/**  @} */

#endif /* FLEXIO_UART_IP_TYPES_H */
