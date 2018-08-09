/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_RTC_H__
#define NRF_DRV_RTC_H__

#include <nrfx_rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_rtc RTC driver - legacy layer
 * @{
 * @ingroup  nrf_rtc
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_rtc_t          nrf_drv_rtc_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_rtc_config_t   nrf_drv_rtc_config_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INSTANCE            NRFX_RTC_INSTANCE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_DEFAULT_CONFIG      NRFX_RTC_DEFAULT_CONFIG
/** @brief Macro for forwarding the new implementation. */
#define RTC_US_TO_TICKS                 NRFX_RTC_US_TO_TICKS

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INT_COMPARE0        NRFX_RTC_INT_COMPARE0
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INT_COMPARE1        NRFX_RTC_INT_COMPARE1
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INT_COMPARE2        NRFX_RTC_INT_COMPARE2
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INT_COMPARE3        NRFX_RTC_INT_COMPARE3
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INT_TICK            NRFX_RTC_INT_TICK
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_RTC_INT_OVERFLOW        NRFX_RTC_INT_OVERFLOW
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_int_type_t          nrfx_rtc_int_type_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_handler_t           nrfx_rtc_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_init                nrfx_rtc_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_uninit              nrfx_rtc_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_enable              nrfx_rtc_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_disable             nrfx_rtc_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_cc_set              nrfx_rtc_cc_set
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_cc_disable          nrfx_rtc_cc_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_tick_enable         nrfx_rtc_tick_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_tick_disable        nrfx_rtc_tick_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_overflow_enable     nrfx_rtc_overflow_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_overflow_disable    nrfx_rtc_overflow_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_max_ticks_get       nrfx_rtc_max_ticks_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_int_disable         nrfx_rtc_int_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_int_enable          nrfx_rtc_int_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_counter_get         nrfx_rtc_counter_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_counter_clear       nrfx_rtc_counter_clear

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_task_address_get    nrfx_rtc_task_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_rtc_event_address_get   nrfx_rtc_event_address_get

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_RTC_H__
