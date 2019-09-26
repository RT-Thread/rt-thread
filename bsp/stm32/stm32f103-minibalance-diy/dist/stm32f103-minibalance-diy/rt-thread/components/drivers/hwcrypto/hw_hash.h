/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-23     tyx          the first version
 */

#ifndef __HW_HASH_H__
#define __HW_HASH_H__

#include <hwcrypto.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hwcrypto_hash;

struct hwcrypto_hash_ops
{
    rt_err_t (*update)(struct hwcrypto_hash *hash_ctx,
                       const rt_uint8_t *in, rt_size_t length);     /**< Processing a packet of data */
    rt_err_t (*finish)(struct hwcrypto_hash *hash_ctx,
                       rt_uint8_t *out, rt_size_t length);          /**< Get the final hash value */
};

/**
 * @brief           hash context. Hardware driver usage
 */
struct hwcrypto_hash
{
    struct rt_hwcrypto_ctx parent;              /**< Inheritance from hardware crypto context */
    const struct hwcrypto_hash_ops *ops;        /**< !! Hardware initializes this value when creating context !! */
};

/**
 * @brief           Creating hash Context
 *
 * @param device    Hardware crypto device
 * @param type      Type of hash context
 *
 * @return          Hash context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_hash_create(struct rt_hwcrypto_device *device,
                                                hwcrypto_type type);

/**
 * @brief           Destroy hash Context
 *
 * @param ctx       Hash context
 */
void rt_hwcrypto_hash_destroy(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Get the final hash value
 *
 * @param ctx       Hash context
 * @param output    Hash value buffer
 * @param length    Hash value buffer length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_finish(struct rt_hwcrypto_ctx *ctx, rt_uint8_t *output, rt_size_t length);

/**
 * @brief           Processing a packet of data
 *
 * @param ctx       Hash context
 * @param input     Data buffer to be Processed
 * @param length    Data Buffer length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_update(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *input, rt_size_t length);

/**
 * @brief           This function copy hash context
 *
 * @param des       The destination hash context
 * @param src       The hash context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_cpy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src);

/**
 * @brief           Reset hash context
 *
 * @param ctx       Hash context
 */
void rt_hwcrypto_hash_reset(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Setting hash context type
 *
 * @param ctx       Hash context
 * @param type      Types of settings
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_set_type(struct rt_hwcrypto_ctx *ctx, hwcrypto_type type);

#ifdef __cplusplus
}
#endif

#endif
