/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
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

struct swm_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

#ifdef BSP_USING_CRC

struct hash_ctx_des
{
    struct swm_crc_cfg contex;
};

static struct hwcrypto_crc_cfg crc_backup_cfg;

static rt_uint32_t _crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t result = 0;
    struct swm_hwcrypto_device *swm_hw_dev = (struct swm_hwcrypto_device *)ctx->parent.device->user_data;

    struct swm_crc_cfg *hw_crc_cfg = (struct swm_crc_cfg *)(ctx->parent.contex);

    rt_mutex_take(&swm_hw_dev->mutex, RT_WAITING_FOREVER);

    if (memcmp(&crc_backup_cfg, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg)) != 0)
    {
        hw_crc_cfg->CRCx = CRC;

        hw_crc_cfg->inival = ctx->crc_cfg.last_val;

        switch (ctx->crc_cfg.width)
        {
        case 8:
            hw_crc_cfg->crc_inbits = 2;
            break;
        case 16:
            hw_crc_cfg->crc_inbits = 1;
            break;
        case 32:
            hw_crc_cfg->crc_inbits = 0;
            break;
        default:
            goto _exit;
        }
        switch (ctx->crc_cfg.poly)
        {
        case 0x1021:
            hw_crc_cfg->crc_1632 = 1;
            break;
        case 0x04C11DB7:
            hw_crc_cfg->crc_1632 = 0;
            break;
        default:
            goto _exit;
        }

        hw_crc_cfg->crc_out_not = 0;

        switch (ctx->crc_cfg.flags)
        {
        case 0:
        case CRC_FLAG_REFIN:
            hw_crc_cfg->crc_out_rev = 0;
            break;
        case CRC_FLAG_REFOUT:
        case CRC_FLAG_REFIN | CRC_FLAG_REFOUT:
            hw_crc_cfg->crc_out_rev = 1;
            break;
        default:
            goto _exit;
        }

        CRC_Init(hw_crc_cfg->CRCx, (hw_crc_cfg->crc_inbits << 1) | hw_crc_cfg->crc_1632, hw_crc_cfg->crc_out_not, hw_crc_cfg->crc_out_rev, hw_crc_cfg->inival);
        memcpy(&crc_backup_cfg, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg));
    }

    for (uint32_t i = 0; i < length; i++)
        CRC_Write((uint32_t)in[i]);
    result = CRC_Result();

    ctx->crc_cfg.last_val = result;

    crc_backup_cfg.last_val = ctx->crc_cfg.last_val;
    result = (result ? result ^ (ctx->crc_cfg.xorout) : result);

_exit:
    rt_mutex_release(&swm_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_crc_ops crc_ops =
    {
        .update = _crc_update,
};

static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        struct swm_crc_cfg *contex = rt_calloc(1, sizeof(struct swm_crc_cfg));
        if (RT_NULL == contex)
        {
            res = -RT_ERROR;
            break;
        }
        contex->CRCx = DEFAULT_CRC;
        contex->inival = DEFAULT_INIVAL;
        contex->crc_inbits = DEFAULT_INBITS;
        contex->crc_1632 = DEFAULT_CRC1632;
        contex->crc_out_not = DEFAULT_OUT_NOT;
        contex->crc_out_rev = DEFAULT_OUT_REV;

        ctx->contex = contex;
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
    struct swm_crc_cfg *hw_crc_cfg = (struct swm_crc_cfg *)(ctx->contex);
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        hw_crc_cfg->CRCx->CR &= ~CRC_CR_EN_Msk;
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
    struct swm_crc_cfg *hw_crc_cfg = (struct swm_crc_cfg *)(ctx->contex);
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        hw_crc_cfg->CRCx->CR &= ~CRC_CR_EN_Msk;
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

int rt_hw_crypto_init(void)
{
    static struct swm_hwcrypto_device _crypto_dev;
    rt_uint32_t cpuid[2] = {0};

    _crypto_dev.dev.ops = &_ops;

    cpuid[0] = SCB->CPUID;
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
INIT_BOARD_EXPORT(rt_hw_crypto_init);

#endif /* BSP_USING_WDT */
#endif /* RT_USING_WDT */
