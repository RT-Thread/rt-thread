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
#include "ssi_aes_error.h"
#include "cc310_backend_aes.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_CC310_AES)

/**@internal @brief Type declarations of templates matching all possible context sizes
 *                  for this backend.
 */
typedef struct
{
    nrf_crypto_aes_internal_context_t header;   /**< Common header for context. */
    SaSiAesUserContext_t              context;  /**< AES context internal to mbed TLS. */
    nrf_crypto_backend_aes_ctx_t      backend;  /**< Backend-specific internal context. */
} nrf_crypto_backend_cc310_aes_any_context_t;

/**@internal @brief Type declarations of templates matching all possible context sizes
 *                  for this backend.
 */
typedef union
{
    nrf_crypto_backend_cc310_aes_any_context_t any;      /**< Common for all contexts. */

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_ECB)
    nrf_crypto_backend_aes_ecb_context_t ecb;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC)
    nrf_crypto_backend_aes_cbc_context_t cbc;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CTR)
    nrf_crypto_backend_aes_ctr_context_t ctr;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
    nrf_crypto_backend_aes_cbc_mac_context_t cbc_mac;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CMAC)
    nrf_crypto_backend_aes_cmac_context_t cmac;
#endif
} nrf_crypto_backend_cc310_aes_context_t;


static ret_code_t result_get(SaSiError_t error)
{
    ret_code_t ret_val;
    switch (error)
    {
        case SASI_SUCCESS:
            ret_val = NRF_SUCCESS;
            break;

        case SASI_AES_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NULL;
            break;

        case SASI_AES_ILLEGAL_KEY_SIZE_ERROR:
        case SASI_AES_DATA_IN_SIZE_ILLEGAL:
        case SASI_AES_DATA_IN_BUFFER_SIZE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case SASI_AES_INVALID_IV_OR_TWEAK_PTR_ERROR:
        case SASI_AES_INVALID_KEY_POINTER_ERROR:
        case SASI_AES_DATA_IN_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INPUT_NULL;
            break;

        case SASI_AES_ILLEGAL_OPERATION_MODE_ERROR:
        case SASI_AES_KEY_TYPE_NOT_SUPPORTED_ERROR:
        case SASI_AES_INVALID_ENCRYPT_MODE_ERROR:
        case SASI_AES_ILLEGAL_PADDING_TYPE_ERROR:
        case SASI_AES_INCORRECT_PADDING_ERROR:
        case SASI_AES_DECRYPTION_NOT_ALLOWED_ON_THIS_MODE:
        case SASI_AES_ADDITIONAL_BLOCK_NOT_PERMITTED_ERROR:
        case SASI_AES_IS_NOT_SUPPORTED:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        case SASI_AES_DATA_OUT_BUFFER_SIZE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
            break;

        case SASI_AES_DATA_OUT_POINTER_INVALID_ERROR:
        case SASI_AES_DATA_OUT_SIZE_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_NULL;
            break;

        case SASI_AES_CTX_SIZES_ERROR:
        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }
    return ret_val;
}

static ret_code_t params_validate(nrf_crypto_backend_cc310_aes_context_t const * const p_ctx,
                                  SaSiAesOperationMode_t *                             p_mode,
                                  nrf_crypto_operation_t                               operation)
{
    ret_code_t ret_val = NRF_SUCCESS;

    switch (p_ctx->any.header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_ECB)
        case NRF_CRYPTO_AES_MODE_ECB:
        case NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7:
            *p_mode = SASI_AES_MODE_ECB;
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC)
        case NRF_CRYPTO_AES_MODE_CBC:
        case NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7:
            *p_mode = SASI_AES_MODE_CBC;
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CTR)
        case NRF_CRYPTO_AES_MODE_CTR:
            *p_mode = SASI_AES_MODE_CTR;
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
        case NRF_CRYPTO_AES_MODE_CBC_MAC:
        case NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7:
            *p_mode = SASI_AES_MODE_CBC_MAC;
            VERIFY_TRUE((operation == NRF_CRYPTO_MAC_CALCULATE), NRF_ERROR_CRYPTO_INVALID_PARAM);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CMAC)
        case NRF_CRYPTO_AES_MODE_CMAC:
            *p_mode = SASI_AES_MODE_CMAC;
            VERIFY_TRUE((operation == NRF_CRYPTO_MAC_CALCULATE), NRF_ERROR_CRYPTO_INVALID_PARAM);
            break;
#endif

        default:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;
    }

    return ret_val;
}

static ret_code_t backend_cc310_init(void * const p_context, nrf_crypto_operation_t operation)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;

    SaSiAesOperationMode_t mode;
    SaSiAesEncryptMode_t   operation_cc310;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (!nrfx_is_in_ram(&p_ctx->any.context))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }
    if (p_ctx->any.header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_128)
    {
        ret_val = NRF_ERROR_CRYPTO_KEY_SIZE;
        goto exit;
    }

    ret_val = params_validate(p_ctx, &mode, operation);

    if (ret_val != NRF_SUCCESS)
    {
        goto exit;
    }

    if (operation == NRF_CRYPTO_DECRYPT)
    {
        operation_cc310 = SASI_AES_DECRYPT;
    }
    else if ((operation == NRF_CRYPTO_ENCRYPT) || (operation == NRF_CRYPTO_MAC_CALCULATE))
    {
        operation_cc310 = SASI_AES_ENCRYPT;
    }
    else
    {
        ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
        goto exit;
    }
    p_ctx->any.backend.operation = operation;

    result  = SaSi_AesInit(&p_ctx->any.context,
                           operation_cc310,
                           mode,
                           SASI_AES_PADDING_NONE);  /* CC310 does not support padding */
    ret_val = result_get(result);

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}

static ret_code_t backend_cc310_uninit(void * const p_context)
{
    SaSiError_t result;
    ret_code_t  ret_val;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    bool mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    result  = SaSi_AesFree(&p_ctx->any.context);
    ret_val = result_get(result);

    cc310_backend_mutex_unlock();
    return ret_val;
}

static ret_code_t backend_cc310_key_set(void * const p_context, uint8_t * p_key)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;

    SaSiAesUserKeyData_t key_data;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (!nrfx_is_in_ram(p_key))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    key_data.pKey    = p_key;
    key_data.keySize = (p_ctx->any.header.p_info->key_size) >> 3; // change bits to bytes

    result  = SaSi_AesSetKey(&p_ctx->any.context,
                             SASI_AES_USER_KEY,
                             &key_data,
                             sizeof(key_data));
    ret_val = result_get(result);

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC)      ||  \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CTR)      ||  \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
static ret_code_t backend_cc310_iv_set(void * const p_context, uint8_t * p_iv)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (!nrfx_is_in_ram(p_iv))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    result  = SaSi_AesSetIv(&p_ctx->any.context, p_iv);
    ret_val = result_get(result);

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}

static ret_code_t backend_cc310_iv_get(void * const p_context, uint8_t * p_iv)
{
    SaSiError_t result;
    ret_code_t  ret_val = NRF_ERROR_CRYPTO_INTERNAL;
    bool        mutex_locked;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (!nrfx_is_in_ram(p_iv))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    result  = SaSi_AesGetIv(&p_ctx->any.context, p_iv);

    /* Below code allows to read IV after calling nrf_crypto_aes_finalize */
    if (result == SASI_AES_ILLEGAL_OPERATION_MODE_ERROR)
    {
        if (p_ctx->any.header.init_value == NRF_CRYPTO_AES_UNINIT_MAGIC_VALUE)
        {
            memcpy(p_iv, p_ctx->any.backend.iv, NRF_CRYPTO_MBEDTLS_AES_IV_SIZE);
            ret_val = NRF_SUCCESS;
        }
    }
    else
    {
        ret_val = result_get(result);
    }

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}
#endif

static ret_code_t backend_cc310_update(void * const p_context,
                                       uint8_t *    p_data_in,
                                       size_t       data_size,
                                       uint8_t *    p_data_out)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;
    size_t      size;
    size_t      offset = 0;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (!nrfx_is_in_ram(p_data_in) || !nrfx_is_in_ram(p_data_out))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    do
    {
        /* CC310 allows only 64kB blocks, operation must be devided */
        if (data_size > CC310_MAX_LENGTH_DMA_AES_OPERATIONS)
        {
            size       = CC310_MAX_LENGTH_DMA_AES_OPERATIONS;
            data_size -= CC310_MAX_LENGTH_DMA_AES_OPERATIONS;
        }
        else
        {
            size       = data_size;
            data_size  = 0;
        }

        cc310_backend_enable();

        if (p_ctx->any.backend.operation == NRF_CRYPTO_MAC_CALCULATE)
        {
            result  = SaSi_AesBlock(&p_ctx->any.context,
                                    p_data_in  + offset,
                                    size,
                                    p_data_out);
        }
        else
        {
            result  = SaSi_AesBlock(&p_ctx->any.context,
                                    p_data_in  + offset,
                                    size,
                                    p_data_out + offset);
        }

        cc310_backend_disable();

        offset += size;
        ret_val = result_get(result);

    } while ((data_size > 0) && (ret_val == NRF_SUCCESS));

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}

static ret_code_t backend_cc310_finalize(void * const p_context,
                                         uint8_t *    p_data_in,
                                         size_t       data_size,
                                         uint8_t *    p_data_out,
                                         size_t *     p_data_out_size)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;
    size_t      size;
    size_t      offset = 0;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
        VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (*p_data_out_size < data_size)
    {
        ret_val = NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
        goto exit;
    }

    /* This function does not support padding */
    if (((data_size & 0xF) != 0) &&
        (p_ctx->any.header.p_info->mode != NRF_CRYPTO_AES_MODE_CTR))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
        goto exit;
    }

    if (!nrfx_is_in_ram(p_data_in) || !nrfx_is_in_ram(p_data_out))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    /* CC310 allows only 64kB blocks, operation must be devided */
    while (data_size > CC310_MAX_LENGTH_DMA_AES_OPERATIONS)
    {
        size       = CC310_MAX_LENGTH_DMA_AES_OPERATIONS;
        data_size -= CC310_MAX_LENGTH_DMA_AES_OPERATIONS;

        cc310_backend_enable();

        result  = SaSi_AesBlock(&p_ctx->any.context,
                                p_data_in  + offset,
                                size,
                                p_data_out + offset);

        cc310_backend_disable();

        offset += size;
        ret_val = result_get(result);

        if (ret_val != NRF_SUCCESS)
        {
            goto exit;
        }
    }

    /* Calculate space in the output buffer */
    *p_data_out_size -= offset;

    cc310_backend_enable();

    result = SaSi_AesFinish(&p_ctx->any.context,
                            data_size,
                            p_data_in  + offset,
                            data_size,
                            p_data_out + offset,
                            p_data_out_size);

    cc310_backend_disable();

    ret_val = result_get(result);

    if (ret_val == NRF_SUCCESS)
    {
        /* update information about size of encrypted data */
        *p_data_out_size += offset;
    }

    /* Store IV value in case it will be needed after finalize operation */
    if ((p_ctx->any.header.p_info->mode == NRF_CRYPTO_AES_MODE_CBC) ||
        (p_ctx->any.header.p_info->mode == NRF_CRYPTO_AES_MODE_CTR))
    {
        result  = SaSi_AesGetIv(&p_ctx->any.context, &p_ctx->any.backend.iv[0]);
        ret_val = result_get(result);
    }

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CMAC)   || \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
static ret_code_t backend_cc310_mac_finalize(void * const p_context,
                                             uint8_t *    p_data_in,
                                             size_t       data_size,
                                             uint8_t *    p_data_out,
                                             size_t *     p_data_out_size)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    bool        mutex_locked;
    size_t      size;
    size_t      offset = 0;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    if (*p_data_out_size < NRF_CRYPTO_AES_BLOCK_SIZE)
    {
        ret_val = NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
        goto exit;
    }

    if (!nrfx_is_in_ram(p_data_in) || !nrfx_is_in_ram(p_data_out))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LOCATION;
        goto exit;
    }

    /* This function does not support padding for CBC-MAC */
    if (((data_size & 0xF) != 0) &&
        (NRF_CRYPTO_AES_MODE_CBC_MAC == p_ctx->any.header.p_info->mode))
    {
        ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
        goto exit;
    }

    /* CC310 allows only 64kB blocks, operation must be devided */
    while (data_size > CC310_MAX_LENGTH_DMA_AES_OPERATIONS)
    {
        size       = CC310_MAX_LENGTH_DMA_AES_OPERATIONS;
        data_size -= CC310_MAX_LENGTH_DMA_AES_OPERATIONS;

        cc310_backend_enable();

        result  = SaSi_AesBlock(&p_ctx->any.context,
                                p_data_in  + offset,
                                size,
                                p_data_out);

        cc310_backend_disable();

        offset += size;
        ret_val = result_get(result);

        if (ret_val != NRF_SUCCESS)
        {
            goto exit;
        }
    }

    cc310_backend_enable();

    result = SaSi_AesFinish(&p_ctx->any.context,
                            data_size,
                            p_data_in  + offset,
                            data_size,
                            p_data_out,
                            p_data_out_size);

    cc310_backend_disable();

    ret_val = result_get(result);

    if (ret_val == NRF_SUCCESS)
    {
        /* update information about size of encrypted data */
        *p_data_out_size = NRF_CRYPTO_AES_BLOCK_SIZE;
    }

    /* Store IV value in case it will be needed after finalize operation */
    if (p_ctx->any.header.p_info->mode == NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7)
    {
        result  = SaSi_AesGetIv(&p_ctx->any.context, &p_ctx->any.backend.iv[0]);
        ret_val = result_get(result);
    }

exit:
    cc310_backend_mutex_unlock();
    return ret_val;
}
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
static ret_code_t backend_cc310_cbc_mac_padding_finalize(void * const p_context,
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
        ret_val = backend_cc310_update(p_context,
                                       p_data_in,
                                       data_size,
                                       p_data_out);
        VERIFY_SUCCESS(ret_val);
    }

    ret_val = padding_pkcs7_add(&padding_buffer[0],
                                p_data_in + data_size,
                                msg_ending);
    VERIFY_SUCCESS(ret_val);

    ret_val = backend_cc310_mac_finalize(p_context,
                                         &padding_buffer[0],
                                         NRF_CRYPTO_AES_BLOCK_SIZE,
                                         p_data_out,
                                         p_data_out_size);
    VERIFY_SUCCESS(ret_val);

    return ret_val;
}
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC) || \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_ECB)
static ret_code_t backend_cc310_padding_finalize(void * const p_context,
                                                 uint8_t *    p_data_in,
                                                 size_t       data_size,
                                                 uint8_t *    p_data_out,
                                                 size_t *     p_data_out_size)
{
    SaSiError_t result;
    ret_code_t  ret_val;
    uint8_t     padding_buffer[NRF_CRYPTO_AES_BLOCK_SIZE] = {0};
    uint8_t     msg_ending = (uint8_t)(data_size & (size_t)0x0F);
    size_t      buff_out_size;

    nrf_crypto_backend_cc310_aes_context_t * p_ctx =
        (nrf_crypto_backend_cc310_aes_context_t *)p_context;

    if (p_ctx->any.backend.operation == NRF_CRYPTO_DECRYPT)
    {
        ret_val = backend_cc310_finalize(p_context,
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
        ret_val = backend_cc310_update(p_context,
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

    ret_val = backend_cc310_finalize(p_context,
                                     &padding_buffer[0],
                                     NRF_CRYPTO_AES_BLOCK_SIZE,
                                     p_data_out + data_size,
                                     &buff_out_size);
    VERIFY_SUCCESS(ret_val);

    *p_data_out_size = buff_out_size + data_size;

    /* Store IV value in case it will be needed after finalize operation */
    if (p_ctx->any.header.p_info->mode == NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7)
    {
        result  = SaSi_AesGetIv(&p_ctx->any.context, &p_ctx->any.backend.iv[0]);
        ret_val = result_get(result);
    }

    return ret_val;
}
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = backend_cc310_iv_set,
    .iv_get_fn      = backend_cc310_iv_get,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_128_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = backend_cc310_iv_set,
    .iv_get_fn      = backend_cc310_iv_get,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_padding_finalize
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CTR)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_ctr_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CTR,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_ctr_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = backend_cc310_iv_set,
    .iv_get_fn      = backend_cc310_iv_get,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_finalize
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_ECB)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_ecb_128_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_ecb_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_padding_finalize
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = backend_cc310_iv_set,
    .iv_get_fn      = backend_cc310_iv_get,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_mac_finalize
};

nrf_crypto_aes_info_t const g_nrf_crypto_aes_cbc_mac_128_pad_pkcs7_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cbc_mac_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = backend_cc310_iv_set,
    .iv_get_fn      = backend_cc310_iv_get,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_cbc_mac_padding_finalize
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CMAC)
nrf_crypto_aes_info_t const g_nrf_crypto_aes_cmac_128_info =
{
    .mode           = NRF_CRYPTO_AES_MODE_CMAC,
    .key_size       = NRF_CRYPTO_KEY_SIZE_128,
    .context_size   = sizeof(nrf_crypto_backend_aes_cmac_context_t),

    .init_fn        = backend_cc310_init,
    .uninit_fn      = backend_cc310_uninit,
    .key_set_fn     = backend_cc310_key_set,
    .iv_set_fn      = NULL,
    .iv_get_fn      = NULL,
    .update_fn      = backend_cc310_update,
    .finalize_fn    = backend_cc310_mac_finalize
};
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_AES_BACKEND_CC310)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

