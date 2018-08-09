/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup sdk_nrf_svci_async_handler Asynchronous Supervisor handler functions
 * @{
 * @ingroup app_common
 *
 * @brief Macros to create Asynchronous Supervisor interface handler functions.
 */

#ifndef NRF_SVCI_ASYNC_HANDLER_H__
#define NRF_SVCI_ASYNC_HANDLER_H__

#include "nrf_svc_function.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Macro for creating a registration for an async handler for the SVCI interface
 *
 * @details     Calling this macro will register a SVCI function handler using @ref
 *              NRF_SVCI_FUNCTION_REGISTER
 *
 * @note This macro must be invoked from a source file as it declares static functions
 *       to be implemented and because it creates a @ref lib_section_vars registration to
 *       SVCI interface which is intended to be unique.
 *
 * @param[in]   svci_num    SVC indirect number.
 * @param[in]   name        Name of the async function.
 * @param[in]   param_type  Type of the param to send when running the async interface.
 * @param[in]   state_type  Type of the state to be called together with sys_event.
 *
 * @retval Static declarations to handler functions to be implemented in the form NAME_handler
 *         NAME_on_call, and NAME_on_sys_event.
 */
#define NRF_SVCI_ASYNC_HANDLER_CREATE(svci_num,                                 \
                                      name,                                     \
                                      param_type,                               \
                                      state_type)                               \
                                                                                \
static uint32_t name ## _handler(name ## _svci_async_t * p_async);              \
static uint32_t name ## _on_call(param_type * p_param, state_type * p_state);   \
static uint32_t name ## _on_sys_evt(uint32_t sys_event, state_type * p_state);  \
                                                                                \
NRF_SVCI_FUNCTION_REGISTER(svci_num, name ## _var, name ## _handler)


#ifdef __cplusplus
}
#endif

#endif // NRF_SVCI_ASYNC_HANDLER_H__

/** @} */
