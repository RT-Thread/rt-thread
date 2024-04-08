/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexio_i2c_master.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexio_i2c_master"
#endif

/*! @brief  FLEXIO I2C transfer state */
enum _flexio_i2c_master_transfer_states
{
    kFLEXIO_I2C_Idle             = 0x0U, /*!< I2C bus idle */
    kFLEXIO_I2C_Start            = 0x1U, /*!< I2C start phase */
    kFLEXIO_I2C_SendCommand      = 0x2U, /*!< Send command byte phase */
    kFLEXIO_I2C_SendData         = 0x3U, /*!< Send data transfer phase*/
    kFLEXIO_I2C_ReceiveDataBegin = 0x4U, /*!< Receive data begin transfer phase*/
    kFLEXIO_I2C_ReceiveData      = 0x5U, /*!< Receive data transfer phase*/
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Set up master transfer, send slave address and decide the initial
 * transfer state.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param transfer pointer to flexio_i2c_master_transfer_t structure
 */
static status_t FLEXIO_I2C_MasterTransferInitStateMachine(FLEXIO_I2C_Type *base,
                                                          flexio_i2c_master_handle_t *handle,
                                                          flexio_i2c_master_transfer_t *xfer);

/*!
 * @brief Master run transfer state machine to perform a byte of transfer.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param statusFlags flexio i2c hardware status
 * @retval kStatus_Success Successfully run state machine
 * @retval kStatus_FLEXIO_I2C_Nak Receive Nak during transfer
 */
static status_t FLEXIO_I2C_MasterTransferRunStateMachine(FLEXIO_I2C_Type *base,
                                                         flexio_i2c_master_handle_t *handle,
                                                         uint32_t statusFlags);

/*!
 * @brief Complete transfer, disable interrupt and call callback.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param status flexio transfer status
 */
static void FLEXIO_I2C_MasterTransferComplete(FLEXIO_I2C_Type *base,
                                              flexio_i2c_master_handle_t *handle,
                                              status_t status);

/*!
 * @brief introduce function FLEXIO_I2C_MasterTransferStateMachineStart.
 * This function was deal with Initial state, i2c start state.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 */
static void FLEXIO_I2C_MasterTransferStateMachineStart(FLEXIO_I2C_Type *base, flexio_i2c_master_handle_t *handle);

/*!
 * @brief introduce function FLEXIO_I2C_MasterTransferStateMachineSendCommand.
 * This function was deal with Check address only needed for transfer with subaddress .
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param statusFlags flexio i2c hardware status
 *
 * @return default is true when No abnormality.
 * @return false when time out.
 */
static bool FLEXIO_I2C_MasterTransferStateMachineSendCommand(FLEXIO_I2C_Type *base,
                                                             flexio_i2c_master_handle_t *handle,
                                                             uint32_t statusFlags);

/*!
 * @brief introduce function FLEXIO_I2C_MasterTransferStateMachineSendData.
 * This function was deal with Send command byte.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param statusFlags flexio i2c hardware status
 *
 * @return default is true when No abnormality.
 * @return false when time out.
 */
static bool FLEXIO_I2C_MasterTransferStateMachineSendData(FLEXIO_I2C_Type *base,
                                                          flexio_i2c_master_handle_t *handle,
                                                          uint32_t statusFlags);

/*!
 * @brief introduce function FLEXIO_I2C_MasterTransferStateMachineReceiveDataBegin.
 * This function was deal with Receive Data Begin.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param statusFlags flexio i2c hardware status
 *
 * @return default is true when No abnormality.
 * @return false when time out.
 */
static bool FLEXIO_I2C_MasterTransferStateMachineReceiveDataBegin(FLEXIO_I2C_Type *base,
                                                                  flexio_i2c_master_handle_t *handle,
                                                                  uint32_t statusFlags);

/*!
 * @brief introduce function Case_kFLEXIO_I2C_ReceiveDataBegin.
 * This function was deal with Receive Data.
 *
 * @param base pointer to FLEXIO_I2C_Type structure
 * @param handle pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * @param statusFlags flexio i2c hardware status
 *
 * @return default is kStatus_Success when No abnormality.
 * @return kStatus_FLEXIO_I2C_Nak when ReceiveNakFlag is not set.
 * @return kStatus_FLEXIO_I2C_Timeout when time out.
 */
static status_t FLEXIO_I2C_MasterTransferStateMachineReceiveData(FLEXIO_I2C_Type *base,
                                                                 flexio_i2c_master_handle_t *handle,
                                                                 uint32_t statusFlags);

/*******************************************************************************
 * Codes
 ******************************************************************************/

static uint32_t FLEXIO_I2C_GetInstance(FLEXIO_I2C_Type *base)
{
    return FLEXIO_GetInstance(base->flexioBase);
}

static status_t FLEXIO_I2C_MasterTransferInitStateMachine(FLEXIO_I2C_Type *base,
                                                          flexio_i2c_master_handle_t *handle,
                                                          flexio_i2c_master_transfer_t *xfer)
{
    bool needRestart;
    uint32_t byteCount;

    /* Init the handle member. */
    handle->transfer.slaveAddress   = xfer->slaveAddress;
    handle->transfer.direction      = xfer->direction;
    handle->transfer.subaddress     = xfer->subaddress;
    handle->transfer.subaddressSize = xfer->subaddressSize;
    handle->transfer.data           = xfer->data;
    handle->transfer.dataSize       = xfer->dataSize;
    handle->transfer.flags          = xfer->flags;
    handle->transferSize            = xfer->dataSize;

    /* Initial state, i2c start state. */
    handle->state = (uint8_t)kFLEXIO_I2C_Start;

    /* Clear all status before transfer. */
    FLEXIO_I2C_MasterClearStatusFlags(base, (uint32_t)kFLEXIO_I2C_ReceiveNakFlag);

    /* Calculate whether need to send re-start. */
    needRestart         = (handle->transfer.subaddressSize != 0U) && (handle->transfer.direction == kFLEXIO_I2C_Read);
    handle->needRestart = needRestart;

    /* Calculate total byte count in a frame. */
    byteCount = 1U;

    if (!needRestart)
    {
        byteCount += handle->transfer.dataSize;
    }

    if (handle->transfer.subaddressSize != 0U)
    {
        byteCount += handle->transfer.subaddressSize;
    }

    /* Configure data count. */
    if (FLEXIO_I2C_MasterSetTransferCount(base, (uint16_t)byteCount) != kStatus_Success)
    {
        return kStatus_InvalidArgument;
    }

    /* Configure timer1 disable condition. */
    uint32_t tmpConfig = base->flexioBase->TIMCFG[base->timerIndex[1]];
    tmpConfig &= ~FLEXIO_TIMCFG_TIMDIS_MASK;
    tmpConfig |= FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnPreTimerDisable);
    base->flexioBase->TIMCFG[base->timerIndex[1]] = tmpConfig;

#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
    while ((0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0]))) &&
           (0U != --waitTimes))
    {
    }
    if (0U == waitTimes)
    {
        return kStatus_FLEXIO_I2C_Timeout;
    }
#else
    while (0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0])))
    {
    }
#endif

    return kStatus_Success;
}

static void FLEXIO_I2C_MasterTransferStateMachineStart(FLEXIO_I2C_Type *base, flexio_i2c_master_handle_t *handle)
{
    if (handle->needRestart)
    {
        FLEXIO_I2C_MasterStart(base, handle->transfer.slaveAddress, kFLEXIO_I2C_Write);
    }
    else
    {
        FLEXIO_I2C_MasterStart(base, handle->transfer.slaveAddress, handle->transfer.direction);
    }
    if (handle->transfer.subaddressSize == 0U)
    {
        if (handle->transfer.direction == kFLEXIO_I2C_Write)
        {
            /* Next state, send data. */
            handle->state = (uint8_t)kFLEXIO_I2C_SendData;
        }
        else
        {
            /* Next state, receive data begin. */
            handle->state = (uint8_t)kFLEXIO_I2C_ReceiveDataBegin;
        }
    }
    else
    {
        /* Next state, send command byte. */
        handle->state = (uint8_t)kFLEXIO_I2C_SendCommand;
    }
}

static bool FLEXIO_I2C_MasterTransferStateMachineSendCommand(FLEXIO_I2C_Type *base,
                                                             flexio_i2c_master_handle_t *handle,
                                                             uint32_t statusFlags)
{
    if ((statusFlags & (uint32_t)kFLEXIO_I2C_TxEmptyFlag) != 0U)
    {
        if (handle->transfer.subaddressSize > 0U)
        {
            handle->transfer.subaddressSize--;
            FLEXIO_I2C_MasterWriteByte(base, ((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize)));

            if (handle->transfer.subaddressSize == 0U)
            {
                /* Load re-start in advance. */
                if (handle->transfer.direction == kFLEXIO_I2C_Read)
                {
#if I2C_RETRY_TIMES
                    while ((0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0]))) &&
                           (0U != --waitTimes))
                    {
                    }
                    if (0U == waitTimes)
                    {
                        return false;
                    }
#else
                    while (0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0])))
                    {
                    }
#endif
                    FLEXIO_I2C_MasterRepeatedStart(base);
                }
            }
        }
        else
        {
            if (handle->transfer.direction == kFLEXIO_I2C_Write)
            {
                /* Send first byte of data. */
                if (handle->transfer.dataSize > 0U)
                {
                    /* Next state, send data. */
                    handle->state = (uint8_t)kFLEXIO_I2C_SendData;

                    FLEXIO_I2C_MasterWriteByte(base, *handle->transfer.data);
                    handle->transfer.data++;
                    handle->transfer.dataSize--;
                }
                else
                {
                    FLEXIO_I2C_MasterStop(base);

#if I2C_RETRY_TIMES
                    while ((0U == (FLEXIO_I2C_MasterGetStatusFlags(base) & (uint32_t)kFLEXIO_I2C_RxFullFlag)) &&
                           (0U != --waitTimes))
                    {
                    }
                    if (0U == waitTimes)
                    {
                        return false;
                    }
#else
                    while (0U == (FLEXIO_I2C_MasterGetStatusFlags(base) & (uint32_t)kFLEXIO_I2C_RxFullFlag))
                    {
                    }
#endif
                    (void)FLEXIO_I2C_MasterReadByte(base);

                    handle->state = (uint8_t)kFLEXIO_I2C_Idle;
                }
            }
            else
            {
                (void)FLEXIO_I2C_MasterSetTransferCount(base, (uint16_t)(handle->transfer.dataSize + 1U));
                /* Delay at least one clock cycle so that the restart setup time is up to spec standard. */
                SDK_DelayAtLeastUs(1000000UL / base->baudrate, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
                FLEXIO_I2C_MasterStart(base, handle->transfer.slaveAddress, kFLEXIO_I2C_Read);

                /* Next state, receive data begin. */
                handle->state = (uint8_t)kFLEXIO_I2C_ReceiveDataBegin;
            }
        }
    }
    return true;
}

static bool FLEXIO_I2C_MasterTransferStateMachineSendData(FLEXIO_I2C_Type *base,
                                                          flexio_i2c_master_handle_t *handle,
                                                          uint32_t statusFlags)
{
    if ((statusFlags & (uint32_t)kFLEXIO_I2C_TxEmptyFlag) != 0U)
    {
        /* Send one byte of data. */
        if (handle->transfer.dataSize > 0U)
        {
            FLEXIO_I2C_MasterWriteByte(base, *handle->transfer.data);

            handle->transfer.data++;
            handle->transfer.dataSize--;
        }
        else
        {
            FLEXIO_I2C_MasterStop(base);

#if I2C_RETRY_TIMES
            while ((0U == (FLEXIO_I2C_MasterGetStatusFlags(base) & (uint32_t)kFLEXIO_I2C_RxFullFlag)) &&
                   (0U != --waitTimes))
            {
            }
            if (0U == waitTimes)
            {
                return false;
            }
#else
            while (0U == (FLEXIO_I2C_MasterGetStatusFlags(base) & (uint32_t)kFLEXIO_I2C_RxFullFlag))
            {
            }
#endif
            (void)FLEXIO_I2C_MasterReadByte(base);

            handle->state = (uint8_t)kFLEXIO_I2C_Idle;
        }
    }
    return true;
}

static bool FLEXIO_I2C_MasterTransferStateMachineReceiveDataBegin(FLEXIO_I2C_Type *base,
                                                                  flexio_i2c_master_handle_t *handle,
                                                                  uint32_t statusFlags)
{
    if ((statusFlags & (uint32_t)kFLEXIO_I2C_RxFullFlag) != 0U)
    {
        handle->state = (uint8_t)kFLEXIO_I2C_ReceiveData;
        /* Send nak at the last receive byte. */
        if (handle->transfer.dataSize == 1U)
        {
            FLEXIO_I2C_MasterEnableAck(base, false);
#if I2C_RETRY_TIMES
            while ((0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0]))) &&
                   (0U != --waitTimes))
            {
            }
            if (0U == waitTimes)
            {
                return false;
            }
#else
            while (0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0])))
            {
            }
#endif
            FLEXIO_I2C_MasterStop(base);
        }
        else
        {
            FLEXIO_I2C_MasterEnableAck(base, true);
        }
    }
    else if ((statusFlags & (uint32_t)kFLEXIO_I2C_TxEmptyFlag) != 0U)
    {
        /* Read one byte of data. */
        FLEXIO_I2C_MasterWriteByte(base, 0xFFFFFFFFU);
    }
    else
    {
        ; /* Avoid MISRA 2012 rule 15.7 */
    }
    return true;
}

static status_t FLEXIO_I2C_MasterTransferStateMachineReceiveData(FLEXIO_I2C_Type *base,
                                                                 flexio_i2c_master_handle_t *handle,
                                                                 uint32_t statusFlags)
{
    if ((statusFlags & (uint32_t)kFLEXIO_I2C_RxFullFlag) != 0U)
    {
        *handle->transfer.data = FLEXIO_I2C_MasterReadByte(base);
        handle->transfer.data++;
        if (0U != handle->transfer.dataSize--)
        {
            if (handle->transfer.dataSize == 0U)
            {
                FLEXIO_I2C_MasterDisableInterrupts(base, (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable);
                handle->state = (uint8_t)kFLEXIO_I2C_Idle;
                /* Return nak if ReceiveNakFlag is not set */
                if ((statusFlags & (uint32_t)kFLEXIO_I2C_ReceiveNakFlag) == 0U)
                {
                    return kStatus_FLEXIO_I2C_Nak;
                }
            }

            /* Send nak at the last receive byte. */
            if (handle->transfer.dataSize == 1U)
            {
                FLEXIO_I2C_MasterEnableAck(base, false);
#if I2C_RETRY_TIMES
                while ((0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0]))) &&
                       (0U != --waitTimes))
                {
                }
                if (0U == waitTimes)
                {
                    return kStatus_FLEXIO_I2C_Timeout;
                }
#else
                while (0U == (FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0])))
                {
                }
#endif
                FLEXIO_I2C_MasterStop(base);
            }
        }
    }
    else if ((statusFlags & (uint32_t)kFLEXIO_I2C_TxEmptyFlag) != 0U)
    {
        if (handle->transfer.dataSize > 1U)
        {
            FLEXIO_I2C_MasterWriteByte(base, 0xFFFFFFFFU);
        }
    }
    else
    {
        ; /* Avoid MISRA 2012 rule 15.7 */
    }
    return kStatus_Success;
}

static status_t FLEXIO_I2C_MasterTransferRunStateMachine(FLEXIO_I2C_Type *base,
                                                         flexio_i2c_master_handle_t *handle,
                                                         uint32_t statusFlags)
{
    status_t status;
#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    if ((statusFlags & (uint32_t)kFLEXIO_I2C_ReceiveNakFlag) != 0U)
    {
        /* Clear receive nak flag. */
        FLEXIO_ClearShifterErrorFlags(base->flexioBase, 1UL << base->shifterIndex[1]);

        if ((!((handle->state == (uint8_t)kFLEXIO_I2C_SendData) && (handle->transfer.dataSize == 0U))) &&
            (!(((handle->state == (uint8_t)kFLEXIO_I2C_ReceiveData) ||
                (handle->state == (uint8_t)kFLEXIO_I2C_ReceiveDataBegin)) &&
               (handle->transfer.dataSize == 1U))))
        {
            (void)FLEXIO_I2C_MasterReadByte(base);

            FLEXIO_I2C_MasterAbortStop(base);

            /* Delay one clk cycle to ensure the bus is idle. */
            SDK_DelayAtLeastUs(1000000UL / base->baudrate, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            handle->state = (uint8_t)kFLEXIO_I2C_Idle;

            return kStatus_FLEXIO_I2C_Nak;
        }
    }

    if (((statusFlags & (uint8_t)kFLEXIO_I2C_RxFullFlag) != 0U) && (handle->state != (uint8_t)kFLEXIO_I2C_ReceiveData))
    {
        (void)FLEXIO_I2C_MasterReadByte(base);
    }

    switch (handle->state)
    {
        /* Initial state, i2c start state. */
        case (uint8_t)kFLEXIO_I2C_Start:
            /* Send address byte first. */
            FLEXIO_I2C_MasterTransferStateMachineStart(base, handle);
            break;

        /* Check address only needed for transfer with subaddress */
        case (uint8_t)kFLEXIO_I2C_SendCommand:
            if (false == FLEXIO_I2C_MasterTransferStateMachineSendCommand(base, handle, statusFlags))
            {
                return kStatus_FLEXIO_I2C_Timeout;
            }
            break;

        /* Send command byte. */
        case (uint8_t)kFLEXIO_I2C_SendData:
            if (false == FLEXIO_I2C_MasterTransferStateMachineSendData(base, handle, statusFlags))
            {
                return kStatus_FLEXIO_I2C_Timeout;
            }
            break;

        case (uint8_t)kFLEXIO_I2C_ReceiveDataBegin:
            if (false == FLEXIO_I2C_MasterTransferStateMachineReceiveDataBegin(base, handle, statusFlags))
            {
                return kStatus_FLEXIO_I2C_Timeout;
            }
            break;

        case (uint8_t)kFLEXIO_I2C_ReceiveData:
            status = FLEXIO_I2C_MasterTransferStateMachineReceiveData(base, handle, statusFlags);
            if (kStatus_Success != status)
            {
                return status;
            }
            break;

        default:
            /* Add comment to avoid MISRA violation */
            break;
    }

    return kStatus_Success;
}

static void FLEXIO_I2C_MasterTransferComplete(FLEXIO_I2C_Type *base,
                                              flexio_i2c_master_handle_t *handle,
                                              status_t status)
{
    FLEXIO_I2C_MasterDisableInterrupts(
        base, (uint32_t)kFLEXIO_I2C_TxEmptyInterruptEnable | (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable);

    if (handle->completionCallback != NULL)
    {
        handle->completionCallback(base, handle, status, handle->userData);
    }
}

#if defined(FSL_FEATURE_FLEXIO_HAS_PIN_STATUS) && FSL_FEATURE_FLEXIO_HAS_PIN_STATUS
/*!
 * brief Make sure the bus isn't already pulled down.
 *
 * Check the FLEXIO pin status to see whether either of SDA and SCL pin is pulled down.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * retval kStatus_Success
 * retval kStatus_FLEXIO_I2C_Busy
 */
status_t FLEXIO_I2C_CheckForBusyBus(FLEXIO_I2C_Type *base)
{
    uint32_t mask;
    /* If in certain loops the SDA/SCL is continuously pulled down, then return bus busy status. */
    /* The loop count is determined by maximum CPU clock frequency */
    for (uint32_t i = 0U; i < SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY / 600000U; ++i)
    {
        mask = 1UL << base->SDAPinIndex | 1UL << base->SCLPinIndex;
        if ((FLEXIO_ReadPinInput(base->flexioBase) & mask) == mask)
        {
            return kStatus_Success;
        }
    }
    return kStatus_FLEXIO_I2C_Busy;
}
#endif /*FSL_FEATURE_FLEXIO_HAS_PIN_STATUS*/

/*!
 * brief Ungates the FlexIO clock, resets the FlexIO module, and configures the FlexIO I2C
 * hardware configuration.
 *
 * Example
   code
   FLEXIO_I2C_Type base = {
   .flexioBase = FLEXIO,
   .SDAPinIndex = 0,
   .SCLPinIndex = 1,
   .shifterIndex = {0,1},
   .timerIndex = {0,1}
   };
   flexio_i2c_master_config_t config = {
   .enableInDoze = false,
   .enableInDebug = true,
   .enableFastAccess = false,
   .baudRate_Bps = 100000
   };
   FLEXIO_I2C_MasterInit(base, &config, srcClock_Hz);
   endcode
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param masterConfig Pointer to flexio_i2c_master_config_t structure.
 * param srcClock_Hz FlexIO source clock in Hz.
 * retval kStatus_Success Initialization successful
 * retval kStatus_InvalidArgument The source clock exceed upper range limitation
*/
status_t FLEXIO_I2C_MasterInit(FLEXIO_I2C_Type *base, flexio_i2c_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert((base != NULL) && (masterConfig != NULL));

    flexio_shifter_config_t shifterConfig;
    flexio_timer_config_t timerConfig;
    uint32_t controlVal = 0;
    uint16_t timerDiv   = 0;
    status_t result     = kStatus_Success;

    (void)memset(&shifterConfig, 0, sizeof(shifterConfig));
    (void)memset(&timerConfig, 0, sizeof(timerConfig));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate flexio clock. */
    CLOCK_EnableClock(s_flexioClocks[FLEXIO_I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Do hardware configuration. */
    /* 1. Configure the shifter 0 for tx. */
    shifterConfig.timerSelect   = base->timerIndex[2];
    shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnPositive;
    shifterConfig.pinConfig     = kFLEXIO_PinConfigOpenDrainOrBidirection;
    shifterConfig.pinSelect     = base->SDAPinIndex;
    shifterConfig.pinPolarity   = kFLEXIO_PinActiveLow;
    shifterConfig.shifterMode   = kFLEXIO_ShifterModeTransmit;
    shifterConfig.inputSource   = kFLEXIO_ShifterInputFromPin;
    shifterConfig.shifterStop   = kFLEXIO_ShifterStopBitHigh;
    shifterConfig.shifterStart  = kFLEXIO_ShifterStartBitLow;

    FLEXIO_SetShifterConfig(base->flexioBase, base->shifterIndex[0], &shifterConfig);

    /* 2. Configure the shifter 1 for rx. */
    shifterConfig.timerSelect   = base->timerIndex[2];
    shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
    shifterConfig.pinConfig     = kFLEXIO_PinConfigOutputDisabled;
    shifterConfig.pinSelect     = base->SDAPinIndex;
    shifterConfig.pinPolarity   = kFLEXIO_PinActiveHigh;
    shifterConfig.shifterMode   = kFLEXIO_ShifterModeReceive;
    shifterConfig.inputSource   = kFLEXIO_ShifterInputFromPin;
    shifterConfig.shifterStop   = kFLEXIO_ShifterStopBitLow;
    shifterConfig.shifterStart  = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;

    FLEXIO_SetShifterConfig(base->flexioBase, base->shifterIndex[1], &shifterConfig);

    /*3. Configure the timer 0 and timer 1 for generating bit clock. */
    /* timer 1 is used to config baudrate */
    timerConfig.triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(base->shifterIndex[0]);
    timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveLow;
    timerConfig.triggerSource   = kFLEXIO_TimerTriggerSourceInternal;
    timerConfig.pinConfig       = kFLEXIO_PinConfigOpenDrainOrBidirection;
    timerConfig.pinSelect       = base->SCLPinIndex;
    timerConfig.pinPolarity     = kFLEXIO_PinActiveHigh;
    timerConfig.timerMode       = kFLEXIO_TimerModeSingle16Bit;
    timerConfig.timerOutput     = kFLEXIO_TimerOutputZeroNotAffectedByReset;
    timerConfig.timerDecrement  = kFLEXIO_TimerDecSrcOnFlexIOClockShiftTimerOutput;
    timerConfig.timerReset      = kFLEXIO_TimerResetOnTimerPinEqualToTimerOutput;
    timerConfig.timerDisable    = kFLEXIO_TimerDisableOnPreTimerDisable;
    timerConfig.timerEnable     = kFLEXIO_TimerEnableOnTriggerHigh;
    timerConfig.timerStop       = kFLEXIO_TimerStopBitDisabled;
    timerConfig.timerStart      = kFLEXIO_TimerStartBitDisabled;

    /* Set TIMCMP = (baud rate divider / 2) - 1. */
    timerDiv = (uint16_t)(srcClock_Hz / masterConfig->baudRate_Bps) / 2U - 1U;
    /* Calculate and assign the actual baudrate. */
    base->baudrate = srcClock_Hz / (2U * ((uint32_t)timerDiv + 1U));

    timerConfig.timerCompare = timerDiv;

    FLEXIO_SetTimerConfig(base->flexioBase, base->timerIndex[1], &timerConfig);

    /* timer 0 is used to config total shift clock edges */
    timerConfig.triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(base->shifterIndex[0]);
    timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveLow;
    timerConfig.triggerSource   = kFLEXIO_TimerTriggerSourceInternal;
    timerConfig.pinConfig       = kFLEXIO_PinConfigOutputDisabled;
    timerConfig.pinSelect       = base->SCLPinIndex;
    timerConfig.pinPolarity     = kFLEXIO_PinActiveHigh;
    timerConfig.timerMode       = kFLEXIO_TimerModeSingle16Bit;
    timerConfig.timerOutput     = kFLEXIO_TimerOutputOneNotAffectedByReset;
    timerConfig.timerDecrement  = kFLEXIO_TimerDecSrcOnPinInputShiftPinInput;
    timerConfig.timerReset      = kFLEXIO_TimerResetNever;
    timerConfig.timerDisable    = kFLEXIO_TimerDisableOnTimerCompare;
    timerConfig.timerEnable     = kFLEXIO_TimerEnableOnTriggerHigh;
    timerConfig.timerStop       = kFLEXIO_TimerStopBitDisabled;
    timerConfig.timerStart      = kFLEXIO_TimerStartBitDisabled;

    /* Set TIMCMP when confinguring transfer bytes. */
    FLEXIO_SetTimerConfig(base->flexioBase, base->timerIndex[0], &timerConfig);

    /* 4. Configure the timer 2 for controlling shifters. */
    timerConfig.triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(base->shifterIndex[0]);
    timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveLow;
    timerConfig.triggerSource   = kFLEXIO_TimerTriggerSourceInternal;
    timerConfig.pinConfig       = kFLEXIO_PinConfigOutputDisabled;
    timerConfig.pinSelect       = base->SCLPinIndex;
    timerConfig.pinPolarity     = kFLEXIO_PinActiveLow;
    timerConfig.timerMode       = kFLEXIO_TimerModeSingle16Bit;
    timerConfig.timerOutput     = kFLEXIO_TimerOutputOneNotAffectedByReset;
    timerConfig.timerDecrement  = kFLEXIO_TimerDecSrcOnPinInputShiftPinInput;
    timerConfig.timerReset      = kFLEXIO_TimerResetNever;
    timerConfig.timerDisable    = kFLEXIO_TimerDisableOnPreTimerDisable;
    timerConfig.timerEnable     = kFLEXIO_TimerEnableOnPrevTimerEnable;
    timerConfig.timerStop       = kFLEXIO_TimerStopBitEnableOnTimerCompare;
    timerConfig.timerStart      = kFLEXIO_TimerStartBitEnabled;

    /* Set TIMCMP[15:0] = (number of bits x 2) - 1. */
    timerConfig.timerCompare = 8U * 2U - 1U;

    FLEXIO_SetTimerConfig(base->flexioBase, base->timerIndex[2], &timerConfig);

    /* Configure FLEXIO I2C Master. */
    controlVal = base->flexioBase->CTRL;
    controlVal &=
        ~(FLEXIO_CTRL_DOZEN_MASK | FLEXIO_CTRL_DBGE_MASK | FLEXIO_CTRL_FASTACC_MASK | FLEXIO_CTRL_FLEXEN_MASK);
    controlVal |= (FLEXIO_CTRL_DBGE(masterConfig->enableInDebug) | FLEXIO_CTRL_FASTACC(masterConfig->enableFastAccess) |
                   FLEXIO_CTRL_FLEXEN(masterConfig->enableMaster));
    if (!masterConfig->enableInDoze)
    {
        controlVal |= FLEXIO_CTRL_DOZEN_MASK;
    }

    base->flexioBase->CTRL = controlVal;
    /* Disable internal IRQs. */
    FLEXIO_I2C_MasterDisableInterrupts(
        base, (uint32_t)kFLEXIO_I2C_TxEmptyInterruptEnable | (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable);
    return result;
}

/*!
 * brief De-initializes the FlexIO I2C master peripheral. Calling this API Resets the FlexIO I2C master
 * shifer and timer config, module can't work unless the FLEXIO_I2C_MasterInit is called.
 *
 * param base pointer to FLEXIO_I2C_Type structure.
 */
void FLEXIO_I2C_MasterDeinit(FLEXIO_I2C_Type *base)
{
    base->flexioBase->SHIFTCFG[base->shifterIndex[0]] = 0;
    base->flexioBase->SHIFTCTL[base->shifterIndex[0]] = 0;
    base->flexioBase->SHIFTCFG[base->shifterIndex[1]] = 0;
    base->flexioBase->SHIFTCTL[base->shifterIndex[1]] = 0;
    base->flexioBase->TIMCFG[base->timerIndex[0]]     = 0;
    base->flexioBase->TIMCMP[base->timerIndex[0]]     = 0;
    base->flexioBase->TIMCTL[base->timerIndex[0]]     = 0;
    base->flexioBase->TIMCFG[base->timerIndex[1]]     = 0;
    base->flexioBase->TIMCMP[base->timerIndex[1]]     = 0;
    base->flexioBase->TIMCTL[base->timerIndex[1]]     = 0;
    base->flexioBase->TIMCFG[base->timerIndex[2]]     = 0;
    base->flexioBase->TIMCMP[base->timerIndex[2]]     = 0;
    base->flexioBase->TIMCTL[base->timerIndex[2]]     = 0;
    /* Clear the shifter flag. */
    base->flexioBase->SHIFTSTAT = (1UL << base->shifterIndex[0]);
    base->flexioBase->SHIFTSTAT = (1UL << base->shifterIndex[1]);
    /* Clear the timer flag. */
    base->flexioBase->TIMSTAT = (1UL << base->timerIndex[0]);
    base->flexioBase->TIMSTAT = (1UL << base->timerIndex[1]);
    base->flexioBase->TIMSTAT = (1UL << base->timerIndex[2]);
}

/*!
 * brief Gets the default configuration to configure the FlexIO module. The configuration
 * can be used directly for calling the FLEXIO_I2C_MasterInit().
 *
 * Example:
   code
   flexio_i2c_master_config_t config;
   FLEXIO_I2C_MasterGetDefaultConfig(&config);
   endcode
 * param masterConfig Pointer to flexio_i2c_master_config_t structure.
*/
void FLEXIO_I2C_MasterGetDefaultConfig(flexio_i2c_master_config_t *masterConfig)
{
    assert(masterConfig != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    masterConfig->enableMaster     = true;
    masterConfig->enableInDoze     = false;
    masterConfig->enableInDebug    = true;
    masterConfig->enableFastAccess = false;

    /* Default baud rate at 100kbps. */
    masterConfig->baudRate_Bps = 100000U;
}

/*!
 * brief Gets the FlexIO I2C master status flags.
 *
 * param base Pointer to FLEXIO_I2C_Type structure
 * return Status flag, use status flag to AND #_flexio_i2c_master_status_flags can get the related status.
 */

uint32_t FLEXIO_I2C_MasterGetStatusFlags(FLEXIO_I2C_Type *base)
{
    uint32_t status = 0;

    status =
        ((FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[0])) >> base->shifterIndex[0]);
    status |=
        (((FLEXIO_GetShifterStatusFlags(base->flexioBase) & (1UL << base->shifterIndex[1])) >> (base->shifterIndex[1]))
         << 1U);
    status |=
        (((FLEXIO_GetShifterErrorFlags(base->flexioBase) & (1UL << base->shifterIndex[1])) >> (base->shifterIndex[1]))
         << 2U);

    return status;
}

/*!
 * brief Clears the FlexIO I2C master status flags.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param mask Status flag.
 *      The parameter can be any combination of the following values:
 *          arg kFLEXIO_I2C_RxFullFlag
 *          arg kFLEXIO_I2C_ReceiveNakFlag
 */

void FLEXIO_I2C_MasterClearStatusFlags(FLEXIO_I2C_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kFLEXIO_I2C_TxEmptyFlag) != 0U)
    {
        FLEXIO_ClearShifterStatusFlags(base->flexioBase, 1UL << base->shifterIndex[0]);
    }

    if ((mask & (uint32_t)kFLEXIO_I2C_RxFullFlag) != 0U)
    {
        FLEXIO_ClearShifterStatusFlags(base->flexioBase, 1UL << base->shifterIndex[1]);
    }

    if ((mask & (uint32_t)kFLEXIO_I2C_ReceiveNakFlag) != 0U)
    {
        FLEXIO_ClearShifterErrorFlags(base->flexioBase, 1UL << base->shifterIndex[1]);
    }
}

/*!
 * brief Enables the FlexIO i2c master interrupt requests.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param mask Interrupt source.
 *     Currently only one interrupt request source:
 *     arg kFLEXIO_I2C_TransferCompleteInterruptEnable
 */
void FLEXIO_I2C_MasterEnableInterrupts(FLEXIO_I2C_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kFLEXIO_I2C_TxEmptyInterruptEnable) != 0U)
    {
        FLEXIO_EnableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[0]);
    }
    if ((mask & (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable) != 0U)
    {
        FLEXIO_EnableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[1]);
    }
}

/*!
 * brief Disables the FlexIO I2C master interrupt requests.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param mask Interrupt source.
 */
void FLEXIO_I2C_MasterDisableInterrupts(FLEXIO_I2C_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kFLEXIO_I2C_TxEmptyInterruptEnable) != 0U)
    {
        FLEXIO_DisableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[0]);
    }
    if ((mask & (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable) != 0U)
    {
        FLEXIO_DisableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[1]);
    }
}

/*!
 * brief Sets the FlexIO I2C master transfer baudrate.
 *
 * param base Pointer to FLEXIO_I2C_Type structure
 * param baudRate_Bps the baud rate value in HZ
 * param srcClock_Hz source clock in HZ
 */
void FLEXIO_I2C_MasterSetBaudRate(FLEXIO_I2C_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint16_t timerDiv       = 0;
    FLEXIO_Type *flexioBase = base->flexioBase;

    /* Set TIMCMP = (baud rate divider / 2) - 1.*/
    timerDiv = (uint16_t)((srcClock_Hz / baudRate_Bps) / 2U - 1U);

    flexioBase->TIMCMP[base->timerIndex[1]] = timerDiv;

    /* Calculate and assign the actual baudrate. */
    base->baudrate = srcClock_Hz / (2U * ((uint32_t)timerDiv + 1U));
}

/*!
 * brief Sets the number of bytes to be transferred from a start signal to a stop signal.
 *
 * note Call this API before a transfer begins because the timer generates a number of clocks according
 * to the number of bytes that need to be transferred.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param count Number of bytes need to be transferred from a start signal to a re-start/stop signal
 * retval kStatus_Success Successfully configured the count.
 * retval kStatus_InvalidArgument Input argument is invalid.
 */
status_t FLEXIO_I2C_MasterSetTransferCount(FLEXIO_I2C_Type *base, uint16_t count)
{
    /* Calculate whether the transfer count is larger than the max value compare register can achieve */
    if (count > ((0xFFFFUL - 1UL) / (16UL + 1UL + 1UL)))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t timerConfig    = 0U;
    FLEXIO_Type *flexioBase = base->flexioBase;

    flexioBase->TIMCMP[base->timerIndex[0]] = (uint32_t)count * 18U + 1U;
    timerConfig                             = flexioBase->TIMCFG[base->timerIndex[0]];
    timerConfig &= ~FLEXIO_TIMCFG_TIMDIS_MASK;
    timerConfig |= FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnTimerCompare);
    flexioBase->TIMCFG[base->timerIndex[0]] = timerConfig;

    return kStatus_Success;
}

/*!
 * brief Sends START + 7-bit address to the bus.
 *
 * note This API should be called when the transfer configuration is ready to send a START signal
 * and 7-bit address to the bus. This is a non-blocking API, which returns directly after the address
 * is put into the data register but the address transfer is not finished on the bus. Ensure that
 * the kFLEXIO_I2C_RxFullFlag status is asserted before calling this API.
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param address 7-bit address.
 * param direction transfer direction.
 *     This parameter is one of the values in flexio_i2c_direction_t:
 *        arg kFLEXIO_I2C_Write: Transmit
 *        arg kFLEXIO_I2C_Read:  Receive
 */

void FLEXIO_I2C_MasterStart(FLEXIO_I2C_Type *base, uint8_t address, flexio_i2c_direction_t direction)
{
    uint32_t data;

    data = ((uint32_t)address) << 1U | ((direction == kFLEXIO_I2C_Read) ? 1U : 0U);

    FLEXIO_I2C_MasterWriteByte(base, data);
}

/*!
 * brief Sends the repeated start signal on the bus.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 */
void FLEXIO_I2C_MasterRepeatedStart(FLEXIO_I2C_Type *base)
{
    /* Prepare for RESTART condition, no stop.*/
    FLEXIO_I2C_MasterWriteByte(base, 0xFFFFFFFFU);
}

/*!
 * brief Sends the stop signal on the bus.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 */
void FLEXIO_I2C_MasterStop(FLEXIO_I2C_Type *base)
{
    /* Prepare normal stop. */
    (void)FLEXIO_I2C_MasterSetTransferCount(base, 0x0U);
    FLEXIO_I2C_MasterWriteByte(base, 0x0U);
}

/*!
 * brief Sends the stop signal when transfer is still on-going.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 */
void FLEXIO_I2C_MasterAbortStop(FLEXIO_I2C_Type *base)
{
    uint32_t tmpConfig;

    /* Prepare abort stop. */
    /* Disable timer 0. */
    tmpConfig = base->flexioBase->TIMCFG[base->timerIndex[0]];
    tmpConfig &= ~FLEXIO_TIMCFG_TIMDIS_MASK;
    tmpConfig |= FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnPinBothEdge);
    base->flexioBase->TIMCFG[base->timerIndex[0]] = tmpConfig;

    /* Disable timer 1. */
    tmpConfig = base->flexioBase->TIMCFG[base->timerIndex[1]];
    tmpConfig &= ~FLEXIO_TIMCFG_TIMDIS_MASK;
    tmpConfig |= FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnPinBothEdge);
    base->flexioBase->TIMCFG[base->timerIndex[1]] = tmpConfig;
}

/*!
 * brief Configures the sent ACK/NAK for the following byte.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param enable True to configure send ACK, false configure to send NAK.
 */
void FLEXIO_I2C_MasterEnableAck(FLEXIO_I2C_Type *base, bool enable)
{
    uint32_t tmpConfig = 0;

    tmpConfig = base->flexioBase->SHIFTCFG[base->shifterIndex[0]];
    tmpConfig &= ~FLEXIO_SHIFTCFG_SSTOP_MASK;
    if (enable)
    {
        tmpConfig |= FLEXIO_SHIFTCFG_SSTOP(kFLEXIO_ShifterStopBitLow);
    }
    else
    {
        tmpConfig |= FLEXIO_SHIFTCFG_SSTOP(kFLEXIO_ShifterStopBitHigh);
    }
    base->flexioBase->SHIFTCFG[base->shifterIndex[0]] = tmpConfig;
}

/*!
 * brief Sends a buffer of data in bytes.
 *
 * note This function blocks via polling until all bytes have been sent.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param txBuff The data bytes to send.
 * param txSize The number of data bytes to send.
 * retval kStatus_Success Successfully write data.
 * retval kStatus_FLEXIO_I2C_Nak Receive NAK during writing data.
 * retval kStatus_FLEXIO_I2C_Timeout Timeout polling status flags.
 */
status_t FLEXIO_I2C_MasterWriteBlocking(FLEXIO_I2C_Type *base, const uint8_t *txBuff, uint8_t txSize)
{
    assert(txBuff != NULL);
    assert(txSize != 0U);

    uint32_t status;
#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    while (0U != txSize--)
    {
        FLEXIO_I2C_MasterWriteByte(base, *txBuff++);

        /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES
        waitTimes = I2C_RETRY_TIMES;
        while ((0U == ((status = FLEXIO_I2C_MasterGetStatusFlags(base)) & (uint32_t)kFLEXIO_I2C_RxFullFlag)) &&
               (0U != --waitTimes))
        {
        }
        if (0U == waitTimes)
        {
            return kStatus_FLEXIO_I2C_Timeout;
        }
#else
        while (0U == ((status = FLEXIO_I2C_MasterGetStatusFlags(base)) & (uint32_t)kFLEXIO_I2C_RxFullFlag))
        {
        }
#endif

        if ((status & (uint32_t)kFLEXIO_I2C_ReceiveNakFlag) != 0U)
        {
            FLEXIO_ClearShifterErrorFlags(base->flexioBase, 1UL << base->shifterIndex[1]);
            return kStatus_FLEXIO_I2C_Nak;
        }
    }
    return kStatus_Success;
}

/*!
 * brief Receives a buffer of bytes.
 *
 * note This function blocks via polling until all bytes have been received.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param rxBuff The buffer to store the received bytes.
 * param rxSize The number of data bytes to be received.
 * retval kStatus_Success Successfully read data.
 * retval kStatus_FLEXIO_I2C_Timeout Timeout polling status flags.
 */
status_t FLEXIO_I2C_MasterReadBlocking(FLEXIO_I2C_Type *base, uint8_t *rxBuff, uint8_t rxSize)
{
    assert(rxBuff != NULL);
    assert(rxSize != 0U);

#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    while (0U != rxSize--)
    {
        /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES
        waitTimes = I2C_RETRY_TIMES;
        while ((0U == (FLEXIO_I2C_MasterGetStatusFlags(base) & (uint32_t)kFLEXIO_I2C_RxFullFlag)) &&
               (0U != --waitTimes))
        {
        }
        if (0U == waitTimes)
        {
            return kStatus_FLEXIO_I2C_Timeout;
        }
#else
        while (0U == (FLEXIO_I2C_MasterGetStatusFlags(base) & (uint32_t)kFLEXIO_I2C_RxFullFlag))
        {
        }
#endif
        *rxBuff++ = FLEXIO_I2C_MasterReadByte(base);
    }
    return kStatus_Success;
}

/*!
 * brief Performs a master polling transfer on the I2C bus.
 *
 * note The API does not return until the transfer succeeds or fails due
 * to receiving NAK.
 *
 * param base pointer to FLEXIO_I2C_Type structure.
 * param xfer pointer to flexio_i2c_master_transfer_t structure.
 * return status of status_t.
 */
status_t FLEXIO_I2C_MasterTransferBlocking(FLEXIO_I2C_Type *base, flexio_i2c_master_transfer_t *xfer)
{
    assert(xfer != NULL);

#if defined(FSL_FEATURE_FLEXIO_HAS_PIN_STATUS) && FSL_FEATURE_FLEXIO_HAS_PIN_STATUS
    /* Return an error if the bus is already in use not by us.*/
    status_t status = FLEXIO_I2C_CheckForBusyBus(base);
    if (status != kStatus_Success)
    {
        return status;
    }
#endif /*FSL_FEATURE_FLEXIO_HAS_PIN_STATUS*/

    flexio_i2c_master_handle_t tmpHandle;
    uint32_t statusFlags;
    status_t result = kStatus_Success;
#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    /* Zero the handle. */
    (void)memset(&tmpHandle, 0, sizeof(tmpHandle));

    /* Set up transfer machine. */
    result = FLEXIO_I2C_MasterTransferInitStateMachine(base, &tmpHandle, xfer);
    if (result != kStatus_Success)
    {
        return result;
    }

    do
    {
        /* Wait either tx empty or rx full flag is asserted. */
#if I2C_RETRY_TIMES
        waitTimes = I2C_RETRY_TIMES;
        while ((0U == ((statusFlags = FLEXIO_I2C_MasterGetStatusFlags(base)) &
                       ((uint32_t)kFLEXIO_I2C_TxEmptyFlag | (uint32_t)kFLEXIO_I2C_RxFullFlag))) &&
               (0U != --waitTimes))
        {
        }
        if (0U == waitTimes)
        {
            return kStatus_FLEXIO_I2C_Timeout;
        }
#else
        while (0U == ((statusFlags = FLEXIO_I2C_MasterGetStatusFlags(base)) &
                      ((uint32_t)kFLEXIO_I2C_TxEmptyFlag | (uint32_t)kFLEXIO_I2C_RxFullFlag)))
        {
        }
#endif
        FLEXIO_ClearTimerStatusFlags(base->flexioBase, ((1UL << base->timerIndex[0]) | (1UL << base->timerIndex[1])));
        result = FLEXIO_I2C_MasterTransferRunStateMachine(base, &tmpHandle, statusFlags);

    } while ((tmpHandle.state != (uint8_t)kFLEXIO_I2C_Idle) && (result == kStatus_Success));

    /* Timer disable on timer compare, wait until bit clock TSF set, which means timer disable and stop has been sent.
     */
    while (0U == (FLEXIO_GetTimerStatusFlags(base->flexioBase) & (1UL << base->timerIndex[1])))
    {
    }

    return result;
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param handle Pointer to flexio_i2c_master_handle_t structure to store the transfer state.
 * param callback Pointer to user callback function.
 * param userData User param passed to the callback function.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_OutOfRange The FlexIO type/handle/isr table out of range.
 */
status_t FLEXIO_I2C_MasterTransferCreateHandle(FLEXIO_I2C_Type *base,
                                               flexio_i2c_master_handle_t *handle,
                                               flexio_i2c_master_transfer_callback_t callback,
                                               void *userData)
{
    assert(handle != NULL);

    IRQn_Type flexio_irqs[] = FLEXIO_IRQS;

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Register callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Clear pending NVIC IRQ before enable NVIC IRQ. */
    NVIC_ClearPendingIRQ(flexio_irqs[FLEXIO_I2C_GetInstance(base)]);
    (void)EnableIRQ(flexio_irqs[FLEXIO_I2C_GetInstance(base)]);

    /* Save the context in global variables to support the double weak mechanism. */
    return FLEXIO_RegisterHandleIRQ(base, handle, FLEXIO_I2C_MasterTransferHandleIRQ);
}

/*!
 * brief Performs a master interrupt non-blocking transfer on the I2C bus.
 *
 * note The API returns immediately after the transfer initiates.
 * Call FLEXIO_I2C_MasterTransferGetCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is not kStatus_FLEXIO_I2C_Busy, the transfer
 * is finished.
 *
 * param base Pointer to FLEXIO_I2C_Type structure
 * param handle Pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 * param xfer pointer to flexio_i2c_master_transfer_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_FLEXIO_I2C_Busy FlexIO I2C is not idle, is running another transfer.
 */
status_t FLEXIO_I2C_MasterTransferNonBlocking(FLEXIO_I2C_Type *base,
                                              flexio_i2c_master_handle_t *handle,
                                              flexio_i2c_master_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    status_t result = kStatus_Success;

#if defined(FSL_FEATURE_FLEXIO_HAS_PIN_STATUS) && FSL_FEATURE_FLEXIO_HAS_PIN_STATUS
    /* Return an error if the bus is already in use not by us.*/
    result = FLEXIO_I2C_CheckForBusyBus(base);
    if (result != kStatus_Success)
    {
        return result;
    }
#endif /*FSL_FEATURE_FLEXIO_HAS_PIN_STATUS*/

    if (handle->state != (uint8_t)kFLEXIO_I2C_Idle)
    {
        return kStatus_FLEXIO_I2C_Busy;
    }
    else
    {
        /* Set up transfer machine. */
        result = FLEXIO_I2C_MasterTransferInitStateMachine(base, handle, xfer);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Enable both tx empty and rxfull interrupt. */
        FLEXIO_I2C_MasterEnableInterrupts(
            base, (uint32_t)kFLEXIO_I2C_TxEmptyInterruptEnable | (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable);

        return kStatus_Success;
    }
}

/*!
 * brief Aborts an interrupt non-blocking transfer early.
 *
 * note This API can be called at any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base Pointer to FLEXIO_I2C_Type structure
 * param handle Pointer to flexio_i2c_master_handle_t structure which stores the transfer state
 */
void FLEXIO_I2C_MasterTransferAbort(FLEXIO_I2C_Type *base, flexio_i2c_master_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable interrupts. */
    FLEXIO_I2C_MasterDisableInterrupts(
        base, (uint32_t)kFLEXIO_I2C_TxEmptyInterruptEnable | (uint32_t)kFLEXIO_I2C_RxFullInterruptEnable);

    /* Reset to idle state. */
    handle->state = (uint8_t)kFLEXIO_I2C_Idle;
}

/*!
 * brief Gets the master transfer status during a interrupt non-blocking transfer.
 *
 * param base Pointer to FLEXIO_I2C_Type structure.
 * param handle Pointer to flexio_i2c_master_handle_t structure which stores the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 * retval kStatus_Success Successfully return the count.
 */
status_t FLEXIO_I2C_MasterTransferGetCount(FLEXIO_I2C_Type *base, flexio_i2c_master_handle_t *handle, size_t *count)
{
    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state == (uint8_t)kFLEXIO_I2C_Idle)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    *count = handle->transferSize - handle->transfer.dataSize;

    return kStatus_Success;
}

/*!
 * brief Master interrupt handler.
 *
 * param i2cType Pointer to FLEXIO_I2C_Type structure
 * param i2cHandle Pointer to flexio_i2c_master_transfer_t structure
 */
void FLEXIO_I2C_MasterTransferHandleIRQ(void *i2cType, void *i2cHandle)
{
    FLEXIO_I2C_Type *base              = (FLEXIO_I2C_Type *)i2cType;
    flexio_i2c_master_handle_t *handle = (flexio_i2c_master_handle_t *)i2cHandle;
    uint32_t statusFlags;
    status_t result;

    statusFlags = FLEXIO_I2C_MasterGetStatusFlags(base);

    result = FLEXIO_I2C_MasterTransferRunStateMachine(base, handle, statusFlags);

    if (handle->state == (uint8_t)kFLEXIO_I2C_Idle)
    {
        FLEXIO_I2C_MasterTransferComplete(base, handle, result);
    }
}
