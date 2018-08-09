/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef HAL_NRF52_RTC_H_INCLUDED
#define HAL_NRF52_RTC_H_INCLUDED

#include "nordic_common.h"
#include "nrf_drv_config.h"
#include "nrf_drv_common.h"
#include "nrf_drv_rtc.h"
#include "nrf_rtc.h"

/**
 * @defgroup hal_nrf52_rtc HAL RTC
 * @ingroup hal_15_4_nrf52
 * @{
 */

// RTC counter bitlenght
#define LAGEST_PRESCALER_VALUE 4096
// RTC counter bitlenght
#define RTC_CNT_BITLENGHT      24
// Longest sleep time, ms
#define LONGEST_SLEEP_TIME     ((( 1UL << RTC_CNT_BITLENGHT )  \
                                /(RTC_INPUT_FREQ/LAGEST_PRESCALER_VALUE)) * 1000UL )

// Shortest sleep time, ms
#define SHORTEST_SLEEP_TIME    1

/**@brief Function for initialize low frequency clock
 */
void rtc_lfclk_start(void);


/** @brief Function initialization and configuration of RTC driver instance.
 *
 *  @param[in]   sleep_time_ms    after this time compare event will be triggered
 */
void rtc_start(uint32_t sleep_time_ms);

/** @brief Stop RTC
 */
void rtc_stop(void);

/** @brief Get RTC counter
 *
 *  @retval  uint32_t  Contents of RTC counter register.
 */
uint32_t rtc_cnt_get(void);

/** @brief Get time elapsed since cnt_ticks
 *
 *   @param[in]   cnt_ticks    Number of rtc-ticks
 *
 *   @retval      uint32_t     Time since cnt_ticks, ms
 */
uint64_t get_rtc_time_since(uint32_t cnt_ticks);

/** @brief Check if rtc compare interrupt  was triggered after calling
 *         rtc_start function
 *
 *   @retval     bool     true  -  compare interrupt  was triggered
 *                        false -  it wasn't
 */
bool  is_rtc_comp_irq_triggerd(void);

/** @} */

#endif /* HAL_NRF52_RTC_H_INCLUDED */
