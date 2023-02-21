/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_crypto.h"
#include <string.h>

#ifdef RT_USING_HWCRYPTO

//#define DRV_DEBUG
#define LOG_TAG "drv.crypto"
#include <drv_log.h>

struct swm_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

static struct swm_hwcrypto_device hwcrypto_obj;

#ifdef BSP_USING_CRC

struct swm_crc_cfg
{
    CRC_TypeDef *CRCx;
    CRC_InitStructure CRC_initstruct;
};

static struct hwcrypto_crc_cfg swm_crc_cfg;

static rt_uint32_t swm_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t result = 0;
    struct swm_hwcrypto_device *hwcrypto_dev = (struct swm_hwcrypto_device *)ctx->parent.device->user_data;

    struct swm_crc_cfg *crc_cfg = (struct swm_crc_cfg *)(ctx->parent.contex);

    rt_mutex_take(&hwcrypto_dev->mutex, RT_WAITING_FOREVER);

    if (memcmp(&swm_crc_cfg, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg)) != 0)
    {
        crc_cfg->CRCx = CRC;

        crc_cfg->CRC_initstruct.init_crc = ctx->crc_cfg.last_val;

        switch (ctx->crc_cfg.poly)
        {
        case 0x07:
            crc_cfg->CRC_initstruct.Poly = CRC_POLY_107;
            break;
        case 0x1021:
            crc_cfg->CRC_initstruct.Poly = CRC_POLY_11021;
            break;
        case 0x8005:
            crc_cfg->CRC_initstruct.Poly = CRC_POLY_18005;
            break;
        case 0x04C11DB7:
            crc_cfg->CRC_initstruct.Poly = CRC_POLY_104C11DB7;
            break;
        default:

            goto _exit;
        }

        switch (ctx->crc_cfg.width)
        {
        case 8:
            crc_cfg->CRC_initstruct.in_width = CRC_WIDTH_8;
            break;
        case 16:
            crc_cfg->CRC_initstruct.in_width = CRC_WIDTH_16;
            break;
        case 32:
            crc_cfg->CRC_initstruct.in_width = CRC_WIDTH_32;
            break;
        default:
            goto _exit;
        }

        switch (ctx->crc_cfg.flags)
        {
        case 0:
            crc_cfg->CRC_initstruct.in_not = false;
            crc_cfg->CRC_initstruct.out_not = false;
            break;
        case CRC_FLAG_REFIN:
            crc_cfg->CRC_initstruct.in_not = true;
            crc_cfg->CRC_initstruct.out_not = false;
            break;
        case CRC_FLAG_REFOUT:
            crc_cfg->CRC_initstruct.in_not = false;
            crc_cfg->CRC_initstruct.out_not = true;
            break;
        case CRC_FLAG_REFIN | CRC_FLAG_REFOUT:
            crc_cfg->CRC_initstruct.in_not = true;
            crc_cfg->CRC_initstruct.out_not = true;
            break;
        default:
            goto _exit;
        }

        crc_cfg->CRC_initstruct.in_rev = CRC_REV_NOT;
        crc_cfg->CRC_initstruct.out_rev = CRC_REV_NOT;
        CRC_Init(crc_cfg->CRCx, &(crc_cfg->CRC_initstruct));
        memcpy(&swm_crc_cfg, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg));
    }

    for (uint32_t i = 0; i < length; i++)
        CRC_Write((uint32_t)in[i]);
    result = CRC_Result();

    ctx->crc_cfg.last_val = result;

    swm_crc_cfg.last_val = ctx->crc_cfg.last_val;
    result = (result ? result ^ (ctx->crc_cfg.xorout) : result);

_exit:
    rt_mutex_release(&hwcrypto_dev->mutex);

    return result;
}

static const struct hwcrypto_crc_ops swm_crc_ops =
    {
        .update = swm_crc_update,
};
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)

struct swm_rng_cfg
{
    SYS_TypeDef *SYSx;
};

static rt_uint32_t swm_rng_update(struct hwcrypto_rng *ctx)
{
    rt_uint32_t gen_randoml = 0, gen_randomh = 0;

    struct swm_rng_cfg *rng_cfg = (struct swm_rng_cfg *)(ctx->parent.contex);

    while ((rng_cfg->SYSx->PRNGCR & SYS_PRNGCR_RDY_Msk) == 0)
        __NOP();
    gen_randoml = rng_cfg->SYSx->PRNGDL;
    gen_randomh = rng_cfg->SYSx->PRNGDH;
    return gen_randoml;
}

static const struct hwcrypto_rng_ops swm_rng_ops =
    {
        .update = swm_rng_update,
};
#endif /* BSP_USING_RNG */

static rt_err_t swm_crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        struct swm_crc_cfg *crc_cfg = rt_calloc(1, sizeof(struct swm_crc_cfg));
        if (RT_NULL == crc_cfg)
        {
            res = -RT_ERROR;
            break;
        }

        ctx->contex = crc_cfg;
        ((struct hwcrypto_crc *)ctx)->ops = &swm_crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
    {
        struct swm_rng_cfg *rng_cfg = rt_calloc(1, sizeof(struct swm_rng_cfg));
        if (RT_NULL == rng_cfg)
        {
            res = -RT_ERROR;
            break;
        }
        rng_cfg->SYSx = SYS;
        rng_cfg->SYSx->HRCCR |= (1 << SYS_HRCCR_ON_Pos);
        rng_cfg->SYSx->LRCCR |= (1 << SYS_LRCCR_ON_Pos);
        rng_cfg->SYSx->PRNGCR = (0 << SYS_PRNGCR_CLR_Pos) |
                             (3 << SYS_PRNGCR_MODE_Pos);
        ctx->contex = rng_cfg;
        ((struct hwcrypto_rng *)ctx)->ops = &swm_rng_ops;

        break;
    }
#endif /* BSP_USING_RNG */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void swm_crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    struct swm_crc_cfg *crc_cfg = (struct swm_crc_cfg *)(ctx->contex);
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        crc_cfg->CRCx->CR &= ~CRC_CR_EN_Msk;
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_RNG */

    default:
        break;
    }

    rt_free(ctx->contex);
}

static rt_err_t swm_crypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(struct swm_crc_cfg));
        }
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(struct swm_rng_cfg));
        }
        break;
#endif /* BSP_USING_RNG */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void swm_crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    struct swm_crc_cfg *crc_cfg = (struct swm_crc_cfg *)(ctx->contex);
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        crc_cfg->CRCx->CR &= ~CRC_CR_EN_Msk;
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_RNG */

    default:
        break;
    }
}

static const struct rt_hwcrypto_ops swm_hwcrypto_ops =
    {
        .create = swm_crypto_create,
        .destroy = swm_crypto_destroy,
        .copy = swm_crypto_clone,
        .reset = swm_crypto_reset,
};

int swm_crypto_init(void)
{
    rt_uint32_t cpuid[2] = {0};

    hwcrypto_obj.dev.ops = &swm_hwcrypto_ops;

    cpuid[0] = SCB->CPUID;
    hwcrypto_obj.dev.id = 0;
    rt_memcpy(&hwcrypto_obj.dev.id, cpuid, 8);

    hwcrypto_obj.dev.user_data = &hwcrypto_obj;

    if (rt_hwcrypto_register(&hwcrypto_obj.dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }
    rt_mutex_init(&hwcrypto_obj.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_BOARD_EXPORT(swm_crypto_init);

#endif /* RT_USING_HWCRYPTO */
