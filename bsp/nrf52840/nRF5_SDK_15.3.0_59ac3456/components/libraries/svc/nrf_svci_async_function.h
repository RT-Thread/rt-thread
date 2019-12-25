/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
 * @defgroup sdk_nrf_svci_async_function Asynchronous Supervisor function interface
 * @{
 * @ingroup app_common
 *
 * @brief Macros to create Asynchronous Supervisor interface functions.
 */

#ifndef NRF_SVC_ASYNC_FUNCTION_H__
#define NRF_SVC_ASYNC_FUNCTION_H__

#include "nrf_svci.h"
#include "nrf_svci_async_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Macro for creating type definition for SVCI interface init function.
 *
 * @warning     Do not call this macro directly! Use @ref NRF_SVCI_ASYNC_FUNC_DECLARE instead.
 *
 * @param[in]   name        Name of async request function. Will be appended with _async_fn_t.
 * @param[in]   param_type  Parameter type.
 * @param[in]   state_type  State type.
 *
 * @retval Type definition a named SVCI async init function.
 */
#define NRF_SVCI_ACYNC_FUNC_TYPEDEF(name, param_type, state_type)                       \
typedef uint32_t (* name ## _async_fn_t)(param_type * p_param, state_type * p_state)


/**@brief Macro for creating type definition for SVCI interface event function.
 *
 * @warning     Do not call this macro directly! Use @ref NRF_SVCI_ASYNC_FUNC_DECLARE instead.
 *
 * @details Calling this function with sys-events will report @ref NRF_ERROR_BUSY until
 *          the asynchronous calls is finished, at which time it will report either
 *          NRF_SUCCESS or any another error-message.
 *
 * @param[in]   name        Name of the event function. Will be appended with _event_fn_t
 * @param[in]   state_type  Type parameter for the state.
 *
 * @retval Type definition for a named SVCI async event function.
 */
#define NRF_SVCI_ASYNC_EVENT_FUNC_TYPEDEF(name, state_type)                             \
typedef uint32_t (* name ## _event_fn_t)(uint32_t sys_evt, state_type * p_state)


/**@brief Macro for creating a declaration of a named async function for the SVCI interface.
 *
 * @details     The async interface provides a method to call into a external application
 *              through the SVCI interface without relying on allocated or reserved memory inside the
 *              external application.
 *
 *              This macro declares variables and function types in use by the async SVCI interface.
 *
 * @note        This is intended to be invoked in a header file shared by both the
 *              caller and the recipient (handler).
 *
 * @param[in]   svci_num    SVC indirect number.
 * @param[in]   name        Name of the async function.
 * @param[in]   param_type  Type of the param used for the async interface.
 * @param[in]   state_type  Type of the state used for the async interface.
 *
 * @retval  A type definition of NAME_svc_async_t to be used for async access
 *          through the SVCI interface.
 */
#define NRF_SVCI_ASYNC_FUNC_DECLARE(svci_num,                                           \
                                    name,                                               \
                                    param_type,                                         \
                                    state_type)                                         \
/*lint --e{19} */                                                                       \
NRF_SVCI_ACYNC_FUNC_TYPEDEF(name, param_type, state_type);                              \
NRF_SVCI_ASYNC_EVENT_FUNC_TYPEDEF(name, state_type);                                    \
                                                                                        \
typedef struct                                                                          \
{                                                                                       \
    name ## _async_fn_t     async_func;                                                 \
    name ## _event_fn_t     sys_evt_handler;                                            \
    state_type              state;                                                      \
} name ## _svci_async_t;



//lint -save --e{10, 19, 40, 102} -esym(526, *_init) -esym(628, *_init)

/**@brief Macro for defining a named SVCI async interface.
 *
 * @details     The async interface provides a method to call into an external application
 *              through the SVCI interface without relying on allocated or reserved memory inside the
 *              external application.
 *
 *              Running this macro creates a defintion of the structure that holds the
 *              information about the async function, the event handler, and the state.
 *
 *              Running this macro also defines convenience functions to the SVCI interface.
 *
 *              The available functions are:
 *              -NAME_init            -    Function to call to set up the async SVCI interface.
 *              -NAME                 -    Function to call the async SVCI interface.
 *              -NAME_on_sys_event    -    Function to report sys events to the async
 *                                         SVCI interface.
 *              -NAME_is_initialized  -    Function to check if the async SVCI interface is
 *                                         initialized and ready to use.
 *
 * @note        Invoking this macro is only possible in a source file as the macro creates
 *              a static variable for the async interface as well as static functions to call
 *              into the async interface.
 *
 * @param[in]   svci_num    SVC indirect number.
 * @param[in]   name        Name of the async function.
 * @param[in]   param_type  Type of the param used for the async interface.
 *
 * @retval Instance of the async SVCI interface and convenience functions for using it.
 */
#define NRF_SVCI_ASYNC_FUNC_DEFINE(svci_num, name, param_type)                                  \
                                                                                                \
SVCI(svci_num, uint32_t, name ## _svci_async_init, name ## _svci_async_t *, p_async);           \
static name ## _svci_async_t name ## _svci_async_def = {0};                                     \
                                                                                                \
static __INLINE uint32_t name ## _init (void)                                                   \
{                                                                                               \
    return name ## _svci_async_init(&name ## _svci_async_def);                                  \
}                                                                                               \
                                                                                                \
static __INLINE uint32_t name(param_type * p_param)                                             \
{                                                                                               \
    return name ## _svci_async_def.async_func(p_param, &name ## _svci_async_def.state);         \
}                                                                                               \
                                                                                                \
static __INLINE uint32_t name ## _on_sys_evt(uint32_t sys_evt)                                  \
{                                                                                               \
    return name ## _svci_async_def.sys_evt_handler(sys_evt, &name ## _svci_async_def.state);    \
}                                                                                               \
                                                                                                \
static __INLINE uint32_t name ## _is_initialized(void)                                          \
{                                                                                               \
    return (name ## _svci_async_def.async_func != NULL  &&                                      \
        name ## _svci_async_def.sys_evt_handler != NULL );                                      \
}

//lint -restore

#ifdef __cplusplus
}
#endif

#endif // NRF_SVC_ASYNC_FUNCTION_H__

/** @} */
