/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexio_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexio_spi"
#endif

/*! @brief FLEXIO SPI transfer state, which is used for SPI transactiaonl APIs' internal state. */
enum _flexio_spi_transfer_states
{
    kFLEXIO_SPI_Idle = 0x0U, /*!< Nothing in the transmitter/receiver's queue. */
    kFLEXIO_SPI_Busy,        /*!< Transmiter/Receive's queue is not finished. */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Send a piece of data for SPI.
 *
 * This function computes the number of data to be written into D register or Tx FIFO,
 * and write the data into it. At the same time, this function updates the values in
 * master handle structure.
 *
 * @param base pointer to FLEXIO_SPI_Type structure
 * @param handle Pointer to SPI master handle structure.
 */
static void FLEXIO_SPI_TransferSendTransaction(FLEXIO_SPI_Type *base, flexio_spi_master_handle_t *handle);

/*!
 * @brief Receive a piece of data for SPI master.
 *
 * This function computes the number of data to receive from D register or Rx FIFO,
 * and write the data to destination address. At the same time, this function updates
 * the values in master handle structure.
 *
 * @param base pointer to FLEXIO_SPI_Type structure
 * @param handle Pointer to SPI master handle structure.
 */
static void FLEXIO_SPI_TransferReceiveTransaction(FLEXIO_SPI_Type *base, flexio_spi_master_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Codes
 ******************************************************************************/

static uint32_t FLEXIO_SPI_GetInstance(FLEXIO_SPI_Type *base)
{
    return FLEXIO_GetInstance(base->flexioBase);
}

static void FLEXIO_SPI_TransferSendTransaction(FLEXIO_SPI_Type *base, flexio_spi_master_handle_t *handle)
{
    uint32_t tmpData = FLEXIO_SPI_DUMMYDATA;

    if (handle->txData != NULL)
    {
        /* Transmit data and update tx size/buff. */
        if (handle->bytePerFrame == 1U)
        {
            tmpData = (uint32_t) * (handle->txData);
            handle->txData++;
        }
        else if (handle->bytePerFrame == 2U)
        {
            if (handle->direction == kFLEXIO_SPI_MsbFirst)
            {
                tmpData = (uint32_t)(handle->txData[0]) << 8U;
                tmpData += (uint32_t)handle->txData[1];
            }
            else
            {
                tmpData = (uint32_t)(handle->txData[1]) << 8U;
                tmpData += (uint32_t)handle->txData[0];
            }
            handle->txData += 2U;
        }
        else
        {
            if (handle->direction == kFLEXIO_SPI_MsbFirst)
            {
                tmpData = (uint32_t)(handle->txData[0]) << 24U;
                tmpData += (uint32_t)(handle->txData[1]) << 16U;
                tmpData += (uint32_t)(handle->txData[2]) << 8U;
                tmpData += (uint32_t)handle->txData[3];
            }
            else
            {
                tmpData = (uint32_t)(handle->txData[3]) << 24U;
                tmpData += (uint32_t)(handle->txData[2]) << 16U;
                tmpData += (uint32_t)(handle->txData[1]) << 8U;
                tmpData += (uint32_t)handle->txData[0];
            }
            handle->txData += 4U;
        }
    }
    else
    {
        tmpData = FLEXIO_SPI_DUMMYDATA;
    }

    handle->txRemainingBytes -= handle->bytePerFrame;

    FLEXIO_SPI_WriteData(base, handle->direction, tmpData);

    if (0U == handle->txRemainingBytes)
    {
        FLEXIO_SPI_DisableInterrupts(base, (uint32_t)kFLEXIO_SPI_TxEmptyInterruptEnable);
    }
}

static void FLEXIO_SPI_TransferReceiveTransaction(FLEXIO_SPI_Type *base, flexio_spi_master_handle_t *handle)
{
    uint32_t tmpData;

    tmpData = FLEXIO_SPI_ReadData(base, handle->direction);

    if (handle->rxData != NULL)
    {
        if (handle->bytePerFrame == 1U)
        {
            *handle->rxData = (uint8_t)tmpData;
        }
        else if (handle->bytePerFrame == 2U)
        {
            if (handle->direction == kFLEXIO_SPI_LsbFirst)
            {
                *handle->rxData = (uint8_t)(tmpData >> 8);
                handle->rxData++;
                *handle->rxData = (uint8_t)tmpData;
            }
            else
            {
                *handle->rxData = (uint8_t)tmpData;
                handle->rxData++;
                *handle->rxData = (uint8_t)(tmpData >> 8);
            }
        }
        else
        {
            if (handle->direction == kFLEXIO_SPI_LsbFirst)
            {
                *handle->rxData = (uint8_t)(tmpData >> 24U);
                handle->rxData++;
                *handle->rxData = (uint8_t)(tmpData >> 16U);
                handle->rxData++;
                *handle->rxData = (uint8_t)(tmpData >> 8U);
                handle->rxData++;
                *handle->rxData = (uint8_t)tmpData;
            }
            else
            {
                *handle->rxData = (uint8_t)tmpData;
                handle->rxData++;
                *handle->rxData = (uint8_t)(tmpData >> 8U);
                handle->rxData++;
                *handle->rxData = (uint8_t)(tmpData >> 16U);
                handle->rxData++;
                *handle->rxData = (uint8_t)(tmpData >> 24U);
            }
        }
        handle->rxData++;
    }
    handle->rxRemainingBytes -= handle->bytePerFrame;
}

/*!
 * brief Ungates the FlexIO clock, resets the FlexIO module, configures the FlexIO SPI master hardware,
 * and configures the FlexIO SPI with FlexIO SPI master configuration. The
 * configuration structure can be filled by the user, or be set with default values
 * by the FLEXIO_SPI_MasterGetDefaultConfig().
 *
 * note 1.FlexIO SPI master only support CPOL = 0, which means clock inactive low.
 *      2.For FlexIO SPI master, the input valid time is 1.5 clock cycles, for slave the output valid time
 *        is 2.5 clock cycles. So if FlexIO SPI master communicates with other spi IPs, the maximum baud
 *        rate is FlexIO clock frequency divided by 2*2=4. If FlexIO SPI master communicates with FlexIO
 *        SPI slave, the maximum baud rate is FlexIO clock frequency divided by (1.5+2.5)*2=8.
 *
 * Example
   code
   FLEXIO_SPI_Type spiDev = {
   .flexioBase = FLEXIO,
   .SDOPinIndex = 0,
   .SDIPinIndex = 1,
   .SCKPinIndex = 2,
   .CSnPinIndex = 3,
   .shifterIndex = {0,1},
   .timerIndex = {0,1}
   };
   flexio_spi_master_config_t config = {
   .enableMaster = true,
   .enableInDoze = false,
   .enableInDebug = true,
   .enableFastAccess = false,
   .baudRate_Bps = 500000,
   .phase = kFLEXIO_SPI_ClockPhaseFirstEdge,
   .direction = kFLEXIO_SPI_MsbFirst,
   .dataMode = kFLEXIO_SPI_8BitMode
   };
   FLEXIO_SPI_MasterInit(&spiDev, &config, srcClock_Hz);
   endcode
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param masterConfig Pointer to the flexio_spi_master_config_t structure.
 * param srcClock_Hz FlexIO source clock in Hz.
*/
void FLEXIO_SPI_MasterInit(FLEXIO_SPI_Type *base, flexio_spi_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert(base != NULL);
    assert(masterConfig != NULL);

    flexio_shifter_config_t shifterConfig;
    flexio_timer_config_t timerConfig;
    uint32_t ctrlReg  = 0;
    uint16_t timerDiv = 0;
    uint16_t timerCmp = 0;

    /* Clear the shifterConfig & timerConfig struct. */
    (void)memset(&shifterConfig, 0, sizeof(shifterConfig));
    (void)memset(&timerConfig, 0, sizeof(timerConfig));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate flexio clock. */
    CLOCK_EnableClock(s_flexioClocks[FLEXIO_SPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Configure FLEXIO SPI Master */
    ctrlReg = base->flexioBase->CTRL;
    ctrlReg &= ~(FLEXIO_CTRL_DOZEN_MASK | FLEXIO_CTRL_DBGE_MASK | FLEXIO_CTRL_FASTACC_MASK | FLEXIO_CTRL_FLEXEN_MASK);
    ctrlReg |= (FLEXIO_CTRL_DBGE(masterConfig->enableInDebug) | FLEXIO_CTRL_FASTACC(masterConfig->enableFastAccess) |
                FLEXIO_CTRL_FLEXEN(masterConfig->enableMaster));
    if (!masterConfig->enableInDoze)
    {
        ctrlReg |= FLEXIO_CTRL_DOZEN_MASK;
    }

    base->flexioBase->CTRL = ctrlReg;

    /* Do hardware configuration. */
    /* 1. Configure the shifter 0 for tx. */
    shifterConfig.timerSelect = base->timerIndex[0];
    shifterConfig.pinConfig   = kFLEXIO_PinConfigOutput;
    shifterConfig.pinSelect   = base->SDOPinIndex;
    shifterConfig.pinPolarity = kFLEXIO_PinActiveHigh;
    shifterConfig.shifterMode = kFLEXIO_ShifterModeTransmit;
    shifterConfig.inputSource = kFLEXIO_ShifterInputFromPin;
    if (masterConfig->phase == kFLEXIO_SPI_ClockPhaseFirstEdge)
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
        shifterConfig.shifterStop   = kFLEXIO_ShifterStopBitDisable;
        shifterConfig.shifterStart  = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;
    }
    else
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnPositive;
        shifterConfig.shifterStop   = kFLEXIO_ShifterStopBitLow;
        shifterConfig.shifterStart  = kFLEXIO_ShifterStartBitDisabledLoadDataOnShift;
    }

    FLEXIO_SetShifterConfig(base->flexioBase, base->shifterIndex[0], &shifterConfig);

    /* 2. Configure the shifter 1 for rx. */
    shifterConfig.timerSelect  = base->timerIndex[0];
    shifterConfig.pinConfig    = kFLEXIO_PinConfigOutputDisabled;
    shifterConfig.pinSelect    = base->SDIPinIndex;
    shifterConfig.pinPolarity  = kFLEXIO_PinActiveHigh;
    shifterConfig.shifterMode  = kFLEXIO_ShifterModeReceive;
    shifterConfig.inputSource  = kFLEXIO_ShifterInputFromPin;
    shifterConfig.shifterStop  = kFLEXIO_ShifterStopBitDisable;
    shifterConfig.shifterStart = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;
    if (masterConfig->phase == kFLEXIO_SPI_ClockPhaseFirstEdge)
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnPositive;
    }
    else
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
    }

    FLEXIO_SetShifterConfig(base->flexioBase, base->shifterIndex[1], &shifterConfig);

    /*3. Configure the timer 0 for SCK. */
    timerConfig.triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(base->shifterIndex[0]);
    timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveLow;
    timerConfig.triggerSource   = kFLEXIO_TimerTriggerSourceInternal;
    timerConfig.pinConfig       = kFLEXIO_PinConfigOutput;
    timerConfig.pinSelect       = base->SCKPinIndex;
    timerConfig.pinPolarity     = kFLEXIO_PinActiveHigh;
    timerConfig.timerMode       = kFLEXIO_TimerModeDual8BitBaudBit;
    timerConfig.timerOutput     = kFLEXIO_TimerOutputZeroNotAffectedByReset;
    timerConfig.timerDecrement  = kFLEXIO_TimerDecSrcOnFlexIOClockShiftTimerOutput;
    timerConfig.timerReset      = kFLEXIO_TimerResetNever;
    timerConfig.timerDisable    = kFLEXIO_TimerDisableOnTimerCompare;
    timerConfig.timerEnable     = kFLEXIO_TimerEnableOnTriggerHigh;
    timerConfig.timerStop       = kFLEXIO_TimerStopBitEnableOnTimerDisable;
    timerConfig.timerStart      = kFLEXIO_TimerStartBitEnabled;
    /* Low 8-bits are used to configure baudrate. */
    timerDiv = (uint16_t)(srcClock_Hz / masterConfig->baudRate_Bps);
    timerDiv = timerDiv / 2U - 1U;
    /* High 8-bits are used to configure shift clock edges(transfer width). */
    timerCmp = ((uint16_t)masterConfig->dataMode * 2U - 1U) << 8U;
    timerCmp |= timerDiv;

    timerConfig.timerCompare = timerCmp;

    FLEXIO_SetTimerConfig(base->flexioBase, base->timerIndex[0], &timerConfig);

    /* 4. Configure the timer 1 for CSn. */
    timerConfig.triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_TIMn(base->timerIndex[0]);
    timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveHigh;
    timerConfig.triggerSource   = kFLEXIO_TimerTriggerSourceInternal;
    timerConfig.pinConfig       = kFLEXIO_PinConfigOutput;
    timerConfig.pinSelect       = base->CSnPinIndex;
    timerConfig.pinPolarity     = kFLEXIO_PinActiveLow;
    timerConfig.timerMode       = kFLEXIO_TimerModeSingle16Bit;
    timerConfig.timerOutput     = kFLEXIO_TimerOutputOneNotAffectedByReset;
    timerConfig.timerDecrement  = kFLEXIO_TimerDecSrcOnFlexIOClockShiftTimerOutput;
    timerConfig.timerReset      = kFLEXIO_TimerResetNever;
    timerConfig.timerDisable    = kFLEXIO_TimerDisableOnPreTimerDisable;
    timerConfig.timerEnable     = kFLEXIO_TimerEnableOnPrevTimerEnable;
    timerConfig.timerStop       = kFLEXIO_TimerStopBitDisabled;
    timerConfig.timerStart      = kFLEXIO_TimerStartBitDisabled;

    timerConfig.timerCompare = 0xFFFFU; /* Never compare. */

    FLEXIO_SetTimerConfig(base->flexioBase, base->timerIndex[1], &timerConfig);
}

/*!
 * brief Resets the FlexIO SPI timer and shifter config.
 *
 * param base Pointer to the FLEXIO_SPI_Type.
 */
void FLEXIO_SPI_MasterDeinit(FLEXIO_SPI_Type *base)
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
}

/*!
 * brief Gets the default configuration to configure the FlexIO SPI master. The configuration
 * can be used directly by calling the FLEXIO_SPI_MasterConfigure().
 * Example:
   code
   flexio_spi_master_config_t masterConfig;
   FLEXIO_SPI_MasterGetDefaultConfig(&masterConfig);
   endcode
 * param masterConfig Pointer to the flexio_spi_master_config_t structure.
*/
void FLEXIO_SPI_MasterGetDefaultConfig(flexio_spi_master_config_t *masterConfig)
{
    assert(masterConfig != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    masterConfig->enableMaster     = true;
    masterConfig->enableInDoze     = false;
    masterConfig->enableInDebug    = true;
    masterConfig->enableFastAccess = false;
    /* Default baud rate 500kbps. */
    masterConfig->baudRate_Bps = 500000U;
    /* Default CPHA = 0. */
    masterConfig->phase = kFLEXIO_SPI_ClockPhaseFirstEdge;
    /* Default bit count at 8. */
    masterConfig->dataMode = kFLEXIO_SPI_8BitMode;
}

/*!
 * brief Ungates the FlexIO clock, resets the FlexIO module, configures the FlexIO SPI slave hardware
 * configuration, and configures the FlexIO SPI with FlexIO SPI slave configuration. The
 * configuration structure can be filled by the user, or be set with default values
 * by the FLEXIO_SPI_SlaveGetDefaultConfig().
 *
 * note 1.Only one timer is needed in the FlexIO SPI slave. As a result, the second timer index is ignored.
 *      2.FlexIO SPI slave only support CPOL = 0, which means clock inactive low.
 *      3.For FlexIO SPI master, the input valid time is 1.5 clock cycles, for slave the output valid time
 *        is 2.5 clock cycles. So if FlexIO SPI slave communicates with other spi IPs, the maximum baud
 *        rate is FlexIO clock frequency divided by 3*2=6. If FlexIO SPI slave communicates with FlexIO
 *        SPI master, the maximum baud rate is FlexIO clock frequency divided by (1.5+2.5)*2=8.
 * Example
   code
   FLEXIO_SPI_Type spiDev = {
   .flexioBase = FLEXIO,
   .SDOPinIndex = 0,
   .SDIPinIndex = 1,
   .SCKPinIndex = 2,
   .CSnPinIndex = 3,
   .shifterIndex = {0,1},
   .timerIndex = {0}
   };
   flexio_spi_slave_config_t config = {
   .enableSlave = true,
   .enableInDoze = false,
   .enableInDebug = true,
   .enableFastAccess = false,
   .phase = kFLEXIO_SPI_ClockPhaseFirstEdge,
   .direction = kFLEXIO_SPI_MsbFirst,
   .dataMode = kFLEXIO_SPI_8BitMode
   };
   FLEXIO_SPI_SlaveInit(&spiDev, &config);
   endcode
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param slaveConfig Pointer to the flexio_spi_slave_config_t structure.
*/
void FLEXIO_SPI_SlaveInit(FLEXIO_SPI_Type *base, flexio_spi_slave_config_t *slaveConfig)
{
    assert((base != NULL) && (slaveConfig != NULL));

    flexio_shifter_config_t shifterConfig;
    flexio_timer_config_t timerConfig;
    uint32_t ctrlReg = 0;

    /* Clear the shifterConfig & timerConfig struct. */
    (void)memset(&shifterConfig, 0, sizeof(shifterConfig));
    (void)memset(&timerConfig, 0, sizeof(timerConfig));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate flexio clock. */
    CLOCK_EnableClock(s_flexioClocks[FLEXIO_SPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Configure FLEXIO SPI Slave */
    ctrlReg = base->flexioBase->CTRL;
    ctrlReg &= ~(FLEXIO_CTRL_DOZEN_MASK | FLEXIO_CTRL_DBGE_MASK | FLEXIO_CTRL_FASTACC_MASK | FLEXIO_CTRL_FLEXEN_MASK);
    ctrlReg |= (FLEXIO_CTRL_DBGE(slaveConfig->enableInDebug) | FLEXIO_CTRL_FASTACC(slaveConfig->enableFastAccess) |
                FLEXIO_CTRL_FLEXEN(slaveConfig->enableSlave));
    if (!slaveConfig->enableInDoze)
    {
        ctrlReg |= FLEXIO_CTRL_DOZEN_MASK;
    }

    base->flexioBase->CTRL = ctrlReg;

    /* Do hardware configuration. */
    /* 1. Configure the shifter 0 for tx. */
    shifterConfig.timerSelect = base->timerIndex[0];
    shifterConfig.pinConfig   = kFLEXIO_PinConfigOutput;
    shifterConfig.pinSelect   = base->SDOPinIndex;
    shifterConfig.pinPolarity = kFLEXIO_PinActiveHigh;
    shifterConfig.shifterMode = kFLEXIO_ShifterModeTransmit;
    shifterConfig.inputSource = kFLEXIO_ShifterInputFromPin;
    shifterConfig.shifterStop = kFLEXIO_ShifterStopBitDisable;
    if (slaveConfig->phase == kFLEXIO_SPI_ClockPhaseFirstEdge)
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
        shifterConfig.shifterStart  = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;
    }
    else
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnPositive;
        shifterConfig.shifterStart  = kFLEXIO_ShifterStartBitDisabledLoadDataOnShift;
    }

    FLEXIO_SetShifterConfig(base->flexioBase, base->shifterIndex[0], &shifterConfig);

    /* 2. Configure the shifter 1 for rx. */
    shifterConfig.timerSelect  = base->timerIndex[0];
    shifterConfig.pinConfig    = kFLEXIO_PinConfigOutputDisabled;
    shifterConfig.pinSelect    = base->SDIPinIndex;
    shifterConfig.pinPolarity  = kFLEXIO_PinActiveHigh;
    shifterConfig.shifterMode  = kFLEXIO_ShifterModeReceive;
    shifterConfig.inputSource  = kFLEXIO_ShifterInputFromPin;
    shifterConfig.shifterStop  = kFLEXIO_ShifterStopBitDisable;
    shifterConfig.shifterStart = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;
    if (slaveConfig->phase == kFLEXIO_SPI_ClockPhaseFirstEdge)
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnPositive;
    }
    else
    {
        shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
    }

    FLEXIO_SetShifterConfig(base->flexioBase, base->shifterIndex[1], &shifterConfig);

    /*3. Configure the timer 0 for shift clock. */
    timerConfig.triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_PININPUT(base->CSnPinIndex);
    timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveLow;
    timerConfig.triggerSource   = kFLEXIO_TimerTriggerSourceInternal;
    timerConfig.pinConfig       = kFLEXIO_PinConfigOutputDisabled;
    timerConfig.pinSelect       = base->SCKPinIndex;
    timerConfig.pinPolarity     = kFLEXIO_PinActiveHigh;
    timerConfig.timerMode       = kFLEXIO_TimerModeSingle16Bit;
    timerConfig.timerOutput     = kFLEXIO_TimerOutputZeroNotAffectedByReset;
    timerConfig.timerDecrement  = kFLEXIO_TimerDecSrcOnPinInputShiftPinInput;
    timerConfig.timerReset      = kFLEXIO_TimerResetNever;
    timerConfig.timerEnable     = kFLEXIO_TimerEnableOnTriggerRisingEdge;
    timerConfig.timerStop       = kFLEXIO_TimerStopBitDisabled;
    if (slaveConfig->phase == kFLEXIO_SPI_ClockPhaseFirstEdge)
    {
        timerConfig.timerDisable = kFLEXIO_TimerDisableOnTimerCompare;
        timerConfig.timerStart   = kFLEXIO_TimerStartBitDisabled;
    }
    else
    {
        timerConfig.timerDisable = kFLEXIO_TimerDisableOnTriggerFallingEdge;
        timerConfig.timerStart   = kFLEXIO_TimerStartBitEnabled;
    }

    timerConfig.timerCompare = (uint32_t)slaveConfig->dataMode * 2U - 1U;

    FLEXIO_SetTimerConfig(base->flexioBase, base->timerIndex[0], &timerConfig);
}

/*!
 * brief Gates the FlexIO clock.
 *
 * param base Pointer to the FLEXIO_SPI_Type.
 */
void FLEXIO_SPI_SlaveDeinit(FLEXIO_SPI_Type *base)
{
    FLEXIO_SPI_MasterDeinit(base);
}

/*!
 * brief Gets the default configuration to configure the FlexIO SPI slave. The configuration
 * can be used directly for calling the FLEXIO_SPI_SlaveConfigure().
 * Example:
   code
   flexio_spi_slave_config_t slaveConfig;
   FLEXIO_SPI_SlaveGetDefaultConfig(&slaveConfig);
   endcode
 * param slaveConfig Pointer to the flexio_spi_slave_config_t structure.
*/
void FLEXIO_SPI_SlaveGetDefaultConfig(flexio_spi_slave_config_t *slaveConfig)
{
    assert(slaveConfig != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    slaveConfig->enableSlave      = true;
    slaveConfig->enableInDoze     = false;
    slaveConfig->enableInDebug    = true;
    slaveConfig->enableFastAccess = false;
    /* Default CPHA = 0. */
    slaveConfig->phase = kFLEXIO_SPI_ClockPhaseFirstEdge;
    /* Default bit count at 8. */
    slaveConfig->dataMode = kFLEXIO_SPI_8BitMode;
}

/*!
 * brief Enables the FlexIO SPI interrupt.
 *
 * This function enables the FlexIO SPI interrupt.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param mask interrupt source. The parameter can be any combination of the following values:
 *        arg kFLEXIO_SPI_RxFullInterruptEnable
 *        arg kFLEXIO_SPI_TxEmptyInterruptEnable
 */
void FLEXIO_SPI_EnableInterrupts(FLEXIO_SPI_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kFLEXIO_SPI_TxEmptyInterruptEnable) != 0U)
    {
        FLEXIO_EnableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[0]);
    }
    if ((mask & (uint32_t)kFLEXIO_SPI_RxFullInterruptEnable) != 0U)
    {
        FLEXIO_EnableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[1]);
    }
}

/*!
 * brief Disables the FlexIO SPI interrupt.
 *
 * This function disables the FlexIO SPI interrupt.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param mask interrupt source The parameter can be any combination of the following values:
 *        arg kFLEXIO_SPI_RxFullInterruptEnable
 *        arg kFLEXIO_SPI_TxEmptyInterruptEnable
 */
void FLEXIO_SPI_DisableInterrupts(FLEXIO_SPI_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kFLEXIO_SPI_TxEmptyInterruptEnable) != 0U)
    {
        FLEXIO_DisableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[0]);
    }
    if ((mask & (uint32_t)kFLEXIO_SPI_RxFullInterruptEnable) != 0U)
    {
        FLEXIO_DisableShifterStatusInterrupts(base->flexioBase, 1UL << base->shifterIndex[1]);
    }
}

/*!
 * brief Enables/disables the FlexIO SPI transmit DMA. This function enables/disables the FlexIO SPI Tx DMA,
 * which means that asserting the kFLEXIO_SPI_TxEmptyFlag does/doesn't trigger the DMA request.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param mask SPI DMA source.
 * param enable True means enable DMA, false means disable DMA.
 */
void FLEXIO_SPI_EnableDMA(FLEXIO_SPI_Type *base, uint32_t mask, bool enable)
{
    if ((mask & (uint32_t)kFLEXIO_SPI_TxDmaEnable) != 0U)
    {
        FLEXIO_EnableShifterStatusDMA(base->flexioBase, 1UL << base->shifterIndex[0], enable);
    }

    if ((mask & (uint32_t)kFLEXIO_SPI_RxDmaEnable) != 0U)
    {
        FLEXIO_EnableShifterStatusDMA(base->flexioBase, 1UL << base->shifterIndex[1], enable);
    }
}

/*!
 * brief Gets FlexIO SPI status flags.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * return status flag; Use the status flag to AND the following flag mask and get the status.
 *          arg kFLEXIO_SPI_TxEmptyFlag
 *          arg kFLEXIO_SPI_RxEmptyFlag
 */

uint32_t FLEXIO_SPI_GetStatusFlags(FLEXIO_SPI_Type *base)
{
    uint32_t shifterStatus = FLEXIO_GetShifterStatusFlags(base->flexioBase);
    uint32_t status        = 0;

    status = ((shifterStatus & (1UL << base->shifterIndex[0])) >> base->shifterIndex[0]);
    status |= (((shifterStatus & (1UL << base->shifterIndex[1])) >> (base->shifterIndex[1])) << 1U);

    return status;
}

/*!
 * brief Clears FlexIO SPI status flags.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param mask status flag
 *      The parameter can be any combination of the following values:
 *          arg kFLEXIO_SPI_TxEmptyFlag
 *          arg kFLEXIO_SPI_RxEmptyFlag
 */

void FLEXIO_SPI_ClearStatusFlags(FLEXIO_SPI_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag) != 0U)
    {
        FLEXIO_ClearShifterStatusFlags(base->flexioBase, 1UL << base->shifterIndex[0]);
    }
    if ((mask & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag) != 0U)
    {
        FLEXIO_ClearShifterStatusFlags(base->flexioBase, 1UL << base->shifterIndex[1]);
    }
}

/*!
 * brief Sets baud rate for the FlexIO SPI transfer, which is only used for the master.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param baudRate_Bps Baud Rate needed in Hz.
 * param srcClockHz SPI source clock frequency in Hz.
 */
void FLEXIO_SPI_MasterSetBaudRate(FLEXIO_SPI_Type *base, uint32_t baudRate_Bps, uint32_t srcClockHz)
{
    uint16_t timerDiv       = 0;
    uint16_t timerCmp       = 0;
    FLEXIO_Type *flexioBase = base->flexioBase;

    /* Set TIMCMP[7:0] = (baud rate divider / 2) - 1.*/
    timerDiv = (uint16_t)(srcClockHz / baudRate_Bps);
    timerDiv = timerDiv / 2U - 1U;

    timerCmp = (uint16_t)(flexioBase->TIMCMP[base->timerIndex[0]]);
    timerCmp &= 0xFF00U;
    timerCmp |= timerDiv;

    flexioBase->TIMCMP[base->timerIndex[0]] = timerCmp;
}

/*!
 * brief Sends a buffer of data bytes.
 *
 * note This function blocks using the polling method until all bytes have been sent.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param direction Shift direction of MSB first or LSB first.
 * param buffer The data bytes to send.
 * param size The number of data bytes to send.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_FLEXIO_SPI_Timeout The transfer timed out and was aborted.
 */
status_t FLEXIO_SPI_WriteBlocking(FLEXIO_SPI_Type *base,
                                  flexio_spi_shift_direction_t direction,
                                  const uint8_t *buffer,
                                  size_t size)
{
    assert(buffer != NULL);
    assert(size != 0U);

#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (0U != size--)
    {
        /* Wait until data transfer complete. */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while ((0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag)) &&
               (0U != --waitTimes))
#else
        while (0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag))
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_FLEXIO_SPI_Timeout;
        }
#endif
        FLEXIO_SPI_WriteData(base, direction, *buffer++);
    }

    return kStatus_Success;
}

/*!
 * brief Receives a buffer of bytes.
 *
 * note This function blocks using the polling method until all bytes have been received.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param direction Shift direction of MSB first or LSB first.
 * param buffer The buffer to store the received bytes.
 * param size The number of data bytes to be received.
 * param direction Shift direction of MSB first or LSB first.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_FLEXIO_SPI_Timeout The transfer timed out and was aborted.
 */
status_t FLEXIO_SPI_ReadBlocking(FLEXIO_SPI_Type *base,
                                 flexio_spi_shift_direction_t direction,
                                 uint8_t *buffer,
                                 size_t size)
{
    assert(buffer != NULL);
    assert(size != 0U);

#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (0U != size--)
    {
        /* Wait until data transfer complete. */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while ((0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag)) &&
               (0U != --waitTimes))
#else
        while (0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag))
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_FLEXIO_SPI_Timeout;
        }
#endif
        *buffer++ = (uint8_t)FLEXIO_SPI_ReadData(base, direction);
    }

    return kStatus_Success;
}

/*!
 * brief Receives a buffer of bytes.
 *
 * note This function blocks via polling until all bytes have been received.
 *
 * param base pointer to FLEXIO_SPI_Type structure
 * param xfer FlexIO SPI transfer structure, see #flexio_spi_transfer_t.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_FLEXIO_SPI_Timeout The transfer timed out and was aborted.
 */
status_t FLEXIO_SPI_MasterTransferBlocking(FLEXIO_SPI_Type *base, flexio_spi_transfer_t *xfer)
{
    flexio_spi_shift_direction_t direction;
    uint8_t bytesPerFrame;
    uint32_t dataMode  = 0;
    uint16_t timerCmp  = (uint16_t)(base->flexioBase->TIMCMP[base->timerIndex[0]]);
    uint32_t tmpData   = FLEXIO_SPI_DUMMYDATA;
    uint8_t dataFormat = FLEXIO_SPI_XFER_DATA_FORMAT(xfer->flags);
#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    timerCmp &= 0x00FFU;

    if ((xfer->flags & (uint8_t)kFLEXIO_SPI_csContinuous) != 0U)
    {
        base->flexioBase->TIMCFG[base->timerIndex[0]] =
            (base->flexioBase->TIMCFG[base->timerIndex[0]] & ~FLEXIO_TIMCFG_TSTOP_MASK) |
            FLEXIO_TIMCFG_TSTOP(kFLEXIO_TimerStopBitDisabled);
    }
    else
    {
        base->flexioBase->TIMCFG[base->timerIndex[0]] =
            (base->flexioBase->TIMCFG[base->timerIndex[0]] & ~FLEXIO_TIMCFG_TSTOP_MASK) |
            FLEXIO_TIMCFG_TSTOP(kFLEXIO_TimerStopBitEnableOnTimerDisable);
    }

    /* Configure the values in handle. */
    switch (dataFormat)
    {
        case (uint8_t)kFLEXIO_SPI_8bitMsb:
            dataMode      = (8UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 1U;
            direction     = kFLEXIO_SPI_MsbFirst;
            break;

        case (uint8_t)kFLEXIO_SPI_8bitLsb:
            dataMode      = (8UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 1U;
            direction     = kFLEXIO_SPI_LsbFirst;
            break;

        case (uint8_t)kFLEXIO_SPI_16bitMsb:
            dataMode      = (16UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 2U;
            direction     = kFLEXIO_SPI_MsbFirst;
            break;

        case (uint8_t)kFLEXIO_SPI_16bitLsb:
            dataMode      = (16UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 2U;
            direction     = kFLEXIO_SPI_LsbFirst;
            break;

        case (uint8_t)kFLEXIO_SPI_32bitMsb:
            dataMode      = (32UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 4U;
            direction     = kFLEXIO_SPI_MsbFirst;
            break;

        case (uint8_t)kFLEXIO_SPI_32bitLsb:
            dataMode      = (32UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 4U;
            direction     = kFLEXIO_SPI_LsbFirst;
            break;

        default:
            dataMode      = (8UL * 2UL - 1UL) << 8U;
            bytesPerFrame = 1U;
            direction     = kFLEXIO_SPI_MsbFirst;
            assert(true);
            break;
    }

    dataMode |= timerCmp;

    /* Transfer size should be bytesPerFrame divisible. */
    if ((xfer->dataSize % bytesPerFrame) != 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* Configure transfer size. */
    base->flexioBase->TIMCMP[base->timerIndex[0]] = dataMode;

    while (xfer->dataSize != 0U)
    {
        /* Wait until data transfer complete. */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while ((0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag)) &&
               (0U != --waitTimes))
#else
        while (0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag))
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_FLEXIO_SPI_Timeout;
        }
#endif
        if (xfer->txData != NULL)
        {
            /* Transmit data and update tx size/buff. */
            if (bytesPerFrame == 1U)
            {
                tmpData = (uint32_t) * (xfer->txData);
                xfer->txData++;
            }
            else if (bytesPerFrame == 2U)
            {
                if (direction == kFLEXIO_SPI_MsbFirst)
                {
                    tmpData = (uint32_t)(xfer->txData[0]) << 8U;
                    tmpData += (uint32_t)xfer->txData[1];
                }
                else
                {
                    tmpData = (uint32_t)(xfer->txData[1]) << 8U;
                    tmpData += (uint32_t)xfer->txData[0];
                }
                xfer->txData += 2U;
            }
            else
            {
                if (direction == kFLEXIO_SPI_MsbFirst)
                {
                    tmpData = (uint32_t)(xfer->txData[0]) << 24U;
                    tmpData += (uint32_t)(xfer->txData[1]) << 16U;
                    tmpData += (uint32_t)(xfer->txData[2]) << 8U;
                    tmpData += (uint32_t)xfer->txData[3];
                }
                else
                {
                    tmpData = (uint32_t)(xfer->txData[3]) << 24U;
                    tmpData += (uint32_t)(xfer->txData[2]) << 16U;
                    tmpData += (uint32_t)(xfer->txData[1]) << 8U;
                    tmpData += (uint32_t)xfer->txData[0];
                }
                xfer->txData += 4U;
            }
        }
        else
        {
            tmpData = FLEXIO_SPI_DUMMYDATA;
        }

        xfer->dataSize -= bytesPerFrame;

        FLEXIO_SPI_WriteData(base, direction, tmpData);

#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while ((0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag)) &&
               (0U != --waitTimes))
#else
        while (0U == (FLEXIO_SPI_GetStatusFlags(base) & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag))
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_FLEXIO_SPI_Timeout;
        }
#endif
        tmpData = FLEXIO_SPI_ReadData(base, direction);

        if (xfer->rxData != NULL)
        {
            if (bytesPerFrame == 1U)
            {
                *xfer->rxData = (uint8_t)tmpData;
            }
            else if (bytesPerFrame == 2U)
            {
                if (direction == kFLEXIO_SPI_LsbFirst)
                {
                    *xfer->rxData = (uint8_t)(tmpData >> 8);
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)tmpData;
                }
                else
                {
                    *xfer->rxData = (uint8_t)tmpData;
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)(tmpData >> 8);
                }
            }
            else
            {
                if (direction == kFLEXIO_SPI_LsbFirst)
                {
                    *xfer->rxData = (uint8_t)(tmpData >> 24U);
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)(tmpData >> 16U);
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)(tmpData >> 8U);
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)tmpData;
                }
                else
                {
                    *xfer->rxData = (uint8_t)tmpData;
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)(tmpData >> 8U);
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)(tmpData >> 16U);
                    xfer->rxData++;
                    *xfer->rxData = (uint8_t)(tmpData >> 24U);
                }
            }
            xfer->rxData++;
        }
    }

    return kStatus_Success;
}

/*!
 * brief Initializes the FlexIO SPI Master handle, which is used in transactional functions.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param handle Pointer to the flexio_spi_master_handle_t structure to store the transfer state.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_OutOfRange The FlexIO type/handle/ISR table out of range.
 */
status_t FLEXIO_SPI_MasterTransferCreateHandle(FLEXIO_SPI_Type *base,
                                               flexio_spi_master_handle_t *handle,
                                               flexio_spi_master_transfer_callback_t callback,
                                               void *userData)
{
    assert(handle != NULL);

    IRQn_Type flexio_irqs[] = FLEXIO_IRQS;

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Register callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Clear pending NVIC IRQ before enable NVIC IRQ. */
    NVIC_ClearPendingIRQ(flexio_irqs[FLEXIO_SPI_GetInstance(base)]);
    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(flexio_irqs[FLEXIO_SPI_GetInstance(base)]);

    /* Save the context in global variables to support the double weak mechanism. */
    return FLEXIO_RegisterHandleIRQ(base, handle, FLEXIO_SPI_MasterTransferHandleIRQ);
}

/*!
 * brief Master transfer data using IRQ.
 *
 * This function sends data using IRQ. This is a non-blocking function, which returns
 * right away. When all data is sent out/received, the callback function is called.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param handle Pointer to the flexio_spi_master_handle_t structure to store the transfer state.
 * param xfer FlexIO SPI transfer structure. See #flexio_spi_transfer_t.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_FLEXIO_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t FLEXIO_SPI_MasterTransferNonBlocking(FLEXIO_SPI_Type *base,
                                              flexio_spi_master_handle_t *handle,
                                              flexio_spi_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    uint32_t dataMode  = 0;
    uint16_t timerCmp  = (uint16_t)base->flexioBase->TIMCMP[base->timerIndex[0]];
    uint32_t tmpData   = FLEXIO_SPI_DUMMYDATA;
    uint8_t dataFormat = FLEXIO_SPI_XFER_DATA_FORMAT(xfer->flags);

    timerCmp &= 0x00FFU;

    /* Check if SPI is busy. */
    if (handle->state == (uint32_t)kFLEXIO_SPI_Busy)
    {
        return kStatus_FLEXIO_SPI_Busy;
    }

    /* Check if the argument is legal. */
    if ((xfer->txData == NULL) && (xfer->rxData == NULL))
    {
        return kStatus_InvalidArgument;
    }

    /* Timer1 controls the CS signal which enables/disables(asserts/deasserts) when timer0 enable/disable. Timer0
       enables when tx shifter is written and disables when timer compare. The timer compare event causes the
       transmit shift registers to load which generates a tx register empty event. Since when timer stop bit is
       disabled, a timer enable condition can be detected in the same cycle as a timer disable condition, so if
       software writes the tx register upon the detection of tx register empty event, the timer enable condition
       is triggered again, then the CS signal can remain low until software no longer writes the tx register. */
    if ((xfer->flags & (uint8_t)kFLEXIO_SPI_csContinuous) != 0U)
    {
        base->flexioBase->TIMCFG[base->timerIndex[0]] =
            (base->flexioBase->TIMCFG[base->timerIndex[0]] & ~FLEXIO_TIMCFG_TSTOP_MASK) |
            FLEXIO_TIMCFG_TSTOP(kFLEXIO_TimerStopBitDisabled);
    }
    else
    {
        base->flexioBase->TIMCFG[base->timerIndex[0]] =
            (base->flexioBase->TIMCFG[base->timerIndex[0]] & ~FLEXIO_TIMCFG_TSTOP_MASK) |
            FLEXIO_TIMCFG_TSTOP(kFLEXIO_TimerStopBitEnableOnTimerDisable);
    }

    /* Configure the values in handle */
    switch (dataFormat)
    {
        case (uint8_t)kFLEXIO_SPI_8bitMsb:
            dataMode             = (8UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 1U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_8bitLsb:
            dataMode             = (8UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 1U;
            handle->direction    = kFLEXIO_SPI_LsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_16bitMsb:
            dataMode             = (16UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 2U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_16bitLsb:
            dataMode             = (16UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 2U;
            handle->direction    = kFLEXIO_SPI_LsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_32bitMsb:
            dataMode             = (32UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 4U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_32bitLsb:
            dataMode             = (32UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 4U;
            handle->direction    = kFLEXIO_SPI_LsbFirst;
            break;
        default:
            dataMode             = (8UL * 2UL - 1UL) << 8U;
            handle->bytePerFrame = 1U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            assert(true);
            break;
    }

    dataMode |= timerCmp;

    /* Transfer size should be bytesPerFrame divisible. */
    if ((xfer->dataSize % handle->bytePerFrame) != 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* Configure transfer size. */
    base->flexioBase->TIMCMP[base->timerIndex[0]] = dataMode;

    handle->state            = (uint32_t)kFLEXIO_SPI_Busy;
    handle->txData           = xfer->txData;
    handle->rxData           = xfer->rxData;
    handle->rxRemainingBytes = xfer->dataSize;

    /* Save total transfer size. */
    handle->transferSize = xfer->dataSize;

    /* Send first byte of data to trigger the rx interrupt. */
    if (handle->txData != NULL)
    {
        /* Transmit data and update tx size/buff. */
        if (handle->bytePerFrame == 1U)
        {
            tmpData = (uint32_t) * (handle->txData);
            handle->txData++;
        }
        else if (handle->bytePerFrame == 2U)
        {
            if (handle->direction == kFLEXIO_SPI_MsbFirst)
            {
                tmpData = (uint32_t)(handle->txData[0]) << 8U;
                tmpData += (uint32_t)handle->txData[1];
            }
            else
            {
                tmpData = (uint32_t)(handle->txData[1]) << 8U;
                tmpData += (uint32_t)handle->txData[0];
            }
            handle->txData += 2U;
        }
        else
        {
            if (handle->direction == kFLEXIO_SPI_MsbFirst)
            {
                tmpData = (uint32_t)(handle->txData[0]) << 24U;
                tmpData += (uint32_t)(handle->txData[1]) << 16U;
                tmpData += (uint32_t)(handle->txData[2]) << 8U;
                tmpData += (uint32_t)handle->txData[3];
            }
            else
            {
                tmpData = (uint32_t)(handle->txData[3]) << 24U;
                tmpData += (uint32_t)(handle->txData[2]) << 16U;
                tmpData += (uint32_t)(handle->txData[1]) << 8U;
                tmpData += (uint32_t)handle->txData[0];
            }
            handle->txData += 4U;
        }
    }
    else
    {
        tmpData = FLEXIO_SPI_DUMMYDATA;
    }

    handle->txRemainingBytes = xfer->dataSize - handle->bytePerFrame;

    FLEXIO_SPI_WriteData(base, handle->direction, tmpData);

    /* Enable transmit and receive interrupt to handle rx. */
    FLEXIO_SPI_EnableInterrupts(base, (uint32_t)kFLEXIO_SPI_RxFullInterruptEnable);

    return kStatus_Success;
}

/*!
 * brief Gets the data transfer status which used IRQ.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param handle Pointer to the flexio_spi_master_handle_t structure to store the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */
status_t FLEXIO_SPI_MasterTransferGetCount(FLEXIO_SPI_Type *base, flexio_spi_master_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Return remaing bytes in different cases. */
    if (handle->rxData != NULL)
    {
        *count = handle->transferSize - handle->rxRemainingBytes;
    }
    else
    {
        *count = handle->transferSize - handle->txRemainingBytes;
    }

    return kStatus_Success;
}

/*!
 * brief Aborts the master data transfer, which used IRQ.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param handle Pointer to the flexio_spi_master_handle_t structure to store the transfer state.
 */
void FLEXIO_SPI_MasterTransferAbort(FLEXIO_SPI_Type *base, flexio_spi_master_handle_t *handle)
{
    assert(handle != NULL);

    FLEXIO_SPI_DisableInterrupts(base, (uint32_t)kFLEXIO_SPI_RxFullInterruptEnable);
    FLEXIO_SPI_DisableInterrupts(base, (uint32_t)kFLEXIO_SPI_TxEmptyInterruptEnable);

    /* Transfer finished, set the state to idle. */
    handle->state = (uint32_t)kFLEXIO_SPI_Idle;

    /* Clear the internal state. */
    handle->rxRemainingBytes = 0;
    handle->txRemainingBytes = 0;
}

/*!
 * brief FlexIO SPI master IRQ handler function.
 *
 * param spiType Pointer to the FLEXIO_SPI_Type structure.
 * param spiHandle Pointer to the flexio_spi_master_handle_t structure to store the transfer state.
 */
void FLEXIO_SPI_MasterTransferHandleIRQ(void *spiType, void *spiHandle)
{
    assert(spiHandle != NULL);

    flexio_spi_master_handle_t *handle = (flexio_spi_master_handle_t *)spiHandle;
    FLEXIO_SPI_Type *base;
    uint32_t status;

    if (handle->state == (uint32_t)kFLEXIO_SPI_Idle)
    {
        return;
    }

    base   = (FLEXIO_SPI_Type *)spiType;
    status = FLEXIO_SPI_GetStatusFlags(base);

    /* Handle rx. */
    if (((status & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag) != 0U) && (handle->rxRemainingBytes != 0U))
    {
        FLEXIO_SPI_TransferReceiveTransaction(base, handle);
    }

    /* Handle tx. */
    if (((status & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag) != 0U) && (handle->txRemainingBytes != 0U))
    {
        FLEXIO_SPI_TransferSendTransaction(base, handle);
    }

    /* All the transfer finished. */
    if ((handle->txRemainingBytes == 0U) && (handle->rxRemainingBytes == 0U))
    {
        FLEXIO_SPI_MasterTransferAbort(base, handle);
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_FLEXIO_SPI_Idle, handle->userData);
        }
    }
}

/*!
 * brief Initializes the FlexIO SPI Slave handle, which is used in transactional functions.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param handle Pointer to the flexio_spi_slave_handle_t structure to store the transfer state.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_OutOfRange The FlexIO type/handle/ISR table out of range.
 */
status_t FLEXIO_SPI_SlaveTransferCreateHandle(FLEXIO_SPI_Type *base,
                                              flexio_spi_slave_handle_t *handle,
                                              flexio_spi_slave_transfer_callback_t callback,
                                              void *userData)
{
    assert(handle != NULL);

    IRQn_Type flexio_irqs[] = FLEXIO_IRQS;

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Register callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Clear pending NVIC IRQ before enable NVIC IRQ. */
    NVIC_ClearPendingIRQ(flexio_irqs[FLEXIO_SPI_GetInstance(base)]);
    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(flexio_irqs[FLEXIO_SPI_GetInstance(base)]);

    /* Save the context in global variables to support the double weak mechanism. */
    return FLEXIO_RegisterHandleIRQ(base, handle, FLEXIO_SPI_SlaveTransferHandleIRQ);
}

/*!
 * brief Slave transfer data using IRQ.
 *
 * This function sends data using IRQ. This is a non-blocking function, which returns
 * right away. When all data is sent out/received, the callback function is called.
 * param handle Pointer to the flexio_spi_slave_handle_t structure to store the transfer state.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 * param xfer FlexIO SPI transfer structure. See #flexio_spi_transfer_t.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_FLEXIO_SPI_Busy SPI is not idle; it is running another transfer.
 */
status_t FLEXIO_SPI_SlaveTransferNonBlocking(FLEXIO_SPI_Type *base,
                                             flexio_spi_slave_handle_t *handle,
                                             flexio_spi_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    uint32_t dataMode  = 0;
    uint8_t dataFormat = FLEXIO_SPI_XFER_DATA_FORMAT(xfer->flags);

    /* Check if SPI is busy. */
    if (handle->state == (uint32_t)kFLEXIO_SPI_Busy)
    {
        return kStatus_FLEXIO_SPI_Busy;
    }

    /* Check if the argument is legal. */
    if ((xfer->txData == NULL) && (xfer->rxData == NULL))
    {
        return kStatus_InvalidArgument;
    }

    /* SCK timer use CS pin as inverted trigger so timer should be disbaled on trigger falling edge(CS re-asserts). */
    /* However if CPHA is first edge mode, timer will restart each time right after timer compare event occur and
       before CS pin re-asserts, which triggers another shifter load. To avoid this, when in CS dis-continuous mode,
       timer should disable in timer compare rather than trigger falling edge(CS re-asserts), and in CS continuous mode,
       tx/rx shifters should be flushed after transfer finishes and before next transfer starts. */
    FLEXIO_SPI_FlushShifters(base);
    if ((xfer->flags & (uint8_t)kFLEXIO_SPI_csContinuous) != 0U)
    {
        base->flexioBase->TIMCFG[base->timerIndex[0]] |= FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnTriggerFallingEdge);
    }
    else
    {
        if ((base->flexioBase->SHIFTCTL[base->shifterIndex[0]] & FLEXIO_SHIFTCTL_TIMPOL_MASK) ==
            FLEXIO_SHIFTCTL_TIMPOL(kFLEXIO_ShifterTimerPolarityOnNegitive))
        {
            base->flexioBase->TIMCFG[base->timerIndex[0]] =
                (base->flexioBase->TIMCFG[base->timerIndex[0]] & ~FLEXIO_TIMCFG_TIMDIS_MASK) |
                FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnTimerCompare);
        }
        else
        {
            base->flexioBase->TIMCFG[base->timerIndex[0]] =
                (base->flexioBase->TIMCFG[base->timerIndex[0]] & ~FLEXIO_TIMCFG_TIMDIS_MASK) |
                FLEXIO_TIMCFG_TIMDIS(kFLEXIO_TimerDisableOnTriggerFallingEdge);
        }
    }

    /* Configure the values in handle */
    switch (dataFormat)
    {
        case (uint8_t)kFLEXIO_SPI_8bitMsb:
            dataMode             = 8U * 2U - 1U;
            handle->bytePerFrame = 1U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_8bitLsb:
            dataMode             = 8U * 2U - 1U;
            handle->bytePerFrame = 1U;
            handle->direction    = kFLEXIO_SPI_LsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_16bitMsb:
            dataMode             = 16U * 2U - 1U;
            handle->bytePerFrame = 2U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_16bitLsb:
            dataMode             = 16U * 2U - 1U;
            handle->bytePerFrame = 2U;
            handle->direction    = kFLEXIO_SPI_LsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_32bitMsb:
            dataMode             = 32UL * 2UL - 1UL;
            handle->bytePerFrame = 4U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            break;
        case (uint8_t)kFLEXIO_SPI_32bitLsb:
            dataMode             = 32UL * 2UL - 1UL;
            handle->bytePerFrame = 4U;
            handle->direction    = kFLEXIO_SPI_LsbFirst;
            break;
        default:
            dataMode             = 8UL * 2UL - 1UL;
            handle->bytePerFrame = 1U;
            handle->direction    = kFLEXIO_SPI_MsbFirst;
            assert(true);
            break;
    }

    /* Transfer size should be bytesPerFrame divisible. */
    if ((xfer->dataSize % handle->bytePerFrame) != 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* Configure transfer size. */
    base->flexioBase->TIMCMP[base->timerIndex[0]] = dataMode;

    handle->state            = (uint32_t)kFLEXIO_SPI_Busy;
    handle->txData           = xfer->txData;
    handle->rxData           = xfer->rxData;
    handle->txRemainingBytes = xfer->dataSize;
    handle->rxRemainingBytes = xfer->dataSize;

    /* Save total transfer size. */
    handle->transferSize = xfer->dataSize;

    /* Enable transmit and receive interrupt to handle tx and rx. */
    FLEXIO_SPI_EnableInterrupts(base, (uint32_t)kFLEXIO_SPI_TxEmptyInterruptEnable);
    FLEXIO_SPI_EnableInterrupts(base, (uint32_t)kFLEXIO_SPI_RxFullInterruptEnable);

    return kStatus_Success;
}

/*!
 * brief FlexIO SPI slave IRQ handler function.
 *
 * param spiType Pointer to the FLEXIO_SPI_Type structure.
 * param spiHandle Pointer to the flexio_spi_slave_handle_t structure to store the transfer state.
 */
void FLEXIO_SPI_SlaveTransferHandleIRQ(void *spiType, void *spiHandle)
{
    assert(spiHandle != NULL);

    flexio_spi_master_handle_t *handle = (flexio_spi_master_handle_t *)spiHandle;
    FLEXIO_SPI_Type *base;
    uint32_t status;

    if (handle->state == (uint32_t)kFLEXIO_SPI_Idle)
    {
        return;
    }

    base   = (FLEXIO_SPI_Type *)spiType;
    status = FLEXIO_SPI_GetStatusFlags(base);

    /* Handle tx. */
    if (((status & (uint32_t)kFLEXIO_SPI_TxBufferEmptyFlag) != 0U) && (handle->txRemainingBytes != 0U))
    {
        FLEXIO_SPI_TransferSendTransaction(base, handle);
    }

    /* Handle rx. */
    if (((status & (uint32_t)kFLEXIO_SPI_RxBufferFullFlag) != 0U) && (handle->rxRemainingBytes != 0U))
    {
        FLEXIO_SPI_TransferReceiveTransaction(base, handle);
    }

    /* All the transfer finished. */
    if ((handle->txRemainingBytes == 0U) && (handle->rxRemainingBytes == 0U))
    {
        FLEXIO_SPI_SlaveTransferAbort(base, handle);
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_FLEXIO_SPI_Idle, handle->userData);
        }
    }
}

/*!
 * brief Flush tx/rx shifters.
 *
 * param base Pointer to the FLEXIO_SPI_Type structure.
 */
void FLEXIO_SPI_FlushShifters(FLEXIO_SPI_Type *base)
{
    /* Disable then re-enable to flush the tx shifter. */
    base->flexioBase->SHIFTCTL[base->shifterIndex[0]] &= ~FLEXIO_SHIFTCTL_SMOD_MASK;
    base->flexioBase->SHIFTCTL[base->shifterIndex[0]] |= FLEXIO_SHIFTCTL_SMOD(kFLEXIO_ShifterModeTransmit);
    /* Read to flush the rx shifter. */
    (void)base->flexioBase->SHIFTBUF[base->shifterIndex[1]];
}
