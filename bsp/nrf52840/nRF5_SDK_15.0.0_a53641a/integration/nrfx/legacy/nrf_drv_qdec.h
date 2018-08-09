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

#ifndef NRF_DRV_QDEC_H__
#define NRF_DRV_QDEC_H__

#include <nrfx_qdec.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_qdec QDEC driver - legacy layer
 * @{
 * @ingroup  nrf_qdec
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_qdec_config_t          nrf_drv_qdec_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_qdec_sample_data_evt_t nrf_drv_qdec_sample_data_evt_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_qdec_report_data_evt_t nrf_drv_qdec_report_data_evt_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_qdec_event_t           nrf_drv_qdec_event_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_QDEC_DEFAULT_CONFIG NRFX_QDEC_DEFAULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define qdec_event_handler_t            nrfx_qdec_event_handler_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qdec_uninit             nrfx_qdec_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qdec_enable             nrfx_qdec_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qdec_disable            nrfx_qdec_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qdec_accumulators_read  nrfx_qdec_accumulators_read

/**
 * @brief Function for initializing QDEC.
 *
 * @param[in] p_config      Pointer to the structure with initial configuration.
 * @param[in] event_handler Event handler function.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_PARAM If invalid parameters were supplied.
 * @retval NRF_ERROR_INVALID_STATE If QDEC was already initialized.
 */
__STATIC_INLINE ret_code_t nrf_drv_qdec_init(nrf_drv_qdec_config_t const * p_config,
                                             qdec_event_handler_t          event_handler)
{
    if (p_config == NULL)
    {
        static nrf_drv_qdec_config_t const default_config = NRFX_QDEC_DEFAULT_CONFIG;
        p_config = &default_config;
    }
    return nrfx_qdec_init(p_config, event_handler);
}

/**
 * @brief Function for returning the address of a specific timer task.
 *
 * @param[in]  task       QDEC task.
 * @param[out] p_task     Task address.
 */
void nrf_drv_qdec_task_address_get(nrf_qdec_task_t task, uint32_t * p_task)
{
    *p_task = nrfx_qdec_task_address_get(task);
}

/**
 * @brief Function for returning the address of a specific timer event.
 *
 * @param[in]  event       QDEC event.
 * @param[out] p_event     Event address.
 */
void nrf_drv_qdec_event_address_get(nrf_qdec_event_t event, uint32_t * p_event)
{
    *p_event = nrfx_qdec_event_address_get(event);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_QDEC_H__
