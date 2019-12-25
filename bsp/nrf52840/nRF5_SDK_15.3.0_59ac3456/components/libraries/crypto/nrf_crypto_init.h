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

#ifndef NRF_CRYPTO_INIT_H__
#define NRF_CRYPTO_INIT_H__

/** @file
 *
 * @defgroup nrf_crypto_initialization Initialization
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Initialization related functions for nrf_crypto .
 *
 * @details @ref lib_crypto is responsible for global initialization of the nrf_crypto
 *          frontend and backends that are enabled in @ref sdk_config.
 */

#include <stdint.h>
#include <stdbool.h>
#include "nrf_section.h"
#include "sdk_errors.h"
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@internal @brief  Macro for registering a nrf_crypto backend for initialization by using
 *                   nrf_section.
 *
 * @details     This macro places a variable in a section named "crypto_data", which
 *              is initialized by @ref nrf_crypto_init.
 *
 * @note    This macro is used internally based on sdk_config.h configurations for nrf_crypto
 */
#define CRYPTO_BACKEND_REGISTER(crypto_var) NRF_SECTION_ITEM_REGISTER(crypto_data, crypto_var)

/**@internal @brief Type definition of function pointer to initialize the nrf_crypto backend.
 *
 * This function type is used internally. See @nrf_crypto_init for documentation.
 */
typedef ret_code_t (*nrf_crypto_backend_init_fn_t)(void);


/**@internal @brief Type definition of function pointer to uninitialize the nrf_crypto backend.
 *
 * This function type is used internally. Please see @nrf_crypto_uninit for documentation.
 */
typedef ret_code_t (*nrf_crypto_backend_uninit_fn_t)(void);



/**@internal @brief Type definition for structure holding the calling interface to
 *                  init, uninit, enable, or disable an nrf_crypto_backend
 *
 * @note    Some backends require no expressive init, uninit, enable, or disable.
 *          In this case, the backend will not use this structure type or only select
 *          to implement
 */
typedef struct
{
    nrf_crypto_backend_init_fn_t      const init_fn;
    nrf_crypto_backend_uninit_fn_t    const uninit_fn;
} nrf_crypto_backend_info_t;


/**@brief Function for initializing nrf_crypto and all registered backends.
 *
 * @details Must always be called before any other @ref nrf_crypto function.
 *
 * @retval  NRF_SUCCESS         The initialization was successful.
 * @retval  NRF_ERROR_INTERNAL  An internal error occured in the nrf_crypt backend init.
 */
ret_code_t nrf_crypto_init(void);


/**@brief Function for uninitializing nrf_crypto and all registered backends.
 *
 * @retval  NRF_SUCCESS         If unititialization was successful.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypt backend init.
 */
ret_code_t nrf_crypto_uninit(void);


/**@brief Function reporting if nrf_crypto has been initialized.
 *
 * @retval  True    If cryptographic library is initialized.
 * @retval  False   If cryptographic library is not initialized.
 */
bool nrf_crypto_is_initialized(void);


/**@brief Function reporting if nrf_crypto is initialized or is in the process of being initialized.
 *
 * @retval  True    If cryptographic library is initializing or already initialized.
 * @retval  False   If cryptographic library is not initialized.
 */
bool nrf_crypto_is_initializing(void);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_INIT_H__
