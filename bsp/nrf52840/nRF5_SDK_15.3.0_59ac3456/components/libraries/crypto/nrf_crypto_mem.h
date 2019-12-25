/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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

#ifndef NRF_CRYPTO_MEM_H__
#define NRF_CRYPTO_MEM_H__

/** @file
 *
 * @defgroup nrf_crypto_mem Dynamic memory management module
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Module to manage dynamically allocated memory used by nrf_crypto APIs.
 *
 * @ref NRF_CRYPTO_ALLOCATOR definition is used to configure this module.
 */

#include <stdint.h>
#include "sdk_common.h"
#include "sdk_config.h"
#include "nrf_crypto_types.h"
#include "sdk_alloca.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __SDK_DOXYGEN__


#define NRF_CRYPTO_ALLOCATOR_DEFAULT    0  /**< @internal @brief Value for NRF_CRYPTO_ALLOCATOR to select default memory allocation. */
#define NRF_CRYPTO_ALLOCATOR_USER       1  /**< @internal @brief Value for NRF_CRYPTO_ALLOCATOR to select user defined memory allocation. */
#define NRF_CRYPTO_ALLOCATOR_ALLOCA     2  /**< @internal @brief Value for NRF_CRYPTO_ALLOCATOR to select stack based memory allocation. */
#define NRF_CRYPTO_ALLOCATOR_MALLOC     3  /**< @internal @brief Value for NRF_CRYPTO_ALLOCATOR to select stdlib's dynamic memory allocation. */
#define NRF_CRYPTO_ALLOCATOR_NRF_MALLOC 4  /**< @internal @brief Value for NRF_CRYPTO_ALLOCATOR to select mem_manager for memory allocation. */


#ifndef NRF_CRYPTO_ALLOCATOR
#define NRF_CRYPTO_ALLOCATOR NRF_CRYPTO_ALLOCATOR_DEFAULT
#endif


#if NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_DEFAULT
#undef NRF_CRYPTO_ALLOCATOR
#if SDK_ALLOCA_DEFINED && !NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)
#define NRF_CRYPTO_ALLOCATOR NRF_CRYPTO_ALLOCATOR_ALLOCA
#else
#define NRF_CRYPTO_ALLOCATOR NRF_CRYPTO_ALLOCATOR_NRF_MALLOC
#endif
#endif


#if NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_USER

#include "nrf_crypto_allocator.h"
#ifndef NRF_CRYPTO_ALLOC
#error "User defined allocator for nrf_crypto does not define NRF_CRYPTO_ALLOC"
#endif
#ifndef NRF_CRYPTO_FREE
#error "User defined allocator for nrf_crypto does not define NRF_CRYPTO_FREE"
#endif
#ifndef NRF_CRYPTO_ALLOC_ON_STACK
#error "User defined allocator for nrf_crypto does not define NRF_CRYPTO_ALLOC_ON_STACK"
#endif

#elif NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_ALLOCA

#if !SDK_ALLOCA_DEFINED
#warning "Stack based allocation is selected, but alloca() is not supported on this platform"
#endif
#define NRF_CRYPTO_ALLOC(size)    (alloca((size_t)(size)))
#define NRF_CRYPTO_FREE(p_buffer) // Empty
#define NRF_CRYPTO_ALLOC_ON_STACK 1

#elif NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_MALLOC

#include "stdlib.h"
#define NRF_CRYPTO_ALLOC(size)    (malloc((size_t)(size)))
#define NRF_CRYPTO_FREE(p_buffer) (free((void *)(p_buffer)))
#define NRF_CRYPTO_ALLOC_ON_STACK 0

#elif NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_NRF_MALLOC

#include "mem_manager.h"
#define NRF_CRYPTO_ALLOC(size)    (nrf_malloc((uint32_t)(size)))
#define NRF_CRYPTO_FREE(p_buffer) (nrf_free((void *)(p_buffer)))
#define NRF_CRYPTO_ALLOC_ON_STACK 0

#else

#error "Invalid NRF_CRYPTO_ALLOCATOR configuration value"

#endif


#else // __SDK_DOXYGEN__


/** @brief Defines memory allocation function for nrf_crypto.
 *
 *  This macro is used internally by nrf_crypto library to allocate temporary memory. It is not
 *  intended to be used outside nrf_crypto library. How memory is actually allocated is configured
 *  by @ref NRF_CRYPTO_ALLOCATOR definition.
 *
 *  If user macros are selected by @ref NRF_CRYPTO_ALLOCATOR then this macro have to be defined by
 *  the user in "nrf_crypto_allocator.h" file. The file will be included into "nrf_crypto_mem.h".
 *
 *  If @ref NRF_CRYPTO_ALLOC_ON_STACK is 1 then this function will allocate data on stack,
 *  so make sure that returned pointer is not used outside the caller function.
 *
 *  @param size      Number of bytes to allocate.
 *  @returns         Pointer to newly allocated memory or NULL on error.
 */
#define NRF_CRYPTO_ALLOC(size)

/** @brief Defines memory deallocation function for nrf_crypto.
 *
 *  This macro is used internally by nrf_crypto library to deallocate temporary memory. It is not
 *  intended to be used outside nrf_crypto library.
 *
 *  If user macros are selected by @ref NRF_CRYPTO_ALLOCATOR then this macro have to be defined by
 *  the user in "nrf_crypto_allocator.h" file. The file will be included into "nrf_crypto_mem.h".
 *
 *  @param p_buffer  Pointer to memory buffer for deallocation.
 */
#define NRF_CRYPTO_FREE(p_buffer)

/** @brief Contains 1 if memory allocated by @ref NRF_CRYPTO_ALLOC is on stack or 0 otherwise.
 *
 *  This definition is used internally by nrf_crypto library. It is not intended to be used outside
 *  nrf_crypto library.
 *
 *  If user macros are selected by @ref NRF_CRYPTO_ALLOCATOR then this macro have to be defined by
 *  the user in "nrf_crypto_allocator.h" file. The file will be included into "nrf_crypto_mem.h".
 */
#define NRF_CRYPTO_ALLOC_ON_STACK


#endif // __SDK_DOXYGEN__

#ifdef __cplusplus
}
#endif

/**@} */

 #endif // NRF_CRYPTO_MEM_H__
