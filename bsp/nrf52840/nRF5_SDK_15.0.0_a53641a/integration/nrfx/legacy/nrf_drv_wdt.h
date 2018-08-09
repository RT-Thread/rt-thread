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

#ifndef NRF_DRV_WDT_H__
#define NRF_DRV_WDT_H__

#include <nrfx_wdt.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_wdt WDT driver - legacy layer
 * @{
 * @ingroup  nrf_wdt
 *
 * @brief    A layer providing compatibility with former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_wdt_config_t nrf_drv_wdt_config_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_WDT_DEAFULT_CONFIG  NRFX_WDT_DEAFULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define nrf_wdt_event_handler_t     nrfx_wdt_event_handler_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_channel_id      nrfx_wdt_channel_id

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_channel_alloc   nrfx_wdt_channel_alloc
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_enable          nrfx_wdt_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_feed            nrfx_wdt_feed
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_channel_feed    nrfx_wdt_channel_feed

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_ppi_task_addr   nrfx_wdt_ppi_task_addr
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_wdt_ppi_event_addr  nrfx_wdt_ppi_event_addr

/**
 * @brief This function initializes watchdog.
 *
 * @param[in] p_config          Pointer to the structure with initial configuration. Default
 *                              configuration used if NULL.
 * @param[in] wdt_event_handler Specifies event handler provided by user.
 *
 * @note Function asserts if wdt_event_handler is NULL.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
__STATIC_INLINE ret_code_t nrf_drv_wdt_init(nrf_drv_wdt_config_t const * p_config,
                                            nrf_wdt_event_handler_t      wdt_event_handler)
{
    if (p_config == NULL)
    {
        static const nrfx_wdt_config_t default_config = NRFX_WDT_DEAFULT_CONFIG;
        p_config = &default_config;
    }
    return nrfx_wdt_init(p_config, wdt_event_handler);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_WDT_H__
