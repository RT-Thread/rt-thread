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
#ifndef NRF_CRYPTO_INIT_H__
#define NRF_CRYPTO_INIT_H__

/** @file
 *
 * @defgroup nrf_crypto_initialization Initialization.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides nrf_crypto initialization related functions.
 */

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "nrf_crypto_types.h"

/**@brief Function for initializing the cryptography library.
 *
 * @retval  NRF_SUCCESS     If initialization was successful.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypt backend.
 */
uint32_t nrf_crypto_init(void);


/**@brief Function for uninitializing the cryptography library.
 *
 * @retval  NRF_SUCCESS         If unititialization was successful.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypt backend.
 */
uint32_t nrf_crypto_uninit(void);


/**@brief Function reporting if nrf_crypto has been initialized.
 *
 * @retval  True    If cryptographic library is initialized.
 * @retval  False   If cryptographic library isn't initialized.
 */
bool nrf_crypto_is_initialized(void);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_INIT_H__
