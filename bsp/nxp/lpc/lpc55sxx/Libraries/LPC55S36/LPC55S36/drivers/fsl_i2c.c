/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i2c.h"
#include "fsl_flexcomm.h"
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_i2c"
#endif

/*! @brief Common sets of flags used by the driver's transactional layer internally. */
enum _i2c_flag_constants
{
    kI2C_MasterIrqFlags = I2C_INTSTAT_MSTPENDING_MASK | I2C_INTSTAT_MSTARBLOSS_MASK | I2C_INTSTAT_MSTSTSTPERR_MASK |
                          I2C_INTSTAT_EVENTTIMEOUT_MASK | I2C_INTSTAT_SCLTIMEOUT_MASK,
    kI2C_SlaveIrqFlags = I2C_INTSTAT_SLVPENDING_MASK | I2C_INTSTAT_SLVDESEL_MASK,
};

/*!
 * @brief Used for conversion from `flexcomm_irq_handler_t` to `flexcomm_i2c_master_irq_handler_t` and
 * `flexcomm_i2c_slave_irq_handler_t`.
 */
typedef union i2c_to_flexcomm
{
    flexcomm_i2c_master_irq_handler_t i2c_master_handler;
    flexcomm_i2c_slave_irq_handler_t i2c_slave_handler;
    flexcomm_irq_handler_t flexcomm_handler;
} i2c_to_flexcomm_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Waits for Master Pending status bit to set and check for bus error status.
 *
 * @param base The I2C peripheral base address.
 * @return Bus status.
 */
static status_t I2C_PendingStatusWait(I2C_Type *base);

/*!
 * @brief Prepares the transfer state machine and fills in the command buffer.
 * @param base The I2C peripheral base address.
 * @param handle Master nonblocking driver handle.
 * @param xfer The I2C transfer configuration structure.
 */
static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer);

/*!
 * @brief Resets the slave hardware state machine.
 * According to documentation, after disabling slave to rest the slave hardware state machine, the register
 * configuration remains unchanged.
 * @param base The I2C peripheral base address.
 */
static void I2C_SlaveInternalStateMachineReset(I2C_Type *base);

/*!
 * @brief Compute CLKDIV
 *
 * This function computes CLKDIV value according to the given bus speed and Flexcomm source clock frequency.
 * This setting is used by hardware during slave clock stretching.
 *
 * @param base The I2C peripheral base address.
 * @return status of the operation
 */
static status_t I2C_SlaveDivVal(uint32_t srcClock_Hz, i2c_slave_bus_speed_t busSpeed, uint32_t *divVal);

/*!
 * @brief Poll wait for the SLVPENDING flag.
 *
 * Wait for the pending status to be set (SLVPENDING = 1) by polling the STAT register.
 *
 * @param base The I2C peripheral base address.
 * @return status register at time the SLVPENDING bit is read as set
 */
static uint32_t I2C_SlavePollPending(I2C_Type *base);

/*!
 * @brief Invoke event from I2C_SlaveTransferHandleIRQ().
 *
 * Sets the event type to transfer structure and invokes the event callback, if it has been
 * enabled by eventMask.
 *
 * @param base The I2C peripheral base address.
 * @param handle The I2C slave handle for non-blocking APIs.
 * @param event The I2C slave event to invoke.
 */
static void I2C_SlaveInvokeEvent(I2C_Type *base, i2c_slave_handle_t *handle, i2c_slave_transfer_event_t event);

/*!
 * @brief Handle slave address match event.
 *
 * Called by Slave interrupt routine to ACK or NACK the matched address.
 * It also determines master direction (read or write).
 *
 * @param base The I2C peripheral base address.
 * @return true if the matched address is ACK'ed
 * @return false if the matched address is NACK'ed
 */
static bool I2C_SlaveAddressIRQ(I2C_Type *base, i2c_slave_handle_t *handle);

/*!
 * @brief Starts accepting slave transfers.
 *
 * Call this API after calling I2C_SlaveInit() and I2C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and pass events to the
 * callback that was passed into the call to I2C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * @param base The I2C peripheral base address.
 * @param handle Pointer to #i2c_slave_handle_t structure which stores the transfer state.
 * @param txData Data to be transmitted to master in response to master read from slave requests. NULL if slave RX only.
 * @param txSize Size of txData buffer in bytes.
 * @param rxData Data where received data from master will be stored in response to master write to slave requests. NULL
 *               if slave TX only.
 * @param rxSize Size of rxData buffer in bytes.
 * @retval #kStatus_Success Slave transfers were successfully started.
 * @retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
static status_t I2C_SlaveTransferNonBlockingInternal(I2C_Type *base,
                                                     i2c_slave_handle_t *handle,
                                                     const void *txData,
                                                     size_t txSize,
                                                     void *rxData,
                                                     size_t rxSize,
                                                     uint32_t eventMask);

/*!
 * @brief Execute master transfer software state machine until FIFOs are exhausted.
 *
 * For master transmit, the states would be kStartState->kTransmitSubaddrState->kTransmitDataState->kStopState
 * For master receive, the states would be kStartState->kTransmitSubaddrState->kStartState->kReceiveDataState->
 * kWaitForCompletionState
 *
 * @param handle Master nonblocking driver handle.
 * @param[out] isDone Set to true if the transfer has completed.
 * @retval #kStatus_Success
 * @retval #kStatus_I2C_ArbitrationLost
 * @retval #kStatus_I2C_Nak
 */
static status_t I2C_RunTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone);

/*!
 * @brief Checks the slave response to master's start signal.
 *
 * @param base I2C peripheral base address.
 * @retval kStatus_Success Successfully complete the data transmission.
 * @retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 * @retval kStataus_I2C_Nak Transfer error, receive NAK during addressing.
 */
static status_t I2C_MasterCheckStartResponse(I2C_Type *base);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map i2c instance number to base address. */
static const uint32_t s_i2cBaseAddrs[FSL_FEATURE_SOC_I2C_COUNT] = I2C_BASE_ADDRS;

/*! @brief IRQ name array */
static const IRQn_Type s_i2cIRQ[] = I2C_IRQS;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Returns an instance number given a base address.
 *
 * If an invalid base address is passed, debug builds will assert. Release builds will just return
 * instance number 0.
 *
 * param base The I2C peripheral base address.
 * return I2C instance number starting from 0.
 */
uint32_t I2C_GetInstance(I2C_Type *base)
{
    uint32_t i;
    for (i = 0; i < (uint32_t)FSL_FEATURE_SOC_I2C_COUNT; i++)
    {
        if ((uint32_t)base == s_i2cBaseAddrs[i])
        {
            break;
        }
    }
    assert(i < (uint32_t)FSL_FEATURE_SOC_I2C_COUNT);
    return i;
}

/*!
 * brief Provides a default configuration for the I2C master peripheral.
 *
 * This function provides the following default configuration for the I2C master peripheral:
 * code
 *  masterConfig->enableMaster            = true;
 *  masterConfig->baudRate_Bps            = 100000U;
 *  masterConfig->enableTimeout           = false;
 * endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the master driver with I2C_MasterInit().
 *
 * param[out] masterConfig User provided configuration structure for default values. Refer to #i2c_master_config_t.
 */
void I2C_MasterGetDefaultConfig(i2c_master_config_t *masterConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    masterConfig->enableMaster  = true;
    masterConfig->baudRate_Bps  = 100000U;
    masterConfig->enableTimeout = false;
    masterConfig->timeout_Ms    = 35;
}

/*!
 * brief Initializes the I2C master peripheral.
 *
 * This function enables the peripheral clock and initializes the I2C master peripheral as described by the user
 * provided configuration. A software reset is performed prior to configuration.
 *
 * param base The I2C peripheral base address.
 * param masterConfig User provided peripheral configuration. Use I2C_MasterGetDefaultConfig() to get a set of
 * defaults
 *      that you can override.
 * param srcClock_Hz Frequency in Hertz of the I2C functional clock. Used to calculate the baud rate divisors,
 *      filter widths, and timeout periods.
 */
void I2C_MasterInit(I2C_Type *base, const i2c_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    (void)FLEXCOMM_Init(base, FLEXCOMM_PERIPH_I2C);
    I2C_MasterEnable(base, masterConfig->enableMaster);
    I2C_MasterSetBaudRate(base, masterConfig->baudRate_Bps, srcClock_Hz);
    I2C_MasterSetTimeoutValue(base, masterConfig->timeout_Ms, srcClock_Hz);
}

/*!
 * brief Deinitializes the I2C master peripheral.
 *
 * This function disables the I2C master peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * param base The I2C peripheral base address.
 */
void I2C_MasterDeinit(I2C_Type *base)
{
    I2C_MasterEnable(base, false);
}

/*!
 * brief Gets the I2C status flags.
 *
 * A bit mask with the state of all I2C status flags is returned. For each flag, the corresponding bit
 * in the return value is set if the flag is asserted.
 *
 * param base The I2C peripheral base address.
 * return State of the status flags:
 *         - 1: related status flag is set.
 *         - 0: related status flag is not set.
 * see ref _i2c_status_flags, ref _i2c_master_status_flags and ref _i2c_slave_status_flags.
 */
uint32_t I2C_GetStatusFlags(I2C_Type *base)
{
    uint32_t statusMask = base->STAT;
    if ((statusMask & (uint32_t)I2C_STAT_MSTSTATE_MASK) == 0UL)
    {
        statusMask |= (uint32_t)kI2C_MasterIdleFlag;
    }
    if (((statusMask & (uint32_t)I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT) == 3UL)
    {
        statusMask = (statusMask & ~(uint32_t)I2C_STAT_MSTSTATE_MASK) | (uint32_t)kI2C_MasterAddrNackFlag;
    }
    if ((statusMask & (uint32_t)I2C_STAT_SLVSTATE_MASK) == 0UL)
    {
        statusMask |= (uint32_t)kI2C_SlaveAddressedFlag;
    }
    if ((statusMask & (uint32_t)I2C_STAT_SLVIDX_MASK) == 0UL)
    {
        statusMask |= (uint32_t)kI2C_SlaveAddress0MatchFlag;
    }
    if (((statusMask & (uint32_t)I2C_STAT_SLVIDX_MASK) >> I2C_STAT_SLVIDX_SHIFT) == 3UL)
    {
        statusMask = (statusMask & ~(uint32_t)I2C_STAT_SLVIDX_MASK) | (uint32_t)kI2C_SlaveAddress3MatchFlag;
    }
    return statusMask;
}

/*!
 * brief Sets the I2C bus frequency for master transactions.
 *
 * The I2C master is automatically disabled and re-enabled as necessary to configure the baud
 * rate. Do not call this function during a transfer, or the transfer is aborted.
 *
 * param base The I2C peripheral base address.
 * param srcClock_Hz I2C functional clock frequency in Hertz.
 * param baudRate_Bps Requested bus frequency in bits per second.
 */
void I2C_MasterSetBaudRate(I2C_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t scl, divider;
    uint32_t mindivider;
    uint32_t err, best_err;
    uint32_t best_scl = 0U;
    uint32_t best_div = 0U;

#if defined(FSL_FEATURE_I2C_PREPCLKFRG_8MHZ) && (FSL_FEATURE_I2C_PREPCLKFRG_8MHZ)
    /*
     * RFT1717/RFT1437: workaround for hardware bug when using DMA
     * I2C peripheral clock frequency has to be fixed at 8MHz
     * source clock is 32MHz or 48MHz so divider is a round integer value
     */
    best_div = srcClock_Hz / 8000000U;
    best_scl = 8000000U / baudRate_Bps;

    if ((8000000U / best_scl - baudRate_Bps) > (baudRate_Bps - (8000000U / (best_scl + 1U))))
    {
        best_scl = best_scl + 1U;
    }

    /*
     * Fallback to usual baudrate computation method, when:
     * 1.Master SCL frequency does not fit in workaround range,
     * 2.User's setting of baudRate_Bps is 400kHz while the clock frequency after divval is larger than 2MHz
     */
    if ((best_scl > 18U) || ((best_scl < 4U)) || ((baudRate_Bps == 400000U) && (srcClock_Hz / best_div > 2000000U)))
    {
#endif /*FSL_FEATURE_I2C_PREPCLKFRG_8MHZ*/

        /* Calculate the minimal divider value to make sure the clock frequency after divval is not larger than 2MHz */
        /* This is required in RM in order to generate 400kHz baudrate */
        mindivider = ((srcClock_Hz * 10U) / 2000000U + 5U) / 10U;
        /* If the scl value with current mindivider is smaller than 4, which is the minimal value register can achieve,
           update mindivider */
        if ((srcClock_Hz / mindivider / baudRate_Bps) < 4U)
        {
            mindivider = srcClock_Hz / 4U / baudRate_Bps;
        }
        /* Calculate the ideal div and scl value*/
        best_err = 0U;
        for (divider = mindivider; divider <= 0x10000U; divider++)
        {
            /* Calculte ideal scl value, round up the value */
            scl = ((srcClock_Hz * 10U) / (divider * baudRate_Bps) + 5U) / 10U;

            /* adjust it if it is out of range */
            scl = (scl > 18U) ? 18U : scl;

            /* calculate error */
            err = srcClock_Hz - (baudRate_Bps * scl * divider);
            if ((err < best_err) || (best_err == 0U))
            {
                best_div = divider;
                best_scl = scl;
                best_err = err;
            }

            if ((err == 0U) || (scl <= 4U))
            {
                /* either exact value was found
                   or scl is at its min (it would be even smaller in the next iteration for sure) */
                break;
            }
        }
#if defined(FSL_FEATURE_I2C_PREPCLKFRG_8MHZ) && (FSL_FEATURE_I2C_PREPCLKFRG_8MHZ)
    }
#endif /*FSL_FEATURE_I2C_PREPCLKFRG_8MHZ*/
    base->CLKDIV = I2C_CLKDIV_DIVVAL(best_div - 1U);
    if (best_scl % 2U == 0U)
    {
        base->MSTTIME = I2C_MSTTIME_MSTSCLLOW(best_scl / 2U - 2U) | I2C_MSTTIME_MSTSCLHIGH(best_scl / 2U - 2U);
    }
    else
    {
        base->MSTTIME = I2C_MSTTIME_MSTSCLLOW(best_scl / 2U - 1U) | I2C_MSTTIME_MSTSCLHIGH(best_scl / 2U - 2U);
    }
}

/*!
 * brief Sets the I2C bus timeout value.
 *
 * If the SCL signal remains low or bus does not have event longer than the timeout value, kI2C_SclTimeoutFlag or
 * kI2C_EventTimeoutFlag is set. This can indicete the bus is held by slave or any fault occurs to the I2C module.
 *
 * param base The I2C peripheral base address.
 * param timeout_Ms Timeout value in millisecond.
 * param srcClock_Hz I2C functional clock frequency in Hertz.
 */
void I2C_MasterSetTimeoutValue(I2C_Type *base, uint8_t timeout_Ms, uint32_t srcClock_Hz)
{
    assert((timeout_Ms != 0U) && (srcClock_Hz != 0U));

    /* The low 4 bits of the timout reister TIMEOUT is hard-wired to be 1, so the the time out value is always 16 times
       the I2C functional clock, we only need to calculate the high bits. */
    uint32_t timeoutValue = ((uint32_t)timeout_Ms * srcClock_Hz / 16UL / 100UL + 5UL) / 10UL;
    if (timeoutValue > 0x1000UL)
    {
        timeoutValue = 0x1000UL;
    }
    timeoutValue  = ((timeoutValue - 1UL) << 4UL) | 0xFUL;
    base->TIMEOUT = timeoutValue;
}

static status_t I2C_PendingStatusWait(I2C_Type *base)
{
    status_t result = kStatus_Success;
    uint32_t status;

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    do
    {
        status = I2C_GetStatusFlags(base);
        if ((status & (uint32_t)kI2C_EventTimeoutFlag) != 0U)
        {
            result = kStatus_I2C_EventTimeout;
        }
        if ((status & (uint32_t)kI2C_SclTimeoutFlag) != 0U)
        {
            result = kStatus_I2C_SclLowTimeout;
        }
#if defined(FSL_FEATURE_I2C_TIMEOUT_RECOVERY) && FSL_FEATURE_I2C_TIMEOUT_RECOVERY
        if (result != kStatus_Success)
        {
            I2C_MasterEnable(base, false);
            I2C_MasterEnable(base, true);
            break;
        }
#endif
#if I2C_RETRY_TIMES != 0U
        waitTimes--;
    } while (((status & (uint32_t)kI2C_MasterPendingFlag) == 0U) && (waitTimes != 0U));

    if (waitTimes == 0U)
    {
#if defined(FSL_FEATURE_I2C_TIMEOUT_RECOVERY) && FSL_FEATURE_I2C_TIMEOUT_RECOVERY
        I2C_MasterEnable(base, false);
        I2C_MasterEnable(base, true);
#endif
        return (uint32_t)kStatus_I2C_Timeout;
    }
#else
    } while ((status & (uint32_t)kI2C_MasterPendingFlag) == 0U);
#endif

    if ((status & (uint32_t)kI2C_MasterArbitrationLostFlag) != 0U)
    {
        result = kStatus_I2C_ArbitrationLost;
    }

    if ((status & (uint32_t)kI2C_MasterStartStopErrorFlag) != 0U)
    {
        result = kStatus_I2C_StartStopError;
    }

    /* Clear controller state. */
    I2C_ClearStatusFlags(
        base, (uint32_t)kI2C_MasterAllClearFlags | (uint32_t)kI2C_EventTimeoutFlag | (uint32_t)kI2C_SclTimeoutFlag);

    return result;
}

/*!
 * brief Sends a START on the I2C bus.
 *
 * This function is used to initiate a new master mode transfer by sending the START signal.
 * The slave address is sent following the I2C START signal.
 *
 * param base I2C peripheral base pointer
 * param address 7-bit slave device address.
 * param direction Master transfer directions(transmit/receive).
 * retval kStatus_Success Successfully send the start signal.
 * retval kStatus_I2C_Busy Current bus is busy.
 */
status_t I2C_MasterStart(I2C_Type *base, uint8_t address, i2c_direction_t direction)
{
    status_t result;
    result = I2C_PendingStatusWait(base);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Write Address and RW bit to data register */
    base->MSTDAT = ((uint32_t)address << 1) | ((uint32_t)direction & 1U);
    /* Start the transfer */
    base->MSTCTL = I2C_MSTCTL_MSTSTART_MASK;

    return kStatus_Success;
}

/*!
 * brief Sends a STOP signal on the I2C bus.
 *
 * retval kStatus_Success Successfully send the stop signal.
 * retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterStop(I2C_Type *base)
{
    status_t result = I2C_PendingStatusWait(base);
    if (result != kStatus_Success)
    {
        return result;
    }

    base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;
    return kStatus_Success;
}

/*!
 * brief Performs a polling send transfer on the I2C bus.
 *
 * Sends up to a txSize number of bytes to the previously addressed slave device. The slave may
 * reply with a NAK to any byte in order to terminate the transfer early. If this happens, this
 * function returns #kStatus_I2C_Nak.
 *
 * param base  The I2C peripheral base address.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * param flags Transfer control flag to control special behavior like suppressing start or stop, for normal transfers
 * use kI2C_TransferDefaultFlag
 * retval kStatus_Success Data was sent successfully.
 * retval #kStatus_I2C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_I2C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_I2C_ArbitrationLost Arbitration lost error.
 */
status_t I2C_MasterWriteBlocking(I2C_Type *base, const void *txBuff, size_t txSize, uint32_t flags)
{
    uint32_t master_state;
    status_t err;

    const uint8_t *buf = (const uint8_t *)txBuff;

    assert(txBuff != NULL);

    err = kStatus_Success;
    while (txSize != 0U)
    {
        err = I2C_PendingStatusWait(base);

        if (err != kStatus_Success)
        {
            return err;
        }

        master_state = (base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;
        switch (master_state)
        {
            case I2C_STAT_MSTCODE_TXREADY:
                /* ready to send next byte */
                base->MSTDAT = *buf++;
                txSize--;
                base->MSTCTL = I2C_MSTCTL_MSTCONTINUE_MASK;
                break;

            case I2C_STAT_MSTCODE_NACKADR:
            case I2C_STAT_MSTCODE_NACKDAT:
                err = kStatus_I2C_Nak;
                /* Issue nack signal when nacked by slave. */
                (void)I2C_MasterStop(base);
                break;

            default:
                /* unexpected state */
                err = kStatus_I2C_UnexpectedState;
                break;
        }

        if (err != kStatus_Success)
        {
            return err;
        }
    }

    err = I2C_PendingStatusWait(base);

    if (err != kStatus_Success)
    {
        return err;
    }

#if !I2C_MASTER_TRANSMIT_IGNORE_LAST_NACK
    /* Check nack signal. If master is nacked by slave of the last byte, return kStatus_I2C_Nak. */
    if (((base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT) == (uint32_t)I2C_STAT_MSTCODE_NACKDAT)
    {
        (void)I2C_MasterStop(base);
        return kStatus_I2C_Nak;
    }
#endif

    if (0U == (flags & (uint32_t)kI2C_TransferNoStopFlag))
    {
        /* Initiate stop */
        base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;
        err          = I2C_PendingStatusWait(base);
        if (err != kStatus_Success)
        {
            return err;
        }
    }

    return kStatus_Success;
}

/*!
 * brief Performs a polling receive transfer on the I2C bus.
 *
 * param base  The I2C peripheral base address.
 * param rxBuff The pointer to the data to be transferred.
 * param rxSize The length in bytes of the data to be transferred.
 * param flags Transfer control flag to control special behavior like suppressing start or stop, for normal transfers
 * use kI2C_TransferDefaultFlag
 * retval kStatus_Success Data was received successfully.
 * retval #kStatus_I2C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_I2C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_I2C_ArbitrationLost Arbitration lost error.
 */
status_t I2C_MasterReadBlocking(I2C_Type *base, void *rxBuff, size_t rxSize, uint32_t flags)
{
    uint32_t master_state;
    status_t err;

    uint8_t *buf = (uint8_t *)(rxBuff);

    assert(rxBuff != NULL);

    err = kStatus_Success;
    while (rxSize != 0U)
    {
        err = I2C_PendingStatusWait(base);

        if (err != kStatus_Success)
        {
            return err;
        }

        master_state = (base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;
        switch (master_state)
        {
            case I2C_STAT_MSTCODE_RXREADY:
                /* ready to send next byte */
                *(buf++) = (uint8_t)base->MSTDAT;
                if (--rxSize != 0U)
                {
                    base->MSTCTL = I2C_MSTCTL_MSTCONTINUE_MASK;
                }
                else
                {
                    if ((flags & (uint32_t)kI2C_TransferNoStopFlag) == 0U)
                    {
                        /* initiate NAK and stop */
                        base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;
                        err          = I2C_PendingStatusWait(base);
                    }
                }
                break;

            case I2C_STAT_MSTCODE_NACKADR:
            case I2C_STAT_MSTCODE_NACKDAT:
                /* slave nacked the last byte */
                err = kStatus_I2C_Nak;
                break;

            default:
                /* unexpected state */
                err = kStatus_I2C_UnexpectedState;
                break;
        }

        if (err != kStatus_Success)
        {
            return err;
        }
    }

    return kStatus_Success;
}

static status_t I2C_MasterCheckStartResponse(I2C_Type *base)
{
    /* Wait for start signal to be transmitted. */
    status_t result = I2C_PendingStatusWait(base);

    if (result != kStatus_Success)
    {
        return result;
    }

    if (((base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT) == I2C_STAT_MSTCODE_NACKADR)
    {
        (void)I2C_MasterStop(base);
        return kStatus_I2C_Addr_Nak;
    }
    return kStatus_Success;
}

/*!
 * brief Performs a master polling transfer on the I2C bus.
 *
 * note The API does not return until the transfer succeeds or fails due
 * to arbitration lost or receiving a NAK.
 *
 * param base I2C peripheral base address.
 * param xfer Pointer to the transfer structure.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_Busy Previous transmission still not finished.
 * retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 * retval kStataus_I2C_Addr_Nak Transfer error, receive NAK during addressing.
 */
status_t I2C_MasterTransferBlocking(I2C_Type *base, i2c_master_transfer_t *xfer)
{
    status_t result = kStatus_Success;
    uint32_t subaddress;
    uint8_t subaddrBuf[4];
    i2c_direction_t direction;
    int i;

    assert(xfer != NULL);

    /* If start signal is requested, send start signal. */
    if (0U == (xfer->flags & (uint32_t)kI2C_TransferNoStartFlag))
    {
        direction = (xfer->subaddressSize != 0U) ? kI2C_Write : xfer->direction;
        result    = I2C_MasterStart(base, xfer->slaveAddress, direction);
        if (result == kStatus_Success)
        {
            result = I2C_MasterCheckStartResponse(base);
            if (result != kStatus_Success)
            {
                return result;
            }
            if ((xfer->subaddressSize) != 0U)
            {
                /* Prepare subaddress transmit buffer, most significant byte is stored at the lowest address */
                subaddress = xfer->subaddress;
                for (i = (int)xfer->subaddressSize - 1; i >= 0; i--)
                {
                    subaddrBuf[i] = (uint8_t)subaddress & 0xffU;
                    subaddress >>= 8;
                }
                /* Send subaddress. */
                result =
                    I2C_MasterWriteBlocking(base, subaddrBuf, xfer->subaddressSize, (uint32_t)kI2C_TransferNoStopFlag);
                if (result != kStatus_Success)
                {
                    if (result == kStatus_I2C_Nak)
                    {
                        (void)I2C_MasterStop(base);
                        return kStatus_I2C_Addr_Nak;
                    }
                }
                else if (xfer->direction == kI2C_Read)
                {
                    result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, xfer->direction);
                    if (result == kStatus_Success)
                    {
                        result = I2C_MasterCheckStartResponse(base);
                        if (result != kStatus_Success)
                        {
                            return result;
                        }
                    }
                }
                else
                {
                    /* Empty else block to avoid MISRA 14.1 violation. */
                }
            }
        }
    }

    if (result == kStatus_Success)
    {
        if ((xfer->direction == kI2C_Write) && (xfer->dataSize > 0U))
        {
            /* Transmit data. */
            result = I2C_MasterWriteBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
        }
        else
        {
            if ((xfer->direction == kI2C_Read) && (xfer->dataSize > 0U))
            {
                /* Receive Data. */
                result = I2C_MasterReadBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
            }
        }
    }

    if (result == kStatus_I2C_Nak)
    {
        (void)I2C_MasterStop(base);
    }

    return result;
}

/*!
 * brief Creates a new handle for the I2C master non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I2C_MasterTransferAbort() API shall be called.
 *
 * param base The I2C peripheral base address.
 * param[out] handle Pointer to the I2C master driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void I2C_MasterTransferCreateHandle(I2C_Type *base,
                                    i2c_master_handle_t *handle,
                                    i2c_master_transfer_callback_t callback,
                                    void *userData)
{
    assert(handle != NULL);

    uint32_t instance;
    i2c_to_flexcomm_t handler;
    handler.i2c_master_handler = I2C_MasterTransferHandleIRQ;

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I2C_GetInstance(base);

    /* Save base and instance. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    FLEXCOMM_SetIRQHandler(base, handler.flexcomm_handler, handle);

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_MasterIrqFlags);
    (void)EnableIRQ(s_i2cIRQ[instance]);
}

/*!
 * brief Performs a non-blocking transaction on the I2C bus.
 *
 * param base The I2C peripheral base address.
 * param handle Pointer to the I2C master driver handle.
 * param xfer The pointer to the transfer descriptor.
 * retval kStatus_Success The transaction was started successfully.
 * retval #kStatus_I2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t I2C_MasterTransferNonBlocking(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
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

    /* Disable I2C IRQ sources while we configure stuff. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_MasterIrqFlags);

    /* Prepare transfer state machine. */
    result = I2C_InitTransferStateMachine(base, handle, xfer);

    /* Clear error flags. */
    I2C_ClearStatusFlags(base, I2C_STAT_MSTARBLOSS_MASK | I2C_STAT_MSTSTSTPERR_MASK);

    /* Enable I2C internal IRQ sources. */
    I2C_EnableInterrupts(base, (uint32_t)kI2C_MasterIrqFlags);

    return result;
}

/*!
 * brief Returns number of bytes transferred so far.
 * param base The I2C peripheral base address.
 * param handle Pointer to the I2C master driver handle.
 * param[out] count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_Success
 * retval #kStatus_I2C_Busy
 */
status_t I2C_MasterTransferGetCount(I2C_Type *base, i2c_master_handle_t *handle, size_t *count)
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
 * brief Terminates a non-blocking I2C master transmission early.
 *
 * note It is not safe to call this function from an IRQ handler that has a higher priority than the
 *      I2C peripheral's IRQ priority.
 *
 * param base The I2C peripheral base address.
 * param handle Pointer to the I2C master driver handle.
 * retval kStatus_Success A transaction was successfully aborted.
 * retval #kStatus_I2C_Timeout Timeout during polling for flags.
 */
status_t I2C_MasterTransferAbort(I2C_Type *base, i2c_master_handle_t *handle)
{
    status_t result = kStatus_Success;
    uint32_t master_state;

    if (handle->state != (uint8_t)kIdleState)
    {
        /* Disable internal IRQ enables. */
        I2C_DisableInterrupts(base, (uint32_t)kI2C_MasterIrqFlags);

        /* Wait until module is ready */
        result = I2C_PendingStatusWait(base);

        if (result != kStatus_Success)
        {
            handle->state = (uint8_t)kIdleState;
            return result;
        }

        /* Get the state of the I2C module */
        master_state = (base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;

        if (master_state != (uint32_t)I2C_STAT_MSTCODE_IDLE)
        {
            /* Send a stop command to finalize the transfer. */
            base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;

            /* Wait until the STOP is completed */
            result = I2C_PendingStatusWait(base);

            if (result != kStatus_Success)
            {
                handle->state = (uint8_t)kIdleState;
                return result;
            }
        }

        /* Reset handle. */
        handle->state         = (uint8_t)kIdleState;
        handle->checkAddrNack = false;
    }
    return kStatus_Success;
}

static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    struct _i2c_master_transfer *transfer;

    handle->transfer = *xfer;
    transfer         = &(handle->transfer);

    handle->transferCount    = 0;
    handle->remainingBytes   = transfer->dataSize;
    handle->buf              = (uint8_t *)transfer->data;
    handle->remainingSubaddr = 0;
    handle->checkAddrNack    = false;

    if ((transfer->flags & (uint32_t)kI2C_TransferNoStartFlag) != 0U)
    {
        /* Start condition shall be ommited, switch directly to next phase */
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
            handle->state = (uint8_t)kReceiveDataBeginState;
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

static status_t I2C_RunTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone)
{
    uint32_t status;
    uint32_t master_state;
    struct _i2c_master_transfer *transfer;
    status_t err;

    transfer       = &(handle->transfer);
    bool ignoreNak = ((handle->state == (uint8_t)kWaitForCompletionState) && (handle->remainingBytes == 0U))
#if I2C_MASTER_TRANSMIT_IGNORE_LAST_NACK
                     /* If master is nacked by slave after the last byte during transmit, ignore the nack. */
                     || ((handle->state == (uint8_t)kStopState) && (handle->remainingBytes == 0U))
#endif
        ;

    *isDone = false;

    status = I2C_GetStatusFlags(base);

    if ((status & I2C_STAT_MSTARBLOSS_MASK) != 0U)
    {
        I2C_ClearStatusFlags(base, I2C_STAT_MSTARBLOSS_MASK);
        return kStatus_I2C_ArbitrationLost;
    }

    if ((status & I2C_STAT_MSTSTSTPERR_MASK) != 0U)
    {
        I2C_ClearStatusFlags(base, I2C_STAT_MSTSTSTPERR_MASK);
        return kStatus_I2C_StartStopError;
    }

    /* Event timeout happens when the time since last bus event has been longer than the time specified by TIMEOUT
       register. eg: Start signal fails to generate, no error status is set and transfer hangs if glitch on bus happens
       before, the timeout status can be used to avoid the transfer hangs indefinitely. */
    if ((status & (uint32_t)kI2C_EventTimeoutFlag) != 0U)
    {
        I2C_ClearStatusFlags(base, (uint32_t)kI2C_EventTimeoutFlag);
        return kStatus_I2C_EventTimeout;
    }

    /* SCL timeout happens when the slave is holding the SCL line low and the time has been longer than the time
       specified by TIMEOUT register. */
    if ((status & (uint32_t)kI2C_SclTimeoutFlag) != 0U)
    {
        I2C_ClearStatusFlags(base, (uint32_t)kI2C_SclTimeoutFlag);
        return kStatus_I2C_SclLowTimeout;
    }

    if ((status & I2C_STAT_MSTPENDING_MASK) == 0U)
    {
        return kStatus_I2C_Busy;
    }

    /* Get the hardware state of the I2C module */
    master_state = (base->STAT & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;
    if (((master_state == (uint32_t)I2C_STAT_MSTCODE_NACKADR) ||
         (master_state == (uint32_t)I2C_STAT_MSTCODE_NACKDAT)) &&
        (ignoreNak != true))
    {
        /* Slave NACKed last byte, issue stop and return error */
        base->MSTCTL  = I2C_MSTCTL_MSTSTOP_MASK;
        handle->state = (uint8_t)kWaitForCompletionState;
        /* If master is nacked during slave probe or during sending subaddress, return kStatus_I2C_ADDR_Nak. */
        if ((master_state == (uint32_t)I2C_STAT_MSTCODE_NACKADR) || (handle->checkAddrNack))
        {
            return kStatus_I2C_Addr_Nak;
        }
        else /* Otherwise just return kStatus_I2C_Nak */
        {
            return kStatus_I2C_Nak;
        }
    }

    err = kStatus_Success;
    switch (handle->state)
    {
        case (uint8_t)kStartState:
            if (handle->remainingSubaddr != 0U)
            {
                /* Subaddress takes precedence over the data transfer, direction is always "write" in this case */
                base->MSTDAT  = (uint32_t)transfer->slaveAddress << 1U;
                handle->state = (uint8_t)kTransmitSubaddrState;
            }
            else if (transfer->direction == kI2C_Write)
            {
                base->MSTDAT  = (uint32_t)transfer->slaveAddress << 1;
                handle->state = (handle->remainingBytes != 0U) ? (uint8_t)kTransmitDataState : (uint8_t)kStopState;
            }
            else
            {
                base->MSTDAT  = ((uint32_t)transfer->slaveAddress << 1) | 1u;
                handle->state = (handle->remainingBytes != 0U) ? (uint8_t)kReceiveDataState : (uint8_t)kStopState;
            }
            /* Send start condition */
            base->MSTCTL = I2C_MSTCTL_MSTSTART_MASK;
            break;

        case (uint8_t)kTransmitSubaddrState:
            if (master_state != (uint32_t)I2C_STAT_MSTCODE_TXREADY)
            {
                return kStatus_I2C_UnexpectedState;
            }
            /* Most significant subaddress byte comes first */
            base->MSTDAT = handle->subaddrBuf[handle->transfer.subaddressSize - handle->remainingSubaddr];
            base->MSTCTL = I2C_MSTCTL_MSTCONTINUE_MASK;
            if (--(handle->remainingSubaddr) != 0U)
            {
                /* There are still subaddress bytes to be transmitted */
                break;
            }
            if (handle->remainingBytes != 0U)
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
            handle->checkAddrNack = false;
            if (master_state != (uint32_t)I2C_STAT_MSTCODE_TXREADY)
            {
                return kStatus_I2C_UnexpectedState;
            }
            base->MSTDAT = *(handle->buf)++;
            base->MSTCTL = I2C_MSTCTL_MSTCONTINUE_MASK;
            if (--handle->remainingBytes == 0U)
            {
                /* No more data, schedule stop condition */
                handle->state = (uint8_t)kStopState;
            }
            handle->transferCount++;
            break;

        case (uint8_t)kReceiveDataBeginState:
            handle->checkAddrNack = false;
            if (master_state != (uint32_t)I2C_STAT_MSTCODE_RXREADY)
            {
                return kStatus_I2C_UnexpectedState;
            }
            (void)base->MSTDAT;
            base->MSTCTL  = I2C_MSTCTL_MSTCONTINUE_MASK;
            handle->state = (uint8_t)kReceiveDataState;
            break;

        case (uint8_t)kReceiveDataState:
            handle->checkAddrNack = false;
            if (master_state != (uint32_t)I2C_STAT_MSTCODE_RXREADY)
            {
                return kStatus_I2C_UnexpectedState;
            }
            *(handle->buf)++ = (uint8_t)base->MSTDAT;
            if (--handle->remainingBytes != 0U)
            {
                base->MSTCTL = I2C_MSTCTL_MSTCONTINUE_MASK;
            }
            else
            {
                /* No more data expected, issue NACK and STOP right away */
                if (0U == (transfer->flags & (uint32_t)kI2C_TransferNoStopFlag))
                {
                    base->MSTCTL = I2C_MSTCTL_MSTSTOP_MASK;
                }
                handle->state = (uint8_t)kWaitForCompletionState;
            }
            handle->transferCount++;
            break;

        case (uint8_t)kStopState:
            handle->checkAddrNack = false;
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

        case (uint8_t)kIdleState:
        default:
            /* State machine shall not be invoked again once it enters the idle state */
            err = kStatus_I2C_UnexpectedState;
            break;
    }

    return err;
}

/*!
 * brief Reusable routine to handle master interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  nonblocking API's interrupt handler routines to add special functionality.
 * param base The I2C peripheral base address.
 * param handle Pointer to the I2C master driver handle.
 */
void I2C_MasterTransferHandleIRQ(I2C_Type *base, i2c_master_handle_t *handle)
{
    bool isDone;
    status_t result;

    /* Don't do anything if we don't have a valid handle. */
    if (NULL == handle)
    {
        return;
    }

    result = I2C_RunTransferStateMachine(base, handle, &isDone);

    if ((result != kStatus_Success) || isDone)
    {
        /* Restore handle to idle state. */
        handle->state = (uint8_t)kIdleState;

        /* Disable internal IRQ enables. */
        I2C_DisableInterrupts(base, (uint32_t)kI2C_MasterIrqFlags);

        /* Invoke callback. */
        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }
}

static void I2C_SlaveInternalStateMachineReset(I2C_Type *base)
{
    I2C_SlaveEnable(base, false); /* clear SLVEN Slave enable bit */
}

static status_t I2C_SlaveDivVal(uint32_t srcClock_Hz, i2c_slave_bus_speed_t busSpeed, uint32_t *divVal)
{
    uint32_t dataSetupTime_ns;

    switch ((uint8_t)(busSpeed))
    {
        case (uint8_t)kI2C_SlaveStandardMode:
            dataSetupTime_ns = 250U;
            break;

        case (uint8_t)kI2C_SlaveFastMode:
            dataSetupTime_ns = 100U;
            break;

        case (uint8_t)kI2C_SlaveFastModePlus:
            dataSetupTime_ns = 50U;
            break;

        case (uint8_t)kI2C_SlaveHsMode:
            dataSetupTime_ns = 10U;
            break;

        default:
            dataSetupTime_ns = 0U;
            break;
    }

    if (0U == dataSetupTime_ns)
    {
        return kStatus_InvalidArgument;
    }

    /* divVal = (sourceClock_Hz / 1000000) * (dataSetupTime_ns / 1000) */
    *divVal = srcClock_Hz / 1000U;
    *divVal = (*divVal) * dataSetupTime_ns;
    *divVal = (*divVal) / 1000000U;

    if ((*divVal) > I2C_CLKDIV_DIVVAL_MASK)
    {
        *divVal = I2C_CLKDIV_DIVVAL_MASK;
    }

    return kStatus_Success;
}

static uint32_t I2C_SlavePollPending(I2C_Type *base)
{
    uint32_t stat;

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif
    do
    {
        stat = base->STAT;
#if I2C_RETRY_TIMES != 0U
        waitTimes--;
    } while ((0U == (stat & I2C_STAT_SLVPENDING_MASK)) && (waitTimes != 0U));

    if (waitTimes == 0U)
    {
        return (uint32_t)kStatus_I2C_Timeout;
    }
#else
    } while (0U == (stat & I2C_STAT_SLVPENDING_MASK));
#endif

    return stat;
}

static void I2C_SlaveInvokeEvent(I2C_Type *base, i2c_slave_handle_t *handle, i2c_slave_transfer_event_t event)
{
    uint32_t eventMask     = handle->transfer.eventMask;
    handle->transfer.event = event;
    if (((handle->callback) != NULL) && ((eventMask & (uint32_t)event) != 0U))
    {
        handle->callback(base, &handle->transfer, handle->userData);

        size_t txSize = handle->transfer.txSize;
        size_t rxSize = handle->transfer.rxSize;
        /* if after event callback we have data buffer (callback func has added new data), keep transfer busy */
        if (false == handle->isBusy)
        {
            if (((handle->transfer.txData != NULL) && (txSize != 0U)) ||
                ((handle->transfer.rxData != NULL) && (rxSize != 0U)))
            {
                handle->isBusy = true;
            }
        }

        /* Clear the transferred count now that we have a new buffer. */
        if ((event == kI2C_SlaveReceiveEvent) || (event == kI2C_SlaveTransmitEvent))
        {
            handle->transfer.transferredCount = 0;
        }
    }
}

static bool I2C_SlaveAddressIRQ(I2C_Type *base, i2c_slave_handle_t *handle)
{
    uint8_t addressByte0;
    size_t txSize;
    size_t rxSize;

    addressByte0 = (uint8_t)base->SLVDAT;

    /* store the matched address */
    handle->transfer.receivedAddress = addressByte0;

    /* R/nW */
    if ((addressByte0 & 1U) != 0U)
    {
        txSize = handle->transfer.txSize;
        /* if we have no data in this transfer, call callback to get new */
        if ((handle->transfer.txData == NULL) || (txSize == 0U))
        {
            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveTransmitEvent);
        }

        txSize = handle->transfer.txSize;
        /* NACK if we have no data in this transfer. */
        if ((handle->transfer.txData == NULL) || (txSize == 0U))
        {
            base->SLVCTL = I2C_SLVCTL_SLVNACK_MASK;
            return false;
        }

        /* master wants to read, so slave transmit is next state */
        handle->slaveFsm = kI2C_SlaveFsmTransmit;
    }
    else
    {
        rxSize = handle->transfer.rxSize;
        /* if we have no receive buffer in this transfer, call callback to get new */
        if ((handle->transfer.rxData == NULL) || (rxSize == 0U))
        {
            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveReceiveEvent);
        }

        rxSize = handle->transfer.rxSize;
        /* NACK if we have no data in this transfer */
        if ((handle->transfer.rxData == NULL) || (rxSize == 0U))
        {
            base->SLVCTL = I2C_SLVCTL_SLVNACK_MASK;
            return false;
        }

        /* master wants write, so slave receive is next state */
        handle->slaveFsm = kI2C_SlaveFsmReceive;
    }

    /* continue transaction */
    base->SLVCTL = I2C_SLVCTL_SLVCONTINUE_MASK;

    return true;
}

static status_t I2C_SlaveTransferNonBlockingInternal(I2C_Type *base,
                                                     i2c_slave_handle_t *handle,
                                                     const void *txData,
                                                     size_t txSize,
                                                     void *rxData,
                                                     size_t rxSize,
                                                     uint32_t eventMask)
{
    assert(handle != NULL);

    status_t status;
    status = kStatus_Success;

    /* Disable I2C IRQ sources while we configure stuff. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_SlaveIrqFlags);

    /* Return busy if another transaction is in progress. */
    if (handle->isBusy)
    {
        status = kStatus_I2C_Busy;
    }

    /* Save transfer into handle. */
    handle->transfer.txData           = (const uint8_t *)txData;
    handle->transfer.txSize           = txSize;
    handle->transfer.rxData           = (uint8_t *)rxData;
    handle->transfer.rxSize           = rxSize;
    handle->transfer.transferredCount = 0;
    handle->transfer.eventMask = eventMask | (uint32_t)kI2C_SlaveTransmitEvent | (uint32_t)kI2C_SlaveReceiveEvent;
    handle->isBusy             = true;

    /* Set the SLVEN bit to 1 in the CFG register. */
    I2C_SlaveEnable(base, true);

    /* Clear w1c flags. */
    base->STAT |= 0u;

    /* Enable I2C internal IRQ sources. */
    I2C_EnableInterrupts(base, (uint32_t)kI2C_SlaveIrqFlags);

    return status;
}

/*!
 * brief Starts accepting master read from slave requests.
 *
 * The function can be called in response to #kI2C_SlaveTransmitEvent callback to start a new slave Tx transfer
 * from within the transfer callback.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #i2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI2C_SlaveTransmitEvent and #kI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, you can pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The I2C peripheral base address.
 * param transfer Pointer to #i2c_slave_transfer_t structure.
 * param txData Pointer to data to send to master.
 * param txSize Size of txData in bytes.
 * param eventMask Bit mask formed by OR'ing together #i2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI2C_SlaveAllEvents to enable all events.
 *
 * retval kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
status_t I2C_SlaveSetSendBuffer(
    I2C_Type *base, volatile i2c_slave_transfer_t *transfer, const void *txData, size_t txSize, uint32_t eventMask)
{
    return I2C_SlaveTransferNonBlockingInternal(base, transfer->handle, txData, txSize, NULL, 0u, eventMask);
}

/*!
 * brief Starts accepting master write to slave requests.
 *
 * The function can be called in response to #kI2C_SlaveReceiveEvent callback to start a new slave Rx transfer
 * from within the transfer callback.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #i2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI2C_SlaveTransmitEvent and #kI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, you can pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The I2C peripheral base address.
 * param transfer Pointer to #i2c_slave_transfer_t structure.
 * param rxData Pointer to data to store data from master.
 * param rxSize Size of rxData in bytes.
 * param eventMask Bit mask formed by OR'ing together #i2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI2C_SlaveAllEvents to enable all events.
 *
 * retval kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
status_t I2C_SlaveSetReceiveBuffer(
    I2C_Type *base, volatile i2c_slave_transfer_t *transfer, void *rxData, size_t rxSize, uint32_t eventMask)
{
    return I2C_SlaveTransferNonBlockingInternal(base, transfer->handle, NULL, 0u, rxData, rxSize, eventMask);
}

/*!
 * brief Configures Slave Address n register.
 *
 * This function writes new value to Slave Address register.
 *
 * param base The I2C peripheral base address.
 * param addressRegister The module supports multiple address registers. The parameter determines which one shall be
 * changed.
 * param address The slave address to be stored to the address register for matching.
 * param addressDisable Disable matching of the specified address register.
 */
void I2C_SlaveSetAddress(I2C_Type *base,
                         i2c_slave_address_register_t addressRegister,
                         uint8_t address,
                         bool addressDisable)
{
    base->SLVADR[addressRegister] = I2C_SLVADR_SLVADR(address) | I2C_SLVADR_SADISABLE(addressDisable);
}

/*!
 * brief Provides a default configuration for the I2C slave peripheral.
 *
 * This function provides the following default configuration for the I2C slave peripheral:
 * code
 *  slaveConfig->enableSlave = true;
 *  slaveConfig->address0.disable = false;
 *  slaveConfig->address0.address = 0u;
 *  slaveConfig->address1.disable = true;
 *  slaveConfig->address2.disable = true;
 *  slaveConfig->address3.disable = true;
 *  slaveConfig->busSpeed = kI2C_SlaveStandardMode;
 * endcode
 *
 * After calling this function, override any settings  to customize the configuration,
 * prior to initializing the master driver with I2C_SlaveInit(). Be sure to override at least the a
 * address0.address member of the configuration structure with the desired slave address.
 *
 * param[out] slaveConfig User provided configuration structure that is set to default values. Refer to
 *      #i2c_slave_config_t.
 */
void I2C_SlaveGetDefaultConfig(i2c_slave_config_t *slaveConfig)
{
    assert(slaveConfig != NULL);

    i2c_slave_config_t mySlaveConfig = {0};

    /* default config enables slave address 0 match to general I2C call address zero */
    mySlaveConfig.enableSlave             = true;
    mySlaveConfig.address1.addressDisable = true;
    mySlaveConfig.address2.addressDisable = true;
    mySlaveConfig.address3.addressDisable = true;

    *slaveConfig = mySlaveConfig;
}

/*!
 * brief Initializes the I2C slave peripheral.
 *
 * This function enables the peripheral clock and initializes the I2C slave peripheral as described by the user
 * provided configuration.
 *
 * param base The I2C peripheral base address.
 * param slaveConfig User provided peripheral configuration. Use I2C_SlaveGetDefaultConfig() to get a set of defaults
 *      that you can override.
 * param srcClock_Hz Frequency in Hertz of the I2C functional clock. Used to calculate CLKDIV value to provide
 * enough
 *                       data setup time for master when slave stretches the clock.
 */
status_t I2C_SlaveInit(I2C_Type *base, const i2c_slave_config_t *slaveConfig, uint32_t srcClock_Hz)
{
    status_t status;
    uint32_t divVal = 0;

    /* configure data setup time used when slave stretches clock */
    status = I2C_SlaveDivVal(srcClock_Hz, slaveConfig->busSpeed, &divVal);
    if (kStatus_Success != status)
    {
        return status;
    }

    (void)FLEXCOMM_Init(base, FLEXCOMM_PERIPH_I2C);

    /* I2C Clock Divider register */
    base->CLKDIV = divVal;

    /* set Slave address */
    I2C_SlaveSetAddress(base, kI2C_SlaveAddressRegister0, slaveConfig->address0.address,
                        slaveConfig->address0.addressDisable);
    I2C_SlaveSetAddress(base, kI2C_SlaveAddressRegister1, slaveConfig->address1.address,
                        slaveConfig->address1.addressDisable);
    I2C_SlaveSetAddress(base, kI2C_SlaveAddressRegister2, slaveConfig->address2.address,
                        slaveConfig->address2.addressDisable);
    I2C_SlaveSetAddress(base, kI2C_SlaveAddressRegister3, slaveConfig->address3.address,
                        slaveConfig->address3.addressDisable);

    /* set Slave address 0 qual */
    base->SLVQUAL0 = I2C_SLVQUAL0_QUALMODE0(slaveConfig->qualMode) | I2C_SLVQUAL0_SLVQUAL0(slaveConfig->qualAddress);

    /* set Slave enable */
    base->CFG = I2C_CFG_SLVEN(slaveConfig->enableSlave);

    return status;
}

/*!
 * brief Deinitializes the I2C slave peripheral.
 *
 * This function disables the I2C slave peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * param base The I2C peripheral base address.
 */
void I2C_SlaveDeinit(I2C_Type *base)
{
    I2C_SlaveEnable(base, false);
}

/*!
 * brief Performs a polling send transfer on the I2C bus.
 *
 * The function executes blocking address phase and blocking data phase.
 *
 * param base  The I2C peripheral base address.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * return kStatus_Success Data has been sent.
 * return kStatus_Fail Unexpected slave state (master data write while master read from slave is expected).
 */
status_t I2C_SlaveWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize)
{
    const uint8_t *buf = txBuff;
    uint32_t stat;
    bool slaveAddress;
    bool slaveTransmit;

    /* Set the SLVEN bit to 1 in the CFG register. */
    I2C_SlaveEnable(base, true);

    /* wait for SLVPENDING */
    stat = I2C_SlavePollPending(base);
    if (stat == (uint32_t)kStatus_I2C_Timeout)
    {
        return kStatus_I2C_Timeout;
    }

    /* Get slave machine state */
    slaveAddress  = (((stat & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_ADDR);
    slaveTransmit = (((stat & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_TX);

    /* in I2C_SlaveSend() it shall be either slaveAddress or slaveTransmit */
    if (!(slaveAddress || slaveTransmit))
    {
        I2C_SlaveInternalStateMachineReset(base);
        return kStatus_Fail;
    }

    if (slaveAddress)
    {
        /* Acknowledge (ack) the address by setting SLVCONTINUE = 1 in the slave control register */
        base->SLVCTL = I2C_SLVCTL_SLVCONTINUE_MASK;

        /* wait for SLVPENDING */
        stat = I2C_SlavePollPending(base);
        if (stat == (uint32_t)kStatus_I2C_Timeout)
        {
            return kStatus_I2C_Timeout;
        }
    }

    /* send bytes up to txSize */
    while (txSize != 0U)
    {
        slaveTransmit = (((stat & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_TX);

        if (!slaveTransmit)
        {
            I2C_SlaveInternalStateMachineReset(base);
            return kStatus_Fail;
        }

        /* Write 8 bits of data to the SLVDAT register */
        base->SLVDAT = I2C_SLVDAT_DATA(*buf);

        /* continue transaction */
        base->SLVCTL = I2C_SLVCTL_SLVCONTINUE_MASK;

        /* advance counters and pointers for next data */
        buf++;
        txSize--;

        if (txSize != 0U)
        {
            /* wait for SLVPENDING */
            stat = I2C_SlavePollPending(base);
            if (stat == (uint32_t)kStatus_I2C_Timeout)
            {
                return kStatus_I2C_Timeout;
            }
        }
    }

    return kStatus_Success;
}

/*!
 * brief Performs a polling receive transfer on the I2C bus.
 *
 * The function executes blocking address phase and blocking data phase.
 *
 * param base  The I2C peripheral base address.
 * param rxBuff The pointer to the data to be transferred.
 * param rxSize The length in bytes of the data to be transferred.
 * return kStatus_Success Data has been received.
 * return kStatus_Fail Unexpected slave state (master data read while master write to slave is expected).
 */
status_t I2C_SlaveReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize)
{
    uint8_t *buf = rxBuff;
    uint32_t stat;
    bool slaveAddress;
    bool slaveReceive;

    /* Set the SLVEN bit to 1 in the CFG register. */
    I2C_SlaveEnable(base, true);

    /* wait for SLVPENDING */
    stat = I2C_SlavePollPending(base);
    if (stat == (uint32_t)kStatus_I2C_Timeout)
    {
        return kStatus_I2C_Timeout;
    }

    /* Get slave machine state */
    slaveAddress = (((stat & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_ADDR);
    slaveReceive = (((stat & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_RX);

    /* in I2C_SlaveReceive() it shall be either slaveAddress or slaveReceive */
    if (!(slaveAddress || slaveReceive))
    {
        I2C_SlaveInternalStateMachineReset(base);
        return kStatus_Fail;
    }

    if (slaveAddress)
    {
        /* Acknowledge (ack) the address by setting SLVCONTINUE = 1 in the slave control register */
        base->SLVCTL = I2C_SLVCTL_SLVCONTINUE_MASK;

        /* wait for SLVPENDING */
        stat = I2C_SlavePollPending(base);
        if (stat == (uint32_t)kStatus_I2C_Timeout)
        {
            return kStatus_I2C_Timeout;
        }
    }

    /* receive bytes up to rxSize */
    while (rxSize != 0U)
    {
        slaveReceive = (((stat & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_RX);

        if (!slaveReceive)
        {
            I2C_SlaveInternalStateMachineReset(base);
            return kStatus_Fail;
        }

        /* Read 8 bits of data from the SLVDAT register */
        *buf = (uint8_t)base->SLVDAT;

        /* continue transaction */
        base->SLVCTL = I2C_SLVCTL_SLVCONTINUE_MASK;

        /* advance counters and pointers for next data */
        buf++;
        rxSize--;

        if (rxSize != 0U)
        {
            /* wait for SLVPENDING */
            stat = I2C_SlavePollPending(base);
            if (stat == (uint32_t)kStatus_I2C_Timeout)
            {
                return kStatus_I2C_Timeout;
            }
        }
    }

    return kStatus_Success;
}

/*!
 * brief Creates a new handle for the I2C slave non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I2C_SlaveTransferAbort() API shall be called.
 *
 * param base The I2C peripheral base address.
 * param[out] handle Pointer to the I2C slave driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void I2C_SlaveTransferCreateHandle(I2C_Type *base,
                                   i2c_slave_handle_t *handle,
                                   i2c_slave_transfer_callback_t callback,
                                   void *userData)
{
    assert(handle != NULL);

    uint32_t instance;
    i2c_to_flexcomm_t handler;
    handler.i2c_slave_handler = I2C_SlaveTransferHandleIRQ;

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I2C_GetInstance(base);

    /* Save base and instance. */
    handle->callback = callback;
    handle->userData = userData;

    /* initialize fsm */
    handle->slaveFsm = kI2C_SlaveFsmAddressMatch;

    /* store pointer to handle into transfer struct */
    handle->transfer.handle = handle;

    FLEXCOMM_SetIRQHandler(base, handler.flexcomm_handler, handle);

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_SlaveIrqFlags);
    (void)EnableIRQ(s_i2cIRQ[instance]);
}

/*!
 * brief Starts accepting slave transfers.
 *
 * Call this API after calling I2C_SlaveInit() and I2C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and pass events to the
 * callback that was passed into the call to I2C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * If no slave Tx transfer is busy, a master read from slave request invokes #kI2C_SlaveTransmitEvent callback.
 * If no slave Rx transfer is busy, a master write to slave request invokes #kI2C_SlaveReceiveEvent callback.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #i2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI2C_SlaveTransmitEvent and #kI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, you can pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The I2C peripheral base address.
 * param handle Pointer to i2c_slave_handle_t structure which stores the transfer state.
 * param eventMask Bit mask formed by OR'ing together #i2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI2C_SlaveAllEvents to enable all events.
 *
 * retval kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
status_t I2C_SlaveTransferNonBlocking(I2C_Type *base, i2c_slave_handle_t *handle, uint32_t eventMask)
{
    return I2C_SlaveTransferNonBlockingInternal(base, handle, NULL, 0u, NULL, 0u, eventMask);
}

/*!
 * brief Gets the slave transfer remaining bytes during a interrupt non-blocking transfer.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_slave_handle_t structure.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */
status_t I2C_SlaveTransferGetCount(I2C_Type *base, i2c_slave_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (!handle->isBusy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* For an active transfer, just return the count from the handle. */
    *count = handle->transfer.transferredCount;

    return kStatus_Success;
}

/*!
 * brief Aborts the slave non-blocking transfers.
 * note This API could be called at any time to stop slave for handling the bus events.
 * param base The I2C peripheral base address.
 * param handle Pointer to i2c_slave_handle_t structure which stores the transfer state.
 * retval kStatus_Success
 * retval #kStatus_I2C_Idle
 */
void I2C_SlaveTransferAbort(I2C_Type *base, i2c_slave_handle_t *handle)
{
    /* Disable I2C IRQ sources while we configure stuff. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_SlaveIrqFlags);

    /* Set the SLVEN bit to 0 in the CFG register. */
    I2C_SlaveEnable(base, false);

    handle->isBusy          = false;
    handle->transfer.txSize = 0U;
    handle->transfer.rxSize = 0U;
}

/*!
 * brief Reusable routine to handle slave interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  non blocking API's interrupt handler routines to add special functionality.
 * param base The I2C peripheral base address.
 * param handle Pointer to i2c_slave_handle_t structure which stores the transfer state.
 */
void I2C_SlaveTransferHandleIRQ(I2C_Type *base, i2c_slave_handle_t *handle)
{
    uint32_t i2cStatus = base->STAT;
    uint8_t tmpdata;
    size_t txSize;
    size_t rxSize;

    if ((i2cStatus & I2C_STAT_SLVDESEL_MASK) != 0U)
    {
        I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveDeselectedEvent);
        I2C_SlaveClearStatusFlags(base, I2C_STAT_SLVDESEL_MASK);
    }

    /* SLVPENDING flag is cleared by writing I2C_SLVCTL_SLVCONTINUE_MASK to SLVCTL register */
    if ((i2cStatus & I2C_STAT_SLVPENDING_MASK) != 0U)
    {
        bool slaveAddress =
            (((i2cStatus & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) == (uint32_t)I2C_STAT_SLVST_ADDR);

        if (slaveAddress)
        {
            (void)I2C_SlaveAddressIRQ(base, handle);
            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveAddressMatchEvent);
        }
        else
        {
            switch (handle->slaveFsm)
            {
                case kI2C_SlaveFsmReceive:
                {
                    bool slaveReceive = (((i2cStatus & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) ==
                                         (uint32_t)I2C_STAT_SLVST_RX);

                    if (slaveReceive)
                    {
                        rxSize = handle->transfer.rxSize;
                        /* if we have no receive buffer in this transfer, call callback to get new */
                        if ((handle->transfer.rxData == NULL) || (rxSize == 0U))
                        {
                            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveReceiveEvent);
                        }

                        rxSize = handle->transfer.rxSize;
                        /* receive a byte */
                        if ((handle->transfer.rxData != NULL) && (rxSize != 0U))
                        {
                            /* continue transaction */
                            base->SLVCTL               = I2C_SLVCTL_SLVCONTINUE_MASK;
                            tmpdata                    = (uint8_t)base->SLVDAT;
                            *(handle->transfer.rxData) = tmpdata;
                            (handle->transfer.rxSize)--;
                            (handle->transfer.rxData)++;
                            (handle->transfer.transferredCount)++;
                        }

                        rxSize = handle->transfer.rxSize;
                        txSize = handle->transfer.txSize;
                        /* is this last transaction for this transfer? allow next transaction */
                        if ((0U == rxSize) && (0U == txSize))
                        {
                            handle->isBusy = false;
                            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveCompletionEvent);
                        }
                    }
                    else
                    {
                        base->SLVCTL = I2C_SLVCTL_SLVNACK_MASK;
                    }
                }
                break;

                case kI2C_SlaveFsmTransmit:
                {
                    bool slaveTransmit = (((i2cStatus & I2C_STAT_SLVSTATE_MASK) >> I2C_STAT_SLVSTATE_SHIFT) ==
                                          (uint32_t)I2C_STAT_SLVST_TX);

                    if (slaveTransmit)
                    {
                        txSize = handle->transfer.txSize;
                        /* if we have no data in this transfer, call callback to get new */
                        if ((handle->transfer.txData == NULL) || (txSize == 0U))
                        {
                            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveTransmitEvent);
                        }

                        txSize = handle->transfer.txSize;
                        /* transmit a byte */
                        if ((handle->transfer.txData != NULL) && (txSize != 0U))
                        {
                            base->SLVDAT = *(handle->transfer.txData);
                            /* continue transaction */
                            base->SLVCTL = I2C_SLVCTL_SLVCONTINUE_MASK;
                            (handle->transfer.txSize)--;
                            (handle->transfer.txData)++;
                            (handle->transfer.transferredCount)++;
                        }

                        rxSize = handle->transfer.rxSize;
                        txSize = handle->transfer.txSize;
                        /* is this last transaction for this transfer? allow next transaction */
                        if ((0U == rxSize) && (0U == txSize))
                        {
                            handle->isBusy = false;
                            I2C_SlaveInvokeEvent(base, handle, kI2C_SlaveCompletionEvent);
                        }
                    }
                    else
                    {
                        base->SLVCTL = I2C_SLVCTL_SLVNACK_MASK;
                    }
                }
                break;

                default:
                    /* incorrect state, slv_abort()? */
                    break;
            }
        }
    }
}
