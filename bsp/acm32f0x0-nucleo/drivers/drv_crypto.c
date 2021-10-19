/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-10-13   AisinoChip    first add to bsp
 */

#include "board.h"
#include <rtdevice.h>

#if defined(RT_USING_HWCRYPTO)

struct acm32_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

#if defined(RT_HWCRYPTO_USING_CRC) && defined(BSP_USING_CRC)
extern rt_err_t rt_hw_crc_init(void);
extern rt_uint32_t rt_hw_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length);

static const struct hwcrypto_crc_ops crc_ops =
{
    .update = rt_hw_crc_update,
};
#endif /* RT_HWCRYPTO_USING_CRC && BSP_USING_CRC */

#if defined(RT_HWCRYPTO_USING_RNG) && defined(BSP_USING_HRNG)
static rt_uint32_t _rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t gen_random = 0;
    HAL_HRNG_Initial();

    if (0 ==  HAL_HRNG_GetHrng((uint8_t*)&gen_random, 4))
    {
        HAL_HRNG_Source_Disable();
        return gen_random;
    }
    HAL_HRNG_Source_Disable();
    return 0;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = _rng_rand,
};
#endif /* RT_HWCRYPTO_USING_RNG && BSP_USING_HRNG */

#if defined(RT_HWCRYPTO_USING_AES) && defined(BSP_USING_AES)
extern rt_err_t rt_hw_aes_init(void);
extern rt_err_t rt_hw_aes_crypto(struct hwcrypto_symmetric *ctx,
                                struct hwcrypto_symmetric_info *info);

static const struct hwcrypto_symmetric_ops aes_ops =
{
    .crypt = rt_hw_aes_crypto
};
#endif /* RT_HWCRYPTO_USING_AES && BSP_USING_AES */

static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & (HWCRYPTO_MAIN_TYPE_MASK|HWCRYPTO_SUB_TYPE_MASK))
    {
#if defined(BSP_USING_HRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        HAL_HRNG_Initial();
        ctx->contex = RT_NULL;
        ((struct hwcrypto_rng *)ctx)->ops = &rng_ops;
        break;
    }
#endif /* BSP_USING_HRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        ctx->contex = RT_NULL;
        ((struct hwcrypto_crc *)ctx)->ops = &crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES_ECB:
    case HWCRYPTO_TYPE_AES_CBC:
    {
        ctx->contex = RT_NULL;
        ((struct hwcrypto_symmetric *)ctx)->ops = &aes_ops;
        break;
    }
#endif  /* BSP_USING_AES */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void _crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_HRNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_HRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
         break;
#endif /* BSP_USING_AES */

    default:
        break;
    }
}

static rt_err_t _crypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_HRNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_HRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(CRC_HandleTypeDef));
        }
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
        break;
#endif /* BSP_USING_AES */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void _crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_HRNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_HRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
        break;
#endif /* BSP_USING_AES */

    default:
        break;
    }
}

static const struct rt_hwcrypto_ops _ops =
{
    .create = _crypto_create,
    .destroy = _crypto_destroy,
    .copy = _crypto_clone,
    .reset = _crypto_reset,
};

int rt_hw_crypto_device_init(void)
{
    static struct acm32_hwcrypto_device _crypto_dev;

#if defined(RT_HWCRYPTO_USING_CRC) && defined(BSP_USING_CRC)
    rt_hw_crc_init();
#endif /* RT_HWCRYPTO_USING_CRC && BSP_USING_CRC */
#if defined(RT_HWCRYPTO_USING_AES) && defined(BSP_USING_AES)
    rt_hw_aes_init();
#endif /* RT_HWCRYPTO_USING_AES) && BSP_USING_AES */

    _crypto_dev.dev.ops = &_ops;

    _crypto_dev.dev.user_data = &_crypto_dev;

    if (rt_hwcrypto_register(&_crypto_dev.dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_crypto_device_init);

#endif /* RT_USING_HWCRYPTO */

