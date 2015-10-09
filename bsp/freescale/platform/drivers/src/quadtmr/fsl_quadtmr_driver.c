/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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

#include "fsl_quadtmr_driver.h"
#include "fsl_clock_manager.h"

#if FSL_FEATURE_SOC_TMR_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* IP source clock variable which will be updated in QUADTMR_DRV_SetupFlexPwm */
uint32_t g_quadtmrIpSourceClock;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_Init
 * Description   : Initializes the Quad Timer driver.
 * Initialize the Quad Timer registers, ungates the module clock and enables Quad Timer
 * interrupt in the system interrupt controller.
 *
 *END**************************************************************************/
quadtmr_status_t QUADTMR_DRV_Init(uint32_t instance)
{
    assert(instance < TMR_INSTANCE_COUNT);

    TMR_Type *tmrBase = g_quadtmrBase[instance];

    /* clock setting initialization*/
    CLOCK_SYS_EnableQuadTmrClock(instance);

    QUADTMR_HAL_Init(tmrBase);

    NVIC_ClearPendingIRQ(g_quadtmrIrqId[instance]);
    INT_SYS_EnableIRQ(g_quadtmrIrqId[instance]);

    return kStatusQuadTmrSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_Deinit
 * Description   : Shuts down the Quad Timer driver.
 * Gates the module clock and disables the interrupt in the system interrupt controller.
 *
 *END**************************************************************************/
void QUADTMR_DRV_Deinit(uint32_t instance)
{
    assert(instance < TMR_INSTANCE_COUNT);

    /* disable clock for Quad timer.*/
    CLOCK_SYS_DisableQuadTmrClock(instance);

    INT_SYS_DisableIRQ(g_quadtmrIrqId[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_Start64BitCounter
 * Description   : Provides a 64-bit counter.
 * The user gets to choose which source clock will be used by the counter.
 * User must ensure that QUADTMR_DRV_Init() is called on all timer instances as all
 * will be used in this mode. Timer 0 is clocked via the source clock and Timers 1, 2 and 3
 * are setup in cascade mode. All 4 counters will count up to 0xFFFF, then roll-over and continue
 * counting.
 *
 *END**************************************************************************/
void QUADTMR_DRV_Start64BitCounter(quadtmr_pri_count_source_t clk)
{
    quadtmr_counter_params_t params;

    /* Setup to count upto the max value */
    params.countUpCompareVal = 0xFFFF;

    params.countDir = 0;
    params.countLength = 0;
    params.countOnce = 0;
    params.counterVal = 0;
    params.counterLoadVal = 0;

    /* Provide the clock as the input source for counter of timer 0 */
    params.primarySrc = clk;
    QUADTMR_HAL_SetupCounter(g_quadtmrBase[0], &params, false);
    /* Setup timers 1,2,3 to receive clock from the prior timer's output */
    params.primarySrc = kQuadTmrCntr0Out;
    QUADTMR_HAL_SetupCounter(g_quadtmrBase[1], &params, false);
    params.primarySrc = kQuadTmrCntr1Out;
    QUADTMR_HAL_SetupCounter(g_quadtmrBase[2], &params, false);
    params.primarySrc = kQuadTmrCntr2Out;
    QUADTMR_HAL_SetupCounter(g_quadtmrBase[3], &params, false);

    /* Set timers 1,2,3 to be in cascade mode */
    QUADTMR_HAL_SetCountMode(g_quadtmrBase[1], kQuadTmrCascadeCnt);
    QUADTMR_HAL_SetCountMode(g_quadtmrBase[2], kQuadTmrCascadeCnt);
    QUADTMR_HAL_SetCountMode(g_quadtmrBase[3], kQuadTmrCascadeCnt);

    /* Start the counter */
    QUADTMR_HAL_SetCountMode(g_quadtmrBase[0], kQuadTmrCntPriSrcRiseEdge);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_Get64BitCountVal
 * Description   : Get the current count value when running in 64-bit mode.
 * The function will read all 4 timer values and return the value.
 * The current value of all 4 counters will be concatenated to a 64-bit value.
 *
 *END**************************************************************************/
uint64_t QUADTMR_DRV_Get64BitCountVal(void)
{
    uint64_t countVal;

    QUADTMR_HAL_GetCounterVal(g_quadtmrBase[0]);

    countVal = ((uint64_t)QUADTMR_HAL_GetHoldVal(g_quadtmrBase[3]) << 48 |
                (uint64_t)QUADTMR_HAL_GetHoldVal(g_quadtmrBase[2]) << 32 |
                (uint64_t)QUADTMR_HAL_GetHoldVal(g_quadtmrBase[1]) << 16 |
                (uint64_t)QUADTMR_HAL_GetHoldVal(g_quadtmrBase[0]));

    return countVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_SetupFlexPwm
 * Description   : Provides a PWM signal
 * The user provides the input clock source which is derived from the IP Bus clock. The user also
 * provides the desired PWM signal's period in microseconds and the pulse width in microseconds.
 * This function enables the pre-load function for each comapare register to allow updating
 * the PWM signal characteristics at a later time.
 *
 *END**************************************************************************/
void QUADTMR_DRV_SetupFlexPwm(uint32_t instance, quadtmr_ip_bus_clock_source_t clockSrc,
                                          uint32_t pwmPulsePeriod, uint32_t pulseWidthPeriod)
{
    TMR_Type *tmrBase = g_quadtmrBase[instance];
    uint16_t pulseCnt, highPulse, lowPulse;

    /* Update source clock frequency.*/
    g_quadtmrIpSourceClock = CLOCK_SYS_GetBusClockFreq() / (1 << clockSrc);

    pulseCnt = ((uint64_t)g_quadtmrIpSourceClock * pwmPulsePeriod) / 1000000;
    highPulse = ((uint64_t)g_quadtmrIpSourceClock * pulseWidthPeriod) / 1000000;
    lowPulse = pulseCnt - highPulse;

    QUADTMR_HAL_SetupComparePreload(tmrBase, 2, highPulse, kQuadTmrLoadOnComp2);
    QUADTMR_HAL_SetupComparePreload(tmrBase, 1, lowPulse, kQuadTmrLoadOnComp1);
    QUADTMR_HAL_OutPwmSignal(tmrBase, (quadtmr_pri_count_source_t)(clockSrc + 8), highPulse, lowPulse);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_UpdatePwm
 * Description   : Provides a way to update the current PWM signal.
 * Prior to calling this function user should call QUADTMR_DRV_SetupFlexPwm() to start outputting a
 * PWM signal. User can then call this function to update the PWM's period and/or pulse width.
 * The PWM will continue to be derived from the clock source provided during setup.
 *
 *END**************************************************************************/
void QUADTMR_DRV_UpdatePwm(uint32_t instance, uint32_t pwmPulsePeriod, uint32_t pulseWidthPeriod)
{
    TMR_Type *tmrBase = g_quadtmrBase[instance];
    uint16_t pulseCnt, highPulse, lowPulse;

    pulseCnt = (g_quadtmrIpSourceClock * pwmPulsePeriod) / 1000000;
    highPulse = (g_quadtmrIpSourceClock * pulseWidthPeriod) / 1000000;
    lowPulse = pulseCnt - highPulse;

    QUADTMR_HAL_SetComp1PreloadVal(tmrBase, lowPulse);
    QUADTMR_HAL_SetComp2PreloadVal(tmrBase, highPulse);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_DRV_IRQHandler
 * Description   : Action to take when a Quad Timer interrupt is triggered.
 * The timer compare flags are checked and cleared if set.
 *
 *END**************************************************************************/
void QUADTMR_DRV_IRQHandler(uint32_t instance)
{
    TMR_Type *tmrBase = g_quadtmrBase[instance];

    /* Clear the Compare 1 status flag if the interrupt is enabled */
    if (TMR_BRD_CSCTRL_TCF1EN(tmrBase) && TMR_BRD_CSCTRL_TCF1(tmrBase))
    {
        TMR_BWR_CSCTRL_TCF1(tmrBase, 0);
    }

    /* Clear the Compare 2 status flag if the interrupt is enabled */
    if (TMR_BRD_CSCTRL_TCF2EN(tmrBase) && TMR_BRD_CSCTRL_TCF2(tmrBase))
    {
        TMR_BWR_CSCTRL_TCF2(tmrBase, 0);
    }
}

#endif /* FSL_FEATURE_SOC_TMR_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

