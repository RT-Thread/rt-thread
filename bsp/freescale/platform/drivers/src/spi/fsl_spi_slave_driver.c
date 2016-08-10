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

#include <assert.h>
#include <string.h>
#include "fsl_spi_slave_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_SPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Flags of SPI slave event.
 *
 * SPI event used to notify user that it finishes the task.
 */
typedef enum _spi_event_flags {
    kSpiTransferDone = 0x01,        /*!< Transferring done flag */
} spi_event_flag_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Pointer to runtime state structure.*/
extern void * g_spiStatePtr[SPI_INSTANCE_COUNT];

/* Table of SPI FIFO sizes per instance. */
extern const uint32_t g_spiFifoSize[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Configure SPI slave module and start the transfer
 *
 * This function updates SPI slave state structure, configures SPI slave module
 * using interrupt driven and then start the transfer.
 *
 * @param instance The instance number of the SPI peripheral.
 */
static spi_status_t SPI_DRV_SlaveStartTransfer(uint32_t instance);

/*!
 * @brief Stop the SPI slave transfer
 *
 * This function makes SPI slave transferring stop.
 *
 * @param instance The instance number of the SPI peripheral.
 */
static void SPI_DRV_SlaveCompleteTransfer(uint32_t instance);

#if FSL_FEATURE_SPI_FIFO_SIZE
/*!
 * @brief Fill up the TX FIFO by data from transmit buffer.
 *
 * This function fill up the available TX FIFO register by transmit data from the buffer.
 *
 * @param instance The instance number of the SPI peripheral.
 */
static void SPI_DRV_SlaveFillupTxFifo(uint32_t instance);
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveIRQHandler
 * Description   : SPI Slave Generic IRQ handler.
 *
 *END**************************************************************************/
void SPI_DRV_SlaveIRQHandler(uint32_t instance)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];
    int32_t minRemainingSend = 0;
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    spi_data_bitcount_mode_t bitCount = SPI_HAL_Get8or16BitMode(base);
#endif

    /* Exit the ISR if no transfer is happening for this instance.*/
    if (!spiState->isTransferInProgress)
    {
        return;
    }
    /* Calculate the minimum remaining send count value, if remainingSendByteCount less
     * than this value, disable the transmit interrupt
     */
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (bitCount == kSpi16BitMode)
    {
        minRemainingSend = -1;
    }
    else
    {
        minRemainingSend = 0;
    }
#else
    minRemainingSend = 0;
#endif

    /* TRANSMIT IRQ handler - note, handle TX first for slave mode
     * Check write buffer. We always have to send a byte in order to keep the transfer
     * moving. So if the caller didn't provide a send buffer, we just send a zero byte.
     */
    if (spiState->remainingSendByteCount >= minRemainingSend)
    {
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
        /* Initialize bytes to send with zero so that if tere is no send buffer, we'll always
         * send zeros as the default.
         */
        uint8_t byteToSendLow = 0;
        uint8_t byteToSendHigh = 0;

        /* Set the default sending value to dummy pattern value */
        byteToSendLow = spiState->dummyPattern & 0xFF;
        byteToSendHigh = (spiState->dummyPattern & 0xFF00) >> 8;

        /* If module instance has a FIFO (and is enabled), fill up any empty slots in the FIFO */
        if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
        {
            /* Fill of the TX FIFO with ongoing data */
            SPI_DRV_SlaveFillupTxFifo(instance);
        }
        /* For instances without a FIFO or if disabled */
        else
        {
            if (SPI_HAL_IsTxBuffEmptyPending(base))
            {
                if (bitCount == kSpi16BitMode)
                {
                    if ((spiState->sendBuffer) && (spiState->remainingSendByteCount > 0))
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
                    if ((spiState->sendBuffer) && (spiState->remainingSendByteCount > 0))
                    {
                        byteToSendLow = *(spiState->sendBuffer);
                        ++spiState->sendBuffer;
                    }
                    SPI_HAL_WriteDataLow(base, byteToSendLow);

                    --spiState->remainingSendByteCount;
                    ++spiState->transferredByteCount;
                }
            }
        }
#else /* For SPI modules that do not support 16-bit transfers */
        if (SPI_HAL_IsTxBuffEmptyPending(base))
        {
            uint8_t byteToSend = spiState->dummyPattern;
            if ((spiState->sendBuffer) && (spiState->remainingSendByteCount > 0))
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

#if 1
    if (spiState->remainingSendByteCount < minRemainingSend)
    {
        /* After all send data was pushed into TX FIFO or buffer, the TX near empty interrupt
         * and SPI transmit interrupt must be disabled.
         */
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
        if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
        {
            /* Clear the TX near empty interrupt */
            SPI_HAL_ClearFifoIntUsingBitWrite(base, kSpiTxFifoEmptyClearInt);
            /* Disable TX near empty interrupt */
            SPI_HAL_SetFifoIntCmd(base, kSpiTxFifoNearEmptyInt, false);
        }
        else
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
        {
            /* Disable Tx buffer empty interrupt */
            SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, false);
        }
    }
#endif

    /* RECEIVE IRQ handler
     * Check read buffer only if there are remaining bytes to read. If user did not supply a
     * receive buffer, then simply read the data register and discard the data.
     */
    if (spiState->remainingReceiveByteCount > 0)
    {
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
        uint8_t byteReceivedLow, byteReceivedHigh;

        /* If the SPI module contains a FIFO (and if enabled), drain the FIFO until it is empty
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
            if (bitCount == kSpi16BitMode)
            {
                /* Do this while the RX FIFO is not empty */
                while (SPI_HAL_GetFifoStatusFlag(base, kSpiRxFifoEmpty) == 0)
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);
                    byteReceivedHigh = SPI_HAL_ReadDataHigh(base);

                    /* Store read bytes into rx buffer, only if rx buffer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;

                        if (--spiState->remainingReceiveByteCount > 0)
                        {
                            *spiState->receiveBuffer = byteReceivedHigh;
                            ++spiState->receiveBuffer;
                        }
                        --spiState->remainingReceiveByteCount;
                    }
                    else
                    {
                        spiState->remainingReceiveByteCount -= 2;
                    }

                    /* If there is no more data to receive, break */
                    if (spiState->remainingReceiveByteCount == 0)
                    {
                        break;
                    }
                }
            }
            /* Optimized for bit count = 8 */
            else
            {
                while (SPI_HAL_GetFifoStatusFlag(base, kSpiRxFifoEmpty) == 0)
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);

                    /* Store read bytes into rx buffer, only if rx buffer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;
                    }

                    --spiState->remainingReceiveByteCount;

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
        /* For SPI modules that do not have a FIFO, but have 16-bit transfer capability */
        else
        {
            if (SPI_HAL_IsReadBuffFullPending(base))
            {
                if (bitCount == kSpi16BitMode)
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);
                    byteReceivedHigh = SPI_HAL_ReadDataHigh(base);

                    /* Store read bytes into rx buffer, only if rx buffer was provided */
                    if (spiState->receiveBuffer)
                    {

                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;
                        if (--spiState->remainingReceiveByteCount > 0)
                        {

                            *spiState->receiveBuffer = byteReceivedHigh;
                            ++spiState->receiveBuffer;
                        }
                        --spiState->remainingReceiveByteCount;
                    }
                    else
                    {
                        spiState->remainingReceiveByteCount -= 2;
                    }
                }
                else /* For 8-bit transfers */
                {
                    /* Read the bytes from the RX FIFO */
                    byteReceivedLow = SPI_HAL_ReadDataLow(base);

                    /* Store read bytes into rx buffer, only if rx buffer was provided */
                    if (spiState->receiveBuffer)
                    {
                        *spiState->receiveBuffer = byteReceivedLow;
                        ++spiState->receiveBuffer;
                    }
                    --spiState->remainingReceiveByteCount;
                }
            }
        }
#else
        uint8_t byteReceived;
        /* For SPI modules without 16-bit transfer capability or FIFO support */
        if (SPI_HAL_IsReadBuffFullPending(base))
        {
            /* Read the bytes from the RX FIFO */
            byteReceived = SPI_HAL_ReadData(base);

            /* Store read bytes into rx buffer, only if rx buffer was provided */
            if (spiState->receiveBuffer)
            {
                *spiState->receiveBuffer = byteReceived;
                ++spiState->receiveBuffer;
            }

            --spiState->remainingReceiveByteCount;
        }
#endif  /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
    }

    /* Check if we're done with this transfer.*/
    if ((spiState->remainingSendByteCount <= 0) && (spiState->remainingReceiveByteCount <= 0))
    {
        /* Complete the transfer. This disables the interrupts, so we don't wind up in
         * the ISR again.
         */
        SPI_DRV_SlaveCompleteTransfer(instance);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveInit
 * Description   : Initializes the SPI module for slave mode.
 * Saves the application callback info, turns on the clock to the module,
 * enables the device, and enables interrupts. Sets the SPI to a slave mode.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_SlaveInit(uint32_t instance, spi_slave_state_t * spiState,
                       const spi_slave_user_config_t * slaveConfig)
{
    SPI_Type *base = g_spiBase[instance];

    assert(slaveConfig);
    assert(instance < SPI_INSTANCE_COUNT);
    assert(spiState);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (slaveConfig->bitCount > kSpi16BitMode)
    {
        /* bits/frame larger than hardware support */
        return kStatus_SPI_InvalidParameter;
    }
#endif

    /* Check if the slave already initialized */
    if (g_spiStatePtr[instance])
    {
        return kStatus_SPI_AlreadyInitialized;
    }

    /* Clear the state for this instance. */
    memset(spiState, 0, sizeof(* spiState));

    /* Update dummy pattern value */
    spiState->dummyPattern = slaveConfig->dummyPattern;

    /* Enable clock for SPI */
    CLOCK_SYS_EnableSpiClock(instance);

    /* Reset the SPI module to its default settings including disabling SPI */
    SPI_HAL_Init(base);

    /* Initialize the event structure */
    if (OSA_EventCreate(&spiState->event, kEventAutoClear) != kStatus_OSA_Success)
    {
        return kStatus_SPI_Error;
    }

    /* Set SPI to slave mode */
    SPI_HAL_SetMasterSlave(base, kSpiSlave);

    /* Configure the slave clock polarity, phase and data direction */
    SPI_HAL_SetDataFormat(base, slaveConfig->polarity, slaveConfig->phase,
                          slaveConfig->direction);

    /* Set the SPI pin mode to normal mode */
    SPI_HAL_SetPinMode(base, kSpiPinMode_Normal);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Set the bit/frame mode */
    SPI_HAL_Set8or16BitMode(base, slaveConfig->bitCount);
#endif

#if FSL_FEATURE_SPI_FIFO_SIZE
    if (g_spiFifoSize[instance] != 0)
    {
        /* If SPI module contains a FIFO, enable it and set watermarks to half full/empty */
        SPI_HAL_SetFifoMode(base, true, kSpiTxFifoOneHalfEmpty, kSpiRxFifoOneHalfFull);
    }
#endif

    /* Save runtime structure pointers to irq handler can point to the correct state structure */
    g_spiStatePtr[instance] = spiState;

    /* Enable SPI interrupt. */
    INT_SYS_EnableIRQ(g_spiIrqId[instance]);

    /* SPI system enable now */
    SPI_HAL_Enable(base);

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveDeinit
 * Description   : De-initializes the device.
 * Clears the control register and turns off the clock to the module.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_SlaveDeinit(uint32_t instance)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];

    assert(instance < SPI_INSTANCE_COUNT);

    if (spiState == NULL)
    {
        return kStatus_SPI_NonInit;
    }

    /* Disable SPI interrupt */
    INT_SYS_DisableIRQ(g_spiIrqId[instance]);

    /* Reset the SPI module to its default settings including disabling SPI and its interrupts */
    SPI_HAL_Init(base);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (g_spiFifoSize[instance] != 0)
    {
        /* Disable the FIFO feature */
        SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, false);
    }

    /* Disable transmit interrupt */
    SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, false);
#endif

    /* SPI system disable */
    SPI_HAL_Disable(base);

    /* Disable clock for SPI */
    CLOCK_SYS_DisableSpiClock(instance);

    /* Destroy the event */
    OSA_EventDestroy(&spiState->event);

    /* Clear state pointer. */
    g_spiStatePtr[instance] = NULL;

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveTransfer
 * Description   : Transfer data with the master. Starts the transfer with
 * transmit buffer, receive buffer and transfer byte count passed.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_SlaveTransfer(uint32_t instance,
                                   const uint8_t *sendBuffer,
                                   uint8_t *receiveBuffer,
                                   uint32_t transferByteCount)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];
    spi_status_t errorStatus = kStatus_SPI_Success;

    /* Validate the parameter */
    assert(instance < SPI_INSTANCE_COUNT);

    if ((!sendBuffer) && (!receiveBuffer))
    {
        /* sendBuffer and receiveBuffer are not available, this is invalid */
        return kStatus_SPI_InvalidParameter;
    }

    if (!transferByteCount)
    {
        /* number of transfer bytes is 0 */
        return kStatus_SPI_InvalidParameter;
    }

    if (spiState->isTransferInProgress)
    {
        /* The another transfer is in progress */
        return kStatus_SPI_Busy;
    }

    /* fill in members of the run-time state struct */
    spiState->isSync = false;
    spiState->sendBuffer = sendBuffer;
    spiState->receiveBuffer = receiveBuffer;
    spiState->remainingSendByteCount = transferByteCount;
    spiState->remainingReceiveByteCount = transferByteCount;

    /* Start the transfer */
    errorStatus = SPI_DRV_SlaveStartTransfer(instance);
    if (errorStatus != kStatus_SPI_Success)
    {
        return errorStatus;
    }

    return kStatus_SPI_Success;
}


#if FSL_FEATURE_SPI_FIFO_SIZE
/*!
 * @brief Fill up the TX FIFO with data.
 * This function fills up the TX FIFO.
 * This is not a public API as it is called from other driver functions.
 */
static void SPI_DRV_SlaveFillupTxFifo(uint32_t instance)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];
    uint8_t byteToSendLow = 0;
    uint8_t byteToSendHigh = 0;
    spi_data_bitcount_mode_t bitCount = SPI_HAL_Get8or16BitMode(base);  /* the bit/frame */

    /* Set the default sending value to dummy pattern value */
    byteToSendLow = spiState->dummyPattern & 0xFF;
    byteToSendHigh = (spiState->dummyPattern & 0xFF00) >> 8;

    /* Architectural note: When developing the TX FIFO fill functionality, it was found that to
     * achieve more efficient run-time performance, it was better to first check the bits/frame
     * setting and then proceed with the FIFO fill management process, rather than to clutter the
     * FIFO fill process with continual checks of the bits/frame setting.
     */

    /* If bits/frame is greater than one byte */
    if (bitCount == kSpi16BitMode)
    {
        /* Fill the fifo until it is full or until the send word count is 0 */
        while(SPI_HAL_GetFifoStatusFlag(base, kSpiTxFifoFull)== 0)
        {
            if ((spiState->sendBuffer) && (spiState->remainingSendByteCount > 0))
            {
                byteToSendLow = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
                byteToSendHigh = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteDataLow(base, byteToSendLow);
            SPI_HAL_WriteDataHigh(base, byteToSendHigh);

            spiState->remainingSendByteCount -= 2;      /* decrement by 2 */
            spiState->transferredByteCount += 2;        /* increment by 2 */

            /* exit loop if send count is zero */
            if (spiState->remainingSendByteCount < 0)
            {
                break;
            }
        }
    }
    /* Optimized for bit count = 8 */
    else
    {
        /* Fill the fifo until it is full or until the send word count is 0 */
        while(SPI_HAL_GetFifoStatusFlag(base, kSpiTxFifoFull)== 0)
        {
            if ((spiState->sendBuffer) && (spiState->remainingSendByteCount > 0))
            {
                byteToSendLow = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteDataLow(base, byteToSendLow);

            --spiState->remainingSendByteCount;
            ++spiState->transferredByteCount;

            /* exit loop if send count is zero */
            if (spiState->remainingSendByteCount < 0)
            {
                break;
            }
        }
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveStartTransfer
 * Description   : Starts the transfer with information passed.
 *
 *END**************************************************************************/
static spi_status_t SPI_DRV_SlaveStartTransfer(uint32_t instance)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    spi_data_bitcount_mode_t bitCount;

    bitCount = SPI_HAL_Get8or16BitMode(base);
#endif

    /* Save information about the transfer for use by the ISR. */
    spiState->isTransferInProgress = true;
    spiState->transferredByteCount = 0;

    /* SPI system disable */
    SPI_HAL_Disable(base);
    /* SPI system enable now */
    SPI_HAL_Enable(base);

    /* Make sure TX data register (or FIFO) is empty. If not, return appropriate
     * error status. This also causes a read of the status
     * register which is required before writing to the data register below.
     */
    if (SPI_HAL_IsTxBuffEmptyPending(base) != 1)
    {
        return kStatus_SPI_TxBufferNotEmpty;
    }

    /* If SPI module/instance contains a FIFO (and enabled), proceed with FIFO usage, else bypass */
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
#if FSL_FEATURE_SPI_FIFO_SIZE
    if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
    {
        /* First fill the FIFO with data */
        SPI_DRV_SlaveFillupTxFifo(instance);

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
            /* Enable both receive and transmit interrupts to make the slave can keep up with the
             * master.
             */
            SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, true);
            SPI_HAL_SetFifoIntCmd(base, kSpiTxFifoNearEmptyInt, true);
        }
    }
    else
#endif /* FSL_FEATURE_SPI_FIFO_SIZE */
    /* For instances without a FIFO but with the capability to transfer up to 16-bits */
    {
        uint8_t byteToSend = 0;
        if (bitCount == kSpi16BitMode)
        {
            uint8_t byteToSendLow = 0;
            uint8_t byteToSendHigh = 0;

            if (spiState->sendBuffer)
            {
                byteToSendLow = *(spiState->sendBuffer);
                ++spiState->sendBuffer;

                byteToSendHigh = *(spiState->sendBuffer);
                ++spiState->sendBuffer;
            }
            SPI_HAL_WriteDataLow(base, byteToSendLow);
            SPI_HAL_WriteDataHigh(base, byteToSendHigh);

            spiState->remainingSendByteCount -= 2;      /* decrement by 2 */
            spiState->transferredByteCount += 2;        /* increment by 2 */
        }
        else        /* SPI configured for 8-bit transfers */
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

        /* Enable both receive and transmit interrupts to make the slave can keep up with the
         * master.
         */
        SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, true);
        SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, true);
    }
#else
    /* For modules that do not support 16-bit transfers or FIFO
     * Start the transfer by writing the first byte. If a send buffer was provided, the byte
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

    /* Enable both receive and transmit interrupts to make the slave can keep up with the
     * master.
     */
    SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, true);
    SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, true);

#endif

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveCompleteTransfer
 * Description   : The transfer has ben completed, stop it.
 *
 *END**************************************************************************/
static void SPI_DRV_SlaveCompleteTransfer(uint32_t instance)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];

    /* The transfer is complete, update state */
    spiState->isTransferInProgress = false;
    spiState->status = kStatus_SPI_Success;
    spiState->errorCount = 0;
    spiState->sendBuffer = NULL;
    spiState->receiveBuffer = NULL;
    spiState->remainingSendByteCount = 0;
    spiState->remainingReceiveByteCount = 0;

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

    /* Set the event flag if function is sync */
    if(spiState->isSync)
    {
        OSA_EventSet(&spiState->event, kSpiTransferDone);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveAbortTransfer
 * Description   : Stop the transfer if it is in progress
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_SlaveAbortTransfer(uint32_t instance)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];

    /* Check instance is valid or not */
    assert(instance < SPI_INSTANCE_COUNT);

    /* Check driver is initialized */
    if (!spiState)
    {
        return kStatus_SPI_NonInit;
    }

    /* Check transfer is in progress */
    if (!spiState->isTransferInProgress)
    {
        return kStatus_SPI_NoTransferInProgress;
    }

    /* Stop transfer */
    SPI_DRV_SlaveCompleteTransfer(instance);

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveGetTransferStatus
 * Description   : Returns whether the previous transfer finished.
 * When performing an a-sync transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can get the number of words that have been
 * transferred up to now.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_SlaveGetTransferStatus(uint32_t instance,
                                            uint32_t * framesTransferred)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];

    /* Fill in the bytes transferred. */
    if (framesTransferred)
    {
        *framesTransferred = spiState->transferredByteCount;
    }

    return (spiState->isTransferInProgress ? kStatus_SPI_Busy : kStatus_SPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_SlaveTransferBlocking
 * Description   : Transfer data with the master, using blocking call.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_SlaveTransferBlocking(uint32_t instance,
                                           const uint8_t *sendBuffer,
                                           uint8_t *receiveBuffer,
                                           uint32_t transferByteCount,
                                           uint32_t timeout)
{
    spi_slave_state_t * spiState = (spi_slave_state_t *)g_spiStatePtr[instance];
    spi_status_t errorStatus = kStatus_SPI_Success;
    event_flags_t setFlags = 0;

    /* Validate the parameter */
    assert(instance < SPI_INSTANCE_COUNT);

    if ((!sendBuffer) && (!receiveBuffer))
    {
        /* sendBuffer and receiveBuffer are not available, this is invalid */
        return kStatus_SPI_InvalidParameter;
    }

    if (!transferByteCount)
    {
        /* number of transfer bytes is 0 */
        return kStatus_SPI_InvalidParameter;
    }

    if (spiState->isTransferInProgress)
    {
        /* The another transfer is in progress */
        return kStatus_SPI_Busy;
    }

    /* fill in members of the run-time state struct */
    spiState->isSync = true;
    spiState->sendBuffer = (const uint8_t *)sendBuffer;
    spiState->receiveBuffer = (uint8_t *)receiveBuffer;
    spiState->remainingSendByteCount = transferByteCount;
    spiState->remainingReceiveByteCount = transferByteCount;

    /* Clear the event flags */
    OSA_EventClear(&spiState->event, kSpiTransferDone);

    errorStatus = SPI_DRV_SlaveStartTransfer(instance);
    if (errorStatus != kStatus_SPI_Success)
    {
        return errorStatus;
    }

    /* As this is a synchronous transfer, wait until the transfer is complete. */
    osa_status_t syncStatus;

    do
    {
        syncStatus = OSA_EventWait(&spiState->event, kSpiTransferDone, true, timeout, &setFlags);
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Abort the transfer so it doesn't continue unexpectedly. */
        SPI_DRV_SlaveAbortTransfer(instance);

        errorStatus = kStatus_SPI_Timeout;
    }

    return errorStatus;
}

#endif /* FSL_FEATURE_SOC_SPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

