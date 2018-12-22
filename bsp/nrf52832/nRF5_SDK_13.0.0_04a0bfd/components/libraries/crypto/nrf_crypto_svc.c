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
#include "nrf_svc_function.h"
#include "nrf_error.h"
#include "sdk_common.h"

/* use direct calls */
#define SVC_INTERFACE_CALL_AS_NORMAL_FUNCTION
#include "nrf_crypto.h"

#ifndef NRF51

SVC_REGISTER_FUNCTION(const nrf_svc_func_reg_t nrf_crypto_svci_init) =
{
    .svc_num = NRF_SVCI_SVC_NUM,
    .svci_num = NRF_CRYPTO_SVCI_INIT,
    .func_ptr = (nrf_svc_func_t)&nrf_crypto_init
};

SVC_REGISTER_FUNCTION(const nrf_svc_func_reg_t nrf_crypto_svci_public_key_compute) =
{
    .svc_num = NRF_SVCI_SVC_NUM,
    .svci_num = NRF_CRYPTO_SVCI_PUBLIC_KEY_COMPUTE,
    .func_ptr = (nrf_svc_func_t)&nrf_crypto_public_key_compute
};

SVC_REGISTER_FUNCTION(const nrf_svc_func_reg_t nrf_crypto_svci_shared_secret_compute) =
{
    .svc_num = NRF_SVCI_SVC_NUM,
    .svci_num = NRF_CRYPTO_SVCI_SHARED_SECRET_COMPUTE,
    .func_ptr = (nrf_svc_func_t)&nrf_crypto_shared_secret_compute
};

SVC_REGISTER_FUNCTION(const nrf_svc_func_reg_t nrf_crypto_svci_sign) =
{
    .svc_num = NRF_SVCI_SVC_NUM,
    .svci_num = NRF_CRYPTO_SVCI_SIGN,
    .func_ptr = (nrf_svc_func_t)&nrf_crypto_sign
};

#endif

SVC_REGISTER_FUNCTION(const nrf_svc_func_reg_t nrf_crypto_svci_verify) =
{
    .svc_num = NRF_SVCI_SVC_NUM,
    .svci_num = NRF_CRYPTO_SVCI_VERIFY,
    .func_ptr = (nrf_svc_func_t)&nrf_crypto_verify
};

SVC_REGISTER_FUNCTION(const nrf_svc_func_reg_t nrf_crypto_svci_hash_compute) =
{
    .svc_num = NRF_SVCI_SVC_NUM,
    .svci_num = NRF_CRYPTO_SVCI_HASH_COMPUTE,
    .func_ptr = &nrf_crypto_hash_compute
};
