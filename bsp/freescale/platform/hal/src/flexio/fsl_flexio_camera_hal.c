/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_flexio_camera_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

#if FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH

/* This XXX_TEMPLETE_CONFIG could help you clean the code.
 * However, for some C++ compiler, it would cause problem. So you could unlock
 * these code as your wish.
 */
#if 0
#define FLEXIO_CAMERA_SHIFTER_TEMPLETE_CONFIG                                   \
{                                                                               \
  .timsel = 0, /* control the available data, would be changed according to application. */ \
  .timpol = kFlexioShifterTimerPolarityOnPositive,                              \
  .pincfg = kFlexioPinConfigOutputDisabled,                                     \
  .pinsel = 0, /* data pin, would be changed according to application. */       \
  .pinpol = kFlexioPinActiveHigh,                                               \
  .smode  = kFlexioShifterModeReceive,                                          \
  .pwidth = FLEXIO_CAMERA_PARALLEL_DATA_WIDTH-1U,                               \
  .insrc  = kFlexioShifterInputFromNextShifterOutput,                           \
  .sstop  = kFlexioShifterStopBitDisable,                                       \
  .sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable                      \
}

#define FLEXIO_CAMERA_TIMER_TEMPLETE_CONFIG                                     \
{                                                                               \
  .trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(0), /* HREF pin, would be changed. */ \
  .trgpol = kFlexioTimerTriggerPolarityActiveHigh,                              \
  .trgsrc = kFlexioTimerTriggerSourceInternal,                                  \
  .pincfg = kFlexioPinConfigOutputDisabled,                                     \
  .pinsel = 0U, /* PCLK pin, would be changed. */                               \
  .pinpol = kFlexioPinActiveHigh,                                               \
  .timod  = kFlexioTimerModeSingle16Bit,                                        \
  .timout = kFlexioTimerOutputZeroNotAffectedByReset,                           \
  .timdec = kFlexioTimerDecSrcOnPinInputShiftPinInput,                          \
  .timrst = kFlexioTimerResetOnTimerTriggerRisingEdge,                          \
  .timdis = kFlexioTimerDisableOnTriggerFallingEdge,                            \
  .timena = kFlexioTimerEnableOnTriggerRisingEdge,                              \
  .tstop  = kFlexioTimerStopBitDisabled,                                        \
  .tstart = kFlexioTimerStartBitDisabled,                                       \
  .timcmp = 0  /* time of shift buffer, would be changed. */                    \
}
#endif

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_Configure
 * Description: Configure the flexio working as flexio_camera device.
 *
 * There are only data pin, pclk pin and href pin are simulated with flexio. 
 * So the camera interface can be considered as an advanced SPI interface with
 * 8-bit data parallel bus. the pclk and href signal are just working as SCLK 
 * and CS signal of SPI bus.
 *
 *END*********************************************************************/
flexio_status_t FLEXIO_Camera_HAL_Configure(flexio_camera_dev_t *devPtr)
{
    uint32_t i;

    
    flexio_shifter_config_t flexioShifterConfig;
    flexio_timer_config_t flexioTimerConfig;

    if (!devPtr)
    {
        return kStatus_FLEXIO_InvalidArgument;
    }
    
    /* FLEXIO_CAMERA_SHIFTER_TEMPLETE_CONFIG */
    flexioShifterConfig.timsel = 0; /* control the available data, would be changed according to application. */
    flexioShifterConfig.timpol = kFlexioShifterTimerPolarityOnPositive;
    flexioShifterConfig.pincfg = kFlexioPinConfigOutputDisabled;
    flexioShifterConfig.pinsel = 0; /* data pin, would be changed according to application. */
    flexioShifterConfig.pinpol = kFlexioPinActiveHigh;
    flexioShifterConfig.smode  = kFlexioShifterModeReceive;
    flexioShifterConfig.pwidth = FLEXIO_CAMERA_PARALLEL_DATA_WIDTH-1U;
    flexioShifterConfig.insrc  = kFlexioShifterInputFromNextShifterOutput;
    flexioShifterConfig.sstop  = kFlexioShifterStopBitDisable;
    flexioShifterConfig.sstart = kFlexioShifterStartBitDisabledLoadDataOnEnable;
    
    /* FLEXIO_CAMERA_TIMER_TEMPLETE_CONFIG */
    flexioTimerConfig.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(0); /* HREF pin, would be changed. */
    flexioTimerConfig.trgpol = kFlexioTimerTriggerPolarityActiveHigh;
    flexioTimerConfig.trgsrc = kFlexioTimerTriggerSourceInternal;
    flexioTimerConfig.pincfg = kFlexioPinConfigOutputDisabled;
    flexioTimerConfig.pinsel = 0U; /* PCLK pin, would be changed. */
    flexioTimerConfig.pinpol = kFlexioPinActiveHigh;
    flexioTimerConfig.timod  = kFlexioTimerModeSingle16Bit;
    flexioTimerConfig.timout = kFlexioTimerOutputZeroNotAffectedByReset;
    flexioTimerConfig.timdec = kFlexioTimerDecSrcOnPinInputShiftPinInput;
    flexioTimerConfig.timrst = kFlexioTimerResetOnTimerTriggerRisingEdge;
    flexioTimerConfig.timdis = kFlexioTimerDisableOnTriggerFallingEdge;
    flexioTimerConfig.timena = kFlexioTimerEnableOnTriggerRisingEdge;
    flexioTimerConfig.tstop  = kFlexioTimerStopBitDisabled;
    flexioTimerConfig.tstart = kFlexioTimerStartBitDisabled;
    flexioTimerConfig.timcmp = 0;  /* time of shift buffer, would be changed. */
    
    /* Configure the shifters as FIFO buffer. */
    flexioShifterConfig.timsel = devPtr->timerIdx; /* driven timer. */
    flexioShifterConfig.pinsel = devPtr->datPinStartIdx; /* data pin. */
    for ( i = devPtr->shifterStartIdx;
          i < (devPtr->shifterStartIdx + devPtr->shifterCount - 1U);
          i++)
    {
        FLEXIO_HAL_ConfigureShifter(devPtr->flexioBase, i, &flexioShifterConfig);
    }
    flexioShifterConfig.insrc = kFlexioShifterInputFromPin;
    FLEXIO_HAL_ConfigureShifter(devPtr->flexioBase, i, &flexioShifterConfig);

    /* Configure the timer to select the available data. 
    * The PCLK's clk is source of timer to drive the shifter.
    * The HREF is the selecting signal for available data.
    */
    flexioTimerConfig.trgsel = FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(devPtr->hrefPinIdx); /* HREF pin. */
    flexioTimerConfig.pinsel = devPtr->pclkPinIdx; /* PCLK pin. */
    flexioTimerConfig.timcmp = 8U * devPtr->shifterCount - 1U;
    FLEXIO_HAL_ConfigureTimer(devPtr->flexioBase, devPtr->timerIdx, &flexioTimerConfig);

    /* Clear flags. */
    FLEXIO_HAL_ClearShifterErrorFlags(devPtr->flexioBase, ((1U<<(devPtr->shifterCount))-1U)<<(devPtr->shifterStartIdx) );
    FLEXIO_HAL_ClearTimerStatusFlags(devPtr->flexioBase, 1U<<(devPtr->timerIdx) );
    
    return kStatus_FLEXIO_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_GetRxBufferFullFlag
 * Description: Get the flag mask if the Rx buffer is full.
 *
 *END*********************************************************************/
uint32_t FLEXIO_Camera_HAL_GetRxBufferFullFlag(flexio_camera_dev_t *devPtr)
{
    return (    (FLEXIO_HAL_GetShifterStatusFlags(devPtr->flexioBase)>>(devPtr->shifterStartIdx)) 
             &  ((1U<<(devPtr->shifterCount))-1U) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_ClearRxBufferFullFlag
 * Description: Clear the flag that Rx buffer is full manually.
 *
 * Usually, this API is not necessary, since the flag would be cleared
 * automatically once the buffer is read. However, if the application
 * would reset the condition from some unexpected situation, to call this
 * API would make sure the flags are cleared.
 *
 * Once the buffer is cleared, that means all the shifters' flag should
 * be cleared, otherwise the error flag would be asserted.
 *
 *END*********************************************************************/
void FLEXIO_Camera_HAL_ClearRxBufferFullFlag(flexio_camera_dev_t *devPtr)
{
    FLEXIO_HAL_ClearShifterStatusFlags(
        devPtr->flexioBase, ((1U << (devPtr->shifterCount))-1U) << (devPtr->shifterStartIdx) );
    /* Clear error flags if they are asserted to make sure the buffer would be available. */
    FLEXIO_HAL_ClearShifterErrorFlags(
        devPtr->flexioBase, ((1U << (devPtr->shifterCount))-1U) << (devPtr->shifterStartIdx) );
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_SetRxBufferFullIntCmd
 * Description: Switcher on/off the interrupt for Rx buffer full event.
 *
 *END*********************************************************************/
void FLEXIO_Camera_HAL_SetRxBufferFullIntCmd(
    flexio_camera_dev_t *devPtr, uint32_t syncMsk, bool enable)
{
    FLEXIO_HAL_SetShifterStatusIntCmd( devPtr->flexioBase, 
                                       syncMsk<<(devPtr->shifterStartIdx),
                                       enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_GetRxBufferData
 * Description: Get the data from hardware Rx FIFO which is build by
 * shifters.
 *
 *END*********************************************************************/
void FLEXIO_Camera_HAL_GetRxBufferData(flexio_camera_dev_t *devPtr, uint32_t *datPtr)
{
    uint32_t i;
    for (i = 0U; i < devPtr->shifterCount; i++)
    {
        *(datPtr+i) = FLEXIO_HAL_GetShifterBuffer(devPtr->flexioBase,
                                                  (devPtr->shifterStartIdx) + i);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_SetRxBufferFullDmaCmd
 * Description: Switch on/off the Rx DMA support.
 *
 *END*********************************************************************/
void FLEXIO_Camera_HAL_SetRxBufferDmaCmd(
    flexio_camera_dev_t *devPtr, uint32_t syncMsk, bool enable)

{
    FLEXIO_HAL_SetShifterStatusDmaCmd( devPtr->flexioBase, 
                                       syncMsk<<(devPtr->shifterStartIdx),
                                       enable);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_Camera_HAL_GetRxBufferAddr
 * Description: Get the Rx buffer's address for DMA use.
 *
 *END*********************************************************************/
uint32_t FLEXIO_Camera_HAL_GetRxBufferAddr(flexio_camera_dev_t *devPtr)
{
    return (uint32_t)(&(FLEXIO_SHIFTBUF_REG(devPtr->flexioBase, devPtr->shifterStartIdx)));
}

#endif /* FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH */

#endif /* FSL_FEATURE_SOC_FLEXIO_COUNT */

/******************************************************************************
 * EOF
 *****************************************************************************/

