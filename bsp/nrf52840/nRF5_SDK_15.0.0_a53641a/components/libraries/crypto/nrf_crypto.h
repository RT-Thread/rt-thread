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

#ifndef NRF_CRYPTO_H__
#define NRF_CRYPTO_H__

/**
 * @defgroup nrf_crypto Cryptography library
 * @ingroup app_common
 * @{
 *
 * @brief   Cryptography library (nrf_crypto).
 *
 * @details The cryptography library provides cryptographic functionality in a portable way.
 *
 * @note The functions in this API can run in software or hardware, depending on the supported features of your SoC and the configuration of nrf_crypto backend in the application.
 * See @ref lib_crypto_config for details on changing the nrf_crypto backend.
 *
 * @}
 *
 */
 


#include <stdint.h>
#include "nrf_crypto_init.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_hash.h"
#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_aes.h"
#include "nrf_crypto_aead.h"
#include "nrf_crypto_hmac.h"
#include "nrf_crypto_hkdf.h"


#endif // NRF_CRYPTO_H__
