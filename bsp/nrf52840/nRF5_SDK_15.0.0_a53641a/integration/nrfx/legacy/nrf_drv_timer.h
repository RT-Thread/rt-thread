/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_TIMER_H__
#define NRF_DRV_TIMER_H__

#include <nrfx_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_timer TIMER driver - legacy layer
 * @{
 * @ingroup  nrf_timer
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_timer_t        nrf_drv_timer_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_timer_config_t nrf_drv_timer_config_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TIMER_INSTANCE                   NRFX_TIMER_INSTANCE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TIMER_DEFAULT_CONFIG             NRFX_TIMER_DEFAULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define nrf_timer_event_handler_t                nrfx_timer_event_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_init                       nrfx_timer_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_uninit                     nrfx_timer_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_enable                     nrfx_timer_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_disable                    nrfx_timer_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_is_enabled                 nrfx_timer_is_enabled
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_pause                      nrfx_timer_pause
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_resume                     nrfx_timer_resume
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_clear                      nrfx_timer_clear
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_increment                  nrfx_timer_increment
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_capture                    nrfx_timer_capture
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_capture_get                nrfx_timer_capture_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_compare                    nrfx_timer_compare
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_extended_compare           nrfx_timer_extended_compare
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_us_to_ticks                nrfx_timer_us_to_ticks
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_ms_to_ticks                nrfx_timer_ms_to_ticks
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_compare_int_enable         nrfx_timer_compare_int_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_compare_int_disable        nrfx_timer_compare_int_disable

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_task_address_get           nrfx_timer_task_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_capture_task_address_get   nrfx_timer_capture_task_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_event_address_get          nrfx_timer_event_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_timer_compare_event_address_get  nrfx_timer_compare_event_address_get

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_TIMER_H__
