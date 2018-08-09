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

#ifndef NRF_DRV_COMP_H__
#define NRF_DRV_COMP_H__

#include <nrfx_comp.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_comp COMP driver - legacy layer
 * @{
 * @ingroup  nrf_comp
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_comp_config_t  nrf_drv_comp_config_t;

/** @brief Macro for forwarding the new implementation. */
#define VOLTAGE_THRESHOLD_TO_INT                NRFX_VOLTAGE_THRESHOLD_TO_INT
/** @brief Macro for forwarding the new implementation. */
#define COMP_CONFIG_TH                          NRFX_COMP_CONFIG_TH
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_DEFAULT_CONFIG             NRFX_COMP_DEFAULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define comp_events_handler_t                   nrfx_comp_event_handler_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_SHORT_STOP_AFTER_CROSS_EVT NRFX_COMP_SHORT_STOP_AFTER_CROSS_EVT
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_SHORT_STOP_AFTER_UP_EVT    NRFX_COMP_SHORT_STOP_AFTER_UP_EVT
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_SHORT_STOP_AFTER_DOWN_EVT  NRFX_COMP_SHORT_STOP_AFTER_DOWN_EVT
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_short_mask_t               nrfx_comp_short_mask_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_EVT_EN_CROSS_MASK          NRFX_COMP_EVT_EN_CROSS_MASK
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_EVT_EN_UP_MASK             NRFX_COMP_EVT_EN_UP_MASK
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_EVT_EN_DOWN_MASK           NRFX_COMP_EVT_EN_DOWN_MASK
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_COMP_EVT_EN_READY_MASK          NRFX_COMP_EVT_EN_READY_MASK
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_evt_en_mask_t              nrfx_comp_evt_en_mask_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_uninit                     nrfx_comp_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_pin_select                 nrfx_comp_pin_select
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_start                      nrfx_comp_start
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_stop                       nrfx_comp_stop
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_sample                     nrfx_comp_sample

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_task_address_get           nrfx_comp_task_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_comp_event_address_get          nrfx_comp_event_address_get

/**
 * @brief Function for initializing the COMP driver.
 *
 * This function initializes the COMP driver, but does not enable the peripheral or any interrupts.
 * To start the driver, call the function @ref nrf_drv_comp_start() after initialization.
 *
 * If no configuration structure is provided, the driver is initialized with the default settings.
 *
 * @param[in] p_config      Pointer to the structure with initial configuration.
 * @param[in] event_handler Handler function.
 *
 * @retval NRF_ERROR_INVALID_PARAM If the configuration is invalid.
 * @retval NRF_ERROR_INVALID_STATE If the driver has already been initialized.
 * @retval NRF_ERROR_BUSY          If the LPCOMP driver is initialized.
 */
__STATIC_INLINE ret_code_t nrf_drv_comp_init(nrf_drv_comp_config_t const * p_config,
                                             comp_events_handler_t         event_handler)
{
    if (p_config == NULL)
    {
        static nrfx_comp_config_t const default_config = NRFX_COMP_DEFAULT_CONFIG(NRF_COMP_INPUT_0);
        p_config = &default_config;
    }
    return nrfx_comp_init(p_config, event_handler);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_COMP_H__
