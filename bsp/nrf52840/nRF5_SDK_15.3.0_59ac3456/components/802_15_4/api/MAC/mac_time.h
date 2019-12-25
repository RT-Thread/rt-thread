/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef MAC_TIME_H_INCLUDED
#define MAC_TIME_H_INCLUDED

#include <stdint.h>
#include "sys_time.h"
#include "hal_timer.h"
#include "hal_timer_critical.h"
#include "sys_debug.h"

/** @file
 * The MAC Time module declares some useful macros/types and routines that deal with the MAC
 * timer.
 *
 * @defgroup mac_time MAC Time API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC Time API.
 * @details The MAC Time module declares some useful macros/types and routines that deal with the MAC
 * timer. More specifically, some convertion routines such as mac_timestamp_from_systime(),
 * mac_time_from_us(), and mac_time_to_us() are declared here.
 */

/**@brief This mask shall always be used after any mathematical operation on
 * mac_time_t to avoid overflow.
 */
#define MAC_TIME_MASK              0xFFFFFFULL

/**@brief   Type of MAC time in symbols. */
typedef uint32_t  mac_time_t;

/**@brief   Type is used to save timestamps with microsecond precision. */
typedef uint32_t  mac_timestamp_t;


/**@brief   Gets timestamp from system time.
 *
 * @param[in]   time_us   System time.
 *
 * @return Time in us but smaller type size.
 */
static inline mac_timestamp_t mac_timestamp_from_systime(sys_time_t time_us)
{
    return (mac_timestamp_t)time_us;
}

/**@brief   Converts microseconds to symbol time.
 *
 * @details Symbol time is measured in PHY Symbol Periods (16 us).
 *
 * @param[in]   time_us     Time in microseconds.
 *
 * @return Time in PHY Symbol Periods (16 us).
 */
static inline mac_time_t mac_time_from_us(sys_time_t time_us)
{
    return (mac_time_t)((time_us >> 4ull) & MAC_TIME_MASK);
}


/**@brief   Converts symbol time to microseconds.
 *
 * @details Symbol time is measured in PHY Symbol Periods (16 us).
 *
 * @param[in]   time_symbol    Time in PHY Symbol Periods (16 us).
 *
 * @return Time in microseconds.
 */
static inline sys_time_t mac_time_to_us(mac_time_t time_symbol)
{
    return time_symbol << 4u;
}


/**@brief   Starts the critical MAC timer.
 *
 * @details The callback function of the critical MAC timer will be called from
 *          the timer's interrupt routine. Only one critical MAC timer can run
 *          at the same time.
 *
 * @warning This is internal MAC functionality, needed for the realtime channel access.
 *          This function must not be used by other modules.
 *
 * @param[in]   interval_us         Interval in microseconds, after which the callback 
 *                                  function will be called.
 * @param[in]   callback            Callback function to be called after the specified inteval.
 */
static inline void mac_timer_critical_start(sys_time_t interval_us, void (* callback)(void))
{
    // Make sure interval_us fits into 32 bits, since hardware critical timer is 32 bit.
    ASSERT(interval_us < (1ULL << 32));

    hal_timer_critical_start((uint32_t)interval_us, callback);
}


/**@brief   Stops the critical MAC timer.
 *
 * @details After critical MAC timer is stopped with this function, its callback will not be called.
 *
 * @warning This is internal MAC functionality, needed for the realtime channel access.
 *          This function must not be used by other modules.
 */
static inline void mac_timer_critical_stop(void)
{
    hal_timer_critical_stop();
}

/** @} */

#endif // MAC_TIME_H_INCLUDED
