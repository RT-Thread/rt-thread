/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i2c_dma.h"
#include "fsl_flexcomm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_i2c_dma"
#endif

/*<! @brief Structure definition for i2c_master_dma_handle_t. The structure is private. */
typedef struct _i2c_master_dma_private_handle
{
    I2C_Type *base;
    i2c_master_dma_handle_t *handle;
} i2c_master_dma_private_handle_t;

/*!
 * @brief Used for conversion from `flexcomm_irq_handler_t` to `flexcomm_i2c_dma_master_irq_handler_t`
 */
typedef union i2c_dma_to_flexcomm
{
    flexcomm_i2c_dma_master_irq_handler_t i2c_dma_master_handler;
    flexcomm_irq_handler_t flexcomm_handler;
} i2c_dma_to_flexcomm_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief DMA callback for I2C master DMA driver.
 *
 * @param handle DMA handler for I2C master DMA driver
 * @param userData user param passed to the callback function
 */
static void I2C_MasterTransferCallbackDMA(dma_handle_t *handle, void *userData, bool transferDone, uint32_t intmode);

/*!
 * @brief Set up master transfer, send slave address and sub address(if any), wait until the
 * wait until address sent status return.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_dma_handle_t structure which stores the transfer state.
 * @param xfer pointer to i2c_master_transfer_t structure.
 */
static status_t I2C_InitTransferStateMachineDMA(I2C_Type *base,
                                                i2c_master_dma_handle_t *handle,
                                                i2c_master_transfer_t *xfer);

static void I2C_RunDMATransfer(I2C_Type *base, i2c_master_dma_handle_t *handle);

/*!
 * @brief Execute states until the transfer is done.
 * @param handle Master nonblocking driver handle.
 * @param[out] isDone Set to true if the transfer has completed.
 * @retval #kStatus_Success
 * @retval #kStatus_I2C_ArbitrationLost
 * @retval #kStatus_I2C_Nak
 */
static status_t I2C_RunTransferStateMachineDMA(I2C_Type *base, i2c_master_dma_handle_t *handle, bool *isDone);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief IRQ name array */
static const IRQn_Type s_i2cIRQ[] = I2C_IRQS;

/*<! Private handle only used for internally. */
static i2c_master_dma_private_handle_t s_dmaPrivateHandle[ARRAY_SIZE(s_i2cIRQ)];

/*******************************************************************************
 * Codes
 ******************************************************************************/
static status_t I2C_InitTransferStateMachineDMA(I2C_Type *base,
                                                i2c_master_dma_handle_t *handle,
                                                i2c_master_transfer_t *xfer)
{
    struct _i2c_master_transfer *transfer;

    handle->transfer = *xfer;
    transfer         = &(handle->transfer);

    handle->transferCount     = 0U;
    handle->remainingBytesDMA = 0U;
    handle->buf               = (uint8_t *)transfer->data;
    handle->remainingSubaddr  = 0U;

    if ((transfer->flags & (uint32_t)kI2C_TransferNoStartFlag) != 0U)
    {
        handle->checkAddrNack = false;
        /* Start condition shall not be ommited, switch directly to next phase */
        if (transfer->dataSize == 0U)
        {
            handle->state = (uint8_t)kStopState;
        }
        else if (handle->transfer.direction == kI2C_Write)
        {
            handle->state = (uint8_t)kTransmitDataState;
        }
        else if (handle->transfer.direction == kI2C_Read)
        {
            handle->state = (xfer->dataSize == 1U) ? (uint8_t)kReceiveLastDataState : (uint8_t)kReceiveDataState;
        }
        else
        {
            return kStatus_I2C_InvalidParameter;
        }
    }
    else
    {
        if (transfer->subaddressSize != 0U)
        {
            int i;
            uint32_t subaddress;

            if (transfer->subaddressSize > sizeof(handle->subaddrBuf))
            {
                return kStatus_I2C_InvalidParameter;
            }

            /* Prepare subaddress transmit buffer, most significant byte is stored at the lowest address */
            subaddress = xfer->subaddress;
            for (i = (int)xfer->subaddressSize - 1; i >= 0; i--)
            {
                handle->subaddrBuf[i] = (uint8_t)subaddress & 0xffU;
                subaddress >>= 8;
            }
            handle->remainingSubaddr = transfer->subaddressSize;
        }

        handle->state         = (uint8_t)kStartState;
        handle->checkAddrNack = true;
    }

    return kStatus_Success;
}

static void I2C_RunDMATransfer(I2C_Type *base, i2c_master_dma_handle_t *handle)
{
    uint32_t transfer_size;
    dma_transfer_config_t xferConfig;
    uint32_t address;
    address = (uint32_t)&base->MSTDAT;

    /* Update transfer count */
    int32_t count = handle->buf - (uint8_t *)handle->transfer.data;
    assert(count >= 0);
    handle->transferCount = (uint32_t)count;

    /* Check if there is anything to be transferred at all */
    if (handle->remainingBytesDMA == 0U)
    {
        /* No data to be transferrred, disable DMA */
        base->MSTCTL = 0;
        return;
    }

    /* Calculate transfer size */
    transfer_size = handle->remainingBytesDMA;
    if (transfer_size > (uint32_t)I2C_MAX_DMA_TRANSFER_COUNT)
    {
        transfer_size = (uint32_t)I2C_MAX_DMA_TRANSFER_COUNT;
    }

    switch (handle->transfer.direction)
    {
        case kI2C_Write:
            DMA_PrepareTransfer(&xferConfig, handle->buf, (uint32_t *)address, sizeof(uint8_t), transfer_size,
                                kDMA_MemoryToPeripheral, NULL);
            break;

        case kI2C_Read:
            DMA_PrepareTransfer(&xferConfig, (uint32_t *)address, handle->buf, sizeof(uint8_t), transfer_size,
                                kDMA_PeripheralToMemory, NULL);
            break;

        default:
            /* This should never happen */
            assert(0);
            break;
    }

    (void)DMA_SubmitTransfer(handle->dmaHandle, &xferConfig);
    DMA_StartTransfer(handle->dmaHandle);

    handle->remainingBytesDMA -= transfer_size;
    handle->buf += transfer_size;
    handle->checkAddrNack = false;
}

static status_t I2C_RunTransferStateMachineDMA(I2C_Type *base, i2c_master_dma_handle_t *handle, bool *isDone)
{
    uint32_t status;
    uint32_t master_state;
    struct _i2c_master_transfer *transfer;
    dma_transfer_config_t xferConfig;
    status_t err;
    uint32_t start_flag = 0U;
    uint32_t address;
    address = (uint32_t)&base->MSTDAT;

    transfer = &(handle->transfer);

    *isDone = false;

    status = I2C_GetStatusFlags(base);

    if ((status & (uint32_t)I2C_STAT_MSTARBLOSS_MASK) != 0U)
    {
        I2C_MasterClearStatusFlags(base, I2C_STAT_MSTARBLOSS_MASK);
        DMA_AbortTransfer(handle->dmaHandle);
        base->MSTCTL = 0;
        return kStatus_I2C_ArbitrationLost;
    }

    if ((status & (uint32_t)I2C_STAT_MSTSTSTPERR_MASK) != 0U)
    {
        I2C_MasterClearStatusFlags(base, I2C_STAT_MSTSTSTPERR_MASK);
        DMA_AbortTransfer(handle->dmaHandle);
        base->MSTCTL = 0;
        return kStatus_I2C_StartStopError;
    }

    /* Event timeout happens when the time since last bus event has been longer than the time specified by TIMEOUT
       register. eg: Start signal fails to generate, no error status is set and transfer hangs if glitch on bus happens
       before, the timeout status can be used to avoid the transfer hangs indefinitely. */
    if ((status & (uint32_t)kI2C_EventTimeoutFlag) != 0U)
    {
        I2C_ClearStatusFlags(base, (uint32_t)kI2C_EventTimeoutFlag);
        DMA_AbortTransfer(handle->dmaHandle);
        base->MSTCTL = 0;
        return kStatus_I2C_EventTimeout;
    }

    /* SCL timeout happens when the slave is holding the SCL line low and the time has been longer than the time
       specified by TIMEOUT register. */
    if ((status & (uint32_t)kI2C_SclTimeoutFlag) != 0U)
    {
        I2C_ClearStatusFlags(base, (uint32_t)kI2C_SclTimeoutFlag);
        DMA_AbortTransfer(handle->dmaHandle);
        base->MSTCTL = 0;
        return kStatus_I2C_SclLowTimeout;
    }

    if ((status & (uint32_t)I2C_STAT_MSTPENDING_MASK) == 0U)
    {
        return kStatus_I2C_Busy;
    }

    /* Get the state of the I2C module */
    master_state = (base->STAT & (uint32_t)I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;

    if ((master_state == (uint32_t)I2C_STAT_MSTCODE_NACKADR) || (master_state == (uint32_t)I2C_STAT_MSTCODE_NACKDAT))
    {
        /* Slave NACKed last byte, issue stop and return error */
        DMA_AbortTransfer(handle->dmaHandle);
        base->MSTCTL  = I2C_MSTCTL_MSTSTOP_MASK;
        handle->state = (uint8_t)kWaitForCompletionState;
        if ((master_state == (uint32_t)I2C_STAT_MSTCODE_NACKADR) || (handle->checkAddrNack == true))
        {
            return kStatus_I2C_Addr_Nak;
        }
        else
        {
            return kStatus_I2C_Nak;
        }
    }

    err = kStatus_Success;

    if (handle->state == (uint8_t)kStartState)
    {
        /* set start flag for later use */
        start_flag = I2C_MSTCTL_MSTSTART_MASK;

        if (handle->remainingSubaddr != 0U)
        {
            base->MSTDAT  = (uint32_t)transfer->slaveAddress << 1;
            handle->state = (uint8_t)kTransmitSubaddrState;
        }
        else if (transfer->direction == kI2C_Write)
        {
            base->MSTDAT = (uint32_t)transfer->slaveAddress << 1;
            if (transfer->dataSize == 0U)
            {
                /* No data to be transferred, initiate start and schedule stop */
                base->MSTCTL  = I2C_MSTCTL_MSTSTART_MASK;
                handle->state = (uint8_t)kStopState;
                return err;
            }
            handle->state = (uint8_t)kTransmitDataState;
        }
        else if ((transfer->direction == kI2C_Read) && (transfer->dataSize > 0U))
        {
            base->MSTDAT = ((uint32_t)transfer->slaveAddress << 1) | 1u;
            if (transfer->dataSize == 1U)
            {
                /* The very last byte is always received by means of SW */
                base->MSTCTL  = I2C_MSTCTL_MSTSTART_MASK;
                handle->state = (uint8_t)kReceiveLastDataState;
                return err;
            }
            handle->state = (uint8_t)kReceiveDataState;
        }
        else
        {
            handle->state = (uint8_t)kIdleState;
            err           = kStatus_I2C_UnexpectedState;
            return err;
        }
    }

    switch (handle->state)
    {
        case (uint8_t)kTransmitSubaddrState:
            if ((master_state != (uint32_t)I2C_STAT_MSTCODE_TXREADY) && (0U == start_flag))
            {
                return kStatus_I2C_UnexpectedState;
            }

            base->MSTCTL = start_flag | I2C_MSTCTL_MSTDMA_MASK;

            /* Prepare and submit DMA transfer. */
            DMA_PrepareTransfer(&xferConfig, handle->subaddrBuf, (uint32_t *)address, sizeof(uint8_t),
                                handle->remainingSubaddr, kDMA_MemoryToPeripheral, NULL);
            (void)DMA_SubmitTransfer(handle->dmaHandle, &xferConfig);
            DMA_StartTransfer(handle->dmaHandle);
            handle->remainingSubaddr = 0;
            if (transfer->dataSize != 0U)
            {
                /* There is data to be transferred, if there is write to read turnaround it is necessary to perform
                 * repeated start */
                handle->state = (transfer->direction == kI2C_Read) ? (uint8_t)kStartState : (uint8_t)kTransmitDataState;
            }
            else
            {
                /* No more data, schedule stop condition */
                handle->state = (uint8_t)kStopState;
            }
            break;

        case (uint8_t)kTransmitDataState:
            if ((master_state != (uint32_t)I2C_STAT_MSTCODE_TXREADY) && (0U == start_flag))
            {
                return kStatus_I2C_UnexpectedState;
            }

            base->MSTCTL              = start_flag | I2C_MSTCTL_MSTDMA_MASK;
            handle->remainingBytesDMA = handle->transfer.dataSize;

            I2C_RunDMATransfer(base, handle);

            /* Schedule stop condition */
            handle->state         = (uint8_t)kStopState;
            handle->checkAddrNack = false;
            break;

        case (uint8_t)kReceiveDataState:
            if ((master_state != (uint32_t)I2C_STAT_MSTCODE_RXREADY) && (0U == start_flag))
            {
                if (0U == (transfer->flags & (uint32_t)kI2C_TransferNoStartFlag))
                {
                    return kStatus_I2C_UnexpectedState;
                }
            }

            base->MSTCTL              = start_flag | I2C_MSTCTL_MSTDMA_MASK;
            handle->remainingBytesDMA = handle->transfer.dataSize - 1U;

            if ((transfer->flags & (uint32_t)kI2C_TransferNoStartFlag) != 0U)
            {
                /* Read the master data register to avoid the data be read again */
                (void)base->MSTDAT;
            }
            I2C_RunDMATransfer(base, handle);

            /* Schedule reception of last data byte */
            handle->state         = (uint8_t)kReceiveLastDataState;
            handle->checkAddrNack = false;
            break;

        case (uint8_t)kReceiveLastDataState:
            if (master_state != (uint32_t)I2C_STAT_MSTCODE_RXREADY)
            {
                return kStatus_I2C_UnexpectedState;
            }

            ((uint8_t *)transfer->data)[transfer->dataSize - 1U] = (uint8_t)base->MSTDAT;
            handle->transferCount++;

            /* No more data expected, issue NACK and STOP right away */
            if (0U == (transfer->flags & (uint32_t)kI2C_TransferNoStopFlag))
            {
                base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;
            }
            handle->state = (uint8_t)kWaitForCompletionState;
            break;

        case (uint8_t)kStopState:
            if ((transfer->flags & (uint32_t)kI2C_TransferNoStopFlag) != 0U)
            {
                /* Stop condition is omitted, we are done */
                *isDone       = true;
                handle->state = (uint8_t)kIdleState;
                break;
            }
            /* Send stop condition */
            base->MSTCTL  = I2C_MSTCTL_MSTSTOP_MASK;
            handle->state = (uint8_t)kWaitForCompletionState;
            break;

        case (uint8_t)kWaitForCompletionState:
            *isDone       = true;
            handle->state = (uint8_t)kIdleState;
            break;

        case (uint8_t)kStartState:
        case (uint8_t)kIdleState:
        default:
            /* State machine shall not be invoked again once it enters the idle state */
            err = kStatus_I2C_UnexpectedState;
            break;
    }

    return err;
}

static void I2C_MasterTransferDMAHandleIRQ(I2C_Type *base, i2c_master_dma_handle_t *handle)
{
    bool isDone;
    status_t result;

    /* Don't do anything if we don't have a valid handle. */
    if (NULL == handle)
    {
        return;
    }

    result = I2C_RunTransferStateMachineDMA(base, handle, &isDone);

    if ((result != kStatus_Success) || isDone)
    {
        /* Restore handle to idle state. */
        handle->state = (uint8_t)kIdleState;

        /* Disable internal IRQ enables. */
        I2C_DisableInterrupts(base, I2C_INTSTAT_MSTPENDING_MASK | I2C_INTSTAT_MSTARBLOSS_MASK |
                                        I2C_INTSTAT_MSTSTSTPERR_MASK | I2C_INTSTAT_EVENTTIMEOUT_MASK);

        /* Invoke callback. */
        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }
}

static void I2C_MasterTransferCallbackDMA(dma_handle_t *handle, void *userData, bool transferDone, uint32_t intmode)
{
    i2c_master_dma_private_handle_t *dmaPrivateHandle;

    /* Don't do anything if we don't have a valid handle. */
    if (NULL == handle)
    {
        return;
    }

    dmaPrivateHandle = (i2c_master_dma_private_handle_t *)userData;
    I2C_RunDMATransfer(dmaPrivateHandle->base, dmaPrivateHandle->handle);
}

/*!
 * brief Init the I2C handle which is used in transactional functions
 *
 * param base I2C peripheral base address
 * param handle pointer to i2c_master_dma_handle_t structure
 * param callback pointer to user callback function
 * param userData user param passed to the callback function
 * param dmaHandle DMA handle pointer
 */
void I2C_MasterTransferCreateHandleDMA(I2C_Type *base,
                                       i2c_master_dma_handle_t *handle,
                                       i2c_master_dma_transfer_callback_t callback,
                                       void *userData,
                                       dma_handle_t *dmaHandle)
{
    assert(handle != NULL);
    assert(dmaHandle != NULL);

    uint32_t instance;
    i2c_dma_to_flexcomm_t handler;
    handler.i2c_dma_master_handler = I2C_MasterTransferDMAHandleIRQ;

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I2C_GetInstance(base);

    /* Set the user callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    FLEXCOMM_SetIRQHandler(base, handler.flexcomm_handler, handle);

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I2C_DisableInterrupts(base, I2C_INTSTAT_MSTPENDING_MASK | I2C_INTSTAT_MSTARBLOSS_MASK |
                                    I2C_INTSTAT_MSTSTSTPERR_MASK | I2C_INTSTAT_EVENTTIMEOUT_MASK);
    (void)EnableIRQ(s_i2cIRQ[instance]);

    /* Set the handle for DMA. */
    handle->dmaHandle = dmaHandle;

    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

    DMA_SetCallback(dmaHandle, I2C_MasterTransferCallbackDMA, &s_dmaPrivateHandle[instance]);
}

/*!
 * brief Performs a master dma non-blocking transfer on the I2C bus
 *
 * param base I2C peripheral base address
 * param handle pointer to i2c_master_dma_handle_t structure
 * param xfer pointer to transfer structure of i2c_master_transfer_t
 * retval kStatus_Success Sucessully complete the data transmission.
 * retval kStatus_I2C_Busy Previous transmission still not finished.
 * retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive Nak during transfer.
 */
status_t I2C_MasterTransferDMA(I2C_Type *base, i2c_master_dma_handle_t *handle, i2c_master_transfer_t *xfer)
{
    status_t result;

    assert(handle != NULL);
    assert(xfer != NULL);
    assert(xfer->subaddressSize <= sizeof(xfer->subaddress));

    /* Return busy if another transaction is in progress. */
    if (handle->state != (uint8_t)kIdleState)
    {
        return kStatus_I2C_Busy;
    }

    /* Prepare transfer state machine. */
    result = I2C_InitTransferStateMachineDMA(base, handle, xfer);

    /* Clear error flags. */
    I2C_MasterClearStatusFlags(base, I2C_STAT_MSTARBLOSS_MASK | I2C_STAT_MSTSTSTPERR_MASK);

    /* Enable I2C internal IRQ sources */
    /* Enable arbitration lost interrupt, start/stop error interrupt and master pending interrupt.
       The master pending flag is not set during dma transfer. */
    I2C_EnableInterrupts(base, I2C_INTSTAT_MSTARBLOSS_MASK | I2C_INTSTAT_MSTSTSTPERR_MASK |
                                   I2C_INTSTAT_MSTPENDING_MASK | I2C_INTSTAT_EVENTTIMEOUT_MASK);

    return result;
}

/*!
 * brief Get master transfer status during a dma non-blocking transfer
 *
 * param base I2C peripheral base address
 * param handle pointer to i2c_master_dma_handle_t structure
 * param count Number of bytes transferred so far by the non-blocking transaction.
 */
status_t I2C_MasterTransferGetCountDMA(I2C_Type *base, i2c_master_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state == (uint8_t)kIdleState)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* There is no necessity to disable interrupts as we read a single integer value */
    *count = handle->transferCount;
    return kStatus_Success;
}

/*!
 * brief Abort a master dma non-blocking transfer in a early time
 *
 * param base I2C peripheral base address
 * param handle pointer to i2c_master_dma_handle_t structure
 */
void I2C_MasterTransferAbortDMA(I2C_Type *base, i2c_master_dma_handle_t *handle)
{
    uint32_t status;
    uint32_t master_state;

    if (handle->state != (uint8_t)kIdleState)
    {
        DMA_AbortTransfer(handle->dmaHandle);

        /* Disable DMA */
        base->MSTCTL = 0;

        /* Disable internal IRQ enables. */
        I2C_DisableInterrupts(base, I2C_INTSTAT_MSTPENDING_MASK | I2C_INTSTAT_MSTARBLOSS_MASK |
                                        I2C_INTSTAT_MSTSTSTPERR_MASK | I2C_INTSTAT_EVENTTIMEOUT_MASK);

        /* Wait until module is ready */
        do
        {
            status = I2C_GetStatusFlags(base);
        } while ((status & (uint8_t)I2C_STAT_MSTPENDING_MASK) == 0U);

        /* Clear controller state. */
        I2C_MasterClearStatusFlags(base, I2C_STAT_MSTARBLOSS_MASK | I2C_STAT_MSTSTSTPERR_MASK);

        /* Get the state of the I2C module */
        master_state = (base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;

        if (master_state != (uint32_t)I2C_STAT_MSTCODE_IDLE)
        {
            /* Send a stop command to finalize the transfer. */
            base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;

            /* Wait until module is ready */
            do
            {
                status = I2C_GetStatusFlags(base);
            } while ((status & (uint32_t)I2C_STAT_MSTPENDING_MASK) == 0U);

            /* Clear controller state. */
            I2C_MasterClearStatusFlags(base, I2C_STAT_MSTARBLOSS_MASK | I2C_STAT_MSTSTSTPERR_MASK);
        }

        /* Reset the state to idle. */
        handle->state = (uint8_t)kIdleState;
    }
}
