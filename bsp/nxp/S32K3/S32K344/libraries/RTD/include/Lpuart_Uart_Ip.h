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

#ifndef LPUART_UART_IP_H
#define LPUART_UART_IP_H

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
#include "Lpuart_Uart_Ip_Types.h"
#include "Lpuart_Uart_Ip_Cfg.h"
#include "Mcal.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_UART_IP_VENDOR_ID                    43
#define LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION     4
#define LPUART_UART_IP_AR_RELEASE_MINOR_VERSION     7
#define LPUART_UART_IP_AR_RELEASE_REVISION_VERSION  0
#define LPUART_UART_IP_SW_MAJOR_VERSION             5
#define LPUART_UART_IP_SW_MINOR_VERSION             0
#define LPUART_UART_IP_SW_PATCH_VERSION             0
/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Lpuart_Uart_Ip_Types.h */
#if (LPUART_UART_IP_VENDOR_ID != LPUART_UART_IP_TYPES_VENDOR_ID)
    #error "Lpuart_Uart_Ip.h and Lpuart_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION    != LPUART_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION    != LPUART_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_REVISION_VERSION != LPUART_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip.h and Lpuart_Uart_Ip_Types.h are different"
#endif
#if ((LPUART_UART_IP_SW_MAJOR_VERSION != LPUART_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_SW_MINOR_VERSION != LPUART_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_SW_PATCH_VERSION != LPUART_UART_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lpuart_Uart_Ip.h and Lpuart_Uart_Ip_Types.h are different"
#endif

/* Checks against Lpuart_Uart_Ip_Cfg.h */
#if (LPUART_UART_IP_VENDOR_ID != LPUART_UART_IP_CFG_VENDOR_ID)
    #error "Lpuart_Uart_Ip.h and Lpuart_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION    != LPUART_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION    != LPUART_UART_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_REVISION_VERSION != LPUART_UART_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip.h and Lpuart_Uart_Ip_Cfg.h are different"
#endif
#if ((LPUART_UART_IP_SW_MAJOR_VERSION != LPUART_UART_IP_CFG_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_SW_MINOR_VERSION != LPUART_UART_IP_CFG_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_SW_PATCH_VERSION != LPUART_UART_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lpuart_Uart_Ip.h and Lpuart_Uart_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip.h and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
/* Calling the external Configuration symbols defined by Lpuart_Uart_Ip_Cfg.h */
LPUART_UART_IP_CONFIG_EXT
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
 * @brief Initializes an LPUART operation instance.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the LPUART clock source in the application to initialize the LPUART.
 *
 * @param Instance  LPUART instance number
 * @param UserConfig user configuration structure of type #Lpuart_Uart_Ip_UserConfigType
 * @return void
 */
void Lpuart_Uart_Ip_Init(const uint8 Instance, const Lpuart_Uart_Ip_UserConfigType * UserConfig);

/*!
 * @brief Shuts down the LPUART by disabling interrupts and transmitter/receiver.
 *
 * @param Instance  LPUART instance number
 * @return  LPUART_UART_IP_STATUS_SUCCESS if successful;
 *          LPUART_UART_IP_STATUS_ERROR if the progress has not fully completed;
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_Deinit(const uint8 Instance);


/*!
 * @brief Send out multiple bytes of data using polling method.
 *
 * @param   Instance  LPUART instance number.
 * @param   TxBuff The buffer pointer which saves the data to be sent.
 * @param   TxSize Size of data to be sent in unit of byte.
 * @param   Timeout value in microseconds.
 * @return  LPUART_UART_IP_STATUS_SUCCESS if successful;
 *          LPUART_UART_IP_STATUS_BUSY if the resource is busy;
 *          LPUART_UART_IP_STATUS_TIMEOUT if timeout occur
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_SyncSend(const uint8 Instance,
                                                  const uint8 *TxBuff,
                                                  const uint32 TxSize,
                                                  const uint32 Timeout);

/*!
 * @brief Sends data out through the LPUART module using a non-blocking method.
 *  This enables an a-sync method for transmitting data. When used with
 *  a non-blocking receive, the LPUART can perform a full duplex operation.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the transmit status to know when the transmit is complete.
 *
 * @param   Instance  LPUART instance number.
 * @param   TxBuff The buffer pointer which saves the data to be sent.
 * @param   TxSize Size of data to be sent in unit of byte.
 * @return  LPUART_UART_IP_STATUS_SUCCESS if successful;
 *          LPUART_UART_IP_STATUS_BUSY if the resource is busy;
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AsyncSend(const uint8 Instance,
                                                   const uint8 * TxBuff,
                                                   const uint32 TxSize);

/*!
 * @brief Returns whether the previous transmit is complete.
 *
 * @param Instance  LPUART instance number
 * @param BytesRemaining Pointer to value that is populated with the number of bytes that
 *        have been sent in the active transfer
 *        @note In DMA mode, this parameter may not be accurate, in case the transfer completes
 *              right after calling this function; in this edge-case, the parameter will reflect
 *              the initial transfer size, due to automatic reloading of the major loop count
 *              in the DMA transfer descriptor.
 * @return The transmit status.
 * @retval LPUART_UART_IP_STATUS_SUCCESS The transmit has completed successfully.
 * @retval LPUART_UART_IP_STATUS_BUSY The transmit is still in progress. @a bytesRemaining will be
 *         filled with the number of bytes that are yet to be transmitted.
 * @retval LPUART_UART_IP_STATUS_ABORTED The transmit was aborted.
 * @retval LPUART_UART_IP_STATUS_TIMEOUT A timeout was reached.
 * @retval LPUART_UART_IP_STATUS_ERROR An error occurred.
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_GetTransmitStatus(const uint8 Instance, uint32 * BytesRemaining);

/*!
 * @brief Terminates a non-blocking transmission early.
 *
 * @param instance  LPUART instance number
 * @return LPUART_UART_IP_STATUS_ERROR if the transmit process has not fully completed,
 *         LPUART_UART_IP_STATUS_SUCCESS if the transmit process has successfully completed
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AbortSendingData(const uint8 Instance);


/*!
 * @brief Receive multiple bytes of data using polling method.
 *
 *
 * @param   Instance  LPUART instance number.
 * @param   RxBuff The buffer pointer which saves the data to be received.
 * @param   RxSize Size of data need to be received in unit of byte.
 * @param   Timeout value in microseconds.
 * @return  LPUART_UART_IP_STATUS_SUCCESS if the transaction is successful;
 *          LPUART_UART_IP_STATUS_BUSY if the resource is busy;
 *          LPUART_UART_IP_STATUS_RX_OVERRUN if an overrun error occured
 *          LPUART_UART_IP_STATUS_FRAMING_ERROR if a framing error occured
 *          LPUART_UART_IP_STATUS_PARITY_ERROR if a parity error occured
 *          LPUART_UART_IP_STATUS_NOISE_ERROR if a noise error occured
 *          LPUART_UART_IP_STATUS_TIMEOUT if timeout occur
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_SyncReceive(const uint8 Instance,
                                                     uint8 *RxBuff,
                                                     const uint32 RxSize,
                                                     const uint32 Timeout);

/*!
 * @brief Gets data from the LPUART module by using a non-blocking method.
 *  This enables an a-sync method for receiving data. When used with
 *  a non-blocking transmission, the LPUART can perform a full duplex operation.
 *  Non-blocking means that the function returns immediately.
 *  The application has to get the receive status to know when the receive is complete.
 *
 * @param Instance  LPUART instance number
 * @param RxBuff  buffer containing 8-bit read data chars received
 * @param RxSize  the number of bytes to receive
 * @return LPUART_UART_IP_STATUS_SUCCESS if successful;
 *         LPUART_UART_IP_STATUS_BUSY if the resource is busy
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AsyncReceive(const uint8 Instance,
                                                      uint8 * RxBuff,
                                                      const uint32 RxSize);

/*!
 * @brief Returns whether the previous receive is complete.
 *
 * @param Instance  LPUART instance number
 * @param BytesRemaining pointer to value that is filled  with the number of bytes that
 *        still need to be received in the active transfer.
 *        @note In DMA mode, this parameter may not be accurate, in case the transfer completes
 *              right after calling this function; in this edge-case, the parameter will reflect
 *              the initial transfer size, due to automatic reloading of the major loop count
 *              in the DMA transfer descriptor.
 * @return The receive status.
 * @retval LPUART_UART_IP_STATUS_SUCCESS the receive has completed successfully.
 * @retval LPUART_UART_IP_STATUS_BUSY the receive is still in progress. @a bytesReceived will be
 *     filled with the number of bytes that have been received so far.
 * @retval LPUART_UART_IP_STATUS_ABORTED The receive was aborted.
 * @retval LPUART_UART_IP_STATUS_TIMEOUT A timeout was reached.
 * @retval LPUART_UART_IP_STATUS_RX_OVERRUN, LPUART_UART_IP_STATUS_FRAMING_ERROR, LPUART_UART_IP_STATUS_PARITY_ERROR,
           or LPUART_UART_IP_STATUS_NOISE_ERROR, LPUART_UART_IP_STATUS_ERROR An error occurred during reception.
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_GetReceiveStatus(const uint8 Instance, uint32 * BytesRemaining);

/*!
 * @brief Terminates a non-blocking receive early.
 *
 * @param Instance  LPUART instance number
 *
 * @return LPUART_UART_IP_STATUS_ERROR if the receive process has not fully completed,
 *         LPUART_UART_IP_STATUS_SUCCESS if the receive process has successfully completed
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AbortReceivingData(const uint8 Instance);

/*!
 * @brief Configures the LPUART baud rate.
 *
 * This function configures the LPUART baud rate.
 * In some LPUART instances the user must disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param Instance  LPUART instance number.
 * @param DesiredBaudrate LPUART desired baud rate.
 * @param ClockFrequency Clock Frequency of LPUART instance.
 * @return LPUART_UART_IP_STATUS_BUSY if called during an on-going transfer, LPUART_UART_IP_STATUS_SUCCESS otherwise
 */
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_SetBaudRate(const uint8 Instance,
                                                     const Lpuart_Uart_Ip_BaudrateType DesiredBaudrate,
                                                     const uint32 ClockFrequency);

/*!
 * @brief Returns the LPUART baud rate.
 *
 * This function returns the LPUART configured baud rate.
 *
 * @param Instance  LPUART instance number.
 * @param[out] ConfiguredBaudRate LPUART configured baud rate.
 */
void Lpuart_Uart_Ip_GetBaudRate(const uint8 Instance, uint32 * ConfiguredBaudRate);

/*!
 * @brief Sets the internal driver reference to the tx buffer.
 *
 * This function can be called from the tx callback to provide the driver
 * with a new buffer, for continuous transmission.
 *
 * @param Instance  LPUART instance number
 * @param TxBuff  source buffer containing 8-bit data chars to send
 * @param TxSize  the number of bytes to send
 * @return void
 */
void Lpuart_Uart_Ip_SetTxBuffer(const uint8 Instance,
                                const uint8 * TxBuff,
                                const uint32 TxSize);

/*!
 * @brief Sets the internal driver reference to the rx buffer.
 *
 * This function can be called from the rx callback to provide the driver
 * with a new buffer, for continuous reception.
 *
 * @param instance  LPUART instance number
 * @param RxBuff  destination buffer containing 8-bit data chars to receive
 * @param RxSize  the number of bytes to receive
 * @return void
 */
void Lpuart_Uart_Ip_SetRxBuffer(const uint8 Instance,
                                uint8 * RxBuff,
                                const uint32 RxSize);

void Lpuart_Uart_Ip_IrqHandler(const uint8 Instance);

#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
/**
 * @internal
 * @brief   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a part of callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * @param Instance Lpuart instance number
 * @return void
 */
void Lpuart_Uart_Ip_CompleteSendUsingDma(uint8 Instance);

/**
 * @internal
 * @brief   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a part of callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * @param Instance Lpuart instance number
 * @return void
 */
void Lpuart_Uart_Ip_CompleteReceiveUsingDma(uint8 Instance);
#endif

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LPUART_UART_IP_H */
