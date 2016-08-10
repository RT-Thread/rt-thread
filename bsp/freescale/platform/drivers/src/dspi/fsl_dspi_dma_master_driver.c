/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include <string.h>
#include "fsl_dspi_dma_master_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Pointer to runtime state structure.*/
extern void * g_dspiStatePtr[SPI_INSTANCE_COUNT];

/* For storing DMA intermediate buffers between the source buffer and TX FIFO */
static uint32_t s_cmdData;      /* Intermediate 16-bit command and 16-bit data buffer */
static uint32_t s_lastCmdData;  /* Consists of the last command and the final source data */
static uint16_t s_wordToSend; /* Word to send, if no send buffer, this variable is used
                                 as the word to send, which should be initialized to 0. Needs
                                 to be static and stored in data section as this variable
                                 address is the source address if no source buffer.  */
static uint8_t s_rxBuffIfNull; /* If no receive buffer provided, direct rx DMA channel to this
                                  destination */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static dspi_status_t DSPI_DRV_DmaMasterStartTransfer(uint32_t instance,
                                                      const dspi_dma_device_t * device,
                                                      const uint8_t * sendBuffer,
                                                      uint8_t * receiveBuffer,
                                                      size_t transferByteCount);

static void DSPI_DRV_DmaMasterCompleteTransfer(uint32_t instance);
static void DSPI_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static void DSPI_DRV_DmaTxLastCallback(void *param, dma_channel_status_t status);
static void DSPI_DRV_DmaRxCallback(void *param, dma_channel_status_t status);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterInit
 * Description   : Initializes a DSPI instance for master mode operation to work with DMA.
 * This function uses a dma driven method for transferring data.
 * This function initializes the run-time state structure to track the ongoing
 * transfers, ungates the clock to the DSPI module, resets the DSPI module, initializes the module
 * to user defined settings and default settings, configures the IRQ state structure, enables
 * the module-level interrupt to the core, and enables the DSPI module.
 * The CTAR parameter is special in that it allows the user to have different SPI devices
 * connected to the same DSPI module instance in addition to different peripheral chip
 * selects. Each CTAR contains the bus attributes associated with that particular SPI device.
 * For most use cases where only one SPI device is connected per DSPI module
 * instance, use CTAR0.
 * This is an example to set up and call the DSPI_DRV_DmaMasterInit function by passing
 * in these parameters:
 *   dspi_dma_master_state_t dspiDmaState; <- the user simply allocates memory for this struct
 *   uint32_t calculatedBaudRate;
 *   dspi_dma_master_user_config_t userConfig; <- the user fills out members for this struct
 *   userConfig.isChipSelectContinuous = false;
 *   userConfig.isSckContinuous = false;
 *   userConfig.pcsPolarity = kDspiPcs_ActiveLow;
 *   userConfig.whichCtar = kDspiCtar0;
 *   userConfig.whichPcs = kDspiPcs0;
 *   DSPI_DRV_DmaMasterInit(masterInstance, &dspiDmaState, &userConfig);
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterInit(uint32_t instance,
                                      dspi_dma_master_state_t * dspiDmaState,
                                      const dspi_dma_master_user_config_t * userConfig)
{
    uint32_t dspiSourceClock;
    SPI_Type *base = g_dspiBase[instance];
    dma_request_source_t dspiTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t dspiRxDmaRequest = kDmaRequestMux0Disable;

    /* Check parameter pointers to make sure there are not NULL */
    if ((dspiDmaState == NULL) || (userConfig == NULL))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* Clear the run-time state struct for this instance.*/
    memset(dspiDmaState, 0, sizeof(* dspiDmaState));

    /* Note, remember to first enable clocks to the DSPI module before making any register accesses
     * Enable clock for DSPI
     */
    CLOCK_SYS_EnableSpiClock(instance);
    /* Get module clock freq*/
    dspiSourceClock = CLOCK_SYS_GetSpiFreq(instance);

    /* Configure the run-time state struct with the DSPI source clock */
    dspiDmaState->dspiSourceClock = dspiSourceClock;

    /* Configure the run-time state struct with the data command parameters*/
    dspiDmaState->whichCtar = userConfig->whichCtar;  /* set the dspiDmaState struct CTAR*/
    dspiDmaState->whichPcs = userConfig->whichPcs;  /* set the dspiDmaState struct whichPcs*/
    dspiDmaState->isChipSelectContinuous = userConfig->isChipSelectContinuous; /* continuous PCS*/

    /* Initialize the DSPI module registers to default value, which disables the module */
    DSPI_HAL_Init(base);

    /* Init the interrupt sync object.*/
    if (OSA_SemaCreate(&dspiDmaState->irqSync, 0) != kStatus_OSA_Success)
    {
        return kStatus_DSPI_Error;
    }

    /* Set to master mode.*/
    DSPI_HAL_SetMasterSlaveMode(base, kDspiMaster);

    /* Configure for continuous SCK operation*/
    DSPI_HAL_SetContinuousSckCmd(base, userConfig->isSckContinuous);

    /* Configure for peripheral chip select polarity*/
    DSPI_HAL_SetPcsPolarityMode(base, userConfig->whichPcs, userConfig->pcsPolarity);

    /* Enable fifo operation (regardless of FIFO depth) */
    DSPI_HAL_SetFifoCmd(base, true, true);

    /* Initialize the configurable delays: PCS-to-SCK, prescaler = 0, scaler = 1 */
    DSPI_HAL_SetDelay(base, userConfig->whichCtar, 0, 1, kDspiPcsToSck);

    /* Save runtime structure pointers to irq handler can point to the correct state structure*/
    g_dspiStatePtr[instance] = dspiDmaState;

    /* enable the interrupt*/
    INT_SYS_EnableIRQ(g_dspiIrqId[instance]);

    /* DSPI system enable */
    DSPI_HAL_Enable(base);


    /* Request DMA channels from the DMA peripheral driver.
     * Note, some MCUs have a separate RX and TX DMA request for each DSPI instance, while
     * other MCUs have a separate RX and TX DMA request for DSPI instance 0 only and shared DMA
     * requests for all other instances. Therefore, use the DSPI feature file to distinguish
     * how to request DMA channels between the various MCU DSPI instances.
     * For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
     * trigger ongoing transfers and will link to the TX DMA channel from the RX DMA channel.
     */

    switch (instance)
    {
        case 0:
            /* SPI0 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(0)
            dspiRxDmaRequest = kDmaRequestMux0SPI0Rx;
            dspiTxDmaRequest = kDmaRequestMux0SPI0Tx;
#else
            /* DMA is simple link control, so DSPI - DMA driver does not support the case that DSPI have
             * shared DMA channels
             */
            return kStatus_DSPI_DMAChannelInvalid;
#endif
            break;
#if (SPI_INSTANCE_COUNT > 1)
        case 1:
            /* SPI1 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(1)
            dspiRxDmaRequest = kDmaRequestMux0SPI1Rx;
            dspiTxDmaRequest = kDmaRequestMux0SPI1Tx;
#else
            /* DMA is simple link control, so DSPI - DMA driver does not support the case that DSPI have
             * shared DMA channels
             */
            return kStatus_DSPI_DMAChannelInvalid;
#endif
            break;
#endif
#if (SPI_INSTANCE_COUNT > 2)
        case 2:
            /* SPI2 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(2)
            dspiRxDmaRequest = kDmaRequestMux0SPI2Rx;
            dspiTxDmaRequest = kDmaRequestMux0SPI2Tx;
#else
            /* DMA is simple link control, so DSPI - DMA driver does not support the case that DSPI have
             * shared DMA channels
             */
            return kStatus_DSPI_DMAChannelInvalid;
#endif
            break;
#endif
        default :
            return kStatus_DSPI_InvalidInstanceNumber;
    }

    /* This channel transfers data from RX FIFO to receiveBuffer */
    if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                      dspiRxDmaRequest,
                                                      &dspiDmaState->dmaRxChannel))
    {
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /* This channel transfers data from transmitBuffer to TX FIFO */
    if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                      dspiTxDmaRequest,
                                                      &dspiDmaState->dmaTxDataChannel))
    {
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /* Source buffer to intermediate command/data
     * This channel is not activated by dma request, but by channel link.
     */
    if (DMA_DRV_RequestChannel(kDmaAnyChannel,
                            kDmaRequestMux0Disable,
                            &dspiDmaState->dmaTxCmdChannel) == kDmaInvalidChannel)
    {
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /* Start the transfer process in the hardware */
    DSPI_HAL_StartTransfer(base);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterDeinit
 * Description   : Shuts down a DSPI instance with DMA support.
 *
 * This function resets the DSPI peripheral, gates its clock, disables any used interrupts to
 * the core, and releases any used DMA channels.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterDeinit(uint32_t instance)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* First stop transfers */
    DSPI_HAL_StopTransfer(base);

    /* Restore the module to defaults then power it down. This also disables the DSPI module.*/
    DSPI_HAL_Init(base);

    /* destroy the interrupt sync object.*/
    OSA_SemaDestroy(&dspiDmaState->irqSync);

    /* disable the interrupt*/
    INT_SYS_DisableIRQ(g_dspiIrqId[instance]);

    /* Gate the clock for DSPI.*/
    CLOCK_SYS_DisableSpiClock(instance);

    /* Release all of the DMA channels used in the driver. DMA channel structures are stored in
     * the run-time state structure.
     */
    DMA_DRV_FreeChannel(&dspiDmaState->dmaTxDataChannel);
    DMA_DRV_FreeChannel(&dspiDmaState->dmaTxCmdChannel);
    DMA_DRV_FreeChannel(&dspiDmaState->dmaRxChannel);

    /* Clear state pointer. */
    g_dspiStatePtr[instance] = NULL;

    return kStatus_DSPI_Success;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterSetDelay
 * Description   : Configures the DSPI master mode bus timing delay options with DMA support.
 *
 * This function allows the user to take advantage of the DSPI module's delay options in order to
 * "fine tune" some of the signal timings to match the timing needs of a slower peripheral device.
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
 *                        frame to the assertion of the PCS signal for the next frame. Note this
 *                        is not adjustable for continuous clock mode as this delay is fixed at
 *                        one SCK period.
 *
 * Each of the above delay parameters use both a pre-scalar and scalar value to calculate the
 * needed delay. This function takes in as a parameter the desired delay type and the
 * delay value (in nanoseconds), calculates the values needed for the prescaler and scaler.
 * Returning the actual calculated delay as an exact delay match may not be possible. In this
 * case, the closest match is calculated without going below the desired delay value input.
 * It is possible to input a very large delay value that exceeds the capability of the part, in
 * which case the maximum supported delay is returned.  In addition, the function returns
 * an out-of-range status.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterSetDelay(uint32_t instance, dspi_delay_type_t whichDelay,
                                         uint32_t delayInNanoSec, uint32_t * calculatedDelay)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];
    dspi_status_t errorCode = kStatus_DSPI_Success;

    *calculatedDelay = DSPI_HAL_CalculateDelay(base, dspiDmaState->whichCtar, whichDelay,
                                               dspiDmaState->dspiSourceClock, delayInNanoSec);

    /* If the desired delay exceeds the capability of the device, alert the user */
    if (*calculatedDelay < delayInNanoSec)
    {
        errorCode = kStatus_DSPI_OutOfRange;
    }

    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterConfigureBus
 * Description   : Configures the DSPI port physical parameters to access a device on the bus with
 *                 DMA support.
 *
 * The term "device" is used to indicate the SPI device for which the DSPI master is communicating.
 * The user has two options to configure the device parameters: either pass in the
 * pointer to the device configuration structure to the desired transfer function (see
 * DSPI_DRV_DmaMasterTransferBlocking or DSPI_DRV_DmaMasterTransfer) or pass it in to the
 * DSPI_DRV_DmaMasterConfigureBus function.  The user can pass in a device structure to the
 * transfer function which contains the parameters for the bus (the transfer function then calls
 * this function). However, the user has the option to call this function directly especially
 * to get the calculated baud rate, at which point they may pass in NULL for the device
 * structure in the transfer function (assuming they have called this configure bus function
 * first). This is an example to set up the dspi_device_t structure to call
 * the DSPI_DRV_DmaMasterConfigureBus function by passing in these parameters:
 *   dspi_dma_device_t spiDevice;
 *   spiDevice.dataBusConfig.bitsPerFrame = 16;
 *   spiDevice.dataBusConfig.clkPhase = kDspiClockPhase_FirstEdge;
 *   spiDevice.dataBusConfig.clkPolarity = kDspiClockPolarity_ActiveHigh;
 *   spiDevice.dataBusConfig.direction = kDspiMsbFirst;
 *   spiDevice.bitsPerSec = 50000;
 *   DSPI_DRV_DmaMasterConfigureBus(instance, &spiDevice, &calculatedBaudRate);
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterConfigureBus(uint32_t instance,
                                             const dspi_dma_device_t * device,
                                             uint32_t * calculatedBaudRate)
{
    assert(device);
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    dspi_status_t errorCode = kStatus_DSPI_Success;

    /* Configure the bus to access the provided device.*/
    *calculatedBaudRate = DSPI_HAL_SetBaudRate(base, dspiDmaState->whichCtar,
                                               device->bitsPerSec, dspiDmaState->dspiSourceClock);

    errorCode = DSPI_HAL_SetDataFormat(base, dspiDmaState->whichCtar, &device->dataBusConfig);

    /* Check bits/frame number */
    if (device->dataBusConfig.bitsPerFrame > 16)
    {
        errorCode = kStatus_DSPI_OutOfRange;
    }
    else
    {
        dspiDmaState->bitsPerFrame = device->dataBusConfig.bitsPerFrame; /* update bits/frame */
    }

    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterTransferBlocking
 * Description   : Performs a blocking SPI master mode transfer with DMA support.
 *
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus. The function does not return until the transfer is complete.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterTransferBlocking(uint32_t instance,
                                                  const dspi_dma_device_t * device,
                                                  const uint8_t * sendBuffer,
                                                  uint8_t * receiveBuffer,
                                                  size_t transferByteCount,
                                                  uint32_t timeout)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];
    dspi_status_t error = kStatus_DSPI_Success;

    /* If the transfer count is zero, then return immediately.*/
    if (transferByteCount == 0)
    {
        return kStatus_DSPI_InvalidParameter;
    }

    dspiDmaState->isTransferBlocking = true; /* Indicates this is a blocking transfer */
    /* As this is a synchronous transfer, set up the sync status variable*/
    osa_status_t syncStatus;

    if (DSPI_DRV_DmaMasterStartTransfer(instance, device, sendBuffer, receiveBuffer,
                                         transferByteCount) == kStatus_DSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    /* As this is a synchronous transfer, wait until the transfer is complete.*/
    do
    {
        syncStatus = OSA_SemaWait(&dspiDmaState->irqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);

    /* If a timeout occurs, stop the transfer by setting the isTransferInProgress to false and
     * disabling DMA requests and interrupts, then return the timeout error status.
     */
    if (syncStatus != kStatus_OSA_Success)
    {
        /* The transfer is complete.*/
        dspiDmaState->isTransferInProgress = false;

        /* Disable the Receive FIFO Drain DMA Request */
        DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, false);

        /* Disable TFFF DMA request */
        DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);

        /* Disable End of Queue request */
        DSPI_HAL_SetIntMode(base, kDspiEndOfQueue, false);

        error = kStatus_DSPI_Timeout;
    }

    return error;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterTransfer
 * Description   : Performs a non-blocking SPI master mode transfer with DMA support.
 *
 * This function  returns immediately. The user must check back to
 * check whether the transfer is complete (using the DSPI_DRV_DmaMasterGetTransferStatus function).
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterTransfer(uint32_t instance,
                                          const dspi_dma_device_t * device,
                                          const uint8_t * sendBuffer,
                                          uint8_t * receiveBuffer,
                                          size_t transferByteCount)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance]; 

    /* If the transfer count is zero, then return immediately.*/
    if (transferByteCount == 0)
    {
        return kStatus_DSPI_InvalidParameter;
    }

    dspiDmaState->isTransferBlocking = false; /* Indicates this is not a blocking transfer */
    /* start the transfer process*/
    if (DSPI_DRV_DmaMasterStartTransfer(instance, device, sendBuffer, receiveBuffer,
                                         transferByteCount) == kStatus_DSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    /* Else, return immediately as this is an async transfer */
    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterGetTransferStatus
 * Description   : Returns whether the previous transfer is finished with DMA support.
 *
 * When performing an a-sync transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can get the number of words that have been
 * transferred up to now.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterGetTransferStatus(uint32_t instance, uint32_t * framesTransferred)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* Fill in the bytes transferred.*/
    if (framesTransferred)
    {
        *framesTransferred = DSPI_HAL_GetTransferCount(base);
    }

    return (dspiDmaState->isTransferInProgress ? kStatus_DSPI_Busy : kStatus_DSPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaMasterAbortTransfer
 * Description   : Terminates an asynchronous transfer early with DMA support.
 *
 * During an async transfer, the user has the option to terminate the transfer early if the transfer
 * is still in progress.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaMasterAbortTransfer(uint32_t instance)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];

    /* Check if a transfer is running.*/
    if (!dspiDmaState->isTransferInProgress)
    {
        return kStatus_DSPI_NoTransferInProgress;
    }

    /* Stop the running transfer.*/
    DSPI_DRV_DmaMasterCompleteTransfer(instance);

    return kStatus_DSPI_Success;
}

/*!
 * @brief Initiate (start) a transfer using DMA. This is not a public API as it is called from
 *  other driver functions
 */
static dspi_status_t DSPI_DRV_DmaMasterStartTransfer(uint32_t instance,
                                                      const dspi_dma_device_t * device,
                                                      const uint8_t * sendBuffer,
                                                      uint8_t * receiveBuffer,
                                                      size_t transferByteCount)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    /* For temporarily storing DMA instance and channel */
    uint8_t transferSizeInBytes = 1U;

    uint32_t calculatedBaudRate;
    dspi_command_config_t command;  /* create an instance of the data command struct*/
    SPI_Type *base = g_dspiBase[instance];
    uint32_t txTransferByteCnt = 0;
    uint32_t rxTransferByteCnt = 0;

    /* Initialize s_wordToSend */
    s_wordToSend = 0;

    /* Check that we're not busy.*/
    if (dspiDmaState->isTransferInProgress)
    {
        return kStatus_DSPI_Busy;
    }

    /* Calculate the transfer size on bits/frame */
    if (dspiDmaState->bitsPerFrame <= 8)
    {
        transferSizeInBytes = 1U;
    }
    else if (dspiDmaState->bitsPerFrame <= 16)
    {
        transferSizeInBytes = 2U;
    }
    else
    {
        transferSizeInBytes = 4U;
    }

    /* Configure bus for this device. If NULL is passed, we assume the caller has
     * preconfigured the bus using DSPI_DRV_DmaMasterConfigureBus().
     * Do nothing for calculatedBaudRate. If the user wants to know the calculatedBaudRate
     * then they can call this function separately.
     */
    if (device)
    {
        DSPI_DRV_DmaMasterConfigureBus(instance, device, &calculatedBaudRate);
        dspiDmaState->bitsPerFrame = device->dataBusConfig.bitsPerFrame; /*update bits/frame*/
    }

    /* Check the transfer byte count. If bits/frame > 8, meaning 2 bytes, and if
     * the transfer byte count is an odd count we'll have to increase the TX transfer byte count
     * by one and assert a flag to indicate to the send functions that it will
     * need to handle an extra byte.
     * For receive, we actually round down the transfer count to the next lowest even number.
     * Then in the interrupt handler, we take care of geting this last byte.
     */
    if ((dspiDmaState->bitsPerFrame > 8) && (transferByteCount & 1UL))
    {
        dspiDmaState->extraByte = true;
        txTransferByteCnt = transferByteCount + 1U;  /* Increment to next even byte count */
        rxTransferByteCnt = transferByteCount & ~1U;  /* Decrement to next even byte count */
    }
    else
    {
        dspiDmaState->extraByte = false;
        txTransferByteCnt = transferByteCount;
        rxTransferByteCnt = transferByteCount;
    }
    /* Store the receiveBuffer pointer and receive byte count to the run-time state struct
     * for later use in the interrupt handler.
     */
    dspiDmaState->rxBuffer = (uint8_t *)receiveBuffer;
    dspiDmaState->rxTransferByteCnt = rxTransferByteCnt;

    /* Save information about the transfer for use by the ISR.*/
    dspiDmaState->isTransferInProgress = true;

    /* Reset the transfer counter to 0. Normally this is done via the PUSHR[CTCNT], but as we
     * are under DMA controller, we won't be able to change this bit dynamically after the
     * first word is transferred.
     */
    DSPI_HAL_PresetTransferCount(base, 0);

    /* flush the fifos*/
    DSPI_HAL_SetFlushFifoCmd(base, true, true);

    /* Clear status flags that may have been set from previous transfers */
    DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
    DSPI_HAL_ClearStatusFlag(base, kDspiEndOfQueue);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoUnderflow);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);
    DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoOverflow);
    DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoDrainRequest);

    /************************************************************************************
     * Set up the RX DMA channel Transfer Control Descriptor (TCD)
     * Do this before filling the TX FIFO.
     * Note, if there is no remaining receive count, then bypass RX DMA set up.
     * This means we only have one byte to read of a 16-bit data word and will read this
     * in the complete transfer function.
     ***********************************************************************************/
    /* If a receive buffer is used and if rxTransferByteCnt > 0 */
    if (rxTransferByteCnt)
    {
        if (!receiveBuffer)
        {
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&dspiDmaState->dmaRxChannel,
                                   kDmaPeripheralToPeripheral,
                                   transferSizeInBytes,
                                   DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                                   (uint32_t)(&s_rxBuffIfNull), /* dest is temporary location */
                                   (uint32_t)(rxTransferByteCnt));
        }
        else
        {
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&dspiDmaState->dmaRxChannel,
                                   kDmaPeripheralToMemory,
                                   transferSizeInBytes,
                                   DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                                   (uint32_t)(receiveBuffer), /* dest is rx buffer */
                                   (uint32_t)(rxTransferByteCnt));

            /* Destination size is only 1 byte */
            DMA_DRV_SetDestTransferSize(&dspiDmaState->dmaRxChannel, 1U);
        }

        /* Enable the DMA peripheral request */
        DMA_DRV_StartChannel(&dspiDmaState->dmaRxChannel);
    }
    else if (dspiDmaState->extraByte)
    {
        /* Need to receive only one frame - extra byte by calling Rx callback function*/
        DSPI_DRV_DmaRxCallback((void *)instance, kDmaIdle);
    }

    /************************************************************************************
     * Set up the Last Command/data Word Intermediate Buffer and fill up the TX FIFO.
     ***********************************************************************************/
    /* Before sending the data, we first need to initialize the data command struct
     * Configure the data command attributes for the desired PCS, CTAR, and continuous PCS
     * which are derived from the run-time state struct
     */
    command.whichPcs = dspiDmaState->whichPcs;
    command.whichCtar = dspiDmaState->whichCtar;
    command.clearTransferCount = false; /* don't clear the transfer count */

    /************************************************************************
     * Next, set up the Last Command/data Word Intermediate Buffer before
     * filling up the TX FIFO
     * Create a 32-bit word with the final 16-bit command settings. This means
     * that EOQ = 1 and CONT = 0.
     * This 32-bit word will also be initialized with the final data byte/word
     * from the send source buffer and then the entire 32-bit word will be
     * transferred to the DSPI PUSHR.
     ************************************************************************/
    /* Declare a variable for storing the last send data (either 8- or 16-bit) */
    uint32_t lastWord = 0;

    /* If a send buffer was provided, the word comes from there. Otherwise we just send
     * a zero (initialized above).
     */
    if (sendBuffer)
    {
        /* Store the last byte from the send buffer */
        if (dspiDmaState->bitsPerFrame <= 8)
        {
            lastWord = sendBuffer[txTransferByteCnt-1]; /* Last byte */
        }
        /* Store the last two bytes the send buffer */
        else
        {
            /* If 16-bit transfers and odd transfer byte count then an extra byte was added
             * to the transfer byte count, but we cannot access more of the send buffer
             */
            if(!dspiDmaState->extraByte)
            {
                lastWord = sendBuffer[txTransferByteCnt-1] ; /* Save off the last byte */
                lastWord = lastWord << 8U; /* Shift to MSB (separate step due to MISHA) */
            }
            lastWord |= sendBuffer[txTransferByteCnt-2]; /* OR with next to last byte */
        }
    }

    /* Now, build the last command/data word intermediate buffer */
    command.isChipSelectContinuous = false; /* Always clear CONT for last data word */
    command.isEndOfQueue = true; /* Set EOQ for last data word */
    s_lastCmdData = DSPI_HAL_GetFormattedCommand(base, &command) | lastWord;
    /************************************************************************
     * Begin TX DMA channels transfer control descriptor set up.
     * 1. First, set up intermediate buffers which contain 16-bit commands.
     * 2. Set up the DMA Software Transfer Control Descriptors (STCD) for various
     *    scenarios:
     *    - Channel for intermediate buffer to TX FIFO
     *    - Channel for source buffer to intermediate buffer
     *    - STCD for scatter/gather for end of previous channel to replace
     *      intermediate buffer with last-command buffer.
     ************************************************************************/

    /************************************************************************
     * Intermediate Buffer
     * Create a 32-bit word with the 16-bit command settings. Data from
     * the send source buffer will be transferred here and then the entire
     * 32-bit word will be transferred to the DSPI PUSHR.
     * This buffer will be preloaded with the next data word in the send buffer
     ************************************************************************/
    /* restore the isChipSelectContinuous setting to the original value as it was cleared above */
    command.isChipSelectContinuous = dspiDmaState->isChipSelectContinuous;
    command.isEndOfQueue = false; /* Clear End of Queue (previously set for last cmd/data word)*/
    s_cmdData = DSPI_HAL_GetFormattedCommand(base, &command);

    /* Place the next data from the send buffer into the intermediate buffer (preload it)
     * based on whether it is one byte or two.
     */
    if (dspiDmaState->bitsPerFrame <= 8)
    {
        /* If a send buffer was provided, the word comes from there. Otherwise we just send
         * a zero (initialized above).
         */
        if (sendBuffer)
        {
            s_wordToSend = *sendBuffer;  /* queue up the next data */
            ++sendBuffer; /* increment to next data word*/
        }
        --txTransferByteCnt; /* decrement txTransferByteCnt*/
    }
    else
    {
        /* If a send buffer was provided, the word comes from there. Otherwise we just send
         * a zero (initialized above).
         */
        if (sendBuffer)
        {
            s_wordToSend = *sendBuffer;
            ++sendBuffer; /* increment to next data byte */

            /* Note, if the extraByte flag is set and we're down to the last two bytes we can still
             * do this even though we're going past the sendBuffer size. We're just reading data we
             * don't care about anyways since it is dummy data to make up for the last byte.
             */
            s_wordToSend |= (unsigned)(*sendBuffer) << 8U;
            ++sendBuffer; /* increment to next data byte */

        }
        txTransferByteCnt -= 2;  /* decrement txTransferByteCnt by 2 bytes */
    }

    s_cmdData |= s_wordToSend; /* write s_wordToSend to intermediate buffer */

    /* For Tx, DSPI need two DMA channel, one for calculate the command and data into one value
     * (dmaTxCmdChannel), and another for push the value into DSPI PUSHR register (dmaTxDataChannel).
     * The dmaTxCmdChannel DMA channel will be triggered by DSPI Tx FIFO, and the dmaTxDataChannel
     * DMA channel will be linked to calculate DMA channel and triggered by this channel also.
     */

    /* If the transfer size is less than size of one frame, only transmit the last byte that calculated */
    if (!txTransferByteCnt)
    {
        DMA_DRV_ConfigTransfer(&dspiDmaState->dmaTxDataChannel, kDmaMemoryToPeripheral,
                               4u, (uint32_t)(&s_lastCmdData),
                               DSPI_HAL_GetMasterPushrRegAddr(base), 4u);
        /* Register callback for last byte transmitting */
        DMA_DRV_RegisterCallback(&dspiDmaState->dmaTxDataChannel, DSPI_DRV_DmaTxLastCallback, (void *)instance);
    }
    else
    {
        /* Config DMA to copy data from generated cmd data to FIFO */
        if (dspiDmaState->bitsPerFrame <= 8)
        {
            DMA_DRV_ConfigTransfer(&dspiDmaState->dmaTxDataChannel, kDmaPeripheralToPeripheral,
                                   4u, (uint32_t)(&s_cmdData),
                                   DSPI_HAL_GetMasterPushrRegAddr(base),
                                   (uint32_t)((txTransferByteCnt) * 4));
        }
        else
        {
            DMA_DRV_ConfigTransfer(&dspiDmaState->dmaTxDataChannel, kDmaPeripheralToPeripheral,
                                   4u, (uint32_t)(&s_cmdData),
                                   DSPI_HAL_GetMasterPushrRegAddr(base),
                                   (uint32_t)((txTransferByteCnt) * 2));
        }
        /* Register Tx callback function */
        DMA_DRV_RegisterCallback(&dspiDmaState->dmaTxDataChannel, DSPI_DRV_DmaTxCallback, (void *)instance);

        /* Config dmaTxCmdChannel channel if send buffer is provided */
        if (sendBuffer)
        {
            dma_channel_link_config_t config;
            DMA_DRV_ConfigTransfer(&dspiDmaState->dmaTxCmdChannel, kDmaMemoryToPeripheral,
                                    1u, (uint32_t)(sendBuffer),
                                    (uint32_t)(&s_cmdData),
                                    (uint32_t)(txTransferByteCnt - transferSizeInBytes));
            if (dspiDmaState->bitsPerFrame > 8)
            {
                DMA_DRV_SetDestTransferSize(&dspiDmaState->dmaTxCmdChannel, 2U);
            }

            /* Link dmaTxCmdChannel after dmaTxDataChannel */
            config.channel1 = dspiDmaState->dmaTxCmdChannel.channel;
            config.channel2 = 0;
            config.linkType = kDmaChannelLinkChan1;
            DMA_DRV_ConfigChanLink(&dspiDmaState->dmaTxDataChannel, &config);
            /* start channel */
            DMA_DRV_StartChannel(&dspiDmaState->dmaTxCmdChannel);
        }
    }

    /* Register callback */
    DMA_DRV_RegisterCallback(&dspiDmaState->dmaRxChannel, DSPI_DRV_DmaRxCallback, (void *)instance);

    /* Enable the Receive FIFO Drain DMA Request */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, true);

    /* Enable TFFF DMA request */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, true);

    /* Enable the DMA peripheral request */
    DMA_DRV_StartChannel(&dspiDmaState->dmaTxDataChannel);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaRxCallback
 * Description   : Callback function, this called when DMA receiving data
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    uint32_t instance = (uint32_t)param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];

    /* Stop DMA Rx channel */
    DMA_DRV_StopChannel(&dspiDmaState->dmaRxChannel);

    if (dspiDmaState->extraByte != 0)
    {
        /* Have one more byte, config DMA Rx channel to receive this byte */
        DMA_DRV_ConfigTransfer(&dspiDmaState->dmaRxChannel,
                               kDmaPeripheralToPeripheral,
                               1u, DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                               (uint32_t)(&s_rxBuffIfNull), /* dest is temporary location */
                               (uint32_t)(1u));

        /* Register callback */
        DMA_DRV_RegisterCallback(&dspiDmaState->dmaRxChannel, DSPI_DRV_DmaRxCallback, (void *)instance);

        /* Enable the DMA peripheral request */
        DMA_DRV_StartChannel(&dspiDmaState->dmaRxChannel);

        if (dspiDmaState->rxBuffer)
        {
            /* Update the receive pointer to extra byte */
            dspiDmaState->rxBuffer = dspiDmaState->rxBuffer + dspiDmaState->rxTransferByteCnt;
        }
        dspiDmaState->rxTransferByteCnt = 0;
        dspiDmaState->extraByte = false;

        return;
    }

    /* If transmission completed, stop the transferring */
    if ((dspiDmaState->isTransferInProgress) &&
             (dspiDmaState->rxTransferByteCnt == 0))
    {
        /* Extra byte completed */
        if (dspiDmaState->rxBuffer)
        {
            /* Store the extra byte */
            *dspiDmaState->rxBuffer = (uint8_t)s_rxBuffIfNull;
        }
        /* Stop DMA Rx channel */
        DMA_DRV_StopChannel(&dspiDmaState->dmaRxChannel);

        DSPI_DRV_DmaMasterCompleteTransfer(instance);
    }
    else
    {
        /* Stop DMA Rx channel */
        DMA_DRV_StopChannel(&dspiDmaState->dmaRxChannel);

        DSPI_DRV_DmaMasterCompleteTransfer(instance);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaTxLastCallback
 * Description   : Callback function, this called when DMA transmitting the last frame
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaTxLastCallback(void *param, dma_channel_status_t status)
{
    uint32_t instance = (uint32_t)param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];

    /* Stop DMA Tx channel */
    DMA_DRV_StopChannel(&dspiDmaState->dmaTxDataChannel);

    /* Disable Tx Fifo fill interrupt */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaTxCallback
 * Description   : Callback function, this called when DMA transmitting data
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    uint32_t instance = (uint32_t)param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    uint32_t dmaChannel;
    DMAMUX_Type *dmamuxbase;

    dmaChannel = dspiDmaState->dmaTxDataChannel.channel;
    dmamuxbase = g_dmamuxBase[dmaChannel/FSL_FEATURE_DMAMUX_MODULE_CHANNEL];
    // DMA_DRV_ClearStatus(&dspiDmaState->dmaTxDataChannel);
    DMAMUX_HAL_SetChannelCmd(dmamuxbase, dmaChannel, false);
    DMAMUX_HAL_SetChannelCmd(dmamuxbase, dmaChannel, true);

    /* Stop DMA Tx channel */
    DMA_DRV_StopChannel(&dspiDmaState->dmaTxDataChannel);

    /* Setup DMA to transmit the last frame */
    /* Have one more byte, config DMA Rx channel to receive this byte */
    DMA_DRV_ConfigTransfer(&dspiDmaState->dmaTxDataChannel,
                           kDmaPeripheralToPeripheral,
                           4u, (uint32_t)(&s_lastCmdData), /* src is data register */
                           DSPI_HAL_GetMasterPushrRegAddr(base), /* dest is temporary location */
                           4u);

    /* Register callback */
    DMA_DRV_RegisterCallback(&dspiDmaState->dmaTxDataChannel, DSPI_DRV_DmaTxLastCallback, (void *)instance);

    /* Enable the DMA peripheral request */
    DMA_DRV_StartChannel(&dspiDmaState->dmaTxDataChannel);
}

/*!
 * @brief Finish up a transfer.
 * Cleans up after a transfer is complete. Interrupts are disabled, and the DSPI module
 * is disabled. This is not a public API as it is called from other driver functions.
 */
static void DSPI_DRV_DmaMasterCompleteTransfer(uint32_t instance)
{
    /* instantiate local variable of type dspi_dma_master_state_t and point to global state */
    dspi_dma_master_state_t * dspiDmaState = (dspi_dma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* The transfer is complete.*/
    dspiDmaState->isTransferInProgress = false;

    /* Disable the Receive FIFO Drain DMA Request */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, false);

    /* Disable TFFF DMA request */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);

    if (dspiDmaState->isTransferBlocking)
    {
        /* Signal the synchronous completion object */
        OSA_SemaPost(&dspiDmaState->irqSync);
    }
}

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/
