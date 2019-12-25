/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_SYSTICK_H__
#define NRF_DRV_SYSTICK_H__

#include <nrfx_systick.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup   nrf_drv_systick ARM(R) SysTick driver - legacy layer
 * @{
 * @ingroup    nrf_systick
 *
 * @brief      Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_systick_state_t nrf_drv_systick_state_t;

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_systick_init        nrfx_systick_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_systick_get         nrfx_systick_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_systick_test        nrfx_systick_test
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_systick_delay_ticks nrfx_systick_delay_ticks
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_systick_delay_us    nrfx_systick_delay_us
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_systick_delay_ms    nrfx_systick_delay_ms

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_SYSTICK_H__
