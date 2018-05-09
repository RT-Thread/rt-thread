/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
 * @brief Module to manage dynamically allocated memory used by nrf_crypto APIs
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

 #ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

/** @brief Function to initialize the nrf_crypto memory module.
 *
 * @retval NRF_SUCCESS     The nrf_crypto memory manager initialized successfully.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_mem_init(void);


/**@brief Function to allocate memory for use by the nrf_crypto API.
 *
 * @param[in]       size        Length in bytes to allocate
 * @param[in,out]   p_result    Pointer to value length structure to hold information about the allocated memory.
 *
 * @retval  NRF_SUCCESS     The memory was allocated successfully.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_mem_allocate(uint32_t size, nrf_value_length_t * p_result);


/**@brief Function to free memory to use by nrf_crypto API.
 *
 * @param[in]   p_mem       Pointer to value length structure holding information about allocated memory to free
 *
 * @retval NRF_SUCCESS      The memory was freed successfully.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_mem_free(nrf_value_length_t * p_mem);

#ifdef __cplusplus
}
#endif

/**@} */

 #endif // NRF_CRYPTO_MEM_H__
