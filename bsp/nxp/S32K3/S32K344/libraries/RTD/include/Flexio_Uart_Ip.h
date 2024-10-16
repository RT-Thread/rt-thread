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

#ifndef FLEXIO_UART_IP_H
#define FLEXIO_UART_IP_H

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
#include "Flexio_Uart_Ip_Cfg.h"
#include "Mcal.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_UART_IP_VENDOR_ID                    43
#define FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION     4
#define FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION     7
#define FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION  0
#define FLEXIO_UART_IP_SW_MAJOR_VERSION             5
#define FLEXIO_UART_IP_SW_MINOR_VERSION             0
#define FLEXIO_UART_IP_SW_PATCH_VERSION             0
/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Flexio_Uart_Ip_Cfg.h */
#if (FLEXIO_UART_IP_VENDOR_ID != FLEXIO_UART_IP_CFG_VENDOR_ID)
    #error "Flexio_Uart_Ip.h and Flexio_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION    != FLEXIO_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION    != FLEXIO_UART_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION != FLEXIO_UART_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip.h and Flexio_Uart_Ip_Cfg.h are different"
#endif
#if ((FLEXIO_UART_IP_SW_MAJOR_VERSION != FLEXIO_UART_IP_CFG_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_SW_MINOR_VERSION != FLEXIO_UART_IP_CFG_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_SW_PATCH_VERSION != FLEXIO_UART_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip.h and Flexio_Uart_Ip_Cfg.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of Flexio_Uart_Ip.h and Mcal.h are different"
    #endif
#endif
#if (FLEXIO_UART_IP_IS_USING == STD_ON)
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
/* Calling the external Configuration symbols defined by FlexIO_Uart_Ip_Cfg.h */
FLEXIO_UART_IP_CONFIG_EXT
#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

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
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

/*!
 * @brief Initializes an Flexio UART operation channel.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the Flexio UART clock source in the application to initialize the Flexio UART.
 *
 * @param Channel  FLEXIO peripheral channel number
 * @param UserConfig Pointer to the Flexio over Uart user configuration structure.
 * @return void
 */
void Flexio_Uart_Ip_Init(const uint8 Channel,
                         const Flexio_Uart_Ip_UserConfigType * UserConfig);

/*!
 * @brief Shuts down the Flexio UART by disabling interrupts and transmitter/receiver.
 *
 * @param Channel  FLEXIO peripheral channel number
 * @return Error or success status returned by API
 */
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_Deinit(const uint8 Channel);

/*!
 * @brief Returns the Flexio UART baud rate.
 *
 * This function returns the Flexio UART configured baud rate.
 *
 * @param Channel  FLEXIO peripheral channel number
 * @param[out] BaudRate Pointer to location where the baudrate value will be provided
 */
void Flexio_Uart_Ip_GetBaudRate(const uint8 Channel, uint32 * BaudRate);

/*!
 * @brief Configures the Flexio Uart baud rate.
 *
 * This function configures the Flexio Uart baud rate.
 * In some Flexio Uart channels the user must disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all Flexio Uarts to ensure safe operation.
 *
 * @param Channel  Flexio Uart channel number.
 * @param DesiredBaudrate Flexio Uart desired baud rate.
 * @param ClockFrequency Clock Frequency of Flexio Uart channel.
 * @return FLEXIO_UART_IP_STATUS_BUSY if called during an on-going transfer, FLEXIO_UART_IP_STATUS_SUCCESS otherwise
 */
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_SetBaudRate(const uint8 Channel,
                                                     const Flexio_Uart_Ip_BaudrateType DesiredBaudrate,
                                                     const uint32 ClockFrequency);

/*!
 * @brief Perform a Asynchronous UART transmission
 *
 * This function sends a block of data and returns immediately.
 * The rest of the transmission is handled by the interrupt service routine (if the driver
 * is initialized in interrupt mode)
 *
 * @param Channel    FLEXIO peripheral channel number
 * @param TxBuff    pointer to the data to be transferred
 * @param TxSize    length in bytes of the data to be transferred
 * @return    Error or success status returned by API
 */
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_AsyncSend(const uint8 Channel,
                                                   const uint8 * TxBuff,
                                                   const uint32 TxSize);

/*!
 * @brief Transfer multiple bytes of data using polling method.
 * @param Channel   FLEXIO peripheral channel number
 * @param TxBuff    pointer to the data to be transferred
 * @param TxSize    length in bytes of the data to be transferred
 * @param Timeout   value in microseconds.
 * @return    Error or success status returned by API
 */
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_SyncSend(const uint8 Channel,
                                                  const uint8 * TxBuff,
                                                  const uint32 TxSize,
                                                  const uint32 Timeout);

/*!
 * @brief Perform a Asynchronous UART reception
 *
 * This function receives a block of data and returns immediately.
 * The rest of the transmission is handled by the interrupt service routine (if the driver
 * is initialized in interrupt mode) or by the Flexio_Uart_Ip_GetStatus() function (if
 * the driver is initialized in polling mode).
 *
 * @param Channel    FLEXIO peripheral channel number
 * @param RxBuff    source buffer containing 8-bit data chars to receive
 * @param RxSize    the number of bytes to receive
 * @return    Error or success status returned by API
 */
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_AsyncReceive(const uint8 Channel,
                                                      uint8 * RxBuff,
                                                      const uint32 RxSize);

/*!
 * @brief Receive multiple bytes of data using polling method.
 *
 * This function receives a block of data and returns immediately.
 * The rest of the transmission is handled by the Flexio_Uart_Ip_GetStatus() function to initialized in polling mode.
 *
 * @param Channel   FLEXIO peripheral channel number
 * @param RxBuff    buffer pointer where the bytes will be received
 * @param RxSize    size of data need to be sent in unit of byte
 * @param Timeout   timeout value in microsecond
 * @return    Error or success status returned by API
 */
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_SyncReceive(const uint8 Channel,
                                                     uint8 * RxBuff,
                                                     const uint32 RxSize,
                                                     const uint32 Timeout);

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_GetStatus
 * Description   : Get the status of the current non-blocking UART transaction
 * @param Channel    FLEXIO peripheral channel number
 * @param BytesRemaining    Number of remaining bytes to be transferred.
 * Implements : Flexio_Uart_Ip_GetStatus_Activity
 *
 *END**************************************************************************/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_GetStatus(const uint8 Channel, uint32 *BytesRemaining);

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CompleteSendUsingDma
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * @param Channel    FLEXIO peripheral channel number
 *
 *END**************************************************************************/
void Flexio_Uart_Ip_CompleteSendUsingDma(uint8 Channel);

/**
 * @internal
 * @brief   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a part of callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * @param Channel Flexio channel number
 * @return void
 */
void Flexio_Uart_Ip_CompleteReceiveUsingDma(uint8 Channel);

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_AbortTransferData
 * Description   : This function terminates an non-blocking FLEXIO transmission
 * early. During a non-blocking FLEXIO transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 * @param Channel  Flexio Uart channel number.
 * @return FLEXIO_UART_IP_STATUS_ERROR if the transfer process has not fully completed,
 *         FLEXIO_UART_IP_STATUS_SUCCESS if the transfer process has successfully completed
 * Implements    : Flexio_Uart_Ip_AbortTransferData_Activity
 *END**************************************************************************/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_AbortTransferData(const uint8 Channel);

/*!
 * @brief Sets the internal driver reference to the tx buffer.
 *
 * This function can be called from the tx callback to provide the driver
 * with a new buffer, for continuous transmission.
 *
 * @param Channel  Flexio Uart channel number
 * @param TxData  source buffer containing 8-bit data chars to send
 * @param TxSize  the number of bytes to send
 * @return void
 */
void Flexio_Uart_Ip_SetTxBuffer(const uint8 Channel,
                                const uint8 * TxData,
                                const uint32 TxSize);

/*!
 * @brief Sets the internal driver reference to the rx buffer.
 *
 * This function can be called from the rx callback to provide the driver
 * with a new buffer, for continuous reception.
 *
 * @param Channel  FLEXIO channel number
 * @param RxData  destination buffer containing 8-bit data chars to receive
 * @param RxSize  the number of bytes to receive
 * @return void
 */
void Flexio_Uart_Ip_SetRxBuffer(const uint8 Channel,
                                uint8 * RxData,
                                const uint32 RxSize);


#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"
#endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FLEXIO_UART_IP_H */
