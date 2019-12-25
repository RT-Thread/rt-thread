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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

/*lint -save -e????*/
#include "mbedtls/md.h"
#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
/*lint -restore*/
#include "nrf_crypto_error.h"
#include "mbedtls_backend_aes.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_MBEDTLS_AES)

/* macro changing bits to bytes */
#define BITS_TO_BYTES(bits)     ((bits)>>3)
#define BACKEND_ERROR_CHECK(error)      \
    do {                                \
        if ((error) != 0)               \
        {                               \
            return result_get((error)); \
        }                               \
    } while (0);

/**@internal @brief Type declarations of templates matching all possible context sizes
 *                  for this backend.
 */
typedef struct
{
    nrf_crypto_aes_internal_context_t header;       /**< Common header for context. */
    nrf_crypto_backend_aes_ctx_t      backend;      /**< Backend-specific internal context. */
    uint32_t                          context[1];   /**< AES context internal to mbed TLS. */
} nrf_crypto_backend_mbedtls_aes_any_context_t;

/**@internal @brief Type declarations of templates matching all possible context sizes
 *                  for this backend.
 */
typedef union
{
    nrf_crypto_backend_mbedtls_aes_any_context_t any;      /**< Common for all contexts. */

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
    nrf_crypto_backend_aes_ecb_context_t ecb;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
    nrf_crypto_backend_aes_cbc_context_t cbc;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
    nrf_crypto_backend_aes_ctr_context_t ctr;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
    nrf_crypto_backend_aes_cfb_context_t cfb;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
    nrf_crypto_backend_aes_cbc_mac_context_t cbc_mac;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
    nrf_crypto_backend_aes_cmac_context_t cmac;
#endif
} nrf_crypto_backend_mbedtls_aes_context_t;


static ret_code_t result_get(int error)
{
    ret_code_t ret_val;
    switch (error)
    {
        case 0:
            ret_val = NRF_SUCCESS;
            break;

        case MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case MBEDTLS_ERR_CIPHER_ALLOC_FAILED:
            ret_val = NRF_ERROR_CRYPTO_ALLOC_FAILED;
            break;

        case MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        case MBEDTLS_ERR_MD_BAD_INPUT_DATA:
            ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
            break;

        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }

    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
static ret_code_t backend_cmac_init(nrf_crypto_backend_aes_cmac_context_t * const p_cmac_ctx)
{
    int error;

    mbedtls_cipher_type_t         cipher_type;
    mbedtls_cipher_info_t const * p_cipher_info;

    mbedtls_cipher_init(&p_cmac_ctx->context);

    switch (p_cmac_ctx->header.p_info->key_size)
    {
        case NRF_CRYPTO_KEY_SIZE_128:
                cipher_type = MBEDTLS_CIPHER_AES_128_ECB;
                break;

        case NRF_CRYPTO_KEY_SIZE_192:
            cipher_type = MBEDTLS_CIPHER_AES_192_ECB;
            break;

        case NRF_CRYPTO_KEY_SIZE_256:
            cipher_type = MBEDTLS_CIPHER_AES_256_ECB;
            break;

        default:
                return NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
    }

    p_cipher_info = mbedtls_cipher_info_from_type(cipher_type);

    if (p_cipher_info == NULL)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    error = mbedtls_cipher_setup(&p_cmac_ctx->context, p_cipher_info);
    BACKEND_ERROR_CHECK(error);

    return NRF_SUCCESS;
}
#endif

static ret_code_t backend_mbedtls_init(void * const p_context, nrf_crypto_operation_t operation)
{
    ret_code_t ret_val = NRF_SUCCESS;

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    switch (p_ctx->any.header.p_info->key_size)
    {
        case NRF_CRYPTO_KEY_SIZE_128:
        case NRF_CRYPTO_KEY_SIZE_192:
        case NRF_CRYPTO_KEY_SIZE_256:
            break;

        default:
            return NRF_ERROR_CRYPTO_KEY_SIZE;
    }

    switch (p_ctx->any.header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
        case NRF_CRYPTO_AES_MODE_CBC:
        case NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7:
            VERIFY_FALSE(((operation != NRF_CRYPTO_ENCRYPT) && (operation != NRF_CRYPTO_DECRYPT)),
                         NRF_ERROR_CRYPTO_INVALID_PARAM);
            memset(&p_ctx->cbc.backend, 0, sizeof(p_ctx->cbc.backend));

            mbedtls_aes_init(&p_ctx->cbc.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
        case NRF_CRYPTO_AES_MODE_CTR:
            VERIFY_FALSE(((operation != NRF_CRYPTO_ENCRYPT) && (operation != NRF_CRYPTO_DECRYPT)),
                         NRF_ERROR_CRYPTO_INVALID_PARAM);
            memset(&p_ctx->ctr.backend, 0, sizeof(p_ctx->ctr.backend));

            mbedtls_aes_init(&p_ctx->ctr.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
        case NRF_CRYPTO_AES_MODE_CFB:
            VERIFY_FALSE(((operation != NRF_CRYPTO_ENCRYPT) && (operation != NRF_CRYPTO_DECRYPT)),
                         NRF_ERROR_CRYPTO_INVALID_PARAM);
            memset(&p_ctx->cfb.backend, 0, sizeof(p_ctx->cfb.backend));

            mbedtls_aes_init(&p_ctx->cfb.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
        case NRF_CRYPTO_AES_MODE_ECB:
        case NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7:
            VERIFY_FALSE(((operation != NRF_CRYPTO_ENCRYPT) && (operation != NRF_CRYPTO_DECRYPT)),
                         NRF_ERROR_CRYPTO_INVALID_PARAM);
            memset(&p_ctx->ecb.backend, 0, sizeof(p_ctx->ecb.backend));

            mbedtls_aes_init(&p_ctx->ecb.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
        case NRF_CRYPTO_AES_MODE_CBC_MAC:
        case NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7:
            VERIFY_TRUE((operation == NRF_CRYPTO_MAC_CALCULATE), NRF_ERROR_CRYPTO_INVALID_PARAM);
            memset(&p_ctx->cbc_mac.backend, 0, sizeof(p_ctx->cbc_mac.backend));

            mbedtls_aes_init(&p_ctx->cbc_mac.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
        case NRF_CRYPTO_AES_MODE_CMAC:
            VERIFY_TRUE((operation == NRF_CRYPTO_MAC_CALCULATE), NRF_ERROR_CRYPTO_INVALID_PARAM);

            ret_val = backend_cmac_init(&p_ctx->cmac);
            break;
#endif
        default:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;
    }

    p_ctx->any.backend.operation = operation;

    return ret_val;
}

static ret_code_t backend_mbedtls_uninit(void * const p_context)
{
    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    switch (p_ctx->any.header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
        case NRF_CRYPTO_AES_MODE_CBC:
        case NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7:
            mbedtls_aes_free(&p_ctx->cbc.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
        case NRF_CRYPTO_AES_MODE_CTR:
            mbedtls_aes_free(&p_ctx->ctr.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
        case NRF_CRYPTO_AES_MODE_CFB:
            mbedtls_aes_free(&p_ctx->cfb.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
        case NRF_CRYPTO_AES_MODE_ECB:
        case NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7:
            mbedtls_aes_free(&p_ctx->ecb.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
        case NRF_CRYPTO_AES_MODE_CBC_MAC:
        case NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7:
            mbedtls_aes_free(&p_ctx->cbc_mac.context);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
        case NRF_CRYPTO_AES_MODE_CMAC:
            mbedtls_cipher_free(&p_ctx->cmac.context);
            break;
#endif

        default:
            return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
    }

    return NRF_SUCCESS;
}

static ret_code_t backend_mbedtls_key_set(void * const p_context, uint8_t * p_key)
{
    int        error;
    ret_code_t ret_val;

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    switch (p_ctx->any.header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
        case NRF_CRYPTO_AES_MODE_CBC:
        case NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7:
            if (p_ctx->cbc.backend.operation == NRF_CRYPTO_ENCRYPT)
            {
                error = mbedtls_aes_setkey_enc(&p_ctx->cbc.context,
                                               (uint8_t const *)p_key,
                                               p_ctx->cbc.header.p_info->key_size);
            }
            else
            {
                error = mbedtls_aes_setkey_dec(&p_ctx->cbc.context,
                                               (uint8_t const *)p_key,
                                               p_ctx->cbc.header.p_info->key_size);
            }
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
        case NRF_CRYPTO_AES_MODE_CTR:
            /* Due to the nature of CFB / CTR, you should use the same key schedule for both
               encryption and decryption.*/
            error = mbedtls_aes_setkey_enc(&p_ctx->ctr.context,
                                           (uint8_t const *)p_key,
                                           p_ctx->ctr.header.p_info->key_size);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
        case NRF_CRYPTO_AES_MODE_CFB:
            /* Due to the nature of CFB / CTR, you should use the same key schedule for both
               encryption and decryption.*/
            error = mbedtls_aes_setkey_enc(&p_ctx->cfb.context,
                                           (uint8_t const *)p_key,
                                           p_ctx->cfb.header.p_info->key_size);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
        case NRF_CRYPTO_AES_MODE_ECB:
        case NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7:
            if (p_ctx->ecb.backend.operation == NRF_CRYPTO_ENCRYPT)
            {
                error = mbedtls_aes_setkey_enc(&p_ctx->ecb.context,
                                               (uint8_t const *)p_key,
                                               p_ctx->ecb.header.p_info->key_size);
            }
            else
            {
                error = mbedtls_aes_setkey_dec(&p_ctx->ecb.context,
                                               (uint8_t const *)p_key,
                                               p_ctx->ecb.header.p_info->key_size);
            }
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
        case NRF_CRYPTO_AES_MODE_CBC_MAC:
        case NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7:
            error = mbedtls_aes_setkey_enc(&p_ctx->cbc_mac.context,
                                           (uint8_t const *)p_key,
                                           p_ctx->cbc_mac.header.p_info->key_size);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
                case NRF_CRYPTO_AES_MODE_CMAC:
                    error = mbedtls_cipher_cmac_starts(&p_ctx->cmac.context,
                                                       p_key,
                                                       p_ctx->cmac.header.p_info->key_size);
                    break;
#endif

        default:
            return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
    }

    ret_val = result_get(error);

    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)      ||  \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)      ||  \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)      ||  \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
static ret_code_t backend_mbedtls_iv_set(void * const p_context, uint8_t * p_iv)
{
    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    memcpy(&p_ctx->any.backend.iv[0], p_iv, sizeof(p_ctx->any.backend.iv));

    return NRF_SUCCESS;
}

static ret_code_t backend_mbedtls_iv_get(void * const p_context, uint8_t * p_iv)
{
    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    memcpy(p_iv, p_ctx->any.backend.iv, sizeof(p_ctx->any.backend.iv));

    return NRF_SUCCESS;
}
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
/* Function extending mbedtls_aes_crypt_ecb functionality. It allows to process more than 1
   data block. It is returning MBEDTLS error type. */
static int backend_mbedtls_ecb_crypt(nrf_crypto_backend_aes_ecb_context_t * const p_ctx,
                                     uint8_t *                                    p_text_in,
                                     uint8_t *                                    p_text_out,
                                     size_t                                       text_size)
{
    int    error        = 0;
    size_t crypted_text = 0;

    if ((text_size & 0x0F) != 0)
    {
        return MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH;
    }

    while (crypted_text < text_size)
    {
        error = mbedtls_aes_crypt_ecb(&p_ctx->context,
                                      (int)p_ctx->backend.operation,
                                      p_text_in  + crypted_text,
                                      p_text_out + crypted_text);
        if (error != 0)
        {
            break;
        }
        crypted_text += NRF_CRYPTO_AES_BLOCK_SIZE;
    }

    return error;
}
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
static int backend_mbedtls_cbc_mac_update(void * const p_context,
                                          uint8_t *    p_data_in,
                                          size_t       data_size,
                                          uint8_t *    p_data_out)
{
    int error = 0;

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    for (size_t i = 0; i < data_size; i += NRF_CRYPTO_AES_BLOCK_SIZE)
    {
        error = mbedtls_aes_crypt_cbc(&p_ctx->cbc_mac.context,
                                      MBEDTLS_AES_ENCRYPT,
                                      NRF_CRYPTO_AES_BLOCK_SIZE,
                                      p_ctx->cbc_mac.backend.iv,
                                      (uint8_t const *)p_data_in + i,
                                      p_data_out);
        if (error != 0)
        {
            return error;
        }
    }

    return error;
}

static ret_code_t backend_mbedtls_cbc_mac_finalize(void * const p_context,
                                                   uint8_t *    p_data_in,
                                                   size_t       data_size,
                                                   uint8_t *    p_data_out,
                                                   size_t *     p_data_out_size)
{
    int error;

    if (*p_data_out_size < NRF_CRYPTO_AES_BLOCK_SIZE)
    {
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }

    /* this function does not support padding */
    if ((data_size & 0xF) != 0)
    {
        return NRF_ERROR_CRYPTO_INPUT_LENGTH;
    }

    error = backend_mbedtls_cbc_mac_update(p_context, p_data_in, data_size, p_data_out);
    BACKEND_ERROR_CHECK(error);

    *p_data_out_size = NRF_CRYPTO_AES_BLOCK_SIZE;

    return NRF_SUCCESS;
}

static ret_code_t backend_mbedtls_cbc_mac_padding_finalize(void * const p_context,
                                                           uint8_t *    p_data_in,
                                                           size_t       data_size,
                                                           uint8_t *    p_data_out,
                                                           size_t *     p_data_out_size)
{
    ret_code_t  ret_val;
    uint8_t     padding_buffer[NRF_CRYPTO_AES_BLOCK_SIZE] = {0};
    uint8_t     msg_ending = (uint8_t)(data_size & (size_t)0x0F);

    if (*p_data_out_size < NRF_CRYPTO_AES_BLOCK_SIZE)
    {
        /* output buffer too small */
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }

    data_size -= msg_ending;

    if (data_size > 0)
    {
        ret_val = backend_mbedtls_cbc_mac_update(p_context,
                                                 p_data_in,
                                                 data_size,
                                                 p_data_out);
        VERIFY_SUCCESS(ret_val);
    }

    ret_val = padding_pkcs7_add(&padding_buffer[0],
                                p_data_in + data_size,
                                msg_ending);
    VERIFY_SUCCESS(ret_val);

    ret_val = backend_mbedtls_cbc_mac_finalize(p_context,
                                               &padding_buffer[0],
                                               NRF_CRYPTO_AES_BLOCK_SIZE,
                                               p_data_out,
                                               p_data_out_size);
    VERIFY_SUCCESS(ret_val);

    return ret_val;
}
#endif

static ret_code_t backend_mbedtls_update(void * const p_context,
                                         uint8_t *    p_data_in,
                                         size_t       data_size,
                                         uint8_t *    p_data_out)
{
    int error;

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    switch (p_ctx->any.header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
        case NRF_CRYPTO_AES_MODE_CBC:
        case NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7:
            error = mbedtls_aes_crypt_cbc(&p_ctx->cbc.context,
                                          (int)p_ctx->cbc.backend.operation,
                                          data_size,
                                          p_ctx->cbc.backend.iv,
                                          (uint8_t const *)p_data_in,
                                          p_data_out);
            break;
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
        case NRF_CRYPTO_AES_MODE_CTR:
        {
            size_t  nc_off = 0;
            uint8_t stream_block[NRF_CRYPTO_AES_BLOCK_SIZE];

            error = mbedtls_aes_crypt_ctr(&p_ctx->ctr.context,
                                          data_size,
                                          &nc_off,
                                          p_ctx->ctr.backend.iv,
                                          stream_block,
                                          (uint8_t const *)p_data_in,
                                          p_data_out);
            break;
        }
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
        case NRF_CRYPTO_AES_MODE_CFB:
            error = mbedtls_aes_crypt_cfb8(&p_ctx->cfb.context,
                                           (int)p_ctx->cfb.backend.operation,
                                           data_size,
                                           p_ctx->cfb.backend.iv,
                                           (uint8_t const *)p_data_in,
                                           p_data_out);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
        case NRF_CRYPTO_AES_MODE_ECB:
        case NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7:
            error = backend_mbedtls_ecb_crypt(&p_ctx->ecb, p_data_in, p_data_out, data_size);
            break;
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
        case NRF_CRYPTO_AES_MODE_CBC_MAC:
        case NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7:
            error = backend_mbedtls_cbc_mac_update(p_context, p_data_in, data_size, p_data_out);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
        case NRF_CRYPTO_AES_MODE_CMAC:
            error = mbedtls_cipher_cmac_update(&p_ctx->cmac.context,
                                               p_data_in,
                                               data_size);
            break;
#endif

        default:
            return NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
    }
    BACKEND_ERROR_CHECK(error);

    return NRF_SUCCESS;
}

static ret_code_t backend_mbedtls_finalize(void * const p_context,
                                           uint8_t *    p_data_in,
                                           size_t       data_size,
                                           uint8_t *    p_data_out,
                                           size_t *     p_data_out_size)
{
    ret_code_t ret_val;

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    if (*p_data_out_size < data_size)
    {
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }

    /* data is not multiple of 16 bytes */
    if ((data_size & 0x0F) != 0)
    {
        if ((p_ctx->any.header.p_info->mode != NRF_CRYPTO_AES_MODE_CTR) &&
            (p_ctx->any.header.p_info->mode != NRF_CRYPTO_AES_MODE_CFB))
        {
            /* There are separate handlers for AES modes with padding and for MAC modes. */
            return NRF_ERROR_CRYPTO_INPUT_LENGTH;
        }
    }

    ret_val = backend_mbedtls_update(p_context, p_data_in, data_size, p_data_out);
    VERIFY_SUCCESS(ret_val);

    *p_data_out_size = data_size;

    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
static ret_code_t backend_mbedtls_cmac_finalize(void * const p_context,
                                                uint8_t *    p_data_in,
                                                size_t       data_size,
                                                uint8_t *    p_data_out,
                                                size_t *     p_data_out_size)
{
    int        error;

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    if (*p_data_out_size < NRF_CRYPTO_AES_BLOCK_SIZE)
    {
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }

    error = mbedtls_cipher_cmac_update(&p_ctx->cmac.context, p_data_in, data_size);
    BACKEND_ERROR_CHECK(error);

    error = mbedtls_cipher_cmac_finish(&p_ctx->cmac.context, p_data_out);
    BACKEND_ERROR_CHECK(error);

    *p_data_out_size = NRF_CRYPTO_AES_BLOCK_SIZE;

    return NRF_SUCCESS;
}
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC) || \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
static ret_code_t backend_mbedtls_padding_finalize(void * const p_context,
                                                   uint8_t *    p_data_in,
                                                   size_t       data_size,
                                                   uint8_t *    p_data_out,
                                                   size_t *     p_data_out_size)
{
    ret_code_t ret_val;
    size_t     buff_out_size;
    uint8_t    padding_buffer[NRF_CRYPTO_AES_BLOCK_SIZE] = {0};
    uint8_t    msg_ending = (uint8_t)(data_size & (size_t)0x0F);

    nrf_crypto_backend_mbedtls_aes_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_context_t *)p_context;

    if (p_ctx->any.backend.operation == NRF_CRYPTO_DECRYPT)
    {
        ret_val = backend_mbedtls_finalize(p_context,
                                           p_data_in,
                                           data_size,
                                           p_data_out,
                                           p_data_out_size);
        VERIFY_SUCCESS(ret_val);

        ret_val = padding_pkcs7_remove(p_data_out,
                                       p_data_out_size);
        return ret_val;
    }

    /* -------------- ENCRYPTION --------------*/
    data_size -= msg_ending;

    if (*p_data_out_size < (data_size + NRF_CRYPTO_AES_BLOCK_SIZE))
    {
        /* no space for padding */
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }

    if (data_size > 0)
    {
        /* Encrypt 16 byte blocks */
        ret_val = backend_mbedtls_update(p_context,
                                         p_data_in,
                                         data_size,
                                         p_data_out);
        VERIFY_SUCCESS(ret_val);
    }

    ret_val = padding_pkcs7_add(&padding_buffer[0],
                                p_data_in + data_size,
                                msg_ending);
    VERIFY_SUCCESS(ret_val);

    buff_out_size = *p_data_out_size - data_size;

    ret_val = backend_mbedtls_finalize(p_context,
                                       &padding_buffer[0],
                                       NRF_CRYPTO_AES_BLOCK_SIZE,
                                       p_data_out + data_size,
                                       &buff_out_size);
    VERIFY_SUCCESS(ret_val);

    *p_data_out_size = buff_out_size + data_size;

    return ret_val;
}
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_192_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_256_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_128_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_padding_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_192_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_padding_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_256_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_padding_finalize
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_ctr_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CTR,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_ctr_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ctr_192_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CTR,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_ctr_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ctr_256_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CTR,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_ctr_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};
#endif

// CFB
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cfb_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CFB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cfb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cfb_192_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CFB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_cfb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cfb_256_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CFB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_cfb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_192_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_256_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_128_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_padding_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_192_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_padding_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_256_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_padding_finalize
};
#endif


// CBC MAC
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cbc_mac_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_192_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cbc_mac_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_256_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cbc_mac_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_128_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cbc_mac_padding_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_192_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cbc_mac_padding_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_256_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = backend_mbedtls_iv_set,
    .iv_get_fn      = backend_mbedtls_iv_get,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cbc_mac_padding_finalize
};

#endif

// CMAC
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cmac_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CMAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cmac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cmac_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cmac_192_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CMAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_192,
    .context_size   = sizeof(nrf_crypto_backend_aes_cmac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cmac_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cmac_256_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CMAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_256,
    .context_size   = sizeof(nrf_crypto_backend_aes_cmac_context_t),

    .init_fn        = backend_mbedtls_init,
    .uninit_fn      = backend_mbedtls_uninit,
    .key_set_fn     = backend_mbedtls_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_mbedtls_update,
    .finalize_fn    = backend_mbedtls_cmac_finalize
};
#endif

#endif // #if NRF_MODULE_ENABLED(NRF_CRYPTO_MBEDTLS_AES)
#endif // MODULE_ENABLED(NRF_CRYPTO)

