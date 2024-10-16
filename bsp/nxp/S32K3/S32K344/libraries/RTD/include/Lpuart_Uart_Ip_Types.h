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

#ifndef LPUART_UART_IP_TYPES_H
#define LPUART_UART_IP_TYPES_H

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
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Lpuart_Uart_Ip_HwAccess.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_UART_IP_TYPES_VENDOR_ID                    43
#define LPUART_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define LPUART_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION     7
#define LPUART_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION  0
#define LPUART_UART_IP_TYPES_SW_MAJOR_VERSION             5
#define LPUART_UART_IP_TYPES_SW_MINOR_VERSION             0
#define LPUART_UART_IP_TYPES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Lpuart_Uart_Ip_Types.h */
#if (LPUART_UART_IP_HWACCESS_VENDOR_ID != LPUART_UART_IP_TYPES_VENDOR_ID)
    #error "Lpuart_Uart_Ip_HwAccess.h and Lpuart_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION    != LPUART_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION    != LPUART_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION != LPUART_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip_HwAccess.h and Lpuart_Uart_Ip_Types.h are different"
#endif
#if ((LPUART_UART_IP_HWACCESS_SW_MAJOR_VERSION != LPUART_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_SW_MINOR_VERSION != LPUART_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_SW_PATCH_VERSION != LPUART_UART_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lpuart_Uart_Ip_HwAccess.h and Lpuart_Uart_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Std_Types.h header file are of the same Autosar version */
    #if ((LPUART_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Lpuart_Uart_Ip_Types.h and Std_Types.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       TYPES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/**
 * @brief Type of UART transfer (based on interrupts or DMA).
 *
 *
 */
typedef enum
{
    LPUART_UART_IP_USING_DMA         = 0U,    /**< @brief The driver will use DMA to perform UART transfer */
    LPUART_UART_IP_USING_INTERRUPTS  = 1U     /**< @brief The driver will use interrupts to perform UART transfer */
} Lpuart_Uart_Ip_TransferType;


/**
 * @brief Driver status type.
 *
 *
 * */
typedef enum
{
    LPUART_UART_IP_STATUS_SUCCESS                    = 0x00U,  /**< @brief Generic operation success status */
    LPUART_UART_IP_STATUS_ERROR                      = 0x01U,  /**< @brief Generic operation failure status */
    LPUART_UART_IP_STATUS_BUSY                       = 0x02U,  /**< @brief Generic operation busy status */
    LPUART_UART_IP_STATUS_TIMEOUT                    = 0x03U,  /**< @brief Generic operation timeout status */
    LPUART_UART_IP_STATUS_TX_UNDERRUN                = 0x04U,  /**< @brief TX underrun error */
    LPUART_UART_IP_STATUS_RX_OVERRUN                 = 0x05U,  /**< @brief RX overrun error */
    LPUART_UART_IP_STATUS_ABORTED                    = 0x06U,  /**< @brief* A transfer was aborted */
    LPUART_UART_IP_STATUS_FRAMING_ERROR              = 0x07U,  /**< @brief Framing error */
    LPUART_UART_IP_STATUS_PARITY_ERROR               = 0x08U,  /**< @brief Parity error */
    LPUART_UART_IP_STATUS_NOISE_ERROR                = 0x09U,  /**< @brief Noise error */
    LPUART_UART_IP_STATUS_DMA_ERROR                  = 0x10U,  /**< @brief DMA error */
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    LPUART_UART_IP_STATUS_RX_IDLE_STATE              = 0x11U   /**< @brief The idle state of the reception line is generated */
#endif
} Lpuart_Uart_Ip_StatusType;


/**
 * @brief Define the enum of the Events which can trigger UART callback
 *
 * This enum should include the Events for all platforms
 *
 *
 */
typedef enum
{
    LPUART_UART_IP_EVENT_RX_FULL      = 0x00U,    /**< @brief Rx buffer is full */
    LPUART_UART_IP_EVENT_TX_EMPTY     = 0x01U,    /**< @brief Tx buffer is empty */
    LPUART_UART_IP_EVENT_END_TRANSFER = 0x02U,    /**< @brief The current transfer is ending */
    LPUART_UART_IP_EVENT_ERROR        = 0x03U,    /**< @brief An error occured during transfer */
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    LPUART_UART_IP_EVENT_IDLE_STATE   = 0x04U     /**< @brief The idle state of the reception line is generated*/
#endif
} Lpuart_Uart_Ip_EventType;

/**
 * @brief Define the enum of the baudrate values that should be set for Uart
 *
 */

typedef enum
{
  LPUART_UART_BAUDRATE_1200   = 1200U,
  LPUART_UART_BAUDRATE_2400   = 2400U,
  LPUART_UART_BAUDRATE_4800   = 4800U,
  LPUART_UART_BAUDRATE_7200   = 7200U,
  LPUART_UART_BAUDRATE_9600   = 9600U,
  LPUART_UART_BAUDRATE_14400  = 14400U,
  LPUART_UART_BAUDRATE_19200  = 19200U,
  LPUART_UART_BAUDRATE_28800  = 28800U,
  LPUART_UART_BAUDRATE_38400  = 38400U,
  LPUART_UART_BAUDRATE_57600  = 57600U,
  LPUART_UART_BAUDRATE_115200 = 115200U,
  LPUART_UART_BAUDRATE_230400 = 230400U,
  LPUART_UART_BAUDRATE_460800 = 460800U,
  LPUART_UART_BAUDRATE_921600 = 921600U,
  LPUART_UART_BAUDRATE_1843200 = 1843200U

}Lpuart_Uart_Ip_BaudrateType;
/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
 * @brief Callback for all peripherals which support UART features
 *
 *
 */
typedef void (*Lpuart_Uart_Ip_CallbackType)(const uint8 HwInstance,
                                            const Lpuart_Uart_Ip_EventType Event,
                                            const void *UserData);


/*!
 * @brief Runtime  of the LPUART driver.
 *
 * Note that the caller provides memory for the driver  structures during
 * initialization because the driver does not statically allocate memory.
 *
 * Implements : Lpuart_Uart_Ip_StateStructureType
 */
typedef struct
{
    uint32 BaudRate;                                     /**< @brief Variable that indicates if structure belongs to an instance already initialized.*/
    const uint8 * TxBuff;                                  /**< @brief The buffer of data being sent.*/
    uint8 * RxBuff;                                        /**< @brief The buffer of received data.*/
    volatile uint32 TxSize;                              /**< @brief The remaining number of bytes to be transmitted. */
    volatile uint32 RxSize;                              /**< @brief The remaining number of bytes to be received. */
    volatile boolean IsTxBusy;                             /**< @brief True if there is an active transmit.*/
    volatile boolean IsRxBusy;                             /**< @brief True if there is an active receive.*/
    volatile Lpuart_Uart_Ip_StatusType TransmitStatus;     /**< @brief Status of last driver transmit operation */
    volatile Lpuart_Uart_Ip_StatusType ReceiveStatus;      /**< @brief Status of last driver receive operation */
}  Lpuart_Uart_Ip_StateStructureType;


/*! @brief LPUART configuration structure
 *
 * Implements : Lpuart_Uart_Ip_UserConfigType
 */
typedef struct
{
    uint32 BaudRate;                                   /**< @brief Baudrate value*/
    uint32 BaudRateDivisor;                            /**< @brief Baud clock divisor*/
    uint8 BaudOverSamplingRatio;                        /**< @brief Over sampling ratio*/

    Lpuart_Uart_Ip_ParityModeType ParityMode;            /*!< @brief Parity mode, disabled (default), even, odd */
    Lpuart_Uart_Ip_StopBitCountType StopBitsCount;       /*!< @brief Number of stop bits, 1 stop bit (default) or 2 stop bits */
    Lpuart_Uart_Ip_BitCountPerCharType BitCountPerChar;  /*!< @brief Number of bits in a character (8-default, 9 or 10);
                                                                for 9/10 bits chars, users must provide appropriate buffers
                                                                to the send/receive functions (bits 8/9 in subsequent bytes);
                                                                for DMA transmission only 8-bit char is supported. */
    Lpuart_Uart_Ip_TransferType TransferType;            /*!< @briefType of LPUART transfer (interrupt/dma based) */
    Lpuart_Uart_Ip_CallbackType Callback;             /**< @brief Callback to invoke for handle uart event */
    void * CallbackParam;                              /**< @brief User callback parameter pointer.*/
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    uint32 RxDMAChannel;                                 /**< @brief DMA channel number for DMA-based rx.
                                                                If DMA mode is not used this field will be ignored. */
    uint32 TxDMAChannel;                                 /**< @brief DMA channel number for DMA-based tx.
                                                                If DMA mode is not used this field will be ignored. */
#endif
    Lpuart_Uart_Ip_StateStructureType *StateStruct;
} Lpuart_Uart_Ip_UserConfigType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/**  @} */

#endif /* LPUART_UART_IP_TYPES_H */
