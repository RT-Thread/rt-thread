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

#include "sdk_common.h"
#include <drivers/nrfx_common.h>
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include <stdbool.h>
#include "crys_aesccm_error.h"
#include "cc310_backend_aes_aead.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_CC310_AES_AEAD)

/**@internal @brief Type declaration of a template suiting all possible context sizes
 *                  for this backend.
 */
typedef struct
{
    nrf_crypto_aead_internal_context_t header;  /**< Common header for context. */
    CRYS_AESCCM_UserContext_t          context;
    uint8_t                            key[16]; /**< Only supported key size by CC310 is 128 bit */
} nrf_crypto_backend_cc310_aes_aead_context_t;

static ret_code_t result_get(CRYSError_t error)
{
    ret_code_t ret_val;

    switch (error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_AESCCM_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NULL;
            break;

        case CRYS_AESCCM_ILLEGAL_KEY_SIZE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_KEY_SIZE;
            break;

        case CRYS_AESCCM_ILLEGAL_TAG_SIZE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_AEAD_MAC_SIZE;
            break;

        case CRYS_AESCCM_ILLEGAL_NONCE_SIZE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_AEAD_NONCE_SIZE;
            break;

        case CRYS_AESCCM_ILLEGAL_PARAMETER_SIZE_ERROR:
        case CRYS_AESCCM_DATA_IN_SIZE_ILLEGAL:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case CRYS_AESCCM_INVALID_KEY_POINTER_ERROR:
        case CRYS_AESCCM_ILLEGAL_PARAMETER_PTR_ERROR:
        case CRYS_AESCCM_DATA_IN_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INPUT_NULL;
            break;

        case CRYS_AESCCM_IS_NOT_SUPPORTED:
        case CRYS_AESCCM_INVALID_ENCRYPT_MODE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        case CRYS_AESCCM_DATA_OUT_SIZE_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
            break;

        case CRYS_AESCCM_DATA_OUT_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_NULL;
            break;

        case CRYS_AESCCM_ILLEGAL_PARAMETER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
            break;

        case CRYS_AESCCM_CCM_MAC_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_AEAD_INVALID_MAC;
            break;

        case CRYS_AESCCM_CTX_SIZES_ERROR:
        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }
    return ret_val;
}

static ret_code_t backend_cc310_init(void * const p_context, uint8_t * p_key)
{
    ret_code_t ret_val;

    nrf_crypto_backend_cc310_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_aead_context_t *)p_context;

    if (!nrfx_is_in_ram(p_ctx))
    {
        return NRF_ERROR_CRYPTO_INPUT_LOCATION;
    }
    if (p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_128)
    {
        return NRF_ERROR_CRYPTO_KEY_SIZE;
    }

    switch (p_ctx->header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CCM)
        case NRF_CRYPTO_AEAD_MODE_AES_CCM:
            ret_val = NRF_SUCCESS;
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CCM_STAR)
        case NRF_CRYPTO_AEAD_MODE_AES_CCM_STAR:
            ret_val = NRF_SUCCESS;
            break;
#endif

        default:
            return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
    }

    memcpy(p_ctx->key, p_key, sizeof(p_ctx->key));

    return ret_val;
}

static ret_code_t backend_cc310_uninit(void * const p_context)
{
    nrf_crypto_backend_cc310_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_aead_context_t *)p_context;

    memset(&p_ctx->context, 0, sizeof(CRYS_AESCCM_UserContext_t));

    return NRF_SUCCESS;
}

static ret_code_t backend_cc310_crypt(void * const           p_context,
                                      nrf_crypto_operation_t operation,
                                      uint8_t *              p_nonce,
                                      uint8_t                nonce_size,
                                      uint8_t *              p_adata,
                                      size_t                 adata_size,
                                      uint8_t *              p_data_in,
                                      size_t                 data_in_size,
                                      uint8_t *              p_data_out,
                                      uint8_t *              p_mac,
                                      uint8_t                mac_size)

{
    uint32_t    mode;
    CRYSError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;

    SaSiAesEncryptMode_t  operation_cc310;
    CRYS_AESCCM_Mac_Res_t mac_buffer;

    nrf_crypto_backend_cc310_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_aead_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (!nrfx_is_in_ram(p_adata) && (adata_size > 0))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    /* CC310 supports: CCM & CCM*, where nonce_size must be > 0, so p_nonce must always
       point to RAM. */
    if (!nrfx_is_in_ram(p_nonce)         ||
        !nrfx_is_in_ram(p_data_in)  ||
        !nrfx_is_in_ram(p_data_out) ||
        !nrfx_is_in_ram(p_mac))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    if (operation == NRF_CRYPTO_DECRYPT)
    {
        operation_cc310 = SASI_AES_DECRYPT;
    }
    else if (operation == NRF_CRYPTO_ENCRYPT)
    {
        operation_cc310 = SASI_AES_ENCRYPT;
    }
    else
    {
        ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
        goto exit;
    }

    if (p_ctx->header.p_info->mode == NRF_CRYPTO_AEAD_MODE_AES_CCM)
    {
        mode = CRYS_AESCCM_MODE_CCM;

        /* Allowed MAC size in CCM mode: [4, 6, 8, 10, 12, 14, 16] */
        if ((mac_size < NRF_CRYPTO_AES_CCM_MAC_MIN) ||
            (mac_size > NRF_CRYPTO_AES_CCM_MAC_MAX) ||
            ((mac_size & 0x01) != 0))
        {
            ret_val = NRF_ERROR_CRYPTO_AEAD_MAC_SIZE;
            goto exit;
        }

        if ((nonce_size < NRF_CRYPTO_AES_CCM_NONCE_SIZE_MIN) ||
            (nonce_size > NRF_CRYPTO_AES_CCM_NONCE_SIZE_MAX))
        {
            ret_val = NRF_ERROR_CRYPTO_AEAD_NONCE_SIZE;
            goto exit;
        }
    }
    else
    {
        mode = CRYS_AESCCM_MODE_STAR;

        /* Allowed MAC size in CCM* mode: [0, 4, 8, 16] */
        if ((mac_size | NRF_CRYPTO_AES_CCM_STAR_MAC_BITMASK) != NRF_CRYPTO_AES_CCM_STAR_MAC_BITMASK)
        {
            ret_val = NRF_ERROR_CRYPTO_AEAD_MAC_SIZE;
            goto exit;
        }

        /* Allowed nonce size in CCM* mode: [13] */
        if (nonce_size != NRF_CRYPTO_AES_CCM_STAR_NONCE_SIZE)
        {
            ret_val = NRF_ERROR_CRYPTO_AEAD_NONCE_SIZE;
            goto exit;
        }
    }

    cc310_backend_enable();

    result = CC_AESCCM_Init(&p_ctx->context,
                            operation_cc310,
                            p_ctx->key,
                            CRYS_AES_Key128BitSize, // the only allowed key size for CC310
                            (uint32_t)adata_size,
                            (uint32_t)data_in_size,
                            p_nonce,
                            nonce_size,
                            mac_size,
                            mode);

    cc310_backend_disable();

    ret_val = result_get(result);

    if (ret_val != NRF_SUCCESS)
    {
        goto exit;
    }

    if ((adata_size > 0) && (p_adata != NULL))
    {
        cc310_backend_enable();

        result = CRYS_AESCCM_BlockAdata(&p_ctx->context,
                                        p_adata,
                                        (uint32_t)adata_size);

        cc310_backend_disable();

        ret_val = result_get(result);

        if (ret_val != NRF_SUCCESS)
        {
            goto exit;
        }
    }

    /* CC310 backend always needs 16 bytes buffer for MAC calculation. */
    memcpy(mac_buffer, p_mac, mac_size);

    cc310_backend_enable();

    result = CRYS_AESCCM_Finish(&p_ctx->context,
                                p_data_in,
                                (uint32_t)data_in_size,
                                p_data_out,
                                mac_buffer,
                                &mac_size);

    cc310_backend_disable();

    ret_val = result_get(result);
    if (ret_val == NRF_SUCCESS)
    {
        memcpy(p_mac, mac_buffer, mac_size);
    }

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CCM)
nrf_crypto_aead_info_t const g_nrf_crypto_aes_ccm_128_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_128,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_CCM,

    .init_fn   = backend_cc310_init,
    .uninit_fn = backend_cc310_uninit,
    .crypt_fn  = backend_cc310_crypt
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CCM_STAR)
nrf_crypto_aead_info_t const g_nrf_crypto_aes_ccm_star_128_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_128,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_CCM_STAR,

    .init_fn   = backend_cc310_init,
    .uninit_fn = backend_cc310_uninit,
    .crypt_fn  = backend_cc310_crypt
};
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_CC310_AES_AEAD)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

