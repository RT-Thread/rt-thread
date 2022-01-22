/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-14     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hw_gcm.h>

/**
 * @brief           Creating GCM Context
 *
 * @param device    Hardware crypto device
 * @param type      Type of symmetric crypto context
 *
 * @return          GCM context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_gcm_create(struct rt_hwcrypto_device *device,
                                               hwcrypto_type crypt_type)
{
    struct rt_hwcrypto_ctx *ctx;

    ctx = rt_hwcrypto_ctx_create(device, HWCRYPTO_TYPE_GCM, sizeof(struct hwcrypto_gcm));
    if (ctx)
    {
        ((struct hwcrypto_gcm *)ctx)->crypt_type = crypt_type;
    }
    return ctx;
}

/**
 * @brief           Destroy GCM Context
 *
 * @param ctx       GCM context
 */
void rt_hwcrypto_gcm_destroy(struct rt_hwcrypto_ctx *ctx)
{
    rt_hwcrypto_ctx_destroy(ctx);
}

/**
 * @brief           This function starts a GCM encryption or decryption operation
 *
 * @param ctx       GCM context
 * @param add       The buffer holding the additional data
 * @param add_len   The length of the additional data
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_gcm_start(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *add,
                               rt_size_t add_len)
{
    struct hwcrypto_gcm *gcm_ctx = (struct hwcrypto_gcm *)ctx;

    if (gcm_ctx && gcm_ctx->ops->start)
    {
        return gcm_ctx->ops->start(gcm_ctx, add, add_len);
    }
    return -RT_EINVAL;
}

/**
 * @brief           This function finishes the GCM operation and generates the authentication tag
 *
 * @param ctx       GCM context
 * @param tag       The buffer for holding the tag
 * @param tag_len   The length of the tag to generate
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_gcm_finish(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *tag,
                                rt_size_t tag_len)
{
    struct hwcrypto_gcm *gcm_ctx = (struct hwcrypto_gcm *)ctx;

    if (gcm_ctx && gcm_ctx->ops->finish)
    {
        return gcm_ctx->ops->finish(gcm_ctx, tag, tag_len);
    }
    return -RT_EINVAL;
}

/**
 * @brief           This function performs a symmetric encryption or decryption operation
 *
 * @param ctx       GCM context
 * @param mode      Operation mode. HWCRYPTO_MODE_ENCRYPT or HWCRYPTO_MODE_DECRYPT
 * @param length    The length of the input data in Bytes. This must be a multiple of the block size
 * @param in        The buffer holding the input data
 * @param out       The buffer holding the output data
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_gcm_crypt(struct rt_hwcrypto_ctx *ctx, hwcrypto_mode mode,
                               rt_size_t length, const rt_uint8_t *in, rt_uint8_t *out)
{
    return rt_hwcrypto_symmetric_crypt(ctx, mode, length, in, out);
}

/**
 * @brief           Set Symmetric Encryption and Decryption Key
 *
 * @param ctx       GCM context
 * @param key       The crypto key
 * @param bitlen    The crypto key bit length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_gcm_setkey(struct rt_hwcrypto_ctx *ctx,
                                const rt_uint8_t *key, rt_uint32_t bitlen)
{
    return rt_hwcrypto_symmetric_setkey(ctx, key, bitlen);
}

/**
 * @brief           Get Symmetric Encryption and Decryption Key
 *
 * @param ctx       GCM context
 * @param key       The crypto key buffer
 * @param bitlen    The crypto key bit length
 *
 * @return          Key length of copy
 */
rt_err_t rt_hwcrypto_gcm_getkey(struct rt_hwcrypto_ctx *ctx,
                                rt_uint8_t *key, rt_uint32_t bitlen)
{
    return rt_hwcrypto_symmetric_getkey(ctx, key, bitlen);
}

/**
 * @brief           Set Symmetric Encryption and Decryption initialization vector
 *
 * @param ctx       GCM context
 * @param iv        The crypto initialization vector
 * @param len       The crypto initialization vector length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_gcm_setiv(struct rt_hwcrypto_ctx *ctx,
                               const rt_uint8_t *iv, rt_size_t len)
{
    return rt_hwcrypto_symmetric_setiv(ctx, iv, len);
}

/**
 * @brief           Get Symmetric Encryption and Decryption initialization vector
 *
 * @param ctx       GCM context
 * @param iv        The crypto initialization vector buffer
 * @param len       The crypto initialization vector buffer length
 *
 * @return          IV length of copy
 */
rt_err_t rt_hwcrypto_gcm_getiv(struct rt_hwcrypto_ctx *ctx,
                               rt_uint8_t *iv, rt_size_t len)
{
    return rt_hwcrypto_symmetric_getiv(ctx, iv, len);
}

/**
 * @brief           Set offset in initialization vector
 *
 * @param ctx       GCM context
 * @param iv_off    The offset in IV
 */
void rt_hwcrypto_gcm_set_ivoff(struct rt_hwcrypto_ctx *ctx, rt_int32_t iv_off)
{
    rt_hwcrypto_symmetric_set_ivoff(ctx, iv_off);
}

/**
 * @brief           Get offset in initialization vector
 *
 * @param ctx       GCM context
 * @param iv_off    It must point to a valid memory
 */
void rt_hwcrypto_gcm_get_ivoff(struct rt_hwcrypto_ctx *ctx, rt_int32_t *iv_off)
{
    rt_hwcrypto_symmetric_get_ivoff(ctx, iv_off);
}

/**
 * @brief           This function copy GCM context
 *
 * @param des       The destination GCM context
 * @param src       The GCM context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_gcm_cpy(struct rt_hwcrypto_ctx *des,
                             const struct rt_hwcrypto_ctx *src)
{
    struct hwcrypto_gcm *gcm_des = (struct hwcrypto_gcm *)des;
    struct hwcrypto_gcm *gcm_src = (struct hwcrypto_gcm *)src;

    if (des != RT_NULL && src != RT_NULL)
    {
        gcm_des->crypt_type = gcm_src->crypt_type;
        /* symmetric crypto context copy */
        return rt_hwcrypto_symmetric_cpy(des, src);
    }
    return -RT_EINVAL;
}

/**
 * @brief           Reset GCM context
 *
 * @param ctx       GCM context
 */
void rt_hwcrypto_gcm_reset(struct rt_hwcrypto_ctx *ctx)
{
    rt_hwcrypto_symmetric_reset(ctx);
}
