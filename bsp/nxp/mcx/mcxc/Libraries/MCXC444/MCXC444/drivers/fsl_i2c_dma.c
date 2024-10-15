/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i2c_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.i2c_dma"
#endif

/*<! @brief Structure definition for i2c_master_dma_handle_t. The structure is private. */
typedef struct _i2c_master_dma_private_handle
{
    I2C_Type *base;
    i2c_master_dma_handle_t *handle;
} i2c_master_dma_private_handle_t;

/*! @brief i2c master DMA transfer state. */
enum _i2c_master_dma_transfer_states
{
    kIdleState         = 0x0U, /*!< I2C bus idle. */
    kTransferDataState = 0x1U, /*!< 7-bit address check state. */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief DMA callback for I2C master DMA driver.
 *
 * @param handle DMA handler for I2C master DMA driver
 * @param userData user param passed to the callback function
 */
static void I2C_MasterTransferCallbackDMA(dma_handle_t *handle, void *userData);

/*!
 * @brief Check and clear status operation.
 *
 * @param base I2C peripheral base address.
 * @param status current i2c hardware status
 * @retval kStatus_Success No error found.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStatus_I2C_Nak Received Nak error.
 */
static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status);

/*!
 * @brief DMA config for I2C master driver.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_dma_handle_t structure which stores the transfer state.
 */
static void I2C_MasterTransferDMAConfig(I2C_Type *base, i2c_master_dma_handle_t *handle);

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

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*<! Private handle only used for internally. */
static i2c_master_dma_private_handle_t s_dmaPrivateHandle[FSL_FEATURE_SOC_I2C_COUNT];

/*******************************************************************************
 * Codes
 ******************************************************************************/

static void I2C_MasterTransferCallbackDMA(dma_handle_t *handle, void *userData)
{
    i2c_master_dma_private_handle_t *i2cPrivateHandle = (i2c_master_dma_private_handle_t *)userData;
    status_t result                                   = kStatus_Success;
    uint32_t tmpsize                                  = (uint32_t)i2cPrivateHandle->handle->transfer.dataSize;
    uint8_t tmpdata;

    /* Disable DMA. */
    I2C_EnableDMA(i2cPrivateHandle->base, false);

    /* Send stop if kI2C_TransferNoStop flag is not asserted. */
    if (0U == (i2cPrivateHandle->handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag))
    {
        if (i2cPrivateHandle->handle->transfer.direction == kI2C_Read)
        {
            /* Change to send NAK at the last byte. */
            i2cPrivateHandle->base->C1 |= I2C_C1_TXAK_MASK;

            /* Wait the last data to be received. */
            while (0U == (i2cPrivateHandle->base->S & (uint8_t)kI2C_TransferCompleteFlag))
            {
            }

            /* Send stop signal. */
            result = I2C_MasterStop(i2cPrivateHandle->base);

            /* Read the last data byte. */
            tmpdata                                                   = i2cPrivateHandle->base->D;
            *(i2cPrivateHandle->handle->transfer.data + tmpsize - 1U) = tmpdata;
        }
        else
        {
            /* Wait the last data to be sent. */
            while (0U == (i2cPrivateHandle->base->S & (uint8_t)kI2C_TransferCompleteFlag))
            {
            }

            /* Send stop signal. */
            result = I2C_MasterStop(i2cPrivateHandle->base);
        }
    }
    else
    {
        if (i2cPrivateHandle->handle->transfer.direction == kI2C_Read)
        {
            /* Change to send NAK at the last byte. */
            i2cPrivateHandle->base->C1 |= I2C_C1_TXAK_MASK;

            /* Wait the last data to be received. */
            while (0U == (i2cPrivateHandle->base->S & (uint8_t)kI2C_TransferCompleteFlag))
            {
            }

            /* Change direction to send. */
            i2cPrivateHandle->base->C1 |= I2C_C1_TX_MASK;

            /* Read the last data byte. */
            tmpdata                                                   = i2cPrivateHandle->base->D;
            *(i2cPrivateHandle->handle->transfer.data + tmpsize - 1U) = tmpdata;
        }
    }

    i2cPrivateHandle->handle->state = (uint8_t)kIdleState;

    if (i2cPrivateHandle->handle->completionCallback != NULL)
    {
        i2cPrivateHandle->handle->completionCallback(i2cPrivateHandle->base, i2cPrivateHandle->handle, result,
                                                     i2cPrivateHandle->handle->userData);
    }
}

static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check arbitration lost. */
    if ((status & (uint32_t)kI2C_ArbitrationLostFlag) != 0U)
    {
        /* Clear arbitration lost flag. */
        base->S = (uint8_t)kI2C_ArbitrationLostFlag;
        result  = kStatus_I2C_ArbitrationLost;
    }
    /* Check NAK */
    else if ((status & (uint32_t)kI2C_ReceiveNakFlag) != 0U)
    {
        result = kStatus_I2C_Nak;
    }
    else
    {
        /* Avoid MISRA 2012 rule 15.7 */
    }

    return result;
}

static status_t I2C_InitTransferStateMachineDMA(I2C_Type *base,
                                                i2c_master_dma_handle_t *handle,
                                                i2c_master_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    /* Set up transfer first. */
    i2c_direction_t direction = xfer->direction;
    status_t result           = kStatus_Success;
#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    if (handle->state != (uint8_t)kIdleState)
    {
        return kStatus_I2C_Busy;
    }
    else
    {
        /* Init the handle member. */
        handle->transfer = *xfer;

        /* Save total transfer size. */
        handle->transferSize = xfer->dataSize;

        handle->state = (uint8_t)kTransferDataState;

        /* Clear all status before transfer. */
        I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

        /* Change to send write address when it's a read operation with command. */
        if ((xfer->subaddressSize > 0U) && (xfer->direction == kI2C_Read))
        {
            direction = kI2C_Write;
        }

        /* If repeated start is requested, send repeated start. */
        if ((handle->transfer.flags & (uint32_t)kI2C_TransferRepeatedStartFlag) != 0U)
        {
            result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, direction);
        }
        else /* For normal transfer, send start. */
        {
            result = I2C_MasterStart(base, handle->transfer.slaveAddress, direction);
        }

        if (result != kStatus_Success)
        {
            return result;
        }

#if I2C_RETRY_TIMES
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != --waitTimes))
        {
        }
        if (waitTimes == 0U)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif

        /* Check if there's transfer error. */
        result = I2C_CheckAndClearError(base, base->S);

        /* Return if error. */
        if (result != kStatus_Success)
        {
            if (result == kStatus_I2C_Nak)
            {
                result = kStatus_I2C_Addr_Nak;

                if (I2C_MasterStop(base) != kStatus_Success)
                {
                    result = kStatus_I2C_Timeout;
                }

                if (handle->completionCallback != NULL)
                {
                    (handle->completionCallback)(base, handle, result, handle->userData);
                }
            }

            return result;
        }

        /* Send subaddress. */
        if (handle->transfer.subaddressSize != 0U)
        {
            do
            {
                /* Clear interrupt pending flag. */
                base->S = (uint8_t)kI2C_IntPendingFlag;

                handle->transfer.subaddressSize--;
                base->D = (uint8_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));

                /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES
                waitTimes = I2C_RETRY_TIMES;
                while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != --waitTimes))
                {
                }
                if (waitTimes == 0U)
                {
                    return kStatus_I2C_Timeout;
                }
#else
                while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
                {
                }
#endif

                /* Check if there's transfer error. */
                result = I2C_CheckAndClearError(base, base->S);

                if (result != kStatus_Success)
                {
                    return result;
                }

            } while (handle->transfer.subaddressSize > 0U);

            if (handle->transfer.direction == kI2C_Read)
            {
                /* Clear pending flag. */
                base->S = (uint8_t)kI2C_IntPendingFlag;

                /* Send repeated start and slave address. */
                result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, kI2C_Read);

                if (result != kStatus_Success)
                {
                    return result;
                }

                /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES
                waitTimes = I2C_RETRY_TIMES;
                while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != --waitTimes))
                {
                }
                if (waitTimes == 0U)
                {
                    return kStatus_I2C_Timeout;
                }
#else
                while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
                {
                }
#endif

                /* Check if there's transfer error. */
                result = I2C_CheckAndClearError(base, base->S);

                if (result != kStatus_Success)
                {
                    return result;
                }
            }
        }

        /* Clear pending flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;
    }

    return result;
}

static void I2C_MasterTransferDMAConfig(I2C_Type *base, i2c_master_dma_handle_t *handle)
{
    dma_transfer_config_t transfer_config   = {0};
    dma_transfer_options_t transfer_options = kDMA_EnableInterrupt;

    if (handle->transfer.direction == kI2C_Read)
    {
        transfer_config.srcAddr             = (uint32_t)I2C_GetDataRegAddr(base);
        transfer_config.destAddr            = (uint32_t)(handle->transfer.data);
        transfer_config.transferSize        = (handle->transfer.dataSize - 1U);
        transfer_config.srcSize             = kDMA_Transfersize8bits;
        transfer_config.enableSrcIncrement  = false;
        transfer_config.destSize            = kDMA_Transfersize8bits;
        transfer_config.enableDestIncrement = true;
    }
    else
    {
        transfer_config.srcAddr             = (uint32_t)(handle->transfer.data + 1U);
        transfer_config.destAddr            = (uint32_t)I2C_GetDataRegAddr(base);
        transfer_config.transferSize        = (handle->transfer.dataSize - 1U);
        transfer_config.srcSize             = kDMA_Transfersize8bits;
        transfer_config.enableSrcIncrement  = true;
        transfer_config.destSize            = kDMA_Transfersize8bits;
        transfer_config.enableDestIncrement = false;
    }

    (void)DMA_SubmitTransfer(handle->dmaHandle, &transfer_config, (uint32_t)transfer_options);
    DMA_StartTransfer(handle->dmaHandle);
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base I2C peripheral base address
 * param handle Pointer to the i2c_master_dma_handle_t structure
 * param callback Pointer to the user callback function
 * param userData A user parameter passed to the callback function
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

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set the user callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Set the handle for DMA. */
    handle->dmaHandle = dmaHandle;

    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

    DMA_SetCallback(dmaHandle, (dma_callback)I2C_MasterTransferCallbackDMA, &s_dmaPrivateHandle[instance]);
}

/*!
 * brief Performs a master DMA non-blocking transfer on the I2C bus.
 *
 * param base I2C peripheral base address
 * param handle A pointer to the i2c_master_dma_handle_t structure
 * param xfer A pointer to the transfer structure of the i2c_master_transfer_t
 * retval kStatus_Success Successfully completes the data transmission.
 * retval kStatus_I2C_Busy A previous transmission is still not finished.
 * retval kStatus_I2C_Timeout A transfer error, waits for the signal timeout.
 * retval kStatus_I2C_ArbitrationLost A transfer error, arbitration lost.
 * retval kStataus_I2C_Nak A transfer error, receives NAK during transfer.
 */
status_t I2C_MasterTransferDMA(I2C_Type *base, i2c_master_dma_handle_t *handle, i2c_master_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    status_t result;
    uint8_t tmpReg;
    uint8_t tmpdata;

    /* Disable dma transfer. */
    I2C_EnableDMA(base, false);

    /* Send address and command buffer(if there is), until senddata phase or receive data phase. */
    result = I2C_InitTransferStateMachineDMA(base, handle, xfer);

    if (result != kStatus_Success)
    {
        /* Send stop if received Nak. */
        if (result == kStatus_I2C_Nak)
        {
            if (I2C_MasterStop(base) != kStatus_Success)
            {
                result = kStatus_I2C_Timeout;
            }
        }

        /* Reset the state to idle state. */
        handle->state = (uint8_t)kIdleState;

        return result;
    }

    /* Configure dma transfer. */
    /* For i2c send, need to send 1 byte first to trigger the dma, for i2c read,
    need to send stop before reading the last byte, so the dma transfer size should
    be (xSize - 1). */
    if (handle->transfer.dataSize > 1U)
    {
        I2C_MasterTransferDMAConfig(base, handle);
        if (handle->transfer.direction == kI2C_Read)
        {
            /* Change direction for receive. */
            base->C1 &= ~((uint8_t)I2C_C1_TX_MASK | (uint8_t)I2C_C1_TXAK_MASK);

            /* Read dummy to release the bus. */
            (void)base->D;

            /* Enabe dma transfer. */
            I2C_EnableDMA(base, true);
        }
        else
        {
            /* Enabe dma transfer. */
            I2C_EnableDMA(base, true);

            /* Send the first data. */
            base->D = *handle->transfer.data;
        }
    }
    else /* If transfer size is 1, use polling method. */
    {
        if (handle->transfer.direction == kI2C_Read)
        {
            tmpReg = base->C1;

            /* Change direction to Rx. */
            tmpReg &= ~(uint8_t)I2C_C1_TX_MASK;

            /* Configure send NAK */
            tmpReg |= I2C_C1_TXAK_MASK;

            base->C1 = tmpReg;

            /* Read dummy to release the bus. */
            (void)base->D;
        }
        else
        {
            base->D = *handle->transfer.data;
        }

        /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES
        uint32_t waitTimes = I2C_RETRY_TIMES;
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != --waitTimes))
        {
        }
        if (waitTimes == 0U)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif

        /* Clear pending flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Send stop if kI2C_TransferNoStop flag is not asserted. */
        if (0U == (handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag))
        {
            result = I2C_MasterStop(base);
        }
        else
        {
            /* Change direction to send. */
            base->C1 |= I2C_C1_TX_MASK;
        }

        /* Read the last byte of data. */
        if (handle->transfer.direction == kI2C_Read)
        {
            tmpdata                = base->D;
            *handle->transfer.data = tmpdata;
        }

        /* Reset the state to idle. */
        handle->state = (uint8_t)kIdleState;

        /* Call the callback function after the function has completed. */
        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }

    return result;
}

/*!
 * brief Gets a master transfer status during a DMA non-blocking transfer.
 *
 * param base I2C peripheral base address
 * param handle A pointer to the i2c_master_dma_handle_t structure
 * param count A number of bytes transferred so far by the non-blocking transaction.
 */
status_t I2C_MasterTransferGetCountDMA(I2C_Type *base, i2c_master_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    if ((uint8_t)kIdleState != handle->state)
    {
        *count = (handle->transferSize - DMA_GetRemainingBytes(handle->dmaHandle->base, handle->dmaHandle->channel));
    }
    else
    {
        *count = handle->transferSize;
    }

    return kStatus_Success;
}

/*!
 * brief Aborts a master DMA non-blocking transfer early.
 *
 * param base I2C peripheral base address
 * param handle A pointer to the i2c_master_dma_handle_t structure.
 */
void I2C_MasterTransferAbortDMA(I2C_Type *base, i2c_master_dma_handle_t *handle)
{
    DMA_AbortTransfer(handle->dmaHandle);

    /* Disable dma transfer. */
    I2C_EnableDMA(base, false);

    /* Reset the state to idle. */
    handle->state = (uint8_t)kIdleState;
}
