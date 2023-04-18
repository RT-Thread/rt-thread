/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hw_symmetric.h>

/**
 * @brief           Creating Symmetric Encryption and Decryption Context
 *
 * @param device    Hardware crypto device
 * @param type      Type of symmetric crypto context
 *
 * @return          Symmetric crypto context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_symmetric_create(struct rt_hwcrypto_device *device, hwcrypto_type type)
{
    struct rt_hwcrypto_ctx *ctx;

    ctx = rt_hwcrypto_ctx_create(device, type, sizeof(struct hwcrypto_symmetric));
    return ctx;
}

/**
 * @brief           Destroy Symmetric Encryption and Decryption Context
 *
 * @param ctx       Symmetric crypto context
 */
void rt_hwcrypto_symmetric_destroy(struct rt_hwcrypto_ctx *ctx)
{
    rt_hwcrypto_ctx_destroy(ctx);
}

/**
 * @brief           This function performs a symmetric encryption or decryption operation
 *
 * @param ctx       Symmetric crypto context
 * @param mode      Operation mode. HWCRYPTO_MODE_ENCRYPT or HWCRYPTO_MODE_DECRYPT
 * @param length    The length of the input data in Bytes. This must be a multiple of the block size
 * @param in        The buffer holding the input data
 * @param out       The buffer holding the output data
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_crypt(struct rt_hwcrypto_ctx *ctx, hwcrypto_mode mode, rt_size_t length, const rt_uint8_t *in, rt_uint8_t *out)
{
    struct hwcrypto_symmetric *symmetric_ctx;
    struct hwcrypto_symmetric_info symmetric_info;
    rt_err_t err;

    if (ctx == RT_NULL)
    {
        return -RT_EINVAL;
    }
    symmetric_ctx = (struct hwcrypto_symmetric *)ctx;
    if (symmetric_ctx->ops->crypt == RT_NULL)
    {
        return -RT_ERROR;
    }
    if (mode != HWCRYPTO_MODE_ENCRYPT && mode != HWCRYPTO_MODE_DECRYPT)
    {
        return -RT_EINVAL;
    }

    /* Input information packaging */
    symmetric_info.mode = mode;
    symmetric_info.in = in;
    symmetric_info.out = out;
    symmetric_info.length = length;

    /* Calling Hardware Encryption and Decryption Function */
    err = symmetric_ctx->ops->crypt(symmetric_ctx, &symmetric_info);

    /* clean up flags */
    symmetric_ctx->flags &= ~(SYMMTRIC_MODIFY_KEY | SYMMTRIC_MODIFY_IV | SYMMTRIC_MODIFY_IVOFF);
    return err;
}

/**
 * @brief           Set Symmetric Encryption and Decryption Key
 *
 * @param ctx       Symmetric crypto context
 * @param key       The crypto key
 * @param bitlen    The crypto key bit length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_setkey(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *key, rt_uint32_t bitlen)
{
    struct hwcrypto_symmetric *symmetric_ctx;

    if (ctx && bitlen <= RT_HWCRYPTO_KEYBIT_MAX_SIZE)
    {
        symmetric_ctx = (struct hwcrypto_symmetric *)ctx;
        rt_memcpy(symmetric_ctx->key, key, bitlen >> 3);
        /* Record key length */
        symmetric_ctx->key_bitlen = bitlen;
        /* Key change flag set up */
        symmetric_ctx->flags |= SYMMTRIC_MODIFY_KEY;
        return RT_EOK;
    }

    return -RT_EINVAL;
}

/**
 * @brief           Get Symmetric Encryption and Decryption Key
 *
 * @param ctx       Symmetric crypto context
 * @param key       The crypto key buffer
 * @param bitlen    The crypto key bit length
 *
 * @return          Key length of copy
 */
int rt_hwcrypto_symmetric_getkey(struct rt_hwcrypto_ctx *ctx, rt_uint8_t *key, rt_uint32_t bitlen)
{
    struct hwcrypto_symmetric *symmetric_ctx = (struct hwcrypto_symmetric *)ctx;

    if (ctx && bitlen >= symmetric_ctx->key_bitlen)
    {
        rt_memcpy(key, symmetric_ctx->key, symmetric_ctx->key_bitlen >> 3);
        return symmetric_ctx->key_bitlen;
    }

    return 0;
}

/**
 * @brief           Set Symmetric Encryption and Decryption initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv        The crypto initialization vector
 * @param len       The crypto initialization vector length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_setiv(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *iv, rt_size_t len)
{
    struct hwcrypto_symmetric *symmetric_ctx;

    if (ctx && len <= RT_HWCRYPTO_IV_MAX_SIZE)
    {
        symmetric_ctx = (struct hwcrypto_symmetric *)ctx;
        rt_memcpy(symmetric_ctx->iv, iv, len);
        symmetric_ctx->iv_len = len;
        /* IV change flag set up */
        symmetric_ctx->flags |= SYMMTRIC_MODIFY_IV;
        return RT_EOK;
    }

    return -RT_EINVAL;
}

/**
 * @brief           Get Symmetric Encryption and Decryption initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv        The crypto initialization vector buffer
 * @param len       The crypto initialization vector buffer length
 *
 * @return          IV length of copy
 */
int rt_hwcrypto_symmetric_getiv(struct rt_hwcrypto_ctx *ctx, rt_uint8_t *iv, rt_size_t len)
{
    struct hwcrypto_symmetric *symmetric_ctx = (struct hwcrypto_symmetric *)ctx;;

    if (ctx && len >= symmetric_ctx->iv_len)
    {
        rt_memcpy(iv, symmetric_ctx->iv, symmetric_ctx->iv_len);
        return symmetric_ctx->iv_len;
    }

    return 0;
}

/**
 * @brief           Set offset in initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv_off    The offset in IV
 */
void rt_hwcrypto_symmetric_set_ivoff(struct rt_hwcrypto_ctx *ctx, rt_int32_t iv_off)
{
    if (ctx)
    {
        ((struct hwcrypto_symmetric *)ctx)->iv_off = iv_off;
        /* iv_off change flag set up */
        ((struct hwcrypto_symmetric *)ctx)->flags |= SYMMTRIC_MODIFY_IVOFF;
    }
}

/**
 * @brief           Get offset in initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv_off    It must point to a valid memory
 */
void rt_hwcrypto_symmetric_get_ivoff(struct rt_hwcrypto_ctx *ctx, rt_int32_t *iv_off)
{
    if (ctx && iv_off)
    {
        *iv_off = ((struct hwcrypto_symmetric *)ctx)->iv_off;
    }
}

/**
 * @brief           This function copy symmetric crypto context
 *
 * @param des       The destination symmetric crypto context
 * @param src       The symmetric crypto context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_cpy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    struct hwcrypto_symmetric *symmetric_des = (struct hwcrypto_symmetric *)des;
    struct hwcrypto_symmetric *symmetric_src = (struct hwcrypto_symmetric *)src;

    if (des != RT_NULL && src != RT_NULL)
    {
        /* Copy Symmetric Encryption and Decryption Context Information */
        symmetric_des->flags      = symmetric_src->flags     ;
        symmetric_des->iv_len     = symmetric_src->iv_len    ;
        symmetric_des->iv_off     = symmetric_src->iv_off    ;
        symmetric_des->key_bitlen = symmetric_src->key_bitlen;
        rt_memcpy(symmetric_des->iv, symmetric_src->iv, symmetric_src->iv_len);
        rt_memcpy(symmetric_des->key, symmetric_src->key, symmetric_src->key_bitlen >> 3);

        /* Hardware context copy */
        return rt_hwcrypto_ctx_cpy(des, src);
    }
    return -RT_EINVAL;
}

/**
 * @brief           Reset symmetric crypto context
 *
 * @param ctx       Symmetric crypto context
 */
void rt_hwcrypto_symmetric_reset(struct rt_hwcrypto_ctx *ctx)
{
    struct hwcrypto_symmetric *symmetric_ctx = (struct hwcrypto_symmetric *)ctx;
    if (ctx != RT_NULL)
    {
        /* Copy Symmetric Encryption and Decryption Context Information */
        symmetric_ctx->flags      = 0x00;
        symmetric_ctx->iv_len     = 0x00;
        symmetric_ctx->iv_off     = 0x00;
        symmetric_ctx->key_bitlen = 0x00;
        rt_memset(symmetric_ctx->iv, 0, RT_HWCRYPTO_IV_MAX_SIZE);
        rt_memset(symmetric_ctx->key, 0, RT_HWCRYPTO_KEYBIT_MAX_SIZE >> 3);

        /* Hardware context reset */
        rt_hwcrypto_ctx_reset(ctx);
    }
}

/**
 * @brief           Setting symmetric crypto context type
 *
 * @param ctx       Symmetric crypto context
 * @param type      Types of settings
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_set_type(struct rt_hwcrypto_ctx *ctx, hwcrypto_type type)
{
    return rt_hwcrypto_set_type(ctx, type);
}
