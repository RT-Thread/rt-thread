/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-23     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hw_hash.h>

/**
 * @brief           Creating hash Context
 *
 * @param device    Hardware crypto device
 * @param type      Type of hash context
 *
 * @return          Hash context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_hash_create(struct rt_hwcrypto_device *device, hwcrypto_type type)
{
    struct rt_hwcrypto_ctx *ctx;

    ctx = rt_hwcrypto_ctx_create(device, type, sizeof(struct hwcrypto_hash));
    return ctx;
}

/**
 * @brief           Destroy hash Context
 *
 * @param ctx       Hash context
 */
void rt_hwcrypto_hash_destroy(struct rt_hwcrypto_ctx *ctx)
{
    rt_hwcrypto_ctx_destroy(ctx);
}

/**
 * @brief           Get the final hash value
 *
 * @param ctx       Hash context
 * @param output    Hash value buffer
 * @param length    Hash value buffer length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_finish(struct rt_hwcrypto_ctx *ctx, rt_uint8_t *output, rt_size_t length)
{
    if (ctx && ((struct hwcrypto_hash *)ctx)->ops->finish)
    {
        return ((struct hwcrypto_hash *)ctx)->ops->finish((struct hwcrypto_hash *)ctx, output, length);
    }
    return -RT_ERROR;
}

/**
 * @brief           Processing a packet of data
 *
 * @param ctx       Hash context
 * @param input     Data buffer to be Processed
 * @param length    Data Buffer length
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_update(struct rt_hwcrypto_ctx *ctx, const rt_uint8_t *input, rt_size_t length)
{
    if (ctx && ((struct hwcrypto_hash *)ctx)->ops->update)
    {
        return ((struct hwcrypto_hash *)ctx)->ops->update((struct hwcrypto_hash *)ctx, input, length);
    }
    return -RT_ERROR;
}

/**
 * @brief           This function copy hash context
 *
 * @param des       The destination hash context
 * @param src       The hash context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_cpy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    return rt_hwcrypto_ctx_cpy(des, src);
}

/**
 * @brief           Reset hash context
 *
 * @param ctx       Hash context
 */
void rt_hwcrypto_hash_reset(struct rt_hwcrypto_ctx *ctx)
{
    rt_hwcrypto_ctx_reset(ctx);
}

/**
 * @brief           Setting hash context type
 *
 * @param ctx       Hash context
 * @param type      Types of settings
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_hash_set_type(struct rt_hwcrypto_ctx *ctx, hwcrypto_type type)
{
    return rt_hwcrypto_set_type(ctx, type);
}
