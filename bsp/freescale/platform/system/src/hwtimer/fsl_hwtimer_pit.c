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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_hwtimer.h"
#include "fsl_hwtimer_pit.h"
#include "fsl_pit_hal.h"
#include "fsl_os_abstraction.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Internal type definition
 ******************************************************************************/
extern PIT_Type * const g_pitBase[];
extern const IRQn_Type g_pitIrqId[];
/*******************************************************************************
 * Internal Variables
 ******************************************************************************/
void HWTIMER_SYS_PitIsrAction(uint8_t pitChannel);
static _hwtimer_error_code_t HWTIMER_SYS_PitInit(hwtimer_t *hwtimer, uint32_t pitId, void *data);
static _hwtimer_error_code_t HWTIMER_SYS_PitDeinit(hwtimer_t *hwtimer);
static _hwtimer_error_code_t HWTIMER_SYS_PitSetDiv(hwtimer_t *hwtimer, uint32_t period);
static _hwtimer_error_code_t HWTIMER_SYS_PitStart(hwtimer_t *hwtimer);
static _hwtimer_error_code_t HWTIMER_SYS_PitStop(hwtimer_t *hwtimer);
static _hwtimer_error_code_t HWTIMER_SYS_PitGetTime(hwtimer_t *hwtimer, hwtimer_time_t *time);


const hwtimer_devif_t kPitDevif =
{
    HWTIMER_SYS_PitInit,
    HWTIMER_SYS_PitDeinit,
    HWTIMER_SYS_PitSetDiv,
    HWTIMER_SYS_PitStart,
    HWTIMER_SYS_PitStop,
    HWTIMER_SYS_PitGetTime,
};

static hwtimer_t *g_hwtimersPit[FSL_FEATURE_PIT_TIMER_COUNT] = {0U};


 /*******************************************************************************
 * Internal Code
 ******************************************************************************/
/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Called from the Interrupt service routine.
 *
 * Checks whether callback_func is not NULL,
 * and unless callback is blocked by callback_blocked being non-zero it calls the callback function with callback_data as parameter,
 * otherwise callback_pending is set to non-zero value.
 *
 * @return void
 *
 * @see HWTIMER_SYS_Pitdeinit
 * @see HWTIMER_SYS_PitsetDiv
 * @see HWTIMER_SYS_Pitstart
 * @see HWTIMER_SYS_Pitstop
 * @see HWTIMER_SYS_PitgetTime
 */
void HWTIMER_SYS_PitIsrAction(uint8_t pitChannel)
{
    PIT_Type * base = g_pitBase[0];
    hwtimer_t *hwtimer =  g_hwtimersPit[pitChannel];

    /* If hwtimer exist*/
    if (NULL != hwtimer)
    {
        /* Check if interrupt is enabled for this channel. Cancel spurious interrupt */
        if (!(PIT_BRD_TCTRL_TIE(base, pitChannel)))
        {
            return;
        }

        /* If interrupt occurred for this pit and channel*/
        if(PIT_HAL_IsIntPending(base, pitChannel))
        {
            /* Clear interrupt flag */
            PIT_HAL_ClearIntFlag(base, pitChannel);
            /* Following part of function is typically the same for all low level hwtimer drivers */
            hwtimer->ticks++;

            if (NULL != hwtimer->callbackFunc)
            {
                if (hwtimer->callbackBlocked)
                {
                    hwtimer->callbackPending = 1U;
                }
                else
                {
                    /* Run user function*/
                    hwtimer->callbackFunc(hwtimer->callbackData);
                }
            }
        }
    }
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief This function initializes caller allocated structure according to given
 * numerical identifier of the timer.
 *
 * Called by hwtimer_init().
 * Initializes the HWTIMER structure.
 *
 * @param hwtimer[in]   Returns initialized hwtimer structure handle.
 * @param pitId[in]     Determines PIT module and pit channel.
 * @param data[in]      Specific data. Not used in this timer.
 *
 * @return kHwtimerSuccess              Success.
 * @return kHwtimerInvalidInput         When channel number does not exist in pit module.
 * @return kHwtimerRegisterHandlerError When registration of the interrupt service routine failed.
 *
 * @see HWTIMER_SYS_PitDeinit
 * @see HWTIMER_SYS_PitSetDiv
 * @see HWTIMER_SYS_PitStart
 * @see HWTIMER_SYS_PitStop
 * @see HWTIMER_SYS_PitGetTime
 * @see HWTIMER_SYS_PitIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_PitInit(hwtimer_t * hwtimer, uint32_t pitId, void *data)
{
    uint32_t pitChannel;
    PIT_Type * base = g_pitBase[0];
    if (FSL_FEATURE_PIT_TIMER_COUNT < pitId)
    {
        return kHwtimerInvalidInput;
    }

    assert(NULL != hwtimer);

    /* We need to store pitId of timer in context struct */
    hwtimer->llContext[0U] = pitId;

    pitChannel = hwtimer->llContext[0U];

   /* Un-gate pit clock */
    CLOCK_SYS_EnablePitClock(0U);

    /* Enable PIT module clock */
    PIT_HAL_Enable(base);

    /* Allows the timers to be stopped when the device enters the Debug mode. */
    PIT_HAL_SetTimerRunInDebugCmd(base, false);

    /* Disable timer and interrupt */
    PIT_HAL_StopTimer(base, pitChannel);
    PIT_HAL_SetIntCmd(base, pitChannel, false);
    /* Clear any pending interrupt */
    PIT_HAL_ClearIntFlag(base, pitChannel);

    /* Store hwtimer in global array */
    g_hwtimersPit[pitChannel] = hwtimer;

    PIT_HAL_SetIntCmd(base, pitChannel, true);
    INT_SYS_EnableIRQ(g_pitIrqId[pitChannel]);

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Initialization of pit timer module
 *
 * Called by hwtimer_deinit. Disables the peripheral. Unregisters ISR.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 *
 * @return kHwtimerSuccess              Success.
 * @return kHwtimerRegisterHandlerError When un-registration of the interrupt service routine failed.
 *
 * @see HWTIMER_SYS_PitInit
 * @see HWTIMER_SYS_PitSetDiv
 * @see HWTIMER_SYS_PitStart
 * @see HWTIMER_SYS_PitStop
 * @see HWTIMER_SYS_PitGetTime
 * @see HWTIMER_SYS_PitIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_PitDeinit(hwtimer_t * hwtimer)
{
    /* We believe that if isr is shared ,than is shared for every channels */
    PIT_Type * base = g_pitBase[0];
    uint32_t pitChannel;
    int i;

    assert(NULL != hwtimer);

    pitChannel = hwtimer->llContext[0U];
    assert(pitChannel < FSL_FEATURE_PIT_TIMER_COUNT);

    /* Remove Hwtimer from global array and disable interrupt on this channel */
    PIT_HAL_StopTimer(base, pitChannel);
    PIT_HAL_SetIntCmd(base, pitChannel, false);
    PIT_HAL_ClearIntFlag(base, pitChannel);

    /* Pit can have shared interrupt vectors. We need un-register interrupt only when all hwtimers are de-inited(set to NULL) */
    g_hwtimersPit[pitChannel] = NULL;

    /* Check if this is last hwtimer in pit_hwtimers_array */
    for (i = 0U; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        if (NULL != g_hwtimersPit[i])
        {
            break;
        }
    }

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Sets up timer with divider settings closest to the requested period in microseconds.
 *
 * The function gets the value of the base frequency of the timer via clock manager and calculates required
 * divider ratio.
 *
 * Called by hwtimer_set_freq() and hwtimer_set_period().
 * Fills in the divider (actual total divider) and modulo (sub-tick resolution) members of the HWTIMER structure.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 * @param period[in] Required period of timer in micro seconds.
 *
 * @return kHwtimerSuccess                Success.
 *
 * @see HWTIMER_SYS_PitInit
 * @see HWTIMER_SYS_PitDeinit
 * @see HWTIMER_SYS_PitStart
 * @see HWTIMER_SYS_PitStop
 * @see HWTIMER_SYS_PitGetTime
 * @see HWTIMER_SYS_PitIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_PitSetDiv(hwtimer_t * hwtimer, uint32_t period)
{
    uint32_t pitChannel;
    PIT_Type * base = g_pitBase[0];
    uint64_t divider;

    assert(NULL != hwtimer);

    /* Store clock frequency in struct. */
    hwtimer->clockFreq = CLOCK_SYS_GetPitFreq(0);

    divider = (((uint64_t)hwtimer->clockFreq * period)) / 1000000U ;
    /* If required frequency is higher than input clock frequency, we set divider 1 (for setting the highest possible frequency) */
    if (0U == divider)
    {
        divider = 1U;
    }
    /* if divider is greater than 32b value we set divider to max 32b value */
    else if (divider & 0xFFFFFFFF00000000U)
    {
        return kHwtimerInvalidInput;
    }

    pitChannel = hwtimer->llContext[0U];
    assert(pitChannel < FSL_FEATURE_PIT_TIMER_COUNT);

    /* Set divider for pit chanell */
    PIT_HAL_SetTimerPeriodByCount(base, pitChannel, divider - 1U);

    hwtimer->divider    = divider;
    hwtimer->modulo     = divider;

    return kHwtimerSuccess;
}


/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Start pit timer module
 *
 * This function enables the timer and leaves it running, timer is
 * periodically generating interrupts.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 *
 * @return kHwtimerSuccess Success.
 *
 * @see HWTIMER_SYS_PitInit
 * @see HWTIMER_SYS_PitDeinit
 * @see HWTIMER_SYS_PitSetDiv
 * @see HWTIMER_SYS_PitStop
 * @see HWTIMER_SYS_PitGet_time
 * @see HWTIMER_SYS_PitIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_PitStart(hwtimer_t * hwtimer)
{
    uint32_t pitChannel;
    PIT_Type * base = g_pitBase[0];
    assert(NULL != hwtimer);

    pitChannel = hwtimer->llContext[0U];
    assert(pitChannel < FSL_FEATURE_PIT_TIMER_COUNT);

    PIT_HAL_StopTimer(base, pitChannel);
    PIT_HAL_ClearIntFlag(base, pitChannel);
    PIT_HAL_SetIntCmd(base, pitChannel, true);
    PIT_HAL_StartTimer(base, pitChannel);

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Stop pit timer module
 *
 * Disable timer and interrupt
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 *
 * @return kHwtimerSuccess Success.
 *
 * @see HWTIMER_SYS_PitInit
 * @see HWTIMER_SYS_PitDeinit
 * @see HWTIMER_SYS_PitSetDiv
 * @see HWTIMER_SYS_PitStart
 * @see HWTIMER_SYS_PitGetTime
 * @see HWTIMER_SYS_PitIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_PitStop(hwtimer_t * hwtimer)
{
    uint32_t pitChannel;
    PIT_Type * base = g_pitBase[0];
    assert(NULL != hwtimer);

    pitChannel = hwtimer->llContext[0U];
    assert(pitChannel < FSL_FEATURE_PIT_TIMER_COUNT);

    /* Disable timer and interrupt */
    PIT_HAL_StopTimer(base, pitChannel);
    PIT_HAL_SetIntCmd(base, pitChannel, false);
    PIT_HAL_ClearIntFlag(base, pitChannel);

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Atomically captures current time into HWTIMER_TIME_STRUCT structure
 *
 * Corrects/normalizes the values if necessary (interrupt pending, etc.)
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 * @param time[out]   Pointer to time structure. This value is filled with current value of the timer.
 *
 * @return kHwtimerSuccess Success.
 *
 * @see HWTIMER_SYS_PitInit
 * @see HWTIMER_SYS_PitDeinit
 * @see HWTIMER_SYS_PitSetDiv
 * @see HWTIMER_SYS_PitStart
 * @see HWTIMER_SYS_PitStop
 * @see HWTIMER_SYS_PitIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_PitGetTime(hwtimer_t *hwtimer, hwtimer_time_t *time)
{
    uint32_t    pitChannel;
    uint32_t    tempCval;
    PIT_Type * base = g_pitBase[0];
    assert(NULL != hwtimer);
    assert(NULL != time);

    pitChannel = hwtimer->llContext[0U];
    assert(pitChannel < FSL_FEATURE_PIT_TIMER_COUNT);

    /* Enter critical section to avoid disabling interrupt from pit for very long time */
    OSA_EnterCritical(kCriticalDisableInt);
    PIT_HAL_SetIntCmd(base, pitChannel, false);

    time->ticks = hwtimer->ticks;

    tempCval = PIT_HAL_ReadTimerCount(base, pitChannel);
    /* Check pending interrupt flag */
   if (PIT_HAL_IsIntPending(base, pitChannel))
    {
        PIT_HAL_SetIntCmd(base, pitChannel, true);
        OSA_ExitCritical(kCriticalDisableInt);
        time->subTicks = hwtimer->modulo - 1U;
    }
    else
    {
        PIT_HAL_SetIntCmd(base, pitChannel, true);
        OSA_ExitCritical(kCriticalDisableInt);
        /* todo: following line should be updated when HAL will be updated with this functionality. */
        time->subTicks = PIT_RD_LDVAL(base, pitChannel) - tempCval;
    }

    return kHwtimerSuccess;
}
 /*******************************************************************************
 * Code
 ******************************************************************************/
/*******************************************************************************
 * EOF
 ******************************************************************************/
