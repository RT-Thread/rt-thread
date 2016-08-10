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

#include "fsl_flexio_spi_hal.h"
#include <string.h>
/*---------------------------------------------------------------------------
 * Configure.
 *-------------------------------------------------------------------------*/
/* Master. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_ConfigMaster
 * Description: Configure the flexio working as spi master.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_SPI_HAL_ConfigMaster(flexio_spi_dev_t *devPtr, 
    const flexio_spi_master_config_t *configPtr)
{
    flexio_shifter_config_t mFlexioShfiterConfigStruct;
    flexio_timer_config_t mFlexioTimerConfigStruct;
    memset(&mFlexioShfiterConfigStruct, 0, sizeof(mFlexioShfiterConfigStruct));
    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));
    uint32_t timdiv = 0U, timcmp = 0U;
    
    if ( (!devPtr) || (!configPtr) )
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    /* 1. Configure shifter 0 for tx. */
    if (configPtr->cphaOneEnable)
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutput;
        mFlexioShfiterConfigStruct.pinsel = devPtr->txPinIdx; /* MOSI */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeTransmit;
        mFlexioShfiterConfigStruct.insrc  = kFlexioShifterInputFromPin;
        mFlexioShfiterConfigStruct.sstop  = kFlexioShifterStopBitLow;
        mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnShift;
    }
    else
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutput;
        mFlexioShfiterConfigStruct.pinsel = devPtr->txPinIdx; /* MOSI */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeTransmit;
        mFlexioShfiterConfigStruct.insrc  = kFlexioShifterInputFromPin;
        mFlexioShfiterConfigStruct.sstop  = kFlexioShifterStopBitDisable;
        mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    }
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[0], &mFlexioShfiterConfigStruct);
    
    /* 2. Configure shifter 1 for rx. */
    if (configPtr->cphaOneEnable)
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
        mFlexioShfiterConfigStruct.pinsel = devPtr->rxPinIdx; /* MISO */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeReceive;
    }
    else
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
        mFlexioShfiterConfigStruct.pinsel = devPtr->rxPinIdx; /* MISO */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeReceive;
    }
    mFlexioShfiterConfigStruct.insrc  = kFlexioShifterInputFromPin;
    mFlexioShfiterConfigStruct.sstop  = kFlexioShifterStopBitDisable;
    mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[1], &mFlexioShfiterConfigStruct);

    /* 3. Configure timer 1 for csn. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_TIMn(devPtr->timerIdx[0]);
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveHigh;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioTimerConfigStruct.pinsel = devPtr->csnPinIdx; /* CSn. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveLow;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeSingle16Bit;
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnPreTimerDisable;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnPrevTimerEnable;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitDisabled;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitDisabled;
    mFlexioTimerConfigStruct.timcmp = 0xFFFFU;
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[1], &mFlexioTimerConfigStruct);

    /* 4. Configure timer 0 for sclk. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_SHIFTnSTAT(devPtr->shifterIdx[0]);
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveLow;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioTimerConfigStruct.pinsel = devPtr->sclkPinIdx; /* SCLK. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeDual8BitBaudBit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputZeroNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTimerCompare;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnTriggerHigh;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitEnableOnTimerDisable;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;
    timdiv = (configPtr->flexioBusClk) / (configPtr->baudrate);
    timcmp = ( (configPtr->bitCount << 1U) - 1U )  << 8U;
    timcmp |= ( (timdiv >> 1U) - 1U);
    mFlexioTimerConfigStruct.timcmp = timcmp;
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[0], &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/* Slave. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_ConfigSlave
 * Description: Configure the flexio working as spi slave.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_SPI_HAL_ConfigSlave(flexio_spi_dev_t *devPtr,
    const flexio_spi_slave_config_t *configPtr)
{
    flexio_shifter_config_t mFlexioShfiterConfigStruct;
    flexio_timer_config_t mFlexioTimerConfigStruct;
    memset(&mFlexioShfiterConfigStruct, 0, sizeof(mFlexioShfiterConfigStruct));
    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));

    if ( (!devPtr) || (!configPtr) )
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    /* 1. Configure shifter 0 for tx. */
    if (configPtr->cphaOneEnable)
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutput;
        mFlexioShfiterConfigStruct.pinsel = devPtr->txPinIdx; /* MISO */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode = kFlexioShifterModeTransmit;
        mFlexioShfiterConfigStruct.insrc = kFlexioShifterInputFromPin;
        mFlexioShfiterConfigStruct.sstop = kFlexioShifterStopBitDisable;
        mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnShift;
    }
    else
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutput;
        mFlexioShfiterConfigStruct.pinsel = devPtr->txPinIdx; /* MISO */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeTransmit;
        mFlexioShfiterConfigStruct.insrc  = kFlexioShifterInputFromPin;
        mFlexioShfiterConfigStruct.sstop  = kFlexioShifterStopBitDisable;
        mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    }
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[0], &mFlexioShfiterConfigStruct);

    /* 2. Configure shifter 1 for tx. */
    if (configPtr->cphaOneEnable)
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
        mFlexioShfiterConfigStruct.pinsel = devPtr->rxPinIdx; /* MOSI */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeReceive;
    }
    else
    {
        mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[0];
        mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
        mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
        mFlexioShfiterConfigStruct.pinsel = devPtr->rxPinIdx; /* MOSI */
        mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh;
        mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeReceive;
    }
    mFlexioShfiterConfigStruct.insrc = kFlexioShifterInputFromPin;
    mFlexioShfiterConfigStruct.sstop = kFlexioShifterStopBitDisable;
    mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx[1], &mFlexioShfiterConfigStruct);
    
    /* 3. Configure timer 1 for csn. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(devPtr->csnPinIdx);  /* CSn. */
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveLow;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceExternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioTimerConfigStruct.pinsel = devPtr->sclkPinIdx; /* SCLK. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeSingle16Bit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputZeroNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnPinInputShiftPinInput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTriggerFallingEdge;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnTriggerRisingEdge;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitDisabled;
    if (configPtr->cphaOneEnable)
    {
        mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;
    }
    else
    {
        mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitDisabled;
    }
    mFlexioTimerConfigStruct.timcmp = ( (configPtr->bitCount << 1U) - 1U );
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx[0], &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/*---------------------------------------------------------------------------
 * Tx.
 *-------------------------------------------------------------------------*/
 /* Status flag and interrupt. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetTxBufferEmptyFlag
 * Description: Get the flag if the tx buffer is empty.
 *
 *END*********************************************************************/
bool FLEXIO_SPI_HAL_GetTxBufferEmptyFlag(flexio_spi_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[0])) 
            & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_ClearTxBufferEmptyFlag
 * Description: Clear the flag that tx buffer is empty.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_ClearTxBufferEmptyFlag(flexio_spi_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd
 * Description: Switch on/off the interrupt for event of tx buffer empty.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(flexio_spi_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetTxErrFlag
 * Description: Get the flag of tx error.
 *
 *END*********************************************************************/
/* Error flag and interrupt. */
bool FLEXIO_SPI_HAL_GetTxErrFlag(flexio_spi_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[0])) 
            & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_ClearTxErrFlag
 * Description: Clear the flag of tx error manually.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_ClearTxErrFlag(flexio_spi_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_SetTxErrIntCmd
 * Description: Switch on/off the interrupt for tx error event.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_SetTxErrIntCmd(flexio_spi_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]), enable);
}

/* Data buffer. */

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_PutDataMSB
 * Description: Put the data to tx buffer as MSB transfer.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_PutDataMSB(flexio_spi_dev_t *devPtr, uint32_t dat)
{
    /* SHIFTBUFBBS for MSB. */
    FLEXIO_HAL_SetShifterBufferBitSwapped(
            devPtr->flexioBase, devPtr->shifterIdx[0], dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_PutDataMSBPolling
 * Description: Put the data to tx buffer as MSB transfer when empty.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_PutDataMSBPolling(flexio_spi_dev_t *devPtr, uint32_t dat)
{
    while ( !FLEXIO_SPI_HAL_GetTxBufferEmptyFlag(devPtr) ) {}
    FLEXIO_SPI_HAL_PutDataMSB(devPtr, dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_PutDataLSB
 * Description: Put the data to tx buffer as LSB transfer.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_PutDataLSB(flexio_spi_dev_t *devPtr, uint32_t dat)
{
    FLEXIO_HAL_SetShifterBuffer(
            devPtr->flexioBase, devPtr->shifterIdx[0], dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_PutDataLSBPolling
 * Description: Put the data to tx buffer as LSB transfer when empty.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_PutDataLSBPolling(flexio_spi_dev_t *devPtr, uint32_t dat)
{
    while ( !FLEXIO_SPI_HAL_GetTxBufferEmptyFlag(devPtr) ) {}
    FLEXIO_SPI_HAL_PutDataLSB(devPtr, dat);
}

/* DMA. */

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_SetTxDmaCmd
 * Description: Switch on/off the DMA support for tx event.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_SetTxDmaCmd(flexio_spi_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
            devPtr->flexioBase, 1U <<(devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetTxBufferMSBAddr
 * Description: Get the tx MSB buffer's register for DMA use.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetTxBufferMSBAddr(flexio_spi_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBIS_REG(devPtr->flexioBase, devPtr->shifterIdx[0])));
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetTxBufferLSBAddr
 * Description: Get the tx LSB buffer's register for DMA use.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetTxBufferLSBAddr(flexio_spi_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUF_REG(devPtr->flexioBase, devPtr->shifterIdx[0])));
}

/*---------------------------------------------------------------------------
 * Rx.
 *-------------------------------------------------------------------------*/

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetRxBufferFullFlag
 * Description: Get the flag if the rx buffer is full.
 *
 *END*********************************************************************/
bool FLEXIO_SPI_HAL_GetRxBufferFullFlag(flexio_spi_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[1])) 
            & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_ClearRxBufferFullFlag
 * Description: Clear the flag of rx buffer full manually.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_ClearRxBufferFullFlag(flexio_spi_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_SetRxBufferFullIntCmd
 * Description: Switch on/off the interrupt of rx buffer full event.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(flexio_spi_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]), enable );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetRxErrFlag
 * Description: Get the flag of rx error.
 *
 *END*********************************************************************/
bool FLEXIO_SPI_HAL_GetRxErrFlag(flexio_spi_dev_t *devPtr)
{
    return ( 0U != ( (1U << devPtr->shifterIdx[1]) 
            & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_ClearRxErrFlag
 * Description: Clear the flag of rx error manually.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_ClearRxErrFlag(flexio_spi_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_SetRxErrIntCmd
 * Description: Switch on/off the interrupt of the rx error event.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_SetRxErrIntCmd(flexio_spi_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]), enable);
}

/* Data. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetDataMSB
 * Description: Get the data from rx MSB buffer. 
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetDataMSB(flexio_spi_dev_t *devPtr)
{
    return FLEXIO_HAL_GetShifterBufferBitSwapped(
            devPtr->flexioBase, devPtr->shifterIdx[1]);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetDataMSBPolling
 * Description: Get the data from rx MSB buffer when full.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetDataMSBPolling(flexio_spi_dev_t *devPtr)
{
    while ( !FLEXIO_SPI_HAL_GetRxBufferFullFlag(devPtr) ) {}
    return FLEXIO_SPI_HAL_GetDataMSB(devPtr);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetDataLSB
 * Description: Get the data from rx LSB buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetDataLSB(flexio_spi_dev_t *devPtr)
{
    return FLEXIO_HAL_GetShifterBuffer(
            devPtr->flexioBase, devPtr->shifterIdx[1]);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetDataLSBPolling
 * Description: Get the data from rx LSB buffer when full.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetDataLSBPolling(flexio_spi_dev_t *devPtr)
{
    while ( !FLEXIO_SPI_HAL_GetRxBufferFullFlag(devPtr) ) {}
    return FLEXIO_SPI_HAL_GetDataLSB(devPtr);
}

/* DMA. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_SetRxDmaCmd
 * Description: Switch on/off the DMA for rx event.
 *
 *END*********************************************************************/
void FLEXIO_SPI_HAL_SetRxDmaCmd(flexio_spi_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
        devPtr->flexioBase, 1U <<(devPtr->shifterIdx[1]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetRxBufferMSBAddr
 * Description: Get the address of rx MSB buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetRxBufferMSBAddr(flexio_spi_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBIS_REG(devPtr->flexioBase, devPtr->shifterIdx[1])));
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_SPI_HAL_GetRxBufferLSBAddr
 * Description: Get the address of rx LSB buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_SPI_HAL_GetRxBufferLSBAddr(flexio_spi_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUF_REG(devPtr->flexioBase, devPtr->shifterIdx[1])));
}

/******************************************************************************
 * EOF
 *****************************************************************************/

