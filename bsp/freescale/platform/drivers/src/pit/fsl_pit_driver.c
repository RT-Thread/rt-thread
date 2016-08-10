/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "fsl_pit_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_PIT_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* pit source clock variable which will be updated in PIT_DRV_Init */
uint64_t g_pitSourceClock;

/* pit instance and channel number used by microseconds functions */
uint8_t g_pitUsInstance;
uint8_t g_pitUsChannel;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_Init
 * Description   : Initialize PIT module.
 * This function must be called before calling all the other PIT driver functions.
 * This function un-gates the PIT clock and enables the PIT module. The
 * isRunInDebug passed into function will affect all timer channels.
 *
 *END**************************************************************************/
pit_status_t PIT_DRV_Init(uint32_t instance, bool isRunInDebug)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    /* Un-gate pit clock*/
    CLOCK_SYS_EnablePitClock(instance);

    /* Enable PIT module clock*/
    PIT_HAL_Enable(base);

    /* Set timer run or stop in debug mode*/
    PIT_HAL_SetTimerRunInDebugCmd(base, isRunInDebug);

    /* Finally, update pit source clock frequency.*/
    g_pitSourceClock = CLOCK_SYS_GetPitFreq(instance);

    return kStatus_PIT_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_InitChannel
 * Description   : Initialize PIT channel.
 * This function initialize PIT timers by channel. Pass in timer number and its
 * config structure. Timers do not start counting by default after calling this
 * function. Function PIT_DRV_StartTimer must be called to start timer counting.
 * Call PIT_DRV_SetTimerPeriodByUs to re-set the period.
 *
 *END**************************************************************************/
void PIT_DRV_InitChannel(uint32_t instance,
                         uint32_t channel,
                         const pit_user_config_t * config)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    /* Set timer period.*/
    PIT_DRV_SetTimerPeriodByUs(instance, channel, config->periodUs);

    /* Enable or disable interrupt.*/
    PIT_HAL_SetIntCmd(base, channel, config->isInterruptEnabled);

    /* Configure NVIC*/
    if (config->isInterruptEnabled)
    {
        /* Enable PIT interrupt.*/
        INT_SYS_EnableIRQ(g_pitIrqId[channel]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_Deinit
 * Description   : Disable PIT module and gate control
 * This function will disable all PIT interrupts and PIT clock. Then gate the
 * PIT clock control. pit_init must be called in order to use PIT again.
 *
 *END**************************************************************************/
pit_status_t PIT_DRV_Deinit(uint32_t instance)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    uint32_t i;

    /* Exit if current instance is gated.*/
    if (!CLOCK_SYS_GetPitGateCmd(instance))
    {
        return kStatus_PIT_Fail;
    }

    /* Disable all PIT interrupts. Clear the chain bit if available */
    for (i=0; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        PIT_HAL_SetIntCmd(base, i, false);
        INT_SYS_DisableIRQ(g_pitIrqId[i]);
#if FSL_FEATURE_PIT_HAS_CHAIN_MODE
        PIT_HAL_SetTimerChainCmd(base, i, false);
#endif
    }

    /* Disable PIT module clock*/
    PIT_HAL_Disable(base);

    /* Gate PIT clock control*/
    CLOCK_SYS_DisablePitClock(instance);

    return kStatus_PIT_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_StartTimer
 * Description   : Start timer counting.
 * After calling this function, timers load period value, count down to 0 and
 * then load the respective start value again. Each time a timer reaches 0,
 * it will generate a trigger pulse and set the timeout interrupt flag.
 *
 *END**************************************************************************/
void PIT_DRV_StartTimer(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    PIT_HAL_StartTimer(base, channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_StopTimer
 * Description   : Stop timer counting.
 * This function will stop every timer counting. Timers will reload their periods
 * respectively after calling PIT_DRV_StartTimer next time.
 *
 *END**************************************************************************/
void PIT_DRV_StopTimer(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    PIT_HAL_StopTimer(base, channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_SetTimerPeriodByUs
 * Description   : Set timer period in microseconds unit.
 * The period range depends on the frequency of PIT source clock. If required
 * period is out the range, try to use lifetime timer if applicable.
 * This function is only valid for one single channel. If channels are chained together,
 * the period here will make no sense.
 *
 *END**************************************************************************/
void PIT_DRV_SetTimerPeriodByUs(uint32_t instance, uint32_t channel, uint32_t us)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    /* Calculate the count value, assign it to timer counter register.*/
    uint32_t count = (uint32_t)(us * g_pitSourceClock / 1000000U - 1U);
    PIT_HAL_SetTimerPeriodByCount(base, channel, count);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_GetTimerPeriodByUs
 * Description   : Gets the timer period in microseconds for one single channel.
 *
 *END**************************************************************************/
uint32_t PIT_DRV_GetTimerPeriodByUs(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    /* Get current timer period by count.*/
    uint64_t currentPeriod = PIT_HAL_GetTimerPeriodByCount(base, channel);

    /* Convert count numbers to microseconds unit.*/
    currentPeriod = (currentPeriod + 1U) * 1000000U / g_pitSourceClock;
    return (uint32_t)currentPeriod ;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_ReadTimerUs
 * Description   : Read current timer value in microseconds unit.
 * This function will return an absolute time stamp in the unit of microseconds.
 * One common use of this function is to measure the running time of part of
 * code. Just call this function at both the beginning and end of code, the time
 * difference between these two time stamp will be the running time (Need to
 * make sure the running time will not exceed the timer period). Also, the time
 * stamp returned is up-counting.
 *
 *END**************************************************************************/
uint32_t PIT_DRV_ReadTimerUs(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    /* Get current timer count, and reverse it to up-counting.*/
    uint64_t currentTime = (~PIT_HAL_ReadTimerCount(base, channel));

    /* Convert count numbers to microseconds unit.*/
    currentTime = (currentTime * 1000000U) / g_pitSourceClock;
    return (uint32_t)currentTime;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_SetTimerPeriodByCount
 * Description   : Sets the timer period in units of count.
 * Timers begin counting from the value set by this function.
 * The counter period of a running timer can be modified by first stopping
 * the timer, setting a new load value, and  starting the timer again. If
 * timers are not restarted, the new value is loaded after the next trigger
 * event.
 *
 *END**************************************************************************/
void PIT_DRV_SetTimerPeriodByCount(uint32_t instance, uint32_t channel, uint32_t count)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    PIT_HAL_SetTimerPeriodByCount(base, channel, count);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_GetTimerPeriodByCount
 * Description   : Returns the current timer period in units of count.
 *
 *END**************************************************************************/
uint32_t PIT_DRV_GetTimerPeriodByCount(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    return PIT_HAL_GetTimerPeriodByCount(base, channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_ReadTimerCount
 * Description   : Reads the current timer counting value.
 * This function returns the real-time timer counting value, in a range from 0
 * to a timer period.
 *
 *END**************************************************************************/
uint32_t PIT_DRV_ReadTimerCount(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    return PIT_HAL_ReadTimerCount(base, channel);
}

#if FSL_FEATURE_PIT_HAS_LIFETIME_TIMER
/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_SetLifetimeTimerPeriodByUs
 * Description   : Set lifetime timer period (Timers must be chained).
 * Timer 1 must be chained with timer 0 before using lifetime timer. The period
 * range is restricted by "period * g_pitSourceClock < max of an uint64_t integer",
 * or it may cause a overflow and is not able to set correct period.
 *
 *END**************************************************************************/
void PIT_DRV_SetLifetimeTimerPeriodByUs(uint32_t instance, uint64_t us)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    uint64_t lifeTimeCount;

    /* Calculate the counter value.*/
    lifeTimeCount = us * g_pitSourceClock / 1000000U - 1U;

    /* Assign to timers.*/
    PIT_HAL_SetTimerPeriodByCount(base, 0U, (uint32_t)lifeTimeCount);
    PIT_HAL_SetTimerPeriodByCount(base, 1U, (uint32_t)(lifeTimeCount >> 32U));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_ReadLifetimeTimerUs
 * Description   : Read current lifetime value in microseconds unit.
 * Return an absolute time stamp in the unit of microseconds. The time stamp
 * value will not exceed the timer period. Also, the timer is up-counting.
 *
 *END**************************************************************************/
uint64_t PIT_DRV_ReadLifetimeTimerUs(uint32_t instance)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];
    /* Get current lifetime timer count, and reverse it to up-counting.*/
    uint64_t currentTime = (~PIT_HAL_ReadLifetimeTimerCount(base));

    /* Convert count numbers to microseconds unit.*/
    /* Note: using currentTime * 1000 rather than 1000000 to avoid short time overflow. */
    return currentTime = (currentTime * 1000U) / (g_pitSourceClock / 1000U);
}
#endif /* FSL_FEATURE_PIT_HAS_LIFETIME_TIMER*/

#if FSL_FEATURE_PIT_HAS_CHAIN_MODE
/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_InitUs
 * Description   : Initializes two PIT channels to serve as a microseconds unit.
 * This function is in parallel with PIT_DRV_InitChannel, they will overwrite
 * each other. PIT_DRV_Init must be called before calling this function.
 * The microseconds unit will use two chained channels to simulate a lifetime
 * timer, the channel number passed in and the "channel -1" channel will be used.
 * Note:
 * 1. These two channels will be occupied and could not be used with other purposes.
 * 2. The channel number passed in must be greater than 0.

 *END**************************************************************************/
void PIT_DRV_InitUs(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);
    assert(channel > 0U);

    PIT_Type * base = g_pitBase[instance];
    g_pitUsInstance = instance;
    g_pitUsChannel = channel;

    PIT_HAL_SetTimerChainCmd(base, channel, true);
    PIT_HAL_SetTimerPeriodByCount(base, channel, 0xFFFFFFFFU);
    PIT_HAL_SetTimerPeriodByCount(base, channel - 1U, 0xFFFFFFFFU);

    PIT_HAL_StartTimer(base, channel);
    PIT_HAL_StartTimer(base, channel - 1U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_GetUs
 * Description   : Get an absolute time stamp.
 * This function is useful to get elapsed time through calling this function in
 * time A, and then call it in time B. The elapsed time could be get by B-A, the
 * result may have 3-5 microseconds error depends on system clock frequency.
 *
 *END**************************************************************************/
uint32_t PIT_DRV_GetUs(void)
{
    PIT_Type * base = g_pitBase[g_pitUsInstance];
    /* Get current timer count, and reverse it to up-counting.*/
    uint64_t currentTime = ~(((uint64_t)PIT_HAL_ReadTimerCount(base, g_pitUsChannel) << 32U) +
                           PIT_HAL_ReadTimerCount(base, g_pitUsChannel - 1U));

    /* Convert count numbers to microseconds unit.*/
    return currentTime = (currentTime * 1000U) / (g_pitSourceClock / 1000U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_DelayUs
 * Description   : Delay specific microseconds.
 * The delay will have a 3-5 microseconds error depends on system clock frequency.
 *
 *END**************************************************************************/
void PIT_DRV_DelayUs(uint32_t us)
{
    PIT_Type * base = g_pitBase[g_pitUsInstance];

    uint64_t x = us * g_pitSourceClock / 1000000;
    uint64_t timeToBe = ((uint64_t)PIT_HAL_ReadTimerCount(base, g_pitUsChannel) << 32U) +
                           PIT_HAL_ReadTimerCount(base, g_pitUsChannel - 1U) - x;

    while (((uint64_t)PIT_HAL_ReadTimerCount(base, g_pitUsChannel) << 32U) +
                      PIT_HAL_ReadTimerCount(base, g_pitUsChannel - 1U)
                      >= timeToBe)
    {}
}

#endif /* FSL_FEATURE_PIT_HAS_CHAIN_MODE */

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_ClearIntFlag
 * Description   : Clears the timer interrupt flag.
 *
 *END**************************************************************************/
void PIT_DRV_ClearIntFlag(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    PIT_HAL_ClearIntFlag(base, channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_IsIntPending
 * Description   : Reads the current timer timeout flag.
 *
 *END**************************************************************************/
bool PIT_DRV_IsIntPending(uint32_t instance, uint32_t channel)
{
    assert(instance < PIT_INSTANCE_COUNT);

    PIT_Type * base = g_pitBase[instance];

    return PIT_HAL_IsIntPending(base, channel);
}

#endif /* FSL_FEATURE_SOC_PIT_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

