/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#ifndef __HW_RNG_H__
#define __HW_RNG_H__

#include <hwcrypto.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hwcrypto_rng;

struct hwcrypto_rng_ops
{
    rt_uint32_t (*update)(struct hwcrypto_rng *ctx);    /**< Return a random number */
};

/**
 * @brief           random context. Hardware driver usage
 */
struct hwcrypto_rng
{
    struct rt_hwcrypto_ctx parent;          /**< Inheritance from hardware crypto context */
    const struct hwcrypto_rng_ops *ops;     /**< !! Hardware initializes this value when creating context !! */
};

/**
 * @brief           Creating RNG Context
 *
 * @param device    Hardware crypto device
 *
 * @return          RNG context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_rng_create(struct rt_hwcrypto_device *device);

/**
 * @brief           Destroy RNG Context
 *
 * @param ctx       RNG context
 */
void rt_hwcrypto_rng_destroy(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Setting RNG default devices
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_rng_default(struct rt_hwcrypto_device *device);

/**
 * @brief           Getting Random Numbers from RNG Context
 *
 * @param ctx       RNG context
 *
 * @return          Random number
 */
rt_uint32_t rt_hwcrypto_rng_update_ctx(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Return a random number
 *
 * @return          Random number
 */
rt_uint32_t rt_hwcrypto_rng_update(void);

#ifdef __cplusplus
}
#endif

#endif
