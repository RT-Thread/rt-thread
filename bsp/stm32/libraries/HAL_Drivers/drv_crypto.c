/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-10     Ernest       1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>
#include <string.h>
#include "drv_crypto.h"
#include "board.h"

struct stm32_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

#if defined(BSP_USING_CRC)

struct hash_ctx_des
{
    CRC_HandleTypeDef contex;
};

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
static struct hwcrypto_crc_cfg  crc_backup_cfg;

static int reverse_bit(rt_uint32_t n)
{
    n = ((n >> 1) & 0x55555555) | ((n << 1) & 0xaaaaaaaa);
    n = ((n >> 2) & 0x33333333) | ((n << 2) & 0xcccccccc);
    n = ((n >> 4) & 0x0f0f0f0f) | ((n << 4) & 0xf0f0f0f0);
    n = ((n >> 8) & 0x00ff00ff) | ((n << 8) & 0xff00ff00);
    n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);

    return n;
}
#endif /* defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) */

static rt_uint32_t _crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t result = 0;
    struct stm32_hwcrypto_device *stm32_hw_dev = (struct stm32_hwcrypto_device *)ctx->parent.device->user_data;

#if defined(SOC_SERIES_STM32L4)|| defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
    CRC_HandleTypeDef *HW_TypeDef = (CRC_HandleTypeDef *)(ctx->parent.contex);
#endif

    rt_mutex_take(&stm32_hw_dev->mutex, RT_WAITING_FOREVER);
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
    if (memcmp(&crc_backup_cfg, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg)) != 0)
    {
        if (HW_TypeDef->Init.DefaultPolynomialUse == DEFAULT_POLYNOMIAL_DISABLE)
        {
            HW_TypeDef->Init.GeneratingPolynomial = ctx ->crc_cfg.poly;
        }
        else
        {
            HW_TypeDef->Init.GeneratingPolynomial = DEFAULT_CRC32_POLY;
        }

        switch (ctx ->crc_cfg.flags)
        {
        case 0:
            HW_TypeDef->Init.InputDataInversionMode   = CRC_INPUTDATA_INVERSION_NONE;
            HW_TypeDef->Init.OutputDataInversionMode   = CRC_OUTPUTDATA_INVERSION_DISABLE;
            break;
        case CRC_FLAG_REFIN:
            HW_TypeDef->Init.InputDataInversionMode   = CRC_INPUTDATA_INVERSION_BYTE;
            break;
        case CRC_FLAG_REFOUT:
            HW_TypeDef->Init.OutputDataInversionMode   = CRC_OUTPUTDATA_INVERSION_ENABLE;
            break;
        case CRC_FLAG_REFIN|CRC_FLAG_REFOUT:
            HW_TypeDef->Init.InputDataInversionMode   = CRC_INPUTDATA_INVERSION_BYTE;
            HW_TypeDef->Init.OutputDataInversionMode   = CRC_OUTPUTDATA_INVERSION_ENABLE;
            break;
        default :
            goto _exit;
        }

        HW_TypeDef->Init.CRCLength = ctx ->crc_cfg.width;
        if (HW_TypeDef->Init.DefaultInitValueUse == DEFAULT_INIT_VALUE_DISABLE)
        {
            HW_TypeDef->Init.InitValue = ctx ->crc_cfg.last_val;
        }

        if (HAL_CRC_Init(HW_TypeDef) != HAL_OK)
        {
            goto _exit;
        }
        memcpy(&crc_backup_cfg, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg));
    }

    if (HAL_CRC_STATE_READY != HAL_CRC_GetState(HW_TypeDef))
    {
        goto _exit;
    }
#else
    if (ctx->crc_cfg.flags != 0 || ctx->crc_cfg.last_val != 0xFFFFFFFF || ctx->crc_cfg.xorout != 0 || length % 4 != 0)
    {
        goto _exit;
    }
    length /= 4;
#endif /* defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) */

    result = HAL_CRC_Accumulate(ctx->parent.contex, (rt_uint32_t *)in, length);

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
    if (HW_TypeDef->Init.OutputDataInversionMode)
    {
        ctx ->crc_cfg.last_val = reverse_bit(result);
    }
    else
    {
        ctx ->crc_cfg.last_val = result;
    }
    crc_backup_cfg.last_val = ctx ->crc_cfg.last_val;
    result = (result ? result ^ (ctx ->crc_cfg.xorout) : result);
#endif /* defined(SOC_SERIES_STM32L4)|| defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) */

_exit:
    rt_mutex_release(&stm32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_crc_ops crc_ops =
{
    .update = _crc_update,
};
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)
static rt_uint32_t _rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t gen_random = 0;

    RNG_HandleTypeDef *HW_TypeDef = (RNG_HandleTypeDef *)(ctx->parent.contex);

    if (HAL_OK ==  HAL_RNG_GenerateRandomNumber(HW_TypeDef, &gen_random))
    {
        return gen_random ;
    }

    return 0;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = _rng_rand,
};
#endif /* BSP_USING_RNG */

static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
    {
        RNG_HandleTypeDef *hrng = rt_calloc(1, sizeof(RNG_HandleTypeDef));

        hrng->Instance = RNG;
        HAL_RNG_Init(hrng);
        ctx->contex = hrng;
        ((struct hwcrypto_rng *)ctx)->ops = &rng_ops;

        break;
    }
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        CRC_HandleTypeDef *hcrc = rt_calloc(1, sizeof(CRC_HandleTypeDef));
        if (RT_NULL == hcrc)
        {
            res = -RT_ERROR;
            break;
        }

        hcrc->Instance = CRC;
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
        hcrc->Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
        hcrc->Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_DISABLE;
        hcrc->Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_BYTE;
        hcrc->Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_ENABLE;
        hcrc->InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
#else
        if (HAL_CRC_Init(hcrc) != HAL_OK)
        {
            res = -RT_ERROR;
        }
#endif /* defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) */
        ctx->contex = hcrc;
        ((struct hwcrypto_crc *)ctx)->ops = &crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */
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
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        __HAL_CRC_DR_RESET((CRC_HandleTypeDef *)ctx-> contex);			
        HAL_CRC_DeInit((CRC_HandleTypeDef *)(ctx->contex));
        break;
#endif /* BSP_USING_CRC */
    default:
        break;
    }

    rt_free(ctx->contex);
}

static rt_err_t _crypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(struct hash_ctx_des));
        }    
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(struct hash_ctx_des));
        }
        break;
#endif /* BSP_USING_CRC */
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
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        __HAL_CRC_DR_RESET((CRC_HandleTypeDef *)ctx-> contex);
        break;
#endif /* BSP_USING_CRC */
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

int stm32_hw_crypto_device_init(void)
{
    static struct stm32_hwcrypto_device _crypto_dev;
    rt_uint32_t cpuid[3] = {0};

    _crypto_dev.dev.ops = &_ops;
#if defined(BSP_USING_UDID)

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    cpuid[0] = HAL_GetUIDw0();
    cpuid[1] = HAL_GetUIDw1();
#elif defined(SOC_SERIES_STM32H7)
    cpuid[0] = HAL_GetREVID();
    cpuid[1] = HAL_GetDEVID();
#endif

#endif /* BSP_USING_UDID */

    _crypto_dev.dev.id = 0;
    rt_memcpy(&_crypto_dev.dev.id, cpuid, 8);

    _crypto_dev.dev.user_data = &_crypto_dev;

    if (rt_hwcrypto_register(&_crypto_dev.dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }
    rt_mutex_init(&_crypto_dev.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_DEVICE_EXPORT(stm32_hw_crypto_device_init);
