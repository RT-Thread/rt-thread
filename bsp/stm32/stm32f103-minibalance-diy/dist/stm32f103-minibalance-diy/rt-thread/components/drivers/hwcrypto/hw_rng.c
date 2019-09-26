/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hw_rng.h>

/* Used to save default RNG Context */
static struct rt_hwcrypto_ctx *ctx_default;

/**
 * @brief           Creating RNG Context
 *
 * @param device    Hardware crypto device
 *
 * @return          RNG context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_rng_create(struct rt_hwcrypto_device *device)
{
    struct rt_hwcrypto_ctx *ctx;

    ctx = rt_hwcrypto_ctx_create(device, HWCRYPTO_TYPE_RNG, sizeof(struct hwcrypto_rng));
    return ctx;
}

/**
 * @brief           Destroy RNG Context
 *
 * @param ctx       RNG context
 */
void rt_hwcrypto_rng_destroy(struct rt_hwcrypto_ctx *ctx)
{
    /* Destroy the defaule RNG Context ? */
    if (ctx == ctx_default)
    {
        ctx_default = RT_NULL;
    }
    rt_hwcrypto_ctx_destroy(ctx);
}

/**
 * @brief           Setting RNG default devices
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_rng_default(struct rt_hwcrypto_device *device)
{
    struct rt_hwcrypto_ctx *tmp_ctx;

    /* if device is null, destroy default RNG Context */
    if (device == RT_NULL)
    {
        if (ctx_default)
        {
            rt_hwcrypto_rng_destroy(ctx_default);
            ctx_default = RT_NULL;
        }
        return RT_EOK;
    }
    /* Try create RNG Context */
    tmp_ctx = rt_hwcrypto_rng_create(device);
    if (tmp_ctx == RT_NULL)
    {
        return -RT_ERROR;
    }
    /* create RNG Context success, update default RNG Context */
    rt_hwcrypto_rng_destroy(ctx_default);
    ctx_default = tmp_ctx;

    return RT_EOK;
}

/**
 * @brief           Getting Random Numbers from RNG Context
 *
 * @param ctx       RNG context
 * 
 * @return          Random number
 */
rt_uint32_t rt_hwcrypto_rng_update_ctx(struct rt_hwcrypto_ctx *ctx)
{
    if (ctx)
    {
        return ((struct hwcrypto_rng *)ctx)->ops->update((struct hwcrypto_rng *)ctx);
    }
    return 0;
}

/**
 * @brief           Return a random number
 *
 * @return          Random number
 */
rt_uint32_t rt_hwcrypto_rng_update(void)
{
    /* Default device does not exist ? */
    if (ctx_default == RT_NULL)
    {
        /* try create Context from default device */
        rt_hwcrypto_rng_default(rt_hwcrypto_dev_default());
    }
    return rt_hwcrypto_rng_update_ctx(ctx_default);
}
