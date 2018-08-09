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

#ifndef NRF_DRV_SAADC_H__
#define NRF_DRV_SAADC_H__

#include <nrfx_saadc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_saadc SAADC driver - legacy layer
 * @{
 * @ingroup  nrf_saadc
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_saadc_config_t nrf_drv_saadc_config_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_EVT_DONE          NRFX_SAADC_EVT_DONE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_EVT_LIMIT         NRFX_SAADC_EVT_LIMIT
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_EVT_CALIBRATEDONE NRFX_SAADC_EVT_CALIBRATEDONE
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_evt_type_t        nrfx_saadc_evt_type_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_done_evt_t        nrfx_saadc_done_evt_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_limit_evt_t       nrfx_saadc_limit_evt_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_evt_t             nrfx_saadc_evt_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_event_handler_t   nrfx_saadc_event_handler_t

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_LIMITH_DISABLED   NRFX_SAADC_LIMITH_DISABLED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_LIMITL_DISABLED   NRFX_SAADC_LIMITL_DISABLED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_DEFAULT_CONFIG    NRFX_SAADC_DEFAULT_CONFIG
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE \
        NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL \
        NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_uninit            nrfx_saadc_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_channel_init      nrfx_saadc_channel_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_channel_uninit    nrfx_saadc_channel_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_sample            nrfx_saadc_sample
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_sample_convert    nrfx_saadc_sample_convert
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_buffer_convert    nrfx_saadc_buffer_convert
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_calibrate_offset  nrfx_saadc_calibrate_offset
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_is_busy           nrfx_saadc_is_busy
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_abort             nrfx_saadc_abort
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_limits_set        nrfx_saadc_limits_set

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_saadc_sample_task_get   nrfx_saadc_sample_task_get

/**
 * @brief Function for initializing the SAADC.
 *
 * @param[in] p_config      Pointer to the structure with initial configuration.
 *                          If NULL, the default one is used.
 * @param[in] event_handler Event handler provided by the user.
 *
 * @retval NRF_SUCCESS If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver is already initialized.
 * @retval NRF_ERROR_INVALID_PARAM If event_handler is NULL.
 */
__STATIC_INLINE ret_code_t nrf_drv_saadc_init(nrf_drv_saadc_config_t const * p_config,
                                              nrf_drv_saadc_event_handler_t  event_handler)
{
    if (p_config == NULL)
    {
        static const nrfx_saadc_config_t default_config = NRFX_SAADC_DEFAULT_CONFIG;
        p_config = &default_config;
    }
    return nrfx_saadc_init(p_config, event_handler);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_SAADC_H__
