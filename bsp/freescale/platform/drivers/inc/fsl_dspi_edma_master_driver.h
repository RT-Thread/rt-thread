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
#if !defined(__FSL_DSPI_EDMA_MASTER_DRIVER_H__)
#define __FSL_DSPI_EDMA_MASTER_DRIVER_H__

#include "fsl_dspi_hal.h"
#include "fsl_os_abstraction.h"
#include "fsl_edma_driver.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*!
 * @addtogroup dspi_master_driver
 * @{
 */

/*! @brief Table of base pointers for SPI instances. */
extern SPI_Type * const g_dspiBase[SPI_INSTANCE_COUNT];

/*! @brief Table to save DSPI IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_dspiIrqId[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Data structure containing information about a device on the SPI bus with EDMA.
 *
 * The user must populate the members to set up the DSPI master with EDMA and
 * properly communicate with the SPI device.
 */
typedef struct DspiEdmaDevice {
    uint32_t bitsPerSec;                 /*!< @brief Baud rate in bits per second.*/
    dspi_data_format_config_t dataBusConfig;  /* data format configuration structure*/
} dspi_edma_device_t;

/*!
 * @brief Runtime state structure for the DSPI master driver with EDMA.
 *
 * This structure holds data used by the DSPI master Peripheral driver to
 * communicate between the transfer function and the interrupt handler. The
 * interrupt handler also uses this information to keep track of its progress.
 * The user passes  the memory for this run-time state structure. The
 * DSPI master driver  populates the members.
 */
typedef struct DspiEdmaMasterState {
    dspi_ctar_selection_t whichCtar; /*!< Desired Clock and Transfer Attributes Register (CTAR)*/
    uint32_t bitsPerFrame;         /*!< Desired number of bits per frame */
    dspi_which_pcs_config_t whichPcs; /*!< Desired Peripheral Chip Select (pcs) */
    bool isChipSelectContinuous;  /*!< Option to enable the continuous assertion of chip select
                                       between transfers*/
    uint32_t dspiSourceClock;              /*!< Module source clock*/
    volatile bool isTransferInProgress;             /*!< True if there is an active transfer.*/
    volatile bool isTransferBlocking;    /*!< True if transfer is a blocking transaction. */
    semaphore_t irqSync;                 /*!< Used to wait for ISR to complete its business.*/
    edma_chn_state_t dmaCmdData2Fifo; /*!< Structure definition for the eDMA channel */
    edma_chn_state_t dmaSrc2CmdData;  /*!< Structure definition for the eDMA channel */
    edma_chn_state_t dmaFifo2Receive; /*!< Structure definition for the eDMA channel */
    edma_software_tcd_t * stcdSrc2CmdDataLast; /*!< Pointer to SW TCD in memory */
    bool extraByte;    /*!< Flag used for 16-bit transfers with odd byte count */
    uint8_t * rxBuffer;     /*!< The buffer into which received bytes are placed.*/
    uint32_t rxTransferByteCnt;  /*!< Number of bytes to receive.*/
} dspi_edma_master_state_t;

/*!
 * @brief The user configuration structure for the DSPI master driver with EDMA.
 *
 * Use an instance of this structure with the DSPI_DRV_EdmaMasterInit() function. This allows the user to configure
 * the most common settings of the DSPI peripheral with a single function call.
 */
typedef struct DspiEdmaMasterUserConfig {
    dspi_ctar_selection_t whichCtar; /*!< Desired Clock and Transfer Attributes Register(CTAR)*/
    bool isSckContinuous;                  /*!< Disable or Enable continuous SCK operation*/
    bool isChipSelectContinuous;  /*!< Option to enable the continuous assertion of chip select
                                       between transfers */
    dspi_which_pcs_config_t whichPcs;        /*!< Desired Peripheral Chip Select (pcs) */
    dspi_pcs_polarity_config_t pcsPolarity;  /*!< Peripheral Chip Select (pcs) polarity setting.*/
} dspi_edma_master_user_config_t;

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
 * @brief Initializes a DSPI instance for master mode operation to work with EDMA.
 *
 * This function uses a DMA-driven method for transferring data.
 * This function initializes the run-time state structure to track the ongoing
 * transfers, ungates the clock to the DSPI module, resets the DSPI module, initializes the module
 * to user-defined settings and default settings, configures the IRQ state structure, enables
 * the module-level interrupt to the core, and enables the DSPI module.
 * The CTAR parameter is special in that it allows the user to have different SPI devices
 * connected to the same DSPI module instance in addition to different peripheral chip
 * selects. Each CTAR contains the bus attributes associated with that particular SPI device.
 * For most use cases, where only one SPI device is connected per DSPI module
 * instance, use CTAR0.
 * This is an example to set up and call the DSPI_DRV_EdmaMasterInit function by passing
 * in these parameters:
   @code
    dspi_edma_master_state_t dspiEdmaState; <- the user allocates memory for this structure
    uint32_t calculatedBaudRate;
    dspi_edma_master_user_config_t userConfig; <- the user populates members for this structure
    userConfig.isChipSelectContinuous = false;
    userConfig.isSckContinuous = false;
    userConfig.pcsPolarity = kDspiPcs_ActiveLow;
    userConfig.whichCtar = kDspiCtar0;
    userConfig.whichPcs = kDspiPcs0;
    DSPI_DRV_EdmaMasterInit(masterInstance, &dspiEdmaState, &userConfig);
   @endcode
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param dspiEdmaState The pointer to the DSPI EDMA master driver state structure. The user
 *  passes the memory for the run-time state structure. The DSPI master driver
 *  populates the members. The run-time state structure keeps track of the
 *  transfer in progress.
 * @param userConfig The dspi_edma_master_user_config_t user configuration structure. The user
 *  populates the members of this structure and  passes the pointer of the structure
 *  into the function.
 * @param stcdSrc2CmdDataLast This is a pointer to a structure of the stcdSrc2CmdDataLast type. It
 *  needs to be aligned to a 32-byte boundary.  Some compilers allow you to use a
 *  #pragma directive to align a variable to a desired boundary.
 *
 * @return An error code or kStatus_DSPI_Success.
 */
dspi_status_t DSPI_DRV_EdmaMasterInit(uint32_t instance,
                                      dspi_edma_master_state_t * dspiEdmaState,
                                      const dspi_edma_master_user_config_t * userConfig,
                                      edma_software_tcd_t * stcdSrc2CmdDataLast);


/*!
 * @brief Shuts down a DSPI instance with the EDMA support.
 *
 * This function resets the DSPI peripheral, gates its clock, disables any used interrupts to
 * the core, and releases any used DMA channels.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @return kStatus_DSPI_Success indicating successful de-initialization
 */
dspi_status_t DSPI_DRV_EdmaMasterDeinit(uint32_t instance);


/*!
 * @brief Configures the DSPI master mode bus timing delay options with the EDMA support.
 *
 * This function uses the DSPI module delay options to
 * "fine tune" some of the signal timings and match the timing needs of a slower peripheral device.
 * This is an optional function that can be called after the DSPI module has been initialized for
 * master mode.
 * The bus timing delays that can be adjusted are listed below:
 *
 * PCS to SCK Delay: Adjustable delay option between the assertion of the PCS signal to the
 *                   first SCK edge.
 *
 * After SCK Delay: Adjustable delay option between the last edge of SCK to the de-assertion
 *                  of the PCS signal.
 *
 * Delay after Transfer:  Adjustable delay option between the de-assertion of the PCS signal for a
 *                        frame to the assertion of the PCS signal for the next frame. Note that this
 *                        is not adjustable for continuous clock mode because this delay is fixed at
 *                        one SCK period.
 *
 * Each of the above delay parameters uses both a pre-scalar and scalar value to calculate the
 * needed delay. This function takes  the desired delay type as a parameter and the
 * delay value (in nanoseconds), calculates the values needed for the prescaler and scaler.
 * Returning the actual calculated delay as an exact delay match may not be possible. In this
 * situation, the closest match is calculated without going below the desired delay value input.
 * It is possible to input a very large delay value that exceeds the capability of the part, in
 * which case the maximum supported delay is returned.  In addition, the function returns
 * an out-of-range status.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param whichDelay The desired delay to configure, must be of type dspi_delay_type_t
 * @param delayInNanoSec The desired delay value in nanoseconds.
 * @param calculatedDelay The calculated delay that best matches the desired
 *        delay (in nanoseconds).
 * @return Either kStatus_DSPI_Success or kStatus_DSPI_OutOfRange if the desired delay exceeds
 *         the capability of the device.
 */
dspi_status_t DSPI_DRV_EdmaMasterSetDelay(uint32_t instance, dspi_delay_type_t whichDelay,
                                          uint32_t delayInNanoSec, uint32_t * calculatedDelay);

/*@}*/

/*!
 * @name Bus configuration
 * @{
 */

/*!
 * @brief Configures the DSPI port physical parameters to access a device on the bus with the EDMA
 *        support.
 *
 * The term "device" describes the SPI device for which the DSPI master is communicating.
 * The user has two options to configure the device parameters: pass in the
 * pointer to the device configuration structure to the desired transfer function (see
 * DSPI_DRV_EdmaMasterTransferBlocking or DSPI_DRV_EdmaMasterTransfer) or pass it in to the
 * DSPI_DRV_EdmaMasterConfigureBus function.  The user can pass in a device structure to the
 * transfer function which contains the parameters for the bus (the transfer function then calls
 * this function). However, the user has the option to call this function directly 
 * to get the calculated baud rate, at which point, the user may pass in NULL for the device
 * structure in the transfer function (assuming they have called this configure bus function
 * first). This is an example to set up the dspi_device_t structure to call
 * the DSPI_DRV_EdmaMasterConfigureBus function by passing in these parameters:
   @code
    dspi_edma_device_t spiDevice;
    spiDevice.dataBusConfig.bitsPerFrame = 16;
    spiDevice.dataBusConfig.clkPhase = kDspiClockPhase_FirstEdge;
    spiDevice.dataBusConfig.clkPolarity = kDspiClockPolarity_ActiveHigh;
    spiDevice.dataBusConfig.direction = kDspiMsbFirst;
    spiDevice.bitsPerSec = 50000;
    DSPI_DRV_EdmaMasterConfigureBus(instance, &spiDevice, &calculatedBaudRate);
   @endcode
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param device Pointer to the device information structure. This structure contains the settings
 *  for the SPI bus configuration.  The device parameters are the desired baud rate (in
 *  bits-per-sec), and the data format field which consists of bits-per-frame, clock polarity and
 *  phase, and data shift direction.
 * @param calculatedBaudRate The calculated baud rate passed back to the user to determine
 *  if the calculated baud rate is close enough to meet the needs. The baud rate never exceeds
 *  the desired baud rate.
 * @return An error code or kStatus_DSPI_Success.
 */
dspi_status_t DSPI_DRV_EdmaMasterConfigureBus(uint32_t instance,
                                              const dspi_edma_device_t * device,
                                              uint32_t * calculatedBaudRate);

/*@}*/

/*!
 * @name Blocking transfers
 * @{
 */

/*!
 * @brief Performs a blocking SPI master mode transfer with the EDMA support.
 *
 * This function simultaneously sends and receives data on the SPI bus, because the SPI is naturally
 * a full-duplex bus. The function does not return until the transfer is complete.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param device Pointer to the device information structure. This structure contains the settings
 *  for the SPI bus configuration in this transfer. You may pass NULL for this
 *  parameter, in which case the current bus configuration is used unmodified. The device can be
 *  configured separately by calling the DSPI_DRV_EdmaMasterConfigureBus function.
 * @param sendBuffer The pointer to the data buffer of the data to send. You may pass NULL for this
 *  parameter and  bytes with a value of 0 (zero) is sent.
 * @param receiveBuffer Pointer to the buffer where the received bytes are stored. If you pass NULL
 *  for this parameter, the received bytes are ignored.
 * @param transferByteCount The number of bytes to send and receive.
 * @param timeout A timeout for the transfer in milliseconds. If the transfer takes longer than
 *  this amount of time, the transfer is aborted and a kStatus_SPI_Timeout error
 *  returned.
 *
 * @return kStatus_DSPI_Success The transfer was successful, or
 *         kStatus_DSPI_Busy Cannot perform transfer because a transfer is already in progress, or
 *         kStatus_DSPI_Timeout The transfer timed out and was aborted.
 */
dspi_status_t DSPI_DRV_EdmaMasterTransferBlocking(uint32_t instance,
                                                  const dspi_edma_device_t * device,
                                                  const uint8_t * sendBuffer,
                                                  uint8_t * receiveBuffer,
                                                  size_t transferByteCount,
                                                  uint32_t timeout);
/*@}*/

/*!
 * @name Non-blocking transfers
 * @{
 */

/*!
 * @brief Performs a non-blocking SPI master mode transfer with the EDMA support.
 *
 * This function  returns immediately. The user must check back
 * whether the transfer is complete (using the DSPI_DRV_EdmaMasterGetTransferStatus function).
 * This function simultaneously sends and receives data on the SPI bus because the SPI is
 * a full-duplex bus.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param device Pointer to the device information structure. This structure contains the settings
 *  for the SPI bus configuration in this transfer. You may pass NULL for this
 *  parameter, in which case the current bus configuration is used unmodified. The device can be
 *  configured separately by calling the DSPI_DRV_EdmaMasterConfigureBus function.
 * @param sendBuffer The pointer to the data buffer of the data to send. You may pass NULL for this
 *  parameter, in which case bytes with a value of 0 (zero) are sent.
 * @param receiveBuffer Pointer to the buffer where the received bytes are stored. If you pass NULL
 *  for this parameter, the received bytes are ignored.
 * @param transferByteCount The number of bytes to send and receive.
 *
 * @return kStatus_DSPI_Success The transfer was successful, or
 *         kStatus_DSPI_Busy Cannot perform transfer because a transfer is already in progress.
 */
dspi_status_t DSPI_DRV_EdmaMasterTransfer(uint32_t instance,
                                          const dspi_edma_device_t * device,
                                          const uint8_t * sendBuffer,
                                          uint8_t * receiveBuffer,
                                          size_t transferByteCount);


/*!
 * @brief Returns whether the previous transfer is completed with the EDMA support.
 *
 * When performing an a-sync transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can get the number of words that have been
 * transferred up to now.
 *
 * @param instance The instance number of the DSPI peripheral.
 * @param framesTransferred Pointer to value populated with the number of frames that
 *  have been sent during the active transfer. A frame is defined as the number of bits per frame.
 *
 * @return kStatus_DSPI_Success The transfer has completed successfully, or
 *         kStatus_DSPI_Busy The transfer is still in progress. framesTransferred is filled
 *         with the number of words that have been transferred so far.
 */
dspi_status_t DSPI_DRV_EdmaMasterGetTransferStatus(uint32_t instance, uint32_t * framesTransferred);

/*!
 * @brief Terminates an asynchronous transfer early with the EDMA support.
 *
 * During an a-sync transfer, the user has the option to terminate the transfer early if the transfer
 * is still in progress.
 *
 * @param instance The instance number of the DSPI peripheral.
 *
 * @return kStatus_DSPI_Success The transfer was successful, or
 *         kStatus_DSPI_NoTransferInProgress No transfer is currently in progress.
 */
dspi_status_t DSPI_DRV_EdmaMasterAbortTransfer(uint32_t instance);

/*!
 * @brief Interrupt handler for DSPI master mode.
 * This handler uses the buffers stored in the dspi_master_state_t structures to transfer data.
 *
 * @param instance The instance number of the DSPI peripheral.
 */
void DSPI_DRV_EdmaMasterIRQHandler(uint32_t instance);

/* @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
#endif /* __FSL_DSPI_EDMA_MASTER_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

