/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-23     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hwcrypto.h>

/**
 * @brief           Setting context type (Direct calls are not recommended)
 *
 * @param ctx       Crypto context
 * @param type      Types of settings
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_set_type(struct rt_hwcrypto_ctx *ctx, hwcrypto_type type)
{
    if (ctx)
    {
        /* Is it the same category? */
        if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == (type & HWCRYPTO_MAIN_TYPE_MASK))
        {
            ctx->type = type;
            return RT_EOK;
        }
        /* Context is empty type */
        else if (ctx->type == HWCRYPTO_TYPE_NULL)
        {
            ctx->type = type;
            return RT_EOK;
        }
        else
        {
            return -RT_ERROR;
        }
    }
    return -RT_EINVAL;
}

/**
 * @brief           Reset context type (Direct calls are not recommended)
 *
 * @param ctx       Crypto context
 *
 */
void rt_hwcrypto_ctx_reset(struct rt_hwcrypto_ctx *ctx)
{
    if (ctx && ctx->device->ops->reset)
    {
        ctx->device->ops->reset(ctx);
    }
}

/**
 * @brief           Init crypto context
 *
 * @param ctx       The context to initialize
 * @param device    Hardware crypto device
 * @param type      Type of context
 * @param obj_size  Size of context object
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_ctx_init(struct rt_hwcrypto_ctx *ctx, struct rt_hwcrypto_device *device, hwcrypto_type type)
{
    rt_err_t err;

    /* Setting context type */
    rt_hwcrypto_set_type(ctx, type);
    ctx->device = device;
    /* Create hardware context */
    err = ctx->device->ops->create(ctx);
    if (err != RT_EOK)
    {
        return err;
    }
    return RT_EOK;
}

/**
 * @brief           Create crypto context
 *
 * @param device    Hardware crypto device
 * @param type      Type of context
 * @param obj_size  Size of context object
 *
 * @return          Crypto context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_ctx_create(struct rt_hwcrypto_device *device, hwcrypto_type type, rt_uint32_t obj_size)
{
    struct rt_hwcrypto_ctx *ctx;
    rt_err_t err;

    /* Parameter checking */
    if (device == RT_NULL || obj_size < sizeof(struct rt_hwcrypto_ctx))
    {
        return RT_NULL;
    }
    ctx = rt_malloc(obj_size);
    if (ctx == RT_NULL)
    {
        return ctx;
    }
    rt_memset(ctx, 0, obj_size);
    /* Init context */
    err = rt_hwcrypto_ctx_init(ctx, device, type);
    if (err != RT_EOK)
    {
        rt_free(ctx);
        ctx = RT_NULL;
    }
    return ctx;
}

/**
 * @brief           Destroy crypto context
 *
 * @param device    Crypto context
 */
void rt_hwcrypto_ctx_destroy(struct rt_hwcrypto_ctx *ctx)
{
    if (ctx == RT_NULL)
    {
        return;
    }
    /* Destroy hardware context */
    if (ctx->device->ops->destroy)
    {
        ctx->device->ops->destroy(ctx);
    }
    /* Free the resources */
    rt_free(ctx);
}

/**
 * @brief           Copy crypto context
 *
 * @param des       The destination context
 * @param src       The context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_ctx_cpy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    if (des == RT_NULL || src == RT_NULL)
    {
        return -RT_EINVAL;
    }

    /* The equipment is different or of different types and cannot be copied */
    if (des->device != src->device ||
        (des->type & HWCRYPTO_MAIN_TYPE_MASK) != (src->type & HWCRYPTO_MAIN_TYPE_MASK))
    {
        return -RT_EINVAL;
    }
    des->type = src->type;
    /* Calling Hardware Context Copy Function */
    return src->device->ops->copy(des, src);
}

/**
 * @brief           Get the default hardware crypto device
 *
 * @return          Hardware crypto device
 *
 */
struct rt_hwcrypto_device *rt_hwcrypto_dev_default(void)
{
    static struct rt_hwcrypto_device *hwcrypto_dev;

    /* If there is a default device, return the device */
    if (hwcrypto_dev)
    {
        return hwcrypto_dev;
    }
    /* Find by default device name */
    hwcrypto_dev = (struct rt_hwcrypto_device *)rt_device_find(RT_HWCRYPTO_DEFAULT_NAME);
    return hwcrypto_dev;
}

/**
 * @brief           Get the unique ID of the device
 *
 * @param device    Device object
 *
 * @return          Device unique ID
 */
rt_uint64_t rt_hwcrypto_id(struct rt_hwcrypto_device *device)
{
    if (device)
    {
        return device->id;
    }
    return 0;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops hwcrypto_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL
};
#endif

/**
 * @brief           Register hardware crypto device
 *
 * @param device    Hardware crypto device
 * @param name      Name of device
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_register(struct rt_hwcrypto_device *device, const char *name)
{
    rt_err_t err;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(name != RT_NULL);
    RT_ASSERT(device->ops != RT_NULL);
    RT_ASSERT(device->ops->create != RT_NULL);
    RT_ASSERT(device->ops->destroy != RT_NULL);
    RT_ASSERT(device->ops->copy != RT_NULL);
    RT_ASSERT(device->ops->reset != RT_NULL);

    rt_memset(&device->parent, 0, sizeof(struct rt_device));
#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &hwcrypto_ops;
#else
    device->parent.init       = RT_NULL;
    device->parent.open       = RT_NULL;
    device->parent.close      = RT_NULL;
    device->parent.read       = RT_NULL;
    device->parent.write      = RT_NULL;
    device->parent.control    = RT_NULL;
#endif

    device->parent.user_data  = RT_NULL;
    device->parent.type = RT_Device_Class_Security;

    /* Register device */
    err = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return err;
}
