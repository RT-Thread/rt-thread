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
#if !defined(__FSL_DSPI_EDMA_SLAVE_DRIVER_H__)
#define __FSL_DSPI_EDMA_SLAVE_DRIVER_H__

#include "fsl_dspi_hal.h"
#include "fsl_edma_driver.h"
#include "fsl_os_abstraction.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*!
 * @addtogroup dspi_slave_driver
 * @{
 */

/*! @brief Table of base pointers for SPI instances. */
extern SPI_Type * const g_dspiBase[SPI_INSTANCE_COUNT];

/*! @brief Table to save DSPI IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_dspiIrqId[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DSPI_EDMA_DEFAULT_DUMMY_PATTERN     (0u)   /*!< Dummy pattern, that DSPI slave will send
                                                        when transmit data was not configured */

/*!
 *  @brief User configuration structure for the DSPI slave driver.
 */
typedef struct DSPIEdmaSlaveUserConfig {
    dspi_data_format_config_t dataConfig;   /*!< Data format configuration structure */
    uint16_t dummyPattern;                  /*!< Dummy data value */
} dspi_edma_slave_user_config_t;

/*!
 * @brief Runtime state structure of the DSPI slave driver.
 *
 * This structure holds data that is used by the DSPI slave peripheral driver to
 * communicate between the transfer function and the interrupt handler. The user
 * needs to pass in the memory for this structure and the driver fills out
 * the members.
 */
typedef struct DSPIEdmaSlaveState {
    uint32_t bitsPerFrame;                      /*!< Desired number of bits per frame */
    dspi_status_t status;                       /*!< Current state of slave */
    event_t event;                              /*!< Event to notify waiting task */
    uint16_t errorCount;                        /*!< Driver error count */
    uint32_t dummyPattern;                      /*!< Dummy data will be send when do not have data
                                                     in transmit buffer */
    volatile bool isTransferInProgress;         /*!< True if there is an active transfer.*/
    const uint8_t * sendBuffer;        /*!< Pointer to transmit buffer */
    uint8_t * receiveBuffer;           /*!< Pointer to receive buffer */
    volatile int32_t remainingSendByteCount;    /*!< Number of bytes remaining to send.*/
    volatile int32_t remainingReceiveByteCount; /*!< Number of bytes remaining to receive.*/
    uint8_t extraReceiveByte;                   /*!< Number of extra receive bytes */
    bool isSync;                                /*!< Indicates the function call is sync or async */
    edma_chn_state_t edmaTxChannel;             /*!< Structure definition for the eDMA channel */
    edma_chn_state_t edmaRxChannel;             /*!< Structure definition for the eDMA channel */
} dspi_edma_slave_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/


#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @name Initialization and shutdown
 * @{
 */

/*!
 * @brief Initializes a DSPI instance for a slave mode operation, using eDMA mechanism.
 *
 * This function un-gates the clock to the DSPI module, initializes the DSPI for slave
 * mode and initializes eDMA channels. After it is initialized, the DSPI module is configured
 * in slave mode and user can start transmit, receive data by calls send, receive,
 * transfer functions. This function indicates DSPI slave uses the eDMA mechanism.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param dspiState The pointer to the DSPI slave driver state structure.
 * @param slaveConfig The configuration structure dspi_edma_slave_user_config_t which
 *              configures the data bus format.
 *
 * @return An error code or kStatus_DSPI_Success.
 */
dspi_status_t DSPI_DRV_EdmaSlaveInit(uint32_t instance,
                                     dspi_edma_slave_state_t * dspiState,
                                     const dspi_edma_slave_user_config_t * slaveConfig);

/*!
 * @brief Shuts down a DSPI instance - eDMA mechanism.
 *
 * Disables the DSPI module, gates its clock, changes the DSPI slave driver state to NonInit
 * for DSPI slave module which is initialized with the eDMA mechanism. After de-initialization,
 * the user can re-initialize the DSPI slave module with other mechanisms.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @return kStatus_DSPI_Success indicating successful de-initialization or error code
 */
dspi_status_t DSPI_DRV_EdmaSlaveDeinit(uint32_t instance);
/*! @} */

/*!
 * @name Blocking transfers
 * @{
 */

/*!
 * @brief Transfers data on the SPI bus using the eDMA and blocking call.
 *
 * This function checks driver status, mechanism and transmits/receives data through SPI bus.
 * If sendBuffer is NULL, transmit process is ignored, and if the receiveBuffer is NULL, the receive
 * process is ignored. If both the receiveBuffer and the sendBuffer  are available, the transmit and
 * receive progress is processed. If only the receiveBuffer is available, the receive is processed,
 * Otherwise, the transmit is processed. This function only returns when its processes
 * are complete. This function uses the eDMA mechanism.
 *
 * @param instance The instance number of DSPI peripheral
 * @param sendBuffer The pointer to data that user wants to transmit.
 * @param receiveBuffer The pointer to data that user wants to store received data.
 * @param transferByteCount The number of bytes to send and receive.
 * @param timeOut The maximum number of milliseconds that function will wait before
 *              timed out reached.
 *
 * @return  kStatus_DSPI_Success if driver starts to send/receive data successfully.
 *          kStatus_DSPI_Error if driver is error and needs to clean error.
 *          kStatus_DSPI_Busy if driver is receiving/transmitting data and not available.
 *          kStatus_DSPI_Timeout if time out reached while transferring is in progress.
 */
dspi_status_t DSPI_DRV_EdmaSlaveTransferBlocking(uint32_t instance,
                                                 const uint8_t *sendBuffer,
                                                 uint8_t *receiveBuffer,
                                                 uint32_t transferByteCount,
                                                 uint32_t timeOut);

/*@}*/

/*!
 * @name Non-blocking transfers
 * @{
 */

/*!
 * @brief Starts transfer data on SPI bus using eDMA
 *
 * This function checks the driver status then sets buffer pointers to receive and transmit
 * SPI data. If the sendBuffer is NULL, transmit process is ignored. If the receiveBuffer is
 * NULL, the receive process is ignored. If both the receiveBuffer and sendBuffer are available, the
 * transfer is done when the kDspiTxDone and the kDspiRxDone are set. If only the receiveBuffer is
 * available, the transfer is done when the kDspiRxDone  flag is set. Otherwise, the transfer is
 * done when the kDspiTxDone is set. This function uses the eDMA mechanism.
 *
 * @param instance The instance number of DSPI peripheral.
 * @param sendBuffer The pointer to data that user wants to transmit.
 * @param receiveBuffer The pointer to data that user wants to store received data.
 * @param transferByteCount The number of bytes to send and receive.
 *
 * @return  kStatus_DSPI_Success if driver starts to send/receive data successfully.
 *          kStatus_DSPI_Error if driver is error and needs to clean error.
 *          kStatus_DSPI_Busy if driver is receiving/transmitting data and not available.
 */
dspi_status_t DSPI_DRV_EdmaSlaveTransfer(uint32_t instance,
                                         const uint8_t *sendBuffer,
                                         uint8_t *receiveBuffer,
                                         uint32_t transferByteCount);

/*!
 * @brief Aborts the transfer that started by a non-blocking call to the eDMA transfer function.
 *
 * This function stops the transfer which was started by the DSPI_DRV_EdmaSlaveTransfer() function.
 *
 * @param instance The instance number of DSPI peripheral
 *
 * @return  kStatus_DSPI_Success if everything is ok.
 *          kStatus_DSPI_InvalidMechanism if the current transaction does not use
 *                      eDMA mechanism.
 */
dspi_status_t DSPI_DRV_EdmaSlaveAbortTransfer(uint32_t instance);

/*!
 * @brief Returns whether the previous transfer is finished.
 *
 * When performing an a-sync transfer, the user can call this function to ascertain
 * the state of the current transfer: in progress (or busy) or complete (success).
 * In addition, if the transfer is still in progress, the user can get the number
 * of words that have been transferred up to now.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param framesTransferred Pointer to value that is filled in with the number of
 *  frames that have been sent in the active transfer. A frame is defined as the
 *  number of bits per frame.
 *
 * @return kStatus_DSPI_Success The transfer has completed successfully, or
 *         kStatus_DSPI_Busy The transfer is still in progress. framesTransferred
 *         is filled with the number of words that have been transferred so far.
 */
dspi_status_t DSPI_DRV_EdmaSlaveGetTransferStatus(uint32_t instance,
                                                  uint32_t * framesTransferred);

/*!
 * @brief DSPI slave interrupt handler
 * @details This function is DSPI slave interrupt handler using eDMA mechanism. The
 *          pupose of this interrupt handler is indicates when the transfer is really
 *          finished. The eDMA only used to copy data from/to RX FIFO/TX FIFO, but it
 *          not sure the data was transmitted to the master. So must have to enable
 *          this interrupt to do it. This interrupt only be enabled when the last
 *          four FIFO will be transmitted.
 *
 * @param instance The SPI number
 */
void DSPI_DRV_EdmaSlaveIRQHandler(uint32_t instance);

/*! @} */

#if defined(__cplusplus)
}
#endif

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
#endif /* __FSL_DSPI_EDMA_SLAVE_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

