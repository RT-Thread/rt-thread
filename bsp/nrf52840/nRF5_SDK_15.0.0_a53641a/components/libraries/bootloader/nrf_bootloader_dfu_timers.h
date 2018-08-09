/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
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
/**@file
 *
 * @defgroup nrf_bootloader_dfu_timers Timers for DFU in the bootloader
 * @{
 * @ingroup  nrf_bootloader
 */

#ifndef NRF_BOOTLOADER_DFU_TIMERS_H__
#define NRF_BOOTLOADER_DFU_TIMERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**@brief Handler called on timeout of a timer requested by the watchdog.
 */
typedef void (*nrf_bootloader_dfu_timeout_callback_t)(void);


/**@brief Function for restarting the inactivity timer.
 *
 * @note Calling this function cancels any previous calls to this function.
 *
 * @param[in]  timeout_ms  The number of milliseconds until reset if not restarted.
 *                         If 0 is passed, the timer will be stopped and not restarted.
 * @param[in]  callback    Function to be called on timeout.
 */
void nrf_bootloader_dfu_inactivity_timer_restart(uint32_t timeout_ms, nrf_bootloader_dfu_timeout_callback_t callback);


/**@brief Function for initializing and starting a repeated timer for feeding the watchdog.
 *
 * @param[in] timeout_ms Timer period.
 * @param[in] callback   Function called on every timeout.
 */
void nrf_bootloader_wdt_feed_timer_start(uint32_t timeout_ms, nrf_bootloader_dfu_timeout_callback_t callback);


#ifdef __cplusplus
}
#endif

#endif // NRF_BOOTLOADER_DFU_TIMERS_H__

/** @} */
