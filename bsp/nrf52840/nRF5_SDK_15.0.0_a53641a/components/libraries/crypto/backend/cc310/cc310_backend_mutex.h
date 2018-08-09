/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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

#ifndef CC310_BACKEND_MUTEX_H__
#define CC310_BACKEND_MUTEX_H__

/** @file
 *
 * @defgroup nrf_crypto_cc310_backend_mutex nrf_crypto CC310 backend mutex.
 * @{
 * @ingroup nrf_crypto_cc310_backend
 *
 * @brief Mutex control for the nrf_crypto CC310 backend.
 */

#include "sdk_config.h"
#include "nrf_mtx.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

#ifdef __cplusplus
extern "C" {
#endif

extern nrf_mtx_t g_cc310_mutex;

__STATIC_INLINE void cc310_backend_mutex_init(void);
__STATIC_INLINE bool cc310_backend_mutex_trylock(void);
__STATIC_INLINE void cc310_backend_mutex_unlock(void);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
/**@internal @brief Function initializing CC310 mutex.
 *
 *  This function _must_ be called before other mutex operations.
 */
__STATIC_INLINE void cc310_backend_mutex_init(void)
{
    nrf_mtx_init(&g_cc310_mutex);
}

/**@internal @brief Function try to lock a CC310 mutex.
 *
 * @return true if lock was acquired, false if not.
 */
__STATIC_INLINE bool cc310_backend_mutex_trylock(void)
{
    return nrf_mtx_trylock(&g_cc310_mutex);
}


/**@internal @brief Unlock a CC310 mutex.
 *
 * This function _must_ only be called when holding the lock. Unlocking a mutex which you do not
 * hold will give undefined behavior.
 *
 */
__STATIC_INLINE void cc310_backend_mutex_unlock(void)
{
    nrf_mtx_unlock(&g_cc310_mutex);
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

/** @} */

#endif // CC310_BACKEND_MUTEX_H__

