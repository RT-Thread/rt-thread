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

#ifndef __FSL_LPUART_DMA_DRIVER_H__
#define __FSL_LPUART_DMA_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_lpuart_hal.h"
#include "fsl_dma_driver.h"
#include "fsl_clock_manager.h"

/*!
 * @addtogroup lpuart_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for LPUART instances. */
extern LPUART_Type * const g_lpuartBase[LPUART_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Runtime state structure for UART driver with DMA.
 */
typedef struct LpuartDmaState {
    volatile bool isTxBusy;     /*!< True if there is an active transmit. */
    volatile bool isRxBusy;     /*!< True if there is an active receive. */
    volatile bool isTxBlocking; /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking; /*!< True if receive is blocking transaction. */
    semaphore_t txIrqSync;      /*!< Used to wait for ISR to complete its TX business. */
    semaphore_t rxIrqSync;      /*!< Used to wait for ISR to complete its RX business. */
    dma_channel_t dmaLpuartTx; /*!< Structure definition for the DMA channel */
    dma_channel_t dmaLpuartRx; /*!< Structure definition for the DMA channel */
} lpuart_dma_state_t;

/*! @brief LPUART configuration structure*/
typedef struct LpuartDmaUserConfig {
    clock_lpuart_src_t clockSource;      /*!< LPUART clock source in fsl_sim_hal_<device>.h */
    uint32_t baudRate;                   /*!< LPUART baud rate*/
    lpuart_parity_mode_t parityMode;     /*!< parity mode, disabled (default), even, odd */
    lpuart_stop_bit_count_t stopBitCount;/*!< number of stop bits, 1 stop bit (default) or 2 stop bits*/
    lpuart_bit_count_per_char_t bitCountPerChar; /*!< number of bits, 8-bit (default) or 9-bit in a
                                                   char (up to 10-bits in some LPUART instances.*/
} lpuart_dma_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPUART DMA Driver
 * @{
 */

/*!
 * @brief Initializes an LPUART instance to work with DMA.
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, un-gates the clock to the LPUART module, initializes the module
 * to user-defined settings and default settings, configures the IRQ state structure and enables
 * the module-level interrupt to the core, and enables the LPUART module transmitter and receiver.
 * This example shows how to set up the lpuart_dma_state_t and the
 * lpuart_user_config_t parameters and how to call the LPUART_DRV_DmaInit function by passing
 * in these parameters:
   @code
    lpuart_user_config_t lpuartConfig;
    lpuartConfig.baudRate = 9600;
    lpuartConfig.bitCountPerChar = kLpuart8BitsPerChar;
    lpuartConfig.parityMode = kLpuartParityDisabled;
    lpuartConfig.stopBitCount = kLpuartOneStopBit;
    lpuart_dma_state_t lpuartDmaState;
    LPUART_DRV_DmaInit(instance, &lpuartDmaState, &lpuartConfig);
   @endcode
 *
 * @param instance The LPUART instance number.
 * @param lpuartDmaStatePtr A pointer to the LPUART driver state structure memory. The user
 *  passes in the memory for the run-time state structure. The LPUART driver
 *  populates the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param lpuartUserConfig The user configuration structure of type lpuart_user_config_t. The user
 *  populates the members of this structure and passes the pointer of this structure
 *  into this function.
 * @return An error code or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_DRV_DmaInit(uint32_t instance, lpuart_dma_state_t * lpuartDmaStatePtr,
                               const lpuart_dma_user_config_t * lpuartUserConfig);
/*!
 * @brief Shuts down the LPUART.
 *
 * This function disables the LPUART-DMA trigger, the transmitter, and the receiver.
 *
 * @param instance The LPUART instance number.
 * @return An error code or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_DRV_DmaDeinit(uint32_t instance);

/*!
 * @brief Sends (transmits) data out through the LPUART-DMA module using a blocking method.
 *
 * @param instance The LPUART instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_DRV_DmaSendDataBlocking(uint32_t instance,
                                        const uint8_t * txBuff,
                                        uint32_t txSize,
                                        uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the LPUART-DMA module using a non-blocking method.
 *
 * @param instance The LPUART module base address.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_DRV_DmaSendData(uint32_t instance,
                                const uint8_t * txBuff,
                                uint32_t txSize);
/*!
 * @brief Returns whether the previous LPUART-DMA transmit has finished.
 *
 * @param instance The LPUART module base address.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return Current transmit status.
 * @retval kStatus_LPUART_Success The transmit has completed successfully.
 * @retval kStatus_LPUART_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
lpuart_status_t LPUART_DRV_DmaGetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining);

/*!
 * @brief Terminates a non-blocking LPUART-DMA transmission early.
 *
 * @param instance The LPUART module base address.
 * @return Whether the abort of transmitting was successful or not.
 * @retval kStatus_LPUART_Success The transmit was successful.
 * @retval kStatus_LPUART_NoTransmitInProgress No transmission is currently in progress.
 */
lpuart_status_t LPUART_DRV_DmaAbortSendingData(uint32_t instance);

/*!
 * @brief Gets (receives) data from the LPUART-DMA module using a blocking method.
 *
 * @param instance The LPUART module base address.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_DRV_DmaReceiveDataBlocking(uint32_t instance, uint8_t * rxBuff,
                                              uint32_t rxSize, uint32_t timeout);
/*!
 * @brief Gets (receives) data from the LPUART-DMA module using a non-blocking method.
 *
 * @param instance The LPUART module base address.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_DRV_DmaReceiveData(uint32_t instance, uint8_t * rxBuff, uint32_t rxSize);

/*!
 * @brief Returns whether the previous LPUART-DMA receive is complete.
 *
 * @param instance The LPUART module base address.
 * @param bytesRemaining A pointer to a value that populated with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return Current receiving status.
 * @retval kStatus_LPUART_Success The receive has completed successfully.
 * @retval kStatus_LPUART_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
lpuart_status_t LPUART_DRV_DmaGetReceiveStatus(uint32_t instance, uint32_t * bytesRemaining);

/*!
 * @brief Terminates a non-blocking LPUART-DMA receive early.
 *
 * @param instance The LPUART module base address.
 * @return Whether the abort of receiving was successful or not.
 * @retval kStatus_LPUART_Success The receive was successful.
 * @retval kStatus_LPUART_NoTransmitInProgress No receive is currently in progress.
 */
lpuart_status_t LPUART_DRV_DmaAbortReceivingData(uint32_t instance);

/*@}*/


#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPUART_DMA_DRIVER_H__ */
/******************************************************************************/
/* EOF */
/******************************************************************************/

