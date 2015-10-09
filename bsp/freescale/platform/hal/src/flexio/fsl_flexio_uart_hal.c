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

#include "fsl_flexio_uart_hal.h"
#include <string.h>
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/**************************************************************************
 * UART Tx
 *************************************************************************/
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_Configure
 * Description: Configure the flexio working as uart tx device.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_UART_Tx_HAL_Configure(
    flexio_uart_tx_dev_t *devPtr, const flexio_uart_config_t *configPtr)
{
    flexio_timer_config_t   mFlexioTimerConfigStruct;
    flexio_shifter_config_t mFlexioShifterConfigStruct;
    memset(&mFlexioShifterConfigStruct, 0, sizeof(mFlexioShifterConfigStruct));
    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));

    uint32_t divider, timCmp;
    
    if ( (!devPtr) || (!configPtr) )
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    /* 1. Configure the shifter 0 for tx buffer. */
    mFlexioShifterConfigStruct.timsel = devPtr->timerIdx;
    mFlexioShifterConfigStruct.timpol = kFlexioShifterTimerPolarityOnPositive;
    mFlexioShifterConfigStruct.pincfg = kFlexioPinConfigOutput;
    mFlexioShifterConfigStruct.pinsel = devPtr->txPinIdx;
    mFlexioShifterConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioShifterConfigStruct.smode  = kFlexioShifterModeTransmit;
    mFlexioShifterConfigStruct.insrc  = kFlexioShifterInputFromPin;
    mFlexioShifterConfigStruct.sstop  = kFlexioShifterStopBitHigh;
    mFlexioShifterConfigStruct.sstart = kFlexioShifterStartBitLow;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx, &mFlexioShifterConfigStruct);

    /* 2. Configure the timer 0 for bandrate. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_SHIFTnSTAT(devPtr->shifterIdx);
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveLow;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceInternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioTimerConfigStruct.pinsel = devPtr->txPinIdx;
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeDual8BitBaudBit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneNotAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetNever;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTimerCompare;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnTriggerHigh;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitEnableOnTimerCompareDisable;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;
    divider = configPtr->flexioBusClk / configPtr->baudrate;
    timCmp = ( ((configPtr->bitCount) << 1U) - 1U )  << 8U;
    timCmp |= ( (divider >> 1U) - 1U );
    mFlexioTimerConfigStruct.timcmp = timCmp;
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx, &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_GetTxBufferEmptyFlag
 * Description: Get the flag if the tx buffer is empty.
 *
 *END*********************************************************************/
bool FLEXIO_UART_Tx_HAL_GetTxBufferEmptyFlag(flexio_uart_tx_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx)) 
                & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_ClearTxBufferEmptyFlag
 * Description: Clear the tx buffer empty flag manually.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_ClearTxBufferEmptyFlag(flexio_uart_tx_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, (1U << devPtr->shifterIdx) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_SetTxBufferEmptyIntCmd
 * Description: Switch on/off the interrupt for buffer empty event.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_SetTxBufferEmptyIntCmd(flexio_uart_tx_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
        devPtr->flexioBase, (1U << devPtr->shifterIdx), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_GetTxBufferEmptyIntCmd
 * Description: Get the current setting for tx buffer empty event.
 *
 *END*********************************************************************/
bool FLEXIO_UART_Tx_HAL_GetTxBufferEmptyIntCmd(flexio_uart_tx_dev_t *devPtr)
{
    return ( 0U != ((1U << (devPtr->shifterIdx))
        & FLEXIO_HAL_GetShifterStatusIntCmd(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_GetTxErrFlag
 * Description: Get the tx error flag.
 *
 *END*********************************************************************/
bool FLEXIO_UART_Tx_HAL_GetTxErrFlag(flexio_uart_tx_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx)) 
                & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_ClearTxErrFlag
 * Description: Clear the tx error flag manually.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_ClearTxErrFlag(flexio_uart_tx_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
        devPtr->flexioBase, (1U << devPtr->shifterIdx) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_SetTxErrIntCmd
 * Description: Switch on/off the interrupt for tx error event.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_SetTxErrIntCmd(flexio_uart_tx_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
        devPtr->flexioBase, (1U << devPtr->shifterIdx), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_PutData
 * Description: Put the data into the tx buffer.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_PutData(flexio_uart_tx_dev_t *devPtr, uint32_t dat)
{
    FLEXIO_HAL_SetShifterBuffer(
        devPtr->flexioBase, devPtr->shifterIdx, dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_PutDataPolling
 * Description: Put the data into the tx buffer when empty.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_PutDataPolling(flexio_uart_tx_dev_t *devPtr, uint32_t dat)
{
    /* Wait for tx buffer to be empty. */
    while ( !FLEXIO_UART_Tx_HAL_GetTxBufferEmptyFlag(devPtr) ) {}
    FLEXIO_UART_Tx_HAL_PutData(devPtr, dat);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_SendDataPolling
 * Description: Send an array of data by flexio uart tx device.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_SendDataPolling(flexio_uart_tx_dev_t *devPtr, uint32_t *txBufPtr, uint32_t txLen)
{
    uint32_t i;
    for (i = 0U; i < txLen; i++)
    {
        FLEXIO_UART_Tx_HAL_PutDataPolling(devPtr, txBufPtr[i]);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_SetTxDmaCmd
 * Description: Switch on/off the DMA on flexio uart tx device.
 *
 *END*********************************************************************/
void FLEXIO_UART_Tx_HAL_SetTxDmaCmd(flexio_uart_tx_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
        devPtr->flexioBase, 1U <<(devPtr->shifterIdx), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Tx_HAL_GetTxBufferAddr
 * Description: Get the tx buffer's address for DMA use.
 *
 *END*********************************************************************/
uint32_t FLEXIO_UART_Tx_HAL_GetTxBufferAddr(flexio_uart_tx_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUF_REG(devPtr->flexioBase, devPtr->shifterIdx)));
}

/************************************************************************
 * UART Rx
 ************************************************************************/
/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_Configure
 * Description: Configure the flexio working as uart rx device.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_UART_Rx_HAL_Configure(
    flexio_uart_rx_dev_t *devPtr, const flexio_uart_config_t *configPtr)
{
    flexio_timer_config_t   mFlexioTimerConfigStruct;
    flexio_shifter_config_t mFlexioShifterConfigStruct;
    memset(&mFlexioShifterConfigStruct, 0, sizeof(mFlexioShifterConfigStruct));
    memset(&mFlexioTimerConfigStruct, 0, sizeof(mFlexioTimerConfigStruct));

    uint32_t divider, timCmp;

    if  ( (!devPtr) || (!configPtr) )
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    /* 1. Configure the shifter 0 for rx buffer. */
    mFlexioShifterConfigStruct.timsel = devPtr->timerIdx;
    mFlexioShifterConfigStruct.timpol = kFlexioShifterTimerPolarityOnNegitive;
    mFlexioShifterConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioShifterConfigStruct.pinsel = devPtr->rxPinIdx;
    mFlexioShifterConfigStruct.pinpol = kFlexioPinActiveHigh;
    mFlexioShifterConfigStruct.smode = kFlexioShifterModeReceive;
    mFlexioShifterConfigStruct.insrc = kFlexioShifterInputFromPin;
    mFlexioShifterConfigStruct.sstop = kFlexioShifterStopBitHigh;
    mFlexioShifterConfigStruct.sstart = kFlexioShifterStartBitLow;
    FLEXIO_HAL_ConfigureShifter(
        devPtr->flexioBase, devPtr->shifterIdx, &mFlexioShifterConfigStruct);

    /* 2. Configure the timer 0 for bandrate. */
    mFlexioTimerConfigStruct.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(devPtr->rxPinIdx);
    mFlexioTimerConfigStruct.trgpol = kFlexioTimerTriggerPolarityActiveHigh;
    mFlexioTimerConfigStruct.trgsrc = kFlexioTimerTriggerSourceExternal;
    mFlexioTimerConfigStruct.pincfg = kFlexioPinConfigOutputDisabled;
    mFlexioTimerConfigStruct.pinsel = devPtr->rxPinIdx;
    mFlexioTimerConfigStruct.pinpol = kFlexioPinActiveLow;
    mFlexioTimerConfigStruct.timod  = kFlexioTimerModeDual8BitBaudBit; 
    mFlexioTimerConfigStruct.timout = kFlexioTimerOutputOneAffectedByReset;
    mFlexioTimerConfigStruct.timdec = kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput;
    mFlexioTimerConfigStruct.timrst = kFlexioTimerResetOnTimerPinRisingEdge;
    mFlexioTimerConfigStruct.timdis = kFlexioTimerDisableOnTimerCompare;
    mFlexioTimerConfigStruct.timena = kFlexioTimerEnableOnPinRisingEdge;
    mFlexioTimerConfigStruct.tstop  = kFlexioTimerStopBitEnableOnTimerDisable;
    mFlexioTimerConfigStruct.tstart = kFlexioTimerStartBitEnabled;
    divider = configPtr->flexioBusClk / configPtr->baudrate;
    timCmp = ( (configPtr->bitCount << 1U) - 1U )  << 8U;
    timCmp |= ( (divider >> 1U) - 1U );
    mFlexioTimerConfigStruct.timcmp = timCmp;
    FLEXIO_HAL_ConfigureTimer(
        devPtr->flexioBase, devPtr->timerIdx, &mFlexioTimerConfigStruct);

    return kStatus_FLEXIO_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_GetRxBufferFullFlag
 * Description: Get the flag if the rx buffer is full.
 *
 *END*********************************************************************/
bool FLEXIO_UART_Rx_HAL_GetRxBufferFullFlag(flexio_uart_rx_dev_t *devPtr)
{
    return (0U != ((1U << (devPtr->shifterIdx)) 
        & FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_ClearRxBufferFullFlag
 * Description: Clear the flag that rx buffer is full manually.
 *
 *END*********************************************************************/
void FLEXIO_UART_Rx_HAL_ClearRxBufferFullFlag(flexio_uart_rx_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_SetRxBufferFullIntCmd
 * Description: Switcher on/off the interrupt for rx buffer full event.
 *
 *END*********************************************************************/
void FLEXIO_UART_Rx_HAL_SetRxBufferFullIntCmd(flexio_uart_rx_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx), enable );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_GetRxBufferFullIntCmd
 * Description: Get the current setting if interrupt is enabled.
 *
 *END*********************************************************************/
bool FLEXIO_UART_Rx_HAL_GetRxBufferFullIntCmd(flexio_uart_rx_dev_t *devPtr)
{
    return ( 0U != ((1U << (devPtr->shifterIdx))
        & FLEXIO_HAL_GetShifterStatusIntCmd(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_GetRxErrFlag
 * Description: Get the flag of rx error event.
 *
 *END*********************************************************************/
bool FLEXIO_UART_Rx_HAL_GetRxErrFlag(flexio_uart_rx_dev_t *devPtr)
{
    return ( 0U != ((1U << (devPtr->shifterIdx))
        & FLEXIO_HAL_GetShifterErrorFlags(devPtr->flexioBase)) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_ClearRxErrFlag
 * Description: Clear the flag of rx error event manually.
 *
 *END*********************************************************************/
void FLEXIO_UART_Rx_HAL_ClearRxErrFlag(flexio_uart_rx_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterErrorFlags(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_SetRxErrIntCmd
 * Description: Switch on/off the interrupt for rx error event.
 *
 *END*********************************************************************/
void FLEXIO_UART_Rx_HAL_SetRxErrIntCmd(flexio_uart_rx_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterErrorIntCmd(
        devPtr->flexioBase, 1U << (devPtr->shifterIdx), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_GetData
 * Description: Get the data from rx buffer.
 *
 *END*********************************************************************/
uint32_t FLEXIO_UART_Rx_HAL_GetData(flexio_uart_rx_dev_t *devPtr)
{
    return FLEXIO_HAL_GetShifterBufferByteSwapped(
        devPtr->flexioBase, devPtr->shifterIdx);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_GetDataPolling
 * Description: Get the data from rx buffer when full.
 *
 *END*********************************************************************/
uint32_t FLEXIO_UART_Rx_HAL_GetDataPolling(flexio_uart_rx_dev_t *devPtr)
{
    while ( !FLEXIO_UART_Rx_HAL_GetRxBufferFullFlag(devPtr) ) {}
    return FLEXIO_UART_Rx_HAL_GetData(devPtr);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_ReceiveDataPolling
 * Description: Receive an array of data through the rx buffer.
 *
 *END*********************************************************************/
void FLEXIO_UART_Rx_HAL_ReceiveDataPolling(flexio_uart_rx_dev_t *devPtr, uint32_t *rxBufPtr, uint32_t rxLen)
{
    uint32_t i;
    
    for (i = 0U; i < rxLen; i++)
    {
        rxBufPtr[i] = FLEXIO_UART_Rx_HAL_GetDataPolling(devPtr);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_SetRxDmaCmd
 * Description: Switch on/off the rx DMA support.
 *
 *END*********************************************************************/
void FLEXIO_UART_Rx_HAL_SetRxDmaCmd(flexio_uart_rx_dev_t *devPtr, bool enable)
{
    FLEXIO_HAL_SetShifterStatusDmaCmd(
        devPtr->flexioBase, 1U <<(devPtr->shifterIdx), enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_UART_Rx_HAL_GetRxBufferAddr
 * Description: Get the rx buffer's address for DMA use.
 *
 *END*********************************************************************/
uint32_t FLEXIO_UART_Rx_HAL_GetRxBufferAddr(flexio_uart_rx_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUFBYS_REG(devPtr->flexioBase, devPtr->shifterIdx)));
}
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

