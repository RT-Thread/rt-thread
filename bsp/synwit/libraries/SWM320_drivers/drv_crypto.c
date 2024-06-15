/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-10     lik          first version
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

#define DEFAULT_CRC (CRC)
#define DEFAULT_INIVAL (0x00000000)
#define DEFAULT_INBITS (2)
#define DEFAULT_CRC1632 (0)
#define DEFAULT_OUT_NOT (0)
#define DEFAULT_OUT_REV (0)


struct swm_crc_cfg
{
    CRC_TypeDef *CRCx;
    uint32_t inival;
    uint8_t crc_inbits;
    uint8_t crc_1632;
    uint8_t crc_out_not;
    uint8_t crc_out_rev;
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

        crc_cfg->inival = ctx->crc_cfg.last_val;

        switch (ctx->crc_cfg.poly)
        {
        case 0x1021:
            crc_cfg->crc_1632 = 1;
            break;
        case 0x04C11DB7:
            crc_cfg->crc_1632 = 0;
            break;
        default:
            goto _exit;
        }

        switch (ctx->crc_cfg.width)
        {
        case 8:
            crc_cfg->crc_inbits = 2;
            break;
        case 16:
            crc_cfg->crc_inbits = 1;
            break;
        case 32:
            crc_cfg->crc_inbits = 0;
            break;
        default:
            goto _exit;
        }

        crc_cfg->crc_out_not = 0;

        switch (ctx->crc_cfg.flags)
        {
        case 0:
        case CRC_FLAG_REFIN:
            crc_cfg->crc_out_rev = 0;
            break;
        case CRC_FLAG_REFOUT:
        case CRC_FLAG_REFIN | CRC_FLAG_REFOUT:
            crc_cfg->crc_out_rev = 1;
            break;
        default:
            goto _exit;
        }

        CRC_Init(crc_cfg->CRCx, (crc_cfg->crc_inbits << 1) | crc_cfg->crc_1632, crc_cfg->crc_out_not, crc_cfg->crc_out_rev, crc_cfg->inival);
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
        crc_cfg->CRCx = DEFAULT_CRC;
        crc_cfg->inival = DEFAULT_INIVAL;
        crc_cfg->crc_inbits = DEFAULT_INBITS;
        crc_cfg->crc_1632 = DEFAULT_CRC1632;
        crc_cfg->crc_out_not = DEFAULT_OUT_NOT;
        crc_cfg->crc_out_rev = DEFAULT_OUT_REV;

        ctx->contex = crc_cfg;
        ((struct hwcrypto_crc *)ctx)->ops = &swm_crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */
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
    rt_mutex_init(&hwcrypto_obj.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_PRIO);
    return 0;
}
INIT_BOARD_EXPORT(swm_crypto_init);


#endif /* RT_USING_HWCRYPTO */
