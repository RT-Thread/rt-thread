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
#ifndef __FSL_PIT_HAL_H__
#define __FSL_PIT_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup pit_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Error codes for PIT driver. */
typedef enum _pit_status
{
    kStatus_PIT_Success = 0x00U,
    kStatus_PIT_Fail    = 0x01U
} pit_status_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Enables the PIT module.
 *
 * This function enables the PIT timer clock (Note: this function does not un-gate
 * the system clock gating control). It should be called before any other timer
 * related setup.
 *
 * @param base Base address for current PIT instance.
 */
static inline void PIT_HAL_Enable(PIT_Type * base)
{
    PIT_BWR_MCR_MDIS(base, 0U);
}

/*!
 * @brief Disables the PIT module.
 *
 * This function disables all PIT timer clocks(Note: it does not affect the
 * SIM clock gating control).
 *
 * @param base Base address for current PIT instance.
 */
static inline void PIT_HAL_Disable(PIT_Type * base)
{
    PIT_BWR_MCR_MDIS(base, 1U);
}

/*!
 * @brief Configures the timers to continue  running or to stop in debug mode.
 *
 * In debug mode, the timers may or may not be frozen, based on the configuration of
 * this function. This is intended to aid software development, allowing the developer
 * to halt the processor, investigate the current state of the system (for example,
 * the timer values), and  continue the operation.
 *
 * @param base Base address for current PIT instance.
 * @param timerRun Timers run or stop in debug mode.
 *        - true:  Timers continue to run in debug mode.
 *        - false: Timers stop in debug mode.
 */
static inline void PIT_HAL_SetTimerRunInDebugCmd(PIT_Type * base, bool timerRun)
{
    PIT_BWR_MCR_FRZ(base, !timerRun);
}

#if FSL_FEATURE_PIT_HAS_CHAIN_MODE
/*!
 * @brief Enables or disables the timer chain with the previous timer.
 *
 * When a timer has a chain mode enabled, it  only counts after the previous
 * timer has expired. If the timer n-1 has counted down to 0, counter n
 * decrements the value by one. This allows the developers to chain timers together
 * and form a longer timer. The first timer (timer 0) cannot be chained to any
 * other timer.
 *
 * @param base Base address for current PIT instance.
 * @param channel  Timer channel number which is chained with the previous timer.
 * @param enable Enable or disable chain.
 *        - true:  Current timer is chained with the previous timer.
 *        - false: Timer doesn't chain with other timers.
 */
static inline void PIT_HAL_SetTimerChainCmd(PIT_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    PIT_BWR_TCTRL_CHN(base, channel, enable);
}

#endif /* FSL_FEATURE_PIT_HAS_CHAIN_MODE*/

/* @} */

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the timer counting.
 *
 * After calling this function, timers load the start value as specified by the function
 * PIT_HAL_SetTimerPeriodByCount(PIT_Type * base, uint32_t channel, uint32_t count), count down to
 * 0, and  load the respective start value again. Each time a timer reaches 0,
 * it generates a trigger pulse and sets the time-out interrupt flag.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 */
static inline void PIT_HAL_StartTimer(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    PIT_BWR_TCTRL_TEN(base, channel, 1U);
}

/*!
 * @brief Stops the timer from counting.
 *
 * This function stops every timer from counting. Timers reload their periods
 * respectively after they call the PIT_HAL_StartTimer the next time.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 */
static inline void PIT_HAL_StopTimer(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    PIT_BWR_TCTRL_TEN(base, channel, 0U);
}

/*!
 * @brief Checks to see whether the current timer is started or not.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 * @return Current timer running status
 *         -true: Current timer is running.
 *         -false: Current timer has stopped.
 */
static inline bool PIT_HAL_IsTimerRunning(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    return PIT_BRD_TCTRL_TEN(base, channel);
}

/* @} */

/*!
 * @name Timer Period
 * @{
 */

/*!
 * @brief Sets the timer period in units of count.
 *
 * Timers begin counting from the value set by this function.
 * The counter period of a running timer can be modified by first stopping
 * the timer, setting a new load value, and  starting the timer again. If
 * timers are not restarted, the new value is loaded after the next trigger
 * event.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 * @param count Timer period in units of count
 */
static inline void PIT_HAL_SetTimerPeriodByCount(PIT_Type * base, uint32_t channel, uint32_t count)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    PIT_WR_LDVAL(base, channel, count);
}

/*!
 * @brief Returns the current timer period in units of count.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 * @return Timer period in units of count
 */
static inline uint32_t PIT_HAL_GetTimerPeriodByCount(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    return PIT_RD_LDVAL(base, channel);
}

/*!
 * @brief Reads the current timer counting value.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 * @return Current timer counting value
 */
static inline uint32_t PIT_HAL_ReadTimerCount(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    return PIT_RD_CVAL(base, channel);
}

#if FSL_FEATURE_PIT_HAS_LIFETIME_TIMER
/*!
 * @brief Reads the current lifetime counter value.
 *
 * The lifetime timer is a 64-bit timer which chains timer 0 and timer 1 together.
 * Timer 0 and 1 are chained by calling the PIT_HAL_SetTimerChainCmd
 * before using this timer. The period of lifetime timer is equal to the "period of
 * timer 0 * period of timer 1". For the 64-bit value, the higher 32-bit has
 * the value of timer 1, and the lower 32-bit has the value of timer 0.
 *
 * @param base Base address for current PIT instance.
 * @return Current lifetime timer value
 */
uint64_t PIT_HAL_ReadLifetimeTimerCount(PIT_Type * base);
#endif /*FSL_FEATURE_PIT_HAS_LIFETIME_TIMER*/

/* @} */

/*!
 * @name Interrupt
 * @{
 */

/*!
 * @brief Enables or disables the timer interrupt.
 *
 * If enabled, an interrupt happens when a timeout event occurs
 * (Note: NVIC should be called to enable pit interrupt in system level).
 *
 * @param base Base address for current PIT instance.
 * @param channel  Timer channel number
 * @param enable Enable or disable interrupt.
 *        - true:  Generate interrupt when timer counts to 0.
 *        - false: No interrupt is generated.
 */
static inline void PIT_HAL_SetIntCmd(PIT_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    PIT_BWR_TCTRL_TIE(base, channel, enable);
}

/*!
 * @brief Checks whether the timer interrupt is enabled or not.
 *
 * @param base Base address for current PIT instance.
 * @param channel  Timer channel number
 * @return Status of enabled or disabled interrupt
 *        - true: Interrupt is enabled.
 *        - false: Interrupt is disabled.
 */
static inline bool PIT_HAL_GetIntCmd(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    return PIT_BRD_TCTRL_TIE(base, channel);
}

/*!
 * @brief Clears the timer interrupt flag.
 *
 * This function clears the timer interrupt flag after a timeout event
 * occurs.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 */
static inline void PIT_HAL_ClearIntFlag(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    /* Write 1 will clear the flag. */
    PIT_WR_TFLG(base, channel, 1U);
}

/*!
 * @brief Reads the current timer timeout flag.
 *
 * Every time the timer counts to 0, this flag is set.
 *
 * @param base Base address for current PIT instance.
 * @param channel Timer channel number
 * @return Current status of the timeout flag
 *         - true:  Timeout has occurred.
 *         - false: Timeout has not yet occurred.
 */
static inline bool PIT_HAL_IsIntPending(PIT_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    return PIT_RD_TFLG(base, channel);
}

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_PIT_HAL_H__*/
/*******************************************************************************
* EOF
*******************************************************************************/

