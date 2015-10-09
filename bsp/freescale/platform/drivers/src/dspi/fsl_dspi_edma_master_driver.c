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

#include <string.h>
#include "fsl_dspi_edma_master_driver.h"
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
static dspi_status_t DSPI_DRV_EdmaMasterStartTransfer(uint32_t instance,
                                                      const dspi_edma_device_t * device,
                                                      const uint8_t * sendBuffer,
                                                      uint8_t * receiveBuffer,
                                                      size_t transferByteCount);

static void DSPI_DRV_EdmaMasterCompleteTransfer(uint32_t instance);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterInit
 * Description   : Initializes a DSPI instance for master mode operation to work with EDMA.
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
 * This is an example to set up and call the DSPI_DRV_EdmaMasterInit function by passing
 * in these parameters:
 *   dspi_edma_master_state_t dspiEdmaState; <- the user simply allocates memory for this struct
 *   uint32_t calculatedBaudRate;
 *   dspi_edma_master_user_config_t userConfig; <- the user fills out members for this struct
 *   userConfig.isChipSelectContinuous = false;
 *   userConfig.isSckContinuous = false;
 *   userConfig.pcsPolarity = kDspiPcs_ActiveLow;
 *   userConfig.whichCtar = kDspiCtar0;
 *   userConfig.whichPcs = kDspiPcs0;
 *   DSPI_DRV_EdmaMasterInit(masterInstance, &dspiEdmaState, &userConfig);
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterInit(uint32_t instance,
                                      dspi_edma_master_state_t * dspiEdmaState,
                                      const dspi_edma_master_user_config_t * userConfig,
                                      edma_software_tcd_t * stcdSrc2CmdDataLast)
{
    uint32_t dspiSourceClock;
    SPI_Type *base = g_dspiBase[instance];

    /* Check parameter pointers to make sure there are not NULL */
    if ((dspiEdmaState == NULL) || (userConfig == NULL) || (stcdSrc2CmdDataLast == NULL))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* Check to see if stcdSrc2CmdDataLast is aligned to a 32-byte boundary */
    if ((uint32_t)stcdSrc2CmdDataLast & 0x1FU)
    {
        return kStatus_DSPI_EdmaStcdUnaligned32Error;
    }

    /* Clear the run-time state struct for this instance.*/
    memset(dspiEdmaState, 0, sizeof(* dspiEdmaState));

    /* Note, remember to first enable clocks to the DSPI module before making any register accesses
     * Enable clock for DSPI
     */
    CLOCK_SYS_EnableSpiClock(instance);
    /* Get module clock freq*/
    dspiSourceClock = CLOCK_SYS_GetSpiFreq(instance);

    /* Configure the run-time state struct with the DSPI source clock */
    dspiEdmaState->dspiSourceClock = dspiSourceClock;

    /* Configure the run-time state struct with the data command parameters*/
    dspiEdmaState->whichCtar = userConfig->whichCtar;  /* set the dspiEdmaState struct CTAR*/
    dspiEdmaState->whichPcs = userConfig->whichPcs;  /* set the dspiEdmaState struct whichPcs*/
    dspiEdmaState->isChipSelectContinuous = userConfig->isChipSelectContinuous; /* continuous PCS*/

    /* Initialize the DSPI module registers to default value, which disables the module */
    DSPI_HAL_Init(base);

    /* Init the interrupt sync object.*/
    if (OSA_SemaCreate(&dspiEdmaState->irqSync, 0) != kStatus_OSA_Success)
    {
        return kStatus_DSPI_Error;
    }

    /* Initialize the DSPI module with user config */

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
    g_dspiStatePtr[instance] = dspiEdmaState;

    /* enable the interrupt*/
    INT_SYS_EnableIRQ(g_dspiIrqId[instance]);

    /* DSPI system enable */
    DSPI_HAL_Enable(base);


    /* Request DMA channels from the EDMA peripheral driver.
     * Note, some MCUs have a separate RX and TX DMA request for each DSPI instance, while
     * other MCUs have a separate RX and TX DMA request for DSPI instance 0 only and shared DMA
     * requests for all other instances. Therefore, use the DSPI feature file to distinguish
     * how to request DMA channels between the various MCU DSPI instances.
     * For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
     * trigger ongoing transfers and will link to the TX DMA channel from the RX DMA channel.
     */
    if (instance == 0)
    {
        /* Set up channels for separate RX/TX DMA requests */
        /* This channel transfers data from RX FIFO to receiveBuffer */
        if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                kDmaRequestMux0SPI0Rx,
                                &dspiEdmaState->dmaFifo2Receive) == kEDMAInvalidChannel)
        {
            return kStatus_DSPI_DMAChannelInvalid;
        }

        /* Intermediate command/data to TX FIFO (PUSHR). */
        if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                kDmaRequestMux0SPI0Tx,
                                &dspiEdmaState->dmaCmdData2Fifo) == kEDMAInvalidChannel)
        {
            return kStatus_DSPI_DMAChannelInvalid;
        }
    }

    else if (instance == 1)
    {
#if (FSL_FEATURE_SOC_DSPI_COUNT > 1) /* Continue only if the MCU has another DSPI instance */
        /* Set up channels for separate RX/TX DMA requests */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(1)
        {
            /* This channel transfers data from RX FIFO to receiveBuffer */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0SPI1Rx,
                                    &dspiEdmaState->dmaFifo2Receive) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }

            /* Intermediate command/data to TX FIFO (PUSHR). */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0SPI1Tx,
                                    &dspiEdmaState->dmaCmdData2Fifo) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }
        }
#else /* Set up channels for shared RX/TX DMA request */
        {
            /* This channel transfers data from RX FIFO to receiveBuffer */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0SPI1,
                                    &dspiEdmaState->dmaFifo2Receive) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }

            /* Intermediate command/data to TX FIFO (PUSHR) linked from RX channel.
             * This channel is not activated by dma request, but by channel link from RX.
             */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0Disable,
                                    &dspiEdmaState->dmaCmdData2Fifo) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }
        }
#endif

#else
    return kStatus_DSPI_InvalidInstanceNumber;
#endif
    }

    else
    {
#if (FSL_FEATURE_SOC_DSPI_COUNT > 2) /* Continue only if the MCU has another DSPI instance */
        /* Set up channels for separate RX/TX DMA requests */
#if (FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(2))
        {
            /* This channel transfers data from RX FIFO to receiveBuffer */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0SPI2Rx,
                                    &dspiEdmaState->dmaFifo2Receive) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }

            /* Intermediate command/data to TX FIFO (PUSHR). */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0SPI2Tx,
                                    &dspiEdmaState->dmaCmdData2Fifo) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }
        }
#else /* Set up channels for shared RX/TX DMA request */
        {
            /* This channel transfers data from RX FIFO to receiveBuffer */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0SPI2,
                                    &dspiEdmaState->dmaFifo2Receive) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }

            /* Intermediate command/data to TX FIFO (PUSHR) linked from RX channel.
             * This channel is not activated by dma request, but by channel link from RX.
             */
            if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                    kDmaRequestMux0Disable,
                                    &dspiEdmaState->dmaCmdData2Fifo) == kEDMAInvalidChannel)
            {
                return kStatus_DSPI_DMAChannelInvalid;
            }
        }
#endif

#else
    return kStatus_DSPI_InvalidInstanceNumber;
#endif
    }

    /* Source buffer to intermediate command/data
     * This channel is not activated by dma request, but by channel link.
     */
    if (EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                            kDmaRequestMux0Disable,
                            &dspiEdmaState->dmaSrc2CmdData) == kEDMAInvalidChannel)
    {
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /**************************************************************************************
     * Update run-time state struct with the pointer to Software Transfer Control Descriptor
     **************************************************************************************/
    dspiEdmaState->stcdSrc2CmdDataLast = stcdSrc2CmdDataLast;

    /* Start the transfer process in the hardware */
    DSPI_HAL_StartTransfer(base);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterDeinit
 * Description   : Shuts down a DSPI instance with EDMA support.
 *
 * This function resets the DSPI peripheral, gates its clock, disables any used interrupts to
 * the core, and releases any used DMA channels.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterDeinit(uint32_t instance)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* First stop transfers */
    DSPI_HAL_StopTransfer(base);

    /* Restore the module to defaults then power it down. This also disables the DSPI module.*/
    DSPI_HAL_Init(base);

    /* destroy the interrupt sync object.*/
    OSA_SemaDestroy(&dspiEdmaState->irqSync);

    /* disable the interrupt*/
    INT_SYS_DisableIRQ(g_dspiIrqId[instance]);

    /* Gate the clock for DSPI.*/
    CLOCK_SYS_DisableSpiClock(instance);

    /* Release all of the DMA channels used in the driver. DMA channel structures are stored in
     * the run-time state structure.
     */
    EDMA_DRV_ReleaseChannel(&dspiEdmaState->dmaCmdData2Fifo);
    EDMA_DRV_ReleaseChannel(&dspiEdmaState->dmaSrc2CmdData);
    EDMA_DRV_ReleaseChannel(&dspiEdmaState->dmaFifo2Receive);

    /* Clear state pointer. */
    g_dspiStatePtr[instance] = NULL;

    return kStatus_DSPI_Success;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterSetDelay
 * Description   : Configures the DSPI master mode bus timing delay options with EDMA support.
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
dspi_status_t DSPI_DRV_EdmaMasterSetDelay(uint32_t instance, dspi_delay_type_t whichDelay,
                                          uint32_t delayInNanoSec, uint32_t * calculatedDelay)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];
    dspi_status_t errorCode = kStatus_DSPI_Success;

    *calculatedDelay = DSPI_HAL_CalculateDelay(base, dspiEdmaState->whichCtar, whichDelay,
                                               dspiEdmaState->dspiSourceClock, delayInNanoSec);

    /* If the desired delay exceeds the capability of the device, alert the user */
    if (*calculatedDelay < delayInNanoSec)
    {
        errorCode = kStatus_DSPI_OutOfRange;
    }

    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterConfigureBus
 * Description   : Configures the DSPI port physical parameters to access a device on the bus with
 *                 EDMA support.
 *
 * The term "device" is used to indicate the SPI device for which the DSPI master is communicating.
 * The user has two options to configure the device parameters: either pass in the
 * pointer to the device configuration structure to the desired transfer function (see
 * DSPI_DRV_EdmaMasterTransferBlocking or DSPI_DRV_EdmaMasterTransfer) or pass it in to the
 * DSPI_DRV_EdmaMasterConfigureBus function.  The user can pass in a device structure to the
 * transfer function which contains the parameters for the bus (the transfer function then calls
 * this function). However, the user has the option to call this function directly especially
 * to get the calculated baud rate, at which point they may pass in NULL for the device
 * structure in the transfer function (assuming they have called this configure bus function
 * first). This is an example to set up the dspi_device_t structure to call
 * the DSPI_DRV_EdmaMasterConfigureBus function by passing in these parameters:
 *   dspi_edma_device_t spiDevice;
 *   spiDevice.dataBusConfig.bitsPerFrame = 16;
 *   spiDevice.dataBusConfig.clkPhase = kDspiClockPhase_FirstEdge;
 *   spiDevice.dataBusConfig.clkPolarity = kDspiClockPolarity_ActiveHigh;
 *   spiDevice.dataBusConfig.direction = kDspiMsbFirst;
 *   spiDevice.bitsPerSec = 50000;
 *   DSPI_DRV_EdmaMasterConfigureBus(instance, &spiDevice, &calculatedBaudRate);
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterConfigureBus(uint32_t instance,
                                              const dspi_edma_device_t * device,
                                              uint32_t * calculatedBaudRate)
{
    assert(device);
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    dspi_status_t errorCode = kStatus_DSPI_Success;

    /* Configure the bus to access the provided device.*/
    *calculatedBaudRate = DSPI_HAL_SetBaudRate(base, dspiEdmaState->whichCtar,
                                               device->bitsPerSec, dspiEdmaState->dspiSourceClock);

    errorCode = DSPI_HAL_SetDataFormat(base, dspiEdmaState->whichCtar, &device->dataBusConfig);

    /* Check bits/frame number */
    if (device->dataBusConfig.bitsPerFrame > 16)
    {
        errorCode = kStatus_DSPI_OutOfRange;
    }
    else
    {
        dspiEdmaState->bitsPerFrame = device->dataBusConfig.bitsPerFrame; /* update bits/frame */
    }

    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterTransferBlocking
 * Description   : Performs a blocking SPI master mode transfer with EDMA support.
 *
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus. The function does not return until the transfer is complete.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterTransferBlocking(uint32_t instance,
                                                  const dspi_edma_device_t * device,
                                                  const uint8_t * sendBuffer,
                                                  uint8_t * receiveBuffer,
                                                  size_t transferByteCount,
                                                  uint32_t timeout)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];
    dspi_status_t error = kStatus_DSPI_Success;

    /* If the transfer count is zero, then return immediately.*/
    if (transferByteCount == 0)
    {
        return kStatus_DSPI_InvalidParameter;
    }

    dspiEdmaState->isTransferBlocking = true; /* Indicates this is a blocking transfer */

    /* If using a shared RX/TX DMA request, then this limits the amount of data we can transfer
     * due to the linked channel. The max bytes is 511 if 8-bit/frame or 1022 if 16-bit/frame
     */
    if (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
    {
        if (dspiEdmaState->bitsPerFrame > 8)
        {
            if (transferByteCount > 1022)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
        else
        {
            if (transferByteCount > 511)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
    }

    /* As this is a synchronous transfer, set up the sync status variable*/
    osa_status_t syncStatus;

    if (DSPI_DRV_EdmaMasterStartTransfer(instance, device, sendBuffer, receiveBuffer,
                                         transferByteCount) == kStatus_DSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    /* As this is a synchronous transfer, wait until the transfer is complete.*/
    do
    {
        syncStatus = OSA_SemaWait(&dspiEdmaState->irqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);

    /* If a timeout occurs, stop the transfer by setting the isTransferInProgress to false and
     * disabling DMA requests and interrupts, then return the timeout error status.
     */
    if (syncStatus != kStatus_OSA_Success)
    {
        /* The transfer is complete.*/
        dspiEdmaState->isTransferInProgress = false;

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
 * Function Name : DSPI_DRV_EdmaMasterTransfer
 * Description   : Performs a non-blocking SPI master mode transfer with EDMA support.
 *
 * This function  returns immediately. The user must check back to
 * check whether the transfer is complete (using the DSPI_DRV_EdmaMasterGetTransferStatus function).
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterTransfer(uint32_t instance,
                                          const dspi_edma_device_t * device,
                                          const uint8_t * sendBuffer,
                                          uint8_t * receiveBuffer,
                                          size_t transferByteCount)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];

    /* If the transfer count is zero, then return immediately.*/
    if (transferByteCount == 0)
    {
        return kStatus_DSPI_InvalidParameter;
    }
    
    dspiEdmaState->isTransferBlocking = false; /* Indicates this is not a blocking transfer */
    /* If using a shared RX/TX DMA request, then this limits the amount of data we can transfer
     * due to the linked channel. The max bytes is 511.
     */
    if (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
    {
        if (dspiEdmaState->bitsPerFrame > 8)
        {
            if (transferByteCount > 1022)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
        else
        {
            if (transferByteCount > 511)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
    }

    /* start the transfer process*/
    if (DSPI_DRV_EdmaMasterStartTransfer(instance, device, sendBuffer, receiveBuffer,
                                         transferByteCount) == kStatus_DSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    /* Else, return immediately as this is an async transfer */
    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterGetTransferStatus
 * Description   : Returns whether the previous transfer is finished with EDMA support.
 *
 * When performing an a-sync transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can get the number of words that have been
 * transferred up to now.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterGetTransferStatus(uint32_t instance, uint32_t * framesTransferred)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* Fill in the bytes transferred.*/
    if (framesTransferred)
    {
        *framesTransferred = DSPI_HAL_GetTransferCount(base);
    }

    return (dspiEdmaState->isTransferInProgress ? kStatus_DSPI_Busy : kStatus_DSPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterAbortTransfer
 * Description   : Terminates an asynchronous transfer early with EDMA support.
 *
 * During an async transfer, the user has the option to terminate the transfer early if the transfer
 * is still in progress.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaMasterAbortTransfer(uint32_t instance)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];

    /* Check if a transfer is running.*/
    if (!dspiEdmaState->isTransferInProgress)
    {
        return kStatus_DSPI_NoTransferInProgress;
    }

    /* Stop the running transfer.*/
    DSPI_DRV_EdmaMasterCompleteTransfer(instance);

    return kStatus_DSPI_Success;
}

/*!
 * @brief Initiate (start) a transfer using DMA. This is not a public API as it is called from
 *  other driver functions
 */
static dspi_status_t DSPI_DRV_EdmaMasterStartTransfer(uint32_t instance,
                                                      const dspi_edma_device_t * device,
                                                      const uint8_t * sendBuffer,
                                                      uint8_t * receiveBuffer,
                                                      size_t transferByteCount)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    uint32_t calculatedBaudRate;
    dspi_command_config_t command;  /* create an instance of the data command struct*/
    SPI_Type *base = g_dspiBase[instance];
    uint32_t txTransferByteCnt = 0;
    uint32_t rxTransferByteCnt = 0;
    edma_software_tcd_t   stcd;
    edma_transfer_config_t edmaConfig;

    /* Initialize s_wordToSend */
    s_wordToSend = 0;

    /* Check that we're not busy.*/
    if (dspiEdmaState->isTransferInProgress)
    {
        return kStatus_DSPI_Busy;
    }

    /* Configure bus for this device. If NULL is passed, we assume the caller has
     * preconfigured the bus using DSPI_DRV_EdmaMasterConfigureBus().
     * Do nothing for calculatedBaudRate. If the user wants to know the calculatedBaudRate
     * then they can call this function separately.
     */
    if (device)
    {
        DSPI_DRV_EdmaMasterConfigureBus(instance, device, &calculatedBaudRate);
        dspiEdmaState->bitsPerFrame = device->dataBusConfig.bitsPerFrame; /*update bits/frame*/
    }

    /* Check the transfer byte count. If bits/frame > 8, meaning 2 bytes, and if
     * the transfer byte count is an odd count we'll have to increase the TX transfer byte count
     * by one and assert a flag to indicate to the send functions that it will
     * need to handle an extra byte.
     * For receive, we actually round down the transfer count to the next lowest even number.
     * Then in the interrupt handler, we take care of geting this last byte.
     */
    if ((dspiEdmaState->bitsPerFrame > 8) && (transferByteCount & 1UL))
    {
        dspiEdmaState->extraByte = true;
        txTransferByteCnt = transferByteCount + 1U;  /* Increment to next even byte count */
        rxTransferByteCnt = transferByteCount & ~1U;  /* Decrement to next even byte count */
    }
    else
    {
        dspiEdmaState->extraByte = false;
        txTransferByteCnt = transferByteCount;
        rxTransferByteCnt = transferByteCount;
    }
    /* Store the receiveBuffer pointer and receive byte count to the run-time state struct
     * for later use in the interrupt handler.
     */
    dspiEdmaState->rxBuffer = (uint8_t *)receiveBuffer;
    dspiEdmaState->rxTransferByteCnt = rxTransferByteCnt;

    /* Save information about the transfer for use by the ISR.*/
    dspiEdmaState->isTransferInProgress = true;

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

    /* Enable the End Of Queue interrupt, which will set when DSPI sees EOQ bit set in the
     * last data word being sent. The ISR should clear this flag.
     */
    DSPI_HAL_SetIntMode(base, kDspiEndOfQueue, true);

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
        /* Clear structure config */
        memset(&edmaConfig, 0, sizeof(edma_transfer_config_t));
        memset(&stcd, 0, sizeof(edma_software_tcd_t));

        /* Source addr, RX FIFO */
        edmaConfig.srcAddr = DSPI_HAL_GetPoprRegAddr(base);

        /* Source addr offset is 0 as source addr never increments */
        edmaConfig.srcOffset = 0;

        /* The source and destination attributes (bit size) depends on bits/frame setting */
        if (dspiEdmaState->bitsPerFrame <= 8)
        {
            /* Source size is one byte, destination size is one byte */
            edmaConfig.srcTransferSize = kEDMATransferSize_1Bytes;
            edmaConfig.destTransferSize = kEDMATransferSize_1Bytes;

            /* Transfer 1 byte from RX FIFO to receive buffer */
            edmaConfig.minorLoopCount   = 1;

            /* Set MAJOR count to remaining receive byte count. Configure both the
             * CITER and BITER fields. */
            edmaConfig.majorLoopCount   = rxTransferByteCnt;
        }
        else /* For 16-bit words, but the receive buffer is still an 8-bit buffer */
        {
            /* Source size is 2 byte, destination size is one byte */
            edmaConfig.srcTransferSize = kEDMATransferSize_2Bytes;
            edmaConfig.destTransferSize = kEDMATransferSize_1Bytes;

            /* Transfer 2 bytes from RX FIFO to receive buffer */
            edmaConfig.minorLoopCount   = 2;

            /* Set MAJOR count to remaining receive byte count. Configure both the
             * CITER and BITER fields.  Divide by 2 to account for minor loop of 2 bytes
             */
            edmaConfig.majorLoopCount   = rxTransferByteCnt/2;
        }

        /* Don't increment source address, it is constant */
        edmaConfig.srcLastAddrAdjust = 0;

        /* Disable source/destination modulo */
        edmaConfig.srcModulo = kEDMAModuloDisable;
        edmaConfig.destModulo = kEDMAModuloDisable;

        /* If no receive buffer then disable incrementing the destination and set the destination
         * to a temporary location. Always handle rx operations to avoid rx overrun.
         */
        if (!receiveBuffer)
        {
            /* Destination is the "throw away" receive buffer */
            edmaConfig.destAddr   = (uint32_t)(&s_rxBuffIfNull);

            /* Dest addr offset, do not increment to the next byte */
            edmaConfig.destOffset = 0;
        }
        else /* Receive buffer is used */
        {
            /* Destination is the receive buffer */
            edmaConfig.destAddr   = (uint32_t)(receiveBuffer);
            /* Dest addr offset, increment to the next byte */
            edmaConfig.destOffset = 1;
        }

        /* No adjustment needed for destination addr */
        edmaConfig.destLastAddrAdjust = 0;

        /* Sets the descriptor basic transfer for the descriptor. */
        EDMA_DRV_PrepareDescriptorTransfer(&dspiEdmaState->dmaFifo2Receive, &stcd, &edmaConfig, false, true);

        /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
         * trigger ongoing transfers and will link to the TX DMA channel from the RX DMA channel.
         */
        if (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
        {
            /* Enable channel linking to TX channel (at the end of each minor loop) */
            EDMA_DRV_PrepareDescriptorMinorLink(&stcd,
                                    VIRTUAL_CHN_TO_EDMA_CHN(dspiEdmaState->dmaCmdData2Fifo.channel));
            /* Enable MAJOR link and link to TX DMA channel. This is needed to perform one more
             * channel link when the major loop is exhausted.
             */
            EDMA_DRV_PrepareDescriptorChannelLink(&stcd,
                                    VIRTUAL_CHN_TO_EDMA_CHN(dspiEdmaState->dmaCmdData2Fifo.channel));
        }

        /* Push the contents of the SW TCD to the HW TCD registers */
        EDMA_DRV_PushDescriptorToReg(&dspiEdmaState->dmaFifo2Receive, &stcd);

        /* Now that TCD was set up, enable the DSPI Peripheral Hardware request for the RX FIFO */
        EDMA_DRV_StartChannel(&dspiEdmaState->dmaFifo2Receive);

        /* Enable the Receive FIFO Drain Request as a DMA request */
        DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, true);
    }

    /************************************************************************************
     * Set up the Last Command/data Word Intermediate Buffer and fill up the TX FIFO.
     ***********************************************************************************/
    /* Before sending the data, we first need to initialize the data command struct
     * Configure the data command attributes for the desired PCS, CTAR, and continuous PCS
     * which are derived from the run-time state struct
     */
    command.whichPcs = dspiEdmaState->whichPcs;
    command.whichCtar = dspiEdmaState->whichCtar;
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
        if (dspiEdmaState->bitsPerFrame <= 8)
        {
            lastWord = sendBuffer[txTransferByteCnt-1]; /* Last byte */
        }
        /* Store the last two bytes the send buffer */
        else
        {
            /* If 16-bit transfers and odd transfer byte count then an extra byte was added
             * to the transfer byte count, but we cannot access more of the send buffer
             */
            if(!dspiEdmaState->extraByte)
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
    command.isChipSelectContinuous = dspiEdmaState->isChipSelectContinuous;
    command.isEndOfQueue = 0; /* Clear End of Queue (previously set for last cmd/data word)*/
    s_cmdData = DSPI_HAL_GetFormattedCommand(base, &command);

    /* Place the next data from the send buffer into the intermediate buffer (preload it)
     * based on whether it is one byte or two.
     */
    if (dspiEdmaState->bitsPerFrame <= 8)
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

    /************************************************************************************
     * Transfer Control Descriptor set up for Intermediate command/data to TX
     * FIFO (PUSHR). AKA "Channel 1"
     * Note, actual channel number may very depending on DMA system usage.
     * This channels links to "Channel 1" on completion of MAJOR loop.  "Channel 1" is
     * the channel that transfers data from the send source buffer to the intermediate
     * command/data buffer.
     * Note that the channel linking is based on the MAJOR loop complete and not on minor
     * loop.  This is because we are only sending one 32-bit word so when the minor loop
     * completes, the MAJOR loop also completes.  The eDMA does not channel link on the
     * last iteration of the MAJOR loop using the ELINK mechanism, hence we have to link
     * on the MAJOR loop completion using MAJORLINK channel linking.
     ************************************************************************************/
    /* For each transfer control descriptor set up, save off DMA instance and channel number
     * to simplified variable names to make code cleaner
     */

    /* Implement the following DMA channel set up only if we still have data yet to send
     * Otherwise, bypass this and enable the DSPI Transmit DMA request.
     */
    if (txTransferByteCnt != 0)
    {
        /************************************************************************************
         * Scatter/gather STCD set up
         * STCD ONLY for Last intermediate command/data to PUSHR. Do not call
         * edma_hal_stcd_push_to_htcd as this is used for "Channel 2" scatter/gather.
         * Hence we will call this "Channel 2 prime". This needs to be defined before
         * setting up "Channel 2" as it needs the address for this STCD.
         *
         * IMPORTANT: Per eDMA spec, the pointer address for this STCD structure needs to be
         *            aligned on 32-byte boundaries.
         ************************************************************************************/
        /* This channel should use scatter gather method, first configure the last STCD */
        memset(&edmaConfig, 0, sizeof(edma_transfer_config_t));
        memset(dspiEdmaState->stcdSrc2CmdDataLast, 0, sizeof(edma_software_tcd_t));

        /* Fill out members of the EDMA transfer edmaConfig structure and then use this structure to
         * prepare the software transfer control descriptor stcdSrc2CmdDataLast
         */
        edmaConfig.srcAddr = (uint32_t)(&s_lastCmdData); /* Source addr is last data + last command */
        edmaConfig.srcOffset = 0;
        edmaConfig.srcTransferSize = kEDMATransferSize_4Bytes;
        edmaConfig.destTransferSize = kEDMATransferSize_4Bytes;
        edmaConfig.destAddr = (uint32_t)(&s_cmdData); /* Destination is the command/data buffer */
        edmaConfig.destOffset = 0;
        edmaConfig.destLastAddrAdjust = 0;
        edmaConfig.srcLastAddrAdjust = 0;
        edmaConfig.destModulo = kEDMAModuloDisable;
        edmaConfig.srcModulo = kEDMAModuloDisable;
        edmaConfig.majorLoopCount = 1; /* We are only sending one 32-bit word, so MAJOR count is "1" */
        edmaConfig.minorLoopCount = 4; /* Transfer 4 bytes or one word */

        /* Sets the descriptor basic transfer for the descriptor. */
        EDMA_DRV_PrepareDescriptorTransfer(&dspiEdmaState->dmaSrc2CmdData,
                dspiEdmaState->stcdSrc2CmdDataLast, &edmaConfig,false,true);

        /* If at this point we are left with only sending one more data byte/word, then this
         * is the last command/data to send.  So the transfer control descriptor should move the
         * last command/data word into the intermediate buffer and this will get transferred to the
         * DSPI when the FIFO is ready for this.
         */
        if (((dspiEdmaState->bitsPerFrame <= 8) && ((txTransferByteCnt-1) == 0)) ||
            ((dspiEdmaState->bitsPerFrame > 8) && ((txTransferByteCnt-2) == 0)))
        {
            /* Push the contents of the SW TCD to the HW TCD registers */
            EDMA_DRV_PushDescriptorToReg(&dspiEdmaState->dmaSrc2CmdData,
                                         dspiEdmaState->stcdSrc2CmdDataLast);
        }
        /* Otherwise, we are left with more data to send, so use the transfer control
         * descriptor that will move data from the send source buffer to the intermediate
         * command/data buffer.
         */
        else
        {
            /* Clear structure config */
            memset(&edmaConfig, 0, sizeof(edma_transfer_config_t));
            memset(&stcd, 0, sizeof(edma_software_tcd_t));

            /************************************************************************************
             * Transfer Control Descriptor set up for Source buffer to intermediate
             * command/data (this is a linked channel). AKA "Channel 2"
             * Note, actual channel number may very depending on DMA system usage
             * This channel is triggered by the completion of "Channel 1". It transfers data from
             * the send source buffer to the intermediate command/data word. When the source
             * buffer transfers the word before the last data word, the MAJOR loop completes
             * and triggers the scatter/gather (ESG = 1) and loads the STCD that is set up to
             * transfer the last command/data word to the PUSHR.
             ************************************************************************************/
            /* If a send buffer was provided, the word comes from there. Otherwise we set
             * the source address to point to the s_wordToSend variable that was set to 0.
             */
            if (sendBuffer)
            {
                /* Source addr is the "send" data buffer */
                edmaConfig.srcAddr = (uint32_t)(sendBuffer);

                /* Increment the source address by one byte after every transfer */
                edmaConfig.srcOffset = 1;
            }
            else
            {
                /* Source addr is the "send" data buffer */
                edmaConfig.srcAddr = (uint32_t)(&s_wordToSend);

                /* Don't increment the source address  */
                edmaConfig.srcOffset = 0;
            }

            if (dspiEdmaState->bitsPerFrame <= 8)
            {
                /* Source and destination size: byte */
                edmaConfig.srcModulo = kEDMAModuloDisable;
                edmaConfig.destModulo = kEDMAModuloDisable;
                edmaConfig.srcTransferSize = kEDMATransferSize_1Bytes;
                edmaConfig.destTransferSize = kEDMATransferSize_1Bytes;

                /* minor byte transfer: 1 byte (8-bit word) */
                edmaConfig.minorLoopCount = 1;

                /* Major loop count is equal to remaining number of bytes to send minus 1.
                 * That is because the last data byte/word is written to the last command/data
                 * intermediate buffer.
                 */
                edmaConfig.majorLoopCount = txTransferByteCnt-1;
            }
            else
            {
                /* Source size: byte and destination size: halfword */
                edmaConfig.srcModulo = kEDMAModuloDisable;
                edmaConfig.destModulo = kEDMAModuloDisable;
                edmaConfig.srcTransferSize = kEDMATransferSize_1Bytes;
                edmaConfig.destTransferSize = kEDMATransferSize_2Bytes;

                /* minor byte transfer: 2 bytes (16-bit word) */
                edmaConfig.minorLoopCount = 2;

                /* Major loop count is equal to remaining number of 16-bit words to send
                 * hence need to convert remainingSendByteCount from byte to 16-bit word
                 */
                edmaConfig.majorLoopCount = (uint16_t)(txTransferByteCnt-2)/2;
            }
            /* Set SLAST to 0 */
            edmaConfig.srcLastAddrAdjust = 0;

            /* Destination addr is the intermediate command/data buffer */
            edmaConfig.destAddr = (uint32_t)(&s_cmdData);

            /* No dest addr offset, since we never increment the dest addr */
            edmaConfig.destOffset = 0;

            /* Sets the descriptor basic transfer for the descriptor. */
            EDMA_DRV_PrepareDescriptorTransfer(&dspiEdmaState->dmaSrc2CmdData, &stcd, &edmaConfig, false, false);

            /* Place the address of the scatter/gather in order to reload STCD for the final
             * last command/data word to be loaded to the intermediate buffer.
             * IMPORTANT: This address needs to be 32-byte aligned.
             */
            EDMA_DRV_PrepareDescriptorScatterGather(&stcd,
                                    (edma_software_tcd_t *)(dspiEdmaState->stcdSrc2CmdDataLast));

            /* Push the contents of the SW TCD to the HW TCD registers */
            EDMA_DRV_PushDescriptorToReg(&dspiEdmaState->dmaSrc2CmdData, &stcd);
        }
    }

    /* Clear structure config */
    memset(&edmaConfig, 0, sizeof(edma_transfer_config_t));
    memset(&stcd, 0, sizeof(edma_software_tcd_t));

    /* Source addr offset is 0 as source addr never increments */
    edmaConfig.srcOffset = 0;

    /* source size 32-bits */
    /* destination size 32bits*/
    /* Clear the SMOD and DMOD fields */
    edmaConfig.srcModulo = kEDMAModuloDisable;
    edmaConfig.destModulo = kEDMAModuloDisable;
    edmaConfig.srcTransferSize = kEDMATransferSize_4Bytes;
    edmaConfig.destTransferSize = kEDMATransferSize_4Bytes;

    /* Transfer 4 bytes or one word */
    edmaConfig.minorLoopCount = 4;

    /* Don't increment source/destination address, it is constant */
    edmaConfig.srcLastAddrAdjust = 0;
    edmaConfig.destLastAddrAdjust = 0;

    /* Destination is SPI PUSHR TX FIFO */
    edmaConfig.destAddr = DSPI_HAL_GetMasterPushrRegAddr(base);

    edmaConfig.majorLoopCount = 1;

    /* No dest addr offset, since we never increment the dest addr */
    edmaConfig.destOffset = 0;

    /* If txTransferByteCnt is 0, then send last command/data since this is the
     * last data word to send
     */
    if (txTransferByteCnt == 0)
    {
        /* Source address is the last command/data intermediate buffer */
        edmaConfig.srcAddr = (uint32_t)(&s_lastCmdData);

        /* Sets the descriptor basic transfer for the descriptor. */
        EDMA_DRV_PrepareDescriptorTransfer(&dspiEdmaState->dmaCmdData2Fifo, &stcd, &edmaConfig, false, true);
    }
    /* Else, send the intermediate buffer  */
    else
    {
        /* Source addr, intermediate command/data*/
        edmaConfig.srcAddr = (uint32_t)(&s_cmdData);

        /* Sets the descriptor basic transfer for the descriptor. */
        EDMA_DRV_PrepareDescriptorTransfer(&dspiEdmaState->dmaCmdData2Fifo, &stcd, &edmaConfig, false, false);

        /* Set the MAJOR link channel to link to the next channel that will pull data from
         * the source buffer into the intermediate command/data buffer and enable MAJOR link
         */
        EDMA_DRV_PrepareDescriptorChannelLink(&stcd,
                        VIRTUAL_CHN_TO_EDMA_CHN(dspiEdmaState->dmaSrc2CmdData.channel));
    }
    /* Push the contents of the SW TCD to the HW TCD registers */
    EDMA_DRV_PushDescriptorToReg(&dspiEdmaState->dmaCmdData2Fifo, &stcd);

    /* For DSPI instances with separate RX/TX DMA requests, we'll use the TX DMA request to
     * trigger the TX DMA channel hence we'll enable the TX channel DMA request.
     */
    if (FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
    {
        /* Now that the TCD was set up for each channel, enable the DSPI peripheral hardware request
         * for the first TX DMA channel.
         */
        EDMA_DRV_StartChannel(&dspiEdmaState->dmaCmdData2Fifo);

        /* Enable TFFF request in the DSPI module */
        DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, true);
    }
    /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
     * trigger ongoing transfers that will link to the TX DMA channel from the RX DMA channel.
     * So, we'll disable the TX channel DMA request and then we'll have to manually start the
     * TX DMA channel to get the tranfer process started, where the RX DMA channel will take care
     * of the ongoing transfers from there.
     */
    else /* For shared RX/TX DMA requests */
    {
        /* Disable the DSPI TX peripheral hardware request*/
        EDMA_DRV_StopChannel(&dspiEdmaState->dmaCmdData2Fifo);

        /* Disable TFFF request in the DSPI module */
        DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);

        /* Manually start the TX DMA channel to get the process going */
        EDMA_DRV_TriggerChannelStart(&dspiEdmaState->dmaCmdData2Fifo);
    }

    return kStatus_DSPI_Success;
}

/*!
 * @brief Finish up a transfer.
 * Cleans up after a transfer is complete. Interrupts are disabled, and the DSPI module
 * is disabled. This is not a public API as it is called from other driver functions.
 */
static void DSPI_DRV_EdmaMasterCompleteTransfer(uint32_t instance)
{
    /* instantiate local variable of type dspi_edma_master_state_t and point to global state */
    dspi_edma_master_state_t * dspiEdmaState = (dspi_edma_master_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* If an odd transfer count was provided when bits/frame > 8, then there will be an extra byte
     * received. Get this byte now and put it into the receive buffer if a receive buffer was
     * provided.
     */
    if ((dspiEdmaState->extraByte) && (dspiEdmaState->rxBuffer))
    {
        /* copy the final byte from the DSPI data register to the receive buffer */
        dspiEdmaState->rxBuffer[dspiEdmaState->rxTransferByteCnt] = DSPI_HAL_ReadData(base);
    }

    /* The transfer is complete.*/
    dspiEdmaState->isTransferInProgress = false;

    /* Disable the Receive FIFO Drain DMA Request */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, false);

    /* Disable TFFF DMA request */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);

    /* Disable End of Queue request */
    DSPI_HAL_SetIntMode(base, kDspiEndOfQueue, false);

    if (dspiEdmaState->isTransferBlocking)
    {
        /* Signal the synchronous completion object */
        OSA_SemaPost(&dspiEdmaState->irqSync);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaMasterIRQHandler
 * Description   : Interrupt handler for DSPI master mode.
 * This handler uses the buffers stored in the dspi_master_state_t structs to transfer data.
 *
 *END**************************************************************************/
void DSPI_DRV_EdmaMasterIRQHandler(uint32_t instance)
{
    SPI_Type *base = g_dspiBase[instance];

    /* If the interrupt is due to an end-of-queue, then complete. This interrupt is
     * is used during DMA operations and we want to handle this interrupt only
     * when DMA is being used.
     */
    if (DSPI_HAL_GetStatusFlag(base, kDspiEndOfQueue))
    {
        /* Complete the transfer. This disables the interrupts, so we don't wind up in
         * the ISR again.
         */
        DSPI_DRV_EdmaMasterCompleteTransfer(instance);
    }
}

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

