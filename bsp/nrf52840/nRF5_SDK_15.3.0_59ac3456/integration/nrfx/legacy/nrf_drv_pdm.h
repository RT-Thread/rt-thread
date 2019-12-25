/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_PDM_H__
#define NRF_DRV_PDM_H__

#include <nrfx_pdm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_pdm PDM driver - legacy layer
 * @{
 * @ingroup  nrf_pdm
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_pdm_config_t   nrf_drv_pdm_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_pdm_evt_t      nrf_drv_pdm_evt_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_PDM_MAX_BUFFER_SIZE         NRFX_PDM_MAX_BUFFER_SIZE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_PDM_DEFAULT_CONFIG      NRFX_PDM_DEFAULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define PDM_NO_ERROR                    NRFX_PDM_NO_ERROR
/** @brief Macro for forwarding the new implementation. */
#define PDM_ERROR_OVERFLOW              NRFX_PDM_ERROR_OVERFLOW
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_error_t             nrfx_pdm_error_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_event_handler_t     nrfx_pdm_event_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_uninit              nrfx_pdm_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_task_address_get    nrfx_pdm_task_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_enable_check        nrfx_pdm_enable_check
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_start               nrfx_pdm_start
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_stop                nrfx_pdm_stop
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_pdm_buffer_set          nrfx_pdm_buffer_set

/**
 * @brief Function for initializing the PDM interface.
 *
 * @param[in] p_config      Pointer to the structure with initial configuration. Cannot be NULL.
 * @param[in] event_handler Event handler provided by the user. Cannot be NULL.
 *
 * @retval NRF_SUCCESS If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver is already initialized.
 * @retval NRF_ERROR_INVALID_PARAM If invalid parameters were specified.
 */
__STATIC_INLINE ret_code_t nrf_drv_pdm_init(nrf_drv_pdm_config_t const * p_config,
                                            nrf_drv_pdm_event_handler_t  event_handler)
{
    if (p_config == NULL)
    {
        return NRFX_ERROR_INVALID_PARAM;
    }
    return nrfx_pdm_init(p_config, event_handler);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_PDM_H__
