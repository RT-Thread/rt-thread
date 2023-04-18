/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#ifndef __HW_SYMMETRIC_H__
#define __HW_SYMMETRIC_H__

#include <hwcrypto.h>

#ifndef RT_HWCRYPTO_IV_MAX_SIZE
#define RT_HWCRYPTO_IV_MAX_SIZE  (16)
#endif
#ifndef RT_HWCRYPTO_KEYBIT_MAX_SIZE
#define RT_HWCRYPTO_KEYBIT_MAX_SIZE  (256)
#endif

#define SYMMTRIC_MODIFY_KEY    (0x1 << 0)
#define SYMMTRIC_MODIFY_IV     (0x1 << 1)
#define SYMMTRIC_MODIFY_IVOFF  (0x1 << 2)

#ifdef __cplusplus
extern "C" {
#endif

struct hwcrypto_symmetric;
struct hwcrypto_symmetric_info;

struct hwcrypto_symmetric_ops
{
    rt_err_t (*crypt)(struct hwcrypto_symmetric *symmetric_ctx,
                      struct hwcrypto_symmetric_info *symmetric_info);  /**< Hardware Symmetric Encryption and Decryption Callback */
};

/**
 * @brief           Hardware driver usage, including input and output information
 */
struct hwcrypto_symmetric_info
{
    hwcrypto_mode mode;             /**< crypto mode. HWCRYPTO_MODE_ENCRYPT or HWCRYPTO_MODE_DECRYPT */
    const rt_uint8_t *in;           /**< Input data */
    rt_uint8_t *out;                /**< Output data will be written */
    rt_size_t length;               /**< The length of the input data in Bytes. It's a multiple of block size. */
};

/**
 * @brief           Symmetric crypto context. Hardware driver usage
 */
struct hwcrypto_symmetric
{
    struct rt_hwcrypto_ctx parent;                      /**< Inheritance from hardware crypto context */
    rt_uint16_t flags;                                  /**< key or iv or ivoff has been changed. The flag will be set up */
    rt_uint16_t iv_len;                                 /**< initialization vector effective length */
    rt_uint16_t iv_off;                                 /**< The offset in IV */
    rt_uint16_t key_bitlen;                             /**< The crypto key bit length */
    rt_uint8_t iv[RT_HWCRYPTO_IV_MAX_SIZE];             /**< The initialization vector */
    rt_uint8_t key[RT_HWCRYPTO_KEYBIT_MAX_SIZE >> 3];   /**< The crypto key */
    const struct hwcrypto_symmetric_ops *ops;           /**< !! Hardware initializes this value when creating context !! */
};

/**
 * @brief           Creating Symmetric Encryption and Decryption Context
 *
 * @param device    Hardware crypto device
 * @param type      Type of symmetric crypto context
 *
 * @return          Symmetric crypto context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_symmetric_create(struct rt_hwcrypto_device *device,
        hwcrypto_type type);

/**
 * @brief           Destroy Symmetric Encryption and Decryption Context
 *
 * @param ctx       Symmetric crypto context
 */
void rt_hwcrypto_symmetric_destroy(struct rt_hwcrypto_ctx *ctx);

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
rt_err_t rt_hwcrypto_symmetric_crypt(struct rt_hwcrypto_ctx *ctx, hwcrypto_mode mode,
                                     rt_size_t length, const rt_uint8_t *in, rt_uint8_t *out);

/**
 * @brief           Set Symmetric Encryption and Decryption Key
 *
 * @param ctx       Symmetric crypto context
 * @param key       The crypto key
 * @param bitlen    The crypto key bit length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_setkey(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *key, rt_uint32_t bitlen);

/**
 * @brief           Get Symmetric Encryption and Decryption Key
 *
 * @param ctx       Symmetric crypto context
 * @param key       The crypto key buffer
 * @param bitlen    The crypto key bit length
 *
 * @return          Key length of copy
 */
int rt_hwcrypto_symmetric_getkey(struct rt_hwcrypto_ctx *ctx, rt_uint8_t *key, rt_uint32_t bitlen);

/**
 * @brief           Set Symmetric Encryption and Decryption initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv        The crypto initialization vector
 * @param len       The crypto initialization vector length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_setiv(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *iv, rt_size_t len);

/**
 * @brief           Get Symmetric Encryption and Decryption initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv        The crypto initialization vector buffer
 * @param len       The crypto initialization vector buffer length
 *
 * @return          IV length of copy
 */
int rt_hwcrypto_symmetric_getiv(struct rt_hwcrypto_ctx *ctx, rt_uint8_t *iv, rt_size_t len);

/**
 * @brief           Set offset in initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv_off    The offset in IV
 */
void rt_hwcrypto_symmetric_set_ivoff(struct rt_hwcrypto_ctx *ctx, rt_int32_t iv_off);

/**
 * @brief           Get offset in initialization vector
 *
 * @param ctx       Symmetric crypto context
 * @param iv_off    It must point to a valid memory
 */
void rt_hwcrypto_symmetric_get_ivoff(struct rt_hwcrypto_ctx *ctx, rt_int32_t *iv_off);

/**
 * @brief           This function copy symmetric crypto context
 *
 * @param des       The destination symmetric crypto context
 * @param src       The symmetric crypto context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_cpy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src);

/**
 * @brief           Reset symmetric crypto context
 *
 * @param ctx       Symmetric crypto context
 */
void rt_hwcrypto_symmetric_reset(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Setting symmetric crypto context type
 *
 * @param ctx       Symmetric crypto context
 * @param type      Types of settings
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_symmetric_set_type(struct rt_hwcrypto_ctx *ctx, hwcrypto_type type);

#ifdef __cplusplus
}
#endif

#endif
