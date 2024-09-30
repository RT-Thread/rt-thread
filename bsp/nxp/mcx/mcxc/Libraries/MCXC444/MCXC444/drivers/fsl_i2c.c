/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.i2c"
#endif

/*! @brief i2c transfer state. */
enum _i2c_transfer_states
{
    kIdleState             = 0x0U, /*!< I2C bus idle. */
    kCheckAddressState     = 0x1U, /*!< 7-bit address check state. */
    kSendCommandState      = 0x2U, /*!< Send command byte phase. */
    kSendDataState         = 0x3U, /*!< Send data transfer phase. */
    kReceiveDataBeginState = 0x4U, /*!< Receive data transfer phase begin. */
    kReceiveDataState      = 0x5U, /*!< Receive data transfer phase. */
};

/*! @brief Typedef for interrupt handler. */
typedef void (*i2c_isr_t)(I2C_Type *base, void *i2cHandle);

/*! @brief static variable to keep current configured baudrate. */
#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
static uint32_t g_baudrate = 100000;
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Set SCL/SDA hold time, this API receives SCL stop hold time, calculate the
 * closest SCL divider and MULT value for the SDA hold time, SCL start and SCL stop
 * hold time. To reduce the ROM size, SDA/SCL hold value mapping table is not provided,
 * assume SCL divider = SCL stop hold value *2 to get the closest SCL divider value and MULT
 * value, then the related SDA hold time, SCL start and SCL stop hold time is used.
 *
 * @param base I2C peripheral base address.
 * @param sourceClock_Hz I2C functional clock frequency in Hertz.
 * @param sclStopHoldTime_ns SCL stop hold time in ns.
 */
static void I2C_SetHoldTime(I2C_Type *base, uint32_t sclStopHoldTime_ns, uint32_t sourceClock_Hz);

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
/*!
 * @brief I2C master manually ack byte.
 *
 * @param base I2C peripheral base address.
 */
static void I2C_MasterAckByte(I2C_Type *base);
#endif

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

/*! @brief Pointers to i2c handles for each instance. */
static void *s_i2cHandle[FSL_FEATURE_SOC_I2C_COUNT];

/*! @brief SCL clock divider used to calculate baudrate. */
static const uint16_t s_i2cDividerTable[] = {
    20,  22,  24,  26,   28,   30,   34,   40,   28,   32,   36,   40,   44,   48,   56,   68,
    48,  56,  64,  72,   80,   88,   104,  128,  80,   96,   112,  128,  144,  160,  192,  240,
    160, 192, 224, 256,  288,  320,  384,  480,  320,  384,  448,  512,  576,  640,  768,  960,
    640, 768, 896, 1024, 1152, 1280, 1536, 1920, 1280, 1536, 1792, 2048, 2304, 2560, 3072, 3840};

/*! @brief Pointers to i2c IRQ number for each instance. */
static const IRQn_Type s_i2cIrqs[] = I2C_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to i2c clocks for each instance. */
static const clock_ip_name_t s_i2cClocks[] = I2C_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointer to master IRQ handler for each instance. */
static i2c_isr_t s_i2cMasterIsr;

/*! @brief Pointer to slave IRQ handler for each instance. */
static i2c_isr_t s_i2cSlaveIsr;

/*! @brief Pointers to i2c bases for each instance. */
static I2C_Type *const s_i2cBases[] = I2C_BASE_PTRS;
/*******************************************************************************
 * Codes
 ******************************************************************************/

/*!
 * brief Get instance number for I2C module.
 *
 * param base I2C peripheral base address.
 */
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

static void I2C_SetHoldTime(I2C_Type *base, uint32_t sclStopHoldTime_ns, uint32_t sourceClock_Hz)
{
    uint32_t multiplier;
    uint32_t computedSclHoldTime;
    uint32_t absError;
    uint32_t bestError = UINT32_MAX;
    uint32_t bestMult  = 0u;
    uint32_t bestIcr   = 0u;
    uint32_t u32flag   = 1u;
    uint8_t mult;
    uint8_t i;

    /* Search for the settings with the lowest error. Mult is the MULT field of the I2C_F register,
     * and ranges from 0-2. It selects the multiplier factor for the divider. */
    /* SDA hold time = bus period (s) * mul * SDA hold value. */
    /* SCL start hold time = bus period (s) * mul * SCL start hold value. */
    /* SCL stop hold time = bus period (s) * mul * SCL stop hold value. */

    for (mult = 0u; mult <= 2u; ++mult)
    {
        if (bestError == 0u)
        {
            break;
        }

        multiplier = u32flag << mult;

        /* Scan table to find best match. */
        for (i = 0u; i < sizeof(s_i2cDividerTable) / sizeof(s_i2cDividerTable[0]); ++i)
        {
            /* Assume SCL hold(stop) value = s_i2cDividerTable[i]/2. */
            computedSclHoldTime = ((multiplier * s_i2cDividerTable[i]) * 500000U) / (sourceClock_Hz / 1000U);
            absError = sclStopHoldTime_ns > computedSclHoldTime ? (sclStopHoldTime_ns - computedSclHoldTime) :
                                                                  (computedSclHoldTime - sclStopHoldTime_ns);

            if (absError < bestError)
            {
                bestMult  = mult;
                bestIcr   = i;
                bestError = absError;

                /* If the error is 0, then we can stop searching because we won't find a better match. */
                if (absError == 0u)
                {
                    break;
                }
            }
        }
    }

    /* Set frequency register based on best settings. */
    base->F = I2C_F_MULT(bestMult) | I2C_F_ICR(bestIcr);
}

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
static void I2C_MasterAckByte(I2C_Type *base)
{
    /* Clear the TXAK flag. */
    base->C1 &= ~(uint8_t)I2C_C1_TXAK_MASK;

    /* Delay at least one bit time */
    SDK_DelayAtLeastUs(1000000 / g_baudrate, SystemCoreClock);

    /* Do dummy read. */
    (void)base->D;
}
#endif

static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    status_t result           = kStatus_Success;
    i2c_direction_t direction = xfer->direction;

    /* Initialize the handle transfer information. */
    handle->transfer = *xfer;

    /* Save total transfer size. */
    handle->transferSize = xfer->dataSize;

    /* Initial transfer state. */
    if (handle->transfer.subaddressSize > 0u)
    {
        if (xfer->direction == kI2C_Read)
        {
            direction = kI2C_Write;
        }
    }

    handle->state = (uint8_t)kCheckAddressState;

    /* Clear all status before transfer. */
    I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

    /* Handle no start option. */
    if (0U != (handle->transfer.flags & (uint32_t)kI2C_TransferNoStartFlag))
    {
        /* No need to send start flag, directly go to send command or data */
        if (handle->transfer.subaddressSize > 0u)
        {
            handle->state = (uint8_t)kSendCommandState;
        }
        else
        {
            if (direction == kI2C_Write)
            {
                /* Next state, send data. */
                handle->state = (uint8_t)kSendDataState;
            }
            else
            {
                /* Only support write with no stop signal. */
                return kStatus_InvalidArgument;
            }
        }

        /* Wait for TCF bit and manually trigger tx interrupt. */
#if I2C_RETRY_TIMES != 0U
        uint32_t waitTimes = I2C_RETRY_TIMES;
        while ((0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag))
        {
        }
#endif
        I2C_MasterTransferHandleIRQ(base, handle);
    }
    /* If repeated start is requested, send repeated start. */
    else if (0U != (handle->transfer.flags & (uint32_t)kI2C_TransferRepeatedStartFlag))
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
    if (0U != (status & (uint32_t)kI2C_ArbitrationLostFlag))
    {
        /* Clear arbitration lost flag. */
        base->S = (uint8_t)kI2C_ArbitrationLostFlag;
        result  = kStatus_I2C_ArbitrationLost;
    }
    /* Check NAK */
    else if (0U != (status & (uint32_t)kI2C_ReceiveNakFlag))
    {
        result = kStatus_I2C_Nak;
    }
    else
    {
        /* Add this to fix MISRA C2012 rule15.7 issue: Empty else without comment. */
    }

    return result;
}

static status_t I2C_MasterTransferRunStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone)
{
    status_t result      = kStatus_Success;
    uint32_t statusFlags = base->S;
    *isDone              = false;
    uint32_t tmpDataSize = handle->transfer.dataSize;
    bool ignoreNak       = ((handle->state == (uint8_t)kSendDataState) && (tmpDataSize == 0U)) ||
                     ((handle->state == (uint8_t)kReceiveDataState) && (tmpDataSize == 1U));
    uint8_t tmpdata;

    /* Check & clear error flags. */
    result = I2C_CheckAndClearError(base, statusFlags);

    /* Ignore Nak when it's appeared for last byte. */
    if ((result == kStatus_I2C_Nak) && ignoreNak)
    {
        result = kStatus_Success;
    }

    /* Handle Check address state to check the slave address is Acked in slave
       probe application. */
    if (handle->state == (uint8_t)kCheckAddressState)
    {
        if (0U != (statusFlags & (uint8_t)kI2C_ReceiveNakFlag))
        {
            result = kStatus_I2C_Addr_Nak;
        }
        else
        {
            if (handle->transfer.subaddressSize > 0U)
            {
                handle->state = (uint8_t)kSendCommandState;
            }
            else
            {
                if (handle->transfer.direction == kI2C_Write)
                {
                    /* Next state, send data. */
                    handle->state = (uint8_t)kSendDataState;
                }
                else
                {
                    /* Next state, receive data begin. */
                    handle->state = (uint8_t)kReceiveDataBeginState;
                }
            }
        }
    }

    if (kStatus_Success != result)
    {
        return result;
    }

    /* Run state machine. */
    switch (handle->state)
    {
        /* Send I2C command. */
        case (uint8_t)kSendCommandState:
            if (0U != (handle->transfer.subaddressSize))
            {
                handle->transfer.subaddressSize--;
                base->D = (uint8_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));
            }
            else
            {
                if (handle->transfer.direction == kI2C_Write)
                {
                    /* Send first byte of data. */
                    if (handle->transfer.dataSize > 0U)
                    {
                        /* Next state, send data. */
                        handle->state = (uint8_t)kSendDataState;
                        base->D       = *handle->transfer.data;
                        handle->transfer.data++;
                        handle->transfer.dataSize--;
                    }
                    else
                    {
                        *isDone = true;
                    }
                }
                else
                {
                    /* Send repeated start and slave address. */
                    result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, kI2C_Read);

                    /* Next state, receive data begin. */
                    handle->state = (uint8_t)kReceiveDataBeginState;
                }
            }
            break;

        /* Send I2C data. */
        case (uint8_t)kSendDataState:
            /* Send one byte of data. */
            if (handle->transfer.dataSize > 0U)
            {
                base->D = *handle->transfer.data;
                handle->transfer.data++;
                handle->transfer.dataSize--;
            }
            else
            {
                *isDone = true;
            }
            break;

        /* Start I2C data receive. */
        case (uint8_t)kReceiveDataBeginState:

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
            base->SMB |= I2C_SMB_FACK_MASK;
#endif

            base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

            /* Read dummy to release the bus. */
            (void)base->D;

            if (handle->transfer.dataSize == 1U)
            {
                /* Issue NACK on read. */
                base->C1 |= I2C_C1_TXAK_MASK;
#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
                base->SMB &= ~(uint8_t)I2C_SMB_FACK_MASK;
#endif
            }

            /* Next state, receive data. */
            handle->state = (uint8_t)kReceiveDataState;
            break;

        /* Receive I2C data. */
        case (uint8_t)kReceiveDataState:
            /* Receive one byte of data. */
            if (0U != (handle->transfer.dataSize--))
            {
                if (handle->transfer.dataSize == 0U)
                {
                    *isDone = true;

                    /* Send stop if kI2C_TransferNoStop is not asserted. */
                    if (0U == (handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag))
                    {
                        result = I2C_MasterStop(base);
                    }
                    else
                    {
                        base->C1 |= I2C_C1_TX_MASK;
                    }
                }

                /* Read the data byte into the transfer buffer. */
                tmpdata                = base->D;
                *handle->transfer.data = tmpdata;
                handle->transfer.data++;

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
                if (handle->transfer.dataSize != 0U)
                {
                    I2C_MasterAckByte(base);
                }
#endif
                if (handle->transfer.dataSize == 1U)
                {
                    /* Issue NACK on read. */
                    base->C1 |= I2C_C1_TXAK_MASK;
#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
                    base->SMB &= ~(uint8_t)I2C_SMB_FACK_MASK;
#endif
                }
            }

            break;

        default:
            /* Add this to fix MISRA C2012 rule 16.4 issue: Empty default. */
            assert(false);
            break;
    }

    return result;
}

static void I2C_TransferCommonIRQHandler(I2C_Type *base, void *handle)
{
    uint8_t tmpS  = base->S;
    uint8_t tmpC1 = base->C1;

    /* Check if master interrupt. */
    if ((0U != (tmpC1 & I2C_C1_MST_MASK)) || (0U != (tmpS & (uint8_t)kI2C_ArbitrationLostFlag)))
    {
        s_i2cMasterIsr(base, handle);
    }
    else
    {
        s_i2cSlaveIsr(base, handle);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * brief Initializes the I2C peripheral. Call this API to ungate the I2C clock
 * and configure the I2C with master configuration.
 *
 * note This API should be called at the beginning of the application.
 * Otherwise, any operation to the I2C module can cause a hard fault
 * because the clock is not enabled. The configuration structure can be custom filled
 * or it can be set with default values by using the I2C_MasterGetDefaultConfig().
 * After calling this API, the master is ready to transfer.
 * This is an example.
 * code
 * i2c_master_config_t config = {
 * .enableMaster = true,
 * .enableStopHold = false,
 * .highDrive = false,
 * .baudRate_Bps = 100000,
 * .glitchFilterWidth = 0
 * };
 * I2C_MasterInit(I2C0, &config, 12000000U);
 * endcode
 *
 * param base I2C base pointer
 * param masterConfig A pointer to the master configuration structure
 * param srcClock_Hz I2C peripheral clock frequency in Hz
 */
void I2C_MasterInit(I2C_Type *base, const i2c_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert(NULL != masterConfig);
    assert(0U != srcClock_Hz);

    /* Temporary register for filter read. */
    uint8_t fltReg;
#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE
    uint8_t s2Reg;
#endif
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable I2C clock. */
    CLOCK_EnableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the module. */
    base->A1 = 0;
    base->F  = 0;
    base->C1 = 0;
    base->S  = 0xFFU;
    base->C2 = 0;
#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    base->FLT = 0x50U;
#elif defined(FSL_FEATURE_I2C_HAS_STOP_DETECT) && FSL_FEATURE_I2C_HAS_STOP_DETECT
    base->FLT = 0x40U;
#endif
    base->RA = 0;

    /* Disable I2C prior to configuring it. */
    base->C1 &= ~(uint8_t)(I2C_C1_IICEN_MASK);

    /* Clear all flags. */
    I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

    /* Configure baud rate. */
    I2C_MasterSetBaudRate(base, masterConfig->baudRate_Bps, srcClock_Hz);

    /* Read out the FLT register. */
    fltReg = base->FLT;

#if defined(FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF) && FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF
    /* Configure the stop / hold enable. */
    fltReg &= ~(uint8_t)(I2C_FLT_SHEN_MASK);
    fltReg |= I2C_FLT_SHEN(masterConfig->enableStopHold);
#endif

    /* Configure the glitch filter value. */
    fltReg &= ~(uint8_t)(I2C_FLT_FLT_MASK);
    fltReg |= I2C_FLT_FLT(masterConfig->glitchFilterWidth);

    /* Write the register value back to the filter register. */
    base->FLT = fltReg;

    /* Enable the I2C peripheral based on the configuration. */
    base->C1 = I2C_C1_IICEN(masterConfig->enableMaster);

    /* Enable/Disable double buffering. */
#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE
    s2Reg    = (uint8_t)(base->S2 & (~I2C_S2_DFEN_MASK));
    base->S2 = s2Reg | I2C_S2_DFEN(masterConfig->enableDoubleBuffering);
#endif
}

/*!
 * brief De-initializes the I2C master peripheral. Call this API to gate the I2C clock.
 * The I2C master module can't work unless the I2C_MasterInit is called.
 * param base I2C base pointer
 */
void I2C_MasterDeinit(I2C_Type *base)
{
    /* Disable I2C module. */
    I2C_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable I2C clock. */
    CLOCK_DisableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Sets the I2C master configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the I2C_MasterConfigure().
 * Use the initialized structure unchanged in the I2C_MasterConfigure() or modify
 * the structure before calling the I2C_MasterConfigure().
 * This is an example.
 * code
 * i2c_master_config_t config;
 * I2C_MasterGetDefaultConfig(&config);
 * endcode
 * param masterConfig A pointer to the master configuration structure.
 */
void I2C_MasterGetDefaultConfig(i2c_master_config_t *masterConfig)
{
    assert(NULL != masterConfig);

    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    /* Default baud rate at 100kbps. */
    masterConfig->baudRate_Bps = 100000U;

/* Default stop hold enable is disabled. */
#if defined(FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF) && FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF
    masterConfig->enableStopHold = false;
#endif

    /* Default glitch filter value is no filter. */
    masterConfig->glitchFilterWidth = 0U;

/* Default enable double buffering. */
#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE
    masterConfig->enableDoubleBuffering = true;
#endif

    /* Enable the I2C peripheral. */
    masterConfig->enableMaster = true;
}

/*!
 * brief Enables I2C interrupt requests.
 *
 * param base I2C base pointer
 * param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     arg kI2C_GlobalInterruptEnable
 *     arg kI2C_StopDetectInterruptEnable/kI2C_StartDetectInterruptEnable
 *     arg kI2C_SdaTimeoutInterruptEnable
 */
void I2C_EnableInterrupts(I2C_Type *base, uint32_t mask)
{
#ifdef I2C_HAS_STOP_DETECT
    uint8_t fltReg;
#endif

    if (0U != (mask & (uint32_t)kI2C_GlobalInterruptEnable))
    {
        base->C1 |= I2C_C1_IICIE_MASK;
    }

#if defined(FSL_FEATURE_I2C_HAS_STOP_DETECT) && FSL_FEATURE_I2C_HAS_STOP_DETECT
    if (0U != (mask & (uint32_t)kI2C_StopDetectInterruptEnable))
    {
        fltReg = base->FLT;

        /* Keep STOPF flag. */
        fltReg &= ~I2C_FLT_STOPF_MASK;

        /* Stop detect enable. */
        fltReg |= I2C_FLT_STOPIE_MASK;
        base->FLT = fltReg;
    }
#endif /* FSL_FEATURE_I2C_HAS_STOP_DETECT */

#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    if (0U != (mask & (uint32_t)kI2C_StartStopDetectInterruptEnable))
    {
        fltReg = base->FLT;

        /* Keep STARTF and STOPF flags. */
        fltReg &= ~(uint8_t)(I2C_FLT_STOPF_MASK | I2C_FLT_STARTF_MASK);

        /* Start and stop detect enable. */
        fltReg |= I2C_FLT_SSIE_MASK;
        base->FLT = fltReg;
    }
#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */
}

/*!
 * brief Disables I2C interrupt requests.
 *
 * param base I2C base pointer
 * param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     arg kI2C_GlobalInterruptEnable
 *     arg kI2C_StopDetectInterruptEnable/kI2C_StartDetectInterruptEnable
 *     arg kI2C_SdaTimeoutInterruptEnable
 */
void I2C_DisableInterrupts(I2C_Type *base, uint32_t mask)
{
    if (0U != (mask & (uint32_t)kI2C_GlobalInterruptEnable))
    {
        base->C1 &= ~(uint8_t)I2C_C1_IICIE_MASK;
    }

#if defined(FSL_FEATURE_I2C_HAS_STOP_DETECT) && FSL_FEATURE_I2C_HAS_STOP_DETECT
    if (0U != (mask & (uint32_t)kI2C_StopDetectInterruptEnable))
    {
        base->FLT &= ~(I2C_FLT_STOPIE_MASK | I2C_FLT_STOPF_MASK);
    }
#endif /* FSL_FEATURE_I2C_HAS_STOP_DETECT */

#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    if (0U != (mask & (uint32_t)kI2C_StartStopDetectInterruptEnable))
    {
        base->FLT &= ~(uint8_t)(I2C_FLT_SSIE_MASK | I2C_FLT_STOPF_MASK | I2C_FLT_STARTF_MASK);
    }
#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */
}

/*!
 * brief Sets the I2C master transfer baud rate.
 *
 * param base I2C base pointer
 * param baudRate_Bps the baud rate value in bps
 * param srcClock_Hz Source clock
 */
void I2C_MasterSetBaudRate(I2C_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t multiplier;
    uint32_t computedRate;
    uint32_t absError;
    uint32_t bestError = UINT32_MAX;
    uint32_t bestMult  = 0u;
    uint32_t bestIcr   = 0u;
    uint32_t u32flag   = 1u;
    uint8_t mult;
    uint8_t i;

    /* Search for the settings with the lowest error. Mult is the MULT field of the I2C_F register,
     * and ranges from 0-2. It selects the multiplier factor for the divider. */
    for (mult = 0u; mult <= 2u; ++mult)
    {
        if (bestError == 0u)
        {
            break;
        }

        multiplier = u32flag << mult;

        /* Scan table to find best match. */
        for (i = 0u; i < sizeof(s_i2cDividerTable) / sizeof(uint16_t); ++i)
        {
            computedRate = srcClock_Hz / (multiplier * s_i2cDividerTable[i]);
            absError     = baudRate_Bps > computedRate ? (baudRate_Bps - computedRate) : (computedRate - baudRate_Bps);

            if (absError < bestError)
            {
                bestMult  = mult;
                bestIcr   = i;
                bestError = absError;

                /* If the error is 0, then we can stop searching because we won't find a better match. */
                if (absError == 0u)
                {
                    break;
                }
            }
        }
    }

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
    g_baudrate = baudRate_Bps;
#endif
    /* Set frequency register based on best settings. */
    base->F = I2C_F_MULT(bestMult) | I2C_F_ICR(bestIcr);
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
    status_t result      = kStatus_Success;
    uint32_t statusFlags = I2C_MasterGetStatusFlags(base);

    /* Return an error if the bus is already in use. */
    if (0U != (statusFlags & (uint32_t)kI2C_BusBusyFlag))
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* Send the START signal. */
        base->C1 |= I2C_C1_MST_MASK | I2C_C1_TX_MASK;

#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING
#if I2C_RETRY_TIMES != 0U
        uint32_t waitTimes = I2C_RETRY_TIMES;
        while ((0U == (base->S2 & I2C_S2_EMPTY_MASK)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S2 & I2C_S2_EMPTY_MASK))
        {
        }
#endif
#endif /* FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING */

        base->D = (uint8_t)(((uint32_t)address) << 1U | ((direction == kI2C_Read) ? 1U : 0U));
    }

    return result;
}

/*!
 * brief Sends a REPEATED START on the I2C bus.
 *
 * param base I2C peripheral base pointer
 * param address 7-bit slave device address.
 * param direction Master transfer directions(transmit/receive).
 * retval kStatus_Success Successfully send the start signal.
 * retval kStatus_I2C_Busy Current bus is busy but not occupied by current I2C master.
 */
status_t I2C_MasterRepeatedStart(I2C_Type *base, uint8_t address, i2c_direction_t direction)
{
    status_t result = kStatus_Success;
    uint8_t savedMult;
    uint32_t statusFlags = I2C_MasterGetStatusFlags(base);
    uint8_t timeDelay    = 6;

    /* Return an error if the bus is already in use, but not by us. */
    if ((0U == (base->C1 & I2C_C1_MST_MASK)) && (0U != (statusFlags & (uint32_t)kI2C_BusBusyFlag)))
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        savedMult = base->F;
        base->F   = savedMult & (~(uint8_t)I2C_F_MULT_MASK);

        /* We are already in a transfer, so send a repeated start. */
        base->C1 |= I2C_C1_RSTA_MASK | I2C_C1_TX_MASK;

        /* Restore the multiplier factor. */
        base->F = savedMult;

        /* Add some delay to wait the Re-Start signal. */
        while (0U != (timeDelay--))
        {
            __NOP();
        }

#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING
#if I2C_RETRY_TIMES != 0U
        uint32_t waitTimes = I2C_RETRY_TIMES;
        while ((0U == (base->S2 & I2C_S2_EMPTY_MASK)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S2 & I2C_S2_EMPTY_MASK))
        {
        }
#endif
#endif /* FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING */

        base->D = (uint8_t)(((uint32_t)address) << 1U | ((direction == kI2C_Read) ? 1U : 0U));
    }

    return result;
}

/*!
 * brief Sends a STOP signal on the I2C bus.
 *
 * retval kStatus_Success Successfully send the stop signal.
 * retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterStop(I2C_Type *base)
{
    status_t result = kStatus_Success;

    /* Issue the STOP command on the bus. */
    base->C1 &= ~(uint8_t)(I2C_C1_MST_MASK | I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait until bus not busy. */
    while ((0U != (base->S & (uint8_t)kI2C_BusBusyFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }

    if (0U == waitTimes)
    {
        result = kStatus_I2C_Timeout;
    }
#else
    /* Wait until data transfer complete. */
    while (0U != (base->S & (uint8_t)kI2C_BusBusyFlag))
    {
    }
#endif

    return result;
}

/*!
 * brief Gets the I2C status flags.
 *
 * param base I2C base pointer
 * return status flag, use status flag to AND #_i2c_flags to get the related status.
 */
uint32_t I2C_MasterGetStatusFlags(I2C_Type *base)
{
    uint32_t statusFlags = base->S;

#ifdef I2C_HAS_STOP_DETECT
    /* Look up the STOPF bit from the filter register. */
    if (0U != (base->FLT & I2C_FLT_STOPF_MASK))
    {
        statusFlags |= (uint32_t)kI2C_StopDetectFlag;
    }
#endif

#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Look up the STARTF bit from the filter register. */
    if (0U != (base->FLT & I2C_FLT_STARTF_MASK))
    {
        statusFlags |= (uint32_t)kI2C_StartDetectFlag;
    }
#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */

    return statusFlags;
}

/*!
 * brief Performs a polling send transaction on the I2C bus.
 *
 * param base  The I2C peripheral base pointer.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * param flags Transfer control flag to decide whether need to send a stop, use kI2C_TransferDefaultFlag
 *  to issue a stop and kI2C_TransferNoStop to not send a stop.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_MasterWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize, uint32_t flags)
{
    status_t result     = kStatus_Success;
    uint8_t statusFlags = 0;

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait until the data register is ready for transmit. */
    while ((0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait until the data register is ready for transmit. */
    while (0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag))
    {
    }
#endif

    /* Clear the IICIF flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to transmit data. */
    base->C1 |= I2C_C1_TX_MASK;

    while (0U != (txSize--))
    {
        /* Send a byte of data. */
        base->D = *txBuff++;

#if I2C_RETRY_TIMES != 0U
        waitTimes = I2C_RETRY_TIMES;
        /* Wait until data transfer complete. */
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        /* Wait until data transfer complete. */
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif
        statusFlags = base->S;

        /* Clear the IICIF flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Check if arbitration lost or no acknowledgement (NAK), return failure status. */
        if (0U != (statusFlags & (uint8_t)kI2C_ArbitrationLostFlag))
        {
            base->S = (uint8_t)kI2C_ArbitrationLostFlag;
            result  = kStatus_I2C_ArbitrationLost;
        }

        if ((0U != (statusFlags & (uint8_t)kI2C_ReceiveNakFlag)) && (0U != txSize))
        {
            base->S = (uint8_t)kI2C_ReceiveNakFlag;
            result  = kStatus_I2C_Nak;
        }

        if (result != kStatus_Success)
        {
            /* Breaking out of the send loop. */
            break;
        }
    }

    if (((result == kStatus_Success) && (0U == (flags & (uint32_t)kI2C_TransferNoStopFlag))) ||
        (result == kStatus_I2C_Nak))
    {
        /* Clear the IICIF flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Send stop. */
        result = I2C_MasterStop(base);
    }

    return result;
}

/*!
 * brief Performs a polling receive transaction on the I2C bus.
 *
 * note The I2C_MasterReadBlocking function stops the bus before reading the final byte.
 * Without stopping the bus prior for the final read, the bus issues another read, resulting
 * in garbage data being read into the data register.
 *
 * param base I2C peripheral base pointer.
 * param rxBuff The pointer to the data to store the received data.
 * param rxSize The length in bytes of the data to be received.
 * param flags Transfer control flag to decide whether need to send a stop, use kI2C_TransferDefaultFlag
 *  to issue a stop and kI2C_TransferNoStop to not send a stop.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize, uint32_t flags)
{
    status_t result = kStatus_Success;

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait until the data register is ready for transmit. */
    while ((0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait until the data register is ready for transmit. */
    while (0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag))
    {
    }
#endif

    /* Clear the IICIF flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
    base->SMB |= I2C_SMB_FACK_MASK;
#endif

    /* Setup the I2C peripheral to receive data. */
    base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

    /* Do dummy read. */
    (void)base->D;

    if (rxSize == 1U)
    {
        /* Issue NACK on read. */
        base->C1 |= I2C_C1_TXAK_MASK;
#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
        base->SMB &= ~(uint8_t)I2C_SMB_FACK_MASK;
#endif
    }

    while (0U != (rxSize--))
    {
#if I2C_RETRY_TIMES != 0U
        waitTimes = I2C_RETRY_TIMES;
        /* Wait until data transfer complete. */
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        /* Wait until data transfer complete. */
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif

        if (rxSize == 0U)
        {
            if (0U == (flags & (uint32_t)kI2C_TransferNoStopFlag))
            {
                /* Issue STOP command before reading last byte. */
                result = I2C_MasterStop(base);
            }
            else
            {
                /* Change direction to Tx to avoid extra clocks. */
                base->C1 |= I2C_C1_TX_MASK;
            }
        }

        /* Clear the IICIF flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Read from the data register. */
        *rxBuff++ = base->D;

#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
        if (rxSize != 0U)
        {
            I2C_MasterAckByte(base);
        }
#endif

        if (rxSize == 1U)
        {
            base->C1 |= I2C_C1_TXAK_MASK;
#if defined(I2C_MASTER_FACK_CONTROL) && I2C_MASTER_FACK_CONTROL
            /* Issue NACK on read. */
            base->SMB &= ~(uint8_t)I2C_SMB_FACK_MASK;
#endif
        }
    }

    return result;
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
 */
status_t I2C_MasterTransferBlocking(I2C_Type *base, i2c_master_transfer_t *xfer)
{
    assert(NULL != xfer);

    i2c_direction_t direction = xfer->direction;
    status_t result           = kStatus_Success;

    /* Clear all status before transfer. */
    I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait until the data register is ready for transmit. */
    while ((0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait until the data register is ready for transmit. */
    while (0U == (base->S & (uint8_t)kI2C_TransferCompleteFlag))
    {
    }
#endif

    /* Change to send write address when it's a read operation with command. */
    if ((xfer->subaddressSize > 0U) && (xfer->direction == kI2C_Read))
    {
        direction = kI2C_Write;
    }

    /* Handle no start option, only support write with no start signal. */
    if (0U != (xfer->flags & (uint32_t)kI2C_TransferNoStartFlag))
    {
        if (direction == kI2C_Read)
        {
            return kStatus_InvalidArgument;
        }
    }
    /* If repeated start is requested, send repeated start. */
    else if (0U != (xfer->flags & (uint32_t)kI2C_TransferRepeatedStartFlag))
    {
        result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, direction);
    }
    else /* For normal transfer, send start. */
    {
        result = I2C_MasterStart(base, xfer->slaveAddress, direction);
    }

    if (0U == (xfer->flags & (uint32_t)kI2C_TransferNoStartFlag))
    {
        /* Return if error. */
        if (kStatus_Success != result)
        {
            return result;
        }

#if I2C_RETRY_TIMES != 0U
        waitTimes = I2C_RETRY_TIMES;
        /* Wait until data transfer complete. */
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        /* Wait until data transfer complete. */
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif
        /* Check if there's transfer error. */
        result = I2C_CheckAndClearError(base, base->S);

        /* Return if error. */
        if (kStatus_Success != result)
        {
            if (result == kStatus_I2C_Nak)
            {
                result = kStatus_I2C_Addr_Nak;

                (void)I2C_MasterStop(base);
            }

            return result;
        }
    }

    /* Send subaddress. */
    if (0U != (xfer->subaddressSize))
    {
        do
        {
            /* Clear interrupt pending flag. */
            base->S = (uint8_t)kI2C_IntPendingFlag;

            xfer->subaddressSize--;
            base->D = (uint8_t)((xfer->subaddress) >> (8U * xfer->subaddressSize));

#if I2C_RETRY_TIMES != 0U
            waitTimes = I2C_RETRY_TIMES;
            /* Wait until data transfer complete. */
            while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
            {
                waitTimes--;
            }
            if (0U == waitTimes)
            {
                return kStatus_I2C_Timeout;
            }
#else
            /* Wait until data transfer complete. */
            while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
            {
            }
#endif

            /* Check if there's transfer error. */
            result = I2C_CheckAndClearError(base, base->S);

            if (0 != result)
            {
                if (result == kStatus_I2C_Nak)
                {
                    (void)I2C_MasterStop(base);
                }

                return result;
            }

        } while (xfer->subaddressSize > 0u);

        if (xfer->direction == kI2C_Read)
        {
            /* Clear pending flag. */
            base->S = (uint8_t)kI2C_IntPendingFlag;

            /* Send repeated start and slave address. */
            result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, kI2C_Read);

            /* Return if error. */
            if (kStatus_Success != result)
            {
                return result;
            }

#if I2C_RETRY_TIMES != 0U
            waitTimes = I2C_RETRY_TIMES;
            /* Wait until data transfer complete. */
            while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
            {
                waitTimes--;
            }
            if (0U == waitTimes)
            {
                return kStatus_I2C_Timeout;
            }
#else
            /* Wait until data transfer complete. */
            while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
            {
            }
#endif

            /* Check if there's transfer error. */
            result = I2C_CheckAndClearError(base, base->S);

            if (kStatus_Success != result)
            {
                if (result == kStatus_I2C_Nak)
                {
                    result = kStatus_I2C_Addr_Nak;

                    (void)I2C_MasterStop(base);
                }

                return result;
            }
        }
    }

    /* Transmit data. */
    if (xfer->direction == kI2C_Write)
    {
        if (xfer->dataSize > 0U)
        {
            uint8_t *tmpData   = xfer->data;
            size_t tmpDataSize = xfer->dataSize;
            uint32_t tmpFlags  = xfer->flags;
            /* Send Data. */
            result = I2C_MasterWriteBlocking(base, tmpData, tmpDataSize, tmpFlags);
        }
        else if (0U == (xfer->flags & (uint32_t)kI2C_TransferNoStopFlag))
        {
            /* Send stop. */
            result = I2C_MasterStop(base);
        }
        else
        {
            /* Add this to fix MISRA C2012 rule15.7 issue: Empty else without comment. */
        }
    }

    /* Receive Data. */
    if ((xfer->dataSize > 0u) && (xfer->direction == kI2C_Read))
    {
        uint8_t *tmpData   = xfer->data;
        size_t tmpDataSize = xfer->dataSize;
        uint32_t tmpFlags  = xfer->flags;

        result = I2C_MasterReadBlocking(base, tmpData, tmpDataSize, tmpFlags);
    }

    return result;
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure to store the transfer state.
 * param callback pointer to user callback function.
 * param userData user parameter passed to the callback function.
 */
void I2C_MasterTransferCreateHandle(I2C_Type *base,
                                    i2c_master_handle_t *handle,
                                    i2c_master_transfer_callback_t callback,
                                    void *userData)
{
    assert(NULL != handle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Save the context in global variables to support the double weak mechanism. */
    s_i2cHandle[instance] = handle;

    /* Save master interrupt handler. */
    s_i2cMasterIsr = I2C_MasterTransferHandleIRQ;

    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_i2cIrqs[instance]);
}

/*!
 * brief Performs a master interrupt non-blocking transfer on the I2C bus.
 *
 * note Calling the API returns immediately after transfer initiates. The user needs
 * to call I2C_MasterGetTransferCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is not kStatus_I2C_Busy, the transfer
 * is finished.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * param xfer pointer to i2c_master_transfer_t structure.
 * retval kStatus_Success Successfully start the data transmission.
 * retval kStatus_I2C_Busy Previous transmission still not finished.
 * retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 */
status_t I2C_MasterTransferNonBlocking(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    assert(NULL != handle);
    assert(NULL != xfer);

    status_t result = kStatus_Success;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (handle->state != (uint8_t)kIdleState)
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
            I2C_EnableInterrupts(base, (uint32_t)kI2C_GlobalInterruptEnable);
        }
    }

    return result;
}

/*!
 * brief Aborts an interrupt non-blocking transfer early.
 *
 * note This API can be called at any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure which stores the transfer state
 * retval kStatus_I2C_Timeout Timeout during polling flag.
 * retval kStatus_Success Successfully abort the transfer.
 */
status_t I2C_MasterTransferAbort(I2C_Type *base, i2c_master_handle_t *handle)
{
    assert(NULL != handle);

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    /* Disable interrupt. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_GlobalInterruptEnable);

    /* Reset the state to idle. */
    handle->state = (uint8_t)kIdleState;

    /* If the bus is already in use, but not by us */
    if (0U == (base->C1 & I2C_C1_MST_MASK))
    {
        return kStatus_I2C_Busy;
    }

    /* Send STOP signal. */
    if (handle->transfer.direction == kI2C_Read)
    {
        base->C1 |= I2C_C1_TXAK_MASK;

#if I2C_RETRY_TIMES != 0U
        /* Wait until data transfer complete. */
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        /* Wait until data transfer complete. */
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif
        base->S = (uint8_t)kI2C_IntPendingFlag;

        base->C1 &= ~(uint8_t)(I2C_C1_MST_MASK | I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);
        (void)base->D;
    }
    else
    {
#if I2C_RETRY_TIMES != 0U
        /* Wait until data transfer complete. */
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        /* Wait until data transfer complete. */
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif
        base->S = (uint8_t)kI2C_IntPendingFlag;
        base->C1 &= ~(uint8_t)(I2C_C1_MST_MASK | I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);
    }

    return kStatus_Success;
}

/*!
 * brief Gets the master transfer status during a interrupt non-blocking transfer.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */
status_t I2C_MasterTransferGetCount(I2C_Type *base, i2c_master_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    *count = handle->transferSize - handle->transfer.dataSize;

    return kStatus_Success;
}

/*!
 * brief Master interrupt handler.
 *
 * param base I2C base pointer.
 * param i2cHandle pointer to i2c_master_handle_t structure.
 */
void I2C_MasterTransferHandleIRQ(I2C_Type *base, void *i2cHandle)
{
    assert(NULL != i2cHandle);

    i2c_master_handle_t *handle = (i2c_master_handle_t *)i2cHandle;
    status_t result             = kStatus_Success;
    bool isDone;

    /* Clear the interrupt flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;

    /* Check transfer complete flag. */
    result = I2C_MasterTransferRunStateMachine(base, handle, &isDone);

    if ((true == isDone) || (0 != result))
    {
        /* Send stop command if transfer done or received Nak. */
        if ((0U == (handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag)) || (result == kStatus_I2C_Nak) ||
            (result == kStatus_I2C_Addr_Nak))
        {
            /* Ensure stop command is a need. */
            if (0U != (base->C1 & I2C_C1_MST_MASK))
            {
                if (I2C_MasterStop(base) != kStatus_Success)
                {
                    result = kStatus_I2C_Timeout;
                }
            }
        }

        /* Restore handle to idle state. */
        handle->state = (uint8_t)kIdleState;

        /* Disable interrupt. */
        I2C_DisableInterrupts(base, (uint32_t)kI2C_GlobalInterruptEnable);

        /* Call the callback function after the function has completed. */
        if (NULL != (handle->completionCallback))
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }
}

/*!
 * brief Initializes the I2C peripheral. Call this API to ungate the I2C clock
 * and initialize the I2C with the slave configuration.
 *
 * note This API should be called at the beginning of the application.
 * Otherwise, any operation to the I2C module can cause a hard fault
 * because the clock is not enabled. The configuration structure can partly be set
 * with default values by I2C_SlaveGetDefaultConfig() or it can be custom filled by the user.
 * This is an example.
 * code
 * i2c_slave_config_t config = {
 * .enableSlave = true,
 * .enableGeneralCall = false,
 * .addressingMode = kI2C_Address7bit,
 * .slaveAddress = 0x1DU,
 * .enableWakeUp = false,
 * .enablehighDrive = false,
 * .enableBaudRateCtl = false,
 * .sclStopHoldTime_ns = 4000
 * };
 * I2C_SlaveInit(I2C0, &config, 12000000U);
 * endcode
 *
 * param base I2C base pointer
 * param slaveConfig A pointer to the slave configuration structure
 * param srcClock_Hz I2C peripheral clock frequency in Hz
 */
void I2C_SlaveInit(I2C_Type *base, const i2c_slave_config_t *slaveConfig, uint32_t srcClock_Hz)
{
    assert(NULL != slaveConfig);

    uint8_t tmpReg;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the module. */
    base->A1 = 0;
    base->F  = 0;
    base->C1 = 0;
    base->S  = 0xFFU;
    base->C2 = 0;
#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    base->FLT = 0x50U;
#elif defined(FSL_FEATURE_I2C_HAS_STOP_DETECT) && FSL_FEATURE_I2C_HAS_STOP_DETECT
    base->FLT = 0x40U;
#endif
    base->RA = 0;

    /* Configure addressing mode. */
    switch (slaveConfig->addressingMode)
    {
        case kI2C_Address7bit:
            base->A1 = (uint8_t)(((uint32_t)(slaveConfig->slaveAddress)) << 1U);
            break;

        case kI2C_RangeMatch:
            assert(slaveConfig->slaveAddress < slaveConfig->upperAddress);
            base->A1 = (uint8_t)(((uint32_t)(slaveConfig->slaveAddress)) << 1U);
            base->RA = (uint8_t)(((uint32_t)(slaveConfig->upperAddress)) << 1U);
            base->C2 |= I2C_C2_RMEN_MASK;
            break;

        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    /* Configure low power wake up feature. */
    tmpReg = base->C1;
    tmpReg &= ~(uint8_t)I2C_C1_WUEN_MASK;
    base->C1 = tmpReg | I2C_C1_WUEN(slaveConfig->enableWakeUp) | I2C_C1_IICEN(slaveConfig->enableSlave);

    /* Configure general call & baud rate control. */
    tmpReg = base->C2;
    tmpReg &= ~(uint8_t)(I2C_C2_SBRC_MASK | I2C_C2_GCAEN_MASK);
    tmpReg |= I2C_C2_SBRC(slaveConfig->enableBaudRateCtl) | I2C_C2_GCAEN(slaveConfig->enableGeneralCall);
    base->C2 = tmpReg;

/* Enable/Disable double buffering. */
#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE
    tmpReg   = (uint8_t)(base->S2 & (~I2C_S2_DFEN_MASK));
    base->S2 = tmpReg | I2C_S2_DFEN(slaveConfig->enableDoubleBuffering);
#endif

    /* Set hold time. */
    I2C_SetHoldTime(base, slaveConfig->sclStopHoldTime_ns, srcClock_Hz);
}

/*!
 * brief De-initializes the I2C slave peripheral. Calling this API gates the I2C clock.
 * The I2C slave module can't work unless the I2C_SlaveInit is called to enable the clock.
 * param base I2C base pointer
 */
void I2C_SlaveDeinit(I2C_Type *base)
{
    /* Disable I2C module. */
    I2C_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable I2C clock. */
    CLOCK_DisableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Sets the I2C slave configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the I2C_SlaveConfigure().
 * Modify fields of the structure before calling the I2C_SlaveConfigure().
 * This is an example.
 * code
 * i2c_slave_config_t config;
 * I2C_SlaveGetDefaultConfig(&config);
 * endcode
 * param slaveConfig A pointer to the slave configuration structure.
 */
void I2C_SlaveGetDefaultConfig(i2c_slave_config_t *slaveConfig)
{
    assert(NULL != slaveConfig);

    /* Initializes the configure structure to zero. */
    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    /* By default slave is addressed with 7-bit address. */
    slaveConfig->addressingMode = kI2C_Address7bit;

    /* General call mode is disabled by default. */
    slaveConfig->enableGeneralCall = false;

    /* Slave address match waking up MCU from low power mode is disabled. */
    slaveConfig->enableWakeUp = false;

    /* Independent slave mode baud rate at maximum frequency is disabled. */
    slaveConfig->enableBaudRateCtl = false;

/* Default enable double buffering. */
#if defined(FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE) && FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE
    slaveConfig->enableDoubleBuffering = true;
#endif

    /* Set default SCL stop hold time to 4us which is minimum requirement in I2C spec. */
    slaveConfig->sclStopHoldTime_ns = 4000;

    /* Enable the I2C peripheral. */
    slaveConfig->enableSlave = true;
}

/*!
 * brief Performs a polling send transaction on the I2C bus.
 *
 * param base  The I2C peripheral base pointer.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_SlaveWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize)
{
    status_t result = kStatus_Success;

#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Check start flag. */
    while (0U == (base->FLT & I2C_FLT_STARTF_MASK))
    {
    }
    /* Clear STARTF flag. */
    base->FLT |= I2C_FLT_STARTF_MASK;
    /* Clear the IICIF flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;
#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait until data transfer complete. */
    while ((0U == (base->S & (uint8_t)kI2C_AddressMatchFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait for address match flag. */
    while (0U == (base->S & (uint8_t)kI2C_AddressMatchFlag))
    {
    }
#endif
    /* Read dummy to release bus. */
    (void)base->D;

    result = I2C_MasterWriteBlocking(base, txBuff, txSize, (uint32_t)kI2C_TransferNoStopFlag);

    /* Switch to receive mode. */
    base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

    /* Read dummy to release bus. */
    (void)base->D;

    return result;
}

/*!
 * brief Performs a polling receive transaction on the I2C bus.
 *
 * param base I2C peripheral base pointer.
 * param rxBuff The pointer to the data to store the received data.
 * param rxSize The length in bytes of the data to be received.
 * retval kStatus_Success Successfully complete data receive.
 * retval kStatus_I2C_Timeout Wait status flag timeout.
 */
status_t I2C_SlaveReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize)
{
    status_t result = kStatus_Success;

/* Wait until address match. */
#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Check start flag. */
    while (0U == (base->FLT & I2C_FLT_STARTF_MASK))
    {
    }
    /* Clear STARTF flag. */
    base->FLT |= I2C_FLT_STARTF_MASK;
    /* Clear the IICIF flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;
#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait for address match and int pending flag. */
    while ((0U == (base->S & (uint8_t)kI2C_AddressMatchFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }

    waitTimes = I2C_RETRY_TIMES;
    while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
    {
        waitTimes--;
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait for address match and int pending flag. */
    while (0U == (base->S & (uint8_t)kI2C_AddressMatchFlag))
    {
    }
    while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
    {
    }
#endif

    /* Read dummy to release bus. */
    (void)base->D;

    /* Clear the IICIF flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to receive data. */
    base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK);

    while (0U != (rxSize--))
    {
#if I2C_RETRY_TIMES != 0U
        waitTimes = I2C_RETRY_TIMES;
        /* Wait until data transfer complete. */
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (0U == waitTimes)
        {
            return kStatus_I2C_Timeout;
        }
#else
        /* Wait until data transfer complete. */
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif
        /* Clear the IICIF flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Read from the data register. */
        *rxBuff++ = base->D;
    }

    return result;
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_slave_handle_t structure to store the transfer state.
 * param callback pointer to user callback function.
 * param userData user parameter passed to the callback function.
 */
void I2C_SlaveTransferCreateHandle(I2C_Type *base,
                                   i2c_slave_handle_t *handle,
                                   i2c_slave_transfer_callback_t callback,
                                   void *userData)
{
    assert(NULL != handle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Save the context in global variables to support the double weak mechanism. */
    s_i2cHandle[instance] = handle;

    /* Save slave interrupt handler. */
    s_i2cSlaveIsr = I2C_SlaveTransferHandleIRQ;

    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_i2cIrqs[instance]);
}

/*!
 * brief Starts accepting slave transfers.
 *
 * Call this API after calling the I2C_SlaveInit() and I2C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and passes events to the
 * callback that was passed into the call to I2C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #i2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI2C_SlaveTransmitEvent and #kLPI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The I2C peripheral base address.
 * param handle Pointer to #i2c_slave_handle_t structure which stores the transfer state.
 * param eventMask Bit mask formed by OR'ing together #i2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI2C_SlaveAllEvents to enable all events.
 *
 * retval #kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
status_t I2C_SlaveTransferNonBlocking(I2C_Type *base, i2c_slave_handle_t *handle, uint32_t eventMask)
{
    assert(NULL != handle);

    /* Check if the I2C bus is idle - if not return busy status. */
    if (true == handle->isBusy)
    {
        return kStatus_I2C_Busy;
    }
    else
    {
        /* Disable LPI2C IRQ sources while we configure stuff. */
        I2C_DisableInterrupts(base, (uint32_t)kIrqFlags);

        /* Clear transfer in handle. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Record that we're busy. */
        handle->isBusy = true;

        /* Set up event mask. tx and rx are always enabled. */
        handle->eventMask = eventMask | (uint32_t)kI2C_SlaveTransmitEvent | (uint32_t)kI2C_SlaveReceiveEvent |
                            (uint32_t)kI2C_SlaveGenaralcallEvent;

        /* Clear all flags. */
        I2C_SlaveClearStatusFlags(base, (uint32_t)kClearFlags);

        /* Enable I2C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
        I2C_EnableInterrupts(base, (uint32_t)kIrqFlags);
    }

    return kStatus_Success;
}

/*!
 * brief Aborts the slave transfer.
 *
 * note This API can be called at any time to stop slave for handling the bus events.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_slave_handle_t structure which stores the transfer state.
 */
void I2C_SlaveTransferAbort(I2C_Type *base, i2c_slave_handle_t *handle)
{
    assert(NULL != handle);

    if (true == handle->isBusy)
    {
        /* Disable interrupts. */
        I2C_DisableInterrupts(base, (uint32_t)kIrqFlags);

        /* Reset transfer info. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Reset the state to idle. */
        handle->isBusy = false;
    }
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
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (false == handle->isBusy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* For an active transfer, just return the count from the handle. */
    *count = handle->transfer.transferredCount;

    return kStatus_Success;
}

/*!
 * brief Slave interrupt handler.
 *
 * param base I2C base pointer.
 * param i2cHandle pointer to i2c_slave_handle_t structure which stores the transfer state
 */
void I2C_SlaveTransferHandleIRQ(I2C_Type *base, void *i2cHandle)
{
    assert(NULL != i2cHandle);

    uint16_t status;
    bool doTransmit            = false;
    i2c_slave_handle_t *handle = (i2c_slave_handle_t *)i2cHandle;
    i2c_slave_transfer_t *xfer;
    size_t tmpDataSize = 0;

    status = (uint16_t)I2C_SlaveGetStatusFlags(base);
    xfer   = &(handle->transfer);

#ifdef I2C_HAS_STOP_DETECT
    /* Check stop flag. */
    if (0U != (status & (uint16_t)kI2C_StopDetectFlag))
    {
        I2C_MasterClearStatusFlags(base, (uint32_t)kI2C_StopDetectFlag);

        /* Clear the interrupt flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Call slave callback if this is the STOP of the transfer. */
        if (true == handle->isBusy)
        {
            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->isBusy         = false;

            if ((0U != (handle->eventMask & (uint32_t)xfer->event)) && (NULL != handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }

        if (0U == (status & (uint16_t)kI2C_AddressMatchFlag))
        {
            return;
        }
    }
#endif /* I2C_HAS_STOP_DETECT */

#if defined(FSL_FEATURE_I2C_HAS_START_STOP_DETECT) && FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Check start flag. */
    if (0U != (status & (uint16_t)kI2C_StartDetectFlag))
    {
        I2C_MasterClearStatusFlags(base, (uint32_t)kI2C_StartDetectFlag);

        /* Clear the interrupt flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        xfer->event = kI2C_SlaveStartEvent;

        if ((0U != (handle->eventMask & (uint32_t)xfer->event)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }

        if (0U == (status & (uint16_t)kI2C_AddressMatchFlag))
        {
            return;
        }
    }
#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */

    /* Clear the interrupt flag. */
    base->S = (uint8_t)kI2C_IntPendingFlag;

    /* Check NAK */
    if (0U != (status & (uint16_t)kI2C_ReceiveNakFlag))
    {
        /* Set receive mode. */
        base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

        /* Read dummy. */
        (void)base->D;

        if (handle->transfer.dataSize != 0u)
        {
            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_I2C_Nak;
            handle->isBusy         = false;

            if ((0U != (handle->eventMask & (uint32_t)xfer->event)) && (NULL != handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
        else
        {
#ifndef I2C_HAS_STOP_DETECT
            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->isBusy         = false;

            if ((0U != (handle->eventMask & (uint32_t)xfer->event)) && (NULL != handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
#endif /* !FSL_FEATURE_I2C_HAS_START_STOP_DETECT or !FSL_FEATURE_I2C_HAS_STOP_DETECT */
        }
    }
    /* Check address match. */
    else if (0U != (status & (uint16_t)kI2C_AddressMatchFlag))
    {
        handle->isBusy = true;
        xfer->event    = kI2C_SlaveAddressMatchEvent;

        /* Slave transmit, master reading from slave. */
        if (0U != (status & (uint16_t)kI2C_TransferDirectionFlag))
        {
            /* Change direction to send data. */
            base->C1 |= I2C_C1_TX_MASK;

            doTransmit = true;
        }
        else
        {
            /* Slave receive, master writing to slave. */
            base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

            /* Read dummy to release the bus and check the address master issued. */
            if (base->D == 0u)
            {
                xfer->event = kI2C_SlaveGenaralcallEvent;
            }
        }

        if ((0U != (handle->eventMask & (uint32_t)xfer->event)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }
    /* Check transfer complete flag. */
    else if (0U != (status & (uint16_t)kI2C_TransferCompleteFlag))
    {
        /* Slave transmit, master reading from slave. */
        if (0U != (status & (uint16_t)kI2C_TransferDirectionFlag))
        {
            doTransmit = true;
        }
        else
        {
            tmpDataSize = xfer->dataSize;
            /* If we're out of data, invoke callback to get more. */
            if ((NULL == xfer->data) || (0U == tmpDataSize))
            {
                xfer->event = kI2C_SlaveReceiveEvent;

                if (NULL != handle->callback)
                {
                    handle->callback(base, xfer, handle->userData);
                }

                /* Clear the transferred count now that we have a new buffer. */
                xfer->transferredCount = 0;
            }

            /* Slave receive, master writing to slave. */
            uint8_t data = base->D;

            if (0U != (handle->transfer.dataSize))
            {
                /* Receive data. */
                *handle->transfer.data++ = data;
                handle->transfer.dataSize--;
                xfer->transferredCount++;
                if (0U == handle->transfer.dataSize)
                {
#ifndef I2C_HAS_STOP_DETECT
                    xfer->event            = kI2C_SlaveCompletionEvent;
                    xfer->completionStatus = kStatus_Success;
                    handle->isBusy         = false;

                    /* Proceed receive complete event. */
                    if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
                    {
                        handle->callback(base, xfer, handle->userData);
                    }
#endif /* !FSL_FEATURE_I2C_HAS_START_STOP_DETECT or !FSL_FEATURE_I2C_HAS_STOP_DETECT */
                }
            }
        }
    }
    else
    {
        /* Read dummy to release bus. */
        (void)base->D;
    }

    /* Send data if there is the need. */
    if (doTransmit)
    {
        tmpDataSize = xfer->dataSize;
        /* If we're out of data, invoke callback to get more. */
        if ((NULL == xfer->data) || (0U == tmpDataSize))
        {
            xfer->event = kI2C_SlaveTransmitEvent;

            if (NULL != handle->callback)
            {
                handle->callback(base, xfer, handle->userData);
            }

            /* Clear the transferred count now that we have a new buffer. */
            xfer->transferredCount = 0;
        }

        if (0U != (handle->transfer.dataSize))
        {
            /* Send data. */
            base->D = *handle->transfer.data++;
            handle->transfer.dataSize--;
            xfer->transferredCount++;
        }
        else
        {
            /* Switch to receive mode. */
            base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

            /* Read dummy to release bus. */
            (void)base->D;

#ifndef I2C_HAS_STOP_DETECT
            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->isBusy         = false;

            /* Proceed txdone event. */
            if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
            {
                handle->callback(base, xfer, handle->userData);
            }
#endif /* !FSL_FEATURE_I2C_HAS_START_STOP_DETECT or !FSL_FEATURE_I2C_HAS_STOP_DETECT */
        }
    }
}

#if defined(FSL_FEATURE_I2C_HAS_SHARED_IRQ0_IRQ1) && FSL_FEATURE_I2C_HAS_SHARED_IRQ0_IRQ1
void I2C0_I2C1_DriverIRQHandler(void);
void I2C0_I2C1_DriverIRQHandler(void)
{
    for (uint32_t instance = 0U; instance < 2U; instance++)
    {
        if (s_i2cHandle[instance] != NULL)
        {
            I2C_TransferCommonIRQHandler(s_i2cBases[instance], s_i2cHandle[instance]);
        }
    }
}
#else
#if defined(I2C0)
void I2C0_DriverIRQHandler(void);
void I2C0_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C0, s_i2cHandle[0]);
}
#endif

#if defined(I2C1)
void I2C1_DriverIRQHandler(void);
void I2C1_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C1, s_i2cHandle[1]);
}
#endif
#endif

#if defined(I2C2)
void I2C2_DriverIRQHandler(void);
void I2C2_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C2, s_i2cHandle[2]);
}
#endif

#if defined(I2C3)
void I2C3_DriverIRQHandler(void);
void I2C3_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C3, s_i2cHandle[3]);
}
#endif
