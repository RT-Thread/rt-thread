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

#ifndef NRF_DRV_I2S_H__
#define NRF_DRV_I2S_H__

#include <nrfx_i2s.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_i2s I2S driver - legacy layer
 * @{
 * @ingroup  nrf_i2s
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_i2s_config_t   nrf_drv_i2s_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_i2s_buffers_t  nrf_drv_i2s_buffers_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_I2S_PIN_NOT_USED               NRFX_I2S_PIN_NOT_USED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_I2S_FLAG_SYNCHRONIZED_MODE     NRFX_I2S_FLAG_SYNCHRONIZED_MODE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_I2S_DEFAULT_CONFIG             NRFX_I2S_DEFAULT_CONFIG
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_I2S_STATUS_NEXT_BUFFERS_NEEDED NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_i2s_data_handler_t             nrfx_i2s_data_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_i2s_uninit                     nrfx_i2s_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_i2s_start                      nrfx_i2s_start
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_i2s_next_buffers_set           nrfx_i2s_next_buffers_set
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_i2s_stop                       nrfx_i2s_stop

/**
 * @brief Function for initializing the I2S driver.
 *
 * @param[in] p_config Pointer to the structure with initial configuration.
 *                     If NULL, the default configuration is used.
 * @param[in] handler  Data handler provided by the user. Must not be NULL.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver was already initialized.
 * @retval NRF_ERROR_INVALID_PARAM If the requested combination of configuration
  *                                 options is not allowed by the I2S peripheral.
 */
__STATIC_INLINE ret_code_t nrf_drv_i2s_init(nrf_drv_i2s_config_t const * p_config,
                                            nrf_drv_i2s_data_handler_t   handler)
{
    if (p_config == NULL)
    {
        static nrfx_i2s_config_t const default_config = NRFX_I2S_DEFAULT_CONFIG;
        p_config = &default_config;
    }
    return nrfx_i2s_init(p_config, handler);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_I2S_H__
