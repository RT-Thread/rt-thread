/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#include "fsl_flexio_i2s_hal.h"
#include <string.h>
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*------------------------------------------------------------------------
 * Configure.
 -----------------------------------------------------------------------*/
/* Master. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_Configure_Master
 * Description: Configure the flexio working as i2s master device.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_I2S_HAL_Configure_Master(
    flexio_i2s_dev_t *devPtr, const flexio_i2s_master_config_t *configPtr)
{
    flexio_timer_config_t mFlexioTimerConfigStruct;
    flexio_shifter_config_t mFlexioShifterConfigStruct;
    uint32_t tmpdiv = 0xFFU & ((configPtr->flexioBusClk) / (configPtr->bitClk));
    
    if (!devPtr)
    {
        return kStatus_FLEXIO_InvalidArgument;
    }
    memset(&mFlexioShifterConfigStruct, 0, sizeof(mFlexioShifterConfigStruct));
    /* 1. Configure the shifter 0 for tx. */
    mFlexioShifterConfigStruct.timsel = devPtr->timerIdx[0];
    mFlexioShifterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
    mFlexioShifterConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioShifterConfigStruct.pinsel = devPtr->txPinIdx; /* TxPin. */
    mFlexioShifterConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioShifterConfigStruct.smode  = kFlexioShifterModeTransmit; /* Tx. */
    mFlexioShifterConfigStruct.insrc = kFlexioShifterInputFromPin;
    mFlexioShifterConfigStruct.sstop = kFlexioShifterStopBitDisable;  /* Stop disable. */
    mFlexioShifterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnShift;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[0], &mFlexioShifterConfigStruct);
    /* Clear the status flag immediately after setting shifter the work mode. */
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx[0]) );
    
    memset(&mFlexioShifterConfigStruct, 0, sizeof(mFlexioShifterConfigStruct));
    /* 2. Configure the shifter 1 for rx. */
    mFlexioShifterConfigStruct.timsel = devPtr->timerIdx[0];
    mFlexioShifterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
    mFlexioShifterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioShifterConfigStruct.pinsel = devPtr->rxPinIdx; /* RxPin. */
    mFlexioShifterConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioShifterConfigStruct.smode  = kFlexioShifterModeReceive; /* Rx. */
    mFlexioShifterConfigStruct.insrc = kFlexioShifterInputFromPin;
    mFlexioShifterConfigStruct.sstop = kFlexioShifterStopBitDisable;  /* Stop disable. */
    mFlexioShifterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[1], &mFlexioShifterConfigStruct);
    /* Clear the status flag immediately after setting shifter the work mode. */
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
    
    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));
    /* 3. Confiugre the timer 1 as sync frame clock. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(devPtr->txPinIdx);
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveHigh;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceExternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioTimerConfigStruct.pinsel = devPtr->wsPinIdx; /* WS. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveLow;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeSingle16Bit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableNever;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnPrevTimerEnable;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitDisabled;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitDisabled;
    /* Configure 32-bit transfer with baud rate of divide by 4 of the FlexIO
     * clock. Set TIMCMP[15:0] = (number of bits x baudrate divider) - 1. */
    mFlexioTimerConfigStruct.timcmp = 32 * tmpdiv - 1U; /* 0x7FU, Dummy value currently. */
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[1], &mFlexioTimerConfigStruct);

    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));
    /* 4. Configure the timer 0 as bit clock trigger by shifter 0. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_SHIFTnSTAT(devPtr->shifterIdx[0]);
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveLow;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioTimerConfigStruct.pinsel = devPtr->sckPinIdx; /* SCK. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeDual8BitBaudBit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableNever;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnTriggerHigh;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitDisabled;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;
    /* Configure 32-bit transfer with baud rate of divide by 4 of the FlexIO
     * clock. Set TIMCMP[15:8] = (number of bits x 2) - 1.
     * Set TIMCMP[7:0] = (baud rate divider /2) - 1. */
    mFlexioTimerConfigStruct.timcmp = tmpdiv / 2U - 1U;
    mFlexioTimerConfigStruct.timcmp |= (32 * 2U - 1U) << 8U;
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[0], &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/* Slave. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_Configure_Slave
 * Description: Configure the flexio working as i2s slave device.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_I2S_HAL_Configure_Slave(
    flexio_i2s_dev_t *devPtr, const flexio_i2s_slave_config_t *configPtr)
{
    flexio_timer_config_t mFlexioTimerConfigStruct;
    flexio_shifter_config_t mFlexioShifterConfigStruct;

    if (!devPtr)
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    memset(&mFlexioShifterConfigStruct, 0, sizeof(mFlexioShifterConfigStruct));
    /* 1. Configure the shifter 0 for tx. */
    mFlexioShifterConfigStruct.timsel = devPtr->timerIdx[1];
    mFlexioShifterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
    mFlexioShifterConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioShifterConfigStruct.pinsel = devPtr->txPinIdx; /* Pin0. */
    mFlexioShifterConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioShifterConfigStruct.smode  = kFlexioShifterModeTransmit; /* Tx. */
    mFlexioShifterConfigStruct.insrc = kFlexioShifterInputFromPin;
    mFlexioShifterConfigStruct.sstop = kFlexioShifterStopBitDisable;  /* Stop disable. */
    mFlexioShifterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[0], &mFlexioShifterConfigStruct);
    /* Clear the status flag immediately after setting shifter the work mode. */
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx[0]) );

    memset(&mFlexioShifterConfigStruct, 0, sizeof(mFlexioShifterConfigStruct));
    /* 2. Configure the shifter 1 for rx. */
    mFlexioShifterConfigStruct.timsel = devPtr->timerIdx[1];
    mFlexioShifterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
    mFlexioShifterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioShifterConfigStruct.pinsel = devPtr->rxPinIdx; /* Pin1. */
    mFlexioShifterConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioShifterConfigStruct.smode  = kFlexioShifterModeReceive; /* Rx. */
    mFlexioShifterConfigStruct.insrc = kFlexioShifterInputFromPin;
    mFlexioShifterConfigStruct.sstop = kFlexioShifterStopBitDisable;  /* Stop disable. */
    mFlexioShifterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[1], &mFlexioShifterConfigStruct);
    /* Clear the status flag immediately after setting shifter the work mode. */
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );

    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));
    /* 3. Configure the timer 1 as bit clock trigger by shifter 0. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_TIMn(devPtr->timerIdx[0]); /* timer0. */
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveHigh;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioTimerConfigStruct.pinsel = devPtr->sckPinIdx; /* Pin2. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeSingle16Bit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnPinInputShiftPinInput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTimerCompareTriggerLow;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnPinRisingEdgeTriggerHigh;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitDisabled;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitDisabled;
    /* Configure 32-bit transfer with baud rate of divide by 4 of the FlexIO
     * clock. Set TIMCMP[15:0] = (number of bits x baudrate divider) - 1. */
    mFlexioTimerConfigStruct.timcmp = configPtr->bitCount * 2U - 1U; /* 0x7FU, Dummy value currently. */
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[1], &mFlexioTimerConfigStruct);

    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));
    /* 4. Configure the timer 0 as sync frame clock. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(devPtr->sckPinIdx); /* Pin2. */
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveHigh;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioTimerConfigStruct.pinsel = devPtr->wsPinIdx; /* Pin3. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveLow;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeSingle16Bit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnTriggerInputShiftTriggerInput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTimerCompare;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnPinRisingEdge;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitDisabled;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitDisabled;
    /* Configure two 32-bit transfers per frame. Set TIMCMP[15:0] = (number of bits x 4) - 3. */
    mFlexioTimerConfigStruct.timcmp = configPtr->bitCount * 4U - 3U;
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[0], &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/*---------------------------------------------------------------------------
 * Tx.
 --------------------------------------------------------------------------*/
/* Status flag and interrupt. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetTxBufferEmptyFlag
 * Description: Get the flag that tx buffer is empty.
 *
 *END*********************************************************************/
bool FLEXIO_I2S_HAL_GetTxBufferEmptyFlag(flexio_i2s_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[0])) 
               & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_ClearTxBufferEmptyFlag
 * Description: Clear the tx buffer empty flag manually.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_ClearTxBufferEmptyFlag(flexio_i2s_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, (1U << devPtr->shifterIdx[0]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_SetTxBufferEmptyIntCmd
 * Description: Switch on/off the interrupt for tx buffer empty.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_SetTxBufferEmptyIntCmd(flexio_i2s_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
        devPtr->flexioBase, (1U << devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetTxBufferEmptyIntCmd
 * Description: Get the current setting of interrupt switcher.
 *
 *END*********************************************************************/
bool FLEXIO_I2S_HAL_GetTxBufferEmptyIntCmd(flexio_i2s_dev_t *devPtr)
{
    return ( 0U != ((1U << (devPtr->shifterIdx[0]))
            & FLEXIO_HAL_GetShifterStatusIntCmd(devPtr->flexioBase)) );
}

/* Error flag and interrupt. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetTxErrFlag
 * Description: Get the rx error flag.
 *
 *END*********************************************************************/
bool FLEXIO_I2S_HAL_GetTxErrFlag(flexio_i2s_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[0])) 
            & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_ClearTxErrFlag
 * Description: Clear the tx error flag manually.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_ClearTxErrFlag(flexio_i2s_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
        devPtr->flexioBase, (1U << devPtr->shifterIdx[0]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_SetTxErrIntCmd
 * Description: Switch on/off the interrupt for tx error.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_SetTxErrIntCmd(flexio_i2s_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
        devPtr->flexioBase, (1U << devPtr->shifterIdx[0]), enable);
}

/* Data buffer. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_PutData
 * Description: Put the data into tx buffer.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_PutData(flexio_i2s_dev_t *devPtr, uint32_t dat)
{
    FLEXIO_HAL_SetShifterBufferBitSwapped(
        devPtr->flexioBase, devPtr->shifterIdx[0], dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_PutDataPolling
 * Description: Put the data into tx buffer when empty.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_PutDataPolling(flexio_i2s_dev_t *devPtr, uint32_t dat)
{
    while ( !FLEXIO_I2S_HAL_GetTxBufferEmptyFlag(devPtr) ) {}
    FLEXIO_I2S_HAL_PutData(devPtr, dat);
}

/* DMA. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_SetTxDmaCmd
 * Description: Switch on/off the tx DMA support.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_SetTxDmaCmd(flexio_i2s_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
        devPtr->flexioBase, 1U <<(devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetTxBufferAddr
 * Description: Get the address of tx buffer when using DMA.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2S_HAL_GetTxBufferAddr(flexio_i2s_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBIS_REG(devPtr->flexioBase, devPtr->shifterIdx[0])));
}

/*---------------------------------------------------------------------------
 * Rx.
 --------------------------------------------------------------------------*/
/* Status flag and interrupt. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetRxBufferFullFlag
 * Description: Get the flag if the rx buffer is full.
 *
 *END*********************************************************************/
bool FLEXIO_I2S_HAL_GetRxBufferFullFlag(flexio_i2s_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[1])) 
                & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_ClearRxBufferFullFlag
 * Description: Clear the rx buffer full flag.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_ClearRxBufferFullFlag(flexio_i2s_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_SetRxBufferFullIntCmd
 * Description: Switch on/off the interrupt for rx buffer full.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_SetRxBufferFullIntCmd(flexio_i2s_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]), enable );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetRxBufferFullIntCmd
 * Description: Get the current setting of tx buffer full interrupt.
 *
 *END*********************************************************************/
bool FLEXIO_I2S_HAL_GetRxBufferFullIntCmd(flexio_i2s_dev_t *devPtr)
{
    return ( 0U != ((1U << (devPtr->shifterIdx[1]))
                   & FLEXIO_HAL_GetShifterStatusIntCmd(devPtr->flexioBase)) );
}

/* Error flag and interrupt. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetRxErrFlag
 * Description: Get the flag if rx error.
 *
 *END*********************************************************************/
bool FLEXIO_I2S_HAL_GetRxErrFlag(flexio_i2s_dev_t *devPtr)
{
    return ( 0U != ( (1U << devPtr->shifterIdx[1]) 
                   & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_ClearRxErrFlag
 * Description: Clear the rx error flag manually.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_ClearRxErrFlag(flexio_i2s_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_SetRxErrIntCmd
 * Description: Switch on/off the interrupt for rx error event.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_SetRxErrIntCmd(flexio_i2s_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]), enable);
}

/* Data buffer. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetData
 * Description: Get the data from rx buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2S_HAL_GetData(flexio_i2s_dev_t *devPtr)
{
    return FLEXIO_HAL_GetShifterBufferBitSwapped(
                devPtr->flexioBase, devPtr->shifterIdx[1]);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetDataPolling
 * Description: Get the data from rx buffer when full.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2S_HAL_GetDataPolling(flexio_i2s_dev_t *devPtr)
{
    while ( !FLEXIO_I2S_HAL_GetRxBufferFullFlag(devPtr) ) {}
    return FLEXIO_I2S_HAL_GetData(devPtr);
}

/*-------------------------------------------------------------------------
 * DMA.
 ------------------------------------------------------------------------*/
 /*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_SetRxDmaCmd
 * Description: Switch on/off the rx DMA support.
 *
 *END*********************************************************************/
void FLEXIO_I2S_HAL_SetRxDmaCmd(flexio_i2s_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
        devPtr->flexioBase, 1U <<(devPtr->shifterIdx[1]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2S_HAL_GetRxBufferAddr
 * Description: Get the address of rx buffer when using DMA.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2S_HAL_GetRxBufferAddr(flexio_i2s_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBIS_REG(devPtr->flexioBase, devPtr->shifterIdx[1])));
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

