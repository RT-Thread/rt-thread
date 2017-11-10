/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef SYS_TIME_H_INCLUDED
#define SYS_TIME_H_INCLUDED

#include <stdint.h>
#include "sys_queue.h"

/** @file
 * This file contains declarations of the primitives to work with Time (timers) and necessary types.
 *
 * @defgroup sys_time Time API
 * @ingroup sys_15_4
 * @{
 * @brief Module for declaring Time API.
 * @details The system time module implements some routines to deal with time (timers). The timer can be started by
 * sys_timer_start(), stopped by sys_timer_stop(), and adjusted after sleep by sys_timer_adjust(). Some
 * information can be acquired by sys_timer_is_started() and sys_time_get(). The correct API for implementing hardware
 * delays is sys_time_delay_us(). Note that the module must be initialized by sys_timers_init() which
 * is done by sys_init().
 */

/**@brief   Unsigned type of system time.
 */
typedef uint64_t  sys_time_t;

/**@brief   Signed type of system time.
 */
typedef int64_t   sys_signed_time_t;

/**@brief   Prototype of the user-defined timer callback.
 *
 * @param   p_data  Pointer to the data, specific for this callback.
 */
typedef void (* sys_timer_callback_t)(void * p_data);


/**@brief   System timer type (one-shot or periodic timer).
 */
typedef enum
{
    SYS_TIMER_ONESHOT,   /**< The timer is Oneshot */
    SYS_TIMER_PERIODIC   /**< The timer is Periodic */
} sys_timer_type_t;


/**@brief   Timer descriptor.
 */
typedef struct
{
    /** Service field. */
    sys_queue_item_t    item;

    /** Service field. */
    sys_time_t          absolute_time;

    /** Relevant time moment, at which this timer is programmed to be triggered,
     *  measured in microseconds.
     */
    sys_time_t          interval;

    /** Periodic or one-shot timer.
     *
     * @details If type is set to SYS_TIMER_PERIODIC, the timer will restart automatically
     *          with the same period.
     */
    sys_timer_type_t     type;

    /** Timer callback function.
     *
     * @details This function is to be called, when this timer triggers.
     */
    sys_timer_callback_t callback;

    /** Timer callback parameter.
     *
     * @details This pointer is to be passed to the timer callback function.
     */
    void *               p_data;
} sys_timer_t;


/**@brief   Function for initializing the timers module.
 */
void sys_timers_init(void);


/**@brief   Function for starting the timer.
 *
 * @details See the description of \ref sys_timer_t fields for the details
 *          on how to program the timer.
 *
 * @param[in]   p_timer    Pointer to a valid timer descriptor, which is filled by the user,
 *                         according to \ref sys_timer_t fields description.
 */
void sys_timer_start(sys_timer_t * p_timer);


/**@brief   Function for stopping the timer.
 *
 * @details This function is used to stop the timer, which was started earlier.
 *          After this function is called, the timer will not fire.
 *
 * @param[in]   p_timer     Pointer to a valid timer descriptor.
 */
void sys_timer_stop(sys_timer_t * p_timer);


/**@brief   Function for checking if input timer has been started.
 *
 * @param[in]   p_timer     Pointer to a timer.
 *
 * @retval  true  p_timer has been started and has not been stopped yet.
 * @retval  false p_timer has never been started or already timed out.
 */
bool sys_timer_is_started(sys_timer_t * p_timer);


/**@brief   Function for getting the current system time.
 *
 * @retval  The current system timer counter value in microseconds.
 */
sys_time_t sys_time_get(void);


/**@brief   Function for implementing a delay for short hardware delays.
 *
 * @warning Interrupts are NOT disabled inside this function.
 *
 * @param[in]   delay_us    Number of microseconds to delay.
 */
void sys_time_delay_us(uint32_t delay_us);


/**@brief   Function for executing expired timers after sleep.
 */
void sys_timer_adjust(void);

/** @} */

#endif // SYS_TIME_H_INCLUDED
