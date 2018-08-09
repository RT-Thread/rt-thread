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

#ifndef NRF_DRV_SWI_H__
#define NRF_DRV_SWI_H__

#include <nrfx_swi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_swi SWI driver - legacy layer
 * @{
 * @ingroup  nrf_swi_egu
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Macro for forwarding the new implementation. */
#define NRF_SWI_UNALLOCATED     NRFX_SWI_UNALLOCATED
/** @brief Macro for forwarding the new implementation. */
#define SWI_DEFAULT_PRIORITY    NRFX_SWI_DEFAULT_PRIORITY

/** @brief Macro for forwarding the new implementation. */
#define nrf_swi_t           nrfx_swi_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_swi_flags_t     nrfx_swi_flags_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_swi_handler_t   nrfx_swi_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_swi_alloc   nrfx_swi_alloc
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_swi_free    nrfx_swi_free
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_swi_trigger nrfx_swi_trigger

#if NRF_MODULE_ENABLED(EGU) || defined(__SDK_DOXYGEN__)
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_swi_task_trigger_address_get    nrfx_swi_task_trigger_address_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_swi_event_triggered_address_get nrfx_swi_event_triggered_address_get
#endif // NRF_MODULE_ENABLED(EGU) || defined(__SDK_DOXYGEN__)

/**
 * @brief Function for initializing the SWI module.
 *
 * @retval NRF_SUCCESS                          If the module was successfully initialized.
 * @retval NRF_ERROR_MODULE_ALREADY_INITIALIZED If the module has already been initialized.
 */
ret_code_t nrf_drv_swi_init(void);

/**
 * @brief Function for uninitializing the SWI module.
 *
 * This function also frees all SWIs.
 *
 * @retval NRF_SUCCESS             If the module was successfully uninitialized.
 * @retval NRF_ERROR_INVALID_STATE If the module has not been initialized yet.
 */
ret_code_t nrf_drv_swi_uninit(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_SWI_H__
