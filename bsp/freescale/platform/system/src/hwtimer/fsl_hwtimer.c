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
#include <assert.h>
#include "fsl_hwtimer.h"

/*******************************************************************************
 * Internal type definition
 ******************************************************************************/
/*******************************************************************************
 * Internal Variables
 ******************************************************************************/
 /*******************************************************************************
 * Internal Code
 ******************************************************************************/
 /*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_Init
 * Description   : The device interface pointer determines low layer driver to
 * be used. Device interface structure is exported by each low layer driver and
 * is opaque to the applications. Please refer to chapter concerning low layer
 * driver below for details. Meaning of the numerical identifier varies depending
 * on low layer driver used. Typically, it identifies particular timer channel to
 * initialize. The initialization function has to be called prior using any other
 * API function.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_Init(hwtimer_t *hwtimer, const hwtimer_devif_t * kDevif, uint32_t id, void *data)
 {
    /* Check input parameters */
    if ((hwtimer == NULL) || (kDevif == NULL))
    {
        return kHwtimerInvalidInput;
    }

    assert(NULL != kDevif->init);

    /* Initialize hwtimer structure */
    hwtimer->devif   = kDevif;
    hwtimer->ticks   = 0U;
    hwtimer->divider = 0U;
    hwtimer->modulo  = 0U;
    hwtimer->callbackFunc = NULL;
    hwtimer->callbackData = NULL;
    hwtimer->callbackPending = 0U;
    hwtimer->callbackBlocked = 0U;

    /* Call low level driver init function. */
    return hwtimer->devif->init(hwtimer, id, data);
 }

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_Deinit
 * Description   : Calls lower layer stop function to stop timer, then calls low
 * layer de-initialization function and afterwards invalidates hwtimer structure
 * by clearing it.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_Deinit(hwtimer_t *hwtimer)
{
    _hwtimer_error_code_t result;

    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }
    if (NULL == hwtimer->devif)
    {
        return kHwtimerInvalidPointer;
    }
    /* Stop timer if runs */
    assert(NULL != hwtimer->devif->stop);
    result = hwtimer->devif->stop(hwtimer);
    if (kHwtimerSuccess != result)
    {
        return result;
    }

    /* De-initialize timer. */
    assert(NULL != hwtimer->devif->deinit);
    result = hwtimer->devif->deinit(hwtimer);
    if (kHwtimerSuccess != result)
    {
        return result;
    }

    hwtimer->devif      = NULL;
    hwtimer->clockFreq  = 0U;
    hwtimer->ticks      = 0U;
    hwtimer->divider    = 0U;
    hwtimer->modulo     = 0U;
    hwtimer->callbackFunc = NULL;
    hwtimer->callbackData = NULL;
    hwtimer->callbackPending = 0U;
    hwtimer->callbackBlocked = 0U;

    return kHwtimerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_SetPeriod
 * Description   : The function provides an alternate way to set up the timer to
 * desired period specified in microseconds rather than to frequency in Hz.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_SetPeriod(hwtimer_t *hwtimer, uint32_t period)
{
    /* Check input parameters */
    if ((NULL == hwtimer) || (0U == period))
    {
        return kHwtimerInvalidInput;
    }
    if (NULL == hwtimer->devif)
    {
        return kHwtimerInvalidPointer;
    }

    assert(NULL != hwtimer->devif->setDiv);
    return hwtimer->devif->setDiv(hwtimer, period);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_GetPeriod
 * Description   : The function returns current period of the timer in
 * microseconds calculated from the base frequency and actual divider settings
 * of the timer.
 *
 *END**************************************************************************/
uint32_t HWTIMER_SYS_GetPeriod(hwtimer_t *hwtimer)
{
    uint32_t period;

    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return 0U;
    }

    /* Obtain clock source clock frequency.*/
    if (hwtimer->clockFreq == 0U)
    {
        return 0U;
    }

    assert(hwtimer->divider <= hwtimer->clockFreq);
    /* Divider is always less than clockFreq */
    period = ((uint64_t)1000000U * hwtimer->divider) / hwtimer->clockFreq;

    return period;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_Start
 * Description   : Enables the timer and leaves it running. The timer starts
 * counting a new period generating interrupts every time the timer rolls over.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_Start(hwtimer_t *hwtimer)
{
    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }
    if (NULL == hwtimer->devif)
    {
        return kHwtimerInvalidPointer;
    }
    /* Start timer */
    assert(NULL != hwtimer->devif->start);
    return hwtimer->devif->start(hwtimer);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_Stop
 * Description   : The timer stops counting after this function is called.
 * Pending interrupts and callbacks are cancelled.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_Stop(hwtimer_t *hwtimer)
{
    _hwtimer_error_code_t result;

    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }
    if (NULL == hwtimer->devif)
    {
        return kHwtimerInvalidPointer;
    }

    assert(NULL != hwtimer->devif->stop);
    result = hwtimer->devif->stop(hwtimer);
    hwtimer->callbackPending = 0U;

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_GetModulo
 * Description   : The function returns period of the timer in sub-ticks. It is
 * typically called after HWTIMER_SYS_SetPeriod() to obtain actual resolution
 * of the timer in the current configuration.
 *
 *END**************************************************************************/
uint32_t HWTIMER_SYS_GetModulo(hwtimer_t *hwtimer)
{
    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return 0U;
    }

    return hwtimer->modulo;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_GetTime
 * Description   : The function reads the current value of the hwtimer. Elapsed
 * periods(ticks) and current value of the timer counter (sub-ticks) are filled
 * into the Hwtimer_time structure. The sub-ticks number always counts up and is
 * reset to zero when the timer overflows regardless of the counting direction
 * of the underlying device.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_GetTime(hwtimer_t *hwtimer, hwtimer_time_t *time)
{
    /* Check input parameters */
    if ((NULL == hwtimer) || (NULL == time))
    {
        return kHwtimerInvalidInput;
    }
    if (NULL == hwtimer->devif)
    {
        return kHwtimerInvalidPointer;
    }

    assert(NULL != hwtimer->devif->getTime);
    return hwtimer->devif->getTime(hwtimer, time);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_GetTicks
 * Description   : The function reads the current value of the hwtimer.
 * The returned value corresponds with lower 32 bits of elapsed periods (ticks).
 * The value is guaranteed to be obtained atomically without necessity to mask
 * timer interrupt. Lower layer driver is not involved at all, thus call to this
 * function is considerably faster than HWTIMER_SYS_GetTime.
 *
 *END**************************************************************************/
uint32_t HWTIMER_SYS_GetTicks(hwtimer_t *hwtimer)
{
    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return 0U;
    }

    /* return lower 32b of 64 bit value */
    return (uint32_t)hwtimer->ticks;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_RegisterCallback
 * Description   : Registers function to be called when the timer expires.
 * The callback_data is arbitrary pointer passed as parameter to the callback
 * function.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_RegisterCallback(hwtimer_t *hwtimer, hwtimer_callback_t callbackFunc, void *callbackData)
{
    hwtimer_t volatile *hwtimerVol;

    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }

    hwtimerVol = hwtimer;
    /* Volatile used to prevent optimization of following lines. Interrupt may happen meanwhile. */
    hwtimerVol->callbackFunc = NULL; /* Prevent callback execution with old data */
    hwtimerVol->callbackPending = 0U;
    hwtimerVol->callbackData = callbackData;
    hwtimerVol->callbackFunc = callbackFunc;

    return kHwtimerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_BlockCallback
 * Description   : The function is used to block callbacks in circumstances when
 * execution of the callback function is undesired. If the timer overflows when
 * callbacks are blocked the callback becomes pending.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_BlockCallback(hwtimer_t *hwtimer)
{
    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }

    hwtimer->callbackBlocked = 1U;

    return kHwtimerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_UnblockCallback
 * Description   : The function is used to unblock previously blocked callbacks.
 * If there is a callback pending, it gets immediately executed. This function
 * must not be called from a callback routine (it does not make sense to do so
 * anyway as callback function never gets executed while callbacks are blocked).
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_UnblockCallback(hwtimer_t *hwtimer)
{
    hwtimer_callback_t callbackFunc;
    hwtimer_t volatile *hwtimerVol = hwtimer;

    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }

    /* Unblock callbacks in ISR. No more pending request could arrive after this. */
    hwtimerVol->callbackBlocked = 0U;
    /* Check for any previously set pending requests during blocked state */
    if (hwtimerVol->callbackPending)
    {
        callbackFunc = hwtimerVol->callbackFunc;
        if (NULL != callbackFunc)
        {
            /* Prevent invocation of callback from ISR (callback may not be re-entrant) */
            hwtimerVol->callbackFunc = NULL;
            callbackFunc(hwtimerVol->callbackData);
            /* Allow invocation of callback from ISR */
            hwtimerVol->callbackFunc = callbackFunc;
        }
        /* Clear pending flag, callback just serviced */
        hwtimerVol->callbackPending = 0U;
    }

    return kHwtimerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HWTIMER_SYS_CancelCallback
 * Description   : The function cancels pending callback, if any.
 *
 *END**************************************************************************/
_hwtimer_error_code_t HWTIMER_SYS_CancelCallback(hwtimer_t *hwtimer)
{
    /* Check input parameters */
    if (NULL == hwtimer)
    {
        return kHwtimerInvalidInput;
    }

    hwtimer->callbackPending = 0U;

    return kHwtimerSuccess;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
