/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-10     Ernest       1st version
 * 2020-10-14     Dozingfiretruck   Porting for stm32wbxx
 * 2020-11-26     thread-liu   add hash
 * 2020-11-26     thread-liu   add cryp
 * 2020-12-11     WKJay        fix build problem
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>
#include <string.h>
#include "drv_crypto.h"
#include "board.h"
#include "drv_config.h"

struct stm32_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

#if defined(BSP_USING_CRC)

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32MP1)
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

#if defined(SOC_SERIES_STM32L4)|| defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32MP1)
    CRC_HandleTypeDef *HW_TypeDef = (CRC_HandleTypeDef *)(ctx->parent.contex);
#endif

    rt_mutex_take(&stm32_hw_dev->mutex, RT_WAITING_FOREVER);
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32MP1)
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

        switch(ctx ->crc_cfg.width)
        {
#if defined(CRC_POLYLENGTH_7B) && defined(CRC_POLYLENGTH_8B) && defined(CRC_POLYLENGTH_16B) && defined(CRC_POLYLENGTH_32B)
        case 7:
            HW_TypeDef->Init.CRCLength = CRC_POLYLENGTH_7B;
            break;
        case 8:
            HW_TypeDef->Init.CRCLength = CRC_POLYLENGTH_8B;
            break;
        case 16:
            HW_TypeDef->Init.CRCLength = CRC_POLYLENGTH_16B;
            break;
        case 32:
            HW_TypeDef->Init.CRCLength = CRC_POLYLENGTH_32B;
            break;
        default :
            goto _exit;
#else
        case 32:
            HW_TypeDef->Init.CRCLength = CRC_POLYLENGTH_32B;
            break;
        default :
            goto _exit;
#endif /* defined(CRC_POLYLENGTH_7B) && defined(CRC_POLYLENGTH_8B) && defined(CRC_POLYLENGTH_16B) && defined(CRC_POLYLENGTH_32B) */
        }

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

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32MP1)
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

#if defined(BSP_USING_HASH)
static rt_err_t _hash_update(struct hwcrypto_hash *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t tickstart = 0;
    rt_uint32_t result = RT_EOK;
    struct stm32_hwcrypto_device *stm32_hw_dev = (struct stm32_hwcrypto_device *)ctx->parent.device->user_data;
    rt_mutex_take(&stm32_hw_dev->mutex, RT_WAITING_FOREVER);

#if defined(SOC_SERIES_STM32MP1)
    HASH_HandleTypeDef *HW_TypeDef = (HASH_HandleTypeDef *)(ctx->parent.contex);
    /* Start HASH computation using DMA transfer */
    switch (ctx->parent.type)
    {
    case HWCRYPTO_TYPE_SHA224:
       result = HAL_HASHEx_SHA224_Start_DMA(HW_TypeDef, (uint8_t *)in, length);
       break;
    case HWCRYPTO_TYPE_SHA256:
       result = HAL_HASHEx_SHA256_Start_DMA(HW_TypeDef, (uint8_t *)in, length);
       break;
    case HWCRYPTO_TYPE_MD5:
       result = HAL_HASH_MD5_Start_DMA(HW_TypeDef, (uint8_t *)in, length);
       break;
    case HWCRYPTO_TYPE_SHA1:
       result = HAL_HASH_SHA1_Start_DMA(HW_TypeDef, (uint8_t *)in, length);
       break;
    default :
        rt_kprintf("not support hash type: %x", ctx->parent.type);
        break;
    }
    if (result != HAL_OK)
    {
        goto _exit;
    }
    /* Wait for DMA transfer to complete */
    tickstart = rt_tick_get();
    while (HAL_HASH_GetState(HW_TypeDef) == HAL_HASH_STATE_BUSY)
    {
        if (rt_tick_get() - tickstart > 0xFFFF)
        {
            result = RT_ETIMEOUT;
            goto _exit;
        }
    }

#endif
_exit:
    rt_mutex_release(&stm32_hw_dev->mutex);

   return  result;
}

static rt_err_t _hash_finish(struct hwcrypto_hash *ctx, rt_uint8_t *out, rt_size_t length)
{
    rt_uint32_t result = RT_EOK;
    struct stm32_hwcrypto_device *stm32_hw_dev = (struct stm32_hwcrypto_device *)ctx->parent.device->user_data;
    rt_mutex_take(&stm32_hw_dev->mutex, RT_WAITING_FOREVER);
#if defined(SOC_SERIES_STM32MP1)
    HASH_HandleTypeDef *HW_TypeDef = (HASH_HandleTypeDef *)(ctx->parent.contex);
    /* Get the computed digest value */
    switch (ctx->parent.type)
    {
    case HWCRYPTO_TYPE_SHA224:
       result = HAL_HASHEx_SHA224_Finish(HW_TypeDef, (uint8_t *)out, length);
       break;

    case HWCRYPTO_TYPE_SHA256:
       result = HAL_HASHEx_SHA256_Finish(HW_TypeDef, (uint8_t *)out, length);
       break;

    case HWCRYPTO_TYPE_MD5:
       result = HAL_HASH_MD5_Finish(HW_TypeDef, (uint8_t *)out, length);
       break;

    case HWCRYPTO_TYPE_SHA1:
       result = HAL_HASH_SHA1_Finish(HW_TypeDef, (uint8_t *)out, length);
       break;

    default :
        rt_kprintf("not support hash type: %x", ctx->parent.type);
        break;
    }
    if (result != HAL_OK)
    {
        goto _exit;
    }
#endif

_exit:
    rt_mutex_release(&stm32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_hash_ops hash_ops =
{
    .update = _hash_update,
    .finish  = _hash_finish
};

#endif /* BSP_USING_HASH */

#if defined(BSP_USING_CRYP)
static rt_err_t _cryp_crypt(struct hwcrypto_symmetric *ctx,
                            struct hwcrypto_symmetric_info *info)
{
    rt_uint32_t result = RT_EOK;
    rt_uint32_t tickstart = 0;

    struct stm32_hwcrypto_device *stm32_hw_dev = (struct stm32_hwcrypto_device *)ctx->parent.device->user_data;
    rt_mutex_take(&stm32_hw_dev->mutex, RT_WAITING_FOREVER);

#if defined(SOC_SERIES_STM32MP1)
    CRYP_HandleTypeDef *HW_TypeDef = (CRYP_HandleTypeDef *)(ctx->parent.contex);

    switch (ctx->parent.type)
    {
    case HWCRYPTO_TYPE_AES_ECB:
       HW_TypeDef->Init.Algorithm = CRYP_AES_ECB;
       break;

    case HWCRYPTO_TYPE_AES_CBC:
       HW_TypeDef->Init.Algorithm = CRYP_AES_CBC;
       break;

    case HWCRYPTO_TYPE_AES_CTR:
       HW_TypeDef->Init.Algorithm = CRYP_AES_CTR;
       break;

    case HWCRYPTO_TYPE_DES_ECB:
       HW_TypeDef->Init.Algorithm = CRYP_DES_ECB;
       break;

    case HWCRYPTO_TYPE_DES_CBC:
       HW_TypeDef->Init.Algorithm = CRYP_DES_CBC;
       break;

    default :
        rt_kprintf("not support cryp type: %x", ctx->parent.type);
        break;
    }

    HAL_CRYP_DeInit(HW_TypeDef);

    HW_TypeDef->Init.DataType       = CRYP_DATATYPE_8B;
    HW_TypeDef->Init.DataWidthUnit  = CRYP_DATAWIDTHUNIT_BYTE;
    HW_TypeDef->Init.KeySize        = CRYP_KEYSIZE_128B;
    HW_TypeDef->Init.pKey           = (uint32_t*)ctx->key;

    result =  HAL_CRYP_Init(HW_TypeDef);
    if (result != HAL_OK)
    {
        /* Initialization Error */
        goto _exit;
    }
    if (info->mode == HWCRYPTO_MODE_ENCRYPT)
    {
         result = HAL_CRYP_Encrypt_DMA(HW_TypeDef, (uint32_t *)info->in, info->length, (uint32_t *)info->out);
    }
    else if (info->mode == HWCRYPTO_MODE_DECRYPT)
    {
         result = HAL_CRYP_Decrypt_DMA(HW_TypeDef, (uint32_t *)info->in, info->length, (uint32_t *)info->out);
    }
    else
    {
        rt_kprintf("error cryp mode : %02x!\n", info->mode);
        result = RT_ERROR;
        goto _exit;
    }

    if (result != HAL_OK)
    {
        goto _exit;
    }

    tickstart = rt_tick_get();
    while (HAL_CRYP_GetState(HW_TypeDef) != HAL_CRYP_STATE_READY)
    {
        if (rt_tick_get() - tickstart > 0xFFFF)
        {
            result = RT_ETIMEOUT;
            goto _exit;
        }
    }

#endif

    if (result != HAL_OK)
    {
        goto _exit;
    }

_exit:
    rt_mutex_release(&stm32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_symmetric_ops cryp_ops =
{
    .crypt = _cryp_crypt
};
#endif

static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
    {
        __HAL_RCC_RNG_CLK_ENABLE();
        RNG_HandleTypeDef *hrng = rt_calloc(1, sizeof(RNG_HandleTypeDef));
        if (RT_NULL == hrng)
        {
            res = -RT_ERROR;
            break;
        }
#if defined(SOC_SERIES_STM32MP1)
        hrng->Instance = RNG2;
#else
        hrng->Instance = RNG;
#endif
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
#if defined(SOC_SERIES_STM32MP1)
        hcrc->Instance = CRC2;
#else
        hcrc->Instance = CRC;
#endif
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32MP1)
        hcrc->Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_DISABLE;
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

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
    {
        HASH_HandleTypeDef *hash = rt_calloc(1, sizeof(HASH_HandleTypeDef));
        if (RT_NULL == hash)
        {
            res = -RT_ERROR;
            break;
        }
#if defined(SOC_SERIES_STM32MP1)
        /* enable dma for hash */
        __HAL_RCC_DMA2_CLK_ENABLE();
        HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

        hash->Init.DataType = HASH_DATATYPE_8B;
        if (HAL_HASH_Init(hash) != HAL_OK)
        {
            res = -RT_ERROR;
        }
#endif
        ctx->contex = hash;
        ((struct hwcrypto_hash *)ctx)->ops = &hash_ops;

        break;
    }
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
    {
        CRYP_HandleTypeDef *cryp = rt_calloc(1, sizeof(CRYP_HandleTypeDef));
        if (RT_NULL == cryp)
        {
            res = -RT_ERROR;
            break;
        }
#if defined(SOC_SERIES_STM32MP1)
        cryp->Instance = CRYP2;
        /* enable dma for cryp */
        __HAL_RCC_DMA2_CLK_ENABLE();

        HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

        HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

        if (HAL_CRYP_Init(cryp) != HAL_OK)
        {
            res = -RT_ERROR;
        }
#endif
        ctx->contex = cryp;
        ((struct hwcrypto_symmetric *)ctx)->ops = &cryp_ops;

        break;
    }
#endif  /* BSP_USING_CRYP */

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

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        __HAL_HASH_RESET_HANDLE_STATE((HASH_HandleTypeDef *)(ctx->contex));
        HAL_HASH_DeInit((HASH_HandleTypeDef *)(ctx->contex));
        break;
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
         HAL_CRYP_DeInit((CRYP_HandleTypeDef *)(ctx->contex));
         break;
#endif /* BSP_USING_CRYP */

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
            rt_memcpy(des->contex, src->contex, sizeof(RNG_HandleTypeDef));
        }
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(CRC_HandleTypeDef));
        }
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(HASH_HandleTypeDef));
        }
        break;
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(CRYP_HandleTypeDef));
        }
        break;
#endif /* BSP_USING_CRYP */

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

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        __HAL_HASH_RESET_HANDLE_STATE((HASH_HandleTypeDef *)(ctx->contex));
        break;
#endif /* BSP_USING_HASH*/

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        break;
#endif /* BSP_USING_CRYP */

    default:
        break;
    }
}

#if defined(HASH2_IN_DMA_INSTANCE)
void HASH2_DMA_IN_IRQHandler(void)
{
    extern DMA_HandleTypeDef hdma_hash_in;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_hash_in);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(CRYP2_IN_DMA_INSTANCE)
void CRYP2_DMA_IN_IRQHandler(void)
{
    extern DMA_HandleTypeDef hdma_cryp_in;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_cryp_in);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined (CRYP2_OUT_DMA_INSTANCE)
void CRYP2_DMA_OUT_IRQHandler(void)
{
    extern DMA_HandleTypeDef hdma_cryp_out;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_cryp_out);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

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
#elif defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
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
    rt_mutex_init(&_crypto_dev.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_PRIO);
    return 0;
}
INIT_DEVICE_EXPORT(stm32_hw_crypto_device_init);
