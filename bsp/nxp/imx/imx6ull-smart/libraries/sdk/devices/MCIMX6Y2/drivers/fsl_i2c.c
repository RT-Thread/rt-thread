/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
#include "fsl_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief i2c transfer state. */
enum _i2c_transfer_states
{
    kIdleState = 0x0U,             /*!< I2C bus idle. */
    kCheckAddressState = 0x1U,     /*!< 7-bit address check state. */
    kSendCommandState = 0x2U,      /*!< Send command byte phase. */
    kSendDataState = 0x3U,         /*!< Send data transfer phase. */
    kReceiveDataBeginState = 0x4U, /*!< Receive data transfer phase begin. */
    kReceiveDataState = 0x5U,      /*!< Receive data transfer phase. */
};

/*! @brief Common sets of flags used by the driver. */
enum _i2c_flag_constants
{
    kClearFlags = kI2C_ArbitrationLostFlag | kI2C_IntPendingFlag,
    kIrqFlags = kI2C_GlobalInterruptEnable,
};

/*! @brief Typedef for interrupt handler. */
typedef void (*i2c_isr_t)(I2C_Type *base, void *i2cHandle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for I2C module.
 *
 * @param base I2C peripheral base address.
 */
uint32_t I2C_GetInstance(I2C_Type *base);

/*!
 * @brief Set up master transfer, send slave address and decide the initial
 * transfer state.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * @param xfer pointer to i2c_master_transfer_t structure.
 */
static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer);

/*!
 * @brief Check and clear status operation.
 *
 * @param base I2C peripheral base address.
 * @param status current i2c hardware status.
 * @retval kStatus_Success No error found.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStatus_I2C_Nak Received Nak error.
 */
static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status);

/*!
 * @brief Master run transfer state machine to perform a byte of transfer.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state
 * @param isDone input param to get whether the thing is done, true is done
 * @retval kStatus_Success No error found.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStatus_I2C_Nak Received Nak error.
 * @retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 */
static status_t I2C_MasterTransferRunStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone);

/*!
 * @brief I2C common interrupt handler.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state
 */
static void I2C_TransferCommonIRQHandler(I2C_Type *base, void *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief SCL clock divider used to calculate baudrate. */
static const uint16_t s_i2cDividerTable[] = {
    30,  32,  36,  42,  48,  52,  60,  72,  80,   88,   104,  128,  144,  160,  192,  240,
    288, 320, 384, 480, 576, 640, 768, 960, 1152, 1280, 1536, 1920, 2304, 2560, 3072, 3840,
    22,  24,  26,  28,  32,  36,  40,  44,  48,   56,   64,   72,   80,   96,   112,  128,
    160, 192, 224, 256, 320, 384, 448, 512, 640,  768,  896,  1024, 1280, 1536, 1792, 2048};

/*! @brief Pointers to i2c bases for each instance. */
static I2C_Type *const s_i2cBases[] = I2C_BASE_PTRS;

/*! @brief Pointers to i2c IRQ number for each instance. */
static const IRQn_Type s_i2cIrqs[] = I2C_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to i2c clocks for each instance. */
static const clock_ip_name_t s_i2cClocks[] = I2C_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to i2c handles for each instance. */
static void *s_i2cHandle[ARRAY_SIZE(s_i2cBases)] = {NULL};

/*! @brief Pointer to master IRQ handler for each instance. */
static i2c_isr_t s_i2cMasterIsr;

/*! @brief Pointer to slave IRQ handler for each instance. */
static i2c_isr_t s_i2cSlaveIsr;

/*******************************************************************************
 * Codes
 ******************************************************************************/

uint32_t I2C_GetInstance(I2C_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_i2cBases); instance++)
    {
        if (s_i2cBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_i2cBases));

    return instance;
}

static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    status_t result = kStatus_Success;
    i2c_direction_t direction = xfer->direction;

    /* Initialize the handle transfer information. */
    handle->transfer = *xfer;

    /* Save total transfer size. */
    handle->transferSize = xfer->dataSize;

    /* Initial transfer state. */
    if (handle->transfer.subaddressSize > 0)
    {
        if (xfer->direction == kI2C_Read)
        {
            direction = kI2C_Write;
        }
    }

    handle->state = kCheckAddressState;

    /* Clear all status before transfer. */
    I2C_MasterClearStatusFlags(base, kClearFlags);

    /* If repeated start is requested, send repeated start. */
    if (handle->transfer.flags & kI2C_TransferRepeatedStartFlag)
    {
        result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, direction);
    }
    else /* For normal transfer, send start. */
    {
        result = I2C_MasterStart(base, handle->transfer.slaveAddress, direction);
    }

    return result;
}

static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check arbitration lost. */
    if (status & kI2C_ArbitrationLostFlag)
    {
        /* Clear arbitration lost flag. */
        base->I2SR &= (uint8_t)(~kI2C_ArbitrationLostFlag);

        /* Reset I2C controller*/
        base->I2CR &= ~I2C_I2CR_IEN_MASK;
        base->I2CR |= I2C_I2CR_IEN_MASK;

        result = kStatus_I2C_ArbitrationLost;
    }
    /* Check NAK */
    else if (status & kI2C_ReceiveNakFlag)
    {
        result = kStatus_I2C_Nak;
    }
    else
    {
    }

    return result;
}

static status_t I2C_MasterTransferRunStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone)
{
    status_t result = kStatus_Success;
    uint32_t statusFlags = base->I2SR;
    *isDone = false;
    volatile uint8_t dummy = 0;
    bool ignoreNak = ((handle->state == kSendDataState) && (handle->transfer.dataSize == 0U)) ||
                     ((handle->state == kReceiveDataState) && (handle->transfer.dataSize == 1U));

    /* Add this to avoid build warning. */
    dummy++;

    /* Check & clear error flags. */
    result = I2C_CheckAndClearError(base, statusFlags);

    /* Ignore Nak when it's appeared for last byte. */
    if ((result == kStatus_I2C_Nak) && ignoreNak)
    {
        result = kStatus_Success;
    }
    /* Handle Check address state to check the slave address is Acked in slave
       probe application. */
    if (handle->state == kCheckAddressState)
    {
        if (statusFlags & kI2C_ReceiveNakFlag)
        {
            result = kStatus_I2C_Addr_Nak;
        }
        else
        {
            if (handle->transfer.subaddressSize > 0)
            {
                handle->state = kSendCommandState;
            }
            else
            {
                if (handle->transfer.direction == kI2C_Write)
                {
                    /* Next state, send data. */
                    handle->state = kSendDataState;
                }
                else
                {
                    /* Next state, receive data begin. */
                    handle->state = kReceiveDataBeginState;
                }
            }
        }
    }

    if (result)
    {
        return result;
    }

    /* Run state machine. */
    switch (handle->state)
    {
        /* Send I2C command. */
        case kSendCommandState:
            if (handle->transfer.subaddressSize)
            {
                handle->transfer.subaddressSize--;
                base->I2DR = ((handle->transfer.subaddress) >> (8 * handle->transfer.subaddressSize));
            }
            else
            {
                if (handle->transfer.direction == kI2C_Write)
                {
                    /* Next state, send data. */
                    handle->state = kSendDataState;

                    /* Send first byte of data. */
                    if (handle->transfer.dataSize > 0)
                    {
                        base->I2DR = *handle->transfer.data;
                        handle->transfer.data++;
                        handle->transfer.dataSize--;
                    }
                }
                else
                {
                    /* Send repeated start and slave address. */
                    result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, kI2C_Read);

                    /* Next state, receive data begin. */
                    handle->state = kReceiveDataBeginState;
                }
            }
            break;

        /* Send I2C data. */
        case kSendDataState:
            /* Send one byte of data. */
            if (handle->transfer.dataSize > 0)
            {
                base->I2DR = *handle->transfer.data;
                handle->transfer.data++;
                handle->transfer.dataSize--;
            }
            else
            {
                *isDone = true;
            }
            break;

        /* Start I2C data receive. */
        case kReceiveDataBeginState:
            base->I2CR &= ~(I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

            /* Send nak at the last receive byte. */
            if (handle->transfer.dataSize == 1)
            {
                base->I2CR |= I2C_I2CR_TXAK_MASK;
            }

            /* Read dummy to release the bus. */
            dummy = base->I2DR;

            /* Next state, receive data. */
            handle->state = kReceiveDataState;
            break;

        /* Receive I2C data. */
        case kReceiveDataState:
            /* Receive one byte of data. */
            if (handle->transfer.dataSize--)
            {
                if (handle->transfer.dataSize == 0)
                {
                    *isDone = true;

                    /* Send stop if kI2C_TransferNoStop is not asserted. */
                    if (!(handle->transfer.flags & kI2C_TransferNoStopFlag))
                    {
                        result = I2C_MasterStop(base);
                    }
                    else
                    {
                        base->I2CR |= I2C_I2CR_MTX_MASK;
                    }
                }

                /* Send NAK at the last receive byte. */
                if (handle->transfer.dataSize == 1)
                {
                    base->I2CR |= I2C_I2CR_TXAK_MASK;
                }
                /* Read the data byte into the transfer buffer. */
                *handle->transfer.data = base->I2DR;
                handle->transfer.data++;
            }
            break;

        default:
            break;
    }

    return result;
}

static void I2C_TransferCommonIRQHandler(I2C_Type *base, void *handle)
{
    /* Check if master interrupt. */
    if ((base->I2SR & kI2C_ArbitrationLostFlag) || (base->I2CR & I2C_I2CR_MSTA_MASK))
    {
        s_i2cMasterIsr(base, handle);
    }
    else
    {
        s_i2cSlaveIsr(base, handle);
    }
    __DSB();
}

void I2C_MasterInit(I2C_Type *base, const i2c_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert(masterConfig && srcClock_Hz);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable I2C clock. */
    CLOCK_EnableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable I2C prior to configuring it. */
    base->I2CR &= ~(I2C_I2CR_IEN_MASK);

    /* Clear all flags. */
    I2C_MasterClearStatusFlags(base, kClearFlags);

    /* Configure baud rate. */
    I2C_MasterSetBaudRate(base, masterConfig->baudRate_Bps, srcClock_Hz);

    /* Enable the I2C peripheral based on the configuration. */
    base->I2CR = I2C_I2CR_IEN(masterConfig->enableMaster);
}

void I2C_MasterDeinit(I2C_Type *base)
{
    /* Disable I2C module. */
    I2C_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable I2C clock. */
    CLOCK_DisableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void I2C_MasterGetDefaultConfig(i2c_master_config_t *masterConfig)
{
    assert(masterConfig);

    /* Default baud rate at 100kbps. */
    masterConfig->baudRate_Bps = 100000U;

    /* Enable the I2C peripheral. */
    masterConfig->enableMaster = true;
}

void I2C_EnableInterrupts(I2C_Type *base, uint32_t mask)
{
    if (mask & kI2C_GlobalInterruptEnable)
    {
        base->I2CR |= I2C_I2CR_IIEN_MASK;
    }
}

void I2C_DisableInterrupts(I2C_Type *base, uint32_t mask)
{
    if (mask & kI2C_GlobalInterruptEnable)
    {
        base->I2CR &= ~I2C_I2CR_IIEN_MASK;
    }
}

void I2C_MasterSetBaudRate(I2C_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t computedRate;
    uint32_t absError;
    uint32_t bestError = UINT32_MAX;
    uint32_t bestIcr = 0u;
    uint8_t i;

    /* Scan table to find best match. */
    for (i = 0u; i < sizeof(s_i2cDividerTable) / sizeof(s_i2cDividerTable[0]); ++i)
    {
        computedRate = srcClock_Hz / s_i2cDividerTable[i];
        absError = baudRate_Bps > computedRate ? (baudRate_Bps - computedRate) : (computedRate - baudRate_Bps);

        if (absError < bestError)
        {
            bestIcr = i;
            bestError = absError;

            /* If the error is 0, then we can stop searching because we won't find a better match. */
            if (absError == 0)
            {
                break;
            }
        }
    }

    /* Set frequency register based on best settings. */
    base->IFDR = I2C_IFDR_IC(bestIcr);
}

status_t I2C_MasterStart(I2C_Type *base, uint8_t address, i2c_direction_t direction)
{
    status_t result = kStatus_Success;
    uint32_t statusFlags = I2C_MasterGetStatusFlags(base);

    /* Return an error if the bus is already in use. */
    if (statusFlags & kI2C_BusBusyFlag)
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* Send the START signal. */
        base->I2CR |= I2C_I2CR_MSTA_MASK | I2C_I2CR_MTX_MASK;

        base->I2DR = (((uint32_t)address) << 1U | ((direction == kI2C_Read) ? 1U : 0U));
    }

    return result;
}

status_t I2C_MasterRepeatedStart(I2C_Type *base, uint8_t address, i2c_direction_t direction)
{
    status_t result = kStatus_Success;
    uint32_t statusFlags = I2C_MasterGetStatusFlags(base);

    /* Return an error if the bus is already in use, but not by us. */
    if ((statusFlags & kI2C_BusBusyFlag) && ((base->I2CR & I2C_I2CR_MSTA_MASK) == 0))
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* We are already in a transfer, so send a repeated start. */
        base->I2CR |= I2C_I2CR_RSTA_MASK | I2C_I2CR_MTX_MASK;

        base->I2DR = (((uint32_t)address) << 1U | ((direction == kI2C_Read) ? 1U : 0U));
    }

    return result;
}

status_t I2C_MasterStop(I2C_Type *base)
{
    status_t result = kStatus_Success;
    uint16_t timeout = UINT16_MAX;

    /* Issue the STOP command on the bus. */
    base->I2CR &= ~(I2C_I2CR_MSTA_MASK | I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

    /* Wait until data transfer complete. */
    while ((base->I2SR & kI2C_BusBusyFlag) && (--timeout))
    {
    }

    if (timeout == 0)
    {
        result = kStatus_I2C_Timeout;
    }

    return result;
}

status_t I2C_MasterWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize, uint32_t flags)
{
    status_t result = kStatus_Success;
    uint8_t statusFlags = 0;

    /* Wait until the data register is ready for transmit. */
    while (!(base->I2SR & kI2C_TransferCompleteFlag))
    {
    }

    /* Clear the IICIF flag. */
    base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to transmit data. */
    base->I2CR |= I2C_I2CR_MTX_MASK;

    while (txSize--)
    {
        /* Send a byte of data. */
        base->I2DR = *txBuff++;

        /* Wait until data transfer complete. */
        while (!(base->I2SR & kI2C_IntPendingFlag))
        {
        }

        statusFlags = base->I2SR;

        /* Clear the IICIF flag. */
        base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

        /* Check if arbitration lost or no acknowledgement (NAK), return failure status. */
        if (statusFlags & kI2C_ArbitrationLostFlag)
        {
            base->I2SR = kI2C_ArbitrationLostFlag;
            result = kStatus_I2C_ArbitrationLost;
        }

        if ((statusFlags & kI2C_ReceiveNakFlag) && txSize)
        {
            base->I2SR = kI2C_ReceiveNakFlag;
            result = kStatus_I2C_Nak;
        }

        if (result != kStatus_Success)
        {
            /* Breaking out of the send loop. */
            break;
        }
    }

    if (((result == kStatus_Success) && (!(flags & kI2C_TransferNoStopFlag))) || (result == kStatus_I2C_Nak))
    {
        /* Clear the IICIF flag. */
        base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

        /* Send stop. */
        result = I2C_MasterStop(base);
    }

    return result;
}

status_t I2C_MasterReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize, uint32_t flags)
{
    status_t result = kStatus_Success;
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    /* Wait until the data register is ready for transmit. */
    while (!(base->I2SR & kI2C_TransferCompleteFlag))
    {
    }

    /* Clear the IICIF flag. */
    base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to receive data. */
    base->I2CR &= ~(I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

    /* If rxSize equals 1, configure to send NAK. */
    if (rxSize == 1)
    {
        /* Issue NACK on read. */
        base->I2CR |= I2C_I2CR_TXAK_MASK;
    }

    /* Do dummy read. */
    dummy = base->I2DR;

    while ((rxSize--))
    {
        /* Wait until data transfer complete. */
        while (!(base->I2SR & kI2C_IntPendingFlag))
        {
        }

        /* Clear the IICIF flag. */
        base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

        /* Single byte use case. */
        if (rxSize == 0)
        {
            if (!(flags & kI2C_TransferNoStopFlag))
            {
                /* Issue STOP command before reading last byte. */
                result = I2C_MasterStop(base);
            }
            else
            {
                /* Change direction to Tx to avoid extra clocks. */
                base->I2CR |= I2C_I2CR_MTX_MASK;
            }
        }

        if (rxSize == 1)
        {
            /* Issue NACK on read. */
            base->I2CR |= I2C_I2CR_TXAK_MASK;
        }

        /* Read from the data register. */
        *rxBuff++ = base->I2DR;
    }

    return result;
}

status_t I2C_MasterTransferBlocking(I2C_Type *base, i2c_master_transfer_t *xfer)
{
    assert(xfer);

    i2c_direction_t direction = xfer->direction;
    status_t result = kStatus_Success;

    /* Clear all status before transfer. */
    I2C_MasterClearStatusFlags(base, kClearFlags);

    /* Wait until ready to complete. */
    while (!(base->I2SR & kI2C_TransferCompleteFlag))
    {
    }

    /* Change to send write address when it's a read operation with command. */
    if ((xfer->subaddressSize > 0) && (xfer->direction == kI2C_Read))
    {
        direction = kI2C_Write;
    }

    /* If repeated start is requested, send repeated start. */
    if (xfer->flags & kI2C_TransferRepeatedStartFlag)
    {
        result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, direction);
    }
    else /* For normal transfer, send start. */
    {
        result = I2C_MasterStart(base, xfer->slaveAddress, direction);
    }

    /* Return if error. */
    if (result)
    {
        return result;
    }

    while (!(base->I2SR & kI2C_IntPendingFlag))
    {
    }

    /* Check if there's transfer error. */
    result = I2C_CheckAndClearError(base, base->I2SR);

    /* Return if error. */
    if (result)
    {
        if (result == kStatus_I2C_Nak)
        {
            result = kStatus_I2C_Addr_Nak;

            I2C_MasterStop(base);
        }

        return result;
    }

    /* Send subaddress. */
    if (xfer->subaddressSize)
    {
        do
        {
            /* Clear interrupt pending flag. */
            base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

            xfer->subaddressSize--;
            base->I2DR = ((xfer->subaddress) >> (8 * xfer->subaddressSize));

            /* Wait until data transfer complete. */
            while (!(base->I2SR & kI2C_IntPendingFlag))
            {
            }

            /* Check if there's transfer error. */
            result = I2C_CheckAndClearError(base, base->I2SR);

            if (result)
            {
                if (result == kStatus_I2C_Nak)
                {
                    I2C_MasterStop(base);
                }

                return result;
            }

        } while ((xfer->subaddressSize > 0) && (result == kStatus_Success));

        if (xfer->direction == kI2C_Read)
        {
            /* Clear pending flag. */
            base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

            /* Send repeated start and slave address. */
            result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, kI2C_Read);

            /* Return if error. */
            if (result)
            {
                return result;
            }

            /* Wait until data transfer complete. */
            while (!(base->I2SR & kI2C_IntPendingFlag))
            {
            }

            /* Check if there's transfer error. */
            result = I2C_CheckAndClearError(base, base->I2SR);

            if (result)
            {
                if (result == kStatus_I2C_Nak)
                {
                    result = kStatus_I2C_Addr_Nak;

                    I2C_MasterStop(base);
                }

                return result;
            }
        }
    }

    /* Transmit data. */
    if ((xfer->direction == kI2C_Write) && (xfer->dataSize > 0))
    {
        /* Send Data. */
        result = I2C_MasterWriteBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
    }

    /* Receive Data. */
    if ((xfer->direction == kI2C_Read) && (xfer->dataSize > 0))
    {
        result = I2C_MasterReadBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
    }

    return result;
}

void I2C_MasterTransferCreateHandle(I2C_Type *base,
                                    i2c_master_handle_t *handle,
                                    i2c_master_transfer_callback_t callback,
                                    void *userData)
{
    assert(handle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->completionCallback = callback;
    handle->userData = userData;

    /* Save the context in global variables to support the double weak mechanism. */
    s_i2cHandle[instance] = handle;

    /* Save master interrupt handler. */
    s_i2cMasterIsr = I2C_MasterTransferHandleIRQ;

    /* Enable NVIC interrupt. */
    EnableIRQ(s_i2cIrqs[instance]);
}

status_t I2C_MasterTransferNonBlocking(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    assert(handle);
    assert(xfer);

    status_t result = kStatus_Success;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (handle->state != kIdleState)
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* Start up the master transfer state machine. */
        result = I2C_InitTransferStateMachine(base, handle, xfer);

        if (result == kStatus_Success)
        {
            /* Enable the I2C interrupts. */
            I2C_EnableInterrupts(base, kI2C_GlobalInterruptEnable);
        }
    }

    return result;
}

void I2C_MasterTransferAbort(I2C_Type *base, i2c_master_handle_t *handle)
{
    assert(handle);

    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    /* Disable interrupt. */
    I2C_DisableInterrupts(base, kI2C_GlobalInterruptEnable);

    /* Reset the state to idle. */
    handle->state = kIdleState;

    /* Send STOP signal. */
    if (handle->transfer.direction == kI2C_Read)
    {
        base->I2CR |= I2C_I2CR_TXAK_MASK;
        while (!(base->I2SR & kI2C_IntPendingFlag))
        {
        }
        base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

        base->I2CR &= ~(I2C_I2CR_MSTA_MASK | I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);
        dummy = base->I2DR;
    }
    else
    {
        while (!(base->I2SR & kI2C_IntPendingFlag))
        {
        }
        base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;
        base->I2CR &= ~(I2C_I2CR_MSTA_MASK | I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);
    }
}

status_t I2C_MasterTransferGetCount(I2C_Type *base, i2c_master_handle_t *handle, size_t *count)
{
    assert(handle);

    if (!count)
    {
        return kStatus_InvalidArgument;
    }

    *count = handle->transferSize - handle->transfer.dataSize;

    return kStatus_Success;
}

void I2C_MasterTransferHandleIRQ(I2C_Type *base, void *i2cHandle)
{
    assert(i2cHandle);

    i2c_master_handle_t *handle = (i2c_master_handle_t *)i2cHandle;
    status_t result = kStatus_Success;
    bool isDone;

    /* Clear the interrupt flag. */
    base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

    /* Check transfer complete flag. */
    result = I2C_MasterTransferRunStateMachine(base, handle, &isDone);

    if (isDone || result)
    {
        /* Send stop command if transfer done or received Nak. */
        if ((!(handle->transfer.flags & kI2C_TransferNoStopFlag)) || (result == kStatus_I2C_Nak) ||
            (result == kStatus_I2C_Addr_Nak))
        {
            /* Ensure stop command is a need. */
            if ((base->I2CR & I2C_I2CR_MSTA_MASK))
            {
                if (I2C_MasterStop(base) != kStatus_Success)
                {
                    result = kStatus_I2C_Timeout;
                }
            }
        }

        /* Restore handle to idle state. */
        handle->state = kIdleState;

        /* Disable interrupt. */
        I2C_DisableInterrupts(base, kI2C_GlobalInterruptEnable);

        /* Call the callback function after the function has completed. */
        if (handle->completionCallback)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }
}

void I2C_SlaveInit(I2C_Type *base, const i2c_slave_config_t *slaveConfig)
{
    assert(slaveConfig);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable I2C clock. */
    CLOCK_EnableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    base->IADR = ((uint32_t)(slaveConfig->slaveAddress)) << 1U;
    base->I2CR = I2C_I2CR_IEN(slaveConfig->enableSlave);
}

void I2C_SlaveDeinit(I2C_Type *base)
{
    /* Disable I2C module. */
    I2C_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable I2C clock. */
    CLOCK_DisableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void I2C_SlaveGetDefaultConfig(i2c_slave_config_t *slaveConfig)
{
    assert(slaveConfig);

    /* Enable the I2C peripheral. */
    slaveConfig->enableSlave = true;
}

status_t I2C_SlaveWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize)
{
    status_t result = kStatus_Success;
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    /* Wait for address match flag. */
    while (!(base->I2SR & kI2C_AddressMatchFlag))
    {
    }

    /* Read dummy to release bus. */
    dummy = base->I2DR;

    result = I2C_MasterWriteBlocking(base, txBuff, txSize, kI2C_TransferDefaultFlag);

    /* Switch to receive mode. */
    base->I2CR &= ~(I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

    /* Read dummy to release bus. */
    dummy = base->I2DR;

    return result;
}

void I2C_SlaveReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize)
{
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    /* Wait for address match and int pending flag. */
    while (!(base->I2SR & kI2C_AddressMatchFlag))
    {
    }

    /* Read dummy to release bus. */
    dummy = base->I2DR;

    /* Clear the IICIF flag. */
    base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to receive data. */
    base->I2CR &= ~(I2C_I2CR_MTX_MASK);

    while (rxSize--)
    {
        /* Wait until data transfer complete. */
        while (!(base->I2SR & kI2C_IntPendingFlag))
        {
        }
        /* Clear the IICIF flag. */
        base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

        /* Read from the data register. */
        *rxBuff++ = base->I2DR;
    }
}

void I2C_SlaveTransferCreateHandle(I2C_Type *base,
                                   i2c_slave_handle_t *handle,
                                   i2c_slave_transfer_callback_t callback,
                                   void *userData)
{
    assert(handle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Save the context in global variables to support the double weak mechanism. */
    s_i2cHandle[instance] = handle;

    /* Save slave interrupt handler. */
    s_i2cSlaveIsr = I2C_SlaveTransferHandleIRQ;

    /* Enable NVIC interrupt. */
    EnableIRQ(s_i2cIrqs[instance]);
}

status_t I2C_SlaveTransferNonBlocking(I2C_Type *base, i2c_slave_handle_t *handle, uint32_t eventMask)
{
    assert(handle);

    /* Check if the I2C bus is idle - if not return busy status. */
    if (handle->state != kIdleState)
    {
        return kStatus_I2C_Busy;
    }
    else
    {
        /* Disable LPI2C IRQ sources while we configure stuff. */
        I2C_DisableInterrupts(base, kIrqFlags);

        /* Clear transfer in handle. */
        memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Record that we're busy. */
        handle->state = kCheckAddressState;

        /* Set up event mask. tx and rx are always enabled. */
        handle->eventMask = eventMask | kI2C_SlaveTransmitEvent | kI2C_SlaveReceiveEvent;

        /* Clear all flags. */
        I2C_SlaveClearStatusFlags(base, kClearFlags);

        /* Enable I2C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
        I2C_EnableInterrupts(base, kIrqFlags);
    }

    return kStatus_Success;
}

void I2C_SlaveTransferAbort(I2C_Type *base, i2c_slave_handle_t *handle)
{
    assert(handle);

    if (handle->state != kIdleState)
    {
        /* Disable interrupts. */
        I2C_DisableInterrupts(base, kIrqFlags);

        /* Reset transfer info. */
        memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Reset the state to idle. */
        handle->state = kIdleState;
    }
}

status_t I2C_SlaveTransferGetCount(I2C_Type *base, i2c_slave_handle_t *handle, size_t *count)
{
    assert(handle);

    if (!count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state == kIdleState)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* For an active transfer, just return the count from the handle. */
    *count = handle->transfer.transferredCount;

    return kStatus_Success;
}

void I2C_SlaveTransferHandleIRQ(I2C_Type *base, void *i2cHandle)
{
    assert(i2cHandle);

    uint16_t status;
    bool doTransmit = false;
    i2c_slave_handle_t *handle = (i2c_slave_handle_t *)i2cHandle;
    i2c_slave_transfer_t *xfer;
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    status = I2C_SlaveGetStatusFlags(base);
    xfer = &(handle->transfer);

    /* Clear the interrupt flag. */
    base->I2SR &= (uint8_t)~kI2C_IntPendingFlag;

    /* Check NAK */
    if (status & kI2C_ReceiveNakFlag)
    {
        /* Set receive mode. */
        base->I2CR &= ~(I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

        /* Read dummy. */
        dummy = base->I2DR;

        if (handle->transfer.dataSize != 0)
        {
            xfer->event = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_I2C_Nak;
            handle->state = kIdleState;

            if ((handle->eventMask & xfer->event) && (handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
        else
        {
            xfer->event = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->state = kIdleState;

            if ((handle->eventMask & xfer->event) && (handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
    }
    /* Check address match. */
    else if (status & kI2C_AddressMatchFlag)
    {
        xfer->event = kI2C_SlaveAddressMatchEvent;

        /* Slave transmit, master reading from slave. */
        if (status & kI2C_TransferDirectionFlag)
        {
            handle->state = kSendDataState;
            /* Change direction to send data. */
            base->I2CR |= I2C_I2CR_MTX_MASK;

            doTransmit = true;
        }
        else
        {
            handle->state = kReceiveDataState;
            /* Slave receive, master writing to slave. */
            base->I2CR &= ~(I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

            /* Read dummy to release the bus. */
            dummy = base->I2DR;
        }

        if ((handle->eventMask & xfer->event) && (handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }
    /* Check transfer complete flag. */
    else if (status & kI2C_TransferCompleteFlag)
    {
        /* Slave transmit, master reading from slave. */
        if (handle->state == kSendDataState)
        {
            doTransmit = true;
        }
        else
        {
            /* If we're out of data, invoke callback to get more. */
            if ((!xfer->data) || (!xfer->dataSize))
            {
                xfer->event = kI2C_SlaveReceiveEvent;

                if (handle->callback)
                {
                    handle->callback(base, xfer, handle->userData);
                }

                /* Clear the transferred count now that we have a new buffer. */
                xfer->transferredCount = 0;
            }

            /* Slave receive, master writing to slave. */
            uint8_t data = base->I2DR;

            if (handle->transfer.dataSize)
            {
                /* Receive data. */
                *handle->transfer.data++ = data;
                handle->transfer.dataSize--;
                xfer->transferredCount++;

                if (!handle->transfer.dataSize)
                {
                    xfer->event = kI2C_SlaveCompletionEvent;
                    xfer->completionStatus = kStatus_Success;
                    handle->state = kIdleState;

                    /* Proceed receive complete event. */
                    if ((handle->eventMask & xfer->event) && (handle->callback))
                    {
                        handle->callback(base, xfer, handle->userData);
                    }
                }
            }
        }
    }
    else
    {
        /* Read dummy to release bus. */
        dummy = base->I2DR;
    }

    /* Send data if there is the need. */
    if (doTransmit)
    {
        /* If we're out of data, invoke callback to get more. */
        if ((!xfer->data) || (!xfer->dataSize))
        {
            xfer->event = kI2C_SlaveTransmitEvent;

            if (handle->callback)
            {
                handle->callback(base, xfer, handle->userData);
            }

            /* Clear the transferred count now that we have a new buffer. */
            xfer->transferredCount = 0;
        }

        if (handle->transfer.dataSize)
        {
            /* Send data. */
            base->I2DR = *handle->transfer.data++;
            handle->transfer.dataSize--;
            xfer->transferredCount++;
        }
        else
        {
            /* Switch to receive mode. */
            base->I2CR &= ~(I2C_I2CR_MTX_MASK | I2C_I2CR_TXAK_MASK);

            /* Read dummy to release bus. */
            dummy = base->I2DR;

            xfer->event = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->state = kIdleState;

            /* Proceed txdone event. */
            if ((handle->eventMask & xfer->event) && (handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
    }
}

#if defined(I2C1)
void I2C1_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C1, s_i2cHandle[1]);
}
#endif

#if defined(I2C2)
void I2C2_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C2, s_i2cHandle[2]);
}
#endif

#if defined(I2C3)
void I2C3_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C3, s_i2cHandle[3]);
}
#endif

#if defined(I2C4)
void I2C4_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C4, s_i2cHandle[4]);
}
#endif

#include <drv_i2c.h>
void I2C_DriverIRQHandler(int irq, void *base)
{
    struct imx6ull_i2c_config *config;
    uint32_t i2c_instance = 0;

    config = (struct imx6ull_i2c_config*)base;

    i2c_instance = I2C_GetInstance(config->hw_base);
    I2C_TransferCommonIRQHandler(config->I2C, s_i2cHandle[i2c_instance]);
}
