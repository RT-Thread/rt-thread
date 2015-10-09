/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_LPSCI_DMA_DRIVER_H__
#define __FSL_LPSCI_DMA_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_lpsci_hal.h"
#include "fsl_dma_driver.h"
#include "fsl_clock_manager.h"

/*!
 * @addtogroup lpsci_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for LPSCI instances. */
extern UART0_Type * const g_lpsciBase[UART0_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Runtime state structure for LPSCI driver with DMA.
 */
typedef struct LpsciDmaState {
    volatile bool isTxBusy;     /*!< True if there is an active transmit. */
    volatile bool isRxBusy;     /*!< True if there is an active receive. */
    volatile bool isTxBlocking; /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking; /*!< True if receive is blocking transaction. */
    semaphore_t txIrqSync;      /*!< Used to wait for ISR to complete its TX business. */
    semaphore_t rxIrqSync;      /*!< Used to wait for ISR to complete its RX business. */
    dma_channel_t dmaLpsciTx;    /*!< DMA channel used for send. */
    dma_channel_t dmaLpsciRx;   /*!< DMA channel used for receive. */
} lpsci_dma_state_t;

/*!
 * @brief User configuration structure for the LPSCI driver.
 *
 * Use an instance of this structure with the LPSCI_DRV_Init()function. This enables configuration of the
 * most common settings of the LPSCI peripheral with a single function call. Settings include:
 * LPSCI baud rate, LPSCI parity mode: disabled (default), or even or odd, the number of stop bits, and
 * the number of bits per data word.
 */
typedef struct LpsciDmaUserConfig {
    clock_lpsci_src_t clockSource;       /*!< LPSCI clock source in fsl_sim_hal_<device>.h */
    uint32_t baudRate;                   /*!< LPSCI baud rate*/
    lpsci_parity_mode_t parityMode;      /*!< parity mode, disabled (default), even, odd */
    lpsci_stop_bit_count_t stopBitCount; /*!< number of stop bits, 1 stop bit (default) or 2 stop bits */
    lpsci_bit_count_per_char_t bitCountPerChar; /*!< number of bits, 8-bit (default) or 9-bit in
                                                    a word (up to 10-bits in some LPSCI instances) */
} lpsci_dma_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPSCI DMA Driver
 * @{
 */

/*!
 * @brief Initializes an LPSCI instance to work with DMA.
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, un-gates the clock to the LPSCI module, initializes the module
 * to user-defined settings and default settings, configures the IRQ state structure, and enables
 * the module-level interrupt to the core, the LPSCI module transmitter and receiver.
 * This example shows how to set up the lpsci_dma_state_t and the
 * lpsci_user_config_t parameters and how to call the LPSCI_DRV_DmaInit function by passing
 * in these parameters:
   @code
    lpsci_user_config_t lpsciConfig;
    lpsciConfig.baudRate = 9600;
    lpsciConfig.bitCountPerChar = kLpsci8BitsPerChar;
    lpsciConfig.parityMode = kLpsciParityDisabled;
    lpsciConfig.stopBitCount = kLpsciOneStopBit;
    lpsci_dma_state_t lpsciDmaState;
    LPSCI_DRV_DmaInit(instance, &lpsciDmaState, &lpsciConfig);
   @endcode
 *
 * @param instance The LPSCI instance number.
 * @param lpsciDmaStatePtr A pointer to the LPSCI driver state structure memory. The user
 *  passes in the memory for the run-time state structure. The LPSCI driver
 *  populates the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param lpsciUserConfig The user configuration structure of type lpsci_user_config_t. The user
 *  populates the members of this structure and passes the pointer of this structure
 *  to this function.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_DmaInit(uint32_t instance, lpsci_dma_state_t * lpsciDmaStatePtr,
                               const lpsci_dma_user_config_t * lpsciUserConfig);
/*!
 * @brief Shuts down the LPSCI.
 *
 * This function disables the LPSCI-DMA trigger and disables the transmitter and receiver.
 *
 * @param instance The LPSCI instance number.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_DmaDeinit(uint32_t instance);

/*!
 * @brief Sends (transmits) data out through the LPSCI-DMA module using blocking method.
 *
 * @param instance The LPSCI instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_DmaSendDataBlocking(uint32_t instance,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the LPSCI-DMA module using a non-blocking method.
 *
 * @param instance The LPSCI module base address.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_DmaSendData(uint32_t instance,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);
/*!
 * @brief Returns whether the previous LPSCI-DMA transmit has finished.
 *
 * @param instance The LPSCI module base address.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return An error code or kStatus_LPSCI_Success.
 * @retval kStatus_LPSCI_Success The transmit has completed successfully.
 * @retval kStatus_LPSCI_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
lpsci_status_t LPSCI_DRV_DmaGetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining);

/*!
 * @brief Terminates a non-blocking LPSCI-DMA transmission early.
 *
 * @param instance The LPSCI module base address.
 * @return An error code or kStatus_LPSCI_Success.
 * @retval kStatus_LPSCI_Success The transmit was successful.
 * @retval kStatus_LPSCI_NoTransmitInProgress No transmission is currently in progress.
 */
lpsci_status_t LPSCI_DRV_DmaAbortSendingData(uint32_t instance);

/*!
 * @brief Gets (receives) data from the LPSCI-DMA module using a blocking method.
 *
 * @param instance The LPSCI module base address.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_DmaReceiveDataBlocking(uint32_t instance,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout);
/*!
 * @brief Gets (receives) data from the LPSCI-DMA module using a non-blocking method.
 *
 * @param instance The LPSCI module base address.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_DmaReceiveData(uint32_t instance,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize);

/*!
 * @brief Returns whether the previous LPSCI-DMA receive is complete.
 *
 * @param instance The LPSCI module base address.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return An error code or kStatus_LPSCI_Success.
 * @retval kStatus_LPSCI_Success The receive has completed successfully.
 * @retval kStatus_LPSCI_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
lpsci_status_t LPSCI_DRV_DmaGetReceiveStatus(uint32_t instance, uint32_t * bytesRemaining);

/*!
 * @brief Terminates a non-blocking LPSCI-DMA receive early.
 *
 * @param instance The LPSCI module base address.
 * @return An error code or kStatus_LPSCI_Success.
 * @retval kStatus_LPSCI_Success The receive was successful.
 * @retval kStatus_LPSCI_NoTransmitInProgress No receive is currently in progress.
 */
lpsci_status_t LPSCI_DRV_DmaAbortReceivingData(uint32_t instance);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPSCI_DMA_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

