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
#include "fsl_hwtimer_systick.h"
#include "fsl_os_abstraction.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Internal type definition
 ******************************************************************************/
/*******************************************************************************
 * Internal Variables
 ******************************************************************************/
void HWTIMER_SYS_SystickIsrAction(void);
static _hwtimer_error_code_t HWTIMER_SYS_SystickInit(hwtimer_t *hwtimer, uint32_t systickId, void *data);
static _hwtimer_error_code_t HWTIMER_SYS_SystickDeinit(hwtimer_t *hwtimer);
static _hwtimer_error_code_t HWTIMER_SYS_SystickSetDiv(hwtimer_t *hwtimer, uint32_t period);
static _hwtimer_error_code_t HWTIMER_SYS_SystickStart(hwtimer_t *hwtimer);
static _hwtimer_error_code_t HWTIMER_SYS_SystickStop(hwtimer_t *hwtimer);
static _hwtimer_error_code_t HWTIMER_SYS_SystickGetTime(hwtimer_t *hwtimer, hwtimer_time_t *time);

const hwtimer_devif_t kSystickDevif =
{
    HWTIMER_SYS_SystickInit,
    HWTIMER_SYS_SystickDeinit,
    HWTIMER_SYS_SystickSetDiv,
    HWTIMER_SYS_SystickStart,
    HWTIMER_SYS_SystickStop,
    HWTIMER_SYS_SystickGetTime,
};

static hwtimer_t *g_hwtimersSystick = NULL;


 /*******************************************************************************
 * Internal Code
 ******************************************************************************/

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Called from the Interrupt service routine.
 *
 * This ISR is used when SysTick counted to 0.
 * Checks whether callback_func is not NULL,
 * and unless callback is blocked by callback_blocked being non-zero it calls the callback function with callback_data as parameter,
 * otherwise callback_pending is set to non-zero value.
 *
 * @return void
 *
 * @see HWTIMER_SYS_SystickDeinit
 * @see HWTIMER_SYS_SystickSet_div
 * @see HWTIMER_SYS_SystickStart
 * @see HWTIMER_SYS_SystickStop
 * @see HWTIMER_SYS_SystickGet_time
 */
void HWTIMER_SYS_SystickIsrAction(void)
{
    hwtimer_t *hwtimer = g_hwtimersSystick;

    /* Check if interrupt is enabled for this systick. Cancel spurious interrupt */
    if (!(SysTick_CTRL_TICKINT_Msk & SysTick->CTRL))
    {
        return;
    }

    if (NULL != hwtimer)
    {

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


/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief This function initializes caller allocated structure according to given
 * numerical identifier of the timer.
 *
 * Called by hwtimer_init().
 * Initializes the hwtimer_t structure.
 *
 * @param hwtimer[in]   Returns initialized hwtimer structure handle.
 * @param systickId[in] Determines Systick modul( Always 0).
 * @param isrPrior[in]  Interrupt priority for systick
 * @param data[in]      Specific data. Not used in this timer.
 *
 * @return kHwtimerSuccess              Success.
 * @return kHwtimerInvalidInput         When systick_id does not exist(When systick_id is not zero).
 * @return kHwtimerRegisterHandlerError When registration of the interrupt service routine failed.
 *
 * @see HWTIMER_SYS_SystickDeinit
 * @see HWTIMER_SYS_SystickSet_div
 * @see HWTIMER_SYS_SystickStart
 * @see HWTIMER_SYS_SystickStop
 * @see HWTIMER_SYS_SystickGet_time
 * @see HWTIMER_SYS_SystickIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_SystickInit(hwtimer_t *hwtimer, uint32_t systickId, void *data)
{

    assert(NULL != hwtimer);
    /* We count only with one systick module inside core */
    if ( 1U <= systickId)
    {
        return kHwtimerInvalidInput;
    }

    /* Disable timer and interrupt. Set clock source to processor clock */
    /* But mostly The CLKSOURCE bit in SysTick Control and Status register is always set to select the core clock. */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;

    /* Reset reload value register. A start value of 0 is possible, but has no effect */
    SysTick->LOAD = 0U;
    /* A write of any value to current value register clears the field to 0, and also clears the SYST_CSR COUNTFLAG bit to 0. */
    SysTick->VAL = 0U;

    /* Store hwtimer in global variable */
    g_hwtimersSystick = hwtimer;

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Initialization of systick timer module
 *
 * Called by hwtimer_deinit. Disables the peripheral. Unregisters ISR.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 *
 * @return kHwtimerSuccess              Success.
 * @return kHwtimerRegisterHandlerError When registration of the interrupt service routine failed.
 *
 * @see HWTIMER_SYS_SystickInit
 * @see HWTIMER_SYS_SystickSet_div
 * @see HWTIMER_SYS_SystickStart
 * @see HWTIMER_SYS_SystickStop
 * @see HWTIMER_SYS_SystickGet_time
 * @see HWTIMER_SYS_SystickIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_SystickDeinit(hwtimer_t *hwtimer)
{
    _hwtimer_error_code_t retval = kHwtimerSuccess;
    assert(NULL != hwtimer);

    /* Disable timer and interrupt */
    SysTick->CTRL = 0U;
    /* Reset reload value register. A start value of 0 is possible, but has no effect */
    SysTick->LOAD = 0U;
    /* A write of any value to current value register clears the field to 0, and also clears the SYST_CSR COUNTFLAG bit to 0. */
    SysTick->VAL = 0U;

    g_hwtimersSystick = NULL;

    return retval;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Sets up timer with divider settings closest to the requested period in microseconds.
 *
 * The function gets the value of the base frequency of the timer via clock manager and calculates required
 * divider ratio. If the required period is a large value, then the code will try to use a low-frequency
 * external clock if available.
 *
 * Called by hwtimer_set_freq() and hwtimer_set_period().
 * Fills in the divider (actual total divider) and modulo (sub-tick resolution) members of the hwtimer_t structure.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 * @param period[in] Required period of timer in micro seconds.
 *
 * @return kHwtimerSuccess      Success.
 * @return kHwtimerInvalidInput Divider is equal too big.
 *
 * @see HWTIMER_SYS_SystickInit
 * @see HWTIMER_SYS_SystickDeinit
 * @see HWTIMER_SYS_SystickStart
 * @see HWTIMER_SYS_SystickStop
 * @see HWTIMER_SYS_SystickGet_time
 * @see HWTIMER_SYS_SystickIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_SystickSetDiv(hwtimer_t *hwtimer, uint32_t period)
{
    assert(NULL != hwtimer);
    uint64_t divider;

#if FSL_FEATURE_SYSTICK_HAS_EXT_REF
    /* Set the clock source back to core freq */
    CLOCK_SYS_SetSystickSrc(kClockSystickSrcCore);
#endif
    /* Get Core clock frequency */
    hwtimer->clockFreq = CLOCK_SYS_GetSystickFreq();

    divider = (((uint64_t)hwtimer->clockFreq * period)) / 1000000U ;

    /* if divider is greater than 24b value we return an error */
    if ((divider - 1U) & ~SysTick_LOAD_RELOAD_Msk)
    {
#if FSL_FEATURE_SYSTICK_HAS_EXT_REF
        /* Check if we can use a slower clock source to get required period */
        CLOCK_SYS_SetSystickSrc(kClockSystickSrcExtRef);
        hwtimer->clockFreq = CLOCK_SYS_GetSystickFreq();
        divider = (((uint64_t)hwtimer->clockFreq * period)) / 1000000U ;

        if ((divider - 1U) & ~SysTick_LOAD_RELOAD_Msk)
        {
            return kHwtimerInvalidInput;
        }
#else
        return kHwtimerInvalidInput;
#endif
    }

    /*
     * A start value of 0 (divider == 1) is possible, but has no effect because the
     * SysTick interrupt and COUNTFLAG are activated when counting from 1 to 0.
     */
    if (divider == 1U)
    {
        divider = 2U; /* Set smallest possible value for divider. */
    }

    SysTick->LOAD = divider - 1U;

    /* Store in struct. */
    hwtimer->divider    = divider;
    hwtimer->modulo     = divider;

    return kHwtimerSuccess;
}


/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Start systick timer module
 *
 * This function enables the timer and leaves it running, timer is
 * periodically generating interrupts.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 *
 * @return kHwtimerSuccess Success.
 *
 * @see HWTIMER_SYS_SystickInit
 * @see HWTIMER_SYS_SystickDeinit
 * @see HWTIMER_SYS_SystickSet_div
 * @see HWTIMER_SYS_SystickStop
 * @see HWTIMER_SYS_SystickGet_time
 * @see HWTIMER_SYS_SystickIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_SystickStart(hwtimer_t *hwtimer)
{
    assert(NULL != hwtimer);

    /* A write of any value to current value register clears the field to 0, and also clears the SYST_CSR COUNTFLAG bit to 0. */
    SysTick->VAL = 0U;

    /* Run timer and enable interrupt */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Stop systick timer module.
 *
 * Disable timer and interrupt.
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 *
 * @return kHwtimerSuccess Success.
 *
 * @see HWTIMER_SYS_SystickInit
 * @see HWTIMER_SYS_SystickDeinit
 * @see HWTIMER_SYS_SystickSet_div
 * @see HWTIMER_SYS_SystickStart
 * @see HWTIMER_SYS_SystickGet_time
 * @see HWTIMER_SYS_SystickIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_SystickStop(hwtimer_t *hwtimer)
{
    assert(NULL != hwtimer);

    /* Disable timer and interrupt */
    SysTick->CTRL = 0U;

    return kHwtimerSuccess;
}

/*!
 * @cond DOXYGEN_PRIVATE
 *
 * @brief Atomically captures current time into Hwtimer_time structure.
 *
 * Corrects/normalizes the values if necessary (interrupt pending, etc.)
 *
 * @param hwtimer[in] Pointer to hwtimer structure.
 * @param time[out]   Pointer to time structure. This value is filled with current value of the timer.
 *
 * @return kHwtimerSuccess Success.
 *
 * @warning This function calls _int_enable and _int_disable functions
 *
 * @see HWTIMER_SYS_SystickInit
 * @see HWTIMER_SYS_SystickDeinit
 * @see HWTIMER_SYS_SystickSet_div
 * @see HWTIMER_SYS_SystickStart
 * @see HWTIMER_SYS_SystickStop
 * @see HWTIMER_SYS_SystickIsrAction
 */
static _hwtimer_error_code_t HWTIMER_SYS_SystickGetTime(hwtimer_t *hwtimer, hwtimer_time_t *time)
{
    uint32_t tempVal;

    assert(NULL != hwtimer);
    assert(NULL != time);

    /* Enter critical section to avoid disabling interrupt from pit for very long time */
    OSA_EnterCritical(kCriticalDisableInt);
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    time->ticks = hwtimer->ticks;
    tempVal = SysTick->VAL;
    /* Check systick pending interrupt flag */
    if (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
    {
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        OSA_ExitCritical(kCriticalDisableInt);
        time->subTicks = hwtimer->modulo - 1U;
    }
    else
    {
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        OSA_ExitCritical(kCriticalDisableInt);
        /* interrupt flag is set upon 1->0 transition, not upon reload - wrap around */
        time->subTicks = SysTick->LOAD - tempVal + 1U;
    }

    return kHwtimerSuccess;
}
 /*******************************************************************************
 * Code
 ******************************************************************************/
/*******************************************************************************
 * EOF
 ******************************************************************************/
