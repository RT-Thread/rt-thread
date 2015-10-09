/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_FLEXIO_SPI_DRIVER_H
#define __FSL_FLEXIO_SPI_DRIVER_H
#include "fsl_flexio_spi_hal.h"
#include "fsl_flexio_driver.h"
#include "fsl_os_abstraction.h"
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
#include "fsl_edma_driver.h"
#else
#include "fsl_dma_driver.h"
#endif

/*!
 * @addtogroup flexio_spi_driver
 * @{
 */
 
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Error codes for the FlexIO SPI driver. */
typedef enum flexio_spi_status
{
    kStatus_FlexIO_SPI_Success                  = 0x00U, 
    kStatus_FlexIO_SPI_TxBusy                   = 0x01U, 
    kStatus_FlexIO_SPI_RxBusy                   = 0x02U,  
    kStatus_FlexIO_SPI_XBusy                    = 0x03U,  
    kStatus_FlexIO_SPI_NoTransmitInProgress     = 0x04U,
    kStatus_FlexIO_SPI_NoReceiveInProgress      = 0x05U, 
    kStatus_FlexIO_SPI_NoTransferInProgress      = 0x06U, 
    kStatus_FlexIO_SPI_Timeout                  = 0x07U,
    kStatus_FlexIO_SPI_NoDataToDeal             = 0x08U,   
    kStatus_FlexIO_SPI_InvalidParam             = 0x09U,
    kStatus_FlexIO_SPI_DmaRequestFail           = 0x0a
} flexio_spi_status_t;
/*! @brief FlexIO SPI master or slave configuration.*/
typedef enum flexio_spi_master_slave_mode {
    kFlexIOSpiMaster = 1,     /*!< SPI peripheral operates in master mode. @internal gui name="Master" */
    kFlexIOSpiSlave = 0       /*!< SPI peripheral operates in slave mode. @internal gui name="Slave" */
} flexio_spi_master_slave_mode_t;
/*! @brief FlexIO SPI data shifter direction options.*/
typedef enum flexio_spi_shift_direction {
    kFlexIOSpiMsbFirst = 0,    /*!< Data transfers start with most significant bit. @internal gui name="MSB first" */
    kFlexIOSpiLsbFirst = 1    /*!< Data transfers start with least significant bit. @internal gui name="LSB first" */
} flexio_spi_shift_direction_t;
/*! @brief FlexIO SPI clock phase configuration.*/
typedef enum flexio_spi_clock_phase {
    kFlexIOSpiClockPhase_FirstEdge = 0,       /*!< First edge on SPSCK occurs at the middle of the first
                                         *   cycle of a data transfer. @internal gui name="First edge" */
    kFlexIOSpiClockPhase_SecondEdge = 1       /*!< First edge on SPSCK occurs at the start of the
                                         *   first cycle of a data transfer. @internal gui name="Second edge" */
} flexio_spi_clock_phase_t;
/*! @brief SPI data length mode options.*/
typedef enum flexio_spi_data_bitcount_mode  {
    kFlexIOSpi8BitMode = 8,  /*!< 8-bit data transmission mode @internal gui name="8-bit" */
    kFlexIOSpi16BitMode = 16, /*!< 16-bit data transmission mode @internal gui name="16-bit" */
} flexio_spi_data_bitcount_mode_t;
/*! @brief SPI receive callback function type */
typedef void (* flexio_spi_rx_callback_t)(void * spiState);
/*!
 * @brief Runtime state structure for the FlexIO SPI driver.
 */ 
typedef struct flexio_spi_state {
    flexio_spi_master_slave_mode_t mode;
    flexio_spi_data_bitcount_mode_t dataSize;
    flexio_spi_shift_direction_t bitDirection;
    flexio_spi_dev_t spiDev;
    const uint8_t *txBuff;
    uint8_t *rxBuff;
    volatile size_t txSize;
    volatile size_t rxSize;
    volatile bool isTxBusy;        /*!< True if there is an active transmit. */
    volatile bool isRxBusy;        /*!< True if there is an active receive. */
    volatile bool isXBusy;      /*!< True if there is an active transmit&receive simultaneously. */
    volatile bool isTxBlocking;    /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;    /*!< True if receive is blocking transaction. */
    volatile bool isXBlocking;     /*!< True if transmit&receive is blocking transaction. */
    semaphore_t txIrqSync;      /*!< Used to wait for ISR to complete its transmit. */
    semaphore_t rxIrqSync;      /*!< Used to wait for ISR to complete its receive. */
    semaphore_t xIrqSync;      /*!< Used to wait for ISR to complete its transmit and receive. */
    flexio_spi_rx_callback_t rxCallback; /*!< Callback to invoke after receiving byte.*/
    void * rxCallbackParam;        /*!< Receive callback parameter pointer.*/
    volatile bool isTxUseDma;    /*!< True if transmit DMA channel has already been configured. */
    volatile bool isRxUseDma;    /*!< True if receive DMA channel has already been configured. */
    #if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    edma_chn_state_t edmaSpiTx;
    edma_chn_state_t edmaSpiRx;
    #else
    dma_channel_t dmaSpiTx; /*!< DMA transmit channel structure */
    dma_channel_t dmaSpiRx; /*!< DMA receive channel structure. */
    #endif
}flexio_spi_state_t;
/*!
 * @brief FlexIO SPI hardware resource configuration.
 *
 * These constants define the hardware resource used by the FlexIO SPI master/slave device and includes
 * the external pin and the internal shifter and timer.
 * @internal gui name="SPI hardware configuration" id="spiHwCfg"
 */
typedef struct flexio_spi_hwconfig{
    uint32_t sdoPinIdx;   /*!< Output pin index. @internal gui name="Data output pin" */
    uint32_t sdiPinIdx;   /*!< Input pin index. @internal gui name="Data input pin" */
    uint32_t sclkPinIdx; /*!< Clock pin index. Output for master, input for slave. @internal gui name="Clock pin" */
    uint32_t csnPinIdx;  /*!< Chip select pin index. Output for master, input for slave. @internal gui name="Chip select pin" */
    uint32_t shifterIdx[2]; /*!< Select two shifters. @internal gui name="Shifter" id="spiShifter" */
    uint32_t timerIdx[2]; /*!< timer 0 is available for both master and slave. 
                            timer 1 would be only available for master 
                            and not used in slave mode. @internal gui name="Timer" id="spiTimer" */
}flexio_spi_hwconfig_t;
/*!
 * @brief User configuration structure for the FlexIO SPI driver.
 *
 * Use an instance of this structure with the FLEXIO_SPI_DRV_Init()function. This enables configuration of the
 * settings of the FlexIO SPI peripheral with a single function call. Settings include:
 * SPI baud rate, data size, FlexIO SPI mode and FlexIO hardware resource
 * resource.
 * @internal gui name="SPI configuration" id="spiCfg"
 */
typedef struct flexio_spi_userconfig{
    flexio_spi_master_slave_mode_t spiMode; /*!< Selects Master or Slave mode. @internal gui name="Mode" id="spiMode" */
    uint32_t baudRate; /*!< Baudrate configuration. @internal gui name="Baudrate" id="spiBaudrate" */
    flexio_spi_clock_phase_t clkPhase; /*!< Clock phase configuration. @internal gui name="Clock phase" id="spiClockPhase" */
    flexio_spi_data_bitcount_mode_t dataSize; /*!< SPI data length mode. @internal gui name="Bits" id="spiBits" */
    flexio_spi_shift_direction_t bitDirection; /*!< SPI data shifter direction options. @internal gui name="Data direction" id="spiDirection" */
    flexio_spi_hwconfig_t spiHwConfig; /*!< FlexIO SPI Resource configuration. @internal gui name="Hardware configuration" */
}flexio_spi_userconfig_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FlexIO SPI Driver
 * @{
 */

/*!
 * @brief Initializes a FlexIO-simulated SPI device.
 *
 * This function initializes the run-time state structure to keep track of
 * the ongoing transfers and the module to user-defined settings and 
 * default settings. It also configures the underlying FlexIO pin, shifter, and timer.
 * This is an example to set up the flexio_spi_state_t and the
 * flexio_spi_userconfig_t parameters and to call the FLEXIO_SPI_DRV_Init function
   @code
      flexio_spi_userconif_t spiConfig;
      spiConfig.spiMode = kFlexIOSpiMaster;
      spiConfig.baudRate = 100000;
      spiConfig.clkPhase = kFlexIOSpiClockPhase_FirstEdge;
      spiConfig.dataSize = kFlexIOSpi8BitMode;
      spiConfig.spiHwConfig.sdoPinIdx = 0;
      spiConfig.spiHwConfig.sdiPinIdx = 1;
      spiConfig.spiHwConfig.sclkPinIdx = 2;
      spiConfig.spiHwConfig.csnPinIdx = 3;
      spiConfig.spiHwConfig.shifterIdx = {0,1};
      spiConfig.spiHwConfig.timerIdx = {0,1};
   @endcode
 *
 * @param instance The FlexIO instance number.
 * @param spiState A pointer to the global FlexIO SPI driver state structure memory. 
 *  The user passes in the memory for the run-time state structure. The FlexIO SPI driver
 *  populates the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param spiConfig The user configuration structure of type flexio_spi_userconfig_t. 
 *  The user populates the members of this structure and passes the pointer of this structure
 *  to this function.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_Init(uint32_t instance, flexio_spi_state_t * spiState,
                               const flexio_spi_userconfig_t * spiConfig);
/*!
 * @brief Shuts down the FlexIO SPI.
 *
 * This function disables the FlexIO-simulated SPI trigger.
 *
 * @param spiState The run-time structure of the FlexIO-simulated SPI.
 */
void FLEXIO_SPI_DRV_Deinit(flexio_spi_state_t * spiState);

/*!
 * @brief Sends (transmits) data out through the FlexIO-simulated SPI module using a 
 * blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_SendDataBlocking(flexio_spi_state_t * spiState,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the FlexIO-simulated SPI module using a 
 * non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_SendData(flexio_spi_state_t * spiState,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);
/*!
 * @brief Returns whether the previous FlexIO-simulated SPI transmit has finished.
 *
 * @param spiState The run-time structure of the FlexIO-simulated SPI.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The transmit has completed successfully.
 * @retval kStatus_FlexIO_SPI_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_GetTransmitStatus(flexio_spi_state_t * spiState, 
                                   uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated SPI transmission early.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The transmit was successful.
 * @retval kStatus_FlexIO_SPI_NoTransmitInProgress No transmission is currently in progress.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_AbortSendingData(flexio_spi_state_t * spiState);

/*!
 * @brief Gets (receives) data from the FlexIO-simulated SPI module using a blocking method.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_ReceiveDataBlocking(flexio_spi_state_t * spiState,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated SPI module using a non-blocking method.
 *
 * @param spiState The run-time structure of the FlexIO-simulated SPI.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data characters received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_ReceiveData(flexio_spi_state_t * spiState,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize);

/*!
 * @brief Returns whether the previous FlexIO-simulated SPI receive is complete.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The receive has completed successfully.
 * @retval kStatus_FlexIO_SPI_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_GetReceiveStatus(flexio_spi_state_t * spiState, 
                                  uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated SPI receive early.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @return An error code or kStatus_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The receive was successful.
 * @retval kStatus_FlexIO_SPI_NoTransmitInProgress No receive is currently in progress.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_AbortReceivingData(flexio_spi_state_t * spiState);
/*!
 * @brief Transfers data through the FlexIO-simulated SPI module using a 
 * blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param xSize The number of bytes to send and receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_TransferDataBlocking(flexio_spi_state_t * spiState,
                                           const uint8_t * txBuff, uint8_t *rxBuff,
                                           uint32_t xSize,
                                           uint32_t timeout);

/*!
 * @brief Transfers data through the FlexIO-simulated SPI module using a 
 * non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param xSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_TransferData(flexio_spi_state_t * spiState,
                                   const uint8_t * txBuff, uint8_t *rxBuff,
                                   uint32_t xSize);

/*!
 * @brief Interrupt handler for the FlexIO-simulated SPI transmit.
 * @param param The run-time structure of FlexIO-simulated SPI.
 */
void FLEXIO_SPI_DRV_TX_IRQHandler(void *param);

/*!
 * @brief Interrupt handler for the FlexIO-simulated SPI receive.
 * @param param The run-time structure of the FlexIO-simulated SPI.
 */
void FLEXIO_SPI_DRV_RX_IRQHandler(void *param);
/*!
 * @brief Sends (transmits) data out through the FlexIO-simulated SPI module using an 
 * eDMA blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaSendDataBlocking(flexio_spi_state_t * spiState,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the FlexIO-simulated SPI module using a 
 * eDMA non-blocking method.
 * @param spiState The run-time structure of the FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaSendData(flexio_spi_state_t * spiState,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);
/*!
 * @brief Returns whether the previous FlexIO-simulated SPI eDMA transmit is complete.
 *
 * @param spiState The run-time structure of the FlexIO-simulated SPI.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The transmit has completed successfully.
 * @retval kStatus_FlexIO_SPI_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaGetTransmitStatus(flexio_spi_state_t * spiState, 
                                   uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated SPI eDMA transmission early.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The transmit was successful.
 * @retval kStatus_FlexIO_SPI_NoTransmitInProgress No transmission is currently in progress.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaAbortSendingData(flexio_spi_state_t * spiState);

/*!
 * @brief Gets (receives) data from the FlexIO-simulated SPI module using an eDMA 
 * blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaReceiveDataBlocking(flexio_spi_state_t * spiState,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated SPI module using an eDMA 
 * non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data characters received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaReceiveData(flexio_spi_state_t * spiState,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize);

/*!
 * @brief Returns whether the previous FlexIO-simulated SPI eDMA receive is complete.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes 
 * which still need to be received in the active transfer.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The receive has completed successfully.
 * @retval kStatus_FlexIO_SPI_RxBusy The receive is still in progress. @a bytesReceived 
 * is filled with the number of bytes which are received up to that point.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaGetReceiveStatus(flexio_spi_state_t * spiState, 
                                  uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated SPI eDMA receive early.
 *
 * @param spiState The run-time structure of the FlexIO-simulated SPI.
 * @return An error code or kStatus_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The receive was successful.
 * @retval kStatus_FlexIO_SPI_NoTransmitInProgress No receive is currently in progress.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaAbortReceivingData(flexio_spi_state_t * spiState);
/*!
 * @brief Transfers data through the FlexIO-simulated SPI module using an eDMA
 * blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param xSize The number of bytes to send&receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaTransferDataBlocking(flexio_spi_state_t * spiState,
                                           const uint8_t * txBuff, uint8_t *rxBuff,
                                           uint32_t xSize,
                                           uint32_t timeout);

/*!
 * @brief Transfers data through the FlexIO-simulated SPI module using an 
 * eDMA non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param xSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaTransferData(flexio_spi_state_t * spiState,
                                   const uint8_t * txBuff, uint8_t *rxBuff,
                                   uint32_t xSize);
/*!
 * @brief Sends (transmits) data out through the FlexIO-simulated SPI module using a 
 * DMA blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaSendDataBlocking(flexio_spi_state_t * spiState,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the FlexIO-simulated SPI module using a DMA
 * non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaSendData(flexio_spi_state_t * spiState,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);
/*!
 * @brief Returns whether the previous FlexIO-simulated SPI DMA transmit has finished.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes 
 * that are remaining in the active transfer.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The transmit has completed successfully.
 * @retval kStatus_FlexIO_SPI_TxBusy The transmit is still in progress. @a bytesTransmitted 
 * is filled with the number of bytes which are transmitted up to that point.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaGetTransmitStatus(flexio_spi_state_t * spiState, 
                                   uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated SPI DMA transmission early.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The transmit was successful.
 * @retval kStatus_FlexIO_SPI_NoTransmitInProgress No transmission is currently in progress.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaAbortSendingData(flexio_spi_state_t * spiState);

/*!
 * @brief Gets (receives) data from the FlexIO-simulated SPI module using a 
 * DMA blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaReceiveDataBlocking(flexio_spi_state_t * spiState,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated SPI module using a 
 * DMA non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data characters received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaReceiveData(flexio_spi_state_t * spiState,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize);

/*!
 * @brief Returns whether the previous FlexIO-simulated SPI DMA receive is complete.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes 
 * which still need to be received in the active transfer.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The receive has completed successfully.
 * @retval kStatus_FlexIO_SPI_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaGetReceiveStatus(flexio_spi_state_t * spiState, 
                                  uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated SPI DMA receive early.
 *
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @return An error code or kStatus_SPI_Success.
 * @retval kStatus_FlexIO_SPI_Success The receive was successful.
 * @retval kStatus_FlexIO_SPI_NoTransmitInProgress No receive is currently in progress.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_AbortDmaReceivingData(flexio_spi_state_t * spiState);
/*!
 * @brief Transfers data through the FlexIO-simulated SPI module using a 
 * DMA blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param xSize The number of bytes to send&receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaTransferDataBlocking(flexio_spi_state_t * spiState,
                                           const uint8_t * txBuff, uint8_t *rxBuff,
                                           uint32_t xSize,
                                           uint32_t timeout);

/*!
 * @brief Transfers data through the FlexIO-simulated SPI module using a 
 * DMA non-blocking method.
 * @param spiState The run-time structure of FlexIO-simulated SPI.
 * @param txBuff A pointer to the source buffer containing 8-bit data characters to send.
 * @param rxBuff A pointer to the buffer containing 8-bit read data characters received.
 * @param xSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_SPI_Success.
 */
flexio_spi_status_t FLEXIO_SPI_DRV_DmaTransferData(flexio_spi_state_t * spiState,
                                   const uint8_t * txBuff, uint8_t *rxBuff,
                                   uint32_t xSize);
/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
