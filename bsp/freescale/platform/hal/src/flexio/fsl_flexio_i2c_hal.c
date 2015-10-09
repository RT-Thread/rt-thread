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

#include "fsl_flexio_i2c_hal.h"
#include "fsl_flexio_hal.h"
#include <string.h>
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*------------------------------------------------------------------------
 * Configure.
 *----------------------------------------------------------------------*/
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ConfigMaster
 * Description: Configure the flexio working as i2c master device.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_I2C_HAL_ConfigMaster(flexio_i2c_dev_t *devPtr, 
    const flexio_i2c_master_config_t *configPtr)
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

    /* 1. Configure the shifter 0 for tx. */
    mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[1];
    mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
    mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOpenDrainOrBidirection;
    mFlexioShfiterConfigStruct.pinsel = devPtr->sdaPinIdx; /* Pin 0. */
    mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveLow;
    mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeTransmit; /* Tx. */
    mFlexioShfiterConfigStruct.insrc  = kFlexioShifterInputFromPin;
    mFlexioShfiterConfigStruct.sstop  = kFlexioShifterStopBitHigh; /* Check ACK Tx. */
    mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitLow; /* Start after low ACK. */
    FLEXIO_HAL_ConfigureShifter(
            devPtr->flexioBase, devPtr->shifterIdx[0], &mFlexioShfiterConfigStruct);

    /* 2. Configure the shifter 1 for rx. */
    mFlexioShfiterConfigStruct.timsel = devPtr->timerIdx[1];
    mFlexioShfiterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
    mFlexioShfiterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioShfiterConfigStruct.pinsel = devPtr->sdaPinIdx; /* Pin 0. */
    mFlexioShfiterConfigStruct.pinpol = kFlexioPinActiveHigh; /*inverted or not*/
    mFlexioShfiterConfigStruct.smode  = kFlexioShifterModeReceive; /* Rx. */
    mFlexioShfiterConfigStruct.insrc  = kFlexioShifterInputFromPin;
    mFlexioShfiterConfigStruct.sstop  = kFlexioShifterStopBitLow; /* Check ACK Rx. */
    mFlexioShfiterConfigStruct.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable; /* Do not check start Rx. */
    FLEXIO_HAL_ConfigureShifter(
            devPtr->flexioBase, devPtr->shifterIdx[1], &mFlexioShfiterConfigStruct);

    /* 3. Configure the timer 0 for generating bit clock. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_SHIFTnSTAT(devPtr->shifterIdx[0]); /* trigger from tx shifter. */
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveLow;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOpenDrainOrBidirection;
    mFlexioTimerConfigStruct.pinsel = devPtr->sckPinIdx; /* Pin 1. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeDual8BitBaudBit; /* To generate baudrate. */
    
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputZeroNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetOnTimerPinEqualToTimerOutput;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTimerCompare;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnTriggerHigh;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitEnableOnTimerDisable;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;

    /*
     * Set TIMCMP[15:8] = (number of words x 18) + 1. 
     * Set TIMCMP[7:0] = (baud rate divider / 2) - 1.
     */
    timdiv = configPtr->flexioBusClk / configPtr->baudrate;
    timcmp = configPtr->xferWordCount * 18U + 1U;
    timcmp <<= 8U;
    timcmp |= timdiv / 2U - 1U;
    mFlexioTimerConfigStruct.timcmp = timcmp;
    FLEXIO_HAL_ConfigureTimer(
            devPtr->flexioBase, devPtr->timerIdx[0], &mFlexioTimerConfigStruct);

    /* 4. Configure the timer 1 for controlling shifters. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_SHIFTnSTAT(devPtr->shifterIdx[0]); /* trigger from tx shifter. */
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveLow;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal; /* trigger no sense here. */
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioTimerConfigStruct.pinsel = devPtr->sckPinIdx; /* Pin 1. */
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveLow;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeSingle16Bit;
    
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset; /* no sense here. */
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnPinInputShiftPinInput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnPreTimerDisable;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnPrevTimerEnable;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitEnableOnTimerCompare;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;

    /* Set TIMCMP[15:0] = (number of bits x 2) - 1 */
    mFlexioTimerConfigStruct.timcmp = 8U * 2U - 1U;// change to 8 bit
    FLEXIO_HAL_ConfigureTimer(
            devPtr->flexioBase, devPtr->timerIdx[1], &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ConfigXferWordCountOnce
 * Description: Configure the count of words for each frame.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_I2C_HAL_ConfigXferWordCountOnce(flexio_i2c_dev_t *devPtr, uint32_t count)
{
    uint32_t timcmp;
    if ( (!devPtr) || (count > 14U) )
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    timcmp = FLEXIO_BRD_TIMCMP_CMP(devPtr->flexioBase, devPtr->timerIdx[0]);
    timcmp &= 0xFFU;
    timcmp |= (count * 18U + 1U) << 8U;
    FLEXIO_BWR_TIMCMP_CMP(devPtr->flexioBase, devPtr->timerIdx[0], timcmp);
    FLEXIO_WR_TIMCFG_TIMDIS(devPtr->flexioBase, devPtr->timerIdx[0],2);
    return kStatus_FLEXIO_Success;
}

/*------------------------------------------------------------------------
 * Tx.
 *----------------------------------------------------------------------*/
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetTxBufferEmptyFlag
 * Description: Get the flag if the rx buffer is empty.
 *
 *END*********************************************************************/
bool FLEXIO_I2C_HAL_GetTxBufferEmptyFlag(flexio_i2c_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[0])) 
            & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ClearTxBufferEmptyFlag
 * Description: Clear the flag of tx buffer empty manually.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_ClearTxBufferEmptyFlag(flexio_i2c_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_SetTxBufferEmptyIntCmd
 * Description: Switch on/off the interrupt for tx buffer is empty.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_SetTxBufferEmptyIntCmd(flexio_i2c_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetTxErrFlag
 * Description: Get the tx error flag.
 *
 *END*********************************************************************/
bool FLEXIO_I2C_HAL_GetTxErrFlag(flexio_i2c_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[0])) 
            & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ClearTxErrFlag
 * Description: Clear the tx error flag manually.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_ClearTxErrFlag(flexio_i2c_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_SetTxErrIntCmd
 * Description: Switch on/off the interrupt for tx error.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_SetTxErrIntCmd(flexio_i2c_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
            devPtr->flexioBase, (1U << devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_PutData
 * Description: Put data into tx buffer.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_PutData(flexio_i2c_dev_t *devPtr, uint32_t dat)
{
    FLEXIO_HAL_SetShifterBufferBitByteSwapped(
            devPtr->flexioBase, devPtr->shifterIdx[0], dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_PutDataPolling
 * Description: Put data into tx buffer when empty.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_PutDataPolling(flexio_i2c_dev_t *devPtr, uint32_t dat)
{
    while ( !FLEXIO_I2C_HAL_GetTxBufferEmptyFlag(devPtr) ) {}
    FLEXIO_I2C_HAL_PutData(devPtr, dat);
}

/* DMA. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_SetTxDmaCmd
 * Description: Switch on/off the tx DMA support.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_SetTxDmaCmd(flexio_i2c_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
            devPtr->flexioBase, 1U <<(devPtr->shifterIdx[0]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetTxBufferAddr
 * Description: Get address of tx buffer when using DMA.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2C_HAL_GetTxBufferAddr(flexio_i2c_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBBS_REG(devPtr->flexioBase, devPtr->shifterIdx[0])));
}

/*---------------------------------------------------------------------------
 * Rx.
 *-------------------------------------------------------------------------*/
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetRxBufferFullFlag
 * Description: Get the flag that rx buffer is full.
 *
 *END*********************************************************************/
bool FLEXIO_I2C_HAL_GetRxBufferFullFlag(flexio_i2c_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx[1])) 
            & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ClearRxBufferFullFlag
 * Description: Clear the rx buffer empty flag manually.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_ClearRxBufferFullFlag(flexio_i2c_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_SetRxBufferFullIntCmd
 * Description: Switch on/off the interrupt for rx buffer is full.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(flexio_i2c_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]), enable );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetRxErrFlag
 * Description: Get the rx error flag.
 *
 *END*********************************************************************/
bool FLEXIO_I2C_HAL_GetRxErrFlag(flexio_i2c_dev_t *devPtr)
{
    return ( 0U != ( (1U << devPtr->shifterIdx[1]) 
            & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ClearRxErrFlag
 * Description: Clear the rx error flag manually.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_ClearRxErrFlag(flexio_i2c_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_SetRxErrIntCmd
 * Description: Switch on/off the interrupt for rx error.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_SetRxErrIntCmd(flexio_i2c_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
            devPtr->flexioBase, 1U << (devPtr->shifterIdx[1]), enable);
}

/* Data. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetData
 * Description: Get the data from tx buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2C_HAL_GetData(flexio_i2c_dev_t *devPtr)
{
    return FLEXIO_HAL_GetShifterBufferBitByteSwapped(
            devPtr->flexioBase, devPtr->shifterIdx[1]);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetDataPolling
 * Description: Get the data from tx buffer when full.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2C_HAL_GetDataPolling(flexio_i2c_dev_t *devPtr)
{
    while ( !FLEXIO_I2C_HAL_GetRxBufferFullFlag(devPtr) ) {}
    return FLEXIO_I2C_HAL_GetData(devPtr);
}

/* DMA. */
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_SetRxDmaCmd
 * Description: Switch on/off the rx DMA support.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_SetRxDmaCmd(flexio_i2c_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
        devPtr->flexioBase, 1U <<(devPtr->shifterIdx[1]), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_GetRxBufferAddr
 * Description: Get the address the of rx buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_I2C_HAL_GetRxBufferAddr(flexio_i2c_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBBS_REG(devPtr->flexioBase, devPtr->shifterIdx[1])));
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ConfigSendNAck
 * Description: Configure the next sending would generate NACK condition.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_ConfigSendNAck(flexio_i2c_dev_t *devPtr)
{
    FLEXIO_WR_SHIFTCFG_SSTOP(devPtr->flexioBase,
        devPtr->shifterIdx[0], kFlexioShifterStopBitHigh);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_I2C_HAL_ConfigSendAck
 * Description: Configure the next sending would generate ACK condition.
 *
 *END*********************************************************************/
void FLEXIO_I2C_HAL_ConfigSendAck(flexio_i2c_dev_t *devPtr)
{
    FLEXIO_WR_SHIFTCFG_SSTOP(devPtr->flexioBase,
        devPtr->shifterIdx[0], kFlexioShifterStopBitLow);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

