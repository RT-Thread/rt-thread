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

#ifndef NRF_DRV_PWM_H__
#define NRF_DRV_PWM_H__

#include <nrfx_pwm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_pwm PWM driver - legacy layer
 * @{
 * @ingroup  nrf_pwm
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_pwm_t          nrf_drv_pwm_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_pwm_config_t   nrf_drv_pwm_config_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_INSTANCE                    NRFX_PWM_INSTANCE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_PIN_NOT_USED                NRFX_PWM_PIN_NOT_USED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_PIN_INVERTED                NRFX_PWM_PIN_INVERTED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_DEFAULT_CONFIG              NRFX_PWM_DEFAULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_FLAG_STOP                   NRFX_PWM_FLAG_STOP
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_FLAG_LOOP                   NRFX_PWM_FLAG_LOOP
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_FLAG_SIGNAL_END_SEQ0        NRFX_PWM_FLAG_SIGNAL_END_SEQ0
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_FLAG_SIGNAL_END_SEQ1        NRFX_PWM_FLAG_SIGNAL_END_SEQ1
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_FLAG_NO_EVT_FINISHED        NRFX_PWM_FLAG_NO_EVT_FINISHED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_FLAG_START_VIA_TASK         NRFX_PWM_FLAG_START_VIA_TASK
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_flag_t                      nrfx_pwm_flag_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_EVT_FINISHED                NRFX_PWM_EVT_FINISHED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_EVT_END_SEQ0                NRFX_PWM_EVT_END_SEQ0
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_EVT_END_SEQ1                NRFX_PWM_EVT_END_SEQ1
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PWM_EVT_STOPPED                 NRFX_PWM_EVT_STOPPED
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_evt_type_t                  nrfx_pwm_evt_type_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_handler_t                   nrfx_pwm_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_init                        nrfx_pwm_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_uninit                      nrfx_pwm_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_simple_playback             nrfx_pwm_simple_playback
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_complex_playback            nrfx_pwm_complex_playback
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_step                        nrfx_pwm_step
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_stop                        nrfx_pwm_stop
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_is_stopped                  nrfx_pwm_is_stopped
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_sequence_update             nrfx_pwm_sequence_update
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_sequence_values_update      nrfx_pwm_sequence_values_update
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_sequence_length_update      nrfx_pwm_sequence_length_update
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_sequence_repeats_update     nrfx_pwm_sequence_repeats_update
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_sequence_end_delay_update   nrfx_pwm_sequence_end_delay_update

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_task_address_get            nrfx_pwm_task_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pwm_event_address_get           nrfx_pwm_event_address_get

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_PWM_H__
