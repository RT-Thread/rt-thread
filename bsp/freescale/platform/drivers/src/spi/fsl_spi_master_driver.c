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

#include <stdlib.h>
#include <string.h>
#include "fsl_spi_master_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_SPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Pointer to runtime state structure.*/
extern void * g_spiStatePtr[SPI_INSTANCE_COUNT];

/* Table of SPI FIFO sizes per instance. */
extern const uint32_t g_spiFifoSize[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static spi_status_t SPI_DRV_MasterStartTransfer(uint32_t instance,
                                                const spi_master_user_config_t * device);
static void SPI_DRV_MasterCompleteTransfer(uint32_t instance);
#if FSL_FEATURE_SPI_FIFO_SIZE
static void SPI_DRV_MasterFillupTxFifo(uint32_t instance);
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterInit
 * Description   : Initialize a SPI instance for master mode operation.
 * This function uses a CPU interrupt driven method for transferring data.
 * This function initializes the run-time state structure to track the ongoing
 * transfers, ungates the clock to the SPI module, resets and initializes the module
 * to default settings, configures the IRQ state structure, enables
 * the module-level interrupt to the core, and enables the SPI module.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_MasterInit(uint32_t instance, spi_master_state_t * spiState)
{
    SPI_Type *base = g_spiBase[instance];

    /* Clear the state for this instance.*/
    memset(spiState, 0, sizeof(* spiState));

    /* Enable clock for SPI*/
    CLOCK_SYS_EnableSpiClock(instance);

    /* configure the run-time state struct with the source clock value */
    spiState->spiSourceClock = CLOCK_SYS_GetSpiFreq(instance);

    /* Reset the SPI module to it's default state, which includes SPI disabled */
    SPI_HAL_Init(base);

    /* Init the interrupt sync object.*/
    if (OSA_SemaCreate(&spiState->irqSync, 0) != kStatus_OSA_Success)
    {
        return kStatus_SPI_Error;
    }

    /* Set SPI to master mode */
    SPI_HAL_SetMasterSlave(base, kSpiMaster);

    /* Set slave select to automatic output mode */
    SPI_HAL_SetSlaveSelectOutputMode(base, kSpiSlaveSelect_AutomaticOutput);

    /* Set the SPI pin mode to normal mode */
    SPI_HAL_SetPinMode(base, kSpiPinMode_Normal);

#if FSL_FEATURE_SPI_FIFO_SIZE
    if (g_spiFifoSize[instance] != 0)
    {
        /* If SPI module contains a FIFO, enable it and set watermarks to half full/empty */
        SPI_HAL_SetFifoMode(base, true, kSpiTxFifoOneHalfEmpty, kSpiRxFifoOneHalfFull);
    }
#endif
    /* Save runtime structure pointers to irq handler can point to the correct state structure*/
    g_spiStatePtr[instance] = spiState;

    /* Enable SPI interrupt.*/
    INT_SYS_EnableIRQ(g_spiIrqId[instance]);

    /* SPI system Enable*/
    SPI_HAL_Enable(base);

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterDeinit
 * Description   : Shutdown a SPI instance.
 * This function resets the SPI peripheral, gates its clock, and disables the interrupt to
 * the core.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_MasterDeinit(uint32_t instance)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];

    /* Restore the module to defaults which includes disabling the SPI then power it down.*/
    SPI_HAL_Init(base);

    /* destroy the interrupt sync object.*/
    OSA_SemaDestroy(&spiState->irqSync);

    /* Disable SPI interrupt.*/
    INT_SYS_DisableIRQ(g_spiIrqId[instance]);

    /* Gate the clock for SPI.*/
    CLOCK_SYS_DisableSpiClock(instance);

    /* Clear state pointer. */
    g_spiStatePtr[instance] = NULL;

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterConfigureBus
 * Description   : Configures the SPI port to access a device on the bus.
 * The term "device" is used to indicate the SPI device for which the SPI master is communicating.
 * The user has two options to configure the device parameters: either pass in the
 * pointer to the device configuration structure to the desired transfer function (see
 * SPI_DRV_MasterTransferDataBlocking or SPI_DRV_MasterTransferData) or pass it in to the
 * SPI_DRV_MasterConfigureBus function.  The user can pass in a device structure to the transfer
 * function which contains the parameters for the bus (the transfer function will then call
 * this function). However, the user has the option to call this function directly especially
 * to get the calculated baud rate, at which point they may pass in NULL for the device
 * struct in the transfer function (assuming they have called this configure bus function
 * first).
 *
 *END**************************************************************************/
void SPI_DRV_MasterConfigureBus(uint32_t instance,
                                const spi_master_user_config_t * device,
                                uint32_t * calculatedBaudRate)
{
    assert(device);

    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];

    /* Configure the bus to access the provided device.*/
    *calculatedBaudRate = SPI_HAL_SetBaud(base, device->bitsPerSec, spiState->spiSourceClock);
    SPI_HAL_SetDataFormat(base, device->polarity, device->phase, device->direction);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    SPI_HAL_Set8or16BitMode(base, device->bitCount);
#endif

}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterTransferBlocking
 * Description   : Performs a blocking SPI master mode transfer.
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus. The function will not return until the transfer is complete.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_MasterTransferBlocking(uint32_t instance,
                                            const spi_master_user_config_t * device,
                                            const uint8_t * sendBuffer,
                                            uint8_t * receiveBuffer,
                                            size_t transferByteCount,
                                            uint32_t timeout)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];
    spi_status_t errorStatus = kStatus_SPI_Success;
    SPI_Type *base = g_spiBase[instance];

    /* fill in members of the run-time state struct*/
    spiState->isTransferBlocking = true; /* Indicates this is a blocking transfer */
    spiState->sendBuffer = (const uint8_t *)sendBuffer;
    spiState->receiveBuffer = (uint8_t *)receiveBuffer;
    spiState->remainingSendByteCount = transferByteCount;
    spiState->remainingReceiveByteCount = transferByteCount;

    /* start the transfer process*/
    errorStatus = SPI_DRV_MasterStartTransfer(instance, device);
    if (errorStatus != kStatus_SPI_Success)
    {
        return errorStatus;
    }

    /* As this is a synchronous transfer, wait until the transfer is complete.*/
    osa_status_t syncStatus;

    do
    {
        syncStatus = OSA_SemaWait(&spiState->irqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);

    /* If a timeout occurs, stop the transfer by setting the isTransferInProgress to false and
     * disabling interrupts, then return the timeout error status.
     */
    if (syncStatus != kStatus_OSA_Success)
    {
        /* The transfer is complete.*/
        spiState->isTransferInProgress = false;

        /* Disable interrupts */
        SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, false);
        SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, false);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
        if (g_spiFifoSize[instance] != 0)
        {
            /* Now disable the SPI FIFO interrupts */
            SPI_HAL_SetFifoIntCmd(base, kSpiTxFifoNearEmptyInt, false);
            SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, false);
        }
#endif
        errorStatus = kStatus_SPI_Timeout;
    }

    return errorStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterTransfer
 * Description   : Perform a non-blocking SPI master mode transfer.
 * This function will return immediately. It is the user's responsiblity to check back to
 * ascertain if the transfer is complete (using the SPI_DRV_MasterGetTransferStatus function).
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus. The function will not return until the transfer is complete.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_MasterTransfer(uint32_t instance,
                                    const spi_master_user_config_t * device,
                                    const uint8_t * sendBuffer,
                                    uint8_t * receiveBuffer,
                                    size_t transferByteCount)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];
    spi_status_t errorStatus = kStatus_SPI_Success;

    /* fill in members of the run-time state struct*/
    spiState->isTransferBlocking = false; /* Indicates this is a non-blocking transfer */
    spiState->sendBuffer = sendBuffer;
    spiState->receiveBuffer = (uint8_t *)receiveBuffer;
    spiState->remainingSendByteCount = transferByteCount;
    spiState->remainingReceiveByteCount = transferByteCount;

    /* start the transfer process*/
    errorStatus = SPI_DRV_MasterStartTransfer(instance, device);
    if (errorStatus != kStatus_SPI_Success)
    {
        return errorStatus;
    }

    /* Else, return immediately as this is an async transfer */
    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterGetTransferStatus
 * Description   : Returns whether the previous transfer finished.
 * When performing an a-sync transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can get the number of words that have been
 * transferred up to now.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_MasterGetTransferStatus(uint32_t instance,
                                             uint32_t * bytesTransferred)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];

    /* Fill in the bytes transferred.*/
    if (bytesTransferred)
    {
        *bytesTransferred = spiState->transferredByteCount;
    }

    return (spiState->isTransferInProgress ? kStatus_SPI_Busy : kStatus_SPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterAbortTransfer
 * Description   : Terminates an asynchronous transfer early.
 * During an async transfer, the user has the option to terminate the transfer early if the transfer
 * is still in progress.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_MasterAbortTransfer(uint32_t instance)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];

    /* Check if a transfer is running.*/
    if (!spiState->isTransferInProgress)
    {
        return kStatus_SPI_NoTransferInProgress;
    }

    /* Stop the running transfer.*/
    SPI_DRV_MasterCompleteTransfer(instance);

    return kStatus_SPI_Success;
}

/*!
 * @brief Initiate (start) a transfer. This is not a public API as it is called from other
 *  driver functions
 */
static spi_status_t SPI_DRV_MasterStartTransfer(uint32_t instance,
                                                const spi_master_user_config_t * device)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];

    uint32_t calculatedBaudRate;
    SPI_Type *base = g_spiBase[instance];

    /* Check that we're not busy.*/
    if (spiState->isTransferInProgress)
    {
        return kStatus_SPI_Busy;
    }

    /* Configure bus for this device. If NULL is passed, we assume the caller has
     * preconfigured the bus using SPI_DRV_MasterConfigureBus().
     * Do nothing for calculatedBaudRate. If the user wants to know the calculatedBaudRate
     * then they can call this function separately.
     */
    if (device)
    {
        SPI_DRV_MasterConfigureBus(instance, device, &calculatedBaudRate);
    }

    /* In order to flush any remaining data in the shift register, disable then enable the SPI */
    SPI_HAL_Disable(base);
    SPI_HAL_Enable(base);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    spi_data_bitcount_mode_t bitCount;

    bitCount = SPI_HAL_Get8or16BitMode(base);

    /* Check the transfer byte count. If bits/frame > 8, meaning 2 bytes if bits/frame > 8, and if
     * the transfer byte count is an odd count we'll have to increase the transfer byte count
     * by one and assert a flag to indicate to the receive function that it will need to handle
     * an extra byte so that it does not inadverently over-write an another byte to the receive
     * buffer. For sending the extra byte, we don't care if we read past the send buffer since we
     * are only reading from it and the absolute last byte (that completes the final 16-bit word)
     * is a don't care byte anyway.
     */
    if ((bitCount == kSpi16BitMode) && (spiState->remainingSendByteCount & 1UL))
    {
        spiState->remainingSendByteCount += 1;
        spiState->remainingReceiveByteCount += 1;
        spiState->extraByte = true;
    }
    else
    {
        spiState->extraByte = false;
    }

#endif

    /* If the byte count is zero, then return immediately.*/
    if (spiState->remainingSendByteCount == 0)
    {
        SPI_DRV_MasterCompleteTransfer(instance);
        return kStatus_SPI_Success;
    }

    /* Save information about the transfer for use by the ISR.*/
    spiState->isTransferInProgress = true;
    spiState->transferredByteCount = 0;

    /* Make sure TX data register (or FIFO) is empty. If not, return appropriate
     * error status. This also causes a read of the status
     * register which is required before writing to the data register below.
     */
    if (SPI_HAL_IsTxBuffEmptyPending(base) != 1)
    {
        return kStatus_SPI_TxBufferNotEmpty;
    }


#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* If the module/instance contains a FIFO (and if enabled), proceed with FIFO usage for either
     *  8- or 16-bit transfers, else bypass to non-FIFO usage.
     */
    if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
    {
        /* First fill the FIFO with data */
        SPI_DRV_MasterFillupTxFifo(instance);

        /* If the remaining RX byte count is less than the RX FIFO watermark, enable
         * the TX FIFO empty interrupt. Once the TX FIFO is empty, we are ensured
         * that the transmission is complete and can then drain the RX FIFO.
         * Else, enable the RX FIFO interrupt based on the watermark. In the IRQ
         * handler, another check will be made to see if the remaining RX byte count
         * is less than the RX FIFO watermark.
         */
        if (spiState->remainingReceiveByteCount < g_spiFifoSize[instance])
        {
            SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, true); /* TX FIFO empty interrupt */
        }
        else
        {
            SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, true);
        }
    }
    /* Modules that support 16-bit transfers but without FIFO support */
    else
    {
        uint8_t byteToSend = 0;

        /* SPI configured for 16-bit transfers, no FIFO */
        if (bitCount == kSpi16BitMode)
        {
            uint8_t byteToSendLow = 0;
            uint8_t byteToSendHigh = 0;

            if (spiState->sendBuffer)
            {
                byteToSendLow = *(spiState->sendBuffer);
                ++spiState->sendBuffer;

                /* If the extraByte flag is set and these are the last 2 bytes, then skip this */
                if (!((spiState->extraByte) && (spiState->remainingSendByteCount == 2)))
                {
                    byteToSendHigh = *(spiState->sendBuffer);
                    ++spiState->sendBuffer;
                }
            }
            SPI_HAL_WriteDataLow(base, byteToSendLow);
            SPI_HAL_WriteDataHigh(base, byteToSendHigh);

            spiState->remainingSendByteCount -= 2;  /* decrement by 2 */
            spiState->transferredByteCount += 2;  /* increment by 2 */
        }
        /* SPI configured for 8-bit transfers, no FIFO */
        else
        {
            if (spiState->sendBuffer)
            {
                byteToSend = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteDataLow(base, byteToSend);

            --spiState->remainingSendByteCount;
            ++spiState->transferredByteCount;
        }

        /* Only enable the receive interrupt.  This should be ok since SPI is a synchronous
         * protocol, so every RX interrupt we get, we should be ready to send. However, since
         * the SPI has a shift register and data buffer (for transmit and receive), things may not
         * be cycle-to-cycle synchronous. To compensate for this, enabling the RX interrupt only
         * ensures that we do indeed receive data before sending out the next data word. In the
         * ISR we make sure to first check for the RX data buffer full before checking the TX
         * data register empty flag.
         */
        SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, true);
    }

#else /* For SPI modules that do not support 16-bit transfers */

    /* Start the transfer by writing the first byte. If a send buffer was provided, the byte
     * comes from there. Otherwise we just send a zero byte. Note that before writing to the
     * data register, the status register must first be read, which was already performed above.
     */
    uint8_t byteToSend = 0;
    if (spiState->sendBuffer)
    {
        byteToSend = *(spiState->sendBuffer);
        ++spiState->sendBuffer;
    }
    SPI_HAL_WriteData(base, byteToSend);

    --spiState->remainingSendByteCount;
    ++spiState->transferredByteCount;

    /* Only enable the receive interrupt.  This should be ok since SPI is a synchronous
     * protocol, so every RX interrupt we get, we should be ready to send. However, since
     * the SPI has a shift register and data buffer (for transmit and receive), things may not
     * be cycle-to-cycle synchronous. To compensate for this, enabling the RX interrupt only
     * ensures that we do indeed receive data before sending out the next data word. In the
     * ISR we make sure to first check for the RX data buffer full before checking the TX
     * data register empty flag.
     */
    SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, true);
#endif

    return kStatus_SPI_Success;
}

#if FSL_FEATURE_SPI_FIFO_SIZE
/*!
 * @brief Fill up the TX FIFO with data.
 * This function fills up the TX FIFO.
 * This is not a public API as it is called from other driver functions.
 */
static void SPI_DRV_MasterFillupTxFifo(uint32_t instance)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];
    uint8_t byteToSendLow = 0;
    uint8_t byteToSendHigh = 0;

    /* Declare variables for storing volatile data later in the code */
    uint32_t remainRxByteCnt, remainTxByteCnt;

    spi_data_bitcount_mode_t bitCount = SPI_HAL_Get8or16BitMode(base);

    /* Store the SPI state struct volatile member variables into temporary
     * non-volatile variables to allow for MISRA compliant calculations
     */
    remainTxByteCnt = spiState->remainingSendByteCount;
    remainRxByteCnt = spiState->remainingReceiveByteCount;

    /* Architectural note: When developing the TX FIFO fill functionality, it was found that to
     * achieve more efficient run-time performance, it was better to first check the bits/frame
     * setting and then proceed with the FIFO fill management process, rather than to clutter the
     * FIFO fill process with continual checks of the bits/frame setting.
     */

    /* If bits/frame is greater than one byte */
    if (bitCount == kSpi16BitMode)
    {
        /* Fill the fifo until it is full or until the send word count is 0 or until the difference
         * between the remainingReceiveByteCount and remainingSendByteCount equals the FIFO depth.
         * The reason for checking the difference is to ensure we only send as much as the
         * RX FIFO can receive.  Note, the FIFO depth assumes maximum data length of 16-bits,
         * but since we are using 8-bit buffers, the FIFO depth is twice the reported depth.
         */
        while((SPI_HAL_GetFifoStatusFlag(base, kSpiTxFifoFull)== 0) &&
              ((remainRxByteCnt - remainTxByteCnt) < (g_spiFifoSize[instance]*2)))
        {
            if (spiState->sendBuffer)
            {
                byteToSendLow = *(spiState->sendBuffer);
                ++spiState->sendBuffer;

                byteToSendHigh = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteDataLow(base, byteToSendLow);
            SPI_HAL_WriteDataHigh(base, byteToSendHigh);

            spiState->remainingSendByteCount -= 2;  /* decrement by 2 */
            spiState->transferredByteCount += 2;  /* increment by 2 */

            /* Update the SPI state struct volatile member variables into temporary
             * non-volatile variables to allow for MISRA compliant calculations
             */
            remainTxByteCnt = spiState->remainingSendByteCount;
            remainRxByteCnt = spiState->remainingReceiveByteCount;

            /* exit loop if send count is zero */
            if (spiState->remainingSendByteCount == 0)
            {
                break;
            }
        }
    }
    /* Optimized for bit count = 8 */
    else
    {
        /* Fill the fifo until it is full or until the send word count is 0 or until the difference
         * between the remainingReceiveByteCount and remainingSendByteCount equals the FIFO depth.
         * The reason for checking the difference is to ensure we only send as much as the
         * RX FIFO can receive.  Note, the FIFO depth assumes maximum data length of 16-bits,
         * but since we are using 8-bit buffers, the FIFO depth is twice the reported depth.
         */
        while((SPI_HAL_GetFifoStatusFlag(base, kSpiTxFifoFull)== 0) &&
              ((remainRxByteCnt - remainTxByteCnt) < (g_spiFifoSize[instance]*2)))
        {
            if (spiState->sendBuffer)
            {
                byteToSendLow = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteDataLow(base, byteToSendLow);

            --spiState->remainingSendByteCount;
            ++spiState->transferredByteCount;

            /* Update the SPI state struct volatile member variables into temporary
             * non-volatile variables to allow for MISRA compliant calculations
             */
            remainTxByteCnt = spiState->remainingSendByteCount;
            remainRxByteCnt = spiState->remainingReceiveByteCount;

            /* exit loop if send count is zero */
            if (spiState->remainingSendByteCount == 0)
            {
                break;
            }
        }
    }
}
#endif /* FSL_FEATURE_SPI_FIFO_SIZE */

/*!
 * @brief Finish up a transfer.
 * Cleans up after a transfer is complete. Interrupts are disabled, and the SPI module
 * is disabled. This is not a public API as it is called from other driver functions.
 */
static void SPI_DRV_MasterCompleteTransfer(uint32_t instance)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];

    /* The transfer is complete.*/
    spiState->isTransferInProgress = false;

    /* Disable interrupts */
    SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, false);
    SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, false);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (g_spiFifoSize[instance] != 0)
    {
        /* Now disable the SPI FIFO interrupts */
        SPI_HAL_SetFifoIntCmd(base, kSpiTxFifoNearEmptyInt, false);
        SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, false);
    }
#endif

    if (spiState->isTransferBlocking)
    {
        /* Signal the synchronous completion object */
        OSA_SemaPost(&spiState->irqSync);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_MasterIRQHandler
 * Description   : Interrupt handler for SPI master mode.
 * This handler uses the buffers stored in the spi_master_state_t structs to transfer data.
 *
 *END**************************************************************************/
void SPI_DRV_MasterIRQHandler(uint32_t instance)
{
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_master_state_t * spiState = (spi_master_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];

    /* Exit the ISR if no transfer is happening for this instance.*/
    if (!spiState->isTransferInProgress)
    {
        return;
    }

    /* RECEIVE IRQ handler: Check read buffer only if there are remaining bytes to read. */
    if (spiState->remainingReceiveByteCount)
    {
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
        uint8_t byteReceivedLow, byteReceivedHigh;

        spi_data_bitcount_mode_t bitCntRx = SPI_HAL_Get8or16BitMode(base);

        /* If the SPI module contains a FIFO (and if it's enabled), drain the FIFO until it is empty
         * or until the remainingSendByteCount reaches 0.
         */
        if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
        {
            /* Clear the RX near full interrupt */
            SPI_HAL_ClearFifoIntUsingBitWrite(base, kSpiRxNearFullClearInt);

            /* Architectural note: When developing the RX FIFO drain code, it was found that to
             * achieve more efficient run-time performance, it was better to first check the
             * bits/frame setting and then proceed with the FIFO fill management process, rather
             * than to clutter the drain process with continual checks of the bits/frame setting.
             */

            /* Optimized for bit count = 16 with FIFO support */
            if (bitCntRx == kSpi16BitMode)
            {
                /* Do this while the RX FIFO is not empty */
                while (SPI_HAL_GetFifoStatusFlag(base, kSpiRxFifoEmpty) == 0)
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);
                    byteReceivedHigh = SPI_HAL_ReadDataHigh(base);

                    /* Store read bytes into rx buffer only if a buffer pointer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;

                        /* If the extraByte flag is set and these are the last 2 bytes, then skip.
                         * This will avoid over-writing the rx buffer with another un-needed byte.
                         */
                        if (!((spiState->extraByte) && (spiState->remainingReceiveByteCount == 2)))
                        {
                            *spiState->receiveBuffer = byteReceivedHigh;
                            ++spiState->receiveBuffer;
                        }
                    }

                    spiState->remainingReceiveByteCount -= 2; /* decrement the rx byte count by 2 */

                    /* If there is no more data to receive, break */
                    if (spiState->remainingReceiveByteCount == 0)
                    {
                        break;
                    }
                }
            }

            /* Optimized for bit count = 8 with FIFO support */
            else
            {
                while (SPI_HAL_GetFifoStatusFlag(base, kSpiRxFifoEmpty) == 0)
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);

                    /* Store read bytes into rx buffer only if a buffer pointer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;
                    }

                    --spiState->remainingReceiveByteCount; /* decrement the rx byte count by 1 */

                    /* If there is no more data to receive, break */
                    if (spiState->remainingReceiveByteCount == 0)
                    {
                        break;
                    }
                }
            }

            /* If the remaining RX byte count is less than the RX FIFO watermark, enable
             * the TX FIFO empty interrupt. Once the TX FIFO is empty, we are ensured
             * that the transmission is complete and can then drain the RX FIFO.
             */
            if (spiState->remainingReceiveByteCount < g_spiFifoSize[instance])
            {
                SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, true); /* TX FIFO empty interrupt */
            }
        }

        /* For SPI modules that do not have a FIFO (or if disabled), but have 16-bit transfer
         * capability */
        else
        {
            if (SPI_HAL_IsReadBuffFullPending(base))
            {

                /* For 16-bit transfers w/o FIFO support */
                if (bitCntRx == kSpi16BitMode)
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);
                    byteReceivedHigh = SPI_HAL_ReadDataHigh(base);

                    /* Store read bytes into rx buffer only if a buffer pointer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;

                        /* If the extraByte flag is set and these are the last 2 bytes, then skip.
                         * This will avoid over-writing the rx buffer with another un-needed byte.
                         */
                        if (!((spiState->extraByte) && (spiState->remainingReceiveByteCount == 2)))
                        {
                            *spiState->receiveBuffer = byteReceivedHigh;
                            ++spiState->receiveBuffer;
                        }
                    }

                    spiState->remainingReceiveByteCount -= 2; /* decrement the rx byte count by 2 */

                }

                /* For 8-bit transfers w/o FIFO support */
                else
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);

                    /* Store read bytes into rx buffer only if a buffer pointer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;
                    }

                    --spiState->remainingReceiveByteCount; /* decrement the rx byte count by 1 */
                }
            }
        }

#else /* For SPI modules that do not support 16-bit transfers and don't have FIFO */

        uint8_t byteReceived;
        /* For SPI modules without 16-bit transfer capability or FIFO support */
        if (SPI_HAL_IsReadBuffFullPending(base))
        {
            /* Read the bytes from the RX FIFO */
            byteReceived = SPI_HAL_ReadData(base);

            /* Store read bytes into rx buffer only if a buffer pointer was provided */
            if (spiState->receiveBuffer)
            {
                *spiState->receiveBuffer = byteReceived;
                ++spiState->receiveBuffer;
            }

            --spiState->remainingReceiveByteCount; /* decrement the rx byte count by 1 */
        }
#endif  /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
    }

    /* TRANSMIT IRQ handler
     * Check write buffer. We always have to send a byte in order to keep the transfer
     * moving. So if the caller didn't provide a send buffer, we just send a zero byte.
     */
    uint8_t byteToSend = 0;
    if (spiState->remainingSendByteCount)
    {
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
        uint8_t byteToSendLow = 0;
        uint8_t byteToSendHigh = 0;

        spi_data_bitcount_mode_t bitCntTx = SPI_HAL_Get8or16BitMode(base);

        /* If SPI module has a FIFO and if it is enabled */
        if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
        {
            if (SPI_HAL_GetFifoStatusFlag(base, kSpiTxNearEmpty))
            {
                /* Fill of the TX FIFO with ongoing data */
                SPI_DRV_MasterFillupTxFifo(instance);
             }
        }
        else
        {
            if (SPI_HAL_IsTxBuffEmptyPending(base))
            {
                if (bitCntTx == kSpi16BitMode)
                {
                    if (spiState->sendBuffer)
                    {
                        byteToSendLow = *(spiState->sendBuffer);
                        ++spiState->sendBuffer;

                        byteToSendHigh = *(spiState->sendBuffer);
                        ++spiState->sendBuffer;
                    }
                    SPI_HAL_WriteDataLow(base, byteToSendLow);
                    SPI_HAL_WriteDataHigh(base, byteToSendHigh);

                    spiState->remainingSendByteCount -= 2;  /* decrement by 2 */
                    spiState->transferredByteCount += 2;  /* increment by 2 */
                }
                else /* SPI configured for 8-bit transfers */
                {
                    if (spiState->sendBuffer)
                    {
                        byteToSend = *(spiState->sendBuffer);
                        ++spiState->sendBuffer;
                    }
                    SPI_HAL_WriteDataLow(base, byteToSend);

                    --spiState->remainingSendByteCount;
                    ++spiState->transferredByteCount;
                }
            }
        }
#else /* For SPI modules that do not support 16-bit transfers */
        if (SPI_HAL_IsTxBuffEmptyPending(base))
        {
            if (spiState->sendBuffer)
            {
                byteToSend = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteData(base, byteToSend);

            --spiState->remainingSendByteCount;
            ++spiState->transferredByteCount;
        }
#endif  /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
    }

    /* Check if we're done with this transfer.  The transfer is complete when all of the
     * expected data is received.
     */
    if ((spiState->remainingSendByteCount == 0) && (spiState->remainingReceiveByteCount == 0))
    {
        /* Complete the transfer. This disables the interrupts, so we don't wind up in
         * the ISR again.
         */
        SPI_DRV_MasterCompleteTransfer(instance);
    }
}

#endif /* FSL_FEATURE_SOC_SPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

