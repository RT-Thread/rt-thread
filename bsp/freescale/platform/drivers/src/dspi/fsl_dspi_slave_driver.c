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
#include <assert.h>
#include "fsl_dspi_slave_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Flags of DSPI slave event.
 *
 * DSPI event used to notify user that it finishes the task.
 */
typedef enum _dspi_event_flags {
    kDspiTransferDone = 0x01,       /*!< Transferring done flag */
} dspi_event_flag_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to runtime state structure.*/
extern void * g_dspiStatePtr[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Finish up a transfer.
 * Cleans up after a transfer is complete. Interrupts are disabled, and the DSPI module
 * is disabled. This is not a public API as it is called from other driver functions.
 */
static void DSPI_DRV_SlaveCompleteTransfer(uint32_t instance);
/*!
 * @brief DSPI Slave Generic IRQ handler.
 *
 * This handler check errors of driver and it puts data into Tx FIFO, gets data
 * from Rx FIFO whenever data transmitting/received.
 * This is not a public API as it is called whenever an interrupt occurs.
 */
static void DSPI_DRV_SlaveStartTransfer(uint32_t instance,
                                        const uint8_t *sendBuffer,
                                        uint8_t *receiveBuffer,
                                        uint32_t transferCount);
/*!
 * @brief Fill up the TX FIFO with data.
 * This function fills up the TX FIFO with initial data for start of transfers where
 * it will first clear the transfer count.  Otherwise, if the TX FIFO fill is part
 * of an ongoing transfer then do not clear the transfer count.
 * This is not a public API as it is called from other driver functions.
 */
static void DSPI_DRV_SlaveFillUpTxFifo(uint32_t instance);

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveIRQHandler
 * Description   : DSPI Slave Generic IRQ handler.
 *
 * This handler check errors of driver and it puts data into Tx FIFO, gets data
 * from Rx FIFO whenever data transmitting/received.
 *
 *END**************************************************************************/
void DSPI_DRV_SlaveIRQHandler(uint32_t instance)
{
    SPI_Type *base = g_dspiBase[instance];
    dspi_slave_state_t *dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    uint8_t nBytes;

    /* Calculate number of bytes in a frame */
    nBytes = dspiState->bitsPerFrame >> 3;      /* Number of bytes is bits/frame divide 8 */
    if ((dspiState->bitsPerFrame & 0x07) != 0)  /* Bits/frame module 8 is not zero */
    {
        nBytes += 1;
    }

    /* Because SPI protocol is synchronous, the number of bytes that that slave received from the
     * master is the actual number of bytes that the slave transmitted to the master. So we only
     * monitor the received size to know when the transfer is complete.
     */
    if (dspiState->remainingReceiveByteCount > 0)
    {
        /* Read data if remaining receive byte > 0 */
        uint32_t dataReceived;
        uint32_t dataSend = 0;

        while (DSPI_HAL_GetStatusFlag(base, kDspiRxFifoDrainRequest))
        {
            /* Have received data in the buffer. */
            dataReceived = DSPI_HAL_ReadData(base);
            /* clear the rx fifo drain request, needed for non-DMA applications as this flag
             * will remain set even if the rx fifo is empty. By manually clearing this flag, it
             * either remain clear if no more data is in the fifo, or it will set if there is
             * more data in the fifo.
             */
            DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoDrainRequest);

            /* If bits/frame is one byte */
            if (nBytes == 1)
            {
                if (dspiState->receiveBuffer)
                {
                    /* Receive buffer is not null, store data into it */
                    *dspiState->receiveBuffer = dataReceived;
                    ++dspiState->receiveBuffer;
                }
                if (dspiState->sendBuffer)
                {
                    dataSend = *dspiState->sendBuffer;
                    ++dspiState->sendBuffer;
                }

                /* Descrease remaining receive byte count */
                --dspiState->remainingReceiveByteCount;
                --dspiState->remainingSendByteCount;
            }
            /* If bits/frame is 2 bytes */
            else
            {
                /* With multibytes frame receiving, we only receive till the received size
                 * matches user request. Other bytes will be ignored.
                 */
                if (dspiState->receiveBuffer)
                {
                    /* Receive buffer is not null, store first byte into it */
                    *dspiState->receiveBuffer = dataReceived;
                    ++dspiState->receiveBuffer;

                    if (--dspiState->remainingReceiveByteCount > 0)
                    {
                        /* Receive buffer is not null, store second byte into it */
                        *dspiState->receiveBuffer = dataReceived >> 8;
                        ++dspiState->receiveBuffer;
                    }

                    /* Decrease remaining receive byte count */
                    --dspiState->remainingReceiveByteCount;
                }
                else
                {
                    /* receive buffer is null, just decrease remaining byte count */
                    dspiState->remainingReceiveByteCount -= 2;
                }
                if (dspiState->sendBuffer)
                {
                    dataSend = *dspiState->sendBuffer;
                    ++dspiState->sendBuffer;
                    dataSend |= (uint32_t)(*dspiState->sendBuffer) << 8;
                    ++dspiState->sendBuffer;
                }
                dspiState->remainingSendByteCount -= 2;
            }

            if (dspiState->sendBuffer == NULL)
            {
                dataSend = dspiState->dummyPattern;
            }
            /* Write the data to the DSPI data register */
            DSPI_HAL_WriteDataSlavemode(base, dataSend);
            /* try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
            DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);
            if (dspiState->remainingReceiveByteCount <= 0)
            {
                break;
            }
        }
    }
    /* Check if remaining receive byte count matches user request */
    if (dspiState->remainingReceiveByteCount <= 0)
    {
        /* Other cases, stop the transfer. */
        DSPI_DRV_SlaveCompleteTransfer(instance);
        return;
    }

    /* catch tx fifo underflow conditions, service only if tx under flow interrupt enabled */
    if ((DSPI_HAL_GetStatusFlag(base, kDspiTxFifoUnderflow)) &&
        (DSPI_HAL_GetIntMode(base, kDspiTxFifoUnderflow)))
    {
        DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoUnderflow);
        /* Change state to error and clear flag */
        dspiState->status = kStatus_DSPI_Error;
        dspiState->errorCount++;
    }
    /* catch rx fifo overflow conditions, service only if rx over flow interrupt enabled */
    if ((DSPI_HAL_GetStatusFlag(base, kDspiRxFifoOverflow)) &&
        (DSPI_HAL_GetIntMode(base, kDspiRxFifoOverflow)))
    {
        DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoOverflow);
        /* Change state to error and clear flag */
        dspiState->status = kStatus_DSPI_Error;
        dspiState->errorCount++;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveInit
 * Description   : Initialize a DSPI slave instance.
 * Un-gate its clock, initialize required resources.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_SlaveInit(uint32_t instance,
                                 dspi_slave_state_t * dspiState,
                                 const dspi_slave_user_config_t * slaveConfig)
{
    dspi_status_t errorCode = kStatus_DSPI_Success;
    SPI_Type *base = g_dspiBase[instance];

    /* Check parameter pointer is not NULL */
    if ((dspiState == NULL) || (slaveConfig == NULL))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* Check DSPI slave instance is already initialized */
    if (g_dspiStatePtr[instance])
    {
        return kStatus_DSPI_Initialized;
    }

    /* Check bits/frame number */
    if (slaveConfig->dataConfig.bitsPerFrame > 16)
    {
        return kStatus_DSPI_OutOfRange;
    }

    /* Clear the run-time state struct for this instance. */
    memset(dspiState, 0, sizeof(* dspiState));

    /* Initial default value for ring buffer */
    dspiState->status = kStatus_DSPI_Success;
    dspiState->errorCount = 0;
    dspiState->dummyPattern = slaveConfig->dummyPattern;
    dspiState->remainingSendByteCount = 0;
    dspiState->remainingReceiveByteCount = 0;
    dspiState->isTransferInProgress = false;
    dspiState->receiveBuffer = NULL;
    dspiState->sendBuffer = NULL;

    if (kStatus_OSA_Success != OSA_EventCreate(&dspiState->event, kEventAutoClear))
    {
        /* Create event error */
        return kStatus_DSPI_Error;
    }

    /* configure the run-time state struct with the nubmer of bits/frame */
    dspiState->bitsPerFrame = slaveConfig->dataConfig.bitsPerFrame;

    /* Enable clock for DSPI */
    CLOCK_SYS_EnableSpiClock(instance);

    /* Reset the DSPI module, which also disables the DSPI module */
    DSPI_HAL_Init(base);

    /* Set to slave mode. */
    DSPI_HAL_SetMasterSlaveMode(base, kDspiSlave);

    errorCode = DSPI_HAL_SetDataFormat(base, kDspiCtar0, &slaveConfig->dataConfig);

    /* Enable fifo operation (regardless of FIFO depth) */
    DSPI_HAL_SetFifoCmd(base, true, true);

    /* DSPI system enable */
    DSPI_HAL_Enable(base);

    /* flush the fifos */
    DSPI_HAL_SetFlushFifoCmd(base, true, true);

    /* Configure IRQ state structure, so irq handler can point to the correct state structure */
    g_dspiStatePtr[instance] = dspiState;

    /* Clear the Tx FIFO Fill Flag (TFFF) status bit */
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);

    /* Enable the interrupt */
    INT_SYS_EnableIRQ(g_dspiIrqId[instance]);

    /* Enable the module */
    DSPI_HAL_Enable(base);

    /* Start the transfer process in the hardware */
    DSPI_HAL_StartTransfer(base);

    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveDeinit
 * Description   : Shutdown a DSPI instance.
 * Resets the DSPI peripheral, disables the interrupt to the core, and gates its clock.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_SlaveDeinit(uint32_t instance)
{
    /* instantiate local variable of type dspi_slave_state_t and equate it to the
     * pointer to state
     */
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* Validate function parameters */
    assert(instance < SPI_INSTANCE_COUNT);

    if (!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }

    /* disable the interrupt */
    INT_SYS_DisableIRQ(g_dspiIrqId[instance]);

    /* Stop the transfer process in the slave */
    DSPI_HAL_StopTransfer(base);

    /* Wait until the DSPI run status signals that is has halted before shutting
     * down the module and before gating off the DSPI clock source.  Otherwise, if the DSPI
     * is shut down before it has halted it's internal processes, it may be left in an unknown
     * state.
     */
    /* Note that if the master slave select is still asserted, the run status will never clear.
     * Hence, ensure before shutting down the slave that the master has de-asserted the slave
     * select signal (it should be high if slave select active low or it should be low if
     * slave select is active high).
     */
    while((DSPI_HAL_GetStatusFlag(base, kDspiTxAndRxStatus))) { }

    /* Restore the module to defaults then power it down. This also disables the DSPI module. */
    DSPI_HAL_Init(base);

    /* Gate the clock for DSPI. */
    CLOCK_SYS_DisableSpiClock(instance);

    /* Destroy event */
    OSA_EventDestroy(&dspiState->event);

    /* Clear state pointer. */
    g_dspiStatePtr[instance] = NULL;

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveFillUpTxFifo
 * Description   : This function fills up the TX FIFO with initial data for start of transfers
 * where it will first clear the transfer count.  Otherwise, if the TX FIFO fill is part of an
 * ongoing transfer then do not clear the transfer count.  The param "isInitialData" is used
 * to determine if this is an initial data fill.
 *END**************************************************************************/
static void DSPI_DRV_SlaveFillUpTxFifo(uint32_t instance)
{
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];
    uint32_t transmitData = 0; /* Maximum supported data bit length in slave mode is 32-bits */
    uint8_t nBytes = 0;

    /* Calculate number of bytes in a frame */
    nBytes = dspiState->bitsPerFrame >> 3;
    if ((dspiState->bitsPerFrame & 0x07) != 0)
    {
        nBytes += 1;
    }

    /* Service the transmitter, if transmit buffer provided, transmit the data,
     * else transmit dummy pattern
     */
    while(DSPI_HAL_GetStatusFlag(base, kDspiTxFifoFillRequest))
    {
        /* transmit data */
        if(dspiState->remainingSendByteCount > 0)
        {
            /* Have data to transmit, update the transmit data and push to FIFO */
            if(nBytes == 1)
            {
                /* bits/frame is 1 byte */
                if (dspiState->sendBuffer)
                {
                    /* Update transmit data and transmit pointer */
                    transmitData = *dspiState->sendBuffer;
                    dspiState->sendBuffer++;
                }
                else
                {
                    transmitData = dspiState->dummyPattern;
                }

                /* Decrease remaining size */
                --dspiState->remainingSendByteCount;
            }
            /* bits/frame is 2 bytes */
            else
            {
                /* With multibytes per frame transmission, the transmit frame contains data from
                 * transmit buffer until sent size matches user request. Other bytes will set to
                 * dummy pattern value.
                 */

                if (dspiState->sendBuffer)
                {
                    /* Update first byte of transmit data and transmit pointer */
                    transmitData = *dspiState->sendBuffer;
                    dspiState->sendBuffer++;

                    /* Check if send completed, decrease remaining size */
                    if(--dspiState->remainingSendByteCount > 0)
                    {
                        /* Update second byte of transmit data and transmit pointer */
                        transmitData |= (uint32_t)(*dspiState->sendBuffer) << 8;
                        dspiState->sendBuffer++;
                    }
                    else
                    {
                        /* Update second byte of transmit data to second byte of dummy pattern */
                        transmitData |= dspiState->dummyPattern & 0xFF00;
                    }

                    /* Decrease remaining size */
                    --dspiState->remainingSendByteCount;
                }
                else
                {
                    /* Decrease remaining size */
                    dspiState->remainingSendByteCount -= 2;
                    transmitData = dspiState->dummyPattern;
                }
            }
        }
        else
        {
            /* Nothing to transmit, send dummy pattern to master */
            transmitData = dspiState->dummyPattern;
        }

        /* Write the data to the DSPI data register */
        DSPI_HAL_WriteDataSlavemode(base, transmitData);
        /* try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
        DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveStartTransfer
 * Description   : Starts transfer data on SPI bus using interrupt and non-blocking call
 * Start DSPI transfering, update transmit/receive information into slave state structure
 *
 *END**************************************************************************/
static void DSPI_DRV_SlaveStartTransfer(uint32_t instance,
                                        const uint8_t *sendBuffer,
                                        uint8_t *receiveBuffer,
                                        uint32_t transferCount)
{
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* Save information about the transfer for use by the ISR. */
    dspiState->isTransferInProgress = true;

    /* Store transfer information */
    dspiState->sendBuffer = sendBuffer;
    dspiState->receiveBuffer = receiveBuffer;
    dspiState->remainingSendByteCount = transferCount;
    dspiState->remainingReceiveByteCount = transferCount;
    dspiState->errorCount = 0;

    /* Restart the transfer by stop then start again, this will clear out the shift register */
    DSPI_HAL_StopTransfer(base);

    /* flush the fifos */
    DSPI_HAL_SetFlushFifoCmd(base, true, true);

    /* Clear status flags that may have been set from previous transfers */
    DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
    DSPI_HAL_ClearStatusFlag(base, kDspiEndOfQueue);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoUnderflow);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);
    DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoOverflow);
    DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoDrainRequest);

    /* Clear the transfer count */
    DSPI_HAL_PresetTransferCount(base, 0);

    /* Start the transfer, make sure to do this before filling the FIFO */
    DSPI_HAL_StartTransfer(base);

    /* Prepare data to transmit */
    DSPI_DRV_SlaveFillUpTxFifo(instance);

    /* Enable RX FIFO drain request, the slave only use this interrupt */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, true);
    if(receiveBuffer)
    {
        /* RX FIFO overflow request enable */
        DSPI_HAL_SetIntMode(base, kDspiRxFifoOverflow, true);
    }
    if (sendBuffer)
    {
        /* TX FIFO underflow request enable */
        DSPI_HAL_SetIntMode(base, kDspiTxFifoUnderflow, true);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveCompleteTransfer
 * Description   : Finish the transfer
 * Called when transfer is finished
 *
 *END**************************************************************************/
static void DSPI_DRV_SlaveCompleteTransfer(uint32_t instance)
{
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* The transfer is complete. */
    dspiState->isTransferInProgress = false;
    dspiState->sendBuffer = NULL;
    dspiState->receiveBuffer = NULL;
    dspiState->remainingReceiveByteCount = 0;
    dspiState->remainingSendByteCount = 0;

    /* Disable interrupt requests */
    /* RX FIFO Drain request: RFDF_RE */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, false);

    /* Disable TX FIFO Fill request */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateIntReq, false);

    /* TX FIFO underflow request disable */
    DSPI_HAL_SetIntMode(base, kDspiTxFifoUnderflow, false);

    /* RX FIFO overflow request disable */
    DSPI_HAL_SetIntMode(base, kDspiRxFifoOverflow, false);

    /* Update DSPI status */
    dspiState->status = kStatus_DSPI_Success;

    /* Notify the event */
    OSA_EventSet(&dspiState->event, kDspiTransferDone);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveTransfer
 * Description   : Transfer data to master
 * Start transfer data to master
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_SlaveTransfer(uint32_t instance,
                                     const uint8_t *sendBuffer,
                                     uint8_t *receiveBuffer,
                                     uint32_t transferByteCount)
{
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];

    /* Check validation of parameters */
    assert(instance < SPI_INSTANCE_COUNT);

    /* Check driver initialization and idle */
    if(!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }
    if (kStatus_DSPI_Success != dspiState->status)
    {
        return dspiState->status;
    }

    /* If receive length is zero */
    if (transferByteCount == 0)
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* If both send buffer and receive buffer is null */
    if ((!sendBuffer) && (!receiveBuffer))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* If DSPI is in transmitting or receving process, return busy */
    if (dspiState->isTransferInProgress)
    {
        return kStatus_DSPI_Busy;
    }

    /* Marks function to async */
    dspiState->isSync = false;

    DSPI_DRV_SlaveStartTransfer(instance, sendBuffer, receiveBuffer, transferByteCount);
    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveTransferBlocking
 * Description   : Transfer data - blocking
 * Transfer data - blocking
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_SlaveTransferBlocking(uint32_t instance,
                                             const uint8_t *sendBuffer,
                                             uint8_t *receiveBuffer,
                                             uint32_t transferByteCount,
                                             uint32_t timeout)
{
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    osa_status_t osaStatus = kStatus_OSA_Success;
    event_flags_t setFlags = 0;
    dspi_status_t result = kStatus_DSPI_Success;

    /* Check validation of parameters */
    assert(instance < SPI_INSTANCE_COUNT);

    /* Check driver initialization and idle */
    if(!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }
    if (kStatus_DSPI_Success != dspiState->status)
    {
        return dspiState->status;
    }

    /* If receive length is zero, return success immediately without any data */
    if (transferByteCount == 0)
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* If both send buffer and receive buffer is null */
    if ((!sendBuffer) && (!receiveBuffer))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* If DSPI is in transmitting or receving process, return busy */
    if (dspiState->isTransferInProgress)
    {
        return kStatus_DSPI_Busy;
    }

    /* Marks function to sync */
    dspiState->isSync = true;

    /* Clear the event flags */
    OSA_EventClear(&dspiState->event, kDspiTransferDone);

    /* Start transfer */
    DSPI_DRV_SlaveStartTransfer(instance, sendBuffer, receiveBuffer, transferByteCount);

    /* wait transfer finished */
    do
    {
        osaStatus = OSA_EventWait(&dspiState->event, kDspiTransferDone, true, timeout, &setFlags);
    } while(osaStatus == kStatus_OSA_Idle);

    /* Check status of OSA wait event */
    switch (osaStatus)
    {
        case kStatus_OSA_Success:
            result = kStatus_DSPI_Success;
            break;
        case kStatus_OSA_Timeout:
            result = kStatus_DSPI_Timeout;
            break;
        case kStatus_OSA_Error:
        default:
            result = kStatus_DSPI_Error;
            break;
    }

    /* Abort the transfer if it is failed */
    if (result != kStatus_DSPI_Success)
    {
        DSPI_DRV_SlaveAbortTransfer(instance);
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveAbortTransfer
 * Description   : Abort tranfer
 * Abort data transfer, using after function DSPI_DRV_SlaveTransfer() to abort
 * transfering data
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_SlaveAbortTransfer(uint32_t instance)
{
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];

    /* Check instance is valid or not */
    assert(instance < SPI_INSTANCE_COUNT);

    /* Check driver is initialized */
    if (!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }

    /* Check transfer is in progress */
    if (!dspiState->isTransferInProgress)
    {
        return kStatus_DSPI_NoTransferInProgress;
    }

    /* Stop transfer */
    DSPI_DRV_SlaveCompleteTransfer(instance);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_SlaveGetTransferStatus
 * Description   : Returns whether the previous transfer has finished yet.
 * When performing an async transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can obtain the number of words that have been currently
 * transferred.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_SlaveGetTransferStatus(uint32_t instance, uint32_t * framesTransferred)
{
    /* instantiate local variable of type dspi_slave_state_t and point to global state */
    dspi_slave_state_t * dspiState = (dspi_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* Fill in the bytes transferred if required */
    if (framesTransferred)
    {
        *framesTransferred = DSPI_HAL_GetTransferCount(base);
    }

    /* return success if non transferring is in progress */
    return ((dspiState->isTransferInProgress) ? kStatus_DSPI_Busy : kStatus_DSPI_Success);
}

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

